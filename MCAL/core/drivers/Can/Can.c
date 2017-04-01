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
/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ */

/* ----------------------------[includes]------------------------------------*/

#include "Can.h"
#include "Can_Internal.h"

#if (CAN_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#include "SchM_Can.h"
#include "CanIf_Cbk.h"


/* ----------------------------[private macro]-------------------------------*/


/* ----------------------------[private variables]---------------------------*/

Can_GlobalType Can_Global = { .initRun = CAN_UNINIT, }; /** @req 4.1.2/SWS_Can_00103 */
Can_UnitType Can_Unit[6];

/* ----------------------------[function definitions]-------------------------------*/

static Can_ReturnType can_Transition( uint8 ch,  CanIf_ControllerModeType state , Can_StateTransitionType transition ) {

    Can_UnitType *unitPtr = &Can_Unit[ch];

    unitPtr->state = state;

    /* Save the transition for the Mode mainfunction */
    unitPtr->transition = transition;
    unitPtr->transitonPending = true;

    /* Make it happen in HW */
    return Can_Hw_SetControllerMode( ChannelToHwChannel(ch), transition );
}


#if (CAN_VERSION_INFO_API == STD_ON)
/**
 * Gets version info
 * @param versioninfo - out parameter filled with version info
 */
void Can_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    /** @req SWS_Can_00224 */
    /** @req SWS_Can_00177 */
    VALIDATE_NO_RV( ( NULL != versioninfo ), CAN_GETVERSIONINFO_SERVICE_ID, CAN_E_PARAM_POINTER);

    versioninfo->vendorID = CAN_VENDOR_ID;
    versioninfo->moduleID = CAN_MODULE_ID;
    versioninfo->sw_major_version = CAN_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = CAN_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = CAN_SW_PATCH_VERSION;

    return;
}
#endif /*CAN_VERSION_INFO_API == STD_ON*/

/**
 * Initializes the CAN driver
 * @param Config - a pointer to the configuration that is used during initialization
 */
void Can_Init( const Can_ConfigType *Config )
{
    /** @req 4.1.2/SWS_Can_00223 */
    /** @req 4.1.2/SWS_Can_00021 */
    /** @req 4.1.2/SWS_Can_00291 */
    /** !req 4.1.2/SWS_Can_00408 */

    /** @req 4.1.2/SWS_Can_00104 */
    /** @req 4.1.2/SWS_Can_00174 */
    uint8 hwCh;


    VALIDATE_NO_RV( (Can_Global.initRun == CAN_UNINIT), CAN_INIT_SERVICE_ID, CAN_E_TRANSITION);

    /** @req 4.1.2/SWS_Can_00175 */
    VALIDATE_NO_RV( (Config != NULL), CAN_INIT_SERVICE_ID, CAN_E_PARAM_POINTER);

    /* Save the configuration */
    Can_Global.config = Config;

    for (uint8 ch = 0; ch < CAN_ARC_CTRL_CONFIG_CNT; ch++) {
        hwCh = Can_Global.config->CanConfigSetPtr->CanController[ch].Can_Arc_HwUnitId;
        Can_Global.channelToHwChannel[ch] = hwCh;
        Can_Global.channelMap[hwCh] = ch;
        Can_Unit[ch].state = CANIF_CS_STOPPED;

    }

    Can_Hw_Init();

    /** @req 4.1.2/SWS_Can_00246 *//* Should be done after initializing all controllers */
    Can_Global.initRun = CAN_READY;
}


/**
 * Deinitializes the CAN driver
 */
void Can_Arc_DeInit( void )
{
    if (Can_Global.initRun != CAN_UNINIT) {

        uint8 hwCh;

        for (uint8 ch = 0; ch < CAN_ARC_CTRL_CONFIG_CNT; ch++) {

            hwCh = Can_Global.config->CanConfigSetPtr->CanController[ch].Can_Arc_HwUnitId;
            Can_Global.channelToHwChannel[ch] = hwCh;

            Can_DisableControllerInterrupts(ch);

            Can_Unit[ch].lockCnt = 0;

            Can_Unit[ch].state = CANIF_CS_UNINIT;
        }

        Can_Arc_Hw_DeInit();

        Can_Global.config = NULL;
        Can_Global.initRun = CAN_UNINIT;
    }
}

/**
 * Checks if a baudrate is supported for a controller
 * @param Controller - controller id
 * @param Baudrate - in kbps
 * @return E_OK if supported, otherwiese E_NOT_OK
 */
Std_ReturnType Can_CheckBaudrate(uint8 Controller, const uint16 Baudrate)
{

    const Can_ControllerConfigType *config;
    Std_ReturnType rv = E_NOT_OK;

    /** @req 4.1.2/SWS_Can_00454 *//* Checks that the target baudrate is found among the configured baudrates for this
                                    * controller. */

    /** @req 4.1.2/SWS_Can_00456 *//* UNINIT  */
    VALIDATE( (Can_Global.initRun == CAN_READY), CAN_CHECK_BAUD_RATE_SERVICE_ID, CAN_E_UNINIT );

    /** @req 4.1.2/SWS_Can_00457 *//* Invalid controller */
    VALIDATE( VALID_CONTROLLER(Controller) , CAN_CHECK_BAUD_RATE_SERVICE_ID, CAN_E_PARAM_CONTROLLER );

    /** @req 4.1.2/SWS_Can_00458 *//* Invalid baudrate value */
    VALIDATE( Baudrate <= 1000u, CAN_CHECK_BAUD_RATE_SERVICE_ID, CAN_E_PARAM_BAUDRATE );

    config = &Can_Global.config->CanConfigSetPtr->CanController[Controller];

    /* Check if the baudrate is supported */
    for( uint32 i=0; i < config->CanControllerSupportedBaudratesCount; i++) {
        if (config->CanControllerSupportedBaudrates[i].CanControllerBaudRate == Baudrate) {
            /* We have found match */
            rv = E_OK;
        }
    }

    return rv;
}

/**
 * Changes baudrate for a controller
 * @param Controller - controller id
 * @param Baudrate - in kpbs
 * @return E_OK if baudrate is changed, otherwise E_NOT_OK
 */
Std_ReturnType Can_ChangeBaudrate(uint8 Controller, const uint16 Baudrate)
{
    const Can_ControllerConfigType *config;
    Std_ReturnType rv = E_NOT_OK;

    /** @req 4.1.2/SWS_Can_00449 */

    /** @req 4.1.2/SWS_Can_00450 */
    VALIDATE( (Can_Global.initRun == CAN_READY), CAN_CHANGE_BAUD_RATE_SERVICE_ID, CAN_E_UNINIT );

    /** @req 4.1.2/SWS_Can_00452 */
    VALIDATE( VALID_CONTROLLER(Controller) , CAN_CHANGE_BAUD_RATE_SERVICE_ID, CAN_E_PARAM_CONTROLLER );

    /** @req 4.1.2/SWS_Can_00451 */
    VALIDATE(Can_CheckBaudrate(Controller, Baudrate) == E_OK, CAN_CHANGE_BAUD_RATE_SERVICE_ID, CAN_E_PARAM_BAUDRATE);

    /** @req 4.1.2/SWS_Can_00453 */
    VALIDATE( (Can_Unit[Controller].state==CANIF_CS_STOPPED), CAN_CHANGE_BAUD_RATE_SERVICE_ID, CAN_E_TRANSITION );

    config = &Can_Global.config->CanConfigSetPtr->CanController[Controller];

    /* Check if the baudrate is supported */
    for( uint32 i=0; i < config->CanControllerSupportedBaudratesCount; i++) {
        if (config->CanControllerSupportedBaudrates[i].CanControllerBaudRate == Baudrate) {
            /* We have found match */
            rv = Can_Hw_ChangeBaudrate( ChannelToHwChannel(Controller), &config->CanControllerSupportedBaudrates[i]);
        }
    }

    return rv;
}

/**
 * Changes the controller mode
 * @param Controller - controller id
 * @param Transition - type of transition to be made
 * @return CAN_OK if request accepted, otherwise CAN_NOT_OK
 */
Can_ReturnType Can_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition )
{
    Can_Hw_CtrlType hwCh;
    uint8			ch = Controller;
    Can_ReturnType retVal = CAN_NOT_OK;

    /** @req 4.1.2/SWS_Can_00230 */

    /** @req 4.1.2/SWS_Can_00198 */
    VALIDATE_RV( (Can_Global.initRun == CAN_READY), CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_UNINIT, CAN_NOT_OK );

    /** @req 4.1.2/SWS_Can_00199 */
    VALIDATE_RV( VALID_CONTROLLER(Controller), CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_PARAM_CONTROLLER, CAN_NOT_OK );
    VALIDATE_RV( (CAN_T_START == Transition ) || \
                (CAN_T_STOP   == Transition )|| \
                (CAN_T_SLEEP  == Transition )|| \
                (CAN_T_WAKEUP == Transition ), CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_PARAM_CONTROLLER, CAN_NOT_OK );

    hwCh = ChannelToHwChannel(Controller);

    switch (Transition) {
    case CAN_T_START:
        /** @req 4.0.3/CAN409 *//** @req 4.1.2/SWS_Can_00409 */
        VALIDATE_RV(Can_Unit[ch].state == CANIF_CS_STOPPED, 0x3, CAN_E_TRANSITION,CAN_NOT_OK);
        retVal = can_Transition( ch, CANIF_CS_STARTED,  Transition );
        break;
    case CAN_T_WAKEUP:
        VALIDATE_RV( (Can_Unit[ch].state == CANIF_CS_SLEEP) || (Can_Unit[ch].state == CANIF_CS_STOPPED), 0x3, CAN_E_TRANSITION,CAN_NOT_OK);
        retVal = can_Transition( hwCh, CANIF_CS_STOPPED,  Transition );
        break;
    case CAN_T_SLEEP:
        VALIDATE_RV(Can_Unit[ch].state == CANIF_CS_STOPPED, 0x3, CAN_E_TRANSITION,CAN_NOT_OK);
        retVal = can_Transition( hwCh, CANIF_CS_STOPPED,  Transition );
        break;
    case CAN_T_STOP:
        /** @req 4.0.3/CAN410 *//** @req 4.1.2/SWS_Can_00410 */
        VALIDATE_RV( (Can_Unit[ch].state == CANIF_CS_STARTED) || (Can_Unit[ch].state == CANIF_CS_STOPPED), 0x3, CAN_E_TRANSITION,CAN_NOT_OK);
        retVal = can_Transition( ch, CANIF_CS_STOPPED,  Transition );
        break;
    default:
        break;
    }


    return retVal;
}


/**
 * Disables interrupts for a controller
 * @param Controller - controller id
 */
void Can_DisableControllerInterrupts( uint8 Controller )
{
    /** @req 4.1.2/SWS_Can_00231 */
    /** @req 4.1.2/SWS_Can_00202 */
    /** !req 4.1.2/SWS_Can_00204 */

    VALIDATE_NO_RV( (Can_Global.initRun == CAN_READY), CAN_DISABLECONTROLLERINTERRUPTS_SERVICE_ID, CAN_E_UNINIT );

    /** @req 4.1.2/SWS_Can_00206*/
    VALIDATE_NO_RV( VALID_CONTROLLER(Controller), CAN_DISABLECONTROLLERINTERRUPTS_SERVICE_ID, CAN_E_PARAM_CONTROLLER );

    SchM_Enter_Can_EA_0(); /*lint !e632 Assignment to strong type 'imask_t'. Tolerable to enter exclusive area*/

    /** @req 4.1.2/SWS_Can_00049 */
    if (Can_Unit[Controller].lockCnt == 0u)
    {
        Can_Hw_DisableControllerInterrupts(ChannelToHwChannel(Controller));
    }

    Can_Unit[Controller].lockCnt++;

    SchM_Exit_Can_EA_0();

    return;
}


/**
 * Enables interrupts for a controller
 * @param Controller - controller id
 */
void Can_EnableControllerInterrupts( uint8 Controller )
{
    /** @req 4.1.2/SWS_Can_00232 */
    /** @req 4.1.2/SWS_Can_00050 */

    /** @req 4.1.2/SWS_Can_00209 */
    VALIDATE_NO_RV( (Can_Global.initRun == CAN_READY), CAN_ENABLECONTROLLERINTERRUPTS_SERVICE_ID, CAN_E_UNINIT );

    /** @req 4.1.2/SWS_Can_00210 */
    VALIDATE_NO_RV( VALID_CONTROLLER(Controller), CAN_ENABLECONTROLLERINTERRUPTS_SERVICE_ID, CAN_E_PARAM_CONTROLLER );

    SchM_Enter_Can_EA_0(); /*lint !e632 Assignment to strong type 'imask_t'. Tolerable to enter exclusive area*/

    if (Can_Unit[Controller].lockCnt == 0) {
        /** @req 4.1.2/SWS_Can_00208 */
        /* Do nothing */
    } else {
        Can_Unit[Controller].lockCnt--;
        if (Can_Unit[Controller].lockCnt == 0) {
            Can_Hw_EnableControllerInterrupts(ChannelToHwChannel(Controller));
        }
    }

    SchM_Exit_Can_EA_0();

    return;
}


/**
 * Checks if a wakeup has occurred for a given controller
 * @param Controller - controller id
 * @return CAN_OK if wakeup was detected, otherwise CAN_NOT_OK
 */
Can_ReturnType Can_CheckWakeup( uint8 Controller )
{
    VALIDATE_RV( (Can_Global.initRun == CAN_READY), CAN_CBK_CHECKWAKEUP_SERVICE_ID, CAN_E_UNINIT, CAN_NOT_OK );

    /** @req 4.1.2/SWS_Can_00210 */
    VALIDATE_RV( VALID_CONTROLLER(Controller), CAN_CBK_CHECKWAKEUP_SERVICE_ID, CAN_E_PARAM_CONTROLLER, CAN_NOT_OK );

    return Can_Hw_CheckWakeup(Controller);
}


/**
 *
 * @param Hth - the HardwareTransmitHandle to be used
 * @param PduInfo - pointer to SDU
 * @return CAN_OK if write was accepted, CAN_NOT_OK if error occurred, CAN_BUSY if not buffer available
 */
Can_ReturnType Can_Write( Can_HwHandleType Hth, const Can_PduType *PduInfo )
{
    /** @req 4.1.2/SWS_Can_00233 */

    /** @req 4.1.2/SWS_Can_00104 */
    /** @req 4.1.2/SWS_Can_00216 */
    VALIDATE_RV( (Can_Global.initRun == CAN_READY), CAN_WRITE_SERVICE_ID, CAN_E_UNINIT, CAN_NOT_OK );

    /** @req 4.1.2/SWS_Can_00219 */
    VALIDATE_RV( (PduInfo != NULL), CAN_WRITE_SERVICE_ID, CAN_E_PARAM_POINTER, CAN_NOT_OK );
    VALIDATE_RV( (PduInfo->sdu != NULL), CAN_WRITE_SERVICE_ID, CAN_E_PARAM_POINTER, CAN_NOT_OK );

    /** @req 4.1.2/SWS_Can_00218 */
    VALIDATE_RV( (PduInfo->length <= 8), CAN_WRITE_SERVICE_ID, CAN_E_PARAM_DLC, CAN_NOT_OK );

    /** @req 4.1.2/SWS_Can_00217 */
    VALIDATE_RV( (Hth < NUM_OF_HOHS), CAN_WRITE_SERVICE_ID, CAN_E_PARAM_HANDLE, CAN_NOT_OK );

    return Can_Hw_Write(Hth, PduInfo);
}


#if (CAN_USE_WRITE_POLLING == STD_ON)
/**
 * This function performs the polling of TX confirmation and TX cancellation
 * confirmation when CAN_TX_PROCESSING is set to POLLING.
 */
void Can_MainFunction_Write( void )
{
    /** @req 4.1.2/SWS_Can_00225 */
    /** @req 4.1.2/SWS_Can_00179 */
    VALIDATE_NO_RV( (Can_Global.initRun == CAN_READY), CAN_MAINFUNCTION_WRITE_SERVICE_ID, CAN_E_UNINIT);

    Can_Hw_MainFunction_Write();
    return;
}
#endif /* CAN_USE_WRITE_POLLING == STD_ON */


#if (CAN_USE_READ_POLLING == STD_ON)
/**
 * This function performs the polling of RX indications when
 * CAN_RX_PROCESSING is set to POLLING.
 */
void Can_MainFunction_Read( void )
{
    /** @req 4.1.2/SWS_Can_00226 */
    /** @req 4.1.2/SWS_Can_00181 */
    VALIDATE_NO_RV( (Can_Global.initRun == CAN_READY), CAN_MAINFUNCTION_READ_SERVICE_ID, CAN_E_UNINIT);

    Can_Hw_MainFunction_Read();
    return;
}
#endif /* CAN_USE_READ_POLLING == STD_ON */


#if (CAN_USE_BUSOFF_POLLING == STD_ON)
/**
 * This function performs the polling of bus-off events that are configured statically as
 * 'to be polled'.
 */
void Can_MainFunction_BusOff( void )
{
    /** @req 4.1.2/SWS_Can_00227 */
    /** @req 4.1.2/SWS_Can_00184 */
    VALIDATE_NO_RV( (Can_Global.initRun == CAN_READY), CAN_MAINFUNCTION_BUSOFF_SERVICE_ID, CAN_E_UNINIT);

    Can_Hw_MainFunction_BusOff();
    return;
}
#endif /* CAN_USE_BUSOFF_POLLING == STD_ON */


#if (ARC_CAN_ERROR_POLLING == STD_ON)
/**
 * This function performs the polling of error events that are configured statically as
 * 'to be polled'.
 */
void Can_Arc_MainFunction_Error(void)
{
    /* Error polling events (not in req spec)*/
    VALIDATE_NO_RV( (Can_Global.initRun == CAN_READY), CAN_MAINFUNCTION_ERROR_SERVICE_ID, CAN_E_UNINIT);

    Can_Arc_Hw_MainFunction_Error();
    return;
}
#endif


#if (CAN_USE_WAKEUP_POLLING == STD_ON)
/**
 * This function performs the polling of wake-up events that are configured statically
 * as 'to be polled'.
 */
void Can_MainFunction_Wakeup( void )
{
    /** @req 4.1.2/SWS_Can_00186 */
    VALIDATE_NO_RV( (Can_Global.initRun == CAN_READY), CAN_MAINFUNCTION_WAKEUP_SERVICE_ID, CAN_E_UNINIT);

    Can_Hw_MainFunction_Wakeup();
    return;
}
#endif /* CAN_USE_WAKEUP_POLLING == STD_ON */


/**
 * This function performs the polling of CAN controller mode transitions.
 */
void Can_MainFunction_Mode( void )
{
    CanIf_ControllerModeType canIfMode = CANIF_CS_UNINIT;
    Can_Arc_ModeType hwMode;

    /** @req 4.1.2/SWS_Can_00368 *//* API */
    /** @req 4.1.2/SWS_Can_00369 *//* Polling */
    /** @req 4.1.2/SWS_Can_00379 */
    VALIDATE_NO_RV( (Can_Global.initRun == CAN_READY), CAN_MAIN_FUNCTION_MODE_SERVICE_ID, CAN_E_UNINIT);

    /* What happens here:
     * If there is a mode change Can_SetControllerMode() will have been called with a new mode.
     * The mode will be set in HW. The job here is to get the HW state and check if it's
     * what it is supposed to be. If so a state change is indicated to CanIf through a callback
     *
     * This means mapping the states : CAN_T_START, CAN_T_STOP, CAN_T_SLEEP, CAN_T_WAKEUP
     *
     */

    /* Loop over all configured controllers */
    for (uint8 ch = 0; ch < CAN_ARC_LOG_UNIT_CNT; ch++) {
        if( !Can_Unit[ch].transitonPending ) {
            continue;
        }

        hwMode = Can_Hw_GetControllerMode(ChannelToHwChannel(ch));

        /* Check transition*/
        switch(Can_Unit[ch].transition) {
        case CAN_T_START:
            if( hwMode == CAN_CTRL_MODE_COMM ) {
                canIfMode = CANIF_CS_STARTED;
            }
            break;
        case CAN_T_STOP:
        case CAN_T_WAKEUP:
            if( hwMode == CAN_CTRL_MODE_STOP ) {
                canIfMode = CANIF_CS_STOPPED;
            }
            break;
        case CAN_T_SLEEP:
            if( hwMode == CAN_CTRL_MODE_STOP ) {
                canIfMode = CANIF_CS_SLEEP;
            }
            break;
        default:
            break;
        }

        if( canIfMode != CANIF_CS_UNINIT ) {
            /** @req 4.1.2/SWS_Can_00370 */
            /** @req 4.1.2/SWS_Can_00373 */
            CanIf_ControllerModeIndication(ch,canIfMode);
        }
    }
}

#ifdef HOST_TEST
Std_ReturnType Can_Test_DriverStateIsUninit(void) {
    return (Can_Global.initRun == CAN_UNINIT) ? E_OK : E_NOT_OK;
}

Std_ReturnType Can_Test_DriverStateIsReady(void) {
    return (Can_Global.initRun == CAN_READY) ? E_OK : E_NOT_OK;
}

Std_ReturnType Can_Test_AllUnitsInState(CanIf_ControllerModeType state) {

    for (uint8 ch = 0; ch < CAN_ARC_CTRL_CONFIG_CNT; ch++) {
        if (Can_Unit[ch].state != state) {
            return E_NOT_OK;
        }
    }

    return E_OK;
}
#endif /* HOST_TEST */
