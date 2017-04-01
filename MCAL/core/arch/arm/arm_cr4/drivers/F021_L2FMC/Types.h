/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 � Copyright 2009-2012 Texas Instruments Incorporated.  All rights reserved.
 *
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *      Project:  Hercules� ARM� Safety MCUs - F021 Flash API 
 *      Version:  v2.01.01 Build(000830)                                                                                
 *   Build Date:  2014-10-21                                                                                            
 *
 *         File:  Types.h                                                                                               
 *
 *  Description:  Types used by the F021 API.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  John R Hall
 *---------------------------------------------------------------------------------------------------------------------
 *
 *********************************************************************************************************************/


#ifndef TYPES_H_
#define TYPES_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
/*LDRA_NOANALYSIS*/
#include <stdint.h>
#include <stddef.h>
/*LDRA_ANALYSIS*/

#if defined(__TI_COMPILER_VERSION__)   /* TI CCS Compiler */
#include "CGT.CCS.h"
#elif defined(__ICCARM__)              /* IAR EWARM Compiler */
#include "CGT.IAR.h"
#elif defined(__ghs__)                 /* GreenHills Compiler */
#include "CGT.GHS.h"
#elif defined(__ARMCC_VERSION)         /* ARM Compiler */
#include "CGT.ARM.h"
#elif defined(__GNUC__)                /* gcc Compiler */
#include "CGT.gcc.h"
#else
#error "A valid code generation compiler type was not determined!"
#endif

#if !defined(_LITTLE_ENDIAN) && !defined(_BIG_ENDIAN)
#error "Target Endianess is not defined"
#endif


/*****************************************************************************/
/* GLOBAL DEFINITIONS                                                        */
/*****************************************************************************/
#if !defined(HIGH_BYTE_FIRST)
#define HIGH_BYTE_FIRST     0U
#endif

#if !defined(LOW_BYTE_FIRST)
#define LOW_BYTE_FIRST      1U
#endif

#if !defined(CPU_BYTE_ORDER)
#if defined(_LITTLE_ENDIAN)
   #define CPU_BYTE_ORDER    (LOW_BYTE_FIRST)
#else
   #define CPU_BYTE_ORDER    (HIGH_BYTE_FIRST)
#endif
#endif

#if !defined(false)
#define false	0U
#endif
#if !defined(true)
#define true	1U
#endif

/*****************************************************************************/
/* TYPE DEFINITIONS                                                          */
/*****************************************************************************/
typedef unsigned char boolean_t;

/*!
    \brief This is used to indicate which Cpu is being used.
*/
typedef enum
{
   Fapi_MasterCpu,
   Fapi_SlaveCpu0
}  ATTRIBUTE_PACKED Fapi_CpuSelectorType;

/*!
    \brief This is used to indicate what type of Cpu is being used.
*/
typedef enum
{
   ARM7 = 0U,  /* ARM7 core, Legacy placeholder */
   M3   = 1U,  /* ARM Cortex M3 core */
   R4   = 2U,  /* ARM Cortex R4 core without ECC logic */
   R4F  = 3U,  /* ARM Cortex R4, R4F, and R5 cores with ECC logic*/
   C28  = 4U,  /* TI C28x core */
   Undefined1 = 5U,  /* To Be Determined.  Future core placeholder */
   Undefined2 = 6U,  /* To Be Determined.  Future core placeholder */
   Undefined3 = 7U   /* To Be Determined.  Future core placeholder */
}  ATTRIBUTE_PACKED Fapi_CpuType;

/*!
    \brief This is used to indicate what type of Family is being used.
*/
typedef enum
{
   Family_FMC       = 0x00,
   Family_L2FMC     = 0x10,
   Family_Sonata    = 0x20,
   Family_Stellaris = 0x30,
   Family_Future    = 0x40
} ATTRIBUTE_PACKED Fapi_FamilyType;

/*!
    \brief This is used to indicate what type of Address is being used.
*/
typedef enum
{
   Fapi_Flash,
   Fapi_FlashEcc,
   Fapi_Otp,
   Fapi_OtpEcc,
   Fapi_Undefined
}  ATTRIBUTE_PACKED Fapi_AddressMemoryType;

/*!
    \brief This is used to return the information from the engineering row in the TI OTP.
*/
typedef struct
{
   uint32_t u32AsicId;
   uint8_t  u8Revision;
   uint32_t u32LotNumber;
   uint16_t u16FlowCheck;
   uint16_t u16WaferNumber;
   uint16_t u16XCoordinate;
   uint16_t u16YCoordinate;
}  ATTRIBUTE_PACKED Fapi_EngineeringRowType;

typedef struct
{
   uint32_t au32StatusWord[4];
}  ATTRIBUTE_PACKED Fapi_FlashStatusWordType;

/*!
    \brief This contains all the possible modes used in the Fapi_IssueAsyncProgrammingCommand().
*/
typedef enum
{
   Fapi_AutoEccGeneration, /* This is the default mode for the command and will auto generate the ECC for the 
                              provided data buffer */
   Fapi_DataOnly,          /* Command will only process the data buffer */
   Fapi_EccOnly,           /* Command will only process the ecc buffer */
   Fapi_DataAndEcc         /* Command will process data and ecc buffers */
}  ATTRIBUTE_PACKED Fapi_FlashProgrammingCommandsType;

/*!
    \brief This is used to indicate which Flash bank is being used.
*/
typedef enum
{
   Fapi_FlashBank0=0,
   Fapi_FlashBank1=1,
   Fapi_FlashBank2=2,
   Fapi_FlashBank3=3,
   Fapi_FlashBank4=4,
   Fapi_FlashBank5=5,
   Fapi_FlashBank6=6,
   Fapi_FlashBank7=7
}  ATTRIBUTE_PACKED Fapi_FlashBankType;

/*!
    \brief This is used to indicate what F021 Bank Technology the bank is
*/
typedef enum
{
    Fapi_FLEP=0,
    Fapi_FLEE=1,
    Fapi_FLES=2,
    Fapi_FLHV=3
}  ATTRIBUTE_PACKED Fapi_FlashBankTechType;

/*!
    \brief This is used to indicate which Flash sector is being used.
*/
typedef enum
{
   Fapi_FlashSector0,
   Fapi_FlashSector1,
   Fapi_FlashSector2,
   Fapi_FlashSector3,
   Fapi_FlashSector4,
   Fapi_FlashSector5,
   Fapi_FlashSector6,
   Fapi_FlashSector7,
   Fapi_FlashSector8,
   Fapi_FlashSector9,
   Fapi_FlashSector10,
   Fapi_FlashSector11,
   Fapi_FlashSector12,
   Fapi_FlashSector13,
   Fapi_FlashSector14,
   Fapi_FlashSector15,
   Fapi_FlashSector16,
   Fapi_FlashSector17,
   Fapi_FlashSector18,
   Fapi_FlashSector19,
   Fapi_FlashSector20,
   Fapi_FlashSector21,
   Fapi_FlashSector22,
   Fapi_FlashSector23,
   Fapi_FlashSector24,
   Fapi_FlashSector25,
   Fapi_FlashSector26,
   Fapi_FlashSector27,
   Fapi_FlashSector28,
   Fapi_FlashSector29,
   Fapi_FlashSector30,
   Fapi_FlashSector31,
   Fapi_FlashSector32,
   Fapi_FlashSector33,
   Fapi_FlashSector34,
   Fapi_FlashSector35,
   Fapi_FlashSector36,
   Fapi_FlashSector37,
   Fapi_FlashSector38,
   Fapi_FlashSector39,
   Fapi_FlashSector40,
   Fapi_FlashSector41,
   Fapi_FlashSector42,
   Fapi_FlashSector43,
   Fapi_FlashSector44,
   Fapi_FlashSector45,
   Fapi_FlashSector46,
   Fapi_FlashSector47,
   Fapi_FlashSector48,
   Fapi_FlashSector49,
   Fapi_FlashSector50,
   Fapi_FlashSector51,
   Fapi_FlashSector52,
   Fapi_FlashSector53,
   Fapi_FlashSector54,
   Fapi_FlashSector55,
   Fapi_FlashSector56,
   Fapi_FlashSector57,
   Fapi_FlashSector58,
   Fapi_FlashSector59,
   Fapi_FlashSector60,
   Fapi_FlashSector61,
   Fapi_FlashSector62,
   Fapi_FlashSector63
}  ATTRIBUTE_PACKED Fapi_FlashSectorType;

/*!
    \brief This contains all the possible Flash State Machine commands.
*/
typedef enum
{
   Fapi_ProgramData    = 0x0002,
   Fapi_EraseSector    = 0x0006,
   Fapi_EraseBank      = 0x0008,
   Fapi_ValidateSector = 0x000E,
   Fapi_ClearStatus    = 0x0010,
   Fapi_ProgramResume  = 0x0014,
   Fapi_EraseResume    = 0x0016,
   Fapi_ClearMore      = 0x0018
}  ATTRIBUTE_PACKED Fapi_FlashStateCommandsType;

/*LDRA_INSPECTED 495 S MR: 6.3 "This does have a size indicated.  LDRA is incorrect" */
typedef  uint32_t Fapi_FlashStatusType;

/*!
    \brief This contains all the possible Flash State Machine commands.
*/
typedef enum
{
   Fapi_NormalRead = 0x0,
   Fapi_RM0        = 0x1,
   Fapi_RM1        = 0x2
}  ATTRIBUTE_PACKED Fapi_FlashReadMarginModeType;

/*!
    \brief This is the master type containing all possible returned status codes.
*/
typedef enum
{
   Fapi_Status_Success=0,           /* Function completed successfully */
   Fapi_Status_FsmBusy,             /* FSM is Busy */
   Fapi_Status_FsmReady,            /* FSM is Ready */
   Fapi_Error_Fail,                 /* Generic Function Fail code */
   Fapi_Error_NullPointer,          /* One of the pointer parameters is a null pointer */
   Fapi_Error_InvalidCommand,       /* Command used is invalid for the function called */
   Fapi_Error_InvalidEccAddress,    /* Returned if the ECC Address given to a function is invalid for that function */
   Fapi_Error_OtpChecksumMismatch,  /* Returned if OTP checksum does not match expected value */
   Fapi_Error_InvalidHclkValue,     /* Returned if FClk is above max FClk value - FClk is a calculated from HClk and 
                                       RWAIT/EWAIT */
   Fapi_Error_InvalidBank,          /* Returned if the specified bank does not exist */
   Fapi_Error_InvalidAddress,       /* Returned if the specified Address does not exist in Flash or OTP */
   Fapi_Error_InvalidReadMode,      /* Returned if the specified read mode does not exist */
   Fapi_Error_AsyncIncorrectDataBufferLength,   /* Returned if Data buffer size specified exceeds Data bank width */
   Fapi_Error_AsyncIncorrectEccBufferLength,    /* Returned if ECC buffer size specified exceeds ECC bank width */
   Fapi_Error_AsyncDataEccBufferLengthMismatch, /* Returned if Data buffer size either is not 64bit aligned or Data
                                                   length exceeds amount ECC supplied */
   Fapi_Error_FeatureNotAvailable  /* FMC feature is not available on this device */
}  ATTRIBUTE_PACKED Fapi_StatusType;

/*LDRA_NOANALYSIS*/
/*LDRA_INSPECTED 42 S MR: 3.5 "Necessary for FMC register definitions" */
/*LDRA_INSPECTED 74 S MR: 18.4 "Necessary for FMC register definitions" */
#if defined(_LITTLE_ENDIAN)
typedef union
{
    volatile struct
   {
#if defined (_C28X)
      uint16_t ChecksumLength:16;  /* 0x150 bits 15:0 */
      uint16_t OtpVersion:16;      /* 0x150 bits 31:16 */
      uint32_t OtpChecksum;        /* 0x154 bits 31:0 */
      uint16_t NumberOfBanks:16;   /* 0x158 bits 15:0 */
      uint16_t NumberOfSectors:16; /* 0x158 bits 31:16 */
      uint16_t MemorySize:16;      /* 0x15C bits 15:0 */
      uint16_t Package:16;         /* 0x15C bits 31:16 */
      uint16_t SiliconRevision:8;  /* 0x160 bits 7:0 */
      uint16_t AsicNumber_23_8:8; /* 0x160 bits 31:8 */
      uint16_t AsicNumber_31_24:16; /* 0x160 bits 31:8 */
      uint32_t LotNumber;          /* 0x164 bits 31:0 */
      uint16_t WaferNumber:16;     /* 0x168 bits 15:0 */
      uint16_t Flowbits:16;        /* 0x168 bits 31:16 */
      uint16_t YCoordinate:16;     /* 0x16C bits 15:0 */
      uint16_t XCoordinate:16;     /* 0x16C bits 31:16 */
      uint16_t EVSU:8;             /* 0x170 bits 7:0 */
      uint16_t PVSU:8;             /* 0x170 bits 15:8 */
      uint16_t ESU:8;              /* 0x170 bits 23:16 */
      uint16_t PSU:8;              /* 0x170 bits 31:24 */
      uint16_t CVSU:12;            /* 0x174 bits 11:0 */
      uint16_t Add_EXEZSU:4;       /* 0x174 bits 15:12 */ 
      uint16_t PVAcc:8;            /* 0x174 bits 23:16 */
      uint16_t RVSU:8;             /* 0x174 bits 31:24 */
      uint16_t PVH2:8;             /* 0x178 bits 7:0 */
      uint16_t PVH:8;              /* 0x178 bits 15:8 */
      uint16_t RH:8;               /* 0x178 bits 23:16 */
      uint16_t PH:8;               /* 0x178 bits 31:24 */  
      uint16_t SmFrequency:12;     /* 0x17C bits 11:0 */
      uint16_t VSTAT:4;            /* 0x17C bits 15:12 */
      uint16_t Sequence:8;         /* 0x17C bits 23:16 */
      uint16_t EH:8;               /* 0x17C bits 31:24 */
      uint16_t VHV_EStep:16;       /* 0x180 bits 15:0 */
      uint16_t VHV_EStart:16;      /* 0x180 bits 31:16 */
      uint16_t MAX_PP:16;          /* 0x184 bits 15:0 */
      uint16_t OtpReserved1:16;    /* 0x184 bits 31:16 */
      uint16_t PROG_PW:16;         /* 0x188 bits 15:0 */
      uint16_t MAX_EP:16;          /* 0x188 bits 31:16 */
      uint32_t ERA_PW;             /* 0x18C bits 31:0 */
      uint16_t VHV_E:16;           /* 0x190 bits 15:0 */
      uint16_t VHV_P:16;           /* 0x190 bits 31:16 */
      uint16_t VINH:8;             /* 0x194 bits 7:0 */
      uint16_t VCG:8;              /* 0x194 bits 15:8 */
      uint16_t VHV_PV:16;          /* 0x194 bits 31:16 */
      uint16_t OtpReserved2:8;     /* 0x198 bits 7:0 */
      uint16_t VRead:8;            /* 0x198 bits 15:8 */
      uint16_t VWL_P:8;            /* 0x198 bits 23:16 */
      uint16_t VSL_P:8;            /* 0x198 bits 31:24 */
      uint32_t ApiChecksum;        /* 0x19C bits 15:0 */ 
      uint32_t OtpReserved3;    /* 0x1A0 bits 31:0 */
      uint32_t OtpReserved4;    /* 0x1A4 bits 31:0 */
      uint32_t OtpReserved5;    /* 0x1A8 bits 31:0 */
      uint32_t OtpReserved6;    /* 0x1AC bits 31:0 */       
#else
      uint32_t ChecksumLength:16;  /* 0x150 bits 15:0 */
      uint32_t OtpVersion:16;      /* 0x150 bits 31:16 */
      uint32_t OtpChecksum;        /* 0x154 bits 31:0 */
      uint32_t NumberOfBanks:16;   /* 0x158 bits 15:0 */
      uint32_t NumberOfSectors:16; /* 0x158 bits 31:16 */
      uint32_t MemorySize:16;      /* 0x15C bits 15:0 */
      uint32_t Package:16;         /* 0x15C bits 31:16 */
      uint32_t SiliconRevision:8;  /* 0x160 bits 7:0 */
      uint32_t AsicNumber:24;       /* 0x160 bits 31:8 */      
      uint32_t LotNumber;          /* 0x164 bits 31:0 */
      uint32_t WaferNumber:16;     /* 0x168 bits 15:0 */
      uint32_t Flowbits:16;        /* 0x168 bits 31:16 */
      uint32_t YCoordinate:16;     /* 0x16C bits 15:0 */
      uint32_t XCoordinate:16;     /* 0x16C bits 31:16 */
      uint32_t EVSU:8;             /* 0x170 bits 7:0 */
      uint32_t PVSU:8;             /* 0x170 bits 15:8 */
      uint32_t ESU:8;              /* 0x170 bits 23:16 */
      uint32_t PSU:8;              /* 0x170 bits 31:24 */
      uint32_t CVSU:12;            /* 0x174 bits 11:0 */
      uint32_t Add_EXEZSU:4;       /* 0x174 bits 15:12 */ 
      uint32_t PVAcc:8;            /* 0x174 bits 23:16 */
      uint32_t RVSU:8;             /* 0x174 bits 31:24 */
      uint32_t PVH2:8;             /* 0x178 bits 7:0 */
      uint32_t PVH:8;              /* 0x178 bits 15:8 */
      uint32_t RH:8;               /* 0x178 bits 23:16 */
      uint32_t PH:8;               /* 0x178 bits 31:24 */  
      uint32_t SmFrequency:12;     /* 0x17C bits 11:0 */
      uint32_t VSTAT:4;            /* 0x17C bits 15:12 */
      uint32_t Sequence:8;         /* 0x17C bits 23:16 */
      uint32_t EH:8;               /* 0x17C bits 31:24 */
      uint32_t VHV_EStep:16;       /* 0x180 bits 15:0 */
      uint32_t VHV_EStart:16;      /* 0x180 bits 31:16 */
      uint32_t MAX_PP:16;          /* 0x184 bits 15:0 */
      uint32_t OtpReserved1:16;    /* 0x184 bits 31:16 */
      uint32_t PROG_PW:16;         /* 0x188 bits 15:0 */
      uint32_t MAX_EP:16;          /* 0x188 bits 31:16 */
      uint32_t ERA_PW;             /* 0x18C bits 31:0 */
      uint32_t VHV_E:16;           /* 0x190 bits 15:0 */
      uint32_t VHV_P:16;           /* 0x190 bits 31:16 */
      uint32_t VINH:8;             /* 0x194 bits 7:0 */
      uint32_t VCG:8;              /* 0x194 bits 15:8 */
      uint32_t VHV_PV:16;          /* 0x194 bits 31:16 */
      uint32_t OtpReserved2:8;     /* 0x198 bits 7:0 */
      uint32_t VRead:8;            /* 0x198 bits 15:8 */
      uint32_t VWL_P:8;            /* 0x198 bits 23:16 */
      uint32_t VSL_P:8;            /* 0x198 bits 31:24 */
      uint32_t ApiChecksum:32;     /* 0x19C bits 31:0 */
      uint32_t OtpReserved3:32;    /* 0x1A0 bits 31:0 */
      uint32_t OtpReserved4:32;    /* 0x1A4 bits 31:0 */
      uint32_t OtpReserved5:32;    /* 0x1A8 bits 31:0 */
      uint32_t OtpReserved6:32;    /* 0x1AC bits 31:0 */
#endif        
   } OTP_VALUE;
   volatile uint8_t  au8OtpWord[0x60];
   volatile uint16_t au16OtpWord[0x30];
   volatile uint32_t au32OtpWord[0x18];
}Fapi_TiOtpBytesType;
#else
typedef union
{
    volatile struct
   {
      uint32_t OtpVersion:16;      /* 0x150 bits 31:16 */
      uint32_t ChecksumLength:16;  /* 0x150 bits 15:0 */
      uint32_t OtpChecksum;        /* 0x154 bits 31:0 */
      uint32_t NumberOfSectors:16; /* 0x158 bits 31:16 */
      uint32_t NumberOfBanks:16;   /* 0x158 bits 15:0 */
      uint32_t Package:16;         /* 0x15C bits 31:16 */
      uint32_t MemorySize:16;      /* 0x15C bits 15:0 */
      uint32_t AsicNumber:24;      /* 0x160 bits 31:8 */
      uint32_t SiliconRevision:8;  /* 0x160 bits 7:0 */
      uint32_t LotNumber;          /* 0x164 bits 31:0 */
      uint32_t Flowbits:16;        /* 0x168 bits 31:16 */
      uint32_t WaferNumber:16;     /* 0x168 bits 15:0 */
      uint32_t XCoordinate:16;     /* 0x16C bits 31:16 */
      uint32_t YCoordinate:16;     /* 0x16C bits 15:0 */
      uint32_t PSU:8;              /* 0x170 bits 31:24 */
      uint32_t ESU:8;              /* 0x170 bits 23:16 */
      uint32_t PVSU:8;             /* 0x170 bits 15:8 */
      uint32_t EVSU:8;             /* 0x170 bits 7:0 */
      uint32_t RVSU:8;             /* 0x174 bits 31:24 */
      uint32_t PVAcc:8;            /* 0x174 bits 23:16 */
      uint32_t Add_EXEZSU:4;       /* 0x174 bits 15:12 */ 
      uint32_t CVSU:12;            /* 0x174 bits 11:0 */
      uint32_t PH:8;               /* 0x178 bits 31:24 */  
      uint32_t RH:8;               /* 0x178 bits 23:16 */
      uint32_t PVH:8;              /* 0x178 bits 15:8 */
      uint32_t PVH2:8;             /* 0x178 bits 7:0 */
      uint32_t EH:8;               /* 0x17C bits 31:24 */
      uint32_t Sequence:8;         /* 0x17C bits 23:16 */
      uint32_t VSTAT:4;            /* 0x17C bits 15:12 */
      uint32_t SmFrequency:12;     /* 0x17C bits 11:0 */
      uint32_t VHV_EStart:16;      /* 0x180 bits 31:16 */
      uint32_t VHV_EStep:16;       /* 0x180 bits 15:0 */
      uint32_t OtpReserved1:16;    /* 0x184 bits 31:16 */
      uint32_t MAX_PP:16;          /* 0x184 bits 15:0 */
      uint32_t MAX_EP:16;          /* 0x188 bits 31:16 */
      uint32_t PROG_PW:16;         /* 0x188 bits 15:0 */
      uint32_t ERA_PW;             /* 0x18C bits 31:0 */
      uint32_t VHV_P:16;           /* 0x190 bits 31:16 */
      uint32_t VHV_E:16;           /* 0x190 bits 15:0 */
      uint32_t VHV_PV:16;          /* 0x194 bits 31:16 */
      uint32_t VCG:8;              /* 0x194 bits 15:8 */
      uint32_t VINH:8;             /* 0x194 bits 7:0 */
      uint32_t VSL_P:8;            /* 0x198 bits 31:24 */
      uint32_t VWL_P:8;            /* 0x198 bits 23:16 */
      uint32_t VRead:8;            /* 0x198 bits 15:8 */
      uint32_t OtpReserved2:8;     /* 0x198 bits 7:0 */
      uint32_t ApiChecksum:32;     /* 0x19C bits 31:0 */
      uint32_t OtpReserved3:32;    /* 0x1A0 bits 31:0 */
      uint32_t OtpReserved4:32;    /* 0x1A4 bits 31:0 */
      uint32_t OtpReserved5:32;    /* 0x1A8 bits 31:0 */
      uint32_t OtpReserved6:32;    /* 0x1AC bits 31:0 */
   } OTP_VALUE;
   volatile uint8_t  au8OtpWord[0x60];
   volatile uint16_t au16OtpWord[0x30];
   volatile uint32_t au32OtpWord[0x18];
}Fapi_TiOtpBytesType;
#endif
/*LDRA_ANALYSIS*/

typedef struct TI_OTP_TYPE
{
   Fapi_TiOtpBytesType aOtpBank[8];
}Fapi_TiOtpType;

/*!
    \brief
*/
typedef enum
{
   Alpha_Internal,          /* For internal TI use only.  Not intended to be used by customers */
   Alpha,                   /* Early Engineering release.  May not be functionally complete */
   Beta_Internal,           /* For internal TI use only.  Not intended to be used by customers */
   Beta,                    /* Functionally complete, to be used for testing and validation */
   Production               /* Fully validated, functionally complete, ready for production use */
}  ATTRIBUTE_PACKED Fapi_ApiProductionStatusType;

typedef struct
{
   uint8_t  u8ApiMajorVersion;
   uint8_t  u8ApiMinorVersion;
   uint8_t  u8ApiRevision;
   Fapi_ApiProductionStatusType oApiProductionStatus;
   uint32_t u32ApiBuildNumber;
   uint8_t  u8ApiTechnologyType;
   uint8_t  u8ApiTechnologyRevision;
   uint8_t  u8ApiEndianness;
   uint32_t u32ApiCompilerVersion;
}Fapi_LibraryInfoType;

typedef struct
{
#if defined(_LITTLE_ENDIAN)
   uint16_t u16NumberOfBanks;
   uint16_t u16Reserved;   
   uint16_t u16DeviceMemorySize;
   uint16_t u16DevicePackage;   
   uint32_t u32AsicId;
   uint32_t u32LotNumber;
   uint16_t u16WaferNumber;
   uint16_t u16FlowCheck;   
   uint16_t u16WaferYCoordinate;
   uint16_t u16WaferXCoordinate;   
#else	
   uint16_t u16Reserved;	
   uint16_t u16NumberOfBanks;
   uint16_t u16DevicePackage;
   uint16_t u16DeviceMemorySize;
   uint32_t u32AsicId;
   uint32_t u32LotNumber;
   uint16_t u16FlowCheck;
   uint16_t u16WaferNumber;
   uint16_t u16WaferXCoordinate;
   uint16_t u16WaferYCoordinate;
#endif
}Fapi_DeviceInfoType;

typedef struct
{
    Fapi_FlashBankTechType oFlashBankTech;
    uint32_t u32NumberOfSectors;
    uint32_t u32BankStartAddress;
    uint16_t au16SectorSizes[16];
}Fapi_FlashBankSectorsType;

#endif /* TYPES_H_*/

/**********************************************************************************************************************
 *  END OF FILE: Types.h
 *********************************************************************************************************************/
