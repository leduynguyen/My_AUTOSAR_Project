/**
 * \file IfxScuCcu.c
 * \brief SCU  basic functionality
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
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxScuCcu.h"
#include "IfxStm_reg.h"
#include "IfxFlash_reg.h"

/** \addtogroup IfxLld_Scu_Std_Ccu
 * \{ */

/******************************************************************************/
/*-----------------------Private Function Prototypes--------------------------*/
/******************************************************************************/

/** \brief Check if oscillator is stable.
 * \return Status of oscillator stability
 * \retval TRUE: Oscillator is unstable
 * \retval FALSE: Oscillator is stable
 */
static boolean IfxScuCcu_isOscillatorStable(void);

/** \brief API to wait for requested duration.
 * Note: IfxScuCcu_wait shall not use STM in future, because we can guarantee that STM is enabled after reset but  If PLL init is called for changing the frequency during runtime, there is no guarantee that STM is enabled
 * \return None
 */
static void IfxScuCcu_wait(float32 timeSec);

/** \} */

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/** \brief Default configuration for the PLL initial steps
 * This is a structure array and the values are defined at the Scu implementation as #define macro
 */
static const IfxScuCcu_PllStepsConfig IfxScuCcu_aDefaultPllConfigSteps[] = {
    IFXSCU_CFG_PLL_STEPS
};

/******************************************************************************/
/*-----------------------Exported Variables/Constants-------------------------*/
/******************************************************************************/

const IfxScuCcu_Config        IfxScuCcu_defaultClockConfig = {
    sizeof(IfxScuCcu_aDefaultPllConfigSteps) / sizeof(IfxScuCcu_PllStepsConfig),
    (IfxScuCcu_PllStepsConfig *)IfxScuCcu_aDefaultPllConfigSteps,
    IFXSCU_CFG_PLL_INITIAL_STEP,
    IFXSCU_CFG_CLK_DISTRIBUTION,
    IFXSCU_CFG_FLASH_WAITSTATE
};

const IfxScuCcu_ErayPllConfig IfxScuCcu_defaultErayPllConfig = {
/*{	uint8 pDivider, uint8 nDivider, uint8 k2Initial, float32 waitTime	}*/
    {(1 - 1), (24 - 1), (6 - 1), 0}
};

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

float32 IfxScuCcu_getAdcFrequency(void)
{
    float32         frequency = 0;
    Ifx_SCU_CCUCON0 ccucon0   = SCU_CCUCON0;

    if (ccucon0.B.ADCCLKSEL == 1)
    {
        frequency = IfxScuCcu_getPll2Frequency();
    }
    else if (ccucon0.B.ADCCLKSEL == 2)
    {
        frequency = IfxScuCcu_getPll2ErayFrequency();
    }
    else if (ccucon0.B.ADCCLKSEL == 3)
    {
        frequency = 100.0;
    }
    else
    {
        frequency = 0;
    }

    return frequency;
}


float32 IfxScuCcu_getBaud1Frequency(void)
{
    float32         frequency;
    Ifx_SCU_CCUCON0 ccucon0 = SCU_CCUCON0;

    if (ccucon0.B.BAUD1DIV == 0)
    {
        frequency = 0;
    }
    else
    {
        frequency = IfxScuCcu_getMaxFrequency() / ccucon0.B.BAUD1DIV;
    }

    return frequency;
}


float32 IfxScuCcu_getBaud2Frequency(void)
{
    float32         frequency;
    Ifx_SCU_CCUCON0 ccucon0 = SCU_CCUCON0;

    if (ccucon0.B.BAUD2DIV == 0)
    {
        frequency = 0;
    }
    else
    {
        frequency = IfxScuCcu_getMaxFrequency() / ccucon0.B.BAUD2DIV;
    }

    return frequency;
}


float32 IfxScuCcu_getBbbFrequency(void)
{
    float32 bbbFrequency;
    float32 sourceFrequency;
    sourceFrequency = IfxScuCcu_getSourceFrequency();

    switch (SCU_CCUCON0.B.LPDIV)
    {
    case 0:                    /*Not in low power mode */

        if (SCU_CCUCON2.B.BBBDIV == 0)
        {
            bbbFrequency = 0.0;
        }
        else
        {
            bbbFrequency = sourceFrequency / SCU_CCUCON2.B.BBBDIV;
        }

        break;
    case 1:
        bbbFrequency = sourceFrequency / 30;
        break;
    case 2:
        bbbFrequency = sourceFrequency / 60;
        break;
    case 3:
        bbbFrequency = sourceFrequency / 120;
        break;
    case 4:
        bbbFrequency = sourceFrequency / 240;
        break;
    default:
        bbbFrequency = 0.0;
        break;
    }

    return bbbFrequency;
}


float32 IfxScuCcu_getCpuFrequency(const IfxCpu_ResourceCpu cpu)
{
    float32 frequency = IfxScuCcu_getSriFrequency();
    uint32  cpuDiv    = 0;

    switch (cpu)
    {
    case IfxCpu_ResourceCpu_0:
        cpuDiv = SCU_CCUCON6.U;
        break;
#if ((IFX_CFG_DEVICE == IFX_CFG_TC29X ) || (IFX_CFG_DEVICE == IFX_CFG_TC27X ) || (IFX_CFG_DEVICE == IFX_CFG_TC26X ))
    case IfxCpu_ResourceCpu_1:
        cpuDiv = SCU_CCUCON7.U;
        break;
#endif
#if ((IFX_CFG_DEVICE == IFX_CFG_TC29X ) || (IFX_CFG_DEVICE == IFX_CFG_TC27X ))
    case IfxCpu_ResourceCpu_2:
        cpuDiv = SCU_CCUCON8.U;
        break;
#endif
    default:
        frequency = 0.0;
        break;
    }

    if (cpuDiv != 0)
    {
        frequency = frequency * (cpuDiv / 64);
    }

    return frequency;
}


float32 IfxScuCcu_getFsi2Frequency(void)
{
    float32         frequency;
    Ifx_SCU_CCUCON0 ccucon0 = SCU_CCUCON0;

    if (ccucon0.B.FSIDIV == 0)
    {
        frequency = 0;
    }
    else
    {
        frequency = IfxScuCcu_getSriFrequency();

        if ((ccucon0.B.FSIDIV == 1) || (ccucon0.B.SRIDIV == 1) || (ccucon0.B.SRIDIV == 2))
        {
            frequency = frequency / ccucon0.B.FSIDIV;
        }
    }

    return frequency;
}


float32 IfxScuCcu_getFsiFrequency(void)
{
    float32         frequency;
    Ifx_SCU_CCUCON0 ccucon0 = SCU_CCUCON0;

    if (ccucon0.B.FSIDIV == 0)
    {
        frequency = 0;
    }
    else
    {
        frequency = IfxScuCcu_getSriFrequency();

        if ((ccucon0.B.FSIDIV == 1) || (ccucon0.B.SRIDIV == 1) || (ccucon0.B.SRIDIV == 2))
        {
            frequency = frequency / ccucon0.B.FSIDIV;
        }
    }

    return frequency;
}


float32 IfxScuCcu_getMaxFrequency(void)
{
    float32 maxFrequency;
    float32 sourceFrequency;
    sourceFrequency = IfxScuCcu_getSourceFrequency();

    switch (SCU_CCUCON0.B.LPDIV)
    {
    case 0:                    /*Not in low power mode */

        if (SCU_CCUCON5.B.MAXDIV == 0)
        {
            maxFrequency = sourceFrequency;
        }
        else
        {
            maxFrequency = sourceFrequency / SCU_CCUCON5.B.MAXDIV;
        }

        break;
    case 1:
        maxFrequency = sourceFrequency / 15;
        break;
    case 2:
        maxFrequency = sourceFrequency / 30;
        break;
    case 3:
        maxFrequency = sourceFrequency / 60;
        break;
    case 4:
        maxFrequency = sourceFrequency / 120;
        break;
    default:
        maxFrequency = 0.0;
        break;
    }

    return maxFrequency;
}


float32 IfxScuCcu_getModuleFrequency(void)
{
    float32     spbFreq;
    float32     moduleFreq;
    Ifx_SCU_FDR scuFdr;
    scuFdr  = SCU_FDR;
    spbFreq = IfxScuCcu_getSpbFrequency();

    if (scuFdr.B.DM == 1)
    {
        moduleFreq = spbFreq / (1024 - scuFdr.B.STEP);
    }
    else if (scuFdr.B.DM == 2)
    {
        moduleFreq = (spbFreq * scuFdr.B.STEP) / 1024;
    }
    else
    {
        moduleFreq = 0;
    }

    return moduleFreq;
}


float32 IfxScuCcu_getPllErayFrequency(void)
{
    Ifx_SCU *scu = &MODULE_SCU;
    float32  oscFreq;
    float32  freq;

    oscFreq = IfxScuCcu_getOscFrequency();

    if (scu->PLLERAYSTAT.B.VCOBYST == 1)
    {
        /* Prescaler mode */
        freq = oscFreq / (scu->PLLERAYCON1.B.K1DIV + 1);
    }
    else if (scu->PLLERAYSTAT.B.FINDIS == 1)
    {
        /* Free running mode */
        freq = IFXSCU_VCO_BASE_FREQUENCY / (scu->PLLERAYCON1.B.K2DIV + 1);
    }
    else
    {
        /* Normal mode */
        freq = (oscFreq * (scu->PLLERAYCON0.B.NDIV + 1)) / (scu->PLLERAYCON1.B.K2DIV + 1);
    }

    return freq;
}


float32 IfxScuCcu_getPllErayVcoFrequency(void)
{
    float32 vcoFreq;

    if (SCU_PLLERAYSTAT.B.FINDIS == 1)
    {
        /* Free running mode */
        vcoFreq = IFXSCU_VCO_BASE_FREQUENCY;
    }
    else
    {
        /* Normal mode */
        vcoFreq = (IfxScuCcu_getOscFrequency() * (SCU_PLLERAYCON0.B.NDIV + 1)) / (SCU_PLLERAYCON0.B.PDIV + 1);
    }

    return vcoFreq;
}


float32 IfxScuCcu_getPllFrequency(void)
{
    Ifx_SCU *scu = &MODULE_SCU;
    float32  oscFreq;
    float32  freq;

    oscFreq = IfxScuCcu_getOscFrequency();

    if (scu->PLLSTAT.B.VCOBYST == 1)
    {
        /* Prescaler mode */
        freq = oscFreq / (scu->PLLCON1.B.K1DIV + 1);
    }
    else if (scu->PLLSTAT.B.FINDIS == 1)
    {
        /* Free running mode */
        freq = IFXSCU_VCO_BASE_FREQUENCY / (scu->PLLCON1.B.K2DIV + 1);
    }
    else
    {
        /* Normal mode */
        freq = (oscFreq * (scu->PLLCON0.B.NDIV + 1)) / ((scu->PLLCON1.B.K2DIV + 1) * (scu->PLLCON0.B.PDIV + 1));
    }

    return freq;
}


float32 IfxScuCcu_getPllVcoFrequency(void)
{
    float32 vcoFreq;

    if (SCU_PLLSTAT.B.FINDIS == 1)
    {
        /* Free running mode */
        vcoFreq = IFXSCU_VCO_BASE_FREQUENCY;
    }
    else
    {
        /* Normal mode */
        vcoFreq = (IfxScuCcu_getOscFrequency() * (SCU_PLLCON0.B.NDIV + 1)) / (SCU_PLLCON0.B.PDIV + 1);
    }

    return vcoFreq;
}


float32 IfxScuCcu_getSourceFrequency(void)
{
    float32 sourcefreq;

    switch (SCU_CCUCON0.B.CLKSEL)
    {
    case IfxScu_CCUCON0_CLKSEL_fBack:
        sourcefreq = IfxScuCcu_getEvrFrequency();
        break;
    case IfxScu_CCUCON0_CLKSEL_fPll:
        sourcefreq = IfxScuCcu_getPllFrequency();
        break;
    default:
        sourcefreq = 0;
        break;
    }

    return sourcefreq;
}


float32 IfxScuCcu_getSpbFrequency(void)
{
    float32 spbFrequency;
    float32 sourceFrequency;
    sourceFrequency = IfxScuCcu_getSourceFrequency();

    switch (SCU_CCUCON0.B.LPDIV)
    {
    case 0:                    /*Not in low power mode */

        if (SCU_CCUCON0.B.SPBDIV == 0)
        {
            spbFrequency = 0.0;
        }
        else
        {
            spbFrequency = sourceFrequency / SCU_CCUCON0.B.SPBDIV;
        }

        break;
    case 1:
        spbFrequency = sourceFrequency / 30;
        break;
    case 2:
        spbFrequency = sourceFrequency / 60;
        break;
    case 3:
        spbFrequency = sourceFrequency / 120;
        break;
    case 4:
        spbFrequency = sourceFrequency / 240;
        break;
    default:
        spbFrequency = 0.0;
        break;
    }

    return spbFrequency;
}


float32 IfxScuCcu_getSriFrequency(void)
{
    float32 sriFrequency;
    float32 sourceFrequency;
    sourceFrequency = IfxScuCcu_getSourceFrequency();

    switch (SCU_CCUCON0.B.LPDIV)
    {
    case 0:                    /*Not in low power mode */

        if (SCU_CCUCON0.B.SRIDIV == 0)
        {
            sriFrequency = 0.0;
        }
        else
        {
            sriFrequency = sourceFrequency / SCU_CCUCON0.B.SRIDIV;
        }

        break;
    case 1:
        sriFrequency = sourceFrequency / 30;
        break;
    case 2:
        sriFrequency = sourceFrequency / 60;
        break;
    case 3:
        sriFrequency = sourceFrequency / 120;
        break;
    case 4:
        sriFrequency = sourceFrequency / 240;
        break;
    default:
        sriFrequency = 0.0;
        break;
    }

    return sriFrequency;
}


boolean IfxScuCcu_init(const IfxScuCcu_Config *cfg)
{
    uint8   smuTrapEnable;
    uint16  endinit_pw, endinitSfty_pw;
    boolean status = 0;

    endinit_pw     = IfxScuWdt_getCpuWatchdogPassword();
    endinitSfty_pw = IfxScuWdt_getSafetyWatchdogPassword();

    {                           /* Disable TRAP for SMU (oscillator watchdog and unlock detection) */
        IfxScuWdt_clearCpuEndinit(endinit_pw);
        smuTrapEnable      = SCU_TRAPDIS.B.SMUT;
        SCU_TRAPDIS.B.SMUT = 1U;
        IfxScuWdt_setCpuEndinit(endinit_pw);
    }

    {
        /* Select fback (fosc-evr) as CCU input clock */
        IfxScuWdt_clearSafetyEndinit(endinitSfty_pw);

        while (SCU_CCUCON0.B.LCK != 0U)
        {                       /*Wait till ccucon0 lock is set */
            /*No "timeout" required, because if it hangs, Safety Endinit will give a trap */
        }

        SCU_CCUCON0.B.CLKSEL = 0; /*Select the EVR as fOSC for the clock distribution */
        SCU_CCUCON0.B.UP     = 1; /*Update the ccucon0 register */

        /* Disconnet PLL (SETFINDIS=1): oscillator clock is disconnected from PLL */
        SCU_PLLCON0.B.SETFINDIS = 1;
        /* Now PLL is in free running mode */

        /* Select Clock Source as PLL input clock */
        while (SCU_CCUCON0.B.LCK != 0U)
        {                       /*Wait till ccucon0 lock is set */
            /*No "timeout" required, because if it hangs, Safety Endinit will give a trap */
        }

        SCU_CCUCON1.B.INSEL = 1; /*Select oscillator OSC0 as clock to PLL */
        SCU_CCUCON1.B.UP    = 1; /*Update the ccucon0 register */

        status             |= IfxScuCcu_isOscillatorStable();

        IfxScuWdt_setSafetyEndinit(endinitSfty_pw);
    }

    if (status == 0)
    {                           /*Start the PLL configuration sequence */
        uint8 pllStepsCount;

        /*Setting up P N and K2 values equate pll to evr osc freq */
        {
            {                   /*Set the K2 divider value for the step corresponding to step count */
                IfxScuWdt_clearSafetyEndinit(endinitSfty_pw);

                while (SCU_PLLSTAT.B.K2RDY == 0U)
                {               /*Wait until K2 divider is ready */
                    /*No "timeout" required because Safety Endinit will give a trap */
                }

                SCU_PLLCON1.B.K2DIV = cfg->pllInitialStep.k2Initial;

                if ((SCU_PLLCON0.B.PDIV != cfg->pllInitialStep.pDivider) ||
                    (SCU_PLLCON0.B.NDIV != cfg->pllInitialStep.nDivider))
                {
                    /*change P and N divider values */
                    SCU_PLLCON0.B.PDIV = cfg->pllInitialStep.pDivider;
                    SCU_PLLCON0.B.NDIV = cfg->pllInitialStep.nDivider;

                    /* Disable oscillator disconnect feature
                     * in case of PLL unlock, PLL stays connected to fref */
                    SCU_PLLCON0.B.OSCDISCDIS = 1;
                    /* Connect PLL to fREF as oscillator clock is connected to PLL   */
                    SCU_PLLCON0.B.CLRFINDIS  = 1;

                    IfxScuCcu_wait(0.000050F);  /*Wait for 50us */

                    /* Restart PLL lock detection (RESLD = 1) */
                    SCU_PLLCON0.B.RESLD = 1;

                    while (SCU_PLLSTAT.B.VCOLOCK == 0U)
                    {           /* Wait for PLL lock */
                        /*No "timeout" required, because if it hangs, Safety Endinit will give a trap */
                    }

                    SCU_PLLCON0.B.VCOBYP = 0; /*VCO bypass disabled */

                    while (SCU_CCUCON0.B.LCK != 0U)
                    {                         /*Wait till ccucon registers can be written with new value */
                        /*No "timeout" required, because if it hangs, Safety Endinit will give a trap */
                    }

                    SCU_CCUCON0.B.CLKSEL = 0x01;

                    /*Configure the clock distribution */
                    while (SCU_CCUCON0.B.LCK != 0U)
                    {           /*Wait till ccucon registers can be written with new value */
                        /*No "timeout" required, because if it hangs, Safety Endinit will give a trap */
                    }

                    /*Wait until the initial clock configurations take in to effect for the PLL*/
                    IfxScuCcu_wait(cfg->pllInitialStep.waitTime); /*Wait for configured initial time */

                    {                                             /*Write CCUCON0 configuration */
                        Ifx_SCU_CCUCON0 ccucon0;
                        ccucon0.U        = SCU_CCUCON0.U & ~cfg->clockDistribution.ccucon0.mask;
                        /*update with configured value */
                        ccucon0.U       |= (cfg->clockDistribution.ccucon0.mask & cfg->clockDistribution.ccucon0.value);
                        ccucon0.B.CLKSEL = 0x01;    /*  Select fpll as CCU input clock, even if this was not selected by configuration */
                        ccucon0.B.UP     = 1;
                        SCU_CCUCON0      = ccucon0; /*Set update bit explicitly to make above configurations effective */
                    }

                    while (SCU_CCUCON1.B.LCK != 0U)
                    {           /*Wait till ccucon registers can be written with new value */
                        /*No "timeout" required, because if it hangs, Safety Endinit will give a trap */
                    }

                    {           /*Write CCUCON1 configuration */
                        Ifx_SCU_CCUCON1 ccucon1;
                        ccucon1.U       = SCU_CCUCON1.U & ~cfg->clockDistribution.ccucon1.mask;
                        /*update with configured value */
                        ccucon1.U      |= (cfg->clockDistribution.ccucon1.mask & cfg->clockDistribution.ccucon1.value);
                        ccucon1.B.INSEL = 1;
                        ccucon1.B.UP    = 1;
                        SCU_CCUCON1     = ccucon1;
                    }

                    while (SCU_CCUCON2.B.LCK != 0U)
                    {           /*Wait till ccucon registers can be written with new value */
                        /*No "timeout" required, because if it hangs, Safety Endinit will give a trap */
                    }

                    {                                             /*Write CCUCON2 configuration */
                        Ifx_SCU_CCUCON2 ccucon2;
                        ccucon2.U    = SCU_CCUCON2.U & ~cfg->clockDistribution.ccucon2.mask;
                        /*update with configured value */
                        ccucon2.U   |= (cfg->clockDistribution.ccucon2.mask & cfg->clockDistribution.ccucon2.value);
                        ccucon2.B.UP = 1;
                        SCU_CCUCON2  = ccucon2;
                    }

                    while (SCU_CCUCON5.B.LCK != 0U)
                    {           /*Wait till ccucon registers can be written with new value */
                        /*No "timeout" required, because if it hangs, Safety Endinit will give a trap */
                    }

                    {           /*Write CCUCON5 configuration */
                        Ifx_SCU_CCUCON5 ccucon5;
                        ccucon5.U    = SCU_CCUCON5.U & ~cfg->clockDistribution.ccucon5.mask;
                        /*update with configured value */
                        ccucon5.U   |= (cfg->clockDistribution.ccucon5.mask & cfg->clockDistribution.ccucon5.value);
                        ccucon5.B.UP = 1;
                        SCU_CCUCON5  = ccucon5;
                    }

                    {           /*Write CCUCON6 configuration */
                        Ifx_SCU_CCUCON6 ccucon6;
                        ccucon6.U   = SCU_CCUCON6.U & ~cfg->clockDistribution.ccucon6.mask;
                        /*update with configured value */
                        ccucon6.U  |= (cfg->clockDistribution.ccucon6.mask & cfg->clockDistribution.ccucon6.value);
                        SCU_CCUCON6 = ccucon6;
                    }
#if ((IFX_CFG_DEVICE == IFX_CFG_TC29X ) || (IFX_CFG_DEVICE == IFX_CFG_TC27X ) || (IFX_CFG_DEVICE == IFX_CFG_TC26X ))
                    {           /*Write CCUCON7 configuration */
                        Ifx_SCU_CCUCON7 ccucon7;
                        ccucon7.U   = SCU_CCUCON7.U & ~cfg->clockDistribution.ccucon7.mask;
                        /*update with configured value */
                        ccucon7.U  |= (cfg->clockDistribution.ccucon7.mask & cfg->clockDistribution.ccucon7.value);
                        SCU_CCUCON7 = ccucon7;
                    }
#endif
#if ((IFX_CFG_DEVICE == IFX_CFG_TC29X ) || (IFX_CFG_DEVICE == IFX_CFG_TC27X ))
                    {           /*Write CCUCON8 configuration */
                        Ifx_SCU_CCUCON8 ccucon8;
                        ccucon8.U   = SCU_CCUCON8.U & ~cfg->clockDistribution.ccucon8.mask;
                        /*update with configured value */
                        ccucon8.U  |= (cfg->clockDistribution.ccucon8.mask & cfg->clockDistribution.ccucon8.value);
                        SCU_CCUCON8 = ccucon8;
                    }
#endif
                }

                IfxScuWdt_setSafetyEndinit(endinitSfty_pw);
            }
        }

        {           /*Write Flash waitstate configuration */
            Ifx_FLASH_FCON fcon;
            fcon.U = FLASH0_FCON.U & ~cfg->flashFconWaitStateConfig.mask;

            /*update with configured value */
            fcon.U &= ~cfg->flashFconWaitStateConfig.mask;
            fcon.U |= (cfg->flashFconWaitStateConfig.mask & cfg->flashFconWaitStateConfig.value);
            {
                IfxScuWdt_clearCpuEndinit(endinit_pw);
                FLASH0_FCON = fcon;
                IfxScuWdt_setCpuEndinit(endinit_pw);
            }
        }

        /*Start Pll ramp up sequence */
        for (pllStepsCount = 0; pllStepsCount < cfg->numOfPllDividerSteps; pllStepsCount++)
        {                       /*iterate through number of pll steps */
            {
                IfxScuWdt_clearSafetyEndinit(endinitSfty_pw);

                /*Configure K2 divider */
                while (SCU_PLLSTAT.B.K2RDY == 0U)
                {               /*Wait until K2 divider is ready */
                    /*No "timeout" required, because if it hangs, Safety Endinit will give a trap */
                }

                /*Now set the K2 divider value for the step corresponding to step count */
                SCU_PLLCON1.B.K2DIV = cfg->pllDividerStep[pllStepsCount].k2Step;
                IfxScuWdt_setSafetyEndinit(endinitSfty_pw);
            }

            /*call the hook function if configured */
            if (cfg->pllDividerStep[pllStepsCount].hookFunction != (IfxScuCcu_PllStepsFunctionHook)0)
            {
                cfg->pllDividerStep[pllStepsCount].hookFunction();
            }

            /*Wait for waitCounter corresponding to the pll step */
            IfxScuCcu_wait(cfg->pllDividerStep[pllStepsCount].waitTime);
        }
    }

    {                           /* Enable oscillator disconnect feature */
        IfxScuWdt_clearSafetyEndinit(endinitSfty_pw);
        SCU_PLLCON0.B.OSCDISCDIS = 0U;
        IfxScuWdt_setSafetyEndinit(endinitSfty_pw);
    }
    {                           /* Enable VCO unlock Trap if it was disabled before */
        IfxScuWdt_clearCpuEndinit(endinit_pw);
        SCU_TRAPCLR.B.SMUT = 1U;
        SCU_TRAPDIS.B.SMUT = smuTrapEnable;
        IfxScuWdt_setCpuEndinit(endinit_pw);
    }
    return status;
}


void IfxScuCcu_initConfig(IfxScuCcu_Config *cfg)
{
    *cfg = IfxScuCcu_defaultClockConfig;
}


boolean IfxScuCcu_initErayPll(const IfxScuCcu_ErayPllConfig *cfg)
{
    uint8   smuTrapEnable;
    uint16  endinit_pw, endinitSfty_pw;
    boolean status = 0;
    uint8   i;

    endinit_pw     = IfxScuWdt_getCpuWatchdogPassword();
    endinitSfty_pw = IfxScuWdt_getSafetyWatchdogPassword();

    {                           /* Disable TRAP for SMU (oscillator watchdog and unlock detection) */
        IfxScuWdt_clearCpuEndinit(endinit_pw);
        smuTrapEnable      = SCU_TRAPDIS.B.SMUT;
        SCU_TRAPDIS.B.SMUT = 1U;
        IfxScuWdt_setCpuEndinit(endinit_pw);
    }
    IfxScuWdt_clearSafetyEndinit(endinitSfty_pw);

    // ensure that PLL enabled
    if (!SCU_PLLERAYCON0.B.PLLPWD || SCU_PLLERAYCON0.B.VCOPWD || SCU_PLLERAYSTAT.B.PWDSTAT)
    {   // PLLPWD=0 or VCOPWD=1 or PWDSTAT=1?
      // enable PLL and leave power saving mode
        SCU_PLLERAYCON0.B.PLLPWD = 1;
        SCU_PLLERAYCON0.B.VCOPWD = 0;

        while (SCU_PLLERAYSTAT.B.PWDSTAT)  // poll PWDSTAT
        {}

        /*Wait for waitCounter corresponding to the pll step */
        IfxScuCcu_wait(cfg->pllInitialStep.waitTime);
    }

    /* Enter Prescalar mode */
    /* Update K and N dividers */
    if (!SCU_PLLERAYSTAT.B.VCOBYST)      // checking PLLERAYBYPST flag
    {                                    // select "secure" K1 value - please check @silicon if K1=4 is ok
        while (!SCU_PLLERAYSTAT.B.K1RDY) // poll K1RDY before changing K
        {}

        SCU_PLLERAYCON1.B.K1DIV = 3;

        // activate VCO bypass (bit 0: VCOBYP=1)
        SCU_PLLERAYCON0.B.VCOBYP = 1;
    }

    while (!SCU_PLLERAYSTAT.B.K2RDY)     // poll K1RDY before changing K
    {}

    SCU_PLLERAYCON1.B.K2DIV = cfg->pllInitialStep.k2Initial;

    SCU_PLLERAYCON0.B.PDIV  = cfg->pllInitialStep.pDivider;
    SCU_PLLERAYCON0.B.NDIV  = cfg->pllInitialStep.nDivider;
    /*
     *  RESLD = 1     ==> Restart VCO lock detection
     *  CLRFINDIS = 1 ==> Connect OSC to PLL
     *  PLLPWD = 1    ==> PLL Power Saving Mode : Normal behaviour
     *  NDIV = NDIV
     */

    SCU_PLLERAYCON0.B.RESLD     = 1U;
    SCU_PLLERAYCON0.B.CLRFINDIS = 1U;

    IfxScuWdt_setSafetyEndinit(endinitSfty_pw);

    // Wait until VCO LOCK bit is set
    uint32 time_out_ctr = 50000; // higher time out value as for clib_pll, since system is clocked much faster while polling the lock flag

    while (--time_out_ctr && !SCU_PLLERAYSTAT.B.VCOLOCK)
    {}

    // check for timeout, exit immediately (don't disable VCO bypass) of not locked
    if (!time_out_ctr)
    {
        status = FALSE;
    }

    IfxScuWdt_clearSafetyEndinit(endinitSfty_pw);
    /*Bypass VCO*/
    SCU_PLLERAYCON0.B.VCOBYP = 0U;

    // wait until bypass has been deactivated
    while (SCU_PLLERAYSTAT.B.VCOBYST)         // poll VCOBYST
    {}

    if (!SCU_PLLERAYSTAT.B.VCOLOCK)
    {
        status = FALSE;
    }

    IfxScuWdt_setSafetyEndinit(endinitSfty_pw);

    /*Wait for waitCounter corresponding to the pll step */
    for (i = 0; i < 100; i++)
    {}

    {                           /* Enable VCO unlock Trap if it was disabled before */
        IfxScuWdt_clearCpuEndinit(endinit_pw);
        SCU_TRAPCLR.B.SMUT = 1U;
        SCU_TRAPDIS.B.SMUT = smuTrapEnable;
        IfxScuWdt_setCpuEndinit(endinit_pw);
    }
    return status;
}


void IfxScuCcu_initErayPllConfig(IfxScuCcu_ErayPllConfig *cfg)
{
    *cfg = IfxScuCcu_defaultErayPllConfig;
}


static boolean IfxScuCcu_isOscillatorStable(void)
{
    uint16  endinitPw  = IfxScuWdt_getCpuWatchdogPassword();
    sint32  TimeoutCtr = IFXSCUCCU_OSC_STABLECHK_TIME;
    boolean status     = 0;

    /* Mode External Crystal / Ceramic Resonator Mode and External Input Clock.
     * The oscillator Power-Saving Mode is not entered
     */
    SCU_OSCCON.B.MODE = 0U;

    if (IFX_CFG_SCU_XTAL_FREQUENCY <= 8000000)
    {
        SCU_OSCCON.B.OSCVAL = 2;
    }
    else
    {
        SCU_OSCCON.B.OSCVAL = 7;
    }

    /* The Oscillator Watchdog of the PLL is cleared and restarted */
    SCU_OSCCON.B.OSCRES = 1U;

    /* wait until PLLLV and PLLHV flags are set */
    while ((SCU_OSCCON.B.PLLLV == 0) || (SCU_OSCCON.B.PLLHV == 0))
    {
        TimeoutCtr--;

        if (TimeoutCtr == 0)
        {
            status = 1;
            break;
        }
    }

    {                            /* clear and then set SMU trap (oscillator watchdog and unlock detection) */
        IfxScuWdt_clearCpuEndinit(endinitPw);
        SCU_TRAPCLR.B.SMUT = 1U; /* TODO Can this be removed? */
        SCU_TRAPDIS.B.SMUT = 1U; /* TODO Can this be removed? */
        IfxScuWdt_setCpuEndinit(endinitPw);
    }
    return status;
}


void IfxScuCcu_selectAdcClock(IfxScuCcu_AdcClockSelection adcClkSel)
{
    uint16 password = IfxScuWdt_getSafetyWatchdogPassword();
    IfxScuWdt_clearSafetyEndinit(password);

    /*Wait till ccucon registers can be written with new value
     * No "timeout" required, because if it hangs, Safety Endinit will give a trap */
    while (SCU_CCUCON0.B.LCK)
    {}

    Ifx_SCU_CCUCON0 ccucon0 = SCU_CCUCON0;
    ccucon0.B.ADCCLKSEL = adcClkSel;
    ccucon0.B.UP        = 1U;
    SCU_CCUCON0.U       = ccucon0.U;
    IfxScuWdt_setSafetyEndinit(password);
}


float32 IfxScuCcu_setCpuFrequency(IfxCpu_ResourceCpu cpu, float32 cpuFreq)
{
    uint16  endinitSfty_pw;
    float32 sriFreq;
    uint32  cpuDiv;

    sriFreq = IfxScuCcu_getSriFrequency();

    if (cpuFreq >= sriFreq)
    {
        cpuDiv = 0;
    }
    else
    {
        cpuDiv = (uint32)((cpuFreq * 64) / sriFreq);
    }

    endinitSfty_pw = IfxScuWdt_getSafetyWatchdogPassword();

    {
        IfxScuWdt_clearSafetyEndinit(endinitSfty_pw);

        switch (cpu)
        {
        case IfxCpu_ResourceCpu_0:
            SCU_CCUCON6.U = cpuDiv;
            break;
#if ((IFX_CFG_DEVICE == IFX_CFG_TC29X ) || (IFX_CFG_DEVICE == IFX_CFG_TC27X ) || (IFX_CFG_DEVICE == IFX_CFG_TC26X ))
        case IfxCpu_ResourceCpu_1:
            SCU_CCUCON7.U = cpuDiv;
            break;
#endif
#if ((IFX_CFG_DEVICE == IFX_CFG_TC29X ) || (IFX_CFG_DEVICE == IFX_CFG_TC27X ))
        case IfxCpu_ResourceCpu_2:
            SCU_CCUCON8.U = cpuDiv;
            break;
#endif
        default:
            break;
        }

        IfxScuWdt_setSafetyEndinit(endinitSfty_pw);
    }

    if (cpuDiv != 0)
    {
        sriFreq = sriFreq * (cpuDiv / 64);
    }

    return sriFreq;
}


float32 IfxScuCcu_setPll2ErayFrequency(float32 pll2ErayFreq)
{
    uint16 password = IfxScuWdt_getSafetyWatchdogPassword();
    uint32 pll2Div  = (uint32)((IfxScuCcu_getPllErayVcoFrequency() / pll2ErayFreq) - 1);
    {
        IfxScuWdt_clearSafetyEndinit(password);
        SCU_PLLERAYCON1.B.K3DIV = pll2Div;
        IfxScuWdt_setSafetyEndinit(password);
    }
    return IfxScuCcu_getPll2ErayFrequency();
}


float32 IfxScuCcu_setPll2Frequency(float32 pll2Freq)
{
    uint16 endinitSfty_pw = IfxScuWdt_getSafetyWatchdogPassword();
    uint32 pll2Div        = (uint32)((IfxScuCcu_getPllVcoFrequency() / pll2Freq) - 1);
    {
        IfxScuWdt_clearSafetyEndinit(endinitSfty_pw);
        SCU_PLLCON1.B.K3DIV = pll2Div;
        IfxScuWdt_setSafetyEndinit(endinitSfty_pw);
    }
    return IfxScuCcu_getPll2Frequency();
}


float32 IfxScuCcu_setSpbFrequency(float32 spbFreq)
{
    /* TODO: check whether it is necessary to disable trap and/or the safety */
    uint16  l_EndInitPW;
    uint16  l_SEndInitPW;
    float32 inputFreq = IfxScuCcu_getSourceFrequency();
    uint32  spbDiv    = (uint32)(inputFreq / spbFreq);
    spbDiv       = __maxu(spbDiv, 2);
    spbDiv       = spbDiv & 0x2U; /* only even dividers */

    l_EndInitPW  = IfxScuWdt_getCpuWatchdogPassword();
    l_SEndInitPW = IfxScuWdt_getSafetyWatchdogPassword();

    IfxScuWdt_clearCpuEndinit(l_EndInitPW);
    SCU_TRAPDIS.U = SCU_TRAPDIS.U | 0x3E0U;
    IfxScuWdt_setCpuEndinit(l_EndInitPW);

    IfxScuWdt_clearSafetyEndinit(l_SEndInitPW);
    SCU_CCUCON0.B.SPBDIV = spbDiv;
    IfxScuWdt_setSafetyEndinit(l_SEndInitPW);

    IfxScuWdt_clearCpuEndinit(l_EndInitPW);
    SCU_TRAPDIS.U = SCU_TRAPDIS.U & (uint32)~0x3E0UL;
    IfxScuWdt_setCpuEndinit(l_EndInitPW);

    return IfxScuCcu_getSpbFrequency();
}


static void IfxScuCcu_wait(float32 timeSec)
{
    uint32 stmCount      = (uint32)(IfxScuCcu_getStmFrequency() * timeSec);
    uint32 stmCountBegin = STM0_TIM0.U;

    while ((uint32)(STM0_TIM0.U - stmCountBegin) < stmCount)
    {
        /* There is no need to check overflow of the STM timer.
         * When counter after overflow subtracted with counter before overflow,
         * the subtraction result will be as expected, as long as both are unsigned 32 bits
         * eg: stmCountBegin= 0xFFFFFFFE (before overflow)
         *     stmCountNow = 0x00000002 (before overflow)
         *     diff= stmCountNow - stmCountBegin = 4 as expected.*/
    }
}


float32 IfxScuCcu_setGtmFrequency(float32 gtmFreq)
{
    uint16          l_SEndInitPW;
    Ifx_SCU_CCUCON1 ccucon1   = SCU_CCUCON1;

    float32         inputFreq = IfxScuCcu_getSourceFrequency();
    uint32          gtmDiv    = (uint32)__roundf(inputFreq / gtmFreq);
    gtmDiv = __maxu(gtmDiv, 1);

    /*gtmDiv       = gtmDiv & 0x2U;*//* only even dividers */
    if ((gtmDiv >= 7) && (gtmDiv < 14) && ((gtmDiv & 1) == 1))
    {
        gtmDiv = gtmDiv - 1;
    }

    if (gtmDiv == 14)
    {
        gtmDiv = 12;
    }

    l_SEndInitPW     = IfxScuWdt_getSafetyWatchdogPassword();
    IfxScuWdt_clearSafetyEndinit(l_SEndInitPW);
    ccucon1.B.GTMDIV = gtmDiv;
    ccucon1.B.UP     = 1U;
    SCU_CCUCON1.U    = ccucon1.U;

    IfxScuWdt_setSafetyEndinit(l_SEndInitPW);

    return IfxScuCcu_getGtmFrequency();
}
#if 0
#if (IFX_CFG_SCUCCU_MON_TRIGGER == STD_ON)
void IfxScuCcu_ClockMonitor(void)
{
  uint16 l_SEndInitPW;

  l_SEndInitPW = IfxScuWdt_getSafetyWatchdogPassword ();

  IfxScuWdt_clearSafetyEndinit(l_SEndInitPW);

    SCU_CCUCON3.U   |= ( (SCU_CCUCON3.U & IFXSTART_CCUCON_UP_MASK) |  \
                         (IFXSTART_PLL_MON_DIV   << 0U) | \
                         (IFXSTART_PLL_MON_FREQ << 6U) | \
                         (IFXSTART_SRI_MON_DIV  << 16U) | \
                         (IFXSTART_SRI_MON_FREQ << 22U)
                       );

    SCU_CCUCON4.U   |= ( (SCU_CCUCON4.U & IFXSTART_CCUCON_UP_MASK) |  \
                         (IFXSTART_SPB_MON_DIV   << 0U) | \
                         (IFXSTART_SPB_MON_FREQ  << 6U) | \
                         (IFXSTART_GTM_MON_DIV   << 8U) | \
                         (IFXSTART_GTM_MON_FREQ  << 14U) | \
                         (IFXSTART_STM_MON_DIV   << 16U) | \
                         (IFXSTART_STM_MON_FREQ  << 22U) | \
                         (1U << 30U)
                       );
    IfxScuWdt_setSafetyEndinit(l_SEndInitPW);
}
#endif
/* #if (IFX_CFG_SCUCCU_MON_TRIGGER == STD_ON) */
#endif

void IfxScuCcu_enable_ClockOut (uint16 Step_Val , uint8 Clk_Sel , uint8 Clk)
{
  uint16 l_SEndInitPW;

  l_SEndInitPW = IfxScuWdt_getSafetyWatchdogPassword ();

  IfxScuWdt_clearSafetyEndinit(l_SEndInitPW);

  if(0U == Clk)
  {
    SCU_EXTCON.B.EN0   = 1U;
    SCU_EXTCON.B.SEL0  = Clk_Sel;
    SCU_FDR.B.STEP     = (IFXSCUCCU_EXTCLK0_STEP_MASK - Step_Val) ;
    /* normal divider mode */
    SCU_FDR.B.DM       = 1U ;
  }
  else
  {
    SCU_EXTCON.B.EN1   = 1U;
    SCU_EXTCON.B.SEL1  = Clk_Sel;
    SCU_EXTCON.B.DIV1  = (Step_Val - 1U);
  }
    IfxScuWdt_setSafetyEndinit(l_SEndInitPW);
}
