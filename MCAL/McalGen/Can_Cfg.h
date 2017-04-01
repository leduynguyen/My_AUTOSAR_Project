
/*
 * Generator version: 5.0.0
 * AUTOSAR version:   4.1.2
 */

#ifndef CAN_CFG_H_
#define CAN_CFG_H_

#if !(((CAN_SW_MAJOR_VERSION == 5) && (CAN_SW_MINOR_VERSION == 0)) )
#error Can: Configuration file expected BSW module version to be 5.0.*
#endif

#if !(((CAN_AR_MAJOR_VERSION == 4) && (CAN_AR_MINOR_VERSION == 1)) )
#error Can: Configuration file expected AUTOSAAR version to be 4.1.*
#endif

// Number of controller configs
#define CAN_ARC_CTRL_CONFIG_CNT			1

#define CAN_DEV_ERROR_DETECT			STD_ON
#define CAN_VERSION_INFO_API			STD_ON
#define CAN_MULTIPLEXED_TRANSMISSION	STD_OFF  // Not supported
#define CAN_WAKEUP_SUPPORT				STD_OFF  // Not supported
#define CAN_HW_TRANSMIT_CANCELLATION	STD_OFF  // Not supported
#define CAN_USE_WRITE_POLLING			STD_OFF  // Not supported
#define CAN_USE_READ_POLLING			STD_OFF  // Not supported
#define CAN_USE_BUSOFF_POLLING			STD_OFF  // Not supported
#define CAN_USE_WAKEUP_POLLING			STD_OFF  // Not supported

#define NO_CANIF_CONTROLLER 0xFF

typedef enum {
	CAN_CTRL_1 = 0,
	CAN_CTRL_2 = 1,
	CAN_CONTROLLER_CNT = 2
} CanControllerIdType;
  
#define CanConf_CanController_CanController	(CanControllerIdType)0
#define Can_CanController	CanConf_CanController_CanController
#define CanConf_CanHardwareObject_CanHardwareObjectTx (Can_HwHandleType)0
#define Can_CanHardwareObjectTx CanConf_CanHardwareObject_CanHardwareObjectTx
#define NUM_OF_HTHS (Can_HwHandleType)1

#define CanConf_CanHardwareObject_CanHardwareObjectRx (Can_HwHandleType)1
#define Can_CanHardwareObjectRx CanConf_CanHardwareObject_CanHardwareObjectRx


/* Configuration Set Handles */
#define CanConfigSet (CanConfigData)
#define Can_CanConfigSet (CanConfigData)

#endif /*CAN_CFG_H_*/

