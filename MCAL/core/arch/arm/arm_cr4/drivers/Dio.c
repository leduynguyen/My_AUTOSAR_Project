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

/** @tagSettings DEFAULT_ARCHITECTURE=TMS570 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */


#include "Std_Types.h"
#include "Dio.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "Cpu.h"
#include "core_cr4.h"
#include <string.h>

/* Important note: the board has two dedicated GIO ports, but port GIO_PORTC is
 * actually one of the NHET units being used as general I/O. GIOA and GIOB ports
 * have 8 pins/channels each, but the NHET has 32, so some functions that deal
 * with offsets act differently for GIO_PORTC
 */
GIO_RegisterType *GPIO_ports[] = { GIO_PORTA_BASE, GIO_PORTB_BASE, GIO_PORTC_BASE };
GIO_SpiRegisterCollectionType spi5Collection = {
    .dirReg = (uint32_t*)0xFFF7FC18,
    .inReg  = (uint32_t*)0xFFF7FC1C,
    .outReg = (uint32_t*)0xFFF7FC20,
};
#define GIO_SPI5PORT   ((GIO_SpiRegisterCollectionType)spi5Collection)

#define NHET_GIO_PORT_INDEX 2
#define SPI5_GIO_PORT_INDEX 3
#define SPI5_FIRST_CHANNEL (48)

typedef struct {
    const Dio_ConfigType* Config;
    boolean InitRun;
}Dio_GlobalType;

static Dio_GlobalType DioGlobal = {.InitRun = FALSE, .Config = NULL};

#define DIO_GET_PORT_FROM_CHANNEL_ID(_channelId) getPortFromChannel(_channelId)
#define DIO_GET_BIT_FROM_CHANNEL_ID(_channelId) getBitFromChannel(_channelId)

#define SPI_SOMI_SHIFT (24)
#define SPI_SIMO_SHIFT (16)
#define SPI_CLK_SHIFT  (9)
#define SPI_ENA_SHIFT  (8)
#define SPI_CS_SHIFT   (0)

#if ( DIO_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(DIO_MODULE_ID,0,_api,_err); \
          return; \
        }
#define VALIDATE_W_RV(_exp, _api, _err, _rv) \
        if( !(_exp) ) { \
            (void)Det_ReportError(DIO_MODULE_ID,0,_api,_err); \
            return _rv; \
        }
#else
#define VALIDATE(_exp, _api, _err)
#define VALIDATE_W_RV(_exp, _api, _err, _rv)
#endif

/* Correspondence map of the 14 logical bits in the SPI5 port
 * to actual locations of where the set/clear mask will need to
 * be written
 */
static uint8 spiBitMap[14] =
{
    /* Bits 0-3 correspond to CS, match logical/physical */
    0, 1, 2, 3,
    /* Bit 4 - ENA*/
    8,
    /* Bit 5 - CLK */
    9,
    /* Bits 6-9 are SIMO */
    16, 17, 18, 19,
    /* Bits 10-13 are SOMI */
    24, 25, 26, 27
};

static uint8 getPortFromChannel(uint8 channel)
{
    if (channel >= SPI5_FIRST_CHANNEL) {
        return SPI5_GIO_PORT_INDEX;
    } else if (channel < 16) {
        return channel / 8;
    }
    return NHET_GIO_PORT_INDEX;
}

static uint32 getBitFromChannel (int channel)
{
    if (channel >= SPI5_FIRST_CHANNEL) {
        return (1 << (channel - SPI5_FIRST_CHANNEL) % 14);
    } else if (channel < 16) {
        return (int)(1 << (channel % 8));
    }
    return (1 << ((channel - 16) % 32));
}

#if ( DIO_DEV_ERROR_DETECT == STD_ON )
static int Channel_Config_Contains(Dio_ChannelType channelId)
{
    Dio_ChannelType* ch_ptr=(Dio_ChannelType*)(&DioChannelTypes);
    int rv=0;
    while (DIO_END_OF_LIST!=*ch_ptr)
    {
    if (*ch_ptr==channelId)
    {
        rv=1;
        break;
    }
    ch_ptr++;
    }
    return rv;
}

static int Port_Config_Contains(Dio_PortType portId)
{
    const Dio_PortType* port_ptr= (DioGlobal.Config->PortConfig);
    int rv=0;
    while (DIO_END_OF_LIST!=*port_ptr)
    {
    if (*port_ptr==portId)
    { rv=1; break;}
    port_ptr++;
    }
    return rv;
}

static int Channel_Group_Config_Contains(const Dio_ChannelGroupType* _channelGroupIdPtr)
{
    const Dio_ChannelGroupType* chGrp_ptr= (DioGlobal.Config->GroupConfig);
    int rv=0;

    while (DIO_END_OF_LIST!=chGrp_ptr->port)
    {
    if (chGrp_ptr->port==_channelGroupIdPtr->port&&
        chGrp_ptr->offset==_channelGroupIdPtr->offset&&
        chGrp_ptr->mask==_channelGroupIdPtr->mask)
    { rv=1; break;}
    chGrp_ptr++;
    }
    return rv;
}
#endif

/** @req SWS_Dio_00165 **/
void Dio_Init(const Dio_ConfigType* ConfigPtr)
{
    /** @req SWS_Dio_00166 **/
    /** @req SWS_Dio_00167 **/
    VALIDATE( (NULL != ConfigPtr), DIO_INIT_ID, DIO_E_PARAM_CONFIG );
    DioGlobal.Config = ConfigPtr;
    DioGlobal.InitRun = TRUE;
}

/* For Dio_ReadPort and Dio_WritePort, it is important to note the structure
 * of the SPI5 GPIO, which is different. The bits are not consecutive in
 * memory, and it's also impossible to write with one operation (see in
 * Dio_WritePort).
 * The SPI5 GPIO is a logical port of 14 bits, which consists of the following
 * bits/pins:
 *
 *  <- More Significant                                              Less Significant ->
 * -------------------------------------------------------------------------------------
 * |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
 * | SO3 | SO2 | SO1 | SO0 | SI3 | SI2 | SI1 | SI0 | CLK | ENA | CS3 | CS2 | CS1 | CS0 |
 * |  13 |  12 |  11 |  10 |  9  |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * -------------------------------------------------------------------------------------
 *
 * That order of bits within the port is not mandated by the hardware (it's a
 * logical port anyway), but was chosen as convenient based on the actual addresses,
 * the relation between the addresses is the same in the logical port and actual memory.
 * That is, SI3 is a more significant bit in the physical memory than SO3, which is more
 * significant than CLK, and so on.
 * For the actual memory layout, see register descriptions in TMS570LS1227 manual,
 * sections 28.9.9 - 28.9.11
 */

static inline uint8 readSpiBit(uint8 bit) {
    if ((*(GIO_SPI5PORT.dirReg) & (1 << bit))) {
        return (*GIO_SPI5PORT.outReg >> bit) & 1;
    } else {
        return (*GIO_SPI5PORT.inReg >> bit) & 1;
    }
}

static Dio_PortLevelType Internal_ReadSpiPort()
{
    Dio_PortLevelType level = 0;
    /*read SOMI[3:0] pins (27-24) to bits 13-10*/
    level |= readSpiBit(27) << 13;
    level |= readSpiBit(26) << 12;
    level |= readSpiBit(25) << 11;
    level |= readSpiBit(24) << 10;
    /*read SIMO[3:0] pins (19-16) to bits 9-6*/
    level |= readSpiBit(19) << 9;
    level |= readSpiBit(18) << 8;
    level |= readSpiBit(17) << 7;
    level |= readSpiBit(16) << 6;
    /*read CLK (pin 9) to bit 5*/
    level |= readSpiBit(9) << 5;
    /*read ENA (pin 8) to bit 4*/
    level |= readSpiBit(8) << 4;
    /*read CS[3:0] (pins 3-0) to bits 3-0*/
    level |= readSpiBit(3) << 3;
    level |= readSpiBit(2) << 2;
    level |= readSpiBit(1) << 1;
    level |= readSpiBit(0) << 0;

    return level;
}

/** @req SWS_Dio_00135 **/
Dio_PortLevelType Dio_ReadPort(Dio_PortType portId)
{
    Dio_PortLevelType level = 0;
    VALIDATE_W_RV(DioGlobal.InitRun == TRUE, DIO_READPORT_ID, DIO_E_UNINIT, level);
    /** @req SWS_Dio_00118 **/
    VALIDATE_W_RV(0 != Port_Config_Contains(portId), DIO_READPORT_ID, DIO_E_PARAM_INVALID_PORT_ID, level);

    /** @req SWS_Dio_00031 */
    if (portId == SPI5_GIO_PORT_INDEX)
    {
        level = Internal_ReadSpiPort();
    }
    else if (portId < NHET_GIO_PORT_INDEX)
    {
        /** @req SWS_Dio_00104 **/
        /* The port size actually being 8 bits, set all undefined bits to 0 */
        level = GPIO_ports[portId]->DIN;
        level &= 0xFF;
    }
    else
    {
        level = GPIO_ports[portId]->DIN;
    }

    return level;
}

/** @req SWS_Dio_00136 **/
void Dio_WritePort(Dio_PortType portId, Dio_PortLevelType level)
{
    VALIDATE(DioGlobal.InitRun == TRUE, DIO_WRITEPORT_ID, DIO_E_UNINIT);
    /** @req SWS_Dio_00119 **/
    VALIDATE(0 != Port_Config_Contains(portId), DIO_WRITEPORT_ID, DIO_E_PARAM_INVALID_PORT_ID);

    /** @req SWS_Dio_00034 **/
    /* When writing a smaller port, ignore the MSB */
    if (portId == SPI5_GIO_PORT_INDEX)
    {
        /* This logical port is again very special. In addition to its layout
         * (see before Dio_ReadPort), there isn't a register corresponding to
         * DOUT on the normal ports where you can just write the values.
         * Instead, there's a SET register where you can write 1 to bits, and
         * a CLR register where you can write 0.
         *
         * First we trim the level value to ignore all but the 14 bits, then we
         * calculate what bits need to be set and cleared in the registers.
         */
        uint32 regMask = 0;
        uint8 tmp;
        level = level & 0x3FFF;
        /* Read bits 13-10, corresponding to SOMI[3:0] */
        tmp = (level >> 10) & 0xF;
        regMask |= (tmp << SPI_SOMI_SHIFT);
        /* Read bits 9-6, corresponding to SIMO[3:0] */
        tmp = (level >> 6) & 0xF;
        regMask |= (tmp << SPI_SIMO_SHIFT);
        /* Read bit 5, corresponding to CLK */
        tmp = (level >> 5) & 1;
        regMask |= (tmp  << SPI_CLK_SHIFT);
        /* Read bit 4, corresponding to ENA */
        tmp = (level >> 4) & 1;
        regMask |= (tmp << SPI_ENA_SHIFT);
        /* Finally the 4 least-significant bits are CS */
        tmp = level & 0xF;
        regMask |= (tmp << SPI_CS_SHIFT);

        /* Special consideration since performing a 32-bit write: bit 10 has
         * to be set to bit 16, and bit 11 to bit 24. Because if bit 16 is 1
         * but bit 10 is 0, then bit 16 would get ignored.
         */
        regMask |= ((regMask >> 16) & 1) << 10;
        regMask |= ((regMask >> 24) & 1) << 11;

        /* Now first clear the relevant bits to 0, then write 1 bits */
        *(GIO_SPI5PORT.outReg) = regMask;
    }
    else if (portId < NHET_GIO_PORT_INDEX)
    {
        GPIO_ports[portId]->DOUT = ((Dio_PortLevelType)level) & 0x00FFFFFF;
    }
    else
    {
        GPIO_ports[portId]->DOUT = level;
    }
}

/** @req SWS_Dio_00133 **/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType channelId)
{
    Dio_LevelType level = 0;
    VALIDATE_W_RV(DioGlobal.InitRun == TRUE, DIO_READCHANNEL_ID, DIO_E_UNINIT, level);
    /** @req SWS_Dio_00118 **/
    VALIDATE_W_RV(0!=Channel_Config_Contains(channelId), DIO_READCHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID, level);

    Dio_PortType port = DIO_GET_PORT_FROM_CHANNEL_ID(channelId);
    Dio_PortLevelType bit = DIO_GET_BIT_FROM_CHANNEL_ID(channelId);

    Dio_PortLevelType portVal = Dio_ReadPort(port);

    /** @req SWS_Dio_00027 **/
    if ((portVal & bit) != STD_LOW) {
        level = STD_HIGH;
    } else {
        level = STD_LOW;
    }

    return (level);
}

/** @req SWS_Dio_00134 **/
void Dio_WriteChannel(Dio_ChannelType channelId, Dio_LevelType level)
{
    VALIDATE(DioGlobal.InitRun == TRUE, DIO_WRITECHANNEL_ID, DIO_E_UNINIT);
    /** @req SWS_Dio_00119 **/
    VALIDATE((0!=Channel_Config_Contains(channelId)), DIO_WRITECHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID);

    Dio_PortType port = DIO_GET_PORT_FROM_CHANNEL_ID(channelId);
    Dio_PortLevelType bit = DIO_GET_BIT_FROM_CHANNEL_ID(channelId);

    if (port == SPI5_GIO_PORT_INDEX) {
        /* This port is again special. Need to look up which physical bit to write */
        uint8 physBit = spiBitMap[channelId - SPI5_FIRST_CHANNEL];
        if (!(*(GIO_SPI5PORT.dirReg) & (1 << physBit))) {
            return;
        }
        Dio_PortLevelType portVal = *(GIO_SPI5PORT.outReg);
        if (level == STD_HIGH) {
            portVal |= (1 << physBit);
        } else {
            portVal &= ~(1 << physBit);
        }
        *(GIO_SPI5PORT.outReg) = portVal;
    }
    else
    {

        if(!(GPIO_ports[port]->DIR & bit)) {
            return;
        }

        Dio_PortLevelType portVal;
        if (port < NHET_GIO_PORT_INDEX) {
            portVal = GPIO_ports[port]->DOUT;
        } else {
            portVal = (uint32)GPIO_ports[port]->DOUT;
        }

        if(level == STD_HIGH){
            portVal |= bit;
        }else{
            portVal &= ~bit;
        }

        /** @req SWS_Dio_00028 **/
        GPIO_ports[port]->DOUT = portVal;
    }
}

/** @req SWS_Dio_00137 **/
Dio_PortLevelType Dio_ReadChannelGroup(
    const Dio_ChannelGroupType *channelGroupIdPtr)
{
    Dio_LevelType level = 0;
    /** @req SWS_Dio_00118 **/
    VALIDATE_W_RV((0!=Channel_Group_Config_Contains(channelGroupIdPtr)), DIO_READCHANNELGROUP_ID, DIO_E_PARAM_INVALID_GROUP_ID, level);

    /** @req SWS_Dio_00037 **/
    /** @req SWS_Dio_00092 **/
    // Get masked values
    level = Dio_ReadPort(channelGroupIdPtr->port) & channelGroupIdPtr->mask;

    /** @req SWS_Dio_00093 **/
    // Shift down
    level = level >> channelGroupIdPtr->offset;

    return level;
}

/** @req SWS_Dio_00138 **/
void Dio_WriteChannelGroup(const Dio_ChannelGroupType *channelGroupIdPtr,
    Dio_PortLevelType level)
{
    VALIDATE(DioGlobal.InitRun == TRUE, DIO_WRITECHANNELGROUP_ID, DIO_E_UNINIT);
    /** @req SWS_Dio_00119 **/
    VALIDATE((0!=Channel_Group_Config_Contains(channelGroupIdPtr)), DIO_WRITECHANNELGROUP_ID, DIO_E_PARAM_INVALID_GROUP_ID);

    // Shift up and apply mask so that no unwanted bits are affected
    level = (level << channelGroupIdPtr->offset) & channelGroupIdPtr->mask;

    /** @req SWS_Dio_00090 **/
    // Read port and clear out masked bits
    Dio_PortLevelType portVal = Dio_ReadPort(channelGroupIdPtr->port) & (~channelGroupIdPtr->mask);

    // Or in the upshifted masked level
    portVal |= level;

    /** @req SWS_Dio_00039 **/
    Dio_WritePort(channelGroupIdPtr->port, portVal);
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
    /* Not implemented for this platform */
}
#endif
