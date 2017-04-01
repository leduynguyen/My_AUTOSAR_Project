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

#ifndef RTE_WDGM_TYPE_H_
#define RTE_WDGM_TYPE_H_

#define WDGM_NOT_SERVICE_COMPONENT
#ifdef USE_RTE
#warning This file should only be used when NOT using an EcuM Service Component.
#include "Rte_Type.h"
#else

typedef uint8 WdgM_LocalStatusType;
typedef uint8 WdgM_GlobalStatusType;
typedef uint8 WdgM_ModeType;


/* NOTE:    datatype depends on the maximal configured amount of supervised entities
 *          currently we assume that 16bit are necessary (alternative would be 8)
 */
typedef uint16 WdgM_SupervisedEntityIdType;


/* NOTE:    datatype depends on the maximal configured amount of supervised entities
 *          currently we assume that 16bit are necessary (alternative would be 8)
 */
typedef uint16 WdgM_CheckpointIdType;
#endif

#endif /* RTE_WDGM_TYPE_H_ */
