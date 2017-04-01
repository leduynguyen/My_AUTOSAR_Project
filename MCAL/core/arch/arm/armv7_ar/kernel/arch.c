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

extern void Os_TaskPost( void );

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/



StatusType Os_ArchGetProtectionType( uint32 exception ) {
    (void)exception;

    return E_OS_ILLEGAL;
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
    isrFramePtr->fpexc = 0;
#if defined(CFG_THUMB)
    isrFramePtr->psr = (0x1fu | 0x20);		/* System mode + Thumb */
#else
    isrFramePtr->psr = 0x1fu;				/* System mode */
#endif
    pcbPtr->regs[0] = 0;					/* regs[0] used to detect co-processor */

}

void Os_ArchInit( void ) {
#if (OS_SC3 == STD_ON) || (OS_SC4 == STD_ON)
    Os_MMInit();
#endif
}

void Os_ArchSetStackPointer(void *sp) {

}

