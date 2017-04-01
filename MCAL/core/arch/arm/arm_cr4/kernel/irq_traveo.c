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
#include "isr.h"
#include "irq_types.h"
#include "core_cr4.h"

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/

#define IRC     (*(volatile struct IRC_Reg *)       0xB0400000UL)

#define UNLOCK_UNLOCK  0x17ACC911UL
#define UNLOCK_LOCK    0x17B10C11UL


/* ----------------------------[private typedef]-----------------------------*/

struct IRC_Reg {
    vuint32_t NMIVAS;
    vuint32_t NMIST;          /* NMI Status Register */
    vuint32_t IRQVAS;         /* IRQ Vector Address Status Register */
    vuint32_t IRQST;          /* IRQ Status Register */
    vuint32_t NMIVA[32];     /* NMI Vector Address Register */
    vuint32_t IRQVA[512];     /* IRQ Vector Address Register  */
    vuint32_t NMIPL[8];       /* NMI Priority Level Register */
    vuint32_t IRQPL[128];     /* IRQ Priority Level Register*/
    vuint32_t NMIS;           /* NMI Software Interrupt Set Register */
    vuint32_t NMIR ;          /* NMI Software Interrupt Reset Register   */
    vuint32_t NMISIS ;        /* NMI Software Interrupt Status Register */
    vuint32_t :32;            /*  */
    vuint32_t IRQS[16];       /* IRQ Software Interrupt Set Register  */
    vuint32_t IRQR[16];       /* IRQ Software Interrupt Reset Register  */
    vuint32_t IRQSIS[16];     /* IRQ Software Interrupt Status Register  */
    vuint32_t IRQCES[16];     /* IRQ Channel Enable Set Register  */
    vuint32_t IRQCEC[16];     /* IRQ Channel Enable Clear Register  */
    vuint32_t IRQCE[16];      /* IRQ Channel Enable Setting Register   */
    vuint32_t NMIHC;          /* NMI Hold Clear Register */
    vuint32_t NMIHS;          /* NMI Hold Status Register */
    vuint32_t IRQHC;          /* IRQ Hold Clear Register */
    vuint32_t :32;
    vuint32_t IRQHS[16];      /* IRQ Hold Status Register */
    vuint32_t IRQPLM ;        /* IRQ Priority Level Mask Register  */
    vuint32_t :32;
    vuint32_t CSR;            /* Control/Status Register */
    vuint32_t :32;
    vuint32_t :32;
    vuint32_t :32;
    vuint32_t NMIRS ;         /* NMI RAW Status Register */
    vuint32_t NMIPS;          /* NMI Preprocessed Status Register */
    vuint32_t IRQRS[16];      /* IRQ RAW Status Register   */
    vuint32_t IRQPS[16];      /* IRQ Preprocessed Status Register  */
    vuint32_t UNLOCK;         /* Unlock Register */
    vuint32_t :32;
    vuint32_t :32;
    vuint32_t IRQEEVA;        /* ECC Error Vector Address Register  */
    vuint32_t EEI;            /* ECC Error Interrupt Register */
    vuint32_t EAN;            /* ECC Address Number Register*/
    vuint32_t ET ;            /* ECC Test Register  */
    vuint32_t EEB[3];         /* ECC Error Bit Register */
};

typedef void (* IrqFuncType)(void);

uint32 eoi = 0;

/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

IrqFuncType Irq_VectorTable[NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS];

/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

extern void Irq_Handler( void );

/**
 * Function to initialize the interrupt controller.
 */
void Irq_Init( void ) {
    /* Nothing to do */
}

/**
 *
 * @param stack_p Ptr to the current stack.
 */
void *Irq_Entry( void *stack_p ) {

    /* We enter here in interrupt suppress state ( AN 3.1 ) */

    /* To be able to read from IRQST we must enable the global
     * interrupts, but we are still in interrupt suppress state
     */
    Irq_Enable();

    /* Grab channel, reading this */
    uint16_t channel = IRC.IRQST & 0x3ffUL;

    Os_Isr(stack_p, channel );

    return stack_p;
}


void Irq_SOI( void ) {
    Irq_Enable();
    IRC.CSR = 1;
}

void Irq_EOI( int16_t vector ) {
    /* Ack interrupt */
    while ( (IRC.IRQST & 0x01000000UL) == 0 ) {}

    Irq_Disable();

    IRC.IRQHC = vector;
    eoi++;
}

/**
 * Attach an ISR type 1 to the interrupt controller.
 *
 * @param entry
 * @param int_ctrl
 * @param vector
 * @param prio
 */
void Irq_AttachIsr1( void (*entry)(void), void *int_ctrl, uint32_t vector, uint8_t prio) {

}

/**
 * Enable a vector in the interrupt controller.
 *
 * @param func
 * @param vector
 * @param type
 * @param priority
 * @param core
 */
void Irq_EnableVector2( IrqFuncType func,  int16_t vector, uint16_t type,  uint8_t priority, int core ) {

    (void)core;

    /* Invalid vector! */
    ASSERT(vector < NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS);

    IRC.UNLOCK = UNLOCK_UNLOCK;

    if( type == ISR_TYPE_1 ) {
        /* No suppport yet */
        ASSERT(0);
    }

    if( type == ISR_TYPE_2  ) {
        IRC.IRQVA[vector] = (uint32)Irq_Handler;
        Irq_VectorTable[vector] = func;
    }

    /* Enable interrupt */
    IRC.IRQCE[vector/32] |= (1 << (vector%32));

    /* Priority */
    IRC.IRQPL[vector/4] |= (priority << ((vector%4)*8) );

    /* Enable IRQ processing block */
    IRC.CSR |= 1UL;        /* IRQEN = 1, Enable IRQs */

}


/**
 * Generates a soft interrupt
 *
 * Note! This implementation uses real HW interrupts
 * for vector 9 and 23
 *
 * @param vector
 */
void Irq_GenerateSoftInt( IrqType vector ) {
    IRC.IRQS[vector/32] |= (1 << (vector%32));
}

void Irq_AckSoftInt( IrqType vector ) {

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


