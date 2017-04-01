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

/* ----------------------------[information]----------------------------------*/
/*
 * Author: mahi
 *
 * Description:
 *
 *
 */

/* ----------------------------[includes]------------------------------------*/


#include "os_i.h"
#include "isr.h"
#include "irq_types.h"
#if defined(__ghs__)
#include "v800_ghs.h"
#endif


/* ----------------------------[private define]------------------------------*/

#if defined(CFG_RH850F1H)
/* First 32 entries */
#define IC_0TO31_BASE 	0xFFFEEA00ul
/* The rest  */
#define IC_32TOX_BASE 	0xFFFFB040ul
#elif defined(CFG_RH850F1L)
#define IC_0TO31_BASE 	0xFFFF9000ul
#define IC_32TOX_BASE 	0xFFFFA040ul
#else
#error Base not defined
#endif

#define IC_0TO31 (*(struct IC_regs *)IC_0TO31_BASE)
#define IC_32TOX (*(struct IC2_regs *)IC_32TOX_BASE)


#define IC_RF(_x)		((_x)<<12)		/* Interrupt request */
#define IC_MK(_x)		((_x)<<7)		/* 1-Mask Interrupt */
#define IC_PRIO(_x)		(_x)			/* Prio */

/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
struct IC_regs {
            vuint16_t ic[32];
        };

struct IC2_regs {
            vuint16_t ic[350-32];
        };

/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
uint16_t Irq_Index =  0;

/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/


extern TaskType Os_Arc_CreateIsr( void (*entry)(void ), uint8_t prio, const char *name );
extern void *Irq_VectorTable[NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS];

static void writeIC( IrqType vector, uint32_t val) {
    if( vector < 32 ) {
        IC_0TO31.ic[vector] = val;
    } else {
        IC_32TOX.ic[vector-32] = val;
    }
    synci();
}


static uint32_t readIC( IrqType vector ) {
    uint32_t val;
    if( vector < 32 ) {
        val = IC_0TO31.ic[vector];
    } else {
        val = IC_32TOX.ic[vector-32];
    }

    return val;
}



/**
 * The interrupt controller have 8 levels, 0 to 7 , 0-high,7-low
 * Autosar have prio=0 as lowest and then up..
 *
 * @param prio
 * @return
 */
static inline uint8_t osPrioToCpuPio( uint8_t prio ) {
    ASSERT(prio<32);
    return (31 - prio)/4;
}




void Irq_SetPriority( CoreIDType cpu,  IrqType vector, uint8_t prio ) {

    /* RH850/F1H have 8! interrupt priorities.. */
    uint8_t val = osPrioToCpuPio(prio);

    writeIC(vector,IC_PRIO(val));
}


static void Intc_Init( void ) {
    /*
    * Rh850g3m
    * ----------------------
    * SR7,1  FPIPR  - Floating point exceptions.....
    * SR10,2 ISPR   - Serviced interrupt priority
    * SR11,2 PMR    - Interrupt priority masking
    * SR12,2 ICSR   - Interrupt status (Read Only)
    * SR13,2 INTCFG - ISPR update setting (auto or manual)
    */

    /*
    * RH850F1H
    * - ICxxx				- 350 interrupts  (exception code?)
    *                       - Request interrupt
    *                       - Interrupt level 0-high, 7-lowest...
    * - IMRm                - 0 to 11 , Interrupt enable
    * - IBDxxx              - Bind Interrupt to CORE1 or CORE2 (350 regs)
    * - SELB_INTC1 (16-bit) - Multiplexer for some interrupts
    * - SELB_INTC2 (16-bit) - Multiplexer for some interrupts
    *
    * SR2,1 RBASE - Reset vector base
    * SR3,1 EBASE - Exception vector base
    * SR4,1 INTBP - Base address of interrupt table (not used since we go on priority instead)
    */

    /* - Setup EBASE to somewhere else so we can have a bootloader.
     * - Exception Table: Use Direct Mode (see 4.5.1) */

    /* Strategy:
     * 1. Point all vectors to the same routine (the exception code is in EIIC)
     * 2.
     */
}


void Irq_Init( void ) {
    Intc_Init();
}

void *Irq_Entry( void *stack_p )
{
    uint16_t code =  get_sr( 13,0 );	/* Get EIIC */
    uint16_t vector = 0;

    /* assume for now its an EI int */
    if( code >= 0x1000 ) {
        vector = code - 0x1000;
    } else {
        while(1) {};
    }

    Os_Isr(stack_p,vector);

    return stack_p;
}

void Irq_EOI( int16_t vector ) {
    (void)vector;
    /* Ack interrupt */
    --Irq_Index;
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

    // IMPROVEMENT: Use NVIC_InitVector(vector, osPrioToCpuPio(pcb->prio)); here
}



void Irq_EnableVector( int16_t vector, uint8_t priority, int core ) {

    if (vector < NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS) {
        uint32_t val;

        Irq_SetPriority( core,  vector, priority );

        /* Enable interrupt */
        val = readIC(vector);

        /* Set MK=0 */
        writeIC( vector, (val & ~(IC_RF(1)|IC_MK(1))) | IC_MK(0) );

        /*
        * - ICxxx				- 350 interrupts  (exception code?)
        *                       - Request interrupt
        *                       - Interrupt level 0-high, 7-lowest...
        * - IMRm                - 0 to 11 , Interrupt enable
        * - IBDxxx              - Bind Interrupt to CORE1 or CORE2 (350 regs)
        * - SELB_INTC1 (16-bit) - Multiplexer for some interrupts
        * - SELB_INTC2 (16-bit) - Multiplexer for some interrupts
        */
    } else {
        /* Invalid vector! */
        ASSERT(0);
    }
}

/**
 * Generates a soft interrupt, ie sets pending bit.
 * This could also be implemented using ISPR regs.
 *
 * @param vector
 */
void Irq_GenerateSoftInt( IrqType vector ) {

    /* Set RF bit to generate interrupt, leave the rest */
    uint32 val = readIC(vector);
    writeIC( vector, val | IC_RF(1));

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


