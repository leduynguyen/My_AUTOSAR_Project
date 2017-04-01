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
/** @tagSettings DEFAULT_ARCHITECTURE=RH850F1H|ZYNQ|JACINTO6|MPC5748G|MPC5747C */

/* General requirements */
/* @req 4.0.3/ETH001 */
/* @req 4.0.3/ETH003 *//* @req 4.1.2/SWS_Eth_00003 */ /* @req 4.2.2/SWS_Eth_00003 */ /*The Ethernet Driver is using a zero-based index to abstract the access for upper software layers */
/* @req 4.0.3/ETH004 *//* @req 4.1.2/SWS_Eth_00004 */ /* @req 4.2.2/SWS_Eth_00004 */ /*buffer index (BufIdx) indentifies an Ethernet buffer processed by Ethernet Driver API functions.*/
/* @req 4.0.3/ETH010 */
/* @req 4.0.3/ETH015 */
/* @req 4.0.3/ETH026 *//* @req 4.1.2/SWS_Eth_00026 */ /* @req 4.2.2/SWS_Eth_00026 */ /* requirement for Imported types */
#include "Eth.h"
#include "EthIf_Cbk.h"
#include "Eth_Internal.h"
#if defined(USE_DEM) || defined(CFG_ETH_USE_DEM)
/* @req 4.0.3/ETH002 */
#include "Dem.h"
#endif

#if ( ETH_DEV_ERROR_DETECT == STD_ON )
/* @req 4.0.3/ETH008 *//* @req 4.1.2/SWS_Eth_00008 */ /* @req 4.2.2/SWS_Eth_00008 */ /* Default / DET error check if enabled */
/* @req 4.0.3/ETH017 */
/* @req 4.0.3/ETH018 */
/* @req 4.0.3/ETH020 */
#if defined(USE_DET)
#include "Det.h"
#else
#error "Eth: Det must be used when dev error detect is enabled"
#endif
/* @req 4.1.2/SWS_Eth_00120 *//* @req 4.2.2/SWS_Eth_00120 *//* @req 4.0.3/ETH120 */
#define VALIDATE_RV(_exp,_api,_err,_rv) \
        if( !(_exp) ) { \
          (void)Det_ReportError(ETH_MODULE_ID,0,(_api),(_err)); \
          return (_rv); \
        }

#define VALIDATE_NO_RV(_exp,_api,_err) \
        if( !(_exp) ) { \
          (void)Det_ReportError(ETH_MODULE_ID,0,(_api),(_err)); \
          return; \
        }
#define DET_REPORT_ERROR(_api,_err) (void)Det_ReportError(ETH_MODULE_ID,0,(_api),(_err))
#else
#define VALIDATE_RV(_exp,_api,_err,_rv)  \
         if( !(_exp) ) { \
             return (_rv); \
         }
#define VALIDATE_NO_RV(_exp,_api,_err)   \
         if( !(_exp) ) { \
           return; \
         }
#define DET_REPORT_ERROR(_api,_err)
#endif

#ifndef DEM_EVENT_ID_NULL
#define DEM_EVENT_ID_NULL    0u
#endif

typedef struct {
    const Eth_ConfigType* Config;
    boolean InitRun;
    Eth_StateType ControllerState[ETH_NOF_CONFIG_CTRL];
    Eth_ModeType ControllerMode[ETH_NOF_CONFIG_CTRL];
}EthInternalType;/*lint !e9038 Allow flexible member */

static EthInternalType EthGlobal = {.InitRun = FALSE, .Config = NULL, .ControllerState = {ETH_STATE_UNINIT}, .ControllerMode = {ETH_MODE_DOWN} };
/*lint -save -e904 -e9027 */ /*Return statement before end of function - OK
 *                             Unpermitted operand to operator '! - OK */
/**
 * Initializes the Ethernet Driver
 * @param CfgPtr
 */
/* @req 4.1.2/SWS_Eth_00027 *//* @req 4.2.2/SWS_Eth_00027 *//* @req 4.0.3/ETH027 */
void Eth_Init(const Eth_ConfigType* CfgPtr)
{
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
	/* @req 4.1.2/SWS_Eth_00030 *//* @req 4.0.3/ETH030 */
    VALIDATE_NO_RV((NULL != CfgPtr), ETH_INIT_ID, ETH_E_INV_POINTER);
#else
    /* No requirement, but better to check this */
    VALIDATE_NO_RV((NULL != CfgPtr), ETH_INIT_ID, ETH_E_PARM_POINTER);
#endif

#if !defined(CFG_RH850) && !defined(CFG_BRD_ZYNQ_ZC702)/* 4.2.2 req */
    const Eth_ControllerConfigType *pCtrlCfgPtr;
    for (uint8 ctrlIdx = 0u;ctrlIdx < ETH_NOF_CONFIG_CTRL; ctrlIdx++){
        pCtrlCfgPtr = &CfgPtr->ConfigSet->Controllers[ctrlIdx];
        /* @req 4.2.2/SWS_Eth_00039 */
        if(pCtrlCfgPtr == NULL){ /*lint !e774 Allow rule - Boolean within 'if' always evaluates to False */
#if defined(USE_DEM) || defined(CFG_ETH_USE_DEM)
            if(DEM_EVENT_ID_NULL != CfgPtr->ConfigSet->Controllers[ctrlIdx].ETH_E_ACCESS){
                Dem_ReportErrorStatus(CfgPtr->ConfigSet->Controllers[ctrlIdx].ETH_E_ACCESS, DEM_EVENT_STATUS_FAILED);
            }
#endif
            return;
        }else{
#if defined(USE_DEM) || defined(CFG_ETH_USE_DEM)
            if(DEM_EVENT_ID_NULL != CfgPtr->ConfigSet->Controllers[ctrlIdx].ETH_E_ACCESS){
                Dem_ReportErrorStatus(CfgPtr->ConfigSet->Controllers[ctrlIdx].ETH_E_ACCESS, DEM_EVENT_STATUS_PASSED);
            }
#endif
        }
    }
#endif
    /* Init hardware */
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
    Eth_Hw_Init(CfgPtr);
#else
    /* @req 4.2.2/SWS_Eth_00034 */
    if( Eth_Hw_Init(CfgPtr) != E_OK){
        return;
    }
#endif
    for(uint8 ctrlIndex = 0; ctrlIndex < ETH_NOF_CONFIG_CTRL; ctrlIndex++) {
        EthGlobal.ControllerMode[ctrlIndex] = ETH_MODE_DOWN;
        /* @req 4.1.2/SWS_Eth_00029 *//* @req 4.2.2/SWS_Eth_00029 *//* @req 4.0.3/ETH029 */
        EthGlobal.ControllerState[ctrlIndex] = ETH_STATE_INIT;
    }
    /* @req 4.1.2/SWS_Eth_00028 *//* @req 4.2.2/SWS_Eth_00028 *//* @req 4.0.3/ETH028 */
    EthGlobal.Config = CfgPtr;
    EthGlobal.InitRun = TRUE;
#if defined(CFG_BRD_ZYNQ_ZC702) && defined(USE_ETHIF)/* Make backward compatible with ASR version lower than 4.2.2 and use it with EthIf*/
    for(uint8 ctrlIndex = 0; ctrlIndex < ETH_NOF_CONFIG_CTRL; ctrlIndex++) {
        Eth_ControllerInit(ctrlIndex,0);
    }
#endif
}

#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
/**
 * Initializes the indexed controller
 * @param CtrlIdx
 * @param CfgIdx
 * @return E_OK: Success, E_NOT_OK: Controller could not be initialized
 */
/* @req 4.1.2/SWS_Eth_00033 *//* @req 4.0.3/ETH033 */
Std_ReturnType Eth_ControllerInit(uint8 CtrlIdx, uint8 CfgIdx)
{
    /* @req 4.1.2/SWS_Eth_00036 *//* @req 4.0.3/ETH036 */
    VALIDATE_RV(EthGlobal.InitRun, ETH_CONTROLLERINIT_ID, ETH_E_NOT_INITIALIZED, E_NOT_OK);
    /* @req 4.1.2/SWS_Eth_00037 *//* @req 4.0.3/ETH037 */
    VALIDATE_RV((CtrlIdx < ETH_NOF_CONFIG_CTRL), ETH_CONTROLLERINIT_ID, ETH_E_INV_CTRL_IDX, E_NOT_OK);
    /* @req 4.1.2/SWS_Eth_00038 *//* @req 4.0.3/ETH038 */
    VALIDATE_RV((0 == CfgIdx), ETH_CONTROLLERINIT_ID, ETH_E_INV_CONFIG, E_NOT_OK);

    /* @req 4.1.2/SWS_Eth_00034 *//* @req 4.0.3/ETH034 */
    if(E_OK == Eth_Hw_ControllerInit(&EthGlobal.Config->ConfigSet->Controllers[CtrlIdx], CtrlIdx)) {
        /* @req 4.1.2/SWS_Eth_00035 *//* @req 4.0.3/ETH035 */
        EthGlobal.ControllerState[CtrlIdx] = ETH_STATE_ACTIVE;
        EthGlobal.ControllerMode[CtrlIdx] = ETH_MODE_DOWN;
        return E_OK;
    } else {
#if defined(USE_DEM) || defined(CFG_ETH_USE_DEM)
        /* @req 4.1.2/SWS_Eth_00039 *//* @req 4.0.3/ETH039 */
        /* @req 4.0.3/ETH019 */
        /* @req 4.1.2/SWS_Eth_00154 */
        if(DEM_EVENT_ID_NULL != EthGlobal.Config->ConfigSet->Controllers[CtrlIdx].ETH_E_ACCESS) {
            /* @req 4.1.2/SWS_Eth_00021 *//* @req 4.0.3/ETH021 */
            Dem_ReportErrorStatus(EthGlobal.Config->ConfigSet->Controllers[CtrlIdx].ETH_E_ACCESS, DEM_EVENT_STATUS_FAILED);
        }
#endif
        return E_NOT_OK;
    }
}
#endif

/**
 * Enables / disables the indexed controller
 * @param CtrlIdx
 * @param CtrlMode
 * @return E_OK: Success, E_NOT_OK: Controller mode could not be changed
 */
/* @req 4.1.2/SWS_Eth_00041 *//* @req 4.2.2/SWS_Eth_00041 *//* @req 4.0.3/ETH041 */
Std_ReturnType Eth_SetControllerMode(uint8 CtrlIdx, Eth_ModeType CtrlMode)
{
    /* @req 4.1.2/SWS_Eth_00043 *//* @req 4.2.2/SWS_Eth_00043 *//* @req 4.0.3/ETH043 */
    VALIDATE_RV(EthGlobal.InitRun, ETH_SETCONTROLLERMODE_ID, ETH_E_NOT_INITIALIZED, E_NOT_OK);
    /* @req 4.1.2/SWS_Eth_00044 *//* @req 4.2.2/SWS_Eth_00044 *//* @req 4.0.3/ETH044 */
    VALIDATE_RV((CtrlIdx < ETH_NOF_CONFIG_CTRL), ETH_SETCONTROLLERMODE_ID, ETH_E_INV_CTRL_IDX, E_NOT_OK);
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
    /* @req 4.1.2/SWS_Eth_00043 *//* @req 4.0.3/ETH043 */
    VALIDATE_RV((ETH_STATE_ACTIVE == EthGlobal.ControllerState[CtrlIdx]), ETH_SETCONTROLLERMODE_ID, ETH_E_NOT_INITIALIZED, E_NOT_OK);
#endif
    /* Development req */
    VALIDATE_RV(((ETH_MODE_DOWN == CtrlMode) || (ETH_MODE_ACTIVE == CtrlMode)), ETH_SETCONTROLLERMODE_ID, ETH_E_INV_MODE, E_NOT_OK);
    /* @req 4.1.2/SWS_Eth_00042 *//* @req 4.2.2/SWS_Eth_00042 *//* @req 4.0.3/ETH042 */
    Std_ReturnType ret = Eth_Hw_SetControllerMode(&EthGlobal.Config->ConfigSet->Controllers[CtrlIdx], CtrlIdx, CtrlMode);
    if( ret == E_OK ) {
        EthGlobal.ControllerMode[CtrlIdx] = CtrlMode;
#if defined(USE_ETHIF)
        EthIf_CtrlModeIndication(CtrlIdx,CtrlMode);
#endif
    }
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702) /* 4.2.2 req */
    else {
#if defined(USE_DEM) || defined(CFG_ETH_USE_DEM)
        /* @req 4.2.2/SWS_Eth_00168 */
        /* @req 4.0.3/ETH019 */
        /* @req 4.1.2/SWS_Eth_00154 */
        /* @req 4.2.2/SWS_Eth_00173 */
        if(DEM_EVENT_ID_NULL != EthGlobal.Config->ConfigSet->Controllers[CtrlIdx].ETH_E_ACCESS) {
            /* @req 4.0.3/ETH021 */
            Dem_ReportErrorStatus(EthGlobal.Config->ConfigSet->Controllers[CtrlIdx].ETH_E_ACCESS, DEM_EVENT_STATUS_FAILED);
        }
#endif
    }
#endif

#if !defined(CFG_RH850) && !defined(CFG_BRD_ZYNQ_ZC702) /* 4.2.2 req */
    /* @req 4.2.2/SWS_Eth_00168 */
#if defined(USE_DEM) || defined(CFG_ETH_USE_DEM)
    if(DEM_EVENT_ID_NULL != EthGlobal.Config->ConfigSet->Controllers[CtrlIdx].ETH_E_ACCESS){
        if(ret != E_OK){
            Dem_ReportErrorStatus(EthGlobal.Config->ConfigSet->Controllers[CtrlIdx].ETH_E_ACCESS, DEM_EVENT_STATUS_FAILED);
        }else{
            Dem_ReportErrorStatus(EthGlobal.Config->ConfigSet->Controllers[CtrlIdx].ETH_E_ACCESS, DEM_EVENT_STATUS_PASSED);
        }
    }
#endif
#endif
    return ret;
}

/**
 * Obtains the state of the indexed controller
 * @param CtrlIdx
 * @param CtrlModePtr
 * @return E_OK: Success, E_NOT_OK: Controller mode could not be obtained
 */
/* @req 4.1.2/SWS_Eth_00046 *//* @req 4.2.2/SWS_Eth_00046 *//* @req 4.0.3/ETH046 */
Std_ReturnType Eth_GetControllerMode(uint8 CtrlIdx, Eth_ModeType* CtrlModePtr)
{
    /* @req 4.1.2/SWS_Eth_00048 *//* @req 4.2.2/SWS_Eth_00048 *//* @req 4.0.3/ETH048 */
    VALIDATE_RV(EthGlobal.InitRun, ETH_GETCONTROLLERMODE_ID, ETH_E_NOT_INITIALIZED, E_NOT_OK);
    /* @req 4.1.2/SWS_Eth_00049 *//* @req 4.2.2/SWS_Eth_00049 *//* @req 4.0.3/ETH049 */
    VALIDATE_RV((CtrlIdx < ETH_NOF_CONFIG_CTRL), ETH_GETCONTROLLERMODE_ID, ETH_E_INV_CTRL_IDX, E_NOT_OK);
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
    /* @req 4.1.2/SWS_Eth_00048 *//* @req 4.0.3/ETH048 */
    VALIDATE_RV((ETH_STATE_ACTIVE == EthGlobal.ControllerState[CtrlIdx]), ETH_GETCONTROLLERMODE_ID, ETH_E_NOT_INITIALIZED, E_NOT_OK);
    /* @req 4.1.2/SWS_Eth_00050 *//* @req 4.0.3/ETH050 */
    VALIDATE_RV((NULL != CtrlModePtr), ETH_GETCONTROLLERMODE_ID, ETH_E_INV_POINTER, E_NOT_OK);
#else
    /* @req 4.2.2/SWS_Eth_00050 */
    VALIDATE_RV((NULL != CtrlModePtr), ETH_GETCONTROLLERMODE_ID, ETH_E_PARM_POINTER, E_NOT_OK);
#endif
   /* @req 4.1.2/SWS_Eth_00047 *//* @req 4.2.2/SWS_Eth_00047 *//* @req 4.0.3/ETH047 */
    *CtrlModePtr = EthGlobal.ControllerMode[CtrlIdx];
    return E_OK;
}

/**
 * Obtains the physical source address used by the indexed controller
 * @param CtrlIdx
 * @param PhysAddrPtr
 */
/* @req 4.1.2/SWS_Eth_00052 *//* @req 4.2.2/SWS_Eth_00052 *//* @req 4.0.3/ETH052 */
void Eth_GetPhysAddr(uint8 CtrlIdx, uint8* PhysAddrPtr)
{
    /* @req 4.1.2/SWS_Eth_00054 *//* @req 4.2.2/SWS_Eth_00054 *//* @req 4.0.3/ETH054 */
    VALIDATE_NO_RV(EthGlobal.InitRun, ETH_GETPHYSADDR_ID, ETH_E_NOT_INITIALIZED);
    /* @req 4.1.2/SWS_Eth_00055 *//* @req 4.2.2/SWS_Eth_00055 *//* @req 4.0.3/ETH055 */
    VALIDATE_NO_RV((CtrlIdx < ETH_NOF_CONFIG_CTRL), ETH_GETPHYSADDR_ID, ETH_E_INV_CTRL_IDX);
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
    /* @req 4.1.2/SWS_Eth_00054 *//* @req 4.0.3/ETH054 */
    VALIDATE_NO_RV((ETH_STATE_ACTIVE == EthGlobal.ControllerState[CtrlIdx]), ETH_GETPHYSADDR_ID, ETH_E_NOT_INITIALIZED);
    /* @req 4.1.2/SWS_Eth_00056 *//* @req 4.0.3/ETH056 */
    VALIDATE_NO_RV((NULL != PhysAddrPtr), ETH_GETPHYSADDR_ID, ETH_E_INV_POINTER);
#else
    /* @req 4.2.2/SWS_Eth_00056 */
    VALIDATE_NO_RV((NULL != PhysAddrPtr), ETH_GETPHYSADDR_ID, ETH_E_PARM_POINTER);
#endif
    /* @req 4.1.2/SWS_Eth_00053 */ /* @req 4.2.2/SWS_Eth_00053 *//* @req 4.0.3/ETH053 */
    Eth_Hw_GetPhysAddr(&EthGlobal.Config->ConfigSet->Controllers[CtrlIdx], PhysAddrPtr);
}

/**
 * Sets the physical source address used by the indexed controller
 * @param CtrlIdx
 * @param PhysAddrPtr
 * @return void
 */
#if !defined(CFG_RH850)
/* @req 4.1.2/SWS_Eth_00151 *//* @req 4.2.2/SWS_Eth_00151 */
void Eth_SetPhysAddr(uint8 CtrlIdx, const uint8* PhysAddrPtr)
{
    /* @req 4.1.2/SWS_Eth_00140 *//* @req 4.2.2/SWS_Eth_00140 */
    VALIDATE_NO_RV(EthGlobal.InitRun, ETH_SETPHYSADDR_ID, ETH_E_NOT_INITIALIZED);
    /* @req 4.1.2/SWS_Eth_00141 *//* @req 4.2.2/SWS_Eth_00141 */
    VALIDATE_NO_RV((CtrlIdx < ETH_NOF_CONFIG_CTRL), ETH_SETPHYSADDR_ID, ETH_E_INV_CTRL_IDX);
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
    /* @req 4.1.2/SWS_Eth_00140 */
    VALIDATE_NO_RV((ETH_STATE_ACTIVE == EthGlobal.ControllerState[CtrlIdx]), ETH_SETPHYSADDR_ID, ETH_E_NOT_INITIALIZED);
    /* @req 4.1.2/SWS_Eth_00142 */
    VALIDATE_NO_RV((NULL != PhysAddrPtr), ETH_SETPHYSADDR_ID, ETH_E_INV_POINTER);
#else
    /* @req 4.2.2/SWS_Eth_00142 */
    VALIDATE_NO_RV((NULL != PhysAddrPtr), ETH_SETPHYSADDR_ID, ETH_E_PARM_POINTER);
#endif
    /* @req 4.1.2/SWS_Eth_00139 *//* @req 4.2.2/SWS_Eth_00139 */
    Eth_Hw_SetPhysAddr(&EthGlobal.Config->ConfigSet->Controllers[CtrlIdx], PhysAddrPtr);
}
#endif

/* @req 4.1.2/SWS_Eth_00152 *//* @req 4.2.2/SWS_Eth_00152 */
#if (ETH_PHYS_ADRS_FILTER_API == STD_ON)
/**
 * Sets the physical source address used by the indexed controller
 * @param CtrlIdx
 * @param PhysAddrPtr
 * @param Action
 * @return E_OK: filter was successfully changed, E_NOT_OK: filter could not be changed
 */
/*lint -e{818} 'PhysAddrPtr' can not be declared as pointing to const as API is specified by AUTOSAR*/
Std_ReturnType Eth_UpdatePhysAddrFilter(uint8 CtrlIdx, const uint8* PhysAddrPtr,Eth_FilterActionType Action )
{
    /* @req 4.1.2/SWS_Eth_00164 *//* @req 4.2.2/SWS_Eth_00164 */
    VALIDATE_RV(EthGlobal.InitRun, ETH_UPDATEPHYSADDRFILTER_ID, ETH_E_NOT_INITIALIZED,E_NOT_OK);
    /* @req 4.1.2/SWS_Eth_00165 *//* @req 4.2.2/SWS_Eth_00165 */
	VALIDATE_RV((CtrlIdx < ETH_NOF_CONFIG_CTRL), ETH_UPDATEPHYSADDRFILTER_ID, ETH_E_INV_CTRL_IDX,E_NOT_OK);
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
    /* @req 4.1.2/SWS_Eth_00164 */
    VALIDATE_RV((ETH_STATE_ACTIVE == EthGlobal.ControllerState[CtrlIdx]), ETH_UPDATEPHYSADDRFILTER_ID, ETH_E_NOT_INITIALIZED,E_NOT_OK);
    /* @req 4.1.2/SWS_Eth_00166 */
    VALIDATE_RV((NULL != PhysAddrPtr), ETH_UPDATEPHYSADDRFILTER_ID, ETH_E_INV_POINTER,E_NOT_OK);
#else
    /* @req 4.2.2/SWS_Eth_00166 */
    VALIDATE_RV((NULL != PhysAddrPtr), ETH_UPDATEPHYSADDRFILTER_ID, ETH_E_PARM_POINTER,E_NOT_OK);
#endif
    /* @req 4.1.2/SWS_Eth_00150 *//* @req 4.2.2/SWS_Eth_00150 */
    return Eth_Hw_UpdatePhysAddrFilter(&EthGlobal.Config->ConfigSet->Controllers[CtrlIdx], PhysAddrPtr,Action);
}
#endif

/* @req 4.1.2/SWS_Eth_00062 *//* @req 4.2.2/SWS_Eth_00062 *//* @req 4.0.3/ETH062 */
/* @req 4.1.2/SWS_Eth_00069 *//* @req 4.2.2/SWS_Eth_00069 *//* @req 4.0.3/ETH069 */
#if (ETH_MII_API == STD_ON)
/**
 * Configures a transceiver register or triggers a function offered by the receiver
 * @param CtrlIdx
 * @param TrcvIdx
 * @param RegIdx
 * @param RegVal
 */
 /* @req 4.1.2/SWS_Eth_00058 *//* @req 4.0.3/ETH058 */
#if defined(CFG_RH850)
void Eth_WriteMii(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal)
{
    /* @req 4.1.2/SWS_Eth_00060 *//* @req 4.0.3/ETH060 */
    VALIDATE_NO_RV(EthGlobal.InitRun, ETH_WRITEMII_ID, ETH_E_NOT_INITIALIZED);
    /* @req 4.1.2/SWS_Eth_00061 *//* @req 4.0.3/ETH061 */
    VALIDATE_NO_RV((CtrlIdx < ETH_NOF_CONFIG_CTRL), ETH_WRITEMII_ID, ETH_E_INV_CTRL_IDX);
    /* @req 4.1.2/SWS_Eth_00060 *//* @req 4.0.3/ETH060 */
    VALIDATE_NO_RV((ETH_STATE_ACTIVE == EthGlobal.ControllerState[CtrlIdx]), ETH_WRITEMII_ID, ETH_E_NOT_INITIALIZED);
    /* @req 4.0.3/ETH128 */
    VALIDATE_NO_RV((ETH_MODE_ACTIVE == EthGlobal.ControllerMode[CtrlIdx]), ETH_WRITEMII_ID, ETH_E_INV_MODE);

    if( !EthGlobal.Config->ConfigSet->Controllers[CtrlIdx].EthCtrlEnableMii ) {
        DET_REPORT_ERROR(ETH_READMII_ID, ETH_E_MII_NOT_ENABLED);
        return;
    }

    /* @req 4.1.2/SWS_Eth_00059 *//* @req 4.0.3/ETH059 */
    if( E_OK != Eth_Hw_WriteMii(&EthGlobal.Config->ConfigSet->Controllers[CtrlIdx], TrcvIdx, RegIdx, RegVal) ) {
        DET_REPORT_ERROR(ETH_READMII_ID, ETH_E_WRITE_MII_FAIL);
    }
}
#else
/* @req 4.2.2/SWS_Eth_00058 */
Eth_ReturnType Eth_WriteMii(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal)
{
    /* @req 4.1.2/SWS_Eth_00060 *//* @req 4.2.2/SWS_Eth_00060 *//* @req 4.0.3/ETH060 */
    VALIDATE_RV(EthGlobal.InitRun, ETH_WRITEMII_ID, ETH_E_NOT_INITIALIZED, ETH_E_NOT_OK);
    /* @req 4.1.2/SWS_Eth_00061 *//* @req 4.2.2/SWS_Eth_00061 *//* @req 4.0.3/ETH061 */
	VALIDATE_RV((CtrlIdx < ETH_NOF_CONFIG_CTRL), ETH_WRITEMII_ID, ETH_E_INV_CTRL_IDX,ETH_E_NOT_OK);
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
    /* @req 4.1.2/SWS_Eth_00060 *//* @req 4.0.3/ETH060 */
    VALIDATE_RV((ETH_STATE_ACTIVE == EthGlobal.ControllerState[CtrlIdx]), ETH_WRITEMII_ID, ETH_E_NOT_INITIALIZED,ETH_E_NOT_OK);
#endif
    if( !EthGlobal.Config->ConfigSet->Controllers[CtrlIdx].EthCtrlEnableMii ) {
        DET_REPORT_ERROR(ETH_READMII_ID, ETH_E_MII_NOT_ENABLED);
        return ETH_E_NOT_OK;
    }

    /* @req 4.1.2/SWS_Eth_00059 *//* @req 4.2.2/SWS_Eth_00059 *//* @req 4.0.3/ETH059 */
    if( E_OK != Eth_Hw_WriteMii(&EthGlobal.Config->ConfigSet->Controllers[CtrlIdx], TrcvIdx, RegIdx, RegVal) ) {
        DET_REPORT_ERROR(ETH_READMII_ID, ETH_E_WRITE_MII_FAIL);
        return ETH_E_NO_ACCESS;
    }
    return ETH_OK;
}
#endif

/**
 * Reads a transceiver register
 * @param CtrlIdx
 * @param TrcvIdx
 * @param RegIdx
 * @param RegValPtr
 */
 /* @req 4.1.2/SWS_Eth_00064 *//* @req 4.0.3/ETH064 */
#if defined(CFG_RH850)
void Eth_ReadMii(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16* RegValPtr)
{
    /* @req 4.1.2/SWS_Eth_00066 *//* @req 4.0.3/ETH066 */
    VALIDATE_NO_RV(EthGlobal.InitRun, ETH_READMII_ID, ETH_E_NOT_INITIALIZED);
    /* @req 4.1.2/SWS_Eth_00067 *//* @req 4.0.3/ETH067 */
    VALIDATE_NO_RV((CtrlIdx < ETH_NOF_CONFIG_CTRL), ETH_READMII_ID, ETH_E_INV_CTRL_IDX);
    /* @req 4.1.2/SWS_Eth_00066 *//* @req 4.0.3/ETH066 */
    VALIDATE_NO_RV((ETH_STATE_ACTIVE == EthGlobal.ControllerState[CtrlIdx]), ETH_READMII_ID, ETH_E_NOT_INITIALIZED);
    /* @req 4.1.2/SWS_Eth_00068 *//* @req 4.0.3/ETH068 */
    VALIDATE_NO_RV((NULL != RegValPtr), ETH_READMII_ID, ETH_E_INV_POINTER);
    /* @req 4.0.3/ETH127 */
    VALIDATE_NO_RV((ETH_MODE_ACTIVE == EthGlobal.ControllerMode[CtrlIdx]), ETH_READMII_ID, ETH_E_INV_MODE);

    if( !EthGlobal.Config->ConfigSet->Controllers[CtrlIdx].EthCtrlEnableMii ) {
        DET_REPORT_ERROR(ETH_READMII_ID, ETH_E_MII_NOT_ENABLED);
        return;
    }

    /* @req 4.1.2/SWS_Eth_00065 *//* @req 4.0.3/ETH065 */
    if( E_OK != Eth_Hw_ReadMii(&EthGlobal.Config->ConfigSet->Controllers[CtrlIdx], TrcvIdx, RegIdx, RegValPtr) ) {
        DET_REPORT_ERROR(ETH_READMII_ID, ETH_E_READ_MII_FAIL);
    }
}
#else
/* @req 4.2.2/SWS_Eth_00064 */
Eth_ReturnType Eth_ReadMii(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16* RegValPtr)
{
    /* @req 4.1.2/SWS_Eth_00066 *//* @req 4.2.2/SWS_Eth_00066 *//* @req 4.0.3/ETH066 */
    VALIDATE_RV(EthGlobal.InitRun, ETH_READMII_ID, ETH_E_NOT_INITIALIZED,ETH_E_NOT_OK);
    /* @req 4.1.2/SWS_Eth_00067 *//* @req 4.2.2/SWS_Eth_00067 *//* @req 4.0.3/ETH067 */
	VALIDATE_RV((CtrlIdx < ETH_NOF_CONFIG_CTRL), ETH_READMII_ID, ETH_E_INV_CTRL_IDX,ETH_E_NOT_OK);
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
    /* @req 4.1.2/SWS_Eth_00066 *//* @req 4.0.3/ETH066 */
    VALIDATE_RV((ETH_STATE_ACTIVE == EthGlobal.ControllerState[CtrlIdx]), ETH_READMII_ID, ETH_E_NOT_INITIALIZED,ETH_E_NOT_OK);
    /* @req 4.1.2/SWS_Eth_00068 *//* @req 4.0.3/ETH068 */
    VALIDATE_RV((NULL != RegValPtr), ETH_READMII_ID, ETH_E_INV_POINTER,ETH_E_NOT_OK);
#else
    /* @req 4.2.2/SWS_Eth_00068 *//* @req 4.0.3/ETH068 */
    VALIDATE_RV((NULL != RegValPtr), ETH_READMII_ID, ETH_E_PARM_POINTER,ETH_E_NOT_OK);
#endif
    if( !EthGlobal.Config->ConfigSet->Controllers[CtrlIdx].EthCtrlEnableMii ) {
        DET_REPORT_ERROR(ETH_READMII_ID, ETH_E_MII_NOT_ENABLED);
        return ETH_E_NOT_OK;
    }

    /* @req 4.1.2/SWS_Eth_00065 *//* @req 4.2.2/SWS_Eth_00065 *//* @req 4.0.3/ETH065 */
    if( E_OK != Eth_Hw_ReadMii(&EthGlobal.Config->ConfigSet->Controllers[CtrlIdx], TrcvIdx, RegIdx, RegValPtr) ) {
        DET_REPORT_ERROR(ETH_READMII_ID, ETH_E_READ_MII_FAIL);
        return ETH_E_NO_ACCESS;
    }
    return ETH_OK;
}
#endif
#endif

/**
 * Provides access to a transmit buffer of the specified controller
 * @param CtrlIdx
 * @param BufIdxPtr
 * @param BufPtr
 * @param LenBytePtr
 * @return  BUFREQ_OK: success,
 *          BUFREQ_E_NOT_OK: development error detected,
 *          BUFREQ_E_BUSY: all buffers in use
 */
/* @req 4.1.2/SWS_Eth_00077 *//* @req 4.2.2/SWS_Eth_00077 *//* @req 4.0.3/ETH077 */
BufReq_ReturnType Eth_ProvideTxBuffer(uint8 CtrlIdx, Eth_BufIdxType* BufIdxPtr, uint8** BufPtr, uint16* LenBytePtr)
{
    /* @req 4.1.2/SWS_Eth_00081 *//* @req 4.2.2/SWS_Eth_00081 *//* @req 4.0.3/ETH081*/
    VALIDATE_RV(EthGlobal.InitRun, ETH_PROVIDETXBUFFER_ID, ETH_E_NOT_INITIALIZED, BUFREQ_E_NOT_OK);
    /* @req 4.1.2/SWS_Eth_00082 *//* @req 4.2.2/SWS_Eth_00082 *//* @req 4.0.3/ETH082 */
    VALIDATE_RV((CtrlIdx < ETH_NOF_CONFIG_CTRL), ETH_PROVIDETXBUFFER_ID, ETH_E_INV_CTRL_IDX, BUFREQ_E_NOT_OK);
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
    /* @req 4.1.2/SWS_Eth_00081 *//* @req 4.0.3/ETH081*/
    VALIDATE_RV((ETH_STATE_ACTIVE == EthGlobal.ControllerState[CtrlIdx]), ETH_PROVIDETXBUFFER_ID, ETH_E_NOT_INITIALIZED, BUFREQ_E_NOT_OK);
    /* @req 4.1.2/SWS_Eth_00083 *//* @req 4.0.3/ETH083 */
    VALIDATE_RV((NULL != BufIdxPtr), ETH_PROVIDETXBUFFER_ID, ETH_E_INV_POINTER, BUFREQ_E_NOT_OK);
    /* @req 4.1.2/SWS_Eth_00084 *//* @req 4.0.3/ETH084 */
    VALIDATE_RV((NULL != BufPtr), ETH_PROVIDETXBUFFER_ID, ETH_E_INV_POINTER, BUFREQ_E_NOT_OK);
    /* @req 4.1.2/SWS_Eth_00085 *//* @req 4.0.3/ETH085 */
    VALIDATE_RV((NULL != LenBytePtr), ETH_PROVIDETXBUFFER_ID, ETH_E_INV_POINTER, BUFREQ_E_NOT_OK);
#else
    /* @req 4.2.2/SWS_Eth_00083 */
    VALIDATE_RV((NULL != BufIdxPtr), ETH_PROVIDETXBUFFER_ID, ETH_E_PARM_POINTER, BUFREQ_E_NOT_OK);
    /* @req 4.2.2/SWS_Eth_00084 */
    VALIDATE_RV((NULL != BufPtr), ETH_PROVIDETXBUFFER_ID, ETH_E_PARM_POINTER, BUFREQ_E_NOT_OK);
    /* @req 4.2.2/SWS_Eth_00085 */
    VALIDATE_RV((NULL != LenBytePtr), ETH_PROVIDETXBUFFER_ID, ETH_E_PARM_POINTER, BUFREQ_E_NOT_OK);
#endif

    return Eth_Hw_ProvideTxBuffer(&EthGlobal.Config->ConfigSet->Controllers[CtrlIdx], BufIdxPtr, BufPtr, LenBytePtr);
}

/**
 * Triggers transmission of a previously filled transmit buffer
 * @param CtrlIdx
 * @param BufIdx
 * @param FrameType
 * @param TxConfirmation
 * @param LenByte
 * @param PhysAddrPtr
 * @return E_OK: success, E_NOT_OK: transmission failed
 */
/* @req 4.1.2/SWS_Eth_00087 *//* @req 4.2.2/SWS_Eth_00087 *//* @req 4.0.3/ETH087 */
/*lint -e{818} 'PhysAddrPtr' can not be declared as pointing to const as API is specified by AUTOSAR*/
Std_ReturnType Eth_Transmit(uint8 CtrlIdx, Eth_BufIdxType BufIdx, Eth_FrameType FrameType, boolean TxConfirmation, uint16 LenByte, const uint8* PhysAddrPtr)
{
    /* @req 4.1.2/SWS_Eth_00090 *//* @req 4.2.2/SWS_Eth_00090 *//* @req 4.0.3/ETH090 */
    VALIDATE_RV(EthGlobal.InitRun, ETH_TRANSMIT_ID, ETH_E_NOT_INITIALIZED, E_NOT_OK);
    /* @req 4.1.2/SWS_Eth_00091 *//* @req 4.2.2/SWS_Eth_00091 *//* @req 4.0.3/ETH091 */
    VALIDATE_RV((CtrlIdx < ETH_NOF_CONFIG_CTRL), ETH_TRANSMIT_ID, ETH_E_INV_CTRL_IDX, E_NOT_OK);
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
    /* @req 4.1.2/SWS_Eth_00090 *//* @req 4.0.3/ETH090 */
    VALIDATE_RV((ETH_STATE_ACTIVE == EthGlobal.ControllerState[CtrlIdx]), ETH_TRANSMIT_ID, ETH_E_NOT_INITIALIZED, E_NOT_OK);
#endif
    /* @req 4.1.2/SWS_Eth_00092 *//* @req 4.2.2/SWS_Eth_00092 *//* @req 4.0.3/ETH092 */
    VALIDATE_RV((BufIdx < (uint32)EthGlobal.Config->ConfigSet->Controllers[CtrlIdx].EthTxBufTotal), ETH_TRANSMIT_ID, ETH_E_INV_PARAM, E_NOT_OK);
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
    /* @req 4.1.2/SWS_Eth_00093 *//* @req 4.0.3/ETH093 */
    VALIDATE_RV((NULL != PhysAddrPtr), ETH_TRANSMIT_ID, ETH_E_INV_POINTER, E_NOT_OK);
#else
    /* @req 4.2.2/SWS_Eth_00093 */
    VALIDATE_RV((NULL != PhysAddrPtr), ETH_TRANSMIT_ID, ETH_E_PARM_POINTER, E_NOT_OK);
#endif
    /* @req 4.1.2/SWS_Eth_00129 *//* @req 4.2.2/SWS_Eth_00129 *//* @req 4.0.3/ETH129 */
    VALIDATE_RV((ETH_MODE_ACTIVE == EthGlobal.ControllerMode[CtrlIdx]), ETH_TRANSMIT_ID, ETH_E_INV_MODE, E_NOT_OK);

    return Eth_Hw_Transmit(&EthGlobal.Config->ConfigSet->Controllers[CtrlIdx], BufIdx, FrameType, TxConfirmation, LenByte, PhysAddrPtr);
}

/**
 * Triggers frame reception
 * @param CtrlIdx
 * @param RxStatusPtr (depends on version)
 * @return None
 */
/* @req 4.0.3/ETH095 */
#if defined(CFG_RH850)
void Eth_Receive(uint8 CtrlIdx)
#else
/* @req 4.1.2/SWS_Eth_00095 *//* @req 4.2.2/SWS_Eth_00095 */
void Eth_Receive(uint8 CtrlIdx,Eth_RxStatusType* RxStatusPtr)
#endif
{
    /* @req 4.1.2/SWS_Eth_00097 *//* @req 4.2.2/SWS_Eth_00097 *//* @req 4.0.3/ETH097 */
    VALIDATE_NO_RV(EthGlobal.InitRun, ETH_RECEIVE_ID, ETH_E_NOT_INITIALIZED);
    /* @req 4.1.2/SWS_Eth_00098 *//* @req 4.2.2/SWS_Eth_00098 *//* @req 4.0.3/ETH098 */
    VALIDATE_NO_RV((CtrlIdx < ETH_NOF_CONFIG_CTRL), ETH_RECEIVE_ID, ETH_E_INV_CTRL_IDX);
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
    /* @req 4.1.2/SWS_Eth_00097 *//* @req 4.0.3/ETH097 */
    VALIDATE_NO_RV((ETH_STATE_ACTIVE == EthGlobal.ControllerState[CtrlIdx]), ETH_RECEIVE_ID, ETH_E_NOT_INITIALIZED);
#endif
    /* @req 4.1.2/SWS_Eth_00132 *//* @req 4.2.2/SWS_Eth_00132 *//* @req 4.0.3/ETH132 */
    VALIDATE_NO_RV((ETH_MODE_ACTIVE == EthGlobal.ControllerMode[CtrlIdx]), ETH_RECEIVE_ID, ETH_E_INV_MODE);
#if defined(CFG_RH850)
    Eth_Hw_Receive(CtrlIdx);
#else
    Eth_Hw_Receive(CtrlIdx,RxStatusPtr);
#endif
}

/**
 * Triggers frame transmission confirmation
 * @param CtrlIdx
 * @return None
 */
/* @req 4.1.2/SWS_Eth_00100 *//* @req 4.2.2/SWS_Eth_00100 *//* @req 4.0.3/ETH100 */
void Eth_TxConfirmation(uint8 CtrlIdx)
{
    /* @req 4.1.2/SWS_Eth_00103 *//* @req 4.2.2/SWS_Eth_00103 *//* @req 4.0.3/ETH103 */
    VALIDATE_NO_RV(EthGlobal.InitRun, ETH_TXCONFIRMATION_ID, ETH_E_NOT_INITIALIZED);
    /* @req 4.1.2/SWS_Eth_00104 *//* @req 4.2.2/SWS_Eth_00104 *//* @req 4.0.3/ETH104 */
    VALIDATE_NO_RV((CtrlIdx < ETH_NOF_CONFIG_CTRL), ETH_TXCONFIRMATION_ID, ETH_E_INV_CTRL_IDX);
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
    /* @req 4.1.2/SWS_Eth_00103 *//* @req 4.0.3/ETH103 */
    VALIDATE_NO_RV((ETH_STATE_ACTIVE == EthGlobal.ControllerState[CtrlIdx]), ETH_TXCONFIRMATION_ID, ETH_E_NOT_INITIALIZED);
#endif
    /* @req 4.1.2/SWS_Eth_00134 *//* @req 4.2.2/SWS_Eth_00134 *//* @req 4.0.3/ETH134 */
    VALIDATE_NO_RV((ETH_MODE_ACTIVE == EthGlobal.ControllerMode[CtrlIdx]), ETH_TXCONFIRMATION_ID, ETH_E_INV_MODE);

    Eth_Hw_TxConfirmation(CtrlIdx);
}

/**
 * The function checks for controller errors and lost frames. Used for polling state changes.
 * Calls EthIf_CtrlModeIndication when the controller mode changed
 * @param void
 * @return None
 */
#if !defined(CFG_RH850) && !defined(CFG_BRD_ZYNQ_ZC702)
void Eth_MainFunction (void){
    /* !req 4.2.2/SWS_Eth_00169 */
    /* !req 4.2.2/SWS_Eth_00172 */
    /* !req 4.2.2/SWS_Eth_00240 */
}
#endif

/* @req 4.0.3/ETH108 */
#if (ETH_VERSION_INFO_API == STD_ON)
/**
 * Returns the version information of this module
 * @param VersionInfoPtr
 * @return None
 */
/* @req 4.1.2/SWS_Eth_00106 *//* @req 4.2.2/SWS_Eth_00106 *//* @req 4.0.3/ETH106 */
void Eth_GetVersionInfo(Std_VersionInfoType* VersionInfoPtr)
{
#if defined(CFG_RH850) || defined(CFG_BRD_ZYNQ_ZC702)
	/* @req 4.1.2/SWS_Eth_00136 *//* @req 4.0.3/ETH136 */
    VALIDATE_NO_RV((NULL != VersionInfoPtr), ETH_GETVERSIONINFO_ID, ETH_E_INV_POINTER);
#else
    /* @req 4.2.2/SWS_Eth_00136 *//* @req 4.0.3/ETH136 */
    VALIDATE_NO_RV((NULL != VersionInfoPtr), ETH_GETVERSIONINFO_ID, ETH_E_PARM_POINTER);
#endif
    /* @req 4.0.3/ETH107 */
    VersionInfoPtr->vendorID = ETH_VENDOR_ID;
    VersionInfoPtr->moduleID = ETH_MODULE_ID;
    VersionInfoPtr->sw_major_version = ETH_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = ETH_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = ETH_SW_PATCH_VERSION;
}
#endif
/*lint -restore*/ /*Return statement before end of function - OK
 *                             Unpermitted operand to operator '! - OK */

