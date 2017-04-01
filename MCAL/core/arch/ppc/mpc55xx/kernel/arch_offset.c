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
#include "arch_stack.h"
#include "Compiler.h"
#include "mpc55xx.h"
#include "Os.h"


#if defined(__GNUC__) || defined(__ghs__)
#define DECLARE(sym,val) \
    __asm("#define " #sym " %0" : : "i" ((val)))

#elif defined(__CWCC__)

#pragma section ".apa" ".apa"

#define DECLARE(_var,_offset) \
    __declspec(section ".apa") char _var[100+_offset]
#elif (defined(__DCC__))
#define DECLARE(_sym,_val) \
    const int arc_dummy_ ## _sym = _val
#endif

#if defined(__GNUC__) || defined(__ghs__)
void  oil_foo(void);

void  oil_foo(void) {
#endif


/* Exceptions */
    DECLARE(EXC_FRM_SIZE,	sizeof(Os_ExceptionFrameType));
    DECLARE(EXC_FRM_SP,		offsetof(Os_ExceptionFrameType, sp));
    DECLARE(EXC_FRM_SRR0,	offsetof(Os_ExceptionFrameType, srr0));
    DECLARE(EXC_FRM_SRR1,	offsetof(Os_ExceptionFrameType, srr1));
    DECLARE(EXC_FRM_LR,		offsetof(Os_ExceptionFrameType, lr));
    DECLARE(EXC_FRM_CTR,	offsetof(Os_ExceptionFrameType, ctr));
    DECLARE(EXC_FRM_XER,	offsetof(Os_ExceptionFrameType, xer));
    DECLARE(EXC_FRM_CR,		offsetof(Os_ExceptionFrameType, cr));
    DECLARE(EXC_FRM_R3,		offsetof(Os_ExceptionFrameType, r3));
    DECLARE(EXC_FRM_VECTOR,	offsetof(Os_ExceptionFrameType, vector));
    DECLARE(EXC_FRM_USPRG0,	offsetof(Os_ExceptionFrameType, usprg0));

/* Volatile frame */
    DECLARE(VOLATILE_FRM_SIZE,	sizeof(Os_VolatileFrameType)+16);
    DECLARE(VOLATILE_FRM_R0,	offsetof(Os_VolatileFrameType, r0));
    DECLARE(VOLATILE_FRM_R3,	offsetof(Os_VolatileFrameType, r3));
    DECLARE(VOLATILE_FRM_R4,	offsetof(Os_VolatileFrameType, r4));
    DECLARE(VOLATILE_FRM_R5,	offsetof(Os_VolatileFrameType, r5));
    DECLARE(VOLATILE_FRM_R6,	offsetof(Os_VolatileFrameType, r6));
    DECLARE(VOLATILE_FRM_R7,	offsetof(Os_VolatileFrameType, r7));
    DECLARE(VOLATILE_FRM_R8,	offsetof(Os_VolatileFrameType, r8));
    DECLARE(VOLATILE_FRM_R9,	offsetof(Os_VolatileFrameType, r9));
    DECLARE(VOLATILE_FRM_R10,	offsetof(Os_VolatileFrameType, r10));
    DECLARE(VOLATILE_FRM_R11,	offsetof(Os_VolatileFrameType, r11));
    DECLARE(VOLATILE_FRM_R12,	offsetof(Os_VolatileFrameType, r12));
    DECLARE(VOLATILE_FRM_LR,	offsetof(Os_VolatileFrameType, lr));
    DECLARE(VOLATILE_FRM_CTR,	offsetof(Os_VolatileFrameType, ctr));
    DECLARE(VOLATILE_FRM_XER,	offsetof(Os_VolatileFrameType, xer));
    DECLARE(VOLATILE_FRM_CR,	offsetof(Os_VolatileFrameType, cr));

    /* Exception info */
    DECLARE(MPC5XXX_INFO_SIZE,	sizeof(Mpc5xxx_ExceptionInfoType));
    DECLARE(MPC5XXX_INFO_C_SRR0,offsetof(Mpc5xxx_ExceptionInfoType, c_srr0));
    DECLARE(MPC5XXX_INFO_C_SRR1,offsetof(Mpc5xxx_ExceptionInfoType, c_srr1));
    DECLARE(MPC5XXX_INFO_MCSR,	offsetof(Mpc5xxx_ExceptionInfoType, mcsr));
    DECLARE(MPC5XXX_INFO_ESR,	offsetof(Mpc5xxx_ExceptionInfoType, esr));
    DECLARE(MPC5XXX_INFO_DEAR,	offsetof(Mpc5xxx_ExceptionInfoType, dear));

    DECLARE(FUNC_FRM_SIZE,	sizeof(Os_FuncFrameType));
    DECLARE(FUNC_FRM_CR, offsetof(Os_FuncFrameType,cr));
    DECLARE(FUNC_FRM_LR, offsetof(Os_FuncFrameType,lr));
    DECLARE(FUNC_FRM_PATTERN, offsetof(Os_FuncFrameType,pattern));
    DECLARE(FUNC_FRM_R14, offsetof(Os_FuncFrameType,r14));
    DECLARE(FUNC_FRM_R15, offsetof(Os_FuncFrameType,r15));
    DECLARE(FUNC_FRM_R16, offsetof(Os_FuncFrameType,r16));
    DECLARE(FUNC_FRM_R17, offsetof(Os_FuncFrameType,r17));
    DECLARE(FUNC_FRM_R18, offsetof(Os_FuncFrameType,r18));
    DECLARE(FUNC_FRM_R19, offsetof(Os_FuncFrameType,r19));
    DECLARE(FUNC_FRM_R20, offsetof(Os_FuncFrameType,r20));
    DECLARE(FUNC_FRM_R21, offsetof(Os_FuncFrameType,r21));
    DECLARE(FUNC_FRM_R22, offsetof(Os_FuncFrameType,r22));
    DECLARE(FUNC_FRM_R23, offsetof(Os_FuncFrameType,r23));
    DECLARE(FUNC_FRM_R24, offsetof(Os_FuncFrameType,r24));
    DECLARE(FUNC_FRM_R25, offsetof(Os_FuncFrameType,r25));
    DECLARE(FUNC_FRM_R26, offsetof(Os_FuncFrameType,r26));
    DECLARE(FUNC_FRM_R27, offsetof(Os_FuncFrameType,r27));
    DECLARE(FUNC_FRM_R28, offsetof(Os_FuncFrameType,r28));
    DECLARE(FUNC_FRM_R29, offsetof(Os_FuncFrameType,r29));
    DECLARE(FUNC_FRM_R30, offsetof(Os_FuncFrameType,r30));
    DECLARE(FUNC_FRM_R31, offsetof(Os_FuncFrameType,r31));

#if defined(CFG_SPE) || defined(CFG_EFPU)
    DECLARE(ISR_FRM_SPE_FSCR, offsetof(Os_IsrFrameType,fscr));
#endif
#if defined(CFG_SPE)
    DECLARE(ISR_FRM_SPE_ACC, offsetof(Os_IsrFrameType,acc));
    DECLARE(ISR_FRM_R3, offsetof(Os_IsrFrameType,r3));
#endif
    DECLARE(ISR_FRM_SIZE,	sizeof(Os_IsrFrameType));
    DECLARE(ISR_FRM_R0, offsetof(Os_IsrFrameType,r0));
    DECLARE(ISR_FRM_R4, offsetof(Os_IsrFrameType,r4));
    DECLARE(ISR_FRM_R5, offsetof(Os_IsrFrameType,r5));
    DECLARE(ISR_FRM_R6, offsetof(Os_IsrFrameType,r6));
    DECLARE(ISR_FRM_R7, offsetof(Os_IsrFrameType,r7));
    DECLARE(ISR_FRM_R8, offsetof(Os_IsrFrameType,r8));
    DECLARE(ISR_FRM_R9, offsetof(Os_IsrFrameType,r9));
    DECLARE(ISR_FRM_R10, offsetof(Os_IsrFrameType,r10));
    DECLARE(ISR_FRM_R11, offsetof(Os_IsrFrameType,r11));
    DECLARE(ISR_FRM_R12, offsetof(Os_IsrFrameType,r12));
    DECLARE(ISR_FRM_R14, offsetof(Os_IsrFrameType,r14));
    DECLARE(ISR_FRM_R15, offsetof(Os_IsrFrameType,r15));
    DECLARE(ISR_FRM_R16, offsetof(Os_IsrFrameType,r16));
    DECLARE(ISR_FRM_R17, offsetof(Os_IsrFrameType,r17));
    DECLARE(ISR_FRM_R18, offsetof(Os_IsrFrameType,r18));
    DECLARE(ISR_FRM_R19, offsetof(Os_IsrFrameType,r19));
    DECLARE(ISR_FRM_R20, offsetof(Os_IsrFrameType,r20));
    DECLARE(ISR_FRM_R21, offsetof(Os_IsrFrameType,r21));
    DECLARE(ISR_FRM_R22, offsetof(Os_IsrFrameType,r22));
    DECLARE(ISR_FRM_R23, offsetof(Os_IsrFrameType,r23));
    DECLARE(ISR_FRM_R24, offsetof(Os_IsrFrameType,r24));
    DECLARE(ISR_FRM_R25, offsetof(Os_IsrFrameType,r25));
    DECLARE(ISR_FRM_R26, offsetof(Os_IsrFrameType,r26));
    DECLARE(ISR_FRM_R27, offsetof(Os_IsrFrameType,r27));
    DECLARE(ISR_FRM_R28, offsetof(Os_IsrFrameType,r28));
    DECLARE(ISR_FRM_R29, offsetof(Os_IsrFrameType,r29));
    DECLARE(ISR_FRM_R30, offsetof(Os_IsrFrameType,r30));
    DECLARE(ISR_FRM_R31, offsetof(Os_IsrFrameType,r31));
    DECLARE(ISR_FRM_PATTERN, offsetof(Os_IsrFrameType,pattern));
    DECLARE(INTC_HI, ((uint32)&INTC >> 16));
    DECLARE(INTC_LO, ((uint32)&INTC & 0xFFFF));
#if defined(CFG_MPC5516) || defined(CFG_MPC5668)
    DECLARE(INTC_IACR_PRC0_OFFS, offsetof(struct INTC_tag,IACKR_PRC0));
    DECLARE(INTC_IACR_PRC1_OFFS, offsetof(struct INTC_tag,IACKR_PRC1));
    DECLARE(INTC_EOIR_PRC0_OFFS, offsetof(struct INTC_tag,EOIR_PRC0));
    DECLARE(INTC_EOIR_PRC1_OFFS, offsetof(struct INTC_tag,EOIR_PRC1));
#elif defined(CFG_MPC5777M)
    DECLARE(INTC_IACR_OFFS, offsetof(struct INTC_tag,MPC5777M_INTC_REG_IACKR));
    DECLARE(INTC_EOIR_OFFS, offsetof(struct INTC_tag,MPC5777M_INTC_REG_EOIR));
#else
    DECLARE(INTC_IACR_OFFS, offsetof(struct INTC_tag,IACKR));
    DECLARE(INTC_EOIR_OFFS, offsetof(struct INTC_tag,EOIR));
#endif
    DECLARE(INTC_SSCIR0_OFFS, offsetof(struct INTC_tag,SSCIR));
    DECLARE(NUM_SOFT_INT, sizeof(INTC.SSCIR) / sizeof(INTC.SSCIR[0]));


#if (OS_SC3 == STD_ON)
    DECLARE(OS_SC3_ASM, 1);
#endif
#if (OS_SC4 == STD_ON)
    DECLARE(OS_SC4_ASM, 1);
#endif


#if (OS_SC3 == STD_ON) || (OS_SC4 == STD_ON)
    DECLARE(SYS_CALL_CNT_ASM , SYS_CALL_CNT);
    DECLARE(E_OS_TRUSTED_INDEX_ASM , E_OS_TRUSTED_INDEX);
    DECLARE(E_OS_TRUSTED_FUNC_ASM , E_OS_TRUSTED_FUNC);
#endif
    DECLARE(E_OS_BAD_CONTEXT_ASM , E_OS_BAD_CONTEXT);

#if defined(__GNUC__) || defined(__ghs__)
}
#endif


