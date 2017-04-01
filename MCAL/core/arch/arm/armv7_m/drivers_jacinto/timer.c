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

#include "timer.h"
#include "Cpu.h"
#include "Mcu.h"

#if defined(CFG_JAC6)
#define TIM1_BASE                   0x4AE18000U
#define TIM2_BASE                   0x48032000U
#define TIM3_BASE                   0x48034000U
#define TIM4_BASE                   0x48036000U
#define TIM5_BASE                   0x48820000U
#define TIM6_BASE                   0x48822000U
#define TIM7_BASE                   0x48824000U
#define TIM8_BASE                   0x48826000U
#define TIM9_BASE                   0x4803E000U
#define TIM10_BASE                  0x48086000U
#define TIM11_BASE                  0x48088000U
#define TIM12_BASE                  0x4AE20000U
#define TIM13_BASE                  0x48828000U
#define TIM14_BASE                  0x4882A000U
#define TIM15_BASE                  0x4882C000U
#define TIM16_BASE                  0x4882E000U
#else
#define TIM1_BASE                   0x4802E000U
#define TIM2_BASE                   0x48040000U
#define TIM3_BASE                   0x48042000U
#define TIM4_BASE                   0x48044000U
#define TIM5_BASE                   0x48046000U
#define TIM6_BASE                   0x48048000U
#define TIM7_BASE                   0x4804a000U
#define TIM8_BASE                   0x481C1000U
#endif

#define TIM_BASE (TIM3_BASE + L3_OFFSET)

/* ----------------------------[private define]------------------------------*/
#define TIOCP_CFG (TIM_BASE + 0x10u) /*TIMER config register adress*/
#define TCLR (TIM_BASE + 0x38u) /*Timer TCLR reg*/
#define TCRR (TIM_BASE + 0x3Cu) /*Timer counter reg*/


#define SW_RESET_BIT 0x00001U /*SW reset bit*/
#define ST 0x00001U /*Start timer bit*/
#define GPT_COUNTER_RST_VAL	0x00000000U /*reset value*/



/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/



volatile uint32_t* timer3TIOCP_CFGPtr = (volatile uint32_t*)TIOCP_CFG;
volatile uint32_t* timer3TCLRPtr = (volatile uint32_t*)TCLR;
volatile uint32_t* timer3TCRRPtr = (volatile uint32_t*)TCRR;
static boolean initFlag = FALSE;
uint32_t Timer_Freq;
/**
 * Initialize the TB
 */
void Timer_Init( void ) {

    if (!initFlag) {
        /*Timer default to using system clock*/

        uint32_t TIOCP_CFGsnapshot; /*Snapshot placeholder*/

        *timer3TIOCP_CFGPtr |= SW_RESET_BIT; /*Toggle reset bit*/
        TIOCP_CFGsnapshot = *timer3TIOCP_CFGPtr; /*read snapshot of TIOCP_CFG reg, timer 3*/

        while (TIOCP_CFGsnapshot & SW_RESET_BIT) /*Wait for reset bit to turn 0*/
            TIOCP_CFGsnapshot = *timer3TIOCP_CFGPtr; /*read snapshot again*/

        *timer3TCRRPtr = GPT_COUNTER_RST_VAL; /*reset counter*/
        *timer3TCLRPtr = ST; /*Start timer*/

        /* Get system clock*/
        Timer_Freq = Mcu_Arc_GetPeripheralClock(PERIPHERAL_CLOCK_GPT);
        initFlag = TRUE;
    }
}

uint32_t Timer_GetTicks( void ) {
    return *timer3TCRRPtr;
}

void Reset_Timer_Count() {
    *timer3TCRRPtr = GPT_COUNTER_RST_VAL; /*reset counter*/
}


