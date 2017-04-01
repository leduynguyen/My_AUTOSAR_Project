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

#ifndef E2E_P06_H_
#define E2E_P06_H_

/* @req SWS_E2E_00115 */
/* @req SWS_E2E_00217 */
#include "E2E.h"
#include "E2E_SM.h"


/* @req SWS_E2E_00445*/
typedef enum {
    E2E_P06STATUS_OK = 0x00,
    E2E_P06STATUS_NONEWDATA = 0x01,
    E2E_P06STATUS_ERROR =  0x02,
    E2E_P06STATUS_REPEATED = 0x08,
    E2E_P06STATUS_OKSOMELOST = 0x20,
    E2E_P06STATUS_WRONGSEQUENCE = 0x40
} E2E_P06CheckStatusType;


/* @req SWS_E2E_00441 */
/* @req SWS_E2E_00479 */
typedef struct {
    uint16 Offset;
    uint16 MinDataLength;
    uint16 MaxDataLength;
    uint16 DataID;
    uint8 MaxDeltaCounter;
} E2E_P06ConfigType;


/* @req SWS_E2E_00443 */
typedef struct {
    uint8 Counter;
} E2E_P06ProtectStateType;


/* @req SWS_E2E_00444 */
typedef struct {
    E2E_P06CheckStatusType Status;
    uint8 Counter;
} E2E_P06CheckStateType;


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00393 */
Std_ReturnType E2E_P06Protect( E2E_P06ConfigType* ConfigPtr, E2E_P06ProtectStateType* StatePtr, uint8* DataPtr, uint16 Length );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00457 */
Std_ReturnType E2E_P06Check( E2E_P06ConfigType* ConfigPtr, E2E_P06CheckStateType* StatePtr, uint8* DataPtr, uint16 Length );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00455 */
Std_ReturnType E2E_P06ProtectInit( E2E_P06ProtectStateType* StatePtr );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00458 */
Std_ReturnType E2E_P06CheckInit( E2E_P06CheckStateType* StatePtr );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00460 */
/*
 * The function maps the check status of Profile 6 to a generic check status, which can be used by E2E state machine check function.
 * The E2E Profile 6 delivers a more fine-granular status, but this is not relevant for the E2E state machine.
 */
E2E_PCheckStatusType E2E_P06MapStatusToSM( Std_ReturnType CheckReturn, E2E_P06CheckStatusType Status );


#endif
