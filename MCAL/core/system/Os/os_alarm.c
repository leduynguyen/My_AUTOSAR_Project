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

#include "os_i.h"


#if (OS_ALARM_CNT!=0)
#define COUNTER_MAX(x) 			(x)->counter->alarm_base.maxallowedvalue
#define COUNTER_MIN_CYCLE(x) 	(x)->counter->alarm_base.mincycle
#define ALARM_CHECK_ID(x) 				\
    if( (x) > OS_ALARM_CNT) { \
        rv = E_OS_ID;					\
        goto err; 						\
    }


/**
 * The system service  GetAlarmBase  reads the alarm base
 * characteristics. The return value <Info> is a structure in which
 * the information of data type AlarmBaseType is stored.
 *
 * @param alarm_id  Reference to alarm
 * @param info Reference to structure with constants of the alarm base.
 * @return
 */
StatusType GetAlarmBase( AlarmType AlarmId, AlarmBaseRefType Info ) {
    StatusType rv = E_OK;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */
    ALARM_CHECK_ID(AlarmId);

#if (OS_SC3==STD_ON) || (OS_SC4==STD_ON)
    OsTaskVarType *currPcbPtr = Os_SysTaskGetCurr();
    OsAlarmType *aPtr =  Os_AlarmGet(AlarmId);

    if( currPcbPtr->constPtr->applOwnerId != aPtr->applOwnerId ) {
        APPL_CHECK_STATE(aPtr->applOwnerId);
        APPL_CHECK_ACCESS(currPcbPtr->constPtr->applOwnerId, aPtr->accessingApplMask);

#if	(OS_NUM_CORES > 1)
        if (Os_ApplGetCore(aPtr->applOwnerId) != GetCoreID()) {
            StatusType status = Os_NotifyCore(Os_ApplGetCore(aPtr->applOwnerId),
                                              OSServiceId_GetAlarmBase,
                                              AlarmId,
                                              (uint32_t)Info,
                                              0);
            return status;
        }
#endif
    }
#endif

    rv = Os_AlarmGetBase(AlarmId,Info);
    if (rv != E_OK) {
        goto err;
    }
    OS_STD_END_2(OSServiceId_GetAlarmBase,AlarmId, Info);
}


/**
 * The system service GetAlarm returns the relative value in ticks
 * before the alarm <AlarmID> expires.

 * @param AlarmId	Reference to an alarm
 * @param Tick[out]	Relative value in ticks before the alarm <AlarmID> expires.
 * @return
 */
StatusType GetAlarm(AlarmType AlarmId, TickRefType Tick) {
    StatusType rv = E_OK;
    imask_t flags;
    OsAlarmType *aPtr;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */
    ALARM_CHECK_ID(AlarmId);
    aPtr =  Os_AlarmGet(AlarmId);

#if (OS_SC3==STD_ON) || (OS_SC4==STD_ON)
    OsTaskVarType *currPcbPtr = Os_SysTaskGetCurr();

    if( currPcbPtr->constPtr->applOwnerId != aPtr->applOwnerId ) {
        APPL_CHECK_STATE(aPtr->applOwnerId);
        APPL_CHECK_ACCESS(currPcbPtr->constPtr->applOwnerId, aPtr->accessingApplMask);

#if	(OS_NUM_CORES > 1)
        if (Os_ApplGetCore(aPtr->applOwnerId) != GetCoreID()) {
            StatusType status = Os_NotifyCore(Os_ApplGetCore(aPtr->applOwnerId),
                                              OSServiceId_GetAlarm,
                                              AlarmId,
                                              (uint32_t)Tick,
                                              0);
            return status;
        }
#endif
    }
#endif

    Irq_Save(flags);
    if( aPtr->active == 0 ) {
        rv = E_OS_NOFUNC;
        Irq_Restore(flags);
        goto err;
    }

    *Tick = Os_CounterDiff( 	aPtr->expire_val,
                                Os_CounterGetValue(aPtr->counter),
                                Os_CounterGetMaxValue(aPtr->counter) );

    Irq_Restore(flags);

    OS_STD_END_2(OSServiceId_GetAlarm,AlarmId, Tick);
}




/**
 * The system service occupies the alarm <AlarmID> element.
 * After <increment> ticks have elapsed, the task assigned to the
 * alarm <AlarmID> is activated or the assigned event (only for
 * extended tasks) is set or the alarm-callback routine is called.
 *
 * @param alarm_id Reference to the alarm element
 * @param increment Relative value in ticks
 * @param cycle Cycle value in case of cyclic alarm. In case of single alarms, cycle shall be zero.
 * @return
 */

StatusType SetRelAlarm(AlarmType AlarmId, TickType Increment, TickType Cycle){
    StatusType rv = E_OK;
    imask_t flags;
    OsAlarmType *aPtr;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */
    ALARM_CHECK_ID(AlarmId);
    aPtr =  Os_AlarmGet(AlarmId);

    OS_DEBUG(D_ALARM,"SetRelAlarm id:%d inc:%u cycle:%u\n",
                    AlarmId,
                    (unsigned)Increment,
                    (unsigned)Cycle);

#if (OS_SC3==STD_ON) || (OS_SC4==STD_ON)

    OsTaskVarType *currPcbPtr = Os_SysTaskGetCurr();

    if( currPcbPtr->constPtr->applOwnerId != aPtr->applOwnerId ) {
        APPL_CHECK_STATE(aPtr->applOwnerId);
        APPL_CHECK_ACCESS(currPcbPtr->constPtr->applOwnerId, aPtr->accessingApplMask);

#if (OS_NUM_CORES > 1)
        if (Os_ApplGetCore(aPtr->applOwnerId) != GetCoreID()) {
            StatusType status = Os_NotifyCore(Os_ApplGetCore(aPtr->applOwnerId),
                                              OSServiceId_SetRelAlarm,
                                              AlarmId,
                                              Increment,
                                              Cycle);
            return status;
        }
#endif
    }
#endif

    if( (Increment == 0) || (Increment > COUNTER_MAX(aPtr)) ) {
        /** @req OS304 */
        rv =  E_OS_VALUE;
        goto err;
    } else {
        if( Cycle != 0 &&
            ( (Cycle < COUNTER_MIN_CYCLE(aPtr)) ||
              (Cycle > COUNTER_MAX(aPtr)) ) ) {
            /** @req OS304 */
            rv =  E_OS_VALUE;
            goto err;
        }
    }

    {
        Irq_Save(flags);
        if( aPtr->active == 1 ) {
                Irq_Restore(flags);
            rv = E_OS_STATE;
            goto err;
        }

        aPtr->active = 1;

        aPtr->expire_val = Os_CounterAdd(
                                Os_CounterGetValue(aPtr->counter),
                                COUNTER_MAX(aPtr),
                                Increment);
        aPtr->cycletime = Cycle;

        Irq_Restore(flags);
        OS_DEBUG(D_ALARM,"  expire:%u cycle:%u\n",
                (unsigned)aPtr->expire_val,
                (unsigned)aPtr->cycletime);
    }

    OS_STD_END_3(OSServiceId_SetRelAlarm,AlarmId, Increment, Cycle);
}

/**
 * The  system  service  occupies  the  alarm  <AlarmID>  element.
 * When <start> ticks are reached, the task assigned to the alarm
 *
 * If the absolute value <start> is very close to the current counter
 * value, the alarm may expire, and the task may become ready or
 * the  alarm-callback  may  be  called  before  the  system  service
 * returns to the user.
 * If  the  absolute  value  <start>  already  was  reached  before  the
 * system call, the alarm shall only expire when the absolute value
 * <start>  is  reached  again,  i.e.  after  the  next  overrun  of  the
 * counter.
 *
 * If <cycle> is unequal zero, the alarm element is logged on again
 * immediately after expiry with the relative value <cycle>.
 *
 * The alarm <AlarmID> shall not already be in use.
 * To  change  values  of  alarms  already  in  use  the  alarm  shall  be
 * cancelled first.
 *
 * If  the  alarm  is  already  in  use,  this  call  will  be  ignored  and  the
 * error E_OS_STATE is returned.
 *
 * Allowed on task level and in ISR, but not in hook routines.
 *
 * @param AlarmId
 * @param Start
 * @param Cycle
 * @return
 */

StatusType SetAbsAlarm(AlarmType AlarmId, TickType Start, TickType Cycle) {
    imask_t flags;
    StatusType rv = E_OK;
    OsAlarmType *aPtr;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */
    ALARM_CHECK_ID(AlarmId);
    aPtr =  Os_AlarmGet(AlarmId);

#if (OS_SC3==STD_ON) || (OS_SC4==STD_ON)
    OsTaskVarType *currPcbPtr = Os_SysTaskGetCurr();

    if( currPcbPtr->constPtr->applOwnerId != aPtr->applOwnerId ) {
        APPL_CHECK_STATE(aPtr->applOwnerId);
        APPL_CHECK_ACCESS(currPcbPtr->constPtr->applOwnerId, aPtr->accessingApplMask);

#if (OS_NUM_CORES > 1)
        if (Os_ApplGetCore(aPtr->applOwnerId) != GetCoreID()) {
            StatusType status = Os_NotifyCore(Os_ApplGetCore(aPtr->applOwnerId),
                                              OSServiceId_SetAbsAlarm,
                                              AlarmId,
                                              Start,
                                              Cycle);
            return status;
        }
#endif
    }
#endif

    OS_VALIDATE( ! (Start > COUNTER_MAX(aPtr)), E_OS_VALUE );    /** @req OS304 */

    if( Cycle != 0 &&
        ( (Cycle < COUNTER_MIN_CYCLE(aPtr)) ||
          (Cycle > COUNTER_MAX(aPtr)) ) ) {
        /** @req OS304 */
        rv =  E_OS_VALUE;
        goto err;
    }

    Irq_Save(flags);
    if( aPtr->active == 1 ) {
        rv = E_OS_STATE;
        Irq_Restore(flags);
        goto err;
    }

    aPtr->active = 1;

    aPtr->expire_val = Start;
    aPtr->cycletime = Cycle;

    Irq_Restore(flags);

    OS_DEBUG(D_ALARM,"  expire:%u cycle:%u\n",
                    (unsigned)aPtr->expire_val,
                    (unsigned)aPtr->cycletime);

    OS_STD_END_3(OSServiceId_SetAbsAlarm,AlarmId, Start, Cycle);
}

StatusType CancelAlarm(AlarmType AlarmId) {
    StatusType rv = E_OK;
    OsAlarmType *aPtr;
    imask_t flags;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );   /* @req 4.1.2/SWS_Os_00093 */
    ALARM_CHECK_ID(AlarmId);

    aPtr = Os_AlarmGet(AlarmId);

#if (OS_SC3==STD_ON) || (OS_SC4==STD_ON)
    OsTaskVarType *currPcbPtr = Os_SysTaskGetCurr();

    if( currPcbPtr->constPtr->applOwnerId != aPtr->applOwnerId ) {
        APPL_CHECK_STATE(aPtr->applOwnerId);
        APPL_CHECK_ACCESS(currPcbPtr->constPtr->applOwnerId, aPtr->accessingApplMask);
    }
#if	(OS_NUM_CORES > 1)
    if (Os_ApplGetCore(aPtr->applOwnerId) != GetCoreID()) {
        StatusType status = Os_NotifyCore(Os_ApplGetCore(aPtr->applOwnerId),
                                          OSServiceId_CancelAlarm,
                                          AlarmId,
                                          0,
                                          0);
        return status;
    }
#endif
#endif

    Irq_Save(flags);
    if( aPtr->active == 0 ) {
        rv = E_OS_NOFUNC;
        Irq_Restore(flags);
        goto err;
    }

    aPtr->active = 0;

    Irq_Restore(flags);

    OS_STD_END_1(OSServiceId_CancelAlarm,AlarmId);
}



/**
 *
 * @param a_obj
 */
static void AlarmProcess( OsAlarmType *aPtr ) {
    if( aPtr->cycletime == 0 ) {
        aPtr->active = 0;
    } else {
        // Calc new expire value..
        aPtr->expire_val = Os_CounterAdd( Os_CounterGetValue(aPtr->counter),
                                            Os_CounterGetMaxValue(aPtr->counter),
                                            aPtr->cycletime);
    }
}

void Os_AlarmCheck( OsCounterType *c_p ) {
    OsAlarmType *a_obj;
    StatusType rv;

    SLIST_FOREACH(a_obj,&c_p->alarm_head,alarm_list) {
        if( a_obj->active && (c_p->val == a_obj->expire_val) ) {
            /* Check if the alarms have expired */
            OS_DEBUG(D_ALARM,"expired %s id:%u val:%u\n",
                                            a_obj->name,
                                            (unsigned)a_obj->counter_id,
                                            (unsigned)a_obj->expire_val);

            switch( a_obj->action.type ) {
            case ALARM_ACTION_ACTIVATETASK:
                if( ActivateTask(a_obj->action.task_id) != E_OK ) {
                    /* We actually do thing here, See 0S321 */
                }
                AlarmProcess(a_obj);
                break;
            case ALARM_ACTION_SETEVENT:
                rv =  SetEvent(a_obj->action.task_id,a_obj->action.event_id);
                if( rv != E_OK ) {
                    ERRORHOOK(rv);
                }
                AlarmProcess(a_obj);
                break;
            case ALARM_ACTION_ALARMCALLBACK:
                /* IMPROVEMENT: not done */
                break;

            case ALARM_ACTION_INCREMENTCOUNTER:
                /** @req OS301 */
                (void)IncrementCounter(a_obj->action.counter_id);
                AlarmProcess(a_obj);
                break;
            default:
                ASSERT(0);
            }
        }
    }
}

void Os_AlarmAutostart(void) {

	AlarmType j;

	/* @req OS476
	 * The Operating System module shall allow to automatically start
	 * preconfigured absolute alarms during the start of the Operating System.
	 */
    for (j = 0; j < OS_ALARM_CNT; j++) {
        if (Os_OnRunningCore(OBJECT_ALARM,j)) {
            OsAlarmType *alarmPtr;
            alarmPtr = Os_AlarmGet(j);
            if (alarmPtr->autostartPtr != NULL) {
                const OsAlarmAutostartType *autoPtr = alarmPtr->autostartPtr;

                if (OS_SYS_PTR->appMode & autoPtr->appModeRef) {
                    if (autoPtr->autostartType == ALARM_AUTOSTART_ABSOLUTE) {
                        (void)SetAbsAlarm(j, autoPtr->alarmTime, autoPtr->cycleTime);
                    } else {
                        (void)SetRelAlarm(j, autoPtr->alarmTime, autoPtr->cycleTime);
                    }
                }
            }
        }
    }
}
#endif


