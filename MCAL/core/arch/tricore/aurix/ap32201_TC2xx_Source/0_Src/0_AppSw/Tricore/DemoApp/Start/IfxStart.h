/**
 * \file IfxStart.h
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
 * $Revision: 003 $
 * $Date: 24-05-2013 12:09 +0530 $
 *
 * \defgroup Ifx Infineon Software
 * \defgroup Ifx_Lld Infineon Low Level Drivers' Software
 * \ingroup I
 */ 

#ifndef IFXSTART_H_
#define IFXSTART_H_

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "IfxStart_Cfg.h"
/*#include "IfxEdMem.h"*/
#include "IfxScuCcu.h"
#include "IfxScuRcu.h"
#include "IfxPort.h"
#include "IfxMtu_Cfg.h"

#define IFXSTART_CSA_TEST_ERROR         (1U)
#define IFXSTART_RAM_TEST_ERROR         (2U)


#define IfxStart_NORMAL_RESET          (0U) /* SW Reset */
#define IfxStart_SW_RES                (1U)       /* SW Reset */
#define IfxStart_ILL_BUS               (2U)      /* SW Reset */
#define IfxStart_ILL_INA               (3U)      /* SW Reset */
#define IfxStart_ILL_OPA               (4U)      /* SW Reset */
#define IfxStart_PRT_FLT               (5U)      /* SW Reset */
#define IfxStart_WDT_RES               (6U)      /* SMU Reset */
#define IfxStart_HW_RES                (7U)       /* PORST */
#define IfxStart_MAC_TRP               (8U)      /* SW Reset */
#define IfxStart_UND_OPC               (9U)      /* SW Reset */
#define IfxStart_ILL_INTR              (10U)     /* SW Reset */
/* The below type is in case of stack memory test failure */
#define IfxStart_STK_UNF               (11U)       /* SW Reset */
#define IfxStart_STK_OVF               (12U)       /* SW Reset */
#define IfxStart_NMI_INT               (13U)       /* SW Reset TIN7 */
#define IfxStart_PLL_RES               (14U)
#define IfxStart_EXT_RES               (15U)
#define IfxStart_BATTERY_OFF           (16U)
#define IfxStart_RES_UNKNOWN           (0xFFFF)       /* reset cause unknown*/

#define MODE_OUT				       16U        /* Output mode selected for Port pin - IOCR */
#define MODE_OUT_PUSHPULL               0U         /* Output,  Push-pull output mode selected for Port pin - IOCR */
#define MODE_OUT_GPIO		    		0U         /* Output, General-purpose output selected for Port pin - IOCR */
#define OUT_GPIO_OFF	    			2U         /* Reset or disabled state - to be used incase input selected for Port pin */

#define MODE_OUT_ALT1		    		1U         /* Output, Alternate output function 1 selected for Port pin - IOCR */

#define MODE_OUT_ALT2		    		2U         /* Output, Alternate output function 2 selected for Port pin - IOCR */

#define MODE_OUT_ALT3		    		3U         /* Output, Alternate output function 3 selected for Port pin - IOCR */

#define MODE_OUT_ALT4		    		4U         /* Output, Alternate output function 4 selected for Port pin - IOCR  */

#define MODE_OUT_ALT5		    		5U         /* Output, Alternate output function 5 selected for Port pin - IOCR  */

#define MODE_OUT_ALT6		    		6U         /* Output, Alternate output function 6 selected for Port pin - IOCR  */

#define MODE_OUT_ALT7		    		7U         /* Output, Alternate output function 7 selected for Port pin - IOCR  */
#define PDR_CMOS		    				0U         /* Automotive CMOS level, Port Output Voltage threshold level for Port pin  - PDR */
#define PDR_SG3		    				  2U         /* Pad driver strength and slew rate, Speed Grade 3 selected for Port pin - PDR */
#define PDR_SG1		    				  0U         /* Pad driver strength and slew rate, Speed Grade 1 selected for Port pin - PDR */
/*******************************************************************************
**                      Type definitions                                     **
*******************************************************************************/

typedef enum
{
  IfxStart_ErrorType_tinError  = 1U, /* RAM Test Error */
  IfxStart_ErrorType_smuError  = 2U, /* SMU Error */
  IfxStart_ErrorType_addrError = 3U,    /* Address Error */
  IfxStart_ErrorType_appError  = 8U  /* Aplication Error */
} IfxStart_ErrorType;


typedef enum
{
  IfxStart_ClassbError_Type_Mmu = 1U,
  IfxStart_ClassbError_Type_Protection = 2U,
  IfxStart_ClassbError_Type_Intsruction = 3U,
  IfxStart_ClassbError_Type_Context = 4U,
  IfxStart_ClassbError_Type_Bus = 5U,
  IfxStart_ClassbError_Type_Assertion = 6U,
  IfxStart_ClassbError_Type_SysCall = 7U,
  IfxStart_ClassbError_Type_Nmi = 8U
} IfxStart_ClassbError_Type;



/*******************************************************************************
**                Global Exported variables/constants                         **
*******************************************************************************/

/*******************************************************************************
**         Global Exported macros/inlines/function ptototypes                 **
*******************************************************************************/
int         Start_Main(void);
int         core1_main(void);
int         core2_main(void);
void        IfxStart_CpuEx(void);
void        IfxStart_Defaults(void);
void        IfxStart_SysInitEx(void);
void        IfxStart_DriverInit(void);
void        IfxStart_SafetyTestEx(void);
void        IfxStart_DriverInitEx(void);
uint8       IfxStart_getMemTestStatus(void);
void        IfxStart_memTestEnable(uint8 RamTest_Run);
void        IfxStart_BootLdrToApplJump(uint32 address);
void IfxStart_PerformReset(uint8  resetType,uint32 userInfo) ;
uint8 IfxStart_memTest(uint8 Num_Sections, uint16 * ErrorAddr ,
                      IfxStart_RamTestCfgType * RamTstConfigPtr );
void        IfxStart_ErrorEx(uint32 errorCode, uint32 ErrorInfo);
uint32  IfxStart_Cpu(IfxCpu_ResourceCpu cpuCoreToStart, uint32 pc_val);

void        IfxStart_RangeFromAddress
  (uint32 * SegStart_Address,uint32 * SegEnd_Address,
   uint8 * SegStart, uint8 * SegEnd, uint8 MbistNumber);

void IfxStartPort_init(IfxStart_Pin_Config * port_config_data, uint8 Num_Port_pins);

#endif   /* IFXSTART_H_ */
