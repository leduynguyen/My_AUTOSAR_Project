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
 *         File:  CGT.GHS.h                                                                                             
 *
 *  Description:  GHS compiler specific info used by the F021 API.
 *                Note:  This has not been tested with the GHS compiler.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  John R Hall
 *---------------------------------------------------------------------------------------------------------------------
 *
 *********************************************************************************************************************/

 
#ifndef CGT_GHS_H_
#define CGT_GHS_H_

#if defined(__BIG_ENDIAN__)      /* is big endian compile */
#if !defined(_BIG_ENDIAN)
    #define _BIG_ENDIAN          /* FAPI generic define for big endian */
#endif
#elif defined(__LITTLE_ENDIAN__) /* is little endian compile */
#if !defined(_LITTLE_ENDIAN)
    #define _LITTLE_ENDIAN       /* FAPI generic define for little endian */
#endif
#endif

/* Defines the method to indicate packed enums */
#define ATTRIBUTE_PACKED    __attribute__((packed))

#endif /* CGT_GHS_H_ */

/**********************************************************************************************************************
 *  END OF FILE: CGT.GHS.h
 *********************************************************************************************************************/
