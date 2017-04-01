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
#include "isr.h"
#include "irq_types.h"

extern void *Irq_VectorTable[NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS];

/**
 * Init NVIC vector. We do not use subpriority
 *
 * @param vector	The IRQ number
 * @param prio      NVIC priority, 0-31, 0-high prio
 */
static void NVIC_InitVector(IRQn_Type vector, uint32_t prio)
{
    // Set prio
    NVIC_SetPriority(vector,prio);

    if(vector>=0){
        // Enable
        NVIC->ISER[(uint8_t)vector >> 5] = (uint32_t)1 << ((uint8_t)vector & (uint8_t)0x1F);
    }
}

/*
PRIGROUP
0 			7.1 indicates seven bits of pre-emption priority, one bit of subpriority
1 			6.2 indicates six bits of pre-emption priority, two bits of subpriority
2 			5.3 indicates five bits of pre-emption priority, three bits of subpriority
3 			4.4 indicates four bits of pre-emption priority, four bits of subpriority
4 			3.5 indicates three bits of pre-emption priority, five bits of subpriority
5 			2.6 indicates two bits of pre-emption priority, six bits of subpriority
6 			1.7 indicates one bit of pre-emption priority, seven bits of subpriority
7 			0.8 indicates no pre-emption priority, eight bits of subpriority.
*/
void Irq_Init( void ) {
    NVIC_SetPriorityGrouping(0);
//    NVIC_SetPriority(PendSV_IRQn, 0xff); // Set lowest prio
    NVIC_SetPriority(PendSV_IRQn, 0x00); // Set highest prio

//    NVIC_SetPriority(SVCall_IRQn, 0xff); // Set lowest prio
//    NVIC_SetPriority(PendSV_IRQn, 0x0); // Set highest prio

#if defined(CFG_STM32F1X) || defined(CFG_STM32F3X)

    /* Stop counters and watchdogs when halting in debug */
    DBGMCU->CR |= 0x00ffffff00;
#endif
}

void Irq_EOI( int16_t vector ) {
    (void)vector;
    /* Note!
     * This is not applicable on the Cortex-M3 since we
     * can't terminate the interrupt request without popping
     * back registers..have to be solved in the context switches
     * themselves.
     */
}

#define ICSR_VECTACTIVE		0x1ff


/**
 * In the ARMv7-M priority model, lower numbers take precedence. That is, the lower the assigned priority value, the
 * higher the priority level. The priority order for exceptions with the same priority level is fixed, and is determined
 * by their exception number.
 *
 * NVIC have 16 priority levels.
 *
 * Autosar    NVIC
 *   31        	0
 *   30        	0
 *   .....
 *   1			15
 *   0
 * @param prio
 * @return
 */
static inline uint8_t osPrioToCpuPio( uint8_t prio ) {
    ASSERT(prio<32);
    return (15 - (prio>>1));
}


void Irq_EnableVector( int16_t vector, uint8_t priority, int core ) {
	(void)core;
	NVIC_InitVector((IRQn_Type)vector, osPrioToCpuPio(priority));
}

/**
 * Generates a soft interrupt, ie sets pending bit.
 * This could also be implemented using ISPR regs.
 *
 * @param vector
 */
void Irq_GenerateSoftInt( IrqType vector ) {

	NVIC->STIR =(uint8_t)vector;
	__ASM volatile ("dsb");
	__ASM volatile ("isb");
	__ASM volatile ("nop");
	__ASM volatile ("nop");
}

/**
 * Get the current priority from the interrupt controller.
 * @param cpu
 * @return
 */
uint8_t Irq_GetCurrentPriority( Cpu_t cpu) {

    uint8_t prio = 0;

    // SCB_ICSR contains the active vector
    return prio;
}

typedef struct {
    uint32_t dummy;
} exc_stack_t;


