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

/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.2.2 */

#ifndef CRC_CFG_H_
#define CRC_CFG_H_

/* @req SWS_CRC_00024 */
/* @req SWS_CRC_00022 */
#include "MemMap.h"

/* @req SWS_CRC_00040 */

/* CRC 8 Configuration
 * Possible values and the mode decides what method to be used
 */
#define CRC_8_HARDWARE (0x01) /* Not supported */
#define CRC_8_RUNTIME  (0x02)
#define CRC_8_TABLE    (0x04) /* Default value */


#define CRC_8_MODE      CRC_8_TABLE


/* CRC 8H2F Configuration
 * Possible values and the mode decides what method to be used
 */
#define CRC_8H2F_HARDWARE (0x01) /* Not supported */
#define CRC_8H2F_RUNTIME  (0x02)
#define CRC_8H2F_TABLE    (0x04) /* Default value */


#define CRC_8H2F_MODE      CRC_8H2F_TABLE


/* CRC 16 Configuration
 * Possible values and the mode decides what method to be used
 */
#define CRC_16_HARDWARE (0x01) /* Not supported */
#define CRC_16_RUNTIME  (0x02)
#define CRC_16_TABLE    (0x04) /* Default value */


#define CRC_16_MODE      CRC_16_TABLE


/* CRC 32 Configuration
 * Possible values and the mode decides what method to be used
 */
#define CRC_32_HARDWARE (0x01)  /* Not supported */
#define CRC_32_RUNTIME  (0x02)
#define CRC_32_TABLE    (0x04)  /* Default value */


#define CRC_32_MODE      CRC_32_TABLE


/* CRC 32P4 Configuration
 * Possible values and the mode decides what method to be used
 */
#define CRC_32P4_HARDWARE (0x01)  /* Not supported */
#define CRC_32P4_RUNTIME  (0x02)
#define CRC_32P4_TABLE    (0x04)  /* Default value */


#define CRC_32P4_MODE      CRC_32P4_TABLE


/* Version info configuration */
#define CRC_VERSION_INFO_API    STD_ON


#endif /* CRC_CFG_H_ */

