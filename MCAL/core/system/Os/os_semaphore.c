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

/*
 * Mutex usage:
 * - Serialized access to a global resource. The same task
 *   ALWAYS first use Os_WaitMutex() and the Os_ReleaseMutex()
 *   Should mutex be as GetResource()/ReleaseResource() be able to
 *   tinker with priotities? Yeees, raise the priority to the
 *   priority of the calling task ( Second call to WaitMutex() )
 *
 *
 *   Task1:
 *     Os_WaitMutex(my_mutex)
 *     ..
 *     Os_ReleaseMutex(my_mutex)

 *   Task2
 *     Os_WaitMutex(my_mutex)
 *     ..
 *     Os_ReleaseMutex(my_mutex)
 *
 * Semaphore usage:
 * - Producer and consumer problems.
 *   Os_WaitSemaphore() and Os_SignalSemaphore().
 *
 *   ISR:
 *     Os_SignalSemaphore(my_semaphore)

 *   Task:
 *     Os_WaitSemaphore(my_semaphore)
 *
 *
 * Mutex vs Resource's
 *   A task, say TASK_A calls GetResource(RES_1) any task that has anything to do
 *   with the RES_1 will not be able to run (since the priority of TASK_A will be
 *   raised to the priority of the task with the highest priority accessing the
 *   resource). This does not encourage the use of resources that is scarcely used
 *   within a high priority task (since it will not get runtime when the resource is
 *   held).
 *
 *   Mutex:es on the other hand will make other tasks run that shares the resource
 *   but the priority of the task that take the mutex for the second time makes the
 *   first task inherit the priority of that task.
 *
 *   Resources is deadlock safe while mutex:es are not (circular lock dependencies)
 */

/* ----------------------------[includes]------------------------------------*/
#include "os_i.h"

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/


void FindAndRemoveTaskFromTimerReadyList(OsTaskVarType *pcbPtrToMatch)
{
    OsTaskVarType *pcbPtr;
    /* Check tasks in the timer queue (here from Sleep() or WaitSemaphore() ) */
    TAILQ_FOREACH(pcbPtr, &OS_SYS_PTR->timerHead, timerEntry ) {
        if(pcbPtr==pcbPtrToMatch){
            pcbPtr->timerDec = 0;
            /* Remove from the timer queue */
            TAILQ_REMOVE(&OS_SYS_PTR->timerHead, pcbPtr, timerEntry);
        }
    }
}

/* traverse and remove, return true if removed any */
boolean FindAndRemoveTaskFromSemReadyList(OsSemaphoreType *semPtr,
        OsTaskVarType *pcbPtr) {
    boolean found = FALSE;
    if ((&semPtr->taskHead)->stqh_first != NULL) {
        if (STAILQ_FIRST((&semPtr->taskHead)) == (pcbPtr)) {
            STAILQ_REMOVE_HEAD((&semPtr->taskHead), semEntry);
            found = TRUE;
        }
        else {
            struct OsTaskVar *curelm = STAILQ_FIRST((&semPtr->taskHead));
            while (STAILQ_NEXT(curelm, semEntry) != (pcbPtr) && (curelm != NULL)) {
                curelm = STAILQ_NEXT(curelm, semEntry);
            }
            if (curelm != NULL) {
                found = TRUE;
                if ((STAILQ_NEXT(curelm, semEntry) = STAILQ_NEXT(
                        STAILQ_NEXT(curelm, semEntry), semEntry)) == NULL) {
                    (&semPtr->taskHead)->stqh_last = &STAILQ_NEXT((curelm),
                            semEntry);
                }
            }
        }
    }
    return found;
}

/**
 * Wait for a semaphore.
 *
 * The count of the semaphore is decremented. If the count is 0 or lower the
 * caller is put in WAITING state.
 *
 * If the scheduler is locked (hold RES_SCHEDULER) the call will fail and
 * return E_NOT_OK.
 *
 * @param semPtr
 * @param tmo   0 - no waiting
 *              0xFFFF_FFFF - Wait forever
 * @return   E_OK (0)     - OK
 *           E_NOT_OK (1) - Something faied.
 *           E_OS_TIMEOUT - Timeout
 *
 */

StatusType Semaphore_Wait(OsSemaphoreType *semPtr, TickType tmo) {
    OsTaskVarType *pcbPtr;
    uint32_t flags;
    StatusType rv = E_OK;
    (void) tmo;

    Irq_Save(flags);

    pcbPtr = Os_SysTaskGetCurr();
    ASSERT(OS_SYS_PTR->intNestCnt == 0);

    if (pcbPtr->constPtr->proc_type != PROC_EXTENDED) {
        rv = E_OS_ACCESS;
        ERRORHOOK(rv);
    }
    else if (Os_TaskOccupiesResources(pcbPtr)) {
        rv = E_OS_RESOURCE;
        ERRORHOOK(rv);
    }
    else {

        if (semPtr->count <= 0) {
            /* To WAITING state */
            if (tmo == 0) {
                /* Failed to acquire the semaphore */
                rv = E_NOT_OK;
            }
            else {
                /*
                 * Wait for the semaphore to be signaled or timeout
                 */
                if (Os_SchedulerResourceIsFree()) {
                    --semPtr->count;
                    /* Add this task to the semaphore */
                    STAILQ_INSERT_TAIL(&semPtr->taskHead, pcbPtr, semEntry);

                    /* Set the timeout */
                    if (tmo != TICK_MAX) {
                        TAILQ_INSERT_TAIL(&OS_SYS_PTR->timerHead, pcbPtr,
                                timerEntry);
                        pcbPtr->timerDec = tmo;
                    }
                    Os_Dispatch(OP_WAIT_SEMAPHORE);

                    if (tmo != TICK_MAX) {
                        /* First we remove any timer if we got the semaphore in time */
                        FindAndRemoveTaskFromTimerReadyList(pcbPtr);

                        if (FindAndRemoveTaskFromSemReadyList(semPtr,
                                pcbPtr) == TRUE) {
                            /* timeout, we didn't get the semaphore, we need to remove ourselves from the queue */
                            ++semPtr->count;
                            rv = E_OS_TIMEOUT;
                        }
                    }
                }
                else {
                    /* We hold RES_SCHEDULER */
                    rv = E_NOT_OK;
                }

            }
        }
        else {
            /* We got the semaphore */
            --semPtr->count;
        }
    }

    Irq_Restore(flags);

    return rv;
}

/**
 * Increase the semaphore count by 1. If
 *
 * @param semPtr
 */
void Semaphore_Signal(OsSemaphoreType *semPtr) {
    uint32_t flags;
    OsTaskVarType *taskPtr;

    Irq_Save(flags);

    if (semPtr != NULL) {
        if (semPtr->count < semPtr->maxCount) {
            ++semPtr->count;

            /* Remove the first task that waits at the semaphore */
            taskPtr = STAILQ_FIRST(&semPtr->taskHead);
            /* Make the first task ready */
            if (taskPtr != NULL) {
                /* Release the first task in queue */
                STAILQ_REMOVE_HEAD(&semPtr->taskHead, semEntry);
                Os_TaskMakeReady(taskPtr);

                if( (OS_SYS_PTR->intNestCnt == 0) &&
                    (taskPtr->activePriority > Os_SysTaskGetCurr()->activePriority)) {
                    Os_Dispatch(OP_SIGNAL_SEMAPHORE);
                }
            }
        }
        else {
            ERRORHOOK(E_OS_VALUE);
        }
    }
    else {
        ERRORHOOK(E_OS_VALUE);
    }

    Irq_Restore(flags);
}

/*
 * Usage:
 */
StatusType Semaphore_Init(OsSemaphoreType *semPtr, int initialCount, int maxCount) {

    semPtr->count = 0;
    semPtr->maxCount = maxCount;
    STAILQ_INIT(&semPtr->taskHead);
    return E_OK;
}

OsSemaphoreType *Semaphore_Create( int initialCount, int maxCount) {

    OsSemaphoreType *semPtr = (OsSemaphoreType *)malloc(sizeof(OsSemaphoreType));

    Semaphore_Init(semPtr,initialCount,1000);
    return semPtr;
}

void Semaphore_Destroy( OsSemaphoreType *semPtr ) {
    free(semPtr);
}

#if 0

/* With priority inheretance */
StatusType CreateMutex( OsMutexType *mutexPtr ) {

}
#endif

/**
 *
 * @param mutexPtr
 * @return
 */

StatusType WaitMutex(OsMutexType *mutexPtr, TickType tmo) {

    (void) mutexPtr;
    return E_OK;
}

StatusType ReleaseMutex(OsMutexType *mutexPtr) {

    (void) mutexPtr;
    return E_OK;
}

