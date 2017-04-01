/**
 * \file Ifx_TrapHook.c
 * \brief This file contains hook function for the Trap Handling. 
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
#include "Ifx_Types.h"
#include "IfxCpu_Trap.h"
#include "IfxStart.h"

void myTrapExtensionHook(IfxCpu_Trap trapInfo)
{         
  uint32 ErrorCode ;
  uint32 ErrorInfo ;	

  /* s(CPU � 1st nibble ) t(basic type) uv wx yz h,
     ST = 0(CPU) 0 (TIN)
     UV = 0,1�7 � TIN type
     WX = 0,1,�7 - TIN sub type
     YZ = reserved for future
  */
  ErrorCode = 0U;
  ErrorCode |= (((trapInfo.tCpu) << 28U ) | ( ((uint32)IfxStart_ErrorType_tinError) << 24U) );
  ErrorCode |= (uint32) ((trapInfo.tId << 8U));
  ErrorInfo   = 0U; 
  
  switch (trapInfo.tClass)
  {
    case IfxCpu_Trap_Class_memoryManagement:
    {
      ErrorCode |= ( (uint32)IfxStart_ClassbError_Type_Mmu << 16U);
      break;
    }
    case IfxCpu_Trap_Class_internalProtection:
    {
      ErrorCode |= ((uint32)IfxStart_ClassbError_Type_Protection << 16U);  
      break;
    }
    case IfxCpu_Trap_Class_instructionErrors:
    {
      ErrorCode |= ((uint32)IfxStart_ClassbError_Type_Intsruction << 16U);
      break;
    }
    case IfxCpu_Trap_Class_contextManagement:
    {
      ErrorCode |= ((uint32)IfxStart_ClassbError_Type_Context << 16U);
      break;
    }
    case IfxCpu_Trap_Class_bus:
    {
      ErrorCode |= ((uint32)IfxStart_ClassbError_Type_Bus << 16U);
      break;
    }
    case IfxCpu_Trap_Class_assertion:
    {
      ErrorCode |= ((uint32)IfxStart_ClassbError_Type_Assertion << 16U);
      break;
    }
    case IfxCpu_Trap_Class_nonMaskableInterrupt:
    {
      ErrorCode |= ((uint32)IfxStart_ClassbError_Type_Nmi << 16U);
      break;
    }
    
    case IfxCpu_Trap_Class_systemCall:
    {
        ErrorCode |= ((uint32)IfxStart_ClassbError_Type_SysCall << 16U);
        break;
    }		
    default:
    {
      break;
    }    
  }
  IfxStart_ErrorEx(ErrorCode , ErrorInfo );
}
