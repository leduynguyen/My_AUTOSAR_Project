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

#ifndef TIMER_RTI_TMS570_H_
#define TIMER_RTI_TMS570_H_

/**
 * @brief Timer_Rt1Init Initialize RTICLK 1 used by Gpt and Wdg.
 * It should be called from both the Gpt module and the Wdg module instead of them
 * initializing it. It will check so the module is not already initialized before
 * initializing, that way the timer will only be initialized once.
 */
void Timer_Rt1Init(void);

/**
 * @brief Timer_Rt1GetClock Timer_Rt1Init must be called before calling this function,
 * else the return value will not be valid.
 * @return The RTI1 clock frequency.
 */
uint32 Timer_Rt1GetClock(void);

/**
 * @brief Timer_Ticks2Us Converts from timer ticks to microseconds.
 * @param ticks The ticks from Timer_GetTicks.
 * @return Microseconds
 */
uint64 Timer_Ticks2Us(uint32 ticks);

#endif /* TIMER_RTI_TMS570_H_ */
