/**
 * \file IfxMtu.c
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
#include "Ifx_Types.h"
#include "IfxMtu.h"
#include "IfxScuWdt.h"
#include "IfxMtu_Cfg.h"
#include "Ifx_Cfg.h"

/*lint -save -e923 */

/*****************************************************************************/
/*                           Function prototypes                             */
/*****************************************************************************/
IFX_INLINE void IfxMtu_lenableMbistShell(uint8 mbistSel);
IFX_INLINE void IfxMtu_ldisableMbistShell(uint8 mbistSel);

/*****************************************************************************/
/*                           Functions                                       */
/*****************************************************************************/

#if !defined TC2XX_A_Step

void Ifx_lenableMtu(void)
{
  register uint16 password ;
  register volatile uint32 index ;

  password = IfxScuWdt_getCpuWatchdogPassword( );
  IfxScuWdt_clearCpuEndinit(password) ;

  /* Enable the Module */
  MODULE_MTU.CLC.B.DISR = 0U ;
  #if (IFX_CFG_DEVICE != IFX_CFG_TC26X )
    MODULE_MTU.CLC.B.EDIS = 0U ;
  #endif

  for( index = 0U ; index < 1000U ; index ++  )
  {
    ;
  }

  IfxScuWdt_setCpuEndinit(password) ;
}

void Ifx_ldisableMtu(void)
{
  register uint16 password ;
  register volatile uint32 index ;

  password = IfxScuWdt_getCpuWatchdogPassword( );
  IfxScuWdt_clearCpuEndinit(password) ;

  /* Enable the Module */
  MODULE_MTU.CLC.B.DISR = 1U ;
  #if (IFX_CFG_DEVICE != IFX_CFG_TC26X )
    MODULE_MTU.CLC.B.EDIS = 0U ;
  #endif

  for( index = 0u ; index < 1000U ; index ++  )
  {
    ;
  }

  IfxScuWdt_setCpuEndinit(password) ;
}
#endif

/** \brief This method Non Destructive memory test. 
 *
 * \param (in) mbistSel -> MBIST controller number
 * \param (in) RangeSel -> Rannge Enable / Disable
 * \param (in) RangeAddrUp -> Upper Address for range register
 * \param (in) RangeAddrLow -> Lower Address for range register
 * \param (out)ErrorAddr -> Address where error address is returned 
 *
 * \return Test Fail / Success 
 *
 */
#if  (IFXMTU_NON_DES_TEST_USED == STD_ON)
uint8 IfxMtu_Non_Destructive_test
(
register uint8 mbistSel    ,register uint8 RangeSel ,
register uint8 RangeAddrUp ,register uint8 RangeAddrLow,
uint16 * ErrorAddr 
)
{
  register Ifx_MC* mc;
  uint8  retVal ; 
  register uint16 Range_Val ;
  register uint16 l_SEndInitPW; 
  
  Range_Val = ( ((uint16)(RangeSel << IFXMTU_RANGE_BIT)) | \
                ((uint16)(RangeAddrUp << IFXMTU_UP_ADDR_BIT)) | \
                RangeAddrLow) ;

  retVal = 0U;
  
  l_SEndInitPW = IfxScuWdt_getSafetyWatchdogPassword (); 
  IfxScuWdt_clearSafetyEndinit (l_SEndInitPW);

  IfxMtu_lenableMbistShell(mbistSel);

  /* Select the Controller */
  mc = (Ifx_MC *)((IFXMTU_MC0_ADDR + IFXMTU_CON_OFFSET * mbistSel));
 
  /* Select the Non destructive test */
  mc->CONFIG0.U = IFXMTU_NOND_NUMACCS |  IFXMTU_NOND_ACC;
  mc->CONFIG1.U = IFXMTU_NOND_TEST;

  /* Set the range register */
  mc->RANGE.U   = Range_Val ;
  
  /* Run the tests */
  mc->MCONTROL.U = ((0xf000U) |IFXMTU_FAILDMP_EN | \
                        IFXMTU_START_TEST); /* 0xf201 */
  
  /* puneetha IfxScuWdt_setSafetyEndinit (l_SEndInitPW); */

  /* Poll DONE  */
  while( !(mc->MSTATUS.U & IFXMTU_DONE))
  {
      
  }
  
  /* puneetha  IfxScuWdt_clearSafetyEndinit (l_SEndInitPW); */

  /* Check the Fail Status */
  /*if ((mc->MSTATUS.U & IFXMTU_FAIL) == IFXMTU_FAIL)*/
  if(mc->MSTATUS.B.FAIL)
  {
      /* Test has failed, check if any un correctable error */
      if (mc->ECCD.B.UERR)
      {	
        /* Read the Error tracking register and return saying test failed */
        *ErrorAddr = mc->ETRR[0U].U ;
        retVal = 1U;  	    
      }  	
  }/*if( mc->MSTATUS.U & IFXMTU_FAIL ) */
  
  mc->MCONTROL.U = 0U ;
  IfxMtu_ldisableMbistShell (mbistSel);

  IfxScuWdt_setSafetyEndinit (l_SEndInitPW);
  return(retVal);
}/* IfxMtu_Non_Destructive_test() */ 
#endif 
/* #if  (IFXMTU_NON_DES_TEST_USED == STD_ON) */


/** \brief This method initializes the RAM area 
 *
 * \param (in) mbistSel -> MBIST controller number
 * \param (in) InitData -> Data byte to initialize
 * \param (in) RangeSel -> Rannge Enable / Disable
 * \param (in) RangeAddrUp -> Upper Address for range register
 * \param (in) RangeAddrLow -> Lower Address for range register
 *
 * \return None
 *
 */
void IfxMtu_PerformAutoInit
(
 register  uint8 mbistSel ,  register   uint16 InitData,
 register  uint8 RangeSel ,  register   uint8 RangeAddrUp , register uint8 RangeAddrLow,
 register  uint8 eccData
)
{
  register Ifx_MC* mc;
  register uint16 range_val ;
  register uint16 l_SEndInitPW; 
  
  range_val = ( ((uint16)(RangeSel << IFXMTU_RANGE_BIT)) | \
                ((uint16)(RangeAddrUp << IFXMTU_UP_ADDR_BIT)) | \
                RangeAddrLow) ;
  
  l_SEndInitPW = IfxScuWdt_getSafetyWatchdogPassword ();   
  IfxScuWdt_clearSafetyEndinit (l_SEndInitPW);

  /* Select the Controller */
  mc = (Ifx_MC *)((IFXMTU_MC0_ADDR + IFXMTU_CON_OFFSET * mbistSel));
 
  IfxMtu_lenableMbistShell(mbistSel);
  #if !defined TC2XX_A_Step
    if( (mbistSel == IFXMTU_CPU0_DSPR) ||
        (mbistSel == IFXMTU_CPU1_DSPR) ||
        (mbistSel == IFXMTU_CPU1_DSPR)
       )
    {
     mc->RDBFL[0].U = (uint16)(InitData);
     mc->RDBFL[1].U = (uint16)((InitData << 6U) | eccData);
     mc->RDBFL[2].U = (uint16)((( (InitData << 12U) | (((InitData >> 10U) & 0x003FU) | eccData << 6) )));
     mc->RDBFL[3].U = (uint16)((((InitData >> 4U) & 0x0fffU)) | eccData << 12);
     mc->RDBFL[4].U = (uint16)(((InitData << 2U)) |  eccData >> 4) ;
     mc->RDBFL[5].U = (uint16)(((InitData & 0x00ffU) << 8U) | ((InitData >> 14U) | eccData << 2));
     mc->RDBFL[6].U = (uint16)(( ((InitData >> 8U) |eccData << 8)|  (InitData & 0x003U) << 14U));
     mc->RDBFL[7].U = (uint16)(((InitData >> 2U)) | eccData << 14);
     mc->RDBFL[8].U = (uint16)(((InitData << 4U))  | eccData >> 2);
     mc->RDBFL[9].U = (uint16)(((InitData << 10U) /* & 0xfc00U */) |  (((InitData >> 12U) | eccData << 4)/*& 0x000fU*/));
     mc->RDBFL[10].U = (uint16)((InitData >> 6U) |eccData << 10);
    }
    /*puneetha check from here */    
    else  if( (mbistSel == IFXMTU_CPU0_PSPR) ||
            (mbistSel == IFXMTU_CPU1_PSPR)
           )
    {
         mc->RDBFL[0U].U = (uint16)(InitData);
         mc->RDBFL[1U].U = (uint16)(InitData);
         mc->RDBFL[2U].U = (uint16)((InitData << 8U) | 3U);
         mc->RDBFL[3U].U = (uint16)(( (InitData >> 8U) | (InitData << 8U)));
         mc->RDBFL[4U].U = (uint16)((InitData >> 8U) | 3U << 8U);
    }
    else  if(mbistSel == IFXMTU_CPU2_PSPR)
    {
        mc->RDBFL[0U].U = InitData;
        mc->RDBFL[1U].U = InitData;
        mc->RDBFL[2U].U = InitData;
        mc->RDBFL[3U].U = InitData;
        mc->RDBFL[4U].U = (uint16)((InitData << 8U));
        mc->RDBFL[5U].U = (uint16)(( (InitData >> 8U) | (InitData << 8U) ));
        mc->RDBFL[6U].U = (uint16)(( (InitData >> 8U) |  (InitData << 8U)));
        mc->RDBFL[7U].U = (uint16)(( (InitData >> 8U) | (InitData << 8U)));
        mc->RDBFL[4U].U = (uint16)((InitData >> 8U));
    }
    else
    {
        mc->RDBFL[0].U = InitData;
    }
    /*puneetha check till here */
  #else
    if( (mbistSel == IFXMTU_CPU0_DSPR) ||
        (mbistSel == IFXMTU_CPU1_DSPR) ||
        (mbistSel == IFXMTU_CPU1_DSPR)
       )
    {
     mc->RDBFL[0].U = (uint16)(InitData);
     mc->RDBFL[1].U = (uint16)(InitData << 6U);
     mc->RDBFL[2].U = (uint16)((( (InitData << 12U) | ((InitData >> 10U) & 0x003FU))));
     mc->RDBFL[3].U = (uint16)(((InitData >> 4U) & 0x0fffU));
     mc->RDBFL[4].U = (uint16)((InitData << 2U));
     mc->RDBFL[5].U = (uint16)(((InitData & 0x00ffU) << 8U)| (InitData >> 14U));
     mc->RDBFL[6].U = (uint16)(((InitData >> 8U) |  (InitData &0x003U) << 14U));
     mc->RDBFL[7].U = (uint16)((InitData >> 2U));
     mc->RDBFL[8].U = (uint16)((InitData << 4U));
     mc->RDBFL[9].U = (uint16)(((InitData << 10U) /* & 0xfc00U */) |  ((InitData >> 12U) /*& 0x000fU*/));
     mc->RDBFL[10].U = (uint16)((InitData >> 6U));
    }
    else  if( (mbistSel == IFXMTU_CPU0_PSPR) ||
            (mbistSel == IFXMTU_CPU1_PSPR)
           )
    {
         mc->RDBFL[0U].U = (uint16)(InitData);
         mc->RDBFL[1U].U = (uint16)(InitData);
         mc->RDBFL[2U].U = (uint16)((InitData << 8U));
         mc->RDBFL[3U].U = (uint16)(( (InitData >> 8U) | (InitData << 8U)));
         mc->RDBFL[4U].U = (uint16)((InitData >> 8U));
    }
    else  if(mbistSel == IFXMTU_CPU2_PSPR)
    {
        mc->RDBFL[0U].U = InitData;
        mc->RDBFL[1U].U = InitData;
        mc->RDBFL[2U].U = InitData;
        mc->RDBFL[3U].U = InitData;
        mc->RDBFL[4U].U = (uint16)((InitData << 8U));
        mc->RDBFL[5U].U = (uint16)(( (InitData >> 8U) | (InitData << 8U) ));
        mc->RDBFL[6U].U = (uint16)(( (InitData >> 8U) |  (InitData << 8U)));
        mc->RDBFL[7U].U = (uint16)(( (InitData >> 8U) | (InitData << 8U)));
        mc->RDBFL[4U].U = (uint16)((InitData >> 8U));
    }
    else
    {
        mc->RDBFL[0].U = InitData;
    }
  #endif 
     /* #if !defined TC2XX_A_Step  */
  mc->RANGE.U   = range_val ;
  /* Start fill operation */
  /* START = DINIT = 1 */
  mc->MCONTROL.U = 0x11U ;
  mc->MCONTROL.B.START = 0U;  
 /* puneetha IfxScuWdt_setSafetyEndinit (l_SEndInitPW);*/

  /* Wait for the end of the fil operation */
  while( !(mc->MSTATUS.U & 0x1U ))
  {
      
  }
 /* puneetha  IfxScuWdt_clearSafetyEndinit (l_SEndInitPW); */
  /* Clear regsiter */
  
  mc->RDBFL[0U].U = 0U;
  mc->MCONTROL.U = 0U;
  IfxMtu_ldisableMbistShell(mbistSel) ;


  IfxScuWdt_setSafetyEndinit (l_SEndInitPW);
}
/** \brief This method enables the memory controller 
 *
 * \param (in) mbistSel 
 *
 * \return None
 *
 */
IFX_INLINE  void IfxMtu_lenableMbistShell(register volatile uint8 mbistSel)
{  
  /* Enable the Memory Controllers */
  register uint32 MselVal ;  
    
  /* Check the MEMTest Controller Number and enable */
  if(mbistSel < IFXMTU_MC0)
  {
      MselVal = (1U << mbistSel) ;	
    MTU_MEMTEST0.U = MselVal;
    
    /* wait until MBISTS is are ready */
    while(!(MTU_MEMTEST0.U & MselVal) )
    {
        
    }    
  }
  else if(mbistSel < IFXMTU_MC1)
  {	
      MselVal = (1U << (mbistSel - IFXMTU_MC0)); 
    MTU_MEMTEST1.U = MselVal ;
    /* wait until MBISTS is are ready */
    while(!(MTU_MEMTEST1.U & MselVal))
    {
        
    }    
  }
  else if(mbistSel < IFXMTU_MAXIMUM_NB_MBISTS) 
  {	
      MselVal = (1U << (mbistSel - IFXMTU_MC1));
    MTU_MEMTEST2.U = MselVal ;
    /* wait until MBISTS is are ready */
    while(!(MTU_MEMTEST2.U & MselVal))
    {
        
    }
  }
}

/** \brief This method disables the memory controller 
 *
 * \param (in) mbistSel 
 *
 * \return None
 *
 */
IFX_INLINE void IfxMtu_ldisableMbistShell(register uint8 mbistSel)
{
    register uint32 MselVal ;  
        
  /* Disable the memory controllers */
  if(mbistSel < IFXMTU_MC0)
  {
      MselVal = (1U << mbistSel);
      MTU_MEMTEST0.U &= (~MselVal);
      /* wait until MBISTS is are ready */
      while(MTU_MEMTEST0.U & MselVal) 
      {
          
      }
  }
  else if(mbistSel < IFXMTU_MC1)
  {
        MselVal = (1U << (mbistSel - IFXMTU_MC0)) ;
      MTU_MEMTEST1.U &= ~MselVal;
      while (MTU_MEMTEST1.U & MselVal) 
      {
          
      }
  }
  else if(mbistSel < IFXMTU_MAXIMUM_NB_MBISTS)
  {
        MselVal = (1U << (mbistSel - IFXMTU_MC1));
      MTU_MEMTEST2.U &= (~MselVal); 
      while (MTU_MEMTEST2.U & MselVal) 
      {
          
      }
  }
}
/*lint -restore */
