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
#include "Cpu.h"

// Register numbers
#define MPU_CSR0_ID_LOCAL 1014
#define DMEMCTRL1_REG_ID_LOCAL 498
// Local Mem (DMEM) is configured as 4 equally sized blocks.
//   Configuring DMEMCTL1 register with 10 for every segment for both user and supervisor mode will enable
//   Memory protection logic configured in MPU (via MAS) for the local memory.
//   Otherwise DMEM ctrl (Local memory) will bypass MPU
#define DMEMCTRL1_REG_CONFIG 0xaaaaaaaa

#if (OS_SC3 == STD_ON ) || (OS_SC4 == STD_ON )

void updateMPU(uint32_t mpu_MAS0, uint32_t mpu_MAS1, uint32_t mpu_MAS2, uint32_t mpu_MAS3) {
    set_spr(SPR_MAS0, mpu_MAS0);
    set_spr(SPR_MAS1, mpu_MAS1);
    set_spr(SPR_MAS2, mpu_MAS2);
    set_spr(SPR_MAS3, mpu_MAS3);

    asm volatile(" .long 0x7e0007a4"); //asm volatile(" mpuwe");
    asm volatile(" .long 0x7e00046c"); //asm volatile(" mpusync");
}

#if 0 // Enable when MPU read required
void readMPU (void) {
    asm volatile(" .long 0x7e00046c"); //asm volatile(" mpusync");
    asm volatile(" .long 0x7E000764"); //asm volatile ("mpure");
    asm volatile(" .long 0x7e00046c"); //asm volatile(" mpusync");
}
#endif

void Os_MMInit( void ) {

    uint32_t mpuMAS0 = 0ul;
    uint32_t mpuMAS1 = 0ul;
    uint32_t mpuMAS2 = 0ul;
    uint32_t mpuMAS3 = 0ul;

    // Configuring the internal flash
    // Instruction: Internal Flash @ 0x0040_0000-0x01FF_FFFF
    // deriving the value mpuMAS0 : 0xa1000f00
    mpuMAS0 = ((1UL << 31U) | // VALID = MPU entry is valid
               (2UL << 28U) | // MPU select
               (1UL << 24U) | // INST = Inst Access
               (0UL << 23U) | // SHD = Not a shared portion
               (0UL << 16U) | // ESEL = Entry select id is 0
               (1UL << 11U) | // UW = Enable user write
               (1UL << 10U) | // SW = Enable supervisor write
               (1UL << 9U) |  // UX/UR = Enable user execute
               (1UL << 8U) |  // SX/SR = Enable supervisor execute
               (1UL << 3U));  // I = Cacheable

    mpuMAS1 = 0x0;         // TID=0, global
    mpuMAS2 = 0x01ffffff;  // Upper bound 0x1ffffff
    mpuMAS3 = 0x00400000;  // Lower bound 0x00400000

    updateMPU(mpuMAS0, mpuMAS1, mpuMAS2, mpuMAS3); // Writing to MAS, MPU registers
    isync(); //mpuwe is preceded by msync and followed by se_isync for region 0. This synchronization step is taken since the code being executed is from the region being modified.

    // Configuring System RAM
    // Instruction: SRAM @ 0x4000_0000-0x4005_FFFF
    // deriving the value mpuMAS0 : 0xa1010f00
    mpuMAS0 = ((1UL << 31U) | // VALID = MPU entry is valid
               (2UL << 28U) | // MPU select
               (1UL << 24U) | // INST = Inst Access
               (0UL << 23U) | // SHD = Not a shared portion
               (1UL << 16U) | // ESEL = Entry select id is 1
               (1UL << 11U) | // UW = Enable user write
               (1UL << 10U) | // SW = Enable supervisor write
               (1UL << 9U) |  // UX/UR = Enable user execute
               (1UL << 8U) |  // SX/SR = Enable supervisor execute
               (0UL << 3U));  // I = Non Cacheable
    mpuMAS1 = 0x0;         // TID=0, global
    mpuMAS2 = 0x4005FFFF;  // Upper Bound = 0x4005FFFF
    mpuMAS3 = 0x40000000;  // Lower Bound = 0x40000000

    updateMPU(mpuMAS0, mpuMAS1, mpuMAS2, mpuMAS3);  // Writing to MAS, MPU registers

    // Configuring System RAM for Data
    // Data: SRAM @ 0x40000000-0x4005FFFF
    // deriving the value mpuMAS0 : 0xa0000f00
    mpuMAS0 = ((1UL << 31U) | // VALID = MPU entry is valid
               (2UL << 28U) | // MPU select
               (0UL << 24U) | // INST = Data Access
               (0UL << 23U) | // SHD = Not a shared portion
               (0UL << 16U) | // ESEL = Entry select id is 0
               (1UL << 11U) | // UW = Enable user write
               (1UL << 10U) | // SW = Enable supervisor write
               (1UL << 9U) |  // UX/UR = Enable user read
               (1UL << 8U) |  // SX/SR = Enable supervisor read
               (0UL << 3U));  // I = Non Cacheable
    mpuMAS1 = 0x0;         // TID=0, global
    mpuMAS2 = 0x4005FFFF;  // Upper Bound = 0x4005FFFF
    mpuMAS3 = 0x40000000;  // Lower Bound = 0x40000000

    updateMPU(mpuMAS0, mpuMAS1, mpuMAS2, mpuMAS3);  // Writing to MAS, MPU registers

    // Configuring Internal Flash for Data
    // Data: Internal Flash @ 0x0040_0000-0x01FF_FFFF
    // deriving the value mpuMAS0 : 0xa0010f00
    mpuMAS0 = ((1UL << 31U) | // VALID = MPU entry is valid
               (2UL << 28U) | // MPU select
               (0UL << 24U) | // INST = Data Access
               (0UL << 23U) | // SHD = Not a shared portion
               (1UL << 16U) | // ESEL = Entry select id is 1
               (1UL << 11U) | // UW = Enable user write
               (1UL << 10U) | // SW = Enable supervisor write
               (1UL << 9U) |  // UX/UR = Enable user read
               (1UL << 8U) |  // SX/SR = Enable supervisor read
               (1UL << 3U));  // I = Cacheable
    mpuMAS1 = 0x0;         // TID=0, global
    mpuMAS2 = 0x01ffffff;  // Upper bound 0x1ffffff
    mpuMAS3 = 0x00400000;  // Lower bound 0x00400000

    updateMPU(mpuMAS0, mpuMAS1, mpuMAS2, mpuMAS3);  // Writing to MAS, MPU registers

    // Configuring PBRIDGE I/O for Data
    // Data: PBRIDGE1/0 @ 0xF800_0000-0xFFFF_FFFF
    // deriving the value mpuMAS0 : 0xa0020f09
    mpuMAS0 = ((1UL << 31U) | // VALID = MPU entry is valid
               (2UL << 28U) | // MPU select
               (0UL << 24U) | // INST = Data Access
               (0UL << 23U) | // SHD = Not a shared portion
               (2UL << 16U) | // ESEL = Entry select id is 2
               (1UL << 11U) | // UW = Enable user write
               (1UL << 10U) | // SW = Enable supervisor write
               (1UL << 9U) |  // UX/UR = Enable user read
               (1UL << 8U) |  // SX/SR = Enable supervisor read
               (0UL << 3U));  // I = Non Cacheable
    mpuMAS1 = 0x0;         // TID=0, global
    mpuMAS2 = 0xffffffff;  // Upper bound 0xffffffff
    mpuMAS3 = 0xf8000000;  // Lower bound 0xf8000000

    updateMPU(mpuMAS0, mpuMAS1, mpuMAS2, mpuMAS3);  // Writing to MAS, MPU registers


    // Configure Local ram
    // Data: DMEM @ 0x50800000-0x5080FFFF
    // deriving the value mpuMAS0 : 0xa0030700
    set_dcr (DMEMCTRL1_REG_ID_LOCAL, DMEMCTRL1_REG_CONFIG);
    mpuMAS0 = ((1UL << 31U) | // VALID = MPU entry is valid
               (2UL << 28U) | // MPU select
               (0UL << 24U) | // INST = Data Access
               (0UL << 23U) | // SHD = Not a shared portion
               (3UL << 16U) | // ESEL = Entry select id is 3
               (0UL << 11U) | // UW = Disable user write
               (1UL << 10U) | // SW = Enable supervisor write
               (1UL << 9U) |  // UX/UR = Enable user read
               (1UL << 8U) |  // SX/SR = Enable supervisor read
               (0UL << 3U));  // I = Non Cacheable
    mpuMAS1 = 0x0;         // TID=0, global
    mpuMAS2 = 0x5080FFFF;  // Upper bound
    mpuMAS3 = 0x50800000;  // Lower bound
    updateMPU(mpuMAS0, mpuMAS1, mpuMAS2, mpuMAS3);  // Writing to MAS, MPU registers

    // enable MPU
    set_spr(MPU_CSR0_ID_LOCAL, 0x1);
    isync();
}


/**
 *
 *
 * @param pcbPtr
 */
void Os_MMSetUserMode( OsTaskVarType *pcbPtr ) {

    uint32_t mpuMAS0 = 0ul;
    uint32_t mpuMAS1 = 0ul;
    uint32_t mpuMAS2 = 0ul;
    uint32_t mpuMAS3 = 0ul;

    /* User Mode, stack */
    // deriving the value mpuMAS0 : 0xa0040f00
    mpuMAS0 = ((1UL << 31U) | // VALID = MPU entry is valid
               (2UL << 28U) | // MPU select
               (0UL << 24U) | // INST = Data Access
               (0UL << 23U) | // SHD = Not a shared portion
               (4UL << 16U) | // ESEL = Entry select id is 4
               (1UL << 11U) | // UW = Enable user write
               (1UL << 10U) | // SW = Enable supervisor write
               (1UL << 9U) |  // UX/UR = Enable user read
               (1UL << 8U) |  // SX/SR = Enable supervisor read
               (0UL << 3U));  // I = Cacheable
    mpuMAS1 = 0x0;         // TID=0, global
    mpuMAS3 = pcbPtr->regs[MPU0_REG_TASK_STACK_START]; // Lower bound
    mpuMAS2 = pcbPtr->regs[MPU0_REG_TASK_STACK_END];   // Upper bound
    updateMPU(mpuMAS0, mpuMAS1, mpuMAS2, mpuMAS3);  // Writing to MAS, MPU registers

    /* User Mode, .data */
    // deriving the value mpuMAS0 : 0xa0050f00
    mpuMAS0 = ((1UL << 31U) | // VALID = MPU entry is valid
               (2UL << 28U) | // MPU select
               (0UL << 24U) | // INST = Data Access
               (0UL << 23U) | // SHD = Not a shared portion
               (5UL << 16U) | // ESEL = Entry select id is 5
               (1UL << 11U) | // UW = Enable user write
               (1UL << 10U) | // SW = Enable supervisor write
               (1UL << 9U) |  // UX/UR = Enable user read
               (1UL << 8U) |  // SX/SR = Enable supervisor read
               (0UL << 3U));  // I = Cacheable
    mpuMAS1 = 0x0;         // TID=0, global
    mpuMAS3 = pcbPtr->regs[MPU0_REG_TASK_DATA_START]; // Lower bound
    mpuMAS2 = pcbPtr->regs[MPU0_REG_TASK_DATA_END];   // Upper bound
    updateMPU(mpuMAS0, mpuMAS1, mpuMAS2, mpuMAS3);  // Writing to MAS, MPU registers

    /* User Mode, .bss */
    // deriving the value mpuMAS0 : 0xa0060f00
    mpuMAS0 = ((1UL << 31U) | // VALID = MPU entry is valid
               (2UL << 28U) | // MPU select
               (0UL << 24U) | // INST = Data Access
               (0UL << 23U) | // SHD = Not a shared portion
               (6UL << 16U) | // ESEL = Entry select id is 6
               (1UL << 11U) | // UW = Enable user write
               (1UL << 10U) | // SW = Enable supervisor write
               (1UL << 9U) |  // UX/UR = Enable user read
               (1UL << 8U) |  // SX/SR = Enable supervisor read
               (0UL << 3U));  // I = Cacheable
    mpuMAS1 = 0x0;         // TID=0, global
    mpuMAS3 = pcbPtr->regs[MPU0_REG_TASK_BSS_START]; // Lower bound
    mpuMAS2 = pcbPtr->regs[MPU0_REG_TASK_BSS_END];   // Upper bound
    updateMPU(mpuMAS0, mpuMAS1, mpuMAS2, mpuMAS3);  // Writing to MAS, MPU registers

}

#endif /* (OS_SC3 == STD_ON ) || (OS_SC4 == STD_ON ) */
