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
/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/


/* ----------------------------[includes]------------------------------------*/

#include "os_i.h"
#include "irq.h"
#include "irq_types.h"
#include "mpc55xx.h"
#include "debug.h"
#include "isr.h"
#include "Ramlog.h"
#include <stdint.h>

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
typedef void (*f_t)( uint32_t *);

/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
extern void exception_tbl(void);

/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

void Irq_Init( void ) {
    /********************************************************************************
     * NOTE
     *
     * This function will be called before BSS and DATA are initialized.
     * Ensure that you do not access any global or static variables before
     * BSS and DATA is initialized
     ********************************************************************************/
      // Check alignment for the exception table
#if defined(CFG_MPC5643L) || defined(CFG_MPC5645S) || defined(CFG_SPC56XL70)
    /* IVPR + IVORx offset registers, exception table is max 0x200  */
    ASSERT((((uint32)exception_tbl + 0x200 - 1) & ~(0x200 -1)) == (uint32)exception_tbl );
#else
      ASSERT(((uint32)exception_tbl & 0xfff)==0);
#endif

      set_spr(SPR_IVPR,(uint32)exception_tbl);

  if (OS_CORE_IS_ID_MASTER(GetCoreID())) {
      // IMPROVEMENT: The 5516 simulator still thinks it's a 5554 so setup the rest
#if (defined(CFG_SIMULATOR) && defined(CFG_MPC5516)) || defined(CFG_MPC5567) || defined(CFG_MPC5554)  || defined(CFG_MPC5668) || defined(CFG_MPC563XM) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC5645S) || defined(CFG_MPC5644A)
        set_spr(SPR_IVOR0,((uint32_t)&exception_tbl+0x0) );
        set_spr(SPR_IVOR1,((uint32_t)&exception_tbl+0x10) );
        set_spr(SPR_IVOR2,((uint32_t)&exception_tbl+0x20) );
        set_spr(SPR_IVOR3,((uint32_t)&exception_tbl+0x30) );
        set_spr(SPR_IVOR4,((uint32_t)&exception_tbl+0x40) );
        set_spr(SPR_IVOR5,((uint32_t)&exception_tbl+0x50) );
        set_spr(SPR_IVOR6,((uint32_t)&exception_tbl+0x60) );
        set_spr(SPR_IVOR7,((uint32_t)&exception_tbl+0x70) );
        set_spr(SPR_IVOR8,((uint32_t)&exception_tbl+0x80) );
        set_spr(SPR_IVOR9,((uint32_t)&exception_tbl+0x90) );
        set_spr(SPR_IVOR10,((uint32_t)&exception_tbl+0xa0) );
        set_spr(SPR_IVOR11,((uint32_t)&exception_tbl+0xb0) );
        set_spr(SPR_IVOR12,((uint32_t)&exception_tbl+0xc0) );
        set_spr(SPR_IVOR13,((uint32_t)&exception_tbl+0xd0) );
        set_spr(SPR_IVOR14,((uint32_t)&exception_tbl+0xe0) );
        set_spr(SPR_IVOR15,((uint32_t)&exception_tbl+0xf0) );
#if defined(CFG_SPE) || defined(CFG_EFPU)
        // SPE exceptions
        set_spr(SPR_IVOR32,((uint32_t)&exception_tbl+0x100) );
        set_spr(SPR_IVOR33,((uint32_t)&exception_tbl+0x110) );
        set_spr(SPR_IVOR34,((uint32_t)&exception_tbl+0x120) );
#endif
#endif

      //
      // Setup INTC
      //
      // according to manual
      //
      // 1. configure VTES_PRC0,VTES_PRC1,HVEN_PRC0 and HVEN_PRC1 in INTC_MCR
      // 2. configure VTBA_PRCx in INTC_IACKR_PRCx
      // 3. raise the PRIx fields and set the PRC_SELx fields to the desired processor in INTC_PSRx_x
      // 4. set the enable bits or clear the mask bits for the peripheral interrupt requests
      // 5. lower PRI in INTC_CPR_PRCx to zero
      // 6. enable processor(s) recognition of interrupts

    #if defined(CFG_MPC5516) || defined(CFG_MPC5668)
      INTC.MCR.B.HVEN_PRC0 = 0; // Soft vector mode
      INTC.MCR.B.VTES_PRC0 = 0; // 4 byte offset between entries
    #elif defined(CFG_MPC5554) || defined(CFG_MPC5567) || defined(CFG_MPC560X) || defined(CFG_MPC563XM) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC5645S) || defined(CFG_MPC5644A)
      INTC.MCR.B.HVEN = 0; // Soft vector mode
      INTC.MCR.B.VTES = 0; // 4 byte offset between entries
    #elif defined(CFG_MPC5777M) || defined(CFG_MPC5744P) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C) ||defined(CFG_MPC5746C)
      // Soft vector mode
      // 4 byte offset between entries
      INTC.MCR.R = 0;
    #endif
	  // Pop the FIFO queue
	  for (int i = 0; i < 15; i++)
	  {
	#if defined(CFG_MPC5516) || defined(CFG_MPC5668)
	    INTC.EOIR_PRC0.R = 0;
	#elif defined(CFG_MPC5554) || defined(CFG_MPC5567) || defined(CFG_MPC560X) || defined(CFG_MPC563XM) || defined(CFG_MPC5643L) ||defined(CFG_SPC56XL70) || defined(CFG_MPC5645S) || defined(CFG_MPC5644A)
	    INTC.EOIR.R = 0;
	#elif defined(CFG_MPC5744P) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C) ||defined(CFG_MPC5746C)
	    INTC.EOIR[0].R = 0;
    #elif defined(CFG_MPC5777M)
        INTC.MPC5777M_INTC_REG_EOIR.R = 0;
    #endif
	  }

      // Accept interrupts
    #if defined(CFG_MPC5516) || defined(CFG_MPC5668)
      INTC.CPR_PRC0.B.PRI = 0;
    #elif defined(CFG_MPC5554) || defined(CFG_MPC5567) || defined(CFG_MPC560X) || defined(CFG_MPC563XM) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC5645S) || defined(CFG_MPC5644A)
      INTC.CPR.B.PRI = 0;
    #elif defined(CFG_MPC5744P) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C) ||defined(CFG_MPC5746C)
      INTC.CPR[0].B.PRI = 0;
    #elif defined(CFG_MPC5777M)
      INTC.CPR[MPC5777M_ACTUAL_CORE_ID_MASTER].B.PRI = 0;
    #endif
    } else { // if slave core (z0)
    // Init Z0
    #if defined(CFG_MPC5516)
      INTC.MCR.B.HVEN_PRC1 = 0; // Soft vector mode
      INTC.MCR.B.VTES_PRC1 = 0; // 4 byte offset between entries
      for (int i = 0; i < 15; i++)
      {
        INTC.EOIR_PRC1.R = 0;
      }
      INTC.EOIR_PRC1.R = 0;
      INTC.CPR_PRC1.B.PRI = 0;
    #endif
    }
}

void Irq_EOI( int16_t vector ) {
    (void)vector;
#if defined(CFG_MPC5516) || defined(CFG_MPC5668)
    volatile struct INTC_tag *intc = &INTC;
    if (OS_CORE_IS_ID_MASTER(GetCoreID())) {
        intc->EOIR_PRC0.R = 0;
    } else {
        intc->EOIR_PRC1.R = 0;
    }
#elif defined(CFG_MPC5554)||defined(CFG_MPC5567) || defined(CFG_MPC560X) || defined(CFG_MPC563XM) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC5645S) || defined(CFG_MPC5644A)

    volatile struct INTC_tag *intc = &INTC;
    intc->EOIR.R = 0;
#elif defined(CFG_MPC5744P) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C) ||defined(CFG_MPC5746C)
    INTC.EOIR[GetCoreID()].R = 0;
#elif defined(CFG_MPC5777M)
    INTC.MPC5777M_INTC_REG_EOIR.R = 0;
#else
#error No CPU defined
#endif
}

static inline uint8_t osPrioToCpuPio( uint8_t prio ) {
    ASSERT(prio<32);
    ASSERT(prio>1);
    return prio>>1;		// Os have 32 -> 16
}

void Irq_SetPriority( CoreIDType coreId,  IrqType vector, uint8_t prio ) {
#if defined(CFG_MPC5516) || defined(CFG_MPC5668)
    if (OS_CORE_IS_ID_MASTER(coreId))
        INTC.PSR[vector].B.PRC_SEL = 0;
    else
        INTC.PSR[vector].B.PRC_SEL = 3;
#elif defined(CFG_MPC5744P) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C) ||defined(CFG_MPC5746C)
    INTC.PSR[vector].B.PRC_SEL = 1 << (3 - coreId);
#elif defined(CFG_MPC5777M)
    (void)coreId;
    /* No multicore support, interrupts on master core only */
#if (MPC5777M_ACTUAL_CORE_ID_MASTER > 3)
#error MPC5777M_ACTUAL_CORE_ID_MASTER invalid
#endif
    INTC.PSR[vector].B.PRC_SEL = (8>>MPC5777M_ACTUAL_CORE_ID_MASTER);
#else
    (void)coreId;
#endif
    INTC.PSR[vector].B.PRI = (vuint8_t)prio;
}




void Irq_EnableVector( int16_t vector, uint8_t priority, int core ) {

    if (vector < (int16_t)INTC_NUMBER_OF_INTERRUPTS) {
        Irq_SetPriority((CoreIDType)core, (IrqType)(vector + IRQ_INTERRUPT_OFFSET), osPrioToCpuPio(priority));
    } else {
        /* Invalid vector! */
        ASSERT(0);
    }
}


/**
 * Generates a soft interrupt
 * @param vector
 */
void Irq_GenerateSoftInt( IrqType vector ) {
    ASSERT( vector <= INTC_SSCIR0_CLR7 );
    INTC.SSCIR[vector].B.SET = 1;
    isync();
}

/**
 * Get the current priority from the interrupt controller.
 * @param cpu
 * @return
 */
uint8_t Irq_GetCurrentPriority( Cpu_t cpu) {

    uint8_t prio = 0;

#if defined(CFG_MPC5516)
    if( cpu == CPU_Z1 ) {
        prio = (uint8_t)INTC.CPR_PRC0.B.PRI;
    } else if ( cpu == CPU_Z0 ) {
        prio = (uint8_t)INTC.CPR_PRC1.B.PRI;
     }
#elif defined(CFG_MPC5668)
    if( cpu == CPU_CORE0 ) {
        prio = (uint8_t)INTC.CPR_PRC0.B.PRI;
    } else if ( cpu == CPU_CORE1 ) {
        prio = (uint8_t)INTC.CPR_PRC1.B.PRI;
     }
#elif defined(CFG_MPC5554)||defined(CFG_MPC5567) || defined(CFG_MPC560X) || defined(CFG_MPC563XM) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC5645S) || defined(CFG_MPC5644A)
    (void)cpu;
    prio = (uint8_t)INTC.CPR.B.PRI;
#elif defined(CFG_MPC5777M) || defined(CFG_MPC5744P) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C) ||defined(CFG_MPC5746C)
    prio = (uint8_t)INTC.CPR[cpu].B.PRI;
#else
#error No CPU defined
#endif

    return prio;
}


