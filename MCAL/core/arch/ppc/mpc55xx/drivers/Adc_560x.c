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

/* In order to support multiple hw units we need to match group to a certain hw controller.
 * We handle this in a very simple way i.e. group 0-99 -> hwUnitId 0, group 100-199 -> hwUnitId 1 etc.*
 */

/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */
/** @tagSettings DEFAULT_ARCHITECTURE=PPC|MPC5607B|MPC5645S|MPC5748G */

/* ----------------------------[includes]------------------------------------*/

#include "arc_assert.h"
#include "Std_Types.h"
#include "mpc55xx.h"
#include "Mcu.h"
#include "Adc.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "Os.h"
#include "isr.h"
#include "irq.h"
#include "arc.h"
#include "Adc_Internal.h"
/* ----------------------------[private define]------------------------------*/


/* DMA support is only experimental for 5606 */
#define DONT_USE_DMA_IN_ADC_MPC560X

#if ( defined(CFG_MPC5606S) && !defined(DONT_USE_DMA_IN_ADC_MPC560X) )
    #define ADC_USES_DMA
    #include "Dma.h"
#endif

#if ( defined(ADC_USES_DMA) && !defined(USE_DMA) )
    #error Adc is configured to use Dma but the module is not enabled.
#endif


#if defined(CFG_MPC5668)
#define ADC0_EOC_INT 	ADC_A_EOC
#define ADC0_ER_INT 		ADC_A_ERR
#define	ADC0_WD_INT		ADC_A_WD
#define ADC1_EOC_INT 	ADC_B_EOC
#define ADC1_ER_INT 		ADC_B_ERR
#define	ADC1_WD_INT		ADC_B_WD
#endif

#if defined(CFG_MPC5668)
#define ADC_BASE_ADDRESS 0xFFF80000
#define GET_HW_CONTROLLER(_controller)  \
                            ((volatile struct ADC_tag *)(ADC_BASE_ADDRESS + 0x4000*(_controller)))
#elif defined(CFG_MPC5744P)
static volatile struct ADC_tag* const ADC_HW[] = {&ADC_0, &ADC_1, &ADC_2, &ADC_3};
#define GET_HW_CONTROLLER(_controller) ADC_HW[_controller]
#elif defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
/*lint -e{923} OTHER required operation */
static volatile struct ADC_tag* const ADC_HW[] = {&ADC_0, &ADC_1};
#define GET_HW_CONTROLLER(_controller) ADC_HW[_controller]
#elif defined(CFG_MPC5777M)
#define ADC_tag SARADC_tag
static volatile struct ADC_tag* const ADC_HW[] = {&SARADC_0, &SARADC_1, &SARADC_2, &SARADC_3, &SARADC_4, &SARADC_5, &SARADC_6, &SARADC_7, &SARADC_8, &SARADC_9, &SARADC_10, &SARADC_B};
#define GET_HW_CONTROLLER(_controller) ADC_HW[_controller]
#else
#define ADC_BASE_ADDRESS 0xFFE00000UL
#define GET_HW_CONTROLLER(_controller)  \
                            ((volatile struct ADC_tag *)(ADC_BASE_ADDRESS + ((_controller)*0x00004000uL)))

#endif


#define GET_HWUNITID_FROM_GROUP(_group) (_group / ADC_NOF_GROUP_PER_CONTROLLER)

/* ----------------------------[private macro]-------------------------------*/
/* Development error macros. */
#if ( ADC_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          Det_ReportError(ADC_MODULE_ID,0,_api,_err); \
          return; \
        }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
        if( !(_exp) ) { \
          Det_ReportError(ADC_MODULE_ID,0,_api,_err); \
          return (_rv); \
        }
#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_W_RV(_exp,_api,_err,_rv )
#endif
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
#ifdef ADC_HWUNIT_ADC_CTRL_0_ENABLED
/**
 * Interrupt Service Routine for HW unit 0
 */
ISR(Group0ConversionComplete_ADC0);
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_1_ENABLED
/**
 * Interrupt Service Routine for HW unit 1
 */
ISR(Group0ConversionComplete_ADC1);
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_2_ENABLED
/**
 * Interrupt Service Routine for HW unit 2
 */
ISR(Group0ConversionComplete_ADC2);
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_3_ENABLED
/**
 * Interrupt Service Routine for HW unit 3
 */
ISR(Group0ConversionComplete_ADC3);
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_4_ENABLED
/**
 * Interrupt Service Routine for HW unit 4
 */
ISR(Group0ConversionComplete_ADC4);
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_5_ENABLED
/**
 * Interrupt Service Routine for HW unit 5
 */
ISR(Group0ConversionComplete_ADC5);
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_6_ENABLED
/**
 * Interrupt Service Routine for HW unit 6
 */
ISR(Group0ConversionComplete_ADC6);
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_7_ENABLED
/**
 * Interrupt Service Routine for HW unit 7
 */
ISR(Group0ConversionComplete_ADC7);
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_8_ENABLED
/**
 * Interrupt Service Routine for HW unit 8
 */
ISR(Group0ConversionComplete_ADC8);
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_9_ENABLED
/**
 * Interrupt Service Routine for HW unit 9
 */
ISR(Group0ConversionComplete_ADC9);
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_10_ENABLED
/**
 * Interrupt Service Routine for HW unit 10
 */
ISR(Group0ConversionComplete_ADC10);
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_11_ENABLED
/**
 * Interrupt Service Routine for HW unit 11
 */
ISR(Group0ConversionComplete_ADC11);
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_B_ENABLED
/**
 * Interrupt Service Routine for HW unit B
 */
ISR(Group0ConversionComplete_ADCB);
#endif
/**
 * Interrupt Service Routine that all the others above use. This gets called when
 * an end of chain interrupt occurs.
 * @param unit Which HW unit
 */
void Group0ConversionComplete (uint32 unit);
/**
 * Sets the clock and powers up the ADC.
 * @param AdcConfigPtr  Pointer to the configuration to use.
 */
static void ConfigureADC (const Adc_ConfigType *AdcConfigPtr);
/**
 * Sets up the ISRs for ADC interrupts.
 */
static void ConfigureADCInterrupts (void);
/**
 * Called in interrupt context. Buffer pointers and sample counters are re-calculated here and
 * state is changed.
 *
 * @param adcGroup      Pointer to the groupDef to use.
 * @param hwPtr         Pointer to a struct of ADC registers for this hw unit.
 */
void GroupConversionComplete (const Adc_GroupDefType *adcGroup, volatile struct ADC_tag *hwPtr);
/* ----------------------------[private variables]---------------------------*/

/* static variable declarations */
static Adc_StateType adcState = ADC_STATE_UNINIT;
static const Adc_ConfigType *AdcGlobalConfigPtr;      /* Pointer to configuration structure. */
static const Adc_GroupDefType *Adc_CurrentConvGroupPtr[ADC_ARC_CTRL_CONFIG_CNT];

/* ----------------------------[private functions]---------------------------*/

/**
 * Gets the index for the supplied HW unit.
 * @param unit Which HW unit
 * @return Index for this HW unit.
 */
static uint8 GetControllerIndexFromHwUnitId(uint32 unit)
{
    uint8 idx = 0xff;

    if(adcState == ADC_STATE_INIT){
        for (uint8 configId = 0; configId < ADC_ARC_CTRL_CONFIG_CNT; configId++) {
            if(unit == AdcGlobalConfigPtr[configId].hwConfigPtr->hwUnitId){
                idx = configId;
                break;
            }
        }
    }
    ASSERT(idx < ADC_ARC_CTRL_CONFIG_CNT );

    return idx;
}
/**
 * Gets the configuration pointer for the supplied HW unit.
 * @param unit Which HW unit
 * @return Pointer to the Adc_Config for this HW unit.
 */
static const Adc_ConfigType * GetControllerConfigPtrFromHwUnitId(uint32 unit)
{
    const Adc_ConfigType *AdcConfigPtr = NULL;

    if(adcState == ADC_STATE_INIT){
        for (uint32 configId = 0; configId < ADC_ARC_CTRL_CONFIG_CNT; configId++) {
            if(unit == AdcGlobalConfigPtr[configId].hwConfigPtr->hwUnitId){
                AdcConfigPtr = &AdcGlobalConfigPtr[configId];
                break;
            }
        }
    }

    return AdcConfigPtr;
}

/**
 * Gets the configuration pointer for the HW unit for the supplied group
 * @param group Numeric ID of requested ADC Channel group
 * @return Pointer to the Adc_Config for this channel group
 */
static const Adc_ConfigType * GetControllerConfigPtrFromGroupId(Adc_GroupType group)
{
    return GetControllerConfigPtrFromHwUnitId(GET_HWUNITID_FROM_GROUP(group)); /*lint !e632 uint32 = Adc_GroupType = uint32 */
}

/* ----------------------------[public functions]----------------------------*/

/* @req SWS_Adc_00228 */
#if (ADC_DEINIT_API == STD_ON)
void Adc_DeInit (void)
{
    volatile struct ADC_tag *hwPtr;
    boolean okToClear = TRUE;

    for (uint32 configId = 0; configId < ADC_ARC_CTRL_CONFIG_CNT; configId++) {
        const Adc_ConfigType *AdcConfigPtr = &AdcGlobalConfigPtr[configId];

        if (E_OK == Adc_CheckDeInit(adcState, AdcConfigPtr))
        {
            Adc_CurrentConvGroupPtr[configId] = NULL;

            /* @req SWS_Adc_00110 */
            /*lint -e{9033} -e{923} Addressing memory mapped register so cast from integer to pointer ok */
            hwPtr = GET_HW_CONTROLLER(AdcGlobalConfigPtr[configId].hwConfigPtr->hwUnitId);
            for(Adc_GroupType group = 0; group < AdcConfigPtr->nbrOfGroups; group++)
            {
                /* Set group status to idle. */
                AdcConfigPtr->groupConfigPtr[group].status->groupStatus = ADC_IDLE;
            }

            /* Disable DMA transfer*/

#ifdef ADC_USES_DMA
#ifndef CFG_MPC5604B
            hwPtr->DMAE.B.DMAEN = 0;
#endif
#endif
            /* Power down ADC */
            hwPtr->MCR.R = 0x0001;

            /* Disable all interrupt*/
            /* @req SWS_Adc_00111 */
            hwPtr->IMR.R = 0;
        }
        else
        {
            /* Not ok to change adcState if any unit is running */
            okToClear = FALSE;
        }
    }

    if(TRUE == okToClear)
    {
        /* Clean internal status. */
        AdcGlobalConfigPtr = (Adc_ConfigType *)NULL;
        adcState = ADC_STATE_UNINIT;
    }
}
#endif

/* @req SWS_Adc_00056  */
/* @req SWS_Adc_00246  Module implementing function, writes the register.*/
/* @req SWS_Adc_00247  PORT should init register if reg is I/O and affetcs several modules*/
/* @req SWS_Adc_00248  MCU shold init register if not I/O but affects several modules*/
/* @req SWS_Adc_00249  One time writable registers that require init directly after reset should be inited by startup code*/
/* @req SWS_Adc_00250  All other registers shall be initialized by the startup code*/
void Adc_Init (const Adc_ConfigType *ConfigPtr)
{
    if ( E_OK == Adc_CheckInit(adcState, ConfigPtr) )
    {
        /* First of all, store the location of the global configuration data. */
        AdcGlobalConfigPtr = ConfigPtr;

        for (uint32 configId = 0; configId < ADC_ARC_CTRL_CONFIG_CNT; configId++)
        {
            const Adc_ConfigType *AdcConfigPtr = &AdcGlobalConfigPtr[configId];

            Adc_CurrentConvGroupPtr[configId] = NULL;

            for (Adc_GroupType group = 0; group < AdcConfigPtr->nbrOfGroups; group++)
            {
                /* @req  SWS_Adc_00307 */
                AdcConfigPtr->groupConfigPtr[group].status->groupStatus = ADC_IDLE;
                AdcConfigPtr->groupConfigPtr[group].status->currSampleCount = 0u;

                /* @req SWS_Adc_00077 */
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
                AdcConfigPtr->groupConfigPtr[group].status->notifictionEnable = 0;
#endif
            }

            /* Enable ADC. */
            ConfigureADC(AdcConfigPtr);
        }

        ConfigureADCInterrupts();

        /* Move on to INIT state. */
        adcState = ADC_STATE_INIT;
    }
}

Std_ReturnType Adc_SetupResultBuffer (Adc_GroupType group, Adc_ValueGroupType *DataBufferPtr)
{
  Std_ReturnType returnValue = E_NOT_OK;

  const Adc_ConfigType *AdcConfigPtr = GetControllerConfigPtrFromGroupId(group);

  /* Check for development errors. */
  if (E_OK == Adc_CheckSetupResultBuffer (adcState, AdcConfigPtr, group ,DataBufferPtr))
  {
      /* @req SWS_Adc_00420 */
    AdcConfigPtr->groupConfigPtr[group%ADC_NOF_GROUP_PER_CONTROLLER].status->resultBufferPtr = DataBufferPtr;
    
    returnValue = E_OK;
  }

  return (returnValue);
}

Adc_StreamNumSampleType Adc_GetStreamLastPointer(Adc_GroupType group, Adc_ValueGroupType** PtrToSamplePtr)
{
    /* @req SWS_Adc_00382  */
    /* @req SWS_Adc_00221 */
    /* @req SWS_Adc_00222 */
    const Adc_ConfigType *AdcConfigPtr = GetControllerConfigPtrFromGroupId(group);
    Adc_StreamNumSampleType nofSample = 0;
    *PtrToSamplePtr = NULL;

    /* Check for development errors. */
    if (E_OK == Adc_CheckGetStreamLastPointer (adcState, AdcConfigPtr, group))
    {
        const Adc_GroupDefType *groupPtr = &AdcConfigPtr->groupConfigPtr[group%ADC_NOF_GROUP_PER_CONTROLLER];

        /* Set resultPtr to application buffer. */

        /* @req SWS_Adc_00214 */
        /* @req SWS_Adc_00387 */
        *PtrToSamplePtr = &groupPtr->status->currResultBufPtr[0];
        nofSample = groupPtr->status->currSampleCount;


        if( (ADC_COMPLETED  == groupPtr->status->groupStatus) ){
            /* @req SWS_Adc_00328 */
            groupPtr->status->groupStatus = ADC_BUSY;
        }
        else if( ADC_STREAM_COMPLETED  == groupPtr->status->groupStatus )
        {
            if( (ADC_CONV_MODE_ONESHOT == groupPtr->conversionMode) &&
                    (ADC_TRIGG_SRC_SW == groupPtr->triggerSrc) &&
                    (ADC_ACCESS_MODE_SINGLE == groupPtr->accessMode)) {
                /* @req SWS_Adc_00327 */
                groupPtr->status->groupStatus = ADC_IDLE;
            }
            else if( (ADC_ACCESS_MODE_STREAMING == groupPtr->accessMode) &&
                    (ADC_STREAM_BUFFER_LINEAR == groupPtr->streamBufferMode) ){
                /* @req SWS_Adc_00327 */
                groupPtr->status->groupStatus = ADC_IDLE;
            }
            else if( ADC_CONV_MODE_CONTINUOUS == groupPtr->conversionMode ){
                /* @req SWS_Adc_00326 */
                groupPtr->status->groupStatus = ADC_BUSY;
            }
            else
            {
                /* MISRA */
            }
        }
        else
        {
            /* MISRA */
        }
    }
    else
    {
        /* MISRA */
    }

    return nofSample;

}

#if (ADC_READ_GROUP_API == STD_ON)
Std_ReturnType Adc_ReadGroup (Adc_GroupType group, Adc_ValueGroupType *dataBufferPtr)
{
    /* @req SWS_Adc_00383  */
    /* @req SWS_Adc_00221 */
    /* @req SWS_Adc_00222 */
    Std_ReturnType returnValue = E_NOT_OK;
    Adc_ChannelType channel;
    Adc_ValueGroupType const *tmpPointer;
    const Adc_ConfigType *AdcConfigPtr = GetControllerConfigPtrFromGroupId(group);

    if ( (E_OK == Adc_CheckReadGroup (adcState, AdcConfigPtr, group)) && (dataBufferPtr != NULL) )
    {
        const Adc_GroupDefType *groupPtr = &AdcConfigPtr->groupConfigPtr[group%ADC_NOF_GROUP_PER_CONTROLLER];

        returnValue = E_OK;

        if ((ADC_CONV_MODE_ONESHOT == groupPtr->conversionMode) &&
                (ADC_STREAM_COMPLETED  == groupPtr->status->groupStatus))
        {
            /** @req SWS_Adc_00330. */
            groupPtr->status->groupStatus = ADC_IDLE;
        }
        else if ((ADC_CONV_MODE_CONTINUOUS == groupPtr->conversionMode) &&
                (ADC_STREAM_BUFFER_LINEAR == groupPtr->streamBufferMode) &&
                (ADC_ACCESS_MODE_STREAMING == groupPtr->accessMode) &&
                (ADC_STREAM_COMPLETED    == groupPtr->status->groupStatus))
        {
            /** @req SWS_Adc_00330. */
            groupPtr->status->groupStatus = ADC_IDLE;
        }
        else if ((ADC_CONV_MODE_CONTINUOUS == groupPtr->conversionMode) &&
                (ADC_STREAM_COMPLETED    == groupPtr->status->groupStatus))
        {
            /** @req SWS_Adc_00329 */
            groupPtr->status->groupStatus = ADC_BUSY;
        }
        else if (ADC_COMPLETED    == groupPtr->status->groupStatus)
        {
            /* @req SWS_Adc_00331. */
            groupPtr->status->groupStatus = ADC_BUSY;
        }
        else{/* MISRA */}
        /* Copy the result to application buffer. */
        for (channel = 0; channel < groupPtr->numberOfChannels; channel++)
        {
            /* Remeber that the result buffer has the following layout: CH1_SMPL1, CH1_SMPL2, CH2_SMPL1, CH2_SMPL2 */
            /* @req SWS_Adc_00075 */
            tmpPointer = groupPtr->status->currResultBufPtr;
            if( ADC_ACCESS_MODE_STREAMING == groupPtr->accessMode )
            {
                if( ADC_STREAM_BUFFER_LINEAR == groupPtr->streamBufferMode ){
                    tmpPointer--;
                }
                else if( ADC_STREAM_BUFFER_CIRCULAR == groupPtr->streamBufferMode ){
                    /* Handle buffer wrapping */
                    if( tmpPointer > groupPtr->status->resultBufferPtr ){ /*lint !e946 Both pointers pointing to same memory object*/
                        tmpPointer--;
                    }
                    else{
                        tmpPointer = &(groupPtr->status->resultBufferPtr[groupPtr->streamNumSamples-1]);
                    }
                }
                else{
                    /*MISRA*/
                }
            }
            dataBufferPtr[channel] = tmpPointer[channel*(uint32)groupPtr->streamNumSamples];
        }
    }

    return (returnValue);
}
#endif

void GroupConversionComplete (const Adc_GroupDefType *adcGroup, volatile struct ADC_tag *hwPtr)
{
    if(ADC_ACCESS_MODE_SINGLE == adcGroup->accessMode )
    {
        /* @req SWS_Adc_00387 */
        adcGroup->status->currSampleCount = 1;

        /* @req SWS_Adc_00325 */
        adcGroup->status->groupStatus = ADC_STREAM_COMPLETED;

        if( adcGroup->conversionMode == ADC_CONV_MODE_CONTINUOUS )
        {
            /* Turn on the end of chain interrupt again */            
            hwPtr->IMR.B.MSKECH = 1;	        
        }
        else
        {            
            /* Stop sampling */
            hwPtr->MCR.B.NSTART=0;
        }
    }
    else
    {
        if(ADC_STREAM_BUFFER_LINEAR == adcGroup->streamBufferMode)
        {
            adcGroup->status->currResultBufPtr++;

            adcGroup->status->currSampleCount++;
            if(adcGroup->status->currSampleCount < adcGroup->streamNumSamples)
            {
                /* @req SWS_Adc_00224 */
                adcGroup->status->groupStatus = ADC_COMPLETED;

#if defined (ADC_USES_DMA)
                /* Increase current result buffer ptr */
                Dma_ConfigureDestinationAddress((uint32_t)adcGroup->status->currResultBufPtr, adcGroup->dmaResultChannel);
#endif

                hwPtr->IMR.B.MSKECH = 1;
            }
            else
            {
                /* All sample completed. */
                /* @req SWS_Adc_00325 */
                adcGroup->status->groupStatus = ADC_STREAM_COMPLETED;

                /* Stop sampling */
                hwPtr->MCR.B.NSTART=0;
            }
        }
        else if(ADC_STREAM_BUFFER_CIRCULAR == adcGroup->streamBufferMode)
        {
            adcGroup->status->currResultBufPtr++;
            /* Check for buffer wrapping */
            if( adcGroup->status->currResultBufPtr >= &(adcGroup->status->resultBufferPtr[adcGroup->streamNumSamples]) ){/*lint !e946 Both pointers pointing to same memory object*/
                adcGroup->status->currResultBufPtr = adcGroup->status->resultBufferPtr;
            }

            adcGroup->status->currSampleCount++;
            if(adcGroup->status->currSampleCount < adcGroup->streamNumSamples)
            {
                /* @req SWS_Adc_00224 */
                adcGroup->status->groupStatus = ADC_COMPLETED;
            }
            else{
                adcGroup->status->currSampleCount = adcGroup->streamNumSamples;
                /* All samples completed */
                /* @req SWS_Adc_00325 */
                adcGroup->status->groupStatus = ADC_STREAM_COMPLETED;
            }

#if defined (ADC_USES_DMA)
            /* Increase current result buffer ptr */
            Dma_ConfigureDestinationAddress((uint32_t)adcGroup->status->currResultBufPtr, adcGroup->dmaResultChannel);
#endif
            hwPtr->IMR.B.MSKECH = 1;            
        }
        else
        {
            //nothing to do.
        }
    }
    /* Call notification if enabled. */
    /* @req SWS_Adc_00060 */
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* @req SWS_Adc_00083 */
    /* @req SWS_Adc_00080 */
    if ( (adcGroup->status->notifictionEnable>0) && (adcGroup->groupCallback != NULL) )
    {
        /* @req SWS_Adc_00082 */
        adcGroup->groupCallback();
    }
#endif
}

void Group0ConversionComplete (uint32 unit)
{
    /*lint -e{9033} -e{923} Addressing memory mapped register so cast from integer to pointer ok */
    volatile struct ADC_tag *hwPtr = GET_HW_CONTROLLER(unit);
    const Adc_GroupDefType *adcGroup = Adc_CurrentConvGroupPtr[GetControllerIndexFromHwUnitId(unit)];

    /* Clear ECH Flag and disable interrupt */
    /* @req SWS_Adc_00078 */
    hwPtr->ISR_STATUS.B.ECH = 1;
    hwPtr->IMR.B.MSKECH = 0;

    if(adcGroup != NULL)
    {
#if !defined (ADC_USES_DMA)
        /* Copy to result buffer */
        for(Adc_ChannelType channel=0; channel < adcGroup->numberOfChannels; channel++)
        {
            /* To get the layout of the buffer right, first all samples from one channel,
            than all samples for the next etc.*/
            Adc_ValueGroupType *resultBufPtr = &adcGroup->status->currResultBufPtr[channel*(uint32)adcGroup->streamNumSamples];
#if defined(CFG_MPC5606S) || defined(CFG_MPC5645S)
            uint32 chDataRegIndex = adcGroup->channelList[channel];
#else
            uint32 chDataRegIndex = adcGroup->channelList[channel];
#endif
            *resultBufPtr = hwPtr->CDR[chDataRegIndex].B.CDATA; /*lint !e632 */
        }
#endif
        GroupConversionComplete(adcGroup, hwPtr);
    }
}

#ifdef ADC_HWUNIT_ADC_CTRL_0_ENABLED
ISR(Group0ConversionComplete_ADC0){
    Group0ConversionComplete(ADC_CTRL_0);
}
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_1_ENABLED
ISR(Group0ConversionComplete_ADC1){
    Group0ConversionComplete(ADC_CTRL_1);
}
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_2_ENABLED
ISR(Group0ConversionComplete_ADC2){
    Group0ConversionComplete(ADC_CTRL_2);
}
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_3_ENABLED
ISR(Group0ConversionComplete_ADC3){
    Group0ConversionComplete(ADC_CTRL_3);
}
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_4_ENABLED
ISR(Group0ConversionComplete_ADC4){
    Group0ConversionComplete(ADC_CTRL_4);
}
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_5_ENABLED
ISR(Group0ConversionComplete_ADC5){
    Group0ConversionComplete(ADC_CTRL_5);
}
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_6_ENABLED
ISR(Group0ConversionComplete_ADC6){
    Group0ConversionComplete(ADC_CTRL_6);
}
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_7_ENABLED
ISR(Group0ConversionComplete_ADC7){
    Group0ConversionComplete(ADC_CTRL_7);
}
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_8_ENABLED
ISR(Group0ConversionComplete_ADC8){
    Group0ConversionComplete(ADC_CTRL_8);
}
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_9_ENABLED
ISR(Group0ConversionComplete_ADC9){
    Group0ConversionComplete(ADC_CTRL_9);
}
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_10_ENABLED
ISR(Group0ConversionComplete_ADC10){
    Group0ConversionComplete(ADC_CTRL_10);
}
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_B_ENABLED
ISR(Group0ConversionComplete_ADCB){
    Group0ConversionComplete(ADC_CTRL_B);
}
#endif

static void  ConfigureADC (const Adc_ConfigType *AdcConfigPtr)
{
    /* NULL pointer check */
    /*lint -e{904} ARGUMENT_CHECK */
    if ( (AdcConfigPtr == NULL) || (AdcConfigPtr->hwConfigPtr == NULL) ){
        return;
    }

  /*lint -e{9033} -e{923} Addressing memory mapped register so cast from integer to pointer ok */
  volatile struct ADC_tag *hwPtr = GET_HW_CONTROLLER(AdcConfigPtr->hwConfigPtr->hwUnitId);

  /* Set ADC CLOCK */
#if !defined(CFG_MPC5777M)
  hwPtr->MCR.B.ADCLKSEL = AdcConfigPtr->hwConfigPtr->adcPrescale; /*lint !e632 vuint32_t = Adc_PrescaleType = uint32*/
#endif
#if !defined(CFG_MPC5744P) && !defined(CFG_MPC5643L) && !defined(CFG_SPC56XL70)
#if defined(CFG_MPC5777M)
  if((uint32)hwPtr==(uint32)&SARADC_B){ // DSDR only for ADC_B
      hwPtr->DSDR.B.DSD = 254;
  }
#endif
#endif
  /* Power on ADC */
  hwPtr->MCR.B.PWDN = 0;

#if defined(ADC_USES_DMA)
  /* Enable DMA. */
  hwPtr->DMAE.B.DMAEN = 1;
#endif
}

static void ConfigureADCInterrupts (void)
{
#ifdef ADC_HWUNIT_ADC_CTRL_0_ENABLED
    ISR_INSTALL_ISR2(  "Adc_Grp", Group0ConversionComplete_ADC0, ADC0_EOC_INT,     2, 0 ); /*lint !e717 !e641 We want the do ... while(FALSE) */
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_1_ENABLED
    ISR_INSTALL_ISR2(  "Adc_Grp", Group0ConversionComplete_ADC1, ADC1_EOC_INT,     2, 0 );/*lint !e717 !e641 We want the do ... while(FALSE) */
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_2_ENABLED
    ISR_INSTALL_ISR2(  "Adc_Grp", Group0ConversionComplete_ADC2, ADC2_EOC_INT,     2, 0 );
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_3_ENABLED
    ISR_INSTALL_ISR2(  "Adc_Grp", Group0ConversionComplete_ADC3, ADC3_EOC_INT,     2, 0 );
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_4_ENABLED
    ISR_INSTALL_ISR2(  "Adc_Grp", Group0ConversionComplete_ADC4, ADC4_EOC_INT,     2, 0 );
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_5_ENABLED
    ISR_INSTALL_ISR2(  "Adc_Grp", Group0ConversionComplete_ADC5, ADC5_EOC_INT,     2, 0 );
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_6_ENABLED
    ISR_INSTALL_ISR2(  "Adc_Grp", Group0ConversionComplete_ADC6, ADC6_EOC_INT,     2, 0 );
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_7_ENABLED
    ISR_INSTALL_ISR2(  "Adc_Grp", Group0ConversionComplete_ADC7, ADC7_EOC_INT,     2, 0 );
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_8_ENABLED
    ISR_INSTALL_ISR2(  "Adc_Grp", Group0ConversionComplete_ADC8, ADC8_EOC_INT,     2, 0 );
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_9_ENABLED
    ISR_INSTALL_ISR2(  "Adc_Grp", Group0ConversionComplete_ADC9, ADC9_EOC_INT,     2, 0 );
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_10_ENABLED
    ISR_INSTALL_ISR2(  "Adc_Grp", Group0ConversionComplete_ADC10, ADC10_EOC_INT,     2, 0 );
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_11_ENABLED
    ISR_INSTALL_ISR2(  "Adc_Grp", Group0ConversionComplete_ADC11, ADC11_EOC_INT,     2, 0 );
#endif
#ifdef ADC_HWUNIT_ADC_CTRL_B_ENABLED
    ISR_INSTALL_ISR2(  "Adc_Grp", Group0ConversionComplete_ADCB, ADCB_EOC_INT,     2, 0 );
#endif
}

/* @req SWS_Adc_00259 */
/* @req SWS_Adc_00260 */
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/**
 * Configures the conversion time using the configuration parameters supplied.
 *
 * @param hwPtr Pointer to ADC hardware struct
 * @param convTimePtr Pointer to configuration struct for the Conversion Time.
 */
static void setConversionTime(volatile struct ADC_tag *hwPtr, const Adc_Channel_Phase_DurationType *convTimePtr)
{
/*lint -save -e632 Register files from Freescale */
#if defined(CFG_MPC5643L) || defined(CFG_SPC56XL70)
    hwPtr->CTR0.B.INPLATCH = convTimePtr->INPLATCH;
    hwPtr->CTR0.B.INPCMP = convTimePtr->INPCMP;
    hwPtr->CTR0.B.INSAMP = convTimePtr->INPSAMP;
    hwPtr->CTR1.B.INSAMP = convTimePtr->INPSAMP;
#elif defined(CFG_MPC5606S) || defined(CFG_MPC5645S)
    hwPtr->CTR[1].B.INPLATCH = convTimePtr->INPLATCH; /*lint !e632 vuint32_t = Adc_LatchTimeType = uint32 */
    hwPtr->CTR[1].B.INPCMP = convTimePtr->INPCMP; /*lint !e632 vuint32_t = Adc_CmpTimeType = uint32 */
    hwPtr->CTR[1].B.INPSAMP = convTimePtr->INPSAMP; /*lint !e632 vuint32_t = Adc_SampTimeType = uint32 */
#elif defined(CFG_MPC5744P)
    hwPtr->CTR[0].B.INPSAMP = convTimePtr->INPSAMP;
    hwPtr->CTR[1].B.INPSAMP = convTimePtr->INPSAMP;
#elif defined(CFG_MPC5777M)
    hwPtr->CTR[0].B.INPSAMP = convTimePtr->INPSAMP;
    hwPtr->CTR[1].B.INPSAMP = convTimePtr->INPSAMP;
    hwPtr->CTR[2].B.INPSAMP = convTimePtr->INPSAMP;
    hwPtr->CTR[3].B.INPSAMP = convTimePtr->INPSAMP;
#elif defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
    hwPtr->CTR0.B.INPSAMP = convTimePtr->INPSAMP;
    hwPtr->CTR1.B.INPSAMP = convTimePtr->INPSAMP;
    hwPtr->CTR2.B.INPSAMP = convTimePtr->INPSAMP;
#elif defined(CFG_SPC560B54) || defined(CFG_MPC5606B)
    /*ADC0 has to three CTR registers and ADC1 has two CTR registers for SPC560B54  */
    hwPtr->CTR[0].B.INPLATCH = convTimePtr->INPLATCH;
    hwPtr->CTR[0].B.INPCMP = convTimePtr->INPCMP;
    hwPtr->CTR[0].B.INPSAMP = convTimePtr->INPSAMP;
    hwPtr->CTR[1].B.INPLATCH = convTimePtr->INPLATCH;
    hwPtr->CTR[1].B.INPCMP = convTimePtr->INPCMP;
    hwPtr->CTR[1].B.INPSAMP = convTimePtr->INPSAMP;
    if(hwPtr == (volatile struct ADC_tag *)ADC_BASE_ADDRESS){
        hwPtr->CTR[2].B.INPLATCH = convTimePtr->INPLATCH;
        hwPtr->CTR[2].B.INPCMP = convTimePtr->INPCMP;
        hwPtr->CTR[2].B.INPSAMP = convTimePtr->INPSAMP;
    }
#else
    hwPtr->CTR[0].B.INPLATCH = convTimePtr->INPLATCH;
    hwPtr->CTR[0].B.INPCMP = convTimePtr->INPCMP;
    hwPtr->CTR[0].B.INPSAMP = convTimePtr->INPSAMP;
    hwPtr->CTR[1].B.INPLATCH = convTimePtr->INPLATCH;
    hwPtr->CTR[1].B.INPCMP = convTimePtr->INPCMP;
    hwPtr->CTR[1].B.INPSAMP = convTimePtr->INPSAMP;
    hwPtr->CTR[2].B.INPLATCH = convTimePtr->INPLATCH;
    hwPtr->CTR[2].B.INPCMP = convTimePtr->INPCMP;
    hwPtr->CTR[2].B.INPSAMP = convTimePtr->INPSAMP;
#endif
    /*lint -restore */
}

/**
 * Enables ADC conversion and interrupts for the channels in the bitmask.
 *
 * @param hwPtr Pointer to ADC hardware struct
 * @param groupChannelIdMaskPtr Pointer to bitmask for channels
 */
static void enableNormalConversionAndIntrpt(volatile struct ADC_tag *hwPtr, uint32 const *groupChannelIdMaskPtr)
{
#if defined(CFG_MPC5643L) || defined(CFG_SPC56XL70)
    /* Enable Normal conversion */
    hwPtr->NCMR0.R = groupChannelIdMaskPtr[0];

    /* Enable Channel Interrupt */
    hwPtr->CIMR0.R = groupChannelIdMaskPtr[0];
#elif defined(CFG_MPC5606S) || defined(CFG_MPC5645S)
    /* Enable Normal conversion */
    hwPtr->NCMR[1].R = groupChannelIdMaskPtr[1];

    /* Enable Channel Interrupt */
    hwPtr->CIMR[1].R = groupChannelIdMaskPtr[1];
#elif defined(CFG_MPC5744P)
    /* Enable Normal conversion */
    hwPtr->NCMR[0].R = groupChannelIdMaskPtr[0];

    /* Enable Channel Interrupt */
    hwPtr->CIMR[0].R = groupChannelIdMaskPtr[0];
#elif defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
    /* Enable Normal conversion */
    hwPtr->NCMR0.R = groupChannelIdMaskPtr[0];
    hwPtr->NCMR1.R = groupChannelIdMaskPtr[1];
    hwPtr->NCMR2.R = groupChannelIdMaskPtr[2];

    /* Enable Channel Interrupt */
    hwPtr->CIMR0.R = groupChannelIdMaskPtr[0];
    hwPtr->CIMR1.R = groupChannelIdMaskPtr[1];
    hwPtr->CIMR2.R = groupChannelIdMaskPtr[2];

#elif defined(CFG_SPC560B54) || defined(CFG_MPC5606B)
    /*ADC0 has three NCMR and CIMR registers*/
    /* Enable Normal conversion */
    hwPtr->NCMR[0].R = groupChannelIdMaskPtr[0];
    hwPtr->NCMR[1].R = groupChannelIdMaskPtr[1];

    /* Enable Channel Interrupt */
    hwPtr->CIMR[0].R = groupChannelIdMaskPtr[0];
    hwPtr->CIMR[1].R = groupChannelIdMaskPtr[1];

    if(hwPtr == (volatile struct ADC_tag *)ADC_BASE_ADDRESS){
        hwPtr->NCMR[2].R = groupChannelIdMaskPtr[2];
        hwPtr->CIMR[2].R = groupChannelIdMaskPtr[2];
    }
#elif defined(CFG_MPC5777M)
    if((uint32)hwPtr==(uint32)&SARADC_B){
        /* Enable Normal conversion */
        hwPtr->NCMR[0].R = groupChannelIdMaskPtr[0];
        hwPtr->NCMR[1].R = groupChannelIdMaskPtr[1];
        hwPtr->NCMR[2].R = groupChannelIdMaskPtr[2];

        /* Enable Channel Interrupt */
        hwPtr->CIMR[0].R = groupChannelIdMaskPtr[0];
        hwPtr->CIMR[1].R = groupChannelIdMaskPtr[1];
        hwPtr->CIMR[2].R = groupChannelIdMaskPtr[2];
    }
    else if( ((uint32)hwPtr==(uint32)&SARADC_0) ||
              ((uint32)hwPtr==(uint32)&SARADC_1) ||
              ((uint32)hwPtr==(uint32)&SARADC_2) ||
              ((uint32)hwPtr==(uint32)&SARADC_3) ){
        /* Enable Normal conversion */
        hwPtr->NCMR[0].R = groupChannelIdMaskPtr[0];

        /* Enable Channel Interrupt */
        hwPtr->CIMR[0].R = groupChannelIdMaskPtr[0];
    }
    else if( ((uint32)hwPtr==(uint32)&SARADC_4) ||
              ((uint32)hwPtr==(uint32)&SARADC_5) ||
              ((uint32)hwPtr==(uint32)&SARADC_6) ||
              ((uint32)hwPtr==(uint32)&SARADC_7) ){
        /* Enable Normal conversion */
        hwPtr->NCMR[1].R = groupChannelIdMaskPtr[1];

        /* Enable Channel Interrupt */
        hwPtr->CIMR[1].R = groupChannelIdMaskPtr[1];
    }
    else if( ((uint32)hwPtr==(uint32)&SARADC_8) ||
              ((uint32)hwPtr==(uint32)&SARADC_9) ||
              ((uint32)hwPtr==(uint32)&SARADC_10) ){
        /* Enable Normal conversion */
        hwPtr->NCMR[2].R = groupChannelIdMaskPtr[2];

        /* Enable Channel Interrupt */
        hwPtr->CIMR[2].R = groupChannelIdMaskPtr[2];
    }
    else{
    }
#else
    /* Enable Normal conversion */
    hwPtr->NCMR[0].R = groupChannelIdMaskPtr[0];
    hwPtr->NCMR[1].R = groupChannelIdMaskPtr[1];
    hwPtr->NCMR[2].R = groupChannelIdMaskPtr[2];

    /* Enable Channel Interrupt */
    hwPtr->CIMR[0].R = groupChannelIdMaskPtr[0];
    hwPtr->CIMR[1].R = groupChannelIdMaskPtr[1];
    hwPtr->CIMR[2].R = groupChannelIdMaskPtr[2];
#endif
}

#if defined(ADC_USES_DMA)
/**
 * Enables DMA
 *
 * @param hwPtr Pointer to ADC hardware struct.
 * @param groupChannelIdMaskPtr Pointer to bitmask for channels
 */
static void enableDMA(volatile struct ADC_tag *hwPtr, uint32 *groupChannelIdMaskPtr)
{
#if defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
    hwPtr->DMAE.R = 0x01;
    /* Enable DMA Transfer */
    hwPtr->DMAR0.R = groupChannelIdMask;
    Dma_StartChannel(DMA_ADC_GROUP0_RESULT_CHANNEL);        /* Enable EDMA channel for ADC */
#elif defined(CFG_MPC5606S)
    hwPtr->DMAE.R = 0x01;
    /* Enable DMA Transfer */
    hwPtr->DMAR[1].R = groupChannelIdMask;
    Dma_StartChannel(DMA_ADC_GROUP0_RESULT_CHANNEL);        /* Enable EDMA channel for ADC */
#elif defined(CFG_MPC5744P) || defined(CFG_MPC5777M)
    hwPtr->DMAE.R = 0x01;
    /* Enable DMA Transfer */
    hwPtr->DMAR[1].R = groupChannelIdMask;
    Dma_StartChannel(DMA_ADC_GROUP0_RESULT_CHANNEL);        /* Enable EDMA channel for ADC */
#endif
}
#endif

void Adc_StartGroupConversion (Adc_GroupType group)
{
    const Adc_ConfigType *AdcConfigPtr = GetControllerConfigPtrFromGroupId(group);

    /* Run development error check. */
    if (E_OK == Adc_CheckStartGroupConversion (adcState, AdcConfigPtr, group))
    {
        /*lint -e{9033} -e{923} Addressing memory mapped register so cast from integer to pointer ok */
        volatile struct ADC_tag *hwPtr = GET_HW_CONTROLLER(AdcConfigPtr->hwConfigPtr->hwUnitId);

        const Adc_GroupDefType *groupPtr = &AdcConfigPtr->groupConfigPtr[group%ADC_NOF_GROUP_PER_CONTROLLER];
        Adc_CurrentConvGroupPtr[GetControllerIndexFromHwUnitId(AdcConfigPtr->hwConfigPtr->hwUnitId)] = groupPtr;

        /* Disable trigger normal conversions for ADC0 */
        hwPtr->MCR.B.NSTART = 0;

        /* Set group state to BUSY. */
        groupPtr->status->groupStatus = ADC_BUSY;

        groupPtr->status->currSampleCount = 0;
        /* @req SWS_Adc_00431 */
        groupPtr->status->currResultBufPtr = groupPtr->status->resultBufferPtr; /* Set current result buffer */

#if defined(ADC_USES_DMA)
        Dma_ConfigureChannel ((Dma_TcdType *)groupPtr->groupDMAResults, groupPtr->dmaResultChannel);
        Dma_ConfigureDestinationAddress ((uint32_t)groupPtr->status->currResultBufPtr, groupPtr->dmaResultChannel);
#endif

            /* Set conversion mode. */
        hwPtr->MCR.B.MODE = groupPtr->conversionMode; /*lint !e641 !e632 Should be enum acording to Autosar */

        /* Enable Overwrite*/
        hwPtr->MCR.B.OWREN = 1;

        /* Set Conversion Time. */
        setConversionTime(hwPtr, &groupPtr->adcChannelConvTime);

        uint32 groupChannelIdMask[3] = {0,0,0};
        for(Adc_ChannelType i =0; i < groupPtr->numberOfChannels; i++)
        {
#if defined(CFG_MPC5668) || defined(CFG_MPC5777M)
            if(groupPtr->channelList[i] <= 31){
#else
            if(groupPtr->channelList[i] <= 15){
#endif
                groupChannelIdMask[0] |= (1UL << groupPtr->channelList[i]); /*lint !e632 uint32 = Adc_ChannelType = uint32 */
#if defined(CFG_MPC5606B) || defined(CFG_SPC560B54)
            }else if((groupPtr->channelList[i] >= 32) && (groupPtr->channelList[i] <=59)){
#elif defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
            }else if((groupPtr->channelList[i] >= 32) && (groupPtr->channelList[i] <=63)){ /* ADC_0 has channels in the range 32 to 63 (standard channels) */
#else
            }else if((groupPtr->channelList[i] >= 32) && (groupPtr->channelList[i] <=47)){
#endif
                groupChannelIdMask[1] |= (1UL << (groupPtr->channelList[i] - 32UL)); /*lint !e632 uint32 = Adc_ChannelType = uint32 */
            }else if((groupPtr->channelList[i] >= 64) && (groupPtr->channelList[i] <=95)){
                groupChannelIdMask[2] |= (1UL << (groupPtr->channelList[i] - 64UL)); /*lint !e632 uint32 = Adc_ChannelType = uint32 */
            }
            else{
                /* MISRA */
            }
        }

#if defined(ADC_USES_DMA)
        enableDMA(hwPtr, &groupChannelIdMask);
#endif
        /* Enable Normal conversion and channel interrupt */
        enableNormalConversionAndIntrpt(hwPtr, groupChannelIdMask);

        /* Clear interrupts */
        hwPtr->ISR_STATUS.B.ECH = 1;
        /* Enable ECH interrupt */
        hwPtr->IMR.B.MSKECH = 1;

        /* @req SWS_Adc_00061 */
        /* Trigger normal conversions for ADC0 */
        hwPtr->MCR.B.NSTART = 1;
    }
    else
    {
        /* Error have been set within Adc_CheckStartGroupConversion(). */
    }
    /* @req SWS_Adc_00156 */
}

void Adc_StopGroupConversion (Adc_GroupType group)
{
  const Adc_ConfigType *AdcConfigPtr = GetControllerConfigPtrFromGroupId(group);

  if (E_OK == Adc_CheckStopGroupConversion (adcState, AdcConfigPtr, group))
  {
    /*lint -e{9033} -e{923} Addressing memory mapped register so cast from integer to pointer ok */
    volatile struct ADC_tag *hwPtr = GET_HW_CONTROLLER(AdcConfigPtr->hwConfigPtr->hwUnitId);

    /* Disable trigger normal conversions for ADC0 */
    /*@req SWS_Adc_00385 */
    /*@req SWS_Adc_00386 */
    hwPtr->MCR.B.NSTART = 0;
    hwPtr->MCR.B.ABORTCHAIN = 1;
    hwPtr->MCR.B.ABORT = 1;
    /*lint -e{9036} HARDWARE_ACCESS */
    while(hwPtr->MSR.B.NSTART) {
        /* Make sure that abort really hits. Mpc5668 have problem here */
        hwPtr->MCR.B.NSTART = 0;
        hwPtr->MCR.B.ABORTCHAIN = 1;
        hwPtr->MCR.B.ABORT = 1;
    };

    /* Set group state to IDLE. */
    /* @req SWS_Adc_00360 */
    AdcConfigPtr->groupConfigPtr[group%ADC_NOF_GROUP_PER_CONTROLLER].status->groupStatus = ADC_IDLE;

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* Disable group notification if enabled. */
    if(1 == AdcConfigPtr->groupConfigPtr[group%ADC_NOF_GROUP_PER_CONTROLLER].status->notifictionEnable){
        /* @req SWS_Adc_00155 */
        Adc_DisableGroupNotification (group);
    }
#endif
  }
  else
  {
    /* Error have been set within Adc_CheckStartGroupConversion(). */
  }
}
#endif  /* endof #if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */


/* @req SWS_Adc_00100 */
/* @req SWS_Adc_00101 */
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
void Adc_EnableGroupNotification (Adc_GroupType group)
{
    /* @req SWS_Adc_00057 */
    Adc_EnableInternalGroupNotification(adcState, GetControllerConfigPtrFromGroupId(group), group);
}

void Adc_DisableGroupNotification (Adc_GroupType group)
{
    /* @req SWS_Adc_00058 */
    Adc_InternalDisableGroupNotification(adcState, GetControllerConfigPtrFromGroupId(group), group);
}
#endif

Adc_StatusType Adc_GetGroupStatus (Adc_GroupType group)
{
    return Adc_InternalGetGroupStatus(adcState, GetControllerConfigPtrFromGroupId(group), group);
}

#if (STD_ON == ADC_VERSION_INFO_API)
void Adc_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    Adc_InternalGetVersionInfo(versioninfo);
}
#endif
