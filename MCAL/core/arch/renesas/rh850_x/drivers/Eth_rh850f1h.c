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

/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.0.3 */
/** @tagSettings DEFAULT_ARCHITECTURE=RH850F1H */

#include "Eth.h"
#include "Eth_Internal.h"
#include "rh850.h"
#include "timer.h"
#include "irq_types.h"
#include <string.h>
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
#include "isr.h"
#endif
#include "Os.h"
#include "SchM_Eth.h"

#include "EthIf_Cbk.h"
#if (ETH_NOF_CONFIG_CTRL > 1)
#error "Eth: The number of configured Eth controllers exceeds to number of controller supported by RH850F1H"
#endif

#if ( ETH_DEV_ERROR_DETECT == STD_ON )
#if defined(USE_DET)
#include "Det.h"
#else
#error "Eth: Det must be used when dev error detect is enabled"
#endif
#define DET_REPORT_ERROR(_api,_err) (void)Det_ReportError(ETH_MODULE_ID,0,(_api),(_err))
#else
#define DET_REPORT_ERROR(_api,_err)
#endif

#define ETH_ISR_PRIORITY 5
/* Defines for sizes in ethernet header */
#define ETH_MAC_ADDR_SIZE               6u
#define ETH_ETHERNETTYPE_SIZE           2u
/* Start indexes for content of ethernet header */
#define ETH_MAC_DST_ADDR_START_INDEX    0u
#define ETH_MAC_SRC_ADDR_START_INDEX    ETH_MAC_ADDR_SIZE
#define ETH_ETHERNETTYPE_START_INDEX    (2*ETH_MAC_ADDR_SIZE)
/* Size of ethernet header */
#define ETH_HEADER_SIZE                 ((2*ETH_MAC_ADDR_SIZE) + ETH_ETHERNETTYPE_SIZE)

#define GET_ETNB0_HW_PTR()    ((volatile struct st_etnb0   *)0xFFD6E000UL)

/* AVB-DMAC operation modes */
#define ETNB_CSR_OPS_RESET      0x1UL
#define ETNB_CSR_OPS_CONFIG     (1UL<<1UL)
#define ETNB_CSR_OPS_OPERATION  (1UL<<2UL)
#define ETNB_CSR_OPS_STANDBY    (1UL<<3UL)

/* Defines for descriptor interrupts used */
#define ETH_RX_INTRPT_SRC       1UL
#define ETH_TX_INTRPT_SRC       2UL
#define ETH_RX_INTRPT_BIT       (1UL<<ETH_RX_INTRPT_SRC)
#define ETH_TX_INTRPT_BIT       (1UL<<ETH_TX_INTRPT_SRC)

/* MII Management Frame */
#define MII_PRE_DATA        0xFFFFFFFFUL
#define MII_PRE_LEN         32u
#define MII_ST_DATA         1UL
#define MII_ST_LEN          2u
#define MII_OP_WRITE_DATA   1UL
#define MII_OP_READ_DATA    2UL
#define MII_OP_LEN          2u
#define MII_PHYAD_LEN       5u
#define MII_REGAD_LEN       5u
#define MII_TA_DATA         2UL
#define MII_TA_LEN          2u
#define MII_DATA_LEN        16u

/* ETNBn registers */
/* AVB-DMAC Mode Register (ETNBnCCC) */
#define ETNB_CCC_OPC_MASK       0x03UL
#define ETNB_CCC_DTSR_OFFSET    8UL
#define ETNB_CCC_DTSR_BIT      (1UL<<ETNB_CCC_DTSR_OFFSET)
#define ETNB_CCC_CSEL_OFFSET    16UL
#define ETNB_CCC_CSEL_MASK      (0x03UL<<ETNB_CCC_CSEL_OFFSET)
#define ETNB_CCC_BOC_OFFSET     20UL
#define ETNB_CCC_BOC_BIT        (1UL<<ETNB_CCC_BOC_OFFSET)
#define ETNB_CCC_LBME_OFFSET    24UL
#define ETNB_CCC_LBME_BIT       (1UL<<ETNB_CCC_LBME_OFFSET)
#define ETNB_CCC_FCE_OFFSET     25UL
#define ETNB_CCC_FCE_BIT        (1UL<<ETNB_CCC_FCE_OFFSET)

/* AVB-DMAC Status Register (ETNBnCSR) */
#define ETNB_CSR_OPS_MASK       0x0FUL
#define ETNB_CSR_DTS_OFFSET     8UL
#define ETNB_CSR_DTS_BIT        (1UL<<ETNB_CSR_DTS_OFFSET)
#define ETNB_CSR_TPO0_OFFSET    16UL
#define ETNB_CSR_TPO0_BIT       (1UL<<ETNB_CSR_TPO0_OFFSET)
#define ETNB_CSR_TPO1_OFFSET    17UL
#define ETNB_CSR_TPO1_BIT       (1UL<<ETNB_CSR_TPO1_OFFSET)
#define ETNB_CSR_TPO2_OFFSET    18UL
#define ETNB_CSR_TPO2_BIT       (1UL<<ETNB_CSR_TPO2_OFFSET)
#define ETNB_CSR_TPO3_OFFSET    19UL
#define ETNB_CSR_TPO3_BIT       (1UL<<ETNB_CSR_TPO3_OFFSET)
#define ETNB_CSR_TPO_MASK       (ETNB_CSR_TPO0_BIT | ETNB_CSR_TPO1_BIT | ETNB_CSR_TPO2_BIT | ETNB_CSR_TPO3_BIT)
#define ETNB_CSR_RPO_OFFSET     20UL
#define ETNB_CSR_RPO_BIT        (1UL<<ETNB_CSR_RPO_OFFSET)

/* Receive Configuration Register (ETNBnRCR) */
#define ETNB_RCR_EFFFS_BIT      1UL
#define ETNB_RCR_ENCF_OFFSET    1UL
#define ETNB_RCR_ENCF_BIT       (1UL<<ETNB_RCR_ENCF_OFFSET)
#define ETNB_RCR_ESF_OFFSET     2UL
#define ETNB_RCR_ETS0_OFFSET    4UL
#define ETNB_RCR_ETS0_BIT       (1UL<<ETNB_RCR_ETS0_OFFSET)
#define ETNB_RCR_ETS2_OFFSET    5UL
#define ETNB_RCR_ETS2_BIT       (1UL<<ETNB_RCR_ETS2_OFFSET)
#define ETNB_RCR_RFCL_OFFSET    15UL

/* Transmit Configuration Register (ETNBnTGC) */
#define ETNB_TGC_TSM0_BIT       1UL
#define ETNB_TGC_TSM1_OFFSET    1UL
#define ETNB_TGC_TSM1_BIT       (1UL<<ETNB_TGC_TSM1_OFFSET)
#define ETNB_TGC_TSM2_OFFSET    2UL
#define ETNB_TGC_TSM2_BIT       (1UL<<ETNB_TGC_TSM2_OFFSET)
#define ETNB_TGC_TSM3_OFFSET    3UL
#define ETNB_TGC_TSM3_BIT       (1UL<<ETNB_TGC_TSM3_OFFSET)
#define ETNB_TGC_TQP_OFFSET     4UL
#define ETNB_TGC_TBD0_OFFSET    8UL
#define ETNB_TGC_TBD1_OFFSET    12UL
#define ETNB_TGC_TBD2_OFFSET    16UL
#define ETNB_TGC_TBD3_OFFSET    20UL

/* Transmit Configuration Control Register (ETNBnTCCR) */
#define ETNB_TCCR_TSRQ0_BIT     1UL
#define ETNB_TCCR_TSRQ1_OFFSET  1UL
#define ETNB_TCCR_TSRQ1_BIT     (1UL<<ETNB_TCCR_TSRQ1_OFFSET)
#define ETNB_TCCR_TSRQ2_OFFSET  2UL
#define ETNB_TCCR_TSRQ2_BIT     (1UL<<ETNB_TCCR_TSRQ2_OFFSET)
#define ETNB_TCCR_TSRQ3_OFFSET  3UL
#define ETNB_TCCR_TSRQ3_BIT     (1UL<<ETNB_TCCR_TSRQ3_OFFSET)
#define ETNB_TCCR_TSRQ_MASK     (ETNB_TCCR_TSRQ0_BIT | ETNB_TCCR_TSRQ1_BIT | ETNB_TCCR_TSRQ2_BIT | ETNB_TCCR_TSRQ3_BIT)

/* Error Interrupt Control Register (ETNBnEIC) */
#define ETNB_EIC_MREE_BIT       1UL
#define ETNB_EIC_MTEE_OFFSET    1UL
#define ETNB_EIC_MTEE_BIT       (1UL<<ETNB_EIC_MTEE_OFFSET)
#define ETNB_EIC_QEE_OFFSET     2UL
#define ETNB_EIC_QEE_BIT        (1UL<<ETNB_EIC_QEE_OFFSET)
#define ETNB_EIC_SEE_OFFSET     3UL
#define ETNB_EIC_SEE_BIT        (1UL<<ETNB_EIC_SEE_OFFSET)
#define ETNB_EIC_CLLE0_OFFSET   4UL
#define ETNB_EIC_CLLE0_BIT      (1UL<<ETNB_EIC_CLLE0_OFFSET)
#define ETNB_EIC_CLLE1_OFFSET   5UL
#define ETNB_EIC_CLLE1_BIT      (1UL<<ETNB_EIC_CLLE1_OFFSET)
#define ETNB_EIC_CULE0_OFFSET   6UL
#define ETNB_EIC_CULE0_BIT      (1UL<<ETNB_EIC_CULE0_OFFSET)
#define ETNB_EIC_CULE1_OFFSET   7UL
#define ETNB_EIC_CULE1_BIT      (1UL<<ETNB_EIC_CULE1_OFFSET)
#define ETNB_EIC_TFFE_OFFSET    8UL
#define ETNB_EIC_TFFE_BIT       (1UL<<ETNB_EIC_TFFE_OFFSET)
#define ETNB_EIC_MFFE_OFFSET    9UL
#define ETNB_EIC_MFFE_BIT       (1UL<<ETNB_EIC_MFFE_OFFSET)

/* E-MAC Mode Register (ETNBnECMR) */
#define ETNB_ECMR_DM_OFFSET     1UL
#define ETNB_ECMR_DM_BIT        (1UL<<ETNB_ECMR_DM_OFFSET)
#define ETNB_ECMR_TE_OFFSET     5UL
#define ETNB_ECMR_TE_BIT        (1UL<<ETNB_ECMR_TE_OFFSET)
#define ETNB_ECMR_RE_OFFSET     6UL
#define ETNB_ECMR_RE_BIT        (1UL<<ETNB_ECMR_RE_OFFSET)
#define ETNB_ECMR_MPDE_OFFSET   9UL
#define ETNB_ECMR_MPDE_BIT      (1UL<<ETNB_ECMR_MPDE_OFFSET)
#define ETNB_ECMR_TXF_OFFSET    16UL
#define ETNB_ECMR_TXF_BIT       (1UL<<ETNB_ECMR_TXF_OFFSET)
#define ETNB_ECMR_RXF_OFFSET    17UL
#define ETNB_ECMR_RXF_BIT       (1UL<<ETNB_ECMR_RXF_OFFSET)
#define ETNB_ECMR_PFR_OFFSET    18UL
#define ETNB_ECMR_PFR_BIT       (1UL<<ETNB_ECMR_PFR_OFFSET)
#define ETNB_ECMR_ZPF_OFFSET    19UL
#define ETNB_ECMR_ZPF_BIT       (1UL<<ETNB_ECMR_ZPF_OFFSET)
#define ETNB_ECMR_RZPF_OFFSET   20UL
#define ETNB_ECMR_RZPF_BIT      (1UL<<ETNB_ECMR_RZPF_OFFSET)
#define ETNB_ECMR_DPAD_OFFSET   21UL
#define ETNB_ECMR_DPAD_BIT      (1UL<<ETNB_ECMR_DPAD_OFFSET)
#define ETNB_ECMR_RCSC_OFFSET   23UL
#define ETNB_ECMR_RCSC_BIT      (1UL<<ETNB_ECMR_RCSC_OFFSET)
#define ETNB_ECMR_TRCCM_OFFSET  26UL
#define ETNB_ECMR_TRCCM_BIT     (1UL<<ETNB_ECMR_TRCCM_OFFSET)

/* PHY Interface Register (ETNBnPIR) */
#define ETNB_PIR_MDC_BIT        1UL
#define ETNB_PIR_MMD_OFFSET     1UL
#define ETNB_PIR_MMD_BIT        (1UL<<ETNB_PIR_MMD_OFFSET)
#define ETNB_PIR_MDO_OFFSET     2UL
#define ETNB_PIR_MDO_BIT        (1UL<<ETNB_PIR_MDO_OFFSET)
#define ETNB_PIR_MDI_OFFSET     3UL

/* PHY timing limitation */
#define PHY_MIN_PERIOD      600UL
#define PHY_MDO_TO_MDC_HIGH 200UL
#define PHY_MDC_HIGH_TO_MDI 400UL

/* Descriptor types */
/* Frame data */
#define DT_FSTART       5UL
#define DT_FMID         4UL
#define DT_FEND         6UL
#define DT_FSINGLE      7UL
/* Chain control */
#define DT_LINK         8UL
#define DT_LINKFIX      9UL
#define DT_EOS          10UL
/* HW/SW arbitration */
#define DT_FEMPTY       12UL
#define DT_FEMPTY_IS    13UL
#define DT_FEMPTY_IC    14UL
#define DT_FEMPTY_ND    15UL
#define DT_LEMPTY       2UL
#define DT_EEMPTY       3UL

/* ETNB0 queues */
#define ETNB_TX_QUEUE_0         0UL
#define ETNB_RX_QUEUE_0         4UL
#define ETNB_NOF_QUEUES         22UL
#define TX_QUEUE_CDAR           CDAR0
#define RX_QUEUE_UFCD           UFCD0
#define RX_QUEUE_UFCD_OFFSET    0UL

#define ETH_BROADCAST_BYTE 0xffu
/* Max wait cycles for actions to occur in busy wait */
#define ETH_MAX_BUSY_WAIT_CYCLES (uint32)10000

/* Macro for busy waiting for a while */
#define BUSY_WAIT_A_WHILE(_regPtr, _mask, _val, _retPtr)\
    *(_retPtr) = E_NOT_OK;\
    for( uint32 i = 0; i < ETH_MAX_BUSY_WAIT_CYCLES; i++) {\
        if( (*(_regPtr) & (_mask)) == (_val) ) {\
            *(_retPtr) = E_OK;\
            break;\
        }\
    }\


/* ISR */
ISR(Eth_TxRxIrqHdlr_0);

/* Local typedefs */
typedef enum {
   AVB_DMAC_MODE_RESET = 0,
   AVB_DMAC_MODE_CONFIG,
   AVB_DMAC_MODE_OPERATION,
   AVB_DMAC_MODE_STANDBY,
   AVB_DMAC_NOF_MODES
}AVB_DMAC_CCC_ModeType;

typedef struct Descriptor_s {
    union {
        struct {
            uint32 DS:12;
            uint32 CC:12;
            uint32 DIE:4;
            uint32 DT:4;
        }B;
    }DESC;/*lint !e9018 Allow use of union based types */
    union {
        uint8* DATAPTR;
        struct Descriptor_s* DESCPTR;
    }PTR;/*lint !e9018 Allow use of union based types */
}EthDescriptorType;

typedef struct {
    boolean locked;
    uint8* dataPtr;
}EthBufferStatusType;

typedef enum {
    ETH_TX_DESC_IDLE = 0,
    ETH_TX_DESC_TX_REQUESTED_NO_CONFIRM,
    ETH_TX_DESC_TX_REQUESTED_CONFIRM
}EthTxRequestType;

typedef struct {
    EthTxRequestType TxState;
    uint8 TxBufferIdx;
}EthTxDescriptorStatusType;

#if defined(CFG_ETH_ARC_STATISTICS)
static Eth_Arc_StatisticsType EthStatistics;
#endif

/* Buffer for rx/tx data */
static uint8 EthRxDataBuffer[ETH_TOTAL_RX_BUFFER_SIZE]__attribute__ ((aligned(8))) __attribute__ ((section (".ethData")));
static uint8 EthTxDataBuffer[ETH_TOTAL_TX_BUFFER_SIZE]__attribute__ ((aligned(8))) __attribute__ ((section (".ethData")));

/* Rx/Tx descriptors */
static EthDescriptorType EthRxDescriptors[ETH_NUM_RX_BUFFERS + 1]__attribute__ ((aligned(8))) __attribute__ ((section (".ethData")));
static EthDescriptorType EthTxDescriptors[ETH_NUM_TX_BUFFERS + 1]__attribute__ ((aligned(8))) __attribute__ ((section (".ethData")));

/* For holding the state of a tx buffer */
static EthBufferStatusType EthTxBufferStatus[ETH_NUM_TX_BUFFERS];

/* For link to tx buffer and state of tx descriptor */
static EthTxDescriptorStatusType EthTxDescriptorStatus[ETH_NUM_TX_BUFFERS];

/* Index of the next descriptor to use for tx */
static uint8 EthNextTxDescIdx = 0;

/* Index of the next descriptor to handle tx confirmation (which descriptor to start from on intrpt or call to Eth_TxConfirmation) */
static uint8 NextTxConfirmDescIndex = 0;

/* Index of the next descriptor to handle rx indication (which descriptor to start from on intrpt or call to Eth_Receive) */
static uint8 NextRxDescIndex = 0;

/* For holding buffer sizes from configuration */
static uint16 EthRxBufSize[ETH_NOF_CONFIG_CTRL];

/**
 * Changes mode of AVDB-DMAC
 * @param requestMode
 * @return E_OK: Mode change OK, E_NOT_OK: mode change failed
 */
static Std_ReturnType AVB_DMAC_EnterMode(AVB_DMAC_CCC_ModeType requestMode)
{
    const uint32 CCC_Mode_To_CSR_Mode[AVB_DMAC_NOF_MODES] = {
            [AVB_DMAC_MODE_RESET] = ETNB_CSR_OPS_RESET,
            [AVB_DMAC_MODE_CONFIG] = ETNB_CSR_OPS_CONFIG,
            [AVB_DMAC_MODE_OPERATION] = ETNB_CSR_OPS_OPERATION,
            [AVB_DMAC_MODE_STANDBY] = ETNB_CSR_OPS_STANDBY
    };
    volatile struct st_etnb0 *hwPtr = GET_ETNB0_HW_PTR();/*lint !e923 Intentional cast from integer literal HW register address to pointer */
    uint32 temp;
    Std_ReturnType ret = E_NOT_OK;
    uint32 currMode = (uint32)(hwPtr->CSR & ETNB_CSR_OPS_MASK);
    if(currMode != CCC_Mode_To_CSR_Mode[requestMode]) {
        if( (ETNB_CSR_OPS_OPERATION == currMode) && (AVB_DMAC_MODE_CONFIG == requestMode) ) {
            /* Transition from operation to configuration */
            boolean done = FALSE;
            for(uint32 i = 0; (i < ETH_MAX_BUSY_WAIT_CYCLES) && !done; i++) {
                /* Figure 22.7 in reference manual */
                /* Set the operating mode */
                temp = (uint32)hwPtr->CCC.UINT32;
                hwPtr->CCC.UINT32 = (temp & ~ETNB_CCC_OPC_MASK) | (uint32)requestMode;
                /* Check the operation mode */
                switch(hwPtr->CSR & ETNB_CSR_OPS_MASK) {
                    case ETNB_CSR_OPS_OPERATION:
                        break;
                    case ETNB_CSR_OPS_CONFIG:
                        ret = E_OK;
                        done = TRUE;
                        break;
                    default:
                        done = TRUE;
                }
            }
        } else {
            /* Figure 22.6 in reference manual */
            if( (ETNB_CSR_OPS_OPERATION == currMode) && (AVB_DMAC_MODE_RESET == requestMode) ) {
                hwPtr->CCC.UINT32 |= ETNB_CCC_DTSR_BIT;
                BUSY_WAIT_A_WHILE(&hwPtr->CSR, ETNB_CSR_DTS_BIT, ETNB_CSR_DTS_BIT, &ret);
                if( E_OK != ret ) {
                    /* Failed to suspend data transmission*/
                    return E_NOT_OK;
                }
            }
            /* Set the operating mode */
            temp = (uint32)hwPtr->CCC.UINT32;
            hwPtr->CCC.UINT32 = (temp & ~ETNB_CCC_OPC_MASK) | (uint32)requestMode;
            /* Check the operation mode */
            if( (uint32)(hwPtr->CSR & ETNB_CSR_OPS_MASK) == CCC_Mode_To_CSR_Mode[requestMode] ) {
                ret = E_OK;
            } else {
                ret = E_NOT_OK;
            }
        }
    } else {
        ret = E_OK;
    }
    return ret;
}

/**
 * Activates/deactivates the Eth controller
 * @param active
 * @return E_OK: Action OK
 */
static Std_ReturnType setCommunicationMode(Eth_ModeType CtrlMode)
{
    Std_ReturnType ret = E_OK;
    volatile struct st_etnb0 *hwPtr = GET_ETNB0_HW_PTR();/*lint !e923 Intentional cast from integer literal HW register address to pointer */
    switch (CtrlMode) {
        case ETH_MODE_ACTIVE:
            /* Enable reception and transmission */
            hwPtr->ECMR |= (ETNB_ECMR_TE_BIT | ETNB_ECMR_RE_BIT);
            break;
        case ETH_MODE_DOWN:
            if(0 != (hwPtr->ECMR & (ETNB_ECMR_TE_BIT | ETNB_ECMR_RE_BIT))) {
                boolean commEnabled = (0UL != (hwPtr->ECMR & (ETNB_ECMR_TE_BIT | ETNB_ECMR_RE_BIT))) ? TRUE: FALSE;
                /* Disable reception */
                hwPtr->ECMR &= ~ETNB_ECMR_RE_BIT;
                ret = E_NOT_OK;
                /* Wait until transmission and reception processes are completed */
                BUSY_WAIT_A_WHILE(&hwPtr->TCCR.UINT32, ETNB_TCCR_TSRQ_MASK, 0UL, &ret);
                if( E_OK == ret ) {
                    BUSY_WAIT_A_WHILE(&hwPtr->CSR, (ETNB_CSR_TPO_MASK | ETNB_CSR_RPO_BIT), 0UL, &ret);
                    if( E_OK == ret ) {
                        /* Disable transmission */
                        hwPtr->ECMR &= ~ETNB_ECMR_TE_BIT;
                    }
                }
                if((E_OK != ret) && commEnabled) {
                    /* Failed to disable and rx and tx was previously enabled */
                    hwPtr->ECMR |= (ETNB_ECMR_TE_BIT | ETNB_ECMR_RE_BIT);
                }
            }
            break;
        default:
            ret = E_NOT_OK;
            break;
    }
    return ret;
}

/**
 * Initializes buffer
 * @param CfgPtr
 */
static void initBuffers(const Eth_ControllerConfigType *CfgPtr, uint8 CtrlIdx)
{
    uint32 nextDataIndex = 0;
    /* Set up the buffer runtime variables */
    EthNextTxDescIdx = 0;
    NextTxConfirmDescIndex = 0;
    NextRxDescIndex = 0;
    memset(EthTxDescriptorStatus, 0, sizeof(EthTxDescriptorStatus));
    for(uint8 txBufIdx = 0; txBufIdx < CfgPtr->EthTxBufTotal; txBufIdx++) {
        EthTxBufferStatus[txBufIdx].locked = FALSE;
        EthTxBufferStatus[txBufIdx].dataPtr = &EthTxDataBuffer[nextDataIndex];
        nextDataIndex = nextDataIndex + (uint32)(CfgPtr->EthCtrlTxBufLenByte + (CfgPtr->EthCtrlTxBufLenByte % 8UL));
    }
    EthRxBufSize[CtrlIdx] = CfgPtr->EthCtrlRxBufLenByte;
}

/**
 * Resets rx and tx buffer
 * @return E_OK: Action OK
 */
static Std_ReturnType resetBuffers(const Eth_ControllerConfigType *CtrlCfgPtr, uint8 CtrlIdx) {
    volatile struct st_etnb0 *hwPtr = GET_ETNB0_HW_PTR();/*lint !e923 Intentional cast from integer literal HW register address to pointer */
    for(uint8 txBufIdx = 0; txBufIdx < CtrlCfgPtr->EthTxBufTotal; txBufIdx++) {
        EthTxDescriptors[txBufIdx].DESC.B.DT = DT_FEMPTY;
    }
    for(uint8 rxBufIdx = 0; rxBufIdx < CtrlCfgPtr->EthRxBufTotal; rxBufIdx++) {
        EthRxDescriptors[rxBufIdx].DESC.B.DT = DT_FEMPTY;
    }

    memset(EthRxDataBuffer, 0, sizeof(EthRxDataBuffer));
    memset(EthTxDataBuffer, 0, sizeof(EthRxDataBuffer));
    /* Initialize buffer runtime data */
    initBuffers(CtrlCfgPtr, CtrlIdx);
    /* Reload desc addr. */
    hwPtr->DLR = 0x3FFFFFUL;
    return E_OK;
}

/**
 * Configures descriptors
 * @param CfgPtr
 * @param hwPtr
 */
static void configureDescriptors(const Eth_ControllerConfigType *CfgPtr, volatile struct st_etnb0 *hwPtr)
{
    static EthDescriptorType EthLinkDescriptors[ETNB_NOF_QUEUES]__attribute__ ((aligned(8))) __attribute__ ((section (".ethData")));
    memset(EthLinkDescriptors, 0, sizeof(EthLinkDescriptors));
    /* Set descriptor base address */
    /*lint -e{9033,923} Need to set address */
    hwPtr->DBAT = (uint32)&EthLinkDescriptors[0];

    /* Setup the link descriptors */
    for(uint32 q = ETNB_TX_QUEUE_0; q < ETNB_NOF_QUEUES; q++) {
        if( ETNB_TX_QUEUE_0 == q ) {
            EthLinkDescriptors[q].DESC.B.DT = DT_LINKFIX;
            EthLinkDescriptors[q].DESC.B.DIE = 0UL;
            EthLinkDescriptors[q].DESC.B.DS = 0UL;
            EthLinkDescriptors[q].PTR.DESCPTR = &EthTxDescriptors[0];
        } else if( ETNB_RX_QUEUE_0 == q ) {
            EthLinkDescriptors[q].DESC.B.DT = DT_LINKFIX;
            EthLinkDescriptors[q].DESC.B.DIE = 0UL;
            EthLinkDescriptors[q].DESC.B.DS = 0UL;
            EthLinkDescriptors[q].PTR.DESCPTR = &EthRxDescriptors[0];
        } else {
            /* Don't use the other ones */
            EthLinkDescriptors[q].DESC.B.DT = DT_EOS;
            EthLinkDescriptors[q].DESC.B.DIE = 0;
            EthLinkDescriptors[q].PTR.DESCPTR = NULL;
        }
    }

    /* Setup descriptor chains */
    uint32 nextDataIndex = 0;
    for(uint8 rxBufIdx = 0; rxBufIdx <= CfgPtr->EthRxBufTotal; rxBufIdx++) {
        if(CfgPtr->EthRxBufTotal == rxBufIdx) {
            /* Last one should be link */
            EthRxDescriptors[rxBufIdx].DESC.B.CC = 0;
            EthRxDescriptors[rxBufIdx].DESC.B.DIE = 0;
            EthRxDescriptors[rxBufIdx].DESC.B.DS = 0;
            EthRxDescriptors[rxBufIdx].DESC.B.DT = DT_LINKFIX;
            EthRxDescriptors[rxBufIdx].PTR.DESCPTR = &EthRxDescriptors[0];
        } else {
            EthRxDescriptors[rxBufIdx].DESC.B.CC = 0;
            EthRxDescriptors[rxBufIdx].DESC.B.DIE = (CfgPtr->EthCtrlEnableRxInterrupt) ? ETH_RX_INTRPT_SRC:0UL;
            EthRxDescriptors[rxBufIdx].DESC.B.DS = (uint32)CfgPtr->EthCtrlRxBufLenByte;
            EthRxDescriptors[rxBufIdx].DESC.B.DT = DT_FEMPTY;
            EthRxDescriptors[rxBufIdx].PTR.DATAPTR = &EthRxDataBuffer[nextDataIndex];
            nextDataIndex = nextDataIndex + (uint32)(CfgPtr->EthCtrlRxBufLenByte + (CfgPtr->EthCtrlRxBufLenByte % 8UL));
        }
    }

    for(uint8 txBufIdx = 0; txBufIdx <= CfgPtr->EthTxBufTotal; txBufIdx++) {
        if(CfgPtr->EthTxBufTotal == txBufIdx) {
            /* Last one should be link */
            EthTxDescriptors[txBufIdx].DESC.B.CC = 0;
            EthTxDescriptors[txBufIdx].DESC.B.DIE = 0;
            EthTxDescriptors[txBufIdx].DESC.B.DS = 0;
            EthTxDescriptors[txBufIdx].DESC.B.DT = DT_LINKFIX;
            EthTxDescriptors[txBufIdx].PTR.DESCPTR = &EthTxDescriptors[0];
        } else {
            EthTxDescriptors[txBufIdx].DESC.B.CC = 0;
            EthTxDescriptors[txBufIdx].DESC.B.DIE = (CfgPtr->EthCtrlEnableTxInterrupt) ? ETH_TX_INTRPT_SRC:0UL;
            EthTxDescriptors[txBufIdx].DESC.B.DT = DT_FEMPTY;
        }
    }
}

/**
 * ISR for ETNB0 data interrupt
 */
/* !req 4.1.3/SWS_Eth_00109 *//* !req 4.0.3/ETH109 */
/* !req 4.1.3/SWS_Eth_00114 *//* !req 4.0.3/ETH114 */
ISR(Eth_TxRxIrqHdlr_0)
{
    /* !req 4.1.3/SWS_Eth_00111 *//* !req 4.0.3/ETH111 */
    /* !req 4.1.3/SWS_Eth_00116 *//* !req 4.0.3/ETH116 */
    volatile struct st_etnb0 *hwPtr = GET_ETNB0_HW_PTR();/*lint !e923 Intentional cast from integer literal HW register address to pointer */
    if(0 != (hwPtr->DIS & ETH_RX_INTRPT_BIT)) {
        /* @req 4.1.3/SWS_Eth_00110 *//* @req 4.0.3/ETH110 */
        Eth_Hw_Receive(0);
#if defined(CFG_ETH_ARC_STATISTICS)
        EthStatistics.RxInterptCnt++;
#endif
        hwPtr->DIS &= ~ETH_RX_INTRPT_BIT;
    }
    hwPtr->RIS0 = 0;
    if(0 != (hwPtr->DIS & ETH_TX_INTRPT_BIT)) {
        /* @req 4.1.3/SWS_Eth_00115 *//* @req 4.0.3/ETH115 */
        Eth_Hw_TxConfirmation(0);
#if defined(CFG_ETH_ARC_STATISTICS)
        EthStatistics.TxInterptCnt++;
#endif
        hwPtr->DIS &= ~ETH_TX_INTRPT_BIT;
    }
    hwPtr->TIS = 0;

}

/**
 * Configures the Eth controller
 * @param CfgPtr
 * @return E_OK: Configuration successful, E_NOT_OK: Configuration failed
 */
static Std_ReturnType configureController(const Eth_ControllerConfigType *CfgPtr)
{
    /* Init EMAC */
    Std_ReturnType ret = E_OK;
    volatile struct st_etnb0 *hwPtr = GET_ETNB0_HW_PTR();/*lint !e923 Intentional cast from integer literal HW register address to pointer */
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
    if( (TRUE == CfgPtr->EthCtrlEnableRxInterrupt) || (TRUE == CfgPtr->EthCtrlEnableTxInterrupt) ) {
        ISR_INSTALL_ISR2("Eth", Eth_TxRxIrqHdlr_0, IRQ_INTETNB0DATA, ETH_ISR_PRIORITY, 0);
    }
#endif
    /* Disable flow control, loopback, gPTP etc. */
    uint32 ccc = (uint32)hwPtr->CCC.UINT32;
    ccc &= ETNB_CCC_OPC_MASK;
#if defined(CFG_ETH_LOOPBACK)
    ccc |= ETNB_CCC_LBME_BIT;
#endif
    hwPtr->CCC.UINT32 = ccc;

    /* Disable all error interrupts */
    hwPtr->EIC = 0;

    /* Rx config, disable timestamps, network control and stream filtering and error frames */
    hwPtr->RCR = (0x1800UL<<ETNB_RCR_RFCL_OFFSET);

    /* TX config, set all fifo sizes to 2(as mentioned in manual) and set transmit queue priority to Non-AVB mode */
    hwPtr->TGC = (2UL<<ETNB_TGC_TBD0_OFFSET) | (2UL<<ETNB_TGC_TBD1_OFFSET) | (2UL<<ETNB_TGC_TBD2_OFFSET) | (2UL<<ETNB_TGC_TBD3_OFFSET);

    /* Configure descriptors */
    configureDescriptors(CfgPtr, hwPtr);

    /* Configure MAC address */
    hwPtr->MAHR = ((uint32)CfgPtr->EthCtrlPhyAddress[0] << 24u) + ((uint32)CfgPtr->EthCtrlPhyAddress[1] << 16u) + ((uint32)CfgPtr->EthCtrlPhyAddress[2] << 8u) + (uint32)CfgPtr->EthCtrlPhyAddress[3];/*lint !e9033 */
    hwPtr->MALR = (((uint32)CfgPtr->EthCtrlPhyAddress[4]) << 8u) | (uint32)CfgPtr->EthCtrlPhyAddress[5];/*lint !e9033 */

    /* Set speed */
    hwPtr->GECMR = 0;/* 100mpbs (manual is wrong here) */

    /* Setup max rx frame length  */
    hwPtr->RFLR = CfgPtr->EthCtrlRxBufLenByte;

    /* Disable EMAC interrupts */
    hwPtr->ECSIPR = 0UL;

    /* Clear all counters */
    hwPtr->TROCR = 0;
    hwPtr->CDCR = 0;
    hwPtr->LCCR = 0;
    hwPtr->CEFCR = 0;
    hwPtr->FRECR = 0;
    hwPtr->TSFRCR = 0;
    hwPtr->TLFRCR = 0;
    hwPtr->RFCR = 0;
    hwPtr->MAFCR = 0;

    /* Disable unread frame warning/stop level */
    hwPtr->UFCW = 0UL;
    hwPtr->UFCS = 0UL;

    /* Set MAC mode, enable full-duplex mode, disable rx and tx */
    hwPtr->ECMR = ETNB_ECMR_DM_BIT;

    /* set RIC0 interrupt, we only use receive queue 0 so enable interrupt on this if configured */
    hwPtr->RIC0 = (TRUE == CfgPtr->EthCtrlEnableRxInterrupt) ? 1UL : 0UL;

    /* set RIC1 interrupt, disable FIFO warning interrupt */
    hwPtr->RIC1 = 0UL;

    /* set RIC2 interrupt, disable all FIFO/Receive queue full interrupts */
    hwPtr->RIC2 = 0UL;

    /* set TIC interrupt, disable all FIFO interrupts */
    hwPtr->TIC = 0UL;

    /* set GIC interrupt, disable gPTP interrupt */
    hwPtr->GIC = 0UL;

    /* Clear pending interrupts */
    hwPtr->RIS0 = 0UL;
    hwPtr->RIS1 = 0UL;
    hwPtr->RIS2 = 0UL;
    hwPtr->TIS = 0UL;

    /* Use Mii */
    hwPtr->IFCTL = 0;

    /* All padding 0 */
    hwPtr->RPC = 0;

    /* Setup the descriptor interrupts */
    hwPtr->DIC = 0;
    if(TRUE == CfgPtr->EthCtrlEnableRxInterrupt) {
        hwPtr->DIC |= ETH_RX_INTRPT_BIT;
    }
    if(TRUE == CfgPtr->EthCtrlEnableTxInterrupt) {
        hwPtr->DIC |= ETH_TX_INTRPT_BIT;
    }
    /* Reload desc base address */
    hwPtr->DLR = 0x3FFFFFUL;

    return ret;
}


/**
 * Busy-wait function
 * @param tmo
 */
static inline void waitNanoSec(uint32 tmo)
{
    /* IMPROVEMENT: Fix this function when timer is available */
#if 0
    Timer_uDelay(((tmo + 999UL)/1000UL));
#else
    volatile uint32 dummy = 0;
    for( uint32 i = 0; (i < tmo); i++ ) {
        dummy++;
    }
    (void)dummy;
#endif
}

/**
 * Writes a bit sequence through MII
 * @param data
 * @param dataLen
 */
static void miiWrite(uint32 data, uint8 dataLen)
{
    uint32 bitVal = 0;
    volatile struct st_etnb0 *hwPtr = GET_ETNB0_HW_PTR();/*lint !e923 Intentional cast from integer literal HW register address to pointer */
    for(uint8 i = 0; i < dataLen; i++) {
        bitVal = ((data>>(dataLen - (i + 1UL))) & 1UL);
        hwPtr->PIR = (ETNB_PIR_MMD_BIT | ((uint32)bitVal<<ETNB_PIR_MDO_OFFSET));
        waitNanoSec(PHY_MIN_PERIOD/3UL);
        hwPtr->PIR = (ETNB_PIR_MMD_BIT | (bitVal<<ETNB_PIR_MDO_OFFSET) | ETNB_PIR_MDC_BIT);
        waitNanoSec(PHY_MIN_PERIOD/3UL);
        hwPtr->PIR = (ETNB_PIR_MMD_BIT | (bitVal<<ETNB_PIR_MDO_OFFSET));
        waitNanoSec(PHY_MIN_PERIOD/3UL);
    }
}

/**
 * Reads bit sequence through MII
 * @param dataLen
 * @param data
 */
static void miiRead(uint8 dataLen, uint16 *data)
{
    uint16 readData = 0;
    volatile struct st_etnb0 *hwPtr = GET_ETNB0_HW_PTR();/*lint !e923 Intentional cast from integer literal HW register address to pointer */
    for(uint8 i = 0; i < dataLen; i++) {
        readData <<= 1u;
        hwPtr->PIR = ETNB_PIR_MDC_BIT;
        waitNanoSec(PHY_MDC_HIGH_TO_MDI);
        readData |= (uint16)((hwPtr->PIR>>ETNB_PIR_MDI_OFFSET) & 0x1u);
        hwPtr->PIR = 0;
        waitNanoSec((PHY_MIN_PERIOD - PHY_MDC_HIGH_TO_MDI));
    }
    *data = readData;
}

/**
 * Performs independent bus release
 */
static void miiIndependantBusRelease(void)
{
    volatile struct st_etnb0 *hwPtr = GET_ETNB0_HW_PTR();/*lint !e923 Intentional cast from integer literal HW register address to pointer */
    hwPtr->PIR = 0;
    waitNanoSec(PHY_MIN_PERIOD);
}

/**
 * Performs bus release
 */
static void miiBusRelease(void)
{
    volatile struct st_etnb0 *hwPtr = GET_ETNB0_HW_PTR();/*lint !e923 Intentional cast from integer literal HW register address to pointer */
    hwPtr->PIR = 0;
    waitNanoSec(PHY_MIN_PERIOD/3UL);
    hwPtr->PIR = ETNB_PIR_MDC_BIT;
    waitNanoSec(PHY_MIN_PERIOD/3UL);
    hwPtr->PIR = 0;
    waitNanoSec(PHY_MIN_PERIOD/3UL);
}

/**
 * Inserts ethernet header in a data buffer
 * @param CtrlCfgPtr
 * @param PhysAddrPtr
 * @param dataPtr
 */
static void insertEthHeader(const Eth_ControllerConfigType *CtrlCfgPtr, const uint8* PhysAddrPtr, uint8* dataPtr, Eth_FrameType FrameType)
{
    /* Dest MAC */
    memcpy(&dataPtr[ETH_MAC_DST_ADDR_START_INDEX], PhysAddrPtr, ETH_MAC_ADDR_SIZE);
    /* Src MAC */
    memcpy(&dataPtr[ETH_MAC_SRC_ADDR_START_INDEX], CtrlCfgPtr->EthCtrlPhyAddress, ETH_MAC_ADDR_SIZE);
    /* Ethernet type */
    memcpy(&dataPtr[ETH_ETHERNETTYPE_START_INDEX], &FrameType, ETH_ETHERNETTYPE_SIZE);
}

#if 0
/**
 * Enables/disables AVB-DMAC access to URAM
 * @param enabled
 */
static void setURAMAccess(boolean enabled)
{
    volatile struct st_etnb0 *hwPtr = GET_ETNB0_HW_PTR();/*lint !e923 Intentional cast from integer literal HW register address to pointer */
    if(enabled) {
        hwPtr->CCC.UINT32 &= ~ETNB_CCC_DTSR_BIT;
    } else {
        hwPtr->CCC.UINT32 |= ETNB_CCC_DTSR_BIT;
        while(0UL == (hwPtr->CSR & ETNB_CSR_DTS_BIT)){};
    }
}
/**
 * Cancels pending transmissions
 * @param CtrlCfgPtr
 * @return E_OK
 */
static Std_ReturnType deletePendingTxRequests(const Eth_ControllerConfigType *CtrlCfgPtr)
{
    EthDescriptorType *currDescPtr;
    uint8 descStartIndex;
    uint8 descIndex;
    volatile struct st_etnb0 *hwPtr = GET_ETNB0_HW_PTR();/*lint !e923 Intentional cast from integer literal HW register address to pointer */
    setURAMAccess(FALSE);
    /* Get current descriptor */
    currDescPtr = (EthDescriptorType *)hwPtr->TX_QUEUE_CDAR;
    if( (DT_LINK == currDescPtr->DESC.B.DT) || (DT_LINKFIX == currDescPtr->DESC.B.DT) ) {
        descStartIndex = 0;
    } else {
        descStartIndex = ((currDescPtr - &EthTxDescriptors[0])/sizeof(EthDescriptorType)) + 1;
    }
    for(uint8 i = 0; i < CtrlCfgPtr->EthTxBufTotal; i++) {
        descIndex = (descStartIndex + i)%CtrlCfgPtr->EthTxBufTotal;
        if(currDescPtr != &EthTxDescriptors[descIndex] ) {
            EthTxDescriptors[descIndex].DESC.B.DT = DT_EEMPTY;
        }
    }
    setURAMAccess(TRUE);
    return E_OK;
}
#endif

/* APIs */

/**
 * Initializes Ethernet hw module
 * @param CfgPtr
 */
void Eth_Hw_Init(const Eth_ConfigType* CfgPtr)
{
    (void)CfgPtr;/*lint !e920 */
}

/**
 * Initializes an Ethernet controller
 * @param CtrlCfgPtr
 * @return E_OK: Initialization OK, E_NOT_OK: Initialization failed
 */
Std_ReturnType Eth_Hw_ControllerInit(const Eth_ControllerConfigType *CtrlCfgPtr, uint8 CtrlIdx)
{
    /*
     * 1: Disable the controller
     * 2: Clear pending Ethernet interrupts
     * 3: Configure all controller configuration parameters (e.g. interrupts, frame length, frame filter, ...)
     * 4: Configure all transmit / receive resources (e.g. buffer initialization)
     * 5: delete all pending transmit and receive requests
     *
     */
    if( ETNB_0 != CtrlCfgPtr->EthHwUnit ) {
        DET_REPORT_ERROR(ETH_GLOBAL_ID, ETH_E_CONFIG_INVALID);
        return E_NOT_OK;
    }

    /* Enter reset mode */
    if(E_OK != AVB_DMAC_EnterMode(AVB_DMAC_MODE_RESET)) {
        return E_NOT_OK;
    }

    /* Enter config mode */
    if(E_OK != AVB_DMAC_EnterMode(AVB_DMAC_MODE_CONFIG)) {
        return E_NOT_OK;
    }

    /* Disable controller */
    if(E_OK != setCommunicationMode(ETH_MODE_DOWN)) {
        return E_NOT_OK;
    }

    /* Initialize buffer runtime data */
    initBuffers(CtrlCfgPtr, CtrlIdx);

    /* Configure the controller */
    if(E_OK != configureController(CtrlCfgPtr)) {
        return E_NOT_OK;
    }
    /* Enter operation mode */
    if(E_OK != AVB_DMAC_EnterMode(AVB_DMAC_MODE_OPERATION)) {
        return E_NOT_OK;
    }
    return E_OK;
}

/**
 * Writes PHY register through MII
 * @param CtrlCfgPtr
 * @param TrcvIdx
 * @param RegIdx
 * @param RegVal
 * @return E_OK: Write OK, E_NOT_OK: Write failed
 */
Std_ReturnType Eth_Hw_WriteMii(const Eth_ControllerConfigType *CtrlCfgPtr, uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal)
{
    if( ETNB_0 != CtrlCfgPtr->EthHwUnit ) {
        DET_REPORT_ERROR(ETH_GLOBAL_ID, ETH_E_CONFIG_INVALID);
        return E_NOT_OK;
    }
    /* 32 consecutive 1s */
    miiWrite(MII_PRE_DATA, MII_PRE_LEN);
    /* Start of frame */
    miiWrite(MII_ST_DATA, MII_ST_LEN);
    /* Access type: write */
    miiWrite(MII_OP_WRITE_DATA, MII_OP_LEN);
    /* Phy address */
    miiWrite((uint32)TrcvIdx, MII_PHYAD_LEN);
    /* Register address */
    miiWrite((uint32)RegIdx, MII_REGAD_LEN);
    /* Turn around */
    miiWrite(MII_TA_DATA, MII_TA_LEN);
    /* Write data */
    miiWrite((uint32)RegVal, MII_DATA_LEN);
    /* Independant bus release */
    miiIndependantBusRelease();
    /* Done */
    return E_OK;
}

/**
 * Reads PHY register through MII
 * @param CtrlCfgPtr
 * @param TrcvIdx
 * @param RegIdx
 * @param RegVal
 * @return E_OK: Read OK, E_NOT_OK: Read failed
 */
Std_ReturnType Eth_Hw_ReadMii(const Eth_ControllerConfigType *CtrlCfgPtr, uint8 TrcvIdx, uint8 RegIdx, uint16 *RegVal)
{
    if( ETNB_0 != CtrlCfgPtr->EthHwUnit ) {
        DET_REPORT_ERROR(ETH_GLOBAL_ID, ETH_E_CONFIG_INVALID);
        return E_NOT_OK;
    }
    /* 32 consecutive 1s */
    miiWrite(MII_PRE_DATA, MII_PRE_LEN);
    /* Start of frame */
    miiWrite(MII_ST_DATA, MII_ST_LEN);
    /* Access type: read */
    miiWrite(MII_OP_READ_DATA, MII_OP_LEN);
    /* Phy address */
    miiWrite((uint32)TrcvIdx, MII_PHYAD_LEN);
    /* Register address */
    miiWrite((uint32)RegIdx, MII_REGAD_LEN);
    /* Bus release */
    miiBusRelease();
    /* read data */
    miiRead(MII_DATA_LEN, RegVal);
    /* bus release */
    miiBusRelease();
    /* Done */
    return E_OK;
}

/**
 * Set hw in requested mode
 * @param CtrlCfgPtr
 * @param CtrlMode
 * @return E_OK: Success, E_NOT_OK: Failed
 */
Std_ReturnType Eth_Hw_SetControllerMode(const Eth_ControllerConfigType *CtrlCfgPtr, uint8 CtrlIdx, Eth_ModeType CtrlMode)
{

    Std_ReturnType ret = E_OK;
    if( ETNB_0 != CtrlCfgPtr->EthHwUnit ) {
        DET_REPORT_ERROR(ETH_GLOBAL_ID, ETH_E_CONFIG_INVALID);
        return E_NOT_OK;
    }
    switch(CtrlMode) {
        case ETH_MODE_ACTIVE:
            if(E_OK != setCommunicationMode(ETH_MODE_ACTIVE)) {
                ret = E_NOT_OK;
            }
            break;
        case ETH_MODE_DOWN:
#if 0
            /* Specification does not say if frames already
             * requested for transmission should be cancelled.
             * Only that buffers should be released..  */
            if( E_OK != deletePendingTxRequests(CtrlCfgPtr) ) {
                ret = E_NOT_OK;
            }
#endif
            if(E_OK != setCommunicationMode(ETH_MODE_DOWN)) {
                ret = E_NOT_OK;
            }
            /* @req 4.1.3/SWS_Eth_00137 *//* @req 4.0.3/ETH137 */
            /* @req 4.1.3/SWS_Eth_00138 *//* @req 4.0.3/ETH138 */
            if(E_OK != resetBuffers(CtrlCfgPtr, CtrlIdx)) {
                ret = E_NOT_OK;
            }
            break;
        default:
            ret = E_NOT_OK;
            break;
    }
    return ret;
}

/**
 * Reads MAC address from Hw
 * @param CtrlIdx
 * @param PhysAddrPtr
 */
void Eth_Hw_GetPhysAddr(const Eth_ControllerConfigType *CtrlCfgPtr, uint8* PhysAddrPtr)
{
    const volatile struct st_etnb0 *hwPtr = GET_ETNB0_HW_PTR();/*lint !e923 Intentional cast from integer literal HW register address to pointer */
    if( ETNB_0 != CtrlCfgPtr->EthHwUnit ) {
        DET_REPORT_ERROR(ETH_GLOBAL_ID, ETH_E_CONFIG_INVALID);
        return;
    }
    uint32 temp = (uint32)hwPtr->MAHR;
    PhysAddrPtr[0] = (uint8)((temp>>24u) & 0xFFu);
    PhysAddrPtr[1] = (uint8)((temp>>16u) & 0xFFu);
    PhysAddrPtr[2] = (uint8)((temp>>8u) & 0xFFu);
    PhysAddrPtr[3] = (uint8)(temp & 0xFFu);

    temp = (uint32)hwPtr->MALR;
    PhysAddrPtr[4] = (uint8)((temp>>8u) & 0xFFu);
    PhysAddrPtr[5] = (uint8)(temp & 0xFFu);
}

/**
 * Provides free tx buffer if available
 * @param CtrlIdx
 * @param BufIdxPtr
 * @param BufPtr
 * @param LenBytePtr
 * @return
 */
BufReq_ReturnType Eth_Hw_ProvideTxBuffer(const Eth_ControllerConfigType *CtrlCfgPtr, Eth_BufIdxType* BufIdxPtr, Eth_DataType** BufPtr, uint16* LenBytePtr)
{
    /* @req 4.1.3/SWS_Eth_00078 *//* @req 4.0.3/ETH078 */
    /* @req 4.1.3/SWS_Eth_00080 *//* @req 4.0.3/ETH080 */
    BufReq_ReturnType ret = BUFREQ_E_BUSY;
    if( ETNB_0 != CtrlCfgPtr->EthHwUnit ) {
        DET_REPORT_ERROR(ETH_GLOBAL_ID, ETH_E_CONFIG_INVALID);
        return BUFREQ_E_NOT_OK;
    }
    /* Find a free buffer */
    for( Eth_BufIdxType bufIndex = 0; ((bufIndex < ETH_NUM_TX_BUFFERS) && (BUFREQ_E_BUSY == ret)); bufIndex++ ) {
    	SchM_Enter_Eth_EA_0();
        if( FALSE == EthTxBufferStatus[bufIndex].locked ) {
            if( *LenBytePtr > ((uint16)CtrlCfgPtr->EthCtrlTxBufLenByte - ETH_HEADER_SIZE) ) {
                /* @req 4.1.3/SWS_Eth_00079 *//* !req 4.0.3/ETH079 */
                ret = BUFREQ_E_OVFL;
            } else {
                EthTxBufferStatus[bufIndex].locked = TRUE;
                *BufIdxPtr = bufIndex;
                *BufPtr = &EthTxBufferStatus[bufIndex].dataPtr[ETH_HEADER_SIZE];
                ret = BUFREQ_OK;
            }
            *LenBytePtr = (uint16)CtrlCfgPtr->EthCtrlTxBufLenByte - ETH_HEADER_SIZE;
        }
        SchM_Exit_Eth_EA_0();
    }
    return ret;
}

/**
 * Issues a transmit request on a previously locked buffer
 * @param CtrlIdx
 * @param BufIdx
 * @param FrameType
 * @param TxConfirmation
 * @param LenByte
 * @param PhysAddrPtr
 * @return
 */
Std_ReturnType Eth_Hw_Transmit(const Eth_ControllerConfigType *CtrlCfgPtr, Eth_BufIdxType BufIdx, Eth_FrameType FrameType, boolean TxConfirmation, uint16 LenByte, const uint8* PhysAddrPtr)
{
    volatile struct st_etnb0 *hwPtr = GET_ETNB0_HW_PTR();/*lint !e923 Intentional cast from integer literal HW register address to pointer */
    if( ETNB_0 != CtrlCfgPtr->EthHwUnit ) {
        DET_REPORT_ERROR(ETH_GLOBAL_ID, ETH_E_CONFIG_INVALID);
        return E_NOT_OK;
    }
    if( BufIdx >= ETH_NUM_TX_BUFFERS ) {
        /* Bad buffer id */
        return E_NOT_OK;
    }
    if( FALSE == EthTxBufferStatus[BufIdx].locked ) {
        /* Trying to transmit using a buffer not provided */
        return E_NOT_OK;
    }
    if( LenByte > (CtrlCfgPtr->EthCtrlTxBufLenByte - ETH_HEADER_SIZE) ) {
        return E_NOT_OK;
    }

    /* Check if the next descriptor in the chain is available*/
    Std_ReturnType ret = E_NOT_OK;
    SchM_Enter_Eth_EA_0();
    if( (DT_EOS == EthTxDescriptors[EthNextTxDescIdx].DESC.B.DT) || (DT_FEMPTY == EthTxDescriptors[EthNextTxDescIdx].DESC.B.DT) || (DT_EEMPTY == EthTxDescriptors[EthNextTxDescIdx].DESC.B.DT) ) {
        /* This descriptor can be used */
        /* @req 4.1.3/SWS_Eth_00088 *//* @req 4.0.3/ETH088 */
        insertEthHeader(CtrlCfgPtr, PhysAddrPtr, EthTxBufferStatus[BufIdx].dataPtr, FrameType);
        EthTxDescriptors[EthNextTxDescIdx].DESC.B.DS = (uint32)LenByte + ETH_HEADER_SIZE;
        EthTxDescriptors[EthNextTxDescIdx].PTR.DATAPTR = EthTxBufferStatus[BufIdx].dataPtr;
        EthTxDescriptorStatus[EthNextTxDescIdx].TxBufferIdx = BufIdx;
        /* @req 4.1.3/SWS_Eth_00089 *//* @req 4.0.3/ETH089 */
        EthTxBufferStatus[BufIdx].locked = TxConfirmation;
        if(TxConfirmation) {
            EthTxDescriptorStatus[EthNextTxDescIdx].TxState = ETH_TX_DESC_TX_REQUESTED_CONFIRM;
        } else {
            EthTxDescriptorStatus[EthNextTxDescIdx].TxState = ETH_TX_DESC_TX_REQUESTED_NO_CONFIRM;
        }
        /* Issue transmit request for the queue */
        EthTxDescriptors[EthNextTxDescIdx].DESC.B.DT = DT_FSINGLE;
        hwPtr->TCCR.UINT32 |= (1UL<<ETNB_TX_QUEUE_0);/*lint !e835 Allow shift by zero for clearer code*/
        EthNextTxDescIdx = (EthNextTxDescIdx + 1) % ETH_NUM_TX_BUFFERS;
        ret =  E_OK;
    } else {
        /* No descriptor available. Something wrong */
        EthTxBufferStatus[BufIdx].locked = FALSE;
        DET_REPORT_ERROR(ETH_GLOBAL_ID, ETH_E_GENERAL_ERROR);
    }
    SchM_Exit_Eth_EA_0();

    return ret;

}

/**
 * Triggers frame transmission confirmation
 * @param CtrlIdx
 */
void Eth_Hw_TxConfirmation(uint8 CtrlIdx)
{
    /* !req 4.1.3/SWS_Eth_00101 *//* @req 4.0.3/ETH101 */
	SchM_Enter_Eth_EA_0(); // basically when in polling (Tx interrupt is off)
    while( (DT_FEMPTY == EthTxDescriptors[NextTxConfirmDescIndex].DESC.B.DT) && (ETH_TX_DESC_IDLE != EthTxDescriptorStatus[NextTxConfirmDescIndex].TxState) ) {
        if( ETH_TX_DESC_TX_REQUESTED_CONFIRM == EthTxDescriptorStatus[NextTxConfirmDescIndex].TxState ) {
            EthIf_TxConfirmation(CtrlIdx, EthTxDescriptorStatus[NextTxConfirmDescIndex].TxBufferIdx);
            /* @req 4.1.3/SWS_Eth_00102 *//* @req 4.0.3/ETH102 */
            EthTxBufferStatus[EthTxDescriptorStatus[NextTxConfirmDescIndex].TxBufferIdx].locked = FALSE;
        }
        EthTxDescriptorStatus[NextTxConfirmDescIndex].TxState = ETH_TX_DESC_IDLE;
        NextTxConfirmDescIndex = (NextTxConfirmDescIndex + 1) % ETH_NUM_TX_BUFFERS;
    }
    SchM_Exit_Eth_EA_0();
}

/**
 * Triggers frame reception
 * @param CtrlIdx
 */
void Eth_Hw_Receive(uint8 CtrlIdx)
{
    volatile struct st_etnb0 *hwPtr = GET_ETNB0_HW_PTR();/*lint !e923 Intentional cast from integer literal HW register address to pointer */
    /* @req 4.1.3/SWS_Eth_00096 *//* @req 4.0.3/ETH096 */
    while( DT_FEMPTY != EthRxDescriptors[NextRxDescIndex].DESC.B.DT ) {
        if( DT_FSINGLE == EthRxDescriptors[NextRxDescIndex].DESC.B.DT ) {
            uint8* framePtr = EthRxDescriptors[NextRxDescIndex].PTR.DATAPTR;
            Eth_FrameType frameType;
            boolean isBroadcast = TRUE;
            for( uint8 i = 0; (i < ETH_MAC_ADDR_SIZE) && isBroadcast; i++ ) {
                if(ETH_BROADCAST_BYTE != framePtr[i]) {
                    isBroadcast = FALSE;
                }
            }
            memcpy(&frameType, &framePtr[ETH_ETHERNETTYPE_START_INDEX], ETH_ETHERNETTYPE_SIZE);
            EthIf_RxIndication(CtrlIdx, frameType, isBroadcast, &framePtr[ETH_MAC_SRC_ADDR_START_INDEX], &framePtr[ETH_HEADER_SIZE], (uint16)(EthRxDescriptors[NextRxDescIndex].DESC.B.DS - ETH_HEADER_SIZE));
            /* Decrement unread frame counter for receive queue */
            hwPtr->RX_QUEUE_UFCD.UINT32 = (1UL<<RX_QUEUE_UFCD_OFFSET);/*lint !e835 Allow shift by zero for clearer code */
        } else if(DT_FSTART == EthRxDescriptors[NextRxDescIndex].DESC.B.DT) {
            /* No support for split frames */
            DET_REPORT_ERROR(ETH_GLOBAL_ID, ETH_E_GENERAL_ERROR);
            /* Decrement unread frame counter for receive queue */
            hwPtr->RX_QUEUE_UFCD.UINT32 = (1UL<<RX_QUEUE_UFCD_OFFSET);/*lint !e835 Allow shift by zero for clearer code  */
        } else {
            /* Unsupported frame */
        }
        EthRxDescriptors[NextRxDescIndex].DESC.B.DT = DT_FEMPTY;
        EthRxDescriptors[NextRxDescIndex].DESC.B.DS = (uint32)EthRxBufSize[CtrlIdx]; /*lint !e9033 Allow cast from uint16 */
        NextRxDescIndex = (NextRxDescIndex + 1) % ETH_NUM_RX_BUFFERS;
    }
}

#if defined(CFG_ETH_ARC_STATISTICS)
Std_ReturnType Eth_Arc_GetStatistics(Eth_Arc_StatisticsType *stats)
{
    Std_ReturnType ret = E_OK;
    if(NULL != stats) {
        stats->RxInterptCnt = EthStatistics.RxInterptCnt;
        stats->TxInterptCnt = EthStatistics.TxInterptCnt;
    } else {
        ret = E_NOT_OK;
    }
    return ret;
}

void Eth_Arc_ResetStatistics(void)
{
    EthStatistics.RxInterptCnt = 0;
    EthStatistics.TxInterptCnt = 0;
}
#endif

void Eth_Hw_SetPhysAddr(const Eth_ControllerConfigType *CtrlCfgPtr,
        const uint8* PhysAddrPtr) {
}
