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

/* ----------------------------[includes]------------------------------------*/

#include "arc_assert.h"
#include "Std_Types.h"
#include "Mcu.h"
#include "io.h"
#include "mpc55xx.h"
#include "Mcu_Arc.h"
#if defined(USE_FEE)
#include "Fee_Memory_Cfg.h"
#endif
#if defined(USE_DMA)
#include "Dma.h"
#endif
#include "asm_ppc.h"
#include "Os.h"
#include "EcuM.h"
#include "isr.h"
#include "Mcu_Internal.h"

#include "debug.h"
#include <string.h>


/* ----------------------------[private define]------------------------------*/

#define CALC_SYSTEM_CLOCK(_extal,_emfd,_eprediv,_erfd)  \
            ( (((_extal)/(_eprediv))*(_emfd)) / ((_erfd)) )

#define ME_RUN_PC0      0
#define ME_RUN_PC1      1



/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/



void Mcu_Arc_InitPre(const Mcu_ConfigType *configPtr) {
    /*lint -e{920} General interface, the configPtr may be needed for other architectures */
    (void) configPtr;
}

void Mcu_Arc_InitPost( const Mcu_ConfigType *configPtr ) {
    /*lint -e{920} General interface, the configPtr may be needed for other architectures */
    (void)configPtr;
}

void Mcu_Arc_InitClockPre( const Mcu_ClockSettingConfigType *clockSettingsPtr )
{
     /*lint -e{920} General interface, the clockSettingsPtr may be needed for other architectures */
    (void)clockSettingsPtr; // get rid of compiler warning
}

struct EccInitTableS {
    uint8 *start;
    uint32 length;
};

// freescale provided code for setting upp clocks, de appnote
//http://cache.freescale.com/files/microcontrollers/doc/app_note/AN4812.pdf?fpsp=1&WT_TYPE=Application%20Notes&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=pdf&WT_ASSET=Documentation&Parent_nodeId=1351098580720722626559&Parent_pageType=product
/*!****************************************************************************/
/*! MPC5777M Matterhorn PLL and Clock Configuration */
/*! Configure the Mode and Clock Tree */
/*! Note: For MPC5777M cut 1, code must run from Core 2 local Memory, */
/*! it cannot run from System RAM */
/*!****************************************************************************/
void MC_MODE_INIT(void){
    //int i;
    /*! 1 Clear any faults */
    /*! Clear faults | MC_RGM.DES, MC_RGM.FES, and MC_ME.ME */
    MC_RGM.DES.R = 0xFFFF;
    MC_RGM.FES.R = 0xFFFF;
    MC_ME.ME.R = 0x000005FF;
    /*! 2 Set up peripheral run modes */
    /*! Enable the modes Required | MC_ME.ME */
    MC_ME.ME.R = 0x0000800F;
    /*! Add MC_ME.PCTL[x].R initializations here */
    /*! Set RUN Configuration Registers | MC_ME.RUN_PC[n] */
    MC_ME.RUN_PC[0].R=0x000000FE; /* Peripheral ON in every mode */
    MC_ME.RUN_PC[1].R=0x000000FE; /* Peripheral ON in every mode */
    MC_ME.RUN_PC[2].R=0x000000FE; /* Peripheral ON in every mode */
    MC_ME.RUN_PC[3].R=0x000000FE; /* Peripheral ON in every mode */
    MC_ME.RUN_PC[4].R=0x000000FE; /* Peripheral ON in every mode */
    MC_ME.RUN_PC[5].R=0x000000FE; /* Peripheral ON in every mode */
    MC_ME.RUN_PC[6].R=0x000000FE; /* Peripheral ON in every mode */
    MC_ME.RUN_PC[7].R=0x000000FE; /* Peripheral ON in every mode */
    /*! 3 Configure System Clock Dividers */
    /*! Configure System clock dividers */
    /*! Full speed Core 0 / 1 = 300 MHz. PLL1 = 600 MHz. */

    MC_CGM.SC_DIV_RC.R = 0x00000001uL; /* System clock divider ratios will */
    /* change with next update. */
    /* Not required for Cut 1. */
    MC_CGM.DIV_UPD_TYPE.R = 0x80000000uL; /* System clock divider ratios updated */
    /* on writing MC_CGM.DIV_UPD_TRIG.
    */ /* Not required for Cut 1. */
    MC_CGM.SC_DC2.R=0x800B0000uL; /*! PBRIDGE Clock Divide by 12 (50 MHz) */
    MC_CGM.SC_DC1.R=0x80050000uL; /*! SXBAR Clock Divide by 6 (100 MHz) */
    MC_CGM.SC_DC0.R=0x80020000uL; /*! FXBAR Clock Divide by 3 (200 MHz) */
    MC_CGM.SC_DC3.R=0x80010000uL; /*! Core0/1 Clock Divide by 2 (300 MHz) */
    MC_CGM.SC_DC4.R=0x80020000uL; /*! System Clock Divide by 3 (200 MHz) */
    MC_CGM.DIV_UPD_TRIG.R = 0xfeedfaceuL; /*! System clock divider ratio updates */
    /* triggered. Not required for Cut 1. */
    while (MC_CGM.DIV_UPD_STAT.B.SYS_UPD_STAT == 1u){} /*! Wait for System Clock */
    /* Div Update Status == 0. */
    /* Not required for Cut 1. */
    /*! 4 Configure System Clock Dividers */

    /*! Enable and configure Aux clocks */
    MC_CGM.AC0_SC.B.SELCTL=2u; // set PLL0 PHI for Aux Clock 0

    MC_CGM.AC0_DC0.R=0x80040000uL; // program Aux Clock 0 divider 0
    // peripheral clock -> Divide by = 4 + 1
    // 400 MHz/5 = 80 MHz

    MC_CGM.AC0_DC1.R=0x80180000uL; // program Aux Clock 0 divider 1
    // SDADC clock -> Divide by 24 + 1.
    // 400 MHz / 25 = 16 MHz

    // MC_CGM.AC0_DC2.R=0x801B0000uL; // program Aux Clock 0 divider 2
    // SARADC clock -> Divide by 27 + 1
    // 400 MHz / 28 = 14.6 MHz
    MC_CGM.AC0_DC2.R=0x80140000uL; // program Aux Clock 0 divider 2
       // SARADC clock -> Divide by 20 + 1
       // 400 MHz / 21 = 19 MHz
    MC_CGM.AC0_DC3.R=0x80030000uL; // program Aux Clock 0 divider 3
    // DSPI_CLK0 -> Divide by 3 + 1
    //400 MHz / 4 = 100 MHz
    MC_CGM.AC0_DC4.R=0x80030000uL; // program Aux Clock 0 divider 4
    // DSPI_CLK1/LIN_CLK -> Divide by 3 + 1
    // 400 MHz / 4 = 100 MHz
    MC_CGM.AC2_DC0.R=0x80090000uL; // program Aux Clock 2 divider 0
    // FlexRay -> Divide by 9 + 1
    // 400 MHz / 10 = 40 MHz
    MC_CGM.AC2_DC1.R=0x80090000uL; // program Aux Clock 2 divider 1
    // SENT -> Divide by 9 + 1
    // 400 MHz / 10 = 40 MHz
    MC_CGM.AC5_DC0.R=0x80090000uL; // program Aux Clock 5 divider 0
    // PSI5 -> Divide by 9 + 1
    // 400 MHz / 10 = 40 MHz
    MC_CGM.AC5_DC1.R=0x80090000uL; // program Aux Clock 5 divider 1
    // PSI5 -> Divide by 9 + 1
    // 400 MHz / 10 = 40 MHz
    MC_CGM.AC5_DC2.R=0x80090000uL; // program Aux Clock 5 divider 2
    // PSI5 -> Divide by 9 + 1
    // 400 MHz / 10 = 40 MHz
    /* CAN Clock Runs from XOSC by Default */
    //CAN controller clock divider to be set in MCU.c according to clock source selected.
    MC_CGM.AC9_SC.B.SELCTL=1; // Select XOSC for Aux Clock 9
    MC_CGM.AC9_DC0.R=0x80030000uL; // program Aux Clock 8 divider 0
    // RTI/PIT-> Divide by 4

    MC_CGM.AC10_SC.B.SELCTL=2u;   // Select PLL0 PHI for Aux Clock 10
    MC_CGM.AC10_DC0.R=0x800F0000uL; // program Aux Clock 10 divider 0
    // ENET -> Divide by 15 + 1
    // 400 MHz / 16 = 25 MHz

    while ( MC_CGM.AC10_SS.B.SELSTAT != 2u);


    /* Ref_clk output for Phy if needed */
    MC_CGM.AC7_SC.B.SELCTL=2u;             /*slect PLL0*/
    MC_CGM.AC7_DC0.R = 0x800F0000uL;        /*400MHz/16  = 25MHz use sysclk1 op to PHY*/
    while ( MC_CGM.AC7_SS.B.SELSTAT != MC_CGM.AC7_SC.B.SELCTL);
    /*! Set the PRAMC Flow Through disable */
    /*! SRAM requires additional wait state */
    /*! Note: Do not change the FT_DIS bit while accessing System RAM.
    Relocate code programming the FT_DIS bit to another memory area
    (e.g. local Core memory). */
    /*! Also, set the FT_DIS bit after programming clock dividers and before
    setting PLLs and executing the Mode Entry change */
    PRAMC.PRCR1.B.FT_DIS = 1u; /*! Set Flow Through Disable. */

    /*! Step 5 --- CONFIGURE X0SC PLL0 PLL1 --- */
    /*! Route XOSC to the PLLs - IRC is default */
    MC_CGM.AC3_SC.B.SELCTL=1u; /*! Connect XOSC to PLL0 */
    MC_CGM.AC4_SC.B.SELCTL=1u; /*! Connect XOSC to PLL1 */

    /*! Configure PLL0 Dividers - 400 MHz from 40 MHz XOSC */
    PLLDIG.PLL0DV.B.RFDPHI = 1u;
    PLLDIG.PLL0DV.B.PREDIV = 4u;
    PLLDIG.PLL0DV.B.MFD = 40u;
    //! fPLL0_VCO = (fpll0_ref * 2 * MFD) / PREDIV
    //! fPLL0_VCO = (40 MHz * 2 * 40) / 4
    //! fPLL0_VCO = 800 MHz
    //!
    //! fPLL0_PHI = (fpll0_ref * 2 * MFD) / (PREDIV * RFDPHI * 2)
    //! fPLL0_PHI = (40 MHz * 2 * 40) / (4 * 1 * 2)
    //! fPLL0_PHI = 400 MHz

    /*! Put PLL0 into Normal mode */
    PLLDIG.PLL0CR.B.CLKCFG = 3u;
    /*! Configure PLL1 Dividers - 600 MHz from 40 MHz XOSC */
    PLLDIG.PLL1DV.B.RFDPHI = 1u;
    PLLDIG.PLL1DV.B.MFD = 30u;
    //! fPLL1_VCO = (fpll1_ref * MFD)
    //! fPLL1_VCO = (40 MHz * 30)
    //! fPLL1_VCO = 1200 MHz
    //!
    //! fPLL1_PHI = (fpll0_ref * MFD) / (RFDPHI * 2)
    //! fPLL1_PHI = (40 MHz * 30) / (1 * 2)
    //! fPLL1_PHI = 600 MHz

    /*! Put PLL1 into Normal mode */
    PLLDIG.PLL1CR.B.CLKCFG = 3u;
    /*! 6 CONFIGURE PROGRESSIVE CLOCK SWITCHING (PCS), Configure Progressive Clock Switching
    (PCS) to prevent glitches - 0.05 rate 70 steps. */
    MC_CGM.PCS_SDUR.R = 100u; /*! set Switch Duration */
    MC_ME.DRUN_MC.B.PWRLVL=3u; /*! Configure DRUN power level */
    /*! Configure PLL1 PCS switch | See RM section "Progressive system clock switching" */
    MC_CGM.PCS_DIVC4.B.INIT = 851u; /*! Set the Divider Change Initial Value */
    MC_CGM.PCS_DIVC4.B.RATE = 12u; /*! Set the Divider Change Rate */
    MC_CGM.PCS_DIVS4.R = 31671u; /*! Set the Divider Start Value. */
    MC_CGM.PCS_DIVE4.R = 31671u; /*! Set the Divider End Value */
    /* Configure PLL0 PCS switch (See RM section Progressive system clock switching) */
    MC_CGM.PCS_DIVC2.B.INIT = 851; /*! Set the Divider Change Initial Value */
    MC_CGM.PCS_DIVC2.B.RATE = 12; /*! Set the Divider Change Rate */
    MC_CGM.PCS_DIVS2.R = 31671; /*! Set the Divider Start Value */
    MC_CGM.PCS_DIVE2.R = 31671; /*! Set the Divider End Value */

#if 0
    /*! 7 ----- Initialize e200z Cores ----- */
    /* Enable cores if running from RAM and not using the BAF */
    /*! Enable Cores - Will start on next mode transition */
    /*! If core n is enabled, then */
    /*! - Set MC_ME.CADDR[n] to the code start address (see linker file) */
    /*! - Set MC_ME.CCTL[n] to enable core in all modes */
    MC_ME.CCTL0.R = 0x00FE;
    /* RAM addresses */
    MC_ME.CADDR1.R = 0x40010001; /* Set Core 0 Start Address */
    MC_ME.CCTL1.R = 0x00FE; /* Set modes in which Core 0 will run. */
    MC_ME.CADDR2.R = 0x40010001; /* Set Checker Core Start Address */
    MC_ME.CCTL2.R = 0x00FE; /* Set modes in which Checker Core will run.*/
    MC_ME.CADDR3.R = 0x40012001; /* Set Core 1 Start Address */
    MC_ME.CCTL3.R = 0x00FE; /* Set modes in which Core 1 will run. */

    MC_ME.CADDR4.R = 0x40012001; /* Set HSM Start Address */
    MC_ME.CCTL4.R = 0x00FE; /* Set modes in which HSM will run. */
#endif

    /* 8 ----- Perform Mode Entry change ----- */
    /* Set the System Clock. Enable XOSC and PLLs - PLL1 is sysclk, PWRLVL = 3. */
    MC_ME.DRUN_MC.R = 0x301300F4;
    /* Execute mode change: */
    /* Re-enter the DRUN mode to start cores, clock tree dividers, PCS, and PLL1 */
    MC_ME.MCTL.R = 0x30005AF0; /*! Write Mode and Key */
    MC_ME.MCTL.R = 0x3000A50F; /*! Write Mode and Key inverted */
    while(MC_ME.GS.B.S_MTRANS == 1){} /*! Wait for mode entry complete */
    while(MC_ME.GS.B.S_CURRENTMODE != 0x3u){} /*! Check DRUN mode entered */


    while(MC_ME.GS.B.S_XOSC != 0x1u){} /*! Check if external oscillator is not stable */


}

void Mcu_Arc_InitClockPost( const Mcu_ClockSettingConfigType *clockSettingsPtr )
{
    /*lint -e{920} General interface, the clockSettingsPtr may be needed for other architectures */
   (void)clockSettingsPtr; // get rid of compiler warning

   uint32  extal = Mcu_Arc_GetClockReferencePointFrequency();
   while(extal != 40000000){} // code is assuming 40MHz crystal
   // call function provided by freescale to setup clocks to max freq with 40MHz crystal
   MC_MODE_INIT();

}

void Mcu_Arc_SetModePre(Mcu_ModeType mcuMode) {
    /*lint -e{920} General interface, the configPtr may be needed for other architectures */
    (void)mcuMode;
}

void Mcu_Arc_SetModePost( Mcu_ModeType mcuMode)
{
    /*lint -e{920} General interface, the configPtr may be needed for other architectures */
    (void)mcuMode;
}






