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
/** @tagSettings DEFAULT_ARCHITECTURE=RH850F1H */

/* ----------------------------[includes]------------------------------------*/


#include <string.h>
#include "Std_Types.h"
#include "SchM_Mcu.h"
#include "Mcu.h"
#include "Mcu_Internal.h"
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
#include "rh850.h"

//#define USE_LDEBUG_PRINTF 1
#if defined(USE_LDEBUG_PRINTF)
#include "debug.h"
#endif

/* ----------------------------[private define]------------------------------*/

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(_x)  (sizeof(_x)/sizeof((_x)[0]))
#endif

/* ----------------------------[private macro]-------------------------------*/

#define PROTECTED_WRITE(preg,reg,value)   (preg)=0xa5uL;\
                                          (reg)=(value);\
                                          (reg)=~(value);\
                                          (reg)=(value);

/* ----------------------------[private typedef]-----------------------------*/

typedef struct {
  char *name;
  uint32 pvr;
  const char *info;
} core_info_t;

typedef struct {
  char *name;
  uint32 pvr;
} cpu_info_t;

/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

const cpu_info_t cpu_info_list[] = {
    {
    .name = "RH850F1H",
    .pvr = 0,
    },
};

const core_info_t core_info_list[] = {
    {
    .name = "RH850G3M",
    .pvr = 0,
    .info = "Max Freq: 120Mhz, ICache: Yes (8KB)",
    },
};


/* ----------------------------[private functions]---------------------------*/

static uint32 getClockReferencePointFrequency( Mcu_ClockType clockType ) {
    return Mcu_Global.config->McuClockSettingConfig[clockType].McuClockReferencePointFrequency;
}


static void GetAndClearResetCause(void) {
    Mcu_ResetType resetReason;

    /*lint -e{970} Note: Use of modifier or type 'unsigned', 'long', etc outside of a typedef. OK, comes from a Renesas h-file. */
    /*lint -e{9048} Note: Unsigned integer literal without a 'U' suffix. OK, comes from a Renesas h-file. */
    /*lint -e{923} Note: Cast from unsigned int to pointer. OK, comes from a Renesas h-file. */
    uint32 status = RESF;

    /* Get RAW reset value and resetReson value and save it */
    Mcu_Global.rawResetvalue = status;

    if( (status & 1u) == 1u ) {					            /* RESF0  */
        resetReason = MCU_SW_RESET;
    } else if( (status & ((1uL<<1u) + (1uL<<2u) + (1uL<<11u))) > 0) {	/* WDTA0 + WDTA1 + WDTA2 */
        resetReason = MCU_WATCHDOG_RESET;
    } else if( (status & (1uL<<9u)) == (1uL<<9u) ) {						/* POR */
        resetReason = MCU_POWER_ON_RESET;
    } else if( (status & (1uL<<8u)) == (1uL<<8u) ) {
        resetReason = MCU_EXT_RESET;
    } else {
        resetReason = MCU_RESET_UNDEFINED;
    }

    /*lint -e{970} Note: Use of modifier or type 'unsigned', 'long', etc outside of a typedef. OK, comes from a Renesas h-file. */
    /*lint -e{9048} Note: Unsigned integer literal without a 'U' suffix. OK, comes from a Renesas h-file. */
    /*lint -e{923} Note: Cast from unsigned int to pointer. OK, comes from a Renesas h-file. */
    /* Clear */
    RESFC = status;

    /* @req SWS_Mcu_00005 */
    Mcu_Global.resetReason = resetReason;
}

/*lint -e{715} Info: Symbol 'ConfigPtr' not referenced.
 * This is OK. For other implementations than RH850F1H the variable might be used. */
void Mcu_Hw_Init( const Mcu_ConfigType *ConfigPtr ) {
    GetAndClearResetCause();
}


#if ( MCU_NO_PLL == STD_OFF )

Std_ReturnType Mcu_Hw_DistributePllClock(void)
{
    /* There is no such function in the chip */
    return E_OK;
}

/**
 * Init PLL's
 *
 * @return
 */
static void initPll( const Mcu_ClockSettingConfigType *cPtr ) {

    uint32 mosccVal;
    uint32 pll0fvvVal;

    if( cPtr->McuClockReferencePointFrequency > 200000000uL ) {
        mosccVal = 0;
    } else if( cPtr->McuClockReferencePointFrequency > 160000000uL ) {
        mosccVal = 1;
    } else {
        mosccVal = 2;
    }

    /* PLL0 range check */
    CONFIG_ASSERT( (cPtr->Mcu_Hw_ClockSettings->pll0_VCOOUT <= 480000000uL) &&
            (cPtr->Mcu_Hw_ClockSettings->pll0_VCOOUT >= 320000000uL) );

    ASSERT( (cPtr->Mcu_Hw_ClockSettings->pll1_VCOOUT <= 480000000uL) &&
            (cPtr->Mcu_Hw_ClockSettings->pll1_VCOOUT >= 240000000uL) );


    if( cPtr->Mcu_Hw_ClockSettings->pll0_VCOOUT >= 440000000uL ) {
        pll0fvvVal = 3;
    } else if( cPtr->Mcu_Hw_ClockSettings->pll0_VCOOUT >= 400000000uL ) {
        pll0fvvVal = 2;
    } else if( cPtr->Mcu_Hw_ClockSettings->pll0_VCOOUT >= 360000000uL ) {
        pll0fvvVal = 1;
    } else if( cPtr->Mcu_Hw_ClockSettings->pll0_VCOOUT >= 320000000uL ) {
        pll0fvvVal = 0;
    } else {
       ASSERT(0);
    }

    /*lint -save -e970 Note: Use of modifier or type 'unsigned', 'long', etc outside of a typedef. OK, comes from a Renesas h-file. */
    /*lint -save -e9048 Note: Unsigned integer literal without a 'U' suffix. OK, comes from a Renesas h-file. */
    /*lint -save -e923 Note: Cast from unsigned int to pointer. OK, comes from a Renesas h-file. */

    /*--  Enable MainOSC ---  */
    MOSCC  = mosccVal;                      /* Crystal value select */
    MOSCST = 0xffffuL;                      /* Stabilization value */
    PROTECTED_WRITE(PROTCMD0,MOSCE,0x01u);   /* Enable MainOSC */
    /* Wait until it's active */
    while ((MOSCS&0x04u) != 0x4u) {};

    /* --- Setup PLL0 --- */
    PLL0C = cPtr->Mcu_Hw_ClockSettings->pll0_PLLxC  + (pll0fvvVal<<29uL);
    PROTECTED_WRITE(PROTCMD1,PLL0E,0x01u);   /* Enable */
    while((PLL0S&0x04u) != 0x04u) {};            /* Check active */

    /* --- Setup PLL1 --- */
    PLL1C=cPtr->Mcu_Hw_ClockSettings->pll1_PLLxC;
    PROTECTED_WRITE(PROTCMD1,PLL1E,0x01u);
    while((PLL1S&0x04u) != 0x04u) {};

    /*lint -restore -e923 */
    /*lint -restore -e9048 */
    /*lint -restore -e970 */
}

Std_ReturnType Mcu_Hw_InitClock( const Mcu_ClockSettingConfigType *clkPtr ) {

    initPll(clkPtr);

    /* Setup
     * - CPU clock
     * - CAN clock to MainOSC (in case we want modulation on)
     */


    /*lint -save -e970 Note: Use of modifier or type 'unsigned', 'long', etc outside of a typedef. OK, comes from a Renesas h-file. */
    /*lint -save -e9048 Note: Unsigned integer literal without a 'U' suffix. OK, comes from a Renesas h-file. */
    /*lint -save -e923 Note: Cast from unsigned int to pointer. OK, comes from a Renesas h-file. */

    /*----  CPU Clock ----*/
    PROTECTED_WRITE(PROTCMD0,CKSC_CPUCLKD_CTL,0x01u);    /* Divide by 1 (default) */
    while(CKSC_CPUCLKD_ACT!=0x01u) {};

    /* Select CPUCLK from EMCLK, MainOSC and CPLLCLK(PLL0) -> CPLLCLK */
    PROTECTED_WRITE(PROTCMD1,CKSC_CPUCLKS_CTL,0x03u);
    while(CKSC_CPUCLKS_ACT!=0x03u) {};

    /*----  CAN Clock ----*/
    /* Set to MainOSC */
    PROTECTED_WRITE(PROTCMD1,CKSC_ICANS_CTL,0x1u);
    while(CKSC_ICANS_ACT!=0x1u) {};

    /* Set divider to 1 */
    PROTECTED_WRITE(PROTCMD1,CKSC_ICANOSCD_CTL,0x1u);
    while(CKSC_ICANOSCD_ACT!=0x1u) {};

    /*lint -restore -e923 */
    /*lint -restore -e9048 */
    /*lint -restore -e970 */

    return E_OK;
}

#endif /*  ( MCU_NO_PLL == STD_OFF ) */


//-------------------------------------------------------------------

/* !req SWS_Mcu_00008 */
Mcu_PllStatusType Mcu_Hw_GetPllStatus(void)
{
    /* There is no such function in the chip */
    return MCU_PLL_LOCKED;
}


#if ( MCU_PERFORM_RESET_API == STD_ON )
/* @req SWS_Mcu_00143 */
/* !req SWS_Mcu_00144 */
void Mcu_Hw_PerformReset(void)
{
    /*lint -save -e970 Note: Use of modifier or type 'unsigned', 'long', etc outside of a typedef. OK, comes from a Renesas h-file. */
    /*lint -save -e9048 Note: Unsigned integer literal without a 'U' suffix. OK, comes from a Renesas h-file. */
    /*lint -save -e923 Note: Cast from unsigned int to pointer. OK, comes from a Renesas h-file. */
    PROTECTED_WRITE(PROTCMD0,SWRESA,0x01uL);
    /*lint -restore -e923 */
    /*lint -restore -e9048 */
    /*lint -restore -e970 */
}
#endif

//-------------------------------------------------------------------


/*lint -e{715} Info: Symbol 'mcuMode' not referenced.
 * This is OK. For other implementations than RH850F1H the variable might be used. */
void Mcu_Hw_SetMode( Mcu_ModeType mcuMode)
{

}

/*lint -save -e970 Note: Use of modifier or type 'unsigned', 'long', etc outside of a typedef. OK, comes from a Renesas h-file. */
/*lint -save -e9048 Note: Unsigned integer literal without a 'U' suffix. OK, comes from a Renesas h-file. */
/*lint -save -e923 Note: Cast from unsigned int to pointer. OK, comes from a Renesas h-file. */
static uint32 getCpuClk( Mcu_ClockType clockIdx ) {
    uint32 clock;
    uint32 clockSelect = CKSC_CPUCLKS_ACT;
    if( clockSelect == 1uL) {
        clock = 0;  /* MCU_ARC_EMCLK_FREQUENCY */
    } else if( clockSelect == 2uL ) {
        clock = getClockReferencePointFrequency(clockIdx);
    } else if( clockSelect == 3uL ) {
        /* C_CPLLCLK */
        clock = Mcu_Global.config->McuClockSettingConfig[clockIdx].Mcu_Hw_ClockSettings->pll0_Clk;
    } else {
        clock = 0;
    }
    return clock;
}
/*lint -restore -e923 */
/*lint -restore -e9048 */
/*lint -restore -e970 */

/*lint -save -e970 Note: Use of modifier or type 'unsigned', 'long', etc outside of a typedef. OK, comes from a Renesas h-file. */
/*lint -save -e9048 Note: Unsigned integer literal without a 'U' suffix. OK, comes from a Renesas h-file. */
/*lint -save -e923 Note: Cast from unsigned int to pointer. OK, comes from a Renesas h-file. */
uint32 Mcu_Arc_GetPeripheralClock(Mcu_Arc_PeriperalClock_t type) {
    uint32 clock;
    uint32 divider = 1uL;

    Mcu_ClockType clockIdx = Mcu_Global.config->McuDefaultClockSettings;

    /* Read clock source (CKSC_xxS_ACT) and dividers (CKSC_xxD_ACT) */
    switch(type) {
        /* Directly from the PLLs */
        case C_CPLLCLK:
            /* PLL0 */
            clock = Mcu_Global.config->McuClockSettingConfig[clockIdx].Mcu_Hw_ClockSettings->pll0_Clk;
            break;
        case C_PPLLCLK:
            /* PLL1 */
            clock = Mcu_Global.config->McuClockSettingConfig[clockIdx].Mcu_Hw_ClockSettings->pll1_Clk;
            break;
        case C_PPLLCLK2:
            /* PLL1/2 */
            clock = Mcu_Global.config->McuClockSettingConfig[clockIdx].Mcu_Hw_ClockSettings->pll1_Clk;
            divider = 2;
            break;

        /* Clock Domain Names */
        case C_AWO_WDTA:
            break;
        case C_AWO_TAUJ:

            /*lint -save -e9013 Note: No 'else' at end of 'if ... else if' chain. OK, all allowed values are checked except for
             * disabled (CKSC_ATAUJS_ACT == 0) for which clock will be 0 anyway. */
            if( CKSC_ATAUJS_ACT == 1u ) {
                clock = MCU_ARC_HS_INT_OSC_FREQUENCY;
            } else if( CKSC_ATAUJS_ACT == 2u ) {
                clock = getClockReferencePointFrequency(clockIdx);
            } else if( CKSC_ATAUJS_ACT == 3u ) {
                clock = MCU_ARC_LS_INT_OSC_FREQUENCY;
            } else if( CKSC_ATAUJS_ACT == 4u ) {
                /* C_PPLLCLK2 */
                clock = Mcu_Global.config->McuClockSettingConfig[clockIdx].Mcu_Hw_ClockSettings->pll1_Clk / 2;
            }
            /*lint -restore -e9013 */

            divider = 1uL<<(CKSC_ATAUJD_ACT - 1uL);
            break;
        case C_AWO_RTCA:
            break;
        case C_AWO_ADCA:
            break;
        case C_AWO_FOUT:
            break;
        case C_CPUCLK:
            clock = getCpuClk( clockIdx );
            break;
        case C_CPUCLK2:
            clock = getCpuClk( clockIdx );
            divider = 2;
            break;
        case C_CPUCLK4:
            clock = getCpuClk( clockIdx );
            divider = 4;
            break;
        case C_ISO_CPUCLK:
            clock = getCpuClk( clockIdx );
            divider = 1uL<<(CKSC_ATAUJD_ACT - 1uL);
            break;
        case C_ISO_PERI1:
            /* Unit: TAUD0, TAUJ1, ENCA0, TAPA0, PIC0 */
            /* No divider for IPERI1 itself, the divider is from C_CPUCLK2. */
            /*lint -save -e9013 Note: No 'else' at end of 'if ... else if' chain. OK, all allowed values are checked except for
             * disabled (CKSC_IPERI1S_ACT == 0) for which clock will be 0 anyway. */
            if( CKSC_IPERI1S_ACT == 1 ) {
                /* C_CPUCLK2) */
                clock = getCpuClk( clockIdx );
                divider = 2;
            } else if( CKSC_IPERI1S_ACT == 2 ) {
                /* C_PPLLCLK */
                clock = Mcu_Global.config->McuClockSettingConfig[clockIdx].Mcu_Hw_ClockSettings->pll1_Clk;
            }
            /*lint -restore -e9013 */

            break;
        case C_ISO_PERI2:
            /* No divider for IPERI2 itself, the divider is from C_CPUCLK2 or C_PPLLCLK2. */
            /*lint -save -e9013 Note: No 'else' at end of 'if ... else if' chain. OK, all allowed values are checked except for
             * disabled (CKSC_IPERI2S_CTL == 0) for which clock will be 0 anyway. */
            if( CKSC_IPERI2S_ACT == 1 ) {
                /* C_CPUCLK2 */
                clock = getCpuClk( clockIdx );
                divider = 2;
            } else if( CKSC_IPERI2S_ACT == 2 ) {
                /* C_PPLLCLK2 */
                clock = Mcu_Global.config->McuClockSettingConfig[clockIdx].Mcu_Hw_ClockSettings->pll1_Clk;
                divider = 2;
            }
            /*lint -restore -e9013 */
            break;
        case C_ISO_LIN:
            break;
        case C_ISO_ADCA:
            break;
        case C_ISO_CAN:
            /* Unit: RS-CANn */
            /* No divider for ICAN itself, the divider comes from C_PPLLCLK and C_CPUCLK2. */
            /*lint -save -e9013 Note: No 'else' at end of 'if ... else if' chain. OK, all allowed values are checked except for
             * disabled (CKSC_ICANS_ACT == 0) for which clock will be 0 anyway. */
            if( CKSC_ICANS_ACT == 1 ) {
                clock = getClockReferencePointFrequency(clockIdx);
            } else if( CKSC_ICANS_ACT == 2 ) {
                /* C_PPLLCLK */
                clock = Mcu_Global.config->McuClockSettingConfig[clockIdx].Mcu_Hw_ClockSettings->pll1_Clk;
            } else if( CKSC_ICANS_ACT == 3 ) {
                /* C_CPUCLK2 */
                clock = getCpuClk( clockIdx );
                divider = 2;
            }
            /*lint -restore -e9013 */
            break;
        case C_ISO_CANOSC:
            /* Unit: RS-CANn */
            /* No source register */
            divider = CKSC_ICANOSCD_ACT;
            break;
        case C_ISO_CSI:
            break;
        case C_ISO_IIC:
            break;
        default:
            break;
    }

    return clock/divider;
}
/*lint -restore -e923 */
void Mcu_Arc_PrintInfo( void )
{
    uint32 i;
    printf( "CPU: %s\n"
            "  Cores: %d\n",cpu_info_list[0].name, sizeof(core_info_list)/sizeof(core_info_t));
    for (i = 0; i < ARRAY_SIZE(core_info_list); i++) {
        printf("  %10s %10s\n",core_info_list[i].name, core_info_list[i].info  );
    }
    printf("  Actual Core Freq: %d [Hz]\n",Mcu_Arc_GetPeripheralClock(C_CPLLCLK));
}

void Mcu_Arc_InitZero(void)
{

}

