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

#ifndef PWM_CONFIGTYPES_H_
#define PWM_CONFIGTYPES_H_
typedef uint16 Pwm_PeriodType;

typedef enum {
  PWM_CHANNEL_1 = 0,
  PWM_CHANNEL_2,
  PWM_CHANNEL_3,
  PWM_CHANNEL_4,
  PWM_CHANNEL_5,
  PWM_CHANNEL_6,
  PWM_CHANNEL_7,
  PWM_TOTAL_NOF_CHANNELS,
} Pwm_ChannelType;

typedef enum {
    PWM_CHANNEL_PRESCALER_1=0,
    PWM_CHANNEL_PRESCALER_2,
    PWM_CHANNEL_PRESCALER_3,
    PWM_CHANNEL_PRESCALER_4,
} Pwm_ChannelPrescalerType;
//#define DUTY_AND_PERIOD(_duty,_period) .duty = (_duty*_period)>>15, .period = _period
//#define CUSTOM_PERIOD(_custom,_period) .notificationPeriod = (_custom*_period)>>15

typedef struct {
    /* Number of duty ticks */
    uint16_t                 duty:16;
    /* Frequency in Hz */
    uint32_t                 frequency:32;
    /* Counter */
    uint16_t                 counter:16;
    /* Custom notification part of period */
    uint8_t					 midPeriodInterrupt:1;
    /* Prescale the emios clock some more? */
    Pwm_ChannelPrescalerType prescaler:2;
    /* Prescale the emios clock some more? */
    uint32_t				 usePrescaler:1;
    /* Polarity of the channel */
    Pwm_OutputStateType		 polarity:1;
    /* Idle state */
    Pwm_OutputStateType      idleState:1;
    /* Class */
    Pwm_ChannelClassType	 class:2;
    /* Deadband delay frequency in Hz */
    uint32_t				 deadband:32;
} Pwm_ChannelSettingsType;

typedef struct {
    Pwm_ChannelSettingsType settings;
    Pwm_ChannelType channel;
} Pwm_ChannelConfigurationType;



// Channel configuration macro.
#define PWM_CHANNEL_CONFIG(_hwchannel, _frequency, _duty, _prescaler, _polarity, _idleState, _class, _midPeriodInterrupt, _deadband) \
    {\
        .channel = _hwchannel,\
        .settings = {\
            .frequency = _frequency,\
            .duty = _duty,  \
            .usePrescaler = 1,\
            .prescaler = _prescaler,\
            .polarity = _polarity,\
            .idleState = _idleState,\
            .class = _class,\
            .midPeriodInterrupt = _midPeriodInterrupt,\
            .deadband = _deadband,\
        }\
    }

#endif /* PWM_CONFIGTYPES_H_ */
