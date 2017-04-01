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
#include "Port.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "Cpu.h"
#include <string.h>

#include "core_cr4.h"

#include "Port_tms570.h"

static Port_StateType _portState = PORT_UNINITIALIZED;
static const Port_ConfigType * _configPtr = &PortConfigData;

static Port_GioRegisterType * const Gio_Port_Base[] = {
    PORT_GIO_0_BASE,
    PORT_GIO_1_BASE,
    PORT_GIO_2_BASE,
    PORT_GIO_3_BASE,
    PORT_GIO_4_BASE,
    PORT_GIO_5_BASE,
    PORT_GIO_6_BASE,
    PORT_GIO_7_BASE,
    PORT_GIO_8_BASE,
    PORT_GIO_9_BASE,
    PORT_GIO_10_BASE
};
#if defined(CFG_TMS570LC43X)
static Port_SpiControlRegisterType * const Gio_Spi_Port_Base[] = {
        PORT_SPI1_GIO_BASE,
        PORT_SPI2_GIO_BASE,
        PORT_SPI3_GIO_BASE,
        PORT_SPI4_GIO_BASE,
        PORT_SPI5_GIO_BASE
    };
static uint32 * const Gio_Spi_Port_CGR[] = {
        SPI1GCR,
        SPI2GCR,
        SPI3GCR,
        SPI4GCR,
        SPI5GCR
    };
#endif

#ifdef CFG_TMS570LC43X
static uint32 * PINMMR_Port_Base[] = {
    PINMMR0_BASE_ADDR,
    PINMMR1_BASE_ADDR,
    PINMMR2_BASE_ADDR,
    PINMMR3_BASE_ADDR,
    PINMMR4_BASE_ADDR,
    PINMMR5_BASE_ADDR,
    PINMMR6_BASE_ADDR,
    PINMMR7_BASE_ADDR,
    PINMMR8_BASE_ADDR,
    PINMMR9_BASE_ADDR,
    PINMMR10_BASE_ADDR,
    PINMMR11_BASE_ADDR,
    PINMMR12_BASE_ADDR,
    PINMMR13_BASE_ADDR,
    PINMMR14_BASE_ADDR,
    PINMMR15_BASE_ADDR,
    PINMMR16_BASE_ADDR,
    PINMMR17_BASE_ADDR,
    PINMMR18_BASE_ADDR,
    PINMMR19_BASE_ADDR,
    PINMMR20_BASE_ADDR,
    PINMMR21_BASE_ADDR,
    PINMMR22_BASE_ADDR,
    PINMMR23_BASE_ADDR,
    PINMMR24_BASE_ADDR,
    PINMMR25_BASE_ADDR,
    PINMMR26_BASE_ADDR,
    PINMMR27_BASE_ADDR,
    PINMMR28_BASE_ADDR,
    PINMMR29_BASE_ADDR,
    PINMMR30_BASE_ADDR,
    PINMMR31_BASE_ADDR,
    PINMMR32_BASE_ADDR,
    PINMMR33_BASE_ADDR,
    PINMMR34_BASE_ADDR,
    PINMMR35_BASE_ADDR,
    PINMMR36_BASE_ADDR,
    PINMMR37_BASE_ADDR,
    PINMMR80_BASE_ADDR,
    PINMMR81_BASE_ADDR,
    PINMMR82_BASE_ADDR,
    PINMMR83_BASE_ADDR,
    PINMMR84_BASE_ADDR,
    PINMMR85_BASE_ADDR,
    PINMMR86_BASE_ADDR,
    PINMMR87_BASE_ADDR,
    PINMMR88_BASE_ADDR,
    PINMMR89_BASE_ADDR,
    PINMMR90_BASE_ADDR,
    PINMMR91_BASE_ADDR,
    PINMMR92_BASE_ADDR,
    PINMMR93_BASE_ADDR,
    PINMMR94_BASE_ADDR,
    PINMMR95_BASE_ADDR,
    PINMMR96_BASE_ADDR,
    PINMMR97_BASE_ADDR,
    PINMMR98_BASE_ADDR,
    PINMMR99_BASE_ADDR
};
#elif defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
static uint32 * PINMMR_Port_Base[] = {
    PINMMR0_BASE_ADDR,
    PINMMR1_BASE_ADDR,
    PINMMR2_BASE_ADDR,
    PINMMR3_BASE_ADDR,
    PINMMR4_BASE_ADDR,
    PINMMR5_BASE_ADDR,
    PINMMR6_BASE_ADDR,
    PINMMR7_BASE_ADDR,
    PINMMR8_BASE_ADDR,
    PINMMR9_BASE_ADDR,
    PINMMR10_BASE_ADDR,
    PINMMR11_BASE_ADDR,
    PINMMR12_BASE_ADDR,
    PINMMR13_BASE_ADDR,
    PINMMR14_BASE_ADDR,
    PINMMR15_BASE_ADDR,
    PINMMR16_BASE_ADDR,
    PINMMR17_BASE_ADDR,
    PINMMR18_BASE_ADDR,
    PINMMR19_BASE_ADDR,
    PINMMR20_BASE_ADDR,
    PINMMR21_BASE_ADDR,
    PINMMR22_BASE_ADDR,
    PINMMR23_BASE_ADDR,
    PINMMR24_BASE_ADDR,
    PINMMR25_BASE_ADDR,
    PINMMR26_BASE_ADDR,
    PINMMR27_BASE_ADDR,
    PINMMR28_BASE_ADDR,
    PINMMR29_BASE_ADDR,
    PINMMR30_BASE_ADDR,
    PINMMR31_BASE_ADDR,
    PINMMR32_BASE_ADDR,
    PINMMR33_BASE_ADDR,
    PINMMR34_BASE_ADDR,
    PINMMR35_BASE_ADDR,
    PINMMR36_BASE_ADDR,
    PINMMR37_BASE_ADDR,
    PINMMR38_BASE_ADDR,
    PINMMR39_BASE_ADDR,
    PINMMR40_BASE_ADDR,
    PINMMR41_BASE_ADDR,
    PINMMR42_BASE_ADDR,
    PINMMR43_BASE_ADDR,
    PINMMR44_BASE_ADDR,
    PINMMR45_BASE_ADDR,
    PINMMR46_BASE_ADDR,
    PINMMR47_BASE_ADDR
};
#endif


#if PORT_VERSION_INFO_API == STD_ON
static Std_VersionInfoType _Port_VersionInfo =
{
    .vendorID = (uint16)PORT_VENDOR_ID,
    .moduleID = (uint16) PORT_MODULE_ID,
    .sw_major_version = (uint8)PORT_SW_MAJOR_VERSION,
    .sw_minor_version = (uint8)PORT_SW_MINOR_VERSION,
    .sw_patch_version = (uint8)PORT_SW_PATCH_VERSION,
};
#endif

static inline void Internal_RefreshGioPin(uint16 pinNumber) {
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
    const ArcPort_PadConfigType * pin = &_configPtr->padConfig[pinNumber];
    Port_GioRegisterType *portReg = Gio_Port_Base[pin->regOffset];
    uint32 mask = GET_PIN_MASK(pin->regBit);
    /* On the 144-pin package, some of GIO-enabled pins may have another
     * function by default. E.g. N2HET1 pins 23 and 25. So these need to
     * be multiplexed. Does not apply to GIOA and GIOB ports.
     */
    if (pin->regOffset > 1) { /* Functional port being used for GIO */
        uint8 multiplexOffset = pin->extraOffset;
        uint32 multiplexBit = pin->extraBit;
        if (multiplexOffset != PORT_FUNC_INVALID) {
            /* This is one of the pins that need to be multiplexed */
            *(PINMMR_Port_Base[multiplexOffset]) &= ~(0xFF << ((multiplexBit / 8) * 8));
            *(PINMMR_Port_Base[multiplexOffset]) |= (1 << multiplexBit);
        }
    }
#elif defined(CFG_TMS570LC43X)
    const ArcPort_PadConfigType * pin = &_configPtr->padConfig[pinNumber];
    Port_GioRegisterType *portReg;
    if(pin->config & PORT_PIN_N2HET2){
        portReg = PORT_GIO_3_BASE; // Register for N2HET2
    }else{
        portReg = Gio_Port_Base[pin->regOffset];
    }
    uint32 mask = GET_PIN_MASK(pin->regBit);

    /* Setting the PINMMR for all pins on lc43x even though it is the default that has been chosen. */
    uint8 multiplexOffset = pin->extraOffset;
    uint32 multiplexBit = pin->extraBit;

    if ((multiplexOffset > 37) && (multiplexOffset != PORT_FUNC_INVALID) && (multiplexOffset != PORT_FUNC_USE_DEFAULT_SETTINGS))
    {
        /* There is a gap between 37 and 80 in the PINMMR registers. */
        multiplexOffset = 38 + multiplexOffset - 80;
    }

    if ((multiplexOffset != PORT_FUNC_INVALID) && (multiplexOffset != PORT_FUNC_USE_DEFAULT_SETTINGS))
    {
        *(PINMMR_Port_Base[multiplexOffset]) &= ~(0xFFu << ((multiplexBit / 8u) * 8u));
        *(PINMMR_Port_Base[multiplexOffset]) |= (1u << multiplexBit);
    }
#else
#error MCU not defined.
#endif
    /* @req SWS_Port_00055 */
    /* Pull up/down should be set before direction */

    // Set pull up or down or nothing.
    if (pin->config & PORT_PULL_NONE) {
        portReg->PULDIS |= mask;

    } else {
        portReg->PULDIS &= ~mask;
        if (pin->config & PORT_PULL_UP) {
            portReg->PSL |= mask;

        } else {
            portReg->PSL &= ~mask;
        }
    }

    // Set pin direction
    if (pin->config & PORT_DIR_OUT) {
        portReg->DIR |= mask;

        // Set open drain
        if (pin->config & PORT_ODE_ENABLE) {
            portReg->PDR |= mask;
        } else {
            portReg->PDR &= ~mask;
        }

        // Set Pin High/Low
        if(pin->config & PORT_PIN_LEVEL_HIGH){
            portReg->DOUT |= mask;
        }else{
            portReg->DOUT &= ~mask;
        }

    } else {
        portReg->DIR &= ~mask;
    }
}

static inline void Internal_RefreshSpiGioPin(uint16 pinNumber) {
    const ArcPort_PadConfigType * pin = &_configPtr->padConfig[pinNumber];
#if defined(CFG_TMS570LS12X) || defined (CFG_TMS570LS1114)
    *(SPI5GCR) = 0x1; /* bring SPI module out of reset */
    Port_SpiControlRegisterType *portReg = PORT_SPI5_GIO_BASE;
    uint8 bit = pin->regBit;
#elif defined(CFG_TMS570LC43X)
    /* Setting the PINMMR for all pins on lc43x even though it is the default that has been chosen. */
    uint8 multiplexOffset = pin->extraOffset;
    uint32 multiplexBit = pin->extraBit;

    if ((multiplexOffset > 37) && (multiplexOffset != PORT_FUNC_INVALID) &&
            (multiplexOffset != PORT_FUNC_USE_DEFAULT_SETTINGS))
    {
        /* There is a gap between 37 and 80 in the PINMMR registers. */
        multiplexOffset = 38 + multiplexOffset - 80;
    }

    if ((multiplexOffset != PORT_FUNC_INVALID) && (multiplexOffset != PORT_FUNC_USE_DEFAULT_SETTINGS))
    {
        *(PINMMR_Port_Base[multiplexOffset]) &= ~(0xFFu << ((multiplexBit / 8u) * 8u));
        *(PINMMR_Port_Base[multiplexOffset]) |= (1u << multiplexBit);
    }

    uint32 Spi_port_mask = (((pin->config) >> PORT_PIN_DIO_SPIX_SHIFT) & PORT_PIN_DIO_SPIX_MASK);
    uint32_t *portCGR = Gio_Spi_Port_CGR[Spi_port_mask];
    *(portCGR) = 0x1; /* bring SPI module out of reset */
    Port_SpiControlRegisterType *portReg = Gio_Spi_Port_Base[Spi_port_mask];

    uint32 bit = pin->regBit;
    /* 0 => GIO pin
     * 1 => SPI pin
     */
    portReg->PC0 &= ~(1u << bit);
#endif

    /* @req SWS_Port_00055 */
    /* Pull up/down should be set before direction */

    // Set pull up or down or nothing.
    if (pin->config & PORT_PULL_NONE) {
        portReg->PC7 |= (1u << bit);

    } else {
        portReg->PC7 &= ~(1u << bit);
        if (pin->config & PORT_PULL_UP) {
            portReg->PC8 |= (1u << bit);
        } else {
            portReg->PC8 &= ~(1u << bit);
        }
    }

    // Set pin direction
    if ((pin->config & PORT_DIR_OUT) == PORT_DIR_OUT) {
        portReg->PC1 |= (1u << bit);

        // Set open drain
        if (pin->config & PORT_ODE_ENABLE) {
            portReg->PC6 |= (1u << bit);
        } else {
            portReg->PC6 &= ~(1u << bit);
        }

        // Set Pin High/Low
        if(pin->config & PORT_PIN_LEVEL_HIGH){
            portReg->PC3 |= (1u << bit);
        }else{
            portReg->PC3 &= ~(1u << bit);
        }

    } else {
        portReg->PC1 &= ~(1u << bit);
    }
}

void Internal_RefreshPin(uint16 pinNumber) {
    const ArcPort_PadConfigType * pin = &_configPtr->padConfig[pinNumber];

    // @req SWS_Port_00214
    if (pin->mode == PORT_PIN_MODE_DIO) {
        Internal_RefreshGioPin(pinNumber);
    } else if (pin->mode == PORT_PIN_MODE_DIO_SPI) {
        Internal_RefreshSpiGioPin(pinNumber);
    }
    else {
#if defined(CFG_TMS570LC43X)
        if (pin->regOffset != PORT_FUNC_USE_DEFAULT_SETTINGS)
        {
#if defined(PORT_PIN_MODE_SPI)
            if(pin->mode == PORT_PIN_MODE_SPI){
                /* For SPI the PINMMR mux is stored in the extra variables. */
                *(PINMMR_Port_Base[pin->extraOffset]) &= ~(0xFFu << ((pin->extraBit / 8u) * 8u));
                *(PINMMR_Port_Base[pin->extraOffset]) |= (1u << pin->extraBit);
            }else
#endif
            {
                *(PINMMR_Port_Base[pin->regOffset]) &= ~(0xFFu << ((pin->regBit / 8u) * 8u));
                *(PINMMR_Port_Base[pin->regOffset]) |= (1u << pin->regBit);
            }

        }

        /* The SPI pins will not be set up as SPI pins here, the SPI driver
         * will do it. It is not allowed to use SPI pins as DIOs if the unit
         * is used as SPI as well (meaning that even pins that are not used by the SPI
         * unit, for example an unused chip select, cannot be used as DIO). */

#elif defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
        *(PINMMR_Port_Base[pin->regOffset]) &= ~(0xFFu << ((pin->regBit / 8u) * 8u));
        *(PINMMR_Port_Base[pin->regOffset]) |= (1u << pin->regBit);
#else
#error MCU not defined.
#endif
    }
}

// @req SWS_Port_00140
void Port_Init(const Port_ConfigType *configType) {
    // @req SWS_Port_00105
    VALIDATE(configType != NULL, PORT_INIT_ID, PORT_E_PARAM_CONFIG);

    _configPtr = (Port_ConfigType *) configType;

    // Bring GIO register out of reset.
    gioREG->GCR0 = 1;

    *((uint32*)PORT_IOMM_KICK0) = PORT_IOMM_KICK0_MAGIC;
    *((uint32*)PORT_IOMM_KICK1) = PORT_IOMM_KICK1_MAGIC;


    // @req SWS_Port_00041
    for (uint16 i = 0; i < PORT_NR_PINS; i++) {
        Internal_RefreshPin(i);
    }

    _portState = PORT_INITIALIZED;

    *((uint32*)PORT_IOMM_KICK0) = 0x00000000;

}

// @req SWS_Port_00086
#if ( PORT_SET_PIN_DIRECTION_API == STD_ON )
// @req SWS_Port_00141
void Port_SetPinDirection( Port_PinType pinNr, Port_PinDirectionType direction )
{
    VALIDATE(_portState == PORT_INITIALIZED, PORT_SET_PIN_DIRECTION_ID, PORT_E_UNINIT);
    VALIDATE_PIN(pinNr, PORT_SET_PIN_DIRECTION_ID);

    const ArcPort_PadConfigType * pin= &_configPtr->padConfig[pinNr];
    Port_GioRegisterType *portReg = Gio_Port_Base[pin->regOffset];
    uint32 mask = GET_PIN_MASK(pin->regBit);

    // @req SWS_Port_00063
    if (direction == PORT_PIN_IN)
    {
        portReg->DIR &= ~mask;
    }
    else
    {
        portReg->DIR |= mask;
    }
}
#endif

// @req SWS_Port_00142
void Port_RefreshPortDirection(void) {
    // @req SWS_Port_00051
    VALIDATE(_portState == PORT_INITIALIZED, PORT_REFRESH_PORT_DIRECTION_ID, PORT_E_UNINIT);
    // @req SWS_Port_00060
    for (uint16 i = 0; i < PORT_NR_PINS; i++) {
        Internal_RefreshPin(i);
    }
}


#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versionInfo)
{
    //No need to check if initialized here, that requirement was removed
    VALIDATE(versionInfo != NULL, PORT_GET_VERSION_INFO_ID, PORT_E_PARAM_POINTER);
    memcpy(versionInfo, &_Port_VersionInfo, sizeof(Std_VersionInfoType));
}
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
// !req SWS_Port_00145
// !req SWS_Port_00125
// !req SWS_Port_00128
// !req SWS_Port_00223
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode) {

    /* Not supported! */
}
#endif
