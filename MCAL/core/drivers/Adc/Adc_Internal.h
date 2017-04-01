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

/** @tagSettings DEFAULT_ARCHITECTURE=PPC|ZYNQ|MPC5607B|MPC5645S|STM32|MPC5748G */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#ifndef ADC_INTERNAL_H_
#define ADC_INTERNAL_H_

typedef enum
{
  ADC_STATE_UNINIT,
  ADC_STATE_INIT,
}Adc_StateType;

Std_ReturnType ValidateInit(Adc_StateType adcState, uint8 api);
Std_ReturnType ValidateGroup(const Adc_ConfigType *ConfigPtr, Adc_GroupType group,uint8 api);

Adc_StatusType Adc_InternalGetGroupStatus (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group);
void Adc_EnableInternalGroupNotification (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group);
void Adc_InternalDisableGroupNotification (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group);
void Adc_InternalGetVersionInfo(Std_VersionInfoType* versioninfo);

/* Development error checking. */
Std_ReturnType Adc_CheckReadGroup (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group);
Std_ReturnType Adc_CheckStartGroupConversion (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group);
Std_ReturnType Adc_CheckStopGroupConversion (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group);
Std_ReturnType Adc_CheckInit (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr);
#if (ADC_DEINIT_API == STD_ON)
Std_ReturnType Adc_CheckDeInit (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr);
#endif
Std_ReturnType Adc_CheckSetupResultBuffer (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group, const Adc_ValueGroupType *bufferPtr);
Std_ReturnType Adc_CheckGetStreamLastPointer (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group);
#if (STD_ON == ADC_HW_TRIGGER_API)
Std_ReturnType Adc_CheckEnableHardwareTrigger (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group);
Std_ReturnType Adc_CheckDisableHardwareTrigger (Adc_StateType adcState, const Adc_ConfigType *ConfigPtr, Adc_GroupType group);

#endif
#endif /* ADC_INTERNAL_H_ */
