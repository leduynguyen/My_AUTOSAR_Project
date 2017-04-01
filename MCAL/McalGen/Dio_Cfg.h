
/*
 * Generator version: 5.0.0
 * AUTOSAR version:   4.1.2
 */

#ifndef DIO_CFG_H_
#define DIO_CFG_H_

#include "Dio.h"

#if !(((DIO_SW_MAJOR_VERSION == 5) && (DIO_SW_MINOR_VERSION == 0)) )
#error Dio: Configuration file expected BSW module version to be 5.0.*
#endif

#if !(((DIO_AR_RELEASE_MAJOR_VERSION == 4) && (DIO_AR_RELEASE_MINOR_VERSION == 1)) )
#error Dio: Configuration file expected AUTOSAR version to be 4.1.*
#endif


#define DIO_VERSION_INFO_API    STD_OFF
#define DIO_DEV_ERROR_DETECT    STD_OFF

#define DIO_END_OF_LIST  (0xFFFFFFFFu)

typedef enum {
	DIO_PORT_A,
	DIO_PORT_B,
	DIO_PORT_C,
	DIO_PORT_D,
	DIO_PORT_E,
	DIO_PORT_F,
} Dio_Hw_PortType;

// Channels
#define DioConf_DioChannel_D7 76
#define Dio_D7 DioConf_DioChannel_D7
#define DioConf_DioChannel_D8 77
#define Dio_D8 DioConf_DioChannel_D8
#define DioConf_DioChannel_LED1 55
#define Dio_LED1 DioConf_DioChannel_LED1
#define DioConf_DioChannel_LED2 61
#define Dio_LED2 DioConf_DioChannel_LED2

// Channel groups


// Ports
#define DioConf_DioPort_D (uint32)(DIO_PORT_D)
#define Dio_D DioConf_DioPort_D
#define DioConf_DioPort_E (uint32)(DIO_PORT_E)
#define Dio_E DioConf_DioPort_E

/* Configuration Set Handles */
#define DioConfig (DioConfigData)
#define Dio_DioConfig (DioConfigData)

#endif /*DIO_CFG_H_*/
