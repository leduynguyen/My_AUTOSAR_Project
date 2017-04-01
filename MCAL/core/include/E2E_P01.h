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

#ifndef E2E_P01_H_
#define E2E_P01_H_

/* @req SWS_E2E_00115 */
/* @req SWS_E2E_00217 */
#include "E2E.h"
#include "E2E_SM.h"


/* @req SWS_E2E_00200 */
typedef enum {
    E2E_P01_DATAID_BOTH = 0x0,
    E2E_P01_DATAID_ALT = 0x1,
    E2E_P01_DATAID_LOW = 0x2,
    E2E_P01_DATAID_NIBBLE = 0x3 // new for ASR 4.2.2
} E2E_P01DataIDMode;


/* @req SWS_E2E_00018  */
/* @req SWS_E2E_00085  */
/* @req SWS_E2E_00227  Profile variant 1A, No explicit support for variants but the config allows such a configuration */
/* @req SWS_E2E_00228  Profile variant 1B, No explicit support for variants but the config allows such a configuration */
/* @req SWS_E2E_00307  Profile variant 1C, No explicit support for variants but the config allows such a configuration */
typedef struct  {
    uint16 CounterOffset;
    uint16 CRCOffset;
    uint16 DataID;
    uint16 DataIDNibbleOffset; // new for ASR 4.2.2
    E2E_P01DataIDMode DataIDMode;
    uint16 DataLength;
    uint8 MaxDeltaCounterInit;
    uint8 MaxNoNewOrRepeatedData; // new for ASR 4.2.2
    uint8 SyncCounterInit; // new for ASR 4.2.2
} E2E_P01ConfigType;


/* @req SWS_E2E_00020 */
typedef struct {
    uint8 Counter;
} E2E_P01ProtectStateType; //new name E2E_P01ProtectStateType according to ASR4.2.2


/* @req SWS_E2E_00022 */
typedef enum {
        E2E_P01STATUS_OK = 0x00,
        E2E_P01STATUS_NONEWDATA = 0x1,
        E2E_P01STATUS_WRONGCRC = 0x2,
        E2E_P01STATUS_SYNC = 0x03,
        E2E_P01STATUS_INITIAL = 0x4,
        E2E_P01STATUS_REPEATED = 0x8,
        E2E_P01STATUS_OKSOMELOST = 0x20,
        E2E_P01STATUS_WRONGSEQUENCE = 0x40
} E2E_P01CheckStatusType;


/* @req SWS_E2E_00021 */
typedef struct {
    uint8 LastValidCounter;
    uint8 MaxDeltaCounter;
    boolean WaitForFirstData;
    boolean NewDataAvailable;
    uint8 LostData;
    E2E_P01CheckStatusType Status;
    uint8 SyncCounter;
    uint8 NoNewOrRepeatedDataCounter;
} E2E_P01CheckStateType;  //new name E2E_P01CheckStateType according to ASR4.2.2


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00166 */
Std_ReturnType E2E_P01Protect( E2E_P01ConfigType* ConfigPtr, E2E_P01ProtectStateType* StatePtr, uint8* DataPtr );

/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00158 */
Std_ReturnType E2E_P01Check( E2E_P01ConfigType* ConfigPtr, E2E_P01CheckStateType* StatePtr, uint8* DataPtr );

/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00385 */
Std_ReturnType E2E_P01ProtectInit( E2E_P01ProtectStateType* StatePtr );

/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00390 */
Std_ReturnType E2E_P01CheckInit( E2E_P01CheckStateType* StatePtr );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00382 */
/*
 * The function maps the check status of Profile 1 to a generic check status, which can be used by E2E state machine check function.
 * The E2E Profile 1 delivers a more fine-granular status, but this is not relevant for the E2E state machine.
 */
E2E_PCheckStatusType E2E_P01MapStatusToSM( Std_ReturnType CheckReturn, E2E_P01CheckStatusType Status, boolean profileBehavior );


#endif
