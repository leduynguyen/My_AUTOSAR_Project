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
 *  Free-running MPC560x series of processors.
 */

/*lint -e923 Cast in Freescale header file */

/* ----------------------------[includes]------------------------------------*/

#include "Os.h"
#include "timer.h"
#include "Cpu.h"
#include "Mcu.h"
#include "mpc55xx.h"

/* ----------------------------[private define]------------------------------*/

#define RTCC_CNTEN				(1uL<<(31u))
#define RTCC_FRZEN				(1uL<<(31u-2u))
#define RTCC_CLKSEL_SXOSC		(0uL<<(31u-19u))
#define RTCC_CLKSEL_SIRC		(1uL<<(31u-19u))
#define RTCC_CLKSEL_FIRC		(2uL<<(31u-19u))
#define RTCC_CLKSEL_FXOSC		(3uL<<(31u-19u))

#define RTCC_DIV32EN			(1uL<<(21u-31u))
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

/*lint -esym(9003, Timer_Freq) Performance, used in header file */
uint32_t Timer_Freq;

/**
 * Initialize the RTC
 */
void Timer_Init(void) {
    static boolean OnlyAllowedOnce = TRUE;

    if (OnlyAllowedOnce == TRUE) {
        CGM.SXOSC_CTL.B.OSCON = 1u;	// enable the osc for RTC

        RTC.RTCC.R = 0u;
        /* FIRC=16Mhz */
        RTC.RTCC.R = RTCC_CNTEN | RTCC_FRZEN | RTCC_CLKSEL_FIRC;
        Timer_Freq = 16000000u;
        OnlyAllowedOnce = FALSE;
    }
}

TimerTick Timer_GetTicks(void) {
    return (TimerTick) RTC.RTCCNT.R;
}

