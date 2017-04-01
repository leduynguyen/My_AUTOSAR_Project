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

/** @tagSettings DEFAULT_ARCHITECTURE=STM32 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/*
 * Pwm.c
 *
 *  Created on: 2009-okt-02
 *      Author: jonte
 */

#include "Std_Types.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "Mcu.h"
#include "Os.h"
#include "Pwm.h"
#include "stm32f10x_tim.h"
#if PWM_NOTIFICATION_SUPPORTED==STD_ON
#include "isr.h"
#include "irq.h"
#include "arc.h"
#endif

#if defined(USE_DET)
#	define Pwm_Det_ReportError(ApiId, ErrorId) Det_ReportError( PWM_MODULE_ID, 0, ApiId, ErrorId);
#else
#   define Pwm_Det_ReportError(ApiId, ErrorId)
#endif

#if PWM_DEV_ERROR_DETECT==STD_ON
	#define PWM_VALIDATE(_exp, _apiid, _errid) \
		if (!(_exp)){ \
			(void)Pwm_Det_ReportError( _apiid, _errid); \
			return; \
		}
	#define Pwm_VALIDATE_CHANNEL(_apiid, _ch) PWM_VALIDATE( (_ch <= PWM_TOTAL_NOF_CHANNELS), _apiid, PWM_E_PARAM_CHANNEL)
	#define Pwm_VALIDATE_INITIALIZED(_apiid) PWM_VALIDATE( (Pwm_ModuleState == PWM_STATE_INITIALIZED), _apiid, PWM_E_UNINIT)
	#define Pwm_VALIDATE_UNINITIALIZED(_apiid) PWM_VALIDATE( (Pwm_ModuleState != PWM_STATE_INITIALIZED), _apiid, PWM_E_ALREADY_INITIALIZED)
#else
    #define PWM_VALIDATE(_exp, _apiid, _errid)
    #define Pwm_VALIDATE_CHANNEL(_apiid, _ch)
    #define Pwm_VALIDATE_INITIALIZED(_apiid)
    #define Pwm_VALIDATE_UNINITIALIZED(_apiid)
#endif

typedef enum {
    PWM_STATE_UNINITIALIZED, PWM_STATE_INITIALIZED
} Pwm_ModuleStateType;

static Pwm_ModuleStateType Pwm_ModuleState = PWM_STATE_UNINITIALIZED;
const Pwm_ConfigType *PwmConfigPtr;

/* Local functions */
#if PWM_NOTIFICATION_SUPPORTED==STD_ON
ISR(Pwm_Isr);
#endif

static TIM_TypeDef * GetTimeBaseFromChannel(Pwm_ChannelType Channel)
{
	TIM_TypeDef *TIMx=NULL;

	if(Channel < PWM_CHANNEL_21){
		TIMx = (TIM_TypeDef *)TIM1_BASE;
	} else if(Channel < PWM_CHANNEL_31){
		TIMx = (TIM_TypeDef *)TIM2_BASE;
	} else if(Channel < PWM_CHANNEL_41){
		TIMx = (TIM_TypeDef *)TIM3_BASE;
	}else if(Channel <= PWM_CHANNEL_44){
		TIMx = (TIM_TypeDef *)TIM4_BASE;
	}else{

	}

	return TIMx;
}

void Pwm_Init( const Pwm_ConfigType *ConfigPtr )
{
    uint8 i;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    Pwm_VALIDATE_UNINITIALIZED( PWM_INIT_SERVICE_ID );
	/*
	 * PWM046: If development error detection is enabled for the Pwm module,
	 * the function Pwm_Init shall raise development error PWM_E_PARAM_CONFIG
	 * if ConfigPtr is a null pointer.
	 *
	 * PWM120: For pre-compile and link-time configuration variants, a NULL
	 * pointer shall be passed to the initialization routine. In this case the
	 * check for this NULL pointer has to be omitted.
	 */
	#if PWM_STATICALLY_CONFIGURED==STD_OFF
	 PWM_VALIDATE((ConfigPtr != NULL), PWM_INIT_SERVICE_ID, PWM_E_PARAM_CONFIG);
	#endif

        
  for (i=0;i<PWM_NUMBER_OF_CHANNELS;i++){
    TIM_TypeDef *TIMx;

    TIMx = GetTimeBaseFromChannel(ConfigPtr->Channels[i].channel);
  
  /* -----------------------------------------------------------------------
     TIM4CLK = 72 MHz, Prescaler = 7199, TIM4 counter clock = 72 MHz
     TIM4 ARR Register = 10000 => TIM4 Frequency = TIM4 counter clock/(ARR*(PSC + 1)
     TIM4 Frequency = 1 Hz.
     TIM4 Channel1 duty cycle = (TIM4_CCR1/ TIM4_ARR)* 100 = 12.5%
     ----------------------------------------------------------------------- */

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = ConfigPtr->Channels[i].r.period;
    TIM_TimeBaseStructure.TIM_Prescaler = ConfigPtr->Channels[i].r.prescaler;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
   
    /* Mode configuration */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ConfigPtr->Channels[i].r.duty;
    if(ConfigPtr->Channels[i].r.edgePolarity == (uint32_t)PWM_HIGH){
    	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    }else{
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    }
    
    if((uint32)ConfigPtr->Channels[i].channel%4 == 0){
      TIM_OC1Init(TIMx, &TIM_OCInitStructure);
      TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
    } else if((uint32)ConfigPtr->Channels[i].channel%4 == 1){
      TIM_OC2Init(TIMx, &TIM_OCInitStructure);
      TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
    } else if((uint32)ConfigPtr->Channels[i].channel%4 == 2){
      TIM_OC3Init(TIMx, &TIM_OCInitStructure);
      TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
    } else if((uint32)ConfigPtr->Channels[i].channel%4 == 3){
      TIM_OC4Init(TIMx, &TIM_OCInitStructure);
      TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
    }
    
    TIM_ARRPreloadConfig(TIMx, ENABLE);
    
    /* TIMx enable counter */
    TIM_Cmd(TIMx, ENABLE);

    PwmConfigPtr = ConfigPtr;

  }

#if PWM_NOTIFICATION_SUPPORTED==STD_ON
  ISR_INSTALL_ISR2( "Pwm1", Pwm_Isr, TIM1_CC_IRQn, 6, 0 );
  ISR_INSTALL_ISR2( "Pwm2", Pwm_Isr, TIM2_IRQn,    6, 0 );
  ISR_INSTALL_ISR2( "Pwm3", Pwm_Isr, TIM3_IRQn,    6, 0 );
  ISR_INSTALL_ISR2( "Pwm4", Pwm_Isr, TIM4_IRQn,    6, 0 );
#endif

  Pwm_ModuleState = PWM_STATE_INITIALIZED;
}

#if (PWM_DE_INIT_API==STD_ON)
void Pwm_DeInit( void )
{
  Pwm_VALIDATE_INITIALIZED( PWM_DEINIT_SERVICE_ID );

  uint8 i;

  /*
   * PWM052: The function Pwm_DeInit shall disable all notifications.
   */
  for (i=0;i<PWM_TOTAL_NOF_CHANNELS;i++){
#if PWM_NOTIFICATION_SUPPORTED==STD_ON
      Pwm_DisableNotification(i);
#endif
  }
  TIM_DeInit(TIM1);
  TIM_DeInit(TIM2);
  TIM_DeInit(TIM3);
  TIM_DeInit(TIM4);

  Pwm_ModuleState = PWM_STATE_UNINITIALIZED;
}
#endif

#if (PWM_SET_DUTY_CYCLE_API == STD_ON) || (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
static void setDutyCycle(Pwm_ChannelType Channel, uint16 dutyCycle)
{
    TIM_TypeDef *TIMx;
    TIMx = GetTimeBaseFromChannel(Channel);

    /*
     * PWM058: The width of the duty cycle parameter is 16 bits
     *
     * PWM059: The PWM module shall comply with the following scaling scheme
     * for the duty cycle:
     * 0x0    =   0%,
     * 0x8000 = 100% */
    dutyCycle = (uint16)(((uint32)dutyCycle * TIMx->ARR)>>15u); /* Need to cast to uint32 avoid overflow,
     	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 * Ok, to loose the top bit since DutyCyle
     	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 * is in never > 0x8000
     	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 */

    if((uint32)Channel%4 == 0){
      TIM_SetCompare1(TIMx,dutyCycle);
    } else if((uint32)Channel%4 == 1){
      TIM_SetCompare2(TIMx,dutyCycle);
    } else if((uint32)Channel%4 == 2){
      TIM_SetCompare3(TIMx,dutyCycle);
    } else if((uint32)Channel%4 == 3){
      TIM_SetCompare4(TIMx,dutyCycle);
    }
}
#endif
#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
void Pwm_SetDutyCycle( Pwm_ChannelType Channel, uint16 dutyCycle )
{

  Pwm_VALIDATE_CHANNEL( PWM_SETDUTYCYCLE_SERVICE_ID, Channel );
  Pwm_VALIDATE_INITIALIZED( PWM_SETDUTYCYCLE_SERVICE_ID );
  
  setDutyCycle(Channel, dutyCycle);
}
#endif
/*
 * PWM083: The function Pwm_SetPeriodAndDuty shall be pre compile time
 * changeable STD_ON/STD_OFF by the configuration parameter PwmSetPeriodAndDuty.
 */
#if PWM_SET_PERIOD_AND_DUTY_API==STD_ON
void Pwm_SetPeriodAndDuty(Pwm_ChannelType Channel, Pwm_PeriodType Period,
        uint16 DutyCycle) {
    TIM_TypeDef *TIMx;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    Pwm_VALIDATE_INITIALIZED( PWM_SETPERIODANDDUTY_SERVICE_ID );
    Pwm_VALIDATE_CHANNEL( PWM_SETPERIODANDDUTY_SERVICE_ID, Channel );

    Pwm_ChannelType channel_iterator;

    for (channel_iterator = 0; channel_iterator < PWM_NUMBER_OF_CHANNELS; channel_iterator++)
    {
        if(Channel == PwmConfigPtr->Channels[channel_iterator].channel){
            /* @req SWS_Pwm_00041 */
            if(PwmConfigPtr->ChannelClass[channel_iterator] != PWM_VARIABLE_PERIOD){
#if PWM_DEV_ERROR_DETECT==STD_ON
                /* @req SWS_Pwm_00045 */
                /* @req SWS_Pwm_40002 */
                (void)Det_ReportError(PWM_MODULE_ID,0, PWM_SETPERIODANDDUTY_SERVICE_ID, PWM_E_PERIOD_UNCHANGEABLE);
#endif
                return;
            }
            break;
        }
    }
    /* Check that we found a valid channel */
    /* @req SWS_Pwm_00047*/
    PWM_VALIDATE(channel_iterator < PWM_NUMBER_OF_CHANNELS, PWM_SETPERIODANDDUTY_SERVICE_ID, PWM_E_PARAM_CHANNEL);

    TIMx = GetTimeBaseFromChannel(Channel);

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = Period;
    TIM_TimeBaseStructure.TIM_Prescaler = TIMx->PSC; // get old prescaler
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

    setDutyCycle(Channel,DutyCycle);
}
#endif

#if PWM_NOTIFICATION_SUPPORTED==STD_ON
void Pwm_DisableNotification(Pwm_ChannelType Channel) 
{
    TIM_TypeDef *TIMx;
    uint16_t tim_it = 0;
    Pwm_VALIDATE_CHANNEL( PWM_DISABLENOTIFICATION_SERVICE_ID, Channel );
    Pwm_VALIDATE_INITIALIZED( PWM_DISABLENOTIFICATION_SERVICE_ID );

    TIMx = GetTimeBaseFromChannel(Channel);

    if(Channel%4 == 0){
        tim_it = TIM_IT_CC1;
    } else if(Channel%4 == 1){
        tim_it = TIM_IT_CC2;
    } else if(Channel%4 == 2){
        tim_it = TIM_IT_CC3;
    } else if(Channel%4 == 3){
        tim_it = TIM_IT_CC4;
    }

    TIM_ITConfig(TIMx, tim_it,DISABLE);
}

void Pwm_EnableNotification(Pwm_ChannelType Channel,
        Pwm_EdgeNotificationType Notification) 
{
    TIM_TypeDef *TIMx;
    uint16_t tim_it = 0;
    Pwm_VALIDATE_CHANNEL( PWM_ENABLENOTIFICATION_SERVICE_ID, Channel );
    Pwm_VALIDATE_INITIALIZED( PWM_ENABLENOTIFICATION_SERVICE_ID );

    TIMx = GetTimeBaseFromChannel(Channel);

    if(Channel%4 == 0){
        tim_it = TIM_IT_CC1;
    } else if(Channel%4 == 1){
        tim_it = TIM_IT_CC2;
    } else if(Channel%4 == 2){
        tim_it = TIM_IT_CC3;
    } else if(Channel%4 == 3){
        tim_it = TIM_IT_CC4;
    }
    //@req PWM081 clear any pending interrupts before enable
    TIM_ClearITPendingBit (TIMx,TIM_IT_Update|TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4|TIM_IT_COM|TIM_IT_Trigger|TIM_IT_Break);

    TIM_ITConfig(TIMx, tim_it,ENABLE);
}

ISR(Pwm_Isr) {
    ITStatus status = 0;
    status = TIM_GetITStatus(TIM1, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4);
    if(status != 0){
        TIM_ClearITPendingBit(TIM1, status);
        status = 0;
    }
    status = TIM_GetITStatus(TIM2, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4);
    if(status != 0){
        TIM_ClearITPendingBit(TIM2, status);
        status = 0;
    }
    status = TIM_GetITStatus(TIM3, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4);
    if(status != 0){
        TIM_ClearITPendingBit(TIM3, status);
        status = 0;
    }
    status = TIM_GetITStatus(TIM4, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4);
    if(status != 0){
        TIM_ClearITPendingBit(TIM4, status);
        status = 0;
    }
}
#endif //PWM_NOTIFICATION_SUPPORTED==STD_ON

#if ( PWM_SET_OUTPUT_TO_IDLE_API == STD_ON )
void Pwm_SetOutputToIdle(Pwm_ChannelType Channel) {
    TIM_TypeDef *TIMx;
    Pwm_VALIDATE_CHANNEL( PWM_SETOUTPUTTOIDLE_SERVICE_ID, Channel );
    Pwm_VALIDATE_INITIALIZED( PWM_SETOUTPUTTOIDLE_SERVICE_ID );

    TIMx = GetTimeBaseFromChannel(Channel);

    if(Channel%4 == 0){
      TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Disable);
    } else if(Channel%4 == 1){
      TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Disable);
    } else if(Channel%4 == 2){
      TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Disable);
    } else if(Channel%4 == 3){
      TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Disable);
    }
}
#endif

/*
 * PWM085: The function Pwm_GetOutputState shall be pre compile configurable
 * STD_ON/STD_OFF by the configuration parameter PwmGetOutputState
 */
#if PWM_GET_OUTPUT_STATE_API==STD_ON
/*
 * PWM022: The function Pwm_GetOutputState shall read the internal state
 * of the PWM output signal and return it.
 */
Pwm_OutputStateType Pwm_GetOutputState(Pwm_ChannelType Channel) {

    // We need to return something, even in presence of errors
    if (Channel >= PWM_TOTAL_NOF_CHANNELS) {
        Pwm_Det_ReportError( PWM_GETOUTPUTSTATE_SERVICE_ID, PWM_E_PARAM_CHANNEL );

        /*
         * Accordingly to PWM025, we should return PWM_LOW on failure.
         */
        return PWM_LOW;

    } else if (Pwm_ModuleState != PWM_STATE_INITIALIZED) {
        Pwm_Det_ReportError( PWM_GETOUTPUTSTATE_SERVICE_ID, PWM_E_UNINIT );

        /*
         * Accordingly to PWM025, we should return PWM_LOW on failure.
         */
        return PWM_LOW;

    }

    return PWM_LOW; // IMPROVEMENT: implement Pwm_GetOutputState
}
#endif

#if ( PWM_VERSION_INFO_API == STD_ON)
void Pwm_GetVersionInfo( Std_VersionInfoType* versioninfo) {

    /* @req SWS_Pwm_00151 */
    PWM_VALIDATE( ( NULL != versioninfo ), PWM_GETVERSIONINFO_SERVICE_ID, PWM_E_PARAM_POINTER);

    versioninfo->vendorID = PWM_VENDOR_ID;
    versioninfo->moduleID = PWM_MODULE_ID;
    versioninfo->sw_major_version = PWM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = PWM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = PWM_SW_PATCH_VERSION;
}
#endif
