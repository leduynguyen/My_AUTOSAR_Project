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
 *         File:  CGT.CCS.h                                                                                             
 *
 *  Description:  TI CCS compiler specific info used by the F021 API.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  John R Hall
 *---------------------------------------------------------------------------------------------------------------------
 *
 *********************************************************************************************************************/

 
#ifndef CGT_CCS_H_
#define CGT_CCS_H_

#if defined(__big_endian__)         /* is big endian compile */
#if !defined(_BIG_ENDIAN)
    #define _BIG_ENDIAN           /* FAPI generic define for big endian */
#endif
#elif  defined(__little_endian__)   /* is little endian compile */
#if !defined(_LITTLE_ENDIAN)
    #define _LITTLE_ENDIAN        /* FAPI generic define for little endian */
#endif
#endif

/* Defines the method to indicate packed enums */
#if defined(__TI_GNU_ATTRIBUTE_SUPPORT__) && (__TI_GNU_ATTRIBUTE_SUPPORT__==1)
/* --gcc option enabled so we can specify this */
#define ATTRIBUTE_PACKED    __attribute__((packed))
#else
/* --gcc option not enabled so we cannot specify this */
#define ATTRIBUTE_PACKED
#endif


#endif /* CGT_CCS_H_ */

/**********************************************************************************************************************
 *  END OF FILE: CGT.CCS.h
 *********************************************************************************************************************/
