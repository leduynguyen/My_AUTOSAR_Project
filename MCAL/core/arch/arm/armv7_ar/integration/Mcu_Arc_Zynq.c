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
/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ */

/* ----------------------------[includes]------------------------------------*/
#include "Std_Types.h"
#include "Mcu.h"
#include "Mcu_Arc.h"

/* ----------------------------[includes]------------------------------------*/
/* ----------------------------[private define]------------------------------*/

#define NUM_PAGE_TABLE_ENTRIES      4096U /* 1 entry per 1MB, so this covers 4G address space */
#define CACHE_DISABLED              0x12U
#define SDRAM_START                 0x80000000UL
#define SDRAM_END                   0x8fffffffUL
#define CACHE_WRITEBACK             0x1eU

#define S_NGLOBAL                   (1UL << 17U)
#define S_SHARED                    (1UL << 16U)
#define S_APX                       (1UL << 15U)
#define S_TEX1                      (1UL << 12U)
#define S_AP0                       (1UL << 10U)
#define S_AP1                       (1UL << 11U)
#define S_PARITY                    (1UL << 9U)
#define S_XN                        (1UL << 4U)
#define S_CACHE                     (1UL << 3U)
#define S_BUFFER                    (1UL << 2U)

#define IS_A_SECTION                (1UL << 1U)

#define S_PERIPHERAL                (S_TEX1 | S_BUFFER | S_AP0 | S_AP1 | IS_A_SECTION)
#define S_NORMAL                    (S_TEX1 | S_CACHE | S_BUFFER | S_AP0 | S_AP1 | IS_A_SECTION)
#define S_SHARED_NORMAL             (S_NORMAL | S_SHARED)
#define S_SHARED_DEVICE             (S_BUFFER | S_SHARED | S_AP0 | S_AP1 | IS_A_SECTION | S_XN)
#define S_SHARED_STRONGLY_ORDERED   (S_SHARED | S_AP0 | S_AP1 | IS_A_SECTION)
#define S_NO_ACCESS                 (IS_A_SECTION)


#define PAGE_TABLE_CNT              4096U


/* ----------------------------[private macro]-------------------------------*/


/* ----------------------------[private typedef]-----------------------------*/

typedef struct MmuMapS {
    uint32 addr;
    uint32 entry;
} MmuMapType;

/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

const cpu_info_t cpu_info_list[] = {
    {
    .name = "zynq_zc702",
    .pvr = 0,
    .info = "",
    },
    {
    .name = NULL,
    }
};

/* The supported cores. */
const core_info_t core_info_list[] = {
    {
        .name = "Cortex-A9",
        .pvr = 0,
        .info = "",
    },
    {
        .name = NULL,
    }

};

#if defined(CFG_MMU_SETUP)

/*lint -esym( 9003, MMU_PageTable) Defined module wide for readability */


/* 1MB entries all over the 4GB space */
/* MUST BE 16KB aligned */
__balign(0x4000) __attribute__ ((section (".mmu_table"))) uint32 MMU_PageTable[PAGE_TABLE_CNT];

/*
 * Want to setup 4096 "Section" short-descriptor format entries.
 * The entries look like this:
 *
 *   3                     2                   1
 *   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 *  | Section Base Address  |N|0|n|S|A| TEX |AP0|0| Domain|X|C|B|1|0|
 *                           S   G   P                     N
 *                                   2
 *
 *                          |       |       |       |       |       |
 *                          |0|0|0|0|0|0|0|1|1|1|0|0|0|0|0|0|1|1|1|0|
 *
 *  TEX[2:0], C, B  - Memory Attributes
 *
 * AP[2:0]          011     Read/Write Read/Write Full access
 * TEX[2:0],C,B     001 0 0 Outer and Inner Non-cacheable.
 *
 *                          |       |       |       |       |       |
 *                          |0|0|0|0|0|0|0|1|1|1|0|0|0|0|0|0|0|0|1|0|  -> 1c02
 *
 *
 * Other registers:
 *   TTBR0 - TTBR0 holds the base address of translation table 0, and information
 *            about the memory it occupies
 *
 *   Level 1 Page Tables:   (CP15,c2)
 *    -  master page table, which divides the full 4 GB address space into
 *       4,096 equally sized 1 MB sections
 */

/*lint -esym( 9003, MmuMap) Defined module wide for readability */
const MmuMapType MmuMap[] = {
        { .addr = 0x00000000UL, .entry = 0x1c02 }   ,                 /* OCM RAM + other */
#if defined(USE_ETH)
        { .addr = 0x00100000UL, .entry = S_SHARED_DEVICE },           /* non-cached space 1 mega        */
        { .addr = 0x00200000UL, .entry = S_NORMAL },                  /* rest of 1 Gig DDR           */
#else
        { .addr = 0x00100000UL, .entry = S_NORMAL },                  /* 1 Gig DDR           */
#endif
        { .addr = 0x40000000UL, .entry = S_NO_ACCESS },               /* M_AXI_GP0    */
        { .addr = 0x80000000UL, .entry = S_NO_ACCESS },               /* M_AXI_GP1    */
        { .addr = 0xc0000000UL, .entry = S_SHARED_DEVICE } ,          /* Peripherals      */
        { .addr = 0xfff00000UL, .entry = S_NORMAL },                  /* OCM RAM                        */
        { .addr = 0x0UL, .entry = 0x0UL },                              /* Termination */

};

/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/



/* Refs:
 * ArchRM: Chapter B4 System Control Registers in a VMSA implementation
 * ArchRM: B3.17.2   Full list of VMSA CP15 registers, by coprocessor register number
 */

static void setupPageTable( void )
{
    uint32 i;
    uint32 j;
    uint32 pCnt = 0;
    uint32 entries;


    /* Create the 4096 entries big MMU_PageTable[] in RAM from MmuMap */
    for (i = 0UL; i < ((sizeof(MmuMap)/sizeof(MmuMapType))-1UL); i++) {
        entries = (MmuMap[i+1UL].addr - MmuMap[i].addr)/0x100000UL;
        /* Increase in 1MB pages */
        for(j=0UL; j < entries ;j++ ) {
            /* Virtual = Physical mapping */
            MMU_PageTable[pCnt] = (pCnt << 20U) | MmuMap[i].entry;
            pCnt++;
        }
    }
}
#endif

void Mcu_Arc_PlatformInit( void ) {
#if defined(CFG_MMU_SETUP)
    setupPageTable();
#endif
}


