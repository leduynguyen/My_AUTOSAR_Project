/**
 * \file IfxSrc_cfg.h
 * \brief Src on-chip implementation data 
 * \ingroup IfxLld_Src 
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
 * \defgroup IfxLld_Src_Impl Implementation
 * \ingroup IfxLld_Src
 * \defgroup IfxLld_Src_Impl_Enumerations Enumerations
 * \ingroup IfxLld_Src_Impl
 */

#ifndef IFXSRC_CFG_H
#define IFXSRC_CFG_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "Cpu/Std/IfxCpu_Intrinsics.h"
#include "_Reg/IfxSrc_reg.h"
#include "Ifx_Cfg.h"


/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Src_Impl_Enumerations
 * \{ */
/** \brief Identifier of interrupt service provider, which handles the interrupt service request.  
 */
typedef enum
{
    IfxSrc_Tos_cpu0 = 0,  /**< \brief CPU0 interrupt service provider, which handles the interrupt service request. */
    IfxSrc_Tos_cpu1 = 1,  /**< \brief CPU1 interrupt service provider, which handles the interrupt service request. */
    IfxSrc_Tos_cpu2 = 2,  /**< \brief CPU2 interrupt service provider, which handles the interrupt service request. */
    IfxSrc_Tos_dma = 3    /**< \brief DMA interrupt service provider, which handles the interrupt service request. */
} IfxSrc_Tos;

/** \} */ 
 

#endif /* IFXSRC_CFG_H */
