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

/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ|PPC|MPC5645S|MPC5607B|MPC5748G|MPC5747C|TMS570|RH850F1H|JACINTO5|JACINTO6|STM32 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */


/** @addtogroup Gpt GPT Driver
 *  @{ */

/** @file Gpt.h
 * API and type definitions for GPT Driver.
 */

#ifndef GPT_H_
#define GPT_H_

#include "Std_Types.h"

#define GPT_VENDOR_ID                       60u
#define GPT_MODULE_ID                       100u

#define GPT_SW_MAJOR_VERSION                3u
#define GPT_SW_MINOR_VERSION                0u
#define GPT_SW_PATCH_VERSION                0u

#define GPT_AR_RELEASE_MAJOR_VERSION        4u
#define GPT_AR_RELEASE_MINOR_VERSION        1u
#define GPT_AR_RELEASE_PATCH_VERSION        2u


/** Error Codes */
#define GPT_E_UNINIT                        0x0Au
#define GPT_E_BUSY                          0x0Bu
#define GPT_E_MODE                          0x0cu
#define GPT_E_ALREADY_INITIALIZED           0x0du
#define GPT_E_PARAM_CHANNEL                 0x14u
#define GPT_E_PARAM_VALUE                   0x15u
#define GPT_E_PARAM_POINTER                 0x16u
#define GPT_E_PARAM_MODE                    0x1fu

/** Service id's */
#define GPT_GETVERSIONINFO_SERVICE_ID       0x00u
#define GPT_INIT_SERVICE_ID                 0x01u
#define GPT_DEINIT_SERVICE_ID               0x02u
#define GPT_GETTIMEELAPSED_SERVICE_ID       0x03u
#define GPT_GETTIMEREMAINING_SERVICE_ID     0x04u
#define GPT_STARTTIMER_SERVICE_ID           0x05u
#define GPT_STOPTIMER_SERVICE_ID            0x06u
#define GPT_ENABLENOTIFICATION_SERVICE_ID   0x07u
#define GPT_DISABLENOTIFICATION_SERVICE_ID  0x08u
#define GPT_SETMODE_SERVICE_ID              0x09u
#define GPT_DISABLEWAKEUP_SERVICE_ID        0x0au
#define GPT_ENABLEWAKEUP_SERVICE_ID         0x0bu
#define GPT_CHECKWAKEUP_SERVICE_ID          0x0cu


/** Channel time value type */
/** @req SWS_Gpt_00359 */
#if defined(CFG_ZYNQ)
typedef uint16 Gpt_ValueType;
#else
typedef uint32 Gpt_ValueType;
#endif

/** Channel behavior */
typedef enum {
  GPT_CH_MODE_ONESHOT=0,
  GPT_CH_MODE_CONTINUOUS
} Gpt_ChannelMode;


/** @req SWS_Gpt_00360 */
typedef enum {
  GPT_MODE_NORMAL=0,
  GPT_MODE_SLEEP,
  GPT_MODE_UNINTIALIZED
} Gpt_ModeType;

/** Channel id type */
/** @req SWS_Gpt_00358 */
typedef uint8 Gpt_ChannelType;

/* Needs Gpt_ConfigType */
#include "Gpt_Cfg.h"		/* @req 4.0.3/GPT259 */

/* Some time convert macros */
#define GPT_ARC_US2TICKS(_us, _timer_freq)  	(((_us) * (_timer_freq/1000))/1000uL)
#define GPT_ARC_TICKS2US(_ticks, _timer_freq)  	((_ticks) / (_timer_freq/1000000uL))

/* The config needs EcuM_WakeupSourceType from EcuM */

#if (GPT_VERSION_INFO_API == STD_ON)
/* @req SWS_Gpt_00279 */
void Gpt_GetVersionInfo( Std_VersionInfoType* versioninfo);
#endif

/* @req SWS_Gpt_00280 */
void Gpt_Init( const Gpt_ConfigType * ConfigPtr);

#if GPT_DEINIT_API == STD_ON
/* @req SWS_Gpt_00281 */
/* @req SWS_Gpt_00194 */
void Gpt_DeInit( void );
#endif

#if ( GPT_TIME_ELAPSED_API == STD_ON )
/* @req SWS_Gpt_00282 */
/* @req SWS_Gpt_00195 */
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType channel);
#endif

#if ( GPT_TIME_REMAINING_API == STD_ON )
/* @req SWS_Gpt_00283 */
/* @req SWS_Gpt_00196 */
Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType channel );
#endif


/* @req SWS_Gpt_00284 */
void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value);

/* @req SWS_Gpt_00285 */
void Gpt_StopTimer(Gpt_ChannelType Channel);

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )

/* @req SWS_Gpt_00286 */
/* @req SWS_Gpt_00199 */
void Gpt_EnableNotification( Gpt_ChannelType Channel);

/* @req SWS_Gpt_00287 */
/* @req SWS_Gpt_00200 */
void Gpt_DisableNotification( Gpt_ChannelType Channel);
#endif

#if ( GPT_WAKEUP_FUNCTIONALITY_API == STD_ON ) && (defined(CFG_ZYNQ) || defined(CFG_JAC5) ||  defined(CFG_JAC5E) || defined(CFG_JAC6))
/* @req:ZYNQ SWS_Gpt_00288 */
/* @req:ZYNQ SWS_Gpt_00201 */
/* @req:ZYNQ SWS_Gpt_00255 */
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON )
void Gpt_SetMode( Gpt_ModeType Mode );


/* @req:ZYNQ SWS_Gpt_00289 */
/* @req:ZYNQ SWS_Gpt_00202 */
void Gpt_DisableWakeup( Gpt_ChannelType Channel );

/* @req:ZYNQ SWS_Gpt_00290 */
/* @req:ZYNQ SWS_Gpt_00203 */
void Gpt_EnableWakeup( Gpt_ChannelType Channel );


/* @req:ZYNQ SWS_Gpt_00328 */
/* @req:ZYNQ SWS_Gpt_00324 */
void Gpt_CheckWakeup( EcuM_WakeupSourceType WakeupSource );
#endif
#endif

/* @req SWS_Gpt_00292  */
extern void Gpt_Notification_0( void );
extern void Gpt_Notification_1( void );
extern void Gpt_Notification_2( void );
extern void Gpt_Notification_3( void );

/* Arc defined functions */

/**
 * Get the frequency in Hz for a particular channel.
 * Used to calculate how long a "tick" is.
 * Must not be called before Gpt_Init (the value will not be valid).
 *
 * @param Channel
 * @return The frequency in Hz
 */
uint32 Gpt_Arc_GetClock(Gpt_ChannelType Channel);


#endif /*GPT_H_*/
/** @} */
