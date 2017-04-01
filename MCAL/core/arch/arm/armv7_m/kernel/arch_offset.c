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

#include <stddef.h>
#include <stdint.h>

#define DECLARE(_sym,_val) \
    __asm("#define " #_sym " %0 ": : "i" (_val))


#include "arch_stack.h"

void  arch_foo(void) {
    /* StackNvgprType */
    DECLARE(STACK_NVGPR_R4,		offsetof(StackNvgprType, r4));
    DECLARE(STACK_NVGPR_R5,		offsetof(StackNvgprType, r5));
    DECLARE(STACK_NVGPR_R6,		offsetof(StackNvgprType, r6));
    DECLARE(STACK_NVGPR_R7,		offsetof(StackNvgprType, r7));
    DECLARE(STACK_NVGPR_R8,		offsetof(StackNvgprType, r8));
    DECLARE(STACK_NVGPR_R10,	offsetof(StackNvgprType, r10));
    DECLARE(STACK_NVGPR_R11,	offsetof(StackNvgprType, r11));
    DECLARE(STACK_NVGPR_VA,	offsetof(StackNvgprType, va));

    /* StackCallAndContextType */
}



