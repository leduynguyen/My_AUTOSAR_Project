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

/** @tagSettings DEFAULT_ARCHITECTURE=PPC|MPC5607B|MPC5645S */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#define STATE_NORMAL    0
#define STATE_CONFIG    1
#define STATE_ALARM     2
#define STATE_FAULT     3

#define OP_NOOP             0
#define OP_CONFIG           1
#define OP_NORMAL           2
#define OP_READ_CFS         9
#define OP_READ_NCFS        10
#define OP_CLEARING_CFS     11


#define SPR_PIR 286
#define SPR_PVR 287


/* ----------------------------[includes]------------------------------------*/
#include "Cpu.h"
#include "Mcu.h"
#include "Mcu_Arc.h"
#include "irq.h"
#include "mpc55xx.h"

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/

#define WAIT_FOR_OP()  while( FCCU.CTRL.R & 0x1f ) {}

/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

/**
 * Get Fault Control and Collection Unit status
 */
uint32 Fccu_GetStat( void ) {
    FCCU.CTRL.B.OPR = 3;    /* NO key needed */
    while (FCCU.CTRL.B.OPS != 3) {};
    return FCCU.STAT.R;
}




#if defined(CFG_MCU_ARC_CLEAR_FCCU)

void Fccu_ClearCriticalStatusReg( uint32 regIndex, uint32_t val ) {
    FCCU.CFK.R        = 0x618B7A50;
    FCCU.CF_S[regIndex].R = val;    /* A write will trigger an OP11 */

    WAIT_FOR_OP();
}
#endif

/**
 * Executes one operation on the Initialize the Fault Control and Collection Unit.
 * @param op - operation to perfrom
 */
void Fccu_Op( uint32 operation ) {
    uint32 unlockVal = 0uL;

    /* Unlock first */
    switch(operation) {
        case OP_CONFIG: unlockVal = 0x913756AFuL; break;
        case OP_NORMAL: unlockVal = 0x825A132BuL; break;
        case 16u: unlockVal = 0x7ACB32F0uL; break;
        case 31u: unlockVal = 0x29AF8752uL; break;
        default:
            break;
    }

    /* unlock */
    if( unlockVal != 0uL ) {
        FCCU.CTRLK.R = unlockVal;
    }
    FCCU.CTRL.R = operation;

    WAIT_FOR_OP();
}




/**
 * Initialize the Fault Control and Collection Unit.
 *
 * Register naming:
 * _CF_      - Critical Fault
 * _NCF_     - Non-Critical Fault.
 * _CF_CFGx and _NCF_CFGx
 *           - 0 HW recoverable fault
 *             1 SW recoverable fault
 * _CFS_CFGx and _NCFS_CFGx
 *           - 00 No reset reaction
 *             01 Short functional reset (FAULT state reaction)
 *             10 Long functional reset (FAULT state reaction)
 *             11 No reset reaction
 */
void Fccu_Init( void ) {
    int i;
    uint32 state;

    state = Fccu_GetStat();
    if( state != STATE_NORMAL) {
        Mcu_Arc_SafeMode();
    }

#if defined(MPC5643L) || defined(CFG_SPC56XL70)
    /*
     * Clear status bits
     */
    for(i=0;i<sizeof(FCCU.CF_S)/sizeof(FCCU_CF_S_32B_tag);i++) {

        FCCU.CFK.R        = 0x618B7A50uL;
        FCCU.CF_S[i].R     = 0xFFFFFFFFuL;
        WAIT_FOR_OP();
    }

    for(i=0;i<sizeof(FCCU.NCF_S)/sizeof(FCCU_NCF_S_32B_tag);i++) {
        FCCU.NCFK.R        = 0xAB3498FEuL;
        FCCU.NCF_S[i].R     = 0xFFFFFFFFuL;
        WAIT_FOR_OP();
    }

    Fccu_Op(OP_CONFIG);


    /*
     * Setup as software faults
     */

    /* For CF */
    for(i=0;i<sizeof(FCCU.CF_CFG)/sizeof(FCCU_CF_CFG_32B_tag);i++) {
        FCCU.CF_CFG[i].R = 0xffffffffuL;
    }

    /* and for NCF */
    for(i=0;i<sizeof(FCCU.NCF_CFG)/sizeof(FCCU_NCF_CFG_32B_tag);i++) {
        FCCU.NCF_CFG[i].R = 0xffffffffuL;
    }
#endif

    /* Leave CFS and NCF as is */

    Fccu_Op(OP_NORMAL);
}

