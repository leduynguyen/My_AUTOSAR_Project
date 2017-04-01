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
//#include "zynq.h"
#include "Mcu.h"
#include "rh850_ostm.h"



#define TIMER_IRQ_ENABLE      4
#define TIMER_AUTO_RELOAD     2
#define TIMER_ENABLE          1

static uint32 reload = 0;

static void OsTick_rh850f1l( void ) {

    OSTM.OSTMnCMP += reload;
    OsTick();
}

/**
 * Init of free running timer.
 */
void Os_SysTickInit( void ) {
    ISR_INSTALL_ISR2("OsTick_rh850f1l",OsTick_rh850f1l,IRQ_INTOSTM0,6,0);
}


/**
 * Start the Sys Tick timer
 *
 * @param frequency The frequency of the Os Tick.
 *
 */
void Os_SysTickStart2(uint32_t frequency) {

    /*
     * Use OSTM0 for system tick.
     * PCLK  CPUCLK2
     */

    OSTM.OSTMnCTL = 2;	/* Mode=Interval,interrupt at start */
    OSTM.OSTMnEMU = 0;  /* STop timer when debugger stops */

    reload = Mcu_Arc_GetPeripheralClock(C_CPUCLK2)/(frequency-1);
    OSTM.OSTMnCMP = OSTM.OSTMnCNT + reload;

    OSTM.OSTMnTS = 1;	/* Start timer , OSTMnTS = 1*/

}
