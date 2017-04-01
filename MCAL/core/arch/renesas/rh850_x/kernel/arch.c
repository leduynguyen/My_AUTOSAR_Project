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
#include "asm_rh850.h"
#include "arch_stack.h"
#include "irq.h"
#include "arch.h"
#include <stdio.h>

#define PSW_UM_BIT       30u
#define PSW_CU0_BIT      16u
#define PSW_EBV_BIT      15u
#define PSW_NP_BIT       7u
#define PSW_EP_BIT       6u
#define PSW_ID_BIT       5u




#if defined(__ghs__)
static int bla = 0;

__interrupt void test( void ) {
    bla++;
}
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

    /* No memory protection support */
    return E_OS_PROTECTION_EXCEPTION;
}


void Os_ArchFirstCall( void )
{
}


/**
 * Function make sure that we switch to supervisor mode(rfi) before
 * we call a task for the first time.
 */

void *Os_ArchGetStackPtr( void ) {

    return (void *)0;
}


unsigned int Os_ArchGetScSize( void ) {
    return sizeof(Os_IsrFrameType)+C_SIZE;
}

void Os_ArchSetTaskEntry(OsTaskVarType *pcbPtr ) {
    /* Not used, setup in Os_ArchSetupContext() instead */
    (void)pcbPtr;
}

void Os_ArchSetupContext( OsTaskVarType *pcbPtr ) {

    Os_IsrFrameType *isrFramePtr = (Os_IsrFrameType *)((char *)pcbPtr->stack.curr + C_SIZE);
    uint32_t *context = (uint32_t *)pcbPtr->stack.curr;

    context[0] = 0UL;
    context[1] = ISR_PATTERN;

    isrFramePtr->r4 = 0x12345678;
    isrFramePtr->r31 = (uint32_t)Os_TaskPost;
    isrFramePtr->xpc = (uint32_t)pcbPtr->constPtr->entry;
    isrFramePtr->xpsw = (0UL<<PSW_UM_BIT) +     /* 0 - Supervisor mode */
#if defined(CFG_HW_FLOAT)
                        (1UL<<PSW_CU0_BIT) +    /* CU0 - 1 FPU enable */
#endif
                        (1UL<<PSW_EBV_BIT) +    /* EBV */
                        (0UL<<PSW_NP_BIT) +     /* 0: The acknowledgement of FE level exception is enabled. */
                        (0UL<<PSW_EP_BIT) +     /* 1: An exception other than an interrupt is being serviced.  */
                        (0UL<<PSW_ID_BIT);      /* 0: The acknowledgement of EI level exception is enabled. */
}

void Os_ArchInit( void ) {
#if (OS_SC3 == STD_ON) || (OS_SC4 == STD_ON)
    Os_MMInit();
#endif
}

void Os_ArchSetStackPointer(void *sp) {

}

