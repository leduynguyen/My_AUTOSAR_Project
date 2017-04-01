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

#ifndef IRQ_TYPES_H_
#define IRQ_TYPES_H_

#if defined(CFG_RH850F1H)
#include "irq_rh850f1h.h"
#elif defined(CFG_RH850F1L)
#include "irq_rh850f1l.h"

#define IRQ_INTRCANGRECC0 IRQ_INTRCANGRECC

#else
#error CPU not defined
#endif

#endif /* IRQ_TYPES_H_ */
