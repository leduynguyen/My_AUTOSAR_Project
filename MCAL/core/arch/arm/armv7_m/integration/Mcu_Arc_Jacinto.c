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
 * Author: jcar
 *
 * Description:
 *
 */
/** @tagSettings DEFAULT_ARCHITECTURE=JACINTO5|JACINTO6 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */


/* ----------------------------[includes]------------------------------------*/


#include "Std_Types.h"
#include "Mcu.h"
#include "io.h"
#include "Mcu_Arc.h"
#include "irq.h"
#include "irq_types.h"
#include "io.h"
#if defined(USE_KERNEL)
#include "Os.h"
#endif

/* ----------------------------[private define]------------------------------*/
#define CM3_MMU_CFG				           (0x55080000U)
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

#if defined(CFG_MCU_MMU)

#if defined(CFG_JAC5) || defined(CFG_JAC5E) || (defined(CFG_JAC6) && !defined(CFG_BRD_JAC6_VAYU_EVM))
void Mcu_Arc_InitMM( void ) {

    /* User: Setup TLBs if needed  */
    WRITE32(CM3_MMU_CFG+0x004,0x00000000);/* disable cache */
    WRITE32(CM3_MMU_CFG+0x014,0x80020000);/* set start addr */
    WRITE32(CM3_MMU_CFG+0x018,0x80120000);/* set end addr */
    WRITE32(CM3_MMU_CFG+0x010,0x00000010);/* invalidate cache */

    /*Large Pages Translations */
    WRITE32(CM3_MMU_CFG+0x800,0x40000000);/* Address */
    WRITE32(CM3_MMU_CFG+0x820,0x40000000);/* Translated Address */
    WRITE32(CM3_MMU_CFG+0x840,0x0000000B);/* Page Policy (Enabled, 512MB, Follow volatile qualifier) */

    WRITE32(CM3_MMU_CFG+0x804,0x80000000);/* Address */
    WRITE32(CM3_MMU_CFG+0x824,0x80000000);/* Translated Address */
    WRITE32(CM3_MMU_CFG+0x844,0x0003000B);/* Page Policy (Enabled, 512MB, Volatile, L1 cachable, L1 posted) */

    WRITE32(CM3_MMU_CFG+0x808,0xC0000000);/* Address */
    WRITE32(CM3_MMU_CFG+0x828,0xC0000000);/* Translated Address */
    WRITE32(CM3_MMU_CFG+0x848,0x00000000);/* Page Policy (disabled) */

    WRITE32(CM3_MMU_CFG+0x80C,0xE0000000);/* Address */
    WRITE32(CM3_MMU_CFG+0x82C,0xE0000000);/* Translated Address */
    WRITE32(CM3_MMU_CFG+0x84C,0x0000000B);/* Page Policy (Enabled, 512MB, Volatile) */

    /* Medium Pages Translations */
    WRITE32(CM3_MMU_CFG+0x860,0x00300000);/* Address */
    WRITE32(CM3_MMU_CFG+0x8A0,0x40300000);/* Translated Address */
    WRITE32(CM3_MMU_CFG+0x8E0,0x0003000B);/* Page Policy (Enabled, 256KB, Volatile, L1 cachable, L1 posted) */

    /* Small Pages Translations */
    WRITE32(CM3_MMU_CFG+0x920,0x00000000);/* Address */
    WRITE32(CM3_MMU_CFG+0x9A0,0x55020000);/* Translated Address */
    WRITE32(CM3_MMU_CFG+0xA20,0x0003000B);/* Page Policy (Enabled, 256KB, Volatile, L1 cachable, L1 posted) */

    WRITE32(CM3_MMU_CFG+0x928,0x00004000);/* Address */
    WRITE32(CM3_MMU_CFG+0x9A8,0x55024000);/* Translated Address */
    WRITE32(CM3_MMU_CFG+0xA28,0x0003000B);/* Page Policy (Enabled, 256KB, Volatile, L1 cachable, L1 posted) */

    WRITE32(CM3_MMU_CFG+0x92C,0x00008000);/* Address */
    WRITE32(CM3_MMU_CFG+0x9AC,0x55028000);/* Translated Address */
    WRITE32(CM3_MMU_CFG+0xA2C,0x0003000B);/* Page Policy (Enabled, 256KB, Volatile, L1 cachable, L1 posted) */

    WRITE32(CM3_MMU_CFG+0x930,0x0000C000);/* Address */
    WRITE32(CM3_MMU_CFG+0x9B0,0x5502C000);/* Translated Address */
    WRITE32(CM3_MMU_CFG+0xA30,0x0003000B);/* Page Policy (Enabled, 256KB, Volatile, L1 cachable, L1 posted) */

    WRITE32(CM3_MMU_CFG+0x924,0xE0000000);/* Address */
    WRITE32(CM3_MMU_CFG+0x9A4,0x55080000);/* Translated Address */
    WRITE32(CM3_MMU_CFG+0xA24,0x00000000);/* Page Policy (disabled) */


    /* Must enable caches in order to get some speed on execution */
    WRITE32(CM3_MMU_CFG+0x004,0x00000002);/* enable cache */

}
#endif
#endif
