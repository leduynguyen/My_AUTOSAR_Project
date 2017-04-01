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

/* ----------------------------[includes]------------------------------------*/


#include "Std_Types.h"
#include "Mcu.h"
#include "core_cr4.h"
#include "MemMap.h"
#if defined(USE_FEE)
#include "Fee_Memory_Cfg.h"
#endif
#if defined(USE_DMA)
#include "Dma.h"
#endif
#include "asm_arm.h"
#include "Os.h"
#include "arc.h"

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

/**
 * Called by lower level exception handlers and tries to handle
 * the exception.
 *
 * @param exceptionVector The exception vector.
 * @return
 */
uint32_t Cpu_ExceptionHandler(uint32_t exceptionVector) {
	uint32 rv = EXC_NOT_HANDLED;
	uint32 far;
	uint32 fsr;
	uint16 status;

//	Mpc5xxx_vectorMask |= (1<<exceptionVector);

	/* The MPU can generate
	 * - Background fault
	 * - Permission fault
	 * - Alignment fault
	 *
	 * and generates a prefetch or data abort.
	 */

	switch (exceptionVector) {
	    case EXC_PREFETCH_ABORT:

	        /* IFSR */
            fsr = CoreGetIFSR();
	        far = CoreGetIFAR();

	        (void)far;
	        (void)fsr;

	        break;
	    case EXC_DATA_ABORT:
	        /* DFSR */
	        fsr = CoreGetDFSR();
	        far = CoreGetDFAR();

	        status = (uint16)((fsr & 0xfUL) & ((fsr >> 7U) & 0x10UL));

	        /* Check for MMU things */
	        if( (status == 0x1U) || (status == 0x0U) || (status == 0xdU) ) {
	            rv = EXC_NOT_HANDLED | EXC_ADJUST_ADDR;
	        }

	        break;
        case EXC_UNDEFINED_INSTRUCTION:
            /* flow down */
	    case EXC_SVC_CALL:
	        /* flow down */
	    default:
	        break;
	}

	return rv;
}


