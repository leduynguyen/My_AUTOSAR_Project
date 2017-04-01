/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 © Copyright 2009-2012 Texas Instruments Incorporated.  All rights reserved.
 *
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *      Project:  Hercules™ ARM® Safety MCUs - F021 Flash API 
 *      Version:  v2.01.01 Build(000830)                                                                                
 *   Build Date:  2014-10-21                                                                                            
 *
 *         File:  Compatibility.h                                                                                       
 *
 *  Description:  A set of macro defines to provide backwards compatibility to v1.x API.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  John R Hall
 *---------------------------------------------------------------------------------------------------------------------
 *
 *********************************************************************************************************************/


#ifndef COMPATIBILITY_H_
#define COMPATIBILITY_H_

/*LDRA_NOANALYSIS*/
/* This header file is intended for backwards compatibility only and is not meant to be MISRA-C compliant */

/* Define to provide backwards compatibility with Fapi_initializeFlashApi() */
#define Fapi_initializeAPI(mControlRegister,mFrequency) (Fapi_initializeFlashBanks((mFrequency)))

/* Define to provide backwards compatibility with Fapi_getFsmStatus() */
#define Fapi_getFsmStatus() (FAPI_GET_FSM_STATUS)

/* Define to provide backwards compatibility with Fapi_issueFsmSuspendCommand() */
#define Fapi_issueFsmSuspendCommand()  (FAPI_SUSPEND_FSM)

/* Define to provide backwards compatibility with Fapi_writeEwaitValue() */
#define Fapi_writeEwaitValue(mEwait)  (FAPI_WRITE_EWAIT((mEwait)))

/* Define to provide backwards compatibility with Fapi_checkFsmForReady() */
#define Fapi_checkFsmForReady()  (FAPI_CHECK_FSM_READY_BUSY)


#endif
/*LDRA_ANALYSIS*/

/**********************************************************************************************************************
 *  END OF FILE: Compatibility.h
 *********************************************************************************************************************/
