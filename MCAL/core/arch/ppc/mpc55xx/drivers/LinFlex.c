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

/** @tagSettings DEFAULT_ARCHITECTURE=PPC|MPC5607B|MPC5645S|MPC5748G|MPC5747C */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#include "Lin.h"
#include "LinIf_Cbk.h"
#include "mpc55xx.h"
#include "LinFlex_Common.h"
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
#if defined(USE_DET)
#include "Det.h"
#else
#error Lin: Need to add DET module when LinDevErrorDetect is enabled
#endif
#endif
#include "Mcu.h"
#include <stdlib.h>
#include <string.h>
#include "LinIf_Cbk.h"
#include "SchM_Lin.h"
#include "isr.h"
#include "irq.h"
#include "arc.h"

/** General requirements tagging */
/* @req SWS_Lin_00103 */
/* @req SWS_Lin_00013 */
/* @req SWS_Lin_00014 */
/* @req SWS_Lin_00015 */
/* @req SWS_Lin_00156 */
/* @req SWS_Lin_00017 */
/* @req SWS_Lin_00018 */
/* @req SWS_Lin_00019 */
/* @req SWS_Lin_00184 */
/* @req SWS_Lin_00207 */
/* @req SWS_Lin_00224 */
/* @req SWS_Lin_00225 */
/* @req SWS_Lin_00235 */
/* @req SWS_Lin_00237 */
/* @req SWS_Lin_00239 */
/* @req SWS_Lin_00240 */
/* @req SWS_Lin_00027 */
/* @req SWS_Lin_00028 */
/* @req SWS_Lin_00029 */
/* @req SWS_Lin_00045 */
/* @req SWS_Lin_00005 */
/* @req SWS_Lin_00055 */


#define LIN_MAX_MSG_LENGTH 8
#if defined(CFG_MPC5744P)
static volatile struct LINFLEX_tag * const _LINFLEX[] = {&LINFlexD_0, &LINFlexD_1};
#define LINFLEX(exp) _LINFLEX[exp]
#elif defined(CFG_MPC5777M)
static volatile struct LINFLEX_tag * const _LINFLEX[] = {&LINFlexD_0, &LINFlexD_1, &LINFlexD_2, [14] = &LINFlexD_14, [15] = &LINFlexD_15, [16] = &LINFlexD_16};
#define LINFLEX(exp) _LINFLEX[exp]
#elif defined(CFG_MPC5748G) || defined(CFG_MPC5747C)
static volatile struct LINFLEX_tag * const _LINFLEX[] = {&LINFlexD_0, &LINFlexD_1, &LINFlexD_2, &LINFlexD_3, &LINFlexD_4, &LINFlexD_5,
                                                         &LINFlexD_6, &LINFlexD_7, &LINFlexD_8 ,&LINFlexD_9, &LINFlexD_10, &LINFlexD_11,
                                                         &LINFlexD_12, &LINFlexD_13, &LINFlexD_14, &LINFlexD_15, &LINFlexD_16, &LINFlexD_17};
#define LINFLEX(exp) _LINFLEX[exp]
#elif defined(CFG_MPC5746C)
/*lint -e{923} OTHER required operation */
static volatile struct LINFLEX_tag * const _LINFLEX[] = {&LINFlexD_0, &LINFlexD_1, &LINFlexD_2, &LINFlexD_3, &LINFlexD_4, &LINFlexD_5,
                                                         &LINFlexD_6, &LINFlexD_7, &LINFlexD_8 ,&LINFlexD_9, &LINFlexD_10, &LINFlexD_11,
                                                         &LINFlexD_12, &LINFlexD_13, &LINFlexD_14, &LINFlexD_15};
#define LINFLEX(exp) _LINFLEX[exp]
#else
#define LINFLEX(exp) (volatile struct LINFLEX_tag *)(0xFFE40000uL + (0x4000uL * exp))
#endif

#define NBR_DATA_BYTES  8u

#define MASK_LINCR2_DDRQ    (uint32)0x800UL
#define MASK_LINCR2_ABRQ    (uint32)0x200UL
#define MAX_WAIT_CYCLES     (uint32)10000UL
#define MASK_FRAME_ID       0x3FU

/* Reset -> LIN_UNINIT: After reset, the Lin module shall set its state to LIN_UNINIT. */
/* @req SWS_Lin_00145 */
static Lin_DriverStatusType LinDriverStatus = LIN_UNINIT;

static Lin_StatusType LinChannelStatus[LIN_CONTROLLER_CNT];
static Lin_StatusType LinChannelOrderedStatus[LIN_CONTROLLER_CNT];

static const Lin_ConfigType* LinConfigPtr = (Lin_ConfigType*)0;

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

#define LIN_DET_REPORT_ERROR(_api, _err)    (void)Det_ReportError(LIN_MODULE_ID,0,_api,_err)
#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_W_RV(_exp,_api,_err,_rv )
#define LIN_DET_REPORT_ERROR(_api, _err)
#endif

static Std_ReturnType waitWhileBusy(volatile const uint32 *regBaseAddr, uint32 mask, boolean retCondition);
#if defined (CFG_MPC5606S)
static void waitSomeCycles(void);
#endif

static Std_ReturnType resyncDriver(uint8 Channel)
{
    /* In case we need to re-init or re-sync driver because of error or hangup it should be done here */
    /*lint -e{923,9033} Hardware access */
    volatile struct LINFLEX_tag * LINFLEXHw = LINFLEX(LinConfigPtr->LinChannelConfig[Channel].LinChannelId);

    //abort current transmission and reception
    if (LinChannelStatus[Channel] == LIN_TX_BUSY) {
        LINFLEXHw->LINCR2.B.ABRQ =1;
#if !defined(CFG_MPC5606S)
        //Wait until abort is completed before sending a new frame
        if (E_NOT_OK == waitWhileBusy(&LINFLEXHw->LINCR2.R, MASK_LINCR2_ABRQ, FALSE)) {
            /*lint -e{904} OTHER to increase readability */
            return E_NOT_OK;
        }
#else
        /* Note: Do not rely on reading LINFLEXHw->LINCR2.B.DDRQ, LINFLEXHw->LINCR2.B.HTRQ or LINFLEXHw->LINCR2.B.ABRQ because in
         * some PPC devices like MPC5606s reading this bit results in undesired results (only write-able).
         */
        waitSomeCycles(); /* This delay is necessary to ensure that abort is completed. This is tested in MCAL tests */
#endif
    }
    else if (LinChannelStatus[Channel] == LIN_RX_BUSY) {
#if !defined(CFG_MPC5606S)
        //Check if header transmission is still ongoing
        if (LINFLEXHw->LINCR2.B.HTRQ != 0) {
            //Request for abort
            LINFLEXHw->LINCR2.B.ABRQ =1;

            //Wait until abort is completed
            if (E_NOT_OK == waitWhileBusy(&LINFLEXHw->LINCR2.R, MASK_LINCR2_ABRQ, FALSE)) {
                /*lint -e{904} OTHER to increase readability */
                return E_NOT_OK;
            }
        }
        //Check whether there is ongoing reception
        else if (LINFLEXHw->LINSR.B.RBSY != 0) {
#else
        /* Note: Do not rely on reading LINFLEXHw->LINCR2.B.DDRQ, LINFLEXHw->LINCR2.B.HTRQ or LINFLEXHw->LINCR2.B.ABRQ because in
        * some PPC devices like MPC5606s reading this bit results in undesired results (only write-able).
        */
        LINFLEXHw->LINCR2.B.ABRQ =1;
        waitSomeCycles(); /* This delay is necessary to ensure that abort is completed. This is tested in MCAL tests */

        if (LINFLEXHw->LINSR.B.RBSY != 0) {
#endif
            //Request for discarding the received data
            LINFLEXHw->LINCR2.B.DDRQ =1;
#if !defined(CFG_MPC5606S)
            //Wait until discard request is completed
            if (E_NOT_OK == waitWhileBusy(&LINFLEXHw->LINCR2.R, MASK_LINCR2_DDRQ, FALSE)) {
                /*lint -e{904} OTHER to increase readability */
                return E_NOT_OK;
            }
#else
            /* Note: Do not rely on reading LINFLEXHw->LINCR2.B.DDRQ, LINFLEXHw->LINCR2.B.HTRQ or LINFLEXHw->LINCR2.B.ABRQ because in
             * some PPC devices like MPC5606s reading this bit results in undesired results (only write-able).
             */
            waitSomeCycles(); /* This delay is necessary to ensure that abort is completed. This is tested in MCAL tests */
#endif
        }
        else {
            /* Nothing to do */
        }
    }
    else {
        /* Nothing to do */
    }

    //reset status and error status registers
    LINFLEXHw->LINSR.R = 0xfffuL; /* Do not change Lin Mode register field */
    LINFLEXHw->LINESR.R= 0xffffffffuL;

    return E_OK;
}

#if defined (CFG_MPC5606S)
/** @brief This function provides some delay
*
*/
static void waitSomeCycles(void) {
    uint32 n;

    for (n = 0; n < MAX_WAIT_CYCLES ; n++) {

    }
}
#endif

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

/* @req SWS_Lin_00060 */
static void linInterruptRx(uint8 hwId) /*lint -e{957} No prototypes for interrupts */
{
    /*lint -e{923,9033} Hardware access */
    volatile struct LINFLEX_tag * LINFLEXHw = LINFLEX(hwId);
    uint8 Channel = LinConfigPtr->Lin_HwId2ChannelMap[hwId];

    if (1 == LINFLEXHw->LINSR.B.DRF) {
        /* Clear flags */
        /* @req SWS_Lin_00157 */
        LINFLEXHw->LINSR.B.DRF = 1;

        if (LinChannelStatus[Channel]==LIN_RX_BUSY) {
            /* receive complete */
            LinChannelStatus[Channel] = LIN_RX_OK;
         }
    }else{
        /* Other interrupt cause */
        LINFLEXHw->LINSR.R = 0xffffffffuL;
        if (LinChannelStatus[Channel]==LIN_RX_BUSY) {
            LinChannelStatus[Channel] = LIN_RX_ERROR;
         }
    }
}

static void linInterruptTx(uint8 hwId) /*lint -e{957} No prototypes for interrupts */
{
    /*lint -e{923,9033} Hardware access */
    volatile struct LINFLEX_tag * LINFLEXHw = LINFLEX(hwId);
    uint8 Channel = LinConfigPtr->Lin_HwId2ChannelMap[hwId];

    if (1 == LINFLEXHw->LINSR.B.DTF) {
        /* Clear flags */
        /* @req SWS_Lin_00157 */
        LINFLEXHw->LINSR.B.DTF = 1;

        if (LinChannelStatus[Channel]==LIN_TX_BUSY) {
            /* transmit complete */
            LinChannelStatus[Channel] = LIN_TX_OK;
        }
    }else{
        /* Other interrupt cause */
        LINFLEXHw->LINSR.R = 0xffffffffuL;
        if (LinChannelStatus[Channel]==LIN_TX_BUSY) {
            LinChannelStatus[Channel] = LIN_TX_ERROR;
        }
    }

    if (LIN_CH_SLEEP_PENDING == LinChannelOrderedStatus[Channel]) {

        /** @req SWS_Lin_00221*/
        /* @req SWS_Lin_00032 */
        //Enter power saving mode
        LINFLEXHw->LINCR1.B.SLEEP = 1;

        /** @req SWS_Lin_00266*/
        LinChannelStatus[Channel] = LIN_CH_SLEEP_PENDING;
        LinChannelOrderedStatus[Channel]=LIN_OPERATIONAL;
    }

}

static void linInterruptErr(uint8 hwId) /*lint -e{957} No prototypes for interrupts */
{
    /*lint -e{923,9033} Hardware access */
    volatile struct LINFLEX_tag * LINFLEXHw = LINFLEX(hwId);
    uint8 Channel = LinConfigPtr->Lin_HwId2ChannelMap[hwId];

    /* Error handling */
    if (LIN_CH_SLEEP_PENDING == LinChannelOrderedStatus[Channel]) {

        /** @req SWS_Lin_00221*/
        /* @req SWS_Lin_00032 */
        //Enter power saving mode
        LINFLEXHw->LINCR1.B.SLEEP = 1;

        /** @req SWS_Lin_00266*/
        LinChannelStatus[Channel] = LIN_CH_SLEEP_PENDING;
        LinChannelOrderedStatus[Channel]=LIN_OPERATIONAL;
    }
    else if(LinChannelStatus[Channel]==LIN_RX_BUSY){
        //Header error when Parity, Bit error, Break delimiter error or synch field error flag is set
        /*lint -e{9007} No side effects */
        if ((LINFLEXHw->LINESR.B.IDPEF != 0) || (LINFLEXHw->LINESR.B.BEF != 0) || (LINFLEXHw->LINESR.B.BDEF != 0) || (LINFLEXHw->LINESR.B.SFEF != 0)) {
            LinChannelStatus[Channel] = LIN_TX_HEADER_ERROR;
        }
        //OCF indicates a response timeout
        else if (LINFLEXHw->LINESR.B.OCF != 0) {
            LinChannelStatus[Channel] = LIN_RX_NO_RESPONSE;
            /* Must be set to init mode to clear this flag */
            LINFLEXHw->LINCR1.B.INIT = 1;
            LINFLEXHw->LINCR1.B.INIT = 0;
        }
        else  {
            LinChannelStatus[Channel] = LIN_RX_ERROR;
        }

    }else if (LinChannelStatus[Channel]==LIN_TX_BUSY){
        //Bit error is ignored here since it can occur during header or data transmission
        /*lint -e{9007} No side effects */
        if ((LINFLEXHw->LINESR.B.IDPEF != 0) || (LINFLEXHw->LINESR.B.BDEF != 0) || (LINFLEXHw->LINESR.B.SFEF != 0)) {
            LinChannelStatus[Channel] = LIN_TX_HEADER_ERROR;
        }
        else {
            LinChannelStatus[Channel] = LIN_TX_ERROR;
        }
        /* If an error is detected the transmission shall be aborted */
        LINFLEXHw->LINCR2.B.ABRQ =1;
    }
    else {
        /* Nothing to do */
    }


    /* @req SWS_Lin_00157 */
    /* Clear flags  */
    LINFLEXHw->LINESR.R=0xffffffffuL;
}

/*lint -save -e957 No prototypes for interrupts */
#ifdef LIN_CHANNEL_0_USED
ISR(LinInterruptRxA){linInterruptRx(0);}
ISR(LinInterruptTxA){linInterruptTx(0);}
ISR(LinInterruptErrA){linInterruptErr(0);}
#endif

#ifdef LIN_CHANNEL_1_USED
ISR(LinInterruptRxB){linInterruptRx(1);}
ISR(LinInterruptTxB){linInterruptTx(1);}
ISR(LinInterruptErrB){linInterruptErr(1);}
#endif

#ifdef LIN_CHANNEL_2_USED
ISR(LinInterruptRxC){linInterruptRx(2);}
ISR(LinInterruptTxC){linInterruptTx(2);}
ISR(LinInterruptErrC){linInterruptErr(2);}
#endif

#ifdef LIN_CHANNEL_3_USED
ISR(LinInterruptRxD){linInterruptRx(3);}
ISR(LinInterruptTxD){linInterruptTx(3);}
ISR(LinInterruptErrD){linInterruptErr(3);}
#endif

#ifdef LIN_CHANNEL_4_USED
ISR(LinInterruptRxE){linInterruptRx(4);}
ISR(LinInterruptTxE){linInterruptTx(4);}
ISR(LinInterruptErrE){linInterruptErr(4);}
#endif

#ifdef LIN_CHANNEL_5_USED
ISR(LinInterruptRxF){linInterruptRx(5);}
ISR(LinInterruptTxF){linInterruptTx(5);}
ISR(LinInterruptErrF){linInterruptErr(5);}
#endif

#ifdef LIN_CHANNEL_6_USED
ISR(LinInterruptRxG){linInterruptRx(6);}
ISR(LinInterruptTxG){linInterruptTx(6);}
ISR(LinInterruptErrG){linInterruptErr(6);}
#endif

#ifdef LIN_CHANNEL_7_USED
ISR(LinInterruptRxH){linInterruptRx(7);}
ISR(LinInterruptTxH){linInterruptTx(7);}
ISR(LinInterruptErrH){linInterruptErr(7);}
#endif

#ifdef LIN_CHANNEL_8_USED
ISR(LinInterruptRx8){linInterruptRx(8);}
ISR(LinInterruptTx8){linInterruptTx(8);}
ISR(LinInterruptErr8){linInterruptErr(8);}
#endif

#ifdef LIN_CHANNEL_9_USED
ISR(LinInterruptRx9){linInterruptRx(9);}
ISR(LinInterruptTx9){linInterruptTx(9);}
ISR(LinInterruptErr9){linInterruptErr(9);}
#endif

#ifdef LIN_CHANNEL_10_USED
ISR(LinInterruptRx10){linInterruptRx(10);}
ISR(LinInterruptTx10){linInterruptTx(10);}
ISR(LinInterruptErr10){linInterruptErr(10);}
#endif

#ifdef LIN_CHANNEL_11_USED
ISR(LinInterruptRx11){linInterruptRx(11);}
ISR(LinInterruptTx11){linInterruptTx(11);}
ISR(LinInterruptErr11){linInterruptErr(11);}
#endif

#ifdef LIN_CHANNEL_12_USED
ISR(LinInterruptRx12){linInterruptRx(12);}
ISR(LinInterruptTx12){linInterruptTx(12);}
ISR(LinInterruptErr12){linInterruptErr(12);}
#endif

#ifdef LIN_CHANNEL_13_USED
ISR(LinInterruptRx13){linInterruptRx(13);}
ISR(LinInterruptTx13){linInterruptTx(13);}
ISR(LinInterruptErr13){linInterruptErr(13);}
#endif

#ifdef LIN_CHANNEL_14_USED
ISR(LinInterruptRx14){linInterruptRx(14);}
ISR(LinInterruptTx14){linInterruptTx(14);}
ISR(LinInterruptErr14){linInterruptErr(14);}
#endif

#ifdef LIN_CHANNEL_15_USED
ISR(LinInterruptRx15){linInterruptRx(15);}
ISR(LinInterruptTx15){linInterruptTx(15);}
ISR(LinInterruptErr15){linInterruptErr(15);}
#endif

#ifdef LIN_CHANNEL_16_USED
ISR(LinInterruptRx16){linInterruptRx(16);}
ISR(LinInterruptTx16){linInterruptTx(16);}
ISR(LinInterruptErr16){linInterruptErr(16);}
#endif

#ifdef LIN_CHANNEL_17_USED
ISR(LinInterruptRx17){linInterruptRx(17);}
ISR(LinInterruptTx17){linInterruptTx(17);}
ISR(LinInterruptErr17){linInterruptErr(17);}
#endif
/*lint -restore */

/** @req SWS_Lin_00006 */
void Lin_Init( const Lin_ConfigType* Config )
{/*lint !e9046 Lin_Init and LIN_INIT are in the AutoSAR specification. */
    Std_ReturnType retval;

    LinConfigPtr = Config;
    enum
    {
      LIN_PRIO = 3
    };

    /** @req SWS_Lin_00105 **/
    /* @req SWS_Lin_00213 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE( (LinDriverStatus == LIN_UNINIT), LIN_INIT_SERVICE_ID, LIN_E_STATE_TRANSITION );
    /** @req SWS_Lin_00099 **/
    /** @req SWS_Lin_00216 **/
    VALIDATE( (Config!=NULL), LIN_INIT_SERVICE_ID, LIN_E_INVALID_POINTER );
    /*lint -restore */

    /* Install the interrupt */
    /* @req SWS_Lin_00155 */
    #ifdef LIN_CHANNEL_0_USED
    ISR_INSTALL_ISR2("LinIsrRxA", LinInterruptRxA, (int16_t)(LINFLEX_0_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTxA", LinInterruptTxA, (int16_t)(LINFLEX_0_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErrA", LinInterruptErrA, (int16_t)(LINFLEX_0_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_1_USED
    ISR_INSTALL_ISR2("LinIsrRxB", LinInterruptRxB, (int16_t)(LINFLEX_1_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTxB", LinInterruptTxB, (int16_t)(LINFLEX_1_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErrB", LinInterruptErrB, (int16_t)(LINFLEX_1_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_2_USED
    ISR_INSTALL_ISR2("LinIsrRxC", LinInterruptRxC, (int16_t)(LINFLEX_2_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTxC", LinInterruptTxC, (int16_t)(LINFLEX_2_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErrC", LinInterruptErrC, (int16_t)(LINFLEX_2_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_3_USED
    ISR_INSTALL_ISR2("LinIsrRxD", LinInterruptRxD, (int16_t)(LINFLEX_3_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTxD", LinInterruptTxD, (int16_t)(LINFLEX_3_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErrD", LinInterruptErrD, (int16_t)(LINFLEX_3_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_4_USED
    ISR_INSTALL_ISR2("LinIsrRxE", LinInterruptRxE, (int16_t)(LINFLEX_4_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTxE", LinInterruptTxE, (int16_t)(LINFLEX_4_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErrE", LinInterruptErrE, (int16_t)(LINFLEX_4_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_5_USED
    ISR_INSTALL_ISR2("LinIsrRxF", LinInterruptRxF, (int16_t)(LINFLEX_5_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTxF", LinInterruptTxF, (int16_t)(LINFLEX_5_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErrF", LinInterruptErrF, (int16_t)(LINFLEX_5_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_6_USED
    ISR_INSTALL_ISR2("LinIsrRxG", LinInterruptRxG, (int16_t)(LINFLEX_6_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTxG", LinInterruptTxG, (int16_t)(LINFLEX_6_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErrG", LinInterruptErrG, (int16_t)(LINFLEX_6_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_7_USED
    ISR_INSTALL_ISR2("LinIsrRxH", LinInterruptRxH, (int16_t)(LINFLEX_7_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTxH", LinInterruptTxH, (int16_t)(LINFLEX_7_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErrH", LinInterruptErrH, (int16_t)(LINFLEX_7_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_8_USED
    ISR_INSTALL_ISR2("LinIsrRx8", LinInterruptRx8, (int16_t)(LINFLEX_8_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTx8", LinInterruptTx8, (int16_t)(LINFLEX_8_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErr8", LinInterruptErr8, (int16_t)(LINFLEX_8_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_9_USED
    ISR_INSTALL_ISR2("LinIsrRx9", LinInterruptRx9, (int16_t)(LINFLEX_9_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTx9", LinInterruptTx9, (int16_t)(LINFLEX_9_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErr9", LinInterruptErr9, (int16_t)(LINFLEX_9_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_10_USED
    ISR_INSTALL_ISR2("LinIsrRx10", LinInterruptRx10, (int16_t)(LINFLEX_10_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTx10", LinInterruptTx10, (int16_t)(LINFLEX_10_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErr10", LinInterruptErr10, (int16_t)(LINFLEX_10_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_11_USED
    ISR_INSTALL_ISR2("LinIsrRx11", LinInterruptRx11, (int16_t)(LINFLEX_11_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTx11", LinInterruptTx11, (int16_t)(LINFLEX_11_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErr11", LinInterruptErr11, (int16_t)(LINFLEX_11_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_12_USED
    ISR_INSTALL_ISR2("LinIsrRx12", LinInterruptRx12, (int16_t)(LINFLEX_12_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTx12", LinInterruptTx12, (int16_t)(LINFLEX_12_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErr12", LinInterruptErr12, (int16_t)(LINFLEX_12_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_13_USED
    ISR_INSTALL_ISR2("LinIsrRx13", LinInterruptRx13, (int16_t)(LINFLEX_13_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTx13", LinInterruptTx13, (int16_t)(LINFLEX_13_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErr13", LinInterruptErr13, (int16_t)(LINFLEX_13_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_14_USED
    ISR_INSTALL_ISR2("LinIsrRx14", LinInterruptRx14, (int16_t)(LINFLEX_14_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTx14", LinInterruptTx14, (int16_t)(LINFLEX_14_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErr14", LinInterruptErr14, (int16_t)(LINFLEX_14_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_15_USED
    ISR_INSTALL_ISR2("LinIsrRx15", LinInterruptRx15, (int16_t)(LINFLEX_15_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTx15", LinInterruptTx15, (int16_t)(LINFLEX_15_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErr15", LinInterruptErr15, (int16_t)(LINFLEX_15_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_16_USED
    ISR_INSTALL_ISR2("LinIsrRx16", LinInterruptRx16, (int16_t)(LINFLEX_16_RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTx16", LinInterruptTx16, (int16_t)(LINFLEX_16_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErr16", LinInterruptErr16, (int16_t)(LINFLEX_16_ERR),LIN_PRIO, 0);
    #endif
    #ifdef LIN_CHANNEL_17_USED
    ISR_INSTALL_ISR2("LinIsrRx17", LinInterruptRx17, (int16_t)(LINFLEX_17RXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrTx17", LinInterruptTx17, (int16_t)(LINFLEX_17_TXI),LIN_PRIO, 0);
    ISR_INSTALL_ISR2("LinIsrErr17", LinInterruptErr17, (int16_t)(LINFLEX_17_ERR),LIN_PRIO, 0);
    #endif
    /* Initialize the hardware specifics for each supported channel */
    /** @req SWS_Lin_00190 */
    /** @req SWS_Lin_00008 */
    /* @req SWS_Lin_00084 */
    for (uint8 ctrl =0; ctrl < LIN_CONTROLLER_CNT; ctrl++) {
        retval = LinFlex_Common_Init(&LinConfigPtr->LinChannelConfig[ctrl], LIN_MASTER);
        if (E_NOT_OK == retval) {
            //Abort initialization
            /*lint -e{904} PERFORMANCE reduce cyclomatic complexity and increase readability */
            return;
        }

        /** @req SWS_Lin_00171 */
        LinChannelStatus[ctrl]=LIN_OPERATIONAL;
        LinChannelOrderedStatus[ctrl]=LIN_OPERATIONAL;
    }
    /** @req SWS_Lin_00146 */
    /* LIN_UNINIT -> LIN_INIT: The Lin module shall transition from LIN_UNINIT
     * to LIN_INIT when the function Lin_Init is called. */
    LinDriverStatus = LIN_INIT;
}

void Lin_Arc_DeInit(void)
{
  LinDriverStatus = LIN_UNINIT;
  for (uint8 ctrl =0; ctrl < LIN_CONTROLLER_CNT; ctrl++) {
      /*lint -e{923,9033} Hardware access */
      //volatile struct LINFLEX_tag * LINFLEXHw = LINFLEX(LinConfigPtr->LinChannelConfig[ctrl].LinChannelId);

          if(LinChannelStatus[ctrl] != LIN_CH_UNINIT){
              if(LinConfigPtr != NULL) {
                  LinFlex_Common_DeInit(&LinConfigPtr->LinChannelConfig[ctrl]);
              }
              LinChannelStatus[ctrl]=LIN_CH_UNINIT;
          }
  }
}

#if (LIN_VERSION_INFO_API == STD_ON)
/** @req SWS_Lin_00161 **/
/** @reqSWS_Lin_00001 **/
void Lin_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    /** @req SWS_Lin_00248 **/
    /** @req SWS_Lin_00249 **/
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE( !(versioninfo == NULL), LIN_GETVERSIONINFO_SERVICE_ID, LIN_E_PARAM_POINTER );

    /** @req SWS_Lin_00001 **/
    versioninfo->vendorID = LIN_VENDOR_ID;
    versioninfo->moduleID = LIN_MODULE_ID;
    versioninfo->sw_major_version = LIN_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = LIN_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = LIN_SW_PATCH_VERSION;
}
#endif

/** @req SWS_Lin_00191 */
Std_ReturnType Lin_SendFrame(  uint8 Channel,  Lin_PduType* PduInfoPtr ) /*lint -e{818} Follows AUTOSAR API spec */
{
    Std_ReturnType retval;

    /** @req SWS_Lin_00195 */
    /** @req SWS_Lin_00214 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_W_RV( (LinDriverStatus != LIN_UNINIT), LIN_SEND_FRAME_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);

    /** @req SWS_Lin_00197 */
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_SEND_FRAME_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);
    /* Send header is used to wake the net in this implementation(no actual header is sent */
    /** @req SWS_Lin_00199 */
    /* @req SWS_Lin_00213 */
    VALIDATE_W_RV( (LinChannelStatus[Channel] != LIN_CH_SLEEP), LIN_SEND_FRAME_SERVICE_ID, LIN_E_STATE_TRANSITION, E_NOT_OK);
    /** @req SWS_Lin_00198 */
    /** @req SWS_Lin_00249 **/
    VALIDATE_W_RV( (PduInfoPtr != NULL), LIN_SEND_FRAME_SERVICE_ID, LIN_E_PARAM_POINTER, E_NOT_OK);
    /*lint -restore */

    /*lint -e{923,9033} Hardware access */
    volatile struct LINFLEX_tag * LINFLEXHw = LINFLEX(LinConfigPtr->LinChannelConfig[Channel].LinChannelId);
    /** @req SWS_Lin_00021 */
    /* @req SWS_Lin_00074 */
    SchM_Enter_Lin_EA_0();
    if( (LinChannelStatus[Channel] == LIN_TX_BUSY) || (LinChannelStatus[Channel] == LIN_TX_ERROR) ||
       (LinChannelStatus[Channel] == LIN_RX_BUSY) || (LinChannelStatus[Channel] == LIN_RX_ERROR) ||
       (LinChannelStatus[Channel] == LIN_RX_NO_RESPONSE) || (LinChannelStatus[Channel] ==LIN_TX_HEADER_ERROR) )
    {
        retval = resyncDriver(Channel);
        if (E_NOT_OK == retval) {
            /*lint -e{904} PERFORMANCE reduce cyclomatic complexity and increase readability */
            return E_NOT_OK;
        }
        LinChannelStatus[Channel]=LIN_OPERATIONAL;
    }
    SchM_Exit_Lin_EA_0();

    /* @req SWS_Lin_00194 */

    LINFLEXHw->BIDR.R = 0; /* Clear reg */

    /** @req SWS_Lin_00192 */
    /* Checksum */
    if (PduInfoPtr->Cs != LIN_ENHANCED_CS){ /*Frame identifiers 60 (0x3C) to 61 (0x3D) shall always use classic checksum */
        LINFLEXHw->BIDR.B.CCS = 1;
    }
    /* Length */
    LINFLEXHw->BIDR.B.DFL = PduInfoPtr->DI - 1;

    /* Id */
    LINFLEXHw->BIDR.B.ID = (MASK_FRAME_ID & PduInfoPtr->Pid); /* ID field = 6bits frame Id;parity bits are automatically calculated by driver */

    /* Direction */
    if (PduInfoPtr->Drc == LIN_MASTER_RESPONSE)
    {
        LINFLEXHw->BIDR.B.DIR = 1;

        /*@req SWS_Lin_00053 */
        retval = LinFlex_Common_WriteDataBufToHwReg(PduInfoPtr->DI, PduInfoPtr->SduPtr, LINFLEXHw);
        /*lint -e{904} ARGUMENT_CHECK */
        VALIDATE_W_RV( (E_OK == retval), LIN_SEND_FRAME_SERVICE_ID, LIN_E_INVALID_POINTER, E_NOT_OK);

        LinChannelStatus[Channel]=LIN_TX_BUSY;
    }
    else
    {
        /** @req SWS_Lin_00193 */
        LinChannelStatus[Channel]=LIN_RX_BUSY;
    }

    /* Request transmission of header */
    LINFLEXHw->LINCR2.B.HTRQ = 1;

    return E_OK;
}

/**@req SWS_Lin_00166 */
Std_ReturnType Lin_GoToSleep(  uint8 Channel )
{
    Lin_PduType PduInfo;

    uint8 data[8] = {0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

    /** @req SWS_Lin_00129*/
    /** @req SWS_Lin_00214 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_W_RV( (LinDriverStatus != LIN_UNINIT), LIN_GO_TO_SLEEP_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);

    /** @req SWS_Lin_00131*/
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_GO_TO_SLEEP_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);
    /*lint -restore*/

    //Send sleep command on bus
    PduInfo.Cs = LIN_CLASSIC_CS;
    PduInfo.Pid = 0x3C;
    PduInfo.SduPtr = data;
    PduInfo.DI = 8;
    PduInfo.Drc = LIN_MASTER_RESPONSE;
    /** @req SWS_Lin_00089 */
    /** @req SWS_Lin_00074 */ //Cancellation of previous send in done in Lin_SendFrame Api
    Lin_SendFrame(Channel,  &PduInfo); /*lint !e534 According to SWS_Lin_00266 action is same regardless of return value */


    /* @req SWS_Lin_00033 */
    /* @req SWS_Lin_00263 */
    LinChannelOrderedStatus[Channel]=LIN_CH_SLEEP_PENDING;

    return E_OK;
}

/** @req SWS_Lin_00167 */
Std_ReturnType Lin_GoToSleepInternal(  uint8 Channel )
{
    /** @req SWS_Lin_00133 */
    /** @req SWS_Lin_00214 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_W_RV( (LinDriverStatus != LIN_UNINIT), LIN_GO_TO_SLEEP_INTERNAL_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);

    /** @req SWS_Lin_00135 */
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_GO_TO_SLEEP_INTERNAL_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);
    /*lint -restore*/

    LinFlex_Common_GoToSleepInternal(&LinConfigPtr->LinChannelConfig[Channel]);

    /** @req SWS_Lin_00095 */
    /** @req SWS_Lin_00265 */
    LinChannelStatus[Channel]=LIN_CH_SLEEP;
    LinChannelOrderedStatus[Channel]=LIN_OPERATIONAL;
    return E_OK;
}

/** @req SWS_Lin_00169 */
Std_ReturnType Lin_Wakeup( uint8 Channel )
{
    Std_ReturnType retval;

    /** @req SWS_Lin_00137 */
    /** @req SWS_Lin_00214 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_W_RV( (LinDriverStatus != LIN_UNINIT), LIN_WAKE_UP_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);

    /** @req SWS_Lin_00139 */
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_WAKE_UP_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);
    /** @req SWS_Lin_00140 */
    /* @req SWS_Lin_00213 */
    VALIDATE_W_RV( (LinChannelStatus[Channel] == LIN_CH_SLEEP), LIN_WAKE_UP_SERVICE_ID, LIN_E_STATE_TRANSITION, E_NOT_OK);
    /*lint -restore */

    retval = LinFlex_Common_Wakeup(&LinConfigPtr->LinChannelConfig[Channel]);

    if (E_OK == retval) {
        /**Lin_SendFrame API call will modify the channel status, so reset it here */
        /* @req SWS_Lin_00174 */
        LinChannelStatus[Channel]=LIN_OPERATIONAL;
    }

    return retval;
}

/** @req SWS_Lin_00256 */
Std_ReturnType   Lin_WakeupInternal( uint8 Channel ) {
    /** @req SWS_Lin_00258 */
    /** @req SWS_Lin_00214 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_W_RV( (LinDriverStatus != LIN_UNINIT), LIN_WAKE_UP_INTERNAL_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);
    /** @req SWS_Lin_00259 */
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_WAKE_UP_INTERNAL_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);
    /** @req SWS_Lin_00260 */
    /* @req SWS_Lin_00213 */
    VALIDATE_W_RV( (LinChannelStatus[Channel] == LIN_CH_SLEEP), LIN_WAKE_UP_INTERNAL_SERVICE_ID, LIN_E_STATE_TRANSITION, E_NOT_OK);
    /*lint -restore*/

    /*lint -e{923,9033} Hardware access */
    volatile struct LINFLEX_tag * LINFLEXHw = LINFLEX(LinConfigPtr->LinChannelConfig[Channel].LinChannelId);
    /* Clear sleep bit */
    LINFLEXHw->LINCR1.B.SLEEP = 0;

    /**@req SWS_Lin_00257 */
    /* @req SWS_Lin_00261 */
    /* @req SWS_Lin_00262 */
    LinChannelStatus[Channel]=LIN_OPERATIONAL;
    return E_OK;
}

/** @req SWS_Lin_00168 */
Lin_StatusType Lin_GetStatus( uint8 Channel, uint8** Lin_SduPtr )
{
    static uint8 LinBufRx[LIN_CONTROLLER_CNT][LIN_MAX_MSG_LENGTH];

    /** @req SWS_Lin_00141*/
    /** @req SWS_Lin_00214 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_W_RV( (LinDriverStatus != LIN_UNINIT), LIN_GETSTATUS_SERVICE_ID, LIN_E_UNINIT, LIN_NOT_OK);
    /** @req SWS_Lin_00143*/
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_GETSTATUS_SERVICE_ID, LIN_E_INVALID_CHANNEL, LIN_NOT_OK);
    /** @req SWS_Lin_00144*/
    /** @req SWS_Lin_00249 **/
    VALIDATE_W_RV( (Lin_SduPtr!=NULL), LIN_GETSTATUS_SERVICE_ID, LIN_E_PARAM_POINTER, LIN_NOT_OK);
    /*lint -restore */
    Std_ReturnType retval;
    SchM_Enter_Lin_EA_0();
    Lin_StatusType res = LinChannelStatus[Channel];
    /*lint -e{923,9033} Hardware access */
    const volatile struct LINFLEX_tag * LINFLEXHw = LINFLEX(LinConfigPtr->LinChannelConfig[Channel].LinChannelId);

    /** @req SWS_Lin_00200 */
    switch (res) {
        case LIN_RX_OK:
            /** @req SWS_Lin_00092 */
            /* @req SWS_Lin_00211 */
            retval = LinFlex_Common_WriteHwRegToDataBuf(LinBufRx[Channel], LINFLEXHw);
            /*lint -e{904} ARGUMENT_CHECK */
            VALIDATE_W_RV( (E_OK==retval), LIN_GETSTATUS_SERVICE_ID, LIN_E_PARAM_POINTER, LIN_NOT_OK);

            *Lin_SduPtr = LinBufRx[Channel];
        //lint -fallthrough
        case LIN_TX_OK:
            /** @req SWS_Lin_00238 */
            LinChannelStatus[Channel]=LIN_OPERATIONAL;
            break;

        case LIN_RX_ERROR:
            //lint -fallthrough
        case LIN_TX_ERROR:
            //lint -fallthrough
        case LIN_RX_NO_RESPONSE:
            //lint -fallthrough
        case LIN_TX_HEADER_ERROR:
            //lint -fallthrough

            retval = resyncDriver(Channel);
            if (E_NOT_OK == retval) {
                /*lint -e{904} OTHER to increase readability */
                return LIN_NOT_OK;
            }
            LinChannelStatus[Channel]=LIN_OPERATIONAL;
            break;

        case LIN_CH_SLEEP_PENDING:
            /** @req SWS_Lin_00255 */
            /** @req SWS_Lin_00264 */
            res = LinChannelStatus[Channel]=LIN_CH_SLEEP;
            //lint -fallthrough
        default:
            break;
    }

    SchM_Exit_Lin_EA_0();
    /** @req SWS_Lin_00091 */
    /* @req SWS_Lin_00022 */
    /* @req SWS_Lin_00024 */
    return res;
}




