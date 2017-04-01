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

/** @tagSettings DEFAULT_ARCHITECTURE=RH850F1H */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/* General Port module requirements */
/** @req SWS_Port_00004 */
/** @req SWS_Port_00079 All pins are changeable during runtime */
/** @req SWS_Port_00081 */
/** @req SWS_Port_00082 */
/** @req SWS_Port_00124 */
/** @req SWS_Port_00013 Symbolic names */
/** @req SWS_Port_00073 */

/** @req SWS_Port_00006 Implemented in the generator/tool */
/** @req SWS_Port_00207 Implemented in the generator/tool */
/** @req SWS_Port_00076 Implemented in the generator */
/** @req SWS_Port_00006 */
/** @req SWS_Port_00075 Atomic access */
/** @req SWS_Port_00129 */
/** @req SWS_Port_00087 Not PORT_E_MODE_UNCHANGEABLE and PORT_E_DIRECTION_UNCHANGEABLE*/

/** @req SWS_Port_00204 Not including Port_Cbk.c*/
/** @req SWS_Port_00129 Additional types are included from other files */


#include "Port.h"
#include "Port_RegFinder.h"
#include "Cpu.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#include "SchM_Port.h"

/* SHORT ON HW
 *  Have a bunch of port groups (14):
 *  - P0 to P2, P8 to P12, P18, P20, JP0, AP0, AP1, IP0
 *
 *  Regs:
 *  The settings for one pin is spread out over ~10 registers where each bit
 *  represent one pin.
 *
 *  For example: To set the input buffer on or off for one PIN you have to set
 *   the right bit in one of the following registers: PIBCn, APIBCn, JPIBC0 or
 *   IPIBC0. Where n=port group number.
 *
 *   To translate from the "Port Pin Id" used in the autosar configuration to
 *   the port group type and number used in Renesas the array PinIdToPort is used.
 *
 *   Knowing which type of register one wants to set and having the info from
 *   PinIdToPort make it possible to get the correct register adress from the
 *   array regs. This is done in the helper function getReg().
 */

typedef enum {
    PORT_UNINITIALIZED = 0, //!< PORT_UNINITIALIZED
    PORT_INITIALIZED,      //!< PORT_INITIALIZED
} Port_StateType;

static Port_StateType Port_state = PORT_UNINITIALIZED;
static const Port_ConfigType * Port_configPtr = &PortConfigData;

#if (PORT_DEV_ERROR_DETECT)
#define NR_OF_CONFIGURABLE_PINS 176
#define VALIDATE_PARAM_CONFIG(_ptr,_api) \
    if( (_ptr)==((void *)0) ) { \
        Det_ReportError(PORT_MODULE_ID, 0, _api, PORT_E_PARAM_CONFIG ); \
        return; \
    }

#define VALIDATE_STATE_INIT(_api)\
    if(PORT_INITIALIZED!=Port_state){\
        Det_ReportError(PORT_MODULE_ID, 0, _api, PORT_E_UNINIT ); \
        return; \
    }

#define VALIDATE_PARAM_PIN(_pin, _api)\
    if(_pin>(NR_OF_CONFIGURABLE_PINS+1) || _pin<1){\
        Det_ReportError(PORT_MODULE_ID, 0, _api, PORT_E_PARAM_PIN ); \
        return; \
    }

#define VALIDATE_PARAM_POINTER(_pointer, _api)\
    if(_pointer == ((void *)0) ) {\
        Det_ReportError(PORT_MODULE_ID, 0, _api, PORT_E_PARAM_POINTER ); \
        return; \
    }

#else
#define VALIDATE_PARAM_CONFIG(_ptr,_api)
#define VALIDATE_STATE_INIT(_api)
#define VALIDATE_PARAM_PIN(_pin, _api)
#define VALIDATE_PARAM_POINTER(_pointer)
#endif

/** @req SWS_Port_00001 */
/** @req SWS_Port_00043 */
/** @req SWS_Port_00214 All I/O registers are initialized by port */
/** @req SWS_Port_00215 */
/** @req SWS_Port_00217 Only I/O registers are initialized by port */
/** @req SWS_Port_00218 Only I/O registers are initialized by port */
/** @req SWS_Port_00042 */
/** @req SWS_Port_00041 */
/** !req SWS_Port_00055 */
/** !req SWS_Port_00005 */
void Port_Init(const Port_ConfigType *configType) {
    /* @req SWS_Port_00105 Always checking the parameter */
    VALIDATE_PARAM_CONFIG(configType, PORT_INIT_ID);

    uint8 pinNr = 0;    // The numbering used in table 2.1 Pin Assignment 176-Pin LQFP in the Renesas Ref Manual

    // First set outputs
    for (uint16 i = 0; configType->pinConfig[i].PortPinId != PORT_INVALID_REG; i++) {
        pinNr = configType->pinConfig[i].PortPinId;
        SET_PORT_REGISTER(pinNr, P, configType->pinConfig[i], PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
    }

    // Copy config to register areas
    for (uint16 i = 0; configType->pinConfig[i].PortPinId != PORT_INVALID_REG; i++) {
        pinNr = configType->pinConfig[i].PortPinId;

        SET_PORT_REGISTER(pinNr, PMC, configType->pinConfig[i], PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
        SET_PORT_REGISTER(pinNr, PIPC, configType->pinConfig[i], PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
        SET_PORT_REGISTER(pinNr, PM, configType->pinConfig[i], PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
        SET_PORT_REGISTER(pinNr, PIBC, configType->pinConfig[i], PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
        SET_PORT_REGISTER(pinNr, PFC, configType->pinConfig[i], PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
        SET_PORT_REGISTER(pinNr, PFCE, configType->pinConfig[i], PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
        SET_PORT_REGISTER(pinNr, PFCAE, configType->pinConfig[i], PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
        SET_PORT_REGISTER(pinNr, PBDC, configType->pinConfig[i], PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
        SET_PORT_REGISTER(pinNr, PU, configType->pinConfig[i], PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
        SET_PORT_REGISTER(pinNr, PD, configType->pinConfig[i], PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
        SET_PROTECTED_PORT_REGISTER(pinNr, PDSC, configType->pinConfig[i], PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
        SET_PROTECTED_PORT_REGISTER(pinNr, PODC, configType->pinConfig[i], PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
        SET_PORT_REGISTER(pinNr, PIS, configType->pinConfig[i], PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
    }

    /** @req SWS_Port_00002 */
    Port_state = PORT_INITIALIZED;
    Port_configPtr = configType;
}

#if ( PORT_SET_PIN_DIRECTION_API == STD_ON )
/** @req SWS_Port_00138 */
/** @req SWS_Port_00054 */
void Port_SetPinDirection( Port_PinType bit, Port_PinDirectionType direction )
{
    VALIDATE_STATE_INIT(PORT_SET_PIN_DIRECTION_ID);
    VALIDATE_PARAM_PIN(bit, PORT_SET_PIN_DIRECTION_ID);

    SchM_Enter_Port_EA_0(); // Lock interrupts
    /** @req SWS_Port_00063 */
    if (direction==PORT_PIN_IN) {
        Port_Arc_setPin(bit, Port_Arc_getRegPointerFromPinId( REGISTERSELECTION_PM, bit, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION), 1);
        Port_Arc_setPin(bit, Port_Arc_getRegPointerFromPinId( REGISTERSELECTION_PIBC, bit, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION), 1);
    }
    else {
        Port_Arc_setPin(bit, Port_Arc_getRegPointerFromPinId( REGISTERSELECTION_PM, bit, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION), 0);
        Port_Arc_setPin(bit, Port_Arc_getRegPointerFromPinId( REGISTERSELECTION_PIBC, bit, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION), 0);
    }
    SchM_Exit_Port_EA_0(); // Restore interrupts

}
#endif

/** !req SWS_Port_00066 */
void Port_RefreshPortDirection(void) {
    VALIDATE_STATE_INIT(PORT_REFRESH_PORT_DIRECTION_ID);
    uint8 pinNr = 0;
    SchM_Enter_Port_EA_0();
    for (uint16 i = 0; Port_configPtr->pinConfig[i].PortPinId != PORT_INVALID_REG; i++) {
        pinNr = Port_configPtr->pinConfig[i].PortPinId;
        SET_PORT_REGISTER(pinNr, PM, Port_configPtr->pinConfig[i], PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
        SET_PORT_REGISTER(pinNr, PIBC, Port_configPtr->pinConfig[i], PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
    }
    SchM_Exit_Port_EA_0();
}

#if PORT_VERSION_INFO_API == STD_ON
/** @req SWS_Port_00225 */
/** @req SWS_Port_00087 */

void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    VALIDATE_PARAM_POINTER(versioninfo, PORT_GET_VERSION_INFO_ID);
    versioninfo->vendorID = PORT_VENDOR_ID;
    versioninfo->moduleID = PORT_MODULE_ID;
    versioninfo->sw_major_version = PORT_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = PORT_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = PORT_SW_PATCH_VERSION;
}
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
/** @req SWS_Port_00128 */
/** !req SWS_Port_00077*/
/** @req SWS_Port_00212 */
/** @req SWS_Port_00087 PORT_E_MODE_UNCHANGEABLE and PORT_E_PARAM_INVALID_MODE not available */
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
    /** @req SWS_Port_00125 */
    VALIDATE_STATE_INIT(PORT_SET_PIN_MODE_ID);
    VALIDATE_PARAM_PIN(Pin, PORT_SET_PIN_MODE_ID);

    ArcPort_PinConfig tmpPortCfg = {.flags.UINT16 = Mode};

    SET_PORT_REGISTER(Pin, PMC,   tmpPortCfg, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
    SET_PORT_REGISTER(Pin, PIPC,  tmpPortCfg, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
    SET_PORT_REGISTER(Pin, PM,    tmpPortCfg, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
    SET_PORT_REGISTER(Pin, PIBC,  tmpPortCfg, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
    SET_PORT_REGISTER(Pin, PFC,   tmpPortCfg, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
    SET_PORT_REGISTER(Pin, PFCE,  tmpPortCfg, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
    SET_PORT_REGISTER(Pin, PFCAE, tmpPortCfg, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
    SET_PORT_REGISTER(Pin, PBDC, tmpPortCfg, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
    SET_PORT_REGISTER(Pin, PU,    tmpPortCfg, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
    SET_PORT_REGISTER(Pin, PD,    tmpPortCfg, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
    SET_PORT_REGISTER(Pin, PDSC,  tmpPortCfg, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
    SET_PORT_REGISTER(Pin, PODC,  tmpPortCfg, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);
    SET_PORT_REGISTER(Pin, PIS,  tmpPortCfg, PORT_MODULE_ID, PORT_GLOBAL_ID, PORT_E_UNEXPECTED_EXECUTION);

}
#endif

