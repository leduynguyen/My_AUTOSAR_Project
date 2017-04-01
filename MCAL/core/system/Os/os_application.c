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

/* ----------------------------[includes]------------------------------------*/

#include "os_i.h"
/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
#if OS_APPLICATION_CNT!=0
OsAppVarType Os_AppVar[OS_APPLICATION_CNT];
#endif

/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/
/* ----------------------------[General requirements handled in this functions]----------------------------*/
/* @req OS547
 *   Availability of AllowAccess(): Available in Scalability Classes 3 and 4.
 * OS536
 *    Availability of TerminateApplication(): Available in Scalability Classes 3 and 4.
 * OS520
 *    Availability of CheckObjectOwnership():Available in Scalability Classes 3 and 4.
 * @req OS514
 *    Availability of GetApplicationID():Available in Scalability Classes 3 and 4.
 * @req OS519
 *    Availability of CheckObjectAccess():Available in Scalability Classes 3 and 4.
 * @req OS537
 *    Availability of GetApplicationState(): Available in Scalability Classes 3 and 4.
 *
 */

#if (OS_APPLICATION_CNT > 1) && ((OS_SC1 == STD_ON )||(OS_SC2 == STD_ON )) && (OS_NUM_CORES==1)
#error Cant configure more than one application on SC1 and SC1 if on single-core
#endif

#if	(OS_USE_APPLICATIONS == STD_ON)
#if ((OS_SC3 == STD_ON) || (OS_SC4 == STD_ON))
/**
 * This service determines the currently running OS-Application (a unique
 * identifier has to be allocated to each application).
 *
 * @return <identifier of running OS-Application> or INVALID_OSAPPLICATION
 */
/** @req OS016  OS provides the service GetApplicationID() */
ApplicationType GetApplicationID( void ) {
    /** @req OS261 *//** !req OS262 */
    return OS_SYS_PTR->currApplId;
}

/**
 * A (trusted or non-trusted) OS-Application uses this service to call a trusted
 * function
 *
 * @param FunctionIndex		Index of the function to be called.
 * @param FunctionParams    Pointer to the parameters for the function -
 * 							specified by the FunctionIndex - to be called.
 * 							If no parameters are provided, a NULL pointer has
 * 							to be passed.
 * @return
 */
StatusType CallTrustedFunction( TrustedFunctionIndexType FunctionIndex,
        TrustedFunctionParameterRefType FunctionParams ) {

    (void)FunctionIndex;
    (void)FunctionParams; //lint !e920 MISRA False positive. Allowed to cast pointer to void here.
    return E_OK;
}

/**
 * This service checks if a memory region is write/read/execute accessible
 * and also returns information if the memory region is part of the stack
 * space.
 *
 * @param ISRID		ISR reference
 * @param Address   Start of memory area
 * @param Size      Size of memory area
 * @return
 */
AccessType CheckISRMemoryAccess( ISRType isrId,
        MemoryStartAddressType address,
        MemorySizeType size )
{
    //lint -e(923) MISRA 2004 11.3, MISRA 2012 11.4 (adv) Allow pointer to ptrdiff_t cast
    ptrdiff_t addr = (ptrdiff_t)address;
    (void)addr;
    (void)size;

    if( isrId > (ISRType)OS_ISR_CNT ) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return 0;
    }

    /** !req OS449 */
    return 0;
}
/**
 * This service checks if a memory region is write/read/execute accessible
 * and also returns information if the memory region is part of the stack
 * space.
 *
 * Check returned accesstype with:
 *   OSMEMORY_IS_READABLE(<AccessType>)
 *   OSMEMORY_IS_WRITEABLE(<AccessType>)
 *   OSMEMORY_IS_EXECUTABLE(<AccessType>)
 *   OSMEMORY_IS_STACKSPACE(<AccessType>)
 *
 * NOTE: Not really sure what this function is actually good for? Add a use-case!
 *
 * @param TaskID   Task reference
 * @param Address  Start of memory area
 * @param Size     Size of memory area
 * @return
 */
AccessType CheckTaskMemoryAccess( TaskType taskId,
        MemoryStartAddressType address,
        MemorySizeType size )
{
    //lint -e(923) MISRA 2004 11.3, MISRA 2012 11.4 (adv) Allow pointer to ptrdiff_t cast
    ptrdiff_t addr = (ptrdiff_t)address;
    (void)addr;
    (void)size;

    if( taskId > OS_TASK_CNT ) {
        /*lint -e{904} Return statement is necessary to avoid multiple if loops and hence increase readability in case of argument check */
        return 0;
    }

    /* IMPROVEMENT: Add body */
    return 0;
}

/**
 * This service determines if the OS-Applications, given by ApplID,
 * is allowed to use the IDs of a Task, ISR, Resource, Counter,
 * Alarm or Schedule Table in API calls.
 *
 * @param ApplID      OS-Application identifier
 * @param ObjectType  Type of the following parameter
 * @param object      The object to be examined
 * @return ACCESS if the ApplID has access to the object
 * NO_ACCESS otherwise
 */
/** @req OS256 OS provides the service CheckObjectAccess() */
/** @req OS450 CheckObjectAccess checks access rights for Operating System objects. */
ObjectAccessType CheckObjectAccess( ApplicationType ApplId,
        ObjectTypeType ObjectType,
        uint32_t objectId )
{
    uint32 appMask = APPL_ID_TO_MASK(ApplId);
    ObjectAccessType rv = NO_ACCESS;
    _Bool rvMask = 0;


    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );    /* @req 4.1.2/SWS_Os_00093 */

    /* @req OS423
     * If in a call of CheckObjectAccess() the object to  be examined
     * is not avalid object OR <ApplID> is invalid OR <ObjectType> is
     * invalid THEN CheckObjectAccess() shall return NO_ACCESS.
     */
    if( ApplId >= (ApplicationType)OS_APPLICATION_CNT ) {
        goto err;
    }

    /* @req OS272
     * If the OS-Application <ApplID> in a call of CheckObjectAccess() has no
     * access to the queried object, CheckObjectAccess() shall return NO_ACCESS.
     *
     * NOTE: Could be that OS450 comes into play here....and then this is wrong.
     */
    if( Os_AppVar[ApplId].state != APPLICATION_ACCESSIBLE ) {
        goto err;
    }

    //lint -e{685, 568} Allow MISRA violations depending on configuration (if _CNT == 0)
    switch( ObjectType ) {
        case OBJECT_ALARM:
#if (OS_ALARM_CNT != 0)
            if (objectId < OS_ALARM_CNT) {
                OsAlarmType *lPtr = Os_AlarmGet((AlarmType)objectId);
                if (lPtr != NULL) {
                    rvMask = lPtr->accessingApplMask & (appMask);
                }
            }
#endif
            break;
        case OBJECT_COUNTER:
#if (OS_COUNTER_CNT != 0)
            if (objectId < OS_COUNTER_CNT) {
                OsCounterType *lPtr = Os_CounterGet((CounterType)objectId);
                if (lPtr != NULL) {
                    rvMask = lPtr->accessingApplMask & (appMask);
                }
            }
            break;
#endif
        case OBJECT_ISR:
        {
            /* An ISR do not have accessingApplicationMask, just check if owner */
            const OsIsrVarType *lPtr = Os_IsrGet((ISRType)objectId);
            if(lPtr != NULL) {
                rvMask = (lPtr->constPtr->appOwner == ApplId);
            }
            break;
        }
        case OBJECT_MESSAGE:
        break;
        case OBJECT_RESOURCE:
#if (OS_RESOURCE_CNT != 0)
            if (objectId < OS_RESOURCE_CNT) {
                OsResourceType *lPtr = Os_ResourceGet((ResourceType)objectId);
                if(lPtr != NULL) {
                    rvMask = lPtr->accessingApplMask & (appMask);
                }
            }
            break;
#endif
        case OBJECT_SCHEDULETABLE:
#if (OS_SCHTBL_CNT != 0)
            if (objectId < OS_SCHTBL_CNT) {
                OsSchTblType *lPtr = Os_SchTblGet((ScheduleTableType)objectId);
                if(lPtr != NULL) {
                    rvMask = lPtr->accessingApplMask & (appMask);
                }
            }
#endif
            break;
        case OBJECT_TASK:
        {
            if (objectId < OS_TASK_CNT) {
                OsTaskVarType *lPtr = Os_TaskGet((TaskType)objectId);
                if(lPtr != NULL) {
                    rvMask = lPtr->constPtr->accessingApplMask & (appMask);
                }
            }
            break;
        }
        default:
        /* @req OS423 */
        // rvMask = NO_ACCESS;
        break;
    }

    /** @req OS271 *//** @req OS272 */
    rv = rvMask ? ACCESS : NO_ACCESS;

    //lint -save -e632 -e641  PC-lint exception, allow ERRORHOOK to use ObjectAccessType, as OS_STD_END_3 use this as return type
    OS_STD_END_3(OSServiceId_CheckObjectAccess,ApplId,ObjectType,objectId);
    //lint -restore
}


/**
 * This service terminates the OS-Application to which the calling Task/Category 2
 * ISR/application specific error hook belongs.
 *
 * @param 	Application - The identifier of the OS-Application to be terminated.
 * 			If the caller belongs to <Application> the call results in a
 * 			self termination.
 *
 * @param 	RestartOption - Either RESTART for doing a restart of the
 * 			OS-Application or NO_RESTART if OS-Application shall not be restarted.
 *
 * @return  E_OK: No errors
 * 			E_OS_ID: <Application> was not valid
 * 			E_OS_VALUE: <RestartOption> was neither RESTART nor NO_RESTART
 * 			E_OS_ACCESS: The caller does not have the right to terminate <Application>
 * 			E_OS_STATE: The state of <Application> does not allow terminating <Application>
 */
StatusType TerminateApplication( ApplicationType applId, RestartType restartOption ) {
    StatusType rv = E_OK;

    (void)applId;
    (void)restartOption;


    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );    /* @req 4.1.2/SWS_Os_00093 */
    OS_VALIDATE( applId < (ApplicationType)OS_APPLICATION_CNT, E_OS_ID); /* @req 4.1.2/SWS_Os_00493 *//** OS493 */
    OS_VALIDATE( restartOption <= NO_RESTART, E_OS_VALUE); /* @req 4.1.2/SWS_Os_00459 *//** OS459 */
    OS_VALIDATE( !(Os_ApplGet(applId)->state == APPLICATION_TERMINATED), E_OS_STATE); /* @req 4.1.2/SWS_Os_00507 *//** OS507 */

    if( applId != OS_SYS_PTR->currApplId ) {
        OS_VALIDATE( !(Os_ApplGet(applId)->state == APPLICATION_RESTARTING), E_OS_ID); /* @req 4.1.2/SWS_Os_00508 */

        /* OS548 */
        if( (Os_ApplGet(applId)->state == APPLICATION_RESTARTING ) &&
                ( applId == OS_SYS_PTR->currApplId ) &&
                ( restartOption == RESTART ) ) {
            rv = E_OS_STATE;
            goto err;
        }

        /* IMPROVEMENT: MISSING OS503, OS494, OS287, OS535  */
        /** !req OS503 *//** !req OS494 *//** !req OS287 *//** !req OS535 */
    }

    OS_STD_END_2(OSServiceId_TerminateApplication,applId,restartOption);
}

/**
 * This service sets the own state of an OS-Application from
 * APPLICATION_RESTARTING to APPLICATION_ACCESSIBLE.
 *
 * @return  E_OK : No errors
 * 			E_OS_STATE : The OS-Application of the caller is in the wrong
 state
 */
/** @req OS501 OS provides the service AllowAccess() */
StatusType AllowAccess( void ) {
    StatusType rv = E_OK;
    ApplicationType applId = OS_SYS_PTR->currApplId;

    /* @req OS497
     * If the state of the OS-Application of the caller of AllowAccess() is not APPLICATION_RESTARTING
     * AllowAccess() shall return E_OS_STATE. */
    OS_VALIDATE( !(Os_ApplGetState(applId) != APPLICATION_RESTARTING), E_OS_STATE );

    /* @req OS498
     * If the state of the OS-Application of the caller of AllowAccess() is APPLICATION_RESTARTING,
     * AllowAccess() shall set the state to APPLICATION_ACCESSIBLE and
     * allow other OS-Applications to access the configured objects of the callers OS-Application. */
    Os_ApplSetState(applId, APPLICATION_ACCESSIBLE);

    OS_STD_END(OSServiceId_AllowAccess);
}

/**
 * This service returns the current state of an OS-Application.
 * SC: SC3 and SC4
 *
 * @param ApplId 		The OS-Application from which the state is requested
 * @param Value 		The current state of the application
 * @return  E_OK: No errors, E_OS_ID: <Application> is not valid
 */
/**
 * @req OS499
 * This service returns the current state of an OS-Application.
 */
StatusType GetApplicationState( ApplicationType applId, ApplicationStateRefType value ) {
    StatusType rv = E_OK;


    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );    /* @req 4.1.2/SWS_Os_00093 */
	/* @req OS495
	 * If the <Application> in a call of GetApplicationState() is not valid GetApplicationState() shall return E_OS_ID.
	 */
    OS_VALIDATE(applId < (ApplicationType)OS_APPLICATION_CNT, E_OS_ID);
    /* @req OS496
     * If the parameters in a call of GetApplicationState() are valid,
     * GetApplicationState() shall return the state of OS-Application <Application> in <Value>.
     */
    *value = Os_ApplGetState(applId);

    OS_STD_END_2(OSServiceId_GetApplicationState,applId,value);
}
#endif // #if ((OS_SC3 == STD_ON) || (OS_SC4 == STD_ON))

/**
 * This service determines to which OS-Application a given Task, ISR, Resource,
 * Counter, Alarm or Schedule Table belongs
 *
 * @param ObjectType Type of the following parameter
 * @param object     The object to be examined
 * @return The OS-Application to which the object ObjectType belongs or
 * INVALID_OSAPPLICATION if the object does not exists
 */
/** @req OS017 OS provides the service CheckObjectOwnership() */
ApplicationType CheckObjectOwnership( ObjectTypeType ObjectType,
        uint32_t objectId )
{
    ApplicationType rv = INVALID_OSAPPLICATION;

    OS_VALIDATE( (Os_SysIntAnyDisabled() == FALSE) , E_OS_DISABLEDINT );    /* @req 4.1.2/SWS_Os_00093 */

    switch( ObjectType ) {
        case OBJECT_ALARM:
        rv = Os_AlarmGetApplicationOwner((AlarmType)objectId);
        break;
        case OBJECT_COUNTER:
        rv = Os_CounterGetApplicationOwner((CounterType)objectId);
        break;
        case OBJECT_ISR:
        rv = Os_IsrGetApplicationOwner((ISRType)objectId);
        break;
        case OBJECT_MESSAGE:
#if 0
        if( objectId < OS_SCHTBL_CNT ) {
            rv = Os_SchTblkGetApplicationOwner((TaskType)objectId);
        }
#endif
        break;
        case OBJECT_RESOURCE:
        rv = Os_ResourceGetApplicationOwner((ResourceType)objectId);
        break;
        case OBJECT_SCHEDULETABLE:
        rv = Os_SchTblGetApplicationOwner((ScheduleTableType)objectId);
        break;
        case OBJECT_TASK:
        rv = Os_TaskGetApplicationOwner((TaskType)objectId);
        break;
        default:
        /** @req OS274 */
        rv = INVALID_OSAPPLICATION;
        break;
    }

    if( rv == INVALID_OSAPPLICATION ) {
        goto err;
    }

    /** @req OS273 */
    //lint -save -e632  PC-lint exception, allow ERRORHOOK to use ApplicationType, as OS_STD_END_2 use this as return type
    OS_STD_END_2(OSServiceId_CheckObjectOwnership,ObjectType,objectId);
    //lint -restore
}


/**
 * IMPROVEMENT: Move somewhere else
 * @param mode
 * @return
 */
StatusType GetActiveApplicationMode( AppModeType* mode) {
    *mode = OS_SYS_PTR->appMode;
    return E_OK;
}

/**
 *
 */
void Os_ApplStart( void ) {
    uint16_t i;

    /* Call startuphooks for all applications */
    for(i=0;i<OS_APPLICATION_CNT;i++) {
        /** @req OS500 */
        Os_AppVar[i].state = APPLICATION_ACCESSIBLE;

        if( Os_AppConst[i].StartupHook != NULL ) {
            /** @req OS060 */
            Os_AppConst[i].StartupHook();
        }
    }
}

#endif // #if	(OS_USE_APPLICATIONS == STD_ON)
