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
 * Author: mahi
 *
 * Description:
 *
 */


/* ----------------------------[includes]------------------------------------*/


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
#if defined(USE_KERNEL)
#include "Os.h"
#endif

/* ----------------------------[private define]------------------------------*/

/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

#if defined(USE_FLS)
extern uint32 EccErrReg;
#endif

/* ----------------------------[private functions]---------------------------*/

#if defined(CFG_MCU_MMU)
void Mcu_Arc_InitMM( void ) {
    /* User: Setup TLBs if needed  */
    MM_TlbSetup( Mcu_Arc_ConfigData.tblTable );
}
#endif


void Mcu_Arc_InitPre( const Mcu_ConfigType *configPtr ) {
    (void)configPtr; //lint !e920 MISRA False positive. Allowed to cast pointer to void here.

}
/*
 * Called at a very early stage...
 */
void Mcu_Arc_InitPost( const Mcu_ConfigType *configPtr ) {
    (void)configPtr; //lint !e920 MISRA False positive. Allowed to cast pointer to void here.
#if defined(CFG_MCU_MMU)
    Mcu_Arc_InitMM();
#endif
}


/* ----------------------------[public functions]----------------------------*/

void Mcu_Arc_InitClockPre( const Mcu_ClockSettingConfigType *clockSettingsPtr ) {
    (void)clockSettingsPtr; //lint !e920 MISRA False positive. Allowed to cast pointer to void here.
}


void Mcu_Arc_InitClockPost( const Mcu_ClockSettingConfigType *clockSettingsPtr ) {
    (void)clockSettingsPtr; //lint !e920 MISRA False positive. Allowed to cast pointer to void here.
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



