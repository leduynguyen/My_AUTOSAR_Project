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

/** @tagSettings DEFAULT_ARCHITECTURE=JACINTO5 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/* ----------------------------[includes]------------------------------------*/

#include "Adc.h"
#include "Adc_Internal2.h"
#include "Adc_jacinto.h"

#if defined(USE_DET)
#include "Det.h"
#endif
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
#include "isr.h"
#endif
#include "irq_types.h"

/* ----------------------------[private define]------------------------------*/
#if ( ADC_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE_NO_RV(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(ADC_MODULE_ID,0,_api,_err); \
          return; \
        }

#define DET_REPORTERROR(_x,_y,_z,_q) (void)Det_ReportError(_x, _y, _z, _q)
#else
#define VALIDATE_NO_RV(_exp,_api,_err )
#define DET_REPORTERROR(_x,_y,_z,_q)
#endif

#define MASK_CTRL_ENABLE                (uint32)0x1uL
#define MASK_CTRL_ADCCHNLID             (uint32)0x2uL
#define MASK_CTRL_SC_WRITE_PROTECT_OFF	(uint32)0x04uL
#define MASK_ADCSTAT_FSM_BUSY           (uint32)0x20uL
#define MASK_STEPCONFIG_MODE_ONE_SHOT   (uint32)0uL
#define MASK_STEPCONFIG_MODE_CONT       (uint32)1uL
#define MASK_IRQ_EOS  (uint32)0x2uL

#define MASK_STEPID                     0x0FuL
#define MASK_12BIT_ADC                  0xFFFuL

#define BIT_SHIFT_STEPCONFIG_DIFF_CNTRL 25uL
#define BIT_SHIFT_STEPCONFIG_SEL_RFM    23uL
#define BIT_SHIFT_STEPCONFIG_SEL_INP    19uL
#define BIT_SHIFT_STEPCONFIG_SEL_INM    15uL
#define BIT_SHIFT_STEPCONFIG_SEL_RFP    12uL

#define BIT_SHIFT_FIFO_ADCCHNLID        16uL

#define TS_CHARGE_OFFSET                1uL

#define MAX_FIFO_ENTRIES                64uL

#define MAX_WAIT_CYCLES (uint32)10000UL
/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
static Std_ReturnType waitWhileBusy(volatile const uint32 *regBaseAddr, uint32 mask, boolean retCondition);
static void GroupConversionComplete(Adc_ArcControllerIdType ADCn);
ISR(TSC_ADCGrpConversionComplete_Isr);
/* ----------------------------[private variables]---------------------------*/

/*lint -esym(9003, hwPtr) Unnecessary .....  */
TSC_ADC_RegType * const hwPtr = (TSC_ADC_RegType*)0x48450000; /*lint !e923 Must assign address to hw register*/

/* ----------------------------[private functions]---------------------------*/

/**
 * Interrupt service routine.
 * @param TSC_ADCGrpConversionComplete_Isr
 */
ISR(TSC_ADCGrpConversionComplete_Isr){
    GroupConversionComplete(TSC_ADC);
}

/**
 * Routine called by the interrupt to handle the ongoing conversion.
 * @param ADCn
 */
static void GroupConversionComplete(Adc_ArcControllerIdType ADCn){
    const Adc_GroupDefType *groupPtr = NULL;
    Adc_ValueGroupType adcData;
    Adc_ChannelType i;
    uint32 stepIdNbr;
    uint32 fifoData;
    uint32 group;

    /* Disable interrupts */
    /* @req SWS_Adc_00078 */
    hwPtr->IRQENABLE_CLR = MASK_IRQ_EOS;
    hwPtr->IRQSTATUS     = MASK_IRQ_EOS;

    // Check which group is busy, only one is allowed to be busy at a time in a hw unit
    for (group = 0; group <  GET_CONFIG_PTR(ADCn)->nbrOfGroups; group++){
        if( GET_CONFIG_PTR(ADCn)->groupConfigPtr[group].status->groupStatus != ADC_IDLE){
            groupPtr = &( GET_CONFIG_PTR(ADCn)->groupConfigPtr[group]);
            break;
        }
    }

    if( groupPtr != NULL ){
        for(Adc_ChannelType index=0; index < groupPtr->numberOfChannels; index++){
            /**
             * The Channels will be sampled from STEPCONFIG 1->15. But the configuration does not
             * have to be defined in ascending order.
             */

            fifoData = hwPtr->FIFO0DATA;

            stepIdNbr = ((fifoData >> BIT_SHIFT_FIFO_ADCCHNLID) & MASK_STEPID);

            /* Get matching buffer index */
            for (i = 0; i < groupPtr->numberOfChannels; i++) {
                if (stepIdNbr == groupPtr->channelMappingList[i]) {
                    break;
                }
            }

            /* To get the layout of the buffer right, first all samples from one channel,
                         then all samples for the next etc.*/
            adcData = (Adc_ValueGroupType)(fifoData & MASK_12BIT_ADC);
            groupPtr->status->currResultBufPtr[i*(uint32)groupPtr->streamNumSamples] = adcData;
        }
    }

    Adc_Internal_Isr(groupPtr);
}


/**
 * This function is used instead of "while". It returns when the condition is cleared or
 * when n reach MAX_WAIT_CYCLES.
 * @param regBaseAddr
 * @param mask
 * @param retCondition
 * @return
 */
static Std_ReturnType waitWhileBusy(volatile const uint32 *regBaseAddr, uint32 mask, boolean retCondition) {
    Std_ReturnType retval = E_NOT_OK;
    boolean condition;
    uint32 n;

    for (n = 0; n < MAX_WAIT_CYCLES ; n++) {
        condition = ((*regBaseAddr & mask) == mask) ? TRUE : FALSE;

        //Shall remain in the loop while the condition is false.
        if(retCondition == condition) {
            retval = E_OK;
            break;
        }
    }
    return retval;
}

/* ----------------------------[public functions]----------------------------*/

/**
 * Used to initialize hardware
 * @param ConfigPtr
 */
void Adc_Hw_Init(const Adc_ConfigType* ConfigPtr){
    uint32 nbrOfChannels = ConfigPtr->hwConfigPtr[0].numberOfChannels;
    uint32 pinMuxValue;
    uint32 pinDiffMode;
    uint32 pinSelRfp;
    uint32 pinSelRfm;
    uint32 i;

    VALIDATE_NO_RV( (NULL != ConfigPtr), ADC_INIT_ID, ADC_E_PARAM_POINTER);

    if ((hwPtr->CTRL & MASK_CTRL_ENABLE) == MASK_CTRL_ENABLE) {
        hwPtr->CTRL &= ~MASK_CTRL_ENABLE;
        (void)waitWhileBusy(&hwPtr->CTRL, MASK_CTRL_ENABLE, FALSE);
    }

    hwPtr->CTRL = MASK_CTRL_SC_WRITE_PROTECT_OFF;

#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
    ISR_INSTALL_ISR2("TSC_ADC_0", TSC_ADCGrpConversionComplete_Isr, TSC_ADC_MUX_IRQ, ADC_ISR_PRIORITY, 0);
#endif

    hwPtr->ADC_CLKDIV = ConfigPtr->hwConfigPtr[0].adcPrescale - 1uL;

    for (i = 0; i < nbrOfChannels; i++) {
        pinMuxValue = (uint32)ConfigPtr->hwConfigPtr[0].channelList[i].Adc_Channel;
        pinDiffMode = ConfigPtr->hwConfigPtr[0].channelList[i].Adc_ChnDiff;
        pinSelRfp   = ConfigPtr->hwConfigPtr[0].channelList[i].Adc_ChnSelrfp;
        pinSelRfm   = ConfigPtr->hwConfigPtr[0].channelList[i].Adc_ChnSelrfm;

        hwPtr->STEPCONF[i].STEPCONFIG = (pinMuxValue << BIT_SHIFT_STEPCONFIG_SEL_INP) | \
                                                    (pinMuxValue << BIT_SHIFT_STEPCONFIG_SEL_INM) |
                                                    MASK_STEPCONFIG_MODE_CONT | /* Always set to continuous mode */
                                                    (pinSelRfp << BIT_SHIFT_STEPCONFIG_SEL_RFP) |
                                                    (pinSelRfm << BIT_SHIFT_STEPCONFIG_SEL_RFM) |
                                                    (pinDiffMode << BIT_SHIFT_STEPCONFIG_DIFF_CNTRL);
    }

    /* Bit 2 = 0 -> The step config write protection is set to active (active low). */
    hwPtr->CTRL = MASK_CTRL_ENABLE | MASK_CTRL_ADCCHNLID;
}


#if (ADC_DEINIT_API == STD_ON)
/**
 * Used to de-initialize the ADC hardware.
 */
void Adc_Hw_DeInit(void){
    /* @req SWS_Adc_00110 */
    uint32 i;

    /* Disable all interrupts */
    hwPtr->IRQENABLE_CLR = 0x7FFuL;

    /* Abort any ongoing conversion */
    hwPtr->CTRL &= ~MASK_CTRL_ENABLE;

    /* Wait until the internal state is idle */
    (void)waitWhileBusy(&hwPtr->CTRL, MASK_CTRL_ENABLE, FALSE);

    /* Clear any status flag */
    hwPtr->IRQSTATUS = 0x7FFuL;

    /* Clear all StepConfig and StepDelay registers */
    hwPtr->CTRL = MASK_CTRL_SC_WRITE_PROTECT_OFF;
    for (i = 0; i < ADC_TSC_MAX_NBR_STEP_CONFIGS; i++) {
        hwPtr->STEPCONF[i].STEPCONFIG = 0uL;
        hwPtr->STEPCONF[i].STEPDELAY = 0uL;
    }

    hwPtr->ADC_CLKDIV = 0;

    /* Default value */
    hwPtr->CTRL = 0uL;
}
#endif

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/**
 * Used to start the group conversion.
 * @param group
 */
void Adc_Hw_StartGroupConversion (Adc_GroupType group){
    const Adc_GroupDefType * groupPtr = NULL;
    uint32 chnStepConfIdx;
    uint32 stepEnable = 0;
    Adc_ChannelType i;

    for (uint32 configId = 0; configId < ADC_ARC_CTRL_CONFIG_CNT; configId++) {
        if( GET_CONFIG_PTR(configId)->hwConfigPtr->hwUnitId == (group / ADC_NOF_GROUP_PER_CONTROLLER) ){
            if( GET_CONFIG_PTR(configId)->nbrOfGroups > (group % ADC_NOF_GROUP_PER_CONTROLLER) ){
                groupPtr =  &(GET_CONFIG_PTR(configId)->groupConfigPtr[group % ADC_NOF_GROUP_PER_CONTROLLER]);
            }
        }
    }

    VALIDATE_NO_RV( NULL != groupPtr , ADC_STARTGROUPCONVERSION_ID, ADC_E_PARAM_POINTER);

    /* Wait until the internal state is idle */
    (void)waitWhileBusy(&hwPtr->ADCSTAT, MASK_ADCSTAT_FSM_BUSY, FALSE);

    /* Should there be any data in the FIFO empty it. May be the case if a conversion was aborted */
    for (i = 0; ((hwPtr->FIFO0COUNT > 0) && (i < MAX_FIFO_ENTRIES)); i++) {
        (void)hwPtr->FIFO0DATA;
    }

    /* Parse out the steps/channels to enable */
    for (i = 0; i < groupPtr->numberOfChannels; i++) {
        chnStepConfIdx = groupPtr->channelMappingList[i];

        stepEnable |= 1uL << (chnStepConfIdx + TS_CHARGE_OFFSET);
    }

    /* Should the EOS flag be set, clear it */
    hwPtr->IRQSTATUS = MASK_IRQ_EOS;
    /* Enable EOS interrupt flag */
    hwPtr->IRQENABLE_SET = MASK_IRQ_EOS;

    /* Start group conversion */
    /* @req SWS_Adc_00061 */
    hwPtr->STEPENABLE = stepEnable;
}

/**
 * Used to stop the group conversion
 * @param group
 */
void Adc_Hw_StopGroupConversion (Adc_GroupType group){
    /*@req SWS_Adc_00385 */
    /*@req SWS_Adc_00386 */
    /* Disable the EOS interrupt */
    hwPtr->IRQENABLE_CLR = MASK_IRQ_EOS;
    /* Disable all steps */
    hwPtr->STEPENABLE = 0;

    (void)group;
}
#endif


/**
 * Function used the the interrupt routine to enable or disable the interrupt.
 * @param groupPtr
 * @param enableInt
 */
void Adc_Hw_IsrPost(const Adc_GroupDefType * groupPtr, boolean enableInt) {
    if (enableInt) {
        if (ADC_TRIGG_SRC_HW == groupPtr->triggerSrc) {
            //Improvement: HW Trigger support.
        } else {
            hwPtr->IRQENABLE_SET = MASK_IRQ_EOS;
        }
    } else {
        hwPtr->IRQENABLE_CLR = MASK_IRQ_EOS;
        hwPtr->STEPENABLE = 0;
    }
}
