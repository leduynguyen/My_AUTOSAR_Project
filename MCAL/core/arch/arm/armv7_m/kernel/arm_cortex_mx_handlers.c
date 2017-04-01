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

/** @tagSettings DEFAULT_ARCHITECTURE=ARM_CM3 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#include "arc.h"
#include "irq_types.h"

/* define this to enable debug of hardfaults */
#define DEBUG_HARDFAULT		1

#if defined(DEBUG_HARDFAULT)
#define _NAKED __attribute__ ( ( naked ) )
#else
#define _NAKED
#endif

void NMI_Handler(void){
	Os_Arc_Panic((uint32)NonMaskableInt_IRQn, NULL);
}


#if defined(DEBUG_HARDFAULT)

/**
 * Function to extract stacked registers (that was stacked by the hardfault
 * handler)
 * @param stackPtr
 */
void regs( uint32_t *stackPtr )
{
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;
    uint32_t pc;
    uint32_t xpsr;
    uint32_t bfar;

    /* Registers as when the hardfault happend */
    r0 = stackPtr[ 0 ];
    r1 = stackPtr[ 1 ];
    r2 = stackPtr[ 2 ];
    r3 = stackPtr[ 3 ];

    r12 = stackPtr[ 4 ];
    lr = stackPtr[ 5 ];
    pc = stackPtr[ 6 ];
    xpsr = stackPtr[ 7 ];

#if defined (CFG_ARMV7_M)
    if( SCB->CFSR & SCB_CFSR_INVPC ) {
        /* INVPC */
        while( 1 ) {}
    }

    if( SCB->CFSR & SCB_CFSR_INVSTATE ) {
        /* INVSTATE
         *
         * This is usually that the EPSR.T = 0 and can depend on a
         * corrupt stack.
         *
         * Checklist:
         * - Does PC seem sane?
         * - If PC does not seem sane you should be able to figure the last call
         *   by checking LR.
         * - If the xpsr.T-bit is not set, e.g. NOT 0x01000000, you have a stack error.
         *
         * Example: Call with bit[0] = 0
         * 	void (*fPtr)(void );
         *  fPtr = 0x08000000;
         *  fPtr();
         *
         *  This will give you:
         *    pc   = 0x8000_0000
         *    xpsr = 0x0000_0000
         *
         * In this case we can see that the T-bit is not set and pc will give you
         * the address. (using address 0x0800_0001 will NOT give you hardfault)
         * */
        while( 1 ) {}
    }

    if( SCB->CFSR & SCB_CFSR_BFARVALID ) {

    	/* Faulting address */
    	bfar = SCB->BFAR;
    	(void)bfar;

    	while( 1 ) {}
    }



#endif /* CFG_STM32 */

    (void)r0;
    (void)r1;
    (void)r2;
    (void)r3;
    (void)r12;
    (void)pc;
    (void)xpsr;
    (void)lr;

    while(1) {}
}
#endif

#if defined(CFG_T1_ENABLE) && !defined(CFG_T1_DISABLE_FLEX)

void T1_AppHardFaultHandler(void)
{
#if defined(DEBUG_HARDFAULT)
  /* Use of r0,r1,.. OK since it's on the stack */
    __asm volatile (" mrs r0, msp");			/* we only have MSP, so grab it */
    __asm volatile (" ldr r1, handler");		/* Call the C-function */
    __asm volatile (" bx r1");
    __asm volatile (" handler: .word regs");
#else
    Os_Arc_Panic(HardFault_IRQn, SCB);
#endif
}

#else

_NAKED void HardFault_Handler(void)
{
#if defined(DEBUG_HARDFAULT)

	/* We are always on the MSP stack here, we need to figure out
	 * on what stack we were.
	 */
	__asm volatile (" cpsid i");            /* Disable interrupts */
	__asm volatile (" tst lr, #4");         /* grab SPSEL */
											/* SPSEL = 1  thread mode  */
											/* SPSEL = 0  handler mode */
	__asm volatile (" ite eq");             /* if SPEL = 0   */
	__asm volatile (" mrseq r0, msp");      /*      r0 = msp */
	__asm volatile (" mrsne r0, psp");      /* else r0 = psp */
	__asm volatile (" ldr r1, handler");    /* call regs("stack") */
	__asm volatile (" bx r1");
	__asm volatile (" handler: .word regs");

#else
	Os_Arc_Panic(HardFault_IRQn, SCB);
#endif
}

#endif /* defined(CFG_T1_ENABLE) */

void MemManage_Handler(void){
	Os_Arc_Panic((uint32)MemoryManagement_IRQn, SCB);
}
void BusFault_Handler(void){
	Os_Arc_Panic((uint32)BusFault_IRQn, SCB);
}
void UsageFault_Handler(void){
	Os_Arc_Panic((uint32)UsageFault_IRQn, SCB);
}

