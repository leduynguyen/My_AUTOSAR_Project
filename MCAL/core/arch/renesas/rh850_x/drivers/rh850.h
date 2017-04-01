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

#ifndef RH850_H_
#define RH850_H_


/*lint -save -e9048 -e46 Renesas include file */
#if defined(CFG_RH850F1H)
#include "dr7f701503.dvf.h"
#elif defined(CFG_RH850F1L)
#include "dr7f701013.dvf.h"
#endif
/*lint -restore */

#endif /* RH850_H_ */
