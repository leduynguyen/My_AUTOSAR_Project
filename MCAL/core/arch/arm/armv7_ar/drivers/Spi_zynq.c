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
/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ */

/* @req SWS_Spi_00149 - The driver shall take care of the differences between the frame width of the channel and the data access data type. */
/* @req SWS_Spi_00263 - Chip Select shall be handled during Job transmission and shall be released at the end of it. */
/* @req SWS_Spi_00438 - The driver shall provide separate buffers for receive and transmit. */

/*lint -save -e9003 Misra 2012 8.9 Blockscope variables definitions neglected.
 * Static variable declaration in Function body violates the AUTOSAR memory mapping concept.*/

/* ----------------------------[includes]------------------------------------*/

#include "Spi_Internal.h"
#include "zynq.h"
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
#include "isr.h"
#include "irq_zynq.h"
#endif
#include "Mcu.h"
#include "Os.h"

/* ----------------------------[private define]------------------------------*/
#define SPI_ISR_PRIORITY                4u
#define FIFO_DEPTH		                128u
#define MASK_INTERRUPT_DISABLE          0x0000007Fu
#define TX_FIFO_UNDERFLOW	            ((uint32)1<<6u)
#define TX_FIFO_NO_FULL                 ((uint32)1<<2u)

#define CONFIG_REG_RST_VALUE            0x00020000u
#define INTRPT_EN_REG_RST_VALUE         0x00000000u
#define INTRPT_DIS_REG_RST_VALUE        0x00000000u
#define EN_REG_RST_VALUE                0x00000000u
#define DELAY_REG_RST_VALUE             0x00000000u
#define TX_DATA_REG_RST_VALUE           0x00000000u
#define SLAVE_IDLE_COUNT_REG_RST_VALUE  0x000000FFu
#define TX_THRES_REG_RST_VALUE          0x00000001u
#define RX_THRES_REG_RST_VALUE          0x00000001u

#define RX_FIFO_NOT_EMPTY_MASK          0x00000010u
#define TX_FIFO_NOT_EMPTY_MASK          0x00000004u

#define MASTER_MODE                     0x00000001u
#define MAN_START_EN                    0x00008000u

#define MASK_CLR_D_INIT                 0xFFFFFF00u

#define BAUD_DIV_INVALID        0u
#define BAUD_DIV_4              4u
#define BAUD_DIV_8              8u
#define BAUD_DIV_16             16u
#define BAUD_DIV_32             32u
#define BAUD_DIV_64             64u
#define BAUD_DIV_128            128u
#define BAUD_DIV_256            256u
#define NBR_VALID_BAUD_DIV      7u

#define SHIFT_CHIP_SELECT(_x)   ((uint32)(_x)<<10u)
#define CS_SIZE_MASK            0x0Fu
#define SHIFT_DIVIDER(_x)       ((uint32)(_x)<<3u)
#define CLK_PH_MASK             0x00000004u
#define CLK_POL_MASK            0x00000002u

#define MAX_CLK2CS_DELAY_TICKS 255u

/* ----------------------------[private macro]-------------------------------*/

#define  GET_SPI_HW_PTR(_unit)    (SPI_PTR[_unit])

/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

/* Set SFR registers of Spi properly.*/
typedef volatile struct SPI_reg Spi_HwRegType;
/*lint -e{923} cast from unsigned int to pointer MISRA 2004 11.1 11.3 2012 11.4 11.6
 * Integer to pointer casting is necessary to set SFR of Microcontroller. */
static Spi_HwRegType* const SPI_PTR[2] =
{
        (Spi_HwRegType*)ZYNQ_SPI_BASE,
        (Spi_HwRegType*)(ZYNQ_SPI_BASE+0x1000u),
};

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
    Spi_Internal_Isr(GET_SPI_UNIT_PTR(0));
}
#endif
#if (SPI_USE_HW_UNIT_1 == STD_ON )
ISR(Spi_Isr_1) {
    Spi_Internal_Isr(GET_SPI_UNIT_PTR(1));
}
#endif


static void emptyRxFifo(const Spi_HwRegType *hwPtr);
static void emptyTxFifo(Spi_HwRegType *hwPtr);
static void emptyRxTxFifo(Spi_HwRegType *hwPtr);
static sint32 checkJobTotalLength(const Spi_UnitType *uPtr, uint16_t *numberOfChannels);

static const uint16_t baudrateDiv[NBR_VALID_BAUD_DIV] = {BAUD_DIV_4, BAUD_DIV_8, BAUD_DIV_16, BAUD_DIV_32, BAUD_DIV_64, BAUD_DIV_128, BAUD_DIV_256};

/* ----------------------------[public functions]----------------------------*/


typedef struct {
    uint32 configReg0;
    uint32 delayReg0;
}ExternalDeviceType;

static ExternalDeviceType hwDeviceCfg[SPI_EXT_DEVICES_CNT];
/**
 *
 * @param hwPtr
 * @param ePtr
 */
static void setupExternalDevice(const struct Spi_ExternalDevice *ePtr, const SpiZynqDelay0RegType * delayPtr, uint32 deviceIdx ) {
    uint8_t n;
    uint32_t chipSelect = SHIFT_CHIP_SELECT(ePtr->SpiCsIdentifier & CS_SIZE_MASK);
    uint32_t polarity = (ePtr->SpiShiftClockIdleLevel == STD_LOW) ? (uint32)0u : CLK_POL_MASK;
    uint32_t shiftLevel = (ePtr->SpiDataShiftEdge == SPI_EDGE_LEADING) ? (uint32)0u : CLK_PH_MASK;
    uint32_t wantedDivider = (MCU_ARC_CLOCK_SPI_0_FREQUENCY + (ePtr->SpiBaudrate/2))/ ePtr->SpiBaudrate;
    uint32_t wantedClk2CsDelay = 0;
    uint32_t actualDivider = BAUD_DIV_INVALID;

    for (n = 0u; n < NBR_VALID_BAUD_DIV; n++) {
        if (wantedDivider >= (uint32)baudrateDiv[n]) { /*lint !e9033 Impermissible cast of composite expression Misra 2012 10.8 */
            actualDivider = SHIFT_DIVIDER(n + 1u);     /*lint !e9033 Impermissible cast of composite expression Misra 2012 10.8 */
        }
    }

    if( BAUD_DIV_INVALID == actualDivider ) {
        /* Did not find a suiting divider */
        SPI_DET_REPORT_ERROR(SPI_GENERAL_SERVICE_ID, SPI_E_CONFIG_INVALID);
        actualDivider = SHIFT_DIVIDER(NBR_VALID_BAUD_DIV);
    }

    hwDeviceCfg[deviceIdx].configReg0 = MAN_START_EN | chipSelect | actualDivider | polarity | shiftLevel | MASTER_MODE;

    if (ePtr->SpiTimeClk2Cs != 0) {
        wantedClk2CsDelay = (ePtr->SpiTimeClk2Cs * (MCU_ARC_CLOCK_SPI_0_FREQUENCY / 1000000) ) /1000;
        //Delay register can only delay a max of 255 MCU_ARC_CLOCK_SPI_0_FREQUENCY cycles.
        if( wantedClk2CsDelay > MAX_CLK2CS_DELAY_TICKS ) {
            SPI_DET_REPORT_ERROR(SPI_GENERAL_SERVICE_ID, SPI_E_CONFIG_INVALID);
            wantedClk2CsDelay = MAX_CLK2CS_DELAY_TICKS;
        }
    }

    hwDeviceCfg[deviceIdx].delayReg0 = (delayPtr->SpiArcDNss << 24u) | (delayPtr->SpiArcDBtwn << 16u) | \
                    (delayPtr->SpiArcDAfter << 8u) | wantedClk2CsDelay;
}



/**
 * Writes data to the SPI device. This is always a job.
 *
 * @param uPtr
 */
/*lint -save -e818 Pointer parameter 'uPtr' could be declared as pointing to const Misra 2004 16.7 2012 8.13
 * It has to be tolerated, because the function definition is coming from a commonly used header file:  Spi_Internal.h*/
sint32 Spi_Hw_Tx(Spi_UnitType *uPtr ) {

    /* @req SWS_Spi_00311 */

    Spi_NumberOfDataType 		txBufSize;
    const Spi_DataBufferType  	*txBuf;
    uint16_t numberOfChannels = 0;
    uint16_t n;
    uint32_t data;
    sint32 jobLengthCheck;
    Spi_HwRegType *hwPtr = GET_SPI_HW_PTR(uPtr->hwUnit);
    uint8 externalDeviceIdx;
    uint32 defaultValue;
    const Spi_ChannelConfigType *chPtr;

    jobLengthCheck = checkJobTotalLength(uPtr, &numberOfChannels); /*lint !e934 Taking address of near auto variable Misra 2004 1.2 2012 1.3 Using stack pointer as argument is tolerable.*/
    if (jobLengthCheck == SPIE_BAD) {
        return SPIE_BAD;
    }

    hwPtr->En_reg0 = 1;

    /* Setup HW to match configuration */
    externalDeviceIdx = Spi_Global.configPtr->SpiHwDeviceConfig->SpiHwExternalDeviceIdx[uPtr->jobPtr->SpiJobId];
    hwPtr->Config_reg0 = hwDeviceCfg[externalDeviceIdx].configReg0;
    hwPtr->Delay_reg0  = hwDeviceCfg[externalDeviceIdx].delayReg0;

    //Buffer and transmit all channels of the job.
    for (n = 0; n < numberOfChannels; n++) {

        chPtr = uPtr->jobPtr->SpiChannelAssignment[n];

        /* Get buffer the channel uses (either EB or IB) */
        txBuf = Spi_Internal_GetTxChBuf(chPtr->SpiChannelId, &txBufSize);/*lint !e934 Taking address of near auto variable Misra 2004 1.2 2012 1.3 Using stack pointer as argument is tolerable.*/

        /* Copy from TX channel buffer to HW */
        /* @req SWS_Spi_00028 */
        defaultValue = Spi_Internal_GetTxDefValue(chPtr->SpiChannelId);

        for (uint32 i=0u; i < txBufSize ; i++ ) {
            data = (txBuf != NULL) ? (uint32_t)txBuf[i] : defaultValue; /*lint !e9033 Impermissible cast of composite expression Misra 2012 10.8 */

            hwPtr->Tx_data_reg0 = data;
        }

    }

    if ((uPtr->callType == SPI_ASYNC_CALL) && (Spi_Global.asyncMode == SPI_INTERRUPT_MODE)) {
        Spi_Hw_EnableInterrupt(uPtr->hwUnit);
    }

    /* Start transmission */
    hwPtr->Config_reg0 |= ((uint32)1u<<16u);

    return SPIE_OK;
}
/*lint -restore*/

/*lint -save -e818 Pointer parameter 'uPtr' could be declared as pointing to const Misra 2004 16.7 2012 8.13
 * It has to be tolerated, because the function definition is coming from a commonly used header file:  Spi_Internal.h*/
sint32 Spi_Hw_Rx( Spi_UnitType *uPtr ) {
    Spi_DataBufferType *rxBuf;
    vuint32_t rxData;
    Spi_NumberOfDataType rxLength;
    Spi_NumberOfDataType n;
    const Spi_HwRegType *hwPtr = GET_SPI_HW_PTR(uPtr->hwUnit);
    uint16_t numberOfChannels;
    uint16_t i;
    const Spi_ChannelConfigType *chPtr;

    numberOfChannels = Spi_Internal_GetNbrChnInJob(uPtr);

    for (i = 0; i < numberOfChannels; i++) {
        chPtr = uPtr->jobPtr->SpiChannelAssignment[i];
        rxBuf = Spi_Internal_GetRxChBuf(chPtr->SpiChannelId, &rxLength);/*lint !e934 Taking address of near auto variable Misra 2004 1.2 2012 1.3 Using stack pointer as argument is tolerable.*/

        for (n = 0; n < rxLength; n++) {
            rxData = hwPtr->Rx_data_reg0;

            // If its a NULL pointer the data shall not be stored.
            /* @req SWS_Spi_00030 */
            /* @req SWS_Spi_00036 */
            if (rxBuf != NULL) {
                //Rx register is 32 bit but the data is only valid in bits [7:0].
                rxBuf[n] = (Spi_DataBufferType) rxData;
            }
        }
    }

    return SPIE_OK;
}
/*lint -restore*/

/* @req SWS_Spi_00013 */
void Spi_Hw_Init( const Spi_ConfigType *ConfigPtr ) {

    for (uint32_t i=0; i < SPI_CONTROLLER_CNT; i++) {
        Spi_Hw_InitController(Spi_Unit[i].hwUnit);
    }

    for (uint32 j=0; j < SPI_EXT_DEVICES_CNT; j++) {
        setupExternalDevice(&ConfigPtr->SpiExternalDevice[j], &ConfigPtr->SpiHwDeviceConfig->SpiHwDelayReg[j], j);
    }
}

//-------------------------------------------------------------------

void Spi_Hw_InitController( uint32 hwUnit ) {
    Spi_HwRegType *spiHw = GET_SPI_HW_PTR(hwUnit);

    /* Enable Controller */
    spiHw->Config_reg0 = (uint32_t)(MAN_START_EN | MASTER_MODE);

    //Empty all FIFOs
    emptyRxTxFifo(spiHw);

    spiHw->TX_thres_reg0 = TX_THRES_REG_RST_VALUE;
    spiHw->RX_thres_reg0 = RX_THRES_REG_RST_VALUE;

    //Disable all interrupts
    /* @req SWS_Spi_00151 */
    Spi_Hw_DisableInterrupt(hwUnit);

#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
    switch (hwUnit) {
#if (SPI_USE_HW_UNIT_0 == STD_ON )
    case 0:
        ISR_INSTALL_ISR2("SPI_0",Spi_Isr_0, IRQ_SPI_0, SPI_ISR_PRIORITY, 0);
        break;
#endif
#if (SPI_USE_HW_UNIT_1 == STD_ON )
    case 1:
        ISR_INSTALL_ISR2("SPI_1",Spi_Isr_1, IRQ_SPI_1, SPI_ISR_PRIORITY, 0);
        break;
#endif
    default:
        break;
    }
#endif
}

void Spi_Hw_DeInitController(uint32 hwUnit ) {
    vuint32_t intr_status_wtc;
    Spi_HwRegType *spiHw = GET_SPI_HW_PTR(hwUnit);

    //Empty the FIFO.
    emptyRxTxFifo(GET_SPI_HW_PTR(hwUnit));

    spiHw->Config_reg0             = CONFIG_REG_RST_VALUE;
    //write to clear
    intr_status_wtc = spiHw->Intr_status_reg0;
    spiHw->Intr_status_reg0 = intr_status_wtc;

    spiHw->Intrpt_en_reg0          = INTRPT_EN_REG_RST_VALUE;
    spiHw->Intrpt_dis_reg0         = INTRPT_DIS_REG_RST_VALUE;
    spiHw->Delay_reg0              = DELAY_REG_RST_VALUE;
    spiHw->Slave_Idle_count_reg0   = SLAVE_IDLE_COUNT_REG_RST_VALUE;
    spiHw->TX_thres_reg0           = TX_THRES_REG_RST_VALUE;
    spiHw->RX_thres_reg0           = RX_THRES_REG_RST_VALUE;
    spiHw->En_reg0                 = EN_REG_RST_VALUE;
}



static void emptyRxFifo(const Spi_HwRegType *hwPtr)
{
    vuint32_t dummyRead;

    while (0u != (hwPtr->Intr_status_reg0 & RX_FIFO_NOT_EMPTY_MASK)) {
        dummyRead = hwPtr->Rx_data_reg0;

        /* dummyRead is not used */
        (void)dummyRead;
    }
}

static void emptyTxFifo(Spi_HwRegType *hwPtr)
{
    // Check if the tx fifo is empty. If its not it must be flushed.
    if (0u == ((hwPtr->Intr_status_reg0 & TX_FIFO_NOT_EMPTY_MASK) >> 2u)) {

        hwPtr->En_reg0 = 1;
        hwPtr->Config_reg0 |= ((uint32)1u<<16u);
        while(0u == ((hwPtr->Intr_status_reg0 & TX_FIFO_NOT_EMPTY_MASK) >> 2u)) {;/*do nothing*/}
        hwPtr->En_reg0 = 0;

    }
}

static void emptyRxTxFifo(Spi_HwRegType *hwPtr)
{
    //emptyTxFifo must be done first.
    emptyTxFifo(hwPtr);
    emptyRxFifo(hwPtr);
}

static boolean spi_isTxFifoEmpty(const Spi_HwRegType *hwPtr )
{
    return (boolean)(((hwPtr->Intr_status_reg0 & (uint32)TX_FIFO_NOT_EMPTY_MASK) >> 2u) != 0u);
}



static sint32 checkJobTotalLength(const Spi_UnitType *uPtr, uint16_t *numberOfChannels)
{
    Spi_NumberOfDataType totalLength = 0;
    Spi_NumberOfDataType chnLength = 0;
    sint32 retval = SPIE_OK;
    uint16_t n;
    uint16_t nbrOfChan = Spi_Internal_GetNbrChnInJob(uPtr);

    for(n = 0; n < nbrOfChan; n++) {

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

void Spi_Hw_EndTransmission(Spi_UnitType *uPtr)
{
    (void)uPtr;  /*lint !e920 STANDARDIZED INTERFACE */
}

boolean Spi_Hw_IsTransmissionDone( uint32 hwUnit )
{
    return spi_isTxFifoEmpty(GET_SPI_HW_PTR(hwUnit));
}

void Spi_Hw_Halt( uint32 hwUnit ) {
    Spi_HwRegType *hwPtr = GET_SPI_HW_PTR(hwUnit);
    hwPtr->En_reg0 = 0;
}

void Spi_Hw_DisableInterrupt( uint32 hwUnit ) {
    Spi_HwRegType *hwPtr = GET_SPI_HW_PTR(hwUnit);
    uint32 intr_status_wtc = hwPtr->Intr_status_reg0;
    (void)intr_status_wtc;

    hwPtr->Intrpt_dis_reg0 = MASK_INTERRUPT_DISABLE;
}
void Spi_Hw_EnableInterrupt( uint32 hwUnit ) {
    Spi_HwRegType *hwPtr = GET_SPI_HW_PTR(hwUnit);
    hwPtr->Intrpt_en_reg0 = TX_FIFO_NO_FULL;
}
