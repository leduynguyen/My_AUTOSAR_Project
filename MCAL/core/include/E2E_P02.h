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

#ifndef E2E_P02_H_
#define E2E_P02_H_

/* @req SWS_E2E_00115 */
/* @req SWS_E2E_00217 */
#include "E2E.h"
#include "E2E_SM.h"


/* @req SWS_E2E_00214*/
typedef enum {
    E2E_P02STATUS_OK = 0x00,
    E2E_P02STATUS_NONEWDATA = 0x01,
    E2E_P02STATUS_WRONGCRC =  0x02,
    E2E_P02STATUS_SYNC = 0x03,
    E2E_P02STATUS_INITIAL = 0x04,
    E2E_P02STATUS_REPEATED = 0x08,
    E2E_P02STATUS_OKSOMELOST = 0x20,
    E2E_P02STATUS_WRONGSEQUENCE = 0x40
} E2E_P02CheckStatusType;


/* @req SWS_E2E_00152 */
typedef struct {
    uint16 DataLength;
    uint8 DataIDList[16];
    uint8 MaxDeltaCounterInit;
    uint8 MaxNoNewOrRepeatedData; // new for ASR 4.2.2
    uint8 SyncCounterInit; // new for ASR 4.2.2
    uint16 Offset; // new for ASR 4.2.2
} E2E_P02ConfigType;


/* @req SWS_E2E_00153 */
typedef struct {
    uint8 Counter;
} E2E_P02ProtectStateType; //new name E2E_P02ProtectStateType according to ASR4.2.2


/* @req SWS_E2E_00154 */
typedef struct {
    uint8 LastValidCounter;
    uint8 MaxDeltaCounter;
    boolean WaitForFirstData;
    boolean NewDataAvailable;
    uint8 LostData;
    E2E_P02CheckStatusType Status;
    uint8 SyncCounter;
    uint8 NoNewOrRepeatedDataCounter;
} E2E_P02CheckStateType;  //new name E2E_P02CheckStateType according to ASR4.2.2


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00160 */
Std_ReturnType E2E_P02Protect( E2E_P02ConfigType* ConfigPtr, E2E_P02ProtectStateType* StatePtr, uint8* DataPtr );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00161 */
Std_ReturnType E2E_P02Check( E2E_P02ConfigType* ConfigPtr, E2E_P02CheckStateType* StatePtr, uint8* DataPtr );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00387 */
Std_ReturnType E2E_P02ProtectInit( E2E_P02ProtectStateType* StatePtr );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00391 */
Std_ReturnType E2E_P02CheckInit( E2E_P02CheckStateType* StatePtr );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00379 */
/*
 * The function maps the check status of Profile 2 to a generic check status, which can be used by E2E state machine check function.
 * The E2E Profile 2 delivers a more fine-granular status, but this is not relevant for the E2E state machine.
 */
E2E_PCheckStatusType E2E_P02MapStatusToSM( Std_ReturnType CheckReturn, E2E_P02CheckStatusType Status, boolean profileBehavior );


#endif
