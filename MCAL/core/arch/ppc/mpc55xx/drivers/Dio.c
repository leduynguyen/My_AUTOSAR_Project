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
/** @tagSettings DEFAULT_ARCHITECTURE=PPC|MPC5607B|MPC5645S|MPC5748G|MPC5747C  */

/** @req SWS_Dio_00012 Read function should work on both in and out channels */
/** @req SWS_Dio_00063 MCU architecture specific driver */
/** @req SWS_Dio_00065 Det error table */
/** @req SWS_Dio_00118 If Det error occurs - the read function shall return 0 */
/** @req SWS_Dio_00083 The real value of the pin shall be returned */
/** @req SWS_Dio_00131 Imported types */
/** @req SWS_Dio_00129 Post build or pre compile shall be supported */
/** @req SWS_Dio_00026 Implemented in generator */
/** @req SWS_Dio_00113 Implemented in generator */

#include "Dio.h"
#if defined(USE_DET)
#include "Det.h" /** @req SWS_Dio_00194 */
#endif
#include "mpc55xx.h"

typedef struct {
    const Dio_ConfigType* Config;
    boolean InitRun;
}Dio_GlobalType;

static Dio_GlobalType DioGlobal = {.InitRun = FALSE, .Config = NULL};

#if ( DIO_DEV_ERROR_DETECT == STD_ON )
/**
 * Search for channelId in configuration
 * @param channelId
 * @return TRUE if channelId exists in the configuration,
 *         FALSE otherwise
 */
static boolean Channel_Config_Contains(Dio_ChannelType channelId)
{
    const Dio_ChannelType* ch_ptr=DioGlobal.Config->ChannelConfig;
    boolean rv=FALSE;
    while ((NULL != ch_ptr) && (DIO_END_OF_LIST!=*ch_ptr)) {
        if (*ch_ptr==channelId) {
            rv=TRUE;
            break;
        }
        ch_ptr++;
    }
    return rv;
}

#if !defined(DISABLE_DIO_PARALLELL_RW_API)
/**
 * Search for portId in configuration
 * @param portId
 * @return TRUE if portId exists in the configuration,
 *         FALSE otherwise
 */
static boolean Port_Config_Contains(Dio_PortType portId)
{
    const Dio_PortType* port_ptr=DioGlobal.Config->PortConfig;
    boolean rv=FALSE;
    while ((NULL != port_ptr) && (DIO_END_OF_LIST!=*port_ptr)) {
        if (*port_ptr==portId) {
            rv=TRUE;
            break;
        }
        port_ptr++;
    }
    return rv;
}

/**
 * Search for _channelGroupIdPtr in configuration
 * @param _channelGroupIdPtr
 * @return TRUE if _channelGroupIdPtr exists in the configuration,
 *         FALSE otherwise
 */
static boolean Channel_Group_Config_Contains(const Dio_ChannelGroupType* channelGroupIdPtr)
{
    const Dio_ChannelGroupType* chGrp_ptr=DioGlobal.Config->GroupConfig;
    boolean rv=FALSE;
    if(channelGroupIdPtr != 0) {
        while ((NULL != chGrp_ptr) && (DIO_END_OF_LIST!=chGrp_ptr->port)) {
            if ((chGrp_ptr->port==channelGroupIdPtr->port) &&
                (chGrp_ptr->mask==channelGroupIdPtr->mask)) {
                rv=TRUE;
                break;
            }
            chGrp_ptr++;
        }
    }
    return rv;
}
#endif

#define IS_VALID_CHANNEL(_x) (0u != Channel_Config_Contains(_x))
#define IS_VALID_PORT(_x) (0u != Port_Config_Contains(_x))
#define IS_VALID_CHANNELGROUP(_x) (0u != Channel_Group_Config_Contains(_x))

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
#define REPORT_DET_ERROR(_api,_err) (void)Det_ReportError(DIO_MODULE_ID,0,_api,_err)

#else
#define IS_VALID_CHANNEL(_x)
#define IS_VALID_PORT(_x)
#define IS_VALID_CHANNELGROUP(_x)
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_RV(_exp,_api,_err,_rv )
#define REPORT_DET_ERROR(_api,_err)
#endif


Dio_LevelType Dio_ReadChannel(Dio_ChannelType channelId)
{
    /** @req SWS_Dio_00027 */
    /** @req SWS_Dio_00089 */
    /** @req SWS_Dio_00128 */
    /** @req SWS_Dio_00011 */
    /** @req SWS_Dio_00051 */

    Dio_LevelType level = STD_LOW;
    /*lint -e{904, 9027} ARGUMENT_CHECK */
    VALIDATE_RV( DioGlobal.InitRun, DIO_READCHANNEL_ID, DIO_E_UNINIT, (Dio_LevelType)0u );
    /** @req SWS_Dio_00074 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_RV( IS_VALID_CHANNEL(channelId), DIO_READCHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID, (Dio_LevelType)0u );
    /*lint -save -e923 False positive */
    if (SIU.PCR[channelId].B.IBE != 0u) {
        // Read level from SIU.
        if (SIU.GPDI [channelId].R != 0u) {
            level = STD_HIGH;
        }
    }
    /*lint -restore*/
    else {
        REPORT_DET_ERROR(DIO_READCHANNEL_ID, DIO_E_UNEXPECTED_EXECUTION);
    }

    /* @safe Safe_Dio_00001 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_RV( (level == STD_ON) || (level == STD_OFF), DIO_READCHANNEL_ID, DIO_E_UNEXPECTED_EXECUTION, (Dio_LevelType)STD_OFF );
    return level;
}

// Disable R/W Channel Group and R/W Port APIs for incompatible MCU:s
#if !defined(DISABLE_DIO_PARALLELL_RW_API)


Dio_PortLevelType Dio_ReadPort(Dio_PortType portId)
{

    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00053 */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00031 */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00013 */
    /** @req PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00051 */
    /** @!req SWS_Dio_00104 Undefined port pins are not set to 0 (for arch < 16bit) */

    Dio_PortLevelType level;
    /*lint -e{904, 9027} ARGUMENT_CHECK */
    VALIDATE_RV( DioGlobal.InitRun, DIO_READPORT_ID, DIO_E_UNINIT, (Dio_PortLevelType)0u );

    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00075 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_RV( IS_VALID_PORT(portId), DIO_READPORT_ID, DIO_E_PARAM_INVALID_PORT_ID, (Dio_PortLevelType)0u );

    /*lint -save -e954 False positive, cannot set ptr to const */
#if defined(CFG_MPC5668) || defined(CFG_MPC5516)
    vuint16_t *ptr = (vuint16_t *)&SIU.PGPDI0; // The GPDI 0-3 is organized in 32bit chunks but we want to step them in 16bit port-widths
#else
    /*lint -e{545, 923, 929, 740} The GPDI 0-3 is organized in 32bit chunks but we want to step them in 16bit port-widths */
    vuint16_t *ptr = (vuint16_t *)&SIU.PGPDI;
#endif
    level = (Dio_PortLevelType)ptr[portId]; // Read the bit pattern (16bits) to the port
    return level;
    /*lint -restore */
}

/**
 * Writes levels to a port, writing only masked bits using HW masked write register.
 * @param portId
 * @param levels Each bit in levels corresponds to a channel that shall be
 *               written only if the corresponding bit in the mask is set to 1.
 * @param mask   Each binary 1 in the mask corresponds to a channel that shall be written.
 */
static void writePortMasked(Dio_PortType portId, Dio_PortLevelType levels, Dio_PortLevelType mask)
{
    /*lint -e{904, 9027} ARGUMENT_CHECK */
    VALIDATE( DioGlobal.InitRun, DIO_READCHANNELGROUP_ID, DIO_E_UNINIT );
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE( IS_VALID_PORT(portId), DIO_WRITEPORT_ID, DIO_E_PARAM_INVALID_PORT_ID );

    /*lint -e{923} Ok, in Freescale header file */
#if defined(CFG_MPC5516)
    vuint32_t *ptr = (vuint32_t *)&SIU.MPGPDO0;
#elif defined(CFG_MPC5668)
    vuint32_t *ptr = (vuint32_t *)&SIU.MPGPDO1;
#else
    vuint32_t *ptr = &SIU.MPGPDO[0].R;
#endif
    uint32 levelsAndMask = 0u;
    levelsAndMask |= (uint32)levels;
    levelsAndMask |= ((uint32)mask << 16u);

    ptr[portId] = levelsAndMask; // Write the bit pattern and mask to the port
}


void Dio_WritePort(Dio_PortType portId, Dio_PortLevelType level)
{
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00034 */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00053 */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00007 */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00051 */
    /** @!req SWS_Dio_00004 No check if channels of port is set as input */
    /** @!req SWS_Dio_00035 No check if channels of port is set as input */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00105 Note: No check for endianess */
    /*lint -e{904, 9027} ARGUMENT_CHECK */
    VALIDATE( DioGlobal.InitRun, DIO_WRITEPORT_ID, DIO_E_UNINIT );
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00075 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE( IS_VALID_PORT(portId), DIO_WRITEPORT_ID, DIO_E_PARAM_INVALID_PORT_ID );

    // find address of first port
#if defined(CFG_MPC5668) || defined(CFG_MPC5516)
    vuint16_t *ptr = (vuint16_t *)&SIU.PGPDO0; // The GPDO 0-3 is organized in 32bit chunks but we want to step them in 16bit port-widths
#else
    /*lint -e{545, 923, 929, 740} The GPDI 0-3 is organized in 32bit chunks but we want to step them in 16bit port-widths */
    vuint16_t *ptr = (vuint16_t *)&SIU.PGPDO;

#endif
    /*lint -e{632} Ok to assign to register, same width */
    ptr[portId] = level; // Write the bit pattern (16bits) to the port

    return;
}


Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType *channelGroupIdPtr)
{

    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00056 */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00014 */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00037 Depends on the generator */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00092 */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00093 */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00051 */

    Dio_PortLevelType level;
    /*lint -e{904, 9027} ARGUMENT_CHECK */
    VALIDATE_RV( DioGlobal.InitRun, DIO_READCHANNELGROUP_ID, DIO_E_UNINIT, (Dio_PortLevelType)0u );
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00114 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_RV( IS_VALID_CHANNELGROUP(channelGroupIdPtr), DIO_READCHANNELGROUP_ID, DIO_E_PARAM_INVALID_GROUP_ID, (Dio_PortLevelType)0u );

    // Get masked values
    level = Dio_ReadPort(channelGroupIdPtr->port) & channelGroupIdPtr->mask;

    // Shift down
    level = level >> channelGroupIdPtr->offset;

    return level;
}


void Dio_WriteChannelGroup(const Dio_ChannelGroupType *channelGroupIdPtr, Dio_PortLevelType level) {

    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00056 */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00008 */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00039 Depends on the generator */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00040 */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00090 */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00091 */
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00051 */

    Dio_PortLevelType tmpLevel; /* Function parameters may not  modified in Misra 2012 */
    /*lint -e{904, 9027} ARGUMENT_CHECK */
    VALIDATE( DioGlobal.InitRun, DIO_WRITECHANNELGROUP_ID, DIO_E_UNINIT );
    /** @req:PPC|MPC5607B|MPC5748G|MPC5747C SWS_Dio_00114 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE( IS_VALID_CHANNELGROUP(channelGroupIdPtr), DIO_WRITECHANNELGROUP_ID, DIO_E_PARAM_INVALID_GROUP_ID );

    // Shift up and apply mask
    /*lint -e{701} False positive detected, it is not signed */
    tmpLevel = (level << channelGroupIdPtr->offset) & channelGroupIdPtr->mask;

    // Write to masked write register
    writePortMasked(channelGroupIdPtr->port, tmpLevel, channelGroupIdPtr->mask);
}
#endif


#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    /*lint -e{904, 9027} ARGUMENT_CHECK */
    VALIDATE( DioGlobal.InitRun, DIO_GETVERSIONINFO_ID, DIO_E_UNINIT );
    /** @req SWS_Dio_00189 **/
    /*lint -e{904} ARGUMENT_CHECK */
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
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE( (NULL != ConfigPtr), DIO_INIT_ID, DIO_E_PARAM_CONFIG );
    DioGlobal.Config = ConfigPtr;
    DioGlobal.InitRun = TRUE;
}

void Dio_WriteChannel(Dio_ChannelType channelId, Dio_LevelType level) {

    /** @req SWS_Dio_00089 */
    /** @req SWS_Dio_00128 */
    /** @req SWS_Dio_00119 */
    /** @req SWS_Dio_00006 */
    /** @req SWS_Dio_00028 */
    /** @req SWS_Dio_00029 */
    /** @req SWS_Dio_00079 */
    /*lint -e{904, 9027} ARGUMENT_CHECK */
    VALIDATE( DioGlobal.InitRun, DIO_WRITECHANNEL_ID, DIO_E_UNINIT );
    /** @req SWS_Dio_00074 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE( IS_VALID_CHANNEL(channelId), DIO_WRITECHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID);

    /** @safe Safe_Dio_00005 */
    VALIDATE( ((level == STD_ON) || (level == STD_OFF)), DIO_WRITECHANNEL_ID, DIO_E_PARAM_LEVEL);
    /*lint -restore*/
    // Write level to SIU.

    /*lint -save -e923 False positive */
    /*lint -e{632} Ok to write to register, same width */
    SIU.GPDO [channelId].R = level;
    /*lint -restore */
}

#if defined(HOST_TEST)
/**
 * Deinitialize the module. Only used for testing purposes
 */
void Dio_Arc_Deinit(void)
{
    DioGlobal.Config = NULL;
    DioGlobal.InitRun = FALSE;
}

void Dio_Arc_SetConfigToNULL()
{

    static const Dio_ChannelGroupType testChannelGroup[] = {
        {
            .port = (Dio_PortType)0,
            .mask = 0u,
            .offset = 0u
        },
        {
            .port = DIO_END_OF_LIST,
            .mask = 0u,
            .offset = 0u
        }
    };

    static const Dio_ConfigType testConfig = {.ChannelConfig = NULL, .PortConfig = NULL, .GroupConfig = testChannelGroup};
    DioGlobal.Config = &testConfig;
}


#endif

