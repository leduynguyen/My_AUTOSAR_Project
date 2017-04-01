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
 *   INTERRUPTS
 *   -------------------------------------
 *   Implements GICv1 (Global Interrupt Controller) found in Cortex-A9 (ARMv7-AR)
 *
 *   PPI - Private peripheral interrupts
 *         5 - Global Timer, CPU private timer, Watchdog, nFIQ and nIRQ
 *
 *   SPI - Shared peripheral interrupts
 *         60 - "Normal" peripherals such as CAN, ADC, etc.
 *
 *   SGI - Software generated interrupts
 *
 *
 *   SECURE VS NON-SECURE
 *   -------------------------------------
 *   The zynq have implemented the security extensions in the GIC.
 *   By default all interrupts are defined as secure (ICDISRx is 0)
 *
 *   The priorities are implemented differently depending on if security
 *   is used or not. This implementation will use only the 5 most MSB bits.
 *
 *
 *
 *
 * References:
 *   - GIC_architecture_spec_v1_0.pdf
 *   - DDI0416B_gic_pl390_r0p0_trm.pdf - Programmers model for GIC(pl390)
 *
 * From Zynq:
 * -  In addition, the controller supports security extension for implementing a security-aware system
 *
 *
 *
 */



/* ----------------------------[includes]------------------------------------*/


#include "os_i.h"
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
#include "isr.h"
#endif
#include "irq_types.h"
#include "zynq.h"


/* ----------------------------[private define]------------------------------*/

#define GIC_SECURE

/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/


extern TaskType Os_Arc_CreateIsr( void (*entry)(void ), uint8_t prio, const char *name );
extern void *Irq_VectorTable[NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS];

#define IRQ_TRIGGER_RISING_EDGE		3
#define IRQ_TRIGGER_HIGH_LEVEL		1




#define GIC_CORE		0

#define NUM_SPI			64
#define NUM_INTERRUPTS	(NUM_SPI+32)



/**
 * GIC secure prio using only secure is 32 levels.
 * GIC have have prio=0 as highest while Autosar have prio=0
 * as lowest
 *
 * @param prio
 * @return
 */
static inline uint8_t osPrioToCpuPio( uint8_t prio ) {
    ASSERT(prio<32);
    prio = 31 - prio;
    return prio;
}


static void GIC_DistrubutorInit( void ) {
    int i;

    /* We have a GIC distributor and a GIC */

    /* Disable forwarding */
    ICD.ICDDCR = 0;

    /* SPI Init, Table 7-3 in RM  (called CDICFR2-> in RM )
     * 01 : High level
     * 11 : Rising Edge
     *
     *   3                     2                   1
     *   1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0
     * */

    /* 1. SPI config */

    /* ICD.ICDICR[0] is SGI 0-15 */
    /* ICD.ICDICR[1] is PPI 15-31 */
    ICD.ICDICR[0+2] = 0x555d555f;		/* ID #32 - > #47 */
    ICD.ICDICR[1+2] = 0x555d5555;		/* ID #48 - > #63 */
    ICD.ICDICR[2+2] = 0x55555555;		/* ID #64 - > #79 */

    /* 2. SPI Prio ( 4 ID / reg ) */

    for (i = 8; i < NUM_INTERRUPTS / 4; i++)
    {
        ICD.ICDIPR[i] = 0x00000000;
    }


#if !defined(GIC_SECURE)
#error Set ICDISR to 1
#endif

    /* 3. SPI Select Target
     *
     * SGI/PPI:  0b01-CPU0  ,0b10 - CPU1
     * SPI    :  0b00-NoCPU, 0b01-CPU0, 0b10-CPU1, 0b11-CPU0andCPU1
     * */

    //  Direct to no core for the moment
    for(i=0x20; i<NUM_SPI/4;i++) {
        ICD.ICDIPTR[0] = 0x0;
    }


}


void Irq_SetPriority( CoreIDType cpu,  IrqType vector, uint8_t prio ) {

    /* NOTE: CPU HW prio is 8-bit, bit LSB is always 0 */

    /* 4 interrupts for each register */
    uint8_t shift = (vector % 4)*8;
    uint8_t reg = vector / 4;
    uint32_t mask = (0xffu<<shift);

    prio = osPrioToCpuPio(prio);

    /* + 3 here because the only the 5 most MSB bits are used in Secure view */
    ICD.ICDIPR[reg] = (( (prio<<(shift+3)) & mask ) | ( ICD.ICDIPR[reg] & ~mask ));

}


static void GIC_Init( void ) {
    GIC_DistrubutorInit();

    /* 1. Write pri_msk register */
    ICCI.ICCPMR = 0;	/*  A value of zero, the register reset value,
                            masks all interrupts to the associated processor. */

    /* 2. Enable */
    ICCI.ICCICR = 1;

    /* 3. binary point ...select gggg.ssss (yet, to determine)*/
    ICCI.ICCBPR = 3;

    ICCI.ICCPMR = 0xf8;		/* Mask none */

    /* Enable the distributor */
#if defined(GIC_SECURE)
    ICD.ICDDCR = 1;		/* 1=Secure, 2-Non-Secure*/
#else
    ICD.ICDDCR = 2;		/* 1=Secure, 2-Non-Secure*/
#endif
}



/**
 * Init GIC
 */
void Irq_Init( void ) {
    GIC_Init();
}


/**
 * GIC handler
 *
 * @param stack_p Ptr to the current stack.
 *
 * The stack holds C, NVGPR, VGPR and the EXC frame.
 *
 *
 */
#define MAX_WAIT_COUNT 1000

#define INT_SPURIOUS 			1023



uint16_t Irq_Stack[16][2] ;
uint16_t Irq_Index =  0;
#define I_MASK		0
#define I_VECTOR	1

void *Irq_Entry( void *stack_p )
{
    uint16_t vector;
    /* For SGI:
     * - Inactive->Pending
     * - Pending ->Active when ICCIAR is read.
     */

    /* Reading ICCIAR will make the interrupt go from Pending->Active
     * ICCHPIR will become the next pending interrupt or 1023 if none
     * */
    vector = ICCI.ICCIAR & 0x3ff;

    /* Set new mask */
    Irq_Stack[Irq_Index][I_MASK] = ICCI.ICCPMR;
    Irq_Stack[Irq_Index][I_VECTOR] = vector;
    Irq_Index++,

    ICCI.ICCPMR = ICCI.ICCRPR;

    if( vector ==  INT_SPURIOUS) {
        return stack_p; 	/* Nothing to do */
    }

    Os_Isr(stack_p,vector);

    return stack_p;
}

void Irq_EOI( int16_t vector ) {
    (void)vector;
    /* Ack interrupt */
    --Irq_Index;
    ICCI.ICCEOIR = Irq_Stack[Irq_Index][I_VECTOR];
    /* Set old mask */
    ICCI.ICCPMR = Irq_Stack[Irq_Index][I_MASK];
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
        Irq_SetPriority( core,  vector, priority );

        /* Forward to GIC, 1-bit */
        ICD.ICDISER[vector/32] = (1 << (vector % 32));

        /* Select Target CPU 8 bits vector.. IPTR[8] start with 32 */
        {
            uint8_t shift = (vector % 4)*8;
            uint8_t reg = vector / 4;
            uint32_t mask = (0xffu<<shift);
            uint8_t cpu = 1;

            /* Write target register */
            ICD.ICDIPTR[reg] = (( (cpu<<(shift)) & mask ) | ( ICD.ICDIPTR[reg] & ~mask ));
        }



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

    /* NOTE: TRGFILT is not right for all cases */
#if defined(GIC_SECURE)
    ICDSGIR_t val = { 	.B.TRGFILT = 2,
                        .B.CPU = 0,
                        .B.SATT = 0,	/* Secure */
                        .B.SBZ = 0,
                        .B.SGIINTID = vector };
#else
#error Non-secure not implemtened
#endif

    ICD.ICDSGIR.R = val.R;

    /* Now
     * ICC.ICDSGIR should be set to the vector
     * ICDICPR should reflect that the vector is pending
     *
     */

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


