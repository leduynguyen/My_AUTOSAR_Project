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

/* IMPLEMENTATION NOTES
 *   This driver is implemented with to work with over SPI with
 *   "ADC128S102 8-Channel, 500-ksps to 1-Msps, 12-Bit A/D Converter"
 *
 *   However this driver should be able to be used for most ADCs over SPI
 *   assuming that it's above 8-bit.
 *
 *   The driver is configured as normal ADC driver can currently not be added
 *   to an architecture that already have support for ADC.
 */


/** @tagSettings DEFAULT_ARCHITECTURE=JACINTO6 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/* !req SWS_Adc_00082  IoHwAb not supported with external hardware*/
/* !req SWS_Adc_00083  IoHwAb not supported with external hardware*/
/* @req SWS_Adc_00085  call-backs defined during configuration*/
/* @req SWS_Adc_00104  Each group has the possibility to have separate call-backs*/
/* !req SWS_Adc_00342  not implemented on top level architecture*/
/* !req SWS_Adc_00416  Not possible to change notification settings during runtime*/
/* @req SWS_Adc_00056  Initialization done in top level and in SPI drivers*/

/* ----------------------------[includes]------------------------------------*/
#include <string.h>

#include "Adc.h"
#include "Adc_Internal2.h"
#include "Spi.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "isr.h"
#include "irq_types.h"

/* ----------------------------[private define]------------------------------*/
#define MASK_12BIT_ADC                  0xFFFuL

#define VALIDATE_NO_RV(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(ADC_MODULE_ID,0,_api,_err); \
          return; \
        }

#define DET_REPORTERROR(_x,_y,_z,_q) (void)Det_ReportError(_x, _y, _z, _q)
#define   ADC_HW_MAIN_SPI_INIT                           0x1Cu

/* ----------------------------[private macro]-------------------------------*/

#define EXTERNAL_JOB(_x)		ExternalSpiDevices[_x]->SpiJobAssignment
#define EXTERNAL_CHANNEL(_x)	ExternalSpiDevices[_x].SpiSequence->SpiJobAssignment[0]->SpiChannelAssignment[0]->SpiChannelId
#define GROUP_MODE(_x)		AdcGroupConfiguration_AdcHwUnit[_x].conversionMode
#define CURRENT_GROUP(_x) 	AdcGroupConfiguration_AdcHwUnit[_x]


/** API service ID's */
#define ADC_MAINFUNCTION_ID 0x0Du

/* ----------------------------[private typedef]-----------------------------*/
typedef struct {
    /** Reference to SPI sequence (required for external ADC drivers). */
    const Spi_SequenceConfigType* SpiSequence;

} Adc_ExternalDriver;




/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

static uint16 adcResultBuffer[16];
static uint16 adcAddr[16];

Adc_StateType adcInternalState = ADC_STATE_UNINIT;
Adc_ExternalDriver ExternalSpiDevices[ADC_NBR_OF_ADCHWUNIT_GROUPS];
boolean runConversion = FALSE;
Adc_GroupType currentGroupIndex;
struct AdcStats {
    uint32 start;
    uint32 stop;
    uint32 handler;
    uint32 post;
};

struct AdcStats adcStats;

/* ----------------------------[private functions]---------------------------*/


/* ----------------------------[public functions]----------------------------*/

void Adc_Handler(void);
void Adc_Hw_DeInit(void);
void Adc_Hw_StartGroupConversion(Adc_GroupType group);
/**
 * Used to initialize hardware
 * @param ConfigPtr
 */
void Adc_Hw_Init(const Adc_ConfigType* ConfigPtr){
     VALIDATE_NO_RV( (NULL != ConfigPtr), ADC_INIT_ID, ADC_E_PARAM_POINTER);
     adcInternalState = ADC_STATE_INIT;
}

#if (ADC_DEINIT_API == STD_ON)
void Adc_Hw_DeInit(void){
    /* @req SWS_Adc_00110 */
    adcInternalState = ADC_STATE_UNINIT;
}
#endif

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
void Adc_Hw_StartGroupConversion (Adc_GroupType group){
    const Adc_GroupDefType* groupPtr = &AdcConfig[0].groupConfigPtr[group];
    Std_ReturnType retVal = E_NOT_OK;

    VALIDATE_NO_RV( NULL != groupPtr , ADC_STARTGROUPCONVERSION_ID, ADC_E_PARAM_POINTER);
    memset(adcResultBuffer, 0x00u, sizeof(adcResultBuffer));


//    puts("START\n");
    /* Just loop over the channels and send the first round of conversions
     * Note that streamNumSamples is handled later.
     * */
    for (uint32 ch = 0; ch < groupPtr->numberOfChannels; ch++) {
        adcAddr[ch] = ((uint16)((AdcChannelConfiguration_AdcHwUnit[groupPtr->channelMappingList[ch]].Adc_Channel)) << (3u+8u));
    }

    adcAddr[groupPtr->numberOfChannels] = 0;

    /* Start group conversion */
    /* @req SWS_Adc_00061 */
   retVal = Spi_SetupEB(groupPtr->ExtChannelId, (Spi_DataBufferType *)&adcAddr[0], (Spi_DataBufferType *)&adcResultBuffer[0], groupPtr->numberOfChannels + 1u );
   if(retVal == E_OK){
       retVal = Spi_AsyncTransmit(groupPtr->ExtSequenceId);
       if (retVal == E_OK )  {
           runConversion = TRUE;
           currentGroupIndex = group;
           adcStats.start++;
       }
   }
}

void Adc_Hw_StopGroupConversion (Adc_GroupType group){
    const Adc_GroupDefType* groupPtr = &AdcConfig[0].groupConfigPtr[currentGroupIndex];

    runConversion = FALSE;
    adcStats.stop++;

    while( Spi_GetSequenceResult(groupPtr->ExtSequenceId) == SPI_SEQ_PENDING ) {};
}
#endif

void Adc_Hw_EnableHardwareTrigger(Adc_GroupType Group){
    /*NOT SUPPORTED*/
}

void Adc_Hw_DisableHardwareTrigger(Adc_GroupType Group){
    /*NOT SUPPORTED*/
}

void Adc_Handler(void) {

    adcStats.handler++;
    if( !runConversion ) {
        return;
    }

    const Adc_GroupDefType* groupPtr = &AdcConfig[0].groupConfigPtr[currentGroupIndex];
    uint16 conversionData[(groupPtr->numberOfChannels * groupPtr->streamNumSamples)];
    memset(conversionData, 0x00u, sizeof(conversionData));

    if( groupPtr != NULL ){
        for(uint32 index=0; index < groupPtr->numberOfChannels; index++){
            /* To get the layout of the buffer right, first all samples from one channel,  then all samples for the next etc.*/
            groupPtr->status->currResultBufPtr[index*(uint32)groupPtr->streamNumSamples] = adcResultBuffer[index+1u];
        }
    }

    /* @req SWS_Adc_00080 */
    /* @req SWS_Adc_00060 */
    Adc_Internal_Isr(groupPtr);
}

void Adc_Hw_IsrPost(const Adc_GroupDefType * groupPtr, boolean enableInt) {

    adcStats.post++;

    if( runConversion ) {
        if ( enableInt ) {
            Spi_SetupEB(groupPtr->ExtChannelId, (Spi_DataBufferType *)&adcAddr[0], (Spi_DataBufferType *)&adcResultBuffer[0], groupPtr->numberOfChannels + 1u );
            (void)Spi_AsyncTransmit(groupPtr->ExtSequenceId);
        } else {
        }
    }
}


