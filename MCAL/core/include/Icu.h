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
/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ|PPC|MPC5645S|MPC5607B */

/* Icu_ModeType */
/** @req:MPC560XB|MPC5645S SWS_Icu_00277 */

/* Icu_ChannelType */
/** @req SWS_Icu_00278 */

/* Icu_InputStateType */
/** @req:MPC560XB|MPC5645S SWS_Icu_00279 */

/* Icu_ConfigType */
/** @req SWS_Icu_00280 */

/* Icu_ActivaitonType */
/** @req SWS_Icu_00289 */

/* Icu_ValueType */
/** @req:MPC560XB|MPC5645S SWS_Icu_00290 */

/* Icu_DutyCycleType */
/** @req:MPC560XB|MPC5645S SWS_Icu_00291 */

/* Icu_IndexType */
/** @req:MPC560XB|MPC5645S SWS_Icu_00292 */

/* Icu_EdgeNumberType */
/** @req:MPC560XB|MPC5645S SWS_Icu_00293 */

/* Icu_MeasurementModeType */
/** @req:MPC560XB|MPC5645S SWS_Icu_00294 */

/* Icu_SignalMeasurementPropertyType */
/** @req:MPC560XB|MPC5645S SWS_Icu_00295 */

/* Icu_TimestampBufferType */
/** @req:MPC560XB|MPC5645S SWS_Icu_00296 */



#ifndef ICU_H_
#define ICU_H_


#include "Std_Types.h"

#define ICU_MODULE_ID           (122u)
#define ICU_VENDOR_ID           (60u)

#define ICU_SW_MAJOR_VERSION    2u
#define ICU_SW_MINOR_VERSION    0u
#define ICU_SW_PATCH_VERSION    0u

#define ICU_AR_RELEASE_MAJOR_VERSION    4u
#define ICU_AR_RELEASE_MINOR_VERSION    1u
#define ICU_AR_RELEASE_PATCH_VERSION    2u

/* API Service ID's  */
#define ICU_INIT_ID                    0x00u
#define ICU_DEINIT_ID                  0x01u
#define ICU_SETMODE_ID                 0x02u
#define ICU_DISABLEWAKEUP_ID           0x03u
#define ICU_ENABLEWAKEUP_ID            0x04u
#define ICU_CHECKWAKEUP_ID             0x15u
#define ICU_SETACTIVATIONCONDITION_ID  0x05u
#define ICU_DISABLENOTIFICATION_ID     0x06u
#define ICU_ENABLENOTIFICATION_ID      0x07u
#define ICU_GETINPUTSTATE_ID           0x08u
#define ICU_STARTTIMESTAMP_ID          0x09u
#define ICU_STOPTIMESTAMP_ID           0x0Au
#define ICU_GETTIMESTAMPINDEX_ID       0x0Bu
#define ICU_RESETEDGECOUNT_ID          0x0Cu
#define ICU_ENABLEEDGECOUNT_ID         0x0Du
#define ICU_ENABLEEDGEDETECTION_ID     0x16u
#define ICU_DISABLEEDGEDETECTION_ID    0x17u
#define ICU_DISABLEEDGECOUNT_ID        0x0Eu
#define ICU_GETEDGENUMBERS_ID          0x0Fu
#define ICU_STARTSIGNALMEASUREMENT_ID  0x13u
#define ICU_STOPSIGNALMEASUREMENT_ID   0x14u
#define ICU_GETTIMEELAPSED_ID          0x10u
#define ICU_GETDUTYCYCLEVALUES_ID      0x11u
#define ICU_GETVERSIONINFO_ID          0x12u

/* Error Codes */
#define ICU_E_PARAM_CONFIG              0x0Au
#define ICU_E_PARAM_CHANNEL             0x0Bu
#define ICU_E_PARAM_ACTIVATION          0x0Cu
#define ICU_E_PARAM_BUFFER_PTR          0x0Du
#define ICU_E_PARAM_BUFFER_SIZE         0x0Eu
#define ICU_E_PARAM_MODE                0x0Fu
#define ICU_E_UNINIT                    0x14u
#define ICU_E_NOT_STARTED               0x15u
#define ICU_E_BUSY_OPERATION            0x16u
#define ICU_E_ALREADY_INITIALIZED       0x17u
#define ICU_E_PARAM_NOTIFY_INTERVAL     0x18u
#define ICU_E_PARAM_VINFO               0x19u
// Following error codes are added by ArcCore
#define ICU_E_UNEXPECTED_EXECUTION      0x70u

/* Mode type */
typedef enum
{
    ICU_MODE_NORMAL,
    ICU_MODE_SLEEP
} Icu_ModeType;

/* Input state of an ICU channel */
typedef enum
{
    ICU_ACTIVE,
    ICU_IDLE
} Icu_InputStateType;


/* Activation type */
typedef enum
{
    ICU_RISING_EDGE,
    ICU_FALLING_EDGE,
    ICU_BOTH_EDGES
} Icu_ActivationType;

/* Width of timeticks */
typedef uint16 Icu_ValueType;

/* Values for calculating duty cycles */
typedef struct
{
    Icu_ValueType ActiveTime;
    Icu_ValueType PeriodTime;
} Icu_DutyCycleType;

/* Return value for Icu_GetTimeStampIndex() */
typedef uint32 Icu_IndexType; /* TBC: MCU Specific. Should 0 be allowed? (normally error) */

/* Return value for Icu_GetEdgeNumbers() */
typedef uint32 Icu_EdgeNumberType; /* TBC: MCU Specific. */

/* Measurement modes */
typedef enum
{
    ICU_MODE_SIGNAL_EDGE_DETECT,
    ICU_MODE_SIGNAL_MEASUREMENT,
    ICU_MODE_TIMESTAMP,
    ICU_MODE_EDGE_COUNTER
} Icu_MeasurementModeType;

/* Measurement properties */
typedef enum
{
    ICU_LOW_TIME,
    ICU_HIGH_TIME,
    ICU_PERIOD_TIME,
    ICU_DUTY_CYCLE
} Icu_SignalMeasurementPropertyType;

/* Timestamp measurement properties */
typedef enum
{
    ICU_LINEAR_BUFFER,
    ICU_CIRCULAR_BUFFER
} Icu_TimestampBufferType;

/* @req SWS_Icu_00187 */
typedef void (*Icu_NotificationHandlerType)();

/* Icu_ChannelType == eemios channel id.  */
typedef uint8 Icu_ChannelType;
typedef boolean Icu_WakeupCapabilityType;

#if defined(CFG_MPC5606B) || defined(CFG_MPC5607B) || defined(CFG_MPC5645S) || defined(CFG_SPC560B54) || defined(CFG_MPC5606S) || defined(CFG_MPC5746C)
typedef uint8 Icu_ChannelPrescalerType;
#endif

/** !req SWS_Icu_00039 - The edge counter is located in another struct. */
typedef struct {
    Icu_ChannelType             physical_channel;
    Icu_ActivationType          default_start_edge;
    Icu_MeasurementModeType     measurement_mode;
    Icu_SignalMeasurementPropertyType signal_measurement_property;
    Icu_WakeupCapabilityType    wakeup_capability;
    Icu_NotificationHandlerType notification;   /* @req SWS_Icu_00018 */
    Icu_TimestampBufferType     buffer_type;
#if defined(CFG_MPC5606B) || defined(CFG_MPC5607B) || defined(CFG_MPC5645S) || defined(CFG_SPC560B54) || defined(CFG_MPC5606S) || defined(CFG_MPC5746C)
    uint8                       clksrc;
    Icu_ChannelPrescalerType    prescaler;
#endif
} Icu_ChannelConfigurationType;


/** @req SWS_Icu_00245 */
#include "Icu_Cfg.h"


/* Initialize the driver */
/** @req SWS_Icu_00191 */
void Icu_Init( const Icu_ConfigType* ConfigPtr );

#if (ICU_DE_INIT_API == STD_ON)
/* De-initialize the ICU module */
/** @req SWS_Icu_00193 */
void Icu_DeInit( void );
#endif

#if (ICU_SET_MODE_API == STD_ON)
/* Sets the ICU mode */
/** @req:MPC560XB|MPC5645S SWS_Icu_00194 */
void Icu_SetMode( Icu_ModeType Mode );
#endif

#if (ICU_DISABLE_WAKEUP_API == STD_ON)
/* Disables the wakeup capability of a single ICU channel */
void Icu_DisableWakeup( Icu_ChannelType Channel );
#endif

#if (ICU_ENABLE_WAKEUP_API == STD_ON)
/* (Re-)enables the wakeup capability of the given ICU channel */
/** @req:MPC560XB|MPC5645S SWS_Icu_00196 */
void Icu_EnableWakeup( Icu_ChannelType Channel );
#endif

#if (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON && ICU_REPORT_WAKEUP_SOURCE == STD_ON)
/* Checks if a wakeup capable ICU channel is the source for a wakeup event
 * and calls the ECU state manager service EcuM_SetWakeupEvent
 * in case of a valid ICU channel wakeup event. */
/** @req:MPC560XB|MPC5645S SWS_Icu_00358 */
void Icu_CheckWakeup( EcuM_WakeupSourceType WakeupSource );
#endif

/* Sets the activation-edge for the given channel */
/** @req SWS_Icu_00197 */
void Icu_SetActivationCondition( Icu_ChannelType Channel, Icu_ActivationType Activation );

/* Disables the notification of a channel */
/** @req SWS_Icu_00198 */
void Icu_DisableNotification( Icu_ChannelType Channel );

/* Enables the notification on the given channel */
/** @req SWS_Icu_00199 */
void Icu_EnableNotification( Icu_ChannelType Channel );


#if (ICU_GET_INPUT_STATE_API == STD_ON)
/* Returns the status of the ICU input */
/** @req:MPC560XB|MPC5645S SWS_Icu_00200 */
Icu_InputStateType Icu_GetInputState( Icu_ChannelType Channel );
#endif

#if (ICU_TIMESTAMP_API == STD_ON)
/* Starts the capturing of timer values on the edges*/
/** @req:MPC560XB|MPC5645S SWS_Icu_00201 */
void Icu_StartTimestamp( Icu_ChannelType Channel, Icu_ValueType* BufferPtr, uint16 BufferSize, uint16 NotifyInterval );

/* Stops the timestamp measurement of the given channel */
/** @req:MPC560XB|MPC5645S SWS_Icu_00202 */
void Icu_StopTimestamp( Icu_ChannelType Channel );

/* Reads the timestamp index of the given channel */
/** @req:MPC560XB|MPC5645S SWS_Icu_00203 */
Icu_IndexType Icu_GetTimestampIndex( Icu_ChannelType Channel );
#endif

#if (ICU_EDGE_COUNT_API == STD_ON)
/* Resets the value of the counted edges to zero */
/** @req:MPC560XB|MPC5645S SWS_Icu_00204 */
void Icu_ResetEdgeCount( Icu_ChannelType Channel );

/* Enables the counting of edges of the given channel */
/** @req:MPC560XB|MPC5645S SWS_Icu_00205 */
void Icu_EnableEdgeCount( Icu_ChannelType Channel );

/* Disables the counting of edges of the given channel */
/** @req:MPC560XB|MPC5645S SWS_Icu_00206 */
void Icu_DisableEdgeCount( Icu_ChannelType Channel );

/* Reads the number of counted edges */
/** @req:MPC560XB|MPC5645S SWS_Icu_00207 */
Icu_EdgeNumberType Icu_GetEdgeNumbers( Icu_ChannelType Channel );
#endif

#if (ICU_EDGE_DETECT_API == STD_ON)
/* (Re-)Enables the detection of edges of the given channel */
/** @req SWS_Icu_00364 */
void Icu_EnableEdgeDetection( Icu_ChannelType Channel );

/* Disables the detection of edges of the given channel */
/** @req SWS_Icu_00377 */
void Icu_DisableEdgeDetection( Icu_ChannelType Channel );
#endif

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/* Starts the measurement of signals */
/** @req:MPC560XB|MPC5645S SWS_Icu_00208 */
void Icu_StartSignalMeasurement( Icu_ChannelType Channel );

/* Stops the measurement of signals of the given channel */
/** @req:MPC560XB|MPC5645S SWS_Icu_00209 */
void Icu_StopSignalMeasurement( Icu_ChannelType Channel );
#endif

#if (ICU_GET_TIME_ELAPSED_API == STD_ON)
/* Reads the elapsed Signal Low Time for the given channel */
/** @req:MPC560XB|MPC5645S SWS_Icu_00210 */
Icu_ValueType Icu_GetTimeElapsed( Icu_ChannelType Channel );
#endif

#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)
/* Reads the coherent active time and period time for the given ICU Channel */
/** @req:MPC560XB|MPC5645S SWS_Icu_00211 */
void Icu_GetDutyCycleValues( Icu_ChannelType Channel, Icu_DutyCycleType* DutyCycleValues );
#endif

#if (ICU_GET_VERSION_INFO_API)
/* returns the version information of this module */
/** @req SWS_Icu_00212 */
void Icu_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif

#endif /* ICU_H_ */
