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

#ifndef IRQ_RH850F1H_H_
#define IRQ_RH850F1H_H_

#define IRQ_INTIPIR0 				0	/* Internal processor interrupt 0 IPIR Edge 1000 */
#define IRQ_INTIPIR1 				1	/* Internal processor interrupt 1 IPIR Edge 1001 */
#define IRQ_INTIPIR2 				2	/* Internal processor interrupt 2 IPIR Edge 1002 */
#define IRQ_INTIPIR3 				3	/* Internal processor interrupt 3 IPIR Edge 1003 */
#define IRQ_INTBN0 					4	/* Broadcasting detection interrupt 0 INTC2 Edge 1004 */
#define IRQ_INTTAUD0I0				8
#define IRQ_INTCSIH2IC_1			8
#define IRQ_INTTAUD0I2				9
#define IRQ_INTCSIH3IC_1			9
#define IRQ_INTTAUD0I4				10
#define IRQ_INTCSIH2IR_1			10
#define IRQ_INTTAUD0I6				11
#define IRQ_INTCSIH2IRE_1			11
#define IRQ_INTTAUD0I8				12
#define IRQ_INTCSIH2IJC_1			12
#define IRQ_INTTAUD0I10				13
#define IRQ_INTCSIH3IR_1			13
#define IRQ_INTTAUD0I12				14
#define IRQ_INTCSIH3IRE_1			14
#define IRQ_INTTAUD0I14				15
#define IRQ_INTCSIH3IJC_1			15
#define IRQ_INTTAPA0IPEK0 			16	/* TAPA0 peak interrupt 0 TAPA0 Edge 1010 */
#define IRQ_INTCSIH1IC_1			16
#define IRQ_INTTAPA0IVLY0 			17	/* TAPA0 valley interrupt 0 TAPA0 Edge 1011 */
#define IRQ_INTCSIH1IR_1			17
#define IRQ_INTADCA0I0 				18	/* ADCA0 SG1 end interrupt ADCA0 Edge 1012 */
#define IRQ_INTADCA0I1 				19	/* ADCA0 SG2 end interrupt ADCA0 Edge 1013 */
#define IRQ_INTADCA0I2				20
#define IRQ_INTCSIH0IJC_1			20
#define IRQ_INTDCUTDI 				21	/* Dedicated interrupt for on-chip debug  */
#define IRQ_INTRCANGERR0 			22	/* CAN global error interrupt RS-CAN0 Level 1016 */
#define IRQ_INTRCANGRECC0 			23	/* CAN receive FIFO interrupt RS-CAN0 Level 1017 */
#define IRQ_INTRCAN0ERR 			24	/* CAN0 error interrup RS-CAN0 Level 1018 */
#define IRQ_INTRCAN0REC 			25	/* CAN0 transmit/receive FIFO receive  */
#define IRQ_INTRCAN0TRX 			26	/* CAN0 transmit interrupt RS-CAN0 Level 101A */
#define IRQ_INTCSIG0IC 				27	/* CSIG0 communication status interrupt CSIG0 Edge 101B */
#define IRQ_INTCSIH1IRE_1			27
#define IRQ_INTCSIG0IR				28
#define IRQ_INTCSIH1IJC_1			28
#define IRQ_INTCSIH0IC 				29 	/* CSIH0 communication status interrupt CSIH0 Edge 101D */
#define IRQ_INTCSIH0IR 				30	/* CSIH0 receive status interrupt CSIH0 Edge 101E */
#define IRQ_INTCSIH0IRE 			31	/* CSIH0 communication error interrupt CSIH0 Edge 101F */
#define IRQ_INTCSIH0IJC 			32	/* CSIH0 job completion interrupt CSIH0 Edge 1020 */
#define IRQ_INTADCA0I2_2			32
#define IRQ_INTRLIN30 				33	/* RLIN30 interrupt RLIN30 Edge 1021 */
#define IRQ_INTRLIN30UR0 			34	/* RLIN30 transmit interrupt RLIN30 Edge 1022 */
#define IRQ_INTRLIN30UR1 			35	/* RLIN30 receive complete interrupt RLIN30 Edge 1023 */
#define IRQ_INTRLIN30UR2 			36	/* RLIN30 status interrupt RLIN30 Edge 1024 */
#define IRQ_INTP0 					37	/* External interrupt Port Edge 1025 */
#define IRQ_INTP1 					38	/* External interrupt Port Edge 1026 */
#define IRQ_INTP2 					39	/* External interrupt Port Edge 1027 */
#define IRQ_INTWDTA0 				40	/* WDTA0 interrupt WDTA0 Edge 1028 */
#define IRQ_INTWDTA1 				41  /* WDTA1 interrupt WDTA1 Edge 1029 */
#define IRQ_INTWDTA2 				42  /* WDTA2 interrupt WDTA2 Edge 102A */
#define IRQ_INTP3 					43	/* External interrupt Port Edge 102B */
#define IRQ_INTP4 					44	/* External interrupt Port Edge 102C */
#define IRQ_INTP5 					45	/* External interrupt Port Edge 102D */
#define IRQ_INTP10 					46	/* External interrupt Port Edge 102E */
#define IRQ_INTP11 					47	/* External interrupt Port Edge 102F */
#define IRQ_INTTAUD0I1 				48	/* Interrupt for CH1 of TAUD0 TAUD0 Edge 1030 */
#define IRQ_INTTAUD0I3 				49	/* Interrupt for CH3 of TAUD0 TAUD0 Edge 1031 */
#define IRQ_INTTAUD0I5 				50	/* Interrupt for CH5 of TAUD0 TAUD0 Edge 1032 */
#define IRQ_INTTAUD0I7 				51	/* Interrupt for CH7 of TAUD0 TAUD0 Edge 1033 */
#define IRQ_INTTAUD0I9 				52	/* Interrupt for CH9 of TAUD0 TAUD0 Edge 1034 */
#define IRQ_INTTAUD0I11 			53	/* Interrupt for CH11 of TAUD0 TAUD0 Edge 1035 */
#define IRQ_INTTAUD0I13 			54	/* Interrupt for CH13 of TAUD0 TAUD0 Edge 1036 */
#define IRQ_INTTAUD0I15 			55	/* Interrupt for CH15  of TAUD0 TAUD0 Edge 1037 */
#define IRQ_INTADCA0ERR 			56	/* ADCA0 error interrupt ADCA0 Edge 1038 */
#define IRQ_INTCSIG0IRE 			57	/* CSIG0 receive error interrupt CSIG0 Edge 1039 */
#define IRQ_INTRLIN20 				58	/* RLIN20 interrupt RLIN240 Edge 103A */
#define IRQ_INTRLIN21 				59 	/* RLIN21 interrupt RLIN240 Edge 103B */
#define IRQ_INTDMA0 				60 	/* DMA0 transfer completion DMAC Edge 103C */
#define IRQ_INTDMA1 				61 	/* DMA1 transfer completion DMAC Edge 103D */
#define IRQ_INTDMA2 				62	/* DMA2 transfer completion DMAC Edge 103E */
#define IRQ_INTDMA3 				63	/* DMA3 transfer completion DMAC Edge 103F */
#define IRQ_INTDMA4 				64	/* DMA4 transfer completion DMAC Edge 1040 */
#define IRQ_INTDMA5 				65	/* DMA5 transfer completion DMAC Edge 1041 */
#define IRQ_INTDMA6 				66	/* DMA6 transfer completion DMAC Edge 1042 */
#define IRQ_INTDMA7 				67	/* DMA7 transfer completion DMAC Edge 1043 */
#define IRQ_INTDMA8 				68	/* DMA8 transfer completion DMAC Edge 1044 */
#define IRQ_INTDMA9 				69	/* DMA9 transfer completion DMAC Edge 1045 */
#define IRQ_INTDMA10 				70	/* DMA10 transfer completion DMAC Edge 1046 */
#define IRQ_INTDMA11 				71	/* DMA11 transfer completion DMAC Edge 1047 */
#define IRQ_INTDMA12 				72	/* DMA12 transfer completion DMAC Edge 1048 */
#define IRQ_INTDMA13 				73	/* DMA13 transfer completion DMAC Edge 1049 */
#define IRQ_INTDMA14 				74	/* DMA14 transfer completion DMAC Edge 104A */
#define IRQ_INTDMA15 				75	/* DMA15 transfer completion DMAC Edge 104B */
#define IRQ_INTRIIC0TI 				76	/* RIIC transmit data empty interrupt RIIC0 Edge 104C */
#define IRQ_INTRIIC0TEI 			77	/* RIIC transmit end interrupt RIIC0 Level 104D */
#define IRQ_INTRIIC0RI 				78	/* RIIC receive end interrupt RIIC0 Edge 104E */
#define IRQ_INTRIIC0EE 				79	/* RIIC receive error/event interrupt RIIC0 Level 104F */
#define IRQ_INTTAUJ0I0 				80	/* Interrupt for CH0 of TAUJ0 TAUJ0 Edge 1050 */
#define IRQ_INTTAUJ0I1 				81	/* Interrupt for CH1 of TAUJ0 TAUJ0 Edge 1051 */
#define IRQ_INTTAUJ0I2 				82	/* Interrupt for CH2 of TAUJ0 TAUJ0 Edge 1052 */
#define IRQ_INTTAUJ0I3 				83	/* Interrupt for CH3 of TAUJ0 TAUJ0 Edge 1053 */
#define IRQ_INTOSTM0 				84	/* OSTM0 interrupt OSTM0 Edge 1054 */
#define IRQ_IINTENCA0IOV			85
#define IRQ_INTPWGA4                85
#define IRQ_INTENCA0IUD             86
#define IRQ_INTPWGA5                86
#define IRQ_INTENCA0I0              87
#define IRQ_INTPWGA6                87
#define IRQ_INTENCA0I1				88
#define IRQ_INTPWGA7				88
#define IRQ_INTENCA0IEC 			89	/* Encoder clear interrupt ENCA0 Edge 1059 */
#define IRQ_INTKR0 				    90	/* Key interrupt KR0 Edge 105A */
#define IRQ_INTQFULL 				91	/* PWSA queue full interrupt PWSA Edge 105B */
#define IRQ_INTPWGA0 				92	/* PWGA0 interrupt PWGA0 Edge 105C */
#define IRQ_INTPWGA1 				93	/* PWGA1 interrupt PWGA1 Edge 105D */
#define IRQ_INTPWGA2 				94	/* PWGA2 interrupt PWGA2 Edge 105E */
#define IRQ_INTPWGA3 				95	/* PWGA3 interrupt PWGA3 Edge 105F */
#define IRQ_INTPWGA8 				96	/* PWGA8 interrupt PWGA8 Edge 1060 */
#define IRQ_INTPWGA9 				97	/* PWGA9 interrupt PWGA9 Edge 1061 */
#define IRQ_INTPWGA10 				98	/* PWGA10 interrupt PWGA10 Edge 1062 */
#define IRQ_INTPWGA11 				99	/* PWGA11 interrupt PWGA11 Edge 1063 */
#define IRQ_INTPWGA12 				100 /* PWGA12 interrupt PWGA12 Edge 1064 */
#define IRQ_INTPWGA13 				101 /* PWGA13 interrupt PWGA13 Edge 1065 */
#define IRQ_INTPWGA14 				102 /* PWGA14 interrupt PWGA14 Edge 1066 */
#define IRQ_INTPWGA15 				103 /* PWGA15 interrupt PWGA15 Edge 1067 */

#define IRQ_INTFLERR 				110 /* Flash sequencer end error interrupt FACI Level 106E */
#define IRQ_INTFLENDNM 				111    /* Flash sequencer end interrupt FACI Edge 106F */
#define IRQ_INTCWEND 				112    /* LPS port polling end interrupt LPS Edge 1070 */
#define IRQ_INTRCAN1ERR 			113	/* CAN1 error interrupt RS-CAN0 Level 1071 */
#define IRQ_INTRCAN1REC 			114	/* CAN1 transmit/receive FIFO receive  */
#define IRQ_INTRCAN1TRX 			115	/* CAN1 transmit interrupt RS-CAN0 Level 1073 */
#define IRQ_INTCSIH1IC 				116	/* CSIH1 communication status interrupt CSIH1 Edge 1074 */
#define IRQ_INTTAPA0IPEK0_2			116
#define IRQ_INTCSIH1IR 				117	/* CSIH1 receive status interrupt CSIH1 Edge 1075 */
#define IRQ_INTTAPA0IVLY0_2			117
#define IRQ_INTCSIH1IRE 			118	/* CSIH1 communication error interrupt CSIH1 Edge 1076 */
#define IRQ_INTCSIG0IC_2			118
#define IRQ_INTCSIH1IJC 			119	/* CSIH1 job interrupt CSIH1 Edge 1077 */
#define IRQ_INTCSIG0IR_2			119
#define IRQ_INTRLIN31 				120	/* RLIN31 interrupt RLIN31 Edge 1078 */
#define IRQ_INTRLIN31UR0 			121	/* RLIN31 transmit interrupt RLIN31 Edge 1079 */
#define IRQ_INTRLIN31UR1 			122	/* RLIN31 receive complete interrupt RLIN31 Edge 107A */
#define IRQ_INTRLIN31UR2 			123	/* RLIN31 status interrupt RLIN31 Edge 107B */
#define IRQ_INTPWGA20 				124	/* PWGA20 interrupt PWGA20 Edge 107C */
#define IRQ_INTPWGA21 				125	/* PWGA21 interrupt PWGA21 Edge 107D */
#define IRQ_INTPWGA22 				126	/* PWGA22 interrupt PWGA22 Edge 107E */
#define IRQ_INTPWGA23 				127	/* PWGA23 interrupt PWGA23 Edge 107F */
#define IRQ_INTP6 					128	/* External interrupt Port Edge 1080 */
#define IRQ_INTP7 					129	/* External interrupt Port Edge 1081 */
#define IRQ_INTP8 					130	/* External interrupt Port Edge 1082 */
#define IRQ_INTP12 					131	/* External interrupt Port Edge 1083 */
#define IRQ_INTCSIH2IC				132
#define IRQ_INTTAUD0I0_2			132
#define IRQ_INTCSIH2IR				133
#define IRQ_INTTAUD0I4_2			133
#define IRQ_INTCSIH2IRE				134
#define IRQ_INTTAUD0I6_2			134
#define IRQ_INTCSIH2IJC				135
#define IRQ_INTTAUD0I8_2			135

#define IRQ_INTTAUB0I0 				142  /* Interrupt for CH0 of TAUB0 TAUB0 Edge 108E */
#define IRQ_INTTAUB0I1 				143  /* Interrupt for CH1 of TAUB0 TAUB0 Edge 108F */
#define IRQ_INTTAUB0I2 				144  /* Interrupt for CH2 of TAUB0 TAUB0 Edge 1090 */
#define IRQ_INTTAUB0I3              145
#define IRQ_INTPWGA16               145
#define IRQ_INTTAUB0I4 				146  /* Interrupt for CH4 of TAUB0 TAUB0 Edge 1092 */
#define IRQ_INTTAUB0I5              147
#define IRQ_INTPWGA17               147
#define IRQ_INTTAUB0I6 				148  /* Interrupt for CH6 of TAUB0 TAUB0 Edge 1094 */
#define IRQ_INTTAUB0I7              149
#define IRQ_INTPWGA18               149
#define IRQ_INTTAUB0I8 				150  /* Interrupt for CH8 of TAUB0 TAUB0 Edge 1096 */
#define IRQ_INTTAUB0I9				151
#define IRQ_INTPWGA19				151

#define IRQ_INTTAUB0I10 			152	 /* Interrupt for CH10 of TAUB0 TAUB0 Edge 1098 */
#define IRQ_INTTAUB0I11				153
#define IRQ_INTPWGA26				153
#define IRQ_INTTAUB0I12 			154	 /* Interrupt for CH12 of TAUB0 TAUB0 Edge 109A */
#define IRQ_INTTAUB0I13				155
#define IRQ_INTPWGA30				155
#define IRQ_INTTAUB0I14 			156	 /* Interrupt for CH14 of TAUB0 TAUB0 Edge 109C */
#define IRQ_INTTAUB0I15				157
#define IRQ_INTPWGA31				157
#define IRQ_INTCSIH3IC 				158  /* CSIH3 communication status interrupt CSIH3 Edge 109E */
#define Interrupt 				158  /* for CH2 of TAUD0 TAUD0 Edge */
#define IRQ_INTCSIH3IR              159
#define IRQ_INTTAUD0I10_2           159
#define IRQ_INTCSIH3IRE             160
#define IRQ_INTTAUD0I12_2           160
#define IRQ_INTCSIH3IJC             161
#define IRQ_INTTAUD0I14_2           161
#define IRQ_INTRLIN22 				162  /* RLIN22 interrupt RLIN240 Edge 10A2 */
#define IRQ_INTRLIN23 				163  /* RLIN23 interrupt RLIN240 Edge 10A3 */
#define IRQ_INTRLIN32 				164  /* RLIN32 interrupt RLIN32 Edge 10A4 */
#define IRQ_INTRLIN32UR0 			165  /* RLIN32 transmit interrupt RLIN32 Edge 10A5 */
#define IRQ_INTRLIN32UR1 			166  /* RLIN32 receive complete interrupt RLIN32 Edge 10A6 */
#define IRQ_INTRLIN32UR2 			167  /* RLIN32 status interrupt RLIN32 Edge 10A7 */
#define IRQ_INTTAUJ1I0 				168  /* Interrupt for CH0 of TAUJ1 TAUJ1 Edge 10A8 */
#define IRQ_INTTAUJ1I1 				169  /* Interrupt for CH1 of TAUJ1 TAUJ1 Edge 10A9 */
#define IRQ_INTTAUJ1I2 				170  /* Interrupt for CH2 of TAUJ1 TAUJ1 Edge 10AA */
#define IRQ_INTTAUJ1I3 				171  /* Interrupt for CH3 of TAUJ1 TAUJ1 Edge 10AB */

#define IRQ_INTFLX0FDA 				173  /* FIFO transfer interrupt FLXA0 Level 10AD */
#define IRQ_INTFLX0FW 				174  /* FIFO transfer warning interrupt FLXA0 Level 10AE */
#define IRQ_INTFLX0IQE 				175  /* Input queue empty interrupt FLXA0 Level 10AF */
#define IRQ_INTFLX0IQF 				176  /* Input queue full interrupt FLXA0 Level 10B0 */
#define IRQ_INTFLX0OT 				177  /* Output transfer end interrupt FLXA0 Level 10B1 */
#define IRQ_INTFLX0OW 				178  /* Output transfer warning interrupt FLXA0 Level 10B2 */
#define IRQ_INTFLX0LINE0 			179  /* FlexRay0 interrupt FLXA0 Level 10B3 */
#define IRQ_INTFLX0LINE1 			180  /* FlexRay1 interrupt FLXA0 Level 10B4 */
#define IRQ_INTFLX0TIM0 			181  /* Timer 0 interrupt FLXA0 Level 10B5 */
#define IRQ_INTFLX0TIM1 			182  /* Timer 1 interrupt FLXA0 Level 10B6 */
#define IRQ_INTFLX0TIM2 			183  /* Timer 2 interrupt FLXA0 Level 10B7 */
#define IRQ_INTPWGA24 				184  /* PWGA24 interrupt PWGA24 Edge 10B8 */
#define IRQ_INTPWGA25 				185  /* PWGA25 interrupt PWGA25 Edge 10B9 */
#define IRQ_INTPWGA27 				186  /* PWGA27 interrupt PWGA27 Edge 10BA */
#define IRQ_INTPWGA28 				187  /* PWGA28 interrupt PWGA28 Edge 10BB */
#define IRQ_INTPWGA29 				188  /* PWGA29 interrupt PWGA29 Edge 10BC */
#define IRQ_INTPWGA32 				189  /* PWGA32 interrupt PWGA32 Edge 10BD */
#define IRQ_INTPWGA33 				190  /* PWGA33 interrupt PWGA33 Edge 10BE */
#define IRQ_INTPWGA34 				191  /* PWGA34 interrupt PWGA34 Edge 10BF */
#define IRQ_INTPWGA35 				192  /* PWGA35 interrupt PWGA35 Edge 10C0 */
#define IRQ_INTPWGA36 				193  /* PWGA36 interrupt PWGA36 Edge 10C1 */
#define IRQ_INTPWGA37 				194  /* PWGA37 interrupt PWGA37 Edge 10C2 */
#define IRQ_INTPWGA38 				195  /* PWGA38 interrupt PWGA38 Edge 10C3 */
#define IRQ_INTPWGA39 				196  /* PWGA39 interrupt PWGA39 Edge 10C4 */
#define IRQ_INTPWGA40 				197  /* PWGA40 interrupt PWGA40 Edge 10C5 */
#define IRQ_INTPWGA41 				198  /* PWGA41 interrupt PWGA41 Edge 10C6 */
#define IRQ_INTPWGA42 				199  /* PWGA42 interrupt PWGA42 Edge 10C7 */
#define IRQ_INTPWGA43 				200  /* PWGA43 interrupt PWGA43 Edge 10C8 */
#define IRQ_INTPWGA44 				201  /* PWGA44 interrupt PWGA44 Edge 10C9 */
#define IRQ_INTPWGA45 				202  /* PWGA45 interrupt PWGA45 Edge 10CA */
#define IRQ_INTPWGA46 				203  /* PWGA46 interrupt PWGA46 Edge 10CB */
#define IRQ_INTPWGA47 				204  /* PWGA47 interrupt PWGA47 Edge 10CC */
#define IRQ_INTP9 					205  /* External interrupt Port Edge 10CD */
#define IRQ_INTP13 					206  /* External interrupt Port Edge 10CE */
#define IRQ_INTP14 					207  /* External interrupt Port Edge 10CF */
#define IRQ_INTP15 					208  /* External interrupt Port Edge 10D0 */
#define IRQ_INTRTCA01S 				209  /* 1 second interrupt RTCA Edge 10D1 */
#define IRQ_INTRTCA0AL 				210  /* Alarm interrupt RTCA Edge 10D2 */
#define IRQ_INTRTCA0R 				211  /* Periodic interrupt RTCA Edge 10D3 */
#define IRQ_INTADCA1ERR 			212  /* ADCA1 error interrupt ADCA1 Edge 10D4 */
#define IRQ_INTADCA1I0 				213  /* ADCA1 SG1 end interrupt ADCA1 Edge 10D5 */
#define IRQ_INTADCA1I1 				214  /* ADCA1 SG2 end interrupt ADCA1 Edge 10D6 */
#define IRQ_INTADCA1I2 				215  /* ADCA1 SG3 end interrupt ADCA1 Edge 10D7 */

#define IRQ_INTRCAN2ERR 			217  /* CAN2 error interrupt RS-CAN0 Level 10D9 */
#define IRQ_INTRCAN2REC 			218  /* CAN2 transmit/receive FIFO receive  */
#define IRQ_INTRCAN2TRX 			219  /* CAN2 transmit interrupt RS-CAN0 Level 10DB */
#define IRQ_INTRCAN3ERR 			220  /* CAN3 error interrupt RS-CAN0 Level 10DC */
#define IRQ_INTRCAN3REC 			221  /* CAN3 transmit/receive FIFO receive  */
#define IRQ_INTRCAN3TRX 			222  /* CAN3 transmit interrupt RS-CAN0 Level 10DE */
#define IRQ_INTCSIG1IC 				223  /* CSIG1 communication status interrupt CSIG1 Edge 10DF */
#define IRQ_INTCSIG1IR 				224  /* CSIG1 receive status interrupt CSIG1 Edge 10E0 */
#define IRQ_INTCSIG1IRE 			225  /* CSIG1 receive error interrupt CSIG1 Edge 10E1 */
#define IRQ_INTRLIN24 				226  /* RLIN24 interrupt RLIN241 Edge 10E2 */
#define IRQ_INTRLIN25 				227  /* RLIN25 interrupt RLIN241 Edge 10E3 */
#define IRQ_INTRLIN33 				228  /* RLIN33 interrupt RLIN33 Edge 10E4 */
#define IRQ_INTRLIN33UR0 			229  /* RLIN33 transmit interrupt RLIN33 Edge 10E5 */
#define IRQ_INTRLIN33UR1 			230  /* RLIN33 receive complete interrupt RLIN33 Edge 10E6 */
#define IRQ_INTRLIN33UR2 			231  /* RLIN33 status interrupt RLIN33 Edge 10E7 */
#define IRQ_INTRLIN34 				232  /* RLIN34 interrupt RLIN34 Edge 10E8 */
#define IRQ_INTRLIN34UR0 			233  /* RLIN34 transmit interrupt RLIN34 Edge 10E9 */
#define IRQ_INTRLIN34UR1 			234  /* RLIN34 receive complete interrupt RLIN34 Edge 10EA */
#define IRQ_INTRLIN34UR2 			235  /* RLIN34 status interrupt RLIN34 Edge 10EB */

#define IRQ_INTRLIN35 				236  /* RLIN35 interrupt RLIN35 Edge 10EC */
#define IRQ_INTRLIN35UR0 			237  /* RLIN35 transmit interrupt RLIN35 Edge 10ED */
#define IRQ_INTRLIN35UR1 			238  /* RLIN35 receive complete interrupt RLIN35 Edge 10EE */
#define IRQ_INTRLIN35UR2 			239  /* RLIN35 status interrupt RLIN35 Edge 10EF */
#define IRQ_INTPWGA48 				240  /* PWGA48 interrupt PWGA48 Edge 10F0 */
#define IRQ_INTPWGA49 				241  /* PWGA49 interrupt PWGA49 Edge 10F1 */
#define IRQ_INTPWGA50 				242  /* PWGA50 interrupt PWGA50 Edge 10F2 */
#define IRQ_INTPWGA51 				243  /* PWGA51 interrupt PWGA51 Edge 10F3 */
#define IRQ_INTPWGA52 				244  /* PWGA52 interrupt PWGA52 Edge 10F4 */
#define IRQ_INTPWGA53 				245  /* PWGA53 interrupt PWGA53 Edge 10F5 */
#define IRQ_INTPWGA54 				246  /* PWGA54 interrupt PWGA54 Edge 10F6 */
#define IRQ_INTPWGA55 				247  /* PWGA55 interrupt PWGA55 Edge 10F7 */
#define IRQ_INTPWGA56 				248  /* PWGA56 interrupt PWGA56 Edge 10F8 */
#define IRQ_INTPWGA57 				249  /* PWGA57 interrupt PWGA57 Edge 10F9 */
#define IRQ_INTPWGA58 				250  /* PWGA58 interrupt PWGA58 Edge 10FA */
#define IRQ_INTPWGA59 				251  /* PWGA59 interrupt PWGA59 Edge 10FB */
#define IRQ_INTPWGA60 				252  /* PWGA60 interrupt PWGA60 Edge 10FC */
#define IRQ_INTPWGA61 				253  /* PWGA61 interrupt PWGA61 Edge 10FD */
#define IRQ_INTPWGA62 				254  /* PWGA62 interrupt PWGA62 Edge 10FE */
#define IRQ_INTPWGA63 				255  /* PWGA63 interrupt PWGA63 Edge 10FF */
#define IRQ_INTTAUB1I0 				256  /* Interrupt for CH0 of TAUB1 TAUB1 Edge 1100 */
#define IRQ_INTTAUB1I1 				257  /* Interrupt for CH1 of TAUB1 TAUB1 Edge 1101 */
#define IRQ_INTTAUB1I2 				258  /* Interrupt for CH2 of TAUB1 TAUB1 Edge 1102 */
#define IRQ_INTTAUB1I3 				259  /* Interrupt for CH3 of TAUB1 TAUB1 Edge 1103 */
#define IRQ_INTTAUB1I4 				260  /* Interrupt for CH4 of TAUB1 TAUB1 Edge 1104 */
#define IRQ_INTTAUB1I5 				261  /* Interrupt for CH5 of TAUB1t TAUB1 Edge 1105 */
#define IRQ_INTTAUB1I6 				262  /* Interrupt for CH6 of TAUB1 TAUB1 Edge 1106 */
#define IRQ_INTTAUB1I7 				263  /* Interrupt for CH7 of TAUB1t TAUB1 Edge 1107 */
#define IRQ_INTTAUB1I8 				264  /* Interrupt for CH8 of TAUB1 TAUB1 Edge 1108 */
#define IRQ_INTTAUB1I9 				265  /* Interrupt for CH9 of TAUB1 TAUB1 Edge 1109 */
#define IRQ_INTTAUB1I10 			266  /* Interrupt for CH10 of TAUB1 TAUB1 Edge 110A */
#define IRQ_INTTAUB1I11 			267  /* Interrupt for CH11 of TAUB1 TAUB1 Edge 110B */
#define IRQ_INTTAUB1I12 			268  /* Interrupt for CH12 of TAUB1 TAUB1 Edge 110C */
#define IRQ_INTTAUB1I13 			269  /* Interrupt for CH13 of TAUB1 TAUB1 Edge 110D */
#define IRQ_INTTAUB1I14 			270  /* Interrupt for CH14 of TAUB1 TAUB1 Edge 110E */
#define IRQ_INTTAUB1I15 			271  /* Interrupt for CH15 of TAUB1 TAUB1 Edge 110F */
#define IRQ_INTRCAN4ERR 			272  /* CAN4 error interrupt RS-CAN0 Level 1110 */
#define IRQ_INTRCAN4REC 			273  /* CAN4 transmit/receive FIFO receive  */
#define IRQ_INTRCAN4TRX 			274  /* CAN4 transmit interrupt RS-CAN0 Level 1112 */
#define IRQ_INTRLIN26 				275  /* RLIN26 interrupt RLIN241 Edge 1113 */
#define IRQ_INTRLIN27 				276  /* RLIN27 interrupt RLIN241 Edge 1114 */
#define IRQ_INTPWGA64 				277  /* PWGA64 interrupt PWGA64 Edge 1115 */
#define IRQ_INTPWGA65 				278  /* PWGA65 interrupt PWGA65 Edge 1116 */
#define IRQ_INTPWGA66 				279  /* PWGA66 interrupt PWGA66 Edge 1117 */
#define IRQ_INTPWGA67 				280  /* PWGA67 interrupt PWGA67 Edge 1118 */
#define IRQ_INTPWGA68 				281  /* PWGA68 interrupt PWGA68 Edge 1119 */

#define IRQ_INTPWGA69 				282  /* PWGA69 interrupt PWGA69 Edge 111A */
#define IRQ_INTPWGA70 				283  /* PWGA70 interrupt PWGA70 Edge 111B */
#define IRQ_INTPWGA71 				284  /* PWGA71 interrupt PWGA71 Edge 111C */
#define IRQ_INTRLIN28 				285  /* RLIN28 interrupt RLIN242 Edge 111D */
#define IRQ_INTRLIN29 				286  /* RLIN29 interrupt RLIN242 Edge 111E */
#define IRQ_INTRCAN5ERR 			287  /* CAN5 error interrupt RS-CAN0 Level 111F */
#define IRQ_INTRCAN5REC 			288  /* CAN5 transmit/receive FIFO receive  */
#define IRQ_INTRCAN5TRX 			289  /* CAN5 transmit interrupt RS-CAN0 Level 1121 */
#define IRQ_INTPWGA72 				290  /* PWGA72 interrupt PWGA72 Edge 1122 */
#define IRQ_INTPWGA73 				291  /* PWGA73 interrupt PWGA73 Edge 1123 */
#define IRQ_INTPWGA74 				292  /* PWGA74 interrupt PWGA74 Edge 1124 */
#define IRQ_INTPWGA75 				293  /* PWGA75 interrupt PWGA75 Edge 1125 */
#define IRQ_INTPWGA76 				294  /* PWGA76 interrupt PWGA76 Edge 1126 */
#define IRQ_INTPWGA77 				295  /* PWGA77 interrupt PWGA77 Edge 1127 */
#define IRQ_INTPWGA78 				296  /* PWGA78 interrupt PWGA78 Edge 1128 */
#define IRQ_INTPWGA79 				297  /* PWGA79 interrupt PWGA79 Edge 1129 */
#define IRQ_INTDMA16 				298  /* DMA16 transfer completion DMAC Edge 112A */
#define IRQ_INTDMA17 				299  /* DMA17 transfer completion DMAC Edge 112B */
#define IRQ_INTDMA18 				300  /* DMA18 transfer completion DMAC Edge 112C */
#define IRQ_INTDMA19 				301  /* DMA19 transfer completion DMAC Edge 112D */
#define IRQ_INTDMA20 				302  /* DMA20 transfer completion DMAC Edge 112E */
#define IRQ_INTDMA21 				303  /* DMA21 transfer completion DMAC Edge 112F */
#define IRQ_INTDMA22 				304  /* DMA22 transfer completion DMAC Edge 1130 */
#define IRQ_INTDMA23 				305  /* DMA23 transfer completion DMAC Edge 1131 */
#define IRQ_INTDMA24 				306  /* DMA24 transfer completion DMAC Edge 1132 */
#define IRQ_INTDMA25 				307  /* DMA25 transfer completion DMAC Edge 1133 */
#define IRQ_INTDMA26 				308  /* DMA26 transfer completion DMAC Edge 1134 */
#define IRQ_INTDMA27 				309  /* DMA27 transfer completion DMAC Edge 1135 */
#define IRQ_INTDMA28 				310  /* DMA28 transfer completion DMAC Edge 1136 */
#define IRQ_INTDMA29 				311  /* DMA29 transfer completion DMAC Edge 1137 */
#define IRQ_INTDMA30 				312  /* DMA30 transfer completion DMAC Edge 1138 */
#define IRQ_INTDMA31 				313  /* DMA31 transfer completion DMAC Edge 1139 */
#define IRQ_INTOSTM5 				314  /* OSTM5 interrupt OSTM5 Edge 113A */
#define IRQ_INTETNB0DATA 			315  /* ETNB data related interrupt ETH0 Level 113B */
#define IRQ_INTETNB0ERR 			316  /* ETNB error related interrupt ETH0 Level 113C */
#define IRQ_INTETNB0MNG 			317  /* ETNB management related interrupt ETH0 Level 113D */
#define IRQ_INTETNB0MAC 			318  /* ETNB MAC interrupt ETH0 Level 113E */
#define IRQ_INTRCANGERR1 			319  /* CAN global error interrupt RS-CAN1 Level 113F */
#define IRQ_INTRCANGRECC1 			320  /* CAN receive FIFO interrupt RS-CAN1 Level 1140 */
#define IRQ_INTRCAN6ERR 			321  /* CAN6 error interrupt RS-CAN1 Level 1141 */
#define IRQ_INTRCAN6REC 			322  /* CAN6 transmit/receive FIFO receive 1142 */
#define IRQ_INTRCAN6TRX 			323  /* CAN6 transmit interrupt RS-CAN1 Level 1143 */
#define IRQ_INTRLIN210 				324  /* RLIN210 interrupt RLIN242 Edge 1144 */
#define IRQ_INTRLIN211 				325  /* RLIN211 interrupt RLIN242 Edge 1145 */
#define IRQ_INTCSIG2IC 				326  /* CSIG2 communication status interrupt CSIG2 Edge 1146 */

#define IRQ_INTCSIG2IR 				327  /* CSIG2 receive status interrupt CSIG2 Edge 1147 */
#define IRQ_INTCSIG2IRE 			328  /* CSIG2 receive error interrupt CSIG2 Edge 1148 */
#define IRQ_INTCSIG3IC 				329  /* CSIG3 communication status interrupt CSIG3 Edge 1149 */
#define IRQ_INTCSIG3IR 				330  /* CSIG3 receive status interrupt CSIG3 Edge 114A */
#define IRQ_INTCSIG3IRE 			331  /* CSIG3 receive error interrupt CSIG3 Edge 114B */
#define IRQ_INTRCAN7ERR             332  /* CAN7 error interrupt RS-CAN1 Level 114C */
#define IRQ_INTRCAN7REC             333  /* CAN7 transmit/receive FIFO receive 114D */
#define IRQ_INTRCAN7TRX             334  /* CAN7 transmit interrupt RS-CAN1 Level 114E */
#define IRQ_INTPWGA80 				335  /* PWGA80 interrupt PWGA80 Edge 114F */
#define IRQ_INTPWGA81 				336  /* PWGA81 interrupt PWGA81 Edge 1150 */
#define IRQ_INTPWGA82 				337  /* PWGA82 interrupt PWGA82 Edge 1151 */
#define IRQ_INTPWGA83 				338  /* PWGA83 interrupt PWGA83 Edge 1152 */
#define IRQ_INTPWGA84 				339  /* PWGA84 interrupt PWGA84 Edge 1153 */
#define IRQ_INTPWGA85 				340  /* PWGA85 interrupt PWGA85 Edge 1154 */
#define IRQ_INTPWGA86 				341  /* PWGA86 interrupt PWGA86 Edge 1155 */
#define IRQ_INTPWGA87 				342  /* PWGA87 interrupt PWGA87 Edge 1156 */
#define IRQ_INTPWGA88 				343  /* PWGA88 interrupt PWGA88 Edge 1157 */
#define IRQ_INTPWGA89 				344  /* PWGA89 interrupt PWGA89 Edge 1158 */
#define IRQ_INTPWGA90 				345  /* PWGA90 interrupt PWGA90 Edge 1159 */
#define IRQ_INTPWGA91 				346  /* PWGA91 interrupt PWGA91 Edge 115A */
#define IRQ_INTPWGA92 				347  /* PWGA92 interrupt PWGA92 Edge 115B */
#define IRQ_INTPWGA93 				348  /* PWGA93 interrupt PWGA93 Edge 115C */
#define IRQ_INTPWGA94 				349  /* PWGA94 interrupt PWGA94 Edge 115D */
#define IRQ_INTPWGA95 				350  /* PWGA95 interrupt PWGA95 Edge 115E */

#define IRQ_CNT					351
#define IRQ_SPI_CNT				64

#define NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS		IRQ_CNT
#define IRQ_INTERRUPT_OFFSET					0

typedef enum
{
    /* Directly from the PLLs */
    C_CPLLCLK,      /* PLL0 */
    C_PPLLCLK,      /* PPL1 */
    C_PPLLCLK2,     /* PPL1/2 */
    C_CPUCLK,       /* CPU */
    C_CPUCLK2,      /* CPU/2 */
    C_CPUCLK4,      /* CPU/4 */

    /* Clock Domain Names */
    C_AWO_WDTA,
    C_AWO_TAUJ,
    C_AWO_RTCA,
    C_AWO_ADCA,
    C_AWO_FOUT,
    C_ISO_CPUCLK,
    C_ISO_PERI1,
    C_ISO_PERI2,
    C_ISO_LIN,
    C_ISO_ADCA,
    C_ISO_CAN,
    C_ISO_CANOSC,
    C_ISO_CSI,
    C_ISO_IIC,
} Mcu_Arc_PeriperalClock_t;

#define Irq_SOI()

typedef uint8_t Cpu_t;
typedef uint16 IrqType;

#endif /* IRQ_RH850F1H_H_ */
