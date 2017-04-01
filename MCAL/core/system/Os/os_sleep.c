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


#include "os_i.h"


/**
 * Will sleep for sleep ticks. This works only for extended
 * tasks. If sleep is 0 it will just call the dispatcher to
 * see if there is anything with higher or equal priority to run.
 *
 * @param sleep
 * @return E_OS_ACCESS if called from a basic task
 *         E_OS_RESOURCE called while holding a resource
 *         E_OS_CALLEVEL if called from interrupt context
 *         E_OK if called from a FULL task
 */

StatusType Sleep( TickType sleep ) {
    StatusType rv = E_OK;
    OsTaskVarType *pcbPtr;
    uint32_t flags;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */

    pcbPtr = Os_SysTaskGetCurr();

    if (pcbPtr->constPtr->proc_type != PROC_EXTENDED) {
        rv = E_OS_ACCESS;
        goto err;
    }

    /* Check that we are not calling from interrupt context */
    if( OS_SYS_PTR->intNestCnt != 0 ) {
        rv =  E_OS_CALLEVEL;
        goto err;
    }

    if ( Os_TaskOccupiesResources(pcbPtr) ) {
        rv =  E_OS_RESOURCE;
        goto err;
    }

    Irq_Save(flags);

    if ( Os_SchedulerResourceIsFree() ) {
        if( sleep != 0 ) {
            TAILQ_INSERT_TAIL(&OS_SYS_PTR->timerHead,pcbPtr,timerEntry);
            pcbPtr->timerDec = sleep;
            Os_Dispatch(OP_SLEEP);
        } else {

            /* Put us last in the ready list */
            TAILQ_REMOVE(&OS_SYS_PTR->ready_head,pcbPtr,ready_list);

            /* Add us again */
            TAILQ_INSERT_TAIL(& OS_SYS_PTR->ready_head,pcbPtr,ready_list);

            OsTaskVarType *topTask = Os_TaskGetTop();
            if( topTask != pcbPtr ) {
                Os_Dispatch(OP_SCHEDULE);
            }
        }
    }

    Irq_Restore(flags);

    OS_STD_END_1(OSServiceId_Sleep,sleep);
}
