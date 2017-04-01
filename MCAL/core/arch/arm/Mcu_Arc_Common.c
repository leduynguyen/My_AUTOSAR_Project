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


/** @tagSettings DEFAULT_ARCHITECTURE=PPC|MPC5607B|MPC5645S */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */


/* ----------------------------[includes]------------------------------------*/
#include <stdio.h> /*lint !e829  +headerwarn option was previously issued for header 'stdio.h' require for printf */
#include "Cpu.h"
#include "Mcu.h"
#include "Mcu_Arc.h"
#include "irq.h"

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

/**
 * Reads Core info
 * @param pvr
 * @return
 */
const cpu_info_t *Mcu_Arc_IdentifyCpu(uint32 pvr)
{
    uint32 i = 0;

    while( cpu_info_list[i].name != NULL  ) {
        if (cpu_info_list[i].pvr == pvr) {
            return &cpu_info_list[i];
        }
        i++;
    }

    return NULL;
}

/**
 * Reads Core info
 * @param pvr
 * @return
 */
const core_info_t *Mcu_Arc_IdentifyCore(uint32 pvr)
{
    uint32 i = 0;

    while( core_info_list[i].name != NULL  ) {
        if (core_info_list[i].pvr == pvr) {
            return &core_info_list[i];
        }
        i++;
    }

    return NULL;
}


/*lint -save -e586   MISRA 2012 21.6 (req)
 * Allow standard library functions to be used as this function is used for tests only.
 */


void Mcu_Arc_PrintInfo( void )
{
    uint32 i = 0;

    while( cpu_info_list[i].name != NULL  ) {
        printf( "CPU: %s\n"
                "  Info: %s\n",cpu_info_list[i].name, cpu_info_list[i].info );
        i++;
    }

    i = 0;
    while( core_info_list[i].name != NULL  ) {
        printf("  Core: - %s %10s\n",core_info_list[i].name, core_info_list[i].info  );
        i++;
    }

    printf("        - Calculated Core Freq: %d [Hz])\n",Mcu_Arc_GetSystemClock());

}
/*lint -restore */

