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

/* ----------------------------[information]----------------------------------*/
/*
 * Author: ?+mahi
 *
 *
 * Description:
 *   Implements the EcuM (fixed) module
 *
 * Support:
 *   General                  Have Support
 *   -------------------------------------------
 *   ECUM_TTII_ENABLED            		N
 *   ECUM_DEV_ERROR_DETECT				Y
 *   ECUM_VERSION_INFO_API				Y
 *   ECUM_INCLUDE_DEM					N (controlled by USE_x macro's instead)
 *   ECUM_INCLUDE_NVRAM_MGR				N (controlled by USE_x macro's instead)
 *   ECUM_INLCUDE_DET					N (controlled by USE_x macro's instead)
 *   ECUM_MAIN_FUNCTION_PERDIOD			Y
 *   ECUM_TTII_WKSOURCE					N
 *
 *   Configuration            Have Support
 *   -------------------------------------------
 *   ECUM_SLEEP_ACTIVITY_PERIOD			?
 *   ECUM_CONFIGCONSISTENCY_HASH		N
 *   ECUM_RUN_SELF_REQUEST_PERIOD		?
 *   ECUM_NVRAM_WRITEALL_TIMEOUT		Y
 *   ECUM_DEFAULT_APP_MODE				?
 *
 *
 *   DefaultShutdownTarget
 *   -------------------------------------------
 *   ECUM_DEFAULT_SHUTDOWN_TARGET		N
 *
 * Implementation Notes:
 *
 *   3.1.x
 *    From ComM
 *      - EcuM_ComM_RequestRUN(channel)
 *      - EcuM_ComM_ReleaseRUN(channel)
 *      - EcuM_ComM_HasRequestedRUN(channel)
 *    From EcuM:
 *      - ComM_EcuM_RunModeIndication(channel)
 *      - ComM_EcuM_WakeUpIndication(channel)
 *
 *   4.x
 *    From ComM
 *       None :)
 *
 *    From EcuM:
 *      - ComM_CommunicationAllowed(channel)
 *      - ComM_GetState(channel, &state)
 *      - ComM_EcuM_WakeUpIndication(channel)
 *
 */

//lint -emacro(904,VALIDATE,VALIDATE_RV,VALIDATE_NO_RV) //904 PC-Lint exception to MISRA 14.7 (validate macros).
/* ----------------------------[includes]------------------------------------*/

/* @req EcuM2986 */ /* @req EcuM2987 */
/* @req EcuM3009 */ /* @req EcuM3023 */
/* @req EcuM2862 */  /* @req EcuMf2862 */
/* @req EcuM2810 */  /* @req EcuMf2810 */
/* @req EcuM2757 */ /* The ECU Manager shall treat all errors immediately as errors. */
/* @req EcuM2758 */ /* The ECU Manager shall not recover from an error */
/* @req EcuM2759 */ /* The ECU Manager Module shall report all errors as events. */
/* @req EcuM2763.partially */
/* @req EcuM2858 */
/* @req EcuM2859 */
/* @req EcuM2985 */ /* EcuM doesn't do anything to switch off Dem */
/* @req EcuM2977.partially */ /* Since alarm clock is not supported */
/* @req EcuM2988.partially */ /* EcuM_Lcfg.c is not created */
/** These requirements are supported in .swcd file */
/* @req EcuM3018 */ /* @req EcuM3017 */ /* @req EcuM3012 */ /* @req EcuM3011 */ /* @req EcuM2979 */

#include "Std_Types.h"
#include "EcuM.h"
#include "Modules.h"
#include <string.h>
#include <Os.h>
#include "EcuM_Generated_Types.h"
#include "EcuM_Internals.h"
#include "EcuM_Cbk.h"
#include "SchM_EcuM.h"
#include "MemMap.h"
#include "Mcu.h"
#include "ComStack_Types.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"                /* @req EcuM2875 */   /* @req EcuMf2875 */
#endif
#include "isr.h"
#if defined(USE_NVM)
#include "NvM.h"
#endif
#if defined(USE_RTE)
/* @req EcuMf0001 */
#include "Rte_Main.h"
#endif
#if defined(USE_SCHM)
#include "SchM.h"
#endif

//#define USE_LDEBUG_PRINTF
#include "debug.h"

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
#if  ( ECUM_DEV_ERROR_DETECT == STD_ON )
boolean CheckWakupSourceValidity(EcuM_WakeupSourceType sources, uint8 FunctionId);
#endif

/* ----------------------------[private variables]---------------------------*/

 /* @req EcuM4035 */
EcuM_GlobalType EcuM_World;

/* ----------------------------[private functions]---------------------------*/

#if !defined(USE_BSWM)
#define BswM_EcuM_CurrentWakeup(source, state)
#endif

#if  ( ECUM_DEV_ERROR_DETECT == STD_ON )
boolean CheckWakupSourceValidity(EcuM_WakeupSourceType sources, uint8 FunctionId) {
    EcuM_WakeupSourceType wkSource;
    const EcuM_SleepModeType *sleepModePtr;
    boolean status;
    status = TRUE;

    sleepModePtr = &EcuM_World.config->EcuMSleepModeConfig[EcuM_World.sleep_mode];
    wkSource =  sleepModePtr->EcuMWakeupSourceMask;

    /* 4.0.3/EcuM2625 */
    /* Predefined source does not require validation */
    if ( ( sources & (ECUM_WKSOURCE_POWER | ECUM_WKSOURCE_RESET
                    | ECUM_WKSOURCE_INTERNAL_RESET | ECUM_WKSOURCE_INTERNAL_WDG
                    | ECUM_WKSOURCE_EXTERNAL_WDG) ) != 0 ) {
        status = TRUE;
    }

    else if( !((sources | wkSource) ==  wkSource)) {
        DET_REPORT_ERROR(FunctionId, ECUM_E_UNKNOWN_WAKEUP_SOURCE );
        /*lint -e{904} Return statement is necessary in case of reporting a DET error */
        return FALSE;
    } else {
        /* do nothing */
    }

    return status;
}
#else
#define CheckWakupSourceValidity(sources, FunctionId) (FALSE)
#endif


#if defined(CFG_POSTBUILD)
static boolean ValidatePostBuildConfiguration(const EcuM_ConfigType* config) {

    boolean status;
    status = TRUE;

    /* The hash is calculated both when generating the pre compile configuration
     * and the postbuild configuration. It is based on all pre compile configuration
     * parameters.
     * Generator version and vendor id also needs to be a part of the input to the
     * hash.
     */

    /* Chech that the pointer at least isn't NULL */
    if (config->PostBuildConfig == NULL) {
        status = FALSE;
    }

    /* Just a basic check that the it seems to be a valid post build area */
    else if (0x5A5A5A5A != config->PostBuildConfig->startPattern) {
        status = FALSE;
    }

    /* Check the variant  */
    else if (config->EcuMPostBuildVariant != config->PostBuildConfig->postBuildVariant) {
        status = FALSE;
    }

    /* Check the hash */
    else if ((config->EcuMConfigConsistencyHashLow != config->PostBuildConfig->preCompileHashLow) ||
        (config->EcuMConfigConsistencyHashHigh != config->PostBuildConfig->preCompileHashHigh)) {
        status = FALSE;
    } else {
        status = TRUE;
    }
    return status;
}

#endif

/* ----------------------------[public functions]----------------------------*/

#if !defined(USE_DET) && (ECUM_DEV_ERROR_DETECT == STD_ON)
#error EcuM configuration error. DET is not enabled when ECUM_DEV_ERROR_DETECT is set
#endif

/* @req EcuM2411 */  /* @req EcuMf2411 */ /* @req EcuM2684 */
/* @req EcuM2980 */ /* Init function of all Bsw modules doesn't have return value hence error is ignored implicitly  */
/**
 * Initialize EcuM.
 */
void EcuM_Init(void) {
    Mcu_ResetType resetReason;
    /* @req EcuM4015 */
    boolean ret;
    ret = TRUE;
    /*lint -e506 -e774 Always true for single core MCUs */
    if (OS_CORE_IS_ID_MASTER(GetCoreID())) {
        Std_ReturnType status;
#if defined(USE_ECUM_FIXED)
        SetCurrentState(ECUM_STATE_STARTUP_ONE);
#endif
        // Initialize drivers that are needed to determine PostBuild configuration
        EcuM_AL_DriverInitZero();
        // Initialize the OS
        InitOS();
        // Setup interrupts
        Os_IsrInit();
        // Determine PostBuild configuration
        EcuM_World.config = EcuM_DeterminePbConfiguration();

#if defined(CFG_POSTBUILD)
        /* @req EcuMf2796 @req EcuMf2798 */ /* @req EcuM2796 @req EcuM2798 */
        if (FALSE == ValidatePostBuildConfiguration(EcuM_World.config)) {
#if defined(USE_DEM)
            EcuM_ErrorHook(EcuM_World.config->EcuMDemInconsistencyEventId);
#endif
            ret = FALSE;
        }
#endif
        if (ret == TRUE) {
            // Initialize drivers needed before the OS-starts
            EcuM_AL_DriverInitOne(EcuM_World.config);

            resetReason = Mcu_GetResetReason();
            // Determine the reset/wakeup reason
            /* @req EcuM2623 */ /* @req EcuMf2623 *//* Validated immediately */
            switch (resetReason) {
            case MCU_POWER_ON_RESET:
                EcuM_ValidateWakeupEvent(ECUM_WKSOURCE_POWER);
                break;
            case MCU_SW_RESET:
                EcuM_ValidateWakeupEvent(ECUM_WKSOURCE_RESET);
                break;
            case MCU_RESET_UNDEFINED:
                break;
            case MCU_WATCHDOG_RESET:
                EcuM_ValidateWakeupEvent(ECUM_WKSOURCE_INTERNAL_WDG);
                break;
            default:
                EcuM_Arc_RememberWakeupEvent((uint32)resetReason);
                break;
            }

            /* Moved this here because EcuM_SelectShutdownTarget needs us to be initilized.*/
            EcuM_World.initiated = TRUE;

            /* Set default shutdown target */
            /* @req EcuM2181 */  /* @req EcuMf2181 */
            status = EcuM_SelectShutdownTarget(EcuM_World.config->EcuMDefaultShutdownTarget,
                                               EcuM_World.config->EcuMDefaultSleepMode);/** @req EcuM2181 */
            if (status == E_OK) {

#if defined(USE_COMM) && (ECUM_AR_VERSION < 40000)
                EcuM_World.run_comm_requests = 0;
#endif
                EcuM_World.run_requests = 0;
                EcuM_World.postrun_requests = 0;
#if (ECUM_RESET_LOOP_DETECTION == STD_ON)
                /* NOTE: This returns true if a loop is detected. The spec does not say */
                /*      what to do if that happens. */
                (void)EcuM_LoopDetection();
#endif
                // Start this baby up
                /* @req EcuMf0010 */
                /* @req EcuM2603 */  /* @req EcuMf2603 */
#if (OS_NUM_CORES > 1)
                StatusType coreStatus;
                StartCore(GetCoreID() + 1, &coreStatus);
#endif

                StartOS(EcuM_World.config->EcuMDefaultAppMode);  /* @req EcuMf2243 */
            }
        }
    } else { /* @req EcuM4017 */
        InitOS();
        Os_IsrInit();
#if (OS_NUM_CORES > 1 )
        StatusType coreStatus;
        StartCore(GetCoreID() + 1, &coreStatus);
#endif
        StartOS(OSDEFAULTAPPMODE);
    }
}

/* @req EcuM4020 */
// Typically called from OS shutdown hook
void EcuM_Shutdown(void) {
#if defined(USE_ECUM_FIXED)
    SetCurrentState(ECUM_STATE_GO_OFF_TWO);
#endif

    // Let the last drivers do a nice shutdown
    EcuM_OnGoOffTwo();

    if (EcuM_World.shutdown_target == ECUM_STATE_OFF) {
        EcuM_AL_SwitchOff();          /* @req EcuM4075 */
    } else {
#if defined(USE_ECUM_FIXED)
#if (MCU_PERFORM_RESET_API == STD_ON)
        Mcu_PerformReset();
#else
        for(;;)
        {
            ;
        }
#endif
#elif defined(USE_ECUM_FLEXIBLE)
            EcuM_AL_Reset(EcuM_World.sleep_mode);  /* @req EcuM4074 */
#endif
    }
}

Std_ReturnType EcuM_SelectBootTarget(EcuM_BootTargetType target) {
    VALIDATE_RV(EcuM_World.initiated, ECUM_SELECT_BOOTARGET_ID, ECUM_E_UNINIT, E_NOT_OK);

    // Not supported
    (void)target;
    return E_NOT_OK;
}

Std_ReturnType EcuM_GetBootTarget(EcuM_BootTargetType* target) {
    VALIDATE_RV(EcuM_World.initiated, ECUM_GET_BOOTARGET_ID, ECUM_E_UNINIT, E_NOT_OK);
    /* @req EcuMf035 */
    VALIDATE_RV(target != NULL, ECUM_GET_BOOTARGET_ID, ECUM_E_NULL_POINTER, E_NOT_OK);

    // Not supported
    //lint -estring(920,pointer)  /* cast to void */
    (void) target;
    //lint +estring(920,pointer)  /* cast to void */
    return E_NOT_OK;
}

Std_ReturnType EcuM_SelectShutdownTarget(EcuM_StateType shutdownTarget,
                uint8 sleepMode) {
    VALIDATE_RV(EcuM_World.initiated, ECUM_SELECTSHUTDOWNTARGET_ID, ECUM_E_UNINIT, E_NOT_OK);
    /* @req EcuMf624 */
    VALIDATE_RV((shutdownTarget == ECUM_STATE_OFF) ||
                (shutdownTarget == ECUM_STATE_RESET) ||
                (shutdownTarget == ECUM_STATE_SLEEP),
                ECUM_SELECTSHUTDOWNTARGET_ID, ECUM_E_STATE_PAR_OUT_OF_RANGE, E_NOT_OK);

    LDEBUG_PRINTF("EcuM_SelectShutdownTarget(): shutdownTarget=%s, sleepMode=%d\n",
            GetMainStateAsString(shutdownTarget),
            sleepMode);

    /* @req EcuMf2585 */
    /* @req EcuMf2232 */
    /* @req EcuM2585 */
    /* @req EcuM624 */
    EcuM_World.shutdown_target = shutdownTarget;
    EcuM_World.sleep_mode = sleepMode;

    return E_OK;
}

Std_ReturnType EcuM_GetShutdownTarget(EcuM_StateType* shutdownTarget,
                uint8* sleepMode) /** @req EcuM2824 */  /** @req EcuMf2824 */
{
    /* @req EcuM2788 */  /* @req EcuMf2788 */
    VALIDATE_RV(EcuM_World.initiated, ECUM_GETSHUTDOWNTARGET_ID, ECUM_E_UNINIT, E_NOT_OK);VALIDATE_RV(shutdownTarget != NULL, ECUM_GETSHUTDOWNTARGET_ID, ECUM_E_NULL_POINTER, E_NOT_OK);VALIDATE_RV(sleepMode != NULL, ECUM_GETSHUTDOWNTARGET_ID, ECUM_E_NULL_POINTER, E_NOT_OK);

    *shutdownTarget = EcuM_World.shutdown_target;
    *sleepMode = EcuM_World.sleep_mode;

    return E_OK;
}
/* !req EcuM2825 */
Std_ReturnType EcuM_GetLastShutdownTarget(EcuM_StateType* shutdownTarget, uint8* sleepMode) {
    /* NOT SUPPORTED */

    (void)shutdownTarget; /*lint !e920 */
    (void)sleepMode; /*lint !e920 */

    return E_OK;
}


/**
 *
 * @param sources
 */
/* @req EcuM2572 */ /* !req EcuM4012 */ /* !req EcuM2712 */
void EcuM_SetWakeupEvent(EcuM_WakeupSourceType sources) {

    EcuM_WakeupSourceType wkSource;

    DEBUG_ECUM_CALLIN_W_ARG("EcuM_SetWakeupEvent","0x%lx",(uint32)sources);

    /* @req EcuM2826 The function exists */  /* @req EcuMf2826 */
    /* @req EcuM2171 */  /* @req EcuMf2171 */
    /* @req EcuM2976 */  /* @req EcuMf2976 */
    /* @req EcuM2565 Validate at once for pre-defined sources */  /* @req EcuMF2565  */
    wkSource = (ECUM_WKSOURCE_POWER | ECUM_WKSOURCE_RESET
                    | ECUM_WKSOURCE_INTERNAL_RESET | ECUM_WKSOURCE_INTERNAL_WDG
                    | ECUM_WKSOURCE_EXTERNAL_WDG);

    /* Sources that should be validated at once */
    wkSource &= sources;
    /* @req EcuM2975 */
    if (wkSource != 0) {
        /* Validate pre-defined source at once */
        EcuM_ValidateWakeupEvent(wkSource);
    }

    /* Don't add pre-defined source to PENDING */
    sources ^= wkSource;

    if (sources != 0 ) {
        /* @req EcuM2867 */  /* @req EcuMf2867 */
#if  ( ECUM_DEV_ERROR_DETECT == STD_ON )
        /* Get user defined sources */
        wkSource = EcuM_World.config->EcuMSleepModeConfig[EcuM_World.sleep_mode].EcuMWakeupSourceMask;

        /* Add always validated sources */
        wkSource |= (ECUM_WKSOURCE_POWER|ECUM_WKSOURCE_RESET | ECUM_WKSOURCE_INTERNAL_RESET |
                ECUM_WKSOURCE_INTERNAL_WDG | ECUM_WKSOURCE_EXTERNAL_WDG);

        if( !((sources | wkSource) == wkSource))
        {
            DET_REPORT_ERROR(ECUM_SETWAKEUPEVENT_ID, ECUM_E_UNKNOWN_WAKEUP_SOURCE );
            /*lint -e{904} Return statement is necessary in case of reporting a DET error */
            return;
        }
#endif

        /* @req EcuM1117 */   /* @req EcuMf1117 */
        EcuM_World.wakeupEvents |= sources;
#if defined(USE_BSWM)
        BswM_EcuM_CurrentWakeup(sources, ECUM_WKSTATUS_PENDING);
#endif
    }
    /* @req EcuM2707 */  /* @req EcuMf2707 */
    /* @req EcuMf2714 */
    /* @req EcuM2565 */  /* @req EcuMf2565 */
    /* @req EcuMf2709 */ /*@req EcuM2709 */ /*@req EcuM4004 */
    EcuM_World.validationTimer = ECUM_VALIDATION_TIMEOUT / ECUM_MAIN_FUNCTION_PERIOD; //lint !e835 PC-lint violation: Allow zero value as left parameter for configuration

}

#if defined(USE_COMM) && (ECUM_AR_VERSION < 40000)

/**
 *
 * @param user
 * @return
 */
Std_ReturnType EcuM_ComM_RequestRUN(NetworkHandleType channel)
{
    VALIDATE_RV(EcuM_World.initiated, ECUM_COMM_REQUESTRUN_ID, ECUM_E_UNINIT, E_NOT_OK);
    VALIDATE_RV(channel < 32, ECUM_COMM_REQUESTRUN_ID, ECUM_E_INVALID_PAR, E_NOT_OK);

    if( !EcuM_World.killAllRequest ) {
        EcuM_World.run_comm_requests |= (uint32)1 << channel;
    }

    return E_OK;
}

/**
 *
 * @param user
 * @return
 */
Std_ReturnType EcuM_ComM_ReleaseRUN(NetworkHandleType channel)
{
    VALIDATE_RV(EcuM_World.initiated, ECUM_COMM_RELEASERUN_ID, ECUM_E_UNINIT, E_NOT_OK);
    VALIDATE_RV(channel < 32, ECUM_COMM_RELEASERUN_ID, ECUM_E_INVALID_PAR, E_NOT_OK);

    EcuM_World.run_comm_requests &= ~((uint32)1 << channel);
    /* @req 3.1.5/EcuM2709 */
    /* @req EcuMf2714 */
    /* @req EcuM2565 */
    EcuM_World.validationTimer = ECUM_VALIDATION_TIMEOUT/ECUM_MAIN_FUNCTION_PERIOD;

    return E_OK;
}


boolean EcuM_ComM_HasRequestedRUN(NetworkHandleType channel)
{
    VALIDATE_RV(EcuM_World.initiated, ECUM_COMM_HASREQUESTEDRUN_ID, ECUM_E_UNINIT, FALSE);
    VALIDATE_RV(channel < 32, ECUM_COMM_HASREQUESTEDRUN_ID, ECUM_E_INVALID_PAR, FALSE);

    return (EcuM_World.run_comm_requests &((uint32)1 << channel)) != 0;
}

#endif


/**
 * Clear wakeup events
 *
 * @return
 */
void EcuM_ClearWakeupEvent(EcuM_WakeupSourceType source) {
    /* @req EcuM2807 */  /* @req EcuMf2807 */
    /* @req EcuMf2683 */ /* @req EcuM2683 */
    EcuM_World.wakeupEvents &= ~(uint32)source;     /* Clear pending events */
    EcuM_World.validEvents &= ~(uint32)source;      /* Clear validated events */
}

/**
 * Get the pending wakeup events.
 *
 * @return
 */
EcuM_WakeupSourceType EcuM_GetPendingWakeupEvents(void) {
    /* @req EcuM2827 API */ /*  @req EcuMf2827 */
    /* @req EcuM2172 Callable from interrupt context */   /* @req EcuMf2172  */


    /* @req EcuM1156 */  /* @req EcuMf1156 */
    return EcuM_World.wakeupEvents;

}

/* @req EcuM2532 */  /* @req EcuMf2532 */
EcuM_WakeupSourceType EcuM_GetValidatedWakeupEvents(void) {
    // is not really an enum.
    /* @req EcuM2496 */  /* @req EcuMf2496 */
    /* @req EcuM2533 */  /* @req EcuMf2533 */ /* @req EcuM3003 */
    return EcuM_World.validEvents;

}

/**
 *
 * @param sources
 */
void EcuM_ValidateWakeupEvent(EcuM_WakeupSourceType sources) {
    /* !req EcuMf2710 */ /* !req EcuM2710 */ /* Timer not stopped */
    /* @req EcuM2625 No validation of any source */  /* @req EcuMf2625 */

    /* @req EcuMf2344 */
    /* @req EcuM2868 */  /* @req EcuMf2868 */
    /* @req EcuM2345 */  /* @req EcuMf2345 */

    (void)CheckWakupSourceValidity(sources, ECUM_VALIDATE_WAKEUP_EVENT_ID);

    /* @req EcuM2496 */   /* @req EcuMf2496 */ /* @req EcuM4078 */
    EcuM_World.validEvents |= sources;

    /* NOTE: Shouldn't the validated event be removed from the pending list? Don't dare to change */

    /* @req EcuM2645 */ /* @req EcuMf2645 */
#if defined(USE_COMM)
    const EcuM_WakeupSourceConfigType *wkupCfgPtr;
    for (uint32 i = 0; i < ECUM_WKSOURCE_USER_CNT; i++) {
        wkupCfgPtr = &EcuM_World.config->EcuMWakeupSourceConfig[i];
        /*lint -e{9027} Lint Exceptions:- Unpermitted operand to operator '&&' (9027)*/ /* @req EcuMf2480 */
        if ( (sources & wkupCfgPtr->EcuMWakeupSourceId) && (wkupCfgPtr->EcuMComMChannel != ECUM_COMM_CHANNEL_ILL) ) {
            ComM_EcuM_WakeUpIndication(wkupCfgPtr->EcuMComMChannel);
        }
    }
#endif
    /* !req EcuM2790 *//* !req EcuMf2790 */
    /* !req EcuM2791 *//* !req EcuMf2791 */
    /* @req EcuM4003 *//* @req EcuM4079 */
    BswM_EcuM_CurrentWakeup(sources, ECUM_WKSTATUS_VALIDATED);
}

#if defined(USE_NVM) && !defined(NVM_ECUM_CBK_USER_OVERRIDE)
void EcuM_CB_NfyNvMJobEnd(uint8 ServiceId, NvM_RequestResultType JobResult) {
    (void)ServiceId;
    (void)JobResult;
}
#endif
