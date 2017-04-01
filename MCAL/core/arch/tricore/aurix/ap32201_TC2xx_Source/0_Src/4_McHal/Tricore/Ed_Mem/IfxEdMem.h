/**
 * \file IfxEdMem.c
 * \brief This file contains the API for initializing the ED memory. 
 * Port related functions.
 *
 * \copyright Copyright (c) 2012 Infineon Technologies AG. All rights reserved.
 *
 * $Revision: 002 $
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

#ifndef IFXEDMEM_H_
#define IFXEDMEM_H_

#include <Platform_Types.h>
#include "IfxEdMem_cfg.h"
#include "IfxScuWdt.h"

#define EMEM_ADDRESS_BASE              (0xf00e6000)
#define EMEM_ADDRESS_BASE_SRI          (0xf90e6000)
#define EMEM_ADDRESS_RANGE             (0x0100)

#define OVC0_ADDRESS_BASE              (0xf880fb00)
#define IFXEMEM_OBASE_MASK             (0x003FFFE0U)
#define IFXEMEM_TBASE_MASK             (0x0FFFFFE0U)
#define IFXEMEM_OMASK_MASK             (0x0001FFE0U)


typedef enum
{
    IfxEmem_TileType_Cal       = 0U ,
    IfxEmem_TileType_Trace     = 1U ,
    IfxEmem_TileType_Unused    = 2U ,
    IfxEmem_TileType_Cal_Bbb   = 3U,
    IfxEmem_TileType_Trace_Bbb = 4U ,
    IfxEmem_TileType_Unchanged = 5U
}IfxEmem_TileType ;

typedef enum
{
    IfxEmem_TileConfig_Cal        = 0U,
    IfxEmem_TileConfig_Unchange   = 1U,
    IfxEmem_TileConfig_Trace      = 2U,
    IfxEmem_TileConfig_Unused     = 3U   
}IfxEmem_TileConfig ; 

typedef enum
{
    IfxEmem_TileSts_Cal        = 0U,
    IfxEmem_TileSts_Bbb        = 1U,
    IfxEmem_TileSts_Trace      = 2U,
    IfxEmem_TileSts_Unused     = 3U
}IfxEmem_TileSts ;

#define  IFXEMEM_TILE_CAL             (IfxEmem_TileType_Cal)
#define  IFXEMEM_TILE_TRACE           (IfxEmem_TileType_Trace)
#define  IFXEMEM_TILE_UNUSED          (IfxEmem_TileType_Unused)
#define  IFXEMEM_TILE_CAL_BBB         (IfxEmem_TileType_Cal_Bbb)
#define  IFXEMEM_TILE_TRACE_BBB       (IfxEmem_TileType_Trace_Bbb)
#define  IFXEMEM_TILE_UNCHANGED       (IfxEmem_TileType_Unchanged)


uint32 IfxEd_EmemInit(void) ;
inline void IfxEd_DataOverlayCfg
( 
  uint32 cpu, 
  uint32 overlayMemory,
  uint32 overlayBlock,
  uint32 targetBaseAddr, 
  uint32 redirectedBaseAddr,
  uint32 overlayAddrMask
);
void IfxEd_DataOverlayEn(uint32 cpu) ;
void IfxEd_DataOverlayDis(uint32 cpu); 
#endif /* IFXEDMEM_H_ */
