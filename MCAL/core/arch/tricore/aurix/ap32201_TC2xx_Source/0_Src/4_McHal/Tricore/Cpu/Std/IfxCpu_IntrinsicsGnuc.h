/**
 * \file IfxCpu_IntrinsicsGnuc.h
 * \version iLLD_0_1_0_6
 * \copyright Copyright (c) 2012 Infineon Technologies AG. All rights reserved.
 *
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * \defgroup IfxLld_Cpu_Intrinsics_Gnuc Intrinsics for GNU compiler
 * \ingroup IfxLld_Cpu_Intrinsics
 *
 */

#ifndef IFXCPU_INTRINSICSGNUC_H
#define IFXCPU_INTRINSICSGNUC_H


/* old style intrinsics handling for AGENtiX environment */
#if defined(SCTB_EMBEDDED)
# define IFXCPU_INTRINSICSGNUC_USE_MACHINE_INTRINSICS 0
#else
# define IFXCPU_INTRINSICSGNUC_USE_MACHINE_INTRINSICS 1
#endif

/******************************************************************************/
#include "Ifx_Types.h"

#if IFXCPU_INTRINSICSGNUC_USE_MACHINE_INTRINSICS
//MAHI#include "C:\HIGHTEC\toolchains\tricore\v4.6.4.0\tricore\include\machine\intrinsics.h"
#include "machine/intrinsics.h"
#endif

/******************************************************************************/
/* *INDENT-OFF* */
#define STRINGIFY(x)    #x

/** Function call without return
 */
#define __non_return_call(fun)	__asm__ volatile ("ja "#fun)

/** Jump and link
 */
/*
IFX_INLINE void __jump_and_link(void (*fun)(void))
{
    __asm__ volatile ("jli %0"::"a"(fun));
}
*/
/** \defgroup IfxLld_Cpu_Intrinsics_Gnuc_any_type Cross type arithmetic operation
 *
 * Macro compatible with float, fix point, signed integer and unsigned integer
 *
 * \ingroup IfxLld_Cpu_Intrinsics_Gnuc
 * \{
 */
#define __minX(X,Y)                     ( ((X) < (Y)) ? (X) : (Y) )
#define __maxX(X,Y)                     ( ((X) > (Y)) ? (X) : (Y) )
#define __saturateX(X,Min,Max)          ( __minX(__maxX(X, Min), Max) )
#define __checkrangeX(X,Min,Max)        (((X) >= (Min)) && ((X) <= (Max)))
/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Gnuc_singed_integer Signed integer operation
 * \ingroup IfxLld_Cpu_Intrinsics_Gnuc
 * \{
 */
#define __saturate(X,Min,Max)           ( __min(__max(X, Min), Max) )
/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Gnuc_unsinged_integer Unsigned integer operation
 * \ingroup IfxLld_Cpu_Intrinsics_Gnuc
 * \{
 */
#define __saturateu(X,Min,Max)           ( __minu(__maxu(X, Min), Max) )
/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Gnucmin_max Minimum and Maximum of (sint16) Integers
 These intrinsic functions return the minimum or maximum of a sint16, uint16 or sint16
 * \ingroup IfxLld_Cpu_Intrinsics_Gnuc
 * \{
 */

/** Return maximum of two integers
 */
IFX_INLINE sint32 __max(sint32 a, sint32 b)
{
    sint32 res;
    __asm__ volatile ("max %0, %1, %2": "=d" (res) : "d" (a), "d" (b));
    return res;
}

/** Return maximum of two sint16
 */
IFX_INLINE sint32 __maxs(sint16 a, sint16 b)
{
    sint32 res;
    __asm__ volatile ("max.h %0, %1, %2": "=d" (res) : "d" (a), "d" (b));
    return res;
}
/** Return maximum of two unsigned integers
 */
IFX_INLINE uint32 __maxu(uint32 a, uint32 b)
{
    uint32 res;
    __asm__ volatile ("max.u %0, %1, %2": "=d" (res) : "d" (a), "d" (b));
    return res;
}

/** Return minimum of two integers
 */
IFX_INLINE sint32 __min(sint32 a, sint32 b)
{
    sint32 res;
    __asm__ volatile ("min %0, %1, %2": "=d" (res) : "d" (a), "d" (b));
    return res;
}

/** Return minimum of two sint16
 */
IFX_INLINE sint16 __mins(sint16 a, sint16 b)
{
    sint16 res;
    __asm__ volatile ("min.h %0, %1, %2": "=d" (res) : "d" (a), "d" (b));
    return res;
}

/** Return minimum of two unsigned integers
 */
IFX_INLINE uint32 __minu(uint32 a, uint32 b)
{
    uint32 res;
    __asm__ volatile ("min.u %0, %1, %2": "=d" (res) : "d" (a), "d" (b));
    return res;
}

/** \} */

/** \defgroup intrinsicsgnuc_float Floating point operation
 * \ingroup IfxLld_Cpu_Intrinsics_Gnuc
 * \{
 */

#define __sqrf(X)                       ((X) * (X))
#define __sqrtf(X)                      sqrtf(X)
#define __checkrange(X,Min,Max)         (((X) >= (Min)) && ((X) <= (Max)))

#define __roundf(X)                     ((((X) - (sint32)(X)) > 0.5) ? (1 + (sint32)(X)) : ((sint32)(X)))
#define __absf(X)                       ( ((X) < 0.0) ? -(X) : (X) )
#define __minf(X,Y)                     ( ((X) < (Y)) ? (X) : (Y) )
#define __maxf(X,Y)                     ( ((X) > (Y)) ? (X) : (Y) )
#define __saturatef(X,Min,Max)          ( __minf(__maxf(X, Min), Max) )
#define __checkrangef(X,Min,Max)        (((X) >= (Min)) && ((X) <= (Max)))

#define __abs_stdreal(X)                ( ((X) > 0.0) ? (X) : -(X) )
#define __min_stdreal(X,Y)              ( ((X) < (Y)) ? (X) : (Y) )
#define __max_stdreal(X,Y)              ( ((X) > (Y)) ? (X) : (Y) )
#define __saturate_stdreal(X,Min,Max)   ( __min_stdreal(__max_stdreal(X, Min), Max) )

#define __neqf(X,Y)                     ( ((X) > (Y)) ||  ((X) < (Y)) )     /**< X != Y */
#define __leqf(X,Y)                     ( !((X) > (Y)) )     /**< X <= Y */
#define __geqf(X,Y)                     ( !((X) < (Y)) )     /**< X >= Y */
/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Gnucfractional Fractional Arithmetic Support
 The next table provides an overview of intrinsic functions to convert fractional values. Note that the
 TASKING VX-toolset C compiler for TriCore fully supports the fractional type so normally you should not
 need these intrinsic functions (except for __mulfractlong). For compatibility reasons the TASKING C
 compiler does support these functions.
 * \ingroup IfxLld_Cpu_Intrinsics_Gnuc
 * \{
 */

/** Count the consecutive number of bits that have the same value as bit 15 of an sfract
 */
IFX_INLINE sint16 __clssf(sfract a)
{
    sint16 res;
    __asm__ volatile ("cls  %0,%1":"=d"(res):"d"(a):"memory");
    return res;
}

/** Convert fract to float
 */
IFX_INLINE float __fract_to_float(fract a)
{
    float res;
    __asm__ volatile ("q31tof  %0,%1,%2":"=d"(res):"d"(a), "d"(0):"memory");
    return res;
}

/** Convert float to fract
 */
IFX_INLINE fract __float_to_fract(float a)
{
    fract res;
    __asm__ volatile ("ftoq31  %0,%1,%2":"=d"(res):"d"(a), "d"(0):"memory");
    return res;
}

/** Convert laccum to fract
 */
IFX_INLINE fract __getfract(laccum a)
{
    fract res;
    __asm__ volatile ("dextr  %0,%H1,%L1,0x11":"=&d" (res):"d" (a):"memory");
    return res;
}

/** Multiply-add with rounding. Returns the rounded result of ( a + b * c )
 */
IFX_INLINE sfract __mac_r_sf(sfract a, sfract b, sfract c)
{
    sfract res;
    __asm__ volatile ("maddrs.q  %0,%1,%2U,%3U,1":"=d"(res):"d"(a), "d"(b), "d"(c):"memory");
    return res;
}

/** Multiply-add sfract. Returns ( a + b * c )
 */
IFX_INLINE sfract __mac_sf(sfract a, sfract b, sfract c)
{
    sfract res;
    __asm__ volatile ("madds.q  %0,%1,%2U,%3U,1":"=d"(res):"d"(a), "d"(b), "d"(c):"memory");
    return res;
}

/** Integer part of the multiplication of a fract and a fract
 */
IFX_INLINE long __mulfractfract(fract a, fract b)
{
    long res;
    __asm__ volatile ("mul.q %0,%1,%2,1":"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/** Integer part of the multiplication of a fract and a long
 */
IFX_INLINE long __mulfractlong(fract a, long b)
{
    long res;
    __asm__ volatile ("mul.q %0,%1,%2,1":"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/** Convert fract to sfract
 */
IFX_INLINE sfract __round16(fract a)
{
    sfract res;
    __asm__ volatile ("mov.u  %0,0x8000        \n\
                    adds  %0,%1              \n\
                    insert  %0,%0,0,0,0x10 "
                      :"=&d"(res):"d"(a):"memory");
    return res;
}

/** Convert signed sint16 to sfract
 */
IFX_INLINE sfract __s16_to_sfract(sint16 a)
{
    sfract res;
    __asm__ volatile ("sh  %0,%1,16":"=d"(res):"d"(a):"memory");
    return res;
}

/** Convert sfract to sint16
 */
IFX_INLINE sint16 __sfract_to_s16(sfract a)
{
    sint16 res;
    __asm__ volatile ("sh  %0,%1,-16":"=d"(res):"d"(a):"memory");
    return res;
}

/** Convert sfract to uint16
 */
IFX_INLINE uint16 __sfract_to_u16(sfract a)
{
    uint16 res;
    __asm__ volatile ("sh  %0,%1,-16":"=d"(res):"d"(a):"memory");
    return res;
}

/** Left/right shift of an laccum
 */
IFX_INLINE laccum __shaaccum(laccum a, sint32 b)
{
    laccum res;
    __asm__ volatile ("jge   %2,0,0f        \n\
                    sha   %H0,%H1,%2     \n\
                    rsub  %2,%2,0        \n\
                    dextr %L0,%H1,%L1,%2 \n\
                    j  1f                \n\
                    0:dextr %H0,%H1,%L1,%2 \n\
                    sha   %L0,%L1,%2     \n\
                    1:"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/** Left/right shift of an fract
 */
IFX_INLINE fract __shafracts(fract a, sint32 b)
{
    fract res;
    __asm__ volatile ("shas  %0,%1,%2":"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/** Left/right shift of an sfract
 */
IFX_INLINE sfract __shasfracts(sfract a, sint32 b)
{
    sfract res;
    __asm__ volatile ("shas  %0,%1,%2":"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/** Convert uint16 to sfract
 */
IFX_INLINE sfract __u16_to_sfract(uint16 a)
{
    sfract res;
    __asm__ volatile ("sh  %0,%1,16":"=d"(res):"d"(a):"memory");
    return res;
}

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Gnucinsert Insert / Extract Bit-fields and Bits
 * \ingroup IfxLld_Cpu_Intrinsics_Gnuc
 * \{
 */

/** Extract a bit-field (bit pos to bit pos+width) from value
 */
IFX_INLINE sint32 __extr(sint32 a, uint32 p, uint32 w)
{
    sint32 res;
    __asm__ volatile ("mov %%d14,%2  \n\
                     mov %%d15,%3  \n\
                     extr %0,%1,%%e14"
                      : "=d" (res) : "d" (a), "d" (p), "d" (w):"d14", "d15");
    return res;
}

/** Same as __extr() but return bit-field as unsigned integer
 */
IFX_INLINE uint32 __extru(uint32 a, uint32 p, uint32 w)
{
    uint32 res;
    __asm__ volatile ("mov %%d14,%2  \n\
                     mov %%d15,%3  \n\
                     extr.u %0,%1,%%e14"
                      : "=d" (res) : "d" (a), "d" (p), "d" (w):"d14", "d15");
    return res;
}

/** Load a single bit.
 */
//#define __getbit(address,bitoffset ) __extru( *(address), bitoffset, 1 )
#define __getbit(address, bitoffset) ((*(address) & (1U << (bitoffset))) != 0)

/** Atomic load-modify-store.
 */
#define __imaskldmst(address, value, bitoffset, bits) \
  {long long tmp;\
  __asm("imask %A0,%1,%2,%3":"=d"((long long)tmp):"d"(value),"d"(bitoffset),"i"(bits): "memory");\
  __asm("ldmst %0,%A1"::"i"(address),"d"(tmp));}

/** Return trg but replace trgbit by srcbit in src.
 */
IFX_INLINE sint32 __ins(sint32 trg, const sint32 trgbit, sint32 src, const sint32 srcbit)
{
    sint32 res;
    __asm__ volatile ("ins.t %0,%1,%2,%3,%4":"=d"(res):"d"(trg), "i"(trgbit), "d"(src), "i"(srcbit));
    return res;
}

/** Extract bit-field (width bits starting at bit 0) from src and insert it in trg at pos.
 */
IFX_INLINE sint32 __insert(sint32 a, sint32 b, sint32 p, const sint32 w)
{
    sint32 res;
    __asm__ volatile ("mov %%d14,%2  \n\
                     mov %%d15,%3  \n\
                     insert %0,%1,%2,%%e14"
                      :"=d"(res):"d"(a), "d"(b), "d"(p), "d"(w):"d14", "d15");
    return res;
}

/** Return trg but replace trgbit by inverse of srcbit in src.
 */
IFX_INLINE sint32 __insn(sint32 trg, const sint32 trgbit, sint32 src, const sint32 srcbit)
{
    sint32 res;
    __asm__ volatile ("insn.t %0,%1,%2,%3,%4":"=d"(res):"d"(trg), "i"(trgbit), "d"(src), "i"(srcbit));
    return res;
}

/** Store a single bit.
 */
#define __putbit(value,address,bitoffset ) __imaskldmst(address, value, bitoffset,1)

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Gnucinterrupt_handling Interrupt Handling
 The next table provides an overview of the intrinsic functions to read or set interrupt handling.
 * \ingroup IfxLld_Cpu_Intrinsics_Gnuc
 * \{
 */

#if !IFXCPU_INTRINSICSGNUC_USE_MACHINE_INTRINSICS
/** Set CPU priority number [0..255] (or [0..1023] for TriCore 1.6.x) and enable interrupts immediately at function entry
 */
#define __bisr(intlvl) __asm__ volatile ("bisr "#intlvl : : : "memory")
#endif

/** Disable interrupts. Only supported for TriCore1
 */
#define __disable() __asm__ volatile ("disable" : : : "memory")

/** Disable interrupts and return previous interrupt state (enabled or disabled). Direct supported for TriCore1.6. Emulated on TC1.3.1
 */
IFX_INLINE sint32 __disable_and_save(void)
{
    sint32 res;
    __asm__ volatile("disable %0":"=d"(res));
    return res;
}

/** Enable interrupts immediately at function entry
 */
#define __enable() __asm__ volatile ("enable" : : : "memory")

/** Restore interrupt state. Direct supported for TriCore1.6. Emulated on TC1.3.1
 */
IFX_INLINE void __restore(sint32 ie)
{
    __asm__ volatile ("restore %0"::"d"(ie));
}

#if !IFXCPU_INTRINSICSGNUC_USE_MACHINE_INTRINSICS
/** Call a system call function number
 */
#define __syscall(svcno) __tric_syscall(svcno)
#define __tric_syscall(svcno) __asm__ volatile ("syscall "STRINGIFY(svcno) : : : "memory")
#endif

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Gnucmiscellaneous Miscellaneous Intrinsic Functions
 * \ingroup IfxLld_Cpu_Intrinsics_Gnuc
 * \{
 */

/**  Write back and invalidate cache address "p". Generates CACHEA.WI [Ab].
 */
IFX_INLINE void __cacheawi(uint8* p)
{
    __asm__ volatile("cachea.wi [%0]0"::"a"(p));
}
/**  Write back and invalidate cache index "p". Generates CACHEI.WI [Ab].
 */
IFX_INLINE void __cacheiwi(uint8* p)
{
    __asm__ volatile("cachei.wi [%0]0"::"a"(p));
}

/**  Write back and invalidate cache address \"p\" and return post incremented
 * value of \"p\". Generates CACHEA.WI [Ab+].
 */
IFX_INLINE uint8* __cacheawi_bo_post_inc(uint8* p)
{
    __asm__ volatile("cachea.wi  [%0+]0"::"a"(p));
    return p;
}

/** Multiply two 32-bit numbers to an intermediate 64-bit result, and scale
 * back the result to 32 bits. To scale back the result, 32 bits are extracted
 * from the intermediate 64-bit result: bit 63-offset to bit 31-offset.
 */
IFX_INLINE sint32 __mulsc(sint32 a, sint32 b, sint32 offset)
{
    sint32 res;
    __asm__ volatile("mul  %%e12,%1,%2      \n\
                    dextr  %0,%%d13,%%d12,%3"
                     :"=d"(res):"d"(a), "d"(b), "d"(offset):"d12", "d13");
    return res;
}

/**  Rotate operand left count times. The bits that are shifted out are inserted at the right side (bit 31 is shifted to bit 0).
 */
IFX_INLINE uint32 __rol(uint32 operand, uint32 count)
{
    uint32 res;
    __asm__ volatile("dextr  %0,%1,%1,%2":"=d"(res):"d"(operand), "d"(count):"memory");
    return res;
}

/**  Rotate operand right count times. The bits that are shifted out are inserted at the left side (bit 0 is shifted to bit 31).
 */
IFX_INLINE uint32 __ror(uint32 operand, uint32 count)
{
    uint32 res;
    __asm__ volatile("rsub %2,%2,0 \n\
                    dextr  %0,%1,%1,%2"
                     :"=d"(res):"d"(operand), "d"(count):"memory");
    return res;
}
/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Gnucpacked Packed Data Type Support
 The next table provides an overview of the intrinsic functions for initialization of packed data type.
 * \ingroup IfxLld_Cpu_Intrinsics_Gnuc
 * \{
 */

/**  Absolute value of __packb
 */
IFX_INLINE __packb __absb(__packb a)
{
    __packb res;
    __asm__ volatile ("abs.b %0,%1"
                      :"=d"(res):"d"(a):"memory");
    return res;
}

/**  Absolute value of __packhw
 */
IFX_INLINE __packhw __absh(__packhw a)
{
    __packhw res;
    __asm__ volatile ("abs.h %0,%1"
                      :"=d"(res):"d"(a):"memory");
    return res;
}

/**  Absolute value of __packhw using saturation
 */
IFX_INLINE __packhw __abssh(__packhw a)
{
    __packb res;
    __asm__ volatile ("abss.h %0,%1"
                      :"=d"(res):"d"(a):"memory");
    return res;
}

/** Extract first byte from a __packb
 */
IFX_INLINE sint8 __extractbyte1(__packb a)
{
    sint8 res;
    __asm__ volatile ("extr  %0,%1,0,8"
                      :"=d"(res):"d"(a):"memory");
    return res;
}

/** Extract second byte from a __packb
 */
IFX_INLINE sint8 __extractbyte2(__packb a)
{
    sint8 res;
    __asm__ volatile ("extr  %0,%1,8,8"
                      :"=d"(res):"d"(a):"memory");
    return res;
}

/** Extract third byte from a __packb
 */
IFX_INLINE sint8 __extractbyte3(__packb a)
{
    sint8 res;
    __asm__ volatile ("extr  %0,%1,16,8"
                      :"=d"(res):"d"(a):"memory");
    return res;
}

/**  Extract fourth byte from a __packb
 */
IFX_INLINE sint8 __extractbyte4(__packb a)
{
    sint8 res;
    __asm__ volatile ("extr  %0,%1,24,8"
                      :"=d"(res):"d"(a):"memory");
    return res;
}

/** Extract first sint16 from a __packhw
 */
IFX_INLINE sint16 __extracthw1(__packhw a)
{
    sint16 res;
    __asm__ volatile ("extr  %0,%1,0,16"
                      :"=d"(res):"d"(a):"memory");
    return res;
}

/** Extract second sint16 from a __packhw
 */
IFX_INLINE sint16 __extracthw2(__packhw a)
{
    sint16 res;
    __asm__ volatile ("extr  %0,%1,16,16"
                      :"=d"(res):"d"(a):"memory");
    return res;
}

/** Extract first uint8 from a __packb
 */
IFX_INLINE uint8 __extractubyte1(__upackb a)
{
    uint8 res;
    __asm__ volatile ("extr  %0,%1,0,8"
                      :"=d"(res):"d"(a):"memory");
    return res;
}

/** Extract second uint8 from a __packb
 */
IFX_INLINE uint8 __extractubyte2(__upackb a)
{
    uint8 res;
    __asm__ volatile ("extr  %0,%1,8,8"
                      :"=d"(res):"d"(a):"memory");
    return res;
}

/** Extract third uint8 from a __packb
 */
IFX_INLINE uint8 __extractubyte3(__upackb a)
{
    uint8 res;
    __asm__ volatile ("extr  %0,%1,16,8"
                      :"=d"(res):"d"(a):"memory");
    return res;
}

/** Extract fourth uint8 from a __packb
 */
IFX_INLINE uint8 __extractubyte4(__upackb a)
{
    uint8 res;
    __asm__ volatile ("extr  %0,%1,24,8"
                      :"=d"(res):"d"(a):"memory");
    return res;
}

/** Extract first uint16 from a __packhw
 */
IFX_INLINE uint16 __extractuhw1(__upackhw a)
{
    uint16 res;
    __asm__ volatile ("extr  %0,%1,0,16"
                      :"=d"(res):"d"(a):"memory");
    return res;
}

/** Extract second uint16 from a __packhw
 */
IFX_INLINE uint16 __extractuhw2(__upackhw a)
{
    uint16 res;
    __asm__ volatile ("extr  %0,%1,16,16"
                      :"=d"(res):"d"(a):"memory");
    return res;
}

/**  Extract first byte from a __packb
 */
IFX_INLINE sint8 __getbyte1(__packb* a)
{
    sint8 res;
    __asm__ volatile ("ld.w  %0,[%1]0 \n\
                     extr  %0,%0,0,8"
                      :"=d"(res):"a"(a):"memory");
    return res;

}

/**  Extract second byte from a __packb
 */
IFX_INLINE sint8 __getbyte2(__packb* a)
{
    sint8 res;
    __asm__ volatile ("ld.w  %0,[%1]0 \n\
                     extr  %0,%0,8,8"
                      :"=d"(res):"a"(a):"memory");
    return res;

}

/**  Extract third byte from a __packb
 */
IFX_INLINE sint8 __getbyte3(__packb* a)
{
    sint8 res;
    __asm__ volatile ("ld.w  %0,[%1]0 \n\
                     extr  %0,%0,16,8"
                      :"=d"(res):"a"(a):"memory");
    return res;

}

/**  Extract fourth byte from a __packb
 */
IFX_INLINE sint8 __getbyte4(__packb* a)
{
    sint8 res;
    __asm__ volatile ("ld.w  %0,[%1]0 \n\
                     extr  %0,%0,24,8"
                      :"=d"(res):"a"(a):"memory");
    return res;

}

/**  Extract first sint16 from a __packhw
 */
IFX_INLINE sint16 __gethw1(__packhw* a)
{
    sint16 res;
    __asm__ volatile ("ld.w  %0,[%1]0 \n\
                     extr  %0,%0,0,16"
                      :"=d"(res):"a"(a):"memory");
    return res;
}
/**  Extract second sint16 from a __packhw
 */
IFX_INLINE sint16 __gethw2(__packhw* a)
{
    sint16 res;
    __asm__ volatile ("ld.w  %0,[%1]0 \n\
                     extr  %0,%0,16,16"
                      :"=d"(res):"a"(a):"memory");
    return res;
}

/**  Extract first uint8 from a __packb
 */
IFX_INLINE uint8 __getubyte1(__upackb* a)
{
    uint8 res;
    __asm__ volatile ("ld.w  %0,[%1]0 \n\
                     extr  %0,%0,0,8"
                      :"=d"(res):"a"(a):"memory");
    return res;
}

/**  Extract second uint8 from a __packb
 */
IFX_INLINE uint8 __getubyte2(__upackb* a)
{
    uint8 res;
    __asm__ volatile ("ld.w  %0,[%1]0 \n\
                     extr  %0,%0,8,8"
                      :"=d"(res):"a"(a):"memory");
    return res;
}

/**  Extract third uint8 from a __packb
 */
IFX_INLINE uint8 __getubyte3(__upackb* a)
{
    uint8 res;
    __asm__ volatile ("ld.w  %0,[%1]0 \n\
                     extr  %0,%0,16,8"
                      :"=d"(res):"a"(a):"memory");
    return res;
}

/**  Extract fourth uint8 from a __packb
 */
IFX_INLINE uint8 __getubyte4(__upackb* a)
{
    uint8 res;
    __asm__ volatile ("ld.w  %0,[%1]0 \n\
                     extr  %0,%0,24,8"
                      :"=d"(res):"a"(a):"memory");
    return res;
}

/**  Extract first uint16 from a __packhw
 */
IFX_INLINE uint16 __getuhw1(__upackhw* a)
{
    uint16 res;
    __asm__ volatile ("ld.w  %0,[%1]0 \n\
                     extr  %0,%0,0,16"
                      :"=d"(res):"a"(a):"memory");
    return res;
}

/**  Extract second uint16 from a __packhw
 */
IFX_INLINE uint16 __getuhw2(__upackhw* a)
{
    uint16 res;
    __asm__ volatile ("ld.w  %0,[%1]0 \n\
                     extr  %0,%0,16,16"
                      :"=d"(res):"a"(a):"memory");
    return res;
}

/**  Initialize  __packb with four integers
 */
IFX_INLINE __packb __initpackb(sint32 a, sint32 b, sint32 c, sint32 d)
{
    __packb res;
    __asm__ volatile ("insert  %3,%3,%4,8,8   \n\
                    insert  %4,%1,%2,8,8   \n\
                    insert  %0,%4,%3,16,16 "
                      :"=d"(res):"d"(a), "d"(b), "d"(c), "d"(d):"memory");
    return res;
}

/** Initialize  __packb with a long integer
 */
IFX_INLINE __packb __initpackbl(long a)
{
    return (__packb) a;
}

/** Initialize  __packhw with two integers
 */
IFX_INLINE __packhw __initpackhw(sint16 a, sint16 b)
{
    __packhw res;
    __asm__ volatile ("insert  %0,%1,%2,16,16"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/**  Initialize  __packhw with a long integer
 */
IFX_INLINE __packhw __initpackhwl(long a)
{
    return a;
}

/** Initialize  __packb with four unsigned integers
 */
IFX_INLINE __upackb    __initupackb( uint32 a, uint32 b, uint32 c, uint32 d)
{
    __upackb res;
    __asm__ volatile ("insert  %3,%3,%4,8,8   \n\
                    insert  %1,%1,%2,8,8   \n\
                    insert  %0,%1,%3,16,16"
                      :"=d"(res):"d"(a), "d"(b), "d"(c), "d"(d):"memory");
    return res;
}

/**  Initialize  __packhw with two unsigned integers
 */
IFX_INLINE __upackhw    __initupackhw( uint16 a, uint16 b)
{
    __upackhw res;
    __asm__ volatile ("insert  %0,%1,%2,16,16"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/** Insert sint8 into first byte of a __packb
 */
IFX_INLINE __packb __insertbyte1(__packb a, sint8 b)
{
    __packb res;
    __asm__ volatile ("insert  %0,%1,%2,0,8"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/** Insert sint8 into second byte of a __packb
 */
IFX_INLINE __packb __insertbyte2(__packb a, sint8 b)
{
    __packb res;
    __asm__ volatile ("insert  %0,%1,%2,8,8"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/** Insert sint8 into third byte of a __packb
 */
IFX_INLINE __packb __insertbyte3(__packb a, sint8 b)
{
    __packb res;
    __asm__ volatile ("insert  %0,%1,%2,16,8"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/** Insert sint8 into fourth byte of a __packb
 */
IFX_INLINE __packb __insertbyte4(__packb a, sint8 b)
{
    __packb res;
    __asm__ volatile ("insert  %0,%1,%2,24,8"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/** Insert sint8 into first uint8 of a __packb
 */
IFX_INLINE __upackb    __insertubyte1( __upackb a, uint8 b)
{
    __upackb res;
    __asm__ volatile ("insert  %0,%1,%2,0,8"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/** Insert sint8 into second uint8 of a __packb
 */
IFX_INLINE __upackb    __insertubyte2( __upackb a, uint8 b)
{
    __upackb res;
    __asm__ volatile ("insert  %0,%1,%2,8,8"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/** Insert sint8 into third uint8 of a __packb
 */
IFX_INLINE __upackb     __insertubyte3( __upackb a, uint8 b)
{
    __upackb res;
    __asm__ volatile ("insert  %0,%1,%2,16,8"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/** Insert sint8 into fourth uint8 of a __packb
 */
IFX_INLINE __upackb     __insertubyte4( __upackb a, uint8 b)
{
    __upackb res;
    __asm__ volatile ("insert  %0,%1,%2,24,8"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/**  Insert sint16 into first halfword of a __packhw
 */
IFX_INLINE __packhw __inserthw1(__packhw a, sint16 b)
{
    __packhw res;
    __asm__ volatile ("insert  %0,%1,%2,0,16"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/**  Insert sint16 into second halfword of a __packhw
 */
IFX_INLINE __packhw __inserthw2(__packhw a, sint16 b)
{
    __packhw res;
    __asm__ volatile ("insert  %0,%1,%2,16,16"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/** Insert uint16 into first halfword of a __upackhw
 */
IFX_INLINE __upackhw    __insertuhw1( __upackhw a, uint16 b)
{
    __upackhw res;
    __asm__ volatile ("insert  %0,%1,%2,0,16"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/** Insert uint16 into second halfword of a __upackhw
 */
IFX_INLINE __upackhw    __insertuhw2( __upackhw a, uint16 b)
{
    __upackhw res;
    __asm__ volatile ("insert  %0,%1,%2,16,16"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/**  Minimum of two  __packb values
 */
IFX_INLINE __packb __minb(__packb a, __packb b)
{
    __packb res;
    __asm__ volatile ("min.b %0,%1,%2"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/**  Minimum of two __upackb  values
 */
IFX_INLINE __upackb     __minbu( __upackb  a, __upackb  b)
{
    __upackb res;
    __asm__ volatile ("min.bu %0,%1,%2"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/**  Minimum of two  __packhw values
 */
IFX_INLINE __packhw __minh(__packhw a, __packhw b)
{
    __packhw res;
    __asm__ volatile ("min.h %0,%1,%2"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/**  Minimum of two __upackhw values
 */
IFX_INLINE __upackhw    __minhu( __upackhw a, __upackhw b)
{
    __upackhw res;
    __asm__ volatile ("min.hu %0,%1,%2"
                      :"=d"(res):"d"(a), "d"(b):"memory");
    return res;
}

/**  Insert sint8 into first byte of a __packb
 */
IFX_INLINE void __setbyte1(__packb* a, sint8 b)
{
    __asm__ volatile ("ld.w  %%d15,[%0] \n\
                    insert  %%d15,%%d15,%1,0,8 \n\
                    st.w [%0],%%d15"
                      ::"a"(a), "d"(b):"d15", "memory");
}

/**  Insert sint8 into second byte of a __packb
 */
IFX_INLINE void __setbyte2(__packb* a, sint8 b)
{
    __asm__ volatile ("ld.w  %%d15,[%0] \n\
                    insert  %%d15,%%d15,%1,8,8 \n\
                    st.w [%0],%%d15"
                      ::"a"(a), "d"(b):"d15", "memory");
}

/**  Insert sint8 into third byte of a __packb
 */
IFX_INLINE void __setbyte3(__packb* a, sint8 b)
{
    __asm__ volatile ("ld.w  %%d15,[%0] \n\
                    insert  %%d15,%%d15,%1,16,8 \n\
                    st.w [%0],%%d15"
                      ::"a"(a), "d"(b):"d15", "memory");
}

/**  Insert sint8 into fourth byte of a __packb
 */
IFX_INLINE void __setbyte4(__packb* a, sint8 b)
{
    __asm__ volatile ("ld.w  %%d15,[%0] \n\
                    insert  %%d15,%%d15,%1,24,8 \n\
                    st.w [%0],%%d15"
                      ::"a"(a), "d"(b):"d15", "memory");
}

/**  Insert sint16 into first halfword of a __packhw
 */
IFX_INLINE void __sethw1(__packhw* a, sint16 b)
{
    __asm__ volatile ("ld.w  %%d15,[%0] \n\
                    insert  %%d15,%%d15,%1,0,16 \n\
                    st.w [%0],%%d15"
                      ::"a"(a), "d"(b):"d15", "memory");
}

/**  Insert sint16 into second halfword of a __packhw
 */
IFX_INLINE void __sethw2(__packhw* a, sint16 b)
{
    __asm__ volatile ("ld.w  %%d15,[%0] \n\
                    insert  %%d15,%%d15,%1,16,16 \n\
                    st.w [%0],%%d15"
                      ::"a"(a), "d"(b):"d15", "memory");
}

/**  Insert uint8 into first byte of a __upackb
 */
IFX_INLINE void __setubyte1(__upackb* a, uint8 b)
{
    __asm__ volatile ("ld.w  %%d15,[%0] \n\
                    insert  %%d15,%%d15,%1,0,8 \n\
                    st.w [%0],%%d15"
                      ::"a"(a), "d"(b):"d15", "memory");
}

/**  Insert uint8 into second byte of a __upackb
 */
IFX_INLINE void __setubyte2(__upackb* a, uint8 b)
{
    __asm__ volatile ("ld.w  %%d15,[%0] \n\
                    insert  %%d15,%%d15,%1,8,8 \n\
                    st.w [%0],%%d15"
                      ::"a"(a), "d"(b):"d15", "memory");
}

/**  Insert uint8 into third byte of a __upackb
 */
IFX_INLINE void __setubyte3(__upackb* a, uint8 b)
{
    __asm__ volatile ("ld.w  %%d15,[%0] \n\
                    insert  %%d15,%%d15,%1,16,8 \n\
                    st.w [%0],%%d15"
                      ::"a"(a), "d"(b):"d15", "memory");
}

/**  Insert uint8 into fourth byte of a __upackb
 */
IFX_INLINE void __setubyte4(__upackb* a, uint8 b)
{
    __asm__ volatile ("ld.w  %%d15,[%0] \n\
                    insert  %%d15,%%d15,%1,24,8 \n\
                    st.w [%0],%%d15"
                      ::"a"(a), "d"(b):"d15", "memory");
}

/**  Insert uint16 into first halfword of a __upackhw
 */
IFX_INLINE void __setuhw1(__upackhw* a, uint16 b)
{
    __asm__ volatile ("ld.w  %%d15,[%0] \n\
                    insert  %%d15,%%d15,%1,0,16 \n\
                    st.w [%0],%%d15"
                      ::"a"(a), "d"(b):"d15", "memory");
}

/**  Insert uint16 into second halfword of a __upackhw
 */
IFX_INLINE void __setuhw2(__upackhw* a, uint16 b)
{
    __asm__ volatile ("ld.w  %%d15,[%0] \n\
                    insert  %%d15,%%d15,%1,16,16 \n\
                    st.w [%0],%%d15"
                      ::"a"(a), "d"(b):"d15", "memory");
}

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Gnucregister Register Handling
 The next table provides an overview of the intrinsic functions that you can use to access control registers.
 * \ingroup IfxLld_Cpu_Intrinsics_Gnuc
 * \{
 */

/**  Return absolute value
 */
#define __abs(a) __builtin_abs(a)

/** Return absolue difference of two integers
 */
IFX_INLINE sint32 __absdif(sint32 a, sint32 b)
{
    sint32 res;
    __asm__ volatile ("absdif %0, %1, %2": "=d" (res) : "d" (a), "d" (b));
    return res;
}

/**  Return absolute value with saturation
 */
IFX_INLINE sint32 __abss(sint32 a)
{
    sint32 res;
    __asm__ volatile ("abss %0, %1": "=d" (res) : "d" (a));
    return res;
}

/**  Count leading ones in int
 */
IFX_INLINE sint32 __clo(sint32 a)
{
    sint32 res;
    __asm__ volatile ("clo %0,%1":"=d"(res):"d"(a));
    return res;
}

/**  Count number of redundant sign bits (all consecutive bits with the same value as bit 31
 */
IFX_INLINE sint32 __cls(sint32 a)
{
    sint32 res;
    __asm__ volatile ("cls %0,%1":"=d"(res):"d"(a));
    return res;
}

/**  Count leading zeros in int
 */
#define  __clz(a) __builtin_clz(a)

/**  Return absolute double precision floating-point value
 */
IFX_INLINE double __fabs(double d)
{
    double res;
    __asm__ volatile ("insert  %0,%1,0,31,1": "=d" (res) : "d" (d):"memory");
    return res;
}

/**  Return absolute floating-point value
 */
IFX_INLINE float __fabsf(float f)
{
    float res;
    __asm__ volatile ("insert  %0,%1,0,31,1": "=d" (res) : "d" (f):"memory");
    return res;
}


#if !IFXCPU_INTRINSICSGNUC_USE_MACHINE_INTRINSICS
/**  Move contents of the addressed core SFR into a data register
 */
#define __mfcr(regaddr)  \
 ({ sint32 res; __asm__ volatile ("mfcr %0,%1": "=d" (res) :"i"(regaddr): "memory"); res; })

//({ sint32 res; __asm__ volatile ("mfcr %0,"#regaddr : "=d" (res) : : "memory"); res; })

/**  Move contents of a data register (second int) to the addressed core SFR (first int)
 */
#define __mtcr(regaddr,val) __asm__ volatile ("mtcr %0,%1\n\tisync"::"i"(regaddr),"d"(val):"memory")
#endif


/**  Return parity
 */
IFX_INLINE sint32 __parity(sint32 a)
{
    sint32 res;
    __asm__ volatile ("parity  %0,%1": "=d" (res) : "d" (a):"memory");
    return res;
}

/**  Return saturated byte
 */
IFX_INLINE sint8 __satb(sint32 a)
{
    sint8 res;
    __asm__ volatile ("sat.b %0,%1":"=d"(res):"d"(a));
    return res;
}

/**  Return saturated uint8
 */
IFX_INLINE uint8 __satbu(sint32 a)
{
    uint8 res;
    __asm__ volatile ("sat.bu %0,%1":"=d"(res):"d"(a));
    return res;
}

/**  Return saturated halfword
 */
IFX_INLINE sint16 __sath(sint32 a)
{
    sint8 res;
    __asm__ volatile ("sat.h %0,%1":"=d"(res):"d"(a));
    return res;
}

/**  Return saturated unsigned halfword
 */
IFX_INLINE uint16 __sathu(sint32 a)
{
    sint8 res;
    __asm__ volatile ("sat.hu %0,%1":"=d"(res):"d"(a));
    return res;
}

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Gnucsaturation Saturation Arithmetic Support
 These intrinsics support saturation arithmetic
 * \ingroup IfxLld_Cpu_Intrinsics_Gnuc
 * \{
 */

/** add signed with saturation
 */
IFX_INLINE sint32 __adds(sint32 a, sint32 b)
{
    sint32 res;
    __asm__ volatile ("adds %0, %1, %2": "=d" (res) : "d" (a), "d" (b));
    return res;
}

/** add unsigned with saturation
 */
IFX_INLINE uint32 __addsu(uint32 a, uint32 b)
{
    uint32 res;
    __asm__ volatile ("adds.u %0, %1, %2": "=d" (res) : "d" (a), "d" (b));
    return res;
}

/** substract signed with saturation
 */
IFX_INLINE sint32 __subs(sint32 a, sint32 b)
{
    sint32 res;
    __asm__ volatile ("subs %0, %1, %2": "=d" (res) : "d" (a), "d" (b));
    return res;
}

/** substract unsigned with saturation
 */
IFX_INLINE uint32 __subsu(uint32 a, uint32 b)
{
    uint32 res;
    __asm__ volatile ("subs.u %0, %1, %2": "=d" (res) : "d" (a), "d" (b));
    return res;
}

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Gnucsingle_assembly Insert Single Assembly Instruction
 The next table provides an overview of the intrinsic functions that you can use to insert a single assembly
 instruction.You can also use inline assembly but these intrinsics provide a shorthand for frequently used
 assembly instructions.
 * \ingroup IfxLld_Cpu_Intrinsics_Gnuc
 * \{
 */

/** Insert DEBUG instruction
 */
IFX_INLINE void __debug(void)
{
    __asm__ volatile ("debug" : : : "memory");
}

/** Insert DSYNC instruction
 */
IFX_INLINE void __dsync(void)
{
    __asm__ volatile ("dsync" : : : "memory");
}

/** Insert ISYNC instruction
 */
IFX_INLINE void __isync(void)
{
    __asm__ volatile ("isync" : : : "memory");
}

/** Insert LDMST instruction. Note that all operands must be word-aligned.
 */
IFX_INLINE void __ldmst(volatile void* address, uint32 mask, uint32 value)
{
    __asm__ volatile("mov %H2,%1 \n\
                  ldmst [%0]0,%A2"
                     ::"a"(address), "d"(mask), "d"((long long)value));
}

/** Insert NOP instruction
 */
IFX_INLINE void __nop(void)
{
    __asm__ volatile ("nop" : : : "memory");
}

/** Insert a loop over cnt NOP instruction
 */
IFX_INLINE void __nops(void* cnt)
{
    __asm__ volatile ("0: nop \n\
        loop %0,0b"
                      ::"a"(((sint8*)cnt)-1));
}

/** Insert RSLCX instruction
 */
IFX_INLINE void __rslcx(void)
{
    __asm__ volatile ("rslcx" : : : "memory");
}

/** Insert SVLCX instruction
 */
IFX_INLINE void __svlcx(void)
{
    __asm__ volatile ("svlcx" : : : "memory");
}

/** Insert SWAP instruction. Note that all operands must be word-aligned.
 */
IFX_INLINE uint32 __swap(void* place, uint32 value)
{
    uint32 res;
    __asm__ volatile("swap.w [%1]0,%2":"=d"(res):"a"(place), "0"(value));
    return res;
}

/** Insert n NOP instruction
 */
#define NOP(n)   __asm(".rept " #n "\n\tnop\n\t.endr\n")

/** \} */

/* FIXME use inline instead of #define */
#define __extru(src,start,size) \
    ({ sint32 res; asm volatile (" extr.u\t %0,%1,%2,%3" : "=d" (res) : \
        "d" (src),"i" (start),"i" (size) : "memory"); res; })

/* FIXME use inline instead of #define */
#define __setareg(areg,val) \
    { uint32 reg_val= (uint32)val; \
        asm volatile (" mov.a\t %%"#areg",%0"::"d"(reg_val)); }

/**__mtcr (CPU_CCTRL, 0);
*/
IFX_INLINE void __stopPerfCounters(void)
{
    __asm__ volatile("mov %%d0,0\n\
                  mtcr 0xFC00,%%d0\n\
                  isync\n"
            : : :"d0"); /* FIXME check that the parameter d0 is understood by the compiler as a register used by the inline */
}

/** \brief This function is a implementation of a binary semaphore using compare and swap instruction
 * \param address address of resource.
 * \param value This variable is updated with status of address
 * \param condition if the value of address matches with the value of condition, then swap of value & address occurs.
 *
 */
IFX_INLINE unsigned int __cmpAndSwap (unsigned int volatile *address,
           unsigned int value, unsigned int condition)
{
 /* Gnu C compiler with Tricore 1.6 support is required to use cmpswap instruction */
#ifdef IFX_USE_GNUC_TRICORE_1_6
  __extension__ unsigned long long reg64
    = value | (unsigned long long) condition << 32;

  __asm__ __volatile__ ("cmpswap.w [%[addr]]0, %A[reg]"
                        : [reg] "+d" (reg64)
                        : [addr] "a" (address)
                        : "memory");
    return reg64;
#else
  sint32 ie;
  uint32 retval = 1;
  ie = __disable_and_save();
  if (condition == *address)
  {
     __swap((void *)address,value );
    retval = 0;
  }
  __restore(ie);
  return retval;
#endif
}
/******************************************************************************/
/* *INDENT-ON* */
#endif /* IFXCPU_INTRINSICSGNUC_H */
