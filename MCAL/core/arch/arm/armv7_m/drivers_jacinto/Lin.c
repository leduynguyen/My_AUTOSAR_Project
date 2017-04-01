
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

/** @tagSettings DEFAULT_ARCHITECTURE=JACINTO6 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */
#include "Lin_jacinto.h"
#include "timer.h"
#include "Lin.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "SchM_Lin.h"
#include "isr.h"
#include "irq.h"

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
/* @req SWS_Lin_00029 This Lin driver implementation is specific for the Jacinto6 uart controller */
/* @req SWS_Lin_00045 There are up to nine uart controllers of the same type, each with one channel*/
/* @req SWS_Lin_00005 The driver is implemented to support the LIN 2.1 protcol */
/* @!req SWS_Lin_00032 Not supported by hardware */
/* @req SWS_Lin_00157 Done by hardware*/
/* @req SWS_Lin_00206 The lin driver does not provid any callback functions*/
/* @!req SWS_Lin_00234 Only callback to EcuM_SetWakeupEvent is supported by the module */
/* @req SWS_Lin_00063 Hardware uart used */
/* @req SWS_Lin_00227 initialized from top layer */
/* @req SWS_Lin_00054 all internal functions are static */
/* @!req SWS_Lin_00055 Implemented accodring to the ArcCore C-coding style*/

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

#define BREAK_FIELD_DATA    0uL
#define WAKEUP_FIELD_DATA   0uL

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

typedef struct {
    uint8 channelMap[LIN_ARC_HW_UNIT_CNT];
    uint8 channelToHwChannel[LIN_ARC_LOG_UNIT_CNT];
} Lin_GlobalType;


static void waitAndReset(uint8 hwChannel);

void Uart_Init_Channel(uint8 hwCh, uint16 baudRate);
static void InitChannel(uint8 hwChannel, uint16 baudRate );
static void EnterModeA(uint8 hwChannel);
static void EnterModeB(uint8 hwChannel);
static void EnterSubmodeTlr(uint8 hwChannel);
static void EnterModeOp(uint8 hwChannel);
static void EnableChannel(uint8 hwChannel);

/* Reset -> LIN_UNINIT: After reset, the Lin module shall set its state to LIN_UNINIT. */
/* @req SWS_Lin_00145 */
static Lin_DriverStatusType Lin_DrivStat = LIN_UNINIT;

static Lin_StatusType Lin_ChanStat[LIN_ARC_LOG_UNIT_CNT];
static boolean Lin_SleepPending[LIN_ARC_LOG_UNIT_CNT];

static const Lin_ConfigType* Lin_CfgPtr = NULL;

static Lin_FramePidType Lin_Pid[LIN_ARC_LOG_UNIT_CNT];
static Lin_FrameCsModelType Lin_Cs[LIN_ARC_LOG_UNIT_CNT];

/* static buffers, holds one frame at a time */
static uint8 Lin_BufTxRx[LIN_ARC_LOG_UNIT_CNT][LIN_MAX_MSG_LENGTH];

static uint8  Lin_CsTx[LIN_ARC_LOG_UNIT_CNT];
static uint8  Lin_TxRxSize[LIN_ARC_LOG_UNIT_CNT];
static uint32 Lin_RxTimeoutValue[LIN_ARC_LOG_UNIT_CNT]; //lint -e551 Used for state machines

static boolean Lin_WakeupSet[LIN_ARC_LOG_UNIT_CNT];

//static BaudrateDivisorType Lin_BaudrateSendWakeup = {0};
static BaudrateDivisorType Lin_BaudrateReceiveWakeup = {0};
static BaudrateDivisorType Lin_BaudrateDivisors[LIN_ARC_LOG_UNIT_CNT][NR_OF_BAUDRATE_SETUPS];

static uint8 Lin_LastTxData[LIN_ARC_LOG_UNIT_CNT] = {0}; //lint -e551 Used for state machines
static Lin_IsrStateType Lin_IsrState[LIN_ARC_LOG_UNIT_CNT];
static boolean Lin_IsTransmitting[LIN_ARC_LOG_UNIT_CNT];  //lint -e551 Used for state machines
static boolean Lin_ChanSlvToSlv[LIN_ARC_LOG_UNIT_CNT];

Lin_GlobalType Lin_Global;

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

static inline uint8 HwChannelToChannel(uint8 ch) {
    return Lin_Global.channelMap[ch];
}
static inline uint8 ChannelToHwChannel(uint8 ch) {
    return Lin_Global.channelToHwChannel[ch];
}


/* RS-CAN Channel based indexing */
/*lint -e{923} HARDWARE ACCESS */
Uart_reg * const Lin_HwChToPtr[] = {
        ((Uart_reg *) (UART_1_ADDRESS)),
        ((Uart_reg *) (UART_2_ADDRESS)),
        ((Uart_reg *) (UART_3_ADDRESS)),
        ((Uart_reg *) (UART_4_ADDRESS)),
        ((Uart_reg *) (UART_5_ADDRESS)),
        ((Uart_reg *) (UART_6_ADDRESS)),
        ((Uart_reg *) (UART_7_ADDRESS)),
        ((Uart_reg *) (UART_8_ADDRESS)),
        ((Uart_reg *) (UART_9_ADDRESS)),
        ((Uart_reg *) (UART_10_ADDRESS)),
};

static const uint32 UartClkCtrl[] = {
    (0x4A009840UL + L3_OFFSET), /* CM_L4PER_UART1_CLKCTRL */
    (0x4A009848UL + L3_OFFSET), /* CM_L4PER_UART2_CLKCTRL */
    (0x4A009850UL + L3_OFFSET), /* CM_L4PER_UART3_CLKCTRL */
    (0x4A009858UL + L3_OFFSET), /* CM_L4PER_UART4_CLKCTRL */
    (0x4A009870UL + L3_OFFSET),
    (0x4A005580UL + L3_OFFSET), /* CM_IPU_UART6_CLKCTRL */
    (0x4A0098D0UL + L3_OFFSET), /* CM_L4PER2_UART7_CLKCTRL */
    (0x4A0098E0UL + L3_OFFSET), /* CM_L4PER2_UART8_CLKCTRL */
    (0x4A0098E8UL + L3_OFFSET), /* CM_L4PER2_UART9_CLKCTRL */
    (0x4AE07880UL + L3_OFFSET), /* CM_WKUPAON_UART10_CLKCTRL */
};



/**
 * Disable the transmission and reception of data
 * @param ch
 */
static void disableTXRX(uint8 hwCh){
   volatile Uart_reg* uartPtr = Lin_HwChToPtr[hwCh];
   uartPtr->IER_DLH &= ~0x01U;
}


/**
 * Used to flush rx/tx data
 * @param ch
 */
static void resetTXRX(uint8 hwCh){
    volatile Uart_reg* uartPtr = Lin_HwChToPtr[hwCh];
    uartPtr->IIR_FCR_EFR |=  0x6U;
}


/**
 * This function is used instead of "while". It returns when the condition is cleared or
 * when n reach MAX_WAIT_CYCLES.
 * @param regBaseAddr
 * @param mask
 * @param retCondition
 * @return
 */
#if 0 /** function nou in use for the moment but could be usefull **/
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
#endif
/**
 * Resets tx/rx and wait for status bits to clear.
 * @param Channel
 * @return
 */
static Std_ReturnType resetTxRxWaitUntilReady(uint8 hwCh) {
    resetTXRX(hwCh);
    return E_OK;
}

/**
 * Aborts an ongoing transmission/reception. Is used in case of error.
 * @param ch
 * @param timeoutErr
 */
static void abortOngoingTxRx(uint8 hwCh, boolean timeoutErr, uint8 nbrRxTxData) {
    volatile Uart_reg* uartPtr = Lin_HwChToPtr[hwCh];
    uint8 logCh = HwChannelToChannel(hwCh);

    uartPtr->IER_DLH &= ~0x3U;

    switch(Lin_IsrState[logCh]) {
        case SEND_SYNC:
        case SEND_PID:
        case PID_TRANSMITTED:
            Lin_ChanStat[logCh] = LIN_TX_HEADER_ERROR;
            break;
        case TX_DATA:
        case TX_CHECKSUM:
                Lin_ChanStat[logCh] = LIN_TX_ERROR;
            break;
        case RX_DATA:
        case RX_CHECKSUM:
            if ((timeoutErr == TRUE) && (nbrRxTxData == 0)) {
                Lin_ChanStat[logCh] = LIN_RX_NO_RESPONSE;
            } else {
                Lin_ChanStat[logCh] = LIN_RX_ERROR;
            }
            break;
        default:
            break;
    }


    /* If wake-up detection is supported by configuration parameter LinChannelWakeupSupport,
     * then the function Lin_GoToSleep shall enable the wake-up detection,
     * even in case of an erroneous transmission of the go-to-sleep-command.
     */
    if ((Lin_SleepPending[logCh] == TRUE) && (Lin_CfgPtr->LinChannelConfig[logCh].LinChannelWakeUpSupport == TRUE)) {
        /** @req SWS_Lin_00220 */
        Lin_IsrState[logCh] = WAKEUP_DETECT_INIT;
        Lin_SleepPending[logCh] = FALSE;
    } else {
        Lin_IsrState[logCh] = IDLE;
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
static Std_ReturnType calculateBaudrateDivisors(uint32 Clock, uint16 BaudRate, uint32 *rbdiv)
 {
    uint32 bdiv;
    uint32 clk;

    VALIDATE_W_RV( (BaudRate != 0uL), LIN_INIT_SERVICE_ID, LIN_E_INVALID_CONFIG, E_NOT_OK );
    VALIDATE_W_RV( (rbdiv != NULL)  , LIN_INIT_SERVICE_ID, LIN_E_INVALID_POINTER, E_NOT_OK );

    clk = Clock/16;

    bdiv = clk / BaudRate;

    *rbdiv = bdiv;

    return E_OK;
}

/**
 * Set baudrate divisors based
 * @param ch
 * @param bdiv
 * @param cd
 * @param div8
 */
static void setBaudrateFromDivisors(uint8 hwCh, uint32 bdiv){
    volatile Uart_reg* uartPtr = Lin_HwChToPtr[hwCh];

    uartPtr->MDR1 |= MDR1_DISABLE_UART_MASK;
    waitAndReset(hwCh);


    disableTXRX(hwCh);
    /** open DLL and DHL latch **/
    EnterModeB(hwCh);
    if (bdiv == 0) { /* Failsafe: to 19.2 kbps */
        uartPtr->THR_RHR_DLL = 156;
    }
    else {
        uartPtr->THR_RHR_DLL = bdiv;
    }
    /* Enable RX and TX interrupts */
    EnterModeOp(hwCh);
    (void)resetTxRxWaitUntilReady(hwCh);

    uartPtr->MDR1 &= ~MDR1_DISABLE_UART_MASK;
    waitAndReset(hwCh);

}


/**
 * Setup peripheral to send a break field. This is doen by changing the baudrate
 * @param ch
 */
static void sendBreakField(uint8 hwCh) {
    /* To be able to set low level for at least 13 bits we change to a slower baudrate
     * We will use 9 bits (1 start and 8 data bits) to represent 13 bits so
     * the new baudrate is 9/13*oldBaudrate > 8/13*oldBaudrate */
    uint8 logCh = HwChannelToChannel(hwCh);

    setBaudrateFromDivisors(hwCh, Lin_BaudrateDivisors[logCh][BREAK_BAUDRATE_INDEX].bdiv);
    //setBaudrateFromDivisors(ch, 0xFFU);

    volatile Uart_reg* uartPtr = Lin_HwChToPtr[hwCh];

    uartPtr->THR_RHR_DLL = BREAK_FIELD_DATA;
    Lin_LastTxData[logCh] = BREAK_FIELD_DATA;

    Lin_IsTransmitting[logCh] = TRUE;
    Lin_IsrState[logCh] = SEND_SYNC;

 //   uartPtr->IER_DLH |= IIR_RX_INTERRUPT;
    uartPtr->IER_DLH |= IIR_TX_INTERRUPT;
}

/**
 * Sends a wakeup pulse on the channel
 * @param ch
 */
static void sendWakeup(uint8 hwCh) {

    volatile Uart_reg* uartPtr = Lin_HwChToPtr[hwCh];
    uint8 logCh = HwChannelToChannel(hwCh);

    uartPtr->IER_DLH |= IIR_RX_INTERRUPT;

    uartPtr->THR_RHR_DLL = WAKEUP_FIELD_DATA;
    Lin_LastTxData[logCh] = WAKEUP_FIELD_DATA;

    Lin_IsTransmitting[logCh] = TRUE;
    Lin_IsrState[logCh] = WAKEUP;
    uartPtr->IER_DLH |= IIR_TX_INTERRUPT;
}

/**
 * Setup the peripheral to monitor the bus for a wakeup pulse
 * @param ch
 */
static void enableWakeupDetection(uint8 hwCh) {
    volatile Uart_reg* uartPtr = Lin_HwChToPtr[hwCh];
    uint8 logCh = HwChannelToChannel(hwCh);
    setBaudrateFromDivisors(hwCh, Lin_BaudrateReceiveWakeup.bdiv);

    uartPtr->IER_DLH = IIR_RX_INTERRUPT;
    uartPtr->SYSC |= 0x4U;

    Lin_WakeupSet[logCh] = FALSE;
    Lin_IsTransmitting[logCh] = FALSE;
    Lin_IsrState[logCh] = WAKEUP_DETECT;
}

/**
 * Disables wakeup detection
 * @param ch
 */
static void disableWakeupDetection(uint8 hwCh) {
    volatile Uart_reg* uartPtr = Lin_HwChToPtr[hwCh];
    uint8 logCh = HwChannelToChannel(hwCh);

    uartPtr->IER_DLH &= ~IIR_RX_INTERRUPT;
    uartPtr->SYSC &= ~0x4U;

    Lin_WakeupSet[logCh] = FALSE;
    Lin_IsrState[logCh] = IDLE;
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
static void Lin_Internal_Interrupt(uint8 hwCh) {

    volatile Uart_reg* uartPtr = Lin_HwChToPtr[hwCh];

    uartPtr->IER_DLH &= ~IIR_TX_INTERRUPT;
    uartPtr->IER_DLH &= ~IIR_RX_INTERRUPT;

    static uint8 byteNr[LIN_ARC_LOG_UNIT_CNT] = { 0 };
    static boolean timeoutErrEnable[LIN_ARC_LOG_UNIT_CNT] = { 0 };
    static boolean txCsSent[LIN_ARC_LOG_UNIT_CNT] = { 0 };

    uint8 logCh = HwChannelToChannel(hwCh);

    boolean timeoutErr;
    uint8 rxData;
    uint8 cs;

    uint32 iir = (uartPtr->IIR_FCR_EFR & IIR_INTERRUPT_TYPE_MASK) >> 1;
    rxData = (uint8) uartPtr->THR_RHR_DLL;

    timeoutErr = (0x6 == (iir & 0x6U)) ? TRUE : FALSE;

    if ((timeoutErr == TRUE ) && (timeoutErrEnable[logCh] == TRUE)) {
        abortOngoingTxRx(hwCh, timeoutErr, 0);
    }

    switch (Lin_IsrState[logCh]) {
        case WAKEUP_DETECT_INIT:
            /** @req SWS_Lin_00037 */
            /** @req SWS_Lin_00220 */
            enableWakeupDetection(hwCh);
            Lin_IsrState[logCh] = WAKEUP_DETECT;
            break;
        case WAKEUP_DETECT:
            if (WAKEUP_FIELD_DATA == rxData) {
                Lin_WakeupSet[logCh] = TRUE;

#if (LIN_REPORT_WAKEUP_SOURCE == STD_ON)
                /* @req SWS_Lin_00176 */
                if (Lin_CfgPtr->LinChannelConfig[logCh].LinChannelEcuWakeUpDefined == TRUE) {
                    EcuM_CheckWakeup(Lin_CfgPtr->LinChannelConfig[logCh].LinChannelEcuMWakeUpSource);
                }
#endif
            }
            break;
        case SEND_SYNC:
            byteNr[hwCh] = 0;
            Lin_IsTransmitting[logCh] = TRUE;
            timeoutErrEnable[logCh] = FALSE;
            txCsSent[logCh] = FALSE;

           setBaudrateFromDivisors(hwCh, Lin_BaudrateDivisors[logCh][NORMAL_BAUDRATE_INDEX].bdiv);

            /* Set data for Sync field transmission */
            uartPtr->THR_RHR_DLL = 0x55;
            Lin_LastTxData[logCh] = 0x55;
            Lin_IsrState[logCh] = SEND_PID;
            uartPtr->IER_DLH |= IIR_TX_INTERRUPT;
            break;

        case SEND_PID:
            /* Set data for PID transmission */
            uartPtr->THR_RHR_DLL = Lin_Pid[logCh];
            Lin_LastTxData[logCh] = Lin_Pid[logCh];

            Lin_IsrState[logCh] = PID_TRANSMITTED;
            uartPtr->IER_DLH |= IIR_TX_INTERRUPT;
            break;

        case PID_TRANSMITTED:
            /* PID transmitted, determine if we are going to receive or transmit data */
            if (LIN_RX_BUSY == Lin_ChanStat[logCh]) {
                Lin_IsTransmitting[hwCh] = FALSE;

#if !defined(CFG_LIN_LOOPBACK)
                /** Clear RX FIFO AND RHR **/
                uartPtr->IIR_FCR_EFR |= 0x02U;
                uint8 dummey = uartPtr->THR_RHR_DLL;
                (void) dummey;
#endif

                /* Set timeout */
                timeoutErrEnable[logCh] = TRUE;

                Lin_IsrState[logCh] = RX_DATA;
                uartPtr->IER_DLH |= IIR_RX_INTERRUPT;
                break;
            } else if (Lin_ChanSlvToSlv[logCh] == TRUE) {
                Lin_IsrState[logCh] = IDLE;
                Lin_ChanSlvToSlv[logCh] = FALSE;
                Lin_ChanStat[logCh] = LIN_TX_OK;
            } else {
                Lin_IsrState[logCh] = TX_DATA;
            }
            //lint -fallthrough for TX_DATA
        case TX_DATA:
            uartPtr->THR_RHR_DLL = Lin_BufTxRx[logCh][byteNr[logCh]];
            Lin_LastTxData[logCh] = Lin_BufTxRx[logCh][byteNr[logCh]];

            byteNr[logCh]++;

            if (Lin_TxRxSize[logCh] <= byteNr[logCh]) {
                Lin_IsrState[logCh] = TX_CHECKSUM;
            }
            uartPtr->IER_DLH |= IIR_TX_INTERRUPT;
            break;

        case TX_CHECKSUM:
            uartPtr->THR_RHR_DLL = Lin_CsTx[logCh];
            Lin_LastTxData[logCh] = Lin_CsTx[logCh];

            if ((Lin_SleepPending[logCh] == TRUE) && (Lin_CfgPtr->LinChannelConfig[logCh].LinChannelWakeUpSupport == TRUE)) {
                Lin_IsrState[logCh] = WAKEUP_DETECT_INIT;
            } else {
                Lin_IsrState[logCh] = TX_CHECKSUM_VALIDATION;
                txCsSent[logCh] = TRUE;
            }
            Lin_SleepPending[logCh] = FALSE;
            uartPtr->IER_DLH |= IIR_TX_INTERRUPT;
            break;
        case RX_DATA:
            /** @req SWS_Lin_00060 */
            Lin_BufTxRx[logCh][byteNr[logCh]] = rxData;
            byteNr[logCh]++;

            if (Lin_TxRxSize[logCh] <= byteNr[logCh]) {
                Lin_IsrState[logCh] = RX_CHECKSUM;
            }
            uartPtr->IER_DLH |= IIR_RX_INTERRUPT;
            break;
        case RX_CHECKSUM:
            /* expected cs */
            cs = calculateChecksum(Lin_BufTxRx[logCh], Lin_TxRxSize[logCh], Lin_Pid[logCh], Lin_Cs[logCh]);

            if (cs == rxData) {
                Lin_ChanStat[logCh] = LIN_RX_OK;
                Lin_IsrState[logCh] = IDLE;
                uartPtr->IER_DLH &= ~IIR_RX_INTERRUPT;
            } else {
                abortOngoingTxRx(hwCh, FALSE, byteNr[logCh]);
            }
            timeoutErrEnable[logCh] = FALSE;
            uartPtr->IER_DLH &= ~IIR_RX_INTERRUPT;
            //lint -fallthrough
        case WAKEUP:
            // If baudrate was reconfigured to transmit the wakeup there is no need to change it back here. It will
            // be changed the sendBreak function anyway.
            //lint -fallthrough
        case TX_CHECKSUM_VALIDATION:
            if ((txCsSent[logCh] == TRUE) && (Lin_ChanStat[logCh] != LIN_CH_SLEEP_PENDING)) {
                Lin_ChanStat[logCh] = LIN_TX_OK;
            }
            //lint -fallthrough
        case IDLE:
            //lint -fallthrough
        default:
            Lin_IsrState[logCh] = IDLE;
            timeoutErrEnable[logCh] = FALSE;
            Lin_ChanSlvToSlv[logCh] = FALSE;
            txCsSent[logCh] = FALSE;
            uartPtr->IER_DLH &= ~IIR_RX_INTERRUPT;
            break;
    }

    /* Clear interrupt flags */

    /** Hardware clearest flags **/

}


ISR(LinInterruptUSART1); /* Prototype */
ISR(LinInterruptUSART1){ Lin_Internal_Interrupt(1u);}
ISR(LinInterruptUSART2); /* Prototype */
ISR(LinInterruptUSART2){ Lin_Internal_Interrupt(2u);}
ISR(LinInterruptUSART3); /* Prototype */
ISR(LinInterruptUSART3){ Lin_Internal_Interrupt(3u);}
ISR(LinInterruptUSART4); /* Prototype */
ISR(LinInterruptUSART4){ Lin_Internal_Interrupt(4u);}
ISR(LinInterruptUSART5); /* Prototype */
ISR(LinInterruptUSART5){ Lin_Internal_Interrupt(5u);}
ISR(LinInterruptUSART6); /* Prototype */
ISR(LinInterruptUSART6){ Lin_Internal_Interrupt(6u);}
ISR(LinInterruptUSART7); /* Prototype */
ISR(LinInterruptUSART7){ Lin_Internal_Interrupt(7u);}
ISR(LinInterruptUSART8); /* Prototype */
ISR(LinInterruptUSART8){ Lin_Internal_Interrupt(8u);}
ISR(LinInterruptUSART9); /* Prototype */
ISR(LinInterruptUSART9){ Lin_Internal_Interrupt(9u);}
ISR(LinInterruptUSART10); /* Prototype */
ISR(LinInterruptUSART10){ Lin_Internal_Interrupt(10u);}

/**
 * Initializes the module
 * @param Config
 */
/** @req SWS_Lin_00006 */
/** @req SWS_Lin_00084 */
/** @req SWS_Lin_00150 */
void Lin_Init(const Lin_ConfigType* Config) {
    Std_ReturnType retval;
    uint32 cd = 0;
    uint32 bdiv = 0;
    uint8  div8 = 0;
    uint32 breakBaud;
    uint8 hwCh;

    /** @req SWS_Lin_00105 **/
    VALIDATE( (Lin_DrivStat == LIN_UNINIT), LIN_INIT_SERVICE_ID, LIN_E_STATE_TRANSITION );
    /** @req SWS_Lin_00099 **/
    /** @req SWS_Lin_00216 **/
    VALIDATE( (Config!=NULL), LIN_INIT_SERVICE_ID, LIN_E_INVALID_POINTER );

    Lin_CfgPtr = Config;

    for (uint8 i = 0; i < LIN_ARC_LOG_UNIT_CNT; i++) {
        Lin_TxRxSize[i] = 0;
        Lin_RxTimeoutValue[i] = 0;
        Lin_IsrState[i] = IDLE;
        Lin_WakeupSet[i] = FALSE;
        Lin_SleepPending[i] = FALSE;
        Lin_ChanSlvToSlv[i] = FALSE;
    }

    // Calculate a baudrate setup for the lin wakeup pulse.
    retval = calculateBaudrateDivisors(UART_FIXED_CLOCK_RATE, 56000UL, &Lin_BaudrateReceiveWakeup.bdiv);
    if (E_NOT_OK == retval) {
        return;
    }

    /** @req SWS_Lin_00190 */

    for (uint8 logCh = 0; logCh < LIN_ARC_LOG_UNIT_CNT; logCh++) {
        hwCh = Config->LinChannelConfig[logCh].LinChannelId;
        Lin_Global.channelToHwChannel[logCh] = hwCh;
        Lin_Global.channelMap[hwCh] = logCh;

        Lin_CfgPtr = Config;
        retval = calculateBaudrateDivisors(UART_FIXED_CLOCK_RATE,
                (uint32)Lin_CfgPtr->LinChannelConfig[logCh].LinChannelBaudRate, &bdiv); /*lint !e934 Only used in this function  */
        if (E_NOT_OK == retval) {
            return;
        }

        Lin_BaudrateDivisors[logCh][NORMAL_BAUDRATE_INDEX].bdiv = bdiv;
        Lin_BaudrateDivisors[logCh][NORMAL_BAUDRATE_INDEX].cd = cd;
        Lin_BaudrateDivisors[logCh][NORMAL_BAUDRATE_INDEX].div8 = div8;

        /* To be able to set low level for at least 13 bits we change to a slower baudrate
        * We will use 9 bits (1 start and 8 data bits) to represent 13 bits so
        * the new baudrate is 9/13*oldBaudrate > 8/13*oldBaudrate */

        breakBaud = ((uint32)Lin_CfgPtr->LinChannelConfig[logCh].LinChannelBaudRate * 9uL) / 13uL;
        retval = calculateBaudrateDivisors(UART_FIXED_CLOCK_RATE,
                (uint16)breakBaud, &bdiv); /*lint !e934 Only used in this function  */
        if (E_NOT_OK == retval) {
            return;
        }

        Lin_BaudrateDivisors[logCh][BREAK_BAUDRATE_INDEX].bdiv = bdiv;
        Lin_BaudrateDivisors[logCh][BREAK_BAUDRATE_INDEX].cd = cd;
        Lin_BaudrateDivisors[logCh][BREAK_BAUDRATE_INDEX].div8 = div8;

        /* @req SWS_Lin_00008 */
#if 0
        if(LinChannelConfigData[logCh].LinUartChannelId <= 2) {
            uartConfigs.ChannelConfigs[logCh].logCh = LinChannelConfigData[logCh].LinUartChannelId;
        }
        else {
            uartConfigs.ChannelConfigs[logCh].Channel = 1;     /** Default to Channel 1 if incorrect selection**/
        }
        uartConfigs.ChannelConfigs[logCh].BaudRate = LinChannelConfigData[logCh].LinChannelBaudRate;
#endif

        Uart_Init_Channel(hwCh, Config->LinChannelConfig[logCh].LinChannelBaudRate );

        /** @req SWS_Lin_00171 */
        Lin_ChanStat[logCh] = LIN_OPERATIONAL;
    }



    /* @req SWS_Lin_00146 */
    /* LIN_UNINIT -> LIN_INIT: The Lin module shall transition from LIN_UNINIT
     * to LIN_INIT when the function Lin_Init is called. */
    Lin_DrivStat = LIN_INIT;
}

/**
 * De-initializes the module
 */
void Lin_Arc_DeInit(void){
    volatile Uart_reg* uartPtr;
    uint8 ch;

    VALIDATE( (Lin_DrivStat != LIN_UNINIT), LIN_ARC_DEINIT_SERVICE_ID, LIN_E_UNINIT);

    Lin_DrivStat = LIN_UNINIT;

    for (ch = 0; ch < LIN_ARC_LOG_UNIT_CNT; ch++) {

        uartPtr = Lin_HwChToPtr[ChannelToHwChannel(ch)];

        /** reset uart **/
        uartPtr->SYSC |= 0x2U;
        while ((uartPtr->SYSS & SYSS_RESET_PROGRESS_MASK) == 0){};

        /* Disable interrupts */
        uartPtr->IER_DLH &= ~0x3U;
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
    uint8 logCh = HwChannelToChannel(Channel);

    /** @req SWS_Lin_00195 */
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (Lin_DrivStat != LIN_UNINIT), LIN_SEND_FRAME_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);

    /** @req SWS_Lin_00197 */
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (logCh < LIN_ARC_LOG_UNIT_CNT), LIN_SEND_FRAME_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);
    /* Send header is used to wake the net in this implementation(no actual header is sent */
    /** @req SWS_Lin_00199 */
    /** @req SWS_Lin_00213 */
    /** @req SWS_Lin_00194 */
    VALIDATE_W_RV( (Lin_ChanStat[logCh] != LIN_CH_SLEEP), LIN_SEND_FRAME_SERVICE_ID, LIN_E_STATE_TRANSITION, E_NOT_OK);
    /** @req SWS_Lin_00198 */
    /** @req SWS_Lin_00249 **/
    VALIDATE_W_RV( (PduInfoPtr != NULL), LIN_SEND_FRAME_SERVICE_ID, LIN_E_PARAM_POINTER, E_NOT_OK);

    /** @req SWS_Lin_00021 */
    SchM_Enter_Lin_EA_0();

    if( (Lin_ChanStat[logCh] == LIN_TX_BUSY) || (Lin_ChanStat[logCh] == LIN_TX_ERROR) ||
        (Lin_ChanStat[logCh] == LIN_RX_BUSY) || (Lin_ChanStat[logCh] == LIN_RX_ERROR) ||
        (Lin_ChanStat[logCh] == LIN_RX_NO_RESPONSE) || (Lin_ChanStat[logCh] ==LIN_TX_HEADER_ERROR) )
    {
        retval = resetTxRxWaitUntilReady(logCh);
        if (E_NOT_OK == retval) {
            return E_NOT_OK;
        }

        Lin_ChanStat[logCh]=LIN_OPERATIONAL;
    }
    SchM_Exit_Lin_EA_0();

    /* Save this info for later use in the interrupt routine */
    /* @req SWS_Lin_00016 */
    Lin_Pid[logCh] = PduInfoPtr->Pid;
    /* @req SWS_Lin_00014 */
    Lin_Cs[logCh] = PduInfoPtr->Cs;

    if (PduInfoPtr->Drc == LIN_MASTER_RESPONSE) {
        Lin_ChanStat[logCh] = LIN_TX_BUSY;

        if (PduInfoPtr->DI > 0){
            Lin_TxRxSize[logCh] = PduInfoPtr->DI;
            /* @req SWS_Lin_00053 */
            /* @req SWS_Lin_00025 */
            /* @req SWS_Lin_00026 */
            /* @req SWS_Lin_00096 */
            for (i = 0; i < PduInfoPtr->DI; i++) {
                Lin_BufTxRx[logCh][i] = PduInfoPtr->SduPtr[i];
            }

            Lin_CsTx[logCh] = calculateChecksum(Lin_BufTxRx[logCh],
                                                Lin_TxRxSize[logCh],
                                                Lin_Pid[logCh],
                                                Lin_Cs[logCh]);
        }
    }
    else if (PduInfoPtr->Drc == LIN_SLAVE_TO_SLAVE) {
        Lin_ChanStat[logCh] = LIN_TX_BUSY;
        Lin_ChanSlvToSlv[logCh] = TRUE;
    }
    /** @req SWS_Lin_00193 */
    else{
        Lin_ChanStat[logCh]=LIN_RX_BUSY;

        Lin_TxRxSize[logCh] = PduInfoPtr->DI;

        /* Calculate the time out value for the frame. MaxCnt = ((10 * (NDATA + 1) * 1.4) according to LIN 2.1 */
        Lin_RxTimeoutValue[logCh] = (((10 * (PduInfoPtr->DI + 1)) * 14) / 10);
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
    uint8 logCh = HwChannelToChannel(Channel);
    volatile Uart_reg* uartPtr = Lin_HwChToPtr[Channel];
    uartPtr->IER_DLH &= ~0x3U;

    Lin_PduType PduInfo;

    uint8 data[8] = {0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

    /** @req SWS_Lin_00129*/
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (Lin_DrivStat != LIN_UNINIT), LIN_GO_TO_SLEEP_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);

    /** @req SWS_Lin_00131*/
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_ARC_HW_UNIT_CNT), LIN_GO_TO_SLEEP_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);

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
    Lin_ChanStat[logCh]=LIN_CH_SLEEP_PENDING;
    Lin_SleepPending[logCh]=TRUE;

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
    uint8 logCh = HwChannelToChannel(Channel);
    /** @req SWS_Lin_00133 */
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (Lin_DrivStat != LIN_UNINIT), LIN_GO_TO_SLEEP_INTERNAL_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);

    /** @req SWS_Lin_00135 */
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_ARC_HW_UNIT_CNT), LIN_GO_TO_SLEEP_INTERNAL_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);

    /** @req SWS_Lin_00222 Software implemented */
    /** @req SWS_Lin_00037 */
    if (Lin_CfgPtr->LinChannelConfig[logCh].LinChannelWakeUpSupport == TRUE) {
            enableWakeupDetection(logCh);
    }

    /** @req SWS_Lin_00095 */
    /** @req SWS_Lin_00265 */
    Lin_ChanStat[logCh]=LIN_CH_SLEEP;
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
    uint8 logCh = HwChannelToChannel(Channel);
    /** @req SWS_Lin_00137 */
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (Lin_DrivStat != LIN_UNINIT), LIN_WAKE_UP_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);

    /** @req SWS_Lin_00139 */
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_ARC_HW_UNIT_CNT), LIN_WAKE_UP_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);
    /** @req SWS_Lin_00140 */
    /* @req SWS_Lin_00213 */
    VALIDATE_W_RV( (Lin_ChanStat[logCh] == LIN_CH_SLEEP), LIN_WAKE_UP_SERVICE_ID, LIN_E_STATE_TRANSITION, E_NOT_OK);

    if (Lin_CfgPtr->LinChannelConfig[logCh].LinChannelWakeUpSupport == TRUE) {
        disableWakeupDetection(Channel);
    }

    // Wakeup shall be 250us-5ms long.
    // For baudrate lower than 2k the baudrate must be reconfigured before sending wakeup.
  /*  if (Lin_CfgPtr->LinChannelConfig[Channel].LinChannelBaudRate < BAUD_RATE_2K) {
        setBaudrateFromDivisors(Channel, Lin_BaudrateSendWakeup.bdiv);
    }*/

    /** @req SWS_Lin_00043 */
    /** @req SWS_Lin_00209 */
    sendWakeup(Channel);

    /* @req SWS_Lin_00174 */
    Lin_ChanStat[logCh]=LIN_OPERATIONAL;

    return E_OK;
}

/**
 * Sets the channel state to operational without generating a wakeup pulse.
 * @param Channel
 * @return
 */
/** @req SWS_Lin_00256 */
Std_ReturnType   Lin_WakeupInternal(uint8 Channel) {
    uint8 logCh = HwChannelToChannel(Channel);
    /** @req SWS_Lin_00258 */
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (Lin_DrivStat != LIN_UNINIT), LIN_WAKE_UP_INTERNAL_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);
    /** @req SWS_Lin_00259 */
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_ARC_HW_UNIT_CNT), LIN_WAKE_UP_INTERNAL_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);
    /** @req SWS_Lin_00260 */
    /* @req SWS_Lin_00213 */
    VALIDATE_W_RV( (Lin_ChanStat[logCh] == LIN_CH_SLEEP), LIN_WAKE_UP_INTERNAL_SERVICE_ID, LIN_E_STATE_TRANSITION, E_NOT_OK);

    if (Lin_CfgPtr->LinChannelConfig[logCh].LinChannelWakeUpSupport == TRUE) {
        disableWakeupDetection(logCh);
    }

    /**@req SWS_Lin_00257 */
    /* @req SWS_Lin_00261 */
    /* @req SWS_Lin_00262 */
    Lin_ChanStat[logCh]=LIN_OPERATIONAL;
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
    uint8 logCh = HwChannelToChannel(Channel);

    /* @req SWS_Lin_00107 */
    VALIDATE_W_RV( (Lin_DrivStat != LIN_UNINIT), LIN_CHECKWAKEUP_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);
    /* @req SWS_Lin_00251 */
    VALIDATE_W_RV( (Channel < LIN_ARC_HW_UNIT_CNT), LIN_CHECKWAKEUP_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);

#if (LIN_REPORT_WAKEUP_SOURCE == STD_ON)
    chnCfg = &Lin_CfgPtr->LinChannelConfig[logCh];

    if ((chnCfg->LinChannelWakeUpSupport == TRUE) &&
        (chnCfg->LinChannelEcuWakeUpDefined == TRUE) &&
        Lin_WakeupSet[logCh])
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
    uint8 logCh = HwChannelToChannel(Channel);
    Std_ReturnType retval;

    /** @req SWS_Lin_00141*/
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (Lin_DrivStat != LIN_UNINIT), LIN_GETSTATUS_SERVICE_ID, LIN_E_UNINIT, LIN_NOT_OK);
    /** @req SWS_Lin_00143*/
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_ARC_HW_UNIT_CNT), LIN_GETSTATUS_SERVICE_ID, LIN_E_INVALID_CHANNEL, LIN_NOT_OK);
    /** @req SWS_Lin_00144*/
    /** @req SWS_Lin_00249 **/
    VALIDATE_W_RV( (Lin_SduPtr!=NULL), LIN_GETSTATUS_SERVICE_ID, LIN_E_PARAM_POINTER, LIN_NOT_OK);

    SchM_Enter_Lin_EA_0();
    Lin_StatusType res = Lin_ChanStat[logCh];

    /** @req SWS_Lin_00200 */
    switch (res) {
        case LIN_RX_OK:
            /** @req SWS_Lin_00092 */
            /** @!req SWS_Lin_00211 The receive frame processing is handled in the ISR */
            *Lin_SduPtr = Lin_BufTxRx[logCh];
            //lint -fallthrough
        case LIN_TX_OK:
            /** @req SWS_Lin_00238 */
            Lin_ChanStat[logCh]=LIN_OPERATIONAL;
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

            Lin_ChanStat[logCh]=LIN_OPERATIONAL;
            break;

        case LIN_CH_SLEEP_PENDING:
            /** @req SWS_Lin_00255 */
            /** @req SWS_Lin_00264 */
            res = Lin_ChanStat[logCh]=LIN_CH_SLEEP;
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
/*
 *
 * UART FUNCTIONS
 *
 *
 */

void Uart_EnableLoopback(uint8 hwChannel) {
    volatile Uart_reg* reg = Lin_HwChToPtr[hwChannel];
    reg->MCR_XON1 |= MCR_LOOPBACK_MASK;
}

void Uart_DisableLoopback(uint8 hwChannel) {
    volatile Uart_reg* reg = Lin_HwChToPtr[hwChannel];
    reg->MCR_XON1 &= ~MCR_LOOPBACK_MASK;
}

static void EnterModeA(uint8 hwChannel) {
    volatile Uart_reg* reg = Lin_HwChToPtr[hwChannel];
    uint32 val = reg->LCR & ~(0xFFU); /* Clear setting byte */
    reg->LCR = val | LCR_MODE_A_MASK;
}

static void EnterModeB(uint8 hwChannel) {
    volatile Uart_reg* reg = Lin_HwChToPtr[hwChannel];
    uint32 val = reg->LCR & ~(0xFFU); /* Clear setting byte */
    reg->LCR = val | LCR_MODE_B_MASK;
}

static void EnterSubmodeTlr(uint8 hwChannel) {
    volatile Uart_reg* reg = Lin_HwChToPtr[hwChannel];
    EnterModeB(hwChannel);
    reg->IIR_FCR_EFR |= EFR_ENHANCED_EN_MASK;
    EnterModeA(hwChannel);
    reg->MCR_XON1 |= MCR_ENABLE_TLR_MASK;
}

static void EnterModeOp(uint8 hwChannel) {
    volatile Uart_reg* reg = Lin_HwChToPtr[hwChannel];
    reg->LCR &= ~LCR_MODE_OP;
}


static void EnableChannel(uint8 hwCh) {
    *(uint32 *)UartClkCtrl[hwCh] |= 0x02UL;
}

void Uart_Init_Channel(uint8 hwCh, uint16 baudRate) {

    EnableChannel(hwCh);
    InitChannel(hwCh, baudRate);

    /* @req SWS_Lin_00155 */
#ifdef LIN_ARC_HW_UNIT_0_USED
    ISR_INSTALL_ISR2("Uart0Irq",LinInterruptUSART0 , (IrqType)UARTINT1_IRQ, 3, 0);
#endif
#ifdef LIN_ARC_HW_UNIT_1_USED
    ISR_INSTALL_ISR2("Uart1Irq",LinInterruptUSART1 , (IrqType)UARTINT2_IRQ, 3, 0);
#endif
#ifdef LIN_ARC_HW_UNIT_2_USED
    ISR_INSTALL_ISR2("Uart2Irq",LinInterruptUSART2 , (IrqType)UARTINT3_IRQ, 3, 0);
#endif
#ifdef LIN_ARC_HW_UNIT_3_USED
    ISR_INSTALL_ISR2("Uart3Irq",LinInterruptUSART3 , (IrqType)UARTINT4_IRQ, 3, 0);
#endif
#ifdef LIN_ARC_HW_UNIT_4_USED
    ISR_INSTALL_ISR2("Uart4Irq",LinInterruptUSART4 , (IrqType)UARTINT5_IRQ, 3, 0);
#endif
#ifdef LIN_ARC_HW_UNIT_5_USED
    ISR_INSTALL_ISR2("Uart5Irq",LinInterruptUSART5 , (IrqType)UARTINT6_IRQ, 3, 0);
#endif
#ifdef LIN_ARC_HW_UNIT_6_USED
    ISR_INSTALL_ISR2("Uart6Irq",LinInterruptUSART6 , (IrqType)UARTINT7_IRQ, 3, 0);
#endif
#ifdef LIN_ARC_HW_UNIT_7_USED
    ISR_INSTALL_ISR2("Uart7Irq",LinInterruptUSART7 , (IrqType)UARTINT8_IRQ, 3, 0);
#endif
#ifdef LIN_ARC_HW_UNIT_8_USED
    ISR_INSTALL_ISR2("Uart8Irq",LinInterruptUSART8 , (IrqType)UARTINT9_IRQ, 3, 0);
#endif
#ifdef LIN_ARC_HW_UNIT_9_USED
    ISR_INSTALL_ISR2("Uart9Irq",LinInterruptUSART9 , (IrqType)UARTINT10_IRQ, 3, 0);
#endif

}


static void InitChannel(uint8 channel, uint16 baudRate) {
    volatile Uart_reg* reg = Lin_HwChToPtr[channel];
    Timer_Init();
    /* Software reset */
    reg->SYSC = SYSC_RESET_MASK;
    while ((reg->SYSS & SYSS_RESET_PROGRESS_MASK) == 0u) {}


    /* No need to set DMA mode - on reset, SCR[0] == 0 and FCR[3] == 0,
     which means no DMA */
    reg->IIR_FCR_EFR |= FCR_ENABLE_DMA_MASK;

    /* Configure FIFO queue trigger levels */
    EnterSubmodeTlr(channel);
    /* After reset, FCR[7:6] and [5:4] == 0, meaning trigger level is
     8 spaces for both TX and RX FIFOs. This suits us, only need to
     program the triggers in TLR */
    reg->TLR_SPR_XOFF2 |= TLR_RX_TRIGGER_1_MASK;
    reg->TLR_SPR_XOFF2 |= TLR_TX_TRIGGER_1_MASK;

    //reg->SCR |= 0xC0;
    //reg->IIR_FCR_EFR |= 0x50;

    /*Start of protocol configuration */
    reg->MDR1 |= MDR1_DISABLE_UART_MASK;
    waitAndReset(channel);

    EnterModeB(channel);
    reg->IIR_FCR_EFR |= EFR_ENHANCED_EN_MASK;
    EnterModeOp(channel);
    reg->IIR_FCR_EFR &= ~(IER_SLEEP_BIT);
    EnterModeB(channel);


    /* Clock: we'll be operating in 16X mode, therefore:
     divisor = freq / (16 * baudRate) */
    uint32 divisor = UART_FIXED_CLOCK_RATE / (16 * baudRate);
    if (divisor == 0) {
        divisor = 156; /* Failsafe: to 19.2 kbps */
    }
    reg->THR_RHR_DLL = divisor;

    /* If desired to change character length - put the code here */
    reg->LCR |= 0x3U;

    /* Enable RX and TX interrupts */
    EnterModeOp(channel); /* Closes divisor latch */
    reg->IER_DLH = IER_RHR_IT_MASK;
    //reg->IER_DLH |= IER_THR_IT_MASK;
    reg->IIR_FCR_EFR |= FCR_ENABLE_FIFO_MASK;

    /* Finalize - clear Break bit and enable the driver */
    reg->LCR &= ~LCR_BREAK_BIT;
    reg->SCR |= 0x08U;

    reg->MDR1 &= ~MDR1_DISABLE_UART_MASK; /* Gives 16x mode */
    waitAndReset(channel);

    /* clear bit in RHR register */
     while ((reg->LSR_XON2 & 0x06U) != 0) {
         uint8 dummy = reg->THR_RHR_DLL; /*lint !e734 loss of precision acceptable*/
         (void) dummy;
     }
    /* We don't need no flow control */
}

static void waitAndReset(uint8 hwCh) {
    uint32 regVal;

    volatile Uart_reg* reg = Lin_HwChToPtr[hwCh];

    Timer_uDelay(1);
#if 0
    uint32_t refclock;
    refclock = Timer_GetTicks() + 65U;

    /** Wait for 5 M4 clock cycles and approximately 5 uart cycles **/
    while (Timer_GetTicks() < (refclock)) { /** NEEDS BETTER FIX **/
    }
#endif
    /** Clear RX and TX FIFO **/
    regVal = reg->IIR_FCR_EFR;
    reg->IIR_FCR_EFR = regVal & 0x00000006UL;
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


