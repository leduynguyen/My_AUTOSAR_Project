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
/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ */

/* General Wdg module requirements */
/* @req SWS_Wdg_00086 */
/* @req SWS_Wdg_00031 */
/* @req SWS_Wdg_00161 */
/* @req SWS_Wdg_00093 */
/* @req SWS_Wdg_00105 */
/* @req SWS_Wdg_00157 */
/* @req SWS_Wdg_00158 */
/* @req SWS_Wdg_00159 */

/*lint -save -e9003 Misra 2012 8.9 Blockscope variables definitions neglected.
 * Static variable declaration in Function body violates the AUTOSAR memory mapping concept.*/


#include "Wdg.h"
#include "zynq.h"
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
#include "isr.h"
#include "irq_zynq.h"
#endif
#include "Os.h"

#if defined(USE_DET)
#include "Det.h"
#endif
#if (WDG_DEV_ERROR_DETECT)
#define VALIDATE(_exp,_api,_err ) \
        /*lint -save -e506 -e774*/ \
        if( !(_exp) ) { \
          (void)Det_ReportError(WDG_MODULE_ID,0,_api,_err); \
          return; /*lint -restore*/\
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

typedef enum {
    WDG_UNINIT = 0u,
    WDG_IDLE,
    WDG_BUSY
}WdgInternalState;

enum  {
    PRESCALER_8    = 8u,
    PRESCALER_64   = 64u,
    PRESCALER_512  = 512u,
    PRESCALER_4096 = 4096u
}PrescalerSelectType;

static const uint16 PrescalerSelect[4]= {PRESCALER_8, PRESCALER_64, PRESCALER_512, PRESCALER_4096}; /*lint !e641 Converting enum*/

/* @req SWS_Wdg_00152 */
/* @req SWS_Wdg_00154 */
WdgInternalState wdgState = WDG_UNINIT;


/* swdt mode */
#define WDG_ZERO_ACCESS_KEY     ((uint32)0xABCu << 12u)
#define WDG_ZKEY_ACCESS_MASK    (0xFFFu)
#define WDG_IRQLN_4CLK          0u
#define WDG_IRQLN_8CLK          1u
#define WDG_IRQLN_16CLK         2u
#define WDG_IRQLN_32CLK         3u
#define WDG_IRQLN               ((uint32)WDG_IRQLN_32CLK << 7u) //Interrupt request length set to 32 pclk cycles
#define WDG_IRQ_ENABLE          ((uint32)1u << 2u) //Interrupt when counter reaches zero
#define WDG_IRQ_DISABLE         (~WDG_IRQ_ENABLE)
#define WDG_RST_ENABLE          ((uint32)1u << 1u) //Reset enable when counter reaches zero
#define WDG_RST_DISABLE         (~WDG_RST_ENABLE)
#define WDG_ENABLE              (1u)    //WDG enable
#define WDG_DISABLE             (~WDG_ENABLE)
/* counter control */
#define WDG_COUNTER_ACCESS_KEY      ((uint32)0x248u << 14u)
#define WDG_COUNTER_ACCESS_MASK     (0x3FFFu)
#define WDG_CLK_PRESCALER_8         0u
#define WDG_CLK_PRESCALER_64        1u
#define WDG_CLK_PRESCALER_512       2u
#define WDG_CLK_PRESCALER_4096      3u
/* restart */
#define WDG_RESTART_KEY         0x1999u
/* swdt status*/
#define WDG_WDZ                 0xFFFFFFFEu
/* counter maximum value */
#define WDG_COUNTER_MAXIMUM     0xFFFFFFu
/* counter reload value mask */
#define WDG_COUNTER_RELOAD_MASK 0xFFF000u
#define WDG_INVERTED_COUNTER_RELOAD_MASK ((uint32)~WDG_COUNTER_RELOAD_MASK)
/* Interrupt priority */
#define WDG_INTERRUPT_PRIORITY  2u

const Wdg_ConfigType* WdgConfigPtr = NULL;

/* Set SFR registers of Wdg properly.*/
typedef volatile struct SWDT_reg Wdg_SwdtHwRegType;
/*lint -e{923} cast from unsigned int to pointer MISRA 2004 11.1 11.3 2012 11.4 11.6
 * Integer to pointer casting is necessary to set SFR of Microcontroller. */
static Wdg_SwdtHwRegType* const SWDT_PTR = (Wdg_SwdtHwRegType*)ZYNQ_SWDT_BASE;

ISR(Wdg_Isr);

ISR(Wdg_Isr) {

    if ((0u != SWDT_PTR->status) && (NULL != WdgConfigPtr->Wdg_Notification)){
        /* Call notification */
        WdgConfigPtr->Wdg_Notification();
    }
}


static inline uint32 calcCounterVal(uint16 timeout, uint8 *wdgPrescSetting, boolean *Overflow) {

    uint32 ret = 0;
    uint8 prescale = WDG_CLK_PRESCALER_8;

    for (; prescale <=  WDG_CLK_PRESCALER_4096; prescale++) {
       /*lint -e{9033} -e{9032}
        * Impermissible cast of composite expression (different essential type categories) Misra 2012 10.8
        * Composite expression with smaller essential type than other operand Misra 2012 10.7 */
       ret = (uint32) (timeout  * ((uint64)MCU_ARC_CLOCK_ARM_CPU_1X_FREQUENCY / (uint32)( PrescalerSelect[prescale] *1000)));
       if (ret <= WDG_COUNTER_MAXIMUM) {
           *wdgPrescSetting  = prescale;
           *Overflow = FALSE;
           break; //Found the counter prescale
       }
    }
    if (prescale > WDG_CLK_PRESCALER_4096) {
        *Overflow = TRUE;
    }

    return ret;

}


static inline Std_ReturnType setMode(WdgIf_ModeType mode) {

    uint8 wdgPrescale=0;
    uint32 counterReloadVal = 0;
    boolean ovf  = FALSE;

    if(WDGIF_SLOW_MODE == mode) {
        /*lint -e{934} Taking address of near auto variable Misra 2004 1.2 2012 1.3 Using stack pointer as argument is tolerable.*/
        counterReloadVal = calcCounterVal(WdgConfigPtr->Wdg_ModeConfig->WdgSettingsSlow, &wdgPrescale, &ovf);
    } else if(WDGIF_FAST_MODE == mode) {
        /*lint -e{934} Taking address of near auto variable Misra 2004 1.2 2012 1.3 Using stack pointer as argument is tolerable.*/
        counterReloadVal = calcCounterVal(WdgConfigPtr->Wdg_ModeConfig->WdgSettingsFast, &wdgPrescale, &ovf);
    } else {
        ;/*do nothing*/
    }

    if (ovf == FALSE) {
#if defined(CFG_WDG_ROUND_CRV_TO_NEAREST)
        if(  ((counterReloadVal & WDG_INVERTED_COUNTER_RELOAD_MASK) < (WDG_INVERTED_COUNTER_RELOAD_MASK / 2)) &&
                (0 != (counterReloadVal & (uint32)WDG_COUNTER_RELOAD_MASK)) ) {
            /* Since we cannot use the lower 3 bytes (these will be 0xFFF, see Register CONTROL Details in appendix B),
             * round downwards if closer to 0xXY(Z-1)FFF than to 0xXYZFFF*/
            uint32 crvTemp = ((counterReloadVal & (uint32)WDG_COUNTER_RELOAD_MASK) >> 12u) - 1u;
            counterReloadVal = (crvTemp<<12);

        }
#endif
        SWDT_PTR->mode  = ((SWDT_PTR->mode & (uint32)WDG_ZKEY_ACCESS_MASK) | (uint32)WDG_ZERO_ACCESS_KEY)  & (uint32)WDG_DISABLE; //Disable watchdog

        /* Set prescale and Counter reload value */
        SWDT_PTR->control =   ((WDG_COUNTER_ACCESS_KEY) | ((counterReloadVal & (uint32)WDG_COUNTER_RELOAD_MASK) >> 10u) | wdgPrescale );

        /* Restart watch dog */
        SWDT_PTR->mode = ((SWDT_PTR->mode & (uint32)WDG_ZKEY_ACCESS_MASK) | (uint32)WDG_ZERO_ACCESS_KEY) | (uint32)WDG_ENABLE;//Enable watchdog
        SWDT_PTR->restart = WDG_RESTART_KEY;
        return E_OK;
    } else {
        return E_NOT_OK;
    }



}

/* @req SWS_Wdg_00106 */
void Wdg_Init(const Wdg_ConfigType* ConfigPtr) {

    Std_ReturnType ret;

    /* @req SWS_Wdg_00089 */
    VALIDATE((NULL != ConfigPtr), WDG_INIT_SERVICE_ID, WDG_E_PARAM_POINTER);
    /* @req SWS_Wdg_00090 */
    VALIDATE((0 != ConfigPtr->Wdg_ModeConfig->WdgSettingsFast)&& (0 != ConfigPtr->Wdg_ModeConfig->WdgSettingsSlow), WDG_INIT_SERVICE_ID, WDG_E_PARAM_CONFIG);

    WdgConfigPtr = ConfigPtr;

    SWDT_PTR->mode      = ((SWDT_PTR->mode & (uint32)WDG_ZKEY_ACCESS_MASK) | (uint32)WDG_ZERO_ACCESS_KEY) &  (uint32)WDG_DISABLE; //Disable watchdog

    if (WdgConfigPtr->Wdg_ResetEnable == TRUE) {
        SWDT_PTR->mode  = ((SWDT_PTR->mode & (uint32)WDG_ZKEY_ACCESS_MASK) | (uint32)WDG_ZERO_ACCESS_KEY) | (uint32)WDG_RST_ENABLE ; // Reset enable
    } else {
        SWDT_PTR->mode  = ((SWDT_PTR->mode & (uint32)WDG_ZKEY_ACCESS_MASK) | (uint32)WDG_ZERO_ACCESS_KEY) & (uint32)WDG_RST_DISABLE;
    }

    SWDT_PTR->mode  = ((SWDT_PTR->mode & (uint32)WDG_ZKEY_ACCESS_MASK) | (uint32)WDG_ZERO_ACCESS_KEY) | (uint32)WDG_IRQ_ENABLE; //Set Interrupt
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
    /* Install interrupt */
    ISR_INSTALL_ISR2("WdgIsr", Wdg_Isr, (IrqType)(IRQ_SWDT), WDG_INTERRUPT_PRIORITY, 0);
#endif

    /* @req SWS_Wdg_00001 */
    /* @req SWS_Wdg_00100 */
    /* @req SWS_Wdg_00101 */

    if(WDGIF_OFF_MODE == WdgConfigPtr->Wdg_ModeConfig->Wdg_DefaultMode) {
        /* @req SWS_Wdg_00019 */
        wdgState = WDG_IDLE;

        return;
    }

    ret = setMode(WdgConfigPtr->Wdg_ModeConfig->Wdg_DefaultMode);

    if (E_OK == ret) {
        /* @req SWS_Wdg_00019 */
        wdgState = WDG_IDLE;
        return;

    } else {
        /* @req SWS_Wdg_00090 */
        VALIDATE((FALSE), WDG_INIT_SERVICE_ID, WDG_E_PARAM_CONFIG);
    }

}


/* @req SWS_Wdg_00107 */
Std_ReturnType Wdg_SetMode( WdgIf_ModeType Mode ) {

    /* @req SWS_Wdg_00017 */
    /* @req SWS_Wdg_00035 */
    VALIDATE_RV((WDG_IDLE == wdgState), WDG_SET_MODE_SERVICE_ID, WDG_E_DRIVER_STATE, E_NOT_OK);

    /* @req SWS_Wdg_00091 */
    VALIDATE_RV(((WDGIF_OFF_MODE == Mode) || (WDGIF_FAST_MODE == Mode) || (WDGIF_SLOW_MODE == Mode)), WDG_SET_MODE_SERVICE_ID, WDG_E_PARAM_MODE, E_NOT_OK);
    /* @req SWS_Wdg_00092 */
    VALIDATE_RV((0 != WdgConfigPtr->Wdg_ModeConfig->WdgSettingsFast)&& (0 != WdgConfigPtr->Wdg_ModeConfig->WdgSettingsSlow), WDG_SET_MODE_SERVICE_ID, WDG_E_PARAM_MODE, E_NOT_OK);

    /* @req SWS_Wdg_00052 */
    wdgState = WDG_BUSY;

    /* @req SWS_Wdg_00160 */

    /* @req SWS_Wdg_00051 */
    /* @req SWS_Wdg_00145 */
    SWDT_PTR->mode      = ((SWDT_PTR->mode & (uint32)WDG_ZKEY_ACCESS_MASK) | (uint32)WDG_ZERO_ACCESS_KEY) &  (uint32)WDG_DISABLE; //Disable watchdog

    if(WDGIF_OFF_MODE != Mode) {
        if (E_NOT_OK == setMode(Mode)) {

            /* @req SWS_Wdg_00018 */
            wdgState = WDG_IDLE;
            /* @req SWS_Wdg_00092 */
            /*lint -save -e506 -e774*/
            VALIDATE_RV((FALSE), WDG_SET_MODE_SERVICE_ID, WDG_E_PARAM_MODE,E_NOT_OK);
            /*lint -restore */
        }
    }

    /* @req SWS_Wdg_00018 */
    wdgState = WDG_IDLE;
    /* @req SWS_Wdg_00103 */
    return E_OK;
}

/* @req SWS_Wdg_00155 */
void Wdg_SetTriggerCondition( uint16 timeout ) {


    uint8 wdgPrescale=0;
    uint32 counterReloadVal;
    boolean ovf  = FALSE;

    /* @req SWS_Wdg_00035 */
    VALIDATE((WDG_IDLE == wdgState), WDG_SET_TRIGGERING_CONDITION_SERVICE_ID, WDG_E_DRIVER_STATE);

    if (timeout == 0) {
        return;
    }

    /* @req SWS_Wdg_00052 */
    wdgState = WDG_BUSY;


    /* @req SWS_Wdg_00138 */
    /*lint -e{934} Taking address of near auto variable Misra 2004 1.2 2012 1.3 Using stack pointer as argument is tolerable.*/
    counterReloadVal  = calcCounterVal(timeout, &wdgPrescale, &ovf);

    /* @req SWS_Wdg_00146 */
    VALIDATE(!ovf, WDG_SET_TRIGGERING_CONDITION_SERVICE_ID, WDG_E_PARAM_TIMEOUT);

    /* @req SWS_Wdg_00140 */
    /* @req SWS_Wdg_00136 */
    /* Set prescale and Counter reload value */
    SWDT_PTR->control = (( WDG_COUNTER_ACCESS_KEY) | ((counterReloadVal & (uint32)WDG_COUNTER_RELOAD_MASK) >> 10u) |wdgPrescale );

    /* Restart watch dog */
    SWDT_PTR->restart = WDG_RESTART_KEY;

    wdgState = WDG_IDLE;

}

#if (STD_ON == WDG_VERSION_INFO_API)
/* @req SWS_Wdg_00109 */
void Wdg_GetVersionInfo( Std_VersionInfoType* versioninfo )
{
    /* @req SWS_Wdg_00174 */
    VALIDATE((NULL != versioninfo), WDG_GET_VERSION_INFO_SERVICE_ID,WDG_E_PARAM_POINTER);
    versioninfo->vendorID = WDG_VENDOR_ID;
    versioninfo->moduleID = WDG_MODULE_ID;
    versioninfo->sw_major_version = WDG_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = WDG_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = WDG_SW_PATCH_VERSION;
}

#endif
