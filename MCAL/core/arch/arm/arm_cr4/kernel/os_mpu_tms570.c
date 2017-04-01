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
//#include "asm_ppc.h"
//#include "mpc55xx.h"
#include "os_mm.h"


#if 1 // (OS_SC3 == STD_ON ) || (OS_SC4 == STD_ON )
/* Masters:
 * 0 - z4d_0 and z4d_1 instruction
 * 1 - z4d_0 and z4d_1 load/store
 * 2 - DMA_0
 * 3 - FlexRAY
 *
 * Slaves:
 * 0 - PFLASH_0_PORT_0, PFLASH_1_PORT_1
 * 1 - --
 * 2 - --
 * 3 - SRAMC_0, SRAMC_1
 *
 */


#define _SIZE_1M        (0x100000)
#define _SIZE_2M        (0x200000)
#define _SIZE_192K      (0x30000)


/**
 *
 * @param region
 * @param baseAddr
 * @param sizeEnable
 * @param accessControl
 */
void WriteRegion(uint32 region, uint32 baseAddr, uint32 size, uint32 accessControl ) {

//    printf("r=%x base=%x, sizeCtrl=%x, ac=%x\n",region, baseAddr, size, accessControl);

    ASSERT((baseAddr & 0x1fUL) == 0UL );
    __asm volatile ("mcr p15, 0, %0, c6, c2, 0" : : "r" (region));
    __asm volatile ("mcr p15, 0, %0, c6, c1, 0" : : "r" (baseAddr));
    __asm volatile ("mcr p15, 0, %0, c6, c1, 4" : : "r" (accessControl));
    __asm volatile ("mcr p15, 0, %0, c6, c1, 2" : : "r" (size));
}

static uint32 SCTLR_Read(void) {
    uint32 r;
    __asm volatile("mrc   p15, 0, %0, c1, c0, 0 " : "=r" (r));
    return r;
}

static uint32 SCTLR_Write(uint32 r) {
    __asm volatile("mcr   p15, 0, %0, c1, c0, 0" : : "r" (r));
    return r;
}


void EnableMMU( void ) {
    uint32 r;

    __asm volatile("dsb");
    r = SCTLR_Read();
    r |= (1UL << 2 ) |   /* Cache enable */
         (1UL << 0 );    /* MPU enable */
    SCTLR_Write(r);
    __asm volatile("isb");
}


/*
 * MPU: We have unified map.
 *
 */

#if 0
typedef union {
    vuint32_t R;
    struct {
        vuint32_t BaseAddr:30;
        vuint32_t :2;
    } B;
} MpuBAR_T;

typedef union {
    vuint32_t R;
    struct {
        vuint32_t :16;
        vuint32_t SxD:3;    /* Subregion disable */
        vuint32_t :2;
        vuint32_t RSize:5;  /* Region Size field. */
        vuint32_t En:5;
    } B;
} MpuBR_T;

typedef union {
    vuint32_t R;
    struct {
        vuint32_t :19;
        vuint32_t XN:1;
        vuint32_t :1;
        vuint32_t AP:2;
        vuint32_t :2;
        vuint32_t TEX:3;
        vuint32_t S:1;
        vuint32_t C:1;
        vuint32_t B:1;
    } B;
} MpuACR_T;

struct MpuEntryT {
    uint32   region;
    MpuBAR_T bar;
    MpuBR_T  br;
    MpuACR_T acr;
};


struct MpuEntryT MpuTable[] =  {
     {
         .region = 0,
         .bar.R = 0x0UL,
         .br.R = 0x0UL,
         .acr.R = 0x0UL,
     },
     {
         .region = 1,
         .bar.R = 0x0UL,            /* Base Address */

         .br.B.SxD = 0x0UL,
         .br.B.RSize = 0x3fUL,      /* Region Size (size = 2^(N+1)  */
         .br.B.En = 0x1UL,          /* Enable */

         .acr.B.AP  = 0x0UL, .acr.B.TEX = 0x0UL,.acr.B.S = 0x0UL,
         .acr.B.C   = 0x0UL, .acr.B.B   = 0x0UL,
     },
     {
         .region = 2,
         .bar.R = 0x0UL,

         .br.B.SxD = 0x0UL,         /* Base Address */
         .br.B.RSize = 0x3fUL,      /* Region Size (size = 2^(N+1)  */
         .br.B.En = 0x1UL,          /* Enable */

         .acr.B.AP  = 0x0UL, .acr.B.TEX = 0x0UL,.acr.B.S = 0x0UL,
         .acr.B.C   = 0x0UL, .acr.B.B   = 0x0UL,
     },
};
#endif


#define RSIZE_128           6   /* 2^(6+1) */
#define RSIZE_256           7
#define RSIZE_512           8
#define RSIZE_1K            9
#define RSIZE_2K            10
#define RSIZE_64K           15
#define RSIZE_128K          16
#define RSIZE_256K          17
#define RSIZE_512K          18
#define RSIZE_1M            19
#define RSIZE_2M            20
#define RSIZE_4M            21
#define RSIZE_8M            22
#define RSIZE_16M            23
#define RSIZE_32M            24
#define RSIZE_64M            25

#define RSIZE_4G            31



void Os_MMInit( void ) {

    /* We have PMSA
     *
     *
     * https://static.docs.arm.com/100699_0100/00/armv8m_architecture_memory_protection_unit_100699_0100_00_en.pdf
     * http://infocenter.arm.com/help/topic/com.arm.doc.dai0425/DAI0425_migrating_an_application_from_ARMv5_to_ARMv7_AR.pdf
     *
     * Sizes
     *   The region size is 2^(N+1) where N is the size, e.g N=7 -> size is 2^(7+1) =  256 bytes.
     *   The region can be subdivided into 8 equally sized regions
     *
     */
    uint32 region = 0U;
    uint32 baseAddr = 0UL;
    uint32 sizeEnable = 0UL;
    uint32 accessControl = 0UL;


    /*
     * TMS570 Memory Map
     * 0x0000.0000 -- 0x0013.FFFF Flash
     * 0x0800.0000 -- 0x0802.FFFF RAM
     * 0x0840.0000 -- 0x0842.FFFF RAM ECC
     * 0xFC00.0000 -- 0xFCFF.FFFF Peri Frame 2
     * 0xFF00.0000 -- 0xFFFF.FFFF Peri Frame 1 + System Modules
     *
     * B5.2.1
     * PL0 - User Mode
     * PL1 - Supervisor MOde
     *
     *
     * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0553a/BABDJJGF.html
     *
     */

#define AP_SRW_URO      2
#define AP_SRW_URW      3




    /* Flash (TCM memory)
     * Supervisor/User code */
    baseAddr = 0UL & 0xfffffff0UL;
    sizeEnable =    0UL         << 16U |    /* Reserved */
                    0UL         << 8U |     /* Sub Region */
                    RSIZE_4M    << 1U |     /* Region Size (size = 2^(N+1)  */
                    1UL         << 0U;      /* Enable */

    accessControl = 0UL           << 13U |     /* Reserved */
                    AP_SRW_URO    << 8U |      /* AP[2:0] */
                    1UL           << 3U |      /* TEX[2:0] */
                    0UL           << 2U |      /* S - Sharable */
                    0UL           << 1U |      /* C */
                    0UL           << 0U;       /* B */

    WriteRegion(region, baseAddr, sizeEnable, accessControl );
    region++;

    /* RAM (TCM memory)
     *  Supervisor data (.bss + .data) + User data (Read Only)
     */
    baseAddr = 0x08000000UL;
    sizeEnable =    0UL         << 16U |    /* Reserved */
                    0UL         << 8U |     /* Sub Region */
                    RSIZE_256K  << 1U |     /* Region Size (size = 2^(N+1)  */
                    1UL         << 0U;      /* Enable */

    accessControl = 0UL         << 13U |     /* Reserved */
                    1UL         << 12U |     /* XN */
                    AP_SRW_URO  << 8U |      /* AP[2:0], 3 - R/W */
                    1UL         << 3U |      /* TEX[2:0] */
                    0UL         << 2U |      /* S - Sharable */
                    0UL         << 1U |      /* C */
                    0UL         << 0U;       /* B */

    WriteRegion(region, baseAddr, sizeEnable, accessControl );
    region++;

    /* Peripheral
     *  Supervisor data (.bss + .data) + User data (Read Only)
     */
    baseAddr = 0xFC000000UL;
    sizeEnable =    0UL       << 16U |    /* Reserved */
                    0UL       << 8U |     /* Sub Region */
                    RSIZE_64M << 1U |     /* Region Size (size = 2^(N+1)  */
                    1UL       << 0U;      /* Enable */

    accessControl = 0UL         << 13U |     /* Reserved */
                    1UL         << 12U |     /* XN */
                    AP_SRW_URO  << 8U |      /* AP[2:0], 3 - R/W */
                    0UL         << 3U |      /* TEX[2:0] */
                    0UL         << 2U |      /* S - Sharable */
                    0UL         << 1U |      /* C */
                    1UL         << 0U;       /* B */

    WriteRegion(region, baseAddr, sizeEnable, accessControl );
    region++;


    /* System */
    baseAddr = 0xFFF80000UL;
    sizeEnable =    0UL         << 16U |    /* Reserved */
                    0UL         << 8U |     /* Sub Region */
                    RSIZE_512K  << 1U |     /* Region Size (size = 2^(N+1)  */
                    1UL         << 0U;      /* Enable */

    accessControl = 0UL         << 13U |     /* Reserved */
                    1UL         << 12U |     /* XN */
                    AP_SRW_URO  << 8U |      /* AP[2:0], 3 - R/W */
                    0UL         << 3U |      /* TEX[2:0] */
                    0UL         << 2U |      /* S - Sharable */
                    0UL         << 1U |      /* C */
                    0UL         << 0U;       /* B */

    WriteRegion(region, baseAddr, sizeEnable, accessControl );
    region++;

    EnableMMU();
}


#define ACCESS_CONTROL_RAM  ( \
                    (0UL         << 13U) |  /* Reserved */ \
                    (1UL         << 12U) |  /* XN */ \
                    (AP_SRW_URW  << 8U) |   /* AP[2:0], 3 - R/W */\
                    (1UL         << 3U) |   /* TEX[2:0] */ \
                    (0UL         << 2U) |   /* S - Sharable */ \
                    (0UL         << 1U) |   /* C */ \
                    (0UL         << 0U))  /* B */


/**
 *
 *
 * @param pcbPtr
 */
void Os_MMSetUserMode( OsTaskVarType *pcbPtr ) {

    if( Os_ApplGetConst(pcbPtr->constPtr->applOwnerId)->trusted == 0) {
        uint32 region = 8;

        /* User Mode, stack */
        WriteRegion(region, pcbPtr->regs[MPU0_REG_TASK_STACK_BASEADDR], pcbPtr->regs[MPU0_REG_TASK_STACK_SIZEENABLE], ACCESS_CONTROL_RAM );
        region++;

        /* User Mode, .data */
        WriteRegion(region, pcbPtr->regs[MPU0_REG_TASK_DATA_BASEADDR], pcbPtr->regs[MPU0_REG_TASK_DATA_SIZEENABLE], ACCESS_CONTROL_RAM );
        region++;

        /* User Mode, .bss */
        WriteRegion(region, pcbPtr->regs[MPU0_REG_TASK_BSS_BASEADDR], pcbPtr->regs[MPU0_REG_TASK_BSS_SIZEENABLE], ACCESS_CONTROL_RAM );
        region++;
    }
}

#endif /* (OS_SC3 == STD_ON ) || (OS_SC4 == STD_ON ) */
