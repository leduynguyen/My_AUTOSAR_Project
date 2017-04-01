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

#ifndef ETH_INTERNAL_H_
#define ETH_INTERNAL_H_

#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
void Eth_Hw_Init(const Eth_ConfigType* CfgPtr);
#else
Std_ReturnType Eth_Hw_Init(const Eth_ConfigType *CfgPtr);
#endif
Std_ReturnType Eth_Hw_ControllerInit(const Eth_ControllerConfigType *CtrlCfgPtr, uint8 CtrlIdx);
Std_ReturnType Eth_Hw_WriteMii(const Eth_ControllerConfigType *CtrlCfgPtr, uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal);
Std_ReturnType Eth_Hw_ReadMii(const Eth_ControllerConfigType *CtrlCfgPtr, uint8 TrcvIdx, uint8 RegIdx, uint16 *RegValPtr);
Std_ReturnType Eth_Hw_SetControllerMode(const Eth_ControllerConfigType *CtrlCfgPtr, uint8 CtrlIdx, Eth_ModeType CtrlMode);
void Eth_Hw_GetPhysAddr(const Eth_ControllerConfigType *CtrlCfgPtr, uint8* PhysAddrPtr);
void Eth_Hw_SetPhysAddr(const Eth_ControllerConfigType *CtrlCfgPtr, const uint8* PhysAddrPtr);
Std_ReturnType Eth_Hw_UpdatePhysAddrFilter(const Eth_ControllerConfigType *CtrlCfgPtr, const uint8* PhysAddrPtr,Eth_FilterActionType Action);
BufReq_ReturnType Eth_Hw_ProvideTxBuffer(const Eth_ControllerConfigType *CtrlCfgPtr, Eth_BufIdxType* BufIdxPtr, Eth_DataType** BufPtr, uint16* LenBytePtr);
Std_ReturnType Eth_Hw_Transmit(const Eth_ControllerConfigType *CtrlCfgPtr, Eth_BufIdxType BufIdx, Eth_FrameType FrameType, boolean TxConfirmation, uint16 LenByte, const uint8* PhysAddrPtr);
void Eth_Hw_TxConfirmation(uint8 CtrlIdx);
#if defined(CFG_RH850)
void Eth_Hw_Receive(uint8  CtrlIdx);
#else
void Eth_Hw_Receive(uint8  CtrlIdx,Eth_RxStatusType* RxStatusPtr);
#endif

#endif /* ETH_INTERNAL_H_ */
