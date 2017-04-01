/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/* lwIP includes. */
#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/sys.h"

#include "os.h"
#include "Std_Types.h"
#include "arch/sys_arch.h"
#include "Mcu.h"

static void (* tcpip_thread)(void *arg) = NULL;

#if !NO_SYS

#include "lwip/tcpip.h"


/* This is the number of threads that can be started with sys_thread_new()
 * Cannot be modified at the moment. No need to support slip/ppp */
#define SYS_THREAD_MAX 1

static u16_t nextthread = 0;

#define SYS_SEM_MAX 25
struct semlist_t
{
    sys_sem_t val;
    boolean used;
    u32_t event;
    TaskType task[SYS_SEM_MAX];
    u8_t taskIndex;
};
static struct semlist_t semlist[SYS_SEM_MAX];

/*
  This optional function does a "fast" critical region protection and returns
  the previous protection level. This function is only called during very short
  critical regions. An embedded system which supports ISR-based drivers might
  want to implement this function by disabling interrupts. Task-based systems
  might want to implement this by using a mutex or disabling tasking. This
  function should support recursive calls from the same task or interrupt. In
  other words, sys_arch_protect() could be called while already protected. In
  that case the return value indicates that it is already protected.

  sys_arch_protect() is only required if your port is supporting an operating
  system.
*/
sys_prot_t sys_arch_protect(void)
{
    uint32_t val;
    Irq_Save(val);
    return val;
}

/*
  This optional function does a "fast" set of critical region protection to the
  value specified by pval. See the documentation for sys_arch_protect() for
  more information. This function is only required if your port is supporting
  an operating system.
*/
void sys_arch_unprotect(sys_prot_t pval)
{
    Irq_Restore(pval);
}


/*-----------------------------------------------------------------------------------*/
//  Creates an empty mailbox.
err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
    err_t res = ERR_OK;
    if(size==0){
        size=20;
    }
    *mbox = Arc_MBoxCreate(size);

    if(mbox == NULL){
        res = ERR_MEM;
    }
    return res;
}

/*-----------------------------------------------------------------------------------*/
/*
  Deallocates a mailbox. If there are messages still present in the
  mailbox when the mailbox is deallocated, it is an indication of a
  programming error in lwIP and the developer should be notified.
*/
void sys_mbox_free(sys_mbox_t *mbox)
{
    Arc_MBoxDestroy(*mbox);
}

/*-----------------------------------------------------------------------------------*/
/* void sys_mbox_post(sys_mbox_t mbox, void *msg)

  Posts the "msg" to the mailbox. This function have to block until
  the "msg" is really posted.
  */
void sys_mbox_post(sys_mbox_t *mbox, void *msg)
{   
    while(Arc_MBoxPost( *mbox, (ApplicationDataRef) &msg ) != E_OK)
    {
        Sleep(1);
    }
}


/* err_t sys_mbox_trypost(sys_mbox_t mbox, void *msg)

  Try to post the "msg" to the mailbox. Returns ERR_MEM if this one
  is full, else, ERR_OK if the "msg" is posted.
  */
err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
{
    if(Arc_MBoxPost( *mbox, (ApplicationDataRef) &msg ) != E_OK)
    {
        return ERR_MEM;
    }
    else
    {
        return ERR_OK;
    }
}

/* This is similar to sys_arch_mbox_fetch, however if a message is not
  present in the mailbox, it immediately returns with the code
  SYS_MBOX_EMPTY. On success 0 is returned.

  To allow for efficient implementations, this can be defined as a
  function-like macro in sys_arch.h instead of a normal function. For
  example, a naive implementation could be:
    #define sys_arch_mbox_tryfetch(mbox,msg) \
      sys_arch_mbox_fetch(mbox,msg,1)
  although this would introduce unnecessary delays. */
u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
    void *dummyptr;

    if( msg == NULL )
    {
        msg = &dummyptr;
    }

    if( Arc_MBoxFetch( *mbox, msg) != E_OK )
    {
        return SYS_MBOX_EMPTY;
    }

    return 0;
}

/*-----------------------------------------------------------------------------------*/
/*
  Blocks the thread until a message arrives in the mailbox, but does
  not block the thread longer than "timeout" milliseconds (similar to
  the sys_arch_sem_wait() function). The "msg" argument is a result
  parameter that is set by the function (i.e., by doing "*msg =
  ptr"). The "msg" parameter maybe NULL to indicate that the message
  should be dropped.

  The return values are the same as for the sys_arch_sem_wait() function:
  Number of milliseconds spent waiting or SYS_ARCH_TIMEOUT if there was a
  timeout.

  Note that a function with a similar name, sys_mbox_fetch(), is
  implemented by lwIP. 
*/
u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout)
{
    void *dummyptr;
    TickType StartTime, EndTime, Elapsed;

    StartTime = GetOsTick();

    if( msg == NULL )
    {
        msg = &dummyptr;
    }
        
    if(	timeout != 0 )
    {
        while( Arc_MBoxFetch( *mbox, msg) != E_OK )
        {
            Sleep(1);
            EndTime = GetOsTick();
            Elapsed = EndTime - StartTime;
            if(Elapsed > timeout)
            {
                *msg = NULL;
                return SYS_ARCH_TIMEOUT;
            }
        }
        EndTime = GetOsTick();
        Elapsed = EndTime - StartTime;
        if( Elapsed == 0 )
        {
            Elapsed = 1;
        }
        return (Elapsed); // return time blocked TBD test
    }
    else // block forever for a message.
    {
        while( E_OK != Arc_MBoxFetch( *mbox, msg) )
        {
            Sleep(1);
            /*TaskType TaskID;
            GetTaskID(&TaskID);
            SetEvent(TaskID, EVENT_MASK_dispatch);
            WaitEvent(EVENT_MASK_dispatch);
            ClearEvent(EVENT_MASK_dispatch);*/
        }
        EndTime = GetOsTick();
        Elapsed = EndTime - StartTime;
        if( Elapsed == 0 )
        {
            Elapsed = 1;
        }
        return ( Elapsed ); // return time blocked TBD test	
    }
}

uint8 GetSem(sys_sem_t sem)
{
    uint8 res = E_OK;
    sys_prot_t val = sys_arch_protect();

    if(semlist[sem].val > 0){
        res = E_NOT_OK;
    }else{
        semlist[sem].val = 1;
    }

    sys_arch_unprotect(val);
    return res;
}

/*-----------------------------------------------------------------------------------*/
//  Creates and returns a new semaphore. The "count" argument specifies
//  the initial state of the semaphore. TBD finish and test
err_t sys_sem_new(sys_sem_t *sem, u8_t count)
{
    uint8 i;

    sys_prot_t val = sys_arch_protect();

    // use semaphore pool
    for(i = 0; i < SYS_SEM_MAX; i++)
    {
        if(semlist[i].used == FALSE)
        {
            semlist[i].used = TRUE;
            if(count==0)
            {
                if(GetSem( i) != E_OK)
                {
                    sys_arch_unprotect(val);
                    ErrorHook(E_OS_LIMIT);
                    return ERR_MEM;
                }
            }
            sys_arch_unprotect(val);
            *sem = i;
            return ERR_OK;
        }
    }
    ErrorHook(E_OS_LIMIT);
    sys_arch_unprotect(val);
    return ERR_MEM;
}

/*-----------------------------------------------------------------------------------*/
/*
  Blocks the thread while waiting for the semaphore to be
  signaled. If the "timeout" argument is non-zero, the thread should
  only be blocked for the specified time (measured in
  milliseconds).

  If the timeout argument is non-zero, the return value is the number of
  milliseconds spent waiting for the semaphore to be signaled. If the
  semaphore wasn't signaled within the specified time, the return value is
  SYS_ARCH_TIMEOUT. If the thread didn't have to wait for the semaphore
  (i.e., it was already signaled), the function may return zero.

  Notice that lwIP implements a function with a similar name,
  sys_sem_wait(), that uses the sys_arch_sem_wait() function.
*/
u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
    TickType StartTime, EndTime, Elapsed;

    StartTime = GetOsTick();

    if(	timeout != 0)
    {
        while( GetSem( *sem) != E_OK )
        {
            Sleep(1);
            EndTime = GetOsTick();
            Elapsed = EndTime - StartTime;
            if(Elapsed > timeout)
            {
                return SYS_ARCH_TIMEOUT;
            }
        }
        EndTime = GetOsTick();
        Elapsed = EndTime - StartTime;
        if( Elapsed == 0 )
        {
            Elapsed = 1;
        }
        return (Elapsed); // return time blocked TBD test
    }
    else // must block without a timeout
    {
        while( GetSem( *sem) != E_OK )
        {
#if 0
        	TaskType TaskID;
            sys_prot_t val = sys_arch_protect();
            GetTaskID(&TaskID);
            semlist[*sem].task[semlist[*sem].taskIndex++] = TaskID;
            sys_arch_unprotect(val);
            WaitEvent(semlist[*sem].event);
            ClearEvent(semlist[*sem].event);
#endif
            Sleep(1);
        }
        EndTime = GetOsTick();
        Elapsed = EndTime - StartTime;
        if( Elapsed == 0 )
        {
            Elapsed = 1;
        }

        return ( Elapsed ); // return time blocked	
         
    }
}

/*-----------------------------------------------------------------------------------*/
// Signals a semaphore
void
sys_sem_signal(sys_sem_t *sem)
{
    sys_prot_t val = sys_arch_protect();

    if(semlist[*sem].val > 0){
        semlist[*sem].val = 0;

        for(int i=0;i<semlist[*sem].taskIndex;i++){
            SetEvent(semlist[*sem].task[i] , semlist[*sem].event);
        }
        semlist[*sem].taskIndex = 0;
    }

    sys_arch_unprotect(val);
}

/*-----------------------------------------------------------------------------------*/
// Deallocates a semaphore
void
sys_sem_free(sys_sem_t *sem)
{
    sys_prot_t val = sys_arch_protect();

    if(semlist[*sem].used == TRUE)
    {
        sys_sem_signal(sem); // Just to be sure its released
        semlist[*sem].used = FALSE;
        semlist[*sem].taskIndex = 0;
        sys_arch_unprotect(val);
        return;
    }
    ErrorHook(E_OS_VALUE);
    sys_arch_unprotect(val);
    return;

}

/*-----------------------------------------------------------------------------------*/
// Initialize sys arch
void
sys_init(void)
{
}

// Preinitialize sys arch
void
pre_sys_init(void)
{
    uint8 i;

    //initialize semaphore pool
    for(i = 0; i < SYS_SEM_MAX; i++)
    {
        semlist[i].used = FALSE;
        semlist[i].val = 0;
        semlist[i].taskIndex = 0;
    }

    i=0;
    semlist[i++].event = EVENT_MASK_OsEvent1;
    semlist[i++].event = EVENT_MASK_OsEvent2;
    semlist[i++].event = EVENT_MASK_OsEvent3;
    semlist[i++].event = EVENT_MASK_OsEvent4;
    semlist[i++].event = EVENT_MASK_OsEvent5;
    semlist[i++].event = EVENT_MASK_OsEvent6;
    semlist[i++].event = EVENT_MASK_OsEvent7;
    semlist[i++].event = EVENT_MASK_OsEvent8;
    semlist[i++].event = EVENT_MASK_OsEvent9;
    semlist[i++].event = EVENT_MASK_OsEvent10;
    semlist[i++].event = EVENT_MASK_OsEvent11;
    semlist[i++].event = EVENT_MASK_OsEvent12;
    semlist[i++].event = EVENT_MASK_OsEvent13;
    semlist[i++].event = EVENT_MASK_OsEvent14;
    semlist[i++].event = EVENT_MASK_OsEvent15;
    semlist[i++].event = EVENT_MASK_OsEvent16;
    semlist[i++].event = EVENT_MASK_OsEvent17;
    semlist[i++].event = EVENT_MASK_OsEvent18;
    semlist[i++].event = EVENT_MASK_OsEvent19;
    semlist[i++].event = EVENT_MASK_OsEvent20;
    semlist[i++].event = EVENT_MASK_OsEvent21;
    semlist[i++].event = EVENT_MASK_OsEvent22;
    semlist[i++].event = EVENT_MASK_OsEvent23;
    semlist[i++].event = EVENT_MASK_OsEvent24;
    semlist[i++].event = EVENT_MASK_OsEvent25;


    // keep track of how many threads have been created
    nextthread = 0;
}

// TBD memory leak with invalid mbox?
int sys_mbox_valid(sys_mbox_t *mbox)
{
    return (*mbox == NULL) ? 0 : 1;
}

void sys_mbox_set_invalid(sys_mbox_t *mbox)
{
    *mbox = NULL;
}


int sys_sem_valid(sys_sem_t *sem)
{
    return (semlist[*sem].used == FALSE) ? 0 : 1;
}


void sys_sem_set_invalid(sys_sem_t *sem)
{
    semlist[*sem].used = FALSE;
}


/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
// TBD 
/*-----------------------------------------------------------------------------------*/
/*
  Starts a new thread with priority "prio" that will begin its execution in the
  function "thread()". The "arg" argument will be passed as an argument to the
  thread() function. The id of the new thread is returned. Both the id and
  the priority are system dependent.
*/
sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio)
{
    sys_thread_t CreatedTask = TASK_ID_tcpip_task;
    static uint8 iCall = 0;

    if( iCall == 0 )
    {
        tcpip_thread = thread;
    }
    else
    {
        // We only support creating tcpip thread at the moment
        ErrorHook(E_OS_LIMIT);
        return 0;
    }

    SetEvent(TASK_ID_tcpip_task,EVENT_MASK_START_TCPIP); // Start tcpip stack
    return CreatedTask;
}

#endif /* !NO_SYS */

// TCPIP task shell
void tcpip_task( void ) {
    for(;;) {
        WaitEvent(EVENT_MASK_START_TCPIP);
        ClearEvent(EVENT_MASK_START_TCPIP);
        if(tcpip_thread != NULL)
        {
            tcpip_thread(NULL); // Will never return
        }
    }
}
