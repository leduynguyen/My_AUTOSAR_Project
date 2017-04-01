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

#ifndef E2E_SM_H_
#define E2E_SM_H_

/* @req SWS_E2E_00115 */
#include "E2E.h"


/* @req SWS_E2E_00347 */
/* Profile-independent status of the reception on one single Data in one cycle. */
typedef enum {
    E2E_P_OK = 0x00,
    E2E_P_REPEATED = 0x01,
    E2E_P_WRONGSEQUENCE = 0x02,
    E2E_P_ERROR =  0x03,
    E2E_P_NOTAVAILABLE = 0x04,
    E2E_P_NONEWDATA = 0x05
} E2E_PCheckStatusType;


/* @req SWS_E2E_00344 */
/* Status of the communication channel exchanging the data. If the status is OK, then the data may be used. */
typedef enum {
    E2E_SM_VALID = 0x00,
    E2E_SM_DEINIT = 0x01,
    E2E_SM_NODATA = 0x02,
    E2E_SM_INIT =  0x03,
    E2E_SM_INVALID = 0x04
} E2E_SMStateType;


/* @req SWS_E2E_00342 */
/* Configuration of a communication channel for exchanging Data. */
typedef struct {
    uint8 WindowSize;
    uint8 MinOkStateInit;
    uint8 MaxErrorStateInit;
    uint8 MinOkStateValid;
    uint8 MaxErrorStateValid;
    uint8 MinOkStateInvalid;
    uint8 MaxErrorStateInvalid;
} E2E_SMConfigType;


/* @req SWS_E2E_00343 */
/* State of the protection of a communication channel. */
typedef struct {
    uint8* ProfileStatusWindow;
    uint8 WindowTopIndex;
    uint8 OkCount;
    uint8 ErrorCount;
    E2E_SMStateType SMState;
} E2E_SMCheckStateType;


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00340 */
/* Checks the communication channel.
 * It determines if the data can be used for safety-related application, based on history of checks performed by a corresponding E2E_P0XCheck() function.
 */
Std_ReturnType E2E_SMCheck( E2E_PCheckStatusType ProfileStatus, const E2E_SMConfigType* ConfigPtr, E2E_SMCheckStateType* StatePtr );


/* @req SWS_E2E_00047 */
/* @req SWS_E2E_00353 */
/* Initializes the state machine. */
Std_ReturnType E2E_SMCheckInit( E2E_SMCheckStateType* StatePtr, const E2E_SMConfigType* ConfigPtr );


#endif
