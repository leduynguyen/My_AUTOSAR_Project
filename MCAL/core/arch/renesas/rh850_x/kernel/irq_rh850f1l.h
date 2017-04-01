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

#ifndef IRQ_RH850F1L_H_
#define IRQ_RH850F1L_H_



/* 1. Copy table from Table 6.4 in F1L
 * 2. $ gawk '{printf "#define IRQ_%-20s %s // %s %s %s %s %s \n",$5,$1,$6, $7, $8, $9, $10 }' blaha.txt"
 */

#define IRQ_INTTAUD0I0           0  /* Interrupt for TAUD0 channel 0 TAUD0 Edge */
#define IRQ_INTCSIH2IC_1         0  /* CSIH2 communication status interrupt CSIH2 Edge */
#define IRQ_INTTAUD0I2           1  /* Interrupt for TAUD0 channel 2 TAUD0 Edge */
#define IRQ_INTCSIH3IC_1         1  /* CSIH3 communication status interrupt CSIH3 Edge — */
#define IRQ_INTTAUD0I4           2  /* Interrupt for TAUD0 channel 4 TAUD0 Edge */
#define IRQ_INTTAUD0I6           3  /* Interrupt for TAUD0 channel 6 TAUD0 Edge */
#define IRQ_INTTAUD0I8           4  /* Interrupt for TAUD0 channel 8 TAUD0 Edge */
#define IRQ_INTTAUD0I10          5  /* Interrupt for TAUD0 channel 10 TAUD0 Edge */
#define IRQ_INTCSIH3IR_1         5  /* CSIH3 receive status interrupt CSIH3 Edge — */
#define IRQ_INTTAUD0I12          6  /* Interrupt for TAUD0 channel 12 TAUD0 Edge */
#define IRQ_INTCSIH3IRE_1        6  /* CSIH3 communication error interrupt CSIH3 Edge — */
#define IRQ_INTTAUD0I14          7  /* Interrupt for TAUD0 channel 14 TAUD0 Edge */
#define IRQ_INTCSIH3IJC_1        7  /* CSIH3 job completion interrupt CSIH3 Edge — */
#define IRQ_INTTAPA0IPEK0        8  /* TAPA0 peak interrupt 0 TAPA0 Edge */
#define IRQ_INTCSIH1IC_1         8  /* CSIH1 communication status interrupt CSIH1 Edge */
#define IRQ_INTTAPA0IVLY0        9  /* TAPA0 valley interrupt 0 TAPA0 Edge */
#define IRQ_INTCSIH1IR_1         9  /* CSIH1 receive status interrupt CSIH1 Edge */
#define IRQ_INTADCA0I0           10  /* ADCA0 scan group 1 (SG1) end interruptADCA0 Edge */
#define IRQ_INTADCA0I1           11  /* ADCA0 scan group 2 (SG2) end interrupt ADCA0 Edge */
#define IRQ_INTADCA0I2           12  /* ADCA0 scan group 3 (SG3) endinterrupt ADCA0 Edge */
#define IRQ_INTDCUTDI            13  /* Dedicated interrupt for on-chip debugfunction Port Edge */
#define IRQ_INTRCANGERR          14  /* CAN global error interrupt RSCAN0 Level */
#define IRQ_INTRCANGRECC         15  /* CAN receive FIFO interrupt RSCAN0 Level */
#define IRQ_INTRCAN0ERR          16  /* CAN0 error interrupt RSCAN0 Level */
#define IRQ_INTRCAN0REC          17  /* CAN0 transmit/receive FIFO receive complete interrupt RSCAN0 Level */
#define IRQ_INTRCAN0TRX          18  /* CAN0 transmit interrupt RSCAN0 Level */
#define IRQ_INTCSIG0IC           19  /* CSIG0 communication status interrupt CSIG0 Edge */
#define IRQ_INTCSIH1IRE_1        19  /* CSIH1 communication error interrupt CSIH1 Edge */
#define IRQ_INTCSIG0IR           20  /* CSIG0 receive status interrupt CSIG0 Edge */
#define IRQ_INTCSIH1IJC_1        20  /* CSIH1 job complete interrupt CSIH1 Edge */
#define IRQ_INTCSIH0IC           21  /* CSIH0 communication status interrupt CSIH0 Edge */
#define IRQ_INTCSIH0IR           22  /* CSIH0 receive status interrupt CSIH0 Edge */
#define IRQ_INTCSIH0IRE          23  /* CSIH0 communication error interrupt CSIH0 Edge */
#define IRQ_INTCSIH0IJC          24  /* CSIH0 job completion interrupt CSIH0 Edge */
#define IRQ_INTRLIN30            25  /* RLIN30 interrupt RLIN30 Edge */
#define IRQ_INTRLIN30UR0         26  /* RLIN30 transmit interrupt RLIN30 Edge */
#define IRQ_INTRLIN30UR1         27  /* RLIN30 reception complete interrupt RLIN30 Edge */
#define IRQ_INTRLIN30UR2         28  /* RLIN30 status interrupt RLIN30 Edge */
#define IRQ_INTP0                29  /* External interrupt Port Edge/Level */
#define IRQ_INTCSIH2IR_1         29  /* CSIH2 reception status interrupt CSIH2 Edge */
#define IRQ_INTP1                30  /* External interrupt Port Edge/Level */
#define IRQ_INTCSIH2IRE_1        30  /* CSIH2 communication error interrupt CSIH2 Edge */
#define IRQ_INTP2                31  /* External interrupt  Port Edge/Level */
#define IRQ_INTCSIH2IJC_1        31  /* CSIH2 job completion interrupt CSIH2 Edge */
#define IRQ_INTWDTA0             32  /* WDTA0 75% interrupt WDTA0 Edge */
#define IRQ_INTWDTA1             33  /* WDTA1 75% interrupt WDTA1 Edge */
#define IRQ_INTP3                34  /* External interrupt Port Edge/Level */
#define IRQ_INTP4                35  /* External interrupt Port Edge/ Level */
#define IRQ_INTP5                36  /* External interrupt Port Edge/Level */
#define IRQ_INTP10               37  /* External interrupt Port Edge/Level */
#define IRQ_INTP11               38  /* External interrupt Port Edge/Level */
#define IRQ_INTTAUD0I1           39  /* Interrupt for TAUD0 channel 1 TAUD0 Edge */
#define IRQ_INTTAUD0I3           40  /* Interrupt for TAUD0 channel 3 TAUD0 Edge */
#define IRQ_INTTAUD0I5           41  /* Interrupt for TAUD0 channel 5 TAUD0 Edge */
#define IRQ_INTTAUD0I7           42  /* Interrupt for TAUD0 channel 7 TAUD0 Edge */
#define IRQ_INTTAUD0I9           43  /* Interrupt for TAUD0 channel 9 TAUD0 Edge */
#define IRQ_INTTAUD0I11          44  /* Interrupt for TAUD0 channel 11 TAUD0 Edge */
#define IRQ_INTTAUD0I13          45  /* Interrupt for TAUD0 channel 13 TAUD0 Edge */
#define IRQ_INTTAUD0I15          46  /* Interrupt for TAUD0 channel 15 TAUD0 Edge */
#define IRQ_INTADCA0ERR          47  /* ADCA0 error interrupt ADCA0 Edge */
#define IRQ_INTCSIG0IRE          49  /* CSIG0 communication error interrupt CSIG0 Edge */
#define IRQ_INTRLIN20            50  /* RLIN20 interrupt RLIN240 Edge */
#define IRQ_INTRLIN21            51  /* RLIN21 interrupt RLIN240 Edge */
#define IRQ_INTDMA0              52  /* DMA0 transfer completion DMAC Edge */
#define IRQ_INTDMA1              53  /* DMA1 transfer completion DMAC Edge */
#define IRQ_INTDMA2              54  /* DMA2 transfer completion DMAC Edge */
#define IRQ_INTDMA3              55  /* DMA3 transfer completion DMAC Edge */
#define IRQ_INTDMA4              56  /* DMA4 transfer completion DMAC Edge */
#define IRQ_INTDMA5              57  /* DMA5 transfer completion DMAC Edge */
#define IRQ_INTDMA6              58  /* DMA6 transfer completion DMAC Edge */
#define IRQ_INTDMA7              59  /* DMA7 transfer completion DMAC Edge */
#define IRQ_INTDMA8              60  /* DMA8 transfer completion DMAC Edge */
#define IRQ_INTDMA9              61  /* DMA9 transfer completion DMAC Edge */
#define IRQ_INTDMA10             62  /* DMA10 transfer completion DMAC Edge */
#define IRQ_INTDMA11             63  /* DMA11 transfer completion DMAC Edge */
#define IRQ_INTDMA12             64  /* DMA12 transfer completion DMAC Edge */
#define IRQ_INTDMA13             65  /* DMA13 transfer completion DMAC Edge */
#define IRQ_INTDMA14             66  /* DMA14 transfer completion DMAC Edge */
#define IRQ_INTDMA15             67  /* DMA15 transfer completion DMAC Edge */
#define IRQ_INTRIIC0TI           68  /* RIIC transmit data empty interrupt RIIC0 Edge */
#define IRQ_INTRIIC0TEI          69  /* RIIC transmit end interrupt RIIC0 Level */
#define IRQ_INTRIIC0RI           70  /* RIIC receive end interrupt RIIC0 Edge */
#define IRQ_INTRIIC0EE           71  /* RIIC communication error/event interrupt RIIC0 Level */
#define IRQ_INTTAUJ0I0           72  /* Interrupt for TAUJ0 channel 0 TAUJ0 Edge */
#define IRQ_INTTAUJ0I1           73  /* Interrupt for TAUJ0 channel 1 TAUJ0 Edge */
#define IRQ_INTTAUJ0I2           74  /* Interrupt for TAUJ0 channel 2 TAUJ0 Edge */
#define IRQ_INTTAUJ0I3           75  /* Interrupt for TAUJ0 channel 3 TAUJ0 Edge */
#define IRQ_INTOSTM0             76  /* OSTM0 interrupt OSTM0 Edge */
#define IRQ_INTENCA0IOV          77  /* ENCA0 overflow interrupt ENCA0 Edge 104DH v v v v v v +134H ICPWGA4 FFFF */
#define IRQ_INTENCA0IUD          78  /* ENCA0 underflow interrupt ENCA0 Edge 104EH v v v v v v +138H ICPWGA5 FFFF */
#define IRQ_INTENCA0I0           79  /* ENCA0 capture/compare match interrupt 0 ENCA0 Edge 104FH v v v v v v +13CH ICPWGA6 FFFF */
#define IRQ_INTENCA0I1           80  /* ENCA0 capture/compare match interrupt 1 ENCA0 Edge */
#define IRQ_INTPWGA7             80  /* PWGA7 interrupt PWGA7 Edge */
#define IRQ_INTENCA0IEC          81  /* ENCA0 encoder clear interrupt ENCA0 Edge */
#define IRQ_INTKR0               82  /* KR0 key interrupt KR0 Edge */
#define IRQ_INTQFULL             83  /* PWSA queue full interrupt PWSA Edge */
#define IRQ_INTPWGA0             84  /* PWGA0 interrupt PWGA0 Edge */
#define IRQ_INTPWGA1             85  /* PWGA1 interrupt PWGA1 Edge */
#define IRQ_INTPWGA2             86  /* PWGA2 interrupt PWGA2 Edge */
#define IRQ_INTPWGA3             87  /* PWGA3 interrupt PWGA3 Edge */
#define IRQ_INTPWGA8             88  /* PWGA8 interrupt PWGA8 Edge */
#define IRQ_INTPWGA9             89  /* PWGA9 interrupt PWGA9 Edge */
#define IRQ_INTPWGA10            90  /* PWGA10 interrupt PWGA10 Edge */
#define IRQ_INTPWGA11            91  /* PWGA11 interrupt PWGA11 Edge */
#define IRQ_INTPWGA12            92  /* PWGA12 interrupt PWGA12 Edge */
#define IRQ_INTPWGA13            93  /* PWGA13 interrupt PWGA13 Edge */
#define IRQ_INTPWGA14            94  /* PWGA14 interrupt PWGA14 Edge */
#define IRQ_INTPWGA15            95  /* PWGA15 interrupt PWGA15 Edge */
#define IRQ_INTFLERR             102  /* Flash sequencer access error interrupt*12 Flash Level */
#define IRQ_INTFLENDNM           103  /* Flash sequencer end interrupt*12 Flash Edge */
#define IRQ_INTCWEND             104  /* LPS0 port polling end interrupt LPS Edge */
#define IRQ_INTRCAN1ERR          105  /* CAN1 error interrupt RSCAN0 Level */
#define IRQ_INTRCAN1REC          106  /* CAN1 transmit/receive FIFO receive complete interrupt RSCAN0 Level */
#define IRQ_INTRCAN1TRX          107  /* CAN1 transmit interrupt RSCAN0 Level */
#define IRQ_INTCSIH1IC           108  /* CSIH1 communication status interrupt CSIH1 Edge 106CH */
#define IRQ_INTCSIH1IR           109  /* CSIH1 receive status interrupt CSIH1 Edge 106DH */
#define IRQ_INTCSIH1IRE          110  /* CSIH1 communication error interrupt CSIH1 Edge 106EH */
#define IRQ_ICCSIG0IC_2          110  /* FFFF A0DCH INTCSIG0IC_2*6 CSIG0 communication status interrupt CSIG0 Edge */
#define IRQ_INTCSIH1IJC          111  /* CSIH1 job completion interrupt CSIH1 Edge 106FH */
#define IRQ_ICCSIG0IR_2          111  /* INTCSIG0IR_2*6 CSIG0 receive status interrupt CSIG0 Edge */
#define IRQ_INTRLIN31            112  /* RLIN31 interrupt RLIN31 Edge */
#define IRQ_INTRLIN31UR0         113  /* RLIN31 transmit interrupt RLIN31 Edge */
#define IRQ_INTRLIN31UR1         114  /* RLIN31 reception complete interrupt RLIN31 Edge */
#define IRQ_INTRLIN31UR2         115  /* RLIN31 status interrupt RLIN31 Edge */
#define IRQ_INTPWGA20            116  /* PWGA20 interrupt PWGA20 Edge */
#define IRQ_INTPWGA21            117  /* PWGA21 interrupt PWGA21 Edge */
#define IRQ_INTPWGA22            118  /* PWGA22 interrupt PWGA22 Edge */
#define IRQ_INTPWGA23            119  /* PWGA23 interrupt PWGA23 Edge */
#define IRQ_INTP6                120  /* External interrupt Port Edge/Level */
#define IRQ_INTP7                121  /* External interrupt Port Edge/Level */
#define IRQ_INTP8                122  /* External interrupt Port Edge/Level 107AH */
#define IRQ_INTP12               123  /* External interrupt Port Edge/Level 107BH */
#define IRQ_INTCSIH2IC           124  /* CSIH2 communication status interrupt CSIH2 Edge 107CH */
#define IRQ_ICTAUD0I0_2          124  /* INTTAUD0I0_2*6 Interrupt for TAUD0 channel 0 TAUD0 Edge */
#define IRQ_INTCSIH2IR           125  /* CSIH2 receive status interrupt CSIH2 Edge 107DH */
#define IRQ_ICP0_2               125  /* INTP0_2*6 External interrupt Port Edge/Level */
#define IRQ_INTCSIH2IRE          126  /* CSIH2 communication error interrupt CSIH2 Edge 107EH */
#define IRQ_ICP1_2               126  /* INTP1_2*6 External interrupt Port Edge/Level */
#define IRQ_INTCSIH2IJC          127  /* CSIH2 job completion interrupt CSIH2 Edge 107FH */
#define IRQ_ICP2_2               127  /* A0FEH INTP2_2*6 External interrupt Port Edge/Level */
#define IRQ_INTTAUB0I0           134  /* Interrupt for TAUB0 channel 0 TAUB0 Edge */
#define IRQ_INTTAUB0I1           135  /* Interrupt for TAUB0 channel 1 TAUB0 Edge */
#define IRQ_INTTAUB0I2           136  /* Interrupt for TAUB0 channel 2 TAUB0 Edge */
#define IRQ_INTTAUB0I3           137  /* Interrupt for TAUB0 channel 3 TAUB0 Edge */
#define IRQ_ICPWGA16             137  /*INTPWGA16*7 PWGA16 interrupt PWGA16 Edge */
#define IRQ_INTTAUB0I4           138  /* Interrupt for TAUB0 channel 4 TAUB0 Edge 108AH */
#define IRQ_INTTAUB0I5           139  /* Interrupt for TAUB0 channel 5 TAUB0 Edge 108BH */
#define IRQ_ICPWGA17             139  /*INTPWGA17*7 PWGA17 interrupt PWGA17 Edge */
#define IRQ_INTTAUB0I6           140  /* Interrupt for TAUB0 channel 6 TAUB0 Edge 108CH */
#define IRQ_INTTAUB0I7           141  /* Interrupt for TAUB0 channel 7 TAUB0 Edge 108DH */
#define IRQ_ICPWGA18             141  /* INTPWGA18*7 PWGA18 interrupt PWGA18 Edge */
#define IRQ_INTTAUB0I8           142  /* Interrupt for TAUB0 channel 8 TAUB0 Edge 108EH */
#define IRQ_INTTAUB0I9           143  /* Interrupt for TAUB0 channel 9 TAUB0 Edge 108FH */
#define IRQ_INTPWGA19            143  /* PWGA19 interrupt PWGA19 Edge */
#define IRQ_INTTAUB0I10          144  /* Interrupt for TAUB0 channel 10 TAUB0 Edge */
#define IRQ_INTTAUB0I11          145  /* Interrupt for TAUB0 channel 11 TAUB0 Edge */
#define IRQ_INTPWGA26            145  /* PWGA26 interrupt PWGA26 Edge */
#define IRQ_INTTAUB0I12          146  /* Interrupt for TAUB0 channel 12 TAUB0 Edge */
#define IRQ_INTTAUB0I13          147  /* Interrupt for TAUB0 channel 13 TAUB0 Edge */
#define IRQ_INTPWGA30            147  /* PWGA30 interrupt PWGA30 Edge */
#define IRQ_INTTAUB0I14          148  /* Interrupt for TAUB0 channel 14 TAUB0 Edge */
#define IRQ_INTTAUB0I15          149  /* Interrupt for TAUB0 channel 15 TAUB0 Edge */
#define IRQ_INTPWGA31            149  /* PWGA31 interrupt PWGA31 Edge */
#define IRQ_INTCSIH3IC           150  /* CSIH3 communication status interrupt CSIH3 Edge */
#define IRQ_INTTAUD0I2_2         150  /* Interrupt for TAUD0 channel 2 TAUD0 Edge */
#define IRQ_INTCSIH3IR           151  /* CSIH3 receive status interrupt CSIH3 Edge */
#define IRQ_INTTAUD0I10_2        151  /* Interrupt for TAUD0 channel 10 TAUD0 Edge */
#define IRQ_INTCSIH3IRE          152  /* CSIH3 communication error interrupt CSIH3 Edge */
#define IRQ_INTTAUD0I12_2        152  /* Interrupt for TAUD0 channel 12 TAUD0 Edge */
#define IRQ_INTCSIH3IJC          153  /* CSIH3 job completion interrupt CSIH3 Edge */
#define IRQ_INTTAUD0I14_2        153  /* Interrupt for TAUD0 channel 14 TAUD0 Edge */
#define IRQ_INTRLIN22            154  /* RLIN22 interrupt RLIN240 Edge 109AH — */
#define IRQ_INTRLIN23            155  /* RLIN23 interrupt RLIN240 Edge 109BH — — */
#define IRQ_INTRLIN32            156  /* RLIN32 interrupt RLIN32 Edge 109CH */
#define IRQ_INTRLIN32UR0         157  /* RLIN32 transmit interrupt RLIN32 Edge 109DH */
#define IRQ_INTRLIN32UR1         158  /* RLIN32 reception complete interrupt RLIN32 Edge 109EH */
#define IRQ_INTRLIN32UR2         159  /* RLIN32 status interrupt RLIN32 Edge 109FH */
#define IRQ_INTTAUJ1I0           160  /* Interrupt for TAUJ1 channel 0 TAUJ1 Edge 10A0H — */
#define IRQ_INTTAUJ1I1           161  /* Interrupt for TAUJ1 channel 1 TAUJ1 Edge 10A1H — */
#define IRQ_INTTAUJ1I2           162  /* Interrupt for TAUJ1 channel 2 TAUJ1 Edge 10A2H — */
#define IRQ_INTTAUJ1I3           163  /* Interrupt for TAUJ1 channel 3 TAUJ1 Edge 10A3H — */
#define IRQ_INTPWGA24            176  /* PWGA24 interrupt PWGA24 Edge 10B0H — */
#define IRQ_INTPWGA25            177  /* PWGA25 interrupt PWGA25 Edge 10B1H — */
#define IRQ_INTPWGA27            178  /* PWGA27 interrupt PWGA27 Edge 10B2H — */
#define IRQ_INTPWGA28            79 /* PWGA28 interrupt PWGA28 Edge 10B3H */
#define IRQ_INTPWGA29            180 /* PWGA29 interrupt PWGA29 Edge 10B4H */
#define IRQ_INTPWGA32            181 /* PWGA32 interrupt PWGA32 Edge 10B5H */
#define IRQ_INTPWGA33            182 /* PWGA33 interrupt PWGA33 Edge 10B6H */
#define IRQ_INTPWGA34            183 /* PWGA34 interrupt PWGA34 Edge 10B7H */
#define IRQ_INTPWGA35            184 /* PWGA35 interrupt PWGA35 Edge 10B8H */
#define IRQ_INTPWGA36            185 /* PWGA36 interrupt PWGA36 Edge 10B9H */
#define IRQ_INTPWGA37            186 /* PWGA37 interrupt PWGA37 Edge 10BAH */
#define IRQ_INTPWGA38            187 /* PWGA38 interrupt PWGA38 Edge 10BBH */
#define IRQ_INTPWGA39            188 /* PWGA39 interrupt PWGA39 Edge 10BCH */
#define IRQ_INTPWGA40            189 /* PWGA40 interrupt PWGA40 Edge 10BDH */
#define IRQ_INTPWGA41            190 /* PWGA41 interrupt PWGA41 Edge 10BEH */
#define IRQ_INTPWGA42            191 /* PWGA42 interrupt PWGA42 Edge 10BFH */
#define IRQ_INTPWGA43            192 /* PWGA43 interrupt PWGA43 Edge 10C0H */
#define IRQ_INTPWGA44            193 /* PWGA44 interrupt PWGA44 Edge 10C1H */
#define IRQ_INTPWGA45            194 /* PWGA45 interrupt PWGA45 Edge 10C2H */
#define IRQ_INTPWGA46            195 /* PWGA46 interrupt PWGA46 Edge 10C3H */
#define IRQ_INTPWGA47            196 /* PWGA47 interrupt PWGA47 Edge 10C4H */
#define IRQ_INTP9                197 /* External interrupt Port Edge/Level 10C5H */
#define IRQ_INTP13               198 /* External interrupt Port Edge/Level 10C6H */
#define IRQ_INTP14               199 /* External interrupt Port Edge/Level 10C7H */
#define IRQ_INTP15               200 /* External interrupt Port Edge/Level 10C8H */
#define IRQ_INTRTCA01S           201 /* RTCA0 1 second interval interrupt */
#define IRQ_INTRTCA0AL           202 /* RTCA0 alarm interrupt RTCA Edge */
#define IRQ_INTRTCA0R            203 /* RTCA0 periodic interrupt RTCA Edge */
#define IRQ_INTADCA1ERR          204 /* ADCA1 error interrupt ADCA1 Edge */
#define IRQ_INTADCA1I0           205 /* ADCA1 scan group 1 (SG1) */
#define IRQ_INTADCA1I1           206 /* ADCA1 scan group 2 (SG2) */
#define IRQ_INTADCA1I2           207 /* ADCA1 scan group 3 (SG3) */
#define IRQ_AA                   208 /* */
#define IRQ_INTRCAN2ERR          209 /* CAN2 error interrupt RSCAN0 Level */
#define IRQ_INTRCAN2REC          210 /* CAN2 transmit/receive FIFO receive complete */
#define IRQ_INTRCAN2TRX          211 /* CAN2 transmit interrupt RSCAN0 Level */
#define IRQ_INTRCAN3ERR          212 /* CAN3 error interrupt RSCAN0 Level */
#define IRQ_INTRCAN3REC          213 /* CAN3 transmit/receive FIFO receive complete */
#define IRQ_INTRCAN3TRX          214 /* CAN3 transmit interrupt RSCAN0 Level */
#define IRQ_INTCSIG1IC           215 /* CSIG1 communication status interrupt CSIG1 */
#define IRQ_INTCSIG1IR           216 /* CSIG1 receive status interrupt CSIG1 */
#define IRQ_INTCSIG1IRE          217 /* CSIG1 communication error interrupt CSIG1 */
#define IRQ_INTRLIN24            218 /* RLIN24 interrupt RLIN241 Edge 10DAH */
#define IRQ_INTRLIN25            219 /* RLIN25 interrupt RLIN241 Edge 10DBH */
#define IRQ_INTRLIN33            220 /* RLIN33 interrupt RLIN33 Edge 10DCH */
#define IRQ_INTRLIN33UR0         221 /* RLIN33 transmit interrupt RLIN33 Edge */
#define IRQ_INTRLIN33UR1         222 /* RLIN33 reception complete interrupt RLIN33 */
#define IRQ_INTRLIN33UR2         223 /* RLIN33 status interrupt RLIN33 Edge */
#define IRQ_INTRLIN34            224 /* RLIN34 interrupt RLIN34 Edge 10E0H */
#define IRQ_INTRLIN34UR0         225 /* RLIN34 transmit interrupt RLIN34 Edge */
#define IRQ_INTRLIN34UR1         226 /* RLIN34 reception complete interrupt RLIN34 */
#define IRQ_INTRLIN34UR2         227 /* RLIN34 status interrupt RLIN34 Edge */
#define IRQ_INTRLIN35            228 /* RLIN35 interrupt RLIN35 Edge 10E4H */
#define IRQ_INTRLIN35UR0         229 /* RLIN35 transmit interrupt RLIN35 Edge */
#define IRQ_INTRLIN35UR1         230 /* RLIN35 reception complete interrupt RLIN35 */
#define IRQ_INTRLIN35UR2         231 /* RLIN35 status interrupt RLIN35 Edge */
#define IRQ_INTPWGA48            232 /* PWGA48 interrupt PWGA48 Edge 10E8H */
#define IRQ_INTPWGA49            233 /* PWGA49 interrupt PWGA49 Edge 10E9H */
#define IRQ_INTPWGA50            234 /* PWGA50 interrupt PWGA50 Edge 10EAH */
#define IRQ_INTPWGA51            235 /* PWGA51 interrupt PWGA51 Edge 10EBH */
#define IRQ_INTPWGA52            236 /* PWGA52 interrupt PWGA52 Edge 10ECH */
#define IRQ_INTPWGA53            237 /* PWGA53 interrupt PWGA53 Edge 10EDH */
#define IRQ_INTPWGA54            238 /* PWGA54 interrupt PWGA54 Edge 10EEH */
#define IRQ_INTPWGA55            239 /* PWGA55 interrupt PWGA55 Edge 10EFH */
#define IRQ_INTPWGA56            240 /* PWGA56 interrupt PWGA56 Edge 10F0H */
#define IRQ_INTPWGA57            241 /* PWGA57 interrupt PWGA57 Edge 10F1H */
#define IRQ_INTPWGA58            242 /* PWGA58 interrupt PWGA58 Edge 10F2H */
#define IRQ_INTPWGA59            243 /* PWGA59 interrupt PWGA59 Edge 10F3H */
#define IRQ_INTPWGA60            244 /* PWGA60 interrupt PWGA60 Edge 10F4H */
#define IRQ_INTPWGA61            245 /* PWGA61 interrupt PWGA61 Edge 10F5H */
#define IRQ_INTPWGA62            246 /* PWGA62 interrupt PWGA62 Edge 10F6H */
#define IRQ_INTPWGA63            247 /* PWGA63 interrupt PWGA63 Edge 10F7H */
#define IRQ_INTTAUB1I0           248 /* Interrupt for TAUB1 channel 0 */
#define IRQ_INTTAUB1I1           249 /* Interrupt for TAUB1 channel 1 */
#define IRQ_INTTAUB1I2           250 /* Interrupt for TAUB1 channel 2 */
#define IRQ_INTTAUB1I3           251 /* Interrupt for TAUB1 channel 3 */
#define IRQ_INTTAUB1I4           252 /* Interrupt for TAUB1 channel 4 */
#define IRQ_INTTAUB1I5           253 /* Interrupt for TAUB1 channel 5 */
#define IRQ_INTTAUB1I6           254 /* Interrupt for TAUB1 channel 6 */
#define IRQ_INTTAUB1I7           255 /* Interrupt for TAUB1 channel 7 */
#define IRQ_INTTAUB1I8           256 /* Interrupt for TAUB1 channel 8 */
#define IRQ_INTTAUB1I9           257 /* Interrupt for TAUB1 channel 9 */
#define IRQ_INTTAUB1I10          258 /* Interrupt for TAUB1 channel 10 */
#define IRQ_INTTAUB1I11          259 /* Interrupt for TAUB1 channel 11 */
#define IRQ_INTTAUB1I12          260 /* Interrupt for TAUB1 channel 12 */
#define IRQ_INTTAUB1I13          261 /* Interrupt for TAUB1 channel 13 */
#define IRQ_INTTAUB1I14          262 /* Interrupt for TAUB1 channel 14 */
#define IRQ_INTTAUB1I15          263 /* Interrupt for TAUB1 channel 15 */
#define IRQ_INTRCAN4ERR          264 /* CAN4 error interrupt RSCAN0 Level */
#define IRQ_INTRCAN4REC          265 /* CAN4 transmit/receive FIFO receive complete */
#define IRQ_INTRCAN4TRX          266 /* CAN4 transmit interrupt RSCAN0 Level */
#define IRQ_INTRLIN26            267 /* RLIN26 interrupt RLIN241 Edge 110BH */
#define IRQ_INTRLIN27            268 /* RLIN27 interrupt RLIN241 Edge 110CH */
#define IRQ_INTPWGA64            269 /* PWGA64 interrupt PWGA64 Edge 110DH */
#define IRQ_INTPWGA65            270 /* PWGA65 interrupt PWGA65 Edge 110EH */
#define IRQ_INTPWGA66            271 /* PWGA66 interrupt PWGA66 Edge 110FH */
#define IRQ_INTPWGA67            272 /* PWGA67 interrupt PWGA67 Edge 1110H */
#define IRQ_INTPWGA68            273 /* PWGA68 interrupt PWGA68 Edge 1111H */
#define IRQ_INTPWGA69            274 /* PWGA69 interrupt PWGA69 Edge 1112H */
#define IRQ_INTPWGA70            275 /* PWGA70 interrupt PWGA70 Edge 1113H */
#define IRQ_INTPWGA71            276 /* PWGA71 interrupt PWGA71 Edge 1114H */
#define IRQ_INTRLIN28            277 /* RLIN28 interrupt RLIN210 Edge 1115H */
#define IRQ_INTRLIN29            278 /* RLIN29 interrupt RLIN211 Edge 1116H */
#define IRQ_INTRCAN5ERR          279 /* CAN5 error interrupt RSCAN0 Level */
#define IRQ_INTRCAN5REC          280 /* CAN5 transmit/receive FIFO receive complete */
#define IRQ_INTRCAN5TRX          281 /* CAN5 transmit interrupt RSCAN0 Level */


#define IRQ_CNT					351
#define IRQ_SPI_CNT				64

#define NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS		IRQ_CNT
#define IRQ_INTERRUPT_OFFSET					0

typedef enum
{
    /* Directly from the PLLs */
    C_CPLLCLK,
    C_CPLLCLK2,
    C_PPLLCLK,
    C_PPLLCLK2,
    C_PPLLCLK4,
    C_CPUCLK,
    C_CPUCLK2,
    C_CPUCLK4,

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
