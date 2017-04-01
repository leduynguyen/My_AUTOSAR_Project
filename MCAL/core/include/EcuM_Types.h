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

/**
 * @addtogroup EcuM ECU State Manager
 * @{
 *
 * @file EcuM_Types.h
 * Typedefs needed by EcuM module. Note that types that are generated together with
 * Ecum Service Ports should be guarded by _DEFINED_TYPEDEF_FOR_<Type>_ to avoid re-definition.
 */

/* @req EcuM4037 */



#ifndef ECUM_TYPES_H_
#define ECUM_TYPES_H_

#include "Std_Types.h"
#include "Os.h"

#if defined(RTE_TYPE_H) && defined(__GNUC__)
//#warning RTE_TYPE included before EcuM_Types.h
#endif

/* @req EcuMf0001 */  /* @req EcuM3025 */
#include "Rte_EcuM_Type.h"

/** Enum literals for EcuM_StateType */
/* @req EcuMf507 */
/* @req EcuMf2664 */
#ifndef ECUM_SUBSTATE_MASK
#define ECUM_SUBSTATE_MASK 15U
#endif /* ECUM_SUBSTATE_MASK */

#ifndef ECUM_STATE_STARTUP
#define ECUM_STATE_STARTUP 16U
#endif /* ECUM_STATE_STARTUP */

#ifndef ECUM_STATE_STARTUP_ONE
#define ECUM_STATE_STARTUP_ONE 17U
#endif /* ECUM_STATE_STARTUP_ONE */

#ifndef ECUM_STATE_STARTUP_TWO
#define ECUM_STATE_STARTUP_TWO 18U
#endif /* ECUM_STATE_STARTUP_TWO */

#ifndef ECUM_STATE_WAKEUP
#define ECUM_STATE_WAKEUP 32U
#endif /* ECUM_STATE_WAKEUP */

#ifndef ECUM_STATE_WAKEUP_ONE
#define ECUM_STATE_WAKEUP_ONE 33U
#endif /* ECUM_STATE_WAKEUP_ONE */

#ifndef ECUM_STATE_WAKEUP_VALIDATION
#define ECUM_STATE_WAKEUP_VALIDATION 34U
#endif /* ECUM_STATE_WAKEUP_VALIDATION */

#ifndef ECUM_STATE_WAKEUP_REACTION
#define ECUM_STATE_WAKEUP_REACTION 35U
#endif /* ECUM_STATE_WAKEUP_REACTION */

#ifndef ECUM_STATE_WAKEUP_TWO
#define ECUM_STATE_WAKEUP_TWO 36U
#endif /* ECUM_STATE_WAKEUP_TWO */

#ifndef ECUM_STATE_WAKEUP_WAKESLEEP
#define ECUM_STATE_WAKEUP_WAKESLEEP 37U
#endif /* ECUM_STATE_WAKEUP_WAKESLEEP */

#ifndef ECUM_STATE_WAKEUP_TTII
#define ECUM_STATE_WAKEUP_TTII 38U
#endif /* ECUM_STATE_WAKEUP_TTII */

#ifndef ECUM_STATE_RUN
#define ECUM_STATE_RUN 48U
#endif /* ECUM_STATE_RUN */

#ifndef ECUM_STATE_APP_RUN
#define ECUM_STATE_APP_RUN 50U
#endif /* ECUM_STATE_APP_RUN */

#ifndef ECUM_STATE_APP_POST_RUN
#define ECUM_STATE_APP_POST_RUN 51U
#endif /* ECUM_STATE_APP_POST_RUN */

#ifndef ECUM_STATE_SHUTDOWN
#define ECUM_STATE_SHUTDOWN 64U
#endif /* ECUM_STATE_SHUTDOWN */

#ifndef ECUM_STATE_PREP_SHUTDOWN
#define ECUM_STATE_PREP_SHUTDOWN 68U
#endif /* ECUM_STATE_PREP_SHUTDOWN */

#ifndef ECUM_STATE_GO_SLEEP
#define ECUM_STATE_GO_SLEEP 73U
#endif /* ECUM_STATE_GO_SLEEP */

#ifndef ECUM_STATE_GO_OFF_ONE
#define ECUM_STATE_GO_OFF_ONE 77U
#endif /* ECUM_STATE_GO_OFF_ONE */

#ifndef ECUM_STATE_GO_OFF_TWO
#define ECUM_STATE_GO_OFF_TWO 78U
#endif /* ECUM_STATE_GO_OFF_TWO */

#ifndef ECUM_STATE_SLEEP
#define ECUM_STATE_SLEEP 80U
#endif /* ECUM_STATE_SLEEP */

#ifndef ECUM_STATE_OFF
#define ECUM_STATE_OFF 128U
#endif /* ECUM_STATE_OFF */

#ifndef ECUM_STATE_RESET
#define ECUM_STATE_RESET 144U
#endif /* ECUM_STATE_RESET */

/** Enum literals for EcuM_BootTargetType */
#ifndef ECUM_BOOT_TARGET_APP
#define ECUM_BOOT_TARGET_APP 0U
#endif /* ECUM_BOOT_TARGET_APP */

#ifndef ECUM_BOOT_TARGET_OEM_BOOTLOADER
#define ECUM_BOOT_TARGET_OEM_BOOTLOADER 1U
#endif /* ECUM_BOOT_TARGET_OEM_BOOTLOADER */

#ifndef ECUM_BOOT_TARGET_SYS_BOOTLOADER
#define ECUM_BOOT_TARGET_SYS_BOOTLOADER 2U
#endif /* ECUM_BOOT_TARGET_SYS_BOOTLOADER */

#if 0
enum {
    /** Internal reset of �C (bit 2).
     *  The internal reset typically only resets the �C
     *  core but not peripherals or memory
     *  controllers. The exact behavior is hardware
     *  specific.
     *  This source may also indicate an unhandled
     *  exception. */
    ECUM_WKSOURCE_INTERNAL_RESET = 0x04,

    /** Reset by external watchdog (bit 4), if
     *  detection supported by hardware */
    ECUM_WKSOURCE_EXTERNAL_WDG = 0x10,

    /** Reset by internal watchdog (bit 3) */
    ECUM_WKSOURCE_INTERNAL_WDG = 0x08,

    /** Power cycle (bit 0) */
    ECUM_WKSOURCE_POWER = 0x01,

    /** Hardware reset (bit 1).
     *  If hardware cannot distinguish between a
     *  power cycle and a reset reason, then this
     *  shall be the default wakeup source */
    ECUM_WKSOURCE_RESET = 0x02
};

#endif
/* @req EcuM4040 */
typedef uint32 EcuM_WakeupSourceType;

/* @req EcuM4041 */
typedef enum
{
    ECUM_WKSTATUS_NONE = 0,        /**< No pending wakeup event was detected */
    ECUM_WKSTATUS_PENDING = 1,     /**< The wakeup event was detected but not yet validated */
    ECUM_WKSTATUS_VALIDATED = 2,   /**< The wakeup event is valid */
    ECUM_WKSTATUS_EXPIRED = 3,     /**< The wakeup event has not been validated and has expired therefore */
    ECUM_WKSTATUS_DISABLED = 4     /**< The wakeup source is disabled and does not detect wakeup events. */
} EcuM_WakeupStatusType;


#if defined(USE_WDGM)
#include "WdgM.h"
#endif

#include "Mcu.h"

#if defined(USE_COMM)
#include "ComM.h"
#endif

typedef struct EcuM_WakeupSourceConfig {
    EcuM_WakeupSourceType 	EcuMWakeupSourceId;
    uint32 					EcuMValidationTimeout;
#if defined(USE_COMM)
    uint8 					EcuMComMChannel;
#endif
} EcuM_WakeupSourceConfigType;

typedef struct EcuM_SleepMode
{
   uint8 					EcuMSleepModeId;
   EcuM_WakeupSourceType 	EcuMWakeupSourceMask;
   Mcu_ModeType  			EcuMSleepModeMcuMode;
 } EcuM_SleepModeType;

#if defined(USE_COMM)
typedef struct EcuM_ComMConfig {
    uint8                   EcuMComMNetworkHandle;
    ComM_BusTypeType        EcuMComBusType;
} EcuM_ComMConfigType;
#endif

typedef AppModeType EcuM_AppModeType;


 /* Defines for illegal modes/channels */
#define ECUM_SLEEP_MODE_WDGM_MODE_ILL		0xff
#define ECUM_COMM_CHANNEL_ILL				0xff
#define ECUM_VALIDATION_TIMEOUT_ILL   0xffffffffuL

#endif /* ECUM_TYPES_H_ */
/** @} */
