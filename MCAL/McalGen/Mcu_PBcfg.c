/*
 * Generator version: 2.0.0
 * AUTOSAR version:   4.1.2
 */
/*lint -w2*/
#include "Mcu.h"
 



const Mcu_ClockSettingConfigType Mcu_ClockSettingConfigData[] = {
   {
      .McuClockReferencePointFrequency = 25000000UL,
	  .Pll1    = 9,
      .Pll2    = 8,
      .Pll3    = 0,
   }
};

const Mcu_PerClockConfigType McuPerClockConfigData =
{ 
.AHBClocksEnable  = 0,
.APB1ClocksEnable = RCC_APB1Periph_CAN1 ,
.APB2ClocksEnable = RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO };

const Mcu_ConfigType McuConfigData[] = {
   {
      .McuNumberOfMcuModes = 3u,
      .McuRamSectors = 0u,
      .McuClockSettings = 1u,
      .McuDefaultClockSettings = McuConf_McuClockSettingConfig_McuClockSettingConfig, 
      .McuClockSettingConfig = &Mcu_ClockSettingConfigData[0],	

      .McuRamSectorSettingConfig = NULL

   }
};

