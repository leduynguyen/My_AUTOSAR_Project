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

/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ|PPC|TMS570|MPC5607B|MPC5645S|RH850F1H|STM32|JACINTO5|MPC5748G */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/** @addtogroup Adc ADC Driver
 *  @{ */

/** @file Adc.h
 * API and type definitions for ADC Driver.
 */

#ifndef ADC_H_
#define ADC_H_

#include "Std_Types.h"

#define ADC_VENDOR_ID                       60u
#define ADC_MODULE_ID                       123u
#define ADC_AR_RELEASE_MAJOR_VERSION        4u
#define ADC_AR_RELEASE_MINOR_VERSION        1u
#define ADC_AR_RELEASE_PATCH_VERSION        2u

#define ADC_SW_MAJOR_VERSION                2u
#define ADC_SW_MINOR_VERSION                0u
#define ADC_SW_PATCH_VERSION                0u

/** General requirements tagging */
/* @req SWS_Adc_00363 VARIANT-POST-BUILD: Parameters with “Pre-compile time”, “Link time” and “Post-build time” are allowed */
/* @req SWS_Adc_00364 Imported types: Dem_EventIdType, Dem_EventStatusType, Std_Types, Std_ReturnType, Std_VersionInfoType */
/* @req SWS_Adc_00505 Adc_ConfigType structure */
/* @req SWS_Adc_00506 Adc_ChannelType uint */
/* @req SWS_Adc_00507 Adc_GroupType uint */
/* @req SWS_Adc_00508 Adc_ValueGroupType int */
/* @req SWS_Adc_00509 Adc_PrescaleType uint */
/* @req SWS_Adc_00510 Adc_ConversionTimeType uint */
/* @req SWS_Adc_00513 Adc_StatusType enum */
/* @req SWS_Adc_00515 Adc_GroupConvModeType Enumeration */
/* @req SWS_Adc_00517 Adc_GroupDefType */
/* @req SWS_Adc_00518 Adc_StreamNumSampleType uint */
/* @req SWS_Adc_00098 All channels of a group share the same group configuration */
/* @req SWS_Adc_00099 Symbolic names of channels and groups shall be defined by the configurator*/

/* @req:PPC|MPC5607B|MPC5645S|MPC5748G SWS_Adc_00084 Every group shall have a call-back. */
/* @req:PPC|MPC5607B|MPC5645S|MPC5748G SWS_Adc_00085 The call-backs shall be configured as pointers to functions. */
/* @req:PPC|MPC5607B|MPC5645S|JACINTO5|RH850F1H|MPC5748G SWS_Adc_00104 Individual notification per channel group. */
/* @req:PPC|MPC5607B|MPC5645S|JACINTO5|RH850F1H|MPC5748G SWS_Adc_00416 No buffering of nofifications when notifications are disabled. */


/** Group status. */
typedef enum
{
  ADC_IDLE,
  ADC_BUSY,
  ADC_COMPLETED,
  ADC_STREAM_COMPLETED,
}Adc_StatusType;


/* DET errors that the ADC can produce. */

#define  ADC_E_UNINIT               0x0Au
#define  ADC_E_BUSY                 0x0Bu
#define  ADC_E_IDLE                 0x0Cu
#define  ADC_E_ALREADY_INITIALIZED  0x0Du
#define  ADC_E_PARAM_CONFIG         0x0Eu
#define  ADC_E_PARAM_POINTER        0x14u
#define  ADC_E_PARAM_GROUP          0x15u
#define  ADC_E_WRONG_CONV_MODE      0x16u
#define  ADC_E_WRONG_TRIGG_SRC      0x17u
#define  ADC_E_NOTIF_CAPABILITY     0x18u
#define  ADC_E_BUFFER_UNINIT        0x19u


/** API service ID's */

#define   ADC_INIT_ID                           0x00u
#define   ADC_DEINIT_ID                         0x01u
#define   ADC_STARTGROUPCONVERSION_ID           0x02u
#define   ADC_STOPGROUPCONVERSION_ID            0x03u
#define   ADC_READGROUP_ID                      0x04u
#define   ADC_ENABLEHARDWARETRIGGER_ID          0x05u
#define   ADC_DISABLEHARDWARETRIGGER_ID         0x06u
#define   ADC_ENABLEGROUPNOTIFICATION_ID        0x07u
#define   ADC_DISABLEGROUPNOTIFICATION_ID       0x08u
#define   ADC_GETGROUPSTATUS_ID                 0x09u
#define   ADC_GETVERSIONINFO_ID                 0x0Au
#define   ADC_GETSTREAMLASTPOINTER_ID           0x0Bu
#define   ADC_SETUPRESULTBUFFER_ID              0x0Cu




/*
 * Std-types
 *
 */
/** Access mode to group conversion results. */
/* @req SWS_Adc_00528 */
typedef enum
{
  ADC_ACCESS_MODE_SINGLE,
  ADC_ACCESS_MODE_STREAMING
}Adc_GroupAccessModeType;

/** Group trigger source (Not supported). */
/* @req SWS_Adc_00514 */
typedef enum
{
  ADC_TRIGG_SRC_SW,
  ADC_TRIGG_SRC_HW
}Adc_TriggerSourceType;

/** HW trigger edge (Not supported). */
/* @!req SWS_Adc_00520 */
typedef enum
{
  ADC_HW_TRIG_FALLING_EDGE,
  ADC_HW_TRIG_RISING_EDGE,
  ADC_HW_TRIG_BOTH_EDGES,
}Adc_HwTriggerSignalType;

/** Stream buffer type. */
/* @req SWS_Adc_00519 */
typedef enum
{
  ADC_STREAM_BUFFER_LINEAR,
  ADC_STREAM_BUFFER_CIRCULAR
}Adc_StreamBufferModeType;

#include "Adc_Cfg.h"


/* Function interface. */
/* @req SWS_Adc_00365 */
/** Initializes the ADC hardware units and driver.
 * @param ConfigPtr Pointer to configuration structure. */
void Adc_Init(const Adc_ConfigType *ConfigPtr);
#if (ADC_DEINIT_API == STD_ON)
/* @req SWS_Adc_00366 */
/* @req SWS_Adc_00228 */
/** Returns all ADC HW Units to a state comparable to their power on reset state. */
void Adc_DeInit(void);

#endif

/* @req SWS_Adc_00419 */
/** Sets up the result buffer for a group.
 * @param Group The ADC Group to setup buffer for.
 * @param DataBufferPtr The buffer to use.
 * @returns E_OK: result buffer pointer initialized correctly E_NOT_OK: operation failed or development error occured*/
Std_ReturnType Adc_SetupResultBuffer (Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr);

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/* @req SWS_Adc_00367 */
/* @req SWS_Adc_00259 */
/** Starts the conversion of all channels of the requested ADC Channel group.
 * @param Group The group to start.*/
void           Adc_StartGroupConversion (Adc_GroupType Group);
/* @req SWS_Adc_00368 */
/* @req SWS_Adc_00260 */
/** Stops the conversion of all channels of the requested ADC Channel group.
 * @param Group The group to stop.*/
void           Adc_StopGroupConversion (Adc_GroupType Group);
#endif
#if (ADC_READ_GROUP_API == STD_ON)
/* @req SWS_Adc_00369 */
/* @req SWS_Adc_00359*/
/** Reads results from last conversion into buffer
 * @param Group The group you want samples for.
 * @param DataBufferPtr The buffer to which the result will be copied
 * @returns E_OK if results are available and written to the data buffer.
 * E_NOT_OK: no results are available or development error occured */
Std_ReturnType Adc_ReadGroup (Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr);
#endif

#if !defined(CFG_HC1X)
/* @req SWS_Adc_00375 */
/** Reads results from last streaming conversion into buffer
 * @param Group The group you want samples for.
 * @param PtrToSampleDataPtr Pointer into the result buffer where the latest result is located.
 * @returns Number of valid samples per channel stored in the result buffer. */
Adc_StreamNumSampleType Adc_GetStreamLastPointer(Adc_GroupType Group, Adc_ValueGroupType** PtrToSamplePtr);
#endif

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
/* @req SWS_Adc_00372 */
/* @req SWS_Adc_00100 */
/** Enables the notification mechanism for the requested ADC Channel group.
 * @param Group The group for which you want to enable notifications.*/
void           Adc_EnableGroupNotification (Adc_GroupType Group);
/* @req SWS_Adc_00373 */
/* @req SWS_Adc_00101*/
/** Disables the notification mechanism for the requested ADC Channel group.
* @param Group The group for which you want to enable notifications.*/
void           Adc_DisableGroupNotification (Adc_GroupType Group);
#endif

/* @req SWS_Adc_00374 */
/** Returns the conversion status of the requested ADC Channel group.
 * @param Group The group for which you want status.*/
Adc_StatusType Adc_GetGroupStatus (Adc_GroupType Group);

#if (STD_ON == ADC_VERSION_INFO_API)
/* @req SWS_Adc_00376 */
/**
 * Returns the version information of this module.
 *
 * @param versioninfo Pointer to where to store the version information of this module.
 */
void Adc_GetVersionInfo (Std_VersionInfoType* versioninfo);
#endif

#if (STD_ON == ADC_HW_TRIGGER_API)
/* @req:ZYNQ SWS_Adc_00370 */
/* @req:ZYNQ SWS_Adc_00265*/
/**
 * Enables the hardware trigger for the requested ADC Channel group.
 * @param Group Numeric ID of requested ADC Channel group.
 */
void Adc_EnableHardwareTrigger(Adc_GroupType Group);
/* @req:ZYNQ SWS_Adc_00371 */
/* @req:ZYNQ SWS_Adc_00266 */
/**
 * Disables the hardware trigger for the requested ADC Channel group.
 * @param Group Numeric ID of requested ADC Channel group.
 */
void Adc_DisableHardwareTrigger(Adc_GroupType Group);
#endif



#endif /*ADC_H_*/

/** @} */

