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


/** @tagSettings DEFAULT_ARCHITECTURE=TMS570 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */


#include "Wdg.h"
#include "WdgIf.h"
#include "Std_Types.h"
#include "isr.h"
#include "core_cr4.h"
#include "irq_types.h"
#include "irq_tms570.h"
#include "Wdg_Cfg.h"

#include "timer_rti.h"

#if defined(USE_DET)
#include "Det.h"
#endif

#if defined(WDG_DEV_ERROR_DETECT)
typedef enum {
    WDG_IDLE,
    WDG_UNINIT,
    WDG_BUSY
} Wdg_ModuleStateType;
#endif

#if (WDG_DEV_ERROR_DETECT)
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(WDG_MODULE_ID,0,_api,_err); \
          return; \
        }
#define VALIDATE_RV(_exp,_api,_err,_ret ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(WDG_MODULE_ID,0,_api,_err); \
          return _ret; \
        }
#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_RV(_exp,_api,_err,_ret )
#endif

#if defined(WDG_DEV_ERROR_DETECT)
Wdg_ModuleStateType moduleState = WDG_UNINIT;
#endif

const Wdg_ConfigType* WdgConfigPtr;

static uint32 Wdg_KickTimerTicksPerPeriod;
static volatile uint32 Wdg_TriggerCounter = 0;

void* RTIDWDCTRL = (void*)0xFFFFFC90;
void* RTIDWDPRLD = (void*)0xFFFFFC94;
void* RTIDWDKEY  = (void*)0xFFFFFC9C;
void* RTIWWDSIZE = (void*)0xFFFFFCA8;

#define WDG_ENABLE_MAGIC					0xA98559DA
#define WDG_KEY_ONE							0xE51Au
#define WDG_KEY_TWO							0xA35Cu
#define WDG_INTERRUPT_PRIORITY				2u
#define WDG_WINDOW_100_SETTING				0x5
#define WDG_RTICLK_CMP_INDEX				3u
#define WDG_COMP_CTRL_COMPSEL_JUMP			4u
#define WDG_APP								0u
#define WDG_ARC_US2TICKS(_us, _timer_freq)	(((_us) * (_timer_freq/1000))/1000uL)

static void Internal_SetMode(WdgIf_ModeType Mode);

/**
 * Calculate the timeout for the watchdog hardware,
 * the DWDPRLD register. Ready to be inserted as is.
 * @param period The timeout in Hz.
 * @return Value to be written to DWDPRLD.
 */
static uint32 calcWatchdogTimeout(uint16 period);

ISR(Wdg_Isr) {

    /* Clear Interrupt */
    rtiREG1->INTFLAG |= (1 << WDG_RTICLK_CMP_INDEX);

    if (Wdg_TriggerCounter > 0) {

        --Wdg_TriggerCounter;

        /* The watchdog is serviced by two separate write operations
         * with constant magic byte sequences. */
        *(uint32*)RTIDWDKEY = WDG_KEY_ONE;
        *(uint32*)RTIDWDKEY = WDG_KEY_TWO;
    }
}

void Wdg_Init(const Wdg_ConfigType* ConfigPtr) {

    WdgConfigPtr = ConfigPtr;

    /* @req SWS_Wdg_00089 */
    VALIDATE((ConfigPtr != NULL), WDG_INIT_SERVICE_ID, WDG_E_PARAM_POINTER);

    if (ConfigPtr->Wdg_ModeConfig->Wdg_DefaultMode == WDGIF_OFF_MODE) {
        if (WDG_DISABLE_ALLOWED == STD_OFF) {
            /* Report DEM error */
            return;
        }
    }

    /* @req SWS_Wdg_00090 */
    uint32 wdgTimeout = calcWatchdogTimeout(ConfigPtr->Wdg_ModeConfig->WdgSettingsFast->period);
    VALIDATE((wdgTimeout <= 4095), WDG_INIT_SERVICE_ID, WDG_E_PARAM_CONFIG);

    Timer_Rt1Init();

    uint32 rti1Clock = Timer_Rt1GetClock();

    rtiREG1->COMPCTRL |= (1u << (WDG_COMP_CTRL_COMPSEL_JUMP * WDG_RTICLK_CMP_INDEX));

    ISR_INSTALL_ISR2("WdgIsr", Wdg_Isr, RTI_COMPARE_3, WDG_INTERRUPT_PRIORITY, WDG_APP);

    Wdg_KickTimerTicksPerPeriod = WDG_ARC_US2TICKS(1000, rti1Clock);

    rtiREG1->INTFLAG |= (1uL << WDG_RTICLK_CMP_INDEX);

    /** - Setup compare 1 value. This value is compared with selected free running counter. */
    rtiREG1->CMP[WDG_RTICLK_CMP_INDEX].COMPx = Wdg_KickTimerTicksPerPeriod;

    /** - Setup update compare 1 value. This value is added to the compare 1 value on each compare match. */
    rtiREG1->CMP[WDG_RTICLK_CMP_INDEX].UDCPx = Wdg_KickTimerTicksPerPeriod;

    Internal_SetMode(ConfigPtr->Wdg_ModeConfig->Wdg_DefaultMode);

    /* Enable compare interrupt. */
    rtiREG1->SETINT |= (1u << WDG_RTICLK_CMP_INDEX);

    /* @req SWS_Wdg_00019 */
#if defined(WDG_DEV_ERROR_DETECT)
    moduleState = WDG_IDLE;
#endif
}

Std_ReturnType Wdg_SetMode(WdgIf_ModeType Mode) {

    VALIDATE_RV((Mode == WDGIF_FAST_MODE || Mode == WDGIF_OFF_MODE), WDG_SET_MODE_SERVICE_ID, WDG_E_PARAM_MODE, E_NOT_OK);
    VALIDATE_RV(moduleState == WDG_IDLE, WDG_SET_MODE_SERVICE_ID, WDG_E_DRIVER_STATE, E_NOT_OK);

    /* Disabling the watchdog is not allowed. */
    if (Mode == WDGIF_OFF_MODE) {
        /* Report DEM error. */
        return E_NOT_OK;
    }

    Internal_SetMode(Mode);

    return E_OK;
}

static void Internal_SetMode(WdgIf_ModeType Mode) {

#if defined(WDG_DEV_ERROR_DETECT)
    moduleState = WDG_BUSY;
#endif

    /* The watchdog has only one mode which is fast. It also has an OFF mode
     * but once set to FAST it cannot go back
     */
    if (Mode != WDGIF_FAST_MODE) {
        return;
    }

    uint32 dwdprld = calcWatchdogTimeout(WdgConfigPtr->Wdg_ModeConfig->WdgSettingsFast->period);
    *(uint32*)RTIDWDPRLD = dwdprld;

    /* Set the window size. Acts as timeout watchdog if window size == 100%. */
    *(uint32*)RTIWWDSIZE = WDG_WINDOW_100_SETTING;

#if defined(WDG_DEV_ERROR_DETECT)
    moduleState = WDG_IDLE;
#endif
}

void Wdg_SetTriggerCondition(uint16 timeout) {

    VALIDATE((moduleState == WDG_IDLE), WDG_SET_TRIGGERING_CONDITION_SERVICE_ID, WDG_E_DRIVER_STATE);

#if (WDG_DEV_ERROR_DETECT == STD_ON)
    moduleState = WDG_BUSY;
#endif

    /* @req SWS_Wdg_00136
     * @req SWS_Wdg_00138
     * @req SWS_Wdg_00140
     * !req SWS_Wdg_00146
     */

    rtiREG1->CLEARINT |= (1uL << WDG_RTICLK_CMP_INDEX);

    Wdg_TriggerCounter = timeout;

    rtiREG1->SETINT = (1uL << WDG_RTICLK_CMP_INDEX);

    /* Set the mode before starting the Watchdog device
     * The hardware requires that this happens before the
     * actual Watchdog module is started. */

    /* Start the actual watchdog hardware */
    *(uint32*)RTIDWDCTRL = WDG_ENABLE_MAGIC;

#if (WDG_DEV_ERROR_DETECT == STD_ON)
    moduleState = WDG_IDLE;
#endif
}

#if (STD_ON == WDG_VERSION_INFO_API)
/* @req SWS_Wdg_00109 */
void Wdg_GetVersionInfo( Std_VersionInfoType* versioninfo ) {
    /* @req SWS_Wdg_00174 */
    VALIDATE((NULL != versioninfo), WDG_GET_VERSION_INFO_SERVICE_ID,WDG_E_PARAM_POINTER);
    versioninfo->vendorID = WDG_VENDOR_ID;
    versioninfo->moduleID = WDG_MODULE_ID;
    versioninfo->sw_major_version = WDG_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = WDG_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = WDG_SW_PATCH_VERSION;
}
#endif /* (STD_ON == WDG_VERSION_INFO_API) */

static uint32 calcWatchdogTimeout(uint16 period) {

    /*
     * According to TMS570LS1227 manual, section 13.2.5.1 and
     * TMS570LC4357 manual, section 17.2.5.1,
     * the watchdog counter expiration time T is:
     *
     * 						13
     * T = (DWDPRLD + 1) * 2   / RTICLK
     *
     * DWDPRLD is the value in range 0..4095 that is stored in a control register
     *
     * From that we calculate:
     *
     * DWDPRLD = (T * RTICLK / 2^13) - 1
     */
    double seconds = (1.0 / period);

    uint32 rticlk = Mcu_Arc_GetPeripheralClock(PERIPHERAL_CLOCK_RTICLK);

    sint32 dwdprld = (seconds * rticlk / 8192) - 1;

    return (uint32) dwdprld;
}

#ifdef HOST_TEST
uint32 Wdg_Arc_GetTriggerCounter(void) {
    return Wdg_TriggerCounter;
}
#endif /* HOST_TEST */
