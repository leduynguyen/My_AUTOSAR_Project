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

/** @tagSettings DEFAULT_ARCHITECTURE=PPC|MPC5748G|MPC5645S|MPC5607B */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/* ----------------------------[information]----------------------------------*/
/*
 * Description:
 *   Implements the Fls module (flash driver)
 *
 * Support:
 *   General                  Have Support
 *   -------------------------------------------
 *   FLS_AC_LOAD_ON_JOB_START    Y
 *   FLS_BASE_ADDRESS            Y, taken from FlashInfo
 *   FLS_CANCEL_API              N
 *   FLS_COMPARE_API             Y
 *   FLS_DEV_ERROR_DETECT        Y
 *   FLS_GET_JOB_RESULT_API      Y
 *   FLS_GET_STATUS_API          Y
 *   FLS_SET_MODE_API            Y
 *   FLS_TOTAL_SIZE              Y, taken from FlashInfo
 *   FLS_USE_INTERRUPTS          N, no hardware support
 *   FLS_VERSION_INFO_API        Y
 *
 *   FlsConfigSet             Have Support
 *   -------------------------------------------
 *   FLS_AC_ERASE                N
 *   FLS_AC_WRITE                N
 *   FLS_CALL_CYCLE              N
 *   FLS_JOB_END_NOTIFICATION    Y
 *   FLS_JOB_ERROR_NOTIFICATION  Y
 *   FLS_MAX_READ_FAST_MODE      N
 *   FLS_MAX_READ_NORMAL_MODE    N
 *   FLS_MAX_WRITE_FAST_MODE     N
 *   FLS_MAX_WRITE_NORMAL_MODE   N
 *   FLS_PROTECTION              N
 *
 *
 *   Device
 *   - MPC5668  , No support for shadow flash
 *   - MPC5606S , Support for dataflash only
 *
 * Implementation Notes:
 *   Affected files:
 *   - Fls.c
 *   - Fls_Cfg.c/.h
 *   - flash_h7f_c90.c     middle level driver
 *   - flash_ll_h7f_c90.c  low level driver
 *   - flash.h             interface for flash_xxx
 *
 *
 * Things left:
 *   - Virtual addresses, FLS209 is not done (code assumes FLS_BASE_ADDRESS is 0)
 *
 *
 */
/** @req SWS_Fls_00001 *//*The FLS module shall offer asynchronous services for operations on flash memory (read/erase/write).*/
/** @req SWS_Fls_00002 *//*The FLS module shall not buffer data. The FLS module shall use application data buffers that are referenced by a pointer passed via the API.*/
/** @req SWS_Fls_00003 *//*The FLS module shall not ensure data consistency of the given application buffer*/
/** @req SWS_Fls_00206 *//*The FLS module shall validate the version information in the FLS module header and source files for consistency (e.g. by comparing the version information in the module header and source files with a pre-processor macro).*/

/* ----------------------------[requirements]--------------------------------*/

/* FlsGeneral */
/* Partially supported */

/* FlsConfigSet */
/** Only ECUC_Fls_00273 ECUC_Fls_00274 ECUC_Fls_00277 ECUC_Fls_00278 are supported */
/* ECUC_Fls_00279  N/A in core */

/* FlsPublishedInformation not supported*/
/* FlsSectorList and FlsSector not supported in core since we use own format */

/* ----------------------------[includes]------------------------------------*/

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "arc_assert.h"
#include <string.h>
/* @req SWS_Fls_00107 */
#include "Fls.h"
#include "flash.h"
#include "arc.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#include "Cpu.h"
#include "mpc55xx.h"
#include "Mcu.h"
#if (FLS_BASE_ADDRESS != 0)
#error Virtual addresses not supported
#endif

/*lint -save -e635 Want to reset types of Fls_AddressType */
/*lint -parent(Fls_AddressType, Fls_LengthType) */
/*lint -restore */

/* ----------------------------[private define]------------------------------*/

/* Add ramlog prints at each read/write/erase */
//#define CFG_FLS_DEBUG
#if defined(CFG_FLS_DEBUG)
#include "Ramlog.h"
#define LOG_HEX1(_str,_arg1) \
    ramlog_str(_str);ramlog_hex(_arg1);ramlog_str("\n")

#define LOG_HEX2(_str,_arg1,_str2,_arg2) \
    ramlog_str(_str);ramlog_hex(_arg1);ramlog_str(_str2);ramlog_hex(_arg2);ramlog_str("\n")

#define LOG_STR(_str)   ramlog_str(_str)
#else
#define LOG_HEX1(_str,_arg1)
#define LOG_HEX2(_str,_arg1,_str2,_arg2)
#define LOG_STR(_str)
#endif

/* ----------------------------[private macro]-------------------------------*/

#if ( FLS_DEV_ERROR_DETECT == STD_ON )
/* @req SWS_Fls_00261 */

#define DET_REPORTERROR(_x,_y,_z,_q) (void)Det_ReportError(FLS_MODULE_ID, _y, _z, _q)

#define FEE_JOB_END_NOTIFICATION() \
  if( Fls_Global.config->FlsJobEndNotification != NULL ) { \
    /* @req SWS_Fls_00167 */ \
    Fls_Global.config->FlsJobEndNotification(); \
  }

#define FEE_JOB_ERROR_NOTIFICATION() \
  if( Fls_Global.config->FlsJobErrorNotification != NULL ) { \
    /* @req SWS_Fls_00347 */ \
    Fls_Global.config->FlsJobErrorNotification(); \
  }

#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(FLS_MODULE_ID,0,_api,_err); \
          return E_NOT_OK; \
        }

#define VALIDATE_NO_RV(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(FLS_MODULE_ID,0,_api,_err); \
          return; \
        }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(FLS_MODULE_ID,0,_api,_err); \
          return (_rv); \
        }

#else
#define DET_REPORTERROR(_x,_y,_z,_q)
#define FEE_JOB_END_NOTIFICATION()
#define FEE_JOB_ERROR_NOTIFICATION()
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_NO_RV(_exp,_api,_err )
#define VALIDATE_W_RV(_exp,_api,_err,_rv )
#define DET_REPORTERROR(_x,_y,_z,_q)
#endif

/* ----------------------------[private typedef]-----------------------------*/
/* @req SWS_Fls_00308 */

typedef enum {
    FLS_JOB_NONE, FLS_JOB_COMPARE, FLS_JOB_ERASE, FLS_JOB_READ, FLS_JOB_WRITE,
} Fls_Arc_JobType;

typedef struct {
    uint32 dest;
    uint32 source;
    uint32 left;
    uint32 pDest;
    uint32 pLeft;
    uint32 chunkSize;
} Fls_ProgInfoType;

typedef struct {
    const Fls_ConfigType*   config;
    MemIf_StatusType        status;
    MemIf_JobResultType     jobResultType;
    Fls_Arc_JobType         jobType;
    Fls_AddressType         flashAddr;   //sourceAddr /* @req SWS_Fls_00217 */
    uint8 *                 ramAddr;    // targetAddr
    Fls_LengthType          length;
    Fls_ProgInfoType        flashWriteInfo;
    MemIf_ModeType          mode;
    uint32                  readChunkSize;
} Fls_GlobalType;

Fls_GlobalType Fls_Global = {
    .config = NULL,
    .status = MEMIF_UNINIT,
    .jobResultType = MEMIF_JOB_OK,
    .jobType = FLS_JOB_NONE,
    .flashAddr = 0uL,
    .ramAddr = NULL,
    .length = 0,
    .flashWriteInfo = {0u,0u,0u,0u,0u,0u},
    .mode = MEMIF_MODE_SLOW,
    .readChunkSize = 0
};

#define MAX_PROGRESS_CNTR (uint32)90000UL

/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/

static Std_ReturnType sectorAligned( Fls_AddressType SourceAddress ) {
    Std_ReturnType rv = E_NOT_OK;
    const FlashType *bPtr;

    for (uint32 bank = 0; bank < FLASH_BANK_CNT; bank++) {
        bPtr = &Fls_Global.config->FlsInfo[bank];
        /* @req SWS_Fls_00216 */
        /* In range of bank */
        if( (SourceAddress >= bPtr->sectAddr[0]) &&
            (SourceAddress <= (bPtr->sectAddr[bPtr->sectCnt])) )
        {
            for (uint32 sector = 0; sector < (bPtr->sectCnt + 1); sector++)
            {
                if( SourceAddress == bPtr->sectAddr[sector] ) {
                    rv = E_OK;
                    break;
                }
            }
            break;
        }
    }
    return rv;
}

#if defined(CFG_MPC5777M)||defined(CFG_MPC5748G)|| defined(CFG_MPC5746C) || defined(CFG_MPC5747C)
static Std_ReturnType checkValidChunk( Fls_AddressType StartAddress, Fls_AddressType EndAddress ) {
    Std_ReturnType ret = E_NOT_OK;
    const FlashType *bPtr;

    if( StartAddress <= EndAddress ) {
        for (uint32 bank = 0; bank < FLASH_BANK_CNT; bank++) {
            bPtr = &Fls_Global.config->FlsInfo[bank];
            uint32 bankStartAddr = bPtr->sectAddr[0];
            if( (StartAddress >= bankStartAddr) &&
                    (EndAddress < (bankStartAddr + bPtr->bankSize)) ) {
                /* Adresses are within bank. Check if there is an empty sector
                 * between the addresses. */
                ret = E_OK;
                uint32 sector = 0;
                boolean done = FALSE;
                while(!done && (sector < bPtr->sectCnt)) {
                    switch(bPtr->addrSpace[sector]) {
                        case SECTOR_EMPTY:
                            /* Empty sector */
                            if( (((bPtr->sectAddr[sector] <= StartAddress) && (bPtr->sectAddr[sector + 1] > StartAddress)) || /* Start address within the empty sector */
                                    ((bPtr->sectAddr[sector] <= EndAddress) && (bPtr->sectAddr[sector + 1] > EndAddress)) ) || /* End adress within the empty sector */
                                    ((StartAddress < bPtr->sectAddr[sector]) && (bPtr->sectAddr[sector + 1] < EndAddress)) ) {/* Chunk overlaps the complete empty sector */
                                ret = E_NOT_OK;
                                done = TRUE;
                            }
                            break;
                        default:
                            if( (bPtr->sectAddr[sector] <= StartAddress ) &&
                                    (bPtr->sectAddr[sector + 1] > EndAddress) ) {
                                /* Both adresses are within a non-empty dector */
                                ret = E_OK;
                                done = TRUE;
                            }
                            break;
                    }
                    sector++;
                }
                break;
            }
        }
    }
    return ret;
}
#endif

/**
 * Check all bank ranges for a valid address
 *
 * @param SourceAddress
 * @return
 */
static Std_ReturnType checkValidAddress( Fls_AddressType SourceAddress ) {
    Std_ReturnType rv = E_NOT_OK;
    const FlashType *bPtr;

    for (uint32 bank = 0; bank < FLASH_BANK_CNT; bank++) {
        bPtr = &Fls_Global.config->FlsInfo[bank];
        uint32 startAddr = bPtr->sectAddr[0];

        if( (SourceAddress >= startAddr) &&
            (SourceAddress < (startAddr + bPtr->bankSize)) )
        {
            rv = E_OK;
            break;
        }
    }
    return rv;
}

/* @req SWS_Fls_00104 */
static void eraseFail( void ) {
    Fls_Global.jobResultType = MEMIF_JOB_FAILED;
    Fls_Global.jobType = FLS_JOB_NONE;
    Fls_Global.status = MEMIF_IDLE;

/* @req SWS_Fls_00260 */
/* @req SWS_Fls_00315 */

#if defined(USE_DEM)
    Dem_ReportErrorStatus(DemConf_DemEventParameter_FLS_E_ERASE_FAILED, DEM_EVENT_STATUS_FAILED);
#endif
    FEE_JOB_ERROR_NOTIFICATION();
}

/* @req SWS_Fls_00105 */
static void writeFail( void ) {
    Fls_Global.jobResultType = MEMIF_JOB_FAILED;
    Fls_Global.jobType = FLS_JOB_NONE;
    Fls_Global.status = MEMIF_IDLE;
/* @req SWS_Fls_00260 */
/* @req SWS_Fls_00316 */

#if defined(USE_DEM)
    Dem_ReportErrorStatus(DemConf_DemEventParameter_FLS_E_WRITE_FAILED, DEM_EVENT_STATUS_FAILED);
#endif
    FEE_JOB_ERROR_NOTIFICATION();

}

/* @req SWS_Fls_00106 */
static void readFail( void ) {
    Fls_Global.jobResultType = MEMIF_BLOCK_INCONSISTENT;
    Fls_Global.jobType = FLS_JOB_NONE;
    Fls_Global.status = MEMIF_IDLE;
/* @req SWS_Fls_00260 */
/* @req SWS_Fls_00317 */
#if defined(USE_DEM)
    Dem_ReportErrorStatus(DemConf_DemEventParameter_FLS_E_READ_FAILED, DEM_EVENT_STATUS_FAILED);
#endif
    FEE_JOB_ERROR_NOTIFICATION();

}
/* ----------------------------[public functions]----------------------------*/

/**
 *
 * @param ConfigPtr
 */

void Fls_Init(const Fls_ConfigType *ConfigPtr) {
    /** @req SWS_Fls_00014 */
    /** @req SWS_Fls_00086 */
    /** @req SWS_Fls_00015 */
    /** !req SWS_Fls_00048 */
    /** !req SWS_Fls_00325 */
    /** !req SWS_Fls_00326 */
    /** @req SWS_Fls_00109 */
    /** @req SWS_Fls_00353 */
    /** @req SWS_Fls_00268 */
    /** @req SWS_Fls_00312 */
    /** @req SWS_Fls_00205 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_NO_RV(Fls_Global.status!=MEMIF_BUSY,FLS_INIT_ID, FLS_E_BUSY );
    VALIDATE_NO_RV((ConfigPtr != NULL), FLS_INIT_ID, FLS_E_PARAM_CONFIG);
    VALIDATE_NO_RV(ConfigPtr->FlsMaxReadFastMode != 0, FLS_INIT_ID, FLS_E_PARAM_CONFIG);
    VALIDATE_NO_RV(ConfigPtr->FlsMaxReadNormalMode != 0, FLS_INIT_ID, FLS_E_PARAM_CONFIG);
    VALIDATE_NO_RV(ConfigPtr->FlsMaxWriteFastMode != 0, FLS_INIT_ID, FLS_E_PARAM_CONFIG);
    VALIDATE_NO_RV(ConfigPtr->FlsMaxWriteNormalMode != 0, FLS_INIT_ID, FLS_E_PARAM_CONFIG);
    /*lint -restore*/

    Fls_Global.status = MEMIF_UNINIT;
    Fls_Global.jobResultType = MEMIF_JOB_PENDING;

    /** @req SWS_Fls_00191 */
    Fls_Global.config = ConfigPtr;

    Flash_Init();

    /** @req SWS_Fls_00323 */
    /** @req SWS_Fls_00324 */
    Fls_Global.status = MEMIF_IDLE;
    Fls_Global.jobResultType = MEMIF_JOB_OK;
    return;
}

/**
 * Erase flash sectors
 *
 * @param TargetAddress Always from 0 to FLS_TOTAL_SIZE
 * @param Length
 * @return
 */
Std_ReturnType Fls_Erase(Fls_AddressType TargetAddress, Fls_LengthType Length) {
#if FLS_BASE_ADDRESS > 0
    /* Avoid compiler warning */
    /** @req SWS_Fls_00221  */
    TargetAddress += FLS_BASE_ADDRESS;
#endif
    Std_ReturnType status;
    status = E_OK;
    /** @req SWS_Fls_00218  */
    /** @req SWS_Fls_00220 */
    /** @req SWS_Fls_00327 */
    /** @req SWS_Fls_00065 */
    /** @req SWS_Fls_00311 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_W_RV( Fls_Global.status != MEMIF_UNINIT, FLS_ERASE_ID, FLS_E_UNINIT, E_NOT_OK );
    /** @req SWS_Fls_00023 */
    /** @req SWS_Fls_00312 */
    VALIDATE_W_RV( Fls_Global.status != MEMIF_BUSY, FLS_ERASE_ID, FLS_E_BUSY, E_NOT_OK );
    /** @req SWS_Fls_00020 */
    VALIDATE_W_RV( E_OK == sectorAligned( TargetAddress ),
            FLS_ERASE_ID, FLS_E_PARAM_ADDRESS, E_NOT_OK );
    /** @req SWS_Fls_00021  */
    VALIDATE_W_RV( (Length != 0) && (E_OK == sectorAligned( TargetAddress + Length)),
            FLS_ERASE_ID, FLS_E_PARAM_LENGTH, E_NOT_OK );
#if defined(CFG_MPC5777M) || defined(CFG_MPC5748G)|| defined(CFG_MPC5746C) || defined(CFG_MPC5747C)
    VALIDATE_W_RV((E_OK == checkValidChunk(TargetAddress, TargetAddress + Length - 1)), FLS_ERASE_ID, FLS_E_INVALID_AREA, E_NOT_OK);
#endif
    /*lint -restore */
    Fls_Global.status = MEMIF_BUSY;				    /** @req SWS_Fls_00328 */
    Fls_Global.jobResultType = MEMIF_JOB_PENDING;   /** @req SWS_Fls_00329 */
    Fls_Global.jobType = FLS_JOB_ERASE;
    Fls_Global.flashAddr = TargetAddress;
    Fls_Global.length = Length;

    LOG_HEX2("Fls_Erase() ",TargetAddress," ", Length);

    /* Unlock */
    Flash_Lock(Fls_Global.config->FlsInfo,FLASH_OP_UNLOCK,TargetAddress, Length );

    /** @req SWS_Fls_00145 */
    if (EE_OK != Flash_Erase(Fls_Global.config->FlsInfo,TargetAddress, Length, NULL )) {
        status = E_NOT_OK;
    }
    return status;	/** @req SWS_Fls_00330 */
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
        const uint8 *SourceAddressPtr, Fls_LengthType Length) {
#if FLS_BASE_ADDRESS > 0
    /* Avoid compiler warning */
    TargetAddress += FLS_BASE_ADDRESS;
#endif
    Std_ReturnType status;
    status = E_OK;
    /** @req SWS_Fls_00223 */
    /** @req SWS_Fls_00225 */
    /** @req SWS_Fls_00226 */
    /** @req SWS_Fls_00311 */
    /** @req SWS_Fls_00066 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_W_RV(Fls_Global.status != MEMIF_UNINIT,FLS_WRITE_ID, FLS_E_UNINIT,E_NOT_OK );
    /** @req SWS_Fls_00030 */
    /** @req SWS_Fls_00312 */
    VALIDATE_W_RV(Fls_Global.status != MEMIF_BUSY,FLS_WRITE_ID, FLS_E_BUSY,E_NOT_OK );
    /** @req SWS_Fls_00157 */
    /** @req SWS_Fls_00310 */
    VALIDATE_W_RV(SourceAddressPtr != NULL,FLS_WRITE_ID, FLS_E_PARAM_DATA,E_NOT_OK );
    /** @req SWS_Fls_00026 */
    VALIDATE_W_RV( ((TargetAddress % FLASH_PAGE_SIZE) == 0) && (E_OK == checkValidAddress(TargetAddress)),
            FLS_WRITE_ID, FLS_E_PARAM_ADDRESS, E_NOT_OK );
    /** @req SWS_Fls_00027 */
    VALIDATE_W_RV( ((Length != 0) && ((((TargetAddress + Length) % FLASH_PAGE_SIZE) == 0) && (E_OK == checkValidAddress(TargetAddress + Length -1 )))),
            FLS_WRITE_ID, FLS_E_PARAM_LENGTH, E_NOT_OK );
#if defined(CFG_MPC5777M)|| defined(CFG_MPC5748G)|| defined(CFG_MPC5746C) || defined(CFG_MPC5747C)
    VALIDATE_W_RV((E_OK == checkValidChunk(TargetAddress, TargetAddress + Length - 1)), FLS_WRITE_ID, FLS_E_INVALID_AREA, E_NOT_OK);
#endif
    /*lint -restore*/
    // Destination is FLS_BASE_ADDRESS + TargetAddress
    /** @req SWS_Fls_333 */
    Fls_Global.jobResultType = MEMIF_JOB_PENDING;
    /** @req SWS_Fls_332  */
    Fls_Global.status = MEMIF_BUSY;
    Fls_Global.jobType = FLS_JOB_WRITE;

    // Fill in the required fields for programming...
    /** @req SWS_Fls_331 */
    Fls_Global.flashWriteInfo.source = (uint32)SourceAddressPtr;  /*lint !e923 Intended use */
    Fls_Global.flashWriteInfo.dest = TargetAddress;
    Fls_Global.flashWriteInfo.left = Length;

    if( Fls_Global.mode == MEMIF_MODE_FAST ) {
        Fls_Global.flashWriteInfo.chunkSize = Fls_Global.config->FlsMaxWriteFastMode;
    } else {
        Fls_Global.flashWriteInfo.chunkSize = Fls_Global.config->FlsMaxWriteNormalMode;
    }

    // unlock flash for the entire range.
    Flash_Lock(Fls_Global.config->FlsInfo,FLASH_OP_UNLOCK, TargetAddress, Length );

    LOG_HEX2("Fls_Write() ",Fls_Global.flashWriteInfo.dest," ", Fls_Global.flashWriteInfo.left);

    /* Save to original request */
    Fls_Global.flashWriteInfo.pDest = TargetAddress;
    Fls_Global.flashWriteInfo.pLeft = Length;

    /** @req SWS_Fls_146  */
    if (EE_OK != Flash_ProgramPageStart(    Fls_Global.config->FlsInfo,
                            &Fls_Global.flashWriteInfo.dest,
                            &Fls_Global.flashWriteInfo.source,
                            &Fls_Global.flashWriteInfo.left,
                            NULL)) {
        status = E_NOT_OK;
    }

    return status; /** @req SWS_Fls_334 */
}

#if ( FLS_CANCEL_API == STD_ON )
/** !req SWS_Fls_00348 */
/** !req SWS_Fls_00349 */
void Fls_Cancel( void )
{
    /* API NOT SUPPORTED */
}
#endif

#if ( FLS_GET_STATUS_API == STD_ON )
MemIf_StatusType Fls_GetStatus( void )
/** @req SWS_Fls_00184 */
/** @req SWS_Fls_00034 */
{
    return Fls_Global.status;
}
#endif
/** @req SWS_Fls_00185 */

#if ( FLS_GET_JOB_RESULT_API == STD_ON )

MemIf_JobResultType  Fls_GetJobResult ( void )
{
    /** !req SWS_Fls_00358 */
    /** !req SWS_Fls_00035 */
    return Fls_Global.jobResultType;
}
#endif

void Fls_MainFunction(void) {
    /** @req SWS_Fls_00038 */

    static uint32 progressCntr = 0;
    uint32 flashStatus;
    sint32 result;
    uint8 eccError = 0;

    uint32 chunkSize;

    /** @req SWS_Fls_117 */
    /** @req SWS_Fls_00311 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_NO_RV(Fls_Global.status != MEMIF_UNINIT,FLS_MAIN_FUNCTION_ID, FLS_E_UNINIT );

    /** @req SWS_Fls_00039 */
    /** @req SWS_Fls_00040 */
    /** @req SWS_Fls_00001 */
    /** @req SWS_Fls_00036 */
    /** @req SWS_Fls_00037 */
    if ( Fls_Global.jobResultType == MEMIF_JOB_PENDING) {
        switch (Fls_Global.jobType) {
        case FLS_JOB_COMPARE:
            /** @req SWS_Fls_00243 */
            /** !req SWS_Fls_00318 */
            // !req SWS_Fls_00154  Hardware error = FLS_E_COMPARE_FAILED
            // ( we are reading directly from flash so it makes no sense )
            // Read ECC-error to clear it
            Mcu_Arc_GetECCError(&eccError); /*lint !e934 Only used in this function  */

            chunkSize = MIN( Fls_Global.length, Fls_Global.readChunkSize );

            /** @req SWS_Fls_00244 */
            /*lint -e{923} flashAddr set by AUTOSAR and it is justified to cast in this case */
            result = (sint32)memcmp((void *)Fls_Global.ramAddr,
                                    (void *)Fls_Global.flashAddr, (size_t)chunkSize );

            Fls_Global.ramAddr = &Fls_Global.ramAddr[chunkSize];
            Fls_Global.flashAddr += chunkSize;
            Fls_Global.length -= chunkSize;

            Mcu_Arc_GetECCError(&eccError);  /*lint !e934 Only used in this function  */
            if( eccError > 0u ){
                readFail();
            } else {
                if( 0 != Fls_Global.length ) {
                    if (result == 0) {
                        Fls_Global.jobResultType = MEMIF_JOB_OK;
                    } else {
                        /* @req SWS_Fls_00200 */
                        Fls_Global.jobResultType = MEMIF_BLOCK_INCONSISTENT;
                    }
                    Fls_Global.status = MEMIF_IDLE;
                    Fls_Global.jobType = FLS_JOB_NONE;
                } else {
                    /* Do nothing, wait for next loop */
                }
            }

            break;

        case FLS_JOB_ERASE: {

            flashStatus = Flash_CheckStatus(Fls_Global.config->FlsInfo, (uint32*)Fls_Global.flashAddr, Fls_Global.length ); /*lint !e923 Intended  */

            if (flashStatus == EE_OK ) {
                /** @req SWS_Fls_00345 */
                /** @req SWS_Fls_00346 */
                Fls_Global.jobResultType = MEMIF_JOB_OK;
                Fls_Global.jobType = FLS_JOB_NONE;
                Fls_Global.status = MEMIF_IDLE;
                FEE_JOB_END_NOTIFICATION();
            } else if (flashStatus == EE_INFO_HVOP_INPROGRESS) {
                /* Busy, Do nothing */
            } else {
                // Error
                eraseFail();
            }
            break;
        }
        case FLS_JOB_READ:
            /** @req SWS_Fls_00238 */
            /** @req SWS_Fls_00239 */

            // NOT implemented. Hardware error = FLS_E_READ_FAILED
            // ( we are reading directly from flash so it makes no sense )
            // Read ECC-error to clear it
            Mcu_Arc_GetECCError(&eccError); /*lint !e934 Only used in this function  */


            chunkSize = MIN( Fls_Global.length, Fls_Global.readChunkSize );

            memcpy( (void *)Fls_Global.ramAddr, (void *) Fls_Global.flashAddr, (size_t)chunkSize );  /*lint !e923 Inteded use  */

            Fls_Global.ramAddr += chunkSize; /*lint !e9016 Intended use */
            Fls_Global.flashAddr += chunkSize;
            Fls_Global.length -= chunkSize;

            Mcu_Arc_GetECCError(&eccError);  /*lint !e934 Only used in this function  */
            if( eccError > 0u ){
                readFail();
            } else {
                if( 0 == Fls_Global.length ) {
                    /** @req SWS_Fls_00345 */
                    /** @req SWS_Fls_00346 */
                    Fls_Global.jobResultType = MEMIF_JOB_OK;
                    Fls_Global.status = MEMIF_IDLE;
                    Fls_Global.jobType = FLS_JOB_NONE;
                    FEE_JOB_END_NOTIFICATION();
                    LOG_STR("Fls_RP() OK\n");
                }
            }
            break;

        case FLS_JOB_WRITE:
        {
            /* We are writing in chunks. If we want to write 6 chunks in total but
             * only 2 at a time:
             *
             * Call
             *  #1   The Fls_Write
             *  #2   Wait for Flash_CheckStatus(), Flash_ProgramPageStart().. function return
             *      -> 1 verified write, 1 pending
             *  #3  Wait for Flash_CheckStatus(), Flash_ProgramPageStart()
             *      Wait for Flash_CheckStatus(), Flash_ProgramPageStart() .. function return
             *      -> 3 verified writes, 1 pending
             *  #4  Wait for Flash_CheckStatus(), Flash_ProgramPageStart()
             *      Wait for Flash_CheckStatus(), Flash_ProgramPageStart() .. function return
             *      -> 5 verified writes, 1 pending
             *  #5  Wait for Flash_CheckStatus(), ...function return
             *      -> 6 verified writes,
             */

            uint32 bytesLeftToBeWritten = MIN(Fls_Global.flashWriteInfo.chunkSize, Fls_Global.flashWriteInfo.left);

            do {
                flashStatus = Flash_CheckStatus(
                                        Fls_Global.config->FlsInfo,
                                        (uint32 *) Fls_Global.flashWriteInfo.pDest, /*lint !e923 Intended use */
                                        Fls_Global.flashWriteInfo.pLeft - Fls_Global.flashWriteInfo.left);

                if (flashStatus == EE_OK) {
                    progressCntr = 0;

                    LOG_HEX1("Fls_CS() OK ",Fls_Global.flashWriteInfo.pDest);

                    if (Fls_Global.flashWriteInfo.left == 0) {
                        /* Done! */
                        /** @req SWS_Fls_00345 */
                        /** @req SWS_Fls_00346 */
                        Fls_Global.jobResultType = MEMIF_JOB_OK;
                        Fls_Global.status = MEMIF_IDLE;
                        Fls_Global.jobType = FLS_JOB_NONE;
                        FEE_JOB_END_NOTIFICATION();
                        break;
                    }

                    /* Write more */
                    Fls_Global.flashWriteInfo.pDest = Fls_Global.flashWriteInfo.dest;
                    Fls_Global.flashWriteInfo.pLeft = Fls_Global.flashWriteInfo.left;

                    /* Double word programming */
                    LOG_HEX2("Fls_PP() ",Fls_Global.flashWriteInfo.dest," ", Fls_Global.flashWriteInfo.left);

                    flashStatus = Flash_ProgramPageStart(
                                            Fls_Global.config->FlsInfo,
                                            &Fls_Global.flashWriteInfo.dest,
                                            &Fls_Global.flashWriteInfo.source,
                                            &Fls_Global.flashWriteInfo.left, NULL);
                    if (flashStatus != EE_OK) {
                        writeFail();
                        break;  /*lint !e9011 Better readability this way */
                    }
                    else {
                        uint32 bytesWritten = Fls_Global.flashWriteInfo.pLeft - Fls_Global.flashWriteInfo.left;
                        bytesLeftToBeWritten = (bytesWritten > bytesLeftToBeWritten) ? 0u : (bytesLeftToBeWritten - bytesWritten);
                    }

                } else if (flashStatus == EE_INFO_HVOP_INPROGRESS) {
                    /* Wait for it */

                    // One return cycle takes approx ~130 instructions.
                    if (MAX_PROGRESS_CNTR < progressCntr) {
                        progressCntr = 0;
                        writeFail();
                        break; /*lint !e9011 Better readability this way */
                    }

                    progressCntr++;

                } else {
                    progressCntr = 0;
                    writeFail();
                    /* Nothing to do, quit loop */
                    break;  /*lint !e9011 Better readability this way */
                }

            } while (bytesLeftToBeWritten > 0 );

            break;
        }
        case FLS_JOB_NONE:
            ASSERT(FALSE);
            break;

        default:
            break;
        } /* switch */

    }   /* if */
}


/**
 * Read from flash memory
 *
 * @param SourceAddress
 * @param TargetAddressPtr
 * @param Length
 * @return
 */
Std_ReturnType Fls_Read(    Fls_AddressType SourceAddress,
                            uint8 *TargetAddressPtr,
                            Fls_LengthType Length)
{
#if FLS_BASE_ADDRESS > 0
    /* Avoid compiler warning */
    SourceAddress += FLS_BASE_ADDRESS;
#endif
    Std_ReturnType status;
    status = E_OK;
    /** @req SWS_Fls_00236 */
    /** @req SWS_Fls_00239 */
    /** @req SWS_Fls_00240 */
    /** @req SWS_Fls_00311 */
    /** @req SWS_Fls_00099 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_W_RV(Fls_Global.status != MEMIF_UNINIT,FLS_READ_ID, FLS_E_UNINIT,E_NOT_OK );
    /** @req SWS_Fls_00100 */
    /** @req SWS_Fls_00312 */
    VALIDATE_W_RV( Fls_Global.status != MEMIF_BUSY, FLS_READ_ID, FLS_E_BUSY, E_NOT_OK );
    /** @req SWS_Fls_00158 */
    /** @req SWS_Fls_00310 */
    VALIDATE_W_RV( TargetAddressPtr != NULL , FLS_READ_ID, FLS_E_PARAM_DATA, E_NOT_OK );
    /** @req SWS_Fls_00097  */
    VALIDATE_W_RV( E_OK == checkValidAddress(SourceAddress), FLS_READ_ID, FLS_E_PARAM_ADDRESS, E_NOT_OK );
    /** @req SWS_Fls_00098  */
    VALIDATE_W_RV( (Length != 0) && (E_OK == checkValidAddress(SourceAddress + Length -1)), FLS_READ_ID, FLS_E_PARAM_LENGTH, E_NOT_OK );
#if defined(CFG_MPC5777M)|| defined(CFG_MPC5748G)|| defined(CFG_MPC5746C) || defined(CFG_MPC5747C)
    VALIDATE_W_RV((E_OK == checkValidChunk(SourceAddress, SourceAddress + Length - 1)), FLS_READ_ID, FLS_E_INVALID_AREA, E_NOT_OK);
#endif
    /*lint -restore*/
    // Always check if status is not busy
    if (Fls_Global.status == MEMIF_BUSY) {
        status = E_NOT_OK;
    } else {
    /* @req SWS_Fls_00338  */
    /* @req SWS_Fls_00339  */
        Fls_Global.status = MEMIF_BUSY;
        Fls_Global.jobResultType = MEMIF_JOB_PENDING;
        Fls_Global.jobType = FLS_JOB_READ;

        LOG_HEX2("Fls_Read() ",(uint32)TargetAddressPtr," ", Length);

        /** @req SWS_Fls_00337 */
        Fls_Global.flashAddr = SourceAddress;
        Fls_Global.ramAddr = TargetAddressPtr;
        Fls_Global.length = Length;

        if( Fls_Global.mode == MEMIF_MODE_FAST ) {
            Fls_Global.readChunkSize = Fls_Global.config->FlsMaxReadFastMode;
        } else {
            Fls_Global.readChunkSize = Fls_Global.config->FlsMaxReadNormalMode;
        }
    }
    /* @req SWS_Fls_00340 */
    return status;
}

#if ( FLS_COMPARE_API == STD_ON )
Std_ReturnType Fls_Compare( Fls_AddressType SourceAddress,
                            const uint8 *TargetAddressPtr,
                            Fls_LengthType Length )
{
#if FLS_BASE_ADDRESS > 0
    /* Avoid compiler warning */
    SourceAddress += FLS_BASE_ADDRESS;
#endif
    Std_ReturnType status;
    /** @req SWS_Fls_00344 */
    status = E_OK;
    /** @req SWS_Fls_00241 */
    /** @req SWS_Fls_00186 */
    /** @req SWS_Fls_00311 */
    /** @req SWS_Fls_00152 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_W_RV(Fls_Global.status != MEMIF_UNINIT,FLS_COMPARE_ID, FLS_E_UNINIT,E_NOT_OK );
    /** @req SWS_Fls_00153 */
    /** @req SWS_Fls_00312 */
    VALIDATE_W_RV( Fls_Global.status != MEMIF_BUSY, FLS_COMPARE_ID, FLS_E_BUSY, E_NOT_OK );
    /** @req SWS_Fls_00273 */
    /** @req SWS_Fls_00310 */
    VALIDATE_W_RV( TargetAddressPtr != NULL , FLS_COMPARE_ID, FLS_E_PARAM_DATA, E_NOT_OK );
    /** @req SWS_Fls_00150  */
    VALIDATE_W_RV( E_OK == checkValidAddress(SourceAddress), FLS_COMPARE_ID, FLS_E_PARAM_ADDRESS, E_NOT_OK );
    /** @req SWS_Fls_00151  */
    VALIDATE_W_RV( (Length != 0uL) && (E_OK == checkValidAddress( SourceAddress + Length - 1uL)),
            FLS_COMPARE_ID, FLS_E_PARAM_LENGTH, E_NOT_OK );
#if defined(CFG_MPC5777M)|| defined(CFG_MPC5748G)|| defined(CFG_MPC5746C) || defined(CFG_MPC5747C)
    VALIDATE_W_RV((E_OK == checkValidChunk(SourceAddress, SourceAddress + Length - 1)), FLS_COMPARE_ID, FLS_E_INVALID_AREA, E_NOT_OK);
#endif
    /*lint -restore*/
    // Always check if status is not busy
    if (Fls_Global.status == MEMIF_BUSY ) {
        status = E_NOT_OK;
    } else {

        Fls_Global.status = MEMIF_BUSY;    /* @req SWS_Fls_00342 */
        Fls_Global.jobResultType = MEMIF_JOB_PENDING;  /* @req SWS_Fls_00343 */
        Fls_Global.jobType = FLS_JOB_COMPARE;

        if( Fls_Global.mode == MEMIF_MODE_FAST ) {
            Fls_Global.readChunkSize = Fls_Global.config->FlsMaxReadFastMode;
        } else {
            Fls_Global.readChunkSize = Fls_Global.config->FlsMaxReadNormalMode;
        }
        /** @req SWS_Fls_00341  */
        Fls_Global.flashAddr = SourceAddress;
        Fls_Global.ramAddr = (uint8*)TargetAddressPtr; /*lint !e9005 !e926 Would make core more complex. IMPROVMENT: Remove cast */
        Fls_Global.length = Length;
    }
    return status;
}
#endif

#if ( FLS_SET_MODE_API == STD_ON )
void Fls_SetMode(MemIf_ModeType Mode) {
    /** @req SWS_Fls_00311 */
    VALIDATE_NO_RV( ( Fls_Global.status != MEMIF_UNINIT ), FLS_SET_MODE_ID, FLS_E_UNINIT);
    /* @req SWS_Fls_00156 */
    /* @req SWS_Fls_00312 */
    VALIDATE_NO_RV( ( Fls_Global.status != MEMIF_BUSY ), FLS_SET_MODE_ID, FLS_E_BUSY);

    VALIDATE_NO_RV(((Mode == MEMIF_MODE_SLOW ) || (Mode == MEMIF_MODE_SLOW)), FLS_SET_MODE_ID, FLS_E_PARAM_POINTER);

    /* @req SWS_Fls_00155 */
    Fls_Global.mode = Mode;
}
#endif

#if ( FLS_VERSION_INFO_API == STD_ON )
void Fls_GetVersionInfo( Std_VersionInfoType *VersioninfoPtr )
{
    /* @req SWS_Fls_00363 */
    /* @req SWS_Fls_00206 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_NO_RV( ( NULL != VersioninfoPtr ), FLS_GET_VERSION_INFO_ID, FLS_E_PARAM_POINTER);
    VersioninfoPtr->vendorID = FLS_VENDOR_ID;
    VersioninfoPtr->moduleID = FLS_MODULE_ID;
    VersioninfoPtr->sw_major_version = FLS_SW_MAJOR_VERSION;
    VersioninfoPtr->sw_minor_version = FLS_SW_MINOR_VERSION;
    VersioninfoPtr->sw_patch_version = FLS_SW_PATCH_VERSION;

}
#endif

#if 0

void Fls_Check(uint32 flsBaseAddress, uint32 flsTotalSize) {
    /* @req SWS_Fls_00208 */
    // ECC checking is always on by default.
    // If a non correctable error is discovered
    // we will get an IVOR2 exception.

    // Enable Flash Non_Correctible Reporting,
    // Not really necessary but makes more information
    // available in the MCM registers if an error occurs.
#if defined(CFG_MPC560X) || defined(CFG_MPC5567) || defined(CFG_MPC563XM) || defined(CFG_MPC5644A)
    ECSM.ECR.B.EFNCR = 1;
#elif defined (CFG_MPC5516)
    MCM.ECR.B.EFNCR = 1;
#else
#warning "Non supported processor"
#endif

    // Read flash in 32bit chunks, it's most efficient.
    uint32* memoryChunkPtr = (uint32*) flsBaseAddress;
    uint32* flsTotalSizePtr = (uint32*) flsTotalSize;
    uint32 memoryChunk = *memoryChunkPtr; // The first read

    // Read the rest of the flash, chunk by chunk
    while (memoryChunkPtr < flsTotalSizePtr) {
        memoryChunk = *(memoryChunkPtr++);
    }
}
#endif
