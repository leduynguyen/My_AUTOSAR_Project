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

/* ----------------------------[includes]------------------------------------*/

#include "Platform_Types.h"
#include "assert.h"
#include "Spi_Internal.h"
/*lint -save -e451 Header file repeatedly included but does not have a standard include guard. OK, there is one. */
#include "Spi_Cfg.h"
/*lint -restore -e451 */
#include "isr.h"
#include "Arc_Types.h"
#include "Spi_jacinto.h"
#include "Mcu.h"

/* ----------------------------[private define]------------------------------*/

#define FIFO_FFNBYTE 	64
#define FIFO_DEPTH		32

#if !defined(SPI_ISR_PRIORITY)
#define SPI_ISR_PRIORITY			4u
#endif

/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/


/* @req SWS_Spi_00263 */
/* !req SWS_Spi_00370 */
/* @req SWS_Spi_00056 */
/* @req SWS_Spi_00076 */
/* !req SWS_Spi_00148 */

/* @req SWS_Spi_00128 */

typedef struct SPI_reg {
    volatile uint32 MCSPI_HL_REV;			/* Offset: 0x0uL   - McSPI IP revision register */
    volatile uint32 MCSPI_HL_HWINFO;		/* Offset: 0x4uL   - McSPI IP hardware information register */
    uint8 _pad00[(0x10-0x4)-0x4];
    volatile uint32 MCSPI_HL_SYSCONFIG;		/* Offset: 0x10uL  - McSPI IP system configuration register  */
    uint8 _pad01[(0x100-0x10)-0x4];
    volatile uint32 MCSPI_REVISION;			/* Offset: 0x100uL - McSPI revision register  */
    uint8 _pad02[(0x110-0x100)-0x4];
    volatile uint32 MCSPI_SYSCONFIG;		/* Offset: 0x110uL - McSPI system configuration register  */
    volatile uint32 MCSPI_SYSSTATUS;       /* Offset: 0x114uL - McSPI system status register  */
    SPI_IRQSTATUS_t MCSPI_IRQSTATUS;       /* Offset: 0x118uL - McSPI interrupt status register  */
    volatile uint32 MCSPI_IRQENABLE;		/* Offset: 0x11CuL - McSPI interrupt enable register  */
    volatile uint32 MCSPI_WAKEUPENABLE;    /* Offset: 0x120uL - McSPI wakeup enable register  */
    volatile uint32 MCSPI_SYST;            /* Offset: 0x124uL - McSPI system test register  */
    SPI_MODULCTRL_t MCSPI_MODULCTRL;       /* Offset: 0x128uL - McSPI module control register  */
    MCSPI_CHn_Type	MCSPI_CHn[4];
    SPI_XFERLEVEL_t MCSPI_XFERLEVEL;		/* McSPI transfer levels register */
    volatile uint32 MCSPI_DAFTX;			/* DMA address aligned FIFO transmitter register */
    volatile uint32 MCSPI_DAFRX;
} SPI_RegType;

struct privData {
    /* Number bytes copied to the TX FIFO for a specific channel */
    uint32 chTxBytesCopied;

    /* Number of bytes copied from the FIFO */
    uint32 chRxBytesCopied;

    /* Total length of a job in bytes */
    uint16 jobLengthInBytes;
    /* Number of total bytes copied from a job */
    uint32 jobTxBytesCopied;
    /* Number of bytes copied in to the FIFO */
    uint32 fifoCopyCnt;
} ;

/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

SPI_RegType *Spi_HwRegs[4] = {
        (SPI_RegType *)MCSPI1_BASE_ADDR,
        (SPI_RegType *)MCSPI2_BASE_ADDR,
        (SPI_RegType *)MCSPI3_BASE_ADDR,
        (SPI_RegType *)MCSPI4_BASE_ADDR,
};

/* The McSPI hardware is not ideal when it comes to how interrupts are generated.
 * The EOW interrupt  is generated before it's actually permitted to write new data in the FIFO.
 * According to the TRM we have to wait until this is done. This is recorded in the variable "Spi_WaitInRx".
 * The higher frequency of the SPI the shorter the waiting time will be
 * (since it's waiting for the last word to be shifted out)
 */
uint32 Spi_WaitInRx = 0;

/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/


ISR( Spi_Isr_0) {
    Spi_Internal_Isr(GET_SPI_UNIT_PTR(0));
}

ISR( Spi_Isr_1) {
    Spi_Internal_Isr(GET_SPI_UNIT_PTR(1));
}

ISR( Spi_Isr_2) {
    Spi_Internal_Isr(GET_SPI_UNIT_PTR(2));
}

ISR( Spi_Isr_3) {
    Spi_Internal_Isr(GET_SPI_UNIT_PTR(3));
}


#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)	/*lint -e961 */

static void installChannelInterrupt(uint8 Chnl) {
    switch (Chnl) {
#if (SPI_USE_HW_UNIT_0 == STD_ON)
        case 0:
#if defined(CFG_JAC5) || defined(CFG_JAC5E)
            ISR_INSTALL_ISR2("Spi0", Spi_Isr_0, (IrqType )(SPIINT0_IRQ), SPI_ISR_PRIORITY, 0);
#else //CFG_JAC6
            ISR_INSTALL_ISR2("Spi1", Spi_Isr_0, (IrqType )(MCSPI1_IRQ), SPI_ISR_PRIORITY, 0);
#endif
            break;
#endif
#if (SPI_USE_HW_UNIT_1 == STD_ON)
        case 1:
#if defined(CFG_JAC5) || defined(CFG_JAC5E)
              ISR_INSTALL_ISR2("Spi1", Spi_Isr_1, (IrqType )(SPIINT1_IRQ),SPI_ISR_PRIORITY, 0);
#else //CFG_JAC6
              ISR_INSTALL_ISR2("Spi2", Spi_Isr_1, (IrqType )(MCSPI2_IRQ),SPI_ISR_PRIORITY, 0);
#endif
            break;
#endif
#if (SPI_USE_HW_UNIT_2 == STD_ON)
        case 2:
#if defined(CFG_JAC5) || defined(CFG_JAC5E)
            ISR_INSTALL_ISR2("Spi2", Spi_Isr_2, (IrqType )(SPIINT2_IRQ), SPI_ISR_PRIORITY, 0);
#else //CFG_JAC6
            ISR_INSTALL_ISR2("Spi3", Spi_Isr_2, (IrqType )(MCSPI3_IRQ), SPI_ISR_PRIORITY, 0);
#endif
            break;
#endif
#if (SPI_USE_HW_UNIT_3 == STD_ON)
        case 3:
#if defined(CFG_JAC5) || defined(CFG_JAC5E)
            ISR_INSTALL_ISR2("Spi3", Spi_Isr_3, (IrqType )(SPIINT3_IRQ), SPI_ISR_PRIORITY, 0);
#else //CFG_JAC6
            ISR_INSTALL_ISR2("Spi4", Spi_Isr_3, (IrqType )(MCSPI4_IRQ), SPI_ISR_PRIORITY, 0);
#endif
            break;
#endif
        default:
            break;
    }
}
#endif


static void getJobInfo(const Spi_UnitType *uPtr, uint16_t *numberOfChannels, uint16_t *totalJobLength)
{
    Spi_NumberOfDataType totalLength = 0;
    Spi_NumberOfDataType chnLength = 0;
    uint16_t n;
    uint16_t nbrOfChan = Spi_Internal_GetNbrChnInJob(uPtr);
    *totalJobLength = 0;

    for(n = 0; n < nbrOfChan; n++) {

        /*lint -e{934} Taking address of near auto variable Misra 2004 1.2 2012 1.3 Using stack pointer as argument is tolerable. */
        Spi_Internal_GetTxChBuf( uPtr->jobPtr->SpiChannelAssignment[n]->SpiChannelId, &chnLength);
        /* chnLength is in "units", convert to bytes */
        chnLength = chnLength * ((uPtr->jobPtr->SpiChannelAssignment[n]->SpiDataWidth - 1UL)/8UL + 1UL);

        totalLength += chnLength;
    }

    *numberOfChannels = n;
    *totalJobLength = totalLength;
}

/**
 * @brief Sets upp all the default settings for a given external device.
 * This means setting up the SPI hardware unit and its channels according to the given
 * configuration (baudrate etc).
 *
 * This can be done before hand since the HW have one set of registers for each CS.
 *
 *
 * @param ePtr Represents an external device to communicate with.
 */
static void setupExternalDevice(const struct Spi_ExternalDevice *ePtr ) {
    uint32 divider;
    uint32 clock;
    uint8 hwCh = ePtr->SpiHwUnit;
    uint8 csCh = ePtr->SpiCsIdentifier;
    SPI_RegType *hwPtr = Spi_HwRegs[hwCh];

    hwPtr->MCSPI_CHn[csCh].MCSPI_CHnCONF.B.TRM = 0; 		/* Tx/RX mode */

    /* Chip Select active LOW */
    hwPtr->MCSPI_CHn[csCh].MCSPI_CHnCONF.B.EPOL = 1;

    hwPtr->MCSPI_CHn[csCh].MCSPI_CHnCONF.B.POL = (ePtr->SpiShiftClockIdleLevel == STD_LOW) ? 0 : 1;
    hwPtr->MCSPI_CHn[csCh].MCSPI_CHnCONF.B.PHA = (ePtr->SpiDataShiftEdge == SPI_EDGE_LEADING) ? 0 : 1;

    /*
     * Clock setup
     *   - Always use CHnCONF.B.CLKG (12-bit clock divider)
     *   - Minimum supported freq. is then 48000000/4096 = 11.7Khz
     *
     * baud = clock / divider -> divider = clock / baud
     */
    clock = Mcu_Arc_GetPeripheralClock(PERIPHERAL_CLOCK_SPI);
    divider = clock / ePtr->SpiBaudrate;

    hwPtr->MCSPI_CHn[csCh].MCSPI_CHnCONF.B.CLKG = 1;
    hwPtr->MCSPI_CHn[csCh].MCSPI_CHnCTRL.B.EXTCLK = (divider >> 4u);
    hwPtr->MCSPI_CHn[csCh].MCSPI_CHnCONF.B.CLKD = (divider & 0xfuL);

    /*
     * FIFO Setup
     */
    hwPtr->MCSPI_CHn[csCh].MCSPI_CHnCONF.B.FFER = 1;
    hwPtr->MCSPI_CHn[csCh].MCSPI_CHnCONF.B.FFEW = 1;		/* RM_ERROR: Must be 011 here instead of 010 */
}

void Spi_Hw_InitController(uint32 hwUnit) {
}

/* @req SWS_Spi_00013 */
void Spi_Hw_Init(const Spi_ConfigType *ConfigPtr) {
    uint8 hwCh;
    static struct privData    Spi_PrivateData[SPI_CONTROLLER_CNT];

    /* Loop over all configured channels */
    for (uint8 ch = 0; ch < SPI_ARC_CTRL_CONFIG_CNT; ch++) {
        hwCh = ChannelToHwChannel(ch);
        Spi_Unit[ch].pData = &Spi_PrivateData[ch];

        /* Reset Controller */

        Spi_HwRegs[hwCh]->MCSPI_SYSCONFIG |= 2;	/* Soft reset */

        /* Wait for reset to complete */
        while( Spi_HwRegs[hwCh]->MCSPI_SYSSTATUS  ==  0 ) {
        }

        /* Direction of SPI_D[0] and SPI_D[1]
         * D[0] - Output
         * D[1] - Input
         * */
        Spi_HwRegs[hwCh]->MCSPI_SYST = 0x200;

        /* Set Master Mode */
        Spi_HwRegs[hwCh]->MCSPI_MODULCTRL.B.MS = 0;
        /* Set SINGLE mode */
        Spi_HwRegs[hwCh]->MCSPI_MODULCTRL.B.SINGLE = 1;

#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
        installChannelInterrupt(hwCh);
#endif

    }

    /* External Device */
    for (uint32 j=0; j < SPI_EXT_DEVICES_CNT; j++) {
        setupExternalDevice(&ConfigPtr->SpiExternalDevice[j]);
    }
}


sint32 Spi_Hw_Tx(Spi_UnitType *uPtr)
{

    const Spi_DataBufferType  	*bufPtr;
    const Spi_ChannelConfigType *chPtr;
    SPI_RegType 				*hwPtr;
    Spi_NumberOfDataType 		chUnitCnt;
    uint32 			i;
    boolean         done;
    uint32 			csCh;
    sint32 			rv;
    uint32 			bytesPerUnit;
    uint32 			bytesToCopy;
    uint16 			numberOfChannels;

    hwPtr = Spi_HwRegs[uPtr->hwUnit];

    done = FALSE;
    rv = SPIE_JOB_PENDING;

    csCh = uPtr->extDevPtr->SpiCsIdentifier;

    /* Check if initial frames */
    if( (uPtr->txChIdxInJob == 0) && (uPtr->pData->chTxBytesCopied == 0)  ) {
        getJobInfo(uPtr, &numberOfChannels, &uPtr->pData->jobLengthInBytes);

        /* Write WL and XFERLEVEL */
        hwPtr->MCSPI_CHn[csCh].MCSPI_CHnCONF.B.WL = 7;		/* 7 - 8-bits */
        //hwPtr->MCSPI_XFERLEVEL.B.WCNT = jobLengthCheck;

        /* Write XFERLEVEL[AEL] to the FIFO how much we want to send....
         * This will trigger almost empty interrupt, ie trigger MCSPI_IRQSTATUS[TXx_EMPTY]
         * once the module is enabled (MCSPI_CHnCTRL.B.EN)*/

        hwPtr->MCSPI_XFERLEVEL.B.AFL = FIFO_DEPTH - 1;
        hwPtr->MCSPI_XFERLEVEL.B.AEL = FIFO_DEPTH - 1;
        uPtr->pData->jobTxBytesCopied = 0;

        /* Force the CS Active */
        hwPtr->MCSPI_CHn[csCh].MCSPI_CHnCONF.B.FORCE = 1;
    }

    /* Reset all IRQ status */
    hwPtr->MCSPI_IRQSTATUS.R = 0x0003777FUL;

    /* Write WCNT */
    hwPtr->MCSPI_XFERLEVEL.B.WCNT = MIN(uPtr->pData->jobLengthInBytes - uPtr->pData->jobTxBytesCopied, FIFO_DEPTH);

    /* Enable channel */
    hwPtr->MCSPI_CHn[csCh].MCSPI_CHnCTRL.B.EN = 1;

    /*
     * We are going to process multiple channels for this job as long
     * as the FIFO is not full.
     *
     * Since we have full control over the CS we use WL=8-bits for all transfers ->
     * WCNT is the number of bytes we want to send.
     */

    uPtr->pData->fifoCopyCnt = 0;

    do {
        chPtr = uPtr->jobPtr->SpiChannelAssignment[uPtr->txChIdxInJob];
        ASSERT(chPtr!=NULL);

        bufPtr = Spi_Internal_GetTxChBuf( chPtr->SpiChannelId, &chUnitCnt);

        /* chUnitCnt is in units, find out how many bytes it is */
        bytesPerUnit = (chPtr->SpiDataWidth - 1UL) / 8UL + 1UL;

        /* Since both the channel or the FIFO can be limiting to how many bytes we copy
         * we take the minimum of the two */
        bytesToCopy = MIN(FIFO_DEPTH - uPtr->pData->fifoCopyCnt, chUnitCnt * bytesPerUnit - uPtr->pData->chTxBytesCopied);

        /* Fill the FIFO */
        if( bufPtr != NULL ) {
            if( chPtr->SpiDataWidth > 8 )
            {
                /* 9 to 16-bit transfers, WL is STILL 8-bit here. */
                for (i = 0; i < bytesToCopy/2; i++)
                {
                    uint16 txData = *(uint16 *)&bufPtr[uPtr->pData->chTxBytesCopied];
                    hwPtr->MCSPI_CHn[csCh].MCSPI_TXn = (uint32)((txData>>8U)&0xffUL);
                    hwPtr->MCSPI_CHn[csCh].MCSPI_TXn = (txData & 0xffUL);
                    uPtr->pData->chTxBytesCopied += 2U;
                }
            } else {
                /* <= 8-bit transfers */
                for (i = 0; i < bytesToCopy; i++)
                {
                    uint8 txData = bufPtr[uPtr->pData->chTxBytesCopied];
                    hwPtr->MCSPI_CHn[csCh].MCSPI_TXn = (uint32)txData;
                    uPtr->pData->chTxBytesCopied += 1U;
                }
            }
        } else {
            /* default data */
            for (i = 0; i < bytesToCopy; i++) {
                hwPtr->MCSPI_CHn[csCh].MCSPI_TXn = chPtr->SpiDefaultData;
            }
            uPtr->pData->chTxBytesCopied += bytesToCopy;
        }

        /* We have now either filled the FIFO or we are done with
         * a channel or both */
        uPtr->pData->fifoCopyCnt += bytesToCopy;
        /* Save in order to calculate next WCNT */
        uPtr->pData->jobTxBytesCopied += bytesToCopy;

        /* Space left in FIFO? */
        if( FIFO_DEPTH == uPtr->pData->fifoCopyCnt )
        {
            done = TRUE;
        }

        /* Check if this channel is done */
        if( (chUnitCnt * bytesPerUnit) == uPtr->pData->chTxBytesCopied )
        {
               uPtr->pData->chTxBytesCopied = 0;
               uPtr->txChIdxInJob++;
               if ( uPtr->jobPtr->SpiChannelAssignment[uPtr->txChIdxInJob] == NULL ) { /*lint !e9032 Comparison to NULL is ok */
                   uPtr->txChIdxInJob = 0;
                   /* CS will be raised by RX routine */
                   done = TRUE;
                   rv = SPIE_OK;
               } else {
               }
        }
    } while (!done);

    if ((uPtr->callType == SPI_ASYNC_CALL) && (Spi_Global.asyncMode == SPI_INTERRUPT_MODE))
    {
       Spi_Hw_EnableInterrupt(uPtr->hwUnit);
   }

    return rv;
}

sint32 Spi_Hw_Rx(Spi_UnitType *uPtr) {
    const Spi_ChannelConfigType *chPtr;
    Spi_DataBufferType 			*bufPtr;
    SPI_RegType 				*hwPtr;
    Spi_NumberOfDataType 		chUnitCnt;
    uint16 	i;
    uint32 	csCh;
    uint32 	bytesInFifo;
    uint32 	bytesPerUnit;
    uint32 	popVal;
    sint32  rv;
    uint32 	bytesToCopy;

    hwPtr = Spi_HwRegs[uPtr->hwUnit];
    rv = SPIE_JOB_PENDING;

    /* When we are here we have received a TX_EMPTY interrupt, so
     * we must now read the FIFO, with so many entries that we just
     * sent in previous TX.
     */

    csCh = uPtr->extDevPtr->SpiCsIdentifier;

    /* If we use EOW/TX_EMPTY we must sadly wait here. The "End Of Word" interrupt
     * is generated before everything have been sent....
     * See "End Of Transfer Management" in TRM */
    while( hwPtr->MCSPI_XFERLEVEL.B.WCNT != 0 ) {
        Spi_WaitInRx++;
    };

    /* Disable channel */
    hwPtr->MCSPI_CHn[csCh].MCSPI_CHnCTRL.B.EN = 0;

    /* How many bytes we have just sent */
    bytesInFifo = uPtr->pData->fifoCopyCnt;

    do
    {
        chPtr = uPtr->jobPtr->SpiChannelAssignment[uPtr->rxChIdxInJob];
        ASSERT(chPtr!=NULL);

        bufPtr 			= Spi_Internal_GetRxChBuf( chPtr->SpiChannelId, &chUnitCnt);
        bytesPerUnit = (chPtr->SpiDataWidth - 1UL) / 8UL + 1UL;
        bytesToCopy 	= MIN(bytesInFifo, chUnitCnt * bytesPerUnit);

        /* Fill the FIFO */
        if( bufPtr != NULL ) {
            if( chPtr->SpiDataWidth > 8 )
            {
                /* 9 to 16-bit transfers, WL is STILL 8-bit here. */
                for (i = 0; i < bytesToCopy/2; i++)
                {
                    /* IMPROVEMENT: Check order */
                    uint16 *rxData = (uint16 *)&bufPtr[uPtr->pData->chRxBytesCopied];
                    uint32 tmp = hwPtr->MCSPI_CHn[csCh].MCSPI_RXn;
                    *rxData = (tmp<<8u) + (hwPtr->MCSPI_CHn[csCh].MCSPI_RXn & 0xfful);
                    uPtr->pData->chRxBytesCopied += 2U;
                }
            } else {
                /* <= 8-bit transfers */
                for (i = 0; i < bytesToCopy; i++)
                {
                    bufPtr[uPtr->pData->chRxBytesCopied] = hwPtr->MCSPI_CHn[csCh].MCSPI_RXn;
                    uPtr->pData->chRxBytesCopied += 1U;
                }
            }
        } else {
            /* No RX buffer so just pop the data without action */
            for (i = 0; i < bytesToCopy; i++) {
                popVal = hwPtr->MCSPI_CHn[csCh].MCSPI_RXn;
            }
            (void)popVal; 	/* compiler touch */
            uPtr->pData->chRxBytesCopied += bytesToCopy;
        }

        /* Decrease the number of bytes in the FIFO with the number of bytes we have
         * just popped. */
        bytesInFifo -= bytesToCopy;

        /* Check if this channel is done  */
        if( (chUnitCnt * bytesPerUnit) == uPtr->pData->chRxBytesCopied )
        {
            uPtr->pData->chRxBytesCopied = 0;
            /* Check this is the last channel in the job */
            uPtr->rxChIdxInJob++;
            if ( uPtr->jobPtr->SpiChannelAssignment[uPtr->rxChIdxInJob] == NULL )	/*lint !e9032 Comparison to NULL is ok */
            {
                uPtr->rxChIdxInJob = 0;
                rv = SPIE_OK;

                /* De-assert the CS */
                hwPtr->MCSPI_CHn[csCh].MCSPI_CHnCONF.B.FORCE = 0;

                /* break for loop */
                break;
            }
        }
    } while (bytesInFifo != 0);

    return rv;
}


void Spi_Hw_EndTransmission(Spi_UnitType *uPtr)
{
}

void Spi_Hw_DeInitController(uint32 hwUnit) {
}

void Spi_Hw_DisableInterrupt(uint32 hwUnit) {
    /* Disable EOW */
    Spi_HwRegs[hwUnit]->MCSPI_IRQENABLE = 0;
}

void Spi_Hw_EnableInterrupt(uint32 hwUnit) {
    /* Enable EOW
     * Note! We could get the same result with 0x00001111UL */
    Spi_HwRegs[hwUnit]->MCSPI_IRQENABLE = 0x00020000UL;
}

void Spi_Hw_Halt(uint32 hwUnit) {
}

boolean Spi_Hw_IsTransmissionDone( uint32 hwUnit ) {
    return (Spi_HwRegs[hwUnit]->MCSPI_XFERLEVEL.B.WCNT == 0);
}








