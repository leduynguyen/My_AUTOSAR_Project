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

/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */
/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ|PPC|TMS570|MPC5607B|MPC5645S|RH850F1H|MPC5748G */

#ifndef WDG_H_
#define WDG_H_

#include "WdgIf_Types.h"

#define WDG_MODULE_ID                   102u
#define WDG_VENDOR_ID                   60u

#define WDG_SW_MAJOR_VERSION            2u
#define WDG_SW_MINOR_VERSION            0u
#define WDG_SW_PATCH_VERSION            0u

#define WDG_AR_RELASE_MAJOR_VERSION     4u
#define WDG_AR_RELASE_MINOR_VERSION     1u
#define WDG_AR_RELASE_PATCH_VERSION     2u

/* Needs to be after the version defines */
#include "Wdg_Cfg.h"

/* Error codes */
/* @req SWS_Wdg_00010 */
#define WDG_E_DRIVER_STATE  0x10u
#define WDG_E_PARAM_MODE    0x11u
#define WDG_E_PARAM_CONFIG  0x12u
#define WDG_E_PARAM_TIMEOUT 0x13u
#define WDG_E_PARAM_POINTER 0x14u

/* Service Id */
#define WDG_INIT_SERVICE_ID                        0x00u
#define WDG_SET_MODE_SERVICE_ID                    0x01u
#define WDG_SET_TRIGGERING_CONDITION_SERVICE_ID    0x03u
#define WDG_GET_VERSION_INFO_SERVICE_ID            0x04u

#if defined(CFG_STM32F1X)
void Wdg_IWDG_Init (const Wdg_IWDG_ConfigType* ConfigPtr);
void Wdg_IWDG_Trigger (uint16 timeout);
Std_ReturnType Wdg_IWDG_SetMode (WdgIf_ModeType Mode);
void Wdg_IWDG_GetVersionInfo (void /* IMPROVEMENT Std_VersionInfoType* versioninfo*/);

void Wdg_WWDG_Init (const Wdg_WWDG_ConfigType* ConfigPtr);
void Wdg_WWDG_Trigger (uint16 timeout);
Std_ReturnType Wdg_WWDG_SetMode (WdgIf_ModeType Mode);
void Wdg_WWDG_GetVersionInfo (void /* IMPROVEMENT Std_VersionInfoType* versioninfo*/);
#endif

#if (WDG_VERSION_INFO_API == STD_ON)

/**
 * Gets the version info for the module
 * @param versionInfo - out parameter that hold the version info
 */
/** @req SWS_Wdg_00109 */
void Wdg_GetVersionInfo( Std_VersionInfoType *versionInfo );
#endif


/**
 * Initialized the watchdog driver
 * @param ConfigPtr - a pointer to the configuration that will be used for initialization
 */
/** @req SWS_Wdg_00106 */
void Wdg_Init (const Wdg_ConfigType* ConfigPtr);


/**
 * Resets the watchdog timer
 * @param timeout - not used. A zero will not reset the watchdog
 */
/** @req SWS_Wdg_00155 */
void Wdg_SetTriggerCondition (uint16 timeout);


/**
 * Ses the mode of the watchdog driver
 * @param Mode - the mode that the watchdog will be set to
 * @return
 */
/** @req SWS_Wdg_00107 */
Std_ReturnType Wdg_SetMode (WdgIf_ModeType Mode);

#ifdef HOST_TEST
uint32 Wdg_Arc_GetTriggerCounter(void);
#endif

#endif /* WDG_H_ */
