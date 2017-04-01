/**
 * \file IfxEdMem_cfg.h
 * \brief Ed memory configuration file
 *
 *
 * \copyright Copyright (c) 2012 Infineon Technologies AG. All rights reserved.
 *
 * $Revision: 001 $
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
#ifndef IFXEDMEM_CFG_H
#define IFXEDMEM_CFG_H

#include "Ifx_Cfg.h"
#include "IfxOvc_reg.h"
#if (IFX_CFG_DEVICE != IFX_CFG_TC24X )
  #include "IfxEmem_reg.h"
#endif
  /* */
#include "IfxScu_reg.h"
#include "IfxCpu.h"


/* Number of Tiles to be cofnigured */      
#define  IFXEMEM_MAX_NUM_TILES        (16U) 
#endif 
  /* */

