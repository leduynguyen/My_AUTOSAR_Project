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

#ifndef E2E_H_
#define E2E_H_


/* @req SWS_E2E_00017 */
/* @req SWS_E2E_00037 */
/* @req SWS_E2E_00048 E2E_SM.c and E2E_SM.h still missing */
/* @req SWS_E2E_00110 */
/* @req SWS_E2E_00115 */
/* @req SWS_E2E_00050 Safety-related reviews still to be done depending on ASIL-Level */
/* @req SWS_E2E_00311 Safety-related reviews still to be done depending on ASIL-Level */
#include "Crc.h"
#include "Std_Types.h"
#include "Platform_Types.h"
#include "MemMap.h"
#include "Modules.h"


/* @req SWS_E2E_00011 */
/* @req SWS_E2E_00047 */
/* Return values used by the E2E module */
#define E2E_E_INPUTERR_NULL     0x13 //ASR4.0.3 and ASR4.2.2, At least one pointer parameter is a NULL pointer
#define E2E_E_INPUTERR_WRONG    0x17 //ASR4.0.3 and ASR4.2.2, At least one input parameter is erroneous, e.g. out of range
#define E2E_E_INTERR            0x19 //ASR4.0.3 and ASR4.2.2, An internal library error has occurred (e.g. error detected by program flow monitoring, violated invariant or postcondition)
#define E2E_E_OK                0x00 //ASR4.0.3 and ASR4.2.2, Function completed successfully
#define E2E_E_WRONGSTATE        0x1A //ASR4.2.2, Function executed in wrong state


/* @req SWS_E2E_00099 */ //ASR4.0.3, obsolete for ASR4.2.2, shall be removed is backwards compatibility is skipped
uint8 E2E_UpdateCounter(uint8 Counter);


/*  General CRC functions */


/* @req SWS_E2E_00091 */
/* @req SWS_E2E_00092 */


/* The spec is a bit unclear whether the final XOR used in CRC module shall
 * be removed or not. It is concluded that it is different between CRC8 and
 * CRC8H2F.
 *
 * CRC8:
 * The description of E2E0092 clearly states that "The function uses SAE J1850
 * polynomial, but with 0x00 as start value and XOR value." It is reasonable in
 * order to make it compatibility between AR3 and AR4. This means that if making
 * the CRC in multiple calls, there is no need to XOR the after each call.
 *
 * CRC8H2F:
 * For the CRC8H2F this is not the case, it was introduced in AR4 and it is
 * necessary to XOR the result after each call. Clearly described in E2E0096.
 */
uint8 E2E_CRC8u8(uint8 E2E_Data, uint8 E2E_StartValue);
uint8 E2E_CRC8u16(uint16 E2E_Data, uint8 E2E_StartValue);
uint8 E2E_CRC8u32(uint32 E2E_Data, uint8 E2E_StartValue);


/* @req SWS_E2E_00094 */
/* @req SWS_E2E_00095 */
uint8 E2E_CRC8u8Array(const uint8* E2E_DataPtr, uint32 E2E_ArrayLength, uint8 E2E_StartValue);
uint8 E2E_CRC8u16Array(const uint16* E2E_DataPtr, uint32 E2E_ArrayLength, uint8 E2E_StartValue);
uint8 E2E_CRC8u32Array(const uint32* E2E_DataPtr, uint32 E2E_ArrayLength, uint8 E2E_StartValue);


/* @req SWS_E2E_00096 */
/* @req SWS_E2E_00276 */
uint8 E2E_CRC8H2Fu8(uint8 E2E_Data, uint8 E2E_StartValue);
uint8 E2E_CRC8H2Fu16(uint16 E2E_Data, uint8 E2E_StartValue);
uint8 E2E_CRC8H2Fu32(uint32 E2E_Data, uint8 E2E_StartValue);


/* @req SWS_E2E_00097 */
/* @req SWS_E2E_00098 */
uint8 E2E_CRC8H2Fu8Array(const uint8* E2E_DataPtr, uint32 E2E_ArrayLength, uint8 E2E_StartValue);
uint8 E2E_CRC8H2Fu16Array(const uint16* E2E_DataPtr, uint32 E2E_ArrayLength, uint8 E2E_StartValue);
uint8 E2E_CRC8H2Fu32Array(const uint32* E2E_DataPtr, uint32 E2E_ArrayLength, uint8 E2E_StartValue);


/* @req SWS_E2E_00032 */
/* @req SWS_E2E_00038 */
#define E2E_VENDOR_ID               60
#define E2E_MODULE_ID               MODULE_ID_E2E
#define E2E_AR_MAJOR_VERSION        4
#define E2E_AR_MINOR_VERSION        2
#define E2E_AR_PATCH_VERSION        2

#define E2E_SW_MAJOR_VERSION        1
#define E2E_SW_MINOR_VERSION        0
#define E2E_SW_PATCH_VERSION        0


/* @req SWS_E2E_00032 */
/* @req SWS_E2E_00033 */
#define E2E_GetVersionInfo(_vi) STD_GET_VERSION_INFO(_vi,E2E)


#endif
