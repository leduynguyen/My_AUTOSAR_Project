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
#include "context.h"
#include "isr.h"
#include "sys.h"

/**
 * Function make sure that we switch to supervisor mode(rfi) before
 * we call a task for the first time.
 */

void Os_ArchFirstCall( void )
{
    // IMPROVEMENT: make switch here... for now just call func.
    Irq_Enable();
    Os_Sys.currTaskPtr->constPtr->entry();
}

#if defined(__IAR_SYSTEMS_ICC__)
// in arch_krn.sx

#else
void *Os_ArchGetStackPtr( void ) {
  void* val;

  asm("sts _.tmp");
  asm volatile("movw _.tmp, %0":"=m" (val));

  return val;
}
#endif


unsigned int Os_ArchGetScSize( void ) {
    return CONTEXT_SIZE_W;
}


void Os_ArchSetupContext( OsTaskVarType *pcb ) {
  // Nothing to be done here
}

/**
 *
 * @param pcbPtr
 */

#if defined(__ICCHCS12__)
void Os_ArchSetTaskEntry(OsTaskVarType *pcbPtr ) {
    uint8_t *context_bytes = (uint8_t *)pcbPtr->stack.curr;
    uint32_t temp;

    /* Set Return to start function */
    if( pcbPtr->constPtr->proc_type == PROC_EXTENDED ) {
        temp = (uint32_t)Os_TaskStartExtended;
      context_bytes[0] = temp >> 16;
        context_bytes[HIGH_BYTE_RETURN_ADRESS] = temp >> 8;
        context_bytes[LOW_BYTE_RETURN_ADRESS] = temp & 0xFF;
    } else if( pcbPtr->constPtr->proc_type == PROC_BASIC ) {
        temp = (uint32_t)Os_TaskStartBasic;
      context_bytes[0] = temp >> 16;
        context_bytes[HIGH_BYTE_RETURN_ADRESS] = temp >> 8;
        context_bytes[LOW_BYTE_RETURN_ADRESS] = temp & 0xFF;
    }
}
#else
void Os_ArchSetTaskEntry(OsTaskVarType *pcbPtr ) {
    uint8_t *context_bytes = (uint8_t *)pcbPtr->stack.curr;
    uint16_t temp;

    /* Set Return to start function */
    context_bytes[8] = OS_KERNEL_CODE_PPAGE;

    if( pcbPtr->constPtr->proc_type == PROC_EXTENDED ) {
        temp = (uint16_t)Os_TaskStartExtended;
        context_bytes[HIGH_BYTE_RETURN_ADRESS] = temp >> 8;
        context_bytes[LOW_BYTE_RETURN_ADRESS] = temp & 0xFF;
    } else if( pcbPtr->constPtr->proc_type == PROC_BASIC ) {
        temp = (uint16_t)Os_TaskStartBasic;
        context_bytes[HIGH_BYTE_RETURN_ADRESS] = temp >> 8;
        context_bytes[LOW_BYTE_RETURN_ADRESS] = temp & 0xFF;
    }
}
#endif

void Os_ArchInit( void ) {
  // Nothing to be done here
}
