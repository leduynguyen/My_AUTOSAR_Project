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

/** @tagSettings DEFAULT_ARCHITECTURE=RH850F1H */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/* ----------------------------[includes]------------------------------------*/

#include "Adc.h"
#include "Adc_Internal2.h"
#include "rh850.h"

#if defined(USE_DET)
#include "Det.h"
#endif
#include "isr.h"
#include "irq_types.h"

/* ----------------------------[private define]------------------------------*/
#define SCAN_END_INTERRUPT_ENABLE 			0x000010uL
#define SCAN_GROUPS_STATUS_FLAGS_MASK 		0x00000E00uL
#define SGACT_MASK 							0x00001E00
#define ADCA0_BASE 							0xFFF20000uL
#define ADCA1_BASE 							0xFFD6D000uL


#define VALIDATE_NO_RV(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(ADC_MODULE_ID,0,_api,_err); \
          return; \
        }

#define DET_REPORTERROR(_x,_y,_z,_q) (void)Det_ReportError(_x, _y, _z, _q)

/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/
typedef union
{                                                          /* IOR              */
    uint32 UINT32;                                         /* 32-bit Access    */
    uint16 UINT16[2];                                      /* 16-bit Access    */
    uint8  UINT8[4];                                       /* 8-bit Access     */
} _type7;

typedef union
{                                                          /* IOR              */
    uint32 UINT32;                                         /* 32-bit Access    */
    uint16 UINT16[2];                                      /* 16-bit Access    */
} _type12;

typedef struct ADCA_SGx {
    _type7 SGSTCR;     									/* SGSTCR1          */
    uint8  dummy302[4];                                  /* Reserved         */
    _type7 SGCR;                                         /* SGCR1            */
    _type7 SGVCSP;                                       /* SGVCSP1          */
    _type7 SGVCEP;                                       /* SGVCEP1          */
    _type7 SGMCYCR;                                      /* SGMCYCR1         */
    _type7 SGSEFCR;                                      /* SGSEFCR1         */
    _type12 SGTSEL;                                      /* SGTSEL1          */
    uint8  dummy[32];                                   /* Reserved         */
} ADCA_SGx_t;



typedef struct
{
    /* 29, 30, 31, 32 are reserved */
    _type7 VCR[36] ;
    uint8  dummy290[100];                                  /* Reserved         */
    const _type7 PWDVCR;                                  /* PWDVCR           */
    uint8  dummy291[8];                                    /* Reserved         */

    /* */
    const _type12 DR[18];                                 /* DR00, DR02, etc    */
    uint8  dummy293[48];                                   /* Reserved         */
    const _type12 PWDTSNDR;                               /* PWDTSNDR         */
    uint8  dummy294[132];                                  /* Reserved         */

    const uint32 DIR[36];                                  /* DIR00            */
    uint8  dummy296[100];                                  /* Reserved         */
    const uint32 PWDDIR;                                   /* PWDDIR           */
    uint8  dummy297[8];                                    /* Reserved         */
    _type7 ADHALTR;                                       /* ADHALTR          */
    _type7 ADCR;                                          /* ADCR             */
    const _type12 SGSTR;                                  /* SGSTR            */
    const _type7 MPXCURR;                                 /* MPXCURR          */
    uint8  dummy298[4];                                    /* Reserved         */
    _type7 THSMPSTCR;                                     /* THSMPSTCR        */
    _type7 THCR;                                          /* THCR             */
    _type7 THAHLDSTCR;                                    /* THAHLDSTCR       */
    _type7 THBHLDSTCR;                                    /* THBHLDSTCR       */
    _type7 THACR;                                         /* THACR            */
    _type7 THBCR;                                         /* THBCR            */
    _type7 THER;                                          /* THER             */
    _type7 THGSR;                                         /* THGSR            */
    _type7 SFTCR;                                         /* SFTCR            */
    _type12 ULLMTBR0;                                     /* ULLMTBR0         */
    _type12 ULLMTBR1;                                     /* ULLMTBR1         */
    _type12 ULLMTBR2;                                     /* ULLMTBR2         */
    _type7 ECR;                                           /* ECR              */
    const _type7 ULER;                                    /* ULER             */
    const _type7 OWER;                                    /* OWER             */
    _type7 DGCTL0;                                        /* DGCTL0           */
    _type12 DGCTL1;                                       /* DGCTL1           */
    _type12 PDCTL1;                                       /* PDCTL1           */
    _type7 PDCTL2;                                        /* PDCTL2           */
    uint8  dummy299[32];                                   /* Reserved         */
    _type7 SMPCR;                                         /* SMPCR            */
    uint8  dummy300[4];                                    /* Reserved         */
    uint8  EMU;                                            /* EMU              */
    uint8  dummy301[183];                                  /* Reserved         */
    ADCA_SGx_t SGx[3];
    uint8  dummy307[8];                                   /* Reserved         */
    _type7 PWDSGCR;                                       /* PWDSGCR          */
    uint8  dummy308[12];                                   /* Reserved         */
    _type7 PWDSGSEFCR;                                    /* PWDSGSEFCR       */
} ADCA_RegType;

/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

ADCA_RegType * Adc_HwReg[] = {
        ((ADCA_RegType *) (ADCA0_BASE)),  		  /* 0 */
#if defined(RH850F1H)
        ((ADCA_RegType *) (ADCA1_BASE)),  		  /* 1 */
#endif
};


/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/
static void GroupConversionComplete(Adc_ArcControllerIdType ADCn);
ISR(ADCA0GrpConversionComplete_Isr);
ISR(ADCA1GrpConversionComplete_Isr);

void Adc_Hw_Init(const Adc_ConfigType* ConfigPtr){

    uint8 hwCh = ConfigPtr->hwConfigPtr->hwUnitId;
    /* @req SWS_Adc_00056 */
    Adc_HwReg[hwCh]->SGx[0].SGCR.UINT32 = 0UL;

    //*ADCR_Ptr = (*ADCR_Ptr & (~ADC_RESOLUTION_MASK)) | ConfigPtr->hwConfigPtr->resolution;
    Adc_HwReg[hwCh]->ADCR.UINT32 = (Adc_HwReg[hwCh]->ADCR.UINT32 & (~ADC_RESOLUTION_MASK)) | ConfigPtr->hwConfigPtr->resolution;

    /* Install all handlers */
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
    ISR_INSTALL_ISR2("Adc0GrpConvComplete", ADCA0GrpConversionComplete_Isr, IRQ_INTADCA0I0, ADC_ISR_PRIORITY, 0);
    ISR_INSTALL_ISR2("Adc1GrpConvComplete", ADCA1GrpConversionComplete_Isr, IRQ_INTADCA1I0, ADC_ISR_PRIORITY, 0);
#endif

}

#if (ADC_DEINIT_API == STD_ON)
void Adc_Hw_DeInit(void){
    /* @req SWS_Adc_00110 */
    /*lint -save -e506 Lint reports: Constant value Boolean*/
    Adc_HwReg[0]->SGx[0].SGCR.UINT32 = 0uL;
    Adc_HwReg[0]->ADCR.UINT32 = 0uL;
#if defined(CFG_RH850F1H)
    Adc_HwReg[1]->SGx[0].SGCR.UINT32 = 0uL;
    Adc_HwReg[1]->ADCR.UINT32 = 0uL;
#endif
    /*lint -restore */
}
#endif

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
void Adc_Hw_StartGroupConversion (Adc_GroupType group){
    const Adc_GroupDefType * groupPtr = NULL;

    for (uint32 configId = 0; configId < ADC_ARC_CTRL_CONFIG_CNT; configId++) {
        if( GET_CONFIG_PTR(configId)->hwConfigPtr->hwUnitId == (group / ADC_NOF_GROUP_PER_CONTROLLER) ){
            if( GET_CONFIG_PTR(configId)->nbrOfGroups > (group % ADC_NOF_GROUP_PER_CONTROLLER) ){
                groupPtr =  &(GET_CONFIG_PTR(configId)->groupConfigPtr[group % ADC_NOF_GROUP_PER_CONTROLLER]);
            }
        }
    }

    VALIDATE_NO_RV( NULL != groupPtr , ADC_STARTGROUPCONVERSION_ID, ADC_E_PARAM_POINTER);

    Adc_ArcControllerIdType hwUnit = groupPtr->hwUnit;
//	volatile uint32* adcanvcrPtr = (volatile uint32*)Adc_HwReg[hwUnit]->VCR[0].UINT32;
    Adc_ChannelType i;

    for (i = 0; i < groupPtr->numberOfChannels; i++) {
        Adc_HwReg[hwUnit]->VCR[i].UINT32 = groupPtr->channelList[i];
    }

    /* Virtual Channel to start at */
    Adc_HwReg[hwUnit]->SGx[0].SGVCSP.UINT32 = 0;

    /* Virtual Channel to end at */
    Adc_HwReg[hwUnit]->SGx[0].SGVCEP.UINT32 = i - 1;

    //Always continuous, we turn on/off the interrupts in the interrupt handler.
    Adc_HwReg[hwUnit]->SGx[0].SGCR.UINT32 = ADC_CONV_MODE_CONTINUOUS | SCAN_END_INTERRUPT_ENABLE; /*lint !e9027 !e641 2012 10.1 Unpermitted operand to operator '|'  & Enum to int*/

    /* Start group conversion */
    /* @req SWS_Adc_00061 */
    Adc_HwReg[hwUnit]->SGx[0].SGSTCR.UINT32 = 1uL;
}
void Adc_Hw_StopGroupConversion (Adc_GroupType group){
    uint32 hwId = group / ADC_NOF_GROUP_PER_CONTROLLER;

    /* Disable trigger normal conversions for ADC0 */
    /*@req SWS_Adc_00385 */
    /*@req SWS_Adc_00386 */
    Adc_HwReg[hwId]->ADHALTR.UINT32 = 1uL;
    Adc_HwReg[hwId]->SGx[0].SGCR.UINT32 = 1uL;
}
#endif

ISR(ADCA0GrpConversionComplete_Isr){
    GroupConversionComplete(HWUNIT_ADCA0);
}
ISR(ADCA1GrpConversionComplete_Isr){
    GroupConversionComplete(HWUNIT_ADCA1);
}

static void GroupConversionComplete(Adc_ArcControllerIdType ADCn){
    uint32 configId;
    const Adc_GroupDefType *groupPtr = NULL;
    uint32 group;

    /* Disable interrupts */
    /* @req SWS_Adc_00078 */
    Adc_HwReg[ADCn]->SGx[0].SGCR.UINT32 &=  ~SCAN_END_INTERRUPT_ENABLE;

    for (configId = 0; configId < ADC_ARC_CTRL_CONFIG_CNT; configId++) {
        if( GET_CONFIG_PTR(configId)->hwConfigPtr->hwUnitId == ADCn ){
            break;
        }
    }

    // Check which group is busy, only one is allowed to be busy at a time in a hw unit
    for (group = 0; group <  GET_CONFIG_PTR(configId)->nbrOfGroups; group++){
        if( GET_CONFIG_PTR(configId)->groupConfigPtr[group].status->groupStatus != ADC_IDLE){
            groupPtr = &( GET_CONFIG_PTR(configId)->groupConfigPtr[group]);
            break;
        }
    }

    if( groupPtr != NULL ){
        for(Adc_ChannelType index=0; index < groupPtr->numberOfChannels; index++){
            /* To get the layout of the buffer right, first all samples from one channel,
                         then all samples for the next etc.*/
            Adc_ValueGroupType test = (Adc_ValueGroupType)(Adc_HwReg[ADCn]->DIR[index]);
            groupPtr->status->currResultBufPtr[index*(uint32)groupPtr->streamNumSamples] = test;
        }
    }

    Adc_Internal_Isr(groupPtr);
}

void Adc_Hw_IsrPost(const Adc_GroupDefType * groupPtr, boolean enableInt) {
    if (enableInt) {
        if (ADC_TRIGG_SRC_HW == groupPtr->triggerSrc) {
            //Improvement: HW Trigger support.
        } else {
            Adc_HwReg[groupPtr->hwUnit]->SGx[0].SGCR.UINT32 |= SCAN_END_INTERRUPT_ENABLE;
        }
    }
}
