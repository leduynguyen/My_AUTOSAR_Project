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

/** @tagSettings DEFAULT_ARCHITECTURE=TMS570|RH850F1H|JACINTO5 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#ifndef ADC_INTERNAL2_H_
#define ADC_INTERNAL2_H_


#define GET_CONFIG_PTR(ch)			(&((*Adc_Global.config)[ch]))

typedef enum
{
  ADC_STATE_UNINIT,
  ADC_STATE_INIT,
}Adc_StateType;

typedef enum {
    ADC_STATE_STOPPED = 0,
    ADC_STATE_RUNNING,
    ADC_STATE_EXPIRED,
    ADC_STATE_INITIALIZED
} Adc_ChannelStateType;

typedef struct {
    /* Our config */
    const Adc_ConfigType (*config)[ADC_ARC_CTRL_CONFIG_CNT];

#if ( ADC_WAKEUP_FUNCTIONALITY_API == STD_ON )
    uint8 wakeupEnabled;
#endif
} Adc_GlobalType;

/*lint -esym(9003,Adc_Global) */
extern Adc_GlobalType Adc_Global;

typedef uint8 Adc_Hw_ChannelType;
typedef uint8 Adc_Hw_UnitType;

void Adc_Hw_Init(const Adc_ConfigType* ConfigPtr);
void Adc_Hw_DeInit(void);
void Adc_Hw_StartGroupConversion (Adc_GroupType group);
void Adc_Hw_StopGroupConversion (Adc_GroupType group);
void Adc_Hw_EnableHardwareTrigger(Adc_GroupType Group);
void Adc_Hw_DisableHardwareTrigger(Adc_GroupType Group);
/**
 * Called "late" from generic ADC
 *
 * @param groupPtr		The group pointer
 * @param enableInt		If interrupts should be re-enabled.
 */
void Adc_Hw_IsrPost( const Adc_GroupDefType * groupPtr, boolean enableInt);

void Adc_Internal_Isr(const Adc_GroupDefType * groupPtr );

#endif /* ADC_INTERNAL2_H_ */
