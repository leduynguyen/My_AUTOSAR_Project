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

/** @tagSettings DEFAULT_ARCHITECTURE=PPC|MPC5607B|MPC5645S */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/* ----------------------------[includes]------------------------------------*/

#include "Mcu.h"
#include <string.h>
#include "Std_Types.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#include "mpc55xx.h"
#include "Cpu.h"
#include "io.h"
#include "irq.h"
#include "arc_assert.h" /*lint !e451 Depends on compiler, some don't have the include guard */

#include "Mcu_Internal.h"
#include "Mcu_Arc.h"

//#define CFG_MPC5744P 1
//#define MCU_INIT_CLOCK 1

#if defined(USE_DMA)
#include "Dma.h"
#endif


/* Global requirements */
/* @req SWS_Mcu_00237 Mcu_ModeType specifies the identification mode */
/* @req SWS_Mcu_00239 Mcu_RamSectionType specifies the identification of ram section */
/* @req SWS_Mcu_00232 Mcu_ClockType defines the identification of clock type*/
/* @req SWS_Mcu_00051 Mcu_ModeType specifies the identification*/
/* @req SWS_Mcu_00152 Imported types */

#include "debug.h"

/* ----------------------------[private define]------------------------------*/

#define SYSCLOCK_SELECT_PLL	0x2u


#if defined(CFG_MPC5516) || defined(CFG_MPC5668)

#if defined(CFG_VLE)
#define VLE_VAL		xVEC_VLE
#else
#define VLE_VAL		0
#endif

#endif

#if defined(CFG_MPC5516)
    /* since the MCM module contains the registers normally located in ECSM */
    #define ECSM        MCM
#endif
/* ----------------------------[private macro]-------------------------------*/


#if defined(CFG_MPC5567) || defined(CFG_MPC563XM) || defined(CFG_MPC5644A)
#define CALC_SYSTEM_CLOCK(_extal,_emfd,_eprediv,_erfd)  \
            ( (_extal) * ((_emfd)+4uL) / (((_eprediv)+1uL)*(1uL<<(_erfd))) )
#elif defined(CFG_MPC560X) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70)
#define CALC_SYSTEM_CLOCK(_extal,_emfd,_eprediv,_erfd)  \
            ( ((_extal)*(_emfd)) / (((_eprediv)+1uL)*(2uL<<(_erfd))) )
#elif defined(CFG_MPC5645S)
#define CALC_SYSTEM_CLOCK(_extal,_emfd,_eprediv,_erfd)  \
            ( ((_extal)*(_emfd)) / (2uL*((_eprediv)+1uL)*(2uL<<(_erfd))) )
#else
#define CALC_SYSTEM_CLOCK(_extal,_emfd,_eprediv,_erfd)  \
            ( ((_extal) * ((_emfd)+16uL)) / (((_eprediv)+1uL)*((_erfd)+1uL)) )
#endif



/**
 * Checks if a bit is set
 */
#define ISSET(_x,_bit)	(((_x) & (1uL<<(_bit)))>0u)


/* ----------------------------[private typedef]-----------------------------*/


#if !defined(CFG_MPC560X)
typedef struct{
    uint32 lossOfLockCnt;
    uint32 lossOfClockCnt;
} Mcu_Stats;
#endif

#if 0
/**
 * Type that holds all global data for Mcu
 */
typedef struct
{
    // Set if Mcu_Init() have been called
    boolean initRun;
    // Our config
    const Mcu_ConfigType *config;
    Mcu_ClockType clockSetting;
#if !defined(CFG_MPC560X)
    Mcu_Stats stats;
#endif
    Mcu_RawResetType rawResetvalue;
    Mcu_ResetType resetReason;
} Mcu_GlobalType;

#endif

/* ----------------------------[private function prototypes]-----------------*/

/* Function declarations. */
static void Mcu_ConfigureFlash(void);

/* ----------------------------[private variables]---------------------------*/

#if 0
/**
 * Global config used internally in the MCU
 */
Mcu_GlobalType Mcu_Global =
{
    .initRun = FALSE,
    .config = &McuConfigData[0],
    .clockSetting = 0u,
#if !defined(CFG_MPC560X)
    .stats = {0u, 0u},
#endif
    .rawResetvalue = 0u,
    .resetReason = MCU_POWER_ON_RESET
};
#endif


/* ----------------------------[private functions]---------------------------*/


/**
 * This function get the raw reset reason and also translated to the defined
 * reasons. The reasons are set to the global config and may then be accessed
 * by other functions.
 */
static void GetAndClearResetCause(void) {
    Mcu_ResetType resetReason;

    /* @req SWS_Mcu_00005 */

#if defined(CFG_MPC560X) || defined(CFG_MPC5645S) || defined (CFG_MPC5643L) || defined(CFG_SPC56XL70)
    uint16 rawValueDES;
    uint16 rawValueFES;

    /* DES and FES is 16 bit */
    /*lint -save -e923 Ok, this cast is in Freescale header file */
    rawValueDES = RGM.DES.R;
    rawValueFES = RGM.FES.R;

    RGM.DES.R = rawValueDES;	/* Clear */
    RGM.FES.R = rawValueFES;	/* Clear */
    /*lint -restore  */

    /* Grab reset type */
    if( ISSET(rawValueFES,(15u-13u)) ) {			/* F_SOFT */
        resetReason = MCU_SW_RESET;
    } else if( ISSET(rawValueDES,(15u-13u)) ) {   /* F_SWT */
        resetReason = MCU_WATCHDOG_RESET;
    } else if( ISSET(rawValueDES, 15u)) {	/* F_POR */
        resetReason = MCU_POWER_ON_RESET;
    } else {
        resetReason = MCU_RESET_UNDEFINED;
    }


    Mcu_Global.rawResetvalue = (Mcu_RawResetType)((((uint32)rawValueDES)<<16u) + rawValueFES);

#else
    typeof(SIU.RSR) rawValue;
    rawValue.R = SIU.RSR.R;

    SIU.RSR.R =	rawValue.R; /* Clear */

    if( rawValue.B.SSRS ) {
        resetReason = MCU_SW_RESET;
    } else if( rawValue.B.WDRS ) {
        resetReason = MCU_WATCHDOG_RESET;
    } else if( rawValue.B.PORS ) {
        resetReason = MCU_POWER_ON_RESET;
#if defined(CFG_MPC5644A)
    } else if( rawValue.B.ERS ) {
        resetReason = MCU_EXT_RESET;
#endif
    } else {
        resetReason = MCU_RESET_UNDEFINED;
    }

    Mcu_Global.rawResetvalue = rawValue.R;
#endif

    Mcu_Global.resetReason = resetReason;
}


/* ----------------------------[public functions]----------------------------*/


//-------------------------------------------------------------------


//-------------------------------------------------------------------

#define CORE_PVR_E200Z1         0x81440000UL
#define CORE_PVR_E200Z0         0x81710000UL
#define CORE_PVR_E200Z3         0x81120000UL
#define CORE_PVR_E200Z335       0x81260000UL
#define CORE_PVR_E200Z6         0x81170000UL
#define CORE_PVR_E200Z65        0x81150000UL
#define CORE_PVR_E200Z0H        0x817F0000UL
#define CORE_PVR_E200Z424       0x81560011UL
#define CORE_PVR_E200Z448       0x81570000UL
#define CORE_PVR_E200Z4D        0x81550001UL
#define CORE_PVR_E200Z4D_1      0x81550000UL

/*lint -esym(9003, cpu_info_list) It is defined at block scope */
/*lint -save -e1776 Name only used for test */
const cpu_info_t cpu_info_list[] = {
#if defined(CFG_MPC5516)
    {
        .name = "MPC5516",
        .pvr = CORE_PVR_E200Z1,
        .info = ""
    },
    {
        .name = "MPC5516",
        .pvr = CORE_PVR_E200Z0,
        .info = ""
    },
#elif defined(CFG_MPC5567)
    {
        .name = "MPC5567",
        .pvr = CORE_PVR_E200Z6,
        .info = ""
    }
#elif defined(CFG_MPC563XM)
    {
        .name = "MPC563X",
        .pvr = CORE_PVR_E200Z335,
        .info = ""
    },
#elif defined(CFG_MPC5644A)
    {
        .name = "MPC5644A",
        .pvr = CORE_PVR_E200Z448,
        .info = ""
    },
#elif defined(CFG_MPC5604B)
    {
        .name = "MPC5604B",
        .pvr = CORE_PVR_E200Z0H,
        .info = ""
    },
#elif defined(CFG_MPC5604P)
    {
        .name = "MPC5604P",
        .pvr = CORE_PVR_E200Z0H,
        .info = ""
    },
#elif defined(CFG_SPC560B54)
    {
        .name = "SPC560B54",
        .pvr = CORE_PVR_E200Z0H,
        .info = ""
    },
#elif defined(CFG_MPC5606B)
    {
        .name = "MPC5606B",
        .pvr = CORE_PVR_E200Z0H,
        .info = ""
    },
#elif defined(CFG_MPC5606S)
    {
        .name = "MPC5606S",
        .pvr = CORE_PVR_E200Z0H,
        .info = ""
    },
#elif defined(CFG_MPC5668)
    {
        .name = "MPC5668",
        .pvr = CORE_PVR_E200Z65,
        .info = ""
    },
    {
        .name = "MPC5668",
        .pvr = CORE_PVR_E200Z0,
        .info = ""
    },
#elif defined(CFG_MPC5643L)
    {
        .name = "MPC5643L",
        .pvr = CORE_PVR_E200Z4D,
        .info = ""
    },
#elif defined(CFG_SPC56XL70)
    {
        .name = "SPC56XL70",
        .pvr = CORE_PVR_E200Z4D,
        .info = ""
    },
#elif defined(CFG_MPC5645S)
    {
        .name = "MPC5645S",
        .pvr = CORE_PVR_E200Z4D_1,
        .info = ""
    },
#endif
};

/*lint -esym(9003, core_info_list) It is defined at block scope */
const core_info_t core_info_list[] = {
#if defined(CFG_MPC5516)
    {
        .name = "CORE_E200Z1",
        .pvr = CORE_PVR_E200Z1,
        .info = "Max Freq: 66Mhz, Cache: NO",
    },
    {
        .name = "CORE_E200Z0",
        .pvr = CORE_PVR_E200Z1,
        .info = "Max Freq: 66Mhz, Cache: NO",
    },
#elif defined(CFG_MPC5567)
    {
        .name = "CORE_E200Z6",
        .pvr = CORE_PVR_E200Z6,
        .info = ""
    }
#elif defined(CFG_MPC563XM)
    {
        .name = "CORE_E200Z3",
        .pvr = CORE_PVR_E200Z335,
        .info = ""
    },
#elif defined(CFG_MPC5644A)
    {
        .name = "CORE_PVR_E200Z448",
        .pvr = CORE_PVR_E200Z448,
        .info = ""
    },
#elif defined(CFG_MPC5604B)
    {
        .name = "MPC5604B",
        .pvr = CORE_PVR_E200Z0H,
        .info = ""
    },
#elif defined(CFG_MPC5604P)
    {
        .name = "MPC5604P",
        .pvr = CORE_PVR_E200Z0H,
        .info = ""
    },
#elif defined(CFG_SPC560B54)
    {
        .name = "SPC560B54",
        .pvr = CORE_PVR_E200Z0H,
        .info = ""
    },
#elif defined(CFG_MPC5606B)
    {
        .name = "MPC5606B",
        .pvr = CORE_PVR_E200Z0H,
        .info = ""
    },
#elif defined(CFG_MPC5606S)
    {
        .name = "MPC5606S",
        .pvr = CORE_PVR_E200Z0H,
        .info = ""
    },
#elif defined(CFG_MPC5668)
    {
        .name = "CORE_E200Z65",
        .pvr = CORE_PVR_E200Z65,
        .info = ""
    },
    {
        .name = "CORE_E200Z0",
        .pvr = CORE_PVR_E200Z1,
        .info = ""
    },

#elif defined(CFG_MPC5643L)
    {
        .name = "MPC5643L",
        .pvr = CORE_PVR_E200Z4D,
        .info = ""
    },
#elif defined(CFG_SPC56XL70)
    {
        .name = "SPC56XL70",
        .pvr = CORE_PVR_E200Z4D,
        .info = ""
    },
#elif defined(CFG_MPC5645S)
    {
        .name = "MPC5645S",
        .pvr = CORE_PVR_E200Z4D_1,
        .info = "Max Freq: 120hz, Cache: 4K Instruction",
    },
#endif
};
/*lint -restore */

const cpu_info_t * Mcu_Arc_GetCpuInfoList( uint32 *num ) {
    *num = (sizeof(cpu_info_list)/sizeof((cpu_info_list)[0u]));
    return cpu_info_list;
}

const core_info_t * Mcu_Arc_GetCoreInfoList( uint32 *num ) {
    *num = (sizeof(core_info_list)/sizeof((cpu_info_list)[0u]));
    return core_info_list;
}

#if (MCU_CLOCK_SRC_FAILURE_NOTIFICATION == STD_ON)
/**
 * Called when loss of lock from interrupt
 */
void Mcu_Arc_LossOfLock( void  ){


  /*
   * NOTE!!!
   * This interrupt may be triggered more than expected.
   * If you are going to use this interrupt, see [Freescale Device Errata MPC5510ACE, Rev. 10 APR 2009, errata ID: 6764].
   *
   */
#if defined(CFG_MPC560X)
    /*not support*/
#else
    // Clear interrupt
#if defined (CFG_MPC5744P)
    PLLDIG.PLL1SR.B.LOLF = 1;
#else
    FMPLL.SYNSR.B.LOLF = 1;
#endif
#endif
}

//-------------------------------------------------------------------

/**
 * Called when loss of clock
 */
void Mcu_Arc_LossOfClock( void  ){

    /* @req SWS_Mcu_00226 No return value */

#if defined(CFG_MPC560X) || defined(CFG_MPC5744P)
    /*not support*/
#else

#ifdef USE_DEM
    /* @req:PPC SWS_Mcu_00053 */
    /* @req:PPC SWS_Mcu_00051 */
    /* @req:PPC SWS_Mcu_00166 */
    if( DEM_EVENT_ID_NULL != McuGlobal.config.McuClockFailure ) {
        Dem_ReportErrorStatus(McuGlobal.config.McuClockFailure, DEM_EVENT_STATUS_FAILED);
    }
#endif

    // Clear interrupt
    FMPLL.SYNSR.B.LOCF = 1;
#endif

}

#endif

//-------------------------------------------------------------------

/**
 * Initializes the MCU
 * @param ConfigPtr
 */
void Mcu_Hw_Init(const Mcu_ConfigType *ConfigPtr)
{
    Mcu_Arc_InitPre(ConfigPtr);

    /* Get reset cause and clear */
    GetAndClearResetCause();

    /* Setup Flash */
    Mcu_ConfigureFlash();

    Mcu_Global.config = ConfigPtr;

#if defined(CFG_MPC560X)
    /* Enable DRUN, RUN0, SAFE, RESET modes */
    /*lint -e{923}  Ok, this cast is in Freescale header file */
    ME.MER.R = 0x0000001D;
    /*	MPC5604P: CMU_0 must be initialized differently from the default value
                in case of 8 MHz crystal. */
#if defined (CFG_MPC5604P)
    CGM.CMU_0_CSR.R = 0x00000004;
#endif
#endif

    Mcu_Global.initRun = TRUE;

#if (MCU_CLOCK_SRC_FAILURE_NOTIFICATION == STD_ON)

#if defined(CFG_MPC560X)
        /*not support*/
#else
        ISR_INSTALL_ISR1("LossOfLock", Mcu_Arc_LossOfLock, PLL_SYNSR_LOLF, 10 , 0 );
#if defined(CFG_MPC5516)  || defined(CFG_MPC5668)
        FMPLL.ESYNCR2.B.LOLIRQ = 1;
#elif defined(CFG_MPC5554) || defined(CFG_MPC5567) || defined(CFG_MPC563XM) || defined(CFG_MPC5644A)
        FMPLL.SYNCR.B.LOLIRQ = 1;
#endif
        ISR_INSTALL_ISR1("LossOfClock", Mcu_Arc_LossOfClock, PLL_SYNSR_LOCF, 10 , 0 );
#if defined(CFG_MPC5516) || defined(CFG_MPC5668)
        FMPLL.ESYNCR2.B.LOCIRQ = 1;
#elif defined(CFG_MPC5554) || defined(CFG_MPC5567) || defined(CFG_MPC563XM) || defined(CFG_MPC5644A)
        FMPLL.SYNCR.B.LOCIRQ = 1;
#endif
#endif

#endif /* MCU_CLOCK_SRC_FAILURE_NOTIFICATION == STD_ON */

    Mcu_Arc_InitPost(ConfigPtr);

}


//-------------------------------------------------------------------


#if ( MCU_INIT_CLOCK == STD_ON )
/**
 * Initializes clock
 * @param ClockSetting
 * @return
 */
Std_ReturnType Mcu_Hw_InitClock(const Mcu_ClockSettingConfigType *clockSettingsPtr)
{

    Mcu_Arc_InitClockPre(clockSettingsPtr);

    // IMPROVEMENT: find out if the 5554 really works like the 5516 here
    // All three (16, 54, 67) used to run the same code here though, so i'm sticking it with 5516
#if defined(CFG_MPC5516) || defined(CFG_MPC5554) || defined(CFG_MPC5668)
    /* 5516clock info:
     * Fsys - System frequency ( CPU + all periperals? )
     *
     *  Fsys = EXTAL_FREQ *(  (emfd+16) / ( (eprediv+1) * ( erfd+1 )) ) )
     */
    // Check ranges...
    CONFIG_ASSERT((clockSettingsPtr->Pll2>=32) && (clockSettingsPtr->Pll2<=132));
    CONFIG_ASSERT( (clockSettingsPtr->Pll1 != 6) &&
            (clockSettingsPtr->Pll1 != 8) &&
            (clockSettingsPtr->Pll1 < 10) );
    CONFIG_ASSERT( clockSettingsPtr->Pll3 & 1); // Must be odd
#elif defined(CFG_MPC5567)
    /* 5567 clock info:
     *  Fsys = EXTAL_FREQ *(  (emfd+4) / ( (eprediv+1) * ( 2^erfd )) ) )
     */
    // Check ranges...
    CONFIG_ASSERT(clockSettingsPtr->Pll1 <= 4);
    CONFIG_ASSERT(clockSettingsPtr->Pll2 < 16);
    CONFIG_ASSERT(clockSettingsPtr->Pll3 < 8);
#elif defined(CFG_MPC563XM)
    /* 563XM clock info:
     *  Fsys = EXTAL_FREQ *(  (emfd+4) / ( (eprediv+1) * ( 2^erfd )) ) )
     */
    // Check ranges...
    CONFIG_ASSERT(clockSettingsPtr->Pll1 < 8);
    CONFIG_ASSERT(clockSettingsPtr->Pll2 <= 20);
    CONFIG_ASSERT(clockSettingsPtr->Pll3 <= 2);
#elif defined(CFG_MPC5644A)
    /* 5644A clock info:
     *  Fsys = EXTAL_FREQ *(  (emfd+4) / ( (eprediv+1) * ( 2^erfd )) ) )
     */
    // Check ranges...
    CONFIG_ASSERT(clockSettingsPtr->Pll1 < 8);
    CONFIG_ASSERT(clockSettingsPtr->Pll2 <= 20);
    CONFIG_ASSERT(clockSettingsPtr->Pll3 <= 2);
#endif

#if defined(USE_LDEBUG_PRINTF)
    {
        uint32  extal = Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting].McuClockReferencePointFrequency;
        uint32  f_sys;

        f_sys = CALC_SYSTEM_CLOCK( extal,
            clockSettingsPtr->Pll2,
            clockSettingsPtr->Pll1,
            clockSettingsPtr->Pll3 );

        //DEBUG(DEBUG_HIGH,"/drivers/mcu: F_sys will be:%08d Hz\n",f_sys);
    }
#endif

#if defined(CFG_MPC5516) || defined(CFG_MPC5668)
    
    // set post divider to next valid value to ensure that an overshoot during lock phase
    // won't result in a too high freq
    FMPLL.ESYNCR2.B.ERFD = (clockSettingsPtr->Pll3 + 1) | 1;

    // External crystal PLL mode.
    FMPLL.ESYNCR1.B.CLKCFG = 7;

    // Write pll parameters.
    FMPLL.ESYNCR1.B.EPREDIV = clockSettingsPtr->Pll1;
    FMPLL.ESYNCR1.B.EMFD    = clockSettingsPtr->Pll2;

#if !defined(CFG_SIMULATOR)
    while(FMPLL.SYNSR.B.LOCK != 1) {};
#endif

    FMPLL.ESYNCR2.B.ERFD    = clockSettingsPtr->Pll3;
    // Connect SYSCLK to FMPLL
    SIU.SYSCLK.B.SYSCLKSEL = SYSCLOCK_SELECT_PLL;
 #elif defined(CFG_MPC5554) || defined(CFG_MPC5567)
    
    // Partially following the steps in MPC5567 RM..
    FMPLL.SYNCR.B.DEPTH	= 0;
    FMPLL.SYNCR.B.LOLRE	= 0;
    FMPLL.SYNCR.B.LOLIRQ = 0;
    
    FMPLL.SYNCR.B.PREDIV 	= clockSettingsPtr->Pll1;
    FMPLL.SYNCR.B.MFD		= clockSettingsPtr->Pll2;
    FMPLL.SYNCR.B.RFD    	= clockSettingsPtr->Pll3;

    // Wait for PLL to sync.
#if !defined(CFG_SIMULATOR)
    while (Mcu_GetPllStatus() != MCU_PLL_LOCKED) ;
#endif

    FMPLL.SYNCR.B.LOLIRQ    = 1;
#elif defined(CFG_MPC563XM) || defined(CFG_MPC5644A)

   FMPLL.SYNCR.B.PREDIV 	= clockSettingsPtr->Pll1;
   FMPLL.SYNCR.B.MFD		= clockSettingsPtr->Pll2;
   FMPLL.SYNCR.B.RFD    	= clockSettingsPtr->Pll3;

    // Wait for PLL to sync.
#if !defined(CFG_SIMULATOR)
   while (Mcu_GetPllStatus() != MCU_PLL_LOCKED) ;
#endif

   FMPLL.SYNCR.B.LOLIRQ	= 1;
#endif

    Mcu_Arc_InitClockPost(clockSettingsPtr);

    return E_OK;
}

#endif /* #if ( MCU_INIT_CLOCK == STD_ON )*/

//-------------------------------------------------------------------

#if ( MCU_NO_PLL == STD_OFF )
/**
 * Distributes the PLL clock
 * @return
 */
Std_ReturnType Mcu_Hw_DistributePllClock(void)
{
    /* !req SWS_Mcu_00140  */
    /* !req SWS_Mcu_00141 */
    /* !req SWS_Mcu_00056 */

    /* NOT IMPLEMENTED due to pointless function on this hardware */
    return E_OK;

}

#endif /* #if ( MCU_NO_PLL == STD_ON ) */

//-------------------------------------------------------------------

/**
 * Gets PLL status
 * @return
 */
Mcu_PllStatusType Mcu_Hw_GetPllStatus(void)
{

    Mcu_PllStatusType rv;

#if !defined(CFG_SIMULATOR)
#if defined(CFG_MPC560XB)
        /*lint -e{923}  Ok, this cast is in Freescale header file */
        if ( 0u == CGM.FMPLL_CR.B.S_LOCK )
        {
            rv = MCU_PLL_UNLOCKED;
        } else
        {
            rv = MCU_PLL_LOCKED;
        }
#elif defined(CFG_MPC5606S) || defined(CFG_MPC5604P) || defined(CFG_MPC5645S)
        if ( 0u == CGM.FMPLL[0].CR.B.S_LOCK )
        {
            rv = MCU_PLL_UNLOCKED;
        } else
        {
            rv = MCU_PLL_LOCKED;
        }
#elif defined(CFG_MPC5643L) || defined(CFG_SPC56XL70)
        if ( 0u == PLLD0.CR.B.S_LOCK ) {
            rv = MCU_PLL_UNLOCKED;
        } else {
            rv = MCU_PLL_LOCKED;
        }
#else
        if ( 0u == FMPLL.SYNSR.B.LOCK)
        {
            rv = MCU_PLL_UNLOCKED;
        } else
        {
            rv = MCU_PLL_LOCKED;
        }
#endif
#else
    /* We are running on instruction set simulator. PLL is then always in sync... */
    rv = MCU_PLL_LOCKED;
#endif

    /* @req SWS_Mcu_00008, The function Mcu_GetPllStatus shall return the lock status of the PLL*/
  return rv;
}


//-------------------------------------------------------------------

//-------------------------------------------------------------------

#if ( MCU_PERFORM_RESET_API == STD_ON )
/**
 * Performs a reset
 */
void Mcu_Hw_PerformReset(void) {
    // Reset
    /*lint -save -e923  Ok, this cast is in Freescale header file */
#if defined(CFG_MPC560X) || defined(CFG_MPC5645S) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70)
#ifndef ME
#define ME MC_ME
#endif
    ME.MCTL.R = 0x00005AF0;   /* Reset, 0x5AF0 is control key to enable writing to register */
    ME.MCTL.R = 0x0000A50F;   /* Reset, 0xA50F is inverted control key to enable writing to register */

    while(ME.GS.B.S_MTRANS != 0) {}
    while(ME.GS.B.S_CURRENTMODE != 0) {}
#else
    SIU.SRCR.B.SSR = 1;
#endif
    /*lint -restore */
}
#endif



/**
 * Sets MCU mode
 * @param mcuMode
 */
void Mcu_Hw_SetMode( Mcu_ModeType mcuMode)
{
#if defined(CFG_MCU_ARC_LP)
    Mcu_Arc_SetModePre(mcuMode);
    Mcu_Arc_SetModePost(mcuMode);
#endif
}


#if defined(CFG_MPC5777M)
/**
 * Gets XOSC
 * @return
 */

static inline uint32_t GetXosc() {
    return  Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting].McuClockReferencePointFrequency;
}
/**
 * Gets Pll0 Clock
 * @return
 */
static uint32_t GetPll0Clock(void) {
    uint32_t eprediv = PLLDIG.PLL0DV.B.PREDIV;
    uint32_t emfd = PLLDIG.PLL0DV.B.MFD;
    uint32_t erfd = PLLDIG.PLL0DV.B.RFDPHI;
    uint32_t f_pll0;

    if(MC_CGM.AC3_SC.B.SELCTL== 1u) {
       uint32  extal = GetXosc();
       f_pll0 = (extal * 2u * emfd) / (eprediv * erfd * 2u);
    }
    else{
      f_pll0 = 16000000uL; /* default internal OSC */
    }
    return f_pll0;
}


/**
 * Gets Pll1 Clock
 * @return
 */
static uint32_t GetPll1Clock(void) {
    uint32_t emfd = PLLDIG.PLL1DV.B.MFD;
    uint32_t erfd = PLLDIG.PLL1DV.B.RFDPHI;
    uint32_t f_pll1;
    uint32  ref = 0u;
    if(MC_CGM.AC4_SC.B.SELCTL==1u) {
        /* pll1 uses the oscillator as clock source */
        ref = GetXosc();
    } else {
        /* pll1 uses PLL0 PHI1 as clock source */
        ref = GetPll0Clock();
    }
    f_pll1 = (ref * emfd) / (erfd * 2u);
    return f_pll1;
}


/**
 * Get the system clock in Hz. It calculates the clock from the
 * different register settings in HW.
 * @return
 */
uint32_t Mcu_Arc_GetSystemClock(void) {
    uint32 sysClock = 0;
    if(MC_ME.GS.B.S_SYSCLK == 1u) {
        sysClock= GetXosc();
    }
    else if(MC_ME.GS.B.S_SYSCLK   == 2u) {
        // sys clock is driven by pll0
        sysClock = GetPll0Clock();
    } else if(MC_ME.GS.B.S_SYSCLK == 4u) {
        // sys clock is driven by pll1
        sysClock = GetPll1Clock();
    }
    else {
        sysClock = 16000000uL; /* default internal OSC */
    }
    return sysClock;
}

#else

/**
 * Get the system clock in Hz. It calculates the clock from the
 * different register settings in HW.
 * @return
 */
uint32 Mcu_Arc_GetSystemClock(void)
{
    /*
     * System clock calculation
     *
     * 5516 -  f_sys = extal * (emfd+16) / ( (eprediv+1) * ( erfd+1 ));
     * 5567 -  f_sys = extal * (emfd+4) / ( (eprediv+1) * ( 2^erfd ));
     * 563x -  We run in legacy mode = 5567
     * 5606s - f_sys = extal * emfd / ((eprediv+1)*(2<<(erfd)));
     */
    /*lint -save -e923  Ok, this cast is in Freescale header file */
#if defined(CFG_MPC5516) || defined(CFG_MPC5668)
    uint32 eprediv = FMPLL.ESYNCR1.B.EPREDIV;
    uint32 emfd = FMPLL.ESYNCR1.B.EMFD;
    uint32 erfd = FMPLL.ESYNCR2.B.ERFD;
#elif defined(CFG_MPC5554) || defined(CFG_MPC5567) || defined(CFG_MPC563XM) || defined(CFG_MPC5644A)
    uint32 eprediv = FMPLL.SYNCR.B.PREDIV;
    uint32 emfd = FMPLL.SYNCR.B.MFD;
    uint32 erfd = FMPLL.SYNCR.B.RFD;
#elif defined(CFG_MPC560XB)
    uint32 eprediv = CGM.FMPLL_CR.B.IDF;
    uint32 emfd = CGM.FMPLL_CR.B.NDIV;
    uint32 erfd = CGM.FMPLL_CR.B.ODF;
#elif defined(CFG_MPC5643L) || defined(CFG_SPC56XL70)
    uint32 eprediv = PLLD0.CR.B.IDF;
    uint32 emfd = PLLD0.CR.B.NDIV;
    uint32 erfd = PLLD0.CR.B.ODF;
#elif defined(CFG_MPC5606S) || defined(CFG_MPC5604P) || defined(CFG_MPC5645S)
    uint32 eprediv = CGM.FMPLL[0].CR.B.IDF;
    uint32 emfd = CGM.FMPLL[0].CR.B.NDIV;
    uint32 erfd = CGM.FMPLL[0].CR.B.ODF;
#elif defined (CFG_MPC5744P)
    uint32 eprediv = PLLDIG.PLL0DV.B.PREDIV;
    uint32 emfd = PLLDIG.PLL0DV.B.MFD;
    uint32 erfd = PLLDIG.PLL0DV.B.RFDPHI;
#else
#error No CPU selected
#endif
    /*lint -restore */

    uint32  extal = Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting].McuClockReferencePointFrequency;
    uint32 f_sys = CALC_SYSTEM_CLOCK(extal,emfd,eprediv,erfd);

    return f_sys;
}
#endif

#if defined(CFG_MPC5668)
/***
 * Gets a peripheral clock in Hz.
 * @param type
 * @return
 */
uint32 Mcu_Arc_GetPeripheralClock(Mcu_Arc_PeriperalClock_t type) {
    uint32 sysClock = Mcu_Arc_GetSystemClock();
    vuint32_t prescaler;

    switch (type)
    {
        case PERIPHERAL_CLOCK_PIT_0:
            prescaler = 0;
            break;
        case PERIPHERAL_CLOCK_FLEXCAN_A:
        case PERIPHERAL_CLOCK_FLEXCAN_B:
        case PERIPHERAL_CLOCK_FLEXCAN_C:
        case PERIPHERAL_CLOCK_FLEXCAN_D:
        case PERIPHERAL_CLOCK_FLEXCAN_E:
        case PERIPHERAL_CLOCK_FLEXCAN_F:
        case PERIPHERAL_CLOCK_DSPI_A:
        case PERIPHERAL_CLOCK_DSPI_B:
        case PERIPHERAL_CLOCK_DSPI_C:
        case PERIPHERAL_CLOCK_DSPI_D:
            prescaler = SIU.SYSCLK.B.LPCLKDIV1;
            break;
        case PERIPHERAL_CLOCK_ESCI_A:
        case PERIPHERAL_CLOCK_ESCI_B:
        case PERIPHERAL_CLOCK_ESCI_C:
        case PERIPHERAL_CLOCK_ESCI_D:
        case PERIPHERAL_CLOCK_ESCI_E:
        case PERIPHERAL_CLOCK_ESCI_F:
        case PERIPHERAL_CLOCK_IIC_A:
        case PERIPHERAL_CLOCK_IIC_B:
            prescaler = SIU.SYSCLK.B.LPCLKDIV0;
            break;
        case PERIPHERAL_CLOCK_ADC_A:
            prescaler = SIU.SYSCLK.B.LPCLKDIV2;
            break;
        case PERIPHERAL_CLOCK_EMIOS:
            prescaler = SIU.SYSCLK.B.LPCLKDIV3;
            break;
        default:
            ASSERT(0);
            break;
    }

    return sysClock/(1<<prescaler);

}

#elif defined(CFG_MPC5645S)

/**
 * Gets a peripheral clock in Hz.
 * @param type
 * @return
 */
uint32 Mcu_Arc_GetPeripheralClock(Mcu_Arc_PeriperalClock_t type) {

    uint32 sysClock = Mcu_Arc_GetSystemClock();
    vuint32_t prescaler = 1;

    /*
     * AUX0: DCU3
     * AUX1: eMIOS0
     * AUX2: eMIOS1
     * AUX3: QuadSPI
     * AUX4: DCULite
     *
     * Peripheral Sets:
     *  1. LinFlex, I2C, Stepper Motor  (CGM_SC_DC0)
     *  2. FlexCAN, Can Sampler , DSPI  (CGM_SC_DC1)
     *  3. ADC                          (CGM_SC_DC2)
     *  4. Sound generation module.     ( divide by 2)
     */

    switch (type)
    {

        case PERIPHERAL_CLOCK_FLEXCAN_A:
        case PERIPHERAL_CLOCK_FLEXCAN_B:
        case PERIPHERAL_CLOCK_FLEXCAN_C:
        case PERIPHERAL_CLOCK_FLEXCAN_D:
        case PERIPHERAL_CLOCK_FLEXCAN_E:
        case PERIPHERAL_CLOCK_FLEXCAN_F:
        case PERIPHERAL_CLOCK_DSPI_A:
        case PERIPHERAL_CLOCK_DSPI_B:
        case PERIPHERAL_CLOCK_DSPI_C:
        case PERIPHERAL_CLOCK_DSPI_D:
            if( CGM.SC_DC[1].B.DE ) {
                prescaler = CGM.SC_DC[1].B.DIV + 1;
            }
            break;
        case PERIPHERAL_CLOCK_EMIOS_0:
            /* Check what system clock that is selected */
            switch( CGM.AC1_SC.B.SELCTL ) {
                 case 0:
                     /* FIRC */
                     sysClock = 16000000;
                     break;
                 case 1:
                     /* EXTAL */
                     sysClock = 8000000;
                     break;
                 case 2:
                     /* NOT SUPPORTED */
                     break;
                 case 3:
                     /* FMPLL0 */
                     break;
                 default:
                     ASSERT(0);
                     break;
            }

            /* .. and prescaler */
            if( CGM.AC1_DC.B.DE0 ) {
                prescaler = CGM.AC1_DC.B.DIV0 + 1;
            }
            break;
        case PERIPHERAL_CLOCK_EMIOS_1:
            /* Check what system clock that is selected */
            switch( CGM.AC2_SC.B.SELCTL ) {
                 case 0:
                     /* FIRC */
                     sysClock = 16000000;
                     break;
                 case 1:
                     /* EXTAL */
                     sysClock = 8000000;
                     break;
                 case 2:
                     /* NOT SUPPORTED */
                     break;
                 case 3:
                     /* FMPLL0 */
                     break;
                 default:
                     ASSERT(0);
                     break;
            }

            /* .. and prescaler */
            if( CGM.AC2_DC.B.DE0 ) {
                prescaler = CGM.AC2_DC.B.DIV0 + 1;
            }
            break;

        case PERIPHERAL_CLOCK_LIN_A:
        case PERIPHERAL_CLOCK_LIN_B:
        case PERIPHERAL_CLOCK_LIN_C:
        case PERIPHERAL_CLOCK_LIN_D:
            if( CGM.SC_DC[0].B.DE ) {
                prescaler = CGM.SC_DC[0].B.DIV + 1;
            }
            break;

        case PERIPHERAL_CLOCK_PIT_0:
        case PERIPHERAL_CLOCK_PIT_1:
        case PERIPHERAL_CLOCK_PIT_2:
        case PERIPHERAL_CLOCK_PIT_3:
            // using the system clock
            prescaler = 1;
            break;
        default:
            ASSERT(0);
            break;
    }

    return sysClock/(prescaler);
}
#elif defined(CFG_MPC5643L) || defined(CFG_SPC56XL70)
/***
 * Gets a peripheral clock in Hz.
 * @param type
 * @return
 */
uint32 Mcu_Arc_GetPeripheralClock(Mcu_Arc_PeriperalClock_t type) {
    uint32 sysClock = Mcu_Arc_GetSystemClock();
    vuint32_t prescaler;

    switch (type)
    {
        case PERIPHERAL_CLOCK_FLEXCAN_A:
        case PERIPHERAL_CLOCK_FLEXCAN_B:
#if defined(CFG_SPC56XL70)
        case PERIPHERAL_CLOCK_FLEXCAN_C:
#endif
            prescaler = CGM.AC2_DC0.B.DIV + 1;
            break;
        case PERIPHERAL_CLOCK_DSPI_A:
        case PERIPHERAL_CLOCK_DSPI_B:
        case PERIPHERAL_CLOCK_DSPI_C:
        case PERIPHERAL_CLOCK_LIN_A:
        case PERIPHERAL_CLOCK_LIN_B:
        case PERIPHERAL_CLOCK_PIT:
            /* Peripheral set 0 */
            prescaler = CGM.SC_DC0.B.DIV + 1;
            break;
        case PERIPHERAL_CLOCK_FLEXPWM_0:
            /* Motor control */
            prescaler = CGM.AC0_DC0.B.DIV + 1;
            break;
        default:
            ASSERT(0);
            break;
    }

    return sysClock/(prescaler);

}

#elif defined(CFG_MPC5777M)
/**
 * Gets AuxClock0
 * @return
 */
static uint32 GetAuxClock0(void) {
    uint32 clock = 0;
    if(MC_CGM.AC0_SC.B.SELCTL == 2) {
        // sys clock is driven by pll0
        clock = GetPll0Clock();
    }
    return clock;
}


/***
 * Gets a peripheral clock in Hz.
 * @param type
 * @return
 */
uint32_t Mcu_Arc_GetPeripheralClock(Mcu_Arc_PeriperalClock_t type) {
    uint32_t clock = 0;
    vuint32_t prescaler;

    switch (type)
    {
        case PERIPHERAL_CLOCK_M_CAN_1:
        case PERIPHERAL_CLOCK_M_CAN_2:
        case PERIPHERAL_CLOCK_M_CAN_3:
        case PERIPHERAL_CLOCK_M_CAN_4:
            // ppbridge clock
            if (MC_CGM.AC8_SC.B.SELCTL == 0x1) {
                //external clock source
                clock = GetXosc();
                MC_CGM.AC8_DC0.R = 0x80000000uL;
                //Div = 0 + 1
                // 40 MHz / 1 = 40 MHz

            } else if (MC_CGM.AC8_SC.B.SELCTL == 0x2) {
                //PLL
                clock = GetPll0Clock();
                MC_CGM.AC8_DC0.R = 0x800E0000uL;
                //Div = 14 + 1
                // 600 MHz / 15 = 40 MHz
            }
            prescaler = MC_CGM.AC8_DC0.B.DIV + 1;
            break;
        case PERIPHERAL_CLOCK_PIT_0:
        case PERIPHERAL_CLOCK_PIT_1:
        case PERIPHERAL_CLOCK_PIT_2:
        case PERIPHERAL_CLOCK_PIT_3:
            // ppbridge clock
            clock = Mcu_Arc_GetSystemClock();
            prescaler = MC_CGM.SC_DC2.B.DIV + 1;
            break;
        case PERIPHERAL_CLOCK_DSPI_A:
        case PERIPHERAL_CLOCK_DSPI_B:
        case PERIPHERAL_CLOCK_DSPI_C:
        case PERIPHERAL_CLOCK_DSPI_D:
        case PERIPHERAL_CLOCK_DSPI_12:
        case PERIPHERAL_CLOCK_LIN_A:
        case PERIPHERAL_CLOCK_LIN_B:
        case PERIPHERAL_CLOCK_LIN_14:
        case PERIPHERAL_CLOCK_LIN_15:
        case PERIPHERAL_CLOCK_LIN_16:
            clock = GetAuxClock0();
            prescaler = MC_CGM.AC0_DC4.B.DIV + 1;
            break;
        case PERIPHERAL_CLOCK_DSPI_E:
        case PERIPHERAL_CLOCK_DSPI_F:
        case PERIPHERAL_CLOCK_DSPI_6:
            clock = GetAuxClock0();
            switch(MC_CGM.AC0_DC3.B.DIV_FMT) {
            case 0:
                // no fraction
                break;
            case 1:
                clock = clock * 10;
                break;
            case 2:
                clock = clock * 100;
                break;
            case 3:
                clock = clock * 1000;
                break;
            }
            prescaler = MC_CGM.AC0_DC3.B.DIV + 1;
            break;
        case PERIPHERAL_CLOCK_FEC_0:
            if ( MC_CGM.AC10_SC.B.SELCTL == 2u)
            {
                clock = GetPll0Clock();
            }else{
                clock = GetXosc();
            }
            prescaler = MC_CGM.AC10_DC0.B.DIV + 1u;
            break;
        default:
            ASSERT(0);
            break;
    }

    return clock/(prescaler);

}

#elif defined (CFG_MPC5604P)

/***
 * Gets a peripheral clock in Hz.
 * @param type
 * @return
 */
 uint32 Mcu_Arc_GetPeripheralClock(Mcu_Arc_PeriperalClock_t type)
 {
     uint32 sysClock = Mcu_Arc_GetSystemClock();
    vuint32_t prescaler;

   // See table 3.1, section 3.4.5 Peripheral Clock dividers
    switch (type)
    {
        case PERIPHERAL_CLOCK_FLEXPWM_0:
            /* FMPLL1 */
             uint32 eprediv = CGM.FMPLL[1].CR.B.IDF;
             uint32 emfd = CGM.FMPLL[1].CR.B.NDIV;
             uint32 erfd = CGM.FMPLL[1].CR.B.ODF;

             uint32 f_sys;
             uint32  extal = Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting].McuClockReferencePointFrequency;
             f_sys = CALC_SYSTEM_CLOCK(extal,emfd,eprediv,erfd);

             prescaler = CGM.AC0DC.B.DIV0;
             return f_sys/(1<<prescaler);
         break;

        case PERIPHERAL_CLOCK_FLEXCAN_A:
        case PERIPHERAL_CLOCK_FLEXCAN_B:
        case PERIPHERAL_CLOCK_FLEXCAN_C:
        case PERIPHERAL_CLOCK_FLEXCAN_D:
        case PERIPHERAL_CLOCK_FLEXCAN_E:
        case PERIPHERAL_CLOCK_FLEXCAN_F:
        case PERIPHERAL_CLOCK_DSPI_A:
         case PERIPHERAL_CLOCK_DSPI_B:
        case PERIPHERAL_CLOCK_DSPI_C:
        case PERIPHERAL_CLOCK_DSPI_D:
        case PERIPHERAL_CLOCK_DSPI_E:
        case PERIPHERAL_CLOCK_DSPI_F:
        case PERIPHERAL_CLOCK_PIT:
        case PERIPHERAL_CLOCK_LIN_A:
        case PERIPHERAL_CLOCK_LIN_B:
         case PERIPHERAL_CLOCK_LIN_C:
        case PERIPHERAL_CLOCK_LIN_D:
        case PERIPHERAL_CLOCK_PIT_0:
        case PERIPHERAL_CLOCK_PIT_1:
        case PERIPHERAL_CLOCK_PIT_2:
        case PERIPHERAL_CLOCK_PIT_3:
            prescaler = 0;
            break;

        default:
            ASSERT(0);
            break;
    }

    return sysClock/(1<<prescaler);
}
#else

 /***
  * Gets a peripheral clock in Hz.
  * @param type
  * @return
  */
uint32 Mcu_Arc_GetPeripheralClock(Mcu_Arc_PeriperalClock_t type)
{
#if defined(CFG_MPC5567) || defined(CFG_MPC563XM) || defined(CFG_MPC5644A)
    // No peripheral dividers on 5567.
    return Mcu_Arc_GetSystemClock();
#else
    uint32 sysClock = Mcu_Arc_GetSystemClock();
    uint32 prescaler;

    // See table 3.1, section 3.4.5 Peripheral Clock dividers
    /*lint -save -e923  Ok, this cast is in Freescale header file  */
    switch (type)
    {
        case PERIPHERAL_CLOCK_FLEXCAN_A:
        case PERIPHERAL_CLOCK_DSPI_A:
#if defined(CFG_MPC5516)
            prescaler = SIU.SYSCLK.B.LPCLKDIV0;
            break;
#elif defined(CFG_MPC560X)
            prescaler = (CGM.SC_DC[1].B.DE != 0uL) ? CGM.SC_DC[1].B.DIV : 0uL;
            break;
#endif

        case PERIPHERAL_CLOCK_PIT:
        case PERIPHERAL_CLOCK_ESCI_A:
        case PERIPHERAL_CLOCK_IIC_A:
#if defined(CFG_MPC5516)
            prescaler = SIU.SYSCLK.B.LPCLKDIV1;
            break;
#endif

        case PERIPHERAL_CLOCK_FLEXCAN_B:
        case PERIPHERAL_CLOCK_FLEXCAN_C:
        case PERIPHERAL_CLOCK_FLEXCAN_D:
        case PERIPHERAL_CLOCK_FLEXCAN_E:
        case PERIPHERAL_CLOCK_FLEXCAN_F:
#if defined(CFG_MPC5516)
            prescaler = SIU.SYSCLK.B.LPCLKDIV2;
            break;
#elif defined(CFG_MPC560X)
            prescaler = (CGM.SC_DC[1].B.DE != 0uL) ? CGM.SC_DC[1].B.DIV : 0uL;
            break;
#endif

        case PERIPHERAL_CLOCK_DSPI_B:
        case PERIPHERAL_CLOCK_DSPI_C:
        case PERIPHERAL_CLOCK_DSPI_D:
        case PERIPHERAL_CLOCK_DSPI_E:
        case PERIPHERAL_CLOCK_DSPI_F:
#if defined(CFG_MPC5516)
            prescaler = SIU.SYSCLK.B.LPCLKDIV3;
            break;
#endif

        case PERIPHERAL_CLOCK_ESCI_B:
        case PERIPHERAL_CLOCK_ESCI_C:
        case PERIPHERAL_CLOCK_ESCI_D:
        case PERIPHERAL_CLOCK_ESCI_E:
        case PERIPHERAL_CLOCK_ESCI_F:
        case PERIPHERAL_CLOCK_ESCI_G:
        case PERIPHERAL_CLOCK_ESCI_H:
#if defined(CFG_MPC5516)
            prescaler = SIU.SYSCLK.B.LPCLKDIV4;
            break;
#endif

#if defined(CFG_MPC560X)
        case PERIPHERAL_CLOCK_LIN_A:
        case PERIPHERAL_CLOCK_LIN_B:
        case PERIPHERAL_CLOCK_LIN_C:
        case PERIPHERAL_CLOCK_LIN_D:
            prescaler = (CGM.SC_DC[0].B.DE != 0uL) ? CGM.SC_DC[0].B.DIV : 0uL;
            break;
        case PERIPHERAL_CLOCK_EMIOS_0:
        case PERIPHERAL_CLOCK_EMIOS_1:
            prescaler = (CGM.SC_DC[2].B.DE != 0uL) ? CGM.SC_DC[2].B.DIV : 0uL;
            break;
#else
        case PERIPHERAL_CLOCK_EMIOS:
#if defined(CFG_MPC5516)
            prescaler = SIU.SYSCLK.B.LPCLKDIV5;
            break;
#endif
#endif

        case PERIPHERAL_CLOCK_MLB:
#if defined(CFG_MPC5516)
            prescaler = SIU.SYSCLK.B.LPCLKDIV6;
            break;
#endif

        default:
            REPORT_ERROR(MCU_ARC_GET_PERIPHERAL_CLOCK, MCU_E_UNEXPECTED_EXECUTION);
            prescaler = 0uL;
            break;
    }
    /*lint -restore */
#if defined(CFG_MPC560X)
    /*lint -e{632} Ok, this expression is correct. */
    return sysClock / (1uL + prescaler);
#else
    return sysClock / (1uL<< prescaler);
#endif
#endif
}
#endif

/**
 * Function to setup the internal flash for optimal performance
 */
static void Mcu_ConfigureFlash(void) {
    /* These flash settings increases the CPU performance of 7 times compared
          to reset default settings!! */
    /*lint -e923  Ok, this cast is in Freescale header file  */
#if defined(CFG_MPC5516)
      /* Have 2 ports, p0 and p1
     * - All Z1 instructions go to port 0
     * - All Z1 data go to port 1
     *
     * --> Flash port 0 is ONLY used by Z1 instructions.
     */

    /* Disable pipelined reads when flash options are changed. */
    FLASH.MCR.B.PRD = 1;
    /* Errata e1178 (note that Errata A is the same as Errata B)
     * - Disable all prefetch for all masters
     * - Fixed Arb mode+ Port 0 highest prio
     * - PFCRPn[RWSC] = 0b010; PFCRPn[WWSC] = 0b01 for 80Mhz (MPC5516 data sheeet)
     * - APC = RWSC, The settings for APC and RWSC should be the same. ( MPC5516 ref.  manual)
     */
    FLASH.PFCRP0.R = PFCR_LBCFG(0) + PFCR_ARB + PFCR_APC(2) + PFCR_RWSC(2) + PFCR_WWSC(1) + PFCR_BFEN;
    FLASH.PFCRP1.R = PFCR_LBCFG(3) + PFCR_APC(2) + PFCR_RWSC(2) + PFCR_WWSC(1) + PFCR_BFEN;

    /* Enable pipelined reads again. */
    FLASH.MCR.B.PRD = 0;
#elif defined(CFG_MPC5668)
    /* Check values from cookbook and MPC5668x Microcontroller Data Sheet */

    /* Should probably trim this values */
    const typeof(FLASH.PFCRP0.B) val = {.M0PFE = 1, .M2PFE=1, .APC=3,
                                 .RWSC=3, .WWSC =1, .DPFEN = 0, .IPFEN = 1, .PFLIM =2,
                                 .BFEN  = 1 };
    FLASH.PFCRP0.B = val;

    /* Enable pipelined reads again. */
#elif defined(CFG_MPC5554) || defined(CFG_MPC5567)
    FLASH.BIUCR.R = 0x00104B3D; /* value for up to 128 MHz  */
#elif defined(CFG_MPC5606S)
    CFLASH0.PFCR0.R = 0x10840B6F; /* Instruction prefetch enabled and other according to cookbook */
#elif defined(CFG_MPC563XM)
#if defined(USE_FLS)
    CFLASH0.BIUCR.R = 0x00006b57; /* Prefetch disabled due to flash driver limitations */
#else
    CFLASH0.BIUCR.R = 0x01016b57; /* Prefetch enabled */
#endif
#elif defined(CFG_MPC5644A)
     const typeof(FLASH_A.BIUCR.B) val = { .M6PFE = 0, .M4PFE = 0, .M1PFE = 1, .M0PFE = 1,
                                     .APC = 4, .WWSC = 3, .RWSC = 4, .DPFEN = 0,
                                     .IPFEN = 1, .PFLIM = 2, .BFEN = 1 };

     FLASH_A.BIUCR.B = val;
     ECSM.MUDCR.B.SWSC = 1;       /* One wait-state for RAM@153Mhz */
#elif defined(CFG_MPC560X)
    CFLASH.PFCR0.R =  0x10840B6Fu; /* Instruction prefetch enabled and other according to cookbook */
#elif defined(CFG_MPC5777M)
#if 0
    // this part of the code must be done from RAM and not from flash.
    // using the default settings for now, performance must be optimized later
    // values according to preliminary datasheet for 200MHz(cross bar switch freq) clock freq.
    // Only instruction prefetching, prefetch on buffer miss or next line on hit, master core 0 - 3
    PFLASH.PFCR1.B = (typeof(PFLASH.PFCR1.B)){.P0_M0PFE = 1, .P0_M1PFE = 1, .P0_M2PFE = 1, .APC=2,
                                 .RWSC=5, .P0_DPFEN = 0, .P0_IPFEN = 1, .P0_PFLIM =2,
                                 .P0_BFEN  = 1 };
    PFLASH.PFCR2.B = (typeof(PFLASH.PFCR2.B)){.P1_M0PFE = 1, .P1_M1PFE = 1, .P1_M2PFE = 1,
                                 .P1_DPFEN = 0, .P1_IPFEN = 1, .P1_PFLIM =2,
                                 .P1_BFEN  = 1 };
#endif
#elif defined(CFG_MPC5643L) || defined(CFG_SPC56XL70)
    /*
     * Flash: 3 wait-states @120Mhz
     * SRAM : 1 wait-states @120Mhz
     */
    const FLASH_PFCR0_32B_tag val = {
            .B.B02_APC=3,
            .B.B02_WWSC=3,
            .B.B02_RWSC=3,
            .B.B02_P1_BCFG=3,
            .B.B02_P1_DPFE=0,
            .B.B02_P1_IPFE=1,
            .B.B02_P1_PFLM=2,
            .B.B02_P1_BFE=1,
            .B.B02_P0_BCFG=3,
            .B.B02_P0_DPFE=0,
            .B.B02_P0_IPFE=1,
            .B.B02_P0_PFLM=2,
            .B.B02_P0_BFE=1
 };

 FLASH.PFCR0.R = val.R;

 ECSM.MUDCR.B.MUDC30 = 1;       /* One wait-state for RAM@120Mhz */

#elif defined(CFG_MPC5645S)
     const typeof(CFLASH0.PFCR0.R) val0 = 0x30017B17;
     const typeof(CFLASH0.PFCR1.R) val1 = 0x007C7B43;
     CFLASH0.PFCR0.R = val0;
     CFLASH0.PFCR1.R = val1;
#else
#error No flash setup for this MCU
#endif
    /* Enable Flash ECC reporting */
#if defined(CFG_MPC5744P) || defined(CFG_MPC5777M)
    /* ECC reporting always enabled in MEMU */
#elif defined(CFG_MPC5643L) || defined(CFG_SPC56XL70)

     /* Enabling ECSM.ECR.B.EPFNCR=1 will cause a reset no matter how you
      * try to configure RGM or FCCU. Instead in Freescales infinite
      * wisdom you must now check FLASH.MCR.EER to check for ECC errors.
      */
#else
     /* Enable Flash Non-Correctable error reporting */
     ECSM.ECR.B.EFNCR = 1;
#endif
    /*lint -restore */
}


void Mcu_Arc_WdgExtendTimeout( void ) {

    /*lint -save -e923  Ok, this cast is in Freescale header file */
#if defined(CFG_MPC560X) || defined(CFG_MPC563XM) || defined(CFG_MPC5643L) || defined(CFG_MPC5645S) || defined(CFG_SPC56XL70) || defined(CFG_MPC5644A) || defined(CFG_MPC5668)
#   define WDG_SOFTLOCK_WORD_1   0x0000c520uL
#   define WDG_SOFTLOCK_WORD_2   0x0000d928uL

    /* Disable watchdog. Watchdog is enabled default after reset.*/
    SWT.SR.R = WDG_SOFTLOCK_WORD_1;     /* Write keys to clear soft lock bit */
    SWT.SR.R = WDG_SOFTLOCK_WORD_2;
#if defined(CFG_MPC5644A)
    SWT.MCR.R = 0x8000010Au;     /* Disable watchdog */
#else
    SWT.CR.R = 0x8000010Au;     /* Disable watchdog */
#endif

#if defined(USE_WDG)
#if defined(CFG_MPC5604P)
    SWT.TO.R = 0x7d000u;         /* set the timout to 500ms, , 16khz clock */
#elif defined(CFG_MPC563XM) || defined(CFG_MPC5644A)
    SWT.TO.R = 4000000u;             /* set the timout to 500ms, 8mhz crystal clock */
#elif defined(CFG_MPC5744P) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC5777M) || defined(CFG_MPC5668)
    SWT.TO.R = (uint32)(16000000u*0.5); /* set timeout to 500ms 16MHz IRC clock */
#else
    SWT.TO.R = 0xfa00u;          /* set the timout to 500ms, 128khz clock */
#endif

#if defined(CFG_MPC5644A)
    SWT.MCR.R = 0x8000011Bu;      /* enable watchdog */
#else
    SWT.CR.R = 0x8000011Bu;       /* enable watchdog */
#endif

#endif
#endif
    /*lint -restore */
}

void Mcu_Arc_PlatformInit( void ) {
#if defined(CFG_MPC5643L) || defined(CFG_SPC56XL70)
    /* Masters */
    PBRIDGE.MPROT0_7.R  = 0x77770070u;   /* Enable all */
    PBRIDGE.MPROT8_15.R = 0x77000000u;   /* Enable all */

    /* On platform */
    PBRIDGE.PACR0_7.R = 0u;
    PBRIDGE.PACR8_15.R = 0u;
    PBRIDGE.PACR16_23.R = 0u;
    /* Off platform */
    PBRIDGE.OPACR0_7.R = 0u;
    PBRIDGE.OPACR16_23.R = 0u;
    PBRIDGE.OPACR24_31.R = 0u;
    PBRIDGE.OPACR32_39.R = 0u;
    PBRIDGE.OPACR40_47.R = 0u;
    PBRIDGE.OPACR48_55.R = 0u;
    PBRIDGE.OPACR56_63.R = 0u;
    PBRIDGE.OPACR64_71.R = 0u;
    PBRIDGE.OPACR80_87.R = 0u;
    PBRIDGE.OPACR88_95.R = 0u;

#endif
#if defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC560X) || defined(CFG_MPC5744P)
    /* Debug..... */
    SSCM.ERROR.B.PAE = 1u;
    SSCM.ERROR.B.RAE = 1u;
#endif

}
