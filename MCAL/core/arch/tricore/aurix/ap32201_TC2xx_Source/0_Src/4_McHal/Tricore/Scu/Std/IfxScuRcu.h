/**
 * \file IfxScuRcu.h
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
#ifndef IFXSCURCU_H_
#define IFXSCURCU_H_



#include "IfxSmu.h"
#include "IfxScu_reg.h"

/*******************************************************************************
**                      Type definitions                                     **
*******************************************************************************/

typedef enum {
  /* Reset types  */
  IfxScuRcu_ResetType_coldpoweron,     /* Cold Power On Reset */
  IfxScuRcu_ResetType_warmpoweron,     /* Warm Power On Reset */
  IfxScuRcu_ResetType_system,          /* System Reset */
  IfxScuRcu_ResetType_application,     /* Application Reset */
  IfxScuRcu_ResetType_debug,           /* debug Reset */
  IfxScuRcu_ResetType_undefined
}IfxScuRcu_ResetType;

typedef enum {
  /* Reset Triggers */
  IfxScuRcu_Trigger_esr0,            /* ESR0 */
  IfxScuRcu_Trigger_esr1,            /* ESR1 */
  IfxScuRcu_Trigger_smu,             /* SMU Alaram */
  IfxScuRcu_Trigger_sw,              /* Software */
  IfxScuRcu_Trigger_stm0,            /* STM0 */
  IfxScuRcu_Trigger_stm1,            /* STM1 */
  IfxScuRcu_Trigger_stm2,            /* STM2 */
  IfxScuRcu_Trigger_porst,           /* Power on Reset */
  IfxScuRcu_Trigger_cb0,             /* Cerberus 0  */
  IfxScuRcu_Trigger_cb1,             /* Cerberus 1  */
  IfxScuRcu_Trigger_cb3,             /* Cerberus 2  */
  IfxScuRcu_Trigger_evr13,           /* EVR13 Watchdog */
  IfxScuRcu_Trigger_evr33,           /* EVR33 Watchdog */  
  IfxScuRcu_Trigger_swd,             /* Supply Watchdog */
  IfxScuRcu_Trigger_stbyr,           /* Standby Regulator Watchdog */
  IfxScuRcu_Trigger_tcu,             /* TCU */
  IfxScuRcu_Trigger_tp,              /* Tuning Protection */
  IfxScuRcu_Trigger_hsms,            /* HSM System */
  IfxScuRcu_Trigger_hsma,            /* HSM Application */
  IfxScuRcu_Trigger_undefined        /* Undefined Value */
}IfxScuRcu_Trigger;


/*******************************************************************************
**                Global Exported variables/constants                         **
*******************************************************************************/
typedef struct 
{
    uint8  ResetType ; 
    uint8  ResetTrigger ;
    uint16 ResetReason; 
} IfxScuRcu_ResetCode ; 

/*******************************************************************************
**         Global Exported macros/inlines/function ptototypes                 **
*******************************************************************************/
/* CPU Safe State */
#define IFXSCURCU_CPU_IN_SAFE_STATE           (1U) 
#define IFXSCURCU_CPU_NOT_IN_SAFE_STATE       (0U) 
#define IFXSCURCU_CPU_SAFE_STATE_POS          (12U)
#define IFXSCURCU_CPU_SAFE_STATE_MASK         (0x00007000U)
#define IFXSCURCU_USRINFO_MASK                (0xFFFF0000U)

/* Mask to check CPU safe states */
#define IFXSCURCU_CPU0_SAFE_STATE_MASK         (1U)
#define IFXSCURCU_CPU0_1_SAFE_STATE_MASK       (3U)
#define IFXSCURCU_CPU0_1_2_SAFE_STATE_MASK     (7U)
 
/*This value masks the reset status register*/
#if defined TC2XX_A_Step
  #define IFXSCURCU_RESET_REASON_MASK           (0x039D00FBU)
#else
  #define IFXSCURCU_RESET_REASON_MASK           (0x1FFD00FBU)
#endif 
   /* #if defined TC2XX_A_Step */  
/*  ESR0 reset */
#define IFXSCURCU_RAW_ESR0_RESET          (0x00000001U)
/* ESR1 reset */ 
#define IFXSCURCU_RAW_ESR1_RESET          (0x00000002U)
/* SMU reset */
#define IFXSCURCU_RAW_SMU_RESET           (0x00000008U)
/* Software reset */
#define IFXSCURCU_RAW_SW_RESET            (0x00000010U)
/* STM0 reset */
#define IFXSCURCU_RAW_STM0_RESET          (0x00000020U)
/* STM1 reset */
#define IFXSCURCU_RAW_STM1_RESET          (0x00000040U)
/* STM2 reset */
#define IFXSCURCU_RAW_STM2_RESET          (0x00000080U)
/* Power On reset */
#define IFXSCURCU_RAW_POWER_ON_RESET      (0x00010000U) 
/* CB0 reset */
#define IFXSCURCU_RAW_CB0_RESET           (0x00040000U) 
/* CB1 reset */
#define IFXSCURCU_RAW_CB1_RESET           (0x00080000U) 
/* CB3 reset */
#define IFXSCURCU_RAW_CB3_RESET           (0x00100000U)
/* TP reset */
#define IFXSCURCU_RAW_TP_RESET            (0x00200000U) 
/* TCU reset */
#define IFXSCURCU_RAW_TCU_RESET           (0x00400000U) 
/* EVR13  reset */
#define IFXSCURCU_RAW_EVR13_RESET         (0x00800000U) 
/* EVR33  reset */
#define IFXSCURCU_RAW_EVR33_RESET         (0x01000000U) 
/* Supply Watch dog reset */
#define IFXSCURCU_RAW_SUPPLY_WDOG_RESET   (0x02000000U) 
/* HSM system Reset */
#define IFXSCURCU_RAW_HSM_SYS_RESET       (0x04000000U) 
/* HSM Application Reset */
#define IFXSCURCU_RAW_HSM_APP_RESET       (0x08000000U) 
/* Wake up From Standby Reset*/
#define IFXSCURCU_RAW_STBYR_RESET         (0x10000000U) 
/* Reset Reason Not Valid */
#define IFXSCURCU_RESET_REASON_DEFAULT    (0x00000000U) 

#define  IFXSCURCU_SYSTEM_RESET           (1U)
#define IFXSCURCU_APPLICATION_RESET       (2U)
#define IFXSCURCU_RESET_TRIGGER_MASK      (0x00000003U)

#define IFXSCURCU_ESR0_MASK               (0x00000000U)
#define IFXSCURCU_ESR1_MASK               (0x00000002U)
#define IFXSCURCU_SMU_MASK                (0x00000006U)
#define IFXSCURCU_SW_MASK                 (0x00000008U)
#define IFXSCURCU_STM0_MASK               (0x0000000AU)
#define IFXSCURCU_STM1_MASK               (0x0000000CU)
#define IFXSCURCU_STM2_MASK               (0x0000000EU)

#define IfxStart_STK_MEM_TEST_FAIL         (0x2000)


/* Used for the delay after performing reset */
#define IFXSCURCU_PERFORM_RESET_DELAY    (90000U)

IFX_INLINE void IfxScuCcu_PerformReset_Inline(uint8  resetType,uint32 userInfo)
{  
  register uint32 index ;
  uint16 password;

  password = IfxScuWdt_getSafetyWatchdogPasswordInline( );
  
  /*Clear the SafetyENDINIT bit in the WDT_CON0 register in order
  to disable the write-protection for registers protected
  via the EndInit feature */
  IfxScuWdt_clearSafetyEndinitInline(password) ;

  /* Do a Application */
  SCU_RSTCON.B.SW = resetType ;

  /* Write the user DATA to reset evaluation */
  SCU_RSTCON2.B.USRINFO = userInfo ;
 
  /* software Reset can be performed by writing to Reset Request register
  SWRSTCON */

  SCU_SWRSTCON.B.SWRSTREQ = 1U;

  /* Add some delay for HW to reset */
  for(index = 0U ; index< (uint32)IFXSCURCU_PERFORM_RESET_DELAY; index++)
  {
      
  }
}  

IfxScuRcu_ResetCode IfxScu_ResetRamEval(void);
void IfxScuRcu_ClrCPorstStatus(void) ;
void IfxScuCcu_PerformReset(uint8  resetType,uint32 userInfo);

#endif  /* IFXSCURCU_H_ */
