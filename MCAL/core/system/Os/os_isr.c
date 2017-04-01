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

#include "irq.h"
#include "irq_types.h"
#include "os_i.h"

#if defined(CFG_TC2XX)
#include "IfxCpu.h"
#endif

#define VECTOR_ILL		0xff

#define ACK_INTERRUPT(_x) Irq_EOI(_x);


extern uint8_t Os_VectorToIsr[NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS];
/* IMPROVEMENT: Have each Os_Sys struct keep the needed interrupts instead of a
         global Os_IsrVarList. Get rid of the isrCnt variable below. */
ISRType isrCnt = 0;

#if OS_ISR_CNT!=0
extern const OsIsrConstType Os_IsrConstList[OS_ISR_CNT];
#endif

#if OS_ISR_MAX_CNT!=0
OsIsrVarType Os_IsrVarList[OS_ISR_MAX_CNT];
#endif

uint8_t Os_IsrStack[OS_NUM_CORES][OS_INTERRUPT_STACK_SIZE] __balign(0x10);

// IMPROVEMENT: remove. Make soft links or whatever
#if defined(CFG_ARM_CM3)
#include "irq_types.h"
#endif


#if defined(CFG_OS_ISR_HOOKS)
/**
 * Call external hook function.
 *
 * @param isrP Pointer to Isr
 */
static inline void Os_PreIsrHookStartI( OsIsrVarType *isrP ) {
    Os_PreIsrHook(isrP->id);
}

static inline void Os_PreIsrHookStartPreemptI( OsIsrVarType *isrP ) {
#if defined(CFG_T1_ENABLE)
    /* T1 figures out this state, so it does not want it */
#else
    Os_PreIsrHook(isrP->id);
#endif
}

/**
 * Call external hook function.
 *
 * @param isrP Pointer to Isr
 */
static inline void Os_PostIsrHookPreemptI( OsIsrVarType *isrP ) {
#if defined(CFG_T1_ENABLE)
    /* T1 figures out this state, so it does not want it */
#else
    Os_PostIsrHook(isrP->id);
#endif
}

/** */
static inline void Os_PostIsrHookTerminateI( OsIsrVarType *isrP ) {
    Os_PostIsrHook(isrP->id);
}


#endif


void Os_IsrResourceAdd( struct OsResource *rPtr, OsIsrVarType *isrPtr) {
    /* A resource can be owned by either a Task or an Isr. The owner element
     * is of TaskType, but let the Isr re-use the same. Before entering this
     * function, the resource should have no registered used anyway.
     */
    rPtr->owner = (TaskType)isrPtr->id;

    ASSERT( rPtr->type != RESOURCE_TYPE_INTERNAL );
}

static inline  void Os_IsrResourceRemove( OsResourceType *rPtr , OsIsrVarType *isrPtr) {
    ASSERT( rPtr->owner == isrPtr->id );
    rPtr->owner = NO_TASK_OWNER;

    if( rPtr->type != RESOURCE_TYPE_INTERNAL ) {
        /* The list can't be empty here */
        ASSERT( !TAILQ_EMPTY(&isrPtr->resourceHead) );

        /* The list should be popped in LIFO order */
        ASSERT( TAILQ_LAST(&isrPtr->resourceHead, head) == rPtr );

        /* Remove the entry */
        TAILQ_REMOVE(&isrPtr->resourceHead, rPtr, listEntry);
    }
}

static inline void Os_IsrResourceFreeAll( OsIsrVarType *isrPtr ) {
    OsResourceType *rPtr;

    /* Pop the queue */
    TAILQ_FOREACH(rPtr, &isrPtr->resourceHead, listEntry ) {
        Os_IsrResourceRemove(rPtr,isrPtr);
    }
}

static inline _Bool Os_IsrOccupiesResources(  OsIsrVarType *isrPtr ) {
    return !(TAILQ_EMPTY(&isrPtr->resourceHead));
}


void Os_IsrAddWithId( const OsIsrConstType * isrPtr, ISRType id ) {
    Os_IsrVarList[id].constPtr = isrPtr;
    Os_IsrVarList[id].id = id;
#if defined(CFG_OS_ISR_HOOKS)
    Os_IsrVarList[id].preemtedId = INVALID_ISR;
#endif
    Os_VectorToIsr[isrPtr->vector + IRQ_INTERRUPT_OFFSET ] = (uint8_t)id;
#if defined(CFG_TMS570) || defined(CFG_TRAVEO)
    Irq_EnableVector2( isrPtr->entry, isrPtr->vector, isrPtr->type,  isrPtr->priority, Os_ApplGetCore(isrPtr->appOwner) );
#elif defined(CFG_TC2XX)
    Irq_EnableVector2( isrPtr->entry, isrPtr->vector, isrPtr->type,  isrPtr->priority, IfxCpu_getCoreId() );
#else
    Irq_EnableVector( isrPtr->vector, isrPtr->priority, Os_ApplGetCore(isrPtr->appOwner )  );
#endif

}

void Os_IsrInit( void ) {

    Irq_Init();

    isrCnt = OS_ISR_CNT;
    /* Probably something smarter, but I cant figure out what */
    memset(Os_VectorToIsr,VECTOR_ILL,(size_t)NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS);

#if OS_ISR_CNT != 0
    /* Attach the interrupts */
    GetSpinlock(OS_SPINLOCK);
    for (ISRType i = 0; i < isrCnt; i++) {
        Os_IsrAddWithId(&Os_IsrConstList[i],i);
    }
    ReleaseSpinlock(OS_SPINLOCK);
#endif
}

/**
 * Adds an ISR to a list of Isr's. The ISRType (id) is returned
 * for the "created" ISR.
 *
 * @param isrPtr Pointer to const data holding ISR information.
 * @return
 */
ISRType Os_IsrAdd( const OsIsrConstType * isrPtr ) {
    ISRType id;
    ISRType installedId;

    ASSERT( isrPtr != NULL );
    ASSERT( (isrPtr->vector + IRQ_INTERRUPT_OFFSET) < NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS );

    /* Check if we already have installed it */
    installedId = (ISRType)Os_VectorToIsr[isrPtr->vector + IRQ_INTERRUPT_OFFSET ];

    if( installedId != VECTOR_ILL ) {
        /* The vector is already installed */
        id = installedId;
    } else {
        /* It a new vector */
#if (OS_NUM_CORES > 1)
        GetSpinlock(OS_RTE_SPINLOCK);
#endif
        id = isrCnt++;
#if (OS_NUM_CORES > 1)
        ReleaseSpinlock(OS_RTE_SPINLOCK);
#endif
		/* Since OS_ISR_MAX_CNT defines the allocation limit for Os_IsrVarList,
		 * we must not allocate more IDs than that */
        ASSERT(id<(ISRType)OS_ISR_MAX_CNT);

        Os_IsrAddWithId(isrPtr,id);
    }

    return id;
}

/*
 * Resources:
 *   Irq_VectorTable[]
 *   Irq_IsrTypeTable[]
 *   Irq_PriorityTable[]
 *
 *   exception table
 *   interrupt table
 *
 * Usual HW resources.
 * - prio in HW (ppc and arm (even cortex m4))
 *
 *
 * TOOL GENERATES ALL
 *   Irq_VectorTable   CONST
 *   Irq_IsrTypeTable  CONST
 *   Irq_PriorityTable CONST  Can probably be a table with ISR_MAX number
 *                            of for a CPU with prio registers.  For masking
 *                            CPUs it's better to keep an array to that indexing
 *                            can be used.
 *
 *   The problem with this approach is that the tool needs to know everything.
 *
 * TOOL GENERATES PART
 *   Irq_VectorTable   VAR     Since we must add vectors later
 *   Irq_IsrTypeTable  VAR     Since we must add vectors later
 *   Irq_PriorityTable VAR
 *
 *   We move the
 *
 */

/*-----------------------------------------------------------------*/

void Os_IsrGetStackInfo( OsIsrStackType *stack ) {
    stack->top = Os_IsrStack[GetCoreID()];
    stack->size = sizeof(Os_IsrStack[GetCoreID()]);
}

const OsIsrVarType *Os_IsrGet( ISRType id ) {
#if OS_ISR_MAX_CNT != 0
    if( id < isrCnt ) {
        return &Os_IsrVarList[id];
    } else  {
        return NULL;
    }
#else
    (void)id;
    return NULL;
#endif
}

ApplicationType Os_IsrGetApplicationOwner( ISRType id ) {
    /** @req OS274 */
    ApplicationType rv = INVALID_OSAPPLICATION;

#if (OS_ISR_MAX_CNT!=0)
    if( id < isrCnt ) {
        rv = Os_IsrGet(id)->constPtr->appOwner;
    }
#else
    (void)id;
#endif
    return rv;
}

#if defined(CFG_ARMV7_M)
extern uint32 Os_ArchNestedIsr;

void *Os_Isr( void *stack, int16_t vector ) {

    OsIsrVarType *isrPtr =  &Os_IsrVarList[Os_VectorToIsr[vector]];
    OsTaskVarType *taskPtr = NULL;
    OsIsrVarType *oldIsrPtr = NULL;

    ASSERT( isrPtr != NULL );

    if( isrPtr->constPtr->type == ISR_TYPE_1) {
        oldIsrPtr = OS_SYS_PTR->currIsrPtr;
        OS_SYS_PTR->currIsrPtr = isrPtr;
        OS_SYS_PTR->intNestCnt++;
        Irq_Enable();
        isrPtr->constPtr->entry();
        Irq_Disable();
        OS_SYS_PTR->intNestCnt--;
        OS_SYS_PTR->currIsrPtr = oldIsrPtr;
#if !defined(CFG_TMS570)
        ACK_INTERRUPT(vector);
#endif
        return stack;
    }

    /* Check if we interrupted a task or ISR */
    if( (OS_SYS_PTR->intNestCnt + Os_ArchNestedIsr) == 0 ) {
        /* We interrupted a task */
        POSTTASKHOOK();

        /* Save info for preempted pcb */
        taskPtr = Os_SysTaskGetCurr();
        // taskPtr->stack.curr = stack;
        taskPtr->state = ST_READY;
        OS_DEBUG(D_TASK,"Preempted %s\n",taskPtr->constPtr->name);

        Os_StackPerformCheck(taskPtr);
    } else {
        if( Os_ArchNestedIsr == 1) {
            /* Do nothing.
             * We have a run the ISR but it's not terminated yet. */
        } else {
            /* We interrupted an ISR, save current ISR id in this ISR  */
            oldIsrPtr = OS_SYS_PTR->currIsrPtr;
    #if defined(CFG_OS_ISR_HOOKS)
            isrPtr->preemtedId = oldIsrPtr->id;
            Os_PostIsrHookPreemptI(oldIsrPtr);
    #endif
        }
    }

    OS_SYS_PTR->intNestCnt++;

    isrPtr->state = ST_ISR_RUNNING;
    OS_SYS_PTR->currIsrPtr = isrPtr;

    Irq_SOI();
#if defined(CFG_ARM_CR4) || defined(CFG_TMS570LC43X)
    Irq_SOI3(isrPtr->constPtr->priority);
#endif

#if defined(CFG_OS_ISR_HOOKS)
    Os_PreIsrHookStartI(isrPtr);
#endif


#if defined(CFG_HCS12D)
    isrPtr->constPtr->entry();
#else
    Irq_Enable();
    isrPtr->constPtr->entry();
    Irq_Disable();
#endif

#if defined(CFG_OS_ISR_HOOKS)
    Os_PostIsrHookTerminateI(isrPtr );
    if( isrPtr->preemtedId != INVALID_ISR ) {
        OS_SYS_PTR->currIsrPtr = &Os_IsrVarList[isrPtr->preemtedId];
        Os_PreIsrHookStartPreemptI(OS_SYS_PTR->currIsrPtr);
        isrPtr->preemtedId = INVALID_ISR;
    }
#endif


    /* Check so that ISR2 haven't disabled the interrupts */
    /** @req OS368 */
    if( Os_SysIntAnyDisabled() ) {
        Os_SysIntClearAll();
        ERRORHOOK(E_OS_DISABLEDINT);
    }

    /* Check so that the ISR2 have called ReleaseResource() for each GetResource() */
    /** @req OS369 */
    if( Os_IsrOccupiesResources(isrPtr) ) {
        Os_IsrResourceFreeAll(isrPtr);
        ERRORHOOK(E_OS_RESOURCE);
    }

    isrPtr->state = ST_ISR_NOT_RUNNING;
    OS_SYS_PTR->currIsrPtr = isrPtr;

    ACK_INTERRUPT(vector);

    --OS_SYS_PTR->intNestCnt;

    return NULL;
}
#else

/**
 * Handle ISR type 2 interrupts from interrupt controller.
 *
 * @param stack Pointer to the current stack
 * @param vector
 */
void *Os_Isr( void *stack, int16_t vector ) {

    OsIsrVarType *isrPtr =  &Os_IsrVarList[Os_VectorToIsr[vector]];
    OsTaskVarType *taskPtr = NULL;
    OsIsrVarType *oldIsrPtr = NULL;

    ASSERT( isrPtr != NULL );

    if( isrPtr->constPtr->type == ISR_TYPE_1) {
        oldIsrPtr = OS_SYS_PTR->currIsrPtr;
        OS_SYS_PTR->currIsrPtr = isrPtr;
        OS_SYS_PTR->intNestCnt++;
        Irq_Enable();
        isrPtr->constPtr->entry();
        Irq_Disable();
        OS_SYS_PTR->intNestCnt--;
        OS_SYS_PTR->currIsrPtr = oldIsrPtr;
#if !defined(CFG_TMS570)
        ACK_INTERRUPT(vector);
#endif
        return stack;
    }

    /* Check if we interrupted a task or ISR */
    if( OS_SYS_PTR->intNestCnt == 0 ) {
        /* We interrupted a task */
        POSTTASKHOOK();

        /* Save info for preempted pcb */
        taskPtr = Os_SysTaskGetCurr();
        taskPtr->stack.curr = stack;
        taskPtr->state = ST_READY;
        OS_DEBUG(D_TASK,"Preempted %s\n",taskPtr->constPtr->name);

        Os_StackPerformCheck(taskPtr);
    } else {
        /* We interrupted an ISR, save it */
        oldIsrPtr = OS_SYS_PTR->currIsrPtr;
#if defined(CFG_OS_ISR_HOOKS)
        isrPtr->preemtedId = oldIsrPtr->id;
        Os_PostIsrHookPreemptI(oldIsrPtr);
#endif
    }

    OS_SYS_PTR->intNestCnt++;

    isrPtr->state = ST_ISR_RUNNING;
    OS_SYS_PTR->currIsrPtr = isrPtr;

    Irq_SOI();
#if defined(CFG_ARM_CR4) || defined(CFG_TMS570LC43X)
    Irq_SOI3(isrPtr->constPtr->priority);
#endif

#if defined(CFG_OS_ISR_HOOKS)
    Os_PreIsrHookStartI(isrPtr);
#endif


#if defined(CFG_HCS12D)
    isrPtr->constPtr->entry();
#elif defined(CFG_TRAVEO)
    isrPtr->constPtr->entry();
#else
    Irq_Enable();
    isrPtr->constPtr->entry();
    Irq_Disable();
#endif

#if defined(CFG_OS_ISR_HOOKS)
    Os_PostIsrHookTerminateI(isrPtr );
    if( isrPtr->preemtedId != INVALID_ISR ) {
        OS_SYS_PTR->currIsrPtr = &Os_IsrVarList[isrPtr->preemtedId];
        Os_PreIsrHookStartPreemptI( OS_SYS_PTR->currIsrPtr );
        isrPtr->preemtedId = INVALID_ISR;
    }
#endif


    /* Check so that ISR2 haven't disabled the interrupts */
    /** @req OS368 */
    if( Os_SysIntAnyDisabled() ) {
        Os_SysIntClearAll();
        ERRORHOOK(E_OS_DISABLEDINT);
    }

    /* Check so that the ISR2 have called ReleaseResource() for each GetResource() */
    /** @req OS369 */
    if( Os_IsrOccupiesResources(isrPtr) ) {
        Os_IsrResourceFreeAll(isrPtr);
        ERRORHOOK(E_OS_RESOURCE);
    }

    isrPtr->state = ST_ISR_NOT_RUNNING;
    OS_SYS_PTR->currIsrPtr = isrPtr;

    ACK_INTERRUPT(vector);

    --OS_SYS_PTR->intNestCnt;

    // We have preempted a task
    if( (OS_SYS_PTR->intNestCnt == 0) ) {
        OsTaskVarType *new_pcb  = Os_TaskGetTop();

        Os_StackPerformCheck(new_pcb);

        //lint -e{9007} MISRA False positive. No side effects of Os_SchedulerResourceIsFree
        if(     (new_pcb == OS_SYS_PTR->currTaskPtr) ||
                (OS_SYS_PTR->currTaskPtr->constPtr->scheduling == NON) ||
                !Os_SchedulerResourceIsFree() )
        {
            /* Just bring the preempted task back to running */
            OS_SYS_PTR->currTaskPtr->state = ST_RUNNING;
            PRETASKHOOK();
#ifdef CFG_T1_ENABLE
            Os_StartTaskHook(OS_SYS_PTR->currTaskPtr->constPtr->pid);
#endif
        } else {
            OS_DEBUG(D_TASK,"Found candidate %s\n",new_pcb->constPtr->name);

            // MAHI REMOVE
            /* Mark context with 0, so that we can free it later */
#if defined(CFG_TC2XX)
            {

                #define CSA_TO_ADDRESS(_csa)	( (((_csa) & 0x000f0000UL) << 12U) | (((_csa) & 0xffffL) << 6U ) )

                uint32_t *CSAPtr =  (uint32_t *)CSA_TO_ADDRESS(_mfcr(CPU_PCXI));
                CSAPtr[0] = 0;
            }
#endif

            Os_TaskSwapContextTo(NULL,new_pcb);
        }
    } else {
        /* We have a nested interrupt */

        /* Restore current running ISR from stack */
        OS_SYS_PTR->currIsrPtr = oldIsrPtr;
    }

    return stack;
}




#endif

void Os_Arc_GetIsrInfo( Arc_PcbType *pcbPtr, ISRType isrId ) {
    const OsIsrVarType *isrPtr = Os_IsrGet(isrId);

    if( isrPtr != NULL ) {
        strncpy(pcbPtr->name,Os_IsrGet(isrId)->constPtr->name,OS_ARC_PCB_NAME_SIZE);
    }

}

int Os_Arc_GetIsrCount( void ) {
    return (int)isrCnt;
}

