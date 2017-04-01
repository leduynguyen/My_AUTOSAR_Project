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
/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ|PPC|TMS570|MPC5607B|MPC5645S|RH850F1H|MPC5777M|MPC5748G|JACINTO5|JACINTO6|STM32 */

#ifndef CAN_H_
#define CAN_H_

#include "CanIf_Types.h"
#include "ComStack_Types.h"/** @req 4.1.2/SWS_Can_00388 */
#include "Can_GeneralTypes.h"/** @req 4.1.2/SWS_Can_00435 */
#include "Mcu.h"

#define CAN_VENDOR_ID               60u
#define CAN_MODULE_ID               80u

#define CAN_AR_MAJOR_VERSION        4u
#define CAN_AR_MINOR_VERSION        1u
#define CAN_AR_PATCH_VERSION        2u

#define CAN_SW_MAJOR_VERSION        5u
#define CAN_SW_MINOR_VERSION        0u
#define CAN_SW_PATCH_VERSION        0u

#define CAN_E_PARAM_POINTER         0x01u
#define CAN_E_PARAM_HANDLE          0x02u
#define CAN_E_PARAM_DLC             0x03u
#define CAN_E_PARAM_CONTROLLER      0x04u
// API service used without initialization
#define CAN_E_UNINIT                0x05u
// Init transition for current mode
#define CAN_E_TRANSITION            0x06u
#define CAN_E_DATALOST              0x07u
#define CAN_E_PARAM_BAUDRATE        0x08u

/* Added by ArcCore*/
#define CAN_E_PARAM_TIMING          0x09u
#define CAN_E_UNEXPECTED_EXECUTION  0x20u


/*Service id's */
#define CAN_INIT_SERVICE_ID                         0x00u
#define CAN_MAINFUNCTION_WRITE_SERVICE_ID           0x01u
#define CAN_SETCONTROLLERMODE_SERVICE_ID            0x03u
#define CAN_DISABLECONTROLLERINTERRUPTS_SERVICE_ID  0x04u
#define CAN_ENABLECONTROLLERINTERRUPTS_SERVICE_ID   0x05u
#define CAN_WRITE_SERVICE_ID                        0x06u
#define CAN_GETVERSIONINFO_SERVICE_ID               0x07u
#define CAN_MAINFUNCTION_READ_SERVICE_ID            0x08u
#define CAN_MAINFUNCTION_BUSOFF_SERVICE_ID          0x09u
#define CAN_MAINFUNCTION_WAKEUP_SERVICE_ID          0x0au
#define CAN_CBK_CHECKWAKEUP_SERVICE_ID              0x0bu
#define CAN_MAIN_FUNCTION_MODE_SERVICE_ID           0x0cu
#define CAN_CHANGE_BAUD_RATE_SERVICE_ID             0x0du
#define CAN_CHECK_BAUD_RATE_SERVICE_ID              0x0eu
#define CAN_RXPROCESS_ID                            0x10u
#define CAN_GLOBAL_ID                               0x11u  // Not in spec but follows pattern
#define CAN_MAINFUNCTION_ERROR_SERVICE_ID           0x12u  // Not in spec but follows pattern

#if defined(CFG_PPC) || defined(CFG_TMS570) || defined(CFG_ZYNQ)

/* HOH flags */
#define CAN_HOH_FIFO_MASK           (1UL)

/* Controller flags */
#define CAN_CTRL_RX_PROCESSING_INTERRUPT        ((uint32)1u)
#define CAN_CTRL_RX_PROCESSING_POLLING          0u
#define CAN_CTRL_TX_PROCESSING_INTERRUPT        ((uint32)1u<<1u)
#define CAN_CTRL_TX_PROCESSING_POLLING          0u
#define CAN_CTRL_WAKEUP_PROCESSING_INTERRUPT    ((uint32)1u<<2u)
#define CAN_CTRL_WAKEUP_PROCESSING_POLLING      0u
#define CAN_CTRL_BUSOFF_PROCESSING_INTERRUPT    ((uint32)1u<<3u)
#define CAN_CTRL_BUSOFF_PROCESSING_POLLING      0u
#define CAN_CTRL_ACTIVATION                     ((uint32)1u<<4u)

#define CAN_CTRL_LOOPBACK                       ((uint32)1u<<5u)
#define CAN_CTRL_FIFO                           ((uint32)1u<<6u)

#define CAN_CTRL_ERROR_PROCESSING_INTERRUPT     ((uint32)1u<<7u)
#define CAN_CTRL_ERROR_PROCESSING_POLLING       0u

#elif defined(CFG_RH850)

/* HOH flags */
#define CAN_HOH_FIFO_MASK           (1UL)

/* Controller flags */
#define CAN_CTRL_RX_PROCESSING_INTERRUPT        (1UL)
#define CAN_CTRL_RX_PROCESSING_POLLING          0
#define CAN_CTRL_TX_PROCESSING_INTERRUPT        (1UL<<1)
#define CAN_CTRL_TX_PROCESSING_POLLING          0
#define CAN_CTRL_WAKEUP_PROCESSING_INTERRUPT    (1UL<<2)
#define CAN_CTRL_WAKEUP_PROCESSING_POLLING      0
#define CAN_CTRL_BUSOFF_PROCESSING_INTERRUPT    (1UL<<3)
#define CAN_CTRL_BUSOFF_PROCESSING_POLLING      0
#define CAN_CTRL_ACTIVATION                     (1UL<<4)

#define CAN_CTRL_LOOPBACK                       (1UL<<5)
#define CAN_CTRL_FIFO                           (1UL<<6)

#define CAN_CTRL_ERROR_PROCESSING_INTERRUPT    (1UL<<7)
#define CAN_CTRL_ERROR_PROCESSING_POLLING      0

#endif

typedef struct {
    uint32 txSuccessCnt;
    uint32 rxSuccessCnt;
    uint32 txErrorCnt;
    uint32 rxErrorCnt;
    uint32 boffCnt;
    uint32 fifoOverflow;
    uint32 fifoWarning;
} Can_Arc_StatisticsType;


#if defined(CFG_CAN_TEST)
typedef struct {
    uint64_t mbMaskTx;
    uint64_t mbMaskRx;
} Can_TestType;
#endif

/* Good things to know
 * L-PDU  - Link PDU
 *
 *
 */

/* Error from  CAN controller */
#if defined(CFG_RH850)
typedef union {
     uint32_t R;
     struct {
         uint32 BEF:1; /* Bus Error Flag */
         uint32 EWF:1; /*  Error Warning Flag */
         uint32 EPF:1; /*  Error Passive Flag */
         uint32 BOEF:1; /*  Bus Off Entry Flag */
         uint32 BORF:1; /*  Bus Off Recovery Flag */
         uint32 OVLF:1; /*  Overload Flag */
         uint32 BLF:1; /*  Bus Lock Flag */
         uint32 ALF:1; /*  Arbitration-lost Flag */
         uint32 SERR:1; /*  Stuff Error Flag */
         uint32 FERR:1; /*  Form Error Flag */
         uint32 AERR:1; /*  ACK Error Flag */
         uint32 CERR:1; /*  CRC Error Flag */
         uint32 B1ERR:1; /*  Recessive Bit Error Flag */
         uint32 B0ERR:1; /*  Dominant Bit Error Flag */
         uint32 ADERR:1; /*  ACK Delimiter Error Flag */
         uint32 :1; /* Reserved */
         uint32 CRCREG:15; /* CRC Calculation Data */
         uint32 :1; /* Reserved */
     } B;
 } Can_Arc_ErrorType;
#elif defined(CFG_TMS570) || defined(CFG_ZYNQ)
typedef union {
    uint32 R;
    struct {
        uint32:27;
        uint32 ACKER:1;
        uint32 BERR:1;
        uint32 STER:1;
        uint32 FMER:1;
        uint32 CRCER:1;
    } B;
  } Can_Arc_ErrorType;
#elif defined(CFG_MPC5777M)
 typedef union {
     volatile uint32_t R;
     struct {
         uint32:27;
         uint32 STE:1;		/* Stuff Error */
         uint32 FOE:1;       /* Format Error */
         uint32 ACKE:1;      /* Acknowledge Error */
         uint32 BE:1;        /* Bit Error */
         uint32 CRCE:1;      /* CRC Error */
     } B;
} Can_Arc_ErrorType;
#else
typedef union {
     uint32 R;
     struct {
         uint32:24;
         uint32 BIT1ERR:1;
         uint32 BIT0ERR:1;
         uint32 ACKERR:1;
         uint32 CRCERR:1;
         uint32 FRMERR:1;
         uint32 STFERR:1;
         uint32 TXWRN:1;
         uint32 RXWRN:1;
     } B;
 } Can_Arc_ErrorType;
#endif

#include "Can_Cfg.h"

/** @req 4.1.2/SWS_Can_00414 */
typedef struct {
    // Specifies the buadrate of the controller in kbps.
    uint16 CanControllerBaudRate;

    // Specifies propagation delay in time quantas.
    uint8 CanControllerPropSeg;

    // Specifies phase segment 1 in time quantas.
    uint8 CanControllerSeg1;

    // Specifies phase segment 2 in time quantas.
    uint8 CanControllerSeg2;

    // Specifies the resynchronization jump width in time quantas.
    uint8 CanControllerSyncJumpWidth;
} Can_ControllerBaudrateConfigType;

typedef enum {
    CAN_ID_TYPE_EXTENDED,
    CAN_ID_TYPE_MIXED,
    CAN_ID_TYPE_STANDARD
} Can_IdTypeType;

typedef enum {
    CAN_ARC_HANDLE_TYPE_BASIC,
    CAN_ARC_HANDLE_TYPE_FULL
} Can_Arc_HohType;


typedef enum {
    CAN_ARC_PROCESS_TYPE_INTERRUPT,
    CAN_ARC_PROCESS_TYPE_POLLING
} Can_Arc_ProcessType;

typedef uint32 Can_FilterMaskType;

typedef enum {
    CAN_OBJECT_TYPE_RECEIVE,
    CAN_OBJECT_TYPE_TRANSMIT
} Can_ObjectTypeType;


typedef struct {
    //  Specifies the InstanceId of this module instance. If only one instance is
    //  present it shall have the Id 0
    uint8 CanIndex;
} Can_GeneralType;

#if defined(CFG_ZYNQ)
typedef struct Can_HardwareFilterStruct {
    /* PC/PB Specifies (together with the filter mask) the identifiers range that passes
     *  the hardware filter. */
    uint32 CanHwFilterCode;

    /* PC/PB The filter mask that is used for hardware filtering together
     * with the CanHwFilterCode */
    uint32 CanHwFilterMask;
}Can_HardwareFilterType;
#endif

#if defined(CFG_ZYNQ)
typedef struct Can_HardwareObjectStruct {
    /* PC/PB Holds the handle ID of HRH or HTH. The value of this parameter is unique
    *  in a given CAN Driver, and it should start with 0 and continue without any
    *  gaps. The HRH and HTH Ids are defined under two different name-spaces.
    *  Example: HRH0-0, HRH1-1, HTH0-2, HTH1-3 */
    uint8 CanObjectId;

    /* PC/PB, Specifies the type (Full-CAN or Basic-CAN) of a hardware object. */
    Can_Arc_HohType CanHandleType;

    /* PC/PB, Specifies whether the IdValue is of type - standard identifier - extended
    * identifier - mixed mode ImplementationType: Can_IdType */
    Can_IdTypeType CanIdType;

    /* PC/PB, Specifies if the HardwareObject is used as Transmit or as Receive object */
    Can_ObjectTypeType CanObjectType;

    /* Size of the Filter assigned to the Hardware Object*/
    uint16 CanHwFilterSize;

    /* Pointer to the list of the Hardware Filters*/
    const Can_HardwareFilterType* const CanHwFilterPtr;
 } Can_HardwareObjectType;
#else
 typedef struct Can_HardwareObjectStruct {
     /* PC/PB, Specifies the type (Full-CAN or Basic-CAN) of a hardware object. */
     Can_Arc_HohType CanHandleType;

     /* PC/PB, Specifies whether the IdValue is of type - standard identifier - extended
      * identifier - mixed mode ImplementationType: Can_IdType */
     Can_IdTypeType CanIdType;

     /* PC/PB Specifies (together with the filter mask) the identifiers range that passes
      *  the hardware filter. */
     uint32 CanHwFilterCode;

     /* PC/PB Holds the handle ID of HRH or HTH. The value of this parameter is unique
      *  in a given CAN Driver, and it should start with 0 and continue without any
      *  gaps. The HRH and HTH Ids are defined under two different name-spaces.
      *  Example: HRH0-0, HRH1-1, HTH0-2, HTH1-3 */
     uint32 CanObjectId;

     /* PC/PB, Specifies if the HardwareObject is used as Transmit or as Receive object */
     Can_ObjectTypeType CanObjectType;

     /* PC/PB The filter mask that is used for hardware filtering together
      * with the CanHwFilterCode */
     Can_FilterMaskType CanHwFilterMask;
#if defined(CFG_PPC)

     /* PC,  See CAN_HOH_XX macros */
     uint32 Can_Arc_Flags;

     /* Bitmask of used message boxes */
#if defined(CFG_MPC5777M)
     uint32  Can_Arc_BufferMask;
#else
     uint64  ArcMailboxMask;
#endif

#elif defined(CFG_RH850)
     /* PC,  See CAN_HOH_XX macros */
     uint32 Can_Arc_Flags;
#elif defined(CFG_TMS570) || defined(CFG_JACINTO)
     uint8 Can_Arc_NrMessageBoxes;
     uint64  ArcMailboxMask;
     uint8 ArcCanControllerId;

     boolean Can_Arc_EOL;
#elif defined(CFG_STM32)
     // A "1" in this mask tells the driver that that HW Message Box should be
     // occupied by this Hoh. A "1" in bit 31(ppc) occupies Mb 0 in HW.
     uint32 Can_Arc_MbMask;

     // End Of List. Set to TRUE is this is the last object in the list.
     boolean Can_Arc_EOL;
#endif
 } Can_HardwareObjectType;
#endif
#if defined(CFG_ZYNQ)
typedef struct Can_ControllerConfigStruct{
    /* Defines if a CAN controller is used in the configuration - Currently not used. */
    bool CanControllerActivation;

    /* This parameter provides the controller ID which is unique in a given CAN
    Driver. The value for this parameter starts with 0 and continue without any gaps. */
    CanHwUnitIdType Can_Arc_HwUnitId;

    /* Specifies the default baud rate in kbps (from the list CanControllerSupportedBaudrates). */
    const Can_ControllerBaudrateConfigType *CanControllerDefaultBaudrate;

    /* Specifies the supported baud rates. */
    const Can_ControllerBaudrateConfigType * const CanControllerSupportedBaudrates;

    /* Specifices the length of the CanControllerSupportedBaudrates list. */
    uint16 CanControllerSupportedBaudratesCount;

    /* This parameter contains a reference to the Wakeup Source for this controller as defined
     in the ECU State Manager. Implementation Type: reference to EcuM_WakeupSourceType */
    uint32 CanWakeupSourceRef;

    /* List of Hoh id's that belong to this controller*/
    const Can_HardwareObjectType  * const Can_Arc_Hoh;

    /* Total number of HOHs in Can_Arc_Hoh */
    uint8 Can_Arc_HohCnt;

    /* Flags, See CAN_CTRL_XX macros */
    uint32 Can_Arc_Flags;

#if defined(CFG_CAN_USE_SYMBOLIC_CANIF_CONTROLLER_ID)
    uint8 Can_Arc_CanIfControllerId;
#endif

} Can_ControllerConfigType;
#else

typedef struct {

     boolean CanControllerActivation;

     //  This parameter provides the controller ID which is unique in a given CAN
     //  Driver. The value for this parameter starts with 0 and continue without any
     //  gaps.
#if defined(CFG_PPC)
     CanHwUnitIdType CanHwUnitId;
#elif defined(CFG_RH850)
     uint8 Can_Arc_HwUnitId;
#else
     CanControllerIdType CanControllerId;
#endif

     // Specifies the default baud rate in kbps (from the list CanControllerSupportedBaudrates)
#if defined(CFG_RH850)
     const Can_ControllerBaudrateConfigType *CanControllerDefaultBaudrate;
#else
     uint16 CanControllerDefaultBaudrate;
#endif

     // Specifies the supported baud rates
     const Can_ControllerBaudrateConfigType * const CanControllerSupportedBaudrates;

     // Specifices the length of the CanControllerSupportedBaudrates list
     uint16 CanControllerSupportedBaudratesCount;

     //  Reference to the CPU clock configuration, which is set in the MCU driver
     //  configuration
     uint32 CanCpuClockRef;

     //  This parameter contains a reference to the Wakeup Source for this
     //  controller as defined in the ECU State Manager. Implementation Type:
     //  reference to EcuM_WakeupSourceType
     uint32 CanWakeupSourceRef;

     // List of Hoh id's that belong to this controller
     const Can_HardwareObjectType  * const Can_Arc_Hoh;
#if defined(CFG_CAN_USE_SYMBOLIC_CANIF_CONTROLLER_ID)
     uint8 Can_Arc_CanIfControllerId;
#endif
#if defined(CFG_PPC)
     /* Flags, See CAN_CTRL_XX macros */
     uint32 Can_Arc_Flags;

     /* Number of FIFO MB in the HOH list */
     uint8 Can_Arc_HohFifoCnt;

     /* Total number of HOHs in Can_Arc_Hoh */
     uint8 Can_Arc_HohCnt;
#if defined(CFG_MPC5777M)
     uint64 Can_Arc_RxBufferMask;
     uint32 Can_Arc_TxBufferMask;
#else
     uint64 Can_Arc_RxMailBoxMask;
     uint64 Can_Arc_TxMailBoxMask;
#endif
     const uint8 * const Can_Arc_MailBoxToSymbolicHrh;

     PduIdType * const Can_Arc_TxPduHandles;

     uint8 Can_Arc_TxMailboxStart;

     uint8 Can_Arc_MailboxMax; //Used for MAXMB configuration in MCR

     uint8 Can_Arc_NumMsgBox;//Maximum number of message boxes available per controller
     
     boolean Can_Arc_ClockSrcOsc;

#elif defined(CFG_RH850)
     /* Flags, See CAN_CTRL_XX macros */
     uint32 Can_Arc_Flags;

     /* Total number of HOHs in Can_Arc_Hoh */
     uint32 Can_Arc_HohCnt;

     PduIdType * const Can_Arc_TxPduHandles;

     uint32 Can_Arc_RxFifoSz;
     
#elif defined(CFG_STM32)  || defined(CFG_JACINTO) || defined(CFG_TMS570)
     //  Enables / disables API Can_MainFunction_BusOff() for handling busoff
     //  events in polling mode.
     // INTERRUPT or POLLING
     Can_Arc_ProcessType CanBusOffProcessing;

     //  Enables / disables API Can_MainFunction_Read() for handling PDU
     //  reception events in polling mode.
     Can_Arc_ProcessType CanRxProcessing;

     //  Enables / disables API Can_MainFunction_Write() for handling PDU
     //  transmission events in polling mode.
     Can_Arc_ProcessType CanTxProcessing;

     //  Enables / disables API Can_MainFunction_Wakeup() for handling wakeup
     //  events in polling mode.
     Can_Arc_ProcessType CanWakeupProcessing;

     boolean Can_Arc_Loopback;

     const uint8 * const Can_Arc_MailBoxToHrh;

     // Set this to use the fifo
     boolean Can_Arc_Fifo;
#endif
#if defined(CFG_STM32)  || defined(CFG_JACINTO) || defined(CFG_TMS570)
     // A "1" in this mask tells the driver that that HW Message Box should be
     // occupied by this Hoh. A "1" in bit 31(ppc) occupies Mb 0 in HW.
     uint32 Can_Arc_MbMask;

     // End Of List. Set to TRUE is this is the last object in the list.
     boolean Can_Arc_EOL;
     // Specifies propagation delay in time quantas.
     uint32 CanControllerPropSeg;

     // Specifies phase segment 1 in time quantas.
     uint32 CanControllerSeg1;

     // Specifies phase segment 2 in time quantas.
     uint32 CanControllerSeg2;
#endif
 } Can_ControllerConfigType;
#endif

typedef struct {
    const Can_ControllerConfigType *CanController;

#if defined(CFG_PPC) || defined(CFG_TMS570) || defined(CFG_ZYNQ)
    const  uint8 * const ArcHthToSymbolicController;
    const  uint8 * const ArcHthToHoh;
    const  uint8 * const ArcHwUnitToController;
    const Can_HwHandleType * const ArcSymbolicHohToInternalHoh;
#elif defined(CFG_RH850)
    const  uint8 * const ArcHthToSymbolicController;
    const  uint8 * const ArcHthToHoh;
    const  uint8 * const ArcHwUnitToController;
    const Can_HwHandleType * const ArcSymbolicHohToInternalHoh;
#endif

#if defined(CFG_TMS570) || defined(CFG_JACINTO)
    const Can_HardwareObjectType * const ArcCanHardwareObjects;
#endif
} Can_ConfigSetType;

/** @req 4.1.2/SWS_Can_00413 *//* Can_ConfigType */
typedef struct {
     // This is the multiple configuration set container for CAN Driver
     // Multiplicity 1..*
     const Can_ConfigSetType  *CanConfigSetPtr;
 } Can_ConfigType;

 /* Publish the configuration */
extern const Can_ConfigType CanConfigData;

/**
 * Initializes the CAN driver
 * @param Config - a pointer to the configuration that is used during initialization
 */
void Can_Init( const Can_ConfigType *Config );
#if ( CAN_VERSION_INFO_API == STD_ON )
/**
 * Gets version info
 * @param versioninfo - out parameter filled with version info
 */
void Can_GetVersionInfo( Std_VersionInfoType* versioninfo);
#endif


/**
 * Checks if a baudrate is supported for a controller
 * @param Controller - controller id
 * @param Baudrate - in kbps
 * @return E_OK if supported, otherwiese E_NOT_OK
 */
Std_ReturnType Can_CheckBaudrate(uint8 Controller, const uint16 Baudrate);


/**
 * Changes baudrate for a controller
 * @param Controller - controller id
 * @param Baudrate - in kpbs
 * @return E_OK if baudrate is changed, otherwise E_NOT_OK
 */
Std_ReturnType Can_ChangeBaudrate(uint8 Controller, const uint16 Baudrate);


/**
 * This service shall set the baud rate configuration of the CAN controller. Depending
 * on necessary baud rate modifications the controller might have to reset.
 *
 * @param Controller
 * @param BaudRateConfigID
 * @return
 */
Std_ReturnType Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID );

/**
 * Changes the controller mode
 * @param Controller - controller id
 * @param Transition - type of transition to be made
 * @return CAN_OK if request accepted, otherwise CAN_NOT_OK
 */
Can_ReturnType Can_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition );


/**
 * Disables interrupts for a controller
 * @param Controller - controller id
 */
void Can_DisableControllerInterrupts( uint8 Controller );


/**
 * Enables interrupts for a controller
 * @param Controller - controller id
 */
void Can_EnableControllerInterrupts( uint8 Controller );


/**
 * Checks if a wakeup has occurred for a given controller
 * @param Controller - controller id
 * @return CAN_OK if wakeup was detected, otherwise CAN_NOT_OK
 */
Can_ReturnType Can_CheckWakeup( uint8 Controller );


/**
 *
 * @param Hth - the HardwareTransmitHandle to be used
 * @param PduInfo - pointer to SDU
 * @return CAN_OK if write was accepted, CAN_NOT_OK if error occurred, CAN_BUSY if not buffer available
 */
Can_ReturnType Can_Write( Can_HwHandleType Hth, const Can_PduType *PduInfo );


#if (CAN_USE_WRITE_POLLING == STD_ON)
/**
 * This function performs the polling of TX confirmation and TX cancellation
 * confirmation when CAN_TX_PROCESSING is set to POLLING.
 */
void Can_MainFunction_Write( void );
#else
/** @req 4.0.3/CAN178 *//** @req 4.1.2/SWS_Can_00178 */
#define Can_MainFunction_Write()
#endif


#if (CAN_USE_READ_POLLING == STD_ON)
/**
 * This function performs the polling of RX indications when
 * CAN_RX_PROCESSING is set to POLLING.
 */
void Can_MainFunction_Read( void );
#else
/** @req 4.0.3/CAN180 *//** @req 4.1.2/SWS_Can_00180 */
#define Can_MainFunction_Read()
#endif


#if (CAN_USE_BUSOFF_POLLING == STD_ON)
/**
 * This function performs the polling of bus-off events that are configured statically as
 * 'to be polled'.
 */
void Can_MainFunction_BusOff( void );
#else
/** @req 4.0.3/CAN183 *//** @req 4.1.2/SWS_Can_00183 */
#define Can_MainFunction_BusOff()
#endif


#if (CAN_USE_WAKEUP_POLLING == STD_ON)
/**
 * This function performs the polling of wake-up events that are configured statically
 * as 'to be polled'.
 */
void Can_MainFunction_Wakeup( void );
#else
/** @req 4.0.3/CAN185 *//** @req 4.1.2/SWS_Can_00185 */
#define Can_MainFunction_Wakeup()
#endif


/**
 * This function performs the polling of CAN controller mode transitions.
 */
void Can_MainFunction_Mode( void );

/* ArcCore specific */
#if (ARC_CAN_ERROR_POLLING == STD_ON)
/**
 * This function performs polling of CAN controller errors. Added by Arccore.
 */
void Can_Arc_MainFunction_Error( void );
#endif


/**
 * Get send/receive/error statistics for a controller
 *
 * @param controller - Controller id
 * @param stats - Pointer to buffer to copy statistics into
 */
void Can_Arc_GetStatistics( uint8 controller, Can_Arc_StatisticsType * stat);


/**
 * Deinites the CAN driver (added by ArcCore and not a part of the standard)
 */
void Can_Arc_DeInit(void);
void Can_Arc_Hw_DeInit(void);

#ifdef HOST_TEST
/**
 * Checks that the module is in the state CAN_UNINIT.
 *
 * @return E_OK if module is in state CAN_UNINIT, else E_NOT_OK.
 */
Std_ReturnType Can_Test_DriverStateIsUninit(void);

/**
 * Checks that the module is in the state CAN_READY.
 *
 * @return E_OK if module is in state CAN_READY, else E_NOT_OK.
 */
Std_ReturnType Can_Test_DriverStateIsReady(void);

/**
 * Checks that all hardware units in the module are in the state state.
 *
 * Cannot be called before Can_Init.
 *
 * @param state The state the hardware units are expected to be in.
 * @return E_OK if all units are in the expected state, else E_NOT_OK.
 */
Std_ReturnType Can_Test_AllUnitsInState(CanIf_ControllerModeType state);
#endif /* HOST_TEST */

#endif /*CAN_H_*/
