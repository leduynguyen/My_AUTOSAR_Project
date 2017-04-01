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
#define INTC_SSCIR0_CLR16   16
#define INTC_SSCIR0_CLR17   17
#define INTC_SSCIR0_CLR18   18
#define INTC_SSCIR0_CLR19   19
#define INTC_SSCIR0_CLR20   20
#define INTC_SSCIR0_CLR21   21
#define INTC_SSCIR0_CLR22   22
#define INTC_SSCIR0_CLR23   23
#define INTC_SSCIR0_CLR24   24
#define INTC_SSCIR0_CLR25   25
#define INTC_SSCIR0_CLR26   26
#define INTC_SSCIR0_CLR27   27
#define INTC_SSCIR0_CLR28   28
#define INTC_SSCIR0_CLR29   29
#define INTC_SSCIR0_CLR30   30
#define INTC_SSCIR0_CLR31   31

/* Platform watchdog */
#define MCM_MSWTIR_SWTIC0   32
#define MCM_MSWTIR_SWTIC1   33
#define MCM_MSWTIR_SWTIC2   34
#define MCM_MSWTIR_SWTIC3   35

/* Platform periodic timer */
#define STM0_CH0_INT        36
#define STM0_CH1_INT        37
#define STM0_CH2_INT        38
#define STM0_CH3_INT        39
#define STM1_CH0_INT        40
#define STM1_CH1_INT        41
#define STM1_CH2_INT        42
#define STM1_CH3_INT        43
#define STM2_CH0_INT        44
#define STM2_CH1_INT        45
#define STM2_CH2_INT        46
#define STM2_CH3_INT        47

/* 48-51 reserved */


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
#define EDMA_INTL_INT32     85
#define EDMA_INTL_INT33     86
#define EDMA_INTL_INT34     87
#define EDMA_INTL_INT35     88
#define EDMA_INTL_INT36     89
#define EDMA_INTL_INT37     90
#define EDMA_INTL_INT38     91
#define EDMA_INTL_INT39     92
#define EDMA_INTL_INT40     93
#define EDMA_INTL_INT41     94
#define EDMA_INTL_INT42     95
#define EDMA_INTL_INT43     96
#define EDMA_INTL_INT44     97
#define EDMA_INTL_INT45     98
#define EDMA_INTL_INT46     99
#define EDMA_INTL_INT47     100
#define EDMA_INTL_INT48     101
#define EDMA_INTL_INT49     102
#define EDMA_INTL_INT50     103
#define EDMA_INTL_INT51     104
#define EDMA_INTL_INT52     105
#define EDMA_INTL_INT53     106
#define EDMA_INTL_INT54     107
#define EDMA_INTL_INT55     108
#define EDMA_INTL_INT56     109
#define EDMA_INTL_INT57     110
#define EDMA_INTL_INT58     111
#define EDMA_INTL_INT59     112
#define EDMA_INTL_INT60     113
#define EDMA_INTL_INT61     114
#define EDMA_INTL_INT62     115
#define EDMA_INTL_INT63     116
#define EDMA_INTL_INT64     117
#define EDMA_INTL_INT65     118
#define EDMA_INTL_INT66     119
#define EDMA_INTL_INT67     120
#define EDMA_INTL_INT68     121
#define EDMA_INTL_INT69     122
#define EDMA_INTL_INT70     123
#define EDMA_INTL_INT71     124
#define EDMA_INTL_INT72     125
#define EDMA_INTL_INT73     126
#define EDMA_INTL_INT74     127
#define EDMA_INTL_INT75     128
#define EDMA_INTL_INT76     129
#define EDMA_INTL_INT77     130
#define EDMA_INTL_INT78     131
#define EDMA_INTL_INT79     132
#define EDMA_INTL_INT80     133
#define EDMA_INTL_INT81     134
#define EDMA_INTL_INT82     135
#define EDMA_INTL_INT83     136
#define EDMA_INTL_INT84     137
#define EDMA_INTL_INT85     138
#define EDMA_INTL_INT86     139
#define EDMA_INTL_INT87     140
#define EDMA_INTL_INT88     141
#define EDMA_INTL_INT89     114
#define EDMA_INTL_INT90     143
#define EDMA_INTL_INT91     144
#define EDMA_INTL_INT92     145
#define EDMA_INTL_INT93     146
#define EDMA_INTL_INT94     147
#define EDMA_INTL_INT95     148
#define EDMA_INTL_INT96     149
#define EDMA_INTL_INT97     150
#define EDMA_INTL_INT98     151
#define EDMA_INTL_INT99     152
#define EDMA_INTL_INT100    153
#define EDMA_INTL_INT101    154
#define EDMA_INTL_INT102    155
#define EDMA_INTL_INT103    156
#define EDMA_INTL_INT104    157
#define EDMA_INTL_INT105    158
#define EDMA_INTL_INT106    159
#define EDMA_INTL_INT107    160
#define EDMA_INTL_INT108    161
#define EDMA_INTL_INT109    162
#define EDMA_INTL_INT110    163
#define EDMA_INTL_INT111    164
#define EDMA_INTL_INT112    165
#define EDMA_INTL_INT113    166
#define EDMA_INTL_INT114    167
#define EDMA_INTL_INT115    168
#define EDMA_INTL_INT116    169
#define EDMA_INTL_INT117    170
#define EDMA_INTL_INT118    171
#define EDMA_INTL_INT119    172
#define EDMA_INTL_INT120    173
#define EDMA_INTL_INT121    174
#define EDMA_INTL_INT122    175
#define EDMA_INTL_INT123    176
#define EDMA_INTL_INT124    177
#define EDMA_INTL_INT125    178
#define EDMA_INTL_INT126    179
#define EDMA_INTL_INT127    180

/* Flash controller */
#define FLASH_IRQ0          185

/* 86-217 reserved */

/* Ethernet */
#define FEC_TX              218
#define FEC_RX              219
#define FEC_WORLD           220

/* Periodic interrupt timer */
#define PIT_INT0            226
#define PIT_INT1            227
#define PIT_INT2            228
#define PIT_INT3            229
#define PIT_INT4            230
#define PIT_INT5            231
#define PIT_INT6            232
#define PIT_INT7            233

/* 234-238 reserved */

#define PIT_0_RTI_TFLG      239
#define PIT_1_TFLG0         240
#define PIT_1_TFLG1         241
#define XOSC_CTREXPIRED     242
#define SIU_EISR_EIF0       243
#define SIU_EISR_EIF1       244

/* 245-250 reserved */

/* MC_ME */
#define ME_SAFE_MODE        251
#define ME_MODE_TRANS       252
#define ME_INVALID_MODE     253
#define ME_INVALID_MODE_CFG 254
#define ME_RESET_ALT_IRQ    255

/* 256-258 reserved */

/* SPI */
#define DSPI_0_ISR_OVER     259
#define DSPI_0_ISR_EOQF     260
#define DSPI_0_ISR_TFFF     261
#define DSPI_0_ISR_TCF      262
#define DSPI_0_ISR_RFDF     263
/* 264-265 reserved */
#define DSPI_0_ISR_SPEF     266
/* 267 reserved */
#define DSPI_1_ISR_OVER     268
#define DSPI_1_ISR_EOQF     269
#define DSPI_1_ISR_TFFF     270
#define DSPI_1_ISR_TCF      271
#define DSPI_1_ISR_RFDF     272
/* 273-274 reserved */
#define DSPI_1_ISR_SPEF     275
/* 276 reserved */
#define DSPI_2_ISR_OVER     277
#define DSPI_2_ISR_EOQF     278
#define DSPI_2_ISR_TFFF     279
#define DSPI_2_ISR_TCF      280
#define DSPI_2_ISR_RFDF     281
/* 282-283 reserved */
#define DSPI_2_ISR_SPEF     284
/* 285 reserved */
#define DSPI_3_ISR_OVER     286
#define DSPI_3_ISR_EOQF     287
#define DSPI_3_ISR_TFFF     288
#define DSPI_3_ISR_TCF      289
#define DSPI_3_ISR_RFDF     290
/* 291-292 reserved */
#define DSPI_3_ISR_SPEF     293
/* 294reserved */
#define DSPI_4_ISR_OVER     295
#define DSPI_4_ISR_EOQF     296
#define DSPI_4_ISR_TFFF     297
#define DSPI_4_ISR_TCF      298
#define DSPI_4_ISR_RFDF     299
#define DSPI_4_ISR_SPITCF   300
#define DSPI_4_ISR_DSITCF   301
#define DSPI_4_ISR_SPEF     302
#define DSPI_4_ISR_DDIF     303
#define DSPI_5_ISR_OVER     304
#define DSPI_5_ISR_EOQF     305
#define DSPI_5_ISR_TFFF     306
#define DSPI_5_ISR_TCF      307
#define DSPI_5_ISR_RFDF     308
#define DSPI_5_ISR_SPITCF   309
#define DSPI_5_ISR_DSITCF   310
#define DSPI_5_ISR_SPEF     311
#define DSPI_5_ISR_DDIF     312
#define DSPI_6_ISR_OVER     313
#define DSPI_6_ISR_EOQF     314
#define DSPI_6_ISR_TFFF     315
#define DSPI_6_ISR_TCF      316
#define DSPI_6_ISR_RFDF     317
#define DSPI_6_ISR_SPITCF   318
#define DSPI_6_ISR_DSITCF   319
#define DSPI_6_ISR_SPEF     320
#define DSPI_6_ISR_DDIF     321
/* 322-366 reserved */
#define DSPI_12_ISR_OVER    367
#define DSPI_12_ISR_EOQF    368
#define DSPI_12_ISR_TFFF    369
#define DSPI_12_ISR_TCF     370
#define DSPI_12_ISR_RFDF    371
/* 372-373 reserved */
#define DSPI_12_ISR_SPEF    374

/* 375 reserved */

/* LinFlex/eSCIO */
#define LINFLEX_0_RXI       376
#define LINFLEX_0_TXI       377
#define LINFLEX_0_ERR       378
/* 379 reserved */
#define LINFLEX_1_RXI       380
#define LINFLEX_1_TXI       381
#define LINFLEX_1_ERR       382
/* 383 reserved */
#define LINFLEX_2_RXI       384
#define LINFLEX_2_TXI       385
#define LINFLEX_2_ERR       386
/* 387-415 reserved */
#define LINFLEX_16_RXI      416
#define LINFLEX_16_TXI      417
#define LINFLEX_16_ERR      418
/* 419-431 reserved */
#define LINFLEX_14_RXI      432
#define LINFLEX_14_TXI      433
#define LINFLEX_14_ERR      434
/* 435reserved */
#define LINFLEX_15_RXI      436
#define LINFLEX_15_TXI      437
#define LINFLEX_15_ERR      438

/* 439 reserved */

/* I2C */
#define IRQ_I2C_A           440
/* 441 reserved */
#define IRQ_I2C_B           442

/* 443-452 reserved */

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
#define FLEXRAY_0_STPCLK    463
/* 464 reserved */
#define FLEXRAY_1_xLRNEIF   465
#define FLEXRAY_1_xLRCEIF   466
#define FLEXRAY_1_FNEAIF    467
#define FLEXRAY_1_FNEBIF    468
#define FLEXRAY_1_WUPIF     469
#define FLEXRAY_1_PRIF      470
#define FLEXRAY_1_CHIF      471
#define FLEXRAY_1_TBIF      472
#define FLEXRAY_1_RBIF      473
#define FLEXRAY_1_MIF       474
#define FLEXRAY_1_STPCLK    475

/* 476 reserved */

/* Power monitoring unit */
#define PMU_GLOB            478
#define PMU_TEMP            479

/* 479 reserved */

/* PLL */
#define PLL_0_SYNSR_LOLF    480
/* 481 reserved */
#define PLL_1_SYNSR_LOLF    482
/* 483 reserved */
#define PLL_0_SYNSR_EXTPDF  454
#define PLL_1_SYNSR_EXTPDF  485

/* 486-487 reserved */

/* FCCU */
#define FCCU_ALARM          488
#define FCCU_CFG_TIMEOUT    489
#define FCCU_RCCS0          490
#define FCCU_RCCS1          491

/* 491-493 reserved */

/* STCU */
#define STCU_RUNSW_LBIE     494
#define STCU_RUNSW_MBIE     495

/* Hardware security module */
#define HSM2HTIE_0          496
#define HSM2HTIE_1          497
#define HSM2HTIE_2          498
#define HSM2HTIE_3          499
#define HSM2HTIE_4          500
#define HSM2HTIE_5          501
#define HSM2HTIE_6          502
#define HSM2HTIE_7          503
#define HSM2HTIE_8          504
#define HSM2HTIE_9          505
#define HSM2HTIE_10         506
#define HSM2HTIE_11         507
#define HSM2HTIE_12         508
#define HSM2HTIE_13         509
#define HSM2HTIE_14         510
#define HSM2HTIE_15         511
#define HSM2HTIE_16         512
#define HSM2HTIE_17         513
#define HSM2HTIE_18         514
#define HSM2HTIE_19         515
#define HSM2HTIE_20         516
#define HSM2HTIE_21         517
#define HSM2HTIE_22         518
#define HSM2HTIE_23         519
#define HSM2HTIE_24         520
#define HSM2HTIE_25         521
#define HSM2HTIE_26         522
#define HSM2HTIE_27         523
#define HSM2HTIE_28         524
#define HSM2HTIE_29         525
#define HSM2HTIE_30         526
#define HSM2HTIE_31         527

/* SAR_ADC */
#define ADC0_EOC_INT        528
#define ADC1_EOC_INT        529
#define ADC2_EOC_INT        530
#define ADC3_EOC_INT        531
#define ADC4_EOC_INT        532
#define ADC5_EOC_INT        533
#define ADC6_EOC_INT        534
#define ADC7_EOC_INT        535
#define ADC8_EOC_INT        536
#define ADC9_EOC_INT        537
#define ADC10_EOC_INT       538
#define ADC11_EOC_INT       539
/* 540-542 reserved */
#define ADCB_EOC_INT        543

/* SD_ADC */
#define SD_ADC_0_INT        544
#define SD_ADC_1_INT        545
#define SD_ADC_2_INT        546
#define SD_ADC_3_INT        547
#define SD_ADC_4_INT        548
#define SD_ADC_5_INT        549
#define SD_ADC_6_INT        550
#define SD_ADC_7_INT        551
#define SD_ADC_8_INT        552
#define SD_ADC_9_INT        553

/* TTCAN */
#define M_TTCAN_0_0         677
#define M_TTCAN_0_1         678
#define M_TTCAN_0_2         679

/* 680-687 reserved */

/* CAN */
#define M_CAN_1_0           688
#define M_CAN_1_1           689
#define M_CAN_2_0           690
#define M_CAN_2_1           691
#define M_CAN_3_0           692
#define M_CAN_3_1           693
#define M_CAN_4_0           694
#define M_CAN_4_1           695

#define INTC_NUMBER_OF_INTERRUPTS   962
#define NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS INTC_NUMBER_OF_INTERRUPTS

typedef enum
{
    C_PBRIDGE,
    C_PLL0_PHI,
    C_PLL1_PHI,
    C_SYS_CLK,
    PERIPHERAL_CLOCK_M_CAN_1,
    PERIPHERAL_CLOCK_M_CAN_2,
    PERIPHERAL_CLOCK_M_CAN_3,
    PERIPHERAL_CLOCK_M_CAN_4,
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
    PERIPHERAL_CLOCK_STM_0,
}Mcu_Arc_PeriperalClock_t;

typedef enum
{
    CPU_CORE0,
    CPU_CORE1,
    CPU_CORE2
} Cpu_t;

/* Offset from exceptions to interrupts */
#define IRQ_INTERRUPT_OFFSET    0

#endif /* IRQ_MPC5777M_H_ */
