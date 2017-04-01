/**
 * \file IfxCpu_Irq.c
 * \brief This file contains the APIs for Interrupt related functions.
 *
 *
 * \version iLLD_0_1_0_6
 * \copyright Copyright (c) 2012 Infineon Technologies AG. All rights reserved.
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
 *
 */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Cpu/Irq/IfxCpu_Irq.h"
#include "Tricore/Compilers/Compilers.h"
#include "Cpu/Std/IfxCpu_Intrinsics.h"
#include "IfxCpu_reg.h"

/*******************************************************************************
**                      Private macros                                        **
*******************************************************************************/

/*******************************************************************************
**                       Global variables/constants                           **
*******************************************************************************/
#if defined(IFX_USE_SW_MANAGED_INT)

typedef void (*Ifx_Isr)(void);

static Ifx_Isr IfxCpu_Irq_swIntVector[256];

#endif /*defined(IFX_USE_SW_MANAGED_INT) */

/*******************************************************************************
**                      Global Function definitions                          **
*******************************************************************************/
#if defined(IFX_USE_SW_MANAGED_INT)

/** \brief Macro to abstract compilers for the pre interrupt service routine instructions.
 *
 */
IFX_INLINE void IfxCpu_Irq_preIsrCall(void)
{
#if defined(__DCC__)
/*__svlcx(); is introduced by Windriver automatically*/

#elif defined(__GNUC__)
    __svlcx();

#elif defined(__TASKING__)
    __svlcx();

#else
#error Compiler unsupported
#endif
}


/** \brief Macro to abstract compilers for the post interrupt service routine instructions.
 *
 */
IFX_INLINE void IfxCpu_Irq_postIsrCall(void)
{
#if defined(__DCC__)
    /*__rslcx();; is introduced by DCC automatically*/

#elif defined(__GNUC__)
    /*__rslcx();; is introduced by GCC automatically*/

#elif defined(__TASKING__)
    __rslcx();

#else
#error Compiler unsupported
#endif
}


/** \brief API to install the interrupt service routine for Software Managed Interrupts.
 *
 */
void IfxCpu_Irq_installInterruptHandler(void *isrFuncPointer, uint32 serviceReqPrioNumber)
{
    IfxCpu_Irq_swIntVector[serviceReqPrioNumber] = (Ifx_Isr)isrFuncPointer;
}

void __Ifx_int_handler (void);

 void __Ifx_int_handler (void)
{
  /* Just ignore this interrupt.  */
  __debug( );

}

void IfxCpu_Irq_initHandler (void)
{
  uint32 vecno;

  /* Initialize the interrupt handlers.  */
  for (vecno = 0U; vecno < 256; ++vecno)
  {
    IfxCpu_Irq_swIntVector[vecno] =  (void *)/*(Ifx_Isr)*/__Ifx_int_handler;
  }
  /* IfxCpu_Irq_TableInitialized = 1U; */
}
/* Install INTHANDLER for interrupt INTNO and remember ARG for later use.  */


/** SW managed Interrupt vector table
 *
 * This is vector table with single entry for Software Managed Interrupts.
 * This function need to be located at boundary 0xXFE0 where (X=1,3,5 and so on). For the software managed
 * interrupts to work correctly, the BIV must be set to address of this function.
 *
 */
#if defined(__DCC__)
#define IFXCPU_IRQ_INT_ATTRIBUTE __interrupt__ void
#pragma section CODE ".intvec_tc0_255" far-absolute X

#elif defined(__GNUC__)
#define IFXCPU_IRQ_INT_ATTRIBUTE void   /*Nothing else required to define this attribute */
void __attribute__ ((interrupt_handler)) IfxCpu_Irq_intVecTable();
#pragma section ".intvec_tc0_255" x

#elif defined(__TASKING__)
#define IFXCPU_IRQ_INT_ATTRIBUTE void __interrupt(255) __vector_table(0)
#else
#error Compiler unsupported
#endif

IFXCPU_IRQ_INT_ATTRIBUTE IfxCpu_Irq_intVecTable(void)
{
    Ifx_CPU_ICR icr;

    IfxCpu_Irq_preIsrCall();    /*call svlcx if required explicitly, for compiler used */

    icr.U = __mfcr(CPU_ICR);    /*Fetch the ICR value */

    /*Call the ISR */
    IfxCpu_Irq_swIntVector[icr.B.CCPN]();

    IfxCpu_Irq_postIsrCall();   /*call rslcx if required explicitly, for compiler used */
}


/*reset the pragma sections */
#if defined(__DCC__)
#pragma section CODE X
#elif defined(__GNUC__)
#pragma section
#elif defined(__TASKING__)
/*No user section defined */
#else
#error Compiler unsupported
#endif /*defined(__TASKING__) */

#endif /*defined(IFX_USE_SW_MANAGED_INT) */
