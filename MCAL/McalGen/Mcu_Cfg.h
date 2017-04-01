/*
 * Generator version: 2.0.0
 * AUTOSAR version:   4.1.2
 */

#if !(((MCU_SW_MAJOR_VERSION == 2) && (MCU_SW_MINOR_VERSION == 0)) )
#error Mcu: Configuration file expected BSW module version to be 2.0.*
#endif

#if !(((MCU_AR_RELEASE_MAJOR_VERSION == 4) && (MCU_AR_RELEASE_MINOR_VERSION == 1)) )
#error Mcu: Configuration file expected AUTOSAR version to be 4.1.*
#endif

#ifndef MCU_CFG_H_
#define MCU_CFG_H_

#include "Mcu_ConfigTypes.h"

#define MCU_DEV_ERROR_DETECT 	           STD_ON 
#define MCU_PERFORM_RESET_API 	           STD_OFF
#define MCU_VERSION_INFO_API 	           STD_OFF
#define MCU_NO_PLL                         STD_OFF
#define MCU_INIT_CLOCK                     STD_ON
#define MCU_GET_RAM_STATE                  STD_OFF
#define MCU_CLOCK_SRC_FAILURE_NOTIFICATION STD_OFF
#define MCU_POSTBUILD_VARIANT 			   STD_OFF


/* Mcu Modes (Symbolic name) */
#define McuConf_McuModeSettingConf_NORMAL (Mcu_ModeType)0u 
#define Mcu_NORMAL McuConf_McuModeSettingConf_NORMAL 
#define McuConf_McuModeSettingConf_RUN (Mcu_ModeType)1u 
#define Mcu_RUN McuConf_McuModeSettingConf_RUN 
#define McuConf_McuModeSettingConf_SLEEP (Mcu_ModeType)2u 
#define Mcu_SLEEP McuConf_McuModeSettingConf_SLEEP 

/* Mcu Clock Types (Symbolic name) */
#define McuConf_McuClockSettingConfig_McuClockSettingConfig (Mcu_ClockType)0u  
#define Mcu_McuClockSettingConfig McuConf_McuClockSettingConfig_McuClockSettingConfig 

/* Mcu Ram Sections */


/* Configuration Set Handle */
#define McuModuleConfiguration (McuConfigData)
#define Mcu_McuModuleConfiguration (McuConfigData)

#endif /* MCU_CFG_H_ */

