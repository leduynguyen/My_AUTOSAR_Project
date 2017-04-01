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


#define CORE_CPUID_CORTEX_M3_ST     0x411FC231UL
#define CORE_CPUID_CORTEX_M3_TI     0x412FC230UL

#define PRCM_BASE_ADDR			           (0x48180000 )
#define PRCM_ALWON_OFFSET		           (0x1400     )
#define CM3_BASE_ADDR	    	           (0x55020000 )
#define CTRL_MODULE_BASE_ADDR	           (0x48140000 )
#define PLL_BASE_ADDRESS                   (0x481C5000 )
#define PRCM_DPLL_OFFSET 		           (0x0300     )
#define I2C_0_CLKCTRL_OFFSET               (0x164      )
#define I2C_1_CLKCTRL_OFFSET               (0x168      )
#define SPI_CLKCTRL_OFFSET				   (0x190uL)

#define CM_ALWON_L3_SLOW_CLKSTCTRL	       (PRCM_BASE_ADDR + PRCM_ALWON_OFFSET)
#define CM_ALWON_TIMER_0_CLKCTRL           (PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + 0x16C)
#define CM_ALWON_TIMER_1_CLKCTRL           (PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + 0x170)
#define CM_ALWON_TIMER_2_CLKCTRL           (PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + 0x174)
#define CM_ALWON_TIMER_3_CLKCTRL           (PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + 0x178)
#define CM_ALWON_TIMER_4_CLKCTRL           (PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + 0x17C)
#define CM_ALWON_TIMER_5_CLKCTRL           (PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + 0x180)
#define CM_ALWON_TIMER_6_CLKCTRL           (PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + 0x184)
#define CM_ALWON_TIMER_7_CLKCTRL           (PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + 0x188)
#define CM_ALWON_DCAN_0_1_CLKCTRL	       (PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + 0x218)
#define CM_TIMER0_CLKSEL			       (PRCM_BASE_ADDR + PRCM_DPLL_OFFSET + 0x8C)
#define CM_TIMER1_CLKSEL			       (PRCM_BASE_ADDR + PRCM_DPLL_OFFSET + 0x90)
#define CM_TIMER2_CLKSEL			       (PRCM_BASE_ADDR + PRCM_DPLL_OFFSET + 0x94)
#define CM_TIMER3_CLKSEL			       (PRCM_BASE_ADDR + PRCM_DPLL_OFFSET + 0x98)
#define CM_TIMER4_CLKSEL			       (PRCM_BASE_ADDR + PRCM_DPLL_OFFSET + 0x9C)
#define CM_TIMER5_CLKSEL			       (PRCM_BASE_ADDR + PRCM_DPLL_OFFSET + 0xA0)
#define CM_TIMER6_CLKSEL			       (PRCM_BASE_ADDR + PRCM_DPLL_OFFSET + 0xA4)
#define CM_TIMER7_CLKSEL			       (PRCM_BASE_ADDR + PRCM_DPLL_OFFSET + 0xA8)
#define TIMER_CLKSRC				       (PLL_BASE_ADDRESS + 0x02E0)
/* I2C */
#define CM_ALWON_I2C_0_CLKCTRL             (PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + I2C_0_CLKCTRL_OFFSET)
#define CM_ALWON_I2C_1_CLKCTRL             (PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + I2C_1_CLKCTRL_OFFSET)
/* SPI */
#define CM_ALWON_SPI_CLKCTRL			   (PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + SPI_CLKCTRL_OFFSET)
#define	SPI_CLKCTRL_MODULEMODE_ENABLED	   0x2uL


#define CM_ALWON_ADCTSC_CLKCTRL				(PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + 0x1C0)

/* INTMUX */
#define MEDIA_CON_INTMUX_0_3_ADDR_OFFSET	0xF54uL
#define MEDIA_CON_INTMUX_1_REG_OFFSET		8uL
#define MEDIA_CON_INTMUX_32_35_ADDR_OFFSET	0xF74uL
#define MEDIA_CON_INTMUX_35_REG_OFFSET		24uL

/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

const cpu_info_t cpu_info_list[] = {
    {
    .name = "Jacinto5",
    .pvr = 0,
    .info = "",
    },
    {
    .name = NULL,
    }
};

/* The supported cores. */
const core_info_t core_info_list[] = {
    {
        .name = "CORE_ARM_CORTEX_M3_TI",
        .pvr = CORE_CPUID_CORTEX_M3_TI,
        .info = "",
    },
    {
        .name = NULL,
    }

};

/* ----------------------------[private functions]---------------------------*/

/* @req SWS_Mcu_00026 */
/* @req SWS_Mcu_00116 */ /* Driver module will be responsible for initializing MCU registers */
void Mcu_Arc_InitPre( const Mcu_ConfigType *configPtr ) {
    (void)configPtr;
#if defined (USE_GPT)
    uint8 timer;
#endif

    /* Set vector table */
    SCB->VTOR = 0x400;
    /* @req SWS_Mcu_00245 */ /* MCU initializes non I/O registers */

    WRITE32(CM_ALWON_L3_SLOW_CLKSTCTRL, 0x2); /*Enable the Power Domain Transition of L3 Slow Domain Peripheral*/

    /* Initiate GPIO clocks */
    /* GPIO_0 */
    WRITE32(PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + 0x15C,0x00000000); /* CM_ALWON_GPIO_0_CLKCTRL */
    WRITE32(PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + 0x15C,0x00000102); /* OPTFCLKEN_DBCLK = 1 (functional clock enabled), MODULEMODE = 2 (enabled) */
    /* GPIO_1-3 */
    WRITE32(PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + 0x160,0x00000000); /* CM_ALWON_GPIO_1_3_CLKCTRL */
    WRITE32(PRCM_BASE_ADDR + PRCM_ALWON_OFFSET + 0x160,0x00000102); /* OPTFCLKEN_DBCLK = 1 (functional clock enabled), MODULEMODE = 2 (enabled) */


#if defined (USE_GPT)
    /* Initiate GPT clocks */
    /* GPT0 */
#if ( Mcu_Enable_Timer_1 == STD_ON )
    timer = 0;
    WRITE32(CM_ALWON_TIMER_0_CLKCTRL,	0x2);
    WRITE32(CM_TIMER0_CLKSEL,  	 	0x2);
    while(((READ32(CM_ALWON_TIMER_0_CLKCTRL ) & 0x30000)>>16) !=0);
    WRITE32(TIMER_CLKSRC, (READ32(TIMER_CLKSRC) & (0xFFFFFFFF^(0x7 << (3*timer)))));
    WRITE32(CM_TIMER0_CLKSEL , 0x1);
#endif //Mcu_Enable_Timer_1

    /* GPT1 */
#if ( Mcu_Enable_Timer_2 == STD_ON )
    timer = 1;
    WRITE32(CM_ALWON_TIMER_1_CLKCTRL,	0x2);
    WRITE32(CM_TIMER1_CLKSEL,  	 	0x2);
    while(((READ32(CM_ALWON_L3_SLOW_CLKSTCTRL) & (0x80000<<timer))>>(19 + timer)) !=0x1);
    while(((READ32(CM_ALWON_TIMER_1_CLKCTRL ) & 0x30000)>>16) !=0);
    WRITE32(TIMER_CLKSRC, (READ32(TIMER_CLKSRC) & (0xFFFFFFFF^(0x7 << (3*timer)))));
    WRITE32(CM_TIMER1_CLKSEL , 0x1);
#endif //Mcu_Enable_Timer_2

    /* GPT2 */
#if ( Mcu_Enable_Timer_3 == STD_ON )
    timer = 2;
    WRITE32(CM_ALWON_TIMER_2_CLKCTRL,	0x2);
    WRITE32(CM_TIMER2_CLKSEL,   		0x2);
    while(((READ32(CM_ALWON_L3_SLOW_CLKSTCTRL) & (0x80000<<timer))>>(19 + timer)) !=0x1);
    while(((READ32(CM_ALWON_TIMER_2_CLKCTRL ) & 0x30000)>>16) !=0);
    WRITE32(TIMER_CLKSRC, (READ32(TIMER_CLKSRC) & (0xFFFFFFFF^(0x7 << (3*timer)))));
    WRITE32(CM_TIMER2_CLKSEL , 0x1);
#endif //Mcu_Enable_Timer_3

    /* GPT3 */
#if ( Mcu_Enable_Timer_4 == STD_ON )
    timer = 3;
    WRITE32(CM_ALWON_TIMER_3_CLKCTRL,	0x2);
    WRITE32(CM_TIMER3_CLKSEL,   		0x2);
    while(((READ32(CM_ALWON_L3_SLOW_CLKSTCTRL) & (0x80000<<timer))>>(19 + timer)) !=0x1);
    while(((READ32(CM_ALWON_TIMER_3_CLKCTRL ) & 0x30000)>>16) !=0);
    WRITE32(TIMER_CLKSRC, (READ32(TIMER_CLKSRC) & (0xFFFFFFFF^(0x7 << (3*timer)))));
    WRITE32(CM_TIMER3_CLKSEL , 		0x1);
#endif //Mcu_Enable_Timer_4

    /* GPT4 */
#if ( Mcu_Enable_Timer_5 == STD_ON )
    timer = 4;
    WRITE32(CM_ALWON_TIMER_4_CLKCTRL,	0x2);
    WRITE32(CM_TIMER4_CLKSEL,			0x2);
    while(((READ32(CM_ALWON_L3_SLOW_CLKSTCTRL) & (0x80000<<timer))>>(19 + timer)) !=0x1);
    while(((READ32(CM_ALWON_TIMER_4_CLKCTRL ) & 0x30000)>>16) !=0);
    WRITE32(TIMER_CLKSRC, (READ32(TIMER_CLKSRC) & (0xFFFFFFFF^(0x7 << (3*timer)))));
    WRITE32(CM_TIMER4_CLKSEL , 0x1);
#endif //Mcu_Enable_Timer_5

    /* GPT5 */
#if ( Mcu_Enable_Timer_6 == STD_ON )
    timer = 5;
    WRITE32(CM_ALWON_TIMER_5_CLKCTRL,	0x2);
    WRITE32(CM_TIMER5_CLKSEL,			0x2);
    while(((READ32(CM_ALWON_L3_SLOW_CLKSTCTRL) & (0x80000<<timer))>>(19 + timer)) !=0x1);
    while(((READ32(CM_ALWON_TIMER_5_CLKCTRL ) & 0x30000)>>16) !=0);
    WRITE32(TIMER_CLKSRC, (READ32(TIMER_CLKSRC) & (0xFFFFFFFF^(0x7 << (3*timer)))));
    WRITE32(CM_TIMER5_CLKSEL , 0x1);
#endif //Mcu_Enable_Timer_6

    /* GPT6 */
#if ( Mcu_Enable_Timer_7 == STD_ON )
    timer = 6;
    WRITE32(CM_ALWON_TIMER_6_CLKCTRL,	0x2);
    WRITE32(CM_TIMER6_CLKSEL,			0x2);
    while(((READ32(CM_ALWON_L3_SLOW_CLKSTCTRL) & (0x80000<<timer))>>(19 + timer)) !=0x1);
    while(((READ32(CM_ALWON_TIMER_6_CLKCTRL ) & 0x30000)>>16) !=0);
    WRITE32(TIMER_CLKSRC, (READ32(TIMER_CLKSRC) & (0xFFFFFFFF^(0x7 << (3*timer)))));
    WRITE32(CM_TIMER6_CLKSEL , 0x1);
#endif //Mcu_Enable_Timer_7

    /* GPT7 */
#if ( Mcu_Enable_Timer_8 == STD_ON )
    timer = 7;
    WRITE32(CM_ALWON_TIMER_7_CLKCTRL,	0x2);
    WRITE32(CM_TIMER7_CLKSEL,   		0x2);
    while(((READ32(CM_ALWON_L3_SLOW_CLKSTCTRL) & (0x80000<<timer))>>(19 + timer)) !=0x1);
    while(((READ32(CM_ALWON_TIMER_7_CLKCTRL ) & 0x30000)>>16) !=0);
    WRITE32(TIMER_CLKSRC, (READ32(TIMER_CLKSRC) & (0xFFFFFFFF^(0x7 << (3*timer)))));
    WRITE32(CM_TIMER7_CLKSEL , 		0x1);
#endif //Mcu_Enable_Timer_8

#endif //USE_GPT

#if defined (USE_CAN)
    /* Initiate CAN clocks */
    if((READ32(CM_ALWON_DCAN_0_1_CLKCTRL) & 0x0000000f) != 0){
        WRITE32(CM_ALWON_DCAN_0_1_CLKCTRL, 0x0); /*Disable DCAN Clk domain */
    }
    for(volatile uint32 i=0;i<100;i++);

    /* Initiate CAN clocks */
    WRITE32(CM_ALWON_DCAN_0_1_CLKCTRL, 0x2); /*Enable DCAN Clk domain */
    while(READ32(CM_ALWON_DCAN_0_1_CLKCTRL) != 0x2);

    /* Setup default interrupt mux for CAN */
    WRITE32(CTRL_MODULE_BASE_ADDR + 0xF88, (DCAN0INT0 << 8) | (DCAN1INT0 << 16));
#endif

#if defined (USE_ADC)
    /* Initiate ADC clocks */
    WRITE32(CM_ALWON_ADCTSC_CLKCTRL, 0x2); /*Enable ADC Clk domain */
    while(READ32(CM_ALWON_ADCTSC_CLKCTRL) != 0x2);

    /* Map intmux[29] to Crossbar Mapping ADC_TSC_GENINT (dec 72) */
    WRITE32(CTRL_MODULE_BASE_ADDR + 0xF70, (uint32)(ADC_TSC_GENINT << 8));
#endif

#if defined (USE_I2C)
    /* Initiate I2C clocks */
    WRITE32(CM_ALWON_I2C_0_CLKCTRL, 0x2u); /*Enable I2C0 and I2C2 Clk domain */
    while(READ32(CM_ALWON_I2C_0_CLKCTRL) != 0x2u);
    WRITE32(CM_ALWON_I2C_1_CLKCTRL, 0x2u); /*Enable I2C1 and I2C3 Clk domain */
    while(READ32(CM_ALWON_I2C_1_CLKCTRL) != 0x2u);

    /* Setup default interrupt mux for I2C2 and I2C3, INTMUX 33 and 34 */
    WRITE32(CTRL_MODULE_BASE_ADDR + 0xF74, (I2CINT2 << 8) | (I2CINT3 << 16u) );
#endif

#if defined (USE_SPI)
    /* Set up default interrupt mux for SPI1 and 2.
     * (SPI0 is already set up and does not need to be muxed).
     * SPI3 is currently not muxed (no interrupt).
     */
    SET32(CTRL_MODULE_BASE_ADDR + MEDIA_CON_INTMUX_0_3_ADDR_OFFSET,
            (SPIINT1 << MEDIA_CON_INTMUX_1_REG_OFFSET));
    SET32(CTRL_MODULE_BASE_ADDR + MEDIA_CON_INTMUX_32_35_ADDR_OFFSET,
            (SPIINT2 << MEDIA_CON_INTMUX_35_REG_OFFSET));

    /* Initiate SPI clocks */
    WRITE32(CM_ALWON_SPI_CLKCTRL, SPI_CLKCTRL_MODULEMODE_ENABLED);
    while(READ32(CM_ALWON_SPI_CLKCTRL) != SPI_CLKCTRL_MODULEMODE_ENABLED);
#endif


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
