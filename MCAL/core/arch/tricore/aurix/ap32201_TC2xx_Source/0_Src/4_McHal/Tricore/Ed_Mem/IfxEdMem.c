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
#include "IfxEdMem.h"


#if (IFX_CFG_ED_DEVICE_SUPPORTED == STD_ON)
  extern uint32 IfxEmem_Tile_Cfg[IFXEMEM_MAX_NUM_TILES ] ;
#endif
  /* #if defined IFX_CFG_ED_DEVICE_SUPPORTED */


/******************************************************************************/
/*                           Function prototypes                              */
/******************************************************************************/


/******************************************************************************/
/*                           Functions                                         */
/******************************************************************************/
#if (IFX_CFG_DEVICE != IFX_CFG_TC24X )
/** \brief This initializes the ED Memory tiles, configures the tiles.
 *
 * \param None
 *
 * \return Success (0) / Failure (1) 
 *
 */
#if (IFX_CFG_ED_DEVICE_SUPPORTED == STD_ON)
uint32 IfxEd_EmemInit(void)
{
  uint32 index ;
  uint32 result;
  uint32 *tiles_cfg ;
  uint8 modify_tilecc;
  uint8 modify_tilect;
  uint32 tileconfig, tilecc, tilect;
  uint32 tilestate, tilestate_expected;
  
  result = 0U;     
  modify_tilecc  = 0U; 
  modify_tilect  = 0U;
  
  tiles_cfg = (uint32*)IfxEmem_Tile_Cfg[0] ;

  Ifx_EMEM* ememSfrsPtr;
  ememSfrsPtr = (Ifx_EMEM *) (EMEM_ADDRESS_BASE_SRI);  
  
  tileconfig = ememSfrsPtr->TILESTATE.U;
  /* Before re-assigning tiles have to be set to unused */
  for (index = 0U; index < IFXEMEM_MAX_NUM_TILES; index++)
  {
    if (*(tiles_cfg + index) != IfxEmem_TileType_Unchanged)
    {
      tileconfig = tileconfig | (IfxEmem_TileConfig_Unused << index * 2U);
    }
  }
  ememSfrsPtr->TILECONFIG.U = tileconfig;  
  
  /* Tiles are assumed to be in Un-Used Mode */
  for (index = 0U; index < IFXEMEM_MAX_NUM_TILES; index++)
  {
    if (*(tiles_cfg + index) != IfxEmem_TileType_Unchanged)
    {
      if ((*(tiles_cfg + index) == IfxEmem_TileType_Cal) || (*(tiles_cfg + index) == IfxEmem_TileType_Cal_Bbb))
      {
        tileconfig = (tileconfig & ~((0x3U) << index * 2U)) | ((IfxEmem_TileConfig_Cal) << index * 2U);
      }
      if ((*(tiles_cfg + index) == IfxEmem_TileType_Trace) || (*(tiles_cfg + index) == IfxEmem_TileType_Trace_Bbb))
      {
        tileconfig = (tileconfig & ~((0x3U) << index * 2U)) | ((IfxEmem_TileConfig_Trace) << index * 2U);
      }
      if (*(tiles_cfg + index) == IfxEmem_TileType_Unused)
      {
        tileconfig = (tileconfig & ~((0x3U) << index * 2U)) | ((IfxEmem_TileConfig_Unused) << index * 2U);
      }
    }/* if (*(tiles_cfg + index) != IfxEmem_Tile_Allocation_Unchanged) */
  }/* End of for loop */
  
  ememSfrsPtr->TILECONFIG.U = tileconfig;
  tilestate_expected = tileconfig;
  
  /* Tile mode setting */
  tilecc = 0U;
  tilect = 0U;
  
  for (index = 0U; index < IFXEMEM_MAX_NUM_TILES; index++)
  {
    if (*(tiles_cfg + index) != IfxEmem_TileType_Unchanged)
    {
      if (*(tiles_cfg + index) == IfxEmem_TileType_Cal_Bbb)
      {
        tilecc = (tilecc | (1U << index));
        tilestate_expected = (tilestate_expected & ~((0x3U)<<index * 2U))
                | ((IfxEmem_TileSts_Bbb) << index * 2U);
        modify_tilecc = 1U;        
      }
      if (*(tiles_cfg + index) == IfxEmem_TileType_Cal)
      {
        tilecc = (tilecc & ~(1U << index));
        tilestate_expected = (tilestate_expected & ~((0x3U)<<index * 2))
                | ((IfxEmem_TileSts_Cal) << index * 2U);
        modify_tilecc = 1U;        
      }
      
      if (*(tiles_cfg + index) == IfxEmem_TileType_Trace_Bbb)
      {
        tilect = (tilect | (1U << index));
        tilestate_expected = (tilestate_expected & ~(0x3U << index * 2U))
                | (IfxEmem_TileSts_Bbb << index * 2);                
        modify_tilect = 1U;          
      }
      if (*(tiles_cfg + index) == IfxEmem_TileType_Trace)
      {
        tilect = (tilect & ~(1U << index));
        tilestate_expected = (tilestate_expected & ~(0x3U << index * 2U))
                | (IfxEmem_TileSts_Trace << index * 2U);
        modify_tilect = 1U;          
      }
    }/* if (*(tiles_cfg + index) != IfxEmem_TileConfig_Unchanged) */
  }/* for loop */  
  
  /* Write values to TILECC, TILECT only when required */
  if (modify_tilecc)
  {	
    ememSfrsPtr->TILECC.U = tilecc;
  }
  if (modify_tilect)
  {	
    ememSfrsPtr->TILECT.U = tilect;
  }  
  
  EMEM_SBRCTR.B.ACGEN = 1U ;
  
  /* Tile configuration failed */
  tilestate = ememSfrsPtr->TILESTATE.U;
  if (tilestate != tilestate_expected)
  {
    result = 1U;
  }
  return result;  
}

/** \brief  function that configures the overlay blocks
 *
 * \param cpu
 * \param overlayMemory
 * \param overlayBlock : overlay block number
 * \param targetBaseAddr
 * \param redirectedBaseAddr
 * \param overlayAddrMask : refer 13.4 for overlay configuration
 *
 *
 * \return result
 *             - 0 : OVC is configured and enabled successfully.
 *			       - !=0 : error in configuration
 */
void IfxEd_DataOverlayCfg
( 
  uint32 cpu, 
  uint32 overlayMemory,
  uint32 overlayBlock,
  uint32 targetBaseAddr, 
  uint32 redirectedBaseAddr,
  uint32 overlayAddrMask
)
{
  /* pointer to OVC SFRs for each CPU */
  Ifx_OVC* ovcSfrs;
  uint32 oselData; 
  uint32 rabrData ;
  uint32 otarData ; 
  uint32 omaskData; 

  ovcSfrs   = (Ifx_OVC *) ( (OVC0_ADDRESS_BASE) + cpu * 0x20000 ) ;
  
  /* select bits [21:5] of address and provide overlayMemory */
  rabrData = (redirectedBaseAddr & IFXEMEM_OBASE_MASK) | ( overlayMemory << 24U);
  otarData = (targetBaseAddr & IFXEMEM_TBASE_MASK); 
  
  omaskData = (overlayAddrMask & IFXEMEM_OMASK_MASK);
  
  /* OVCx_RABRy */
  ovcSfrs->BLK[overlayBlock].RABR.U = (rabrData | 1U << 31U);
  /* OVCx_OTARy */
  ovcSfrs->BLK[overlayBlock].OTAR.U = otarData;
  /* OVCx_OMASKy */
  ovcSfrs->BLK[overlayBlock].OMASK.U = omaskData;  
  
  /* Shadow Overlay enable */
  oselData = ovcSfrs->OSEL.U;
  oselData |= (1U << overlayBlock);
  ovcSfrs->OSEL.U = oselData;
}

/** \brief  function that enables the overlay blocks and sets the global OVC enable for the
 * dedicated CPU. 
 * function that enables the overlay blocks and sets the global OVC enable for the
 * dedicated CPU 
 *
 * \param cpu number
 *
 * \return  result
 *             - 0 : No error in enabling OCDS
 */ 
void IfxEd_DataOverlayEn(uint32 cpu) 
{
  uint16 l_SEndInitPW; 
 
  /* Set SELx and OVSTRT to enable all overlay blocks for which 
     the shadow bit is set in OVC_OSEL.
     enable overlay for CPUx .
  */
  l_SEndInitPW = IfxScuWdt_getSafetyWatchdogPassword (); 
  IfxScuWdt_clearSafetyEndinit (l_SEndInitPW);

  if (0U == cpu)
  {
    SCU_OVCCON.U = ((1U << 16U) |(1 << 0U ));  /* 0x00010001 */;
    SCU_OVCENABLE.B.OVEN0 = 1U;
  }
  if (1U == cpu)
  {
    SCU_OVCCON.U = ((1U << 16U) |(1 << 1U ));   /* 0x00010002; */
    SCU_OVCENABLE.B.OVEN1 = 1U;
  }
  if (2U == cpu)
  {
    SCU_OVCCON.U = ((1U << 16U) |(1 << 2U ));  /* 0x00010004; */
    SCU_OVCENABLE.B.OVEN2 = 1U;
  }

  IfxScuWdt_setSafetyEndinit (l_SEndInitPW);;
}

/** \brief  function that disables the overlay blocks and clears the 
 * global OVC enable for the dedicated CPU. 
 *
 * function that disables the overlay blocks and clears the global OVC enable for the
 * dedicated CPU.
 *
 * \param cpu number
 *
 * \return  result
 *             - 0 : No error in enabling OCDS
 */ 
void IfxEd_DataOverlayDis(uint32 cpu)
{
  uint16 l_SEndInitPW; 
  
  /* set SELx and OVSTOP to disable all overlay blocks
     disable overlay for CPUx
  */   
  l_SEndInitPW = IfxScuWdt_getSafetyWatchdogPassword (); 
  IfxScuWdt_clearSafetyEndinit (l_SEndInitPW);

  if (0U == cpu)
  {
    SCU_OVCCON.U = ((1U << 17U) |(1 << 0U ));  /* 0x00020001; */
    SCU_OVCENABLE.B.OVEN0 = 0U;
  }
  if (1U == cpu)
  {
    SCU_OVCCON.U = ((1U << 17U) |(1 << 1U ));  /* 0x00020002; */
    SCU_OVCENABLE.B.OVEN1 = 0U;
  }
  if (2U == cpu)
  {
    SCU_OVCCON.U = ((1U << 17U) |(1 << 2U ));  /* 0x00020004; */
    SCU_OVCENABLE.B.OVEN2 = 0U;
  }
  IfxScuWdt_setSafetyEndinit (l_SEndInitPW);;
}
#endif
   /* #if defined IFX_CFG_ED_DEVICE_SUPPORTED */
#endif
  /* #if (IFX_CFG_DEVICE != IFX_CFG_TC24X ) */
