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


#ifndef WDGM_H
#define WDGM_H

#include "Std_Types.h"

#define WDGM_AR_RELEASE_MAJOR_VERSION   	4u
#define WDGM_AR_RELEASE_MINOR_VERSION   	0u
#define WDGM_AR_RELEASE_REVISION_VERSION    3u

#define WDGM_VENDOR_ID          60u
#define WDGM_MODULE_ID          MODULE_ID_WDGM
#define WDGM_AR_MAJOR_VERSION   WDGM_AR_RELEASE_MAJOR_VERSION
#define WDGM_AR_MINOR_VERSION   WDGM_AR_RELEASE_MINOR_VERSION
#define WDGM_AR_PATCH_VERSION   WDGM_AR_RELEASE_REVISION_VERSION

#define WDGM_SW_MAJOR_VERSION   2u
#define WDGM_SW_MINOR_VERSION   0u
#define WDGM_SW_PATCH_VERSION   0u


/* globally fulfilled requirements */
/** @req WDGM038 */
/** @req WDGM047 */
/** @req WDGM260 */
/** @req WDGM015 */
/** @req WDGM048 */
/** @req WDGM200 */
/** @req WDGM085 */
/** @req WDGM293 */
/** @req WDGM267 */
/** @req WDGM127 */
/** !req WDGM014.partially */

#define WDGM_SID_INIT					0x00u
#define WDGM_SID_DEINIT					0x01u
#define WDGM_SID_GETVERSIONINFO 		0x02u
#define WDGM_SID_SETMODE				0x03u
#define WDGM_SID_GETMODE				0x0Bu
#define WDGM_SID_CHECKPOINTREACHED 		0x0Eu
#define WDGM_SID_UPDATEALIVECOUNTER		0x04u
#define WDGM_SID_GETLOCALSTATUS			0x0Cu
#define WDGM_SID_GETGLOBALSTATUS		0x0Du
#define WDGM_SID_PERFORMRESET			0x0Fu
#define WDGM_SID_GETFIRSTEXPIREDSEID	0x10u
#define WDGM_SID_MAINFUNCTION			0x08u

/** @req WDGM259 */
/** @req WDGM004 */
#define WDGM_E_NO_INIT					0x10u
#define WDGM_E_PARAM_CONFIG				0x11u
#define WDGM_E_PARAM_MODE				0x12u
#define WDGM_E_PARAM_SEID				0x13u
#define WDGM_E_INV_POINTER				0x14u
#define WDGM_E_DISABLE_NOT_ALLOWED		0x15u
#define WDGM_E_CPID						0x16u
#define WDGM_E_DEPRECATED				0x17u
#define WDGM_E_SEDEACTIVATED			0x19u
#define WDGM_E_AMBIGIOUS				0x18u

/* the following datatypes are defined globally in order to allow debugging as mentioned in the spec */
#include "WdgM_ConfigTypes.h"
#include "WdgM_internalTypes.h"
/** @req WDGM002 */
/** @req WDGM011 */
/** @req WDGM038 */
/** !req WDGM161 *//* Os interfaces not used */
/** !req WDGM162 *//* Os interface not used and resetting partition not supported */

/** @req WDGM151 */
void WdgM_Init(const WdgM_ConfigType *ConfigPtr);

/** @req WDGM261 */
void WdgM_DeInit( void );

/** @req WDGM153 */
/** @req WDGM262 */
/** @req WDGM110 */
#if ( WDGM_VERSION_INFO_API == STD_ON )
#define WdgM_GetVersionInfo(_vi) STD_GET_VERSION_INFO(_vi,WDGM)
#endif


/** @req WDGM154 */
Std_ReturnType WdgM_SetMode( WdgM_ModeType Mode, uint16 CallerID);

/** @req WDGM168 */
Std_ReturnType WdgM_GetMode( WdgM_ModeType *Mode);

/** @req WDGM263 */
Std_ReturnType WdgM_CheckpointReached( WdgM_SupervisedEntityIdType SEID, WdgM_CheckpointIdType CheckpointID);

/** @req WDGM155 */
Std_ReturnType WdgM_UpdateAliveCounter( WdgM_SupervisedEntityIdType SEID);

/** @req WDGM169 */
Std_ReturnType WdgM_GetLocalStatus( WdgM_SupervisedEntityIdType SEID, WdgM_LocalStatusType *Status);

/** @req WDGM175 */
Std_ReturnType WdgM_GetGlobalStatus( WdgM_GlobalStatusType *Status);

/** @req WDGM264 */
void WdgM_PerformReset( void );

/** @req WDGM346 */
Std_ReturnType WdgM_GetFirstExpiredSEID( WdgM_SupervisedEntityIdType *SEID);

/** @req WDGM159 */
void WdgM_MainFunction( void );

#if (WDGM_OFF_MODE_ENABLED != STD_OFF)
boolean WdgM_internal_isAtLeastOneWdogEnabled(WdgM_ModeType Mode, uint8 SID, uint8 errID);
#endif

#if (WDGM_DEFENSIVE_BEHAVIOR == STD_ON)
boolean WdgM_internal_isAllowedForCalling(uint16 CallerID);
#endif




#endif
