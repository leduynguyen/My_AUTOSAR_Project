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

/* ----------------------------[includes]------------------------------------*/

#include "Adc.h"
#include "Adc_TMS570.h" /* Use Texas Instrument header-file*/
#include "Adc_Internal2.h"

#if defined(USE_DET)
#include "Det.h"
#endif
#include "isr.h"
#include "irq_types.h"

/* ----------------------------[private define]------------------------------*/

#define EV_THR_INT_FLG_MASK	(1uL<<0u)
#define EV_END_MASK			(1uL<<3u)

/* ----------------------------[private macro]-------------------------------*/
/*lint -emacro(923,GET_HW_PTR) -emacro(9016,GET_HW_PTR) Access to HW registers */
#define GET_HW_PTR(_unit)	(adcREG1 + (_unit))

/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

static void ADCConversionComplete_Isr(uint32 adc, Adc_GroupType group);
ISR( ADC1Grp1ConversionComplete_Isr);
ISR( ADC1Grp2ConversionComplete_Isr);
ISR( ADC2Grp1ConversionComplete_Isr);
ISR( ADC2Grp2ConversionComplete_Isr);

uint32 ChannelMask[2u][3u];

void Adc_Hw_Init(const Adc_ConfigType *ConfigPtr) {
    (void) (ConfigPtr); /*lint !e920 Not used by this arch */
    uint32 channels = 0;

    /*
     * We have up to 2 controllers with 2 "normal" groups that
     * we need to initialize.
     *
     * Create the channels masks needed by HW
     * IMPROVEMENT: We should generate the mask
     */

    /* Loop over all controllers */
    for (uint32 configId = 0; configId < ADC_ARC_CTRL_CONFIG_CNT; configId++) {
        const Adc_ConfigType *AdcConfigPtr = GET_CONFIG_PTR(configId);

        adcBASE_t *hwPtr = GET_HW_PTR(AdcConfigPtr->hwConfigPtr->hwUnitId);

        /* Release from Reset */
        hwPtr->RSTCR = 0;

        /* Enable ADC and setup 10bit ADC, leave the rest of the values as reset */
        hwPtr->OPMODECR = 0x00140001;

        /* Setup prescaler */
        hwPtr->CLOCKCR = AdcConfigPtr->hwConfigPtr->adcPrescale - 1uL;

        /* ...and over the groups */
        for (Adc_GroupType group = 0; group < AdcConfigPtr->nbrOfGroups; group++) {

            const Adc_GroupDefType *groupPtr = &(AdcConfigPtr->groupConfigPtr[group]);
            /* ...and over the channels */
            for (uint32 i = 0u; i < (uint32_t) groupPtr->numberOfChannels; i++) {
                /* Select physical channel. */
                channels |= (1uL << (uint32) groupPtr->channelList[i]);
            }

            /* Assign the channels to the group */
            ChannelMask[AdcConfigPtr->hwConfigPtr->hwUnitId][group] = channels;
            channels = 0;

            /* Setup Sample time */
            hwPtr->GxSAMP[group + 1] = groupPtr->arcAdcGroupSampTime & 0x3ffuL;
        }
    }

    /* Install all handlers */
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
    ISR_INSTALL_ISR2("ADC1Grp1ConvComplete", ADC1Grp1ConversionComplete_Isr, MIBADC1_GROUP_1, ADC_ISR_PRIORITY, 0);
    ISR_INSTALL_ISR2("ADC1Grp2ConvComplete", ADC1Grp2ConversionComplete_Isr, MIBADC1_GROUP_2, ADC_ISR_PRIORITY, 0);
    ISR_INSTALL_ISR2("ADC2Grp1ConvComplete", ADC2Grp1ConversionComplete_Isr, MIBADC2_GROUP_1, ADC_ISR_PRIORITY, 0);
    ISR_INSTALL_ISR2("ADC2Grp2ConvComplete", ADC2Grp2ConversionComplete_Isr, MIBADC2_GROUP_2, ADC_ISR_PRIORITY, 0);
#endif
}

#if (ADC_DEINIT_API == STD_ON)
void Adc_Hw_DeInit (void) {
    /* @req SWS_Adc_00110 */
    /* @req SWS_Adc_00111 */

    /* Set AD Reset Control Register(ADRSTCR) to reset all ADC internal state
     * machines and control and status registers */
    adcREG1->RSTCR = 0x1uL;
    adcREG2->RSTCR = 0x1uL;
}
#endif

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
void Adc_Hw_StartGroupConversion (Adc_GroupType group)
{
    uint32 hwId = group / ADC_NOF_GROUP_PER_CONTROLLER;
    uint32 groupIdx = group % ADC_NOF_GROUP_PER_CONTROLLER;

    /* Generate interrupt at end of conversion  */
    GET_HW_PTR(hwId)->GxINTENA[groupIdx + 1] = 0x8uL;
    GET_HW_PTR(hwId)->GxTHRINTCR[groupIdx+1] = 1; /* One conversion */

    /* Write to GxSEL to start the conversion */
    GET_HW_PTR(hwId)->GxSEL[groupIdx+1] = ChannelMask[hwId][groupIdx];
}

void Adc_Hw_StopGroupConversion (Adc_GroupType group)
{
    uint32 hwId = group / ADC_NOF_GROUP_PER_CONTROLLER;
    uint32 groupIdx = group % ADC_NOF_GROUP_PER_CONTROLLER;

    /* disable interrupt for group   */
    GET_HW_PTR(hwId)->GxINTENA[groupIdx + 1] &= ~0x8uL;
    GET_HW_PTR(hwId)->GxTHRINTCR[groupIdx+1] = 0; /* No conversion */

    /* @req SWS_Adc_00385 */
    /* @req SWS_Adc_00386 */

    /* Write to GxSEL to stop the conversion */
    GET_HW_PTR(hwId)->GxSEL[groupIdx+1] = 0;
}
#endif

ISR( ADC1Grp1ConversionComplete_Isr) {
    ADCConversionComplete_Isr(0uL, 1uL);
}

ISR( ADC1Grp2ConversionComplete_Isr) {
    ADCConversionComplete_Isr(0uL, 2uL);
}

ISR( ADC2Grp1ConversionComplete_Isr) {
    ADCConversionComplete_Isr(1uL, 1uL);
}

ISR( ADC2Grp2ConversionComplete_Isr) {
    ADCConversionComplete_Isr(1uL, 2uL);
}

static void ADCConversionComplete_Isr(uint32 adc, Adc_GroupType hwGroup) {
    uint32 configId;

    for (configId = 0; configId < ADC_ARC_CTRL_CONFIG_CNT; configId++) {
        if( GET_CONFIG_PTR(configId)->hwConfigPtr->hwUnitId == adc ){
            break;
        }
    }

    /* Get group, -1 is since hwGroup is TMS570 group that starts at 1...index starts at 0 */
    const Adc_GroupDefType * groupPtr = &(GET_CONFIG_PTR(configId)->groupConfigPtr[hwGroup - 1]);
    uint32 data;

    adcBASE_t *hwPtr = GET_HW_PTR(adc);

    /* Copy the complete group to it's result registers */
    for (uint32 i = 0; i < (uint32) groupPtr->numberOfChannels; i++) {
        /* Read from FIFO */
        data = hwPtr->GxBUF[hwGroup].BUF0;

        /* Mask away not needed things and put in result buffer */
        groupPtr->status->currResultBufPtr[i * groupPtr->streamNumSamples] = ((uint16) data & 0x3ffu);
    }

    /* Clear interrupts */
    hwPtr->GxINTFLG[hwGroup] = (EV_END_MASK | EV_THR_INT_FLG_MASK);

    Adc_Internal_Isr(groupPtr);
}

void Adc_Hw_IsrPost(const Adc_GroupDefType * groupPtr, boolean enableInt) {
    if (enableInt) {
        /* Write to GxSEL to start the conversion */
        volatile uint32 *p = &(GET_HW_PTR(groupPtr->hwUnit)->GxSEL[groupPtr->groupId % ADC_NOF_GROUP_PER_CONTROLLER + 1]);
        *p = *p;
    }
}

