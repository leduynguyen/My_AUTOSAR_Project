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
/* Note:
 *
 * This driver is intended to support whole MPC5XXX Family *
 *
 *  */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.2.2 */
/** @tagSettings DEFAULT_ARCHITECTURE=MPC5748G|MPC5747C */
#ifndef ETH_MPC5XXX_H_
#define ETH_MPC5XXX_H_

#include "mpc55xx.h"

/*
 * Typedef Eth_HwRegType to the exact MAC structure depending on the family
 * Eth_HwRegType is required to be used as generic inside the *.c file
 * */

#if defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
typedef volatile struct ENET_tag Eth_HwRegType; /* HW register type */
#define ETH_HW0_ADRS      (0xFFCC4000UL)
#if defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
#define ETH_HW1_ADRS      (ETH_HW0_ADRS + 0x4000)
#endif
#endif

#if defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
#define ETH_MAX_HW_UNITS                              2u
#elif defined(CFG_MPC5747C)
#define ETH_MAX_HW_UNITS                              1u
#endif

#endif /* ETH_MPC5XXX_H_ */
