/**
 * \file IfxScuRcu.c
 * \brief SCU Reset control functionality.
 * \copyright Copyright (c) 2012 Infineon Technologies AG. All rights reserved.
 *
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

/******************************************************************************/
#include "Ifx_Types.h"
#include "Ifx_Cfg.h"
#include "IfxScuWdt.h"
#include "IfxScuRcu.h"
#include "IfxCpu_cfg.h"


IfxScuRcu_ResetCode  Reset_Code ; 
static uint16 IfxScu_lGetSmuAlaramStatus(void);

/** \brief Evaluate the Reset Functionality
 *
 * Evaluates the Reset Status register b reading the 
 * RSTSTAT register
 *
 * \param None
 *
 * \return Reset Evaluation Value abcdef(Reset Type , Trigger , Reason).
 */
IfxScuRcu_ResetCode IfxScu_ResetRamEval(void)
{
  uint32 ResetReasonRaw;
  uint32 ResetCpuState;
  uint32 CPUSafeState;
  uint32 ResetCon ;
 
  /* check the CSSx from SCU_RSTCON2, evaluate the information */
  CPUSafeState  = IFXSCURCU_CPU_NOT_IN_SAFE_STATE; 
  ResetCpuState = ((uint32)SCU_RSTCON2.U & IFXSCURCU_CPU_SAFE_STATE_MASK);
  ResetCpuState = (ResetCpuState >> IFXSCURCU_CPU_SAFE_STATE_POS) ;   
  
  /* Verify the status of CSSx bits depending on how many CPU available */
  #if (IFXCPU_COUNT == 1U)  /* if(1U == IFXCPU_COUNT) */  
      /* if one CPU verify for CPU0 only */
      if(ResetCpuState == IFXSCURCU_CPU0_SAFE_STATE_MASK)
      {	
        CPUSafeState = IFXSCURCU_CPU_IN_SAFE_STATE; 
      }    
  #elif (IFXCPU_COUNT == 2U)  /* else if(2U == IFXCPU_COUNT)*/
      /* if 2 CPU verify for CPU0 and CPU1 only */
      if(ResetCpuState == IFXSCURCU_CPU0_1_SAFE_STATE_MASK)
      {	
        CPUSafeState = IFXSCURCU_CPU_IN_SAFE_STATE; 
      }  
  #else /*else */ /* Check CPU0  CPU1 , CPU2 */  	
      if(ResetCpuState == IFXSCURCU_CPU0_1_2_SAFE_STATE_MASK)
      {	
        CPUSafeState = IFXSCURCU_CPU_IN_SAFE_STATE; 
      }  
  #endif 
  Reset_Code.ResetType    = (uint8)(CPUSafeState) ;
  Reset_Code.ResetReason  = IFXSCURCU_RESET_REASON_DEFAULT ;  
  ResetCon                = (uint32)(SCU_RSTCON.U );
  
  /* Extract raw reset reason from the status register */
  ResetReasonRaw = ((uint32)(SCU_RSTSTAT.U & IFXSCURCU_RESET_REASON_MASK));
  
  switch(ResetReasonRaw)
  {
    case IFXSCURCU_RAW_ESR0_RESET:
    {
        /* ESR0  trigger and get the type by reading the RSTCON.ESR0 bits */
      Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_esr0;
      /*lint -e835 */ResetCon     = ((ResetCon >> IFXSCURCU_ESR0_MASK) & \
                       IFXSCURCU_RESET_TRIGGER_MASK);   
      if(IFXSCURCU_APPLICATION_RESET == ResetCon)
      {	
        Reset_Code.ResetType    |= (uint8)((uint8)IfxScuRcu_ResetType_application << 1U);
      }  
      else
      {	
        Reset_Code.ResetType    |= (uint8)((uint8)IfxScuRcu_ResetType_system << 1U);      	  
      }  
      break;
    }
    case IFXSCURCU_RAW_ESR1_RESET:
    {
        /* ESR1  trigger and get the type by reading the RSTCON.ESR1 bits */    	
      Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_esr1;
      
      ResetCon     = ((ResetCon >> IFXSCURCU_ESR1_MASK) & \
                        IFXSCURCU_RESET_TRIGGER_MASK);      
      if(IFXSCURCU_APPLICATION_RESET == ResetCon)
      {	
        Reset_Code.ResetType    |= (uint8)((uint8)IfxScuRcu_ResetType_application << 1U);
      }  
      else
      {	
        Reset_Code.ResetType    |= (uint8)((uint8)IfxScuRcu_ResetType_system << 1U);      	  
      }  
      break;
    }
    case IFXSCURCU_RAW_SMU_RESET:
    {
        /* SMU trigger and get the type by reading the RSTCON.SMU bits */    	
      Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_smu;
      
      ResetCon     = ((ResetCon >> IFXSCURCU_SMU_MASK) & \
                       IFXSCURCU_RESET_TRIGGER_MASK);      
      if(IFXSCURCU_APPLICATION_RESET == ResetCon)
      {	
        Reset_Code.ResetType    |= (uint8)((uint8)IfxScuRcu_ResetType_application << 1U);
      }  
      else
      {	
        Reset_Code.ResetType    |= (uint8)((uint8)IfxScuRcu_ResetType_system << 1U);      	  
      }  
      /* Get the reset Reason, What value is not clear needs clarification
         update this section after discussions
       */
      Reset_Code.ResetReason  = IfxScu_lGetSmuAlaramStatus( );
      break;
    }
    case IFXSCURCU_RAW_SW_RESET:
    {
        /* SOFTWARE RESET  trigger */ 
      Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_sw;
      
      /* Get the type by reading the RSTCON.SW bits */    	
      ResetCon     = ((ResetCon >> IFXSCURCU_SW_MASK) & \
                       IFXSCURCU_RESET_TRIGGER_MASK);      
      if(IFXSCURCU_APPLICATION_RESET == ResetCon)
      {	
        Reset_Code.ResetType    |= (uint8)((uint8)IfxScuRcu_ResetType_application << 1U);
      }  
      else
      {	
        Reset_Code.ResetType    |= (uint8)((uint8)IfxScuRcu_ResetType_system << 1U);      	  
      }       
      /* Get the reset Reason by reading the USR_INFO from RSTCON2 */
      Reset_Code.ResetReason = ((uint32)(SCU_RSTCON2.U & IFXSCURCU_USRINFO_MASK) >> 16U);
      break;
    }
    
    case IFXSCURCU_RAW_STM0_RESET:
    {
        /* STM0 is the reset trigger */
      Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_stm0;
      
      /* Get the type by reading the RSTCON.STM0 bits */    	
      ResetCon     = ((ResetCon >> IFXSCURCU_STM0_MASK) & \
                       IFXSCURCU_RESET_TRIGGER_MASK);      
      if(IFXSCURCU_APPLICATION_RESET == ResetCon)
      {	
        Reset_Code.ResetType    |= (uint8)((uint8)IfxScuRcu_ResetType_application << 1U);
      }  
      else
      {	
        Reset_Code.ResetType    |= (uint8)((uint8)IfxScuRcu_ResetType_system << 1U);      	  
      }       
      break;
    }
    
    case IFXSCURCU_RAW_STM1_RESET:
    {
        /* STM1 is the reset trigger */
      Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_stm1;
      
      /* Get the type by reading the RSTCON.STM1 bits */ 
      ResetCon     = ((ResetCon >> IFXSCURCU_STM1_MASK) & \
                       IFXSCURCU_RESET_TRIGGER_MASK);           
      if(IFXSCURCU_APPLICATION_RESET == ResetCon)
      {	
        Reset_Code.ResetType    |= (uint8)((uint8)IfxScuRcu_ResetType_application << 1U);
      }  
      else
      {	
        Reset_Code.ResetType    |= (uint8)((uint8)IfxScuRcu_ResetType_system << 1U);      	  
      }       

      break;
    }
    
    case IFXSCURCU_RAW_STM2_RESET:
    {
        /* STM2 is the reset trigger */
      Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_stm2;
      
      /* Get the type by reading the RSTCON.STM2 bits */    	
      ResetCon     = ((ResetCon >> IFXSCURCU_STM2_MASK) & \
                       IFXSCURCU_RESET_TRIGGER_MASK);      
      if(IFXSCURCU_APPLICATION_RESET == ResetCon)
      {	
        Reset_Code.ResetType    |= (uint8)((uint8)IfxScuRcu_ResetType_application << 1U);
      }  
      else
      {	
        Reset_Code.ResetType    |= (uint8)((uint8)IfxScuRcu_ResetType_system << 1U);      	  
      }       
      break;
    }    
    
    case IFXSCURCU_RAW_POWER_ON_RESET:
    {
        /* Power on Reset */
      Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_porst;
      /* Warm reset */
      Reset_Code.ResetType   |= (uint8)((uint8)IfxScuRcu_ResetType_warmpoweron << 1U);
      break;
    }
    
    case IFXSCURCU_RAW_CB0_RESET:
    {
      Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_cb0;
      Reset_Code.ResetType   |= (uint8)((uint8)IfxScuRcu_ResetType_system << 1U);
      break;
    }
    
    case IFXSCURCU_RAW_CB1_RESET:
    {
      Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_cb1;
      Reset_Code.ResetType   |= (uint8)((uint8)IfxScuRcu_ResetType_debug << 1U);
      break;
    }
    
    case IFXSCURCU_RAW_CB3_RESET:
    {
      Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_cb3;
      Reset_Code.ResetType   |= (uint8)((uint8)IfxScuRcu_ResetType_application << 1U);
      break;
    }
    
    #if !defined TC2XX_A_Step
      case IFXSCURCU_RAW_TP_RESET:
      {
        Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_tp;
        Reset_Code.ResetType   |= (uint8)((uint8)IfxScuRcu_ResetType_application << 1U);
        break;
      }
      
      case IFXSCURCU_RAW_TCU_RESET:
      {
        Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_tcu;
        Reset_Code.ResetType   |= (uint8)((uint8)IfxScuRcu_ResetType_system << 1U);
        break;
      }
    #endif 
       /* #if !defined TC2XX_A_Step */
       
    case IFXSCURCU_RAW_EVR13_RESET:
    {
      Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_evr13;
      Reset_Code.ResetType   |= (uint8)((uint8)IfxScuRcu_ResetType_coldpoweron << 1U);
      break;
    }
    
    case IFXSCURCU_RAW_EVR33_RESET:
    {
      Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_evr33;
      Reset_Code.ResetType   |= (uint8)((uint8)IfxScuRcu_ResetType_coldpoweron << 1U);
      break;
    }
            
    case IFXSCURCU_RAW_SUPPLY_WDOG_RESET:
    {
      Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_swd;
      Reset_Code.ResetType   |= (uint8)((uint8)IfxScuRcu_ResetType_coldpoweron << 1U);
      break;
    }
    
    #if !defined TC2XX_A_Step
      case IFXSCURCU_RAW_HSM_SYS_RESET:
      {
        Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_hsms;
        Reset_Code.ResetType   |= (uint8)((uint8)IfxScuRcu_ResetType_system << 1U);            	
        break;
      }	
      
      case IFXSCURCU_RAW_HSM_APP_RESET: 
      {
        Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_hsma;
        Reset_Code.ResetType   |= (uint8)((uint8)IfxScuRcu_ResetType_application << 1U);            	
        break;      	
      }	
          
      case IFXSCURCU_RAW_STBYR_RESET:
      {
        Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_stbyr;
        Reset_Code.ResetType   |= (uint8)((uint8)IfxScuRcu_ResetType_coldpoweron << 1U);      
        break;
      }
    #endif 
       /* #if !defined TC2XX_A_Step */
    default:
    {
      /* if none of the above match, check if many bits are set */
      if(ResetReasonRaw)
      {
        if((SCU_RSTSTAT.B.EVR13) ||(SCU_RSTSTAT.B.EVR33) || (SCU_RSTSTAT.B.SWD))
        {
             Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_evr13;
          Reset_Code.ResetType   |= (uint8)((uint8)IfxScuRcu_ResetType_coldpoweron << 1U);
        }
        else if (SCU_RSTSTAT.B.PORST)
        {
          Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_porst;
          Reset_Code.ResetType    |= (uint8)((uint8)IfxScuRcu_ResetType_warmpoweron << 1U);
        }
        else
        {
          Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_undefined;
          Reset_Code.ResetType   |= (uint8)((uint8)IfxScuRcu_ResetType_undefined << 1U);
        }
      }
      else /* Un-defined state */
      {
        Reset_Code.ResetTrigger = (uint8)IfxScuRcu_Trigger_undefined;
        /* Warm reset */
        Reset_Code.ResetType   |= (uint8)((uint8)IfxScuRcu_ResetType_undefined << 1U);
      }
      break;
    }
  }
  /* Return the computed value which is user friendly */
  return(Reset_Code); 
} /* End of IfxScu_ResetRamEval() */

/** \brief This method clears the Cold Reset Status
 *
 * \param None
 *
 * \return None
 *
 */
void IfxScuRcu_ClrCPorstStatus(void)
{
  uint16 l_SEndInitPW; 
  
  l_SEndInitPW = IfxScuWdt_getSafetyWatchdogPassword ();  
    IfxScuWdt_clearSafetyEndinit(l_SEndInitPW);	
  /* Clear Cold PORST */
  SCU_RSTCON2.B.CLRC = 1U;
  IfxScuWdt_setSafetyEndinit(l_SEndInitPW);
}
/** \brief This method gets the Alarm Number which has done the reset. 
 *
 * \param None
 *
 * \return Alarm Number which has done the reset (ResetReason)
 *
 */     
static uint16  IfxScu_lGetSmuAlaramStatus(void)
{
    uint32  Value ;
    uint16  ResetReason ;
    uint8   loop ;
    uint8   retVal ;
    
    ResetReason = 0U;
    retVal = 0U ;
    
  /* Check for AD0 : bit 0 - 31 */		
    for(loop = 0U ; loop < 32U ; loop ++ )
    {
        /* check from 0 till 31 */
        if( (IFXSMU_AD0_RST_MASK >> loop) & 0x1U)
        {
            /* Get the bit value */
            Value = ( (SCU_SMU_AD0.U >> loop) & 0x01U) ;  
            /* Check for Error */
            if(IFXSMU_NO_ERROR != Value)
            {
                if(loop < 16U)
                {
                  ResetReason = (uint32)(SCU_SMU_AD0.U & 0x0000ffffU) ;
                }
                else
                {
                ResetReason = (uint32) ( (SCU_SMU_AD0.U >>16U) & 0x0000ffffU) ;
                }
                #ifdef IFXSMU_AG_CLEAR
                  SMU_AG0.U &= ~( 1U  << loop);
                #endif
                  /* #ifdef IFXSMU_AG_CLEAR */			  
              retVal = 1U ;   
            }	 
        } /* Checking if mask is on */
    } /* End of for loop */
    
  /* Check for AD1 : bit 0 - 31 */		
  if(0U == retVal)
  {	
    for(loop = 0U ; loop < 32U ; loop ++ )
      {
          /* check from 0 till 31 */
          if( (IFXSMU_AD1_RST_MASK >> loop) & 0x1U)
          {
              /* Get the bit value */
              Value = ( (SCU_SMU_AD1.U >> loop) & 0x01U) ;  
              /* Check for Error */
              if(IFXSMU_NO_ERROR != Value)
              {
                  if(loop < 16U)
                  {
                    ResetReason = (uint32)(SCU_SMU_AD1.U & 0x0000ffffU) ;
                  }
                  else
                  {
                  ResetReason = (uint32) ( (SCU_SMU_AD1.U >>16U) & 0x0000ffffU) ;
                  }
                  
                  #ifdef IFXSMU_AG_CLEAR
                    SMU_AG1.U &= ~( 1U  << loop);
                  #endif
                    /* #ifdef IFXSMU_AG_CLEAR */
                  retVal = 1U ;
              }	 
          } /* Checking if mask is on */
      } /* End of for loop */
    if(0U == retVal)	  	
    {
      /* Check for AD2 : bit 0 - 31 */		
        for(loop = 0U ; loop < 32U ; loop ++ )
        {
            /* check from 0 till 31 */
            if( (IFXSMU_AD2_RST_MASK >> loop) & 0x1U)
            {
                /* Get the bit value */
                Value = ( (SCU_SMU_AD2.U >> loop) & 0x01U) ;  
                /* Check for Error */
                if(IFXSMU_NO_ERROR != Value)
                {
                    if(loop < 16U)
                    {
                      ResetReason = (uint32)(SCU_SMU_AD2.U & 0x0000ffffU) ;
                    }
                    else
                    {
                    ResetReason = (uint32) ( (SCU_SMU_AD2.U >>16U) & 0x0000ffffU) ;
                    }
                    #ifdef IFXSMU_AG_CLEAR
                      SMU_AG2.U &= ~( 1U  << loop);
                    #endif
                      /* #ifdef IFXSMU_AG_CLEAR */
                    retVal = 1U ;   
                }	 
            } /* Checking if mask is on */
        } /* End of for loop */	
        
        if(0U == retVal)
        {
        /* Check for AD3 : bit 0 - 31 */		
          for(loop = 0U ; loop < 32U ; loop ++ )
          {
              /* check from 0 till 31 */
              if( (IFXSMU_AD3_RST_MASK >> loop) & 0x1U)
              {
                  /* Get the bit value */
                  Value = ( (SCU_SMU_AD3.U >> loop) & 0x01U) ;  
                  /* Check for Error */
                  if(IFXSMU_NO_ERROR != Value)
                  {
                      if(loop < 16U)
                      {
                        ResetReason = (uint32)(SCU_SMU_AD3.U & 0x0000ffffU) ;
                      }
                      else
                      {
                      ResetReason = (uint32) ( (SCU_SMU_AD3.U >>16U) & 0x0000ffffU) ;
                      }
        
                      #ifdef IFXSMU_AG_CLEAR
                        SMU_AG3.U &= ~( 1U  << loop);
                      #endif
                        /* #ifdef IFXSMU_AG_CLEAR */
                      retVal = 1U ;   
                  }	 
              } /* Checking if mask is on */
          } /* End of for loop */
          if(0U == retVal)
          {	
          /* Check for AD4 : bit 0 - 31 */		
            for(loop = 0U ; loop < 32U ; loop ++ )
            {
                /* check from 0 till 31 */
                if( (IFXSMU_AD4_RST_MASK >> loop) & 0x1U)
                {
                    /* Get the bit value */
                    Value = ( (SCU_SMU_AD4.U >> loop) & 0x01U) ;  
                    /* Check for Error */
                    if(IFXSMU_NO_ERROR != Value)
                    {
                        if(loop < 16U)
                        {
                          ResetReason = (uint32)(SCU_SMU_AD4.U & 0x0000ffffU) ;
                        }
                        else
                        {
                        ResetReason = (uint32) ( (SCU_SMU_AD4.U >>16U) & 0x0000ffffU) ;
                        }
                        
                        #ifdef IFXSMU_AG_CLEAR
                          SMU_AG4.U &= ~( 1U  << loop);
                        #endif
                          /* #ifdef IFXSMU_AG_CLEAR */
                        retVal = 1U ;   
                    }	 
                } /* Checking if mask is on */
            } /* End of for loop */
            
            if(0U == retVal)
            {
            /* Check for AD5 : bit 0 - 31 */		
              for(loop = 0U ; loop < 32U ; loop ++ )
              {
                  /* check from 0 till 31 */
                  if( (IFXSMU_AD5_RST_MASK >> loop) & 0x1U)
                  {
                      /* Get the bit value */
                      Value = ( (SCU_SMU_AD5.U >> loop) & 0x01U) ;  
                      /* Check for Error */
                      if(IFXSMU_NO_ERROR != Value)
                      {
                          if(loop < 16U)
                          {
                            ResetReason = (uint32)(SCU_SMU_AD5.U & 0x0000ffffU) ;
                          }
                          else
                          {
                          ResetReason = (uint32) ( (SCU_SMU_AD5.U >>16U) & 0x0000ffffU) ;
                          }
                                          
                          #ifdef IFXSMU_AG_CLEAR
                            SMU_AG5.U &= ~( 1U  << loop);
                          #endif
                            /* #ifdef IFXSMU_AG_CLEAR */
                          retVal = 1U ;   
                      }	 
                  } /* Checking if mask is on */
              } /* End of for loop */
              
              if(0U == retVal)
              {
              /* Check for AD6 : bit 0 - 31 */		
                for(loop = 0U ; loop < 32U ; loop ++ )
                {
                    /* check from 0 till 31 */
                    if( (IFXSMU_AD6_RST_MASK >> loop) & 0x1U)
                    {
                        /* Get the bit value */
                        Value = ( (SCU_SMU_AD6.U >> loop) & 0x01U) ;  
                        /* Check for Error */
                        if(IFXSMU_NO_ERROR != Value)
                        {
                            if(loop < 16U)
                            {
                              ResetReason = (uint32)(SCU_SMU_AD6.U & 0x0000ffffU) ;
                            }
                            else
                            {
                            ResetReason = (uint32) ( (SCU_SMU_AD6.U >>16U) & 0x0000ffffU) ;
                            }
                            #ifdef IFXSMU_AG_CLEAR
                              SMU_AG6.U &= ~( 1U  << loop);
                            #endif
                              /* #ifdef IFXSMU_AG_CLEAR */
                        }	 
                    } /* Checking if mask is on */
                } /* End of for loop */		        	          	
              }	  	
            }	
          }    		    		    	
        }
    }	
  }		
    return ( ResetReason ) ;
}/* */

/** \brief Performs the Reset Functionality
 *
 * Evaluates the Reset Status register b reading the 
 * RSTSTAT register
 *
 * \param resetType Application(0) / System Reset (1)
 * \param userInfo User Data for evaluation after reset
 *
 * \return None.
 */
void IfxScuCcu_PerformReset(uint8  resetType,uint32 userInfo)
{
  uint32 index;
  uint16 l_SEndInitPW; 

  l_SEndInitPW = IfxScuWdt_getSafetyWatchdogPassword ();  

  /*Clear the SafetyENDINIT bit in the WDT_CON0 register in order
  to disable the write-protection for registers protected
  via the EndInit feature */
  IfxScuWdt_clearSafetyEndinit(l_SEndInitPW);

  /* Write the Reset Type - Application or System Reset */
  if( IFXSCURCU_SYSTEM_RESET == resetType)
  {
    SCU_RSTCON.B.SW = IFXSCURCU_SYSTEM_RESET;
  }  
  else
  {
    SCU_RSTCON.B.SW = IFXSCURCU_APPLICATION_RESET;
  }	
  /* Write the user DATA to reset evaluation */
  SCU_RSTCON2.B.USRINFO = userInfo;
  
  /* software Reset can be performed by writing to Reset Request register
  SWRSTCON */

  SCU_SWRSTCON.B.SWRSTREQ = 1U;

  /* Add some delay for HW to reset */
  for(index = 0U ; index< (uint32)IFXSCURCU_PERFORM_RESET_DELAY; index++)
  {
      
  }
  /*IfxScu_Wdt_enableSafetyEndinit() is not needed, as the micro would RESET */
}	
/*lint -restore */
