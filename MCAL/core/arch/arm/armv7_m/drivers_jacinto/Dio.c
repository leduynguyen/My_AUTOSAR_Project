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

/** @tagSettings DEFAULT_ARCHITECTURE=JACINTO5|JACINTO6 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/** @req SWS_Dio_00129  PRE-COMPILE is supported */
/** @req SWS_Dio_00128  A general-purpose digital IO pin represents a DIO channel */
/** @req SWS_Dio_00063 The Dio module shall adapt its configuration and usage to the microcontroller and ECU */
/** @req SWS_DIO_00065 Dio module shall detect errors and exceptions depending on its build version */

#include "Std_Types.h"
#include "Dio.h"
/**@req SWS_Dio_00194 */
#if defined(USE_DET)
#include "Det.h"
#endif

#if defined(CFG_JAC5) || defined(CFG_JAC5E)
/* Jacinto5 */
#define GPIO1_BASE 0x48032000
#define GPIO2_BASE 0x4804C000
#define GPIO3_BASE 0x481AC000
#define GPIO4_BASE 0x481AE000
#if defined(CFG_JAC5E)
/* Jacinto5E */
#define GPIO5_BASE 0x48420000
#define GPIO6_BASE 0x48422000
#endif
#else
/* Jacinto6 */
#define GPIO1_BASE (0x4AE10000 + L3_OFFSET)
#define GPIO2_BASE (0x48055000 + L3_OFFSET)
#define GPIO3_BASE (0x48057000 + L3_OFFSET)
#define GPIO4_BASE (0x48059000 + L3_OFFSET)
#define GPIO5_BASE (0x4805B000 + L3_OFFSET)
#define GPIO6_BASE (0x4805D000 + L3_OFFSET)
#define GPIO7_BASE (0x48051000 + L3_OFFSET)
#define GPIO8_BASE (0x48053000 + L3_OFFSET)
#endif

struct Gpio_t{
    volatile volatile uint32 GPIO_REVISION;/* Offset 0x0 */
    volatile uint32 RESERVED1[3];
    volatile uint32 GPIO_SYSCONFIG;/* Offset 0x10 */
    volatile uint32 RESERVED2[3];
    volatile uint32 GPIO_EOI;/* Offset 0x20 */
    volatile uint32 GPIO_IRQSTATUS_RAW_0;
    volatile uint32 GPIO_IRQSTATUS_RAW_1;
    volatile uint32 GPIO_IRQSTATUS_0;
    volatile uint32 GPIO_IRQSTATUS_1;
    volatile uint32 GPIO_IRQSTATUS_SET_0;
    volatile uint32 GPIO_IRQSTATUS_SET_1;
    volatile uint32 GPIO_IRQSTATUS_CLR_0;
    volatile uint32 GPIO_IRQSTATUS_CLR_1;
    volatile uint32 GPIO_IRQWAKEN_0;
    volatile uint32 GPIO_IRQWAKEN_1;
    volatile uint32 RESERVED3[50];
    volatile uint32 GPIO_SYSSTATUS;
    volatile uint32 RESERVED4[6];
    volatile uint32 GPIO_CTRL;
    volatile uint32 GPIO_OE;
    volatile uint32 GPIO_DATAIN;
    volatile uint32 GPIO_DATAOUT;
    volatile uint32 GPIO_LEVELDETECT0;
    volatile uint32 GPIO_LEVELDETECT1;
    volatile uint32 GPIO_RISINGDETECT;
    volatile uint32 GPIO_FALLINGDETECT;
    volatile uint32 GPIO_DEBOUNCENABLE;
    volatile uint32 GPIO_DEBOUNCINGTIME;
    volatile uint32 RESERVED5[14];
    volatile uint32 GPIO_CLEARDATAOUT;
    volatile uint32 GPIO_SETDATAOUT;
};

typedef volatile struct Gpio_t Gpio_Type;

#define GPIO1               ((Gpio_Type *) GPIO1_BASE)
#define GPIO2               ((Gpio_Type *) GPIO2_BASE)
#define GPIO3               ((Gpio_Type *) GPIO3_BASE)
#define GPIO4               ((Gpio_Type *) GPIO4_BASE)
#if defined(CFG_JAC5E) || defined(CFG_JAC6)
#define GPIO5               ((Gpio_Type *) GPIO5_BASE)
#define GPIO6               ((Gpio_Type *) GPIO6_BASE)
#endif
#if defined(CFG_JAC6)
#define GPIO7               ((Gpio_Type *) GPIO7_BASE)
#define GPIO8               ((Gpio_Type *) GPIO8_BASE)
#endif

#if defined(CFG_JAC5)
/* Jacinto5: has 4 GPIOs */
#define PORT_NOF_GPIO 4u
#elif defined (CFG_JAC5E)
/* Jacinto5e: has 6 GPIOs */
#define PORT_NOF_GPIO 6u
#else
/* Jacinto6: has 8 GPIOs */
#define PORT_NOF_GPIO 8u
#endif
#define GPIO_NOF_PINS 32u

static Gpio_Type *GPIO_ports[] = {
        GPIO1, GPIO2, GPIO3, GPIO4
#if defined (CFG_JAC5E)
        , GPIO5, GPIO6
#endif
#if defined(CFG_JAC6)
        , GPIO5, GPIO6, GPIO7, GPIO8
#endif
};

typedef struct {
    const Dio_ConfigType* Config;
    boolean InitRun;
}Dio_GlobalType;

static Dio_GlobalType DioGlobal = {.InitRun = FALSE, .Config = NULL};

#if ( DIO_DEV_ERROR_DETECT == STD_ON )
static uint8 Channel_Config_Contains(Dio_ChannelType channelId)
{
    const Dio_ChannelType* ch_ptr = DioGlobal.Config->ChannelConfig;
    uint8 rv = 0;
    while (DIO_END_OF_LIST != *ch_ptr) {
        if (*ch_ptr == channelId) {
            rv = 1;
            break;
        }
        ch_ptr++;
    }
    return rv;
}

#define IS_VALID_CHANNEL(_x) (0 != Channel_Config_Contains(_x))

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
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_RV(_exp,_api,_err,_rv )
#endif

/**
 *
 * @param channelId
 * @return
 */

/* @req SWS_Dio_00012 */ /* @req SWS_Dio_00051*/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType channelId)
{
    Dio_LevelType level;
    /** @req SWS_Dio_00118 */
    VALIDATE_RV( DioGlobal.InitRun, DIO_READCHANNEL_ID, DIO_E_UNINIT, (Dio_LevelType)0 );
    /** @req SWS_Dio_00074 */ /** @req SWS_Dio_00118 */
    VALIDATE_RV( IS_VALID_CHANNEL(channelId), DIO_READCHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID, (Dio_LevelType)0 );
    /** @req SWS_Dio_00011 */
    if( 0 != (GPIO_ports[channelId/GPIO_NOF_PINS]->GPIO_DATAIN & (1UL<<(channelId  % GPIO_NOF_PINS))) ) {
        level = STD_HIGH;
    } else {
        level = STD_LOW;
    }
    return level; /** @req SWS_Dio_00027 */
}

/**
 *
 * @param channelId
 * @param level
 */
/* @req SWS_Dio_00051 */
void Dio_WriteChannel(Dio_ChannelType channelId, Dio_LevelType level)
{   /** @req SWS_Dio_00119 */
    VALIDATE( DioGlobal.InitRun, DIO_WRITECHANNEL_ID, DIO_E_UNINIT );
    /** @req SWS_Dio_00074 */ /** @req SWS_Dio_00119 */
    VALIDATE( IS_VALID_CHANNEL(channelId), DIO_WRITECHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID);
    /** @req SWS_Dio_00089 */ /** @req SWS_Dio_00006 */
    /**  !req SWS_Dio_00028 */ /**  !req SWS_Dio_00029 */
    if( level == STD_HIGH ) {
        GPIO_ports[channelId/GPIO_NOF_PINS]->GPIO_DATAOUT |= (1UL<<(channelId  % GPIO_NOF_PINS));
    } else if(level == STD_LOW ) {
        GPIO_ports[channelId/GPIO_NOF_PINS]->GPIO_DATAOUT &= ~(1UL<<(channelId  % GPIO_NOF_PINS));
    }else{
        /* do nothing */
    }

    return;
}

/**
 *
 * @param ConfigPtr
 */
void Dio_Init(const Dio_ConfigType* ConfigPtr)
{
    /** @req SWS_Dio_00167 **/
    /** @req SWS_Dio_00166 **/
    VALIDATE( (NULL != ConfigPtr), DIO_INIT_ID, DIO_E_PARAM_CONFIG );
    DioGlobal.Config = ConfigPtr;
    DioGlobal.InitRun = TRUE;
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
void Dio_Arc_Deinit(void)
{
    DioGlobal.Config = NULL;
    DioGlobal.InitRun = FALSE;
}
#endif

