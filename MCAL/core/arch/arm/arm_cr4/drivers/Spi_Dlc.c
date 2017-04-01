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

#define SPI_DLC_SOURCE 1

/* includes */
#include "Spi.h"
#include "Spi_Hw.h"
#include "SchM_Spi.h"
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
#include "Spi_DlcDma.h"
#endif /* defined(CFG_TMS570LS12X) */
#include "Cpu.h"


/* macros */
#define SPI_DLC_MAXOPT       (2U)
#define SPI_DLC_STDOPT       (0U)
#define SPI_DLC_RAMOPT       (1U)

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
CONST(Dma_ChannelSelectType, SPI_VAR) Dma_MapChannel[] =
{
    {SPI_DLC_RXUNIT0_Channel, SPI_DLC_TXUNIT0_Channel}
    ,{SPI_DLC_RXUNIT1_Channel, SPI_DLC_TXUNIT1_Channel}
    ,{SPI_DLC_RXUNIT2_Channel, SPI_DLC_TXUNIT2_Channel}
    ,{SPI_DLC_RXUNIT3_Channel, SPI_DLC_TXUNIT3_Channel}
    ,{SPI_DLC_RXUNIT4_Channel, SPI_DLC_TXUNIT4_Channel}
};

CONST(uint8, SPI_VAR) Dma_ChanneltoHWunit[] =
{
    1U,  /* Channel 0 is used by SPI2 */
    1U,  /* Channel 1 is used by SPI2 */
    3U,  /* Channel 2 is used by SPI4 */
    3U   /* Channel 3 is used by SPI4 */
};
#endif /* defined(CFG_TMS570LS12X) */

#define SPI_ANALOG_LOOPBACK_MASK    (0x00000A02)

#define SPI_DIGITAL_LOOPBACK_MASK   (0x00000A00)

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
#define Spi_Dlc(Type, Name)    Spi_Dlc##Type##Name
#define Spi_Irq(Type, Name)    Spi_Irq##Type##Name
#endif /* CFG_TMS570LS12X */

/* data */

#define SPI_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

/* we have to schedule one transfer group */
static Spi_DlcEventType Spi_DlcEvent_t[SPI_DLC_MAXHWUNIT];
/* for hardware unit mapping */
static Spi_HWUnitMapType Spi_HWUnitMap_at[SPI_DLC_MAXHWUNIT] =
{
    {NULL_PTR, NULL_PTR, NULL_PTR},
    {NULL_PTR, NULL_PTR, NULL_PTR},
    {NULL_PTR, NULL_PTR, NULL_PTR},
    {NULL_PTR, NULL_PTR, NULL_PTR},
    {NULL_PTR, NULL_PTR, NULL_PTR},
};

static Spi_DlcFunctionType Spi_DlcOptionSelect[SPI_DLC_MAXOPT];

#define SPI_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"


#define SPI_START_SEC_CODE
#include "MemMap.h"

/* function prototypes */

/* interface functions  are part of the Spi_Dlc.h */
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
/* derived functions with option Ram, the macro Spi_Dlc(Ram,Init) expands to Spi_DlcRamInit  */
static FUNC(void, SPI_CODE) Spi_Dlc(Ram,Init)       (uint32 HwUnit_u32);
static FUNC(void, SPI_CODE) Spi_Dlc(Ram,Close)      (uint32 HwUnit_u32);
static FUNC(void, SPI_CODE) Spi_Dlc(Ram,FillData)   (uint32 HwUnit_u32);
static FUNC(void, SPI_CODE) Spi_Dlc(Ram,DrainData)  (uint32 HwUnit_u32);
static FUNC(void, SPI_CODE) Spi_Dlc(Ram,TriggerData)(uint32 HwUnit_u32);

/* derived functions with option Std */
static FUNC(void, SPI_CODE) Spi_Dlc(Std,Init)       (uint32 HwUnit_u32);
static FUNC(void, SPI_CODE) Spi_Dlc(Std,Close)      (uint32 HwUnit_u32);
static FUNC(void, SPI_CODE) Spi_Dlc(Std,FillData)   (uint32 HwUnit_u32);
static FUNC(void, SPI_CODE) Spi_Dlc(Std,DrainData)  (uint32 HwUnit_u32);
static FUNC(void, SPI_CODE) Spi_Dlc(Std,TriggerData)(uint32 HwUnit_u32);
static FUNC(void, SPI_CODE) Spi_Dlc(Std, PrepareDma)
(
    uint32 HwUnit_u32,
    Spi_DlcTxRxDefType Dir_t
);
#endif /* defined(CFG_TMS570LS12X) */

/* functions of master class */
static FUNC(void, SPI_CODE) Spi_DlcConsumeEvent(uint32 HwUnit_u32);
static FUNC(void, SPI_CODE) Spi_DlcTransmit(uint32 HwUnit_u32);
static FUNC(uint16 , SPI_CODE) Spi_DlcRamTransmit(uint32 HwUnit_u32);
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
static FUNC(uint16 , SPI_CODE) Spi_DlcStdTransmit(uint32 HwUnit_u32);
#endif /* defined(CFG_TMS570LS12X) */

static FUNC(Std_ReturnType, SPI_CODE) Spi_DlcSwitchChannel
(
    uint32 HwUnit_u32,
    P2VAR(volatile uint16, AUTOMATIC, SPI_VAR) Ctrl_pt,
    P2VAR(Spi_DlcEventType, AUTOMATIC, SPI_VAR) Ev_pt,
    Spi_DlcTxRxDefType Dir_t
);
static FUNC(void, SPI_CODE) Spi_DlcError        (uint32 HwUnit_u32);

static void Spi_GlobalSuspend(void);
static void Spi_GlobalRestore(void);

/* functions */

static void Spi_GlobalSuspend(void)
{
    SchM_Enter_Spi_EA_0();
}

static void Spi_GlobalRestore(void)
{
    SchM_Exit_Spi_EA_0();
}

/* SourceId : SPI_SourceId_062 */
/* Requirements : AR_SPI_SR31, AR_SPI_SR34, AR_SPI_SR206, AR_SPI_SR226 */
static FUNC(void, SPI_CODE) Spi_DlcRamFillData(uint32 HwUnit_u32)
{
    uint8  ChIDTx_u8    ; /* channel identifier, Rx used as index */
    uint16 TgLen_u16    ; /* local transfer group length */
    uint16 TxPos_u16    ; /* buffer filled counter, increases with each successful write/read to MIB Ram */
    uint16 DefData_u16  ; /* local default data value, to prevent too many rom accesses */
    uint16 DataLoc_u16  ; /* local default data value */
    P2VAR(Spi_BufferDescriptorType, AUTOMATIC, SPI_APPL_DATA) ChBufTx_pt; /* pointer to Tx channel buffer */
    Spi_DlcEventPtrType DlcEv_pt;
    Spi_RamBufferPtrType MRam_pt;
    Std_ReturnType EVal_t;  /* evaluate return value of Spi_DlcSwitchChannel */

    DlcEv_pt = &Spi_DlcEvent_t[HwUnit_u32];
    MRam_pt  = Spi_HWUnitMap_at[HwUnit_u32].Ram_pt;
    if(Spi_HWUnitMap_at[HwUnit_u32].Ram_pt == NULL_PTR)
    {
      return;
    }
    switch(DlcEv_pt->Guard_u8)
    {
        case SPI_DLC_G_PENDING:
        DlcEv_pt->Guard_u8 = (uint8)SPI_DLC_G_ACTIVE ;
        /* fall through */

        case SPI_DLC_G_ACTIVE:
        /* mark the transfer group */
        TgLen_u16  = 0U ;

        /* in this module we try to transmit one or more channels, depending on the configuration */
        /* max transfer amount per transfer group*/
        while(TgLen_u16 < SPI_DLC_TG_LEN)
        {
            ChIDTx_u8 = DlcEv_pt->ID_u8[SPI_DLC_TX] ;
            TxPos_u16 = DlcEv_pt->Pos_u16[SPI_DLC_TX];
            /* handle buffers for Tx and Rx */
            ChBufTx_pt  = Spi_ConfigPtr_pt->Spi_ChannelCfg[ChIDTx_u8].Spi_Descriptor ;
            if(ChBufTx_pt == NULL_PTR)
            {
              return;
            }
            DefData_u16 = DlcEv_pt->Default_u16[SPI_DLC_TX];
            /*
            * this loop transfers data from the channel(s) to RAM
            * and uses interrupts to transfer and reload the data
            */
            while(TxPos_u16 < ChBufTx_pt->Spi_TxRxLength)
            {
                /* check i transfer group is full */
                if(TgLen_u16 == SPI_DLC_TG_LEN)
                {
                    /* transfer group is full, write position back and leave */
                    DlcEv_pt->Pos_u16[SPI_DLC_TX] = TxPos_u16;
                    return;
                }
                else
                {
                    /* no action */
                }
                /* get Mib status */
                DlcEv_pt->RxStat_u16 = MRam_pt->Spi_RxBank[TgLen_u16].RxStat;
                /* ready to fill ? */
                /* the ram buffer should only be filled if the flag is zero, otherwise the data was not transmitted */
                if(SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_TXFULL))
                {
                    /* this should not happen! */
                    Spi_DlcError(HwUnit_u32);
                    return;
                }
                else
                {
                    /* setup data */
                    MRam_pt->Spi_TxBank[TgLen_u16].TxCtrl = DlcEv_pt->TxCtrl_u16;
                    if(ChBufTx_pt->Spi_Tx_pt == NULL_PTR)
                    {
                        /* write default data */
                        DataLoc_u16 = DefData_u16;
                    }
                    else
                    {
                        /* write bytes to the channel */
                        if(Spi_ConfigPtr_pt->Spi_ChannelCfg[ChIDTx_u8].Spi_DataWidth == 8U)
                        {
                            /* use uint8 buffer mode */
                            DataLoc_u16 = ((Spi_DlcFrame8PtrType)ChBufTx_pt->Spi_Tx_pt)[TxPos_u16];
                        }
                        else
                        {
                            /* use uint16 buffer mode */
                            DataLoc_u16 = ((Spi_DlcFrame16PtrType)ChBufTx_pt->Spi_Tx_pt)[TxPos_u16];

                            /* 32Bit mode selected? */
                            if(Spi_ConfigPtr_pt->Spi_ChannelCfg[ChIDTx_u8].Spi_DataWidth == 32U)
                            {
                               /* First 16 bits of 32 word? */
                               if(0U == (TgLen_u16 % 2))
                               {
                                  /* Enable CSHOLD */
                                  SPI_SETVAL16(MRam_pt->Spi_TxBank[TgLen_u16].TxCtrl, TXRAMCTRL_CSHOLD) ;
                                  /* Disable WDEL */
                                  SPI_CLRVAL16(MRam_pt->Spi_TxBank[TgLen_u16].TxCtrl, TXRAMCTRL_WDEL) ;
                                  /* If LSB selected, invert 16bit words */
                                  if(Spi_ConfigPtr_pt->Spi_ChannelCfg[ChIDTx_u8].Spi_TxStart == SPI_LSB)
                                  {
                                     DataLoc_u16 = ((Spi_DlcFrame16PtrType)ChBufTx_pt->Spi_Tx_pt)[TxPos_u16+1];
                                  }
                               }
                               else
                               {
                                  /* If LSB selected, invert 16bit words */
                                  if(Spi_ConfigPtr_pt->Spi_ChannelCfg[ChIDTx_u8].Spi_TxStart == SPI_LSB)
                                  {
                                     DataLoc_u16 = ((Spi_DlcFrame16PtrType)ChBufTx_pt->Spi_Tx_pt)[TxPos_u16-1];
                                  }
                               }
                            }
                        }
                    }
                    MRam_pt->Spi_TxBank[TgLen_u16].TxData = DataLoc_u16;
                    /* data filled, increase count */
                    TxPos_u16++;
                    TgLen_u16++ ;
                }
            }
            EVal_t = Spi_DlcSwitchChannel(HwUnit_u32,
                                          &MRam_pt->Spi_TxBank[(TgLen_u16-1)].TxCtrl,
                                          DlcEv_pt,
                                          SPI_DLC_TX);
            if(EVal_t == E_NOT_OK)
            {
                /* all channels have been processed */
                break;
            }
        }
        break ;

        default:
        break ;
    }
    return;
}

/* SourceId : SPI_SourceId_063 */
/* Requirements : AR_SPI_SR207, AR_SPI_SR227 */
static FUNC(void, SPI_CODE) Spi_DlcRamDrainData(uint32 HwUnit_u32)
{
    uint16 TgLen_u16    ; /* local transfer group length */
    uint16 RxPos_u16    ; /* buffer filled counter, increases with each successful write/read to MIB Ram */
    P2VAR(Spi_BufferDescriptorType, AUTOMATIC, SPI_APPL_DATA) ChBufRx_pt ; /* pointer to channel buffer internal or external */
    Spi_DlcEventPtrType DlcEv_pt;
    Spi_RamBufferPtrType MRam_pt;
    uint8  ChIDRx_u8    ;   /* channel identifier, used as index */
    uint16 DataLoc_u16   ;   /* local data value from MIB Ram register */
    Std_ReturnType EVal_t;  /* evaluate return value of Spi_DlcSwitchChannel */
    uint8 Guard;

    DlcEv_pt = &Spi_DlcEvent_t[HwUnit_u32];
    MRam_pt  = Spi_HWUnitMap_at[HwUnit_u32].Ram_pt;
    if(Spi_HWUnitMap_at[HwUnit_u32].Ram_pt == NULL_PTR)
    {
         return;
    }
    /* in this module we try to transmit one or more channels, depending on the configuration */
    Guard = DlcEv_pt->Guard_u8;
    switch(Guard)
    {
        case SPI_DLC_G_ACTIVE:
        case SPI_DLC_G_FINISHED:
        /* mark the transfer group */
        TgLen_u16  = 0U ;

        /* copy data to mib Rx buffer */
        /* in this module we try to transmit one or more channels, depending on the configuration */
        /* max transfer amount per transfer group*/
        while(TgLen_u16 < SPI_DLC_TG_LEN)
        {
            ChIDRx_u8  = DlcEv_pt->ID_u8[SPI_DLC_RX];
            RxPos_u16  = DlcEv_pt->Pos_u16[SPI_DLC_RX];
            /* handle buffers for Rx */
            ChBufRx_pt = Spi_ConfigPtr_pt->Spi_ChannelCfg[ChIDRx_u8].Spi_Descriptor ;
            if(ChBufRx_pt == NULL_PTR)
            {
              return;
            }
            /* this loop drains data from MIB ram to the channel(s)*/
            while(RxPos_u16 < ChBufRx_pt->Spi_TxRxLength)
            {
                if(TgLen_u16 == SPI_DLC_TG_LEN)
                {
                    /* transfer group is full, write position back and leave */
                    DlcEv_pt->Pos_u16[SPI_DLC_RX] = RxPos_u16;
                    return;
                }
                /* access MIB ram */
                /* read of this register resets the RX flag to 1 */
                DlcEv_pt->RxStat_u16 = MRam_pt->Spi_RxBank[TgLen_u16].RxStat;
                /* ready to drain ? */
                if(SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_RXEMPTY))
                {
                    /* this should not happen! */
                    Spi_DlcError(HwUnit_u32);
                    return;
                }
                else
                {
                    DataLoc_u16 = MRam_pt->Spi_RxBank[TgLen_u16].RxData;
                    if(ChBufRx_pt->Spi_Rx_pt == NULL_PTR)
                    {
                        /* skip any data, but data must be read to clear the flag, see line above */
                    }
                    else
                    {
                        /* read bytes to the channel */
                        if(Spi_ConfigPtr_pt->Spi_ChannelCfg[ChIDRx_u8].Spi_DataWidth == 8U)
                        {
                            /* use uint8 buffer mode */
                            ((Spi_DlcFrame8PtrType)ChBufRx_pt->Spi_Rx_pt)[RxPos_u16] = (uint8)DataLoc_u16;
                        }
                        else
                        {
                            /* use uint16 buffer mode */
                            ((Spi_DlcFrame16PtrType)ChBufRx_pt->Spi_Rx_pt)[RxPos_u16] = DataLoc_u16;
                        }
                    }
                    /* data drained, increase count */
                    RxPos_u16++;
                    TgLen_u16++ ;
                }
            }
            /* all bytes in a channel have been treated, select next channel */
            {
                /* one channel received, prepare next */
                EVal_t = Spi_DlcSwitchChannel(HwUnit_u32,
                                              NULL_PTR,
                                              DlcEv_pt,
                                              SPI_DLC_RX);
                if(EVal_t == E_NOT_OK)
                {
                    /* all channels have been processed */
                    break;
                }
            }
        }
        break ;

        default:
        break ;
    }
}

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
static FUNC(void, SPI_CODE) Spi_Dlc(Std, FillData)(uint32 HwUnit_u32)
{
    uint16 DefData_u16  ; /* local default data value, to prevent too many rom accesses */
    uint16 TxPos_u16    ; /* local data value for Tx position in buffer */
    P2VAR(Spi_BufferDescriptorType, AUTOMATIC, SPI_APPL_DATA) ChBufTx_pt; /* pointer to Tx channel buffer */
    Spi_DlcEventPtrType DlcEv_pt;
    Spi_RegisterPtrType MStd_pt;
    uint8  ChIDTx_u8    ; /* channel identifier, Rx used as index */
    uint16 DataLoc_u16  ; /* local data value for Tx */
    uint8 Guard;

    DlcEv_pt = &Spi_DlcEvent_t[HwUnit_u32];
    MStd_pt  = Spi_HWUnitMap_at[HwUnit_u32].Reg_pt;
    Guard = DlcEv_pt->Guard_u8;
    switch(Guard)
    {
        case SPI_DLC_G_PENDING:
        DlcEv_pt->Guard_u8 = (uint8)SPI_DLC_G_ACTIVE ;
        /* fall through */

        case SPI_DLC_G_ACTIVE:

        /* in this module we try to transmit one Data unit */
        /* in this module we try to transmit one or more channels, depending on the configuration */
        ChIDTx_u8 = DlcEv_pt->ID_u8[SPI_DLC_TX] ;
        /* handle buffers for Tx and Rx */
        ChBufTx_pt  = Spi_ConfigPtr_pt->Spi_ChannelCfg[ChIDTx_u8].Spi_Descriptor ;
        DefData_u16 = DlcEv_pt->Default_u16[SPI_DLC_TX];
        TxPos_u16   = DlcEv_pt->Pos_u16[SPI_DLC_TX];
        /*
         * this loop transfers data from the channel(s) to RAM
         * and uses interrupts to transfer and reload the data
         */
        /* get status */
        DlcEv_pt->RxStat_u16 = MStd_pt->Spi_BUF.RxStat;
        /* ready to fill ? */
        /* the buffer should only be filled if the flag is zero, otherwise the data was not transmitted */
        if(SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_TXFULL))
        {
            /* this should not happen! */
            Spi_DlcError(HwUnit_u32);
        }
        else
        {
            /* setup data */
            MStd_pt->Spi_DAT1.TxCtrl = DlcEv_pt->TxCtrl_u16;
            if(ChBufTx_pt->Spi_Tx_pt == NULL_PTR)
            {
                /* write default data */
                DataLoc_u16 = DefData_u16;
            }
            else
            {
                /* write bytes to the channel */
                if(Spi_ConfigPtr_pt->Spi_ChannelCfg[ChIDTx_u8].Spi_DataWidth == 8U)
                {
                    /* use uint8 buffer mode */
                    DataLoc_u16 = ((Spi_DlcFrame8PtrType)ChBufTx_pt->Spi_Tx_pt)[TxPos_u16];
                }
                else
                {
                    /* use uint16 buffer mode */
                    DataLoc_u16 = ((Spi_DlcFrame16PtrType)ChBufTx_pt->Spi_Tx_pt)[TxPos_u16];
                }
            }
            /* data filled, increase count */
            TxPos_u16++;
        }
        if(TxPos_u16 < ChBufTx_pt->Spi_TxRxLength)
        {
            /* write data back for next transfer */
            DlcEv_pt->Pos_u16[SPI_DLC_TX]++;
        }
        else
        {
            /* Spi_DlcSwitchChannel changes the Guard_u8 state if a channel end has been reached */
            (FUNC(void, SPI_CODE)) Spi_DlcSwitchChannel(HwUnit_u32,
                                                        &MStd_pt->Spi_DAT1.TxCtrl,
                                                        DlcEv_pt,
                                                        SPI_DLC_TX);
        }
        break ;

        default:
        break ;
    }
    DlcEv_pt->Data_u16 = DataLoc_u16;
    return;
}

static FUNC(void, SPI_CODE) Spi_Dlc(Std, DrainData)(uint32 HwUnit_u32)
{
    uint16 RxPos_u16    ; /* buffer filled counter, increases with each successful write/read to MIB Ram */
    uint16 DataLoc_u16; /* local data value */
    P2VAR(Spi_BufferDescriptorType, AUTOMATIC, SPI_APPL_DATA) ChBufRx_pt ; /* pointer to channel buffer internal or external */
    Spi_DlcEventPtrType DlcEv_pt;
    Spi_RegisterPtrType MStd_pt;
    uint8  ChIDRx_u8    ; /* channel identifier, used as index */
    uint8 Guard;

    DlcEv_pt = &Spi_DlcEvent_t[HwUnit_u32];
    MStd_pt  = Spi_HWUnitMap_at[HwUnit_u32].Reg_pt;

    /* in this module we try to transmit one or more channels, depending on the configuration */
    Guard = DlcEv_pt->Guard_u8;
    switch(Guard)
    {
        case SPI_DLC_G_ACTIVE:
        case SPI_DLC_G_FINISHED:
        ChIDRx_u8  = DlcEv_pt->ID_u8[SPI_DLC_RX];
        RxPos_u16  = DlcEv_pt->Pos_u16[SPI_DLC_RX];
        ChBufRx_pt = Spi_ConfigPtr_pt->Spi_ChannelCfg[ChIDRx_u8].Spi_Descriptor;

        /* drains data from Spi register to channel(s)*/
        /* read of this register resets the RX flag to 1 */
        DlcEv_pt->RxStat_u16 = MStd_pt->Spi_BUF.RxStat;
        /* ready to drain ? */
        if((DlcEv_pt->RxStat_u16 & RXRAMCTRL_RXEMPTY) == 0U)
        {
            DataLoc_u16 = MStd_pt->Spi_BUF.RxData;
            if(ChBufRx_pt->Spi_Rx_pt == NULL_PTR)
            {
                /* skip any data, but data must be read to clear the flag, seee line above */
            }
            else
            {
                /* read bytes to the channel */
                if(Spi_ConfigPtr_pt->Spi_ChannelCfg[ChIDRx_u8].Spi_DataWidth == 8U)
                {
                    /* use uint8 buffer mode */
                    ((Spi_DlcFrame8PtrType)ChBufRx_pt->Spi_Rx_pt)[RxPos_u16] = (uint8)DataLoc_u16;
                }
                else
                {
                    /* use uint16 buffer mode */
                    ((Spi_DlcFrame16PtrType)ChBufRx_pt->Spi_Rx_pt)[RxPos_u16] = DataLoc_u16;;
                }
            }
        }
        else
        {
            /* this should not happen! */
            Spi_DlcError(HwUnit_u32);
        }
        /* data drained, increase count */
        RxPos_u16++;
        if(RxPos_u16 < ChBufRx_pt->Spi_TxRxLength)
        {
            /* write data back for next transfer */
            DlcEv_pt->Pos_u16[SPI_DLC_RX]++;
        }
        else
        {
            (FUNC(void, SPI_CODE)) Spi_DlcSwitchChannel(HwUnit_u32,
                                                        &MStd_pt->Spi_BUF.RxData,
                                                        DlcEv_pt,
                                                        SPI_DLC_RX);
        }
        break ;

        default:
        break ;
    }
}

/* Requirements : AR_SPI_SR206, AR_SPI_SR207, AR_SPI_SR226, AR_SPI_SR227 */
static FUNC(void, SPI_CODE) Spi_Dlc(Std, PrepareDma)
(
    uint32 HwUnit_u32,
    Spi_DlcTxRxDefType Dir_t
)
{
    P2VAR(Spi_BufferDescriptorType, AUTOMATIC, SPI_APPL_DATA) ChBuf_pt; /* pointer to Tx channel buffer */
    Spi_DlcEventPtrType DlcEv_pt;
    VAR(Dma_ChannelSetupType, AUTOMATIC) ChSetup_t;
    Spi_RegisterPtrType MStd_pt;
    uint16 Count_u16;
    uint16 Offset_u16;
    uint8  ChID_u8;


    /* to trigger a Dma transfer, the first data must be manually written to the register
     *  to handle this, the value OffsetTx_u8 is added to address and subtracted from length
     */

    DlcEv_pt = &Spi_DlcEvent_t[HwUnit_u32];
    MStd_pt  = Spi_HWUnitMap_at[HwUnit_u32].Reg_pt;
    ChID_u8  = DlcEv_pt->ID_u8[Dir_t];
    ChBuf_pt = Spi_ConfigPtr_pt->Spi_ChannelCfg[ChID_u8].Spi_Descriptor;
    /* setup length */
    Count_u16  = ChBuf_pt->Spi_TxRxLength - DlcEv_pt->Pos_u16[Dir_t];
    Offset_u16 = 0U;

    /* check for a channel if there is no need to switch a channel, the Dma can refill the register
     *  several times with a frame transfer not using any interrupts. Also check if the channel is the last
     *  channel belonging to a job - the TxCtrl field must be adapted to deactivate the CS# signal
     */
    /* set element count */
    ChSetup_t.ECount = 1U;
    ChSetup_t.FCount = Count_u16;
    /* frame count is set according to the following conditions */
    if(DlcEv_pt->Num_u8[Dir_t] >= Spi_ConfigPtr_pt->Spi_JobCfg[DlcEv_pt->JobID_u8].Spi_ChannelList[0U])
    {
       /* Last channel to transmit */
       DlcEv_pt->Guard_u8 = SPI_DLC_G_IDLE;
    }

    /* address next element by incrementing the address is not used */
    ChSetup_t.EIDstInc = 0U;
    ChSetup_t.EISrcInc = 0U;
    ChSetup_t.FISrcInc = 0U;
    ChSetup_t.FIDstInc = 0U;
    /* the element count is zero if the channel has a length of one byte or word
     * so only setup a Rx Dma to receive the data
     */
    ChSetup_t.Unit   = (uint16) HwUnit_u32;
    ChSetup_t.Channel = Dma_MapChannel[HwUnit_u32].Dmachannel[1U];
    ChSetup_t.Direction = DMA_TX;
    /* place control field */
    MStd_pt->Spi_DAT1.TxCtrl = DlcEv_pt->TxCtrl_u16;
    /* setup channel 0 for std and fill the data field.
     * Writing to the data field of the  Spi_DAT1 register generates the Dma requests
     */
    ChSetup_t.DstAddr = (uint32)&MStd_pt->Spi_DAT1.TxData;
    if(ChBuf_pt->Spi_Tx_pt == NULL_PTR)
    {
        ChSetup_t.SrcAddr = (uint32)&DlcEv_pt->Default_u16[SPI_DLC_TX];
        /* 8 bit DMA: source and destination are 16bit aligned so to access the lower value in big endian
         * the address has to be increased [xxDD] ;   [xxDD]
         *                  starting here   ^  moving to ^
         *                  this applies to source address as well as the destination address
         */
        if(Spi_ConfigPtr_pt->Spi_ChannelCfg[ChID_u8].Spi_DataWidth == 8U)
        {
            ChSetup_t.ChCtrl = DMA_STDTX08_CONST;
            /* to transmit real 8bit via Dma, the source and destination must be increased by one */
            ChSetup_t.DstAddr++;
            ChSetup_t.SrcAddr++;
        }
        else
        {
            ChSetup_t.ChCtrl = DMA_STDTX16_CONST;
        }
    }
    else
    {
        if(Spi_ConfigPtr_pt->Spi_ChannelCfg[ChID_u8].Spi_DataWidth == 8U)
        {
            ChSetup_t.ChCtrl = DMA_STDTX08_INC;
            /* to transmit real 8bit via Dma, the destination must be increased */
            ChSetup_t.DstAddr++;
            ChSetup_t.SrcAddr  = (uint32) &((Spi_DlcFrame8PtrType)ChBuf_pt->Spi_Tx_pt)[Offset_u16];
        }
        else
        {
            ChSetup_t.ChCtrl = DMA_STDTX16_INC;
            /* set the address to a aligned 16 bit address */
            ChSetup_t.SrcAddr  = (uint32) &((Spi_DlcFrame16PtrType)ChBuf_pt->Spi_Tx_pt)[Offset_u16];
        }
    }
    Dma_Setup(&ChSetup_t);
    /* now the Dma is prepared for Tx, now prepare next two channels for Rx */
    /* setup channel 1 for std and read the data field.
     * incoming data to the Spi_BUF field register generates the Dma Rx requests
     */
    ChSetup_t.Channel = Dma_MapChannel[HwUnit_u32].Dmachannel[0U];
    ChSetup_t.Direction = DMA_RX;

    ChSetup_t.SrcAddr = (uint32)&MStd_pt->Spi_BUF.RxData;
    if(ChBuf_pt->Spi_Rx_pt == NULL_PTR)
    {
        ChSetup_t.DstAddr = (uint32)&DlcEv_pt->Default_u16[SPI_DLC_RX];
        if(Spi_ConfigPtr_pt->Spi_ChannelCfg[ChID_u8].Spi_DataWidth == 8U)
        {
            ChSetup_t.ChCtrl = DMA_STDRX08_CONST;
            /* to receive real 8bit via Dma, the source and destination must be increased, see line 694 */
            ChSetup_t.DstAddr++;
            ChSetup_t.SrcAddr++;
        }
        else
        {
            ChSetup_t.ChCtrl = DMA_STDRX16_CONST;
        }
    }
    else
    {
        if(Spi_ConfigPtr_pt->Spi_ChannelCfg[ChID_u8].Spi_DataWidth == 8U)
        {
            ChSetup_t.ChCtrl = DMA_STDRX08_INC;
            /* to receive real 8bit via Dma, the source must be increased */
            ChSetup_t.SrcAddr++;
            /* write data to Rx channel */
            ChSetup_t.DstAddr  = (uint32) &((Spi_DlcFrame8PtrType)ChBuf_pt->Spi_Rx_pt)[Offset_u16];
        }
        else
        {
            ChSetup_t.ChCtrl = DMA_STDRX16_INC;
            /* write data to Rx channel */
            ChSetup_t.DstAddr  = (uint32) &((Spi_DlcFrame16PtrType)ChBuf_pt->Spi_Rx_pt)[Offset_u16];
        }
    }
    /* setup channel 1 for std and read the data fields */
    Dma_Setup(&ChSetup_t);
}
#endif /* defined(CFG_TMS570LS12X) */

static FUNC(void, SPI_CODE) Spi_DlcRamTriggerData(uint32 HwUnit_u32)
{
     /* transfer group is ready for transfer, trigger interrupt generation */
    Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_RegTGCTL.Spi_TGCTRL[0U] |= TGCTRL_TGENA(1U) ;
}

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
static FUNC(void, SPI_CODE) Spi_Dlc(Std,TriggerData)(uint32 HwUnit_u32)
{
    /* data is ready for transfer, trigger interrupt generation */
    Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_DAT1.TxData = Spi_DlcEvent_t[HwUnit_u32].Data_u16;
}
#endif /* defined(CFG_TMS570LS12X) */

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
static FUNC(void, SPI_CODE) Spi_DlcConsumeEvent(uint32 HwUnit_u32)
{
    Spi_HWUnitMapPtrType MStd_pt;
    uint8  Ram_u8 ;   /* temporary parameter for RamUsed ON/OFF */

    MStd_pt = &Spi_HWUnitMap_at[HwUnit_u32];
    Ram_u8  = MStd_pt->Prop_pt->Spi_RamUsed;

    Spi_DlcTransmit(HwUnit_u32) ;
    Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_DlcResult[HwUnit_u32] = SPI_DLC_PENDING;
    if(MStd_pt->Prop_pt->Spi_DmaUsed == STD_ON)
    {
        Spi_Dlc(Std, PrepareDma)(HwUnit_u32, SPI_DLC_TX);
        /* enable DmaReq to generate the first pulse */
        MStd_pt->Reg_pt->Spi_INT0 |= 0x00010000U;
    }
    else
    {
        Spi_DlcOptionSelect[Ram_u8].FillData(HwUnit_u32);
        /* this triggers the normal data transfer */
        Spi_DlcOptionSelect[Ram_u8].Trigger(HwUnit_u32);
    }
}
#elif defined(CFG_TMS570LC43X)
static FUNC(void, SPI_CODE) Spi_DlcConsumeEvent(uint32 HwUnit_u32)
{
    Spi_DlcTransmit(HwUnit_u32) ;
    Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_DlcResult[HwUnit_u32] = SPI_DLC_PENDING;

    Spi_DlcRamFillData(HwUnit_u32);
    /* this triggers the normal data transfer */
    Spi_DlcRamTriggerData(HwUnit_u32);
}
#else
#error This SPI driver does not support this MCU.
#endif

/* Requirements : AR_SPI_SR98 */
static FUNC(void, SPI_CODE) Spi_DlcError(uint32 HwUnit_u32)
{
    Spi_DlcEventPtrType  DlcEv_pt;
    Spi_HWUnitMapPtrType MUnit_pt;
    uint16 Error_u16     ; /* local error level */
    uint8  JobIDLoc_u8   ; /* job identifier, used as index */
      /* set the simulated job, error and HW unit */
    JobIDLoc_u8   = SPI_DLC_LOWBYTE_GET(HwUnit_u32);
    HwUnit_u32 = Spi_ConfigPtr_pt->Spi_JobCfg[JobIDLoc_u8].Spi_HWUnitID;
    
    MUnit_pt = &Spi_HWUnitMap_at[HwUnit_u32];
    DlcEv_pt = &Spi_DlcEvent_t[HwUnit_u32];
    /* this value if not zero, indicates that the error function was called from Fill/Drain function */
    if(DlcEv_pt->RxStat_u16 != 0U)
    {
#if (SPI_DEM_ERROR_REPORTING == STD_ON)
        if(SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_TXFULL))
        {
            /* the transmit function has been called, but the sequencer still has not processed the buffer */
            Dem_ReportErrorStatus(SPI_E_TXSTALL_ERROR, DEM_EVENT_STATUS_FAILED);
        }
        else if(SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_RXEMPTY))
        {
            /* the receive function has been called, but the sequencer still has not processed the buffer */
            Dem_ReportErrorStatus(SPI_E_RXSTALL_ERROR, DEM_EVENT_STATUS_FAILED);
        }
        else
        {
            /* no action */
        }
#endif
    }
    else
    {
        if (MUnit_pt->Prop_pt->Spi_RamUsed == STD_ON)
        {
            /* the ovverrun value ranges from 0x200 - 0x3FC, so we have to subtract an offset */
            Error_u16 = MUnit_pt->Reg_pt->Spi_RXOVRN_ADDR - SPI_DLC_MIBTXSIZE;
            DlcEv_pt->RxStat_u16 = MUnit_pt->Ram_pt->Spi_RxBank[Error_u16].RxStat;
        }
        else
        {
            DlcEv_pt->RxStat_u16 = MUnit_pt->Reg_pt->Spi_BUF.RxStat;
        }
#if (SPI_DEM_ERROR_REPORTING == STD_ON)
        /* report to DEM */
        if(SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_BITERR))
        {
            /* bit error*/
            Dem_ReportErrorStatus(SPI_E_BIT_ERROR, DEM_EVENT_STATUS_FAILED) ;
        }
        else if(SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_DESYNC))
        {
            /* desynch error*/
            Dem_ReportErrorStatus(SPI_E_DESYNC_ERROR, DEM_EVENT_STATUS_FAILED) ;
        }
        else if(SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_TIMEOUT))
        {
            /* timeout error */
            Dem_ReportErrorStatus(SPI_E_TO_ERROR, DEM_EVENT_STATUS_FAILED) ;
        }
        else if(SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_DLENERR))
        {
            /* data length error */
            Dem_ReportErrorStatus(SPI_E_DLEN_ERROR, DEM_EVENT_STATUS_FAILED) ;
        }
        else if(SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_RXOVR))
        {
            /* overwrite occurred, Rx */
            Dem_ReportErrorStatus(SPI_E_DOVR_ERROR, DEM_EVENT_STATUS_FAILED) ;
        }
        else
        {
            /* no action */
        }
#endif
    }

    /* release job */
    DlcEv_pt->RxStat_u16 = 0U;
    DlcEv_pt->Guard_u8 = SPI_DLC_G_IDLE ;
    DlcEv_pt->Event_u8 = SPI_DLC_EV_CONSUMED;
    Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_DlcResult[HwUnit_u32] = SPI_DLC_FAILED ;
    Spi_HwJobComplete(JobIDLoc_u8, HwUnit_u32) ;
}

static FUNC(Std_ReturnType, SPI_CODE) Spi_DlcSwitchChannel
(
    uint32 HwUnit_u32,
    P2VAR(volatile uint16, AUTOMATIC, SPI_VAR) Ctrl_pt,
    P2VAR(Spi_DlcEventType, AUTOMATIC, SPI_VAR) Ev_pt,
    Spi_DlcTxRxDefType Dir_t
)
{
    uint32 TGReg_u32;
    uint8  ChIDTxRx_u8  ; /* channel identifier, used as index */
    uint8  ChIdx_u8     ; /* channel index of a channel list */
    uint8  ExtDev_u8     ; /* channel index of a channel list */
    Std_ReturnType RVal = E_OK;

    /* one channel transferred, prepare next */
    ExtDev_u8 = Ev_pt->DFSel_u8[1U];
    Ev_pt->Num_u8[Dir_t]++;
    /* all channels in a job transferred ? */
    if(Ev_pt->Num_u8[Dir_t] > Spi_ConfigPtr_pt->Spi_JobCfg[Ev_pt->JobID_u8].Spi_ChannelList[0U])
    {
        /* execute this only if CS handling is selected as active and in TX mode */
        if(  (Ev_pt->DFSel_u8[0U] != SPI_NO_CHIP_SELECT)
          && (Ctrl_pt != NULL_PTR))
        {
            /* finish job, and deactivate CS */
            SPI_CLRVAL16(*Ctrl_pt, TXRAMCTRL_CSHOLD);
        }
        else
        {
            /* no action */
        }
        /* all channels in a job transmitted */
        if(Dir_t == SPI_DLC_TX)
        {
            /* if tx direction detects a end of all channels, the state is finished */
            Ev_pt->Guard_u8 = SPI_DLC_G_FINISHED;
        }
        else
        {
            /* if rx direction detects a end of all channels, the state is idle, because
             * all data has been transmitted and received
             * */
            Ev_pt->Guard_u8 = SPI_DLC_G_IDLE;
        }
        RVal = E_NOT_OK;
    }
    else
    {
        /* get next channel to receive */
        Ev_pt->Pos_u16[Dir_t] = 0U;
        ChIdx_u8              = Ev_pt->Num_u8[Dir_t];
        ChIDTxRx_u8           = Spi_ConfigPtr_pt->Spi_JobCfg[Ev_pt->JobID_u8].Spi_ChannelList[ChIdx_u8];
        Ev_pt->ID_u8[Dir_t]   = ChIDTxRx_u8;
        /* now get the format word an clear the channel related parameters */
        TGReg_u32 = Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_FMT[0U];
        /* set the new values */
        SPI_CLRVAL32(TGReg_u32, SPIFMT_CHARLEN(SPIFMT_CHARLEN_MASK) | SPIFMT_SHIFTDIR(1U));
        /* set new char length (here 8bit) */
        if(32U == (Spi_ConfigPtr_pt->Spi_ChannelCfg[ChIDTxRx_u8].Spi_DataWidth))
        {
           /* Hardware supports up to 16 bits */
           SPI_SETVAL32(TGReg_u32, SPIFMT_CHARLEN(16U));
        }
        else
        {
           SPI_SETVAL32(TGReg_u32, SPIFMT_CHARLEN(Spi_ConfigPtr_pt->Spi_ChannelCfg[ChIDTxRx_u8].Spi_DataWidth));
        }
         /* set shift dir (LSB or MSB) */
        SPI_SETVAL32(TGReg_u32, SPIFMT_SHIFTDIR(Spi_ConfigPtr_pt->Spi_ChannelCfg[ChIDTxRx_u8].Spi_TxStart));
        /* set WDELAY */
        SPI_SETVAL32(TGReg_u32, SPIFMT_WDELAY(Spi_ConfigPtr_pt->Spi_DevCfg[ExtDev_u8].Spi_CsIdleTime));
        /* values set, update the register */
        SPI_SETVAL32(Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_FMT[0U], TGReg_u32);
    }
    return(RVal);
}

/* Requirements : AR_SPI_SR24, AR_SPI_SR25 */
static FUNC(void, SPI_CODE) Spi_DlcTransmit(uint32 HwUnit_u32)
{
    uint32 TGReg_u32    ; /* local register mirror */
    uint32 CSVal_u32    ; /* local value for chip select */
    uint8  ExtDev_u8    ; /* local external device, used as index  */
    uint8  TMS_SpiModeWA[4U]; /* the modes of the TMS Spi do not match the Spi Mode Matrix, so they have to be converted */
    uint8  JobIDLoc_u8     ; /* job identifier, used as index */
    uint8  ChIDTxRx_u8     ; /* channel identifier, used as index */
    Spi_DlcEventPtrType DlcEv_pt;
    P2CONST(Spi_ExternalDeviceConfigType, AUTOMATIC, SPI_PBCFG) DevCfg_pt;
    P2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_PBCFG) ChCfg_pt;
    Spi_HWUnitMapPtrType MUnit_pt;

    DlcEv_pt = &Spi_DlcEvent_t[HwUnit_u32];
    MUnit_pt = &Spi_HWUnitMap_at[HwUnit_u32];

    TGReg_u32 = 0U;

    TMS_SpiModeWA[0U] = 1U; /* the index is the real Spi mode, the contents the TMS Spi mode */
    TMS_SpiModeWA[1U] = 0U;
    TMS_SpiModeWA[2U] = 3U;
    TMS_SpiModeWA[3U] = 2U;

    /* start with high prio job, IdxLev0_uloc is the TG index, equal to the job priority  */
    JobIDLoc_u8 = DlcEv_pt->JobID_u8 ;
    /* external device assigned to a job */
    ExtDev_u8   = Spi_ConfigPtr_pt->Spi_JobCfg[JobIDLoc_u8].Spi_ExDev ;
    /* the guard signals the job to be transmitted */
    if(DlcEv_pt->Guard_u8 == SPI_DLC_G_PENDING)
    {
        /* start with first channel in a job */
        /* the assignment starts with index 1, index 0 is the number of channels */
        DlcEv_pt->Num_u8[SPI_DLC_TX] = 1U ;
        DlcEv_pt->Num_u8[SPI_DLC_RX] = 1U ;
        /* get first channel ID in a job */
        ChIDTxRx_u8 = Spi_ConfigPtr_pt->Spi_JobCfg[JobIDLoc_u8].Spi_ChannelList[1U] ;
        /* save ChID for later transmit */
        DlcEv_pt->ID_u8[SPI_DLC_TX] = ChIDTxRx_u8 ;
        DlcEv_pt->ID_u8[SPI_DLC_RX] = ChIDTxRx_u8 ;
        /* reset channel pointer for Tx,Rx  */
        DlcEv_pt->Pos_u16[SPI_DLC_TX] = 0U ;
        DlcEv_pt->Pos_u16[SPI_DLC_RX] = 0U ;
        DlcEv_pt->Default_u16[SPI_DLC_TX] = Spi_ConfigPtr_pt->Spi_ChannelCfg[ChIDTxRx_u8].Spi_DefaultTxData;
        DlcEv_pt->Default_u16[SPI_DLC_RX] = 0U; /* us a memory location to store and trash data */

        DevCfg_pt = &Spi_ConfigPtr_pt->Spi_DevCfg[ExtDev_u8];
        ChCfg_pt  = &Spi_ConfigPtr_pt->Spi_ChannelCfg[ChIDTxRx_u8];
        /* set other data related parameters                               */

        /* set clock polarity (clock idle level) and */
        /* set phase (data shift edge), apply the TMS WA */
        SPI_SETVAL32(TGReg_u32, SPIFMT_PHASE(TMS_SpiModeWA[DevCfg_pt->Spi_Mode]));
        /* this register holds the data format word, which is vital for transmission */
        MUnit_pt->Reg_pt->Spi_FMT[0U] = TGReg_u32;
        /* For every channel we need to update the data format word */
        /* set new char length (here 8bit) */
        if(32U == (ChCfg_pt->Spi_DataWidth))
        {
           /* Hardware supports up to 16 bits */
           SPI_SETVAL32(TGReg_u32, SPIFMT_CHARLEN(16U));
        }
        else
        {
           SPI_SETVAL32(TGReg_u32, SPIFMT_CHARLEN(ChCfg_pt->Spi_DataWidth));
        }
         /* set shift dir (LSB or MSB) */
        SPI_SETVAL32(TGReg_u32, SPIFMT_SHIFTDIR(ChCfg_pt->Spi_TxStart));
        /* set WDELAY */
        SPI_SETVAL32(TGReg_u32, SPIFMT_WDELAY(DevCfg_pt->Spi_CsIdleTime));

        /* Prescaler */
        if (DevCfg_pt->Spi_Prescaler < 255) {
            SPI_SETVAL32(TGReg_u32, SPIFMT_PRESCALE(DevCfg_pt->Spi_Prescaler));
        } else {
            SPI_SETVAL32(MUnit_pt->Reg_pt->Spi_EXT_PRESCALE1, DevCfg_pt->Spi_Prescaler);
        }
        /* values set, update the register */
        SPI_SETVAL32(MUnit_pt->Reg_pt->Spi_FMT[0U], TGReg_u32);

        /* build the TX control field, set buffer mode to 3 */
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
        DlcEv_pt->TxCtrl_u16  = Spi_DlcOptionSelect[MUnit_pt->Prop_pt->Spi_RamUsed].Transmit(HwUnit_u32);
#elif defined(CFG_TMS570LC43X)
        DlcEv_pt->TxCtrl_u16  = Spi_DlcRamTransmit(HwUnit_u32);
#else
#error This SPI driver does not support this MCU.
#endif

        if(DevCfg_pt->Spi_CsMode == (uint8) SPI_CONTINUOUS)
        {
            /* set chip select mode */
            SPI_SETVAL16(DlcEv_pt->TxCtrl_u16, TXRAMCTRL_CSHOLD) ;
        }
        else
        {
            /* enable WDELAY in single mode */
            SPI_SETVAL16(DlcEv_pt->TxCtrl_u16, TXRAMCTRL_WDEL) ;
        }
        /* get the chip select */
        CSVal_u32 = DevCfg_pt->Spi_DioPin;
        /* set Tx control field with the default value of Spi_Def register */
        SPI_SETVAL16(DlcEv_pt->TxCtrl_u16, SPI_DLC_LOWWORD_GET(MUnit_pt->Reg_pt->Spi_DEF)) ;
        /* execute this only if CS handling is selected as active */
        if(CSVal_u32 != (uint32)SPI_NO_CHIP_SELECT)
        {
            /* low byte holds the CS idle level */
            if(SPI_DLC_LOWBYTE_GET(DevCfg_pt->Spi_CsProperty) == SPI_HIGH)
            {
               SPI_CLRVAL32(MUnit_pt->Reg_pt->Spi_DEF, (1U << CSVal_u32));
               /* activate the corresponding CS for transmit __(IDLE)__/--(ACTIVE)-- */
               SPI_SETVAL16(DlcEv_pt->TxCtrl_u16, (1U << CSVal_u32));
            }
            else
            {
                SPI_SETVAL32(MUnit_pt->Reg_pt->Spi_DEF, (1U << CSVal_u32));
                /* activate the corresponding CS for transmit --(IDLE)--\__(ACTIVE)__ */
                SPI_CLRVAL16(DlcEv_pt->TxCtrl_u16, (1U << CSVal_u32));
            }
        }
        else
        {
            /* no action */
        }
        /* save the CS ID */
        DlcEv_pt->DFSel_u8[0U] = (uint8)CSVal_u32;
        /* save the external device */
        DlcEv_pt->DFSel_u8[1U] = ExtDev_u8;

        /* setup timings CS2_CLK[31..24], CLK_2CS[23..16], CS2_ENA[15..8], ENA_2CS[7..0] */
        uint16 delayVal = DevCfg_pt->Spi_ClkDelays.T2cd | (uint16_t)(DevCfg_pt->Spi_ClkDelays.C2td << 8);
        MUnit_pt->Reg_pt->Spi_DELAY[0U] = delayVal;
    }
    else
    {
        /* no action */
    }
}

static FUNC(uint16 , SPI_CODE) Spi_DlcRamTransmit(uint32 HwUnit_u32)
{
    Spi_HWUnitMapPtrType MRamUnit_pt;

    MRamUnit_pt  = &Spi_HWUnitMap_at[HwUnit_u32];

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
    /* set Transfer group as Software Triggered with ONESHOT*/
    if(MRamUnit_pt->Prop_pt->Spi_DmaUsed == STD_OFF)
    {
        /* start transfer every time the TG_ENA is set */
        MRamUnit_pt->Reg_pt->Spi_RegTGCTL.Spi_TGCTRL[0U] = TGCTRL_TRIGSRC(0x0U) | TGCTRL_TRIGEVT(0x7U);
    }
    else
    {
        /* no action */
    }
#elif defined(CFG_TMS570LC43X)
    /* start transfer every time the TG_ENA is set */
    MRamUnit_pt->Reg_pt->Spi_RegTGCTL.Spi_TGCTRL[0U] = TGCTRL_TRIGSRC(0x0U) | TGCTRL_TRIGEVT(0x7U);
#else
#error This SPI driver does not support this MCU.
#endif

    /* enable oneshot */
    SPI_SETVAL32(MRamUnit_pt->Reg_pt->Spi_RegTGCTL.Spi_TGCTRL[0U], TGCTRL_TGONESHOT(1U)) ;

    /* buffer mode 3 */
    return(SPI_DLC_TXCTRL_BUFMOD(3U));
}

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
static FUNC(uint16, SPI_CODE) Spi_DlcStdTransmit(uint32 HwUnit_u32)
{
    /* To remove compiler warning returning (HwUnit_u32 & 0) instead of 0. */
    return(HwUnit_u32 & 0U);
}
#endif /* defined(CFG_TMS570LS12X) */

static FUNC(void, SPI_CODE) Spi_DlcRamInit(uint32 HwUnit_u32)
{
    Spi_RegisterPtrType MRam_pt;

    MRam_pt = Spi_HWUnitMap_at[HwUnit_u32].Reg_pt;
    /* verify that the MIB ram finished auto initialization */
    while(SPI_DLC_CHECK_HEX32(MRam_pt->Spi_FLG, SPI_BUFINIT))
    {
        /* no action */
    }
    /* prepare TG(x) ctrl register */
    /* set PStart to 0, we use the whole MIB RAM as one TG */
    MRam_pt->Spi_RegTGCTL.Spi_TGCTRL[0U] = 0U ;

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
    /* store end address in LTGPEND register bit 14::8 */
    MRam_pt->Spi_RegTGCTL.Spi_LTGPEND = LTGPEND_LPEND(SPI_DLC_MIBTXSIZE-1) ;
    if(Spi_HWUnitMap_at[HwUnit_u32].Prop_pt->Spi_DmaUsed == STD_OFF)
    {
        /* set Irq parameters            */
        /* map the TG[0] transfer end interrupts to the INT1 line */
        /* map the TG[0] transfer error interrupts to the INT0 line */
        MRam_pt->Spi_RegTGCTL.Spi_TGITLVST = TGITLVST_SETINTLEVEL(1U,16U) ;
        /* enable the TG[0] interrupt generation (Value, bit for TG enable Irq) */
        MRam_pt->Spi_RegTGCTL.Spi_TGITENST = TGITENST_SETINTENRDY(1U,16U) | TGITENST_SETINTENRDY(1U,0U);
    }
    else
    {
        /* no dma for MIB */
    }
#elif defined(CFG_TMS570LC43X)
    /* store end address in LTGPEND register bit 14::8 */
    MRam_pt->Spi_RegTGCTL.Spi_TGCTRL[1U] = LTGPEND_LPEND(SPI_DLC_MIBTXSIZE);
    /* store end address in LTGPEND register bit 14::8 */
    MRam_pt->Spi_RegTGCTL.Spi_LTGPEND = LTGPEND_LPEND(SPI_DLC_MIBTXSIZE-1);

    /* set Irq parameters            */
    /* map the TG[0] transfer end interrupts to the INT1 line */
    /* map the TG[0] transfer error interrupts to the INT0 line */
    MRam_pt->Spi_RegTGCTL.Spi_TGITLVST = TGITLVST_SETINTLEVEL(1U,16U) ;
    /* enable the TG[0] interrupt generation (Value, bit for TG enable Irq) */
    MRam_pt->Spi_RegTGCTL.Spi_TGITENST = TGITENST_SETINTENRDY(1U,16U) | TGITENST_SETINTENRDY(1U,0U);
#else
#error This SPI driver does not support this MCU.
#endif
}

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
static FUNC(void, SPI_CODE) Spi_Dlc(Std, Init)(uint32 HwUnit_u32)
{
    Spi_HWUnitMapPtrType MStd_pt;

    MStd_pt = &Spi_HWUnitMap_at[HwUnit_u32];
    /* set Tx Rx int levels to int line 1, error interrupts are mapped to line 0 */
    MStd_pt->Reg_pt->Spi_LVL = 0x00000300U;
    if(MStd_pt->Prop_pt->Spi_DmaUsed == STD_OFF)
    {
        /* enable RxInt, error tracing -> overrun, biterr, desync err, */
        MStd_pt->Reg_pt->Spi_INT0 = 0x00000158U;
    }
    else
    {
        /* only enable error tracing -> overrun, biterr, desync err, */
        MStd_pt->Reg_pt->Spi_INT0 = 0x00000058U;
    }
}

static FUNC(void, SPI_CODE) Spi_Dlc(Std, Close)(uint32 HwUnit_u32)
{
    Spi_HWUnit_at[HwUnit_u32]->Spi_INT0 = (uint32)SPI_DLC_BITCLR;
    Spi_HWUnit_at[HwUnit_u32]->Spi_LVL  = (uint32)SPI_DLC_BITCLR;
}
#endif /* defined(CFG_TMS570LS12X) */

static FUNC(void, SPI_CODE) Spi_DlcRamClose(uint32 HwUnit_u32)
{
    uint32 MibIdx_u32;              /* index in MIBRAM */
    volatile uint16 temp;           /* dummy data for read */
    Spi_RegisterPtrType MReg_pt;

    MReg_pt = Spi_HWUnit_at[HwUnit_u32];
    MReg_pt->Spi_RegTGCTL.Spi_TGCTRL[0U] = (uint32)SPI_DLC_BITCLR;
    MReg_pt->Spi_RegTGCTL.Spi_TICKCNT   = (uint32)SPI_DLC_BITCLR;
    MReg_pt->Spi_RegTGCTL.Spi_LTGPEND   = (uint32)SPI_DLC_BITCLR;
    MReg_pt->Spi_RegTGCTL.Spi_TGITLVST  = (uint32)SPI_DLC_BITCLR;
    MReg_pt->Spi_RegTGCTL.Spi_TGITENCR  = (uint32)SPI_DLC_BITCLR;
    for(MibIdx_u32 = 0U ; MibIdx_u32 < SPI_DLC_MIBRXSIZE ; MibIdx_u32++)
    {
        /* read whole MIBRAM to reset all status flags */
        temp = Spi_RamUnit_at[HwUnit_u32]->Spi_RxBank[MibIdx_u32].RxStat;
        temp = Spi_RamUnit_at[HwUnit_u32]->Spi_RxBank[MibIdx_u32].RxData;
    }
    /* clear MIBSPI enable bit, this must be done at last */
    /* the bit works as switch to enable access to the MIBSPI registers */
    SPI_CLRVAL32(MReg_pt->Spi_EN, MIBSPIE_EN(1U));
}

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
/* SourceId : SPI_SourceId_067 */
/* Requirements : AR_SPI_SR1, AR_SPI_SR172 */
FUNC(void, SPI_CODE)Spi_DlcInit(void)
{
    uint32 CSVal_u32; /* local value for chip select */
    uint32 ExtDevIdx_u32; /* external device index to set the levels as configured */
    P2VAR(Spi_DlcEventType, AUTOMATIC, SPI_VAR) DlcEv_pt;
    P2CONST(Spi_HWUnitPropertyType, AUTOMATIC, SPI_VAR) PropLoc_pt; /* pointer to unit properties */
    Spi_RegisterPtrType MReg_pt;
    uint8 UnitIdx_u8; /* hardware unit index of generated unit arrays */
    uint8 HWUnit_u8; /* local value for hardware unit */

    Spi_DlcOptionSelect[SPI_DLC_STDOPT].Init      = Spi_Dlc(Std,Init);
    Spi_DlcOptionSelect[SPI_DLC_STDOPT].Close     = Spi_Dlc(Std,Close);
    Spi_DlcOptionSelect[SPI_DLC_STDOPT].FillData  = Spi_Dlc(Std,FillData);
    Spi_DlcOptionSelect[SPI_DLC_STDOPT].DrainData = Spi_Dlc(Std,DrainData);
    Spi_DlcOptionSelect[SPI_DLC_STDOPT].Trigger   = Spi_Dlc(Std,TriggerData);
    Spi_DlcOptionSelect[SPI_DLC_STDOPT].Transmit  = Spi_Dlc(Std,Transmit);

    Spi_DlcOptionSelect[SPI_DLC_RAMOPT].Init      = Spi_Dlc(Ram,Init);
    Spi_DlcOptionSelect[SPI_DLC_RAMOPT].Close     = Spi_Dlc(Ram,Close);
    Spi_DlcOptionSelect[SPI_DLC_RAMOPT].FillData  = Spi_Dlc(Ram,FillData);
    Spi_DlcOptionSelect[SPI_DLC_RAMOPT].DrainData = Spi_Dlc(Ram,DrainData);
    Spi_DlcOptionSelect[SPI_DLC_RAMOPT].Trigger   = Spi_Dlc(Ram,TriggerData);
    Spi_DlcOptionSelect[SPI_DLC_RAMOPT].Transmit  = Spi_Dlc(Ram,Transmit);

    /*
     * set HW unit parameters
     */
    for(UnitIdx_u8 = 0U ; UnitIdx_u8 < Spi_ConfigPtr_pt->Spi_MaxDlcs ; UnitIdx_u8++)
    {
        if(Spi_UnitProperty_at[UnitIdx_u8].Spi_DmaUsed == STD_ON)
        {
            /* if any unit utilizes Dma, it must be initialized */
            Dma_Init();
            break;
        }
    }
    for(UnitIdx_u8 = 0U ; UnitIdx_u8 < Spi_ConfigPtr_pt->Spi_MaxDlcs ; UnitIdx_u8++)
    {
       if(NULL_PTR != Spi_HWUnit_at[UnitIdx_u8])
       {
          PropLoc_pt = &Spi_UnitProperty_at[UnitIdx_u8];
          HWUnit_u8  = PropLoc_pt->Spi_UnitID;
          Spi_HWUnitMap_at[HWUnit_u8].Reg_pt  = Spi_HWUnit_at[UnitIdx_u8];
          Spi_HWUnitMap_at[HWUnit_u8].Ram_pt  = Spi_RamUnit_at[UnitIdx_u8];
          Spi_HWUnitMap_at[HWUnit_u8].Prop_pt = PropLoc_pt;

          DlcEv_pt = &Spi_DlcEvent_t[HWUnit_u8];
          DlcEv_pt->Event_u8 = SPI_DLC_EV_CONSUMED ;
          DlcEv_pt->Guard_u8 = SPI_DLC_G_IDLE ;

          MReg_pt = Spi_HWUnitMap_at[HWUnit_u8].Reg_pt;
          /* Bring SPI out of RESET state */
          MReg_pt->Spi_GCR0 = 1U;

          /* added below so that BUF init is initiated much earlier */
          /* set all pins on the unit to functional */
            MReg_pt->Spi_PC.Spi_FUN = 0xFFFF;
            MReg_pt->Spi_INT0 |= (1 << 9); /* enable TX interrupt */
            MReg_pt->Spi_INT0 |= (1 << 8); /* enable RX interrupt */
            MReg_pt->Spi_INT0 |= 0xFF;
            MReg_pt->Spi_LVL |= (1 << 9);
            MReg_pt->Spi_LVL |= (1 << 8);
          if((PropLoc_pt->Spi_RamUsed == STD_ON) && (PropLoc_pt->Spi_DmaUsed == STD_OFF))
          {
             /* enable MIB spi to get access to the MIB registers */
             SPI_SETVAL32(MReg_pt->Spi_EN, MIBSPIE_EN(1U));
          }
          for (ExtDevIdx_u32 = 0U; ExtDevIdx_u32 < Spi_ConfigPtr_pt->Spi_MaxExtDevs ; ExtDevIdx_u32++)
          {
             if(UnitIdx_u8 == Spi_ConfigPtr_pt->Spi_DevCfg[ExtDevIdx_u32].Spi_HwInstance)
             {
                /* get the chip select */
                CSVal_u32 = Spi_ConfigPtr_pt->Spi_DevCfg[ExtDevIdx_u32].Spi_DioPin;
                /* execute this only if CS handling is selected as active */
                if(CSVal_u32 != SPI_NO_CHIP_SELECT)
                {
                   if(SPI_DLC_LOWBYTE_GET(Spi_ConfigPtr_pt->Spi_DevCfg[ExtDevIdx_u32].Spi_CsProperty) == SPI_HIGH)
                   {
                      /* set the CS idle levels - idle low */
                      SPI_CLRVAL32(MReg_pt->Spi_DEF, 1U << CSVal_u32) ;
                   }
                   else
                   {
                      /* set the CS idle levels - idle high */
                      SPI_SETVAL32(MReg_pt->Spi_DEF, 1U << CSVal_u32) ;
                   }
                }
                else
                {
                    /* disable CS functionality completely */
                    MReg_pt->Spi_PC.Spi_FUN &= ~(0xFF);
                    /* set the CS pins to outputs */
                    MReg_pt->Spi_PC.Spi_DIR  |= 0xFF;
                    /* drive them low or high depending on the BSW configuration */
                    if (Spi_ConfigPtr_pt->Spi_DevCfg[ExtDevIdx_u32].Spi_CsProperty == SPI_HIGH) {
                        MReg_pt->Spi_PC.Spi_DSET |= 0xFF;
                    } else {
                        MReg_pt->Spi_PC.Spi_DCLR |= 0xFF;
                    }
                }
             }
          }

          /* set master, external clk, enable SPI  */
          MReg_pt->Spi_GCR1 = MIBSPIEGCR1_MASTER(1U) |
                              MIBSPIEGCR1_CLKMOD(1U) |
                              MIBSPIEGCR1_SPIEN(1U);
          /* if hardware unit has no RAM so it runs in standard mode, the MIB features will not be initialized */
          Spi_DlcOptionSelect[PropLoc_pt->Spi_RamUsed].Init(HWUnit_u8);
       }
    }
}
#elif defined(CFG_TMS570LC43X)
FUNC(void, SPI_CODE)Spi_DlcInit(void)
{
    uint32 CSVal_u32; /* local value for chip select */
    uint32 ExtDevIdx_u32; /* external device index to set the levels as configured */
    P2VAR(Spi_DlcEventType, AUTOMATIC, SPI_VAR) DlcEv_pt;
    P2CONST(Spi_HWUnitPropertyType, AUTOMATIC, SPI_VAR) PropLoc_pt; /* pointer to unit properties */
    Spi_RegisterPtrType MReg_pt;
    uint8 UnitIdx_u8; /* hardware unit index of generated unit arrays */
    uint8 HWUnit_u8; /* local value for hardware unit */

    for(UnitIdx_u8 = 0U ; UnitIdx_u8 < Spi_ConfigPtr_pt->Spi_MaxDlcs ; UnitIdx_u8++)
    {
       if(NULL_PTR != Spi_HWUnit_at[UnitIdx_u8])
       {
          PropLoc_pt = &Spi_UnitProperty_at[UnitIdx_u8];
          HWUnit_u8  = PropLoc_pt->Spi_UnitID;
          Spi_HWUnitMap_at[HWUnit_u8].Reg_pt  = Spi_HWUnit_at[UnitIdx_u8];
          Spi_HWUnitMap_at[HWUnit_u8].Ram_pt  = Spi_RamUnit_at[UnitIdx_u8];
          Spi_HWUnitMap_at[HWUnit_u8].Prop_pt = PropLoc_pt;

          DlcEv_pt = &Spi_DlcEvent_t[HWUnit_u8];
          DlcEv_pt->Event_u8 = SPI_DLC_EV_CONSUMED ;
          DlcEv_pt->Guard_u8 = SPI_DLC_G_IDLE ;

          MReg_pt = Spi_HWUnitMap_at[HWUnit_u8].Reg_pt;
          /* Bring SPI out of RESET state */
          MReg_pt->Spi_GCR0 = 1U;
          /* set master, external clk, enable SPI  */
          MReg_pt->Spi_GCR1 = MIBSPIEGCR1_MASTER(1U) |
                              MIBSPIEGCR1_CLKMOD(1U) |
                              MIBSPIEGCR1_SPIEN(1U);
          /* added below so that BUF init is initiated much earlier */
          /* enable MIB spi to get access to the MIB registers */
          SPI_SETVAL32(MReg_pt->Spi_EN, MIBSPIE_EN(1U));

          /* set all pins on the unit to functional */
          MReg_pt->Spi_PC.Spi_FUN = 0xFFFF;

          for (ExtDevIdx_u32 = 0U; ExtDevIdx_u32 < Spi_ConfigPtr_pt->Spi_MaxExtDevs ; ExtDevIdx_u32++)
          {
             if(UnitIdx_u8 == Spi_ConfigPtr_pt->Spi_DevCfg[ExtDevIdx_u32].Spi_HwInstance)
             {
                /* get the chip select */
                CSVal_u32 = Spi_ConfigPtr_pt->Spi_DevCfg[ExtDevIdx_u32].Spi_DioPin;
                /* execute this only if CS handling is selected as active */
                if(CSVal_u32 != SPI_NO_CHIP_SELECT)
                {
                   if(SPI_DLC_LOWBYTE_GET(Spi_ConfigPtr_pt->Spi_DevCfg[ExtDevIdx_u32].Spi_CsProperty) == SPI_HIGH)
                   {
                      /* set the CS idle levels - idle low */
                      SPI_CLRVAL32(MReg_pt->Spi_DEF, 1U << CSVal_u32) ;
                   }
                   else
                   {
                      /* set the CS idle levels - idle high */
                      SPI_SETVAL32(MReg_pt->Spi_DEF, 1U << CSVal_u32) ;
                   }
                }
                else
                {
                   /* no action */
                }
             }
          }
          /* if hardware unit has no RAM so it runs in standard mode, the MIB features will not be initialized */
          Spi_DlcRamInit(HWUnit_u8);
       }
    }
}
#endif

FUNC(void, SPI_CODE) Spi_DlcClose(void)
{
    uint32 HwUnit_u32;		/* hardware unit index */
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
    uint32 OptSel_u32;		/* option selector (Std or Ram) */
#endif /* defined(CFG_TMS570LS12X) */
    Spi_RegisterPtrType MReg_pt;

    /* clear registers               */
    for(HwUnit_u32 = 0U ; HwUnit_u32 < Spi_ConfigPtr_pt->Spi_MaxDlcs ; HwUnit_u32++)
    {
       if(NULL_PTR != Spi_HWUnit_at[HwUnit_u32])
       {
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
          MReg_pt = Spi_HWUnit_at[HwUnit_u32];
          /* power on default is 1 for each CS line */
          MReg_pt->Spi_DEF    = (uint32) 0x0Fu;
          MReg_pt->Spi_FMT[0U] = (uint32)SPI_DLC_BITCLR ;
          MReg_pt->Spi_GCR1   = (uint32)SPI_DLC_BITCLR;

          OptSel_u32 = Spi_UnitProperty_at[HwUnit_u32].Spi_RamUsed;
          Spi_DlcOptionSelect[OptSel_u32].Close(HwUnit_u32);
#elif defined(CFG_TMS570LC43X)
          MReg_pt = Spi_HWUnit_at[HwUnit_u32];
          Spi_DlcRamClose(HwUnit_u32);
          /* power on default is 1 for each CS line */
          MReg_pt->Spi_DEF    = (uint32) 0x0FU;
          MReg_pt->Spi_FMT[0U] = (uint32)SPI_DLC_BITCLR ;
          MReg_pt->Spi_GCR1   = (uint32)SPI_DLC_BITCLR;
#else
#error This SPI driver does not support this MCU.
#endif
       }
    }
}

FUNC(Std_ReturnType, SPI_CODE) Spi_DlcSetEvent(const Spi_DlcEventType* Dlc_Event_pt)
{
    Std_ReturnType dlc_set_event_return = E_NOT_OK;
    uint32 HwUnit_u32; /* index of hardware unit */
    Spi_DlcEventPtrType DlcEv_pt;

    HwUnit_u32  = Spi_ConfigPtr_pt->Spi_JobCfg[Dlc_Event_pt->JobID_u8].Spi_HWUnitID;
    Spi_GlobalSuspend();
    DlcEv_pt  = &Spi_DlcEvent_t[HwUnit_u32];
    /* check if a job starts transmission */
    /* check if a job is waiting for transmit, do not queue him again */
    if(DlcEv_pt->Event_u8 != (uint8)SPI_DLC_EV_CONSUMED)
    {
        /* stop critical section */
        Spi_GlobalRestore();
    }
    else
    {
        /* used for transmission mode */
        DlcEv_pt->Event_u8 = Dlc_Event_pt->Event_u8;
        /* high prio jobs are queued at pos 0, low prio jobs at pos. 3*/
        DlcEv_pt->JobID_u8 = Dlc_Event_pt->JobID_u8;
        DlcEv_pt->Guard_u8 = (uint8)SPI_DLC_G_PENDING ;
        /* stop critical section */
        Spi_GlobalRestore();
        Spi_DlcConsumeEvent(HwUnit_u32);
        /* Set return value */
        dlc_set_event_return = E_OK;
    }

    return (dlc_set_event_return);
}

FUNC(void, SPI_CODE) Spi_IrqTxRxERR(uint32 HwUnit_u32)
{
    uint32 TGErr_u32; /* value for error check */
    P2VAR(Spi_DlcEventType, AUTOMATIC, SPI_VAR) DlcEv_pt;

    DlcEv_pt = &Spi_DlcEvent_t[HwUnit_u32];
    /* check if a error is pending, get value */
    TGErr_u32 = SPI_GETVAL32(Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_TGINTVECT[0U], TGINTVECT_INTVEC(0x1FU));
    /* reset value, used in DlcError function */
    DlcEv_pt->RxStat_u16 = 0U;
    /* bit five in the value signals a pending error */
    if(SPI_DLC_CHECK_BIT32(TGErr_u32, 6U))
    {
        /* we caught an error, handle it */
        Spi_DlcError(HwUnit_u32);
    }
}

FUNC(void, SPI_CODE) Spi_IrqTxRx(uint32 HwUnit_u32)
{
    volatile uint16 TGIdx_u16; /* index of transfergroup*/
    Spi_DlcEventPtrType DlcEv_pt;
    Spi_RegisterPtrType MStd_pt;
    Spi_HWUnitMapPtrType MUnit_pt;
    uint8  Ram_u8 ;   /* temporary parameter for RamUsed ON/OFF */

    MUnit_pt = &Spi_HWUnitMap_at[HwUnit_u32];
    /* check the TG which caused the IRQ    */
    /* and clear the interrupt flag by read */
    Ram_u8 = MUnit_pt->Prop_pt->Spi_RamUsed;
    if(Ram_u8 == STD_ON)
    {
        TGIdx_u16 = (uint16)(SPI_GETVAL32(Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_TGINTVECT[1U], TGINTVECT_INTVEC(0x1FU)) >> 1U) - 1U;
        /* TG(ENA) is cleared by one shot option, so the timer does not trigger this TG again */
    }
    else
    {
        TGIdx_u16 = (uint16)(SPI_GETVAL32(Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_FLG , 0x3FFU));
        /* just read the flag */
        TGIdx_u16 = 0U;
    }
    DlcEv_pt = &Spi_DlcEvent_t[HwUnit_u32];
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
    Spi_DlcOptionSelect[Ram_u8].DrainData(HwUnit_u32);
#elif defined(CFG_TMS570LC43X)
    Spi_DlcRamDrainData(HwUnit_u32);
#else
#error This SPI driver does not support this MCU.
#endif

    /* check state if  finished or idle */
    if(DlcEv_pt->Guard_u8 == SPI_DLC_G_IDLE)
    {
        /* close DLC, report the job which has finished */
        MStd_pt  = Spi_HWUnitMap_at[HwUnit_u32].Reg_pt;
        Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_DlcResult[HwUnit_u32] = SPI_DLC_OK ;
        DlcEv_pt->Event_u8 = SPI_DLC_EV_CONSUMED;
        SPI_CLRVAL16(MStd_pt->Spi_DAT1.TxCtrl, TXRAMCTRL_CSHOLD);
        /* report to job and sequence handler that a job has finished */
        Spi_HwJobComplete(DlcEv_pt->JobID_u8, HwUnit_u32);
    }
    else
    {
        /* refill data and
         * trigger transfer  again
         */
        /* transfer group is ready for transfer, trigger interrupt generation */
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
        Spi_DlcOptionSelect[Ram_u8].FillData(HwUnit_u32);
        Spi_DlcOptionSelect[Ram_u8].Trigger(HwUnit_u32);
#elif defined(CFG_TMS570LC43X)
        Spi_DlcRamFillData(HwUnit_u32);
        Spi_DlcRamTriggerData(HwUnit_u32);
#else
#error This SPI driver does not support this MCU.
#endif
    }
}

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
FUNC(void, SPI_CODE) Spi_DlcBlockCbk(void)
{
    Spi_DlcEventPtrType DlcEv_pt;
    Spi_RegisterPtrType MStd_pt;

    /* Temporary ID of a hardware channel,
    * initialized with the ID of the hardware channel which caused this interrupt
    * Note: Reading BTCAOFFSET clears the respective BTCFLAG */
    uint8 HWChannel = (uint8)Dma_GlobalRegister->DMA_BTCAOFFSET - 1U;

    /* Check for valid DMA Channel to service */
    if(HWChannel < DMA_MAX_HW_CHN)
    {
        DlcEv_pt = &Spi_DlcEvent_t[Dma_ChanneltoHWunit[HWChannel]];
        MStd_pt  = Spi_HWUnitMap_at[Dma_ChanneltoHWunit[HWChannel]].Reg_pt;

        /* disable Dma requests */
        MStd_pt->Spi_INT0 &= ~(0x00010000U);
        /* check if job has completed */
        if(DlcEv_pt->Guard_u8 == SPI_DLC_G_IDLE)
        {
            /* close DLC, report the job which has finished */
            Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_DlcResult[(uint32)Dma_ChanneltoHWunit[HWChannel]] = SPI_DLC_OK ;
            DlcEv_pt->Event_u8 = SPI_DLC_EV_CONSUMED;
            /* Clear current CS */
            SPI_CLRVAL16(MStd_pt->Spi_DAT1.TxCtrl, TXRAMCTRL_CSHOLD);
            /* report to job and sequence handler that a job has finished */
            Spi_HwJobComplete(DlcEv_pt->JobID_u8, (uint32)Dma_ChanneltoHWunit[HWChannel]);
        }
        else
        {
            (FUNC(void, SPI_CODE)) Spi_DlcSwitchChannel((uint32)Dma_ChanneltoHWunit[HWChannel],
                                                        &DlcEv_pt->TxCtrl_u16,
                                                        DlcEv_pt,
                                                        SPI_DLC_TX);
            /* setup next channel Dma and enable Dma requests again */
            Spi_DlcStdPrepareDma((uint32)Dma_ChanneltoHWunit[HWChannel], SPI_DLC_TX);
            /* enable Dma requests to generate the first pulse */
            MStd_pt->Spi_INT0 |= 0x00010000U;
        }
    }
}
#endif /* defined(CFG_TMS570LS12X) */

FUNC(void, SPI_CODE) Spi_DlcEnableLpbk(uint8 HwUnit, uint8 LbMode)
{
   if(SPI_ANALOG_LPBK == LbMode)
   {
      SPI_SETVAL32(Spi_HWUnit_at[HwUnit]->Spi_IOLPBTSTCR, SPI_ANALOG_LOOPBACK_MASK);
   }
   else
   {
      SPI_CLRVAL32(Spi_HWUnit_at[HwUnit]->Spi_IOLPBTSTCR, SPI_ANALOG_LOOPBACK_MASK);
      SPI_SETVAL32(Spi_HWUnit_at[HwUnit]->Spi_IOLPBTSTCR, SPI_DIGITAL_LOOPBACK_MASK);
   }
}

FUNC(void, SPI_CODE) Spi_DlcDisableLpbk(uint8 HwUnit)
{
   SPI_CLRVAL32(Spi_HWUnit_at[HwUnit]->Spi_IOLPBTSTCR, SPI_ANALOG_LOOPBACK_MASK);
}

FUNC(uint32, SPI_CODE) Spi_DlcRegisterRdbk(Spi_DlcRegRdbkType DlcRegRdbck,uint8 HwUnit)
{
   uint32 Register_Readback_Return = 0;

   switch(DlcRegRdbck)
   {
      case  SPI_GCR0_RB:
         Register_Readback_Return = Spi_HWUnit_at[HwUnit]->Spi_GCR0;
         break;
      case  SPI_GCR1_RB:
         Register_Readback_Return = Spi_HWUnit_at[HwUnit]->Spi_GCR1;
         break;
      case  SPI_DEF_RB:
         Register_Readback_Return = Spi_HWUnit_at[HwUnit]->Spi_DEF;
         break;
      case  SPI_EN_RB:
         Register_Readback_Return = Spi_HWUnit_at[HwUnit]->Spi_EN;
         break;
      default:
      break ;
  }
   return(Register_Readback_Return);
}

#define SPI_STOP_SEC_CODE
#include "MemMap.h"
