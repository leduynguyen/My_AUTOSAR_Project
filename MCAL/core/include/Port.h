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

/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ|PPC|TMS570|RH850F1H|MPC5607B|MPC5645S|STM32|JACINTO5|JACINTO6|MPC5748G */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#ifndef PORT_H_
#define PORT_H_

#define PORT_MODULE_ID           124u
#define PORT_VENDOR_ID           60u


#define PORT_SW_MAJOR_VERSION   5u
#define PORT_SW_MINOR_VERSION   0u
#define PORT_SW_PATCH_VERSION   1u

#define PORT_AR_RELEASE_MAJOR_VERSION   4u
#define PORT_AR_RELEASE_MINOR_VERSION   1u
#define PORT_AR_RELEASE_PATCH_VERSION   2u

/** @req SWS_Port_00130 */
/** @req SWS_Port_00208 Published via Port_Cfg.h */
/** @req SWS_Port_00228 Defined in Port_Cfg.h */
#include "Std_Types.h"
#include "Port_Cfg.h"

/* Error Codes */
/* @req SWS_Port_00051 */
#define PORT_E_PARAM_PIN              0x0au
#define PORT_E_DIRECTION_UNCHANGEABLE 0x0bu
#define PORT_E_PARAM_CONFIG           0x0cu
#define PORT_E_PARAM_INVALID_MODE     0x0du
#define PORT_E_MODE_UNCHANGEABLE      0x0eu
#define PORT_E_UNINIT                 0x0fu
#define PORT_E_PARAM_POINTER          0x10u
#define PORT_E_UNEXPECTED_EXECUTION   0x20u


/* Service id's */
#define PORT_INIT_ID                    0x00u
#define PORT_SET_PIN_DIRECTION_ID       0x01u
#define PORT_REFRESH_PORT_DIRECTION_ID  0x02u
#define PORT_GET_VERSION_INFO_ID        0x03u
#define PORT_SET_PIN_MODE_ID            0x04u
#define PORT_GLOBAL_ID                  0xffu


/**
 * @req SWS_Port_00230
 * @req SWS_Port_00220
 * @req SWS_Port_00046
 * The type Port_PinDirectionType is a type for defining the direction of a Port Pin.
 * PORT_PIN_IN Sets port pin as input. 
 * PORT_PIN_OUT  Sets port pin as output. 
 */
typedef enum
{
    PORT_PIN_IN = 0u,
    PORT_PIN_OUT = 1u
} Port_PinDirectionType;

/** @req SWS_Port_00221 */
/** @req SWS_Port_00231*/
#if defined(CFG_RH850)
typedef uint16 Port_PinModeType;
#elif defined(CFG_MPC560X) || defined(CFG_MPC5645S) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70)
typedef uint16 Port_PinModeType;
#else
typedef uint32 Port_PinModeType;
#endif

/** @req SWS_Port_00229 */
/** @req SWS_Port_00219 */
#if defined(CFG_PPC) || defined(CFG_RH850)
typedef uint16 Port_PinType;
#elif defined(CFG_ARM)
typedef uint8_t Port_PinType;
#else
#error "Invalid architecture"
#endif


/**
 * Initializes the port module
 * @param configType Initialization config structure
 */
/* @req SWS_Port_00140 */
void Port_Init(const Port_ConfigType *configType);

#if ( PORT_SET_PIN_DIRECTION_API == STD_ON )
/**
 * Set pin direction
 * @param pin
 * @param direction
 */
/** @req SWS_Port_00141 */
/** @req SWS_Port_00086 */
void Port_SetPinDirection(Port_PinType pin, Port_PinDirectionType direction);
#endif


/**
 * Refreshed port direction
 */
/** @req  SWS_Port_00142 */
void Port_RefreshPortDirection(void);

#if (PORT_SET_PIN_MODE_API == STD_ON)
/**
 * Sets the pin mode
 * @param Pin
 * @param Mode
 */
/** @req:ZYNQ|PPC|RH850F1H|MPC5607B|MPC5645S|MPC5748G|STM32|JACINTO5|JACINTO6 SWS_Port_00145 */
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
#endif

#if (PORT_VERSION_INFO_API == STD_ON)
/**
 * Gets the version info for the PORT module
 * @param versioninfo
 */
/** @req SWS_Port_00143 */
void Port_GetVersionInfo(Std_VersionInfoType *versionInfo);
#endif


#endif /*PORT_H_*/
/** @} */
