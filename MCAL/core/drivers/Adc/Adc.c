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

/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */
/** @tagSettings DEFAULT_ARCHITECTURE=TMS570|RH850F1H|JACINTO5|JACINTO6 */

/* ----------------------------[information]----------------------------------*/

/* ----------------------------[includes]------------------------------------*/

#include "Adc.h"
#include "Std_Types.h"
#include "Adc_Internal2.h"

#if defined(USE_DET)
#include "Det.h"
#endif
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
#include "isr.h"
#endif
#include "Os.h"
#include <string.h>

/* @req SWS_Adc_00056  */
/* @req SWS_Adc_00078  */
/* @req SWS_Adc_00090  */
/* @req SWS_Adc_00091  */
/* @req SWS_Adc_00092  */
/* @req SWS_Adc_00098  */
/* @req SWS_Adc_00099  */
/* @req SWS_Adc_100  */
/* @req SWS_Adc_101  */
/* @req SWS_Adc_110  */
/* @req SWS_Adc_111  */
/* @req SWS_Adc_138  */
/* @req SWS_Adc_140  */
/* @req SWS_Adc_155  */
/* @req SWS_Adc_156  */
/* @req SWS_Adc_214  */
/* @req SWS_Adc_224  */
/* @req SWS_Adc_226  */
/* @req SWS_Adc_228  */
/* @req SWS_Adc_246  */
/* @req SWS_Adc_247  */
/* @req SWS_Adc_248  */
/* @req SWS_Adc_249  */
/* @req SWS_Adc_250  */
/* @req SWS_Adc_259  */
/* @req SWS_Adc_260  */
/* @req SWS_Adc_267  */
/* @req SWS_Adc_277  */
/* @req SWS_Adc_280  */
/* @req SWS_Adc_307  */
/* @req SWS_Adc_318  */
/* @req SWS_Adc_319  */
/* @req SWS_Adc_320  */
/* @req SWS_Adc_326  */
/* @req SWS_Adc_327  */
/* @req SWS_Adc_329  */
/* @req SWS_Adc_330  */
/* @req SWS_Adc_359  */
/* @req SWS_Adc_360  */
/* @req SWS_Adc_363  */
/* @req SWS_Adc_364  */
/* @req SWS_Adc_365  */
/* @req SWS_Adc_366  */
/* @req SWS_Adc_367  */
/* @req SWS_Adc_368  */
/* @req SWS_Adc_369  */
/* @req SWS_Adc_372  */
/* @req SWS_Adc_373  */
/* @req SWS_Adc_374  */
/* @req SWS_Adc_375  */
/* @req SWS_Adc_376  */
/* @req SWS_Adc_380  */
/* @req SWS_Adc_381  */
/* @req SWS_Adc_382  */
/* @req SWS_Adc_383  */
/* @req SWS_Adc_385  */
/* @req SWS_Adc_386  */
/* @req SWS_Adc_387  */
/* @req SWS_Adc_413  */
/* @req SWS_Adc_415  */
/* @req SWS_Adc_419  */
/* @req SWS_Adc_420  */
/* @req SWS_Adc_431  */
/* @req SWS_Adc_433  */
/* @req SWS_Adc_458  */
/* @req SWS_Adc_503  */
/* @req SWS_Adc_505  */
/* @req SWS_Adc_506  */
/* @req SWS_Adc_507  */
/* @req SWS_Adc_508  */
/* @req SWS_Adc_509  */
/* @req SWS_Adc_510  */
/* @req SWS_Adc_513  */
/* @req SWS_Adc_514  */
/* @req SWS_Adc_515  */
/* @req SWS_Adc_517  */
/* @req SWS_Adc_518  */
/* @req SWS_Adc_519  */
/* @req SWS_Adc_528  */

/*lint -save -e9003 Misra 2012 8.9 Blockscope variables definitions neglected.
 * Static variable declaration in Function body violates the AUTOSAR memory mapping concept.*/

/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/
#if ( ADC_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE_RV(_exp,_api,_err,_rv) \
        if( !(_exp) ) { \
          (void)Det_ReportError(ADC_MODULE_ID,0,_api,_err); \
          return _rv; \
        }

#define VALIDATE(_exp,_api,_err ) \
        VALIDATE_RV(_exp,_api,_err, (E_NOT_OK))

#define VALIDATE_NO_RV(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(ADC_MODULE_ID,0,_api,_err); \
          return; \
        }

#define DET_REPORTERROR(_x,_y,_z,_q) (void)Det_ReportError(_x, _y, _z, _q)
#else
#define VALIDATE_RV(_exp,_api,_err,_rv)
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_NO_RV(_exp,_api,_err )
#define DET_REPORTERROR(_x,_y,_z,_q)
#endif

/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

Adc_GlobalType Adc_Global;

static Adc_StateType adcState = ADC_STATE_UNINIT;

/* ----------------------------[private functions]---------------------------*/

static const Adc_GroupDefType * getGroupPtr(Adc_GroupType group) {
    for (uint32 configId = 0; configId < ADC_ARC_CTRL_CONFIG_CNT; configId++) {
        if( GET_CONFIG_PTR(configId)->hwConfigPtr->hwUnitId == (group / ADC_NOF_GROUP_PER_CONTROLLER) ){
            if( GET_CONFIG_PTR(configId)->nbrOfGroups > (group % ADC_NOF_GROUP_PER_CONTROLLER) ){
                return &(GET_CONFIG_PTR(configId)->groupConfigPtr[group % ADC_NOF_GROUP_PER_CONTROLLER]);
            }
        }
    }
    return (const Adc_GroupDefType *)NULL;
}

static boolean validGroup(Adc_GroupType group) {
    return getGroupPtr(group) != NULL;
}
static Adc_StatusType getState(Adc_GroupType group) {
    const Adc_GroupDefType * tmpPtr = getGroupPtr(group);
    return tmpPtr->status->groupStatus;
}

/**
 * Implements group status change to ADC_BUSY for Adc_GetStreamLastPointer
 * and Adc_ReadGroup when group status is ADC_STREAM_COMPLETED.
 *
 * @param groupPtr	Pointer to the group
 */
static void forStreamCompletedChangeToBusyIf(const Adc_GroupDefType *groupPtr) {
    /* @req SWS_Adc_00326 */
    /* @req SWS_Adc_00329 */
    if (ADC_STREAM_COMPLETED == groupPtr->status->groupStatus) {
        if (ADC_TRIGG_SRC_SW == groupPtr->triggerSrc) {
            if (((ADC_ACCESS_MODE_SINGLE == groupPtr->accessMode)
                    && (ADC_CONV_MODE_CONTINUOUS == groupPtr->conversionMode))
                    || ((ADC_ACCESS_MODE_STREAMING == groupPtr->accessMode)
                            && (ADC_STREAM_BUFFER_CIRCULAR
                                    == groupPtr->streamBufferMode))) {
                groupPtr->status->groupStatus = ADC_BUSY;
            }
        } else if (ADC_TRIGG_SRC_HW == groupPtr->triggerSrc) {
            if ((ADC_ACCESS_MODE_SINGLE == groupPtr->accessMode)
                    || ((ADC_ACCESS_MODE_STREAMING == groupPtr->accessMode)
                            && (ADC_STREAM_BUFFER_CIRCULAR
                                    == groupPtr->streamBufferMode))) {
                groupPtr->status->groupStatus = ADC_BUSY;
            }
        } else {
            /* Error*/
        }
    }
}

/**
 * Implements group status change to ADC_IDLE for Adc_GetStreamLastPointer
 * and Adc_ReadGroup when group status is ADC_STREAM_COMPLETED.
 *
 * @param groupPtr	Pointer to the group
 */
static void forStreamCompletedChangeStateToIdleIf(const Adc_GroupDefType *groupPtr) {
    /* @req SWS_Adc_00327 */
    /* @req SWS_Adc_00330 */
    if (ADC_STREAM_COMPLETED == groupPtr->status->groupStatus) {
        if (ADC_TRIGG_SRC_SW == groupPtr->triggerSrc) {
            if (((ADC_STREAM_BUFFER_LINEAR == groupPtr->streamBufferMode)
                    && (ADC_ACCESS_MODE_STREAMING == groupPtr->accessMode))
                    || ((ADC_CONV_MODE_ONESHOT == groupPtr->conversionMode))) {
                groupPtr->status->groupStatus = ADC_IDLE;
            }
        } else if (ADC_TRIGG_SRC_HW == groupPtr->triggerSrc) {
            if ((ADC_ACCESS_MODE_STREAMING == groupPtr->accessMode)
                    && (ADC_STREAM_BUFFER_LINEAR == groupPtr->streamBufferMode)) {
                groupPtr->status->groupStatus = ADC_IDLE;
            }
        } else {
            /* Error*/
        }
    }
}

/**
 * Implements group status change to ADC_BUSY for Adc_GetStreamLastPointer
 * and Adc_ReadGroup when group status is ADC_COMPLETED.
 *
 * @param groupPtr	Pointer to the group
 */
static void forADCCompletedChangeToBusyIf(const Adc_GroupDefType *groupPtr) {
    /* @req SWS_Adc_00328 */
    /* @req SWS_Adc_00331 */
    if (ADC_COMPLETED == groupPtr->status->groupStatus) {
        groupPtr->status->groupStatus = ADC_BUSY;
    }
}

/* ----------------------------[public functions]----------------------------*/

/* @req SWS_Adc_00228 */
#if (ADC_DEINIT_API == STD_ON)
void Adc_DeInit (void)
{
#if ( ADC_DEV_ERROR_DETECT == STD_ON )
    VALIDATE_NO_RV(adcState == ADC_STATE_INIT,ADC_DEINIT_ID,ADC_E_UNINIT);
#endif

    /* Loop over the controllers */
    for (uint32 configId = 0; configId < ADC_ARC_CTRL_CONFIG_CNT; configId++) {

        const Adc_ConfigType *AdcConfigPtr = GET_CONFIG_PTR(configId);

        /* Loop over the group in the controller */
        for(Adc_GroupType group = 0; group < AdcConfigPtr->nbrOfGroups; group++)
        {
            Adc_GroupStatus * statusPtr = AdcConfigPtr->groupConfigPtr[group].status;
#if ( ADC_DEV_ERROR_DETECT == STD_ON )
            /* @req SWS_Adc_00112 */
            VALIDATE_NO_RV( (ADC_IDLE == statusPtr->groupStatus ) || ( ADC_STREAM_COMPLETED == statusPtr->groupStatus ), ADC_DEINIT_ID, ADC_E_BUSY );
#endif
            /* Set group status to idle. */
            statusPtr->groupStatus = ADC_IDLE;
        }
    }

    Adc_Hw_DeInit();

    adcState = ADC_STATE_UNINIT;
}
#endif

/* @req SWS_Adc_00056  */
/* @req SWS_Adc_00246  Module implementing function, writes the register.*/
/* @req SWS_Adc_00247  PORT should init register if reg is I/O and affetcs several modules*/
/* @req SWS_Adc_00248  MCU shold init register if not I/O but affects several modules*/
/* @req SWS_Adc_00249  One time writable registers that require init directly after reset should be inited by startup code*/
/* @req SWS_Adc_00250  All other registers shall be initialized by the startup code*/
void Adc_Init(const Adc_ConfigType *ConfigPtr) {
#if ( ADC_DEV_ERROR_DETECT == STD_ON )
    /* @req SWS_Adc_00107 */
    VALIDATE_NO_RV ((ADC_STATE_UNINIT == adcState), ADC_INIT_ID, ADC_E_ALREADY_INITIALIZED);
    /* !req:SWS_Adc_00342 Variant PC*/
    /* @req SWS_Adc_00344 */
    VALIDATE_NO_RV((ConfigPtr != NULL), ADC_INIT_ID, ADC_E_PARAM_CONFIG);
#endif

    memset(&Adc_Global, 0, sizeof(Adc_Global));

    Adc_Global.config = (const Adc_ConfigType (*)[ADC_ARC_CTRL_CONFIG_CNT]) ConfigPtr; /*lint !e929 !e740 !e826 */

    for (uint32 configId = 0; configId < ADC_ARC_CTRL_CONFIG_CNT; configId++) {
        const Adc_ConfigType *AdcConfigPtr = GET_CONFIG_PTR(configId);

        for (Adc_GroupType group = 0; group < AdcConfigPtr->nbrOfGroups; group++) {
            /* @req  SWS_Adc_00307 */
            AdcConfigPtr->groupConfigPtr[group].status->groupStatus = ADC_IDLE;
            AdcConfigPtr->groupConfigPtr[group].status->currSampleCount = 0u;
            /* @req SWS_Adc_00077 */
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
            AdcConfigPtr->groupConfigPtr[group].status->notifictionEnable = 0;
#endif
        }
    }

    Adc_Hw_Init(ConfigPtr);

    adcState = ADC_STATE_INIT;
}

Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType group, Adc_ValueGroupType *bufferPtr) {
#if ( ADC_DEV_ERROR_DETECT == STD_ON )
    /* @req SWS_Adc_00423 */
    /* @req SWS_Adc_00434 */
    VALIDATE_RV(adcState == ADC_STATE_INIT,ADC_SETUPRESULTBUFFER_ID,ADC_E_UNINIT,E_NOT_OK);

    /* Group Validation */
    VALIDATE_RV(validGroup(group), ADC_SETUPRESULTBUFFER_ID, ADC_E_PARAM_GROUP, E_NOT_OK);

    /* @req SWS_Adc_00433 */
    VALIDATE_RV( getState(group) == ADC_IDLE, ADC_SETUPRESULTBUFFER_ID, ADC_E_BUSY, E_NOT_OK);

    /* @req SWS_Adc_00457 */
    VALIDATE_RV(( bufferPtr != NULL),ADC_SETUPRESULTBUFFER_ID, ADC_E_PARAM_POINTER,E_NOT_OK);
#endif

    /* @req SWS_Adc_00420 */
    getGroupPtr(group)->status->resultBufferPtr = bufferPtr;

    return E_OK ;
}

/* @req SWS_Adc_00359. */
#if (ADC_READ_GROUP_API == STD_ON)
Std_ReturnType Adc_ReadGroup (Adc_GroupType group, Adc_ValueGroupType *dataBufferPtr)
{
    uint16_t channel;
    const Adc_ValueGroupType *tmpPointer;
    const Adc_GroupDefType *groupPtr = getGroupPtr(group);

#if ( ADC_DEV_ERROR_DETECT == STD_ON )
    /* @req SWS_Adc_00296 */
    /* @req SWS_Adc_00152 */
    VALIDATE_RV(adcState == ADC_STATE_INIT,ADC_READGROUP_ID,ADC_E_UNINIT,E_NOT_OK);

    /* Group Validation */
    VALIDATE_RV(validGroup(group), ADC_READGROUP_ID, ADC_E_PARAM_GROUP, E_NOT_OK);

    /*  @req SWS_Adc_00388. */
    VALIDATE_RV( getState(group) != ADC_IDLE, ADC_READGROUP_ID, ADC_E_IDLE, E_NOT_OK);
#endif

    /* Group status change handling */
    forStreamCompletedChangeToBusyIf(groupPtr);
    forStreamCompletedChangeStateToIdleIf(groupPtr);
    forADCCompletedChangeToBusyIf(groupPtr);

    /* Copy the result to application buffer. */
#if defined(CFG_TMS570LC43X)
    if(dataBufferPtr != NULL)
    {
#endif
        for (channel = 0u; channel < (uint32)groupPtr->numberOfChannels; channel++)
        {
            if(groupPtr->status->currSampleCount > 0) {
                /* Remeber that the result buffer has the following layout: CH1_SMPL1, CH1_SMPL2, CH2_SMPL1, CH2_SMPL2 */
                /* @req SWS_Adc_00075 */
                tmpPointer = groupPtr->status->currResultBufPtr;
                if( ADC_ACCESS_MODE_STREAMING == groupPtr->accessMode )
                {
                    if( ADC_STREAM_BUFFER_LINEAR == groupPtr->streamBufferMode ) {
                        tmpPointer--;
                    }
                    else if( ADC_STREAM_BUFFER_CIRCULAR == groupPtr->streamBufferMode ) {
                        /* Handle buffer wrapping */
                        if( tmpPointer > groupPtr->status->resultBufferPtr ) {/*lint !e946 Misra 2004 17.2 17.3 2012 18.2 18.3  Relational or subtract operator applied to pointers,
                         working with pointer in a controlled way results more simplified and readable code*/
                            tmpPointer--;
                        }
                        else {
                            tmpPointer = groupPtr->status->resultBufferPtr + (groupPtr->streamNumSamples-1);/*lint !e9016 Misra 2012 18.4  pointer arithmetic other than array indexing used,
                             working with pointer in a controlled way results more simplified and readable code*/
                        }
                    }
                    else
                    {
                        ;/*do nothing*/
                    }
                }
                dataBufferPtr[channel] = tmpPointer[channel*groupPtr->streamNumSamples];
            }
        }
        return E_OK;
#if defined(CFG_TMS570LC43X)
    }
    else
    {
        return E_NOT_OK;
    }
#endif

}
#endif

Adc_StreamNumSampleType Adc_GetStreamLastPointer(Adc_GroupType group, Adc_ValueGroupType** PtrToSamplePtr) {
    Adc_StreamNumSampleType nofSample = 0;
    const Adc_GroupDefType *groupPtr = getGroupPtr(group);

#if ( ADC_DEV_ERROR_DETECT == STD_ON )

    /* @req SWS_Adc_00302 */
    if( !(adcState == ADC_STATE_INIT) ) {
        (void)Det_ReportError(ADC_MODULE_ID,0,ADC_GETSTREAMLASTPOINTER_ID,ADC_E_UNINIT);
        *PtrToSamplePtr = NULL;
        return 0;
    }

    /* @req SWS_Adc_00218 */
    VALIDATE_RV(validGroup(group), ADC_GETSTREAMLASTPOINTER_ID, ADC_E_PARAM_GROUP, 0);

    /* @req SWS_Adc_00215 */
    VALIDATE_RV( groupPtr->status->groupStatus != ADC_IDLE, ADC_GETSTREAMLASTPOINTER_ID, ADC_E_IDLE, 0);
#endif

    /* @req SWS_Adc_00216 */
    if (groupPtr->status->groupStatus == ADC_BUSY) {
        *PtrToSamplePtr = NULL;
        return 0;
    }

    /* Set resultPtr to application buffer. */
    if (groupPtr->status->currSampleCount > 0) {
        /* @req SWS_Adc_00214 */
        /* @req SWS_Adc_00387 */
        *PtrToSamplePtr = &groupPtr->status->currResultBufPtr[0];
        nofSample = groupPtr->status->currSampleCount;
    }

    /* Group status change handling */
    forStreamCompletedChangeToBusyIf(groupPtr);
    forStreamCompletedChangeStateToIdleIf(groupPtr);
    forADCCompletedChangeToBusyIf(groupPtr);

    return nofSample;
}

void Adc_Internal_Isr(const Adc_GroupDefType * groupPtr) {

    if (groupPtr != NULL) {
        if (ADC_ACCESS_MODE_SINGLE == groupPtr->accessMode) {
            groupPtr->status->currSampleCount = 1;
            /* @req SWS_Adc_00325 */
            groupPtr->status->groupStatus = ADC_STREAM_COMPLETED;

            if ((groupPtr->conversionMode == ADC_CONV_MODE_CONTINUOUS)
                    || ((groupPtr->conversionMode == ADC_CONV_MODE_ONESHOT)
                            && (ADC_TRIGG_SRC_HW == groupPtr->triggerSrc))) {
                Adc_Hw_IsrPost(groupPtr, TRUE);
            }
            else {
                Adc_Hw_IsrPost(groupPtr, FALSE);
            }
        }
        else
        {
            /*
             * ADC_ACCESS_MODE_STREAMING access mode
             */
            if (ADC_STREAM_BUFFER_LINEAR == groupPtr->streamBufferMode) {
                groupPtr->status->currSampleCount++;
                if (groupPtr->status->currSampleCount < groupPtr->streamNumSamples) {
                    groupPtr->status->currResultBufPtr++;
                    /* @req SWS_Adc_00224 */
                    groupPtr->status->groupStatus = ADC_COMPLETED;

                    Adc_Hw_IsrPost(groupPtr, TRUE);
                }
                else {
                    /* All samples completed */
                    /* @req SWS_Adc_00325 */
                    groupPtr->status->groupStatus = ADC_STREAM_COMPLETED;
                    Adc_Hw_IsrPost(groupPtr, FALSE);
                }
            }
            else if (ADC_STREAM_BUFFER_CIRCULAR == groupPtr->streamBufferMode) {

                groupPtr->status->currResultBufPtr++;

                /* Check for buffer wrapping */
                /*lint -e{9016} Misra 2012 18.4 pointer arithmetic other than array indexing used */
                /*lint -e{946}  Misra 2004 17.2 Relational or subtract operator applied to pointers
                 * working with pointer in a controlled way results more simplified and readable code*/
                if (groupPtr->status->currResultBufPtr
                        >= (groupPtr->status->resultBufferPtr + groupPtr->streamNumSamples)) {
                    groupPtr->status->currResultBufPtr = groupPtr->status->resultBufferPtr;
                }

                groupPtr->status->currSampleCount++;
                if (groupPtr->status->currSampleCount < groupPtr->streamNumSamples) {
                    /* @req SWS_Adc_00224 */
                    groupPtr->status->groupStatus = ADC_COMPLETED;
                }
                else {
                    groupPtr->status->currSampleCount = groupPtr->streamNumSamples;
                    /* All samples completed */
                    /* @req SWS_Adc_00325 */
                    groupPtr->status->groupStatus = ADC_STREAM_COMPLETED;
                }

                /* Turn on the end of stream/conversion interrupt again */
                Adc_Hw_IsrPost(groupPtr, TRUE);
            }
            else {
                ;/*do nothing*/
            }
        }
        /* Call notification if enabled. */
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
        if ( (0u != groupPtr->status->notifictionEnable) && (groupPtr->groupCallback != NULL) )
        {
            groupPtr->groupCallback();
        }
#endif
    }
}

/* @req SWS_Adc_00259 */
/* @req SWS_Adc_00260 */
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
void Adc_StartGroupConversion (Adc_GroupType group)
{

    const Adc_GroupDefType *groupPtr = getGroupPtr(group);

#if ( ADC_DEV_ERROR_DETECT == STD_ON )
    /* @req SWS_Adc_00294 */
    /* @req SWS_Adc_00125 */
    VALIDATE_NO_RV(adcState == ADC_STATE_INIT,ADC_STARTGROUPCONVERSION_ID,ADC_E_UNINIT);

    /* Group Validation */
    VALIDATE_NO_RV(validGroup(group), ADC_STARTGROUPCONVERSION_ID, ADC_E_PARAM_GROUP);

    /* @req SWS_Adc_00424 , ResultBuffer not set */
    VALIDATE_NO_RV( NULL != groupPtr->status->resultBufferPtr , ADC_STARTGROUPCONVERSION_ID, ADC_E_BUFFER_UNINIT);

    /* @req SWS_Adc_00133 , wrong trigger source */
    VALIDATE_NO_RV( ADC_TRIGG_SRC_HW != groupPtr->triggerSrc , ADC_STARTGROUPCONVERSION_ID, ADC_E_WRONG_TRIGG_SRC);

    /* Group status not OK */
    /* @req  SWS_Adc_00346 */
    /* @req  SWS_Adc_00426 */
    VALIDATE_NO_RV( (ADC_IDLE == groupPtr->status->groupStatus) || ( ADC_STREAM_COMPLETED == groupPtr->status->groupStatus),
            ADC_STARTGROUPCONVERSION_ID, ADC_E_BUSY);
#endif

    /* Set group state to BUSY. */
    groupPtr->status->groupStatus = ADC_BUSY;

    groupPtr->status->currSampleCount = 0;
    /* @req SWS_Adc_00431 */
    groupPtr->status->currResultBufPtr = groupPtr->status->resultBufferPtr;

    Adc_Hw_StartGroupConversion(group);

    /* @req SWS_Adc_00061 */
    /* @req SWS_Adc_00156 */
}

void Adc_StopGroupConversion (Adc_GroupType group)
{
    const Adc_GroupDefType *groupPtr = getGroupPtr(group);

#if ( ADC_DEV_ERROR_DETECT == STD_ON )

    /* @req SWS_Adc_00295 */
    /* @req SWS_Adc_00126 */
    VALIDATE_NO_RV(adcState == ADC_STATE_INIT,ADC_STOPGROUPCONVERSION_ID,ADC_E_UNINIT);

    /* Group Validation */
    VALIDATE_NO_RV(validGroup(group), ADC_STOPGROUPCONVERSION_ID, ADC_E_PARAM_GROUP);

    /* @req SWS_Adc_00164 , wrong trigger source */
    VALIDATE_NO_RV( ADC_TRIGG_SRC_HW != groupPtr->triggerSrc , ADC_STOPGROUPCONVERSION_ID, ADC_E_WRONG_TRIGG_SRC);

    /* @req SWS_Adc_00241 */
    VALIDATE_NO_RV( (ADC_IDLE != groupPtr->status->groupStatus), ADC_STOPGROUPCONVERSION_ID, ADC_E_IDLE);

#endif

    Adc_Hw_StopGroupConversion(group);

    /* @req SWS_Adc_00360 */
    groupPtr->status->groupStatus = ADC_IDLE;

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* Disable group notification if enabled. */
    if(1 == groupPtr->status->notifictionEnable) {
        /* @req SWS_Adc_00155 */
        Adc_DisableGroupNotification (group);
    }
#endif
}
#endif

/* !req SWS_Adc_00265*/
/* !req SWS_Adc_00266*/
#if (STD_ON == ADC_HW_TRIGGER_API)
/* !req SWS_Adc_00370 */
void Adc_EnableHardwareTrigger(Adc_GroupType Group) {
    uint32_t i = 0u;
    uint8_t busyStatus = 1u;
    uint32_t configData;
    uint32_t towClearFlags;

    const Adc_GroupDefType *groupPtr = getGroupPtr(group);

#if ( ADC_DEV_ERROR_DETECT == STD_ON )

    /* !req SWS_Adc_00128 */
    /* !req SWS_Adc_00297 */
    VALIDATE_NO_RV(adcState == ADC_STATE_INIT,ADC_ENABLEHARDWARETRIGGER_ID,ADC_E_UNINIT);

    /* Group Validation */
    VALIDATE_NO_RV(validGroup(group), ADC_ENABLEHARDWARETRIGGER_ID, ADC_E_PARAM_GROUP);

    /* !req SWS_Adc_00321 */
    VALIDATE_NO_RV( (groupPtr->triggerSrc == ADC_TRIGG_SRC_SW) && (groupPtr->status->groupStatus == ADC_IDLE ) ,
            ADC_ENABLEHARDWARETRIGGER_ID, ADC_E_BUSY);

    /* !req SWS_Adc_00349 */
    VALIDATE_NO_RV( groupPtr->status->hwTriggerEnable != 1 , ADC_ENABLEHARDWARETRIGGER_ID, ADC_E_BUSY);

    /* !req SWS_Adc_00353 */

    /* !req SWS_Adc_00425 */
    VALIDATE_NO_RV( (groupPtr->status->resultBufferPtr != NULL), ADC_ENABLEHARDWARETRIGGER_ID, ADC_E_BUFFER_UNINIT );

    /* !req SWS_Adc_00321 */
    for (uint32 configId = 0; configId < ADC_ARC_CTRL_CONFIG_CNT; configId++) {
        const Adc_ConfigType *AdcConfigPtr = GET_CONFIG_PTR(configId);

        for (Adc_GroupType group = 0; group < AdcConfigPtr->nbrOfGroups; group++) {
            const Adc_GroupDefType *gPtr = &AdcConfigPtr->groupConfigPtr[group];
            if( (ADC_TRIGG_SRC_SW == gPtr->triggerSrc) &&
                    (ADC_IDLE == gPtr->status->groupStatus)) {
                (void)Det_ReportError(ADC_MODULE_ID,0,ADC_ENABLEHARDWARETRIGGER_ID, ADC_E_BUSY );
                return;
            }
        }
    }
#endif

    Adc_Hw_EnableHardwareTrigger(Group);

    groupPtr->status->hwTriggerEnable = 1;

    /* Set group state to BUSY. */
    groupPtr->status->groupStatus = ADC_BUSY;
}

/* !req SWS_Adc_00371 */
void Adc_DisableHardwareTrigger(Adc_GroupType Group) {
    if( E_OK == Adc_CheckDisableHardwareTrigger(adcState, AdcConfigPtr, Group) )
    {
        /* !req SWS_Adc_00116 */
        /* IMPROVEMENT: */

        /* !req SWS_Adc_00361 */
        AdcConfigPtr->groupConfigPtr[Group].status->groupStatus = ADC_IDLE;

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
        /* Disable group notification if enabled. */
        if( 0u != AdcConfigPtr->groupConfigPtr[Group].status->notifictionEnable ) {
            /* !req SWS_Adc_00157 */
            Adc_DisableGroupNotification (Group);
        }
#endif
    }
}
#endif

/* @req SWS_Adc_00100 */
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
void Adc_EnableGroupNotification (Adc_GroupType group)
{
    const Adc_GroupDefType *groupPtr = getGroupPtr(group);

    /* @req SWS_Adc_00057 */
#if ( ADC_DEV_ERROR_DETECT == STD_ON )
    /* @req SWS_Adc_00299 */
    /* @req SWS_Adc_00130 */
    VALIDATE_NO_RV(adcState == ADC_STATE_INIT,ADC_ENABLEGROUPNOTIFICATION_ID,ADC_E_UNINIT);

    /* Group Validation */
    VALIDATE_NO_RV(validGroup(group), ADC_ENABLEGROUPNOTIFICATION_ID, ADC_E_PARAM_GROUP);

    /* @req SWS_Adc_00165 , ResultBuffer not set */
    VALIDATE_NO_RV( NULL != groupPtr->groupCallback , ADC_ENABLEGROUPNOTIFICATION_ID, ADC_E_NOTIF_CAPABILITY);
#endif

    groupPtr->status->notifictionEnable = 1u;
}

void Adc_DisableGroupNotification (Adc_GroupType group)
{
    /* @req SWS_Adc_00058 */

    const Adc_GroupDefType *groupPtr = getGroupPtr(group);
#if ( ADC_DEV_ERROR_DETECT == STD_ON )
    /* @req SWS_Adc_00300 */
    /* @req SWS_Adc_00131 */
    VALIDATE_NO_RV(adcState == ADC_STATE_INIT,ADC_DISABLEGROUPNOTIFICATION_ID,ADC_E_UNINIT);

    /* Group Validation */
    VALIDATE_NO_RV(validGroup(group), ADC_DISABLEGROUPNOTIFICATION_ID, ADC_E_PARAM_GROUP);

    /* @req SWS_Adc_00166 */
    VALIDATE_NO_RV( NULL != groupPtr->groupCallback , ADC_DISABLEGROUPNOTIFICATION_ID, ADC_E_NOTIF_CAPABILITY);
#endif

    groupPtr->status->notifictionEnable = 0u;
}
#endif

Adc_StatusType Adc_GetGroupStatus(Adc_GroupType group) {
    const Adc_GroupDefType *groupPtr = getGroupPtr(group);

#if ( ADC_DEV_ERROR_DETECT == STD_ON )
    /* @req SWS_Adc_00301 */
    /* @req SWS_Adc_00225 */
    VALIDATE_RV(adcState == ADC_STATE_INIT,ADC_GETGROUPSTATUS_ID,ADC_E_UNINIT, ADC_IDLE);

    /* @req SWS_Adc_00225 */
    VALIDATE_RV(validGroup(group), ADC_GETGROUPSTATUS_ID, ADC_E_PARAM_GROUP, ADC_IDLE);
#endif

    return groupPtr->status->groupStatus;
}

#if (ADC_VERSION_INFO_API == STD_ON)

void Adc_GetVersionInfo( Std_VersionInfoType* VersionInfoPtr ) {
    /* @req SWS_Adc_00458 **/
    VALIDATE_NO_RV( (VersionInfoPtr != NULL), ADC_GETVERSIONINFO_ID, ADC_E_PARAM_POINTER );

    VersionInfoPtr->vendorID = ADC_VENDOR_ID;
    VersionInfoPtr->moduleID = ADC_MODULE_ID;
    VersionInfoPtr->sw_major_version = ADC_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = ADC_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = ADC_SW_PATCH_VERSION;
}
#endif

