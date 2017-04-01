/**
 * \file Ifx_preInitHook.h
 * \brief This file contains hook function for the RAM tests.
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
 * $Revision: 001 $
 * $Date: 24-05-2013 12:09 +0530 $
 *
 * \defgroup Ifx Infineon Software
 * \defgroup Ifx_Lld Infineon Low Level Drivers' Software
 * \ingroup I
 */ 
#ifndef IFX_PREINITHOOK_H_
#define IFX_PREINITHOOK_H_

/******************************************************************************/
/*                           Includes                                         */
/******************************************************************************/
#include "IfxMtu.h"
#include "IfxMtu_cfg.h"
#include "IfxScuRcu.h"
#include "IfxCpu_cfg.h"
#include "IfxCpu_CStart_Cfg.h"
/******************************************************************************/
/*                           Macros                                           */
/******************************************************************************/

/** \brief Configuration for pre initialization hook function.
 *
 */
#define  IFXCSTART0_EMEM_LOCK1            (0x2U)
#define  IFXCSTART0_EMEM_LOCK2            (0x6U)
#define  IFXCSTART0_EMEM_LOCK3            (0xEU)
#define  IFXSCUWDT_PWD                    (0x000000F1U)
#define  IFXSCUWDT_ENDINIT_CLR            (0x000000F2U)
#define  IFXSCUWDT_ENDINIT_SET            (0x000000F3U)

/*lint -e923 */
/*lint -e788 */
/******************************************************************************/
/*                           Enum                                             */
/******************************************************************************/

/******************************************************************************/
/*                       Function prototypes                                  */
/******************************************************************************/

/******************************************************************************/
/*                         Inline Functions                                   */
/******************************************************************************/
/** \brief API to Run the ED memory initializations
 *
 * \param None
 *
 * \return None
 */
IFX_INLINE void IfxEdInitHook(void)
{
  #if defined IFXSTART_ED_DEVICE_SUPPORTED
    /* chck for ED device and ensure adequate debugging 
       and tracing capabilities from here on
    */   
    if (SCU_CHIPID.B.EEA)
    {    	
      /* first we enable and unlock the emem */
      EMEM_CLC.U = 0U;
      /* wait a cycle to clock is activ */
      EMEM_CLC.U;                     
      /* apply unlock sequence */
      EMEM_SBRCTR.U = IFXCSTART0_EMEM_LOCK1; 
      EMEM_SBRCTR.U = IFXCSTART0_EMEM_LOCK2;
      EMEM_SBRCTR.U = IFXCSTART0_EMEM_LOCK3;
      /* wait a cycle to become EMEM unlocked */
      EMEM_SBRCTR.U;           
      /* we enable also the MBISTS for the ED part later  */
    }
  #endif     
  /* #if defined IFXSTART_ED_DEVICE_SUPPORTED */
}  

/** \brief API to run the initial RAM tests
 *
 * \param MbitSel: MBIST controller Number 
 * \param Seg_Start: Memory Range Start Address
 * \param Seg_End:   Memory Range end Address
 * \param RamTst_Type:  RAM Test Type Checker board / March U
 * \param Ram_Clear:  RAM Segment needs to be cleared or not
 *
 * \return None
 */
IFX_INLINE void IfxInitRamtstHook(uint8  MbitSel , 
                                  uint16 Seg_Start , 
                                  uint16 Seg_End , 
                                  uint8  RamTst_Type ,
                                  uint8  Ram_Clear 
                                 )
{
    register Ifx_MC *mc;
  register uint16 wdtPassword  ;  

  /* first we test the minimal memories
    - cache + csa + stack + global data (START)    
  */   
  mc = (Ifx_MC *) ((IFXMTU_MC0_ADDR) + IFXMTU_CON_OFFSET * MbitSel); 
  wdtPassword = IfxScuWdt_getSafetyWatchdogPasswordInline ( );
  
  IfxScuWdt_clearSafetyEndinitInline (wdtPassword) ;
  /* Enable the Memory Controller */
  MTU_MEMTEST0.U = (1U << MbitSel);
  
  /* wait until MBISTS is are ready */
  while(!(MTU_MEMTEST0.U & (1U << MbitSel)) )
  {
      ;
  }

  /* Check if memory segment needs to be initialized */
  if(1U == Ram_Clear)
  {	
    /* Data which will be written ,cstart init data is zero always  */
    mc->RDBFL[0].U = 0U;
  
    /* Enable the range register */
    mc->RANGE.U   =( (1U << IFXMTU_RANGE_BIT) | \
                     ((uint16)(Seg_End << 7U)) | \
                     (Seg_Start)
                   );
    /* Start fill operation */
    /* START = DINIT = 1 */
    mc->MCONTROL.U = 0x0011U;
    /* Wait for the end of the fil operation */
    while( !(mc->MSTATUS.U & IFXMTU_DONE ))
    {
        ;
    }
  }  
  
  MTU_MEMTEST0.U &= ~(1U << MbitSel);
  /* wait until MBISTS is are ready */
  while (MTU_MEMTEST0.U & (1U << MbitSel))
  {
      ;
  }    
  /* SET ENDINIT */
  IfxScuWdt_setSafetyEndinitInline (wdtPassword);  
}  

/** \brief API to run the inititializations before the Cstart
 *
 * \param cpu Resource index of the CPU.
 *
 * \return None
 */    
IFX_INLINE void mySysPreInitHook (IfxCpu_ResourceCpu cpu)
{
  /* todo: enable the Start up Memory tests */
#if 0
  switch (cpu)
  {
    case IfxCpu_ResourceCpu_0:
    {
          /* Disable the Safety Watchdog Timer here */
          IfxScuWdt_disableSafetyWatchdogInline();

          /* Disable Cpu0 watchdog     */
          IfxScuWdt_disableCpu0WatchdogInline( );

      /* Ed Initializations */
      #if defined IFXSTART_ED_DEVICE_SUPPORTED
        IfxEdInitHook( );
      #endif     
         /* #if defined IFXSTART_ED_DEVICE_SUPPORTED */
      /* First enable the Memory Controller */
      password =  IfxScuWdt_getCpuWatchdogPasswordInline(&MODULE_SCU.WDTCPU[0]) ;
      IfxScuWdt_clearCpuEndinitInline (&MODULE_SCU.WDTCPU[0], password);
      MODULE_MTU.CLC.B.DISR = 0U ;
      MODULE_MTU.CLC.B.EDIS = 0U ;
      IfxScuWdt_setCpuEndinitInline (&MODULE_SCU.WDTCPU[0], password);

        /* Segment 0 test is defined */
        #if defined IFXCSTART0_INIT_RAMTEST_SEG_0
          IfxInitRamtstHook(
                            IFXCSTART0_INIT_RAMTEST_SEG_0_MSEL,
                            IFXCSTART0_INIT_RAMTEST_SEG_0_START,
                            IFXCSTART0_INIT_RAMTEST_SEG_0_END,
                            IFXCSTART0_INIT_RAMTEST_SEG_0_TYPE,
                            IFXCSTART0_INIT_RAMTEST_SEG_0_CLR
                           );
        #endif 
           /* #if defined IFXCSTART0_INIT_RAMTEST_SEG_0 */ 
           
        /* Segment 1 test is defined */
        #if defined IFXCSTART0_INIT_RAMTEST_SEG_1
          IfxInitRamtstHook(
                            IFXCSTART0_INIT_RAMTEST_SEG_1_MSEL,
                            IFXCSTART0_INIT_RAMTEST_SEG_1_START,
                            IFXCSTART0_INIT_RAMTEST_SEG_1_END,
                            IFXCSTART0_INIT_RAMTEST_SEG_1_TYPE,
                            IFXCSTART0_INIT_RAMTEST_SEG_1_CLR
                           );
        #endif 
           /* #if defined IFXCSTART0_INIT_RAMTEST_SEG_1 */            

        /* Segment 2 test is defined */
        #if defined IFXCSTART0_INIT_RAMTEST_SEG_2
          IfxInitRamtstHook(
                            IFXCSTART0_INIT_RAMTEST_SEG_2_MSEL,
                            IFXCSTART0_INIT_RAMTEST_SEG_2_START,
                            IFXCSTART0_INIT_RAMTEST_SEG_2_END,
                            IFXCSTART0_INIT_RAMTEST_SEG_2_TYPE,
                            IFXCSTART0_INIT_RAMTEST_SEG_2_CLR
                           );
        #endif 
           /* #if defined IFXCSTART0_INIT_RAMTEST_SEG_2 */            
           
        /* Segment 3 test is defined */
        #if defined IFXCSTART0_INIT_RAMTEST_SEG_3
          IfxInitRamtstHook(
                            IFXCSTART0_INIT_RAMTEST_SEG_3_MSEL,
                            IFXCSTART0_INIT_RAMTEST_SEG_3_START,
                            IFXCSTART0_INIT_RAMTEST_SEG_3_END,
                            IFXCSTART0_INIT_RAMTEST_SEG_3_TYPE,
                            IFXCSTART0_INIT_RAMTEST_SEG_3_CLR
                           );
        #endif 
           /* #if defined IFXCSTART0_INIT_RAMTEST_SEG_3 */                       
      break;
    }
    case IfxCpu_ResourceCpu_1:
    {
        /* Segment 0 test is defined */
        #if defined IFXCSTART1_INIT_RAMTEST_SEG_0
          IfxInitRamtstHook(
                            IFXCSTART1_INIT_RAMTEST_SEG_0_MSEL,
                            IFXCSTART1_INIT_RAMTEST_SEG_0_START,
                            IFXCSTART1_INIT_RAMTEST_SEG_0_END,
                            IFXCSTART1_INIT_RAMTEST_SEG_0_TYPE,
                            IFXCSTART1_INIT_RAMTEST_SEG_0_CLR
                           );
        #endif 
           /* #if defined IFXCSTART1_INIT_RAMTEST_SEG_0 */ 
           
        /* Segment 1 test is defined */
        #if defined IFXCSTART1_INIT_RAMTEST_SEG_1
          IfxInitRamtstHook(
                            IFXCSTART1_INIT_RAMTEST_SEG_1_MSEL,
                            IFXCSTART1_INIT_RAMTEST_SEG_1_START,
                            IFXCSTART1_INIT_RAMTEST_SEG_1_END,
                            IFXCSTART1_INIT_RAMTEST_SEG_1_TYPE,
                            IFXCSTART1_INIT_RAMTEST_SEG_1_CLR
                           );
        #endif 
           /* #if defined IFXCSTART1_INIT_RAMTEST_SEG_1 */            

        /* Segment 2 test is defined */
        #if defined IFXCSTART1_INIT_RAMTEST_SEG_2
          IfxInitRamtstHook(
                            IFXCSTART1_INIT_RAMTEST_SEG_2_MSEL,
                            IFXCSTART1_INIT_RAMTEST_SEG_2_START,
                            IFXCSTART1_INIT_RAMTEST_SEG_2_END,
                            IFXCSTART1_INIT_RAMTEST_SEG_2_TYPE,
                            IFXCSTART1_INIT_RAMTEST_SEG_2_CLR
                           );
        #endif 
           /* #if defined IFXCSTART1_INIT_RAMTEST_SEG_2 */            
           
        /* Segment 3 test is defined */
        #if defined IFXCSTART1_INIT_RAMTEST_SEG_3
          IfxInitRamtstHook(
                            IFXCSTART1_INIT_RAMTEST_SEG_3_MSEL,
                            IFXCSTART1_INIT_RAMTEST_SEG_3_START,
                            IFXCSTART1_INIT_RAMTEST_SEG_3_END,
                            IFXCSTART1_INIT_RAMTEST_SEG_3_TYPE,
                            IFXCSTART1_INIT_RAMTEST_SEG_3_CLR
                           );
        #endif 
           /* #if defined IFXCSTART1_INIT_RAMTEST_SEG_3 */                       
      break;
    }
    case IfxCpu_ResourceCpu_2:
    {
        /* Segment 0 test is defined */
        #if defined IFXCSTART2_INIT_RAMTEST_SEG_0
          IfxInitRamtstHook(
                            IFXCSTART2_INIT_RAMTEST_SEG_0_MSEL,
                            IFXCSTART2_INIT_RAMTEST_SEG_0_START,
                            IFXCSTART2_INIT_RAMTEST_SEG_0_END,
                            IFXCSTART2_INIT_RAMTEST_SEG_0_TYPE,
                            IFXCSTART2_INIT_RAMTEST_SEG_0_CLR
                           );
        #endif 
           /* #if defined IFXCSTART2_INIT_RAMTEST_SEG_0 */ 
           
        /* Segment 1 test is defined */
        #if defined IFXCSTART2_INIT_RAMTEST_SEG_1
          IfxInitRamtstHook(
                            IFXCSTART2_INIT_RAMTEST_SEG_1_MSEL,
                            IFXCSTART2_INIT_RAMTEST_SEG_1_START,
                            IFXCSTART2_INIT_RAMTEST_SEG_1_END,
                            IFXCSTART2_INIT_RAMTEST_SEG_1_TYPE,
                            IFXCSTART2_INIT_RAMTEST_SEG_1_CLR
                           );
        #endif 
           /* #if defined IFXCSTART2_INIT_RAMTEST_SEG_1 */            

        /* Segment 2 test is defined */
        #if defined IFXCSTART2_INIT_RAMTEST_SEG_2
          IfxInitRamtstHook(
                            IFXCSTART2_INIT_RAMTEST_SEG_2_MSEL,
                            IFXCSTART2_INIT_RAMTEST_SEG_2_START,
                            IFXCSTART2_INIT_RAMTEST_SEG_2_END,
                            IFXCSTART2_INIT_RAMTEST_SEG_2_TYPE,
                            IFXCSTART2_INIT_RAMTEST_SEG_2_CLR
                           );
        #endif 
           /* #if defined IFXCSTART2_INIT_RAMTEST_SEG_2 */            
           
        /* Segment 3 test is defined */
        #if defined IFXCSTART2_INIT_RAMTEST_SEG_3
          IfxInitRamtstHook(
                            IFXCSTART2_INIT_RAMTEST_SEG_3_MSEL,
                            IFXCSTART2_INIT_RAMTEST_SEG_3_START,
                            IFXCSTART2_INIT_RAMTEST_SEG_3_END,
                            IFXCSTART2_INIT_RAMTEST_SEG_3_TYPE,
                            IFXCSTART2_INIT_RAMTEST_SEG_3_CLR
                           );
        #endif 
           /* #if defined IFXCSTART2_INIT_RAMTEST_SEG_3 */                       
    }
    default:
    {
      break;
    }
  }
#endif
  /* #if 0 */
}
/*lint -restore */
#endif 
  /* IFX_PREINITHOOK_H_ */
  
