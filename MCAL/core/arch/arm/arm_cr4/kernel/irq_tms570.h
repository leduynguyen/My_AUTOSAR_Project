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

#ifndef IRQ_TMS570_H_
#define IRQ_TMS570_H_





#define IrqGetCurrentInterruptSource() \
    (((volatile sint8)vimREG->IRQIVEC) - 1)

#if 0
/** IrqActivateChannel turns the selected channel on in the VIM */
#define IrqActivateChannel(_c) \
    uint8 _ch1 = _c; \
    if (_ch1 > 31) { \
        vimREG->REQMASKSET1 |= (1 << (_ch1 - 32)); \
    } else { \
        vimREG->REQMASKSET0 |= (1 << _ch1); \
    }


/** IrqDeactivateChannel turns the selected channel off in the VIM */
#define IrqDeactivateChannel(_c) \
    uint8 _ch2 = _c; \
    if (_ch2 > 31) { \
        vimREG->REQMASKCLR1 = (1 << (_ch2 - 32)); \
    } else { \
        vimREG->REQMASKCLR0 = (1 << _ch2); \
    }
#endif

#define Irq_SOI()


/* Interrupts */
#define ESM_LEVEL_0  		0
#define RESERVED 			1
#define RTI_COMPARE_0		2
#define RTI_COMPARE_1		3
#define RTI_COMPARE_2		4
#define RTI_COMPARE_3		5
#define RTI_OVERFLOW_0		6
#define RTI_OVERFLOW_1		7
#define RTI_TIMEBASE		8
#define DIO_LEVEL_0			9
#define HET_LEVEL_0			10
#define HET_TU_LEVEL_0		11
#define MIBSP1_LEVEL_0		12
#define LIN1_LEVEL_0		13
#define MIBADC1_EVENT		14
#define MIBADC1_GROUP_1		15
#define CAN1_LEVEL_0		16
#define RESERVED_0			17
#define FR_LEVEL_0			18
#define CRC_1				19
#define ESM_LEVEL_1			20
#define SSI					21
#define PMU					22
#define DIO_LEVEL_1			23
#define HET_LEVEL_1			24
#define HET_TU_LEVEL_1		25
#define MIBSP1_LEVEL_1		26
#define LIN1_LEVEL_1		27
#define MIBADC1_GROUP_2		28
#define CAN1_LEVEL_1		29
#define RESERVED_1			30
#define MIBADC1_MAG			31
#define FR_LEVEL_1			32
#define DMA_FTCA			33
#define DMA_LFSA			34
#define CAN2_LEVEL_0		35
#define DMM_LEVEL_0			36
#define MIBSPI3_LEVEL_0		37
#define MIBSPI3_LEVEL_1		38
#define DMA_HBDC			39
#define DMA_BTCA			40
#define RESERVED_2			41
#define CAN2_LEVEL_1		42
#define DMM_LEVEL_1			43
#define CAN1_IF_3			44
#define CAN3_LEVEL_0		45
#define CAN2_IF_3			46
#define FPU					47
#define FR_TU_STATUS		48
#define LIN2_LEVEL_0		49
#define MIBADC2_EVENT		50
#define MIBADC2_GROUP_1		51
#define FR_TOC				52
#define MIBSPIP5_LEVEL_0	53
#define LIN2_LEVEL_1		54
#define CAN3_LEVEL_1		55
#define MIBSPI5_LEVEL_1		56
#define MIBADC2_GROUP_2		57
#define FR_TU_ERROR			58
#define MIBADC2_MAG			59
#define CAN3_IF_3			60
#define FR_TU_MPU			61
#define FR_T1C				62

#define CAN1_LVL0_INT 		16
#define CAN1_LVL1_INT 		29
#define CAN2_LVL0_INT 		35
#define CAN2_LVL1_INT 		42
#define CAN3_LVL0_INT 		45
#define CAN3_LVL1_INT 		55

#define PWM_CH1_INT 		90
#define PWM_CH2_INT		 	92
#define PWM_CH3_INT 		94
#define PWM_CH4_INT 		96
#define PWM_CH5_INT 		98
#define PWM_CH6_INT 		100
#define PWM_CH7_INT 		102

#define SPI1_LVL0_INT 		12
#define SPI1_LVL1_INT 		26
#define SPI2_LVL0_INT 		17
#define SPI2_LVL1_INT 		30
#define SPI3_LVL0_INT 		37
#define SPI3_LVL1_INT 		38
#define SPI4_LVL0_INT 		49
#define SPI4_LVL1_INT 		54
#define SPI5_LVL0_INT 		53
#define SPI5_LVL1_INT 		56
#define SPI_DMABTC_INT 		40


/* Total number of interrupts and exceptions
 */
#define NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS 127

/* Offset from start of exceptions to interrupts
 * Exceptions have negative offsets while interrupts have positive
 */
#define IRQ_INTERRUPT_OFFSET 0

typedef uint16 IrqType;

typedef enum {
    PERIPHERAL_CLOCK_AHB,
    PERIPHERAL_CLOCK_APB1,
    PERIPHERAL_CLOCK_APB2,
    PERIPHERAL_CLOCK_CAN,
    PERIPHERAL_CLOCK_PWM,
    PERIPHERAL_CLOCK_WDG,
    PERIPHERAL_CLOCK_FLASH,
    PERIPHERAL_CLOCK_RTICLK,
} Mcu_Arc_PeriperalClock_t;

typedef enum {
    CPU_0=0,
} Cpu_t;


#endif /* IRQ_TMS570_H_ */
