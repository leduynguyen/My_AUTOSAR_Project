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

/* ----------------------------[information]----------------------------------*/
/*
 *
 *
 * Description:
 *
 *
 * Limitations:
 */

/*lint -save -e9003 Misra 2012 8.9 Blockscope variables definitions neglected.
 * Static variable declaration in Function body violates the AUTOSAR memory mapping concept.*/

/* ----------------------------[includes]------------------------------------*/
#include "Can.h"
#include "CanIf_Cbk.h"
#include "Can_Internal.h"

#include "Mcu.h"
#include "EcuM.h"

#if (CAN_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#if defined(USE_DEM)
#include "Dem.h"
#endif

#include <string.h>
#include "SchM_Can.h"
#include "isr.h"
#include "irq.h"
#include "rh850.h"
#include "CanRegs.h"
/*#define USE_LDEBUG_PRINTF*/
#include "debug.h"
#include "arc_assert.h"




/* ----------------------------[private define]------------------------------*/

#define R_CAN_GRAMINIT_ON  (0x8UL)
#define R_CAN_GSLPSTS_ON   (0x4UL)
#define R_CAN_GRSTSTS_ON   (0x1UL)
#define R_CAN_CSLPSTS_ON   (0x4UL)
#define R_CAN_CHLTSTS_ON   (0x2UL)
#define R_CAN_CRSTSTS_ON   (0x1UL)
#define R_CAN_TMTRM_ON     (0x8U)
#define R_CAN_TMTR_ON      (0x1U)
#define R_CAN_AFLDAE_ON    (0x100UL)
#define R_CAN_GSLPR_MASK   (0x4UL)
#define R_CAN_GMDC_MASK    (0x3UL)
#define R_CAN_CSLPR_MASK   (0x4UL)
#define R_CAN_CHMDC_MASK   (0x3UL)


#define RSCAN0_UNIT                   0U
#define RSCAN1_UNIT                   1U
#define RSCAN0_HWCH_MAX               6U
#define RSCAN1_HWCH_MAX               2U
#define AF_MAX_NUMPAGES              24U  /* Acceptance filter maximum number of pages */
#define AF_PAGE_SIZE                 16U  /* Acceptance filter page size */
#define TXBUFS_PER_CH                16UL

#define USE_CAN_STATISTICS           STD_OFF
#define USE_ONLY_RXFIFOS             STD_ON
#define USE_CAN_OSCILLATOR_CLOCK     STD_ON

#define INVALID_CANID                0xFFFFFFFFUL
#define EXTENDED_CANID_MASK          0x1FFFFFFFUL
#define STD_CANID_MASK               0x7FFUL

#define FIFO_RX				0UL
#define FIFO_RXTX			1
#define FIFO_IMPL			FIFO_RXTX


/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private macro]-------------------------------*/

#if defined(CFG_RH850F1L)
#define RSCAN0_BASE	0xFFD00000U
#else
#error No device selected.
#endif


#define CAN_ASSERT(_x)		ASSERT(_x)

/*lint -save --e{9023,9024} Allow use of ## below */
#define _ADD_ISR_HANDLERS(_x,_y) \
        do { \
            if( ( _y &  (CAN_CTRL_BUSOFF_PROCESSING_INTERRUPT | CAN_CTRL_ERROR_PROCESSING_INTERRUPT) ) != 0UL ) { \
                ISR_INSTALL_ISR2( "Can", Can_Ch ## _x ## _Err, IRQ_INTRCAN ## _x ## ERR, 2, 0UL ); \
            } \
            if( ( _y &  CAN_CTRL_TX_PROCESSING_INTERRUPT ) != 0UL ){ \
                ISR_INSTALL_ISR2( "Can", Can_Ch  ## _x ## _IsrTx, IRQ_INTRCAN ## _x ## TRX, 2, 0UL ); \
            } \
            if( ( _y &  CAN_CTRL_RX_PROCESSING_INTERRUPT ) != 0UL ){ \
                ISR_INSTALL_ISR2( "Can", Can_Ch  ## _x ## _IsrRx, IRQ_INTRCAN ## _x ## REC, 2, 0UL ); \
            } \
        } while(FALSE)
/* Wrapper used for expansion of macro parameters... */
#define ADD_ISR_HANDLERS(_x,_y) _ADD_ISR_HANDLERS(_x,_y)
/*lint -restore */


#define HWCH_TO_CHIDX(_hwch)		((_hwch)*3 % RSCAN0_HWCH_MAX)


/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private constants]---------------------------*/
/* ----------------------------[private variables]---------------------------*/
/* Since the channels can span over several controllers it's best to access via arrays */

/* RS-CAN Controller based indexing */
/*lint --e{923} Allow cast from unsigned to pointer */
RSCAN_RegType * const Can_HwUnitReg[] = {
        ((RSCAN_RegType *) (RSCAN0_BASE)),  		  /* 0 */
#if defined(RH850F1H)
        ((RSCAN_RegType *) (RSCAN1_BASE)),  		  /* 1 */
#endif
};

/* RS-CAN Channel based indexing */
RSCAN_RegType * const Can_HwChUnitReg[] = {
        ((RSCAN_RegType *) (RSCAN0_BASE)),  		  /* 0 */
        ((RSCAN_RegType *) (RSCAN0_BASE)),  		  /* 1 */
        ((RSCAN_RegType *) (RSCAN0_BASE)),  		  /* 2 */
        ((RSCAN_RegType *) (RSCAN0_BASE)),  		  /* 3 */
        ((RSCAN_RegType *) (RSCAN0_BASE)),  		  /* 4 */
        ((RSCAN_RegType *) (RSCAN0_BASE)),  		  /* 5 */
#if defined(RH850F1H)
        ((RSCAN_RegType *) (RSCAN1_BASE)),  		  /* 1 */
#endif
};

uint32 Can_PduIndex[CAN_ARC_CTRL_MAX];

static uint32 gPage = 0UL;

/* ----------------------------[private functions]---------------------------*/


/*
 * Interrupt Enable/Disable functions
 */
static inline void enableRxIrq( uint8 hwCh ) {
    /* Enable FIFO RX interrupt */
    Can_HwChUnitReg[hwCh]->CFCC[HWCH_TO_CHIDX(hwCh)].B.CFRXIE = 1;
}

static inline void enableTxIrq( uint8 hwCh ) {
    /* */
    Can_HwChUnitReg[hwCh]->THLCC[hwCh].B.THLIE = 1;
    Can_HwChUnitReg[hwCh]->THLCC[hwCh].B.THLE = 1;

    /* Transmit queue interrupt */
    Can_HwChUnitReg[hwCh]->TXQCC[hwCh].B.TXQIM = 1;
}

static inline void enableErrIrq( uint8 hwCh ) {
    (void)hwCh; /*lint !e920 */
}

static inline void disableRxIrq( uint8 hwCh ) {
    /* Disable FIFO RX interrupt */
    Can_HwChUnitReg[hwCh]->CFCC[HWCH_TO_CHIDX(hwCh)].B.CFRXIE = 0UL;
}

static inline void disableTxIrq( uint8 hwCh ) {
    /* */
    Can_HwChUnitReg[hwCh]->THLCC[hwCh].B.THLIE = 0UL;
    Can_HwChUnitReg[hwCh]->THLCC[hwCh].B.THLE = 0UL;

    /* Transmit queue interrupt */
    Can_HwChUnitReg[hwCh]->TXQCC[hwCh].B.TXQIM = 0UL;
}

static inline void disableErrIrq( uint8 hwCh ) {
    (void)hwCh; /*lint !e920 */
}

static void Can_IsrChRx(uint8 hwChId);
static void Can_IsrChTx(uint8 hwChId);
static void Can_IsrChErr(uint8 hwChId);


static uint32 getChStatus( uint8 hwCh ) {
    return Can_HwUnitReg[hwCh]->CxREGS[hwCh].CxSTS.R;
}


static uint32 getGlobalStatus( uint8 hwCh ) {
    return Can_HwUnitReg[hwCh]->GSTS.R;
}



/*lint -save -e957 No prototype needed for ISR funcs */
#if USE_RSCAN_CH0 == STD_ON
ISR(Can_Ch0_IsrRx) {Can_IsrChRx(RSCAN_CH0);}
ISR(Can_Ch0_IsrTx) {Can_IsrChTx(RSCAN_CH0);}
ISR(Can_Ch0_Err) {Can_IsrChErr(RSCAN_CH0);}
#endif

#if USE_RSCAN_CH1 == STD_ON
ISR(Can_Ch1_IsrRx) {Can_IsrChRx(RSCAN_CH1);}
ISR(Can_Ch1_IsrTx) {Can_IsrChTx(RSCAN_CH1);}
ISR(Can_Ch1_Err) {Can_IsrChErr(RSCAN_CH1);}
#endif

#if USE_RSCAN_CH2 == STD_ON
ISR(Can_Ch2_IsrRx) {Can_IsrChRx(RSCAN_CH2);}
ISR(Can_Ch2_IsrTx) {Can_IsrChTx(RSCAN_CH2);}
ISR(Can_Ch2_Err) {Can_IsrChErr(RSCAN_CH2);}
#endif

#if USE_RSCAN_CH3 == STD_ON
ISR(Can_Ch3_IsrRx) {Can_IsrChRx(RSCAN_CH3);}
ISR(Can_Ch3_IsrTx) {Can_IsrChTx(RSCAN_CH3);}
ISR(Can_Ch3_Err) {Can_IsrChErr(RSCAN_CH3);}
#endif

#if USE_RSCAN_CH4 == STD_ON
ISR(Can_Ch4_IsrRx) {Can_IsrChRx(RSCAN_CH4);}
ISR(Can_Ch4_IsrTx) {Can_IsrChTx(RSCAN_CH4);}
ISR(Can_Ch4_Err) {Can_IsrChErr(RSCAN_CH4);}
#endif

#if USE_RSCAN_CH5 == STD_ON
ISR(Can_Ch5_IsrRx) {Can_IsrChRx(RSCAN_CH5);}
ISR(Can_Ch5_IsrTx) {Can_IsrChTx(RSCAN_CH5);}
ISR(Can_Ch5_Err) {Can_IsrChErr(RSCAN_CH5);}
#endif

#if USE_RSCAN_CH6 == STD_ON
ISR(Can_Ch6_IsrRx) {Can_IsrChRx(RSCAN_CH6);}
ISR(Can_Ch6_IsrTx) {Can_IsrChTx(RSCAN_CH6);}
ISR(Can_Ch6_Err) {Can_IsrChErr(RSCAN_CH6);}
#endif

#if USE_RSCAN_CH7 == STD_ON
ISR(Can_Ch7_IsrRx) {Can_IsrChRx(RSCAN_CH7);}
ISR(Can_Ch7_IsrTx) {Can_IsrChTx(RSCAN_CH7);}
ISR(Can_Ch7_Err) {Can_IsrChErr(RSCAN_CH7);}
#endif
/*lint -restore*/


static void Can_IsrChTx(uint8 hwCh)
{
    uint32 idx;
    PduIdType handle;
    uint32 msgs;

    /* Check the history buffer interrupt */
    if( Can_HwChUnitReg[hwCh]->THLSTS[hwCh].B.THLIF != 0UL ) {

        msgs = Can_HwChUnitReg[hwCh]->THLSTS[hwCh].B.THLMC;

        for(uint32 i=0UL;i<msgs;i++) {

            /** @req 4.1.2/SWS_Can_00016 */
            idx = Can_HwChUnitReg[hwCh]->THLACC[hwCh].B.TID;
            handle = Can_Global.config->CanConfigSetPtr->CanController[HwChannelToChannel((uint8)hwCh)].Can_Arc_TxPduHandles[idx];

            CanIf_TxConfirmation(handle);
            /* Advance to the next message */
            Can_HwChUnitReg[hwCh]->THLPCTR[hwCh].R = 0xffUL;
        }
    } else {
        CAN_ASSERT(0==1);
    }

    /* clean interrupt */
    Can_HwChUnitReg[hwCh]->THLSTS[hwCh].B.THLIF = 0UL;
}

static void Can_IsrChErr(uint8 hwCh)
{
    (void)hwCh; /*lint !e920 */
}


static void Can_IsrChRx(uint8 hwCh)
{
    uint32 fifoCh = (hwCh*3UL) % RSCAN0_HWCH_MAX;
    CAN_CFSTSx_t cfsts = Can_HwChUnitReg[hwCh]->CFSTS[fifoCh];

    /* Any interrupt? */
    if( cfsts.B.CFRXIF == 1U ) {
        /* Loop over all incoming messages */
        for( uint32 i=0UL; i< cfsts.B.CFMC; i++ ) {
            CanIf_RxIndication(
                    (uint8)      Can_HwChUnitReg[hwCh]->CFx[fifoCh].CFPTR.B.CFPTR, 	/* hrh */
                    (Can_IdType) Can_HwChUnitReg[hwCh]->CFx[fifoCh].CFID,
                    (uint8)      Can_HwChUnitReg[hwCh]->CFx[fifoCh].CFPTR.B.CFDLC,
                    (const uint8 *)&Can_HwChUnitReg[hwCh]->CFx[fifoCh].CFDF0 );

            Can_HwChUnitReg[hwCh]->CFPCTR[fifoCh].R = 0xffUL;
        }
        /* Clear RX interrupt */
        Can_HwChUnitReg[hwCh]->CFSTS[fifoCh].B.CFRXIF = 0UL;
    } else {
        CAN_ASSERT(0UL);
    }
}



static boolean setupChannelRxRules( Can_Hw_CtrlType hwCh, const Can_HardwareObjectType *hrhPtr, uint32 ruleCnt, uint32 flags ) {

    /* Need to setup
     * - Number of receive rules
     */
    uint32 rule = 0UL;
    uint32 rxRuleCnt = 0UL;

    volatile CAN_GAFLx_t *gaflPtr;


    /* Write enable page */
    Can_HwChUnitReg[hwCh]->GAFLECTR.B.AFLPN = gPage;		/* Set page */
    Can_HwChUnitReg[hwCh]->GAFLECTR.B.AFLDAE = 1UL;		/* write enable */

    LDEBUG_PRINTF( "\n"
            "Filter Setup ch=%d\n"
            "  Page rule     Code     Mask    GAFLP1\n"
            "-----------------------------------------------\n",hwCh);

    /* Loop over the filters */
    for (uint32 i=0UL;i<ruleCnt; i++ ) {

        if( hrhPtr[i].CanObjectType != CAN_OBJECT_TYPE_RECEIVE) {
            continue;
        }
        rxRuleCnt++;

        gaflPtr = &Can_HwChUnitReg[hwCh]->GAFLx[rule];
        gaflPtr->GAFLID.R = 0x0;
        gaflPtr->GAFLID.B.GAFLID = hrhPtr->CanHwFilterCode;
        if ((CAN_ID_TYPE_EXTENDED == hrhPtr->CanIdType) ||
            ((CAN_ID_TYPE_MIXED == hrhPtr->CanIdType) &&
             ((hrhPtr->CanHwFilterCode & ~STD_CANID_MASK) !=0UL ))) {
            gaflPtr->GAFLID.B.GAFLIDE = 1UL;
        }
        else {
            gaflPtr->GAFLID.B.GAFLIDE = 0UL;
        }
        gaflPtr->GAFLID.B.GAFLRTR = 0UL;
        gaflPtr->GAFLID.B.GAFLLB = ( (flags & CAN_CTRL_LOOPBACK) != 0UL ) ? 1 : 0UL;

        // ID mask register
        gaflPtr->GAFLM.R = 0x0UL;
        gaflPtr->GAFLM.B.GAFLIDM = (vuint32_t)hrhPtr->CanHwFilterMask;
        gaflPtr->GAFLM.B.GAFLIDEM = (vuint32_t)((hrhPtr->CanHwFilterMask & 0x80000000UL) != 0U);
        gaflPtr->GAFLM.B.GAFLRTRM = 0UL;

        // Pointer 0 and 1 registers
        gaflPtr->GAFLP0.R = 0x0UL;
        gaflPtr->GAFLP0.B.GAFLDLC = 0x0UL; 							/* Consider adding support for DLC filtering */
        gaflPtr->GAFLP0.B.GAFLPTR = hrhPtr->CanObjectId;		/* label, 12-bits */

        gaflPtr->GAFLP1.B.GAFLFDP1 = (1UL <<((hwCh*3UL)));			/* Select FIFO */
        LDEBUG_PRINTF("   %02d   %02d   %08x %08x %08x\n",gPage, rule, hrhPtr->CanHwFilterCode,hrhPtr->CanHwFilterMask, gaflPtr->GAFLP1.R );

        rule += 1UL;
        if( rule >= 16UL ) {
            rule = 0UL;
            /* Go to next page */
            gPage++;
            Can_HwChUnitReg[hwCh]->GAFLECTR.B.AFLPN = gPage;
        }
        hrhPtr++;
    }
    gPage++;

    /* Number of entries to write, ie RNC[x] */
    if( hwCh <= 3UL) {
        Can_HwChUnitReg[hwCh]->GAFLCFGx[0U].R = (rxRuleCnt<< ((3UL-hwCh)*8UL));
    } else {
        Can_HwChUnitReg[hwCh]->GAFLCFGx[1].R = (rxRuleCnt<< ((7UL-hwCh)*8UL));
    }

    Can_HwChUnitReg[hwCh]->GAFLECTR.B.AFLDAE = 0UL;		/* write disable */
    Can_HwChUnitReg[hwCh]->RMNB.R = 0UL;				/* We don't use receive buffers */

    return TRUE;
}

static void installControllerInterrupts(uint8 hwChId, uint32 ArcFlags)
{
    switch (hwChId) {
#if USE_RSCAN_CH0 == STD_ON
    case RSCAN_CH0:
        ADD_ISR_HANDLERS(0, ArcFlags);
        break;
#endif
#if USE_RSCAN_CH1 == STD_ON
    case RSCAN_CH1:
        ADD_ISR_HANDLERS(1, ArcFlags);
        break;
#endif
#if USE_RSCAN_CH2 == STD_ON
    case RSCAN_CH2:
        ADD_ISR_HANDLERS(2, ArcFlags);
        break;
#endif
#if USE_RSCAN_CH3 == STD_ON
    case RSCAN_CH3:
        ADD_ISR_HANDLERS(3, ArcFlags);
        break;
#endif
#if USE_RSCAN_CH4 == STD_ON
    case RSCAN_CH4:
        ADD_ISR_HANDLERS(4, ArcFlags);
        break;
#endif
#if USE_RSCAN_CH5 == STD_ON
    case RSCAN_CH5:
        ADD_ISR_HANDLERS(5, ArcFlags);
        break;
#endif
#if USE_RSCAN_CH6 == STD_ON
    case RSCAN_CH6:
        ADD_ISR_HANDLERS(6, ArcFlags);
        break;
#endif
#if USE_RSCAN_CH7 == STD_ON
    case RSCAN_CH7:
        ADD_ISR_HANDLERS(7, ArcFlags);
        break;
#endif
    default:
        /* Unexpected channel */
        DET_REPORTERROR(CAN_MODULE_ID, 0, CAN_GLOBAL_ID, CAN_E_UNEXPECTED_EXECUTION);
        break;
    }
}


/**
 * Initializes the CAN driver
 * @param Config - a pointer to the configuration that is used during initialization
 */
void Can_Hw_Init(void)
{
    /** !req 4.1.2/SWS_Can_00408 */
    /** !req 4.1.2/SWS_Can_00419 *//* Disable all unused interrupts. We only enable the ones used. */
    /** !req 4.1.2/SWS_Can_00053 *//* Don't change registers for controllers not used. */
    /** !req 4.1.2/SWS_Can_00250 *//* Initialize variables, init controllers. */
    /** !req 4.1.2/SWS_Can_00239 *//* Init all on chip hardware */
    uint32 ctrlMask = 0UL;
    uint32 ctrlMaskSaved = 0UL;

    uint32 i = 0UL;
    uint8 hwCh = RSCAN_CH0;
    uint8 hwChIndex = 0UL;
    const Can_ControllerConfigType *ctrlPtr;
    uint32 flags;

    /* Follow "RS-CAN Setting Procedure" in HW REF
     * RH850F1H - Figure 20.19
     * 1. Global:   STOP->RESET
     * 2. Channel:  STOP->RESET
     * 3. Channel:  Configure channels
     * 4. Global:   RESET->GLOBAL OPERATING
     * 5. Channel:  RESET->COMMUNICATION MODE
     * */

#if RSCAN0_IN_USE == 1
    ctrlMask |= (1UL<<0U);
#endif
#if RSCAN1_IN_USE == 1
    ctrlMask |= (1UL<<1U);
#endif

    ctrlMaskSaved = ctrlMask;

    for( ; ctrlMask != 0UL; ctrlMask &= ~(1UL << i) ) {
        i = ilog2(ctrlMask);

        /* Init RAM */
        while( Can_HwUnitReg[i]->GSTS.B.GRAMINIT == 1UL ) { }

        /* 1) Global: STOP -> RESET */
        Can_HwUnitReg[i]->GCTR.B.GSLPR = 0UL;

        while( (getGlobalStatus(i) & R_CAN_GSLPSTS_ON ) != 0UL  ) { }


#if (USE_CAN_OSCILLATOR_CLOCK == STD_ON)
        Can_HwUnitReg[i]->GCFG.B.DCS = 1;
#else
        Can_HwUnitReg[i]->GCFG.B.DCS = 0UL;
#endif
        Can_HwUnitReg[i]->GCFG.B.TSSS = 0x0; // Timestamp Source Select pclk/2
        Can_HwUnitReg[i]->GCFG.B.TSBTCS = 0x0;
    }


    /* Loop over all configured channels */
    for (uint8 ch = 0U; ch < CAN_ARC_CTRL_CONFIG_CNT; ch++) {
        hwCh = ChannelToHwChannel(ch);
        hwChIndex = HWCH_TO_CHIDX(hwCh);

        /* 2) Channel: STOP -> RESET */
        Can_HwChUnitReg[hwCh]->CxREGS[hwCh % RSCAN0_HWCH_MAX].CxCTR.B.CSLPR = 0UL; /* CSLPR=0 */
        while ( (getChStatus(hwCh) & R_CAN_CSLPSTS_ON) != 0UL ) {}

        /* 3) Configure channel  */
        ctrlPtr = &Can_Global.config->CanConfigSetPtr->CanController[ch];
        Can_Hw_ChangeBaudrate(hwCh, ctrlPtr->CanControllerDefaultBaudrate );
        /* Check that correctly sorted in generator */
        CONFIG_ASSERT(ctrlPtr->Can_Arc_HwUnitId == hwCh );

        setupChannelRxRules(hwCh,ctrlPtr->Can_Arc_Hoh, ctrlPtr->Can_Arc_HohCnt, ctrlPtr->Can_Arc_Flags );

        Can_HwChUnitReg[hwCh]->CxREGS[hwCh].CxCTR.B.BOM = 3;


        /*
         * Transmit queues
         */
        Can_HwChUnitReg[hwCh]->TXQCC[hwCh].B.TXQDC = 15U;   /* Transmit Queue Length (2..15) */
        Can_HwChUnitReg[hwCh]->TXQCC[hwCh].B.TXQIM = 1U;    /* IRQ for every buffer transmitted for now... */
        Can_HwChUnitReg[hwCh]->TXQCC[hwCh].B.TXQIE = 0UL;

        /* Transmit history */
        Can_HwChUnitReg[hwCh]->THLCC[hwCh].B.THLDTE = 0UL;  /* Setup transmit history*/
        Can_HwChUnitReg[hwCh]->THLCC[hwCh].B.THLIM = 1U;    /* Enable Transmit History Buffers */

        /* Set the THLE bit later, can only be set in communication mode or halt mode */

        flags = Can_Global.config->CanConfigSetPtr->CanController[ch].Can_Arc_Flags;

        /*
         * Rx/Tx FIFO (used as Rx)
         */
        Can_HwChUnitReg[hwCh]->CFCC[hwChIndex].B.CFM = 0UL;	    /* RX mode */
        Can_HwChUnitReg[hwCh]->CFCC[hwChIndex].B.CFIM  = 1U;	/* Generate interrupt for each = 1 */
        Can_HwChUnitReg[hwCh]->CFCC[hwChIndex].B.CFDC = 2U; 	/* 8 messages */

        LDEBUG_PRINTF( "\n"
                "RX/TX FIFO: %08x %s\n",Can_HwChUnitReg[hwCh]->CFCC[hwChIndex], "0x00001203" );

        if( flags & CAN_CTRL_RX_PROCESSING_INTERRUPT ) {
            enableRxIrq(hwCh);
        }

        if( flags & CAN_CTRL_TX_PROCESSING_INTERRUPT ) {
            enableTxIrq(hwCh);
        }

        installControllerInterrupts(hwCh,flags);
    }


    ctrlMask = ctrlMaskSaved;
    for( ; ctrlMask != 0ULL; ctrlMask &= ~(1ULL << i) ) {
        i = ilog2(ctrlMask);

        /* 4) Global:   RESET->GLOBAL OPERATING */
        Can_HwUnitReg[i]->GCTR.B.GMDC = 0UL;
        while ( (getGlobalStatus(i) & R_CAN_GRSTSTS_ON) != 0UL ) {}
    }

    /* Note! Don't start the channel here, it's done in Can_SetControllerMode() */
}


/**
 * Changes the controller mode
 * @param Controller - controller id
 * @param Transition - type of transition to be made
 * @return CAN_OK if request accepted, otherwise CAN_NOT_OK
 */
Can_ReturnType Can_Hw_SetControllerMode(uint8 hwCh, Can_StateTransitionType Transition) {

    switch(Transition) {
    case CAN_T_START:
        if( Can_Global.config->CanConfigSetPtr->CanController[HwChannelToChannel(hwCh)].Can_Arc_Flags & CAN_CTRL_LOOPBACK )
        {
            /* -> HALT */
            Can_HwChUnitReg[hwCh]->CxREGS[hwCh % RSCAN0_HWCH_MAX].CxCTR.B.CHMDC = 2;
            while ( (getChStatus(hwCh) & R_CAN_CRSTSTS_ON) != 0UL ) {}

            Can_HwChUnitReg[hwCh]->CxREGS[hwCh % RSCAN0_HWCH_MAX].CxCTR.B.CTMS = 3UL; 	/* Internal loopback mode */
            Can_HwChUnitReg[hwCh]->CxREGS[hwCh % RSCAN0_HWCH_MAX].CxCTR.B.CTME = 1UL;		/* Enable test-mode */
            LDEBUG_PRINTF("-- Enabling loopback mode!\n");

        }
        /* 5) Channel: RESET -> COMM */
        Can_HwChUnitReg[hwCh]->CxREGS[hwCh % RSCAN0_HWCH_MAX].CxCTR.R &= ~7UL;  /* CSLPR=0, CHMDC=0 */
        while ( (getChStatus(hwCh) & R_CAN_CRSTSTS_ON) != 0UL ) {}

        /* Enable the receive FIFO */
        Can_HwChUnitReg[hwCh]->CFCC[HWCH_TO_CHIDX(hwCh)].B.CFE = 1;

        /* Enable the Queue */
        Can_HwChUnitReg[hwCh]->TXQCC[hwCh].B.TXQE = 1;

        /* Enable Transmit history */
        Can_HwChUnitReg[hwCh]->THLCC[hwCh].B.THLE = 1;

        break;
    case CAN_T_STOP:
    case CAN_T_SLEEP:
    case CAN_T_WAKEUP:
        /* -> HALT */
        Can_HwChUnitReg[hwCh]->CxREGS[hwCh % RSCAN0_HWCH_MAX].CxCTR.B.CHMDC = 2;
        while ( (getChStatus(hwCh) & R_CAN_CRSTSTS_ON) != 0UL ) {}

        break;
    default:
        CAN_ASSERT(0);
        break;
    }

    return CAN_OK;
}


Can_Arc_ModeType Can_Hw_GetControllerMode( uint8 hwCh ) {

    const CAN_CxREGS_t *hwPtr = &Can_HwUnitReg[hwCh]->CxREGS[hwCh];
    Can_Arc_ModeType mode;

    if( hwPtr->CxSTS.B.CSLPSTS == 1 ) {
        mode = CAN_CTRL_MODE_STOP;
    } else if (hwPtr->CxSTS.B.CHLTSTS == 1) {
        //mode = CAN_CTRL_MODE_HALT;
        mode = CAN_CTRL_MODE_STOP;
    } else if (hwPtr->CxSTS.B.CRSTSTS == 1) {
        mode = CAN_CTRL_MODE_RESET;
    } else {
        mode =  CAN_CTRL_MODE_COMM;
    }
    return mode;
}


/**
 *
 * @param Controller Controller identifier.
 */
void Can_Hw_DisableControllerInterrupts(uint8 hwCh)
{
    /** @req 4.1.2/SWS_Can_00231 */
    /** @req 4.1.2/SWS_Can_00202 */
    /** !req 4.1.2/SWS_Can_00204 */

    disableRxIrq(hwCh);
    disableTxIrq(hwCh);
    disableErrIrq(hwCh);

    return;
}


/**
 * Enables interrupts for a controller
 * @param Controller - controller id
 */
void Can_Hw_EnableControllerInterrupts(uint8 hwCh)
{
    /** @req 4.1.2/SWS_Can_00232 */
    /** @req 4.1.2/SWS_Can_00050 */
    enableRxIrq(hwCh);
    enableTxIrq(hwCh);
    enableErrIrq(hwCh);
}


/**
 * Checks if a wakeup has occurred for a given controller
 * @param Controller - controller id
 * @return CAN_OK if wakeup was detected, otherwise CAN_NOT_OK
 */
Can_ReturnType Can_Hw_CheckWakeup(uint8 Controller)
{
    /** !req 4.1.2/SWS_Can_00360 */
    /** !req 4.1.2/SWS_Can_00361 */
    /** !req 4.1.2/SWS_Can_00362 */
    /** !req 4.1.2/SWS_Can_00363 */
    /** !req 4.1.2/SWS_Can_00484 */
    /** !req 4.1.2/SWS_Can_00485 */

    /* NOT SUPPORTED */
    (void) Controller;
    return CAN_NOT_OK;
}


/**
 *
 * @param Hth - the HardwareTransmitHandle to be used
 * @param PduInfo - pointer to SDU
 * @return CAN_OK if write was accepted, CAN_NOT_OK if error occurred, CAN_BUSY if not buffer available
 */
Can_ReturnType Can_Hw_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo) {
    /** @req 4.1.2/SWS_Can_00233 */
    /** @req 4.1.2/SWS_Can_00214 */
    /** @req 4.1.2/SWS_Can_00272 */
    /** @req 4.1.2/SWS_Can_00011 */
    /** @req 4.1.2/SWS_Can_00275 */
    /** @req 4.1.2/SWS_Can_00212 */

    Can_HwHandleType internalHth;
    uint8 ch;
    uint8 hwCh;
    CAN_TXBUF_t *pushPtr;
    const Can_HardwareObjectType *hohObj;
    Can_ReturnType rv = CAN_OK;

    internalHth =
            Can_Global.config->CanConfigSetPtr->ArcSymbolicHohToInternalHoh[Hth];
    VALIDATE_RV( (internalHth < NUM_OF_HTHS ), 0x6, CAN_E_PARAM_HANDLE, CAN_NOT_OK );

    ch =
            Can_Global.config->CanConfigSetPtr->ArcHthToSymbolicController[internalHth];
    hwCh = ChannelToHwChannel(ch);
    hohObj =
            &Can_Global.config->CanConfigSetPtr->CanController[ch].Can_Arc_Hoh[Can_Global.config->CanConfigSetPtr->ArcHthToHoh[internalHth]];

    if (Can_HwChUnitReg[ch]->TXQSTS[hwCh].B.TXQFLL == 0UL) {
        /* Get the "push" data to queue entry */
        pushPtr = &Can_HwChUnitReg[hwCh]->TMx[15U];
        pushPtr->TMIDx.R = 0UL;
        pushPtr->TMIDx.B.TMIDE = (vuint32_t) ((hohObj->CanIdType == CAN_ID_TYPE_EXTENDED) || (hohObj->CanIdType == CAN_ID_TYPE_MIXED));
        pushPtr->TMIDx.B.THLEN = 1U; /* Transmit history */
        pushPtr->TMIDx.B.TMID = (vuint32_t) PduInfo->id;

        pushPtr->TMPTRx.R = 0UL;
        pushPtr->TMPTRx.B.TMDLC = (uint32) PduInfo->length;
        pushPtr->TMPTRx.B.TMPTR = Can_PduIndex[hwCh]; /* Use label to store index of PDU handle ID */
        Can_Global.config->CanConfigSetPtr->CanController[ch].Can_Arc_TxPduHandles[Can_PduIndex[hwCh]] = PduInfo->swPduHandle;
        Can_PduIndex[hwCh] += ((Can_PduIndex[hwCh] + 1U) % 16U);

        /** @req 4.1.2/SWS_Can_000059 *//* Definition of data structure */
        memset((void *) &pushPtr->TMDF0x.R, 0UL, 8U); /*lint !e419 Ok since PDU data starts at base of TMDF0 and spans 8 bytes */
        memcpy((void *) &pushPtr->TMDF0x.R, PduInfo->sdu, (size_t)(PduInfo->length));

        Can_HwChUnitReg[hwCh]->TXQPCTR[hwCh].R = 0xffUL;
    } else {
        rv = CAN_BUSY;
    }

    memset(Can_PduIndex,0UL,sizeof(Can_PduIndex));

    return rv;

}

Std_ReturnType Can_Hw_ChangeBaudrate(uint8 HwController, const Can_ControllerBaudrateConfigType *baudratePtr ) {
    uint32 tq;
    uint32 tseg1;
    uint32 tseg2;
    uint32 sjw;
    uint32 clock;
    CAN_CxREGS_t *cxPtr = &Can_HwChUnitReg[HwController]->CxREGS[HwController % RSCAN0_HWCH_MAX ];
    uint32_t prescaler;

    /* Calculate the number of timequanta's*/
    tseg1 = baudratePtr->CanControllerPropSeg + baudratePtr->CanControllerSeg1; /*lint !e9031 Ok to assign to wider type */
    tseg2 = baudratePtr->CanControllerSeg2;
    tq = 1UL + tseg1 + tseg2;
    sjw = baudratePtr->CanControllerSyncJumpWidth;

    // Check TQ limitations..
    VALIDATE(( (tseg1>=4UL) && (tseg1<=16UL)), CAN_E_PARAM_TIMING, E_NOT_OK);
    VALIDATE(( (tseg2>=2UL) && (tseg2<=8UL)), CAN_E_PARAM_TIMING, E_NOT_OK);
    VALIDATE(( (tq>8UL) && (tq<25UL )), CAN_E_PARAM_TIMING, E_NOT_OK);
    VALIDATE(( (sjw>=1UL) && (sjw<=4UL )), CAN_E_PARAM_TIMING, E_NOT_OK);

    /*
    * RSCAN needs two clocks
    * 1. pclk (C_ISO_CAN)
    * 2. clkc(PPLLCLK2 and DCS=0) or clk_xincan(C_ISO_CANOSC and DCS=1)
    *
    * The DCS bit selects the clock to use in 2) and the clocks in 2) is
    * not modulated (not derived from PLL0 that can be modulated).
    * */

#if (USE_CAN_OSCILLATOR_CLOCK == STD_ON)
    clock = Mcu_Arc_GetPeripheralClock(C_ISO_CANOSC);
#else
    clock = Mcu_Arc_GetPeripheralClock(C_PPLLCLK2);
#endif

    cxPtr->CxCFG.R = 0UL;
    prescaler = (vuint32_t)(clock / (baudratePtr->CanControllerBaudRate * 1000UL * tq)) - 1UL;
    cxPtr->CxCFG.B.BRP = prescaler;
    cxPtr->CxCFG.B.TSEG1 = tseg1 - 1UL;
    cxPtr->CxCFG.B.TSEG2 = tseg2 - 1UL;
    cxPtr->CxCFG.B.SJW   = sjw - 1UL;

    /* Make sure we have a perfect match */
    CONFIG_ASSERT( (clock/(tq*(prescaler+1UL))) == ((uint32)baudratePtr->CanControllerBaudRate * 1000UL) );

    return 0UL;
}



#if (CAN_USE_WRITE_POLLING == STD_ON)
/**
 *
 */
void Can_Hw_MainFunction_Write( void )
{
    /** @req 4.1.2/SWS_Can_00225 */
    /** @req 4.1.2/SWS_Can_00031 */
    /** !req 4.1.2/SWS_Can_00441 */

    UnitType *unitPtr;

    /* Write polling events. */
    for (uint8 controllerId = 0U; controllerId < CAN_ARC_CTRL_CONFIG_CNT; controllerId++)
    {
        unitPtr = CTRL_TO_UNIT_PTR(controllerId);
        if( (unitPtr->cfgCtrlPtr->Can_Arc_Flags & CAN_CTRL_TX_PROCESSING_INTERRUPT) == 0U )
        {
            isrTx(unitPtr);
        }
    }
}
#endif /* CAN_USE_WRITE_POLLING == STD_ON */


#if (CAN_USE_READ_POLLING == STD_ON)
/**
 * This function performs the polling of RX indications when
 * CAN_RX_PROCESSING is set to POLLING.
 */

void Can_Hw_MainFunction_Read(void)
{
    /** @req 4.1.2/SWS_Can_00226 */
    /** @req 4.1.2/SWS_Can_00108 */
    /** !req 4.1.2/SWS_Can_00442 */

    const UnitType *unitPtr;

    /* Read polling events. */
    for (uint8 controllerId = 0U; controllerId < CAN_ARC_CTRL_CONFIG_CNT; controllerId++)
    {
        unitPtr = CTRL_TO_UNIT_PTR(controllerId);
        if( (unitPtr->cfgCtrlPtr->Can_Arc_Flags & CAN_CTRL_RX_PROCESSING_INTERRUPT) == 0U )
        {
            isrRx(unitPtr);
        }
    }
}
#endif /*CAN_USE_READ_POLLING == STD_ON*/



#if (CAN_USE_BUSOFF_POLLING == STD_ON)
/**
 * This function performs the polling of bus-off events that are configured statically as
 * 'to be polled'.
 */
void Can_Hw_MainFunction_BusOff(void)
{
    /** @req 4.1.2/SWS_Can_00227 */
    /** @req 4.1.2/SWS_Can_00109 */

    const UnitType *unitPtr;

    /* Bus-off polling events. */
    for (uint8 controllerId = 0U; controllerId < CAN_ARC_CTRL_CONFIG_CNT; controllerId++)
    {
        unitPtr = CTRL_TO_UNIT_PTR(controllerId);
        if( (unitPtr->cfgCtrlPtr->Can_Arc_Flags & CAN_CTRL_BUSOFF_PROCESSING_INTERRUPT) == 0U )
        {
            isrBusoff(unitPtr);
        }
    }
}
#endif /* CAN_USE_BUSOFF_POLLING == STD_ON */


#if (ARC_CAN_ERROR_POLLING == STD_ON)
/**
 * This function performs the polling of error events that are configured statically as
 * 'to be polled'.
 */
void Can_Arc_Hw_MainFunction_Error(void)
{
    /* Error polling events (not in req spec)*/
    const UnitType *unitPtr;

    /* Error polling events. */
    for (uint8 controllerId = 0U; controllerId < CAN_ARC_CTRL_CONFIG_CNT; controllerId++)
    {
        unitPtr = CTRL_TO_UNIT_PTR(controllerId);
        if( (unitPtr->cfgCtrlPtr->Can_Arc_Flags & CAN_CTRL_ERROR_PROCESSING_INTERRUPT) == 0U )
        {
            isrError(unitPtr);
        }
    }
}
#endif /* CAN_USE_BUSOFF_POLLING == STD_ON */


#if (CAN_USE_WAKEUP_POLLING == STD_ON)
/**
 * This function performs the polling of wake-up events that are configured statically
 * as 'to be polled'.
 */
void Can_Hw_MainFunction_Wakeup(void)
{
    /** !req 4.1.2/SWS_Can_00228 */
    /** !req 4.1.2/SWS_Can_00112 */
    /** @req 4.1.2/SWS_Can_00185*/

    /* Wakeup polling events. */
    /* NOT SUPPORTED */
}
#endif /* CAN_USE_WAKEUP_POLLING == STD_ON */

/**
 * This function performs the polling of CAN controller mode transitions.
 */
void Can_Hw_MainFunction_Mode(void)
{
    /** @req 4.1.2/SWS_Can_00368 *//* API */
    /** @req 4.1.2/SWS_Can_00369 *//* Polling */
    /** !req 4.1.2/SWS_Can_00398 *//* Blocking call not supported */
    /** !req 4.1.2/SWS_Can_00371 *//* Blocking call not supported */
    /** !req 4.1.2/SWS_Can_00372 *//* Blocking call not supported */

}

/**
 * Unitialize the module
 */
void Can_Arc_Hw_DeInit(void)
{
}
