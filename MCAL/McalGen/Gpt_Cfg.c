/*
 * Generator version: 3.0.0
 * AUTOSAR version:   4.1.2
 */

#include "Gpt.h"
#include "Gpt_Cfg.h"
#include <stdlib.h>

extern void gpt_notification1 (void);

const Gpt_ConfigType GptConfigData[] =
{

	{ // GptChannel_1
		.GptChannelId    		 = GPT_CHANNEL_TIM_1,
		.GptChannelMode  		 = GPT_CH_MODE_CONTINUOUS,
		.GptNotification 		 = gpt_notification1,
			
		// Prescaler calculation: Target tick frequency: 1 Hz. Using internal clock frequency of: 2.5E+7 Hz. 
		.GptChannelPrescale 	 = ### Error: Frequency too low ###,
		.GptNotificationPriority = 0
	},

 	{
		.GptChannelId 			 = GPT_CHANNEL_ILL,
  	}
};
