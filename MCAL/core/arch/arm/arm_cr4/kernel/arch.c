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
#include "arch_stack.h"
//#include "sys.h"
#include "Cpu.h"
#if defined(CFG_TMS570)
#include "core_cr4.h"
#endif
#include "asm_arm.h"

extern void Os_TaskPost( void );

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/




StatusType Os_ArchGetProtectionType( uint32 exception ) {
    StatusType rv;

    if( (exception == EXC_UNDEFINED_INSTRUCTION) || (exception == EXC_PREFETCH_ABORT) ) {
        /* @req 4.1.2/SWS_OS_00245 *//* @req OS245 Instruction exceptions */
        rv = E_OS_PROTECTION_EXCEPTION;
    } else if( exception == EXC_DATA_ABORT ) {
        /* @req 4.1.2/SWS_OS_00044 Memory Access violation */
        /* @req OS044
         * If a memory access violation is detected, the Operating System module shall call the Protection Hook */
        rv = E_OS_PROTECTION_MEMORY;
    } else {
        rv = E_OS_ILLEGAL;
    }

    return rv;
}


void Os_ArchFirstCall( void )
{
    // IMPROVEMENT: make switch here... for now just call func.
    Irq_Enable();
    OS_SYS_PTR->currTaskPtr->constPtr->entry();
}


/**
 * Function make sure that we switch to supervisor mode(rfi) before
 * we call a task for the first time.
 */

void *Os_ArchGetStackPtr( void ) {

    return (void *)0;
}


unsigned int Os_ArchGetScSize( void ) {
    return 128;
}

void Os_ArchSetTaskEntry(OsTaskVarType *pcbPtr ) {
    /* Not used, setup in Os_ArchSetupContext() instead */
    (void)pcbPtr;
}

void Os_ArchSetupContext( OsTaskVarType *pcbPtr ) {

    uint32 psr = 0;
    /* Our only reference here is the stack for the task.
     * We should fill the stack with "things" that is then
     * pop:ed by Os_ArchSwapContextTo()
     *
     * - We need to use a large context here since it
     *   manipulates PSR when it return (ie rfeia	sp! )
     * - Os_StackSetup() will setup the stack so it points
     *   with space for the context
     *
     *  Address  Description
     *  ---------------------------------------
     *      high
     *
     *      xx+4  CPSR	   (from exception)
     *        xx  LR       (from exception)
     *        ...
     *        14       ^
     *        12       |
     *         8 -- ARM REGS ----
     *         4 context indicator
     *         0 stack
     *        ...    <---- pcbPtr->stack.curr will point here at this stage..
     *      low
     */
    Os_IsrFrameType *isrFramePtr = (Os_IsrFrameType *)((char *)pcbPtr->stack.curr + C_SIZE);
    uint32_t *context = (uint32_t *)pcbPtr->stack.curr;

    /* Zero out the context */
    memset(isrFramePtr,0,sizeof(Os_IsrFrameType) );

    context[0] = 0; 			/* unused? */
    context[1] = LC_PATTERN;

    isrFramePtr->lr = (uint32_t)Os_TaskPost;
    isrFramePtr->pc = (uint32_t)pcbPtr->constPtr->entry;


#if (OS_SC3==STD_ON) || (OS_SC4==STD_ON)
    if( !Os_AppConst[pcbPtr->constPtr->applOwnerId].trusted ) {
        /* Non-trusted */
        psr = 0x10UL;   /* User Mode */
    } else {
        psr = 0x1Ful;   /* System Mode */
    }
#endif


#if defined(CFG_THUMB)
    psr |= 0x20UL;            /* Thumb mode */
#endif
#if defined(CFG_BIG_ENDIAN)
    psr |= (1<<9);
#endif
    isrFramePtr->psr = psr;

    pcbPtr->regs[0] = 0;

#if (OS_SC3==STD_ON) || (OS_SC4==STD_ON)

    /*
     * Setup the stack, .data and .bss regions
     *
     * We only have requirements to protect Application space:
     * - Application data                 __OS_START_SEC_data_<all tasks in application>
     * - Application bss                  __OS_START_SEC_bss_<all tasks in application>
     * - Applications Tasks stack, bss    __OS_START_SEC_stack__<all tasks in application>
     *                                    These symbol are useless and not used.
     * - Execute rights                   Hmmm, we have to group all code and application, jobbigt.
     *
     * .dataStart =    __OS_START_SEC_data_«task.shortName»,
     * .dataEnd = __OS_STOP_SEC_data_«task.shortName»,
     * .bssStart =     __OS_START_SEC_bss_«task.shortName»,
     * .bssEnd = __OS_STOP_SEC_bss_«task.shortName»,
     *
     * So, we keep
     * */


    /* One entry for each stash, data and bss
     *
     * We convert range to base and size
     * */

    /* Stack */
    pcbPtr->regs[MPU0_REG_TASK_STACK_BASEADDR] = (uint32_t)pcbPtr->stack.top;
    pcbPtr->regs[MPU0_REG_TASK_STACK_SIZEENABLE] = ((uint32_t)ilog2((uint32_t)pcbPtr->stack.size) << 1U) | 1UL ;

    /* .data */
    pcbPtr->regs[MPU0_REG_TASK_DATA_BASEADDR] = (uint32_t)pcbPtr->constPtr->dataStart;
    pcbPtr->regs[MPU0_REG_TASK_DATA_SIZEENABLE] =
            ((uint32)ilog2((uint32)pcbPtr->constPtr->dataEnd - (uint32)pcbPtr->constPtr->dataStart ) << 1U) | 1UL ;

    /* .bss */
    pcbPtr->regs[MPU0_REG_TASK_BSS_BASEADDR] = (uint32_t)pcbPtr->constPtr->bssStart;
    pcbPtr->regs[MPU0_REG_TASK_BSS_SIZEENABLE] =
            ((uint32)ilog2((uint32)pcbPtr->constPtr->bssEnd - (uint32)pcbPtr->constPtr->bssStart ) << 1U) | 1UL ;
#endif

}

void Os_ArchInit( void ) {
#if (OS_SC3 == STD_ON) || (OS_SC4 == STD_ON)
    Os_MMInit();
#endif
}

void Os_ArchSetStackPointer(void *sp) {

}


