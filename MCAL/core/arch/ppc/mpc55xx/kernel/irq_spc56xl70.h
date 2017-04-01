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



#ifndef IRQ_SPC56XL70_H
#define IRQ_SPC56XL70_H


#define Irq_SOI()

/**
 * End-Of-Interrupt. Called by the OS it wants to clear the interrupt.
 */


#define INTC_SSCIR0_CLR0    0
#define INTC_SSCIR0_CLR1    1
#define INTC_SSCIR0_CLR2    2
#define INTC_SSCIR0_CLR3    3
#define INTC_SSCIR0_CLR4    4
#define INTC_SSCIR0_CLR5    5
#define INTC_SSCIR0_CLR6    6
#define INTC_SSCIR0_CLR7    7

#define DMA_CH0_INT         11
#define DMA_CH1_INT         12
#define DMA_CH2_INT         13
#define DMA_CH3_INT         14
#define DMA_CH4_INT         15
#define DMA_CH5_INT         16
#define DMA_CH6_INT         17
#define DMA_CH7_INT         18
#define DMA_CH8_INT         19
#define DMA_CH9_INT         20
#define DMA_CH10_INT        21
#define DMA_CH11_INT        22
#define DMA_CH12_INT        23
#define DMA_CH13_INT        24
#define DMA_CH14_INT        25
#define DMA_CH15_INT        26

#define SWT_TIMEOUT         28
//#define SWT_TIMEOUT         29

#define STM_CH0_INT         30
#define STM_CH1_INT         31
#define STM_CH2_INT         32
#define STM_CH3_INT         33

#define ECC_DBD_INT         35
#define ECC_SBC_INT         36

/* ME */
#define SAFE_MODE_INT       51
#define MODE_TRAS_INT       52
#define INV_MODE_INT        53
#define INV_MODE_CONF_INT   54

#define PIT_INT0            59
#define PIT_INT1            60
#define PIT_INT2            61

/* ADC */
#define ADC0_EOC_INT        62
#define ADC0_ER_INT         63
#define ADC0_WD_INT         64

#define FLEXCAN_0_ESR_ERR_INT   65
#define FLEXCAN_0_ESR_BOFF_INT  66

#define FLEXCAN_0_BUF_00_03 68
#define FLEXCAN_0_BUF_04_07	69
#define FLEXCAN_0_BUF_08_11	70
#define FLEXCAN_0_BUF_12_15	71
#define FLEXCAN_0_BUF_16_31	72

#define DSPI_0_ISR_TFUF_RFOF	74
#define DSPI_0_ISR_EOQF	75
#define DSPI_0_ISR_TFFF	76
#define DSPI_0_ISR_TCF	77
#define DSPI_0_ISR_RFDF	78

#define LINFLEX_0_RXI	79
#define LINFLEX_0_TXI	80
#define LINFLEX_0_ERR	81

#define ADC1_EOC_INT	82
#define ADC1_ER_INT	83
#define ADC1_WD_INT	84

#define FLEXCAN_1_ESR_ERR_INT	85
#define FLEXCAN_1_ESR_BOFF_INT	86

#define FLEXCAN_1_BUF_00_03	88
#define FLEXCAN_1_BUF_04_07	89
#define FLEXCAN_1_BUF_08_11	90
#define FLEXCAN_1_BUF_12_15	91
#define FLEXCAN_1_BUF_16_31	92

#define DSPI_1_ISR_TFUF_RFOF	94
#define DSPI_1_ISR_EOQF	95
#define DSPI_1_ISR_TFFF	96
#define DSPI_1_ISR_TCF	97
#define DSPI_1_ISR_RFDF	98

#define LINFLEX_1_RXI	99
#define LINFLEX_1_TXI	100
#define LINFLEX_1_ERR	101

#define FLEXCAN_2_ESR_ERR_INT   105
#define FLEXCAN_2_ESR_BOFF_INT  106

#define FLEXCAN_2_BUF_00_03 108
#define FLEXCAN_2_BUF_04_07 109
#define FLEXCAN_2_BUF_08_11 110
#define FLEXCAN_2_BUF_12_15 111
#define FLEXCAN_2_BUF_16_31 112

#define DSPI_2_ISR_TFUF_RFOF	114
#define DSPI_2_ISR_EOQF	115
#define DSPI_2_ISR_TFFF	116
#define DSPI_2_ISR_TCF	117
#define DSPI_2_ISR_RFDF	118

#define PIT_INT3	127

/* FlexPWM_0 */
#define PWM0_RF0	179
#define PWM0_COF0	180
#define PWM0_CAF0	181
#define PWM0_RF1	182
#define PWM0_COF1	183
#define PWM0_CAF1	184
#define PWM0_RF2	185
#define PWM0_COF2	186
#define PWM0_CAF2	187
#define PWM0_RF3	188
#define PWM0_COF3	189
#define PWM0_CAF3	190
#define PWM0_FFLAG	191
#define PWM0_REF	192

/* FlexPWM_1 */
#define FLEXPWM_1_BASE    233
#define PWM1_RF0    (FLEXPWM_1_BASE+0)
#define PWM1_COF0   (FLEXPWM_1_BASE+1)
#define PWM1_CAF0   (FLEXPWM_1_BASE+2)
#define PWM1_RF1    (FLEXPWM_1_BASE+3)
#define PWM1_COF1   (FLEXPWM_1_BASE+4)
#define PWM1_CAF1   (FLEXPWM_1_BASE+5)
#define PWM1_RF2    (FLEXPWM_1_BASE+6)
#define PWM1_COF2   (FLEXPWM_1_BASE+7)
#define PWM1_CAF2   (FLEXPWM_1_BASE+8)
#define PWM1_RF3    (FLEXPWM_1_BASE+9)
#define PWM1_COF3   (FLEXPWM_1_BASE+10)
#define PWM1_CAF3   (FLEXPWM_1_BASE+11)
#define PWM1_FFLAG  (FLEXPWM_1_BASE+12)
#define PWM1_REF    (FLEXPWM_1_BASE+13)

#define 	INTC_NUMBER_OF_INTERRUPTS               255
#define     NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS     INTC_NUMBER_OF_INTERRUPTS



typedef uint16 IrqType;

typedef enum
{
    PERIPHERAL_CLOCK_FLEXCAN_A,
    PERIPHERAL_CLOCK_FLEXCAN_B,
    PERIPHERAL_CLOCK_FLEXCAN_C,
    PERIPHERAL_CLOCK_FLEXCAN_D,
    PERIPHERAL_CLOCK_FLEXCAN_E,
    PERIPHERAL_CLOCK_FLEXCAN_F,
    PERIPHERAL_CLOCK_PIT,
    PERIPHERAL_CLOCK_DSPI_A,
    PERIPHERAL_CLOCK_DSPI_B,
    PERIPHERAL_CLOCK_DSPI_C,
    PERIPHERAL_CLOCK_DSPI_D,
    PERIPHERAL_CLOCK_DSPI_E,
    PERIPHERAL_CLOCK_DSPI_F,
#if defined(CFG_MPC560X)
    PERIPHERAL_CLOCK_EMIOS_0,
    PERIPHERAL_CLOCK_EMIOS_1,
#else
    PERIPHERAL_CLOCK_EMIOS,
#endif
    PERIPHERAL_CLOCK_ESCI_A,
    PERIPHERAL_CLOCK_ESCI_B,
    PERIPHERAL_CLOCK_ESCI_C,
    PERIPHERAL_CLOCK_ESCI_D,
    PERIPHERAL_CLOCK_ESCI_E,
    PERIPHERAL_CLOCK_ESCI_F,
    PERIPHERAL_CLOCK_ESCI_G,
    PERIPHERAL_CLOCK_ESCI_H,
    PERIPHERAL_CLOCK_LIN_A,
    PERIPHERAL_CLOCK_LIN_B,
    PERIPHERAL_CLOCK_LIN_C,
    PERIPHERAL_CLOCK_LIN_D,
    PERIPHERAL_CLOCK_IIC_A,
    PERIPHERAL_CLOCK_IIC_B,
    PERIPHERAL_CLOCK_MLB,
    PERIPHERAL_CLOCK_ADC_A,
    PERIPHERAL_CLOCK_FLEXPWM_0,
    PERIPHERAL_CLOCK_PIT_0,
    PERIPHERAL_CLOCK_PIT_1,
    PERIPHERAL_CLOCK_PIT_2,
    PERIPHERAL_CLOCK_PIT_3,
    PERIPHERAL_CLOCK_FEC_0,
} Mcu_Arc_PeriperalClock_t;


#if defined(CFG_MPC5516) || defined(CFG_MPC5606S)
#define CPU_Z1 	0
#define CPU_Z0	1
#endif

typedef enum
{
    CPU_CORE0,
    CPU_CORE1
} Cpu_t;

/* Offset from exceptions to interrupts */
#define IRQ_INTERRUPT_OFFSET		0

#endif /* IRQ_SPC56XL70_H */
