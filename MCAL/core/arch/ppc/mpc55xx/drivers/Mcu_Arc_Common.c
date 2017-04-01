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


#define SPR_PIR 286
#define SPR_PVR 287


/** @tagSettings DEFAULT_ARCHITECTURE=PPC|MPC5607B|MPC5645S|MPC5748G */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */


/* ----------------------------[includes]------------------------------------*/
/*lint -e{829} OTHER*/
#include <stdio.h>
#include "Cpu.h"
#include "Mcu.h"
#include "Mcu_Arc.h"
#include "irq.h"
#include "mpc55xx.h"
#if defined(CFG_FCCU)
#include "Mcu_fccu.h"
#endif

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

#if 1
extern uint8 __ram_start[];
extern uint8 __SP_END[];

static void Mcu_Arc_InitECC(void) {

    /*lint -esym(9003,__ram_start, __SP_END) Need to be global */
    static const uint64 val = 0u;
    /*lint -e{946, 947, 732} */
    memset_uint64(__ram_start, &val, __SP_END - __ram_start);
}
#endif

#if !defined(CFG_SIMULATOR)
/**
 * Reads the CPU info, core and name.
 * @param pvr
 * @return
 */
static const cpu_info_t *Mcu_IdentifyCpu(uint32 pvr)
{
    uint32 i;
    uint32 num;

    const cpu_info_t *c =  Mcu_Arc_GetCpuInfoList(&num);
    /*lint -e{9008, 9049} OTHER to increase readability */
    for (i = 0; i < num; i++,c++) {
        if (c->pvr == pvr) {
            /*lint -e{904} OTHER to increase readability as 'c' is a pointer */
            return c;
        }
    }
    return NULL;
}

/**
 * Reads Core info
 * @param pvr
 * @return
 */
static const core_info_t *Mcu_IdentifyCore(uint32 pvr)
{
    uint32 i;
    uint32 num;

    const core_info_t *c =  Mcu_Arc_GetCoreInfoList(&num);
    /*lint -e{9008, 9049} OTHER to increase readability */
    for (i = 0; i < num; i++,c++) {
        if (c->pvr == pvr) {
            /*lint -e{904} OTHER to increase readability as 'c' is a pointer */
            return c;
        }
    }

    return NULL;
}

/*lint -save -e586   MISRA 2012 21.6 (req)
 * Allow standard library functions to be used as this function is used for tests only.
 */

void Mcu_Arc_PrintInfo( void )
{
    uint32 i;
    uint32 cnum;
    uint32 num;
    const cpu_info_t *cpu =  Mcu_Arc_GetCpuInfoList(&cnum);
    const core_info_t *core =  Mcu_Arc_GetCoreInfoList(&num);
    /*lint -e{705} OTHER required operation */
    printf( "CPU: %s\n"
            "  Cores: %d\n",cpu->name, cnum);

    for (i = 0; i < num; i++) {
        printf("  %10s %10s\n",core->name, core->info  ); /*lint !e516 STANDARD */
        core++;
    }
//    printf("  Actual Core Freq: %d [Hz]\n",Mcu_Arc_GetPeripheralClock(C_CPLLCLK));
}

/*lint -restore */



/**
 * Checks that it is possible to identify CPU and core. If not, this function will hang.
 * @return
 */
static uint32 Mcu_CheckCpu( void ) {
    uint32 pvr;

    const cpu_info_t *cpuType;
    const core_info_t *coreType;

    pvr = get_spr(SPR_PVR);  /*lint !e718 !e746 !e548 !e632 !e732 Defined in Cpu.h */
    cpuType = Mcu_IdentifyCpu(pvr);
    coreType = Mcu_IdentifyCore(pvr);

    if( (cpuType == NULL) || (coreType == NULL) ) {
        // Just hang
        /*lint -e{716,  9012, 9036} Ok, this is the intended behavior */
        while(TRUE) ;
    }

    return 0;
}
#endif


/**
 * Function that perform all necessary initialization needed to to run software, such as disabling watchdog,
 * init ECC RAM, setup exception vectors etc
 */
void Mcu_Arc_InitZero(void) {

    /********************************************************************************
     * NOTE
     *
     * This function will be called before BSS and DATA are initialized.
     * Ensure that you do not access any global or static variables before
     * BSS and DATA is initialized
     ********************************************************************************/
    Mcu_Arc_WdgExtendTimeout();

#if !defined(CFG_SIMULATOR)
    (void)Mcu_CheckCpu();
#endif

#if defined(USE_KERNEL)
    Irq_Init();
#endif

    Mcu_Arc_PlatformInit();

    Mcu_Arc_InitECC();

#if defined(CFG_MCU_CACHE_I)
    Cache_EnableI();
#endif
#if defined(CFG_MCU_CACHE_D) && !defined(USE_TTY_WINIDEA)
    Cache_EnableD();
#endif
#if defined(CFG_MCU_CACHE_U)
    Cache_EnableU();
#endif
#if defined(CFG_FCCU)
    Fccu_Init();
#endif
}

/*lint -e{9046} Keeping name */
/*lint -esym(9003, EccError) Cannot be defined at block scope since used by other module */
uint8 EccError = 0u;

/**
 * Reads the ECC erros and clears it
 * @param err
 */
void Mcu_Arc_GetECCError( uint8 *err ) {

    *err = EccError;
    /* Clear stored  */
    EccError = 0u;
}


#if defined(CFG_MPC5643L) || defined(CFG_MPC5645S) || defined(CFG_SPC56XL70) || defined(CFG_MPC560X) || defined(CFG_MPC5744P) || defined(CFG_MPC5777M) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
void Mcu_Arc_SwitchMode( uint32 mode ) {

#ifndef ME
#define ME MC_ME
#endif
     /* Enter RUN0 Mode & Key */
    /*lint -save -e923 HARDWARE_ACCESS */
     ME.MCTL.R = 0x00005AF0 | (mode << 28uL); /*lint !e9027 Setting upper four bits, alternative does not make sense */
     /* Enter RUN0 Mode & Inverted Key */
     ME.MCTL.R = 0x0000A50F | (mode << 28uL); /*lint !e9027 Setting upper four bits, alternative does not make sense*/
     /*lint -restore */
#if !defined(CFG_SIMULATOR)
     /* Wait for mode transition to complete */
     /*lint -save -e923 HARDWARE_ACCESS */
     while (ME.GS.B.S_MTRANS != 0u) {}
     /* Verify RUN0 is the current mode */
     while(ME.GS.B.S_CURRENTMODE != mode) {}
     /*lint -restore */
#endif
}

uint32 Mcu_Arc_GetMode( void ) {
    /*lint -e{923} HARDWARE_ACCESS */
    return ME.GS.B.S_CURRENTMODE;
}
#endif



