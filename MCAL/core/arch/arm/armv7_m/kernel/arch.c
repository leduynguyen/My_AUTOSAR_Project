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

/* ----------------------------[includes]------------------------------------*/


#include "os_i.h"
#include "Cpu.h"
#include "arch_stack.h"
#include "arc_assert.h"

//#define _DEBUG_ARCH

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/

extern uint8_t Os_VectorToIsr[NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS];

extern char _smspstack[];

/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

void PendSV_Handler(void);

/* Assembler functions in arch_krn.sx */
void Os_ArchTrigPendSV( void );
void Os_ArchSwapAndTrigPendSv( void );
uint32 Os_ArchNestedIsr = 0;

/**
 * Function make sure that we switch to supervisor mode(rfi) before
 * we call a task for the first time.
 */

void Os_ArchFirstCall( void )
{
    Irq_Enable();
    OS_SYS_PTR->currTaskPtr->constPtr->entry();
}

void *Os_ArchGetStackPtr( void ) {

    return (void *)__get_PSP();
}

unsigned int Os_ArchGetScSize( void ) {
    return SC_SIZE;
}

/**
 *
 */
void PendSV_Handler(void) {
/*lint -restore*/
  StackExceptionType *excFrame;

  excFrame = (StackExceptionType *)__get_PSP();
  excFrame++;
  __set_PSP((uint32_t)excFrame);
}


/*
 *  Stack:
 *  low address
 *
 *
 *
 *
 *
 *  xpsr     \
 *  pc       |
 *  lr       |
 *  r12      |
 *  r3       |  Exception frame
 *  r2       |
 *  r1       |
 *  r0       /
 *  higher address
 */


/**
 *
 */
void Os_ArchDoSwap( void ) {
	Os_ArchSwapContext(OS_SYS_PTR->oldTaskPtr, OS_SYS_PTR->currTaskPtr);
}



/**
 * Interrupt handler
 */

void Irq_Handler( void ) {

	StackExceptionType *excFrame;
	void *isIsr1;
	void *stack = (void *)__get_PSP();

	/* Known:
	 * 1. On MSP
	 * 2. Exception frame saved on PSP
	 */
	/* Get active vector */
	uint32 vector = SCB->ICSR & 0x1ffUL;

	/* Interrupts are NOT turned off until here, we may have nested interrupts here */
	Irq_Disable();

	ASSERT( (Os_SysIntAnyDisabled() == FALSE) );

	/* Lets run the interrupt */
	isIsr1 = Os_Isr( stack , vector );

#if (OS_STACK_MONITORING == 1)
	if( (_smspstack[0] != STACK_PATTERN) ) {
#if (  OS_SC1 == STD_ON) || (  OS_SC2 == STD_ON )
            /** @req OS068 */
            ShutdownOS(E_OS_STACKFAULT);
#else
            PROTECTIONHOOK(E_OS_STACKFAULT);
#endif
        }
#endif

	/* Check if we already have pending interrupts
	 * From RF:
	 *   "In Handler mode, indicates whether there is an active exception other than the exception
     *    indicated by the current value of the IPSR:
     *    0  There is an active exception other than the exception shown by IPSR.
	 *    1  There is no active exception other than any exception shown by IPSR.
	 * */
	if( (SCB->ICSR & SCB_ICSR_RETTOBASE_Msk) != 0UL ) {

		Os_ArchNestedIsr = 0;
		excFrame = (StackExceptionType *)__get_PSP();
		/* Add a new exception frame */
		excFrame--;
		excFrame->xpsr = (uint32)0x01000000;
		__set_PSP((uint32)excFrame);

		/* Interrupts are at this stage turned off, so we:
		 * - terminate the interrupt (code above)
		 * - "return" to function scheduler/PendSV
		 */

		if( isIsr1 != NULL ) {
			excFrame->pc = (uint32)Os_ArchTrigPendSV;
			return;
		}

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
			excFrame->pc = (uint32)Os_ArchTrigPendSV;
		} else {
			OS_SYS_PTR->oldTaskPtr = OS_SYS_PTR->currTaskPtr;
			Os_SysTaskSetCurr(new_pcb);
		#if	(OS_USE_APPLICATIONS == STD_ON)
			OS_SYS_PTR->currApplId = new_pcb->constPtr->applOwnerId;
		#endif
			Os_ResourceGetInternal();
			Os_TaskMakeRunning(new_pcb);
#ifdef CFG_T1_ENABLE
            Os_StartTaskHook(OS_SYS_PTR->currTaskPtr->constPtr->pid);
#endif
			PRETASKHOOK();
			excFrame->pc = (uint32)Os_ArchSwapAndTrigPendSv;
		}
		/* Return back to PSP stack */
		return;
	} else {
		Os_ArchNestedIsr = 1;
	}

	Irq_Enable();

	/* What happens if we get an interrupt here
	 * - The "old" ISR will still not be terminated
	 * - We will still be on MSP.. so the new interrupt will just be stacked there.
	 *
	 * It  must be a higher priority interrupt, since we would return otherwise.
	 *
	 * */
}

void Os_ArchSetTaskEntry(OsTaskVarType *pcbPtr ) {

}

void Os_ArchSetupContext( OsTaskVarType *pcbPtr ) {
	StackFuncType *fPtr = (StackFuncType *)((char *)pcbPtr->stack.curr);

    if( pcbPtr->constPtr->proc_type == PROC_EXTENDED ) {
    	fPtr->lr = (uint32_t)Os_TaskStartExtended;
    } else if( pcbPtr->constPtr->proc_type == PROC_BASIC ) {
    	fPtr->lr = (uint32_t)Os_TaskStartBasic;
    }
}

void Os_ArchInit( void ) {

}

