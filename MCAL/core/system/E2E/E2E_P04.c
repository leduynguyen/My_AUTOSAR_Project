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

#include "E2E_P04.h"

/* @req SWS_E2E_00478 */
#define MAX_P04_COUNTER_VALUE           (65535)
/* @req SWS_E2E_00334 */
#define MAX_P04_DATA_LENGTH_IN_BITS     (8*4096)
#define MIN_P04_DATA_LENGTH_IN_BITS     (8*12)


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00334 */
/* @req SWS_E2E_00363 */
/* Length of the data in bytes. */
static INLINE Std_ReturnType VerifyProtectInputs( const E2E_P04ConfigType* ConfigPtr, const E2E_P04ProtectStateType* StatePtr, const uint8* DataPtr, uint16 Length ) {

    Std_ReturnType status;
    status = E2E_E_OK;
    /* Check for NULL pointers */
    if ((ConfigPtr == NULL) || (StatePtr == NULL) || (DataPtr == NULL)) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_NULL; /* MISRA exception */
    }

    /* Check input parameters values */
    if ((ConfigPtr->MinDataLength < MIN_P04_DATA_LENGTH_IN_BITS) || (ConfigPtr->MaxDataLength < MIN_P04_DATA_LENGTH_IN_BITS) ||
        (ConfigPtr->MinDataLength > MAX_P04_DATA_LENGTH_IN_BITS) || (ConfigPtr->MaxDataLength > MAX_P04_DATA_LENGTH_IN_BITS) ||
        (ConfigPtr->MinDataLength > ConfigPtr->MaxDataLength)) {

        status = E2E_E_INPUTERR_WRONG; /* MISRA exception */
    }

    /* The offset shall be a multiple of 8 and 0 ≤ Offset ≤ MaxDataLength-(12*8). */
    else if ( ((ConfigPtr->Offset % 8) != 0) || (ConfigPtr->Offset > (MAX_P04_DATA_LENGTH_IN_BITS-MIN_P04_DATA_LENGTH_IN_BITS)) ||
         (ConfigPtr->Offset > ((Length*8)-MIN_P04_DATA_LENGTH_IN_BITS))) {

        status = E2E_E_INPUTERR_WRONG;
    }

    else if ( ((Length*8) < ConfigPtr->MinDataLength) || ((Length*8) > ConfigPtr->MaxDataLength) ) {

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


/* @req SWS_E2E_00376 */
static INLINE uint16 ComputeOffset( const E2E_P04ConfigType* ConfigPtr ) {

    return (ConfigPtr->Offset/8);
}


/* @req SWS_E2E_00364 */
static INLINE void WriteLength( uint8* DataPtr, uint16 offset, uint16 Length ) {

    DataPtr[offset  ] = ChangeBitEndianness(((Length & 0xFF00u) >> 8) & 0xFFu);
    DataPtr[offset+1] = ChangeBitEndianness( (Length & 0x00FFu)       & 0xFFu);
}


/* @req SWS_E2E_00365 */
static INLINE void WriteCounter( uint8* DataPtr, uint16 offset, const E2E_P04ProtectStateType* StatePtr ) {

    DataPtr[offset+2] = ChangeBitEndianness(((StatePtr->Counter & 0xFF00u) >> 8) & 0xFFu);
    DataPtr[offset+3] = ChangeBitEndianness( (StatePtr->Counter & 0x00FFu)       & 0xFFu);
}


/* @req SWS_E2E_00366 */
static INLINE void WriteDataID( uint8* DataPtr, uint16 offset, const E2E_P04ConfigType* ConfigPtr ) {

    DataPtr[offset+4] = ChangeBitEndianness(((ConfigPtr->DataID & 0xFF000000u) >> 24) & 0xFFu);
    DataPtr[offset+5] = ChangeBitEndianness(((ConfigPtr->DataID & 0x00FF0000u) >> 16) & 0xFFu);
    DataPtr[offset+6] = ChangeBitEndianness(((ConfigPtr->DataID & 0x0000FF00u) >>  8) & 0xFFu);
    DataPtr[offset+7] = ChangeBitEndianness(((ConfigPtr->DataID & 0x000000FFu)      ) & 0xFFu);
}


/* @req SWS_E2E_00330 */
/* @req SWS_E2E_00367 */
static INLINE uint32 ComputeCRC( const uint8* DataPtr, uint16 offset, uint16 Length ) {

    uint32 offsetBytes = (offset+8);
    uint32 crc;

    /* compute CRC over bytes that are before CRC */
    crc = Crc_CalculateCRC32P4(&DataPtr[0], offsetBytes, 0xFFFFFFFFu, TRUE);

    /* Compute CRC over bytes that are after CRC (if any) */
    if ((offset + 12) < Length) {
        offsetBytes = ((Length-offset)-12);
        crc = Crc_CalculateCRC32P4(&DataPtr[offset+12], offsetBytes, crc, FALSE);
    }

    return crc;
}


/* @req SWS_E2E_00368 */
static INLINE void WriteCRC( uint8* DataPtr, uint16 offset, uint32 crc ) {

    DataPtr[offset+ 8] = ChangeBitEndianness(((crc & 0xFF000000u) >> 24) & 0xFFu);
    DataPtr[offset+ 9] = ChangeBitEndianness(((crc & 0x00FF0000u) >> 16) & 0xFFu);
    DataPtr[offset+10] = ChangeBitEndianness(((crc & 0x0000FF00u) >>  8) & 0xFFu);
    DataPtr[offset+11] = ChangeBitEndianness(((crc & 0x000000FFu)      ) & 0xFFu);
}


/* @req SWS_E2E_00369 */
static INLINE void IncrementCounter( E2E_P04ProtectStateType* StatePtr ) {

    StatePtr->Counter = (StatePtr->Counter + 1) % (MAX_P04_COUNTER_VALUE + 1);
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00326 */
/* @req SWS_E2E_00329 */
/* @req SWS_E2E_00330 */
/* @req SWS_E2E_00338 */
/* @req SWS_E2E_00362 */
/* @req SWS_E2E_00363 */
/* @req SWS_E2E_00364 */
/* @req SWS_E2E_00365 */
/* @req SWS_E2E_00366 */
/* @req SWS_E2E_00367 */
/* @req SWS_E2E_00368 */
/* @req SWS_E2E_00369 */
/* @req SWS_E2E_00372 */
/* @req SWS_E2E_00376 */
/* Length of the data in bytes. */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P04Protect( E2E_P04ConfigType* ConfigPtr, E2E_P04ProtectStateType* StatePtr, uint8* DataPtr, uint16 Length ) {

    uint16 offset;
    uint32 crc;

    Std_ReturnType returnValue = VerifyProtectInputs(ConfigPtr, StatePtr, DataPtr, Length);

    if (E2E_E_OK != returnValue) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return returnValue; /* MISRA exception */
    }

    offset = ComputeOffset(ConfigPtr);

    WriteLength(DataPtr, offset, Length);

    WriteCounter(DataPtr, offset, StatePtr);

    WriteDataID(DataPtr, offset, ConfigPtr);

    crc = ComputeCRC(DataPtr, offset, Length);

    WriteCRC(DataPtr, offset, crc);

    IncrementCounter(StatePtr);

    return E2E_E_OK;
}


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00356 */
static INLINE Std_ReturnType VerifyCheckInputs( boolean* NewDataAvailable, const E2E_P04ConfigType* ConfigPtr, const E2E_P04CheckStateType* StatePtr, const uint8* DataPtr, uint16 Length ) {

    Std_ReturnType status;
    status = E2E_E_OK;
    *NewDataAvailable = FALSE;

    /* Check for NULL pointers */
    if ((ConfigPtr == NULL) || (StatePtr == NULL)) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_NULL;
    }

    /* Check input parameters values */
    if ((ConfigPtr->MinDataLength < MIN_P04_DATA_LENGTH_IN_BITS) || (ConfigPtr->MaxDataLength < MIN_P04_DATA_LENGTH_IN_BITS) ||
        (ConfigPtr->MinDataLength > MAX_P04_DATA_LENGTH_IN_BITS) || (ConfigPtr->MaxDataLength > MAX_P04_DATA_LENGTH_IN_BITS) ||
        (ConfigPtr->MinDataLength > ConfigPtr->MaxDataLength)) {
        status = E2E_E_INPUTERR_WRONG; /* MISRA exception */
    }

    else if ( !(((DataPtr != NULL) && (Length != 0)) || ((DataPtr == NULL) && (Length == 0))) ) {
        status = E2E_E_INPUTERR_WRONG; /* MISRA exception */
    }

    else if (DataPtr == NULL) {
        status = E2E_E_OK;
    }

    /* The offset shall be a multiple of 8 and 0 ≤ Offset ≤ MaxDataLength-(12*8). */
    else if ( ((ConfigPtr->Offset % 8) != 0) || (ConfigPtr->Offset > (MAX_P04_DATA_LENGTH_IN_BITS-MIN_P04_DATA_LENGTH_IN_BITS)) ||
         (ConfigPtr->Offset > ((Length*8)-MIN_P04_DATA_LENGTH_IN_BITS))) {
        status = E2E_E_INPUTERR_WRONG;
    }

    else if ( ((Length*8) < ConfigPtr->MinDataLength) || ((Length*8) > ConfigPtr->MaxDataLength) ) {
        status = E2E_E_INPUTERR_WRONG;
    } else {

        *NewDataAvailable = TRUE;
    }

    return status;
}


/* @req SWS_E2E_00357 */
static INLINE uint16 ReadLength( const uint8* DataPtr, uint16 offset ) {

    uint16 receivedLength = 0;

    receivedLength |= (((uint16)ChangeBitEndianness(DataPtr[offset  ]) << 8) & 0xFF00u);
    receivedLength |= (((uint16)ChangeBitEndianness(DataPtr[offset+1])     ) & 0x00FFu);

    return receivedLength;
}


/* @req SWS_E2E_00358 */
static INLINE uint16 ReadCounter( const uint8* DataPtr, uint16 offset ) {

    uint16 receivedCounter = 0;

    receivedCounter |= (((uint16)ChangeBitEndianness(DataPtr[offset+2]) << 8) & 0xFF00u);
    receivedCounter |= (((uint16)ChangeBitEndianness(DataPtr[offset+3])     ) & 0x00FFu);

    return receivedCounter;
}


/* @req SWS_E2E_00359 */
static INLINE uint32 ReadDataID( const uint8* DataPtr, uint16 offset ) {

    uint32 receivedDataID = 0;

    receivedDataID |= (((uint32)ChangeBitEndianness(DataPtr[offset+4]) << 24) & 0xFF000000u);
    receivedDataID |= (((uint32)ChangeBitEndianness(DataPtr[offset+5]) << 16) & 0x00FF0000u);
    receivedDataID |= (((uint32)ChangeBitEndianness(DataPtr[offset+6]) <<  8) & 0x0000FF00u);
    receivedDataID |= (((uint32)ChangeBitEndianness(DataPtr[offset+7])      ) & 0x000000FFu);

    return receivedDataID;
}


/* @req SWS_E2E_00360 */
static INLINE uint32 ReadCRC( const uint8* DataPtr, uint16 offset ) {

    uint32 receivedCRC = 0;

    receivedCRC |= (((uint32)ChangeBitEndianness(DataPtr[offset+ 8]) << 24) & 0xFF000000u);
    receivedCRC |= (((uint32)ChangeBitEndianness(DataPtr[offset+ 9]) << 16) & 0x00FF0000u);
    receivedCRC |= (((uint32)ChangeBitEndianness(DataPtr[offset+10]) <<  8) & 0x0000FF00u);
    receivedCRC |= (((uint32)ChangeBitEndianness(DataPtr[offset+11])      ) & 0x000000FFu);

    return receivedCRC;
}


/* @req SWS_E2E_00360 */
static INLINE uint16 CalculateDeltaCounter(uint16 receivedCounter, uint16 lastValidCounter)
{
    uint16 status;
    if (receivedCounter >= lastValidCounter) {
        status = receivedCounter - lastValidCounter;
    }
    else {
        status = (uint16)((uint32)MAX_P04_COUNTER_VALUE + 1 + (uint32)receivedCounter - (uint32)lastValidCounter);
    }
    return status;
}


/* @req SWS_E2E_00360 */
static INLINE void DoChecks( E2E_P04CheckStateType* StatePtr, const boolean* NewDataAvailable, const E2E_P04ConfigType* ConfigPtr, uint32 receivedCRC, uint32 computedCRC, uint32 receivedDataID, uint16 receivedLength, uint16 Length, uint16 receivedCounter ) {

    uint16 deltaCounter;

    if (*NewDataAvailable == FALSE) {
        StatePtr->Status = E2E_P04STATUS_NONEWDATA;
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return;
    }

    if ( (receivedCRC != computedCRC) || (receivedDataID != ConfigPtr->DataID) || (receivedLength != Length)) {
        StatePtr->Status = E2E_P04STATUS_ERROR;
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return;
    }

    deltaCounter = CalculateDeltaCounter(receivedCounter, StatePtr->Counter);

    if (deltaCounter > ConfigPtr->MaxDeltaCounter) {
        StatePtr->Status = E2E_P04STATUS_WRONGSEQUENCE;
    }
    else if (deltaCounter == 0) {
        StatePtr->Status = E2E_P04STATUS_REPEATED;
    }
    else if (deltaCounter == 1) {
        StatePtr->Status = E2E_P04STATUS_OK;
    }
    else {
        StatePtr->Status = E2E_P04STATUS_OKSOMELOST;
    }

    StatePtr->Counter = receivedCounter;
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00326 */
/* @req SWS_E2E_00329 */
/* @req SWS_E2E_00330 */
/* @req SWS_E2E_00339 */
/* @req SWS_E2E_00355 */
/* @req SWS_E2E_00356 */
/* @req SWS_E2E_00357 */
/* @req SWS_E2E_00358 */
/* @req SWS_E2E_00359 */
/* @req SWS_E2E_00360 */
/* @req SWS_E2E_00361 */
/* @req SWS_E2E_00367 */
/* @req SWS_E2E_00372 */
/* @req SWS_E2E_00376 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P04Check( E2E_P04ConfigType* ConfigPtr, E2E_P04CheckStateType* StatePtr, const uint8* DataPtr, uint16 Length ) {

    boolean NewDataAvailable;
    uint16 offset;
    uint16 receivedLength = 0;
    uint16 receivedCounter = 0;
    uint32 receivedDataID = 0;
    uint32 receivedCRC = 0;
    uint32 computedCRC = 0;

    Std_ReturnType returnValue = VerifyCheckInputs(&NewDataAvailable, ConfigPtr, StatePtr, DataPtr, Length);

    if (E2E_E_OK != returnValue) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return returnValue; /* MISRA exception */
    }

    if (NewDataAvailable == TRUE) {

        offset = ComputeOffset(ConfigPtr);

        receivedLength = ReadLength(DataPtr, offset);

        receivedCounter = ReadCounter(DataPtr, offset);

        receivedDataID = ReadDataID(DataPtr, offset);

        receivedCRC = ReadCRC(DataPtr, offset);

        computedCRC = ComputeCRC(DataPtr, offset, Length);
    }

    DoChecks(StatePtr, &NewDataAvailable, ConfigPtr, receivedCRC, computedCRC, receivedDataID, receivedLength, Length, receivedCounter);

    return E2E_E_OK;
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00373 */
/* @req SWS_E2E_00377 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P04ProtectInit( E2E_P04ProtectStateType* StatePtr ) {

    if (StatePtr == NULL) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_NULL; /* MISRA exception */
    }

    StatePtr->Counter = 0;

    return E2E_E_OK;
}


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00012 */
/* @req SWS_E2E_00350 */
/* @req SWS_E2E_00378 */
/* @req SWS_E2E_00471 */
/*lint -e{818} MISRA Exception: Must comply to specification MISRA 2004 Rule 16.7, advisory], [MISRA 2012 Rule 8.13, advisory */
Std_ReturnType E2E_P04CheckInit( E2E_P04CheckStateType* StatePtr ) {

    if (StatePtr == NULL) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_NULL; /* MISRA exception */
    }

    StatePtr->Status = E2E_P04STATUS_ERROR;
    StatePtr->Counter = 0xFFFF;

    return E2E_E_OK;
}


/* @req SWS_E2E_00349 */
/* @req SWS_E2E_00351 */
/* @req SWS_E2E_00352 */
E2E_PCheckStatusType E2E_P04MapStatusToSM( Std_ReturnType CheckReturn, E2E_P04CheckStatusType Status ) {

    E2E_PCheckStatusType retValue = E2E_P_ERROR;

    if (CheckReturn != E2E_E_OK) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return retValue;
    }

    switch( Status ) {
        case E2E_P04STATUS_OK:
        case E2E_P04STATUS_OKSOMELOST:
            retValue = E2E_P_OK;
            break;
        case E2E_P04STATUS_REPEATED:
            retValue = E2E_P_REPEATED;
            break;
        case E2E_P04STATUS_NONEWDATA:
            retValue = E2E_P_NONEWDATA;
            break;
        case E2E_P04STATUS_WRONGSEQUENCE:
            retValue = E2E_P_WRONGSEQUENCE;
            break;
        default:
            retValue = E2E_P_ERROR;
            break;
    }

    return retValue;
}
