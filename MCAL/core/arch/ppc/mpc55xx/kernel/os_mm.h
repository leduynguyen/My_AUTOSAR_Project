
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

/* Common Super/User mode bits for Freescale MPU */
#define SM_RWX      (0<<3)
#define SM_RX       (1<<3)
#define SM_RW       (2<<3)
#define SM_UM       (3<<3)

#define UM_X        (1)
#define UM_W        (2)
#define UM_R        (4)

#define UM_RW       (UM_R+UM_W)

/* Offsets for MPU0 and PPC */
#define MPU0_REG_MSR                 0
#define MPU0_REG_TASK_STACK_START    2
#define MPU0_REG_TASK_STACK_END      3
#define MPU0_REG_TASK_DATA_START     4
#define MPU0_REG_TASK_DATA_END       5
#define MPU0_REG_TASK_BSS_START      6
#define MPU0_REG_TASK_BSS_END        7

