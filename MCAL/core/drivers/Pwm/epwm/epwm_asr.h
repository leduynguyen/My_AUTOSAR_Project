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

#ifndef EPWM_ASR_H_
#define EPWM_ASR_H_

/**
 * The purpose of the epwm_asr (ePWM Autosar) module
 * is to provide a wrapper around the ePWM module so that
 * it can easily be reused for different AUTOSAR PWM drivers.
 */

#include "epwm.h"
#include "Std_Types.h"
#include "epwm_asr.h"
#include "Platform_Types.h"
#include "Pwm.h"
#include "Pwm_ConfigTypes.h"

typedef enum {
    EPWM_FLAT = 0,
    EPWM_MODULATING
} ePWM_ChannelOutputStateType;

/**
 * Finds a prescaler that achieves the desired PWM frequency.
 * @param pwmClockHz The PWM clock frequency
 * @param pwmFreq The desired PWM frequency.
 * @param prescalerOut The prescaler that achieves the desired PWM frequency.
 * @return E_OK if a prescaler that works was found, else E_NOT_OK.
 */
Std_ReturnType ePWM_FindFittingPrescaler(uint32 pwmClockHz, uint32 pwmFreq, uint32 *prescalerOut);

/**
 * This API is needed to know if setting a duty cycle that is greater than 0
 * will result in a duty cycle of 0 anyway due to 0 period.
 * @param PwmHandle
 * @return The period.
 */
uint16 ePWM_GetPeriod(PWM_Handle PwmHandle);

/**
 * Initializes the given PWM channel according to the parameters.
 * @param PwmHandle
 * @param pwmClockHz
 * @param prescaler
 * @param pwmFreq
 * @param DutyCycle
 * @param Polarity
 * @return E_OK if the configuration parameters were valid, else E_NOT_OK.
 */
Std_ReturnType ePWM_InitChannel(PWM_Handle PwmHandle,
        uint32 pwmClockHz,
        uint32 prescaler,
        uint32 pwmFreq,
        uint16 DutyCycle,
        Pwm_OutputStateType Polarity);

/**
 * Sets the channel to idle according to IdleState.
 * @param PwmHandle
 * @param IdleState The idle state (high or low).
 */
void ePWM_SetChannelToIdle(PWM_Handle PwmHandle, Pwm_OutputStateType IdleState);

/**
 * Sets the duty cycle of the given PWM channel.
 * The EnableInterrupts parameter is needed since ePWM_SetChannelToIdle could
 * have been called which will disable interrupts even though notifications
 * are enabled (since there are no edges in idle there should be no interrupts but
 * the interrupts are generated on reached counter values not on actual
 * edges).
 * @param PwmHandle
 * @param DutyCycle DutyCycle 0x0000 (0%) to 0x8000 (100%).
 * @param Polarity Polarity High or low.
 * @param EnableInterrupts TRUE if interrupts should be enabled.
 */
void ePWM_SetDutyCycle(PWM_Handle PwmHandle, uint16 DutyCycle, Pwm_OutputStateType Polarity,
        boolean EnableInterrupts);

/**
 * Sets the period (in ticks) and the duty cycle of the given PWM channel.
 * @param PwmHandle
 * @param Period The desired period in ticks (not milliseconds!).
 * @param DutyCycle 0x0000 (0%) to 0x8000 (100%).
 * @param Polarity High or low.
 * @param EnableInterrupts TRUE if interrupts should be enabled.
 * @return E_OK if the request was accepted (period fits in the TBPRD register), else E_NOT_OK.
 */
Std_ReturnType ePWM_SetPeriodAndDuty(PWM_Handle PwmHandle, Pwm_PeriodType Period, uint16 DutyCycle,
        Pwm_OutputStateType Polarity, boolean EnableInterrupts);

/**
 * Clears the interrupt register from pending events.
 * @param PwmHandle
 */
void ePwm_ClearInterrupts(PWM_Handle PwmHandle);

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
/**
 * Disables interrupts for the given PWM channel.
 * @param PwmHandle
 */
#define EPWM_DISABLE_INTERRUPTS(PwmHandle)				PWM_disableInt(PwmHandle)

/**
 * Enables interrupts for the given PWM channel.
 * @param PwmHandle
 */
#define EPWM_ENABLE_INTERRUPTS(PwmHandle)				PWM_enableInt(PwmHandle)

/**
 * Sets up the desired notification interrupt. If notifications on
 * both edges are desired it is up to the implementer to call the
 * function ePwm_ToggleEdgeDetection from the interrupt to toggle
 * the edge detection setting. There is no hardware setting that detects
 * both rising and falling edges so it has to be handled from software.
 * @param PwmHandle
 * @param Notification
 * @param Polarity
 * @param ChannelOutputState Interrupts will always be set up but only enabled if
 * the duty cycle is bigger than 0% or less than 100%.
 */
void ePWM_EnableNotification(PWM_Handle PwmHandle, Pwm_EdgeNotificationType Notification,
        Pwm_OutputStateType Polarity, ePWM_ChannelOutputStateType ChannelOutputState);

/**
 * Toggles the edge detection from rising to falling edge
 * and vice versa.
 * @param PwmHandle
 */
void ePwm_ToggleEdgeDetection(PWM_Handle PwmHandle);
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) */

#endif /* EPWM_ASR_H_ */
