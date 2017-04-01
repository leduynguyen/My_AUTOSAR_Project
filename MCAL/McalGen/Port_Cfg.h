
/*
 * Generator version: 5.0.1
 * AUTOSAR version:   4.1.2
 */

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

#include "Std_Types.h"
#include "Port_ConfigTypes.h"
#include "Port.h"

#if !(((PORT_SW_MAJOR_VERSION == 5) && (PORT_SW_MINOR_VERSION == 0)) )
#error Port: Configuration file expected BSW module version to be 5.0.*
#endif

#if !(((PORT_AR_RELEASE_MAJOR_VERSION == 4) && (PORT_AR_RELEASE_MINOR_VERSION == 1)) )
#error Port: Configuration file expected AUTOSAR version to be 4.1.*
#endif


#define	PORT_VERSION_INFO_API			STD_OFF
#define	PORT_DEV_ERROR_DETECT			STD_OFF
#define PORT_SET_PIN_DIRECTION_API		STD_OFF
/** Allow Pin mode changes during runtime (not avail on this CPU) */
#define PORT_SET_PIN_MODE_API			STD_OFF
#define PORT_POSTBUILD_VARIANT 			STD_OFF


#define PortConf_PortPin_PD0		((Port_PinType)48)
#define Port_PD0	PortConf_PortPin_PD0
#define PortConf_PortPin_PD1		((Port_PinType)49)
#define Port_PD1	PortConf_PortPin_PD1
#define PortConf_PortPin_PD13		((Port_PinType)61)
#define Port_PD13	PortConf_PortPin_PD13
#define PortConf_PortPin_PD7		((Port_PinType)55)
#define Port_PD7	PortConf_PortPin_PD7
#define PortConf_PortPin_PE12		((Port_PinType)76)
#define Port_PE12	PortConf_PortPin_PE12
#define PortConf_PortPin_PE13		((Port_PinType)77)
#define Port_PE13	PortConf_PortPin_PE13
#define PortConf_PortPin_PortPin_B5		((Port_PinType)21)
#define Port_PortPin_B5	PortConf_PortPin_PortPin_B5
#define PortConf_PortPin_PortPin_B6		((Port_PinType)2222)
#define Port_PortPin_B6	PortConf_PortPin_PortPin_B6

/** Instance of the top level configuration container */
extern const Port_ConfigType PortConfigData;

/* Configuration Set Handles */
#define PortConfigSet (PortConfigData)
#define Can_PortConfigSet (PortConfigData)


#endif /* PORT_CFG_H_ */
