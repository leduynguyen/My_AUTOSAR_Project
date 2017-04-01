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

#ifndef CPU_H_
#define CPU_H_

#include <stdint.h>

#if defined(__ghs__)
#include "../include/arm/arm_ghs.h"
#endif


#if defined(CFG_ARMV7_M) || defined(CFG_ARMV7E_M)
#if   defined ( __CC_ARM )
  #define __ASM            __asm                                      /*!< asm keyword for ARM Compiler          */
  #define __INLINE         __inline                                   /*!< inline keyword for ARM Compiler       */
  #define __STATIC_INLINE  static __inline

#elif defined ( __ICCARM__ )
  #define __ASM            __asm                                      /*!< asm keyword for IAR Compiler          */
  #define __INLINE         inline                                     /*!< inline keyword for IAR Compiler. Only available in High optimization mode! */
  #define __STATIC_INLINE  static inline

#elif defined ( __GNUC__ )
  #define __ASM            __asm                                      /*!< asm keyword for GNU Compiler          */
  #define __INLINE         inline                                     /*!< inline keyword for GNU Compiler       */
  #define __STATIC_INLINE  static inline

#elif defined ( __TASKING__ )
  #define __ASM            __asm                                      /*!< asm keyword for TASKING Compiler      */
  #define __INLINE         inline                                     /*!< inline keyword for TASKING Compiler   */
  #define __STATIC_INLINE  static inline

#endif	/* defined ( __CC_ARM ) */

#include "core_cmInstr.h"

static inline unsigned long _Irq_Save(void)
{
   unsigned long val = __get_PRIMASK();
   __disable_irq();
   return val;
}


static inline void _Irq_Restore(unsigned mask) {
    __set_PRIMASK(mask);
}

/**
  * Initialize a system reset request to reset the MCU
  */
static __INLINE void Cpu_SystemReset(void)
{
  *(uint32_t *)(0xE000ED0C) = 0x05FA0004; /* First pull system reset */
  __DSB();                              /* Ensure completion of memory access */
  *(uint32_t *)(0xE000ED0C) = 0x05FA0001; /* If that does not work pull internal reset */
  __DSB();                              /* Ensure completion of memory access */
  while(1) ;                            /* wait until reset */
}

#elif defined(CFG_ARMV7_AR)

#if defined(__ARMCC_VERSION)
/* ARMCC have __disable_irq and __enable_irq builtin */
#else
static inline void __disable_irq( void ) {
  __asm volatile("CPSID if");
}
static inline void __enable_irq( void ) {
    __asm volatile("CPSIE if");
}
#endif

#if defined(__GNUC__) || defined(__ghs__)
static inline unsigned long _Irq_Save(void)
{
  unsigned long result=0;
  __asm volatile ("mrs %0, cpsr" : "=r" (result) );
 __disable_irq();
  return(result & 0xC0);
}

#else
static inline unsigned long _Irq_Save(void)
{
   uint32_t val;
   __asm volatile ("mrs val, cpsr");
   __asm volatile ("and val, val, #0xC0"); // Mask the I and F bit of CPSR
   __disable_irq();
   return val;
}
#endif	/* defined(__GNUC__) */

static inline void _Irq_Restore(unsigned mask) {
    if (mask & 0x80) {
        __asm volatile("CPSID i");
    } else {
        __asm volatile("CPSIE i");
    }
    if (mask & 0x40) {
        __asm volatile("CPSID f");
    } else {
        __asm volatile("CPSIE f");
    }
}

#else
#error No arch defined
#endif

#include "Std_Types.h"
typedef uint32 imask_t;

/* Call architecture specific code */
#define Irq_Disable()		__disable_irq()
#define Irq_Enable()		__enable_irq()

#define Irq_Save(_flags)     		_flags = (imask_t)_Irq_Save();
#define Irq_Restore(_flags)			_Irq_Restore(_flags);

#define Irq_SuspendAll() 	Irq_Disable()
#define Irq_ResumeAll() 	Irq_Enable()

#define Irq_SuspendOs() 	Irq_Disable()
#define Irq_ResumeOs() 		Irq_Enable()


#define CallService(index,param)

#if defined(__ARMCC_VERSION)
#define ilog2(_x)	((uint8)(32 - 1 - __builtin_clz(_x)))

static inline int ffs( uint32 val ) {
    return 32 - __builtin_clz(val & (-val));
}

#elif defined(__ghs__)
#define ilog2(_x)   ((uint8)(32 - 1 - __CLZ32(_x)))

#else
#define ilog2(x) ((uint8)(__builtin_ffs(x)-1))
#endif

#endif /* CPU_H_ */
