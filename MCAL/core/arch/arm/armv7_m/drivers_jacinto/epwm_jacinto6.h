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

#ifndef EPWM_JACINTO6_H
#define EPWM_JACINTO6_H

#define PWM_ISR_PRIORITY					10u
#define PWM_ISR_APP							0u

#define PWMSS1_CFG_BASE_ADDRESS				(0x4843E000uL + L3_OFFSET)
#define PWMSS2_CFG_BASE_ADDRESS				(0x48440000uL + L3_OFFSET)
#define PWMSS3_CFG_BASE_ADDRESS				(0x48442000uL + L3_OFFSET)

#define PWMSS1_EPWM_BASE_ADDRESS			(0x4843E200uL + L3_OFFSET)
#define PWMSS2_EPWM_BASE_ADDRESS			(0x48440200uL + L3_OFFSET)
#define PWMSS3_EPWM_BASE_ADDRESS			(0x48442200uL + L3_OFFSET)

#define EPWM_JACINTO6_NUM_UNITS				3u

typedef struct {
    volatile uint32 PWMSS_IDVER;
    volatile uint32 PWMSS_SYSCONFIG;
    volatile uint32 PWMSS_CLKCONFIG;
    volatile uint32 PWMSS_CLKSTATUS;
} PWMSS_CFG_Regs;

#define PWMSS_SYSCONFIG_IDLEMODE_SHIFT		2uL
#define PWMSS_SYSCONFIG_IDLEMODE_SMART		2uL
#define PWMSS_SYSCONFIG_SOFTRESET			1uL

#define PWMSS_CLKCONFIG_ECAP_CLKSTOP_REQ	(1uL << 1uL)
#define PWMSS_CLKCONFIG_EQEP_CLKSTOP_REQ	(1uL << 5uL)

#endif /* EPWM_JACINTO6_H */
