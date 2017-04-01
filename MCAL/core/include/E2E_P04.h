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

#ifndef E2E_P04_H_
#define E2E_P04_H_

/* @req SWS_E2E_00115 */
/* @req SWS_E2E_00217 */
#include "E2E.h"
#include "E2E_SM.h"


/* @req SWS_E2E_00337 */
typedef enum {
    E2E_P04STATUS_OK = 0x00,
    E2E_P04STATUS_NONEWDATA = 0x01,
    E2E_P04STATUS_ERROR =  0x02,
    E2E_P04STATUS_REPEATED = 0x08,
    E2E_P04STATUS_OKSOMELOST = 0x20,
    E2E_P04STATUS_WRONGSEQUENCE = 0x40
} E2E_P04CheckStatusType;


/* @req SWS_E2E_00326 */
/* @req SWS_E2E_00334 */
/* @req SWS_E2E_00372 */
typedef struct {
    uint32 DataID;
    uint16 Offset;
    uint16 MinDataLength;
    uint16 MaxDataLength;
    uint8 MaxDeltaCounter;
} E2E_P04ConfigType;


/* @req SWS_E2E_00335 */
typedef struct {
    uint16 Counter;
} E2E_P04ProtectStateType;


/* @req SWS_E2E_00336 */
typedef struct {
    E2E_P04CheckStatusType Status;
    uint16 Counter;
} E2E_P04CheckStateType;


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00338 */
Std_ReturnType E2E_P04Protect( E2E_P04ConfigType* ConfigPtr, E2E_P04ProtectStateType* StatePtr, uint8* DataPtr, uint16 Length );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00339 */
/* Changed DataPtr type to const uint8* (ASR4.2.2 only uint8*), because the E2EXf specification requires a const uint8* buffer type*/
Std_ReturnType E2E_P04Check( E2E_P04ConfigType* ConfigPtr, E2E_P04CheckStateType* StatePtr, const uint8* DataPtr, uint16 Length );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00373 */
Std_ReturnType E2E_P04ProtectInit( E2E_P04ProtectStateType* StatePtr );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00350 */
Std_ReturnType E2E_P04CheckInit( E2E_P04CheckStateType* StatePtr );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00349 */
/*
 * The function maps the check status of Profile 4 to a generic check status, which can be used by E2E state machine check function.
 * The E2E Profile 4 delivers a more fine-granular status, but this is not relevant for the E2E state machine.
 */
E2E_PCheckStatusType E2E_P04MapStatusToSM( Std_ReturnType CheckReturn, E2E_P04CheckStatusType Status );


#endif
