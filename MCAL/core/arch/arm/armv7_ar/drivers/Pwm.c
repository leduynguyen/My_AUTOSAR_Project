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


/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#include "arc_assert.h"
#include <string.h>

#include "Pwm.h"
#include "Mcu.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "zynq.h"
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON) && !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
#include "isr.h"
#include "irq_zynq.h"
#endif
#include "Os.h"

// General requirements implemented/inspected
/* @req SWS_Pwm_00100  */
/* @req SWS_Pwm_10051  */
/* @req SWS_Pwm_10075  */
/* @req SWS_Pwm_10083  */
/* @req SWS_Pwm_00101  */
/* @req SWS_Pwm_00102  */
/* @req SWS_Pwm_00103  */
/* @req SWS_Pwm_00105  */
/* @req SWS_Pwm_00108  */
/* @req SWS_Pwm_00109  */
/* @req SWS_Pwm_00110  */
/* @req SWS_Pwm_20051  */
/* @req SWS_Pwm_20069  */
/* @req SWS_Pwm_20083  */
/* @req SWS_Pwm_00058  */
/* @req SWS_Pwm_00088  */
/* @req SWS_Pwm_00095  */
/* @req SWS_Pwm_00096  */
/* @req SWS_Pwm_00097  */
/* @req SWS_Pwm_00098  */
/* @req SWS_Pwm_00099  */
/* @req SWS_Pwm_00070 All time units should be ticks*/
/* @req SWS_Pwm_00104 Optional Interfaces. Partly implemented, we don't use DEM. */
/* @req SWS_Pwm_00094 Imported types. Partly implemented, Dem not used. */
/* @req SWS_Pwm_00106 Pwm_ChannelType */
/* @req SWS_Pwm_00107 Pwm_PeriodType */
/* @req SWS_Pwm_00111 Pwm_ConfigType */
/* @req SWS_Pwm_00061 Pwm_ConfigType contains initialization data for the PWM driver*/
/* @req SWS_Pwm_00079 Note that 10120 and 20120 not supported, but otherwise precompile variant supported  */


#if ( PWM_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void) Det_ReportError(PWM_MODULE_ID,0,_api,_err); \
          return; \
        }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
        if( !(_exp) ) { \
          (void) Det_ReportError(PWM_MODULE_ID,0,_api,_err); \
          return (_rv); \
        }
#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_W_RV(_exp,_api,_err,_rv )
#endif


#define PWM_RUNTIME_CHANNEL_COUNT	6u
#define IS_VALID_CHANNEL(_x) ((_x) < 6u)

/* Definitions for configuring Triple Timer Counter (TTC)
 * according to Zynq-7000 TRM, App. B.32
 */

#define CHANNEL_0                   0u
#define CHANNEL_1                   1u
#define CHANNEL_2                   2u
#define CHANNEL_3                   3u
#define CHANNEL_4                   4u
#define CHANNEL_5                   5u

#define MATCH_REG_1					0u
#define MATCH_REG_2					1u
#define MATCH_REG_3					2u

#define CLK_CNTRL_PS_EN_MASK		0x00000001u  /**< Prescale enable */
#define CLK_CNTRL_PS_VAL_MASK		0x0000001Eu  /**< Prescale value */
#define CLK_CNTRL_PS_VAL_SHIFT				 1u  /**< Prescale shift */
#define CNT_CNTRL_RESET_VALUE		0x00000021u  /**< Reset value */
#define CNT_CNTRL_DIS_MASK			0x00000001u  /**< Disable the counter */
#define CNT_CNTRL_INT_MASK			0x00000002u  /**< Interval mode */
#define CNT_CNTRL_DECR_MASK			0x00000004u  /**< Decrement mode */
#define CNT_CNTRL_MATCH_MASK		0x00000008u  /**< Match mode */
#define CNT_CNTRL_RST_MASK			0x00000010u  /**< Reset counter */
#define CNT_CNTRL_EN_WAVE_MASK		0x00000020u  /**< Enable waveform */
#define CNT_CNTRL_POL_WAVE_MASK		0x00000040u  /**< Waveform polarity */

#define IXR_INTERVAL_MASK			0x00000001u  /**< Interval Interrupt */
#define IXR_MATCH_0_MASK			0x00000002u  /**< Match 1 Interrupt */
#define IXR_MATCH_1_MASK			0x00000004u  /**< Match 2 Interrupt */
#define IXR_MATCH_2_MASK			0x00000008u  /**< Match 3 Interrupt */
#define IXR_CNT_OVR_MASK			0x00000010u  /**< Counter Overflow */
#define IXR_ALL_MASK				0x0000001Fu  /**< All valid Interrupts */

#define HUNDRED_PERCENT_DUTY_CYCLE	0x8000u

typedef enum {
    PWM_STATE_UNINITIALIZED, PWM_STATE_INITIALIZED
} Pwm_ModuleStateType;

static Pwm_ModuleStateType Pwm_ModuleState = PWM_STATE_UNINITIALIZED;

const Pwm_ConfigType* PwmConfigPtr = NULL;
uint16 Pwm_chnLastSetDuty[PWM_MAX_CHANNEL] = {0};

/* Set SFR registers of Pwm properly.*/
typedef volatile struct TTC_reg Pwm_TtcHwRegType;
/*lint -e{923} cast from unsigned int to pointer MISRA 2004 11.1 11.3 2012 11.4 11.6
 * Integer to pointer casting is necessary to set SFR of Microcontroller. */
static Pwm_TtcHwRegType* const TTC0_PTR = (Pwm_TtcHwRegType*)ZYNQ_TTC0_BASE;
/*lint -e{923} cast from unsigned int to pointer MISRA 2004 11.1 11.3 2012 11.4 11.6
 * Integer to pointer casting is necessary to set SFR of Microcontroller.*/
static Pwm_TtcHwRegType* const TTC1_PTR = (Pwm_TtcHwRegType*)ZYNQ_TTC1_BASE;


#if PWM_DE_INIT_API==STD_ON
static void Pwm_DeInitChannel(Pwm_ChannelType Channel);
#endif

#if PWM_NOTIFICATION_SUPPORTED==STD_ON
ISR(Pwm_0_Isr);
ISR(Pwm_1_Isr);
ISR(Pwm_2_Isr);
ISR(Pwm_3_Isr);
ISR(Pwm_4_Isr);
ISR(Pwm_5_Isr);
#endif

static void calcPeriodTicksAndPrescaler(
        const Pwm_ChannelConfigurationType* channelConfig,
        Pwm_PeriodType* ticks, Pwm_ChannelPrescalerType* prescaler) {

    uint32_t f_in = MCU_ARC_CLOCK_ARM_CPU_1X_FREQUENCY;

    uint32_t f_target = channelConfig->frequency;

    Pwm_ChannelPrescalerType pre;
    uint32_t ticks_temp;

    // Go from lowest to highest prescaler
    /*lint -e9027 -e641 -e737
     * Unpermitted operand to operator '++' and '+' Misra 2012 10.1
     * Converting enum 'Pwm_ChannelPrescalerType' to 'int'
     * Tolerable: working on enumeration with For cycle results more simplified and readable code. */
    if (channelConfig->prescaler == PWM_CHANNEL_PRESCALER_AUTO) {
        for (pre = PWM_CHANNEL_PRESCALER_NONE; pre <= PWM_CHANNEL_PRESCALER_15; pre++) {
            ticks_temp = f_in / (f_target * ((uint32)1u << (pre + 1u))); // Calc ticks
            if (ticks_temp > 0xffffu) {
                ticks_temp = 0xffffu;  // Prescaler too low
            } else {
                break;                // Prescaler ok
            }
        }
    } else {
        pre = channelConfig->prescaler; // Use config setting
        ticks_temp = f_in / (f_target * ((uint32)1u << (pre+1u))); // Calc ticks
        if (ticks_temp > 0xffff) {
            ticks_temp = 0xffff;  // Prescaler too low
        }
    }
    /*lint -restore*/

    (*ticks) = (Pwm_PeriodType) ticks_temp;
    (*prescaler) = pre;
}

/**
 * Write a value to the Clock Control register for the selected TTC channel
 *
 */
static void SetClockControl(Pwm_ChannelType channel, uint8_t clock_control_value)
{
    switch (channel)
    {
        case CHANNEL_0:
            TTC0_PTR->CLOCK_CONTROL_1 = clock_control_value;
            break;
        case CHANNEL_1:
            TTC0_PTR->CLOCK_CONTROL_2 = clock_control_value;
            break;
        case CHANNEL_2:
            TTC0_PTR->CLOCK_CONTROL_3 = clock_control_value;
            break;
        case CHANNEL_3:
            TTC1_PTR->CLOCK_CONTROL_1 = clock_control_value;
            break;
        case CHANNEL_4:
            TTC1_PTR->CLOCK_CONTROL_2 = clock_control_value;
            break;
        case CHANNEL_5:
            TTC1_PTR->CLOCK_CONTROL_3 = clock_control_value;
            break;
        default:
            break;
    }

}

/**
 * Read the Clock Control register for the selected TTC channel
 *
 */
static uint8_t GetClockControl(Pwm_ChannelType channel)
{
    switch (channel)
    {
        case CHANNEL_0:
            return (uint8_t) TTC0_PTR->CLOCK_CONTROL_1;
        case CHANNEL_1:
            return (uint8_t) TTC0_PTR->CLOCK_CONTROL_2;
        case CHANNEL_2:
            return (uint8_t) TTC0_PTR->CLOCK_CONTROL_3;
        case CHANNEL_3:
            return (uint8_t) TTC1_PTR->CLOCK_CONTROL_1;
        case CHANNEL_4:
            return (uint8_t) TTC1_PTR->CLOCK_CONTROL_2;
        case CHANNEL_5:
            return (uint8_t) TTC1_PTR->CLOCK_CONTROL_3;
        default:
            return (uint8_t) 0u;
    }

}

/**
 * Write a value to the Counter Control register for the selected TTC channel
 *
 */
static void SetCounterControl(Pwm_ChannelType channel, uint8_t counter_control_value)
{
    switch (channel)
    {
        case CHANNEL_0:
            TTC0_PTR->COUNTER_CONTROL_1 = counter_control_value;
            break;
        case CHANNEL_1:
            TTC0_PTR->COUNTER_CONTROL_2 = counter_control_value;
            break;
        case CHANNEL_2:
            TTC0_PTR->COUNTER_CONTROL_3 = counter_control_value;
            break;
        case CHANNEL_3:
            TTC1_PTR->COUNTER_CONTROL_1 = counter_control_value;
            break;
        case CHANNEL_4:
            TTC1_PTR->COUNTER_CONTROL_2 = counter_control_value;
            break;
        case CHANNEL_5:
            TTC1_PTR->COUNTER_CONTROL_3 = counter_control_value;
            break;
        default:
            break;
    }

}
/**
 * Read the Counter Control register for the selected TTC channel
 *
 */

static uint8_t GetCounterControl(Pwm_ChannelType channel)
{
    switch (channel)
    {
        case CHANNEL_0:
            return (uint8_t) TTC0_PTR->COUNTER_CONTROL_1;
        case CHANNEL_1:
            return (uint8_t) TTC0_PTR->COUNTER_CONTROL_2;
        case CHANNEL_2:
            return (uint8_t) TTC0_PTR->COUNTER_CONTROL_3;
        case CHANNEL_3:
            return (uint8_t) TTC1_PTR->COUNTER_CONTROL_1;
        case CHANNEL_4:
            return (uint8_t) TTC1_PTR->COUNTER_CONTROL_2;
        case CHANNEL_5:
            return (uint8_t) TTC1_PTR->COUNTER_CONTROL_3;
        default:
            return (uint8_t) 0u;
    }

}

/*This part of the code is never referenced*/
#if 0
/**
 *  Read the Counter Control register for the selected TTC channel
 *
 */
static uint16_t GetCounterRegValue(Pwm_ChannelType channel)
{
    switch (channel)
    {
        case CHANNEL_0:
            return (uint16_t) TTC0_PTR->COUNTER_VALUE_1;
        case CHANNEL_1:
            return (uint16_t) TTC0_PTR->COUNTER_VALUE_2;
        case CHANNEL_2:
            return (uint16_t) TTC0_PTR->COUNTER_VALUE_3;
        case CHANNEL_3:
            return (uint16_t) TTC1_PTR->COUNTER_VALUE_1;
        case CHANNEL_4:
            return (uint16_t) TTC1_PTR->COUNTER_VALUE_2;
        case CHANNEL_5:
            return (uint16_t) TTC1_PTR->COUNTER_VALUE_3;
        default:
            return (uint16_t) 0u;
    }

}
#endif

/**
 * Read the Interval Counter register for the selected TTC channel
 *
 */
static Pwm_PeriodType GetIntervalCounter(Pwm_ChannelType channel)
{
    switch (channel)
    {
        case CHANNEL_0:
            return (Pwm_PeriodType) TTC0_PTR->INTERVAL_COUNTER_1;
        case CHANNEL_1:
            return (Pwm_PeriodType) TTC0_PTR->INTERVAL_COUNTER_2;
        case CHANNEL_2:
            return (Pwm_PeriodType) TTC0_PTR->INTERVAL_COUNTER_3;
        case CHANNEL_3:
            return (Pwm_PeriodType) TTC1_PTR->INTERVAL_COUNTER_1;
        case CHANNEL_4:
            return (Pwm_PeriodType) TTC1_PTR->INTERVAL_COUNTER_2;
        case CHANNEL_5:
            return (Pwm_PeriodType) TTC1_PTR->INTERVAL_COUNTER_3;
        default:
            return (Pwm_PeriodType) 0u;
    }

}

/**
 * Write a value to the Interval counter register for the selected TTC channel
 *
 */
static void SetIntervalCounter(Pwm_ChannelType channel, Pwm_PeriodType value)
{

    switch (channel)
    {
    case CHANNEL_0:
        TTC0_PTR->INTERVAL_COUNTER_1 = value;
        break;
    case CHANNEL_1:
        TTC0_PTR->INTERVAL_COUNTER_2 = value;
        break;
    case CHANNEL_2:
        TTC0_PTR->INTERVAL_COUNTER_3 = value;
        break;
    case CHANNEL_3:
        TTC1_PTR->INTERVAL_COUNTER_1 = value;
        break;
    case CHANNEL_4:
        TTC1_PTR->INTERVAL_COUNTER_2 = value;
        break;
    case CHANNEL_5:
        TTC1_PTR->INTERVAL_COUNTER_3 = value;
        break;
    default:
        break;
    }


}

/**
 * Write a value to the Match 1 counter register for the selected TTC channel
 *
 */
static void SetMatchCounter1(Pwm_ChannelType channel, uint16_t value)
{

    switch (channel)
    {
    case CHANNEL_0:
        TTC0_PTR->MATCH_1_COUNTER_1 = value;
        break;
    case CHANNEL_1:
        TTC0_PTR->MATCH_1_COUNTER_2 = value;
        break;
    case CHANNEL_2:
        TTC0_PTR->MATCH_1_COUNTER_3 = value;
        break;
    case CHANNEL_3:
        TTC1_PTR->MATCH_1_COUNTER_1 = value;
        break;
    case CHANNEL_4:
        TTC1_PTR->MATCH_1_COUNTER_2 = value;
        break;
    case CHANNEL_5:
        TTC1_PTR->MATCH_1_COUNTER_3 = value;
        break;
    default:
        break;
    }

}

/**
 * Write a value to the Match 2 counter register for the selected TTC channel
 *
 */
static void SetMatchCounter2(Pwm_ChannelType channel, uint16_t value)
{

    switch (channel)
    {
    case CHANNEL_0:
        TTC0_PTR->MATCH_2_COUNTER_1 = value;
        break;
    case CHANNEL_1:
        TTC0_PTR->MATCH_2_COUNTER_2 = value;
        break;
    case CHANNEL_2:
        TTC0_PTR->MATCH_2_COUNTER_3 = value;
        break;
    case CHANNEL_3:
        TTC1_PTR->MATCH_2_COUNTER_1 = value;
        break;
    case CHANNEL_4:
        TTC1_PTR->MATCH_2_COUNTER_2 = value;
        break;
    case CHANNEL_5:
        TTC1_PTR->MATCH_2_COUNTER_3 = value;
        break;
    default:
        break;
    }

}

/**
 * Write a value to the Match 3 counter register for the selected TTC channel
 *
 */
static void SetMatchCounter3(Pwm_ChannelType channel, uint16_t value)
{

    switch (channel)
    {
    case CHANNEL_0:
        TTC0_PTR->MATCH_3_COUNTER_1 = value;
        break;
    case CHANNEL_1:
        TTC0_PTR->MATCH_3_COUNTER_2 = value;
        break;
    case CHANNEL_2:
        TTC0_PTR->MATCH_3_COUNTER_3 = value;
        break;
    case CHANNEL_3:
        TTC1_PTR->MATCH_3_COUNTER_1 = value;
        break;
    case CHANNEL_4:
        TTC1_PTR->MATCH_3_COUNTER_2 = value;
        break;
    case CHANNEL_5:
        TTC1_PTR->MATCH_3_COUNTER_3 = value;
        break;
    default:
        break;
    }

}

/**
 * Write a value to the Match counter register for the selected TTC channel and Match regnumber
 *
 */

static void SetMatchCounter(Pwm_ChannelType channel, uint8_t reg_num, uint16_t value)
{

    switch (reg_num)
    {

    case MATCH_REG_1:
        SetMatchCounter1(channel, value);
        break;

    case MATCH_REG_2:
        SetMatchCounter2(channel, value);
        break;

    case MATCH_REG_3:
        SetMatchCounter3(channel, value);
        break;

    default:
        break;

    }
}

/**
 * Write a value to the Interrupt Enable register for the selected TTC channel
 *
 */
static void SetInterruptEnable(Pwm_ChannelType channel, uint8_t value)
{
    switch (channel)
    {
        case CHANNEL_0:
            TTC0_PTR->INTERRUPT_ENABLE_1 = value;
            break;
        case CHANNEL_1:
            TTC0_PTR->INTERRUPT_ENABLE_2 = value;
            break;
        case CHANNEL_2:
            TTC0_PTR->INTERRUPT_ENABLE_3 = value;
            break;
        case CHANNEL_3:
            TTC1_PTR->INTERRUPT_ENABLE_1 = value;
            break;
        case CHANNEL_4:
            TTC1_PTR->INTERRUPT_ENABLE_2 = value;
            break;
        case CHANNEL_5:
            TTC1_PTR->INTERRUPT_ENABLE_3 = value;
            break;
        default:
            break;
    }
}

/*This part of the code is never referenced*/
#if 0
/**
 * Read value from the Interrupt Enable register for the selected TTC channel
 *
 */
static uint8_t GetInterruptEnable(Pwm_ChannelType channel)
{
    switch (channel)
    {
        case CHANNEL_0:
            return (uint8_t)TTC0_PTR->INTERRUPT_ENABLE_1;
        case CHANNEL_1:
            return (uint8_t)TTC0_PTR->INTERRUPT_ENABLE_2;
        case CHANNEL_2:
            return (uint8_t)TTC0_PTR->INTERRUPT_ENABLE_3;
        case CHANNEL_3:
            return (uint8_t)TTC1_PTR->INTERRUPT_ENABLE_1;
        case CHANNEL_4:
            return (uint8_t)TTC1_PTR->INTERRUPT_ENABLE_2;
        case CHANNEL_5:
            return (uint8_t)TTC1_PTR->INTERRUPT_ENABLE_3;
        default:
            break;
    }

    return 0;
}
#endif

/**
 * Read value from the Interrupt Register for the selected TTC channel
 *
 */
/** @req SWS_Pwm_00026 */
static uint8_t GetInterruptRegister(Pwm_ChannelType channel)
{
    switch (channel)
    {
        case CHANNEL_0:
            return (uint8_t)TTC0_PTR->INTERRUPT_REGISTER_1;
        case CHANNEL_1:
            return (uint8_t)TTC0_PTR->INTERRUPT_REGISTER_2;
        case CHANNEL_2:
            return (uint8_t)TTC0_PTR->INTERRUPT_REGISTER_3;
        case CHANNEL_3:
            return (uint8_t)TTC1_PTR->INTERRUPT_REGISTER_1;
        case CHANNEL_4:
            return (uint8_t)TTC1_PTR->INTERRUPT_REGISTER_2;
        case CHANNEL_5:
            return (uint8_t)TTC1_PTR->INTERRUPT_REGISTER_3;
        default:
            break;
    }

    return 0;
}

/**
 * Change period and duty cycle for a channel.
 * @param Channel
 * @param Period in ticks
 * @param DutyCycle 0 <= DutyCycle <= 0x8000
 */
static void changePeriod(Pwm_ChannelType channel, Pwm_PeriodType periodTicks, uint16 dutyCycle)
{
    // Disable TTC
    uint8_t counter_control_value = GetCounterControl(channel);
    uint16  tempDutyCycle = dutyCycle;

    /* @req SWS_Pwm_00150 If the period is zero then the output shall be zero (zero percent duty-cycle). */
    tempDutyCycle = (periodTicks == 0) ? 0UL : dutyCycle;
    Pwm_chnLastSetDuty[channel] = tempDutyCycle;

    SetCounterControl(channel, (counter_control_value | CNT_CNTRL_DIS_MASK));

    // Interval mode + Match Mode + Waveform Disabled
    counter_control_value |= (CNT_CNTRL_INT_MASK | CNT_CNTRL_MATCH_MASK | CNT_CNTRL_EN_WAVE_MASK ) ;
    SetCounterControl(channel, counter_control_value | CNT_CNTRL_DIS_MASK);

    // SET PERIOD: Set Interval to PeriodTicks
    SetIntervalCounter (channel, periodTicks);

    if (tempDutyCycle > PWM_100_PERCENT) {
        tempDutyCycle = PWM_100_PERCENT;
#if PWM_DEV_ERROR_DETECT==STD_ON
        (void)Det_ReportError(PWM_MODULE_ID,0,PWM_GLOBAL_SERVICE_ID, PWM_E_EXECUTION_ERROR);
#endif
    }
    /** @req SWS_Pwm_00018 */
    /** @req SWS_PWM_10009 */
    /** @req SWS_PWM_20009 */
    /** @req SWS_PWM_30009 */
    /** @req SWS_PWM_00059 */
    // SET DUTY CYCLE: Set Match value depending on duty cycle value
    SetMatchCounter(channel, MATCH_REG_1, (uint16_t) (((uint32) periodTicks * (uint32) tempDutyCycle) >> 15u));

    // Enable TTC and output waveform to Start the counter
    /** @req SWS_PWM_10009 */
    counter_control_value = GetCounterControl(channel);
    counter_control_value &= ~CNT_CNTRL_DIS_MASK;
    counter_control_value &= ~CNT_CNTRL_EN_WAVE_MASK;
    counter_control_value |= CNT_CNTRL_RST_MASK;
    SetCounterControl(channel, counter_control_value);
}

/**
 * Configure channel characteristics in TTC
 *
 * The function Pwm_Init shall start all PWM channels with the configured
    default values. If the duty cycle parameter equals:
    􀂃 0% or 100% : Then the PWM output signal shall be in the state according to
        the configured polarity parameter
    􀂃 >0% and <100%: Then the PWM output signal shall be modulated according
    to parameters period, duty cycle and configured polarity.

    A duty cycle of X % should give a signal with state 'channelConfig->polarity' during
     X % of the period time.
 *
 */
static void configureChannel(const Pwm_ChannelConfigurationType* channelConfig){

    Pwm_ChannelType channel = channelConfig->channel;
    Pwm_ChannelPrescalerType prescaler;
    Pwm_PeriodType periodTicks = 0u;    /* Period value in ticks from configuration. */

    // Define clock and prescaler
    /*lint -e{934} Taking address of near auto variable Using stack pointer as argument is tolerable.*/
    calcPeriodTicksAndPrescaler( channelConfig, &periodTicks, &prescaler );

    uint8_t clock_control_value = GetClockControl(channel);
    if (prescaler == PWM_CHANNEL_PRESCALER_NONE ) {
        /* Disable prescaler */
        clock_control_value &= ~CLK_CNTRL_PS_EN_MASK;
    }
    else
    {
        /*lint -e{571} Suspecious cast
         * Tolerable: Using the values of each enumeration for arithmetic operation results more simplified and readable code.*/
        clock_control_value |=	((uint32)prescaler << 1u) & (uint32)CLK_CNTRL_PS_VAL_MASK;
        clock_control_value |= CLK_CNTRL_PS_EN_MASK;
    }

    SetClockControl(channel, clock_control_value);

    // Disable TTC
    uint8_t counter_control_value = GetCounterControl(channel);
    SetCounterControl(channel, (counter_control_value | CNT_CNTRL_DIS_MASK));

    // Set polarity
    if (channelConfig->polarity == PWM_HIGH)
    {
        counter_control_value |= CNT_CNTRL_POL_WAVE_MASK;
    }
    else
    {
        counter_control_value &= ~CNT_CNTRL_POL_WAVE_MASK;
    }
    SetCounterControl(channel, (counter_control_value | CNT_CNTRL_DIS_MASK));

    changePeriod(channel, periodTicks, channelConfig->duty);
}

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON) && !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
static void installChannelInterrupt(uint8 chnl)
{
    switch (chnl) {
        case CHANNEL_0:
            /* Install ISR. IRQ ID#42 */
            ISR_INSTALL_ISR2("PwmIsr", Pwm_0_Isr, (IrqType)(IRQ_TTC_0_0),PWM_ISR_PRIORITY, 0);
            break;

        case CHANNEL_1:
            /* Install ISR. IRQ ID#43 */
            ISR_INSTALL_ISR2("PwmIsr", Pwm_1_Isr, (IrqType)(IRQ_TTC_0_1),PWM_ISR_PRIORITY, 0);
            break;

        case CHANNEL_2:
            /* Install ISR. IRQ ID#44 */
            ISR_INSTALL_ISR2("PwmIsr", Pwm_2_Isr, (IrqType)(IRQ_TTC_0_2),PWM_ISR_PRIORITY, 0);
            break;

        case CHANNEL_3:
            /* Install ISR. IRQ ID#69 */
            ISR_INSTALL_ISR2("PwmIsr", Pwm_3_Isr, (IrqType)(IRQ_TTC_1_0),PWM_ISR_PRIORITY, 0);
            break;

        case CHANNEL_4:
            /* Install ISR. IRQ ID#70 */
            ISR_INSTALL_ISR2("PwmIsr", Pwm_4_Isr, (IrqType)(IRQ_TTC_1_1),PWM_ISR_PRIORITY, 0);
            break;

        case CHANNEL_5:
            /* Install ISR. IRQ ID#71 */
            ISR_INSTALL_ISR2("PwmIsr", Pwm_5_Isr, (IrqType)(IRQ_TTC_1_2),PWM_ISR_PRIORITY, 0);
            break;

        default:
            break;
    }
}
#endif /* PWM_NOTIFICATION_SUPPORED == STD_ON */

/**
 * Service for PWM initialization.
 * @param ConfigPtr
 */
void Pwm_Init(const Pwm_ConfigType* ConfigPtr) {

    /* @req SWS_Pwm_10002 */
    /* @req SWS_Pwm_00046 */
    VALIDATE( ( NULL != ConfigPtr ), PWM_INIT_SERVICE_ID, PWM_E_PARAM_CONFIG );

    Pwm_ChannelType channel_iterator;

    /** @req SWS_PWM_00118 */
    /** @req SWS_PWM_00121 */
    /** @req SWS_PWM_50002 */
    if( Pwm_ModuleState == PWM_STATE_INITIALIZED ) {
#if PWM_DEV_ERROR_DETECT==STD_ON
        (void) Det_ReportError(PWM_MODULE_ID,0,PWM_INIT_SERVICE_ID,PWM_E_ALREADY_INITIALIZED);
#endif
        return;
    }

    /** @req SWS_PWM_00007 */
    /** @req SWS_PWM_00062 */
    PwmConfigPtr = ConfigPtr;

    Pwm_ModuleState = PWM_STATE_INITIALIZED;

    for (channel_iterator = 0; channel_iterator < PWM_NUMBER_OF_CHANNELS; channel_iterator++) {
        const Pwm_ChannelConfigurationType* channelConfig = &ConfigPtr->Channels[channel_iterator];
        Pwm_ChannelType channel = channelConfig->channel;

        /*
         * Reset the count control register to it's default value.
         */
        SetCounterControl(channel, CNT_CNTRL_RESET_VALUE);

        /*
         * Reset the rest of the registers to the default values.
         */
        SetClockControl(channel, 0x00);
        SetIntervalCounter(channel, 0x00);
        SetMatchCounter(channel, MATCH_REG_1, 0x00);
        SetMatchCounter(channel, MATCH_REG_2, 0x00);
        SetMatchCounter(channel, MATCH_REG_3, 0x00);
        SetInterruptEnable(channel, 0x00);
        uint8_t interrupt_status = GetInterruptRegister(channel); /* Clear all interrupts */
        (void)interrupt_status;

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
        installChannelInterrupt(channel);
#endif
        /** @req SWS_PWM_00052 */
        Pwm_DisableNotification(channel);
#endif

        /* Configure the channel with the selected parameters */
        configureChannel( channelConfig );

    }

}

/** @req SWS_PWM_10080 */
/** @req SWS_PWM_20080 */
#if PWM_DE_INIT_API==STD_ON
static void inline Pwm_DeInitChannel(Pwm_ChannelType Channel) {

    /*
     * Reset the all registers to the default values.
     */
    SetCounterControl(Channel, CNT_CNTRL_RESET_VALUE);
    SetClockControl(Channel, 0x00);
    SetIntervalCounter(Channel, 0x00);
    SetMatchCounter(Channel, MATCH_REG_1, 0x00);
    SetMatchCounter(Channel, MATCH_REG_2, 0x00);
    SetMatchCounter(Channel, MATCH_REG_3, 0x00);
    /** @req SWS_PWM_00012 */
    SetInterruptEnable(Channel, 0x00);
    uint8_t interrupt_status = GetInterruptRegister(Channel); /* Clear all interrupts */
    (void) interrupt_status;

    /** @req SWS_PWM_00011 */
#if  PWM_SET_OUTPUT_TO_IDLE_API == STD_ON
    Pwm_SetOutputToIdle(Channel);
#endif

}

/**
 * Service for PWM De-Initialization.
 */
void Pwm_DeInit(void) {
    Pwm_ChannelType channel_iterator;

    /** @req SWS_PWM_00117 */
    /** @req SWS_PWM_20002 */
    VALIDATE(Pwm_ModuleState == PWM_STATE_INITIALIZED, PWM_DEINIT_SERVICE_ID, PWM_E_UNINIT);

    /** @req SWS_PWM_00010 */
    for (channel_iterator = 0; channel_iterator < PWM_NUMBER_OF_CHANNELS; channel_iterator++) {
        Pwm_ChannelType channel = PwmConfigPtr->Channels[channel_iterator].channel;
        Pwm_DeInitChannel(channel);
    }

    Pwm_ModuleState = PWM_STATE_UNINITIALIZED;
}
#endif

/** @req SWS_Pwm_10083 */
/** @req SWS_Pwm_20083 */
/** @req SWS_Pwm_00098 */
#if PWM_SET_PERIOD_AND_DUTY_API==STD_ON
/**
 * Service sets the period and the duty cycle of a PWM channel
 */
/** @req SWS_Pwm_00020 */
void Pwm_SetPeriodAndDuty(Pwm_ChannelType Channel, Pwm_PeriodType Period, uint16 DutyCycle)
{
    /** @req SWS_Pwm_00076 Note: UpdatedEndPeriod not supported. */
    /** @req SWS_PWM_00117 */
    /** @req SWS_PWM_20002 */
    VALIDATE(Pwm_ModuleState == PWM_STATE_INITIALIZED, PWM_SETPERIODANDDUTY_SERVICE_ID, PWM_E_UNINIT);
    /** @req SWS_PWM_30002 */
    /** @req SWS_PWM_00047 */
    VALIDATE(IS_VALID_CHANNEL(Channel), PWM_SETPERIODANDDUTY_SERVICE_ID, PWM_E_PARAM_CHANNEL);

    Pwm_ChannelType channel_iterator;

    for (channel_iterator = 0; channel_iterator < PWM_NUMBER_OF_CHANNELS; channel_iterator++)
    {
        if(Channel == PwmConfigPtr->Channels[channel_iterator].channel){
            /** @req SWS_PWM_00041 */
            if(PwmConfigPtr->ChannelClass[channel_iterator] != PWM_VARIABLE_PERIOD){
#if PWM_DEV_ERROR_DETECT==STD_ON
                /** @req SWS_PWM_00045 */
                /** @req SWS_PWM_40002 */
                (void)Det_ReportError(PWM_MODULE_ID,0, PWM_SETPERIODANDDUTY_SERVICE_ID, PWM_E_PERIOD_UNCHANGEABLE);
#endif
                return;
            }
            break;
        }
    }

    // Check that we found a valid channel
    VALIDATE(channel_iterator < PWM_NUMBER_OF_CHANNELS, PWM_SETPERIODANDDUTY_SERVICE_ID, PWM_E_PARAM_CHANNEL);

    /** @req SWS_Pwm_00019 */
    /** @req SWS_Pwm_10086  */

    // Perform change
    /* @req SWS_Pwm_00150 Dutycyle is passed on and will set 0 percent duty cycle */
    changePeriod(Channel, Period, DutyCycle);
}
#endif



/** @req SWS_PWM_10082 */
/** @req SWS_PWM_20082 */
/** @req SWS_Pwm_00097 */
/**
 * The function Pwm_SetDutyCycle shall set the duty cycle of the PWM channel.
 *
 * @param Channel PWM channel to use. 0 <= Channel < PWM_NUMBER_OF_CHANNELS <= 5
 * @param DutyCycle 0 <= DutyCycle <= 0x8000
 */
#if PWM_SET_DUTY_CYCLE_API==STD_ON
void Pwm_SetDutyCycle(Pwm_ChannelType Channel, uint16 DutyCycle)
{
    /** @req SWS_PWM_00117 */
    /** @req SWS_PWM_20002 */
    VALIDATE(Pwm_ModuleState == PWM_STATE_INITIALIZED, PWM_SETDUTYCYCLE_SERVICE_ID, PWM_E_UNINIT);
    /** @req SWS_PWM_30002 */
    /** @req SWS_PWM_00047 */
    VALIDATE(IS_VALID_CHANNEL(Channel), PWM_SETDUTYCYCLE_SERVICE_ID, PWM_E_PARAM_CHANNEL);

    // Get period value in ticks
    Pwm_PeriodType periodTicks = GetIntervalCounter(Channel);

    /** @req SWS_Pwm_00013  */
    /** @req SWS_Pwm_00014  */
    /** @req SWS_Pwm_00016  */
    /** @req SWS_Pwm_20086  */
    /** @req SWS_Pwm_00119  */

    // Perform change
    changePeriod(Channel, periodTicks, DutyCycle);
}
#endif

/** @req SWS_PWM_10084 */
/** @req SWS_PWM_20084 */
/** @req SWS_Pwm_00099 */
#if  PWM_SET_OUTPUT_TO_IDLE_API == STD_ON
/**
 * Service sets the PWM output to the configured Idle state.
 */
void Pwm_SetOutputToIdle(Pwm_ChannelType Channel)
{
    /** @req SWS_PWM_00117 */
    /** @req SWS_PWM_20002 */
    VALIDATE(Pwm_ModuleState == PWM_STATE_INITIALIZED, PWM_SETOUTPUTTOIDLE_SERVICE_ID, PWM_E_UNINIT);
    /** @req SWS_PWM_30002 */
    /** @req SWS_PWM_00047 */
    VALIDATE(IS_VALID_CHANNEL(Channel), PWM_SETOUTPUTTOIDLE_SERVICE_ID, PWM_E_PARAM_CHANNEL);

    Pwm_ChannelType channel_iterator;
    uint16 dutyCycle = 0u;

    /** @req SWS_Pwm_00021 */

    // Determine idle state duty from polarity
    for (channel_iterator = 0; channel_iterator < PWM_NUMBER_OF_CHANNELS; channel_iterator++)
    {
        if(Channel == PwmConfigPtr->Channels[channel_iterator].channel)
        {
            if(PwmConfigPtr->IdleState[channel_iterator] == PWM_HIGH)
            {
                if(PwmConfigPtr->Channels[channel_iterator].polarity == PWM_HIGH)
                {
                    dutyCycle = HUNDRED_PERCENT_DUTY_CYCLE;
                }
                else
                {
                    dutyCycle = 0u;
                }
            }
            else
            {
                if(PwmConfigPtr->Channels[channel_iterator].polarity == PWM_HIGH)
                {
                    dutyCycle = 0u;
                }
                else
                {
                    dutyCycle = HUNDRED_PERCENT_DUTY_CYCLE;
                }
            }
            break;
        }
    }

    // Disable TTC
    uint8_t counter_control_value = GetCounterControl(Channel);
    SetCounterControl(Channel, (counter_control_value | CNT_CNTRL_DIS_MASK));

    Pwm_PeriodType periodTicks = GetIntervalCounter(Channel);    /* Period value in ticks */

    // Perform change
    changePeriod(Channel, periodTicks, dutyCycle);
}
#endif

/** @req SWS_PWM_10085 */
/** @req SWS_PWM_20085 */
#if (PWM_GET_OUTPUT_STATE_API==STD_ON)
/**
 * The function Pwm_GetOutputState shall read the internal state
 * of the PWM output signal and return it.
 */
Pwm_OutputStateType Pwm_GetOutputState(Pwm_ChannelType Channel)
{
    /** @req SWS_PWM_30051 */
    /** @req SWS_PWM_00117 */
    /** @req SWS_PWM_20002 */
    VALIDATE_W_RV(Pwm_ModuleState == PWM_STATE_INITIALIZED, PWM_GETOUTPUTSTATE_SERVICE_ID, PWM_E_UNINIT, PWM_LOW);
    /** @req SWS_PWM_30002 */
    /** @req SWS_PWM_00047 */
    VALIDATE_W_RV(IS_VALID_CHANNEL(Channel), PWM_GETOUTPUTSTATE_SERVICE_ID, PWM_E_PARAM_CHANNEL, PWM_LOW);


    // Not supported for Zynq, missing resulting wave out readback register.
    return (Pwm_OutputStateType) PWM_LOW;
}
#endif

/** @req SWS_PWM_10112 */
/** @req SWS_PWM_20112 */
/** @req SWS_PWM_20115 */
/** @req SWS_PWM_00101 */
#if PWM_NOTIFICATION_SUPPORTED==STD_ON
/**
 * Service to disable the PWM signal edge notification.
 */
/** @req SWS_Pwm_30115 */
void Pwm_DisableNotification(Pwm_ChannelType Channel)
{
    /** @req SWS_PWM_00117 */
    /** @req SWS_PWM_20002 */
    VALIDATE(Pwm_ModuleState == PWM_STATE_INITIALIZED, PWM_DISABLENOTIFICATION_SERVICE_ID, PWM_E_UNINIT);
    /** @req SWS_PWM_30002 */
    /** @req SWS_PWM_00047 */
   VALIDATE(IS_VALID_CHANNEL(Channel), PWM_DISABLENOTIFICATION_SERVICE_ID, PWM_E_PARAM_CHANNEL);

   /** @req SWS_Pwm_00023 */

   // Disable all interrupts for this channel
   uint8 enableMask = 0;
   SetInterruptEnable(Channel, enableMask);

   // Clear interrupts for this channel
   (void)GetInterruptRegister(Channel);
}


/** @req SWS_PWM_10113 */
/** @req SWS_PWM_20113 */
/** @req SWS_PWM_10115 */
/** @req SWS_PWM_00102 */
/**
 * Service to enable the PWM signal edge notification according to notification parameter.
 */
void Pwm_EnableNotification(Pwm_ChannelType Channel,Pwm_EdgeNotificationType Notification)
{
    /** @req SWS_PWM_00117 */
    /** @req SWS_PWM_20002 */
    VALIDATE(Pwm_ModuleState == PWM_STATE_INITIALIZED, PWM_ENABLENOTIFICATION_SERVICE_ID, PWM_E_UNINIT);
    /** @req SWS_PWM_30002 */
    /** @req SWS_PWM_00047 */
    VALIDATE(IS_VALID_CHANNEL(Channel), PWM_ENABLENOTIFICATION_SERVICE_ID, PWM_E_PARAM_CHANNEL);

    uint8 enableMask;
    Pwm_OutputStateType polarity = PWM_HIGH;
    Pwm_ChannelType channel_iterator;

    // First disable all interrupts for this channel
    enableMask = 0;
    SetInterruptEnable(Channel, enableMask);

    /** @req SWS_Pwm_00024 */

    // Find polarity for this channel
    for (channel_iterator = 0; channel_iterator < PWM_NUMBER_OF_CHANNELS; channel_iterator++)
    {
        if(Channel == PwmConfigPtr->Channels[channel_iterator].channel)
        {
            polarity = PwmConfigPtr->Channels[channel_iterator].polarity;
            break;
        }
    }

    // Enable interrupt at interval end
    enableMask = 0;
    if ((Notification == PWM_BOTH_EDGES) ||
        ((Notification == PWM_RISING_EDGE) && (polarity == PWM_HIGH)) ||
        ((Notification == PWM_FALLING_EDGE) && (polarity == PWM_LOW)))
    {
        enableMask += IXR_INTERVAL_MASK;
    }

    // Enable interrupt at duty end
    if ((Notification == PWM_BOTH_EDGES) ||
        ((Notification == PWM_RISING_EDGE) && (polarity == PWM_LOW)) ||
        ((Notification == PWM_FALLING_EDGE) && (polarity == PWM_HIGH)))
    {
        enableMask += IXR_MATCH_0_MASK;
    }

    if (enableMask != 0)
    {
        // Disable TTC
        uint8_t counter_control_value = GetCounterControl(Channel);
        SetCounterControl(Channel, (counter_control_value | CNT_CNTRL_DIS_MASK));

        /** @req SWS_Pwm_00081 */
        // Clear interrupts for this channel
        (void)GetInterruptRegister(Channel);

        // Enable selected interrupts
        SetInterruptEnable(Channel, enableMask);

        // Enable TTC
        SetCounterControl(Channel, (counter_control_value & ~CNT_CNTRL_DIS_MASK));
    }
}

/**
 * General interrupt service routine for a pwm channel. Handles all notifications.
 * @param channel
 */
static void Pwm_Isr(Pwm_ChannelType channel)
{
    Pwm_NotificationHandlerType func = NULL;
    Pwm_ChannelType channel_iterator;

    // Clear interrupts (Read interrupt status register)
    uint8_t interrupt_status = GetInterruptRegister(channel);
    (void) interrupt_status;

    // Find notification handler for this channel
    for (channel_iterator = 0; channel_iterator < PWM_NUMBER_OF_CHANNELS; channel_iterator++)
    {
        if(channel == PwmConfigPtr->Channels[channel_iterator].channel)
        {
            func = PwmConfigPtr->NotificationHandlers[channel_iterator];
            break;
        }
    }

    /*@req SWS_PWM_00025 The interrupt is enabled and disabled in the PWM_Enable/DisableNotification funcations */

    if (func != NULL && (PWM_0_PERCENT != Pwm_chnLastSetDuty[channel]) && \
        (PWM_100_PERCENT != Pwm_chnLastSetDuty[channel]))
    {
        // Run notification handler
        func();
    }
}

ISR(Pwm_0_Isr)
{
    Pwm_Isr(CHANNEL_0);
}

ISR(Pwm_1_Isr)
{
    Pwm_Isr(CHANNEL_1);
}

ISR(Pwm_2_Isr)
{
    Pwm_Isr(CHANNEL_2);
}

ISR(Pwm_3_Isr)
{
    Pwm_Isr(CHANNEL_3);
}

ISR(Pwm_4_Isr)
{
    Pwm_Isr(CHANNEL_4);
}

ISR(Pwm_5_Isr)
{
    Pwm_Isr(CHANNEL_5);
}

#endif /* PWM_NOTIFICATION_SUPPORED == STD_ON */


/** @req SWS_Pwm_20069 */
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
