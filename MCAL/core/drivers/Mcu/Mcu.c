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
/** @tagSettings DEFAULT_ARCHITECTURE=RH850F1H|TMS570|PPC|MPC5607B|MPC5645S|MPC5748G */

/* ----------------------------[includes]------------------------------------*/

#include <string.h>
#include "Std_Types.h"
#include "SchM_Mcu.h"
#include "Mcu.h"
#include "Mcu_Internal.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#include "Cpu.h"
#include "io.h"
#if defined(USE_KERNEL)
#include "irq.h"
#endif

/* Global requirements */
/* !req SWS_Mcu_00130 */

/* @req SWS_Mcu_00017 API parameter checking  */
/* @req SWS_Mcu_00226 Production Errors shall not be used as the return value of the called function */

//#define USE_LDEBUG_PRINTF 1
#include "debug.h"

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/

#define MCU_ASSERT(_x)		if( !(_x) ) { while(1) {}; }

/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

Mcu_GlobalType Mcu_Global =
{
    .initRun = FALSE,
    .config = &McuConfigData[0],
    .clockSetting = 0,
    .rawResetvalue = 0,
    .resetReason = MCU_RESET_UNDEFINED
};

/* ----------------------------[private functions]---------------------------*/



Mcu_ResetType Mcu_Arc_GetResetReason(void)
{
    return Mcu_Global.resetReason;
}

/* ----------------------------[public functions]----------------------------*/
/* @req SWS_Mcu_00026  */
/* @req SWS_Mcu_00116  */
/* @req SWS_Mcu_00244  */
/* @req SWS_Mcu_00245  */
/* @req SWS_Mcu_00246  */
/* @req SWS_Mcu_00247  */
void Mcu_Init(const Mcu_ConfigType *ConfigPtr)
{
    /* @req SWS_Mcu_00018 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE( ( NULL != ConfigPtr ), MCU_INIT_SERVICE_ID, MCU_E_PARAM_CONFIG );

    /* Get reset cause and clear */
    Mcu_Hw_Init(ConfigPtr);

    Mcu_Global.config = ConfigPtr;
    Mcu_Global.initRun = TRUE;
}

void Mcu_Arc_DeInit( void )
{
    Mcu_Global.initRun = FALSE;
}


//-------------------------------------------------------------------

Std_ReturnType Mcu_InitRamSection(Mcu_RamSectionType RamSection)
{
    /* @req SWS_Mcu_00021 */
    /* @req SWS_Mcu_00125 */
    /* @req SWS_Mcu_00154 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_INITRAMSECTION_SERVICE_ID, MCU_E_UNINIT, E_NOT_OK );
    VALIDATE_W_RV( ( RamSection < Mcu_Global.config->McuRamSectors ), MCU_INITRAMSECTION_SERVICE_ID, MCU_E_PARAM_RAMSECTION, E_NOT_OK );
    /*lint -restore*/

    /*lint -e{923} Note: Cast from unsigned long to pointer. OK. */
    /*lint -e{970} Note: Use of modifier or type 'int' outside of a typedef.
     * OK, Mcu.chk for the specific MCU needs to check that McuRamDefaultValue fits within an int. */
    memset(	(void *)Mcu_Global.config->McuRamSectorSettingConfig[RamSection].McuRamSectionBaseAddress,
            (int) Mcu_Global.config->McuRamSectorSettingConfig[RamSection].McuRamDefaultValue,
            (size_t)Mcu_Global.config->McuRamSectorSettingConfig[RamSection].McuRamSectionSize);

    return E_OK;
}


#if ( MCU_GET_RAM_STATE == STD_ON )
Mcu_RamStateType Mcu_GetRamState( void )
{
    /* NOT SUPPORTED */
    return MCU_RAMSTATE_INVALID;
}
#endif 


//-------------------------------------------------------------------

/* @req SWS_Mcu_00137  */
/* @req SWS_Mcu_00210  */
/* !req SWS_Mcu_00138 Waiting for PLL to look unless CFG_SIMULATOR is defined*/
#if ( MCU_INIT_CLOCK == STD_ON )
Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting)
{
    const Mcu_ClockSettingConfigType *clockSettingsPtr;

    /* @req SWS_Mcu_00125  */
    /* @req SWS_Mcu_00019  */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_INITCLOCK_SERVICE_ID, MCU_E_UNINIT, E_NOT_OK );
    VALIDATE_W_RV( ( ClockSetting < Mcu_Global.config->McuClockSettings ), MCU_INITCLOCK_SERVICE_ID, MCU_E_PARAM_CLOCK, E_NOT_OK );
    /*lint -restore*/

    Mcu_Global.clockSetting = ClockSetting;
    clockSettingsPtr = &Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting];

    return Mcu_Hw_InitClock(clockSettingsPtr);
}

#endif /* #if ( MCU_INIT_CLOCK == STD_ON )*/

//-------------------------------------------------------------------

/* @req SWS_Mcu_00205 */
#if ( MCU_NO_PLL == STD_OFF )
Std_ReturnType Mcu_DistributePllClock(void)
{
    /* @req SWS_Mcu_00125 */
    /* !req SWS_Mcu_00122 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID, MCU_E_UNINIT, E_NOT_OK );
    VALIDATE_W_RV( ( Mcu_Hw_GetPllStatus() == MCU_PLL_LOCKED), MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID, MCU_E_PLL_NOT_LOCKED, E_NOT_OK);
    /*lint -restore*/

    return Mcu_Hw_DistributePllClock();
}

#endif /* #if ( MCU_NO_PLL == STD_ON ) */

//-------------------------------------------------------------------

Mcu_PllStatusType Mcu_GetPllStatus(void)
{

    /* @req SWS_Mcu_00206. The function Mcu_GetPllStatus shall also return MCU_PLL_STATUS_UNDEFINED
     *                     if the pre-compile parameter McuNoPll is set to TRUE */
#if ( MCU_NO_PLL == STD_ON )
    return MCU_PLL_STATUS_UNDEFINED;
#else
    /* @req SWS_Mcu_00125 */
    /* @req SWS_Mcu_00132 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_GETPLLSTATUS_SERVICE_ID, MCU_E_UNINIT, MCU_PLL_STATUS_UNDEFINED );

#if defined(CFG_SIMULATOR)
    return MCU_PLL_LOCKED;
#endif
#endif

    return Mcu_Hw_GetPllStatus();
}


//-------------------------------------------------------------------


Mcu_ResetType Mcu_GetResetReason(void)
{
    /* @req SWS_Mcu_00125 */
    /* @req SWS_Mcu_00133 */
    /* @req SWS_Mcu_00052*/
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_GETRESETREASON_SERVICE_ID, MCU_E_UNINIT, MCU_RESET_UNDEFINED );

    return Mcu_Global.resetReason;
}

//-------------------------------------------------------------------

/* @req SWS_Mcu_00235 */
/* @req SWS_Mcu_00006 */
Mcu_RawResetType Mcu_GetResetRawValue(void)
{
    Mcu_RawResetType Retval;
    /* @req SWS_Mcu_00135 */
    /* @req SWS_Mcu_00125 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_GETRESETREASON_SERVICE_ID, MCU_E_UNINIT, MCU_GETRESETRAWVALUE_UNINIT_RV );
    Retval = Mcu_Global.rawResetvalue;

    if( FALSE == Mcu_Global.initRun ) {
        Retval = (Mcu_RawResetType)MCU_GETRESETRAWVALUE_UNINIT_RV;
    }

    return Retval;
}

//-------------------------------------------------------------------

#if ( MCU_PERFORM_RESET_API == STD_ON )
/* @req SWS_Mcu_00143 */
void Mcu_PerformReset(void)
{
    /* @req SWS_Mcu_00125 */
    VALIDATE( ( TRUE == Mcu_Global.initRun ), MCU_PERFORMRESET_SERVICE_ID, MCU_E_UNINIT );

    Mcu_Hw_PerformReset();
}
#endif

//-------------------------------------------------------------------

void Mcu_SetMode( Mcu_ModeType mcuMode)
{

    /* @req SWS_Mcu_00125 */
    /* @req SWS_Mcu_00020 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE( ( TRUE == Mcu_Global.initRun ), MCU_SETMODE_SERVICE_ID, MCU_E_UNINIT );
    VALIDATE( ( (mcuMode <= Mcu_Global.config->McuNumberOfMcuModes)), MCU_SETMODE_SERVICE_ID, MCU_E_PARAM_MODE );
    /*lint -restore*/

    Mcu_Hw_SetMode(mcuMode);
}
#if ( MCU_VERSION_INFO_API == STD_ON )
void Mcu_GetVersionInfo( Std_VersionInfoType* versioninfo) {

    /* @req SWS_Mcu_00204 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE( ( NULL != versioninfo ), MCU_GETVERSIONINFO_SERVICE_ID, MCU_E_PARAM_POINTER);

    versioninfo->vendorID = MCU_VENDOR_ID;
    versioninfo->moduleID = MCU_MODULE_ID;
    versioninfo->sw_major_version = MCU_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = MCU_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = MCU_SW_PATCH_VERSION;

}
#endif

/**
 * Get frequency of the oscillator
 */
uint32 Mcu_Arc_GetClockReferencePointFrequency(void)
{
    return Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting].McuClockReferencePointFrequency;
}

