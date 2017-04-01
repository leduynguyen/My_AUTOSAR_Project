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

#include "timer.h"
#include "Cpu.h"
#if !defined(CFG_SIMULATOR)
#include "Mcu.h"
#endif

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

uint32_t Timer_Freq;

/**
 * Initialize the TB
 */
void Timer_Init(void) {
    static boolean OnlyAllowedOnce = TRUE;

    if (OnlyAllowedOnce == TRUE) {
        uint32_t tmp;

        /* Clear TB */
        set_spr(SPR_TBU_W, 0);
        set_spr(SPR_TBL_W, 0);

        // Enable the TB
        tmp = get_spr(SPR_HID0);
        tmp |= HID0_TBEN;
        set_spr(SPR_HID0, tmp);

#if !defined(CFG_SIMULATOR)
        Timer_Freq = Mcu_Arc_GetSystemClock();
#else
        /* Run the simulator at 10Mhz (e.g. for T32 "vco.frequency 10Mhz" ) */
        Timer_Freq = 10000000uL;
#endif
        OnlyAllowedOnce = FALSE;
    }
}

TimerTick Timer_GetTicks(void) {
return get_spr(SPR_TBL_R);
}
