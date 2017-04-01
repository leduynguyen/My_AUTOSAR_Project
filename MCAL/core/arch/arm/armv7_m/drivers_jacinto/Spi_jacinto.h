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

#ifndef JACINTO_SPI_H_
#define JACINTO_SPI_H_

/* The MCSPI clock reference can be set to different values but maximum is 48MHz.
 * This can be scaled down further in the MCSPI module. */
#define MCSPI_CLOCK_MAX_HZ				48000000uL

/* Nbr of units in the hardware */
#define SPI_NBR_HW_UNITS				4u
#define MCSPI_NUM_HW_CHANNELS			4u

/* Interrupt service routines - See irq_jacinto.h and Mcu_Arc_Jacinto.c. */
ISR(Spi_Isr_0);
ISR(Spi_Isr_1);
ISR(Spi_Isr_2);
ISR(Spi_Isr_3);

#define MCSPI_ISR_PRIORITY				10uL


typedef union {
    vuint32_t R;
    struct {
        vuint32_t PHA:1;
        vuint32_t POL:1;
        vuint32_t CLKD:4;
        vuint32_t EPOL:1;
        vuint32_t WL:5;
        vuint32_t TRM:2;
        vuint32_t DMAW:1;
        vuint32_t DMAR:1;
        vuint32_t DPE0:1;
        vuint32_t DPE1:1;
        vuint32_t IS:1;
        vuint32_t TURBO:1;
        vuint32_t FORCE:1;
        vuint32_t SPIENSLV:2;
        vuint32_t SBE:1;
        vuint32_t SBPOL:1;
        vuint32_t TCS:2;
        vuint32_t FFEW:1;
        vuint32_t FFER:1;
        vuint32_t CLKG:1;
        vuint32_t :2;
    }B;
} SPI_CHnCONF_t;

typedef union {
    vuint32_t R;
    struct {
        vuint32_t RXS:1;
        vuint32_t TXS:1;
        vuint32_t EOT:1;	/* End of transfer */
        vuint32_t TXFFE:1;
        vuint32_t TXFFF:1;
        vuint32_t RXFFE:1;	/* 0 FIFO receive buffer is not empty, 1 FIFO receive buffer is empty. */
        vuint32_t RXFFF:1;	/* 0 FIFO receive buffer is not full, 1 FIFO receive buffer is full. */
        vuint32_t :25;
    }B;
} SPI_CHnSTAT_t;


typedef union {
    vuint32_t R;
    struct {
        vuint32_t SINGLE:1;
        vuint32_t PIN34:1;		/* 0 - SPI_SCS[n] is used as a chip select. */
        vuint32_t MS:1;
        vuint32_t SYSTEM_TEST:1;
        vuint32_t INITDLY:3;
        vuint32_t MOA:1;
        vuint32_t FDAA:1;
        vuint32_t :23;
    }B;
} SPI_MODULCTRL_t;

typedef union {
    vuint32_t R;
    struct {
        vuint32_t EN:1;
        vuint32_t :7;		/* 0 - SPI_SCS[n] is used as a chip select. */
        vuint32_t EXTCLK:8;
        vuint32_t :16;
    }B;
} SPI_CHnCTRL_t;


typedef union {
    vuint32_t R;
    struct {
        vuint32_t AEL:8;		/* Buffer almost empty. */
        vuint32_t AFL:8;		/* Buffer almost full. */
        vuint32_t WCNT:16;		/* SPI word counter */
    }B;
} SPI_XFERLEVEL_t;


typedef struct
{
    SPI_CHnCONF_t MCSPI_CHnCONF;		/* McSPI channel n configuration register */
    SPI_CHnSTAT_t MCSPI_CHnSTAT;		/* McSPI channel n status register */
    SPI_CHnCTRL_t MCSPI_CHnCTRL;		/* McSPI channel n control register */
    volatile uint32 MCSPI_TXn;			/* McSPI channel n FIFO transmit buffer register */
    volatile uint32 MCSPI_RXn;			/* McSPI channel n FIFO receive buffer register */
} MCSPI_CHn_Type;



typedef union {
    vuint32_t R;
    struct {
        vuint32_t TX0_EMPTY:1;		/* Transmitter register empty or almost empty. w1c */
        vuint32_t TX0_UNDERFLOW:1;  /* ... */
        vuint32_t RX0_FULL:1;
        vuint32_t RX0_OVERFLOW:1;
        vuint32_t TX1_EMPTY:1;
        vuint32_t TX1_UNDERFLOW:1;
        vuint32_t RX1_FULL:1;
        vuint32_t :1;
        vuint32_t TX2_EMPTY:1;
        vuint32_t TX2_UNDERFLOW:1;
        vuint32_t RX2_FULL:1;
        vuint32_t :1;
        vuint32_t TX3_EMPTY:1;
        vuint32_t TX3_UNDERFLOW:1;
        vuint32_t RX3_FULL:1;
        vuint32_t :1;
        vuint32_t :1;
        vuint32_t EOW:1;			/* End of word (EOW) count event when a channel is enabled using the
                                        FIFO buffer and the channel has sent the number of McSPI words
                                        defined by the MCSPI_XFERLEVEL[WCNT]. */
        vuint32_t :14;
    }B;
} SPI_IRQSTATUS_t;


typedef struct
{
    volatile uint32 *MCSPI_HL_REV;			/* Offset: 0x0uL   - McSPI IP revision register */
    volatile uint32 *MCSPI_HL_HWINFO;		/* Offset: 0x4uL   - McSPI IP hardware information register */
    volatile uint32 *MCSPI_HL_SYSCONFIG;	/* Offset: 0x10uL  - McSPI IP system configuration register  */
    volatile uint32 *MCSPI_REVISION;		/* Offset: 0x100uL - McSPI revision register  */
    volatile uint32 *MCSPI_SYSCONFIG;		/* Offset: 0x110uL - McSPI system configuration register  */
    volatile uint32 *MCSPI_SYSSTATUS;       /* Offset: 0x114uL - McSPI system status register  */
    volatile uint32 *MCSPI_IRQSTATUS;       /* Offset: 0x118uL - McSPI interrupt status register  */
    volatile uint32 *MCSPI_IRQENABLE;		/* Offset: 0x11CuL - McSPI interrupt enable register  */
    volatile uint32 *MCSPI_WAKEUPENABLE;    /* Offset: 0x120uL - McSPI wakeup enable register  */
    volatile uint32 *MCSPI_SYST;            /* Offset: 0x124uL - McSPI system test register  */
    volatile uint32 *MCSPI_MODULCTRL;       /* Offset: 0x128uL - McSPI module control register  */
    MCSPI_CHn_Type	*MCSPI_CHn;
    volatile uint32 *MCSPI_XFERLEVEL;		/* McSPI transfer levels register */
    volatile uint32 *MCSPI_DAFTX;			/* DMA address aligned FIFO transmitter register */
    volatile uint32 *MCSPI_DAFRX;			/* DMA address aligned FIFO receiver register */
} Spi_Internal_McSpiHwRegsType;

/* SPI register offsets */
/* MCSPI_CHnCONF */
#define MCSPI_CLKG_OFFSET				29uL
#define MCSPI_FFER_OFFSET				28uL
#define MCSPI_FFEW_OFFSET				27uL
#define MCSPI_FORCE_OFFSET				20uL
#define MCSPI_IS_DPE1_DPE0_OFFSET		16uL
#define MCSPI_TRM_OFFSET				12u
#define MCSPI_WL_OFFSET					7uL
#define MCSPI_EPOL_OFFSET				6uL
#define MCSPI_CLKD_OFFSET				2uL
#define MCSPI_POL_OFFSET				1uL
/* MCSPI_CHnCTRL */
#define MCSPI_EXTCLK_OFFSET				8uL
#define MCSPI_EN_OFFSET					0uL
/* MCSPI_SYSCONFIG */
#define MCSPI_SOFTRESET_OFFSET			1uL
/* MCSPI_IRQENABLE */
#define MCSPI_EOWKE_OFFSET				17uL
/* MCSPI_IRQSTATUS */
#define MCSPI_EOW_OFFSET				17uL
/* MCSPI_CHnSTAT */
#define MCSPI_CHnSTAT_RXFFE_OFFSET		5uL
#define MCSPI_CHnSTAT_TXFFE_OFFSET		3uL
#define MCSPI_EOT_OFFSET				2uL
/* MCSPI_XFERLEVEL */
#define MCSPI_WCNT_OFFSET				16uL
#define MCSPI_AFL_OFFSET				8uL


/* Settings */
#define MCSPI_FORCE						1uL
#define MCSPI_IS_DPE1_DPE0_DEFAULT_CFG	6uL
#define MCSPI_TRM_TX_RX_MODE			0uL
#define MCSPI_TRM_TX_ONLY_MODE			2uL
#define MCSPI_CLKD_DIVIDER_32768		0xFuL
#define SPI_DEFAULT_WORD_SIZE_8_BITS	7uL
#define MCSPI_SOFTRESET					1uL

/* Masks */
#define MCSPI_RESETDONE_MASK					1uL
#define MCSPI_CHnSTAT_EOT_MASK					(1uL << MCSPI_EOT_OFFSET)
//#define MCSPI_CHnSTAT_FIFO_TX_FIN_MASK		(MCSPI_CHnSTAT_EOT_MASK | (1uL << MCSPI_TXFFE_OFFSET))
#define MCSPI_IRQSTATUS_EOW_MASK				(1uL << MCSPI_EOW_OFFSET)
#define MCSPI_CHnCONF_WL_MASK					(0x1FuL << MCSPI_WL_OFFSET)
#define MCSPI_CHnCONF_FFEW_FFER_MASK			((1uL << MCSPI_FFER_OFFSET) | (1uL << MCSPI_FFEW_OFFSET))
//#define MCSPI_CHAN_SETTINGS_MASK				(~((3uL << MCSPI_TRM_OFFSET) | (0x1FuL << MCSPI_WL_OFFSET)))
#define MCSPI_CHAN_SETTINGS_MASK				(~(0x1FuL << MCSPI_WL_OFFSET))
#define MCSPI_CHAN_ACTIVE_MASK					1uL
#define MCSPI_IRQSTATUS_TXn_EMPTY_MASK(chan)	(1uL << (chan * 4uL))
#define MCSPI_IRQSTATUS_RXn_FULL_MASK(chan)		(1uL << (2uL + chan * 4uL))
#define MCSPI_IRQSTATUS_RX0_OVERFLOW_MASK		(1uL << 3uL)
#define MCSPI_CHnSTAT_RXFFE_MASK				(1 << MCSPI_CHnSTAT_RXFFE_OFFSET)
#define MCSPI_CHnSTAT_TXFFE_MASK				(1 << MCSPI_TXFFE_OFFSET)
#define MCSPI_CHnSTAT_RXS_MASK					1uL
#define MCSPI_SYST_SSB_MASK						(1uL << 11uL)
#define MCSPI_XFERLEVEL_WCNT_MASK				0xFFFF0000uL

/* IRQ masks */
#define MCSPI_IRQ_DISABLE_MASK			0x0uL
#define MCSPI_TXn_EMPTY_ENABLE			0x1uL
#define MCSPI_IRQ_ENABLE_REG0_MASK		0xFuL
#define MCSPI_IRQ_ENABLE_REG1_MASK		(0x7uL << 4uL)
#define MCSPI_IRQ_ENABLE_REG2_MASK		(0x7uL << 8uL)
#define MCSPI_IRQ_ENABLE_REG3_MASK		(0x7uL << 12uL)
#define MCSPI_IRQ_ENABLE_EOWKE_MASK		(1uL << 17uL)


#if (defined(CFG_JAC5) || defined(CFG_JAC5E))
#define MCSPI_IRQ_ENABLE_MASK			(MCSPI_IRQ_ENABLE_REG0_MASK | \
                                         MCSPI_IRQ_ENABLE_REG1_MASK | \
                                         MCSPI_IRQ_ENABLE_REG2_MASK | \
                                         MCSPI_IRQ_ENABLE_REG3_MASK | \
                                         MCSPI_IRQ_ENABLE_EOWKE_MASK)
#elif defined(CFG_JAC6)
#define MCSPI_IRQ_ENABLE_WKE_MASK		(1uL << 16uL)
#define MCSPI_IRQ_ENABLE_MASK			(MCSPI_IRQ_ENABLE_REG0_MASK | \
                                         MCSPI_IRQ_ENABLE_REG1_MASK | \
                                         MCSPI_IRQ_ENABLE_REG2_MASK | \
                                         MCSPI_IRQ_ENABLE_REG3_MASK | \
                                         MCSPI_IRQ_ENABLE_WKE_MASK  | \
                                         MCSPI_IRQ_ENABLE_EOWKE_MASK)
#else
#error MCU not configured.
#endif
#define MCSPI_IRQ_CLEAR_ALL_MASK		MCSPI_IRQ_ENABLE_MASK

/* SPI base addresses */
#if (defined(CFG_JAC5) || defined(CFG_JAC5E))
#define MCSPI1_BASE_ADDR				0x48030000uL	/* SPI0 */
#define MCSPI2_BASE_ADDR				0x481A0000uL	/* SPI1 */
#define MCSPI3_BASE_ADDR				0x481A2000uL	/* SPI2 */
#define MCSPI4_BASE_ADDR				0x481A4000uL	/* SPI3 */
#elif defined(CFG_JAC6)
#define MCSPI1_BASE_ADDR				(0x48098000uL + L3_OFFSET)
#define MCSPI2_BASE_ADDR				(0x4809A000uL + L3_OFFSET)
#define MCSPI3_BASE_ADDR				(0x480B8000uL + L3_OFFSET)
#define MCSPI4_BASE_ADDR				(0x480BA000uL + L3_OFFSET)
#else
#error MCU not defined.
#endif

/* Offsets from the base address for each SPI hw unit */
#define MCSPI_HL_REV_OFFSET             0x0uL      /* McSPI IP revision register  */
#define MCSPI_HL_HWINFO_OFFSET          0x4uL      /* McSPI IP hardware information register  */
#define MCSPI_HL_SYSCONFIG_OFFSET       0x10uL     /* McSPI IP system configuration register  */
#define MCSPI_REVISION_OFFSET           0x100uL    /* McSPI revision register  */
#define MCSPI_SYSCONFIG_OFFSET          0x110uL    /* McSPI system configuration register  */
#define MCSPI_SYSSTATUS_OFFSET          0x114uL    /* McSPI system status register  */
#define MCSPI_IRQSTATUS_OFFSET          0x118uL    /* McSPI interrupt status register  */
#define MCSPI_IRQENABLE_OFFSET          0x11CuL    /* McSPI interrupt enable register  */
#define MCSPI_WAKEUPENABLE_OFFSET       0x120uL    /* McSPI wakeup enable register  */
#define MCSPI_SYST_OFFSET               0x124uL    /* McSPI system test register  */
#define MCSPI_MODULCTRL_OFFSET          0x128uL    /* McSPI module control register  */
#define MCSPI_CH0CONF_OFFSET            0x12CuL    /* McSPI channel 0 configuration register  */
#define MCSPI_CH0STAT_OFFSET            0x130uL    /* McSPI channel 0 status register  */
#define MCSPI_CH0CTRL_OFFSET            0x134uL    /* McSPI channel 0 control register  */
#define MCSPI_TX0_OFFSET                0x138uL    /* McSPI channel 0 FIFO transmit buffer register  */
#define MCSPI_RX0_OFFSET                0x13CuL    /* McSPI channel 0 FIFO receive buffer register  */
#define MCSPI_CH1CONF_OFFSET            0x140uL    /* McSPI channel 1 configuration register  */
#define MCSPI_CH1STAT_OFFSET            0x144uL    /* McSPI channel 1 status register  */
#define MCSPI_CH1CTRL_OFFSET            0x148uL    /* McSPI channel 1 control register  */
#define MCSPI_TX1_OFFSET                0x14CuL    /* McSPI channel 1 FIFO transmit buffer register  */
#define MCSPI_RX1_OFFSET                0x150uL    /* McSPI channel 1 FIFO receive buffer register  */
#define MCSPI_CH2CONF_OFFSET            0x154uL    /* McSPI channel 2 configuration register  */
#define MCSPI_CH2STAT_OFFSET            0x158uL    /* McSPI channel 2 status register  */
#define MCSPI_CH2CTRL_OFFSET            0x15CuL    /* McSPI channel 2 control register  */
#define MCSPI_TX2_OFFSET                0x160uL    /* McSPI channel 2 FIFO transmit buffer register  */
#define MCSPI_RX2_OFFSET                0x164uL    /* McSPI channel 2 FIFO receive buffer register  */
#define MCSPI_CH3CONF_OFFSET            0x168uL    /* McSPI channel 3 configuration register  */
#define MCSPI_CH3STAT_OFFSET            0x16CuL    /* McSPI channel 3 status register register  */
#define MCSPI_CH3CTRL_OFFSET            0x170uL    /* McSPI channel 3 control register  */
#define MCSPI_TX3_OFFSET                0x174uL    /* McSPI channel 3 FIFO transmit buffer register  */
#define MCSPI_RX3_OFFSET                0x178uL    /* McSPI channel 3 FIFO receive buffer register  */
#define MCSPI_XFERLEVEL_OFFSET          0x17CuL    /* McSPI transfer levels register  */
#if (defined(CFG_JAC5) || defined(CFG_JAC5E))
#define MCSPI_DAFTX_OFFSET              0x180uL    /* DMA address aligned FIFO transmitter register  */
#define MCSPI_DAFRX_OFFSET              0x1A0uL    /* DMA address aligned FIFO receiver register  */
#endif

#endif /* JACINTO_SPI_H_ */
