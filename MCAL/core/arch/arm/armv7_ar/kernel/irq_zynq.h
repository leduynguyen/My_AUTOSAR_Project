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

#ifndef IRQ_ZYNQ_H_
#define IRQ_ZYNQ_H_

/* SGI */
#define IRQ_SOFTWARE_0	        0
#define IRQ_SOFTWARE_1	        1
#define IRQ_SOFTWARE_2	        2
#define IRQ_SOFTWARE_3	        3
#define IRQ_SOFTWARE_4	        4
#define IRQ_SOFTWARE_5	        5
#define IRQ_SOFTWARE_6	        6
#define IRQ_SOFTWARE_7	        7
#define IRQ_SOFTWARE_8	        8
#define IRQ_SOFTWARE_9	        9
#define IRQ_SOFTWARE_10	        10
#define IRQ_SOFTWARE_11	        11
#define IRQ_SOFTWARE_12	        12
#define IRQ_SOFTWARE_13	        13
#define IRQ_SOFTWARE_14	        14
#define IRQ_SOFTWARE_15	        15

/* PPI */
#define IRQ_GLOBAL_TIMER		27
#define IRQ_FIQ					28
#define IRQ_CPU_PRIVATE_TIMER	29
#define IRQ_AWDT_0_1			30
#define IRQ_IRQ					31

/* SPI */
#define	IRQ_CPU_0				32
#define	IRQ_CPU_1				33
#define	IRQ_L2_CACHE			34
#define	IRQ_OCM					35
#define	IRQ_PMU_0				37
#define	IRQ_PMU_1				38
#define IRQ_XADC				39
#define IRQ_DEVC				40
#define IRQ_SWDT				41
#define IRQ_TTC_0_0				42
#define IRQ_TTC_0_1				43
#define IRQ_TTC_0_2				44
#define IRQ_DMAC_ABORT			45
#define IRQ_DMAC_0				46
#define IRQ_DMAC_1				47
#define IRQ_DMAC_2				48
#define IRQ_DMAC_3				49
#define IRQ_SMC					50
#define IRQ_QUAD_SPI			51
#define IRQ_GPIO				52
#define IRQ_USB_0				53
#define IRQ_ETH_0				54
#define IRQ_ETH_0_WKUP			55
#define IRQ_SDIO_0				56
#define IRQ_I2C_0				57
#define IRQ_SPI_0				58
#define IRQ_UART_0				59
#define IRQ_CAN_0				60
#define IRQ_PL_0				61
#define IRQ_PL_1				62
#define IRQ_PL_2				63
#define IRQ_PL_3				64
#define IRQ_PL_4				65
#define IRQ_PL_5				66
#define IRQ_PL_6				67
#define IRQ_PL_7				68
#define IRQ_TTC_1_0				69
#define IRQ_TTC_1_1				70
#define IRQ_TTC_1_2				71
#define IRQ_DMAC_4				72
#define IRQ_DMAC_5				73
#define IRQ_DMAC_6				74
#define IRQ_DMAC_7				75
#define IRQ_USB_1				76
#define IRQ_ETH_1				77
#define IRQ_ETH_1_WKUP			78
#define IRQ_SDIO_1				79
#define IRQ_I2C_1				80
#define IRQ_SPI_1				81
#define IRQ_UART_1				82
#define IRQ_CAN_1				83
#define IRQ_PL_8				84
#define IRQ_PL_9				85
#define IRQ_PL_10				86
#define IRQ_PL_11				87
#define IRQ_PL_12				88
#define IRQ_PL_13				89
#define IRQ_PL_14				90
#define IRQ_PL_15				91
#define IRQ_PARITY				92

#define IRQ_CNT					96
#define IRQ_SPI_CNT				64

#define NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS		IRQ_CNT
#define IRQ_INTERRUPT_OFFSET					0

#define Irq_SOI()

typedef uint8_t Cpu_t;
typedef uint16 IrqType;

#endif /* IRQ_ZYNQ_H_ */
