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



#ifndef CPU_H
#define CPU_H

#include "Std_Types.h"
#include "machine/intrinsics.h"

typedef uint32_t imask_t;

#define STR__(x)	#x
#define STRINGIFY__(x) STR__(x)

#define Irq_Save(flags)		flags = _Irq_Disable_save()
#define Irq_Restore(flags)	_Irq_Disable_restore(flags)

#define Irq_Disable()		_disable();
#define Irq_Enable()		_enable();

#define Irq_SuspendAll() 	Irq_Disable()
#define Irq_ResumeAll() 	Irq_Enable()

#define Irq_SuspendOs() 	Irq_Disable()
#define Irq_ResumeOs() 		Irq_Enable()


/**
 * Integer log2
 *
 * Examples:
 * - ilog2(0x0) = -1
 * - ilog2(0x1) = 0
 * - ilog2(0x2) = 1
 * - ilog2(0x8000_0000)=31
 *
 * @param val
 * @return
 */
static inline uint8 ilog2( uint32 val ) {
//    return sch1r(val) - 1;
    return 0;
}


static inline unsigned long _Irq_Disable_save(void)
{
    unsigned long result = _mfcr(0xFE2C);   /* CPU_ICR */
    Irq_Disable();
    return result;
}


static inline void _Irq_Disable_restore(unsigned long flags) {
    if( flags & 0x8000 ) {
        Irq_Enable();
    } else {
        Irq_Disable();
    }
    /* restore PSW */
//	asm volatile(" ldsr %0,PSW" : : "r" (flags) );
}


#endif /* CPU_H */
