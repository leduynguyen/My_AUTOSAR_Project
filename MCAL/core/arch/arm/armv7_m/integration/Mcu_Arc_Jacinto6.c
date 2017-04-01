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

/* ----------------------------[information]----------------------------------*/
/*
 * Author: jcar
 *
 * Description:
 *
 */
/** @tagSettings DEFAULT_ARCHITECTURE=JACINTO5|JACINTO6 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */


/* ----------------------------[includes]------------------------------------*/


#include "Std_Types.h"
#include "Mcu.h"
#include "io.h"
#include "Mcu_Arc.h"
#include "irq.h"
#include "irq_types.h"
#include "io.h"
#if defined(USE_KERNEL)
#include "Os.h"
#endif

/* ----------------------------[private define]------------------------------*/
#define CM3_MMU_CFG				           (0x55080000U)

#define MMU_INIT_CFG							(0x55080000U)

// #define DEBUG   1
#if defined(DEBUG)
#define DEBUG_PRINTF(format,...)                    printf(format,## __VA_ARGS__ );
#else
#define DEBUG_PRINTF(format,...)
#endif


#define CORE_CPUID_CORTEX_M4_TI     0x410FC241UL


/* UNICACHE */
#define CACHE_CONFIG 		(MMU_INIT_CFG+0x004UL)
#define CACHE_MAINT			(MMU_INIT_CFG+0x010UL)
#define CACHE_MTSTART		(MMU_INIT_CFG+0x014UL)
#define CACHE_MTEND			(MMU_INIT_CFG+0x018UL)


/* UNICACHE_MMU */
#define CACHE_MMU_MAINT		(MMU_INIT_CFG+0xCA8UL)
#define CACHE_MMU_MTSTART	(MMU_INIT_CFG+0xCACUL)
#define CACHE_MMU_MTEND		(MMU_INIT_CFG+0xCB0UL)
#define CACHE_MMU_MAINTST	(MMU_INIT_CFG+0xCB4UL)
#define CACHE_MMU_MTCONFIG	(MMU_INIT_CFG+0xCB8UL)


#define CTRL_MODULE_CORE                   (0x4A002000U + L3_OFFSET)
#define	CTRL_CORE_MMR_LOCK_1               (0x00000540U)
#define	CTRL_CORE_MMR_LOCK_2               (0x00000544U)
#define CTRL_CORE_MMR_LOCK_5               (0x00000550U)
#define MMR_LOCK_1                         (0x1A1C8144U)
#define MMR_UNLOCK_1                       (0x2FF1AC2BU)
#define MMR_LOCK_2                         (0xFDF45530U)
#define MMR_UNLOCK_2                       (0xF757FDC0U)
#define MMR_LOCK_5                         (0x143F832CU)
#define MMR_UNLOCK_5                       (0x6F361E05U)
#define CTRL_CORE_SMA_SW_6                 (0x4A003C14U + L3_OFFSET)
#define RMII_CLK_SETTING_MASK              (0x00000100U)

#define CM_IPU_CLKSTCTRL                    (0x4A005540UL + L3_OFFSET)

#define CM_WKUPAON_TIMER1_CLKCTRL	       (0x4AE07840U + L3_OFFSET)
#define CM_L4PER_TIMER2_CLKCTRL		       (0x4A009738U + L3_OFFSET)
#define CM_L4PER_TIMER3_CLKCTRL		       (0x4A009740U + L3_OFFSET)
#define CM_L4PER_TIMER4_CLKCTRL		       (0x4A009748U + L3_OFFSET)
#define CM_IPU_TIMER5_CLKCTRL		       (0x4A005558U + L3_OFFSET)
#define CM_IPU_TIMER6_CLKCTRL		       (0x4A005560U + L3_OFFSET)
#define CM_IPU_TIMER7_CLKCTRL		       (0x4A005568U + L3_OFFSET)
#define CM_IPU_TIMER8_CLKCTRL		       (0x4A005570U + L3_OFFSET)
#define CM_L4PER_TIMER9_CLKCTRL		       (0x4A009750U + L3_OFFSET)
#define CM_L4PER_TIMER10_CLKCTRL	       (0x4A009728U + L3_OFFSET)
#define CM_L4PER_TIMER11_CLKCTRL	       (0x4A009730U + L3_OFFSET)
#define CM_WKUPAON_TIMER12_CLKCTRL	       (0x4AE07848U + L3_OFFSET)
#define CM_L4PER3_TIMER13_CLKCTRL	       (0x4A0097C8U + L3_OFFSET)
#define CM_L4PER3_TIMER14_CLKCTRL	       (0x4A0097D0U + L3_OFFSET)
#define CM_L4PER3_TIMER15_CLKCTRL	       (0x4A0097D8U + L3_OFFSET)
#define CM_L4PER3_TIMER16_CLKCTRL	       (0x4A009830U + L3_OFFSET)
#define CM_L4PER_MCSPI1_CLKCTRL			   (0x4A0097F0U + L3_OFFSET)
#define CM_L4PER_MCSPI2_CLKCTRL			   (0x4A0097F8U + L3_OFFSET)
#define CM_L4PER_MCSPI3_CLKCTRL			   (0x4A009800U + L3_OFFSET)
#define CM_L4PER_MCSPI4_CLKCTRL			   (0x4A009808U + L3_OFFSET)
#define CTRL_CORE_IPU1_IRQ_23_24           (0x4A0027E0U + L3_OFFSET)
#define CTRL_CORE_IPU2_IRQ_23_24           (0x4A002854U + L3_OFFSET)
#define NUM_BENELLI_IPU_XBAR_INST		   (57)
#define CTRL_CORE_IRQ_MASK                 (0x000001FFU)
#define LSB_WORD_MASK             	       (0x0000FFFFU)
#define MSB_WORD_MASK 				       (0xFFFF0000U)
#define TIM_CLKSEL_RST				       (0x00000000U)

#define TIM_MODULEMODE_ENABLED             2u
/* CLKSEL = 1 => 32kHz clock.
 * CLKSEL = 0 => TIMER_SYS_CLK (20MHz) clock.
 * TIM_CLKSEL: CLKSEL = 0, IDLEST = 0, MODULEMODE = 0x2
 */
#define TIM_CLKSEL                         TIM_MODULEMODE_ENABLED

/****************   GMAC SW specific ************************/

#define RMII_CLK_SEL_INT_DPLL_GMAC         (0x0u) /* Internal */
#define RMII_CLK_SEL_EXT_RMII_MHZ_50_CLK   (0x1u) /* External */

#define CM_GMAC_GMAC_CLKCTRL               (0x4A0093D0U + L3_OFFSET)
#define MODULE_MODE_DISABLED               (0u)
#define MODULEMODE_AUTO                    (1u)
#define MODULEMODE_ENABLED                 (2u)
#define MODULEMODE_MASK                    (3u)
#define	CLKSEL_REF_MASK                    (0x01000000U)
#define	SEL_GMAC_RMII_HS_CLK               (0x0u) /* Internal */
#define	SEL_GMAC_RMII_CLK                  (0x1u) /* External */

#define	CM_GMAC_CLKSTCTRL                  (0x4A0093C0U + L3_OFFSET)
#define CLKTRCTRL_MASK                     (0x00000003U)
#define CLKTRCTRL_NO_SLEEP                 (0u)
#define CLKTRCTRL_SW_SLEEP                 (1u)
#define CLKTRCTRL_HW_AUTO                  (3u)
#define CLKTRCTRL_SW_WKUP                  (2u)
#define	CM_L4CFG_CLKSTCTRL                 (0x4A008D00U + L3_OFFSET)

#define M4_CORE0_INTC						(0xE000E000)
#define M4_NVIC_ISER0						(0xE000E100)
#define M4_NVIC_ICER0						(0xE000E180)

#define CM_ALWON_DCAN1_CLKCTRL             (0x4AE07888U+L3_OFFSET)
#define CM_L4PER2_DCAN2_CLKCTRL            (0x4a0098f0U+L3_OFFSET)
#define CM_L4PER_I2C1_CLKCTRL              (0x4A0097A0U+L3_OFFSET)
#define CM_L4PER_I2C2_CLKCTRL              (0x4A0097A8U+L3_OFFSET)
#define CM_L4PER_I2C3_CLKCTRL              (0x4A0097B0U+L3_OFFSET)
#define CM_L4PER_I2C4_CLKCTRL              (0x4A0097B8U+L3_OFFSET)

/* ePWM clocks */
#define CM_L4PER2_PWMSS1_CLKCTRL			(0x4A0097C4uL + L3_OFFSET)
#define CM_L4PER2_PWMSS2_CLKCTRL			(0x4A009790uL + L3_OFFSET)
#define CM_L4PER2_PWMSS3_CLKCTRL			(0x4A009798uL + L3_OFFSET)
#define CTRL_CORE_CONTROL_IO_2				(0x4A002558uL + L3_OFFSET)
/* The manual is contradictory regarding these bits.
 * Using manual SPRUHI2T–November 2012–Revised September 2014.
 * On page 5501 describing the CTRL_CORE_CONTROL_IO_2 register
 * PWMSS1_TBCLKEN is bit 20 but on page 8047-8048 it says
 * PWMSS1 ePWM -> CTRL_CORE_CONTROL_IO_2[22] PWMSS3_TBCLKEN bit.
 * It does not matter though since we enable all of them anyway. */
#define PWMSS1_TBCLKEN						(1uL << 20uL)
#define PWMSS2_TBCLKEN						(1uL << 21uL)
#define PWMSS3_TBCLKEN						(1uL << 22uL)
#define PWMSS_1_2_3_TBCLKEN					(PWMSS1_TBCLKEN | PWMSS2_TBCLKEN | PWMSS3_TBCLKEN)


/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

const uint32_t TimeClkSel[] = {
    0,                          // Not used
    CM_WKUPAON_TIMER1_CLKCTRL,
    CM_L4PER_TIMER2_CLKCTRL,
    CM_L4PER_TIMER3_CLKCTRL,
    CM_L4PER_TIMER4_CLKCTRL,
    CM_IPU_TIMER5_CLKCTRL,
    CM_IPU_TIMER6_CLKCTRL,
    CM_IPU_TIMER7_CLKCTRL,
    CM_IPU_TIMER8_CLKCTRL,
    CM_L4PER_TIMER9_CLKCTRL,
    CM_L4PER_TIMER10_CLKCTRL,
    CM_L4PER_TIMER11_CLKCTRL,
    0,
    CM_L4PER3_TIMER13_CLKCTRL,
    CM_L4PER3_TIMER14_CLKCTRL,
    CM_L4PER3_TIMER15_CLKCTRL,
    CM_L4PER3_TIMER16_CLKCTRL,
};

const uint32_t GpioClkSel[] = {
    0,                          // Not used
    0x4AE07838UL + L3_OFFSET,   /* GPIO1 */
    0x4a009760UL + L3_OFFSET,   /* GPIO2 */
    0x4a009768UL + L3_OFFSET,   /* GPIO3 */
    0x4a009770UL + L3_OFFSET,   /* GPIO4 */
    0x4a009778UL + L3_OFFSET,   /* GPIO5 */
    0x4a009780UL + L3_OFFSET,   /* GPIO6 */
    0x4a009810UL + L3_OFFSET,   /* GPIO7 */
    0x4a009818UL + L3_OFFSET,   /* GPIO8 */
};

const cpu_info_t cpu_info_list[] = {
    {
    .name = "Jacinto6",
    .pvr = 0,
    .info = "",
    },
    {
    .name = NULL,
    }
};

/* The supported cores
 */
const core_info_t core_info_list[] = {
    {
    .name = "Cortex M4",
    .pvr = CORE_CPUID_CORTEX_M4_TI,
    .info = "Max Freq: 212Mhz, Cache: 32KiB",
    },
    {
    .name = NULL,
    }
};

/* ----------------------------[private functions]---------------------------*/

/**
 * Connect mux_irq (peripheral) to NVIC irq.
 *
 * @param irq		The NVIC interrupt vector
 * @param mux_irq   One of the 420 muxed interrupt sources
 */
void WriteIrqMux( uint32_t irq, uint32_t mux_irq ) {

    /* The MUX:ed IRQ starts at 7 */
    uint32 addr = (CTRL_CORE_IPU1_IRQ_23_24 + (((irq - 7UL)*2UL)&(~3UL)));

    /* Two entries for each 32-bit entry */
    if( (irq & 0x1UL) == 0UL  ) {
        /* even */
        WRITE32(addr, (mux_irq  << 16) | (READ32(addr) & LSB_WORD_MASK));
    } else {
        /* odd */
        WRITE32(addr, mux_irq | (READ32(addr) & MSB_WORD_MASK));
    }
}

/**
 * Enable the clocks for a timer.
 *
 * @param timer
 */

void EnableClocks_Timer( uint32_t timer ) {

    DEBUG_PRINTF("Timer Clock Init %d (addr=0x%08x,val=0x%08x)\n",timer,TimeClkSel[timer],READ32(TimeClkSel[timer]));

    /* Check if already up and running */
    if ( (READ32(TimeClkSel[timer]) & 0x00030003UL) != 2UL ) {
        /* Fix for ERRATA_I874, set to SW_WKUP */
        DEBUG_PRINTF("CM_IPU_CLKSTCTRL=0x%08x\n",READ32(CM_IPU_CLKSTCTRL));
        WRITE32(CM_IPU_CLKSTCTRL, 0x2 );
        
          /* Enable module  */
        WRITE32(TimeClkSel[timer],2UL);

        DEBUG_PRINTF("  Enabling %d\n",timer);
        while ((READ32(TimeClkSel[timer]) & 0x00030000UL) != 0UL ) {}
    }
}


void EnableClocks_Gpio( uint32_t unit ) {

    DEBUG_PRINTF("Timer Clock Init %d (addr=0x%08x,val=0x%08x)\n",timer,TimeClkSel[timer],READ32(TimeClkSel[timer]));

    /* Check if already up and running */
    if ( (READ32(GpioClkSel[unit]) & 0x00030103UL) != 0x101UL ) {

        WRITE32(GpioClkSel[unit],0x00000101UL);    /* Enable module  */

        DEBUG_PRINTF("  Enabling %d\n",timer);
        while ((READ32(GpioClkSel[unit]) & 0x00030000UL) == 0x00030000UL ) {}
    }
}


#if defined(CFG_MCU_MMU)

#if defined(CFG_BRD_JAC6_VAYU_EVM) && !defined(CFG_JAC6_IPC)
#include "rsc_table_vayu_ipu.h"
#endif

#if defined(CFG_BRD_JAC6_VAYU_EVM)

void Cache_InvRange( void *ptr, uint32_t byteCnt, uint32_t type) {
    WRITE32(CACHE_MTSTART, (uint32_t)ptr);
    WRITE32(CACHE_MTEND,  (uint32_t)((uint8_t *)ptr + byteCnt));
    __asm volatile("dmb");

    /* Perform operation */
    WRITE32(CACHE_MAINT,
            (0UL<<5U) |    // INTERRUPT
            (1UL<<4U) |    // INVALIDATE
            (0UL<<3U) |    // CLEAN
            (0UL<<2U) |    // UNLOCK
            (0UL<<1U) |    // LOCK
            (0UL<<0U) );   // PRELOAD

    __asm volatile("dmb");

    while( READ32(CACHE_MTEND)!= 0x0 ) {};
}


void Cache_CleanRange( void *ptr, uint32_t byteCnt, uint32_t type) {
    WRITE32(CACHE_MTSTART, (uint32_t)ptr);
    WRITE32(CACHE_MTEND,  (uint32_t)((uint8_t *)ptr + byteCnt));
    __asm volatile("dmb");

    /* Perform operation */
    WRITE32(CACHE_MAINT,
            (0UL<<5U) |    // INTERRUPT
            (0UL<<4U) |    // INVALIDATE
            (1UL<<3U) |    // CLEAN
            (0UL<<2U) |    // UNLOCK
            (0UL<<1U) |    // LOCK
            (0UL<<0U) );   // PRELOAD

    __asm volatile("dmb");

    while( READ32(CACHE_MTEND)!= 0x0 ) {};
}

/**
 * Sets up MMU. Done from assembler
 */
void Mcu_Arc_InitMM( void ) {


    /*
     * Setup UNICACHE_MMU 1:1 virtual/physical, that is actually done in the IPUx_MMU instead
     *
     * Type    Pages  Size
     * -------------------------------------------------------
     * Large     4     512 MiB or 32 MiB (configurable)
     * Medium    2     256 KiB or 128 KiB (configurable)
     * Small    10     16 KiB or 4 KiB (configurable)
     *
     * On reset the following small page is setup (in hardware that is):
     *
     *   Page  XLTE          ADDR
     *    0  0x55020       0x00000      IPU RAM
     *    1  0x55080       0x40000      IPU_UNICACHE_MMU
     *
     * The reset handler setup
     *   Page  XLTE          ADDR
     *    0    0x0000      0x00000
     *
     * What is really implemented in this cache is held in the dark.
     * Enabling some features such as posted write and will do nothing and
     * other features will make you go into hardfault.
     *
     *
     */

    uint32_t page;

    /* Clear status registers */
    WRITE32(MMU_INIT_CFG+0x8UL ,0x000000ff);

    /* Remove pages setup from reset */
    page = 0;
    WRITE32(MMU_INIT_CFG+0xA20 + (4*page),0 );

    /*
     * Clear all UNICACHE attribute entries
     */

    /* Large (all except page 0) */
    for( page=1; page < 4; page++) {
        WRITE32(MMU_INIT_CFG+0x840 + (4*page),0);
    }

    /* Medium */
    for( page=0; page < 2; page++) {
        WRITE32(MMU_INIT_CFG+0x8e0 + (4*page),0);
    }

    /* Small */
    for( page=2; page < 10; page++) {
        WRITE32(MMU_INIT_CFG+0xA20 + (4*page),0);
    }

    /*
     * Invalidate cached areas (unicache)
     * */
    WRITE32(CACHE_CONFIG,  0x00000000);
    WRITE32(CACHE_MTSTART, 0x00000000);
    WRITE32(CACHE_MTEND,   0x0b000000);

    __asm volatile("dmb");

    /* Perform operation */
    WRITE32(CACHE_MAINT,
            (0UL<<5U) |    // INTERRUPT
            (1UL<<4U) |    // INVALIDATE
            (0UL<<3U) |    // CLEAN
            (0UL<<2U) |    // UNLOCK
            (0UL<<1U) |    // LOCK
            (0UL<<0U) );   // PRELOAD

    __asm volatile("dmb");

    while( READ32(CACHE_MTEND)!= 0x0 ) {};


    /* Perform global flush */
    WRITE32(CACHE_MMU_MAINT,
            (1UL<<10U) |   // G_FLUSH
            (0UL<<9U) |    // L2_CACHE
            (0UL<<8U) |    // L1_CACHE2
            (0UL<<7U) |    // L1_CACHE1
            (0UL<<6U) |    // CPU_INTERRUPT
            (0UL<<5U) |    // HOST_INTERRUPT
            (0UL<<4U) |    // INVALIDATE
            (0UL<<3U) |    // CLEAN
            (0UL<<2U) |    // UNLOCK
            (0UL<<1U) |    // LOCK
            (0UL<<0U) );   // PRELOAD

    __asm volatile("dmb");

    while( (READ32(CACHE_MMU_MAINTST) & 1ul) == 1ul ) {};


    /* Disable page 0, already setup a big one */
    page = 5;
    WRITE32(MMU_INIT_CFG+0x920 + (4*page),0x55080000);/* VA */
    WRITE32(MMU_INIT_CFG+0x9A0 + (4*page),0x55080000 );/* PA */
    WRITE32(MMU_INIT_CFG+0xA20 + (4*page),
            (0UL<<23U) |    // L2_WR_POLICY, 0x0: Write through, 0x1: Write back
            (0UL<<22U) |    // L2_ALLOCATE,
            (0UL<<21U) |    // L2_POSTED
            (0UL<<20U) |    // L2_CACHEABLE
            (0UL<<19U) |    // L1_WR_POLICY
            (0UL<<18U) |    // L1_ALLOCATE
            (0UL<<17U) |    // L1_POSTED
            (0UL<<16U) |    // L1_CACHEABLE
            (0UL<<6U) |     // PRELOAD
            (0UL<<3U) |     // VOLATILE
            (0UL<<2U) |     // -- RESERVED
            (1UL<<1U) |     // SIZE, 0x0: 4 KiB (0x1000), 0x1: 16 KiB (0x4000)
            (1UL<<0U) );    // ENABLE

    __asm volatile("dmb");

    /* Disable page setup by HW (since we just added page=5 that does 1:1 mapping) */
    page = 1;
    WRITE32(MMU_INIT_CFG+0xA20 + (4*page),0 );
    __asm volatile("dmb");


    /* Adjust caches on LARGE page=0  */
    page = 0;
    WRITE32(MMU_INIT_CFG+0x840 + (4*page),
            (0UL<<23U) |    // L2_WR_POLICY, 0x0: Write through, 0x1: Write back
            (0UL<<22U) |    // L2_ALLOCATE,
            (0UL<<21U) |    // L2_POSTED
            (0UL<<20U) |    // L2_CACHEABLE
            (0UL<<19U) |    // L1_WR_POLICY
            (0UL<<18U) |    // L1_ALLOCATE
            (0UL<<17U) |    // L1_POSTED
            (1UL<<16U) |    // L1_CACHEABLE
            (0UL<<6U) |     // PRELOAD
            (1UL<<3U) |     // VOLATILE
            (0UL<<2U) |     // -- RESERVED
            (0UL<<1U) |     // SIZE, 0x0: 32 MiB (0x200_0000), 0x1: 512 MiB (0x2000_0000)
            (1UL<<0U) );    // ENABLE

    __asm volatile("dmb");

    /*. data 0x8000_0000 -- 0x8200_0000  */
    page = 1;
    WRITE32(MMU_INIT_CFG+0x800 + (4*page),0x80000000);/* VA */
    WRITE32(MMU_INIT_CFG+0x820 + (4*page),0x80000000 );/* PA */
    WRITE32(MMU_INIT_CFG+0x840 + (4*page),
            (0UL<<23U) |    // L2_WR_POLICY, 0x0: Write through, 0x1: Write back
            (0UL<<22U) |    // L2_ALLOCATE,
            (0UL<<21U) |    // L2_POSTED
            (0UL<<20U) |    // L2_CACHEABLE
            (0UL<<19U) |    // L1_WR_POLICY
            (0UL<<18U) |    // L1_ALLOCATE
            (0UL<<17U) |    // L1_POSTED
            (1UL<<16U) |    // L1_CACHEABLE
            (0UL<<6U) |     // PRELOAD
            (1UL<<3U) |     // VOLATILE
            (0UL<<2U) |     // -- RESERVED
            (0UL<<1U) |     // SIZE, 0x0: 32 MiB (0x200_0000), 0x1: 512 MiB (0x2000_0000)
            (1UL<<0U) );    // ENABLE

    __asm volatile("dmb");

    /* Keep L3 and L4 as is,  0x68000000 -- 0x7000_0000 */
    page = 2;
    WRITE32(MMU_INIT_CFG+0x800 + (4*page),0x68000000);/* VA */
    WRITE32(MMU_INIT_CFG+0x820 + (4*page),0x68000000);/* PA */
    WRITE32(MMU_INIT_CFG+0x840 + (4*page),
            (0UL<<23U) |    // L2_WR_POLICY, 0x0: Write through, 0x1: Write back
            (0UL<<22U) |    // L2_ALLOCATE,
            (0UL<<21U) |    // L2_POSTED
            (0UL<<20U) |    // L2_CACHEABLE
            (0UL<<19U) |    // L1_WR_POLICY
            (0UL<<18U) |    // L1_ALLOCATE
            (0UL<<17U) |    // L1_POSTED
            (0UL<<16U) |    // L1_CACHEABLE
            (0UL<<6U) |     // PRELOAD
            (1UL<<3U) |     // VOLATILE
            (0UL<<2U) |     // -- RESERVED
            (1UL<<1U) |     // SIZE, 0x0: 32 MiB (0x0200_0000), 0x1: 512 MiB (0x2000_0000)
            (1UL<<0U) );    // ENABLE

    /*
     * MEDIUM
     */

    /* Disable initial page setup by startup */
    page = 0;
    WRITE32(MMU_INIT_CFG+0x860 + (4*page),0x0);/* VA */
    WRITE32(MMU_INIT_CFG+0x8a0 + (4*page),0x0);/* PA */
    WRITE32(MMU_INIT_CFG+0x8e0 + (4*page),0x0);

    /*
     * SMALL
     */



    __asm volatile("dmb");

    /* VRING0, fix for U-Boot load bug  */
    page = 2;
    WRITE32(MMU_INIT_CFG+0x920 + (4*page),0xa0000000);/* VA */
    WRITE32(MMU_INIT_CFG+0x9A0 + (4*page),0x60000000);/* PA */
    WRITE32(MMU_INIT_CFG+0xA20 + (4*page),
            (0UL<<23U) |    // L2_WR_POLICY, 0x0: Write through, 0x1: Write back
            (0UL<<22U) |    // L2_ALLOCATE,
            (0UL<<21U) |    // L2_POSTED
            (0UL<<20U) |    // L2_CACHEABLE
            (0UL<<19U) |    // L1_WR_POLICY
            (0UL<<18U) |    // L1_ALLOCATE
            (0UL<<17U) |    // L1_POSTED
            (0UL<<16U) |    // L1_CACHEABLE
            (0UL<<6U) |     // PRELOAD
            (0UL<<3U) |     // VOLATILE
            (0UL<<2U) |     // -- RESERVED
            (1UL<<1U) |     // SIZE, 0x0: 4 KiB (0x1000), 0x1: 16 KiB (0x4000)
            (1UL<<0U) );    // ENABLE


    /* VRING1, fix for U-Boot load bug  */
    page = 3;
    WRITE32(MMU_INIT_CFG+0x920 + (4*page),0xa0004000);/* VA */
    WRITE32(MMU_INIT_CFG+0x9A0 + (4*page),0x60004000);/* PA */
    WRITE32(MMU_INIT_CFG+0xA20 + (4*page),
            (0UL<<23U) |    // L2_WR_POLICY, 0x0: Write through, 0x1: Write back
            (0UL<<22U) |    // L2_ALLOCATE,
            (0UL<<21U) |    // L2_POSTED
            (0UL<<20U) |    // L2_CACHEABLE
            (0UL<<19U) |    // L1_WR_POLICY
            (0UL<<18U) |    // L1_ALLOCATE
            (0UL<<17U) |    // L1_POSTED
            (0UL<<16U) |    // L1_CACHEABLE
            (0UL<<6U) |     // PRELOAD
            (0UL<<3U) |     // VOLATILE
            (0UL<<2U) |     // -- RESERVED
            (1UL<<1U) |     // SIZE, 0x0: 4 KiB (0x1000), 0x1: 16 KiB (0x4000)
            (1UL<<0U) );    // ENABLE


    /* Lets have an un-cached page for terminal and other things */
    page = 4;
    WRITE32(MMU_INIT_CFG+0x920 + (4*page),0x82000000);/* VA */
    WRITE32(MMU_INIT_CFG+0x9A0 + (4*page),0x804FC000);/* PA */
    WRITE32(MMU_INIT_CFG+0xA20 + (4*page),
            (0UL<<23U) |    // L2_WR_POLICY, 0x0: Write through, 0x1: Write back
            (0UL<<22U) |    // L2_ALLOCATE,
            (0UL<<21U) |    // L2_POSTED
            (0UL<<20U) |    // L2_CACHEABLE
            (0UL<<19U) |    // L1_WR_POLICY
            (0UL<<18U) |    // L1_ALLOCATE
            (0UL<<17U) |    // L1_POSTED
            (0UL<<16U) |    // L1_CACHEABLE
            (0UL<<6U) |     // PRELOAD
            (0UL<<3U) |     // VOLATILE
            (0UL<<2U) |     // -- RESERVED
            (1UL<<1U) |     // SIZE, 0x0: 4 KiB (0x1000), 0x1: 16 KiB (0x4000)
            (1UL<<0U) );    // ENABLE

    /* Enable caches */
    WRITE32(CACHE_CONFIG,
            (0UL<<4U) |     // LOCK_MAIN
            (0UL<<3U) |     // LOCK_PORT
            (0UL<<2U) |     // LOCK_INT
            (1UL<<1U) |     // BYPASS
            (0UL<<0U) );    // CACHE_LOCK

    __asm volatile("dmb");
}
#endif
#endif

/* @req SWS_Mcu_00026 */
/* @req SWS_Mcu_00116 */ /* Driver module will be responsible for initializing MCU registers */
void Mcu_Arc_InitPre( const Mcu_ConfigType *configPtr ) {
    (void)configPtr;

    /* Set vector table */
    SCB->VTOR = 0x400;
    /* @req SWS_Mcu_00245 */ /* MCU initializes non I/O registers */

    EnableClocks_Gpio(2);
    EnableClocks_Gpio(3);
    EnableClocks_Gpio(4);
    EnableClocks_Gpio(5);
    EnableClocks_Gpio(6);
    EnableClocks_Gpio(7);
    EnableClocks_Gpio(8);

#if defined (USE_GPT) || defined(USE_PWM)
    /* GPT1 */
#if ( Mcu_Enable_Timer_1 == STD_ON )
    EnableClocks_Timer(1);
#endif //Mcu_Enable_Timer_1

    /* GPT2 */
#if ( Mcu_Enable_Timer_2 == STD_ON )
    EnableClocks_Timer(2);
#endif //Mcu_Enable_Timer_2

    /* GPT3 */
#if ( Mcu_Enable_Timer_3 == STD_ON )
    EnableClocks_Timer(3);
#endif //Mcu_Enable_Timer_3

    /* GPT4 */
#if ( Mcu_Enable_Timer_4 == STD_ON )
    EnableClocks_Timer(4);
#endif //Mcu_Enable_Timer_4

    /* GPT5 */
#if ( Mcu_Enable_Timer_5 == STD_ON )
    EnableClocks_Timer(5);
#endif //Mcu_Enable_Timer_5

    /* GPT6 */
#if ( Mcu_Enable_Timer_6 == STD_ON )
    EnableClocks_Timer(6);
#endif //Mcu_Enable_Timer_6

    /* GPT7 */
#if ( Mcu_Enable_Timer_7 == STD_ON )
    EnableClocks_Timer(7);
#endif //Mcu_Enable_Timer_7

    /* GPT8 */
#if ( Mcu_Enable_Timer_8 == STD_ON )
    EnableClocks_Timer(8);
#endif //Mcu_Enable_Timer_8

    /* GPT9 */
#if ( Mcu_Enable_Timer_9 == STD_ON )
    EnableClocks_Timer(9);
#endif //Mcu_Enable_Timer_9

    /* GPT10 */
#if ( Mcu_Enable_Timer_10 == STD_ON )
    EnableClocks_Timer(10);
#endif //Mcu_Enable_Timer_10

    /* GPT11 */
#if ( Mcu_Enable_Timer_11 == STD_ON )
    EnableClocks_Timer(11);
#endif //Mcu_Enable_Timer_11

    /* GPT12 */
#if ( Mcu_Enable_Timer_12 == STD_ON )
    /* CM_WKUPAON_TIMER12_CLKCTRL can only be set to use the TIMER_SYS_CLK.
     * The register is read only so nothing to do. */
#endif //Mcu_Enable_Timer_12

    /* GPT13 */
#if ( Mcu_Enable_Timer_13 == STD_ON )
    EnableClocks_Timer(13);
#endif //Mcu_Enable_Timer_13

    /* GPT14 */
#if ( Mcu_Enable_Timer_14 == STD_ON )
    EnableClocks_Timer(14);
#endif //Mcu_Enable_Timer_14

    /* GPT15 */
#if ( Mcu_Enable_Timer_15 == STD_ON )
    EnableClocks_Timer(15);
#endif //Mcu_Enable_Timer_15

    /* GPT16 */
#if ( Mcu_Enable_Timer_16 == STD_ON )
    EnableClocks_Timer(16);
#endif //Mcu_Enable_Timer_16

    /* Setup default interrupt mux for GPT */
#if ( Mcu_Enable_Timer_1 == STD_ON )
    WriteIrqMux(TINT1_IRQ,TIMER1INT);
#endif
#if ( Mcu_Enable_Timer_2 == STD_ON )
    WriteIrqMux(TINT2_IRQ,TIMER2INT);
#endif
#if ( Mcu_Enable_Timer_3 == STD_ON )
    WriteIrqMux(TINT3_IRQ,TIMER3INT);
#endif
#if ( Mcu_Enable_Timer_4 == STD_ON )
    WriteIrqMux(TINT4_IRQ,TIMER4INT);
#endif
#if ( Mcu_Enable_Timer_5 == STD_ON )
    WriteIrqMux(TINT5_IRQ,TIMER5INT);
#endif
#if ( Mcu_Enable_Timer_6 == STD_ON )
    WriteIrqMux(TINT6_IRQ,TIMER6INT);
#endif
#if ( Mcu_Enable_Timer_7 == STD_ON )
    WriteIrqMux(TINT7_IRQ,TIMER7INT);
#endif
#if ( Mcu_Enable_Timer_8 == STD_ON )
    WriteIrqMux(TINT8_IRQ,TIMER8INT);
#endif
#if ( Mcu_Enable_Timer_9 == STD_ON )
    WriteIrqMux(TINT9_IRQ,TIMER9INT);
#endif
#if ( Mcu_Enable_Timer_10 == STD_ON )
    WriteIrqMux(TINT10_IRQ,TIMER10INT);
#endif
#if ( Mcu_Enable_Timer_11 == STD_ON )
    WriteIrqMux(TINT11_IRQ,TIMER10INT);
#endif
#if ( Mcu_Enable_Timer_12 == STD_ON )
    WriteIrqMux(TINT12_IRQ,TIMER12INT);
#endif
#if ( Mcu_Enable_Timer_13 == STD_ON )
    WriteIrqMux(TINT13_IRQ,TIMER13INT);
#endif
#if ( Mcu_Enable_Timer_14 == STD_ON )
    WriteIrqMux(TINT14_IRQ,TIMER14INT);
#endif
#if ( Mcu_Enable_Timer_15 == STD_ON )
    WriteIrqMux(TINT15_IRQ,TIMER15INT);
#endif
#if ( Mcu_Enable_Timer_16 == STD_ON )
    WriteIrqMux(TINT16_IRQ,TIMER16INT);
#endif
#endif //USE_GPT

#if defined (USE_CAN)
    /*
     * Initiate CAN clocks
     */

    /* Disable clocks */
#if (MCU_CAN0_EN == STD_ON)
    if((READ32(CM_ALWON_DCAN1_CLKCTRL) & 0x0000000f) != 0){
        WRITE32(CM_ALWON_DCAN1_CLKCTRL, 0x0); /*Disable DCAN1 Clk domain */
    }
#endif

#if (MCU_CAN1_EN == STD_ON)
    if((READ32(CM_L4PER2_DCAN2_CLKCTRL) & 0x0000000f) != 0){
        WRITE32(CM_L4PER2_DCAN2_CLKCTRL, 0x0); /*Disable DCAN2 Clk domain */
    }
#endif
    for(volatile uint32 i=0;i<100;i++);

    /* Enable clocks */
#if (MCU_CAN0_EN == STD_ON)
    WRITE32(CM_ALWON_DCAN1_CLKCTRL, 0x2); /*Enable DCAN1 Clk domain */
    while(READ32(CM_ALWON_DCAN1_CLKCTRL) != 0x2);

     WriteIrqMux(DCAN0_IRQ_INT0,DCAN0INT0);
#endif

#if (MCU_CAN1_EN == STD_ON)
    WRITE32(CM_L4PER2_DCAN2_CLKCTRL, 0x2); /*Enable DCAN2 Clk domain */
    while(READ32(CM_L4PER2_DCAN2_CLKCTRL) != 0x2);

    WriteIrqMux(DCAN1_IRQ_INT0 ,DCAN1INT0);
#endif

    /* Setup default interrupt mux for CAN */
    WRITE32(0x4a00284cU+L3_OFFSET, (DCAN0INT0 << 16) | (READ32(0x4a00284cUL+L3_OFFSET) & 0x0000ffff)); /* intmux[78] */
    WRITE32(0x4a002850U+L3_OFFSET, (DCAN1INT0 << 0 )); /* intmux[79] */
#endif /* defined (USE_CAN) */

#if defined (USE_ETH)

    //WRITE32((CTRL_MODULE_CORE + CTRL_CORE_MMR_LOCK_5),MMR_UNLOCK_5);
    //WRITE32(CTRL_CORE_SMA_SW_6, (READ32(CTRL_CORE_SMA_SW_6)   | ( RMII_CLK_SETTING_MASK & RMII_CLK_SEL_INT_DPLL_GMAC))); /* Select RMII  - Internal clock*/
    //WRITE32((CTRL_MODULE_CORE + CTRL_CORE_MMR_LOCK_5),MMR_LOCK_5);

    //WRITE32((CTRL_MODULE_CORE + CTRL_CORE_MMR_LOCK_1),MMR_UNLOCK_1);
    //WRITE32(CM_GMAC_GMAC_CLKCTRL,(READ32(CM_GMAC_GMAC_CLKCTRL) | ( CLKSEL_REF_MASK & SEL_GMAC_RMII_HS_CLK)));           /* Select RMII clock */
    //WRITE32((CTRL_MODULE_CORE + CTRL_CORE_MMR_LOCK_1),MMR_LOCK_1);

    /* Write IRQ mux */
    WriteIrqMux(GMAC_SW_IRQ_RX_THRESH_PULSE,    GMACSWIRQ_RX_THRESH_PULSE);
    WriteIrqMux(GMAC_SW_IRQ_RX_PULSE,           GMACSWIRQ_RX_PULSE);
    WriteIrqMux(GMAC_SW_IRQ_TX_PULSE,           GMACSWIRQ_TX_PULSE);

    WRITE32(CM_GMAC_GMAC_CLKCTRL, (READ32(CM_GMAC_GMAC_CLKCTRL) | (MODULEMODE_ENABLED & MODULEMODE_MASK)));
    while((READ32(CM_GMAC_GMAC_CLKCTRL) & MODULEMODE_MASK) != MODULEMODE_ENABLED);

	/* by default CLKTRCTRL_NO_SLEEP though */
	WRITE32(CM_GMAC_CLKSTCTRL, (READ32(CM_GMAC_CLKSTCTRL) | (CLKTRCTRL_HW_AUTO & CLKTRCTRL_MASK)));
	while(( (READ32(CM_L4CFG_CLKSTCTRL)) &  CLKTRCTRL_MASK) == 0U){ /* to make sure to not re-gate the clock for spinlock */
		WRITE32(CM_L4CFG_CLKSTCTRL, (READ32(CM_L4CFG_CLKSTCTRL) | (CLKTRCTRL_HW_AUTO & CLKTRCTRL_MASK)));
	}
#endif /* defined (USE_ETH) */

#if defined (USE_UART) || defined(USE_LIN)
//	WRITE32(CTRL_CORE_IPU1_IRQ_61_62, (UARTINT2 << 16u)   |  (UARTINT1 & CTRL_CORE_IRQ_MASK));  /*IPU1_IRQ_61 */ /*IPU1_IRQ_62 */
    WriteIrqMux( UARTINT1_IRQ, UARTINT1 );
    WriteIrqMux( UARTINT2_IRQ, UARTINT2 );
#endif /* defined (USE_UART) || defined(USE_LIN) */
#if defined (USE_I2C)
    /* Initiate I2C clocks */
    WRITE32(CM_L4PER_I2C1_CLKCTRL, 0x2u); /*Enable I2C1 clk  */
    while(READ32(CM_L4PER_I2C1_CLKCTRL) != 0x2u);
    WRITE32(CM_L4PER_I2C2_CLKCTRL, 0x2u); /*Enable I2C2 clk  */
    while(READ32(CM_L4PER_I2C2_CLKCTRL) != 0x2u);
    WRITE32(CM_L4PER_I2C3_CLKCTRL, 0x2u); /*Enable I2C3 clk  */
    while(READ32(CM_L4PER_I2C3_CLKCTRL) != 0x2u);
    WRITE32(CM_L4PER_I2C4_CLKCTRL, 0x2u); /*Enable I2C4 clk  */
    while(READ32(CM_L4PER_I2C4_CLKCTRL) != 0x2u);

    WriteIrqMux(I2CINT1_IRQ,    I2C1INT);
    WriteIrqMux(I2CINT2_IRQ,    I2C2INT);
    WriteIrqMux(I2CINT3_IRQ,    I2C3INT);
    WriteIrqMux(I2CINT4_IRQ,    I2C4INT);
    WriteIrqMux(I2CINT5_IRQ,    I2C5INT);
#endif /* defined (USE_I2C) */
#if defined (USE_SPI)
    /* Init SPI clocks */
    WRITE32(CM_L4PER_MCSPI1_CLKCTRL, 0x2u); /*Enable SPI1 clk  */
    while(READ32(CM_L4PER_MCSPI1_CLKCTRL) != 0x2u);
    WRITE32(CM_L4PER_MCSPI2_CLKCTRL, 0x2u); /*Enable SPI2 clk  */
    while(READ32(CM_L4PER_MCSPI2_CLKCTRL) != 0x2u);
    WRITE32(CM_L4PER_MCSPI3_CLKCTRL, 0x2u); /*Enable SPI3 clk  */
    while(READ32(CM_L4PER_MCSPI3_CLKCTRL) != 0x2u);
    WRITE32(CM_L4PER_MCSPI4_CLKCTRL, 0x2u); /*Enable SPI4 clk  */
    while(READ32(CM_L4PER_MCSPI4_CLKCTRL) != 0x2u);

    /* Set up default interrupt mux for SPI
     */
    WriteIrqMux(MCSPI1_IRQ,    MCSPI1INT);
    WriteIrqMux(MCSPI2_IRQ,    MCSPI2INT);
    WriteIrqMux(MCSPI3_IRQ,    MCSPI3INT);
    WriteIrqMux(MCSPI4_IRQ,    MCSPI4INT);
#endif /* defined (USE_SPI) */

#if defined(USE_PWM)

    /* Enable ePWM clocks */

    /* Enable modules */
    WRITE32(CM_L4PER2_PWMSS1_CLKCTRL, MODULEMODE_ENABLED);
    while(READ32(CM_L4PER2_PWMSS1_CLKCTRL) != MODULEMODE_ENABLED);

    WRITE32(CM_L4PER2_PWMSS2_CLKCTRL, MODULEMODE_ENABLED);
    while(READ32(CM_L4PER2_PWMSS2_CLKCTRL) != MODULEMODE_ENABLED);

    WRITE32(CM_L4PER2_PWMSS3_CLKCTRL, MODULEMODE_ENABLED);
    while(READ32(CM_L4PER2_PWMSS3_CLKCTRL) != MODULEMODE_ENABLED);

    /* Enable the PWMSSx clocks. */
    SET32(CTRL_CORE_CONTROL_IO_2, PWMSS_1_2_3_TBCLKEN);
    while((READ32(CTRL_CORE_CONTROL_IO_2) & PWMSS_1_2_3_TBCLKEN) != PWMSS_1_2_3_TBCLKEN);

    /* Mux interrupts. */
    WriteIrqMux(PWMSS1_ePWM0INT_IRQ, PWMSS1_IRQ_ePWM0INT);
    WriteIrqMux(PWMSS2_ePWM1INT_IRQ, PWMSS2_IRQ_ePWM1INT);
    WriteIrqMux(PWMSS3_ePWM2INT_IRQ, PWMSS3_IRQ_ePWM2INT);

#endif /* defined(USE_PWM) */
}
/*
 * Called at a very early stage...
 */
void Mcu_Arc_InitPost( const Mcu_ConfigType *configPtr ) {
    (void)configPtr;
}


/* ----------------------------[public functions]----------------------------*/

void Mcu_Arc_InitClockPre( const Mcu_ClockSettingConfigType *clockSettingsPtr )
{
}


void Mcu_Arc_InitClockPost( const Mcu_ClockSettingConfigType *clockSettingsPtr )
{
}

#if defined(CFG_MCU_ARC_LP)

/**
 *
 * @param mcuMode The mcuMode from Mcu_SetMode()
 */
void Mcu_Arc_SetModePre( Mcu_ModeType mcuMode)
{
    Mcu_Arc_SetModePre2(mcuMode, Mcu_Arc_ConfigData.sleepConfig );
}

/**
 *
 * @param mcuMode The mcuMode from Mcu_SetMode()
 */
void Mcu_Arc_SetModePost( Mcu_ModeType mcuMode)
{
    Mcu_Arc_SetModePost2(mcuMode,  Mcu_Arc_ConfigData.sleepConfig);
}
#endif


#if defined(CFG_JAC6_IPC)
uint8 Mcu_Arc_getIpuId() {
    return 1;
}


uint8 Mcu_Arc_getCoreId() {
    /* Since we don't support multicore, we're always running on the same core */
    return 0;
}


static void IntXbar_initXbarRegs(volatile uint32 **intXbarReg, uint16 *intXbarLength)
{
    if (Mcu_Arc_getIpuId() == 1) {
        *intXbarReg = (uint32 *)CTRL_CORE_IPU1_IRQ_23_24;
    }
    else {
        *intXbarReg = (uint32 *)CTRL_CORE_IPU2_IRQ_23_24;
    }

    *intXbarLength = NUM_BENELLI_IPU_XBAR_INST;

}

/*!
 *  ======== IntXbar_connect ========
 */
void Mcu_Arc_IntXbar_connect(uint8 xbarInstance, uint16 intSource)
{
    uint32 regOffset;
    uint32 oldLockReg;
    uint16 intXbarLength;
    volatile uint32 *mmrLockReg;
    volatile uint32 *intXbarReg;

    mmrLockReg = (uint32 *)(CTRL_MODULE_CORE + CTRL_CORE_MMR_LOCK_2);

    IntXbar_initXbarRegs(&intXbarReg, &intXbarLength);

    regOffset = (xbarInstance - 1) / 2;

    /* Unlock MMR before writing to Xbar Register */
    oldLockReg = *mmrLockReg;
    if (oldLockReg != MMR_UNLOCK_2) {
        *mmrLockReg = MMR_UNLOCK_2;
    }

    if ((xbarInstance - 1) % 2) {
        intXbarReg[regOffset] = (intXbarReg[regOffset] & 0x0000FFFF) |
                                (intSource << 16);
    }
    else {
        intXbarReg[regOffset] = (intXbarReg[regOffset] & 0xFFFF0000) |
                                (intSource);
    }

    /* Lock MMR before returning */
    *mmrLockReg = oldLockReg;
}

/*** Enable/Disable the Cortex M4 internal interrupts.
 *   That is done in NVIC_ISERx and NVIC_ICERx registers of the CPU,
 *   each bit represents interrupt number N..N+31, with N depending on
 *   which ISER/ICER register that is
 */

void Mcu_Arc_EnableM4Interrupt(uint8 vector)
{
    Irq_EnableVector(vector, 0, 0);
#if 0
    uint8 iserRegister = vector / 32;
    uint32 mask = (1 << (vector % 32));
    SET32(M4_NVIC_ISER0 + (4 * iserRegister), mask);
#endif
}

void Mcu_Arc_DisableM4Interrupt(uint8 vector)
{
    uint8 iserRegister = vector / 32;
    uint32 mask = (1 << (vector % 32));
    SET32(M4_NVIC_ICER0 + (4 * iserRegister), mask);
}
#endif

