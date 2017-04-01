/**
 * \file IfxCpu_cfg.c
 * \brief Cpu on-chip implementation data
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

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxCpu_cfg.h"

/******************************************************************************/
/*-----------------------Exported Variables/Constants-------------------------*/
/******************************************************************************/

const IfxModule_IndexMap IfxCpu_cfg_indexMap[IFXCPU_COUNT] = {
    {&MODULE_CPU0, (uint32)IfxCpu_ResourceCpu_0},
#if ((IFX_CFG_DEVICE == IFX_CFG_TC29X ) || (IFX_CFG_DEVICE == IFX_CFG_TC27X ) ||  (IFX_CFG_DEVICE == IFX_CFG_TC26X ))
    {&MODULE_CPU1, (uint32)IfxCpu_ResourceCpu_1},
#endif
#if ((IFX_CFG_DEVICE == IFX_CFG_TC29X ) || (IFX_CFG_DEVICE == IFX_CFG_TC27X ))
    {&MODULE_CPU2, (uint32)IfxCpu_ResourceCpu_2},
#endif
};
