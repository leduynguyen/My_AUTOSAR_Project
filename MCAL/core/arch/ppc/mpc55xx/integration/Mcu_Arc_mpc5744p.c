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

/* From Table 13-2. Maximum system level clock frequencies */
#define CLK_SYS_CLOCK           200000000UL
#define CLK_PBRIDGE_0            50000000UL
#define CLK_MOTC_CLK            160000000UL
#define CLK_ADC                  80000000UL
#define CLK_ENET_CLK             50000000UL
#define CLK_ENET_TIME_CLK        50000000UL
#define CLK_FRAY_CLK             80000000UL
#define CLK_CAN_CLK              80000000UL


/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

/* ----------------------------[private functions]---------------------------*/

static uint32 getDivider( uint32 clock, uint32 freq ) {
    uint32 div = ((clock + freq - 1UL) / freq - 1UL);
    if (div != 0UL ) {
        div |= 1UL;
    }
    return div;
}

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

void Mcu_Arc_InitClockPost( const Mcu_ClockSettingConfigType *clockSettingsPtr )
{
    /*
     * Follow "13.5.1.4 PLLDIG initialization information" from TRM
     */
    uint32 pll0_PREDIV = clockSettingsPtr->Mcu_Hw_ClockSettings->pll0_PREDIV;
    uint32 pll0_MFD = clockSettingsPtr->Mcu_Hw_ClockSettings->pll0_MFD;
    uint32 pll0_RFDPHI = clockSettingsPtr->Mcu_Hw_ClockSettings->pll0_RFDPHI;

    // ensure that pll settings are within range
    CONFIG_ASSERT(pll0_PREDIV >=1 && pll0_PREDIV <= 7);
    CONFIG_ASSERT(pll0_MFD >=8 && pll0_MFD <= 127);
    CONFIG_ASSERT(pll0_RFDPHI >=1 && pll0_RFDPHI <= 63);

    _debug_("Current Mode:%d\n",Mcu_Arc_GetMode());

#if 0
    /* Enable run peripheral 0 in all run modes (RUN0,RUN1, .... RUN7) */
    if(SIUL2.MIDR.B.PARTNUM == 0x5744 && SIUL2.MIDR.B.MAJOR_MASK == 1 && SIUL2.MIDR.B.MINOR_MASK == 0) {
        // always issue a short reset on external reset without any self test. This is a workaround for errata e7218 on rev2.0 mask
        // of the mpc5744P (marked 0N65H)
        MC_RGM.FESS.B.SS_EXR = 1u;
    }
#endif

    // setup clock source to xosc for PLL0
    MC_CGM.AC3_SC.B.SELCTL = 1u;

    // ensure that VCO freq is within range
    uint32 extal = Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting].McuClockReferencePointFrequency;
    _debug_("EXTAL         : %d\n",extal);
    _debug_("PLL\n");

    /* 25.8.2 Clock configuration : Fpll0_vco = (fpll0_ref * PLL0DV[MFD] * 2) / PLL0DV[PREDIV] */
    uint64 vcoFreq = (extal * pll0_MFD * 2ULL) / pll0_PREDIV;
    CONFIG_ASSERT( (vcoFreq >= 600000000) && (vcoFreq <= 1250000000) ); /* see Data Sheet for mpc5744p */
    _debug_("  VCOpll0     : %10d (600 to 1250Mhz)\n",(uint32)vcoFreq);

    uint32 pll0_phi = vcoFreq / (2*pll0_RFDPHI);
    CONFIG_ASSERT(pll0_phi <= 200000000);
    _debug_("  Fpll0_phi   : %10d (Max 160Mhz)\n",pll0_phi);

    PLLDIG.PLL0DV.B.PREDIV = pll0_PREDIV;
    PLLDIG.PLL0DV.B.MFD = pll0_MFD;
    PLLDIG.PLL0DV.B.RFDPHI = pll0_RFDPHI;
    /* set PHI1 divider to generate freq between 40 - 78,5MHz */
    PLLDIG.PLL0DV.B.RFDPHI1 = pll0_phi / extal;

    /* start xosc: configure run mode to have xosc enabled */
    MC_ME.DRUN_MC.B.XOSCON = 1;
    /* configure the new run mode */
    MC_ME.DRUN_MC.B.PLL0ON = 1;
    /* and select PLL0 as clock source */
    MC_ME.DRUN_MC.B.SYSCLK = 2;     /* 2-Primary PLL(PLL0),4-Secondary PLL(PLL1)*/

    _debug_("Switching to DRUN\n");
    _debug_("  SYSCLK=2 (PLL0)\n");

    /* Switch to DRUN */
    Mcu_Arc_SwitchMode(3);

    /*
     * PLL1 (FMPLL)
     */
    uint32 pll1_MFD = clockSettingsPtr->Mcu_Hw_ClockSettings->pll1_MFD;
    uint32 pll1_RFDPHI = clockSettingsPtr->Mcu_Hw_ClockSettings->pll1_RFDPHI;

    /* Turn it off */
    MC_ME.DRUN_MC.B.PLL1ON = 0;
    Mcu_Arc_SwitchMode(3);

    // ensure that pll settings are within range
    CONFIG_ASSERT(pll1_MFD >=8 && pll1_MFD <= 127);
    CONFIG_ASSERT(pll1_RFDPHI >=1 && pll1_RFDPHI <= 63);

    // setup clock source tp xosc for PLL1
    MC_CGM.AC4_SC.B.SELCTL = 1u;

    /* 25.8.2 Clock configuration : Fpll1_vco = (fpll1_ref * PLL1DV[MFD]) (FRCDIV disabled) */
    vcoFreq = extal * (uint64)pll1_MFD;
    CONFIG_ASSERT( (vcoFreq >= 600000000UL) && (vcoFreq <= 1250000000UL) ); /* see Data Sheet for mpc5744p */
    _debug_("  VCOpll1     : %10d (600 to 1250Mhz)\n",(uint32)vcoFreq);

    uint32 pll1_phi = vcoFreq / (2*pll1_RFDPHI);
    CONFIG_ASSERT(pll1_phi <= 200000000);
    _debug_("  Fpll1_phi   : %10d (max 200Mhz)\n",pll1_phi);

    PLLDIG.PLL1DV.B.MFD = pll1_MFD;
    PLLDIG.PLL1DV.B.RFDPHI = pll1_RFDPHI;

    /* Turn PLL1 on */
    MC_ME.DRUN_MC.B.PLL1ON = 1;

    Mcu_Arc_SwitchMode(3);

    typeof(MC_CGM.SC_DC0.B) scDc0 = { .DE = 1 };
    scDc0.DIV = getDivider(pll1_phi,CLK_PBRIDGE_0);
    MC_CGM.SC_DC0.B = scDc0; // register can only be accessed through full register write

    _debug_("PBRIDGE\n");
    _debug_("  System Clock Sel 0 : SEE RUN0 mode\n");
    _debug_("  System Clock div : %d\n", scDc0.DIV);
    _debug_("    -->            : %d\n", pll1_phi / (scDc0.DIV+1));

    /*
     * MOTC + ADC
     */
    typeof(MC_CGM.AC0_DC0.B) ac0Dc0 = { .DE = 1 };
    ac0Dc0.DIV = getDivider(pll0_phi,CLK_MOTC_CLK);
    MC_CGM.AC0_DC0.B = ac0Dc0;

    _debug_("MOTC_CLK + ADC_CLK\n");
    _debug_("  Aux Clock Sel 0  : %d (2=PLL0=%d)\n", MC_CGM.AC0_SC.B.SELCTL,pll0_phi);
    _debug_("  Aux Div 0        : %d\n", ac0Dc0.DIV);
    _debug_("    -->            : %d\n", pll0_phi / (ac0Dc0.DIV+1));

    typeof(MC_CGM.AC0_DC2.B) ac0Dc2 = { .DE = 1 };
    ac0Dc2.DIV = getDivider(pll0_phi,CLK_ADC);
    MC_CGM.AC0_DC2.B = ac0Dc2;
    _debug_("  Aux Div 2        : %d\n", ac0Dc2.DIV);
    _debug_("    -->            : %d\n", pll0_phi / (ac0Dc2.DIV+1));

    /*
     * CAN
     */
    typeof(MC_CGM.AC2_DC0.B) ac2Dc0 = { .DE = 1 };
    ac2Dc0.DIV = getDivider(pll0_phi,CLK_ADC);
    MC_CGM.AC2_DC0.B = ac2Dc0;

    _debug_("CAN_CLK (PLL0_PHI only)\n");
    _debug_("  Aux Div 2        : %d (+1 for divider)\n", ac2Dc0.DIV);
    _debug_("     -->           : %d\n", pll0_phi / (ac2Dc0.DIV+1) );

#if defined(USE_ETH)
    /*
     * ENET
     */
    typeof(MC_CGM.AC10_DC0.B) ac10Dc0 = { .DE = 1 };
    ac10Dc0.DIV = getDivider(pll0_phi,CLK_ENET_CLK);
    MC_CGM.AC10_DC0.B = ac10Dc0;
    MC_CGM.AC10_SC.B.SELCTL = 2; /* PLL0 as source */

    typeof(MC_CGM.AC11_DC0.B) ac11Dc0 = { .DE = 1 };
    ac11Dc0.DIV = getDivider(pll0_phi,CLK_ENET_TIME_CLK);
    MC_CGM.AC11_DC0.B = ac11Dc0;
    MC_CGM.AC11_SC.B.SELCTL = 2; /* PLL0 as source */
#endif

    MC_CGM.AC0_SC.B.SELCTL = 2;  /* 0-IRC,1-XOSC,2- PLL0_PHI */

    uint32 runPC = ME_RUN_PC1;

    /* Enable RUN0 mode in Periconfig 1 */
    _debug_("Enabling RUN0 mode in RUN_PC%d\n",runPC);
    MC_ME.RUN_PC[1].R = 0x00000010;

    runPC = ME_RUN_PC1;

    _debug_("Peripheral configuration: %d\n",runPC);

    /* Put them all to RUN_PC1 */
    MC_ME.PCTL9.R = runPC;   /* LFAST_0 */
    MC_ME.PCTL11.R = runPC;  /* SIPI_0 */
    MC_ME.PCTL12.R = runPC;  /* ENET_0 */
    MC_ME.PCTL30.R = runPC;  /* PIT_0  */
    MC_ME.PCTL36.R = runPC;  /* DMAMUX_0 */
    MC_ME.PCTL38.R = runPC;  /* CRC_0 */
    MC_ME.PCTL77.R = runPC;  /* CAN_2 */
    MC_ME.PCTL78.R = runPC;  /* CAN_1 */
    MC_ME.PCTL79.R = runPC;  /* CAN_0 */
    MC_ME.PCTL91.R = runPC;  /* LINFlex_1 */
    MC_ME.PCTL98.R = runPC;  /* DSPI_1 */
    MC_ME.PCTL99.R = runPC;  /* DSPI_0 */
    MC_ME.PCTL104.R = runPC; /* SENT_0 */
    MC_ME.PCTL107.R = runPC; /* FLEXRAY */
    MC_ME.PCTL124.R = runPC; /* ADC_3 */
    MC_ME.PCTL126.R = runPC; /* ADC_1 */
    MC_ME.PCTL137.R = runPC; /* ETIMER_1 */
    MC_ME.PCTL141.R = runPC; /* CTU_1 */
    MC_ME.PCTL144.R = runPC; /* PWM_1 */
    MC_ME.PCTL146.R = runPC; /* DMAMUX_1 */
    MC_ME.PCTL204.R = runPC; /* LINFlex_0 */
    MC_ME.PCTL208.R = runPC; /* DSPI_3 */
    MC_ME.PCTL209.R = runPC; /* DSPI_2 */
    MC_ME.PCTL214.R = runPC; /* SENT_1 */
    MC_ME.PCTL235.R = runPC; /* ADC_2 */
    MC_ME.PCTL237.R = runPC; /* ADC_0 */
    MC_ME.PCTL239.R = runPC; /* SGEN_0 */
    MC_ME.PCTL245.R = runPC; /* ETIMER_2 */
    MC_ME.PCTL247.R = runPC; /* ETIMER_0 */
    MC_ME.PCTL251.R = runPC; /* CTU_0 */
    MC_ME.PCTL255.R = runPC; /* PWM_0 */

    /* Enabling clocks for RUN0 */
    const typeof(MC_ME.RUN0_MC) val = {
            .B.PDO=1,
            .B.MVRON=1,
            .B.FLAON=3,
            .B.XOSCON=1,
            .B.PLL0ON=1,
            .B.PLL1ON=1,
            .B.IRCON=1,
            .B.SYSCLK=4      /* PLL1 ("secondary" PLL as SYS_CLK) */
    };
    MC_ME.RUN0_MC.R = val.R;

    _debug_("Switching to RUN0\n");
    _debug_("  SYSCLK=4 (secondary PLL = PLL1) \n");
    Mcu_Arc_SwitchMode(MODE_RUN0);

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






