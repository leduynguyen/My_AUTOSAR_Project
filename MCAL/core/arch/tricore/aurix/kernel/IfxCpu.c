/**
 * \file IfxCpu.c
 * \brief CPU  basic functionality
 *
 * \version iLLD_0_1_0_6
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxCpu.h"
#include "IfxScu_cfg.h"

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

Ifx_CPU *IfxCpu_getAddress(IfxCpu_ResourceCpu cpu)
{
    Ifx_CPU *module;

    if (cpu < IfxCpu_ResourceCpu_none)
    {
        module = (Ifx_CPU *)IfxCpu_cfg_indexMap[cpu].module;
    }
    else
    {
        module = NULL_PTR;
    }

    return module;
}


IfxCpu_CoreMode IfxCpu_getCoreMode(Ifx_CPU *cpu)
{
    IfxCpu_CoreMode    cpuMode;
    Ifx_CPU_DBGSR      dbgsr;
    IfxCpu_ResourceCpu index = IfxCpu_getIndex(cpu);

    cpuMode = IfxCpu_CoreMode_unknown;

    /*get the DBGSR.HALT status */
    /*Check if the request is done for same cpu as the host for this call */
    if (IfxCpu_getCoreId() != index)
    {                           /*status request is for other cpu than the host */
        dbgsr = cpu->DBGSR;
    }
    else
    {                           /*status request is for same cpu as the host */
        dbgsr.U = __mfcr(CPU_DBGSR);
    }

    /*Check if the requested CPU is in DBG HALT mode */
    if (dbgsr.B.HALT == (uint32)IfxCpu_DBGST_HALT_halt)
    {                           /*CPU is in DBG HALT mode */
        cpuMode = IfxCpu_CoreMode_halt;
    }
    else
    {
        if (dbgsr.B.HALT == (uint32)IfxCpu_DBGST_HALT_run)
        {                       /*CPU is in DBG RUNNING mode now check PMCSR status */
            Ifx_SCU_PMCSR *pmcsr_val;

            pmcsr_val = (Ifx_SCU_PMCSR *)&MODULE_SCU.PMCSR[index];

            if (pmcsr_val->B.PMST == (uint32)IfxCpu_PMCSR_PMST_normalMode)
            {                   /*Cpu is in normal run mode */
                cpuMode = IfxCpu_CoreMode_run;
            }
            else
            {                   /*Cpu is not in run mode */
                if (pmcsr_val->B.PMST == (uint32)IfxCpu_PMCSR_PMST_idleMode)
                {               /*Cpu is in idle mode */
                    cpuMode = IfxCpu_CoreMode_idle;
                }
            }
        }
        else
        {
            cpuMode = IfxCpu_CoreMode_unknown;
        }
    }

    return cpuMode;
}


IfxCpu_ResourceCpu IfxCpu_getIndex(Ifx_CPU *cpu)
{
    IfxCpu_ResourceCpu result;
    uint32             index;
    result = IfxCpu_ResourceCpu_none;

    for (index = 0; index < IFXCPU_COUNT; index++)
    {
        if (IfxCpu_cfg_indexMap[index].module == cpu)
        {
            result = (IfxCpu_ResourceCpu)IfxCpu_cfg_indexMap[index].index;
            break;
        }
    }

    return result;
}


boolean IfxCpu_setCoreMode(Ifx_CPU *cpu, IfxCpu_CoreMode mode)
{
    // this switch is only temporary required
    // once the IfxCan driver is generated via lldgen, we will vary the code without #ifdef
#ifdef IFX_TC27x
/* FIXME Copied from old TC27xA code, check that this is up to date code */
    IfxCpu_CoreMode     cpuMode;
    boolean             RetVal;
    IfxScu_PMCSR_REQSLP modeSet;

    RetVal  = TRUE;

    modeSet = IfxScu_PMCSR_REQSLP_Idle;

    /* Check the mode the CPU is in */
    cpuMode = IfxCpu_getCoreMode(cpu);

    /* if requested mode is same as current mode nothing to do */
    if (cpuMode != mode)
    {
        /* transition from halt to Run */
        if (IfxCpu_CoreMode_halt == cpuMode)
        {
            if (IfxCpu_CoreMode_run == mode)
            {
                Ifx_CPU_DBGSR dbgsr;

                if (IfxCpu_getCoreId() != IfxCpu_getIndex(cpu))
                {
                    cpu->DBGSR.B.HALT = 0x2;
                }
                else
                {
                    dbgsr.U      = __mfcr(CPU_DBGSR);
                    dbgsr.B.HALT = 0x2;
                    __mtcr(CPU_DBGSR, dbgsr.U);
                }
            }
            else                /* cannot go to any other mode e.g. IfxCpu_CoreMode_idle */
            {
                RetVal = FALSE;
            }
        }
        /* From Run to Idle or vice versa */
        else
        {
            if (IfxCpu_CoreMode_run == cpuMode)
            {
                if (IfxCpu_CoreMode_idle == mode)
                {
                    modeSet = IfxScu_PMCSR_REQSLP_Idle;
                }
                else
                {
                    RetVal = FALSE;
                }
            }
            /* idle to Run */
            else if (IfxCpu_CoreMode_idle == cpuMode)
            {
                if (IfxCpu_CoreMode_run == mode)
                {
                    modeSet = IfxScu_PMCSR_REQSLP_Run;
                }
                else
                {
                    RetVal = FALSE;
                }
            }
            else
            {
                RetVal = FALSE;
            }

            if (TRUE == RetVal)
            {
                /* To take care of the Work Around in A step
                 * In A Step the PMCSR is Cpu Endinit protected
                 * in B step it is by safety endinit*/
                uint16          password;
                uint32          wdtCon0_Val;
                Ifx_SCU_WDTCPU *watchdog;
                watchdog = &MODULE_SCU.WDTCPU[IfxCpu_getCoreId()];    /* FIXME access to the watchdog of an other CPU, this might not work! */
                password = IfxScuWdt_getCpuWatchdogPassword();
                IfxScuWdt_clearCpuEndinit(password);
                /*  password access   */
                watchdog->CON0.U                                        = (password << 2U) | 0x1U;
                /* modify access, E=0 */
                watchdog->CON0.U                                        = (password << 2U) | 0x2U;
                /* password access in advance */
                watchdog->CON0.U                                        = (password << 2U) | 0x1U;
                /* prepare write value */
                wdtCon0_Val                                             = ((0x0000U) << 16U) | (password << 2U) | (0x3U);
                MODULE_SCU.PMCSR[(uint32)IfxCpu_getIndex(cpu)].B.REQSLP = modeSet;
                /* modify access, E=1, reload WDT */
                watchdog->CON0.U                                        = wdtCon0_Val;
                IfxScuWdt_setCpuEndinit(password);
            }
        }
    }

    return RetVal;
#else
    uint8              reqslp;
    boolean            retValue;
    IfxCpu_ResourceCpu index = IfxCpu_getIndex(cpu);

    /*Modes such as HALT, SLEEP and STBY are not handled at CPU level */
    retValue = ((mode == IfxCpu_CoreMode_halt) || (mode == IfxCpu_CoreMode_sleep)
                || (mode == IfxCpu_CoreMode_stby)) ? FALSE : TRUE;

    reqslp = (mode == IfxCpu_CoreMode_idle) ? IfxScu_PMCSR_REQSLP_Idle : IfxScu_PMCSR_REQSLP_Run;

    if (retValue == TRUE)
    {
        /*Check if the same core is requesting to change the core run mode */
        if (IfxCpu_getCoreId() != index)
        {                       /*Request is for the other core */
            /*To access PMCSR of other CPUs handle the safety EndInit protection */
            uint16 safetyWdtPw = IfxScuWdt_getSafetyWatchdogPassword();
            IfxScuWdt_clearSafetyEndinit(safetyWdtPw);
            MODULE_SCU.PMCSR[(uint32)IfxCpu_getIndex(cpu)].B.REQSLP = reqslp;
            IfxScuWdt_setSafetyEndinit(safetyWdtPw);

            cpu->DBGSR.B.HALT = 2; /*reset the HALT bit, if it is already done it is no harm in writing again */
        }
        else
        {                          /*Request is for self, this request normally only for halt, otherwise the core is already running anyway! */
            /*To access PMCSR of self handle the cpu EndInit protection */
            uint16 cpuWdtPw = IfxScuWdt_getCpuWatchdogPassword();
            IfxScuWdt_clearCpuEndinit(cpuWdtPw);
            MODULE_SCU.PMCSR[(uint32)index].B.REQSLP = reqslp;
            IfxScuWdt_setCpuEndinit(cpuWdtPw);
        }
    }

    return retValue;
#endif
}


boolean IfxCpu_setProgramCounter(Ifx_CPU *cpu, uint32 programCounter)
{
    boolean retVal = TRUE;

    if (cpu == IfxCpu_getAddress(IfxCpu_getCoreId()))
    {
        retVal = FALSE;
    }
    else
    {

        cpu->PC.B.PC = programCounter >> 1;
    }

    return retVal;
}


boolean IfxCpu_startCore(Ifx_CPU *cpu, uint32 programCounter)
{
    boolean retVal = TRUE;

    /* Set the PC for Core 1 */
    retVal &= IfxCpu_setProgramCounter(cpu, programCounter);
    /* Get the mode for Core 1 and set it to RUNNING */

    /* Core not running already */
    if (IfxCpu_getCoreMode(cpu) == IfxCpu_CoreMode_halt)
    {
        retVal &= IfxCpu_setCoreMode(cpu, IfxCpu_CoreMode_run);
    }

    return retVal;
}


boolean IfxCpu_setSpinLock(IfxCpu_spinLock *lock, uint32 timeoutCount)
{
    boolean         retVal;
    volatile uint32 spinLockVal;

    retVal = FALSE;

    do
    {
        spinLockVal = 1UL;
        spinLockVal =
            (uint32)__cmpAndSwap(((unsigned int *)lock), spinLockVal, 0);

        /* Check if the SpinLock WAS set before the attempt to acquire spinlock */
        if (spinLockVal == 0)
        {
            retVal = TRUE;
        }
        else
        {
            timeoutCount--;
        }
    } while ((retVal == FALSE) && (timeoutCount > 0));

    return retVal;
}


void IfxCpu_resetSpinLock(IfxCpu_spinLock *lock)
{
    /*Reset the SpinLock*/
    *lock = 0;
}


boolean IfxCpu_acquireMutex(IfxCpu_mutexLock *lock)
{
    boolean         retVal;
    volatile uint32 spinLockVal;

    retVal      = FALSE;

    spinLockVal = 1UL;
    spinLockVal =
        (uint32)__cmpAndSwap(((unsigned int *)lock), spinLockVal, 0);

    /* Check if the SpinLock WAS set before the attempt to acquire spinlock */
    if (spinLockVal == 0)
    {
        retVal = TRUE;
    }

    return retVal;
}


void IfxCpu_releaseMutex(IfxCpu_mutexLock *lock)
{
    /*Reset the SpinLock*/
    *lock = 0;
}
