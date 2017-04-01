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

#ifndef IRQ_MPC5777M_H_
#define IRQ_MPC5777M_H_

#define Irq_SOI()

typedef uint16 IrqType;

/* Software interrupts. */
#define INTC_SSCIR0_CLR0    0
#define INTC_SSCIR0_CLR1    1
#define INTC_SSCIR0_CLR2    2
#define INTC_SSCIR0_CLR3    3
#define INTC_SSCIR0_CLR4    4
#define INTC_SSCIR0_CLR5    5
#define INTC_SSCIR0_CLR6    6
#define INTC_SSCIR0_CLR7    7
#define INTC_SSCIR0_CLR8    8
#define INTC_SSCIR0_CLR9    9
#define INTC_SSCIR0_CLR10   10
#define INTC_SSCIR0_CLR11   11
#define INTC_SSCIR0_CLR12   12
#define INTC_SSCIR0_CLR13   13
#define INTC_SSCIR0_CLR14   14
#define INTC_SSCIR0_CLR15   15

/* Platform watchdog */
#define MCM_MSWTIR_SWTIC0   32
#define MCM_MSWTIR_SWTIC1   33
#define MCM_MSWTIR_SWTIC2   34
#define MCM_MSWTIR_SWTIC3   35

/* eDMA */
#define EDMA_ERRL_ERR127_0  52
#define EDMA_INTL_INT0      53
#define EDMA_INTL_INT1      54
#define EDMA_INTL_INT2      55
#define EDMA_INTL_INT3      55
#define EDMA_INTL_INT4      57
#define EDMA_INTL_INT5      58
#define EDMA_INTL_INT6      59
#define EDMA_INTL_INT7      60
#define EDMA_INTL_INT8      61
#define EDMA_INTL_INT9      52
#define EDMA_INTL_INT10     63
#define EDMA_INTL_INT11     64
#define EDMA_INTL_INT12     65
#define EDMA_INTL_INT13     66
#define EDMA_INTL_INT14     67
#define EDMA_INTL_INT15     68
#define EDMA_INTL_INT16     69
#define EDMA_INTL_INT17     70
#define EDMA_INTL_INT18     71
#define EDMA_INTL_INT19     72
#define EDMA_INTL_INT20     73
#define EDMA_INTL_INT21     74
#define EDMA_INTL_INT22     75
#define EDMA_INTL_INT23     76
#define EDMA_INTL_INT24     77
#define EDMA_INTL_INT25     78
#define EDMA_INTL_INT26     79
#define EDMA_INTL_INT27     80
#define EDMA_INTL_INT28     81
#define EDMA_INTL_INT29     82
#define EDMA_INTL_INT30     83
#define EDMA_INTL_INT31     84

/* ETH 216 - 218  */

/* Periodic interrupt timer */
#define PIT_INT0            226
#define PIT_INT1            227
#define PIT_INT2            228
#define PIT_INT3            229
#define PIT_INT4            230
#define PIT_INT5            231
#define PIT_INT6            232
#define PIT_INT7            233

#define XOSC_CTREXPIRED     242
#define SIU_EISR_EIF0       243
#define SIU_EISR_EIF1       244

/* SPI */
#define DSPI_0_ISR_OVER     259
#define DSPI_0_ISR_EOQF     260
#define DSPI_0_ISR_TFFF     261
#define DSPI_0_ISR_TCF      262
#define DSPI_0_ISR_RFDF     263

#define DSPI_1_ISR_OVER     268
#define DSPI_1_ISR_EOQF     269
#define DSPI_1_ISR_TFFF     270
#define DSPI_1_ISR_TCF      271
#define DSPI_1_ISR_RFDF     272

#define DSPI_2_ISR_OVER     277
#define DSPI_2_ISR_EOQF     278
#define DSPI_2_ISR_TFFF     279
#define DSPI_2_ISR_TCF      280
#define DSPI_2_ISR_RFDF     281

#define DSPI_3_ISR_OVER     286
#define DSPI_3_ISR_EOQF     287
#define DSPI_3_ISR_TFFF     288
#define DSPI_3_ISR_TCF      289
#define DSPI_3_ISR_RFDF     290

/* LinFlex/eSCIO */
#define LINFLEX_0_RXI       376
#define LINFLEX_0_TXI       377
#define LINFLEX_0_ERR       378
/* 379 reserved */
#define LINFLEX_1_RXI       380
#define LINFLEX_1_TXI       381
#define LINFLEX_1_ERR       382

/* FlexRay */
#define FLEXRAY_0_xLRNEIF   453
#define FLEXRAY_0_xLRCEIF   454
#define FLEXRAY_0_FNEAIF    455
#define FLEXRAY_0_FNEBIF    456
#define FLEXRAY_0_WUPIF     457
#define FLEXRAY_0_PRIF      458
#define FLEXRAY_0_CHIF      459
#define FLEXRAY_0_TBIF      460
#define FLEXRAY_0_RBIF      461
#define FLEXRAY_0_MIF       462

/* FCCU */
#define FCCU_ALARM          488
#define FCCU_CFG_TIMEOUT    489

#define ADC0_EOC_INT               496
#define ADC0_ER_INT                497
#define ADC0_WD_INT                498

#define ADC1_EOC_INT               500
#define ADC1_ER_INT                501
#define ADC1_WD_INT                502

#define ADC2_EOC_INT               504
#define ADC2_ER_INT                505
#define ADC2_WD_INT                506

#define ADC3_EOC_INT               508
#define ADC3_ER_INT                509
#define ADC3_WD_INT                510

#define FLEXCAN_0_ESR_ERR_INT       520
#define FLEXCAN_0_ESR_BOFF_INT      521
#define FLEXCAN_0_BUF_00_03         522
#define FLEXCAN_0_BUF_04_07         523
#define FLEXCAN_0_BUF_08_11         524
#define FLEXCAN_0_BUF_12_15         525
#define FLEXCAN_0_BUF_16_31         526
#define FLEXCAN_0_BUF_32_39         527
#define FLEXCAN_0_BUF_40_47         528
#define FLEXCAN_0_BUF_48_55         529
#define FLEXCAN_0_BUF_56_63         530

#define FLEXCAN_1_ESR_ERR_INT       533
#define FLEXCAN_1_ESR_BOFF_INT      534
#define FLEXCAN_1_BUF_00_03         535
#define FLEXCAN_1_BUF_04_07         536
#define FLEXCAN_1_BUF_08_11         537
#define FLEXCAN_1_BUF_12_15         538
#define FLEXCAN_1_BUF_16_31         539
#define FLEXCAN_1_BUF_32_39         540
#define FLEXCAN_1_BUF_40_47         541
#define FLEXCAN_1_BUF_48_55         542
#define FLEXCAN_1_BUF_56_63         543

#define FLEXCAN_2_ESR_ERR_INT       546
#define FLEXCAN_2_ESR_BOFF_INT      547
#define FLEXCAN_2_BUF_00_03         548
#define FLEXCAN_2_BUF_04_07         549
#define FLEXCAN_2_BUF_08_11         550
#define FLEXCAN_2_BUF_12_15         551
#define FLEXCAN_2_BUF_16_31         552
#define FLEXCAN_2_BUF_32_39         553
#define FLEXCAN_2_BUF_40_47         554
#define FLEXCAN_2_BUF_48_55         555
#define FLEXCAN_2_BUF_56_63         556

/* SENT0 570-575 */

/* SENT1 582-587 */

/* eTimer */
#define ETIMER_0_TC0IR              611
#define ETIMER_0_TC1IR              612
#define ETIMER_0_TC2IR              613
#define ETIMER_0_TC3IR              614
#define ETIMER_0_TC4IR              615
#define ETIMER_0_TC5IR              616

#define ETIMER_0_WTIF               619

#define ETIMER_0_RCF                621

#define ETIMER_1_TC0IR              622
#define ETIMER_1_TC1IR              623
#define ETIMER_1_TC2IR              624
#define ETIMER_1_TC3IR              625
#define ETIMER_1_TC4IR              626
#define ETIMER_1_TC5IR              627

#define ETIMER_1_RCF                632

#define ETIMER_2_TC0IR              633
#define ETIMER_2_TC1IR              634
#define ETIMER_2_TC2IR              635
#define ETIMER_2_TC3IR              636
#define ETIMER_2_TC4IR              637
#define ETIMER_2_TC5IR              638

#define ETIMER_2_RCF                643

#define PWM0_RF0                    655
#define PWM0_COF0                   656
#define PWM0_CAF0                   657
#define PWM0_RF1                    658
#define PWM0_COF1                   659
#define PWM0_CAF1                   660
#define PWM0_RF2                    661
#define PWM0_COF2                   662
#define PWM0_CAF2                   663
#define PWM0_RF3                    664
#define PWM0_COF3                   665
#define PWM0_CAF3                   666
#define PWM0_FFLAG                  657
#define PWM0_REF                    668

#define PWM1_RF0                    670
#define PWM1_COF0                   671
#define PWM1_CAF0                   672
#define PWM1_RF1                    673
#define PWM1_COF1                   674
#define PWM1_CAF1                   675
#define PWM1_RF2                    676
#define PWM1_COF2                   677
#define PWM1_CAF2                   678
#define PWM1_RF3                    679
#define PWM1_COF3                   680
#define PWM1_CAF3                   681
#define PWM1_FFLAG                  682
#define PWM1_REF                    683

#define CTU_0_MRS_I                 700
#define CTU_0_T0_I                  701
#define CTU_0_T1_I                  702
#define CTU_0_T2_I                  703
#define CTU_0_T3_I                  704
#define CTU_0_T4_I                  705
#define CTU_0_T5_I                  706
#define CTU_0_T6_I                  707
#define CTU_0_T7_I                  708
#define CTU_0_FIFO0_I               709
#define CTU_0_FIFO1_I               710
#define CTU_0_FIFO2_I               711
#define CTU_0_FIFO3_I               712
#define CTU_0_ADC_I                 713
#define CTU_0_ERR_I                 714

#define CTU_1_MRS_I                 716
#define CTU_1_T0_I                  717
#define CTU_1_T1_I                  718
#define CTU_1_T2_I                  719
#define CTU_1_T3_I                  720
#define CTU_1_T4_I                  721
#define CTU_1_T5_I                  722
#define CTU_1_T6_I                  723
#define CTU_1_T7_I                  724
#define CTU_1_FIFO0_I               725
#define CTU_1_FIFO1_I               726
#define CTU_1_FIFO2_I               727
#define CTU_1_FIFO3_I               728
#define CTU_1_ADC_I                 729
#define CTU_1_ERR_I                 730

#define INTC_NUMBER_OF_INTERRUPTS   733
#define NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS INTC_NUMBER_OF_INTERRUPTS

typedef enum {
    C_PBRIDGE,
    C_PLL0_PHI,
    C_PLL1_PHI,
    C_SYS_CLK,
    PERIPHERAL_CLOCK_FLEXCAN_A,
    PERIPHERAL_CLOCK_FLEXCAN_B,
    PERIPHERAL_CLOCK_FLEXCAN_C,
    PERIPHERAL_CLOCK_FLEXCAN_D,
    PERIPHERAL_CLOCK_FLEXCAN_E,
    PERIPHERAL_CLOCK_FLEXCAN_F,
    PERIPHERAL_CLOCK_DSPI_A,
    PERIPHERAL_CLOCK_DSPI_B,
    PERIPHERAL_CLOCK_DSPI_C,
    PERIPHERAL_CLOCK_DSPI_D,
    PERIPHERAL_CLOCK_DSPI_E,
    PERIPHERAL_CLOCK_DSPI_F,
    PERIPHERAL_CLOCK_DSPI_6,
    PERIPHERAL_CLOCK_DSPI_12,
    PERIPHERAL_CLOCK_LIN_A,
    PERIPHERAL_CLOCK_LIN_B,
    PERIPHERAL_CLOCK_LIN_14,
    PERIPHERAL_CLOCK_LIN_15,
    PERIPHERAL_CLOCK_LIN_16,
    PERIPHERAL_CLOCK_PIT_0,
    PERIPHERAL_CLOCK_PIT_1,
    PERIPHERAL_CLOCK_PIT_2,
    PERIPHERAL_CLOCK_PIT_3,
    PERIPHERAL_CLOCK_FEC_0,
    PERIPHERAL_CLOCK_FLEXPWM_0,
    PERIPHERAL_CLOCK_STM_0,
} Mcu_Arc_PeriperalClock_t;


typedef enum {
    CPU_CORE0,
} Cpu_t;

/* Offset from exceptions to interrupts */
#define IRQ_INTERRUPT_OFFSET    0

#endif /* IRQ_MPC5777M_H_ */
