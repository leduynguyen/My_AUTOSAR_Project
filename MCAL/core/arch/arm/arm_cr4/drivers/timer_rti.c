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
#include "core_cr4.h"

/* ----------------------------[private define]------------------------------*/

#define RTCC_CNTEN				(1<<(31-0))
#define RTCC_FRZEN				(1<<(31-2))
#define RTCC_CLKSEL_SXOSC		(0<<(31-19))
#define RTCC_CLKSEL_SIRC		(1<<(31-19))
#define RTCC_CLKSEL_FIRC		(2<<(31-19))
#define RTCC_CLKSEL_FXOSC		(3<<(31-19))

#define RTCC_DIV32EN			(1<<(21-31))

#define RTICLK_GCTRL_CNT1EN		(1u << 1u)

#define RTICLK1_PRESCALER		10u

#define TIMER_US2TICKS(_us, _timer_freq)	(((_us) * (_timer_freq/1000))/1000uL)

/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

uint32 Timer_Freq;

static uint32 Timer_Rti1ClkPrescaler = 1;

/**
 * Initialize the TB
 */
void Timer_Init(void) {
    static boolean OnlyAllowedOnce = TRUE;

    if (OnlyAllowedOnce == TRUE) {
        /* The RTI module uses RTICLK that uses the same ratio as VCLK_sys, that is
         * VCLK_sys frequency is HCLK divided by 2 */
        rtiREG1->GCTRL |= 0x1; /* Use the same timer as OS */

        /* Prescaler from sys_tick is 10 */
        Timer_Freq = Mcu_Arc_GetPeripheralClock(PERIPHERAL_CLOCK_RTICLK) / 10;
        OnlyAllowedOnce = FALSE;
    }
}

uint32_t Timer_GetTicks(void) {
    return rtiREG1->CNT[0].FRCx;
}

void Timer_Rt1Init(void) {

    /* If the timer is already initialized, do nothing. */
    if ((rtiREG1->GCTRL & RTICLK_GCTRL_CNT1EN) != RTICLK_GCTRL_CNT1EN) {

        /* Counter must be stopped and then re-started to preset. */
        rtiREG1->CNT[1].FRCx = 0u;

        /* Configure the up-counter compare to correspond to a fixed number
         * So that the FRC will increment every millisecond	 */
        uint32 rticlk = Mcu_Arc_GetPeripheralClock(PERIPHERAL_CLOCK_RTICLK);

        /* To turn it into millisecond ticks. */
        Timer_Rti1ClkPrescaler = TIMER_US2TICKS(1000, rticlk);
        /* Prescale with the same value as sys_tick.
         * See #define RTICLK_PRESCALER 10 in sys_tick.c. */
        Timer_Rti1ClkPrescaler /= RTICLK1_PRESCALER;

        rtiREG1->CNT[1].CPUCx = Timer_Rti1ClkPrescaler - 1;

        /* Compare unit 1, 2 and 3 is used by Counter 1,
         * set them in the module that use them, not here. */

        /* Start Counter 1 */
        rtiREG1->GCTRL |= RTICLK_GCTRL_CNT1EN;
    }
}

uint32 Timer_Rt1GetClock(void) {

    uint32 Rt1ClockOut = 0;

    if ((rtiREG1->GCTRL & RTICLK_GCTRL_CNT1EN) == RTICLK_GCTRL_CNT1EN) {

        Rt1ClockOut = Mcu_Arc_GetPeripheralClock(PERIPHERAL_CLOCK_RTICLK)
                / Timer_Rti1ClkPrescaler;
    }

    return Rt1ClockOut;
}

uint64 Timer_Ticks2Us(uint32 ticks) {

    /* Instead of dividing Timer_Freq with 1000000 which could result in an error
     * (7.5 million divided by 1 million is 7 and not 7.5), divide by 100000
     * and multiply ticks with 10. */

    uint64 timer = Timer_Freq / 100000;

    uint64 ticks10 = ((uint64) ticks) * 10;

    return ticks10 / timer;
}
