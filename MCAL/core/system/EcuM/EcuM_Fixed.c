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
#include "Dem.h"                /* @req EcuMf2875 */
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

#if  ( ECUM_DEV_ERROR_DETECT == STD_ON )
extern boolean CheckWakupSourceValidity(EcuM_WakeupSourceType sources, uint8 FunctionId);
#else
#define CheckWakupSourceValidity(sources, FunctionId) (FALSE)
#endif

/*
 * The order defined here is found in EcuM2411
 */
void EcuM_StartupTwo(void)
{
    //IMPROVEMENT:  Validate that we are in state STARTUP_ONE.
#if defined(USE_NVM)
    TickType tickTimerStart, tickTimerElapsed;
    static NvM_RequestResultType readAllResult;
    Std_ReturnType status;
#endif

    SetCurrentState(ECUM_STATE_STARTUP_TWO);

    // Initialize the BSW scheduler
#if defined(USE_SCHM)
    SchM_Init();
#endif

#if defined(USE_BSWM)
    /* @req EcuMf0016 */
    BswM_Init(EcuM_World.config->BswMConfigPtr);
#endif

    // Initialize drivers that don't need NVRAM data
    EcuM_AL_DriverInitTwo(EcuM_World.config);

#if defined(USE_NVM)
    // Start timer to wait for NVM job to complete
    tickTimerStart = GetOsTick();
#endif

    // Prepare the system to startup RTE
    // IMPROVEMENT: EcuM_OnRTEStartup();
#if defined(USE_RTE)
	(void)Rte_Start();
#endif

#if defined(USE_NVM)
    /* Wait for the NVM job (NvM_ReadAll) to terminate. This assumes that:
     * - A task runs the memory MainFunctions, e.g. Ea_MainFunction(), Eep_MainFunction()
     *   are run in a higher priority task that the task that executes this code.
     */
#if defined(CFG_ARC_ECUM_NVM_READ_INIT) && defined(USE_FEE)
    EcuM_Arc_InitFeeReadAdminBlock(tickTimerStart, EcuM_World.config->EcuMNvramReadAllTimeout);
#endif

    do {
        /* Read the multiblock status */
        status = NvM_GetErrorStatus(0, &readAllResult);

        tickTimerElapsed = OS_TICKS2MS_OS_TICK(GetOsTick() - tickTimerStart);

#if defined(CFG_ARC_ECUM_NVM_READ_INIT)
        EcuM_Arc_InitMemReadAllMains();
#endif

        /* The timeout EcuMNvramReadAllTimeout is in ms */
    } while( (readAllResult == NVM_REQ_PENDING) && (tickTimerElapsed < EcuM_World.config->EcuMNvramReadAllTimeout) );
            if(status!=E_OK) {
                //IMPROVEMENT: Report error.
            }

#endif

    // Initialize drivers that need NVRAM data
    EcuM_AL_DriverInitThree(EcuM_World.config);

    // IMPROVEMENT: Indicate mode change to RTE

    /* IMPROVEMENT: If one of the wake up sources listed in 7.8.7 Wake up Sources and Reset Reason is set, then
     * exection shall continue with RUN state. In all other cases, execution shall continue with
     * WAKEUP VALIDATION state.
     * !req EcuMf2632
     * */

    EcuM_enter_run_mode();
}

/* @req EcuMf2423 */
Std_ReturnType EcuM_GetState(EcuM_StateType* state) {
    VALIDATE_RV(EcuM_World.initiated, ECUM_GETSTATE_ID, ECUM_E_UNINIT, E_NOT_OK);VALIDATE_RV(state != NULL, ECUM_GETSTATE_ID, ECUM_E_NULL_POINTER, E_NOT_OK);

    *state = EcuM_World.current_state;

    return E_OK;
}

Std_ReturnType EcuM_RequestRUN(EcuM_UserType user) {
    VALIDATE_RV(EcuM_World.initiated, ECUM_REQUESTRUN_ID, ECUM_E_UNINIT, E_NOT_OK);
    VALIDATE_RV(user < ECUM_USER_ENDMARK, ECUM_REQUESTRUN_ID, ECUM_E_INVALID_PAR, E_NOT_OK); //lint !e638 !e641 Ok. Data is validated

    //	LDEBUG_PRINTF("EcuM_RequestRUN(): User %d\n",user);
    if( FALSE == EcuM_World.killAllRequest ) {
        EcuM_World.run_requests |= (uint32) 1 << user;
    }

    /* @req EcuMf2144 */
    return E_OK;
}

Std_ReturnType EcuM_ReleaseRUN(EcuM_UserType user) {
    VALIDATE_RV(EcuM_World.initiated, ECUM_RELEASERUN_ID, ECUM_E_UNINIT, E_NOT_OK);
    VALIDATE_RV(user < ECUM_USER_ENDMARK, ECUM_RELEASERUN_ID, ECUM_E_INVALID_PAR, E_NOT_OK); //lint !e638 !e641 Ok. Data is validated

    /* @req EcuMf2144 */
#if defined(DEBUG_RELEASE_RUN)
    LDEBUG_PRINTF("EcuM_ReleaseRUN(): User %d\n",user);
#endif
    EcuM_World.run_requests &= ~((uint32) 1 << user);

    return E_OK;
}

/**
 * Kill all RUN requests and perform shutdown without waiting for application
 * to finish
 *
 * Note that for 4.x this should NOT kill POST_RUN requests
 *
 */
void EcuM_KillAllRUNRequests(void) {
    /* @req EcuMf1872 */
    /* @req EcuMf2600 */
    /* @req EcuMf2668 */

    /* @req ECUMf2821 */

    EcuM_World.killAllRequest = true;

    EcuM_World.run_requests = 0;
#if defined(USE_COMM)
    EcuM_World.run_comm_requests = 0;
#endif


#if defined(USE_DEM)
    Dem_ReportErrorStatus(EcuM_World.config->EcuMDemAllRunRequestsKilledEventId , DEM_EVENT_STATUS_FAILED );
#endif

}

Std_ReturnType EcuM_RequestPOST_RUN(EcuM_UserType user) {
    VALIDATE_RV(EcuM_World.initiated, ECUM_REQUESTPOSTRUN_ID, ECUM_E_UNINIT, E_NOT_OK);
    VALIDATE_RV(user < ECUM_USER_ENDMARK, ECUM_REQUESTPOSTRUN_ID, ECUM_E_INVALID_PAR, E_NOT_OK); //lint !e638 !e641 Ok. Data is validated

    if( FALSE == EcuM_World.killAllRequest ) {
        EcuM_World.postrun_requests |= (uint32) 1 << user;
    }

    return E_OK;
}

Std_ReturnType EcuM_ReleasePOST_RUN(EcuM_UserType user) {
    VALIDATE_RV(EcuM_World.initiated, ECUM_RELEASEPOSTRUN_ID, ECUM_E_UNINIT, E_NOT_OK);
    VALIDATE_RV(user < ECUM_USER_ENDMARK, ECUM_RELEASEPOSTRUN_ID, ECUM_E_INVALID_PAR, E_NOT_OK); //lint !e638 !e641 Ok. Data is validated

    EcuM_World.postrun_requests &= ~((uint32) 1 << user);

    return E_OK;
}

EcuM_WakeupStatusType EcuM_GetStatusOfWakeupSource( EcuM_WakeupSourceType sources ) {
    /* @req EcuMf2754 */

    EcuM_WakeupStatusType status;
    status = ECUM_WKSTATUS_NONE;
    /* @req EcuMf2864 */
    (void)CheckWakupSourceValidity(sources, ECUM_GETSTATUSOFWAKEUPSOURCE_ID);

    if ((EcuM_GetValidatedWakeupEvents() & sources) != 0) {
        status = ECUM_WKSTATUS_VALIDATED;
    }
#if 0
    /*IMPROVEMENT: No support for expired events yet*/
    if (EcuM_GetExpiredWakeupEvents() & sources) != 0) {
        return ECUM_WKSTATUS_EXPIRED;
    }
#endif
    else if ((EcuM_GetPendingWakeupEvents() & sources) != 0) {
        status = ECUM_WKSTATUS_PENDING;

    } else {
        status = ECUM_WKSTATUS_NONE;
    }
    return status;

}
