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
#include "IfxStm_reg.h"
#include "Mcu.h"

#if (SELECT_CORE == 0)
# define MODULE_STM MODULE_STM0
# define IRQ_SRC    IRQ_SRC_STM0SR0
#elif (SELECT_CORE == 1)
# define MODULE_STM MODULE_STM1
# define IRQ_SRC    IRQ_SRC_STM1SR0
#elif (SELECT_CORE == 2)
# define MODULE_STM MODULE_STM2
# define IRQ_SRC    IRQ_SRC_STM2SR0
#else
# error "Invalid SELECT_CORE"
#endif

static uint32 reloadValue;

extern uint32 Mcu_Arc_GetPeripheralClock(Mcu_Arc_PeriperalClock_t type);

void Os_SysTickArch( void ) {

    MODULE_STM.CMP[0].U = MODULE_STM.TIM0.U + reloadValue;
    OsTick();
}

/**
 * Init of free running timer.
 */
void Os_SysTickInit( void ) {

    /* Take STM0 and CMP[0] for sys tick */
    ISR_INSTALL_ISR2("OsTick",Os_SysTickArch,IRQ_SRC,128,0);
}

/**
 * Start the Sys Tick timer
 *
 * @param period_ticks How long the period in timer ticks should be.
 *
 */

void Os_SysTickStart2(uint32_t frequency) {
    Ifx_STM_ICR icr = MODULE_STM.ICR;

    reloadValue  = Mcu_Arc_GetPeripheralClock(CLOCK_STM)/frequency;

    MODULE_STM.CMP[0].U = MODULE_STM.TIM0.U + reloadValue;
    MODULE_STM.CMCON.B.MSIZE0 = 31;	/* Use 32 bits Start = 0*/
    MODULE_STM.CMCON.B.MSTART0 = 0;	/* Use only lower 32-bits */

    icr.B.CMP0OS = 0; 	/* STMIR0 */
    icr.B.CMP0EN = 1; 	/* Enable Interrupt */

    /* Stop when debugger is stopped...assumes the suspend signal is also
     * fixed at debugger init */
    MODULE_STM.OCS.U = 0x12000000UL;

    MODULE_STM.ICR = icr;
}
