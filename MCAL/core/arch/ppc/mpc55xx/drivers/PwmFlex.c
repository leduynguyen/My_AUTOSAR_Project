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

/** @tagSettings DEFAULT_ARCHITECTURE=NOT_USED */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/* NOTES
 * The PWMX is bound with submodule period. The PWM signals are generated in the following manner.
 * - The INIT and VAL1 registers define the PWM modulo/period. So the PWM counter counts from INIT to VAL1 and then reinit to INIT again etc.
 * - The VAL2 resp. VAL3 define the compare value when PWMA goes High resp. Low.
 * - The VAL4 resp. VAL5 define the compare value when PWMB goes High resp. Low.
 * - The VAL0 defines half cycle reload point and also define the time when PWMX signal is set and the local sync signal is reset.
 * - The VAL1 also causes PWMX reseting and asserting local sync.
 * So the usage of PMWA and PWMB signals is easy. The PWMX, if not use as input (for capture feature etc), can generate also the PWM signal
 * but you have to take into account that it represents the local sync signal, which is usually selected as sync source by INIT_SEL bits of CTRL2.
 *
 *      ,------,       ,------
 *      |      |       |
 *    --´      `-------´
 *      |<--- VAL1 --->|
 *      |      |
 *    VAL2    VAL3              PWMA
 *    VAL4    VAL5              PWMB
 *
 */


#include "arc_assert.h"
#include <string.h>

#include "Pwm.h"
#include "MemMap.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "mpc55xx.h"

#include "Os.h"
#include "Mcu.h"
#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
#include "isr.h"
#include "irq.h"
#include "arc.h"
#endif

#include "SchM_Pwm.h"


static volatile struct FLEXPWM_tag * const PLEXPWM[] = {&FLEXPWM_0, &FLEXPWM_1};
#define GET_FLEXPWM_HW(_index) PLEXPWM[(_index) / PWM_CHANNELS_PER_MODULE]
#define GET_SUBMODULE(_index) ((_index) % PWM_CHANNELS_PER_MODULE / FLEXPWM_SUB_MODULE_DIVIDER)
#define PWM_CHANNELS_PER_MODULE (sizeof(FLEXPWM_0.SUB)/sizeof(FLEXPWM_0.SUB[0])*FLEXPWM_SUB_MODULE_DIVIDER)
#define GET_SUB_START_CHANNEL(_hw, _sub) ((_hw)*PWM_CHANNELS_PER_MODULE) + ((_sub)*FLEXPWM_SUB_MODULE_DIVIDER)
#define IS_VALID_CHANNEL(_x) ((_x) < PWM_NUMBER_OF_CHANNELS)

#define FLEXPWM_SUB_MODULE_DIVIDER 3

#define PWM_PERIOD_MAX_TICKS 0x7FFE
#define GET_HW_PTR(_hwUnit) PLEXPWM[(_hwUnit)]

#if ( PWM_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          Det_ReportError(PWM_MODULE_ID,0,_api,_err); \
          return; \
        }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
        if( !(_exp) ) { \
          Det_ReportError(PWM_MODULE_ID,0,_api,_err); \
          return (_rv); \
        }
#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_W_RV(_exp,_api,_err,_rv )
#endif


const Pwm_ConfigType* PwmConfigPtr = NULL;

typedef enum {
    PWM_STATE_UNINITIALIZED, PWM_STATE_INITIALIZED
} Pwm_ModuleStateType;
typedef enum {
    PWM_A, PWM_B, PWM_X
} PwmT;

#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
typedef struct {
    Pwm_EdgeNotificationType EdgeNotification;
    boolean Locked;
}EdgeNotificationStatusType;
#endif

typedef struct {
    Pwm_ModuleStateType ModuleState;
#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
    EdgeNotificationStatusType ChannelEdgeNotification[PWM_NUMBER_OF_CHANNELS];
#endif
}PwmInternalType;

static PwmInternalType PwmInternal = {
        .ModuleState = PWM_STATE_UNINITIALIZED,
};
typedef struct {
    uint8 dutyRegIndex;
    uint8 periodRegIndex;
}PwmRegIndexType;

static const PwmRegIndexType PwmRegIndex[FLEXPWM_SUB_MODULE_DIVIDER] = {
        [PWM_A] = {
                .dutyRegIndex = 3, /* VAL[3] */
                .periodRegIndex = 1, /* VAL[1] */
        },
        [PWM_B] = {
                .dutyRegIndex = 5, /* VAL[5] */
                .periodRegIndex = 1, /* VAL[1] */
        },
        [PWM_X] = {
                .dutyRegIndex = 0, /* VAL[0] */
                .periodRegIndex = 1, /* VAL[1] */
        },
};

static void SetDutyCycle(Pwm_ChannelType Channel, uint16 DutyCycle);

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
static void Pwm_Isr(uint8 hwUnit, uint8 sub);
#if defined(NOTIFICATION_ON_CHANNEL_0_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_1_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_2_ENABLED)
ISR(Pwm_Isr_0_0){Pwm_Isr(0,0);}
#endif
#if defined(NOTIFICATION_ON_CHANNEL_3_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_4_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_5_ENABLED)
ISR(Pwm_Isr_0_1){Pwm_Isr(0,1);}
#endif
#if defined(NOTIFICATION_ON_CHANNEL_6_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_7_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_8_ENABLED)
ISR(Pwm_Isr_0_2){Pwm_Isr(0,2);}
#endif
#if defined(NOTIFICATION_ON_CHANNEL_9_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_10_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_11_ENABLED)
ISR(Pwm_Isr_0_3){Pwm_Isr(0,3);}
#endif
#if defined(NOTIFICATION_ON_CHANNEL_12_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_13_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_14_ENABLED)
ISR(Pwm_Isr_1_0){Pwm_Isr(1,0);}
#endif
#if defined(NOTIFICATION_ON_CHANNEL_15_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_16_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_17_ENABLED)
ISR(Pwm_Isr_1_1){Pwm_Isr(1,1);}
#endif
#if defined(NOTIFICATION_ON_CHANNEL_18_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_19_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_20_ENABLED)
ISR(Pwm_Isr_1_2){Pwm_Isr(1,2);}
#endif
#if defined(NOTIFICATION_ON_CHANNEL_21_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_22_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_23_ENABLED)
ISR(Pwm_Isr_1_3){Pwm_Isr(1,3);}
#endif
#endif

static void calcPeriodTicksAndPrescaler(
                const Pwm_ChannelConfigurationType* channelConfig,
                uint16_t* ticks, Pwm_ChannelPrescalerType* prescaler) {

    uint32_t f_in = 0;

    f_in = Mcu_Arc_GetPeripheralClock( PERIPHERAL_CLOCK_FLEXPWM_0 );

    uint32_t f_target = channelConfig->frequency;

    Pwm_ChannelPrescalerType pre;
    uint32_t ticks_temp;

    if (channelConfig->prescaler == PWM_CHANNEL_PRESCALER_DIV_AUTO) {
        // Go from lowest to highest prescaler
        for (pre = PWM_CHANNEL_PRESCALER_DIV_1; pre <= PWM_CHANNEL_PRESCALER_DIV_128; pre++) {
            ticks_temp = f_in / (f_target * (1 << pre)); // Calc ticks
          if (ticks_temp > PWM_PERIOD_MAX_TICKS) {
            ticks_temp = PWM_PERIOD_MAX_TICKS;  // Prescaler too low
            } else {
                break;                // Prescaler ok
            }
        }
    } else {
        pre = channelConfig->prescaler; // Use config setting
        ticks_temp = f_in / (f_target * (1 << pre)); // Calc ticks
        if (ticks_temp > PWM_PERIOD_MAX_TICKS) {
          ticks_temp = PWM_PERIOD_MAX_TICKS;  // Prescaler too low
        }
        }

    (*ticks) = (uint16_t) ticks_temp;
    (*prescaler) = pre;
}


static void configureChannel(Pwm_ChannelType Channel){

    const Pwm_ChannelConfigurationType* channelConfig = &PwmConfigPtr->Channels[Channel];
    volatile struct FLEXPWM_tag *flexHw = GET_FLEXPWM_HW(channelConfig->index);
    uint8 sub = GET_SUBMODULE(channelConfig->index);
    PwmT pwm =  (PwmT)(channelConfig->index % FLEXPWM_SUB_MODULE_DIVIDER);
    Pwm_ChannelPrescalerType prescaler;
    uint16_t period_ticks;

    /*  Remove submodule unique so that it is not configured for all channels */

    /* All channels on same submodule must have same period. Should be checked by validation */
    calcPeriodTicksAndPrescaler( channelConfig, &period_ticks, &prescaler );

    // clear LDOK to be able to modify register settings
    flexHw->MCTRL.B.CLDOK |= 1 << sub;

    /* Prescaler */
    flexHw->SUB[sub].CTRL.B.PRSC = prescaler;

    /* Edge aligned output, modulo count */
    flexHw->SUB[sub].INIT.R =   0x0000; /* INIT value */
    flexHw->SUB[sub].VAL[1].R = period_ticks; /* maximum count i.e. period NOTE! Valid for whole subgroup */

    flexHw->SUB[sub].DISMAP.R   = 0x0000;	/* disable fault pin condition */
    flexHw->SUB[sub].CTRL2.B.INDEP = 1; /* Run as independent channels */

    /* Polarity */
    switch(pwm)
    {
    case PWM_A: /* PWMA */
        flexHw->SUB[sub].VAL[2].R = 0x0000; /* PWMA rising edge */
        flexHw->SUB[sub].OCTRL.B.POLA = (channelConfig->polarity == PWM_LOW) ? 1 : 0;
        break;
    case PWM_B: /* PWMB */
        flexHw->SUB[sub].VAL[4].R = 0x0000; /* PWMB rising edge */
        flexHw->SUB[sub].OCTRL.B.POLB = (channelConfig->polarity == PWM_LOW) ? 1 : 0;
        break;
    case PWM_X: /* PWMX */
        flexHw->SUB[sub].VAL[0].R = 0x0000; /* PWMX rising edge */
        /* Since we can only set the rising edge for PWMX, we set the polarity
         * in the opposite way compared to PWMA and PWMB. */
        flexHw->SUB[sub].OCTRL.B.POLX = (channelConfig->polarity == PWM_LOW) ? 0 : 1;
        break;
    }

    /* PWM009: The function Pwm_Init shall start all PWM channels with the configured
        default values. If the duty cycle parameter equals:
        􀂃 0% or 100% : Then the PWM output signal shall be in the state according to
            the configured polarity parameter
        􀂃 >0% and <100%: Then the PWM output signal shall be modulated according
        to parameters period, duty cycle and configured polarity. */
    SetDutyCycle(Channel, channelConfig->duty);
    // enable outputs when all configuration is done
    switch(pwm)
    {
    case PWM_A:
        flexHw->OUTEN.B.PWMA_EN |= 1 << sub;
        break;
    case PWM_B:
        flexHw->OUTEN.B.PWMB_EN |= 1 << sub;
        break;
    case PWM_X:
        flexHw->OUTEN.B.PWMX_EN |= 1 << sub;
        break;
    }
    flexHw->MCTRL.B.LDOK |= 1 << sub;
    flexHw->MCTRL.B.RUN |= 1 << sub;

}
#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
/**
 * Disables notifications for the channel
 * @param Channel
 */
static void disableNotification(Pwm_ChannelType Channel)
{
    uint8 disableMask = 3;
    const Pwm_ChannelConfigurationType* channelConfig = &PwmConfigPtr->Channels[Channel];
    volatile struct FLEXPWM_tag *flexHw = GET_FLEXPWM_HW(channelConfig->index);
    uint8 sub = GET_SUBMODULE(channelConfig->index);
    PwmT pwm =  (PwmT)(channelConfig->index % FLEXPWM_SUB_MODULE_DIVIDER);

    switch(pwm) {
    case PWM_A:
        disableMask <<= 2;
        break;
    case PWM_B:
        disableMask <<= 4;
        break;
    case PWM_X:
        disableMask <<= 0;
        break;
    }
    // clear eventual pending notification
    flexHw->SUB[sub].STS.B.CMPF = ~disableMask;
    /* Clear flags on this submodule */
    flexHw->SUB[sub].INTEN.B.CMPIE &= ~disableMask;


}
/**
 * Tries to disable notifications for the channel.
 * @param Channel
 */
static void tryDisableNotification(Pwm_ChannelType Channel)
{
    if( !PwmInternal.ChannelEdgeNotification[Channel].Locked ) {
        disableNotification(Channel);
    }
    PwmInternal.ChannelEdgeNotification[Channel].EdgeNotification = (Pwm_EdgeNotificationType)PWM_NO_EDGES;
}
/**
 * Forces disabling of notification and locks the notifications
 * @param Channel
 */
static void forceDisableNotification(Pwm_ChannelType Channel)
{
    if( !PwmInternal.ChannelEdgeNotification[Channel].Locked ) {
        disableNotification(Channel);
        PwmInternal.ChannelEdgeNotification[Channel].Locked = TRUE;
    }
}
/**
 * Enables interrupts for the channel
 * @param Channel
 * @param Notification
 */
static void enableNotification(Pwm_ChannelType Channel, Pwm_EdgeNotificationType Notification)
{

    uint8 enableFlags = 0;
    uint8 mask = 3u;

    switch(Notification) {
        case PWM_FALLING_EDGE:
            enableFlags = 1;
            break;
        case PWM_RISING_EDGE:
            enableFlags = 2;
            break;
        case PWM_BOTH_EDGES:
            enableFlags = 3;
            break;
        default:
            return;
    }

    const Pwm_ChannelConfigurationType* channelConfig = &PwmConfigPtr->Channels[Channel];
    volatile struct FLEXPWM_tag *flexHw = GET_FLEXPWM_HW(channelConfig->index);
    uint8 sub = GET_SUBMODULE(channelConfig->index);
    PwmT pwm =  (PwmT)(channelConfig->index % FLEXPWM_SUB_MODULE_DIVIDER);

    switch(pwm) {
    case PWM_A:
        enableFlags <<= 2;
        mask <<= 2;
        break;
    case PWM_B:
        enableFlags <<= 4;
        mask <<= 4;
        break;
    case PWM_X:
        enableFlags <<= 0;
        break;
    }

    // clear eventual pending notification
    flexHw->SUB[sub].STS.B.CMPF = mask;
    flexHw->SUB[sub].INTEN.B.CMPIE = (flexHw->SUB[sub].INTEN.B.CMPIE & ~mask) | enableFlags;
}
/**
 * Tries to enable notification for the channel
 * @param Channel
 * @param Notification
 */
static void tryEnableNotification(Pwm_ChannelType Channel, Pwm_EdgeNotificationType Notification)
{
    if( !PwmInternal.ChannelEdgeNotification[Channel].Locked ) {
        enableNotification(Channel, Notification);
    }
    /* Store the requested notification */
    PwmInternal.ChannelEdgeNotification[Channel].EdgeNotification = Notification;
}

/**
 * Restores notifications to the state last requested
 * @param Channel
 */
static void restoreNotification(Pwm_ChannelType Channel)
{
    if(PWM_NO_EDGES != PwmInternal.ChannelEdgeNotification[Channel].EdgeNotification) {
        enableNotification(Channel, PwmInternal.ChannelEdgeNotification[Channel].EdgeNotification);
    }
    PwmInternal.ChannelEdgeNotification[Channel].Locked = FALSE;
}
#endif

#if  (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON) || (PWM_DE_INIT_API==STD_ON)
static void setOutputToIdle(Pwm_ChannelType Channel)
{
    const Pwm_ChannelConfigurationType* channelConfig = &PwmConfigPtr->Channels[Channel];
    /* Use SetDutyCycle to set idle level */
    if(channelConfig->polarity == PwmConfigPtr->IdleState[Channel]) {
        SetDutyCycle(Channel, PWM_100_PERCENT);
    } else {
        SetDutyCycle(Channel, 0);
    }

}
#endif

void Pwm_Init(const Pwm_ConfigType* ConfigPtr) {
    /* @req SWS_Pwm_10002 */
    VALIDATE( ( NULL != ConfigPtr ), PWM_INIT_SERVICE_ID, PWM_E_PARAM_CONFIG );
    VALIDATE( ( PwmInternal.ModuleState == PWM_STATE_UNINITIALIZED ), PWM_INIT_SERVICE_ID, PWM_E_ALREADY_INITIALIZED );

    /** @req SWS_PWM_00118 */
    /** @req SWS_PWM_00121 */
    if( PwmInternal.ModuleState == PWM_STATE_INITIALIZED ) {
#if PWM_DEV_ERROR_DETECT==STD_ON
        Det_ReportError(PWM_MODULE_ID,0,PWM_INIT_SERVICE_ID,PWM_E_ALREADY_INITIALIZED);
#endif
        return;
    }

    PwmConfigPtr = ConfigPtr;
    PwmInternal.ModuleState = PWM_STATE_INITIALIZED;

#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
    #if defined(NOTIFICATION_ON_CHANNEL_0_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_1_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_2_ENABLED)
    ISR_INSTALL_ISR2("PwmIsr", Pwm_Isr_0_0, (IrqType)(PWM0_COF0),PWM_ISR_PRIORITY, 0);
    #endif
    #if defined(NOTIFICATION_ON_CHANNEL_3_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_4_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_5_ENABLED)
    ISR_INSTALL_ISR2("PwmIsr", Pwm_Isr_0_1, (IrqType)(PWM0_COF1),PWM_ISR_PRIORITY, 0);
    #endif
    #if defined(NOTIFICATION_ON_CHANNEL_6_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_7_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_8_ENABLED)
    ISR_INSTALL_ISR2("PwmIsr", Pwm_Isr_0_2, (IrqType)(PWM0_COF2),PWM_ISR_PRIORITY, 0);
    #endif
    #if defined(NOTIFICATION_ON_CHANNEL_9_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_10_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_11_ENABLED)
    ISR_INSTALL_ISR2("PwmIsr", Pwm_Isr_0_3, (IrqType)(PWM0_COF3),PWM_ISR_PRIORITY, 0);
    #endif
    #if defined(NOTIFICATION_ON_CHANNEL_12_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_13_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_14_ENABLED)
    ISR_INSTALL_ISR2("PwmIsr", Pwm_Isr_1_0, (IrqType)(PWM1_COF0),PWM_ISR_PRIORITY, 0);
    #endif
    #if defined(NOTIFICATION_ON_CHANNEL_15_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_16_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_17_ENABLED)
    ISR_INSTALL_ISR2("PwmIsr", Pwm_Isr_1_1, (IrqType)(PWM1_COF1),PWM_ISR_PRIORITY, 0);
    #endif
    #if defined(NOTIFICATION_ON_CHANNEL_18_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_19_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_20_ENABLED)
    ISR_INSTALL_ISR2("PwmIsr", Pwm_Isr_1_2, (IrqType)(PWM1_COF2),PWM_ISR_PRIORITY, 0);
    #endif
    #if defined(NOTIFICATION_ON_CHANNEL_21_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_22_ENABLED) || defined(NOTIFICATION_ON_CHANNEL_23_ENABLED)
    ISR_INSTALL_ISR2("PwmIsr", Pwm_Isr_1_3, (IrqType)(PWM1_COF3),PWM_ISR_PRIORITY, 0);
    #endif
#endif

    for (Pwm_ChannelType i = 0; i < PWM_NUMBER_OF_CHANNELS; i++) {
#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
        PwmInternal.ChannelEdgeNotification[i].EdgeNotification = (Pwm_EdgeNotificationType)PWM_NO_EDGES;
        PwmInternal.ChannelEdgeNotification[i].Locked = FALSE;
#endif
        configureChannel( i );
    }

}

#if (PWM_DE_INIT_API==STD_ON)

static void Pwm_DeInitChannel(Pwm_ChannelType Channel) {

    setOutputToIdle(Channel);

    /*
     * PWM052: The function Pwm_DeInit shall disable all notifications.
     */
#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
    /* Try to enable notification. They have been forced disabled
     * by setOutputToIdle since it sets duty cycle to 0 or 100%. */
    tryDisableNotification(Channel);
#endif

}

void Pwm_DeInit(void) {

    VALIDATE(PwmInternal.ModuleState == PWM_STATE_INITIALIZED, PWM_DEINIT_SERVICE_ID, PWM_E_UNINIT);

    for (Pwm_ChannelType i = 0; i < PWM_NUMBER_OF_CHANNELS; i++) {
        const Pwm_ChannelConfigurationType* channelConfig = &PwmConfigPtr->Channels[i];
        volatile struct FLEXPWM_tag *flexHw = GET_FLEXPWM_HW(channelConfig->index);
        uint8 sub = GET_SUBMODULE(channelConfig->index);
        PwmT pwm =  (PwmT)(channelConfig->index % FLEXPWM_SUB_MODULE_DIVIDER);
        Pwm_DeInitChannel(i);
        // disable output
        switch(pwm)
        {
        case PWM_A: /* PWMA */
            flexHw->OUTEN.B.PWMA_EN &= ~(1 << sub);
            break;
        case PWM_B: /* PWMB */
            flexHw->OUTEN.B.PWMB_EN &= ~(1 << sub);
            break;
        case PWM_X: /* PWMX */
            flexHw->OUTEN.B.PWMX_EN &= ~(1 << sub);
            break;
        }
    }
    // Disable module
    for (Pwm_ChannelType i = 0; i < PWM_NUMBER_OF_CHANNELS; i++) {
        const Pwm_ChannelConfigurationType* channelConfig = &PwmConfigPtr->Channels[i];
        volatile struct FLEXPWM_tag *flexHw = GET_FLEXPWM_HW(channelConfig->index);
        uint8 sub = GET_SUBMODULE(channelConfig->index);
        flexHw->MCTRL.B.CLDOK = (1 << sub);
        flexHw->MCTRL.B.RUN &= ~(1 << sub);
    }


    PwmInternal.ModuleState = PWM_STATE_UNINITIALIZED;
}
#endif


/*
 * PWM083: The function Pwm_SetPeriodAndDuty shall be pre compile time
 * changeable ON/OFF by the configuration parameter PwmSetPeriodAndDuty.
 */
#if (PWM_SET_PERIOD_AND_DUTY_API==STD_ON)
void Pwm_SetPeriodAndDuty(Pwm_ChannelType Channel, Pwm_PeriodType Period, uint16 DutyCycle) {

    VALIDATE(PwmInternal.ModuleState == PWM_STATE_INITIALIZED, PWM_SETPERIODANDDUTY_SERVICE_ID, PWM_E_UNINIT);
    VALIDATE(Channel < PWM_NUMBER_OF_CHANNELS, PWM_SETPERIODANDDUTY_SERVICE_ID, PWM_E_PARAM_CHANNEL);

    if(PwmConfigPtr->ChannelClass[Channel] != PWM_VARIABLE_PERIOD){
#if PWM_DEV_ERROR_DETECT==STD_ON
        Det_ReportError(PWM_MODULE_ID,0, PWM_SETPERIODANDDUTY_SERVICE_ID, PWM_E_PERIOD_UNCHANGEABLE);
#endif
        return;
    }

    const Pwm_ChannelConfigurationType* channelConfig = &PwmConfigPtr->Channels[Channel];
    volatile struct FLEXPWM_tag *flexHw = GET_FLEXPWM_HW(channelConfig->index);
    uint8 sub = GET_SUBMODULE(channelConfig->index);
    if(flexHw->SUB[sub].VAL[1].R != Period) { // only tests period 1 since all periods must be the same
        // clear eventual ldok flag
        flexHw->MCTRL.B.CLDOK = 1 << sub;
    	flexHw->SUB[sub].VAL[1].R = Period;
    }

    SetDutyCycle(Channel, DutyCycle);
}
#endif

static void SetDutyCycle(Pwm_ChannelType Channel, uint16 DutyCycle)
{
    const Pwm_ChannelConfigurationType* channelConfig = &PwmConfigPtr->Channels[Channel];
    volatile struct FLEXPWM_tag *flexHw = GET_FLEXPWM_HW(channelConfig->index);
    uint8 sub = GET_SUBMODULE(channelConfig->index);
    PwmT pwm =  (PwmT)(channelConfig->index % FLEXPWM_SUB_MODULE_DIVIDER);

    uint16 leading_edge_position;
    uint32 period;

    /* Timer instant for leading edge */

    /*
     * PWM017: The function Pwm_SetDutyCycle shall update the duty cycle at
     * the end of the period if supported by the implementation and configured
     * with PwmDutycycleUpdatedEndperiod. [ This is achieved in hardware since
     * the A and B registers are double buffered ]
     *
     * PWM014: The function Pwm_SetDutyCycle shall set the output state according
     * to the configured polarity parameter [which is already set from
     * Pwm_Init], when the duty parameter is 0% [=0] or 100% [=0x8000].
     */

	SchM_Enter_Pwm_EA_0();

    period = flexHw->SUB[sub].VAL[PwmRegIndex[pwm].periodRegIndex].R;
    leading_edge_position = (uint16) (( period  * (uint32) DutyCycle) / PWM_100_PERCENT );
    // clear eventual ldok flag
    flexHw->MCTRL.B.CLDOK = 1 << sub;
    if( PWM_100_PERCENT == DutyCycle ) {
        /* Increment to one above period to never get match on turn off (prevents glitch).
         * This may lead to  */
        leading_edge_position++;
    }
    if( PWM_X == pwm ) {
        /* Cannot get 0% duty cycle (according to reference manual you
         * can't get 100% on PWMX but we invert it so it).
         * But we can get 100% percent duty cycle so invert polarity
         * and set the duty cycle to 100%  */
        if( PWM_0_PERCENT == DutyCycle ) {
            flexHw->SUB[sub].OCTRL.B.POLX = (channelConfig->polarity == PWM_LOW) ? 1 : 0;
            leading_edge_position = period + 1;
        } else {
            /* Restore the polarity */
            flexHw->SUB[sub].OCTRL.B.POLX = (channelConfig->polarity == PWM_LOW) ? 0 : 1;
        }
    }
#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
    if( (PWM_100_PERCENT == DutyCycle) || (PWM_0_PERCENT == DutyCycle) || (period == 0) ) {
        /* Will not give edges so disable the notification */
        forceDisableNotification(Channel);
        flexHw->SUB[sub].VAL[PwmRegIndex[pwm].dutyRegIndex].R = 0xffff;
    } else {
        /* Restore the notification as requested */
        restoreNotification(Channel);
        flexHw->SUB[sub].VAL[PwmRegIndex[pwm].dutyRegIndex].R = leading_edge_position;
    }
#else
    flexHw->SUB[sub].VAL[PwmRegIndex[pwm].dutyRegIndex].R = leading_edge_position;
#endif


    // set ldok to ensure that new values are used at next reload
    flexHw->MCTRL.B.LDOK = 1 << sub;

    SchM_Exit_Pwm_EA_0();
}


/**
 * PWM013: The function Pwm_SetDutyCycle shall set the duty cycle of the PWM
 * channel.
 *
 * @param Channel PWM channel to use. 0 <= Channel < PWM_NUMBER_OF_CHANNELS <= 16
 * @param DutyCycle 0 <= DutyCycle <= 0x8000
 */
#if (PWM_SET_DUTY_CYCLE_API==STD_ON)
void Pwm_SetDutyCycle(Pwm_ChannelType Channel, uint16 DutyCycle)
{
    VALIDATE(PwmInternal.ModuleState == PWM_STATE_INITIALIZED, PWM_SETDUTYCYCLE_SERVICE_ID, PWM_E_UNINIT);
    VALIDATE(Channel < PWM_NUMBER_OF_CHANNELS, PWM_SETDUTYCYCLE_SERVICE_ID, PWM_E_PARAM_CHANNEL);

    SetDutyCycle(Channel, DutyCycle);
}
#endif

#if  (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
/* @req SWS_Pwm_10084 */
/* @req SWS_Pwm_20084 */
void Pwm_SetOutputToIdle(Pwm_ChannelType Channel)
{
    VALIDATE(PwmInternal.ModuleState == PWM_STATE_INITIALIZED, PWM_SETOUTPUTTOIDLE_SERVICE_ID, PWM_E_UNINIT);
    VALIDATE(Channel < PWM_NUMBER_OF_CHANNELS, PWM_SETOUTPUTTOIDLE_SERVICE_ID, PWM_E_PARAM_CHANNEL);
    /* @req SWS_Pwm_10021 */
    setOutputToIdle(Channel);
}
#endif
/*
 * PWM085: The function Pwm_GetOutputState shall be pre compile configurable
 * ON/OFF by the configuration parameter PwmGetOutputState
 */
#if (PWM_GET_OUTPUT_STATE_API==STD_ON)
/*
 * PWM022: The function Pwm_GetOutputState shall read the internal state
 * of the PWM output signal and return it.
 */
Pwm_OutputStateType Pwm_GetOutputState(Pwm_ChannelType Channel)
{
    Pwm_OutputStateType res = PWM_LOW;

    VALIDATE_W_RV(PwmInternal.ModuleState == PWM_STATE_INITIALIZED, PWM_GETOUTPUTSTATE_SERVICE_ID, PWM_E_UNINIT, res);
    VALIDATE_W_RV(Channel < PWM_NUMBER_OF_CHANNELS, PWM_GETOUTPUTSTATE_SERVICE_ID, PWM_E_PARAM_CHANNEL, res);

    const Pwm_ChannelConfigurationType* channelConfig = &PwmConfigPtr->Channels[Channel];
    volatile struct FLEXPWM_tag *flexHw = GET_FLEXPWM_HW(channelConfig->index);
    uint8 sub = GET_SUBMODULE(channelConfig->index);
    PwmT pwm =  (PwmT)(channelConfig->index % FLEXPWM_SUB_MODULE_DIVIDER);

    switch(pwm)
    {
    case PWM_A:
        res = PWM_LOW;
        // not supported on this channel
        //res = (Pwm_OutputStateType)flexHw->SUB[sub].OCTRL.B.PWMA_IN;
        break;
    case PWM_B:
        res = PWM_LOW;
        // not supported on this channel
        //res = (Pwm_OutputStateType)flexHw->SUB[sub].OCTRL.B.PWMB_IN;
        break;
    case PWM_X:
        res = (Pwm_OutputStateType)flexHw->SUB[sub].OCTRL.B.PWMX_IN;
        break;
    default:
        break;
    }

    return res;
}
#endif

#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
void Pwm_DisableNotification(Pwm_ChannelType Channel)
{
    VALIDATE(PwmInternal.ModuleState == PWM_STATE_INITIALIZED, PWM_DISABLENOTIFICATION_SERVICE_ID, PWM_E_UNINIT);
    VALIDATE(Channel < PWM_NUMBER_OF_CHANNELS, PWM_DISABLENOTIFICATION_SERVICE_ID, PWM_E_PARAM_CHANNEL);
    /* Try to disable the notification. It may already be
     * disabled due to duty cycle 0% and 100%. */
    tryDisableNotification(Channel);
}

void Pwm_EnableNotification(Pwm_ChannelType Channel, Pwm_EdgeNotificationType Notification)
{
    VALIDATE(PwmInternal.ModuleState == PWM_STATE_INITIALIZED, PWM_ENABLENOTIFICATION_SERVICE_ID, PWM_E_UNINIT);
    VALIDATE(Channel < PWM_NUMBER_OF_CHANNELS, PWM_ENABLENOTIFICATION_SERVICE_ID, PWM_E_PARAM_CHANNEL);
    /* Try to enable the notification. It may be disabled due to
     * duty cycle 0% and 100%. In this case the notifications will be
     * enbled laster when changing duty cycle to other than 0% or 100% */
    tryEnableNotification(Channel, Notification);
}

static void Pwm_Isr(uint8 hwUnit, uint8 sub)
{
    volatile struct FLEXPWM_tag *flexHw = GET_HW_PTR(hwUnit);
    uint8 cmpflags = flexHw->SUB[sub].STS.B.CMPF & flexHw->SUB[sub].INTEN.B.CMPIE;

    uint8 isr = 0;
    for(PwmT pwm = (PwmT)0; pwm < FLEXPWM_SUB_MODULE_DIVIDER; pwm++) {
        isr = 0;
        switch(pwm) {
        case PWM_A:
            isr = (0x3 << 2) & cmpflags;
            break;
        case PWM_B:
            isr = (0x3 << 4) & cmpflags;
            break;
        case PWM_X:
            isr = (0x3 << 0) & cmpflags;
            break;
        }
        if ( isr ) {
            /* Flag set and the channel output. Find the corresponding channel.
             * IMPROVEMENT: Generate mapping from channel to config index to
             * avoid looping. */
            Pwm_ChannelType channel = GET_SUB_START_CHANNEL(hwUnit, sub) + pwm;
            for (Pwm_ChannelType i = 0; i < PWM_NUMBER_OF_CHANNELS; i++) {
                if( channel == PwmConfigPtr->Channels[i].index ) {
                    if( NULL != PwmConfigPtr->NotificationHandlers[i] ) {
                        PwmConfigPtr->NotificationHandlers[i]();
                    }
                    break;
                }
            }

        }
        // Clear interrupt
        flexHw->SUB[sub].STS.B.CMPF = isr;
    }
}
#endif /* PWM_NOTIFICATION_SUPPORED == STD_ON */

#if ( PWM_VERSION_INFO_API == STD_ON)
void Pwm_GetVersionInfo( Std_VersionInfoType* versioninfo) {

    /* @req SWS_Pwm_00151 */
    VALIDATE( ( NULL != versioninfo ), PWM_GETVERSIONINFO_SERVICE_ID, PWM_E_PARAM_POINTER);

    versioninfo->vendorID = PWM_VENDOR_ID;
    versioninfo->moduleID = PWM_MODULE_ID;
    versioninfo->sw_major_version = PWM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = PWM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = PWM_SW_PATCH_VERSION;

}
#endif

