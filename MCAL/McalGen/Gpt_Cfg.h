/*
 * Generator version: 3.0.0
 * AUTOSAR version:   4.1.2
 */

#if !(((GPT_SW_MAJOR_VERSION == 3) && (GPT_SW_MINOR_VERSION == 0)) )
#error Gpt: Configuration file expected BSW module version to be 3.0.*
#endif

#if !(((GPT_AR_RELEASE_MAJOR_VERSION == 4) && (GPT_AR_RELEASE_MINOR_VERSION == 1)) )
#error Gpt: Configuration file expected AUTOSAR version to be 4.1.*
#endif

#ifndef GPT_CFG_H_
#define GPT_CFG_H_

/** HW PIT channels */
#define GPT_CHANNEL_TIM_1	0
#define GPT_CHANNEL_TIM_2	1
#define GPT_CHANNEL_TIM_3	2
#define GPT_CHANNEL_TIM_4	3

#define GPT_CHANNEL_CNT	(GPT_CHANNEL_TIM_4 + 1)

#define GPT_CHANNEL_ILL	31

#define GPT_DEV_ERROR_DETECT				STD_OFF	
#define GPT_REPORT_WAKEUP_SOURCE			STD_OFF
#define GPT_DEINIT_API  					STD_ON
#define GPT_ENABLE_DISABLE_NOTIFICATION_API STD_ON
#define GPT_TIME_REMAINING_API				STD_OFF
#define GPT_TIME_ELAPSED_API                STD_OFF
#define GPT_VERSION_INFO_API				STD_OFF
#define GPT_WAKEUP_FUNCTIONALITY_API		STD_OFF
#define GPT_POSTBUILD_VARIANT 			    STD_OFF


#include "Gpt_ConfigTypes.h"


/* Configuration Set Handles */
#define GptChannelConfigSet (GptConfigData)
#define Gpt_GptChannelConfigSet (GptConfigData)

extern const Gpt_ConfigType GptConfigData[];

#endif /*GPT_CFG_H_*/

