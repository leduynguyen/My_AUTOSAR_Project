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
 *         File:  Constants.h                                                                                           
 *
 *  Description:  A set of Constant Values used by the Flash Memory Controller.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  John R Hall
 *---------------------------------------------------------------------------------------------------------------------
 *
 *********************************************************************************************************************/


#ifndef CONSTANTS_H_
#define CONSTANTS_H_

/* Specifies the bit mask for determining all address bits exclusive of the offest
   imposed by the memory map register */
#define F021_PROGRAM_ADDRESS_MASK    0x07FFFFFFU

/* Specifies the Offset to the TI OTP */
#define F021_PROGRAM_TIOTP_OFFSET    0xF0080000U

/* FMC memory map defines */
#define F021_FLASH_MAP_BEGIN     0x00000000U
#define F021_FLASH_MAP_END       0x00FFFFFFU
#define F021_OTP_MAP_BEGIN       0xF0000000U
#define F021_OTP_MAP_END         0xF000FFFFU
#define F021_OTPECC_MAP_BEGIN    0xF0040000U
#define F021_OTPECC_MAP_END      0xF0041FFFU
#define F021_EEPROMECC_MAP_BEGIN 0xF0100000U
#define F021_EEPROMECC_MAP_END   0xF01FFFFFU
#define F021_EEPROM_MAP_BEGIN    0xF0200000U
#define F021_EEPROM_MAP_END      0xF03FFFFFU
#define F021_FLASHECC_MAP_BEGIN  0xF0400000U
#define F021_FLASHECC_MAP_END    0xF04FFFFFU

#define F021_CPU0_REGISTER_ADDRESS 0xFFF87000U

/* Specific TI OTP Offsets */
#define F021_TIOTP_PER_BANK_SIZE 0x2000U
#define F021_TIOTP_SETTINGS_BASE 0x150U
#define F021_TIOTP_BANK_SECTOR_OFFSET 0x158U

/* Define to map the direct access to the TI OTP memory */
#define F021_TIOTP_BASE_ADDRESS ((Fapi_TiOtpBytesType *)(F021_PROGRAM_TIOTP_OFFSET + F021_TIOTP_SETTINGS_BASE))

#define F021_MINIMUM_HCLK_FREQUENCY 10U

#endif /* CONSTANTS_H_ */

/**********************************************************************************************************************
 *  END OF FILE: Constants.h
 *********************************************************************************************************************/
