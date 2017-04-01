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
 *  Re-uses the RTI free running timer setup by the OS
 */


/* ----------------------------[includes]------------------------------------*/
#include "Cpu.h"
#include "timer.h"
#include "Mcu.h"
#include "IfxStm_reg.h"

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
void Timer_Init( void ) {
    Timer_Freq = 100000000uL;
}

uint32_t Timer_GetTicks( void ) {
    return MODULE_STM0.TIM0.U;
}

uint64_t Timer_GetTicks64( void ) {
    uint64_t capture;
    Irq_Disable(); /* Disable IRQ since CAP is saved for our read of TIM0 */
    capture = MODULE_STM0.TIM0.U;
    capture |= (uint64_t)MODULE_STM0.CAP.U << 32;
    Irq_Enable();
    return capture;
}
