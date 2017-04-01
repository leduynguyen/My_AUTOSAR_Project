/**
 * \file IfxStart.c
 * \brief This file contains start driver functions. 
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
 * $Revision: 004 $
 * $Date: 24-05-2013 12:09 +0530 $
 *
 * \defgroup Ifx Infineon Software
 * \defgroup Ifx_Lld Infineon Low Level Drivers' Software
 * \ingroup I
 */ 
/******************************************************************************/
#include "Ifx_Types.h"
#include "IfxStart.h"
#include "IfxMtu.h"

/*lint -save -e562 */
/*lint -save -e19 */
/*lint -save -e102 */
#ifdef __GNUC__
extern uint8 IfxStart_Ram_Tst /*__attribute__ ((section(".sbss2")))*/;
  /* look up table for the Memory test */
extern uint8 IfxStart_Mtu_Table_Dspr[IFXMTU_DSPR_RANGE]
  /*__attribute__ ((section(".sbss2")))*/;
extern uint8 IfxStart_Mtu_Table_Pspr[IFXMTU_PSPR_RANGE]
  /*__attribute__ ((section(".sbss2")))*/;
extern IfxStart_RamTestCfgType IfxStart_kRamTstConfiguration[IFXSTART_NUM_RAM_SECTIONS]
  /*__attribute__ ((section(".sbss2")))*/;
extern IfxStart_Pin_Config IfxStart_PortConfig[]
  /*__attribute__ ((section(".sbss2")))*/;
#elif __TASKING__
extern uint8 IfxStart_Ram_Tst;
  /* look up table for the Memory test */
extern uint8 IfxStart_Mtu_Table_Dspr[IFXMTU_DSPR_RANGE];
extern uint8 IfxStart_Mtu_Table_Pspr[IFXMTU_PSPR_RANGE];
extern IfxStart_RamTestCfgType IfxStart_kRamTstConfiguration[IFXSTART_NUM_RAM_SECTIONS];
extern IfxStart_Pin_Config IfxStart_PortConfig[];
#endif


#if defined IFXSTART_ERROR_EXCEPTION_SUPPORTED
extern void IFXSTART_ERROR_EXCEPTION(uint32 ErrorCode, uint32 ADDR_error);
#endif
   /* IFXSTART_ERROR_EXCEPTION_SUPPORTED */
#if defined IFXSTART_DEUG_EXCEPTION_SUPPORTED
extern void IFXSTART_DEBUG_EXCEPTION(uint32 ErrorCode, uint32 ADDR_error);
#endif
  /* IFXSTART_DEUG_EXCEPTION_SUPPORTED */
extern void _Core1_start(void);
extern void _Core2_start(void);

/******************************************************************************/
/*                           Function prototypes                              */

/******************************************************************************/


/******************************************************************************/
/*                           Functions                                        */

/*****************************************************************************/

/** \brief Sets the necessary drivers to default
 *
 * \param None
 *
 * \return None.
 */
void IfxStart_Defaults(void)
{
  #if defined IFXSTART_ED_DEVICE_SUPPORTED
    uint32      Result;
  #endif
  uint32      index;
  
  /* Call Port_init function */
  IfxStartPort_init(&IfxStart_PortConfig[0], MAX_CFG_PIN);
  
  #if defined IFXSTART_ED_DEVICE_SUPPORTED
    Result = IfxEd_EmemInit();
    if (Result)
    {
      __debug();
    }
  #endif
     /* #if defined IFXSTART_ED_DEVICE_SUPPORTED */

    Ifx_lenableMtu ();
  for (index = 0U; index < IFXSTART_NUM_RAM_SECTIONS; index++)
  {
    IfxStart_RangeFromAddress
      (&IfxStart_kRamTstConfiguration[index].SegStart_Address,
       &IfxStart_kRamTstConfiguration[index].SegEnd_Address,
       &IfxStart_kRamTstConfiguration[index].SegStart,
       &IfxStart_kRamTstConfiguration[index].SegEnd,
       IfxStart_kRamTstConfiguration[index].MbistNumber);
  }
}

void IfxStart_RangeFromAddress 
                 (
                   uint32 * SegStart_Address,uint32 * SegEnd_Address,
                   uint8 * SegStart, uint8 * SegEnd, uint8 MbistNumber
                 )
{
  uint32      index_buffer;

  /* Check if it is PSPR or DSPR */
  if ((MbistNumber == IFXSTART_CPU2_DSPR) || (MbistNumber == IFXSTART_CPU1_DSPR)
      || (MbistNumber == IFXSTART_CPU0_DSPR))
  {
      index_buffer =
        ((*SegStart_Address & IFXMTU_ADDRESS_EXTRACT_MASK) >>
                IFXMTU_DSPR_ADDRESS_EXTRACT_BIT);

    *SegStart = IfxStart_Mtu_Table_Dspr[index_buffer];
    #if !defined IFXMTU_ADDRESS_DSPR_1K
      *SegEnd =  *SegStart + 3U ;
    #else
      *SegEnd =  *SegStart + 1U ;
    #endif
  }
  else
  {
      index_buffer =
        ((*SegStart_Address & IFXMTU_ADDRESS_EXTRACT_MASK) >>
                IFXMTU_PSPR_ADDRESS_EXTRACT_BIT);

      /* 2K resolution on PSPR */
      index_buffer = index_buffer >> 1U ;
    *SegStart = IfxStart_Mtu_Table_Pspr[index_buffer];

    #if !defined IFXMTU_ADDRESS_PSPR_1K
      *SegEnd =  *SegStart + 7U ;
    #else
      *SegEnd =  *SegStart + 3U ;
    #endif
  }
}

/** \brief Initializes the drivers
 *
 * \param None
 *
 * \return None.
 */
void IfxStart_DriverInit(void)
{
  #if ((IFXSTART_EXTCLK0 == STD_ON) || (IFXSTART_EXTCLK1 == STD_ON) )
    IfxStart_Pin_Config port_config_data;
  #endif
    /* #if ((IFXSTART_EXTCLK0 == STD_ON) || (IFXSTART_EXTCLK1 == STD_ON) ) */
  
  /* Clock Initialization */
  /* puneetha check this as it is already done in the cstart */
  /* IfxScu_CCu_InitClock(); */
  
  /* Clear the Cold PORST Status */
  IfxScuRcu_ClrCPorstStatus();
  

/*
  #if (IFXSTART_MON_TRIGGER == STD_ON)
    IfxScuCcu_ClockMonitor();
  #endif
*/
    /* #if (IFXSTART_MON_TRIGGER == STD_ON) */
    
  #if (IFXSTART_EXTCLK0 == STD_ON)
    /* Configure the External clock out pins , 23.1(90) or 11.12(167) */
    #if (IFXSTART_EXT_CLK_OUT_0_PIN == IFXSCUCCU_EXTCLK0_PIN_0)  /*90U */
      port_config_data.port = IFXSCUCCU_EXTCLK0_PIN_0_PORT;
      port_config_data.pinIndex = IFXSCUCCU_EXTCLK0_PIN_0_PIN;
      port_config_data.mode = (IfxPort_Mode)(MODE_OUT | MODE_OUT_PUSHPULL | MODE_OUT_ALT6);
    #elif (IFXSTART_EXT_CLK_OUT_0_PIN == IFXSCUCCU_EXTCLK0_PIN_1)
      port_config_data.port = IFXSCUCCU_EXTCLK0_PIN_1_PORT;
      port_config_data.pinIndex = IFXSCUCCU_EXTCLK0_PIN_1_PIN;
      port_config_data.mode = (IfxPort_Mode)(MODE_OUT | MODE_OUT_PUSHPULL | MODE_OUT_ALT6);
    #endif
    /* */
    port_config_data.padDriver = (IfxPort_PadDriver)(PDR_CMOS | PDR_SG1);
    port_config_data.DefaultState = (IfxPort_State)OUT_GPIO_OFF;
    IfxStartPort_init(&port_config_data, 1U);

    IfxScuCcu_enable_ClockOut(IFXSTART_EXTCLK_0_DIV , IFXSTART_EXTCLK0_SEL ,0U);
  #endif
    /* (IFXSTART_EXTCLK0 == STD_ON)  */
  #if (IFXSTART_EXTCLK1 == STD_ON)
    /* Configure the External clock out pins , 32.4(88) or 11.12(167) */
    #if (IFXSTART_EXT_CLK_OUT_1_PIN == IFXSCUCCU_EXTCLK1_PIN_0)
      port_config_data.port = IFXSCUCCU_EXTCLK1_PIN_0_PORT;
      port_config_data.pinIndex = IFXSCUCCU_EXTCLK1_PIN_0_PIN;
      port_config_data.mode = (IfxPort_Mode)(MODE_OUT | MODE_OUT_PUSHPULL | MODE_OUT_ALT6);
    #elif (IFXSTART_EXT_CLK_OUT_1_PIN == IFXSCUCCU_EXTCLK1_PIN_1)
      port_config_data.port = IFXSCUCCU_EXTCLK1_PIN_1_PORT;
      port_config_data.pinIndex = IFXSCUCCU_EXTCLK1_PIN_1_PIN;
      port_config_data.mode = (IfxPort_Mode)(MODE_OUT | MODE_OUT_PUSHPULL | MODE_OUT_ALT6);
    #endif
      /* */
    port_config_data.padDriver = (IfxPort_PadDriver)(PDR_CMOS | PDR_SG1);
    port_config_data.DefaultState = (IfxPort_State)OUT_GPIO_OFF;
    IfxStartPort_init(&port_config_data, 1U);

    IfxScuCcu_enable_ClockOut(IFXSTART_EXTCLK_1_DIV , IFXSTART_EXTCLK1_SEL, 1U);
  #endif
    /* (IFXSTART_EXTCLK0 == STD_ON)  */
 
/*
  #if (IFXSTART_SCU_FM_PLL_USED == STD_ON)
    IfxScuCCu_InitClock_FMPll();
  #endif
*/
    /* #if(IFXSTART_SCU_FM_PLL_USED == STD_ON) */
}


/** \brief Error Exception
 *
 * \param Error Type ErrorCode , 
 *        ErrorAddress / ErrorData
 *
 * \return None
 *
 */
void IfxStart_ErrorEx(uint32 errorCode, uint32 ErrorInfo)
{
  IfxStart_ErrorType ErrorCodeMask;

  /* Extract the Errot Type */
  ErrorCodeMask = (IfxStart_ErrorType) ((errorCode & (0x0f000000)) >> 24U);

  switch (ErrorCodeMask)
  {
    case IfxStart_ErrorType_tinError:
    {
      IFXSTART_ERROR_EXCEPTION(errorCode, ErrorInfo);
    }
      break;

    case IfxStart_ErrorType_addrError:
    {
      IFXSTART_DEBUG_EXCEPTION(errorCode, ErrorInfo);
    }
      break;

    case IfxStart_ErrorType_smuError:
    {
      IFXSTART_ERROR_EXCEPTION(errorCode, ErrorInfo);
    }
      break;

    case IfxStart_ErrorType_appError:
    {
      IFXSTART_ERROR_EXCEPTION(errorCode, ErrorInfo);
    }
      break;

    default:
      break;
  }      /* End of switch statement */
}

/** \brief This method does the Memory Tests as per the configurations
 *
 * \param RamTstConfigPtr : The memory test configurations
 * \param Num_Sections : Number of RAM sections
 * \param The ErrorAddr : The location where Error Address is returned.
 *
 * \return Memory Test Status 0 - OK  , 1 - NOT_OK
 */
uint8 IfxStart_memTest(uint8 Num_Sections, uint16 * ErrorAddr ,
                      IfxStart_RamTestCfgType * RamTstConfigPtr )
{
  uint32      index;  
  uint8       RetVal;  

  RetVal = 0U;
  /* No RAM test failure */
  *ErrorAddr = 0U;

  /* Run the RAM  test for all the memory segments */
  for (index = 0U; index < Num_Sections; index++)
  {
    if (IFXSTART_MTU_NON_DES_TEST == (RamTstConfigPtr + index)->RamTstType)
    {
      #if (IFXMTU_NON_DES_TEST_USED == STD_ON)
        RetVal = IfxMtu_Non_Destructive_test
                 ((RamTstConfigPtr + index)->MbistNumber,
                  IFXSTART_RANGE_ENABLE,
                  (RamTstConfigPtr + index)->SegEnd,
                  (RamTstConfigPtr + index)->SegStart, ErrorAddr
                 );
      #endif
      /* #if  (IFXMTU_NON_DES_TEST_USED == STD_ON) */
    }
    /* If the test has failed, RetVal != 0 */
    if (0U == RetVal)
    {    	
      if ( 1U == (RamTstConfigPtr + index)->ClrSeg)
      {
        /* Clear the memory segment */
        IfxMtu_PerformAutoInit((RamTstConfigPtr + index)->MbistNumber,
                               IFXSTART_RAM_TEST_INIT_DATA,
                               IFXSTART_RANGE_ENABLE,
                               (RamTstConfigPtr + index)->SegEnd,
                               (RamTstConfigPtr + index)->SegStart,
                               IFXSTART_ECC_DATA);
      }
    }    /* Test Successful */
    else
    { 
        /* Test Failure, hence return */
      break;
    }    
  }      /* End of for loop */
  return (RetVal);
}        /* IfxStart_memTest( ) */

/** \brief Sets the flag to indicate if RAM Test has to be run or not. 
 * Sets a global flag, which is placed in the global data area(reserved)
 *
 * \param S_ON: The RAM test must be executed during the system startup
 *       S_OFF: The RAM test is not to be executed
 * \param userInfo User Data for evaluation after reset
 *
 * \return None.
 */
void IfxStart_memTestEnable(uint8 RamTest_Run)
{
  /* Place this vaiable in global aea which is reserved for start driver */
  IfxStart_Ram_Tst = RamTest_Run;
}

/** \brief Reads the status and indicates if RAM test was run or not
 *
 * \param None 
 *
 * \return .S_ON: The RAM test must be executed during the system startup
 *       S_OFF: The RAM test is not to be executed
 */
uint8 IfxStart_getMemTestStatus(void)
{
  return (IfxStart_Ram_Tst);
}

/** \brief Jumps to the location provided 
 *
 *
 * \param where to jump
 *
 * \return None.
 */
void IfxStart_BootLdrToApplJump(uint32 address)
{
  IfxCpu_ResourceCpu             cpu;
  Ifx_CPU            *module;

  cpu    = (IfxCpu_ResourceCpu)IfxCpu_getCoreId();
  module = IfxCpu_getAddress(cpu) ; 
  IfxCpu_setProgramCounter(module, address);
}

/** \brief Main entry from Cstart
 *
 * \param None
 *
 * \return None.
 */
int Start_Main(void)
{
    uint32      RetVal;
    IfxScuRcu_ResetCode RestCode ;
/*	uint16      ErrorAddr;*/

    uint8       RamTest = 0U;
/*
    uint32      ErrorCode;
    uint32      cpu;
*/
    Ifx_CPU  *  module;
  
    IfxStart_Ram_Tst = 0U;

    /* Get the reset Reason */
    RestCode = IfxScu_ResetRamEval();
    
    /* Initialize port pins to default */
    IfxStart_Defaults();
    
    /* safety tests to be done */
    IfxStart_SafetyTestEx();  
  
 /*   RamTest =
      IfxStart_memTest(IFXSTART_NUM_RAM_SECTIONS,  &ErrorAddr ,IfxStart_kRamTstConfiguration);
  */
    /* If RAM test is successful */
    if (!RamTest)
    {
      /* Call driver Init Exception */
      IfxStart_DriverInitEx();
  
      /* Driver Initializations */
      IfxStart_DriverInit();
  
      /* */
      IfxStart_SysInitEx();
  
      /* Start all CPU */
      if (IfxCpu_ResourceCpu_0 == IfxCpu_getCoreId())
      {
          #if defined  (IFX_CPU_ENABLE_TRICORE1)
          IfxStart_Cpu(IfxCpu_ResourceCpu_1, ((uint32) (&_Core1_start)));
        #endif   
      }
      else if (IfxCpu_ResourceCpu_1 == IfxCpu_getCoreId())
      {
        /* Set Core 0 to Running */
        module = IfxCpu_getAddress (IfxCpu_ResourceCpu_0) ;
        RetVal = IfxCpu_setCoreMode(module, IfxCpu_CoreMode_run);
  
        /* In case of error */
        if (!RetVal)
        {
          /* Some error code should never come here, can remove in production code */
          return (1U);
        }  
      }
      /* Start CPU2 */
      #if defined  (IFX_CPU_ENABLE_TRICORE2)
        IfxStart_Cpu(IfxCpu_ResourceCpu_2, ((uint32) (&_Core2_start)));
      #endif   
  
      IfxStart_CpuEx();
    }
#if 0
    else
    {
      /* s(CPU � 1st nibble ) t(basic type) uv wx yz h, 
         ST = 0(CPU) 8 (Application) 
         UV = application error , 1 CSA error and 2 RAM Test error
         WX = reserved for future
         YZ = reserved for future
       */
      ErrorCode = 0U;
      /* cpux and Address */
      cpu = IfxCpu_getCoreId();
      ErrorCode |= ((cpu | ((uint32) IfxStart_ErrorType_appError)) << 24U);
      ErrorCode |= (IFXSTART_RAM_TEST_ERROR << 16U);
      IfxStart_ErrorEx(ErrorCode, (uint32) ErrorAddr);
    }
#endif
    return (1U);
}

/** \brief The other CPUs are started
 *
 * \param CPU Core to start
 *
 * \return  None
 *
 */
uint32 IfxStart_Cpu(IfxCpu_ResourceCpu cpuCoreToStart, uint32 pc_val)
{
  /* IfxCpu_CoreMode Core_Mode;*/
  uint32              RetVal;
  Ifx_CPU            *module;

  /* Set the PC for Core 1 */
  module = IfxCpu_getAddress (cpuCoreToStart) ;
  
  RetVal = IfxCpu_startCore (module , (uint32) (pc_val)) ;
  return (RetVal);
}

/** \brief Configure the port pin.
 *
 * \param config Specifies the pin details to be configured.
 *
 * \return None.
 */
void IfxStartPort_init(IfxStart_Pin_Config * port_config_data, uint8 Num_Port_pins)
{
  Ifx_P      *port;
  uint8       pinIndex;
  uint8       index;
  IfxPort_Mode mode;
  IfxPort_PadDriver padDriver;

  for (index = 0; index < Num_Port_pins; index++)
  {
    port = (port_config_data + index)->port;
    pinIndex = (port_config_data + index)->pinIndex;
    mode = (port_config_data + index)->mode;

    padDriver = (port_config_data + index)->padDriver;
    IfxPort_setPinMode(port, pinIndex, (IfxPort_Mode)((uint32)mode << 3U));
    IfxPort_setPinPadDriver(port, pinIndex, padDriver);
    
    /* if (OUT_GPIO_OFF != (port_config_data + index)->DefaultState) */
    {
      IfxPort_setPinState(port, pinIndex,
                          (port_config_data + index)->DefaultState);
    }

  }
} /* End of IfxStartPort_init */

void IfxStart_PerformReset(uint8  resetType,uint32 userInfo)
{
    IfxScuCcu_PerformReset(resetType , userInfo);
}
/*lint -restore */
