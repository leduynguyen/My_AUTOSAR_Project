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

/** @tagSettings DEFAULT_ARCHITECTURE=NOT_USED */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#include "Lin.h"
#include "LinIf_Cbk.h"
#include "mpc55xx.h"
#if defined(USE_DET)
#include "Det.h"
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


/* ERRATA for REV_A of 551x chip. Will use a GPT timer for timeout handling */

#ifdef MPC551X_ERRATA_REV_A
#include "Gpt.h"

static Gpt_ChannelType LinChannelTimeOutGptChannelId[ LIN_CONTROLLER_CNT ];
static uint32          LinChannelBitTimeInTicks[ LIN_CONTROLLER_CNT ];
#endif

#define LIN_MAX_MSG_LENGTH 8

#if defined(CFG_MPC5668)
volatile struct ESCI_tag * const Lin_HwChUnitReg[] = {
        ((volatile struct ESCI_tag *) (0xFFFA0000)), /* 0 */
        ((volatile struct ESCI_tag *) (0xFFFA4000)), /* 1 */
        ((volatile struct ESCI_tag *) (0xFFFA8000)), /* 2 */
        ((volatile struct ESCI_tag *) (0xFFFAC000)), /* 3 */
        ((volatile struct ESCI_tag *) (0xFFFB0000)), /* 4 */
        ((volatile struct ESCI_tag *) (0xFFFB4000)), /* 5 */
        ((volatile struct ESCI_tag *) (0xFFFB8000)), /* 6 */
        ((volatile struct ESCI_tag *) (0xFFFBC000)), /* 7 */
        ((volatile struct ESCI_tag *) (0xC3FA0000)), /* 8 */
        ((volatile struct ESCI_tag *) (0xC3FA4000)), /* 9 */
        ((volatile struct ESCI_tag *) (0xC3FA8000)), /* 10 */
        ((volatile struct ESCI_tag *) (0xC3FAC000)), /* 11 */
};

#define ESCI(exp) Lin_HwChUnitReg[exp]

#elif defined(CFG_MPC5567) || defined(CFG_MPC563XM) || defined(CFG_MPC5644A)
#define ESCI(exp) (volatile struct ESCI_tag *)(0xFFFB0000 + (0x4000 * exp))
#else
#define ESCI(exp) (volatile struct ESCI_tag *)(0xFFFA0000 + (0x4000 * exp))
#endif

/* Reset -> LIN_UNINIT: After reset, the Lin module shall set its state to LIN_UNINIT. */
/* @req SWS_Lin_00145 */
static Lin_DriverStatusType LinDriverStatus = LIN_UNINIT;

static Lin_StatusType LinChannelStatus[LIN_CONTROLLER_CNT];
static Lin_StatusType LinChannelOrderedStatus[LIN_CONTROLLER_CNT];

static const Lin_ConfigType* LinConfigPtr = 0;

/* static buffers, holds one frame at a time */
static uint8 LinBufTx[LIN_CONTROLLER_CNT][LIN_MAX_MSG_LENGTH];
static uint8 LinBufRx[LIN_CONTROLLER_CNT][LIN_MAX_MSG_LENGTH];

static uint8 *TxCurrPtr[LIN_CONTROLLER_CNT];
static uint8  TxSize[LIN_CONTROLLER_CNT];
static uint8 *RxCurrPtr[LIN_CONTROLLER_CNT];
static uint8  RxSize[LIN_CONTROLLER_CNT];

#if (LIN_VERSION_INFO_API == STD_ON)
static Std_VersionInfoType _Lin_VersionInfo =
{ .vendorID = (uint16)60, .moduleID = (uint16) LIN_MODULE_ID,
        .sw_major_version = (uint8)LIN_SW_MAJOR_VERSION,
        .sw_minor_version = (uint8)LIN_SW_MINOR_VERSION,
        .sw_patch_version = (uint8)LIN_SW_PATCH_VERSION
};
#endif

/* Development error macros. */
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          Det_ReportError(LIN_MODULE_ID,0,_api,_err); \
          return; \
        }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
        if( !(_exp) ) { \
          Det_ReportError(LIN_MODULE_ID,0,_api,_err); \
          return (_rv); \
        }
#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_W_RV(_exp,_api,_err,_rv )
#endif

typedef volatile union
{
  uint32_t R;
  struct {
      uint32_t PID:8;
      uint32_t :24;
  } B1;
  struct {
      uint32_t L:8;
      uint32_t :24;
  } B2;
  struct {
      uint32_t HDCHK:1;
      uint32_t CSUM:1;
      uint32_t XCRC:1; /* Renamed CRC to XCRC to avoid conflict with macro CRC in MPC5644A.h. */
      uint32_t TX:1;
      uint32_t TN:4;
      uint32_t :24;
  } B3;
  struct {
      uint32_t T:8;
      uint32_t :24;
  } B4;
  struct {
      uint32_t D:8;
      uint32_t :24;
  } B5;
}LinLTRType;

typedef volatile union {
    vuint32_t R;
    struct {
        vuint32_t TDRE:1;
        vuint32_t TC:1;
        vuint32_t RDRF:1;
        vuint32_t IDLE:1;
        vuint32_t OR:1;
        vuint32_t NF:1;
        vuint32_t FE:1;
        vuint32_t PF:1;
          vuint32_t:3;
        vuint32_t BERR:1;
          vuint32_t:3;
        vuint32_t RAF:1;
        vuint32_t RXRDY:1;
        vuint32_t TXRDY:1;
        vuint32_t LWAKE:1;
        vuint32_t STO:1;
        vuint32_t PBERR:1;
        vuint32_t CERR:1;
        vuint32_t CKERR:1;
        vuint32_t FRC:1;
          vuint32_t:7;
        vuint32_t OVFL:1;
    } B;
} LinSRtype;   /* Status Register */

static void ResyncDriver(uint8 Channel)
{
    volatile struct ESCI_tag * esciHw = ESCI(LinConfigPtr->LinChannelConfig[Channel].LinChannelId);

    esciHw->LCR.B.TXIE = 0; /* Disable tx irq */
    esciHw->LCR.B.RXIE = 0; /* Disable Rx Interrupt */
    esciHw->LCR.B.FCIE = 0; /* Disable Rx Interrupt */

    /* Disable transmitter and receiver. */
    esciHw->CR1.B.TE = 0;
    esciHw->CR1.B.RE = 0;

      /* Clear flags  */
    esciHw->SR.R = esciHw->SR.R;

    /* Prepare module for resynchronization. */
    esciHw->LCR.B.LRES = 1; /* LIN Resynchronize. First set then cleared. */
    /* Resynchronize module. */
    esciHw->LCR.B.LRES = 0; /* LIN Resynchronize. First set then cleared. */

    /* Enable transmitter and receiver. */
    esciHw->CR1.B.TE = 1;
    esciHw->CR1.B.RE = 1;

#if 0 /* This needs if we Disable Fast Bit Error Detection otherwise SR will not be cleared properly....strange */
    volatile uint32 i;
    for(i=0; i < 10000; ){
      i++;
    }
#endif

    /* Clear set flags again */
    esciHw->SR.R = esciHw->SR.R;
}


void LinInterrupt(uint8 hwId)
{
    volatile struct ESCI_tag * esciHw = ESCI(hwId);
    uint8 Channel = LinConfigPtr->Lin_HwId2ChannelMap[hwId];
    LinSRtype sr, tmp;
    LinLTRType tmpLtr;
#ifdef MPC551X_ERRATA_REV_A
    uint8 stopTimeOutTimer = FALSE;
#endif 

    sr.R = esciHw->SR.R;

    /* Clear flags */
    tmp.R = 0;
    if(sr.B.TXRDY == 1){tmp.B.TXRDY = 1;}
    if(sr.B.RXRDY == 1){tmp.B.RXRDY = 1;}
    if(sr.B.TC == 1){tmp.B.TC = 1;}
    if(sr.B.RDRF == 1){tmp.B.RDRF = 1;}
    if(sr.B.IDLE == 1){tmp.B.IDLE = 1;}
    if(sr.B.OVFL == 1){tmp.B.OVFL = 1;}
    if(sr.B.FRC == 1){tmp.B.FRC = 1;}

    esciHw->SR.R = tmp.R;
    esciHw->LCR.B.TXIE = 0; /* Always disable Tx Interrupt */

    /* TX */
    if (LinChannelStatus[Channel]==LIN_TX_BUSY) {
        /* Maybe transmit next byte */
        if (TxSize[Channel] > 0 && sr.B.TXRDY) {
            tmpLtr.R = 0; /* Clear */
            tmpLtr.B4.T = *TxCurrPtr[Channel];
            TxCurrPtr[Channel]++; TxSize[Channel]--;
            esciHw->LCR.B.TXIE = 1; /* Enable tx irq */
            esciHw->LTR.R=tmpLtr.R; /* write to transmit reg */
         }
        else {
            if(sr.B.FRC == 1){
                /* Transmission complete */
                LinChannelStatus[Channel] = LIN_TX_OK;
                /* @req SWS_Lin_00157 */
                esciHw->LCR.B.TXIE = 0; /* Disable tx irq */
            }
            else{
                LinChannelStatus[Channel] = LIN_TX_ERROR;
            }
#ifdef MPC551X_ERRATA_REV_A
            /* Transmission is over. */
            stopTimeOutTimer = TRUE;
#endif 
        }
    }	/* RX */
    /* @req SWS_Lin_00060 */
    else if (LinChannelStatus[Channel]==LIN_RX_BUSY) {
      /* Maybe receive next byte */
        if (RxSize[Channel] > 0 && sr.B.RXRDY) {
            tmpLtr.R = esciHw->LRR.R;
            /* @req SWS_Lin_00096 */
            *RxCurrPtr[Channel] = tmpLtr.B5.D;
            RxCurrPtr[Channel]++; RxSize[Channel]--;
         } else if (RxSize[Channel] == 0 && sr.B.FRC == 1){
            /* receive complete */
            LinChannelStatus[Channel] = LIN_RX_OK;
            /* @req SWS_Lin_00157 */
            esciHw->LCR.B.RXIE = 0; /* Disable Rx Interrupt */
            esciHw->LCR.B.FCIE = 0; /* Disable Rx Interrupt */
#ifdef MPC551X_ERRATA_REV_A
            /* Transmission is over. */
            stopTimeOutTimer = TRUE;
#endif 
         }
    }

    /* Error handling
     * OR    - Overrun
     * NF    - Noise fault
     * FE    - Framing Error
     * PF    - Parity fault
     * BERR  - Bit error (read back)
     * STO   - Slave Timeout
     * PBERR - Physical bit error
     * CERR  - CRC error
     * CKERR - Checksum error
     * OVFL  - Overflow flag
     */
    if(sr.B.OR || sr.B.NF || sr.B.FE || sr.B.PF || sr.B.BERR || sr.B.STO || sr.B.PBERR ||
       sr.B.CERR || sr.B.CKERR || sr.B.OVFL) {
        static uint32 errCnt=0;
        errCnt++;
        // LIN_RX_NO_RESPONSE - Slave Timeout LIN_TX_HEADER_ERROR - Parity Fault or Bit error or Physical bus error
        if(LinChannelStatus[Channel]==LIN_RX_BUSY){
            /** Slave timeout */
            if (sr.B.STO) {
                LinChannelStatus[Channel] = LIN_RX_NO_RESPONSE;
            }
            /** Parity error in the header, bit error and physical bus error (This can be detected only for headers for Rx Frame)*/
            else if (sr.B.PF || sr.B.BERR ||sr.B.PBERR) {
                LinChannelStatus[Channel] = LIN_TX_HEADER_ERROR;
            }
            else {
                LinChannelStatus[Channel] = LIN_RX_ERROR;
            }

        }
        //LIN_TX_HEADER_ERROR - Parity Fault or Bit error or Physical bus error when header has been transmitted
        else if (LinChannelStatus[Channel]==LIN_TX_ERROR){
            //check condition error occurred for header and not data. tmpLtr.B2.L = DL & TxSize[Channel] set to DL when header tx
            if ((sr.B.PF || sr.B.BERR ||sr.B.PBERR) && (tmpLtr.B2.L == TxSize[Channel])) {
                LinChannelStatus[Channel] = LIN_TX_HEADER_ERROR;
            }
            else {
                LinChannelStatus[Channel] = LIN_TX_ERROR;
            }
        }

          /* Clear flags  */
        /* @req SWS_Lin_00157 */
        esciHw->SR.R=0xffffffff;

        /* Resynchronize driver in GetStatus call */

#ifndef MPC551X_ERRATA_REV_A
    }
#else
        /* Transmission is over. */
        stopTimeOutTimer = TRUE;
    }

    /* Handle LIN Wake Up reset manually. See [Freescale Device Errata MPC5510ACE, Rev. 10 APR 2009, errata ID: 8632]. */
    if( sr.B.LWAKE )
    {
        /* Resynchronize driver. */
        esciHw->LCR.B.LRES = 1; /* LIN Resynchronize. First set then cleared */
        esciHw->LCR.B.LRES = 0; /* LIN Resynchronize. First set then cleared */

        /* Transmission is over. */
        stopTimeOutTimer = TRUE;
    }

    if( TRUE == stopTimeOutTimer )
    {
        Gpt_StopTimer( LinChannelTimeOutGptChannelId[ Channel ] );
    }
#endif

    if (LinChannelOrderedStatus[Channel]==LIN_CH_SLEEP_PENDING){
        /** @req SWS_Lin_00266*/
        LinChannelStatus[Channel] = LIN_CH_SLEEP_PENDING;
        LinChannelOrderedStatus[Channel]=LIN_OPERATIONAL;
    }
}

#ifdef LIN_CHANNEL_0_USED
ISR(LinInterruptA){ LinInterrupt(0);}
#endif
#ifdef LIN_CHANNEL_1_USED
ISR(LinInterruptB){ LinInterrupt(1);}
#endif

#if !defined(CFG_MPC5567) && !defined(CFG_MPC563XM)
#ifdef LIN_CHANNEL_2_USED
ISR(LinInterruptC){ LinInterrupt(2);}
#endif
#if !defined(CFG_MPC5644A)
#ifdef LIN_CHANNEL_3_USED
ISR(LinInterruptD){ LinInterrupt(3);}
#endif
#ifdef LIN_CHANNEL_4_USED
ISR(LinInterruptE){ LinInterrupt(4);}
#endif
#ifdef LIN_CHANNEL_5_USED
ISR(LinInterruptF){ LinInterrupt(5);}
#endif
#ifdef LIN_CHANNEL_6_USED
ISR(LinInterruptG){ LinInterrupt(6);}
#endif
#ifdef LIN_CHANNEL_7_USED
ISR(LinInterruptH){ LinInterrupt(7);}
#endif
#endif

#if defined(CFG_MPC5668)
#ifdef LIN_CHANNEL_8_USED
ISR(LinInterruptI){ LinInterrupt(8);}
#endif
#ifdef LIN_CHANNEL_9_USED
ISR(LinInterruptJ){ LinInterrupt(9);}
#endif
#ifdef LIN_CHANNEL_10_USED
ISR(LinInterruptK){ LinInterrupt(10);}
#endif
#ifdef LIN_CHANNEL_11_USED
ISR(LinInterruptL){ LinInterrupt(11);}
#endif
#endif /* #if defined(CFG_MPC5668) */

#endif


#ifdef MPC551X_ERRATA_REV_A
void LinTimeOutInterrupt( uint8 hwId )
{
    /* We ended up here because of that the eSCI module for the given channel has stopped internally.
    * Now we have to reset the LIN module state machine ourself.
    * See [Freescale Device Errata MPC5510ACE, Rev. 10 APR 2009, errata ID: 8173 and 4968]. */

    volatile struct ESCI_tag *esciHw = ESCI( hwId );
    uint8 Channel = LinConfigPtr->Lin_HwId2ChannelMap[hwId];

    /* Make sure that the timer it stopped (e.g. if by mistake setup as continuously). */
    Gpt_StopTimer( LinChannelTimeOutGptChannelId[ channel ] );

    /* @req SWS_Lin_00157 */
    /* Disable transmitter and receiver. */
    esciHw->CR1.B.TE = 0;
    esciHw->CR1.B.RE = 0;

    /* Prepare module for resynchronization. */
    esciHw->LCR.B.LRES = 1; /* LIN Resynchronize. First set then cleared. */

    /* Enable transmitter and receiver. */
    esciHw->CR1.B.TE = 1;
    esciHw->CR1.B.RE = 1;

    /* Resynchronize module. */
    esciHw->LCR.B.LRES = 0; /* LIN Resynchronize. First set then cleared. */
}

#ifdef LIN_CHANNEL_0_USED
ISR(LinTimeOutInterruptA){LinTimeOutInterrupt(0);}
#endif
#ifdef LIN_CHANNEL_1_USED
ISR(LinTimeOutInterruptB){LinTimeOutInterrupt(1);}
#endif

#if !defined(CFG_MPC5567) && !defined(CFG_MPC563XM)
#ifdef LIN_CHANNEL_2_USED
ISR(LinTimeOutInterruptC){LinTimeOutInterrupt(2);}
#endif
#if !defined(CFG_MPC5644A)
#ifdef LIN_CHANNEL_3_USED
ISR(LinTimeOutInterruptD){LinTimeOutInterrupt(3);}
#endif
#ifdef LIN_CHANNEL_4_USED
ISR(LinTimeOutInterruptE){LinTimeOutInterrupt(4);}
#endif
#ifdef LIN_CHANNEL_5_USED
ISR(LinTimeOutInterruptF){LinTimeOutInterrupt(5);}
#endif
#ifdef LIN_CHANNEL_6_USED
ISR(LinTimeOutInterruptG){LinTimeOutInterrupt(6);}
#endif
#ifdef LIN_CHANNEL_7_USED
ISR(LinTimeOutInterruptH){LinTimeOutInterrupt(7);}
#endif
#endif
#endif

#if defined(CFG_MPC5668)
#ifdef LIN_CHANNEL_8_USED
ISR(LinTimeOutInterruptI){LinTimeOutInterrupt(8);}
#endif
#ifdef LIN_CHANNEL_9_USED
ISR(LinTimeOutInterruptJ){LinTimeOutInterrupt(9);}
#endif
#ifdef LIN_CHANNEL_10_USED
ISR(LinTimeOutInterruptK){LinTimeOutInterrupt(10);}
#endif
#ifdef LIN_CHANNEL_11_USED
ISR(LinTimeOutInterruptL){LinTimeOutInterrupt(11);}
#endif
#endif /* #if defined(CFG_MPC5668) */

#endif

/** @req SWS_Lin_00006 */
void Lin_Init( const Lin_ConfigType* Config )
{
    uint8 i;
    LinConfigPtr = Config;
    enum
    {
      LIN_PRIO = 3
    };
    /** @req SWS_Lin_00105 **/
    /* @req SWS_Lin_00213 */
    VALIDATE( (LinDriverStatus == LIN_UNINIT), LIN_INIT_SERVICE_ID, LIN_E_STATE_TRANSITION );
    /** @req SWS_Lin_00099 **/
    /** @req SWS_Lin_00216 **/
    VALIDATE( (Config!=NULL), LIN_INIT_SERVICE_ID, LIN_E_INVALID_POINTER );

    for (i=0;i<LIN_CONTROLLER_CNT;i++)
    {
        TxCurrPtr[i] = 0;
        TxSize[i] = 0;
        RxCurrPtr[i] = 0;
        RxSize[i] = 0;
#ifdef MPC551X_ERRATA_REV_A
        LinChannelTimeOutGptChannelId[ i ] = 0;
        LinChannelBitTimeInTicks[ i ] = 0;
#endif
    }

    /* Install the interrupt */
    /* @req SWS_Lin_00155 */
#if defined(CFG_MPC5567) || defined(CFG_MPC563XM) || defined(CFG_MPC5644A)
#ifdef LIN_CHANNEL_0_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptA, (IrqType)(ESCI_A_COMB),LIN_PRIO, 0);
#endif
#ifdef LIN_CHANNEL_1_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptB, (IrqType)(ESCI_B_COMB),LIN_PRIO, 0);
#endif

#if defined(CFG_MPC5644A)
#ifdef LIN_CHANNEL_2_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptC, (IrqType)(ESCI_C_COMB),LIN_PRIO, 0);
#endif
#endif

#else
#ifdef LIN_CHANNEL_0_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptA, (IrqType)(SCI_A_COMB),LIN_PRIO, 0);
#endif
#ifdef LIN_CHANNEL_1_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptB, (IrqType)(SCI_B_COMB),LIN_PRIO, 0);
#endif
#ifdef LIN_CHANNEL_2_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptC, (IrqType)(SCI_C_COMB),LIN_PRIO, 0);
#endif
#ifdef LIN_CHANNEL_3_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptD, (IrqType)(SCI_D_COMB),LIN_PRIO, 0);
#endif
#ifdef LIN_CHANNEL_4_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptE, (IrqType)(SCI_E_COMB),LIN_PRIO, 0);
#endif
#ifdef LIN_CHANNEL_5_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptF, (IrqType)(SCI_F_COMB),LIN_PRIO, 0);
#endif
#ifdef LIN_CHANNEL_6_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptG, (IrqType)(SCI_G_COMB),LIN_PRIO, 0);
#endif
#ifdef LIN_CHANNEL_7_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptH, (IrqType)(SCI_H_COMB),LIN_PRIO, 0);
#endif

#if defined(CFG_MPC5668)
#ifdef LIN_CHANNEL_8_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptI, (IrqType)(SCI_I_COMB),LIN_PRIO, 0);
#endif
#ifdef LIN_CHANNEL_9_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptJ, (IrqType)(SCI_J_COMB),LIN_PRIO, 0);
#endif
#ifdef LIN_CHANNEL_10_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptK, (IrqType)(SCI_K_COMB),LIN_PRIO, 0);
#endif
#ifdef LIN_CHANNEL_11_USED
    ISR_INSTALL_ISR2("LinIsr", LinInterruptL, (IrqType)(SCI_L_COMB),LIN_PRIO, 0);
#endif
#endif /*#if defined(CFG_MPC5668)*/

#endif
        /* Initialize the hardware specifics for each supported channel */
        /** @req SWS_Lin_00190 */
        /** @req SWS_Lin_00008  */
        /** @req SWS_Lin_00084 */
        for (uint8 Channel =0; Channel < LIN_CONTROLLER_CNT; Channel++) {
            volatile struct ESCI_tag * esciHw = ESCI(LinConfigPtr->LinChannelConfig[Channel].LinChannelId);

            esciHw->CR2.B.MDIS = 0;/* The module is enabled by writing the ESCIx_CR2[MDIS] bit to 0. */

            esciHw->CR1.B.RE = 1;
            esciHw->CR1.B.M = 0; /* The data format bit ESCIx_CR1[M], is set to 0 (8 data bits), and the parity is disabled (PE = 0).*/
            esciHw->CR1.B.PE = 0;
            esciHw->CR1.B.TIE = 0; /*ESCIx_CR1[TIE], ESCIx_CR1[TCIE], ESCIx_CR1[RIE] interrupt enable bits should be inactive.*/
            esciHw->CR1.B.TCIE = 0;
            esciHw->CR1.B.RIE = 0;
              /* Set up ESCIx_CR1 for LIN */
              /*
               * SCI Baud Rate. Used by the counter to determine the baud rate of the eSCI.
               * The formula for calculating the baud rate is:
               *
               *                      eSCI system clock
               * SCI baud rate =   -----------------------
               *                          16 * SBR
               *
               * where SBR can contain a value from 1 to 8191. After reset, the baud generator
               * is disabled until the TE bit or the RE bit is set for the first time. The baud
               * rate generator is disabled when SBR = 0x0.
               */
            /** @req SWS_Lin_00150 */
            esciHw->CR1.B.SBR  = Mcu_Arc_GetPeripheralClock((Mcu_Arc_PeriperalClock_t)Config->LinChannelConfig[Channel].LinClockRef)/(16*Config->LinChannelConfig[Channel].LinChannelBaudRate);
            esciHw->LCR.B.LIN = 1;  /* Instead, the LIN interrupts should be used.Switch eSCI to LIN mode (ESCIx_LCR[LIN] = 1).*/

            esciHw->CR2.B.BRK13 = 1;/* The LIN standard requires that the break character always be 13 bits long
            (ESCIx_CR2[BRK13] = 1). The eSCI will work with BRK13=0, but it will violate LIN 2.0. */

        #ifdef MPC551X_ERRATA_REV_A
            esciHw->LCR.B.LDBG = 1; /* Enable LIN debug => Disable automatic reset of the LIN FSM. See [Freescale Device Errata MPC5510ACE, Rev. 10 APR 2009, errata ID: 8632] */
            esciHw->CR2.B.FBR = 1;  /* Disable Fast Bit Error Detection. See [Freescale Device Errata MPC5510ACE, Rev. 10 APR 2009, errata ID: 8635] */
        #else
        #if !defined(CFG_MPC563XM) && !defined(CFG_MPC5668)
            esciHw->LCR.B.LDBG = 0; /* Normally, bit errors should cause the LIN FSM to reset, stop driving the bus immediately, and stop
                                     * further DMA requests until the BERR flag has been cleared. Set ESCIx_LCR[LDBG] = 0,*/
        #endif
            esciHw->CR2.B.FBR = 1;    /* Fast bit error detection provides superior error checking, so ESCIx_CR2[FBR] should be set; */
        #endif
            esciHw->LCR.B.STIE = 1; /* Enable some fault irq's */
            esciHw->LCR.B.PBIE = 1;
            esciHw->LCR.B.CKIE = 1;
            esciHw->LCR.B.OFIE = 1;

            esciHw->CR2.B.SBSTP = 1;/*ESCIx_CR2[SBSTP] = 1, and ESCIx_CR2[BSTP] = 1 to accomplish these functions.*/
            esciHw->CR2.B.BSTP = 1;

            esciHw->CR2.B.BESM13 = 1; /* normally it will be used with ESCIx_CR2[BESM13] = 1.*/

            /* The error indicators NF, FE, BERR, STO, PBERR, CERR, CKERR, and OVFL should be enabled. */
            /* Should we have these interrupts or check the status register? */
            /*Initially a wakeup character may need to be transmitted on the LIN bus, so that the LIN slaves
            activate.*/

            esciHw->CR1.B.TE = 1; /* Both transmitter and receiver are enabled (ESCIx_CR1[TE] = 1, ESCIx_CR1[RE] = 1). */

            /** @req SWS_Lin_00171 */
            LinChannelOrderedStatus[Channel]=LIN_OPERATIONAL;
            LinChannelStatus[Channel]=LIN_OPERATIONAL;
        #ifdef MPC551X_ERRATA_REV_A
            LinChannelTimeOutGptChannelId[ Channel ] = Config->LinTimeOutGptChannelId;
            LinChannelBitTimeInTicks[ Channel ] = Mcu_Arc_GetPeripheralClock( Config->LinClockRef / Config->LinChannelBaudRate ) / Config->LinChannelBaudRate;
        #endif


    }

        /** @req SWS_Lin_00146 */
    /* LIN_UNINIT -> LIN_INIT: The Lin module shall transition from LIN_UNINIT
     * to LIN_INIT when the function Lin_Init is called. */
    LinDriverStatus = LIN_INIT;

}
void Lin_Arc_DeInit(void) {
    LinDriverStatus = LIN_UNINIT;

    for (uint8 Channel = 0; Channel < LIN_CONTROLLER_CNT; Channel++) {

#ifdef MPC551X_ERRATA_REV_A
        /* Make sure that the timer is stopped. */
        Gpt_StopTimer( LinChannelTimeOutGptChannelId[ Channel ] );
#endif

        if (LinChannelStatus[Channel] != LIN_CH_UNINIT) {
            if (LinConfigPtr != NULL) {
                volatile struct ESCI_tag * esciHw = ESCI(LinConfigPtr->LinChannelConfig[Channel].LinChannelId);
                esciHw->CR2.B.MDIS = 1;/* The module is disabled by writing the ESCIx_CR2[MDIS] bit to 1. */
            }

            LinChannelStatus[Channel] = LIN_CH_UNINIT;
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
    VALIDATE( !(versioninfo == NULL), LIN_GETVERSIONINFO_SERVICE_ID, LIN_E_PARAM_POINTER );

    /** @req SWS_Lin_00001 **/
    memcpy(versioninfo, &_Lin_VersionInfo, sizeof(Std_VersionInfoType));
    return;
}

#endif

/** @req SWS_Lin_00191 */
Std_ReturnType Lin_SendFrame(  uint8 Channel,  Lin_PduType* PduInfoPtr )
{
    LinSRtype tmp;
    LinLTRType tmpLtr;

    /** @req SWS_Lin_00195 */
    /** @req SWS_Lin_00214 */
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

    volatile struct ESCI_tag * esciHw = ESCI(LinConfigPtr->LinChannelConfig[Channel].LinChannelId);

    /** @req SWS_Lin_00021 */
     /* @req SWS_Lin_00074 */
    SchM_Enter_Lin_EA_0();
    if(LinChannelStatus[Channel] == LIN_TX_BUSY || LinChannelStatus[Channel] == LIN_TX_ERROR ||
       LinChannelStatus[Channel] == LIN_RX_BUSY || LinChannelStatus[Channel] == LIN_RX_ERROR ||
       LinChannelStatus[Channel] == LIN_RX_NO_RESPONSE || LinChannelStatus[Channel] ==LIN_TX_HEADER_ERROR)
    {
        ResyncDriver(Channel);
        LinChannelStatus[Channel]=LIN_OPERATIONAL;
    }
    SchM_Exit_Lin_EA_0();

    /* @req SWS_Lin_00194 */
    /** @req SWS_Lin_00192 */
    /* Byte 1 */
    tmpLtr.R = 0; /* Clear */
    tmpLtr.B1.PID = PduInfoPtr->Pid;
    tmp.R = 0; /* Clear ready flag before send */
    tmp.B.TXRDY = 1;
    esciHw->SR.R = tmp.R;
    esciHw->LTR.R=tmpLtr.R; /* write to transmit reg */

    /* Byte 2 */
    tmpLtr.R = 0; /* Clear */
    tmpLtr.B2.L = PduInfoPtr->DI;
    tmp.R = 0; /* Clear ready flag before send */
    tmp.B.TXRDY = 1;
    esciHw->SR.R = tmp.R;
    esciHw->LTR.R=tmpLtr.R; /* write to transmit reg */

    /* Byte 3 */
    tmpLtr.R = 0; /* Clear */
    if (PduInfoPtr->Cs == LIN_ENHANCED_CS){ /*Frame identifiers 60 (0x3C) to 61 (0x3D) shall always use classic checksum */
        tmpLtr.B3.HDCHK = 1;
    }
    tmpLtr.B3.CSUM = 1; /* Append checksum to TX frame or verify for a RX */
    tmpLtr.B3.XCRC = 0; /* Append two CRC bytes(Not LIN standard) */

    /* Calculate the time out value for the frame.(10 * NDATA + 45) * 1.4 according to LIN1.3 */
    /* The reason the LIN1.3 timeout calculation is used instead of the LIN2.1 is for backwards compatibility */
    uint16 timeOutValue = (uint16)( ( ( 10 * PduInfoPtr->DI + 45 ) * 14 ) / 10);

    if (PduInfoPtr->Drc == LIN_MASTER_RESPONSE)
    {
        LinChannelStatus[Channel]=LIN_TX_BUSY;
        tmpLtr.B3.TX = 1; /* TX frame */
        tmpLtr.B3.TN = 0; /* Timeout not valid for TX */
        tmp.R = 0; /* Clear ready flag before send */
        tmp.B.TXRDY = 1;
        esciHw->SR.R = tmp.R;
        esciHw->LCR.B.FCIE = 1; /* Enable frame complete */
        esciHw->LCR.B.TXIE = 1; /* Enable tx irq */
        if (PduInfoPtr->DI > 0){
            TxCurrPtr[Channel] = LinBufTx[Channel];
            TxSize[Channel] = PduInfoPtr->DI;
            /* @req SWS_Lin_00053 */
            /* @req SWS_Lin_00025 */
            /* @req SWS_Lin_00026 */
            /* @req SWS_Lin_00096 */
            memcpy(TxCurrPtr[Channel],PduInfoPtr->SduPtr,PduInfoPtr->DI);
        }
        esciHw->LTR.R=tmpLtr.R; /* write to transmit reg */
    }

    /** @req SWS_Lin_00193 */
    else
    {
        LinChannelStatus[Channel]=LIN_RX_BUSY;
        RxCurrPtr[Channel] = LinBufRx[Channel];
        RxSize[Channel] = PduInfoPtr->DI;

        tmpLtr.B3.TX = 0; /* RX frame */
        tmpLtr.B3.TN = timeOutValue >> 8;     /* Most significant bits to be set here. */
        esciHw->LTR.R=tmpLtr.R; /* write to transmit reg */
        /* Byte 4 for RX */
        tmpLtr.R = 0; /* Clear */
        tmpLtr.B4.T = timeOutValue & 0xFF;   /* Least significant bits to be set here. */
        tmp.R = 0; /* Clear ready flag before send */
        tmp.B.TXRDY = 1;
        esciHw->SR.R = tmp.R;
        esciHw->LTR.R=tmpLtr.R; /* write to transmit reg */
        esciHw->LCR.B.FCIE = 1; /* Enable frame complete */
        esciHw->LCR.B.RXIE = 1; /* Enable rx irq */
    }

#ifdef MPC551X_ERRATA_REV_A
    /* Set up the GPT to twice as long time. Normally this time out shall not be needed but there are two
    * Erratas telling us that the LIN message timeout (written above to byte 3 and 4) is sometimes not used
    * by the LIN module and the LIN module state machine will then wait in infinity.
    * See [Freescale Device Errata MPC5510ACE, Rev. 10 APR 2009, errata ID: 8173 and 4968]. */
    Gpt_StopTimer( LinChannelTimeOutGptChannelId[ Channel ] );
    Gpt_StartTimer( LinChannelTimeOutGptChannelId[ Channel ], LinChannelBitTimeInTicks[ Channel ] * timeOutValue * 2 );
#endif

    return E_OK;
}

/**@req SWS_Lin_00166 */
Std_ReturnType Lin_GoToSleep(  uint8 Channel )
{
    Lin_PduType PduInfo;
    uint8 data[8] = {0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

    /** @req SWS_Lin_00129*/
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (LinDriverStatus != LIN_UNINIT), LIN_GO_TO_SLEEP_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);

    /** @req SWS_Lin_00131*/
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_GO_TO_SLEEP_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);

    /* @req SWS_Lin_00033 */
    /* @req SWS_Lin_00263 */
    LinChannelOrderedStatus[Channel]=LIN_CH_SLEEP_PENDING;

    PduInfo.Cs = LIN_CLASSIC_CS;
    PduInfo.Pid = 0x3C;
    PduInfo.SduPtr = data;
    PduInfo.DI = 8;
    PduInfo.Drc = LIN_MASTER_RESPONSE;
    /** @req SWS_Lin_00089 */
    /** @req SWS_Lin_00074 */ //Cancellation of previous send in done in Lin_SendFrame Api
    Lin_SendFrame(Channel,  &PduInfo);

    return E_OK;
}

/** @req SWS_Lin_00167 */
Std_ReturnType Lin_GoToSleepInternal(  uint8 Channel )
{
    /** @req SWS_Lin_00133 */
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (LinDriverStatus != LIN_UNINIT), LIN_GO_TO_SLEEP_INTERNAL_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);

    /** @req SWS_Lin_00135 */
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_GO_TO_SLEEP_INTERNAL_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);

    /** @req SWS_Lin_00095 */
    /** @req SWS_Lin_00265 */
    LinChannelStatus[Channel] = LIN_CH_SLEEP;
    LinChannelOrderedStatus[Channel]=LIN_OPERATIONAL;
    return E_OK;
}

/** @req SWS_Lin_00169 */
Std_ReturnType Lin_Wakeup( uint8 Channel )
{
    /** @req SWS_Lin_00137 */
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (LinDriverStatus != LIN_UNINIT), LIN_WAKE_UP_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);

    /** @req SWS_Lin_00139 */
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_WAKE_UP_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);
    /** @req SWS_Lin_00140 */
    /* @req SWS_Lin_00213 */
    VALIDATE_W_RV( (LinChannelStatus[Channel] == LIN_CH_SLEEP), LIN_WAKE_UP_SERVICE_ID, LIN_E_STATE_TRANSITION, E_NOT_OK);

    volatile struct ESCI_tag * esciHw = ESCI(LinConfigPtr->LinChannelConfig[Channel].LinChannelId);

    /** Setting WU bit in LCR generates a wakeup pulse and the bit is autocleared by the hw.
     * WUD register specifies how long the hw should wait before starting a new frame after generating wakeup
     */
    /* @req SWS_Lin_00043 */
    /* @req SWS_Lin_00209 */
    //send wake up pulse
    esciHw->LCR.B.WU = 1;
    //wakeup delimiter time set to 32 bit times
    esciHw->LCR.B.WUD0 = 1;
    esciHw->LCR.B.WUD1 = 0;

    /**Lin_SendFrame API call will modify the channel status, so reset it here */
    /* @req SWS_Lin_00174 */
    LinChannelStatus[Channel]=LIN_OPERATIONAL;

    return E_OK;
}
/** @req SWS_Lin_00256 */
Std_ReturnType   Lin_WakeupInternal( uint8 Channel ) {
    /** @req SWS_Lin_00258 */
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (LinDriverStatus != LIN_UNINIT), LIN_WAKE_UP_INTERNAL_SERVICE_ID, LIN_E_UNINIT, E_NOT_OK);
    /** @req SWS_Lin_00259 */
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_WAKE_UP_INTERNAL_SERVICE_ID, LIN_E_INVALID_CHANNEL, E_NOT_OK);
    /** @req SWS_Lin_00260 */
    /* @req SWS_Lin_00213 */
    VALIDATE_W_RV( (LinChannelStatus[Channel] == LIN_CH_SLEEP), LIN_WAKE_UP_INTERNAL_SERVICE_ID, LIN_E_STATE_TRANSITION, E_NOT_OK);

    /**@req SWS_Lin_00257 */
    /* @req SWS_Lin_00261 */
    /* @req SWS_Lin_00262 */
    LinChannelStatus[Channel]=LIN_OPERATIONAL;
    return E_OK;
}
/** @req SWS_Lin_00168 */
Lin_StatusType Lin_GetStatus( uint8 Channel, uint8** Lin_SduPtr )
{
    /** @req SWS_Lin_00141*/
    /** @req SWS_Lin_00214 */
    VALIDATE_W_RV( (LinDriverStatus != LIN_UNINIT), LIN_GETSTATUS_SERVICE_ID, LIN_E_UNINIT, LIN_NOT_OK);
    /** @req SWS_Lin_00143*/
    /** @req SWS_Lin_00215 */
    VALIDATE_W_RV( (Channel < LIN_CONTROLLER_CNT), LIN_GETSTATUS_SERVICE_ID, LIN_E_INVALID_CHANNEL, LIN_NOT_OK);
    /** @req SWS_Lin_00144*/
    /** @req SWS_Lin_00249 **/
    VALIDATE_W_RV( (Lin_SduPtr!=NULL), LIN_GETSTATUS_SERVICE_ID, LIN_E_PARAM_POINTER, LIN_NOT_OK);

    SchM_Enter_Lin_EA_0();
    Lin_StatusType res = LinChannelStatus[Channel];

    /** @req SWS_Lin_00200 */
    switch (res) {
        case LIN_RX_OK:
            /** @req SWS_Lin_00092 */
            /* @req SWS_Lin_00211 */
            *Lin_SduPtr = LinBufRx[Channel];
            //lint -fallthrough
        case LIN_TX_OK:
#ifdef HOST_TEST
            *Lin_SduPtr = LinBufTx[Channel];
#endif
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

            ResyncDriver(Channel);
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





