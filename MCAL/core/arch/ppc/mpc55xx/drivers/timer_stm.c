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
 *  Free-running timer for MPC5xxx devices.
 */

/*lint -e923 Cast in Freescale header file */

/* ----------------------------[includes]------------------------------------*/

#include "Os.h"
#include "timer.h"
#include "Cpu.h"
#include "Mcu.h"
#include "mpc55xx.h"

/* ----------------------------[private define]------------------------------*/

#define STM_CNTEN				(1uL)
#define STM_FRZ					(1uL<<1u)
#define STM_CPS(_x)				((_x)<<8u)


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
void Timer_Init( void ) {
    static boolean OnlyAllowedOnce = TRUE;

    if (OnlyAllowedOnce == TRUE) {
        /* Initialize timer */
        STM_0.CR.R = 0u;
        /*lint -e{9027, 9053, 9027, 845} HARDWARE_ACCESS */
        STM_0.CR.R = STM_CNTEN | STM_FRZ | STM_CPS(0);
        Timer_Freq = Mcu_Arc_GetPeripheralClock(PERIPHERAL_CLOCK_STM_0);
        OnlyAllowedOnce = FALSE;
    }
}

TimerTick Timer_GetTicks( void ) {
    return (TimerTick)STM_0.CNT.R;
}

