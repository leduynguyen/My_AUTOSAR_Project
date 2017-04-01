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

#ifndef IRQ_MPC5748G_H_
#define IRQ_MPC5748G_H_

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


/* Platform watchdog */
#define MCM_MSWTIR_SWTIC0   32
#define MCM_MSWTIR_SWTIC1   33
#define MCM_MSWTIR_SWTIC2   34

/* STM INTC */

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

/* ETH 190 - 218  */

#define ESW_0               190
#define ESW_1               191
#define ESW_2               192
#define ESW_3               193
#define ENET_1_GROUP_0      201
#define ENET_1_GROUP_1      202
#define ENET_1_GROUP_2      203
#define ENET_1_GROUP_3      204
#define ENET_1_GROUP_4      205
#define ENET_1_GROUP_5      206
#define ENET_1_GROUP_6      207
#define ENET_1_GROUP_7      208
#define ENET_1_GROUP_8      209
#define ENET_0_GROUP_0      210
#define ENET_0_GROUP_1      211
#define ENET_0_GROUP_2      212
#define ENET_0_GROUP_3      213
#define ENET_0_GROUP_4      214
#define ENET_0_GROUP_5      215
#define ENET_0_GROUP_6      216
#define ENET_0_GROUP_7      217
#define ENET_0_GROUP_8      218
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

#define PIT_INT8            234
#define PIT_INT9            235
#define PIT_INT10           236
#define PIT_INT11           237
#define PIT_INT12           238
#define PIT_INT13           239
#define PIT_INT14           240
#define PIT_INT15           241

/* #define XOSC_CTREXPIRED     242 */
/*#define SIU_EISR_EIF0       243 */
/*#define SIU_EISR_EIF1       244 */

#define PIT_RTI             242

/* DSPI_0 */
#define DSPI_0_ISR_TFUF_RFOF_TFIWF   259
#define DSPI_0_ISR_EOQF              260
#define DSPI_0_ISR_TFFF              261
#define DSPI_0_ISR_TCF               262
#define DSPI_0_ISR_RFDF              263
#define DSPI_0_ISR_SPITCF_CMDTCF     264
#define DSPI_0_ISR_DSITCF_CMDFFF     265
#define DSPI_0_ISR_SPEF_DPEF         266
#define DSPI_0_ISR_DDIF              267

/* DSPI_1 */
#define DSPI_1_ISR_TFUF_RFOF_TFIWF   268
#define DSPI_1_ISR_EOQF              269
#define DSPI_1_ISR_TFFF              270
#define DSPI_1_ISR_TCF               271
#define DSPI_1_ISR_RFDF              272
#define DSPI_1_ISR_SPITCF_CMDTCF     273
#define DSPI_1_ISR_DSITCF_CMDFFF     274
#define DSPI_1_ISR_SPEF_DPEF         275
#define DSPI_1_ISR_DDIF              276

/* DSPI_2 */
#define DSPI_2_ISR_TFUF_RFOF_TFIWF   277
#define DSPI_2_ISR_EOQF              278
#define DSPI_2_ISR_TFFF              279
#define DSPI_2_ISR_TCF               280
#define DSPI_2_ISR_RFDF              281
#define DSPI_2_ISR_SPITCF_CMDTCF     282
#define DSPI_2_ISR_DSITCF_CMDFFF     283
#define DSPI_2_ISR_SPEF_DPEF         284
#define DSPI_2_ISR_DDIF              285

/* DSPI_3 */
#define DSPI_3_ISR_TFUF_RFOF_TFIWF   286
#define DSPI_3_ISR_EOQF              287
#define DSPI_3_ISR_TFFF              288
#define DSPI_3_ISR_TCF               289
#define DSPI_3_ISR_RFDF              290
#define DSPI_3_ISR_SPITCF_CMDTCF     291
#define DSPI_3_ISR_DSITCF_CMDFFF     292
#define DSPI_3_ISR_SPEF_DPEF         293
#define DSPI_3_ISR_DDIF              294

/************************************************************
* Starting from this point DSPI_X_ISR_DDIF is not available
* and some vectors are reserved for future usage.
*************************************************************/
/* DSPI_4 */
#define DSPI_4_ISR_TFUF_RFOF_TFIWF   295
#define DSPI_4_ISR_EOQF              296
#define DSPI_4_ISR_TFFF              297
#define DSPI_4_ISR_TCF               298
#define DSPI_4_ISR_RFDF              299
#define DSPI_4_ISR_SPITCF_CMDTCF     300
#define DSPI_4_ISR_DSITCF_CMDFFF     301
#define DSPI_4_ISR_SPEF_DPEF         302
/* #define DSPI_D_ISR_DDIF              303 */

/* DSPI_5 */
#define DSPI_5_ISR_TFUF_RFOF_TFIWF   304
#define DSPI_5_ISR_EOQF              305
#define DSPI_5_ISR_TFFF              306
#define DSPI_5_ISR_TCF               307
#define DSPI_5_ISR_RFDF              308
#define DSPI_5_ISR_SPITCF_CMDTCF     309
#define DSPI_5_ISR_DSITCF_CMDFFF     310
#define DSPI_5_ISR_SPEF_DPEF         311
/* #define DSPI_5_ISR_DDIF              312 */

/* DSPI_6 */
#define DSPI_6_ISR_TFUF_RFOF_TFIWF   313
#define DSPI_6_ISR_EOQF              314
#define DSPI_6_ISR_TFFF              315
#define DSPI_6_ISR_TCF               316
#define DSPI_6_ISR_RFDF              317
#define DSPI_6_ISR_SPITCF_CMDTCF     318
#define DSPI_6_ISR_DSITCF_CMDFFF     319
#define DSPI_6_ISR_SPEF_DPEF         320
/* #define DSPI_6_ISR_DDIF              321 */

/* DSPI_7 */
#define DSPI_7_ISR_TFUF_RFOF_TFIWF   322
#define DSPI_7_ISR_EOQF              323
#define DSPI_7_ISR_TFFF              324
#define DSPI_7_ISR_TCF               325
#define DSPI_7_ISR_RFDF              326
/* #define DSPI_7_ISR_SPITCF_CMDTCF     327 */
/* #define DSPI_7_ISR_DSITCF_CMDFFF     328 */
#define DSPI_7_ISR_SPEF_DPEF         329
/* #define DSPI_7_ISR_DDIF              330 */

/* DSPI_8 */
#define DSPI_8_ISR_TFUF_RFOF_TFIWF   331
#define DSPI_8_ISR_EOQF              332
#define DSPI_8_ISR_TFFF              333
#define DSPI_8_ISR_TCF               334
#define DSPI_8_ISR_RFDF              335
/* #define DSPI_8_ISR_SPITCF_CMDTCF     336 */
/* #define DSPI_8_ISR_DSITCF_CMDFFF     337 */
#define DSPI_8_ISR_SPEF_DPEF         338
/* #define DSPI_8_ISR_DDIF              339 */

/* DSPI_9 */
#define DSPI_9_ISR_TFUF_RFOF_TFIWF   340
#define DSPI_9_ISR_EOQF              341
#define DSPI_9_ISR_TFFF              342
#define DSPI_9_ISR_TCF               343
#define DSPI_9_ISR_RFDF              344
/* #define DSPI_9_ISR_SPITCF_CMDTCF     345 */
/* #define DSPI_9_ISR_DSITCF_CMDFFF     346 */
#define DSPI_9_ISR_SPEF_DPEF         347
/* #define DSPI_9_ISR_DDIF              348 */

/* LinFlex/eSCIO */
#define LINFLEX_0_RXI       376
#define LINFLEX_0_TXI       377
#define LINFLEX_0_ERR       378
#define LINFLEX_1_RXI       379
#define LINFLEX_1_TXI       380
#define LINFLEX_1_ERR       381
#define LINFLEX_2_RXI       382
#define LINFLEX_2_TXI       383
#define LINFLEX_2_ERR       384
#define LINFLEX_3_RXI       385
#define LINFLEX_3_TXI       386
#define LINFLEX_3_ERR       387
#define LINFLEX_4_RXI       388
#define LINFLEX_4_TXI       389
#define LINFLEX_4_ERR       390
#define LINFLEX_5_RXI       391
#define LINFLEX_5_TXI       392
#define LINFLEX_5_ERR       393
#define LINFLEX_6_RXI       394
#define LINFLEX_6_TXI       395
#define LINFLEX_6_ERR       396
#define LINFLEX_7_RXI       397
#define LINFLEX_7_TXI       398
#define LINFLEX_7_ERR       399
#define LINFLEX_8_RXI       400
#define LINFLEX_8_TXI       401
#define LINFLEX_8_ERR       402
#define LINFLEX_9_RXI       403
#define LINFLEX_9_TXI       404
#define LINFLEX_9_ERR       405
#define LINFLEX_10_RXI      406
#define LINFLEX_10_TXI      407
#define LINFLEX_10_ERR      408
#define LINFLEX_11_RXI      409
#define LINFLEX_11_TXI      410
#define LINFLEX_11_ERR      411
#define LINFLEX_12_RXI      412
#define LINFLEX_12_TXI      413
#define LINFLEX_12_ERR      414
#define LINFLEX_13_RXI      415
#define LINFLEX_13_TXI      416
#define LINFLEX_13_ERR      417
#define LINFLEX_14_RXI      418
#define LINFLEX_14_TXI      419
#define LINFLEX_14_ERR      420
#define LINFLEX_15_RXI      421
#define LINFLEX_15_TXI      422
#define LINFLEX_15_ERR      423
#define LINFLEX_16_RXI      424
#define LINFLEX_16_TXI      425
#define LINFLEX_16_ERR      426
#define LINFLEX_17_RXI      427
#define LINFLEX_17_TXI      428
#define LINFLEX_17_ERR      429

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

/* PLL loss of lock */
#define PLL_LOSS_OF_LOCK_INTREQ   480

/* FCCU */
#define FCCU_ALARM          488
#define FCCU_CFG_TIMEOUT    489

/* ADC */
#define ADC0_EOC_INT               548
#define ADC0_ER_INT                549
#define ADC0_WD_INT                550

#define ADC1_EOC_INT               554
#define ADC1_ER_INT                555
#define ADC1_WD_INT                556

/* FlexCAN */
#define FLEXCAN_0_PN                565

#define FLEXCAN_0_ESR_ERR_INT       566
#define FLEXCAN_0_ESR_BOFF_INT      567
#define FLEXCAN_0_BUF_00_03         568
#define FLEXCAN_0_BUF_04_07         569
#define FLEXCAN_0_BUF_08_11         570
#define FLEXCAN_0_BUF_12_15         571
#define FLEXCAN_0_BUF_16_31         572
#define FLEXCAN_0_BUF_32_63         573
#define FLEXCAN_0_BUF_64_95         574

#define FLEXCAN_1_ESR_ERR_INT       578
#define FLEXCAN_1_ESR_BOFF_INT      579
#define FLEXCAN_1_BUF_00_03         580
#define FLEXCAN_1_BUF_04_07         581
#define FLEXCAN_1_BUF_08_11         582
#define FLEXCAN_1_BUF_12_15         583
#define FLEXCAN_1_BUF_16_31         584
#define FLEXCAN_1_BUF_32_63         585
#define FLEXCAN_1_BUF_64_95         586

#define FLEXCAN_2_ESR_ERR_INT       590
#define FLEXCAN_2_ESR_BOFF_INT      591
#define FLEXCAN_2_BUF_00_03         592
#define FLEXCAN_2_BUF_04_07         593
#define FLEXCAN_2_BUF_08_11         594
#define FLEXCAN_2_BUF_12_15         595
#define FLEXCAN_2_BUF_16_31         596
#define FLEXCAN_2_BUF_32_63         597
#define FLEXCAN_2_BUF_64_95         598

#define FLEXCAN_3_ESR_ERR_INT       602
#define FLEXCAN_3_ESR_BOFF_INT      603
#define FLEXCAN_3_BUF_00_03         604
#define FLEXCAN_3_BUF_04_07         605
#define FLEXCAN_3_BUF_08_11         606
#define FLEXCAN_3_BUF_12_15         607
#define FLEXCAN_3_BUF_16_31         608
#define FLEXCAN_3_BUF_32_63         609
#define FLEXCAN_3_BUF_64_95         610

#define FLEXCAN_4_ESR_ERR_INT       614
#define FLEXCAN_4_ESR_BOFF_INT      615
#define FLEXCAN_4_BUF_00_03         616
#define FLEXCAN_4_BUF_04_07         617
#define FLEXCAN_4_BUF_08_11         618
#define FLEXCAN_4_BUF_12_15         619
#define FLEXCAN_4_BUF_16_31         620
#define FLEXCAN_4_BUF_32_63         621
#define FLEXCAN_4_BUF_64_95         622

#define FLEXCAN_5_ESR_ERR_INT       626
#define FLEXCAN_5_ESR_BOFF_INT      627
#define FLEXCAN_5_BUF_00_03         628
#define FLEXCAN_5_BUF_04_07         629
#define FLEXCAN_5_BUF_08_11         630
#define FLEXCAN_5_BUF_12_15         631
#define FLEXCAN_5_BUF_16_31         632
#define FLEXCAN_5_BUF_32_63         633
#define FLEXCAN_5_BUF_64_95         634

#define FLEXCAN_6_ESR_ERR_INT       638
#define FLEXCAN_6_ESR_BOFF_INT      639
#define FLEXCAN_6_BUF_00_03         640
#define FLEXCAN_6_BUF_04_07         641
#define FLEXCAN_6_BUF_08_11         642
#define FLEXCAN_6_BUF_12_15         643
#define FLEXCAN_6_BUF_16_31         644
#define FLEXCAN_6_BUF_32_63         645
#define FLEXCAN_6_BUF_64_95         646

#define FLEXCAN_7_ESR_ERR_INT       650
#define FLEXCAN_7_ESR_BOFF_INT      651
#define FLEXCAN_7_BUF_00_03         652
#define FLEXCAN_7_BUF_04_07         653
#define FLEXCAN_7_BUF_08_11         654
#define FLEXCAN_7_BUF_12_15         655
#define FLEXCAN_7_BUF_16_31         656
#define FLEXCAN_7_BUF_32_63         657
#define FLEXCAN_7_BUF_64_95         658



/* EMIOS */
#define EMIOS_0_GFR_F0_F1                        706
#define EMIOS_0_GFR_F2_F3                        707
#define EMIOS_0_GFR_F4_F5                        708
#define EMIOS_0_GFR_F6_F7                        709
#define EMIOS_0_GFR_F8_F9                        710
#define EMIOS_0_GFR_F10_F11                      711
#define EMIOS_0_GFR_F12_F13                      712
#define EMIOS_0_GFR_F14_F15                      713
#define EMIOS_0_GFR_F16_F17                      714
#define EMIOS_0_GFR_F18_F19                      715
#define EMIOS_0_GFR_F20_F21                      716
#define EMIOS_0_GFR_F22_F23                      717
#define EMIOS_0_GFR_F24_F25                      718
#define EMIOS_0_GFR_F26_F27                      719
#define EMIOS_0_GFR_F28_F29                      720
#define EMIOS_0_GFR_F30_F31                      721

#define EMIOS_1_GFR_F0_F1                        722
#define EMIOS_1_GFR_F2_F3                        723
#define EMIOS_1_GFR_F4_F5                        724
#define EMIOS_1_GFR_F6_F7                        725
#define EMIOS_1_GFR_F8_F9                        726
#define EMIOS_1_GFR_F10_F11                      727
#define EMIOS_1_GFR_F12_F13                      728
#define EMIOS_1_GFR_F14_F15                      729
#define EMIOS_1_GFR_F16_F17                      730
#define EMIOS_1_GFR_F18_F19                      731
#define EMIOS_1_GFR_F20_F21                      732
#define EMIOS_1_GFR_F22_F23                      733
#define EMIOS_1_GFR_F24_F25                      734
#define EMIOS_1_GFR_F26_F27                      735
#define EMIOS_1_GFR_F28_F29                      736
#define EMIOS_1_GFR_F30_F31                      737

#define EMIOS_2_GFR_F0_F1                        738
#define EMIOS_2_GFR_F2_F3                        739
#define EMIOS_2_GFR_F4_F5                        740
#define EMIOS_2_GFR_F6_F7                        741
#define EMIOS_2_GFR_F8_F9                        742
#define EMIOS_2_GFR_F10_F11                      743
#define EMIOS_2_GFR_F12_F13                      744
#define EMIOS_2_GFR_F14_F15                      745
#define EMIOS_2_GFR_F16_F17                      746
#define EMIOS_2_GFR_F18_F19                      747
#define EMIOS_2_GFR_F20_F21                      748
#define EMIOS_2_GFR_F22_F23                      749
#define EMIOS_2_GFR_F24_F25                      750
#define EMIOS_2_GFR_F26_F27                      751
#define EMIOS_2_GFR_F28_F29                      752
#define EMIOS_2_GFR_F30_F31                      753

#define INTC_NUMBER_OF_INTERRUPTS   754
#define NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS INTC_NUMBER_OF_INTERRUPTS


typedef enum {
    C_PBRIDGE,
    C_PLL_PHI,
    C_SYS_CLK,
    PERIPHERAL_CLOCK_FLEXCAN_A,
    PERIPHERAL_CLOCK_FLEXCAN_B,
    PERIPHERAL_CLOCK_FLEXCAN_C,
    PERIPHERAL_CLOCK_FLEXCAN_D,
    PERIPHERAL_CLOCK_FLEXCAN_E,
    PERIPHERAL_CLOCK_FLEXCAN_F,
	PERIPHERAL_CLOCK_FLEXCAN_G,
	PERIPHERAL_CLOCK_FLEXCAN_H,
    PERIPHERAL_CLOCK_SPI_A,
    PERIPHERAL_CLOCK_SPI_B,
	PERIPHERAL_CLOCK_SPI_C,
	PERIPHERAL_CLOCK_SPI_D,
	PERIPHERAL_CLOCK_SPI_E,
	PERIPHERAL_CLOCK_SPI_F,
    PERIPHERAL_CLOCK_DSPI_A,	/* DSPI0 */
    PERIPHERAL_CLOCK_DSPI_B,
	PERIPHERAL_CLOCK_DSPI_C,
	PERIPHERAL_CLOCK_DSPI_D,
    PERIPHERAL_CLOCK_SPI_0,
    PERIPHERAL_CLOCK_SPI_1,
	PERIPHERAL_CLOCK_SPI_2,
	PERIPHERAL_CLOCK_SPI_3,
	PERIPHERAL_CLOCK_SPI_4,
	PERIPHERAL_CLOCK_SPI_5,		/* DSPI9 */
    PERIPHERAL_CLOCK_LIN_A,
    PERIPHERAL_CLOCK_LIN_B,
	PERIPHERAL_CLOCK_LIN_C,
	PERIPHERAL_CLOCK_LIN_D,
	PERIPHERAL_CLOCK_LIN_4,
	PERIPHERAL_CLOCK_LIN_5,
	PERIPHERAL_CLOCK_LIN_6,
	PERIPHERAL_CLOCK_LIN_7,
    PERIPHERAL_CLOCK_LIN_8,
	PERIPHERAL_CLOCK_LIN_9,
	PERIPHERAL_CLOCK_LIN_10,
	PERIPHERAL_CLOCK_LIN_11,
	PERIPHERAL_CLOCK_LIN_12,
	PERIPHERAL_CLOCK_LIN_13,
	PERIPHERAL_CLOCK_LIN_14,
    PERIPHERAL_CLOCK_LIN_15,
    PERIPHERAL_CLOCK_LIN_16,
	PERIPHERAL_CLOCK_LIN_17,
    PERIPHERAL_CLOCK_PIT_0,
    PERIPHERAL_CLOCK_PIT_1,
    PERIPHERAL_CLOCK_PIT_2,
    PERIPHERAL_CLOCK_PIT_3,
	PERIPHERAL_CLOCK_ENET,
	PERIPHERAL_CLOCK_ENET_TIMER,
    PERIPHERAL_CLOCK_STM_0,
    PERIPHERAL_CLOCK_EMIOS_0,
    PERIPHERAL_CLOCK_EMIOS_1,
    PERIPHERAL_CLOCK_EMIOS_2
} Mcu_Arc_PeriperalClock_t;


typedef enum {
    CPU_CORE0,
} Cpu_t;

/* Offset from exceptions to interrupts */
#define IRQ_INTERRUPT_OFFSET    0

#endif /* IRQ_MPC5748G_H_ */
