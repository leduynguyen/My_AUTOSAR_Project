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

/** @tagSettings DEFAULT_ARCHITECTURE=ZYNQ */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#include "Lin.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "SchM_Lin.h"
#include "isr.h"
#include "irq.h"
#include "zynq.h"
#if (LIN_REPORT_WAKEUP_SOURCE == STD_ON)
/** @req SWS_Lin_00042 */
#include "EcuM_Cbk.h"
#endif

/** General requirements tagging */
/* @req SWS_Lin_00103 Only precompile */
/* @req SWS_Lin_00013 The configuration is stored as constant data */
/* @req SWS_Lin_00015 In the input argument of Lin_SendFrame the PID is associated with a length*/
/* @req SWS_Lin_00156 Only the required interrupts are enabled*/
/* @req SWS_Lin_00017 The driver can send headers*/
/* @req SWS_Lin_00018 The driver can transmit and receive response frames*/
/* @req SWS_Lin_00019 The driver can calculate classic and enhanced checksum*/
/* @!req SWS_Lin_00184 ambiguous requirement, ie Lin_Wakeup will return DET error(as specified) if called when channel status is LIN_OPERATIONAL */
/* @req SWS_Lin_00207 Are defined within this file*/
/* @req SWS_Lin_00224 Validation is done by the configuration tool*/
/* @req SWS_Lin_00235 Implemented optional interfaces are Det_ReportError and EcuM_CheckWakeup*/
/* @req SWS_Lin_00237 All detected DET errors will call the error tracer and return*/
/* @req SWS_Lin_00027 The driver can initiate transmission and will check transmission of previous byte*/
/* @req SWS_Lin_00028 While receiving data the driver does not block*/
/* @req SWS_Lin_00029 This Lin driver implementation is specific for the Zynq uart controller */
/* @req SWS_Lin_00045 There are two uart controllers of the same type, each with one channel*/
/* @req SWS_Lin_00005 The driver is implemented to support the LIN 2.1 protcol */
/* @!req SWS_Lin_00032 Not supported by hardware */
/* @req SWS_Lin_00206 The lin driver does not provid any callback functions*/
/* @!req SWS_Lin_00234 Only callback to EcuM_SetWakeupEvent is supported by the module */
/* @req SWS_Lin_00063 Hardware uart used */

#define LIN_MAX_MSG_LENGTH 8
#define LIN_PRIO 3

/* Baud dividers min/max values */
#define UART_BDIV_MIN      4
#define UART_BDIV_MAX      255
#define UART_CD_MAX        65535

/* Register bit masks */
#define UART_MR_CLK_NO_PRESCALE    0x00000000uL  /* No pre-scalar selection */
#define UART_MR_CLK_PRESCALE       0x00000001uL  /* Pre-scalar selection */

#define UART_MR_PARITY_NONE        0x00000020uL  /* No parity mode */

#define UART_CR_TX_DIS     0x00000020uL  /* TX disabled. */
#define UART_CR_TX_EN      0x00000010uL  /* TX enabled */
#define UART_CR_RX_DIS     0x00000008uL  /* RX disabled. */
#define UART_CR_RX_EN      0x00000004uL  /* RX enabled */
#define UART_CR_TXRST      0x00000002uL  /* TX logic reset */
#define UART_CR_RXRST      0x00000001uL  /* RX logic reset */
#define UART_CR_RST_TO     0x00000040uL  /* Restart Timeout Counter */

#define UART_IXR_TOUT      0x00000100uL /* RX Timeout error interrupt */
#define UART_IXR_FRAMING   0x00000040uL /* Framing error interrupt */
#define UART_IXR_RXTRIG    0x00000001uL /* RX FIFO trigger interrupt */

#define MAX_WAIT_CYCLES (uint32)100000uL

#define BAUD_RATE_2K    2000uL

#define BREAK_FIELD_DATA    (uint32)0uL
#define WAKEUP_FIELD_DATA   (uint32)0uL

#define PID_MASTER_REQ (uint8)0x3Cu

typedef struct {
    uint32 cd;
    uint32 bdiv;
    uint8  div8;
} BaudrateDivisorType;

/*lint --e{751} Used to create array and index it.*/
typedef enum {
    NORMAL_BAUDRATE_INDEX=0,
    BREAK_BAUDRATE_INDEX,
    NR_OF_BAUDRATE_SETUPS
}BaudrateSetupType;

typedef enum {
    IDLE = 0,
    SEND_SYNC,
    SEND_PID,
    PID_TRANSMITTED,
    TX_DATA,
    TX_CHECKSUM,
    TX_CHECKSUM_VALIDATION,
    RX_DATA,
    RX_CHECKSUM,
    WAKEUP,
    WAKEUP_DETECT,
    WAKEUP_DETECT_INIT,
}Lin_IsrStateType;

/* Reset -> LIN_UNINIT: After reset, the Lin module shall set its state to LIN_UNINIT. */
/* @req SWS_Lin_00145 */
static Lin_DriverStatusType Lin_DrivStat = LIN_UNINIT;

static Lin_StatusType Lin_ChanStat[LIN_CONTROLLER_CNT];
static boolean Lin_SleepPending[LIN_CONTROLLER_CNT];

static const Lin_ConfigType* Lin_CfgPtr = NULL;

static Lin_FramePidType Lin_Pid[LIN_CONTROLLER_CNT];
static Lin_FrameCsModelType Lin_Cs[LIN_CONTROLLER_CNT];

/* static buffers, holds one frame at a time */
static uint8 Lin_BufTxRx[LIN_CONTROLLER_CNT][LIN_MAX_MSG_LENGTH];

static uint8  Lin_CsTx[LIN_CONTROLLER_CNT];
static uint8  Lin_TxRxSize[LIN_CONTROLLER_CNT];
static uint32 Lin_RxTimeoutValue[LIN_CONTROLLER_CNT];

static boolean Lin_WakeupSet[LIN_CONTROLLER_CNT];

static BaudrateDivisorType Lin_BaudrateSendWakeup = {0};
static BaudrateDivisorType Lin_BaudrateReceiveWakeup = {0};
static BaudrateDivisorType Lin_BaudrateDivisors[LIN_CONTROLLER_CNT][NR_OF_BAUDRATE_SETUPS];

static uint8 Lin_LastTxData[LIN_CONTROLLER_CNT] = {0};
static Lin_IsrStateType Lin_IsrState[LIN_CONTROLLER_CNT];
static boolean Lin_IsTransmitting[LIN_CONTROLLER_CNT];
static boolean Lin_ChanSlvToSlv[LIN_CONTROLLER_CNT];

/* Development error macros. */
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(LIN_MODULE_ID,0,_api,_err); \
          return; \
        }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(LIN_MODULE_ID,0,_api,_err); \
          return (_rv); \
        }

#define VALIDATE_PTR_W_RV(_exp,_rv ) \
        if( !(_exp) ) { \
          return (_rv); \
        }
#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_W_RV(_exp,_api,_err,_rv )
#define VALIDATE_PTR_W_RV(_exp,_rv )
#endif

/* Private prototypes */
static void Lin_Internal_Interrupt(uint8 hwId);

/**
 * Returns hardware channel address
 * @param ch
 * @return
 */
static struct UART_reg * getUARTPointerFromChannel(uint8 ch){
    struct UART_reg * regPnt;

    if (Lin_CfgPtr->LinChannelConfig[ch].LinChannelId == 0u){
        regPnt = &UART0_REG; /*lint !e923 Must assign address to hw register*/
    }
    else {
        regPnt = &UART1_REG; /*lint !e923 Must assign address to hw register*/
    }

    return regPnt;
}

/**
 * Disable the transmission and reception of data
 * @param ch
 */
static void disableTXRX(uint8 ch){
    struct UART_reg * uartPtr = getUARTPointerFromChannel(ch);

    uint32 regVal = uartPtr->Control_reg0;
    uartPtr->Control_reg0 = regVal | UART_CR_TX_DIS | UART_CR_RX_DIS;
}

/**
 * Enables the transmission and reception of data
 * @param ch
 */
static void enableTXRX(uint8 ch){
    struct UART_reg * uartPtr = getUARTPointerFromChannel(ch);

    uint32 regVal = uartPtr->Control_reg0;
    regVal &= ~(UART_CR_TX_DIS | UART_CR_RX_DIS);
    regVal |= UART_CR_TX_EN | UART_CR_RX_EN;
    uartPtr->Control_reg0 = regVal;
}

/**
 * Used to flush rx/tx data
 * @param ch
 */
static void resetTXRX(uint8 ch){
    struct UART_reg * uartPtr = getUARTPointerFromChannel(ch);

    uint32 regVal = uartPtr->Control_reg0;
    uartPtr->Control_reg0 = regVal |  UART_CR_TXRST | UART_CR_RXRST;
}


/**
 * This function is used instead of "while". It returns when the condition is cleared or
 * when n reach MAX_WAIT_CYCLES.
 * @param regBaseAddr
 * @param mask
 * @param retCondition
 * @return
 */
static Std_ReturnType waitWhileBusy(volatile const uint32 *regBaseAddr, uint32 mask, boolean retCondition) {
    Std_ReturnType retval = E_NOT_OK;
    boolean condition;
    uint32 n;

    VALIDATE_PTR_W_RV((NULL != regBaseAddr), E_NOT_OK);

    for (n = 0; n < MAX_WAIT_CYCLES ; n++) {
        condition = ((*regBaseAddr & mask) == mask) ? TRUE : FALSE;

        //Shall remain in the loop while the condition is false.
        if(retCondition == condition) {
            retval = E_OK;
            break;
        }
    }
    return retval;
}

/**
 * Resets tx/rx and wait for status bits to clear.
 * @param Channel
 * @return
 */
static Std_ReturnType resetTxRxWaitUntilReady(uint8 Channel) {
    const struct UART_reg * uartPtr = getUARTPointerFromChannel(Channel);
    Std_ReturnType retval;

    resetTXRX(Channel);

    retval = waitWhileBusy(&uartPtr->Control_reg0, (UART_CR_TXRST | UART_CR_RXRST), FALSE);

    return retval;
}

/**
 * Aborts an ongoing transmission/reception. Is used in case of error.
 * @param ch
 * @param timeoutErr
 */
static void abortOngoingTxRx(uint8 ch, boolean timeoutErr, uint8 nbrRxTxData) {
    struct UART_reg * uartPtr = getUARTPointerFromChannel(ch);

    uartPtr->Intrpt_dis_reg0 = UART_IXR_FRAMING | UART_IXR_TOUT | UART_IXR_RXTRIG;

    switch(Lin_IsrState[ch]) {
        case SEND_SYNC:
        case SEND_PID:
        case PID_TRANSMITTED:
            Lin_ChanStat[ch] = LIN_TX_HEADER_ERROR;
            break;
        case TX_DATA:
        case TX_CHECKSUM:
                Lin_ChanStat[ch] = LIN_TX_ERROR;
            break;
        case RX_DATA:
        case RX_CHECKSUM:
            if (timeoutErr && (nbrRxTxData == 0)) {
                Lin_ChanStat[ch] = LIN_RX_NO_RESPONSE;
            } else {
                Lin_ChanStat[ch] = LIN_RX_ERROR;
            }
            break;
        default:
            break;
    }


    /* If wake-up detection is supported by configuration parameter LinChannelWakeupSupport,
     * then the function Lin_GoToSleep shall enable the wake-up detection,
     * even in case of an erroneous transmission of the go-to-sleep-command.
     */
    if ((Lin_SleepPending[ch] == TRUE) && (Lin_CfgPtr->LinChannelConfig[ch].LinChannelWakeUpSupport == TRUE)) {
        /** @req SWS_Lin_00220 */
        Lin_IsrState[ch] = WAKEUP_DETECT_INIT;
        Lin_SleepPending[ch] = FALSE;
    } else {
        Lin_IsrState[ch] = IDLE;
    }


}



/**
 * calculateBaudrateDivisors - Calculate baud rate divisors
 *
 * @param Clock UART module input clock
 * @param Baudrate Desired baud rate
 * @param rbdiv BDIV value (return value)
 * @param rcd CD value (return value)
 * @param div8 Value for clk_sel bit in mod (return value)
 * @return baud rate, requested baud when possible, or actual baud when there
 *      was too much error, zero if no valid divisors are found.
 */
static Std_ReturnType calculateBaudrateDivisors(uint32 Clock,
                uint16 BaudRate, uint32 *rbdiv, uint32 *rcd, uint8 *div8)
 {
    uint32 cd;
    uint32 bdiv;
    uint16 calc_baud;
    uint16 bauderror;
    uint16 besterror = 0xFFFF;

    VALIDATE_W_RV( (BaudRate != 0uL), LIN_INIT_SERVICE_ID, LIN_E_INVALID_CONFIG, E_NOT_OK );
    VALIDATE_W_RV( (rbdiv != NULL)  , LIN_INIT_SERVICE_ID, LIN_E_INVALID_POINTER, E_NOT_OK );
    VALIDATE_W_RV( (rcd != NULL)    , LIN_INIT_SERVICE_ID, LIN_E_INVALID_POINTER, E_NOT_OK );
    VALIDATE_W_RV( (div8 != NULL)   , LIN_INIT_SERVICE_ID, LIN_E_INVALID_POINTER, E_NOT_OK );

    if (BaudRate < (Clock / ((UART_BDIV_MAX + 1) * UART_CD_MAX))) {
        *div8 = 1;
        Clock /= 8;
    }
    else {
        *div8 = 0;
    }

    for (bdiv = UART_BDIV_MIN; bdiv <= UART_BDIV_MAX; bdiv++) {

        cd = (Clock + ((BaudRate * (bdiv + 1)) / 2)) / (BaudRate * (bdiv + 1));
        if ((cd > 0) && (cd <= UART_CD_MAX)) {

            calc_baud = (uint16)(Clock / (cd * (bdiv + 1)));

            if (BaudRate > calc_baud){
                bauderror = BaudRate - calc_baud;
            }
            else {
                bauderror = calc_baud - BaudRate;
            }

            if (besterror > bauderror) {
                *rbdiv = bdiv;
                *rcd = cd;
            }
        }
    }

    return E_OK;
}

/**
 * Set baudrate divisors based
 * @param ch
 * @param bdiv
 * @param cd
 * @param div8
 */
static void setBaudrateFromDivisors(uint8 ch, uint32 bdiv, uint32 cd, uint8 div8){
    struct UART_reg * uartPtr = getUARTPointerFromChannel(ch);
    Std_ReturnType retval;
    uint32 regVal = uartPtr->mode_reg0;

    if (div8>0){
        regVal |= UART_MR_CLK_PRESCALE;
    }
    else{
        regVal &= ~UART_MR_CLK_NO_PRESCALE;
    }
    disableTXRX(ch);
    uartPtr->mode_reg0 = regVal;
    uartPtr->Baud_rate_gen_reg0 = cd;
    uartPtr->Baud_rate_divider_reg0 = bdiv;
    resetTXRX(ch);

    retval = resetTxRxWaitUntilReady(ch);

    if (E_OK == retval) {
        enableTXRX(ch);
    }
}

/**
 * Set the mode register of the Zynq Uart
 * @param ch
 */
static void configureFrameSetup( uint8 ch ) {
    struct UART_reg * uartPtr = getUARTPointerFromChannel(ch);

    uartPtr->mode_reg0 = UART_MR_PARITY_NONE; /* Rest is initialized at default, 0 */
}

/**
 * Setup peripheral to send a break field. This is doen by changing the baudrate
 * @param ch
 */
static void sendBreakField(uint8 ch) {
    /* To be able to set low level for at least 13 bits we change to a slower baudrate
     * We will use 9 bits (1 start and 8 data bits) to represent 13 bits so
     * the new baudrate is 9/13*oldBaudrate > 8/13*oldBaudrate */

    setBaudrateFromDivisors(ch,
            Lin_BaudrateDivisors[ch][BREAK_BAUDRATE_INDEX].bdiv,
            Lin_BaudrateDivisors[ch][BREAK_BAUDRATE_INDEX].cd,
            Lin_BaudrateDivisors[ch][BREAK_BAUDRATE_INDEX].div8);

    struct UART_reg * uartPtr = getUARTPointerFromChannel(ch);

    uartPtr->Rcvr_FIFO_trigger_level0 = 0x01;
    uartPtr->Intrpt_en_reg0 = UART_IXR_FRAMING | UART_IXR_RXTRIG;
    uartPtr->Control_reg0 |= UART_CR_RX_EN;

    uartPtr->TX_RX_FIFO0 = BREAK_FIELD_DATA;
    Lin_LastTxData[ch]       = BREAK_FIELD_DATA;

    Lin_IsTransmitting[ch] = TRUE;
    Lin_IsrState[ch] = SEND_SYNC;
}

/**
 * Sends a wakeup pulse on the channel
 * @param ch
 */
static void sendWakeup(uint8 ch) {

    struct UART_reg * uartPtr = getUARTPointerFromChannel(ch);

    uartPtr->Rcvr_FIFO_trigger_level0 = 0x01;
    uartPtr->Intrpt_en_reg0 = UART_IXR_FRAMING | UART_IXR_RXTRIG;
    uartPtr->Control_reg0 |= UART_CR_RX_EN;

    uartPtr->TX_RX_FIFO0 = WAKEUP_FIELD_DATA;
    Lin_LastTxData[ch]       = WAKEUP_FIELD_DATA;

    Lin_IsTransmitting[ch] = TRUE;
    Lin_IsrState[ch] = WAKEUP;
}

/**
 * Setup the peripheral to monitor the bus for a wakeup pulse
 * @param ch
 */
static void enableWakeupDetection(uint8 ch) {
    struct UART_reg * uartPtr = getUARTPointerFromChannel(ch);

    setBaudrateFromDivisors(ch,
            Lin_BaudrateReceiveWakeup.bdiv,
            Lin_BaudrateReceiveWakeup.cd,
            Lin_BaudrateReceiveWakeup.div8);

    uartPtr->Rcvr_FIFO_trigger_level0 = 0x01;
    uartPtr->Intrpt_en_reg0 = UART_IXR_FRAMING | UART_IXR_RXTRIG;
    uartPtr->Control_reg0 |= UART_CR_RX_EN;

    Lin_WakeupSet[ch] = FALSE;
    Lin_IsTransmitting[ch] = FALSE;
    Lin_IsrState[ch] = WAKEUP_DETECT;
}

/**
 * Disables wakeup detection
 * @param ch
 */
static void disableWakeupDetection(uint8 ch) {
    struct UART_reg * uartPtr = getUARTPointerFromChannel(ch);

    uartPtr->Control_reg0 |= UART_CR_RX_DIS;
    uartPtr->Intrpt_dis_reg0 = UART_IXR_FRAMING | UART_IXR_TOUT | UART_IXR_RXTRIG;

    Lin_WakeupSet[ch] = FALSE;
    Lin_IsrState[ch] = IDLE;
}

/**
 * Calculates the checksum
 * @param DataBytes
 * @param nrOfBytes
 * @param pid
 * @param checksumModel
 * @return
 */
static uint8 calculateChecksum(const uint8* DataBytes, uint8 nrOfBytes, uint8 pid, Lin_FrameCsModelType checksumModel){
    uint16 checksum = 0;
    uint8 endChecksum;
    uint8 i;

    for(i=0;i<nrOfBytes;i++){
        checksum = checksum + DataBytes[i];
        if (checksum >= 256u) {
            checksum = checksum - 255u;
        }
    }

    if(checksumModel == LIN_ENHANCED_CS){
        checksum = checksum + pid;
        if (checksum >= 256u) {
            checksum = checksum - 255u;
        }
    }

    endChecksum = (uint8)checksum;

    return ~endChecksum;
}

/**
 * Handles the UART interrupt routine
 * @param hwId
 */
/** @req SWS_Lin_00239 Header transmission is aborted*/
/** @req SWS_Lin_00192 */
/** @req SWS_Lin_00240 */
static void Lin_Internal_Interrupt(uint8 hwId) {
    static uint8 byteNr[LIN_CONTROLLER_CNT] = {0};
    static boolean timeoutErrEnable[LIN_CONTROLLER_CNT] = {0};
    static boolean txCsSent[LIN_CONTROLLER_CNT] = {0};

    uint8 ch = Lin_CfgPtr->Lin_HwId2ChannelMap[hwId];
    struct UART_reg * uartPtr = getUARTPointerFromChannel(ch);
    boolean timeoutErr;
    boolean frameErr;
    uint32 intStatReg;
    uint8 rxData;
    uint8 cs;

    intStatReg = uartPtr->Chnl_int_sts_reg0;
    rxData     = (uint8)uartPtr->TX_RX_FIFO0;

    timeoutErr = ((UART_IXR_TOUT == (intStatReg & UART_IXR_TOUT)) && timeoutErrEnable[ch]) ? TRUE : FALSE;
    frameErr = (UART_IXR_FRAMING == (intStatReg & UART_IXR_FRAMING)) ? TRUE : FALSE;

    if ((Lin_IsTransmitting[ch] && (rxData != Lin_LastTxData[ch])) ||
        (frameErr && (WAKEUP_DETECT != Lin_IsrState[ch]))   || /* Frame error ignored when reception of wakeup is enabled */
        timeoutErr)
    {
        abortOngoingTxRx(ch, timeoutErr, byteNr[ch]);
    }

    switch (Lin_IsrState[ch]) {
        case WAKEUP_DETECT_INIT:
            /** @req SWS_Lin_00037 */
            /** @req SWS_Lin_00220 */
            enableWakeupDetection(ch);
            Lin_IsrState[ch] = WAKEUP_DETECT;
            break;
        case WAKEUP_DETECT:
            if (WAKEUP_FIELD_DATA == rxData) {
                Lin_WakeupSet[ch] = TRUE;

#if (LIN_REPORT_WAKEUP_SOURCE == STD_ON)
                /* @req SWS_Lin_00176 */
                if (Lin_CfgPtr->LinChannelConfig[ch].LinChannelEcuWakeUpDefined) {
                    EcuM_CheckWakeup(Lin_CfgPtr->LinChannelConfig[ch].LinChannelEcuMWakeUpSource);
                }
#endif
            }
            break;
        case SEND_SYNC:
            byteNr[ch] = 0;
            Lin_IsTransmitting[ch] = TRUE;
            timeoutErrEnable[ch] = FALSE;
            txCsSent[ch] = FALSE;

            setBaudrateFromDivisors(ch,
                Lin_BaudrateDivisors[ch][NORMAL_BAUDRATE_INDEX].bdiv,
                Lin_BaudrateDivisors[ch][NORMAL_BAUDRATE_INDEX].cd,
                Lin_BaudrateDivisors[ch][NORMAL_BAUDRATE_INDEX].div8);

            /* Set data for Sync field transmission */
            uartPtr->TX_RX_FIFO0 = 0x55;
            Lin_LastTxData[ch] = 0x55;
            Lin_IsrState[ch] = SEND_PID;
            break;

        case SEND_PID:
            /* Set data for PID transmission */
            uartPtr->TX_RX_FIFO0 = Lin_Pid[ch];
            Lin_LastTxData[ch] = Lin_Pid[ch];

            Lin_IsrState[ch] = PID_TRANSMITTED;
            break;

        case PID_TRANSMITTED:
            /* PID transmitted, determine if we are going to receive or transmit data */
            if (LIN_RX_BUSY == Lin_ChanStat[ch]) {
                Lin_IsTransmitting[ch] = FALSE;
                /* Set timeout */
                uartPtr->Rcvr_timeout_reg0 = Lin_RxTimeoutValue[ch] >> 2; /* The lower two bits are always 0 */
                uartPtr->Intrpt_en_reg0 |= UART_IXR_TOUT;
                uartPtr->Control_reg0 |= UART_CR_RST_TO;
                timeoutErrEnable[ch] = TRUE;

                Lin_IsrState[ch] = RX_DATA;
                break;
            } else if (Lin_ChanSlvToSlv[ch]) {    
                Lin_IsrState[ch] = IDLE;
                Lin_ChanSlvToSlv[ch] = FALSE;
                Lin_ChanStat[ch] = LIN_TX_OK;
            } else {
                Lin_IsrState[ch] = TX_DATA;
            }
            //lint -fallthrough for TX_DATA
        case TX_DATA:
            uartPtr->TX_RX_FIFO0 = Lin_BufTxRx[ch][byteNr[ch]];
            Lin_LastTxData[ch] = Lin_BufTxRx[ch][byteNr[ch]];

            byteNr[ch]++;

            if (Lin_TxRxSize[ch] <= byteNr[ch]) {
                Lin_IsrState[ch] = TX_CHECKSUM;
            }
            break;

        case TX_CHECKSUM:
            uartPtr->TX_RX_FIFO0 = Lin_CsTx[ch];
            Lin_LastTxData[ch] = Lin_CsTx[ch];

            if (Lin_SleepPending[ch] && Lin_CfgPtr->LinChannelConfig[ch].LinChannelWakeUpSupport) {
                Lin_IsrState[ch] = WAKEUP_DETECT_INIT;
            } else {
                Lin_IsrState[ch] = TX_CHECKSUM_VALIDATION;
                txCsSent[ch] = TRUE;
            }
            Lin_SleepPending[ch] = FALSE;
            break;
        case RX_DATA:
            /** @req SWS_Lin_00060 */
            Lin_BufTxRx[ch][byteNr[ch]] = rxData;
            byteNr[ch]++;

            if (Lin_TxRxSize[ch] <= byteNr[ch]) {
                Lin_IsrState[ch] = RX_CHECKSUM;
            }
            break;
        case RX_CHECKSUM:
            /* expected cs */
            cs = calculateChecksum(Lin_BufTxRx[ch], Lin_TxRxSize[ch], Lin_Pid[ch], Lin_Cs[ch]);

            if (cs == rxData) {
                Lin_ChanStat[ch] = LIN_RX_OK;
                Lin_IsrState[ch] = IDLE;
            } else {
                abortOngoingTxRx(ch, FALSE, byteNr[ch]);
            }
            timeoutErrEnable[ch] = FALSE;
            //lint -fallthrough
        case WAKEUP:
            // If baudrate was reconfigured to transmit the wakeup there is no need to change it back here. It will
            // be changed the sendBreak function anyway.
            //lint -fallthrough
        case TX_CHECKSUM_VALIDATION:
            if (txCsSent[ch]) {
                Lin_ChanStat[ch] = LIN_TX_OK;
            }
            //lint -fallthrough
        case IDLE:
            //lint -fallthrough
        default:
            Lin_IsrState[ch] = IDLE;
            timeoutErrEnable[ch] = FALSE;
            Lin_ChanSlvToSlv[ch] = FALSE;
            txCsSent[ch] = FALSE;
            uartPtr->Control_reg0 |= UART_CR_RX_DIS;
            uartPtr->Intrpt_dis_reg0 = UART_IXR_FRAMING | UART_IXR_TOUT | UART_IXR_RXTRIG;
            break;
    }

    /* Clear interrupt flags */
    /** @req SWS_Lin_00157 */
    uartPtr->Chnl_int_sts_reg0 = 0x0FFF;
}


#ifdef LIN_CHANNEL_0_USED
ISR(LinInterruptUSART0); /* Prototype */
ISR(LinInterruptUSART0){ Lin_Internal_Interrupt(0u);}
#endif
#ifdef LIN_CHANNEL_1_USED
ISR(LinInterruptUSART1); /* Prototype */
ISR(LinInterruptUSART1){ Lin_Internal_Interrupt(1u);}
#endif

/**
 * Initializes the module
 * @param Config
 */
/** @req SWS_Lin_00006 */
/** @req SWS_Lin_00084 */
/** @req SWS_Lin_00150 */
void Lin_Init(const Lin_ConfigType* Config) {
    struct UART_reg * uartPtr;
    Std_ReturnType retval;
    uint32 cd = 0;
    uint32 bdiv = 0;
    uint8  div8 = 0;
    uint32 breakBaud;

    /** @req SWS_Lin_00105 **/
    VALIDATE( (Lin_DrivStat == LIN_UNINIT), LIN_INIT_SERVICE_ID, LIN_E_STATE_TRANSITION );
    /** @req SWS_Lin_00099 **/
    /** @req SWS_Lin_00216 **/
    VALIDATE( (Config!=NULL), LIN_INIT_SERVICE_ID, LIN_E_INVALID_POINTER );

    Lin_CfgPtr = Config;

    for (uint8 i = 0; i < LIN_CONTROLLER_CNT; i++) {
        Lin_TxRxSize[i] = 0;
        Lin_RxTimeoutValue[i] = 0;
        Lin_IsrState[i] = IDLE;
        Lin_WakeupSet[i] = FALSE;
        Lin_SleepPending[i] = FALSE;
        Lin_ChanSlvToSlv[i] = FALSE;
    }

    /* Install the interrupts */
    /* @req SWS_Lin_00155 */
#ifdef LIN_CHANNEL_0_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptUSART0, (IrqType)(IRQ_UART_0),LIN_PRIO, 0);
#endif
#ifdef LIN_CHANNEL_1_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptUSART1, (IrqType)(IRQ_UART_1),LIN_PRIO, 0);
#endif


    // Calculate a baudrate setup for the lin wakeup pulse.
    // This will be used as baudrate if the the configured is less than 2000.
    retval = calculateBaudrateDivisors(MCU_ARC_CLOCK_UART_0_FREQUENCY,
                10000uL, &Lin_BaudrateSendWakeup.bdiv, &Lin_BaudrateSendWakeup.cd, &Lin_BaudrateSendWakeup.div8);
    if (E_NOT_OK == retval) {
        return;
    }


    retval = calculateBaudrateDivisors(MCU_ARC_CLOCK_UART_0_FREQUENCY,
                56000uL, &Lin_BaudrateReceiveWakeup.bdiv, &Lin_BaudrateReceiveWakeup.cd, &Lin_BaudrateReceiveWakeup.div8);
    if (E_NOT_OK == retval) {
        return;
    }

    /** @req SWS_Lin_00190 */
    for (uint8 Channel = 0; Channel < LIN_CONTROLLER_CNT; Channel++) {

        retval = calculateBaudrateDivisors(MCU_ARC_CLOCK_UART_0_FREQUENCY,
                (uint32)Lin_CfgPtr->LinChannelConfig[Channel].LinChannelBaudRate, &bdiv, &cd, &div8); /*lint !e934 Only used in this function  */
        if (E_NOT_OK == retval) {
            return;
        }

        Lin_BaudrateDivisors[Channel][NORMAL_BAUDRATE_INDEX].bdiv = bdiv;
        Lin_BaudrateDivisors[Channel][NORMAL_BAUDRATE_INDEX].cd = cd;
        Lin_BaudrateDivisors[Channel][NORMAL_BAUDRATE_INDEX].div8 = div8;

        /* To be able to set low level for at least 13 bits we change to a slower baudrate
             * We will use 9 bits (1 start and 8 data bits) to represent 13 bits so
             * the new baudrate is 9/13*oldBaudrate > 8/13*oldBaudrate */

        breakBaud = ((uint32)Lin_CfgPtr->LinChannelConfig[Channel].LinChannelBaudRate * 7uL) / 13uL;
        retval = calculateBaudrateDivisors(MCU_ARC_CLOCK_UART_0_FREQUENCY,
                (uint16)breakBaud, &bdiv, &cd, &div8); /*lint !e934 Only used in this function  */
        if (E_NOT_OK == retval) {
            return;
        }

        Lin_BaudrateDivisors[Channel][BREAK_BAUDRATE_INDEX].bdiv = bdiv;
        Lin_BaudrateDivisors[Channel][BREAK_BAUDRATE_INDEX].cd = cd;
        Lin_BaudrateDivisors[Channel][BREAK_BAUDRATE_INDEX].div8 = div8;

        /* @req SWS_Lin_00008 */
        configureFrameSetup(Channel);
        setBaudrateFromDivisors(Channel,  Lin_BaudrateDivisors[Channel][NORMAL_BAUDRATE_INDEX].bdiv,Lin_BaudrateDivisors[Channel][NORMAL_BAUDRATE_INDEX].cd, Lin_BaudrateDivisors[Channel][NORMAL_BAUDRATE_INDEX].div8);

        // clear any pending status flags
        uartPtr = getUARTPointerFromChannel(Channel);
        uartPtr->Chnl_int_sts_reg0 = 0x0FFF;

        /** @req SWS_Lin_00171 */
        Lin_ChanStat[Channel] = LIN_OPERATIONAL;
    }

    /** @req SWS_Lin_00146 */
    /* LIN_UNINIT -> LIN_INIT: The Lin module shall transition from LIN_UNINIT
     * to LIN_INIT when the function Lin_Init is called. */
    Lin_DrivStat = LIN_INIT;
}

/**
 * De-initializes the module
 */
void Lin_Arc_DeInit(void){
    struct UART_reg * uartPtr;
    uint32 status;
    uint8 ch;

    VALIDATE( (Lin_DrivStat != LIN_UNINIT), LIN_ARC_DEINIT_SERVICE_ID, LIN_E_UNINIT);

    Lin_DrivStat = LIN_UNINIT;

    for (ch = 0; ch < LIN_CONTROLLER_CNT; ch++) {

        uartPtr = getUARTPointerFromChannel(ch);

        /* Disable interrupts */
        status = uartPtr->Intrpt_mask_reg0;
        uartPtr->Intrpt_dis_reg0 = status;

        /* Disable the TX and RX */
        uartPtr->Control_reg0 = UART_CR_TX_DIS | UART_CR_RX_DIS;
    }

}

/** @req SWS_Lin_00191 */
/**
 * Sends the header on the bus and depending of direction it sets or listens to response data
 * @param Channel
 * @param PduInfoPtr
 * @return
 */
Std_ReturnType Lin_SendFrame(uint8 Channel, Lin_PduType* PduInfoPtr) /*lint -e{818} Follows AUTOSAR API spec */
{
    Std_ReturnType retval;
    uint8 i;

    /** @req SWS_Lin_00195 */
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (Lin_DrivStat != LIN_UNINIT), LIN_SEND_FRAME_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);

    /** @req SWS_Lin_00197 */
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_SEND_FRAME_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);
    /* Send header is used to wake the net in this implementation(no actual header is sent */
    /** @req SWS_Lin_00199 */
    /** @req SWS_Lin_00213 */
    VALIDATE_W_RV( (Lin_ChanStat[Channel] != LIN_CH_SLEEP), LIN_SEND_FRAME_SERVICE_ID, LIN_E_STATE_TRANSITION, E_NOT_OK);
    /** @req SWS_Lin_00198 */
    /** @req SWS_Lin_00249 **/
    VALIDATE_W_RV( (PduInfoPtr != NULL), LIN_SEND_FRAME_SERVICE_ID, LIN_E_PARAM_POINTER, E_NOT_OK);

    /** @req SWS_Lin_00021 */
    SchM_Enter_Lin_EA_0();
    if( (Lin_ChanStat[Channel] == LIN_TX_BUSY) || (Lin_ChanStat[Channel] == LIN_TX_ERROR) ||
        (Lin_ChanStat[Channel] == LIN_RX_BUSY) || (Lin_ChanStat[Channel] == LIN_RX_ERROR) ||
        (Lin_ChanStat[Channel] == LIN_RX_NO_RESPONSE) || (Lin_ChanStat[Channel] ==LIN_TX_HEADER_ERROR) )
    {
        retval = resetTxRxWaitUntilReady(Channel);
        if (E_NOT_OK == retval) {
            return E_NOT_OK;
        }

        Lin_ChanStat[Channel]=LIN_OPERATIONAL;
    }
    SchM_Exit_Lin_EA_0();

    /* Save this info for later use in the interrupt routine */
    /* @req SWS_Lin_00016 */
    Lin_Pid[Channel] = PduInfoPtr->Pid;
    /* @req SWS_Lin_00014 */
    Lin_Cs[Channel] = PduInfoPtr->Cs;

    if (PduInfoPtr->Drc == LIN_MASTER_RESPONSE) {
        Lin_ChanStat[Channel] = LIN_TX_BUSY;

        if (PduInfoPtr->DI > 0){
            Lin_TxRxSize[Channel] = PduInfoPtr->DI;
            /* @req SWS_Lin_00053 */
            /* @req SWS_Lin_00025 */
            /* @req SWS_Lin_00026 */
            /* @req SWS_Lin_00096 */
            for (i = 0; i < PduInfoPtr->DI; i++) {
                Lin_BufTxRx[Channel][i] = PduInfoPtr->SduPtr[i];
            }

            Lin_CsTx[Channel] = calculateChecksum(Lin_BufTxRx[Channel],
                                                Lin_TxRxSize[Channel],
                                                Lin_Pid[Channel],
                                                Lin_Cs[Channel]);
        }
    }
    else if (PduInfoPtr->Drc == LIN_SLAVE_TO_SLAVE) {
        Lin_ChanStat[Channel] = LIN_TX_BUSY;
        Lin_ChanSlvToSlv[Channel] = TRUE;
    }
    /** @req SWS_Lin_00193 */
    else{
        Lin_ChanStat[Channel]=LIN_RX_BUSY;

        Lin_TxRxSize[Channel] = PduInfoPtr->DI;

        /* Calculate the time out value for the frame. MaxCnt = ((10 * (NDATA + 1) * 1.4) according to LIN 2.1 */
        Lin_RxTimeoutValue[Channel] = (((10 * (PduInfoPtr->DI + 1)) * 14) / 10);
    }

    /** @req SWS_Lin_00192 */
    /* Start by transmitting Break Field. The rest of the frame is handled in the interrupt routine */
    sendBreakField(Channel);
    return E_OK ;
}

/**
 * Sends the GoToSleep command on the bus and sets the internal module state to sleep pending.
 * @param Channel
 * @return
 */
/**@req SWS_Lin_00166 */
/** !req SWS_Lin_00221 Not supported by hardware */
Std_ReturnType Lin_GoToSleep(uint8 Channel)
{
    Lin_PduType PduInfo;

    uint8 data[8] = {0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

    /** @req SWS_Lin_00129*/
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (Lin_DrivStat != LIN_UNINIT), LIN_GO_TO_SLEEP_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);

    /** @req SWS_Lin_00131*/
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_GO_TO_SLEEP_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);

    //Send sleep command on bus
    PduInfo.Cs = LIN_CLASSIC_CS;
    PduInfo.Pid = PID_MASTER_REQ;
    PduInfo.SduPtr = data; /*lint !e934 Only used in this function  */
    PduInfo.DI = 8;
    PduInfo.Drc = LIN_MASTER_RESPONSE;

    /** @req SWS_Lin_00263 */
    /** @req SWS_Lin_00089 */
    /** @req SWS_Lin_00074 */ //Cancellation of previous send in done in Lin_SendFrame Api
    Lin_SendFrame(Channel,  &PduInfo); /*lint !e534 !e934 According to SWS_Lin_00266 action is same regardless of return value. Only used in this function */

    /* @req SWS_Lin_00033 */
    /* @req SWS_Lin_00266 */
    Lin_ChanStat[Channel]=LIN_CH_SLEEP_PENDING;
    Lin_SleepPending[Channel]=TRUE;

    return E_OK;
}

/**
 * Sets the internal module state to sleep
 * @param Channel
 * @return
 */
/** @req SWS_Lin_00167 */
/** !req SWS_Lin_00223 Not supported by Hw */
Std_ReturnType Lin_GoToSleepInternal(uint8 Channel)
{
    /** @req SWS_Lin_00133 */
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (Lin_DrivStat != LIN_UNINIT), LIN_GO_TO_SLEEP_INTERNAL_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);

    /** @req SWS_Lin_00135 */
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_GO_TO_SLEEP_INTERNAL_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);

    /** @req SWS_Lin_00222 Software implemented */
    /** @req SWS_Lin_00037 */
    if (Lin_CfgPtr->LinChannelConfig[Channel].LinChannelWakeUpSupport) {
            enableWakeupDetection(Channel);
    }

    /** @req SWS_Lin_00095 */
    /** @req SWS_Lin_00265 */
    Lin_ChanStat[Channel]=LIN_CH_SLEEP;
    return E_OK;
}

/**
 * Generates a wake up pulse and sets the channel state operational
 * @param Channel
 * @return
 */
/** @req SWS_Lin_00169 */
Std_ReturnType Lin_Wakeup( uint8 Channel )
{

    /** @req SWS_Lin_00137 */
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (Lin_DrivStat != LIN_UNINIT), LIN_WAKE_UP_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);

    /** @req SWS_Lin_00139 */
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_WAKE_UP_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);
    /** @req SWS_Lin_00140 */
    /* @req SWS_Lin_00213 */
    VALIDATE_W_RV( (Lin_ChanStat[Channel] == LIN_CH_SLEEP), LIN_WAKE_UP_SERVICE_ID, LIN_E_STATE_TRANSITION, E_NOT_OK);

    if (Lin_CfgPtr->LinChannelConfig[Channel].LinChannelWakeUpSupport) {
        disableWakeupDetection(Channel);
    }

    // Wakeup shall be 250us-5ms long.
    // For baudrate lower than 2k the baudrate must be reconfigured before sending wakeup.
    if (Lin_CfgPtr->LinChannelConfig[Channel].LinChannelBaudRate < BAUD_RATE_2K) {
        setBaudrateFromDivisors(Channel, Lin_BaudrateSendWakeup.bdiv, Lin_BaudrateSendWakeup.cd, Lin_BaudrateSendWakeup.div8);
    }

    /** @req SWS_Lin_00043 */
    /** @req SWS_Lin_00209 */
    sendWakeup(Channel);

    /* @req SWS_Lin_00174 */
    Lin_ChanStat[Channel]=LIN_OPERATIONAL;

    return E_OK;
}

/**
 * Sets the channel state to operational without generating a wakeup pulse.
 * @param Channel
 * @return
 */
/** @req SWS_Lin_00256 */
Std_ReturnType   Lin_WakeupInternal(uint8 Channel) {
    /** @req SWS_Lin_00258 */
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (Lin_DrivStat != LIN_UNINIT), LIN_WAKE_UP_INTERNAL_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);
    /** @req SWS_Lin_00259 */
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_WAKE_UP_INTERNAL_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);
    /** @req SWS_Lin_00260 */
    /* @req SWS_Lin_00213 */
    VALIDATE_W_RV( (Lin_ChanStat[Channel] == LIN_CH_SLEEP), LIN_WAKE_UP_INTERNAL_SERVICE_ID, LIN_E_STATE_TRANSITION, E_NOT_OK);

    if (Lin_CfgPtr->LinChannelConfig[Channel].LinChannelWakeUpSupport) {
        disableWakeupDetection(Channel);
    }

    /**@req SWS_Lin_00257 */
    /* @req SWS_Lin_00261 */
    /* @req SWS_Lin_00262 */
    Lin_ChanStat[Channel]=LIN_OPERATIONAL;
    return E_OK;
}

/**
 * Checks if the wakeup source have caused the wakeup. If it has it will
 * call EcuM_SetWakeupEvent.
 * @param WakeupSource
 * @return
 */
/* @req SWS_Lin_00160 */
Std_ReturnType Lin_CheckWakeup(uint8 Channel) {
    const Lin_ChannelConfigType *chnCfg;

    /* @req SWS_Lin_00107 */
    VALIDATE_W_RV( (Lin_DrivStat != LIN_UNINIT), LIN_CHECKWAKEUP_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);
    /* @req SWS_Lin_00251 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_CHECKWAKEUP_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);

#if (LIN_REPORT_WAKEUP_SOURCE == STD_ON)
    chnCfg = &Lin_CfgPtr->LinChannelConfig[Channel];

    if (chnCfg->LinChannelWakeUpSupport &&
        chnCfg->LinChannelEcuWakeUpDefined &&
        Lin_WakeupSet[Channel])
    {

        /* !req SWS_Lin_00098 Not fully fulfilled, callback to LinIf_WakeupConfirmation is not done.
         * Event is detected by interrupt routine */
        EcuM_SetWakeupEvent(chnCfg->LinChannelEcuMWakeUpSource);
    }

    // Always set to false after it has been read out.
    Lin_WakeupSet[Channel] = FALSE;
#endif

    return E_OK;
}

/**
 * Gets the status of the LIN driver.
 * @param Channel
 * @param Lin_SduPtr
 * @return
 */
/** @req SWS_Lin_00168 */
Lin_StatusType Lin_GetStatus( uint8 Channel, uint8** Lin_SduPtr ){
    Std_ReturnType retval;

    /** @req SWS_Lin_00141*/
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (Lin_DrivStat != LIN_UNINIT), LIN_GETSTATUS_SERVICE_ID, LIN_E_UNINIT, LIN_NOT_OK);
    /** @req SWS_Lin_00143*/
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_GETSTATUS_SERVICE_ID, LIN_E_INVALID_CHANNEL, LIN_NOT_OK);
    /** @req SWS_Lin_00144*/
    /** @req SWS_Lin_00249 **/
    VALIDATE_W_RV( (Lin_SduPtr!=NULL), LIN_GETSTATUS_SERVICE_ID, LIN_E_PARAM_POINTER, LIN_NOT_OK);

    SchM_Enter_Lin_EA_0();
    Lin_StatusType res = Lin_ChanStat[Channel];

    /** @req SWS_Lin_00200 */
    switch (res) {
        case LIN_RX_OK:
            /** @req SWS_Lin_00092 */
            /** @!req SWS_Lin_00211 The receive frame processing is handled in the ISR */
            *Lin_SduPtr = Lin_BufTxRx[Channel];
            //lint -fallthrough
        case LIN_TX_OK:
            /** @req SWS_Lin_00238 */
            Lin_ChanStat[Channel]=LIN_OPERATIONAL;
            break;

        case LIN_RX_ERROR:
            //lint -fallthrough
        case LIN_TX_ERROR:
            //lint -fallthrough
        case LIN_RX_NO_RESPONSE:
            //lint -fallthrough
        case LIN_TX_HEADER_ERROR:
            //lint -fallthrough

            retval = resetTxRxWaitUntilReady(Channel);
            if (E_NOT_OK == retval) {
                return LIN_NOT_OK;
            }

            Lin_ChanStat[Channel]=LIN_OPERATIONAL;
            break;

        case LIN_CH_SLEEP_PENDING:
            /** @req SWS_Lin_00255 */
            /** @req SWS_Lin_00264 */
            res = Lin_ChanStat[Channel]=LIN_CH_SLEEP;
            break;
        default:
            break;
    }

    SchM_Exit_Lin_EA_0();
    /** @req SWS_Lin_00091 */
    /* @req SWS_Lin_00022 */
    /* @req SWS_Lin_00024 */
    return res;
}

#if (LIN_VERSION_INFO_API == STD_ON)
/**
 * Returns the version information of the module
 * @param versioninfo
 */
/** @req SWS_Lin_00161 **/
/** @req SWS_Lin_00001 **/
void Lin_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    /** @req SWS_Lin_00248 **/
    /** @req SWS_Lin_00249 **/
    VALIDATE( !(versioninfo == NULL), LIN_GETVERSIONINFO_SERVICE_ID, LIN_E_PARAM_POINTER );

    /** @req SWS_Lin_00001 **/
    versioninfo->vendorID = LIN_VENDOR_ID;
    versioninfo->moduleID = LIN_MODULE_ID;
    versioninfo->sw_major_version = LIN_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = LIN_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = LIN_SW_PATCH_VERSION;
    return;
}

#endif
