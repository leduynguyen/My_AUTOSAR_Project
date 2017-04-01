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

/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */
/** @tagSettings DEFAULT_ARCHITECTURE=JACINTO5|JACINTO6 */

#ifndef PWM_INTERNAL_H_
#define PWM_INTERNAL_H_


typedef uint8 Pwm_Hw_ChannelType;
/**
 * Type that holds all global data for Gpt
 */
typedef struct {
    boolean initRun;
    const Pwm_ConfigType (*config)[PWM_ARC_LOG_UNIT_CNT];
    /* Maps the a physical channel id to configured channel index */
    Pwm_ChannelType channelMap[PWM_ARC_HW_UNIT_CNT];
    Pwm_Hw_ChannelType channelToHwChannel[PWM_ARC_LOG_UNIT_CNT];
    boolean Pwm_NotifEnable[PWM_ARC_LOG_UNIT_CNT];
    boolean Pwm_WakUpEnable[PWM_ARC_LOG_UNIT_CNT];
} Pwm_GlobalType;

/*lint -esym(9003,Pwm_Global) */
extern Pwm_GlobalType Pwm_Global;
extern uint32 Pwm_Clock;
/*lint -esym(9003,PwmConfigPtr) */
extern const Pwm_ConfigType *PwmConfigPtr;

static inline Pwm_ChannelType HwChannelToChannel(Pwm_Hw_ChannelType ch) {
    return Pwm_Global.channelMap[ch];
}
static inline Pwm_Hw_ChannelType ChannelToHwChannel(Pwm_ChannelType ch) {
    return Pwm_Global.channelToHwChannel[ch];
}

Std_ReturnType Pwm_Hw_Init(const Pwm_ConfigType* ConfigPtr);

#if (PWM_DE_INIT_API==STD_ON)
void Pwm_Hw_Deinit(const Pwm_ConfigType* ConfigPtr);
#endif

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
void Pwm_Hw_SetPeriodAndDuty( Pwm_ChannelType ChannelNumber,
        Pwm_PeriodType Period, uint16 DutyCycle, Pwm_OutputStateType Polarity);
#endif

#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
void Pwm_Hw_SetDutyCycle( Pwm_ChannelType ChannelNumber, uint16 DutyCycle, Pwm_OutputStateType Polarity);
#endif

#if ( PWM_SET_OUTPUT_TO_IDLE_API == STD_ON )
void Pwm_Hw_SetOutputToIdle(Pwm_ChannelType ChannelNumber, Pwm_OutputStateType IdleState);
#endif

#if (PWM_GET_OUTPUT_STATE_API == STD_ON)
Pwm_OutputStateType Pwm_Hw_GetOutputState(Pwm_ChannelType ChannelNumber);
#endif

#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
void Pwm_Hw_DisableNotification(Pwm_ChannelType ChannelNumber);
void Pwm_Hw_EnableNotification(Pwm_ChannelType ChannelNumber,
        Pwm_EdgeNotificationType Notification, Pwm_OutputStateType Polarity);
#endif

#endif /* PWM_INTERNAL_H_ */
