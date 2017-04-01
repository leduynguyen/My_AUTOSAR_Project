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

/** @tagSettings DEFAULT_ARCHITECTURE=JACINTO5|JACINTO6 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/* ----------------------------[information]----------------------------------*/
#warning "Fls: This Fls driver does no actual reading/write to flash memory!"

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
 *
 * Implementation Notes:
 *   Affected files:
 *   - Fls.c
 *   - Fls_Cfg.c/.h
 *
 *
 * Things left:
 *   - Virtual addresses, FLS209 is not done (code assumes FLS_BASE_ADDRESS is 0)
 *
 */

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
#include "Fls.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#include "Cpu.h"
#include "Mcu.h"
#if (FLS_BASE_ADDRESS != 0)
#ifndef CFG_JACINTO
#error Virtual addresses not supported
#endif
#endif

/*lint -save -e635 Want to reset types of Fls_AddressType */
/*lint -parent(Fls_AddressType, Fls_LengthType) */
/*lint -restore */

/* ----------------------------[private define]------------------------------*/


#define FLS_ERASE_VAL 0xFF
/* ----------------------------[private macro]-------------------------------*/


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
    FLS_JOB_NONE, FLS_JOB_COMPARE, FLS_JOB_ERASE, FLS_JOB_READ, FLS_JOB_WRITE,
} Fls_Arc_JobType;

typedef struct {
    const Fls_ConfigType*   config;
    MemIf_StatusType        status;
    MemIf_JobResultType     jobResultType;
    Fls_Arc_JobType         jobType;
    Fls_AddressType         flashAddr;   //sourceAddr
    uint8 *                 ramAddr;    // targetAddr
    Fls_LengthType          length;
    MemIf_ModeType          mode;
    uint32                  jobChunkSize;
} Fls_GlobalType;

Fls_GlobalType Fls_Global = {
    .config = NULL,
    .status = MEMIF_UNINIT,
    .jobResultType = MEMIF_JOB_OK,
    .jobType = FLS_JOB_NONE,
    .flashAddr = 0uL,
    .ramAddr = NULL,
    .length = 0,
    .mode = MEMIF_MODE_SLOW,
    .jobChunkSize = 0
};


/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
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

    /** @req SWS_Fls_00268 */
    VALIDATE_NO_RV(Fls_Global.status!=MEMIF_BUSY,FLS_INIT_ID, FLS_E_BUSY );

    VALIDATE_NO_RV((ConfigPtr != NULL), FLS_INIT_ID, FLS_E_PARAM_CONFIG);
    VALIDATE_NO_RV(ConfigPtr->FlsMaxReadFastMode != 0, FLS_INIT_ID, FLS_E_PARAM_CONFIG);
    VALIDATE_NO_RV(ConfigPtr->FlsMaxReadNormalMode != 0, FLS_INIT_ID, FLS_E_PARAM_CONFIG);
    VALIDATE_NO_RV(ConfigPtr->FlsMaxWriteFastMode != 0, FLS_INIT_ID, FLS_E_PARAM_CONFIG);
    VALIDATE_NO_RV(ConfigPtr->FlsMaxWriteNormalMode != 0, FLS_INIT_ID, FLS_E_PARAM_CONFIG);

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
#if FLS_BASE_ADDRESS > 0
    /* Avoid compiler warning */
    TargetAddress += FLS_BASE_ADDRESS;
#endif

    /** @req SWS_Fls_00218  */
    /** @req SWS_Fls_00220 */
    /** @req SWS_Fls_00327 */

    /** @req SWS_Fls_00065 */
    VALIDATE_W_RV( Fls_Global.status != MEMIF_UNINIT, FLS_ERASE_ID, FLS_E_UNINIT, E_NOT_OK );
    /** @req SWS_Fls_00023 */
    VALIDATE_W_RV( Fls_Global.status != MEMIF_BUSY, FLS_ERASE_ID, FLS_E_BUSY, E_NOT_OK );

    VALIDATE_W_RV( E_OK == checkValidAddress(TargetAddress), FLS_ERASE_ID, FLS_E_PARAM_ADDRESS, E_NOT_OK );
    VALIDATE_W_RV( (Length != 0) && (E_OK == checkValidAddress(TargetAddress + Length - 1)), FLS_ERASE_ID, FLS_E_PARAM_LENGTH, E_NOT_OK );

    Fls_Global.status = MEMIF_BUSY;/** @req SWS_Fls_00328 */
    Fls_Global.jobResultType = MEMIF_JOB_PENDING;/** @req SWS_Fls_00329 */
    Fls_Global.jobType = FLS_JOB_ERASE;
    Fls_Global.flashAddr = TargetAddress;
    Fls_Global.length = Length;

    if( Fls_Global.mode == MEMIF_MODE_FAST ) {
        Fls_Global.jobChunkSize = Fls_Global.config->FlsMaxWriteFastMode;
    } else {
        Fls_Global.jobChunkSize = Fls_Global.config->FlsMaxWriteNormalMode;
    }
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
#if FLS_BASE_ADDRESS > 0
    /* Avoid compiler warning */
    TargetAddress += FLS_BASE_ADDRESS;
#endif

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
    VALIDATE_W_RV( ((TargetAddress % FLASH_PAGE_SIZE) == 0) && (E_OK == checkValidAddress(TargetAddress)),
            FLS_WRITE_ID, FLS_E_PARAM_ADDRESS, E_NOT_OK );
    /** @req SWS_Fls_00027 */
    VALIDATE_W_RV( ((Length != 0) && ((((TargetAddress + Length) % FLASH_PAGE_SIZE) == 0) && (E_OK == checkValidAddress(TargetAddress + Length -1 )))),
            FLS_WRITE_ID, FLS_E_PARAM_LENGTH, E_NOT_OK );
    // Destination is FLS_BASE_ADDRESS + TargetAddress
    /** @req SWS_Fls_333 */
    Fls_Global.jobResultType = MEMIF_JOB_PENDING;
    /** @req SWS_Fls_332  */
    Fls_Global.status = MEMIF_BUSY;
    Fls_Global.jobType = FLS_JOB_WRITE;

    // Fill in the required fields for programming...
    /** @req SWS_Fls_331 */

    Fls_Global.flashAddr = TargetAddress;
    Fls_Global.ramAddr = (uint8*)SourceAddressPtr;
    Fls_Global.length = Length;

    if( Fls_Global.mode == MEMIF_MODE_FAST ) {
        Fls_Global.jobChunkSize = Fls_Global.config->FlsMaxWriteFastMode;
    } else {
        Fls_Global.jobChunkSize = Fls_Global.config->FlsMaxWriteNormalMode;
    }

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

/**
 * Executes "Fls" job
 * @param job
 */
static void executeJob(Fls_Arc_JobType job)
{
    uint32 chunkSize = MIN( Fls_Global.length, Fls_Global.jobChunkSize );
    sint32 result = 0;
    switch(job) {
        case FLS_JOB_COMPARE:
            result = (sint32)memcmp((void *)Fls_Global.ramAddr,
                                    (void *)Fls_Global.flashAddr, (size_t)chunkSize);
            break;
        case FLS_JOB_ERASE:
            memset((void *)Fls_Global.flashAddr, FLS_ERASED_VALUE, (size_t)chunkSize);
            break;
        case FLS_JOB_READ:
            memcpy((void *)Fls_Global.ramAddr, (void *)Fls_Global.flashAddr, (size_t)chunkSize);
            break;
        case FLS_JOB_WRITE:
            memcpy((void *)Fls_Global.flashAddr, (void *)Fls_Global.ramAddr, (size_t)chunkSize);
            break;
        default:
            break;
    }
    Fls_Global.ramAddr = &Fls_Global.ramAddr[chunkSize];
    Fls_Global.flashAddr += chunkSize;
    Fls_Global.length -= chunkSize;
    if( (FLS_JOB_COMPARE == job) && (0 != result)) {
        /* Compare fail */
        /* @req SWS_Fls_00200 */
        Fls_Global.jobResultType = MEMIF_BLOCK_INCONSISTENT;
        Fls_Global.status = MEMIF_IDLE;
        Fls_Global.jobType = FLS_JOB_NONE;
        FEE_JOB_ERROR_NOTIFICATION();
    } else if( 0 == Fls_Global.length ) {
        Fls_Global.jobResultType = MEMIF_JOB_OK;
        Fls_Global.status = MEMIF_IDLE;
        Fls_Global.jobType = FLS_JOB_NONE;
        FEE_JOB_END_NOTIFICATION();
    }
}

void Fls_MainFunction(void) {
    /** @req SWS_Fls_00038 */

    /** @req SWS_Fls_117 */
    VALIDATE_NO_RV(Fls_Global.status != MEMIF_UNINIT,FLS_MAIN_FUNCTION_ID, FLS_E_UNINIT );

    /** @req SWS_Fls_00039 */
    if ( Fls_Global.jobResultType == MEMIF_JOB_PENDING) {
        switch (Fls_Global.jobType) {
            case FLS_JOB_COMPARE:
                /** @req SWS_Fls_00243 */
                executeJob(FLS_JOB_COMPARE);
                break;
            case FLS_JOB_ERASE:
                executeJob(FLS_JOB_ERASE);
                break;
            case FLS_JOB_READ:
                /** @req SWS_Fls_00238 */
                /** @req SWS_Fls_00239 */
                executeJob(FLS_JOB_READ);
                break;
            case FLS_JOB_WRITE:
                executeJob(FLS_JOB_WRITE);
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
#if FLS_BASE_ADDRESS > 0
    /* Avoid compiler warning */
    SourceAddress += FLS_BASE_ADDRESS;
#endif
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
    Fls_Global.ramAddr = TargetAddressPtr;
    Fls_Global.length = Length;

    if( Fls_Global.mode == MEMIF_MODE_FAST ) {
        Fls_Global.jobChunkSize = Fls_Global.config->FlsMaxReadFastMode;
    } else {
        Fls_Global.jobChunkSize = Fls_Global.config->FlsMaxReadNormalMode;
    }

    return E_OK;
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
    Fls_Global.ramAddr = (uint8*)TargetAddressPtr; /*lint !e9005 !e926 Would make core more complex. IMPROVMENT: Remove cast */
    Fls_Global.length = Length;

    if( Fls_Global.mode == MEMIF_MODE_FAST ) {
        Fls_Global.jobChunkSize = Fls_Global.config->FlsMaxReadFastMode;
    } else {
        Fls_Global.jobChunkSize = Fls_Global.config->FlsMaxReadNormalMode;
    }

    return E_OK;
}
#endif

#if ( FLS_SET_MODE_API == STD_ON )
void Fls_SetMode(MemIf_ModeType Mode) {

    VALIDATE_NO_RV( ( Fls_Global.status != MEMIF_UNINIT ), FLS_SET_MODE_ID, FLS_E_UNINIT);
    /* @req SWS_Fls_00156 */
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
    VALIDATE_NO_RV( ( NULL != VersioninfoPtr ), FLS_GET_VERSION_INFO_ID, FLS_E_PARAM_POINTER);

    VersioninfoPtr->vendorID = FLS_VENDOR_ID;
    VersioninfoPtr->moduleID = FLS_MODULE_ID;
    VersioninfoPtr->sw_major_version = FLS_SW_MAJOR_VERSION;
    VersioninfoPtr->sw_minor_version = FLS_SW_MINOR_VERSION;
    VersioninfoPtr->sw_patch_version = FLS_SW_PATCH_VERSION;

}
#endif

