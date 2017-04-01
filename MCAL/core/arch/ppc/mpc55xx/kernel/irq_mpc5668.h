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
 *   CFG_MPC5668
 *   CFG_MPC5516
 */

#ifndef IRQ_MPC5XXX_2_H
#define IRQ_MPC5XXX_2_H
#define Irq_SOI()

/**
 * End-Of-Interrupt. Called by the OS it wants to clear the interrupt.
 */
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
#if defined(CFG_MPC5668)
    /* DMA 15-31 also here , 27 -> 42 */
#elif defined(CFG_MPC5516)

#define RESERVED0                                27
#define RESERVED1                                28
#define RESERVED2                                29
#define RESERVED3                                30
#define RESERVED4                                31
#define RESERVED5                                32
#define RESERVED6                                33
#define RESERVED7                                34
#define RESERVED8                                35
#define RESERVED9                                36
#define RESERVED10                               37
#define RESERVED11                               38
#define RESERVED12                               39
#define RESERVED13                               40
#define RESERVED14                               41
#define RESERVED15                               42
#else
#error Not defined for this CPU
#endif

        /* Semahpore's */
#define SEMAPHORE_INT0                           43
#define SEMAPHORE_INT1                           44
#define PIN_WAKEUP                               45
#define CRP_INTERRUPT                            46
#define LVI_INTERRUPT                            47
#define IRQ_I2C_A                                48
#define IRQ_I2C_B                                49
#define PLL_SYNSR_LOCF                           50
#define PLL_SYNSR_LOLF                           51
#define SIU_OSR_OVER                             52
        /* External interrupts */
#define SIU_EISR_EIF0                            53
#define SIU_EISR_EIF1                            54
#define SIU_EISR_EIF2                            55
#define SIU_EISR_EIF3                            56
#define SIU_EISR_EIF15_4                         57

        /* eMIOS */
#define EMISOS200_FLAG_F0                        58
#define EMISOS200_FLAG_F1                        59
#define EMISOS200_FLAG_F2                        60
#define EMISOS200_FLAG_F3                        61
#define EMISOS200_FLAG_F4                        62
#define EMISOS200_FLAG_F5                        63
#define EMISOS200_FLAG_F6                        64
#define EMISOS200_FLAG_F7                        65
#define EMISOS200_FLAG_F8                        66
#define EMISOS200_FLAG_F9                        67
#define EMISOS200_FLAG_F10                       68
#define EMISOS200_FLAG_F11                       69
#define EMISOS200_FLAG_F12                       70
#define EMISOS200_FLAG_F13                       71
#define EMISOS200_FLAG_F14                       72
#define EMISOS200_FLAG_F15                       73

#define EMISOS200_FLAG_F16                       74
#define EMISOS200_FLAG_F17                       75
#define EMISOS200_FLAG_F18                       76
#define EMISOS200_FLAG_F19                       77
#define EMISOS200_FLAG_F20                       78
#define EMISOS200_FLAG_F21                       79
#define EMISOS200_FLAG_F22                       80
#define EMISOS200_FLAG_F23                       81

#define ADC_A_EOC                                82
#define ADC_A_ERR                                83
#define ADC_A_WD                                 84
#define ADC_B_EOC                                85
#define ADC_B_ERR                                86
#define ADC_B_WD                                 87
#define ADC_C_EOC                                88
#define ADC_C_ERR                                89
#define ADC_C_WD                                 90
#define RESERVED100                              91
#define CRP_FLASH_READY                          92
#define CTU_TRIGGER                              93
#define RESERVED101                              94
#define MLB_COMB_CH_0_15                         95
#define MLB_SYSTEM_INT                           96
#define MLB_CH_0                                 97
#define MLB_CH_1                                 98
#define MLB_CH_2                                 99
#define MLB_CH_3                                 100
#define MLB_CH_4                                 101
#define MLB_CH_5                                 102
#define MLB_CH_6                                 103
#define MLB_CH_7                                 104
#define MLB_CH_8                                 105
#define MLB_CH_9                                 106
#define MLB_CH_10                                107
#define MLB_CH_11                                108
#define MLB_CH_12                                109
#define MLB_CH_13                                110
#define MLB_CH_14                                111
#define MLB_CH_15                                112

        /* SCI */
#define SCI_A_COMB                               113
#define SCI_B_COMB                               114
#define SCI_C_COMB                               115
#define SCI_D_COMB                               116
/* DSPI */
#define DSPI_A_ISR_OVER                          117
#define DSPI_A_ISR_EOQF                          118
#define DSPI_A_ISR_TFFF                          119
#define DSPI_A_ISR_TCF                           120
#define DSPI_A_ISR_RFDF                          121
#define DSPI_B_ISR_OVER                          122
#define DSPI_B_ISR_EOQF                          123
#define DSPI_B_ISR_TFFF                          124
#define DSPI_B_ISR_TCF                           125
#define DSPI_B_ISR_RFDF                          126

        /* FlexCAN A */
#define FLEXCAN_A_ESR_BOFF_INT                   127
#define FLEXCAN_A_ESR_ERR_INT                    128
#define RESERVED18                               129
#define FLEXCAN_A_IFLAG1_BUF0I                   130
#define FLEXCAN_A_IFLAG1_BUF1I                   131
#define FLEXCAN_A_IFLAG1_BUF2I                   132
#define FLEXCAN_A_IFLAG1_BUF3I                   133
#define FLEXCAN_A_IFLAG1_BUF4I                   134
#define FLEXCAN_A_IFLAG1_BUF5I                   135
#define FLEXCAN_A_IFLAG1_BUF6I                   136
#define FLEXCAN_A_IFLAG1_BUF7I                   137
#define FLEXCAN_A_IFLAG1_BUF8I                   138
#define FLEXCAN_A_IFLAG1_BUF9I                   139
#define FLEXCAN_A_IFLAG1_BUF10I                  140
#define FLEXCAN_A_IFLAG1_BUF11I                  141
#define FLEXCAN_A_IFLAG1_BUF12I                  142
#define FLEXCAN_A_IFLAG1_BUF13I                  143
#define FLEXCAN_A_IFLAG1_BUF14I                  144
#define FLEXCAN_A_IFLAG1_BUF15I                  145
#define FLEXCAN_A_IFLAG1_BUF31_16I               146
#define FLEXCAN_A_IFLAG1_BUF63_32I               147

#if defined(CFG_MPC5516)
        /* Periodic interrupt timer */
#define PIT_PITFLG_RTIF                          148
#define PIT_PITFLG_PIT1                          149
#define PIT_PITFLG_PIT2                          150
#define PIT_PITFLG_PIT3                          151
#define PIT_PITFLG_PIT4                          152
#define PIT_PITFLG_PIT5                          153
#define PIT_PITFLG_PIT6                          154
#define PIT_PITFLG_PIT7                          155
#define PIT_PITFLG_PIT8                          156
#elif defined(CFG_MPC5668)
        /* Periodic interrupt timer */
#define PIT_PITFLG_RTIF                          148
#define PIT_INT0                                 149
#define PIT_INT1                                 150
#define PIT_INT2                                 151
#define PIT_INT3                                 152
#define PIT_INT4                                 153
#define PIT_INT5                                 154
#define PIT_INT6                                 155
#define PIT_INT7                                 156
#endif

/* FlexCAN B */
#define FLEXCAN_B_ESR_BOFF_INT                   157
#define FLEXCAN_B_ESR_ERR_INT                    158
#define RESERVED19                               159
#define FLEXCAN_B_IFLAG1_BUF0I                   160
#define FLEXCAN_B_IFLAG1_BUF1I                   161
#define FLEXCAN_B_IFLAG1_BUF2I                   162
#define FLEXCAN_B_IFLAG1_BUF3I                   163
#define FLEXCAN_B_IFLAG1_BUF4I                   164
#define FLEXCAN_B_IFLAG1_BUF5I                   165
#define FLEXCAN_B_IFLAG1_BUF6I                   166
#define FLEXCAN_B_IFLAG1_BUF7I                   167
#define FLEXCAN_B_IFLAG1_BUF8I                   168
#define FLEXCAN_B_IFLAG1_BUF9I                   169
#define FLEXCAN_B_IFLAG1_BUF10I                  170
#define FLEXCAN_B_IFLAG1_BUF11I                  171
#define FLEXCAN_B_IFLAG1_BUF12I                  172
#define FLEXCAN_B_IFLAG1_BUF13I                  173
#define FLEXCAN_B_IFLAG1_BUF14I                  174
#define FLEXCAN_B_IFLAG1_BUF15I                  175
#define FLEXCAN_B_IFLAG1_BUF31_16I               176
#define FLEXCAN_B_IFLAG1_BUF63_32I               177
        /* FlexCAN C */
#define FLEXCAN_C_ESR_BOFF_INT                   178
#define FLEXCAN_C_ESR_ERR_INT                    179
#define RESERVED20                               180
#define FLEXCAN_C_IFLAG1_BUF0I                   181
#define FLEXCAN_C_IFLAG1_BUF1I                   182
#define FLEXCAN_C_IFLAG1_BUF2I                   183
#define FLEXCAN_C_IFLAG1_BUF3I                   184
#define FLEXCAN_C_IFLAG1_BUF4I                   185
#define FLEXCAN_C_IFLAG1_BUF5I                   186
#define FLEXCAN_C_IFLAG1_BUF6I                   187
#define FLEXCAN_C_IFLAG1_BUF7I                   188
#define FLEXCAN_C_IFLAG1_BUF8I                   189
#define FLEXCAN_C_IFLAG1_BUF9I                   190
#define FLEXCAN_C_IFLAG1_BUF10I                  191
#define FLEXCAN_C_IFLAG1_BUF11I                  192
#define FLEXCAN_C_IFLAG1_BUF12I                  193
#define FLEXCAN_C_IFLAG1_BUF13I                  194
#define FLEXCAN_C_IFLAG1_BUF14I                  195
#define FLEXCAN_C_IFLAG1_BUF15I                  196
#define FLEXCAN_C_IFLAG1_BUF31_16I               197
#define FLEXCAN_C_IFLAG1_BUF63_32I               198
        /* FlexCAN D */
#define FLEXCAN_D_ESR_BOFF_INT                   199
#define FLEXCAN_D_ESR_ERR_INT                    200
#define RESERVED21                               201
#define FLEXCAN_D_IFLAG1_BUF0I                   202
#define FLEXCAN_D_IFLAG1_BUF1I                   203
#define FLEXCAN_D_IFLAG1_BUF2I                   204
#define FLEXCAN_D_IFLAG1_BUF3I                   205
#define FLEXCAN_D_IFLAG1_BUF4I                   206
#define FLEXCAN_D_IFLAG1_BUF5I                   207
#define FLEXCAN_D_IFLAG1_BUF6I                   208
#define FLEXCAN_D_IFLAG1_BUF7I                   209
#define FLEXCAN_D_IFLAG1_BUF8I                   210
#define FLEXCAN_D_IFLAG1_BUF9I                   211
#define FLEXCAN_D_IFLAG1_BUF10I                  212
#define FLEXCAN_D_IFLAG1_BUF11I                  213
#define FLEXCAN_D_IFLAG1_BUF12I                  214
#define FLEXCAN_D_IFLAG1_BUF13I                  215
#define FLEXCAN_D_IFLAG1_BUF14I                  216
#define FLEXCAN_D_IFLAG1_BUF15I                  217
#define FLEXCAN_D_IFLAG1_BUF31_16I               218
#define FLEXCAN_D_IFLAG1_BUF63_32I               219
        /* FlexCAN E */
#define FLEXCAN_E_ESR_BOFF_INT                   220
#define FLEXCAN_E_ESR_ERR_INT                    221
#define RESERVED22                               222
#define FLEXCAN_E_IFLAG1_BUF0I                   223
#define FLEXCAN_E_IFLAG1_BUF1I                   224
#define FLEXCAN_E_IFLAG1_BUF2I                   225
#define FLEXCAN_E_IFLAG1_BUF3I                   226
#define FLEXCAN_E_IFLAG1_BUF4I                   227
#define FLEXCAN_E_IFLAG1_BUF5I                   228
#define FLEXCAN_E_IFLAG1_BUF6I                   229
#define FLEXCAN_E_IFLAG1_BUF7I                   230
#define FLEXCAN_E_IFLAG1_BUF8I                   231
#define FLEXCAN_E_IFLAG1_BUF9I                   232
#define FLEXCAN_E_IFLAG1_BUF10I                  233
#define FLEXCAN_E_IFLAG1_BUF11I                  234
#define FLEXCAN_E_IFLAG1_BUF12I                  235
#define FLEXCAN_E_IFLAG1_BUF13I                  236
#define FLEXCAN_E_IFLAG1_BUF14I                  237
#define FLEXCAN_E_IFLAG1_BUF15I                  238
#define FLEXCAN_E_IFLAG1_BUF31_16I               239
#define FLEXCAN_E_IFLAG1_BUF63_32I               240
        /* FlexCAN F */
#define FLEXCAN_F_ESR_BOFF_INT                   241
#define FLEXCAN_F_ESR_ERR_INT                    242
#define RESERVED23                               243
#define FLEXCAN_F_IFLAG1_BUF0I                   244
#define FLEXCAN_F_IFLAG1_BUF1I                   245
#define FLEXCAN_F_IFLAG1_BUF2I                   246
#define FLEXCAN_F_IFLAG1_BUF3I                   247
#define FLEXCAN_F_IFLAG1_BUF4I                   248
#define FLEXCAN_F_IFLAG1_BUF5I                   249
#define FLEXCAN_F_IFLAG1_BUF6I                   250
#define FLEXCAN_F_IFLAG1_BUF7I                   251
#define FLEXCAN_F_IFLAG1_BUF8I                   252
#define FLEXCAN_F_IFLAG1_BUF9I                   253
#define FLEXCAN_F_IFLAG1_BUF10I                  254
#define FLEXCAN_F_IFLAG1_BUF11I                  255
#define FLEXCAN_F_IFLAG1_BUF12I                  256
#define FLEXCAN_F_IFLAG1_BUF13I                  257
#define FLEXCAN_F_IFLAG1_BUF14I                  258
#define FLEXCAN_F_IFLAG1_BUF15I                  259
#define FLEXCAN_F_IFLAG1_BUF31_16I               260
#define FLEXCAN_F_IFLAG1_BUF63_32I               261

#if defined(CFG_MPC5668)
#define EMIOS200_FLAG_F24                        262
#define EMIOS200_FLAG_F25                        263
#define EMIOS200_FLAG_F26                        264
#define EMIOS200_FLAG_F27                        265
#define EMIOS200_FLAG_F28                        266
#define EMIOS200_FLAG_F29                        267
#define EMIOS200_FLAG_F30                        268
#define EMIOS200_FLAG_F31                        269
#else
/* mpc5516 reserved 262-269 */
#endif
        /* SCI */
#define SCI_E_COMB                               270
#define SCI_F_COMB                               271
#define SCI_G_COMB                               272
#define SCI_H_COMB                               273
        /* DSPI */
#define DSPI_C_ISR_OVER                          274
#define DSPI_C_ISR_EOQF                          275
#define DSPI_C_ISR_TFFF                          276
#define DSPI_C_ISR_TCF                           277
#define DSPI_C_ISR_RFDF                          278
#define DSPI_D_ISR_OVER                          279
#define DSPI_D_ISR_EOQF                          280
#define DSPI_D_ISR_TFFF                          281
#define DSPI_D_ISR_TCF                           282
#define DSPI_D_ISR_RFDF                          283
        /* Flexray */
#define FLEXRAY_GLOB                             284
#define FLEXRAY_PRIF                             285
#define FLEXRAY_CHIF                             286
#define FLEXRAY_WUP_IF                           287
#define FLEXRAY_FBNE_F                           288
#define FLEXRAY_FANE_F                           289
#define FLEXRAY_RBIF                             290
#define FLEXRAY_TBIF                             291
#define RESERVED32                               292
#define MLB_SERVICE_REQUEST                      293
#if defined(CFG_MPC5668)
#define STM_CH0                                  294
#define STM_CH1                                  295
#define STM_CH2                                  296
#define STM_CH3                                  297
#define FEC_TX                                   298
#define FEC_RX                                   299
#define FEC_WORLD                                300
#define RESERVED201                              301
#define RESERVED202                              302
#define RESERVED203                              303
#define RESERVED204                              304
#define RESERVED205                              305
#define SCI_J_COMB                               306
#define SCI_K_COMB                               307
#define SCI_L_COMB                               308
#define SCI_M_COMB                               309
#define SCI_N_COMB                               310
#define SCI_P_COMB                               311
#define SCI_Q_COMB                               312
#define SCI_R_COMB                               313
#define IRQ_I2C_C                                314
#define IRQ_I2C_D                                315
#define INTC_NUMBER_OF_INTERRUPTS                316 /* mpc5668 */
#else
#define INTC_NUMBER_OF_INTERRUPTS                294 /* mpc5516 */
#endif

#define NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS     INTC_NUMBER_OF_INTERRUPTS

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


typedef enum
{
    CPU_CORE0,
    CPU_CORE1
} Cpu_t;

/* Offset from exceptions to interrupts */
#define IRQ_INTERRUPT_OFFSET        0


#endif /* XX_H_ */

