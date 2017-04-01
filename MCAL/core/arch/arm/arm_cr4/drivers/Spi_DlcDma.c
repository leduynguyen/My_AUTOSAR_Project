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

#define SPI_DLCDMA_SOURCE 1

#include "Std_Types.h"
#include "Spi_DlcDma.h"
#include "Spi_Dlc.h"


/* the Spi uses max five Channel_u16s for Tx/Rx with 10 requests */

#define DMA_HW_Channel_u16_NUMBER    (16U)

#define SPI_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

static Dma_StatusType Dma_ModuleInitFlag = DMA_UNINIT;
/* DMa support for max 5 HWUnits */

Dma_GlobalRegisterPtrType Dma_GlobalRegister = DMA_GLOBAL_REGISTER_BASE_ADDRESS;

#define SPI_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#define SPI_START_SEC_CODE
#include "MemMap.h"


FUNC(void, SPI_CODE) Dma_Init( void )
{
    uint32 *volatile ReqMaskSet1 = VIM_REQMASKSET1;   /* Temporary pointer to interrupt request mask set register */
    uint32 *volatile ReqMaskClr1 = VIM_REQMASKCLR1;   /* Temporary pointer to interrupt request mask clear register */
    /* dma has already been initilized */
    if(Dma_ModuleInitFlag == DMA_IDLE)
    {
        return;
    }
    /* ====== Initialization 1 of Global Control Register ====== */
    /* Cause a self reset of the DMA hardware module to reach a defined state of all global registers of DMA module,
    * switch the debug mode off and set DMA to disabled */
    Dma_GlobalRegister->DMA_GCTRL = 0x00000001U;
    /* Reset the reset bit of the DMA hardware module
    * switch the debug mode to "finish current frame transfer" and set DMA to disabled */
    Dma_GlobalRegister->DMA_GCTRL = 0x00000200U;

    /* ====== Initialization of HW Channel_u16 Enable Register ====== */
    /* No initialization needed, all Channel_u16s are disabled after reset. */
    /* Initialization not needed but done because there is no statement in manual about reset state of this register */
    Dma_GlobalRegister->DMA_HWCHENAR = 0xFFFFFFFFU;

    /* ====== Initialization of SW Channel_u16 Enable Register ====== */
    /* No initialization needed, all Channel_u16s are disabled after reset. */
    /* Initialization not needed but done because there is no statement in manual about reset state of this register */
    Dma_GlobalRegister->DMA_SWCHENAR = 0xFFFFFFFFU;

    /* ====== Initialization of Interrupt Enable Register ====== */
    /* Enable all Dma interrupts globally, but disable all Dma interrupts themselves */

    /* Initialization not needed but done because there is no statement in manual about reset state of this register */
    Dma_GlobalRegister->DMA_FTCINTENAR = 0xFFFFFFFFU;  /* disable frame transfer complete interrupt */
    /* Initialization not needed but done because there is no statement in manual about reset state of this register */
    Dma_GlobalRegister->DMA_LFSINTENAR = 0xFFFFFFFFU;  /* disable last frame started interrupt */
    /* Initialization not needed but done because there is no statement in manual about reset state of this register */
    Dma_GlobalRegister->DMA_HBCINTENAR = 0xFFFFFFFFU;  /* disable half block complete interrupt */
    /* Initialization not needed but done because there is no statement in manual about reset state of this register */
    Dma_GlobalRegister->DMA_BTCINTENAR = 0xFFFFFFFFU;  /* disable block transfer complete interrupt */

    /* DMA FTCA interrupt uses interrupt request line #33, enabled by REQMASKSET0 [33] = REQMASKSET1 [1]
    *                                                    disabled by REQMASKCLR0 [33] = REQMASKSET1 [1]
    * DMA LFSA interrupt uses interrupt request line #34, enabled by REQMASKSET0 [34] = REQMASKSET1 [2]
    *                                                    disabled by REQMASKCLR0 [34] = REQMASKSET1 [2]
    * DMA HBCA interrupt uses interrupt request line #39, enabled by REQMASKSET0 [39] = REQMASKSET1 [7]
    *                                                    disabled by REQMASKCLR0 [39] = REQMASKSET1 [7]
    * DMA BTCA interrupt uses interrupt request line #40, enabled by REQMASKSET0 [40] = REQMASKSET1 [8]
    *                                                    disabled by REQMASKCLR0 [40] = REQMASKSET1 [8]*/
    *ReqMaskSet1 |= (DMA_BIT(1U) | DMA_BIT(8U));   /* enable needed Dma interrupts by setting the RequestMask */
    
    Dma_GlobalRegister->DMA_GCHIENAS = ((uint32) 0xFFFFFFFFU);    /* enable all Dma interrupts globally */

    /* ====== Initialization of Port Assignment Registers ====== */
    /* Set Port assignment of all Channel_u16s to Port B only. Port A seems to be not implemented in TMS570PSFC66 */
    Dma_GlobalRegister->DMA_PAR[0U] = 0x77777777U;
    #if DMA_HW_Channel_u16_NUMBER > 8U
    Dma_GlobalRegister->DMA_PAR[1U] = 0x77777777U;    /* only needed if more than 8 hardware Channel_u16s are available */
    #endif
    #if DMA_HW_Channel_u16_NUMBER > 16U
    Dma_GlobalRegister->DMA_PAR[2U] = 0x77777777U;    /* only needed if more than 16 hardware Channel_u16s are available */
    #endif
    #if DMA_HW_Channel_u16_NUMBER > 24U
    Dma_GlobalRegister->DMA_PAR[3U] = 0x77777777U;    /* only needed if more than 24 hardware Channel_u16s are available */
    #endif

    /* ====== Initialization of Channel_u16 Priority Register ====== */
    /* No initialization needed, all Channel_u16s are set to low priority after reset. */
    /* ====== Initialization of Interrupt Mapping Registers ====== */
    /* No initialization needed, all requests are routed to ARM core after reset. */
    /* ====== Initialization of Fall Back Register ====== */
    /* Currently unknown if initialization is needed. */
    /* ====== Initialization of Port Control Register ====== */
    /* Currently unknown if initialization is needed. */
    /* Note: Definition of priority scheme (fixed priority/round robin) can be made in this register. */
    /* Note: DMA module of TMS570 uses a FIFO buffer.
    * Bypassing of FIFO can be switched on in this register. */
    /* ====== Initialization of RAM Test Control Register ====== */
    /* Currently unknown if initialization is needed. */
    /* ====== Initialization of Debug Control Register ====== */
    /* Currently unknown if initialization is needed. */
    /* ====== Initialization of Watch Point Register ====== */
    /* Currently unknown if initialization is needed. */
    /* ====== Initialization of Watch Mask Register ====== */
    /* Currently unknown if initialization is needed. */
    /* ====== Initialization of Parity Control Register ====== */
    /* Currently unknown if initialization is needed. */
    /* ====== Initialization of Memory Protection Control Register ====== */
    /* Currently unknown if initialization is needed. */
    /* ====== Initialization of Memory Protection Region Registers ====== */
    /* Currently unknown if initialization is needed. */
    Dma_GlobalRegister->DMA_DMAPCR = 0x5U;
    /* ====== Initialization 2 of Global Control Register ====== */
    /* Set DMA to enabled */
    Dma_GlobalRegister->DMA_GCTRL    |= 0x00010000U;

    /* Set initialization flag to not uninit */
    Dma_ModuleInitFlag = DMA_IDLE;

    return;
} /* End of Dma_Init() */

FUNC(void, SPI_CODE) Dma_DeInit( void )
{
    /* ====== disable and reset hardware ====== */
    /* Cause a self reset of the DMA hardware module to reach a defined state of all global registers of DMA module,
     * switch the debug mode off and set DMA to disabled */
    Dma_GlobalRegister->DMA_GCTRL = (uint32)0x00000001U;
    /* Reset the reset bit of the DMA hardware module */
    Dma_GlobalRegister->DMA_GCTRL = (uint32)0x00000000U;
    /* ====== set initialization flag to uninit ====== */
    Dma_ModuleInitFlag = DMA_UNINIT;

} /* End of Dma_DeInit() */

FUNC(void, SPI_CODE) Dma_Setup
(
    const Dma_ChannelSetupType* Setup
)
{
    CONST(Dma_RequestType, SPI_VAR) Dma_MapReqLine[5U] =
    {
        {SPI_DLC_RXUNIT0, SPI_DLC_TXUNIT0},
        {SPI_DLC_RXUNIT1, SPI_DLC_TXUNIT1},
        {SPI_DLC_RXUNIT2, SPI_DLC_TXUNIT2},
        {SPI_DLC_RXUNIT3, SPI_DLC_TXUNIT3},
        {SPI_DLC_RXUNIT4, SPI_DLC_TXUNIT4}
    };

    uint16 Channel_u16;
    uint16 Unit_u16;

    Channel_u16 = Setup->Channel;
    Unit_u16    = Setup->Unit;

    DMA_PRIMARY_CONTROL_PACKET_BASE_ADDRESS->DMA_CHCTRL[Channel_u16].ISADDR   = Setup->SrcAddr;
    DMA_PRIMARY_CONTROL_PACKET_BASE_ADDRESS->DMA_CHCTRL[Channel_u16].IDADDR   = Setup->DstAddr;
    DMA_PRIMARY_CONTROL_PACKET_BASE_ADDRESS->DMA_CHCTRL[Channel_u16].IFTCOUNT = Setup->FCount;
    DMA_PRIMARY_CONTROL_PACKET_BASE_ADDRESS->DMA_CHCTRL[Channel_u16].IETCOUNT = Setup->ECount;
    DMA_PRIMARY_CONTROL_PACKET_BASE_ADDRESS->DMA_CHCTRL[Channel_u16].CHCTRL   = Setup->ChCtrl;

    /* configure the Channel_u16s for Dma transmission channels [0 = Tx, 1= Rx]
     * they will be connected later to the Spi Channel_u16 in DMAxCTRL
     */
    if(Setup->Direction == DMA_TX)
    {
       DMA_PRIMARY_CONTROL_PACKET_BASE_ADDRESS->DMA_CHCTRL[Channel_u16].CHCTRL_CHAIN = 0U;
       /* DMA_REQ_SPIx for C66 TxData */
       Dma_GlobalRegister->DMA_DREQASI[Channel_u16] = Dma_MapReqLine[Unit_u16].DmaReq[1U];
       /* enable channel for hardware requests */
       Dma_GlobalRegister->DMA_HWCHENAS = ((uint32)1U << Channel_u16);
    }
    else
    {
       DMA_PRIMARY_CONTROL_PACKET_BASE_ADDRESS->DMA_CHCTRL[Channel_u16].CHCTRL_CHAIN = 0U;
       /* DMA_REQ_SPIx for C66 RxData */
       Dma_GlobalRegister->DMA_DREQASI[Channel_u16] = Dma_MapReqLine[Unit_u16].DmaReq[0U];
       /* enable FTC interrupts only on channel 1 (Rx ready) */
       Dma_GlobalRegister->DMA_BTCINTENAS = ((uint32)1U << Channel_u16);
       /* enable channel for hardware requests */
       Dma_GlobalRegister->DMA_HWCHENAS = ((uint32)1U << Channel_u16);
    }

    DMA_PRIMARY_CONTROL_PACKET_BASE_ADDRESS->DMA_CHCTRL[Channel_u16].EIDXS    = Setup->EISrcInc;
    DMA_PRIMARY_CONTROL_PACKET_BASE_ADDRESS->DMA_CHCTRL[Channel_u16].EIDXD    = Setup->EIDstInc;
    DMA_PRIMARY_CONTROL_PACKET_BASE_ADDRESS->DMA_CHCTRL[Channel_u16].FIDXS    = Setup->FISrcInc;
    DMA_PRIMARY_CONTROL_PACKET_BASE_ADDRESS->DMA_CHCTRL[Channel_u16].FIDXD    = Setup->FIDstInc;
}

FUNC(Dma_ChannelType, SPI_CODE) Dma_GetFree_Channel(void)
{
    Dma_ChannelType  Dma_ChId ; /* DMA channel identifier */
    uint32 Dma_Hwchenas;

    for(Dma_ChId=0U; Dma_ChId < 32U; Dma_ChId++)
    {
        Dma_Hwchenas = Dma_GlobalRegister->DMA_HWCHENAS;
        if((Dma_Hwchenas & (0x00000001U << Dma_ChId)) == 0U)
        {
            break;
        }
    }
    return(Dma_ChId);
}

#define SPI_STOP_SEC_CODE
#include "MemMap.h"
