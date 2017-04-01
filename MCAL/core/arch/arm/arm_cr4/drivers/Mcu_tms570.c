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

/*
* Copyright (C) 2009-2015 Texas Instruments Incorporated - www.ti.com
*
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/** @tagSettings DEFAULT_ARCHITECTURE=TMS570 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */


/* ----------------------------[Information]---------------------------------*/
/*
 * Manual updates from TI: (that are not SPNU515B, April 2015)
 * - VCLKACON1
 *   26:24 	VCLKA4R(2:0)
 *   20    	VCLKA4_DIV_CDDIS
 *   19:16 	VCLKA4S(3:0)
 *   10:8  	VCLKA3R(2:0)
 *   4		VCLKA3_DIV_CDDIS
 *   3:0  	VCLKA3S(3:0)
 *
 * - CLK2CNTRL
 *   11:8 	VCLK4R(3:0)
 *   3:0	VCLK3R(3:0)
 *
 * - CDDIS   (just added ones are here)
 *   10     CLRVCLKA3OFF
 *   7      RTICLK2OFF
 */
/* ----------------------------[includes]------------------------------------*/

#include "Std_Types.h"
#include "Mcu.h"
#include "Mcu_Internal.h"
#include "Mcu_Arc.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#include "arc_assert.h"
#include "Cpu.h"
#include <string.h>
#include "Ramlog.h"
#if defined(USE_KERNEL)
#include "irq.h"
#endif
#include "irq_tms570.h"
#include "core_cr4.h"

/* ----------------------------[private define]------------------------------*/


//#define USE_LDEBUG_PRINTF 1
#include "debug.h"

/* PLLCTL1 register */
#define	MCU_RESET_ON_SLIP				0  		// Reset on slip is off
#define	MCU_RESET_ON_SLIP_OFFSET		31  	// Offset in PLLCTL1

#define	MCU_BYPASS_ON_SLIP				2		// Bypass on slip is off
#define	MCU_BYPASS_ON_SLIP_OFFSET		29  	// Offset in PLLCTL1 (2 bits)

#define	MCU_RESET_ON_OSC_FAIL			0  		// Reset on oscillator fail is off
#define	MCU_RESET_ON_OSC_FAIL_OFFSET	23  	// Offset in PLLCTL1

#define	MCU_PLLDIV_OFFSET				24  	// Offset in PLLCTL1 (5 bits)
#define MCU_PLLDIV_MASK     			(0x1F << MCU_PLLDIV_OFFSET)
#define	MCU_REFCLKDIV_OFFSET			16  	// Offset in PLLCTL1 (6 bits)
#define MCU_REFCLKDIV_MASK  			(0x3F << MCU_REFCLKDIV_OFFSET)
#define	MCU_PLLMUL_OFFSET				0  		// Offset in PLLCTL1 (16 bits)
#define MCU_PLLMUL_MASK     			(0xFFFF << MCU_PLLMUL_OFFSET)

/* PLLCTL2 register */
#define MCU_FM_ENABLE					0  		// Frequency modulation is off
#define MCU_FM_ENABLE_OFFSET			31 		// Offset in PLLCTL2

#define MCU_SPREADING_RATE				0		// Spreading rate
#define MCU_SPREADING_RATE_OFFSET		22 		// Offset in PLLCTL2 (9 bits)

#define MCU_BWADJ						0 		// Bandwidth adjustment
#define MCU_BWADJ_OFFSET				12 		// Offset in PLLCTL2 (9 bits)

#define MCU_ODPLL_OFFSET				9		// Offset in PLLCTL2 (3 bits)
#define MCU_ODPLL_MASK     				(0x7 << MCU_ODPLL_OFFSET)

#define MCU_SPREADING_AMOUNT			0 		// Spreading amount
#define MCU_SPREADING_AMOUT_OFFSET		0 		// Offset in PLLCTL2 (9 bits)


/* CSDIS (Clock source disable) register offsets */
#define CLK_SRC_OSC_MASK			(1uL<<0u)
#define CLK_SRC_PLL1_MASK			(1uL<<1u)
#define CLK_SRC_LPO_MASK			(1uL<<4u)
#define CLK_SRC_HPO_MASK			(1uL<<5u)
#define CLK_SRC_PLL2_MASK			(1uL<<6u)

/* GLBSTAT */
#define GLBSTAT_OSCFAIL_MASK	    (1uL<<0u)
#define GLBSTAT_RFSLIP_MASK		    (1uL<<8u)
#define GLBSTAT_FBSLIP_MASK		    (1uL<<9u)

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(_x)  (sizeof(_x)/sizeof((_x)[0]))
#endif

#ifdef CFG_ARM_CR4
#define CORE_CPUID_CORTEX_R4   	0x0UL		/* This is not checked for the moment */
#elif defined(CFG_ARM_CR5)
#define CORE_CPUID_CORTEX_R5   	0x0UL		/* This is not checked for the moment */
#endif


#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
#define MSINENA_DCAN			((1uL << 5) | (1uL << 6) | (1uL << 10))
#elif defined(CFG_TMS570LC43X)
#define MSINENA_DCAN        	((1uL << 5) | (1uL << 6) | (1uL << 10) | (1uL << 20))
/* The SPI RAM is initialized by the SPI driver instead.
 * MSINENA_SPI				((1uL << 7) | (1uL << 18) | (1uL << 11) | (1uL << 19) | (1uL << 12))
 */
#else
#error MCU not defined.
#endif
#define MSINENA_HET_TU			((1uL << 4) | (1uL << 16))
#define MSINENA_N2HET			((1uL << 3) | (1uL << 15))
#define MSINENA_ADC				((1uL << 8) | (1uL << 14))
#define MSINENA_FLEXRAY_TU		(1uL << 13)
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
#define MSINENA_MASK			(MSINENA_DCAN | MSINENA_HET_TU | MSINENA_N2HET | MSINENA_ADC)
#elif defined(CFG_TMS570LC43X)
#define MSINENA_MASK			(MSINENA_DCAN | MSINENA_HET_TU | MSINENA_N2HET | MSINENA_ADC)
#endif
#define MINIDONE_MASK			0x100uL
#define MINIDONE_FINISHED		0x0uL
#define MEM_INIT_ENABLE_KEY		0xAuL
#define MEM_INIT_DISABLE_KEY	0x5uL

#define FRDCNTL_RWAIT_OFFSET	8uL
#define FRDCNTL_PFUENB_OFFSET	1uL
/* FRDCNTL_PFUENA_OFFSET = 0 */
#define FSM_WRITE_ENABLE		0x5uL
#define FSM_WRITE_DISABLE		0x0uL
#define EEPROM_CONFIG_REG_RWAIT_OFFSET	16u

/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/


typedef enum {
    GCLK,
    GCLK2,
    HCLK,
    VCLK,
    VCLK2,
    VCLK3,
    VCLK4,
    VCLKA1,
    VCLKA2,
    VCLKA4,
    VCLKA4_DIVR,
    RTICLK,
} InternalClockType;

/* ----------------------------[private function prototypes]-----------------*/

void Mcu_ConfigureFlash(const Mcu_ClockSettingConfigType *);
void _errata_CORTEXR4_66_(void);
void _errata_CORTEXR4_57_(void);

/* ----------------------------[private variables]---------------------------*/

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
/* Haven't found any ID accessable from memory.
 * There is the DBGMCU_IDCODE (0xe0042000) found in RM0041 but it
 * you can't read from that address..
 */
const cpu_info_t cpu_info_list[] = {
    {
    .name = "TMS570LS12",
    .pvr = 0,
    },
    {
    .name = NULL,
    }
};

/* The supported cores
 */
const core_info_t core_info_list[] = {
    {
    .name = "CORE_ARM_CORTEX_R4",
    .pvr = CORE_CPUID_CORTEX_R4,
    .info = "Max Freq: 180Mhz, Cache: NO",
    },
    {
    .name = NULL,
    }
};
#elif defined(CFG_TMS570LC43X)
const cpu_info_t cpu_info_list[] = {
    {
    .name = "TMS570LC43",
    .pvr = 0,
    },
    {
    .name = NULL,
    }

};

/* The supported cores
 */
const core_info_t core_info_list[] = {
    {
    .name = "CORE_ARM_CORTEX_R5",
    .pvr = CORE_CPUID_CORTEX_R5,
    .info = "Max Freq: 300Mhz, Cache: YES",
    },
    {
    .name = NULL,
    }
};
#else
#error Mcu driver not implemented for this tms570 version.
#endif

/* ----------------------------[private functions]---------------------------*/

/*
 * Identify the core, just to check that we have support for it.
 */
static uint32 Mcu_CheckCpu( void ) {
    return 0;
}

/*
 * Init peripheral memory. Will set all to 0 and calculate ECC things.
 */
static void initPeripheralMemory( uint32 mask ) {
    systemREG1->MINITGCR = MEM_INIT_ENABLE_KEY;
    systemREG1->MSINENA = mask;

    do {
        /* Wait until all is done */
    } while( (systemREG1->MSTCGSTAT & MINIDONE_MASK) == MINIDONE_FINISHED);

    systemREG1->MINITGCR = MEM_INIT_DISABLE_KEY;
}


#if  defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
/*
  * Initialize Peripherals clocks
  */
static void periphInit( void  )
{
    /* From Datasheet:
     * The clocks to a module must be turned off before powering down the
     * core domain that contains the module. */

    /* Write PENA bit to turn off the clocks to the peripherals */
    systemREG1->CLKCNTL &= 0xFFFFFEFFU;

    /* TI manual is not really clear what the PENA bit does, so turn off all clocks */
    pmmREG->PDCLKDISSET = 0x1f;

    /* From RM:
     * - 7 power domains in total: PD1, PD2, PD3, PD4, PD5, RAM_PD1, and RAM_PD2.
     * - There are 4 power registers, PSPWRDWNxxx, where there is 4 bits to describe
     *   each power domain. The PS[x]s are listed in Table 2-3. Sooo
     *   PSPWRDWNCLR0 0:3 is PS[0]  = MibSPI5
     *   PSPWRDWNCLR0 4:7 is PS[1]  = SPI4
     *   ..
     *   PSPWRDWNCLR1 0:3 is PS[8]  = DCAN1, DCAN2
     *   etc.
     * */

    /* Powerup all peripherals...how this is mapped is not known it seems */

    pcrREG->PSPWRDWNCLR0 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR1 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR2 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR3 = 0xFFFFFFFFU;

    /* Enable clocks again */
    pmmREG->PDCLKDISCLR = 0x1f;

    /* Set PENA bit again to enable clocks  */
    systemREG1->CLKCNTL |= 0x00000100U;
}
#endif /* CFG_TMS570LS12X */

//-------------------------------------------------------------------

static void GetAndClearResetCause(void) {
    Mcu_ResetType resetReason = MCU_RESET_UNDEFINED;

    uint32 status = systemREG1->SYSESR;

    /* Get RAW reset value and resetReson value and save it */
    Mcu_Global.rawResetvalue = status;

    if (status & 0x00008000UL) {
        resetReason = MCU_POWER_ON_RESET;
    } else if (status & 0x00004000UL) {
        resetReason = MCU_OSC_FAILURE_RESET;
    } else if (status & 0x00002000UL) {
        resetReason = MCU_WATCHDOG_RESET;
    } else if (status & 0x00000020UL) {
        resetReason = MCU_CPU_RESET;
    } else if (status & 0x00000010UL) {
        resetReason = MCU_SW_RESET;
    } else if (status & 0x00000008UL) {
        resetReason = MCU_EXT_RESET;
    } else {
        resetReason = MCU_RESET_UNDEFINED;
    }

    /* Clear */
    systemREG1->SYSESR = status;

    /* @req SWS_Mcu_00005 */
    Mcu_Global.resetReason = resetReason;
}

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
static void mapClocks( const Mcu_ClockSettingConfigType *clockSettingsPtr ) {
    uint32 SYS_CSVSTAT, SYS_CSDIS;

    /* CSDIS - Clock Source Disable Register
     * CDDIS - Clock Domain Disable Register
     * */

    systemREG1->CDDIS =   (0u<<11u)	/*  VCLKA4            */
                        | (0u<<10u)	/*  VCLKA3            */
                        | (0u<<9u)	/*  VCLK4 (etpwm,etc)     */
                        | (0u<<8u)	/*  VCLK3 (ethernet, etc) */	/* Must be on for PWM!!!!  */
                        | (0u<<7u)	/*  RTICLK2	          */
                        | (0u<<6u)	/*  RTICLK1			  */
                        | (1u<<5u)	/*  VCLKA2 (Flexray)  */
                        | (0u<<4u)	/*  VCLKA1 (DCAN)     */
                        | (0u<<3u)	/*  VCLK2 (NHET)   	  */
                        | (0u<<2u)	/*  VCLK_periph   	  */
                        | (0u<<1u)	/*  HCLK and VCLK_sys */
                        | (0u<<0u); 	/*  CPU 			  */


     /* Work Around for Errata SYS#46:
     *
     * Errata Description:
     *            Clock Source Switching Not Qualified with Clock Source Enable And Clock Source Valid
     * Workaround:
     *            Always check the CSDIS register to make sure the clock source is turned on and check
     * the CSVSTAT register to make sure the clock source is valid. Then write to GHVSRC to switch the clock.
     */

    /*  Wait for until ALL clocks are locked */
    SYS_CSVSTAT = systemREG1->CSVSTAT;
    SYS_CSDIS = systemREG1->CSDIS;
    while ((SYS_CSVSTAT & ((SYS_CSDIS ^ 0xFFU) & 0xFFU)) != ((SYS_CSDIS ^ 0xFFU) & 0xFFU)) {
        SYS_CSVSTAT = systemREG1->CSVSTAT;
        SYS_CSDIS = systemREG1->CSDIS;
    }


    /* Run PLL at full speed */
    systemREG1->PLLCTL1 = (systemREG1->PLLCTL1 & 0xE0FFFFFFU) | ((clockSettingsPtr->R - 1) << 24u);

    /* Enable/Disable Frequency modulation */
    systemREG1->PLLCTL2 |= 0x00000000U;

    /* - Setup GCLK, HCLK and VCLK clock source for normal operation, power down mode and after wakeup */
    systemREG1->GHVSRC = 			(SYS_OSC << 24u)
                         | ((uint32) SYS_OSC << 16U)
                         | ((uint32) SYS_PLL1 << 0U);

    /*  VCLK1, VCLK2 setup at half HCLK frequency */
    /* Must write VCLK2R first */
    systemREG1->CLKCNTL = (systemREG1->CLKCNTL & 0xF0FFFFFFU) | (uint32) ((uint32) 1U << 24U);  /* divide by 2 */
    /* Then VCLKR */
    systemREG1->CLKCNTL = (systemREG1->CLKCNTL & 0xFFF0FFFFU)| (uint32) ((uint32) 1U << 16U);	/* divide by 2 */

    /* VCLK3 and VCLK4 is HCLK / 2 */
    systemREG2->CLK2CNTRL = ((1<<8) | (1<<0)) ;

    /* - Setup RTICLK1 and RTICLK2 clocks */
    systemREG1->RCLKSRC  = (0U << 8U) 	// RTICLK1 divider is 1
                           |  SYS_VCLK; // Select VCLK as source for RTICLK1.

    /* - Setup asynchronous peripheral clock sources for AVCLK1 and AVCLK2 */
    /* OSCIN for VCLKA1 and VCLK for VCLKA2 */
    systemREG1->VCLKASRC = (SYS_VCLK << 8U)
                         |  0;
}

/*
 * Initialize Flash, PLL and clocks.
 */
static void InitPLL1(const Mcu_ClockSettingConfigType *clockSettingsPtr) {

    /* Check if already running the PLL, if so select OSC source for GCLK */
    if ( systemREG1->GHVSRC & 0xfuL) {
        /* Start over again, assign to oscillator */
        systemREG1->GHVSRC = 0;
    }

    /* Disable the PLL1 and PLL2 to set them up */
    systemREG1->CSDISSET = CLK_SRC_PLL1_MASK | CLK_SRC_PLL2_MASK;

    while ((systemREG1->CSDIS & (CLK_SRC_PLL1_MASK | CLK_SRC_PLL2_MASK)) != (CLK_SRC_PLL1_MASK | CLK_SRC_PLL2_MASK)) {
        /* Wait for lock */
    }

    /* Clear Global Status Register */
    systemREG1->GBLSTAT = (GLBSTAT_OSCFAIL_MASK | GLBSTAT_RFSLIP_MASK | GLBSTAT_FBSLIP_MASK);

    /*
     * Make sure we full fill table 10-1 from RM
     */

    /* Setup PLL1, use max divider for now */
    systemREG1->PLLCTL1 = 	  (MCU_RESET_ON_SLIP 	 << MCU_RESET_ON_SLIP_OFFSET)
                            | (MCU_BYPASS_ON_SLIP 	 << MCU_BYPASS_ON_SLIP_OFFSET)
                            | (MCU_RESET_ON_OSC_FAIL << MCU_RESET_ON_OSC_FAIL_OFFSET)
                            | (((clockSettingsPtr->NF - 1) * 256UL) << 0u) 		/* PLL_MULT */
                            | ((clockSettingsPtr->NR - 1) << 16u) 		/* REF_CLK_DIV */
                            | ((0x1f) << 24u); 				/* PLLDIV */

    /* ODPLL */
    systemREG1->PLLCTL2 = 	(systemREG1->PLLCTL2 & 0xfffff1ffU)
                            | (uint32) (((clockSettingsPtr->ODPLL - 1) << MCU_ODPLL_OFFSET));

    /* Enable the main PLL (PLL1) among others */
    systemREG1->CSDIS =    (1u<<7u)	/*  EXTCLKIN2 	    */
                         | (1u<<6u)	/*  PLL2 (FPLL) 	*/
                         | (0u<<5u)	/*  High Frequency LPO (Low Power Oscillator) clock */
                         | (0u<<4u)	/*  Low Frequency LPO (Low Power Oscillator) clock  */
                         | (1u<<3u)	/*  EXTCLKIN  			*/
                         | (1u<<2u)	/*  Not Implemented   	*/
                         | (0u<<1u)	/*  PLL1 (FMzPLL)  		*/
                         | (0u<<0u); 	/*  Oscillator 		*/
}

#endif /* CFG_TMS570LS12X */

#ifdef CFG_TMS570LC43X
void setupPLL(const Mcu_ClockSettingConfigType *clockSettingsPtr)
{
    /* Check if already running the PLL, if so select OSC source for GCLK */
    if ( systemREG1->GHVSRC & 0xfuL) {
        /* Start over again, assign to oscillator */
        systemREG1->GHVSRC = 0;
    }

    /* Disable PLL1 and PLL2 */
    systemREG1->CSDISSET = 0x00000002U | 0x00000040U;
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while((systemREG1->CSDIS & 0x42U) != 0x42U)
    {
    /* Wait */
    }

    /* Clear Global Status Register */
    systemREG1->GBLSTAT = 0x301U;

    /* - Configure PLL control registers */
    /*   - Setup pll control register 1:
    *     - Setup reset on oscillator slip
    *     - Setup bypass on pll slip
    *     - setup Pll output clock divider to max before Lock
    *     - Setup reset on oscillator fail
    *     - Setup reference clock divider
    *     - Setup Pll multiplier
    */
    systemREG1->PLLCTL1 = 	  (MCU_RESET_ON_SLIP 	 << MCU_RESET_ON_SLIP_OFFSET)
                            | (MCU_BYPASS_ON_SLIP 	 << MCU_BYPASS_ON_SLIP_OFFSET)
                            | (MCU_RESET_ON_OSC_FAIL << MCU_RESET_ON_OSC_FAIL_OFFSET)
                            | (((clockSettingsPtr->NF - 1) * 256UL) << 0u) 		/* PLL_MULT */
                            | ((clockSettingsPtr->NR - 1) << 16u) 		/* REF_CLK_DIV */
                            | ((0x1f) << 24u); 				/* PLLDIV */

    /*    - Setup pll control register 2
    *     - Setup spreading rate
    *     - Setup bandwidth adjustment
    *     - Setup internal Pll output divider
    *     - Setup spreading amount
    */
    systemREG1->PLLCTL2 =  (uint32)((uint32)255U << 22U)
                        |  (uint32)((uint32)7U << 12U)
                        |  (uint32)((uint32)(1U - 1U) << 9U)
                        |  (uint32)61U;

    /*    - Setup pll3 control register :
    *     - setup Pll output clock divider to max before Lock
    *     - Setup reference clock divider
    *     - Setup internal Pll output divider
    *     - Setup Pll multiplier
    */
    systemREG2->PLLCTL3 = (uint32)((uint32)(1U - 1U) << 29U)
                        | (uint32)((uint32)0x1FU << 24U)
                        | (uint32)((uint32)(8U - 1U)<< 16U)
                        | (uint32)((uint32)(150U - 1U) << 8U);

    /* - Enable PLL(s) to start up or Lock */
    systemREG1->CSDIS = 0x00000000U
                      | 0x00000000U
                      | 0x00000008U
                      | 0x00000080U
                      | 0x00000000U
                      | 0x00000000U
                      | 0x00000000U
                      | 0x00000004U;
}

void setupFlash(void)
{
    /* - Setup flash read mode, address wait states and data wait states */
    flashWREG->FRDCNTL =  0x00000000U
                       | (uint32)((uint32)3U << 8U)
                       |  3U;

    /* - Setup flash access wait states for bank 7 */
    FSM_WR_ENA_HL    = 0x5U;
    EEPROM_CONFIG_HL = 0x00000000U | (uint32)((uint32)9U << 16U) ;


    /* - Disable write access to flash state machine registers */
    FSM_WR_ENA_HL    = 0x2U;

    /* - Setup flash bank power modes */
    flashWREG->FBPWRMODE = 0x00000000U
                          | (uint32)((uint32)SYS_ACTIVE << 14U) /* BANK 7 */
                          | (uint32)((uint32)SYS_ACTIVE << 2U)  /* BANK 1 */
                          | (uint32)((uint32)SYS_ACTIVE << 0U); /* BANK 0 */
}

void periphInit(void)
{
    /* - Disable Peripherals before peripheral powerup*/
    systemREG1->CLKCNTL &= 0xFFFFFEFFU;

    /* - Release peripherals from reset and enable clocks to all peripherals */
    /* - Power-up all peripherals */
    pcrREG1->PSPWRDWNCLR0 = 0xFFFFFFFFU;
    pcrREG1->PSPWRDWNCLR1 = 0xFFFFFFFFU;
    pcrREG1->PSPWRDWNCLR2 = 0xFFFFFFFFU;
    pcrREG1->PSPWRDWNCLR3 = 0xFFFFFFFFU;

    pcrREG2->PSPWRDWNCLR0 = 0xFFFFFFFFU;
    pcrREG2->PSPWRDWNCLR1 = 0xFFFFFFFFU;
    pcrREG2->PSPWRDWNCLR2 = 0xFFFFFFFFU;
    pcrREG2->PSPWRDWNCLR3 = 0xFFFFFFFFU;

    pcrREG3->PSPWRDWNCLR0 = 0xFFFFFFFFU;
    pcrREG3->PSPWRDWNCLR1 = 0xFFFFFFFFU;
    pcrREG3->PSPWRDWNCLR2 = 0xFFFFFFFFU;
    pcrREG3->PSPWRDWNCLR3 = 0xFFFFFFFFU;

    /* - Enable Peripherals */
    systemREG1->CLKCNTL |= 0x00000100U;
}

void mapClocks(const Mcu_ClockSettingConfigType *clockSettingsPtr)
{
    uint32 SYS_CSVSTAT, SYS_CSDIS;
    /* - Setup system clock divider for HCLK */
    systemREG2->HCLKCNTL = 1U;

    /* - Disable / Enable clock domain */
    systemREG1->CDDIS = (uint32)((uint32)0U << 4U ) /* AVCLK 1 OFF */
                      | (uint32)((uint32)1U << 5U ) /* AVCLK 2 OFF */
                      | (uint32)((uint32)0U << 8U ) /* VCLK3 OFF */
                      | (uint32)((uint32)0U << 9U ) /* VCLK4 OFF */
                      | (uint32)((uint32)0U << 10U) /* AVCLK 3 OFF */
                      | (uint32)((uint32)0U << 11U); /* AVCLK 4 OFF */

    /* Always check the CSDIS register to make sure the clock source is turned on and check
     * the CSVSTAT register to make sure the clock source is valid. Then write to GHVSRC to switch the clock.
     */
    /* - Wait for until clocks are locked */
    SYS_CSVSTAT = systemREG1->CSVSTAT;
    SYS_CSDIS = systemREG1->CSDIS;
    while ((SYS_CSVSTAT & ((SYS_CSDIS ^ 0xFFU) & 0xFFU)) != ((SYS_CSDIS ^ 0xFFU) & 0xFFU))
    {
        SYS_CSVSTAT = systemREG1->CSVSTAT;
        SYS_CSDIS = systemREG1->CSDIS;
    } /* Wait */

    /* Now the PLLs are locked and the PLL outputs can be sped up */
    /* The R-divider was programmed to be 0xF. Now this divider is changed to programmed value */
    systemREG1->PLLCTL1 = (systemREG1->PLLCTL1 & 0xE0FFFFFFU) | (uint32)((uint32)(clockSettingsPtr->R - 1U) << 24U);
    /*SAFETYMCUSW 134 S MR:12.2 <APPROVED> " Clear and write to the volatile register " */
    systemREG2->PLLCTL3 = (systemREG2->PLLCTL3 & 0xE0FFFFFFU) | (uint32)((uint32)(1U - 1U) << 24U);

    /* Enable/Disable Frequency modulation */
    systemREG1->PLLCTL2 |= 0x00000000U;

    /* - Setup GCLK, HCLK and VCLK clock source for normal operation, power down mode and after wakeup */
    systemREG1->GHVSRC = (uint32)((uint32)SYS_PLL1 << 24U)
                       | (uint32)((uint32)SYS_PLL1 << 16U)
                       | (uint32)((uint32)SYS_PLL1 << 0U);

    /* - Setup synchronous peripheral clock dividers for VCLK1, VCLK2, VCLK3 */
    systemREG1->CLKCNTL  = (systemREG1->CLKCNTL & 0xF0FFFFFFU)
                         | (uint32)((uint32)1U << 24U);
    systemREG1->CLKCNTL  = (systemREG1->CLKCNTL & 0xFFF0FFFFU)
                         | (uint32)((uint32)1U << 16U);
    systemREG2->CLK2CNTRL = (systemREG2->CLK2CNTRL & 0xFFFFFFF0U)
                         | (uint32)((uint32)1U << 0U);

    /* - Setup RTICLK1 and RTICLK2 clocks */
    systemREG1->RCLKSRC = (uint32)((uint32)1U << 24U)        /* RTI2 divider (Not applicable for lock-step device)  */
                        | (uint32)((uint32)SYS_VCLK << 16U) /* RTI2 clock source (Not applicable for lock-step device) */
                        | (uint32)((uint32)1U << 8U)         /* RTI1 divider */
                        | (uint32)((uint32)SYS_VCLK << 0U); /* RTI1 clock source */

    /* - Setup asynchronous peripheral clock sources for AVCLK1 and AVCLK2 */
    systemREG1->VCLKASRC = (uint32)((uint32)SYS_VCLK << 8U)
                         | (uint32)((uint32)SYS_OSC  << 0U);

    systemREG2->VCLKACON1 =  (uint32)((uint32)(1U - 1U) << 24U)
                           | (uint32)((uint32)0U << 20U)
                           | (uint32)((uint32)SYS_VCLK << 16U)
                           | (uint32)((uint32)(1U - 1U) << 8U)
                           | (uint32)((uint32)0U << 4U)
                           | (uint32)((uint32)SYS_VCLK << 0U);
}
#endif /* CFG_TMS570LC43X */

//-------------------------------------------------------------------

void Mcu_Hw_Init(const Mcu_ConfigType *configPtr)
{

    GetAndClearResetCause();

#if !defined(USE_SIMULATOR)
    Mcu_CheckCpu();
#endif
}

//-------------------------------------------------------------------

Std_ReturnType Mcu_Hw_InitClock(const Mcu_ClockSettingConfigType *clockSettingsPtr)
{

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
    InitPLL1(clockSettingsPtr);
    /* Power Up Peripherals (clocks to module must be turned off) */
    periphInit();

    Mcu_ConfigureFlash(clockSettingsPtr);

    /* */
    mapClocks(clockSettingsPtr);

    /* IMPROVEMENT: For safety run PBIST */
    initPeripheralMemory(MSINENA_MASK);

#elif defined(CFG_TMS570LC43X)

    /* Configure PLL control registers and enable PLLs.
     * The PLL takes (127 + 1024 * NR) oscillator cycles to acquire lock.
     * This initialization sequence performs all the tasks that are not
     * required to be done at full application speed while the PLL locks.
     */
    setupPLL(clockSettingsPtr);

    /* Enable clocks to peripherals and release peripheral reset */
    periphInit();

    /* - Set up flash address and data wait states based on the target CPU clock frequency */
    Mcu_ConfigureFlash(clockSettingsPtr);

    /* - Wait for PLLs to start up and map clock domains to desired clock sources */
    mapClocks(clockSettingsPtr);

    initPeripheralMemory(MSINENA_MASK);

#else
#error Mcu driver not implemented for this tms570 version.
#endif

    return E_OK;
}


//-------------------------------------------------------------------

Std_ReturnType Mcu_Hw_DistributePllClock(void)
{
    return E_OK;
}

//-------------------------------------------------------------------


Mcu_PllStatusType Mcu_Hw_GetPllStatus(void) {

    /* @req SWS_Mcu_00008, The function Mcu_GetPllStatus shall return the lock status of the PLL*/

    if ((systemREG1->CSVSTAT & ((systemREG1->CSDIS ^ 0xFF) & 0xFF)) != ((systemREG1->CSDIS ^ 0xFF) & 0xFF)) {
        return MCU_PLL_UNLOCKED;
    }

    return MCU_PLL_LOCKED;
}

//-------------------------------------------------------------------

#if ( MCU_PERFORM_RESET_API == STD_ON )
/*
 * Shell perform a microcontroller reset by using the hardware feature
 * of the micro controller.
 */
void Mcu_Hw_PerformReset(void)
{
    /* @req SWS_Mcu_00143 */
    /* !req SWS_Mcu_00144 */
    systemREG1->SYSECR = 0x00008000;
}
#endif

//-------------------------------------------------------------------

void Mcu_Hw_SetMode(const Mcu_ModeType McuMode)
{
  /* NOT SUPPORTED */
}

//-------------------------------------------------------------------

/*
 * Get the system clock in Hz. It calculates the clock from the
 * different register settings in HW.
 *
 * The system clock in this case is assumed to be GCLK (Cortex Speed)
 *
 */
uint32 Mcu_Arc_GetSystemClock(void)
{
  uint32_t f_sys;

  // PLLCLK = (CLKIN * PLLMUL) / (REFCLKDIV * ODPLL * PLLDIV);

  uint32 odpll = ((systemREG1->PLLCTL2 & MCU_ODPLL_MASK) >> MCU_ODPLL_OFFSET) + 1;
  uint32 plldiv = ((systemREG1->PLLCTL1 & MCU_PLLDIV_MASK) >> MCU_PLLDIV_OFFSET) + 1;
  uint32 refclkdiv = ((systemREG1->PLLCTL1 & MCU_REFCLKDIV_MASK) >> MCU_REFCLKDIV_OFFSET) + 1;
  uint32 pllmult = (((systemREG1->PLLCTL1 & MCU_PLLMUL_MASK) >> MCU_PLLMUL_OFFSET) / 256) + 1;

  f_sys = Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting].McuClockReferencePointFrequency;
  f_sys = f_sys * pllmult / (refclkdiv * odpll * plldiv);

  return f_sys;
}


uint32 getClockSource( enum systemClockSource clockSource) {
    uint32 clock = 0;
    uint32 divider = 1;

    switch(clockSource) {
    case SYS_OSC:
        clock = Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting].McuClockReferencePointFrequency;
        break;
    case SYS_PLL1:
        clock = Mcu_Arc_GetSystemClock();
        break;
//	case SYS_O32:
    case SYS_EXTERNAL1:
    case SYS_LPO_LOW:
    case SYS_LPO_HIGH:
//	case SYS_FR_PLL:
        /* NOT SUPPORTED */
        break;
    case SYS_VCLK:
        divider = ((systemREG1->CLKCNTL >> 16u) & 0xfu) + 1uL;
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
        clock = Mcu_Arc_GetSystemClock();
#elif defined(CFG_TMS570LC43X)
        clock = Mcu_Arc_GetSystemClock() / 2;
#else
#error Mcu driver not implemented for this tms570 version.
#endif
        break;
    default:
        break;
    }

    return clock / divider;
}

/**
 * Get the peripheral clock in Hz for a specific device
 */
uint32 getInternalClock(InternalClockType type) {

    uint32 clock = 0uL;
    uint32 divider = 1uL;
    enum systemClockSource clockSource;

    switch(type) {
    case GCLK:
        clock = Mcu_Arc_GetSystemClock();
        break;
    case GCLK2:
        clock = Mcu_Arc_GetSystemClock();
        break;
    case HCLK:
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
        clock = Mcu_Arc_GetSystemClock();
#elif defined(CFG_TMS570LC43X)
        clock = Mcu_Arc_GetSystemClock() / 2;
#else
#error Mcu driver not implemented for this tms570 version.
#endif
        break;
    case VCLK:
        /* default supply clock to peripherals */
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
        clock = Mcu_Arc_GetSystemClock();
#elif defined(CFG_TMS570LC43X)
        clock = Mcu_Arc_GetSystemClock() / 2;
#else
#error Mcu driver not implemented for this tms570 version.
#endif
        /* VCLKR,  default=1 (ie divide by 2)  */
        divider = ((systemREG1->CLKCNTL >> 16u) & 0xfu) + 1uL;
        break;
    case VCLK2:
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
        clock = Mcu_Arc_GetSystemClock();
#elif defined(CFG_TMS570LC43X)
        clock = Mcu_Arc_GetSystemClock() / 2;
#else
#error Mcu driver not implemented for this tms570 version.
#endif
        /* VCLKR2, default=1 (ie divide by 2)  */
        divider = ((systemREG1->CLKCNTL >> 24u) & 0xfu) + 1uL;
        break;
    case VCLK3:
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
        clock = Mcu_Arc_GetSystemClock();
#elif defined(CFG_TMS570LC43X)
        clock = Mcu_Arc_GetSystemClock() / 2;
#else
#error Mcu driver not implemented for this tms570 version.
#endif
        /* VCLK3R, default=1 (ie divide by 2)  */
        divider = ((systemREG2->CLK2CNTRL) & 0xfu) + 1uL;
        break;
    case VCLK4:
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
        clock = Mcu_Arc_GetSystemClock();
#elif defined(CFG_TMS570LC43X)
        clock = Mcu_Arc_GetSystemClock() / 2;
#else
#error Mcu driver not implemented for this tms570 version.
#endif
        /* VCLK4R, default=1 (ie divide by 2)  */
        divider = ((systemREG2->CLK2CNTRL >> 8u) & 0xfu) + 1uL;
        break;
    case VCLKA1:
        /* CAN Controllers */
        clockSource = systemREG1->VCLKASRC & 0xfu;
        clock = getClockSource(clockSource);
        /* No divider */
        break;
    case VCLKA2:
        /* Flexray */
        clockSource = (systemREG1->VCLKASRC>>8u) & 0xfu;
        clock = getClockSource(clockSource);
        /* No divider */
        break;
    case VCLKA4:
        break;
    case VCLKA4_DIVR:
        break;
    case RTICLK:
        clockSource = (systemREG1->VCLKASRC>>8u) & 0xfu;
        clock = getClockSource(clockSource);
        if( clockSource != SYS_VCLK ) {
            divider = (1uL << ((systemREG1->RCLKSRC >> 8u) & 0x3u));
        }
        break;
    default:
        /*IMPROVMENT: Add Det error */
        break;
    }

    return clock/divider;
}

/**
 * Get the peripheral clock in Hz for a specific device
 */
uint32 Mcu_Arc_GetPeripheralClock(Mcu_Arc_PeriperalClock_t type) {

    uint32 clockInHz = 0uL;

    switch (type) {

    case PERIPHERAL_CLOCK_CAN:
        clockInHz = getInternalClock(VCLKA1);
        break;

    case PERIPHERAL_CLOCK_RTICLK:
    case PERIPHERAL_CLOCK_WDG:
        clockInHz = getInternalClock(RTICLK);
        break;

    case PERIPHERAL_CLOCK_FLASH:
        clockInHz = getInternalClock(HCLK);
        break;

    case PERIPHERAL_CLOCK_PWM:
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
        clockInHz = getInternalClock(VCLK4);
#elif defined(CFG_TMS570LC43X)
        clockInHz = getInternalClock(VCLK3);
#else
#error Mcu driver not implemented for this tms570 version.
#endif
        break;

    default:
        /*IMPROVMENT: Add Det error */
        break;
    }

    return clockInHz;
}


/**
 * Function to setup the internal flash for optimal performance
 */
void Mcu_ConfigureFlash(const Mcu_ClockSettingConfigType *clockSettingsPtr)
{
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
    uint32 readWaitStates = 3uL;
    (void)clockSettingsPtr;
    /* Enable pipeline reads from flash
     * ZWT:
     *   - 180Mhz, Flash
     * PGE:
     *   - 160Mhz, Flash
     * */

    flashREG->FRDCNTL = (readWaitStates<<8) +	/* Read wait states    */
                        (1<<4) + 	            /* Address wait states */
                        (1<<0);		            /* Enable pipeline mode */

    /* Enable write to EEPROM_CONFIG_REG */
    FSM_WR_ENA_REG = 0x5uL;

    /* From RM: The same formulas that apply to RWAIT will apply to EWAIT in the EEPROM bank.
     * Write EWAIT , leave rest as on reset*/
    EEPROM_CONFIG_REG = 0x00000002uL | (readWaitStates << 16u) ;

    FSM_WR_ENA_REG = 0x0uL;

#elif defined(CFG_TMS570LC43X)
    uint32 readWaitStates;
    uint32 readWaitStatesEEPROM;

    //uint32 clock = getInternalClock(HCLK); Not used since PLL not correctly set up at this point.
    uint32 clock = ((clockSettingsPtr->McuClockReferencePointFrequency)*(clockSettingsPtr->NF))/((clockSettingsPtr->NR)*(clockSettingsPtr->ODPLL)*(clockSettingsPtr->R));
    clock /= 2; // GCLK/2 = HCLK
    clock /= 1000000; // More managable number.

    if (clock <= 15)
    {
        readWaitStates = 0;
        readWaitStatesEEPROM = 0;
    }
    else if (clock <= 30)
    {
        readWaitStates = 0;
        readWaitStatesEEPROM = 1;
    }
    else if (clock <= 45)
    {
        readWaitStates = 0;
        readWaitStatesEEPROM = 2;
    }
    else if (clock <= 60)
    {
        readWaitStates = 1;
        readWaitStatesEEPROM = 3;
    }
    else if (clock <= 75)
    {
        readWaitStates = 1;
        readWaitStatesEEPROM = 4;
    }
    else if (clock <= 90)
    {
        readWaitStates = 1;
        readWaitStatesEEPROM = 5;
    }
    else if (clock <= 105)
    {
        readWaitStates = 2;
        readWaitStatesEEPROM = 6;
    }
    else if (clock <= 120)
    {
        readWaitStates = 2;
        readWaitStatesEEPROM = 7;
    }
    else if (clock <= 135)
    {
        readWaitStates = 2;
        readWaitStatesEEPROM = 8;
    }
    else // (clock <= 150) 150MHz
    {
        readWaitStates = 3;
        readWaitStatesEEPROM = 9;
    }

    /* Address wait state is fixed to 1 HCLK cycle so cannot be set. */
    flashWREG->FRDCNTL = (readWaitStates << FRDCNTL_RWAIT_OFFSET) +
                        (1uL << FRDCNTL_PFUENB_OFFSET) +   /* Enable prefetch mode for PortB. */
                        1uL;    /* Enable prefetch mode for PortA. */

    /* Enable write to EEPROM_CONFIG_REG */
    FSM_WR_ENA_REG = FSM_WRITE_ENABLE;
    EEPROM_CONFIG_REG = (readWaitStatesEEPROM << EEPROM_CONFIG_REG_RWAIT_OFFSET);
    FSM_WR_ENA_REG = FSM_WRITE_DISABLE;

    flashWREG->FBPWRMODE = 0x00000000U
                          | (uint32)((uint32)SYS_ACTIVE << 14U) /* BANK 7 */
                          | (uint32)((uint32)SYS_ACTIVE << 2U)  /* BANK 1 */
                          | (uint32)((uint32)SYS_ACTIVE << 0U); /* BANK 0 */
#else
#error Mcu driver not implemented for this tms570 version.
#endif
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

    /* Correct chip errata's. Call TI prepared functions */
    if (systemREG1->SYSESR & 0x00008000UL) {

#if defined(CFG_ARM_CR4)
        /* Workaround for Errata CORTEXR4 66 */
        _errata_CORTEXR4_66_();

        /* Workaround for Errata CORTEXR4 57 */
        _errata_CORTEXR4_57_();
#endif

    }


#if defined(USE_KERNEL)
    Irq_Init();
#endif
}
