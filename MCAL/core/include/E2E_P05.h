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

#ifndef E2E_P05_H_
#define E2E_P05_H_

/* @req SWS_E2E_00115 */
/* @req SWS_E2E_00217 */
#include "E2E.h"
#include "E2E_SM.h"


/* @req SWS_E2E_00440 */
typedef enum {
    E2E_P05STATUS_OK = 0x00,
    E2E_P05STATUS_NONEWDATA = 0x01,
    E2E_P05STATUS_ERROR =  0x07,
    E2E_P05STATUS_REPEATED = 0x08,
    E2E_P05STATUS_OKSOMELOST = 0x20,
    E2E_P05STATUS_WRONGSEQUENCE = 0x40
} E2E_P05CheckStatusType;


/* @req SWS_E2E_00394 */
/* @req SWS_E2E_00399 */
/* @req SWS_E2E_00437 */
typedef struct {
    uint16 Offset;
    uint16 DataLength;
    uint16 DataID;
    uint8 MaxDeltaCounter;
} E2E_P05ConfigType;


/* @req SWS_E2E_00438 */
typedef struct {
    uint8 Counter;
} E2E_P05ProtectStateType;


/* @req SWS_E2E_00439 */
typedef struct {
    E2E_P05CheckStatusType Status;
    uint8 Counter;
} E2E_P05CheckStateType;


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00446 */
Std_ReturnType E2E_P05Protect( E2E_P05ConfigType* ConfigPtr, E2E_P05ProtectStateType* StatePtr, uint8* DataPtr, uint16 Length );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00449 */
Std_ReturnType E2E_P05Check( E2E_P05ConfigType* ConfigPtr, E2E_P05CheckStateType* StatePtr, uint8* DataPtr, uint16 Length );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00447 */
Std_ReturnType E2E_P05ProtectInit( E2E_P05ProtectStateType* StatePtr );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00450 */
Std_ReturnType E2E_P05CheckInit( E2E_P05CheckStateType* StatePtr );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00452 */
/*
 * The function maps the check status of Profile 5 to a generic check status, which can be used by E2E state machine check function.
 * The E2E Profile 5 delivers a more fine-granular status, but this is not relevant for the E2E state machine.
 */
E2E_PCheckStatusType E2E_P05MapStatusToSM( Std_ReturnType CheckReturn, E2E_P05CheckStatusType Status );


#endif
