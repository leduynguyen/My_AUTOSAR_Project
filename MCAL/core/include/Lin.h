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

/** @addtogroup Lin LIN Driver
 *  @{ */

/** @file Lin.h
 * API and type definitions for LIN Driver.
 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */
/** @tagSettings DEFAULT_ARCHITECTURE=PPC|MPC5645S|MPC5607B|ZYNQ|JACINTO6|MPC5748G */

#ifndef LIN_H_
#define LIN_H_

#define LIN_MODULE_ID            82u
#define LIN_VENDOR_ID            60u

#define LIN_SW_MAJOR_VERSION            2u
#define LIN_SW_MINOR_VERSION   	        1u
#define LIN_SW_PATCH_VERSION            1u
#define LIN_AR_RELEASE_MAJOR_VERSION    4u
#define LIN_AR_RELEASE_MINOR_VERSION    1u
#define LIN_AR_RELEASE_PATCH_VERSION    2u

#include "Std_Types.h"
/* @req SWS_Lin_00241 */
#include "Lin_GeneralTypes.h"
#include "Lin_Cfg.h"
/* @req SWS_Lin_00205 */
#include "ComStack_Types.h"

/* @req SWS_Lin_00247 */
#include "Lin_ConfigTypes.h"

#if (LIN_VERSION_INFO_API == STD_ON)
void Lin_GetVersionInfo( Std_VersionInfoType *versionInfo );
#endif
/** General requirements tagging */
/* @req SWS_Lin_00226 */
/* @req SWS_Lin_00054 */
/* @req SWS_Lin_00064 */
/* @req SWS_Lin_00075 */

typedef enum {
    LIN_UNINIT,
    LIN_INIT,
}Lin_DriverStatusType;

/** @name Service id's */
//@{
#define LIN_INIT_SERVICE_ID               0x00u
#define LIN_GETVERSIONINFO_SERVICE_ID     0x01u
#define LIN_WAKEUPVALIDATION_SERVICE_ID   0x0Au
#define LIN_INIT_CHANNEL_SERVICE_ID       0x02u
#define LIN_DEINIT_CHANNEL_SERVICE_ID     0x03u
#define LIN_SEND_FRAME_SERVICE_ID         0x04u
#define LIN_SEND_RESPONSE_SERVICE_ID      0x05u
#define LIN_GO_TO_SLEEP_SERVICE_ID        0x06u
#define LIN_WAKE_UP_SERVICE_ID            0x07u
#define LIN_GETSTATUS_SERVICE_ID          0x08u
#define LIN_GO_TO_SLEEP_INTERNAL_SERVICE_ID 0x09u
#define LIN_CHECKWAKEUP_SERVICE_ID        0x0Au
#define LIN_WAKE_UP_INTERNAL_SERVICE_ID   0x0Bu

#define LIN_ARC_DEINIT_SERVICE_ID         0xA0u
//@}

/* @req SWS_Lin_00048 */
/** @name Error Codes */
//@{

#define LIN_E_UNINIT                    0x00u
#define LIN_E_INVALID_CHANNEL			0x02u
#define LIN_E_INVALID_POINTER			0x03u
#define LIN_E_PARAM_POINTER             0x05u
#define LIN_E_STATE_TRANSITION			0x04u
#define LIN_E_INVALID_CONFIG            0x10u

//@}


/** @req SWS_Lin_00006 */
void Lin_Init( const Lin_ConfigType* Config );

void Lin_Arc_DeInit(void);

/** @req SWS_Lin_00191 */
Std_ReturnType Lin_SendFrame(  uint8 Channel,  Lin_PduType* PduInfoPtr );
/**@req SWS_Lin_00166 */
Std_ReturnType Lin_GoToSleep(  uint8 Channel );
/** @req SWS_Lin_00167 */
Std_ReturnType Lin_GoToSleepInternal(  uint8 Channel );
/** @req SWS_Lin_00169 */
Std_ReturnType Lin_Wakeup( uint8 Channel );
/** @req SWS_Lin_00168 */
Lin_StatusType Lin_GetStatus( uint8 Channel, uint8** Lin_SduPtr );
/** @req SWS_Lin_00256 */
Std_ReturnType   Lin_WakeupInternal( uint8 Channel );
/** @req:ZYNQ SWS_Lin_00160 */
Std_ReturnType Lin_CheckWakeup(uint8 Channel);

#endif
/** @} */

