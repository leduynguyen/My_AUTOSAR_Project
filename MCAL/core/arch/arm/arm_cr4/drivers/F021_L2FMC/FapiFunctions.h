/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 © Copyright 2009-2012 Texas Instruments Incorporated.  All rights reserved.
 *
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *      Project:  Hercules™ ARM® Safety MCUs - F021 Flash API 
 *      Version:  v2.01.01 Build(000830)                                                                                
 *   Build Date:  2014-10-21                                                                                            
 *
 *         File:  FapiFunctions.h                                                                                       
 *
 *  Description:  All the FAPI function extern definitions.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  John R Hall
 *---------------------------------------------------------------------------------------------------------------------
 *
 *********************************************************************************************************************/


#ifndef FAPI_FUNCTIONS_H_
#define FAPI_FUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Flash C API functions*/

/* Flash State Machine commands */
extern Fapi_StatusType Fapi_enableMainBankSectors(uint16_t u16SectorsEnables);

extern Fapi_StatusType Fapi_enableEepromBankSectors(
                                                    uint32_t u32SectorsEnables_31_0, 
                                                    uint32_t u32SectorsEnables_63_32
                                                   );

extern Fapi_StatusType Fapi_enableFsmDoneEvent(void);

extern Fapi_StatusType Fapi_disableFsmDoneEvent(void);

extern Fapi_StatusType Fapi_initializeFlashBanks(uint32_t u32HclkFrequency);

extern Fapi_StatusType Fapi_setActiveFlashBank(Fapi_FlashBankType oNewFlashBank);

extern Fapi_StatusType Fapi_enableBanksForOtpWrite(uint8_t u8Banks);

extern Fapi_StatusType Fapi_disableBanksForOtpWrite(void);

/* Functions only available on devices with L2FMC Flash controllers */
#if defined(_L2FMC) 

extern Fapi_StatusType Fapi_enableAutoEccCalculation(void);
extern Fapi_StatusType Fapi_disableAutoEccCalculation(void);

#endif  /* defined(_L2FMC) */

extern void Fapi_flushPipeline(void);

extern uint32_t* Fapi_remapEccAddress(uint32_t u32EccAddress);

extern uint32_t Fapi_remapMainAddress(uint32_t u32MainAddress);

extern boolean_t Fapi_isAddressEcc(uint32_t u32Address);

extern boolean_t Fapi_isAddressEEPROM(uint32_t u32Address);

/* Async Commands */
extern Fapi_StatusType Fapi_issueAsyncCommandWithAddress(
                                                         Fapi_FlashStateCommandsType oCommand,
                                                         uint32_t* pu32StartAddress
                                                        );

extern Fapi_StatusType Fapi_issueAsyncCommand(Fapi_FlashStateCommandsType oCommand);

/* Info Commands */
extern Fapi_LibraryInfoType Fapi_getLibraryInfo(void);
extern Fapi_DeviceInfoType Fapi_getDeviceInfo(void);
extern Fapi_StatusType Fapi_getBankSectors(
                                           Fapi_FlashBankType oBank, 
                                           Fapi_FlashBankSectorsType* poFlashBankSectors 
                                          );
extern uint32_t Fapi_getNumberOfBankSectors( uint32_t u32Bank);
/* Read commands */
extern Fapi_StatusType Fapi_doBlankCheck(
                                         uint32_t* pu32StartAddress,
                                         uint32_t u32Length,
                                         Fapi_FlashStatusWordType* poFlashStatusWord
                                        );

extern Fapi_StatusType Fapi_doMarginRead(
                                         uint32_t* pu32StartAddress,
                                         uint32_t* pu32ReadBuffer,
                                         uint32_t u32Length,
                                         Fapi_FlashReadMarginModeType oReadMode
                                        );

extern Fapi_StatusType Fapi_doVerify(
                                     uint32_t* pu32StartAddress,
                                     uint32_t u32Length,
                                     uint32_t* pu32CheckValueBuffer,
                                     Fapi_FlashStatusWordType* poFlashStatusWord
                                    );

extern uint32_t Fapi_calculatePsa(
                                uint32_t* pu32StartAddress,
                                uint32_t u32Length,
                                uint32_t u32PsaSeed,
                                Fapi_FlashReadMarginModeType oReadMode
                               );

extern Fapi_StatusType Fapi_doPsaVerify(
                                        uint32_t* pu32StartAddress,
                                        uint32_t u32Length,
                                        uint32_t u32PsaValue,
                                        Fapi_FlashStatusWordType* poFlashStatusWord
                                       );

extern Fapi_StatusType Fapi_doBlankCheckByByte(
                                               uint8_t* pu8StartAddress,
                                               uint32_t u32Length,
                                               Fapi_FlashStatusWordType* poFlashStatusWord
                                              );

extern Fapi_StatusType Fapi_doMarginReadByByte(
                                               uint8_t* pu8StartAddress,
                                               uint8_t* pu8ReadBuffer,
                                               uint32_t u32Length,
                                               Fapi_FlashReadMarginModeType oReadMode
                                              );

extern Fapi_StatusType Fapi_doVerifyByByte(
                                           uint8_t* pu8StartAddress,
                                           uint32_t u32Length,
                                           uint8_t* pu8CheckValueBuffer,
                                           Fapi_FlashStatusWordType* poFlashStatusWord
                                          );

/* Programming Commands */
extern Fapi_StatusType Fapi_issueProgrammingCommand(
                                                    uint32_t* pu32StartAddress,
                                                    uint8_t*  pu8DataBuffer,
                                                    uint8_t   u8DataBufferSizeInBytes,
                                                    uint8_t*  pu8EccBuffer,
                                                    uint8_t   u8EccBufferSizeInBytes,
                                                    Fapi_FlashProgrammingCommandsType oMode
                                                   );

extern Fapi_StatusType Fapi_issueProgrammingCommandForEccAddresses(
                                                                   uint32_t* pu32StartAddress,
                                                                   uint8_t*  pu8EccBuffer,
                                                                   uint8_t   u8EccBufferSizeInBytes
                                                                  );

/* Utility Commands */
extern Fapi_StatusType Fapi_waitDelay(volatile uint32_t u32WaitDelay);

extern uint32_t Fapi_calculateFletcherChecksum(
                                             uint32_t u32Address,
                                             uint32_t u32Length
                                            );

extern uint8_t Fapi_calculateEcc(
                               uint32_t u32Address,
                               uint64_t u64Data
                              );

/* User Defined Functions */
extern Fapi_StatusType Fapi_serviceWatchdogTimer(void);

#ifdef __cplusplus
}
#endif

#endif /*FAPI_FUNCTIONS_H_*/

/**********************************************************************************************************************
 *  END OF FILE: FapiFunctions.h
 *********************************************************************************************************************/
