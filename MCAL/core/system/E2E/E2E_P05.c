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

/* @req SWS_E2E_00049 */
/* @req SWS_E2E_00215 */
/* @req SWS_E2E_00221 */

#include "E2E_P05.h"


/* @req SWS_E2E_00397 */
#define MAX_P05_COUNTER_VALUE           (255)
/* @req SWS_E2E_00437 */
#define MAX_P05_DATA_LENGTH_IN_BITS     (8*4096)
#define MIN_P05_DATA_LENGTH_IN_BITS     (8*3)


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00404 */
/* @req SWS_E2E_00437 */
static INLINE Std_ReturnType VerifyProtectInputs( const E2E_P05ConfigType* ConfigPtr, const E2E_P05ProtectStateType* StatePtr, const uint8* DataPtr, uint16 Length ) {

    Std_ReturnType status;
    status = E2E_E_OK;
    /* Check for NULL pointers */
    if ((ConfigPtr == NULL) || (StatePtr == NULL) || (DataPtr == NULL)) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_NULL; /* MISRA exception */
    }

    /* The offset shall be a multiple of 8 and 0 ≤ Offset ≤ MaxDataLength-(3*8). */
    if ( ((ConfigPtr->Offset % 8) != 0) || (ConfigPtr->Offset > (MAX_P05_DATA_LENGTH_IN_BITS-MIN_P05_DATA_LENGTH_IN_BITS)) ||
         (ConfigPtr->Offset > ((8*Length)-MIN_P05_DATA_LENGTH_IN_BITS))) {
        status = E2E_E_INPUTERR_WRONG;
    }

    else if ( ((8*Length) < MIN_P05_DATA_LENGTH_IN_BITS) || ((8*Length) > MAX_P05_DATA_LENGTH_IN_BITS) || ((8*Length) != ConfigPtr->DataLength) ) {
        status = E2E_E_INPUTERR_WRONG;

    } else {
        status = E2E_E_OK;
    }

    return status;
}


/* @req SWS_E2E_00469 */
static INLINE uint16 ComputeOffset( const E2E_P05ConfigType* ConfigPtr ) {

    return (ConfigPtr->Offset/8);
}


/* @req SWS_E2E_00405 */
static INLINE void WriteCounter( uint8* DataPtr, uint16 offset, const E2E_P05ProtectStateType* StatePtr ) {

    DataPtr[offset+2] = (StatePtr->Counter & 0xFFu) & 0xFFu;
}


/* @req SWS_E2E_00399 */
/* @req SWS_E2E_00400 */
/* @req SWS_E2E_00401 */
/* @req SWS_E2E_00406 */
static INLINE uint16 ComputeCRC( const uint8* DataPtr, uint16 length, uint16 offset, uint16 dataId  ) {

    uint16 lengthBytes = (length-offset)-2;
    uint16 crc;
    uint8 dataIdNibble;


    if (offset > 0) {
        /* compute CRC over bytes that are before CRC */
        crc = Crc_CalculateCRC16(&DataPtr[0], offset, 0xFFFFu, TRUE);

        /* Compute CRC over bytes that are after CRC (if any) */
        crc = Crc_CalculateCRC16(&DataPtr[offset+2], lengthBytes, crc, FALSE);
    }
    else {

        /* Compute CRC over bytes that are after CRC (if any) */
        crc = Crc_CalculateCRC16(&DataPtr[offset+2], lengthBytes, 0xFFFFu, TRUE);
    }

    dataIdNibble = ((dataId) & 0xFFu);
    crc = Crc_CalculateCRC16(&dataIdNibble, 1, crc, FALSE);

    dataIdNibble = ((dataId>>8) & 0xFFu);
    crc = Crc_CalculateCRC16(&dataIdNibble, 1, crc, FALSE);

    return crc;
}


/* @req SWS_E2E_00407 */
static INLINE void WriteCRC( uint8* DataPtr, uint16 offset, uint16 crc ) {

    DataPtr[offset  ] = ((crc & 0x00FFu)      ) & 0xFFu;
    DataPtr[offset+1] = ((crc & 0xFF00u) >>  8) & 0xFFu;
}


/* @req SWS_E2E_00397 */
/* @req SWS_E2E_00409 */
static INLINE void IncrementCounter( E2E_P05ProtectStateType* StatePtr ) {

    StatePtr->Counter = (StatePtr->Counter + 1) % (MAX_P05_COUNTER_VALUE + 1);
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00394 */
/* @req SWS_E2E_00397 */
/* @req SWS_E2E_00399 */
/* @req SWS_E2E_00400 */
/* @req SWS_E2E_00401 */
/* @req SWS_E2E_00403 */
/* @req SWS_E2E_00404 */
/* @req SWS_E2E_00405 */
/* @req SWS_E2E_00406 */
/* @req SWS_E2E_00407 */
/* @req SWS_E2E_00409 */
/* @req SWS_E2E_00437 */
/* @req SWS_E2E_00446 */
/* @req SWS_E2E_00469 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P05Protect( E2E_P05ConfigType* ConfigPtr, E2E_P05ProtectStateType* StatePtr, uint8* DataPtr, uint16 Length ) {

    uint16 offset;
    uint16 crc;

    Std_ReturnType returnValue = VerifyProtectInputs(ConfigPtr, StatePtr, DataPtr, Length);

    if (E2E_E_OK != returnValue) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return returnValue; /* MISRA exception */
    }

    offset = ComputeOffset(ConfigPtr);

    WriteCounter(DataPtr, offset, StatePtr);

    crc = ComputeCRC(DataPtr, Length, offset, ConfigPtr->DataID);

    WriteCRC(DataPtr, offset, crc);

    IncrementCounter(StatePtr);

    return E2E_E_OK;
}


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00412 */
static INLINE Std_ReturnType VerifyCheckInputs( boolean* NewDataAvailable, const E2E_P05ConfigType* ConfigPtr, const E2E_P05CheckStateType* StatePtr, const uint8* DataPtr, uint16 Length ) {

    Std_ReturnType status;
    status = E2E_E_OK;
    *NewDataAvailable = FALSE;

    /* Check for NULL pointers */
    if ((ConfigPtr == NULL) || (StatePtr == NULL)) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_NULL;
    }

    if ( !(((DataPtr != NULL) && (Length != 0)) || ((DataPtr == NULL) && (Length == 0))) ) {
        status = E2E_E_INPUTERR_WRONG; /* MISRA exception */
    }

    else if (DataPtr == NULL) {
        status = E2E_E_OK;
    }

    /* Check input parameters values */
    /* The offset shall be a multiple of 8 and 0 ≤ Offset ≤ MaxDataLength-(3*8). */
    else if ( ((ConfigPtr->Offset % 8) != 0) || (ConfigPtr->Offset > (MAX_P05_DATA_LENGTH_IN_BITS-MIN_P05_DATA_LENGTH_IN_BITS)) ||
         (ConfigPtr->Offset > ((8*Length)-MIN_P05_DATA_LENGTH_IN_BITS))) {
        status = E2E_E_INPUTERR_WRONG;
    }

    else if ( ((8*Length) < MIN_P05_DATA_LENGTH_IN_BITS) || ((8*Length) > MAX_P05_DATA_LENGTH_IN_BITS) || ((8*Length) != ConfigPtr->DataLength) ) {
        status = E2E_E_INPUTERR_WRONG;
    } else {

        *NewDataAvailable = TRUE;
    }
    return status;
}


/* @req SWS_E2E_00413 */
static INLINE uint8 ReadCounter( const uint8* DataPtr, uint16 offset ) {

    uint8 receivedCounter = 0;

    receivedCounter |= (DataPtr[offset+2] & 0xFFu);

    return receivedCounter;
}


/* @req SWS_E2E_00414 */
static INLINE uint16 ReadCRC( const uint8* DataPtr, uint16 offset ) {

    uint16 receivedCRC = 0;

    receivedCRC |= (((uint16)DataPtr[offset ]       ) & 0x00FFu);
    receivedCRC |= (((uint16)DataPtr[offset+1] <<  8) & 0xFF00u);

    return receivedCRC;
}


/* @req SWS_E2E_00416 */
static INLINE uint8 CalculateDeltaCounter(uint8 receivedCounter, uint8 lastValidCounter)
{
    uint8 status;
    if (receivedCounter >= lastValidCounter) {
        status = receivedCounter - lastValidCounter;
    }
    else {
        status = (uint8)((uint32)MAX_P05_COUNTER_VALUE + 1 + (uint32)receivedCounter - (uint32)lastValidCounter);
    }
    return status;
}


/* @req SWS_E2E_00416 */
static INLINE void DoChecks( E2E_P05CheckStateType* StatePtr, const boolean* NewDataAvailable, const E2E_P05ConfigType* ConfigPtr, uint16 receivedCRC, uint16 computedCRC, uint8 receivedCounter ) {

    uint8 deltaCounter;

    if (*NewDataAvailable == FALSE) {
        StatePtr->Status = E2E_P05STATUS_NONEWDATA;
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return;
    }

    if (receivedCRC != computedCRC) {
        StatePtr->Status = E2E_P05STATUS_ERROR;
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return;
    }

    deltaCounter = CalculateDeltaCounter(receivedCounter, StatePtr->Counter);

    if (deltaCounter > ConfigPtr->MaxDeltaCounter) {
        StatePtr->Status = E2E_P05STATUS_WRONGSEQUENCE;
    }
    else if (deltaCounter == 0) {
        StatePtr->Status = E2E_P05STATUS_REPEATED;
    }
    else if (deltaCounter == 1) {
        StatePtr->Status = E2E_P05STATUS_OK;
    }
    else {
        StatePtr->Status = E2E_P05STATUS_OKSOMELOST;
    }

    StatePtr->Counter = receivedCounter;
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00394 */
/* @req SWS_E2E_00399 */
/* @req SWS_E2E_00400 */
/* @req SWS_E2E_00401 */
/* @req SWS_E2E_00406 */
/* @req SWS_E2E_00411 */
/* @req SWS_E2E_00412 */
/* @req SWS_E2E_00413 */
/* @req SWS_E2E_00414 */
/* @req SWS_E2E_00416 */
/* @req SWS_E2E_00437 */
/* @req SWS_E2E_00440 */
/* @req SWS_E2E_00449 */
/* @req SWS_E2E_00469 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P05Check( E2E_P05ConfigType* ConfigPtr, E2E_P05CheckStateType* StatePtr, uint8* DataPtr, uint16 Length ) {

    boolean NewDataAvailable;
    uint16 offset;
    uint8 receivedCounter = 0;
    uint16 receivedCRC = 0;
    uint16 computedCRC = 0;

    Std_ReturnType returnValue = VerifyCheckInputs(&NewDataAvailable, ConfigPtr, StatePtr, DataPtr, Length);

    if (E2E_E_OK != returnValue) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return returnValue; /* MISRA exception */
    }

    if (NewDataAvailable == TRUE) {

        offset = ComputeOffset(ConfigPtr);

        receivedCounter = ReadCounter(DataPtr, offset);

        receivedCRC = ReadCRC(DataPtr, offset);

        computedCRC = ComputeCRC(DataPtr, Length, offset, ConfigPtr->DataID);
    }

    DoChecks(StatePtr, &NewDataAvailable, ConfigPtr, receivedCRC, computedCRC, receivedCounter);

    return E2E_E_OK;
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00397 */
/* @req SWS_E2E_00438 */
/* @req SWS_E2E_00447 */
/* @req SWS_E2E_00448 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P05ProtectInit( E2E_P05ProtectStateType* StatePtr ) {

    if (StatePtr == NULL) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_NULL; /* MISRA exception */
    }

    StatePtr->Counter = 0;

    return E2E_E_OK;
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00439 */
/* @req SWS_E2E_00450 */
/* @req SWS_E2E_00451 */
/* @req SWS_E2E_00472 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P05CheckInit( E2E_P05CheckStateType* StatePtr ) {

    if (StatePtr == NULL) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_NULL; /* MISRA exception */
    }

    StatePtr->Status = E2E_P05STATUS_ERROR;
    StatePtr->Counter = 0xFF;

    return E2E_E_OK;
}


/* @req SWS_E2E_00452 */
/* @req SWS_E2E_00453 */
/* @req SWS_E2E_00454 */
E2E_PCheckStatusType E2E_P05MapStatusToSM( Std_ReturnType CheckReturn, E2E_P05CheckStatusType Status ) {

    E2E_PCheckStatusType retValue = E2E_P_ERROR;

    if (CheckReturn != E2E_E_OK) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return retValue;
    }

    switch( Status ) {
        case E2E_P05STATUS_OK:
        case E2E_P05STATUS_OKSOMELOST:
            retValue = E2E_P_OK;
            break;
        case E2E_P05STATUS_REPEATED:
            retValue = E2E_P_REPEATED;
            break;
        case E2E_P05STATUS_NONEWDATA:
            retValue = E2E_P_NONEWDATA;
            break;
        case E2E_P05STATUS_WRONGSEQUENCE:
            retValue = E2E_P_WRONGSEQUENCE;
            break;
        default:
            retValue = E2E_P_ERROR;
            break;
    }

    return retValue;
}
