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

/** @tagSettings DEFAULT_ARCHITECTURE=STM32 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#include "Can.h"
#ifndef USE_CAN_STUB
#include "stm32f10x.h"
#include "stm32f10x_can.h"
#include "Cpu.h"
#include "Mcu.h"
#include "CanIf_Cbk.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#include "arc_assert.h"
#include <stdlib.h>
#include <string.h>
#include "SchM_Can.h"
#include "isr.h"
#include "arc.h"


/* CONFIGURATION NOTES
 * ------------------------------------------------------------------
 * - CanHandleType must be CAN_ARC_HANDLE_TYPE_BASIC
 *   i.e. CanHandleType=CAN_ARC_HANDLE_TYPE_FULL NOT supported
 *   i.e CanIdValue is NOT supported
 * - All CanXXXProcessing must be CAN_ARC_PROCESS_TYPE_INTERRUPT
 *   ie CAN_ARC_PROCESS_TYPE_POLLED not supported
 * - HOH's for Tx are global and Rx are for each controller
 */

/* IMPLEMENTATION NOTES
 * -----------------------------------------------
 * - A HOH us unique for a controller( not a config-set )
 * - Hrh's are numbered for each controller from 0
 * - loopback in HW NOT supported
 * - Only one transmit mailbox is used because otherwise
 *   we cannot use tx_confirmation since there is no way to know
 *   which mailbox caused the tx interrupt. TP will need this feature.
 * - Sleep,wakeup not fully implemented since other modules lack functionality
 */

/* ABBREVATIONS
 *  -----------------------------------------------
 * - Can Hardware unit - One or multiple Can controllers of the same type.
 * - Hrh - HOH with receive definitions
 * - Hth - HOH with transmit definitions
 *
 */

typedef CAN_TypeDef CAN_HW_t;
//-------------------------------------------------------------------

#define GET_CONTROLLER_CONFIG(_controller)	\
                            &Can_Global.config->CanConfigSetPtr->CanController[(_controller)]

#define GET_PRIVATE_DATA(_controller) \
                                    &CanUnit[_controller]

#define GET_CONTROLLER_CNT() (CAN_CONTROLLER_CNT)

//-------------------------------------------------------------------
/** @req 4.0.3/CAN027 */
/** @req 4.1.2/SWS_Can_00091*/
/** @req 4.1.2/SWS_Can_00089*/
/** @req 4.1.2/SWS_Can_00104*/
/** @req 4.1.2/SWS_Can_00039*/
/** @req 4.1.2/SWS_Can_00035*//* No can_cbk.h file */
/** @req 4.1.2/SWS_Can_00079*//* Coding guidelines */
/** @req 4.1.2/SWS_Can_00103*/ /*On power up can module will be in CAN_UNINIT state*/
/** @req 4.1.2/SWS_Can_00220*//* Precompile variant */
/** @req 4.1.2/SWS_Can_00238*//* On-chip controller, does not use other drivers */
/** @req 4.1.2/SWS_Can_00239*//* Init all on chip hardware */
/** @req 4.1.2/SWS_Can_00237*/
/** @req 4.1.2/SWS_Can_00236*/
#if ( CAN_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err, ... ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(CAN_MODULE_ID,0,_api,_err); \
          return __VA_ARGS__;\
        }

#define VALIDATE_NO_RV(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(CAN_MODULE_ID,0,_api,_err); \
          return; \
        }

#define DET_REPORTERROR(_x,_y,_z,_q) (void)Det_ReportError(_x, _y, _z, _q)
#else
#define VALIDATE(_exp,_api,_err, ... )
#define VALIDATE_NO_RV(_exp,_api,_err )
#define DET_REPORTERROR(_x,_y,_z,_q)
#endif

#if defined(USE_DEM)
#define VALIDATE_DEM(_exp,_err,_rv) \
        if( !(_exp) ) { \
           Dem_ReportErrorStatus(_err, DEM_EVENT_STATUS_FAILED); \
          return _rv; \
        }
#else
#define VALIDATE_DEM(_exp,_err,_rv )
#endif

#define AVAIL_TX_MAILBOX_NUM 3
#define BX_CAN_MASTER        0
#define BX_CAN_SLAVE         1
#define AVAILABLE_RX_HWOBJECT 2 // Two fifos
#define AVAILABLE_TX_HWOBJECT 1 // One Tx object containing 3 mailboxes
#if defined (STM32F10X_CL)
#define AVAILABLE_CAN_CONTROLLER  2u
#define SLAVE_START_FILTER_BANK   2u
#else
#define AVAILABLE_CAN_CONTROLLER  1
#endif
#define RX_MAILBOX_IDNTFREG_IDE 4u //IDE field in CAN_RIxR
#define RX_MAILBOX_IDNTFREG_EXTD_IDE 4u //IDE value for Extended Id frames in CAN_RIxR
#define RX_MAILBOX_IDNTFREG_EXTD_MASK_LOWER 0x1FFFU // Lower mask for Extended Id in CAN_RIxR
#define RX_MAILBOX_IDNTFREG_EXTD_MASK_HIGHER 0xFFFFE000U // Higher mask for Extended Id in CAN_RIxR
#define RX_MAILBOX_IDNTFREG_STDID_MASK 0x7FF //Mask for standard id
#define RX_MAILBOX_IDNTFREG_EXTDID_STARTPOS 3u //Bit0 of Extended Id in CAN_RIxR
#define RX_MAILBOX_IDNTFREG_STDID_STARTPOS 5u //Bit0 of Standard Id in CAN_RIxR
#define MASK_STANDARD_ID    0x7FFu
//-------------------------------------------------------------------

typedef enum
{
    CAN_UNINIT = 0,
    CAN_READY
} Can_DriverStateType;

typedef enum {
    CAN_CTRL_INDICATION_NONE,
    CAN_CTRL_INDICATION_PENDING_START,
    CAN_CTRL_INDICATION_PENDING_STOP,
    CAN_CTRL_INDICATION_PENDING_SLEEP /* Sleep is not implemented - but we need a logical sleep mode*/
} Can_CtrlPendingStateIndicationType;

// Mapping between HRH and Controller//HOH
typedef struct Can_Arc_ObjectHOHMapStruct
{
    CanControllerIdType CanControllerRef;    // Reference to controller
    const Can_HardwareObjectType* CanHOHRef;       // Reference to HOH.
} Can_Arc_ObjectHOHMapType;

/* Type for holding global information used by the driver */
typedef struct {
    Can_DriverStateType initRun;

    // Our config
    const Can_ConfigType *config;

    // One bit for each channel that is configured.
    // Used to determine if validity of a channel
    // 1 - configured
    // 0 - NOT configured
    uint32  configured;
    // Maps the a channel id to a configured channel id
    uint8   channelMap[CAN_CONTROLLER_CNT];

    // This is a map that maps the HTH:s with the controller and Hoh. It is built
    // during Can_Init and is used to make things faster during a transmit.
    Can_Arc_ObjectHOHMapType CanHTHMap[NUM_OF_HTHS];
} Can_GlobalType;

// Global config
Can_GlobalType Can_Global =
{
    .initRun = CAN_UNINIT,
};

/* Type for holding information about each controller */
typedef struct {
    CanIf_ControllerModeType state;
    uint32		lock_cnt;

    // Statistics
    Can_Arc_StatisticsType stats;

    // Data stored for Txconfirmation callbacks to CanIf
    PduIdType swPduHandle[AVAIL_TX_MAILBOX_NUM]; // One handle for each tx mailbox
    Can_CtrlPendingStateIndicationType  pendingStateIndication;
} Can_UnitType;

Can_UnitType CanUnit[CAN_CONTROLLER_CNT] =
{
    {
        .state = CANIF_CS_UNINIT,
    },
    {
        .state = CANIF_CS_UNINIT,
    },
};

//-------------------------------------------------------------------
static CAN_HW_t * GetController(int unit)
{
    return ((CAN_HW_t *)(CAN1_BASE + unit*0x400));
}

//-------------------------------------------------------------------
/**
 * Function that finds the Hoh( HardwareObjectHandle ) from a Hth
 * A HTH may connect to one or several HOH's. Just find the first one.
 *
 * @param hth The transmit handle
 * @returns Ptr to the Hoh
 */
static const Can_HardwareObjectType * Can_FindHoh( Can_HwHandleType hth , uint32* controller)
{
    const Can_HardwareObjectType *hohObj;
    const Can_Arc_ObjectHOHMapType *map;

    map = &Can_Global.CanHTHMap[hth];

    // Verify that this is the correct map
    if (map->CanHOHRef->CanObjectId != hth)
    {
        DET_REPORTERROR(CAN_MODULE_ID, 0, CAN_WRITE_SERVICE_ID, CAN_E_PARAM_HANDLE);
    }

    hohObj = map->CanHOHRef;

    // Verify that this is the correct Hoh type
    if ( hohObj->CanObjectType == CAN_OBJECT_TYPE_TRANSMIT)
    {
        *controller = (uint32)map->CanControllerRef;
        return hohObj;
    }

    DET_REPORTERROR(CAN_MODULE_ID, 0, CAN_WRITE_SERVICE_ID, CAN_E_PARAM_HANDLE);

    return NULL;
}

//-------------------------------------------------------------------

static void Can_RxIsr( int unit, uint8 fifo );
static void Can_TxIsr( int unit );
static void Can_ErrIsr( int unit );

ISR(Can_1_Rx0Isr) {	Can_RxIsr((int)CAN_CTRL_1,CAN_FIFO0); }
ISR(Can_1_Rx1Isr) { Can_RxIsr((int)CAN_CTRL_1,CAN_FIFO1); }
ISR(Can_2_Rx0Isr) {	Can_RxIsr((int)CAN_CTRL_2,CAN_FIFO0); }
ISR(Can_2_Rx1Isr) { Can_RxIsr((int)CAN_CTRL_2,CAN_FIFO1); }

ISR(Can_1_TxIsr) {	Can_TxIsr((int)CAN_CTRL_1); }
ISR(Can_2_TxIsr) {	Can_TxIsr((int)CAN_CTRL_2); }

ISR(Can_1_ErrIsr) {	Can_ErrIsr((int)CAN_CTRL_1); }
ISR(Can_2_ErrIsr) {	Can_ErrIsr((int)CAN_CTRL_2); }


//-------------------------------------------------------------------

// Uses 25.4.5.1 Transmission Abort Mechanism
static void Can_AbortTx( CAN_HW_t *canHw, Can_UnitType *canUnit ) {
    // Disable Transmit irq

    // check if mb's empty

    // Abort all pending mb's

    // Wait for mb's being emptied
}

/**
 * Hardware wake ISR for CAN
 *
 * @param unit CAN controller number( from 0 )
 */
static void Can_WakeIsr( int unit ) {

    // 269,270,271
    (void)Can_SetControllerMode(unit, CAN_T_STOP);

    // IMPROVEMENT:  EcuM_CheckWakeup();
}

/**
 * Hardware error ISR for CAN
 *
 * @param unit CAN controller number( from 0 )
 */
static void Can_ErrIsr( int unit ) {
    /** @req 4.0.3/CAN033 *//** @req 4.1.2/SWS_Can_00033 */
    /** @req 4.1.2/SWS_Can_00020 */
    CAN_HW_t *canHw = GetController(unit);
    Can_UnitType *canUnit = GET_PRIVATE_DATA(unit);
    Can_Arc_ErrorType err;
#if defined(CFG_CAN_USE_SYMBOLIC_CANIF_CONTROLLER_ID)
    const Can_ControllerConfigType *canHwConfig= GET_CONTROLLER_CONFIG(Can_Global.channelMap[unit]);
#endif
    err.R = 0;

    // Check wake up
    if(SET == CAN_GetITStatus(canHw, CAN_IT_WKU)){
        Can_WakeIsr(unit);
        CAN_ClearITPendingBit(canHw, CAN_IT_WKU);
    }

    if(SET == CAN_GetITStatus(canHw, CAN_IT_BOF)){
        canUnit->stats.boffCnt++;
#if defined(CFG_CAN_USE_SYMBOLIC_CANIF_CONTROLLER_ID)
        CanIf_ControllerBusOff(canHwConfig->Can_Arc_CanIfControllerId);
#else
        CanIf_ControllerBusOff(unit);
#endif
        (void)Can_SetControllerMode(unit, CAN_T_STOP);/** @req 4.0.3/CAN272 *//** @req 4.1.2/SWS_Can_00272 */

        Can_AbortTx( canHw, canUnit );

        // Clear int
        CAN_ClearITPendingBit(canHw, CAN_IT_BOF);
    }

    (void)err;          /*lint !e920 STANDARDIZED_API */

#if 0
    /* IMPROVEMENT: Add Can_Arc_Error callback to model */
    if (err.R != 0)
    {
#if defined(CFG_CAN_USE_SYMBOLIC_CANIF_CONTROLLER_ID)
        Can_Arc_Error( canHwConfig->Can_Arc_CanIfControllerId, err );
#else
        Can_Arc_Error( unit, err );
#endif
        }
    }
#endif
}

//-------------------------------------------------------------------

/**
 * ISR for CAN. Normal Rx/operation
 *
 * @param unit CAN controller number( from 0 )
 * @param fifo CAN Receive fifo count (from 0)
 */
static void Can_RxIsr(int unit, uint8 fifo) {

    CAN_HW_t *canHw= GetController(unit);
    const Can_ControllerConfigType *canHwConfig= GET_CONTROLLER_CONFIG(Can_Global.channelMap[unit]);
    Can_UnitType *canUnit = GET_PRIVATE_DATA(unit);
    const Can_HardwareObjectType *hohObj;
    uint8 rxhwobjCnt = 0;

    CanRxMsg RxMessage;

    RxMessage.StdId=0x00;
    RxMessage.ExtId=0x00;
    RxMessage.IDE=0;
    RxMessage.DLC=0;
    RxMessage.FMI=0;
    RxMessage.Data[0]=0x00;
    RxMessage.Data[1]=0x00;
    CAN_Receive(canHw,fifo, &RxMessage);

    // Loop over all the Hoh's
    hohObj= canHwConfig->Can_Arc_Hoh;
    --hohObj;
    do {
        ++hohObj;

        if (hohObj->CanObjectType == CAN_OBJECT_TYPE_RECEIVE)
        {
            /* First Receive hardware object is assigned to Fifo 0 and the second one to Fifo 1. This is setup in Can_ChangeBaudrate() */
            if (fifo == rxhwobjCnt) {

                Can_IdType id=0;

                /** @req 4.1.2/SWS_Can_00423 */
                // According to autosar MSB shuould be set if extended
                if (RxMessage.IDE != CAN_ID_STD) {
                    id = RxMessage.ExtId;
                    id |= 0x80000000;
                } else {
                    id = RxMessage.StdId;
                }
                /** @req 4.0.3/CAN279 *//** @req 4.1.2/SWS_Can_00279 */
                /** @req 4.0.3/CAN396 *//** @req 4.1.2/SWS_Can_00396 - Supported by ISR but not by polling. */
                CanIf_RxIndication(hohObj->CanObjectId, id, RxMessage.DLC, (uint8 *)&RxMessage.Data[0] ); // Next layer will copy
                // Increment statistics
                canUnit->stats.rxSuccessCnt++;
            }
            rxhwobjCnt++;

        }
    } while ( !hohObj->Can_Arc_EOL);
}

/**
 * ISR for CAN. Normal Tx operation
 *
 * @param unit CAN controller number( from 0 )
 */
static void Can_TxIsr(int unit) {
    CAN_HW_t *canHw= GetController(unit);
    const Can_ControllerConfigType *canHwConfig= GET_CONTROLLER_CONFIG(Can_Global.channelMap[unit]);
    Can_UnitType *canUnit = GET_PRIVATE_DATA(unit);
    const Can_HardwareObjectType *hohObj;

    // Loop over all the Hoh's
    hohObj= canHwConfig->Can_Arc_Hoh;
    --hohObj;
    do {
        ++hohObj;

        if (hohObj->CanObjectType == CAN_OBJECT_TYPE_TRANSMIT)
        {
            for (uint8 mbox = 0; mbox < AVAIL_TX_MAILBOX_NUM; mbox++){
                if (CANTXOK == CAN_TransmitStatus(canHw,mbox)) {

                    /** @req 4.0.3/CAN016 *//** @req 4.1.2/SWS_Can_00016 */
                    /** @req 4.0.3/CAN276 *//** @req 4.1.2/SWS_Can_00276 */
                    CanIf_TxConfirmation(canUnit->swPduHandle[mbox]);
                }

            }

            // Clear Tx interrupt
            CAN_ClearITPendingBit(canHw,CAN_IT_TME);
            break;//Only one HwObj can be configured as Hth for one controller
        }
    } while ( !hohObj->Can_Arc_EOL);
}

//-------------------------------------------------------------------
/** @req 4.1.2/SWS_Can_00033 */
#define INSTALL_HANDLERS(_can_name,_sce,_rx0,_rx1,_tx) \
  do { \
    ISR_INSTALL_ISR2( "Can_Err", _can_name ## _ErrIsr, _sce, 2, 0 ); \
    ISR_INSTALL_ISR2( "Can_Rx0", _can_name ## _Rx0Isr, _rx0, 2, 0 ); \
    ISR_INSTALL_ISR2( "Can_Rx1", _can_name ## _Rx1Isr, _rx1, 2, 0 ); \
    ISR_INSTALL_ISR2( "Can_Tx",  _can_name ## _TxIsr,  _tx,  2, 0 ); \
  } while(0);

// This initiates ALL can controllers
/** @req 4.1.2/SWS_Can_00223 */
void Can_Init( const Can_ConfigType *Config ) {
    /** @req 4.1.2/SWS_Can_00053 *//* Don't change registers for controllers not used */
    /** @req 4.1.2/SWS_Can_00021 */
    /** @req 4.1.2/SWS_Can_00291 */
    /** @req 4.1.2/SWS_Can_00250 *//* Initialize variables, init controllers. */
    Can_UnitType *canUnit;
    const Can_ControllerConfigType *canHwConfig;
    const Can_HardwareObjectType* hoh;
    uint32 ctlrId;
    uint8 txHwObj,rxHwObj;
    uint8 configId;
    /** @req 4.1.2/SWS_Can_00174 */
    VALIDATE_NO_RV( (Can_Global.initRun == CAN_UNINIT), CAN_INIT_SERVICE_ID, CAN_E_TRANSITION );
    /** @req 4.1.2/SWS_Can_00175 */
    VALIDATE_NO_RV( (Config != NULL ), CAN_INIT_SERVICE_ID, CAN_E_PARAM_POINTER );
    //Check if more than available CAN controllers are configured
#if (CAN_ARC_CTRL_CONFIG_CNT > AVAILABLE_CAN_CONTROLLER)
#error Configured CanControllers exceeds the total controllers available on MCU
#endif

    // Validate if number of Hardware Objects (Rx/Tx) are correct

    for (configId=0; configId < CAN_ARC_CTRL_CONFIG_CNT; configId++) {

        hoh = Config->CanConfigSetPtr->CanController[configId].Can_Arc_Hoh;
        txHwObj = rxHwObj =0;
        while( !hoh->Can_Arc_EOL ){
            if ((hoh->CanObjectType == CAN_OBJECT_TYPE_RECEIVE))
            {
                rxHwObj++;
            }
            else {
                txHwObj++;
            }
            hoh++;
        }
        /* Validate if more than two receive Hardware objects are configuredd */
        VALIDATE_NO_RV( (rxHwObj <= AVAILABLE_RX_HWOBJECT), CAN_INIT_SERVICE_ID, CAN_E_PARAM_CONTROLLER  );

        /* Validate if more than one transmit Hardware objects are configuredd */
        VALIDATE_NO_RV( (txHwObj <= AVAILABLE_TX_HWOBJECT), CAN_INIT_SERVICE_ID, CAN_E_PARAM_CONTROLLER  );
    }

    // Save config
    Can_Global.config = Config;

    /** !req 4.1.2/SWS_Can_00246 *//* Should be done after initializing all controllers */
    /* Improvement: Modify Can_ChangeBaudrate so it calls another function, modifyBaudrate,
     * which does not require the Can module to be in state CAN_READY and thus can be called before it is. */
    Can_Global.initRun = CAN_READY;

    /** @req 4.1.2/SWS_Can_00245 */
    for (configId=0; configId < CAN_ARC_CTRL_CONFIG_CNT; configId++) {
        canHwConfig = GET_CONTROLLER_CONFIG(configId);
        ctlrId = (uint32)canHwConfig->CanControllerId;

        // Assign the configuration channel used later..
        Can_Global.channelMap[ctlrId] = configId;
        Can_Global.configured |= (1<<ctlrId);

        canUnit = GET_PRIVATE_DATA(ctlrId);
        /** @req 4.1.2/SWS_Can_00259 */
        canUnit->state = CANIF_CS_STOPPED;

        canUnit->lock_cnt = 0;

        // Clear stats
        memset(&canUnit->stats, 0, sizeof(Can_Arc_StatisticsType));

        // Note!
        // Could install handlers depending on HW objects to trap more errors
        // in configuration
        switch( canHwConfig->CanControllerId ) {
#ifndef STM32F10X_CL
        case CAN_CTRL_1:
            INSTALL_HANDLERS(Can_1, CAN1_SCE_IRQn, USB_LP_CAN1_RX0_IRQn, CAN1_RX1_IRQn, USB_HP_CAN1_TX_IRQn);	break;
#else
        case CAN_CTRL_1:
            INSTALL_HANDLERS(Can_1, CAN1_SCE_IRQn, CAN1_RX0_IRQn, CAN1_RX1_IRQn, CAN1_TX_IRQn);	break;
        case CAN_CTRL_2:
            INSTALL_HANDLERS(Can_2, CAN2_SCE_IRQn, CAN2_RX0_IRQn, CAN2_RX1_IRQn, CAN2_TX_IRQn);	break;
#endif
            default:
                ASSERT(0);
                break;
        }

        (void)Can_ChangeBaudrate(ctlrId, canHwConfig->CanControllerDefaultBaudrate);
        Can_EnableControllerInterrupts(ctlrId);

        // Loop through all Hoh:s and map them into the HTHMap
        hoh = canHwConfig->Can_Arc_Hoh;
        hoh--;
        do
        {
            hoh++;

            if (hoh->CanObjectType == CAN_OBJECT_TYPE_TRANSMIT)
            {
                Can_Global.CanHTHMap[hoh->CanObjectId].CanControllerRef = canHwConfig->CanControllerId;
                Can_Global.CanHTHMap[hoh->CanObjectId].CanHOHRef = hoh;
            }
        } while (!hoh->Can_Arc_EOL);
    }
}

// Unitialize the module
void Can_Arc_DeInit()
{
    Can_UnitType *canUnit;
    const Can_ControllerConfigType *canHwConfig;
    uint32 ctlrId;
    if( CAN_UNINIT == Can_Global.initRun ) {
        return;
    }
    for (int configId=0; configId < CAN_ARC_CTRL_CONFIG_CNT; configId++) {
        canHwConfig = GET_CONTROLLER_CONFIG(configId);
        ctlrId = (uint32)canHwConfig->CanControllerId;

        canUnit = GET_PRIVATE_DATA(ctlrId);
        canUnit->state = CANIF_CS_UNINIT;

        Can_DisableControllerInterrupts(ctlrId);

        canUnit->lock_cnt = 0;

        // Clear stats
        memset(&canUnit->stats, 0, sizeof(Can_Arc_StatisticsType));
    }

    Can_Global.config = NULL;
    Can_Global.initRun = CAN_UNINIT;
    return;
}

Std_ReturnType Can_ChangeBaudrate(uint8 Controller, const uint16 Baudrate)
{
    /** @req 4.0.3/CAN449 *//** @req 4.1.2/SWS_Can_00449 */

    CAN_HW_t *canHw;
    uint8_t tq;
    uint8_t tq1;
    uint8_t tq2;
    uint32_t clock;
    Can_UnitType *canUnit;
    uint8 cId = Controller;
    uint8 bs1;
    uint8 bs2;
    uint8 sjw;
    uint8 tqsync;
    uint8 fifoCnt;
    uint8 filterCnt;

    const Can_ControllerConfigType *canHwConfig;
    const Can_HardwareObjectType *hohObj;
    const Can_ControllerBaudrateConfigType *baudratePtr;

    /** @req 4.0.3/CAN450 *//** @req 4.1.2/SWS_Can_00450 */
    VALIDATE((Can_Global.initRun == CAN_READY), CAN_CHANGE_BAUD_RATE_SERVICE_ID, CAN_E_UNINIT, E_NOT_OK );
    /** @req 4.0.3/CAN452 *//** @req 4.1.2/SWS_Can_00452 */
    VALIDATE( (Controller < (uint32)GET_CONTROLLER_CNT()), CAN_CHANGE_BAUD_RATE_SERVICE_ID, CAN_E_PARAM_CONTROLLER, E_NOT_OK );

    /** @req 4.0.3/CAN451 *//** @req 4.1.2/SWS_Can_00451 */
    VALIDATE(Can_CheckBaudrate(Controller, Baudrate) == E_OK, CAN_CHANGE_BAUD_RATE_SERVICE_ID, CAN_E_PARAM_BAUDRATE,E_NOT_OK);

    canUnit = GET_PRIVATE_DATA(Controller);

    /** @req 4.0.3/CAN453 *//** @req 4.1.2/SWS_Can_00453 */
    VALIDATE( (canUnit->state==CANIF_CS_STOPPED), CAN_CHANGE_BAUD_RATE_SERVICE_ID, CAN_E_TRANSITION, E_NOT_OK);

    canHw = GetController(cId);
    canHwConfig = GET_CONTROLLER_CONFIG(Can_Global.channelMap[cId]);

    // Find the baudrate config for the target baudrate
    baudratePtr = NULL;
   for( int i=0; i < canHwConfig->CanControllerSupportedBaudratesCount; i++)
   {
       if (canHwConfig->CanControllerSupportedBaudrates[i].CanControllerBaudRate == Baudrate)
       {
           baudratePtr = &canHwConfig->CanControllerSupportedBaudrates[0];
       }
   }
   // Catch NULL-pointer when no DET is available
   if (baudratePtr == NULL)
   {
       return E_NOT_OK; // Baudrate not found
   }

   // Convert segment times to register format (register value 0 = logical value 1 time quanta)
   bs1   = baudratePtr->CanControllerSeg1 + baudratePtr->CanControllerPropSeg - 1;
   bs2   = baudratePtr->CanControllerSeg2 - 1;
   sjw     = baudratePtr->CanControllerSyncJumpWidth - 1;
   tqsync = 1;//Always fixed
   /* Re-initialize the CAN controller and the controller specific settings. */
   /* Only affect register areas that contain specific configuration for a single CAN controller. */

    // Start this baby up
    CAN_DeInit(canHw);

    /* CAN filter init. We set up two filters - one for the master (CAN1) and
    * one for the slave (CAN2)
    *
    * CAN_SlaveStartBank(n) denotes which filter is the first of the slave.
    *
    * The filter registers reside in CAN1 and is shared to CAN2, so we only need
    * to set up this once.
    */

    // Setup Filter banks.
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;

    fifoCnt = CAN_FIFO0;
    filterCnt = 0;

#if defined (STM32F10X_CL) //CAN2 only for Connectivity line devices STM32F105xx,F107xx

    // Set Filter bank 2 for CAN2
    if (BX_CAN_SLAVE == cId) {
        CAN_SlaveStartBank(SLAVE_START_FILTER_BANK);
        filterCnt = SLAVE_START_FILTER_BANK;
    }
#endif


    // acceptance filters
    hohObj = canHwConfig->Can_Arc_Hoh;
    --hohObj;
    do {
       ++hohObj;
        if ((hohObj->CanObjectType == CAN_OBJECT_TYPE_RECEIVE))
        {

            if (CAN_ID_TYPE_STANDARD == hohObj->CanIdType){
                CAN_FilterInitStructure.CAN_FilterIdHigh         = (uint16)(hohObj->CanHwFilterCode & RX_MAILBOX_IDNTFREG_STDID_MASK) << RX_MAILBOX_IDNTFREG_STDID_STARTPOS;
                CAN_FilterInitStructure.CAN_FilterIdLow          = 0;
                CAN_FilterInitStructure.CAN_FilterMaskIdHigh     = (uint16)(hohObj->CanHwFilterMask & RX_MAILBOX_IDNTFREG_STDID_MASK) << RX_MAILBOX_IDNTFREG_STDID_STARTPOS;
                CAN_FilterInitStructure.CAN_FilterMaskIdLow      = 0;
            } else{
                CAN_FilterInitStructure.CAN_FilterIdHigh         = (uint16)((hohObj->CanHwFilterCode & RX_MAILBOX_IDNTFREG_EXTD_MASK_HIGHER) >> (16u - RX_MAILBOX_IDNTFREG_EXTDID_STARTPOS));
                CAN_FilterInitStructure.CAN_FilterIdLow          = ((uint16)(hohObj->CanHwFilterCode & RX_MAILBOX_IDNTFREG_EXTD_MASK_LOWER) << RX_MAILBOX_IDNTFREG_EXTDID_STARTPOS) | RX_MAILBOX_IDNTFREG_IDE;
                CAN_FilterInitStructure.CAN_FilterMaskIdHigh     = (uint16)((hohObj->CanHwFilterMask & RX_MAILBOX_IDNTFREG_EXTD_MASK_HIGHER) >> (16u - RX_MAILBOX_IDNTFREG_EXTDID_STARTPOS));
                CAN_FilterInitStructure.CAN_FilterMaskIdLow      = ((uint16)(hohObj->CanHwFilterMask & RX_MAILBOX_IDNTFREG_EXTD_MASK_LOWER) << RX_MAILBOX_IDNTFREG_EXTDID_STARTPOS) | RX_MAILBOX_IDNTFREG_IDE;
            }
            /* First Receive hardware object is assigned to Fifo 0 and second one to Fifo 1*/
            CAN_FilterInitStructure.CAN_FilterFIFOAssignment = fifoCnt;
            CAN_FilterInitStructure.CAN_FilterNumber         = filterCnt;
            CAN_FilterInit(&CAN_FilterInitStructure);

            fifoCnt++;
            filterCnt++;
        }
    }while( !hohObj->Can_Arc_EOL );

    // Clock calucation
    // -------------------------------------------------------------------
    //
    // * 1 TQ = Sclk period( also called SCK )
    // * Ftq = Fcanclk / ( PRESDIV + 1 ) = Sclk
    //   ( Fcanclk can come from crystal or from the peripheral dividers )
    //
    // -->
    // TQ = 1/Ftq = (PRESDIV+1)/Fcanclk --> PRESDIV = (TQ * Fcanclk - 1 )
    // TQ is between 8 and 25
    clock = Mcu_Arc_GetSystemClock()/2;


    tq1 = bs1 + 1;
    tq2 = bs2 + 1;
    tq = tq1 + tq2 + tqsync;

    CAN_InitTypeDef        CAN_InitStructure;
    CAN_StructInit(&CAN_InitStructure);

    /* CAN cell init */
    CAN_InitStructure.CAN_TTCM=DISABLE;
    CAN_InitStructure.CAN_ABOM=ENABLE;
    CAN_InitStructure.CAN_AWUM=ENABLE;
    CAN_InitStructure.CAN_NART=DISABLE;
    CAN_InitStructure.CAN_RFLM=DISABLE;
    CAN_InitStructure.CAN_TXFP=DISABLE;
    if(canHwConfig->Can_Arc_Loopback){
        CAN_InitStructure.CAN_Mode=CAN_Mode_LoopBack;
    }else{
        CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;
    }

    CAN_InitStructure.CAN_SJW=sjw;
    CAN_InitStructure.CAN_BS1=bs1;
    CAN_InitStructure.CAN_BS2=bs2;
    CAN_InitStructure.CAN_Prescaler= clock/(baudratePtr->CanControllerBaudRate*1000*tq);

    if(CANINITOK != CAN_Init(canHw,&CAN_InitStructure))
    {
        return E_NOT_OK;
    }
    canUnit->state = CANIF_CS_STOPPED;
    return E_OK;
}


Can_ReturnType Can_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition ) {
    /** @req 4.0.3/CAN230 *//** @req 4.1.2/SWS_Can_00230 */
    /** @req 4.0.3/CAN017 *//** @req 4.1.2/SWS_Can_00017 */
    /** !req 4.0.3/CAN294 *//** !req 4.1.2/SWS_Can_00294 *//* Wakeup not supported */
    /** !req 4.0.3/CAN197 *//** !req 4.1.2/SWS_Can_00197 */
    /** !req 4.0.3/CAN426 *//** !req 4.1.2/SWS_Can_00426 */
    /** @req 4.0.3/CAN200 *//** @req 4.1.2/SWS_Can_00200 *//* Detect invalid transitions */
    CAN_HW_t *canHw;
    Std_ReturnType ret;
    Can_ReturnType rv = CAN_OK;
    const Can_ControllerConfigType * hwconfig;
    /** @req 4.0.3/CAN199 *//** @req 4.1.2/SWS_Can_00199 */
    VALIDATE( (Controller < (uint32)GET_CONTROLLER_CNT()), CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_PARAM_CONTROLLER, CAN_NOT_OK );

    Can_UnitType *canUnit = GET_PRIVATE_DATA(Controller);
    /** @req 4.0.3/CAN198 *//** @req 4.1.2/SWS_Can_00198 */
    VALIDATE( (Can_Global.initRun == CAN_READY), CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_UNINIT,CAN_NOT_OK );
    canHw = GetController(Controller);
    canUnit->pendingStateIndication = CAN_CTRL_INDICATION_NONE;

    /** @req 4.1.2/SWS_Can_00417 */
    switch(Transition )
    {
    case CAN_T_START:
        /** @req 4.0.3/CAN200 *//** @req 4.1.2/SWS_Can_00200 */
        /** @req 4.0.3/CAN409 *//** @req 4.1.2/SWS_Can_00409 */
        VALIDATE(canUnit->state == CANIF_CS_STOPPED, CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_TRANSITION, CAN_NOT_OK);

        hwconfig = GET_CONTROLLER_CONFIG(Can_Global.channelMap[Controller]);
        /** @req 4.1.2/SWS_Can_00261 */
        ret = Can_ChangeBaudrate(Controller, hwconfig->CanControllerDefaultBaudrate);

        if (E_OK == ret) {
            canUnit->state = CANIF_CS_STARTED;
            SchM_Enter_Can_EA_0();
            /** @req 4.0.3/CAN196 *//** @req 4.1.2/SWS_Can_00196 */
            /** @req 4.0.3/CAN425 *//** @req 4.1.2/SWS_Can_00425 */
            if (canUnit->lock_cnt == 0){
                Can_EnableControllerInterrupts(Controller);
            }
            SchM_Exit_Can_EA_0();
            canUnit->pendingStateIndication = CAN_CTRL_INDICATION_PENDING_START;
        }
        else
        {
            rv = CAN_NOT_OK;
        }
        break;
    case CAN_T_WAKEUP:
        /** @req 4.0.3/CAN412 *//** @req 4.1.2/SWS_Can_00412 */
        VALIDATE(canUnit->state == CANIF_CS_SLEEP || canUnit->state == CANIF_CS_STOPPED, CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_TRANSITION,CAN_NOT_OK);
        (void)CAN_WakeUp(canHw);
        canUnit->state = CANIF_CS_STOPPED;
        canUnit->pendingStateIndication = CAN_CTRL_INDICATION_PENDING_STOP;
        break;
    case CAN_T_SLEEP:  //CAN258, CAN290
        /** @req 4.0.3/CAN411 *//** @req 4.1.2/SWS_Can_00411 */
        VALIDATE(canUnit->state == CANIF_CS_STOPPED, CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_TRANSITION,CAN_NOT_OK);
    	/** @req 4.1.2/SWS_Can_00257*/
    	/** @req 4.1.2/SWS_Can_00265*/
        (void)CAN_Sleep(canHw);
        canUnit->state = CANIF_CS_SLEEP;
        Can_AbortTx(canHw, canUnit); /** !req 4.0.3/CAN282 *//** !req 4.1.2/SWS_Can_00282 */
        canUnit->pendingStateIndication = CAN_CTRL_INDICATION_PENDING_SLEEP;
        break;
    case CAN_T_STOP:
        // Stop
        canUnit->state = CANIF_CS_STOPPED;
        Can_AbortTx( canHw, canUnit ); /** !req 4.0.3/CAN282 *//** !req 4.1.2/SWS_Can_00282 */
        canUnit->pendingStateIndication = CAN_CTRL_INDICATION_PENDING_STOP;
        break;
    default:
        /** @req 4.0.3/CAN200 *//** @req 4.1.2/SWS_Can_00200 */
        VALIDATE(canUnit->state == CANIF_CS_STOPPED, CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_TRANSITION,CAN_NOT_OK);
        break;
    }

    return rv;
}

void Can_DisableControllerInterrupts( uint8 Controller )
{
    /** @req 4.0.3/CAN231 *//** @req 4.1.2/SWS_Can_00231 */
    /** @req 4.0.3/CAN202 *//** @req 4.1.2/SWS_Can_00202 */
    /** !req 4.0.3/CAN204 *//** !req 4.1.2/SWS_Can_00204 */
    Can_UnitType *canUnit;
    CAN_HW_t *canHw;
    /** @req 4.0.3/CAN206 *//** @req 4.1.2/SWS_Can_00206*/
    VALIDATE_NO_RV( (Controller < (uint32)GET_CONTROLLER_CNT()), CAN_DISABLECONTROLLERINTERRUPTS_SERVICE_ID, CAN_E_PARAM_CONTROLLER );

    canUnit = GET_PRIVATE_DATA(Controller);
    /** @req 4.0.3/CAN205 *//** @req 4.1.2/SWS_Can_00205 */
    VALIDATE_NO_RV( (Can_Global.initRun == CAN_READY), CAN_DISABLECONTROLLERINTERRUPTS_SERVICE_ID, CAN_E_UNINIT );

    SchM_Enter_Can_EA_0();
    /** @req 4.0.3/CAN049 *//** @req 4.1.2/SWS_Can_00049 */
    if(canUnit->lock_cnt > 0 )
    {
        // Interrupts already disabled
        canUnit->lock_cnt++;
        SchM_Exit_Can_EA_0();
        return;
    }
    canUnit->lock_cnt++;
    SchM_Exit_Can_EA_0();

    /* Don't try to be intelligent, turn everything off */
    canHw = GetController(Controller);

    /* Turn off the tx interrupt mailboxes */
    CAN_ITConfig(canHw, CAN_IT_TME, DISABLE);

    /* Turn off the bus off/tx warning/rx warning and error and rx  */
    CAN_ITConfig(canHw, CAN_IT_FMP0 | CAN_IT_BOF | CAN_IT_ERR | CAN_IT_WKU, DISABLE);
}

void Can_EnableControllerInterrupts( uint8 Controller ) {
    /** @req 4.0.3/CAN232 *//** @req 4.1.2/SWS_Can_00232 */
    /** @req 4.0.3/CAN050 *//** @req 4.1.2/SWS_Can_00050 */
    Can_UnitType *canUnit;
    CAN_HW_t *canHw;
    const Can_ControllerConfigType *canHwConfig;

    canUnit = GET_PRIVATE_DATA(Controller);
    /** @req 4.0.3/CAN209 *//** @req 4.1.2/SWS_Can_00209 */
    VALIDATE_NO_RV( (Can_Global.initRun == CAN_READY), CAN_ENABLECONTROLLERINTERRUPTS_SERVICE_ID, CAN_E_UNINIT );

    /** @req 4.0.3/CAN210 *//** @req 4.1.2/SWS_Can_00210 */
    VALIDATE_NO_RV( (Controller <(uint32)GET_CONTROLLER_CNT()), CAN_ENABLECONTROLLERINTERRUPTS_SERVICE_ID, CAN_E_PARAM_CONTROLLER );

    SchM_Enter_Can_EA_0();
    if( canUnit->lock_cnt > 1 )
    {
        /** @req 4.0.3/CAN208 *//** @req 4.1.2/SWS_Can_00208 */
        // IRQ should still be disabled so just decrement counter
        canUnit->lock_cnt--;
        SchM_Exit_Can_EA_0();
        return;
    } else if (canUnit->lock_cnt == 1)
    {
        canUnit->lock_cnt = 0;
    }
    SchM_Exit_Can_EA_0();

    canHw = GetController(Controller);

    canHwConfig = GET_CONTROLLER_CONFIG(Can_Global.channelMap[Controller]);

    if( canHwConfig->CanRxProcessing == CAN_ARC_PROCESS_TYPE_INTERRUPT ) {
        /* Turn on the rx interrupt */
        CAN_ITConfig(canHw, (CAN_IT_FMP0|CAN_IT_FMP1), ENABLE);
    }
    if( canHwConfig->CanTxProcessing == CAN_ARC_PROCESS_TYPE_INTERRUPT ) {
        /* Turn on the tx interrupt mailboxes */
        CAN_ITConfig(canHw, CAN_IT_TME, ENABLE);
    }

    // BusOff here represents all errors and warnings
    if( canHwConfig->CanBusOffProcessing == CAN_ARC_PROCESS_TYPE_INTERRUPT ) {
        /* Turn on the bus off/tx warning/rx warning and error and rx  */
        CAN_ITConfig(canHw, CAN_IT_BOF | CAN_IT_ERR | CAN_IT_WKU, ENABLE);
    }

    return;
}

Can_ReturnType Can_Write( Can_HwHandleType Hth, const Can_PduType *PduInfo ) {
    /** @req 4.0.3/CAN233 *//** @req 4.1.2/SWS_Can_00233 */
    /** !req 4.0.3/CAN213 *//** !req 4.1.2/SWS_Can_00213 */
    /** !req 4.0.3/CAN215 *//** !req 4.1.2/SWS_Can_00215 */
    /** !req 4.0.3/CAN278 *//** !req 4.1.2/SWS_Can_00278 */
    /** !req 4.0.3/CAN399 *//** !req 4.1.2/SWS_Can_00399 */
    /** !req 4.0.3/CAN213 *//** !req 4.1.2/SWS_Can_00213 */
    /** @req 4.1.2/SWS_Can_00275 */
    /** @req 4.1.2/SWS_Can_00011 */
    Can_ReturnType rv = CAN_OK;
    CAN_HW_t *canHw;
    const Can_HardwareObjectType *hohObj;
    uint32 controller;
    uint8 mboxNum;
    /** @req 4.0.3/CAN216 *//** @req 4.1.2/SWS_Can_00216 */
    VALIDATE( (Can_Global.initRun == CAN_READY), CAN_WRITE_SERVICE_ID, CAN_E_UNINIT,CAN_NOT_OK );
    /** @req 4.0.3/CAN219 *//** @req 4.1.2/SWS_Can_00219 */
    VALIDATE( (PduInfo != NULL), CAN_WRITE_SERVICE_ID, CAN_E_PARAM_POINTER,CAN_NOT_OK );
    VALIDATE( (PduInfo->sdu != NULL), CAN_WRITE_SERVICE_ID, CAN_E_PARAM_POINTER,CAN_NOT_OK );
    /** @req 4.0.3/CAN218 *//** @req 4.1.2/SWS_Can_00218 */
    VALIDATE( (PduInfo->length <= 8), CAN_WRITE_SERVICE_ID, CAN_E_PARAM_DLC,CAN_NOT_OK );
    /** @req 4.0.3/CAN217 *//** @req 4.1.2/SWS_Can_00217 */
    VALIDATE( (Hth < NUM_OF_HTHS ), CAN_WRITE_SERVICE_ID, CAN_E_PARAM_HANDLE,CAN_NOT_OK );

    hohObj = Can_FindHoh(Hth, &controller);
    if (hohObj == NULL) {
        return CAN_NOT_OK;
    }

    Can_UnitType *canUnit = GET_PRIVATE_DATA(controller);

    canHw = GetController(controller);
    SchM_Enter_Can_EA_0();

    CanTxMsg TxMessage;

    TxMessage.RTR=CAN_RTR_DATA;
    TxMessage.DLC=PduInfo->length;

    /** @req 4.0.3/CAN059 *//** @req 4.1.2/SWS_Can_00059 */
    /** !req 4.0.3/CAN427 *//** !req 4.1.2/SWS_Can_00427 */
    memcpy(TxMessage.Data, PduInfo->sdu, PduInfo->length);

    if ((hohObj->CanIdType == CAN_ID_TYPE_EXTENDED) || ((hohObj->CanIdType == CAN_ID_TYPE_MIXED) && (PduInfo->id > MASK_STANDARD_ID))) {
        TxMessage.IDE=CAN_ID_EXT;
        TxMessage.ExtId=PduInfo->id;
    } else {
        TxMessage.IDE=CAN_ID_STD;
        TxMessage.StdId=PduInfo->id;
    }

    // check for any free box
    /** @req 4.0.3/CAN212 *//** @req 4.1.2/SWS_Can_00212 */
    mboxNum = CAN_Transmit(canHw,&TxMessage);
    if(mboxNum != CAN_NO_MB) {

        // Increment statistics
        canUnit->stats.txSuccessCnt++;

        // Store pdu handle in unit to be used by TxConfirmation
        /** @req 4.0.3/CAN276 *//** @req 4.1.2/SWS_Can_00276 */
        canUnit->swPduHandle[mboxNum] = PduInfo->swPduHandle;
    } else {
        /** @req 4.1.2/SWS_Can_00214 */
        rv = CAN_BUSY;
    }
    SchM_Exit_Can_EA_0();

    return rv;
}
#if (CAN_USE_WRITE_POLLING == STD_ON)
void Can_MainFunction_Write( void ) {
    /** !req 4.0.3/CAN225 *//** !req 4.1.2/SWS_Can_00225 */
    /** !req 4.0.3/CAN031 *//** !req 4.1.2/SWS_Can_00031 */
    /** !req 4.1.2/SWS_Can_00441 */
    /** !req 4.0.3/CAN179 *//** !req 4.1.2/SWS_Can_00179 *//* CAN_E_UNINIT */
}
#endif

#if (CAN_USE_READ_POLLING == STD_ON)
void Can_MainFunction_Read( void ) {
    /** !req 4.0.3/CAN226 *//** !req 4.1.2/SWS_Can_00226 */
    /** !req 4.0.3/CAN108 *//** !req 4.1.2/SWS_Can_00108 */
    /** !req 4.1.2/SWS_Can_00442 */
    /** req 4.0.3/CAN396 *//** req 4.1.2/SWS_Can_00396 - Supported by ISR */
    /** !req 4.0.3/CAN181 *//** !req 4.1.2/SWS_Can_00181 *//* CAN_E_UNINIT */
    /* NOT SUPPORTED */
}
#endif

#if (CAN_USE_BUSOFF_POLLING == STD_ON)
void Can_MainFunction_BusOff( void ) {
  /* Bus-off polling events */
    /** !req 4.0.3/CAN227 *//** !req 4.1.2/SWS_Can_00227 */
    /** !req 4.0.3/CAN109 *//** !req 4.1.2/SWS_Can_00109 */
    /** !req 4.0.3/CAN184 *//** !req 4.1.2/SWS_Can_00184 *//* CAN_E_UNINIT */
    /* NOT SUPPORTED */
}
#endif

#if (CAN_USE_WAKEUP_POLLING == STD_ON)
void Can_MainFunction_Wakeup( void ) {
  /* Wakeup polling events */
    /** !req 4.0.3/CAN228 *//** !req 4.1.2/SWS_Can_00228 */
    /** !req 4.0.3/CAN112 *//** !req 4.1.2/SWS_Can_00112 */
    /** !req 4.0.3/CAN186 *//** !req 4.1.2/SWS_Can_00186 */
    /* NOT SUPPORTED */
}
#endif

/**
 * Get send/receive/error statistics for a controller
 *
 * @param controller The controller
 * @param stats Pointer to data to copy statistics to
 */

void Can_Arc_GetStatistics( uint8 controller, Can_Arc_StatisticsType *stats)
{
      Can_UnitType *canUnit = GET_PRIVATE_DATA(controller);
      *stats = canUnit->stats;
}

#else // Stub all functions for use in simulator environment

#include "debug.h"

void Can_Init( const Can_ConfigType *Config )
{
    // Do initial configuration of layer here
}

Can_ReturnType Can_SetControllerMode( uint8 Controller, Can_StateTransitionType transition )
{
    // Turn on off controller here depending on transition
    return E_OK;
}

Can_ReturnType Can_Write( Can_HwHandleType hth, Can_PduType *pduInfo )
{
    // Write to mailbox on controller here.
    DEBUG(DEBUG_MEDIUM, "Can_Write(stub): Received data ");
    for (int i = 0; i < pduInfo->length; i++) {
        DEBUG(DEBUG_MEDIUM, "%d ", pduInfo->sdu[i]);
    }
    DEBUG(DEBUG_MEDIUM, "\n");

    return E_OK;
}

extern void CanIf_RxIndication(uint8 Hrh, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr);
Can_ReturnType Can_ReceiveAFrame()
{
    // This function is not part of autosar but needed to feed the stack with data
    // from the mailboxes. Normally this is an interrup but probably not in the PCAN case.
    uint8 CanSduData[] = {1,2,1,0,0,0,0,0};
    CanIf_RxIndication(CAN_HRH_0_1, 3, 8, CanSduData);

    return E_OK;
}

void Can_DisableControllerInterrupts( uint8 controller )
{
}

void Can_EnableControllerInterrupts( uint8 controller )
{
}


// Hth - for Flexcan, the hardware message box number... .We don't care
void Can_Cbk_CheckWakeup( uint8 controller ){}

void Can_MainFunction_Write( void ){}
void Can_MainFunction_Read( void ){}
void Can_MainFunction_BusOff( void ){}
void Can_MainFunction_Wakeup( void ){}

void Can_Arc_GetStatistics( uint8 controller, Can_Arc_StatisticsType * stat){}

#endif


Std_ReturnType Can_CheckBaudrate(uint8 Controller, const uint16 Baudrate)
{
    /** @req 4.0.3/CAN454 *//** @req 4.1.2/SWS_Can_00454 *//* API */

    // Checks that the target baudrate is found among the configured
    // baudrates for this controller.

    const Can_ControllerConfigType *config;
    boolean supportedBR;

    /** @req 4.0.3/CAN456 UNINIT *//** @req 4.1.2/SWS_Can_00456 */
    VALIDATE( ((uint32)Can_Global.initRun == (uint8)CAN_READY), CAN_CHECK_BAUD_RATE_SERVICE_ID, CAN_E_UNINIT,E_NOT_OK );
    /** @req 4.0.3/CAN457 Invalid controller *//** @req 4.1.2/SWS_Can_00457 */
    VALIDATE( Can_Global.configured & (1u<<Controller) , CAN_CHECK_BAUD_RATE_SERVICE_ID, CAN_E_PARAM_CONTROLLER,E_NOT_OK );

    /** @req 4.0.3/CAN458 Invalid baudrate value *//** @req 4.1.2/SWS_Can_00458 */
    VALIDATE( Baudrate <= 1000, CAN_CHECK_BAUD_RATE_SERVICE_ID, CAN_E_PARAM_BAUDRATE,E_NOT_OK );

    config = GET_CONTROLLER_CONFIG(Can_Global.channelMap[Controller]);

    // Find the baudrate config for the target baudrate
    supportedBR = FALSE;
    for( int i=0; i < config->CanControllerSupportedBaudratesCount; i++)
    {
        if (config->CanControllerSupportedBaudrates[i].CanControllerBaudRate == Baudrate)
        {
            supportedBR = TRUE;
        }
    }

    return ((supportedBR==TRUE) ? E_OK : E_NOT_OK);
}

void Can_MainFunction_Mode( void )
{
    /** @req 4.0.3/CAN368 *//** @req 4.1.2/SWS_Can_00368 *//* API */
    /** @req 4.0.3/CAN369 *//** @req 4.1.2/SWS_Can_00369 *//* Polling */

    /** !req 4.0.3/CAN398 *//** !req 4.1.2/SWS_Can_00398 *//* Blocking call not supported */
    /** !req 4.0.3/CAN371 *//** !req 4.1.2/SWS_Can_00371 *//* Blocking call not supported */
    /** !req 4.0.3/CAN372 *//** !req 4.1.2/SWS_Can_00372 *//* Blocking call not supported */

    Can_UnitType *uPtr;

    /** @req 4.0.3/CAN379 *//** @req 4.1.2/SWS_Can_00379 *//* CAN_E_UNINIT */
    VALIDATE_NO_RV( (Can_Global.initRun == CAN_READY), CAN_MAIN_FUNCTION_MODE_SERVICE_ID, CAN_E_UNINIT );

    /** @req 4.0.3/CAN431 *//* On Uninit, return immediately without prod err */
    if (Can_Global.initRun == CAN_UNINIT) {
        return;
    }
    for (int configId=0; configId < CAN_ARC_CTRL_CONFIG_CNT; configId++) {
        boolean clearPending = TRUE;
        CanIf_ControllerModeType indicateMode = CANIF_CS_UNINIT;
        //Get the controller from config index and index CanUnit
        const Can_ControllerConfigType * canHwConfig = GET_CONTROLLER_CONFIG(configId);
        uPtr = &CanUnit[canHwConfig->CanControllerId];

        switch (uPtr->pendingStateIndication)
        {
            case CAN_CTRL_INDICATION_PENDING_START:
                if (uPtr->state == CANIF_CS_STARTED) {
                    indicateMode = CANIF_CS_STARTED;
                }
                break;

            case CAN_CTRL_INDICATION_PENDING_STOP:
                if (uPtr->state == CANIF_CS_STOPPED) {
                    // Stopped, indicate to upper layer
                    indicateMode = CANIF_CS_STOPPED;
                }
                break;

            case CAN_CTRL_INDICATION_PENDING_SLEEP:
                if (uPtr->state == CANIF_CS_SLEEP) {
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
        if( (CANIF_CS_UNINIT != indicateMode) ) {
            /** @req 4.0.3/CAN370 *//** @req 4.1.2/SWS_Can_00370 */
            /** @req 4.0.3/CAN373 *//** @req 4.1.2/SWS_Can_00373 */
#if defined(CFG_CAN_USE_SYMBOLIC_CANIF_CONTROLLER_ID)
            CanIf_ControllerModeIndication(canHwConfig->Can_Arc_CanIfControllerId, indicateMode);
#else
            CanIf_ControllerModeIndication((uint8)canHwConfig->CanControllerId, indicateMode);
#endif
        }
        if (clearPending) {
            uPtr->pendingStateIndication = CAN_CTRL_INDICATION_NONE;
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
