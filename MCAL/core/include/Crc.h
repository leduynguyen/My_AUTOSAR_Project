/*-------------------------------- Arctic Core ------------------------------
 * Copyright (C) 2013, ArcCore AB, Sweden, www.arccore.com.
 * Contact: <contact@arccore.com>
 * 
 * You may ONLY use this file:
 * 1)if you have a valid commercial ArcCore license and then in accordance with  
 * the terms contained in the written license agreement between you and ArcCore, 
 * or alternatively
 * 2)if you follow the terms found in GNU General Public License version 2 as 
 * published by the Free Software Foundation and appearing in the file 
 * LICENSE.GPL included in the packaging of this file or here 
 * <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>
 *-------------------------------- Arctic Core -----------------------------*/

/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.2.2 */

#ifndef CRC_H_
#define CRC_H_


/* @req SWS_CRC_00018 */
/* @req SWS_CRC_00022 */
/* @req SWS_CRC_00024 */
#include "Std_Types.h"
#include "Modules.h"

/* This requirement is also applicable to users of the interface otherwise
 * set by the interface
 * @req SWS_CRC_00023
 */

/* @req SWS_CRC_00022 */
/* @req SWS_CRC_00023 */
#include "Crc_Cfg.h"
#include "Modules.h"

/* @req SWS_CRC_00048 */
/* @req SWS_CRC_00050 */
#define CRC_VENDOR_ID			    VENDOR_ID_ARCCORE
#define CRC_MODULE_ID               MODULE_ID_CRC
#define CRC_AR_MAJOR_VERSION        4u
#define CRC_AR_MINOR_VERSION        2u
#define CRC_AR_PATCH_VERSION        2u

#define CRC_SW_MAJOR_VERSION        1u
#define CRC_SW_MINOR_VERSION        0u
#define CRC_SW_PATCH_VERSION        0u


/* May be needed by CRC lib users since in order to create custom CRCs e.g.
 * used in the E2E lib
 */

/* For CRC 8*/
#define CRC8_START_VALUE        0xFFU
#define CRC8_XOR                0xFFU

/* For CRC8 H2F */
#define CRC8_H2F_START_VALUE    0xFFU
#define CRC8_H2F_XOR            0xFFU



/* These two applies to the caller and it set by the interface  */
/* @req SWS_CRC_00014 */
/* @req SWS_CRC_00041 */


/* @req SWS_CRC_00031 */
uint8  Crc_CalculateCRC8(const uint8* Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8, boolean Crc_IsFirstCall);

/* @req SWS_CRC_00042 */
uint8  Crc_CalculateCRC8H2F(const uint8* Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8, boolean Crc_IsFirstCall);

/* @req SWS_CRC_00019 */
uint16 Crc_CalculateCRC16(const uint8* Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16, boolean Crc_IsFirstCall);

/* @req SWS_CRC_00020 */
uint32 Crc_CalculateCRC32( const uint8* Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32, boolean Crc_IsFirstCall);

/* @req SWS_CRC_00058 */
uint32 Crc_CalculateCRC32P4( const uint8* Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32P4, boolean Crc_IsFirstCall);

/* @req SWS_CRC_00011 */
/* @req SWS_CRC_00017 */
/* @req SWS_CRC_00021 */
#if ( CRC_VERSION_INFO_API == STD_ON )
#define Crc_GetVersionInfo(_vi) STD_GET_VERSION_INFO(_vi,CRC)
#endif



#endif /* CRC_H_ */
