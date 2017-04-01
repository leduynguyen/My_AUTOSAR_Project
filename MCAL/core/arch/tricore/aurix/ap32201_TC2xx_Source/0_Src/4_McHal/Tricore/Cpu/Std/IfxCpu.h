/**
 * \file IfxCpu.h
 * \brief CPU  basic functionality
 * \ingroup IfxLld_Cpu
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
 * \defgroup IfxLld_Cpu CPU
 * \ingroup IfxLld
 * \defgroup IfxLld_Cpu_Std Standard Driver
 * \ingroup IfxLld_Cpu
 * \defgroup IfxLld_Cpu_Std_Core Cpu Core Functions
 * \ingroup IfxLld_Cpu_Std
 * \defgroup IfxLld_Cpu_Std_Std Standard Driver
 * \ingroup IfxLld_Cpu_Std
 * \defgroup IfxLld_Cpu_Std_Interrupt Interrupt Utility Functions
 * \ingroup IfxLld_Cpu_Std
 * \defgroup IfxLld_Cpu_Std_Cache Cache Management Functions
 * \ingroup IfxLld_Cpu_Std
 * \defgroup IfxLld_Cpu_Std_PerformanceCounter Performance Counter Functions
 * \ingroup IfxLld_Cpu_Std
 * \defgroup IfxLld_Cpu_Std_Synchronization Synchronization Functions
 * \ingroup IfxLld_Cpu_Std
 * \defgroup IfxLld_Cpu_Std_Enum Enumerations
 * \ingroup IfxLld_Cpu_Std
 * \defgroup IfxLld_Cpu_Std_DataStructures Data Structures
 * \ingroup IfxLld_Cpu_Std
 */

#ifndef IFXCPU_H
#define IFXCPU_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxCpu_cfg.h"
#include "IfxSrc_reg.h"
#include "IfxScu_reg.h"
#include "Scu/Std/IfxScuWdt.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/** \brief Convert local DSPR address to global DSPR address which can be accessed from the SRI bus.
 * Use this macro to convert a local DSPR address (in segment 0xd00.....) to
 * a global DSPR address (in segment 0x700....., 0x600....., 0x500..... downwards) depending on
 * the CPU number.
 * Example usage:
 *  \code
 *     dmaChConfig.sourceAddress      = IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), &sourceBuffer[i][0]);
 *     dmaChConfig.destinationAddress = IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), &destinationBuffer[i][0]);
 *  \endcode
 */
#define IFXCPU_GLB_ADDR_DSPR(cpu, address) ((((unsigned)(address) & 0x000fffff) | 0x70000000) - ((cpu) * 0x10000000))

/** \brief Convert local PSPR address to global PSPR address which can be accessed from the SRI bus.
 * Use this macro to convert a local PSPR address (in segment 0xc......) to
 * a global PSPR address (in segment 0x701....., 0x601....., 0x501..... downwards) depending on
 * the CPU number.
 *
 *   Example usage:
 *   \code
 *     dmaChConfig.sourceAddress      = IFXCPU_GLB_ADDR_PSPR(IfxCpu_getCoreId(), &sourceBufferInPsprMemory);
 *     dmaChConfig.destinationAddress = IFXCPU_GLB_ADDR_PSPR(IfxCpu_getCoreId(), &destinationBufferInPsprMemory);
 *   \endcode
 */
#define IFXCPU_GLB_ADDR_PSPR(cpu, address) ((((unsigned)(address) & 0x000fffff) | 0x70100000) - ((cpu) * 0x10000000))

/******************************************************************************/
/*------------------------------Type Definitions------------------------------*/
/******************************************************************************/

/** \brief Lock type Spin lock
 */
typedef unsigned int IfxCpu_spinLock;

/** \brief Lock type Mutex lock
 */
typedef unsigned int IfxCpu_mutexLock;

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Cpu_Std_Enum
 * \{ */
/** \brief Enumeration for the Cpu mode
 */
typedef enum
{
    IfxCpu_CoreMode_halt,
    IfxCpu_CoreMode_run,
    IfxCpu_CoreMode_idle,
    IfxCpu_CoreMode_sleep,
    IfxCpu_CoreMode_stby,
    IfxCpu_CoreMode_unknown
} IfxCpu_CoreMode;

/** \brief Performance conunter modes
 */
typedef enum
{
    IfxCpu_CounterMode_normal = 0,  /**< \brief Normal counter mode:the counter increments on their respective triggers */
    IfxCpu_CounterMode_task   = 1   /**< \brief Normal counter mode:additional gating control from the debug unit which allows the data gathered in the performance counters to be filtered by some specific criteria */
} IfxCpu_CounterMode;

/** \} */

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Cpu_Std_DataStructures
 * \{ */
typedef struct
{
    uint32  counter;      /**< \brief Counter value */
    boolean overlfow;     /**< \brief sticky overlfow */
} IfxCpu_Counter;

/** \} */

/** \addtogroup IfxLld_Cpu_Std_DataStructures
 * \{ */
/** \brief Performance counter result
 */
typedef struct
{
    IfxCpu_Counter instruction;     /**< \brief Instruction counter */
    IfxCpu_Counter clock;           /**< \brief CPU clock counter */
    IfxCpu_Counter counter1;        /**< \brief Multi counter 1 */
    IfxCpu_Counter counter2;        /**< \brief Multi counter 2 */
    IfxCpu_Counter counter3;        /**< \brief Multi counter 3 */
} IfxCpu_Perf;

/** \} */

/** \addtogroup IfxLld_Cpu_Std_Core
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief API to get resource index of the CPU of the caller
 * \return Resource index of the CPU.
 */
IFX_INLINE IfxCpu_ResourceCpu IfxCpu_getCoreId(void);

/** \brief API to initialize the context save area of the CPU where this is called.
 *
 * This API can initialize the CSA of the host CPU where this API is called. This API
 * shall not be used to initialize the CSA of another CPU
 * \param csaBegin Pointer to start of context save area
 * \param csaEnd Pointer to end of context save area
 * \return None
 */
IFX_INLINE void IfxCpu_initCSA(uint32 *csaBegin, uint32 *csaEnd);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief API to get the address for CPU HW module register memory map
 * \param cpu Resource index of the CPU
 * \return CPU module register address
 */
IFX_EXTERN Ifx_CPU *IfxCpu_getAddress(IfxCpu_ResourceCpu cpu);

/** \brief API to get current mode of CPU
 * \param cpu Pointer to the CPU HW module (register memory map)
 * \return Current mode of the CPU
 */
IFX_EXTERN IfxCpu_CoreMode IfxCpu_getCoreMode(Ifx_CPU *cpu);

/** \brief API to get current mode of CPU
 * \param cpu Pointer to the CPU HW module (register memory map)
 * \return Resource index of the CPU
 */
IFX_EXTERN IfxCpu_ResourceCpu IfxCpu_getIndex(Ifx_CPU *cpu);

/** \brief API to set mode of the CPU
 * \param cpu Pointer to the CPU HW module (register memory map)
 * \param mode CPU mode to be set by this API
 * \return Success status of the activity (setting the core mode).
 * \retval TRUE: If the activity successfully be performed.
 * \retval FALSE: If the activity can't be performed.
 */
IFX_EXTERN boolean IfxCpu_setCoreMode(Ifx_CPU *cpu, IfxCpu_CoreMode mode);

/** \brief API to set the program counter for the CPU specified.
 * \param cpu Pointer to the CPU HW module (register memory map)
 * \param programCounter Program counter value to be set
 * \return success status of the activity (setting program counter value).
 * \retval TRUE: If the activity successfully be performed.
 * \retval FALSE: If the activity can't be performed
 */
IFX_EXTERN boolean IfxCpu_setProgramCounter(Ifx_CPU *cpu, uint32 programCounter);

/** \brief API to set the program counter for the CPU specified and start the CPU
 * \param cpu Pointer to the CPU HW module (register memory map)
 * \param programCounter Program counter value to start the CPU
 * \return success status of the activity (setting program counter value).
 * \retval TRUE: If the activity successfully be performed.
 * \retval FALSE: If the activity can't be performed
 */
IFX_EXTERN boolean IfxCpu_startCore(Ifx_CPU *cpu, uint32 programCounter);

/** \} */

/** \addtogroup IfxLld_Cpu_Std_Interrupt
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief API to get the status of global interrupt enable (ICR.IE) for the CPU which calls this API
 * This API provides the status of CPU where this API is called
 * \return Status of global interrupt enable bit.
 * \retval TRUE: Global interrupts enabled.
 * \retval FALSE: Global interrupts disabled
 */
IFX_INLINE boolean IfxCpu_areInterruptsEnabled(void);

/** \brief API to disable global interrupt and return the previous status.
 *
 * This API can be used only to disable the global interrupts of caller CPU. It cannot be
 * used for this activity towards other CPUs
 * \return Previous status of global interrupt enable bit.
 * \retval TRUE: Previously, global interrupts enabled.
 * \retval FALSE: Previously, global interrupts disabled
 */
IFX_INLINE boolean IfxCpu_disableInterrupts(void);

/** \brief API to enable global interrupt.
 * This API simply enables the global interrupt.
 * \return None
 */
IFX_INLINE void IfxCpu_enableInterrupts(void);

/** \brief API to restore global interrupt with that of the passed parameter.
 *
 * This API can be used only to disable the global interrupts of caller CPU. It cannot be
 * used for this activity towards other CPUs
 * \param enabled Previous status of the global interrupt enable bit
 * \return None
 */
IFX_INLINE void IfxCpu_restoreInterrupts(boolean enabled);

/** \} */

/** \addtogroup IfxLld_Cpu_Std_Cache
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief API to enable or bypass the data cache for the CPU which calls this API.
 *
 * This API can be used only to enable or bypass the data cache of caller CPU. It cannot be
 * used for this activity towards other CPUs
 * \param enable Command to enable or bypass the data cache
 * TRUE: Enable the data cache.
 * FALSE: Bypass the data cache.
 * \return None
 */
IFX_INLINE void IfxCpu_setDataCache(boolean enable);

/** \brief API to enable or bypass the program cache for the CPU which calls this API.
 *
 * This API can be used only to enable or bypass the program cache of caller CPU. It cannot be
 * used for this activity towards other CPUs
 * \param enable Command to enable or bypass the program cache.
 * TRUE: Enable the program cache.
 * FALSE: Bypass the program cache
 * \return None
 */
IFX_INLINE void IfxCpu_setProgramCache(boolean enable);

/** \brief API to determine if an address is in a cachable or non-cachable Flash/LMU section
 * \param address Address
 * \return Status TRUE/FALSE
 */
IFX_INLINE boolean IfxCpu_isAddressCachable(void *address);

/** \} */

/** \addtogroup IfxLld_Cpu_Std_PerformanceCounter
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief API to read the clock counter for the CPU which calls this API.
 *
 * This API can be used to read clock counter of only the caller CPU. It cannot be
 * used for this activity towards other CPUs.
 * \return Counter value. 0 to 0x7FFFFFFF.
 */
IFX_INLINE uint32 IfxCpu_getClockCounter(void);

/** \brief API to read the instruction counter for the CPU which calls this API.
 *
 * This API can be used to read instruction counter of only the caller CPU. It cannot be
 * used for this activity towards other CPUs
 * \return Counter value. 0 to 0x7FFFFFFF.
 */
IFX_INLINE uint32 IfxCpu_getInstructionCounter(void);

/** \brief API to get sticky overflow bit of clock counter for the CPU, which calls this API.
 *
 * This API can be used to get sticky overflow bit of clock counter of only the caller CPU.
 * It cannot be used for this activity towards other CPUs.
 * This API also clears the sticky overflow after the read. While reading the sticky bit this API disables
 * the counter for short time. (otherwise sticky bit cannot be cleared). This API shall be used after
 * reading the counter
 * \return Status of sticky overflow bit.
 * \retval TRUE: Sticky overflow bit is set.
 * \retval FALSE: Sticky overflow bit is reset
 */
IFX_INLINE boolean IfxCpu_getClockCounterStickyOverflow(void);

/** \brief API to get sticky overflow bit of Instruction counter for the CPU, which calls this API.
 *
 * This API can be used to get sticky overflow bit of Instruction counter of only the caller CPU.
 * It cannot be used for this activity towards other CPUs.
 * This API also clears the sticky overflow after the read. While reading the sticky bit this API disables
 * the counter for short time. (otherwise sticky bit cannot be cleared). This API shall be used after
 * reading the counter
 * \return Status of sticky overflow bit.
 * \retval TRUE: Sticky overflow bit is set.
 * \retval FALSE: Sticky overflow bit is reset
 */
IFX_INLINE boolean IfxCpu_getInstructionCounterStickyOverflow(void);

/** \brief API to enable or disable performance counter for the CPU which calls this API.
 *
 * This API can be used to enable or disable performance counter of only the caller CPU. It cannot be
 * used for this activity towards other CPUs.
 * \param enable enable Command to enable or disable the performance counter.
 * TRUE: Enable the performance counter.
 * FALSE: Disable the performance counter
 * \return None
 */
IFX_INLINE void IfxCpu_setPerformanceCountersEnableBit(uint32 enable);

/** \brief API to update clock counter for the CPU which calls this API.
 *
 * This API can be used to update clock counter of only the caller CPU. It cannot be
 * used for this activity towards other CPUs.
 * \param count Counter value to be updated. 0 to 0x7FFFFFFF
 * \return None
 */
IFX_INLINE void IfxCpu_updateClockCounter(uint32 count);

/** \brief API to update Instruction counter for the CPU which calls this API.
 *
 * This API can be used to update Instruction counter of only the caller CPU. It cannot be
 * used for this activity towards other CPUs.
 * \param count Counter value to be updated. 0 to 0x7FFFFFFF
 * \return None
 */
IFX_INLINE void IfxCpu_updateInstructionCounter(uint32 count);

/** \brief Reset and start instruction, clock and multi counters
 *
 * Reset and start CCNT, ICNT, M1CNT, M2CNT, M3CNT. the overflow bits are cleared.
 * \param mode Counter mode
 * \return None
 */
IFX_INLINE void IfxCpu_resetAndStartCounters(IfxCpu_CounterMode mode);

/** \brief Stop instruction and clock counters, return their values
 *
 * Stop CCNT, ICNT, M1CNT, M2CNT, M3CNT and return their values;
 *  \Note The CCTRL is reset to 0, for more accurate measurements and has to be initialized again before strating the next performance measurement.
 * \return Performance counter result
 */
IFX_INLINE IfxCpu_Perf IfxCpu_stopCounters(void);

/** \brief API to read the performance counter for the CPU which calls this API.
 * \param address Address
 * \return counter value
 */
IFX_INLINE uint32 IfxCpu_getPerformanceCounter(uint32 address);

/** \brief API to get sticky overflow bit of performance counter for the CPU, which calls this API.
 * This is generic function to get sticky overflow bit of any performance counters
 * \param address Address
 * \return Status
 */
IFX_INLINE boolean IfxCpu_getPerformanceCounterStickyOverflow(uint32 address);

/** \brief API to update performance counter for the CPU which calls this API.
 * This is generic function to update any of the performance counters
 * \param address Address
 * \param count Count
 * \return None
 */
IFX_INLINE void IfxCpu_updatePerformanceCounter(uint32 address, uint32 count);

/** \} */

/** \addtogroup IfxLld_Cpu_Std_Synchronization
 * \{ */

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief API to lock the resource in spin mode with the given timeout.
 *
 * This API can be used to spin lock for the lock for the given timeout period.
 * \param lock lock pointer
 * \param timeoutCount loop counter value used for timeout to acquire lock
 * \return TRUE : lock acquired successfully. FALSE: Failed to acquire the lock
 *
 * \code
 *    IfxCpu_spinLock resourceLock;
 *    boolean flag = IfxCpu_setSpinLock(&resourceLock, 0xFFFF);
 *    if (flag){
 *      // critical section
 *      IfxCpu_resetSpinLock(&resourceLock);
 *    }
 * \endcode
 *
 */
IFX_EXTERN boolean IfxCpu_setSpinLock(IfxCpu_spinLock *lock, uint32 timeoutCount);

/** \brief API to unlock the resource .
 *
 * This API can be used to unlock the previously acquired lock
 * \param lock lock pointer
 * \return None
 */
IFX_EXTERN void IfxCpu_resetSpinLock(IfxCpu_spinLock *lock);

/** \brief API to acquire the mutex (binary semaphore).
 *
 * This API can be used to acquire/get the mutex.
 * \param lock lock pointer
 * \return TRUE : lock acquired successfully. FALSE: Failed to acquire the lock
 *
 * \code
 *    IfxCpu_mutexLock resourceLock;
 *    boolean flag = IfxCpu_acquireMutex(&resourceLock);
 *    if (flag){
 *      // critical section
 *      IfxCpu_releaseMutex(&resourceLock);
 *    }
 * \endcode
 *
 */
IFX_EXTERN boolean IfxCpu_acquireMutex(IfxCpu_mutexLock *lock);

/** \brief API to unlock the mutex .
 *
 * This API can be used to unlock the previously acquired mutex
 * \param lock lock pointer
 * \return None
 *
 * \code
 *    IfxCpu_mutexLock resourceLock;
 *    boolean flag = IfxCpu_acquireMutex(&resourceLock);
 *    if (flag){
 *      // critical section
 *      IfxCpu_releaseMutex(&resourceLock);
 *    }
 * \endcode
 *
 */
IFX_EXTERN void IfxCpu_releaseMutex(IfxCpu_mutexLock *lock);

/** \} */

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/

IFX_INLINE IfxCpu_ResourceCpu IfxCpu_getCoreId(void)
{
    Ifx_CPU_CORE_ID reg;
    reg.U = __mfcr(CPU_CORE_ID);
    return (IfxCpu_ResourceCpu)reg.B.CORE_ID;
}


IFX_INLINE void IfxCpu_initCSA(uint32 *csaBegin, uint32 *csaEnd)
{
    uint32  k;
    uint32  nxt_cxi_val = 0;
    uint32 *prvCsa      = 0U;
    uint32 *nxtCsa      = csaBegin;

    for (k = 0; k < (((uint32)csaEnd - (uint32)csaBegin) / 64); k++)
    {
        nxt_cxi_val = ((uint32)nxtCsa & (0XFU << 28)) >> 12 | ((uint32)nxtCsa & (0XFFFFU << 6)) >> 6;

        if (k == 0)
        {
            __mtcr(CPU_FCX, nxt_cxi_val);   /* store the new pcxi value to LCX */
        }
        else
        {
            *prvCsa = nxt_cxi_val;  /* Store null pointer in last CSA (= very first time!) */
        }

        prvCsa  = (uint32 *)nxtCsa;
        nxtCsa += 16;           /* next CSA */
    }

    *prvCsa = 0;
    __mtcr(CPU_LCX, nxt_cxi_val);   /* Last context save area is pointed in LCX to know if there is CSA depletion */
}


IFX_INLINE boolean IfxCpu_areInterruptsEnabled(void)
{
    Ifx_CPU_ICR reg;
    reg.U = __mfcr(CPU_ICR);
    return reg.B.IE != 0;
}


IFX_INLINE boolean IfxCpu_disableInterrupts(void)
{
    boolean enabled;
    enabled = IfxCpu_areInterruptsEnabled();
    __disable();
    __nop();
    return enabled;
}


IFX_INLINE void IfxCpu_enableInterrupts(void)
{
    __enable();
}


IFX_INLINE void IfxCpu_restoreInterrupts(boolean enabled)
{
    if (enabled != FALSE)
    {
        __enable();
    }
}


IFX_INLINE void IfxCpu_setDataCache(boolean enable)
{
    uint32 coreId      = IfxCpu_getCoreId();
    uint16 wdtPassword = IfxScuWdt_getCpuWatchdogPasswordInline(&MODULE_SCU.WDTCPU[coreId]);
    /*PCACHE enable steps */
    {                           /* Step 1: Set PCBYP to 0 if cache is enabled */
        IfxScuWdt_clearCpuEndinitInline(&MODULE_SCU.WDTCPU[coreId], wdtPassword);
        Ifx_CPU_DCON0 dcon0;
        dcon0.U       = 0;
        dcon0.B.DCBYP = enable ? 0 : 1; /*depending on the enable bypas bit is reset/set */
        __mtcr(CPU_DCON0, dcon0.U);
        IfxScuWdt_setCpuEndinitInline(&MODULE_SCU.WDTCPU[coreId], wdtPassword);
    }
    /* Step 2: Call Isync */
    __isync();
}


IFX_INLINE void IfxCpu_setProgramCache(boolean enable)
{
    uint32 coreId      = IfxCpu_getCoreId();
    uint16 wdtPassword = IfxScuWdt_getCpuWatchdogPasswordInline(&MODULE_SCU.WDTCPU[coreId]);
    /*PCACHE enable steps */
    {                           /* Step 1: Set PCBYP to 0 if cache is enabled */
        IfxScuWdt_clearCpuEndinitInline(&MODULE_SCU.WDTCPU[coreId], wdtPassword);
        Ifx_CPU_PCON0 pcon0;
        pcon0.U       = 0;
        pcon0.B.PCBYP = enable ? 0 : 1; /*depending on the enable bypass bit is reset/set */
        __mtcr(CPU_PCON0, pcon0.U);
        IfxScuWdt_setCpuEndinitInline(&MODULE_SCU.WDTCPU[coreId], wdtPassword);
    }
    /* Step 2: Call Isync */
    __isync();

    if (enable)
    {                           /* Step 3: Initiate invalidation of current cache contents if any */
        Ifx_CPU_PCON1 pcon1;
        pcon1.U       = 0;
        pcon1.B.PCINV = 1;
        __mtcr(CPU_PCON1, pcon1.U);
    }
}


IFX_INLINE boolean IfxCpu_isAddressCachable(void *address)
{
    uint8 segment = (uint32)address >> 24;
    return ((segment == IFXCPU_CACHABLE_FLASH_SEGMENT) || (segment == IFXCPU_CACHABLE_LMU_SEGMENT)) ? TRUE : FALSE;
}


IFX_INLINE uint32 IfxCpu_getClockCounter(void)
{
    return IfxCpu_getPerformanceCounter(CPU_CCNT);
}


IFX_INLINE uint32 IfxCpu_getInstructionCounter(void)
{
    return IfxCpu_getPerformanceCounter(CPU_ICNT);
}


IFX_INLINE boolean IfxCpu_getClockCounterStickyOverflow(void)
{
    return IfxCpu_getPerformanceCounterStickyOverflow(CPU_CCNT);
}


IFX_INLINE boolean IfxCpu_getInstructionCounterStickyOverflow(void)
{
    return IfxCpu_getPerformanceCounterStickyOverflow(CPU_ICNT);
}


IFX_INLINE void IfxCpu_setPerformanceCountersEnableBit(uint32 enable)
{
    Ifx_CPU_CCTRL cctrl;
    cctrl.U    = __mfcr(CPU_CCTRL);
    cctrl.B.CE = enable;
    __mtcr(CPU_CCTRL, cctrl.U);
}


IFX_INLINE void IfxCpu_updateClockCounter(uint32 count)
{
    IfxCpu_updatePerformanceCounter(CPU_CCNT, count);
}


IFX_INLINE void IfxCpu_updateInstructionCounter(uint32 count)
{
    IfxCpu_updatePerformanceCounter(CPU_ICNT, count);
}


IFX_INLINE void IfxCpu_resetAndStartCounters(IfxCpu_CounterMode mode)
{
    Ifx_CPU_CCTRL cctrl;
    cctrl.U    = __mfcr(CPU_CCTRL);
    /*Disable the counters */
    cctrl.B.CE = 0;
    __mtcr(CPU_CCTRL, cctrl.U);

    /* reset the counters */
    __mtcr(CPU_CCNT, 0);
    __mtcr(CPU_ICNT, 0);
    __mtcr(CPU_M1CNT, 0);
    __mtcr(CPU_M2CNT, 0);
    __mtcr(CPU_M3CNT, 0);

    /*Enable the counters, set the counter mode */
    cctrl.B.CE = 1;
    cctrl.B.CM = mode;
    __mtcr(CPU_CCTRL, cctrl.U);
}


IFX_INLINE IfxCpu_Perf IfxCpu_stopCounters(void)
{
    IfxCpu_Perf result;
    /*Disable the counters, reset the control reg */
    /* Use inline assembly to ensure constant implementation, and execution of the measurement routines */
    __stopPerfCounters();

    Ifx_CPU_CCNT ccnt;
    ccnt.U                = __mfcr(CPU_CCNT);
    result.clock.counter  = ccnt.B.CountValue;
    result.clock.overlfow = ccnt.B.SOvf;

    Ifx_CPU_ICNT icnt;
    icnt.U                      = __mfcr(CPU_ICNT);
    result.instruction.counter  = icnt.B.CountValue;
    result.instruction.overlfow = icnt.B.SOvf;

    Ifx_CPU_M1CNT m1cnt;
    m1cnt.U                  = __mfcr(CPU_M1CNT);
    result.counter1.counter  = m1cnt.B.CountValue;
    result.counter1.overlfow = m1cnt.B.SOvf;

    Ifx_CPU_M2CNT m2cnt;
    m2cnt.U                  = __mfcr(CPU_M2CNT);
    result.counter2.counter  = m2cnt.B.CountValue;
    result.counter2.overlfow = m2cnt.B.SOvf;

    Ifx_CPU_M3CNT m3cnt;
    m3cnt.U                  = __mfcr(CPU_M3CNT);
    result.counter3.counter  = m3cnt.B.CountValue;
    result.counter3.overlfow = m3cnt.B.SOvf;
    return result;
}


IFX_INLINE uint32 IfxCpu_getPerformanceCounter(uint32 address)
{
    Ifx_CPU_CCNT ccnt;
    ccnt.U = __mfcr(address);
    return ccnt.B.CountValue;
}


IFX_INLINE boolean IfxCpu_getPerformanceCounterStickyOverflow(uint32 address)
{
    Ifx_CPU_CCNT ccnt;

    ccnt.U = __mfcr(address);   /*read the counter */

    return ccnt.B.SOvf;
}


IFX_INLINE void IfxCpu_updatePerformanceCounter(uint32 address, uint32 count)
{
    Ifx_CPU_CCTRL cctrl;
    boolean       enableBit;
    /*Disable the counters */
    cctrl.U    = __mfcr(CPU_CCTRL);
    enableBit  = cctrl.B.CE;
    cctrl.B.CE = 0;
    __mtcr(CPU_CCTRL, cctrl.U);

    /*Update the counter value */
    count &= ~(1U << 31);       /*clear sticky overflow bit if set */
    __mtcr(address, count);

    /*restore the enable bit */
    cctrl.B.CE = enableBit;
    __mtcr(CPU_CCTRL, cctrl.U);
}


#endif /* IFXCPU_H */
