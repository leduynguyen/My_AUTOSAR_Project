/**
 * \file Compilers.h
 *
 * \version iLLD_0_1_0_6
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
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
 */

#ifndef COMPILERS_H
#define COMPILERS_H 1

/******************************************************************************/

#include "Ifx_Cfg.h"

/*this file shall not be modified by the user, CONST_CFG shall be defined in Ifx_Cfg.h */
#ifndef CONST_CFG
#define CONST_CFG       const           /* configuration constants are stored in ROM */
#endif

#ifdef __cplusplus
#define IFX_EXTERN      extern "C"
#else
#define IFX_EXTERN      extern
#endif

#ifndef NULL_PTR
#ifdef __cplusplus
#define NULL_PTR        (0)
#else /*#ifdef __cplusplus */
#define NULL_PTR        ((void *)0)
#endif /*#ifdef __cplusplus */
#endif /*#ifndef NULL_PTR */

#ifndef CFG_LONG_SIZE_T
#define CFG_LONG_SIZE_T (0)
#endif

#if defined(__DCC__)
#include "CompilerDcc.h"

#elif defined(__GNUC__)
#include "CompilerGnuc.h"

#elif defined(__TASKING__)
#include "CompilerTasking.h"

#elif defined(__MSVC__)
#include "CompilerMsvc.h"

#else

/** \addtogroup IfxLld_Cpu_Std_Interrupt
 * \{  */
/** \brief Macro to define Interrupt Service Routine.
 * This macro makes following definitions:\n
 * 1) Define linker section as .intvec_tc<vector number>_<interrupt priority>.\n
 * 2) define compiler specific attribute for the interrupt functions.\n
 * 3) define the Interrupt service routine as Isr function.\n
 * To get details about usage of this macro, refer \ref IfxLld_Cpu_Irq_Usage
 *
 * \param isr Name of the Isr function.
 * \param vectabNum Vector table number. Only 0 is supported now.
 * \param prio Interrupt priority. Refer Usage of Interrupt Macro for more details.
 */
#define IFX_INTERRUPT(isr, vectabNum, prio)

/** \}  */
#error "Compiler unsupported"
#endif

/* Functions prototypes                                                       */
/******************************************************************************/
void Ifx_C_Init(void);
/******************************************************************************/
#endif /* COMPILERS_H */
