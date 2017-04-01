/**
 * \file IfxCpu_CStart_Cfg.h
 * \brief Driver configuration.
 *
 * \license
 * You can use this file under the terms of the IFX License.
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the IFX License for more details (IFX_License.txt).
 *
 * This file may be used, copied, and distributed, with or without modification, provided
 * that all copyright notices are retained; that all modifications to this file are
 * prominently noted in the modified file; and that this paragraph is not modified.
 *
 * \copyright Copyright (C) 2013 Infineon Technologies AG
 * \author Puneetha Mukherjee <puneetha.mukherjee@infineon.com>
 *
 * $Revision: 001 $
 * $Date: 24-05-2013 12:09 +0530 $
 *
 * \defgroup Ifx Infineon Software
 * \defgroup Ifx_Lld Infineon Low Level Drivers' Software
 * \ingroup I
 */ 
/******************************************************************************/
#ifndef IFXCPU_CSTART_CFG_H
#define IFXCPU_CSTART_CFG_H

/******************************************************************************/
/*                           Includes                                         */
/******************************************************************************/
#ifndef IFX_CFG_USE_COMPILER_DEFAULT_LINKER


/******************************************************************************/
/*                           Macros                                           */
/******************************************************************************/

/** \brief Configuration for pre initialization hook function.
 *
 */


/* Comment the below lines if the feature is not needed */
/* ED Device supported needed */
/*#define IFXSTART_ED_DEVICE_SUPPORTED */
#define IFXSTART_MAIN_RAMTEST_SUPPORTED

/* Start driver supports upto 4 segments for Initial RAM tests */
/* CPU0 Initial RAM test segments */
#define IFXCSTART0_INIT_RAMTEST_SEG_0
/*#define IFXCSTART0_INIT_RAMTEST_SEG_1*/
/*#define IFXCSTART0_INIT_RAMTEST_SEG_2 */
/*#define IFXCSTART0_INIT_RAMTEST_SEG_3 */

/* Set the number where stack area is mapped to: eg. CPUx_DSPR */
#define IFXCSTART0_INIT_RAMTEST_SEG_0_MSEL      (IFXSTART_CPU0_DSPR)
#define IFXCSTART0_INIT_RAMTEST_SEG_0_START		  (0x30U)
#define IFXCSTART0_INIT_RAMTEST_SEG_0_END		    (0x3CU)
#define IFXCSTART0_INIT_RAMTEST_SEG_0_TYPE      (IFXSTART_MTU_NON_DES_TEST)
#define IFXCSTART0_INIT_RAMTEST_SEG_0_PATTERN   (0U)
#define IFXCSTART0_INIT_RAMTEST_SEG_0_CLR       (0U)

/* Set the number where stack area is mapped to: eg. CPUx_DSPR */
#define IFXCSTART0_INIT_RAMTEST_SEG_1_MSEL      (IFXSTART_CPU0_PSPR)
#define IFXCSTART0_INIT_RAMTEST_SEG_1_START		  (0xffU)
#define IFXCSTART0_INIT_RAMTEST_SEG_1_END		    (0xffU)
#define IFXCSTART0_INIT_RAMTEST_SEG_1_TYPE      (IFXSTART_MTU_NON_DES_TEST)
#define IFXCSTART0_INIT_RAMTEST_SEG_1_PATTERN   (0U)
#define IFXCSTART0_INIT_RAMTEST_SEG_1_CLR       (0U)      

/* Set the number where stack area is mapped to: eg. CPUx_DSPR */
#define IFXCSTART0_INIT_RAMTEST_SEG_2_MSEL      (IFXSTART_CPU0_PSPR)
#define IFXCSTART0_INIT_RAMTEST_SEG_2_START		  (0xffU)
#define IFXCSTART0_INIT_RAMTEST_SEG_2_END		    (0xffU)
#define IFXCSTART0_INIT_RAMTEST_SEG_2_TYPE      (IFXSTART_MTU_NON_DES_TEST)
#define IFXCSTART0_INIT_RAMTEST_SEG_2_PATTERN   (0U)
#define IFXCSTART0_INIT_RAMTEST_SEG_2_CLR       (0U)

/* Set the number where stack area is mapped to: eg. CPUx_DSPR */
#define IFXCSTART0_INIT_RAMTEST_SEG_3_MSEL       (IFXSTART_CPU0_PSPR)
#define IFXCSTART0_INIT_RAMTEST_SEG_3_START		   (0xffU)
#define IFXCSTART0_INIT_RAMTEST_SEG_3_END		     (0xffU)
#define IFXCSTART0_INIT_RAMTEST_SEG_3_TYPE       (IFXSTART_MTU_NON_DES_TEST)
#define IFXCSTART0_INIT_RAMTEST_SEG_3_PATTERN    (0U)
#define IFXCSTART0_INIT_RAMTEST_SEG_3_CLR        (0U)      
/* CPU0 Initial RAM test segments */    
    
/* CPU1 Initial RAM tests */
#define IFXCSTART1_INIT_RAMTEST_SEG_0 
/* #define IFXCSTART1_INIT_RAMTEST_SEG_1 */
/* #define IFXCSTART1_INIT_RAMTEST_SEG_2 */
/* #define IFXCSTART1_INIT_RAMTEST_SEG_3 */

/* Set the number where stack area is mapped to: eg. CPUx_DSPR */
#define IFXCSTART1_INIT_RAMTEST_SEG_0_MSEL       (IFXSTART_CPU1_PSPR)
#define IFXCSTART1_INIT_RAMTEST_SEG_0_START		   (0x34U)  
#define IFXCSTART1_INIT_RAMTEST_SEG_0_END		     (0x3CU)  
#define IFXCSTART1_INIT_RAMTEST_SEG_0_TYPE       (IFXSTART_MTU_NON_DES_TEST)
#define IFXCSTART1_INIT_RAMTEST_SEG_0_PATTERN    (0U)
#define IFXCSTART1_INIT_RAMTEST_SEG_0_CLR        (0U)      

#define IFXCSTART1_INIT_RAMTEST_SEG_1_MSEL       (IFXSTART_CPU1_PSPR)
#define IFXCSTART1_INIT_RAMTEST_SEG_1_START		   (0xffU)
#define IFXCSTART1_INIT_RAMTEST_SEG_1_END		     (0xffU)
#define IFXCSTART1_INIT_RAMTEST_SEG_1_TYPE       (IFXSTART_MTU_NON_DES_TEST)
#define IFXCSTART1_INIT_RAMTEST_SEG_1_PATTERN    (0U)
#define IFXCSTART1_INIT_RAMTEST_SEG_1_CLR        (0U)      

/* Set the number where stack area is mapped to: eg. CPUx_DSPR */
#define IFXCSTART1_INIT_RAMTEST_SEG_2_MSEL       (IFXSTART_CPU1_PSPR)
#define IFXCSTART1_INIT_RAMTEST_SEG_2_START		   (0xffU) 
#define IFXCSTART1_INIT_RAMTEST_SEG_2_END		     (0xffU) 
#define IFXCSTART1_INIT_RAMTEST_SEG_2_TYPE       (IFXSTART_MTU_NON_DES_TEST)
#define IFXCSTART1_INIT_RAMTEST_SEG_2_PATTERN    (0U)
#define IFXCSTART1_INIT_RAMTEST_SEG_2_CLR        (0U)      

/* Set the number where stack area is mapped to: eg. CPUx_DSPR */
#define IFXCSTART1_INIT_RAMTEST_SEG_3_MSEL       (IFXSTART_CPU1_PSPR)
#define IFXCSTART1_INIT_RAMTEST_SEG_3_START		   (0xffU)
#define IFXCSTART1_INIT_RAMTEST_SEG_3_END		     (0xffU)
#define IFXCSTART1_INIT_RAMTEST_SEG_3_TYPE       (IFXSTART_MTU_NON_DES_TEST)
#define IFXCSTART1_INIT_RAMTEST_SEG_3_PATTERN    (0U)
#define IFXCSTART1_INIT_RAMTEST_SEG_3_CLR        (0U)          
/* CPU1 Initial RAM Tests */
    
/* CPU2 Initial RAM tests */
#define IFXCSTART2_INIT_RAMTEST_SEG_0 
/* #define IFXCSTART2_INIT_RAMTEST_SEG_1 */
/* #define IFXCSTART2_INIT_RAMTEST_SEG_2 */
/* #define IFXCSTART2_INIT_RAMTEST_SEG_3 */

/* Set the number where stack area is mapped to: eg. CPUx_DSPR */
#define IFXCSTART2_INIT_RAMTEST_SEG_0_MSEL       (IFXSTART_CPU2_PSPR)
/* Start up RAM test configurations */
#define IFXCSTART2_INIT_RAMTEST_SEG_0_START		   (0x34U)    
#define IFXCSTART2_INIT_RAMTEST_SEG_0_END		     (0x3CU)    
#define IFXCSTART2_INIT_RAMTEST_SEG_0_TYPE       (IFXSTART_MTU_NON_DES_TEST)
#define IFXCSTART2_INIT_RAMTEST_SEG_0_PATTERN    (0U)
#define IFXCSTART2_INIT_RAMTEST_SEG_0_CLR        (0U)

/* Set the number where stack area is mapped to: eg. CPUx_DSPR */
#define IFXCSTART2_INIT_RAMTEST_SEG_1_MSEL       (IFXSTART_CPU2_PSPR)
#define IFXCSTART2_INIT_RAMTEST_SEG_1_START		   (0xffU) 
#define IFXCSTART2_INIT_RAMTEST_SEG_1_END		     (0xffU) 
#define IFXCSTART2_INIT_RAMTEST_SEG_1_TYPE      (IFXSTART_MTU_NON_DES_TEST)
#define IFXCSTART2_INIT_RAMTEST_SEG_1_PATTERN    (0U)
#define IFXCSTART2_INIT_RAMTEST_SEG_1_CLR        (0U)     

/* Set the number where stack area is mapped to: eg. CPUx_DSPR */
#define IFXCSTART2_INIT_RAMTEST_SEG_2_MSEL       (IFXSTART_CPU2_PSPR)
#define IFXCSTART2_INIT_RAMTEST_SEG_2_START		   (0xffU) 
#define IFXCSTART2_INIT_RAMTEST_SEG_2_END		     (0xffU) 
#define IFXCSTART2_INIT_RAMTEST_SEG_2_TYPE       (IFXSTART_MTU_NON_DES_TEST)
#define IFXCSTART2_INIT_RAMTEST_SEG_2_PATTERN    (0U)
#define IFXCSTART2_INIT_RAMTEST_SEG_2_CLR        (0U)      

/* Set the number where stack area is mapped to: eg. CPUx_DSPR */
#define IFXCSTART2_INIT_RAMTEST_SEG_3_MSEL       (IFXSTART_CPU2_PSPR)
#define IFXCSTART2_INIT_RAMTEST_SEG_3_START		   (0xffU) 
#define IFXCSTART2_INIT_RAMTEST_SEG_3_END		     (0xffU) 
#define IFXCSTART2_INIT_RAMTEST_SEG_3_TYPE       (IFXSTART_MTU_NON_DES_TEST)
#define IFXCSTART2_INIT_RAMTEST_SEG_3_PATTERN    (0U)
#define IFXCSTART2_INIT_RAMTEST_SEG_3_CLR        (0U)     
/* CPU2 Initial RAM tests */                                          
#endif 
  /*#ifndef IFX_CFG_USE_COMPILER_DEFAULT_LINKER */
#endif 
  /* IFXCPU_CSTART_CFG_H */
  
