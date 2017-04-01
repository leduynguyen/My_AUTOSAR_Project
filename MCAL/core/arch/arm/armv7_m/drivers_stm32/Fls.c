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

/** @tagSettings DEFAULT_ARCHITECTURE=STM32 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "arc_assert.h"
#include <string.h>
#include "stm32f10x_flash.h"
#include "Fls.h"
#if defined(USE_DET)
#include "Det.h"
#endif

/* ----------------------------[private macro]-------------------------------*/

#define HALF_WORD_SIZE 2

#if ( FLS_DEV_ERROR_DETECT == STD_ON )

#define DET_REPORTERROR(_x,_y,_z,_q) (void)Det_ReportError(FLS_MODULE_ID, _y, _z, _q)

#define FEE_JOB_END_NOTIFICATION() \
  if( Fls_Global.config->FlsJobEndNotification != NULL ) { \
    Fls_Global.config->FlsJobEndNotification(); \
  }

#define FEE_JOB_ERROR_NOTIFICATION() \
  if( Fls_Global.config->FlsJobErrorNotification != NULL ) { \
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

typedef enum {
    FLS_JOB_NONE, FLS_JOB_COMPARE, FLS_JOB_ERASE, FLS_JOB_ERASE2, FLS_JOB_READ, FLS_JOB_WRITE, FLS_JOB_WRITE2
} Fls_Arc_JobType;

typedef struct {
    const Fls_ConfigType*   config;
    MemIf_StatusType        status;
    MemIf_JobResultType     jobResultType;
    Fls_Arc_JobType         jobType;
    Fls_AddressType         flashAddr;   //sourceAddr
    uint32                  ramAddr;    // targetAddr
    Fls_LengthType          length;
    uint32                  jobChunkSize;
    Fls_AddressType			pageStart;
    Fls_AddressType			erased;
} Fls_GlobalType;

Fls_GlobalType Fls_Global = {
    .config = NULL,
    .status = MEMIF_UNINIT,
    .jobResultType = MEMIF_JOB_OK,
    .jobType = FLS_JOB_NONE,
    .flashAddr = 0uL,
    .ramAddr = 0,
    .length = 0,
    .jobChunkSize = 32,
    .pageStart = 0,
    .erased = 0
};

/* ----------------------------[private functions]---------------------------*/
static Std_ReturnType sectorAligned( Fls_AddressType SourceAddress ) {
    Std_ReturnType rv = E_NOT_OK;
    const FlashType *bPtr;

    bPtr = &Fls_Global.config->FlsInfo[0];

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
    }

    return rv;
}

/**
 * Check all bank ranges for a valid address
 *
 * @param SourceAddress
 * @return
 */
static Std_ReturnType checkValidAddress( Fls_AddressType SourceAddress ) {
    Std_ReturnType rv = E_NOT_OK;
    const FlashType *bPtr;

    bPtr = &Fls_Global.config->FlsInfo[0];
    uint32 startAddr = bPtr->sectAddr[0];

    if( (SourceAddress >= startAddr) &&
        (SourceAddress < (Fls_Global.config->FlsInfo[0].sectAddr[FLASH_MAX_PAGES - 1] + FLASH_PAGE_SIZE)) )
    {
        rv = E_OK;
    }

    return rv;
}
/* ----------------------------[public functions]----------------------------*/

/**
 *
 * @param ConfigPtr
 */
void Fls_Init(const Fls_ConfigType *ConfigPtr)
{
    /** @req SWS_Fls_00014 */
    /** @req SWS_Fls_00086 */
    /** @req SWS_Fls_00015 */
    /** !req SWS_Fls_00048 */
    /** !req SWS_Fls_00325 */
    /** !req SWS_Fls_00326 */

    /** @req SWS_Fls_00268 */
    VALIDATE_NO_RV(Fls_Global.status!=MEMIF_BUSY,FLS_INIT_ID, FLS_E_BUSY );

    VALIDATE_NO_RV((ConfigPtr != NULL), FLS_INIT_ID, FLS_E_PARAM_CONFIG);

    Fls_Global.status = MEMIF_UNINIT;
    Fls_Global.jobResultType = MEMIF_JOB_PENDING;

    /** @req SWS_Fls_00191 */
    Fls_Global.config = ConfigPtr;


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
    /** @req SWS_Fls_00218  */
    /** @req SWS_Fls_00220 */
    /** @req SWS_Fls_00327 */

    /** @req SWS_Fls_00065 */
    VALIDATE_W_RV( Fls_Global.status != MEMIF_UNINIT, FLS_ERASE_ID, FLS_E_UNINIT, E_NOT_OK );
    /** @req SWS_Fls_00023 */
    VALIDATE_W_RV( Fls_Global.status != MEMIF_BUSY, FLS_ERASE_ID, FLS_E_BUSY, E_NOT_OK );
    /** @req SWS_Fls_00020 */
    VALIDATE_W_RV( E_OK == sectorAligned( TargetAddress ),
            FLS_ERASE_ID, FLS_E_PARAM_ADDRESS, E_NOT_OK );
    /** @req SWS_Fls_00021  */
    VALIDATE_W_RV( (Length != 0) && (E_OK == sectorAligned( TargetAddress + Length)),
            FLS_ERASE_ID, FLS_E_PARAM_LENGTH, E_NOT_OK );

    Fls_Global.status = MEMIF_BUSY;/** @req SWS_Fls_00328 */
    Fls_Global.jobResultType = MEMIF_JOB_PENDING;/** @req SWS_Fls_00329 */
    Fls_Global.jobType = FLS_JOB_ERASE;
    Fls_Global.flashAddr = TargetAddress;
    Fls_Global.length = Length;

    return E_OK;/** @req SWS_Fls_00330 */
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
    /** @req SWS_Fls_00223 */
    /** @req SWS_Fls_00225 */
    /** @req SWS_Fls_00226 */

    /** @req SWS_Fls_00066 */
    VALIDATE_W_RV(Fls_Global.status != MEMIF_UNINIT,FLS_WRITE_ID, FLS_E_UNINIT,E_NOT_OK );
    /** @req SWS_Fls_00030 */
    VALIDATE_W_RV(Fls_Global.status != MEMIF_BUSY,FLS_WRITE_ID, FLS_E_BUSY,E_NOT_OK );
    /** @req SWS_Fls_00157 */
    VALIDATE_W_RV(SourceAddressPtr != NULL,FLS_WRITE_ID, FLS_E_PARAM_DATA,E_NOT_OK );
    /** @req SWS_Fls_00026 */
    VALIDATE_W_RV( ((TargetAddress % HALF_WORD_SIZE) == 0) && (E_OK == checkValidAddress(TargetAddress)),
            FLS_WRITE_ID, FLS_E_PARAM_ADDRESS, E_NOT_OK );
    /** @req SWS_Fls_00027 */
    VALIDATE_W_RV( ((Length != 0) && ((((TargetAddress + Length) % HALF_WORD_SIZE) == 0) && (E_OK == checkValidAddress(TargetAddress + Length -1 )))),
            FLS_WRITE_ID, FLS_E_PARAM_LENGTH, E_NOT_OK );

    /** @req SWS_Fls_333 */
    Fls_Global.jobResultType = MEMIF_JOB_PENDING;
    /** @req SWS_Fls_332  */
    Fls_Global.status = MEMIF_BUSY;
    Fls_Global.jobType = FLS_JOB_WRITE;

    // Fill in the required fields for programming...
    /** @req SWS_Fls_331 */

    Fls_Global.flashAddr = TargetAddress;
    Fls_Global.ramAddr = (uint32) SourceAddressPtr; /*lint !e923 intended use */
    Fls_Global.length = Length;

    return E_OK; /** @req SWS_Fls_334 */
}

#if ( FLS_CANCEL_API == STD_ON )
void Fls_Cancel( void )
{
    /* API NOT SUPPORTED */
}
#endif

#if ( FLS_GET_STATUS_API == STD_ON )
MemIf_StatusType Fls_GetStatus( void )
{
    return Fls_Global.status;
}
#endif

#if ( FLS_GET_JOB_RESULT_API == STD_ON )
MemIf_JobResultType Fls_GetJobResult( void )
{
    return Fls_Global.jobResultType;
}
#endif

void executeCompareJob( void );
void executeReadJob( void );
void executeEraseJob( void );
void executeWriteJob( void );

void Fls_MainFunction( void ) {
    /** @req SWS_Fls_00038 */
    uint32 page;

    /** @req SWS_Fls_117 */
    VALIDATE_NO_RV(Fls_Global.status != MEMIF_UNINIT,FLS_MAIN_FUNCTION_ID, FLS_E_UNINIT );

    /** @req SWS_Fls_00039 */
    if ( Fls_Global.jobResultType == MEMIF_JOB_PENDING) {
        switch (Fls_Global.jobType) {
            case FLS_JOB_COMPARE:
                /** @req SWS_Fls_00243 */
                executeCompareJob();
                break;
            case FLS_JOB_ERASE:
                /* Unlock the Flash Program Erase controller */
                FLASH_Unlock();
                /* Clear All pending flags */
                FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
                /* Find first sector. */
                page = (Fls_Global.flashAddr - Fls_Global.config->FlsInfo->sectAddr[0]) / FLASH_PAGE_SIZE;
                Fls_Global.pageStart = Fls_Global.config->FlsInfo->sectAddr[page];
                Fls_Global.jobType = FLS_JOB_ERASE2;
                executeEraseJob();
                break;
            case FLS_JOB_ERASE2:
                executeEraseJob();
                break;
            case FLS_JOB_READ:
                /** @req SWS_Fls_00238 */
                /** @req SWS_Fls_00239 */
                executeReadJob();
                break;
            case FLS_JOB_WRITE:
                /* Unlock the Flash Program Erase controller */
                FLASH_Unlock();
                /* Clear All pending flags */
                FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
                Fls_Global.jobType = FLS_JOB_WRITE2;
                executeWriteJob();
                break;
            case FLS_JOB_WRITE2:
                executeWriteJob();
                break;
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
    /** @req SWS_Fls_00236 */
    /** @req SWS_Fls_00239 */

    /** @req SWS_Fls_00099 */
    VALIDATE_W_RV(Fls_Global.status != MEMIF_UNINIT,FLS_READ_ID, FLS_E_UNINIT,E_NOT_OK );
    /** @req SWS_Fls_00100 */
    VALIDATE_W_RV( Fls_Global.status != MEMIF_BUSY, FLS_READ_ID, FLS_E_BUSY, E_NOT_OK );
    /** @req SWS_Fls_00158 */
    VALIDATE_W_RV( TargetAddressPtr != NULL , FLS_READ_ID, FLS_E_PARAM_DATA, E_NOT_OK );
    /** @req SWS_Fls_00097  */
    VALIDATE_W_RV( E_OK == checkValidAddress(SourceAddress), FLS_READ_ID, FLS_E_PARAM_ADDRESS, E_NOT_OK );
    /** @req SWS_Fls_00098  */
    VALIDATE_W_RV( (Length != 0) && (E_OK == checkValidAddress(SourceAddress + Length -1)), FLS_READ_ID, FLS_E_PARAM_LENGTH, E_NOT_OK );

    // Always check if status is not busy
    if (Fls_Global.status == MEMIF_BUSY) {
        return E_NOT_OK;
    }

    Fls_Global.status = MEMIF_BUSY;
    Fls_Global.jobResultType = MEMIF_JOB_PENDING;
    Fls_Global.jobType = FLS_JOB_READ;

    /** @req SWS_Fls_00337 */
    Fls_Global.flashAddr = SourceAddress;
    Fls_Global.ramAddr = (uint32) TargetAddressPtr; /*lint !e923 intended use */
    Fls_Global.length = Length;

    return E_OK;
}

#if ( FLS_COMPARE_API == STD_ON )
Std_ReturnType Fls_Compare( Fls_AddressType SourceAddress,
                            const uint8 *TargetAddressPtr,
                            Fls_LengthType Length )
{
    /** @req SWS_Fls_00241 */
    /** @req SWS_Fls_00186 */

    /** @req SWS_Fls_00152 */
    VALIDATE_W_RV(Fls_Global.status != MEMIF_UNINIT,FLS_COMPARE_ID, FLS_E_UNINIT,E_NOT_OK );
    /** @req SWS_Fls_00153 */
    VALIDATE_W_RV( Fls_Global.status != MEMIF_BUSY, FLS_COMPARE_ID, FLS_E_BUSY, E_NOT_OK );
    /** @req SWS_Fls_00273 */
    VALIDATE_W_RV( TargetAddressPtr != NULL , FLS_COMPARE_ID, FLS_E_PARAM_DATA, E_NOT_OK );
    /** @req SWS_Fls_00150  */
    VALIDATE_W_RV( E_OK == checkValidAddress(SourceAddress), FLS_COMPARE_ID, FLS_E_PARAM_ADDRESS, E_NOT_OK );
    /** @req SWS_Fls_00151  */
    VALIDATE_W_RV( (Length != 0uL) && (E_OK == checkValidAddress( SourceAddress + Length - 1uL)),
            FLS_COMPARE_ID, FLS_E_PARAM_LENGTH, E_NOT_OK );

    // Always check if status is not busy
    if (Fls_Global.status == MEMIF_BUSY ) {
        return E_NOT_OK;
    }

    Fls_Global.status = MEMIF_BUSY;    /* @req SWS_Fls_00342 */
    Fls_Global.jobResultType = MEMIF_JOB_PENDING;  /* @req SWS_Fls_00343 */
    Fls_Global.jobType = FLS_JOB_COMPARE;

    /** @req SWS_Fls_00341  */
    Fls_Global.flashAddr = SourceAddress;
    Fls_Global.ramAddr = (uint32) TargetAddressPtr; /*lint !e923 intended use */
    Fls_Global.length = Length;

    return E_OK;
}
#endif

#if ( FLS_SET_MODE_API == STD_ON )
void Fls_SetMode(MemIf_ModeType Mode) {
    /* API NOT SUPPORTED */
}
#endif

#if ( FLS_VERSION_INFO_API == STD_ON )
void Fls_GetVersionInfo( Std_VersionInfoType *VersioninfoPtr )
{
    /* @req SWS_Fls_00363 */
    VALIDATE_NO_RV( ( NULL != VersioninfoPtr ), FLS_GET_VERSION_INFO_ID, FLS_E_PARAM_POINTER);

    VersioninfoPtr->vendorID = FLS_VENDOR_ID;
    VersioninfoPtr->moduleID = FLS_MODULE_ID;
    VersioninfoPtr->sw_major_version = FLS_SW_MAJOR_VERSION;
    VersioninfoPtr->sw_minor_version = FLS_SW_MINOR_VERSION;
    VersioninfoPtr->sw_patch_version = FLS_SW_PATCH_VERSION;

}
#endif

void executeCompareJob( void )
{
    uint32 chunkSize;
    sint32 result;

    chunkSize = MIN( Fls_Global.length, Fls_Global.jobChunkSize );

    /** @req SWS_Fls_00244 */
    /*lint -e{923} flashAddr set by AUTOSAR and it is justified to cast in this case */
    result = (sint32)memcmp((void *)Fls_Global.ramAddr,
                            (void *)Fls_Global.flashAddr, (size_t)chunkSize );

    if (result != 0) {
        /* @req SWS_Fls_00200 */
        Fls_Global.jobResultType = MEMIF_BLOCK_INCONSISTENT;
        Fls_Global.status = MEMIF_IDLE;
        Fls_Global.jobType = FLS_JOB_NONE;
        FEE_JOB_END_NOTIFICATION(); /*lint !e746 simplified notation */
    } else {
        /* Continue with next chunk */
        Fls_Global.ramAddr = Fls_Global.ramAddr + chunkSize;
        Fls_Global.flashAddr += chunkSize;
        Fls_Global.length -= chunkSize;

        if( 0 != Fls_Global.length ) {
            Fls_Global.jobResultType = MEMIF_JOB_OK;
            Fls_Global.status = MEMIF_IDLE;
            Fls_Global.jobType = FLS_JOB_NONE;
            FEE_JOB_END_NOTIFICATION();  /*lint !e746 simplified notation */
        } else {
            /* Do nothing, wait for next loop */
        }
    }
}

void executeReadJob( void )
{
    uint32 chunkSize;

    chunkSize = MIN( Fls_Global.length, Fls_Global.jobChunkSize );

    memcpy( (void *)Fls_Global.ramAddr, (void *) Fls_Global.flashAddr, (size_t)chunkSize );  /*lint !e923 Inteded use  */

    Fls_Global.ramAddr += chunkSize; /*lint !e9016 Intended use */
    Fls_Global.flashAddr += chunkSize;
    Fls_Global.length -= chunkSize;

    if( 0 == Fls_Global.length ) {
        Fls_Global.jobResultType = MEMIF_JOB_OK;
        Fls_Global.status = MEMIF_IDLE;
        Fls_Global.jobType = FLS_JOB_NONE;
        FEE_JOB_END_NOTIFICATION(); /*lint !e746 simplified notation */
    }
}

void executeEraseJob( void )
{
    FLASH_Status status = FLASH_ErasePage((uint32_t) Fls_Global.pageStart);
    if (FLASH_COMPLETE == status) {
        Fls_Global.erased += FLASH_PAGE_SIZE;
        if (Fls_Global.erased < Fls_Global.length) {
            Fls_Global.pageStart += FLASH_PAGE_SIZE;
            /* Continue in next call */
        } else {
            Fls_Global.jobResultType = MEMIF_JOB_OK;
            Fls_Global.status = MEMIF_IDLE;
            Fls_Global.jobType = FLS_JOB_NONE;
            FEE_JOB_END_NOTIFICATION(); /*lint !e746 simplified notation */
        }
    } else {
        if (FLASH_BUSY == status) {
            /* Just wait until next call */
        } else {
            /* FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_TIMEOUT */
            Fls_Global.jobResultType = MEMIF_JOB_FAILED;
            Fls_Global.status = MEMIF_IDLE;
            Fls_Global.jobType = FLS_JOB_NONE;
            FEE_JOB_END_NOTIFICATION(); /*lint !e746 simplified notation */
        }
    }
}

void executeWriteJob( void )
{
    FLASH_Status stResult;

    if (Fls_Global.length >= sizeof(uint32_t))
    {
        stResult = FLASH_ProgramWord((uint32_t) Fls_Global.flashAddr, *((uint32*)Fls_Global.ramAddr)); /*lint !e923 intended use */
        if (FLASH_COMPLETE == stResult) {
            Fls_Global.ramAddr += sizeof(uint32_t);
            Fls_Global.flashAddr += sizeof(uint32_t);
            Fls_Global.length -= sizeof(uint32_t);
        } else {
            // FLASH_ERROR_PG, FLASH_ERROR_WRP or FLASH_TIMEOUT
        }
    } else if (Fls_Global.length == sizeof(uint16_t))
    {
        stResult = FLASH_ProgramHalfWord((uint32_t) Fls_Global.flashAddr, (uint16_t)*((uint16_t*)Fls_Global.ramAddr)); /*lint !e923 intended use */
        if (FLASH_COMPLETE == stResult) {
            Fls_Global.ramAddr += sizeof(uint16_t);
            Fls_Global.flashAddr += sizeof(uint16_t);
            Fls_Global.length -= sizeof(uint16_t);
        } else {
            // FLASH_ERROR_PG, FLASH_ERROR_WRP or FLASH_TIMEOUT
            Fls_Global.jobResultType = MEMIF_JOB_FAILED;
            Fls_Global.status = MEMIF_IDLE;
            Fls_Global.jobType = FLS_JOB_NONE;
            FEE_JOB_END_NOTIFICATION(); /*lint !e746 simplified notation */
        }
    } else {
        ASSERT(FALSE); // Bad alignment, should be caught in the Fls_Write function
    }

    if (0 == Fls_Global.length) {
        Fls_Global.jobResultType = MEMIF_JOB_OK;
        Fls_Global.status = MEMIF_IDLE;
        Fls_Global.jobType = FLS_JOB_NONE;
        FEE_JOB_END_NOTIFICATION(); /*lint !e746 simplified notation */
    }
}
