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

#include "Os.h"
#include "os_i.h"
#include "isr.h"
#include "arc.h"
#include "regs.h"
#include "Mcu.h"

void Os_SysTickInit( void ) {
    ISR_INSTALL_ISR2("OsTick",OsTick,IRQ_TYPE_MCCNT_UNDERFLOW,6,0);
}

/**
 * @param period_ticks How long the period in timer ticks should be. The timer
 *                     on PowerPC often driver by the CPU clock or some platform clock.
 *
 */
void Os_SysTickStart(uint32_t period_ticks) {
    // Set timer 0 as output compare. Timer 0 is reserved for the OS.

    // TEN, timer enable
    // TSFRZ, stop in freeze mode (easier debugging)
    TSCR1 = TEN | TSFRZ;

    ICSYS = 0;

    // Modulus counter
    // MCZI, enable interrupt, MCEN enable modulus counter
    // Prescaler 4
    MCCTL =  MCZI | MCEN | MCPRE_VAL_4;

    // Set auto-reload
    MCCTL |= MODMC;

    // time = (count * prescaler)/(bus frequency)
    MCCNT = period_ticks / 8;
}
