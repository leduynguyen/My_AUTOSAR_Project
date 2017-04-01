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
#include "irq.h"
#include "os_i.h"
#include "isr.h"
#include "irq_types.h"
#include "IfxScuWdt.h"
#include "IfxCpu_Reg.h"
#include "machine/intrinsics.h"
#include "IfxSrc_reg.h"
#include "IfxCpu.h"

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
typedef struct
{
    void *(* func)(void*, int16_t);
    uint32 vector;
} Irq_VectorEntry;

/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

/* Since the Tricore interrupt system is so whacked out we need to map
 * the interrupt priority (SRPN) to the vector.
 */


Irq_VectorEntry Irq_VectorTable[IRQ_SRPN_CNT];
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

extern TaskType Os_Arc_CreateIsr( void (*entry)(void ), uint8_t prio, const char *name );


extern uint8 int_tbl[];


void *Irq_NotMapped( void *stack, int16_t vector ) {

#if defined(CFG_OPT_DEBUG)
    _debug();
#endif

    return stack;
}

void Irq_Init( void ) {

    /*
     * Setup Interrupt vector table.
     *
     * The trap table should have been setup at an earlier stage
     * so it's not done here.
     */

    uint32 coreId      = IfxCpu_getCoreId();

    /* Validation or the interrupt vector placement */
#if defined(CFG_OPT_DEBUG)
    uint32 bivAddress = (uint32)&int_tbl[0];
    uint32 isrPtrRange = (IRQ_SRPN_TOP_PRIO << 3UL) - 1UL;
    /* The prio (SRPN) value of an interrupt is used to get
     * the offset address in the interrupt table vector to access
     * the interrupt entry. So the isr entry address will be:
     *
     * offset = SRPN << 3;
     * int_entry = int_tbl | offset;
     *
     * With this check we verify that the int_table address is
     * "clean" so that the OR operation will not accidently access
     * the wrong int_entry.
     */
    if (0UL < (bivAddress & isrPtrRange)) {
        _debug();
    }
#endif

    /* ENDINIT protected */
    uint16 cpuWdtPassword = IfxScuWdt_getCpuWatchdogPasswordInline(&MODULE_SCU.WDTCPU[coreId]);
    uint32 bivReg = (uint32)&int_tbl[0] | 1UL; /* vector table addr + VSS bit set to 1 */

    /* Set BIV (vector base address) */
    IfxScuWdt_clearCpuEndinitInline(&MODULE_SCU.WDTCPU[coreId], cpuWdtPassword);
    __mtcr(CPU_BIV, bivReg);
    IfxScuWdt_setCpuEndinitInline(&MODULE_SCU.WDTCPU[coreId], cpuWdtPassword);

    for(uint32 i=0;i<IRQ_SRPN_CNT;i++) {
        Irq_VectorTable[i].func = Irq_NotMapped;
    }

}


void Irq_EOI( int16_t vector ) {
    (void)vector;
}

#define ICSR_VECTACTIVE		0x1ff


extern void Os_IsrEntry( void );

void Irq_EnableVector2( IrqFuncType func,  int16_t vector, uint16_t type,  uint8_t priority, int core )
{
    Ifx_SRC_SRCR *srcTable = (Ifx_SRC_SRCR *)&MODULE_SRC;

    srcTable[vector].U = priority | core<<11U | 1UL<<10U;

//	srcTable[vector].B.SRPN = priority;
//	srcTable[vector].B.TOS = core;
//	srcTable[vector].B.SRE = 1; /* Enable vector */

    if( type == ISR_TYPE_1 ) {
        // Irq_VectorTable[priority].func = func;
        Irq_VectorTable[priority].func = Os_Isr;
    } else {
        Irq_VectorTable[priority].func = Os_Isr;
    }

    Irq_VectorTable[priority].vector = vector;

}

/**
 * Generates a soft interrupt, ie sets pending bit.
 * This could also be implemented using ISPR regs.
 *
 * @param vector
 */
void Irq_GenerateSoftInt( IrqType vector ) {
    if ((vector >= IRQ_SRC_GPSR00) && (vector <= IRQ_SRC_GPSR23)) {

        Ifx_SRC_SRCR *srcTable = (Ifx_SRC_SRCR *)&MODULE_SRC;

        _isync();
        _dsync();
        srcTable[vector].B.SETR = 1;
        _isync();
        _dsync();
    }
}

/**
 * Acknowledge a soft interrupt.
 *
 * @param vector
 */
void Irq_AckSoftInt( IrqType vector ) {
    if ((vector >= IRQ_SRC_GPSR00) && (vector <= IRQ_SRC_GPSR23)) {

        Ifx_SRC_SRCR *srcTable = (Ifx_SRC_SRCR *)&MODULE_SRC;

        srcTable[vector].B.CLRR = 1;
    }
}

/**
 * Get the current priority from the interrupt controller.
 * @param cpu
 * @return
 */
uint8_t Irq_GetCurrentPriority( Cpu_t cpu) {

    return 0;
}
