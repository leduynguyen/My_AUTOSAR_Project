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

#include "E2E_P06.h"


/* @req SWS_E2E_00443 */
#define MAX_P06_COUNTER_VALUE           (255)
/* @req SWS_E2E_00441 */
#define MAX_P06_DATA_LENGTH_IN_BITS     (8*4096)
#define MIN_P06_DATA_LENGTH_IN_BITS     (8*5)


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00424 */
/* @req SWS_E2E_00441 */
static INLINE Std_ReturnType VerifyProtectInputs( const E2E_P06ConfigType* ConfigPtr, const E2E_P06ProtectStateType* StatePtr, const uint8* DataPtr, uint16 Length ) {

    Std_ReturnType status;
    status = E2E_E_OK;
    /* Check for NULL pointers */
    if ((ConfigPtr == NULL) || (StatePtr == NULL) || (DataPtr == NULL)) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_NULL; /* MISRA exception */
    }

    /* Check input parameters values */
    if ((ConfigPtr->MinDataLength < MIN_P06_DATA_LENGTH_IN_BITS) || (ConfigPtr->MaxDataLength < MIN_P06_DATA_LENGTH_IN_BITS) ||
        (ConfigPtr->MinDataLength > MAX_P06_DATA_LENGTH_IN_BITS) || (ConfigPtr->MaxDataLength > MAX_P06_DATA_LENGTH_IN_BITS) ||
        (ConfigPtr->MinDataLength > ConfigPtr->MaxDataLength)) {
        status = E2E_E_INPUTERR_WRONG; /* MISRA exception */
    }

    /* The offset shall be a multiple of 8 and 0 ≤ Offset ≤ MaxDataLength-(5*8). */
    else if ( ((ConfigPtr->Offset % 8) != 0) || (ConfigPtr->Offset > (MAX_P06_DATA_LENGTH_IN_BITS-MIN_P06_DATA_LENGTH_IN_BITS)) ||
         (ConfigPtr->Offset > ((8*Length)-MIN_P06_DATA_LENGTH_IN_BITS))) {
        status = E2E_E_INPUTERR_WRONG;
    }

    else if ( ((8*Length) < ConfigPtr->MinDataLength) || ((8*Length) > ConfigPtr->MaxDataLength) ) {
        status = E2E_E_INPUTERR_WRONG;

    } else {
        status = E2E_E_OK;
    }

    return status;
}


static INLINE uint8 ChangeBitEndianness(uint8 value)
{
    uint8 result = 0;

    result |= (value & 0x01u) << 7;
    result |= (value & 0x02u) << 5;
    result |= (value & 0x04u) << 3;
    result |= (value & 0x08u) << 1;
    result |= (value & 0x10u) >> 1;
    result |= (value & 0x20u) >> 3;
    result |= (value & 0x40u) >> 5;
    result |= (value & 0x80u) >> 7;

    return result;
}


/* @req SWS_E2E_00470 */
static INLINE uint16 ComputeOffset( const E2E_P06ConfigType* ConfigPtr ) {

    return (ConfigPtr->Offset/8);
}


/* @req SWS_E2E_00425 */
static INLINE void WriteLength( uint8* DataPtr, uint16 offset, uint16 Length ) {

    DataPtr[offset+2] = ChangeBitEndianness(((Length & 0xFF00u) >> 8) & 0xFFu);
    DataPtr[offset+3] = ChangeBitEndianness( (Length & 0x00FFu)       & 0xFFu);
}


/* @req SWS_E2E_00426 */
static INLINE void WriteCounter( uint8* DataPtr, uint16 offset, const E2E_P06ProtectStateType* StatePtr ) {

    DataPtr[offset+4] = ChangeBitEndianness( (StatePtr->Counter & 0xFFu) & 0xFFu);
}


/* @req SWS_E2E_00419 */
/* @req SWS_E2E_00420 */
/* @req SWS_E2E_00421 */
/* @req SWS_E2E_00427 */
/* @req SWS_E2E_00479 */
static INLINE uint16 ComputeCRC( const uint8* DataPtr, uint16 offset, uint16 dataId, uint16 Length ) {

    uint16 lengthBytes = (Length-offset)-2;
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

    dataIdNibble = ((dataId>>8) & 0xFFu);
    crc = Crc_CalculateCRC16(&dataIdNibble, 1, crc, FALSE);

    dataIdNibble = ((dataId) & 0xFFu);
    crc = Crc_CalculateCRC16(&dataIdNibble, 1, crc, FALSE);

    return crc;
}


/* @req SWS_E2E_00428 */
static INLINE void WriteCRC( uint8* DataPtr, uint16 offset, uint16 crc ) {

    DataPtr[offset  ] = ChangeBitEndianness(((crc & 0xFF00u) >>  8) & 0xFFu);
    DataPtr[offset+1] = ChangeBitEndianness(((crc & 0x00FFu)      ) & 0xFFu);
}


/* @req SWS_E2E_00417 */
/* @req SWS_E2E_00429 */
static INLINE void IncrementCounter( E2E_P06ProtectStateType* StatePtr ) {

    StatePtr->Counter = (StatePtr->Counter + 1) % (MAX_P06_COUNTER_VALUE + 1);
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00393 */
/* @req SWS_E2E_00417 */
/* @req SWS_E2E_00419 */
/* @req SWS_E2E_00420 */
/* @req SWS_E2E_00421 */
/* @req SWS_E2E_00423 */
/* @req SWS_E2E_00424 */
/* @req SWS_E2E_00425 */
/* @req SWS_E2E_00426 */
/* @req SWS_E2E_00427 */
/* @req SWS_E2E_00428 */
/* @req SWS_E2E_00429 */
/* @req SWS_E2E_00441 */
/* @req SWS_E2E_00470 */
/* @req SWS_E2E_00479 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P06Protect( E2E_P06ConfigType* ConfigPtr, E2E_P06ProtectStateType* StatePtr, uint8* DataPtr, uint16 Length ) {

    uint16 offset;
    uint16 crc;

    Std_ReturnType returnValue = VerifyProtectInputs(ConfigPtr, StatePtr, DataPtr, Length);

    if (E2E_E_OK != returnValue) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return returnValue; /* MISRA exception */
    }

    offset = ComputeOffset(ConfigPtr);

    WriteLength(DataPtr, offset, Length);

    WriteCounter(DataPtr, offset, StatePtr);

    crc = ComputeCRC(DataPtr, offset, ConfigPtr->DataID, Length);

    WriteCRC(DataPtr, offset, crc);

    IncrementCounter(StatePtr);

    return E2E_E_OK;
}


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00431 */
static INLINE Std_ReturnType VerifyCheckInputs( boolean* NewDataAvailable, const E2E_P06ConfigType* ConfigPtr, const E2E_P06CheckStateType* StatePtr, const uint8* DataPtr, uint16 Length ) {

    Std_ReturnType status;
    status = E2E_E_OK;
    *NewDataAvailable = FALSE;

    /* Check for NULL pointers */
    if ((ConfigPtr == NULL) || (StatePtr == NULL)) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_NULL;
    }

    /* Check input parameters values */
    if ((ConfigPtr->MinDataLength < MIN_P06_DATA_LENGTH_IN_BITS) || (ConfigPtr->MaxDataLength < MIN_P06_DATA_LENGTH_IN_BITS) ||
        (ConfigPtr->MinDataLength > MAX_P06_DATA_LENGTH_IN_BITS) || (ConfigPtr->MaxDataLength > MAX_P06_DATA_LENGTH_IN_BITS) ||
        (ConfigPtr->MinDataLength > ConfigPtr->MaxDataLength)) {
        status = E2E_E_INPUTERR_WRONG; /* MISRA exception */
    }

    else if ( !(((DataPtr != NULL) && (Length != 0)) || ((DataPtr == NULL) && (Length == 0))) ) {
        status = E2E_E_INPUTERR_WRONG; /* MISRA exception */
    }

    else if (DataPtr == NULL) {
        status = E2E_E_OK;
    }

    /* The offset shall be a multiple of 8 and 0 ≤ Offset ≤ MaxDataLength-(5*8). */
    else if ( ((ConfigPtr->Offset % 8) != 0) || (ConfigPtr->Offset > (MAX_P06_DATA_LENGTH_IN_BITS-MIN_P06_DATA_LENGTH_IN_BITS)) ||
         (ConfigPtr->Offset > ((8*Length)-MIN_P06_DATA_LENGTH_IN_BITS))) {
        status = E2E_E_INPUTERR_WRONG;
    }

    else if ( ((8*Length) < ConfigPtr->MinDataLength) || ((8*Length) > ConfigPtr->MaxDataLength) ) {
        status = E2E_E_INPUTERR_WRONG;
    } else {

        *NewDataAvailable = TRUE;
    }
    return status;
}


/* @req SWS_E2E_00432 */
static INLINE uint16 ReadLength( const uint8* DataPtr, uint16 offset ) {

    uint16 receivedLength = 0;

    receivedLength |= (((uint16)ChangeBitEndianness(DataPtr[offset+2]) << 8) & 0xFF00u);
    receivedLength |= (((uint16)ChangeBitEndianness(DataPtr[offset+3])     ) & 0x00FFu);

    return receivedLength;
}


/* @req SWS_E2E_00433 */
static INLINE uint8 ReadCounter( const uint8* DataPtr, uint16 offset ) {

    uint8 receivedCounter = 0;

    receivedCounter |= ((ChangeBitEndianness(DataPtr[offset+4])     ) & 0xFFu);

    return receivedCounter;
}


/* @req SWS_E2E_00434 */
static INLINE uint16 ReadCRC( const uint8* DataPtr, uint16 offset ) {

    uint16 receivedCRC = 0;

    receivedCRC |= (((uint16)ChangeBitEndianness(DataPtr[offset  ]) <<  8) & 0xFF00u);
    receivedCRC |= (((uint16)ChangeBitEndianness(DataPtr[offset+1])      ) & 0x00FFu);

    return receivedCRC;
}


/* @req SWS_E2E_00436 */
static INLINE uint8 CalculateDeltaCounter(uint8 receivedCounter, uint8 lastValidCounter)
{
    uint8 status;
    if (receivedCounter >= lastValidCounter) {
        status = receivedCounter - lastValidCounter;
    }
    else {
        status = (uint8)((uint32)MAX_P06_COUNTER_VALUE + 1 + (uint32)receivedCounter - (uint32)lastValidCounter);
    }
    return status;
}


/* @req SWS_E2E_00436 */
static INLINE void DoChecks( E2E_P06CheckStateType* StatePtr, const boolean* NewDataAvailable, const E2E_P06ConfigType* ConfigPtr, uint16 receivedCRC, uint16 computedCRC, uint16 receivedLength, uint16 Length, uint8 receivedCounter ) {

    uint8 deltaCounter;

    if (*NewDataAvailable == FALSE) {
        StatePtr->Status = E2E_P06STATUS_NONEWDATA;
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return;
    }

    if ( (receivedCRC != computedCRC) || (receivedLength != Length)) {
        StatePtr->Status = E2E_P06STATUS_ERROR;
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return;
    }

    deltaCounter = CalculateDeltaCounter(receivedCounter, StatePtr->Counter);

    if (deltaCounter > ConfigPtr->MaxDeltaCounter) {
        StatePtr->Status = E2E_P06STATUS_WRONGSEQUENCE;
    }
    else if (deltaCounter == 0) {
        StatePtr->Status = E2E_P06STATUS_REPEATED;
    }
    else if (deltaCounter == 1) {
        StatePtr->Status = E2E_P06STATUS_OK;
    }
    else {
        StatePtr->Status = E2E_P06STATUS_OKSOMELOST;
    }

    StatePtr->Counter = receivedCounter;
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00419 */
/* @req SWS_E2E_00457 */
/* @req SWS_E2E_00420 */
/* @req SWS_E2E_00421 */
/* @req SWS_E2E_00427 */
/* @req SWS_E2E_00430 */
/* @req SWS_E2E_00431 */
/* @req SWS_E2E_00432 */
/* @req SWS_E2E_00433 */
/* @req SWS_E2E_00434 */
/* @req SWS_E2E_00436 */
/* @req SWS_E2E_00441 */
/* @req SWS_E2E_00445*/
/* @req SWS_E2E_00457 */
/* @req SWS_E2E_00470 */
/* @req SWS_E2E_00479 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P06Check( E2E_P06ConfigType* ConfigPtr, E2E_P06CheckStateType* StatePtr, uint8* DataPtr, uint16 Length ) {

    boolean NewDataAvailable;
    uint16 offset;
    uint16 receivedLength = 0;
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

        receivedLength = ReadLength(DataPtr, offset);

        receivedCounter = ReadCounter(DataPtr, offset);

        receivedCRC = ReadCRC(DataPtr, offset);

        computedCRC = ComputeCRC(DataPtr, offset, ConfigPtr->DataID, Length);
    }

    DoChecks(StatePtr, &NewDataAvailable, ConfigPtr, receivedCRC, computedCRC, receivedLength, Length, receivedCounter);

    return E2E_E_OK;
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00417 */
/* @req SWS_E2E_00443 */
/* @req SWS_E2E_00455 */
/* @req SWS_E2E_00456 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P06ProtectInit( E2E_P06ProtectStateType* StatePtr ) {

    if (StatePtr == NULL) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_NULL; /* MISRA exception */
    }

    StatePtr->Counter = 0;

    return E2E_E_OK;
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00444 */
/* @req SWS_E2E_00458 */
/* @req SWS_E2E_00459 */
/* @req SWS_E2E_00473 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P06CheckInit( E2E_P06CheckStateType* StatePtr ) {

    if (StatePtr == NULL) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_NULL; /* MISRA exception */
    }

    StatePtr->Status = E2E_P06STATUS_ERROR;
    StatePtr->Counter = 0xFF;

    return E2E_E_OK;
}


/* @req SWS_E2E_00460 */
/* @req SWS_E2E_00461 */
/* @req SWS_E2E_00462 */
E2E_PCheckStatusType E2E_P06MapStatusToSM( Std_ReturnType CheckReturn, E2E_P06CheckStatusType Status ) {

    E2E_PCheckStatusType retValue = E2E_P_ERROR;

    if (CheckReturn != E2E_E_OK) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return retValue;
    }

    switch( Status ) {
        case E2E_P06STATUS_OK:
        case E2E_P06STATUS_OKSOMELOST:
            retValue = E2E_P_OK;
            break;
        case E2E_P06STATUS_REPEATED:
            retValue = E2E_P_REPEATED;
            break;
        case E2E_P06STATUS_NONEWDATA:
            retValue = E2E_P_NONEWDATA;
            break;
        case E2E_P06STATUS_WRONGSEQUENCE:
            retValue = E2E_P_WRONGSEQUENCE;
            break;
        default:
            retValue = E2E_P_ERROR;
            break;
    }

    return retValue;
}
