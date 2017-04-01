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
 * The state of the calling task is set to waiting, unless at least one
 * of the events specified in <Mask> has already been set.
 *
 * This call enforces rescheduling, if the wait condition occurs. If
 * rescheduling takes place, the internal resource of the task is
 * released while the task is in the waiting state.
 * This service shall only be called from the extended task owning
 * the event.
 *
 * From 7.6.1 in Autosar OS 4.0
 * An event is accessible if the task for which the event can be set
 * is accessible. Access means that these Operating System objects are
 * allowed as parameters to API services.
 *
 * @param Mask Mask of the events waited for
 * @return
 */

StatusType WaitEvent( EventMaskType Mask ) {

    OsTaskVarType *curr_pcb = Os_SysTaskGetCurr();
    StatusType rv = E_OK;
    imask_t state;

    OS_DEBUG(D_EVENT,"# WaitEvent %s\n",Os_SysTaskGetCurr()->constPtr->name);

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */
    OS_VALIDATE( OS_SYS_PTR->intNestCnt == 0, E_OS_CALLEVEL);
    OS_VALIDATE( curr_pcb->constPtr->proc_type == PROC_EXTENDED,E_OS_ACCESS);
    OS_VALIDATE( !Os_TaskOccupiesResources(curr_pcb),E_OS_RESOURCE);
#if	(OS_NUM_CORES > 1)
    OS_VALIDATE( !Os_TaskOccupiesSpinlocks(curr_pcb) != 0,E_OS_SPINLOCK);       /* @req 4.1.2/SWS_Os_00622 */
#endif

    /* Remove from ready queue */
    Irq_Save(state);

    // OSEK/VDX footnote 5. The call of WaitEvent does not lead to a waiting state if one of the events passed in the event mask to
    // WaitEvent is already set. In this case WaitEvent does not lead to a rescheduling.
    if( (curr_pcb->ev_set & Mask) == 0 ) {

        curr_pcb->ev_wait = Mask;

        if ( Os_SchedulerResourceIsFree() ) {
            // Os_TaskMakeWaiting(currTaskPtr);
            Os_Dispatch(OP_WAIT_EVENT);
            ASSERT( curr_pcb->state & ST_RUNNING );
        } else {
            Os_TaskMakeWaiting(curr_pcb);
        }
    }

    Irq_Restore(state);

    OS_STD_END_1(OSServiceId_WaitEvent,Mask);
}

/**
 * The events of task <TaskID> are set according to the event
 * mask <Mask>. Calling SetEvent causes the task <TaskID> to
 * be transferred to the  ready state, if it was waiting for at least
 * one of the events specified in <Mask>.
 *
 * @param TaskID - Reference to the task for which one or several events are to be set.
 * @param Mask - Mask of the events to be set
 * @return
 */

StatusType SetEvent( TaskType TaskID, EventMaskType Mask ) {
    StatusType rv = E_OK;
    OsTaskVarType *destPcbPtr;
    OsTaskVarType *currPcbPtr;
    imask_t flags;

    OS_DEBUG(D_EVENT,"# SetEvent %s\n",Os_SysTaskGetCurr()->constPtr->name);

    TASK_CHECK_ID(TaskID);

    destPcbPtr = Os_TaskGet(TaskID);
    currPcbPtr = Os_SysTaskGetCurr();

#if (OS_SC3==STD_ON) || (OS_SC4==STD_ON)

    if( destPcbPtr->constPtr->applOwnerId != OS_SYS_PTR->currApplId ) {
        ApplicationType appId;
        APPL_CHECK_STATE(destPcbPtr->constPtr->applOwnerId);
        /* Do we have access to the task we are activating */
        if(OS_SYS_PTR->intNestCnt == 0 ) {
            appId = currPcbPtr->constPtr->applOwnerId;
        } else {
            appId = Os_SysIsrGetCurr()->constPtr->appOwner;
        }

        APPL_CHECK_ACCESS( appId , destPcbPtr->constPtr->accessingApplMask);

#if (OS_NUM_CORES > 1)
        if (Os_ApplGetCore(destPcbPtr->constPtr->applOwnerId) != GetCoreID()) {
                    StatusType status = Os_NotifyCore(Os_ApplGetCore(destPcbPtr->constPtr->applOwnerId),
                                                      OSServiceId_SetEvent,
                                                      TaskID,
                                                      Mask,
                                                      0);
                    return status;
#endif

    }
#endif

    OS_VALIDATE( destPcbPtr->constPtr->proc_type == PROC_EXTENDED, E_OS_ACCESS );
    OS_VALIDATE( (destPcbPtr->state & ST_SUSPENDED) == 0, E_OS_STATE);

    Irq_Save(flags);

    /* Calling  SetEvent  causes  the  task  <TaskID>  to be  transferred
     * to  the  ready  state,  if  it  was  waiting  for  at  least one of the
     * events specified in <Mask>.
     *
     * OSEK/VDX 4.6.1,  rescheduling is performed in all of the following cases:
     * ..
     * Setting an event to a waiting task at task level (e.g. system service SetEvent,
     * see chapter 13.5.3.1, message notification mechanism, alarm expiration, if event setting
     * defined, see chapter 9.2)
     * ... */

    destPcbPtr->ev_set |= Mask;

    if( (Mask & destPcbPtr->ev_wait) ) {
        /* We have an event match */
        if( destPcbPtr->state & ST_WAITING) {
#if defined(CFG_T1_ENABLE)
            Os_ReleaseEventHook(destPcbPtr->constPtr->pid);
#endif
            Os_TaskMakeReady(destPcbPtr);

            currPcbPtr = Os_SysTaskGetCurr();
            /* Checking "4.6.2  Non preemptive scheduling" it does not dispatch if NON  */
            //lint -e{9007} MISRA False positive. No side effects of Os_SchedulerResourceIsFree
            if( (OS_SYS_PTR->intNestCnt == 0) &&
                (currPcbPtr->constPtr->scheduling == FULL) &&
                (destPcbPtr->activePriority > currPcbPtr->activePriority) &&
                (Os_SysIntAnyDisabled() == FALSE ) &&
                (Os_SchedulerResourceIsFree()) )
            {
                Os_Dispatch(OP_SET_EVENT);
            }

        }  else if(destPcbPtr->state & (ST_READY | ST_RUNNING | ST_SLEEPING) ) {
            /* Hmm, we do nothing */
        } else {
            ASSERT( 0 );
        }
    }

    Irq_Restore(flags);

    OS_STD_END_2(OSServiceId_SetEvent,TaskID, Mask);
}


/**
 * This service returns the current state of all event bits of the task
 * <TaskID>, not the events that the task is waiting for.
 * The service may be called from interrupt service routines, task
 * level and some hook routines (see Figure 12-1).
 *  The current status of the event mask of task <TaskID> is copied
 * to <Event>.
 *
 * @param TaskId Task whose event mask is to be returned.
 * @param Mask   Reference to the memory of the return data.
 * @return
 */
StatusType GetEvent( TaskType TaskId, EventMaskRefType Mask) {

    OsTaskVarType *destPcbPtr;
    StatusType rv = E_OK;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */
    TASK_CHECK_ID(TaskId);

    destPcbPtr = Os_TaskGet(TaskId);

    OS_VALIDATE( (destPcbPtr->constPtr->proc_type == PROC_EXTENDED), E_OS_ACCESS);
    OS_VALIDATE( (destPcbPtr->state & ST_SUSPENDED) == 0, E_OS_STATE);

    *Mask = destPcbPtr->ev_set;

    OS_STD_END_2(OSServiceId_GetEvent,TaskId, Mask);
}


/**
 * The events of the extended task calling ClearEvent are cleared
 * according to the event mask <Mask>.
 *
 *
 * @param Mask
 * @return
 */
StatusType ClearEvent( EventMaskType Mask) {
    StatusType rv = E_OK;
    OsTaskVarType *pcb = Os_SysTaskGetCurr();
    imask_t flags;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */
    OS_VALIDATE( OS_SYS_PTR->intNestCnt == 0,E_OS_CALLEVEL);

    OS_VALIDATE(pcb->constPtr->proc_type == PROC_EXTENDED,E_OS_ACCESS);

    Irq_Save(flags);
    pcb->ev_set &= ~Mask;
    Irq_Restore(flags);

    OS_STD_END_1(OSServiceId_ClearEvent,Mask);
}





