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

#ifndef IRQ_MPC560X_H_
#define IRQ_MPC560X_H_

#define Irq_SOI()

typedef uint16 IrqType;

#define INTC_SSCIR0_CLR0                         0
#define INTC_SSCIR0_CLR1                         1
#define INTC_SSCIR0_CLR2                         2
#define INTC_SSCIR0_CLR3                         3
#define INTC_SSCIR0_CLR4                         4
#define INTC_SSCIR0_CLR5                         5
#define INTC_SSCIR0_CLR6                         6
#define INTC_SSCIR0_CLR7                         7
#define RESERVED0                                8

#define ECC_ERROR                                9

#define DMA_COMBINED_ERROR_INT                   10
#define DMA_CH0_INT                              11
#define DMA_CH1_INT                              12
#define DMA_CH2_INT                              13
#define DMA_CH3_INT                              14
#define DMA_CH4_INT                              15
#define DMA_CH5_INT                              16
#define DMA_CH6_INT                              17
#define DMA_CH7_INT                              18
#define DMA_CH8_INT                              19
#define DMA_CH9_INT                              20
#define DMA_CH10_INT                             21
#define DMA_CH11_INT                             22
#define DMA_CH12_INT                             23
#define DMA_CH13_INT                             24
#define DMA_CH14_INT                             25
#define DMA_CH15_INT                             26

#define RESERVED1                                27

#define SWT_TIMEOUT                              28

#define RESERVED2                                29

#define STM_CH0_INT                              30
#define STM_CH1_INT                              31
#define STM_CH2_INT                              32
#define STM_CH3_INT                              33

#define RESERVED3                                34

#define ECC_DBD_INT                              35
#define ECC_SBC_INT                              36

#define RESERVED4                                37

#define RTC_INT                                  38
#define API_INT                                  39

#define RESERVED5                                40

#define SIU_EXT_IRQ0                             41
#define SIU_EXT_IRQ1                             42
#define SIU_EXT_IRQ2                             43

#define RESERVED7                                44
#define RESERVED8                                45

#define WAKEUP_IRQ0                              46
#define WAKEUP_IRQ1                              47
#define WAKEUP_IRQ2                              48
#define WAKEUP_IRQ3                              49

#define RESERVED10                               50

#define SAFE_MODE_INT                            51
#define MODE_TRAS_INT                            52
#define INV_MODE_INT                             53
#define INV_MODE_CONF_INT                        54

#define RESERVED11                               55

#define RESET_ALT_EVENT_INT                      56

#define FXOSC_COUNTER_EXPIRED                    57

#define RESERVED12                               58

#define PIT_INT0                                 59
#define PIT_INT1                                 60
#define PIT_INT2                                 61

#define ADC0_EOC_INT                             62
#define ADC0_ER_INT                              63
#define ADC0_WD_INT                              64

#define FLEXCAN_0_ESR_ERR_INT                    65
#define FLEXCAN_0_ESR_BOFF_INT                   66

#define RESERVED13                               67

#define FLEXCAN_0_BUF_00_03                      68
#define FLEXCAN_0_BUF_04_07                      69
#define FLEXCAN_0_BUF_08_11                      70
#define FLEXCAN_0_BUF_12_15                      71
#define FLEXCAN_0_BUF_16_31                      72
#define FLEXCAN_0_BUF_32_63                      73

#define DSPI_0_ISR_TFUF_RFOF                     74
#define DSPI_0_ISR_EOQF                          75
#define DSPI_0_ISR_TFFF                          76
#define DSPI_0_ISR_TCF                           77
#define DSPI_0_ISR_RFDF                          78

#define LINFLEX_0_RXI                            79
#define LINFLEX_0_TXI                            80
#define LINFLEX_0_ERR                            81

#define ADC1_EOC_INT                             82
#define ADC1_ER_INT                              83
#define ADC1_WD_INT                              84

#if defined(CFG_MPC5604P)
#define FLEXCAN_X_ESR_ERR_INT                    85
#define FLEXCAN_X_ESR_BOFF_INT                   86

#define RESERVED17                               87
#define FLEXCAN_X_BUF_00_03                      88
#define FLEXCAN_X_BUF_04_07                      89
#define FLEXCAN_X_BUF_08_11                      90
#define FLEXCAN_X_BUF_12_15                      91
#define FLEXCAN_X_BUF_16_31                      92
#define FLEXCAN_X_BUF_32_63                      93
#else
#define FLEXCAN_1_ESR_ERR_INT                    85
#define FLEXCAN_1_ESR_BOFF_INT                   86
#define FLEXCAN_1_ESR_WAK_INT                    87
#define FLEXCAN_1_BUF_00_03                      88
#define FLEXCAN_1_BUF_04_07                      89
#define FLEXCAN_1_BUF_08_11                      90
#define FLEXCAN_1_BUF_12_15                      91
#define FLEXCAN_1_BUF_16_31                      92
#define FLEXCAN_1_BUF_32_63                      93
#endif

#define DSPI_1_ISR_TFUF_RFOF                     94
#define DSPI_1_ISR_EOQF                          95
#define DSPI_1_ISR_TFFF                          96
#define DSPI_1_ISR_TCF                           97
#define DSPI_1_ISR_RFDF                          98

#define LINFLEX_1_RXI                            99
#define LINFLEX_1_TXI                            100
#define LINFLEX_1_ERR                            101

#define RESERVED18                               102
#define RESERVED19                               103
#define RESERVED20                               104
#define FLEXCAN_2_ESR_ERR_INT                    105
#define FLEXCAN_2_ESR_BOFF_INT                   106

#define RESERVED21                               107

#define FLEXCAN_2_BUF_00_03                      108
#define FLEXCAN_2_BUF_04_07                      109
#define FLEXCAN_2_BUF_08_11                      110
#define FLEXCAN_2_BUF_12_15                      111
#define FLEXCAN_2_BUF_16_31                      112
#define FLEXCAN_2_BUF_32_63                      113
#define DSPI_2_ISR_TFUF_RFOF                     114
#define DSPI_2_ISR_EOQF                          115
#define DSPI_2_ISR_TFFF                          116
#define DSPI_2_ISR_TCF                           117
#define DSPI_2_ISR_RFDF                          118

#define LINFLEX_2_RXI                            119
#define LINFLEX_2_TXI                            120
#define LINFLEX_2_ERR                            121
#define LINFLEX_3_RXI                            122
#define LINFLEX_3_TXI                            123
#define LINFLEX_3_ERR                            124
#define I2C_0_INT                                125
#define I2C_1_INT                                126

#define PIT_INT3                                 127

#define PIT_INT4                                 128
#define PIT_INT5                                 129
#define PIT_INT6                                 130
#define PIT_INT7                                 131
#define RESERVED45                               132
#define RESERVED46                               133
#define RESERVED47                               134
#define RESERVED48                               135
#define RESERVED49                               136
#define RESERVED50                               137
#define RESERVED51                               138
#define RESERVED52                               139
#define RESERVED53                               140
#if defined(CFG_MPC560XB)
#define EMIOS_0_GFR_F0_F1                        141
#define EMIOS_0_GFR_F2_F3                        142
#define EMIOS_0_GFR_F4_F5                        143
#define EMIOS_0_GFR_F6_F7                        144
#define EMIOS_0_GFR_F8_F9                        145
#define EMIOS_0_GFR_F10_F11                      146
#define EMIOS_0_GFR_F12_F13                      147
#define EMIOS_0_GFR_F14_F15                      148
#define EMIOS_0_GFR_F16_F17                      149
#define EMIOS_0_GFR_F18_F19                      150
#define EMIOS_0_GFR_F20_F21                      151
#define EMIOS_0_GFR_F22_F23                      152
#define EMIOS_0_GFR_F24_F25                      153
#define EMIOS_0_GFR_F26_F27                      154
#define EMIOS_0_GFR_F28_F29                      155
#define EMIOS_0_GFR_F30_F31                      156
#define EMIOS_1_GFR_F0_F1                        157
#define EMIOS_1_GFR_F2_F3                        158
#define EMIOS_1_GFR_F4_F5                        159
#define EMIOS_1_GFR_F6_F7                        160
#define EMIOS_1_GFR_F8_F9                        161
#define EMIOS_1_GFR_F10_F11                      162
#define EMIOS_1_GFR_F12_F13                      163
#define EMIOS_1_GFR_F14_F15                      164
#define EMIOS_1_GFR_F16_F17                      165
#define EMIOS_1_GFR_F18_F19                      166
#define EMIOS_1_GFR_F20_F21                      167
#define EMIOS_1_GFR_F22_F23                      168
#define EMIOS_1_GFR_F24_F25                      169
#define EMIOS_1_GFR_F26_F27                      170
#define EMIOS_1_GFR_F28_F29                      171
#define EMIOS_1_GFR_F30_F31                      172

#define FLEXCAN_3_ESR_ERR_INT                    173
#define FLEXCAN_3_ESR_BOFF_INT                   174

#define RESERVED58                               175

#define FLEXCAN_3_BUF_00_03                      176
#define FLEXCAN_3_BUF_04_07                      177
#define FLEXCAN_3_BUF_08_11                      178
#define FLEXCAN_3_BUF_12_15                      179
#define FLEXCAN_3_BUF_16_31                      180
#define FLEXCAN_3_BUF_32_63                      181
#define DSPI_3_ISR_TFUF_RFOF                     182
#define DSPI_3_ISR_EOQF                          183
#define DSPI_3_ISR_TFFF                          184
#define DSPI_3_ISR_TCF                           185
#define DSPI_3_ISR_RFDF                          186
#define LINFLEX_4_RXI                            187
#define LINFLEX_4_TXI                            188
#define LINFLEX_4_ERR                            189
#define FLEXCAN_4_ESR_ERR_INT                    190
#define FLEXCAN_4_ESR_BOFF_INT                   191

#define RESERVED67                               192

#define FLEXCAN_4_BUF_00_03                      193
#define FLEXCAN_4_BUF_04_07                      194
#define FLEXCAN_4_BUF_08_11                      195
#define FLEXCAN_4_BUF_12_15                      196
#define FLEXCAN_4_BUF_16_31                      197
#define FLEXCAN_4_BUF_32_63                      198
#define LINFLEX_5_RXI                            199
#define LINFLEX_5_TXI                            200
#define LINFLEX_5_ERR                            201
#define FLEXCAN_5_ESR_ERR_INT                    202
#define FLEXCAN_5_ESR_BOFF_INT                   203
#define RESERVED71                               204
#define FLEXCAN_5_BUF_00_03                      205
#define FLEXCAN_5_BUF_04_07                      206
#define FLEXCAN_5_BUF_08_11                      207
#define FLEXCAN_5_BUF_12_15                      208
#define FLEXCAN_5_BUF_16_31                      209
#define FLEXCAN_5_BUF_32_63                      210
#define DSPI_4_ISR_TFUF_RFOF                     211
#define DSPI_4_ISR_EOQF                          212
#define DSPI_4_ISR_TFFF                          213
#define DSPI_4_ISR_TCF                           214
#define DSPI_4_ISR_RFDF                          215
#define LINFLEX_6_RXI                            216
#define LINFLEX_6_TXI                            217
#define LINFLEX_6_ERR                            218
#define DSPI_5_ISR_TFUF_RFOF                     219
#define DSPI_5_ISR_EOQF                          220
#define DSPI_5_ISR_TFFF                          221
#define DSPI_5_ISR_TCF                           222
#define DSPI_5_ISR_RFDF                          223
#define LINFLEX_7_RXI                            224
#define LINFLEX_7_TXI                            225
#define LINFLEX_7_ERR                            226
#define LINFLEX_8_RXI                            227
#define LINFLEX_8_TXI                            228
#define LINFLEX_8_ERR                            229
#define LINFLEX_9_RXI                            230
#define LINFLEX_9_TXI                            231
#define LINFLEX_9_ERR                            232
#define INTC_NUMBER_OF_INTERRUPTS                233
#elif defined(CFG_MPC5606S)

#define EMIOS_0_GFR_F8_F9                        141
#define EMIOS_0_GFR_F10_F11                      142
#define EMIOS_0_GFR_F12_F13                      143
#define EMIOS_0_GFR_F14_F15                      144
#define EMIOS_0_GFR_F16_F17                      145
#define EMIOS_0_GFR_F18_F19                      146
#define EMIOS_0_GFR_F20_F21                      147
#define EMIOS_0_GFR_F22_F23                      148

#define RESERVED54                               149
#define RESERVED55                               150
#define RESERVED56                               151
#define RESERVED57                               152
#define RESERVED58                               153
#define RESERVED59                               154
#define RESERVED60                               155
#define RESERVED61                               156

#define EMIOS_1_GFR_F16_F17                      157
#define EMIOS_1_GFR_F18_F19                      158
#define EMIOS_1_GFR_F20_F21                      159
#define EMIOS_1_GFR_F22_F23                      160

#define RESERVED62                               161
#define RESERVED63                               162
#define RESERVED64                               163
#define RESERVED65                               164
#define RESERVED66                               165
#define RESERVED67                               166
#define RESERVED68                               167
#define RESERVED69                               168
#define RESERVED70                               169
#define RESERVED71                               170
#define RESERVED72                               171
#define RESERVED73                               172

#define I2C_2_INT                                173
#define I2C_3_INT                                174

#define RESERVED74                               175
#define RESERVED75                               176
#define RESERVED76                               177
#define RESERVED77                               178
#define RESERVED78                               179
#define RESERVED79                               180
#define RESERVED80                               181
#define RESERVED81                               182

#define SDCI_INT                                 183
#define DCUN0_VSYNC_INT                          184
#define DCUN0_UNDRUN                             185
#define DCUN0_PARERR                             186
#define DCUN0_PDI                                187

#define RESERVED82                               188
#define RESERVED83                               189
#define RESERVED84                               190
#define RESERVED85                               191

#define SMD0_INT                                 192
#define SSD0_INT                                 193
#define SSD1_INT                                 194
#define SSD2_INT                                 195
#define SSD3_INT                                 196
#define SSD4_INT                                 197
#define SSD5_INT                                 198

#define LCD0_EOF_INT                             199

#define RESERVED86                               200

#define QSPI0_TFUF                               201
#define QSPI0_EOQF                               202
#define QSPI0_TFFF                               203
#define QSPI0_TCF                                204
#define QSPI0_RFDF                               205
#define QSPI0_IPAEF                              206
#define INTC_NUMBER_OF_INTERRUPTS                207
#elif defined(CFG_MPC5604P)
/* mpc5604P reserved 141-> 178 */
#define PWM0_RF0                                 179
#define PWM0_COF0                                180
#define PWM0_CAF0                                181
#define PWM0_RF1                                 182
#define PWM0_COF1                                183
#define PWM0_CAF1                                184
#define PWM0_RF2                                 185
#define PWM0_COF2                                186
#define PWM0_CAF2                                187
#define PWM0_RF3                                 188
#define PWM0_COF3                                189
#define PWM0_CAF3                                190
#define PWM0_FFLAG                               191
#define PWM0_REF                                 192
#define RESERVED106                              193
#define RESERVED107                              194
#define RESERVED108                              195
#define RESERVED109                              196
#define RESERVED110                              197
#define RESERVED111                              198
#define RESERVED112                              199
#define RESERVED113                              200
#define RESERVED114                              201
#define RESERVED115                              202
#define RESERVED116                              203
#define RESERVED117                              204
#define RESERVED118                              205
#define RESERVED119                              206
#define RESERVED120                              207
#define FLEXCAN_1_ESR_ERR_INT                    208
#define FLEXCAN_1_ESR_BOFF_INT                   209

#define FLEXCAN_1_ESR_WAK                        210

#define FLEXCAN_1_BUF_00_03                      211
#define FLEXCAN_1_BUF_04_07                      212
#define FLEXCAN_1_BUF_08_11                      213
#define FLEXCAN_1_BUF_12_15                      214
#define FLEXCAN_1_BUF_16_31                      215
#define RESERVED121                              216
#define DSPI_3_ISR_TFUF_RFOF                     217
#define DSPI_3_ISR_EOQF                          218
#define DSPI_3_ISR_TFFF                          219
#define DSPI_3_ISR_TCF                           220
#define DSPI_3_ISR_RFDF                          221
#define INTC_NUMBER_OF_INTERRUPTS                222
#endif

#define NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS INTC_NUMBER_OF_INTERRUPTS

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


typedef enum {
    CPU_CORE0,
} Cpu_t;

/* Offset from exceptions to interrupts */
#define IRQ_INTERRUPT_OFFSET    0

#endif /* IRQ_MPC5777M_H_ */
