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

// MISRA 2004 11.3 and 2012 11.4 : Inhibit lint error 923 when addressing
// memory mapped registers defined as macros in header files.
//lint -elibmacro(923)
#include "Os.h"
#include "os_i.h"
#include "isr.h"
#include "irq.h"
#include "arc.h"
#include "irq_types.h"
#include "mpc55xx.h"
#include "Mcu.h"

/**
 * Init of free running timer.
 */
//extern void OsTick( void );
//extern OsTickType OsTickFreq;
#if defined(CFG_MPC560X)
ISR(Os_SysTick_MPC560x);
#endif

#if defined(CFG_MPC560X)
ISR(Os_SysTick_MPC560x) {
    /* Clear API interrupt */
    RTC.RTCS.B.APIF = 1;

    OsTick();
}
#endif

#if defined(CFG_MPC5604P) || defined(CFG_MPC5744P) || defined(CFG_MPC5777M) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
/*lint -e{957} OTHER */
ISR(Os_SysTick_MPC5xxx_PIT) {
    /* Clear interrupt. */
    PIT.CH[3].TFLG.B.TIF = 1;

    OsTick();
}
#endif

void Os_SysTickInit(void) {
#if defined(CFG_MPC5604P) || defined(CFG_MPC5744P) || defined(CFG_MPC5777M) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
    ISR_INSTALL_ISR2("OsTick",Os_SysTick_MPC5xxx_PIT,PIT_INT3,6,0);
#elif defined(CFG_MPC560X)
    ISR_INSTALL_ISR2("OsTick",Os_SysTick_MPC560x,API_INT,6,0);
#else
#if (OS_NUM_CORES > 1)
    if (OS_CORE_IS_ID_MASTER(GetCoreID())) {
        ISR_INSTALL_ISR2( "OsTick", OsTick, INTC_SSCIR0_CLR7, 6, OS_CORE_0_MAIN_APPLICATION);
    }
    else {
        ISR_INSTALL_ISR2( "OsTick_z0", OsTick, INTC_SSCIR0_CLR4, 6, OS_CORE_1_MAIN_APPLICATION);

    }
#else
    ISR_INSTALL_ISR2("OsTick", OsTick, INTC_SSCIR0_CLR7, 6, 0);
#endif
#endif
}

/**
 *
 *
 * @param period_ticks How long the period in timer ticks should be. The timer
 *                     on PowerPC often driver by the CPU clock or some platform clock.
 *
 */
void Os_SysTickStart(TickType period_ticks) {
#if defined(CFG_MPC5604P) || defined(CFG_MPC5744P) || defined(CFG_MPC5777M) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
    PIT.MCR.B.MDIS = 0;
    PIT.MCR.B.FRZ = 1;

    /* period_ticks = sys_freq/OsTickFreq; Ex: Timeout= 64000 sysclks x 1sec/64M sysclks = 1 ms */
    /*lint -e{931} OTHER required operation */
    PIT.CH[3].LDVAL.R = (uint32_t)(((uint64_t)period_ticks * Mcu_Arc_GetPeripheralClock(PERIPHERAL_CLOCK_PIT_3) ) / Mcu_Arc_GetSystemClock());

    // Make sure that no interrupt is pending.
    PIT.CH[3].TFLG.B.TIF = 1;
    // enable int
    PIT.CH[3].TCTRL.B.TIE = 1;
    // Enable timer
    PIT.CH[3].TCTRL.B.TEN = 1;

#elif defined(CFG_MPC560X)
    CGM.SXOSC_CTL.B.OSCON = 1;	// enable the osc for RTC

    RTC.RTCC.R= 0;// disable RTC counter
//	RTC.RTCC.B.CNTEN = 0;		// disable RTC counter
//	RTC.RTCC.B.APIEN = 0;		// disable API
    RTC.RTCS.B.RTCF = 1;// clear RTC interrupt flag
    RTC.RTCS.B.APIF = 1;// clear API interrupt flag
    RTC.RTCC.B.RTCIE = 0;// disable RTC interrupt
    RTC.RTCC.B.APIIE = 1;// enable API interrupt
    RTC.RTCC.B.FRZEN = 1;// enable freeze mode
    RTC.RTCC.B.CLKSEL = 2;// set 16MHz FIRC as input clock
    RTC.RTCC.B.DIV32EN = 1;// Divide by 32 enable
    // ignore period_ticks, and set API compare value
    RTC.RTCC.B.APIVAL = (uint32_t)(500000 / OsTickFreq);
    (void)period_ticks;

    RTC.RTCC.B.APIEN = 1;// start API
    RTC.RTCC.B.CNTEN = 1;// enable RTC counter
#else
    uint32 tmp;

#if defined(CFG_SIMULATOR)
    period_ticks = period_ticks / 90;	// empirical testing..
#endif

    /* Initialize the Decrementer */
    set_spr(SPR_DEC, period_ticks);
    set_spr(SPR_DECAR, period_ticks);

    /* Set autoreload & Enable notification */
    tmp = get_spr(SPR_TCR);
    tmp |= TCR_ARE | TCR_DIE;
    set_spr(SPR_TCR, tmp);

    // Enable the TB
    tmp = get_spr(SPR_HID0);
    tmp |= HID0_TBEN;
    set_spr(SPR_HID0, tmp);
#endif
}
