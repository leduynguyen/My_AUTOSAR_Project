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

#include <assert.h>
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

/* From Table 9-6. Maximum clock frequencies AXBS master/slave */
#define CLK_SYS_CLOCK           160000000UL /* for core0 and core1 */
#define CLK_PBRIDGE_A            80000000UL
#define CLK_PBRIDGE_B            80000000UL
#define CLK_ENET_CLK             80000000UL
#define CLK_FRAY_CLK             80000000UL

/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/

/* ----------------------------[private variables]---------------------------*/
/*lint --e{753} OTHER  */
struct EccInitTableS {
    uint8 *start;
    uint32 length;
};
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


void Mcu_Arc_InitClockPost( const Mcu_ClockSettingConfigType *clockSettingsPtr )
{

	/* Configure PLL from XOSC, no frequency modulation: */
	/* F pll_ref (PLL input) = FXOSC
	 PREDIV = 1 (divide input clock by 1)
	 MFD    = 16 (range 10 to 150)
	 MFN = 0(default)
	 MFDEN = 1 (must be > MFN)
	 F vco range = 600-1200MHz (per MPC5748G Ref Man rev 1 section 26.4)
	 F vco = (F pll_ref / PREDIV ) x (MFD + MFN / MFDEN)

	 RFDPHI = 1 (divides Fvco by 2)
	 RFDPHI1 = 2 (secondary output clock)
	 F pll_phi = F vco   / 2**(RFDPHI + 1)
	*/
    uint32 pll_PREDIV = clockSettingsPtr->Mcu_Hw_ClockSettings->plldv_PREDIV;
    uint32 pll_MFD = clockSettingsPtr->Mcu_Hw_ClockSettings->plldv_MFD;
    uint32 pll_RFDPHI = clockSettingsPtr->Mcu_Hw_ClockSettings->plldv_RFDPHI;

    /* ensure that pll settings are within range */
    /*lint -save -e716 -e9036 OTHER required operation */
    assert((pll_PREDIV >=1) && (pll_PREDIV <= 6));
    assert((pll_MFD >=10) && (pll_MFD <= 150));
    assert((pll_RFDPHI >=1) && (pll_RFDPHI <= 32));
    /*lint -restore*/

    /* Select XOSC as PLL source */
    /*lint -save -e923 HARDWARE_ACCESS */
    MC_CGM.AC5_SC.B.SELCTL=1;

    /* Input clock predivider. */
    PLLDIG.PLLDV.B.PREDIV = pll_PREDIV;
    /* Loop multiplication factor divider. */
    PLLDIG.PLLDV.B.MFD = pll_MFD;
    /* PHI0 reduced frequency divider. */
    PLLDIG.PLLDV.B.RFDPHI  = pll_RFDPHI;

    /* Disable sigma delta modulation */
    PLLDIG.PLLFD.B.SMDEN = 1;

    /* Set MFDEN a nonzero value (0x1 here) */
    PLLDIG.PLLCAL3.B.MFDEN = 1;

    /* Mode entry module */
    MC_ME.ME.R = 0x000005FF;      /* Enable desired modes - all in this case */
    /*lint -restore*/
    /* DRUN config */
    /*lint -e{970,24,40,10,63,133,446,1058,1514,9018, 940) Seems lint can't handle typeof */
    const typeof(MC_ME.DRUN_MC) val1 = {
        .B.PDO=1,
        .B.MVRON=1,
        .B.FLAON=3,
        .B.FXOSCON=1,
        .B.PLLON=1,
        .B.FIRCON=1,
        .B.SYSCLK=2      /* PLL as SYS_CLK */
    };

    /* Set DRUN */
    /*lint -e754 -e923 HARDWARE_ACESSS */
    MC_ME.DRUN_MC.R = val1.R; /* DRUN cfg: PLLON=FXOSCON=FIRCON=1 SYSCLK=PLL*/

    /* switch to run mode */
    Mcu_Arc_SwitchMode(MODE_DRUN);

    /* Enable all peripherals for RUN0 mode */
    //*lint -e{10,40) Seems lint can't handle typeof */
    MC_ME.RUN_PC[0].R = 0x000000FE;

    /* Enabling clocks for RUN0 */
    /*lint --e{970,24,40,10,63,446,1058,1514,9018) OTHER Seems lint can't handle typeof */
    const typeof(MC_ME.RUN_MC[0]) val = {
        .B.PDO=1,
        .B.MVRON=1,
        .B.FLAON=3,
        .B.FXOSCON=1,
        .B.PLLON=1,
        .B.FIRCON=1,
        .B.SIRCON=1,     /* Needed by Watchdog */
        .B.SYSCLK=2      /* PLL as SYS_CLK */
    };

    /* Config RUN0 */
    /*lint -e{10,40) OTHER Seems lint can't handle typeof */
    MC_ME.RUN_MC[0].R = val.R;

    /* Switch to RUN 0 */
    Mcu_Arc_SwitchMode(MODE_RUN0);
}
/*lint -e{957} OTHER */
void Mcu_Arc_SetModePre(Mcu_ModeType mcuMode) {
    /*lint -e{920} STANDARDIZED_API General interface, the configPtr may be needed for other architectures */
    (void)mcuMode;
}

/*lint -e{957} OTHER */
void Mcu_Arc_SetModePost( Mcu_ModeType mcuMode)
{
    /*lint -e{920} STANDARDIZED_API General interface, the configPtr may be needed for other architectures */
    (void)mcuMode;
}






