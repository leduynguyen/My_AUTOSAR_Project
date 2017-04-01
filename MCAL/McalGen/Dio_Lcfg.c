
/*
 * Generator version: 5.0.0
 * AUTOSAR version:   4.1.2
 */

#include "Dio.h"
#include "Dio_Cfg.h"

const Dio_ChannelType DioChannelConfigData[] = { 
	DioConf_DioChannel_D7,
	DioConf_DioChannel_D8,
	DioConf_DioChannel_LED1,
	DioConf_DioChannel_LED2,
	DIO_END_OF_LIST
};

const Dio_PortType DioPortConfigData[] = { 
	DioConf_DioPort_D,
	DioConf_DioPort_E,
	DIO_END_OF_LIST
};

const Dio_ChannelGroupType DioGroupConfigData[] = {
	{ 
	  .port = DIO_END_OF_LIST, 
	  .mask = 0,
	  .offset = 0
	}
};

const Dio_ConfigType DioConfigData = {
	.ChannelConfig = DioChannelConfigData,
	.GroupConfig = DioGroupConfigData,
	.PortConfig = DioPortConfigData
};

