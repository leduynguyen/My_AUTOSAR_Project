/**
 * \file IfxMtu_Cfg.h
 * \brief Driver configuration(memory)
 *
 * \license
 * You can use this file under the terms of the IFX License.
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the IFX License for more details (IFX_License.txt).
 *
 * This file may be used, copied, and distributed, with or without modification, provided
 * that all copyright notices are retained; that all modifications to this file are
 * prominently noted in the modified file; and that this paragraph is not modified.
 *
 * \copyright Copyright (C) 2013 Infineon Technologies AG
 * \author Puneetha Mukherjee <puneetha.mukherjee@infineon.com>
 *
 * $Revision: 001 $
 * $Date: 24-05-2013 12:09 +0530 $
 *
 * \defgroup Ifx Infineon Software
 * \defgroup Ifx_Lld Infineon Low Level Drivers' Software
 * \ingroup I
 */ 
/******************************************************************************/
#ifndef IFXMTU_CFG_H
#define IFXMTU_CFG_H

/******************************************************************************/
/*                           Includes                                         */
/******************************************************************************/
#ifndef IFX_CFG_USE_COMPILER_DEFAULT_LINKER

/******************************************************************************/
/*                           Macros                                           */
/******************************************************************************/
/*lint -e46 */
#include "IfxMc_reg.h"
#include "IfxMtu_reg.h"
/*lint -restore*/
/* Define / Undefine the Below Macros for supporting 
   the different RAM tests, if not needed set to STD_OFF 
*/   
#define IFXMTU_NON_DES_TEST_USED     (STD_ON)

/* MTU addressing is 1K depth resolution */
/* #define IFXMTU_ADDRESS_DSPR_1K */
/* define IFXMTU_ADDRESS_PSPR_1K */

/* Configuration parameter defining the Total number of RAM sectors */
#define IFXSTART_NUM_RAM_SECTIONS    (BIOS_NUM_SEG_CPU0 + BIOS_NUM_SEG_CPU1 + BIOS_NUM_SEG_CPU2)

/* RAM Test initialization data */ 
#define IFXSTART_RAM_TEST_INIT_DATA     (0U)
#if (IFXSTART_RAM_TEST_INIT_DATA == 0)
  #define IFXSTART_ECC_DATA                 (3)
#elif (IFXSTART_RAM_TEST_INIT_DATA == (0xffffU))
  #define IFXSTART_ECC_DATA                 (0x3C)
#else
  #error "Not Supported Init Data"
#endif

#define IFXSTART_MTU_NON_DES_TEST       (1U)

/* Memory Controller Numbers */
#define IFXSTART_CPU2_DSPR              (0U)
#define IFXSTART_CPU2_DCACHE            (1U)
#define IFXSTART_CPU2_DTAG              (2U)
#define IFXSTART_CPU2_PSPR              (3U)
#define IFXSTART_CPU2_PCACHE            (4U)
#define IFXSTART_CPU2_PTAG              (5U)
#define IFXSTART_CPU1_DSPR              (6U)
#define IFXSTART_CPU1_DCACHE            (7U)
#define IFXSTART_CPU1_DTAG              (8U)
#define IFXSTART_CPU1_PSPR              (9U)
#define IFXSTART_CPU1_PCACHE            (10U)
#define IFXSTART_CPU1_PTAG              (11U)
#define IFXSTART_CPU0_DSPR              (14U)
#define IFXSTART_CPU0_PCACHE            (15U)
#define IFXSTART_CPU0_PSPR              (16U)
#define IFXSTART_CPU0_PTAG              (17U)

/* Range enable */
#define IFXSTART_RANGE_ENABLE           (1U)
#define IFXSTART_RANGE_DISBLE           (0U)

/* Data type for RAM Test  configuration */
typedef struct IfxStart_RamTestCfgType
{
  /* Absolute Start address    */
  uint32      SegStart_Address;
  /* Absolute End address    */
  uint32      SegEnd_Address;
  /* Start Address of the Segment */
  uint8       SegStart;
  /* End Address of the Segment */
  uint8       SegEnd;
  /* RAM Test Type */
  uint8       RamTstType;
  /* Mbist Controller Number */
  uint8       MbistNumber;
  /* Range Low Address */
  uint8       ClrSeg;
} IfxStart_RamTestCfgType;

#endif 
  /*#ifndef IFX_CFG_USE_COMPILER_DEFAULT_LINKER */
#endif 
  /* IFXMTU_CFG_H */
