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


#include "os_i.h"
#include "asm_ppc.h"
#include "mpc55xx.h"
#include "os_mm.h"


#if (OS_SC3 == STD_ON ) || (OS_SC4 == STD_ON )
/* Masters:
 * 0 - Z1 instr/data
 * 1 - Z0
 * 2 - DMA
 * 3 - FlexRAY
 *
 * Slaves:
 * 0 - Flash, etc ( mpu1)
 * 3 - SRAM (mpu2??)
 */

void Os_MMInit( void ) {

    /* Supervisor/User code */
    MPU.RGD[0].WORD0.R = 0x0;                 /* start */
    MPU.RGD[0].WORD1.R = 0x7ffff;            /* end */
    MPU.RGD[0].WORD2.R = 0xffffffff;            /* access */
    MPU.RGD[0].WORD3.R = 1;

    /* Supervisor data (.bss + .data) + User data (Read ONly)*/
    MPU.RGD[1].WORD0.R = 0x40000000;            /* start */
    MPU.RGD[1].WORD1.R = 0x4fffffff;            /* end */
    MPU.RGD[1].WORD2.R =    ((SM_RWX+UM_R)<<12) +      /* master 2 (DMA)*/
                            ((SM_RWX+UM_R)<<6) +       /* master 1 (Z0)*/
                            (SM_RWX+UM_R);           /* master 0 (Z1) */
    MPU.RGD[1].WORD3.R = 1;


    /* Supervisor I/O */
    MPU.RGD[2].WORD0.R = 0xfc000000;         /* start */
    MPU.RGD[2].WORD1.R = 0xffffffff;            /* end */
    MPU.RGD[2].WORD2.R =    (SM_RWX<<12) +      /* master 2 (DMA)*/
                            (SM_RWX<<6) +       /* master 1 (Z0)*/
                            (SM_RWX);           /* master 0 (Z1) */
    MPU.RGD[2].WORD3.R = 1;


    /* Enable MPU */
    MPU.CESR.R = 1;
}


/**
 *
 *
 * @param pcbPtr
 */
void Os_MMSetUserMode( OsTaskVarType *pcbPtr ) {

    /* 0 and 1 entries already occupied. */

    /* User Mode, stack */
    MPU.RGD[3].WORD0.R = pcbPtr->regs[MPU0_REG_TASK_STACK_START];      /* start */
    MPU.RGD[3].WORD1.R = pcbPtr->regs[MPU0_REG_TASK_STACK_END];      /* end */
    MPU.RGD[3].WORD2.R = (UM_RW<<6) +       /* master 1 */
                          (UM_RW);           /* master 0 */
    MPU.RGD[3].WORD3.R = 1;

    /* User Mode, .data */
    MPU.RGD[4].WORD0.R = pcbPtr->regs[MPU0_REG_TASK_DATA_START];            /* start */
    MPU.RGD[4].WORD1.R = pcbPtr->regs[MPU0_REG_TASK_DATA_END];            /* end */
    MPU.RGD[4].WORD2.R = (UM_RW<<6) +       /* master 1 */
                         (UM_RW);           /* master 0 */

    MPU.RGD[4].WORD3.R = 1;

    /* User Mode, .bss */
    MPU.RGD[5].WORD0.R = pcbPtr->regs[MPU0_REG_TASK_BSS_START];            /* start */
    MPU.RGD[5].WORD1.R = pcbPtr->regs[MPU0_REG_TASK_BSS_END];            /* end */
    MPU.RGD[5].WORD2.R = (UM_RW<<6) +       /* master 1 */
                          (UM_RW);           /* master 0 */

    MPU.RGD[5].WORD3.R = 1;

}

#endif /* (OS_SC3 == STD_ON ) || (OS_SC4 == STD_ON ) */
