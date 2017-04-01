/**
 * \file IfxCpu_IntrinsicsDcc.h
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
 * \defgroup IfxLld_Cpu_Intrinsics_Dcc intrinsics for DCC compiler
 * \ingroup IfxLld_Cpu_Intrinsics
 *
 */
#ifndef IFXCPU_INTRINSICSDCC_H
#define IFXCPU_INTRINSICSDCC_H
/******************************************************************************/
#include "Ifx_Types.h"

/******************************************************************************/
/* *INDENT-OFF* */
/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_min_smax Minimum and Maximum of (Short) Integers
 These intrinsic functions return the minimum or maximum of a signed integer, unsigned integer or short integer.
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */

/** Function call without return
 */
asm volatile void __non_return_call(void (*fun)(void))
{
% reg fun
    ji fun
}

/** Jump and link
 */
asm volatile void __jump_and_link(void (*fun)(void))
{
% reg fun
    jli fun
}

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_any_type Cross type arithmetic operation
 *
 * Macro compatible with float, fix point, signed integer and unsigned integer
 *
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */
#define __minX(X,Y)                     ( ((X) < (Y)) ? (X) : (Y) )
#define __maxX(X,Y)                     ( ((X) > (Y)) ? (X) : (Y) )
#define __saturateX(X,Min,Max)          ( __minX(__maxX(X, Min), Max) )
#define __checkrangeX(X,Min,Max)        (((X) >= (Min)) && ((X) <= (Max)))


/** Return minimum of two integers
 */
extern sint32 __min( sint32,  sint32) __attribute__((intrinsic_pseudo(3, "min") ));

/** Return minimum of two short integers
 */
extern sint32 __mins( sint32,  sint32) __attribute__((intrinsic_function(0x10b, 0, "min.h") ));

/** Return minimum of two unsigned integers
 */
extern uint32 __minu( uint32,  uint32) __attribute__((intrinsic_pseudo(3, "min.u") ));

/** Return maximum of two integers
 */
extern sint32 __max( sint32,  sint32) __attribute__((intrinsic_pseudo(3, "max") ));

/** Return maximum of two short integers
 */
extern uint32 __maxs( uint32,  uint32) __attribute__((intrinsic_function(0x10b, 0, "max.h") ));

/** Return maximum of two unsigned integers
 */
extern uint32 __maxu( uint32,  uint32) __attribute__((intrinsic_pseudo(3, "max.u") ));

/** \} */

/** \defgroup intrinsicstasking_float Floating point operation
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */
#define __saturate(X,Min,Max)           ( __minf(__maxf(X, Min), Max) )

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
#define __saturate_stdreal(X,Min,Max)    ( __min_stdreal(__max_stdreal(X, Min), Max) )

#define __neqf(X,Y)                     ( ((X) > (Y)) ||  ((X) < (Y)) )     /**< X != Y */
#define __leqf(X,Y)                     ( !((X) > (Y)) )     /**< X <= Y */
#define __geqf(X,Y)                     ( !((X) < (Y)) )     /**< X >= Y */
/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_fractional Fractional Arithmetic Support
 The next table provides an overview of intrinsic functions to convert fractional values. Note that the
 TASKING VX-toolset C compiler for TriCore fully supports the fractional type so normally you should not
 need these intrinsic functions (except for __mulfractlong). For compatibility reasons the TASKING C
 compiler does support these functions.
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */

/** Count the consecutive number of bits that have the same value as bit 15 of an sfract
 */
asm short __clssf(sfract a)
{
% reg a
! "%d2"
    cls  %d2, a
}

/** Convert float to fract
 */
asm fract __float_to_fract(float a)
{
% reg a
! "%d2"
    ftoq31 %d2, a, 0
}

/** \brief Convert fract to float
 */
asm float __fract_to_float(fract a)
{
% reg a
! "%d2", "%d3"
    mov    %d3, 0
    q31tof %d2, a, %d3
}

/** Convert __laccum to fract
 */
asm fract __getfract(laccum a)
{
% reg a
! "%d2"
    dextr  %d2, a!H, a!L, 17
}

/** Multiply-add with rounding. Returns the rounded result of ( a + b * c )
 */
#ifdef INTRINSIC_WORKAROUND
extern sfract __mac_r_sf(sfract a, sfract b, sfract c);
#else
asm sfract __mac_r_sf(sfract a, sfract b, sfract c)
{
% reg a, b, c
! "%d2"
    maddrs.q %d2, a, bU, cU, 1
}
#endif

/** Multiply-add sfract. Returns ( a + b * c )
 */
#ifdef INTRINSIC_WORKAROUND
extern sfract __mac_sf(sfract a, sfract b, sfract c);
#else
asm sfract __mac_sf(sfract a, sfract b, sfract c)
{
% reg a, b, c
! "%d2"
    madds.q  %d2, a, bU, cU, 1
}
#endif

/** Integer part of the multiplication of a fract and a fract
 */
asm long __mulfractfract(fract a, fract b)
{
% reg a, b
! "%d2"
    mul.q %d2, a, b, 1
}

/** Integer part of the multiplication of a fract and a long
 */
asm long __mulfractlong(fract a, long b)
{
% reg a, b
! "%d2"
    mul.q %d2, a, b, 1
}

/** Convert fract to sfract
 */
asm sfract __round16(fract a)
{
% reg a
! "%d2"
    mov.u  %d2, 0x8000
    adds  %d2, a
    insert  %d2, %d0, 0, 0, 0x10
}

/** Convert signed short to sfract
 */
asm sfract __s16_to_sfract(short a)
{
% reg a
! "%d2"
    sh  %d2, a, 16
}

/** Convert sfract to signed short
 */
asm short __sfract_to_s16(sfract a)
{
% reg a
    sh  %d2, a, -16
}

/** Convert sfract to uint16
 */
asm volatile uint16 __sfract_to_u16(sfract a)
{
% reg a
! "%d2"
    sh  %d2, a, -16
}

/** Left/right shift of an __laccum
 */
asm laccum __shaaccum(laccum a, sint32 b)
{
% lab L0, L1; reg a, b
! "%d2", "%d3"
    jge   b, 0, L0
    sha   %d3, a!L, b
    rsub  b, b, 0
    dextr %d2, a!H, a!L, b
    j L1
L0:
    dextr %d2, a!H, a!L, b
    sha   %d2, a!L, b
L1:
}

/** Left/right shift of an fract
 */
#ifdef INTRINSIC_WORKAROUND
extern fract __shafracts(fract a, sint32 b);
#else
asm fract __shafracts(fract a, sint32 b)
{
% reg a, b
! "%d2"
    shas  %d2, a, b
}
#endif

/** Left/right shift of an sfract
 */
#ifdef INTRINSIC_WORKAROUND
extern sfract __shasfracts(sfract a, sint32 b);
#else
asm sfract __shasfracts(sfract a, sint32 b)
{
% reg a, b
! "%d2"
    shas %d2, a, b
}
#endif

/** Convert uint16 to sfract
 */
asm sfract __u16_to_sfract(uint16 a)
{
% reg a
! "%d2"
    sh  %d2, a, 16
}

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_insert Insert / Extract Bit-fields and Bits
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */

/** Extract a bit-field (bit pos to bit pos+width) from value
 */
extern sint32 __extr( sint32,  uint32,  const uint32) __attribute__((intrinsic_function(0x108, 0, "extr") ));

/** Same as __extr() but return bit-field as unsigned integer
 */
extern uint32 __extru( uint32,  uint32,  const uint32) __attribute__((intrinsic_function(0x108, 0, "extr.u") ));

/** Load a single bit.
 */
#define __getbit( address, bitoffset ) __extru( *(address), bitoffset, 1 )

/** Return trg but replace trgbit by srcbit in src.
 */
extern uint32 __ins( uint32,  const uint32,  uint32,  const uint32) __attribute__((intrinsic_function(0x121, 0, "ins.t") ));

/** Extract bit-field (width w bits starting at bit 0) from a and insert it in
 * b at position p.
 */
extern uint32 __insert( uint32,  uint32,  uint32,  const uint32) __attribute__((intrinsic_function(0x109, 0, "insert") ));

/** Return trg but replace trgbit by inverse of srcbit in src.
 */
extern uint32 __insn( uint32,  const uint32,  uint32,  const uint32) __attribute__((intrinsic_function(0x121, 0, "insn.t") ));

/** Atomic load-modify-store.
 */
#ifdef INTRINSIC_WORKAROUND
extern void __imaskldmst(uint32* a, sint32 b, sint32 p, const sint32 w);
#else
asm volatile void __imaskldmst(uint32* a, sint32 b, sint32 p, const sint32 w)
{
% reg a, b, p; con w
! "%d2", "%d3"
    imask %e2, b, p, w
    ldmst  [a]0, %e2
}
#endif

/** Store a single bit.
 */
#define __putbit(value,address,bitoffset) __imaskldmst(address,value,bitoffset,1)

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_interrupt_handling Interrupt Handling
 The next table provides an overview of the intrinsic functions to read or set interrupt handling.
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */

/** Set CPU priority number [0..255] (or [0..1023] for TriCore 1.6.x) and enable interrupts immediately at function entry
 */
extern void __bisr( const uint32) __attribute__((intrinsic_function(0x100, 0, "bisr") ));

/** Disable interrupts. Only supported for TriCore1
 */
extern void __disable( void) __attribute__((intrinsic_function(0x103, 0, "disable") ));

/** Disable interrupts and return previous interrupt state (enabled or disabled). Direct supported for TriCore1.6. Emulated on TC1.3.1
 */
#if defined INTRINSIC_WORKAROUND
extern sint32 __disable_and_save(void);
#endif

/** Enable interrupts immediately at function entry
 */
extern void __enable( void) __attribute__((intrinsic_function(0x103, 0, "enable") ));

/** Restore interrupt state. Direct supported for TriCore1.6. Emulated on TC1.3.1
 */
extern void __restore( sint32) __attribute__((intrinsic_function(0x104, 0, "restore") ));

/** Call a system call function number
 */
extern void __syscall( const uint32) __attribute__((intrinsic_function(0x100, 0, "syscall") ));

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_miscellaneous Miscellaneous Intrinsic Functions
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */

/**  Write back and invalidate cache address "p". Generates CACHEA.WI [Ab].
 */
extern void __cacheawi( void*) __attribute__((intrinsic_function(0x110, 0, "cachea.wi") ));

/**  Write back and invalidate cache address \"p\" and return post incremented
 * value of \"p\". Generates CACHEA.WI [Ab+].
 */
asm volatile uint8* __cacheawi_bo_post_inc(uint8* p)
{
% reg p
!
    cachea.wi [p + ]0
    mov.aa %a2, p
}

/**  Write back and invalidate cache index "p". Generates CACHEI.WI [Ab].
 */
asm volatile void __cacheiwi(uint8* p)
{
% reg p
!
    cachei.wi [p]
}

/** Initialize a circular pointer with a dynamically allocated buffer at run-time.
 */
asm circ_t __initcirc(void* buf, uint16 bufsize, uint16 byteindex)
{
% reg buf, bufsize, byteindex
! "%a2", "%a3"
    lea    %a2, [buf]0
    extr.u bufsize, bufsize, 0, 16
    insert bufsize, byteindex, bufsize, 16, 16
    mov.a  %a3, bufsize
}

/** Multiply two 32-bit numbers to an intermediate 64-bit result, and scale
 * back the result to 32 bits. To scale back the result, 32 bits are extracted
 * from the intermediate 64-bit result: bit 63-offset to bit 31-offset.
 */
asm volatile sint32 __mulsc(sint32 a, sint32 b, sint32 offset)
{
% reg a, b, offset
! "%d2", "%d3"
    mul  %e2, a, b
    dextr %d2, %d3, %d2, offset
}

/**  Rotate operand left count times. The bits that are shifted out are inserted at the right side (bit 31 is shifted to bit 0).
 */
asm volatile uint32 __rol(uint32 operand, uint32 count)
{
% reg operand, count
! "%d2"
    dextr %d2, operand, operand, count
}

/**  Rotate operand right count times. The bits that are shifted out are inserted at the left side (bit 0 is shifted to bit 31).
 */
asm volatile uint32 __ror(uint32 operand, uint32 count)
{
% reg operand, count
! "%d2"
    rsub count, count, 0
    dextr %d2, operand, operand, count
}

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_packed Packed Data Type Support
 The next table provides an overview of the intrinsic functions for initialization of packed data type.
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */

/**  Absolute value of __packb
*/
asm __packb __absb(__packb a)
{
% reg a
! "%d2"
    abs.b %d2, a
}

/**  Absolute value of __packhw
 */
asm __packhw __absh(__packhw a)
{
% reg a
! "%d2"
    abs.h %d2, a
}

/**  Absolute value of __packhw using saturation
 */
asm __packhw __abssh(__packhw a)
{
% reg a
! "%d2"
    abss.h %d2, a
}

/** \brief  Extract first byte from a __packb
 */
asm sint8 __extractbyte1(__packb a)
{
% reg a
! "%d2"
    extr  %d2, a, 0, 8
}

/** \brief  Extract second byte from a __packb
 */
asm sint8 __extractbyte2(__packb a)
{
% reg a
! "%d2"
    extr  %d2, a, 8, 8
}

/** \brief  Extract third byte from a __packb
 */
asm sint8 __extractbyte3(__packb a)
{
% reg a
! "%d2"
    extr  %d2, a, 16, 8
}

/** \brief  Extract fourth byte from a __packb
 */
asm sint8 __extractbyte4(__packb a)
{
% reg a
! "%d2"
    extr  %d2, a, 24, 8
}

/** \brief Extract first short from a __packhw
 */
asm short __extracthw1(__packhw a)
{
% reg a
! "%d2"
    extr  %d2, a, 0, 16
}

/** \brief Extract second short from a __packhw
 */
asm short __extracthw2(__packhw a)
{
% reg a
! "%d2"
    extr  %d2, a, 16, 16
}

/** Extract first unsigned byte from a __packb
 */
asm volatile uint8 __extractubyte1(__upackb a)
{
% reg a
! "%d2"
    extr  %d2, a, 0, 8
}

/** Extract second unsigned byte from a __packb
 */
asm volatile uint8 __extractubyte2(__upackb a)
{
% reg a
! "%d2"
    extr  %d2, a, 8, 8
}

/** Extract third unsigned byte from a __packb
 */
asm volatile uint8 __extractubyte3(__upackb a)
{
% reg a
! "%d2"
    extr  %d2, a, 16, 8
}

/** Extract fourth unsigned byte from a __packb
 */
asm volatile uint8 __extractubyte4(__upackb a)
{
% reg a
! "%d2"
    extr  %d2, a, 24, 8
}

/** Extract first uint16 from a __packhw
 */
asm volatile uint16 __extractuhw1(__upackhw a)
{
% reg a
! "%d2"
    extr  %d2, a, 0, 16
}

/** Extract second uint16 from a __packhw
 */
asm volatile uint16 __extractuhw2(__upackhw a)
{
% reg a
! "%d2"
    extr  %d2, a, 16, 16
}

/**  Extract first byte from a __packb
 */
asm sint8 __getbyte1(__packb* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 0, 8
}

/**  Extract second byte from a __packb
 */
asm sint8 __getbyte2(__packb* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 8, 8
}

/**  Extract third byte from a __packb
 */
asm sint8 __getbyte3(__packb* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 16, 8
}

/**  Extract fourth byte from a __packb
 */
asm sint8 __getbyte4(__packb* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 24, 8
}

/**  Extract first short from a __packhw
 */
asm short __gethw1(__packhw* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 0, 16
}

/**  Extract second short from a __packhw
 */
asm short __gethw2(__packhw* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 16, 16
}

/**  Extract first unsigned byte from a __packb
 */
asm volatile uint8 __getubyte1(__upackb* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 0, 8
}

/**  Extract second unsigned byte from a __packb
 */
asm volatile uint8 __getubyte2(__upackb* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 8, 8
}

/**  Extract third unsigned byte from a __packb
 */
asm volatile uint8 __getubyte3(__upackb* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 16, 8
}

/**  Extract fourth unsigned byte from a __packb
 */
asm volatile uint8 __getubyte4(__upackb* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 24, 8
}

/**  Extract first uint16 from a __packhw
 */
asm volatile uint16 __getuhw1(__upackhw* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 0, 16
}

/**  Extract second uint16 from a __packhw
 */
asm volatile uint16 __getuhw2(__upackhw* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 16, 16
}

/**  Initialize  __packb with four integers
 */
asm __packb __initpackb(sint32 a, sint32 b, sint32 c, sint32 d)
{
% reg a, b, c, d
! "%d2"
    insert  c, c, d, 8, 8
    insert  d, a, b, 8, 8
    insert  %d2, d, c, 16, 16
}

/** Initialize  __packb with a long integer
 */
asm __packb __initpackbl(long a)
{
% reg a
! "%d2"
    mov %d2, a
}

/** \brief  Initialize  __packhw with two integers
 */
asm __packhw __initpackhw(short a, short b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 16, 16
}

/**  Initialize  __packhw with a long integer
 */
asm __packhw __initpackhwl(long a)
{
% reg a
! "%d2"
    mov %d2, a
}

/** Initialize  __packb with four unsigned integers
 */
asm __upackb    __initupackb( uint32 a, uint32 b, uint32 c, uint32 d)
{
% reg a, b, c, d
! "%d2"
    insert  c, c, d, 8, 8
    insert  a, a, b, 8, 8
    insert  %d2, a, c, 16, 16
}

/**  Initialize  __packhw with two unsigned integers
 */
asm __upackhw    __initupackhw( uint16 a, uint16 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 16, 16
}

/** \brief  Insert sint8 into first byte of a __packb
 */
asm __packb __insertbyte1(__packb a, sint8 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 0, 8
}

/** \brief  Insert sint8 into second byte of a __packb
 */
asm __packb __insertbyte2(__packb a, sint8 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 8, 8
}

/** \brief  Insert sint8 into third byte of a __packb
 */
asm __packb __insertbyte3(__packb a, sint8 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 16, 8
}

/** \brief  Insert sint8 into fourth byte of a __packb
 */
asm __packb __insertbyte4(__packb a, sint8 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 24, 8
}

/**  Insert short into first halfword of a __packhw
 */
asm __packhw __inserthw1(__packhw a, short b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 0, 16
}

/**  Insert short into second halfword of a __packhw
 */
asm __packhw __inserthw2(__packhw a, short b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 16, 16
}

/** \brief  Insert uint8 into first unsigned byte of a __packb
 */
asm __upackb    __insertubyte1( __upackb a, uint8 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 0, 8
}

/** \brief  Insert uint8 into second unsigned byte of a __packb
 */
asm __upackb    __insertubyte2( __upackb a, uint8 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 8, 8
}

/** \brief  Insert uint8 into third unsigned byte of a __packb
 */
asm __upackb     __insertubyte3( __upackb a, uint8 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 16, 8
}

/** \brief  Insert uint8 into fourth unsigned byte of a __packb
 */
asm __upackb     __insertubyte4( __upackb a, uint8 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 24, 8
}

/**  Insert uint16 into first halfword of a __upackhw
 */
asm __upackhw    __insertuhw1( __upackhw a, uint16 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 0, 16
}

/**  Insert uint16 into second halfword of a __upackhw
 */
asm __upackhw    __insertuhw2( __upackhw a, uint16 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 16, 16
}

/**  Minimum of two  __packb values
 */
#ifdef INTRINSIC_WORKAROUND
extern __packb __minb(__packb a, __packb b);
#else
asm __packb __minb(__packb a, __packb b)
{
% reg a, b
! "%d2"
    min.b %d2, a, b
}
#endif

/**  Minimum of two __upackb  values
 */
asm __upackb     __minbu( __upackb  a, __upackb  b)
{
% reg a, b
! "%d2"
    min.bu %d2, a, b
}

/**  Minimum of two  __packhw values
 */
asm __packhw __minh(__packhw a, __packhw b)
{
% reg a, b
! "%d2"
    min.h %d2, a, b
}

/**  Minimum of two __upackhw values
 */
asm __upackhw    __minhu( __upackhw a, __upackhw b)
{
% reg a, b
! "%d2"
    min.hu %d2, a, b
}

/**  Insert sint8 into first byte of a __packb
 */
asm volatile void __setbyte1(__packb* a, sint8 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 0, 8
    st.w   [a], %d2
}

/**  Insert sint8 into second byte of a __packb
 */
asm volatile void __setbyte2(__packb* a, sint8 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 8, 8
    st.w   [a], %d2
}

/**  Insert sint8 into third byte of a __packb
 */
asm volatile void __setbyte3(__packb* a, sint8 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 16, 8
    st.w   [a], %d2
}

/**  Insert sint8 into fourth byte of a __packb
 */
asm volatile void __setbyte4(__packb* a, sint8 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 24, 8
    st.w   [a], %d2
}

/**  Insert short into first halfword of a __packhw
 */
asm volatile void __sethw1(__packhw* a, short b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 0, 16
    st.w   [a], %d2
}

/**  Insert short into second halfword of a __packhw
 */
asm volatile void __sethw2(__packhw* a, short b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 16, 16
    st.w   [a], %d2
}

/**  Insert uint8 into first byte of a __upackb
 */
asm volatile void __setubyte1(__upackb* a, uint8 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 0, 8
    st.w   [a], %d2
}

/**  Insert uint8 into second byte of a __upackb
 */
asm volatile void __setubyte2(__upackb* a, uint8 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 8, 8
    st.w   [a], %d2
}

/**  Insert uint8 into third byte of a __upackb
 */
asm volatile void __setubyte3(__upackb* a, uint8 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 16, 8
    st.w   [a], %d2
}

/**  Insert uint8 into fourth byte of a __upackb
 */
asm volatile void __setubyte4(__upackb* a, uint8 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 24, 8
    st.w   [a], %d2
}

/**  Insert uint16 into first halfword of a __upackhw
 */
asm volatile void __setuhw1(__upackhw* a, uint16 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 0, 16
    st.w   [a], %d2
}

/**  Insert uint16 into second halfword of a __upackhw
 */
asm volatile void __setuhw2(__upackhw* a, uint16 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 16, 16
    st.w   [a], %d2
}

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_register Register Handling
 The next table provides an overview of the intrinsic functions that you can use to access control registers.
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */

/**  Return absolute value
 */
extern sint32 __abs( sint32) __attribute__((intrinsic_pseudo(1, "abs") ));

/** Return absolue difference of two integers
 */
extern sint32 __absdif( sint32,  sint32) __attribute__((intrinsic_pseudo(1, "absdif") ));

/**  Return absolute value with saturation
 */
extern sint32 __abss( sint32) __attribute__((intrinsic_pseudo(1, "abss") ));

/**  Count leading ones in int
 */
extern sint32 __clo( sint32) __attribute__((intrinsic_pseudo(1, "clo") ));

/**  Count number of redundant sign bits (all consecutive bits with the same value as bit 31
 */
extern sint32 __cls( sint32) __attribute__((intrinsic_pseudo(1, "cls") ));

/**  Count leading zeros in int
 */
extern sint32 __clz( sint32) __attribute__((intrinsic_pseudo(1, "clz") ));

/**  Return absolute double precision floating-point value
 */
asm double __fabs(double d)
{
% reg d
! "%d2"
    insert  %d2, d, 0, 31, 1
}

/**  Return absolute floating-point value
 */
asm float __fabsf(float f)
{
% reg f
! "%d2"
    insert %d2, f, 0, 31, 1
}

/**  Move contents of the addressed core SFR into a data register
 */
extern sint32 __mfcr( const uint32) __attribute__((intrinsic_function(0x101, 0, "mfcr") ));

/**  Move contents of a data register (second sint32) to the addressed core SFR (first sint32)
 */
extern void __mtcr( const uint32,  sint32) __attribute__((intrinsic_function(0x102, 0, "mtcr") ));

/**  Return parity
 */
asm volatile sint32 __parity(sint32 a)
{
% reg a
! "%d2"
    parity %d2, a
}

/**  Return saturated byte
 */
asm sint8 __satb(sint32 a)
{
% reg a
! "%d2"
    sat.b %d2, a
}

/**  Return saturated unsigned byte
 */
asm volatile uint8 __satbu(sint32 a)
{
% reg a
! "%d2"
    sat.bu %d2, a
}

/**  Return saturated halfword
 */
asm short __sath(sint32 a)
{
% reg a
! "%d2"
    sat.h %d2, a
}

/**  Return saturated unsignedhalfword
 */
asm volatile uint16 __sathu(sint32 a)
{
% reg a
! "%d2"
    sat.hu %d2, a
}

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_saturation Saturation Arithmetic Support
 These intrinsics support saturation arithmetic
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */
/** add signed with saturation
 */
extern sint32 __adds( sint32,  sint32) __attribute__((intrinsic_pseudo(1, "adds") ));

/** add unsigned with saturation
 */
asm volatile uint32 __addsu(uint32 a, uint32 b)
{
% reg a, b
! "%d2"
    adds.u %d2, a, b
}

/** substract signed with saturation
 */
asm volatile sint32 __subs(sint32 a, sint32 b)
{
% reg a, b
! "%d2"
    subs %d2, a, b
}

/** substract unsigned with saturation
 */
asm volatile uint32 __subsu(uint32 a, uint32 b)
{
% reg a, b
! "%d2"
    subs.u %d2, a, b
}

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_single_assembly Insert Single Assembly Instruction
 The next table provides an overview of the intrinsic functions that you can use to insert a single assembly
 instruction.You can also use inline assembly but these intrinsics provide a shorthand for frequently used
 assembly instructions.
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */

/** Insert DEBUG instruction
 */
extern void __debug( void) __attribute__((intrinsic_function(0x103, 0, "debug") ));

/** Insert DSYNC instruction
 */
extern void __dsync( void) __attribute__((intrinsic_function(0x103, 0, "dsync") ));

/** Insert ISYNC instruction
 */
extern void __isync( void) __attribute__((intrinsic_function(0x103, 0, "isync") ));

/** Insert LDMST instruction. Note that all operands must be word-aligned.
 */
#ifdef INTRINSIC_WORKAROUND
#define __ldmst __ldmst_c
#else
asm volatile void __ldmst(volatile void *address, uint32 mask, uint32 value)
{
%reg address, mask, value;
!"%d2", "%d3"
 mov     %d3, mask
 mov     %d2, value
 ldmst	[address],%e2
}

#endif

/** Insert NOP instruction
 */
extern void __nop( void) __attribute__((intrinsic_function(0x103, 0, "nop") ));

/** Insert a loop over n NOP instruction
 */
asm volatile void __nops(void* cnt)
{
% lab L0;
    reg cnt
    add.a cnt, -1
L0:
    nop
    loop cnt, L0
}

/** Insert a loop over n times 1000 NOP instruction
 */
asm volatile void __nops1000(uint32 x)
{
% reg x;
    lab L0, L1
! "%a2", "%a3"
    mov.a %a2, x
L1:
    lea   %a3, 999
L0:
    nop
    nop
    loop  %a3, L0
    loop  %a2, L1
}

/** Insert RSLCX instruction
 */
extern void __rslcx( void) __attribute__((intrinsic_function(0x103, 0, "rslcx") ));

/** Insert SVLCX instruction
 */
extern void __svlcx( void) __attribute__((intrinsic_function(0x103, 0, "svlcx") ));

/** Insert SWAP instruction. Note that all operands must be word-aligned.
 */
#ifdef INTRINSIC_WORKAROUND
extern uint32 __swap(void* place, uint32 value);
#else
asm volatile uint32 __swap(void* place, uint32 value)
{
% reg place, value
! "%d2"
    mov %d2, value
    swap.w [place], %d2
}
#endif

// FIXME
asm volatile unsigned int __cmpAndSwap(unsigned int *address, unsigned long value, unsigned long CmpVal)
{
%reg value, address, CmpVal
! "%d0", "%d1"
  mov %d0,value
  mov %d1,CmpVal
  cmpswap.w %e0, [address]
}
/** \} */

/** Insert n NOP instruction
 */
//#info "NOP: Feature not yet implemented."

#define __setareg(areg,val) ___setareg(areg,val)
/* we need to use a15 for the address register and not direct that the compiler this will not remove */
#define ___setareg(areg,val) \
    { __asm ("#$$bp"); \
      __asm ("  movh.a\t %a15,"#val"@ha\n"); \
      __asm ("  lea\t %a15,[%a15]"#val"@l\n"); \
      __asm ("  mov.aa %"#areg", %a15\n"); \
      __asm ("#$$ep"); }

/* FIXME check that the compiler take in account that d0 is used by the inline function */
asm volatile void __stopPerfCounters(void)
{
! "%d0"
    mov %d0,0
    mtcr 0xFC00,%d0
    isync
}

/* *INDENT-ON* */

/******************************************************************************/
#endif /* IFXCPU_INTRINSICSDCC_H */
