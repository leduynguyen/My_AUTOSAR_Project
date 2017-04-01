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


#ifndef CAN_INTERNAL_H_
#define CAN_INTERNAL_H_

#define VALID_CONTROLLER(_ctrl)          ((_ctrl) < CAN_ARC_CTRL_CONFIG_CNT)

#if ( CAN_DEV_ERROR_DETECT == STD_ON )
/** @req 4.0.3/CAN027 */
/** @req 4.1.2/SWS_Can_00091*/
/** @req 4.1.2/SWS_Can_00089*/
#define VALIDATE_RV(_exp,_api,_err,_rv) \
        if( !(_exp) ) { \
          (void)Det_ReportError(CAN_MODULE_ID,0,_api,_err); \
          return _rv; \
        }

#define VALIDATE(_exp,_api,_err ) \
        VALIDATE_RV(_exp,_api,_err, (E_NOT_OK))

#define VALIDATE_NO_RV(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(CAN_MODULE_ID,0,_api,_err); \
          return; \
        }

#define DET_REPORTERROR(_x,_y,_z,_q) (void)Det_ReportError(_x, _y, _z, _q)
#else
/** @req 4.0.3/CAN424 */
#define VALIDATE_RV(_exp,_api,_err,rv )
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_NO_RV(_exp,_api,_err )
#define DET_REPORTERROR(_x,_y,_z,_q)
#endif

typedef enum {
    CAN_UNINIT = 0u,
    CAN_READY
} Can_DriverStateType;

typedef enum {
    CAN_CTRL_MODE_STOP,
    CAN_CTRL_MODE_RESET,
    CAN_CTRL_MODE_HALT,
    CAN_CTRL_MODE_COMM,
    CAN_CTRL_MODE_SLEEP,
} Can_Arc_ModeType;

/* Type for holding global information used by the driver */
typedef struct {
    Can_DriverStateType initRun; /* If Can_Init() have been run */
    const Can_ConfigType * config; /* Pointer to config */

    uint8 channelMap[CAN_ARC_HW_UNIT_CNT];
    uint8 channelToHwChannel[CAN_ARC_LOG_UNIT_CNT];
} Can_GlobalType;


typedef struct {
    struct canPrivateData *privateData;
    CanIf_ControllerModeType state;


    // Data stored for Txconfirmation callbacks to CanIf
    Can_StateTransitionType transition;
    boolean transitonPending;
    uint8 lockCnt;
} Can_UnitType;

extern Can_GlobalType Can_Global;
extern Can_UnitType Can_Unit[];

typedef uint8 Can_Hw_CtrlType;


static inline uint8 HwChannelToChannel(Can_Hw_CtrlType ch) {
    return Can_Global.channelMap[ch];
}
static inline Can_Hw_CtrlType ChannelToHwChannel(uint8 ch) {
    return Can_Global.channelToHwChannel[ch];
}

void Can_Hw_Init( void );
void Can_Hw_MainFunction_Mode( void );
void Can_Hw_DisableControllerInterrupts( uint8 Controller );
void Can_Hw_EnableControllerInterrupts( uint8 Controller );
Can_ReturnType Can_Hw_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition );
Can_ReturnType Can_Hw_CheckWakeup( uint8 Controller );
Can_ReturnType Can_Hw_Write( Can_HwHandleType Hth, const Can_PduType *PduInfo );

Can_Arc_ModeType Can_Hw_GetControllerMode( uint8 hwCh );

/* Deprecated since 4.1 API */
Std_ReturnType Can_Hw_CheckBaudrate(uint8 Controller, const uint16 Baudrate);
//Std_ReturnType Can_Hw_ChangeBaudrate(uint8 Controller, const uint16 Baudrate);
Std_ReturnType Can_Hw_ChangeBaudrate(uint8 Controller, const Can_ControllerBaudrateConfigType *baudratePtr );


#if (CAN_USE_WRITE_POLLING == STD_ON)
void Can_Hw_MainFunction_Write( void );
#endif /* CAN_USE_WRITE_POLLING == STD_ON */

#if (CAN_USE_READ_POLLING == STD_ON)
void Can_Hw_MainFunction_Read( void );
#endif /* CAN_USE_READ_POLLING == STD_ON */

#if (CAN_USE_BUSOFF_POLLING == STD_ON)
void Can_Hw_MainFunction_BusOff( void );
#endif /* CAN_USE_BUSOFF_POLLING == STD_ON */

#if (ARC_CAN_ERROR_POLLING == STD_ON)
void Can_Arc_Hw_MainFunction_Error(void);
#endif /*ARC_CAN_ERROR_POLLING == STD_ON*/

#if (CAN_USE_WAKEUP_POLLING == STD_ON)
void Can_Hw_MainFunction_Wakeup( void );
#endif /* CAN_USE_WAKEUP_POLLING == STD_ON */


#endif /* CAN_INTERNAL_H_ */
