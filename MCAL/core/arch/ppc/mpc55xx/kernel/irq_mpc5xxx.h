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


#ifndef IRQ_MPC5XXX_H
#define IRQ_MPC5XXX_H

/* Exception Vectors shared among mpc5xxx */
#define EXCEPTION_IVOR0			0uL
#define EXCEPTION_IVOR1			1uL
#define EXCEPTION_IVOR2			2uL
#define EXCEPTION_IVOR3			3uL
#define EXCEPTION_IVOR4			4uL
#define EXCEPTION_IVOR5			5uL
#define EXCEPTION_IVOR6			6uL
#define EXCEPTION_IVOR7			7uL
#define EXCEPTION_IVOR8			8uL
#define EXCEPTION_IVOR9			9uL
#define EXCEPTION_IVOR10		10uL
#define EXCEPTION_IVOR11		11uL
#define EXCEPTION_IVOR12		12uL
#define EXCEPTION_IVOR13		13uL
#define EXCEPTION_IVOR14		14uL
#define EXCEPTION_IVOR15		15uL

#define EXCEPTION_IVOR32		16uL
#define EXCEPTION_IVOR33		17uL
#define EXCEPTION_IVOR34		18uL

/* Special "exception" used to identify the FCCU in Os_Arc_Panic() */
#define EXPECPTION_ARC_FCCU 	100uL


#if defined(CFG_MPC5643L)
#include "irq_mpc5643l.h"
#elif defined(CFG_SPC56XL70)
#include "irq_spc56xl70.h"
#elif defined(CFG_MPC563XM)
#include "irq_mpc563xm.h"
#elif defined(CFG_MPC5644A)
#include "irq_mpc5644a.h"
#elif defined(CFG_MPC5645S)
#include "irq_mpc5645s.h"
#elif defined(CFG_MPC5744P)
#include "irq_mpc5744p.h"
#elif defined(CFG_MPC5777M)
#include "irq_mpc5777m.h"
#elif defined(CFG_MPC560X)
#include "irq_mpc560x.h"
#elif defined(CFG_MPC5516)
#include "irq_mpc551x.h"
#elif defined(CFG_MPC5567)
#include "irq_mpc5567.h"
#elif defined(CFG_MPC5668)
#include "irq_mpc5668.h"
#elif defined(CFG_MPC560X)
#include "irq_mpc560x.h"
#elif defined(CFG_MPC5748G) || defined(CFG_MPC5747C)
#include "irq_mpc5748g.h"
#elif defined(CFG_MPC5746C)
#include "irq_mpc5746c.h"
#else
#error CPU not defined
#endif


#endif /* IRQ_H_ */
