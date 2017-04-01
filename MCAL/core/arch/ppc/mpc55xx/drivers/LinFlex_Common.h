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

#ifndef LINFLEX_COMMON_H_
#define LINFLEX_COMMON_H_

#include "mpc55xx.h"
#include "Lin.h"

#if defined(USE_CDD_LINSLV)
#include "CDD_LinSlv.h"
#endif

typedef enum {
    LIN_MASTER = 0,
    LIN_SLAVE
}LinFlex_ModeType;

Std_ReturnType LinFlex_Common_Init(const Lin_ChannelConfigType *channelCfg, LinFlex_ModeType mode);
void LinFlex_Common_DeInit(const Lin_ChannelConfigType *channelCfg);
void LinFlex_Common_GoToSleepInternal(const Lin_ChannelConfigType *channelCfg);
void LinFlex_Common_WakeupInternal(const Lin_ChannelConfigType *channelCfg);
Std_ReturnType LinFlex_Common_Wakeup(const Lin_ChannelConfigType *channelCfg);
boolean LinFlex_Common_IsWakeUpSet(const Lin_ChannelConfigType *channelCfg);
Lin_StatusType LinFlex_Common_GetPeripheralStatus(const Lin_ChannelConfigType *channelCfg);
Std_ReturnType LinFlex_Common_WriteHwRegToDataBuf(uint8 *buf, const volatile struct LINFLEX_tag * LINFLEXHw);
Std_ReturnType LinFlex_Common_WriteDataBufToHwReg(uint8 length, const uint8 *buf, volatile struct LINFLEX_tag * LINFLEXHw);

#if defined(USE_CDD_LINSLV)
Std_ReturnType LinFlex_Common_SetupSlvFilter(const Lin_ChannelConfigType *channelCfg, const LinSlv_FrameSetupType *LinSlvFrameSetupConfigData);
#endif

#endif /* LINFLEX_COMMON_H_ */





