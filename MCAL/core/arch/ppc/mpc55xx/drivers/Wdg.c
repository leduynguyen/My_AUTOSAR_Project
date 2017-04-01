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
/** @tagSettings DEFAULT_ARCHITECTURE=PPC|MPC5607B|MPC5645S|MPC5748G */

/*
 * Implementation Notes:
 *   MPC5516
 *     SWT: driven by SIU_SYSCLK.SWTCLKSEL (here System Clock, can be 16Mhz IRC)
 *      - SWTCR.SE=1. Enabled by default. Override with RCHW.
 *      - RCHW (WTE bit, 0-disabled, 1-enabled) (This area is read by BAM)
 *     OnChip
 *      - BookE, disabled by default.  SPR_TCR.WRC!=0 enables watchdog
 */

#include "Wdg.h"
#include "Mcu.h"
#include "mpc55xx.h"
#include "SchM_Wdg.h"

#if  defined(CFG_MPC5668)
#include "io.h"   /* Need for WRITEXX, READXX macros */
#endif

#if ( WDG_DEV_ERROR_DETECT == STD_ON )
#include "Det.h"
#endif

/* @req SWS_WDG_00105 Imported types (DEM types not applicable)*/
/* @req SWS_Wdg_00161 Shall access registers directly */
/* @req SWS_WDG_00171 Configuration structure  */
/* @req SWS_Wdg_00031 No deinit is allowed */
/* @req SWS_Wdg_00051 Generator/tool*/

#if defined(CFG_MPC5668)
#define SWT_BASE			0xFFF38000
#define SWT_CR				0x0
#define SWT_TO				0x8
#define SWT_SR				0x10

#define CR_RIA				0x100
#define CR_SLK				0x10
#define CR_CSL				0x8
#define CR_FRZ				0x2
#define CR_WEN				0x1
#endif

#if defined(CFG_MPC5777M)
#define SWT SWT_0
#endif


#if defined(CFG_MPC5744P) || defined(CFG_MPC5748G) || defined(CFG_MPC5746C) || defined(CFG_MPC5645S) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC560X) || \
    defined(CFG_MPC5777M) || defined(CFG_MPC5644A) || defined(CFG_MPC5668) || defined(CFG_MPC563XM) || defined(CFG_MPC5747C)
/* Two words needs to be written to the SR register in the correct order to open the soft lock.
 * These two words are defined here:
 */
#define SOFTLOCK_WORD_1   0x0000c520uL
#define SOFTLOCK_WORD_2   0x0000d928uL
#endif

#if defined(CFG_MPC5567)
typedef union {
    uint32 R;				/*lint !e754 field type is unsigned int so ok. R IS referenced... */
    struct {
        uint32 WP:2;			/*lint !e46 !e754 field type is unsigned int so ok. We don't reference these bits but we want them visible. */
        uint32 WRC:2;			/*lint !e46field type is unsigned int so ok.  */
        uint32 WIE:1;			/*lint !e46field type is unsigned int so ok.  */
        uint32 DIE:1;			/*lint !e46 !e754 field type is unsigned int so ok. We don't reference these bits but we want them visible. */
        uint32 FP:2;			/*lint !e46 !e754 field type is unsigned int so ok. We don't reference these bits but we want them visible. */
        uint32 FIE:1;			/*lint !e46 !e754 field type is unsigned int so ok. We don't reference these bits but we want them visible. */
        uint32 ARE:1;			/*lint !e46 !e754 field type is unsigned int so ok. We don't reference these bits but we want them visible. */
        uint32 RESERVED1:1;		/*lint !e46 !e754 field type is unsigned int so ok. We don't reference these bits but we want them visible. */
        uint32 WPEXT:4;			/*lint !e46field type is unsigned int so ok.  */
        uint32 FPEXT:4;			/*lint !e46 !e754 field type is unsigned int so ok. We don't reference these bits but we want them visible. */
        uint32 RESERVED2:13;	/*lint !e46 !e754 field type is unsigned int so ok. We don't reference these bits but we want them visible. */
    } B;
} SPR_TCR_type;
#endif

/* @req SWS_Wdg_00154 Internal watchdog mod shall be available for debugging */
/* @req SWS_Wdg_00152 configWdgPtr = NULL -> unitialized. Busy not suppported  */
typedef struct {
    const Wdg_ConfigType *configWdgPtr;
    WdgIf_ModeType mode;
} runTimeDataType;

static runTimeDataType runTimeData = { .configWdgPtr = NULL, .mode = WDGIF_OFF_MODE };

#if defined(CFG_MPC5516)
#define SWTCR_SWRI(_x) ((_x)<<5)
#define SWTCR_SWT(_x) 	(_x)
#define SWTCR_SWE 		(1<<7)
#endif


#if ( WDG_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(WDG_MODULE_ID,0,_api,_err); \
          return; \
        }

#define VALIDATE_RV(_exp,_api,_err, _rv ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(WDG_MODULE_ID,0,_api,_err); \
          return _rv; \
        }
#define REPORT_DET_ERROR(_api,_err) (void)Det_ReportError(WDG_MODULE_ID,0,_api,_err)

#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_RV(_exp,_api,_err,_rv )
#define REPORT_DET_ERROR(_api,_err)
#endif

/**
 * Starts the watchdog
 * @param timeout - is in either ms or ticks
 */
static void StartWatchdog(uint32 timeout)
{
    /*lint -save -e923 Ok, that casting is done in Freescale header file  */
#if defined(CFG_MPC5567)	
    /* Calculating what to set WP and WPEXT to get close to the supplied timeout value
     * This is very similar to the calculation for 5516 (see comment further down).
     * timeout = 1/f_clk * 2^x Where X is the value we want. So,
     * x = log2(f_clk*timeout)*/
    uint32 swtVal = ilog2( (Mcu_Arc_GetSystemClock()/1000) * timeout ); /* Timeout in ms */

    /*The value to write in the TCR register is 64-x (see Application Note AN2817)*/
    swtVal = 64uL-swtVal;

    SPR_TCR_type myTCR = (SPR_TCR_type)get_spr(SPR_TCR);

    myTCR.B.WP = 	swtVal & 0x00000003uL;	/* Set timeout period. (see Application Note AN2817) */
    myTCR.B.WPEXT = (swtVal>>2uL) & 0x0000000FuL; /* The timeout is split into to bitfields */
    myTCR.B.WRC = 	1uL;	/* Do a reset when detecting the second timeout event*/
    myTCR.B.WIE = 	0;		/* No watchdog interrupts */

    set_spr(SPR_TCR, (uint32)(myTCR.R));

#elif defined(CFG_MPC563XM)
    SWT.TO.R = timeout;/* Timeout in ticks */
    SWT.CR.R = 0x8000011BuL;
#elif defined(CFG_MPC5777M)
    SWT.CR.R = 0xE000011BuL; /* Access for all cores */
#elif defined(CFG_MPC5644A)
    SWT.TO.R = timeout;/* Timeout in ticks */
    SWT.MCR.R = 0x8000011BuL;
#elif defined(CFG_MPC5744P) || defined(CFG_MPC5645S) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC560X) || defined(CFG_MPC5748G) || defined(CFG_MPC5746C) || defined(CFG_MPC5747C)
    /* Clear soft lock */
    SWT.SR.R = SOFTLOCK_WORD_1;     /* Write keys to clear soft lock bit */
    SWT.SR.R = SOFTLOCK_WORD_2;
#if defined(CFG_MPC5645S) || defined(CFG_MPC560X) || defined(CFG_MPC5748G) || defined (CFG_MPC5746C) || defined(CFG_MPC5747C)
    /* Clocked by 128 kHz IRC clock */
    SWT.TO.R = timeout * 128u; /* Timeout in ms */
#else
    /* Clocked by 16 MHz IRC clock */
    SWT.TO.R = timeout * 16000u; /* Timeout in ms */
#endif
    /* Enable Watchdog */

    /*lint -e{970} -e{26} -e{10} -e{64} Lint does not seem handle typeof well */
    SWT.CR.B = (typeof(SWT.CR.B)){.RIA = 1, .SLK = 1, .FRZ = 1, .WEN = 1, .MAP0 = 1};
#elif defined(CFG_MPC5668)
    /* Clocked by 16 MHz IRC clock */

    /* Clear softlock */
    WRITE32(SWT_BASE + SWT_SR, SOFTLOCK_WORD_1);
    WRITE32(SWT_BASE + SWT_SR, SOFTLOCK_WORD_2);

    /* Write TMO */
    WRITE32(SWT_BASE + SWT_TO, timeout * 16000 ); /* Timeout in ms */

    /* Enable Watchdog */
    WRITE32(SWT_BASE + SWT_CR,0x80000000UL + CR_RIA + CR_SLK + CR_CSL + CR_FRZ + CR_WEN);

#elif defined(CFG_MPC5516)
    /* We running on system clock, ie SIU_SYSCLK.SWTCLKSEL,  so get the value */

    /* The timeout is 2^x, so get best possible value
     *   Table for 80Mhz
     *   ------------------
     *   2^9  = 512 = 6.4 uS
     *   2^15 =       400 uS
     *   2^20 =       13 mS
     *   2^28 =       3.3 S
     *   2^31 =       26,84 S
     *
     * Formula:
     *   1/clock * 2^n  = tmo_in_s
     *   2^n = tmo_in_s * clock -> n = log2(tmo_in_s * clock) = log2(tmo_in_ms * clock / 1000 )
     *  */
    uint32 swtVal = ilog2( Mcu_Arc_GetSystemClock()/1000 * timeout ); /* Timeout in ms */
#if defined(CFG_WDG_TEST)
    MCM.SWTCR.R = (SWTCR_SWE + SWTCR_SWRI(WDG_SWRI_VAL) + swtVal);
#else
    MCM.SWTCR.R = (SWTCR_SWE + SWTCR_SWRI(2) + swtVal);
#endif

#else
    MCM.SWTCR.R = 0x00D8u;
#endif
    /*lint -restore */
}


/**
 * Stops the watchdog
 */
static void StopWatchdog(void)
{
    /*lint -save -e923 Ok, the casting is done in Freesacale header file  */
#if defined(CFG_MPC5567)
    /* Can't be shut off when it has been enabled */
#elif defined(CFG_MPC560X) || defined(CFG_MPC5668) || defined(CFG_MPC563XM) || defined(CFG_MPC5744P) || defined(CFG_MPC5645S) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC5748G) || defined(CFG_MPC5746C) || defined(CFG_MPC5747C)
     SWT.SR.R = SOFTLOCK_WORD_1;     /* Write keys to clear soft lock bit */
     SWT.SR.R = SOFTLOCK_WORD_2;
     /*lint -e{970} -e{26} -e{10} -e{64} Lint does not seem handle typeof well */
     SWT.CR.B = (typeof(SWT.CR.B)){.RIA = 1, .FRZ = 1, .WEN = 0, .MAP0 = 1};
#elif defined(CFG_MPC5777M)
    SWT.SR.R = SOFTLOCK_WORD_1;     /* Write keys to clear soft lock bit */
    SWT.SR.R = SOFTLOCK_WORD_2;
    SWT.CR.R = 0xE000010AuL; /* Access for all cores */
#elif defined(CFG_MPC5644A)
    SWT.SR.R = SOFTLOCK_WORD_1;     /* Write keys to clear soft lock bit */
    SWT.SR.R = SOFTLOCK_WORD_2;
    SWT.MCR.B = (typeof(SWT.MCR.B)){.RIA = 1, .FRZ = 1, .WEN = 0, .MAP0 = 1};

#elif defined(CFG_MPC5516)
     MCM.SWTCR.R = 0x0u;	  /* Disable the watchdog */
#else
    MCM.SWTCR.R = 0x0059u;
#endif
    /*lint -restore */
}


#if (WDG_VERSION_INFO_API == STD_ON)
void Wdg_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    /* @req SWS_Wdg_00174 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE(versioninfo != NULL, WDG_GET_VERSION_INFO_SERVICE_ID, WDG_E_PARAM_POINTER);

    versioninfo->vendorID = WDG_VENDOR_ID;
    versioninfo->moduleID = WDG_MODULE_ID;
    versioninfo->sw_major_version = WDG_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = WDG_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = WDG_SW_PATCH_VERSION;
}
#endif


void Wdg_Init (const Wdg_ConfigType* ConfigPtr)
{
    /* @req SWS_Wdg_00001 */
    /* @req SWS_Wdg_00100 */
    /* @req SWS_Wdg_00101 */

    /*@req SWS_Wdg_00089 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE(ConfigPtr != NULL, WDG_INIT_SERVICE_ID, WDG_E_PARAM_POINTER);

    /* @req SWS_Wdg_00010 */
    VALIDATE(runTimeData.configWdgPtr == NULL, WDG_INIT_SERVICE_ID, WDG_E_DRIVER_STATE);
    /*lint -restore */

    /* Keep a pointer to the config. */
    /* @req SWS_Wdg_00019 Always set regardless of DET or debugging support */
    runTimeData.configWdgPtr = ConfigPtr;

    /* Ignoring return value, DET error set in Wdg_SetMode */
    (void)Wdg_SetMode(ConfigPtr->Wdg_ModeConfig->Wdg_DefaultMode);
}


Std_ReturnType Wdg_SetMode (WdgIf_ModeType Mode)
{
    /* @req SWS_Wdg_00160 */
    static const Wdg_SettingsType *modeWdgConfig;
    Std_ReturnType res = E_NOT_OK;

    /* @req SWS_Wdg_00017 */
    /* @req SWS_Wdg_00010 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_RV(runTimeData.configWdgPtr != NULL, WDG_SET_MODE_SERVICE_ID, WDG_E_DRIVER_STATE, E_NOT_OK);

    switch (Mode)
    {
    case WDGIF_OFF_MODE:
        modeWdgConfig = &(runTimeData.configWdgPtr->Wdg_ModeConfig->WdgSettingsOff);
        break;
    case WDGIF_FAST_MODE:
        modeWdgConfig = &(runTimeData.configWdgPtr->Wdg_ModeConfig->WdgSettingsFast);
        break;
    case WDGIF_SLOW_MODE:
        modeWdgConfig = &(runTimeData.configWdgPtr->Wdg_ModeConfig->WdgSettingsSlow);
        break;
    default:
        /* @req SWS_Wdg_00091 */
        REPORT_DET_ERROR(WDG_SET_MODE_SERVICE_ID, WDG_E_PARAM_MODE);
        modeWdgConfig = NULL;
        break;
    }

    if (modeWdgConfig != NULL)
    {
        /* Enable watchdog if config tell us to.. */
        if (modeWdgConfig->ActivationBit != 0u)
        {
#if defined(CFG_MPC560X) || defined(CFG_MPC563XM) || defined(CFG_MPC5744P) || defined(CFG_MPC5645S) || defined(CFG_MPC5644A) || defined(CFG_MPC5777M) || defined(CFG_MPC5748G) || defined(CFG_MPC5746C) || defined(CFG_MPC5747C)
          StopWatchdog(); // must be stopped in order to change TO
#endif
            /* @req SWS_Wdg_00145*/
            StartWatchdog(modeWdgConfig->ReloadValue);
        }
        else
        {
            StopWatchdog();
        }

        /* Set internal mode for debugging and test */
        runTimeData.mode = Mode;

        res = E_OK;
    }

    /* @req SWS_Wdg_00103 */
    return res;
}


void Wdg_SetTriggerCondition (uint16 timeout)
{
    /* This is not SWS_Wdg_00140 but 0 is supported and will not reset the watchdog
     * meaning that it will take some time until the watchdog expires
     */
    if (timeout == 0) {
        /*lint -e{904} ARGUMENT_CHECK */
        return;
    }

    SchM_Enter_Wdg_EA_0();

    /* @req SWS_Wdg_00093 Configured for fixed activation code */

    /*lint -save -e923 Ok, the casting is done in Freesacale header file  */
#if defined(CFG_MPC5567)
    uint32 myTSR = get_spr(SPR_TSR);
    set_spr(SPR_TSR, (myTSR | 0x40000000uL));
#elif defined(CFG_MPC560X) || defined(CFG_MPC563XM) || defined(CFG_MPC5668) || defined(CFG_MPC5744P) || defined(CFG_MPC5645S) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC5644A) || defined(CFG_MPC5777M) || defined(CFG_MPC5748G) || defined(CFG_MPC5746C) || defined(CFG_MPC5747C)
    SWT.SR.R = 0x0000A602;
    SWT.SR.R = 0x0000B480;
#elif defined(CFG_MPC5516)
    MCM.SWTSR.R = 0x55;
    MCM.SWTSR.R = 0xAA;
#else
    MCM.SWTSR.R = 0x55;
    MCM.SWTSR.R = 0xAA;
#endif
    /*lint -restore */

    SchM_Exit_Wdg_EA_0();
} /*lint !e438 !e529 The myTSR IS used*/

#if defined(HOST_TEST)
/*lint -save -e957 Delibrately without protoype, used in test */
WdgIf_ModeType  Wdg_Arc_GetMode(void) {
    return runTimeData.mode;
}

boolean Wdg_Arc_IsInitialized(void) {
    return (runTimeData.configWdgPtr != NULL) ? TRUE : FALSE;
}

void Wdg_Arc_StopWatchdog(void) {
    StopWatchdog();
}
/*lint -restore */
#endif

