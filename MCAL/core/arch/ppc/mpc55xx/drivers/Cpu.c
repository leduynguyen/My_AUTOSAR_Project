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
 * Part of Release:
 *   Non-Autosar
 *
 * Description:
 *   Implements cache routines.
 */

/* ----------------------------[includes]------------------------------------*/
#include "Cpu.h"

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/



void Cache_Invalidate( void ) {

    /* Wait for it to clear */
    while( ( get_spr(SPR_L1CSR0) & L1CSR0_CINV ) != 0 ) {}

    msync();
    isync();
    set_spr(SPR_L1CSR0, L1CSR0_CINV );

    /* Wait for it to clear */
    while( ( get_spr(SPR_L1CSR0) & L1CSR0_CINV ) != 0 ) {}
}

/**
 * Unified cache enable.
 * MPC5668
 */
void Cache_EnableU( void ) {
    uint32 l1csr0;

    /* Reset  does  not  invalidate  the  cache  lines;  therefore,  the  cache  should  be  invalidated
     * explicitly after a hardware reset.
     */
    Cache_Invalidate();

    l1csr0 = get_spr(SPR_L1CSR0);
    //lint --e(778,845)    lint exception  Allow usage of constants to result in zero or constant value
    l1csr0 |= L1CSR0_CE;		/* enable cache */
    msync();
    isync();
    set_spr(SPR_L1CSR0,l1csr0);
}

void Cache_EnableI( void ) {
    uint32 l1csr1;

    /* Reset  does  not  invalidate  the  cache  lines;  therefore,  the  cache  should  be  invalidated
     * explicitly after a hardware reset.
     */
    /* Wait for it to clear */
    while( ( get_spr(SPR_L1CSR1) & L1CSR0_CINV ) != 0 ) {}

    msync();
    isync();
    set_spr(SPR_L1CSR1, L1CSR0_CINV );

    /* Wait for it to clear */
    while( ( get_spr(SPR_L1CSR1) & L1CSR0_CINV ) != 0 ) {}

    l1csr1 = get_spr(SPR_L1CSR1);
    //lint --e(778,845)    lint exception  Allow usage of constants to result in zero or constant value
    l1csr1 |= L1CSR0_CE;        /* enable cache */
    msync();
    isync();
    set_spr(SPR_L1CSR1,l1csr1);
}

void Cache_EnableD( void ) {
    Cache_EnableU();
}

