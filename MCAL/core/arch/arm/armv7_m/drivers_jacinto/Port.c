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

/** @req SWS_Port_00207 Implemented in the generator/tool */
/** @req SWS_Port_00129 */
/** @req SWS_Port_00073 */
/** @req SWS_Port_00079 */
/** @req SWS_Port_00004 */
/** @req SWS_Port_00087 Not PORT_E_MODE_UNCHANGEABLE and PORT_E_DIRECTION_UNCHANGEABLE*/
/** @req SWS_Port_00204 Not including Port_Cbk.c*/

#include "Port.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include <string.h>
#define GPIO_NOF_PINS 32u
#define IS_VALID_GPIO_PIN(_x) (((_x) >= 0) && ((_x) < GPIO_NOF_PINS))

#if defined(CFG_JAC5) || defined(CFG_JAC5E)
#if defined(CFG_JAC5)
/* Jacinto5: Valid GPIOs are 0-3 */
#define PORT_NOF_GPIO 4u
#else /* defined(CFG_JAC5E) */
/* Jacinto5e: Valid GPIOs are 0-5 */
#define PORT_NOF_GPIO 6u
#endif
#define IS_VALID_GPIO(_x) (((_x) >= 0) && ((_x) < PORT_NOF_GPIO))
#define TO_GPIO_INDEX(_x) (_x)
#define PINCTL_BIT_RSVD3 (1UL<<19UL)
#define PINCTL_BIT_RSVD2 (1UL<<18UL)
#else
/* Jacinto6: Valid GPIOs are 1-8 */
#define PORT_NOF_GPIO 8u
#define IS_VALID_GPIO(_x) (((_x) > 0) && ((_x) <= PORT_NOF_GPIO))
#define TO_GPIO_INDEX(_x) ((_x) - 1)
#endif


#if defined(CFG_JAC5) || defined(CFG_JAC5E)
#define GPIO1_BASE 0x48032000
#define GPIO2_BASE 0x4804C000
#define GPIO3_BASE 0x481AC000
#define GPIO4_BASE 0x481AE000
#if defined(CFG_JAC5E)
#define GPIO5_BASE 0x48420000
#define GPIO6_BASE 0x48422000
#endif
#else
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
    volatile uint32 GPIO_REVISION;/* Offset 0x0 */
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

#define GPIO_SYSTATS_SOFTRESET_BIT (1UL<<1UL)
#define GPIO_SYSCONFIG_IDLEMODE_MASK (3UL<<3UL)
#define GPIO_CTRL_GATINGRATIO_MASK (3UL<<3UL)
#define GPIO_SYSCONFIG_ENAWAKEUP_MASK (1UL<<2UL)

static Gpio_Type *GPIO_ports[] = {
        GPIO1, GPIO2, GPIO3, GPIO4
#if defined (CFG_JAC5E)
        , GPIO5, GPIO6
#endif
#if defined(CFG_JAC6)
        , GPIO5, GPIO6, GPIO7, GPIO8
#endif
};

typedef enum {
    PORT_UNINITIALIZED = 0,
    PORT_INITIALIZED,
} Port_StateType;

static Port_StateType portState = PORT_UNINITIALIZED;
static const Port_ConfigType *portConfigPtr = NULL;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
#define VALIDATE_NO_RV(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(PORT_MODULE_ID,0,_api,_err); \
          return; \
        }
#else
#define VALIDATE_NO_RV(_exp,_api,_err )
#endif

#if (PORT_VERSION_INFO_API == STD_ON)
static Std_VersionInfoType _Port_VersionInfo =
{ .vendorID = (uint16)PORT_VENDOR_ID, .moduleID = (uint16)PORT_MODULE_ID,
        .sw_major_version = (uint8)PORT_SW_MAJOR_VERSION,
        .sw_minor_version = (uint8)PORT_SW_MINOR_VERSION,
        .sw_patch_version = (uint8)PORT_SW_PATCH_VERSION,
};
#endif

/** @req SWS_Port_00001 */
/** @req SWS_Port_00214 All I/O registers are initialized by port */
/** @req SWS_Port_00215 */
/** @req SWS_Port_00217 Only I/O registers are initialized by port */
/** @req SWS_Port_00218 Only I/O registers are initialized by port */
/** @req SWS_Port_00140 */
/** @req SWS_Port_00041 Comment: To reduce flash usage the configuration tool can disable configuration of some ports  */
/** @req SWS_Port_00042 */
/** @req SWS_Port_00043 Comment: Output value is set before ar */
/** @req SWS_Port_00002 The _portState varialble is initialised. */
/** @req SWS_Port_00055 Comment: Output value is set before direction */
void Port_Init(const Port_ConfigType *ConfigPtr)
{
    VALIDATE_NO_RV(NULL != ConfigPtr, PORT_INIT_ID, PORT_E_PARAM_CONFIG);/** @req SWS_Port_00105 */

#if (PORT_GPIO_SOFT_RESET == STD_ON)
    for(uint8 i = 0; i < PORT_NOF_GPIO; i++) {
        /* Reset GPIO */
        GPIO_ports[i]->GPIO_SYSCONFIG |= GPIO_SYSTATS_SOFTRESET_BIT;
        /* Wait until reset done */
        while(0 == (GPIO_ports[i]->GPIO_SYSSTATUS & 1UL));
        GPIO_ports[i]->GPIO_SYSCONFIG &= ~(GPIO_SYSCONFIG_IDLEMODE_MASK);
        GPIO_ports[i]->GPIO_LEVELDETECT1 = 0UL;
        GPIO_ports[i]->GPIO_LEVELDETECT0 = 0UL;
        GPIO_ports[i]->GPIO_RISINGDETECT = 0UL;
        GPIO_ports[i]->GPIO_FALLINGDETECT = 0UL;
        GPIO_ports[i]->GPIO_CTRL &= ~GPIO_CTRL_GATINGRATIO_MASK;
        GPIO_ports[i]->GPIO_OE = 0xffffffffUL;
        GPIO_ports[i]->GPIO_DEBOUNCINGTIME = 0UL;
        GPIO_ports[i]->GPIO_DEBOUNCENABLE = 0UL;
        GPIO_ports[i]->GPIO_IRQWAKEN_0 = 0UL;
        GPIO_ports[i]->GPIO_IRQWAKEN_1 = 0UL;
        GPIO_ports[i]->GPIO_SYSCONFIG &= ~GPIO_SYSCONFIG_ENAWAKEUP_MASK;
    }
#endif
    for(uint32 pin = 0; pin < ConfigPtr->nofDioPins; pin++) {
        if( IS_VALID_GPIO(ConfigPtr->dioConfig[pin].gpio) && IS_VALID_GPIO_PIN(ConfigPtr->dioConfig[pin].gpioPin)) {
            if(ConfigPtr->dioConfig[pin].isOutput) {
                if(PORT_PIN_LEVEL_LOW == ConfigPtr->dioConfig[pin].initLevel ) {
                    GPIO_ports[TO_GPIO_INDEX(ConfigPtr->dioConfig[pin].gpio)]->GPIO_DATAOUT &= ~(1UL<<(ConfigPtr->dioConfig[pin].gpioPin));
                } else {
                    GPIO_ports[TO_GPIO_INDEX(ConfigPtr->dioConfig[pin].gpio)]->GPIO_DATAOUT |= (1UL<<(ConfigPtr->dioConfig[pin].gpioPin));
                }
                GPIO_ports[TO_GPIO_INDEX(ConfigPtr->dioConfig[pin].gpio)]->GPIO_OE &= ~(1UL<<(ConfigPtr->dioConfig[pin].gpioPin));
            } else {
                GPIO_ports[TO_GPIO_INDEX(ConfigPtr->dioConfig[pin].gpio)]->GPIO_OE |= (1UL<<(ConfigPtr->dioConfig[pin].gpioPin));
            }
#if (PORT_GPIO_SOFT_RESET == STD_OFF)
            GPIO_ports[TO_GPIO_INDEX(ConfigPtr->dioConfig[pin].gpio)]->GPIO_LEVELDETECT1 &= ~(1UL<<(ConfigPtr->dioConfig[pin].gpioPin));
            GPIO_ports[TO_GPIO_INDEX(ConfigPtr->dioConfig[pin].gpio)]->GPIO_LEVELDETECT0 &= ~(1UL<<(ConfigPtr->dioConfig[pin].gpioPin));
            GPIO_ports[TO_GPIO_INDEX(ConfigPtr->dioConfig[pin].gpio)]->GPIO_RISINGDETECT &= ~(1UL<<(ConfigPtr->dioConfig[pin].gpioPin));
            GPIO_ports[TO_GPIO_INDEX(ConfigPtr->dioConfig[pin].gpio)]->GPIO_FALLINGDETECT &= ~(1UL<<(ConfigPtr->dioConfig[pin].gpioPin));
            GPIO_ports[TO_GPIO_INDEX(ConfigPtr->dioConfig[pin].gpio)]->GPIO_DEBOUNCENABLE &= ~(1UL<<(ConfigPtr->dioConfig[pin].gpioPin));
            GPIO_ports[TO_GPIO_INDEX(ConfigPtr->dioConfig[pin].gpio)]->GPIO_IRQWAKEN_0 &= ~(1UL<<(ConfigPtr->dioConfig[pin].gpioPin));
            GPIO_ports[TO_GPIO_INDEX(ConfigPtr->dioConfig[pin].gpio)]->GPIO_IRQWAKEN_1 &= ~(1UL<<(ConfigPtr->dioConfig[pin].gpioPin));
#endif
        } else {
            /* IMPROVEMENT: Det-Error */
        }
    }
    for (uint32 i = 0; i < ConfigPtr->nofPins; i++) {
        /* Configure pin. */
#if defined(CFG_JAC6)
        uint32 *regPtr = (uint32*) (ConfigPtr->padConfig[i].pcrRegAddr + L3_OFFSET);
        *regPtr = ConfigPtr->padConfig[i].pcrVal;
#elif defined(CFG_JAC5) || defined(CFG_JAC5E)
        uint32 *regPtr = (uint32*)ConfigPtr->padConfig[i].pcrRegAddr;
        /* According to ref manual bit 19 (Rsvd3) must always be written with the reset value
         * and bit 18 (Rsvd2) must always be written as 1.  */
        uint32 regVal = *regPtr;
        *regPtr = ((regVal & PINCTL_BIT_RSVD3) | PINCTL_BIT_RSVD2 | ConfigPtr->padConfig[i].pcrVal);
#else
#error MCU not defined.
#endif
    }

    portState = PORT_INITIALIZED;
    portConfigPtr = ConfigPtr;
    return;
}

/** @req SWS_Port_00143 */
/** @req SWS_Port_00225 */
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versionInfo)
{
    VALIDATE_NO_RV(NULL != versionInfo, PORT_GET_VERSION_INFO_ID, PORT_E_PARAM_POINTER);
    memcpy(versionInfo, &_Port_VersionInfo, sizeof(Std_VersionInfoType));
    return;
}
#endif
