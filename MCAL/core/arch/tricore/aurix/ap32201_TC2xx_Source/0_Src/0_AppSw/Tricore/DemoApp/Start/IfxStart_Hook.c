/*
 * IfxStart_Hook.c
 *
 *  Created on: 23-Sep-2014
 *      Author: MukherjP
 */

#include "Ifx_Types.h"
#include "IfxStart.h"
#include "IfxStart_Cfg.h"

#if defined IFXSTART_ERROR_EXCEPTION_SUPPORTED
extern void IFXSTART_ERROR_EXCEPTION(uint32 ErrorCode, uint32 ADDR_error);
#endif
   /* IFXSTART_ERROR_EXCEPTION_SUPPORTED */
#if defined IFXSTART_DEUG_EXCEPTION_SUPPORTED
extern void IFXSTART_DEBUG_EXCEPTION(uint32 ErrorCode, uint32 ADDR_error);
#endif
  /* IFXSTART_DEUG_EXCEPTION_SUPPORTED */


#if defined IFXSTART_SYSINIT_EXCEPTION_SUPPORTED
extern void IFXSTART_SYSINIT_EXCEPTION(void);
#endif
   /* IFXSTART_SYSINIT_EXCEPTION_SUPPORTED */

#if defined IFXSTART_DEBUG_EXCEPTION
extern void IFXSTART_OS_START_EXCEPTION(void);
#endif
   /*   #if defined IFXSTART_DEBUG_EXCEPTION  */

/** \brief  Place holders for Driver Init call back
 * \param None
 * \return  None
 *
 */
void IfxStart_DriverInitEx(void)
{
  ;
}



/** \brief  This event runs after the RAM test was executed,
 * so the RAM memory is certified to be in good operative state
 * and global variables can be freely used. All the application
 * initialization code and set-up operations (exept those
 * already carried on at the PowerOnReset event) can be done
 * during this event execution.
 * \param None
 * \return  None
 *
 */
void IfxStart_SysInitEx(void)
{
  IFXSTART_SYSINIT_EXCEPTION();
}

/** \brief  Place holders for CPU Start
 * \param cpu Number
 * \return  None
 *
 */
void IfxStart_CpuEx(void)
{
    Test_DD_Ex_BgTask( );
}


/** \brief This event gives the application the first opportunity
 *  to execute routines shortly after the CPU started its initialization
 *  (by executing code from the BIOS entry point). All the code that must
 *  run shortly after the reset must be placed inside the event function.
 *  This event is triggered just before the RAM test, so the event function
 *  cannot use global variables as they will be erased by the RAM test
 *  afterwards
 * \param None
 * \return  None
 *
 */
void IfxStart_SafetyTestEx(void)
{
  /*IFXSTART_PORST_EXCEPTION();*/
}
/** \brief This method is called by the driver at the occurence of an
 *   internal error. It schedules the exception BIOS_START_Ex_Error passing
 *   its two input parameters, in order to treat the event.
 *   At the end of the execution of the error exception, the CPU must be reset.
 * \param  t_ErrorCode <ErrorCode> :Codes of the errors risen by the START driver.
          It can be CLASS_B_ERROR / RAM_TEST_ERROR
 * \param  ADDR_error : Address of the memory position where the error occured.
 * \return  None
 */
void START_SetEX_ErrorEvent(uint32 ErrorCode, uint32 ADDR_error)
{
  uint32      Data_Val;
  uint32      userInfo;
  uint8       ResetType;
  IfxStart_ErrorType ErrorCodeMask;


  /* Extract the Error Type */
  userInfo = (uint32)IfxStart_NORMAL_RESET;
  ResetType = IFXSCURCU_SYSTEM_RESET;
  ErrorCodeMask = (IfxStart_ErrorType) ((ErrorCode & 0x0f000000U) >> 24U);

  switch (ErrorCodeMask)
  {
    case IfxStart_ErrorType_tinError:
    {
        /*Default_START_ErrorException(1U, ADDR_error)*/;

      /* get the TIN Type and set the user information */
      Data_Val = ((ErrorCode & 0x00FF0000U) >> 16U);

      switch (Data_Val)
      {
        case IfxStart_ClassbError_Type_Mmu:
        {
          ;
        }
        break;

        case IfxStart_ClassbError_Type_Protection:
        {
          ;
        }
        break;

        case IfxStart_ClassbError_Type_Intsruction:
        {
          /* Get the TIN sub type */
          Data_Val = ((ErrorCode & 0x0000ff00U) >> 8U);

          /* if IfxStart_ILL_INA */
          if (1 == Data_Val)
          {
            userInfo = (uint32)IfxStart_ILL_INA;
          }
          /* If Unimplemented Opcode */
          else if (2 == Data_Val)
          {
            userInfo = (uint32)IfxStart_ILL_OPA;
          }
          /* If Invalid Operand */
          else if (3 == Data_Val)
          {
            userInfo = (uint32)IfxStart_UND_OPC;
          }
        }
        break;

        case IfxStart_ClassbError_Type_Context:
        {
          ;
        }
        break;

        case IfxStart_ClassbError_Type_Bus:
        {
          userInfo = (uint32)IfxStart_ILL_BUS;
        }
        break;

        case IfxStart_ClassbError_Type_Assertion:
        {
          ;
        }
        break;

        case IfxStart_ClassbError_Type_SysCall:
        {
          ;
        }
        break;

        case IfxStart_ClassbError_Type_Nmi:
        {
          userInfo = (uint32)IfxStart_NMI_INT;
        }
        break;

        default:
        break;
      }
    }
    break;

    case IfxStart_ErrorType_appError:
    {
        /*Default_START_ErrorException(2U, ADDR_error)*/;
    }
    break;

    default:
      break;
  }      /* End of switch statement */

  /* Call Perform_Reset with NORMAL_RES */
  IfxScuCcu_PerformReset(ResetType, userInfo);
}

/** \brief This event must be triggered by all hardware critical
 *  exceptions (bus error, address error, for example) and by
 * every empty vector table interrupt location, allowing the application
 * to take decisions after a severe system fault is detected
 * \param  Vector table entry of the interrupt that generated the exception
 * \param  ADDR_error:Address of the memory position where the error happened.
 * \return  None
 */
void START_SetEX_DebugEvent(uint32 ErrorCode, uint32 ADDR_error)
{
  uint32      Data_Val;
  IfxStart_ErrorType ErrorCodeMask;
  uint32      userInfo;

  /* Extract the Error Type */
  ErrorCodeMask = (IfxStart_ErrorType) ((ErrorCode & 0x0f000000U) >> 24U);

  switch (ErrorCodeMask)
  {
    case IfxStart_ErrorType_addrError:
    {
      /* Extract the Address information */
      Data_Val = ((ErrorCode & 0x0000FF00U) >> 8U);
      /* Call Perform_Reset with NORMAL_RES */
      userInfo = (uint32)IfxStart_NORMAL_RESET;
      IfxScuCcu_PerformReset(IFXSCURCU_SYSTEM_RESET, (uint32)userInfo);
    }
    break;

    default:
      break;
  }
}
