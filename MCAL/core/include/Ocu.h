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
/** @tagSettings DEFAULT_ARCHITECTURE=PPC|MPC5607B|MPC5645S */

#ifndef OCU_H_
#define OCU_H_

/** General req tagging */
/* @req SWS_Ocu_00027 */
/* @req SWS_Ocu_00169 */

/* @req SWS_Ocu_00003 */
#include "Std_Types.h"


#define OCU_VENDOR_ID               60u
#define OCU_MODULE_ID               125u

#define OCU_AR_MAJOR_VERSION    4u
#define OCU_AR_MINOR_VERSION    1u
#define OCU_AR_PATCH_VERSION    2u

#define OCU_SW_MAJOR_VERSION    1u
#define OCU_SW_MINOR_VERSION    0u
#define OCU_SW_PATCH_VERSION    0u

/** Det error codes */
#define OCU_E_PARAM_CONFIG              1u
#define OCU_E_UNINIT                    2u
#define OCU_E_PARAM_INVALID_CHANNEL     3u
#define OCU_E_PARAM_INVALID_STATE       4u
#define OCU_E_PARAM_INVALID_ACTION      5u
#define OCU_E_NO_VALID_NOTIF            6u
#define OCU_E_ALREADY_INITIALIZED       7u
#define OCU_E_PARAM_POINTER             8u
#define OCU_E_BUSY                      9u
#define OCU_E_PARAM_NO_PIN              0xAu

/** Type definitions */
/* @req SWS_Ocu_00028 */
typedef uint8 Ocu_ChannelType;

/* @req SWS_Ocu_00029 */
typedef uint16 Ocu_ValueType;

/* @req SWS_Ocu_00031 */
typedef enum {
    OCU_HIGH,
    OCU_LOW
}Ocu_PinStateType;

/* @req SWS_Ocu_00032 */
typedef enum {
    OCU_SET_HIGH,
    OCU_SET_LOW,
    OCU_TOGGLE,
    OCU_DISABLE
}Ocu_PinActionType;

typedef struct {

/* @req SWS_Ocu_00034 */
uint8   OcuChannelId;
uint32  OcuDefaultThreshold;
boolean OcuOutpinUsed;
Ocu_PinStateType OcuOutputPinDefState;
void (*OcuNotification)(void);

}Ocu_ChannelConfigType;

typedef enum {
    OCU_DOWNCOUNTING,
    OCU_UPCOUNTING
}Ocu_CountdirectionType;

typedef struct {
uint8   OcuGroupId;
uint16  OcuChannelTickDur;
uint16  OcuMaxCounterTickVal;
}Ocu_GroupConfigType;

/* @req SWS_Ocu_00033 */
typedef struct {
const Ocu_ChannelConfigType * OcuChannelConfig;
const Ocu_CountdirectionType  OcuCountDirection;
const Ocu_GroupConfigType   * OcuGroupConfig;
const uint8                 * OcuHwMap;
}Ocu_ConfigType;

/* @req SWS_Ocu_00138 */
typedef enum {
    OCU_CM_IN_REF_INTERVAL,
    OCU_CM_OUT_REF_INTERVAL
}Ocu_ReturnType;


typedef enum {
    OCU_UNINIT,
    OCU_INIT
}Ocu_DriverStatusType;


typedef enum {
    OCU_CHANNEL_STOPPED,
    OCU_CHANNEL_RUNNING
}Ocu_ChnlStateType;


/* @req SWS_Ocu_00002 */
#include "Ocu_Cfg.h"

/** Api Service Ids */
#define OCU_INIT_SERVICE_ID                     0u
#define OCU_DEINIT_SEVICE_ID                    1u
#define OCU_STARTCHANNEL_SERVICE_ID             2u
#define OCU_STOPCHANNEL_SERVICE_ID              3u
#define OCU_SETPINSTATE_SERVICE_ID              4u
#define OCU_SETPINACTION_SERVICE_ID             5u
#define OCU_GETCOUNTER_SERVICE_ID               6u
#define OCU_SETABSOLUTETHRESHOLD_SERVICE_ID     7u
#define OCU_SETRELATIVETHRESHOLD_SERVICE_ID     8u
#define OCU_GETVERSIONINFO_SERVICE_ID           9u
#define OCU_DISABLE_NOTIFICATION_SERVICE_ID    10u
#define OCU_ENABLE_NOTIFICATION_SERVICE_ID     11u

/** Api declarations */

/* @req SWS_Ocu_00035 */
void Ocu_Init(const Ocu_ConfigType* ConfigPtr);

#if (OCU_DE_INIT_API == STD_ON)
/* @req SWS_Ocu_00045 */
void Ocu_DeInit(void);
#endif

/* @req SWS_Ocu_00051 */
void Ocu_StartChannel(Ocu_ChannelType ChannelNumber);
/* @req SWS_Ocu_00058 */
void Ocu_StopChannel(Ocu_ChannelType ChannelNumber);

#if (OCU_SET_PIN_STATE_API == STD_ON)
/* @req SWS_Ocu_00066 */
void Ocu_SetPinState(Ocu_ChannelType ChannelNumber,Ocu_PinStateType PinState);
#endif

#if (OCU_SET_PIN_ACTION_API == STD_ON)
/* @req SWS_Ocu_00076 */
void Ocu_SetPinAction(Ocu_ChannelType ChannelNumber,Ocu_PinActionType PinAction);
#endif

#if (OCU_GET_COUNTER_API == STD_ON)
/* @req SWS_Ocu_00085 */
Ocu_ValueType  Ocu_GetCounter(Ocu_ChannelType ChannelNumber);
#endif

#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
/* @req SWS_Ocu_00091 */
Ocu_ReturnType Ocu_SetAbsoluteThreshold(Ocu_ChannelType ChannelNumber,Ocu_ValueType ReferenceValue,Ocu_ValueType AbsoluteValue);
#endif

#if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
/* @req SWS_Ocu_00100 */
Ocu_ReturnType Ocu_SetRelativeThreshold(Ocu_ChannelType ChannelNumber,Ocu_ValueType RelativeValue);
#endif

#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
/* @req SWS_Ocu_00108 */
void Ocu_DisableNotification(Ocu_ChannelType ChannelNumber);
/* @req SWS_Ocu_00115 */
void Ocu_EnableNotification(Ocu_ChannelType ChannelNumber);
#endif

#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
/* @req SWS_Ocu_00122 */
void Ocu_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif


#endif /* OCU_H_ */

