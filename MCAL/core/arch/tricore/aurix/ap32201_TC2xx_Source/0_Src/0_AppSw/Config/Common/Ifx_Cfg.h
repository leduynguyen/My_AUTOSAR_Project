/**
 * \file Ifx_Cfg.h
 * \brief Project configuration file.
 *
 * \copyright Copyright (c) 2012 Infineon Technologies AG. All rights reserved.
 *
 *
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
 */

#ifndef IFX_CFG_H
#define IFX_CFG_H 1
/******************************************************************************/
/*#include  "Ifx_preInitHook.h"*/


/* Micro Versions */
#define TC29X   		(1U)
#define TC27X   		(2U)
#define TC26X   		(3U)
#define TC23X   		(4U)

#define IFX_CFG_TC29X   		(TC29X)
#define IFX_CFG_TC27X   		(TC27X)
#define IFX_CFG_TC26X   		(TC26X)
#define IFX_CFG_TC23X   		(TC23X)

#define CLOCK_OPT_POWER       (0U)  /* Clock power optimization */
#define CLOCK_OPT_PERF        (1U)  /* Clock performance optimization */

/*______________________________________________________________________________
** Configuration for IfxScu_cfg.h
**____________________________________________________________________________*/
#define IFX_CFG_SCU_XTAL_FREQUENCY		(20000000)	/**<allowed values 16000000, 20000000 or 40000000*/
#define IFX_CFG_SCU_PLL_FREQUENCY		(200000000) /**<allowed values 80000000, 133000000, 160000000 or 200000000 */
#define IFX_CFG_SCU_CLOCK_OPTION         (CLOCK_OPT_PERF) /* */
#define IFXCFG_PLL_CLOCK_SOURCE          (1U)
#define IFX_CFG_DEVICE                   (IFX_CFG_TC27X)

#if defined IFXSTART_ED_DEVICE_SUPPORTED
  #define IFX_CFG_ED_DEVICE_SUPPORTED      (STD_ON) 
#else                                                
  #define IFX_CFG_ED_DEVICE_SUPPORTED      (STD_OFF) 
#endif   

/** \brief Configuration for CpuX enable.
 *
 */
#define IFX_CPU_ENABLE_TRICORE1
#define IFX_CPU_ENABLE_TRICORE2

#define IFX_CFG_SCUCCU_MON_TRIGGER         (0U)
/*______________________________________________________________________________
** Configuration for Software managed interrupt
**____________________________________________________________________________*/

#define IFX_USE_SW_MANAGED_INT

/*______________________________________________________________________________
** Configuration for Trap Hook Functions' Extensions
**____________________________________________________________________________*/

#define IFX_CFG_EXTEND_TRAP_HOOKS          

/******************************************************************************/

#define IFX_CFG_CPU_TRAP_TSR_HOOK(trapInfo)           myTrapExtensionHook(trapInfo)
#define IFX_CFG_CPU_TRAP_SYSCALL_CPU0_HOOK(trapInfo)  myTrapExtensionHook(trapInfo)
#define IFX_CFG_CPU_TRAP_SYSCALL_CPU1_HOOK(trapInfo)  myTrapExtensionHook(trapInfo)
#define IFX_CFG_CPU_TRAP_SYSCALL_CPU2_HOOK(trapInfo)  myTrapExtensionHook(trapInfo)

#define __jump_and_link(name) \
    __asm__ ( \
        "movh.a  %a14, hi:"#name"                      \n"\
        "lea     %a14, [%a14]lo:"#name"                \n"\
        "jli      %a14                                 \n"\
        );

#define __jump_to_link() \
    __asm__ ( \
        "ji      %a11                                 \n"\
        );

#define IFX_CFG_CPU_CSTART_PRE_C_INIT_HOOK(cpu) \
{\
    extern void IfxSysPreC_InitHook0(void);\
    extern void IfxSysPreC_InitHook1(void);\
    extern void IfxSysPreC_InitHook2(void);\
    if(cpu==0) __jump_and_link(IfxSysPreC_InitHook0) \
    else if(cpu==1) __jump_and_link(IfxSysPreC_InitHook1) \
    else if(cpu==2) __jump_and_link(IfxSysPreC_InitHook2) \
}
#endif /* IFX_CFG_H */
