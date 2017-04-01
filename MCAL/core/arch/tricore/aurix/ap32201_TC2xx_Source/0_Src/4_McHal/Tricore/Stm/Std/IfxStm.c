/**
 * \file IfxStm.c
 * \brief STM  basic functionality
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

#include "IfxStm.h"

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

void IfxStm_clearCompareFlag(Ifx_STM *stm, IfxStm_Comparator comparator)
{
    if (comparator == IfxStm_Comparator_0)
    {
        stm->ISCR.B.CMP0IRR = 1U;
    }
    else if (comparator == IfxStm_Comparator_1)
    {
        stm->ISCR.B.CMP1IRR = 1U;
    }
}


void IfxStm_enableOcdsSuspend(Ifx_STM *stm)
{
    Ifx_STM_OCS ocs = stm->OCS;

    ocs.B.SUS_P      = 1;
    ocs.B.SUS        = 2;
    stm->OCS         = ocs;
    stm->OCS.B.SUS_P = 0;
}


IfxStm_ResourceStm IfxStm_getIndex(Ifx_STM *stm)
{
    uint32             index;
    IfxStm_ResourceStm result;

    result = IfxStm_ResourceStm_none;

    for (index = 0; index < IFXSTM_COUNT; index++)
    {
        if (IfxStm_cfg_indexMap[index].module == stm)
        {
            result = IfxStm_cfg_indexMap[index].index;
            break;
        }
    }

    return result;
}


boolean IfxStm_initCompare(Ifx_STM *stm, IfxStm_CompareConfig *config)
{
    sint32        index;
    boolean       result;
    Ifx_STM_CMCON comcon = stm->CMCON;
    Ifx_STM_ICR   icr    = stm->ICR;

    index = IfxStm_getIndex(stm);

    if ((config->triggerInterruptEnabled > 0) && (index >= 0))
    {                           /* configure interrupt */
        volatile Ifx_SRC_SRCR *srcr;

        if (config->comparatorInterrupt == IfxStm_ComparatorInterrupt_ir0)
        {
            srcr = &(MODULE_SRC.STM.STM[index].SR0);
        }
        else
        {
            srcr = &(MODULE_SRC.STM.STM[index].SR1);
        }

        IfxSrc_init(srcr, config->servProvider, config->triggerInterruptEnabled);
        IfxSrc_enable(srcr);
    }

    /*Configure the comparator ticks */
    stm->CMP[config->comparator].U = IfxStm_getOffsetTimer(stm, (uint8)config->compareOffset) + config->ticks;

    if (config->comparator == 0)
    {
        comcon.B.MSIZE0  = config->compareSize;
        comcon.B.MSTART0 = config->compareOffset;
        icr.B.CMP0OS     = config->comparatorInterrupt;
        icr.B.CMP0EN     = config->triggerInterruptEnabled ? 1 : 0;
        result           = TRUE;
    }
    else if (config->comparator == 1)
    {
        comcon.B.MSIZE1  = config->compareSize;
        comcon.B.MSTART1 = config->compareOffset;
        icr.B.CMP1OS     = config->comparatorInterrupt;
        icr.B.CMP1EN     = config->triggerInterruptEnabled ? 1 : 0;
        result           = TRUE;
    }
    else
    {
        /*Invalid value */
        result = FALSE;
    }

    stm->ICR   = icr;
    stm->CMCON = comcon;

    return result;
}


void IfxStm_initCompareConfig(IfxStm_CompareConfig *config)
{
    config->comparator              = IfxStm_Comparator_0;
    config->compareOffset           = IfxStm_ComparatorOffset_0;
    config->compareSize             = IfxStm_ComparatorSize_32Bits;
    config->triggerInterruptEnabled = FALSE;
    config->comparatorInterrupt     = IfxStm_ComparatorInterrupt_ir0; /*User must select the interrupt output */
    config->ticks                   = 0xFFFFFFFF;
    /* TODO add interrupt configuration */
}
