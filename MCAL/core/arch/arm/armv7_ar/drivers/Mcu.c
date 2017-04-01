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

/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */
/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ */


/* ----------------------------[includes]------------------------------------*/


#include <string.h>
#include "Std_Types.h"
#include "SchM_Mcu.h"
#include "Mcu.h"
#include "Mcu_Arc.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#include "Cpu.h"
#include "io.h"
#if defined(USE_KERNEL)
#include "irq.h"
#endif

/* Global requirements */
/* !req SWS_Mcu_00130 */
/* @req SWS_Mcu_00237 Mcu_ModeType specifies the identification mode */
/* @req SWS_Mcu_00239 Mcu_RamSectionType specifies the identification of ram section */
/* @req SWS_Mcu_00232 Mcu_ClockType defines the identification of clock type*/
/* @req SWS_Mcu_00152 Imported types */
/* @req SWS_Mcu_00226 Production Errors shall not be used as the return value of the called function */

/* API parameter checking */
/* @req SWS_Mcu_00017 OK*/


#include "zynq.h"
#include "irq_zynq.h"

/* ----------------------------[private define]------------------------------*/

#define CLK_CTRL_SRCSEL(_x)		((uint32)(_x)<<4u)

#define CLK_CTRL_DIVISOR_M 		0x3f00u
#define CLK_CTRL_DIVISOR1_M		0x3f00000u
#define CLK_CTRL_SRCSEL_M		0x30u

/* Used for ARM_CLK_CTRL register */
#define SRCSEL_ARM_CLK_CTRL_ARM_PLL		0u
#define SRCSEL_ARM_CLK_CTRL_DDR_PLL		2u
#define SRCSEL_ARM_CLK_CTRL_IO_PLL		3u

/* Used for other clock control registers */
#define SRCSEL_ARM_PLL     2u
#define SRCSEL_DDR_PLL     3u
#define SRCSEL_IO_PLL      0u


#define ZYNQ_SILICON_REV_1_0	0u
#define ZYNQ_SILICON_REV_2_0	1u
#define ZYNQ_SILICON_REV_3_0	2u
#define ZYNQ_SILICON_REV_3_1	3u

/* ----------------------------[private macro]-------------------------------*/

/* Development error macros. */
/* @req SWS_Mcu_00163 */
#if ( MCU_DEV_ERROR_DETECT == STD_ON )

/* Sanity check */
#if !defined(USE_DET)
#error DET not configured when MCU_DEV_ERROR_DETECT is set
#endif

#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(MCU_MODULE_ID,0,_api,_err); \
          return; \
        }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(MCU_MODULE_ID,0,_api,_err); \
          return (_rv); \
        }
#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_W_RV(_exp,_api,_err,_rv )
#endif

#define MCU_ASSERT(_x)		if( !(_x) ) { while(1) {} }


#define SET_REG(_register, _mask, _value) ((_register) = ( (_register) & ~(uint32)(_mask) ) | ( (uint32)(_value) ) )

/* ----------------------------[private typedef]-----------------------------*/

/**
 * Type that holds all global data for Mcu
 */
typedef struct
{
    boolean 			 initRun;	   /* Set if Mcu_Init() have been called */
    const Mcu_ConfigType *config;	   /* Saved pointer to the configuration from Mcu_Init() */
    Mcu_ClockType        clockSetting; /* Saved clock setting from Mcu_InitClock() */
    Mcu_RawResetType rawResetvalue;
    Mcu_ResetType resetReason;
} Mcu_GlobalType;



/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

/* Set SFR registers of MCU properly.*/
typedef volatile struct SLCR_reg Mcu_SlcrHwRegType;
/*lint -e{923} cast from unsigned int to pointer MISRA 2004 11.1 11.3 2012 11.4 11.6
 * Integer to pointer casting is necessary to set SFR of Microcontroller. */
static Mcu_SlcrHwRegType* const SLCR_PTR = (Mcu_SlcrHwRegType*)ZYNQ_SLCR_BASE;


/*lint -save -e785 Misra 2012 9.3 Too few initializers.
 * Just the necessary record are initialized. */
Mcu_GlobalType Mcu_Global =
{
    .initRun = FALSE,
    .config = &McuConfigData[0],
};
/*lint -restore*/

/**
 * Get the system clock in Hz. It calculates the clock from the
 * different register settings in HW.
 */
uint32 Mcu_Arc_GetSystemClock(void) {

    return (uint32)MCU_ARC_CLOCK_ARM_CPU_3X2X_FREQUENCY;
}

/* ----------------------------[private functions]---------------------------*/


/* @req SWS_Mcu_00052*/
Mcu_ResetType Mcu_Arc_GetResetReason(void)
{
    return Mcu_Global.resetReason;
}

static uint32 zynq_GetRevision( void ) {
    /*lint -e{923} cast from unsigned int to pointer MISRA 2004 11.1 11.3 2012 11.4 11.6
     * Integer to pointer casting is necessary to set SFR of Microcontroller. */
    return ((DEVCFG_REG.MCTRL & (uint32)0xf0000000u) >> 28u);
}

static void zynq_GetAndClearResetCause(void) {
    Mcu_ResetType resetReason = MCU_RESET_UNDEFINED;

    SLCR_PTR->SLCR_UNLOCK = 0x0000DF0DU;	/* Unlock SLCR registers */

    uint32 status = SLCR_PTR->REBOOT_STATUS;
    /* Get RAW reset value and resetReason value and save it */
    Mcu_Global.rawResetvalue = status;

    if ( 0u !=  ( status & (((uint32)1u<<21u) + ((uint32)1u<<19u)) ) ) {					/* SRST_B (external reset) + SLC_RST (system software)  */
        resetReason = MCU_SW_RESET;
    } else if ( 0u != (status & (((uint32)1u<<16u) + ((uint32)1u<<17u) + ((uint32)1u<<18u)) ) ) {	/* SWDT_RST + AWDT0_RST + AWDT1_RST */
        resetReason = MCU_WATCHDOG_RESET;
    } else if ( 0u != ( status & ((uint32)1u<<22u) ) ) {							/* POR */
        resetReason = MCU_POWER_ON_RESET;
    } else {
        ;/*do nothing*/
    }

    if((status & 0x00FFFFFFU) !=0u){ /*only save new resetReasons*/
        Mcu_Global.resetReason = resetReason;
    }
    SLCR_PTR->REBOOT_STATUS &= 0xFF800000U; /*bits 31:24 user defines, bit 23 reserved*/
    SLCR_PTR->SLCR_LOCK = 0x0000767BU;	/* Lock SLCR again */
}

#if ( MCU_NO_PLL == STD_OFF )

/**
 * Init PLL's for Zynq 7020
 *
 * @return
 */
static int32_t zynq_InitPll( const Mcu_ClockSettingConfigType *cPtr ) {

    SLCR_PTR->SLCR_UNLOCK = 0x0000DF0DU;	/* Unlock SLCR registers */

    SET_REG(SLCR_PTR->ARM_PLL_CFG,  0x003FFFF0U , cPtr->ARM_PLL_CFG );

    SET_REG(SLCR_PTR->ARM_PLL_CTRL, 0x0007F000U , cPtr->ARM_PLL_CTRL);
    /* Set PLL_BYPASS_FORCE  */
    SET_REG(SLCR_PTR->ARM_PLL_CTRL, 0x00000010U ,0x00000010U);
    /* Assert PLL_RESET */
    SET_REG(SLCR_PTR->ARM_PLL_CTRL, 0x00000001U ,0x00000001U);
    /* De-Assert PLL_RESET */
    SET_REG(SLCR_PTR->ARM_PLL_CTRL, 0x00000001U ,0x00000000U); /*lint !e835 A zero has been given as argument tolerated to use uniform macros to set SFRs*/

    /* Check ARM_PLL_LOCK Status */
    while( 0u != (SLCR_PTR->PLL_STATUS & (uint32)1u) ) {};	/* IMPROVEMENT: Add timeout */

    SET_REG(SLCR_PTR->ARM_PLL_CTRL, 0x00000010U ,0x00000000U);/*lint !e835 A zero has been given as argument tolerated to use uniform macros to set SFRs*/

    /*lint -e{835} -e{845} A zero has been given as argument
     * Tolerable to have arguments with 0 value. Unified macros used to set each bit of an SFR*/
    SET_REG(SLCR_PTR->ARM_CLK_CTRL,
                        0x1F000000U | CLK_CTRL_DIVISOR_M | CLK_CTRL_SRCSEL_M  ,
                        cPtr->ARM_CLK_CTRL | CLK_CTRL_SRCSEL(SRCSEL_ARM_CLK_CTRL_ARM_PLL));

    /* IO_PLL Setup */
    SET_REG(SLCR_PTR->IO_PLL_CFG,  0x003FFFF0U , cPtr->IO_PLL_CFG );

    SET_REG(SLCR_PTR->IO_PLL_CTRL, 0x0007F000U , cPtr->IO_PLL_CTRL);
    SET_REG(SLCR_PTR->IO_PLL_CTRL, 0x00000010U ,0x00000010U);
    SET_REG(SLCR_PTR->IO_PLL_CTRL, 0x00000001U ,0x00000001U);
    SET_REG(SLCR_PTR->IO_PLL_CTRL, 0x00000001U ,0x00000000U);/*lint !e835 A zero has been given as argument tolerated to use uniform macros to set SFRs*/

    while( 0u != (SLCR_PTR->PLL_STATUS & (uint32)4u) ) {};	/* IMPROVEMENT: Add timeout */

    SET_REG(SLCR_PTR->IO_PLL_CTRL, 0x00000010U ,0x00000000U);/*lint !e835 A zero has been given as argument tolerated to use uniform macros to set SFRs*/

    SLCR_PTR->SLCR_LOCK = 0x0000767BU;	/* Lock SLCR again */

    return 0;
}


/**
 * Init clocks
 *
 * @param cPtr Pointer to the clock settings configuration
 * @return
 */
static int32_t zynq_InitClocks( const Mcu_ClockSettingConfigType *cPtr  ) {

    SLCR_PTR->SLCR_UNLOCK = 0x0000DF0DU;	/* Unlock SLCR registers */

    /* CAN 0 and 1*/
    SET_REG(SLCR_PTR->CAN_CLK_CTRL,
                CLK_CTRL_DIVISOR_M + CLK_CTRL_DIVISOR1_M + CLK_CTRL_SRCSEL_M + 3 ,
                cPtr->CAN_CLK_CTRL + CLK_CTRL_SRCSEL(SRCSEL_IO_PLL));/*lint !e835 !e845 A zero has been given as argument tolerated to use uniform macros to set SFRs*/

    SET_REG( SLCR_PTR->CAN_MIOCLK_CTRL , 0xffffffffu , cPtr->CAN_MIOCLK_CTRL);/*lint !e845 A zero has been given as argument tolerated to use uniform macros to set SFRs*/


    /* Eth 0 */
    SET_REG(SLCR_PTR->GEM0_CLK_CTRL,
                CLK_CTRL_DIVISOR_M + CLK_CTRL_DIVISOR1_M + CLK_CTRL_SRCSEL_M + 1 ,
                cPtr->GEM0_CLK_CTRL + CLK_CTRL_SRCSEL(SRCSEL_IO_PLL)); /*lint !e845 !e835 A zero has been given as argument tolerated to use uniform macros to set SFRs*/

    SET_REG(SLCR_PTR->GEM0_RCLK_CTRL, 0xffffffffu,cPtr->GEM0_RCLK_CTRL);/*lint !e845 A zero has been given as argument tolerated to use uniform macros to set SFRs*/

    /* Eth 1 */
    SET_REG(SLCR_PTR->GEM1_CLK_CTRL,
                CLK_CTRL_DIVISOR_M + CLK_CTRL_DIVISOR1_M + CLK_CTRL_SRCSEL_M + 1 ,
                cPtr->GEM1_CLK_CTRL + CLK_CTRL_SRCSEL(SRCSEL_IO_PLL)); /*lint !e845 !e835 A zero has been given as argument tolerated to use uniform macros to set SFRs*/

    SET_REG(SLCR_PTR->GEM1_RCLK_CTRL, 0xffffffffu, cPtr->GEM1_RCLK_CTRL);/*lint !e845 A zero has been given as argument tolerated to use uniform macros to set SFRs*/

    /* SMC */
    SET_REG(SLCR_PTR->SMC_CLK_CTRL,
                CLK_CTRL_DIVISOR_M + CLK_CTRL_SRCSEL_M + 1 ,
                cPtr->SMC_CLK_CTRL + CLK_CTRL_SRCSEL(SRCSEL_IO_PLL));/*lint !e845 !e835 A zero has been given as argument tolerated to use uniform macros to set SFRs*/

    /* QuadSPI */
    SET_REG(SLCR_PTR->LQSPI_CLK_CTRL,
                CLK_CTRL_DIVISOR_M + CLK_CTRL_SRCSEL_M + 1 ,
                cPtr->LQSPI_CLK_CTRL + CLK_CTRL_SRCSEL(SRCSEL_IO_PLL));/*lint !e845 !e835 A zero has been given as argument tolerated to use uniform macros to set SFRs*/



    /* Skip FPGA clocks for now, ie PllFckDivisor_0 and PllFckDivisor_1 */


    /* SDIO 0 and 1 */
    SET_REG(SLCR_PTR->SDIO_CLK_CTRL,
                CLK_CTRL_DIVISOR_M + CLK_CTRL_SRCSEL_M + 3 ,
                cPtr->SDIO_CLK_CTRL + CLK_CTRL_SRCSEL(SRCSEL_IO_PLL)); /*lint !e845 !e835 A zero has been given as argument tolerated to use uniform macros to set SFRs*/


    /* Uart 0 and 1 */
    SET_REG(SLCR_PTR->UART_CLK_CTRL,
                CLK_CTRL_DIVISOR_M + CLK_CTRL_SRCSEL_M + 3 ,
                cPtr->UART_CLK_CTRL + CLK_CTRL_SRCSEL(SRCSEL_IO_PLL)); /*lint !e845 !e835 A zero has been given as argument tolerated to use uniform macros to set SFRs*/

    /* SPI 0 and 1 */
    SET_REG(SLCR_PTR->SPI_CLK_CTRL,
                CLK_CTRL_DIVISOR_M + CLK_CTRL_SRCSEL_M + 3 ,
                cPtr->SPI_CLK_CTRL + CLK_CTRL_SRCSEL(SRCSEL_IO_PLL)); /*lint !e845 !e835 A zero has been given as argument tolerated to use uniform macros to set SFRs*/

    /* Trace, Skip for now */


    /* PCAP */
    SET_REG(SLCR_PTR->PCAP_CLK_CTRL,
                CLK_CTRL_DIVISOR_M + CLK_CTRL_SRCSEL_M + 1 ,
                cPtr->PCAP_CLK_CTRL + CLK_CTRL_SRCSEL(SRCSEL_IO_PLL)); /*lint !e845 !e835 A zero has been given as argument tolerated to use uniform macros to set SFRs*/


    /* Write APER */
    {
        uint32 val = 	((cPtr->SMC_CLK_CTRL & (uint32)1u)<<24u) +
                        ((cPtr->LQSPI_CLK_CTRL & (uint32)1u)<<23u) +
                        /* 22 GPIO */
                        ((cPtr->UART_CLK_CTRL & (uint32)2u)<<20u) +
                        ((cPtr->UART_CLK_CTRL & (uint32)1u)<<20u) +
                        /* 19-18 I2C */
                        ((cPtr->CAN_CLK_CTRL & (uint32)2u)<<16u) +
                        ((cPtr->CAN_CLK_CTRL & (uint32)1u)<<16u) +
                        ((cPtr->SPI_CLK_CTRL & (uint32)2u)<<14u) +
                        ((cPtr->SPI_CLK_CTRL & (uint32)1u)<<14u) +
                        /* 13,12 reserved */
                        ((cPtr->SDIO_CLK_CTRL & (uint32)2u)<<10u) +
                        ((cPtr->SDIO_CLK_CTRL & (uint32)1u)<<10u) +
                        /* 9,8 reserved */
                        ((cPtr->GEM1_CLK_CTRL & (uint32)1u)<<7u) +
                        ((cPtr->GEM0_CLK_CTRL & (uint32)1u)<<6u)
                        /* 1 reserved */
                        /* 0 DMA */
                        ;

        SET_REG(SLCR_PTR->APER_CLK_CTRL,
                    ((uint32)3u<<23u)+((uint32)3u<<20u)+((uint32)3u<<16u)+((uint32)3u<<14u)+((uint32)3u<<10u)+((uint32)3u<<6u),
                    val);

    }

    SLCR_PTR->SLCR_LOCK = 0x0000767BU;	/* Lock SLCR again */

    return 0;
}

#endif /*  ( MCU_NO_PLL == STD_OFF ) */


/**
 * Get PLL status. Only ARM PLL is checked here..
 */

static Mcu_PllStatusType zynq_GetPllStatus( void ) {
    Mcu_PllStatusType rv = MCU_PLL_UNLOCKED;

    SLCR_PTR->SLCR_UNLOCK = 0x0000DF0DU;	/* Unlock SLCR registers */

    /* Check ARM_PLL_LOCK Status */
    if ( 0u != ( SLCR_PTR->PLL_STATUS & (uint32)1u) ) {
        rv = MCU_PLL_LOCKED;
    }

    SLCR_PTR->SLCR_LOCK =  0x0000767BU;	/* Lock SLCR again */

    return rv;
}



/* ----------------------------[public functions]----------------------------*/



/* @req SWS_Mcu_00026  */
/* @req SWS_Mcu_00116  */
/* @req SWS_Mcu_00244  */
/* @req SWS_Mcu_00245  */
/* @req SWS_Mcu_00246  */
/* @req SWS_Mcu_00247  */
/* @req SWS_Mcu_00153  */
void Mcu_Init(const Mcu_ConfigType *ConfigPtr)
{
    /* @req SWS_Mcu_00018 */
    VALIDATE( ( NULL != ConfigPtr ), MCU_INIT_SERVICE_ID, MCU_E_PARAM_CONFIG );

    /* Check Revision, assume backward compatible  */
    /*lint -e{716} -e{9036}
     * while(1),
     * Conditional expression should have essentially Boolean type Misra 2012 14.4
     * All these warning are tolerable to stop code execution */
    MCU_ASSERT( (zynq_GetRevision() >= ZYNQ_SILICON_REV_3_1) );

    /* Get reset cause and clear */
    zynq_GetAndClearResetCause();

    Mcu_Global.config = ConfigPtr;
    Mcu_Global.initRun = TRUE;
}


void Mcu_Arc_DeInit( void )
{
    Mcu_Global.initRun = FALSE; // Very simple Deinit. Should we do more?
}


//-------------------------------------------------------------------

Std_ReturnType Mcu_InitRamSection(Mcu_RamSectionType RamSection)
{
    /* @req SWS_Mcu_00021 */
    /* @req SWS_Mcu_00125 */
    /* @req SWS_Mcu_00154 */
    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_INITRAMSECTION_SERVICE_ID, MCU_E_UNINIT, E_NOT_OK );
    VALIDATE_W_RV( ( RamSection <= Mcu_Global.config->McuRamSectors ), MCU_INITRAMSECTION_SERVICE_ID, MCU_E_PARAM_RAMSECTION, E_NOT_OK );

    /* @req SWS_Mcu_00011 */
    /*lint -save -e923 cast from unsigned int to pointer Misra 2004 11.1,2004 11.3,2012 11.1,2012 11.4, 2012 11.6
     * It suppression is necessary because function signature of memset is fixed*/
    memset(	(void *)Mcu_Global.config->McuRamSectorSettingConfig[RamSection].McuRamSectionBaseAddress,
            (sint32)Mcu_Global.config->McuRamSectorSettingConfig[RamSection].McuRamDefaultValue,
            (size_t)Mcu_Global.config->McuRamSectorSettingConfig[RamSection].McuRamSectionSize);
    /*lint -restore*/

    return E_OK;
}

//-------------------------------------------------------------------

/* @req SWS_Mcu_00137  */
/* @req SWS_Mcu_00210  */
/* !req SWS_Mcu_00138 Not supported because Mcu_InitClock busywaits until the PLL is locked. */
#if ( MCU_INIT_CLOCK == STD_ON )
/* @req SWS_Mcu_00155  */
Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting)
{
    const Mcu_ClockSettingConfigType *clockSettingsPtr;
    /* @req SWS_Mcu_00125  */
    /* @req SWS_Mcu_00019  */
    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_INITCLOCK_SERVICE_ID, MCU_E_UNINIT, E_NOT_OK );
    VALIDATE_W_RV( ( ClockSetting < Mcu_Global.config->McuClockSettings ), MCU_INITCLOCK_SERVICE_ID, MCU_E_PARAM_CLOCK, E_NOT_OK );

    Mcu_Global.clockSetting = ClockSetting;
    clockSettingsPtr = &Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting];

    (void)zynq_InitPll(clockSettingsPtr);
    (void)zynq_InitClocks(clockSettingsPtr);

    return E_OK;
}

#endif /* #if ( MCU_INIT_CLOCK == STD_ON )*/

//-------------------------------------------------------------------

/* @req SWS_Mcu_00205 */
#if ( MCU_NO_PLL == STD_OFF )
/* !req SWS_Mcu_00140  */
/* !req SWS_Mcu_00141 */
/* !req SWS_Mcu_00056 */
/* @req SWS_Mcu_00156 */
Std_ReturnType Mcu_DistributePllClock(void)
{
    /* @req SWS_Mcu_00125 */
    /* !req SWS_Mcu_00122 */

    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID, MCU_E_UNINIT, E_NOT_OK );
    VALIDATE_W_RV( ( zynq_GetPllStatus() == MCU_PLL_LOCKED), MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID, MCU_E_PLL_NOT_LOCKED, E_NOT_OK);

    return E_OK;
}

#endif /* #if ( MCU_NO_PLL == STD_ON ) */

//-------------------------------------------------------------------

/* @req SWS_Mcu_00008 */
/* @req SWS_Mcu_00157 */
/* @req SWS_Mcu_00230 */
Mcu_PllStatusType Mcu_GetPllStatus(void)
{

    /* @req SWS_Mcu_00206 */
#if ( MCU_NO_PLL == STD_ON )
    return MCU_PLL_STATUS_UNDEFINED;
#else
    /* @req SWS_Mcu_00125 */
    /* @req SWS_Mcu_00132 */
    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_GETPLLSTATUS_SERVICE_ID, MCU_E_UNINIT, MCU_PLL_STATUS_UNDEFINED );
    

#if defined(CFG_SIMULATOR)
    return MCU_PLL_LOCKED;
#endif

    return zynq_GetPllStatus();
#endif
}


//-------------------------------------------------------------------


/* @req SWS_Mcu_00158 */
Mcu_ResetType Mcu_GetResetReason(void)
{
    /* @req SWS_Mcu_00133 */
    /* @req SWS_Mcu_00125 */
    /* @req SWS_Mcu_00005 */
    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_GETRESETREASON_SERVICE_ID, MCU_E_UNINIT, MCU_RESET_UNDEFINED );

    return Mcu_Global.resetReason;
}

//-------------------------------------------------------------------

/* @req SWS_Mcu_00235 */
/* @req SWS_Mcu_00006 */
/* @req SWS_Mcu_00159 */
Mcu_RawResetType Mcu_GetResetRawValue(void)
{
    /* @req SWS_Mcu_00135 */
    /* @req SWS_Mcu_00125 */
    VALIDATE_W_RV( ( TRUE == Mcu_Global.initRun ), MCU_GETRESETREASON_SERVICE_ID, MCU_E_UNINIT, MCU_GETRESETRAWVALUE_UNINIT_RV );

    if( !Mcu_Global.initRun ) {
        return MCU_GETRESETRAWVALUE_UNINIT_RV;
    }

    return Mcu_Global.rawResetvalue;
}

//-------------------------------------------------------------------

#if ( MCU_PERFORM_RESET_API == STD_ON )
/* @req SWS_Mcu_00143 */
/* !req SWS_Mcu_00144 */
void Mcu_PerformReset(void)
{
    /* @req SWS_Mcu_00125 */
    VALIDATE( ( TRUE == Mcu_Global.initRun ), MCU_PERFORMRESET_SERVICE_ID, MCU_E_UNINIT );

    SLCR_PTR->SLCR_UNLOCK = 0x0000DF0DU;	/* Unlock SLCR registers */
    SLCR_PTR->PSS_RST_CTRL = 1; 			/* SOFT_RST */
    SLCR_PTR->SLCR_LOCK =  0x0000767BU;	/* Lock SLCR again */
}
#endif

//-------------------------------------------------------------------

void Mcu_SetMode( Mcu_ModeType mcuMode)
{

    /* @req SWS_Mcu_00125 */
    /* @req SWS_Mcu_00020 */
    VALIDATE( ( TRUE == Mcu_Global.initRun ), MCU_SETMODE_SERVICE_ID, MCU_E_UNINIT );
    VALIDATE( ( (mcuMode <= Mcu_Global.config->McuNumberOfMcuModes)), MCU_SETMODE_SERVICE_ID, MCU_E_PARAM_MODE );

    /* Low Power Mode
     * --------------------------------------
     *   APU
     *   SCU
     *   L2
     *   Peripherals
     *   Clock
     * */

    /* Shutdown core 2 (if on) */

    /* NOT_IMPLEMENTED: Sleep mode not supported  */

}
/* @req SWS_Mcu_00162 */
void Mcu_GetVersionInfo( Std_VersionInfoType* versioninfo) {

    /* @req SWS_Mcu_00204 */
    VALIDATE( ( NULL != versioninfo ), MCU_GETVERSIONINFO_SERVICE_ID, MCU_E_PARAM_POINTER);

    versioninfo->vendorID = MCU_VENDOR_ID;
    versioninfo->moduleID = MCU_MODULE_ID;
    versioninfo->sw_major_version = MCU_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = MCU_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = MCU_SW_PATCH_VERSION;

}


/**
 * Get frequency of the oscillator
 */
uint32 Mcu_Arc_GetClockReferencePointFrequency(void)
{
    return Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting].McuClockReferencePointFrequency;
}


/********************************************************************
 * Mcu_Arc_InitZero
 *
 * Function that perform all necessary initialization needed to to run software, such as disabling watchdog,
 * init ECC RAM, setup exception vectors etc
 ********************************************************************/
void Mcu_Arc_InitZero(void) {
    /********************************************************************************
     * NOTE
     *
     * This function will be called before BSS and DATA are initialized.
     * Ensure that you do not access any global or static variables before
     * BSS and DATA is initialized
     ********************************************************************************/

    Mcu_Arc_PlatformInit();

#if defined(USE_KERNEL)
    Irq_Init();
#endif
}
