/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 © Copyright 2009-2012 Texas Instruments Incorporated.  All rights reserved.
 *
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *      Project:  Hercules™ ARM® Safety MCUs - F021 Flash API 
 *      Version:  v2.01.01 Build(000830)                                                                                
 *   Build Date:  2014-10-21                                                                                            
 *
 *         File:  Registers.h                                                                                           
 *
 *  Description:  A complete mapping of the F021 Flash Registers facilitating named access to the F021 Flash Registers.
 *                This file will select the appropriate definitions based on selected compile Endianness.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  John R Hall
 *---------------------------------------------------------------------------------------------------------------------
 *
 *********************************************************************************************************************/


#ifndef REGISTERS_H_
#define REGISTERS_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
/*LDRA_NOANALYSIS*/
/*LDRA_INSPECTED 42 S MR: 3.5 "Necessary for FMC register definitions" */
/*LDRA_INSPECTED 74 S MR: 18.4 "Necessary for FMC register definitions" */
#if defined(_LITTLE_ENDIAN)
    #include "Registers_FMC_LE.h"
#else    
    #include "Registers_FMC_BE.h"
#endif
/*LDRA_ANALYSIS*/

/* Certain non released devices did not contain this information in the FMC */
#if defined(_BIG_ENDIAN) && defined(__TI_TMS470_V7M3__)
   #define WIDTH_MAIN_BANK 0x10U;
   #define WIDTH_MAIN_ECC 0x2U;
   #define WIDTH_EEPROM_BANK 0x10U;
   #define WIDTH_EEPROM_ECC 0x2U;
#else
   /* Macro to get the width of the Data on Main Banks */
   #define WIDTH_MAIN_BANK   ((uint8_t)(( (uint32_t)FLASH_CONTROL_REGISTER->FcfgBank.FCFG_BANK_BITS.MAIN_BANK_WIDTH \
                             & (uint32_t)0x1C0U) >> 3U))
   /* Macro to get the width of the ECC on Main Banks */
   #define WIDTH_MAIN_ECC    ((uint8_t)(( (uint32_t)FLASH_CONTROL_REGISTER->FcfgBank.FCFG_BANK_BITS.MAIN_BANK_WIDTH  \
                             & (uint32_t)0x038U) >> 3U))
   /* Macro to get the width of the Data on EEPROM Bank */
   #define WIDTH_EEPROM_BANK ((uint8_t)(( (uint32_t)FLASH_CONTROL_REGISTER->FcfgBank.FCFG_BANK_BITS.EE_BANK_WIDTH \
                             & (uint32_t)0x0C0U) >> 3U))
   /* Macro to get the width of the ECC on EEPROM Bank */
   #define WIDTH_EEPROM_ECC  ((uint8_t)(( (uint32_t)FLASH_CONTROL_REGISTER->FcfgBank.FCFG_BANK_BITS.EE_BANK_WIDTH \
                             & (uint32_t)0x018U) >> 3U))
#endif

/* Typedef pointer to Fapi_FmcRegistersType */
typedef Fapi_FmcRegistersType* pFapi_FmcRegistersType;

/* Typedef byte pointer to FWPWRITEx Registers */
typedef volatile uint8_t  FwpWriteByteAccessorType;
/* Typedef dword pointer to FWPWRITEx Registers */
typedef volatile uint32_t FwpWriteDWordAccessorType;

/* Offset from FMC base address to the start of the FWPWRITEx registers */
#define FWP_WRITE_OFFSET 0x120U
/* Macro that creates a byte accessor pointer to the FWPWRITEx registers */
#define FWPWRITE_BYTE_ACCESSOR_ADDRESS ((FwpWriteByteAccessorType*)(F021_CPU0_REGISTER_ADDRESS + 0x120U))
/* Macro that creates a byte accessor pointer to the FWPWRITE_ECC register */
#define FWPWRITE_ECC_BYTE_ACCESSOR_ADDRESS ((FwpWriteByteAccessorType*)(F021_CPU0_REGISTER_ADDRESS + 0x140U))
/* Macro that creates a dword accessor pointer to the FWPWRITEx registers */
#define FWPWRITE_DWORD_ACCESSOR_ADDRESS ((FwpWriteDWordAccessorType*)(F021_CPU0_REGISTER_ADDRESS + 0x120U))

/* Macro that creates an object pointer to the start of the FMC registers */
#define FLASH_CONTROL_REGISTER ((pFapi_FmcRegistersType)(F021_CPU0_REGISTER_ADDRESS))

/* Macro that defines the base address for the FMC registers structure */
#define F021_CPU0_BASE_ADDRESS ((Fapi_FmcRegistersType*)F021_CPU0_REGISTER_ADDRESS)

#endif /* REGISTERS_H_ */

/**********************************************************************************************************************
 *  END OF FILE: Registers.h
 *********************************************************************************************************************/
