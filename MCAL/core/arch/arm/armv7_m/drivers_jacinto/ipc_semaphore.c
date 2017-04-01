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

#include "ipc_semaphore.h"
#include "Os.h"
#include "timer.h"

OsSemaphoreType* Ipc_Semaphore_Create( int initialCount, int maxCount )
{
    OsSemaphoreType* ptr =(OsSemaphoreType*)malloc(sizeof(OsSemaphoreType));
    ptr->count = 1;

    return ptr;
}

void Ipc_Semaphore_Destroy( OsSemaphoreType *semPtr ) {
    free(semPtr);
}

#if 0
void Ipc_Semaphore_Wait(OsSemaphoreType* semaphore)
{
    while (semaphore->count == 0) {};
}
#endif

 int Ipc_Semaphore_Busy(OsSemaphoreType* semaphore)
{
     int rv;
     imask_t flags;
     Irq_Save(flags);

     if ( semaphore->count == 0) {
         rv = 1;    /* Semaphore busy */
     } else {
         rv = 0;
     }
     Irq_Restore(flags);
     return rv;
}


/* Returns E_OK if the semaphore is free, E_NOT_OK if it timed out */
int Ipc_Semaphore_Wait(OsSemaphoreType* semaphore, uint32_t timeout)
{
    uint32_t startTicks = Timer_GetTicks();
    /* timeout is in ms, timer operates in us */
    uint32_t waitTicks = TIMER_US2TICK(timeout * 1000);

    if( timeout == 0xfffffffful ) {
        /* Wait forever */
        while (semaphore->count == 0) {
            Sleep(1);
        };
    } else {
        while (semaphore->count == 0)
        {
            Sleep(1);
            if ((Timer_GetTicks() - startTicks) >= waitTicks) {
                return 0;   /* tmeout */
            }
        }
    }

    /* We got the semaphore */
    semaphore->count--;

    return 1;   /* ok */
}

void Ipc_Semaphore_Signal(OsSemaphoreType* semaphore)
{
    semaphore->count++;
}


