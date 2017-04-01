/**
 * \file IfxMtu.h
 * \brief This file contains the API for memory tests.
 * Port related functions.
 *
 * \copyright Copyright (c) 2012 Infineon Technologies AG. All rights reserved.
 *
 * $Revision: 003 $
 * $Date: 24-05-2013 12:09 +0530 $
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * \author Puneetha Mukherjee <puneetha.mukherjee@infineon.com>
 *
 */
#ifndef IFXMTU_H_
#define IFXMTU_H_

//#include "Compilers.h"

#define IFXMTU_CONFIG_EXTRACT_LBYTE       (0x0000FFFFU)
#define IFXMTU_CONFIG_EXTRACT_HBYTE       (0xFFFF0000U)

#define IFXMTU_MC0_ADDR                   (0xF0061000U)
#define IFXMTU_CON_OFFSET                 (0x100U)                                        
#define IFXMTU_MC0                        (32U)
#define IFXMTU_MC1                        (64U)
#define IFXMTU_MAXIMUM_NB_MBISTS          (88U)
#define IFXMTU_ADDRESS_EXTRACT_MASK       (0x000fffffU)

#define IFXMTU_NOND_NUMACCS               (0x4000U)
#define IFXMTU_NOND_ACC                   (0x0005U)
#define IFXMTU_NOND_TEST                  (0x5000U)
#define IFXMTU_CHE_TEST                   (0x0008U)
#define IFXMTU_MARU_TEST                  (0x0006U)
#define IFXMTU_MARC_TEST                  (0x0002U)
                                          
#define IFXMTU_FAILDMP_EN                 (0x0200U)
#define IFXMTU_START_TEST                 (0x0001U)
                                          
#define IFXMTU_DONE                       (0x0001U)
                                          
#define IFXMTU_FAIL                       (0x02U)
#define IFXMTU_RANGE_BIT                  (15U)
#define IFXMTU_UP_ADDR_BIT                (7U)
#define IFXMTU_TESTS_MASK                 (0xB000U)

#if defined IFXMTU_ADDRESS_DSPR_1K                                              
  #define IFXMTU_DSPR_RANGE                  (128U)
  #define  IFXMTU_DSPR_ADDRESS_EXTRACT_BIT   (10U)
#else
  #define IFXMTU_DSPR_RANGE                  (33U)  
  #define  IFXMTU_DSPR_ADDRESS_EXTRACT_BIT   (12U)
#endif  

#if defined IFXMTU_ADDRESS_PSPR_1K
  #define IFXMTU_PSPR_RANGE                  (24U)
  #define IFXMTU_PSPR_ADDRESS_EXTRACT_BIT    (10U)
#else
  #define IFXMTU_PSPR_RANGE                  (6U)
  #define IFXMTU_PSPR_ADDRESS_EXTRACT_BIT    (12U)
#endif

/* Macros for the DSPR memory locations , RANGE registers */
#define IFXMTU_DSPR_0K                     (0x00U)
#define IFXMTU_DSPR_1K                     (0x01U)
#define IFXMTU_DSPR_2K                     (0x02U)
#define IFXMTU_DSPR_3K                     (0x03U)
#define IFXMTU_DSPR_4K                     (0x04U)
#define IFXMTU_DSPR_5K                     (0x05U)
#define IFXMTU_DSPR_6K                     (0x06U)
#define IFXMTU_DSPR_7K                     (0x07U)
#define IFXMTU_DSPR_8K                     (0x08U)
#define IFXMTU_DSPR_9K                     (0x09U)
#define IFXMTU_DSPR_10K                    (0x0AU)
#define IFXMTU_DSPR_11K                    (0x0BU)
#define IFXMTU_DSPR_12K                    (0x0CU)
#define IFXMTU_DSPR_13K                    (0x0DU)
#define IFXMTU_DSPR_14K                    (0x0EU)
#define IFXMTU_DSPR_15K                    (0x0FU)
#define IFXMTU_DSPR_16K                    (0x20U)
#define IFXMTU_DSPR_17K                    (0x21U)
#define IFXMTU_DSPR_18K                    (0x22U)
#define IFXMTU_DSPR_19K                    (0x23U)
#define IFXMTU_DSPR_20K                    (0x24U)
#define IFXMTU_DSPR_21K                    (0x25U)
#define IFXMTU_DSPR_22K                    (0x26U)
#define IFXMTU_DSPR_23K                    (0x27U)
#define IFXMTU_DSPR_24K                    (0x28U)
#define IFXMTU_DSPR_25K                    (0x29U)
#define IFXMTU_DSPR_26K                    (0x2AU)
#define IFXMTU_DSPR_27K                    (0x2BU)
#define IFXMTU_DSPR_28K                    (0x2CU)
#define IFXMTU_DSPR_29K                    (0x2DU)
#define IFXMTU_DSPR_30K                    (0x2EU)
#define IFXMTU_DSPR_31K                    (0x2FU)
#define IFXMTU_DSPR_32K                    (0x40U)
#define IFXMTU_DSPR_33K                    (0x41U)
#define IFXMTU_DSPR_34K                    (0x42U)
#define IFXMTU_DSPR_35K                    (0x43U)
#define IFXMTU_DSPR_36K                    (0x44U)
#define IFXMTU_DSPR_37K                    (0x45U)
#define IFXMTU_DSPR_38K                    (0x46U)
#define IFXMTU_DSPR_39K                    (0x47U)
#define IFXMTU_DSPR_40K                    (0x48U)
#define IFXMTU_DSPR_41K                    (0x49U)
#define IFXMTU_DSPR_42K                    (0x4AU)
#define IFXMTU_DSPR_43K                    (0x4BU)
#define IFXMTU_DSPR_44K                    (0x4CU)
#define IFXMTU_DSPR_45K                    (0x4DU)
#define IFXMTU_DSPR_46K                    (0x4EU)
#define IFXMTU_DSPR_47K                    (0x4FU)
#define IFXMTU_DSPR_48K                    (0x60U)
#define IFXMTU_DSPR_49K                    (0x61U)
#define IFXMTU_DSPR_50K                    (0x62U)
#define IFXMTU_DSPR_51K                    (0x63U)
#define IFXMTU_DSPR_52K                    (0x64U)
#define IFXMTU_DSPR_53K                    (0x65U)
#define IFXMTU_DSPR_54K                    (0x66U)
#define IFXMTU_DSPR_55K                    (0x67U)
#define IFXMTU_DSPR_56K                    (0x68U)
#define IFXMTU_DSPR_57K                    (0x69U)
#define IFXMTU_DSPR_58K                    (0x6AU)
#define IFXMTU_DSPR_59K                    (0x6BU)
#define IFXMTU_DSPR_60K                    (0x6CU)
#define IFXMTU_DSPR_61K                    (0x6DU)
#define IFXMTU_DSPR_62K                    (0x6EU)
#define IFXMTU_DSPR_63K                    (0x6FU)
#define IFXMTU_DSPR_64K                    (0x10U)
#define IFXMTU_DSPR_65K                    (0x11U)
#define IFXMTU_DSPR_66K                    (0x12U)
#define IFXMTU_DSPR_67K                    (0x13U)
#define IFXMTU_DSPR_68K                    (0x14U)
#define IFXMTU_DSPR_69K                    (0x15U)
#define IFXMTU_DSPR_70K                    (0x16U)
#define IFXMTU_DSPR_71K                    (0x17U)
#define IFXMTU_DSPR_72K                    (0x18U)
#define IFXMTU_DSPR_73K                    (0x19U)
#define IFXMTU_DSPR_74K                    (0x1AU)
#define IFXMTU_DSPR_75K                    (0x1BU)
#define IFXMTU_DSPR_76K                    (0x1CU)
#define IFXMTU_DSPR_77K                    (0x1DU)
#define IFXMTU_DSPR_78K                    (0x1EU)
#define IFXMTU_DSPR_79K                    (0x1FU)
#define IFXMTU_DSPR_80K                    (0x30U)
#define IFXMTU_DSPR_81K                    (0x31U)
#define IFXMTU_DSPR_82K                    (0x32U)
#define IFXMTU_DSPR_83K                    (0x33U)
#define IFXMTU_DSPR_84K                    (0x34U)
#define IFXMTU_DSPR_85K                    (0x35U)
#define IFXMTU_DSPR_86K                    (0x36U)
#define IFXMTU_DSPR_87K                    (0x37U)
#define IFXMTU_DSPR_88K                    (0x38U)
#define IFXMTU_DSPR_89K                    (0x39U)
#define IFXMTU_DSPR_90K                    (0x3AU)
#define IFXMTU_DSPR_91K                    (0x3BU)
#define IFXMTU_DSPR_92K                    (0x3CU)
#define IFXMTU_DSPR_93K                    (0x3DU)
#define IFXMTU_DSPR_94K                    (0x3EU)
#define IFXMTU_DSPR_95K                    (0x3FU)
#define IFXMTU_DSPR_96K                    (0x50U)
#define IFXMTU_DSPR_97K                    (0x51U)
#define IFXMTU_DSPR_98K                    (0x52U)
#define IFXMTU_DSPR_99K                    (0x53U)
#define IFXMTU_DSPR_100K                   (0x54U)
#define IFXMTU_DSPR_101K                   (0x55U)
#define IFXMTU_DSPR_102K                   (0x56U)
#define IFXMTU_DSPR_103K                   (0x57U)
#define IFXMTU_DSPR_104K                   (0x58U)
#define IFXMTU_DSPR_105K                   (0x59U)
#define IFXMTU_DSPR_106K                   (0x5AU)
#define IFXMTU_DSPR_107K                   (0x5BU)
#define IFXMTU_DSPR_108K                   (0x5CU)
#define IFXMTU_DSPR_109K                   (0x5DU)
#define IFXMTU_DSPR_110K                   (0x5EU)
#define IFXMTU_DSPR_111K                   (0x5FU)
#define IFXMTU_DSPR_112K                   (0x70U)
#define IFXMTU_DSPR_113K                   (0x71U)
#define IFXMTU_DSPR_114K                   (0x72U)
#define IFXMTU_DSPR_115K                   (0x73U)
#define IFXMTU_DSPR_116K                   (0x74U)
#define IFXMTU_DSPR_117K                   (0x75U)
#define IFXMTU_DSPR_118K                   (0x76U)
#define IFXMTU_DSPR_119K                   (0x77U)
#define IFXMTU_DSPR_120K                   (0x78U)
#define IFXMTU_DSPR_121K                   (0x79U)
#define IFXMTU_DSPR_122K                   (0x7AU)
#define IFXMTU_DSPR_123K                   (0x7BU)
#define IFXMTU_DSPR_124K                   (0x7CU)
#define IFXMTU_DSPR_125K                   (0x7DU)
#define IFXMTU_DSPR_126K                   (0x7EU)
#define IFXMTU_DSPR_127K                   (0x7FU)

/* Macros for the PSPR memory locations , RANGE registers */
#define IFXMTU_PSPR_0K                    (0x000U)
#define IFXMTU_PSPR_1K                    (0x03U)
#define IFXMTU_PSPR_2K                    (0x04U)
#define IFXMTU_PSPR_3K                    (0x07U)
#define IFXMTU_PSPR_4K                    (0x08U)
#define IFXMTU_PSPR_5K                    (0x0BU)
#define IFXMTU_PSPR_6K                    (0x0CU)
#define IFXMTU_PSPR_7K                    (0x0FU)
#define IFXMTU_PSPR_8K                    (0x10U)
#define IFXMTU_PSPR_9K                    (0x13U)
#define IFXMTU_PSPR_10K                   (0x14U)
#define IFXMTU_PSPR_11K                   (0x17U)
#define IFXMTU_PSPR_12K                   (0x18U)
#define IFXMTU_PSPR_13K                   (0x1BU)
#define IFXMTU_PSPR_14K                   (0x1CU)
#define IFXMTU_PSPR_15K                   (0x1FU)
#define IFXMTU_PSPR_16K                   (0x20U)
#define IFXMTU_PSPR_17K                   (0x23U)
#define IFXMTU_PSPR_18K                   (0x24U)
#define IFXMTU_PSPR_19K                   (0x27U)
#define IFXMTU_PSPR_20K                   (0x28U)
#define IFXMTU_PSPR_21K                   (0x2BU)
#define IFXMTU_PSPR_22K                   (0x2CU)
#define IFXMTU_PSPR_23K                   (0x2FU)

/* Memory Controller Numbers */
#define IFXMTU_CPU2_DSPR                  (0U)
#define IFXMTU_CPU2_DCACHE                (1U)
#define IFXMTU_CPU2_DTAG                  (2U)
#define IFXMTU_CPU2_PSPR                  (3U)
#define IFXMTU_CPU2_PCACHE                (4U)
#define IFXMTU_CPU2_PTAG                  (5U)
#define IFXMTU_CPU1_DSPR                  (6U)
#define IFXMTU_CPU1_DCACHE                (7U)
#define IFXMTU_CPU1_DTAG                  (8U)
#define IFXMTU_CPU1_PSPR                  (9U)
#define IFXMTU_CPU1_PCACHE                (10U)
#define IFXMTU_CPU1_PTAG                  (11U)
#define IFXMTU_CPU0_DSPR                  (14U)
#define IFXMTU_CPU0_PCACHE                (15U)
#define IFXMTU_CPU0_PSPR                  (16U)
#define IFXMTU_CPU0_PTAG                  (17U)

/* Range enable */
#define IFXMTU_RANGE_ENABLE               (1U)
#define IFXMTU_RANGE_DISBLE               (0U)


/* CPU Memory ranges */
#define IFXMTU_CPU2_DSPR_START     (0x50000000U)
#define IFXMTU_CPU2_DSPR_END       (0x5001DFFFU)    
#define IFXMTU_CPU2_PSPR_START     (0x50100000U)
#define IFXMTU_CPU2_PSPR_END       (0x50105FFFU)
                          
#define IFXMTU_CPU1_DSPR_START     (0x60000000U)
#define IFXMTU_CPU1_DSPR_END       (0x6001DFFFU)
#define IFXMTU_CPU1_PSPR_START     (0x60100000U)
#define IFXMTU_CPU1_PSPR_END       (0x60105FFFU)


#define IFXMTU_CPU0_DSPR_START     (0x70000000U)
#define IFXMTU_CPU0_DSPR_END       (0x7001BFFFU)
#define IFXMTU_CPU0_PSPR_START     (0x70100000U)
#define IFXMTU_CPU0_PSPR_END       (0x70105FFFU)

#if !defined TC2XX_A_Step
  void Ifx_ldisableMtu(void) ;
  void Ifx_lenableMtu(void);
#endif
  /* #if defined TC2XX_A_Step */

uint8 IfxMtu_Non_Destructive_test( uint8 mbistSel    , uint8 RangeSel , 
                                   uint8 RangeAddrUp ,uint8 RangeAddrLow,
                                   uint16 * ErrorAddr 
                                  );


uint8 IfxMtu_CheckerBoard_test ( uint8 mbistSel , uint8 numberRedundancyLines,
                                        uint8 RangeSel , uint8 RangeAddrUp ,
                                        uint8 RangeAddrLow , uint16 * ErrorAddr
                                      );

uint8 IfxMtu_MarchU_test ( uint8 mbistSel , uint8 numberRedundancyLines,
                           uint8 RangeSel , uint8 RangeAddrUp ,
                           uint8 RangeAddrLow , uint16 * ErrorAddr
                         );

void IfxMtu_PerformAutoInit ( uint8 mbistSel , uint16 InitData,
                             uint8 RangeSel , uint8 RangeAddrUp ,uint8 RangeAddrLow,
                             register  uint8 eccData
                            );

#endif /* IFXMTU_H_ */
