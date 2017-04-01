/**
 * \file IfxStart_Cfg.h
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
 * $Revision: 003 $
 * $Date: 24-05-2013 12:09 +0530 $
 *
 * \defgroup Ifx Infineon Software
 * \defgroup Ifx_Lld Infineon Low Level Drivers' Software
 * \ingroup I
 */ 
/******************************************************************************/

#ifndef IFXSTART_CFG_H_
#define IFXSTART_CFG_H_

#include "Ifx_Types.h"
#include "Compilers.h"
#include "IfxCpu_Intrinsics.h"
#include "IfxPort_reg.h"

#include "IfxMtu_Cfg.h"
#include "IfxPort.h"

/* Support for Execptions are defined here */
/* #define IFX_CPU_ENABLE_TRICORE1 */
/* #define IFX_CPU_ENABLE_TRICORE2  */

#define IFXSTART_ERROR_EXCEPTION_SUPPORTED      
#define IFXSTART_DEUG_EXCEPTION_SUPPORTED  
#define IFXSTART_PORST_EXCEPTION_SUPPORTED  
#define IFXSTART_SYSINIT_EXCEPTION_SUPPORTED  
#define IFXSTART_OS_START_EXCEPTION_SUPPORTED

/* User function for Error Exception */
#ifdef START_SetEX_ErrorEvent
#error START_SetEX_ErrorEvent already defined
#endif
#define IFXSTART_ERROR_EXCEPTION     (START_SetEX_ErrorEvent)

/* User function for Debug Exception */
#ifdef START_SetEX_DebugEvent
#error START_SetEX_DebugEvent already defined
#endif
#define IFXSTART_DEBUG_EXCEPTION     (START_SetEX_DebugEvent)

/* User function for System Init Exception */
#ifdef START_EX_SysInit
#error START_EX_SysInit already defined
#endif
#define IFXSTART_SYSINIT_EXCEPTION     (Test_DD_Ex_SysInit)

/* User function for Back ground task Exception */
#ifdef START_EX_BackgroundTask
#error START_EX_BackgroundTask already defined
#endif
#define IFXSTART_OS_START_EXCEPTION     (Test_DD_Ex_BgTask)


#define IFXSTART_EXTCLK0               (STD_ON)
#define IFXSTART_EXTCLK_0_DIV          (10U)
#define IFXSTART_EXTCLK0_SEL           (0U)
#define IFXSTART_EXT_CLK_OUT_0_PIN     (90U)         /* Select EXT_CLK0 Output Pin */

#define IFXSTART_EXTCLK1               (STD_ON)
#define IFXSTART_EXTCLK_1_DIV          (20U)
#define IFXSTART_EXTCLK1_SEL           (0U)
#define IFXSTART_EXT_CLK_OUT_1_PIN     (88U)          /* Select EXT_CLK1 Output Pin */


#define BIOS_CLEAR_SEGMENT_00     (0U)
#define BIOS_CLEAR_SEGMENT_01     (1U)
#define BIOS_CLEAR_SEGMENT_02     (0U)
#define BIOS_CLEAR_SEGMENT_03     (0U)
#define BIOS_CLEAR_SEGMENT_04     (0U)
#define BIOS_CLEAR_SEGMENT_05     (0U)
#define BIOS_CLEAR_SEGMENT_06     (0U)
#define BIOS_CLEAR_SEGMENT_07     (0U)

#define BIOS_CLEAR_SEGMENT_10     (1U)
#define BIOS_CLEAR_SEGMENT_11     (1U)
#define BIOS_CLEAR_SEGMENT_12     (0U)
#define BIOS_CLEAR_SEGMENT_13     (0U)
#define BIOS_CLEAR_SEGMENT_14     (0U)
#define BIOS_CLEAR_SEGMENT_15     (0U)
#define BIOS_CLEAR_SEGMENT_16     (0U)
#define BIOS_CLEAR_SEGMENT_17     (0U)


#define BIOS_CLEAR_SEGMENT_20     (1U)
#define BIOS_CLEAR_SEGMENT_21     (1U)
#define BIOS_CLEAR_SEGMENT_22     (0U)
#define BIOS_CLEAR_SEGMENT_23     (0U)
#define BIOS_CLEAR_SEGMENT_24     (0U)
#define BIOS_CLEAR_SEGMENT_25     (0U)
#define BIOS_CLEAR_SEGMENT_26     (0U)
#define BIOS_CLEAR_SEGMENT_27     (0U)


/* PERFORM the CACHE Test if defined */
/* #define BIOS_SKIP_CACHE_TEST */
#define BIOS_NUM_SEG_CPU0        (4U)
#define BIOS_NUM_SEG_CPU1        (0U)
#define BIOS_NUM_SEG_CPU2        (0U)

/* These memory segments should be at 4K boundary and of size 4K */
#define BIOS_SEGMENT_00_START	(0x70008000U)/*//(0x70000000U)*/
#define BIOS_SEGMENT_00_END		(0x70008FFFU)/*//(0x70000FFFU)*/

#define BIOS_SEGMENT_01_START	(0x70001000U)
#define BIOS_SEGMENT_01_END		(0x70001FFFU)

#define BIOS_SEGMENT_02_START	(0x70002000U)
#define BIOS_SEGMENT_02_END		(0x70002FFFU)

#define BIOS_SEGMENT_03_START	(0x70100000U)
#define BIOS_SEGMENT_03_END		(0x70100FFFU)

/* Total Number of Pins in the package */
#define MAX_CFG_PIN    					(8U) /*111*/

/* 
The resulting monitoring frequency is configured to  fPLLMON = fPLL / PLLDIV.
For PLLDIV = 0000B the monitoring is disabled.
*/
#if (IFXSTART_MON_PLL == STD_OFF)
  #define IFXSTART_PLL_MON_DIV           (0U)
#else
  #define IFXSTART_PLL_MON_DIV           (1U)
#endif
#define IFXSTART_PLL_MON_FREQ          (IFXSTART_PLL_MON_F_5MHZ)

#if (IFXSTART_MON_SRI == STD_OFF)
  #define IFXSTART_SRI_MON_DIV           (0U) 
#else
  #define IFXSTART_SRI_MON_DIV           (1U) 
#endif     
#define IFXSTART_SRI_MON_FREQ          (IFXSTART_PLL_MON_F_5MHZ) 

#if (IFXSTART_MON_SPB == STD_OFF)
  #define IFXSTART_SPB_MON_DIV           (0U) 
#else
  #define IFXSTART_SPB_MON_DIV           (0U) 
#endif     
#define IFXSTART_SPB_MON_FREQ          (IFXSTART_PLL_MON_F_5MHZ) 

#if (IFXSTART_MON_GTM == STD_OFF)
  #define IFXSTART_GTM_MON_DIV           (0U) 
#else
  #define IFXSTART_GTM_MON_DIV           (0U) 
#endif     
#define IFXSTART_GTM_MON_FREQ          (IFXSTART_PLL_MON_F_5MHZ) 

#if (IFXSTART_MON_STM == STD_OFF)
  #define IFXSTART_STM_MON_DIV           (0U) 
#else
  #define IFXSTART_STM_MON_DIV           (0U) 
#endif     
#define IFXSTART_STM_MON_FREQ          (IFXSTART_PLL_MON_F_5MHZ) 

#if (IFXSTART_MON_ADC == STD_OFF)
  #define IFXSTART_ADC_MON_DIV           (0U) 
#else
  #define IFXSTART_ADC_MON_DIV           (0U) 
#endif     
#define IFXSTART_ADC_MON_FREQ          (IFXSTART_PLL_MON_F_5MHZ) 

typedef struct
{
  Ifx_P            *port;
  uint8             pinIndex;
  IfxPort_Mode      mode;
  IfxPort_PadDriver padDriver;
  IfxPort_State     DefaultState;  /* OUT */
} IfxStart_Pin_Config;

#endif /* IFXSTART_CFG_H_ */
