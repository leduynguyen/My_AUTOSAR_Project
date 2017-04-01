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
 * SCTM timer module. Timer 0,1 can be used as Timers and the rest as counters
 */

/* ----------------------------[includes]------------------------------------*/

#include "timer.h"
#include "Cpu.h"
#include "Mcu.h"

/* ----------------------------[private define]------------------------------*/
#define CACHE_SCTM_CTCNTL     0x55080400UL
#define CACHE_SCTM_CTDBGNUM   0x5508047cUL
#define CACHE_SCTM_CTGNBL     0x550804f0UL
#define CACHE_SCTM_CTGRST     0x550804f8UL

/*
(1) i = 0 to 1
(2) k = 0 to 7
(3) j = 0 to 5
*/
#define CACHE_SCTM_TINTVLR_i  0x55080440UL
#define CACHE_SCTM_CTCR_WT_i  0x55080500UL
#define CACHE_SCTM_CTCR_WOT_j 0x55080508UL
#define CACHE_SCTM_CTCNTR_k   0x55080580UL

#define CACHE_SCTM_DEFAULT_TIMER 7
#define CACHE_SCTM_NOF_TIMERS 8

/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/



static boolean initFlag[CACHE_SCTM_NOF_TIMERS] = {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE};
uint32_t Timer_Freq;
/**
 * Initialize the TB
 */
void Timer_InitIdx( uint8_t timerIdx ) {

    if (initFlag[timerIdx] == FALSE) {
        *(volatile uint32_t *)CACHE_SCTM_CTCNTL |= 0x1UL; /* Enable SCTM module */ /*lint !e923 HARDWARE ACCESS */

        *(volatile uint32_t *)CACHE_SCTM_CTGNBL = (1u << timerIdx);/* Enable indexed timer */ /*lint !e923 HARDWARE ACCESS */

        /* Get system clock*/
        Timer_Freq = Mcu_Arc_GetPeripheralClock(PERIPHERAL_CLOCK_SCTM);

        initFlag[timerIdx] = TRUE;
    }
}
void Timer_Init( void ) {
    Timer_InitIdx(CACHE_SCTM_DEFAULT_TIMER);
}

TimerTick Timer_GetTicksIdx( uint8_t timerIdx ){
    return *(volatile uint32_t *)(CACHE_SCTM_CTCNTR_k + ( 4u * timerIdx )); /*lint !e923 HARDWARE ACCESS */
}

TimerTick Timer_GetTicks( void ) {
    return Timer_GetTicksIdx(CACHE_SCTM_DEFAULT_TIMER);
}



