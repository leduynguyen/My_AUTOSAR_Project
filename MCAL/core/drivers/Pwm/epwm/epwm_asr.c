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

#include "epwm.h"
#include "epwm_asr.h"
#include "Platform_Types.h"
#include "Pwm.h"
#include "Pwm_ConfigTypes.h"

#define PWM_DUTY_50_PERCENT			0x4000u
#define PWM_DUTY_100_PERCENT		0x8000u

#define EPWM_TBPRD_MAX				0xFFFFu

/**
 * Calculates the duty cycle as part of the period.
 * @param Period
 * @param DutyCycle
 * @return The duty value to write to the CMPA register.
 */
static uint16 calcDuty(Pwm_PeriodType Period, uint16 DutyCycle) {

    uint32 absoluteDuty = (Period * ((uint32) DutyCycle)) / PWM_DUTY_100_PERCENT;

    return absoluteDuty & 0xFFFFu;
}

/**
 * Set the prescaler for the ePWM clock. If a non supported value is passed
 * the prescaler will be set to 1.
 * @param PwmHandle
 * @param prescaler 1, 2, 4, 8, 16, 32, 64, 128 or 256 (HSPCLKDIV not fully supported)
 */
static void setPrescaler(PWM_Handle PwmHandle, uint32 prescaler) {

    PWM_ClkDiv_e clkDiv;
    PWM_HspClkDiv_e clkDivHsp = PWM_HspClkDiv_by_1;

    switch(prescaler) {
    case 1:
        clkDiv = PWM_ClkDiv_by_1;
        break;

    case 2:
        clkDiv = PWM_ClkDiv_by_2;
        break;

    case 4:
        clkDiv = PWM_ClkDiv_by_4;
        break;

    case 8:
        clkDiv = PWM_ClkDiv_by_8;
        break;

    case 16:
        clkDiv = PWM_ClkDiv_by_16;
        break;

    case 32:
        clkDiv = PWM_ClkDiv_by_32;
        break;

    case 64:
        clkDiv = PWM_ClkDiv_by_64;
        break;

    case 128:
        clkDiv = PWM_ClkDiv_by_128;
        break;

    case 256:
        clkDiv = PWM_ClkDiv_by_128;
        clkDivHsp = PWM_HspClkDiv_by_2;
        break;

    default:
        /* Non supported value => Do not prescale at all. */
        clkDiv = PWM_ClkDiv_by_1;
        break;
    }

    PWM_setClkDiv(PwmHandle, clkDiv);

    PWM_setHighSpeedClkDiv(PwmHandle, clkDivHsp);
}

/**
 * Sets the actions (set output high or low) for a Pwm channel when the
 * counter reaches the duty cycle and when it reaches the period.
 * @param PwmHandle
 * @param DutyCycle
 * @param Polarity
 */
static void setDutyActions(PWM_Handle PwmHandle, uint16 DutyCycle, Pwm_OutputStateType Polarity) {

    /* Special handling for 0% and 100% duty. */
    if ((DutyCycle == 0) || (DutyCycle == PWM_DUTY_100_PERCENT)) {

        PWM_setActionQual_CntUp_CmpA_PwmA(PwmHandle, PWM_ActionQual_Disabled);
        PWM_setActionQual_CntDown_CmpA_PwmA(PwmHandle, PWM_ActionQual_Disabled);

        if (DutyCycle == 0) {
            PWM_setActionQualContSWForce_PwmA(PwmHandle,
                    (Polarity == PWM_HIGH) ? PWM_ActionQualContSWForce_Clear : PWM_ActionQualContSWForce_Set);
        } else {
            PWM_setActionQualContSWForce_PwmA(PwmHandle,
                    (Polarity == PWM_HIGH) ? PWM_ActionQualContSWForce_Set : PWM_ActionQualContSWForce_Clear);
        }
    } else {

        if (Polarity == PWM_HIGH) {
            PWM_setActionQual_Zero_PwmA(PwmHandle, PWM_ActionQual_Set);
        } else {
            PWM_setActionQual_Zero_PwmA(PwmHandle, PWM_ActionQual_Clear);
        }

        /* With duty cycle reached, we toggle, regardless of polarity. */
        PWM_setActionQual_CntDown_CmpA_PwmA(PwmHandle, PWM_ActionQual_Disabled);
        PWM_setActionQual_CntUp_CmpA_PwmA(PwmHandle, PWM_ActionQual_Toggle);

        /* If the output previously has been set to forced high or low this will clear it. */
        PWM_setActionQualContSWForce_PwmA(PwmHandle, PWM_ActionQualContSWForce_Disabled);
    }
}

Std_ReturnType ePWM_FindFittingPrescaler(uint32 pwmClockHz, uint32 pwmFreq, uint32 *prescalerOut) {

    uint32 prescalerShift;
    uint32 prescaler;
    uint32 period;

    /* Supporting prescalers 1, 2, 4...256 */
    for (prescalerShift = 0; prescalerShift <= 8; prescalerShift++) {

        prescaler = 1uL << prescalerShift;

        period = (pwmClockHz / prescaler) / pwmFreq;

        /* Tpwm = TBPRD + 1. */
        if (period <= (EPWM_TBPRD_MAX + 1)) {

            *prescalerOut = prescaler;

            return E_OK;
        }
    }

    return E_NOT_OK;
}

uint16 ePWM_GetPeriod(PWM_Handle PwmHandle) {

    PWM_Obj *pwm = (PWM_Obj *)PwmHandle;

    return  pwm->TBPRD;
}

Std_ReturnType ePWM_InitChannel(PWM_Handle PwmHandle,
        uint32 pwmClockHz,
        uint32 prescaler,
        uint32 pwmFreq,
        uint16 DutyCycle,
        Pwm_OutputStateType Polarity) {

    uint16 absoluteDuty;
    uint32 period = (pwmClockHz / prescaler) / pwmFreq;

    if (period > (EPWM_TBPRD_MAX + 1)) {
        return E_NOT_OK;
    }

    absoluteDuty = calcDuty(period, DutyCycle);

    /* Check that the configured duty cycle can be achieved. */
    if ((DutyCycle > 0) && (absoluteDuty == 0)) {
        return E_NOT_OK;
    }

    PWM_Obj *pwm = (PWM_Obj *)PwmHandle;

    PWM_setCounterMode(PwmHandle, PWM_CounterMode_Stop);

    PWM_disableInt(PwmHandle);

    setPrescaler(PwmHandle, prescaler);

    /* Update period, duty, etc when the counter equals 0.
     * The default is 0 so no need to set.
     * PWM_setPeriodLoad(PwmHandle, PWM_PeriodLoad_Shadow);
     * PWM_setLoadMode_CmpA(PwmHandle, PWM_LoadMode_Zero);
     * PWM_setShadowMode_CmpA(PwmHandle, PWM_ShadowMode_Shadow);
     * AQSFRC &= ~(3 << RLDCSF);
     */

    pwm->TBCTR = 0;

    /* Tpwm = (TBPRD + 1) * Ttbclk */
    if (period > 0) {
        pwm->TBPRD = (uint16) ((period - 1) & 0xFFFFu);
        pwm->CMPA = absoluteDuty;
        setDutyActions(PwmHandle, DutyCycle, Polarity);
    } else {
        pwm->TBPRD = 0;
        pwm->CMPA = 0;
        setDutyActions(PwmHandle, 0, Polarity);
    }

    PWM_setIntPeriod(PwmHandle, PWM_IntPeriod_FirstEvent);

    ePwm_ClearInterrupts(PwmHandle);

    PWM_setCounterMode(PwmHandle, PWM_CounterMode_Up);

    return E_OK;
}

void ePWM_SetChannelToIdle(PWM_Handle PwmHandle, Pwm_OutputStateType IdleState) {

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
    EPWM_DISABLE_INTERRUPTS(PwmHandle);
#endif

    if (IdleState == PWM_HIGH) {
        PWM_setActionQualContSWForce_PwmA(PwmHandle, PWM_ActionQualContSWForce_Set);
    } else if (IdleState == PWM_LOW) {
        PWM_setActionQualContSWForce_PwmA(PwmHandle, PWM_ActionQualContSWForce_Clear);
    } else {
        /* Lint - All states are already covered. */
    }
}

Std_ReturnType ePWM_SetPeriodAndDuty(PWM_Handle PwmHandle, Pwm_PeriodType Period, uint16 DutyCycle,
        Pwm_OutputStateType Polarity, boolean EnableInterrupts) {

    PWM_Obj *pwm = (PWM_Obj*)PwmHandle;
    uint16 per;

    if (Period > (EPWM_TBPRD_MAX + 1)) {
        return E_NOT_OK;
    }

    if (Period > 0) {
        per = (Period - 1) & 0xFFFFu;
    } else {
        per = 0;
    }

    pwm->TBPRD = per;

    ePWM_SetDutyCycle(PwmHandle, (per == 0) ? 0 : DutyCycle, Polarity, EnableInterrupts);

    return E_OK;
}

void ePWM_SetDutyCycle(PWM_Handle PwmHandle, uint16 DutyCycle, Pwm_OutputStateType Polarity,
        boolean EnableInterrupts) {

    PWM_Obj *pwm = (PWM_Obj*)PwmHandle;

    uint32 period = pwm->TBPRD;

    /* If the period previously has been set to 0 the duty cycle
     * should be 0%. */
    if (period == 0) {
        DutyCycle = 0;
    }

    setDutyActions(PwmHandle, DutyCycle, Polarity);

    pwm->CMPA = calcDuty(period, DutyCycle);

    if ((DutyCycle == 0) || (DutyCycle == PWM_DUTY_100_PERCENT)) {
        PWM_disableInt(PwmHandle);
    } else if (EnableInterrupts) {
        PWM_enableInt(PwmHandle);
    } else {
        /* Nothing needs to be done, notifications are off. */
    }
}

void ePwm_ClearInterrupts(PWM_Handle PwmHandle) {

      PWM_Obj *pwm = (PWM_Obj *) PwmHandle;

      pwm->ETCLR = PWM_ETCLR_INT_BITS;
}

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
void ePWM_EnableNotification(PWM_Handle PwmHandle, Pwm_EdgeNotificationType Notification,
        Pwm_OutputStateType Polarity, ePWM_ChannelOutputStateType ChannelOutputState) {

    PWM_Obj *pwm = (PWM_Obj*)PwmHandle;

    switch(Notification) {

    case PWM_FALLING_EDGE:
        if (Polarity == PWM_HIGH) {
            PWM_setIntMode(PwmHandle, PWM_IntMode_CounterEqualCmpAIncr);
        } else if (Polarity == PWM_LOW) {
            PWM_setIntMode(PwmHandle, PWM_IntMode_CounterEqualZero);
        } else {
            /* All cases are handled already. */
        }
        break;

    case PWM_RISING_EDGE:
        if (Polarity == PWM_HIGH) {
            PWM_setIntMode(PwmHandle, PWM_IntMode_CounterEqualZero);
        } else if (Polarity == PWM_LOW) {
            PWM_setIntMode(PwmHandle, PWM_IntMode_CounterEqualCmpAIncr);
        } else {
            /* All cases are handled already. */
        }
        break;

    case PWM_BOTH_EDGES:
        if (Polarity == PWM_HIGH) {
            PWM_setIntMode(PwmHandle, PWM_IntMode_CounterEqualZero);
        } else if (Polarity == PWM_LOW) {
            PWM_setIntMode(PwmHandle, PWM_IntMode_CounterEqualCmpAIncr);
        } else {
            /* All cases are handled already. */
        }
        break;

    default:
        break;
    }

    /* Clear any pending interrupts before enabling. */
    pwm->ETCLR |= PWM_ETCLR_INT_BITS;

    /* Do not turn on interrupts if the output is flat, i.e. 0 or 100% duty cycle
     * because the interrupts are generated on timer matches and not real edges and
     * 0 and 100% duty cycle should not result in any interrupts. */
    if (ChannelOutputState == EPWM_MODULATING) {
        EPWM_ENABLE_INTERRUPTS(PwmHandle);
    }
}

void ePwm_ToggleEdgeDetection(PWM_Handle PwmHandle) {

    PWM_Obj *pwm = (PWM_Obj *) PwmHandle;

    uint16 interruptMode = pwm->ETSEL & PWM_ETSEL_INTSEL_BITS;

    if ((PWM_IntMode_e) interruptMode == PWM_IntMode_CounterEqualCmpAIncr) {
        PWM_setIntMode(PwmHandle, PWM_IntMode_CounterEqualZero);
    } else if ((PWM_IntMode_e) interruptMode == PWM_IntMode_CounterEqualZero) {
        PWM_setIntMode(PwmHandle, PWM_IntMode_CounterEqualCmpAIncr);
    } else {
        /* Unexpected state, do nothing. */
    }
}
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) */
