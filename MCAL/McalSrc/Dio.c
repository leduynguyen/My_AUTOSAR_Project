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

/** @tagSettings DEFAULT_ARCHITECTURE=STM32 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#include "Std_Types.h"
#include "Dio.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include <string.h>
#include "stm32f10x_gpio.h"

typedef GPIO_TypeDef* GPIO_TypeDefPtr;
const GPIO_TypeDefPtr GPIO_ports[] = { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF };

#define DIO_GET_PORT_FROM_CHANNEL_ID(_channelId) (_channelId / 16)
#define DIO_GET_BIT_FROM_CHANNEL_ID(_channelId) (1 << (_channelId % 16))


typedef struct {
    const Dio_ConfigType* Config;
    boolean InitRun;
}Dio_GlobalType;

static Dio_GlobalType DioGlobal = {.InitRun = FALSE, .Config = NULL};

#if ( DIO_DEV_ERROR_DETECT == STD_ON )
static int Channel_Config_Contains(Dio_ChannelType channelId)
{
    const Dio_ChannelType* ch_ptr=DioGlobal.Config->ChannelConfig;
    int rv=0;
    while (DIO_END_OF_LIST!=*ch_ptr) {
        if (*ch_ptr==channelId) {
            rv=1;
            break;
        }
        ch_ptr++;
    }
    return rv;
}

static int Port_Config_Contains(Dio_PortType portId)
{
    const Dio_PortType* port_ptr=DioGlobal.Config->PortConfig;
    int rv=0;
    while (DIO_END_OF_LIST!=*port_ptr) {
        if (*port_ptr==portId) {
            rv=1;
            break;
        }
        port_ptr++;
    }
    return rv;
}

static int Channel_Group_Config_Contains(const Dio_ChannelGroupType* _channelGroupIdPtr)
{
    const Dio_ChannelGroupType* chGrp_ptr=DioGlobal.Config->GroupConfig;
    int rv=0;
    if(_channelGroupIdPtr != 0) {
        while (DIO_END_OF_LIST!=chGrp_ptr->port) {
            if (chGrp_ptr->port==_channelGroupIdPtr->port&&
                    chGrp_ptr->mask==_channelGroupIdPtr->mask) {
                rv=1;
                break;
            }
            chGrp_ptr++;
        }
    }
    return rv;
}

#define IS_VALID_CHANNEL(_x) (0 != Channel_Config_Contains(_x))
#define IS_VALID_PORT(_x) (0 != Port_Config_Contains(_x))
#define IS_VALID_CHANNELGROUP(_x) (0 != Channel_Group_Config_Contains(_x))

#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(DIO_MODULE_ID,0,_api,_err); \
          return; \
        }

#define VALIDATE_RV(_exp,_api,_err, _rv ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(DIO_MODULE_ID,0,_api,_err); \
          return _rv; \
        }
#else
#define IS_VALID_CHANNEL(_x)
#define IS_VALID_PORT(_x)
#define IS_VALID_CHANNELGROUP(_x)
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_RV(_exp,_api,_err,_rv )
#endif

Dio_PortLevelType Dio_ReadPort(Dio_PortType portId)
{
    Dio_PortLevelType level = 0;
    VALIDATE_RV( DioGlobal.InitRun, DIO_READPORT_ID, DIO_E_UNINIT, (Dio_PortLevelType)0 );
    /** @req SWS_Dio_00074 */
    VALIDATE_RV( IS_VALID_PORT(portId), DIO_READPORT_ID, DIO_E_PARAM_INVALID_PORT_ID, (Dio_PortLevelType)0 );

    level = GPIO_ReadInputData(GPIO_ports[portId]);

    return level;
}

void Dio_WritePort(Dio_PortType portId, Dio_PortLevelType level)
{
    VALIDATE( DioGlobal.InitRun, DIO_READCHANNELGROUP_ID, DIO_E_UNINIT );
    /** @req SWS_Dio_00074 */
    VALIDATE( IS_VALID_PORT(portId), DIO_WRITEPORT_ID, DIO_E_PARAM_INVALID_PORT_ID );

    GPIO_Write(GPIO_ports[portId], level);

    return;
}

Dio_LevelType Dio_ReadChannel(Dio_ChannelType channelId)
{
    Dio_LevelType level;
    VALIDATE_RV( DioGlobal.InitRun, DIO_READCHANNEL_ID, DIO_E_UNINIT, (Dio_LevelType)0 );
    /** @req SWS_Dio_00074 */
    VALIDATE_RV( IS_VALID_CHANNEL(channelId), DIO_READCHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID, (Dio_LevelType)0 );

    Dio_PortLevelType portVal = Dio_ReadPort(DIO_GET_PORT_FROM_CHANNEL_ID(channelId));
    Dio_PortLevelType bit = DIO_GET_BIT_FROM_CHANNEL_ID(channelId);

    if ((portVal & bit) != STD_LOW){
        level = STD_HIGH;
    } else{
        level = STD_LOW;
    }

    return (level);
}

void Dio_WriteChannel(Dio_ChannelType channelId, Dio_LevelType level)
{
    VALIDATE( DioGlobal.InitRun, DIO_WRITECHANNEL_ID, DIO_E_UNINIT );
    /** @req SWS_Dio_00074 */
    VALIDATE( IS_VALID_CHANNEL(channelId), DIO_WRITECHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID);

    Dio_PortLevelType portVal = GPIO_ReadOutputData(GPIO_ports[DIO_GET_PORT_FROM_CHANNEL_ID(channelId)]);
    Dio_PortLevelType bit = DIO_GET_BIT_FROM_CHANNEL_ID(channelId);

    if(level == STD_HIGH){
        portVal |= bit;
    }else{
        portVal &= ~bit;
    }

    Dio_WritePort(DIO_GET_PORT_FROM_CHANNEL_ID(channelId), portVal);

    return;
}


Dio_PortLevelType Dio_ReadChannelGroup(
    const Dio_ChannelGroupType *channelGroupIdPtr)
{
    Dio_PortLevelType level;
    VALIDATE_RV( DioGlobal.InitRun, DIO_READCHANNELGROUP_ID, DIO_E_UNINIT, (Dio_PortLevelType)0 );
    /** @req SWS_Dio_00114 */
    VALIDATE_RV( IS_VALID_CHANNELGROUP(channelGroupIdPtr), DIO_READCHANNELGROUP_ID, DIO_E_PARAM_INVALID_GROUP_ID, (Dio_PortLevelType)0 );

    // Get masked values
    level = Dio_ReadPort(channelGroupIdPtr->port) & channelGroupIdPtr->mask;

    // Shift down
    level = level >> channelGroupIdPtr->offset;

    return level;
}

void Dio_WriteChannelGroup(const Dio_ChannelGroupType *channelGroupIdPtr,
    Dio_PortLevelType level)
{
    VALIDATE( DioGlobal.InitRun, DIO_WRITECHANNELGROUP_ID, DIO_E_UNINIT );
    /** @req SWS_Dio_00114 */
    VALIDATE( IS_VALID_CHANNELGROUP(channelGroupIdPtr), DIO_WRITECHANNELGROUP_ID, DIO_E_PARAM_INVALID_GROUP_ID );

    // Shift up and apply mask so that no unwanted bits are affected
    level = (level << channelGroupIdPtr->offset) & channelGroupIdPtr->mask;

    // Read port and clear out masked bits
    Dio_PortLevelType portVal = GPIO_ReadOutputData(GPIO_ports[channelGroupIdPtr->port]) & (~channelGroupIdPtr->mask);

    // Or in the upshifted masked level
    portVal |= level;

    Dio_WritePort(channelGroupIdPtr->port, portVal);

    return;
}

#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    VALIDATE( DioGlobal.InitRun, DIO_GETVERSIONINFO_ID, DIO_E_UNINIT );
    /** @req SWS_Dio_00189 **/
    VALIDATE( !(versioninfo == NULL), DIO_GETVERSIONINFO_ID, DIO_E_PARAM_POINTER );

    versioninfo->vendorID = DIO_VENDOR_ID;
    versioninfo->moduleID = DIO_MODULE_ID;
    versioninfo->sw_major_version = DIO_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = DIO_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = DIO_SW_PATCH_VERSION;

}
#endif

void Dio_Init(const Dio_ConfigType* ConfigPtr)
{
    /** @req SWS_Dio_00167 **/
    /** @req SWS_Dio_00166 **/
    VALIDATE( (NULL != ConfigPtr), DIO_INIT_ID, DIO_E_PARAM_CONFIG );
    DioGlobal.Config = ConfigPtr;
    DioGlobal.InitRun = TRUE;
}

#if defined(HOST_TEST)
void Dio_Arc_Deinit(void)
{
    DioGlobal.Config = NULL;
    DioGlobal.InitRun = FALSE;
}
void Dio_Arc_SetConfigToNULL()
{
    /* Not implemented for this platform */
}
#endif

