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


#ifndef WDGM_INTERNALTYPESH
#define WDGM_INTERNALTYPESH

#include "WdgM_Cfg.h"
#include "Rte_WdgM_Type.h"

typedef struct
{
    uint32			AliveCounter; 				/* maybe a smaller datatype applies */
    uint16			SupervisionCycleCounter;	/* maybe a smaller datatype applies */
    boolean			wasEvaluated;
} WdgM_internal_AliveSupervision;

typedef struct
{
    uint32			TimestampStart;
} WdgM_internal_DeadlineSupervision;

typedef struct
{
    WdgM_LocalStatusType	LocalState;
    WdgM_Substate			SubstateAlive;
    WdgM_Substate			SubstateDeadline;
    WdgM_Substate			SubstateLogical;

    boolean					IsInternalGraphActive; /* active flag for the internal graph */	/** @req WDGM271 */

    uint16					PreviousCheckpointId_Deadline;			/** @req WDGM246 */
    uint16					PreviousCheckpointId_internalLogic;		/** @req WDGM246 */

    uint8					FailedAliveCyclesCounter;
} WdgM_internal_SupervisedEntity;


typedef struct
{
    WdgM_internal_AliveSupervision 		*AliveSupervisions;
    const uint16						Length_AliveSupervisions;

    WdgM_internal_DeadlineSupervision 	*DeadlineSupervisions;
    const uint16						Length_DeadlineSupervisions;
} WdgM_internal_SupervisedEntityConfig;

typedef struct
{
    WdgM_internal_SupervisedEntityConfig	*SE_Configs;
    const uint16							Length_SEConfigs;

    uint16									ExpiredSupervisionCycleCounter;
} WdgM_internal_Mode;

typedef struct
{
    WdgM_internal_SupervisedEntity			*SEs;
    const uint16							Length_SEs;

    WdgM_internal_Mode						*Modes;
    const uint16							Length_Modes;

} WdgM_internal_RuntimeData;


typedef struct
{
    const WdgM_ConfigType		*ConfigPtr;
    WdgM_internal_RuntimeData	*internalRuntimeDataPtr;
    boolean						isInitiated;
    WdgM_GlobalStatusType		GlobalState;					/** @req WDGM213 */
    uint32						CurrentTime;
    const WdgM_Mode				*CurrentMode;
    boolean						ResetInitiated;
    uint16						firstExpiredSEID;
    boolean						isFirstExpiredSet;
} WdgM_debuggable_internalData;


#endif
