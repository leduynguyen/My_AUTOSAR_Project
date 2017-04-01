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
/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ|PPC|TMS570|MPC5607B|MPC5645S|RH850F1H|STM32|JACINTO5|JACINTO6|MPC5748G */

/* Dio_ChannelType */
/** @req SWS_Dio_00182 */
/** @req SWS_Dio_00180 */

/* Dio_PortType */
/** @req SWS_Dio_00183 */
/** @req SWS_Dio_00181 */

/* Dio_ChannelGroupType */
/** @req SWS_Dio_00184 */

/* Dio_LevelType */
/** @req SWS_Dio_00185 */

/* Dio_PortLevelType */
/** @req SWS_Dio_00186 */

#ifndef DIO_H_
#define DIO_H_

#include "Std_Types.h" /** @req SWS_Dio_00170 */

#define DIO_MODULE_ID                       120u
#define DIO_VENDOR_ID                       60u

#define DIO_SW_MAJOR_VERSION                5u
#define DIO_SW_MINOR_VERSION                0u
#define DIO_SW_PATCH_VERSION                0u

#define DIO_AR_RELEASE_MAJOR_VERSION        4u
#define DIO_AR_RELEASE_MINOR_VERSION        1u
#define DIO_AR_RELEASE_PATCH_VERSION        2u


// API Service ID's
#define DIO_READCHANNEL_ID                  0x00u
#define DIO_WRITECHANNEL_ID                 0x01u
#define DIO_READPORT_ID                     0x02u
#define DIO_WRITEPORT_ID                    0x03u
#define DIO_READCHANNELGROUP_ID             0x04u
#define DIO_WRITECHANNELGROUP_ID            0x05u
#define DIO_INIT_ID                         0x10u
#define DIO_GETVERSIONINFO_ID               0x12u
#define DIO_GLOBAL_ID                       0xFFu

#define DIO_E_PARAM_INVALID_CHANNEL_ID      10u
#define DIO_E_PARAM_INVALID_PORT_ID         20u
#define DIO_E_PARAM_INVALID_GROUP_ID        31u
#define DIO_E_PARAM_CONFIG                  0x10u
#define DIO_E_PARAM_POINTER                 0x20u

/* ArcCore extra error ids */
#define DIO_E_UNINIT                        0x30u
#define DIO_E_UNEXPECTED_EXECUTION          0x31u
#define DIO_E_PARAM_LEVEL                   0x32u


#if defined(CFG_HC1X) || defined(CFG_TMS570)
typedef uint8 Dio_ChannelType;
typedef uint8 Dio_PortType;

typedef struct
{
  Dio_PortType port;
  uint8 offset;
  uint8 mask;
} Dio_ChannelGroupType;

typedef uint8 Dio_LevelType;

typedef uint32 Dio_PortLevelType;

#elif defined (CFG_ZYNQ)

typedef uint32 Dio_ChannelType;
typedef uint32 Dio_PortType;
typedef struct
{
  Dio_PortType port;
  uint8 offset;
  uint32 mask;
} Dio_ChannelGroupType;

typedef uint8 Dio_LevelType;

typedef uint32_t Dio_PortLevelType;

#else	// CFG_PPC, CFG_STM32_STAMP and others
typedef uint32 Dio_ChannelType;
typedef uint32 Dio_PortType;
typedef struct
{
  Dio_PortType port;
  uint8 offset;
  uint16 mask;
} Dio_ChannelGroupType;

typedef uint8 Dio_LevelType;

typedef uint16 Dio_PortLevelType;
#endif

/** @req SWS_Dio_00187 */
typedef struct {
    const Dio_ChannelType* ChannelConfig;
    const Dio_ChannelGroupType* GroupConfig;
    const Dio_PortType *PortConfig;
}Dio_ConfigType;

#include "Dio_Cfg.h"

/* Publish the configuration */
extern const Dio_ConfigType DioConfigData;

/** @req SWS_Dio_00139 */
#if (DIO_VERSION_INFO_API == STD_ON)
/**
 * Gets the version info
 * @param versioninfo
 */
void Dio_GetVersionInfo( Std_VersionInfoType *versionInfo );
#endif

/**
 * Reads the value of a channel, if input buffer enables the actual value will be read
 * otherwise the register value
 * @param channelId - the channel id
 * @return Level of channel
 */
/** @req SWS_Dio_00133 */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType channelId);


/**
 * Writes a level to a channel
 * @param channelId - the channel id
 * @param level - the level to be written
 */
/** @req SWS_Dio_00134 */
void Dio_WriteChannel(Dio_ChannelType channelId, Dio_LevelType level);


// Disable R/W Channel Group and R/W Port APIs for incompatible MCU:s:
#if !defined(DISABLE_DIO_PARALLELL_RW_API)

/**
 * Reads all pins in a port
 * @param portId
 * @return Each bit is a channel within the port
 */
/** @req:ZYNQ|PPC|TMS570|MPC5607B|RH850F1H|STM32|MPC5748G SWS_Dio_00135 */
Dio_PortLevelType Dio_ReadPort(Dio_PortType portId);


/**
 * Writes levels to a port
 * @param portId - the port id id
 * @param level - each bit is a channel within the port
 */
/** @req:ZYNQ|PPC|TMS570|MPC5607B|RH850F1H|STM32|MPC5748G SWS_Dio_00136 */
void Dio_WritePort(Dio_PortType portId, Dio_PortLevelType level);


/**
 * Reads a channel group
 * @param channelGroupIdPtr
 * @return Each bit is a channel within the group
 */
/** @req:ZYNQ|PPC|TMS570|MPC5607B|RH850F1H|STM32|MPC5748G SWS_Dio_00137 */
Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType *channelGroupIdPtr );


/**
 * Writes a channel group
 * @param channelGroupIdPtr
 * @param level - Each bit is a channel within the group
 */
/** @req:ZYNQ|PPC|TMS570|MPC5607B|RH850F1H|STM32|MPC5748G SWS_Dio_00138 */
void Dio_WriteChannelGroup(const Dio_ChannelGroupType *channelGroupIdPtr, Dio_PortLevelType level);

#endif

/**
 * Initialize the DIO module
 * @param ConfigPtr
 */
/** @req SWS_Dio_00165 */
void Dio_Init(const Dio_ConfigType* ConfigPtr);

#if defined(HOST_TEST)
void Dio_Arc_Deinit(void);
void Dio_Arc_SetConfigToNULL(void);
#endif

#endif /*DIO_H_*/
