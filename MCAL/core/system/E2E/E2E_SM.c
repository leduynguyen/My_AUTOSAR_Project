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
#include "E2E_SM.h"


/* @req SWS_E2E_00467 */
static INLINE void E2E_SMClearStatus( E2E_SMCheckStateType* StatePtr, uint8 windowSize ) {

    uint8 i;

    for (i=0; i<windowSize; i++) {
        StatePtr->ProfileStatusWindow[i] = (uint8)E2E_P_NOTAVAILABLE;
    }

    StatePtr->OkCount = 0;
    StatePtr->ErrorCount = 0;
    StatePtr->WindowTopIndex = 0;
}


/* @req SWS_E2E_00466 */
static INLINE void E2E_SMAddStatus( E2E_PCheckStatusType ProfileStatus, E2E_SMCheckStateType* StatePtr, uint8 windowSize ) {

    uint8 i;
    uint8 count;

    StatePtr->ProfileStatusWindow[StatePtr->WindowTopIndex] = (uint8)ProfileStatus;

    count=0;
    for (i=0; i<windowSize; i++) {
        if (StatePtr->ProfileStatusWindow[i] == (uint8)E2E_P_OK) {
            count++;
        }
    }

    StatePtr->OkCount = count;

    count=0;
    for (i=0; i<windowSize; i++) {
        if (StatePtr->ProfileStatusWindow[i] == (uint8)E2E_P_ERROR) {
            count++;
        }
    }

    StatePtr->ErrorCount = count;

    if (StatePtr->WindowTopIndex >= (windowSize-1)) {
        StatePtr->WindowTopIndex = 0;
    }
    else {
        StatePtr->WindowTopIndex++;
    }
}


static INLINE void E2E_SMCheck_NODATA( E2E_PCheckStatusType ProfileStatus, E2E_SMCheckStateType* StatePtr ) {

    if ((ProfileStatus != E2E_P_ERROR) && (ProfileStatus != E2E_P_NONEWDATA)) {
        StatePtr->SMState = E2E_SM_INIT;
    }
    else {
        StatePtr->SMState = E2E_SM_NODATA;
    }
}


static INLINE void E2E_SMCheck_INIT( const E2E_SMConfigType* ConfigPtr, E2E_SMCheckStateType* StatePtr ) {

    if ((StatePtr->ErrorCount <= ConfigPtr->MaxErrorStateInit) && (StatePtr->OkCount >= ConfigPtr->MinOkStateInit)) {
        StatePtr->SMState = E2E_SM_VALID;
    }
    else if (StatePtr->ErrorCount > ConfigPtr->MaxErrorStateInit) {
        StatePtr->SMState = E2E_SM_INVALID;
    }
    else {
        StatePtr->SMState = E2E_SM_INIT;
    }
}


static INLINE void E2E_SMCheck_VALID( const E2E_SMConfigType* ConfigPtr, E2E_SMCheckStateType* StatePtr ) {

    if ((StatePtr->ErrorCount <= ConfigPtr->MaxErrorStateValid) && (StatePtr->OkCount >= ConfigPtr->MinOkStateValid)) {
        StatePtr->SMState = E2E_SM_VALID;
    }
    else {
        StatePtr->SMState = E2E_SM_INVALID;
    }
}


static INLINE void E2E_SMCheck_INVALID( const E2E_SMConfigType* ConfigPtr, E2E_SMCheckStateType* StatePtr ) {

    if ((StatePtr->ErrorCount <= ConfigPtr->MaxErrorStateInvalid) && (StatePtr->OkCount >= ConfigPtr->MinOkStateInvalid)) {
        StatePtr->SMState = E2E_SM_VALID;
    }
    else {
        StatePtr->SMState = E2E_SM_INVALID;
    }
}


/* @req SWS_E2E_00340 */
/* @req SWS_E2E_00345 */
/* @req SWS_E2E_00354 */
/* @req SWS_E2E_00371 */
Std_ReturnType E2E_SMCheck( E2E_PCheckStatusType ProfileStatus, const E2E_SMConfigType* ConfigPtr, E2E_SMCheckStateType* StatePtr ) {

    if ((StatePtr == NULL) || (ConfigPtr == NULL)) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_NULL; /* MISRA exception */
    }

    /* Size of the monitoring window for the state machine can also be 0, check here consistency */
    if ((StatePtr->ProfileStatusWindow == NULL) && (ConfigPtr->WindowSize>0)) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_WRONG;
    }

    if (StatePtr->SMState == E2E_SM_DEINIT) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_WRONGSTATE;
    }

    switch (StatePtr->SMState) {

        case E2E_SM_NODATA:
            E2E_SMCheck_NODATA(ProfileStatus, StatePtr);

            break;

        case E2E_SM_INIT:
            E2E_SMAddStatus(ProfileStatus, StatePtr, ConfigPtr->WindowSize);
            E2E_SMCheck_INIT(ConfigPtr, StatePtr );

            break;

        case E2E_SM_VALID:
            E2E_SMAddStatus(ProfileStatus, StatePtr, ConfigPtr->WindowSize);
            E2E_SMCheck_VALID(ConfigPtr, StatePtr);

            break;

        case E2E_SM_INVALID:
            E2E_SMAddStatus(ProfileStatus, StatePtr, ConfigPtr->WindowSize);
            E2E_SMCheck_INVALID(ConfigPtr, StatePtr);

            break;
        default:
                StatePtr->SMState = E2E_SM_DEINIT;
            break;
    }


    return E2E_E_OK;
}


/* @req SWS_E2E_00353 */
/* @req SWS_E2E_00354 */
/* @req SWS_E2E_00370 */
/* @req SWS_E2E_00375 */
Std_ReturnType E2E_SMCheckInit( E2E_SMCheckStateType* StatePtr, const E2E_SMConfigType* ConfigPtr ) {

    if ((StatePtr == NULL) || (ConfigPtr == NULL)) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_NULL; /* MISRA exception */
    }

    /* Size of the monitoring window for the state machine can also be 0, check here consistency */
    if ((StatePtr->ProfileStatusWindow == NULL) && (ConfigPtr->WindowSize>0)) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return E2E_E_INPUTERR_WRONG;
    }

    E2E_SMClearStatus(StatePtr, ConfigPtr->WindowSize);

    StatePtr->SMState=E2E_SM_NODATA;

    return E2E_E_OK;
}
