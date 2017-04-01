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

#include "Mcu.h"
#include "Lin.h"
#include "LinFlex_Common.h"
#if defined(USE_CDD_LINSLV)
#include "LinIf_Types.h"
#endif

/* ----------------------------[private macro]-------------------------------*/
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
#if defined(USE_CDD_LINSLV)
#define LINFLEXSLV(exp) (volatile struct LINFLEX_MS_tag *)(0xFFE40000uL + (0x4000uL * exp))
#endif
#endif

#if (defined(CFG_MPC5606B) && !defined(CFG_MPC5607B)) || defined(CFG_MPC5645S) || defined(CFG_MPC5744P) || defined(CFG_MPC5777M) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C) || defined(CFG_MPC5746C)
#define LINFLEX_DIV_M_SIZE  20uL
#elif defined(CFG_MPC5643L) || defined(CFG_SPC56XL70)
#define LINFLEX_DIV_M_SIZE  19uL
#elif defined(CFG_SPC560B54)
#define LINFLEX_DIV_M_SIZE  13uL
#else
#define LINFLEX_DIV_M_SIZE  13uL
#endif

#if (( defined(LINSLV_DEV_ERROR_DETECT) && (LINSLV_DEV_ERROR_DETECT == STD_ON) ) || ( defined(LIN_DEV_ERROR_DETECT) && (LIN_DEV_ERROR_DETECT == STD_ON) ))
#define VALIDATE_PTR(_exp ) \
        if( !(_exp) ) { \
          return; \
        }

#define VALIDATE_PTR_W_RV(_exp,_rv ) \
        if( !(_exp) ) { \
          return (_rv); \
        }
#else
#define VALIDATE_PTR(_exp )
#define VALIDATE_PTR_W_RV(_exp,_rv )
#endif
/* ----------------------------[private define]------------------------------*/
#define LIN_MAX_MSG_LENGTH  8u
#define NBR_DATA_BYTES      LIN_MAX_MSG_LENGTH

#define MASK_LINCR2_DDRQ        (uint32)0x800UL
#define MASK_LINCR2_ABRQ        (uint32)0x200UL
#define MASK_LINSR_LINS         (uint32)0xF000UL
#define MASK_LINSR_LINS_INIT    (uint32)0x1000UL
#define MASK_LINSR_LINS_IDLE    (uint32)0x2000UL
#define MAX_WAIT_CYCLES         (uint32)10000UL

#define SHIFT_IFCR_DFL      10u
#define MASK_IFCR_DIR       (uint32)0x200uL
#define MASK_IFCR_CSS       (uint32)0x100uL
#define MASK_IDENTIFIER     (uint32)0x3FuL
#define MAX_FILTER_COUNT    16u

#define LINS_SLEEP          (uint32)0x0u
#define LINS_IDLE           (uint32)0x2u
#define LINS_GENERAL_BUSY   (uint32)0x3u

#define LINFLEX_DIV_M_MAX ((1uL<<LINFLEX_DIV_M_SIZE) - 1)
/* ----------------------------[private function prototypes]-----------------*/
#if defined(CFG_MPC5606S)
static Std_ReturnType waitWhileBusy(volatile const uint16 *regBaseAddr, uint32 mask, uint32 compMask, boolean retCondition);
#else
static Std_ReturnType waitWhileBusy(volatile const uint32 *regBaseAddr, uint32 mask, uint32 compMask, boolean retCondition);
#endif
/* ----------------------------[private variables]---------------------------*/
static boolean isChnConfigured[16] = {0};
/* ----------------------------[functions]-----------------------------------*/

Std_ReturnType LinFlex_Common_Init(const Lin_ChannelConfigType *channelCfg, LinFlex_ModeType mode) {
    volatile struct LINFLEX_tag * LINFLEXHw;
    uint32 chnId = channelCfg->LinChannelId;

    /* Input pointer check */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_PTR_W_RV((NULL != channelCfg), E_NOT_OK);

    /* Check if the channel has been configured */
    /* @req CDD_LinSlv_00004 */
    if (TRUE == isChnConfigured[chnId]) {
        //Set Error, channel has already been configured.
        /*lint -e{904} PERFORMANCE reduce cyclomatic complexity */
        return E_NOT_OK;
    }
    isChnConfigured[chnId] = TRUE;

    /*lint -e{923,9033} Hardware access */
    LINFLEXHw = LINFLEX(chnId);

   /* configure and enable channel */
    LINFLEXHw->LINCR1.B.INIT = 1; /* Go to init mode */
    LINFLEXHw->LINCR1.R = 1; /* Clear all */
    LINFLEXHw->LINCR1.B.MBL = 3; /* 13 bit synch */

    /* Wait for controller to enter init mode */
    if (E_NOT_OK == waitWhileBusy(&LINFLEXHw->LINSR.R, MASK_LINSR_LINS, MASK_LINSR_LINS_INIT, TRUE)) {
        /*lint -e{904} PERFROMANCE reduce cyclomatic complexity */
        return E_NOT_OK;
    }

    if (LIN_MASTER == mode) {
        LINFLEXHw->LINCR1.B.MME = 1; /* Master mode */
        LINFLEXHw->LINCR1.B.LASE = 0;
    } else {
        LINFLEXHw->LINCR1.B.MME = 0; /* Slave mode */
        LINFLEXHw->LINCR1.B.LASE = 1;
    }
    LINFLEXHw->LINCR1.B.CCD = 0;
    LINFLEXHw->LINCR1.B.CFD = 0;
    LINFLEXHw->LINCR1.B.AWUM = 0;
    LINFLEXHw->LINCR1.B.BF = 0;
#if !(defined(CFG_MPC5746C))
    LINFLEXHw->LINCR1.B.SLFM = 0;
#endif
    LINFLEXHw->LINCR1.B.LBKM = 0;
    LINFLEXHw->LINCR1.B.SBDT = 0;
    LINFLEXHw->LINCR1.B.RBLM = 0;
    LINFLEXHw->LINCR1.B.SLEEP = 0;

    LINFLEXHw->LINIER.R = 0; /* Reset all bits */

    LINFLEXHw->LINIER.B.BEIE = 1; /* Bit error */
    LINFLEXHw->LINIER.B.CEIE = 1; /* Checksum error */
    LINFLEXHw->LINIER.B.HEIE = 1; /* Header error */
    LINFLEXHw->LINIER.B.FEIE = 1; /* Framing error */
    /** Report timeout of response by enabling OCIE and enabling timeout mode */
    LINFLEXHw->LINIER.B.OCIE = 1; /* Output compare interrupt enable */
    if (LIN_MASTER == mode) {
        LINFLEXHw->LINIER.B.BOIE = 1; /* Buffer overrun error */
    } else {
        LINFLEXHw->LINIER.B.SZIE = 1;
    }
    LINFLEXHw->LINIER.B.DRIE = 1; /* Data Reception Complete */
    LINFLEXHw->LINIER.B.DTIE = 1; /* Data Transmitted */

#if defined(USE_CDD_LINSLV)
    if (LIN_SLAVE == mode) {
        LINFLEXHw->LINIER.B.HRIE = 1;
        LINFLEXHw->LINTOCR.B.RTO = 0xFuL;
    }
#endif
    /*
     * Tx/ Rx baud = fperiph_set_1_clk / (16 � LFDIV)
     * To program LFDIV = 25.62d,
     * LINFBRR = 16 � 0.62 = 9.92, nearest real number 10d = 0xA
     * LINIBRR = mantissa (25.620d) = 25d = 0x19
     */
    /** @req SWS_Lin_00150 */
    uint32 lfdiv = (uint32)(Mcu_Arc_GetPeripheralClock((Mcu_Arc_PeriperalClock_t)channelCfg->LinClockRef) / (channelCfg->LinChannelBaudRate));

    LINFLEXHw->LINFBRR.B.DIV_F = (uint8)(lfdiv % 16); /* Fraction bits */
    if( (lfdiv / 16) > LINFLEX_DIV_M_MAX ) {
        //LIN_DET_REPORT_ERROR(LIN_INIT_SERVICE_ID, LIN_E_INVALID_CONFIG);
        LINFLEXHw->LINIBRR.B.DIV_M = LINFLEX_DIV_M_MAX;
    } else {
        LINFLEXHw->LINIBRR.B.DIV_M = (lfdiv / 16); /* Integer bits */
    }

    LINFLEXHw->LINCR2.R = 0; /* Reset all bits */
    if (LIN_MASTER == mode) {
        LINFLEXHw->LINCR2.B.IOBE = 1; /* Idle on bit error */
        LINFLEXHw->LINCR2.B.IOPE = 1; /* Idle on parity error */
    }

    /* Status regs */
    LINFLEXHw->LINSR.R = 0xffffffffuL; /* Reset all bits */
    LINFLEXHw->LINESR.R = 0xffffffffuL; /* Reset all bits */

    LINFLEXHw->LINTCSR.B.LTOM = 0;//Enable timeout mode
    LINFLEXHw->LINTCSR.B.IOT = 0;//Disable idle mode on timeout

    LINFLEXHw->LINCR1.B.INIT = 0; /* Go to normal mode */

    return E_OK;
}


void LinFlex_Common_DeInit(const Lin_ChannelConfigType *channelCfg) {
    volatile struct LINFLEX_tag * LINFLEXHw;
    uint32 chnId;
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_PTR((NULL != channelCfg));

    chnId = channelCfg->LinChannelId;
    /*lint -e{923,9033} Hardware access */
    LINFLEXHw = LINFLEX(chnId);

    /* Disable */
    LINFLEXHw->LINCR1.R = 0; /* Reset all bits */
    LINFLEXHw->LINIER.R = 0; /* Reset all bits */
    LINFLEXHw->LINSR.R = 0xffffffffuL; /* Reset all bits */
    LINFLEXHw->LINESR.R = 0xffffffffuL; /* Reset all bits */

    isChnConfigured[chnId] = FALSE;
}

/**
 * Setup slave filter rules
 * @param channelCfg
 * @param LinSlvFrameSetupConfigData
 * @return
 */
#if defined(USE_CDD_LINSLV)
/* @req CDD_LinSlv_00005 */
Std_ReturnType LinFlex_Common_SetupSlvFilter(const Lin_ChannelConfigType *channelCfg, const LinSlv_FrameSetupType *LinSlvFrameSetupConfigData) {
    volatile struct LINFLEX_MS_tag * LINFLEXHw;
    const LinIf_FrameType *frameCfg;
    uint32 fact = 0;
    uint32 dfl;
    uint32 dir;
    uint32 ccs;
    uint32 id;
    uint8 i;

    VALIDATE_PTR_W_RV((NULL != channelCfg), E_NOT_OK);
    VALIDATE_PTR_W_RV((NULL != LinSlvFrameSetupConfigData), E_NOT_OK);

    if (LinSlvFrameSetupConfigData->LinSlvChnlFrameCnt > MAX_FILTER_COUNT) {
        return E_NOT_OK;
    }

    /*lint -e{923,9033} Hardware access */
    LINFLEXHw = LINFLEXSLV(channelCfg->LinChannelId);

    LINFLEXHw->LINCR1.B.INIT = 1;     /* Go to init mode */
    LINFLEXHw->IFER.R = 0;            /* Disable all filters */
    LINFLEXHw->IFMR.R = 0x00000000;    /* Set all filter to identifier mode */

    for (i = 0; i < LinSlvFrameSetupConfigData->LinSlvChnlFrameCnt; i++) {
        frameCfg = LinSlvFrameSetupConfigData->LinSlvChnFrameCfg[i];

        dfl = (uint32)(frameCfg->LinIfLength - 1uL) << SHIFT_IFCR_DFL;
        dir = ((LinIfTxPdu == frameCfg->LinIfPduDirection) || (SRF == frameCfg->LinIfFrameType)) ? MASK_IFCR_DIR : 0uL;
        ccs = (CLASSIC    == frameCfg->LinIfChecksumType) ? MASK_IFCR_CSS : 0uL;
        id = frameCfg->LinIfPid & MASK_IDENTIFIER; /* Mask out the parity bits */

        LINFLEXHw->IFCR[i].R = (dfl | dir | ccs | id);

        fact |= 1uL << i;
    }

    LINFLEXHw->IFER.R          = fact;  /* Enable the configured filters */
    LINFLEXHw->LINCR1.B.INIT = 0;     /* Leave init mode */

    return E_OK;
}
#endif

/**
 * Enter power save mode.
 * @param channelCfg
 */
void LinFlex_Common_GoToSleepInternal(const Lin_ChannelConfigType *channelCfg) {
    /*lint -e{923,9033} Hardware access */
    volatile struct LINFLEX_tag * LINFLEXHw = LINFLEX(channelCfg->LinChannelId);
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_PTR((NULL != channelCfg));

    /** @req SWS_Lin_00223 */
    //Enter power saving mode
    LINFLEXHw->LINCR1.B.SLEEP = 1;

    if (TRUE == channelCfg->LinChannelWakeUpSupport) {
        //Enable wake-up interrupt
        LINFLEXHw->LINIER.B.WUIE = 1;
    }
}

/**
 * Enter operational state
 * @param channelCfg
 */
void LinFlex_Common_WakeupInternal(const Lin_ChannelConfigType *channelCfg) {
    /*lint -e{923,9033} Hardware access */
    volatile struct LINFLEX_tag * LINFLEXHw = LINFLEX(channelCfg->LinChannelId);
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_PTR((NULL != channelCfg));

    //Clear power saving mode
    LINFLEXHw->LINCR1.B.SLEEP = 0;

    //Disable wake-up interrupt
    LINFLEXHw->LINIER.B.WUIE = 0;
}

/**
 * Transmits a wake-up on the bus
 * @param channelCfg
 */
Std_ReturnType LinFlex_Common_Wakeup(const Lin_ChannelConfigType *channelCfg) {

    Std_ReturnType status;
    status = E_OK;
    /*lint -e{923,9033} Hardware access */
    volatile struct LINFLEX_tag * LINFLEXHw = LINFLEX(channelCfg->LinChannelId);
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_PTR_W_RV((NULL != channelCfg), E_NOT_OK);

    //Clear power saving mode
    LINFLEXHw->LINCR1.B.SLEEP = 0;

    /* The Wake-up Generation Request bit can't be set in sleep mode */
    if (E_NOT_OK == waitWhileBusy(&LINFLEXHw->LINSR.R, MASK_LINSR_LINS, MASK_LINSR_LINS_IDLE, TRUE)) {
        status = E_NOT_OK;
    } else {

        //Disable wake-up interrupt
        LINFLEXHw->LINIER.B.WUIE = 0;

        /** Setting WURQ in LINCR2 would send a wakeup character on the bus.DATA0 in BDRL is the wakeup character sent.
         * DATA0 cannot be 0xFF because valid LIN wakeup according to Lin 2.0 spec needs a dominant (logical 0) to recessive (logical 1) transition on the bus.
         */
        //Send wakeup pulse
        /* @req SWS_Lin_00043 */
        /* @req SWS_Lin_00209 */
        LINFLEXHw->BDRL.B.DATA0 = 0; //Dominant for 8 bit times
        LINFLEXHw->LINCR2.B.WURQ = 1;
    }
    return status;
}

/**
 * Checks if the wakeup flag is set in hardware.
 * @param channelCfg
 * @return
 */
boolean LinFlex_Common_IsWakeUpSet(const Lin_ChannelConfigType *channelCfg) {
    volatile struct LINFLEX_tag * LINFLEXHw;
    boolean retval;
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_PTR_W_RV((NULL != channelCfg), FALSE);

    /*lint -e{923,9033} Hardware access */
    LINFLEXHw = LINFLEX(channelCfg->LinChannelId);

    retval = (LINFLEXHw->LINSR.B.WUF == 1uL) ? TRUE : FALSE;

    /* Clear interrupt flag */
    LINFLEXHw->LINSR.B.WUF = 1;

    return retval;
}

/**
 * Reads out the state from the LinFlex unit
 * @param channelCfg
 * @return
 */
Lin_StatusType LinFlex_Common_GetPeripheralStatus(const Lin_ChannelConfigType *channelCfg) {
    volatile struct LINFLEX_tag * LINFLEXHw;
    Lin_StatusType retval;
    uint32 linsr_lins;
    uint32 writeToClear;
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_PTR_W_RV((NULL != channelCfg), LIN_NOT_OK);

    /*lint -e{923,9033} Hardware access */
    LINFLEXHw = LINFLEX(channelCfg->LinChannelId);

    linsr_lins = LINFLEXHw->LINSR.B.LINS;

    /* LIN_NOT_OK
        Development or production error occurred */
    retval = LIN_NOT_OK;

    if (LINS_IDLE == linsr_lins) {
        /* LIN_OPERATIONAL
               Normal operation; the related LIN channel is ready to transmit next header.
               No data from previous frame available (e.g. after initialization) */
        retval = LIN_OPERATIONAL;
    } else if (LINS_SLEEP == linsr_lins) {
        /* LIN_CH_SLEEP
               Sleep state operation; in this state wake-up detection from slave nodes is enabled. */
        retval = LIN_CH_SLEEP;
    } else if ((LINFLEXHw->LINSR.B.RBSY == 1uL) && (LINS_GENERAL_BUSY <= linsr_lins)) {
        retval = LIN_RX_BUSY;
        /* LIN_RX_BUSY
               Ongoing reception: at least one response byte has been received, but the checksum byte has not been received. */
    } else if (LINS_GENERAL_BUSY <= linsr_lins) {
        /* LIN_TX_BUSY
               Ongoing transmission (Header or Response). */
        retval = LIN_TX_BUSY;
    } else {
        ;
    }

    if (LINFLEXHw->LINSR.B.DRF == 1uL) {
        /* LIN_RX_OK
                Reception of correct response. */
        retval = LIN_RX_OK;
    } else if (LINFLEXHw->LINSR.B.DTF == 1uL) {
        /* LIN_TX_OK
                Successful transmission. */
        retval = LIN_TX_OK;
    } else if ((LINFLEXHw->LINESR.B.SFEF > 0uL) || (LINFLEXHw->LINESR.B.BDEF > 0uL) || (LINFLEXHw->LINESR.B.IDPEF > 0uL)) { /*lint !e9007 No side effects */
        /* LIN_TX_HEADER_ERROR
               Erroneous header transmission such as: - Mismatch between sent and read back data */
        retval = LIN_TX_HEADER_ERROR;
    } else if (LINFLEXHw->LINESR.B.BEF == 1uL) {
        /* LIN_TX_ERROR
                Erroneous response transmission such as: - Mismatch between sent and read back data - Physical bus error */
        retval = LIN_TX_ERROR;
    } else if (LINFLEXHw->LINESR.B.FEF == 1uL) {
        /* LIN_RX_ERROR
               Erroneous response reception such as: - Framing error - Overrun error - Checksum error or - Short response */
        retval = LIN_RX_ERROR;
    } else if (LINFLEXHw->LINESR.B.OCF == 1uL) {
        /* LIN_RX_NO_RESPONSE
               No response byte has been received so far. */
        retval = LIN_RX_ERROR;
    } else {
        ;
    }


    /* Clear the two status registers */
    writeToClear = LINFLEXHw->LINSR.R;
    LINFLEXHw->LINSR.R = writeToClear;

    writeToClear = LINFLEXHw->LINESR.R;
    LINFLEXHw->LINESR.R = writeToClear;

    return retval;
}

/**
 * Used to copy Lin data from peripheral to buffer
 * @param buf
 * @param LINFLEXHw
 * @return
 */
Std_ReturnType LinFlex_Common_WriteHwRegToDataBuf(uint8 *buf, const volatile struct LINFLEX_tag * LINFLEXHw)
{
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_PTR_W_RV((NULL != buf)      , E_NOT_OK);
    VALIDATE_PTR_W_RV((NULL != LINFLEXHw), E_NOT_OK);
    /*lint -restore */

    for(uint8 i = 0; i < NBR_DATA_BYTES; i++)
    {
        /* convenient with freescale reg file */
        /* @req SWS_Lin_00096 */
        switch(i) /*lint --e{744,9014} i is bounded by the surrounding for */
        {
        case 0:
             buf[0] = (uint8)LINFLEXHw->BDRL.B.DATA0;
            break;
        case 1:
             buf[1] = (uint8)LINFLEXHw->BDRL.B.DATA1;
            break;
        case 2:
             buf[2] = (uint8)LINFLEXHw->BDRL.B.DATA2;
            break;
        case 3:
             buf[3] = (uint8)LINFLEXHw->BDRL.B.DATA3;
            break;
        case 4:
             buf[4] = (uint8)LINFLEXHw->BDRM.B.DATA4;
            break;
        case 5:
             buf[5] = (uint8)LINFLEXHw->BDRM.B.DATA5;
            break;
        case 6:
             buf[6] = (uint8)LINFLEXHw->BDRM.B.DATA6;
            break;
        case 7:
             buf[7] = (uint8)LINFLEXHw->BDRM.B.DATA7;
            break;
        default:
            break;
        }
    }

    return E_OK;
}

/**
 * Write data from buffer to hardware register
 * @param length
 * @param buf
 * @param LINFLEXHw
 * @return
 */
Std_ReturnType LinFlex_Common_WriteDataBufToHwReg(uint8 length, const uint8 *buf, volatile struct LINFLEX_tag * LINFLEXHw) {
    Std_ReturnType retval = E_OK;
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_PTR_W_RV((NULL != buf)      , E_NOT_OK);
    VALIDATE_PTR_W_RV((NULL != LINFLEXHw), E_NOT_OK);
    /*lint -restore */

    /*lint -e{904} ARGUMENT_CHECK */
    if (NBR_DATA_BYTES < length) {
        return E_NOT_OK;
    }

    for(uint8 i = 0; i < length;i++)
    {
        switch(i)
        {
        case 0:
            LINFLEXHw->BDRL.B.DATA0 = buf[0]; /*lint !e9031 Both are unsigned 8 bit. */
            break;
        case 1:
            LINFLEXHw->BDRL.B.DATA1 = buf[1]; /*lint !e9031 Both are unsigned 8 bit. */
            break;
        case 2:
            LINFLEXHw->BDRL.B.DATA2 = buf[2]; /*lint !e9031 Both are unsigned 8 bit. */
            break;
        case 3:
            LINFLEXHw->BDRL.B.DATA3 = buf[3]; /*lint !e9031 Both are unsigned 8 bit. */
            break;
        case 4:
            LINFLEXHw->BDRM.B.DATA4 = buf[4]; /*lint !e9031 Both are unsigned 8 bit. */
            break;
        case 5:
            LINFLEXHw->BDRM.B.DATA5 = buf[5]; /*lint !e9031 Both are unsigned 8 bit. */
            break;
        case 6:
            LINFLEXHw->BDRM.B.DATA6 = buf[6]; /*lint !e9031 Both are unsigned 8 bit. */
            break;
        case 7:
            LINFLEXHw->BDRM.B.DATA7 = buf[7]; /*lint !e9031 Both are unsigned 8 bit. */
            break;
        default:
            retval = E_NOT_OK;
            break;
        }
    }

    return retval;
}

/**
 * This function is used instead of "while". It returns when the condition is cleared or
 * when n reach MAX_WAIT_CYCLES.
 * @param regBaseAddr
 * @param mask
 * @param compMask
 * @param retCondition
 * @return
 */
#if defined(CFG_MPC5606S)
static Std_ReturnType waitWhileBusy(volatile const uint16 *regBaseAddr, uint32 mask, uint32 compMask, boolean retCondition) {
#else
static Std_ReturnType waitWhileBusy(volatile const uint32 *regBaseAddr, uint32 mask, uint32 compMask, boolean retCondition) {
#endif
    Std_ReturnType retval = E_NOT_OK;
    boolean condition;
    uint32 n;
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE_PTR_W_RV((NULL != regBaseAddr)      , E_NOT_OK);

    for (n = 0; n < MAX_WAIT_CYCLES ; n++) {
        condition = ((*regBaseAddr & mask) == compMask) ? TRUE : FALSE;

        //Shall remain in the loop while the condition is false.
        if(retCondition == condition) {
            retval = E_OK;
            break;
        }
    }
    return retval;
}
