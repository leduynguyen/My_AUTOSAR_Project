/*-------------------------------- Arctic Core ------------------------------
 * Copyright (C) 2013, ArcCore AB, Sweden, www.arccore.com.
 * Contact: <contact@arccore.com>
 * 
 * You may ONLY use this file:
 * 1)if you have a valid commercial ArcCore license and then in accordance with  
 * the terms contained in the written license agreement between you and ArcCore, 
 * or alternatively
 * 2)if you follow the terms found in GNU General Public License version 2 as 
 * published by the Free Software Foundation and appearing in the file 
 * LICENSE.GPL included in the packaging of this file or here 
 * <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>
 *-------------------------------- Arctic Core -----------------------------*/

/*lint -w1 */
/** @tagSettings DEFAULT_ARCHITECTURE=STM32 */

#include "Std_Types.h"
#include "Mcu.h"
#include "Mcu_Arc.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"    /*lint !e537 According to ASR this include is needed in Mcu.c
                      Mcu.h also needs this include to solve DEM type dependency*/
#endif
#include <assert.h>
#include <string.h> /*lint !e537 this inclusion is needed for memeset defnition */
#include "Ramlog.h"

/* General Tagging */
/* @req SWS_Mcu_00017 */ /* Return E_NOT_OK in case of errors*/
/* @req SWS_Mcu_00125 */ /* DET error MCU_E_UNINIT (except Mcu_GetVersionInfo) if any Api is invoked before Mcu_Init */
/* @req SWS_Mcu_00163 */ /* DET report error service is used */
/* @req SWS_Mcu_00226 */ /* Production errors shall not be used as return values of Api */

//#define USE_LDEBUG_PRINTF 1
#include "debug.h"


#ifndef ARRAY_SIZE
#define ARRAY_SIZE(_x)  (sizeof(_x)/sizeof((_x)[0]))
#endif

/* Development error macros. */
#if ( MCU_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(MCU_MODULE_ID,0u,_api,_err); \
          return; \
        }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(MCU_MODULE_ID,0u,_api,_err); \
          return (_rv); \
        }
#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_W_RV(_exp,_api,_err,_rv )
#endif


#define CORE_CPUID_CORTEX_M3   	0x411FC231UL



typedef struct {
    uint32 lossOfLockCnt;
    uint32 lossOfClockCnt;
} Mcu_Stats;

/**
 * Type that holds all global data for Mcu
 */
typedef struct
{
  // Set if Mcu_Init() have been called
  boolean initRun;

  // Our config
  const Mcu_ConfigType *config;

  Mcu_ClockType clockSetting;

  Mcu_Stats stats;

} Mcu_GlobalType;


// Global config
Mcu_GlobalType Mcu_Global =
{
        .initRun = 0,
        .config = &McuConfigData[0],
};

//-------------------------------------------------------------------


void Mcu_ConfigureFlash(void);



/* Haven't found any ID accessable from memory.
 * There is the DBGMCU_IDCODE (0xe0042000) found in RM0041 but it
 * you can't read from that address..
 */
const cpu_info_t cpu_info_list[] = {
    {
    .name = "arccore",
    .pvr = 0,
    },
    {
    .name = NULL,
    .pvr = 0,
    },
};

/* The supported cores
 */
const core_info_t core_info_list[] = {
    {
    .name = "CORE_ARM_CORTEX_M3",
    .pvr = CORE_CPUID_CORTEX_M3,
    },
    {
    .name = NULL,
    .pvr = 0,
    },
};


static core_info_t *Mcu_IdentifyCore(uint32 pvr)
{
  uint32 i;
  for (i = 0; i < ARRAY_SIZE(core_info_list); i++) {
    if (core_info_list[i].pvr == pvr) {
      return (core_info_t *) &core_info_list[i];
    }
  }

  return NULL;
}

/**
 * Identify the core, just to check that we have support for it.
 *
 * @return
 */
static uint32 Mcu_CheckCpu( void ) {

  uint32 pvr = SCB->CPUID;
  //uint32 pir;
  //cpu_info_t *cpuType;
  core_info_t *coreType;

  //cpuType = Mcu_IdentifyCpu(pvr);
  coreType = Mcu_IdentifyCore(pvr);

  if( (coreType == NULL) ) {
    // Just hang
//    while(1) ;
  }

  return 0;
}

static uint32_t GetPllValueFromMult(uint8_t pll)
{
    return (((uint32_t)pll - 2) << 18);
}

#ifdef STM32F10X_CL
static uint32_t GetPll2ValueFromMult(uint8_t pll)
{
    return (((uint32_t)pll - 2) << 8);
}
#endif



#if defined(CFG_BRD_STM32F3_DISCOVERY)

/* Adaption of stm32f1x to stm32f3x */
#define HSE_STARTUP_TIMEOUT   ((uint16_t)0x0500) /*!< Time out for HSE start up */

/*!< STM32F10x Standard Peripheral Library old definitions (maintained for legacy purpose) */
#define HSEStartUp_TimeOut   HSE_STARTUP_TIMEOUT
#define HSE_Value            HSE_VALUE
#define HSI_Value            HSI_VALUE


typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

#define RCC_CFGR_PLLMULL	RCC_CFGR_PLLMUL
#define RCC_CFGR_PLLSRC_HSE RCC_CFGR_PLLSRC_HSE_PREDIV

#endif

/**
  * Set bus clocks. SysClk,AHBClk,APB1Clk,APB2Clk
  */
static void SetClocks(const Mcu_ClockSettingConfigType *clockSettingsPtr)
{
  volatile uint32 StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;
  } while((HSEStatus == 0) && (StartUpCounter != HSEStartUp_TimeOut));

  if ((RCC->CR & RCC_CR_HSERDY) != (uint32)RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 2 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;


    /* HCLK = SYSCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;

    /* PCLK2 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;

    /* PCLK1 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;

#ifdef STM32F10X_CL
    /* Configure PLLs ------------------------------------------------------*/
    /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
    /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 5 = 8 MHz */

    RCC->CFGR2 &= (uint32_t)~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL |
                              RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC);
    RCC->CFGR2 |= (uint32_t)(RCC_CFGR2_PREDIV2_DIV5 | GetPll2ValueFromMult(clockSettingsPtr->Pll2) |
                             RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV5);

    /* Enable PLL2 */
    RCC->CR |= RCC_CR_PLL2ON;
    /* Wait till PLL2 is ready */
    while((RCC->CR & RCC_CR_PLL2RDY) == 0)
    {
    }

    /* PLL configuration: PLLCLK = PREDIV1 * 9 = 72 MHz */
    RCC->CFGR &= (uint32_t)~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 |
                            GetPllValueFromMult(clockSettingsPtr->Pll1));
#else
    /*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                        RCC_CFGR_PLLMULL));
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | GetPllValueFromMult(clockSettingsPtr->Pll1));
#endif /* STM32F10X_CL */

    /* Enable PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
    {
    }
  }
  else
  { /* HSE fails to start-up, the application will have wrong clock */
      NVIC_SystemReset();
  }
}

/**
  * Initialize Peripherals clocks
  */
static void InitPerClocks(void)
{
    RCC->AHBENR |= McuPerClockConfigData.AHBClocksEnable;
    RCC->APB1ENR |= McuPerClockConfigData.APB1ClocksEnable;
    RCC->APB2ENR |= McuPerClockConfigData.APB2ClocksEnable;
}

/**
  * Initialize Flash, PLL and clocks.
  */
static void InitMcuClocks(const Mcu_ClockSettingConfigType *clockSettingsPtr)
{
  /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
#ifndef STM32F10X_CL
  RCC->CFGR &= (uint32_t)0xF8FF0000;
#else
  RCC->CFGR &= (uint32_t)0xF0FF0000;
#endif /* STM32F10X_CL */

  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

#ifndef STM32F10X_CL
  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;
#else
  /* Reset PLL2ON and PLL3ON bits */
  RCC->CR &= (uint32_t)0xEBFFFFFF;

  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x00FF0000;

  /* Reset CFGR2 register */
  RCC->CFGR2 = 0x00000000;
#endif /* STM32F10X_CL */

  /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
  /* Configure the Flash Latency cycles and enable prefetch buffer */
  SetClocks(clockSettingsPtr);
}

//-------------------------------------------------------------------
/* @req SWS_Mcu_00026 */
void Mcu_Init(const Mcu_ConfigType *configPtr)
{
    /* @req SWS_Mcu_00018 */
  VALIDATE( ( NULL != configPtr ), MCU_INIT_SERVICE_ID, MCU_E_PARAM_CONFIG );

#if !defined(USE_SIMULATOR)
  (void)Mcu_CheckCpu();
#endif

  memset(&Mcu_Global.stats,0,sizeof(Mcu_Global.stats));

  Irq_Enable();

  Mcu_Global.config = configPtr;
  Mcu_Global.initRun = 1;
}

//-------------------------------------------------------------------
Std_ReturnType Mcu_InitRamSection(const Mcu_RamSectionType RamSection)
{
  VALIDATE_W_RV( ( 1 == Mcu_Global.initRun ), MCU_INITRAMSECTION_SERVICE_ID, MCU_E_UNINIT, E_NOT_OK );
    /* @req SWS_Mcu_00021 */
  VALIDATE_W_RV( ( RamSection <= Mcu_Global.config->McuRamSectors ), MCU_INITRAMSECTION_SERVICE_ID, MCU_E_PARAM_RAMSECTION, E_NOT_OK );

  /* NOT SUPPORTED, reason: no support for external RAM */

  return E_OK;
}



//-------------------------------------------------------------------

Std_ReturnType Mcu_InitClock(const Mcu_ClockType ClockSetting)
{
  const Mcu_ClockSettingConfigType *clockSettingsPtr;
  VALIDATE_W_RV( ( 1 == Mcu_Global.initRun ), MCU_INITCLOCK_SERVICE_ID, MCU_E_UNINIT, E_NOT_OK );
    /* @req SWS_Mcu_00019 */
  VALIDATE_W_RV( ( ClockSetting < Mcu_Global.config->McuClockSettings ), MCU_INITCLOCK_SERVICE_ID, MCU_E_PARAM_CLOCK, E_NOT_OK );
  /* !req SWS_Mcu_00210 */
  Mcu_Global.clockSetting = ClockSetting;
  clockSettingsPtr = &Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting];
    /* @req SWS_Mcu_00137 */
  InitMcuClocks(clockSettingsPtr);

  InitPerClocks();

  return E_OK;
}

//-------------------------------------------------------------------

Std_ReturnType Mcu_DistributePllClock(void)
{
  VALIDATE_W_RV( ( 1 == Mcu_Global.initRun ), MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID, MCU_E_UNINIT, E_NOT_OK);
//  VALIDATE( ( FMPLL.SYNSR.B.LOCK == 1 ), MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID, MCU_E_PLL_NOT_LOCKED );

  /* NOT IMPLEMENTED due to pointless function on this hardware */

  return E_OK;

}

//-------------------------------------------------------------------


Mcu_PllStatusType Mcu_GetPllStatus(void) {
    /* @req SWS_Mcu_00132 */
    VALIDATE_W_RV( ( 1 == Mcu_Global.initRun ), MCU_GETPLLSTATUS_SERVICE_ID, MCU_E_UNINIT, MCU_PLL_STATUS_UNDEFINED );
    Mcu_PllStatusType rv;

#if !defined(USE_SIMULATOR)
    if (RCC->CR & RCC_CR_PLLRDY) {
        rv = MCU_PLL_LOCKED;
    } else {
        rv = MCU_PLL_UNLOCKED;
    }
#else
    /* We are running on instruction set simulator. PLL is then always in sync... */
    rv = MCU_PLL_LOCKED;
#endif
    return rv;
}

//-------------------------------------------------------------------

/**
 *
 * @return
 */
 
/* @req SWS_Mcu_00052*/
Mcu_ResetType Mcu_GetResetReason(void) {
    Mcu_ResetType rv;
    uint32_t csr;

    VALIDATE_W_RV( ( 1 == Mcu_Global.initRun ), MCU_GETRESETREASON_SERVICE_ID, MCU_E_UNINIT, MCU_RESET_UNDEFINED );

    csr = RCC->CSR;

    if (csr & RCC_CSR_SFTRSTF) {
        rv = MCU_SW_RESET;
    } else if (csr & (RCC_CSR_IWDGRSTF|RCC_CSR_WWDGRSTF) ) {
        rv = MCU_WATCHDOG_RESET;
    } else if ( csr & RCC_CSR_PORRSTF ) {
        rv = MCU_POWER_ON_RESET;
    } else {
        rv = MCU_RESET_UNDEFINED;
    }

    return rv;
}

//-------------------------------------------------------------------

/**
 * Shall read the raw reset value from hardware register if the hardware
 * supports this.
 *
 * @return
 */

Mcu_RawResetType Mcu_GetResetRawValue(void) {
    VALIDATE_W_RV( ( 1 == Mcu_Global.initRun ), MCU_GETRESETREASON_SERVICE_ID, MCU_E_UNINIT, MCU_GETRESETRAWVALUE_UNINIT_RV );

    if (!Mcu_Global.initRun) {
        return MCU_GETRESETRAWVALUE_UNINIT_RV;
    } else {
        return (RCC->CSR) & (RCC_CSR_RMVF | RCC_CSR_PINRSTF | RCC_CSR_PORRSTF
                | RCC_CSR_SFTRSTF | RCC_CSR_IWDGRSTF | RCC_CSR_WWDGRSTF
                | RCC_CSR_LPWRRSTF);
    }
    return 0;
}

//-------------------------------------------------------------------

#if ( MCU_PERFORM_RESET_API == STD_ON )
/**
 * Shell perform a microcontroller reset by using the hardware feature
 * of the micro controller.
 */
void Mcu_PerformReset(void)
{
  VALIDATE( ( 1 == Mcu_Global.initRun ), MCU_PERFORMRESET_SERVICE_ID, MCU_E_UNINIT );
    /* @req SWS_Mcu_00143 */
  NVIC_SystemReset();
}
#endif

//-------------------------------------------------------------------

void Mcu_SetMode(const Mcu_ModeType McuMode)
{
  VALIDATE( ( 1 == Mcu_Global.initRun ), MCU_SETMODE_SERVICE_ID, MCU_E_UNINIT );
  /* !req SWS_Mcu_00020 */
#if 0
  VALIDATE( (FALSE), MCU_SETMODE_SERVICE_ID, MCU_E_PARAM_MODE ); /*lint !e506 FALSE POSITIVE statement used to satisfy requirement SWS_Mcu_00020  */
#endif
  //VALIDATE( ( McuMode <= Mcu_Global.config->McuNumberOfMcuModes ), MCU_SETMODE_SERVICE_ID, MCU_E_PARAM_MODE );
  (void) McuMode;

}

//-------------------------------------------------------------------

/**
 * Get the system clock in Hz. It calculates the clock from the
 * different register settings in HW.
 */
uint32 Mcu_Arc_GetSystemClock(void)
{
  uint32_t f_sys;

  uint32  extal = Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting].McuClockReferencePointFrequency;
  uint32 pll1 = Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting].Pll1;

#ifdef STM32F10X_CL
  uint32 pll2 = Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting].Pll2;
  /* PLL2 configuration: PLL2CLK = (HSE / 5) * PLL2 */
  /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 5 */
  /* PLL configuration: PLLCLK = PREDIV1 * PLL1 */
  f_sys = (extal / 5 * pll2) / 5 * pll1;
#else
  /* PLL configuration: PLLCLK = HSE * PLL1 */
  f_sys = extal * pll1;
#endif

  return f_sys;
}

/**
 * Get the peripheral clock in Hz for a specific device
 */
uint32 Mcu_Arc_GetPeripheralClock(Mcu_Arc_PeriperalClock_t type)
{
    uint32_t res = 0;

    switch(type)
    {
    case PERIPHERAL_CLOCK_AHB:
        res = Mcu_Arc_GetSystemClock();
        break;
    case PERIPHERAL_CLOCK_APB1:
        res = Mcu_Arc_GetSystemClock() / 2;
        break;
    case PERIPHERAL_CLOCK_APB2:
        res = Mcu_Arc_GetSystemClock();
        break;
    default:
        break;
    }

    return res;
}

void Mcu_GetVersionInfo( Std_VersionInfoType* versioninfo) {

    /* @req SWS_Mcu_00204 */
    VALIDATE( ( NULL != versioninfo ), MCU_GETVERSIONINFO_SERVICE_ID, MCU_E_PARAM_POINTER);

    versioninfo->vendorID = MCU_VENDOR_ID;
    versioninfo->moduleID = MCU_MODULE_ID;
    versioninfo->sw_major_version = MCU_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = MCU_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = MCU_SW_PATCH_VERSION;

}

void Mcu_Arc_DeInit( void )
{
    Mcu_Global.initRun = FALSE; // Very simple Deinit. Should we do more?
}


/**
 * Function to setup the internal flash for optimal performance
 */

void Mcu_ConfigureFlash(void)
{

}
