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
 *      Version:  v2.01.00 Build(000828)                                                                                
 *   Build Date:  2014-05-20                                                                                            
 *
 *         File:  Registers_FMC_LE.h                                                                                    
 *
 *  Description:  A complete mapping of the F021 Flash Registers facilitating named access to the F021 Flash Registers.
 *                This file is for Little Endian devices.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  John R Hall
 *---------------------------------------------------------------------------------------------------------------------
 *
 *********************************************************************************************************************/


#ifndef REGISTERS_LE_H_
#define REGISTERS_LE_H_

/*  Flash Configuration Registers */

/*!
    Structure describing the Flash Wrapper registers allowing register and bit
    level accesses.
*/
#if defined(_L2FMC)
typedef volatile struct FMC_REGISTERS
{
   /*!
       Defines whole and bit level accesses to the Read Control Register - 0x00
   */
 
    union FRDCNTL
   {
      uint32_t u32Register; /* Read Control Register, bits 31:0 */
      struct
      {
         uint32_t PFUENA                  :1;/*!< Read Mode, bit 0 */
         uint32_t PFUENB                  :1;/*!< Address Setup Wait State Enable, bit 4 */
         uint32_t _FRDCNTL_Reserved_07_02 :6;/*!< Reserved, bits 7:5 */
         uint32_t RWAIT                   :4;/*!< Random Read Wait State, bits 11:8 */
         uint32_t _FRDCNTL_Reserved_31_12 :20;/*!< Reserved, bits 31:12 */
      } FRDCNTRL_BITS;
   } FrdCntl;
  
   uint32_t _Reserved_04; /* Reserved Address Locations 0x04 */
   
   /*!
       Defines whole and bit level accesses to the Error Correction Control Register1 - 0x08
   */
   union FEDACCTRL1
   {
      uint32_t u32Register; /* Error Correction Control Register1, bits 31:0 */
      struct
      {
         uint32_t _FEDACCTRL1_Reserved_03_00 :4;/* !< Reserved bit 03:00 */
         uint32_t EZCV                       :1;/*!< Zero Condition Valid, bit 4 */
         uint32_t EOCV                       :1;/*!< One Condition Valid, bit 5 */
         uint32_t _FEDACCTRL1_Reserved_31_06 :26;/*!< Reserved, bits 31:06 */		 
 
      } FEDACCTRL1_BITS;
   } FedAcCtrl1;
 
 
   uint32_t _Reserved_0C; /* Reserved Address Locations 0x0C */
   
    uint32_t _Reserved_10; /* Reserved Address Locations 0x10 */
 
    /*!
       Defines whole and bit level accesses to the Port A Error and Status Register - 0x14
   */
   union FEDAC_PASTATUS
   {
      uint32_t u32Register; /*  Port A Error and Status Register, bits 31:0 */
      struct
      {
         uint32_t _FEDACPASTATUS_Reserved_09_00 :10; /* !< Reserved bits 09:00 */
         uint32_t ADD_PAR_ERR                   :1;/*!< Address Parity Error , bits 10 */		 
         uint32_t ADD_TAG_ERR                   :1;/*!< Address Tag Register Error Status Flag, bit 11 */		 
         uint32_t _FEDACPASTATUS_Reserved_13_12 :2; /*!< Reserved bits 13:12 */
         uint32_t MCMD_PAR_ERR                  :1;/*!< Parity error in MCmd while Mcmd=Idle or in MRespAccept, bit 14 */
         uint32_t ACC_TOUT                      :1;/*!< Crossbar access timeout/ Internal address parity error, bit 15 */
         uint32_t _FEDACPASTATUS_Reserved_31_16 :16 ;/*!< Reserved bits 31:17 */
      } FEDAC_PASTATUS_BITS;
   } FedacPAStatus;

    /*!
       Defines whole and bit level accesses to the Port B Error and Status Register - 0x18
   */
   union FEDAC_PBSTATUS
   {
      uint32_t u32Register; /*  Port B Error and Status Register, bits 31:0 */
      struct
      {
        uint32_t _FEDACPBSTATUS_Reserved_09_00 :10; /*!< Reserved bits 09:00 */
        uint32_t ADD_PAR_ERR                   :1;/*!< Address Parity Error , bits 10 */
        uint32_t ADD_TAG_ERR                   :1;/*!< Address Tag Register Error Status Flag, bit 11 */
        uint32_t _FEDACPBSTATUS_Reserved_13_12 :2; /*!< Reserved bits 13:12 */
        uint32_t MCMD_PAR_ERR                  :1;/*!< Parity error in MCmd while Mcmd=Idle or in MRespAccept, bit 14 */
        uint32_t ACC_TOUT                      :1;/*!< Crossbar access timeout/ Internal address parity error, bit 15 */
        uint32_t _FEDACPBSTATUS_Reserved_31_16 :16 ;/*!< Reserved bits 31:17 */
      } FEDAC_PBSTATUS_BITS;
   } FedacPBStatus;	
 
    /*!
       Defines whole and bit level accesses to the Global Error and Status Register - 0x1C
   */
   union FEDAC_GBLSTATUS
   {
      uint32_t u32Register; /* Global Error and Status Register ,bits 31:0 */
      struct
      {
        uint32_t _FEDACGLBSTATUS_Reserved_12_00 :13; /*!< Reserved bits 12:00 */
        uint32_t IMPLICIT_UNC_ERR               :1;/*!<  UnCorrectable error during implicit two reads from OTP, bit 13 */
        uint32_t IMPLICIT_COR_ERR               :1;/*!<  Correctable error during implicit two reads from OTP, bit 14 */
        uint32_t RCR_ERR                        :1;/*!< L2FMC_Config_out port correction, bit 15 */
        uint32_t _FEDACGLBSTATUS_Reserved_23_16 :8; /*!< Reserved bits 23:16 */
        uint32_t FSM_DONE                       :1;/*!< FSM done event, bit 24 */
        uint32_t RVF_EVT                        :1;/*!< FSM Command Read_Verify failed error event, bit 25 */
        uint32_t _FEDACGLBSTATUS_Reserved_31_26 :6 ;/*!< Reserved bits 31:26 */
      } FEDAC_GLBSTATUS_BITS;
   } FedacGblStatus;	
 
     uint32_t _Reserved_20; /* Reserved Address Locations 0x20 */
 
  /*!
       Defines whole and bit level accesses to the Error Detection Sector Disable Register - 0x24
   */
   union FEDACSDIS
   {
      uint32_t u32Register; /* Error Detection Sector Disable Register, bits 31:0 */
      struct
      {
        uint32_t SectorID0                 :6;/*!< Sector ID0 , bits 05:00 */
        uint32_t _FEDACSDIS_Reserved_07_06 :2;/*!< Reserved bits, 07:06 */
        uint32_t SectorID0_inverse         :6;/*!< Sector ID0 Inverse, bits 13:08 */
        uint32_t _FEDACSDIS_Reserved_15_14 :2;/*!< Reserved bits, 15:14 */
        uint32_t SectorID1                 :6;/*!< Sector ID1 , bits 21:16 */
        uint32_t _FEDACSDIS_Reserved_23_22 :2;/*!< Reserved bits, 23:22 */
        uint32_t SectorID1_inverse         :6;/*!< Sector ID1 Inverse, bits 29:24 */
        uint32_t _FEDACSDIS_Reserved_31_30 :2;/*!< Reserved bits, 31:30 */
      } FEDACSDIS_BITS;
   } FedAcsDis;

 /*!
       Defines whole and bit level accesses to the Primary Address Tag Register - 0x28
   */
   union FPRIM_ADD_TAG
   {
      uint32_t u32Register; /* Primary Address Tag Register, bits 31:0 */
      struct
      {
        uint32_t RET_ZERO      :5;/*!< This field always returns 0000, bits 4:0 */
        uint32_t PRIM_ADD_TAG  :27;/*!< Primary Address Tag Register, bits 31:5 */
      } FPRIM_ADD_TAG_BITS;
   } FprimAddTag; 

 /*!
       Defines whole and bit level accesses to the Redundant Address Tag Register - 0x2C
   */
   union FDUP_ADD_TAG
   {
      uint32_t u32Register; /* Duplicate Address Tag Register, bits 31:0 */
      struct
      {
        uint32_t RET_ZERO      :5;/*!< This field always returns 0000, bits 4:0 */
        uint32_t DUP_ADD_TAG   :27;/*!< Duplicate Address Tag Register, bits 31:5 */
      } FDUP_ADD_TAG_BITS;
   } FdupAddTag;

     /*!
       Defines whole and bit level accesses to the Bank Sector Enable Register - 0x30
   */
   union FBPROT
   {
      uint32_t u32Register; /* Bank Protection Register, bits 31:0 */
      struct
      {
        uint32_t  PROTL1DIS             :1; /*!< Level 1 Protection Disabled, bit 0 */
        uint32_t _FBPROT_Reserved_31_01 :31;/*!< Reserved, bits 31:1 */
      } FBPROT_BITS;
   } Fbprot;

    /*!
       Defines whole and bit level accesses to the Bank Protection Register - 0x34
   */
   union FBSE
   {
      uint32_t u32Register; /* Bank Protection Register, bits 31:0 */
      struct
      {
        uint32_t BSE                  :16;/*!< Bank Sector Enable, bits 15:0 */
        uint32_t _FBSE_Reserved_31_16 :16;/*!< Reserved, bits 31:16 */
      } FBSE_BITS;
   } Fbse;
   
   /*!
       Defines whole and bit level accesses to the Bank Busy Register - 0x38
   */
   union FBBUSY
   {
      uint32_t u32Register; /* Bank Busy Register, bits 31:0 */
      struct
      {
        uint32_t  BUSY                  :8; /*!< Bank Busy, bits 7:0 */
        uint32_t _FBBUSY_Reserved_31_08 :24;/*!< Reserved, bits 31:8 */
      } FBPROT_BITS;
   } Fbbusy;
   
    /*!
       Defines whole and bit level accesses to the Bank Access Control Register - 0x3C
   */
   union FBAC
   {
      uint32_t u32Register; /* Bank Access Control Register, bits 31:0 */
      struct
      {
        uint32_t VREADS               :8;/*!< VREAD Setup, bits 7:0 */
        uint32_t _FBAC_Reserved_15_08 :8;/*!< Reserved,  bits 15:8 */
        uint32_t OTPPROTDIS           :8;/*!< OTP Sector Protection Disable, bits 23:16 */
        uint32_t _FBAC_Reserved_31_24 :8;/*!< Reserved, bits 31:24 */
      } FBAC_BITS;
   } Fbac;

  /*!
       Defines whole and bit level accesses to the Bank Power mode Register - 0x40
   */
   union FBFALLBACK
   {
      uint32_t u32Register; /* Bank Fallback Power Register, bits 31:0 */
      struct
      {
        uint32_t BANKPWR0             :2;/*!< Bank 0 Fallback Power Mode, bits 15:14 */
        uint32_t BANKPWR1             :2;/*!< Bank 1 Fallback Power Mode, bits 15:14 */
        uint32_t BANKPWR2             :2;/*!< Bank 2 Fallback Power Mode, bits 15:14 */
        uint32_t BANKPWR3             :2;/*!< Bank 3 Fallback Power Mode, bits 15:14 */
        uint32_t BANKPWR4             :2;/*!< Bank 4 Fallback Power Mode, bits 15:14 */
        uint32_t BANKPWR5             :2;/*!< Bank 5 Fallback Power Mode, bits 15:14 */
        uint32_t BANKPWR6             :2;/*!< Bank 6 Fallback Power Mode, bits 15:14 */
        uint32_t BANKPWR7             :2;/*!< Bank 7 Fallback Power Mode, bits 15:14 */
        uint32_t _FBAC_Reserved_31_16 :16;/*!< Reserved, bits 31:16 */
      } FBFALLBACK_BITS;
   } Fbfallback; 
   
   /*!
       Defines whole and bit level accesses to the Bank/Pump Ready Register - 0x44
   */
   union FBPRDY
   {
      uint32_t u32Register; /* Bank/Pump Ready Register, bits 31:0 */
      struct
      {
        uint32_t BANKRDY                :8;/*!< Bank Ready, bits 7:0 */
        uint32_t _FBPRDY_Reserved_14_08 :7;/*!< Reserved, bits 14:8 */
        uint32_t PUMPRDY                :1;/*!< Pump Ready, bit 15 */
        uint32_t BANKBUSY               :8;/*!< Bank Busy with FSM, SW_INTF, CPU or PMT, bits 23:16 */
        uint32_t _FBPRDY_Reserved_31_24 :8;/*!< Reserved, bits 31:24 */
      } FBPRDY_BITS;
   } Fbprdy;
   
    /*!
       Defines whole and bit level accesses to the Pump Access Control Register 1 - 0x48
   */
   union FPAC1
   {
      uint32_t u32Register; /* Flash Pump Access Control Register 1, bits 31:0 */
      struct
      {
        uint32_t PUMPPWR                :1; /*!< Flash Charge Pump Fallback Power Mode, bit 0 */
        uint32_t _FPAC1_Reserved_15_01  :15;/*!< Reserved, bits 15:1 */
        uint32_t PSBEEP                 :12;/*!< Pump Sleep, bits 27:16 */
        uint32_t _FPAC1_Reserved_31_28  :4; /*!< Reserved, bits 31:28 */
      } FPAC1_BITS;
   } Fpac1;
   
   
     uint32_t _Reserved_4C; /* Reserved Address Locations 0x4C */
 
    /*!
       Defines whole and bit level accesses to the Module Access Control Register - 0x50
   */
   union FMAC
   {
      uint32_t u32Register; /* Module Access Control Register, bits 31:0 */
      struct
      {
        uint32_t  BANK                :3; /*!< Bank Enable, bits 2:0 */
        uint32_t _FMAC_Reserved_31_03 :29; /*!< Reserved, bits 31:3 */
      } FMAC_BITS;
   } Fmac;

    /*!
       Defines whole and bit level accesses to the Module Status Register - 0x54
   */
   union FMSTAT
   {
      uint32_t u32Register; /* Module Status Register, bits 31:0 */
      struct
      {
        uint32_t SLOCK                   :1; /*!< Sector Lock Status, bit 0 */
        uint32_t PSUSP                   :1; /*!< Program Suspend, bit 1 */
        uint32_t ESUSP                   :1; /*!< Erase Suspend, bit 2 */
        uint32_t VOLSTAT                 :1; /*!< Core Voltage Status, bit 3 */
        uint32_t CSTAT                   :1; /*!< Command Status, bit 4 */
        uint32_t INVDAT                  :1; /*!< Invalid Data, bit 5 */
        uint32_t PGM                     :1; /*!< Program Active, bit 6 */
        uint32_t ERS                     :1; /*!< Erase Active, bit 7 */
        uint32_t BUSY                    :1; /*!< Busy, bit 8 */
        uint32_t CV                      :1; /*!< Compact Verify, bit 9 */
        uint32_t EV                      :1; /*!< Erase verify, bit 10 */
        uint32_t PCV                     :1; /*!< Precondidition verify, bit 11 */
        uint32_t PGV                     :1; /*!< Program verify, bit 12 */
        uint32_t DBT                     :1; /*!< Disturbance Test Fail, bit 13 */
        uint32_t ILA                     :1; /*!< Illegal Address, bit 14 */
        uint32_t RVF                     :1; /*!< Read Verify Failure, bit 15 */
        uint32_t RDVER                   :1; /*!< Read Verify command currently underway, bit 16 */
        uint32_t RVSUSP                  :1; /*!< Read Verify Suspend, bit 17 */
        uint32_t _FMSTAT_Reserved_31_18  :14;/*!< Reserved, bits 31:18 */
      } FMSTAT_BITS;
   } FmStat;

    /*!
       Defines whole and bit level accesses to the EEPROM Emulation Data MSW Register - 0x58
   */
   union FEMU_DMSW
   {
      uint32_t u32Register; /* EEPROM Emulation Data MSW Register, bits 31:0 */
   } FemuDmsw;

   /*!
       Defines whole and bit level accesses to the EEPROM Emulation Data LSW Register - 0x5C
   */
   union FEMU_DLSW
   {
      uint32_t u32Register; /* EEPROM Emulation Data LSW Register, bits 31:0 */
   } FemuDlsw;

   /*!
       Defines whole and bit level accesses to the EEPROM Emulation ECC Register - 0x60
   */
   union FEMU_ECC
   {
      uint32_t u32Register; /* EEPROM Emulation ECC Register, bits 31:0 */
      struct
      {
        uint32_t  EMU_ECC                 :8; /*!< EEPROM Emulation ECC, bits 7:0 */
        uint32_t _FEMU_ECC_Reserved_31_08 :24;/*!< Reserved, bits 31:8 */
      } FEMU_ECC_BITS;
   } FemuEcc;

    uint32_t _Reserved_64; /* Reserved Address Locations 0x64 */
    
     /*!
       Defines whole and bit level accesses to the EEPROM Emulation Address Register - 0x68
   */
   union FEMU_ADDR
   {
      uint32_t u32Register; /* EEPROM Emulation Address, bits 31:0 */
      struct
      {
        uint32_t _FEMU_ADDR_Reserved_02_00 :3;/*!< Reserved, bits 02:00 */
        uint32_t EMU_ADDR                  :29;/*!< EEPROM Emulation Address, bits 31:03 */
      } FEMU_ADDR_BITS;
   } FemuAddr;
   
    /*!
       Defines whole and bit level accesses to the Diagnostic Control Register - 0x6C
   */
   union FDIAGCTRL
   {
      uint32_t u32Register; /* Diagnostic Control Register, bits 31:0 */
      struct
      {
        uint32_t DIAGMODE                  :3;/*!< Diagnostic Mode, bits 2:0 */
        uint32_t _FDIAGCTRL_Reserved_07_03 :5;/*!< Reserved, bits 7:3 */
        uint32_t DIAG_BUF_SEL              :3;/*!< Diagnostic Buffer Select, bits 10:8 */
        uint32_t _FDIAGCTRL_Reserved_15_11 :5;/*!< Reserved, bits 15:11 */
        uint32_t DIAG_EN_KEY               :4;/*!< Diagnostic Enable Key, bits 19:16 */
        uint32_t _FDIAGCTRL_Reserved_23_20 :4;/*!< Reserved, bits 23:20 */
        uint32_t DIAG_TRIG                 :1;/*!< Diagnostic Trigger, bit 24 */
        uint32_t _FDIAGCTRL_Reserved_31_25 :7;/*!< Reserved, bits 31:25 */
      } FDIAGCTRL_BITS;
   } FdiagCtrl;

   uint32_t _Reserved_70; /* Reserved Address Locations 0x70 */
   
   /*!
       Defines whole and bit level accesses to the Uncorrected Raw Data High Register - 0x70
   */
   union FRAW_ADDR
   {
      uint32_t u32Register; /* Uncorrected Raw Data High, bits 31:0 */
      struct
      {
        uint32_t _FRAW_ADDR_Reserved_04_00 :5;/*!< Reserved, bits 04:00 */
        uint32_t RAW_ADDR                  :27;/*!< EEPROM Emulation Address, bits 31:05 */
      } FRAW_ADDR_BITS;
   } FrawAddr;
   
     uint32_t _Reserved_78; /* Reserved Address Locations 0x78 */
     
    /*!
       Defines whole and bit level accesses to the Parity Override Register - 0x7C
   */
   union FPAR_OVR
   {
      uint32_t u32Register; /* Parity Override, bits 31:0 */
      struct
      {
        uint32_t  DAT_INV_PAR              :8; /*!< Data Odd Parity, bits 7:0 */
        uint32_t  _FPAR_OVR_Reserved_08    :1; /*!< Reserved , bit 8 */
        uint32_t  PAR_OVR_KEY              :3; /*!< Parity Override Key, bits 11:9 */
        uint32_t  BUS_PAR_DIS              :4; /*!< Disable bus parity, bits 15:12 */
        uint32_t  BNK_INV_PAR              :1; /*!< Buffer Invert Parity, bit 16 */
        uint32_t _FPAR_OVR_Reserved_31_17  :15;/*!< Reserved, bits 31:17 */
      } FPAR_OVR_BITS;
   } FparOvr; 
     
   
    uint32_t _Reserved_80_B0[13];/* Reserved Address Locations 0x80 - 0xB0 */
 
    /*!
       Defines whole and bit level accesses to the Reset Config and JSM Key Valid Register - 0xB4
   */
   union RCR_JSM_VALID
   {
      uint32_t u32Register; /* Uncorrected Raw Data High, bits 31:0 */
      struct
      {
        uint32_t RCR_VALID						:1;/*!< RCR Key Valid, bits 0 */
        uint32_t JSM_VALID						:1;/*!< JSM Key Valid, bits 1 */
        uint32_t _RCR_JSM_VALID_Reserved_31_02  :30;/*!< Reserved , bits 31:02 */
      } RCR_JSM_VALID_BITS;
   } RcrJsmValid;
 
  /*!
       Defines whole and bit level accesses to the Crossbar access time threshold Register - 0xB8
   */
   union ACC_THRESHOLD
   {
      uint32_t u32Register; /* Uncorrected Raw Data High, bits 31:0 */
      struct
      {
        uint32_t ACC_THRESH_CNT					:12;/*!< Crossbar access time threshold count, bits 11:00 */
        uint32_t _ACC_THRESHOLD_Reserved_31_12  :20;/*!< Reserved , bits 31:12 */
      } ACC_THRESHOLD_BITS;
   } AccThreshold;
   
   uint32_t _Reserved_BC;/* Reserved Address Locations 0xBC */
 
     /*!
       Defines whole and bit level accesses to the EEPROM Error Detection Sector Disable Register - 0xC0
   */
   union FEDACSDIS2
   {
      uint32_t u32Register; /* Error Detection Sector Disable Register, bits 31:0 */
      struct
      {
        uint32_t SectorID2                 :6;/*!< Sector ID2 , bits 05:00 */
        uint32_t _FEDACSDIS_Reserved_07_06 :2;/*!< Reserved bits, 07:06 */
        uint32_t SectorID2_inverse         :6;/*!< Sector ID2 Inverse, bits 13:08 */
        uint32_t _FEDACSDIS_Reserved_15_14 :2;/*!< Reserved bits, 15:14 */
        uint32_t SectorID3                 :6;/*!< Sector ID3 , bits 21:16 */
        uint32_t _FEDACSDIS_Reserved_23_22 :2;/*!< Reserved bits, 23:22 */
        uint32_t SectorID3_inverse         :6;/*!< Sector ID3 Inverse, bits 29:24 */
        uint32_t _FEDACSDIS_Reserved_31_30 :2;/*!< Reserved bits, 31:30 */
      } FEDACSDIS_BITS;
   } FedAcsDis2;

  uint32_t _Reserved_C4_CC[3];/* Reserved Address Locations 0xC4-0xCC */
 
    /*!
       Defines whole and bit level accesses to the RCR Lower word - 0xD0
   */
   union RCRVALUE0
   {
      uint32_t u32Register; /* RCR Lower word, bits 31:0 */
   } RcrValue0;
 
 /*!
       Defines whole and bit level accesses to the RCR Upper word - 0xD4
   */
   union RCRVALUE1
   {
      uint32_t u32Register; /* RCR Upper word, bits 31:0 */
   } RcrValue1;
 
  uint32_t _Reserved_D8_DC[2];/* Reserved Address Locations 0xD8-0xDC */
 
  /*!
       Defines whole and bit level accesses to the JSM Key0  - 0xE0
   */
   union JSMKEY0
   {
      uint32_t u32Register; /* Bank Addr Register, bits 31:0 */
   } JSMKey0;
 
    /*!
       Defines whole and bit level accesses to the JSM Key1  - 0xE4
   */
   union JSMKEY1
   {
      uint32_t u32Register; /* Bank Addr Register, bits 31:0 */
   } JSMKey1;
   
   
   /*!
       Defines whole and bit level accesses to the JSM Key2  - 0xE8
   */
   union JSMKEY2
   {
      uint32_t u32Register; /* Bank Addr Register, bits 31:0 */
   } JSMKey2;
   
   
   /*!
       Defines whole and bit level accesses to the JSM Key3  - 0xEC
   */
   union JSMKEY3
   {
      uint32_t u32Register; /* Bank Addr Register, bits 31:0 */
   } JSMKey3;
 
     uint32_t _Reserved_F0_10C[8];/* Reserved Address Locations 0xF0 - 0x10C */


   /*!
       Defines whole and bit level accesses to the Bank Addr Register - 0x110
   */
   union FADDR
   {
      uint32_t u32Register; /* Bank Addr Register, bits 31:0 */
   } Faddr;
 
    uint32_t _Reserved_114_11C[3]; /* Reserved Address Locations 0x114-0x11C */

   /*!
       Defines whole and bit level accesses to the FWPWRITE0 Register - 0x120
   */
   union FWPWRITE0
   {
      uint32_t u32Register; /* FWPWRITE0 Register, bits 31:0 */
   } Fwpwrite0;

   /*!
       Defines whole and bit level accesses to the FWPWRITE1 Register - 0x124
   */
   union FWPWRITE1
   {
      uint32_t u32Register; /* FWPWRITE1 Register, bits 31:0 */
   } Fwpwrite1;

   /*!
       Defines whole and bit level accesses to the FWPWRITE2 Register - 0x128
   */
   union FWPWRITE2
   {
      uint32_t u32Register; /* FWPWRITE2 Register, bits 31:0 */
   } Fwpwrite2;

   /*!
       Defines whole and bit level accesses to the FWPWRITE3 Register - 0x12C
   */
   union FWPWRITE3
   {
      uint32_t u32Register; /* FWPWRITE3 Register, bits 31:0 */
   } Fwpwrite3;

   /*!
       Defines whole and bit level accesses to the FWPWRITE4 Register - 0x130
   */
   union FWPWRITE4
   {
      uint32_t u32Register; /* FWPWRITE4 Register, bits 31:0 */
   } Fwpwrite4;

   /*!
       Defines whole and bit level accesses to the FWPWRITE5 Register - 0x134
   */
   union FWPWRITE5
   {
      uint32_t u32Register; /* FWPWRITE5 Register, bits 31:0 */
   } Fwpwrite5;

   /*!
       Defines whole and bit level accesses to the FWPWRITE6 Register - 0x138
   */
   union FWPWRITE6
   {
      uint32_t u32Register; /* FWPWRITE6 Register, bits 31:0 */
   } Fwpwrite6;

   /*!
       Defines whole and bit level accesses to the FWPWRITE7 Register - 0x13C
   */
   union FWPWRITE7
   {
      uint32_t u32Register; /* FWPWRITE7 Register, bits 31:0 */
   } Fwpwrite7;
   
   /*!
       Defines whole and bit level accesses to the FWPWRITE_ECC Register - 0x140
   */
   union FWPWRITE_ECC
   {
      uint32_t u32Register; /* FWPWRITE_ECC Register, bits 31:0 */
      struct
      {
        uint32_t WPDATA_287_256; /*!< WPDATA[287:256], bits 31:0 */
      } FWPWRITE_ECC_BITS;
      struct
      {
        uint32_t u8Bytes31_24:8;
        uint32_t u8Bytes23_16:8;
        uint32_t u8Bytes15_08:8;
        uint32_t u8Bytes07_00:8;
      } FWPWRITE_ECC_BYTES;
   } FwpwriteEcc;

   uint32_t _Reserved_144_208[50]; /* Reserved Address Locations 0x144-0x208 */

   /*!
       Defines whole and bit level accesses to the FSM Command Register - 0x20C
   */
   union FSM_COMMAND
   {
      uint32_t u32Register; /* FSM Command, bits 31:0 */
      struct
      {
        uint32_t  FSMCMD                     :6; /*!< Flash State Machine Command, bits 5:0 */
        uint32_t _FSM_COMMAND_Reserved_31_06 :26;/*!< Reserved, bits 31:6 */
      } FSM_COMMAND_BITS;
   } FsmCommand;

   uint32_t _Reserved_210_284[30]; /* Reserved Address Locations 0x210-0x284 */

   /*!
       Defines whole and bit level accesses to the FSM Register Write Enable- 0x288
   */
   union FSM_WR_ENA
   {
      uint32_t u32Register; /* FSM Register Write Enable, bits 31:0 */
      struct
      {
        uint32_t  WR_ENA                    :3; /*!< FSM Write Enable, bits 2:0 */
        uint32_t _FSM_WR_ENA_Reserved_31_03 :29;/*!< Reserved, bits 31:3 */
      } FSM_WR_ENA_BITS;
   } FsmWrEna;

   uint32_t _Reserved_28C_2A0[6]; /* Reserved Address Locations 0x28C-0x2A0 */

   /*!
       Defines whole and bit level accesses to the FSM Sector Register - 0x2A4
   */
   union FSM_SECTOR
   {
      uint32_t u32Register; /* FSM Sector, bits 31:0 */
      struct
      {
        uint32_t SEC_OUT		:4; /*!< Sector from Address decoder, bits 3:0 */
        uint32_t SECTOR		 	:4; /*!< Current sector used by FSM, bits 7:4 */
        uint32_t FLEE_SECT_ETXN :8; /*!< FLEE Sector Extension bits, bits 15:8 */
        uint32_t SECT_ERASED    :16;/*!< Sectors Erased, bits 31:16 */
      } FSM_SECTOR_BITS;
   } FsmSector;
   
    uint32_t _Reserved_2A8_2B0[3]; /* Reserved Address Locations 0x2A8-0x2B0 */

   
   /*!
       Defines whole and bit level accesses to the FSM Command Execute Register - 0x2B4
   */
   union FSM_EXECUTE
   {
      uint32_t u32Register; /* FSM Command Execute, bits 31:0 */
      struct
      {
        uint32_t  FSMEXECUTE                 :5; /*!< FSM Command Execute, bits 4:0 */
        uint32_t _FSM_EXECUTE_Reserved_15_05 :11;/*!< Reserved, bits 15:5 */
        uint32_t  SUSPEND_NOW                :4; /*!< FSM Command Suspend, bits 19:16 */
        uint32_t _FSM_EXECUTE_Reserved_31_20 :12;/*!< Reserved, bits 31:20 */
      } FSM_EXECUTE_BITS;
   } FsmExecute;

    /*!
       Defines whole and bit level accesses to the EEPROM Emulation configuration Register - 0x2B8
   */
   union EEPROM_CONFIG
   {
      uint32_t u32Register; /* EEPROM Emulation configuration, bits 31:0 */
      struct
      {
        uint32_t  _EEPROM_CONFIG_Reserved_15_00 :16;/*!< Reserved, bits 15:0 */
        uint32_t  EWAIT                         :4; /*!< EEPROM Wait state Counter, bits 19:16 */
        uint32_t _EEPROM_CONFIG_Reserved_31_20 	:12;/*!< Reserved, bits 31:20 */
      } EEPROM_CONFIG_BITS;
   } EepromConfig;

     uint32_t _Reserved_2BC;  /* Reserved Address Locations 0x2BC */
     
      /*!
       Defines whole and bit level accesses to the FSM Sector1 Register - 0x2C0
   */
   union FSM_SECTOR1
   {
      uint32_t u32Register; /* FSM Sector1, bits 31:0 */
   } FsmSector1;

   /*!
       Defines whole and bit level accesses to the FSM Sector2 Register - 0x2C4
   */
   union FSM_SECTOR2
   {
      uint32_t u32Register; /* FSM Sector1, bits 31:0 */
   } FsmSector2;

   uint32_t _Reserved_2C8_3FC[78];/* Reserved Address Locations 0x2C8 - 0x3FC */

    
     /*!
       Defines whole and bit level accesses to the FCFG BANK Register - 0x400
   */
   union FCFG_BANK
   {
      uint32_t u32Register; /* Flash Bank configuration, bits 31:0 */
      struct
      {
        uint32_t  _FCFG_BANK_Reserved_3_0        :4; /*!< Reserved bits 3:0 */
        uint32_t  MAIN_BANK_WIDTH                :12;/*!< MAIN_BANK_WIDTH, bits 15:4 */
        uint32_t  _FCFG_BANK_Reserved_19_16      :4; /*!< Reserved bits 19:16 */
        uint32_t  EE_BANK_WIDTH                  :12;/*!< EE_BANK_WIDTH, bits 31:20 */
      } FCFG_BANK_BITS;
   } FcfgBank;	
 
 }Fapi_FmcRegistersType; 
#else
typedef volatile struct FMC_REGISTERS
{
   /*!
       Defines whole and bit level accesses to the Read Control Register - 0x00
   */
   union FRDCNTL
   {
      uint32_t u32Register; /* Read Control Register, bits 31:0 */
      struct
      {
         uint32_t ENPIPE                  :1;/*!< Read Mode, bit 0 */
         uint32_t _FRDCNTL_Reserved_03_01 :3;/*!< Reserved, bits 3:1 */
         uint32_t ASWSTEN                 :1;/*!< Address Setup Wait State Enable, bit 4 */
         uint32_t _FRDCNTL_Reserved_07_05 :3;/*!< Reserved, bits 7:5 */
         uint32_t RWAIT                   :4;/*!< Random Read Wait State, bits 11:8 */
         uint32_t _FRDCNTL_Reserved_31_12 :20;/*!< Reserved, bits 31:12 */
      } FRDCNTRL_BITS;
   } FrdCntl;

   uint32_t _Reserved_04; /* Reserved Address Locations 0x04 */

   /*!
       Defines whole and bit level accesses to the Error Correction Control Register1 - 0x08
   */
   union FEDACCTRL1
   {
      uint32_t u32Register; /* Error Correction Control Register1, bits 31:0 */
      struct
      {
         uint32_t EDACEN                     :4;/*!< Error Detection and Correction Enable, bits 3:0 */
         uint32_t EZCV                       :1;/*!< Zero Condition Valid, bit 4 */
         uint32_t EOCV                       :1;/*!< One Condition Valid, bit 5 */
         uint32_t _FEDACCTRL1_Reserved_07_06 :2;/*!< Reserved, bits 7:6 */
         uint32_t EPEN                       :1;/*!< Error Profiling Enable, bit 8 */
         uint32_t EZFEN                      :1;/*!< Error on Zero Fail Enable, bit 9 */
         uint32_t EOFEN                      :1;/*!< Error on One Fail Enable, bit 10 */
         uint32_t _FEDACCTRL1_Reserved_15_11 :5;/*!< Reserved, bits 15:11 */
         uint32_t EDACMODE                   :4;/*!< Error Correction Mode, bits 19:16 */
         uint32_t _FEDACCTRL1_Reserved_23_20 :4;/*!< Reserved, bits 23:20 */
         uint32_t SUSP_IGNR                  :1;/*!< Suspend Ignore, bit 24 */
         uint32_t _FEDACCTRL1_Reserved_31_25 :7;/*!< Reserved, bits 31:25 */
      } FEDACCTRL1_BITS;
   } FedAcCtrl1;

   /*!
       Defines whole and bit level accesses to the Error Correction Control Register2 - 0x0C
   */
   union FEDACCTRL2
   {
      uint32_t u32Register; /* Error Correction Control Register2, bits 31:0 */
      struct
      {
         uint32_t SEC_THRESHOLD              :16;/*!< Single Error Correction Threshold, bits 15:0 */
         uint32_t _FEDACCTRL2_Reserved_31_16 :16;/*!< Reserved, bits 31:16 */
      } FEDACCTRL2_BITS;
   } FedAcCtrl2;

   /*!
       Defines whole and bit level accesses to the Error Correction Counter Register - 0x10
   */
   union FCOR_ERR_CNT
   {
      uint32_t u32Register; /* Error Correction Counter Register, bits 31:0 */
      struct
      {
         uint32_t FERRCNT                      :16;/*!< Correctable Error Counter, bits 15:0 */
         uint32_t _FCOR_ERR_CNT_Reserved_31_16 :16;/*!< Reserved, bits 31:16 */
      } FCOR_ERR_CNT_BITS;
   } FcorErrCnt;

   /*!
       Defines whole and bit level accesses to the Correctable Error Address Register - 0x14
   */
   union FCOR_ERR_ADD
   {
      uint32_t u32Register; /* Correctable Error Address Register, bits 31:0 */
      struct
      {
         uint32_t B_OFF                        :3;/*!< Byte Offset, bits 2:0 */
         uint32_t COR_ERR_ADD                  :29;/*!< Correctable Error Address, bits 31:3 */
      } FCOR_ERR_ADD_BITS;
   } FcorErrAdd;

   /*!
       Defines whole and bit level accesses to the Correctable Error Position Register - 0x18
   */
   union FCOR_ERR_POS
   {
      uint32_t u32Register; /* Correctable Error Position Register, bits 31:0 */
      struct
      {
         uint32_t  ERR_POS                     :8; /*!< Single Error Position, bits 7:0 */
         uint32_t  TYPE                        :1; /*!< Error Type, bit 8 */
         uint32_t  BUS2                        :1; /*!< Bus 2 error position, bit 9 */
         uint32_t _FCOR_ERR_POS_Reserved_31_10 :22;/*!< Reserved, bits 31:10 */
      } FCOR_ERR_POS_BITS;
   } FcorErrPos;

   /*!
       Defines whole and bit level accesses to the Error Status Register - 0x1C
   */
   union FEDACSTATUS
   {
      uint32_t u32Register; /* Error Status Register, bits 31:0 */
      struct
      {
         uint32_t ERR_PRF_FLG                 :1;/*!< Error Profiling Status Flag, bit 0 */
         uint32_t ERR_ZERO_FLG                :1;/*!< Error On Zero Fail Status Flag, bit 1 */
         uint32_t ERR_ONE_FLG                 :1;/*!< Error On One Fail Status Flag, bit 2 */
         uint32_t D_COR_ERR                   :1;/*!< Diagnostic Correctable Error Status Flag, bit 3 */
         uint32_t _FEDACSTATUS_Reserved_7_4   :4;/*!< Reserved, bits 7:4 */
         uint32_t B1_UNC_ERR                  :1;/*!< Bus1 Uncorrectable Error Flag, bit 8 */
         uint32_t _FEDACSTATUS_Reserved_9     :1;/*!< Reserved, bit 9 */
         uint32_t ADD_PAR_ERR                 :1;/*!< Address Parity Error, bit 10 */
         uint32_t ADD_TAG_ERR                 :1;/*!< Address Tag Register Error Status Flag, bit 11 */
         uint32_t D_UNC_ERR                   :1;/*!< Diagnostic Un-correctable Error Status Flag, bit 12 */
         uint32_t _FEDACSTATUS_Reserved_15_13 :3;/*!< Reserved, bits 15:13 */
         uint32_t B2_COR_ERR                  :1;/*!< Bus2 Correctable Error, bit 16 */
         uint32_t B2_UNC_ERR                  :1;/*!< Bus2 Uncorrectable Error, bit 17 */
         uint32_t ECC_B2_MAL_ERR              :1;/*!< Bus2 ECC Malfunction Status Flag, bit 18 */
         uint32_t COMB2_MAL_G                 :1;/*!< Bus2 Compare Malfunction Flag, bit 19 */
         uint32_t _FEDACSTATUS_Reserved_23_20 :4;/*!< Reserved, bits 23:20 */
         uint32_t FSM_DONE                    :1;/*!< FSM is Finished, bit 24 */
         uint32_t _FEDACSTATUS_Reserved_31_25 :7;/*!< Reserved, bits 31:25 */
      } FEDACSTATUS_BITS;
   } FedAcStatus;

   /*!
       Defines whole and bit level accesses to the Un-correctable Error Address Register - 0x20
   */
   union FUNC_ERR_ADD
   {
      uint32_t u32Register; /* Error Status Register, bits 31:0 */
      struct
      {
         uint32_t B_OFF                        :3;/*!< Byte Offset, bits 2:0 */
         uint32_t UNC_ERR_ADD                  :29;/*!< Un-correctable Error Address, bits 31:3 */
      } FUNC_ERR_ADD_BITS;
   } FuncErrAdd;

   /*!
       Defines whole and bit level accesses to the Error Detection Sector Disable Register - 0x24
   */
   union FEDACSDIS
   {
      uint32_t u32Register; /* Error Detection Sector Disable Register, bits 31:0 */
      struct
      {
         uint32_t SectorID0              :4;/*!< Sector ID0 , bits 3:0 */
         uint32_t _FEDACSDIS_Reserved_04 :1;/*!< Reserved, bit 4 */
         uint32_t BankID0                :3;/*!< Bank ID0 , bits 7:5 */
         uint32_t SectorID0_inverse      :4;/*!< Sector ID0 Inverse, bits 11:8 */
         uint32_t _FEDACSDIS_Reserved_12 :1;/*!< Reserved, bit 12 */
         uint32_t BankID0_inverse        :3;/*!< Bank ID0 Inverse, bits 15:13 */
         uint32_t SectorID1              :4;/*!< Sector ID1 , bits 19:16 */
         uint32_t _FEDACSDIS_Reserved_20 :1;/*!< Reserved, bit 20 */
         uint32_t BankID1                :3;/*!< Bank ID1 , bits 23:21 */
         uint32_t SectorID1_inverse      :4;/*!< Sector ID1 Inverse, bits 27:24 */
         uint32_t _FEDACSDIS_Reserved_28 :1;/*!< Reserved, bit 28 */
         uint32_t BankID1_inverse        :3;/*!< Bank ID1 Inverse, bits 31:29 */
      } FEDACSDIS_BITS;
   } FedAcsDis;

   /*!
       Defines whole and bit level accesses to the Primary Address Tag Register - 0x28
   */
   union FPRIM_ADD_TAG
   {
      uint32_t u32Register; /* Primary Address Tag Register, bits 31:0 */
      struct
      {
         uint32_t RET_ZERO                      :4;/*!< This field always returns 0000, bits 3:0 */
         uint32_t PRIM_ADD_TAG                  :28;/*!< Primary Address Tag Register, bits 31:4 */
      } FPRIM_ADD_TAG_BITS;
   } FprimAddTag;

   /*!
       Defines whole and bit level accesses to the Redundant Address Tag Register - 0x2C
   */
   union FDUP_ADD_TAG
   {
      uint32_t u32Register; /* Duplicate Address Tag Register, bits 31:0 */
      struct
      {
         uint32_t RET_ZERO                     :4;/*!< This field always returns 0000, bits 3:0 */
         uint32_t DUP_ADD_TAG                  :28;/*!< Primary Address Tag Register, bits 31:4 */
      } FDUP_ADD_TAG_BITS;
   } FdupAddTag;

   /*!
       Defines whole and bit level accesses to the Bank Sector Enable Register - 0x30
   */
   union FBPROT
   {
      uint32_t u32Register; /* Bank Protection Register, bits 31:0 */
      struct
      {
         uint32_t  PROTL1DIS              :1; /*!< Level 1 Protection Disabled, bit 0 */
         uint32_t _FBPROT_Reserved_31_01 :31;/*!< Reserved, bits 31:1 */
      } FBPROT_BITS;
   } Fbprot;

   /*!
       Defines whole and bit level accesses to the Bank Protection Register - 0x34
   */
   union FBSE
   {
      uint32_t u32Register; /* Bank Protection Register, bits 31:0 */
      struct
      {
         uint32_t BSE                  :16;/*!< Bank Sector Enable, bits 15:0 */
         uint32_t _FBSE_Reserved_31_16 :16;/*!< Reserved, bits 31:16 */
      } FBSE_BITS;
   } Fbse;

   /*!
       Defines whole and bit level accesses to the Bank Busy Register - 0x38
   */
   union FBBUSY
   {
      uint32_t u32Register; /* Bank Busy Register, bits 31:0 */
      struct
      {
         uint32_t  BUSY                   :8; /*!< Bank Busy, bits 7:0 */
         uint32_t _FBBUSY_Reserved_31_08 :24;/*!< Reserved, bits 31:8 */
      } FBPROT_BITS;
   } Fbbusy;

   /*!
       Defines whole and bit level accesses to the Bank Access Control Register - 0x3C
   */
   union FBAC
   {
      uint32_t u32Register; /* Bank Access Control Register, bits 31:0 */
      struct
      {
         uint32_t VREADS               :8;/*!< VREAD Setup, bits 7:0 */
         uint32_t BAGP                 :8;/*!< Bank Active Grace Period, bits 15:8 */
         uint32_t OTPPROTDIS           :8;/*!< OTP Sector Protection Disable, bits 23:16 */
         uint32_t _FBAC_Reserved_31_24 :8;/*!< Reserved, bits 31:24 */
      } FBAC_BITS;
   } Fbac;

   /*!
       Defines whole and bit level accesses to the Bank Fallback Power Register - 0x40
   */
   union FBFALLBACK
   {
      uint32_t u32Register; /* Bank Fallback Power Register, bits 31:0 */
      struct
      {
         uint32_t BANKPWR0             :2;/*!< Bank 0 Fallback Power Mode, bits 1:0 */
         uint32_t BANKPWR1             :2;/*!< Bank 1 Fallback Power Mode, bits 3:2 */
         uint32_t BANKPWR2             :2;/*!< Bank 2 Fallback Power Mode, bits 5:4 */
         uint32_t BANKPWR3             :2;/*!< Bank 3 Fallback Power Mode, bits 7:6 */
         uint32_t BANKPWR4             :2;/*!< Bank 4 Fallback Power Mode, bits 9:8 */
         uint32_t BANKPWR5             :2;/*!< Bank 5 Fallback Power Mode, bits 11:10 */
         uint32_t BANKPWR6             :2;/*!< Bank 6 Fallback Power Mode, bits 13:12 */
         uint32_t BANKPWR7             :2;/*!< Bank 7 Fallback Power Mode, bits 15:14 */
         uint32_t REG_PWRSAV           :4;/*!< Power saving clocking control, bits 19:16 */
         uint32_t _FBAC_Reserved_23_20 :4;/*!< Reserved, bits 23:20 */
         uint32_t FSM_PWRSAV           :4;/*!< Power saving clocking control, bits 27:24 */
         uint32_t _FBAC_Reserved_31_28 :4;/*!< Reserved, bits 31:28 */
      } FBFALLBACK_BITS;
   } Fbfallback;

   /*!
       Defines whole and bit level accesses to the Bank/Pump Ready Register - 0x44
   */
   union FBPRDY
   {
      uint32_t u32Register; /* Bank/Pump Ready Register, bits 31:0 */
      struct
      {
         uint32_t BANKRDY                :8;/*!< Bank Ready, bits 7:0 */
         uint32_t _FBPRDY_Reserved_14_08 :7;/*!< Reserved, bits 14:8 */
         uint32_t PUMPRDY                :1;/*!< Pump Ready, bit 15 */
         uint32_t BANKBUSY               :8;/*!< Bank Busy with FSM, SW_INTF, CPU or PMT, bits 23:16 */
         uint32_t _FBPRDY_Reserved_31_24 :8;/*!< Reserved, bits 31:24 */
      } FBPRDY_BITS;
   } Fbprdy;

   /*!
       Defines whole and bit level accesses to the Pump Access Control Register 1 - 0x48
   */
   union FPAC1
   {
      uint32_t u32Register; /* Flash Pump Access Control Register 1, bits 31:0 */
      struct
      {
         uint32_t  PUMPPWR              :1; /*!< Flash Charge Pump Fallback Power Mode, bit 0 */
         uint32_t _FPAC1_Reserved_15_01 :15;/*!< Reserved, bits 15:1 */
         uint32_t PSLEEP                :11;/*!< Pump Sleep, bits 26:16 */
         uint32_t _FPAC1_Reserved_31_27 :5; /*!< Reserved, bits 31:27 */
      } FPAC1_BITS;
   } Fpac1;

   /*!
       Defines whole and bit level accesses to the Pump Access Control Register 2 - 0x4C
   */
   union FPAC2
   {
      uint32_t u32Register; /* Flash Pump Access Control Register 2, bits 31:0 */
      struct
      {
         uint32_t PAGP                  :16;/*!< Pump Active Grace Period, bits 15:0 */
         uint32_t _FPAC2_Reserved_31_16 :16;/*!< Reserved, bits 31:16 */
      } FPAC2_BITS;
   } Fpac2;

   /*!
       Defines whole and bit level accesses to the Module Access Control Register - 0x50
   */
   union FMAC
   {
      uint32_t u32Register; /* Module Access Control Register, bits 31:0 */
      struct
      {
         uint32_t  BANK                 :3; /*!< Bank Enable, bits 2:0 */
         uint32_t _FMAC_Reserved_31_03 :29;/*!< Reserved, bits 31:3 */
      } FMAC_BITS;
   } Fmac;

   /*!
       Defines whole and bit level accesses to the Module Status Register - 0x54
   */
   union FMSTAT
   {
      uint32_t u32Register; /* Module Status Register, bits 31:0 */
      struct
      {
         uint32_t SLOCK                   :1; /*!< Sector Lock Status, bit 0 */
         uint32_t PSUSP                   :1; /*!< Program Suspend, bit 1 */
         uint32_t ESUSP                   :1; /*!< Erase Suspend, bit 2 */
         uint32_t VOLSTAT                 :1; /*!< Core Voltage Status, bit 3 */
         uint32_t CSTAT                   :1; /*!< Command Status, bit 4 */
         uint32_t INVDAT                  :1; /*!< Invalid Data, bit 5 */
         uint32_t PGM                     :1; /*!< Program Active, bit 6 */
         uint32_t ERS                     :1; /*!< Erase Active, bit 7 */
         uint32_t BUSY                    :1; /*!< Busy, bit 8 */
         uint32_t CV                      :1; /*!< Compact Verify, bit 9 */
         uint32_t EV                      :1; /*!< Erase verify, bit 10 */
         uint32_t PCV                     :1; /*!< Precondidition verify, bit 11 */
         uint32_t PGV                     :1; /*!< Program verify, bit 12 */
         uint32_t DBT                     :1; /*!< Disturbance Test Fail, bit 13 */
         uint32_t ILA                     :1; /*!< Illegal Address, bit 14 */
         uint32_t RVF                     :1; /*!< Read Verify Failure, bit 15 */
         uint32_t RDVER                   :1; /*!< Read Verify command currently underway, bit 16 */
         uint32_t RVSUSP                  :1; /*!< Read Verify Suspend, bit 17 */
         uint32_t _FMSTAT_Reserved_31_18 :14;/*!< Reserved, bits 31:18 */
      } FMSTAT_BITS;
   } FmStat;

   /*!
       Defines whole and bit level accesses to the EEPROM Emulation Data MSW Register - 0x58
   */
   union FEMU_DMSW
   {
      uint32_t u32Register; /* EEPROM Emulation Data MSW Register, bits 31:0 */
   } FemuDmsw;

   /*!
       Defines whole and bit level accesses to the EEPROM Emulation Data LSW Register - 0x5C
   */
   union FEMU_DLSW
   {
      uint32_t u32Register; /* EEPROM Emulation Data LSW Register, bits 31:0 */
   } FemuDlsw;

   /*!
       Defines whole and bit level accesses to the EEPROM Emulation ECC Register - 0x60
   */
   union FEMU_ECC
   {
      uint32_t u32Register; /* EEPROM Emulation ECC Register, bits 31:0 */
      struct
      {
         uint32_t  EMU_ECC                  :8; /*!< EEPROM Emulation ECC, bits 7:0 */
         uint32_t _FEMU_ECC_Reserved_31_08 :24;/*!< Reserved, bits 31:8 */
      } FEMU_ECC_BITS;
   } FemuEcc;

   uint32_t _Reserved_64; /* Reserved Address Locations 0x64 */

   /*!
       Defines whole and bit level accesses to the EEPROM Emulation Address Register - 0x68
   */
   union FEMU_ADDR
   {
      uint32_t u32Register; /* EEPROM Emulation Address, bits 31:0 */
      struct
      {
         uint32_t EMU_ADDR                  :22;/*!< EEPROM Emulation Address, bits 21:0 */
         uint32_t _FEMU_ADDR_Reserved_31_22 :10;/*!< Reserved, bits 31:22 */
      } FEMU_ADDR_BITS;
   } FemuAddr;

   /*!
       Defines whole and bit level accesses to the Diagnostic Control Register - 0x6C
   */
   union FDIAGCTRL
   {
      uint32_t u32Register; /* Diagnostic Control Register, bits 31:0 */
      struct
      {
         uint32_t DIAGMODE                  :3;/*!< Diagnostic Mode, bits 2:0 */
         uint32_t _FDIAGCTRL_Reserved_07_03 :5;/*!< Reserved, bits 7:3 */
         uint32_t DIAG_BUF_SEL              :2;/*!< Diagnostic Buffer Select, bits 9:8 */
         uint32_t _FDIAGCTRL_Reserved_11_10 :2;/*!< Reserved, bits 11:10 */
         uint32_t DIAG_ECC_SEL              :3;/*!< Diagnostic SECDED Select, bits 14-12 */
         uint32_t _FDIAGCTRL_Reserved_15    :1;/*!< Reserved, bit 15 */
         uint32_t DIAG_EN_KEY               :4;/*!< Diagnostic Enable Key, bits 19:16 */
         uint32_t _FDIAGCTRL_Reserved_23_20 :4;/*!< Reserved, bits 23:20 */
         uint32_t DIAG_TRIG                 :1;/*!< Diagnostic Trigger, bit 24 */
         uint32_t _FDIAGCTRL_Reserved_31_25 :7;/*!< Reserved, bits 31:25 */
      } FDIAGCTRL_BITS;
   } FdiagCtrl;

   /*!
       Defines whole and bit level accesses to the Uncorrected Raw Data High Register - 0x70
   */
   union FRAW_DATAH
   {
      uint32_t u32Register; /* Uncorrected Raw Data High, bits 31:0 */
   } FrawDatah;

   /*!
       Defines whole and bit level accesses to the Uncorrected Raw Data Low Register - 0x74
   */
   union FRAW_DATAL
   {
      uint32_t u32Register; /* Uncorrected Raw Data Low, bits 31:0 */
   } FrawDatal;

   /*!
       Defines whole and bit level accesses to the Uncorrected Raw ECC Register - 0x78
   */
   union FRAW_ECC
   {
      uint32_t u32Register; /* Uncorrected Raw ECC, bits 31:0 */
      struct
      {
         uint32_t  RAW_ECC                  :8; /*!< Uncorrected Raw ECC, bits 7:0 */
         uint32_t _FRAW_ECC_Reserved_31_08 :24;/*!< Reserved, bits 31:8 */
      } FRAW_ECC_BITS;
   } FrawEcc;

   /*!
       Defines whole and bit level accesses to the Parity Override Register - 0x7C
   */
   union FPAR_OVR
   {
      uint32_t u32Register; /* Parity Override, bits 31:0 */
      struct
      {
         uint32_t  DAT_INV_PAR              :8; /*!< Data Odd Parity, bits 7:0 */
         uint32_t  ADD_INV_PAR              :1; /*!< Address Odd Parity, bit 8 */
         uint32_t  PAR_OVR_KEY              :3; /*!< Parity Override Key, bits 11:9 */
         uint32_t  BUS_PAR_DIS              :4; /*!< Disable bus parity, bits 15:12 */
         uint32_t  BNK_INV_PAR              :1; /*!< Buffer Invert Parity, bit 16 */
         uint32_t _FPAR_OVR_Reserved_31_17 :15;/*!< Reserved, bits 31:17 */
      } FPAR_OVR_BITS;
   } FparOvr;

   uint32_t _Reserved_80_BC[16];/* Reserved Address Locations 0x80 - 0xBC */

   /*!
       Defines whole and bit level accesses to the Error Detection Sector Disable2 Register - 0xC0
   */
   union FEDACSDIS2
   {
      uint32_t u32Register; /* Error Detection Sector Disable Register, bits 31:0 */
      struct
      {
         uint32_t SectorID2               :4;/*!< Sector ID2 , bits 3:0 */
         uint32_t _FEDACSDIS2_Reserved_4  :1;/*!< Reserved, bit 4 */
         uint32_t BankID2                 :3;/*!< Bank ID2 , bits 7:5 */
         uint32_t SectorID2_inverse       :4;/*!< Sector ID2 Inverse, bits 11:8 */
         uint32_t _FEDACSDIS2_Reserved_12 :1;/*!< Reserved, bit 12 */
         uint32_t BankID2_inverse         :3;/*!< Bank ID2 Inverse, bits 15:13 */
         uint32_t SectorID3               :4;/*!< Sector ID3 , bits 19:16 */
         uint32_t _FEDACSDIS2_Reserved_20 :1;/*!< Reserved, bit 20 */
         uint32_t BankID3                 :3;/*!< Bank ID3 , bits 23:21 */
         uint32_t SectorID3_inverse       :4;/*!< Sector ID3 Inverse, bits 27:24 */
         uint32_t _FEDACSDIS2_Reserved_28 :1;/*!< Reserved, bit 28 */
         uint32_t BankID3_inverse         :3;/*!< Bank ID3 Inverse, bits 31:29 */
      } FEDACSDIS2_BITS;
   } FedAcsDis2;

   uint32_t _Reserved_C4_10C[19];/* Reserved Address Locations 0xC4 - 0x10C */

   /*!
       Defines whole and bit level accesses to the Bank Addr Register - 0x110
   */
   union FADDR
   {
      uint32_t u32Register; /* Bank Addr Register, bits 31:0 */
   } Faddr;

   uint32_t _Reserved_114_11C[3]; /* Reserved Address Locations 0x114-0x11C */

   /*!
       Defines whole and bit level accesses to the FWPWRITE0 Register - 0x120
   */
   union FWPWRITE0
   {
      uint32_t u32Register; /* FWPWRITE0 Register, bits 31:0 */
   } Fwpwrite0;

   /*!
       Defines whole and bit level accesses to the FWPWRITE1 Register - 0x124
   */
   union FWPWRITE1
   {
      uint32_t u32Register; /* FWPWRITE1 Register, bits 31:0 */
   } Fwpwrite1;

   /*!
       Defines whole and bit level accesses to the FWPWRITE2 Register - 0x128
   */
   union FWPWRITE2
   {
      uint32_t u32Register; /* FWPWRITE2 Register, bits 31:0 */
   } Fwpwrite2;

   /*!
       Defines whole and bit level accesses to the FWPWRITE3 Register - 0x12C
   */
   union FWPWRITE3
   {
      uint32_t u32Register; /* FWPWRITE3 Register, bits 31:0 */
   } Fwpwrite3;

   /*!
       Defines whole and bit level accesses to the FWPWRITE4 Register - 0x130
   */
   union FWPWRITE4
   {
      uint32_t u32Register; /* FWPWRITE4 Register, bits 31:0 */
   } Fwpwrite4;

   /*!
       Defines whole and bit level accesses to the FWPWRITE5 Register - 0x134
   */
   union FWPWRITE5
   {
      uint32_t u32Register; /* FWPWRITE5 Register, bits 31:0 */
   } Fwpwrite5;

   /*!
       Defines whole and bit level accesses to the FWPWRITE6 Register - 0x138
   */
   union FWPWRITE6
   {
      uint32_t u32Register; /* FWPWRITE6 Register, bits 31:0 */
   } Fwpwrite6;

   /*!
       Defines whole and bit level accesses to the FWPWRITE7 Register - 0x13C
   */
   union FWPWRITE7
   {
      uint32_t u32Register; /* FWPWRITE7 Register, bits 31:0 */
   } Fwpwrite7;

   /*!
       Defines whole and bit level accesses to the FWPWRITE_ECC Register - 0x140
   */
   union FWPWRITE_ECC
   {
      uint32_t u32Register; /* FWPWRITE_ECC Register, bits 31:0 */
      struct
      {
         uint32_t WPDATA_287_256; /*!< WPDATA[287:256], bits 31:0 */
      } FWPWRITE_ECC_BITS;
      struct
      {
         uint32_t u8Bytes31_24:8;
         uint32_t u8Bytes23_16:8;
         uint32_t u8Bytes15_08:8;
         uint32_t u8Bytes07_00:8;
      } FWPWRITE_ECC_BYTES;
   } FwpwriteEcc;

   uint32_t _Reserved_144_208[50]; /* Reserved Address Locations 0x144-0x208 */

   /*!
       Defines whole and bit level accesses to the FSM Command Register - 0x20C
   */
   union FSM_COMMAND
   {
      uint32_t u32Register; /* FSM Command, bits 31:0 */
      struct
      {
         uint32_t  FSMCMD                      :6; /*!< Flash State Machine Command, bits 5:0 */
         uint32_t _FSM_COMMAND_Reserved_31_06 :26;/*!< Reserved, bits 31:6 */
      } FSM_COMMAND_BITS;
   } FsmCommand;

   uint32_t _Reserved_210_284[30]; /* Reserved Address Locations 0x210-0x284 */

   /*!
       Defines whole and bit level accesses to the FSM Register Write Enable- 0x288
   */
   union FSM_WR_ENA
   {
      uint32_t u32Register; /* FSM Register Write Enable, bits 31:0 */
      struct
      {
         uint32_t  WR_ENA                     :3; /*!< FSM Write Enable, bits 2:0 */
         uint32_t _FSM_WR_ENA_Reserved_31_03 :29;/*!< Reserved, bits 31:3 */
      } FSM_WR_ENA_BITS;
   } FsmWrEna;

   uint32_t _Reserved_28C_2A0[6]; /* Reserved Address Locations 0x28C-0x2A0 */

   /*!
       Defines whole and bit level accesses to the FSM Sector Register - 0x2A4
   */
   union FSM_SECTOR
   {
      uint32_t u32Register; /* FSM Sector, bits 31:0 */
      struct
      {
         uint32_t  _FSM_SECTOR_Reserved_15_0  :8; /*!< Reserved, bits 15:8 */
         uint32_t SECT_ERASED                :16;/*!< Sectors Erased, bits 31:16 */
      } FSM_SECTOR_BITS;
   } FsmSector;

   uint32_t _Reserved_2A8_2B0[3]; /* Reserved Address Locations 0x2A8-0x2B0 */

   /*!
       Defines whole and bit level accesses to the FSM Command Execute Register - 0x2B4
   */
   union FSM_EXECUTE
   {
      uint32_t u32Register; /* FSM Command Execute, bits 31:0 */
      struct
      {
         uint32_t  FSMEXECUTE                  :5; /*!< FSM Command Execute, bits 4:0 */
         uint32_t _FSM_EXECUTE_Reserved_15_05 :11; /*!< Reserved, bits 15:5 */
         uint32_t  SUSPEND_NOW                 :4; /*!< FSM Command Suspend, bits 19:16 */
         uint32_t _FSM_EXECUTE_Reserved_31_20 :12; /*!< Reserved, bits 31:20 */
      } FSM_EXECUTE_BITS;
   } FsmExecute;

   /*!
       Defines whole and bit level accesses to the EEPROM Emulation configuration Register - 0x2B8
   */
   union EEPROM_CONFIG
   {
      uint32_t u32Register; /* EEPROM Emulation configuration, bits 31:0 */
      struct
      {
         uint32_t  AUTOSTART_GRACE               :8; /*!< Auto-suspend Startup Grace Period, bits 7:0 */
         uint32_t  AUTOSUSP_EN                   :1; /*!< Auto-suspend Enable, bit 8 */
         uint32_t  _EEPROM_CONFIG_Reserved_15_09 :7; /*!< Reserved, bits 15:9 */
         uint32_t  EWAIT                         :4; /*!< EEPROM Wait state Counter, bits 19:16 */
         uint32_t _EEPROM_CONFIG_Reserved_31_20 :12; /*!< Reserved, bits 31:20 */
      } EEPROM_CONFIG_BITS;
   } EepromConfig;

   uint32_t _Reserved_2BC;  /* Reserved Address Locations 0x2BC */

   /*!
       Defines whole and bit level accesses to the FSM Sector1 Register - 0x2C0
   */
   union FSM_SECTOR1
   {
      uint32_t u32Register; /* FSM Sector1, bits 31:0 */
   } FsmSector1;

   /*!
       Defines whole and bit level accesses to the FSM Sector2 Register - 0x2C4
   */
   union FSM_SECTOR2
   {
      uint32_t u32Register; /* FSM Sector1, bits 31:0 */
   } FsmSector2;

   uint32_t _Reserved_2C8_304[16];/* Reserved Address Locations 0x2C8 - 0x304 */

   /*!
       Defines whole and bit level accesses to the EEPROM Error Correction Control Register1 - 0x308
   */
   union EE_CTRL1
   {
      uint32_t u32Register; /* EEPROM Error Correction Control Register1, bits 31:0 */
      struct
      {
         uint32_t EE_EDACEN                :4;/*!< Error Detection and Correction Enable, bits 3:0 */
         uint32_t EE_ALL0_OK               :1;/*!< Zero Condition Valid, bit 4 */
         uint32_t EE_ALL1_OK               :1;/*!< One Condition Valid, bit 5 */
         uint32_t _EE_CTRL1_Reserved_07_06 :2;/*!< Reserved, bits 7:6 */
         uint32_t EE_PEN                   :1;/*!< Error Profiling Enable, bit 8 */
         uint32_t EE_EZFEN                 :1;/*!< Error on Zero Fail Enable, bit 9 */
         uint32_t EE_EOFEN                 :1;/*!< Error on One Fail Enable, bit 10 */
         uint32_t _EE_CTRL1_Reserved_15_11 :5;/*!< Reserved, bits 15:11 */
         uint32_t EE_EDACMODE              :4;/*!< Error Correction Mode, bits 19:16 */
         uint32_t _EE_CTRL1_Reserved_31_20 :12;/*!< Reserved, bits 31:20 */
      } EE_CTRL1_BITS;
   } EeCtrl1;

   /*!
       Defines whole and bit level accesses to the EEPROM Error Correction Control Register2 - 0x30C
   */
   union EE_CTRL2
   {
      uint32_t u32Register; /* EEPROM Error Correction Control Register2, bits 31:0 */
      struct
      {
         uint32_t EE_SEC_THRESHOLD          :16;/*!< EEPROM Single Error Correction Threshold, bits 15:0 */
         uint32_t _EE_CTRL2_Reserved_31_16 :16;/*!< Reserved, bits 31:16 */
      } EE_CTRL2_BITS;
   } EeCtrl2;

   /*!
       Defines whole and bit level accesses to the EEPROM Error Correction Counter Register - 0x310
   */
   union EE_COR_ERR_CNT
   {
      uint32_t u32Register; /* EEPROM Error Correction Counter Register, bits 31:0 */
      struct
      {
         uint32_t EE_ERRCNT                      :16;/*!< Correctable Error Counter, bits 15:0 */
         uint32_t _EE_COR_ERR_CNT_Reserved_31_16 :16;/*!< Reserved, bits 31:16 */
      } EE_COR_ERR_CNT_BITS;
   } EeCorErrCnt;

   /*!
       Defines whole and bit level accesses to the EEPROM Correctable Error Address Register - 0x314
   */
   union EE_COR_ERR_ADD
   {
      uint32_t u32Register; /* Correctable Error Address Register, bits 31:0 */
      struct
      {
         uint32_t B_OFF                        :3;/*!< Byte Offset, bits 2:0 */
         uint32_t COR_ERR_ADD                  :29;/*!< Correctable Error Address, bits 31:3 */
      } EE_COR_ERR_ADD_BITS;
   } EeCorErrAdd;

   /*!
       Defines whole and bit level accesses to the EEPROM Correctable Error Position Register - 0x318
   */
   union EE_COR_ERR_POS
   {
      uint32_t u32Register; /* EEPROM Correctable Error Position Register, bits 31:0 */
      struct
      {
         uint32_t  EE_ERR_POS                   :8; /*!< Single Error Position, bits 7:0 */
         uint32_t  TYPE                         :1; /*!< Error Type, bit 8 */
         uint32_t _EE_COR_ERR_POS_Reserved_31_9 :22;/*!< Reserved, bits 31:9 */
      } EE_COR_ERR_POS_BITS;
   } EeCorErrPos;

   /*!
       Defines whole and bit level accesses to the EEPROM Error Status Register - 0x31C
   */
   union EE_STATUS
   {
      uint32_t u32Register; /* EEPROM Error Status Register, bits 31:0 */
      struct
      {
         uint32_t EE_ERR_PRF_FLG            :1;/*!< Error Profiling Status Flag, bit 0 */
         uint32_t EE_ERR_ZERO_FLG           :1;/*!< Error On Zero Fail Status Flag, bit 1 */
         uint32_t EE_ERR_ONE_FLG            :1;/*!< Error On One Fail Status Flag, bit 2 */
         uint32_t EE_D_COR_ERR              :1;/*!< Diagnostic Correctable Error Status Flag, bit 3 */
         uint32_t EE_CME                    :1;/*!< EE ECC Malfunction Status Flag, bit 4 */
         uint32_t _EE_STATUS_Reserved_5     :1;/*!< Reserved, bit 5 */
         uint32_t EE_CMG                    :1;/*!< EE Compare Malfunction Flag, bit 6 */
         uint32_t _EE_STATUS_Reserved_7     :1;/*!< Reserved, bit 7 */
         uint32_t EE_UNC_ERR            :1;/*!< Multiple bit ECC or Parity Error Status Flag, bit 8 */
         uint32_t _EE_STATUS_Reserved_11_9  :3;/*!< Reserved, bits 11:9 */
         uint32_t EE_D_UNC_ERR              :1;/*!< Diagnostic Un-correctable Error Status Flag, bit 12 */
         uint32_t _EE_STATUS_Reserved_31_13 :19;/*!< Reserved, bits 31:13 */
      } EE_STATUS_BITS;
   } EeStatus;

   /*!
       Defines whole and bit level accesses to the Un-correctable Error Address Register - 0x320
   */
   union EE_UNC_ERR_ADD
   {
      uint32_t u32Register; /* Error Status Register, bits 31:0 */
      struct
      {
         uint32_t B_OFF                        :3;/*!< Byte Offset, bits 2:0 */
         uint32_t UNC_ERR_ADD                  :29;/*!< Un-correctable Error Address, bits 31:3 */
      } EE_UNC_ERR_ADD_BITS;
   } EeUncErrAdd;

   uint32_t _Reserved_324_3FC[55];/* Reserved Address Locations 0x324 - 0x3FC */

   /*!
       Defines whole and bit level accesses to the FCFG BANK Register - 0x400
   */
   union FCFG_BANK
   {
      uint32_t u32Register; /* Flash Bank configuration, bits 31:0 */
      struct
      {
         uint32_t  _FCFG_BANK_Reserved_3_0        :4; /*!< Reserved bits 3:0 */
         uint32_t  MAIN_BANK_WIDTH                :12;/*!< MAIN_BANK_WIDTH, bits 15:4 */
         uint32_t  _FCFG_BANK_Reserved_19_16      :4; /*!< Reserved bits 19:16 */
         uint32_t  EE_BANK_WIDTH                  :12;/*!< EE_BANK_WIDTH, bits 31:20 */
      } FCFG_BANK_BITS;
   } FcfgBank;

} Fapi_FmcRegistersType;
#endif

#endif /* REGISTERS_LE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: Registers_FMC_LE.h
 *********************************************************************************************************************/
