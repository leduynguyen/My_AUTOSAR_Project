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
/** @tagSettings DEFAULT_ARCHITECTURE=PPC|ZYNQ|MPC5607B|MPC5645S|STM32|JACINTO5|JACINTO6|MPC5748G */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#include "Adc.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "Adc_Internal.h"

#if !defined(CFG_MPC560X) && !defined(CFG_ZYNQ) && !defined(CFG_RH850) && !defined(CFG_MPC5746C)
#define ADC_NOF_GROUP_PER_CONTROLLER 100
#endif

/** General requirements tagging */
/* @req SWS_Adc_00138  The ADC Driver shall support one or several ADC HW Units*/
/* @req SWS_Adc_00140  Consistency of returned result values*/
/* @req SWS_Adc_00246  Module implementing function, writes the register.*/
/* @req SWS_Adc_00247  PORT should init register if reg is I/O and affetcs several modules*/
/* @req SWS_Adc_00248  MCU shold init register if not I/O but affects several modules*/
/* @req SWS_Adc_00249  One time writable registers that require init directly after reset should be inited by startup code*/
/* @req SWS_Adc_00250  All other registers shall be initialized by the startup code*/
/* @req SWS_Adc_00277  All channels in one group shall belong to the same HW unit */
/* @req SWS_Adc_00280  Only one ADC Channel group per ADC HW Unit should be converted at a time.*/
/* @req SWS_Adc_00318  In single access mode the result buffer shall have as many elements as channels in the group.*/
/* @req SWS_Adc_00319  In streaming access mode the result buffer should have m*n elements. m=samples/channel, n=channels in group.*/
/* @req SWS_Adc_00320  All buffer elements should be of equal size (in numbe rof bits) tailored to the largest channel */
/* @req SWS_Adc_00380 Support One-shot conversions */
/* @req SWS_Adc_00381 Support Continuous Conversion for groups with SW trigger  */
/* @req SWS_Adc_00090  Grouping */
/* @req SWS_Adc_00091  All groups should contain at least one channel*/
/* @req SWS_Adc_00092  A channel can be in more than one group */

/* ----------------------------[private functions]---------------------------*/
#if defined(CFG_MPC5606B) || defined(CFG_MPC5645S) || defined(CFG_SPC560B54)
/**
 * Checks the config struct for NULL pointers.
 *
 * These elements are checked:
 * 		-The pointer itself and all subsequent pointers: ConfigPtr[i] where i is 0 to ADC_ARC_CTRL_CONFIG_CNT.
 *  	-The sub pointer hwConfigPtr
 *  	-The sub pointer  groupConfigPtr and all subsequent sub pointers: groupConfigPtr[i] where i is 0 to nbrOfGroups.
 *  	-The sub pointer to groupConfigPtr: status
 *  	-The sub pointers to groupConfigPtr: channelList[i] where i is 0 to numberOfChannels.
 *
 *  These are NOT checked:
 *		-The callback function pointer since it is allowed to be null.
 *		-The sub pointer resultBufferPtr since it is allowed to be null at init function call.
 *		-The sub pointer currResultBufPtr since it is allowed to be null at init function call.
 *
 * @param ConfigPtr Pointer to configuration structure.
 * @return E_OK if none of the checked pointers are NULL pointers.
 */
static Std_ReturnType checkConfigStruct(const Adc_ConfigType *ConfigPtr){
    Std_ReturnType retVal = E_OK;
    /*lint  --e{774} The expression on the left might evaluate to true. */
    for (uint32 configId = 0; (retVal == E_OK) && (configId < ADC_ARC_CTRL_CONFIG_CNT); configId++)
    {
        if ( (&ConfigPtr[configId] == (Adc_ConfigType *)NULL) ||
                (ConfigPtr[configId].hwConfigPtr == NULL)
        ){
            retVal = E_NOT_OK;
        }
        for (Adc_GroupType group = 0; (retVal == E_OK) && (group < ConfigPtr[configId].nbrOfGroups); group++){
            if ( (&ConfigPtr[configId].groupConfigPtr[group] == NULL)  ||
                    (&ConfigPtr[configId].groupConfigPtr[group].status == NULL)){ /*lint !e845 Depends on configuration */
                retVal = E_NOT_OK;
            }

            if (&ConfigPtr[configId].groupConfigPtr[group].channelList == NULL ){
                retVal = E_NOT_OK;
            }
        }
    }
    return retVal;
}
#endif
/* ----------------------------[public functions]----------------------------*/
/* Validate functions used for development error check */
#if ( ADC_DEV_ERROR_DETECT == STD_ON )
Std_ReturnType ValidateInit(Adc_StateType adcState, uint8 api)
{
    Std_ReturnType res = E_OK;
    if(!(ADC_STATE_INIT == adcState)) {
        (void)Det_ReportError(ADC_MODULE_ID,0,api,ADC_E_UNINIT );
        res = E_NOT_OK;
    }
    return res;
}
Std_ReturnType ValidateGroup(const Adc_ConfigType *ConfigPtr, Adc_GroupType group, uint8 api)
{
    Std_ReturnType res = E_OK;
    if((NULL == ConfigPtr) || !(((uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER) < (uint32)ConfigPtr->nbrOfGroups))
    {
        (void)Det_ReportError(ADC_MODULE_ID,0,api,ADC_E_PARAM_GROUP );
        res = E_NOT_OK;
    }
    return res;
}
#endif

Adc_StatusType Adc_InternalGetGroupStatus (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group)
{
    Adc_StatusType returnValue;

#if ( ADC_DEV_ERROR_DETECT == STD_ON )
    /* @req SWS_Adc_00301 */
    /* @req SWS_Adc_00225 */
    if( ValidateInit(adcState, ADC_GETGROUPSTATUS_ID) == E_NOT_OK )
    {
        returnValue = ADC_IDLE;
    }
    else if(ValidateGroup(ConfigPtr, group, ADC_GETGROUPSTATUS_ID) == E_NOT_OK)
    {
        returnValue = ADC_IDLE;
    }
    else
    {
        returnValue = ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].status->groupStatus;
    }
#else
  returnValue = ConfigPtr->groupConfigPtr[group%ADC_NOF_GROUP_PER_CONTROLLER].status->groupStatus;
#endif
  /* @req SWS_Adc_00226 */
  return (returnValue);
}

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
void Adc_EnableInternalGroupNotification (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group)
{
    Std_ReturnType res;

#if ( ADC_DEV_ERROR_DETECT == STD_ON )
    /* @req SWS_Adc_00299 */
    /* @req SWS_Adc_00130 */
    if(ValidateInit(adcState, ADC_ENABLEGROUPNOTIFICATION_ID) == E_NOT_OK)
    {
        res = E_NOT_OK;
    }
    else if(ValidateGroup(ConfigPtr, group, ADC_ENABLEGROUPNOTIFICATION_ID) == E_NOT_OK)
    {
        res = E_NOT_OK;
    }
    else if (ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].groupCallback == NULL)
    {
        res = E_NOT_OK;
        /* @req SWS_Adc_00165 */
        (void)Det_ReportError(ADC_MODULE_ID,0,ADC_ENABLEGROUPNOTIFICATION_ID ,ADC_E_NOTIF_CAPABILITY );
    }
    else
    {
        /* Nothing strange. Go on... */
        res = E_OK;
    }
#else
    res = E_OK;
#endif
    if (E_OK == res){
        ConfigPtr->groupConfigPtr[(uint32) group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].status->notifictionEnable = 1;
    }
}

void Adc_InternalDisableGroupNotification (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group)
{
    Std_ReturnType res;

#if ( ADC_DEV_ERROR_DETECT == STD_ON )
    /* @req SWS_Adc_00300 */
    /* @req SWS_Adc_00131 */
    if(ValidateInit(adcState, ADC_DISABLEGROUPNOTIFICATION_ID) == E_NOT_OK)
    {
        res = E_NOT_OK;
    }
    else if(ValidateGroup(ConfigPtr, group, ADC_DISABLEGROUPNOTIFICATION_ID) == E_NOT_OK)
    {
        res = E_NOT_OK;
    }
    else if (ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].groupCallback == NULL)
    {
        res = E_NOT_OK;
        /* @req SWS_Adc_00166 */
        (void)Det_ReportError(ADC_MODULE_ID,0,ADC_DISABLEGROUPNOTIFICATION_ID ,ADC_E_NOTIF_CAPABILITY );
    }
    else
    {
        /* Nothing strange. Go on... */
        res = E_OK;
    }
#else
    res = E_OK;
#endif
    if (E_OK == res){
        ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].status->notifictionEnable = 0;
    }
}
#endif




/* Development error checking functions. */
#if (ADC_READ_GROUP_API == STD_ON)
Std_ReturnType Adc_CheckReadGroup (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group)
{
  Std_ReturnType returnValue = E_OK;

#if ( ADC_DEV_ERROR_DETECT == STD_ON )

  /* @req SWS_Adc_00296 */
  /* @req SWS_Adc_00152 */
  if(ValidateInit(adcState, ADC_READGROUP_ID) == E_NOT_OK)
  {
      returnValue = E_NOT_OK;
  }
  else if(ValidateGroup(ConfigPtr, group, ADC_READGROUP_ID) == E_NOT_OK)
  {
      returnValue = E_NOT_OK;
  }
  else if ((ADC_IDLE == ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].status->groupStatus)
#if !defined(CFG_STM32F1X)
          &&  (ConfigPtr->groupConfigPtr[group % ADC_NOF_GROUP_PER_CONTROLLER].status->currSampleCount == 0)
#endif
           )
  {
    /*  @req SWS_Adc_00388. */
    returnValue = E_NOT_OK;
    (void)Det_ReportError(ADC_MODULE_ID,0,ADC_READGROUP_ID ,ADC_E_IDLE );
  }
  else
  {
    /* Nothing strange. Go on... */
    returnValue = E_OK;
  }
#endif
  return (returnValue);
}
#endif


#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
Std_ReturnType Adc_CheckStartGroupConversion (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group)
{
  Std_ReturnType returnValue = E_OK;

#if ( ADC_DEV_ERROR_DETECT == STD_ON )
  /* @req SWS_Adc_00294 */
  /* @req SWS_Adc_00125 */
  if(ValidateInit(adcState, ADC_STARTGROUPCONVERSION_ID) == E_NOT_OK)
  {
      returnValue = E_NOT_OK;
  }
  else if(ValidateGroup(ConfigPtr, group, ADC_STARTGROUPCONVERSION_ID) == E_NOT_OK)
  {
      returnValue = E_NOT_OK;
  }
  else if ( NULL == ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].status->resultBufferPtr )
  {
      /* ResultBuffer not set */
      /* @req SWS_Adc_00424 */
      (void)Det_ReportError(ADC_MODULE_ID,0,ADC_STARTGROUPCONVERSION_ID, ADC_E_BUFFER_UNINIT );
      returnValue = E_NOT_OK;
  }
  else if (!(ADC_TRIGG_SRC_SW == ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].triggerSrc))
  {
    /* Wrong trig source  */
      /* @req SWS_Adc_00133 */
    (void)Det_ReportError(ADC_MODULE_ID,0,ADC_STARTGROUPCONVERSION_ID, ADC_E_WRONG_TRIGG_SRC);
    returnValue = E_NOT_OK;
  }
  else if (!((ADC_IDLE             == ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].status->groupStatus) ||
             (ADC_STREAM_COMPLETED == ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].status->groupStatus)))
  {
    /* Group status not OK */
    /* @req  SWS_Adc_00346 */
    /* @req  SWS_Adc_00426 */
    (void)Det_ReportError(ADC_MODULE_ID,0,ADC_STARTGROUPCONVERSION_ID, ADC_E_BUSY );

#if defined(CFG_ZYNQ)
    returnValue = E_NOT_OK;
#else
    returnValue = E_OK;
#endif
  }
  else
  {
    returnValue = E_OK;
  }
#endif

  return (returnValue);
}

Std_ReturnType Adc_CheckStopGroupConversion (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group)
{
  Std_ReturnType returnValue = E_OK;

#if ( ADC_DEV_ERROR_DETECT == STD_ON )
  /* @req SWS_Adc_00295 */
  /* @req SWS_Adc_00126 */
  if(ValidateInit(adcState, ADC_STOPGROUPCONVERSION_ID) == E_NOT_OK)
  {
      returnValue = E_NOT_OK;
  }
  else if(ValidateGroup(ConfigPtr, group, ADC_STOPGROUPCONVERSION_ID) == E_NOT_OK)
  {
      returnValue = E_NOT_OK;
  }
  else if (!(ADC_TRIGG_SRC_SW == ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].triggerSrc))
  {
    /* Wrong trig source, SWS_Adc_00164. */
    /* @req:ZYNQ SWS_Adc_00164 */
    (void)Det_ReportError(ADC_MODULE_ID,0,ADC_STOPGROUPCONVERSION_ID, ADC_E_WRONG_TRIGG_SRC);
    returnValue = E_NOT_OK;
  }
  else if (ADC_IDLE == ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].status->groupStatus)
  {
    /* Group status not OK */
      /* @req SWS_Adc_00241 */
    (void)Det_ReportError(ADC_MODULE_ID,0,ADC_STOPGROUPCONVERSION_ID, ADC_E_IDLE );
    returnValue = E_NOT_OK;
  }
  else
  {
    returnValue = E_OK;
  }
#endif

  return (returnValue);
}
#endif

Std_ReturnType Adc_CheckInit (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr)
{
  Std_ReturnType returnValue = E_OK;

#if ( ADC_DEV_ERROR_DETECT == STD_ON )
  if (!(ADC_STATE_UNINIT == adcState))
  {
    /* Oops, already initialised. */
      /* @req SWS_Adc_00107 */
    (void)Det_ReportError(ADC_MODULE_ID,0,ADC_INIT_ID, ADC_E_ALREADY_INITIALIZED );
    returnValue = E_NOT_OK;
  }
#if defined(CFG_ZYNQ)
  /* @req:ZYNQ SWS_Adc_00342 */
  else if (ConfigPtr != NULL)
  {
    /* Wrong config! */
      /* @req:ZYNQ SWS_Adc_00344 */
    (void)Det_ReportError(ADC_MODULE_ID,0,ADC_INIT_ID, ADC_E_PARAM_CONFIG );
    returnValue = E_NOT_OK;
  }
#else
  else if (ConfigPtr == NULL)
  {
    /* Wrong config! */
    (void)Det_ReportError(ADC_MODULE_ID,0,ADC_INIT_ID, ADC_E_PARAM_CONFIG );
    returnValue = E_NOT_OK;
  }
#endif
#if defined(CFG_MPC5606B) || defined(CFG_MPC5645S) || defined(CFG_SPC560B54)
  else if (checkConfigStruct(ConfigPtr) != E_OK){
      (void)Det_ReportError(ADC_MODULE_ID,0,ADC_INIT_ID, ADC_E_PARAM_CONFIG );
      returnValue = E_NOT_OK;
  }
#endif
  else
  {
    /* Looks good!! */
    returnValue = E_OK;
  }
#endif
  return (returnValue);
}

#if (ADC_DEINIT_API == STD_ON)
Std_ReturnType Adc_CheckDeInit (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr)
{
    Std_ReturnType returnValue = E_OK;

#if ( ADC_DEV_ERROR_DETECT == STD_ON )
    /* @req SWS_Adc_00154 */
    if(ValidateInit(adcState, ADC_DEINIT_ID) == E_OK)
    {
        for (uint32 group = 0u; group < (uint32)ConfigPtr->nbrOfGroups; group++)
        {
            /*  Check ADC is IDLE or COMPLETE*/
            if( (ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].status->groupStatus != ADC_IDLE)            &&
                (ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].status->groupStatus != ADC_STREAM_COMPLETED) )
            {
                /* @req SWS_Adc_00112 */
                (void)Det_ReportError(ADC_MODULE_ID,0,ADC_DEINIT_ID, ADC_E_BUSY );
                returnValue = E_NOT_OK;
            }
        }
    }
    else
    {
        returnValue = E_NOT_OK;
    }
#endif
    return (returnValue);
}
#endif

Std_ReturnType Adc_CheckSetupResultBuffer (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group, const Adc_ValueGroupType *bufferPtr)
{
  Std_ReturnType returnValue = E_OK;

#if ( ADC_DEV_ERROR_DETECT == STD_ON )
  /* @req SWS_Adc_00423 */
  /* @req SWS_Adc_00434 */
  if(ValidateInit(adcState, ADC_SETUPRESULTBUFFER_ID) == E_NOT_OK)
  {
    returnValue = E_NOT_OK;
  }
  else if(ValidateGroup(ConfigPtr, group, ADC_SETUPRESULTBUFFER_ID) == E_NOT_OK)
  {
      returnValue = E_NOT_OK;
  }
  /* @req SWS_Adc_00433 */
  else if(ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].status->groupStatus != ADC_IDLE)
  { /** Check ADC is in IDLE */
    (void)Det_ReportError(ADC_MODULE_ID,0,ADC_SETUPRESULTBUFFER_ID, ADC_E_BUSY );
    returnValue = E_NOT_OK;
  }
  /* @req SWS_Adc_00457 */
  else if (bufferPtr == NULL){
    (void)Det_ReportError(ADC_MODULE_ID,0,ADC_SETUPRESULTBUFFER_ID, ADC_E_PARAM_POINTER );
    returnValue = E_NOT_OK;
  }
  else{
      /*MISRA*/
  }
#endif
  return (returnValue);
}

Std_ReturnType Adc_CheckGetStreamLastPointer (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group)
{
  Std_ReturnType returnValue = E_OK;

#if ( ADC_DEV_ERROR_DETECT == STD_ON )
  /* @req SWS_Adc_00218 */
  /* @req SWS_Adc_00302 */
  if(ValidateInit(adcState, ADC_GETSTREAMLASTPOINTER_ID) == E_NOT_OK)
  {
      returnValue = E_NOT_OK;
  }
  else if(ValidateGroup(ConfigPtr, group, ADC_GETSTREAMLASTPOINTER_ID) == E_NOT_OK)
  {
      returnValue = E_NOT_OK;
  }
  else if(ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].status->groupStatus == ADC_IDLE)
  { /** Check ADC is not in IDLE */
      /* @req SWS_Adc_00215 */
    (void)Det_ReportError(ADC_MODULE_ID,0,ADC_GETSTREAMLASTPOINTER_ID, ADC_E_IDLE );
    returnValue = E_NOT_OK;
  }
  else{
      /*MISRA*/
  }
#endif
  if ((E_OK == returnValue) && (ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].status->groupStatus == ADC_BUSY)){
      /** @req SWS_Adc_00216 */
      returnValue = E_NOT_OK;
  }
  return (returnValue);
}


#if (STD_ON == ADC_VERSION_INFO_API)
void Adc_InternalGetVersionInfo(Std_VersionInfoType* versioninfo)
{
  Std_ReturnType isOk = E_OK;

    /* @req SWS_Adc_00458 */
#if ( ADC_DEV_ERROR_DETECT == STD_ON )
  if (versioninfo == NULL)
  {
    (void)Det_ReportError(ADC_MODULE_ID,0,ADC_GETVERSIONINFO_ID, ADC_E_PARAM_POINTER );
    isOk = E_NOT_OK;
  }
#endif

  if (isOk == E_OK)
  {
    // Lint warning 613 ignored. Null pointer will only be checked according to autosar spec if development error detection is on.
    /*lint -save -e613 */
    versioninfo->vendorID           = ADC_VENDOR_ID;
    versioninfo->moduleID           = ADC_MODULE_ID;
    versioninfo->sw_major_version   = ADC_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version   = ADC_SW_MINOR_VERSION;
    versioninfo->sw_patch_version   = ADC_SW_PATCH_VERSION;
    /*lint -restore */
  }
}
#endif
#if (STD_ON == ADC_HW_TRIGGER_API)
Std_ReturnType Adc_CheckEnableHardwareTrigger (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group){
    Std_ReturnType returnValue = E_OK;

#if ( ADC_DEV_ERROR_DETECT == STD_ON )
    /* @req:ZYNQ SWS_Adc_00128 */
    /* @req:ZYNQ SWS_Adc_00297 */

    if(ValidateInit(adcState, ADC_ENABLEHARDWARETRIGGER_ID) == E_NOT_OK)
    {
        returnValue = E_NOT_OK;
    }
    else if(ValidateGroup(ConfigPtr, group, ADC_ENABLEHARDWARETRIGGER_ID) == E_NOT_OK)
    {
        returnValue = E_NOT_OK;
    }
    else if( (ADC_TRIGG_SRC_HW == ConfigPtr->groupConfigPtr[group].triggerSrc)   &&
             (ADC_IDLE != ConfigPtr->groupConfigPtr[group].status->groupStatus)    ){
        /* We only support one hw trigger so 00353 are implicitly full filled. */
        /* @req:ZYNQ SWS_Adc_00349 */
        /* @req:ZYNQ SWS_Adc_00353 */
        (void)Det_ReportError(ADC_MODULE_ID,0,ADC_ENABLEHARDWARETRIGGER_ID, ADC_E_BUSY );
        returnValue = E_NOT_OK;
    }
    else if( ADC_TRIGG_SRC_SW == ConfigPtr->groupConfigPtr[group].triggerSrc ){
        /* @req:ZYNQ SWS_Adc_00136 */
        (void)Det_ReportError(ADC_MODULE_ID,0,ADC_ENABLEHARDWARETRIGGER_ID, ADC_E_WRONG_TRIGG_SRC );
        returnValue = E_NOT_OK;
    }
    else if( (ADC_CONV_MODE_CONTINUOUS == ConfigPtr->groupConfigPtr[group].conversionMode) ){
        /* @req:ZYNQ SWS_Adc_00281 */
        (void)Det_ReportError(ADC_MODULE_ID,0,ADC_ENABLEHARDWARETRIGGER_ID, ADC_E_WRONG_CONV_MODE );
        returnValue = E_NOT_OK;
    }
    else if ( NULL == ConfigPtr->groupConfigPtr[(uint32)group % (uint32)ADC_NOF_GROUP_PER_CONTROLLER].status->resultBufferPtr )
    {
        /* ResultBuffer not set */
        /* @req:ZYNQ SWS_Adc_00425 */
        (void)Det_ReportError(ADC_MODULE_ID,0,ADC_ENABLEHARDWARETRIGGER_ID, ADC_E_BUFFER_UNINIT );
        returnValue = E_NOT_OK;
    }
    else
    {
        ;/*do nothing*/
    }

    for( uint32 index = 0; index < ADC_NBR_OF_GROUPS; index++)
    {
        if( (ADC_TRIGG_SRC_SW == ConfigPtr->groupConfigPtr[index%ADC_NOF_GROUP_PER_CONTROLLER].triggerSrc)  &&
            (ADC_IDLE != ConfigPtr->groupConfigPtr[index%ADC_NOF_GROUP_PER_CONTROLLER].status->groupStatus)   ){
            /* @req:ZYNQ SWS_Adc_00321 */
            (void)Det_ReportError(ADC_MODULE_ID,0,ADC_ENABLEHARDWARETRIGGER_ID, ADC_E_BUSY );
            returnValue = E_NOT_OK;
            break;
        }
    }
#endif
    return (returnValue);
}

Std_ReturnType Adc_CheckDisableHardwareTrigger (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group){
    Std_ReturnType returnValue = E_OK;

#if ( ADC_DEV_ERROR_DETECT == STD_ON )
    /* @req:ZYNQ SWS_Adc_00129 */
    /* @req:ZYNQ SWS_Adc_00298 */

    if( ValidateInit(adcState, ADC_DISABLEHARDWARETRIGGER_ID) == E_NOT_OK)
    {
        returnValue = E_NOT_OK;
    }
    else if(ValidateGroup(ConfigPtr, group, ADC_DISABLEHARDWARETRIGGER_ID) == E_NOT_OK)
    {
        returnValue = E_NOT_OK;
    }
    else if( (ADC_TRIGG_SRC_HW == ConfigPtr->groupConfigPtr[group].triggerSrc)    &&
             (ADC_IDLE == ConfigPtr->groupConfigPtr[group].status->groupStatus)    ){
        /* @req:ZYNQ SWS_Adc_00304 */
        (void)Det_ReportError(ADC_MODULE_ID,0,ADC_DISABLEHARDWARETRIGGER_ID, ADC_E_IDLE );
        returnValue = E_NOT_OK;
    }
    else if( ADC_TRIGG_SRC_SW == ConfigPtr->groupConfigPtr[group].triggerSrc ){
        /* @req:ZYNQ SWS_Adc_00137 */
        (void)Det_ReportError(ADC_MODULE_ID,0,ADC_DISABLEHARDWARETRIGGER_ID, ADC_E_WRONG_TRIGG_SRC );
        returnValue = E_NOT_OK;
    }
    else if( (ADC_CONV_MODE_CONTINUOUS == ConfigPtr->groupConfigPtr[group].conversionMode) ){
        /* @req:ZYNQ SWS_Adc_00282 */
        (void)Det_ReportError(ADC_MODULE_ID,0,ADC_DISABLEHARDWARETRIGGER_ID, ADC_E_WRONG_CONV_MODE );
        returnValue = E_NOT_OK;
    }
    else {
        ;/*do nothing*/
    }
#endif
    return (returnValue);
}
#endif
