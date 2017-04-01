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

#ifndef SPI_INTERNAL_H_
#define SPI_INTERNAL_H_

/*Lint Exception */
/*lint -save -e613 -e794 Our asserts check for null pointers.*/

#include "arc_assert.h"
#include "Spi.h"
#if defined(USE_DET) && (SPI_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
#define SPIE_BAD		  (-1)
#define SPIE_OK				0
#define SPIE_JOB_NOT_DONE   1
#define SPIE_JOB_PENDING    1

#define GET_SPI_UNIT_PTR(_unit) &Spi_Unit[Spi_CtrlToUnit[_unit]]

#if !defined(CFG_ZYNQ)
#if defined(USE_LOCAL_RAMLOG)
#define SPI_ASSERT(_exp)	if( !(_exp) ) while(1) {}
#else
#define SPI_ASSERT(_exp)	ASSERT(_exp)
#endif
#endif

#if defined(USE_DET) && (SPI_DEV_ERROR_DETECT == STD_ON)
#define SPI_DET_REPORT_ERROR(_api,_err) (void)Det_ReportError(SPI_MODULE_ID, 0, _api, _err)
#else
#define SPI_DET_REPORT_ERROR(_api,_err)
#endif

typedef enum {
    SPI_ASYNC_CALL,
    SPI_SYNC_CALL,
} Spi_CallTypeType;

typedef struct {
    const Spi_DataBufferType *      src;    /* Pointer to source buffer */
    Spi_DataBufferType *            dest;   /* Pointer to destination buffer */
    Spi_NumberOfDataType            length; /* Number of elements of Spi_DataBufferType in destination buffer */
    boolean                         active; /* Set if the buffer is configured. */
} Spi_EbType;

typedef struct {
    boolean 				initRun;		/* Initially FALSE set to TRUE if Spi_Init() have been called */
    const Spi_ConfigType *  configPtr;      /* Pointer to the configuration */
    Spi_EbType *            extBufPtr;      /* Pointer to the external buffers */
    Spi_AsyncModeType       asyncMode;

    /* Debug Counters */
    uint32 totalNbrOfTranfers;
    uint32 totalNbrOfStartedJobs;

    uint8 channelMap[SPI_ARC_CTRL_MAX + 1];
    uint8 channelToHwChannel[SPI_ARC_CTRL_MAX + 1];
} Spi_GlobalType;

typedef struct  {
    uint8 index;
    Spi_SequenceType seqQueue[SPI_EXT_DEVICES_CNT];
} Spi_QueueType; /*lint !e9038 not flexible */




/**
 * This structure represents a controller unit
 */
typedef struct {
    struct privData                *pData;          /* HW Private data */

    const Spi_JobConfigType *       jobPtr;         /* The current job                     */
    const Spi_SequenceConfigType *  seqPtr;         /* The current job                     */

    const Spi_ExternalDeviceType *  extDevPtr;      /* The current job                     */

    uint8                           rxChIdxInJob;   /* */
    uint8                           txChIdxInJob;   /* */

    uint8                           jobIdxInSeq;    /* */

    Spi_StatusType 					status;          /* Status for this unit				*/
    Spi_CallTypeType callType;                       /* 1 -  if the current job is sync. 0 - if not */

    uint8                           hwUnit;
    /* Queue sequences that share the same controller */
    Spi_QueueType                   queueHead;

} Spi_UnitType;


/**
 * Push to the queue
 *
 * @param qPtr Pointer to the queue head
 * @param val  The value to push
 * @return 0 - if pushed OK
 *         1-  Did not push
 */
static inline uint32_t QueuePush( Spi_QueueType *qPtr, Spi_SequenceType val ) {
    ASSERT(qPtr!=NULL);
    uint32_t rv;

    if( qPtr->index == (SPI_EXT_DEVICES_CNT-1uL) ) { /*lint !e778 !e685 CONFIGURATION EXCEPTION */
        rv = 1;
    } else {
        qPtr->seqQueue[qPtr->index] = val;
        qPtr->index++;
        rv = 0;
    }

    return rv;
}

/**
 * Pop an item from the queue
 *
 * @param qPtr Pointer to the queue head
 * @param val
 * @return 0 - Value pop:ed ok
 *         1 - Nothing to pop.
 */
static inline uint32_t QueuePop( Spi_QueueType *qPtr, Spi_SequenceType *val) {
    ASSERT(qPtr!=NULL);
    uint32_t rv;
    if( qPtr->index == 0 ) {
        rv = 1;
    } else {
        qPtr->index--;
        *val = qPtr->seqQueue[qPtr->index];
        rv = 0;
    }
    return rv;
}


typedef struct {
    Spi_JobResultType jobResult;
} Spi_JobUnitType;

/*lint -esym(9003,Spi_Global, Spi_CtrlToUnit) Need to be global */
extern Spi_GlobalType  Spi_Global;
extern Spi_UnitType    Spi_Unit[SPI_CONTROLLER_CNT];
extern Spi_JobUnitType Spi_JobUnit[SPI_MAX_JOB];
extern uint8 Spi_CtrlToUnit[6];

#define GET_CONFIG(ch)          (*Gpt_Global.config)[ch]
#define Spi_Conf




/**
 * Get sequence ptr from sequence index
 * @param seqIndex the sequence
 * @return Ptr to the sequence configuration
 */

static inline const Spi_SequenceConfigType *Config_GetSequence( Spi_SequenceType sequence ) {
    return &Spi_Global.configPtr->SpiSequenceConfig[sequence];
}

/**
 * Get configuration job ptr from job index
 * @param jobIndex the job
 * @return Ptr to the job configuration
 */
static inline const Spi_JobConfigType *Config_GetJob( Spi_JobType job ) {
    return &Spi_Global.configPtr->SpiJobConfig[job];
}

static inline const Spi_ChannelConfigType *Config_GetChannel( Spi_ChannelType channel ) {
    return &Spi_Global.configPtr->SpiChannelConfig[channel];
}


static inline void Spi_SetJobResult(Spi_JobType Job, Spi_JobResultType result) {
    Spi_JobUnit[Job].jobResult = result;
}

static inline void Spi_SetHWUnitStatus( Spi_UnitType *uPtr, Spi_StatusType status) {
    uPtr->status = status;
}

/**
 * Get external Ptr to device from index
 *
 * @param deviceType The device index.
 * @return Ptr to the external device
 */

static inline const Spi_ExternalDeviceType *Spi_GetExternalDevicePtrFromIndex( Spi_ExternalDeviceTypeType deviceType) {
    return (&(Spi_Global.configPtr->SpiExternalDevice[(deviceType)]));
}


static inline uint8 HwChannelToChannel(uint8 ch) {
    return Spi_Global.channelMap[ch];
}
static inline uint8 ChannelToHwChannel(uint8 ch) {
    return Spi_Global.channelToHwChannel[ch];
}

void Spi_Hw_Init( const Spi_ConfigType *ConfigPtr );
sint32 Spi_Hw_Tx( Spi_UnitType *uPtr );
sint32 Spi_Hw_Rx( Spi_UnitType *uPtr );

boolean Spi_Hw_IsTransmissionDone( uint32 hwUnit );
void Spi_Hw_EndTransmission(Spi_UnitType *uPtr);
void Spi_Hw_InitController( uint32 hwUnit  );
void Spi_Hw_DeInitController( uint32 hwUnit );
void Spi_Hw_DisableInterrupt( uint32 hwUnit );
void Spi_Hw_EnableInterrupt( uint32 hwUnit );
void Spi_Hw_Halt( uint32 hwUnit );

Spi_DataBufferType *Spi_Internal_GetRxChBuf(Spi_ChannelType ch, Spi_NumberOfDataType *length );
const Spi_DataBufferType *Spi_Internal_GetTxChBuf(Spi_ChannelType ch, Spi_NumberOfDataType *length );
uint32 Spi_Internal_GetTxDefValue(Spi_ChannelType ch);
void Spi_Internal_Isr( Spi_UnitType *uPtr );
uint16 Spi_Internal_GetNbrChnInJob(const Spi_UnitType *uPtr);
//lint -restore
#endif /* SPI_INTERNAL_H_ */
