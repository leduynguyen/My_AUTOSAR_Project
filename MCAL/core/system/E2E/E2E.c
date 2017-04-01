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

/* @req SWS_E2E_00115 */
/* @req SWS_E2E_00216 */

#define E2E_AR_MAJOR_VERSION_INT        4
#define E2E_AR_MINOR_VERSION_INT        2
#define E2E_AR_PATCH_VERSION_INT        2

#define E2E_SW_MAJOR_VERSION_INT        1
#define E2E_SW_MINOR_VERSION_INT        0

#include "E2E.h"

/* @req SWS_E2E_00327 */
#if (E2E_SW_MAJOR_VERSION != E2E_SW_MAJOR_VERSION_INT) || (E2E_SW_MINOR_VERSION != E2E_SW_MINOR_VERSION_INT)
#error "SW Version mismatch between E2E.c and E2E.h"
#endif

#if (E2E_AR_MAJOR_VERSION != E2E_AR_MAJOR_VERSION_INT) || (E2E_AR_MINOR_VERSION != E2E_AR_MINOR_VERSION_INT) || \
    (E2E_AR_PATCH_VERSION != E2E_AR_PATCH_VERSION_INT)
#error "AR Version mismatch between E2E.c and E2E.h"
#endif



/* @req SWS_E2E_00099 */ //ASR4.0.3, obsolete for ASR4.2.2, shall be removed is backwards compatibility is skipped
/* @req SWS_E2E_00075 */
uint8 E2E_UpdateCounter(uint8 Counter) {
    return (Counter+1) % 15; /* Use the Profile 1 value */
}


/* @req SWS_E2E_00091 */
/* @req SWS_E2E_00092 */
uint8 E2E_CRC8u8(uint8 E2E_Data, uint8 E2E_StartValue) {
    /* Need to cancel XOR in start and end of the Crc Function since E2E has XOR=0x00 */
    return Crc_CalculateCRC8(&E2E_Data, sizeof(E2E_Data), E2E_StartValue ^ CRC8_XOR, FALSE) ^ CRC8_XOR;
}


/* @req SWS_E2E_00091 */
/* @req SWS_E2E_00092 */
uint8 E2E_CRC8u16(uint16 E2E_Data, uint8 E2E_StartValue) {
    /* Support for both little and big endian */
    uint8 data[2] = { (uint8)(E2E_Data & 0xFFu), (uint8)(E2E_Data >> 8)};
    /* Need to cancel XOR in start and end of the Crc Function since E2E has XOR=0x00 */
    return Crc_CalculateCRC8(data, sizeof(E2E_Data), E2E_StartValue ^ CRC8_XOR, FALSE) ^ CRC8_XOR;
}

/* @req SWS_E2E_00091 */
/* @req SWS_E2E_00092 */
uint8 E2E_CRC8u32(uint32 E2E_Data, uint8 E2E_StartValue) {
    /* Support for both little and big endian */
    uint8 data[4] = {(uint8)(E2E_Data & 0xFFu), (uint8)((E2E_Data >> 8) & 0xFFu),
                     (uint8)((E2E_Data >> 16) & 0xFFu), (uint8)(E2E_Data >> 24)};
    /* Need to cancel XOR in start and end of the Crc Function since E2E has XOR=0x00 */
    return Crc_CalculateCRC8(data, sizeof(E2E_Data), E2E_StartValue ^ CRC8_XOR, FALSE) ^ CRC8_XOR;
}

/* @req SWS_E2E_00094 */
/* @req SWS_E2E_00095 */
uint8 E2E_CRC8u8Array(const uint8* E2E_DataPtr, uint32 E2E_ArrayLength, uint8 E2E_StartValue) {
    /* Need to cancel XOR in start and end of the Crc Function since E2E has XOR=0x00 */
    return Crc_CalculateCRC8(E2E_DataPtr, E2E_ArrayLength, E2E_StartValue ^ CRC8_XOR, FALSE) ^ CRC8_XOR;
}

/* @req SWS_E2E_00094 */
/* @req SWS_E2E_00095 */
uint8 E2E_CRC8u16Array(const uint16* E2E_DataPtr, uint32 E2E_ArrayLength, uint8 E2E_StartValue) {

    /* Supports for both little and big endian by making in endianess idependant */

    uint8 crc = E2E_StartValue;

    for (uint32 i=0;i<E2E_ArrayLength;i++) {
        crc = E2E_CRC8u16(*E2E_DataPtr, crc);
        E2E_DataPtr++;
    }

    return crc;

}

/* @req SWS_E2E_00094 */
/* @req SWS_E2E_00095 */
uint8 E2E_CRC8u32Array(const uint32* E2E_DataPtr, uint32 E2E_ArrayLength, uint8 E2E_StartValue) {

    /* Supports for both little and big endian by making in endianess idependant */

    uint8 crc = E2E_StartValue;

    for (uint32 i=0;i<E2E_ArrayLength;i++) {
        crc = E2E_CRC8u32(*E2E_DataPtr, crc);
        E2E_DataPtr++;
    }

    return crc;
}

/* @req SWS_E2E_00096 */
/* @req SWS_E2E_00276 */
uint8 E2E_CRC8H2Fu8(uint8 E2E_Data, uint8 E2E_StartValue) {
    return Crc_CalculateCRC8H2F(&E2E_Data, sizeof(E2E_Data), E2E_StartValue, FALSE);
}

/* @req SWS_E2E_00096 */
/* @req SWS_E2E_00276 */
uint8 E2E_CRC8H2Fu16(uint16 E2E_Data, uint8 E2E_StartValue) {
    /* Support for both little and big endian */
    uint8 data[2] = { (uint8)(E2E_Data & 0xFFu), (uint8)(E2E_Data >> 8)};
    return Crc_CalculateCRC8H2F(data, sizeof(E2E_Data), E2E_StartValue, FALSE);
}

/* @req SWS_E2E_00096 */
/* @req SWS_E2E_00276 */
uint8 E2E_CRC8H2Fu32(uint32 E2E_Data, uint8 E2E_StartValue) {
    /* Support for both little and big endian */
    uint8 data[4] = {(uint8)(E2E_Data & 0xFFu), (uint8)((E2E_Data >> 8) & 0xFFu),
                     (uint8)((E2E_Data >> 16) & 0xFFu), (uint8)(E2E_Data >> 24)};
    return Crc_CalculateCRC8H2F(data, sizeof(E2E_Data), E2E_StartValue, FALSE);
}


/* @req SWS_E2E_00097 */
/* @req SWS_E2E_00098 */
uint8 E2E_CRC8H2Fu8Array(const uint8* E2E_DataPtr, uint32 E2E_ArrayLength, uint8 E2E_StartValue) {
    return Crc_CalculateCRC8H2F(E2E_DataPtr, E2E_ArrayLength, E2E_StartValue, FALSE);
}


/* @req SWS_E2E_00097 */
/* @req SWS_E2E_00098 */
uint8 E2E_CRC8H2Fu16Array(const uint16* E2E_DataPtr, uint32 E2E_ArrayLength, uint8 E2E_StartValue) {

    /* Supports for both little and big endian by making in endianess idependant */

    uint8 crc = E2E_StartValue;

    for (uint32 i=0;i<E2E_ArrayLength;i++) {
        crc = E2E_CRC8H2Fu16(*E2E_DataPtr, crc);
        E2E_DataPtr++;
    }

    return crc;

}


/* @req SWS_E2E_00097 */
/* @req SWS_E2E_00098 */
uint8 E2E_CRC8H2Fu32Array(const uint32* E2E_DataPtr, uint32 E2E_ArrayLength, uint8 E2E_StartValue) {

    /* Supports for both little and big endian by making in endianess idependant */

    uint8 crc = E2E_StartValue;

    for (uint32 i=0;i<E2E_ArrayLength;i++) {
        crc = E2E_CRC8H2Fu32(*E2E_DataPtr, crc);
        E2E_DataPtr++;
    }

    return crc;

}

