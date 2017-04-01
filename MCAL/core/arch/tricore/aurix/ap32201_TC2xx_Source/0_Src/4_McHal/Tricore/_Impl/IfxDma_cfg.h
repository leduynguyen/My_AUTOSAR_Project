/**
 * \file IfxDma_cfg.h
 * \brief Dma on-chip implementation data 
 * \ingroup IfxLld_Dma 
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

#ifndef IFXDMA_CFG_H
#define IFXDMA_CFG_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "Cpu/Std/Ifx_Types.h"
#include "Cpu/Std/IfxCpu_Intrinsics.h"
#include "Src/Std/IfxSrc.h"
#include "_Reg/IfxDma_bf.h"
#include "_Reg/IfxDma_reg.h"
#include "Cpu/Std/IfxCpu.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/** \brief Number of channels 
 */
#define IFXDMA_NUM_CHANNELS 64
                
/** \brief Error mask for move engine source error 
 */
#define IFXDMA_ERROR_S (IFX_DMA_BLK_CLRE_CSER_MSK << IFX_DMA_BLK_CLRE_CSER_OFF)
                
/** \brief Error mask for move engine destination error 
 */
#define IFXDMA_ERROR_D (IFX_DMA_BLK_CLRE_CDER_MSK << IFX_DMA_BLK_CLRE_CDER_OFF)
                
/** \brief Error mask for bus error on SPB 
 */
#define IFXDMA_ERROR_SPB (IFX_DMA_BLK_CLRE_CSPBER_MSK << IFX_DMA_BLK_CLRE_CSPBER_OFF)
                
/** \brief Error mask for bus error on SRI 
 */
#define IFXDMA_ERROR_SRI (IFX_DMA_BLK_CLRE_CSRIER_MSK << IFX_DMA_BLK_CLRE_CSRIER_OFF)
                
/** \brief Error mask for RAM error 
 */
#define IFXDMA_ERROR_RAM (IFX_DMA_BLK_CLRE_CRAMER_MSK << IFX_DMA_BLK_CLRE_CRAMER_OFF)
                
/** \brief Error mask for SLL (safe linked list CRC checksum) error 
 */
#define IFXDMA_ERROR_SLL (IFX_DMA_BLK_CLRE_CSLLER_MSK << IFX_DMA_BLK_CLRE_CSLLER_OFF)
                
/** \brief Error mask for DLL (failed linked list load) error 
 */
#define IFXDMA_ERROR_DLL (IFX_DMA_BLK_CLRE_CDLLER_MSK << IFX_DMA_BLK_CLRE_CDLLER_OFF)
                

#endif /* IFXDMA_CFG_H */
