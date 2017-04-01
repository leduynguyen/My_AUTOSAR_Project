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

#include "arc.h"
#include "irq_types.h"

#include "core_cr4.h"
#include "asm_arm.h"

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/

struct ExcAbort {
    uint32 r0;
    uint32 r1;
    uint32 r2;
    uint32 r3;
    uint32 r4;
    uint32 r5;
    uint32 r6;
    uint32 r7;
    uint32 r8;
    uint32 r9;
    uint32 r10;
    uint32 r11;
    uint32 r12;
    uint32 lr;
    uint32 lr_abt;
    uint32 sp_abt;

};

/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

extern uint32_t Cpu_ExceptionHandler(uint32_t exceptionVector);

#if defined(CFG_DEBUG_EXCEPTIONS)

/**
 * Function to extract stacked registers
 *
 * @param stackPtr
 */
static void debugException( uint32_t type , uint32_t *stackPtr )
{
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;
    uint32_t pc;
    uint32_t xpsr;
    uint32_t ifar;
    uint32_t ifsr;
    uint32_t dfar;
    uint32_t dfsr;

    r0 = stackPtr[ 0 ];
    r1 = stackPtr[ 1 ];
    r2 = stackPtr[ 2 ];
    r3 = stackPtr[ 3 ];

    r12 = stackPtr[ 12 ];
    lr = stackPtr[ 13 ];
    pc = stackPtr[ 14 ];
    xpsr = stackPtr[ 15 ];

    switch(type) {
    case 0ul:
        /* Prefetch abort */

        /* IFAR holds the faulting address of a Prefetch Abort exception */
        ifar = CoreGetIFAR();

        /*  PMSAv7 IFSR encodings
         * IFSR[3:0]
         *  0001  - Alignment fault
         *  0000  - Background fault, MPU
         *  1101  - Permission fault, MPU
         *  0010  - Debug event
         *  1000  - Synchronous external abort
         *  etc.
         * */
        ifsr = CoreGetIFSR();

        (void)ifar;
        (void)ifsr;

        while(1) {};

        break;
    case 1ul:
        /* Data abort */

        /* IFAR holds the faulting address of a Prefetch Abort exception */
        dfar = CoreGetDFAR();

        /*   PMSAv7 DFSR encodings
         * DFSR[3:0]
         *  0001  - Alignment fault
         *  0000  - Background fault, MPU
         *  1101  - Permission fault, MPU
         *  0010  - Debug event
         *  1000  - Synchronous external abort
         *  etc.
         * */
        dfsr = CoreGetDFSR();

        (void)dfar;
        (void)dfsr;

        while(1) {};

        break;
    default:
        /* We should not get here for the other modes */
        while(1) {};
        break;
    }

    (void)r0;
    (void)r1;
    (void)r2;
    (void)r3;
    (void)r12;
    (void)pc;
    (void)xpsr;
    (void)lr;
    (void)ifar;

    while(1) {};
}
#endif

/**
 * Gets the instruction length of instructions at an address.
 *
 * @param instrAddr
 * @return
 */
static uint32_t adjustReturnAddr( uint32_t instrAddr ) {

    uint16_t fh = *(uint16_t *)(instrAddr);

    /*
     * From TRM:
     * The Thumb instruction stream is a sequence of halfword-aligned halfwords.
     * Each Thumb instruction is either a single 16-bit halfword in that stream,
     * or a 32-bit instruction consisting of two consecutive halfwords in that stream.
     * If the value of bits[15:11] of the halfword being decoded is one of the following,
     * the halfword is the first halfword of a 32-bit instruction:
     *  - 0b11101
     *  - 0b11110
     *  - 0b11111.
     * Otherwise, the halfword is a 16-bit instruction.
     */

    fh = fh & 0xf800U;
    if( (fh == 0xe800U) || (fh == 0xf000U) || (fh == 0xf800U) ) {
        instrAddr += 4;     /* 32-bit */
    } else {
        instrAddr += 2;     /* 16-bit */
    }

    return instrAddr;
}



/**
 * Calls higher level functions to handle the exception.
 *
 * @param exception The exception number
 * @param spr       The SPR number
 * @return
 */
static void handleException( uint32_t exception, struct ExcAbort *sP ) {
    uint32_t rv;

    rv = Cpu_ExceptionHandler( exception );
    if( rv & EXC_NOT_HANDLED ) {
        /* The exception was not handled */
        Os_Arc_Panic(exception,NULL);
        /* we don't get back here */
    }

    if( rv & EXC_ADJUST_ADDR ) {

        sP->lr_abt = adjustReturnAddr( sP->lr_abt );
    }
}

/**
 * Called from handler
 *
 * @param type
 * @param stackPtr
 */

void Mcu_Arc_HandleException( uint32_t type, struct ExcAbort *sP )
{
#if defined(CFG_DEBUG_EXCEPTIONS)
    debugException(type,stackPtr);
#else
    handleException(type, sP);
#endif
}


