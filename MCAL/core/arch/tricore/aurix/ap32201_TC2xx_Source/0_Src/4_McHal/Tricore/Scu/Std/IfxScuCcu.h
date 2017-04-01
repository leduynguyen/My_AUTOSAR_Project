/**
 * \file IfxScuCcu.h
 * \brief SCU  basic functionality
 * \ingroup IfxLld_Scu
 *
 * \version iLLD_0_1_0_6
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * \defgroup IfxLld_Scu SCU
 * \ingroup IfxLld
 * \defgroup IfxLld_Scu_Std Standard Driver
 * \ingroup IfxLld_Scu
 * \defgroup IfxLld_Scu_Std_Ccu Clock Control Functions
 * \ingroup IfxLld_Scu_Std
 * \defgroup IfxLld_Scu_Std_Ccu_Operative Clock Control Operative Functions
 * \ingroup IfxLld_Scu_Std
 * \defgroup IfxLld_Scu_Std_Ccu_Configuration Clock Control Configuration Functions
 * \ingroup IfxLld_Scu_Std
 */

#ifndef IFXSCUCCU_H
#define IFXSCUCCU_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxScu_cfg.h"
#include "Scu/Std/IfxScuWdt.h"
#include "Cpu/Std/IfxCpu.h"
#include "IfxScu_reg.h"
#include "Ifx_Cfg.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/* PLL source clock selection */
#define IFXSCUCCU_XTAL_OSC0             (1U)
#define IFXSCUCCU_EVR_OSC1              (0U)

/* CCU clock selection */
#define IFXSCUCCU_CLKSEL_EVR_OSC1       (0U)
#define IFXSCUCCU_CLKSEL_PLL            (1U)
#define IFXSCUCCU_CLKSEL_OSC0           (2U)

#define IFXSCUCCU_SCU_SFR_UPDATE        (1U)

#define IFXSCUCCU_EXTCLK0_PIN_0        (90U)
#define IFXSCUCCU_EXTCLK1_PIN_0        (88U)
#define IFXSCUCCU_EXTCLK1_PIN_1        (167U)

#define IFXSCUCCU_EXTCLK0_PIN_0_PORT   (&MODULE_P23)
#define IFXSCUCCU_EXTCLK0_PIN_0_PIN    (1U)

#define IFXSCUCCU_EXTCLK1_PIN_0_PORT   (&MODULE_P32)
#define IFXSCUCCU_EXTCLK1_PIN_0_PIN    (4U)
#define IFXSCUCCU_EXTCLK1_PIN_1_PORT   (&MODULE_P11)
#define IFXSCUCCU_EXTCLK1_PIN_1_PIN    (12U)

#define IFXSCUCCU_EXTCLK0_STEP_MASK    (1024U)

#define IFXSCUCCU_SFR_UPDATE           (1U)

/* fOUT is selected for the external clock signal */
#define IFXSTART_EXTCLK_FOUT       (0U)
/* fPLL is selected for the external clock signal */
#define IFXSTART_EXTCLK_FPLL       (1U)
/* fPLLERAY is selected for the external clock signal */
#define IFXSTART_EXTCLK_FERAY      (2U)
/* fOSC0 is selected for the external clock signal */
#define IFXSTART_EXTCLK_FOSC0      (3U)
/* fBACK is selected for the external clock signal */
#define IFXSTART_EXTCLK_FOSC1      (4U)
/* fETH is selected for the external clock signal */
#define IFXSTART_EXTCLK_FETH       (5U)
/* fBBB is selected for the external clock signal */
#define IFXSTART_EXTCLK_FBBB       (6U)
/* fBAUD1 is selected for the external clock signal */
#define IFXSTART_EXTCLK_FBAUD1     (7U)
/* fSRI is selected for the external clock signal */
#define IFXSTART_EXTCLK_FSRI       (8U)
/* fSPB is selected for the external clock signal */
#define IFXSTART_EXTCLK_FSPB       (9U)
/* fFSI is selected for the external clock signal */
#define IFXSTART_EXTCLK_FFSI       (10U)
/* fSTM is selected for the external clock signal */
#define IFXSTART_EXTCLK_FSTM       (11U)
/* fGTM is selected for the external clock signal */
#define IFXSTART_EXTCLK_FGTM       (12U)
/* fTCK is selected for the external clock signal */
#define IFXSTART_EXTCLK_FTCK       (13U)
/* fBAUD2 is selected for the external clock signal */
#define IFXSTART_EXTCLK_FBAUD2     (14U)
/* fMT0 from the ERAY module is selected for the external clock signal */
#define IFXSTART_EXTCLK_FMTO       (15U)
/** \addtogroup IfxLld_Scu_Ccu
 * \{  */

/** \brief Oscillator stability check timeout count
 */
#define IFXSCUCCU_OSC_STABLECHK_TIME (640)

/******************************************************************************/
/*------------------------------Type Definitions------------------------------*/
/******************************************************************************/

/** \brief Function pointer type for the hooks
 * \return None
 */
typedef void (*IfxScuCcu_PllStepsFunctionHook)(void);

/******************************************************************************/
/*-------------------------------Enumerations---------------------------------*/
/******************************************************************************/

/** \brief Selects the ADC converter clock in SCU_CCUCON0.B.ADCCLKSEL
 */
typedef enum
{
    IfxScuCcu_AdcClockSelection_noClock   = 0,  /**< \brief No ADC converter clock, no conversions possible! */
    IfxScuCcu_AdcClockSelection_fpll2     = 1,  /**< \brief Select fPLL2 as clock source for the ADC converter */
    IfxScuCcu_AdcClockSelection_fPLL2ERAY = 2,  /**< \brief Select fPLL2ERAY as clock source for the ADC converter */
    IfxScuCcu_AdcClockSelection_backup    = 3   /**< \brief Select Backup-Clock (100 MHz) as clock source for the ADC converter */
} IfxScuCcu_AdcClockSelection;

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Scu_Std_Ccu
 * \{ */
/** \brief Configuration structure type for CCUCON registers.
 */
typedef struct
{
    uint32 value;     /**< \brief CCUCON Register value to be updated. */
    uint32 mask;      /**< \brief CCUCON Mask to select the bit fields to be updated. */
} IfxScuCcu_CcuconRegConfig;

/** \} */

/** \addtogroup IfxLld_Scu_Std_Ccu
 * \{ */
/** \brief Configuration structure type for all the CCUCON registers to configure clock distribution.
 */
typedef struct
{
    IfxScuCcu_CcuconRegConfig ccucon0;     /**< \brief CCUCON0 Register configuration */
    IfxScuCcu_CcuconRegConfig ccucon1;     /**< \brief CCUCON1 Register configuration */
    IfxScuCcu_CcuconRegConfig ccucon2;     /**< \brief CCUCON2 Register configuration */
    IfxScuCcu_CcuconRegConfig ccucon5;     /**< \brief CCUCON5 Register configuration */
    IfxScuCcu_CcuconRegConfig ccucon6;     /**< \brief CCUCON6 Register configuration */
#if ((IFX_CFG_DEVICE == IFX_CFG_TC29X ) || (IFX_CFG_DEVICE == IFX_CFG_TC27X ) || (IFX_CFG_DEVICE == IFX_CFG_TC26X ))
    IfxScuCcu_CcuconRegConfig ccucon7;     /**< \brief CCUCON7 Register configuration */
#endif
#if ((IFX_CFG_DEVICE == IFX_CFG_TC29X ) || (IFX_CFG_DEVICE == IFX_CFG_TC27X ))
    IfxScuCcu_CcuconRegConfig ccucon8;     /**< \brief CCUCON8 Register configuration */
#endif
} IfxScuCcu_ClockDistributionConfig;

/** \brief Configuration structure type for the Flash waitstate configuration.
 */
typedef struct
{
    uint32 value;     /**< \brief FLASH.FCON Register value to be updated. */
    uint32 mask;      /**< \brief FLASH.FCON Mask to select the bit fields to be updated. */
} IfxScuCcu_FlashWaitstateConfig;

/** \brief Configuration structure type for the Pll initial step.
 * This structure must be used to configure the P, N and K2 dividers for initial step.
 */
typedef struct
{
    uint8   pDivider;      /**< \brief P divider value for basic (initial) step */
    uint8   nDivider;      /**< \brief N divider value for basic (initial) step */
    uint8   k2Initial;     /**< \brief K2 divider value for basic (initial) step */
    float32 waitTime;      /**< \brief Wait time for for basic (initial) step */
} IfxScuCcu_InitialStepConfig;

/** \brief Configuration structure type for the Pll Steps for current jump control.
 */
typedef struct
{
    uint8                          k2Step;           /**< \brief K2 divider value for this step. */
    float32                        waitTime;         /**< \brief Wait time for for this step. */
    IfxScuCcu_PllStepsFunctionHook hookFunction;     /**< \brief Hook function called at the end of this step. */
} IfxScuCcu_PllStepsConfig;

/** \} */

/** \addtogroup IfxLld_Scu_Std_Ccu
 * \{ */
/** \brief Configuration structure SCU module
 */
typedef struct
{
    uint8                             numOfPllDividerSteps;         /**< \brief Number of PLL divider steps during clock throttling. */
    IfxScuCcu_PllStepsConfig         *pllDividerStep;               /**< \brief Pointer to the array of Pll divider step configuration. */
    IfxScuCcu_InitialStepConfig       pllInitialStep;               /**< \brief Configuration of first step which is same as internal osc frequency. */
    IfxScuCcu_ClockDistributionConfig clockDistribution;            /**< \brief Configuration of of bus clocks and other module clock distribution. */
    IfxScuCcu_FlashWaitstateConfig    flashFconWaitStateConfig;     /**< \brief Configuration of flash waitstate */
} IfxScuCcu_Config;

/** \brief Configuration structure for E-ray PLL
 */
typedef struct
{
    IfxScuCcu_InitialStepConfig pllInitialStep;     /**< \brief Configuration of first step which is same as internal osc frequency. */
} IfxScuCcu_ErayPllConfig;

/** \} */

/** \addtogroup IfxLld_Scu_Std_Ccu_Operative
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief API to get EVR Oscillator frequency.
 * This API returns the constant which is specific to the ScuCcu of the controller.
 * \return EVR Oscillator frequency (fBACK or fEVR) in Hz.
 */
IFX_INLINE float32 IfxScuCcu_getEvrFrequency(void);

/** \brief API to get Oscillator 0 frequency.
 * This API returns the fOsc0 frequency based on the divider value in CCUCON register and the input oscillator.
 * \return Osc0 frequency (fOSC0) in Hz.
 */
IFX_INLINE float32 IfxScuCcu_getOsc0Frequency(void);

/** \brief API to get Oscillator 0 frequency.
 * This API returns the fOsc0 frequency based on the divider value in CCUCON register and the input oscillator.
 * \return Osc frequency (fOSC) in Hz.
 */
IFX_INLINE float32 IfxScuCcu_getOscFrequency(void);

/** \brief API to get actual PLL2 (K3 Divider for ADC clock) frequency
 * This API returns the  PLL2ERAY frequency based on the K3 divider value in PLLERAYCON and the VCO frequency. This frequency is one of the configurable inputs to ADC clock.
 * \return PLL2ERAY (K3 Divider for ADC clock) frequency in Hz
 */
IFX_INLINE float32 IfxScuCcu_getPll2ErayFrequency(void);

/** \brief API to get actual PLL2 (K3 Divider for ADC clock) frequency
 * This API returns the  PLL2 frequency based on the K3 divider value in PLLCON and the VCO frequency. This frequency is one of the configurable inputs to ADC clock.
 * \return PLL2 (K3 Divider for ADC clock) frequency in Hz
 */
IFX_INLINE float32 IfxScuCcu_getPll2Frequency(void);

/** \brief API to get STM divider frequency.
 * This API returns the based on the divider value in CCUCON register and fSOURCE.
 * \return STM frequency (fSTM) in Hz
 */
IFX_INLINE float32 IfxScuCcu_getStmFrequency(void);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief API to get ADC divider frequency in Hz.
 * This API returns the fADC based on the divider value in CCUCON register and the input oscillator.
 * \return FSI frequency (fFSI) in Hz.
 */
IFX_EXTERN float32 IfxScuCcu_getAdcFrequency(void);

/** \brief API to get BAUD1 divider frequency.
 * This API returns the based on the divider value in CCUCON register and the input oscillator.
 * \return Baud1 frequency in Hz
 */
IFX_EXTERN float32 IfxScuCcu_getBaud1Frequency(void);

/** \brief API to get BAUD2 divider frequency.
 * This API returns the Baud2 frequency based on the divider value in CCUCON register and the fMAX.
 * \return Baud2 frequency in Hz
 */
IFX_EXTERN float32 IfxScuCcu_getBaud2Frequency(void);

/** \brief API to get BBB divider frequency.
 * This API returns the BBBDivider frequency based on the divider value in CCUCON register and the input oscillator.
 * \return BBB frequency (fBBB) in Hz
 */
IFX_EXTERN float32 IfxScuCcu_getBbbFrequency(void);

/** \brief This API returns the Cpu frequency based on the divider value in CCUCON register and fSource frequency
 * \param cpu CPU number for which effective fCPU is sought
 * \return Cpu[x] frequency in Hz, where x is cpu number passed as parameter
 */
IFX_EXTERN float32 IfxScuCcu_getCpuFrequency(const IfxCpu_ResourceCpu cpu);

/** \brief API to get FSI2 divider frequency in Hz.
 * This API returns the fFSI2 frequency based on the divider value in CCUCON register and the input oscillator.
 * \return FSI2 frequency (fFSI2) in Hz.
 */
IFX_EXTERN float32 IfxScuCcu_getFsi2Frequency(void);

/** \brief API to get FSI divider frequency in Hz.
 * This API returns the fFSI based on the divider value in CCUCON register and the input oscillator.
 * \return FSI frequency (fFSI) in Hz.
 */
IFX_EXTERN float32 IfxScuCcu_getFsiFrequency(void);

/** \brief API to get FMAX divider frequency.
 * This API returns the fMax frequency based on the divider value in CCUCON register and the input oscillator.
 * \return Max frequency (fMAX) in Hz.
 */
IFX_EXTERN float32 IfxScuCcu_getMaxFrequency(void);

/** \brief get source frequency fSOURCE.
 * This API returns the source frequency based on the configurations with CCUCON register configuration.
 * \return Module frequency in Hz
 */
IFX_EXTERN float32 IfxScuCcu_getModuleFrequency(void);

/** \brief API to get actual PLL (Eray) frequency.
 * This API returns the based on the divider values in CCUCON, PLLCON registers and the input oscillator.
 * \return frequency of Pll Eray (fPLLERAY) in Hz
 */
IFX_EXTERN float32 IfxScuCcu_getPllErayFrequency(void);

/** \brief API to get actual ERAY PLL Voltage Controlled Oscillator frequency.
 * This API returns the based on the divider values in PLLERAYCON registers and the input oscillator.
 * \return Pll (Eray) VCO frequency
 */
IFX_EXTERN float32 IfxScuCcu_getPllErayVcoFrequency(void);

/** \brief API to get actual PLL output frequency.
 * This API returns the based on the divider values in CCUCON, PLLCON registers and the input oscillator.
 * \return Pll (fPLL) frequency in Hz
 */
IFX_EXTERN float32 IfxScuCcu_getPllFrequency(void);

/** \brief API to get actual PLL Voltage Controlled Oscillator frequency.
 * This API returns the based on the divider values in PLLCON registers and the input oscillator.
 * \return Pll VCO frequency
 */
IFX_EXTERN float32 IfxScuCcu_getPllVcoFrequency(void);

/** \brief get source frequency fSOURCE.
 * This API returns the source frequency based on the configurations with CCUCON register configuration.
 * \return Effective fSOURCE in Hz
 */
IFX_EXTERN float32 IfxScuCcu_getSourceFrequency(void);

/** \brief API to get SPB divider frequency.
 * This API returns the based on fSOURCE and also on Low power divider mode and/or SPBDIV divider value in CCUCON registers.
 * \return SPB frequency (fSPB) in Hz
 */
IFX_EXTERN float32 IfxScuCcu_getSpbFrequency(void);

/** \brief API to get SRI divider frequency.
 * This API returns the Sri frequency based on the divider values in CCUCON registers and fSOURCE.
 * \return Sri frequency (fSRI) in Hz
 */
IFX_EXTERN float32 IfxScuCcu_getSriFrequency(void);

/** \brief API to select the Converter clock of the ADC in CCUCON0.B.ADCCLKSEL
 * \param adcClkSel The desired clock selection
 * \return None
 */
IFX_EXTERN void IfxScuCcu_selectAdcClock(IfxScuCcu_AdcClockSelection adcClkSel);

/** \brief API to set CPU frequency (with CPU divider)
 * This API configure CPU divider values in CCUCON registers. The actual frequency is always depends on the feasibility with the divider value
 * \param cpu CPU number for which fCPU to be configured
 * \param cpuFreq Desired CPU frequency in Hz
 * \return Actual CPU[x] frequency in Hz, where x is the cpu number passed as parameter
 */
IFX_EXTERN float32 IfxScuCcu_setCpuFrequency(IfxCpu_ResourceCpu cpu, float32 cpuFreq);

/** \brief API to configure PLL2ERAY (K3 Divider for ADC clock) for desired frequency.
 * This API configure K3 divider value in CCUCON. The actual frequency always depends on the feasibility with the divider value
 * \param pll2ErayFreq PLL2ERAY (K3 Divider for ADC clock) frequency in Hz
 * \return Actual PLL2 (K3 Divider for ADC clock) frequency in Hz
 */
IFX_EXTERN float32 IfxScuCcu_setPll2ErayFrequency(float32 pll2ErayFreq);

/** \brief API to configure PLL2 (K3 Divider for ADC clock) for desired frequency.
 * This API configure K3 divider value in CCUCON. The actual frequency always depends on the feasibility with the divider value
 * \param pll2Freq PLL2 (K3 Divider for ADC clock) frequency in Hz
 * \return Actual PLL2 (K3 Divider for ADC clock) frequency in Hz
 */
IFX_EXTERN float32 IfxScuCcu_setPll2Frequency(float32 pll2Freq);

/** \brief API to set SPB frequency (with SPB divider)
 * This API configure SPB divider values in CCUCON registers. The actual frequency always depends on the feasibility with the divider value
 * \param spbFreq Desired SPB frequency in Hz
 * \return Actual SPB frequency in Hz
 */
IFX_EXTERN float32 IfxScuCcu_setSpbFrequency(float32 spbFreq);

/** \} */

/** \addtogroup IfxLld_Scu_Std_Ccu_Configuration
 * \{ */

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief API to initialize the SCU Clock Control Unit.
 * This API initialize the PLL with ramp steps, BUS dividers for the configuration provided by the configuration structure.
 * \param cfg Pointer to the configuration structure of the ScuCcu
 * \return Error status of the ScuCcu initialization process.
 * \retval TRUE: If an error occurred during initialization.
 * \retval FALSE: If initialization was successful.
 */
IFX_EXTERN boolean IfxScuCcu_init(const IfxScuCcu_Config *cfg);

/** \brief Initializes the clock configuration with default values
 * \param cfg Pointer to the configuration structure of the ScuCcu
 * \return None
 */
IFX_EXTERN void IfxScuCcu_initConfig(IfxScuCcu_Config *cfg);

/** \brief API to initialize the SCU Eray Pll
 * This API initialize the Eray PLL for the configuration provided by the configuration structure.
 * \param cfg Pointer to the configuration structure of the Eray Pll
 * \return Error status of the ScuCcu Eray Pll initialization process.
 * \retval TRUE: If an error occurred during initialization.
 * \retval FALSE: If initialization was successful.
 */
IFX_EXTERN boolean IfxScuCcu_initErayPll(const IfxScuCcu_ErayPllConfig *cfg);

/** \brief Initializes the clock configuration with default values
 * \param cfg Pointer to the configuration structure of the ScuCcuEray Pll
 * \return None
 */
IFX_EXTERN void IfxScuCcu_initErayPllConfig(IfxScuCcu_ErayPllConfig *cfg);

/** \} */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief API to get GTMdivider frequency
 * This API returns the based on the divider value in CCUCON register and fSOURCE.
 * return GTM frequency (fGTM) in Hz
 */
IFX_INLINE float32 IfxScuCcu_getGtmFrequency(void);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief API to set GTM frequency (with GTM divider)
 * This API configure GTM divider values in CCUCON registers. The actual frequency always depends on the feasibility with the divider value
 * \param gtmFreq Desired GTM frequency in Hz
 * \return Actual GTM frequency in HZ
 */
IFX_EXTERN float32 IfxScuCcu_setGtmFrequency(float32 gtmFreq);

/******************************************************************************/
/*-------------------Global Exported Variables/Constants----------------------*/
/******************************************************************************/

/** \brief Configuration structure for SCU CCU driver.
 * The values of this structure are defined as # defined macros in the implementation of Scu
 */
IFX_EXTERN const IfxScuCcu_Config IfxScuCcu_defaultClockConfig;

/** \brief Configuration structure for SCU CCU driver.
 * The values of this structure are defined as # defined macros in the implementation of Scu
 */
IFX_EXTERN const IfxScuCcu_ErayPllConfig IfxScuCcu_defaultErayPllConfig;

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/

IFX_INLINE float32 IfxScuCcu_getEvrFrequency(void)
{
    return IFXSCU_EVR_OSC_FREQUENCY;
}


IFX_INLINE float32 IfxScuCcu_getOsc0Frequency(void)
{
    return IFX_CFG_SCU_XTAL_FREQUENCY;
}


IFX_INLINE float32 IfxScuCcu_getOscFrequency(void)
{
    float32 freq;

    if (SCU_CCUCON1.B.INSEL == IfxScu_CCUCON1_INSEL_fOsc1)
    {
        freq = IFXSCU_EVR_OSC_FREQUENCY;
    }
    else if (SCU_CCUCON1.B.INSEL == IfxScu_CCUCON1_INSEL_fOsc0)
    {
        freq = IFX_CFG_SCU_XTAL_FREQUENCY;
    }
    else
    {
        /* Reserved values, this */
        freq = 0.0;
    }

    return freq;
}


IFX_INLINE float32 IfxScuCcu_getPll2ErayFrequency(void)
{
    float32 pll2ErayFrequency;

    pll2ErayFrequency = IfxScuCcu_getPllErayVcoFrequency() / (SCU_PLLERAYCON1.B.K3DIV + 1);

    return pll2ErayFrequency;
}


IFX_INLINE float32 IfxScuCcu_getPll2Frequency(void)
{
    float32 pll2Frequency;

    pll2Frequency = IfxScuCcu_getPllVcoFrequency() / (SCU_PLLCON1.B.K3DIV + 1);

    return pll2Frequency;
}


IFX_INLINE float32 IfxScuCcu_getStmFrequency(void)
{
    return IfxScuCcu_getSourceFrequency() / SCU_CCUCON1.B.STMDIV;
}


IFX_INLINE float32 IfxScuCcu_getGtmFrequency(void)
{
    return IfxScuCcu_getSourceFrequency() / SCU_CCUCON1.B.GTMDIV;
}


#endif /* IFXSCUCCU_H */
