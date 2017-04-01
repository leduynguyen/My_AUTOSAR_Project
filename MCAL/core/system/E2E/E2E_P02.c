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

#include "E2E_P02.h"
//#define USE_LDEBUG_PRINTF // Uncomment this to turn debug statements on.
//#include "debug.h"

/* @req SWS_E2E_00153 */
#define MAX_P02_COUNTER_VALUE           (15)
/* @req SWS_E2E_00121 */
#define MAX_P02_DATA_LENGTH_IN_BITS     (8*256)
#define MIN_P02_DATA_LENGTH_IN_BITS     (8*2)


/* @req SWS_E2E_00135*/
static INLINE uint8 CalculateDeltaCounter(uint8 receivedCounter, uint8 lastValidCounter)
{
    uint8 status;
    if (receivedCounter >= lastValidCounter) {
        status = receivedCounter - lastValidCounter;
    }
    else {
        status = MAX_P02_COUNTER_VALUE + 1 + receivedCounter - lastValidCounter;
    }
    return status;
}


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00152 */
static INLINE Std_ReturnType CheckConfig(const E2E_P02ConfigType* Config) {

    /* Check for NULL pointers */
    Std_ReturnType status;
    status = E2E_E_OK;
    if (Config == NULL) {
        status = E2E_E_INPUTERR_NULL; /* MISRA exception */
    }

    /* Check input parameters values */
    else if (((Config->DataLength % 8) != 0) || (Config->DataLength < MIN_P02_DATA_LENGTH_IN_BITS) ||
        (Config->DataLength > MAX_P02_DATA_LENGTH_IN_BITS)) {
        status = E2E_E_INPUTERR_WRONG; /* MISRA exception */
    }

    /* Offset of the E2E header in the Data[] array in bits. It shall be: 0 ≤ Offset ≤ MaxDataLength-(2*8). */
    else if (Config->Offset > (MAX_P02_DATA_LENGTH_IN_BITS-MIN_P02_DATA_LENGTH_IN_BITS)) {
        status = E2E_E_INPUTERR_WRONG;
    } else {
        status = E2E_E_OK;
    }
    return status;

}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00117 */
/* @req SWS_E2E_00118 */
/* @req SWS_E2E_00119 */
/* @req SWS_E2E_00120 */
/* @req SWS_E2E_00121 */
/* @req SWS_E2E_00122 */
/* @req SWS_E2E_00123 */
/* @req SWS_E2E_00124 */
/* @req SWS_E2E_00126 */
/* @req SWS_E2E_00127 */
/* @req SWS_E2E_00128 */
/* @req SWS_E2E_00129 */
/* @req SWS_E2E_00130 */
/* @req SWS_E2E_00132 */
/* @req SWS_E2E_00133 */
/* @req SWS_E2E_00160 */
/* @req SWS_E2E_00219 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P02Protect( E2E_P02ConfigType* ConfigPtr, E2E_P02ProtectStateType* StatePtr, uint8* DataPtr ) {

    Std_ReturnType status;
    status = E2E_E_OK;
    uint8 dataId;
    uint8 crc;
    Std_ReturnType returnValue = CheckConfig(ConfigPtr);

    if (E2E_E_OK != returnValue) {
        status = returnValue; /* MISRA exception */
    }

    else if ((StatePtr == NULL) || (DataPtr == NULL)) {
        status = E2E_E_INPUTERR_NULL; /* MISRA exception */

    } else {
        /* Increase counter*/
        StatePtr->Counter = (StatePtr->Counter + 1) % (MAX_P02_COUNTER_VALUE + 1);

        /* Add counter to data */
        DataPtr[1] = (DataPtr[1] & 0xF0u) | (StatePtr->Counter & 0x0Fu);

        /* Get the data id */
        dataId = ConfigPtr->DataIDList[StatePtr->Counter];

        /* Calculate CRC over data and then data id */
        crc = Crc_CalculateCRC8H2F(&DataPtr[1],  (ConfigPtr->DataLength/8)-1, 0x00, TRUE);
        crc = Crc_CalculateCRC8H2F(&dataId,  1, crc, FALSE);

        /* Write crc to data */
        DataPtr[0] = crc;
    }
    return status;

}


static INLINE boolean IsFirstDataSinceInitialisation( const E2E_P02ConfigType* ConfigPtr, E2E_P02CheckStateType* StatePtr, uint8 receivedCounter ) {

    boolean status;
    status = FALSE;
    if (StatePtr->WaitForFirstData == TRUE) {
        StatePtr->WaitForFirstData = FALSE;
        StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;
        StatePtr->LastValidCounter = receivedCounter;
        StatePtr->Status= E2E_P02STATUS_INITIAL;

        status = TRUE;
    }

    return status;
}


/* Ok, this is the normal case. Calculate delta counter, Check the counter delta */
static INLINE void DoChecks( const E2E_P02ConfigType* ConfigPtr, E2E_P02CheckStateType* StatePtr, uint8 receivedCounter ) {
    uint8 delta;

    delta = CalculateDeltaCounter(receivedCounter, StatePtr->LastValidCounter);
//    LDEBUG_PRINTF("deltaCounter= 0x%02x", deltaCounter );
//    LDEBUG_PRINTF("\n");

    if (delta == 0) {
        //LDEBUG_PRINTF("deltaCounter == 0");
        //LDEBUG_PRINTF("\n");
        if (StatePtr->NoNewOrRepeatedDataCounter < MAX_P02_COUNTER_VALUE) {
            StatePtr->NoNewOrRepeatedDataCounter++;
        }

        StatePtr->Status= E2E_P02STATUS_REPEATED;
    }
    else if (delta == 1) {
        //LDEBUG_PRINTF("deltaCounter == 1");
        //LDEBUG_PRINTF("\n");
        StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;
        StatePtr->LastValidCounter = receivedCounter;
        StatePtr->LostData = 0;

        if (StatePtr->NoNewOrRepeatedDataCounter <= ConfigPtr->MaxNoNewOrRepeatedData) {
            StatePtr->NoNewOrRepeatedDataCounter = 0;

            if (StatePtr->SyncCounter > 0) {
                StatePtr->SyncCounter--;
                StatePtr->Status = E2E_P02STATUS_SYNC;
            }
            else {
                StatePtr->Status = E2E_P02STATUS_OK;
            }
         }
         else {
             StatePtr->NoNewOrRepeatedDataCounter = 0;
             StatePtr->SyncCounter = ConfigPtr->SyncCounterInit;
             StatePtr->Status = E2E_P02STATUS_SYNC;
         }
    }
    else if (delta > StatePtr->MaxDeltaCounter) {
//        LDEBUG_PRINTF("deltaCounter > StatePtr->MaxDeltaCounter");
//        LDEBUG_PRINTF("\n");

        StatePtr->NoNewOrRepeatedDataCounter= 0;
        StatePtr->SyncCounter = ConfigPtr->SyncCounterInit;

        if (StatePtr->SyncCounter > 0) {
            StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;
            StatePtr->LastValidCounter = receivedCounter;
        }

        StatePtr->Status= E2E_P02STATUS_WRONGSEQUENCE;

    }  // delta > MaxDeltaCounter
    else {
//        LDEBUG_PRINTF("delta > MaxDeltaCounter");
//        LDEBUG_PRINTF("\n");
        StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;
        StatePtr->LastValidCounter = receivedCounter;
        StatePtr->LostData = delta - 1;

        if (StatePtr->NoNewOrRepeatedDataCounter <= ConfigPtr->MaxNoNewOrRepeatedData) {
            StatePtr->NoNewOrRepeatedDataCounter= 0;

            if (StatePtr->SyncCounter > 0) {
                StatePtr->SyncCounter--;
                StatePtr->Status = E2E_P02STATUS_SYNC;
            }
            else {
                StatePtr->Status = E2E_P02STATUS_OKSOMELOST;
            }
        }
        else {
            StatePtr->NoNewOrRepeatedDataCounter= 0;
            StatePtr->SyncCounter = ConfigPtr->SyncCounterInit;
            StatePtr->Status = E2E_P02STATUS_SYNC;
        }

    } // 1 < delta <= MaxDeltaCounter
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00118 */
/* @req SWS_E2E_00119 */
/* @req SWS_E2E_00120 */
/* @req SWS_E2E_00121 */
/* @req SWS_E2E_00122 */
/* @req SWS_E2E_00123 */
/* @req SWS_E2E_00125 */
/* @req SWS_E2E_00134 */
/* @req SWS_E2E_00136 */
/* @req SWS_E2E_00137 */
/* @req SWS_E2E_00138 */
/* @req SWS_E2E_00139 */
/* @req SWS_E2E_00140 */
/* @req SWS_E2E_00141 */
/* @req SWS_E2E_00142 */
/* @req SWS_E2E_00143 */
/* @req SWS_E2E_00145 */
/* @req SWS_E2E_00146 */
/* @req SWS_E2E_00147 */
/* @req SWS_E2E_00148 */
/* @req SWS_E2E_00149 */
/* @req SWS_E2E_00150 */
/* @req SWS_E2E_00151 */
/* @req SWS_E2E_00161 */
/* @req SWS_E2E_00219 */
/* @req SWS_E2E_00298 */
/* @req SWS_E2E_00299 */
/* @req SWS_E2E_00300 */
/* @req SWS_E2E_00301 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P02Check( E2E_P02ConfigType* ConfigPtr, E2E_P02CheckStateType* StatePtr, uint8* DataPtr ) {

    Std_ReturnType status;
    status = E2E_E_OK;
    boolean ret;
    ret = TRUE;
    uint8 receivedCounter;
    uint8 dataId;
    uint8 crc;

    Std_ReturnType returnValue = CheckConfig(ConfigPtr);
    if (E2E_E_OK != returnValue) {
        status = returnValue;  /* MISRA exception */
    } else {

        if ((StatePtr == NULL) || (DataPtr == NULL)) {
            /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
            return E2E_E_INPUTERR_NULL; /* MISRA exception */
        }

        /* This is the stated behavior in figure 7-10 but it seems wrong. This means that if more than 15
         * messages are received with wrong CRC, the first message with correct CRC will be have state
         * OKSOMELOST even though it should be WRONGSEQUENCE.
         */
        if (StatePtr->MaxDeltaCounter < MAX_P02_COUNTER_VALUE) {
            StatePtr->MaxDeltaCounter++;
        }

        if (StatePtr->NewDataAvailable == FALSE) {

            if (StatePtr->NoNewOrRepeatedDataCounter < MAX_P02_COUNTER_VALUE) {
                StatePtr->NoNewOrRepeatedDataCounter++;
            }

            StatePtr->Status = E2E_P02STATUS_NONEWDATA;
            status = E2E_E_OK;
            ret = FALSE;
        }
        if (ret == TRUE) {
            receivedCounter = DataPtr[1] & 0xFu;

            dataId = ConfigPtr->DataIDList[receivedCounter];

            /* Calculate CRC over data and then data id */
            crc = Crc_CalculateCRC8H2F(&DataPtr[1],  (ConfigPtr->DataLength/8)-1, 0x00, TRUE);
            crc = Crc_CalculateCRC8H2F(&dataId,  1, crc, FALSE);

            /* Compare calculate and received crc */
            if (crc != DataPtr[0]) {
                StatePtr->Status = E2E_P02STATUS_WRONGCRC;
                status = E2E_E_OK;
            }

            /* Check if this is the first data since initialization */
            else if (IsFirstDataSinceInitialisation(ConfigPtr, StatePtr, receivedCounter) == TRUE) {
                status = E2E_E_OK;

            } else {

                DoChecks(ConfigPtr, StatePtr, receivedCounter);
            }
        }
    }
    return status;
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00387 */
/* @req SWS_E2E_00388 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P02ProtectInit( E2E_P02ProtectStateType* StatePtr ) {

    if (StatePtr == NULL) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_NULL; /* MISRA exception */
    }

    StatePtr->Counter = 0;

    return E2E_E_OK;
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00391 */
/* @req SWS_E2E_00392 */  /* UC_E2E_00208 overwrites init values */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P02CheckInit( E2E_P02CheckStateType* StatePtr ) {

    if (StatePtr == NULL) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_NULL; /* MISRA exception */
    }

    StatePtr->LastValidCounter = 0;
    StatePtr->MaxDeltaCounter = 0;
    StatePtr->WaitForFirstData = TRUE;
    StatePtr->NewDataAvailable = FALSE;
    StatePtr->LostData = 0;
    StatePtr->Status = E2E_P02STATUS_NONEWDATA;
    StatePtr->SyncCounter = 0;
    StatePtr->NoNewOrRepeatedDataCounter = 0;

    return E2E_E_OK;
}


/* @req SWS_E2E_00379 */
/* @req SWS_E2E_00380 */
/* @req SWS_E2E_00381 */
/* @req SWS_E2E_00477 */
static INLINE E2E_PCheckStatusType E2E_P02MapStatusToSM_TRUE(E2E_P02CheckStatusType Status) {
    E2E_PCheckStatusType retValue = E2E_P_ERROR;

    switch( Status ) {
        case E2E_P02STATUS_OK:
        case E2E_P02STATUS_OKSOMELOST:
        case E2E_P02STATUS_SYNC:
            retValue = E2E_P_OK;
            break;
        case E2E_P02STATUS_REPEATED:
            retValue = E2E_P_REPEATED;
            break;
        case E2E_P02STATUS_NONEWDATA:
            retValue = E2E_P_NONEWDATA;
            break;
        case E2E_P02STATUS_WRONGSEQUENCE:
        case E2E_P02STATUS_INITIAL:
            retValue = E2E_P_WRONGSEQUENCE;
            break;
        default:
            retValue = E2E_P_ERROR;
            break;
    }

    return retValue;
}

/* @req SWS_E2E_00379 */
/* @req SWS_E2E_00380 */
/* @req SWS_E2E_00381 */
/* @req SWS_E2E_00477 */
static INLINE E2E_PCheckStatusType E2E_P02MapStatusToSM_FALSE(E2E_P02CheckStatusType Status) {
    E2E_PCheckStatusType retValue = E2E_P_ERROR;

    switch( Status ) {
        case E2E_P02STATUS_OK:
        case E2E_P02STATUS_OKSOMELOST:
        case E2E_P02STATUS_INITIAL:
            retValue = E2E_P_OK;
            break;
        case E2E_P02STATUS_REPEATED:
            retValue = E2E_P_REPEATED;
            break;
        case E2E_P02STATUS_NONEWDATA:
            retValue = E2E_P_NONEWDATA;
            break;
        case E2E_P02STATUS_WRONGSEQUENCE:
        case E2E_P02STATUS_SYNC:
            retValue = E2E_P_WRONGSEQUENCE;
            break;
        default:
            retValue = E2E_P_ERROR;
            break;
    }

    return retValue;
}


/* @req SWS_E2E_00379 */
/* @req SWS_E2E_00380 */
/* @req SWS_E2E_00381 */
/* @req SWS_E2E_00477 */
E2E_PCheckStatusType E2E_P02MapStatusToSM( Std_ReturnType CheckReturn, E2E_P02CheckStatusType Status, boolean profileBehavior ) {

    E2E_PCheckStatusType retValue = E2E_P_ERROR;

    if (CheckReturn != E2E_E_OK) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return retValue;
    }

    if (profileBehavior == TRUE) { //ASR4.2.2 behavior

        retValue = E2E_P02MapStatusToSM_TRUE(Status);
    }
    else { //ASR4.2.2 pre-behavior

        retValue = E2E_P02MapStatusToSM_FALSE(Status);
    }

    return retValue;
}
