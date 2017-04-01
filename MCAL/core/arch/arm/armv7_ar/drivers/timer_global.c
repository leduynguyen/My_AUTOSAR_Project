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
 *   Timer for most PPC chips (Not MPC560x)
 */

/* ----------------------------[includes]------------------------------------*/

/*lint -save -e9003 Misra 2012 8.9 Blockscope variables definitions neglected.
 * Static variable declaration in Function body violates the AUTOSAR memory mapping concept.*/

#include "timer.h"
//#include "Cpu.h"
#if !defined(CFG_SIMULATOR)
#include "Mcu.h"
#endif

#include "zynq.h"

/* ----------------------------[private define]------------------------------*/

/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

/* Set SFR registers of Adc properly.*/
typedef volatile struct GLOBAL_TIMER_reg Timer_HwRegType;
/*lint -e{923} cast from unsigned int to pointer MISRA 2004 11.1 11.3 2012 11.4 11.6
 * Integer to pointer casting is necessary to set SFR of Microcontroller. */
static Timer_HwRegType* const GLOBAL_TIMER_PTR =
        (Timer_HwRegType*) (ZYNQ_MPCORE_BASE + 0x200u);

uint32_t Timer_Freq;

/**
 * Initialize the TB
 */
void Timer_Init(void) {
    static boolean OnlyAllowedOnce = TRUE;

    if (OnlyAllowedOnce == TRUE) {
        /* Enable the timer */
        GLOBAL_TIMER_PTR->control = 0x1u;

        /* Calculate Timer_Freq */
        Timer_Freq = MCU_ARC_CLOCK_ARM_CPU_3X2X_FREQUENCY;
        OnlyAllowedOnce = FALSE;
    }
}

TimerTick Timer_GetTicks(void) {
    return GLOBAL_TIMER_PTR->counterLow;
}

uint64_t Timer_GetTicks64(void) {
    uint32_t low;
    uint32_t high;

    do {
        high = GLOBAL_TIMER_PTR->counterHigh;
        low = GLOBAL_TIMER_PTR->counterLow;
    } while (GLOBAL_TIMER_PTR->counterHigh != high);

    return ((((uint64_t) high) << 32u) + low);
}

