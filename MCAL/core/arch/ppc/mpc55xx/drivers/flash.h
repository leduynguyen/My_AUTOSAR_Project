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

/*
 * flash.h
 *
 *  Created on: 29 aug 2011
 *      Author: mahi
 */

#ifndef FLASH_H_
#define FLASH_H_

#include "Fls.h"
#include "flash_ll_h7f_c90.h"

#define FLASH_OP_LOCK               0uL
#define FLASH_OP_UNLOCK             1uL
#define FLASH_OP_MASK               1uL

#define ADDR_SPACE_CNT              4u
#define ADDR_SPACE_LOW              0u
#define ADDR_SPACE_MID              1u
#define ADDR_SPACE_HIGH             2u
#define ADDR_SPACE_LARGE            3u
#define SECTOR_EMPTY                0xffffu
#define ADDR_SPACE_GET(_x)          (((_x)>>8uL)&3uL)
#define ADDR_SPACE_SET(_x)          (((_x)&3uL)<<8uL)
#define ADDR_SPACE_GET_SECTOR(_x)   ((_x) & 0xffuL )
#define ADDR_SPACE_GET_PART(_x)     (((_x)>>10uL)& 15uL)
#define ADDR_SPACE_SET_PART(_x)     (((_x)& 15uL)<<10uL)

#define ADDR_SPACE(_sector,_space,_partition)	     \
                    ( ADDR_SPACE_SET_PART(_partition) | \
                     ADDR_SPACE_SET(_space ) | (_sector) )

struct Flash;  /*lint !e763 Redundant desclaration justified to preserve AUTOSAR include structure  */


typedef void (*flashCbType)( void );

void Flash_Init( void );
void Flash_Lock(const struct Flash *fPtr, uint32 op, const Fls_AddressType from, uint32 size);
uint32 Flash_Erase(const struct Flash *fPtr, Fls_AddressType dest, uint32 size, flashCbType sb);
uint32 Flash_ProgramPageStart(const struct Flash *fPtr, uint32 *to, uint32 *from,uint32 *size, flashCbType sb);
uint32 Flash_CheckStatus( const struct Flash *fPtr, const uint32 *to, uint32 size );
uint32 Flash_SectorAligned( const struct Flash *fPtr, Fls_AddressType addr );

#endif /* FLASH_H_ */
