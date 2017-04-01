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

/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.0.3 */
/** @tagSettings DEFAULT_ARCHITECTURE=RH850F1H|ZYNQ|JACINTO6|MPC5748G|MPC5747C  */
/* @req 4.2.2/SWS_Eth_00011 */ /* None of the Ethernet Driver module header files shall define global variables */
#ifndef ETH_H_
#define ETH_H_

#define ETH_VENDOR_ID                 60u
#define ETH_MODULE_ID                 88u
#if defined(CFG_RH850)
/* @req 4.0.3/ETH006 */
#define ETH_AR_RELEASE_MAJOR_VERSION    4u
#define ETH_AR_RELEASE_MINOR_VERSION    0u
#define ETH_AR_RELEASE_PATCH_VERSION    3u
#elif defined (CFG_BRD_ZYNQ_ZC702)
/* @req 4.1.2/SWS_Eth_00006 */
#define ETH_AR_RELEASE_MAJOR_VERSION    4u
#define ETH_AR_RELEASE_MINOR_VERSION    1u
#define ETH_AR_RELEASE_PATCH_VERSION    2u
#else
/* @req 4.2.2/SWS_Eth_00006 */
#define ETH_AR_RELEASE_MAJOR_VERSION    4u
#define ETH_AR_RELEASE_MINOR_VERSION    2u
#define ETH_AR_RELEASE_PATCH_VERSION    2u
#endif

#define ETH_SW_MAJOR_VERSION            1u
#define ETH_SW_MINOR_VERSION            0u
#define ETH_SW_PATCH_VERSION            0u

#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
/* Development errors */
/* @req 4.1.2/SWS_Eth_00016 *//* @req 4.0.3/ETH016 */
#define ETH_E_INV_CTRL_IDX          0x01u
#define ETH_E_NOT_INITIALIZED       0x02u
#define ETH_E_INV_POINTER           0x03u
#define ETH_E_INV_PARAM             0x04u
#define ETH_E_INV_CONFIG            0x05u
#define ETH_E_INV_MODE              0x06u
#define ETH_E_FRAMES_LOST           0x07u
#else
/* Default errors */
/* @req 4.2.2/SWS_Eth_00016 */
#define ETH_E_INV_CTRL_IDX          0x01u
#define ETH_E_NOT_INITIALIZED       0x02u
#define ETH_E_PARM_POINTER          0x03u
#define ETH_E_INV_PARAM             0x04u
#define ETH_E_INV_MODE              0x05u
#endif

/* ArcCore extra development errors */
#define ETH_E_READ_MII_FAIL         0x10u
#define ETH_E_WRITE_MII_FAIL        0x11u
#define ETH_E_MII_NOT_ENABLED       0x12u
#define ETH_E_CONFIG_INVALID        0x13u
#define ETH_E_GENERAL_ERROR         0x14u

/* API ids */
#define ETH_INIT_ID                 0x01u
#define ETH_CONTROLLERINIT_ID       0x02u
#define ETH_SETCONTROLLERMODE_ID    0x03u
#define ETH_GETCONTROLLERMODE_ID    0x04u
#define ETH_WRITEMII_ID             0x05u
#define ETH_READMII_ID              0x06u
#define ETH_GETPHYSADDR_ID          0x08u
#define ETH_PROVIDETXBUFFER_ID      0x09u
#define ETH_TRANSMIT_ID             0x0Au
#define ETH_RECEIVE_ID              0x0Bu
#define ETH_TXCONFIRMATION_ID       0x0Cu
#define ETH_GETVERSIONINFO_ID       0x0Du
#define ETH_UPDATEPHYSADDRFILTER_ID 0x12u
#define ETH_SETPHYSADDR_ID          0x13u
/* ArcCore extra API ids */
#define ETH_GLOBAL_ID               0x20u

/* @req 4.1.2/SWS_Eth_00148 *//* @req 4.2.2/SWS_Eth_00148 */
#include "Eth_GeneralTypes.h"
#include "Eth_Cfg.h" /* Deviation in inclusion of this file, in order not to create dependency with general types
                       and non ASR Ethernet modules  */
#if defined(CFG_ETH_ARC_STATISTICS)
typedef struct {
	uint64 TxIcmp;
	uint64 RxIcmp;
    uint32 TxInterptCnt;
    uint32 RxInterptCnt;
    uint32 RxPktOverrun;
}Eth_Arc_StatisticsType;

Std_ReturnType Eth_Arc_GetStatistics(Eth_Arc_StatisticsType *stats);
void Eth_Arc_ResetStatistics(void);
#endif

void Eth_Init(const Eth_ConfigType* CfgPtr);
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
Std_ReturnType Eth_ControllerInit(uint8 CtrlIdx, uint8 CfgIdx);
#endif
#if (ETH_MII_API == STD_ON)
#if defined(CFG_RH850)
void Eth_WriteMii(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal);
void Eth_ReadMii(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16* RegValPtr);
#else
Eth_ReturnType Eth_WriteMii(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal);
Eth_ReturnType Eth_ReadMii(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16* RegValPtr);
#endif
#endif
Std_ReturnType Eth_SetControllerMode(uint8 CtrlIdx, Eth_ModeType CtrlMode);
Std_ReturnType Eth_GetControllerMode(uint8 CtrlIdx, Eth_ModeType* CtrlModePtr);
void Eth_GetPhysAddr(uint8 CtrlIdx, uint8* PhysAddrPtr);
void Eth_SetPhysAddr(uint8 CtrlIdx, const uint8* PhysAddrPtr);
#if (ETH_PHYS_ADRS_FILTER_API == STD_ON)
Std_ReturnType Eth_UpdatePhysAddrFilter(uint8 CtrlIdx,  const uint8* PhysAddrPtr,Eth_FilterActionType Action);
#endif
BufReq_ReturnType Eth_ProvideTxBuffer(uint8 CtrlIdx, Eth_BufIdxType* BufIdxPtr, uint8** BufPtr, uint16* LenBytePtr);
Std_ReturnType Eth_Transmit(uint8 CtrlIdx, Eth_BufIdxType BufIdx, Eth_FrameType FrameType, boolean TxConfirmation, uint16 LenByte, const uint8* PhysAddrPtr);
void Eth_TxConfirmation(uint8 CtrlIdx);
#if defined(CFG_RH850)
void Eth_Receive(uint8 CtrlIdx);
#else
void Eth_Receive(uint8 CtrlIdx,Eth_RxStatusType* RxStatusPtr);
#endif
#if (ETH_VERSION_INFO_API == STD_ON)
void Eth_GetVersionInfo(Std_VersionInfoType* VersionInfoPtr);
#endif
#if !defined(CFG_RH850) && !defined(CFG_BRD_ZYNQ_ZC702)
void Eth_MainFunction (void);
#endif

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
/* @req:AURIX 4.2.2/SWS_Eth_00181 */
extern Std_ReturnType Eth_GetCurrentTime(uint8 CtrlIdx, Eth_TimeStampQualType* timeQualPtr,
                             Eth_TimeStampType* timeStampPtr);
/* @req:AURIX 4.2.2/SWS_Eth_00186 */
extern void Eth_EnableEgressTimeStamp(uint8 CtrlIdx, Eth_BufIdxType BufIdx);
/* @req:AURIX 4.2.2/SWS_Eth_00190 */
extern void Eth_GetEgressTimeStamp(uint8 CtrlIdx, Eth_BufIdxType BufIdx,
                             Eth_TimeStampQualType* timeQualPtr, Eth_TimeStampType* timeStampPtr);
/* @req:AURIX 4.2.2/SWS_Eth_00195 */
extern void Eth_GetIngressTimeStamp(uint8 CtrlIdx, Eth_DataType* DataPtr,
                             Eth_TimeStampQualType* timeQualPtr, Eth_TimeStampType* timeStampPtr);
/* @req:AURIX 4.2.2/SWS_Eth_00200 */
extern void Eth_SetCorrectionTime(uint8 CtrlIdx, const Eth_TimeIntDiffType* timeOffsetPtr,
                             const Eth_RateRatioType* rateRatioPtr);
/* @req:AURIX 4.2.2/SWS_Eth_00205 */
extern Std_ReturnType Eth_SetGlobalTime(uint8 CtrlIdx, const Eth_TimeStampType* timeStampPtr);
#endif

#endif /* ETH_H_ */
