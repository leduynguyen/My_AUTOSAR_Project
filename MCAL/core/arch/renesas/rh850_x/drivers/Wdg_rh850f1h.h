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

#ifndef WDG_HW_H_
#define WDG_HW_H_

#include "Arc_Types.h"
#include "Os.h"

#define OSTM5_BASE					0xFFD71000u
#define OSTM5p						((struct OSTM_reg*) OSTM5_BASE)
#define OSTMNTS_START				1u
#define OSTMNTT_STOP				1u

#define WDTAN_BASE					0xFFED0000u
#define WDTA0MD7_MASK				0x80u
#define WDT_100_PERCENT_WINDOW		0x03u
#define WDT_KICK_CODE				0xACu
#define WDG_KICK_ISR_PRIO			10u
#define WDG_ISR_APP					0u

#define PROTECTION_REG_UNLOCK_CODE	0x000000A5u
#define PROTCMD0_ADDR				0xFFF80000u
#define PROTS0_ADDR					0xFFF80004u
#define PROTS0_CONTENT				(*((vuint32_t*) PROTS0_ADDR))
#define PROTS0_ERROR_BIT			1u
#define PROTS0_NO_ERROR				0u

#define CKSC_AWDTAD_CTL_ADDR		0xFFF82000u
#define CKSC_AWDTAD_ACT_ADDR		0xFFF82008u
#define CKSC_AWDTAD_ACT_CONTENT		(*((vuint32_t*) CKSC_AWDTAD_ACT_ADDR))
#define CKSC_AWDTAD_ACT_MASK		3u
#define CKSC_AWDTAD_CTL_IS_ACTIVE	1u
#define WDTA0_CLOCK_DIVIDER_128		1u
#define WDTA0_CLOCK_DIVIDER_1		2u
#define WDTA0_CLOCK_DIVIDER_MASK	3u

#define WDG_SCALE_MAX_TRIES			5

/* The watchdog will always be kicked with a 1 ms interval. */
#define WDG_TRIGGER_PERIOD_MS		1

/* WDTA registers */
struct WDTA_reg {
    vuint8_t 	WDTE;		/* 0x00000000 Enable register */
    uint8		pad1[3];
    vuint8_t 	EVAC;		/* 0x00000004 Variable activation code register */
    uint8  		pad2[3];
    vuint8_t	REF;		/* 0x00000008 Reference value register */
    uint8		pad3[3];
    vuint8_t	MD;			/* 0x0000000C Mode register */
};

typedef volatile struct WDTA_reg Wdg_WdtaHwRegType;

ISR(Wdg_Isr_Kick);

/**
 * @brief Does nothing. Tests cannot be written to rely on stopping the watchdog.
 * The RH850F1H watchdog cannot be stopped once started.
 */
void Wdg_Arc_StopWatchdog(void);

#endif /* WDG_HW_H_ */
