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

#include "os_i.h"
#include "Cpu.h"
//#include "arch_stack.h"
#include "IfxCpu_reg.h"
#include "machine/intrinsics.h"

#define CSA_TO_ADDRESS(_csa)	( (((_csa) & 0x000f0000UL) << 12U) | (((_csa) & 0xffffL) << 6U ) )
#define ADDRESS_TO_CSA(_addr)	( (((( _addr ))&0xf0000000UL ) >> 12U) | ((( _addr ) & 0x003FFFC0UL ) >> 6U ) )


extern void Os_TaskPost( void );

/**
 * Function make sure that we switch to supervisor mode(rfi) before
 * we call a task for the first time.
 */

void Os_ArchFirstCall( void )
{
}

void *Os_ArchGetStackPtr( void ) {

    return 0;
}

unsigned int Os_ArchGetScSize( void ) {
    return 16;
}

void Os_ArchSetTaskEntry(OsTaskVarType *pcbPtr ) {
}


typedef struct {
    uint32 pcxi;
    uint32 a11_ra;
    uint32 a2;
    uint32 a3;
    uint32 d0;
    uint32 d1;
    uint32 d2;
    uint32 d3;
    uint32 a4;
    uint32 a5;
    uint32 a6;
    uint32 a7;
    uint32 d4;
    uint32 d5;
    uint32 d6;
    uint32 d7;
} Os_ContextLowType;

typedef struct {
    uint32 pcxi;
    uint32 psw;
    uint32 a10_sp;
    uint32 a11_ra;
    uint32 d8;
    uint32 d9;
    uint32 d10;
    uint32 d11;
    uint32 a12;
    uint32 a13;
    uint32 a14;
    uint32 a15;
    uint32 d12;
    uint32 d13;
    uint32 d14;
    uint32 d15;
} Os_ContextHighType;


volatile uint32 bepa = 0x123;

#if 0
void dummy( void ) {
    Os_Sys[0].currTaskPtr = 1111;
}
#endif
#define REGS_CONTEXT_NR		15


#define BAD_		0x0uL

/**
 * Return CSAs back to the freelist until pxci==0
 *
 * @param pcxi
 */
void Os_ArchFree( uint32_t pcxi ) {

    Os_ContextHighType *CSAPtr =  (Os_ContextHighType *)CSA_TO_ADDRESS(pcxi);
    uint32_t fcx;

    /* Find last, pcxi should be 0 */
    while( CSAPtr->pcxi != 0 ) {
        _dsync();
        CSAPtr = (Os_ContextHighType *)CSA_TO_ADDRESS(CSAPtr->pcxi);
    }

    /* Get the free-list pointer */
    fcx = __mfcr( CPU_FCX );
    _isync();

    CSAPtr->pcxi = fcx;

    /* Set new free list */
    __mtcr( CPU_FCX, pcxi);
    _isync();
}


void Os_ArchSetupContext( OsTaskVarType *pcbPtr ) {
    /* Note!
     *
     * Lots of _isync() and _dsync() here. The manual basically say that
     * you should do :
     * - "isync" after each special function register modification.
     * - "dsync" before reading the CSA stuff
     */

    uint32 fcx;
    Os_ContextLowType *lowerCSAPtr;
    Os_ContextHighType *upperCSAPtr;
    Os_ContextHighType *postCSAPtr;
    Os_ContextHighType *rootCSAPtr;

    /* Grab free-list pointer */
    fcx = __mfcr( CPU_FCX );
    _isync();

    /* Grab a number of entries from the free-list */
    _dsync();
    lowerCSAPtr =  (Os_ContextLowType *)CSA_TO_ADDRESS(fcx);

    _dsync();
    upperCSAPtr = (Os_ContextHighType *)CSA_TO_ADDRESS(lowerCSAPtr->pcxi);

    _dsync();
    postCSAPtr =  (Os_ContextHighType *)CSA_TO_ADDRESS(upperCSAPtr->pcxi);

    _dsync();
    rootCSAPtr =  (Os_ContextHighType *)CSA_TO_ADDRESS(postCSAPtr->pcxi);

    /* Save pointer to rootCSA */
    pcbPtr->regs[REGS_CONTEXT_NR] = postCSAPtr->pcxi;

    /* We have taken two entries, write a new FCX */
    __mtcr( CPU_FCX, rootCSAPtr->pcxi);
    _isync();

    if( rootCSAPtr->pcxi == BAD_ ) {
        asm volatile("debug");
    }

    postCSAPtr->psw = 0x00000b02UL;
    postCSAPtr->d8 = 0x99887766UL;
    postCSAPtr->a11_ra = (uint32_t)0x80000020UL; // pcbPtr->constPtr->entry;
    postCSAPtr->a10_sp = (uint32)pcbPtr->stack.curr;
    postCSAPtr->pcxi |= (1UL<<20U);

    rootCSAPtr->pcxi = BAD_;	/* Indicate that it's ended there */


    /* Clear the CSAs */

    _dsync();
    /* Setup the stack */
    upperCSAPtr->a10_sp = (uint32)pcbPtr->stack.curr;

    /* PRS = 00b  -> Protection Register Set 3 (N/A if not memory protection ?)
     * IO  = 10b  -> Supervisor Mode
     * IS  = 0b   ->  User Stack
     * GW  = 0b   ->  Write permission to global registers A[0], A[1], A[8],A[9] is disabled.
     * CDE = 0
     * CDC = 111111b -> Disable call depth counting.... at least for now.
     * */
    upperCSAPtr->psw = 0x00000b02UL;

    /* To be fixed: hmm, when we pop lower, do the RA make us end up somewhere we dont want.....
     * To be fixed: Os_TaskPost should really be in here */
    upperCSAPtr->a11_ra = (uint32_t)pcbPtr->constPtr->entry;
    lowerCSAPtr->a11_ra = (uint32_t)pcbPtr->constPtr->entry;

    /* Some values just so we know that we are in the right context */
    lowerCSAPtr->a2 = 0x22222222uL;
    upperCSAPtr->d15 = 0x15151515uL;
    upperCSAPtr->pcxi |= (1UL<<20U);    /* Post is upper */
    upperCSAPtr->a11_ra = Os_TaskPost;

    /* When lower will be popped this will be the new CPU_PCXI.
     * Sooo, when upper is restored the ICR.IE will have this value */
    lowerCSAPtr->pcxi |= (1UL<<20U) | (1UL<<21U) ;	/* Lower point to upper so set UL=1, set IE=1 */

    /* Save address to CSA on stack (we later use "rslcx" to pop the context back so we want it on CSA format */
    *(uint32 *)pcbPtr->stack.curr = ADDRESS_TO_CSA((uint32)lowerCSAPtr);

    /* Start a task with RFE (possibly RET?) since that is the only way to restore
     * upper context.
     */
    _dsync();

}

void Os_ArchInit( void ) {
    // nothing to do here, yet :)
}

#if 0
CoreIDType GetCoreID(void)
{
    return 0; // Multicore not supported, just return master core id
}
#endif
