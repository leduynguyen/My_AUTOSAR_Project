/**
 * \file IfxCpu_cfg.h
 * \brief Cpu on-chip implementation data 
 * \ingroup IfxLld_Cpu 
 *
 * \version iLLD_0_1_0_6
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
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

#ifndef IFXCPU_CFG_H
#define IFXCPU_CFG_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "Cpu/Std/IfxCpu_Intrinsics.h"
#include "IfxCpu_reg.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/** \brief CPU count 
 */
 #if ((IFX_CFG_DEVICE == IFX_CFG_TC29X ) || (IFX_CFG_DEVICE == IFX_CFG_TC27X ))
#define IFXCPU_COUNT (3)
#elif  (IFX_CFG_DEVICE == IFX_CFG_TC26X )
  #define IFXCPU_COUNT   (2)               /**< \brief CPU count */
#else
  #define IFXCPU_COUNT   (1)               /**< \brief CPU count */
#endif
                
/** \brief Segment number of cachable flash region 
 */
#define IFXCPU_CACHABLE_FLASH_SEGMENT (8)
                
/** \brief Segment number of cachable LMU region 
 */
#define IFXCPU_CACHABLE_LMU_SEGMENT (9)
                


/******************************************************************************/
/*-------------------------------Enumerations---------------------------------*/
/******************************************************************************/

/** \brief Halt status  
 */
typedef enum
{
    IfxCpu_DBGST_HALT_run = 0,  
    IfxCpu_DBGST_HALT_halt = 1  
} IfxCpu_DBGST_HALT;

/** \brief Power management status  
 */
typedef enum
{
    IfxCpu_PMCSR_PMST_normalMode = 1,         
    IfxCpu_PMCSR_PMST_idleModeRequest = 2,    
    IfxCpu_PMCSR_PMST_idleMode = 3,           
    IfxCpu_PMCSR_PMST_sleepModeRequest = 4,   
    IfxCpu_PMCSR_PMST_standbyModeRequest = 6  
} IfxCpu_PMCSR_PMST;

/** \brief List of the available CPU resources  
 */
typedef enum
{
    IfxCpu_ResourceCpu_0,    /**< \brief CPU 0 */
    IfxCpu_ResourceCpu_1,    /**< \brief CPU 1 */
    IfxCpu_ResourceCpu_2,    /**< \brief CPU 2 */
    IfxCpu_ResourceCpu_none  /**< \brief None of the CPU */
} IfxCpu_ResourceCpu;


/******************************************************************************/
/*-------------------Global Exported Variables/Constants----------------------*/
/******************************************************************************/

IFX_EXTERN const IfxModule_IndexMap IfxCpu_cfg_indexMap[IFXCPU_COUNT];


#endif /* IFXCPU_CFG_H */
