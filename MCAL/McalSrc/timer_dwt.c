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
 * DESCRPTION:
 *   Timer Cortex M3 (the only Free Running Timer I could find)
 */

/** @tagSettings DEFAULT_ARCHITECTURE=STM32 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/* ----------------------------[includes]------------------------------------*/

#include "Os.h"
#include "timer.h"
#include "Cpu.h"
#include "Mcu.h"
#include "io.h"

/* ----------------------------[private define]------------------------------*/

#define DWT_CYCCNT 		0xE0001004
#define DWT_CONTROL		0xE0001000
#define SCB_DEMCR		0xE000EDFC

/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

uint32_t Timer_Freq;

/**
 * Initialize
 */
void Timer_Init(void) {
    static boolean OnlyAllowedOnce = TRUE;

    if (OnlyAllowedOnce == TRUE) {
        READWRITE32(SCB_DEMCR, 0, 0x01000000);
        WRITE32(DWT_CYCCNT, 0);
        READWRITE32(DWT_CONTROL, 0, 1);

        Timer_Freq = Mcu_Arc_GetSystemClock();
        OnlyAllowedOnce = FALSE;
    }
}

TimerTick Timer_GetTicks(void) {
    return READ32(DWT_CYCCNT);
}
