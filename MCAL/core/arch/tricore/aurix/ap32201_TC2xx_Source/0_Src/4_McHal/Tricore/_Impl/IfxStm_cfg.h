/**
 * \file IfxStm_cfg.h
 * \brief Stm on-chip implementation data 
 * \ingroup IfxLld_Stm 
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
 * \defgroup IfxLld_Stm_Impl Implementation
 * \ingroup IfxLld_Stm
 * \defgroup IfxLld_Stm_Impl_Enumerations Enumerations
 * \ingroup IfxLld_Stm_Impl
 * \defgroup IfxLld_Stm_Impl_Variables Global Variables
 * \ingroup IfxLld_Stm_Impl
 */

#ifndef IFXSTM_CFG_H
#define IFXSTM_CFG_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "Cpu/Std/IfxCpu_Intrinsics.h"
#include "Ifx_Cfg.h"
#include "_Reg/IfxStm_reg.h"
#include "Scu/Std/IfxScuCcu.h"
#include "Src/Std/IfxSrc.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/** \brief STM count 
 */
#define IFXSTM_COUNT 3
                


/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Stm_Impl_Enumerations
 * \{ */
/** \brief List of the available STM resources  
 */
typedef enum
{
    IfxStm_ResourceStm_0 = 0,       /**< \brief STM resources 0  */
    IfxStm_ResourceStm_1,           /**< \brief STM resources 1  */
    IfxStm_ResourceStm_2,           /**< \brief STM resources 2  */
    IfxStm_ResourceStm_none = -1  /**< \brief none of STM resources */
} IfxStm_ResourceStm;

/** \} */ 
 
/** \addtogroup IfxLld_Stm_Impl_Variables
 * \{ */

/******************************************************************************/
/*-------------------Global Exported Variables/Constants----------------------*/
/******************************************************************************/

IFX_EXTERN const IfxModule_IndexMap IfxStm_cfg_indexMap[IFXSTM_COUNT];


/** \} */  


#endif /* IFXSTM_CFG_H */
