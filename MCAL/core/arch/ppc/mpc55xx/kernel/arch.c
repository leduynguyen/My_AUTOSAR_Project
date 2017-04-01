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
#include "Cpu.h"
#include "asm_ppc.h"
#include "mpc55xx.h"
#include "arch_stack.h"
#include "irq.h"
#include "arch.h"
#include <stdio.h>

#define USE_LDEBUG_PRINTF
#include "debug.h"
/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/


StatusType Os_ArchGetProtectionType( uint32 exception ) {
    StatusType rv;

    if( (exception == EXCEPTION_IVOR3) || (exception == EXCEPTION_IVOR14) ) {
        /* @req 4.1.2/SWS_OS_00245 *//* @req OS245 Instruction exceptions */
        rv = E_OS_PROTECTION_EXCEPTION;
    } else if( (exception == EXCEPTION_IVOR1) || (exception == EXCEPTION_IVOR2) || (exception == EXCEPTION_IVOR13 ) ) {
        /* On MPC5643L MPU protection errors are reported as machinecheck */

        /* @req 4.1.2/SWS_OS_00044 Memory Access violation */
        /* @req OS044
         * If a memory access violation is detected, the Operating System module shall call the Protection Hook */
        rv = E_OS_PROTECTION_MEMORY;
    } else {
        /* Panic on the rest
         * 0,5,6,7,9,11,12
         * Handled by the OS 4,8*,10
         *  *) if memory protection is used.
         */
        rv = E_OS_ILLEGAL;
    }

    return rv;
}

void Os_MMSetSupervisorMode( void ) {
    /* Nothing to do here */
}


unsigned int Os_ArchGetScSize( void ) {
    return sizeof(Os_ExceptionFrameType) + sizeof(Os_IsrFrameType);
}

extern void Os_TaskPost( void );


/**
 * Setup a context for a task.
 *
 * @param pcb Pointer to the pcb to setup
 */
void Os_ArchSetupContext( OsTaskVarType *pcbPtr ) {
    Os_ExceptionFrameType *excPtr = (Os_ExceptionFrameType *)((char *)pcbPtr->stack.curr + sizeof(Os_IsrFrameType)) ;
    Os_IsrFrameType *cPtr = (Os_IsrFrameType *)pcbPtr->stack.curr;
    uint32_t msr;
    msr = (MSR_EE | MSR_ME | MSR_CE);

#if defined(CFG_SPE)  || defined(CFG_SPE_INIT)   // || defined(CFG_EFPU) Not need for EFPU only accessing lower 32 bits
    msr |= MSR_SPE;
#endif

#if (OS_SC3==STD_ON) || (OS_SC4==STD_ON)
    if( !Os_AppConst[pcbPtr->constPtr->applOwnerId].trusted ) {
        // Non-trusted = User mode..
        msr |= MSR_PR; //  | MSR_DS | MSR_IS;
    }
#endif
    pcbPtr->regs[0] = msr;
#if (OS_SC3==STD_ON) || (OS_SC4==STD_ON)
    /* Stack, start and end */
    pcbPtr->regs[MPU0_REG_TASK_STACK_START] = (uint32_t)pcbPtr->stack.top;
    pcbPtr->regs[MPU0_REG_TASK_STACK_END] = (uint32_t)pcbPtr->stack.top + (uint32_t)pcbPtr->stack.size;
    /* Data, start and stop */
    pcbPtr->regs[MPU0_REG_TASK_DATA_START] = (uint32_t)pcbPtr->constPtr->dataStart;
    pcbPtr->regs[MPU0_REG_TASK_DATA_END] = (uint32_t)pcbPtr->constPtr->dataEnd;

    /* Data, start and stop */
    pcbPtr->regs[MPU0_REG_TASK_BSS_START] = (uint32_t)pcbPtr->constPtr->bssStart;
    pcbPtr->regs[MPU0_REG_TASK_BSS_END] = (uint32_t)pcbPtr->constPtr->bssEnd;
#endif

    cPtr->pattern = ISR_PATTERN;
#if defined(CFG_EFPU) || defined(CFG_SPE_FPU_SCALAR_SINGLE)
    cPtr->fscr = get_spr(SPR_SPEFSCR);			/* SPEFSCR */
#endif

    excPtr->srr0 = (uint32_t)pcbPtr->constPtr->entry;
    excPtr->srr1 = (uint32_t)msr;
    excPtr->lr = (uint32_t)Os_TaskPost;
}

/**
 *
 * @param pcbPtr
 */

void Os_ArchSetTaskEntry(OsTaskVarType *pcbPtr ) {
    /* Not used, setup in Os_ArchSetupContext() instead */
    (void)pcbPtr; //lint !e920 MISRA False positive. Allowed to cast pointer to void here.
}

void Os_ArchInit( void ) {

    unsigned long msr = get_msr();
#if defined(CFG_SPE)  || defined(CFG_SPE_INIT)   // || defined(CFG_EFPU) Not needed for EFPU instructions that only access low 32 bits
    msr |= MSR_SPE;
#endif
    msr |= MSR_ME;	/* We want IVOR1 instead of checkstop */
    set_msr(msr);

#if (OS_SC3 == STD_ON) || (OS_SC4 == STD_ON)
    Os_MMInit();
#endif

}

#if (OS_NUM_CORES > 1)
#define LOGICAL_ID_Z0_CORE	1
#define LOGICAL_ID_Z1_CORE	0

extern void _start_z0(void);
boolean Os_StartCore(CoreIDType id) {
    if (id == LOGICAL_ID_Z0_CORE) {
        CRP.Z0VEC.R = (unsigned int) _start_z0;
        return TRUE;
    } else {
        return FALSE;
    }
}

volatile OsCoreMessageBoxType Os_MessageBox[OS_NUM_CORES];

StatusType Os_NotifyCore(CoreIDType coreId, OsServiceIdType op, uint32_t arg1,uint32_t arg2,uint32_t arg3) {
    /* Other tasks shall not be able to modify the messageBox.
     * But Interrupts must be enabled otherwise a deadlock can occur if both cores
     * calls ActivateTask. */
    GetResource(RES_SCHEDULER);
    Os_MessageBox[coreId].op = op;
    Os_MessageBox[coreId].arg1 = arg1;
    Os_MessageBox[coreId].arg2 = arg2;
    Os_MessageBox[coreId].arg3 = arg3;
    Os_MessageBox[coreId].opFinished = false;
    StatusType result;
    // IMPROVEMENT: defines for other cores should be generated
    if (OS_CORE_IS_ID_MASTER(coreId)) {
        Irq_GenerateSoftInt(INTC_SSCIR0_CLR6);
    } else {
        Irq_GenerateSoftInt(INTC_SSCIR0_CLR5);
    }
    while (!Os_MessageBox[coreId].opFinished) {
        // wait until receiving core has finished
    }
    result = Os_MessageBox[coreId].result;
    ReleaseResource(RES_SCHEDULER);
    return result;
}

ISR(notify) {
    StatusType rv;
    OsServiceIdType op = Os_MessageBox[GetCoreID()].op;

    /* NOTE: We are now at intNestCnt >1. Some system calls specifically
     * check that intNestCnt equals 0 which causes them to fail in this case.
     * Doing the hack below causes problems with ActivateTask not returning
     * and thus opFinished is never set. */
    //--OS_SYS_PTR->intNestCnt;

    switch( op ) {
    case OSServiceId_ActivateTask:
        rv = ActivateTask( (TaskType) Os_MessageBox[GetCoreID()].arg1);
        break;
    case OSServiceId_ChainTask:
        rv = ChainTask( (TaskType) Os_MessageBox[GetCoreID()].arg1);
        break;
    case OSServiceId_GetTaskState:
        rv = GetTaskState( (TaskType) Os_MessageBox[GetCoreID()].arg1,
                          ( TaskStateRefType ) Os_MessageBox[GetCoreID()].arg2);
        break;
    case OSServiceId_SetEvent:
        rv = SetEvent(Os_MessageBox[GetCoreID()].arg1,
                      Os_MessageBox[GetCoreID()].arg2);
        break;
    case OSServiceId_GetCounterValue:
        rv = GetCounterValue(Os_MessageBox[GetCoreID()].arg1,
                             ( TickRefType ) Os_MessageBox[GetCoreID()].arg2);
        break;
    case OSServiceId_GetElapsedValue:
        rv = GetElapsedCounterValue(Os_MessageBox[GetCoreID()].arg1,
                                    (TickRefType ) Os_MessageBox[GetCoreID()].arg2,
                                    ( TickRefType ) Os_MessageBox[GetCoreID()].arg3);
        break;
#if (OS_ALARM_CNT!=0)
    case OSServiceId_GetAlarmBase:
        rv = GetAlarmBase(Os_MessageBox[GetCoreID()].arg1,
                          (AlarmBaseRefType) Os_MessageBox[GetCoreID()].arg2);
        break;
    case OSServiceId_GetAlarm:
        rv = GetAlarm(Os_MessageBox[GetCoreID()].arg1,
                      (TickRefType) Os_MessageBox[GetCoreID()].arg2);
        break;
    case OSServiceId_SetRelAlarm:
        rv = SetRelAlarm(Os_MessageBox[GetCoreID()].arg1,
                         Os_MessageBox[GetCoreID()].arg2,
                         Os_MessageBox[GetCoreID()].arg3);
        break;
    case OSServiceId_SetAbsAlarm:
        rv = SetAbsAlarm(Os_MessageBox[GetCoreID()].arg1,
                         Os_MessageBox[GetCoreID()].arg2,
                         Os_MessageBox[GetCoreID()].arg3);
        break;
    case OSServiceId_CancelAlarm:
        rv = CancelAlarm(Os_MessageBox[GetCoreID()].arg1);
        break;
#endif
    default:
        ASSERT(0);
    }

    Os_MessageBox[GetCoreID()].result = rv;
    msync(); //IMPROVEMENT: needed?
    Os_MessageBox[GetCoreID()].opFinished = true;

    //OS_SYS_PTR->intNestCnt++;
}

void Os_CoreNotificationInit() {
#if (OS_NUM_CORES > 1)
    if (OS_CORE_IS_ID_MASTER(GetCoreID())) {
        /* OS_CORE_<index>_MAIN_APPLICATION are generated */
        ISR_INSTALL_ISR2( "z1_notify", notify, INTC_SSCIR0_CLR6, 6, OS_CORE_0_MAIN_APPLICATION);
    } else {
        ISR_INSTALL_ISR2( "z0_notify", notify, INTC_SSCIR0_CLR5, 6, OS_CORE_1_MAIN_APPLICATION);
    }
#endif
}
#endif
