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

#ifndef QSPI_ZYNQ_H_
#define QSPI_ZYNQ_H_

/***************************** Include Files *********************************/
#include "Std_Types.h"

/************************** Constant Definitions *****************************/

#define FLASH_SECTOR_SIZE		0x10000u
#define FLASH_NUM_SECTORS		0x100u
#define FLASH_MAX_SECTORS		(FLASH_NUM_SECTORS - 1)
#define FLASH_NUM_PAGES			0x10000u
#define FLASH_PAGE_SIZE			0x100u
#define FLS_TOTAL_SIZE			(FLASH_NUM_PAGES * FLASH_PAGE_SIZE)

#define HEADER_SIZE		4 			/* Size of header(commands and address) in the buffer */
#define DUMMY_RD_BYTES	1 			/* Dummy bytes after read*/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

Std_ReturnType QspiIf_Arc_Erase(uint32 address, uint32 bytecnt);

Std_ReturnType QspiIf_Arc_Write(uint32 address, uint32 bytecnt);

Std_ReturnType QspiIf_Arc_Read(uint32 address, uint32 bytecnt);

Std_ReturnType QspiIf_Arc_Fast_Read(uint32 address, uint32 bytecnt);

Std_ReturnType QspiIf_Arc_LQSPI_Read(uint32 address, uint32 bytecnt);

void QspiIf_Arc_Init(void);

/************************** Variable Definitions *****************************/


#endif /* QSPI_ZYNQ_H_ */
