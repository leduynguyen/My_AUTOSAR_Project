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

/** @tagSettings DEFAULT_ARCHITECTURE=TMS570 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#include "Std_Types.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "Mcu.h"
#include "Os.h"
#include "Pwm.h"
#include "core_cr4.h"
#include "epwm_tms570.h"
#include "epwm.h"
#if PWM_NOTIFICATION_SUPPORTED==STD_ON
#include "isr.h"
#include "irq.h"
#include "arc.h"
#endif

#if defined(USE_DET)
#define Pwm_Det_ReportError(ApiId, ErrorId) Det_ReportError( PWM_MODULE_ID, 0, ApiId, ErrorId);
#else
#define Pwm_Det_ReportError(ApiId, ErrorId)
#endif

#if (PWM_DEV_ERROR_DETECT == STD_ON)
#define PWM_VALIDATE(_exp, _apiid, _errid) \
    if (!(_exp)) { \
        (void) Pwm_Det_ReportError( _apiid, _errid); \
        return; \
    }
#define PWM_VALIDATE_CHANNEL(_apiid, _ch) PWM_VALIDATE( (configuredChannels & (1 << _ch) ), _apiid, PWM_E_PARAM_CHANNEL)
#define PWM_VALIDATE_INITIALIZED(_apiid) PWM_VALIDATE( (Pwm_ModuleState == PWM_STATE_INITIALIZED), _apiid, PWM_E_UNINIT)
#define PWM_VALIDATE_UNINITIALIZED(_apiid) PWM_VALIDATE( (Pwm_ModuleState != PWM_STATE_INITIALIZED), _apiid, PWM_E_ALREADY_INITIALIZED)
#else
#define PWM_VALIDATE(_exp, _apiid, _errid)
#define PWM_VALIDATE_CHANNEL(_apiid, _ch)
#define PWM_VALIDATE_INITIALIZED(_apiid)
#define PWM_VALIDATE_UNINITIALIZED(_apiid)
#endif

#define PWM_APP							0u

#define PWM_DUTY_100_PERCENT			0x8000u

#if defined(CFG_TMS570LC43X)
/* TMS570LC43 ref manual, 6.1.1, ePWM CLocking and Reset.
 * The offset is the same in the SET and the CLR registers.
 * Write a 1 to the SET register to power down and a 1 to the
 * CLR register to power up. */
#define EPWM1_PSPWRDWN3_OFFSET			16u
#define EPWM2_PSPWRDWN3_OFFSET			17u
#define EPWM3_PSPWRDWN3_OFFSET			18u
#define EPWM4_PSPWRDWN3_OFFSET			19u
#define EPWM5_PSPWRDWN3_OFFSET			12u
#define EPWM6_PSPWRDWN3_OFFSET			13u
#define EPWM7_PSPWRDWN3_OFFSET			14u
#define EPWMX_PSPWRDWN3_POWER			1u
#define PINMMR166_0_EPWM_MAGIC_BIT		1u
#endif /* defined(CFG_TMS570LC43X) */

#define EPWM_TBCLKSYNC_OFFSET			1u
#define EPWM_TBCLKSYNC_ON				1u

const Pwm_ConfigType* PwmConfigPtr = NULL;

void* PwmBaseAddresses[7] = {
    (void*)PWM_ePWM1_BASE_ADDR,
    (void*)PWM_ePWM2_BASE_ADDR,
    (void*)PWM_ePWM3_BASE_ADDR,
    (void*)PWM_ePWM4_BASE_ADDR,
    (void*)PWM_ePWM5_BASE_ADDR,
    (void*)PWM_ePWM6_BASE_ADDR,
    (void*)PWM_ePWM7_BASE_ADDR
};
PWM_Handle PwmHandles[7];

typedef enum {
    PWM_STATE_UNINITIALIZED,
    PWM_STATE_INITIALIZED
} Pwm_ModuleStateType;

#if PWM_NOTIFICATION_SUPPORTED==STD_ON
#define PWM_NO_NOTIFICATION 0xFFu

// Run-time variables
typedef struct {
    uint16 DutyCycle;
    Pwm_PeriodType Period;
    uint8 NotificationState;
} Pwm_ChannelStructType;

// We use Pwm_ChannelType as index here
Pwm_ChannelStructType ChannelRuntimeStruct[PWM_TOTAL_NOF_CHANNELS];
#endif

#define PWM_IOMM_KICK0_MAGIC	((uint32) 0x83e70b13)
#define PWM_IOMM_KICK1_MAGIC	((uint32) 0x95a4f1e0)

#define AQSFRC_ACTSFA_MASK		0x0003
#define AQSFRC_ACTSFA_CLEAR		0x0001
#define AQSFRC_ACTSFA_SET		0x0002
#define AQSFRC_OTSFA_INIT		0x0004

static Pwm_ModuleStateType Pwm_ModuleState = PWM_STATE_UNINITIALIZED;

/* Local functions */
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
static void Pwm_Isr(uint8 channel);
ISR(Pwm1_Isr);
ISR(Pwm2_Isr);
ISR(Pwm3_Isr);
ISR(Pwm4_Isr);
ISR(Pwm5_Isr);
ISR(Pwm6_Isr);
ISR(Pwm7_Isr);
#endif

static void EnablePwmChannel(uint8 channel);
#if (PWM_DE_INIT_API == STD_ON)
static void DisablePwmChannel(uint8 channel);
#endif
static void EnableInterrupts(uint8 channel);
static uint16 calculateUpDownDuty(uint32 absoluteDuty, uint32 period);
#if ((PWM_SET_PERIOD_AND_DUTY_API == STD_ON) || (PWM_SET_DUTY_CYCLE_API == STD_ON))
static void Internal_SetDutyCycle(Pwm_ChannelType Channel, uint16 DutyCycle);
#endif

static uint8 channelConfigMap[PWM_TOTAL_NOF_CHANNELS];
/*
 * Store which physical channels have been configured in a bit field
 * 0 - not configured
 * 1 - configured
 */
static uint8 configuredChannels;


void Pwm_Init( const Pwm_ConfigType *ConfigPtr ) {

    uint8 i;

    /* @req SWS_Pwm_00118 */
    PWM_VALIDATE_UNINITIALIZED( PWM_INIT_SERVICE_ID );

    /* @req SWS_Pwm_00046
       @req SWS_Pwm_10120
       @req SWS_Pwm_20120 */
#if (PWM_STATICALLY_CONFIGURED == STD_OFF)
    PWM_VALIDATE((ConfigPtr != NULL), PWM_INIT_SERVICE_ID, PWM_E_PARAM_CONFIG);
#else
#error "PWM_STATICALLY_CONFIGURED is not supported"
#endif

    PwmConfigPtr = ConfigPtr;

    /* Unlock IOMM registers. */
    *((uint32*)PWM_IOMM_KICK0) = PWM_IOMM_KICK0_MAGIC;
    *((uint32*)PWM_IOMM_KICK1) = PWM_IOMM_KICK1_MAGIC;

    uint32 pwmClockHz = Mcu_Arc_GetPeripheralClock(PERIPHERAL_CLOCK_PWM);
    pwmClockHz /= 2; /* This is the default PWM prescaler on reset */

    /*
     * TMS570LS12X:
     * According to TI hardware manual SPNU515A
     * Section 19.2.2.3.2 specifies procedure for enabling PWM clocks:
     * Enable clocks in IOMM, set TBLCLKSYNC = 0, configure modules,
     * set TBLCLKSYNC = 1.
     *
     * TMS570LC43X:
     * The procedure is the same as for TMS570LS12X but the registers
     * to write to differ.
     */

    /* @req SWS_Pwm_00007 */
    /* @req SWS_Pwm_00062 */
    /* @req SWS_Pwm_00052 */
    for (i = 0; i < PWM_NUMBER_OF_CHANNELS; i++) {
        Pwm_ChannelType hwChannel = ConfigPtr->Channels[i].channel;
        PwmHandles[hwChannel] = PWM_init(PwmBaseAddresses[hwChannel], sizeof(PWM_Obj));
        EnablePwmChannel(hwChannel);
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        PWM_disableInt(PwmHandles[hwChannel]);
#endif
    }

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
    /* PINMM37[1] is TBLCLKSYNC. */
    *((uint32*)PWM_PINMMR37_BASE_ADDR) &= ~(EPWM_TBCLKSYNC_ON << EPWM_TBCLKSYNC_OFFSET);
#elif defined(CFG_TMS570LC43X)
    /* PINMMR166[1] is the TBCLKSYNC signal. This bit is clear ('0') by default. */
    /* Bit 0 of PINMMR166 also must be cleared for the enabling of Pwm channels to work.
     * The manual does not mention this at all. */
    *(PINMMR166_ADDR) &= ~((EPWM_TBCLKSYNC_ON << EPWM_TBCLKSYNC_OFFSET) | PINMMR166_0_EPWM_MAGIC_BIT);
#else
#error PWM has not been implemented for this MCU.
#endif

    /* @req SWS_Pwm_10009 */
    /* @req SWS_Pwm_20009 */
    /* @req SWS_Pwm_30009 */
    configuredChannels = 0;
    for (i = 0; i < PWM_NUMBER_OF_CHANNELS; i++) {

        Pwm_ChannelType hwChannel = ConfigPtr->Channels[i].channel;
        PWM_Obj *pwm = (PWM_Obj*)PwmHandles[hwChannel];
        channelConfigMap[hwChannel] = i; /*to use in interrupt handler/channel class*/
        configuredChannels |= (1 << hwChannel);
        PWM_setCounterMode(PwmHandles[hwChannel], PWM_CounterMode_UpDown);
        /* Indexing the config with i below is correct! */
        uint32 period = pwmClockHz / ConfigPtr->Channels[i].settings.frequency;

        /*
         * For updates at the end of period, leave default shadowing of CMPA on,
         * and write to the real register on period clock event.
         * For unbuffered updates, disable shadowing of the CMPA register.
         */
#if (PWM_DUTYCYCLE_UPDATED_ENDPERIOD == STD_ON)
        PWM_setShadowMode_CmpA(PwmHandles[hwChannel], PWM_ShadowMode_Shadow);
        PWM_setLoadMode_CmpA(PwmHandles[hwChannel], PWM_LoadMode_Zero);
#else
        PWM_setShadowMode_CmpA(PwmHandles[hwChannel], PWM_ShadowMode_Immediate);
#endif

        /* Hardware has a 16-bit TBPRD register, which denotes the
         * half-period value, so if period exceeds 65535 * 2, we have an invalid
         * config.
         */
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
        /* If we run PWM clock at 45 MHz, then PWM configured frequency would have
         * to be >= 344 Hz, approx. 2.9 ms
         * Period has to be >= 2 for it to make sense */
        PWM_VALIDATE((period <= 65535 * 2), PWM_INIT_SERVICE_ID, PWM_E_PARAM_CONFIG);
        PWM_VALIDATE((period >= 2), PWM_INIT_SERVICE_ID, PWM_E_PARAM_CONFIG);
#elif defined(CFG_TMS570LC43X)
        PWM_VALIDATE((period <= 65535 * 2), PWM_INIT_SERVICE_ID, PWM_E_PARAM_CONFIG);
        /* Improvement: Add another check for TMS570LC43X. */
#else
#error PWM has not been implemented for this MCU.
#endif
        uint16 configDuty = ConfigPtr->Channels[i].settings.duty;
        uint32 absoluteDuty = ((uint32)period * configDuty) >> 15;
        uint16 upDownDuty = calculateUpDownDuty(absoluteDuty, period);

        pwm->TBPRD = period / 2; /* TBPRD is @ half of PWM period in up-down mode */
        pwm->TBCTR = 0;
        pwm->CMPA = upDownDuty;

        /*
         * The hardware can produce two PWM outputs on each channel, A and B
         * In our driver, A has polarity as configured by the user
         * B happens through the deadband module
         */
        if (ConfigPtr->Channels[i].settings.polarity == PWM_HIGH) {
            /* Up-down PWM counter implies that we set the output
             * to the configured polarity when the counter is at 0
             * Then we toggle the output when the duty cycle compare
             * value is reached
             */
            PWM_setActionQual_Zero_PwmA(PwmHandles[hwChannel], PWM_ActionQual_Set);
        } else {
            PWM_setActionQual_Zero_PwmA(PwmHandles[hwChannel], PWM_ActionQual_Clear);
        }
        /* With duty cycle reached, we toggle, regardless of polarity */
        if (configDuty < PWM_50_PERCENT) { /* 50% is handled as counting down */
            PWM_setActionQual_CntUp_CmpA_PwmA(PwmHandles[hwChannel],
                    PWM_ActionQual_Toggle);
        } else {
            PWM_setActionQual_CntDown_CmpA_PwmA(PwmHandles[hwChannel],
                    PWM_ActionQual_Toggle);
        }
        /* Special handling for 0% and 100% duty to prevent two conflicting events
         * from firing in the HW, so just set the output to constant high or low
         */
        /* First disable since Pwm_DeInit could have been called
         * which will force the output to the idle mode. */
        PWM_setActionQualContSWForce_PwmA(PwmHandles[hwChannel], PWM_ActionQualContSWForce_Disabled);

        if ((configDuty == 0) || (configDuty == PWM_DUTY_100_PERCENT)) {
#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
            PWM_disableInt(PwmHandles[hwChannel]);
            ChannelRuntimeStruct[hwChannel].DutyCycle = PWM_0_PERCENT;
            ChannelRuntimeStruct[hwChannel].Period = 0;
#endif

            PWM_setActionQual_CntUp_CmpA_PwmA(PwmHandles[hwChannel], PWM_ActionQual_Disabled);

            if (configDuty == 0) {
                PWM_setActionQualContSWForce_PwmA(PwmHandles[hwChannel], ConfigPtr->Channels[i].settings.polarity == STD_HIGH ? PWM_ActionQualContSWForce_Clear : PWM_ActionQualContSWForce_Set);
            } else {
                PWM_setActionQualContSWForce_PwmA(PwmHandles[hwChannel], ConfigPtr->Channels[i].settings.polarity == STD_HIGH ? PWM_ActionQualContSWForce_Set : PWM_ActionQualContSWForce_Clear);
            }
        }else{
#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
            ChannelRuntimeStruct[hwChannel].DutyCycle = configDuty;
            ChannelRuntimeStruct[hwChannel].Period = period;
#endif
        }
        /* Dead-band setup. This is not part of Autosar but an extra feature
         * that can be desirable for TMS570 users
         */
        if (ConfigPtr->Channels[i].settings.deadband != 0)
        {
            uint32 dbPeriod = pwmClockHz / ConfigPtr->Channels[i].settings.deadband;
            PWM_setDeadBandInputMode(PwmHandles[hwChannel], PWM_DeadBandInputMode_EPWMxA_Rising_and_Falling);
            PWM_setDeadBandOutputMode(PwmHandles[hwChannel], PWM_DeadBandOutputMode_EPWMxA_Rising_EPWMxB_Falling);
            PWM_setDeadBandPolarity(PwmHandles[hwChannel], PWM_DeadBandPolarity_EPWMxB_Inverted);
            PWM_setDeadBandRisingEdgeDelay(PwmHandles[hwChannel], dbPeriod);
            PWM_setDeadBandFallingEdgeDelay(PwmHandles[hwChannel], dbPeriod);
        }

        /*
         * One more custom feature, an interrupt that always triggers in the middle of a period,
         * regardless of whether there is a rising/falling edge at that time.
         * Cannot be used together with the regular ASR-standard edge notification!
         */
        if (ConfigPtr->Channels[i].settings.midPeriodInterrupt == 1) {
            pwm->ETCLR |= (1 << 0);
            EnableInterrupts(hwChannel);
            PWM_setActionQual_Period_PwmA(PwmHandles[hwChannel], PWM_ActionQual_Disabled);
            PWM_setIntMode(PwmHandles[hwChannel], PWM_IntMode_CounterEqualZeroOrPeriod);
        }
    }

    /* Set TBLCKLSYNC to 1, HW init complete. */
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
    *((uint32*)PWM_PINMMR37_BASE_ADDR) |= (EPWM_TBCLKSYNC_ON << EPWM_TBCLKSYNC_OFFSET);
#elif defined(CFG_TMS570LC43X)
    *(PINMMR166_ADDR) |= (EPWM_TBCLKSYNC_ON << EPWM_TBCLKSYNC_OFFSET);
#else
#error PWM has not been implemented for this MCU.
#endif


#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
     ISR_INSTALL_ISR1( "Pwm1", Pwm1_Isr, PWM_CH1_INT, PWM_ISR_PRIORITY, PWM_APP );
     ISR_INSTALL_ISR1( "Pwm2", Pwm2_Isr, PWM_CH2_INT, PWM_ISR_PRIORITY, PWM_APP );
     ISR_INSTALL_ISR1( "Pwm3", Pwm3_Isr, PWM_CH3_INT, PWM_ISR_PRIORITY, PWM_APP );
     ISR_INSTALL_ISR1( "Pwm4", Pwm4_Isr, PWM_CH4_INT, PWM_ISR_PRIORITY, PWM_APP );
     ISR_INSTALL_ISR1( "Pwm5", Pwm5_Isr, PWM_CH5_INT, PWM_ISR_PRIORITY, PWM_APP );
     ISR_INSTALL_ISR1( "Pwm6", Pwm6_Isr, PWM_CH6_INT, PWM_ISR_PRIORITY, PWM_APP );
     ISR_INSTALL_ISR1( "Pwm7", Pwm7_Isr, PWM_CH7_INT, PWM_ISR_PRIORITY, PWM_APP );
#endif

     /* Lock IOMM registers */
     *((uint32*)PWM_IOMM_KICK0) = 0x00000000;

     Pwm_ModuleState = PWM_STATE_INITIALIZED;
}


/* @req SWS_Pwm_20080 */
#if (PWM_DE_INIT_API == STD_ON )
void Pwm_DeInit( void ) {

    PWM_VALIDATE_INITIALIZED( PWM_DEINIT_SERVICE_ID );

    uint8 i;

    /*
     * @req SWS_Pwm_00010
     * @req SWS_Pwm_00011
     * @req SWS_Pwm_00012
    */
    for (i = 0; i < PWM_NUMBER_OF_CHANNELS; i++) {

        Pwm_ChannelType hwChannel = PwmConfigPtr->Channels[i].channel;
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        Pwm_DisableNotification(hwChannel);
#endif
        Pwm_OutputStateType idleState = PwmConfigPtr->Channels[i].settings.idleState;
        if (idleState == PWM_HIGH) {
            PWM_setActionQualContSWForce_PwmA(PwmHandles[hwChannel], PWM_ActionQualContSWForce_Set);
        } else if (idleState == PWM_LOW) {
            PWM_setActionQualContSWForce_PwmA(PwmHandles[hwChannel], PWM_ActionQualContSWForce_Clear);
        } else {
            /* Lint - All states are already covered. */
        }

        DisablePwmChannel(hwChannel);
    }

    Pwm_ModuleState = PWM_STATE_UNINITIALIZED;
}
#endif

/* @req SWS_Pwm_20082 */
#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
void Pwm_SetDutyCycle( Pwm_ChannelType Channel, uint16 DutyCycle )
{
  PWM_VALIDATE_INITIALIZED( PWM_SETDUTYCYCLE_SERVICE_ID );
  PWM_VALIDATE_CHANNEL( PWM_SETDUTYCYCLE_SERVICE_ID, Channel );
  
  Internal_SetDutyCycle(Channel, DutyCycle);
}
#endif

/* @req SWS_Pwm_20083 */
#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
void Pwm_SetPeriodAndDuty(Pwm_ChannelType Channel, Pwm_PeriodType Period, uint16 DutyCycle) {

    PWM_VALIDATE_INITIALIZED( PWM_SETPERIODANDDUTY_SERVICE_ID );
    PWM_VALIDATE_CHANNEL( PWM_SETPERIODANDDUTY_SERVICE_ID, Channel );

    Pwm_ChannelType idx = channelConfigMap[Channel];

    /* @req SWS_PWM_00041 */
    if (PwmConfigPtr->Channels[idx].settings.class != PWM_VARIABLE_PERIOD) {

#if (PWM_DEV_ERROR_DETECT == STD_ON)
        Pwm_Det_ReportError(PWM_SETPERIODANDDUTY_SERVICE_ID, PWM_E_PERIOD_UNCHANGEABLE);
#endif /* (PWM_DEV_ERROR_DETECT == STD_ON) */

        return;
    }

    /* Currently the type Pwm_PeriodType is an uint16 so there is no need to check that
     * it is less than 65535 * 2. If the type is increased to uint32, reenable the check.
     * PWM_VALIDATE((Period <= (65535 * 2)), PWM_SETPERIODANDDUTY_SERVICE_ID, PWM_E_PARAM_CONFIG);
     */

    PWM_Obj *pwm = (PWM_Obj*)PwmHandles[Channel];
    pwm->TBPRD = Period / 2;

    /* @req SWS_Pwm_00150 */
    if (Period == 0) {
        Internal_SetDutyCycle(Channel, 0);
    } else {
        Internal_SetDutyCycle(Channel, DutyCycle);
    }
}
#endif

#if ((PWM_SET_PERIOD_AND_DUTY_API == STD_ON) || (PWM_SET_DUTY_CYCLE_API == STD_ON))
static void Internal_SetDutyCycle( Pwm_ChannelType Channel, uint16 DutyCycle ) {

    /* @req SWS_Pwm_00013
     * @req SWS_Pwm_00014
     * @req SWS_Pwm_00016
     * @req SWS_Pwm_20086
     */

    PWM_Obj *pwm = (PWM_Obj*)PwmHandles[Channel];
    uint32 period = pwm->TBPRD * 2;
    uint32 absoluteDuty = ((uint32)period * DutyCycle) >> 15;
    pwm->CMPA = calculateUpDownDuty(absoluteDuty, period);
    int idx = channelConfigMap[Channel];

    /* Set the compare action again: duty cycle may now be on
     * the other side of TBPRD (middle of period) */
    if ((DutyCycle == 0) || (DutyCycle >= PWM_DUTY_100_PERCENT)) {

        PWM_setActionQual_CntUp_CmpA_PwmA(PwmHandles[Channel], PWM_ActionQual_Disabled);
        PWM_setActionQual_CntDown_CmpA_PwmA(PwmHandles[Channel], PWM_ActionQual_Disabled);

        Pwm_OutputStateType polarity = PwmConfigPtr->Channels[idx].settings.polarity;

        if (DutyCycle == 0) {
            PWM_setActionQualContSWForce_PwmA(PwmHandles[Channel],
                    (polarity == PWM_HIGH) ? PWM_ActionQualContSWForce_Clear : PWM_ActionQualContSWForce_Set);
        } else {
            PWM_setActionQualContSWForce_PwmA(PwmHandles[Channel],
                    (polarity == PWM_HIGH) ? PWM_ActionQualContSWForce_Set : PWM_ActionQualContSWForce_Clear);
        }
#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
        PWM_disableInt(PwmHandles[Channel]);
        ChannelRuntimeStruct[Channel].DutyCycle = PWM_0_PERCENT;
        ChannelRuntimeStruct[Channel].Period = 0;
#endif
    } else {

        if (absoluteDuty <= pwm->TBPRD) {
            PWM_setActionQual_CntUp_CmpA_PwmA(PwmHandles[Channel], PWM_ActionQual_Toggle);
            PWM_setActionQual_CntDown_CmpA_PwmA(PwmHandles[Channel], PWM_ActionQual_Disabled);

        } else {
            PWM_setActionQual_CntDown_CmpA_PwmA(PwmHandles[Channel], PWM_ActionQual_Toggle);
            PWM_setActionQual_CntUp_CmpA_PwmA(PwmHandles[Channel], PWM_ActionQual_Disabled);
        }

        /* If the output previously has been set to forced high or low this will clear it. */
        PWM_setActionQualContSWForce_PwmA(PwmHandles[Channel], PWM_ActionQualContSWForce_Disabled);
#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
        EnableInterrupts(Channel);
        ChannelRuntimeStruct[Channel].Period = period;
        ChannelRuntimeStruct[Channel].DutyCycle = DutyCycle;
#endif
    }

    /* @req SWS_Pwm_00017
     * This requirement is to update duty cycle at the end of the period. That is the
     * default behaviour of the hardware, and this setting is changed in Pwm_Init if
     * PwmDutycycleUpdatedEndperiod was turned off
     */
}
#endif

/* @req SWS_Pwm_20112 */
/* @req SWS_Pwm_20113 */
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
void Pwm_DisableNotification(Pwm_ChannelType Channel) {

    PWM_VALIDATE_INITIALIZED( PWM_DISABLENOTIFICATION_SERVICE_ID );
    PWM_VALIDATE_CHANNEL( PWM_DISABLENOTIFICATION_SERVICE_ID, Channel );
    /* @req SWS_Pwm_00023 */
    PWM_disableInt(PwmHandles[Channel]);
    ChannelRuntimeStruct[Channel].NotificationState = PWM_NO_NOTIFICATION;
}

void Pwm_EnableNotification(Pwm_ChannelType Channel,
        Pwm_EdgeNotificationType Notification) {

    PWM_VALIDATE_CHANNEL( PWM_ENABLENOTIFICATION_SERVICE_ID, Channel );
    PWM_VALIDATE_INITIALIZED( PWM_ENABLENOTIFICATION_SERVICE_ID );

    uint8 idx = channelConfigMap[Channel];

    /*@req SWS_PWM_00081 */
    /* clear any pending interrupts before enable */
    PWM_Obj *pwm = (PWM_Obj*)PwmHandles[Channel];
    pwm->ETCLR |= (1 << 0);

    ChannelRuntimeStruct[Channel].NotificationState = (uint8)Notification;

    if(ChannelRuntimeStruct[Channel].DutyCycle != PWM_0_PERCENT){
        /* @req SWS_Pwm_00024 */
        EnableInterrupts(Channel);
    }

    Pwm_OutputStateType polarity = PwmConfigPtr->Channels[idx].settings.polarity;
    uint16 configDuty = ChannelRuntimeStruct[Channel].DutyCycle;
    uint8 cmpADirection = 0;
    if (configDuty < PWM_50_PERCENT) {/* 50% is handled as counting down */
        cmpADirection = 1;
    }

    /*
     * 	When should an interrupt be generated?
     * 	New PWM period begins on TBCTR = 0
     * 	Duty cycle is at TBCTR = CMPA in one of the directions
     * 	cmpADirection is 0 for down-count and 1 for up-count
     *	 |=================================|
     *   |            |  HIGH   |  LOW     |
     *   |FALLING     |  Duty   |  Zero    |
     *   |RISING      |  Zero   |  Duty    |
     *   |=================================|
     */

    PWM_IntMode_e mode = (cmpADirection == 1) ?
                                PWM_IntMode_CounterEqualCmpAIncr :
                                PWM_IntMode_CounterEqualCmpADecr;
    switch(Notification) {

    case PWM_FALLING_EDGE:
        if (polarity == PWM_HIGH) {
            PWM_setIntMode(PwmHandles[Channel], mode);
        } else if (polarity == PWM_LOW) {
            PWM_setIntMode(PwmHandles[Channel], PWM_IntMode_CounterEqualZero);
        }
        break;

    case PWM_RISING_EDGE:
        if (polarity == PWM_HIGH) {
            PWM_setIntMode(PwmHandles[Channel], PWM_IntMode_CounterEqualZero);
        } else if (polarity == PWM_LOW) {
            PWM_setIntMode(PwmHandles[Channel], mode);
        }
        break;

    case PWM_BOTH_EDGES:
        /* IMPROVEMENT: Add support for both-edge notification */
        break;
    }
}

ISR(Pwm1_Isr) {
    Pwm_Isr(PWM_CHANNEL_1);
}

ISR(Pwm2_Isr) {
    Pwm_Isr(PWM_CHANNEL_2);
}

ISR(Pwm3_Isr) {
    Pwm_Isr(PWM_CHANNEL_3);
}

ISR(Pwm4_Isr) {
    Pwm_Isr(PWM_CHANNEL_4);
}

ISR(Pwm5_Isr) {
    Pwm_Isr(PWM_CHANNEL_5);
}

ISR(Pwm6_Isr) {
    Pwm_Isr(PWM_CHANNEL_6);
}

ISR(Pwm7_Isr) {
    Pwm_Isr(PWM_CHANNEL_7);
}

static void Pwm_Isr(uint8 channel) {
    int idx = channelConfigMap[channel];
    PWM_Obj *pwm = (PWM_Obj*)PwmHandles[channel];
    uint16 intsel = pwm->ETSEL & (0x7);
    if (intsel == 3) { /* TBCTR = ZERO interrupt */
        if (PwmConfigPtr->ArcNotificationHandlers[idx] != NULL) {
            PwmConfigPtr->ArcNotificationHandlers[idx]();
        }
    } else {
        if (PwmConfigPtr->NotificationHandlers[idx] != NULL) {
            PwmConfigPtr->NotificationHandlers[idx]();
        }
    }
    pwm->ETCLR |= (1 << 0); /*clear pending interrupt flag */
}
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) */

/* @req SWS_Pwm_20084 */
#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
void Pwm_SetOutputToIdle(Pwm_ChannelType Channel) {
    PWM_VALIDATE_CHANNEL( PWM_SETOUTPUTTOIDLE_SERVICE_ID, Channel );
    PWM_VALIDATE_INITIALIZED( PWM_SETOUTPUTTOIDLE_SERVICE_ID );

    /* @req SWS_Pwm_00021 */
    Pwm_OutputStateType idleState = PwmConfigPtr->Channels[Channel].settings.idleState;
    if (idleState == PWM_HIGH) {
        PWM_setActionQualContSWForce_PwmA(PwmHandles[Channel],
                PWM_ActionQualContSWForce_Set);
    } else if (idleState == PWM_LOW) {
        PWM_setActionQualContSWForce_PwmA(PwmHandles[Channel],
                PWM_ActionQualContSWForce_Clear);
    }
#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
    PWM_disableInt(PwmHandles[Channel]);
    /* ChannelRuntimeStruct[Channel].Period = 0; Do not set this to zero because
     * later idle state can be removed by calling Pwm_SetDutyCycle() Api. If
     * this is set to zero then Pwm_SetDutyCycle() fails
     */
    ChannelRuntimeStruct[Channel].DutyCycle = PWM_0_PERCENT;
#endif
}
#endif

/* @req SWS_Pwm_20085 */
#if (PWM_GET_OUTPUT_STATE_API == STD_ON)
Pwm_OutputStateType Pwm_GetOutputState(Pwm_ChannelType Channel) {
    PWM_VALIDATE_CHANNEL(PWM_GETOUTPUTSTATE_SERVICE_ID, Channel)
    return PWM_LOW; /* IMPROVEMENT: implement Pwm_GetOutputState */
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


static void EnablePwmChannel(uint8 channel) {

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
    /* The register and bit to enable clock to each PWM are from
       the TI reference SPNS192A, sec. 5.1.1, table 5-1 */

    if (channel == 0) { /* PINMMR37[8] */
        *((uint32*)PWM_PINMMR37_BASE_ADDR) |= (1 << 8);
    } else if (channel == 1) { /* PINMMR37[16] */
        *((uint32*)PWM_PINMMR37_BASE_ADDR) |= (1 << 16);
    } else if (channel == 2) { /* PINMMR37[24] */
        *((uint32*)PWM_PINMMR37_BASE_ADDR) |= (1 << 24);
    } else if (channel == 3) { /* PINMMR38[0] */
        *((uint32*)PWM_PINMMR38_BASE_ADDR) |= (1 << 0);
    } else if (channel == 4) { /* PINMMR38[8] */
        *((uint32*)PWM_PINMMR38_BASE_ADDR) |= (1 << 8);
    } else if (channel == 5) { /* PINMMR38[16] */
        *((uint32*)PWM_PINMMR38_BASE_ADDR) |= (1 << 16);
    } else if (channel == 6) { /* PINMMR38[24] */
        *((uint32*)PWM_PINMMR38_BASE_ADDR) |= (1 << 24);
    } else {
        /* Channel does not exist. */
    }
#elif defined(CFG_TMS570LC43X)
    if (channel == 0) {
        pcrREG2->PSPWRDWNCLR3 |= (EPWMX_PSPWRDWN3_POWER << EPWM1_PSPWRDWN3_OFFSET);
    } else if (channel == 1) {
        pcrREG2->PSPWRDWNCLR3 |= (EPWMX_PSPWRDWN3_POWER << EPWM2_PSPWRDWN3_OFFSET);
    } else if (channel == 2) {
        pcrREG2->PSPWRDWNCLR3 |= (EPWMX_PSPWRDWN3_POWER << EPWM3_PSPWRDWN3_OFFSET);
    } else if (channel == 3) {
        pcrREG2->PSPWRDWNCLR3 |= (EPWMX_PSPWRDWN3_POWER << EPWM4_PSPWRDWN3_OFFSET);
    } else if (channel == 4) {
        pcrREG2->PSPWRDWNCLR3 |= (EPWMX_PSPWRDWN3_POWER << EPWM5_PSPWRDWN3_OFFSET);
    } else if (channel == 5) {
        pcrREG2->PSPWRDWNCLR3 |= (EPWMX_PSPWRDWN3_POWER << EPWM6_PSPWRDWN3_OFFSET);
    } else if (channel == 6) {
        pcrREG2->PSPWRDWNCLR3 |= (EPWMX_PSPWRDWN3_POWER << EPWM7_PSPWRDWN3_OFFSET);
    } else {
        /* Channel does not exist. */
    }
#else
#error PWM has not been implemented for this MCU.
#endif
}

#if (PWM_DE_INIT_API == STD_ON )
static void DisablePwmChannel(uint8 channel) {

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
    if (channel == 0) { /* PINMMR37[8] */
        *((uint32*) PWM_PINMMR37_BASE_ADDR) &= ~(1 << 8);
    } else if (channel == 1) { /* PINMMR37[16] */
        *((uint32*) PWM_PINMMR37_BASE_ADDR) &= ~(1 << 16);
    } else if (channel == 2) { /* PINMMR37[24] */
        *((uint32*) PWM_PINMMR37_BASE_ADDR) &= ~(1 << 24);
    } else if (channel == 3) { /* PINMMR38[0] */
        *((uint32*) PWM_PINMMR38_BASE_ADDR) &= ~(1 << 0);
    } else if (channel == 4) { /* PINMMR38[8] */
        *((uint32*) PWM_PINMMR38_BASE_ADDR) &= ~(1 << 8);
    } else if (channel == 5) { /* PINMMR38[16] */
        *((uint32*) PWM_PINMMR38_BASE_ADDR) &= ~(1 << 16);
    } else if (channel == 6) { /* PINMMR38[24] */
        *((uint32*) PWM_PINMMR38_BASE_ADDR) &= ~(1 << 24);
    } else {
        /* Channel does not exist. */
    }
#elif defined(CFG_TMS570LC43X)
    if (channel == 0) {
        pcrREG2->PSPWRDWNSET3 |= (EPWMX_PSPWRDWN3_POWER << EPWM1_PSPWRDWN3_OFFSET);
    } else if (channel == 1) {
        pcrREG2->PSPWRDWNSET3 |= (EPWMX_PSPWRDWN3_POWER << EPWM2_PSPWRDWN3_OFFSET);
    } else if (channel == 2) {
        pcrREG2->PSPWRDWNSET3 |= (EPWMX_PSPWRDWN3_POWER << EPWM3_PSPWRDWN3_OFFSET);
    } else if (channel == 3) {
        pcrREG2->PSPWRDWNSET3 |= (EPWMX_PSPWRDWN3_POWER << EPWM4_PSPWRDWN3_OFFSET);
    } else if (channel == 4) {
        pcrREG2->PSPWRDWNSET3 |= (EPWMX_PSPWRDWN3_POWER << EPWM5_PSPWRDWN3_OFFSET);
    } else if (channel == 5) {
        pcrREG2->PSPWRDWNSET3 |= (EPWMX_PSPWRDWN3_POWER << EPWM6_PSPWRDWN3_OFFSET);
    } else if (channel == 6) {
        pcrREG2->PSPWRDWNSET3 |= (EPWMX_PSPWRDWN3_POWER << EPWM7_PSPWRDWN3_OFFSET);
    } else {
        /* Channel does not exist. */
    }
#else
#error PWM has not been implemented for this MCU.
#endif
}
#endif

static void EnableInterrupts(uint8 channel) {
    if( ChannelRuntimeStruct[channel].NotificationState != PWM_NO_NOTIFICATION) {
        PWM_enableInt(PwmHandles[channel]);
        PWM_setIntPeriod(PwmHandles[channel], PWM_IntPeriod_FirstEvent);
    }
}

static uint16 calculateUpDownDuty(uint32 absoluteDuty, uint32 period) {
    if (absoluteDuty <= period / 2) {
        return absoluteDuty;
    } else {
        return (period / 2) - (absoluteDuty - (period / 2));
    }
}
