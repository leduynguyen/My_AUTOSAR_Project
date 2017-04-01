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
 * REF
 *
 *
 * DESCRIPTION
 *
 * REGISTER
 *
 *   CPU
 *
 *    From "3.1  Program Registers" in the RH850G3M
 *
 *
 *     #       V  name Description
 *     ---------------------------------------
 *     r0	           always 0
 *     r1              assembler reserved register
 *     r2              used by OS
 *     r3         sp   Stack Pointer
 *     r4         gp   Global Pointer (data)
 *     r5         tp   Text Pointer (code)
 *     r6              arg 1
 *     r7              arg 2
 *     r8              arg 3
 *     r9              arg 4
 *     r20-r29         Preserved by callee
 *     r30             Element Pointer(EP)
 *     r31             Link Pointer (LP)
 *
 *   OTHER
 *
 * Q
 *  EI - "interrupt" exceptions
 *  FE - exceptions
 *
 *
 * EXCEPTION
 *  xPC  <- PC
 *  xPSW <- PSW
 *  xIC  <- Exception cause code is
 *
 *
 *
 * - We need to use a large context here since it
 *   manipulates PSR when it return (ie rfeia	sp! )
 * - Os_StackSetup() will setup the stack so it points
 *   with space for the context
 *
 *
 *  Address  Description
 *  ---------------------------------------
 *   HIGH
 *    ^
 *    |         r0
 *    |         ...
 *    |         r30
 *    |         r31
 *    |         x
 *    |         x
 *    |        xPSW
 *    |         xPC
 *    |          8 -- REGS ----
 *    |          4 context indicator
 *    |          0 stack
 *             ...    <---- pcbPtr->stack.curr will point here at this stage..
 *   LOW
 *
 *
 *   PSW-.
 *
 *   Exception Table
 *     See "Table 4-4  Selection of Base Register/Offset Address"
 *
 *   RBASE - Set to CPU0: 0x0000_0000 and CPU1: 0x0080_0000
 *
 *
 *
 *   USAGE
 *
 *   FRAME
 *
 * EXCEPTION/IRQ TABLE
 *
 * EXCEPTION/IRQ FLOW
 *
 */


#ifndef ARCH_STACK_H_
#define ARCH_STACK_H_

/* Minimum alignment req */
#define ARCH_ALIGN		4

/* Small context (task swap==function call) */
#define SAVE_NVGPR(_x,_y)
#define RESTORE_NVGPR(_x,_y)

/* Save volatile regs, NOT preserved by function calls */
#define SAVE_VGPR(_x,_y)
#define RESTORE_VGPR(_x,_y)

/* Large context (interrupt) */
#define SAVE_ALL_GPR(_x,_y)
#define RESTORE_ALL_GPR(_x,_y)


// NVREGS: r0+r1+r2+r3+r4+r5+r6+r7+r8+r9+r10+r11+r12+lr = 14*4 = 40
#define NVGPR_SIZE		56
// VGPR: 9*4 = 36
//#define VGPR_SIZE		36
// SP + context
#define C_SIZE			8
#define VGPR_LR_OFF		(C_SIZE+NVGPR_SIZE-4)
#define C_CONTEXT_OFFS  4
#define C_SP_OFF 		0
#define SC_SIZE			(NVGPR_SIZE+C_SIZE)
/*
 * FULL_PATTERN is used indicate that a full register context is on the stack.
 * FUNC_PATTERN indicates that a function register context is  on the stack
 */

#define FUNC_PATTERN	0xde		/* Small context */
#define ISR_PATTERN		0xad		/*  */
#define LC_PATTERN 		ISR_PATTERN


#if !defined(_ASSEMBLER_)
#include <stdint.h>


typedef struct {
    uint32_t xpc;
    uint32_t xpsw;
    uint32_t xic;
    uint32_t pad;

    uint32_t r31;
    uint32_t r30;
    uint32_t r29;
    uint32_t r28;

    uint32_t r27;
    uint32_t r26;
    uint32_t r25;
    uint32_t r24;

    uint32_t r23;
    uint32_t r22;
    uint32_t r21;
    uint32_t r20;

    uint32_t r19;
    uint32_t r18;
    uint32_t r17;
    uint32_t r16;

    uint32_t r15;
    uint32_t r14;
    uint32_t r13;
    uint32_t r12;

    uint32_t r11;
    uint32_t r10;
    uint32_t r9;
    uint32_t r8;

    uint32_t r7;
    uint32_t r6;
    uint32_t r5;
    uint32_t r4;

    uint32_t r3;
    uint32_t r2;
    uint32_t r1;
    uint32_t r0;
} Os_IsrFrameType;


#endif /* !defined(_ASSEMLBER_) */
#endif /* ARCH_STACK_H_ */
