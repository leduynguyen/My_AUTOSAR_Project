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


/** @tagSettings DEFAULT_ARCHITECTURE=JACINTO5|JACINTO6 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#include "Std_Types.h"
#include "Mcu.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#include "arc_assert.h"
#include "Cpu.h"
#include <string.h>
#include "Ramlog.h"
#include "Mcu_Arc.h"

/* General Tagging */
/* @req SWS_Mcu_00017 */ /* Return E_NOT_OK in case of errors*/
/* @req SWS_Mcu_00152 */ /* Import Dem and Std Types */
/* @req SWS_Mcu_00163 */ /* DET report error service is used */
/* @req SWS_Mcu_00226 */ /* Production errors shall not be used as return values of Api */
/* @req SWS_Mcu_00244 */ /* Port driver initializes I/O registers */
/* @req SWS_Mcu_00247 */ /* startup code initializes other registers */
/* @req SWS_Mcu_00125 */ /* DET error MCU_E_UNINIT (except Mcu_GetVersionInfo) if any Api is invoked before Mcu_Init */
/* #define USE_LDEBUG_PRINTF 1 */
#include "debug.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(_x)  (sizeof(_x)/sizeof((_x)[0]))
#endif

/* Development error macros. */
/* @req SWS_Mcu_00163 */
#if ( MCU_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void) Det_ReportError(MCU_MODULE_ID,0,_api,_err); \
          return; \
        }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
        if( !(_exp) ) { \
          (void) Det_ReportError(MCU_MODULE_ID,0,_api,_err); \
          return (_rv); \
        }
#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_W_RV(_exp,_api,_err,_rv )
#endif


/* Frequency for DCAN clock. Set hard by startup script */
#define DCAN_CLOCK_FREQ             20000000UL
/* Frequency for UART clock  */
#define UART_CLOCK_FREQ             48000000UL
/* Frequency for SPI clock */
#define SPI_CLOCK_FREQ				48000000UL
/* Frequency for I2C clock  */
#if defined (CFG_JAC5) || defined (CFG_JAC5E)
#define I2C_CLOCK_FREQ              20000000UL
#elif defined (CFG_JAC6)
#define I2C_CLOCK_FREQ              96000000UL
#endif
/* Frequency for General Purpose Timer module. Set hard by startup script */
#define GENERAL_PURPOSE_TIMER_FREQ	20000000UL
#define TIMER_PWM_CLOCK_FREQ		GENERAL_PURPOSE_TIMER_FREQ
#define GPT_CLOCK_FREQ				GENERAL_PURPOSE_TIMER_FREQ
#if defined(CFG_JAC6)
/* Frequency for ePWM clock - only exists on Jacinto 6. */
#define EPWM_CLOCK_FREQ				133000000uL
#endif /* defined(CFG_JAC6) */

/**
 * @brief Mcu_GlobalType Type that holds all global data for Mcu.
 */
typedef struct {
    boolean initRun; /* Set to TRUE after Mcu_Init has been called. */
  const Mcu_ConfigType *config;
  Mcu_ClockType clockSetting;
} Mcu_GlobalType;

Mcu_GlobalType Mcu_Global = {
        .initRun = FALSE,
        .config = &McuConfigData[0],
        .clockSetting = 0
};


//-------------------------------------------------------------------

/* @req SWS_Mcu_00246  */
void Mcu_Init(const Mcu_ConfigType *configPtr) {

    /* @req SWS_Mcu_00018  */
    VALIDATE( ( NULL != configPtr ), MCU_INIT_SERVICE_ID, MCU_E_PARAM_CONFIG );

    Mcu_Arc_InitPre(configPtr);

#if !defined(USE_SIMULATOR)
    /* Identify the core, just to check that we have support for it.
     * If not, just hang. */
    if (Mcu_Arc_IdentifyCore(SCB->CPUID) == NULL) {

        while (TRUE);
    }
#endif

    Mcu_Global.config = configPtr;

    Mcu_Arc_InitPost(configPtr);

    Mcu_Global.initRun = TRUE;
}

//-------------------------------------------------------------------

/* !req SWS_Mcu_00239 */
Std_ReturnType Mcu_InitRamSection(const Mcu_RamSectionType RamSection) {

    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_INITRAMSECTION_SERVICE_ID, MCU_E_UNINIT, E_NOT_OK );
    /* @req SWS_Mcu_00021 */
    VALIDATE_W_RV( ( RamSection <= Mcu_Global.config->McuRamSectors ), MCU_INITRAMSECTION_SERVICE_ID, MCU_E_PARAM_RAMSECTION, E_NOT_OK );

    /* NOT SUPPORTED, reason: no support for external RAM */
    /* !req SWS_Mcu_00011 */

    return E_NOT_OK;
}

//-------------------------------------------------------------------
#if ( MCU_INIT_CLOCK == STD_ON )
Std_ReturnType Mcu_InitClock(const Mcu_ClockType ClockSetting) {

    const Mcu_ClockSettingConfigType *clockSettingsPtr;
    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_INITCLOCK_SERVICE_ID, MCU_E_UNINIT, E_NOT_OK );
    /* @req SWS_Mcu_00019 */
    VALIDATE_W_RV( ( ClockSetting < Mcu_Global.config->McuClockSettings ), MCU_INITCLOCK_SERVICE_ID, MCU_E_PARAM_CLOCK, E_NOT_OK );

    Mcu_Global.clockSetting = ClockSetting;
    clockSettingsPtr = &Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting];

    Mcu_Arc_InitClockPre(clockSettingsPtr);

    Mcu_Arc_InitClockPost(clockSettingsPtr);

    return E_OK;
}
#endif
//-------------------------------------------------------------------

/* !req SWS_Mcu_00056 */
/* !req SWS_Mcu_00141 */
/* !req SWS_Mcu_00140 */
#if ( MCU_NO_PLL == STD_OFF )
Std_ReturnType Mcu_DistributePllClock(void) {

    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID, MCU_E_UNINIT, E_NOT_OK);
    VALIDATE_W_RV( ( Mcu_GetPllStatus() == MCU_PLL_LOCKED ), MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID, MCU_E_PLL_NOT_LOCKED, E_NOT_OK );

    /* NOT IMPLEMENTED due to pointless function on this hardware */

    return E_OK;
}
#endif

//-------------------------------------------------------------------

/* !req SWS_Mcu_00008 */
/* !req SWS_Mcu_00206 */
Mcu_PllStatusType Mcu_GetPllStatus(void) {

    /* @req SWS_Mcu_00132 */
    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_GETPLLSTATUS_SERVICE_ID, MCU_E_UNINIT, MCU_PLL_STATUS_UNDEFINED );

    /* PLL setup not done by Cortex core, PLL is always considered in sync. */
    return MCU_PLL_LOCKED;
}

//-------------------------------------------------------------------

/* !req SWS_Mcu_00005 */
/* !req SWS_Mcu_00052 */
Mcu_ResetType Mcu_GetResetReason(void) {

    /* @req SWS_Mcu_00133 */
    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_GETRESETREASON_SERVICE_ID, MCU_E_UNINIT, MCU_RESET_UNDEFINED );

    /* No support for Reset reason clear. */

    /* Does not matter if Mcu_Init has been called or not, always return MCU_RESET_UNDEFINED
     * since the API is not supported. */

    return MCU_RESET_UNDEFINED;
}

//-------------------------------------------------------------------
/* !req SWS_Mcu_00006 */
Mcu_RawResetType Mcu_GetResetRawValue(void) {

    /* @req SWS_Mcu_00135 */
    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_GETRESETREASON_SERVICE_ID, MCU_E_UNINIT, MCU_GETRESETRAWVALUE_UNINIT_RV );

    /* Does not matter if Mcu_Init has been called or not, always return MCU_GETRESETRAWVALUE_UNINIT_RV
     * since the API is not supported. */

        return MCU_GETRESETRAWVALUE_UNINIT_RV;
}

//-------------------------------------------------------------------

#if ( MCU_PERFORM_RESET_API == STD_ON )
/**
 * Shell perform a microcontroller reset by using the hardware feature
 * of the micro controller.
 */
/* @req SWS_Mcu_00055 */
/* !req SWS_Mcu_00144 */
void Mcu_PerformReset(void) {

    VALIDATE( ( TRUE == Mcu_Global.initRun ), MCU_PERFORMRESET_SERVICE_ID, MCU_E_UNINIT );

    /* @req SWS_Mcu_00143 */
    Cpu_SystemReset();
}
#endif /* ( MCU_PERFORM_RESET_API == STD_ON ) */

//-------------------------------------------------------------------

void Mcu_SetMode(const Mcu_ModeType McuMode) {

    /* !req SWS_Mcu_00020 */
#if ( MCU_DEV_ERROR_DETECT == STD_ON )
    if (!Mcu_Global.initRun) {
        (void) Det_ReportError(MCU_MODULE_ID, 0, MCU_SETMODE_SERVICE_ID, MCU_E_UNINIT);

        return;
    }

    /* Mcu_SetMode is not supported so always report if Det is enabled, no
     * matter if (mcuMode <= Mcu_Global.config->McuNumberOfMcuModes) or not. */
    (void) Det_ReportError(MCU_MODULE_ID, 0, MCU_SETMODE_SERVICE_ID, MCU_E_PARAM_MODE);
#endif /* ( MCU_DEV_ERROR_DETECT == STD_ON ) */

    (void) McuMode;
}

//-------------------------------------------------------------------

/**
 * Get the system clock in Hz. It calculates the clock from the
 * different register settings in HW.
 */
uint32 Mcu_Arc_GetSystemClock(void) {

    return Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting].McuClockReferencePointFrequency;
}

/**
 * Get the peripheral clock in Hz for a specific device
 */
uint32 Mcu_Arc_GetPeripheralClock(Mcu_Arc_PeriperalClock_t type) {

    uint32 res = 0;

    switch(type)
    {
        case PERIPHERAL_CLOCK_DCAN:
            res = DCAN_CLOCK_FREQ;
            break;

        case PERIPHERAL_CLOCK_UART:
            res = UART_CLOCK_FREQ;
            break;

        case PERIPHERAL_CLOCK_I2C:
            res = I2C_CLOCK_FREQ;
            break;

        case PERIPHERAL_CLOCK_SPI:
            res = SPI_CLOCK_FREQ;
            break;

        case PERIPHERAL_CLOCK_GMAC_SW:
        /* IMPROVEMENT - Add GMAC freq */
            break;

        case PERIPHERAL_CLOCK_TIMER_PWM:
            res = TIMER_PWM_CLOCK_FREQ;
            break;
#if defined(CFG_JAC6)
        case PERIPHERAL_CLOCK_EPWM:
            res = EPWM_CLOCK_FREQ;
            break;
#endif
        case PERIPHERAL_CLOCK_GPT:
            res = GPT_CLOCK_FREQ;
            break;

        case PERIPHERAL_CLOCK_SCTM:
            res = Mcu_Arc_GetSystemClock() * 2;
            break;

        default:
            res = Mcu_Arc_GetSystemClock();
            break;
    }

    return res;
}

void Mcu_GetVersionInfo(Std_VersionInfoType* versioninfo) {

    /* @req SWS_Mcu_00204 */
    VALIDATE( ( NULL != versioninfo ), MCU_GETVERSIONINFO_SERVICE_ID, MCU_E_PARAM_POINTER);

    versioninfo->vendorID = MCU_VENDOR_ID;
    versioninfo->moduleID = MCU_MODULE_ID;
    versioninfo->sw_major_version = MCU_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = MCU_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = MCU_SW_PATCH_VERSION;
}

void Mcu_Arc_DeInit(void) {

    Mcu_Global.initRun = FALSE;
}
