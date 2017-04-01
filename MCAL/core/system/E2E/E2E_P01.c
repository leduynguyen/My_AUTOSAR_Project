/*-------------------------------- Arctic Core ------------------------------
 * Copyright (C) 2013, ArcCore AB, Sweden, www.arccore.com.
 * Contact: <contact@arccore.com>
 * 
 * You may ONLY use this file:
 * 1)if you have a valid commercial ArcCore license and then in accordance with  
 * the terms contained in the written license agreement between you and ArcCore, 
 * or alternatively
 * 2)if you follow the terms found in GNU General Public License version 2 as 
 * published by the Free Software Foundation and appearing in the file 
 * LICENSE.GPL included in the packaging of this file or here 
 * <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>
 *-------------------------------- Arctic Core -----------------------------*/

/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.2.2 */

/* @req SWS_E2E_00115 */

/* @req SWS_E2E_00215 */
/* @req SWS_E2E_00049 */
/* @req SWS_E2E_00221 */

#include "E2E_P01.h"
//#define USE_LDEBUG_PRINTF // Uncomment this to turn debug statements on.
//#include "debug.h"

/* @req SWS_E2E_00018 */
#define MAX_P01_DATA_LENGTH_IN_BITS    (240)
/* @req SWS_E2E_00020 */
#define MAX_P01_COUNTER_VALUE          (14)


static INLINE uint8 CalculateDeltaCounter(uint8 receivedCounter, uint8 lastValidCounter) {
    uint8 res;
    res = 0;
    if (receivedCounter >= lastValidCounter) {
        res = receivedCounter - lastValidCounter;
    }
    else {
        res = MAX_P01_COUNTER_VALUE + 1 + receivedCounter - lastValidCounter;
    }
    return res;
}


/* @req SWS_E2E_00018 */
/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00169 */
/* @req SWS_E2E_00227  Profile variant 1A, No explicit support for variants but the config allows such a configuration */
/* @req SWS_E2E_00228  Profile variant 1B, No explicit support for variants but the config allows such a configuration */
/* @req SWS_E2E_00306 */
/* @req SWS_E2E_00307  Profile variant 1C, No explicit support for variants but the config allows such a configuration */
/* UC_E2E_00053 Any user of E2E Profile 1 shall use whenever possible the defined E2E variants. */
static INLINE Std_ReturnType CheckConfig(const E2E_P01ConfigType* Config) {

    Std_ReturnType status;
    status = E2E_E_OK;
    /* Check for NULL pointers */
    if (Config == NULL) {
        status = E2E_E_INPUTERR_NULL;
    }

    /* Check input parameters values */
    else if ((Config->DataLength > MAX_P01_DATA_LENGTH_IN_BITS) || ((Config->DataLength % 8) != 0)  ||
        ((Config->CounterOffset % 4) != 0) || ((Config->CRCOffset % 8) != 0)) {
        status = E2E_E_INPUTERR_WRONG;
    }

    /* Check that input parameters do not overlap and fits into the data array. It is enough to
     * check if the CRC and Counter are in the same byte since the CRC is one byte long */
    else if (((Config->CRCOffset + 8) > Config->DataLength) || ((Config->CounterOffset + 4) > Config->DataLength) ||
        ((Config->CRCOffset/8) == (Config->CounterOffset/8))) {
        status = E2E_E_INPUTERR_WRONG;
    }

    /* For DataIDMode different than E2E_P01_DATAID_NIBBLE, DataIDNibbleOffset shall be initialized to 0 (even if it is ignored by E2E Library). */
    else if ((Config->DataIDMode != E2E_P01_DATAID_NIBBLE) && (Config->DataIDNibbleOffset != 0)) {
        status = E2E_E_INPUTERR_WRONG;
    }

    /* In E2E Profile 1, with E2E_P01DataIDMode equal to E2E_P01_DATAID_LOW, the high byte of Data ID shall be set to 0x00. */
    else if ((Config->DataIDMode == E2E_P01_DATAID_LOW) && ((Config->DataID>>8) != 0)) {
        status = E2E_E_INPUTERR_WRONG;
    }

    /* In E2E Profile 1, with E2E_P01DataIDMode equal to E2E_P01_DATAID_NIBBLE, the high nibble of the high byte shall be 0x0. */
    else if ((Config->DataIDMode == E2E_P01_DATAID_NIBBLE) && ((Config->DataID>>12) != 0)) {
        status = E2E_E_INPUTERR_WRONG;
    }
    else {
        /* return E2E_E_OK*/
        status = E2E_E_OK;
    }
    return status;
}


/* @req SWS_E2E_00070 */
/* @req SWS_E2E_00082 */
/* @req SWS_E2E_00083 */
/* @req SWS_E2E_00163 */
/* @req SWS_E2E_00190 */
/* @req SWS_E2E_00218 */

/* The start value is 0x00 for E2E (0xFF is standard in the CRC lib). The final
 * XOR is 0x00 (0xFF is standard) so we must XOR the crc with 0xFF
 */
static uint8 CalculateCrc(const E2E_P01ConfigType* Config, uint8 Counter, const uint8* Data)
{
    /*lint -e{835} Lint exception: Readability  */
    uint8 crc = 0x00u ^ CRC8_XOR; /* Need to cancel first XOR in Crc */
    uint8 lowerByteId = (uint8)Config->DataID;
    uint8 upperByteId = (uint8)(Config->DataID>>8);

    /* Calculate CRC on the Data ID */
    if (Config->DataIDMode == E2E_P01_DATAID_BOTH)
    {
        crc = Crc_CalculateCRC8(&lowerByteId, 1, crc, FALSE);
        crc = Crc_CalculateCRC8(&upperByteId, 1, crc, FALSE);
    }
    else if (Config->DataIDMode == E2E_P01_DATAID_LOW)
    {
        crc = Crc_CalculateCRC8(&lowerByteId, 1, crc, FALSE);
    }
    else if (Config->DataIDMode == E2E_P01_DATAID_NIBBLE)
    {
        crc = Crc_CalculateCRC8(&lowerByteId, 1, crc, FALSE);
        upperByteId = 0;
        crc = Crc_CalculateCRC8(&upperByteId, 1, crc, FALSE);
    }
    else if ((Counter % 2) == 0) //E2E_P01_DATAID_ALT: even counter
    {
        crc = Crc_CalculateCRC8(&lowerByteId, 1, crc, FALSE);
    }
    else //E2E_P01_DATAID_ALT: odd counter
    {
        crc = Crc_CalculateCRC8(&upperByteId, 1, crc, FALSE);
    }


    /* Calculate CRC on the data */
    if (Config->CRCOffset >= 8) {
        crc = Crc_CalculateCRC8 (Data, (Config->CRCOffset / 8), crc, FALSE);
    }

    if ((Config->CRCOffset / 8) < ((Config->DataLength / 8) - 1)) {
        crc = Crc_CalculateCRC8 (&Data[(Config->CRCOffset/8) + 1],
                                (((Config->DataLength / 8) - (Config->CRCOffset / 8)) - 1),
                                crc, FALSE);
    }

    return crc ^ CRC8_XOR; /* Need to cancel last XOR in Crc*/
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00070 */
/* @req SWS_E2E_00075 */
/* @req SWS_E2E_00166 */
/* @req SWS_E2E_00169 */
/* @req SWS_E2E_00195 */
/* @req SWS_E2E_00218 */
/* @req SWS_E2E_00306 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P01Protect( E2E_P01ConfigType* ConfigPtr, E2E_P01ProtectStateType* StatePtr, uint8* DataPtr ) {

    Std_ReturnType status;
    status = E2E_E_OK;
    Std_ReturnType returnValue = CheckConfig(ConfigPtr);

    if (E2E_E_OK != returnValue) {
        status = returnValue;
    }
    else if ((StatePtr == NULL) || (DataPtr == NULL)) {
        status = E2E_E_INPUTERR_NULL; /* MISRA exception */
    } else {
        /* Put counter in data*/
        if ((ConfigPtr->CounterOffset % 8) == 0) {
            DataPtr[ConfigPtr->CounterOffset/8] = (DataPtr[(ConfigPtr->CounterOffset/8)] & 0xF0u) | (StatePtr->Counter & 0x0Fu);
        }
        else {
            DataPtr[ConfigPtr->CounterOffset/8] = (DataPtr[ConfigPtr->CounterOffset/8] & 0x0Fu) | ((StatePtr->Counter<<4) & 0xF0u);
        }

        /* Put counter in data for E2E_P01_DATAID_NIBBLE */ // ASR4.2.2
        if (ConfigPtr->DataIDMode == E2E_P01_DATAID_NIBBLE) {
            if ((ConfigPtr->DataIDNibbleOffset % 8) == 0) {
                DataPtr[ConfigPtr->DataIDNibbleOffset/8] = (DataPtr[(ConfigPtr->DataIDNibbleOffset/8)] & 0xF0u) | ((uint8)((ConfigPtr->DataID>>8) & 0x0Fu));
            }
            else {
                DataPtr[ConfigPtr->DataIDNibbleOffset/8] = (DataPtr[ConfigPtr->DataIDNibbleOffset/8] & 0x0Fu) | ((uint8)((ConfigPtr->DataID>>4) & 0xF0u));
            }
        }

        /* Calculate CRC */
        DataPtr[(ConfigPtr->CRCOffset/8)] = CalculateCrc(ConfigPtr, StatePtr->Counter, DataPtr);

        /* Update counter */
        StatePtr->Counter = E2E_UpdateCounter(StatePtr->Counter);

    }
    return status;
}


static INLINE uint8 ReadCounter( const E2E_P01ConfigType* ConfigPtr, const uint8* DataPtr ) {
    uint8 receivedCounter = 0;

    /* Counter offset is 4-bit aligned, this check is used to find out if high or low nibble */
    if ((ConfigPtr->CounterOffset % 8) == 0) {
        receivedCounter = DataPtr[ConfigPtr->CounterOffset/8] & 0x0Fu;
    }
    else {
        receivedCounter = (DataPtr[ConfigPtr->CounterOffset/8] >> 4) & 0x0Fu;
    }

    return receivedCounter;
}


static INLINE uint8 ReadDataIDNibbleOffset( const E2E_P01ConfigType* ConfigPtr, const uint8* DataPtr ) {
    uint8 receivedDataIDNibble = 0;

    if (ConfigPtr->DataIDMode == E2E_P01_DATAID_NIBBLE) {

        if ((ConfigPtr->DataIDNibbleOffset % 8) == 0) {
            receivedDataIDNibble = DataPtr[(ConfigPtr->DataIDNibbleOffset)/8] & 0x0Fu;
        }
        else {
            receivedDataIDNibble = (DataPtr[(ConfigPtr->DataIDNibbleOffset)/8] >> 4) & 0x0Fu;
        }
    }

    return receivedDataIDNibble;
}


static INLINE boolean IsFirstDataSinceInitialisation( const E2E_P01ConfigType* ConfigPtr, E2E_P01CheckStateType* StatePtr, uint8 receivedCounter ) {

    boolean status;
    status = FALSE;
    if (StatePtr->WaitForFirstData == TRUE) {

        StatePtr->WaitForFirstData = FALSE;
        StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;
        StatePtr->LastValidCounter = receivedCounter;
        StatePtr->Status = E2E_P01STATUS_INITIAL;

        status = TRUE;
    }
    return status;
}


static INLINE boolean IsCheckOfReceivedDataNotOk( const E2E_P01ConfigType* ConfigPtr, E2E_P01CheckStateType* StatePtr, uint8 receivedCounter, uint8 receivedCrc, uint8 calculatedCrc, uint8 receivedDataIDNibble ) {

    boolean status;
    status = FALSE;
    if ( (receivedCrc != calculatedCrc) ||
         ( (ConfigPtr->DataIDMode == E2E_P01_DATAID_NIBBLE) && (receivedDataIDNibble != ((ConfigPtr->DataID)>>8)) )
       ) {
//		LDEBUG_PRINTF("receivedCrcreceivedDataIDNibble check");
//		LDEBUG_PRINTF("\n");
        StatePtr->Status = E2E_P01STATUS_WRONGCRC;
        status = TRUE;
    }


    /* Check if this is the first data since initialization */
    if (IsFirstDataSinceInitialisation(ConfigPtr, StatePtr, receivedCounter) == TRUE) {
//		LDEBUG_PRINTF("first data check");
//		LDEBUG_PRINTF("\n");
        status = TRUE;
    }

    return status;
}


/* Ok, this is the normal case. Calculate delta counter, Check the counter delta */
static INLINE void DoChecks( const E2E_P01ConfigType* ConfigPtr, E2E_P01CheckStateType* StatePtr, uint8 receivedCounter ) {
    uint8 delta;

    delta = CalculateDeltaCounter(receivedCounter, StatePtr->LastValidCounter);

    if (delta == 0) {
        //	LDEBUG_PRINTF("deltaCounter=0");
        //	LDEBUG_PRINTF("\n");

            if (StatePtr->NoNewOrRepeatedDataCounter < MAX_P01_COUNTER_VALUE) {
                StatePtr->NoNewOrRepeatedDataCounter++;
            }

            StatePtr->Status = E2E_P01STATUS_REPEATED;
    }
    else if (delta == 1) {
        //	LDEBUG_PRINTF("deltaCounter=1");
        //	LDEBUG_PRINTF("\n");

            StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;
            StatePtr->LastValidCounter = receivedCounter;
            StatePtr->LostData = 0;

            if (StatePtr->NoNewOrRepeatedDataCounter <= ConfigPtr->MaxNoNewOrRepeatedData) {
                StatePtr->NoNewOrRepeatedDataCounter = 0;

                if (StatePtr->SyncCounter > 0) {
                    StatePtr->SyncCounter--;
                    StatePtr->Status = E2E_P01STATUS_SYNC;
                }
                else {
                    StatePtr->Status = E2E_P01STATUS_OK;
                }
            }
            else {
                StatePtr->NoNewOrRepeatedDataCounter = 0;
                StatePtr->SyncCounter = ConfigPtr->SyncCounterInit;
                StatePtr->Status = E2E_P01STATUS_SYNC;
            }
    }
    else if (delta <= StatePtr->MaxDeltaCounter) { // 1 < delta <= MaxDeltaCounter
        //	LDEBUG_PRINTF("1<deltaCounter<=Max");
        //	LDEBUG_PRINTF("\n");

            StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;
            StatePtr->LastValidCounter = receivedCounter;
            StatePtr->LostData = delta - 1;

            if (StatePtr->NoNewOrRepeatedDataCounter <= ConfigPtr->MaxNoNewOrRepeatedData) {
                StatePtr->NoNewOrRepeatedDataCounter= 0;

                if (StatePtr->SyncCounter > 0) {
                    StatePtr->SyncCounter--;
                    StatePtr->Status = E2E_P01STATUS_SYNC;
                }
                else {
                    StatePtr->Status = E2E_P01STATUS_OKSOMELOST;
                }
            }
            else {
                StatePtr->NoNewOrRepeatedDataCounter= 0;
                StatePtr->SyncCounter = ConfigPtr->SyncCounterInit;
                StatePtr->Status = E2E_P01STATUS_SYNC;
            }
    }
    else { // delta > MaxDeltaCounter
        //	LDEBUG_PRINTF("deltaCounter>Max");
        //	LDEBUG_PRINTF("\n");

            StatePtr->NoNewOrRepeatedDataCounter= 0;
            StatePtr->SyncCounter = ConfigPtr->SyncCounterInit;

            if (StatePtr->SyncCounter > 0) {
                StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;
                StatePtr->LastValidCounter = receivedCounter;
            }

            StatePtr->Status = E2E_P01STATUS_WRONGSEQUENCE;
    }
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00076 */
/* @req SWS_E2E_00158 */
/* @req SWS_E2E_00196 */
/* @req SWS_E2E_00218 */
/* @req SWS_E2E_00306 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P01Check( E2E_P01ConfigType* ConfigPtr, E2E_P01CheckStateType* StatePtr, uint8* DataPtr ) {

    Std_ReturnType status;
    status = E2E_E_OK;
    boolean ret;
    ret = TRUE;
    uint8 receivedCounter;
    uint8 receivedCrc;
    uint8 calculatedCrc;
    uint8 receivedDataIDNibble;
    Std_ReturnType returnValue = CheckConfig(ConfigPtr);

    if (E2E_E_OK != returnValue) {
        status = returnValue;
    }

    else if ((StatePtr == NULL) || (DataPtr == NULL)) {
        status = E2E_E_INPUTERR_NULL; /* MISRA exception */
    } else {

        /* This is the stated behavior in figure 7-6 but it seems wrong. This means that if more than 15
         * messages are received with wrong CRC, the first message with correct CRC will be have state
         * OKSOMELOST even though it should be WRONGSEQUENCE.
         */
        // changed in ASR 4.2.2, figure is now 7-7
        if (StatePtr->MaxDeltaCounter < MAX_P01_COUNTER_VALUE) {
            StatePtr->MaxDeltaCounter++;
        }

        if (StatePtr->NewDataAvailable == FALSE) {

            if (StatePtr->NoNewOrRepeatedDataCounter < MAX_P01_COUNTER_VALUE) {
                StatePtr->NoNewOrRepeatedDataCounter++;
            }

            StatePtr->Status = E2E_P01STATUS_NONEWDATA;
            status = E2E_E_OK;  /* MISRA exception */
            ret = FALSE;
        }
        if (ret == TRUE){
            receivedCounter = ReadCounter(ConfigPtr, DataPtr);

            if (receivedCounter > MAX_P01_COUNTER_VALUE) {
                status = E2E_E_INPUTERR_WRONG;
            } else {
                receivedCrc = DataPtr[(ConfigPtr->CRCOffset/8)];

                receivedDataIDNibble = ReadDataIDNibbleOffset(ConfigPtr, DataPtr);

                calculatedCrc = CalculateCrc(ConfigPtr, receivedCounter, DataPtr);

                if (IsCheckOfReceivedDataNotOk(ConfigPtr, StatePtr, receivedCounter, receivedCrc, calculatedCrc, receivedDataIDNibble) == TRUE) {
                    status = E2E_E_OK;
                } else {
                    DoChecks(ConfigPtr, StatePtr, receivedCounter);
                }
            }
        }
    }
    return status;
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00075 */
/* @req SWS_E2E_00385 */
/* @req SWS_E2E_00386 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P01ProtectInit( E2E_P01ProtectStateType* StatePtr ) {

    Std_ReturnType status;
    status = E2E_E_OK;
    if (StatePtr == NULL) {
        status = E2E_E_INPUTERR_NULL; /* MISRA exception */
    } else {
        StatePtr->Counter = 0;
    }
    return status;
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00389 */ /* UC_E2E_00208 overwrites init values */
/* @req SWS_E2E_00390 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P01CheckInit( E2E_P01CheckStateType* StatePtr ) {

    Std_ReturnType status;
    status = E2E_E_OK;
    if (StatePtr == NULL) {
        status = E2E_E_INPUTERR_NULL; /* MISRA exception */
    } else {
        StatePtr->LastValidCounter = 0;
        StatePtr->MaxDeltaCounter = 0;
        StatePtr->WaitForFirstData = TRUE;
        StatePtr->NewDataAvailable = FALSE;
        StatePtr->LostData = 0;
        StatePtr->Status = E2E_P01STATUS_NONEWDATA;
        StatePtr->SyncCounter = 0;
        StatePtr->NoNewOrRepeatedDataCounter = 0;
    }
    return status;
}


/* @req SWS_E2E_00382 */
/* @req SWS_E2E_00383 */
/* @req SWS_E2E_00384 */
/* @req SWS_E2E_00476 */
static INLINE E2E_PCheckStatusType E2E_P01MapStatusToSM_TRUE(E2E_P01CheckStatusType Status) {
    E2E_PCheckStatusType retValue = E2E_P_ERROR;

    switch( Status ) {
        case E2E_P01STATUS_OK:
        case E2E_P01STATUS_OKSOMELOST:
        case E2E_P01STATUS_SYNC:
            retValue = E2E_P_OK;
            break;
        case E2E_P01STATUS_REPEATED:
            retValue = E2E_P_REPEATED;
            break;
        case E2E_P01STATUS_NONEWDATA:
            retValue = E2E_P_NONEWDATA;
            break;
        case E2E_P01STATUS_WRONGSEQUENCE:
        case E2E_P01STATUS_INITIAL:
            retValue = E2E_P_WRONGSEQUENCE;
            break;
        default:
            retValue = E2E_P_ERROR;
            break;
    }

    return retValue;
}

/* @req SWS_E2E_00382 */
/* @req SWS_E2E_00383 */
/* @req SWS_E2E_00384 */
/* @req SWS_E2E_00476 */
static INLINE E2E_PCheckStatusType E2E_P01MapStatusToSM_FALSE(E2E_P01CheckStatusType Status) {
    E2E_PCheckStatusType retValue = E2E_P_ERROR;

    switch( Status ) {
        case E2E_P01STATUS_OK:
        case E2E_P01STATUS_OKSOMELOST:
        case E2E_P01STATUS_INITIAL:
            retValue = E2E_P_OK;
            break;
        case E2E_P01STATUS_REPEATED:
            retValue = E2E_P_REPEATED;
            break;
        case E2E_P01STATUS_NONEWDATA:
            retValue = E2E_P_NONEWDATA;
            break;
        case E2E_P01STATUS_WRONGSEQUENCE:
        case E2E_P01STATUS_SYNC:
            retValue = E2E_P_WRONGSEQUENCE;
            break;
        default:
            retValue = E2E_P_ERROR;
            break;
    }

    return retValue;
}


/* @req SWS_E2E_00382 */
/* @req SWS_E2E_00383 */
/* @req SWS_E2E_00384 */
/* @req SWS_E2E_00476 */
E2E_PCheckStatusType E2E_P01MapStatusToSM( Std_ReturnType CheckReturn, E2E_P01CheckStatusType Status, boolean profileBehavior ) {

    E2E_PCheckStatusType retValue = E2E_P_ERROR;

    if (CheckReturn != E2E_E_OK) {
        retValue = E2E_P_ERROR;
    }

    else if (profileBehavior == TRUE) { //ASR4.2.2 behavior

        retValue = E2E_P01MapStatusToSM_TRUE(Status);
    }
    else { //ASR4.2.2 pre-behavior

        retValue = E2E_P01MapStatusToSM_FALSE(Status);
    }

    return retValue;
}
