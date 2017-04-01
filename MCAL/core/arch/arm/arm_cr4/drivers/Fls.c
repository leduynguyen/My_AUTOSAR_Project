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
#include "Fls.h"

#ifdef CFG_TMS570LC43X
#define _L2FMC
#include "F021_L2FMC/F021.h"
#else
#include "F021/F021.h"
#endif
#include "MemIf_Types.h"
#include "Mcu.h"
#include "math.h"
#if defined(USE_DEM)
#include "Dem.h"
#endif
#if defined(USE_DET)
#include "Det.h"
#endif



/** @tagSettings DEFAULT_ARCHITECTURE=TMS570 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */


#if FLS_DEV_ERROR_DETECT==STD_ON
    #define VALIDATE(_exp, _apiid, _errid) \
        if (!(_exp)) { \
            Det_ReportError(FLS_MODULE_ID, 0, _apiid, _errid); \
            return; \
        }
    #define VALIDATE_W_RV(_exp, _apiid, _errid, _rv) \
        if (!(_exp)) { \
            Det_ReportError(FLS_MODULE_ID, 0, _apiid, _errid); \
            return _rv; \
        }
#else
    #define VALIDATE(_exp, _apiid, _errid)
    #define VALIDATE_W_RV(_exp, _apiid, _errid, _rv)
#endif

#if defined(USE_DEM)
    #define DEM_ERROR(_err) Dem_ReportErrorStatus(_err, DEM_EVENT_STATUS_FAILED);
#else
    #define DEM_ERROR(_err)
#endif

#define EEPROM_BANK				(7)
#define EEPROM_BASE				(0xF0200000)
#if defined(CFG_TMS570LC43X)
#define EEPROM_UPPER			(0xF021FFFF)
#define SECTOR_SIZE				(0x1000) //4 kilobytes
#define PAGE_SIZE				(0x8) //8 bytes
#define PAGE_WIDE_SIZE			(PAGE_SIZE)
#else
#define EEPROM_UPPER			(0xF020FFFF)
#define SECTOR_SIZE				(0x4000) //16 kilobytes
#define PAGE_SIZE				(0xE) //16 bytes
#define PAGE_WIDE_SIZE			(PAGE_SIZE + 2) //+ 2 byte checksum*/
#endif

#define ADDRESS8(_addr) ((uint8*)(FLS_BASE_ADDRESS + EEPROM_BASE + _addr))
#define ADDRESS32(_addr) ((uint32*)(FLS_BASE_ADDRESS + EEPROM_BASE + _addr))
#define ADDRESS_BETWEEN(_addr, _lower, _upper) ((uint8*)_addr >= (uint8*)_lower && (uint8*)_addr <= (uint8*)_upper)
#define ADDRESS_ALIGNED(_addr, _lower, _upper, _align) (ADDRESS_BETWEEN(_addr, _lower, _upper) && \
                                                    ((uintptr_t)(const void*)(_addr - _lower) % _align == 0))
#define LENGTH_WITH_ECC(_length) (_length + ((_length / PAGE_WIDE_SIZE) * 2 + (_length % PAGE_WIDE_SIZE > 0 ? 2 : 0)))

typedef enum {
    FLS_JOB_NONE, FLS_JOB_COMPARE, FLS_JOB_ERASE, FLS_JOB_READ, FLS_JOB_WRITE,
} Fls_Arc_JobType;

const Fls_ConfigType* FlsConfig;

MemIf_StatusType	moduleStatus = MEMIF_UNINIT;
MemIf_JobResultType flsJobResult;
Fls_Arc_JobType		pendingJob;

Fls_AddressType jobAddress;
Fls_LengthType jobLength;
uint8* jobPtr;

Fls_AddressType queueAddress;
Fls_LengthType queueLength;
uint8* queuePtr;

static void ReportFlsError(void);
static Std_ReturnType Internal_WriteQueued(void);
static Std_ReturnType Internal_EraseQueued(void);
static void Fls_Setup(void);

void Fls_MainFunction(void)
{
    if (flsJobResult == MEMIF_JOB_PENDING) {
        if (FAPI_CHECK_FSM_READY_BUSY == Fapi_Status_FsmBusy)
        {
            return; //Module busy. Do nothing
        }
        else
        {
            if (FAPI_GET_FSM_STATUS == 0)
            {
                //Operation success, flash unlocked
                if (queuePtr != 0) {
                    //A write job that has at least one more chunk
                    if (Internal_WriteQueued() != Fapi_Status_Success)
                    {
                        ReportFlsError();
                    }
                }
                else if (queuePtr == 0 && queueLength > 0 && pendingJob == FLS_JOB_ERASE)
                {
                    //An erase job has at least one more chunk. It doesn't use the pointer
                    if (Internal_EraseQueued() != Fapi_Status_Success)
                    {
                        ReportFlsError();
                    }
                }
                else
                {
                    pendingJob = FLS_JOB_NONE;
                    flsJobResult = MEMIF_JOB_OK;
                    moduleStatus = MEMIF_IDLE;
                }
            }
            else
            {
                //Something went wrong
                ReportFlsError();

            }
        }
    }
}

void ReportFlsError(void) {
    switch (pendingJob) {
    case FLS_JOB_ERASE:
        DEM_ERROR(DemConf_DemEventParameter_FLS_E_ERASE_FAILED);
        break;
    case FLS_JOB_WRITE:
        DEM_ERROR(DemConf_DemEventParameter_FLS_E_WRITE_FAILED);
        break;
    case FLS_JOB_READ:
        DEM_ERROR(DemConf_DemEventParameter_FLS_E_READ_FAILED);
        break;
    case FLS_JOB_COMPARE:
        DEM_ERROR(DemConf_DemEventParameter_FLS_E_COMPARE_FAILED);
        break;
    case FLS_JOB_NONE:
        break;
    }
    flsJobResult = MEMIF_JOB_FAILED;
    moduleStatus = MEMIF_IDLE;
}

static void Fls_Setup(void)
{
    uint32_t clk = Mcu_Arc_GetPeripheralClock(PERIPHERAL_CLOCK_FLASH);
    //MCU returns frequency in Hz, the API needs it in MHz
    //First division is by 100kHz with another operation then for rounding
    //API requires frequency in MHz to be rounded up, so 133.3 MHz -> 134
    clk /= 100000;
    clk = (uint32_t)ceil(clk / 10.0);
    Fapi_StatusType ret = Fapi_initializeFlashBanks(clk);
    (void)ret;
    ret = Fapi_setActiveFlashBank(EEPROM_BANK);
    ret = Fapi_enableEepromBankSectors(0xFFFFFFFF, 0xFFFFFFFF);
    while(FAPI_CHECK_FSM_READY_BUSY != Fapi_Status_FsmReady){};
}

void Fls_Init(const Fls_ConfigType* ConfigPtr) {
    // @req SWS_Fls_00268
    VALIDATE(moduleStatus != MEMIF_BUSY, FLS_INIT_ID, FLS_E_BUSY);
    // @req SWS_Fls_00014
    FlsConfig = ConfigPtr;
    uint32_t clk = Mcu_Arc_GetPeripheralClock(PERIPHERAL_CLOCK_FLASH);
    //MCU returns frequency in Hz, the API needs it in MHz
    //First division is by 100kHz with another operation then for rounding
    //API requires frequency in MHz to be rounded up, so 133.3 MHz -> 134
    clk /= 100000;
    clk = (uint32_t)ceil(clk / 10.0);
    Fapi_StatusType ret = Fapi_initializeFlashBanks(clk);
    (void)ret;
    ret = Fapi_setActiveFlashBank(EEPROM_BANK);
    ret = Fapi_enableEepromBankSectors(0xFFFFFFFF, 0xFFFFFFFF);
    while(FAPI_CHECK_FSM_READY_BUSY != Fapi_Status_FsmReady){};

    queuePtr = 0;

    moduleStatus = MEMIF_IDLE;
    flsJobResult = MEMIF_JOB_OK;
}

// @req SWS_Fls_00250
Std_ReturnType Fls_Erase(Fls_AddressType TargetAddress, Fls_LengthType Length) {
    // @req SWS_Fls_00065
    VALIDATE_W_RV((moduleStatus != MEMIF_UNINIT), FLS_ERASE_ID, FLS_E_UNINIT, E_NOT_OK);
    // @req SWS_Fls_00023
    VALIDATE_W_RV((moduleStatus != MEMIF_BUSY), FLS_ERASE_ID, FLS_E_BUSY, E_NOT_OK);
    // @req SWS_Fls_00020
    VALIDATE_W_RV((ADDRESS_ALIGNED(ADDRESS32(TargetAddress),
                EEPROM_BASE, EEPROM_UPPER, SECTOR_SIZE)), FLS_ERASE_ID, FLS_E_PARAM_ADDRESS, E_NOT_OK);
    // @req SWS_Fls_00021
    VALIDATE_W_RV((Length > 0 && ADDRESS_ALIGNED(ADDRESS32(TargetAddress + Length),
                    EEPROM_BASE, EEPROM_UPPER, SECTOR_SIZE)), FLS_ERASE_ID, FLS_E_PARAM_LENGTH, E_NOT_OK);
    // @req SWS_Fls_00327
    jobAddress = TargetAddress;
    jobLength = Length;

    if (jobLength > SECTOR_SIZE)
    {
        queueAddress = jobAddress + SECTOR_SIZE;
        queueLength = jobLength - SECTOR_SIZE;
    }
    Fls_Setup();

    // @req SWS_Fls_00220
    // @req SWS_Fls_00221
    Fapi_StatusType ret = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector, ADDRESS32(jobAddress));
    if (ret != Fapi_Status_Success)
    {
        return E_NOT_OK;
    }

    // @req SWS_Fls_00328
    moduleStatus = MEMIF_BUSY;
    // @req SWS_Fls_00329
    flsJobResult = MEMIF_JOB_PENDING;
    pendingJob = FLS_JOB_ERASE;
    // @req SWS_Fls_00330
    return E_OK;
}

static Std_ReturnType Internal_EraseQueued( void )
{
    jobLength = (queueLength > SECTOR_SIZE) ? SECTOR_SIZE : queueLength;
    Fls_Setup();
    Fapi_StatusType ret = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector, ADDRESS32(queueAddress));
    if (ret != Fapi_Status_Success) {
        queuePtr = 0;
        return E_NOT_OK ;
    }
    if (queueLength >= SECTOR_SIZE)
    {
        queueAddress += SECTOR_SIZE;
        queueLength -= SECTOR_SIZE;
    }
    if (queueLength <= 0) {
        //No more chunks to be written, FLS module will be ready after this write
        queueLength = 0;
        queuePtr = 0;
    }
    return E_OK;
}

Std_ReturnType Fls_Write(Fls_AddressType TargetAddress, const uint8* SourceAddressPtr,
                        Fls_LengthType Length) {

    // @req SWS_Fls_00066
    VALIDATE_W_RV((moduleStatus != MEMIF_UNINIT), FLS_WRITE_ID, FLS_E_UNINIT, E_NOT_OK);
    // @req SWS_Fls_00030
    VALIDATE_W_RV((moduleStatus != MEMIF_BUSY), FLS_WRITE_ID, FLS_E_BUSY, E_NOT_OK);
    // @req SWS_Fls_00157
        VALIDATE_W_RV((SourceAddressPtr != NULL), FLS_WRITE_ID, FLS_E_PARAM_DATA, E_NOT_OK);
    // @req SWS_Fls_00026
    VALIDATE_W_RV((ADDRESS_ALIGNED(ADDRESS32(TargetAddress),
            EEPROM_BASE, EEPROM_UPPER, PAGE_WIDE_SIZE)), FLS_WRITE_ID, FLS_E_PARAM_ADDRESS, E_NOT_OK);
    // @req SWS_Fls_00027
    VALIDATE_W_RV((Length > 0 && ADDRESS_ALIGNED(ADDRESS32(TargetAddress + /*LENGTH_WITH_ECC*/(Length)),
                EEPROM_BASE, EEPROM_UPPER, PAGE_WIDE_SIZE)), FLS_WRITE_ID, FLS_E_PARAM_LENGTH, E_NOT_OK);

    jobAddress = TargetAddress;
    //Here both Autosar and F021 API specify the length in bytes, so jobLength == Length,
    //unlike in Fls_Read
    jobLength = Length;
    jobPtr = (uint8_t *) SourceAddressPtr;
    Fls_Setup();

    if (jobLength > PAGE_WIDE_SIZE) {
        queueLength = (jobLength) - (PAGE_WIDE_SIZE);
        queueAddress = jobAddress + (PAGE_WIDE_SIZE);
        queuePtr = jobPtr + (PAGE_WIDE_SIZE);
        jobLength = PAGE_WIDE_SIZE;
    }

    Fapi_StatusType ret = Fapi_issueProgrammingCommand(ADDRESS32(jobAddress), jobPtr, (uint8)jobLength, 0, 0, Fapi_AutoEccGeneration);
    if (ret != Fapi_Status_Success) return E_NOT_OK;

    // @req SWS_Fls_00332
    moduleStatus = MEMIF_BUSY;
    // @req SWS_Fls_00333
    flsJobResult = MEMIF_JOB_PENDING;
    pendingJob = FLS_JOB_WRITE;

    //@req SWS_Fls_00334
    return E_OK;
}

static Std_ReturnType Internal_WriteQueued()
{
    jobLength = (queueLength > PAGE_WIDE_SIZE) ? (PAGE_WIDE_SIZE) : jobLength;
    Fls_Setup();
    Fapi_StatusType ret = Fapi_issueProgrammingCommand(ADDRESS32(queueAddress), queuePtr, (uint8)jobLength, 0, 0, Fapi_AutoEccGeneration);
    if (ret != Fapi_Status_Success) {
        queuePtr = 0;
        return E_NOT_OK;
    }
    if (queueLength > 0) {
        queueAddress += (PAGE_WIDE_SIZE);
        queuePtr += (PAGE_WIDE_SIZE);
        queueLength -= (PAGE_WIDE_SIZE);
    }

    if (queueLength <= 0) {
        //No more chunks to be written, FLS module will be ready after this write
        queueLength = 0;
        queuePtr = 0;
    }


    return E_OK;
}

Std_ReturnType Fls_Read(Fls_AddressType SourceAddress, uint8* TargetAddressPtr, Fls_LengthType Length)
{
    VALIDATE_W_RV((ADDRESS_BETWEEN(ADDRESS8(SourceAddress), EEPROM_BASE, EEPROM_UPPER)), FLS_READ_ID, FLS_E_PARAM_ADDRESS, E_NOT_OK);
    VALIDATE_W_RV((Length > 0), FLS_READ_ID, FLS_E_PARAM_LENGTH, E_NOT_OK);
    VALIDATE_W_RV((ADDRESS_BETWEEN(ADDRESS8(SourceAddress + Length), EEPROM_BASE, EEPROM_UPPER)), FLS_READ_ID, FLS_E_PARAM_LENGTH, E_NOT_OK);
    VALIDATE_W_RV((moduleStatus != MEMIF_UNINIT), FLS_READ_ID, FLS_E_UNINIT, E_NOT_OK);
    VALIDATE_W_RV((NULL != TargetAddressPtr), FLS_READ_ID, FLS_E_PARAM_DATA, E_NOT_OK);
    // @req SWS_Fls_00100
    VALIDATE_W_RV((moduleStatus != MEMIF_BUSY), FLS_READ_ID, FLS_E_BUSY, E_NOT_OK);
    jobAddress = SourceAddress;
    jobPtr = TargetAddressPtr;
    //Autosar Fls_Read API has Length parameter defined as number of bytes to read
    //F021 Flash API has parameter Length defined as amount of 8-bit words to read
    jobLength = Length;

    Fapi_StatusType ret = Fapi_doMarginReadByByte(ADDRESS8(jobAddress), jobPtr, jobLength, Fapi_NormalRead);
    if (ret != Fapi_Status_Success) return E_NOT_OK;
    flsJobResult = MEMIF_JOB_PENDING;
    moduleStatus = MEMIF_BUSY;
    pendingJob = FLS_JOB_READ;

    return E_OK;
}

Std_ReturnType Fls_Compare(Fls_AddressType SourceAddress, const uint8* TargetAddressPtr, Fls_LengthType Length)
{
    // @req SWS_Fls_00152
    VALIDATE_W_RV((moduleStatus != MEMIF_UNINIT), FLS_COMPARE_ID, FLS_E_UNINIT, E_NOT_OK);
    // @req SWS_Fls_00153
    VALIDATE_W_RV((moduleStatus != MEMIF_BUSY), FLS_COMPARE_ID, FLS_E_BUSY, E_NOT_OK);
    // @req SWS_Fls_00273
    VALIDATE_W_RV((TargetAddressPtr != NULL), FLS_COMPARE_ID, FLS_E_PARAM_DATA, E_NOT_OK);
    // @req SWS_Fls_00150
    VALIDATE_W_RV((ADDRESS_BETWEEN(ADDRESS32(SourceAddress), EEPROM_BASE, EEPROM_UPPER)), FLS_COMPARE_ID, FLS_E_PARAM_ADDRESS, E_NOT_OK);
    // @req SWS_Fls_00151
    VALIDATE_W_RV((Length > 0 && ADDRESS_BETWEEN(ADDRESS32(SourceAddress + Length), EEPROM_BASE, EEPROM_UPPER)), FLS_COMPARE_ID, FLS_E_PARAM_LENGTH, E_NOT_OK);
    // @req SWS_Fls_00341
    jobAddress = SourceAddress;
    jobPtr = (uint8_t *) TargetAddressPtr;
    jobLength = Length;

    Fapi_FlashStatusWordType statusWord;

    // @req SWS_Fls_00243
    // @req SWS_Fls_00244
    Fls_Setup();
    Fapi_StatusType ret = Fapi_doVerifyByByte(ADDRESS8(jobAddress), jobLength, jobPtr, &statusWord);
    if (ret != Fapi_Status_Success) return E_NOT_OK;

    // @req SWS_Fls_00343
    flsJobResult = MEMIF_JOB_PENDING;
    // @req SWS_Fls_00342
    moduleStatus = MEMIF_BUSY;
    pendingJob = FLS_JOB_COMPARE;

    // @req SWS_Fls_00344

    return E_OK;
}

void Fls_Cancel(void) {
    //Not supported
}

// @req SWS_Fls_00184
#if (STD_ON == FLS_GET_STATUS_API)
MemIf_StatusType Fls_GetStatus(void)
{
    // No validation needed, this may be called before initialization
    // @req SWS_Fls_00034
    return moduleStatus;
}
#endif

// @req SWS_Fls_00185
#if (STD_ON == FLS_GET_JOB_RESULT_API)
MemIf_JobResultType Fls_GetJobResult(void)
{
    // @req Sws_Fls_00358
    VALIDATE_W_RV((moduleStatus != MEMIF_UNINIT), FLS_GET_JOB_RESULT_ID, FLS_E_UNINIT, MEMIF_JOB_FAILED);
    // @req SWS_Fls_00035
    // @req SWS_Fls_00036
    return flsJobResult;
}
#endif

Fapi_StatusType Fapi_serviceWatchdogTimer(void)
{
    return Fapi_Status_Success;
}

Fapi_StatusType F021_BlankCheck(Fls_AddressType Address, Fls_LengthType Length)
{
    Fapi_FlashStatusWordType word;
    return Fapi_doBlankCheck(ADDRESS32(Address), Length / 4, &word);
}
