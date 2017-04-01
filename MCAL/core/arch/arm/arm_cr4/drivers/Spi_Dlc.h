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

/** @tagSettings DEFAULT_ARCHITECTURE=TMS570 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#ifndef SPI_DLC_H
#define SPI_DLC_H


#include "Std_Types.h"

#define SPI_DLC_MIBTXSIZE    128U
#define SPI_DLC_MIBRXSIZE    128U

/* type for Register Readback */
typedef enum
{
    SPI_GCR0_RB = 0U,
    SPI_GCR1_RB,
    SPI_DEF_RB,
    SPI_EN_RB
} Spi_DlcRegRdbkType;

/* the register space is addressed as structure pointer */
typedef struct
{
    volatile uint16 TxCtrl;
    volatile uint16 TxData;
}Spi_TxField;

typedef struct
{
    volatile uint16 RxStat;
    volatile uint16 RxData;
}Spi_RxField;

typedef struct
{
    volatile uint32 Spi_FUN  ; /* Offset: 0x14 */
    volatile uint32 Spi_DIR  ; /* Offset: 0x18 */
    volatile uint32 Spi_DIN  ; /* Offset: 0x1C */
    volatile uint32 Spi_DOUT ; /* Offset: 0x20 */
    volatile uint32 Spi_DSET ; /* Offset: 0x24 */
    volatile uint32 Spi_DCLR ; /* Offset: 0x28 */
    volatile uint32 Spi_PDR  ; /* Offset: 0x2C */
    volatile uint32 Spi_PDIS ; /* Offset: 0x30 */
    volatile uint32 Spi_PSEL ; /* Offset: 0x34 */
} Spi_PinCtrlType;

typedef struct
{
    volatile uint32 Spi_FMT[4U] ;
} Spi_FMTRegType;

typedef struct
{
    volatile uint32 Spi_TGITENST  ; /* Offset: 0x74 */
    volatile uint32 Spi_TGITENCR  ; /* Offset: 0x78 */
    volatile uint32 Spi_TGITLVST  ; /* Offset: 0x7C */
    volatile uint32 Spi_TGITLVCR  ; /* Offset: 0x80 */
    volatile uint32 Spi_TGINTFLAG ; /* Offset: 0x84 */
    volatile uint32 Spi_Reserved0 ; /* Offset: 0x88 */
    volatile uint32 Spi_Reserved1 ; /* Offset: 0x8C */
    volatile uint32 Spi_TICKCNT   ; /* Offset: 0x90 */
    volatile uint32 Spi_LTGPEND   ; /* Offset: 0x94 */
    volatile uint32 Spi_TGCTRL[16U] ; /* Offset: 0x98 - 0xD4 */
} Spi_TGCTRLRegType;

typedef struct
{
    volatile uint32 Spi_DMACTRL[8U] ;  /* Offset: 0xD8- 0xF8 */
    volatile uint32 Spi_DMACOUNT[8U] ; /* Offset: 0xFC - 0x114 */
    volatile uint32 Spi_DMACNTLEN ;   /* Offset: 0x118 */
} Spi_DMACTRLRegType;

typedef struct
{
    volatile uint32 Spi_GCR0 ;         /* Offset: 0x00 */
    volatile uint32 Spi_GCR1 ;         /* Offset: 0x04 */
    volatile uint32 Spi_INT0 ;         /* Offset: 0x08 */
    volatile uint32 Spi_LVL  ;         /* Offset: 0x0C */
    volatile uint32 Spi_FLG  ;         /* Offset: 0x10 */
    Spi_PinCtrlType Spi_PC ;           /* Offset: 0x14 - 0x34 */
    volatile Spi_TxField Spi_DAT0 ;    /* Offset: 0x38 */
    volatile Spi_TxField Spi_DAT1 ;    /* Offset: 0x3C */
    volatile Spi_RxField Spi_BUF  ;    /* Offset: 0x40 */
    volatile uint32 Spi_EMU  ;         /* Offset: 0x44 */
    volatile uint16 Spi_DELAY[2U] ;     /* Offset: 0x48 */
    volatile uint32 Spi_DEF   ;        /* Offset: 0x4C */
    volatile uint32 Spi_FMT[4U] ;       /* Offset: 0x50 - 0x5C */
    volatile uint32 Spi_TGINTVECT[2U];  /* Offset: 0x60 -0x64 */
    volatile uint32 Spi_SRSEL  ;       /* Offset: 0x68 */
    volatile uint32 Spi_PMCTRL ;       /* Offset: 0x6C */
    volatile uint32 Spi_EN  ;          /* Offset: 0x70 */
    Spi_TGCTRLRegType Spi_RegTGCTL ;   /* Offset: 0x74 - 0xD4 */
    Spi_DMACTRLRegType Spi_RegDMACTRL; /* Offset: 0xD8 - 0x118 */
    volatile uint32 Spi_Reserved2 ;    /* Offset: 0x11C */
    volatile uint32 Spi_UERRCTRL ;     /* Offset: 0x120 */
    volatile uint32 Spi_UERRSTAT ;     /* Offset: 0x124 */
    volatile uint32 Spi_UERRADDR1 ;    /* Offset: 0x128 */
    volatile uint32 Spi_UERRADDR0 ;    /* Offset: 0x12C */
    volatile uint32 Spi_RXOVRN_ADDR;   /* Offset: 0x130 */
    volatile uint32 Spi_IOLPBTSTCR ;   /* Offset: 0x134 */
    volatile uint32 Spi_EXT_PRESCALE1; /* Offset: 0x138 */
}Spi_RegisterType;

typedef struct
{
    volatile Spi_TxField Spi_TxBank[SPI_DLC_MIBTXSIZE] ; /* TxBank consists of 16bit control and 16bit txdata */
    volatile Spi_RxField Spi_RxBank[SPI_DLC_MIBRXSIZE] ; /* RxBank consists of 16bit status  and 16bit rxdata */
}Spi_RamBufferType ;

typedef P2VAR(volatile Spi_RegisterType,  AUTOMATIC, MSR_REGSPACE) Spi_RegisterPtrType ;
typedef P2VAR(volatile Spi_RamBufferType, AUTOMATIC, MSR_REGSPACE) Spi_RamBufferPtrType;

typedef struct
{
    uint8 Spi_RamUsed;
    uint8 Spi_DmaUsed;
    uint8 Spi_UnitID;
}Spi_HWUnitPropertyType;

typedef P2CONST(Spi_HWUnitPropertyType, AUTOMATIC, SPI_CONST) Spi_HWUnitPropertyPtrType;

typedef struct
{
    Spi_RegisterPtrType Reg_pt;        /* pointer to unit registers */
    Spi_RamBufferPtrType Ram_pt;       /* pointer to unit ram (NULL_PTR) if unit has no ram */
    Spi_HWUnitPropertyPtrType Prop_pt; /* pointer to unit properties */
}Spi_HWUnitMapType;

typedef P2VAR(Spi_HWUnitMapType, AUTOMATIC, SPI_VAR_NOINIT) Spi_HWUnitMapPtrType;


#define SPI_REGISTER_BASE_0 (Spi_RegisterPtrType) (0xFFF7F400U)
#define SPI_REGISTER_BASE_1 (Spi_RegisterPtrType) (0xFFF7F600U)
#define SPI_REGISTER_BASE_2 (Spi_RegisterPtrType) (0xFFF7F800U)
#define SPI_REGISTER_BASE_3 (Spi_RegisterPtrType) (0xFFF7FA00U)
#define SPI_REGISTER_BASE_4 (Spi_RegisterPtrType) (0xFFF7FC00U)

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
#define SPI_RAM_BASE_0      (Spi_RamBufferPtrType) (0xFF0E0000U)
#define SPI_RAM_BASE_1      (Spi_RamBufferPtrType) (0x00000000U) /*Null*/
#define SPI_RAM_BASE_2      (Spi_RamBufferPtrType) (0xFF0C0000U)
#define SPI_RAM_BASE_3      (Spi_RamBufferPtrType) (0x00000000U) /*Null*/
#define SPI_RAM_BASE_4      (Spi_RamBufferPtrType) (0xFF0A0000U)
#elif defined(CFG_TMS570LC43X)
#define SPI_RAM_BASE_0      (Spi_RamBufferPtrType) (0xFF0E0000U)
#define SPI_RAM_BASE_1      (Spi_RamBufferPtrType) (0xFF080000U)
#define SPI_RAM_BASE_2      (Spi_RamBufferPtrType) (0xFF0C0000U)
#define SPI_RAM_BASE_3      (Spi_RamBufferPtrType) (0xFF060000U)
#define SPI_RAM_BASE_4      (Spi_RamBufferPtrType) (0xFF0A0000U)
#else
#error This SPI driver does not support this MCU.
#endif

/*---------------------------------------------------*/
/* Register bit mask definitions for MIB registers   */
/*---------------------------------------------------*/
/* naming of the macros is: [REGISTERNAME]_[REGISTERFLAG] */
/* val is the value to be set, bit if available is the bit to set */
/* i.e. TICKCNT_TICKVALUE_SET: set a the TICKCNT register with the TICKVALUE */

#define SPI_WRITEVAL(reg, val)  ((reg) = (val))
#define SPI_READVAL(var, reg)   ((var) = (reg))
#define SPI_SETVAL16(reg, val)    ((reg) |= (uint16)(val))
#define SPI_GETVAL16(reg, mask)   ((reg) &  (uint16)(mask))
#define SPI_CLRVAL16(reg, val)    ((reg) &= (~(uint16)(val)))

#define SPI_SETVAL32(reg, val)    ((reg) |= (uint32)(val))
#define SPI_GETVAL32(reg, mask)   ((reg) &  (uint32)(mask))
#define SPI_CLRVAL32(reg, val)    ((reg) &= (~(uint32)(val)))

/* define for SPIFLG */
#define SPI_BUFINIT          ((uint32)1u << 24)
/*---------------------------------------------------*/
/* Spi_RegTGCTL.Spi_TICKCNT register masks, RW */
/*---------------------------------------------------*/
/* set: set a value to the specified register bit */
#define TICKCNT_TICKVALUE(val)    ((uint32)(val) << 0U)       /* bit 0:15  */
#define TICKCNT_CLKCTRL(val)      ((uint32)(val) << 28U)      /* bit 28:29 */
#define TICKCNT_RELOAD(val)       ((uint32)(val) << 30U)      /* bit 30    */
#define TICKCNT_TICKENA(val)      ((uint32)(val) << 31U)      /* bit 31    */

/*---------------------------------------------------*/
/* Spi_RegTGCTL.Spi_LTGPEND register masks, RW       */
/*---------------------------------------------------*/
#define LTGPEND_LPEND(val)        ((uint32)(val) << 8U)       /* bit 8:14   */
#define LTGPEND_TGINSERVICE(val)  ((uint32)(val) << 24U)      /* bit 24:28  */

/*---------------------------------------------------*/
/* Spi_TGINTVECT[x] register masks, read only        */
/*---------------------------------------------------*/
#define TGINTVECT_SUSPEND(val)    ((uint32)(val) << 0U)       /* bit 0     */
#define TGINTVECT_INTVEC(val)     ((uint32)(val) << 1U)       /* bit 1:5   */

/*---------------------------------------------------*/
/* Spi_EN register masks, RW                         */
/*---------------------------------------------------*/
#define MIBSPIE_EN(val)           ((uint32)(val) << 0U)       /* bit 0     */

/*---------------------------------------------------*/
/* Spi_GCR1 register masks, RW                       */
/*---------------------------------------------------*/
#define MIBSPIEGCR1_MASTER(val)   ((uint32)(val)<< 0U)       /* bit 0     */
#define MIBSPIEGCR1_CLKMOD(val)   ((uint32)(val)<< 1U)       /* bit 1     */
#define MIBSPIEGCR1_SPIEN(val)    ((uint32)(val)<< 24U)      /* bit 24    */

/*---------------------------------------------------*/
/* Spi_RegTGCTL.Spi_TGITENST register masks, RW      */
/*---------------------------------------------------*/
#define TGITENST_SETINTENRDY(val,bit)    ((uint32)(val) << (bit))      /* bit y from 0:31 */

/*---------------------------------------------------*/
/* Spi_RegTGCTL.Spi_TGITENCR register masks, RW      */
/*---------------------------------------------------*/
#define TGITENCR_CLRINTENRDY(val,bit)    ((uint32)(val) << (bit))      /* bit y from 0:31 */

/*---------------------------------------------------*/
/* Spi_RegTGCTL.Spi_TGITLVST register masks, RW      */
/*---------------------------------------------------*/
#define TGITLVST_SETINTLEVEL(val,bit)    ((uint32)(val) << (bit))     /* bit y from 0:31 */

/*---------------------------------------------------*/
/* Spi_RegTGCTL.Spi_TGITLVCR register masks, RW      */
/*---------------------------------------------------*/
#define TGITLVCR_SETINTLEVEL(val,bit)    ((uint32)(val) << (bit))      /* bit y from 0:31 */

/*---------------------------------------------------*/
/* Spi_RegTGCTL.TGCTRL register masks, RW      */
/*---------------------------------------------------*/
#define TGCTRL_PCURRENT(val)    ((uint32)(val) << 0U)     /* bit 0:6   */
#define TGCTRL_PSTART(val)      ((uint32)(val) << 8U)     /* bit 8:14  */
#define TGCTRL_TRIGSRC(val)     ((uint32)(val) << 16U)    /* bit 16:19 */
#define TGCTRL_TRIGEVT(val)     ((uint32)(val) << 20U)    /* bit 20:23 */
#define TGCTRL_TGTD(val)        ((uint32)(val) << 28U)    /* bit 28    */
#define TGCTRL_PRST(val)        ((uint32)(val) << 29U)    /* bit 29    */
#define TGCTRL_TGONESHOT(val)   ((uint32)(val) << 30U)    /* bit 30    */
#define TGCTRL_TGENA(val)       ((uint32)(val) << 31U)    /* bit 31    */

/*---------------------------------------------------*/
/* Spi_RegFMT register masks, RW      */
/*---------------------------------------------------*/
#define SPIFMT_CHARLEN(val)    ((uint32)(val) << 0U)     /* bit 0:4   */
#define SPIFMT_PRESCALE(val)   ((uint32)(val) << 8U)     /* bit 8:15  */
#define SPIFMT_PHASE(val)      ((uint32)(val) << 16U)    /* bit 16    */
#define SPIFMT_POLARITY(val)   ((uint32)(val) << 17U)    /* bit 17    */
#define SPIFMT_DISCSTIMER(val) ((uint32)(val) << 18U)    /* bit 18    */
#define SPIFMT_SHIFTDIR(val)   ((uint32)(val) << 20U)    /* bit 20    */
#define SPIFMT_WAITENA(val)    ((uint32)(val) << 21U)    /* bit 21    */
#define SPIFMT_PARITYENA(val)  ((uint32)(val) << 22U)    /* bit 22    */
#define SPIFMT_PARPOL(val)     ((uint32)(val) << 23U)    /* bit 23    */
#define SPIFMT_WDELAY(val)     ((uint32)(val) << 24U)    /* bit 24:29 */

#define SPIFMT_CHARLEN_MASK    (0x1FU)
/*---------------------------------------------------*/
/* MIBRAM Registers */
/*---------------------------------------------------*/
/* Spi_TXRAM register masks, RW                      */
/*---------------------------------------------------*/
#define TXRAMCTRL_DATA        (0x0000U)  /* bit 0-7  */    /* bit 0:15  */
#define TXRAMCTRL_CSNR        (0x0100U)  /* bit 8    */     /* bit 16:23 */
#define TXRAMCTRL_DFSEL       (0x0200U)  /* bit 9    */     /* bit 24:25 */
#define TXRAMCTRL_WDEL        (0x0400U)  /* bit 10   */    /* bit 26    */
#define TXRAMCTRL_LOCK        (0x0800U)  /* bit 11   */    /* bit 27    */
#define TXRAMCTRL_CSHOLD      (0x1000U)  /* bit 12   */    /* bit 28    */
#define TXRAMCTRL_BUFMODE     (0x2000U)  /* bit 13   */    /* bit 29:31 */
/*
 * Spi_RXRAM register masks, R with auto clear
 */
#define RXRAMCTRL_LCSNR         (0x0000U)  /* bit 0-7  */
#define RXRAMCTRL_DLENERR       (0x0100U)  /* bit 8    */
#define RXRAMCTRL_TIMEOUT       (0x0200U)  /* bit 9    */
#define RXRAMCTRL_PARITYERR     (0x0400U)  /* bit 10   */
#define RXRAMCTRL_DESYNC        (0x0800U)  /* bit 11   */
#define RXRAMCTRL_BITERR        (0x1000U)  /* bit 12   */
#define RXRAMCTRL_TXFULL        (0x2000U)  /* bit 13   */
#define RXRAMCTRL_RXOVR         (0x4000U)  /* bit 14   */
#define RXRAMCTRL_RXEMPTY       (0x8000U)  /* bit 15   */
/* special case , if (value & error mask) = 0, everything is fine */
#define RXRAMCTRL_ERRORMASK     0x5F000000U

/*---------------------------------------------------*/
/* get, set: low/high word of a uint32               */
/*---------------------------------------------------*/
#define SPI_DLC_LOWWORD_SET(val)     (((uint32)(val) & 0x0000FFFFU) << 0U)   /* bit 0:15   */
#define SPI_DLC_HIGHWORD_SET(val)    (((uint32)(val) & 0x0000FFFFU) << 16U)  /* bit 16:31  */

#define SPI_DLC_LOWWORD_GET(val)     (uint16)(((uint32)(val) & 0x0000FFFFU))   /* bit 0:15   */
#define SPI_DLC_HIGHWORD_GET(val)    (uint16)(((uint32)(val) & 0xFFFF0000U) >> 16U)  /* bit 16:31  */

/*---------------------------------------------------*/
/* for tx control field                              */
/*---------------------------------------------------*/
#define SPI_DLC_TXCTRL_BUFMOD(val)    (uint16) ((val) << 13U)
#define SPI_DLC_TXCTRL_CSHOLD(val)    (uint16) ((val) << 12U)
#define SPI_DLC_TXCTRL_DFSEL(val)     (uint16) ((val) << 8U)

/*---------------------------------------------------*/
/* get, set: low/high byte of a uint16               */
/*---------------------------------------------------*/
#define SPI_DLC_LOWBYTE_SET(val)     (uint16)(((uint32)(val) & 0x00FFU) << 0U)    /* bit 0:7   */
#define SPI_DLC_HIGHBYTE_SET(val)    (uint16)(((uint32)(val) & 0x00FFU) << 8U)    /* bit 8:15  */

#define SPI_DLC_LOWBYTE_GET(val)     ((uint8)(((uint32)(val) & 0x00FFU)))          /* bit 0:8   */
#define SPI_DLC_HIGHBYTE_GET(val)    ((uint8)(((uint32)(val) & 0xFF00U) >> 8U))    /* bit 8:15  */

/* define bit masks */
#define SPI_DLC_BITCLR    0x00000000U
#define SPI_DLC_CHECK_BIT08(val,bit)  ((uint8) (val) & (1 << (bit))) == (1 << (bit))
#define SPI_DLC_CHECK_BIT16(val,bit)  ((uint16)(val) & (1 << (bit))) == (1 << (bit))
#define SPI_DLC_CHECK_BIT32(val,bit)  ((uint32)(val) & (1 << (bit))) == (1 << (bit))
#define SPI_DLC_CHECK_HEX08(val,bval) (((uint8) (val) & (bval)) == (bval))
#define SPI_DLC_CHECK_HEX16(val,bval) (((uint16)(val) & (bval)) == (bval))
#define SPI_DLC_CHECK_HEX32(val,bval) (((uint32)(val) & (bval)) == (bval))

/* maximum number of bytes for one transfer group */
#define SPI_DLC_TX_RAM_SHIFT    (7U)
/* number of available transfer groups*/
#define SPI_DLC_TG_NUM          (1U)

#define SPI_DLC_TG_LEN          (1u << SPI_DLC_TX_RAM_SHIFT)
/* oneshot mode = 0, time triggered mode = 1 */
#define SPI_DLC_MODE            (STD_OFF)
/* max priority of a job (ASR conform) */
#define SPI_MAX_JOB_PRIO        (3U)
#define SPI_DLC_MAXHWUNIT       (5U)

extern CONST(Spi_RegisterPtrType, SPI_CONST) Spi_HWUnit_at[];
extern CONST(Spi_RamBufferPtrType, SPI_CONST) Spi_RamUnit_at[];
extern CONST(Spi_HWUnitPropertyType, SPI_CONST) Spi_UnitProperty_at[];

/* state for guard operations */
enum
{
    SPI_DLC_G_IDLE = 0U,
    SPI_DLC_G_PENDING = 1U,
    SPI_DLC_G_ACTIVE = 2U,
    SPI_DLC_G_FINISHED = 3U
};

typedef enum
{
    SPI_DLC_TX = 0U,
    SPI_DLC_RX = 1U
}Spi_DlcTxRxDefType;

typedef enum
{
    SPI_DLC_FRAME08 = 0U,
    SPI_DLC_FRAME16 = 1U
}Spi_DlcFrameDefType;

typedef enum
{
    SPI_DLC_STDUNIT = 0U,
    SPI_DLC_MIBUNIT = 1U
}Spi_DlcOptionDefType;

/* event definitions of the spi job state machine */
typedef enum
{
    SPI_DLC_EV_SYNCTX = 0U,
    SPI_DLC_EV_ASYNCTX = 1U,
    SPI_DLC_EV_CONSUMED = 2U
} Spi_DlcEventDefType;

typedef enum
{
    SPI_DLC_ST_OK = 0U,
    SPI_DLC_ST_PENDING = 1U,
    SPI_DLC_ST_FAILED = 2U,
    SPI_DLC_ST_FINISHED = 3U,
    SPI_DLC_ST_CANCELED = 4U
}Spi_DlcChannelStateType;

typedef struct
{
    P2FUNC(void, SPI_CODE ,Init)(uint32 HwUnit_u32);
    P2FUNC(void, SPI_CODE ,Close)(uint32 HwUnit_u32);
    P2FUNC(void, SPI_CODE ,FillData)(uint32 HwUnit_u32);
    P2FUNC(void, SPI_CODE ,DrainData)(uint32 HwUnit_u32);
    P2FUNC(void, SPI_CODE ,Trigger)(uint32 HwUnit_u32);
    P2FUNC(uint16, SPI_CODE, Transmit)(uint32 HwUnit_u32);
    P2FUNC(void, SPI_CODE ,Error)(uint32 HwUnit_u32);
}Spi_DlcFunctionType;

/* event object definitions of the spi job state machine */
typedef struct
{
    /* the first three entries are part of the Interface and shall not be changed */
    volatile uint8 Event_u8;
    volatile uint8 Guard_u8 ;  /* used for fill status of buffer*/
    uint8  JobID_u8 ;      /* ID of the job */
    uint8  Res_u8   ;      /* dummy */

    uint16 Pos_u16[2U] ;   /* position in a channel [0=Tx, 1=Rx] */
    uint8  ID_u8[2U]  ;    /* ID of the Channel [0=Tx, 1=Rx] */
    uint8  Num_u8[2U] ;    /* number of Channels [0=Tx, 1=Rx] */

    uint16 TxCtrl_u16 ;    /* for transmit control */
    uint16 RxStat_u16 ;    /* for receive status   */
    uint16 Default_u16[2U]; /* default data */
    uint16 Data_u16;       /* valid data */
    uint8  DFSel_u8[2U] ;   /* data format word [0=CS_ID ,1=ExtDev]*/
} Spi_DlcEventType;

typedef P2VAR(Spi_DlcEventType, AUTOMATIC, SPI_VAR) Spi_DlcEventPtrType;
typedef uint32 Spi_DlcInstType;
typedef uint32 Spi_DlcIsrType;

/* driver uses no chip select */
#define SPI_NO_CHIP_SELECT    255U

/* pointer types for 8, 16 bit frame transfer */
typedef P2VAR(uint8, AUTOMATIC,  SPI_APPL_DATA) Spi_DlcFrame8PtrType;
typedef P2VAR(uint16, AUTOMATIC, SPI_APPL_DATA) Spi_DlcFrame16PtrType;

FUNC(void, SPI_CODE) Spi_DlcInit(void) ;
FUNC(void, SPI_CODE) Spi_DlcClose(void) ;
FUNC(Std_ReturnType, SPI_CODE) Spi_DlcSetEvent
(
    P2CONST(Spi_DlcEventType, AUTOMATIC, SPI_VAR_NOINIT) Dlc_Event_pt
);
FUNC(void, SPI_CODE) Spi_IrqTxRxERR(uint32 HwUnit_u32) ;
FUNC(void, SPI_CODE) Spi_IrqTxRx(uint32 HwUnit_u32) ;

FUNC(void, SPI_CODE) Spi_DlcBlockCbk(void);

FUNC(void, SPI_CODE) Spi_DlcEnableLpbk(uint8 HwUnit, uint8 LbMode);

FUNC(void, SPI_CODE) Spi_DlcDisableLpbk(uint8 HwUnit);

FUNC(uint32, SPI_CODE) Spi_DlcRegisterRdbk(Spi_DlcRegRdbkType DlcRegRdbck,uint8 HwUnit);

#endif /* SPI_DLC_H */
