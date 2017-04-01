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

/*
 * How Autosar sees the scheduletable
 *
 * duration
 * repeating
 * accessionApplication
 * counterRef
 * autostart [0..1]
 * |--- absValue   (only if type==ABSOLUTE )
 * |--- relOffset  (only if type==RELATIVE )
 * |--- type       (ABSOLUTE, RELATIVE, SYNCHRON )
 * |--- modeRef
 * |
 * expiryPoint [1..*]
 * |--- offset
 * |--- EventSetting [0..*]
 * |    |--- SetEvent
 * |    `--- SetEventTaskRef
 * |
 * |--- TaskActivation [0..*]
 * |    `- TaskRef
 * |
 * |--- AdjustableExpPoint [0..1] (only if syncStrategy!=NONE)
 * |    |--- maxAdvance
 * |    `--- macRetard
 * |
 * sync
 * |--- explicitPrecision (only if syncStrategy==EXPLICIT )
 * |--- syncStrategy  	  (NONE,EXPLICIT,IMPLICIT )
 *
 */

/*
 * Generic requirements this module can handle
 */
 /** @req OS007 */
 /** @req OS410 */
 /** @req OS411 */
 /** @req OS347 */
 /** @req OS358 */
 /** @req OS428 */


/* ----------------------------[includes]------------------------------------*/

#include "os_i.h"


/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/

#define SCHED_CHECK_ID(x) 		\
    if( (x) > OS_SCHTBL_CNT) { 	\
        rv = E_OS_ID;			\
        goto err; 				\
    }

#if 0
/*lint -emacro(9041, SCHED_STD_END) MISRA 2012 15.3 Exception, allow err to be on different block level */
#define SCHED_STD_END 	\
        return rv;		\
    err:				\
        ERRORHOOK(rv);  \
        return rv // Expecting calling function to provide the ending semicolon
#endif

/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/


/**
 * Calculates expire value and changes state depending it's state.
 *
 * Note!
 * We can't cheat with the final + initial expire-point, instead we
 * must setup trigger after the final delay and set the "previous"
 * table to SCHEDULETABLE_STOPPED and the new to SCHEDULETABLE_RUNNING.
 *
 * @param stbl Ptr to a Schedule Table.
 */
static void Os_SchTblUpdateState( OsSchTblType *stbl ) {

    TickType delta;
    TickType initalOffset;
    TickType finalOffset;
    OsSchTblType *nextStblPtr;
    _Bool handleLast = 0;

    if( (stbl->expire_curr_index) == (SA_LIST_CNT(&stbl->expirePointList) - 1) ) {
        /* We are at the last expiry point */
        finalOffset = Os_SchTblGetFinalOffset(stbl);

        if (finalOffset != 0) {
            stbl->expire_val =	Os_CounterAdd(
                            Os_CounterGetValue(stbl->counter),
                            Os_CounterGetMaxValue(stbl->counter),
                            finalOffset );

            stbl->expire_curr_index++;
            return;
        } else {
            /* Only single shot may have an offset of 0 */
            ASSERT(stbl->repeating == SINGLE_SHOT);
            handleLast = 1;
        }
    }

    if( handleLast ||
        ( (stbl->expire_curr_index) == SA_LIST_CNT(&stbl->expirePointList) ) )
    {
        /* At final offset */
        /** @req OS194 */
        if( (stbl->repeating == REPEATING) || (stbl->next != NULL) ) {
            if( stbl->next != NULL ) {
                /** @req OS284 */
                nextStblPtr = stbl->next;
                /* NextScheduleTable() have been called */
                ASSERT( nextStblPtr->state==SCHEDULETABLE_NEXT );

                /* We don't care about REPEATING or SINGLE_SHOT here */
                initalOffset = Os_SchTblGetInitialOffset(nextStblPtr);
                stbl->state = SCHEDULETABLE_STOPPED;
                nextStblPtr->state = SCHEDULETABLE_RUNNING;

                nextStblPtr->expire_val =	Os_CounterAdd(
                                Os_CounterGetValue(nextStblPtr->counter),
                                Os_CounterGetMaxValue(nextStblPtr->counter),
                                initalOffset );

            } else {
                /** @req OS414 */

                /* REPEATING */
                ASSERT( stbl->repeating == REPEATING );
                initalOffset = Os_SchTblGetInitialOffset(stbl);

                stbl->expire_val =	Os_CounterAdd(
                                Os_CounterGetValue(stbl->counter),
                                Os_CounterGetMaxValue(stbl->counter),
                                initalOffset );
            }


        } else {
            ASSERT( stbl->repeating == SINGLE_SHOT );
            /** @req OS009 */
            stbl->state = SCHEDULETABLE_STOPPED;
        }
        stbl->expire_curr_index = 0;

    } else {

        delta = SA_LIST_GET(&stbl->expirePointList,stbl->expire_curr_index+1)->offset -
                SA_LIST_GET(&stbl->expirePointList,stbl->expire_curr_index)->offset ;

        stbl->expire_val =	Os_CounterAdd(
                        Os_CounterGetValue(stbl->counter),
                        Os_CounterGetMaxValue(stbl->counter),
                        delta );

        stbl->expire_curr_index++;

    }

    return;
}


/* ----------------------------[public functions]----------------------------*/


/**
 * Consistency checks for scheduletables. This should really be checked by
 * the generator.
 *
 * See chapter 11.2.
 *
 * @return
 */
#if (OS_SCHTBL_CNT != 0)
static void ScheduleTableConsistenyCheck( OsSchTblType *sTblPtr ) {

#if ( OS_SC2 == STD_ON ) || ( OS_SC4 == STD_ON )
    /** @req OS440 */
    if( sTblPtr->sync.syncStrategy == IMPLICIT ) {
        ASSERT( sTblPtr->duration == (sTblPtr->counter->alarm_base.maxallowedvalue +1) );
    }

    /** OS431 */
    if( sTblPtr->sync.syncStrategy == EXPLICIT ) {
        ASSERT( sTblPtr->duration <= (sTblPtr->counter->alarm_base.maxallowedvalue +1) );
    }
#endif

    /** @req OS401 */
    ASSERT(SA_LIST_CNT(&sTblPtr->expirePointList)>=1);



    {
        int iter;
        TickType delta = 0;
        TickType minCycle = Os_CounterGetMinCycle(sTblPtr->counter);
        TickType maxValue =  Os_CounterGetMaxValue(sTblPtr->counter);

        /* - start at offset=0
         * - X expiry points = SA_LIST_CNT
         * - Final offset.
         */
        /** @req OS443 */
        /** @req OS408 */
        for(iter=0; iter  <  SA_LIST_CNT(&sTblPtr->expirePointList) ; iter++) {
            delta = SA_LIST_GET(&sTblPtr->expirePointList,iter)->offset - delta;
            /* initial offset may be zero (OS443) */
            if(iter!=0) {
                ASSERT( delta >=  minCycle );
            }
            ASSERT( delta <=  maxValue );
        }

        /* Final */
        /** @req OS444 */ /** !req OS427 */
        delta = sTblPtr->duration - SA_LIST_GET(&sTblPtr->expirePointList,iter-1)->offset;
        ASSERT( delta >=  minCycle );
        ASSERT( delta <=  maxValue );
        // if assert is defined not to access the argument(s) lint warnings about the arguments not used
        //lint -save -e438 -e529
    }
    //lint -restore  Restore the inhibit messages within block above

}
#endif

/** @req OS521 StartScheduleTableRel available in all Scalability Classes. */
StatusType StartScheduleTableRel(ScheduleTableType sid, TickType offset) {
    StatusType rv = E_OK;
    OsSchTblType *sPtr;
    TickType max_offset;
    imask_t state;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */

#if (OS_STATUS_EXTENDED == STD_ON )
    /** @req OS275 */
    SCHED_CHECK_ID(sid);
#endif

    sPtr = Os_SchTblGet(sid);

#if	(OS_APPLICATION_CNT > 1)

    rv = Os_ApplHaveAccess( sPtr->accessingApplMask );
    if( rv != E_OK ) {
        goto err;
    }

#endif

#if ( OS_SC2 == STD_ON ) || ( OS_SC4 == STD_ON )
    if( sPtr->sync != NULL ) {
        /* EXPLICIT or IMPLICIT */

        /** OS452 */ /** OS430 */
        if( sPtr->sync->syncStrategy == IMPLICIT ) {
            rv = E_OS_ID;
            goto err;
        }
    }
#endif

    max_offset = Os_CounterGetMaxValue(sPtr->counter);
#if (OS_STATUS_EXTENDED == STD_ON )
    /** @req OS276 */
    /** @req OS332 */
    //lint -e{9007} MISRA False positive. No side effects of Os_SchTblGetInitialOffset
    if( (offset == 0) || ((offset + Os_SchTblGetInitialOffset(sPtr)) > max_offset ) ) {
        rv = E_OS_VALUE;
        goto err;
    }
#endif

    /** @req OS277 */
    if( sPtr->state != SCHEDULETABLE_STOPPED ) {
        rv = E_OS_STATE;
        goto err;
    }

    Irq_Save(state);
    /* calculate the expire value.. */
    /** @req OS278 */
    sPtr->expire_val = Os_CounterAdd(
                            Os_CounterGetValue(sPtr->counter),
                            max_offset,
                            offset + Os_SchTblGetInitialOffset(sPtr) );
    sPtr->state = SCHEDULETABLE_RUNNING;
    Irq_Restore(state);

    OS_STD_END_2(OSServiceId_StartScheduleTableRel,sid, offset);
}

/** @req OS522 StartScheduleTableAbs available in all Scalability Classes. */
StatusType StartScheduleTableAbs(ScheduleTableType sid, TickType start ){
    StatusType rv = E_OK;
    OsSchTblType *sTblPtr;
    imask_t state;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */
    /** @req OS348 */
    SCHED_CHECK_ID(sid);
    sTblPtr =  Os_SchTblGet(sid);

#if	(OS_APPLICATION_CNT > 1)

    rv = Os_ApplHaveAccess( sTblPtr->accessingApplMask );
    if( rv != E_OK ) {
        goto err;
    }

#endif

    /** @req OS349 */
    if( start > Os_CounterGetMaxValue(sTblPtr->counter) ) {
        rv = E_OS_VALUE;
        goto err;
    }

    /** @req OS350 */
    if( sTblPtr->state != SCHEDULETABLE_STOPPED ) {
        rv = E_OS_STATE;
        goto err;
    }


    Irq_Save(state);
    /** !req OS351 (SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS not supported) */
    sTblPtr->expire_val = start + Os_SchTblGetInitialOffset(sTblPtr);
    sTblPtr->state = SCHEDULETABLE_RUNNING;
    Irq_Restore(state);

    OS_STD_END_2(OSServiceId_StartScheduleTableAbs,sid, start);
}

/**
 *
 * @param sid
 * @return
 */
/** OS201 OS provides the service StartScheduleTableSynchron() */
/** OS525 StartScheduleTableSynchron() available in Scalability Classes 2 and 4. */
#if ( OS_SC2 == STD_ON ) || ( OS_SC4 == STD_ON )
StatusType StartScheduleTableSynchron(ScheduleTableType sid ){
    OsSchTblType *s_p;
    StatusType rv = E_OK;
    imask_t state;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */

    Irq_Save(state);

    SCHED_CHECK_ID(sid);

    /** OS387 */
    if( s_p->sync.syncStrategy != EXPLICIT ) {
        rv = E_OS_ID;
        goto err;
    }

    /** OS388 */
    if( s_p->state != SCHEDULETABLE_STOPPED ) {
        rv = E_OS_STATE;
        goto err;
    }

    /** OS389 */ /** OS435 */
    s_p->state = SCHEDULETABLE_WAITING;

    Irq_Restore(state);

    OS_STD_END_1(OSServiceId_StartScheduleTableSynchron,sid);
}
#endif



/** @req OS006 */
/** @req OS523 StopScheduleTable available in all Scalability Classes. */
/* IMPROVEMENT: Implement StopScheduleTable */
StatusType StopScheduleTable(ScheduleTableType sid) {
    StatusType rv = E_OK;
    OsSchTblType *sPtr;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */
    /** @req OS279 */
    SCHED_CHECK_ID(sid);
    sPtr = Os_SchTblGet(sid);

    /** @req OS280 */
    if(sPtr->state == SCHEDULETABLE_STOPPED ) {
        rv = E_OS_NOFUNC;
        goto err;
    }

    /** @req OS281 */
    sPtr->state = SCHEDULETABLE_STOPPED;

    OS_STD_END_1(OSServiceId_StopScheduleTable,sid);
}

/** @req OS191 */
/** @req OS524 NextScheduleTable available in all Scalability Classes. */
StatusType NextScheduleTable( ScheduleTableType sid_curr, ScheduleTableType sid_next) {
    StatusType rv = E_OK;
    (void)sid_curr;
    (void)sid_next;

    OsSchTblType *sFromPtr;
    OsSchTblType *sToPtr;

    imask_t state;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */

    /** @req OS282 */
    SCHED_CHECK_ID(sid_curr);
    SCHED_CHECK_ID(sid_next);

    sFromPtr = Os_SchTblGet(sid_curr);
    sToPtr = Os_SchTblGet(sid_next);

    /** @req OS330 */
    if( sFromPtr->counter != sToPtr->counter) {
        rv = E_OS_ID;
        goto err;
    }

    /** @req OS283 */
    if( (sFromPtr->state == SCHEDULETABLE_STOPPED) ||
        (sFromPtr->state == SCHEDULETABLE_NEXT) )
    {
        rv = E_OS_NOFUNC;
        goto err;
    }

    /** @req OS309 */
    if( sToPtr->state != SCHEDULETABLE_STOPPED ) {
        rv = E_OS_STATE;
        goto err;
    }

    Irq_Save(state);

    /** @req OS453 */
    if( sFromPtr->state == SCHEDULETABLE_STOPPED ) {
        sFromPtr->next->state = SCHEDULETABLE_STOPPED;
    } else {
        /** @req OS324 */
        if( sFromPtr->next != NULL ) {
            // Stop the schedule-table that was to be next.
            sFromPtr->next->state = SCHEDULETABLE_STOPPED;
        }

        sFromPtr->next = sToPtr;
        sToPtr->state = SCHEDULETABLE_NEXT;
        sToPtr->expire_curr_index = 0;
    }

    Irq_Restore(state);

    OS_STD_END_2(OSServiceId_NextScheduleTable,sid_curr, sid_next);
}



/**
 *
 * @param sid
 * @param globalTime
 * @return
 */
/** OS199 OS provides the service SyncScheduleTable() */
/** OS526 SyncScheduleTable() available in Scalability Classes 2 and 4. */
#if ( OS_SC2 == STD_ON ) || ( OS_SC4 == STD_ON )
StatusType SyncScheduleTable( ScheduleTableType ScheduleTableID, TickType Value  ) {
    StatusType rv = E_OK;
    OsSchTblType *s_p;
    imask_t state;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */

    SCHED_CHECK_ID(ScheduleTableID);
    s_p = Os_SchTblGet(ScheduleTableID);

    /** OS454 */
    if( s_p->sync.syncStrategy != EXPLICIT ) {
        rv =  E_OS_ID;
        goto err;
    }

    /** OS455 */
    if( Value > s_p->duration ) {
        rv = E_OS_VALUE;
        goto err;
    }

    Irq_Save(state);

    /** OS456 */
    if( (s_p->state == SCHEDULETABLE_STOPPED) ||
        (s_p->state == SCHEDULETABLE_NEXT)	) {
        rv = E_OS_STATE;
        goto err;
    }

    switch(s_p->state) {
    case  SCHEDULETABLE_WAITING:
        // First time we called since started. Set the sync counter to
        // the value provided.
        s_p->sync.syncCounter = Value;
        s_p->state = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
        break;

    case SCHEDULETABLE_RUNNING:
    case SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS:
        s_p->sync.deviation = s_p->sync.syncCounter - Value;
        if( s_p->sync.deviation != 0 ) {
            // We are not at sync any more...
            /** OS419 */
            s_p->state = SCHEDULETABLE_RUNNING;
        }
        break;

    default:
        ASSERT(0);
        break;
    }

    Irq_Restore(state);

    OS_STD_END_2(OSServiceId_SyncScheduleTable,ScheduleTableID, Value);
}
#endif


/**
 *
 * @param sid
 * @param status
 * @return
 */

/** @req OS528 GetScheduleTableStatus() available in all Scalability Classes. */
/** @req OS227 */
StatusType GetScheduleTableStatus( ScheduleTableType sid, ScheduleTableStatusRefType status ) {
    StatusType rv = E_OK;
    OsSchTblType *s_p;
    (void)status; //lint !e920 MISRA False positive. Allowed to cast pointer to void here.
    imask_t state;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */
    /** @req OS293 */
    SCHED_CHECK_ID(sid);

    s_p = Os_SchTblGet(sid);
    Irq_Save(state);

    switch(s_p->state) {
        /** @req OS289 */
    case SCHEDULETABLE_STOPPED:
        /** @req OS353 */
    case SCHEDULETABLE_NEXT:
        /** OS290 */
    case SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS:
        /** OS354 */
    case SCHEDULETABLE_WAITING:
        /** OS291 */
    case SCHEDULETABLE_RUNNING:
        *status = s_p->state;
        break;
    default:
        ASSERT(0);

    }

    Irq_Restore(state);

    OS_STD_END_2(OSServiceId_GetScheduleTableStatus,sid, status);
}


/**
 *
 * @param sid
 * @return
 */
/** OS422 OS provides the service SetScheduleTableAsync() */
/** OS527 SetScheduleTableAsync() available in Scalability Classes 2 and 4. */
#if ( OS_SC2 == STD_ON ) || ( OS_SC4 == STD_ON )
StatusType SetScheduleTableAsync( ScheduleTableType sid ) {
    StatusType rv = E_OK;
    OsSchTblType *s_p;
    imask_t state;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */

    SCHED_CHECK_ID(sid);
    s_p = Os_SchTblGet(sid);

    /** OS458 */
    if( s_p->sync.syncStrategy != EXPLICIT ) {
        rv = E_OS_ID;
        goto err;
    }

    Irq_Save(state);

    /** !req OS362 */ /** !req OS323 */ /** !req OS483 */

    /** OS300 */
    s_p->state = SCHEDULETABLE_RUNNING;

    Irq_Restore(state);

    OS_STD_END_1(OSServiceId_SetScheduleTableAsync,sid);
}
#endif



/**
 * Go through the schedule tables connected to this counter
 *
 * @param c_p Pointer to counter object
 */
void Os_SchTblCheck(OsCounterType *c_p) {
    /** @req OS002 */
    /** @req OS007 */

    OsSchTblType *sched_obj;

    /* Iterate through the schedule tables */
    SLIST_FOREACH(sched_obj,&c_p->sched_head,sched_list) {

        if( sched_obj->state == SCHEDULETABLE_STOPPED ) {
            continue;
        }

#if ( OS_SC2 == STD_ON ) || ( OS_SC4 == STD_ON )
        if( sched_obj->sync.syncStrategy == IMPLICIT ) {
            // ....

        } else {
            int adj;
            // Handle EXPLICIT
            if( sched_obj->sync.deviation > 0 ) {
                // The sync counter was set back ==
                // we have more time to complete the table
                adj = MIN(sched_obj->sync.deviation, getAdjExpPoint(sched_obj)->maxAdvance );
                sched_obj->sync.deviation -= adj;

            } else if( sched_obj->sync.deviation < 0 ) {
                // The sync counter was set forward ==
                // we have less time to complete the table
                adj = MIN((-sched_obj->sync.deviation), getAdjExpPoint(sched_obj)->maxRetard);
                sched_obj->sync.deviation -= adj;

            } else {
                // all is well
                sched_obj->state = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
            }
        }
#endif

        /* Check if the expire point have been hit */
        if( ((sched_obj->state == SCHEDULETABLE_RUNNING) ||
            (sched_obj->state == SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS) ) &&
            (c_p->val == sched_obj->expire_val) )
        {
            if ( sched_obj->expire_curr_index < SA_LIST_CNT(&sched_obj->expirePointList) ) {
                OsScheduleTableExpiryPointType * action;
                uint32_t i;

                action = SA_LIST_GET(&sched_obj->expirePointList,sched_obj->expire_curr_index);

                /** @req OS407 */
                /** @req OS412 */

                /* According to OS412 activate tasks before events */
                for(i=0; i< (uint32_t)action->taskListCnt;i++ ) {
                    (void)ActivateTask(action->taskList[i]);
                }

                for(i=0; i< (uint32_t)action->eventListCnt;i++ ) {
                    (void)SetEvent( action->eventList[i].task, action->eventList[i].event);
                }
            }
            // Calc new expire val and state
            Os_SchTblUpdateState(sched_obj);
        }

    }
}

/**
 *
 */
void Os_SchTblInit( void ) {
#if (OS_SCHTBL_CNT != 0)
    OsSchTblType *s_p;
    /*lint -e{681, 685, 568} Allow MISRA violations depending on configuration
     * MISRA 2004 14.1 (req), MISRA 2012 2.1 (req) unreachable code (if OS_SCHTBL_CNT == 0)
     * MISRA 2004 13.7 (req), MISRA 2012 2.1 (req) condition always false (if OS_SCHTBL_CNT == 0)
     */
    for( ScheduleTableType i=0; i < OS_SCHTBL_CNT;i++ ) {
        s_p = Os_SchTblGet(i);

        ScheduleTableConsistenyCheck(s_p);
    }
#endif
}

void Os_SchTblAutostart( void ) {
#if (OS_SCHTBL_CNT != 0)
    /*lint -e{681, 685, 568} Allow MISRA violations depending on configuration
     * MISRA 2004 14.1 (req), MISRA 2012 2.1 (req) unreachable code (if OS_SCHTBL_CNT == 0)
     * MISRA 2004 13.7 (req), MISRA 2012 2.1 (req) condition always false (if OS_SCHTBL_CNT == 0)
     */
    for(ScheduleTableType j=0; j < OS_SCHTBL_CNT; j++ ) {
        OsSchTblType *sPtr;
        sPtr = Os_SchTblGet(j);

        if( sPtr->autostartPtr != NULL ) {
            const struct OsSchTblAutostart *autoPtr = sPtr->autostartPtr;

            /* Check appmode */
            if( OS_SYS_PTR->appMode & autoPtr->appMode ) {

                /* Start the schedule table */
                switch(autoPtr->type) {
                case SCHTBL_AUTOSTART_ABSOLUTE:
                    (void)StartScheduleTableAbs(j,autoPtr->offset);
                    break;
                case SCHTBL_AUTOSTART_RELATIVE:
                    (void)StartScheduleTableRel(j,autoPtr->offset);
                    break;
    #if defined(OS_SC2) || defined(OS_SC4)
                case SCHTBL_AUTOSTART_SYNCHRONE:
                    /* IMPROVEMENT: Add support  */
                    break;
    #endif
                default:
                    ASSERT(0); 		// Illegal value
                    break;
                }
            }
        }
    }
#endif
}


