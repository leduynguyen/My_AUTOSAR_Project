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
#include "Std_Types.h"
#include "EcuM.h"
#include "EcuM_Generated_Types.h"
#include "EcuM_Internals.h"
#include "EcuM_Cbk.h"

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

/* ----------------------------[private functions]---------------------------*/
/* @req EcuM2951 */ /* @req  EcuM4023  */
/* !req EcuM3010 */
static void goSleepSequence(void) {
    uint32 cMask;
    uint8 source;
    const EcuM_SleepModeType *sleepModePtr;

    /* Get the current sleep mode */
    sleepModePtr = &EcuM_World.config->EcuMSleepModeConfig[EcuM_World.sleep_mode];

    cMask = sleepModePtr->EcuMWakeupSourceMask;

    /* Loop over the WKSOURCE for this sleep mode */
    for (;(0 != cMask); cMask &= ~(1uL << source)) {
        /*lint -e{9033}*/
        source = (uint8)(ilog2(cMask));
        /*lint -e{9031}*/
        EcuM_EnableWakeupSources(1u << source);
#if defined(USE_BSWM)
        BswM_EcuM_CurrentWakeup((EcuM_WakeupSourceType)source, ECUM_WKSTATUS_NONE);
#endif
    }

    (void)GetResource(RES_SCHEDULER);
}
/* @req EcuM2960 */
static void haltSequence(void) {
    const EcuM_SleepModeType *sleepModePtr;
    /* @req EcuM2961 */ /* !req EcuM2799 */
    EcuM_GenerateRamHash();

    sleepModePtr =
            &EcuM_World.config->EcuMSleepModeConfig[EcuM_World.sleep_mode];
    Mcu_SetMode(sleepModePtr->EcuMSleepModeMcuMode);
    /* @req EcuM4033 */
    if (EcuM_CheckRamHash() == 0) {
#if defined(USE_DEM)
        EcuM_ErrorHook(EcuM_World.config->EcuMDemRamCheckFailedEventId);
#endif
    }
}

#if 0
static void pollingSequence(void) {
    const EcuM_WakeupSourceConfigType *wkupCfgPtr;
    boolean noPendingWakeupEvents = TRUE;

    /* !req EcuM2962 */
    /* !req EcuM3020 */
    while (noPendingWakeupEvents) {
        EcuM_SleepActivity();
        for (uint32 i = 0; i < ECUM_WKSOURCE_USER_CNT; i++) {
            wkupCfgPtr = &EcuM_World.config->EcuMWakeupSourceConfig[i];
            EcuM_CheckWakeup(wkupCfgPtr->EcuMWakeupSourceId);
            if (EcuM_GetPendingWakeupEvents() != 0) {
                noPendingWakeupEvents = FALSE;
            }
        }
    }
    /* BswM_EcuM_CurrentWakeup called from EcuM_SetWakeupEvent */
}
#endif
/* @req EcuM4026 */
static void wakeupRestartSequence(void) {
    EcuM_WakeupSourceType wMask = 0;

    Mcu_SetMode(EcuM_World.config->EcuMNormalMcuMode);
    /*lint -e{838}*/
    wMask = EcuM_GetPendingWakeupEvents();

    EcuM_DisableWakeupSources(wMask);

    EcuM_AL_DriverRestart(EcuM_World.config);

    (void)ReleaseResource(RES_SCHEDULER);
}

#if (ECUM_DEFENSIVE_BEHAVIOR == STD_ON)
static boolean isCallerAllowed(uint16 caller) {
    boolean status;
    status = FALSE;
    for (uint16 i = 0; i < ECUM_GO_DOWN_ALLOWED_USERS_CNT; i++) {
        if (EcuM_World.config->EcuMGoDownAllowedUsersConfig[i] == caller) {
            status = TRUE;
            break;
        }
    }
    return status;
}
#endif

/* ----------------------------[public functions]----------------------------*/
/* @req EcuM2932 */ /* @req EcuM4016  */ /* This function is always called after init*/
void EcuM_StartupTwo(void) {
#if defined(USE_SCHM)
    SchM_Init();
#endif

#if defined(USE_BSWM)
    BswM_Init(EcuM_World.config->BswMConfigPtr);
#endif
}

/* @req EcuM4050 */
Std_ReturnType EcuM_SelectShutdownCause(EcuM_ShutdownCauseType shutdownCause) {
    VALIDATE_RV(EcuM_World.initiated, ECUM_SELECTSHUTDOWNCAUSE_ID, ECUM_E_UNINIT, E_NOT_OK);

    EcuM_World.shutdown_cause = shutdownCause;

    return E_OK ;
}

/* @req EcuM4051 */
Std_ReturnType EcuM_GetShutdownCause(EcuM_ShutdownCauseType *shutdownCause) {
    VALIDATE_RV(EcuM_World.initiated, ECUM_GETSHUTDOWNCAUSE_ID, ECUM_E_UNINIT, E_NOT_OK);

    *shutdownCause = EcuM_World.shutdown_cause;

    return E_OK ;
}

/* @req EcuM4046 */ /* @req EcuM3022 */ /* @req EcuM3021 */ /* !req EcuM4008 */ /* @req EcuM4019 */
Std_ReturnType EcuM_GoDown(uint16 caller) {
    VALIDATE_RV(EcuM_World.initiated, ECUM_GODOWN_ID, ECUM_E_UNINIT, E_NOT_OK);

    EcuM_WakeupSourceType wakeupEvents;
    Std_ReturnType rv;
    rv = E_OK;
    /* !req EcuM4047 */
#if (ECUM_DEFENSIVE_BEHAVIOR == STD_ON)
    if (FALSE == isCallerAllowed(caller)) {
#if defined(USE_DEM)
        //IMPROVEMENT: Report ECUM_E_IMPROPER_CALLER to DEM when we have the 4.1 config
#endif
        rv = E_NOT_OK;
    }
#else
    (void)caller;
#endif
    /*lint -e{774} if also evaluates to false based on ECUM_DEFENSIVE_BEHAVIOR is STD_OFF*/
    if (rv == E_OK ) {
#if defined(USE_BSWM)
        BswM_Deinit();
#endif

#if defined(USE_SCHM)
        SchM_Deinit();
#endif

        wakeupEvents = EcuM_GetPendingWakeupEvents();

        if (wakeupEvents != 0) {
            rv = EcuM_SelectShutdownTarget(ECUM_STATE_RESET, 0);
        }

        /* @req EcuM2952 */
        ShutdownOS(E_OK);
    }
    return rv;
}

/* @req EcuM4048 */
Std_ReturnType EcuM_GoHalt(void) {
    VALIDATE_RV(EcuM_World.initiated, ECUM_GOHALT_ID, ECUM_E_UNINIT, E_NOT_OK);

    goSleepSequence();
    /* @req EcuM4024 */
    haltSequence();
    /* @req EcuM4001 */ /* @req EcuM2963 */
    wakeupRestartSequence();

    return E_OK ;
}

/* !req EcuM4049 */ /* !req EcuM4025 */
#if 0
Std_ReturnType EcuM_GoPoll(void) {
    VALIDATE_RV(EcuM_World.initiated, ECUM_GOPOLL_ID, ECUM_E_UNINIT, E_NOT_OK);

    goSleepSequence();

    pollingSequence();
    /* @req EcuM4001 */
    wakeupRestartSequence();

    return E_OK ;
}
#endif
/* !req EcuM4011 */
void EcuM_MainFunction(void) {
    static uint32 pendingWkupMask = 0;
    static boolean validationOngoing = FALSE;
    static uint32 validationMaxTime = 0;

    if (FALSE == validationOngoing) {
        pendingWkupMask = EcuM_GetPendingWakeupEvents();

        EcuM_StartWakeupSources(pendingWkupMask);
        EcuM_World.validationTimer = 0;

        /* Calculate the validation timing , if any*/

        /* @req EcuM2479 */
        const EcuM_WakeupSourceConfigType *wkupCfgPtr;
        /* @req EcuM2566 */
        for (uint32 i = 0; i < ECUM_WKSOURCE_USER_CNT; i++) {
            wkupCfgPtr = &EcuM_World.config->EcuMWakeupSourceConfig[i];

            /* Can't validate something that is not pending */
            if (0 != (pendingWkupMask & wkupCfgPtr->EcuMWakeupSourceId)) {

                /* No validation timeout == ECUM_VALIDATION_TIMEOUT_ILL */
                if (wkupCfgPtr->EcuMValidationTimeout
                        != ECUM_VALIDATION_TIMEOUT_ILL) {
                    /* Use one validation timeout, take the longest */
                    validationMaxTime =
                        MAX( wkupCfgPtr->EcuMValidationTimeout / ECUM_MAIN_FUNCTION_PERIOD,
                             validationMaxTime);
                    EcuM_World.validationTimer = validationMaxTime;
                }
                else {
                    /* Validate right away */
                    /* @req EcuM2976 */ /* @req EcuM2539*/
                    EcuM_ValidateWakeupEvent(wkupCfgPtr->EcuMWakeupSourceId);
                }
            }
        }

        validationOngoing = TRUE;
    }

    if (EcuM_World.validationTimer != 0) {
        /*
         * Call EcuM_CheckValidation() while all events have not been validated and
         * timeout have not expired. The call to EcuM_CheckValidation(..) triggers a call
         * to EcuM_ValidateWakeupEvent(..) from the driver when validated.
         */

        /* Check validation for the events that do not match, ie not yet validated */
        EcuM_CheckValidation(EcuM_GetValidatedWakeupEvents() ^ pendingWkupMask);

        if (0 == (EcuM_GetValidatedWakeupEvents() ^ pendingWkupMask)) {
            /* All events have been validated */
            validationOngoing = FALSE;
        }
    }
    else {

        uint32 notValidatedMask = EcuM_GetValidatedWakeupEvents()
                ^ pendingWkupMask;
        /* Stop wakeupSources that are not validated */
        if (0 != notValidatedMask) {
            EcuM_StopWakeupSources(notValidatedMask); /* @req EcuM4081 */
            /* @req EcuM4082 */
#if defined(USE_BSWM)
            BswM_EcuM_CurrentWakeup((EcuM_WakeupSourceType)notValidatedMask, ECUM_WKSTATUS_EXPIRED);
#endif
        }
        validationOngoing = FALSE;
    }

    /* @req 3.1.5/EcuM2710 */
    if (0 != EcuM_World.validationTimer) {
        EcuM_World.validationTimer--;
    }
}
