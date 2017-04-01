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
/** @tagSettings DEFAULT_ARCHITECTURE=RH850F1H|ZYNQ|JACINTO6|MPC5748G|MPC5747C */

#ifndef ETH_GENERALTYPES_H_
#define ETH_GENERALTYPES_H_

#include "ComStack_Types.h"
#if 0 /*  Deviation,in order not to create dependency with general types and non ASR modules ,
          Eth_GeneralTypes.h is also included in other modules such as ETHSM */
#include "Eth_Cfg.h"
#endif

#if defined(USE_DEM) || defined(CFG_ETH_USE_DEM)
#include "Dem.h"
#endif

/* @req 4.1.2/SWS_Eth_00149 *//* @req 4.2.2/SWS_Eth_00149 */

typedef struct {
    uint16          EthCtrlRxBufLenByte;
    uint16          EthCtrlTxBufLenByte;
    uint16          EthRxBufTotal;
    uint16          EthTxBufTotal;
    uint8           EthHwUnit;
    boolean         EthCtrlEnableMii;
    boolean         EthCtrlEnableRxInterrupt;
    boolean         EthCtrlEnableTxInterrupt;
    uint8           EthCtrlPhyAddress[6];
#if defined (CFG_ZYNQ) || defined(CFG_JAC6) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
    uint8           EthCtrlIdx;
    uint8           EthHwSpeed;
#if !defined (CFG_ZYNQ)
    uint8           EthMIIMode; /* Not required for Zynq */
#endif
    boolean         EthHwEnableRxChecksumOffload;
    boolean         EthHwEnableTxChecksumOffload;
#if defined(CFG_JAC6)
    uint8           EthHwTxDmaCh;
    uint8           EthHwRxDmaCh;
    uint8           EthHwTxQueue;
    uint8           EthHwRxQueue;
    uint8           EthHwFifoPrio;
    boolean         EthHwEnableCircDesc;
#endif
#if defined (CFG_ZYNQ) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
    boolean         EthHwCtrlDiscardRxFCS;
#endif
#endif
#if defined(USE_DEM) || defined(CFG_ETH_USE_DEM)
    Dem_EventIdType ETH_E_ACCESS;
#if defined(CFG_JAC6) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
    Dem_EventIdType ETH_E_RX_FRAMES_LOST;
#endif
#endif
}Eth_ControllerConfigType;

typedef struct {
    const Eth_ControllerConfigType *Controllers;
    uint8 NofControllers;
}Eth_ConfigSetType;

/* @req 4.1.2/SWS_Eth_00156 *//* @req 4.2.2/SWS_Eth_00156 */
typedef struct {
    const Eth_ConfigSetType *ConfigSet;
}Eth_ConfigType;

/* @req 4.1.2/SWS_Eth_00157 *//* @req 4.2.2/SWS_Eth_00157 */
typedef enum {
    ETH_OK,
    ETH_E_NOT_OK,
    ETH_E_NO_ACCESS
}Eth_ReturnType;

/* @req 4.1.2/SWS_Eth_00158 *//* @req 4.2.2/SWS_Eth_00158 */
typedef enum {
    ETH_MODE_DOWN,
    ETH_MODE_ACTIVE
}Eth_ModeType;

#if !defined(CFG_AURIX)
/* @req 4.1.2/SWS_Eth_00159 *//* @req 4.2.2/SWS_Eth_00159 */
typedef enum {
    ETH_STATE_UNINIT,
    ETH_STATE_INIT,
    ETH_STATE_ACTIVE
}Eth_StateType;
#endif
/* @req 4.1.2/SWS_Eth_00160 *//* @req 4.2.2/SWS_Eth_00160 */
typedef uint16 Eth_FrameType;

/* @req 4.1.2/SWS_Eth_00161 *//* @req 4.2.2/SWS_Eth_00161 */
typedef uint8 Eth_DataType; /* Depends on the CPU used - 8/16/32 bit */

/* @req 4.1.2/SWS_Eth_00162 *//* @req 4.2.2/SWS_Eth_00162 */
typedef enum {
     ETH_RECEIVED
    ,ETH_NOT_RECEIVED
    ,ETH_RECEIVED_MORE_DATA_AVAILABLE
    ,ETH_RECEIVED_FRAMES_LOST /* not available in 4.2.2 version on */
}Eth_RxStatusType;

/* @req 4.1.2/SWS_Eth_00163 *//* @req 4.2.2/SWS_Eth_00163 */
typedef enum {
    ETH_ADD_TO_FILTER,
    ETH_REMOVE_FROM_FILTER
}Eth_FilterActionType;

/* @req 4.2.2/SWS_Eth_00177 */
typedef enum{
    ETH_VALID,
    ETH_INVALID,
    ETH_UNCERTAIN,
}Eth_TimeStampQualType;

/* @req 4.2.2/SWS_Eth_00178 */
typedef struct __attribute__ ((packed)) {
    uint16 secondsHi;
    uint32 seconds;
    uint32 nanoseconds;
}Eth_TimeStampType;

/* @req 4.2.2/SWS_Eth_00179 */
typedef struct{
    Eth_TimeStampType diff;
    boolean sign;
}Eth_TimeIntDiffType;

/* @req 4.2.2/SWS_Eth_00180 */
typedef struct {
    Eth_TimeIntDiffType IngressTimeStampDelta;
    Eth_TimeIntDiffType OriginTimeStampDelta;
}Eth_RateRatioType;

/* Eth Tranceiver types */
/* @req 4.2.2/SWS_EthTrcv_00099 */
typedef enum{
    ETHTRCV_MODE_DOWN,
    ETHTRCV_MODE_ACTIVE,
}EthTrcv_ModeType;

/* @req 4.2.2/SWS_EthTrcv_00100 */
typedef enum{
    ETHTRCV_LINK_STATE_DOWN,
    ETHTRCV_LINK_STATE_ACTIVE,
}EthTrcv_LinkStateType;

/* @req 4.2.2/SWS_EthTrcv_00101 */
typedef enum{
    ETHTRCV_STATE_UNINIT,
    ETHTRCV_STATE_INIT,
}EthTrcv_StateType;

/* @req 4.2.2/SWS_EthTrcv_00102 */
typedef enum{
    ETHTRCV_BAUD_RATE_10MBIT,
    ETHTRCV_BAUD_RATE_100MBIT,
}EthTrcv_BaudRateType;

/* @req 4.2.2/SWS_EthTrcv_00103 */
typedef enum{
    ETHTRCV_DUPLEX_MODE_HALF,
    ETHTRCV_DUPLEX_MODE_FULL,
}EthTrcv_DuplexModeType;

/* @req 4.2.2/SWS_EthTrcv_00113 */
/* @req 4.2.2/SWS_Eth_00175 */
typedef uint32 Eth_BufIdxType;

/* @req 4.2.2/SWS_EthTrcv_00113 */
typedef enum {
    ETHTRCV_WUM_DISABLE,
    ETHTRCV_WUM_ENABLE,
    ETHTRCV_WUM_CLEAR,
}EthTrcv_WakeupModeType;

/* @req 4.2.2/SWS_EthTrcv_00114 */
typedef enum {
    ETHTRCV_WUR_NONE,
    ETHTRCV_WUR_GENERAL,
    ETHTRCV_WUR_BUS,
    ETHTRCV_WUR_INTERNAL,
    ETHTRCV_WUR_RESET,
    ETHTRCV_WUR_POWER_ON,
    ETHTRCV_WUR_PIN,
    ETHTRCV_WUR_SYSERR,
}EthTrcv_WakeupReasonType;

/* @req 4.2.2/SWS_EthSwt_00123 */
typedef enum {
    ETHSWT_STATE_UNINIT,
    ETHSWT_STATE_INIT,
    ETHSWT_STATE_ACTIVE,
}EthSwt_StateType;

/* @req 4.2.2/SWS_EthSwt_00110 */
typedef struct {
    uint8 MacAddr;
    uint16 VlanId;
    uint8 SwitchPort;
}EthSwt_MacVlanType;

/* @req 4.2.2/SWS_EthSwt_00227 */
typedef enum {
    ETHSWT_MACLEARNING_HWDISABLED,
    ETHSWT_MACLEARNING_HWENABLED,
    ETHSWT_MACLEARNING_SWENABLED,
}EthSwt_MacLearningType;

#endif /* ETH_GENERALTYPES_H_ */
