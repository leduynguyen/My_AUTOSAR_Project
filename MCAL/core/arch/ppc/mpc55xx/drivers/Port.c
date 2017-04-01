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

/** @tagSettings DEFAULT_ARCHITECTURE=PPC|MPC5607B|MPC5645S|MPC5748G|MPC5747C */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/* General Port module requirements */
/** @req SWS_Port_00004 Port shall be able to configure each port and pin */
/** @req SWS_Port_00079 Port shall provide direction, init value, changable dir and mode */

/** @req SWS_Port_00081 Port shall provide optional configuration of slew rate, pull up, open drain and read back. Not supporting pin levels */

/** @req SWS_Port_00082 No inversion support */
/** @req SWS_Port_00013 Symbolic names */
/** @req SWS_Port_00073 Port_Config type shall define configuration data */
/** @req SWS_Port_00006 Symbolic names - implemented in the generator/tool */
/** @req SWS_Port_00207 Symbolic names - implemented in the generator/tool */
/** @req SWS_Port_00076 Symbolic names - implemented in the generator/tool */
/** @req SWS_Port_00075 Atomic access */
/** @req SWS_Port_00129 Types used when applicable, Dem types is not needed since Dem is not used by Port */
/** @req SWS_Port_00087 Det errors.  PORT_E_INVALID_MODE is not supported */
/** @req SWS_Port_00072 Implemented in the generator/tool */
/** @req SWS_Port_00204 Not including Port_Cbk.c or Dem.h since not needed */

#include "Port.h"
#include "mpc55xx.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "SchM_Port.h"

typedef enum {
    PORT_UNINITIALIZED = 0, //!< PORT_UNINITIALIZED
    PORT_INITIALIZED,      //!< PORT_INITIALIZED
} Port_StateType;

static Port_StateType Port_state = PORT_UNINITIALIZED;
static const Port_ConfigType * Port_configPtr = &PortConfigData;

#if (PORT_DEV_ERROR_DETECT)
#define VALIDATE_PARAM_CONFIG(_ptr,_api) \
    if( (_ptr)==((void *)0) ) { \
        (void)Det_ReportError(PORT_MODULE_ID, 0, _api, PORT_E_PARAM_CONFIG ); \
        return; \
    }

#define VALIDATE_STATE_INIT(_api)\
    if(PORT_INITIALIZED!=Port_state){\
        (void)Det_ReportError(PORT_MODULE_ID, 0, _api, PORT_E_UNINIT ); \
        return; \
    }

#define VALIDATE_PARAM_PIN(_pin, _api)\
    if(_pin>=PORT_NOF_PINS){\
        (void)Det_ReportError(PORT_MODULE_ID, 0, _api, PORT_E_PARAM_PIN ); \
        return; \
    }

#define VALIDATE_PARAM_POINTER(_pointer, _api)\
    if(_pointer == ((void *)0) ) {\
        (void)Det_ReportError(PORT_MODULE_ID, 0, _api, PORT_E_PARAM_POINTER ); \
        return; \
    }

#define VALIDATE(_expression, _api, _err)\
    if(!(_expression)) {\
        (void)Det_ReportError(PORT_MODULE_ID, 0, _api, _err ); \
        return; \
    }

#else
#define VALIDATE_PARAM_CONFIG(_ptr,_api)
#define VALIDATE_STATE_INIT(_api)
#define VALIDATE_PARAM_PIN(_pin, _api)
#define VALIDATE_PARAM_POINTER(_pointer)
#define VALIDATE(_expression, _api, _err)
#endif
#if defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
#define ADDRESS_OFFSET_IMCR_TO_MSCR     512 /* &SIU.PMSI[0]- &SIU.PCR[0]/sizeof(SIU.PCR[0]) */
#endif


void Port_Init(const Port_ConfigType *configType) {

    /** @req SWS_Port_00001 */
    /** @req SWS_Port_00043 */
    /** @req SWS_Port_00214 All I/O registers are initialized by port */
    /** @req SWS_Port_00215 */
    /** @req SWS_Port_00217 Only I/O registers are initialized by port */
    /** @req SWS_Port_00218 Only I/O registers are initialized by port */
    /** @req SWS_Port_00042 */
    /** @req SWS_Port_00041 */
    /** !req SWS_Port_00005 Only pins in the configuration is set*/

    /* @req SWS_Port_00105 Always checking the parameter */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_PARAM_CONFIG(configType, PORT_INIT_ID);

    /* Copy config to register areas */
    /* @req SWS_Port_00055 */
    for (uint32 i = 0; configType->outConfig[i].reg != PORT_INVALID_REG; i++) {
        /*lint -e{923} Ok, this cast is in the Freescale header file */
        SIU.GPDO[configType->outConfig[i].reg].R = configType->outConfig[i].config;
    }
#if defined(CFG_MPC5744P) || defined(CFG_MPC560X) || defined(CFG_MPC5645S) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC5777M) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
    for(uint32 i = 0; configType->inputSelectConfig[i].reg != PORT_INVALID_REG; i++) {
        /* IMCR register must be written as a 32bit integer, see reference manual for e.g. mpc5744P */
#if defined(CFG_MPC5777M)
        uint32 offset = sizeof(SIU.PCR)/sizeof(SIU.PCR[0]);
        SIU.PSMI[configType->inputSelectConfig[i].reg - offset].R = (uint32)configType->inputSelectConfig[i].config;
#elif defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
        /*lint -e{923, 9006} HARDWARE_ACCESS */
        uint32 offset = ADDRESS_OFFSET_IMCR_TO_MSCR; /* Address range MSCR[264] + Reserved_32bit[248] + IMCR[512]. MSCR[512] corresponds to IMCR[0] */
        /*lint -e{923} HRADWARE_ACCESS */
        SIU.PSMI[configType->inputSelectConfig[i].reg - offset].R = (uint32)configType->inputSelectConfig[i].config;
#else
        /*lint -e{632, 923}  IMCR register must be written as a 32bit integer, see reference manual for e.g. mpc5744P */
        SIU.PSMI[configType->inputSelectConfig[i].reg].R = (uint32)configType->inputSelectConfig[i].config;
#endif
    }
#endif
       for (uint32 i = 0; configType->padConfig[i].reg != PORT_INVALID_REG; i++) {
        /* MSCR register must be written as a 32bit integer, see reference manual for e.g. mpc5744P */
        /*lint -e{923} Ok, this cast is in the Freescale header file */
           SIU.PCR[configType->padConfig[i].reg].R = configType->padConfig[i].config;
    }

    /** @req SWS_Port_00002 */
    Port_state = PORT_INITIALIZED;
    Port_configPtr = configType;
}

#if ( PORT_SET_PIN_DIRECTION_API == STD_ON )
void Port_SetPinDirection( Port_PinType pin, Port_PinDirectionType direction )
{

    /** @req SWS_Port_00138 */
    /** @req SWS_Port_00054 */
    /** @req SWS_Port_00077 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_STATE_INIT(PORT_SET_PIN_DIRECTION_ID);
    VALIDATE_PARAM_PIN(pin, PORT_SET_PIN_DIRECTION_ID);

    /* @req SWS_Port_00137 */
    /*lint -e{9027} OTHER Negating the expression is required to report the error*/
    VALIDATE(Port_configPtr->padConfig[pin].pinDirectionChangeable, PORT_SET_PIN_DIRECTION_ID, PORT_E_DIRECTION_UNCHANGEABLE)

    /* @safe Safe_Port_00002 */
    VALIDATE((direction == PORT_PIN_IN)|| (direction == PORT_PIN_OUT), PORT_SET_PIN_DIRECTION_ID, PORT_E_UNEXPECTED_EXECUTION)
    /*lint -restore*/
    SchM_Enter_Port_EA_0(); /* Disable interrupts */

    /** @req SWS_Port_00063 */
    /*lint -save -e923 Ok, this cast is in the Freescale header file */
    if (direction==PORT_PIN_IN) {
        SIU.PCR[Port_configPtr->padConfig[pin].reg].B.IBE = 1u;
#if defined(CFG_MPC5777M)
        SIU.PCR[Port_configPtr->padConfig[pin].reg].B.ODC = 0u; /* Output disabled */
#else
        SIU.PCR[Port_configPtr->padConfig[pin].reg].B.OBE = 0u;
#endif
    }
    else {
        SIU.PCR[Port_configPtr->padConfig[pin].reg].B.IBE = 1u; /* Always readback */
#if defined(CFG_MPC5777M)
        if( Port_configPtr->padConfig[pin].config & ODC_MASK ) {
            /* Configured as output */
            SIU.PCR[Port_configPtr->padConfig[pin].reg].B.ODC = ((Port_configPtr->padConfig[pin].config & ODC_MASK)>>ODC_OFFSET);
        } else {
            SIU.PCR[Port_configPtr->padConfig[pin].reg].B.ODC = PORT_OUTPUT_PUSHPULL;
        }
#else
        SIU.PCR[Port_configPtr->padConfig[pin].reg].B.OBE = 1u;
#endif
    }
    /*lint -restore */

    SchM_Exit_Port_EA_0(); /* Enable interrupts */

}
#endif


void Port_RefreshPortDirection(void) {
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_STATE_INIT(PORT_REFRESH_PORT_DIRECTION_ID);
    uint32_t bitMask = PORT_DIRECTION_CFG_MASK;

    SchM_Enter_Port_EA_0(); /* Disable interrupts */

    /** @req SWS_Port_00060 */
    /** @req SWS_Port_00061 */
    /** @req SWS_Port_00066 */
    for (uint32 i = 0; Port_configPtr->padConfig[i].reg != PORT_INVALID_REG; i++) {
        if (FALSE == Port_configPtr->padConfig[i].pinDirectionChangeable) {
            /*lint -e{923} Ok, this cast is in the Freescale header file */
            /*lint -e{632, 639} Ok to assign to vuin16_t*/
            SIU.PCR[Port_configPtr->padConfig[i].reg].R =
                    (SIU.PCR[Port_configPtr->padConfig[i].reg].R & ~bitMask) | /* Clear direction bits*/
                    (Port_configPtr->padConfig[i].config & bitMask);           /* Set the direction bit from config */
        }
    }

    SchM_Exit_Port_EA_0(); /* Enable interrupts */
}

#if PORT_VERSION_INFO_API == STD_ON
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    /** @req SWS_Port_00225 */
    /** @req SWS_Port_00087 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_PARAM_POINTER(versioninfo, PORT_GET_VERSION_INFO_ID);
    versioninfo->vendorID = PORT_VENDOR_ID;
    versioninfo->moduleID = PORT_MODULE_ID;
    versioninfo->sw_major_version = PORT_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = PORT_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = PORT_SW_PATCH_VERSION;
}
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
    /** @req SWS_Port_00124 */
    /** @req SWS_Port_00128 */
    /** @req SWS_Port_00077 */
    /** @req SWS_Port_00212 */
    /** @req SWS_Port_00087 PORT_E_PARAM_INVALID_MODE not supported */
    /** @req SWS_Port_00125 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_STATE_INIT(PORT_SET_PIN_MODE_ID);
    VALIDATE_PARAM_PIN(Pin, PORT_SET_PIN_MODE_ID);
    /*lint -restore*/
    /* @req SWS_Port_00223 */
    /*lint -e{904} ARGUMENT_CHECK *//*lint -e{9027} Negating expression is required operation */
    VALIDATE(Port_configPtr->padConfig[Pin].pinModeChangeable, PORT_SET_PIN_MODE_ID, PORT_E_MODE_UNCHANGEABLE)


    SchM_Enter_Port_EA_0(); /* Disable interrupts */

    //The pad configuration registers (SIU_PCR) in the SIU allow software control of the static electrical
    //characteristics of external pins. The PCRs can select the multiplexed function of a pin, selection of pullup
    //or pulldown devices, the slew rate of I/O signals, open drain mode for output pins, and hysteresis.
    /*lint -e{923} Ok, this cast is in the Freescale header file */
    /*lint -e{632} The PCR is depends on the MCU, ignoring strong type assignment but the precision loss message will be issued to catch errors */
    SIU.PCR[Port_configPtr->padConfig[Pin].reg].R = Mode;// Put the selected mode to the PCR register

    SchM_Exit_Port_EA_0(); /* Enable interrupts */
}
#endif


