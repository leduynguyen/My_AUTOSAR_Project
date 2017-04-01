/**
 * \file IfxStart_Cfg.c
 * \brief Driver configuration.
 *
 * \license
 * You can use this file under the terms of the IFX License.
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the IFX License for more details (IFX_License.txt).
 *
 * This file may be used, copied, and distributed, with or without modification, provided
 * that all copyright notices are retained; that all modifications to this file are
 * prominently noted in the modified file; and that this paragraph is not modified.
 *
 * \copyright Copyright (C) 2013 Infineon Technologies AG
 * \author Puneetha Mukherjee <puneetha.mukherjee@infineon.com>
 *
 * $Revision: 004 $
 * $Date: 24-05-2013 12:09 +0530 $
 *
 * \defgroup Ifx Infineon Software
 * \defgroup Ifx_Lld Infineon Low Level Drivers' Software
 * \ingroup I
 */ 
/******************************************************************************/
#include "Ifx_Types.h"
#include "IfxPort_reg.h"
#include "IfxStart_Cfg.h"
#include "IfxMtu.h"
#include "IfxStart.h"

#ifdef __GNUC__
  #pragma section
  #pragma section ".start_driver_data" awz
#endif

#if defined(__TASKING__)
#pragma section neardata ="START_VARS"
#pragma align 4
#endif


#define IFXSTART_PORT_PIN_0      (0U)    
#define IFXSTART_PORT_PIN_1      (1U)    
#define IFXSTART_PORT_PIN_2      (2U)    
#define IFXSTART_PORT_PIN_3      (3U)    
#define IFXSTART_PORT_PIN_4      (4U)    
#define IFXSTART_PORT_PIN_5      (5U)    
#define IFXSTART_PORT_PIN_6      (6U)    
#define IFXSTART_PORT_PIN_7      (7U)    
#define IFXSTART_PORT_PIN_8      (8U)
#define IFXSTART_PORT_PIN_9      (9U)    
#define IFXSTART_PORT_PIN_10     (10U)   
#define IFXSTART_PORT_PIN_11     (11U)   
#define IFXSTART_PORT_PIN_12     (12U)   
#define IFXSTART_PORT_PIN_13     (13U)   
#define IFXSTART_PORT_PIN_14     (14U)   
#define IFXSTART_PORT_PIN_15     (15U)   

uint8  IfxStart_Ram_Tst ;
uint8  IfxStart_Mtu_Table_Dspr [IFXMTU_DSPR_RANGE] =
{
  IFXMTU_DSPR_0K ,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_1K ,
    IFXMTU_DSPR_2K , 
    IFXMTU_DSPR_3K ,
  #endif 
  IFXMTU_DSPR_4K ,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_5K ,
    IFXMTU_DSPR_6K , 
    IFXMTU_DSPR_7K ,  
  #endif
  IFXMTU_DSPR_8K ,
  #if defined IFXMTU_ADDRESS_DSPR_1K     
    IFXMTU_DSPR_9K ,  
    IFXMTU_DSPR_10K ,
    IFXMTU_DSPR_11K ,    
  #endif   
  IFXMTU_DSPR_12K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_13K,
    IFXMTU_DSPR_14K,
    IFXMTU_DSPR_15K,   
  #endif   
  IFXMTU_DSPR_16K,  
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_17K,
    IFXMTU_DSPR_18K,
    IFXMTU_DSPR_19K,
  #endif 
  IFXMTU_DSPR_20K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_21K,
    IFXMTU_DSPR_22K,
    IFXMTU_DSPR_23K,        
  #endif 
  IFXMTU_DSPR_24K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_25K,
    IFXMTU_DSPR_26K,
    IFXMTU_DSPR_27K,          
  #endif 
  IFXMTU_DSPR_28K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_29K,
    IFXMTU_DSPR_30K,
    IFXMTU_DSPR_31K,          
  #endif 
  IFXMTU_DSPR_32K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_33K,           
    IFXMTU_DSPR_34K,          
    IFXMTU_DSPR_35K,                   
  #endif 
  IFXMTU_DSPR_36K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_37K,          
    IFXMTU_DSPR_38K,          
    IFXMTU_DSPR_39K,                    
  #endif 
  IFXMTU_DSPR_40K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_41K,
    IFXMTU_DSPR_42K,
    IFXMTU_DSPR_43K,        
  #endif 
  IFXMTU_DSPR_44K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_45K,
    IFXMTU_DSPR_46K,
    IFXMTU_DSPR_47K,          
  #endif 
  IFXMTU_DSPR_48K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_49K,
    IFXMTU_DSPR_50K,
    IFXMTU_DSPR_51K,          
  #endif 
  IFXMTU_DSPR_52K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_53K,          
    IFXMTU_DSPR_54K,          
    IFXMTU_DSPR_55K,                    
  #endif 
  IFXMTU_DSPR_56K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_57K,          
    IFXMTU_DSPR_58K,          
    IFXMTU_DSPR_59K,                      
  #endif 
  IFXMTU_DSPR_60K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_61K,
    IFXMTU_DSPR_62K,
    IFXMTU_DSPR_63K,        
  #endif 
  IFXMTU_DSPR_64K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_65K,
    IFXMTU_DSPR_66K,
    IFXMTU_DSPR_67K,  
  #endif 
  IFXMTU_DSPR_68K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_69K,
    IFXMTU_DSPR_70K,
    IFXMTU_DSPR_71K,          
  #endif 
  IFXMTU_DSPR_72K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_73K,
    IFXMTU_DSPR_74K,
    IFXMTU_DSPR_75K,            
  #endif 
  IFXMTU_DSPR_76K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_77K,
    IFXMTU_DSPR_78K,
    IFXMTU_DSPR_79K,  
  #endif 
  IFXMTU_DSPR_80K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_81K,
    IFXMTU_DSPR_82K,
    IFXMTU_DSPR_83K,
  #endif 
  IFXMTU_DSPR_84K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_85K,
    IFXMTU_DSPR_86K,
    IFXMTU_DSPR_87K,  
  #endif 
  IFXMTU_DSPR_88K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_89K,
    IFXMTU_DSPR_90K,
    IFXMTU_DSPR_91K,  
  #endif 
  IFXMTU_DSPR_92K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_93K,
    IFXMTU_DSPR_94K,
    IFXMTU_DSPR_95K,  
  #endif 
  IFXMTU_DSPR_96K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_97K,
    IFXMTU_DSPR_98K,
    IFXMTU_DSPR_99K,  
  #endif 
  IFXMTU_DSPR_100K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_101K,
    IFXMTU_DSPR_102K,
    IFXMTU_DSPR_103K,
  #endif 
  IFXMTU_DSPR_104K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_105K,
    IFXMTU_DSPR_106K,
    IFXMTU_DSPR_107K,  
  #endif 
  IFXMTU_DSPR_108K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_109K,
    IFXMTU_DSPR_110K,
    IFXMTU_DSPR_111K,  
  #endif 
  IFXMTU_DSPR_112K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_113K,
    IFXMTU_DSPR_114K,
    IFXMTU_DSPR_115K,  
  #endif 
  IFXMTU_DSPR_116K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_117K,
    IFXMTU_DSPR_118K,
    IFXMTU_DSPR_119K,  
  #endif 
  IFXMTU_DSPR_120K,
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    IFXMTU_DSPR_121K,
    IFXMTU_DSPR_122K,
    IFXMTU_DSPR_123K,  
  #endif 
  IFXMTU_DSPR_124K 
  #if defined IFXMTU_ADDRESS_DSPR_1K   
    ,
    IFXMTU_DSPR_125K,
    IFXMTU_DSPR_126K,
    IFXMTU_DSPR_127K  
  #endif   
} ;

uint8 IfxStart_Mtu_Table_Pspr [IFXMTU_PSPR_RANGE] =
{
  IFXMTU_PSPR_0K  ,
#if defined IFXMTU_ADDRESS_PSPR_1K
  IFXMTU_PSPR_1K  ,
  IFXMTU_PSPR_2K  ,
  IFXMTU_PSPR_3K  ,
#endif
  IFXMTU_PSPR_4K  ,
#if defined IFXMTU_ADDRESS_DSPR_1K
  IFXMTU_PSPR_5K  ,
  IFXMTU_PSPR_6K  ,
  IFXMTU_PSPR_7K  ,
#endif
  IFXMTU_PSPR_8K  ,
#if defined IFXMTU_ADDRESS_DSPR_1K
  IFXMTU_PSPR_9K  ,
  IFXMTU_PSPR_10K ,
  IFXMTU_PSPR_11K ,
#endif
  IFXMTU_PSPR_12K ,
#if defined IFXMTU_ADDRESS_DSPR_1K
  IFXMTU_PSPR_13K ,
  IFXMTU_PSPR_14K ,
  IFXMTU_PSPR_15K ,
#endif
  IFXMTU_PSPR_16K ,
#if defined IFXMTU_ADDRESS_DSPR_1K
  IFXMTU_PSPR_17K ,
  IFXMTU_PSPR_18K ,
  IFXMTU_PSPR_19K ,
#endif
  IFXMTU_PSPR_20K
#if defined IFXMTU_ADDRESS_DSPR_1K
  ,
  IFXMTU_PSPR_21K ,
  IFXMTU_PSPR_22K ,
  IFXMTU_PSPR_23K
#endif
};

IfxStart_RamTestCfgType IfxStart_kRamTstConfiguration[IFXSTART_NUM_RAM_SECTIONS] =
{
  #if defined BIOS_SEGMENT_00_START
    /* Segment 0 Configurations */
    {
        BIOS_SEGMENT_00_START,
          BIOS_SEGMENT_00_END,
      0U , /* This will be polpulated in the inititialization */
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_00_START >= IFXMTU_CPU0_DSPR_START) && (BIOS_SEGMENT_00_START <= IFXMTU_CPU0_DSPR_END))
        IFXSTART_CPU0_DSPR ,
      #elif ((BIOS_SEGMENT_00_START >= IFXMTU_CPU0_PSPR_START) && (BIOS_SEGMENT_00_START <= IFXMTU_CPU0_PSPR_END))
        IFXSTART_CPU0_PSPR ,                                                                            
      #endif 
         /* */  
      BIOS_CLEAR_SEGMENT_00
    }
  #endif
      /* BIOS_SEGMENT_00_START */
  #if  defined BIOS_SEGMENT_01_START
    ,/* Segment 1 Configurations */
    {
        BIOS_SEGMENT_01_START,
      BIOS_SEGMENT_01_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST,
      #if ((BIOS_SEGMENT_01_START >= IFXMTU_CPU0_DSPR_START) && (BIOS_SEGMENT_01_START <= IFXMTU_CPU0_DSPR_END))
        IFXSTART_CPU0_DSPR ,
      #elif ((BIOS_SEGMENT_01_START >= IFXMTU_CPU0_PSPR_START) && (BIOS_SEGMENT_01_START <= IFXMTU_CPU0_PSPR_END))
        IFXSTART_CPU0_PSPR ,
      #endif
     /* */
      BIOS_CLEAR_SEGMENT_01
    }
  #endif
      /* BIOS_SEGMENT_01_START */
  
  #if  defined BIOS_SEGMENT_02_START
    ,/* Segment 2 Configurations */
    {
        BIOS_SEGMENT_02_START,
          BIOS_SEGMENT_02_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_02_START >= IFXMTU_CPU0_DSPR_START) && (BIOS_SEGMENT_02_START <= IFXMTU_CPU0_DSPR_END))
        IFXSTART_CPU0_DSPR ,
      #elif ((BIOS_SEGMENT_02_START >= IFXMTU_CPU0_PSPR_START) && (BIOS_SEGMENT_02_START <= IFXMTU_CPU0_PSPR_END))
        IFXSTART_CPU0_PSPR ,
      #endif
     /* */  
      BIOS_CLEAR_SEGMENT_02
    }
  #endif
      /* #ifdef  BIOS_SEGMENT_02_START */
  #if  defined BIOS_SEGMENT_03_START
    ,/* Segment 3 Configurations */
    {
        BIOS_SEGMENT_03_START,
          BIOS_SEGMENT_03_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_03_START >= IFXMTU_CPU0_DSPR_START) && (BIOS_SEGMENT_03_START <= IFXMTU_CPU0_DSPR_END))
        IFXSTART_CPU0_DSPR ,
      #elif ((BIOS_SEGMENT_03_START >= IFXMTU_CPU0_PSPR_START) && (BIOS_SEGMENT_03_START <= IFXMTU_CPU0_PSPR_END))
        IFXSTART_CPU0_PSPR ,
      #endif
      /* */
      BIOS_CLEAR_SEGMENT_03
    }
  #endif
    /* #ifdef  BIOS_SEGMENT_03_START */

  #if defined BIOS_SEGMENT_04_START
    ,/* Segment 4 Configurations */
    {
        BIOS_SEGMENT_04_START,
          BIOS_SEGMENT_04_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_04_START >= IFXMTU_CPU0_DSPR_START) && (BIOS_SEGMENT_04_START <= IFXMTU_CPU0_DSPR_END))
        IFXSTART_CPU0_DSPR ,
      #elif ((BIOS_SEGMENT_04_START >= IFXMTU_CPU0_PSPR_START) && (BIOS_SEGMENT_04_START <= IFXMTU_CPU0_PSPR_END))
        IFXSTART_CPU0_PSPR ,
      #endif
      /* */
      BIOS_CLEAR_SEGMENT_04
    }
   #endif
    /* #ifdef  BIOS_SEGMENT_04_START */
  #if defined BIOS_SEGMENT_05_START
    ,/* Segment 5 Configurations */
    {
        BIOS_SEGMENT_05_START,
          BIOS_SEGMENT_05_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_05_START >= IFXMTU_CPU0_DSPR_START) && (BIOS_SEGMENT_05_START <= IFXMTU_CPU0_DSPR_END))
        IFXSTART_CPU0_DSPR ,
      #elif ((BIOS_SEGMENT_05_START >= IFXMTU_CPU0_PSPR_START) && (BIOS_SEGMENT_05_START <= IFXMTU_CPU0_PSPR_END))
        IFXSTART_CPU0_PSPR ,
      #endif
      /* */
      BIOS_CLEAR_SEGMENT_05
    }
   #endif
    /* #ifdef  BIOS_SEGMENT_05_START */
  #if defined BIOS_SEGMENT_06_START
    ,/* Segment 6 Configurations */
    {
        BIOS_SEGMENT_06_START,
          BIOS_SEGMENT_06_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_06_START >= IFXMTU_CPU0_DSPR_START) && (BIOS_SEGMENT_06_START <= IFXMTU_CPU0_DSPR_END))
        IFXSTART_CPU0_DSPR ,
      #elif ((BIOS_SEGMENT_06_START >= IFXMTU_CPU0_PSPR_START) && (BIOS_SEGMENT_06_START <= IFXMTU_CPU0_PSPR_END))
        IFXSTART_CPU0_PSPR ,
      #endif
      /* */
      BIOS_CLEAR_SEGMENT_06
    }
   #endif
    /* #ifdef  BIOS_SEGMENT_06_START */    
  #if defined BIOS_SEGMENT_07_START
    ,/* Segment 7 Configurations */
    {
        BIOS_SEGMENT_07_START,
          BIOS_SEGMENT_07_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_07_START >= IFXMTU_CPU0_DSPR_START) && (BIOS_SEGMENT_07_START <= IFXMTU_CPU0_DSPR_END))
        IFXSTART_CPU0_DSPR ,
      #elif ((BIOS_SEGMENT_07_START >= IFXMTU_CPU0_PSPR_START) && (BIOS_SEGMENT_07_START <= IFXMTU_CPU0_PSPR_END))
        IFXSTART_CPU0_PSPR ,
      #endif
      /* */
      BIOS_CLEAR_SEGMENT_07
    }
   #endif
    /* #ifdef  BIOS_SEGMENT_07_START */
  #if defined BIOS_SEGMENT_10_START
    /* Segment 0 Configurations */
    ,{
        BIOS_SEGMENT_10_START,
          BIOS_SEGMENT_10_END,
      0U , /* This will be polpulated in the inititialization */
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_10_START >= IFXMTU_CPU1_DSPR_START) && (BIOS_SEGMENT_10_START <= IFXMTU_CPU1_DSPR_END))
        IFXSTART_CPU1_DSPR ,
      #elif ((BIOS_SEGMENT_10_START >= IFXMTU_CPU1_PSPR_START) && (BIOS_SEGMENT_10_START <= IFXMTU_CPU1_PSPR_END))
        IFXSTART_CPU1_PSPR ,                                                                            
      #endif 
         /* */  
      BIOS_CLEAR_SEGMENT_10
    }
  #endif
      /* BIOS_SEGMENT_10_START */
  #if defined BIOS_SEGMENT_11_START
    ,/* Segment 1 Configurations */
    {
        BIOS_SEGMENT_11_START,
      BIOS_SEGMENT_11_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_11_START >= IFXMTU_CPU1_DSPR_START) && (BIOS_SEGMENT_11_START <= IFXMTU_CPU1_DSPR_END))
        IFXSTART_CPU1_DSPR ,
      #elif ((BIOS_SEGMENT_11_START >= IFXMTU_CPU1_PSPR_START) && (BIOS_SEGMENT_11_START <= IFXMTU_CPU1_PSPR_END))
        IFXSTART_CPU1_PSPR ,
      #endif
     /* */
      BIOS_CLEAR_SEGMENT_11
    }
  #endif
      /* BIOS_SEGMENT_11_START */
  
  #if defined BIOS_SEGMENT_12_START
    ,/* Segment 2 Configurations */
    {
        BIOS_SEGMENT_12_START,
          BIOS_SEGMENT_12_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_12_START >= IFXMTU_CPU1_DSPR_START) && (BIOS_SEGMENT_12_START <= IFXMTU_CPU1_DSPR_END))
        IFXSTART_CPU1_DSPR ,
      #elif ((BIOS_SEGMENT_12_START >= IFXMTU_CPU1_PSPR_START) && (BIOS_SEGMENT_12_START <= IFXMTU_CPU1_PSPR_END))
        IFXSTART_CPU1_PSPR ,
      #endif
     /* */  
      BIOS_CLEAR_SEGMENT_12
    }
  #endif
      /* #ifdef  BIOS_SEGMENT_12_START */
  #if defined BIOS_SEGMENT_13_START
    ,/* Segment 3 Configurations */
    {
        BIOS_SEGMENT_13_START,
          BIOS_SEGMENT_13_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_13_START >= IFXMTU_CPU1_DSPR_START) && (BIOS_SEGMENT_13_START <= IFXMTU_CPU1_DSPR_END))
        IFXSTART_CPU1_DSPR ,
      #elif ((BIOS_SEGMENT_13_START >= IFXMTU_CPU1_PSPR_START) && (BIOS_SEGMENT_13_START <= IFXMTU_CPU1_PSPR_END))
        IFXSTART_CPU1_PSPR ,
      #endif
      /* */
      BIOS_CLEAR_SEGMENT_13
    }
  #endif
    /* #ifdef  BIOS_SEGMENT_13_START */

  #if defined  BIOS_SEGMENT_14_START
    ,/* Segment 4 Configurations */
    {
        BIOS_SEGMENT_14_START,
          BIOS_SEGMENT_14_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_14_START >= IFXMTU_CPU1_DSPR_START) && (BIOS_SEGMENT_14_START <= IFXMTU_CPU1_DSPR_END))
        IFXSTART_CPU1_DSPR ,
      #elif ((BIOS_SEGMENT_14_START >= IFXMTU_CPU1_PSPR_START) && (BIOS_SEGMENT_14_START <= IFXMTU_CPU1_PSPR_END))
        IFXSTART_CPU1_PSPR ,
      #endif
      /* */
      BIOS_CLEAR_SEGMENT_14
    }
   #endif
    /* #ifdef  BIOS_SEGMENT_14_START */
  #if defined BIOS_SEGMENT_15_START
    ,/* Segment 5 Configurations */
    {
        BIOS_SEGMENT_15_START,
          BIOS_SEGMENT_15_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_15_START >= IFXMTU_CPU1_DSPR_START) && (BIOS_SEGMENT_15_START <= IFXMTU_CPU1_DSPR_END))
        IFXSTART_CPU1_DSPR ,
      #elif ((BIOS_SEGMENT_15_START >= IFXMTU_CPU1_PSPR_START) && (BIOS_SEGMENT_15_START <= IFXMTU_CPU1_PSPR_END))
        IFXSTART_CPU1_PSPR ,
      #endif
      /* */
      BIOS_CLEAR_SEGMENT_15
    }
   #endif
    /* #ifdef  BIOS_SEGMENT_15_START */
  #if defined BIOS_SEGMENT_16_START
    ,/* Segment 6 Configurations */
    {
        BIOS_SEGMENT_16_START,
          BIOS_SEGMENT_16_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_16_START >= IFXMTU_CPU1_DSPR_START) && (BIOS_SEGMENT_16_START <= IFXMTU_CPU1_DSPR_END))
        IFXSTART_CPU1_DSPR ,
      #elif ((BIOS_SEGMENT_16_START >= IFXMTU_CPU1_PSPR_START) && (BIOS_SEGMENT_16_START <= IFXMTU_CPU1_PSPR_END))
        IFXSTART_CPU1_PSPR ,
      #endif
      /* */
      BIOS_CLEAR_SEGMENT_16
    }
   #endif
    /* #ifdef  BIOS_SEGMENT_16_START */    
  #if defined  BIOS_SEGMENT_17_START
    ,/* Segment 7 Configurations */
    {
        BIOS_SEGMENT_17_START,
          BIOS_SEGMENT_17_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_17_START >= IFXMTU_CPU1_DSPR_START) && (BIOS_SEGMENT_17_START <= IFXMTU_CPU1_DSPR_END))
        IFXSTART_CPU1_DSPR ,
      #elif ((BIOS_SEGMENT_17_START >= IFXMTU_CPU1_PSPR_START) && (BIOS_SEGMENT_17_START <= IFXMTU_CPU1_PSPR_END))
        IFXSTART_CPU1_PSPR ,
      #endif
      /* */
      BIOS_CLEAR_SEGMENT_17
    }
   #endif
    /* #ifdef  BIOS_SEGMENT_17_START */    
    
  #if defined BIOS_SEGMENT_20_START
    /* Segment 0 Configurations */
    ,{
        BIOS_SEGMENT_20_START,
          BIOS_SEGMENT_20_END,
      0U , /* This will be polpulated in the inititialization */
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_20_START >= IFXMTU_CPU2_DSPR_START) && (BIOS_SEGMENT_20_START <= IFXMTU_CPU2_DSPR_END))
        IFXSTART_CPU2_DSPR ,
      #elif ((BIOS_SEGMENT_20_START >= IFXMTU_CPU2_PSPR_START) && (BIOS_SEGMENT_20_START <= IFXMTU_CPU2_PSPR_END))
        IFXSTART_CPU2_PSPR ,                                                                            
      #endif 
         /* */  
      BIOS_CLEAR_SEGMENT_20
    }
  #endif
      /* BIOS_SEGMENT_20_START */
  #if defined BIOS_SEGMENT_21_START
    ,/* Segment 1 Configurations */
    {
        BIOS_SEGMENT_21_START,
      BIOS_SEGMENT_21_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_21_START >= IFXMTU_CPU2_DSPR_START) && (BIOS_SEGMENT_21_START <= IFXMTU_CPU2_DSPR_END))
        IFXSTART_CPU2_DSPR ,
      #elif ((BIOS_SEGMENT_21_START >= IFXMTU_CPU2_PSPR_START) && (BIOS_SEGMENT_21_START <= IFXMTU_CPU2_PSPR_END))
        IFXSTART_CPU2_PSPR ,
      #endif
     /* */
      BIOS_CLEAR_SEGMENT_21
    }
  #endif
      /* BIOS_SEGMENT_21_START */
  
  #if defined BIOS_SEGMENT_22_START
    ,/* Segment 2 Configurations */
    {
        BIOS_SEGMENT_22_START,
          BIOS_SEGMENT_22_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_22_START >= IFXMTU_CPU2_DSPR_START) && (BIOS_SEGMENT_22_START <= IFXMTU_CPU2_DSPR_END))
        IFXSTART_CPU2_DSPR ,
      #elif ((BIOS_SEGMENT_22_START >= IFXMTU_CPU2_PSPR_START) && (BIOS_SEGMENT_22_START <= IFXMTU_CPU2_PSPR_END))
        IFXSTART_CPU2_PSPR ,
      #endif
     /* */  
      BIOS_CLEAR_SEGMENT_22
    }
  #endif
      /* #ifdef  BIOS_SEGMENT_22_START */
  #if defined BIOS_SEGMENT_23_START
    ,/* Segment 3 Configurations */
    {
        BIOS_SEGMENT_23_START,
          BIOS_SEGMENT_23_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_23_START >= IFXMTU_CPU2_DSPR_START) && (BIOS_SEGMENT_23_START <= IFXMTU_CPU2_DSPR_END))
        IFXSTART_CPU2_DSPR ,
      #elif ((BIOS_SEGMENT_23_START >= IFXMTU_CPU2_PSPR_START) && (BIOS_SEGMENT_23_START <= IFXMTU_CPU2_PSPR_END))
        IFXSTART_CPU2_PSPR ,
      #endif
      /* */
      BIOS_CLEAR_SEGMENT_23
    }
  #endif
    /* #ifdef  BIOS_SEGMENT_23_START */

  #if defined BIOS_SEGMENT_24_START
    ,/* Segment 4 Configurations */
    {
        BIOS_SEGMENT_24_START,
          BIOS_SEGMENT_24_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_24_START >= IFXMTU_CPU2_DSPR_START) && (BIOS_SEGMENT_24_START <= IFXMTU_CPU2_DSPR_END))
        IFXSTART_CPU2_DSPR ,
      #elif ((BIOS_SEGMENT_24_START >= IFXMTU_CPU2_PSPR_START) && (BIOS_SEGMENT_24_START <= IFXMTU_CPU2_PSPR_END))
        IFXSTART_CPU2_PSPR ,
      #endif
      /* */
      BIOS_CLEAR_SEGMENT_24
    }
   #endif
    /* #ifdef  BIOS_SEGMENT_24_START */
  #if defined  BIOS_SEGMENT_25_START
    ,/* Segment 5 Configurations */
    {
        BIOS_SEGMENT_25_START,
          BIOS_SEGMENT_25_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_25_START >= IFXMTU_CPU2_DSPR_START) && (BIOS_SEGMENT_25_START <= IFXMTU_CPU2_DSPR_END))
        IFXSTART_CPU2_DSPR ,
      #elif ((BIOS_SEGMENT_25_START >= IFXMTU_CPU2_PSPR_START) && (BIOS_SEGMENT_25_START <= IFXMTU_CPU2_PSPR_END))
        IFXSTART_CPU2_PSPR ,
      #endif
      /* */
      BIOS_CLEAR_SEGMENT_25
    }
   #endif
    /* #ifdef  BIOS_SEGMENT_25_START */
  #if defined  BIOS_SEGMENT_26_START
    ,/* Segment 6 Configurations */
    {
        BIOS_SEGMENT_26_START,
          BIOS_SEGMENT_26_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_26_START >= IFXMTU_CPU2_DSPR_START) && (BIOS_SEGMENT_26_START <= IFXMTU_CPU2_DSPR_END))
        IFXSTART_CPU2_DSPR ,
      #elif ((BIOS_SEGMENT_26_START >= IFXMTU_CPU2_PSPR_START) && (BIOS_SEGMENT_26_START <= IFXMTU_CPU2_PSPR_END))
        IFXSTART_CPU2_PSPR ,
      #endif
      /* */
      BIOS_CLEAR_SEGMENT_26
    }
   #endif
    /* #ifdef  BIOS_SEGMENT_26_START */    
  #if defined BIOS_SEGMENT_27_START
    ,/* Segment 7 Configurations */
    {
        BIOS_SEGMENT_27_START,
          BIOS_SEGMENT_27_END,
      0U ,
      0U ,
      IFXSTART_MTU_NON_DES_TEST ,
      #if ((BIOS_SEGMENT_27_START >= IFXMTU_CPU2_DSPR_START) && (BIOS_SEGMENT_27_START <= IFXMTU_CPU2_DSPR_END))
        IFXSTART_CPU2_DSPR ,
      #elif ((BIOS_SEGMENT_27_START >= IFXMTU_CPU2_PSPR_START) && (BIOS_SEGMENT_27_START <= IFXMTU_CPU2_PSPR_END))
        IFXSTART_CPU2_PSPR ,
      #endif
      /* */
      BIOS_CLEAR_SEGMENT_27
    }
   #endif
    /* #ifdef  BIOS_SEGMENT_27_START */    
};

#if defined IFXSTART_ED_DEVICE_SUPPORTED
  /* ED memory Tile configurations */
  uint32 IfxEmem_Tile_Cfg[IFXEMEM_MAX_NUM_TILES ] =
  {
    IFXEMEM_TILE_CAL ,
    IFXEMEM_TILE_UNUSED ,
    IFXEMEM_TILE_TRACE ,
    IFXEMEM_TILE_UNCHANGED ,
    IFXEMEM_TILE_CAL ,
    IFXEMEM_TILE_UNUSED ,
    IFXEMEM_TILE_TRACE ,
    IFXEMEM_TILE_UNCHANGED ,
    IFXEMEM_TILE_CAL ,
    IFXEMEM_TILE_UNUSED ,
    IFXEMEM_TILE_TRACE ,
    IFXEMEM_TILE_UNCHANGED ,
    IFXEMEM_TILE_CAL ,
    IFXEMEM_TILE_UNUSED ,
    IFXEMEM_TILE_TRACE ,
    IFXEMEM_TILE_UNCHANGED
  };
#endif
   /* IFXSTART_ED_DEVICE_SUPPORTED */

/* port Configurations , 1 element is extra as last element cannot be detected */
IfxStart_Pin_Config IfxStart_PortConfig [MAX_CFG_PIN] =
{
    {
      &MODULE_P33,
      IFXSTART_PORT_PIN_6,
      (IfxPort_Mode)MODE_OUT  | MODE_OUT_PUSHPULL | MODE_OUT_GPIO,
      (IfxPort_PadDriver)PDR_CMOS | PDR_SG3,
      IfxPort_State_low
    } ,	
    {
      &MODULE_P33,
      IFXSTART_PORT_PIN_7,
      (IfxPort_Mode)MODE_OUT  | MODE_OUT_PUSHPULL | MODE_OUT_GPIO,
      (IfxPort_PadDriver)PDR_CMOS | PDR_SG3,
      IfxPort_State_low
    } ,	
    {
      &MODULE_P33,
      IFXSTART_PORT_PIN_8,
      (IfxPort_Mode)MODE_OUT  | MODE_OUT_PUSHPULL | MODE_OUT_GPIO,
      (IfxPort_PadDriver)PDR_CMOS | PDR_SG3,
      IfxPort_State_low
    } ,	
    {
      &MODULE_P33,
      IFXSTART_PORT_PIN_9,
      (IfxPort_Mode)MODE_OUT  | MODE_OUT_PUSHPULL | MODE_OUT_GPIO,
      (IfxPort_PadDriver)PDR_CMOS | PDR_SG3,
      IfxPort_State_low
    },
    {
      &MODULE_P33,
      IFXSTART_PORT_PIN_10,
      (IfxPort_Mode)MODE_OUT  | MODE_OUT_PUSHPULL | MODE_OUT_GPIO,
      (IfxPort_PadDriver)PDR_CMOS | PDR_SG3,
      IfxPort_State_low
    },
    {
      &MODULE_P33,
      IFXSTART_PORT_PIN_11,
      (IfxPort_Mode)MODE_OUT  | MODE_OUT_PUSHPULL | MODE_OUT_GPIO,
      (IfxPort_PadDriver)PDR_CMOS | PDR_SG3,
      IfxPort_State_low
    },
    {
      &MODULE_P33,
      IFXSTART_PORT_PIN_12,
      (IfxPort_Mode)MODE_OUT  | MODE_OUT_PUSHPULL | MODE_OUT_GPIO,
      (IfxPort_PadDriver)PDR_CMOS | PDR_SG3,
      IfxPort_State_low
    },
    {
      &MODULE_P33,
      IFXSTART_PORT_PIN_13,
      (IfxPort_Mode)MODE_OUT  | MODE_OUT_PUSHPULL | MODE_OUT_GPIO,
      (IfxPort_PadDriver)PDR_CMOS | PDR_SG3,
      IfxPort_State_low
    }
};

#ifdef __GNUC__
  #pragma section
#endif 

#if defined(__TASKING__)
   #pragma align restore
   #pragma section neardata restore
#endif
