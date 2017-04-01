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

/** @tagSettings DEFAULT_ARCHITECTURE=JACINTO5|JACINTO6|TMS570 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/* General requirements */
/** @req 4.1.2/SWS_Can_00035 *//* No callbacks */
/** @req 4.1.2/SWS_Can_00079 *//* Coding guidelines */
/** @req 4.1.2/SWS_Can_00220 *//* Precompile variant */
/** @req 4.1.2/SWS_Can_00237 *//* No transmit triggered by RTR */
/** @req 4.1.2/SWS_Can_00236 *//* No transmit triggered by RTR */
/** @req 4.1.2/SWS_Can_00238 *//* On-chip controller, does not use other drivers */
/** @req 4.1.2/SWS_Can_00103 */
/** @req 4.1.2/SWS_Can_00104 */

#include "Can.h"
#if defined(CFG_TMS570)
#include "core_cr4.h"
#include "irq_tms570.h"
#elif defined(CFG_JACINTO)
#include "irq_jacinto.h"
#else
#error DCAN not supported for the used MCU.
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#if defined(USE_DET)
#include "Det.h"
#endif
#include "CanIf_Cbk.h"
#include "SchM_Can.h"
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
#include "isr.h"
#endif
#include "Mcu.h"
#include "arc.h"
#include <string.h>

#if defined(CFG_JACINTO)
typedef volatile struct {
    uint32   CTL;
    uint32   SR;
    uint8 TEC :  8;
    uint8 REC :  8;
    uint16     : 16;
    uint32   BTR;
    uint32   IR;
    uint32   TR;
    uint32 : 32;
    uint32   PEC;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32   ABOT;
    uint32   TRX;
    uint32   TRx[4];
    uint32   NDX;
    uint32   NDx[4];
    uint32   IPX;
    uint32   IPx[4];
    uint32   MVX;
    uint32   MVx[4];
    uint32 : 32;
    uint32   IPMx[4];
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    struct
    {
        uint32   COM;
        uint32   MASK;
        uint32   ARB;
        uint32   MC;
        uint8    DATx[8];
        uint32 : 32;
        uint32 : 32;
    } IFx[3];
    uint32   IF3UEy[4];
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32 : 32;
    uint32   IOTX;
    uint32   IORX;
} Can_RegisterType;
#endif

#if defined(CFG_JAC6)
#define DCAN1_Base ((Can_RegisterType *)(0x4AE3C000 + L3_OFFSET))
#define DCAN2_Base ((Can_RegisterType *)(0x48480000 + L3_OFFSET))
#elif defined(CFG_JAC5) || defined(CFG_JAC5E)
#define DCAN1_Base ((Can_RegisterType *)0x481CC000)
#define DCAN2_Base ((Can_RegisterType *)0x481D0000)
#elif defined(CFG_TMS570)
/* DCAN base addresses are defined in core_cr4.h */
#else
#error DCAN not supported for the used MCU.
#endif

#if defined(ARC_CAN_TIMEOUT_DURATION)
#define CAN_TIMEOUT_DURATION				ARC_CAN_TIMEOUT_DURATION
#else
#define CAN_TIMEOUT_DURATION				0xFFFFFFFFu
#endif

#define DCAN1_MAX_MESSAGEBOXES				64
#define DCAN2_MAX_MESSAGEBOXES				64
#if defined (CFG_TMS570)
#define DCAN3_MAX_MESSAGEBOXES				32
#endif

#define DCAN_TX_MSG_OBJECT_NR				1
#define DCAN_RX_MSG_OBJECT_NR				2

#define CAN_REG_CTL_INIT_MASK				1u
#define CAN_REG_CTL_PARITY_DISABLED			0x5uL

#define CAN_REG_CTL_INIT_BIT				0U
#define CAN_REG_CTL_IE0_BIT					1U
#define CAN_REG_CTL_SIE_BIT					2U
#define CAN_REG_CTL_EIE_BIT					3U
#define CAN_REG_CTL_DAR_BIT					5U
#define CAN_REG_CTL_CCE_BIT					6U
#define CAN_REG_CTL_TEST_MODE_BIT			7U
#define CAN_REG_CTL_ABO_BIT					9U
#define CAN_REG_CTL_PARITY_BIT				10U
#define CAN_REG_CTL_SWR_BIT					15U
#define CAN_REG_CTL_IE1_BIT					17U
#define CAN_REG_CTL_PDR_BIT				 	24U
#define CAN_REG_CTL_WUBA_BIT				25U

#define CAN_REG_TR_LBACK_BIT				4U
#define CAN_REG_TR_TX_BIT					4U

#define CAN_REG_INT_EOB_BIT					7U

#define CAN_REG_ES_LEC_MASK					0x7u

#define CAN_REG_ES_TXOK_BIT					3U
#define CAN_REG_ES_RXOK_BIT					4U
#define CAN_REG_ES_EPASS_BIT				5U
#define CAN_REG_ES_EWARN_BIT				6U
#define CAN_REG_ES_BOFF_BIT					7U
#define CAN_REG_ES_PER_BIT					8U
#define CAN_REG_ES_WKPEND_BIT				9U
#define CAN_REG_ES_PDA_BIT					10U

#define CAN_REG_IFX_COM_DATAB_BIT			16U
#define CAN_REG_IFX_COM_DATAA_BIT			17U
#define CAN_REG_IFX_COM_TXREQ_BIT			18U
#define CAN_REG_IFX_COM_NEWDAT_BIT			18U
#define CAN_REG_IFX_COM_CLEARINTPEND_BIT	19U
#define CAN_REG_IFX_COM_CONTROL_BIT			20U
#define CAN_REG_IFX_COM_ARB_BIT				21U
#define CAN_REG_IFX_COM_WRRD_BIT			23U
#define CAN_REG_IFX_ARB_STDID_BIT			18U
#define CAN_REG_IFX_ARB_DIR_BIT				29U
#define CAN_REG_IFX_ARB_XTD_BIT				30U
#define CAN_REG_IFX_ARB_MSGVAL_BIT			31U
#define CAN_REG_IFX_MASK_MXTD_BIT			31U
#define CAN_REG_IFX_MASK_STDMSK_BIT			18U
#define CAN_REG_IFX_MASK_MDIR_BIT			30U

#define CAN_REG_IFX_MCTL_UMASK_BIT			12U
#define CAN_REG_IFX_MCTL_RXIE_BIT			10U
#define CAN_REG_IFX_MCTL_TXIE_BIT			11U
#define CAN_REG_IFX_MCTL_EOB_BIT			7U

#define CAN_REG_MC_DLC_MASK					0x0000000FuL

#define STD_ID_MASK							0x7FFu
#define EXT_ID_MASK							0x1FFFFFFFu
#define EXT_ID_BIT							0x80000000u

#define CAN_REG_BTR_BRP_MASK				0x3Fu
#define CAN_REG_BTR_BRPE_MASK				0x3C0u
#define CAN_REG_BTR_BRPE_RSHIFT				6u

#define CAN_REG_BTR_BRPE_OFFSET				16u
#define CAN_REG_BTR_SJW_OFFSET				6u
#define CAN_REG_BTR_TSEG1_OFFSET			8u
#define CAN_REG_BTR_TSEG2_OFFSET			12u

#define CAN_REG_IR_INT0ID_MASK				0x0000FFFFuL
#define CAN_REG_IR_BUSEVENT					0x8000uL
#define CAN_REG_IR_INT0ID_MSG_MASK			0x000000FFuL

#define CAN_IRQ_PRIORITY					4u

#define DCAN_MC_NEWDAT						15u
#define DCAN_MC_EOB							7u

/** @req 4.0.3/CAN027 */
/** @req 4.1.2/SWS_Can_00091*/
/** @req 4.1.2/SWS_Can_00089*/
#if ( CAN_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err) \
        if( !(_exp) ) { \
          (void)Det_ReportError(CAN_MODULE_ID,0,_api,_err); \
          return CAN_NOT_OK; \
        }

#define VALIDATE_STD_RV(_exp,_api,_err) \
        if( !(_exp) ) { \
          (void)Det_ReportError(CAN_MODULE_ID,0,_api,_err); \
          return E_NOT_OK; \
        }

#define VALIDATE_NO_RV(_exp,_api,_err) \
        if( !(_exp) ) { \
          (void)Det_ReportError(CAN_MODULE_ID,0,_api,_err); \
          return; \
        }

#define DET_REPORTERROR(_x,_y,_z,_q) Det_ReportError(_x, _y, _z, _q)
#else
#define VALIDATE(_exp,_api,_err)
#define VALIDATE_STD_RV(_exp,_api,_err)
#define VALIDATE_NO_RV(_exp,_api,_err)
#define DET_REPORTERROR(_x,_y,_z,_q)
#endif

#if !defined(USE_DEM)
// If compiled without the DEM, calls to DEM are simply ignored.
#define Dem_ReportErrorStatus(...)
#endif

static inline uint8 getControllerConfigIdx(uint8 controller);

#define GET_CONTROLLER_CONFIG(_controller) \
                            &Can_Global.config->CanConfigSetPtr->CanController[getControllerConfigIdx(_controller)]

#define GET_PRIVATE_DATA(_controller) &CanUnits[_controller]



/* Macro for waiting until busy flag is 0 */
#define DCAN_WAIT_UNTIL_NOT_BUSY(ControllerId, IfRegId) \
    { \
        uint32 ErrCounter = CAN_TIMEOUT_DURATION; \
        while((CanRegs[ControllerId]->IFx[IfRegId].COM & 0x00008000u) > 0u) { \
            ErrCounter--; \
            if(ErrCounter == 0) { \
                Dem_ReportErrorStatus(DemConf_DemEventParameter_CAN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED); \
                ErrCounter = CAN_TIMEOUT_DURATION; \
                return CAN_NOT_OK; \
            } \
        } \
    }

/* Macro for waiting until busy flag is 0 */
#define DCAN_WAIT_UNTIL_NOT_BUSY_NO_RV(ControllerId, IfRegId) \
    { \
        uint32 ErrCounter = CAN_TIMEOUT_DURATION; \
        while((CanRegs[ControllerId]->IFx[IfRegId].COM & 0x00008000u) > 0) { \
            ErrCounter--; \
            if(ErrCounter == 0) { \
                Dem_ReportErrorStatus(DemConf_DemEventParameter_CAN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED); \
                ErrCounter = CAN_TIMEOUT_DURATION; \
                return; \
            } \
        } \
    }

extern const Can_ControllerConfigType CanControllerConfigData[];

/* Array for easy access to DCAN register definitions. */
/*lint -e{923} cast from unsigned int to pointer - OK, necessary to use SFR of MCU. */
static Can_RegisterType* CanRegs[] = {
        DCAN1_Base,
        DCAN2_Base,
#if defined(CFG_TMS570)
        DCAN3_Base
#endif
};

typedef enum {
    CAN_UNINIT = 0,
    CAN_READY
} Can_DriverStateType;

typedef enum {
    CAN_CTRL_INDICATION_NONE,
    CAN_CTRL_INDICATION_PENDING_START,
    CAN_CTRL_INDICATION_PENDING_STOP,
    CAN_CTRL_INDICATION_PENDING_SLEEP /* Sleep is not implemented - but we need a logical sleep mode*/
} Can_CtrlPendingStateIndicationType;


/* Mapping between HRH and Controller//HOH */
typedef struct Can_Arc_ObjectHOHMapStruct {
    CanControllerIdType CanControllerRef;
    const Can_HardwareObjectType* CanHOHRef;
} Can_Arc_ObjectHOHMapType;

/* Type for holding global information used by the driver */
typedef struct {
    Can_DriverStateType initRun;
    const Can_ConfigType *config;
    /* One bit for each channel that is configured.
     * Used to determine if validity of a channel
     * 1 - configured
     * 0 - NOT configured */
    uint32 configured;
    /* Maps the a channel id to a configured channel id. */
    uint8 channelMap[CAN_CONTROLLER_CNT];
} Can_GlobalType;

Can_GlobalType Can_Global = { .initRun = CAN_UNINIT };

/* Type for holding information about each controller */
typedef struct {
    CanIf_ControllerModeType state;
    /* Data stored for Txconfirmation callbacks to CanIf. */
    Can_CtrlPendingStateIndicationType pendingStateIndication;
    uint64 mxBoxBusyMask;
    PduIdType transmittedPduIds[64];
    const uint8 MaxBoxes;
    uint32 WakeupSrc;
} Can_UnitType;

/* Used to switch between IF1 and IF2 of DCAN */
#define CAN_REG_IF_1 0
#define CAN_REG_IF_2 1
/* Not used: #define CAN_REG_IF_3 2 */

#define CAN_CTL_INTERRUPT_MASK ((1uL << CAN_REG_CTL_IE0_BIT) | (1uL << CAN_REG_CTL_IE1_BIT) | (0uL << CAN_REG_CTL_SIE_BIT) | (1uL << CAN_REG_CTL_EIE_BIT))
#define IF_MC_MASK(_dlc, _umask, _rxie, _txie, _eob) \
            (_dlc \
            | (_umask << CAN_REG_IFX_MCTL_UMASK_BIT) \
            | (_rxie  << CAN_REG_IFX_MCTL_RXIE_BIT) \
            | (_txie  << CAN_REG_IFX_MCTL_TXIE_BIT) \
            | (_eob   << CAN_REG_IFX_MCTL_EOB_BIT))

#if defined(CFG_TMS570)
/* Used to order Data Bytes according to hardware registers in DCAN.
 * TMS570 is big-endian (BE32). */
static const uint8 ElementIndex[] = { 3, 2, 1, 0, 7, 6, 5, 4 };
#elif defined(CFG_JACINTO)
/* Jacinto is little-endian. */
#else
#error DCAN not supported for the used MCU.
#endif

static uint8 RxShadowBuf[CAN_ARC_CTRL_CONFIG_CNT][8];

/* Driver must know how often Can_DisableControllerInterrupts() has been called */
static uint32 IntDisableCount[CAN_ARC_CTRL_CONFIG_CNT];

/* Private data for the Controller. */
Can_UnitType CanUnits[] = {
    {
        .state = CANIF_CS_UNINIT,
        .pendingStateIndication = CAN_CTRL_INDICATION_NONE,
        .MaxBoxes = DCAN1_MAX_MESSAGEBOXES,
        .WakeupSrc = 0,
        .mxBoxBusyMask = 0,
    },
    {
        .state = CANIF_CS_UNINIT,
        .pendingStateIndication = CAN_CTRL_INDICATION_NONE,
        .MaxBoxes = DCAN2_MAX_MESSAGEBOXES,
        .WakeupSrc = 0,
        .mxBoxBusyMask = 0
    },
#if defined(CFG_TMS570)
    {
        .state = CANIF_CS_UNINIT,
        .pendingStateIndication = CAN_CTRL_INDICATION_NONE,
        .MaxBoxes = DCAN3_MAX_MESSAGEBOXES,
        .WakeupSrc = 0,
        .mxBoxBusyMask = 0
    }
#endif
};

/**
 * Gets the index of a controller in the global configuration structure.
 * @param controller
 * @return controller index
 */
static inline uint8 getControllerConfigIdx(uint8 controller) {

    if (Can_Global.initRun == CAN_UNINIT) {
        //Return the original value to catch out-of-bounds controllers
        return controller;
    }

    for (uint8 i = 0; i < CAN_ARC_CTRL_CONFIG_CNT; i++) {
        if (Can_Global.config->CanConfigSetPtr->CanController[i].CanControllerId == controller) {
            return i;
        }
    }
    return controller;
}

static inline uint8 ilog2_64(uint64 val) {
    uint32 t = (uint32)(val >> 32);

    if (t != 0) {
        return ilog2(t) + 32;
    }

    return ilog2((uint32)(0xFFFFFFFFuL & val));
}

static inline const Can_HardwareObjectType * Can_FindTxHoh(Can_HwHandleType hth) {
    const Can_HardwareObjectType * hoh = &Can_Global.config->CanConfigSetPtr->ArcCanHardwareObjects[hth];
    if ((hoh->CanObjectType != CAN_OBJECT_TYPE_TRANSMIT) || (hoh->CanObjectId != hth)) {
        return NULL;
    }
    return hoh;
}

static inline const Can_HardwareObjectType * Can_FindHoh(Can_HwHandleType handle) {
    return &Can_Global.config->CanConfigSetPtr->ArcCanHardwareObjects[handle];
}

static inline uint8 Can_FindControllerId(Can_HwHandleType handle) {
    const Can_HardwareObjectType * hoh = &Can_Global.config->CanConfigSetPtr->ArcCanHardwareObjects[handle];
    return hoh->ArcCanControllerId;
}

static void Can_SetId(Can_IdTypeType idType, Can_RegisterType * regs, const Can_PduType *PduInfo) {

    if (idType == CAN_ID_TYPE_STANDARD) {
        /* Standard ID */
        regs->IFx[CAN_REG_IF_1].ARB |= (PduInfo->id & STD_ID_MASK) << CAN_REG_IFX_ARB_STDID_BIT;
    } else if (idType == CAN_ID_TYPE_EXTENDED) {
        /* Extended ID */
        regs->IFx[CAN_REG_IF_1].ARB |= PduInfo->id & EXT_ID_MASK;
    } else {
        /* Mixed ID */
        if ((PduInfo->id & EXT_ID_BIT) == EXT_ID_BIT) {
            /* Extended ID */
            regs->IFx[CAN_REG_IF_1].ARB |= (1uL << CAN_REG_IFX_ARB_XTD_BIT);
            regs->IFx[CAN_REG_IF_1].ARB |= PduInfo->id & EXT_ID_MASK;
        } else {
            /* Standard ID */
            regs->IFx[CAN_REG_IF_1].ARB &= ~(1uL << CAN_REG_IFX_ARB_XTD_BIT);
            regs->IFx[CAN_REG_IF_1].ARB |= (PduInfo->id & STD_ID_MASK) << CAN_REG_IFX_ARB_STDID_BIT;
        }
    }
}

/**
 * @brief Can_Hw_DisableControllerInterrupts Disables interrupts in the hardware.
 * Does not perform any other logic like changing the disable interrupt count.
 * @param Controller Hardware index of the controller.
 */
static void Can_Hw_DisableControllerInterrupts(uint8 Controller) {

    Can_RegisterType *canCtrlRegs = CanRegs[Controller];

    // Set init bit in CTL
    canCtrlRegs->CTL |= (1uL << CAN_REG_CTL_INIT_BIT);

    canCtrlRegs->CTL &= ~CAN_CTL_INTERRUPT_MASK;

    // Clear init bit in CTL
    canCtrlRegs->CTL &= ~(1uL << CAN_REG_CTL_INIT_BIT);
}

/**
 * @brief Can_Hw_EnableControllerInterrupts Enables the interrupts in the hardware.
 * Does not perform any other logic like changing the disable interrupt count.
 * @param Controller Hardware index of the controller.
 */
static void Can_Hw_EnableControllerInterrupts(uint8 Controller) {

    Can_RegisterType *canCtrlRegs = CanRegs[Controller];

    // Set init bit in CTL
    canCtrlRegs->CTL |= (1uL << CAN_REG_CTL_INIT_BIT);

    /* Set IE */
    canCtrlRegs->CTL |= CAN_CTL_INTERRUPT_MASK;

    // Clear init bit in CTL
    canCtrlRegs->CTL &= ~(1uL << CAN_REG_CTL_INIT_BIT);
}

/**
 * This function will handle fifo buffers as well as individual message rx objects.
 * Note that fifos must use consecutive message objects.
 *
 */
static inline void Can_HandleRxOk(uint8 MsgObjectNr, const Can_ControllerConfigType * controllerConfig, const Can_HardwareObjectType * hrh) {
    uint32 MsgId;
    uint8 MsgDlc;
    uint8 DataByteIndex;
    uint8 *SduPtr;
    uint32 mc;
    uint32 arb;


    Can_RegisterType * canRegs = CanRegs[controllerConfig->CanControllerId];

    do {
        // Setup hardware to read arbitration, control and data Bits of the message object.
        // Clear IntPnd and Tx

        canRegs->IFx[CAN_REG_IF_2].COM = (1uL << CAN_REG_IFX_COM_DATAB_BIT)
                | (1uL << CAN_REG_IFX_COM_DATAA_BIT)
                | (1uL << CAN_REG_IFX_COM_NEWDAT_BIT)
                | (1uL << CAN_REG_IFX_COM_CLEARINTPEND_BIT)
                | (1uL << CAN_REG_IFX_COM_CONTROL_BIT)
                | (1uL << CAN_REG_IFX_COM_ARB_BIT)
                | (MsgObjectNr);

        DCAN_WAIT_UNTIL_NOT_BUSY_NO_RV(controllerConfig->CanControllerId, CAN_REG_IF_2);

        // Read message control
        mc = canRegs->IFx[CAN_REG_IF_2].MC;
        arb = canRegs->IFx[CAN_REG_IF_2].ARB;

        // Is there a new message waiting?
        if ((mc & (1uL << DCAN_MC_NEWDAT)) == (1uL << DCAN_MC_NEWDAT)) {
            /* Extended Id */
            /** @req 4.1.2/SWS_Can_00423 */
            if ((arb & (1uL << CAN_REG_IFX_ARB_XTD_BIT)) == (1uL << CAN_REG_IFX_ARB_XTD_BIT)) {
                /* Bring Id to standardized format (MSB marks extended Id) */
                MsgId = (arb & EXT_ID_MASK) | EXT_ID_BIT;

            } else { /* Standard Id */
                /* Bring Id to standardized format (MSB marks extended Id) */
                MsgId = (arb >> CAN_REG_IFX_MASK_STDMSK_BIT) & STD_ID_MASK;
            }

            /* DLC (Max 8) */
            MsgDlc = mc & CAN_REG_MC_DLC_MASK;
            if (MsgDlc > 8) {
                MsgDlc = 8;
            }

            /* Let SduPtr point to Shadow Buffer */
            uint8 ix = getControllerConfigIdx(controllerConfig->CanControllerId);
            SduPtr = RxShadowBuf[ix];

            /* Copy Message Data to Shadow Buffer */
            for (DataByteIndex = 0; DataByteIndex < MsgDlc; DataByteIndex++) {
#if defined(CFG_JACINTO)
                SduPtr[DataByteIndex] = canRegs->IFx[CAN_REG_IF_2].DATx[DataByteIndex];
#elif defined(CFG_TMS570)
                SduPtr[DataByteIndex] = canRegs->IFx[CAN_REG_IF_2].DATx[ElementIndex[DataByteIndex]];
#else
#error DCAN not supported for the used MCU.
#endif
            }

            /* Indicate successful Reception */
            /** @req 4.1.2/SWS_Can_00279 */
            /** @req 4.1.2/SWS_Can_00396 */
            CanIf_RxIndication(hrh->CanObjectId, MsgId, MsgDlc, SduPtr);

            if ((mc & (1uL << DCAN_MC_EOB)) == (1uL << DCAN_MC_EOB)) {
                break; // We have parsed the last object of this FIFO.
            }

        } else {
            break; // There is no new data in the fifo.

        }
        MsgObjectNr++;
    } while ((mc & (1uL << DCAN_MC_EOB)) == 0uL);
}

static inline void Can_HandleTxOk(CanControllerIdType controllerNr, uint8 MsgNr) {
    Can_UnitType *canUnit = GET_PRIVATE_DATA(controllerNr);

    /** @req 4.1.2/SWS_Can_00033 */
    /* Clear busy flag */
    canUnit->mxBoxBusyMask &= ~(1uLL << (MsgNr - 1));

    /** @req 4.1.2/SWS_Can_00016 */
    CanIf_TxConfirmation(canUnit->transmittedPduIds[(MsgNr - 1)]);
}

static inline void Can_HandleBusOff(CanControllerIdType controllerNr) {
    /** @req 4.1.2/SWS_Can_00020 */
    /** @req 4.1.2/SWS_Can_00272 */
    /** @req 4.1.2/SWS_Can_00273 */
    //This will also indicate controller mode to CanIF, it probably should not
    Can_SetControllerMode(controllerNr, CAN_T_STOP); // CANIF272
}

static uint32 canInterruptErrors = 0;
static inline void Can_HandleInterruptError(void) {
    canInterruptErrors++;
}

static void Can_InterruptHandler(CanControllerIdType controllerNr) {

    const Can_ControllerConfigType * controllerConfig = GET_CONTROLLER_CONFIG(controllerNr);
    Can_RegisterType * canRegs = CanRegs[controllerConfig->CanControllerId];

    uint32 ir = canRegs->IR;

    /* Interrupt from status register */
    if ((ir & CAN_REG_IR_INT0ID_MASK) == CAN_REG_IR_BUSEVENT) {
        uint32 sr = canRegs->SR;

        if ((sr & (1uL << CAN_REG_ES_TXOK_BIT)) == (1uL << CAN_REG_ES_TXOK_BIT)) {
            Can_HandleInterruptError();

        } else if ((sr & (1uL << CAN_REG_ES_RXOK_BIT)) == (1uL << CAN_REG_ES_RXOK_BIT)) {
            Can_HandleInterruptError(); // This is not the way to handle rx interrupts for us.

        } else if ((sr & (1uL << CAN_REG_ES_BOFF_BIT)) == (1uL << CAN_REG_ES_BOFF_BIT)) {
            Can_HandleBusOff(controllerNr);
            CanIf_ControllerBusOff(controllerNr);

        } else if ((sr & (1uL << CAN_REG_ES_WKPEND_BIT)) == (1uL << CAN_REG_ES_WKPEND_BIT)) {
            /* No support for wakeup. */

        } else {
            /* Do nothing. MISRA-C compliance. */
        }

    } else {

        /* ir contains the message object number causing the interrupt */
        Can_HwHandleType hohHandle = controllerConfig->Can_Arc_MailBoxToHrh[ir - 1];
        const Can_HardwareObjectType * hoh = Can_FindHoh(hohHandle);

        if (hoh->CanObjectType == CAN_OBJECT_TYPE_RECEIVE) {
            Can_HandleRxOk((uint8) (ir & CAN_REG_IR_INT0ID_MSG_MASK), controllerConfig, hoh);

        } else {
            Can_HandleTxOk(controllerNr, (uint8) (ir & CAN_REG_IR_INT0ID_MSG_MASK));
        }

        /* Clear interrupt pending flag. */
        DCAN_WAIT_UNTIL_NOT_BUSY_NO_RV(controllerConfig->CanControllerId, CAN_REG_IF_2);

        canRegs->IFx[CAN_REG_IF_2].COM = (1uL << CAN_REG_IFX_COM_CLEARINTPEND_BIT) | ir;

    }
}

static ISR(Can1_Level0InterruptHandler) {
    Can_InterruptHandler(DCAN1);
}

static ISR(Can2_Level0InterruptHandler) {
    Can_InterruptHandler(DCAN2);
}

#if defined(CFG_TMS570)
static ISR(Can3_Level0InterruptHandler) {
    Can_InterruptHandler(DCAN3);
}
#endif

#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
static inline void Can_InstallInterruptHandlers(const Can_ControllerConfigType * ctrl) {

#if defined (CFG_TMS570)
    if (ctrl->CanControllerId == DCAN1) {
        ISR_INSTALL_ISR2("DCAN1Level0", Can1_Level0InterruptHandler, CAN1_LVL0_INT, CAN_IRQ_PRIORITY, 0);
    } else if (ctrl->CanControllerId == DCAN2) {
        ISR_INSTALL_ISR2("DCAN2Level0", Can2_Level0InterruptHandler, CAN2_LVL0_INT, CAN_IRQ_PRIORITY, 0);
    } else if (ctrl->CanControllerId == DCAN3) {
        ISR_INSTALL_ISR2("DCAN3Level0", Can3_Level0InterruptHandler, CAN3_LVL0_INT, CAN_IRQ_PRIORITY, 0);
    } else {
        /* Do nothing. */
    }
#elif defined(CFG_JACINTO)
    if (ctrl->CanControllerId == DCAN1) {
        ISR_INSTALL_ISR2("DCAN1Level0", Can1_Level0InterruptHandler, DCAN0_IRQ_INT0, CAN_IRQ_PRIORITY, 0);
    } else if (ctrl->CanControllerId == DCAN2) {
        ISR_INSTALL_ISR2("DCAN2Level0", Can2_Level0InterruptHandler, DCAN1_IRQ_INT0, CAN_IRQ_PRIORITY, 0);
    } else {
        /* Do nothing. */
    }
#else
#error DCAN not supported for the used MCU.
#endif
}
#endif /* !defined(CFG_DRIVERS_USE_CONFIG_ISRS) */


static inline uint32 Can_CalculateBTR(const Can_ControllerConfigType * ctrl) {

#if defined(CFG_TMS570)
    uint32 clock = Mcu_Arc_GetPeripheralClock(PERIPHERAL_CLOCK_CAN);
#elif defined(CFG_JACINTO)
    uint32 clock = Mcu_Arc_GetPeripheralClock(PERIPHERAL_CLOCK_DCAN);
#else
#error DCAN not supported for the used MCU.
#endif
    uint32 tseg1 = ctrl->CanControllerPropSeg + ctrl->CanControllerSeg1 - 1;
    uint32 tseg2 = ctrl->CanControllerSeg2 - 1;

    uint32 ntq = tseg1 + tseg2 + 1 + 1 + 1;
    uint32 brp = (clock / (ctrl->CanControllerDefaultBaudrate * 1000 * ntq)) - 1;

    /* Verify that the values for propagation and phase segments work by checking that we get
     * the original clock value back if we go backwards. */
    uint32 clockCheck = (brp + 1) * (ctrl->CanControllerDefaultBaudrate * 1000 * ntq);
    CONFIG_ASSERT(clockCheck == clock);

    uint32 brpStandard = brp & CAN_REG_BTR_BRP_MASK;
    uint32 brpExtended = (brp & CAN_REG_BTR_BRPE_MASK) >> CAN_REG_BTR_BRPE_RSHIFT;

    /* No need to set SJW if it is 0 (the actual value will be 1 not 0). */
    uint32 retVal = (
            brpStandard |
            (brpExtended << CAN_REG_BTR_BRPE_OFFSET) |
            (tseg1 << CAN_REG_BTR_TSEG1_OFFSET) |
            (tseg2 << CAN_REG_BTR_TSEG2_OFFSET));

    return retVal;
}

static inline void Can_InitHardwareObjects( const Can_ControllerConfigType * controllerConfig) {
    uint32 rx;
    uint32 tx;
    uint32 extended;

    Can_RegisterType * canCtrlRegs = CanRegs[controllerConfig->CanControllerId];
    /* Configure the HOHs for this controller. */
    const Can_HardwareObjectType* hoh;
    hoh = controllerConfig->Can_Arc_Hoh;
    hoh--;
    do {
        hoh++;

        if (hoh->ArcCanControllerId != controllerConfig->CanControllerId) {
            continue;
        }

        if ((hoh->CanObjectType == CAN_OBJECT_TYPE_RECEIVE)) {
            rx = 1;
            tx = 0;
        } else {
            rx = 0;
            tx = 1;
        }

        if (hoh->CanIdType == CAN_ID_TYPE_EXTENDED) {
            extended = 1;
        } else {
            extended = 0;
        }

        /* For every message object in this hoh */
        uint64  mbMask = hoh->ArcMailboxMask;
        uint8   mbNr = 0;
        uint8 mbN = 0;
        for (; mbMask; mbMask &= ~(1uLL << mbNr)) {
            mbNr = ilog2_64(mbMask);
            mbN++;

            /* Check if this is the last message box for this hoh. */
            uint32 eob = 1;
            if ((hoh->CanObjectType == CAN_OBJECT_TYPE_RECEIVE) && (mbN != (hoh->Can_Arc_NrMessageBoxes))) {
                /* EndOfBlock Bit will not be set */
                eob = 0;
            }

            if (rx == 1u) {
                /* Setup mask register */
                if(extended == 0U) {
                    canCtrlRegs->IFx[CAN_REG_IF_1].MASK = (hoh->CanHwFilterMask & STD_ID_MASK) << CAN_REG_IFX_MASK_STDMSK_BIT;
                    canCtrlRegs->IFx[CAN_REG_IF_1].ARB = (hoh->CanHwFilterCode & STD_ID_MASK) << CAN_REG_IFX_ARB_STDID_BIT;
                } else {
                    canCtrlRegs->IFx[CAN_REG_IF_1].MASK = hoh->CanHwFilterMask & EXT_ID_MASK;
                    canCtrlRegs->IFx[CAN_REG_IF_1].ARB = hoh->CanHwFilterCode & EXT_ID_MASK;
                }

                canCtrlRegs->IFx[CAN_REG_IF_1].MASK |= extended << CAN_REG_IFX_MASK_MXTD_BIT;
                canCtrlRegs->IFx[CAN_REG_IF_1].MASK |= rx << CAN_REG_IFX_MASK_MDIR_BIT;
            }
            /* Setup arbitration register */
            canCtrlRegs->IFx[CAN_REG_IF_1].ARB |= (1uL << CAN_REG_IFX_ARB_MSGVAL_BIT)
                                    | (extended << CAN_REG_IFX_ARB_XTD_BIT)
                                    | (tx << CAN_REG_IFX_ARB_DIR_BIT);

            /* Setup message control register */
            canCtrlRegs->IFx[CAN_REG_IF_1].MC = IF_MC_MASK(8uL, rx, rx, tx, eob);

            /* Setup command register */
            canCtrlRegs->IFx[CAN_REG_IF_1].COM = 0x00F00000uL | (((uint32) mbNr) + 1);

            DCAN_WAIT_UNTIL_NOT_BUSY_NO_RV(controllerConfig->CanControllerId, CAN_REG_IF_1);
        }
    } while (!hoh->Can_Arc_EOL);
}

void Can_Init(const Can_ConfigType *Config) {

    /** @req 4.1.2/SWS_Can_00053 *//* Don't change registers for controllers not used. */
    /** @req 4.1.2/SWS_Can_00239 *//* Init all on chip hardware */
    /** @req 4.1.2/SWS_Can_00250 *//* Initialize variables, init controllers. */
    /** @req 4.1.2/SWS_Can_00021 */
    /** @req 4.1.2/SWS_Can_00291 */
    /** @req 4.1.2/SWS_Can_00174 */
    /** @req 4.1.2/SWS_Can_00175 */
    /** @req 4.1.2/SWS_Can_00223 */
    /* DET Error Check */
    VALIDATE_NO_RV( (Can_Global.initRun == CAN_UNINIT), CAN_INIT_SERVICE_ID, CAN_E_TRANSITION );
    VALIDATE_NO_RV( (Config != NULL), CAN_INIT_SERVICE_ID, CAN_E_PARAM_POINTER );

    SchM_Enter_Can_EA_0();

    Can_Global.config = Config;

    /** @req 4.1.2/SWS_Can_00245 */
    for (uint8 canCtrlNr = 0; canCtrlNr < CAN_CONTROLLER_CNT; canCtrlNr++) {

        const Can_ControllerConfigType * controllerConfig = GET_CONTROLLER_CONFIG(canCtrlNr);

        // Assign the configuration channel used later..
        Can_Global.channelMap[controllerConfig->CanControllerId] = canCtrlNr;
        Can_Global.configured |= (1uL << controllerConfig->CanControllerId);

        /** @req 4.1.2/SWS_Can_00259 *//* Reset the controller. The device goes to Configuration Mode immediately. */
        Can_UnitType * canUnit = GET_PRIVATE_DATA(controllerConfig->CanControllerId);
        canUnit->state = CANIF_CS_STOPPED;
        canUnit->pendingStateIndication = CAN_CTRL_INDICATION_NONE;
        canUnit->mxBoxBusyMask = 0;
        memset(&canUnit->transmittedPduIds[0], 0, sizeof(canUnit->transmittedPduIds));
        /* MaxBoxes - initialized statically, never changes. */
        canUnit->WakeupSrc = 0;

        Can_RegisterType *canCtrlRegs = CanRegs[controllerConfig->CanControllerId];

        canCtrlRegs->CTL |= CAN_REG_CTL_INIT_MASK;
        canCtrlRegs->CTL |= (1uL << CAN_REG_CTL_SWR_BIT); /* Perform sw reset */

        /* DAR bit should be 0 for automatic retransmission so nothing to set.
         * WUBA off - No detection of dominant CAN bus while in power down. */
        canCtrlRegs->CTL = (
                (1uL << CAN_REG_CTL_INIT_BIT) | // Init enable
                (1uL << CAN_REG_CTL_CCE_BIT)  | // CCE enable
                (1uL << CAN_REG_CTL_ABO_BIT)  | // ABO enable
                (CAN_REG_CTL_PARITY_DISABLED << CAN_REG_CTL_PARITY_BIT) | // Parity disable
                CAN_CTL_INTERRUPT_MASK |
                (controllerConfig->Can_Arc_Loopback << CAN_REG_CTL_TEST_MODE_BIT) // Test mode enable/disable
                );

        while ((canCtrlRegs->CTL & (1uL << CAN_REG_CTL_INIT_BIT)) == 0uL) {};

        /* Clear all pending error flags and reset current status - only reading clears the flags */
        canCtrlRegs->SR = canCtrlRegs->SR;

        /* Test Mode only for Development time: Silent Loopback */
        if (controllerConfig->Can_Arc_Loopback == TRUE) {
            canCtrlRegs->TR = (1uL << CAN_REG_TR_LBACK_BIT);
        }

        Can_InitHardwareObjects(controllerConfig);

        /* Set CCE Bit to allow access to BitTiming Register (Init already set, in mode "stopped") */
        canCtrlRegs->CTL |= (1uL << CAN_REG_CTL_CCE_BIT);
        /* Set Bit Timing Register */
        canCtrlRegs->BTR = Can_CalculateBTR(controllerConfig);

        /* Turn off write access to configuration registers. */
        canCtrlRegs->CTL &= ~(1uL << CAN_REG_CTL_CCE_BIT);

        /* Normal operation. */
        canCtrlRegs->CTL &= ~(1uL << CAN_REG_CTL_INIT_BIT);

#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
        Can_InstallInterruptHandlers(controllerConfig);
#endif
    }

    SchM_Exit_Can_EA_0();

    /** @req 4.1.2/SWS_Can_00246 *//* Should be done after initializing all controllers */
    Can_Global.initRun = CAN_READY;
}

void Can_Arc_DeInit(void) {

    Can_UnitType *canUnit;
    const Can_ControllerConfigType *canHwConfig;
    uint8 ctlrId;

    if (Can_Global.initRun == CAN_UNINIT) {
        return;
    }

    for (uint8 configId = 0; configId < CAN_ARC_CTRL_CONFIG_CNT; configId++) {

        canHwConfig = GET_CONTROLLER_CONFIG(configId);
        ctlrId = canHwConfig->CanControllerId;

        Can_DisableControllerInterrupts(ctlrId);

        canUnit = GET_PRIVATE_DATA(ctlrId);
        canUnit->state = CANIF_CS_UNINIT;
        canUnit->pendingStateIndication = CAN_CTRL_INDICATION_NONE;
        canUnit->mxBoxBusyMask = 0;
        memset(&canUnit->transmittedPduIds[0], 0, sizeof(canUnit->transmittedPduIds));
        /* MaxBoxes - initialized statically, never changes. */
        canUnit->WakeupSrc = 0;

        /* Reset the lock count. */
           IntDisableCount[configId] = 0;
    }

    Can_Global.config = NULL;
    Can_Global.initRun = CAN_UNINIT;

    return;
}

Std_ReturnType Can_ChangeBaudrate(uint8 Controller, const uint16 Baudrate) {
    /** @req 4.0.3/CAN449 *//** @req 4.1.2/SWS_Can_00449 */

    /** @req 4.0.3/CAN450 *//** @req 4.1.2/SWS_Can_00450 */
    VALIDATE_STD_RV( (Can_Global.initRun == CAN_READY), CAN_CHANGE_BAUD_RATE_SERVICE_ID, CAN_E_UNINIT );

    /** @req 4.0.3/CAN452 *//** @req 4.1.2/SWS_Can_00452 */
    VALIDATE_STD_RV( (Controller < CAN_ARC_CTRL_CONFIG_CNT), CAN_CHANGE_BAUD_RATE_SERVICE_ID, CAN_E_PARAM_CONTROLLER );

    /** @req 4.0.3/CAN451 *//** @req 4.1.2/SWS_Can_00451 */
    VALIDATE_STD_RV(Can_CheckBaudrate(Controller, Baudrate) == E_OK, CAN_CHANGE_BAUD_RATE_SERVICE_ID, CAN_E_PARAM_BAUDRATE);

    /** @req 4.0.3/CAN453 *//** @req 4.1.2/SWS_Can_00453 */
    VALIDATE_STD_RV( ((GET_PRIVATE_DATA(Controller))->state == CANIF_CS_STOPPED), CAN_CHANGE_BAUD_RATE_SERVICE_ID, CAN_E_TRANSITION );

    return E_NOT_OK ; // Not implemented.
}

Can_ReturnType Can_SetControllerMode(uint8 Controller, Can_StateTransitionType Transition) {

    Can_ReturnType status = CAN_OK;
    uint32 ErrCounter = CAN_TIMEOUT_DURATION;
    uint32 RegBuf;
    /** @req 4.1.2/SWS_Can_00017 */
    /** @req 4.1.2/SWS_Can_00230 */
    /** @req 4.0.3/CAN199 *//** @req 4.1.2/SWS_Can_00199 */
    VALIDATE( (getControllerConfigIdx(Controller) < CAN_CONTROLLER_CNT), CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_PARAM_CONTROLLER );

    /** @req 4.0.3/CAN198 *//** @req 4.1.2/SWS_Can_00198 */
    VALIDATE( (Can_Global.initRun == CAN_READY), CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_UNINIT );

    Can_UnitType *canUnit = GET_PRIVATE_DATA(Controller);
    const Can_ControllerConfigType * controllerConfig = GET_CONTROLLER_CONFIG(Controller);
    Can_RegisterType *canCtrlRegs = CanRegs[controllerConfig->CanControllerId];

    canUnit->pendingStateIndication = CAN_CTRL_INDICATION_NONE;

    /** @req 4.1.2/SWS_Can_00417 */
    switch (Transition) {
    case CAN_T_START:
        /** @req 4.0.3/CAN200 *//** @req 4.1.2/SWS_Can_00200 */
        /** @req 4.0.3/CAN409 *//** @req 4.1.2/SWS_Can_00409 */
        /** @req 4.1.2/SWS_Can_00261 */
        VALIDATE(canUnit->state == CANIF_CS_STOPPED, CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_TRANSITION);

        SchM_Enter_Can_EA_0();

        /* Clear Init Bit */
        canCtrlRegs->CTL &= ~CAN_REG_CTL_INIT_MASK;
        /* Clear Status Register */
        canCtrlRegs->SR = (
                CAN_REG_ES_LEC_MASK |
                (1uL << CAN_REG_ES_TXOK_BIT) |
                (1uL << CAN_REG_ES_RXOK_BIT) |
                (1uL << CAN_REG_ES_PER_BIT)
                );

        /** @req 4.1.2/SWS_Can_00196 */
        canUnit->state = CANIF_CS_STARTED;

        /** @req 4.1.2/SWS_Can_00425 */
        /* Call Can_Hw_EnableControllerInterrupts instead of
         * Can_EnableControllerInterrupts so as not to
         * change the lock counter. */
        if (IntDisableCount[Controller] == 0) {
            Can_Hw_EnableControllerInterrupts(Controller);
        }

        canUnit->pendingStateIndication = CAN_CTRL_INDICATION_PENDING_START;

        SchM_Exit_Can_EA_0();

        break;

    case CAN_T_WAKEUP:
        /** @req 4.0.3/CAN412 *//** @req 4.1.2/SWS_Can_00412 */
        VALIDATE(((canUnit->state == CANIF_CS_SLEEP) || (canUnit->state == CANIF_CS_STOPPED)), CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_TRANSITION);

        SchM_Enter_Can_EA_0();

        /* Clear Power down bit */
        canCtrlRegs->CTL &= ~(1uL << CAN_REG_CTL_PDR_BIT);
        canUnit->state = CANIF_CS_STOPPED;
        canUnit->pendingStateIndication = CAN_CTRL_INDICATION_PENDING_STOP;

        SchM_Exit_Can_EA_0();

        break;

    case CAN_T_STOP:

        SchM_Enter_Can_EA_0();

        /** @req 4.1.2/SWS_Can_00263 */
        /** @req 4.1.2/SWS_Can_00197 *//* Disable interrupts */
        /** @req 4.1.2/SWS_Can_00282 */
        /** @req 4.1.2/SWS_Can_00283 */
        /* Set Init Bit */
        canCtrlRegs->CTL |= CAN_REG_CTL_INIT_MASK;
        canUnit->state = CANIF_CS_STOPPED;

        /** @req 4.1.2/SWS_Can_00426 */
        /* Call Can_Hw_DisableControllerInterrupts instead of
         * Can_DisableControllerInterrupts so as not to
         * change the lock counter.
         * If the disable count is bigger than 0 then interrupts
         * already have been disabled. */
        if (IntDisableCount[Controller] == 0) {
            Can_Hw_DisableControllerInterrupts(Controller);
        }

        canUnit->pendingStateIndication = CAN_CTRL_INDICATION_PENDING_STOP;

        SchM_Exit_Can_EA_0();

        break;

    case CAN_T_SLEEP:
        /** @req 4.0.3/CAN411 *//** @req 4.1.2/SWS_Can_00411 */
        /** @req 4.1.2/SWS_Can_00257 */
        /** @req 4.1.2/SWS_Can_00265 */
        VALIDATE(canUnit->state == CANIF_CS_STOPPED, CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_TRANSITION);

        SchM_Enter_Can_EA_0();

        /* Set Power down bit */
        canCtrlRegs->CTL |= (1uL << CAN_REG_CTL_PDR_BIT);
        /* Save actual Register status */
        RegBuf = canCtrlRegs->CTL;
        /* Disable WUBA and Status Interrupts */
        canCtrlRegs->CTL &= ~((1uL << CAN_REG_CTL_WUBA_BIT) | (1uL << CAN_REG_CTL_SIE_BIT));
        /* Wait until Local Power Down Mode acknowledged */
        while ((canCtrlRegs->SR & (1uL << CAN_REG_ES_PDA_BIT)) == 0) {
            /* Check if a WakeUp occurs */
            if ((canCtrlRegs->SR & (1uL << CAN_REG_ES_WKPEND_BIT)) == (1uL << CAN_REG_ES_WKPEND_BIT)) {
                status = CAN_NOT_OK;
                break;
            }
            ErrCounter--;
            if (ErrCounter == 0) {
                Dem_ReportErrorStatus(DemConf_DemEventParameter_CAN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
                ErrCounter = CAN_TIMEOUT_DURATION;
                status = CAN_NOT_OK;
                break;
            }
        }
        /* Reset Control Register */
        canCtrlRegs->CTL = RegBuf;
        canUnit->state = CANIF_CS_SLEEP;
        canUnit->pendingStateIndication = CAN_CTRL_INDICATION_PENDING_SLEEP;

        SchM_Exit_Can_EA_0();

        break;

    default:
        /** @req 4.0.3/CAN200 *//** @req 4.1.2/SWS_Can_00200 */
        VALIDATE(canUnit->state == CANIF_CS_STOPPED, CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_TRANSITION);
        break;
    }

    return status;
}

void Can_DisableControllerInterrupts(uint8 Controller) {

    /** @req 4.0.3/CAN206 *//** @req 4.1.2/SWS_Can_00206*/
    /** @req 4.1.2/SWS_Can_00049*/
    /** @req 4.1.2/SWS_Can_00202*/
    /** @req 4.1.2/SWS_Can_00205 */
    /** @req 4.1.2/SWS_Can_00231 */
    VALIDATE_NO_RV( (getControllerConfigIdx(Controller) < CAN_CONTROLLER_CNT), CAN_DISABLECONTROLLERINTERRUPTS_SERVICE_ID, CAN_E_PARAM_CONTROLLER );

    /** @req 4.0.3/CAN209 *//** @req 4.1.2/SWS_Can_00209 */
    VALIDATE_NO_RV( (Can_Global.initRun == CAN_READY), CAN_DISABLECONTROLLERINTERRUPTS_SERVICE_ID, CAN_E_UNINIT );

    SchM_Enter_Can_EA_0();

    /** @req 4.1.2/SWS_Can_00049 */
    if (IntDisableCount[Controller] == 0) {
        Can_Hw_DisableControllerInterrupts(Controller);
    }

    /* Increment Disable Counter */
    IntDisableCount[Controller]++;

    SchM_Exit_Can_EA_0();
}

void Can_EnableControllerInterrupts(uint8 Controller) {
    /** @req 4.0.3/CAN210 *//** @req 4.1.2/SWS_Can_00210 */
    /** @req 4.1.2/SWS_Can_00050 */
    /** @req 4.1.2/SWS_Can_00232 */
    VALIDATE_NO_RV( (getControllerConfigIdx(Controller) < CAN_CONTROLLER_CNT), CAN_ENABLECONTROLLERINTERRUPTS_SERVICE_ID, CAN_E_PARAM_CONTROLLER );

    /** @req 4.0.3/CAN209 *//** @req 4.1.2/SWS_Can_00209 */
    VALIDATE_NO_RV( (Can_Global.initRun == CAN_READY), CAN_ENABLECONTROLLERINTERRUPTS_SERVICE_ID, CAN_E_UNINIT );

    SchM_Enter_Can_EA_0();

    /** @req 4.1.2/SWS_Can_00208 */
    if (IntDisableCount[Controller] > 0) {
        if (IntDisableCount[Controller] == 1) {
            Can_Hw_EnableControllerInterrupts(Controller);
        }

        IntDisableCount[Controller]--;
    }

    SchM_Exit_Can_EA_0();
}

Can_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo) {

    uint8 ControllerId;
    uint32 ArbRegValue;
    uint8 DataByteIndex;
    /** @req 4.1.2/SWS_Can_00233 */
    /** @req 4.1.2/SWS_Can_00212 */
    /** @req 4.1.2/SWS_Can_00011 */
    /** @req 4.1.2/SWS_Can_00275 */
    /** @req 4.0.3/CAN216 *//** @req 4.1.2/SWS_Can_00216 */
    VALIDATE( (Can_Global.initRun == CAN_READY), CAN_WRITE_SERVICE_ID, CAN_E_UNINIT );
    /** @req 4.0.3/CAN219 *//** @req 4.1.2/SWS_Can_00219 */
    VALIDATE( (PduInfo != NULL), CAN_WRITE_SERVICE_ID, CAN_E_PARAM_POINTER );
    VALIDATE( (PduInfo->sdu != NULL), CAN_WRITE_SERVICE_ID, CAN_E_PARAM_POINTER );
    /** @req 4.0.3/CAN218 *//** @req 4.1.2/SWS_Can_00218 */
    VALIDATE( (PduInfo->length <= 8), CAN_WRITE_SERVICE_ID, CAN_E_PARAM_DLC );

    ControllerId = Can_FindControllerId(Hth);
    const Can_HardwareObjectType *hoh = Can_FindTxHoh(Hth);

    /** @req 4.0.3/CAN217 *//** @req 4.1.2/SWS_Can_00217 */
    VALIDATE( (Hth < NUM_OF_HOHS ), CAN_WRITE_SERVICE_ID, CAN_E_PARAM_HANDLE );
    VALIDATE( (hoh != NULL ), CAN_WRITE_SERVICE_ID, CAN_E_PARAM_HANDLE );

    VALIDATE( (hoh->CanObjectType == CAN_OBJECT_TYPE_TRANSMIT ), CAN_WRITE_SERVICE_ID, CAN_E_PARAM_HANDLE );

    const Can_ControllerConfigType * controllerConfig = GET_CONTROLLER_CONFIG(ControllerId);
    Can_UnitType * canUnit = GET_PRIVATE_DATA(controllerConfig->CanControllerId);
    Can_RegisterType *canCtrlRegs = CanRegs[controllerConfig->CanControllerId];
    Can_ReturnType ret = CAN_OK;

    // We cannot allow an interrupt or other task to play with the COM, MC and ARB registers here.
    SchM_Enter_Can_EA_0();

    /* Check if any mailbox is free. If not, return CAN_BUSY. */
    /** @req 4.1.2/SWS_Can_00039 */
    if (hoh->ArcMailboxMask != (hoh->ArcMailboxMask & canUnit->mxBoxBusyMask)) {

        /* Bring Id Value to appropriate format and set ArbRegValue */
        if (hoh->CanIdType == CAN_ID_TYPE_EXTENDED) {
            /* MsgVal, Ext, Transmit, Extended Id */
            ArbRegValue = (
                    (1uL << CAN_REG_IFX_ARB_MSGVAL_BIT) |
                    (1uL << CAN_REG_IFX_ARB_XTD_BIT) |
                    (1uL << CAN_REG_IFX_ARB_DIR_BIT));

        } else {
            /* MsgVal, Std, Transmit, Standard Id */
            ArbRegValue = (
                    (1uL << CAN_REG_IFX_ARB_MSGVAL_BIT) |
                    (1uL << CAN_REG_IFX_ARB_DIR_BIT));
        }

        DCAN_WAIT_UNTIL_NOT_BUSY(ControllerId, CAN_REG_IF_1);

        /* Set NewDat, TxIE (dep on ControllerConfig), TxRqst, EoB and DLC */
        canCtrlRegs->IFx[CAN_REG_IF_1].MC = IF_MC_MASK((uint32) PduInfo->length, 0uL, 0uL, 1uL, 1uL);

        /* Set ArbitrationRegister */
        canCtrlRegs->IFx[CAN_REG_IF_1].ARB = ArbRegValue;
        Can_SetId(hoh->CanIdType, canCtrlRegs, PduInfo);

        /* Set Databytes */
        /** @req 4.1.2/SWS_Can_00059 */
        /** !req 4.1.2/SWS_Can_00427 */
#if defined(CFG_JACINTO)
        for (DataByteIndex = 0; DataByteIndex < PduInfo->length; DataByteIndex++) {
            canCtrlRegs->IFx[CAN_REG_IF_1].DATx[DataByteIndex] = PduInfo->sdu[DataByteIndex];
        }
#elif defined(CFG_TMS570)
        for (DataByteIndex = 0; DataByteIndex < PduInfo->length; DataByteIndex++) {
            canCtrlRegs->IFx[CAN_REG_IF_1].DATx[ElementIndex[DataByteIndex]] = PduInfo->sdu[DataByteIndex];
        }
#else
#error DCAN not supported for the used MCU.
#endif

        /* Find first free mb box */
        uint64 mbMask = hoh->ArcMailboxMask;
        uint64 mbNr = 0;

        for (; mbMask; mbMask &= ~(1uLL << mbNr)) {

            mbNr = ilog2_64(mbMask);

            if (!(canUnit->mxBoxBusyMask & mbMask)) {
                break;
            }
        }

        canUnit->mxBoxBusyMask |= (1uLL<< mbNr); // Mark selected box as busy.
        /** @req 4.1.2/SWS_Can_00276 */
        canUnit->transmittedPduIds[mbNr] = PduInfo->swPduHandle;

        /* Start transmission to MessageRAM */
        canCtrlRegs->IFx[CAN_REG_IF_1].COM = 0x00BF0000uL | (mbNr + 1);

    } else {
        /** @req 4.1.2/SWS_Can_00214 */
        ret = CAN_BUSY;
    }

    SchM_Exit_Can_EA_0();

    return ret;
}

#if (CAN_USE_WRITE_POLLING == STD_ON)
void Can_MainFunction_Write()
{
#error "Polling write not supported by this driver."
    /** !req 4.0.3/CAN225 *//** !req 4.1.2/SWS_Can_00225 */
    /** !req 4.0.3/CAN031 *//** !req 4.1.2/SWS_Can_00031 */
    /** !req 4.1.2/SWS_Can_00441 */
    /** !req 4.0.3/CAN179 *//** !req 4.1.2/SWS_Can_00179 */
}
#endif

#if (CAN_USE_READ_POLLING == STD_ON)
void Can_MainFunction_Read()
{
#error "Polling read not supported by this driver."
    /** !req 4.0.3/CAN226 *//** !req 4.1.2/SWS_Can_00226 */
    /** !req 4.0.3/CAN108 *//** !req 4.1.2/SWS_Can_00108 */
    /** !req 4.1.2/SWS_Can_00442 */
    /** !req 4.0.3/CAN181 *//** !req 4.1.2/SWS_Can_00181 */
}
#endif

#if (CAN_USE_BUSOFF_POLLING == STD_ON)
void Can_MainFunction_BusOff()
{
#error "Polling bus off not supported by this driver."
    /** !req 4.0.3/CAN227 *//** !req 4.1.2/SWS_Can_00227 */
    /** !req 4.0.3/CAN109 *//** !req 4.1.2/SWS_Can_00109 */
    /** !req 4.0.3/CAN184 *//** !req 4.1.2/SWS_Can_00184 */
}
#endif

#if (CAN_USE_WAKEUP_POLLING == STD_ON)
void Can_MainFunction_Wakeup()
{
#error "Polling wakeup not supported by this driver."
    /** !req 4.0.3/CAN228 *//** !req 4.1.2/SWS_Can_00228 */
    /** !req 4.0.3/CAN112 *//** !req 4.1.2/SWS_Can_00112 */
    /** !req 4.0.3/CAN186 *//** !req 4.1.2/SWS_Can_00186 */
}
#endif

Std_ReturnType Can_CheckBaudrate(uint8 Controller, const uint16 Baudrate) {
    /** @req 4.0.3/CAN454 *//** @req 4.1.2/SWS_Can_00454 *//* API */

    // Checks that the target baudrate is found among the configured
    // baudrates for this controller.
    const Can_ControllerConfigType *config;
    Std_ReturnType supportedBR;

    /** @req 4.0.3/CAN456 UNINIT *//** @req 4.1.2/SWS_Can_00456 */
    VALIDATE_STD_RV( (Can_Global.initRun == CAN_READY), CAN_CHECK_BAUD_RATE_SERVICE_ID, CAN_E_UNINIT );
    /** @req 4.0.3/CAN457 Invalid controller *//** @req 4.1.2/SWS_Can_00457 */
    VALIDATE_STD_RV( ((Can_Global.configured & (1uL << Controller)) == (1uL << Controller)) , CAN_CHECK_BAUD_RATE_SERVICE_ID, CAN_E_PARAM_CONTROLLER );

    /** @req 4.0.3/CAN458 Invalid baudrate value *//** @req 4.1.2/SWS_Can_00458 */
    VALIDATE_STD_RV( Baudrate <= 1000, CAN_CHECK_BAUD_RATE_SERVICE_ID, CAN_E_PARAM_BAUDRATE );

    config = GET_CONTROLLER_CONFIG(Can_Global.channelMap[Controller]);

    // Find the baudrate config for the target baudrate
    supportedBR = E_NOT_OK;
    for (uint16 i = 0; i < config->CanControllerSupportedBaudratesCount; i++) {
        if (config->CanControllerSupportedBaudrates[i].CanControllerBaudRate == Baudrate) {
            supportedBR = E_OK;
            break;
        }
    }

    return supportedBR;
}

void Can_MainFunction_Mode(void) {
    /** @req 4.0.3/CAN368 *//** @req 4.1.2/SWS_Can_00368 *//* API */
    /** @req 4.0.3/CAN369 *//** @req 4.1.2/SWS_Can_00369 *//* Polling */

    /** !req 4.0.3/CAN398 *//** !req 4.1.2/SWS_Can_00398 *//* Blocking call not supported */
    /** !req 4.0.3/CAN371 *//** !req 4.1.2/SWS_Can_00371 *//* Blocking call not supported */
    /** !req 4.0.3/CAN372 *//** !req 4.1.2/SWS_Can_00372 *//* Blocking call not supported */


    /** @req 4.0.3/CAN379 *//** @req 4.1.2/SWS_Can_00379 *//* CAN_E_UNINIT */
    VALIDATE_NO_RV( (Can_Global.initRun == CAN_READY), CAN_MAIN_FUNCTION_MODE_SERVICE_ID, CAN_E_UNINIT );

    /** @req 4.0.3/CAN431 *//* On Uninit, return immediately without prod err */
    if (Can_Global.initRun == CAN_UNINIT) {
        return;
    }

    for (uint8 configId = 0; configId < CAN_ARC_CTRL_CONFIG_CNT; configId++) {
        boolean clearPending = TRUE;
        CanIf_ControllerModeType indicateMode = CANIF_CS_UNINIT;
        //Get the controller from config index and index CanUnit
        const Can_ControllerConfigType * canHwConfig = GET_CONTROLLER_CONFIG(configId);

        Can_UnitType * canUnit = GET_PRIVATE_DATA(canHwConfig->CanControllerId);

        switch (canUnit->pendingStateIndication) {
        case CAN_CTRL_INDICATION_PENDING_START:
            if (canUnit->state == CANIF_CS_STARTED) {
                indicateMode = CANIF_CS_STARTED;
            }
            break;

        case CAN_CTRL_INDICATION_PENDING_STOP:
            if (canUnit->state == CANIF_CS_STOPPED) {
                // Stopped, indicate to upper layer
                indicateMode = CANIF_CS_STOPPED;
            }
            break;

        case CAN_CTRL_INDICATION_PENDING_SLEEP:
            if (canUnit->state == CANIF_CS_SLEEP) {
                // Stopped, indicate to upper layer
                indicateMode = CANIF_CS_SLEEP;
            }
            break;

        case CAN_CTRL_INDICATION_NONE:
        default:
            // No action necessary
            clearPending = FALSE;
            break;
        }
        if ((CANIF_CS_UNINIT != indicateMode) ) {
            /** @req 4.0.3/CAN370 *//** @req 4.1.2/SWS_Can_00370 */
            /** @req 4.0.3/CAN373 *//** @req 4.1.2/SWS_Can_00373 */
#if defined(CFG_CAN_USE_SYMBOLIC_CANIF_CONTROLLER_ID)
            CanIf_ControllerModeIndication(canHwConfig->Can_Arc_CanIfControllerId, indicateMode);
#else
            CanIf_ControllerModeIndication( canHwConfig->CanControllerId, indicateMode);
#endif
        }

        if (clearPending == TRUE) {
            canUnit->pendingStateIndication = CAN_CTRL_INDICATION_NONE;
        }
    }
}

#if ( CAN_VERSION_INFO_API == STD_ON )
void Can_GetVersionInfo( Std_VersionInfoType* versioninfo) {

    /* @req SWS_Can_00224 */
    /* @req SWS_Can_00177 */
    VALIDATE_NO_RV( ( NULL != versioninfo ), CAN_GETVERSIONINFO_SERVICE_ID, CAN_E_PARAM_POINTER);

    versioninfo->vendorID = CAN_VENDOR_ID;
    versioninfo->moduleID = CAN_MODULE_ID;
    versioninfo->sw_major_version = CAN_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = CAN_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = CAN_SW_PATCH_VERSION;
}
#endif

#ifdef HOST_TEST
Std_ReturnType Can_Test_DriverStateIsUninit(void) {
    return (Can_Global.initRun == CAN_UNINIT) ? E_OK : E_NOT_OK;
}

Std_ReturnType Can_Test_DriverStateIsReady(void) {
    return (Can_Global.initRun == CAN_READY) ? E_OK : E_NOT_OK;
}

Std_ReturnType Can_Test_AllUnitsInState(CanIf_ControllerModeType state) {

    for (uint8 canCtrlNr = 0; canCtrlNr < CAN_CONTROLLER_CNT; canCtrlNr++) {

        const Can_ControllerConfigType *controllerConfig = GET_CONTROLLER_CONFIG(canCtrlNr);

        const Can_UnitType *canUnit = GET_PRIVATE_DATA(controllerConfig->CanControllerId);

        if (canUnit->state != state) {
            return E_NOT_OK;
        }
    }

    return E_OK;
}
#endif /* HOST_TEST */
