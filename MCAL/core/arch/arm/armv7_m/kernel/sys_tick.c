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
#include "irq_types.h"
#include "isr.h"
#include "arc.h"


/**
 * Init of free running timer.
 */
void Os_SysTickInit( void ) {
    ISR_INSTALL_ISR2("OsTick", OsTick, SysTick_IRQn, 6, 0);
}

/**
 * Start the Sys Tick timer
 *
 * @param period_ticks How long the period in timer ticks should be.
 *
 */

void Os_SysTickStart(TickType period_ticks) {

    /* Cortex-M3 have a 24-bit system timer that counts down
     * from the reload value to zero.
     */

	(void)SysTick_Config(period_ticks);

}
