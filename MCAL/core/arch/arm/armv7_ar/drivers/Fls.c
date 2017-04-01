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

/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/* ----------------------------[information]----------------------------------*/
/*
 * Description:
 *   Implements the Fls module (flash driver)
 *
 * Support:
 *   General				  Have Support
 *   -------------------------------------------
 *   FLS_AC_LOAD_ON_JOB_START	 Y
 *   FLS_BASE_ADDRESS			 Y, taken from FlashInfo
 *   FLS_CANCEL_API				 N
 *   FLS_COMPARE_API			 Y
 *   FLS_DEV_ERROR_DETECT		 Y
 *   FLS_GET_JOB_RESULT_API		 Y
 *   FLS_GET_STATUS_API			 Y
 *   FLS_SET_MODE_API            Y
 *   FLS_TOTAL_SIZE				 Y, taken from FlashInfo
 *   FLS_USE_INTERRUPTS			 N, no hardware support
 *   FLS_VERSION_INFO_API		 Y
 *
 *   FlsConfigSet			  Have Support
 *   -------------------------------------------
 *   FLS_AC_ERASE				 N
 *   FLS_AC_WRITE			 	 N
 *   FLS_CALL_CYCLE				 N
 *   FLS_JOB_END_NOTIFICATION	 Y
 *   FLS_JOB_ERROR_NOTIFICATION  Y
 *   FLS_MAX_READ_FAST_MODE      N
 *   FLS_MAX_READ_NORMAL_MODE    N
 *   FLS_MAX_WRITE_FAST_MODE	 N
 *   FLS_MAX_WRITE_NORMAL_MODE	 N
 *   FLS_PROTECTION				 N
 *
 *
 *   Device
 *   - ZYNQ Qspi Flash
 *
 * Implementation Notes:
 *   Affected files:
 *   - Fls.c
 *   - Fls_Cfg.c/.h
 *   - Qspi.c/.h     		interface for xqspips driver
 *   - dep.h                low level driver
 *   - xqspips_g.c          low level driver
 *   - xqspips_hw.c         low level driver
 *   - xqspips_hw.h         low level driver
 *   - xqspips_options.c    low level driver
 *   - xqspips_selftest.c   low level driver
 *   - xqspips_sinit.c      low level driver
 *   - xqspips.c            low level driver
 *   - xqspips.h            low level driver
 *
 * Things left:
 *
 */

/*
 * General requirements
 */
/** @req SWS_Fls_00001 *//*The FLS module shall offer asynchronous services for operations on flash memory (read/erase/write).*/
/** @req SWS_Fls_00002 *//*The FLS module shall not buffer data. The FLS module shall use application data buffers that are referenced by a pointer passed via the API.*/
/** @req SWS_Fls_00003 *//*The FLS module shall not ensure data consistency of the given application buffer*/
/** @req SWS_Fls_00206 *//*The FLS module shall validate the version information in the FLS module header and source files for consistency (e.g. by comparing the version information in the module header and source files with a pre-processor macro).*/

/* ----------------------------[includes]------------------------------------*/
/** @req SWS_Fls_00248 */
#include "Fls.h"
#include "MemIf_Types.h"
#include "Mcu.h"
#include "math.h"
#include "arc_assert.h"
#include <string.h>
#if defined(USE_DEM)
#include "Dem.h"
#endif
#if (FLS_DEV_ERROR_DETECT==STD_ON)
#include "Det.h"
#endif

/* ----------------------------[private macro]-------------------------------*/

#if (FLS_DEV_ERROR_DETECT==STD_ON)
#define FEE_JOB_END_NOTIFICATION() \
    /*lint -e{746} Function cannnot be identified as it is a function pointer*/	\
  if( FlsConfig->FlsJobEndNotification != NULL ) { \
    FlsConfig->FlsJobEndNotification(); \
  }

#define FEE_JOB_ERROR_NOTIFICATION() \
  /*lint -e{746} Function cannnot be identified as it is a function pointer*/	\
  if( FlsConfig->FlsJobErrorNotification != NULL ) { \
    FlsConfig->FlsJobErrorNotification(); \
  }

/**@req SWS_Fls_00261 */
#define VALIDATE_RV(_exp,_api,_err,_rv) \
        if( !(_exp) ) { \
          (void)Det_ReportError(FLS_MODULE_ID,0,_api,_err); \
          return _rv; \
        }

#define VALIDATE(_exp,_api,_err ) \
        VALIDATE_RV(_exp,_api,_err, (E_NOT_OK))

#define VALIDATE_NO_RV(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(FLS_MODULE_ID,0,_api,_err); \
          return; \
        }

#define DET_REPORTERROR(_x,_y,_z,_q) Det_ReportError(_x, _y, _z, _q)
#else
#define FEE_JOB_END_NOTIFICATION()
#define FEE_JOB_ERROR_NOTIFICATION()
#define VALIDATE_RV(_exp,_api,_err,rv )
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_NO_RV(_exp,_api,_err )
#define DET_REPORTERROR(_x,_y,_z,_q)
#endif

#if defined(USE_DEM)
/**@req SWS_Fls_00260 */
#define VALIDATE_DEM(_exp,_err,_rv) \
        if( !(_exp) ) { \
          Dem_ReportErrorStatus(_err, DEM_EVENT_STATUS_FAILED); \
          return _rv; \
        }
#define VALIDATE_DEM_NO_RV(_exp,_err) \
        if( !(_exp) ) { \
          Dem_ReportErrorStatus(_err, DEM_EVENT_STATUS_FAILED); \
        }
#else
#define VALIDATE_DEM_NO_RV(_exp,_err)
#define VALIDATE_DEM(_exp,_err,_rv )
#endif

/* ----------------------------[private define]------------------------------*/

#define FLS_SRCADDR_MIN 		0
#define FLS_SRCADDR_MAX 		(FLS_TOTAL_SIZE - 1)
#define FLS_LEN_MIN				1
#define FLS_LEN_MAX(_addr)		(FLS_TOTAL_SIZE - _addr)
#define ADDRESS_BETWEEN(_addr, _lower, _upper) (((uint32)_addr >= _lower) && ((uint32)_addr <= _upper))

#define FLS_MEMCPY      (void)memcpy

/* ----------------------------[private typedef]-----------------------------*/

const Fls_ConfigType* FlsConfig;

MemIf_StatusType moduleStatus = MEMIF_UNINIT;
/*lint -esym( 843, mode) mode cannot be made constant as it has to be written by Fls_SetMode*/
MemIf_ModeType mode = MEMIF_MODE_SLOW;
MemIf_JobResultType flsJobResult;
Fls_Arc_JobType pendingJob;

Fls_AddressType jobAddress;
Fls_LengthType jobLength;
const uint8* jobPtr;
Fls_AddressType count;

Fls_AddressType queueAddress;
Fls_LengthType queueLength;

/* ----------------------------[private function prototypes]-----------------*/

static Std_ReturnType sectorAligned(uint32 SourceAddress);
static void eraseFail(void);
static void writeFail(void);
static void readFail(void);
static uint8 flsReadBatchJob(void);
static uint8 flsWriteBatchJob(void);
static uint8 readModeSelection(uint32 byteCount);

/* ----------------------------[private functions]---------------------------*/
/**
 * Passing Internal variables for debugging
 */
/** @req SWS_Fls_00302 */
void Fls_Arc_Internal(MemIf_StatusType *modstat, MemIf_ModeType *moduleMode,
        MemIf_JobResultType *jobResult, Fls_Arc_JobType *jobPending,
        Fls_AddressType *jobAddr, Fls_LengthType *jobLen,
        const uint8** jobPointer) {
    *modstat = moduleStatus;
    *moduleMode = mode;
    *jobResult = flsJobResult;
    *jobPending = pendingJob;
    *jobAddr = jobAddress;
    *jobLen = jobLength;
    *jobPointer = jobPtr;
}
/**
 * Erase Failure
 */
/** @req SWS_Fls_00104 */
static void eraseFail(void) {
    flsJobResult = MEMIF_JOB_FAILED;
    pendingJob = FLS_JOB_NONE;
    moduleStatus = MEMIF_IDLE;
#if defined(USE_DEM)
    /** @req SWS_Fls_00317 */
    Dem_ReportErrorStatus(DemConf_DemEventParameter_FLS_E_ERASE_FAILED, DEM_EVENT_STATUS_FAILED);
#endif
    /** @req SWS_Fls_00347 */
    FEE_JOB_ERROR_NOTIFICATION();
}
/**
 * Write Failure
 */
/** @req SWS_Fls_00105 */
static void writeFail(void) {
    flsJobResult = MEMIF_JOB_FAILED;
    pendingJob = FLS_JOB_NONE;
    moduleStatus = MEMIF_IDLE;
#if defined(USE_DEM)
    /** @req SWS_Fls_00316 */
    Dem_ReportErrorStatus(DemConf_DemEventParameter_FLS_E_WRITE_FAILED, DEM_EVENT_STATUS_FAILED);
#endif
    /** @req SWS_Fls_00347 */
    FEE_JOB_ERROR_NOTIFICATION();
}

/**
 * Read Failure
 */
/** @req SWS_Fls_00106 */
static void readFail(void) {
    flsJobResult = MEMIF_JOB_FAILED;
    pendingJob = FLS_JOB_NONE;
    moduleStatus = MEMIF_IDLE;
#if defined(USE_DEM)
    /** @req SWS_Fls_00315 */
    Dem_ReportErrorStatus(DemConf_DemEventParameter_FLS_E_READ_FAILED, DEM_EVENT_STATUS_FAILED);
#endif
    /** @req SWS_Fls_00347 */
    FEE_JOB_ERROR_NOTIFICATION();
}

/**
 *
 * @param SourceAddress
 * @return
 */
static Std_ReturnType sectorAligned(uint32 SourceAddress) {
    Std_ReturnType rv = E_NOT_OK;

    /* In range of bank */
    if (SourceAddress <= FLS_TOTAL_SIZE) {
        for (uint32 page = 0; page <= FLASH_NUM_PAGES; page++) {
            if (SourceAddress == (page * FLASH_PAGE_SIZE)) {
                rv = E_OK;
                break;
            }
        }
    }
    return rv;
}

/**
 * Read operation
 * @return Error value
 */
static uint8 flsReadBatchJob(void) {
    uint8 err = E_OK;
    if (jobLength != 0) {
        if (jobLength >= FLASH_PAGE_SIZE) {
            //reading a page
            err = readModeSelection(FLASH_PAGE_SIZE);
            /*lint -e{920, 9005} STANDARD INTERFACE */
            FLS_MEMCPY((void *) &jobPtr[(count * FLASH_PAGE_SIZE)],
                    &FlsConfig->QspiIf_Arc_ReadBuffer[HEADER_SIZE],
                    FLASH_PAGE_SIZE);

            jobLength = (jobLength) - (FLASH_PAGE_SIZE);
            jobAddress = jobAddress + (FLASH_PAGE_SIZE);
        }
        else {

            err = readModeSelection(jobLength);
            /*lint -e{920, 9005} STANDARD INTERFACE */
            FLS_MEMCPY((void *) &jobPtr[(count * FLASH_PAGE_SIZE)],
                    &FlsConfig->QspiIf_Arc_ReadBuffer[HEADER_SIZE], (size_t)jobLength);

            jobLength = 0u;
        }
        count = count + 1u;
    }
    return err;
}
/**
 * Write operation
 * @return error value
 */
static uint8 flsWriteBatchJob(void) {
    uint8 err = E_OK;
    if (jobLength != 0) {
        if (jobLength >= FLASH_PAGE_SIZE) {
            //Sending a page
            /** @req SWS_Fls_146  */
            /*lint -e{920} STANDARD INTERFACE */
            FLS_MEMCPY(&FlsConfig->QspiIf_Arc_WriteBuffer[HEADER_SIZE],
                    &jobPtr[(count * FLASH_PAGE_SIZE)], FLASH_PAGE_SIZE);
            if (FlsConfig->QspiIf_Arc_Write(jobAddress, FLASH_PAGE_SIZE) != E_OK) {
                err = E_NOT_OK;
            }
            jobLength = (jobLength) - (FLASH_PAGE_SIZE);
            jobAddress = jobAddress + (FLASH_PAGE_SIZE);
        }
        else {
            /** @req SWS_Fls_146  */
            /*lint -e{920} STANDARD INTERFACE */
            FLS_MEMCPY(&FlsConfig->QspiIf_Arc_WriteBuffer[HEADER_SIZE],
                    &jobPtr[(count * FLASH_PAGE_SIZE)], (size_t)jobLength);
            if (FlsConfig->QspiIf_Arc_Write(jobAddress, jobLength) != E_OK) {
                err = E_NOT_OK;
            }
            jobLength = 0u;
        }
        count = count + 1u;
    }
    return err;
}
/**
 * Mode selection for the read operation
 * @param byteCount
 * @return
 */
static uint8 readModeSelection(uint32 byteCount) {
    if (mode == MEMIF_MODE_SLOW) {
        if (FlsConfig->QspiIf_Arc_Read(jobAddress, byteCount) != E_OK) {
            return E_NOT_OK ;
        }
    }
    else {
        if (FlsConfig->QspiIf_Arc_Fast_Read(jobAddress, byteCount) != E_OK) {
            return E_NOT_OK ;
        }
    }
    return E_OK ;
}

/* ----------------------------[public functions]----------------------------*/

/**
 *
 * @param ConfigPtr
 */
void Fls_Init(const Fls_ConfigType* ConfigPtr) {
    /** @req SWS_Fls_00014 */
    /** @req SWS_Fls_00086 */
    /** !req SWS_Fls_00048 */
    /** @req SWS_Fls_00015 */
    /** @req SWS_Fls_00310 */
    VALIDATE_NO_RV(ConfigPtr != NULL, FLS_INIT_ID, FLS_E_PARAM_CONFIG);
    VALIDATE_NO_RV(ConfigPtr->QspiIf_Arc_Init != NULL, FLS_INIT_ID,
            FLS_E_PARAM_CONFIG);
    VALIDATE_NO_RV(ConfigPtr->QspiIf_Arc_Erase != NULL, FLS_INIT_ID,
            FLS_E_PARAM_CONFIG);
    VALIDATE_NO_RV(ConfigPtr->QspiIf_Arc_Write != NULL, FLS_INIT_ID,
            FLS_E_PARAM_CONFIG);
    VALIDATE_NO_RV(ConfigPtr->QspiIf_Arc_Read != NULL, FLS_INIT_ID,
            FLS_E_PARAM_CONFIG);
    VALIDATE_NO_RV(ConfigPtr->QspiIf_Arc_Fast_Read != NULL, FLS_INIT_ID,
            FLS_E_PARAM_CONFIG);
    VALIDATE_NO_RV(ConfigPtr->QspiIf_Arc_ReadBuffer != NULL, FLS_INIT_ID,
            FLS_E_PARAM_CONFIG);
    VALIDATE_NO_RV(ConfigPtr->QspiIf_Arc_WriteBuffer != NULL, FLS_INIT_ID,
            FLS_E_PARAM_CONFIG);
    VALIDATE_NO_RV(ConfigPtr->FlsInfo != NULL, FLS_INIT_ID, FLS_E_PARAM_CONFIG);

    /** @req SWS_Fls_00268 */
    /** @req SWS_Fls_00312 */
    VALIDATE_NO_RV(moduleStatus != MEMIF_BUSY, FLS_INIT_ID, FLS_E_BUSY);

    /** @req SWS_Fls_00191 */
    FlsConfig = ConfigPtr;

    FlsConfig->QspiIf_Arc_Init();

    /** @req SWS_Fls_00323 */
    moduleStatus = MEMIF_IDLE;
    /** @req SWS_Fls_00324 */
    flsJobResult = MEMIF_JOB_OK;
}

/**
 * Read from flash memory
 *
 * @param SourceAddress
 * @param TargetAddressPtr
 * @param Length
 * @return
 */
/*lint -save -e{818} TargetAddressPtr cannot be made constant as it is not defined in AUTOSAR 4.1.2*/
Std_ReturnType Fls_Read(Fls_AddressType SourceAddress, uint8* TargetAddressPtr,
        Fls_LengthType Length) {
    /** @req SWS_Fls_00236 */
    /** @req SWS_Fls_00239 */

    /** @req SWS_Fls_00099 */
    /** @req SWS_Fls_00240 */
    /** @req SWS_Fls_00311 */
    VALIDATE_RV((moduleStatus != MEMIF_UNINIT), FLS_READ_ID, FLS_E_UNINIT,
            E_NOT_OK);
    /** @req SWS_Fls_00100 */
    /** @req SWS_Fls_00312 */
    VALIDATE_RV((moduleStatus != MEMIF_BUSY), FLS_READ_ID, FLS_E_BUSY, E_NOT_OK);
    /** @req SWS_Fls_00158 */
    /** @req SWS_Fls_00310 */
    VALIDATE_RV((NULL != TargetAddressPtr), FLS_READ_ID, FLS_E_PARAM_DATA,
            E_NOT_OK);
    /** @req SWS_Fls_00097  */
    /** @req SWS_Fls_00310  */
    VALIDATE_RV((SourceAddress <= FLS_SRCADDR_MAX), FLS_READ_ID,
            FLS_E_PARAM_ADDRESS, E_NOT_OK);
    /** @req SWS_Fls_00098  */
    /** @req SWS_Fls_00310  */
    VALIDATE_RV(
            (Length > 0) && (ADDRESS_BETWEEN(Length, FLS_LEN_MIN, FLS_LEN_MAX(SourceAddress))),
            FLS_READ_ID, FLS_E_PARAM_LENGTH, E_NOT_OK);

    /** @req SWS_Fls_00337 */
    jobAddress = SourceAddress;
    jobPtr = TargetAddressPtr;
    //Autosar Fls_Read API has Length parameter defined as number of bytes to read
    //F021 Flash API has parameter u32Length defined as the length to read in 32-bit words
    jobLength = Length;
    count = 0;

    /** @req SWS_Fls_00339 */
    flsJobResult = MEMIF_JOB_PENDING;
    /** @req SWS_Fls_00338 */
    moduleStatus = MEMIF_BUSY;
    pendingJob = FLS_JOB_READ;

    /** @req SWS_Fls_00340 */
    return E_OK ;
}

/**
 * Programs flash sectors
 *
 * @param TargetAddress
 * @param SourceAddressPtr
 * @param Length
 * @return
 */
Std_ReturnType Fls_Write(Fls_AddressType TargetAddress,
        const uint8* SourceAddressPtr, Fls_LengthType Length) {
    /** @req SWS_Fls_00223 */
    /** @req SWS_Fls_00226 */

    /** @req SWS_Fls_00066 */
    /** @req SWS_Fls_00311 */
    VALIDATE_RV((moduleStatus != MEMIF_UNINIT), FLS_WRITE_ID, FLS_E_UNINIT,
            E_NOT_OK);
    /** @req SWS_Fls_00030 */
    /** @req SWS_Fls_00312 */
    VALIDATE_RV((moduleStatus != MEMIF_BUSY), FLS_WRITE_ID, FLS_E_BUSY,
            E_NOT_OK);
    /** @req SWS_Fls_00157 */
    /** @req SWS_Fls_00310 */
    VALIDATE_RV((SourceAddressPtr != NULL), FLS_WRITE_ID, FLS_E_PARAM_DATA,
            E_NOT_OK);
    /** @req SWS_Fls_00026 */
    /** @req SWS_Fls_00310 */
    VALIDATE_RV(
            ( E_OK == sectorAligned( TargetAddress )) && (TargetAddress <= FLS_SRCADDR_MAX),
            FLS_WRITE_ID, FLS_E_PARAM_ADDRESS, E_NOT_OK);
    /** @req SWS_Fls_00027 */
    /** @req SWS_Fls_00310 */
    VALIDATE_RV(
            (ADDRESS_BETWEEN(Length, FLS_LEN_MIN, FLS_LEN_MAX(TargetAddress)))
            && (E_OK == sectorAligned((uint32)TargetAddress + (uint32)Length)),
            FLS_WRITE_ID, FLS_E_PARAM_LENGTH, E_NOT_OK);

    /** @req SWS_Fls_331 */
    jobAddress = TargetAddress;
    jobLength = Length;
    jobPtr = SourceAddressPtr;
    count = 0;

    /** @req SWS_Fls_332  */
    moduleStatus = MEMIF_BUSY;
    /** @req SWS_Fls_333 */
    flsJobResult = MEMIF_JOB_PENDING;
    pendingJob = FLS_JOB_WRITE;

    /** @req SWS_Fls_00225 */
    /** @req SWS_Fls_00146 */
    uint8 opError = flsWriteBatchJob();

    if (opError == E_NOT_OK) {
        writeFail();
    }
    else {
        /* Do nothing, wait for next loop */
    }

    /** @req SWS_Fls_334 */
    return E_OK ;
}
/**
 * Erase flash sectors
 *
 * @param TargetAddress Always from 0 to FLS_TOTAL_SIZE
 * @param Length
 * @return
 */
Std_ReturnType Fls_Erase(Fls_AddressType TargetAddress, Fls_LengthType Length) {

    /** @req SWS_Fls_00218  */
    /** @req SWS_Fls_00327 */

    /** @req SWS_Fls_00065 */
    /** @req SWS_Fls_00311 */
    VALIDATE_RV((moduleStatus != MEMIF_UNINIT), FLS_ERASE_ID, FLS_E_UNINIT,
            E_NOT_OK);
    /** @req SWS_Fls_00023 */
    /** @req SWS_Fls_00312 */
    VALIDATE_RV((moduleStatus != MEMIF_BUSY), FLS_ERASE_ID, FLS_E_BUSY,
            E_NOT_OK);
    /** @req SWS_Fls_00020 */
    /** @req SWS_Fls_00310  */
    VALIDATE_RV(E_OK == sectorAligned( TargetAddress ), FLS_ERASE_ID,
            FLS_E_PARAM_ADDRESS, E_NOT_OK);
    /** @req SWS_Fls_00021  */
    /** @req SWS_Fls_00310  */
    VALIDATE_RV(
            (ADDRESS_BETWEEN(Length, FLS_LEN_MIN, FLS_LEN_MAX(TargetAddress)))
            && (E_OK == sectorAligned((uint32)TargetAddress + (uint32)Length)),
            FLS_ERASE_ID, FLS_E_PARAM_LENGTH, E_NOT_OK);

    jobAddress = TargetAddress;
    jobLength = Length;

    /** @req SWS_Fls_00328 */
    moduleStatus = MEMIF_BUSY;
    /** @req SWS_Fls_00329 */
    flsJobResult = MEMIF_JOB_PENDING;
    pendingJob = FLS_JOB_ERASE;

    /** @req SWS_Fls_00221 */
    /** @req SWS_Fls_00220 */
    if (FlsConfig->QspiIf_Arc_Erase(jobAddress, jobLength) != E_OK) {
        eraseFail();
        return E_NOT_OK ;
    }

    /** @req SWS_Fls_00330 */
    return E_OK ;
}

/** @req SWS_Fls_00186 */
#if ( FLS_COMPARE_API == STD_ON )
/**
 * Comparing memory location to flash
 *
 * @param SourceAddress
 * @param TargetAddressPtr
 * @param Length
 * @return
 */
Std_ReturnType Fls_Compare(Fls_AddressType SourceAddress,
        const uint8* TargetAddressPtr, Fls_LengthType Length) {
    /** @req SWS_Fls_00241 */
    /** @req SWS_Fls_00186 */

    /** @req SWS_Fls_00152 */
    /** @req SWS_Fls_00311 */
    VALIDATE_RV((moduleStatus != MEMIF_UNINIT), FLS_COMPARE_ID, FLS_E_UNINIT,
            E_NOT_OK);
    /** @req SWS_Fls_00153 */
    /** @req SWS_Fls_00312 */
    VALIDATE_RV((moduleStatus != MEMIF_BUSY), FLS_COMPARE_ID, FLS_E_BUSY,
            E_NOT_OK);
    /** @req SWS_Fls_00273 */
    /** @req SWS_Fls_00310 */
    VALIDATE_RV((TargetAddressPtr != NULL), FLS_COMPARE_ID, FLS_E_PARAM_DATA,
            E_NOT_OK);
    /** @req SWS_Fls_00150 */
    /** @req SWS_Fls_00310 */
    VALIDATE_RV((SourceAddress <= FLS_SRCADDR_MAX), FLS_COMPARE_ID,
            FLS_E_PARAM_ADDRESS, E_NOT_OK);
    /** @req SWS_Fls_00151 */
    /** @req SWS_Fls_00310 */
    VALIDATE_RV(
            (Length != 0uL) && (ADDRESS_BETWEEN(Length, FLS_LEN_MIN, FLS_LEN_MAX(SourceAddress))),
            FLS_COMPARE_ID, FLS_E_PARAM_LENGTH, E_NOT_OK);

    /** @req SWS_Fls_00341 */
    jobAddress = SourceAddress;
    jobLength = Length;
    jobPtr = TargetAddressPtr;
    count = 0;

    /** @req SWS_Fls_00343 */
    flsJobResult = MEMIF_JOB_PENDING;
    /** @req SWS_Fls_00342 */
    moduleStatus = MEMIF_BUSY;
    pendingJob = FLS_JOB_COMPARE;

    /** @req SWS_Fls_00344 */
    return E_OK ;
}
#endif

/**
 * Main function to be called cyclically to complete jobs
 */
void Fls_MainFunction(void) {
    sint32 result = 0u;
    uint8 opError = E_OK;
    /** @req SWS_Fls_00037 */
    /** @req SWS_Fls_00038 */
    /** @req SWS_Fls_00117 */
    /** @req SWS_Fls_00311 */
    VALIDATE_NO_RV(moduleStatus != MEMIF_UNINIT, FLS_MAIN_FUNCTION_ID,
            FLS_E_UNINIT);
    /** @req SWS_Fls_00039 */
    if (flsJobResult == MEMIF_JOB_PENDING) {
        /** @req SWS_Fls_00040 */
        switch (pendingJob) {
            case FLS_JOB_COMPARE:
            {
                /** @req SWS_Fls_00154 */
                /** @req SWS_Fls_00244 */
                /** @req SWS_Fls_00243 */
                if (jobLength != 0) {
                    if (jobLength >= FLASH_PAGE_SIZE) {
                        //reading a page
                        opError = readModeSelection(FLASH_PAGE_SIZE);

                        result = (sint32)memcmp(
                                &FlsConfig->QspiIf_Arc_ReadBuffer[HEADER_SIZE],
                                &jobPtr[(count * FLASH_PAGE_SIZE)],
                                FLASH_PAGE_SIZE);

                        jobLength = (jobLength) - (FLASH_PAGE_SIZE);
                        jobAddress = jobAddress + (FLASH_PAGE_SIZE);
                    }
                    else {
                        opError = readModeSelection(jobLength);
                        result = (sint32)memcmp(
                                &FlsConfig->QspiIf_Arc_ReadBuffer[HEADER_SIZE],
                                &jobPtr[(count * FLASH_PAGE_SIZE)], (size_t)jobLength);

                        jobLength = 0u;
                    }
                    count = count + 1u;
                }
                if (opError == E_NOT_OK) {
                    readFail();
#if defined(USE_DEM)
                    /** @req SWS_Fls_00318 */
                    Dem_ReportErrorStatus(DemConf_DemEventParameter_FLS_E_COMPARE_FAILED, DEM_EVENT_STATUS_FAILED);
#endif
                }
                else {
                    if (0u == jobLength) {
                        if ((result == 0)
                                && (flsJobResult == MEMIF_JOB_PENDING)) {
                            /** @req SWS_Fls_00345 */
                            flsJobResult = MEMIF_JOB_OK;
                        }
                        else {
                            /** @req SWS_Fls_00200 */
                            flsJobResult = MEMIF_BLOCK_INCONSISTENT;
                            /** @req SWS_Fls_00349 */
                            FEE_JOB_ERROR_NOTIFICATION();
#if defined(USE_DEM)
                            /** @req SWS_Fls_00318 */
                            Dem_ReportErrorStatus(DemConf_DemEventParameter_FLS_E_COMPARE_FAILED, DEM_EVENT_STATUS_FAILED);
#endif
                        }
                        /** @req SWS_Fls_00346 */
                        moduleStatus = MEMIF_IDLE;
                        pendingJob = FLS_JOB_NONE;
                        /** @req SWS_Fls_00167 */
                        FEE_JOB_END_NOTIFICATION();
                    }
                    else {
                        /* Do nothing, wait for next loop */
                    }
                }
                break;
            }
            case FLS_JOB_ERASE:
            {
                if (flsJobResult == MEMIF_JOB_PENDING) {
                    /** @req SWS_Fls_00345 */
                    flsJobResult = MEMIF_JOB_OK;
                }
                /** @req SWS_Fls_00346 */
                pendingJob = FLS_JOB_NONE;
                moduleStatus = MEMIF_IDLE;
                /** @req SWS_Fls_00167 */
                FEE_JOB_END_NOTIFICATION();
                break;
            }
            case FLS_JOB_READ:
            {
                /** @req SWS_Fls_00238 */
                /** @req SWS_Fls_00239 */

                opError = flsReadBatchJob();

                if (opError == E_NOT_OK) {
                    readFail();
                }
                else {
                    if ((0u == jobLength)
                            && (flsJobResult == MEMIF_JOB_PENDING)) {
                        /** @req SWS_Fls_00345 */
                        flsJobResult = MEMIF_JOB_OK;
                        /** @req SWS_Fls_00346 */
                        moduleStatus = MEMIF_IDLE;
                        pendingJob = FLS_JOB_NONE;
                        /** @req SWS_Fls_00167 */
                        FEE_JOB_END_NOTIFICATION();
                    }
                    else {
                        /* Do nothing, wait for next loop */
                    }
                }
                break;
            }
            case FLS_JOB_WRITE:
            {
                /** @req SWS_Fls_00225 */
                opError = flsWriteBatchJob();

                if (opError == E_NOT_OK) {
                    writeFail();
                }
                else {
                    if ((0u == jobLength)
                            && (flsJobResult == MEMIF_JOB_PENDING)) {
                        /** @req SWS_Fls_00345 */
                        flsJobResult = MEMIF_JOB_OK;
                        /** @req SWS_Fls_00346 */
                        moduleStatus = MEMIF_IDLE;
                        pendingJob = FLS_JOB_NONE;
                        /** @req SWS_Fls_00167 */
                        FEE_JOB_END_NOTIFICATION();
                    }
                    else {
                        /* Do nothing, wait for next loop */
                    }
                }
                break;
            }
            case FLS_JOB_NONE:
                break;

            default:
                break;
        }
    } /* if */
}

#if (STD_ON == FLS_CANCEL_API)
void Fls_Cancel(void) {
    //Not supported
}
#endif

#if ( FLS_SET_MODE_API == STD_ON )
void Fls_SetMode(MemIf_ModeType Mode) {
    /** @req SWS_Fls_00311 */
    VALIDATE_NO_RV((moduleStatus != MEMIF_UNINIT), FLS_SET_MODE_ID,
            FLS_E_UNINIT);
    /** @req SWS_Fls_00156 */
    /** @req SWS_Fls_00312 */
    VALIDATE_NO_RV((moduleStatus != MEMIF_BUSY), FLS_SET_MODE_ID, FLS_E_BUSY);

    VALIDATE_NO_RV(((Mode == MEMIF_MODE_SLOW) || (Mode == MEMIF_MODE_SLOW)),
            FLS_SET_MODE_ID, FLS_E_PARAM_POINTER);

    /** @req SWS_Fls_00155 */
    mode = Mode;
}
#endif

#if ( FLS_VERSION_INFO_API == STD_ON )
void Fls_GetVersionInfo(Std_VersionInfoType *VersioninfoPtr) {
    /** @req SWS_Fls_00363 */
    VALIDATE_NO_RV(( NULL != VersioninfoPtr ), FLS_GET_VERSION_INFO_ID,
            FLS_E_PARAM_POINTER);

    VersioninfoPtr->vendorID = FLS_VENDOR_ID;
    VersioninfoPtr->moduleID = FLS_MODULE_ID;
    VersioninfoPtr->sw_major_version = FLS_SW_MAJOR_VERSION;
    VersioninfoPtr->sw_minor_version = FLS_SW_MINOR_VERSION;
    VersioninfoPtr->sw_patch_version = FLS_SW_PATCH_VERSION;

}
#endif

/** @req SWS_Fls_00184 */
#if (STD_ON == FLS_GET_STATUS_API)
MemIf_StatusType Fls_GetStatus(void) {
    // No validation needed, this may be called before initialization
    /** @req SWS_Fls_00034 */
    return moduleStatus;
}
#endif

/** @req SWS_Fls_00185 */
#if (STD_ON == FLS_GET_JOB_RESULT_API)
MemIf_JobResultType Fls_GetJobResult(void) {
    /** @req Sws_Fls_00358 */
    /** @req SWS_Fls_00311 */
    VALIDATE_RV((moduleStatus != MEMIF_UNINIT), FLS_GET_JOB_RESULT_ID,
            FLS_E_UNINIT, MEMIF_JOB_FAILED);
    /** @req SWS_Fls_00035 */
    /** @req SWS_Fls_00036 */
    return flsJobResult;
}
#endif
