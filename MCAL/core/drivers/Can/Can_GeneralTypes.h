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
/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ|PPC|RH850F1H|MPC5607B|MPC5645S|MPC5777M|JACINTO5|JACINTO6|TMS570|STM32|MPC5748G */

#ifndef CAN_GENERALTYPES_H_
#define CAN_GENERALTYPES_H_

/** @req 4.1.2/SWS_Can_00436 Shared types between Can, CanIf, and CanTrcv */
/** @req 4.1.2/SWS_Can_00439 */
/** @req 4.1.2/SWS_Can_00487 */

/** @req 4.0.3/CAN429 *//** @req 4.1.2/SWS_Can_00429 */
typedef uint8 Can_HwHandleType;

/** @req 4.0.3/CAN039 *//** @req 4.1.2/SWS_Can_00039 */
typedef enum {
    CAN_OK,
    CAN_NOT_OK,
    CAN_BUSY
} Can_ReturnType;

/** @req 4.0.3/CAN417 *//** @req 4.1.2/SWS_Can_00417 */
typedef enum {
    CAN_T_START,
    CAN_T_STOP,
    CAN_T_SLEEP,
    CAN_T_WAKEUP
} Can_StateTransitionType;

/* @req 4.1.3/SWS_CanTrcv_00163 */
/** Operating modes of the CAN Transceiver Driver. */
typedef enum {
    /** Transceiver mode NORMAL. */
    CANTRCV_TRCVMODE_NORMAL = 0,

    /**  Transceiver mode SLEEP. */
    CANTRCV_TRCVMODE_SLEEP,

    /** Transceiver mode STANDBY. */
    CANTRCV_TRCVMODE_STANDBY,

    /** Transceiver mode not Initialized */
//QQ    CANTRCV_TRCVMODE_UNITIALIZED
} CanTrcv_TrcvModeType;

/* @req 4.1.3/SWS_CanTrcv_00164 */
/** CanTrcv_TrcvWakeupModeType type shall be used to control the CAN transceiver
  * concerning wake up events and wake up notifications. */
typedef enum {
    /** The notification for wakeup events is enabled on the addressed transceiver. */
    CANTRCV_WUMODE_ENABLE = 0,

    /** A stored wakeup event is cleared on the addressed transceiver. */
    CANTRCV_WUMODE_CLEAR,

    /** The notification for wakeup events is disabled on the addressed transceiver. */
    CANTRCV_WUMODE_DISABLE
} CanTrcv_TrcvWakeupModeType;

/* @req 4.1.3/SWS_CanTrcv_00165 */
/** CanTrcv_TrcvWakeupReasonType type denotes the wake up reason detected by
  * the CAN transceiver in detail. */
typedef enum {
    /** Due to an error wake up reason was not detected. This value may only be
    * reported when error was reported to DEM before. */
  CANTRCV_WU_ERROR = 0,

  /** The transceiver has detected, that the network has caused the wake up of
    * the ECU. */
  CANTRCV_WU_BY_BUS,

  /** The transceiver has detected a wake-up event at one of the transceiver's
    * pins (not at the CAN bus). */
  CANTRCV_WU_BY_PIN,

  /** The transceiver has detected, that the network has woken up by the ECU
    * via a request to NORMAL mode. */
  CANTRCV_WU_INTERNALLY,

  /** The transceiver does not support any information for the wake up reason. */
  CANTRCV_WU_NOT_SUPPORTED,

  /** The transceiver has detected, that the "wake up" is due to an ECU reset
    * after power on. */
  CANTRCV_WU_POWER_ON,

  /** The transceiver has detected, that the "wake up" is due to an ECU reset. */
  CANTRCV_WU_RESET,

  /** The transceiver has detected, that the wake up of the ECU was caused by
    * a HW related device failure. */
  CANTRCV_WU_BY_SYSERR
} CanTrcv_TrcvWakeupReasonType;


/** @req 4.0.3/CAN416 *//** @req 4.1.2/SWS_Can_00416 */
/* uint16: if only Standard IDs are used */
/* uint32: if also Extended IDs are used */
typedef uint32 Can_IdType;

/** @req 4.0.3/CAN415 *//** @req 4.1.2/SWS_Can_00415 */
typedef struct Can_PduType_s {
    /* private data for CanIf,just save and use for callback */
    PduIdType   swPduHandle;
    /* Length, max 8 bytes */
    uint8       length;
    /* the CAN ID, 29 or 11-bit */
    Can_IdType  id;
    /*  data ptr */
    uint8       *sdu;
} Can_PduType;


#endif /* CAN_GENERALTYPES_H_ */
