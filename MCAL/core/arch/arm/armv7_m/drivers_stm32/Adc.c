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

#include "arc_assert.h"
#include <stdlib.h>
//#include "System.h"
#include "Mcu.h"
#include "Adc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "Os.h"
#include "isr.h"
#include "Adc_Internal.h"

/* Conversion result register for ADC1. */
#define ADC1_DR_Address    ((u32)0x4001244C)

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


static Adc_StateType adcState = ADC_STATE_UNINIT;

/* Pointer to configuration structure. */
static const Adc_ConfigType *AdcConfigPtr;


ISR(Adc_Group0ConversionComplete)
{
  Adc_GroupDefType *groupPtr = NULL;

  /* @req SWS_Adc_00078 */
  /* ISR for DMA. Clear interrupt flag.  */
  DMA_ClearFlag(DMA1_FLAG_TC1);

  // Check which group is busy, only one is allowed to be busy at a time in a hw unit
  for (uint8 value = 0; value < ADC_NBR_OF_GROUPS; value++)
  {
      if(AdcConfigPtr->groupConfigPtr[value].status->groupStatus == ADC_BUSY)
      {
          groupPtr = (Adc_GroupDefType *)&AdcConfigPtr->groupConfigPtr[value];
          break;
      }
  }
  if(groupPtr != NULL)
  {
      if(ADC_CONV_MODE_ONESHOT == groupPtr->conversionMode)
      {
          /* @req SWS_Adc_00325 */
          groupPtr->status->groupStatus = ADC_STREAM_COMPLETED;

          /* Call notification if enabled. */
        #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
          if (groupPtr->status->notifictionEnable && groupPtr->groupCallback != NULL)
          {
              groupPtr->groupCallback();
          }
        #endif
      }
      else{
          /* @req SWS_Adc_00325 */
          //Only single access supported so far for continous
          groupPtr->status->groupStatus = ADC_STREAM_COMPLETED;

          /* Call notification if enabled. */
        #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
          if (groupPtr->status->notifictionEnable && groupPtr->groupCallback != NULL)
          {
              groupPtr->groupCallback();
          }
        #endif
      }
  }
}

#if (ADC_DEINIT_API == STD_ON)
void Adc_DeInit (void)
{
    if (E_OK == Adc_CheckDeInit(adcState, AdcConfigPtr))
    {
        /* @req SWS_Adc_00110 */
        /* @req SWS_Adc_00111 */
      DMA_DeInit(DMA1_Channel1);
      ADC_DeInit(ADC1);

      adcState = ADC_STATE_UNINIT;
    }
}
#endif


void Adc_Init (const Adc_ConfigType *ConfigPtr)
{
  uint16 group;

  ADC_InitTypeDef ADC_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;

  ADC_TempSensorVrefintCmd(ENABLE);
  /* @req SWS_Adc_00342 */
  if (E_OK == Adc_CheckInit(adcState, ConfigPtr))
  {
    /* First of all, store the location of the configuration data. */
    AdcConfigPtr = ConfigPtr;

    /* DMA1 channel1 configuration ---------------------------------------------*/
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ConfigPtr->groupConfigPtr->resultBuffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = (uint32_t)ConfigPtr->groupConfigPtr->numberOfChannels;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

      // Connect interrupt to correct isr
    ISR_INSTALL_ISR2( "DMA1", Adc_Group0ConversionComplete, DMA1_Channel1_IRQn, 6, 0 );

    /* Enable DMA1 channel1 */
    DMA_Cmd(DMA1_Channel1, ENABLE);

    /* Enable the DMA1 Channel1 Transfer complete interrupt */
    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);

    /* ADC1 configuration ------------------------------------------------------*/
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = (uint32_t)ConfigPtr->groupConfigPtr->numberOfChannels;
    ADC_Init(ADC1, &ADC_InitStructure);

    for(group = 0; group < ConfigPtr->nbrOfGroups; group++)
    {
      /* @req  SWS_Adc_00307 */
      ConfigPtr->groupConfigPtr[group].status->groupStatus = ADC_IDLE;
    }

    /* Enable ADC1 DMA */
    ADC_DMACmd(ADC1, ENABLE);

    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);

    /* Enable ADC1 reset calibaration register */
    ADC_ResetCalibration(ADC1);
    /* Check the end of ADC1 reset calibration register */
    while(ADC_GetResetCalibrationStatus(ADC1)) ;

    /* Start ADC1 calibaration */
    ADC_StartCalibration(ADC1);

    /* Check the end of ADC1 calibration */
    while(ADC_GetCalibrationStatus(ADC1)) ;

    /* Move on to INIT state. */
    adcState = ADC_STATE_INIT;
  }
}

Std_ReturnType Adc_SetupResultBuffer (Adc_GroupType group, Adc_ValueGroupType *bufferPtr)
{
  Std_ReturnType returnValue;

  /* Check for development errors. */
  if (E_OK == Adc_CheckSetupResultBuffer (adcState, AdcConfigPtr, group, bufferPtr))
  {

      /* @req SWS_Adc_00420 */
    AdcConfigPtr->groupConfigPtr[group].status->resultBufferPtr = bufferPtr;
    DMA_Cmd(DMA1_Channel1, DISABLE);
    DMA1_Channel1->CMAR = (u32)AdcConfigPtr->groupConfigPtr[group].status->resultBufferPtr;
    DMA1_Channel1->CNDTR = (uint32)AdcConfigPtr->groupConfigPtr[group].numberOfChannels;
    DMA_Cmd(DMA1_Channel1, ENABLE);
    returnValue = E_OK;
  }
  else
  {
    /* An error have been raised from Adc_CheckSetupResultBuffer(). */
    returnValue = E_NOT_OK;
  }

  return (returnValue);
}

#if (ADC_READ_GROUP_API == STD_ON)
Std_ReturnType Adc_ReadGroup (Adc_GroupType group, Adc_ValueGroupType *dataBufferPtr)
{
  Std_ReturnType returnValue;
  uint8 channel;

  if ((E_OK == Adc_CheckReadGroup (adcState, AdcConfigPtr, group)) && (dataBufferPtr != NULL))
  {
    if ((ADC_CONV_MODE_CONTINUOUS == AdcConfigPtr->groupConfigPtr[group].conversionMode) &&
         ((ADC_STREAM_COMPLETED    == AdcConfigPtr->groupConfigPtr[group].status->groupStatus) ||
          (ADC_COMPLETED           == AdcConfigPtr->groupConfigPtr[group].status->groupStatus)))
    {
        /** @req SWS_Adc_00331. */
        /** @req SWS_Adc_00329. */
      AdcConfigPtr->groupConfigPtr[group].status->groupStatus = ADC_BUSY;
      returnValue = E_OK;

      /* Restart continous again after read */
      ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    }
    else if ((ADC_CONV_MODE_ONESHOT == AdcConfigPtr->groupConfigPtr[group].conversionMode) &&
             (ADC_STREAM_COMPLETED  == AdcConfigPtr->groupConfigPtr[group].status->groupStatus))
    {
        /** @req SWS_Adc_00330. */
      AdcConfigPtr->groupConfigPtr[group].status->groupStatus = ADC_IDLE;

      returnValue = E_OK;
    }
    else
    {
      /* Keep status. */
      returnValue = E_OK;
    }

    if (E_OK == returnValue)
    {
      /* Copy the result to application buffer. */
      for (channel = 0; channel < (uint8)AdcConfigPtr->groupConfigPtr[group].numberOfChannels; channel++)
      {
          /* @req SWS_Adc_00075 */
          dataBufferPtr[channel] = AdcConfigPtr->groupConfigPtr[group].status->resultBufferPtr[channel];
      }
    }
  }
  else
  {
    /* An error have been raised from Adc_CheckReadGroup(). */
    returnValue = E_NOT_OK;
  }

  return (returnValue);
}
#endif

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
void Adc_StartGroupConversion (Adc_GroupType group)
{
  /* Run development error check. */
  if (E_OK == Adc_CheckStartGroupConversion (adcState, AdcConfigPtr, group))
  {
	  uint8 channel;
	  Adc_ChannelType channelId;

	  /* Configure the channel queue. */
        ADC1->SQR1 = ((uint8)AdcConfigPtr->groupConfigPtr[group].numberOfChannels -1) << 20;
        ADC1->SQR2 = 0;
        ADC1->SQR3 = 0;
      /* Loop through all channels and make the command queue. */
      for (channel = 0; channel < (uint8)AdcConfigPtr->groupConfigPtr[group].numberOfChannels; channel++)
      {
        /* Get physical channel. */
        channelId = AdcConfigPtr->groupConfigPtr[group].channelList[channel];

        /* Configure channel as regular. */
        ADC_RegularChannelConfig(ADC1, (uint8)channelId, channel+1,
        		(uint8)AdcConfigPtr->channelConfigPtr [channel].adcChannelConvTime);


      }

    /* Set conversion mode. No need we run always in single shot and handle continous ourselves */
/*	if (AdcConfigPtr->groupConfigPtr[group].conversionMode == ADC_CONV_MODE_ONESHOT){
        ADC1->CR2 = ADC1->CR2 & ~(1<<1);
    }else{
        ADC1->CR2 = ADC1->CR2 | (1<<1);
    }*/

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    /* Set group state to BUSY. */
    AdcConfigPtr->groupConfigPtr[group].status->groupStatus = ADC_BUSY;
  }
  else
  {
    /* Error have been set within Adc_CheckStartGroupConversion(). */
  }
  /* @req SWS_Adc_00156 */
}

void Adc_StopGroupConversion (Adc_GroupType group)
{
  /* Run development error check. */
  if (E_OK == Adc_CheckStopGroupConversion (adcState, AdcConfigPtr, group))
  {
      /*@req SWS_Adc_00385 */
      /*@req SWS_Adc_00386 */
        ADC_SoftwareStartConvCmd(ADC1, DISABLE);

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
        /* Disable group notification if enabled. */
        if(1 == AdcConfigPtr->groupConfigPtr[group].status->notifictionEnable){
            /* @req SWS_Adc_00155 */
            Adc_DisableGroupNotification (group);
        }
#endif
        /* @req SWS_Adc_00360 */
        AdcConfigPtr->groupConfigPtr[group].status->groupStatus = ADC_IDLE;
  }
  else
  {
    /* Error have been set within Adc_CheckStartGroupConversion(). */
  }
}
#endif

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
void Adc_EnableGroupNotification (Adc_GroupType group)
{
    /* @req SWS_Adc_00057 */
    Adc_EnableInternalGroupNotification(adcState, AdcConfigPtr, group);
}

void Adc_DisableGroupNotification (Adc_GroupType group)
{
    /* @req SWS_Adc_00058 */
    Adc_InternalDisableGroupNotification(adcState, AdcConfigPtr, group);
}
#endif

Adc_StatusType Adc_GetGroupStatus (Adc_GroupType group)
{
    return Adc_InternalGetGroupStatus(adcState, AdcConfigPtr, group);
}

#if (STD_ON == ADC_VERSION_INFO_API)
void Adc_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    Adc_InternalGetVersionInfo(versioninfo);
}
#endif
