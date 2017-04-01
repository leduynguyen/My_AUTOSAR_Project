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

#ifndef PORT_TMS570_H_
#define PORT_TMS570_H_

#if PORT_DEV_ERROR_DETECT == STD_ON
#define VALIDATE(_exp, _apiid, _errid) \
        if (!(_exp)) { \
            Det_ReportError(PORT_MODULE_ID, 0, _apiid, _errid); \
            return; \
        }

#define VALIDATE_PIN(_pin, _api) VALIDATE((_pin >= 0 && _pin < PORT_NR_PINS), _api, PORT_E_PARAM_PIN)

#else
#define VALIDATE(_exp, _apiid, _errid)
#define VALIDATE_PIN(_pin, _api)
#endif

#define GET_PIN_PORT(_pin) (_pin >> 8)
#define GET_PIN_PIN(_pin)  (_pin & 0x1F)
#define GET_PIN_MASK(_pin) (1 << (_pin & 0x1F))

#define PORT_PIN_DIO_SPIX_SHIFT		8u
#define PORT_PIN_DIO_SPIX_MASK		7u

typedef enum {
    PORT_UNINITIALIZED = 0, PORT_INITIALIZED,
} Port_StateType;

typedef volatile struct {
    uint32 DIR;
    uint32 DIN;
    uint32 DOUT;
    uint32 DSET;
    uint32 DCLR;
    uint32 PDR;
    uint32 PULDIS;
    uint32 PSL;
} Port_GioRegisterType;

typedef volatile struct {
    uint32 PC0; /* Sets Spi to GIO or SPI function */
    uint32 PC1; /* DIR    */
    uint32 PC2; /* DIN    */
    uint32 PC3; /* DOUT   */
    uint32 PC4; /* DSET   */
    uint32 PC5; /* DCLR   */
    uint32 PC6; /* PDR    */
    uint32 PC7; /* PULDIS */
    uint32 PC8; /* PSL    */
} Port_SpiControlRegisterType;

typedef volatile struct {
    uint32 HETGCR; 		/* 0x00 */
    uint32 HETPFR;		/* 0x04 */
    uint32 HETADDR;		/* 0x08 */
    uint32 HETOFF1;		/* 0x0C */
    uint32 HETOFF2;		/* 0x10 */
    uint32 HETINTENAS;	/* 0x14 */
    uint32 HETINTENAC; 	/* 0x18 */
    uint32 HETEXC1;		/* 0x1C */
    uint32 HETEXC2;		/* 0x20 */
    uint32 HETPRY;		/* 0x24 */
    uint32 HETFLG;		/* 0x28 */
    uint32 HETAND;		/* 0x2C */
    uint32 reserved1;	/* 0x30 */
    uint32 HETHRSH;		/* 0x34 */
    uint32 HETXOR;		/* 0x38 */
    uint32 HETREQENS;	/* 0x3C */
    uint32 HETREQENC; 	/* 0x40 */
    uint32 HETREQDS;	/* 0x44 */
    uint32 reserved2; 	/* 0x48 */
    uint32 HETDIR;		/* 0x4C */
    uint32 HETDIN;		/* 0x50 */
    uint32 HETDOUT;		/* 0x54 */
    uint32 HETDSET;		/* 0x58 */
    uint32 HETDCLR;		/* 0x5C */
    uint32 HETPDR;		/* 0x60 */
    uint32 HETPULDIS;	/* 0x64 */
    uint32 HETPSL;		/* 0x68 */
    uint32 reserved3[2];	/* 0x6C - 0x70 */
    uint32 HETPCR;		/* 0x74 */
    uint32 HETPAR;		/* 0x78 */
    uint32 HETPPR;		/* 0x7C */
    uint32 HETSFPRLD; 	/* 0x80 */
    uint32 HETSFENA;	/* 0x84 */
    uint32 reserved4;	/* 0x88 */
    uint32 HETLBPSEL;	/* 0x8C */
    uint32 HETLBPDIR;	/* 0x90 */
    uint32 HETPINDIS;	/* 0x94 */
} Port_N2HETControlRegisterType;


#define PORT_NOT_CONFIGURED 		0x00000000

#define GIO_BASE					0xFFF7BC00u
#define GIOA_OFFSET					0x34u
#define GIOB_OFFSET					0x54u

#define N2HET1_BASE					0xFFF7B800u
#define N2HET2_BASE					0xFFF7B900u
#define NHET_OFFSET					0x4Cu

#define N2HET1_FULL_REGISTER ((Port_N2HETControlRegisterType *)N2HET1_BASE)
#define N2HET2_FULL_REGISTER ((Port_N2HETControlRegisterType *)N2HET2_BASE)

#define PORT_GIO_0_BASE				((Port_GioRegisterType *) (GIO_BASE + GIOA_OFFSET))
#define PORT_GIO_1_BASE 			((Port_GioRegisterType *) (GIO_BASE + GIOB_OFFSET))
#define PORT_GIO_2_BASE 			((Port_GioRegisterType *) (N2HET1_BASE + NHET_OFFSET))
#define PORT_GIO_3_BASE 			((Port_GioRegisterType *) (N2HET2_BASE + NHET_OFFSET))
#define PORT_GIO_4_BASE 			((Port_GioRegisterType *) PORT_NOT_CONFIGURED)
#define PORT_GIO_5_BASE				((Port_GioRegisterType *) PORT_NOT_CONFIGURED)
#define PORT_GIO_6_BASE 			((Port_GioRegisterType *) PORT_NOT_CONFIGURED)
#define PORT_GIO_7_BASE 			((Port_GioRegisterType *) PORT_NOT_CONFIGURED)
#define PORT_GIO_8_BASE 			((Port_GioRegisterType *) PORT_NOT_CONFIGURED)
#define PORT_GIO_9_BASE 			((Port_GioRegisterType *) PORT_NOT_CONFIGURED)
#define PORT_GIO_10_BASE 			((Port_GioRegisterType *) PORT_NOT_CONFIGURED)
#define PORT_NUMBER_OF_PORTS 		11

#define MIBSPI1_BASE				0xFFF7F400u
#define MIBSPI2_BASE				0xFFF7F600u
#define MIBSPI3_BASE				0xFFF7F800u
#define MIBSPI4_BASE				0xFFF7FA00u
#define MIBSPI5_BASE				0xFFF7FC00u
#define SPIPC0_OFFSET				0x14u

#define PORT_SPI1_GIO_BASE			((Port_SpiControlRegisterType*) (MIBSPI1_BASE + SPIPC0_OFFSET))
#define PORT_SPI2_GIO_BASE			((Port_SpiControlRegisterType*) (MIBSPI2_BASE + SPIPC0_OFFSET))
#define PORT_SPI3_GIO_BASE			((Port_SpiControlRegisterType*) (MIBSPI3_BASE + SPIPC0_OFFSET))
#define PORT_SPI4_GIO_BASE			((Port_SpiControlRegisterType*) (MIBSPI4_BASE + SPIPC0_OFFSET))
#define PORT_SPI5_GIO_BASE			((Port_SpiControlRegisterType*) (MIBSPI5_BASE + SPIPC0_OFFSET))

#define SPI1GCR						((uint32_t*) MIBSPI1_BASE)
#define SPI2GCR						((uint32_t*) MIBSPI2_BASE)
#define SPI3GCR						((uint32_t*) MIBSPI3_BASE)
#define SPI4GCR						((uint32_t*) MIBSPI4_BASE)
#define SPI5GCR						((uint32_t*) MIBSPI5_BASE)


#ifdef CFG_TMS570LC43X
/* Output Pin Multiplexing Control Registers */
#define PINMMR0_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x110u))
#define PINMMR1_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x114u))
#define PINMMR2_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x118u))
#define PINMMR3_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x11Cu))
#define PINMMR4_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x120u))
#define PINMMR5_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x124u))
#define PINMMR6_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x128u))
#define PINMMR7_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x12Cu))
#define PINMMR8_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x130u))
#define PINMMR9_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x134u))
#define PINMMR10_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x138u))
#define PINMMR11_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x13Cu))
#define PINMMR12_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x140u))
#define PINMMR13_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x144u))
#define PINMMR14_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x148u))
#define PINMMR15_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x14Cu))
#define PINMMR16_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x150u))
#define PINMMR17_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x154u))
#define PINMMR18_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x158u))
#define PINMMR19_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x15Cu))
#define PINMMR20_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x160u))
#define PINMMR21_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x164u))
#define PINMMR22_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x168u))
#define PINMMR23_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x16Cu))
#define PINMMR24_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x170u))
#define PINMMR25_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x174u))
#define PINMMR26_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x178u))
#define PINMMR27_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x17Cu))
#define PINMMR28_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x180u))
#define PINMMR29_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x184u))
#define PINMMR30_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x188u))
#define PINMMR31_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x18Cu))
#define PINMMR32_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x190u))
#define PINMMR33_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x194u))
#define PINMMR34_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x198u))
#define PINMMR35_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x19Cu))
#define PINMMR36_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x1A0u))
#define PINMMR37_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x1A4u))

/* Input Pin Multiplexing Control Registers */
#define PINMMR80_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x250u))
#define PINMMR81_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x254u))
#define PINMMR82_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x258u))
#define PINMMR83_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x25cu))
#define PINMMR84_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x260u))
#define PINMMR85_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x264u))
#define PINMMR86_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x268u))
#define PINMMR87_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x26cu))
#define PINMMR88_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x270u))
#define PINMMR89_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x274u))
#define PINMMR90_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x278u))
#define PINMMR91_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x27cu))
#define PINMMR92_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x280u))
#define PINMMR93_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x284u))
#define PINMMR94_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x288u))
#define PINMMR95_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x28cu))
#define PINMMR96_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x290u))
#define PINMMR97_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x294u))
#define PINMMR98_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x298u))
#define PINMMR99_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x29cu))

/* Special Functionality Multiplexing Control Registers */
#define PINMMR160_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x390u))
#define PINMMR161_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x394u))
#define PINMMR162_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x398u))
#define PINMMR163_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x39cu))
#define PINMMR164_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x3a0u))
#define PINMMR165_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x3a4u))
#define PINMMR166_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x3a8u))
#define PINMMR167_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x3acu))
#define PINMMR168_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x3b0u))
#define PINMMR169_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x3b4u))
#define PINMMR170_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x3b8u))
#define PINMMR171_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x3bcu))
#define PINMMR172_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x3c0u))
#define PINMMR173_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x3c4u))
#define PINMMR174_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x3c8u))
#define PINMMR175_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x3ccu))
#define PINMMR176_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x3d0u))
#define PINMMR177_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x3d4u))
#define PINMMR178_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x3d8u))
#define PINMMR179_BASE_ADDR ((uint32 *)(IOMM_BASE_ADDR + 0x3dcu))

#elif defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
#define PINMMR0_BASE_ADDR ((uint32 *)0xFFFFEB10)
#define PINMMR1_BASE_ADDR ((uint32 *)0xFFFFEB14)
#define PINMMR2_BASE_ADDR ((uint32 *)0xFFFFEB18)
#define PINMMR3_BASE_ADDR ((uint32 *)0xFFFFEB1C)
#define PINMMR4_BASE_ADDR ((uint32 *)0xFFFFEB20)
#define PINMMR5_BASE_ADDR ((uint32 *)0xFFFFEB24)
#define PINMMR6_BASE_ADDR ((uint32 *)0xFFFFEB28)
#define PINMMR7_BASE_ADDR ((uint32 *)0xFFFFEB2C)
#define PINMMR8_BASE_ADDR ((uint32 *)0xFFFFEB30)
#define PINMMR9_BASE_ADDR ((uint32 *)0xFFFFEB34)
#define PINMMR10_BASE_ADDR ((uint32 *)0xFFFFEB38)
#define PINMMR11_BASE_ADDR ((uint32 *)0xFFFFEB3C)
#define PINMMR12_BASE_ADDR ((uint32 *)0xFFFFEB40)
#define PINMMR13_BASE_ADDR ((uint32 *)0xFFFFEB44)
#define PINMMR14_BASE_ADDR ((uint32 *)0xFFFFEB48)
#define PINMMR15_BASE_ADDR ((uint32 *)0xFFFFEB4C)
#define PINMMR16_BASE_ADDR ((uint32 *)0xFFFFEB50)
#define PINMMR17_BASE_ADDR ((uint32 *)0xFFFFEB54)
#define PINMMR18_BASE_ADDR ((uint32 *)0xFFFFEB58)
#define PINMMR19_BASE_ADDR ((uint32 *)0xFFFFEB5C)
#define PINMMR20_BASE_ADDR ((uint32 *)0xFFFFEB60)
#define PINMMR21_BASE_ADDR ((uint32 *)0xFFFFEB64)
#define PINMMR22_BASE_ADDR ((uint32 *)0xFFFFEB68)
#define PINMMR23_BASE_ADDR ((uint32 *)0xFFFFEB6C)
#define PINMMR24_BASE_ADDR ((uint32 *)0xFFFFEB70)
#define PINMMR25_BASE_ADDR ((uint32 *)0xFFFFEB74)
#define PINMMR26_BASE_ADDR ((uint32 *)0xFFFFEB78)
#define PINMMR27_BASE_ADDR ((uint32 *)0xFFFFEB7C)
#define PINMMR28_BASE_ADDR ((uint32 *)0xFFFFEB80)
#define PINMMR29_BASE_ADDR ((uint32 *)0xFFFFEB84)
#define PINMMR30_BASE_ADDR ((uint32 *)0xFFFFEB88)
#define PINMMR31_BASE_ADDR ((uint32 *)0xFFFFEB8C)
#define PINMMR32_BASE_ADDR ((uint32 *)0xFFFFEB90)
#define PINMMR33_BASE_ADDR ((uint32 *)0xFFFFEB94)
#define PINMMR34_BASE_ADDR ((uint32 *)0xFFFFEB98)
#define PINMMR35_BASE_ADDR ((uint32 *)0xFFFFEB9C)
#define PINMMR36_BASE_ADDR ((uint32 *)0xFFFFEBA0)
#define PINMMR37_BASE_ADDR ((uint32 *)0xFFFFEBA4)
#define PINMMR38_BASE_ADDR ((uint32 *)0xFFFFEBA8)
#define PINMMR39_BASE_ADDR ((uint32 *)0xFFFFEBAC)
#define PINMMR40_BASE_ADDR ((uint32 *)0xFFFFEBB0)
#define PINMMR41_BASE_ADDR ((uint32 *)0xFFFFEBB4)
#define PINMMR42_BASE_ADDR ((uint32 *)0xFFFFEBB8)
#define PINMMR43_BASE_ADDR ((uint32 *)0xFFFFEBBC)
#define PINMMR44_BASE_ADDR ((uint32 *)0xFFFFEBC0)
#define PINMMR45_BASE_ADDR ((uint32 *)0xFFFFEBC4)
#define PINMMR46_BASE_ADDR ((uint32 *)0xFFFFEBC8)
#define PINMMR47_BASE_ADDR ((uint32 *)0xFFFFEBCC)
#endif

#ifdef CFG_TMS570LC43X
#define PORT_IOMM_KICK0 (IOMM_BASE_ADDR + 0x38u)
#define PORT_IOMM_KICK1 (IOMM_BASE_ADDR + 0x3Cu)
#elif defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
#define PORT_IOMM_KICK0 0xFFFFEA38
#define PORT_IOMM_KICK1 0xFFFFEA3C
#endif

#define PORT_IOMM_KICK0_MAGIC (0x83e70b13)
#define PORT_IOMM_KICK1_MAGIC (0x95a4f1e0)

#endif /* PORT_TMS570_H_ */
