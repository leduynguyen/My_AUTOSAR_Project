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

/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ|PPC|MPC5645S|MPC5607B|JACINTO5|JACINTO6|MPC5748G */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */


#ifndef SPI_H_
#define SPI_H_

/* @req SWS_Spi_00272 */
#include "Std_Types.h"

/* Standard info */
#define SPI_VENDOR_ID             60u
#define SPI_MODULE_ID             83u

#define SPI_SW_MAJOR_VERSION      2u
#define SPI_SW_MINOR_VERSION      0u
#define SPI_SW_PATCH_VERSION      0u

#define SPI_AR_RELEASE_MAJOR_VERSION      4u
#define SPI_AR_RELEASE_MINOR_VERSION      1u
#define SPI_AR_RELEASE_PATCH_VERSION      2u


/* --- Service IDs --- */
#define SPI_INIT_SERVICE_ID                         0x00u
#define SPI_DEINIT_SERVICE_ID                       0x01u
#define SPI_WRITEIB_SERVICE_ID                      0x02u
#define SPI_ASYNCTRANSMIT_SERVICE_ID                0x03u
#define SPI_READIB_SERVICE_ID                       0x04u
#define SPI_SETUPEB_SERVICE_ID                      0x05u
#define SPI_GETSTATUS_SERVICE_ID                    0x06u
#define SPI_GETJOBRESULT_SERVICE_ID                 0x07u
#define SPI_GETSEQUENCERESULT_SERVICE_ID            0x08u
#define SPI_GETVERSIONINFO_SERVICE_ID               0x09u
#define SPI_SYNCTRANSMIT_SERVICE_ID                 0x0Au
#define SPI_GETHWUNITSTATUS_SERVICE_ID              0x0Bu
#define SPI_CANCEL_SERVICE_ID                       0x0Cu
#define SPI_SETASYNCMODE_SERVICE_ID                 0x0Du
#define SPI_MAINFUNCTION_HANDLING_SERVICE_ID        0x10u

/* ArcCore extra */
#define SPI_GENERAL_SERVICE_ID                      0x20u

/* --- Error codes --- */
#define SPI_E_PARAM_CHANNEL               0x0Au
#define SPI_E_PARAM_JOB                   0x0Bu
#define SPI_E_PARAM_SEQ                   0x0Cu
#define SPI_E_PARAM_LENGTH                0x0Du
#define SPI_E_PARAM_UNIT                  0x0Eu
#define SPI_E_PARAM_POINTER               0x10u
#define SPI_E_UNINIT                      0x1Au
#define SPI_E_SEQ_PENDING                 0x2Au
#define SPI_E_SEQ_IN_PROCESS              0x3Au
#define SPI_E_ALREADY_INITIALIZED         0x4Au
#define SPI_E_UNEXPECTED_EXECUTION        0x50u

/* The possible levels of SPI_LEVEL_DELIVERED */
/* Basic Synchronous functions */
#define SPI_LEVEL_0									(0u)
/* Basic Asynchronous functions */
#define SPI_LEVEL_1									(1u)
/* Synchronous and Asynchronous functions */
#define SPI_LEVEL_2									(2u)

#if defined(CFG_TMS570)
#include "Spi_TMS570.h"
#else



/* ArcCore extra */
#define SPI_E_CONFIG_INVALID              0x50u
#define SPI_E_SEQUENCE_NOT_OK             0x60u

#define CH_NOT_VALID 	(0xffu)
#define JOB_NOT_VALID	(0xffffu)
#define SEQ_NOT_VALID	(0xffu)

/* Types according to standard */
/* @req SWS_Spi_00378 */
typedef uint8 Spi_ChannelType ;
/* @req SWS_Spi_00379 */
typedef uint16 Spi_JobType;
/*@req SWS_Spi_00380 */
typedef uint8 Spi_SequenceType;

#define SPI_SIMPLE         0u   /* Not implemented, NOT TESTED */
#define SPI_FIFO           1u
#define SPI_DMA            2u

#define SPI_EB_MAX_LENGTH 64u

#define CSIB0	0u
#define CSIB1   1u
#define CSIB2   2u
#define CSIB3   3u
#define CSIB4   4u
#define CSIB5   5u

/* @req SWS_Spi_00367 */
/* @req SWS_Spi_00373 */
typedef enum {
    SPI_UNINIT=0, // The SPI Handler/Driver is not initialized or not usable.
                // SPI011: This shall be the default value after reset. This
                // status shall have the value 0.

    SPI_IDLE,	// The SPI Handler/Driver is not currently transmitting any
                // Job.

    SPI_BUSY, 	// The SPI Handler/Driver is performing a SPI Job( transmit )
} Spi_StatusType;

/* @req SWS_Spi_00374 */
/* @req SWS_Spi_00062 */
typedef enum {
    SPI_JOB_OK=0, 		// The last transmission of the Job has been finished
                        // successfully.
                        // SPI012: This shall be the default value after reset.
                        // This status shall have the value 0.

    SPI_JOB_PENDING,	// The SPI Handler/Driver is performing a SPI Job.
                        // The meaning of this status is equal to SPI_BUSY.

    SPI_JOB_FAILED, 	// The last transmission of the Job has failed.

    SPI_JOB_QUEUED, 	// Job accepted but not started.

} Spi_JobResultType;

/* @req SWS_Spi_00375 */
/* @req SWS_Spi_00019 */
typedef enum {

    SPI_SEQ_OK, 	//	The last transmission of the Sequence has been
                    //    finished successfully.
                    //    SPI017: This shall be the default value after reset.
                    //    This status shall have the value 0.

    SPI_SEQ_PENDING, // The SPI Handler/Driver is performing a SPI
                // Sequence. The meaning of this status is equal to
                // SPI_BUSY.

    SPI_SEQ_FAILED, 	// The last transmission of the Sequence has failed.

    SPI_SEQ_CANCELED, 	// The last transmission of the Sequence has been
                    //    cancelled by user.
} Spi_SeqResultType;


// Type for defining the number of data elements of the type Spi_DataBufferType to
// send and / or receive by Channel
/* @req SWS_Spi_00377 */
typedef uint16 Spi_NumberOfDataType;


// Specifies the asynchronous mechanism mode for SPI busses handled
// asynchronously in LEVEL 2.
// SPI150: This type is available or not accordint to the pre compile time parameter:
// SPI_LEVEL_DELIVERED. This is only relevant for LEVEL 2.

/* @req SWS_Spi_00382 */
typedef enum {

    //	The asynchronous mechanism is ensured by
    //    polling, so interrupts related to SPI busses
    //    handled asynchronously are disabled.
    SPI_POLLING_MODE,

    //    The asynchronous mechanism is ensured by
    //    interrupt, so interrupts related to SPI busses
    //    handled asynchronously are enabled.

    SPI_INTERRUPT_MODE,
} Spi_AsyncModeType;

typedef enum
{
  SPI_EB = 0, // External Buffer
  SPI_IB // Internal Buffer
} Spi_BufferType;

typedef enum
{
  SPI_TRANSFER_START_LSB,
  SPI_TRANSFER_START_MSB,
} Spi_TransferStartType;


typedef enum {
    SPI_EDGE_LEADING,
    SPI_EDGE_TRAILING
} Spi_EdgeType;



/* @req SWS_Spi_00273 */
#include "Spi_Cfg.h"
#if (SPI_IMPLEMENTATION==SPI_DMA)
#include "Dma.h"
#endif


// The communication settings of an external device. Closely linked to Spi-
// Job.
typedef struct Spi_ExternalDevice
{

  // This parameter is the communication baudrate - This parameter allows
  // using a range of values, from the point of view of configuration tools, from
  // Hz up to MHz.
  // Note! Float in config case, not here
  uint32 SpiBaudrate;

  // Symbolic name to identify the CS used for this job
  uint32 SpiCsIdentifier;

  // This parameter defines the active polarity of Chip Select.
  // STD_HIGH or STD_LOW
  uint8 SpiCsPolarity;

  // This parameter defines the SPI data shift edge.
  Spi_EdgeType SpiDataShiftEdge;

  // This parameter enables or not the Chip Select handling functions.
  uint8 SpiEnableCs;

  uint32 SpiHwUnit;

  // This parameter defines the SPI shift clock idle level.
  uint8 SpiShiftClockIdleLevel;

  // Timing between clock and chip select - This parameter allows to use a
  // range of values from 0 up to 100 microSec. the real configuration-value
  // used in software BSW-SPI is calculated out of this by the generator-tools
  // Note! Float in config case, not here. Unit ns
  uint32 SpiTimeClk2Cs;

  // Timing between PCS and first edge of SCK. Unit ns.
  uint32 SpiTimeCs2Clk;

  void (*SpiCsCallback)(uint32 active);

} Spi_ExternalDeviceType;

// All data needed to configure one SPI-channel
typedef struct Spi_ChannelConfig
{
  // Symbolic name
  Spi_ChannelType SpiChannelId;
  // Buffer usage with EB/IB channel
  Spi_BufferType SpiChannelType;

  // This parameter is the width of a transmitted data unit.
  uint32 SpiDataWidth;
  // This parameter is the default value to transmit.
  uint32 SpiDefaultData;

  // This parameter contains the maximum size of data buffers in case of EB
  // Channels and only.
  Spi_NumberOfDataType SpiEbMaxLength;

  // This parameter contains the maximum number of data buffers in case of IB
  // Channels and only.
  Spi_NumberOfDataType SpiIbNBuffers;

  // This parameter defines the first starting bit for transmission.
  Spi_TransferStartType SpiTransferStart;

} Spi_ChannelConfigType;

typedef void (*SpiJobEndNotification_Type)(void);


// All data needed to configure one SPI-Job, amongst others the connection
// between the internal SPI unit and the special settings for an external de-
// vice is done.
/* @req SWS_Spi_00064 */
typedef struct Spi_JobConfig
{

  Spi_JobType SpiJobId;

  //	This parameter is the symbolic name to identify the HW SPI Hardware micro-
  //	controller peripheral allocated to this Job.
  uint32 SpiHwUnit;

  // This parameter is a reference to a notification function.
  SpiJobEndNotification_Type SpiJobEndNotification;

  // Priority of the Job
  // range 0..3
  unsigned SpiJobPriority;

  // A job references several channels. IMPROVEMENT: Optimize this...
#if defined(SPI_CONFIG_VERSION)
  const Spi_ChannelConfigType *SpiChannelAssignment[SPI_MAX_CHANNEL+1];
#else
  Spi_ChannelType ChannelAssignment[SPI_MAX_CHANNEL+1];
#endif

  // Reference to the external device used by this job
  /* @req SWS_Spi_00010 */
#if defined(SPI_CONFIG_VERSION)
  const struct Spi_ExternalDevice * SpiDeviceAssignment;
#else
  Spi_ExternalDeviceTypeType DeviceAssignment;
#endif

} Spi_JobConfigType;

/* @req SWS_Spi_00048 */
typedef void (*Spi_CallbackType)(void);

// All data needed to configure one SPI-sequence
typedef struct Spi_SequenceConfig
{
    const sint16 * SpiSeqSharingCommonJobsTablePtr;
  // This parameter allows or not this Sequence to be suspended by another
  // one.
  unsigned SpiInterruptibleSequence;
  // This parameter is a reference to a notification function.
  Spi_CallbackType SpiSeqEndNotification;
  //
  Spi_SequenceType SpiSequenceId;
  // A sequence references several jobs, which are executed during a commu-
  // nication sequence
#if defined(SPI_CONFIG_VERSION)
  const Spi_JobConfigType *SpiJobAssignment[SPI_MAX_JOB+1];
#else
  Spi_JobType JobAssignment[SPI_MAX_JOB+1];
#endif
} Spi_SequenceConfigType;

typedef struct Spi_HwConfig
{
  /* This channel is to be activated for use. */
  uint8 Activated;

  /* Receive DMA channel. */
#if (SPI_IMPLEMENTATION==SPI_DMA)
  Dma_ChannelType RxDmaChannel;

  /* Transmit DMA channel. */
  Dma_ChannelType TxDmaChannel;
#endif
}Spi_HwConfigType;


// This is implementation specific but not all values may be valid
// within the type.This type shall be chosen in order to have the
// most efficient implementation on a specific microcontroller
// platform.
// In-short: Type of application data buffer elements
// The 5516 TXDATA is 16-bit.. fits ?
/* @req SWS_Spi_00376 */
/* @req SWS_Spi_00355 */
/* @req SWS_Spi_00164 */
typedef uint8 Spi_DataBufferType;

/* Spi_DataType is used in 4.0.3 while Spi_DataBufferType is used 4.1.2 */
typedef Spi_DataBufferType Spi_DataType;

// Specifies the identification (ID) for a SPI Hardware microcontroller peripheral (unit).
// SPI140: This type is configurable (On / Off) at pre-compile time. The switch
// SPI_HW_STATUS_API shall activate or deactivate the declaration of this
// type.
/* @req SWS_Spi_00381 */
typedef uint8 Spi_HWUnitType;

/* @req SWS_Spi_00344 */
/* @req SWS_Spi_00008 */
typedef struct Spi_Driver
{
  //	This parameter contains the number of Channels configured. It will be
  //	gathered by tools during the configuration stage.
  uint8 SpiMaxChannel;

  uint8 SpiMaxJob;

  uint8 SpiMaxSequence;

  // All data needed to configure one SPI-channel
  /* @req SWS_Spi_00063 */
  const struct Spi_ChannelConfig * SpiChannelConfig;

  // The communication settings of an external device. Closely
  // linked to SpiJob.
  const struct Spi_ExternalDevice * SpiExternalDevice;

  //	All data needed to configure one SPI-Job, amongst others the
  //	connection between the internal SPI unit and the special set-
  //	tings for an external device is done.
  const struct Spi_JobConfig * SpiJobConfig;

  // All data needed to configure one SPI-sequence
  const struct Spi_SequenceConfig * SpiSequenceConfig;

#if defined(SPI_USE_ARC_HW_STRUCT)
  const Spi_Hw_DeviceConfigType * SpiHwDeviceConfig;
#endif

} Spi_DriverType;
/* @req SWS_Spi_00372 */
typedef Spi_DriverType Spi_ConfigType;

/* @req SWS_Spi_00175 */
void Spi_Init( const Spi_ConfigType *ConfigPtr );

/* @req SWS_Spi_00176 */
Std_ReturnType Spi_DeInit( void );

/* !req SWS_Spi_00177 */
Std_ReturnType Spi_WriteIB( Spi_ChannelType Channel, const Spi_DataBufferType *DataBufferPtr );


/* @req SWS_Spi_00178 */
Std_ReturnType Spi_AsyncTransmit( Spi_SequenceType Sequence );

/* !req SWS_Spi_00179 */
Std_ReturnType Spi_ReadIB( Spi_ChannelType Channel, Spi_DataBufferType * DataBufferPtr ) ;

/* @req SWS_Spi_00180 */
Std_ReturnType Spi_SetupEB( Spi_ChannelType Channel,
                            const Spi_DataBufferType*  SrcDataBufferPtr,
                            Spi_DataBufferType* DesDataBufferPtr,
                            Spi_NumberOfDataType Length );

/* @req SWS_Spi_00181 */
Spi_StatusType Spi_GetStatus( void );

/* @req SWS_Spi_00182 */
Spi_JobResultType Spi_GetJobResult ( Spi_JobType Job );

/* @req SWS_Spi_00183 */
Spi_SeqResultType Spi_GetSequenceResult(Spi_SequenceType Sequence );

#if ( SPI_VERSION_INFO_API == STD_ON  )
/* @req SWS_Spi_00184*/
void Spi_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

/* @req SWS_Spi_00185 */
Std_ReturnType Spi_SyncTransmit( Spi_SequenceType Sequence );

#if (SPI_HW_STATUS_API == STD_ON)
/* @req SWS_Spi_00186 */
/* @req SWS_Spi_00142 */
Spi_StatusType Spi_GetHWUnitStatus(Spi_HWUnitType HWUnit);
#endif

#if (SPI_CANCEL_API == STD_ON )
/* !req SWS_Spi_00187 */
/* !req SWS_Spi_00146 */
void Spi_Cancel( Spi_SequenceType Sequence );
#endif

/* @req SWS_Spi_00188 */
Std_ReturnType Spi_SetAsyncMode( Spi_AsyncModeType Mode );

/* @req SWS_Spi_00189 */
void Spi_MainFunction_Handling( void );

extern const Spi_ConfigType SpiConfigData;

#endif
#endif /*SPI_H_*/

