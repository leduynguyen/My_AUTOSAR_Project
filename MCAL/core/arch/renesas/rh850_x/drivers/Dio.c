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
/** @tagSettings DEFAULT_ARCHITECTURE=RH850F1H */

/** @req SWS_Dio_00012 */
/** @req SWS_Dio_00063 MCU architecture specific driver */
/** @req SWS_Dio_00051 Read and Write services are acting directly on HW registers */
/** @req SWS_Dio_00118 */
/** @req SWS_Dio_00083 */
/** @req SWS_Dio_00131 */
/** @req SWS_Dio_00129 */
/** @req SWS_Dio_00026 Implemented in generator */
/** @req SWS_Dio_00113 Implemented in generator */

/*
 * ports: PBxx to PJxx with xx ranging from 0 to 15
 *
 */

#include "Dio.h"
#include "Port_RegFinder.h"
#if defined(USE_DET)
#include "Det.h" /** @req SWS_Dio_00194 */
#endif
#include <string.h>

#if (DIO_VERSION_INFO_API == STD_ON)
static Std_VersionInfoType _Dio_VersionInfo =
{ .vendorID = (uint16)DIO_VENDOR_ID, .moduleID = (uint16) DIO_MODULE_ID,
        .sw_major_version = (uint8)DIO_SW_MAJOR_VERSION,
        .sw_minor_version = (uint8)DIO_SW_MINOR_VERSION,
        .sw_patch_version = (uint8)DIO_SW_PATCH_VERSION
};
#endif

typedef struct {
    const Dio_ConfigType* Config;
    boolean InitRun;
}Dio_GlobalType;

Dio_GlobalType DioGlobal = {.InitRun = FALSE, .Config = NULL};

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
          Det_ReportError(DIO_MODULE_ID,0,_api,_err); \
          return; \
        }

#define VALIDATE_RV(_exp,_api,_err, _rv ) \
        if( !(_exp) ) { \
          Det_ReportError(DIO_MODULE_ID,0,_api,_err); \
          return _rv; \
        }
#else
#define IS_VALID_CHANNEL(_x)
#define IS_VALID_PORT(_x)
#define IS_VALID_CHANNELGROUP(_x)
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_RV(_exp,_api,_err,_rv )
#endif

static Dio_PortLevelType ReadPortOutput(Dio_PortType portId)
{
    volatile uint16 *portPinReadRegisterPointer = 0;

    portPinReadRegisterPointer = Port_Arc_getRegPointerFromPort( REGISTERSELECTION_PPR, (Port_Arc_PortGroups)portId, DIO_MODULE_ID, DIO_GLOBAL_ID, DIO_E_UNEXPECTED_EXECUTION);

    return *((Dio_PortLevelType *)portPinReadRegisterPointer);
}

/** @req SWS_Dio_00027 */
/** @req SWS_Dio_00089 */
/** @req SWS_Dio_00128 */
/** @req SWS_Dio_00011 */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType channelId)
{
    Dio_PortLevelType level = STD_LOW;
    VALIDATE_RV( DioGlobal.InitRun, DIO_READCHANNEL_ID, DIO_E_UNINIT, (Dio_LevelType)0 );
    /** @req SWS_Dio_00074 */
    VALIDATE_RV( IS_VALID_CHANNEL(channelId), DIO_READCHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID, (Dio_LevelType)0 );

    volatile uint16 * tempRegPointer = (Dio_PortLevelType *)Port_Arc_getRegPointerFromPinId( REGISTERSELECTION_PPR, (uint16)channelId, 0, 0, 0);
    if( Port_Arc_getPin( (uint16)channelId, tempRegPointer) ){
        level = STD_HIGH;
    }

    return level;
}

/** @req SWS_Dio_00089 */
/** @req SWS_Dio_00128 */
/** @req SWS_Dio_00119 */
/** @!req SWS_Dio_00006 Write depends on value of level, instead on setting STD_HIGH/LOW */
/** @req SWS_Dio_00028 */
/** @req SWS_Dio_00029 */
/** @req SWS_Dio_00079 */
void Dio_WriteChannel(Dio_ChannelType channelId, Dio_LevelType level)
{
    VALIDATE( DioGlobal.InitRun, DIO_WRITECHANNEL_ID, DIO_E_UNINIT );
    /** @req SWS_Dio_00074 */
    VALIDATE( IS_VALID_CHANNEL(channelId), DIO_WRITECHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID);

    Port_Arc_setPin( channelId, Port_Arc_getRegPointerFromPinId(REGISTERSELECTION_P, channelId, 0, 0, 0), level);

    return;
}

/** @req SWS_Dio_00053 */
/** @req SWS_Dio_00031 */
/** @req SWS_Dio_00013 */
/** @!req SWS_Dio_00104 Undefined port pins are not set to 0 (for arch < 16bit) */
Dio_PortLevelType Dio_ReadPort(Dio_PortType portId)
{
    VALIDATE_RV( DioGlobal.InitRun, DIO_READPORT_ID, DIO_E_UNINIT, (Dio_PortLevelType)0 );
    /** @req SWS_Dio_00074 */
    VALIDATE_RV( IS_VALID_PORT(portId), DIO_READPORT_ID, DIO_E_PARAM_INVALID_PORT_ID, (Dio_PortLevelType)0 );

    VALIDATE_RV( portId<_NR_OF_PORTGROUPS_, DIO_READPORT_ID, DIO_E_UNEXPECTED_EXECUTION, (Dio_PortLevelType)0);

    return ReadPortOutput(portId);
}

/** @req SWS_Dio_00034 */
/** @req SWS_Dio_00053 */
/** @req SWS_Dio_00007 */
/** @!req SWS_Dio_00004 No check if channels of port is set as input */
/** @!req SWS_Dio_00035 No check if channels of port is set as input */
/** @req SWS_Dio_00105 Note: No check for endianess */
void Dio_WritePort(Dio_PortType portId, Dio_PortLevelType level)
{
    VALIDATE( DioGlobal.InitRun, DIO_WRITEPORT_ID, DIO_E_UNINIT );
    /** @req SWS_Dio_00074 */
    VALIDATE( IS_VALID_PORT(portId), DIO_WRITEPORT_ID, DIO_E_PARAM_INVALID_PORT_ID );
    volatile uint16 *portRegister = Port_Arc_getRegPointerFromPort( REGISTERSELECTION_P, (Port_Arc_PortGroups)portId, DIO_MODULE_ID, DIO_GLOBAL_ID, DIO_E_UNEXPECTED_EXECUTION);
    *portRegister = level;
}

/** @req SWS_Dio_00056 */
/** @req SWS_Dio_00014 */
/** @req SWS_Dio_00037 Depends on the generator */
/** @req SWS_Dio_00092 */
/** @req SWS_Dio_00093 */
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

/** @req SWS_Dio_00056 */
/** @req SWS_Dio_00008 */
/** @req SWS_Dio_00039 Depends on the generator */
/** @req SWS_Dio_00040 */
/** @req SWS_Dio_00090 */
/** @req SWS_Dio_00091 */
void Dio_WriteChannelGroup(const Dio_ChannelGroupType *channelGroupIdPtr,
    Dio_PortLevelType level) {

    VALIDATE( DioGlobal.InitRun, DIO_WRITECHANNELGROUP_ID, DIO_E_UNINIT );
    /** @req SWS_Dio_00114 */
    VALIDATE( IS_VALID_CHANNELGROUP(channelGroupIdPtr), DIO_WRITECHANNELGROUP_ID, DIO_E_PARAM_INVALID_GROUP_ID );

    VALIDATE( (channelGroupIdPtr->port)<_NR_OF_PORTGROUPS_, DIO_WRITECHANNELGROUP_ID, DIO_E_UNEXPECTED_EXECUTION);

    // Shift up and apply mask so that no unwanted bits are affected
    level = (level << channelGroupIdPtr->offset) & channelGroupIdPtr->mask;

    // Read port and clear out masked bits
    Dio_PortLevelType portVal = ReadPortOutput(channelGroupIdPtr->port) & (~channelGroupIdPtr->mask);

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

    memcpy(versioninfo, &_Dio_VersionInfo, sizeof(Std_VersionInfoType));
    return;
}

#endif

void Dio_Init(const Dio_ConfigType* ConfigPtr)
{
    /** @req SWS_Dio_00167 **/
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
