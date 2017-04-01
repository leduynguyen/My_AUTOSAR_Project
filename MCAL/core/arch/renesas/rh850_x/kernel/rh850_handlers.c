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
#include <stdint.h>
#include "arc.h"
#include "asm_rh850.h"
/* ----------------------------[private define]------------------------------*/

#define DEBUG_EXCEPTIONS	1



/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/




void Exception_Handler( uint32_t exception ) {
    volatile uint32 fepc;
    volatile uint32 mea;
    volatile uint32 mei;

    switch(exception) {
    case  EXC_SYSERR:
        break;
    case  EXC_HVTRAP:
        break;
    case  EXC_FETRAP:
        break;
    case  EXC_TRAP0:
        break;
    case  EXC_TRAP1:
        break;
    case  EXC_RIE:
        break;
    case  EXC_FPP_FPI:
        break;
    case  EXC_UCPOP:
        break;
    case  EXC_MIP_MDP:
        break;
    case  EXC_PIE:
        break;
    case  EXC_DEBUG:
        break;
    case  EXC_MAE:
        /*
         * FEPC - Instruction of offending load/store
         * MEA  - Memory error address register, address we tried to access
         * MEI  - Memory error information register
         *
         */
        fepc = get_sr(2,0);
        mea = get_sr(6,2);
        mei = get_sr(8,2);
        while(1) {
            (void)fepc;
            (void)mea;
            (void)mei;
        };

    case  EXC_RFU:
        break;
    case  EXC_FENMI:
        break;
    case  EXC_FEINT:
        break;
    default:
        break;
    }

    Os_Arc_Panic(exception,NULL);
}

