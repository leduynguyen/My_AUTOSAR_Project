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

/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */
/** @tagSettings DEFAULT_ARCHITECTURE=RH850F1H */


/*lint -save -e9003 Misra 2012 8.9 Blockscope variables definitions neglected.
 * Static variable declaration in Function body violates the AUTOSAR memory mapping concept.*/

/* ----------------------------[includes]------------------------------------*/

#include "Spi_Internal.h"
#include "Arc_Types.h"
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
#include "isr.h"
#include "irq_types.h"
#endif
#include "Mcu.h"
#include "Os.h"

//#define USE_LDEBUG_PRINTF
#include "debug.h"

/* ----------------------------[private define]------------------------------*/

#if defined(CFG_RH850F1L)
#define CSIH_BASE    0xFFD80000UL
#else
#error No device selected.
#endif

#define SPI_ISR_PRIORITY      6U
#define FIFO_DEPTH            128U

/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/

/*lint --e{754} --e{46} Turn off local union member not referenced since it's hardware mapping */
typedef union
{                                                          /* IOR              */
    uint8  UINT8;                                          /* 8-bit Access     */
} __type13;


typedef union {
    vuint16_t R;
    struct {
        vuint16_t CSIHnTO:5;
        vuint16_t :3;
        vuint16_t CSIHnMMS:2;
        vuint16_t :6;
    } B;
} SPI_MCTL0_t;


typedef union {
    vuint16_t R;
    struct {
        vuint16_t :13;
        vuint16_t CSIHnPRS:3;
    } B;
} SPI_CTL2_t;


typedef union {
    vuint32_t R;
    struct {
        vuint32_t CSIHnSSE:1;
        vuint32_t CSIHnHSE:1;
        vuint32_t CSIHnSIT:1;
        vuint32_t CSIHnLBM:1;
        vuint32_t CSIHnCSRI:1;
        vuint32_t CSIHnDCS:1;
        vuint32_t CSIHnJE:1;
        vuint32_t CSIHnEDLE:1;
        vuint32_t CSIHnCSLx:1;
        vuint32_t CSIHnSLIT:1;
        vuint32_t CSIHnCKR:1;
        vuint32_t CSIHnPHE:1;
        vuint32_t :6;
        vuint32_t CSIHnSLRS:1;
        vuint32_t :7;
    } B;
} SPI_CTL1_t;

typedef union {
    vuint32_t R;
    struct {
        vuint32_t CSIHnFFS:7;
        vuint32_t :9;
        vuint32_t CSIHnFES:7;
        vuint32_t :9;
    } B;
} SPI_MCTL1_t;


typedef union {
    vuint16_t R;
    struct {
        vuint16_t CSIHnOVEC:1;
        vuint16_t CSIHnPEC:1;
        vuint16_t :1;
        vuint16_t CSIHnDCEC:1;
        vuint16_t :4;
        vuint16_t CSIHnPCT:1;
        vuint16_t :5;
        vuint16_t CSIHnOFEC:1;
        vuint16_t CSIHnTMOEC:1;
    } B;
} SPI_STCR0_t;


typedef union {
    vuint32_t R;
    struct {
        vuint32_t CSIHnOVE:1;
        vuint32_t CSIHnPE:1;
        vuint32_t :1;
        vuint32_t CSIHnDCE:1;
        vuint32_t CSIHnEMF:1;
        vuint32_t CSIHnFLF:1;
        vuint32_t :1;
        vuint32_t CSIHnTSF:1;
        vuint32_t CSIHnHPST:1;
        vuint32_t :5;
        vuint32_t CSIHnOFE:1;
        vuint32_t CSIHnTMOE:1;
        vuint32_t CSIHnSPF:8;
        vuint32_t CSIHnSRP:8;
    } B;
} SPI_STR0_t;



typedef union {
    vuint32_t R;
    struct {
        vuint32_t CSIHnSPx:4;
        vuint32_t CSIHnINx:4;
        vuint32_t CSIHnHDx:4;
        vuint32_t CSIHnIDx:3;
        vuint32_t CSIHnIDLx:1;
        vuint32_t CSIHnDAPx:1;
        vuint32_t CSIHnCKPx:1;
        vuint32_t CSIHnDIRx:1;
        vuint32_t CSIHnRCBx:1;
        vuint32_t :4;
        vuint32_t CSIHnDLSx:4;
        vuint32_t CSIHnPSx:2;
        vuint32_t CSIHnBRSSx:2;
    } B;
} SPI_CFG_t;

typedef union {
    vuint8_t R;
    struct {
        vuint8_t CSIHnMBS:1;
        vuint8_t CSIHnJOBE:1;
        vuint8_t :3;
        vuint8_t CSIHnRXE:1;
        vuint8_t CSIHnTXE:1;
        vuint8_t CSIHnPWR:1;
    } B;
} SPI_CTL0_t;

typedef struct
{                                                          /* Module           */
    SPI_CTL0_t CTL0;                                       /* CTL0             */
    uint8  dummy56[3];                                     /* Reserved         */
    const SPI_STR0_t STR0;                                 /* STR0             */
    SPI_STCR0_t STCR0;                                     /* STCR0            */
    uint8  dummy57[6];                                     /* Reserved         */
    SPI_CTL1_t CTL1;                                       /* CTL1             */
    SPI_CTL2_t CTL2;                                       /* CTL2             */
    uint8  dummy58[2];                                     /* Reserved         */
    __type13 EMU;                                          /* EMU              */
    uint8  dummy59[4071];                                  /* Reserved         */
    SPI_MCTL1_t MCTL1;                                     /* MCTL1            */
    uint32 MCTL2;                                          /* MCTL2            */
    uint32 TX0W;                                           /* TX0W             */
    uint16 TX0H;                                           /* TX0H             */
    uint8  dummy60[2];                                     /* Reserved         */
    const uint32 RX0W;                                     /* RX0W             */
    const uint16 RX0H;                                     /* RX0H             */
    uint8  dummy61[2];                                     /* Reserved         */
    uint32 MRWP0;                                          /* MRWP0            */
    uint8  dummy62[36];                                    /* Reserved         */
    SPI_MCTL0_t MCTL0;                                     /* MCTL0            */
    uint8  dummy63[2];                                     /* Reserved         */
    SPI_CFG_t CFG[4];                                      /* CFG0             */
    uint8  dummy64[20];                                    /* Reserved         */
    uint16 BRS0;                                           /* BRS0             */
    uint8  dummy65[2];                                     /* Reserved         */
    uint16 BRS1;                                           /* BRS1             */
    uint8  dummy66[2];                                     /* Reserved         */
    uint16 BRS2;                                           /* BRS2             */
    uint8  dummy67[2];                                     /* Reserved         */
    uint16 BRS3;                                           /* BRS3             */
} CSIH_RegType;


/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/


/** Prototypes for ISR*/
#if (SPI_USE_HW_UNIT_0 == STD_ON )
ISR(Spi_Isr_0);
#endif
#if (SPI_USE_HW_UNIT_1 == STD_ON )
ISR(Spi_Isr_1);
#endif
/* ----------------------------[private functions]---------------------------*/


#if (SPI_USE_HW_UNIT_0 == STD_ON )
ISR(Spi_Isr_0) {
    if (Spi_Global.asyncMode == SPI_INTERRUPT_MODE ) {
        Spi_Internal_Isr(GET_SPI_UNIT_PTR(0));
    }
}
#endif
#if (SPI_USE_HW_UNIT_1 == STD_ON )
ISR(Spi_Isr_1) {
    if (Spi_Global.asyncMode == SPI_INTERRUPT_MODE ) {
        Spi_Internal_Isr(GET_SPI_UNIT_PTR(1));
    }
}
#endif
/* ----------------------------[public functions]----------------------------*/

/*lint --e{923} HW register cast */
CSIH_RegType * Spi_HwUnitReg[] = {
        (CSIH_RegType *)CSIH_BASE,
        (CSIH_RegType *)(CSIH_BASE + 0x2000UL),
        (CSIH_RegType *)(CSIH_BASE + 0x4000UL),
        (CSIH_RegType *)(CSIH_BASE + 0x6000UL),
};


typedef struct {
    SPI_CTL1_t ctl1;        /* lots of features */
    SPI_CFG_t  cfg;
    uint16        brs;            /* baudrate register */
    uint32     txow;

}ExternalDeviceType;

static ExternalDeviceType hwDeviceCfg[SPI_EXT_DEVICES_CNT];


static boolean spi_isTxFifoEmpty( uint8 hwCh )
{
    return (Spi_HwUnitReg[hwCh]->STR0.B.CSIHnSPF == 0U) ? TRUE : FALSE;
}


static sint32 checkJobTotalLength(const Spi_UnitType *uPtr, uint16_t *numberOfChannels)
{
    Spi_NumberOfDataType totalLength = 0U;
    Spi_NumberOfDataType chnLength = 0U;
    sint32 retval = SPIE_OK;
    uint16_t n;
    uint16_t nbrOfChan = Spi_Internal_GetNbrChnInJob(uPtr);

    for(n = 0U; n < nbrOfChan; n++) {

        /*lint -e{934} Taking address of near auto variable Misra 2004 1.2 2012 1.3 Using stack pointer as argument is tolerable. */
        (void)Spi_Internal_GetTxChBuf( uPtr->jobPtr->SpiChannelAssignment[n]->SpiChannelId, &chnLength);/*lint !e920 cast from pointer to void Misra 2004 1.2, 11.2, 2012 1.3*/
        totalLength += chnLength;
    }

    if (totalLength > FIFO_DEPTH) {
        retval = SPIE_BAD;
    }

    *numberOfChannels = n;
    return retval;
}


/**
 *
 * @param hwPtr
 * @param ePtr
 */
static void setupExternalDevice(const struct Spi_ExternalDevice *ePtr, const SpiZynqDelay0RegType * delayPtr, uint32 deviceIdx ) {

    /*
     * Calc
     *
     * In master mode, the transfer clock frequency is selectable using the following bits:
     *  - CSIHnCTL2.CSIHnPRS[2:0], CSIHnBRSy.CSIHnBRS[11:0], CSIHnCFGx.CSIHnBRSSx[1:0]
     *
     * Transfer clock frequency (CSIHTSCK) = PCLK / (division ratio of PCLK) = PCLK / (2α × k × 2)
     * We set α=0 (PRS=0/prsDiv=1) and then we have CSIHTSCK = PCLK / (k × 2)
     *
     * - CSIHnBRSSx selects any of the 4 BRS
     * - CSIHnBRS, 4095: PCLK / (2α × 4095 × 2), α is the value of CSIHnCTL2.CSIHnPRS[2:0].
     */
    uint32 prsDiv = 1UL;    /* Set fixed value */
    uint32 clock;
    SPI_CTL1_t ctl1 = {.R = 0U};
    SPI_CFG_t cfg = {.R = 0U};

    /* freq = clock / ( 2^0 * x * 2 ) -> x = clock / (freq *2)
     * e.g 80000000 / (100000 * 2) = 400
     * */
    clock = Mcu_Arc_GetPeripheralClock(C_ISO_CSI);
    hwDeviceCfg[deviceIdx].brs = (uint16)(clock / (prsDiv * ePtr->SpiBaudrate * 2UL));

    SPI_ASSERT( ePtr->SpiBaudrate <= 10000000UL);     /* Maximum master mode clock */
    SPI_ASSERT( ePtr->SpiBaudrate <= (clock/4UL));

    ctl1.B.CSIHnJE = 1U;     /* enable job mode     */
    ctl1.B.CSIHnCSRI = 1U;    /* return CS to inactive */
    ctl1.B.CSIHnLBM = 0U;    /* loopback mode     */
    ctl1.B.CSIHnSIT = 0U;    /* interrupt delay     */
    ctl1.B.CSIHnHSE = 0U;    /* no handshake     */
    ctl1.B.CSIHnSSE = 0U;    /* slave select     */

    ctl1.B.CSIHnCKR = (ePtr->SpiShiftClockIdleLevel == STD_LOW) ? 1U: 0U;

    /* CSIH
     * positive edge mode (low to high transition) : CSIHnCTL1.CSIHnSLRS = 0
     * negative edge mode (high to low transition) : CSIHnCTL1.CSIHnSLRS = 1
     *
     * LOW  LEADING  -> 0
     * LOW  TRAILING -> 1
     * HIGH LEADING  -> 1
     * HIGH TRAILING -> 0
     */
    if( ((ePtr->SpiShiftClockIdleLevel == STD_LOW) &&  (ePtr->SpiDataShiftEdge == SPI_EDGE_LEADING)) ||
        ((ePtr->SpiShiftClockIdleLevel == STD_HIGH) &&  (ePtr->SpiDataShiftEdge == SPI_EDGE_TRAILING)) )
    {
        ctl1.B.CSIHnCKR = 0U;
    } else {
        ctl1.B.CSIHnCKR = 1U;
    }

    hwDeviceCfg[deviceIdx].ctl1 = ctl1;

    cfg.B.CSIHnBRSSx = 0U; /* Use BR0 */
    cfg.B.CSIHnDLSx = 8U;  /* 8 bits */

    hwDeviceCfg[deviceIdx].cfg.R = cfg.R;

    hwDeviceCfg[deviceIdx].txow = ((~(1UL<<(ePtr->SpiCsIdentifier+16))) & 0x00ff0000UL);
}


sint32 Spi_Hw_Tx(Spi_UnitType *uPtr ) {
    /* @req SWS_Spi_00311 */
    Spi_NumberOfDataType         txBufSize;
    const Spi_DataBufferType      *txBuf;
    uint16_t numberOfChannels = 0U;
    uint16_t n;
    uint32_t data;
    sint32 jobLengthCheck;
    CSIH_RegType *hwPtr = Spi_HwUnitReg[uPtr->hwUnit];
    uint8 externalDeviceIdx;
    uint32 defaultValue;
    const Spi_ChannelConfigType *chPtr;
    uint32 i = 0U;
    uint32 txow;
    uint32 tmp;

    jobLengthCheck = checkJobTotalLength(uPtr, &numberOfChannels); /*lint !e934 Taking address of near auto variable Misra 2004 1.2 2012 1.3 Using stack pointer as argument is tolerable.*/
    if (jobLengthCheck == SPIE_BAD) {
        return SPIE_BAD;
    }

    SPI_ASSERT(hwPtr->STR0.B.CSIHnEMF == 1U);     /* When EMF = 1 -> FIFO Empty */

    /* Setup HW to match configuration */
    externalDeviceIdx = Spi_Global.configPtr->SpiHwDeviceConfig->SpiHwExternalDeviceIdx[uPtr->jobPtr->SpiJobId];

    hwPtr->CTL1.R = hwDeviceCfg[externalDeviceIdx].ctl1.R;
    hwPtr->BRS0 = hwDeviceCfg[externalDeviceIdx].brs;

    hwPtr->CFG[0].R = hwDeviceCfg[externalDeviceIdx].cfg.R;
    hwPtr->CFG[1].R = hwDeviceCfg[externalDeviceIdx].cfg.R;
    hwPtr->CFG[2].R = hwDeviceCfg[externalDeviceIdx].cfg.R;
    hwPtr->CFG[3].R = hwDeviceCfg[externalDeviceIdx].cfg.R;
    txow = hwDeviceCfg[externalDeviceIdx].txow;
    if ((uPtr->callType == SPI_ASYNC_CALL) && (Spi_Global.asyncMode == SPI_INTERRUPT_MODE)) {
        txow |= 0x80000000UL;        /* CSIHnCIRE */

    }

    hwPtr->STCR0.B.CSIHnPCT = 1U;     /* Clear FIFO buffers */
    hwPtr->CTL0.B.CSIHnPWR = 1U;     /* Operation clock */

    /* Bits to manipulate after PWR = 1 */
    hwPtr->CTL0.B.CSIHnTXE = 1U;     /* TX Enable */
    hwPtr->CTL0.B.CSIHnRXE = 1U;     /* RX Enable */
    hwPtr->CTL0.B.CSIHnJOBE = 1U;
    hwPtr->CTL0.B.CSIHnMBS = 0U;     /* Memory mode */

    //LDEBUG_PRINTF("Spi_Hw_Tx\n");

    //Buffer and transmit all channels of the job.
    for (n = 0U; n < numberOfChannels; n++) {

        chPtr = uPtr->jobPtr->SpiChannelAssignment[n];

        /* Get buffer the channel uses (either EB or IB) */
        txBuf = Spi_Internal_GetTxChBuf(chPtr->SpiChannelId, &txBufSize);/*lint !e934 Taking address of near auto variable Misra 2004 1.2 2012 1.3 Using stack pointer as argument is tolerable.*/

        /* Copy from TX channel buffer to HW */
        /* @req SWS_Spi_00028 */
        if (txBuf == NULL) {
            defaultValue = Spi_Internal_GetTxDefValue(chPtr->SpiChannelId);
            for (i = 0U; i < ((uint32)txBufSize - 1U); i++) {
                /* Write data to FIFO */
                tmp = defaultValue | txow;
                hwPtr->TX0W = tmp;
                //LDEBUG_PRINTF("D%08x ",tmp);
            }
            tmp = defaultValue | txow;

            //LDEBUG_PRINTF("DL%08x\n",tmp);

        } else {
            if (chPtr->SpiDataWidth > 8U) {
                uint16 txData;

                /* txBufSize is the number of elements to copy, not bytes */
                for (i = 0U; i < (txBufSize - 1U); i++) {
                    txData = ((uint16 *) txBuf)[i];                             /*lint !e927 !826 Autosar requires cast */
                    /* Write data to FIFO, MSB first */
                    hwPtr->TX0W = (uint32) (((uint32)txData >> 8U) & 0xffUL) | txow;
                    hwPtr->TX0W = (uint32) (((uint32)txData) & 0xffUL) | txow;
                }
                /* Write next last byte */
                txData = ((uint16 *) txBuf)[i];                                 /*lint !e927 !826 Autosar requires cast */
                hwPtr->TX0W = (uint32) ((txData >> 8U) & 0xffUL) | txow;
                tmp = (uint32) ((txData) & 0xffUL) | txow;

            } else {
                for (i = 0u; i < (txBufSize - 1); i++) {
                    /* Write data to FIFO */
                    tmp = txBuf[i] | txow;
                    hwPtr->TX0W = tmp;
                    //LDEBUG_PRINTF("T%08x ",tmp);
                }
                tmp = txBuf[i] | txow;
            }
        }

        /* If the last one, set EOJ */
        if( n== (numberOfChannels-1U)) {
            tmp |= 0x40000000UL;
        }

        hwPtr->TX0W = tmp;
    }

    return SPIE_OK;
}

sint32 Spi_Hw_Rx( Spi_UnitType *uPtr ) {
    Spi_DataBufferType *rxBuf;
    vuint32_t rxData;
    Spi_NumberOfDataType rxLength;
    Spi_NumberOfDataType n;
    const CSIH_RegType *hwPtr = Spi_HwUnitReg[uPtr->hwUnit];
    uint16_t numberOfChannels;
    uint16_t i;
    const Spi_ChannelConfigType *chPtr;

    numberOfChannels = Spi_Internal_GetNbrChnInJob(uPtr);

    LDEBUG_PRINTF("Spi_Hw_Rx: SRP=%d FES=%d\n",hwPtr->STR0.B.CSIHnSRP,hwPtr->MCTL1.B.CSIHnFES);

    for (i = 0U; i < numberOfChannels; i++) {
        chPtr = uPtr->jobPtr->SpiChannelAssignment[i];
        rxBuf = Spi_Internal_GetRxChBuf(chPtr->SpiChannelId, &rxLength);/*lint !e934 Taking address of near auto variable Misra 2004 1.2 2012 1.3 Using stack pointer as argument is tolerable.*/

        if( chPtr->SpiDataWidth > 8U ) {
            uint16 rx16;

            for (n = 0U; n < rxLength; n++) {
                rx16 = (uint16)(hwPtr->RX0W<<8U);
                rx16 |= (hwPtr->RX0W & 0xffU);
                if (rxBuf != NULL) {
                    ((uint16 *) rxBuf)[n] = rx16;   /*lint !e826 !e927  Autosar requires cast */
                }
            }

        } else {
            for (n = 0U; n < rxLength; n++) {
                rxData = hwPtr->RX0W;

                // If its a NULL pointer the data shall not be stored.
                /* @req SWS_Spi_00036 */
                if (rxBuf != NULL) {
                    //Rx register is 32 bit but the data is only valid in bits [7:0].
                    rxBuf[n] = (Spi_DataBufferType) rxData;
                }
            }
        }
    }

    return SPIE_OK;
}

void Spi_Hw_Init( const Spi_ConfigType *ConfigPtr ) {

    /* Follow "15.6.4.2 Transmit/Receive Mode when Job Mode is Enabled in Master Mode"
     */

    uint8 hwCh;

    /* Loop over all configured channels */
    for (uint8 ch = 0U; ch < SPI_ARC_CTRL_CONFIG_CNT; ch++) {
        hwCh = ChannelToHwChannel(ch);

        Spi_HwUnitReg[hwCh]->CTL0.R = 0UL;            /* Disable all */
        Spi_HwUnitReg[hwCh]->CTL1.B.CSIHnJE = 1UL;

        /* 1) */
        Spi_HwUnitReg[hwCh]->CTL2.B.CSIHnPRS = 0UL;        /* Select master mode and clock, alpha = 0 */

        Spi_HwUnitReg[hwCh]->MCTL0.B.CSIHnMMS = 0UL;     /* FIFO MODE */
        Spi_HwUnitReg[hwCh]->MCTL0.B.CSIHnTO = 0x1fUL;    /* No timeout in FIFO mode */

        /* 2) */
        Spi_HwUnitReg[hwCh]->STCR0.B.CSIHnPCT = 1UL;     /* Clear FIFO buffers */

        /* 3) */
        SPI_ASSERT( Spi_HwUnitReg[hwCh]->STR0.B.CSIHnFLF == 0UL);
        SPI_ASSERT( Spi_HwUnitReg[hwCh]->STR0.B.CSIHnEMF == 1UL);
        SPI_ASSERT( Spi_HwUnitReg[hwCh]->STR0.B.CSIHnSPF == 0UL);

        /* 4) Interrupt */
        Spi_HwUnitReg[hwCh]->MCTL1.B.CSIHnFES = 0x0UL;
        Spi_HwUnitReg[hwCh]->MCTL1.B.CSIHnFFS = 0x0UL;

#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
        switch (hwCh) {
#if (SPI_USE_HW_UNIT_0 == STD_ON )
        case 0:
            ISR_INSTALL_ISR2("SPI_0", Spi_Isr_0, IRQ_INTCSIH0IC , SPI_ISR_PRIORITY, 0UL);
            break;
#endif
#if (SPI_USE_HW_UNIT_1 == STD_ON )
            case 1:
            ISR_INSTALL_ISR2("SPI_1",Spi_Isr_1, IRQ_INTCSIH1IC, SPI_ISR_PRIORITY, 0UL);
            break;
#endif
#if (SPI_USE_HW_UNIT_2 == STD_ON )
            case 2:
            ISR_INSTALL_ISR2("SPI_2",Spi_Isr_2, IRQ_INTCSIH2IC, SPI_ISR_PRIORITY, 0UL);
            break;
#endif
#if (SPI_USE_HW_UNIT_3 == STD_ON )
            case 3:
            ISR_INSTALL_ISR2("SPI_3",Spi_Isr_3, IRQ_INTCSIH3IC, SPI_ISR_PRIORITY, 0UL);
            break;
#endif
            default:
                SPI_ASSERT(0);
        }
#endif
    }

    /* External Device */
    for (uint32 j=0U; j < SPI_EXT_DEVICES_CNT; j++) {
        setupExternalDevice(&ConfigPtr->SpiExternalDevice[j], &ConfigPtr->SpiHwDeviceConfig->SpiHwDelayReg[j], j);
    }
}

void Spi_Hw_InitController( uint32 hwUnit ) {
    (void)hwUnit; /*lint !e920 Argument not used */
}

void Spi_Hw_DeInitController(uint32 hwUnit ) {
    (void)hwUnit; /*lint !e920 Argument not used */
}

boolean Spi_Hw_IsTransmissionDone( uint32 hwUnit )
{
    return spi_isTxFifoEmpty((uint8)hwUnit);
}

void Spi_Hw_Halt( uint32 hwUnit ) {
    (void)hwUnit; /*lint !e920 Argument not used */
}

void Spi_Hw_DisableInterrupt( uint32 hwUnit ) {
    (void)hwUnit; /*lint !e920 Argument not used */
}
void Spi_Hw_EnableInterrupt( uint32 hwUnit ) {
    (void)hwUnit; /*lint !e920 Argument not used */
}

void Spi_Hw_EndTransmission(Spi_UnitType *uPtr) {
    (void)uPtr; /*lint !e920 Argument not used */

}
