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

#ifndef SPI_H
#define SPI_H

/* Requirements : AR_SPI_SR11, AR_SPI_SR12, AR_SPI_SR125, AR_SPI_SR126 */
#include "Std_Types.h"
#include "Spi_Cfg.h"
#include "Spi_Dlc.h"

/* vendor and module identification */


/* Requirements : AR_SPI_SR118 */

/* SourceId : SPI_SourceId_021 */
/* Requirements : AR_SPI_SR117 */

/* HWUnit Index */
#define SPI_UNIT0    (0U)
#define SPI_UNIT1    (1U)
#define SPI_UNIT2    (2U)
#define SPI_UNIT3    (3U)
#define SPI_UNIT4    (4U)

/* Buffer definitions IB=internal, EB=external buffers  */
#define SPI_IB      (0U)
#define SPI_EB      (1U)
#define SPI_IB_EB   (2U)

/* Requirements : AR_SPI_SR88, AR_SPI_SR89, AR_SPI_SR90, AR_SPI_SR91, AR_SPI_SR92, AR_SPI_SR93, AR_SPI_SR94,
 * AR_SPI_SR95, AR_SPI_SR96 */
#ifndef SPI_E_PARAM_CHANNEL
#define SPI_E_PARAM_CHANNEL         (0x0AU) /* wrong channel  parameter given */
#endif
#ifndef SPI_E_PARAM_JOB
#define SPI_E_PARAM_JOB             (0x0BU) /* wrong job      parameter given */
#endif
#ifndef SPI_E_PARAM_SEQ
#define SPI_E_PARAM_SEQ             (0x0CU) /* wrong sequence parameter given */
#endif
#ifndef SPI_E_PARAM_LENGTH
#define SPI_E_PARAM_LENGTH          (0x0DU) /* wrong length   parameter given */
#endif
#ifndef SPI_E_PARAM_UNIT
#define SPI_E_PARAM_UNIT            (0x0EU) /* wrong HWUnit   parameter given */
#endif
#ifndef SPI_E_PARAM_POINTER
#define SPI_E_PARAM_POINTER         (0x10U) /* API called with a NULL pointer */
#endif
#ifndef SPI_E_UNINIT
#define SPI_E_UNINIT                (0x1AU) /* Error code for not initialized module */
#endif
#ifndef SPI_E_SEQ_PENDING
#define SPI_E_SEQ_PENDING           (0x2AU) /* Error code if service called in a wrong sequence */
#endif
#ifndef SPI_E_SEQ_IN_PROCESS
#define SPI_E_SEQ_IN_PROCESS        (0x3AU) /* transmission of sync. sequence in progress */
#endif
#ifndef SPI_E_ALREADY_INITIALIZED
#define SPI_E_ALREADY_INITIALIZED   (0x4AU) /* Init() service called twice without DeInit() */
#endif

/* these are the service IDs of the functions in the ASR SWS specification                                           */
#define SPI_SID_INIT                  (0x00U)
#define SPI_SID_DEINIT                (0x01U)
#define SPI_SID_WRITE_IB              (0x02U)
#define SPI_SID_ASYNC_TRANSMIT        (0x03U)
#define SPI_SID_READ_IB               (0x04U)
#define SPI_SID_SETUP_EB              (0x05U)
#define SPI_SID_GET_STATUS            (0x06U)
#define SPI_SID_GET_JOB_RESULT        (0x07U)
#define SPI_SID_GET_SEQ_RESULT        (0x08U)
#define SPI_SID_GETVERSION_INFO       (0x09U)
#define SPI_SID_SYNC_TRANSMIT         (0x0AU)
#define SPI_SID_GET_UNIT_STATUS       (0x0BU)
#define SPI_SID_CANCEL                (0x0CU)
#define SPI_SID_SET_ASYNC_MODE        (0x0DU)
#define SPI_SID_MAINFUNCTION_HANDLING (0x10U)
#define SPI_SID_MAINFUNCTION_DRIVING  (0x11U)

#define SPI_INSTANCE_ID (0)

/* Some arccore carryover */
#define CSIB0	0
#define CSIB1   1
#define CSIB2   2
#define CSIB3   3
#define CSIB4   4

#define SPI_EB_MAX_LENGTH 64

/* Driver status enumerations */
/* Requirements : AR_SPI_SR133 */
typedef enum
{
    SPI_UNINIT = 0U,
    SPI_IDLE = 1U,
    SPI_BUSY = 2U
}   Spi_StatusType;

/* Requirements : AR_SPI_SR142 */
typedef enum
{
    SPI_JOB_OK = 0U,
    SPI_JOB_PENDING = 1U,
    SPI_JOB_QUEUED = 2U,
    SPI_JOB_FAILED = 3U,
    SPI_JOB_ACTIVE = 4U
} Spi_JobResultType;

typedef enum
{
    SPI_DLC_OK = 0U,
    SPI_DLC_PENDING = 1U,
    SPI_DLC_FAILED = 2U
}Spi_HwUnitResultType;

/* Requirements : AR_SPI_SR146, AR_SPI_SR147 */
typedef enum
{
    SPI_SEQ_OK = 0U,
    SPI_SEQ_PENDING = 1U,
    SPI_SEQ_FAILED = 2U,
    SPI_SEQ_CANCELLED = 3U
} Spi_SeqResultType;

typedef enum
{
    SPI_MSB = 0U,
    SPI_LSB = 1U
} Spi_TransferType;

/* type for SpiCsPolarity and SpiShiftClockIdleLevel */
typedef enum
{
    SPI_LOW = STD_LOW,
    SPI_HIGH
} Spi_LevelType;

/* type for  SpiCsIdentifier */
typedef enum
{
    SPI_SCS0 = 0U,
    SPI_SCS1,
    SPI_SCS2,
    SPI_SCS3
} Spi_ScsType;

/* type for SpiCsMode */
typedef enum
{
    SPI_SINGLE = 0U,
    SPI_CONTINUOUS = 1U
} Spi_CsModeType;

/* type for SpiCsMode */
typedef enum
{
    SPI_DIGITAL_LPBK = 0U,
    SPI_ANALOG_LPBK = 1U
} Spi_LoopbackModeType;

/* enums end */

/* Driver, job, sequence status types */

/* SourceId : SPI_SourceId_026 */
/* Requirements : AR_SPI_SR155 */
typedef uint16 Spi_NumberOfDataType;
/* SourceId : SPI_SourceId_027 */
/* Requirements : AR_SPI_SR158, AR_SPI_SR159 */
typedef uint16 Spi_JobType;
/* SourceId : SPI_SourceId_028 */
/* Requirements : AR_SPI_SR153, AR_SPI_SR154 */
typedef uint8  Spi_DataType;
typedef uint8 Spi_DataBufferType;
/* SourceId : SPI_SourceId_029 */
/* Requirements : AR_SPI_SR156, AR_SPI_SR157 */
typedef uint8  Spi_ChannelType;
/* SourceId : SPI_SourceId_030 */
/* Requirements : AR_SPI_SR160, AR_SPI_SR161 */
typedef uint8  Spi_SequenceType;
/* SourceId : SPI_SourceId_031 */
/* Requirements : AR_SPI_SR162, AR_SPI_SR163 */
typedef uint8  Spi_HWUnitType;
typedef uint8  Spi_ExternalDeviceType;

/* Requirements : AR_SPI_SR130 */
/* spi external device structure */
typedef struct
{
    uint8 C2td;
    uint8 T2cd;
    uint8 T2ed;
    uint8 C2ed;
} Spi_ClkDelaysType;

typedef struct
{
    uint32 Spi_DioPin;        /* holds the configured Dio pin for toggling CS */
    uint16 Spi_CsProperty;    /* low byte the CS idle level, high byte res. */
    uint16 Spi_Prescaler;
    uint8  Spi_Mode;          /* Mode 0 = {0=CPOL,0=CPHA}; Mode 1={0,1}; Mode 2={1,0} Mode 3={1,1} */
    Spi_ClkDelaysType Spi_ClkDelays;
    uint16 Spi_CsIdleTime;    /* CS idle time if single mode is chosen */
    uint8  Spi_CsMode;        /* select single or continuous mode */
    uint8  Spi_HwInstance;    /* SPI HW Instance */
}Spi_ExternalDeviceConfigType;

/* descriptor type definition for buffers */
typedef struct
{
    P2VAR(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) Spi_Tx_pt;  /* Transmit buffer pointer */
    P2VAR(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) Spi_Rx_pt;  /* Receive buffer pointer */
    uint16 Spi_TxRxLength;    /* length to send and receive */
} Spi_BufferDescriptorType;

/* Requirements : AR_SPI_SR129 */
/* spi channel configuration structure */
typedef struct
{
    P2VAR(Spi_BufferDescriptorType, AUTOMATIC, SPI_VAR_INIT) Spi_Descriptor;
    Spi_ChannelType      Spi_ChannelId;
    uint8                Spi_ChannelBuf;     /* Buffer Type IB/EB */
    uint8                Spi_DataWidth;      /* width of clock frame in bits */
    uint16               Spi_DefaultTxData;  /* Default Transmit Value */
    Spi_NumberOfDataType Spi_BufLength;      /* max Data length external or internal buffer */
    uint8                Spi_TxStart;        /* start with MSB or LSB */
} Spi_ChannelConfigType;

/* Requirements : AR_SPI_SR130, AR_SPI_SR132 */
/* spi job configuration structure */
typedef struct
{
    P2FUNC(void, SPI_APPL_CODE, Spi_JobEndNotification)(void);            /* Job notification */
    P2CONST(Spi_ChannelType, AUTOMATIC, SPI_PBCFG) Spi_ChannelList;       /* Channel index list */
    Spi_ExternalDeviceType Spi_ExDev;           /* external device assigned to a job */
    uint8          Spi_JobID;                   /* job ID */
    uint8          Spi_JobPrio;                 /* job priority */
    Spi_HWUnitType Spi_HWUnitID;                /* HWUnit */
} Spi_JobConfigType;

/* Requirements : AR_SPI_SR131 */
/* spi sequence configuration structure */
typedef struct
{
    P2FUNC(void, SPI_APPL_CODE, Spi_SequenceEndNotification)(void);  /* sequence end notification */
    P2CONST(Spi_JobType, AUTOMATIC, SPI_PBCFG) Spi_JobList;      /* job index list */
    Spi_SequenceType Spi_SeqId;                    /* sequence id */
    uint8            Spi_SeqInt;                   /* sequence interruptible */
} Spi_SequenceConfigType;

typedef struct
{
    P2VAR(Spi_JobResultType, AUTOMATIC, SPI_VAR_ZERO_INIT) Spi_JobResult;      /* job result      */
    P2VAR(Spi_SeqResultType, AUTOMATIC, SPI_VAR_ZERO_INIT) Spi_SeqResult;      /* sequence result */
    P2VAR(Spi_HwUnitResultType, AUTOMATIC, SPI_VAR_ZERO_INIT) Spi_DlcResult;   /* hardware result */
} Spi_ResultType;

/* Requirements : AR_SPI_SR127, AR_SPI_SR128 */
/* spi runtime structure */
typedef struct Spi_Driver
{
    P2CONST(Spi_ExternalDeviceConfigType, AUTOMATIC, SPI_PBCFG) Spi_DevCfg;
    P2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_PBCFG) Spi_ChannelCfg;
    P2CONST(Spi_JobConfigType, AUTOMATIC, SPI_PBCFG) Spi_JobCfg;
    P2CONST(Spi_SequenceConfigType, AUTOMATIC, SPI_PBCFG) Spi_SeqCfg;
    P2CONST(Spi_ResultType, AUTOMATIC, SPI_VAR_INIT) Spi_GlobalStatus_pt;
    uint8 Spi_MaxExtDevs;      /* maximum number of external devices */
    uint8 Spi_MaxChannels;     /* maximum number of channels */
    uint8 Spi_MaxJobs;         /* maximum number of jobs */
    uint8 Spi_MaxSequences;    /* maximum number of sequences */
    uint8 Spi_MaxDlcs;         /* maximum number of dlc's */
} Spi_ConfigType;

typedef Spi_ConfigType Spi_DriverType; //alias for what ArcCore test system expects

typedef struct
{
    uint32 Spi_GCR0 ;         /* SPI Global Control Register 0 */
    uint32 Spi_GCR1 ;         /* SPI Global Control Register 1 */
    uint32 Spi_DEF  ;         /* SPI Default Chip Select Register */
    uint32 Spi_EN   ;         /* Multi-buffer Mode Enable Register */
}Spi_RegisterReadbackType;

/* SourceId : SPI_SourceId_037 */
/* Requirements : AR_SPI_SR164, AR_SPI_SR165, AR_SPI_SR166 */
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
typedef enum
{
    SPI_POLLING_MODE = 0U,
    SPI_INTERRUPT_MODE = 1U
} Spi_AsyncModeType;
#endif /* (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) */

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern CONST(Spi_ConfigType, SPI_PBCFG) SpiRuntime;
extern P2CONST(Spi_ConfigType, SPI_VAR_ZERO_INIT, SPI_PBCFG) Spi_ConfigPtr_pt;
extern volatile Spi_StatusType Spi_DrvStatus;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
FUNC(void, SPI_CODE) Spi_Init
(
    P2CONST(Spi_ConfigType, AUTOMATIC, SPI_PBCFG) ConfigPtr
);
FUNC(Std_ReturnType, SPI_CODE) Spi_DeInit(void);
#if ((SPI_CHANNELBUFFERS == SPI_IB) || (SPI_CHANNELBUFFERS == SPI_IB_EB))
FUNC(Std_ReturnType, SPI_CODE) Spi_WriteIB
(
    Spi_ChannelType Channel,
    P2CONST(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) DataBufferPtr
);
FUNC(Std_ReturnType, SPI_CODE) Spi_ReadIB
(
    Spi_ChannelType Channel,
    P2VAR(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) DataBufferPtr
);
#endif
#if ((SPI_CHANNELBUFFERS == SPI_EB) || (SPI_CHANNELBUFFERS == SPI_IB_EB))
FUNC(Std_ReturnType, SPI_CODE) Spi_SetupEB
(
    Spi_ChannelType Channel,
    P2CONST(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) SrcDataBufferPtr,
    P2VAR(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) DesDataBufferPtr,
    Spi_NumberOfDataType Length
);
#endif
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
FUNC(Std_ReturnType, SPI_CODE) Spi_AsyncTransmit
(
    Spi_SequenceType Sequence
);
#endif
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0)  || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
FUNC(Std_ReturnType, SPI_CODE) Spi_SyncTransmit
(
    Spi_SequenceType Sequence
);
#endif
#if (SPI_CANCEL_API == STD_ON)
FUNC(void, SPI_CODE) Spi_Cancel
(
    Spi_SequenceType Sequence
);
#endif
FUNC(Spi_StatusType, SPI_CODE) Spi_GetStatus(void);
FUNC(Spi_JobResultType, SPI_CODE) Spi_GetJobResult
(
    Spi_JobType Job
);
FUNC(Spi_SeqResultType, SPI_CODE) Spi_GetSequenceResult
(
    Spi_SequenceType Seq
);
FUNC(Spi_StatusType, SPI_CODE) Spi_GetHWUnitStatus
(
    Spi_HWUnitType HWUnit
);

#if (SPI_VERSION_INFO_API == STD_ON)
FUNC(void, SPI_CODE) Spi_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, SPI_APPL_DATA) VersioninfoPtr
);
#endif

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
FUNC(Std_ReturnType, SPI_CODE) Spi_SetAsyncMode
(
    Spi_AsyncModeType Mode
);
#endif

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
FUNC(void, SPI_CODE) Spi_MainFunction_Handling(void);
#endif

#if (SPI_ENABLE_LOOPBACK_MODE_API == STD_ON)
FUNC(Std_ReturnType, SPI_CODE)  Spi_EnableLoopbackMode
(
    Spi_HWUnitType HWUnit,
    Spi_LoopbackModeType LBMode
);
#endif

#if (SPI_DISABLE_LOOPBACK_MODE_API == STD_ON)
FUNC(Std_ReturnType, SPI_CODE)  Spi_DisableLoopbackMode(Spi_HWUnitType HWUnit);
#endif

#if (SPI_REGISTER_READBACK_API == STD_ON)
FUNC(Std_ReturnType, SPI_CODE) Spi_RegisterReadback
(
    P2VAR(Spi_RegisterReadbackType, AUTOMATIC, SPI_APPL_DATA) RegisterReadbackPtr,
    Spi_HWUnitType HWUnit
);
#endif

extern Spi_ConfigType SpiConfigData;

#endif  /* SPI_H */
