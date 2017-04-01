/**
 * \file IfxPort_cfg.h
 * \brief Port on-chip implementation data 
 * \ingroup IfxLld_Port 
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
 *
 */

#ifndef IFXPORT_CFG_H
#define IFXPORT_CFG_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "Cpu/Std/IfxCpu_Intrinsics.h"
#include "_Reg/IfxPort_reg.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/** \brief Port count              \ingroup IfxLld_port_cfg 
 */
#define IFXPORT_COUNT (16)
                
#define IFXPORT_OUTOUTFEATURE_NONE (0xFFFFFFFF)
                


/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/** \brief used by IfxPort_Esr_Masks table  
 */
typedef struct
{
    Ifx_P*    port;   
    uint16    masks;  
} IfxPort_Esr_Masks;


/******************************************************************************/
/*-------------------Global Exported Variables/Constants----------------------*/
/******************************************************************************/

IFX_EXTERN const IfxPort_Esr_Masks IfxPort_cfg_esrMasks[IFXPORT_COUNT];

IFX_EXTERN const IfxModule_IndexMap IfxPort_cfg_indexMap[IFXPORT_COUNT];


#endif /* IFXPORT_CFG_H */
