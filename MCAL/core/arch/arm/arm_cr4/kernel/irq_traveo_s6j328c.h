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

#ifndef IRQ_TRAVEO_S6J328C_H_
#define IRQ_TRAVEO_S6J328C_H_

void Irq_SOI( void );
#define Irq_SOI3(_x)

/* Interrupts */
#define SYSTEM_CONTROL_STATUS          1

#define IRQ_1     1       /*  System Control Status  IRC0_IRQPL0 : IRQPL1  IRC0_IRQVA1  */
#define IRQ_2     2       /*  HW-WDT Pre-warning  IRC0_IRQPL0 : IRQPL2  IRC0_IRQVA2  */
#define IRQ_3     3       /*  SW-WDT Pre-warning  IRC0_IRQPL0 : IRQPL3  IRC0_IRQVA3  */
#define IRQ_8     8       /*  TCFLASH RDY, Hang up, Single Bit Error  IRC0_IRQPL2 : IRQPL8  IRC0_IRQVA8  */
#define IRQ_10     10       /*  Work FLASH Hang up  IRC0_IRQPL2 : IRQPL10  IRC0_IRQVA10  */
#define IRQ_14     14       /*  System RAM Single Bit Error  IRC0_IRQPL3 : IRQPL14  IRC0_IRQVA14  */
#define IRQ_15     15       /*  Backup RAM / CAN FD RAM(ch.0,1,5,6) Single Bit Error  IRC0_IRQPL3 : IRQPL15  IRC0_IRQVA15  */
#define IRQ_16     16       /*  IRC Vector Address RAM Single Bit Error  IRC0_IRQPL4 : IRQPL16  IRC0_IRQVA16  */
#define IRQ_20     20       /*  Work FLASH RDY, Write Enable Release, Single Bit Error  IRC0_IRQPL5 : IRQPL20  IRC0_IRQVA20  */
#define IRQ_23     23       /*  EICU  IRC0_IRQPL5 : IRQPL23  IRC0_IRQVA23  */
#define IRQ_24     24       /*  External Interrupt Request ch.0  IRC0_IRQPL6 : IRQPL24  IRC0_IRQVA24  */
#define IRQ_25     25       /*  External Interrupt Request ch.1  IRC0_IRQPL6 : IRQPL25  IRC0_IRQVA25  */
#define IRQ_26     26       /*  External Interrupt Request ch.2  IRC0_IRQPL6 : IRQPL26  IRC0_IRQVA26  */
#define IRQ_27     27       /*  External Interrupt Request ch.3  IRC0_IRQPL6 : IRQPL27  IRC0_IRQVA27  */
#define IRQ_28     28       /*  External Interrupt Request ch.4  IRC0_IRQPL7 : IRQPL28  IRC0_IRQVA28  */
#define IRQ_29     29       /*  External Interrupt Request ch.5  IRC0_IRQPL7 : IRQPL29  IRC0_IRQVA29  */
#define IRQ_30     30       /*  External Interrupt Request ch.6  IRC0_IRQPL7 : IRQPL30  IRC0_IRQVA30  */
#define IRQ_31     31       /*  External Interrupt Request ch.7  IRC0_IRQPL7 : IRQPL31  IRC0_IRQVA31  */
#define IRQ_32     32       /*  External Interrupt Request ch.8  IRC0_IRQPL8 : IRQPL32  IRC0_IRQVA32  */
#define IRQ_33     33       /*  External Interrupt Request ch.9  IRC0_IRQPL8 : IRQPL33  IRC0_IRQVA33  */
#define IRQ_34     34       /*  External Interrupt Request ch.10  IRC0_IRQPL8 : IRQPL34  IRC0_IRQVA34  */
#define IRQ_35     35       /*  External Interrupt Request ch.11  IRC0_IRQPL8 : IRQPL35  IRC0_IRQVA35  */
#define IRQ_36     36       /*  External Interrupt Request ch.12  IRC0_IRQPL9 : IRQPL36  IRC0_IRQVA36  */
#define IRQ_37     37       /*  External Interrupt Request ch.13  IRC0_IRQPL9 : IRQPL37  IRC0_IRQVA37  */
#define IRQ_38     38       /*  External Interrupt Request ch.14  IRC0_IRQPL9 : IRQPL38  IRC0_IRQVA38  */
#define IRQ_39     39       /*  External Interrupt Request ch.15  IRC0_IRQPL9 : IRQPL39  IRC0_IRQVA39  */
#define IRQ_40     40       /*  MFS RX ch.16  IRC0_IRQPL10 : IRQPL40  IRC0_IRQVA40  */
#define IRQ_41     41       /*  MFS TX ch.16  IRC0_IRQPL10 : IRQPL41  IRC0_IRQVA41  */
#define IRQ_42     42       /*  MFS RX ch.17  IRC0_IRQPL10 : IRQPL42  IRC0_IRQVA42  */
#define IRQ_43     43       /*  MFS TX ch.17  IRC0_IRQPL10 : IRQPL43  IRC0_IRQVA43  */
#define IRQ_46     46       /*  Reload Timer ch.48,49 OR-ed  IRC0_IRQPL11 : IRQPL46  IRC0_IRQVA46  */
#define IRQ_48     48       /*  CAN FD ch.5  IRC0_IRQPL12 : IRQPL48  IRC0_IRQVA48  */
#define IRQ_49     49       /*  CAN FD ch.6  IRC0_IRQPL12 : IRQPL49  IRC0_IRQVA49  */
#define IRQ_56     56       /*  CAN FD ch.0  IRC0_IRQPL14 : IRQPL56  IRC0_IRQVA56  */
#define IRQ_57     57       /*  CAN FD ch.1  IRC0_IRQPL14 : IRQPL57  IRC0_IRQVA57  */
#define IRQ_64     64       /*  MFS RX ch.0  IRC0_IRQPL16 : IRQPL64  IRC0_IRQVA64  */
#define IRQ_65     65       /*  MFS TX ch.0  IRC0_IRQPL16 : IRQPL65  IRC0_IRQVA65  */
#define IRQ_66     66       /*  MFS RX ch.1  IRC0_IRQPL16 : IRQPL66  IRC0_IRQVA66  */
#define IRQ_67     67       /*  MFS TX ch.1  IRC0_IRQPL16 : IRQPL67  IRC0_IRQVA67  */
#define IRQ_68     68       /*  MFS RX ch.2  IRC0_IRQPL17 : IRQPL68  IRC0_IRQVA68  */
#define IRQ_69     69       /*  MFS TX ch.2  IRC0_IRQPL17 : IRQPL69  IRC0_IRQVA69  */
#define IRQ_70     70       /*  MFS RX ch.3  IRC0_IRQPL17 : IRQPL70  IRC0_IRQVA70  */
#define IRQ_71     71       /*  MFS TX ch.3  IRC0_IRQPL17 : IRQPL71  IRC0_IRQVA71  */
#define IRQ_72     72       /*  MFS RX ch.4  IRC0_IRQPL18 : IRQPL72  IRC0_IRQVA72  */
#define IRQ_73     73       /*  MFS TX ch.4  IRC0_IRQPL18 : IRQPL73  IRC0_IRQVA73  */
#define IRQ_80     80       /*  MFS RX ch.8  IRC0_IRQPL20 : IRQPL80  IRC0_IRQVA80  */
#define IRQ_81     81       /*  MFS TX ch.8  IRC0_IRQPL20 : IRQPL81  IRC0_IRQVA81  */
#define IRQ_82     82       /*  MFS RX ch.9  IRC0_IRQPL20 : IRQPL82  IRC0_IRQVA82  */
#define IRQ_83     83       /*  MFS TX ch.9  IRC0_IRQPL20 : IRQPL83  IRC0_IRQVA83  */
#define IRQ_84     84       /*  MFS RX ch.10  IRC0_IRQPL21 : IRQPL84  IRC0_IRQVA84  */
#define IRQ_85     85       /*  MFS TX ch.10  IRC0_IRQPL21 : IRQPL85  IRC0_IRQVA85  */
#define IRQ_86     86       /*  MFS RX ch.11  IRC0_IRQPL21 : IRQPL86  IRC0_IRQVA86  */
#define IRQ_87     87       /*  MFS TX ch.11  IRC0_IRQPL21 : IRQPL87  IRC0_IRQVA87  */
#define IRQ_88     88       /*  MFS RX ch.12  IRC0_IRQPL22 : IRQPL88  IRC0_IRQVA88  */
#define IRQ_89     89       /*  MFS TX ch.12  IRC0_IRQPL22 : IRQPL89  IRC0_IRQVA89  */
#define IRQ_100     100       /*  SHE Error  IRC0_IRQPL25 : IRQPL100  IRC0_IRQVA100  */
#define IRQ_101     101       /*  SHE  IRC0_IRQPL25 : IRQPL101  IRC0_IRQVA101  */
#define IRQ_102     102       /*  DDR HSSPI RX  IRC0_IRQPL25 : IRQPL102  IRC0_IRQVA102  */
#define IRQ_103     103       /*  DDR HSSPI TX  IRC0_IRQPL25 : IRQPL103  IRC0_IRQVA103  */
#define IRQ_110     110       /*  TCRAM  IRC0_IRQPL27 : IRQPL110  IRC0_IRQVA110  */
#define IRQ_112     112       /*  BACKUP RAM  IRC0_IRQPL28 : IRQPL112  IRC0_IRQVA112  */
#define IRQ_116     116       /*  RTC  IRC0_IRQPL29 : IRQPL116  IRC0_IRQVA116  */
#define IRQ_117     117       /*  CR CARIBRATION  IRC0_IRQPL29 : IRQPL117  IRC0_IRQVA117  */
#define IRQ_128     128       /*  Base Timer ch.0/8/9/10/11  IRC0_IRQPL32 : IRQPL128  IRC0_IRQVA128  */
#define IRQ_129     129       /*  Base Timer ch.1  IRC0_IRQPL32 : IRQPL129  IRC0_IRQVA129  */
#define IRQ_130     130       /*  Base Timer ch.2  IRC0_IRQPL32 : IRQPL130  IRC0_IRQVA130  */
#define IRQ_131     131       /*  Base Timer ch.3  IRC0_IRQPL32 : IRQPL131  IRC0_IRQVA131  */
#define IRQ_132     132       /*  Base Timer ch.4  IRC0_IRQPL33 : IRQPL132  IRC0_IRQVA132  */
#define IRQ_133     133       /*  Base Timer ch.5  IRC0_IRQPL33 : IRQPL133  IRC0_IRQVA133  */
#define IRQ_134     134       /*  Base Timer ch.6  IRC0_IRQPL33 : IRQPL134  IRC0_IRQVA134  */
#define IRQ_135     135       /*  Base Timer ch.7  IRC0_IRQPL33 : IRQPL135  IRC0_IRQVA135  */
#define IRQ_136     136       /*  Base Timer ch.12/20/21/22/23  IRC0_IRQPL34 : IRQPL136  IRC0_IRQVA136  */
#define IRQ_137     137       /*  Base Timer ch.13  IRC0_IRQPL34 : IRQPL137  IRC0_IRQVA137  */
#define IRQ_138     138       /*  Base Timer ch.14  IRC0_IRQPL34 : IRQPL138  IRC0_IRQVA138  */
#define IRQ_139     139       /*  Base Timer ch.15  IRC0_IRQPL34 : IRQPL139  IRC0_IRQVA139  */
#define IRQ_140     140       /*  Base Timer ch.16  IRC0_IRQPL35 : IRQPL140  IRC0_IRQVA140  */
#define IRQ_141     141       /*  Base Timer ch.17  IRC0_IRQPL35 : IRQPL141  IRC0_IRQVA141  */
#define IRQ_142     142       /*  Base Timer ch.18  IRC0_IRQPL35 : IRQPL142  IRC0_IRQVA142  */
#define IRQ_143     143       /*  Base Timer ch.19  IRC0_IRQPL35 : IRQPL143  IRC0_IRQVA143  */
#define IRQ_152     152       /*  Reload Timer ch.0  IRC0_IRQPL38 : IRQPL152  IRC0_IRQVA152  */
#define IRQ_153     153       /*  Reload Timer ch.1  IRC0_IRQPL38 : IRQPL153  IRC0_IRQVA153  */
#define IRQ_154     154       /*  Reload Timer ch.2  IRC0_IRQPL38 : IRQPL154  IRC0_IRQVA154  */
#define IRQ_155     155       /*  Reload Timer ch.3  IRC0_IRQPL38 : IRQPL155  IRC0_IRQVA155  */
#define IRQ_160     160       /*  Reload Timer ch.16  IRC0_IRQPL40 : IRQPL160  IRC0_IRQVA160  */
#define IRQ_161     161       /*  Reload Timer ch.17  IRC0_IRQPL40 : IRQPL161  IRC0_IRQVA161  */
#define IRQ_162     162       /*  Reload Timer ch.18  IRC0_IRQPL40 : IRQPL162  IRC0_IRQVA162  */
#define IRQ_163     163       /*  Reload Timer ch.19  IRC0_IRQPL40 : IRQPL163  IRC0_IRQVA163  */
#define IRQ_168     168       /*  Reload Timer ch.32  IRC0_IRQPL42 : IRQPL168  IRC0_IRQVA168  */
#define IRQ_169     169       /*  Reload Timer ch.33  IRC0_IRQPL42 : IRQPL169  IRC0_IRQVA169  */
#define IRQ_170     170       /*  Reload Timer ch.34  IRC0_IRQPL42 : IRQPL170  IRC0_IRQVA170  */
#define IRQ_171     171       /*  Reload Timer ch.35  IRC0_IRQPL42 : IRQPL171  IRC0_IRQVA171  */
#define IRQ_176     176       /*  FRT ch.0  IRC0_IRQPL44 : IRQPL176  IRC0_IRQVA176  */
#define IRQ_177     177       /*  FRT ch.1  IRC0_IRQPL44 : IRQPL177  IRC0_IRQVA177  */
#define IRQ_178     178       /*  FRT ch.2  IRC0_IRQPL44 : IRQPL178  IRC0_IRQVA178  */
#define IRQ_179     179       /*  FRT ch.3  IRC0_IRQPL44 : IRQPL179  IRC0_IRQVA179  */
#define IRQ_180     180       /*  FRT ch.4  IRC0_IRQPL45 : IRQPL180  IRC0_IRQVA180  */
#define IRQ_181     181       /*  FRT ch.5  IRC0_IRQPL45 : IRQPL181  IRC0_IRQVA181  */
#define IRQ_182     182       /*  FRT ch.6  IRC0_IRQPL45 : IRQPL182  IRC0_IRQVA182  */
#define IRQ_183     183       /*  FRT ch.7  IRC0_IRQPL45 : IRQPL183  IRC0_IRQVA183  */
#define IRQ_184     184       /*  FRT ch.8  IRC0_IRQPL46 : IRQPL184  IRC0_IRQVA184  */
#define IRQ_185     185       /*  FRT ch.9  IRC0_IRQPL46 : IRQPL185  IRC0_IRQVA185  */
#define IRQ_186     186       /*  FRT ch.10  IRC0_IRQPL46 : IRQPL186  IRC0_IRQVA186  */
#define IRQ_187     187       /*  FRT ch.11  IRC0_IRQPL46 : IRQPL187  IRC0_IRQVA187  */
#define IRQ_192     192       /*  IRQ0 of Input Capture 0  IRC0_IRQPL48 : IRQPL192  IRC0_IRQVA192  */
#define IRQ_193     193       /*  IRQ0 of Input Capture 1  IRC0_IRQPL48 : IRQPL193  IRC0_IRQVA193  */
#define IRQ_194     194       /*  IRQ0 of Input Capture 2  IRC0_IRQPL48 : IRQPL194  IRC0_IRQVA194  */
#define IRQ_195     195       /*  IRQ0 of Input Capture 3  IRC0_IRQPL48 : IRQPL195  IRC0_IRQVA195  */
#define IRQ_196     196       /*  IRQ0 of Input Capture 4  IRC0_IRQPL49 : IRQPL196  IRC0_IRQVA196  */
#define IRQ_197     197       /*  IRQ0 of Input Capture 5  IRC0_IRQPL49 : IRQPL197  IRC0_IRQVA197  */
#define IRQ_198     198       /*  IRQ0 of Input Capture 6  IRC0_IRQPL49 : IRQPL198  IRC0_IRQVA198  */
#define IRQ_199     199       /*  IRQ0 of Input Capture 7  IRC0_IRQPL49 : IRQPL199  IRC0_IRQVA199  */
#define IRQ_200     200       /*  IRQ0 of Input Capture 8  IRC0_IRQPL50 : IRQPL200  IRC0_IRQVA200  */
#define IRQ_201     201       /*  IRQ0 of Input Capture 9  IRC0_IRQPL50 : IRQPL201  IRC0_IRQVA201  */
#define IRQ_202     202       /*  IRQ0 of Input Capture 10  IRC0_IRQPL50 : IRQPL202  IRC0_IRQVA202  */
#define IRQ_203     203       /*  IRQ0 of Input Capture 11  IRC0_IRQPL50 : IRQPL203  IRC0_IRQVA203  */
#define IRQ_208     208       /*  IRQ0 of Output Compare 0  IRC0_IRQPL52 : IRQPL208  IRC0_IRQVA208  */
#define IRQ_209     209       /*  IRQ0 of Output Compare 1  IRC0_IRQPL52 : IRQPL209  IRC0_IRQVA209  */
#define IRQ_210     210       /*  IRQ0 of Output Compare 2  IRC0_IRQPL52 : IRQPL210  IRC0_IRQVA210  */
#define IRQ_211     211       /*  IRQ0 of Output Compare 3  IRC0_IRQPL52 : IRQPL211  IRC0_IRQVA211  */
#define IRQ_212     212       /*  IRQ0 of Output Compare 4  IRC0_IRQPL53 : IRQPL212  IRC0_IRQVA212  */
#define IRQ_213     213       /*  IRQ0 of Output Compare 5  IRC0_IRQPL53 : IRQPL213  IRC0_IRQVA213  */
#define IRQ_214     214       /*  IRQ0 of Output Compare 6  IRC0_IRQPL53 : IRQPL214  IRC0_IRQVA214  */
#define IRQ_215     215       /*  IRQ0 of Output Compare 7  IRC0_IRQPL53 : IRQPL215  IRC0_IRQVA215  */
#define IRQ_216     216       /*  IRQ0 of Output Compare 8  IRC0_IRQPL54 : IRQPL216  IRC0_IRQVA216  */
#define IRQ_217     217       /*  IRQ0 of Output Compare 9  IRC0_IRQPL54 : IRQPL217  IRC0_IRQVA217  */
#define IRQ_218     218       /*  IRQ0 of Output Compare 10  IRC0_IRQPL54 : IRQPL218  IRC0_IRQVA218  */
#define IRQ_219     219       /*  IRQ0 of Output Compare 11  IRC0_IRQPL54 : IRQPL219  IRC0_IRQVA219  */
#define IRQ_232     232       /*  QPRC ch.8  IRC0_IRQPL58 : IRQPL232  IRC0_IRQVA232  */
#define IRQ_233     233       /*  QPRC ch.9  IRC0_IRQPL58 : IRQPL233  IRC0_IRQVA233  */
#define IRQ_240     240       /*  IRQ1 of Input Capture 0  IRC0_IRQPL60 : IRQPL240  IRC0_IRQVA240  */
#define IRQ_241     241       /*  IRQ1 of Input Capture 1  IRC0_IRQPL60 : IRQPL241  IRC0_IRQVA241  */
#define IRQ_242     242       /*  IRQ1 of Input Capture 2  IRC0_IRQPL60 : IRQPL242  IRC0_IRQVA242  */
#define IRQ_243     243       /*  IRQ1 of Input Capture 3  IRC0_IRQPL60 : IRQPL243  IRC0_IRQVA243  */
#define IRQ_244     244       /*  IRQ1 of Input Capture 4  IRC0_IRQPL61 : IRQPL244  IRC0_IRQVA244  */
#define IRQ_245     245       /*  IRQ1 of Input Capture 5  IRC0_IRQPL61 : IRQPL245  IRC0_IRQVA245  */
#define IRQ_246     246       /*  IRQ1 of Input Capture 6  IRC0_IRQPL61 : IRQPL246  IRC0_IRQVA246  */
#define IRQ_247     247       /*  IRQ1 of Input Capture 7  IRC0_IRQPL61 : IRQPL247  IRC0_IRQVA247  */
#define IRQ_248     248       /*  IRQ1 of Input Capture 8  IRC0_IRQPL62 : IRQPL248  IRC0_IRQVA248  */
#define IRQ_249     249       /*  IRQ1 of Input Capture 9  IRC0_IRQPL62 : IRQPL249  IRC0_IRQVA249  */
#define IRQ_250     250       /*  IRQ1 of Input Capture 10  IRC0_IRQPL62 : IRQPL250  IRC0_IRQVA250  */
#define IRQ_251     251       /*  IRQ1 of Input Capture 11  IRC0_IRQPL62 : IRQPL251  IRC0_IRQVA251  */
#define IRQ_256     256       /*  IRQ1 of Output Compare 0  IRC0_IRQPL64 : IRQPL256  IRC0_IRQVA256  */
#define IRQ_257     257       /*  IRQ1 of Output Compare 1  IRC0_IRQPL64 : IRQPL257  IRC0_IRQVA257  */
#define IRQ_258     258       /*  IRQ1 of Output Compare 2  IRC0_IRQPL64 : IRQPL258  IRC0_IRQVA258  */
#define IRQ_259     259       /*  IRQ1 of Output Compare 3  IRC0_IRQPL64 : IRQPL259  IRC0_IRQVA259  */
#define IRQ_260     260       /*  IRQ1 of Output Compare 4  IRC0_IRQPL65 : IRQPL260  IRC0_IRQVA260  */
#define IRQ_261     261       /*  IRQ1 of Output Compare 5  IRC0_IRQPL65 : IRQPL261  IRC0_IRQVA261  */
#define IRQ_262     262       /*  IRQ1 of Output Compare 6  IRC0_IRQPL65 : IRQPL262  IRC0_IRQVA262  */
#define IRQ_263     263       /*  IRQ1 of Output Compare 7  IRC0_IRQPL65 : IRQPL263  IRC0_IRQVA263  */
#define IRQ_264     264       /*  IRQ1 of Output Compare 8  IRC0_IRQPL66 : IRQPL264  IRC0_IRQVA264  */
#define IRQ_265     265       /*  IRQ1 of Output Compare 9  IRC0_IRQPL66 : IRQPL265  IRC0_IRQVA265  */
#define IRQ_266     266       /*  IRQ1 of Output Compare 10  IRC0_IRQPL66 : IRQPL266  IRC0_IRQVA266  */
#define IRQ_267     267       /*  IRQ1 of Output Compare 11  IRC0_IRQPL66 : IRQPL267  IRC0_IRQVA267  */
#define IRQ_272     272       /*  DMA Error  IRC0_IRQPL68 : IRQPL272  IRC0_IRQVA272  */
#define IRQ_273     273       /*  DMAC Completion ch.0  IRC0_IRQPL68 : IRQPL273  IRC0_IRQVA273  */
#define IRQ_274     274       /*  DMAC Completion ch.1  IRC0_IRQPL68 : IRQPL274  IRC0_IRQVA274  */
#define IRQ_275     275       /*  DMAC Completion ch.2  IRC0_IRQPL68 : IRQPL275  IRC0_IRQVA275  */
#define IRQ_276     276       /*  DMAC Completion ch.3  IRC0_IRQPL69 : IRQPL276  IRC0_IRQVA276  */
#define IRQ_277     277       /*  DMAC Completion ch.4  IRC0_IRQPL69 : IRQPL277  IRC0_IRQVA277  */
#define IRQ_278     278       /*  DMAC Completion ch.5  IRC0_IRQPL69 : IRQPL278  IRC0_IRQVA278  */
#define IRQ_279     279       /*  DMAC Completion ch.6  IRC0_IRQPL69 : IRQPL279  IRC0_IRQVA279  */
#define IRQ_280     280       /*  DMAC Completion ch.7  IRC0_IRQPL70 : IRQPL280  IRC0_IRQVA280  */
#define IRQ_282     282       /*  DMAC RLT(ch.0,1,2,3 OR-ed)  IRC0_IRQPL70 : IRQPL282  IRC0_IRQVA282  */
#define IRQ_285     285       /*  DMAC Completion ch.8  IRC0_IRQPL71 : IRQPL285  IRC0_IRQVA285  */
#define IRQ_286     286       /*  DMAC Completion ch.9  IRC0_IRQPL71 : IRQPL286  IRC0_IRQVA286  */
#define IRQ_287     287       /*  DMAC Completion ch.10  IRC0_IRQPL71 : IRQPL287  IRC0_IRQVA287  */
#define IRQ_288     288       /*  DMAC Completion ch.11  IRC0_IRQPL72 : IRQPL288  IRC0_IRQVA288  */
#define IRQ_289     289       /*  DMAC Completion ch.12  IRC0_IRQPL72 : IRQPL289  IRC0_IRQVA289  */
#define IRQ_290     290       /*  DMAC Completion ch.13  IRC0_IRQPL72 : IRQPL290  IRC0_IRQVA290  */
#define IRQ_291     291       /*  DMAC Completion ch.14  IRC0_IRQPL72 : IRQPL291  IRC0_IRQVA291  */
#define IRQ_292     292       /*  DMAC Completion ch.15  IRC0_IRQPL73 : IRQPL292  IRC0_IRQVA292  */
#define IRQ_308     308       /*  SCT CR IRQ  IRC0_IRQPL77 : IRQPL308  IRC0_IRQVA308  */
#define IRQ_309     309       /*  SCT SRC IRQ  IRC0_IRQPL77 : IRQPL309  IRC0_IRQVA309  */
#define IRQ_310     310       /*  SCT Main OSC IRQ  IRC0_IRQPL77 : IRQPL310  IRC0_IRQVA310  */
#define IRQ_311     311       /*  SCT Sub OSC IRQ  IRC0_IRQPL77 : IRQPL311  IRC0_IRQVA311  */
#define IRQ_312     312       /*  CR5 Performance Monitor Unit IRQ  IRC0_IRQPL78 : IRQPL312  IRC0_IRQVA312  */
#define IRQ_320     320       /*  MFS ch.0 Error (Tx/Rx error, Status OR-ed)  IRC0_IRQPL80 : IRQPL320  IRC0_IRQVA320  */
#define IRQ_321     321       /*  MFS ch.1 Error (Tx/Rx error, Status OR-ed)  IRC0_IRQPL80 : IRQPL321  IRC0_IRQVA321  */
#define IRQ_322     322       /*  MFS ch.2 Error (Tx/Rx error, Status OR-ed)  IRC0_IRQPL80 : IRQPL322  IRC0_IRQVA322  */
#define IRQ_323     323       /*  MFS ch.3 Error (Tx/Rx error, Status OR-ed)  IRC0_IRQPL80 : IRQPL323  IRC0_IRQVA323  */
#define IRQ_324     324       /*  MFS ch.4 Error (Tx/Rx error, Status OR-ed)  IRC0_IRQPL81 : IRQPL324  IRC0_IRQVA324  */
#define IRQ_328     328       /*  MFS ch.8 Error (Tx/Rx error, Status OR-ed)  IRC0_IRQPL82 : IRQPL328  IRC0_IRQVA328  */
#define IRQ_329     329       /*  MFS ch.9 Error (Tx/Rx error, Status OR-ed)  IRC0_IRQPL82 : IRQPL329  IRC0_IRQVA329  */
#define IRQ_330     330       /*  MFS ch.10 Error (Tx/Rx error, Status OR-ed)  IRC0_IRQPL82 : IRQPL330  IRC0_IRQVA330  */
#define IRQ_331     331       /*  MFS ch.11 Error (Tx/Rx error, Status OR-ed)  IRC0_IRQPL82 : IRQPL331  IRC0_IRQVA331  */
#define IRQ_332     332       /*  MFS ch.12 Error (Tx/Rx error, Status OR-ed)  IRC0_IRQPL83 : IRQPL332  IRC0_IRQVA332  */
#define IRQ_336     336       /*  MFS ch.16 Error (Tx/Rx error, Status OR-ed)  IRC0_IRQPL84 : IRQPL336  IRC0_IRQVA336  */
#define IRQ_337     337       /*  MFS ch.17 Error (Tx/Rx error, Status OR-ed)  IRC0_IRQPL84 : IRQPL337  IRC0_IRQVA337  */
#define IRQ_339     339       /*  SMC ch.0  IRC0_IRQPL84 : IRQPL339  IRC0_IRQVA339  */
#define IRQ_340     340       /*  SMC ch.1  IRC0_IRQPL85 : IRQPL340  IRC0_IRQVA340  */
#define IRQ_341     341       /*  SMC ch.2  IRC0_IRQPL85 : IRQPL341  IRC0_IRQVA341  */
#define IRQ_342     342       /*  SMC ch.3  IRC0_IRQPL85 : IRQPL342  IRC0_IRQVA342  */
#define IRQ_343     343       /*  SMC ch.4  IRC0_IRQPL85 : IRQPL343  IRC0_IRQVA343  */
#define IRQ_344     344       /*  SMC ch.5  IRC0_IRQPL86 : IRQPL344  IRC0_IRQVA344  */
#define IRQ_347     347       /*  SG ch.0  IRC0_IRQPL86 : IRQPL347  IRC0_IRQVA347  */
#define IRQ_348     348       /*  SG ch.1  IRC0_IRQPL87 : IRQPL348  IRC0_IRQVA348  */
#define IRQ_349     349       /*  SG ch.2  IRC0_IRQPL87 : IRQPL349  IRC0_IRQVA349  */
#define IRQ_350     350       /*  SG ch.3  IRC0_IRQPL87 : IRQPL350  IRC0_IRQVA350  */
#define IRQ_353     353       /*  ADC12B Conversion Done  IRC0_IRQPL88 : IRQPL353  IRC0_IRQVA353  */
#define IRQ_354     354       /*  ADC12B Group interrupt  IRC0_IRQPL88 : IRQPL354  IRC0_IRQVA354  */
#define IRQ_355     355       /*  ADC12B pulse detection function  IRC0_IRQPL88 : IRQPL355  IRC0_IRQVA355  */
#define IRQ_356     356       /*  ADC12B RCO  IRC0_IRQPL89 : IRQPL356  IRC0_IRQVA356  */
#define IRQ_357     357       /*  RPGCRC  IRC0_IRQPL89 : IRQPL357  IRC0_IRQVA357  */
#define IRQ_359     359       /*  MLB channel interrupt  IRC0_IRQPL89 : IRQPL359  IRC0_IRQVA359  */
#define IRQ_360     360       /*  MLB system interrupt  IRC0_IRQPL90 : IRQPL360  IRC0_IRQVA360  */
#define IRQ_361     361       /*  ETHERNET IRQ  IRC0_IRQPL90 : IRQPL361  IRC0_IRQVA361  */
#define IRQ_362     362       /*  ETHERNET Q1 IRQ  IRC0_IRQPL90 : IRQPL362  IRC0_IRQVA362  */
#define IRQ_363     363       /*  ETHERNET Q2 IRQ  IRC0_IRQPL90 : IRQPL363  IRC0_IRQVA363  */
#define IRQ_364     364       /*  ETHERNET Q3 IRQ  IRC0_IRQPL91 : IRQPL364  IRC0_IRQVA364  */
#define IRQ_368     368       /*  Indicator PWM  IRC0_IRQPL92 : IRQPL368  IRC0_IRQVA368  */
#define IRQ_369     369       /*  PCMPWM_DREQ  IRC0_IRQPL92 : IRQPL369  IRC0_IRQVA369  */
#define IRQ_370     370       /*  PCMPWM_OVFL  IRC0_IRQPL92 : IRQPL370  IRC0_IRQVA370  */
#define IRQ_371     371       /*  PCMPWM_UDRN  IRC0_IRQPL92 : IRQPL371  IRC0_IRQVA371  */
#define IRQ_372     372       /*  PCMPWM_DMAE  IRC0_IRQPL93 : IRQPL372  IRC0_IRQVA372  */
#define IRQ_373     373       /*  AUDIO_DAC_DREQ  IRC0_IRQPL93 : IRQPL373  IRC0_IRQVA373  */
#define IRQ_374     374       /*  AUDIO_DAC_OVFL_IRQ  IRC0_IRQPL93 : IRQPL374  IRC0_IRQVA374  */
#define IRQ_375     375       /*  AUDIO_DAC_UDRN_IRQ  IRC0_IRQPL93 : IRQPL375  IRC0_IRQVA375  */
#define IRQ_376     376       /*  AUDIO_DAC_DMAE_IRQ  IRC0_IRQPL94 : IRQPL376  IRC0_IRQVA376  */
#define IRQ_377     377       /*  I2S0_IRQ  IRC0_IRQPL94 : IRQPL377  IRC0_IRQVA377  */
#define IRQ_378     378       /*  I2S1_IRQ  IRC0_IRQPL94 : IRQPL378  IRC0_IRQVA378  */
#define IRQ_401     401       /*  2D Graphics Core Command Sequencer IRC0_IRQPL100 : IRQPL401 IRC0_IRQVA401  */
#define IRQ_402     402       /*  2D Graphics Core Blit Engine IRC0_IRQPL100 : IRQPL402 IRC0_IRQVA402  */
#define IRQ_403     403       /*  2D Graphics Core Drawing Engine IRC0_IRQPL100 : IRQPL403 IRC0_IRQVA403  */
#define IRQ_404     404       /*  2D Graphics Core Content Stream0 IRC0_IRQPL101 : IRQPL404 IRC0_IRQVA404  */
#define IRQ_405     405       /*  2D Graphics Core Safety Stream0 IRC0_IRQPL101 : IRQPL405 IRC0_IRQVA405  */
#define IRQ_406     406       /*  2D Graphics Core Display Stream0 IRC0_IRQPL101 : IRQPL406 IRC0_IRQVA406  */
#define IRQ_407     407       /*  2D Graphics Core Signature0 IRC0_IRQPL101 : IRQPL407 IRC0_IRQVA407  */
#define IRQ_408     408       /*  2D Graphics Core Display0 Sync0 IRC0_IRQPL102 : IRQPL408 IRC0_IRQVA408  */
#define IRQ_409     409       /*  2D Graphics Core Display0 Sync1 IRC0_IRQPL102 : IRQPL409 IRC0_IRQVA409  */
#define IRQ_410     410       /*  2D Graphics Core Content Stream1 IRC0_IRQPL102 : IRQPL410 IRC0_IRQVA410  */
#define IRQ_411     411       /*  2D Graphics Core Safety Stream1 IRC0_IRQPL102 : IRQPL411 IRC0_IRQVA411  */
#define IRQ_412     412       /*  2D Graphics Core Display Stream1 IRC0_IRQPL103 : IRQPL412 IRC0_IRQVA412  */
#define IRQ_413     413       /*  2D Graphics Core Signature1 IRC0_IRQPL103 : IRQPL413 IRC0_IRQVA413  */
#define IRQ_414     414       /*  2D Graphics Core Display1 Sync0 IRC0_IRQPL103 : IRQPL414 IRC0_IRQVA414  */
#define IRQ_415     415       /*  2D Graphics Core Display1 Sync1 IRC0_IRQPL103 : IRQPL415 IRC0_IRQVA415  */
#define IRQ_416     416       /*  2D Graphics Core Capture Plane0 IRC0_IRQPL104 : IRQPL416 IRC0_IRQVA416  */
#define IRQ_417     417       /*  2D Graphics Core Display Plane0 IRC0_IRQPL104 : IRQPL417 IRC0_IRQVA417  */
#define IRQ_418     418       /*  2D Graphics Core Storage Stream0 IRC0_IRQPL104 : IRQPL418 IRC0_IRQVA418  */
#define IRQ_419     419       /*  2D Graphics Core Histogram IRC0_IRQPL104 : IRQPL419 IRC0_IRQVA419  */
#define IRQ_420     420       /*  2D Graphics Core DDRHSSPI IRC0_IRQPL105 : IRQPL420 IRC0_IRQVA420  */
#define IRQ_421     421       /*  3D Graphics Core SRUI IRC0_IRQPL105 : IRQPL421 IRC0_IRQVA421  */
#define IRQ_422     422       /*  3D Graphics Core LINI IRC0_IRQPL105 : IRQPL422 IRC0_IRQVA422  */
#define IRQ_423     423       /*  3D Graphics Core DFI IRC0_IRQPL105 : IRQPL423 IRC0_IRQVA423  */
#define IRQ_424     424       /*  3D Graphics Core DLEI IRC0_IRQPL106 : IRQPL424 IRC0_IRQVA424  */
#define IRQ_425     425       /*  3D Graphics Core DEI IRC0_IRQPL106 : IRQPL425 IRC0_IRQVA425  */
#define IRQ_426     426       /*  3D Graphics Core BEI IRC0_IRQPL106 : IRQPL426 IRC0_IRQVA426  */
#define IRQ_427     427       /*  3D Graphics Core CAEI IRC0_IRQPL106 : IRQPL427 IRC0_IRQVA427  */
#define IRQ_428     428       /*  3D Graphics Core SBEI IRC0_IRQPL107 : IRQPL428 IRC0_IRQVA428  */
#define IRQ_432     432       /*  WG_END_IRQ0 IRC0_IRQPL108 : IRQPL432 IRC0_IRQVA432  */
#define IRQ_433     433       /*  WG_END_IRQ1 IRC0_IRQPL108 : IRQPL433 IRC0_IRQVA433  */
#define IRQ_434     434       /*  WG_END_IRQ2 IRC0_IRQPL108 : IRQPL434 IRC0_IRQVA434  */
#define IRQ_435     435       /*  WG_END_IRQ3 IRC0_IRQPL108 : IRQPL435 IRC0_IRQVA435  */
#define IRQ_436     436       /*  WG_END_IRQ4 IRC0_IRQPL109 : IRQPL436 IRC0_IRQVA436  */
#define IRQ_437     437       /*  WG_AHB_ERR_IRQ IRC0_IRQPL109 : IRQPL437 IRC0_IRQVA437  */
#define IRQ_438     438       /*  MX_DATA_REQ_IRQ0 IRC0_IRQPL109 : IRQPL438 IRC0_IRQVA438  */
#define IRQ_439     439       /*  MX_DATA_REQ_IRQ1 IRC0_IRQPL109 : IRQPL439 IRC0_IRQVA439  */
#define IRQ_440     440       /*  MX_DATA_REQ_IRQ2 IRC0_IRQPL110 : IRQPL440 IRC0_IRQVA440  */
#define IRQ_441     441       /*  MX_DATA_REQ_IRQ3 IRC0_IRQPL110 : IRQPL441 IRC0_IRQVA441  */
#define IRQ_442     442       /*  MX_DATA_REQ_IRQ4 IRC0_IRQPL110 : IRQPL442 IRC0_IRQVA442  */
#define IRQ_443     443       /*  MX_OVFL_IRQ0 IRC0_IRQPL110 : IRQPL443 IRC0_IRQVA443  */
#define IRQ_444     444       /*  MX_OVFL_IRQ1 IRC0_IRQPL111 : IRQPL444 IRC0_IRQVA444  */
#define IRQ_445     445       /*  MX_OVFL_IRQ2 IRC0_IRQPL111 : IRQPL445 IRC0_IRQVA445  */
#define IRQ_446     446       /*  MX_OVFL_IRQ3 IRC0_IRQPL111 : IRQPL446 IRC0_IRQVA446  */
#define IRQ_447     447       /*  MX_OVFL_IRQ4 IRC0_IRQPL111 : IRQPL447 IRC0_IRQVA447  */
#define IRQ_453     453       /*  MX_DMA_ERR_IRQ0 IRC0_IRQPL113 : IRQPL453 IRC0_IRQVA453  */
#define IRQ_454     454       /*  MX_DMA_ERR_IRQ1 IRC0_IRQPL113 : IRQPL454 IRC0_IRQVA454  */
#define IRQ_455     455       /*  MX_DMA_ERR_IRQ2 IRC0_IRQPL113 : IRQPL455 IRC0_IRQVA455  */
#define IRQ_456     456       /*  MX_DMA_ERR_IRQ3 IRC0_IRQPL114 : IRQPL456 IRC0_IRQVA456  */
#define IRQ_457     457       /*  MX_DMA_ERR_IRQ4 IRC0_IRQPL114 : IRQPL457 IRC0_IRQVA457  */
#define IRQ_458     458       /*  MX_AHB_ERR_IRQ IRC0_IRQPL114 : IRQPL458 IRC0_IRQVA458  */




/* Total number of interrupts and exceptions
 */
#define NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS IRQ_458

/* Offset from start of exceptions to interrupts
 * Exceptions have negative offsets while interrupts have positive
 */
#define IRQ_INTERRUPT_OFFSET 0

typedef uint16 IrqType;

typedef enum {
    PERIPHERAL_CLOCK_BLA,
} Mcu_Arc_PeriperalClock_t;

typedef enum {
    CPU_0=0,
} Cpu_t;


#endif /* IRQ_TMS570_H_ */
