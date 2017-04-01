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

/*
 * DESCRIPTION:
 *  Implements the ARM CPU private timer on at least Cortex_A9-mpcore
 */



#include "Os.h"
#include "os_i.h"
#include "irq_types.h"
#include "isr.h"
#include "arc.h"
#include "zynq.h"
#include "Mcu.h"


#define TIMER_IRQ_ENABLE      4
#define TIMER_AUTO_RELOAD     2
#define TIMER_ENABLE          1

/**
 * Init of free running timer.
 */
void Os_SysTickInit( void ) {
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
    ISR_INSTALL_ISR2("OsTick",OsTick,IRQ_CPU_PRIVATE_TIMER,6,0);
#endif
}


/**
 * Start the Sys Tick timer
 *
 * @param frequency The frequency of the Os Tick.
 *
 */
void Os_SysTickStart2(uint32_t frequency) {

    /*
     *
     *	             (PRESCALER_value+1) x (Load_value+1)
     * interval =  ---------------------------------------
     *	                  PERIPHCLK
     *
     *
     * From Table 25-1: in TRM it seems as we are clocked by
     * CPU_3x2x. That is about 333Mhz... on a 32bit timer
     * -> 12 seconds, so we should be find without a prescaler.
     */

    /* The input period_ticks is a terrible unit and implementation.
     * It's the ratio between the CPU clock / OsTick Freq.
     */

    uint32_t pClock = MCU_ARC_CLOCK_ARM_CPU_3X2X_FREQUENCY; // Mcu_Arc_GetPeripheralClock();

    /* Load_Value = ((interval * PERIPHCLK) / 1 ) - 1 */

    PRIVATE_TIMER.load = (pClock / frequency -1);
    PRIVATE_TIMER.counter = PRIVATE_TIMER.load;
    PRIVATE_TIMER.control = TIMER_IRQ_ENABLE | TIMER_AUTO_RELOAD | TIMER_ENABLE;

}
