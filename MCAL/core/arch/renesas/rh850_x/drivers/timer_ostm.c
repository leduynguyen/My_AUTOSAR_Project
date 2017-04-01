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
#include "Arc_Types.h"
//#include "Cpu.h"
#if !defined(CFG_SIMULATOR)
#include "Mcu.h"
#endif

#include "rh850_ostm.h"

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

#if defined(CFG_RH850F1H)
        struct OSTM_reg *tPtr = &OSTMp[1];

        tPtr->OSTMnCTL = 2; /* Free running */
        tPtr->OSTMnEMU = 0; /* STop timer when debugger stops */

        tPtr->OSTMnCMP = tPtr->OSTMnCNT;

        tPtr->OSTMnTS = 1; /* Start timer , OSTMnTS = 1*/
#endif
        /* Calculate Timer_Freq */
        Timer_Freq = Mcu_Arc_GetPeripheralClock(C_CPUCLK2);

        OnlyAllowedOnce = FALSE;
    }

    /* RH8501FL only have one timer instance of OSTM and it's used by the OS */
}

uint32_t Timer_GetTicks(void) {
#if defined(CFG_RH850F1H)
    struct OSTM_reg *tPtr = &OSTMp[1];
#else
    struct OSTM_reg *tPtr = &OSTMp[0];
#endif
    return tPtr->OSTMnCNT;
}

uint64_t Timer_GetTicks64(void) {
    return 0;
}
