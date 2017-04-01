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

/* IRQ headerfile for:
 *   CFG_MPC5567
 *
 *  mpc5567  - TRM : 10.4.1 Interrupt Request Sources
 *
 */

#ifndef IRQ_MPC5XXX_1_H
#define IRQ_MPC5XXX_1_H
#define Irq_SOI()


    /* Software interrupts. */
#define INTC_SSCIR0_CLR0                         0
#define INTC_SSCIR0_CLR1                         1
#define INTC_SSCIR0_CLR2                         2
#define INTC_SSCIR0_CLR3                         3
#define INTC_SSCIR0_CLR4                         4
#define INTC_SSCIR0_CLR5                         5
#define INTC_SSCIR0_CLR6                         6
#define INTC_SSCIR0_CLR7                         7
#define MCM_MSWTIR_SWTIC                         8
#define ECC_ERROR                                9
        /* eDMA */
#define EDMA_ERRL_ERR31_0                        10
#define EDMA_INTL_INT0                           11
#define EDMA_INTL_INT1                           12
#define EDMA_INTL_INT2                           13
#define EDMA_INTL_INT3                           14
#define EDMA_INTL_INT4                           15
#define EDMA_INTL_INT5                           16
#define EDMA_INTL_INT6                           17
#define EDMA_INTL_INT7                           18
#define EDMA_INTL_INT8                           19
#define EDMA_INTL_INT9                           20
#define EDMA_INTL_INT10                          21
#define EDMA_INTL_INT11                          22
#define EDMA_INTL_INT12                          23
#define EDMA_INTL_INT13                          24
#define EDMA_INTL_INT14                          25
#define EDMA_INTL_INT15                          26

    /* DMA INT15-INT31 also here , 27 -> 42 */

#define PLL_SYNSR_LOCF                           43
#define PLL_SYNSR_LOLF                           44
#define SIU_OSR_OVER                             45
        /* External interrupts */
#define SIU_EISR_EIF0                            46
#define SIU_EISR_EIF1                            47
#define SIU_EISR_EIF2                            48
#define SIU_EISR_EIF3                            49
#define SIU_EISR_EIF15_4                         50

        /* eMIOS */
#define EMISOS200_FLAG_F0                        51
#define EMISOS200_FLAG_F1                        52
#define EMISOS200_FLAG_F2                        53
#define EMISOS200_FLAG_F3                        54
#define EMISOS200_FLAG_F4                        55
#define EMISOS200_FLAG_F5                        56
#define EMISOS200_FLAG_F6                        57
#define EMISOS200_FLAG_F7                        58
#define EMISOS200_FLAG_F8                        59
#define EMISOS200_FLAG_F9                        60
#define EMISOS200_FLAG_F10                       61
#define EMISOS200_FLAG_F11                       62
#define EMISOS200_FLAG_F12                       63
#define EMISOS200_FLAG_F13                       64
#define EMISOS200_FLAG_F14                       65
#define EMISOS200_FLAG_F15                       66

#define ETPU_GLOBAL                              67
#define ETPU_A_CIS_0                             68
#define ETPU_A_CIS_1                             69
#define ETPU_A_CIS_2                             70
#define ETPU_A_CIS_3                             71
#define ETPU_A_CIS_4                             72
#define ETPU_A_CIS_5                             73
#define ETPU_A_CIS_6                             74
#define ETPU_A_CIS_7                             75
#define ETPU_A_CIS_8                             76
#define ETPU_A_CIS_9                             77
#define ETPU_A_CIS_10                            78
#define ETPU_A_CIS_11                            79
#define ETPU_A_CIS_12                            80
#define ETPU_A_CIS_13                            81
#define ETPU_A_CIS_14                            82
#define ETPU_A_CIS_15                            83
#define ETPU_A_CIS_16                            84
#define ETPU_A_CIS_17                            85
#define ETPU_A_CIS_18                            86
#define ETPU_A_CIS_19                            87
#define ETPU_A_CIS_20                            88
#define ETPU_A_CIS_21                            89
#define ETPU_A_CIS_22                            90
#define ETPU_A_CIS_23                            91
#define ETPU_A_CIS_24                            92
#define ETPU_A_CIS_25                            93
#define ETPU_A_CIS_26                            94
#define ETPU_A_CIS_27                            95
#define ETPU_A_CIS_28                            96
#define ETPU_A_CIS_29                            97
#define ETPU_A_CIS_30                            98
#define ETPU_A_CIS_31                            99

/* eQADC */
#define EQADC_FISR_OVER                          100
#define EQADC_FISR0_NCF0                         101
#define EQADC_FISR0_PF0                          102
#define EQADC_FISR0_EOQF0                        103
#define EQADC_FISR0_CFFF0                        104
#define EQADC_FISR0_RFDF0                        105
#define EQADC_FISR1_NCF1                         106
#define EQADC_FISR1_PF1                          107
#define EQADC_FISR1_EOQF1                        108
#define EQADC_FISR1_CFFF1                        109
#define EQADC_FISR1_RFDF1                        110
#define EQADC_FISR2_NCF2                         111
#define EQADC_FISR2_PF2                          112
#define EQADC_FISR2_EOQF2                        113
#define EQADC_FISR2_CFFF2                        114
#define EQADC_FISR2_RFDF2                        115
#define EQADC_FISR3_NCF3                         116
#define EQADC_FISR3_PF3                          117
#define EQADC_FISR3_EOQF3                        118
#define EQADC_FISR3_CFFF3                        119
#define EQADC_FISR3_RFDF3                        120
#define EQADC_FISR4_NCF4                         121
#define EQADC_FISR4_PF4                          122
#define EQADC_FISR4_EOQF4                        123
#define EQADC_FISR4_CFFF4                        124
#define EQADC_FISR4_RFDF4                        125
#define EQADC_FISR5_NCF5                         126
#define EQADC_FISR5_PF5                          127
#define EQADC_FISR5_EOQF5                        128
#define EQADC_FISR5_CFFF5                        129
#define EQADC_FISR5_RFDF5                        130

#define DSPI_B_COMB                              131
#define DSPI_B_ISR_EOQF                          132
#define DSPI_B_ISR_TFFF                          133
#define DSPI_B_ISR_TCF                           134
#define DSPI_B_ISR_RFDF                          135
#define DSPI_C_COMB                              136
#define DSPI_C_ISR_EOQF                          137
#define DSPI_C_ISR_TFFF                          138
#define DSPI_C_ISR_TCF                           139
#define DSPI_C_ISR_RFDF                          140
#define DSPI_D_COMB                              141
#define DSPI_D_ISR_EOQF                          142
#define DSPI_D_ISR_TFFF                          143
#define DSPI_D_ISR_TCF                           144
#define DSPI_D_ISR_RFDF                          145

#define ESCI_A_COMB                              146
#define ESCI_B_COMB                              149
#define IRQ_RESERVED2                            150
#define IRQ_RESERVED3                            151

        /* FlexCAN A */
#define FLEXCAN_A_ESR_BOFF_INT                   152
#define FLEXCAN_A_ESR_ERR_INT                    153
#define IRQ_RESERVED18                           154
#define FLEXCAN_A_IFLAG1_BUF0I                   155
#define FLEXCAN_A_IFLAG1_BUF1I                   156
#define FLEXCAN_A_IFLAG1_BUF2I                   157
#define FLEXCAN_A_IFLAG1_BUF3I                   158
#define FLEXCAN_A_IFLAG1_BUF4I                   159
#define FLEXCAN_A_IFLAG1_BUF5I                   160
#define FLEXCAN_A_IFLAG1_BUF6I                   161
#define FLEXCAN_A_IFLAG1_BUF7I                   162
#define FLEXCAN_A_IFLAG1_BUF8I                   163
#define FLEXCAN_A_IFLAG1_BUF9I                   164
#define FLEXCAN_A_IFLAG1_BUF10I                  165
#define FLEXCAN_A_IFLAG1_BUF11I                  166
#define FLEXCAN_A_IFLAG1_BUF12I                  167
#define FLEXCAN_A_IFLAG1_BUF13I                  168
#define FLEXCAN_A_IFLAG1_BUF14I                  169
#define FLEXCAN_A_IFLAG1_BUF15I                  170
#define FLEXCAN_A_IFLAG1_BUF31_16I               171
#define FLEXCAN_A_IFLAG1_BUF63_32I               172

        /* FlexCAN C */
#define FLEXCAN_C_ESR_BOFF_INT                   173
#define FLEXCAN_C_ESR_ERR_INT                    174
#define IRQ_RESERVED20                           175
#define FLEXCAN_C_IFLAG1_BUF0I                   176
#define FLEXCAN_C_IFLAG1_BUF1I                   177
#define FLEXCAN_C_IFLAG1_BUF2I                   178
#define FLEXCAN_C_IFLAG1_BUF3I                   179
#define FLEXCAN_C_IFLAG1_BUF4I                   180
#define FLEXCAN_C_IFLAG1_BUF5I                   181
#define FLEXCAN_C_IFLAG1_BUF6I                   182
#define FLEXCAN_C_IFLAG1_BUF7I                   183
#define FLEXCAN_C_IFLAG1_BUF8I                   184
#define FLEXCAN_C_IFLAG1_BUF9I                   185
#define FLEXCAN_C_IFLAG1_BUF10I                  186
#define FLEXCAN_C_IFLAG1_BUF11I                  187
#define FLEXCAN_C_IFLAG1_BUF12I                  188
#define FLEXCAN_C_IFLAG1_BUF13I                  189
#define FLEXCAN_C_IFLAG1_BUF14I                  190
#define FLEXCAN_C_IFLAG1_BUF15I                  191
#define FLEXCAN_C_IFLAG1_BUF31_16I               192
#define FLEXCAN_C_IFLAG1_BUF63_32I               193

#define FEC_TX                                   194
#define FEC_RX                                   195
#define FEC_WORLD                                196

   /* FlexCAN B */
#define FLEXCAN_B_ESR_BOFF_INT                   280
#define FLEXCAN_B_ESR_ERR_INT                    281
#define IRQ_RESERVED21                           282
#define FLEXCAN_B_IFLAG1_BUF0I                   283
#define FLEXCAN_B_IFLAG1_BUF1I                   284
#define FLEXCAN_B_IFLAG1_BUF2I                   285
#define FLEXCAN_B_IFLAG1_BUF3I                   286
#define FLEXCAN_B_IFLAG1_BUF4I                   287
#define FLEXCAN_B_IFLAG1_BUF5I                   288
#define FLEXCAN_B_IFLAG1_BUF6I                   289
#define FLEXCAN_B_IFLAG1_BUF7I                   290
#define FLEXCAN_B_IFLAG1_BUF8I                   291
#define FLEXCAN_B_IFLAG1_BUF9I                   292
#define FLEXCAN_B_IFLAG1_BUF10I                  293
#define FLEXCAN_B_IFLAG1_BUF11I                  294
#define FLEXCAN_B_IFLAG1_BUF12I                  295
#define FLEXCAN_B_IFLAG1_BUF13I                  296
#define FLEXCAN_B_IFLAG1_BUF14I                  297
#define FLEXCAN_B_IFLAG1_BUF15I                  298
#define FLEXCAN_B_IFLAG1_BUF31_16I               299
#define FLEXCAN_B_IFLAG1_BUF63_32I               300

        /* FlexCAN D */
#define FLEXCAN_D_ESR_BOFF_INT                   308
#define FLEXCAN_D_ESR_ERR_INT                    309
#define IRQ_RESERVED22                           310
#define FLEXCAN_D_IFLAG1_BUF0I                   311
#define FLEXCAN_D_IFLAG1_BUF1I                   312
#define FLEXCAN_D_IFLAG1_BUF2I                   313
#define FLEXCAN_D_IFLAG1_BUF3I                   314
#define FLEXCAN_D_IFLAG1_BUF4I                   315
#define FLEXCAN_D_IFLAG1_BUF5I                   316
#define FLEXCAN_D_IFLAG1_BUF6I                   317
#define FLEXCAN_D_IFLAG1_BUF7I                   318
#define FLEXCAN_D_IFLAG1_BUF8I                   319
#define FLEXCAN_D_IFLAG1_BUF9I                   320
#define FLEXCAN_D_IFLAG1_BUF10I                  321
#define FLEXCAN_D_IFLAG1_BUF11I                  322
#define FLEXCAN_D_IFLAG1_BUF12I                  323
#define FLEXCAN_D_IFLAG1_BUF13I                  324
#define FLEXCAN_D_IFLAG1_BUF14I                  325
#define FLEXCAN_D_IFLAG1_BUF15I                  326
#define FLEXCAN_D_IFLAG1_BUF31_16I               327
#define FLEXCAN_D_IFLAG1_BUF63_32I               328

        /* FlexCAN E */
#define FLEXCAN_E_ESR_BOFF_INT                   329
#define FLEXCAN_E_ESR_ERR_INT                    330
#define IRQ_RESERVED23                           331
#define FLEXCAN_E_IFLAG1_BUF0I                   332
#define FLEXCAN_E_IFLAG1_BUF1I                   333
#define FLEXCAN_E_IFLAG1_BUF2I                   334
#define FLEXCAN_E_IFLAG1_BUF3I                   335
#define FLEXCAN_E_IFLAG1_BUF4I                   336
#define FLEXCAN_E_IFLAG1_BUF5I                   337
#define FLEXCAN_E_IFLAG1_BUF6I                   338
#define FLEXCAN_E_IFLAG1_BUF7I                   339
#define FLEXCAN_E_IFLAG1_BUF8I                   340
#define FLEXCAN_E_IFLAG1_BUF9I                   341
#define FLEXCAN_E_IFLAG1_BUF10I                  342
#define FLEXCAN_E_IFLAG1_BUF11I                  343
#define FLEXCAN_E_IFLAG1_BUF12I                  344
#define FLEXCAN_E_IFLAG1_BUF13I                  345
#define FLEXCAN_E_IFLAG1_BUF14I                  346
#define FLEXCAN_E_IFLAG1_BUF15I                  347
#define FLEXCAN_E_IFLAG1_BUF31_16I               348
#define FLEXCAN_E_IFLAG1_BUF63_32I               349



    /* Flexray */
#define FLEXRAY_MIF                              350
#define FLEXRAY_PRIF                             351
#define FLEXRAY_CHIF                             352
#define FLEXRAY_WUP_IF                           353
#define FLEXRAY_FBNE_F                           354
#define FLEXRAY_FANE_F                           355
#define FLEXRAY_RBIF                             356
#define FLEXRAY_TBIF                             357

#define INTC_NUMBER_OF_INTERRUPTS                361

#define NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS INTC_NUMBER_OF_INTERRUPTS

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
    PERIPHERAL_CLOCK_EMIOS,
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

typedef enum
{
    CPU_CORE0
} Cpu_t;

/* Offset from exceptions to interrupts */
#define IRQ_INTERRUPT_OFFSET		0

#endif /* IRQ_H_ */
