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
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.2.2 */
/** @tagSettings DEFAULT_ARCHITECTURE=JACINTO6 */
/* ASR general requirements */
/* @req 4.2.2/SWS_Eth_00009 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Eth.h"
#include "Eth_Internal.h"
#include "Eth_jacinto.h"/* HW file */
#include <string.h>
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
#include "isr.h"
#include "irq_types.h"
#endif
#include "SchM_Eth.h"
#include "irq_types.h"
#if defined(USE_DEM) || defined(CFG_ETH_USE_DEM)
#include "Dem.h"
#endif
#include "EthIf_Cbk.h"/*file to abstract ETH from HW */
#if defined(USE_DLT) && defined(CFG_DLT_ETH_DEBUG)
#include "Dlt.h"
#include <stdio.h>
#endif
#if defined(CFG_ETH_HW_SHARE)
#include "spinlock_header.h"
#endif

#define ETH_MAX_HW_UNITS                              2u

/* ========================================================================== */
/*                             Configuration verification                                  */
/* ========================================================================== */
#if (ETH_NOF_CONFIG_CTRL > ETH_MAX_HW_UNITS)
#error "ETH: The number of configured ETH controllers exceeds to number of controller supported by Jacinto X"
#endif

#if ( ETH_DEV_ERROR_DETECT == STD_ON )
#if defined(USE_DET)
#include "Det.h"
#else
#error "Eth: DET must be used when dev error detect is enabled"
#endif
#define DET_REPORT_ERROR(_api,_err)                  (void)Det_ReportError(ETH_MODULE_ID,0,(_api),(_err))
#else
#define DET_REPORT_ERROR(_api,_err)
#endif



/* ========================================================================== */
/*                           Private Macros                                   */
/* ========================================================================== */

/* Defines for sizes in Ethernet header *************************/
#define ETH_MAC_ADDR_SIZE                             (6u)
#define ETH_ETHERNETTYPE_SIZE                         (2u)
#define ETH_CRC_SIZE                                  (4u)
#define ETH_TYPE_VLAN                                 (0x8100U)
/* Start indices for content of Ethernet header *********************/
#define ETH_MAC_DST_ADDR_START_INDEX                  (0u)
#define ETH_MAC_SRC_ADDR_START_INDEX                  (ETH_MAC_ADDR_SIZE)
#define ETH_ETHERNETTYPE_START_INDEX                  (2*ETH_MAC_ADDR_SIZE)
#define ETH_TCI_START_INDEX                           (ETH_ETHERNETTYPE_START_INDEX + 2)

/* Size of Ethernet header ***************************************/
#define ETH_HEADER_SIZE                               ((2*ETH_MAC_ADDR_SIZE) + ETH_ETHERNETTYPE_SIZE)
#define ETH_BROADCAST_BYTE                            (0xFFu)
#define ETH_MAX_MAC_ADRS_SPACE                        (4u)
#define ETH_MAX_BUSY_WAIT_CYCLES                      ((uint32)10000)   /* Max wait cycles for actions to occur in busy wait***** */
/* *************************************************************/
#define ETH_SHIFT_BYTE1                               (8u)
#define ETH_SHIFT_BYTE2                               (16u)
#define ETH_SHIFT_BYTE3                               (24u)
#define ETH_BYTE_MASK                                 (0xFFu)
/* *************************************************************/
#define ETH_BDDESC_SIZE                               (16u)
#if !defined(CFG_ETH_HW_SHARE)
#define ETH_TX_BDDESC_START_ADRS                      (0x48486000U + L3_OFFSET)
#define ETH_RX_BDDESC_START_ADRS                      (ETH_TX_BDDESC_START_ADRS + (GMAC_SW_CPPI_RAM_LEN / 2))
#else
#define ETH_BDDESC_NUM_START                          (176u)
#define ETH_BDDESC_NUM_END                            (512u)
#define ETH_BDDESC_NUM_TX_MARK                        (10u)
#define ETH_BDDESC_NUM_RX_MARK                        ((ETH_BDDESC_NUM_END - ETH_BDDESC_NUM_START) - ETH_BDDESC_NUM_TX_MARK)
#define ETH_TX_BDDESC_START_ADRS                      (0x48486000U + L3_OFFSET + (ETH_BDDESC_NUM_START * ETH_BDDESC_SIZE))
#define ETH_RX_BDDESC_START_ADRS                      (ETH_TX_BDDESC_START_ADRS + (ETH_BDDESC_NUM_TX_MARK * ETH_BDDESC_SIZE))
#if ( ETH_CTRL_0_NUM_TX_BUFFERS > ETH_BDDESC_NUM_TX_MARK) || ( ETH_CTRL_0_NUM_RX_BUFFERS > ETH_BDDESC_NUM_RX_MARK)
#error "Internal Descriptor overflow or overlap is expected"
#endif
#if (ETH_USE_CTRL_1 == STD_ON)
#error "Internal Descriptors allocated are not enough"
#endif
#endif
/* *************************************************************/
#define ETH_ISR_PRIORITY                              (5u)                 /* configure */

/* *************************************************************/
#define ETH_GET_HW_PORT_PTR(_unit)                    (GMAC_SW_PORT[_unit])


/* *************************************************************/
/* Note : These are derived from indirectly from configurations */
#define ETH_TX_BUFFERMARKER                           (ETH_CTRL_0_NUM_TX_BUFFER_SIZE * ETH_CTRL_0_NUM_TX_BUFFERS)
#define ETH_RX_BUFFERMARKER                           (ETH_CTRL_0_NUM_RX_BUFFER_SIZE * ETH_CTRL_0_NUM_RX_BUFFERS)
#define ETH_FIND_TX_BUFFERS(CtrlIdx)                  ((CtrlIdx == 0) ? (ETH_CTRL_0_NUM_TX_BUFFERS) : (ETH_NUM_TX_BUFFERS - ETH_CTRL_0_NUM_TX_BUFFERS))

/* *************************************************************/
/** @defgroup ETH Private FunctionPrototypes
 * @{
 */
/* ISRs */
/*!req 4.1.2/SWS_Eth_00109 */
void Eth_TxIrqHdlr(void);
void Eth_RxIrqHdlr(void);
#if defined(CFG_ETH_TEST)
void Eth_MiscIrqHdlr(void);
#endif

/**
 * @}
 */

/* Macro for busy waiting for a while */
#define BUSY_WAIT_A_WHILE(_regPtr, _mask, _val, _retPtr)\
    *(_retPtr) = E_NOT_OK;\
    for( uint32 i = 0; i < ETH_MAX_BUSY_WAIT_CYCLES; i++) {\
        if( (*(_regPtr) & (_mask)) == (_val) ) {\
            *(_retPtr) = E_OK;\
            break;\
        }\
    }\

#define VALIDATE_HW_NO_RV(_hw,_api,_err ) \
  if( (_hw != GMAC_SW_PORT1) && (_hw != GMAC_SW_PORT2) ) { \
      DET_REPORT_ERROR(_api, _err); \
      return; \
  }

#define VALIDATE_HW_RV(_hw,_api,_err,_ret ) \
  if( (_hw != GMAC_SW_PORT1) && (_hw != GMAC_SW_PORT2)) { \
      DET_REPORT_ERROR(_api, _err); \
      return (_ret); \
  }


/* Global Control Module */
#define CTRL_MODULE_CORE                                     (0x4A002000U + L3_OFFSET)
#define CTRL_CORE_CONTROL_IO_1                               (0x00000554U)
#define	CTRL_CORE_MMR_LOCK_1                                 (0x00000540U)
#define GMII1_SEL_MASK                                       (0x00000003U)
#define GMII2_SEL_MASK                                       (0x00000030U)
#define GMII2_SEL_SHIFT                                      (4u)
#define MMR_LOCK_1                                           (0x1A1C8144U)
#define MMR_UNLOCK_1                                         (0x2FF1AC2BU)

/* IPU Cache Control */
#define IPUx_UNICACHE_CFG_CACHE_MTSTART                      (0x55080014U)
#define IPUx_UNICACHE_CFG_CACHE_MTEND                        (0x55080018U)
#define IPUx_UNICACHE_CFG_CACHE_MAINT                        (0x55080010U)
#define IPUx_UNICACHE_INVALIDATE                             (0x00000010U)
#define ETH_RX_BUF_ACCESS_SOME_DELAY                         (125u)

/* HW Spin Lock  */
#define SPIN_LOCK_REVISION                                   (0x4A0F6000U)
#define SPIN_LOCK_SYSCONFIG                                  (0x4A0F6010U)
#define SPIN_LOCK_SYSSTATUS                                  (0x4A0F6014U)
#define SPIN_LOCK_REG(i)							         (0x4A0F6800 + (0x4 * i))

#define SPIN_LOCK_RESET_STATUS                               (0x00000001U)
#define SPIN_LOCK_TAKEN                                      (0x00000001U)
#define SPIN_LOCK_FREE                                       (0x00000000U)

/*lint -save -e9003 -e923 -e9033 */
/* 923 - "WRITE_REG_32" has notes 'cast from pointer to unsigned int' and 'cast from unsigned int to pointer'.. these are allowed
 * 9033 - Impermissible cast of composite expression (different essential type categories) is allowed
 * 9003 - EthRxDataBuffer and EthTxDataBuffer is defined as static as per ASR , global scope is not allowed*/

#define WRITE_REG_32(addr,value)                             (*(vuint32_t *)(addr) = (uint32)value)
#define READ_REG_32(addr)                                    (*(vuint32_t *)(addr))
#define WRITE_READ_REG_32(addr,mask,value)                   ( WRITE_REG_32( addr,(((READ_REG_32(addr)) & ~(uint32)(mask)) | value) ) )

#if defined(USE_DLT) && defined(CFG_DLT_ETH_DEBUG)
#define ETH_DLT_MAX_MSG_LEN                                  (100U)
#define ETH_DLT_EXTRA_BYTES                                  (4U)

static 	Dlt_MessageLogInfoType EthLoginfo =
{
	.app_id = "ETH ",
	.context_id = "Logr",
	.arg_count = 0,
	.options = (uint8)0x00u,
};


#define ETH_DLT_LOG(level, ...)																							        \
{																																\
	uint8 logMsg[ETH_DLT_MAX_MSG_LEN + ETH_DLT_EXTRA_BYTES];                                                                    \
	EthLoginfo.log_level = level;																					         	\
	snprintf(((sint8*)logMsg + ETH_DLT_EXTRA_BYTES), ETH_DLT_MAX_MSG_LEN, __VA_ARGS__);										    \
	(void)Dlt_SendLogMessage(0x1234u,&EthLoginfo, logMsg, strlen((sint8*)logMsg));                      	                    \
}

#define ETH_DLT_LOG_ERROR(...)                               ETH_DLT_LOG(DLT_LOG_ERROR, __VA_ARGS__)
#define ETH_DLT_LOG_INFO(...)                                ETH_DLT_LOG(DLT_LOG_INFO,  __VA_ARGS__)
#endif


/* ========================================================================== */
/*                           Private Typedefs                                 */
/* ========================================================================== */

typedef struct {
    boolean locked;
    uint8* dataPtr;
} EthBufferStatusType;

typedef enum {
    ETH_TX_DESC_IDLE = 0,
    ETH_TX_DESC_TX_REQUESTED_NO_CONFIRM,
    ETH_TX_DESC_TX_REQUESTED_CONFIRM
} EthTxRequestType;

typedef struct {
    EthTxRequestType TxState;
    Eth_BufIdxType TxBufferIdx;
} EthTxDescStatusType;

typedef struct Desc_s {
    volatile struct Desc_s *pNextDesc;       /* Pointer to next descriptor in chain */
    vuint8_t *pBuf;                          /* Pointer to data buffer */
    uint32 BufOffLen;                        /* Buffer Offset(MSW) and Length(LSW) */
    uint32 PktFlgLen;                        /* Packet Flags(MSW) and Length(LSW) */
} EthDescType;

typedef struct {
    uint32 AleTablW0;
    uint32 AleTablW1;
    uint32 AleTablW2;
}Eth_AleTablValueType;

typedef struct {
	volatile EthDescType* pDescHead;
	volatile EthDescType* pDescTail;
	uint32 EthQueueMissed; /* A mis-queued buffer may occur when the host adds buffers to a queue as the port finishes the reception
                               of the previous last packet in the queue at the same time */
}EthDescChainType;

/* Type for holding information about each controller */
typedef struct {
    /* Controller config */
    const Eth_ControllerConfigType *pEthcfgPtr;
    /* RX/TX descriptors */
    volatile EthDescType*  pEthRxDesc;
    volatile EthDescType*  pEthTxDesc;
    /* TX descriptor status */
    EthTxDescStatusType* EthTxDescStatus;
    EthBufferStatusType* EthTxBufferStatus;
    /* Index of the next descriptor to use for TX */
    uint32 EthNextTxDescIdx;
    /* Circular or non-circular single linked RX descriptor list */
    EthDescChainType* pEthRxDescChain;
    /* Maximum RX buffer length */
    uint32 EthMaxRxBufLen;

} Eth_CtrlType;


/* ========================================================================== */
/*                           Private Variables                                */
/* ========================================================================== */

static GmacSw_HwRegType * const pHwPtr = (GmacSw_HwRegType*) GMAC_SW_BASE; /*lint !e923 Intentional cast from integer literal HW register address to pointer */

/* @req 4.2.2/SWS_Eth_00218 */
/*lint -save -e9003 */ /* Global scope for EthRxDataBuffer and EthTxDataBuffer is allowed */
static uint8 EthRxDataBuffer[ETH_TOTAL_RX_BUFFER_SIZE] __balign(ETH_BUF_ALIGNING_BYTES);
static uint8 EthTxDataBuffer[ETH_TOTAL_TX_BUFFER_SIZE] __balign(ETH_BUF_ALIGNING_BYTES);

/* RX/TX descriptors */
#if defined(CFG_ETH_HW_DESC_NON_CPPI_RAM) /* If CPPI On-chip SRAM is not used it clogs the EMIF(external memory interface ) with stores and fetches */
#define ETH_DESC_START_SEC_CLEARED_4
#include "MemMap.h"
static EthDescType EthRxDesc[ETH_NUM_RX_BUFFERS] __balign(ETH_DESC_ALIGNING_BYTES);
#define ETH_DESC_STOP_SEC_CLEARED_4
#include "MemMap.h"

#define ETH_DESC_START_SEC_CLEARED_4
#include "MemMap.h"
static EthDescType EthTxDesc[ETH_NUM_TX_BUFFERS] __balign(ETH_DESC_ALIGNING_BYTES);
#define ETH_DESC_STOP_SEC_CLEARED_4
#include "MemMap.h"
#endif

#if (ETH_USE_CTRL_0 == STD_ON )
/* For link to TX buffer and state of TX descriptor */
static EthTxDescStatusType EthCtrl0TxDescStatus [ETH_CTRL_0_NUM_TX_BUFFERS];
/* For holding the state of a TX buffer */
static EthBufferStatusType EthCtrl0TxBufferStatus [ETH_CTRL_0_NUM_TX_BUFFERS];
#endif
#if (ETH_USE_CTRL_1 == STD_ON )   /*lint !e553, Intentional it is defined if second controller is not configured from the tool */
/* For link to TX buffer and state of TX descriptor */
static EthTxDescStatusType EthCtrl1TxDescStatus [ETH_CTRL_1_NUM_TX_BUFFERS];
/* For holding the state of a TX buffer */
static EthBufferStatusType EthCtrl1TxBufferStatus [ETH_CTRL_1_NUM_TX_BUFFERS];
#endif
#if (ETH_USE_CTRL_0 == STD_ON )
static EthDescChainType EthCtrl0RxDescChain;
#endif
#if (ETH_USE_CTRL_1 == STD_ON )   /*lint !e553, Intentional it is defined if second controller is not configured from the tool */
static EthDescChainType EthCtrl1RxDescChain;
#endif

#if defined(CFG_ETH_ARC_STATISTICS)
Eth_Arc_StatisticsType EthStatistics;
#endif

/* Controller private data. */
static Eth_CtrlType EthCtrlUnit[ETH_NOF_CONFIG_CTRL] =
        {
#if (ETH_USE_CTRL_0 == STD_ON )
        {
           .pEthcfgPtr = NULL,
#if defined(CFG_ETH_HW_DESC_NON_CPPI_RAM)
        .pEthRxDesc = (EthDescType*) EthRxDesc,
        .pEthTxDesc = (EthDescType*) EthTxDesc,
#else
        /* In order not to create a new bottleneck at the external memory interface (EMIF) to system memory
         8-Kb cache is used for max through put  */
        .pEthRxDesc = (EthDescType*)ETH_RX_BDDESC_START_ADRS, /*lint !e923 Intentional cast */
        .pEthTxDesc = (EthDescType*)ETH_TX_BDDESC_START_ADRS, /*lint !e923 Intentional cast */
#endif
        .EthTxDescStatus = EthCtrl0TxDescStatus,
        .EthTxBufferStatus = EthCtrl0TxBufferStatus,
        .EthNextTxDescIdx = 0u,
		.pEthRxDescChain = &EthCtrl0RxDescChain,
		.EthMaxRxBufLen = 0,
    },
#endif
#if (ETH_USE_CTRL_1 == STD_ON )  /*lint !e553, Intentional it is defined if second controller is not configured from the tool */
        {
        .pEthcfgPtr = NULL,
#if defined(CFG_ETH_HW_DESC_NON_CPPI_RAM)
        .pEthRxDesc = &EthRxDesc[ETH_NUM_RX_BUFFERS - ETH_CTRL_0_NUM_RX_BUFFERS],
        .pEthTxDesc = &EthTxDesc[ETH_NUM_TX_BUFFERS - ETH_CTRL_0_NUM_TX_BUFFERS],
#else
        /* In order not to create a new bottleneck at the external memory interface (EMIF) to system memory
         8-Kb cache is used for max through put  */
        .pEthRxDesc = (EthDescType*)(ETH_RX_BDDESC_START_ADRS + ETH_MAX_DESCRIPTOR_SIZE), /*lint !e923 Intentional cast */
        .pEthTxDesc = (EthDescType*)(ETH_TX_BDDESC_START_ADRS + ETH_MAX_DESCRIPTOR_SIZE), /*lint !e923 Intentional cast */
#endif
        .EthTxDescStatus = EthCtrl1TxDescStatus,
        .EthTxBufferStatus = EthCtrl1TxBufferStatus,
        .EthNextTxDescIdx = 0u,
		.pEthRxDescChain = &EthCtrl1RxDescChain,
		.EthMaxRxBufLen = 0,
    }
#endif
    };


/* ========================================================================== */
/*                           Static Functions                                 */
/* ========================================================================== */
/* Static function declarations */
static void configureDesc(const Eth_ControllerConfigType *pCfgPtr);

/**
 * Clear Desc Pointers
 * @return None
 */
static void resetHeadDescPointers(uint8 ctrlIdx) {
    WRITE_REG_32((uint32)(&pHwPtr->STATERAM.TX0_HDP) + (sizeof(uint32) * EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwTxDmaCh), 0uL );
    WRITE_REG_32((uint32)(&pHwPtr->STATERAM.RX0_HDP) + (sizeof(uint32) * EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwRxDmaCh), 0uL );
    WRITE_REG_32((uint32)(&pHwPtr->STATERAM.TX0_CP)  + (sizeof(uint32) * EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwTxDmaCh), 0uL );
    WRITE_REG_32((uint32)(&pHwPtr->STATERAM.RX0_CP)  + (sizeof(uint32) * EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwRxDmaCh), 0uL );
}


/**
 * Enables GMAC Switch interrupts if configured
 * @param ctrlIdx
 * @return none
 */
static void enableInterrupts (uint8 ctrlIdx){
    if (TRUE == EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthCtrlEnableRxInterrupt) {
        /* RX_PULSE - Receive pulse Interrupt */
        pHwPtr->CPDMA.CPDMA_RX_INTMASK_SET  |=  ((uint32)ETH_GMAC_SW_TRXn_PEND_MASK << EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwRxDmaCh);
        pHwPtr->CPDMA.CPDMA_RX_INTMASK_CLEAR  &= ~((uint32)ETH_GMAC_SW_TRXn_PEND_MASK <<  EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwRxDmaCh);
        pHwPtr->WR.WR_C0_RX_EN |= ((uint32)ETH_GMAC_C0_TRXn_EN <<  EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwRxDmaCh);

        /* RX_THRESH_PULSE - Receive Threshold Pulse Interrupt */
        pHwPtr->CPDMA.CPDMA_RX_INTMASK_SET  |= ((uint32)ETH_GMAC_SW_RXn_THRESH_PEND_MASK <<  EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwRxDmaCh);
        pHwPtr->WR.WR_C0_RX_THRESH_EN |= ((uint32)ETH_GMAC_C0_RXn_THRESH_EN <<  EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwRxDmaCh);

        WRITE_REG_32((uint32)(&pHwPtr->CPDMA.CPDMA_RX0_PENDTHRESH) + (sizeof(uint32) * EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwRxDmaCh), 1u);
    }
    if (TRUE == EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthCtrlEnableTxInterrupt) {
        /* TX_PULSE Transmit Packet Completion Pulse Interrupt */
        pHwPtr->CPDMA.CPDMA_TX_INTMASK_SET |= ((uint32)ETH_GMAC_SW_TRXn_PEND_MASK << EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwTxDmaCh);
        pHwPtr->CPDMA.CPDMA_TX_INTMASK_CLEAR &= ~((uint32)ETH_GMAC_SW_TRXn_PEND_MASK << EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwTxDmaCh);
        pHwPtr->WR.WR_C0_TX_EN |= ((uint32)ETH_GMAC_C0_TRXn_EN << EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwTxDmaCh);
    }

#if defined(CFG_ETH_TEST)
    /* MISC_PULSE Miscellaneous Pulse Interrupt */
    pHwPtr->WR.WR_C0_MISC_EN |= ETH_GMAC_SW_HOST_PENDINT;
    pHwPtr->CPDMA.CPDMA_DMA_INTMASK_SET |= ETH_GMAC_SW_HOST_ERR_INT_MASK;

    pHwPtr->WR.WR_C0_MISC_EN |= ETH_GMAC_SW_STAT_PENDINT;
    pHwPtr->CPDMA.CPDMA_DMA_INTMASK_SET |= ETH_GMAC_SW_STAT_INT_MASK;
#endif
}


/**
 * Disables GMAC Switch interrupts if configured
 * @param ctrlIdx
 * @return none
 */
static void disableInterrupts (uint8 ctrlIdx){
    if (TRUE == EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthCtrlEnableRxInterrupt) {
        /* RX_PULSE - Receive pulse Interrupt */
        pHwPtr->CPDMA.CPDMA_RX_INTMASK_CLEAR  |= ((uint32)ETH_GMAC_SW_TRXn_PEND_MASK << EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwRxDmaCh);
        pHwPtr->WR.WR_C0_RX_EN &= (~(uint32)ETH_GMAC_C0_TRXn_EN << EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwRxDmaCh);

        /* RX_THRESH_PULSE - Receive Threshold Pulse Interrupt */
        pHwPtr->CPDMA.CPDMA_RX_INTMASK_CLEAR  |= ((uint32)ETH_GMAC_SW_RXn_THRESH_PEND_MASK << EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwRxDmaCh);
        pHwPtr->WR.WR_C0_RX_THRESH_EN &= (~(uint32)ETH_GMAC_C0_RXn_THRESH_EN << EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwRxDmaCh);
    }
    if (TRUE == EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthCtrlEnableTxInterrupt) {
        /* TX_PULSE Transmit Packet Completion Pulse Interrupt */
        pHwPtr->CPDMA.CPDMA_TX_INTMASK_CLEAR |= ((uint32)ETH_GMAC_SW_TRXn_PEND_MASK << EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwTxDmaCh);
        pHwPtr->WR.WR_C0_TX_EN &= (~(uint32)ETH_GMAC_C0_TRXn_EN << EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwTxDmaCh);
    }

#if defined(CFG_ETH_TEST)
    /* MISC_PULSE Miscellaneous Pulse Interrupt */
    pHwPtr->WR.WR_C0_MISC_EN &= ~ETH_GMAC_SW_HOST_PENDINT;
    pHwPtr->CPDMA.CPDMA_DMA_INTMASK_SET &= ~ETH_GMAC_SW_HOST_ERR_INT_MASK;

    pHwPtr->WR.WR_C0_MISC_EN &= ~ETH_GMAC_SW_STAT_PENDINT;
    pHwPtr->CPDMA.CPDMA_DMA_INTMASK_SET &= ~ETH_GMAC_SW_STAT_INT_MASK;
#endif

}

/**
 * Configures the MAC address
 * @param hwUnit
 * @param macAdrs (network byte order)
 * @return none
 */
static void configureMacAdrs(uint8 hwUnit, const uint8* macAdrs) {
    uint32 valHi;
    uint32 valLo;

    valLo = 0uL;
    /*lint -save -e9033 -e9053*/
    /* Impermissible cast of composite expression (wider essential type for the destination
     * The shift value is at least the precision of the essential type of the left hand side
     * Misra is not happy with shifting u char and loading on to u int and ultimately with casting
     * Reasoning :: Autosar API is addressed by u character pointer and HW register is an u integer
     * and has to be stored in the same manner
     */
    valLo |= ((uint32) macAdrs[5] << ETH_SHIFT_BYTE1);
    valLo |= ((uint32) macAdrs[4]);

    valHi = 0uL;
    valHi |= ((uint32) macAdrs[3] << ETH_SHIFT_BYTE3);
    valHi |= ((uint32) macAdrs[2] << ETH_SHIFT_BYTE2);
    valHi |= ((uint32) macAdrs[1] << ETH_SHIFT_BYTE1);
    valHi |= ((uint32) macAdrs[0]);
    /*lint -restore*/
    
    if(hwUnit == GMAC_SW_PORT1){
        pHwPtr->PORT1.SA_HI = valHi;
        pHwPtr->PORT1.SA_LO = valLo;
    }else{
        pHwPtr->PORT2.SA_HI = valHi;
        pHwPtr->PORT2.SA_LO = valLo;
    }
}

/**
 * Activates/deactivates the Eth controller
 * @param ctrlMode
 * @param ctrlIdx
 * @return E_OK: Action OK
 */
static Std_ReturnType setCommunicationMode(Eth_ModeType ctrlMode, uint8 ctrlIdx) {
    Std_ReturnType ret = E_OK;
    switch (ctrlMode) {
        case ETH_MODE_ACTIVE:
            /* Start TX and RX operations */
            /* write starting desc address to receive-desc(HDP) queue base address */
            WRITE_REG_32( (uint32)(&pHwPtr->STATERAM.RX0_HDP) + (sizeof(uint32) * EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwRxDmaCh), (uint32)EthCtrlUnit[ctrlIdx].pEthRxDesc);
            WRITE_REG_32( (uint32)(&pHwPtr->CPDMA.CPDMA_RX0_FREEBUFFER) + (sizeof(uint32) * EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwRxDmaCh), EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthRxBufTotal);

            enableInterrupts(ctrlIdx);

            configureDesc(EthCtrlUnit[ctrlIdx].pEthcfgPtr);
            /* Enable transmission and reception */
            if (0u == (pHwPtr->CPDMA.CPDMA_TX_CONTROL & ETH_GMAC_SW_CPDMA_TX_EN)) {
                pHwPtr->CPDMA.CPDMA_TX_CONTROL |= ETH_GMAC_SW_CPDMA_TX_EN;
            }
            if (0u == (pHwPtr->CPDMA.CPDMA_RX_CONTROL & ETH_GMAC_SW_CPDMA_RX_EN)) {
                pHwPtr->CPDMA.CPDMA_RX_CONTROL |= ETH_GMAC_SW_CPDMA_RX_EN;
            }            
            break;

        case ETH_MODE_DOWN:
            /* Disable transmission and reception */
            pHwPtr->CPDMA.CPDMA_TX_CONTROL &= ~ETH_GMAC_SW_CPDMA_TX_EN;
            pHwPtr->CPDMA.CPDMA_RX_CONTROL &= ~ETH_GMAC_SW_CPDMA_RX_EN;
            /* Clear DMA Receive andTransmit HDP Controls */
            resetHeadDescPointers(ctrlIdx);
            /* Clear statuses of TX and RX if any */
            disableInterrupts(ctrlIdx);
            break;

        default:
            ret = E_NOT_OK;
            break;
    }
    return ret;
}

/**
 * Initializes buffer
 * @param pCfgPtr
 * @param ctrlIdx
 */
static void initBuffers(const Eth_ControllerConfigType *pCfgPtr, uint8 ctrlIdx) {
    uint32 nextDataIndex = 0u;
    /* Set up the buffer runtime variables */
    EthCtrlUnit[ctrlIdx].EthNextTxDescIdx = 0u;
    memset(EthCtrlUnit[ctrlIdx].EthTxDescStatus, 0u,
            (sizeof(EthTxDescStatusType) * ETH_FIND_TX_BUFFERS(ctrlIdx)));/*lint !e778 Constant expression evaluates to 0 in operation */
    /* constants used are not zero or evaluates to zero after operation */
    for (uint32 txBufIdx = 0; txBufIdx < pCfgPtr->EthTxBufTotal; txBufIdx++) {
        EthCtrlUnit[ctrlIdx].EthTxBufferStatus[txBufIdx].locked = FALSE;
        EthCtrlUnit[ctrlIdx].EthTxBufferStatus[txBufIdx].dataPtr =
                &EthTxDataBuffer[(pCfgPtr->EthCtrlIdx * ETH_TX_BUFFERMARKER)
                        + nextDataIndex];
        nextDataIndex = (pCfgPtr->EthCtrlIdx * ETH_TX_BUFFERMARKER)
                + nextDataIndex
                + (uint32) (pCfgPtr->EthCtrlTxBufLenByte
                + (pCfgPtr->EthCtrlTxBufLenByte % ETH_BUF_ALIGNING_BYTES));/*lint !e9033 */
        /* wider essential type for the destination - destination would not exceed the limit -
         * ASR restrictions are available too */
    }
}

/**
 * Resets rx and tx buffer
 * @param pCtrlCfgPtr
 * @param ctrlIdx
 * @return E_OK: Action OK
 */
static Std_ReturnType resetBuffers(const Eth_ControllerConfigType *pCtrlCfgPtr,
        uint8 ctrlIdx) {
    volatile EthDescType *pEthDesc = EthCtrlUnit[ctrlIdx].pEthTxDesc;
    for (uint32 txBufIdx = 0; txBufIdx < pCtrlCfgPtr->EthTxBufTotal; txBufIdx++) {
        /* write as Host control, so no transmission*/
        pEthDesc[txBufIdx].PktFlgLen &= ~ETH_GMAC_SW_DSC_FLAG_OWNER;
    }
    pEthDesc = EthCtrlUnit[ctrlIdx].pEthRxDesc;
    for (uint32 rxBufIdx = 0; rxBufIdx < pCtrlCfgPtr->EthRxBufTotal; rxBufIdx++) {
        /* Rx buffers are busy*/
        pEthDesc[rxBufIdx].PktFlgLen &= ~ETH_GMAC_SW_DSC_FLAG_OWNER;
    }

     /* Initialize buffer runtime data */
    initBuffers(pCtrlCfgPtr, ctrlIdx);
    /*  Desc addresses are re loaded  */
    return E_OK ;
}


/**
 * Configures all RX and TX descriptor chain
 * @param pCfgPtr
 * @return none
 */
static void configureDesc(const Eth_ControllerConfigType *pCfgPtr) {
    uint32 Val;
    volatile EthDescType *pEthDesc = EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthRxDesc;
    /* Setup buffer descriptor lists / chains */
    uint32 nextDataIndex = 0;

    pHwPtr->CPDMA.CPDMA_RX_BUFFER_OFFSET &= ~ETH_GMAC_SW_DSC_RX_BUFFER_OFFSET_MASK;
    EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthRxDescChain->pDescHead = pEthDesc;
    EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthRxDescChain->EthQueueMissed = 0;
    for (uint32 rxBufIdx = 0; rxBufIdx < pCfgPtr->EthRxBufTotal; rxBufIdx++) {
        if ((pCfgPtr->EthRxBufTotal - 1) != rxBufIdx) {
            pEthDesc[rxBufIdx].pNextDesc = (pEthDesc + rxBufIdx+1); /*lint !e9016  Intentional pointer arithematic */
        }else{
        	EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthRxDescChain->pDescTail = &pEthDesc[rxBufIdx];
            if(pCfgPtr->EthHwEnableCircDesc == FALSE){
                /* End the queue */
                pEthDesc[rxBufIdx].pNextDesc = NULL;
                EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthRxDescChain->pDescTail->pNextDesc = NULL;
            }else{
                /* make circular linked list,Let the the last one be linked to first one */
                pEthDesc[rxBufIdx].pNextDesc = EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthRxDesc;
                EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthRxDescChain->pDescTail->pNextDesc = pEthDesc[rxBufIdx].pNextDesc;
            }
        }
        pEthDesc[rxBufIdx].BufOffLen = 0uL;

        Val = (pCfgPtr->EthCtrlRxBufLenByte + (pCfgPtr->EthCtrlRxBufLenByte % (uint32)ETH_BUF_ALIGNING_BYTES));

        pEthDesc[rxBufIdx].BufOffLen &= ~ETH_GMAC_SW_DSC_RX_BUF_LEN_MASK;
        pEthDesc[rxBufIdx].BufOffLen |=  Val;

        /* Write with the buffer address */
        pEthDesc[rxBufIdx].pBuf = (vuint8_t *)((&EthRxDataBuffer[(pCfgPtr->EthCtrlIdx * (uint32)ETH_RX_BUFFERMARKER) + nextDataIndex]));/*lint !e926  Intentional cast from pointer to pointer*/
        nextDataIndex = nextDataIndex
                + (uint32) (pCfgPtr->EthCtrlRxBufLenByte
                        + (pCfgPtr->EthCtrlRxBufLenByte % ETH_BUF_ALIGNING_BYTES));/*lint !e9033 destination would not exceed the limit */
        pEthDesc[rxBufIdx].PktFlgLen = 0uL;
        /* Mark all entries in this list as owned by Host */
        pEthDesc[rxBufIdx].PktFlgLen  |= ETH_GMAC_SW_DSC_FLAG_OWNER;
    }
#if defined(CFG_ETH_TX_STATIC_BUF_ASSIGN)
    nextDataIndex = 0;
#endif
    pEthDesc = EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthTxDesc;
    for (uint32 txBufIdx = 0; txBufIdx <  pCfgPtr->EthTxBufTotal ; txBufIdx++) {
#if 0 /* For future uses */
        if ((pCfgPtr->EthTxBufTotal - 1) != txBufIdx) {
            pEthDesc[txBufIdx].pNextDesc =  (pEthDesc + txBufIdx+1);
        }else{
            /* Last one should be NULL terminated */
            pEthDesc[txBufIdx].pNextDesc = NULL;
        }
#endif
        pEthDesc[txBufIdx].pNextDesc = NULL; /* Each Tx Desc is ended */

#if defined(CFG_ETH_TX_STATIC_BUF_ASSIGN)
        /* Static buffer assignment to the descriptor */
        pEthDesc[txBufIdx]->pBuf = (vuint8_t *)&EthTxDataBuffer[(CfgPtr->EthCtrlIdx * ETH_TX_BUFFERMARKER) + nextDataIndex];
        nextDataIndex = nextDataIndex + (uint32)(CfgPtr->EthCtrlTxBufLenByte + (CfgPtr->EthCtrlTxBufLenByte % ETH_BUF_ALIGNING_BYTES));
#endif
        pEthDesc[txBufIdx].BufOffLen &= ~ETH_GMAC_SW_DSC_TX_BUF_LEN_MASK;
        pEthDesc[txBufIdx].BufOffLen &= ~ETH_GMAC_SW_DSC_TX_BUF_OFFSET_MASK;
        pEthDesc[txBufIdx].PktFlgLen = 0uL;
        /* Last buffer, no options in ASR for multi frames, just support Single frames */
        pEthDesc[txBufIdx].PktFlgLen |= ETH_GMAC_SW_DSC_FLAG_PKT_SINGLE;

        pEthDesc[txBufIdx].PktFlgLen &= ~ETH_GMAC_SW_DSC_FLAG_OWNER; /* not yet ready for transmission */

        if (FALSE == EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthcfgPtr->EthHwEnableTxChecksumOffload) {
            pEthDesc[txBufIdx].PktFlgLen |= ETH_GMAC_SW_DSC_FLAG_PASSCRC;
        }
        pEthDesc[txBufIdx].PktFlgLen |= ETH_GMAC_SW_DSC_FLAG_TO_PORT_EN; /* on SOP */
        pEthDesc[txBufIdx].PktFlgLen &= ~ETH_GMAC_SW_DSC_FLAG_TO_PORT_MASK; /* on SOP */
        pEthDesc[txBufIdx].PktFlgLen |= ((uint32)pCfgPtr->EthHwUnit << ETH_GMAC_SW_DSC_FLAG_TO_PORT_SHIFT);
    }
}

#if (ETH_HW_SOFT_RESET == STD_ON)
/**
 * Soft reset
 * @param none
 * @return none
 */
static void reset(void){
    /* Software resets */ /* Happens on any device level reset , no GMAC_SW reset isolation */
    /*  3G logic reset */
    /* CPGMACSS_R logic to be reset (INT, REGS, CPPI).*/
    pHwPtr->WR.WR_SOFT_RESET |= ETH_GMAC_SW_SOFT_RESET;
    while((pHwPtr->WR.WR_SOFT_RESET & ETH_GMAC_SW_SOFT_RESET) ==  ETH_GMAC_SW_SOFT_RESET){};

    /* CPGMAC_SL logic to be reset*/
    pHwPtr->SL1.SL_SOFT_RESET |= ETH_GMAC_SW_SOFT_RESET;
    while((pHwPtr->SL1.SL_SOFT_RESET & ETH_GMAC_SW_SOFT_RESET) ==  ETH_GMAC_SW_SOFT_RESET){};
    /* CPGMAC_SL logic to be reset*/
    pHwPtr->SL2.SL_SOFT_RESET |= ETH_GMAC_SW_SOFT_RESET;
    while((pHwPtr->SL2.SL_SOFT_RESET & ETH_GMAC_SW_SOFT_RESET) ==  ETH_GMAC_SW_SOFT_RESET){};

    /* CPDMA logic to be reset*/
    pHwPtr->CPDMA.CPDMA_SOFT_RESET |= ETH_GMAC_SW_SOFT_RESET;
    while((pHwPtr->CPDMA.CPDMA_SOFT_RESET & ETH_GMAC_SW_SOFT_RESET) ==  ETH_GMAC_SW_SOFT_RESET){};

    pHwPtr->SS.CPSW_SOFT_RESET |= ETH_GMAC_SW_SOFT_RESET;
    while((pHwPtr->SS.CPSW_SOFT_RESET & ETH_GMAC_SW_SOFT_RESET) ==  ETH_GMAC_SW_SOFT_RESET){};
}
#endif

/**
 * Configures MDIO operation
 * @param none
 * @return none
 */
static void configureMDIO(void){
    uint32 mdcClkDiv;
    /*Enable control.*/
    pHwPtr->MDIO.MDIO_CONTROL |= ETH_GMAC_SW_MDIO_ENABLE;

    /*Disable MDIO preamble*/
    /* pHwPtr->MDIO.MDIO_CONTROL |= ETH_GMAC_SW_MDIO_PREAMBLE_DISABLE; */

    /*Enable Fault detect */
    pHwPtr->MDIO.MDIO_CONTROL |= ETH_GMAC_SW_MDIO_FAULTENB;
#if defined(CFG_ETH_TEST)
    /* Interrupt test enable. */
    pHwPtr->MDIO.MDIO_CONTROL |= ETH_GMAC_SW_MDIO_INTTESTENB;
#endif
    /* MDCLK frequency = ICLK frequency/(CLKDIV+1)   CLKDIV = (ICLK frequency /  MDCLK frequency) - 1 */
    mdcClkDiv = ((ETH_GMAC_MAIN_CLK / ETH_GMAC_MDC_CLK ) - 1);

    pHwPtr->MDIO.MDIO_CONTROL &= ~ETH_GMAC_SW_MDIO_CLK_DIV_MASK;
    pHwPtr->MDIO.MDIO_CONTROL |=  mdcClkDiv ;
}


/**
 * Read a ALE table entry
 * @param pTableVal
 * @param tablId
 * @return none
 */
static void readTablEntry(Eth_AleTablValueType * const  pTableVal,uint32 tablId){
    pHwPtr->ALE.ALE_TBLCTL = tablId;
    pTableVal->AleTablW0 = pHwPtr->ALE.ALE_TBLW0;
    pTableVal->AleTablW1 = pHwPtr->ALE.ALE_TBLW1;
    pTableVal->AleTablW2 = pHwPtr->ALE.ALE_TBLW2;
}

/**
 * Write a ALE table entry
 * @param pTableVal
 * @param tablId
 * @return none
 */
static void writeTablEntry(const Eth_AleTablValueType * pTableVal,uint32 tablId){
    uint32 val;
    pHwPtr->ALE.ALE_TBLW0 = pTableVal->AleTablW0;
    pHwPtr->ALE.ALE_TBLW1 = pTableVal->AleTablW1;
    pHwPtr->ALE.ALE_TBLW2 = pTableVal->AleTablW2;
    val = (tablId | ETH_GMAC_SW_ALE_TAB_WRITE_RDZ );
    pHwPtr->ALE.ALE_TBLCTL = val; /* I don't know how TablId looks when learning happens */
}

/**
 * Compare the MAC address with the address in the table value register
 * @param pTableVal
 * @param pMacAdrs
 * @return Std_ReturnType
 */
static inline Std_ReturnType compareEntryAddress(const Eth_AleTablValueType * pTableVal, const uint8 *pMacAdrs){
    Std_ReturnType ret = E_OK;
    for(uint8 i= 0; (i < ETH_MAC_ADDR_SIZE) && (ret == E_OK) ; i++){
        if (*(((uint8 *)pTableVal)+i) != pMacAdrs[5-i]){ /*lint !e928 !e9005 !e9016 Intentional cast from pointer to pointer*/
            ret = E_NOT_OK;
        }
    }
    return ret;
}


/**
 * Search for an address table entry
 * @param pMacAdrs
 * @param vid
 * @return uint32
 */
static uint32 searchAdrsTablEntry(const uint8 *pMacAdrs,uint16 vid){
    uint32 foundTablId = ETH_GMAC_SW_TABL_ENTRY_UNKNOWN;
    Eth_AleTablValueType aleTablVal;
    uint32 tablEntry;

    for(vuint32_t i = 0; i < ETH_GMAC_SW_TABL_ENTRY_UNKNOWN ; i++){
        readTablEntry(&aleTablVal,i);
        tablEntry = ((aleTablVal.AleTablW1 & ETH_GMAC_SW_TABL_ENTRY1_TYPE_MASK)>>ETH_GMAC_SW_TABL_ENTRY1_TYPE_SHIFT);

         if((tablEntry == (uint32)ALE_ADRS_ENTRY) ||
            (tablEntry == (uint32)ALE_VLAN_ADRS_ENTRY)){
            if((compareEntryAddress(&aleTablVal,pMacAdrs) == E_OK) 	   &&
               (((aleTablVal.AleTablW1 & ETH_GMAC_SW_TABL_ENTRY1_VID_MASK) >> ETH_GMAC_SW_TABL_ENTRY1_VID_SHIFT) == vid)){
                foundTablId = i;
                break;
            }
         }
    }
    return foundTablId;
}

/**
 * Verifies if the address is a multicast entry
 * @param pMacAdrs
 * @return boolean
 */
static boolean isEntryMulticast (const uint8 *pMacAdrs){
    boolean isMcastEntry = FALSE;
    if( (pMacAdrs[ETH_GMAC_MCAST_ADDR_VALIDATE_BYTE] & ETH_GMAC_MCAST_ADDR_MASK) == ETH_GMAC_MCAST_ADDR_MASK){
        isMcastEntry = TRUE;
    }
    return isMcastEntry;
}

/**
 * Search for an unicast address table entry
 * @param pMacAdrs
 * @param vid
 * @return uint32
 */
static uint32 searchUnicastAdrsTablEntry(const uint8 *pMacAdrs,uint8 ethHwUnit,uint16 vid){
    uint32 foundTablId = ETH_GMAC_SW_TABL_ENTRY_UNKNOWN;
    Eth_AleTablValueType aleTablVal;
    uint32 tablEntry;

    for(vuint32_t i = 0; i < ETH_GMAC_SW_TABL_ENTRY_UNKNOWN ; i++){
        readTablEntry(&aleTablVal,i);
        tablEntry = ((aleTablVal.AleTablW1 & ETH_GMAC_SW_TABL_ENTRY1_TYPE_MASK)>>ETH_GMAC_SW_TABL_ENTRY1_TYPE_SHIFT);

         if((tablEntry == (uint32)ALE_ADRS_ENTRY) ||
            (tablEntry == (uint32)ALE_VLAN_ADRS_ENTRY)){
            if((compareEntryAddress(&aleTablVal,pMacAdrs) == E_OK) 	   &&
               (((aleTablVal.AleTablW1 & ETH_GMAC_SW_TABL_ENTRY1_VID_MASK) >> ETH_GMAC_SW_TABL_ENTRY1_VID_SHIFT) == vid) &&
               (((aleTablVal.AleTablW2 & ETH_GMAC_SW_TABL_ENTRY2_PORT_NUM_MASK) >> ETH_GMAC_SW_TABL_ENTRY2_PORT_NUM_SHIFT) == ethHwUnit)){
                foundTablId = i;
                break;
            }
         }
    }
    return foundTablId;
}

/**
 * Search for a multicast address table entry
 * @param pMacAdrs
 * @param vid
 * @return uint32
 */
static uint32 searchMulticastAdrsTablEntry(const uint8 *pMacAdrs,uint8 ethHwUnit,uint16 vid){
    uint32 foundTablId = ETH_GMAC_SW_TABL_ENTRY_UNKNOWN;
    Eth_AleTablValueType aleTablVal;
    uint32 tablEntry;
    uint8 hwUnitMask;

    for(vuint32_t i = 0; i < ETH_GMAC_SW_TABL_ENTRY_UNKNOWN ; i++){
        readTablEntry(&aleTablVal,i);
        tablEntry = ((aleTablVal.AleTablW1 & ETH_GMAC_SW_TABL_ENTRY1_TYPE_MASK)>>ETH_GMAC_SW_TABL_ENTRY1_TYPE_SHIFT);
        hwUnitMask = (aleTablVal.AleTablW2 & ETH_GMAC_SW_TABL_ENTRY2_PORT_NUM_MASK) >> ETH_GMAC_SW_TABL_ENTRY2_PORT_NUM_SHIFT;
         if((tablEntry == (uint32)ALE_ADRS_ENTRY) ||
            (tablEntry == (uint32)ALE_VLAN_ADRS_ENTRY)){
            if((compareEntryAddress(&aleTablVal,pMacAdrs) == E_OK) 	   &&
               (((aleTablVal.AleTablW1 & ETH_GMAC_SW_TABL_ENTRY1_VID_MASK) >> ETH_GMAC_SW_TABL_ENTRY1_VID_SHIFT) == vid) &&
               ((hwUnitMask & (1u << ethHwUnit)) != 0u) ){
                foundTablId = i;
                break;
            }
         }
    }
    return foundTablId;
}

/**
 * Search for a VLAN table entry
 * @param vid
 * @return uint32 - Table Id
 */
static uint32 searchVlanTablEntry(uint16 vid){
    uint32 foundTablId = ETH_GMAC_SW_TABL_ENTRY_UNKNOWN;
    Eth_AleTablValueType aleTablVal;
    uint32 tablEntry;

    for(vuint32_t i = 0; i < ETH_GMAC_SW_TABL_ENTRY_UNKNOWN ; i++){
        readTablEntry(&aleTablVal,i);
        tablEntry = ((aleTablVal.AleTablW1 & ETH_GMAC_SW_TABL_ENTRY1_TYPE_MASK)>>ETH_GMAC_SW_TABL_ENTRY1_TYPE_SHIFT);
        if((tablEntry == (uint32)ALE_VLAN_ENTRY) &&
           (((aleTablVal.AleTablW1 & ETH_GMAC_SW_TABL_ENTRY1_VID_MASK) >> ETH_GMAC_SW_TABL_ENTRY1_VID_SHIFT) == vid)){
            foundTablId = i;
            break;
        }
    }
    return foundTablId;
}

/**
 * Search for a free table entry
 * @param void
 * @return uint32 - Table Id
 */
static uint32 searchFreeTablEntry(void){
    uint32 foundTablId = ETH_GMAC_SW_TABL_ENTRY_UNKNOWN;
    Eth_AleTablValueType aleTablVal;
    uint32 tablEntry;

    for(vuint32_t i = 0; i < ETH_GMAC_SW_TABL_ENTRY_UNKNOWN ; i++){
        readTablEntry(&aleTablVal,i);
        tablEntry = ((aleTablVal.AleTablW1 & ETH_GMAC_SW_TABL_ENTRY1_TYPE_MASK)>>ETH_GMAC_SW_TABL_ENTRY1_TYPE_SHIFT);
        if(tablEntry == (uint32)ALE_FREE_ENTRY){
            foundTablId = i;
            break;
        }
    }
    return foundTablId;
}

/**
 * Delete unicast aged address entry from the ALE table starting from the beginning
 * @param none
 * @return uint32
 */
static uint32 deleteAgedTablEntry(void){
    uint32 foundTablId = ETH_GMAC_SW_TABL_ENTRY_UNKNOWN;
    Eth_AleTablValueType aleTablVal;
    uint32 tablEntry;

    for(vuint32_t i = 0; i < ETH_GMAC_SW_TABL_ENTRY_UNKNOWN ; i++){
        readTablEntry(&aleTablVal,i);
        tablEntry = ((aleTablVal.AleTablW1 & ETH_GMAC_SW_TABL_ENTRY1_TYPE_MASK)>>ETH_GMAC_SW_TABL_ENTRY1_TYPE_SHIFT);
        if(((uint32)ALE_ADRS_ENTRY      == tablEntry) ||
           ((uint32)ALE_VLAN_ADRS_ENTRY == tablEntry)){
            if( (uint32)ALE_UNI_ADRS_AGEABLE_NOT_TOUCHED == ((aleTablVal.AleTablW1 & ETH_GMAC_SW_TABL_ENTRY1_UNICAST_TYPE_MASK)>>ETH_GMAC_SW_TABL_ENTRY1_FWD_STATE_SHIFT)){
                aleTablVal.AleTablW1 &= ~ETH_GMAC_SW_TABL_ENTRY1_TYPE_MASK;
                aleTablVal.AleTablW1 |= ((uint32)ALE_FREE_ENTRY  << ETH_GMAC_SW_TABL_ENTRY1_TYPE_SHIFT);/*lint !e845 The right argument to operator '|' is certain to be 0  -- readability issue*/
                writeTablEntry(&aleTablVal,i);
                foundTablId = i;
                break;
            }
        }
    }
    return foundTablId;
}

/**
 * Get the Table id for the inserted address (not VLAN entry ) entry
 * @param pMacAdrs
 * @param vid
 * @return uint32
 */
static uint32 getTablId(const uint8 *pMacAdrs,uint16 vid){
    uint32 foundTablId;
    foundTablId = searchAdrsTablEntry(pMacAdrs,vid);
    if(foundTablId == ETH_GMAC_SW_TABL_ENTRY_UNKNOWN){ /* No double entry */
        foundTablId = searchFreeTablEntry();
        if(foundTablId == ETH_GMAC_SW_TABL_ENTRY_UNKNOWN){
            /* delete an aged & untouched entry */
            foundTablId = deleteAgedTablEntry();
        }
    }
    return foundTablId;
}

/**
 * Get the Table id for the inserted Unicast address (not VLAN entry ) entry
 * @param pMacAdrs
 * @param vid
 * @return uint32
 */
static uint32 getUniTablId(const uint8 *pMacAdrs,uint8 ethHwUnit,uint16 vid){
    uint32 foundTablId;
    foundTablId = searchUnicastAdrsTablEntry(pMacAdrs,ethHwUnit,vid);
    if(foundTablId == ETH_GMAC_SW_TABL_ENTRY_UNKNOWN){ /* No double entry */
        foundTablId = searchFreeTablEntry();
        if(foundTablId == ETH_GMAC_SW_TABL_ENTRY_UNKNOWN){
            /* delete an aged & untouched entry */
            foundTablId = deleteAgedTablEntry();
        }
    }
    return foundTablId;
}

/**
 * Remove the Multicast address entry in the ALE table
 * @param ethHwUnit
 * @param pMacAdrs
 * @param vid
 * @return Std_ReturnType
 */
static Std_ReturnType removeUnicastAdrsTablEntry(uint8 ethHwUnit,const uint8* pMacAdrs, uint16 vid){
    uint32 foundTablId;
    Eth_AleTablValueType aleTablVal = {0};
    Std_ReturnType ret = E_NOT_OK;
    foundTablId = searchUnicastAdrsTablEntry(pMacAdrs,ethHwUnit,vid);

    if(foundTablId != ETH_GMAC_SW_TABL_ENTRY_UNKNOWN){
        aleTablVal.AleTablW1 &= ~ETH_GMAC_SW_TABL_ENTRY1_TYPE_MASK;
        aleTablVal.AleTablW1 |= ((uint32)ALE_FREE_ENTRY << ETH_GMAC_SW_TABL_ENTRY1_TYPE_SHIFT);/*lint !e845 The right argument to operator '|' is certain to be 0  -- readability issue*/
        writeTablEntry(&aleTablVal,foundTablId);
        ret = E_OK;
    }
    return ret;
}

/**
 * Remove the Multicast address entry in the ALE table
 * @param ethHwUnit
 * @param pMacAdrs
 * @param vid
 * @return Std_ReturnType
 */
static Std_ReturnType removeMulticastAdrsTablEntry(uint8 ethHwUnit,const uint8* pMacAdrs, uint16 vid){
    uint32 foundTablId;
    Std_ReturnType ret = E_NOT_OK;
    foundTablId = searchMulticastAdrsTablEntry(pMacAdrs,ethHwUnit,vid);

    if(foundTablId != ETH_GMAC_SW_TABL_ENTRY_UNKNOWN){
        uint8 hwUnitMask;
        Eth_AleTablValueType aleTablVal = {0};
        readTablEntry(&aleTablVal,foundTablId);
        hwUnitMask = (aleTablVal.AleTablW2 & ETH_GMAC_SW_TABL_ENTRY2_PORT_NUM_MASK) >> ETH_GMAC_SW_TABL_ENTRY2_PORT_NUM_SHIFT;
        if(hwUnitMask == 0u){
            aleTablVal.AleTablW1 &= ~ETH_GMAC_SW_TABL_ENTRY1_TYPE_MASK;
            aleTablVal.AleTablW1 |= ((uint32)ALE_FREE_ENTRY << ETH_GMAC_SW_TABL_ENTRY1_TYPE_SHIFT);/*lint !e845 The right argument to operator '|' is certain to be 0  -- readability issue*/
        }else{
            hwUnitMask &= (~((uint32)1u << ethHwUnit));
            aleTablVal.AleTablW2 |=  (uint32)(hwUnitMask) << ETH_GMAC_SW_TABL_ENTRY2_PORT_NUM_SHIFT;
        }
        writeTablEntry(&aleTablVal,foundTablId);
        ret = E_OK;
    }
    return ret;
}

/**
 * Insert a unicast address entry in the ALE table
 * @param ethHwUnit
 * @param pMacAdrs
 * @param vid
 * @return Std_ReturnType
 */
static Std_ReturnType addUnicastAdrsTablEntry(uint8 ethHwUnit,const uint8* pMacAdrs, uint16 vid){
    uint32 tablId;
    Eth_AleTablValueType aleTablVal;
    Std_ReturnType ret = E_NOT_OK;
    (void)removeUnicastAdrsTablEntry(ethHwUnit,pMacAdrs,vid);
    tablId = getUniTablId(pMacAdrs,ethHwUnit,vid);
    readTablEntry(&aleTablVal,tablId);
    if(tablId != ETH_GMAC_SW_TABL_ENTRY_UNKNOWN){
        for (uint8 i = 0u; i < ETH_MAC_ADDR_SIZE; i++)	{
            *(((uint8 *) &aleTablVal)+i) = pMacAdrs[5-i]; /*lint !e928 !e9016 */ /*  Intentional cast from pointer to pointer ,pointer arithmetic other than array indexing used*/
        }

        aleTablVal.AleTablW1 &= ~ETH_GMAC_SW_TABL_ENTRY1_VID_MASK;
        aleTablVal.AleTablW1 |= ((uint32)vid << ETH_GMAC_SW_TABL_ENTRY1_VID_SHIFT);
        aleTablVal.AleTablW1 &= ~ETH_GMAC_SW_TABL_ENTRY1_TYPE_MASK;
        if(vid != 0){
            aleTablVal.AleTablW1 |= ((uint32)ALE_VLAN_ADRS_ENTRY << ETH_GMAC_SW_TABL_ENTRY1_TYPE_SHIFT);
        }else{
            aleTablVal.AleTablW1 |= ((uint32)ALE_ADRS_ENTRY  << ETH_GMAC_SW_TABL_ENTRY1_TYPE_SHIFT);
        }
        aleTablVal.AleTablW1 &= ~ETH_GMAC_SW_TABL_ENTRY1_UNICAST_TYPE_MASK;
        aleTablVal.AleTablW1 |= ((uint32)ALE_UNI_ADRS_NOT_AGEABLE << ETH_GMAC_SW_TABL_ENTRY1_FWD_STATE_SHIFT);/*lint !e845 The right argument to operator '|' is certain to be 0  -- readability issue*/

        /* Port state should be forwarding state cus of secure and block reset */
        aleTablVal.AleTablW2 &= ~ETH_GMAC_SW_TABL_ENTRY2_SECURE; /* Do not care PORT number of the matched source address */
        aleTablVal.AleTablW2 &= ~ETH_GMAC_SW_TABL_ENTRY2_BLOCK;  /* No blockage */

        aleTablVal.AleTablW2 &= ~ETH_GMAC_SW_TABL_ENTRY2_PORT_NUM_MASK;
        aleTablVal.AleTablW2 |= ((uint32)ethHwUnit << ETH_GMAC_SW_TABL_ENTRY2_PORT_NUM_SHIFT); /* Port number - Not a Port mask */

        writeTablEntry(&aleTablVal,tablId);
        ret = E_OK;
    }
    return ret;
}


/**
 * Insert a Multicast address entry in the ALE table
 * @param ethHwUnit
 * @param pMacAdrs
 * @param vid
 * @return Std_ReturnType
 */
static Std_ReturnType addMulticastAdrsTablEntry(uint8 ethHwUnit,const uint8* pMacAdrs,uint16 vid){
    uint32 tablId;
    Eth_AleTablValueType aleTablVal;
    Std_ReturnType ret = E_NOT_OK;

    tablId = getTablId(pMacAdrs,vid);
    readTablEntry(&aleTablVal,tablId);
    if(tablId != ETH_GMAC_SW_TABL_ENTRY_UNKNOWN){
        for (uint8 i = 0u; i < ETH_MAC_ADDR_SIZE; i++)	{
            *(((uint8 *) &aleTablVal)+i) = pMacAdrs[5-i]; /*lint !e928, !e9016 */ /*  Intentional cast from pointer to pointer,pointer arithmetic other than array indexing used */
        }
        aleTablVal.AleTablW1 &= ~ETH_GMAC_SW_TABL_ENTRY1_VID_MASK;
        aleTablVal.AleTablW1 |= ((uint32)vid << ETH_GMAC_SW_TABL_ENTRY1_VID_SHIFT);
        aleTablVal.AleTablW1 &= ~ETH_GMAC_SW_TABL_ENTRY1_TYPE_MASK;
        if(vid != 0u){
            aleTablVal.AleTablW1 |= ((uint32)ALE_VLAN_ADRS_ENTRY << ETH_GMAC_SW_TABL_ENTRY1_TYPE_SHIFT);
        }else{
            aleTablVal.AleTablW1 |= ((uint32)ALE_ADRS_ENTRY  << ETH_GMAC_SW_TABL_ENTRY1_TYPE_SHIFT);
        }

        aleTablVal.AleTablW1 &= ~ETH_GMAC_SW_TABL_ENTRY1_MCAST_FWD_STATE_MASK;
        aleTablVal.AleTablW1 |= ((uint32)ETH_GMAC_MCAST_FWD_STATE_FORWARDING << ETH_GMAC_SW_TABL_ENTRY1_FWD_STATE_SHIFT);

        aleTablVal.AleTablW2 |= ETH_GMAC_SW_TABL_ENTRY2_SUPER; /* used in auth mode, OUI deny mode ... */
        aleTablVal.AleTablW2 |=  ((uint32)1u << ethHwUnit) << ETH_GMAC_SW_TABL_ENTRY2_PORT_NUM_SHIFT; /* Port mask not a port number */

        writeTablEntry(&aleTablVal,tablId);
        ret = E_OK;
    }
    return ret;
}


/**
 * Insert a VLAN entry in the ALE table
 * @param ethHwUnit
 * @param vid
 * @return Std_ReturnType
 */
static Std_ReturnType addVlanTablEntry(uint8 ethHwUnit,uint16 vid){
    uint32 TablId;
    Eth_AleTablValueType aleTablVal;
    Std_ReturnType ret = E_NOT_OK;
    TablId = searchVlanTablEntry(vid);
    if(TablId == ETH_GMAC_SW_TABL_ENTRY_UNKNOWN){ /* No double entry */
        TablId = searchFreeTablEntry();
        if(TablId == ETH_GMAC_SW_TABL_ENTRY_UNKNOWN){
            /* delete an aged & untouched entry */
            TablId = deleteAgedTablEntry();
        }
    }

    if(TablId != ETH_GMAC_SW_TABL_ENTRY_UNKNOWN){

        readTablEntry(&aleTablVal,TablId);

        aleTablVal.AleTablW0 |= ((uint32)1u << ethHwUnit); /* 3 bit filed */
        /* clear the flood masks */
        aleTablVal.AleTablW0 &= ~(((uint32)1u << ethHwUnit) << ETH_GMAC_SW_VLAN_TABL_UNREG_MCAST_FLOOD_SHIFT);
        aleTablVal.AleTablW0 &= ~(((uint32)1u << ethHwUnit) << ETH_GMAC_SW_VLAN_TABL_REG_MCAST_FLOOD_SHIFT);
#if 0  /* kept for future purpose.. the packet VLAN tag to be removed on switch egress */
        aleTablVal.AleTablW0 |= (((uint32)1u << ethHwUnit) << ETH_GMAC_SW_VLAN_TABL_FORCE_UNTAGGED_EGRESS_SHIFT);
#endif
        aleTablVal.AleTablW1 &= ~ETH_GMAC_SW_TABL_ENTRY1_VID_MASK;
        aleTablVal.AleTablW1 |= ((uint32)vid << ETH_GMAC_SW_TABL_ENTRY1_VID_SHIFT);

        aleTablVal.AleTablW1 &= ~ETH_GMAC_SW_TABL_ENTRY1_TYPE_MASK;
        aleTablVal.AleTablW1 |= ((uint32)ALE_VLAN_ENTRY  << ETH_GMAC_SW_TABL_ENTRY1_TYPE_SHIFT);

        writeTablEntry(&aleTablVal,TablId);

        ret = E_OK;
    }
    return ret;
}

/**
 * Configure unicast address entry and set fifo priority mode
 * @param ethHwUnit
 * @param pMacAdrs
 * @param tci
 * @return Std_ReturnType
 */
static Std_ReturnType configureALETabl(uint8 ctrlIdx,uint8 ethHwUnit,const uint8* pMacAdrs){
    Std_ReturnType ret =  E_OK;
    ret |= addUnicastAdrsTablEntry(ethHwUnit,pMacAdrs,0u);
    ret |= addUnicastAdrsTablEntry(0,pMacAdrs,0u);
    pHwPtr->PORT0.TX_IN_CTL &= ~ETH_GMAC_SW_ALE_PORTX_TX_IN_CTL_SEL_MASK;
    if(EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwFifoPrio == (uint8)FIFO_DUAL_MAC){ /*  Dual mac mode */
        /* Select the dual mac FIFO mode on the port 0 */
        pHwPtr->PORT0.TX_IN_CTL |= ((uint32)ETH_GMAC_SW_ALE_DUAL_MAC_MODE << ETH_GMAC_SW_ALE_MODE_SHIFT);
    }else if(EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwFifoPrio == (uint8)FIFO_NORMAL_PRIO){
        pHwPtr->PORT0.TX_IN_CTL |=  ((uint32)ETH_GMAC_SW_ALE_NORMAL_PRIO_MODE << ETH_GMAC_SW_ALE_MODE_SHIFT); /*lint !e845 The right argument to operator '|' is certain to be 0  -- readability issue*/
    }else{
         ret =  E_NOT_OK;
        /* Do nothing */
    }
    return ret;
}


/**
 * Configure TCI / VLAN entries and vlan unicast address entry
 * @param ethHwUnit
 * @param pMacAdrs
 * @param tci
 * @return Std_ReturnType
 */
static Std_ReturnType configureTCI(uint8 ethHwUnit,const uint8* pMacAdrs,uint16 tci){
    Std_ReturnType ret =  E_OK;
    uint16 vid =  ( tci & (uint16)ETH_GMAC_SW_PORT_VID_MASK);
    uint8 prio =  ((tci & (uint16)ETH_GMAC_SW_PORT_PRI_MASK) >> ETH_GMAC_SW_PORT_PRI_SHIFT);
    uint8 cfi  =  ((tci & (uint16)ETH_GMAC_SW_PORT_CFI_MASK) >> ETH_GMAC_SW_PORT_CFI_SHIFT);
    ret |= addUnicastAdrsTablEntry(ethHwUnit,pMacAdrs,vid);
    ret |= addUnicastAdrsTablEntry(0,pMacAdrs,vid);    
    pHwPtr->ALE.ALE_CONTROL |= ETH_GMAC_SW_ALE_VLAN_AWARE; /* VLAN aware mode - common setting for all ports */
    /* Add CPSW_3G VLAN aware bit/VLAN_AWARE in CPSW_CONTROL also if if VLAN's are to exit the switch as well */
    /* Packets from the host (port 0) to ports 1 and 2 should be directed. If directed packets are not desired
    then VLAN with addresses can be added for both destination ports. */
    pHwPtr->SS.CPSW_CONTROL |= ETH_GMAC_SW_VLAN_AWARE;
    if(ethHwUnit == GMAC_SW_PORT1){
        /* VID -   number other than 0x000 and 0xFFF */
        pHwPtr->PORT1.PORT_VLAN &= ~ETH_GMAC_SW_PORT_PRI_MASK;
        pHwPtr->PORT1.PORT_VLAN |= ((uint32)prio << ETH_GMAC_SW_PORT_PRI_SHIFT); /* VLAN prio*/
        pHwPtr->PORT1.PORT_VLAN &= ~ETH_GMAC_SW_PORT_CFI_MASK;
        pHwPtr->PORT1.PORT_VLAN |= ((uint32)cfi << ETH_GMAC_SW_PORT_CFI_SHIFT); /* Canonical Format Identifier*/
        pHwPtr->PORT1.PORT_VLAN &= ~ETH_GMAC_SW_PORT_VID_MASK;
        pHwPtr->PORT1.PORT_VLAN |=  vid;
    }else{
        /* VID -   number other than 0x000 and 0xFFF */
        pHwPtr->PORT2.PORT_VLAN &= ~ETH_GMAC_SW_PORT_PRI_MASK;
        pHwPtr->PORT2.PORT_VLAN |= ((uint32)prio << ETH_GMAC_SW_PORT_PRI_SHIFT);  /* VLAN prio*/
        pHwPtr->PORT2.PORT_VLAN &= ~ETH_GMAC_SW_PORT_CFI_MASK;
        pHwPtr->PORT2.PORT_VLAN |= ((uint32)cfi << ETH_GMAC_SW_PORT_CFI_SHIFT); /* Canonical Format Identifier*/
        pHwPtr->PORT2.PORT_VLAN &= ~ETH_GMAC_SW_PORT_VID_MASK;
        pHwPtr->PORT2.PORT_VLAN |=  vid;
    }
    /* Add VLAN Table entries for Ports */
    ret |= addVlanTablEntry(ethHwUnit,vid);
    ret |= addVlanTablEntry(0,        vid);

    return ret;
}

/**
 * Configures common ALE
 * @param none
  * @return none
 */
static void configureCommonALE(void){
    /*Enable ALE*/
    pHwPtr->ALE.ALE_CONTROL |= ETH_GMAC_SW_ALE_ENABLE;
    /* Clear ALE address table */
#if (ETH_HW_SOFT_RESET == STD_ON)
    pHwPtr->ALE.ALE_CONTROL |= ETH_GMAC_SW_ALE_CLEAR_TABLE;
    while((pHwPtr->ALE.ALE_CONTROL & ETH_GMAC_SW_ALE_CLEAR_TABLE) ==  ETH_GMAC_SW_ALE_CLEAR_TABLE){};
#endif

    /* Each Port is enabled for learning an address by default */

    /* Set Port to forwading state in Address lookup engine port X control register*/
    pHwPtr->ALE.ALE_PORTCTL0 &= ~ETH_GMAC_SW_ALE_PORT_STATE_MASK;
    pHwPtr->ALE.ALE_PORTCTL0 |= ETH_GMAC_SW_ALE_PORT_STATE_FORWARD;

}

/**
 * Configures Address LookUp Engine
 * @param ethHwUnit
 * @param pMacAdrs
 * @return Std_ReturnType
 */
static Std_ReturnType configureALE(uint8 ctrlIdx,uint8 ethHwUnit,const uint8* pMacAdrs){
    Std_ReturnType ret;

    /* Each Port is enabled for learning an address by default */

    if(ethHwUnit == GMAC_SW_PORT1) {/* by default it is in disabled state */

        pHwPtr->ALE.ALE_PORTCTL1  &= ~ETH_GMAC_SW_ALE_PORT_STATE_MASK;
        pHwPtr->ALE.ALE_PORTCTL1  |= ETH_GMAC_SW_ALE_PORT_STATE_FORWARD;
#if 0 /* defined(CFG_ETH_HW_SHARE) */
        pHwPtr->ALE.ALE_PORTCTL1  |= ETH_GMAC_SW_ALE_PORT_DROP_UNTAGGED;
#endif
    }
    if(ethHwUnit == GMAC_SW_PORT2){/* by default it is in disabled state */

        pHwPtr->ALE.ALE_PORTCTL2  &= ~ETH_GMAC_SW_ALE_PORT_STATE_MASK;
        pHwPtr->ALE.ALE_PORTCTL2  |= ETH_GMAC_SW_ALE_PORT_STATE_FORWARD;
#if 0 /* defined(CFG_ETH_HW_SHARE) */
        pHwPtr->ALE.ALE_PORTCTL2  |= ETH_GMAC_SW_ALE_PORT_DROP_UNTAGGED;
#endif
    }
    ret = configureALETabl(ctrlIdx,ethHwUnit,pMacAdrs);

    return ret;
}


/**
 * Configures MII /RMII /GMII /RGMII interfaces of the PORT according to user settings
 * @param ethMIIMode
 * @param ethHwUnit
 * @return none
 */
static void configureGMIIInterface(uint8 ethMIIMode,uint8 ethHwUnit){

    uint32 Val = READ_REG_32( CTRL_MODULE_CORE + CTRL_CORE_MMR_LOCK_1);

    WRITE_REG_32((CTRL_MODULE_CORE + CTRL_CORE_MMR_LOCK_1),MMR_UNLOCK_1);

    /* 0x0: GMII/MII,0x1: RMII,0x2: RGMII */
    if(ethHwUnit == GMAC_SW_PORT1){
        WRITE_READ_REG_32((CTRL_MODULE_CORE+CTRL_CORE_CONTROL_IO_1),
                GMII1_SEL_MASK, ethMIIMode);
    }else{
        WRITE_READ_REG_32((CTRL_MODULE_CORE+CTRL_CORE_CONTROL_IO_1),
                GMII2_SEL_MASK, ((uint32)ethMIIMode << GMII2_SEL_SHIFT));
    }
    WRITE_REG_32((CTRL_MODULE_CORE + CTRL_CORE_MMR_LOCK_1),MMR_LOCK_1);

    WRITE_REG_32((CTRL_MODULE_CORE + CTRL_CORE_MMR_LOCK_1),Val);
}

/**
 * Configures the Eth controller
 * @param pCfgPtr
 * @return E_OK: Configuration successful, E_NOT_OK: Configuration failed
 */
static Std_ReturnType configureController( const Eth_ControllerConfigType *pCfgPtr) {
    uint32 val;
    uint8 ethHwPort = pCfgPtr->EthHwUnit;

    if( configureALE(pCfgPtr->EthCtrlIdx,ethHwPort,pCfgPtr->EthCtrlPhyAddress) != E_OK){
        DET_REPORT_ERROR(ETH_GLOBAL_ID, ETH_E_GENERAL_ERROR);
    }
    /* Tx Priority mapping to the queue */
#if !defined(CFG_ETH_HW_SHARE)
    for(uint8 i = 0u; i <= ETH_GMAC_SW_PORT_MAX_PRI_VAL; i++){
        if(pCfgPtr->EthHwUnit == GMAC_SW_PORT1){
        	WRITE_READ_REG_32((uint32)(&pHwPtr->PORT1.TX_PRI_MAP),
							  (ETH_GMAC_SW_QUEUE_PRIORITY_MASK << (ETH_GMAC_SW_QUEUE_PRIORITY_SHIFT * i) ),
							  (pCfgPtr->EthHwTxQueue << (ETH_GMAC_SW_QUEUE_PRIORITY_SHIFT * i)));
        }else{
        	WRITE_READ_REG_32((uint32)(&pHwPtr->PORT2.TX_PRI_MAP),
							  (ETH_GMAC_SW_QUEUE_PRIORITY_MASK << (ETH_GMAC_SW_QUEUE_PRIORITY_SHIFT * i) ),
							  (pCfgPtr->EthHwTxQueue << (ETH_GMAC_SW_QUEUE_PRIORITY_SHIFT * i)));
        }
    }
#else
    if(EthHwPvtConfig.vConfigureTxQueue != NULL){
    	EthHwPvtConfig.vConfigureTxQueue(ethHwPort,pCfgPtr->EthHwTxQueue);
        }
#endif
#if !defined(CFG_ETH_HW_SHARE)
    for(uint8 i = 0u; i <= ETH_GMAC_SW_PORT_MAX_PRI_VAL; i++){
    	WRITE_READ_REG_32((uint32)(&pHwPtr->PORT0.TX_PRI_MAP),
						  (ETH_GMAC_SW_QUEUE_PRIORITY_MASK << (ETH_GMAC_SW_QUEUE_PRIORITY_SHIFT * i) ),
						  (pCfgPtr->EthHwRxQueue << (ETH_GMAC_SW_QUEUE_PRIORITY_SHIFT * i)));
    }
    /* Switch Priority queue mapping to the RX DMA channel */
    if(pCfgPtr->EthHwUnit == GMAC_SW_PORT1){
        pHwPtr->PORT0.CPDMA_RX_CH_MAP |= ((uint32)pCfgPtr->EthHwRxDmaCh << (ETH_GMAC_SW_CPDMA_CHANNEL_MAP_SHIFT * pCfgPtr->EthHwRxQueue));
    }else{
        pHwPtr->PORT0.CPDMA_RX_CH_MAP |= ((uint32)pCfgPtr->EthHwRxDmaCh << ((ETH_GMAC_SW_CPDMA_CHANNEL_MAP_PORT2_SHIFT + ETH_GMAC_SW_CPDMA_CHANNEL_MAP_SHIFT) * pCfgPtr->EthHwRxQueue));
    }
#else
    if(EthHwPvtConfig.vConfigureRxQueue != NULL){
    	EthHwPvtConfig.vConfigureRxQueue(ethHwPort,pCfgPtr->EthHwRxQueue,pCfgPtr->EthHwRxDmaCh);
    }
#endif

    configureGMIIInterface(pCfgPtr->EthMIIMode, ethHwPort);

#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
    if (TRUE == pCfgPtr->EthCtrlEnableRxInterrupt){
        ISR_INSTALL_ISR2("GMAC_SW_RX", Eth_RxIrqHdlr, GMAC_SW_IRQ_RX_PULSE, ETH_ISR_PRIORITY, 0 );
        ISR_INSTALL_ISR2("GMAC_SW_RX_THRESH", Eth_RxIrqHdlr, GMAC_SW_IRQ_RX_THRESH_PULSE, ETH_ISR_PRIORITY, 0 );
    }
    if(TRUE == pCfgPtr->EthCtrlEnableTxInterrupt) {
       ISR_INSTALL_ISR2("GMAC_SW_TX", Eth_TxIrqHdlr, GMAC_SW_IRQ_TX_PULSE, ETH_ISR_PRIORITY, 0 );
    }
#if defined(CFG_ETH_TEST)
    ISR_INSTALL_ISR2("GMAC_SW_MISC", Eth_MiscIrqHdlr, GMAC_SW_IRQ_MISC_PULSE, ETH_ISR_PRIORITY, 0 );
#endif
#endif

    /* Configure MAC address */
    configureMacAdrs(pCfgPtr->EthHwUnit, pCfgPtr->EthCtrlPhyAddress);

    /* @req 4.2.2/SWS_Eth_00146 *//* Hardware filtering is available and hence there is no promiscous mode set */
    if(ethHwPort == GMAC_SW_PORT1){
        /* 1518 bytes default - SR max is 1522 ( 4 bytes for crc) */
        pHwPtr->SL1.SL_RX_MAXLEN |= (ETH_GMAC_SW_SL_RX_MAXLEN_MASK & (uint32)pCfgPtr->EthCtrlRxBufLenByte);
    }else{
        /* 1518 bytes default - SR max is 1522 ( 4 bytes for crc) */
        pHwPtr->SL2.SL_RX_MAXLEN |= (ETH_GMAC_SW_SL_RX_MAXLEN_MASK & (uint32)pCfgPtr->EthCtrlRxBufLenByte);
    }

    /* IMPROVEMENT - To be added when statistics data is required ASR 4.2.1 */
    /*FIFO overruns (SOFOVERRUNS) are the only port 0 statistics that are enabled to be kept */
    /* pHwPtr->SS->CPSW_STAT_PORT_EN |= (GMAC_SW_SPSW_P0_STAT_EN | GMAC_SW_SPSW_P1_STAT_EN | GMAC_SW_SPSW_P2_STAT_EN); */

    val = 0uL;
    /* If PASSCONTROL is set, enables control frames */
    /*	val |= ETH_GMAC_SW_SL_MACCTRL_RX_CMF_EN;  */

    /* enable passing error frames */
    /*	val |= (ETH_GMAC_SW_SL_MACCTRL_RX_CSF_EN | ETH_GMAC_SW_SL_MACCTRL_RX_CEF_EN); */

    /* limits the number of short gap packets transmitted to 100ppm */
    val |= ETH_GMAC_SW_SL_MACCTRL_TX_SHORT_GAP_LIM_EN;

    /* Transmit Pacing Enabled - Adaptive Performance Optimization - reducing collisions */
    val |= ETH_GMAC_SW_SL_MACCTRL_TX_PACE;

    /* Switch ingress / Transmit Flow Control Enable in Full-duplex mode -
    Determines if Incoming pause frames are acted upon. */
    val |= ETH_GMAC_SW_SL_MACCTRL_TX_FLOW_EN;

    /* FLow control for Switch ingress / CPPI receive operations
     * ( CPPI -> external memory ==> transmit ) is enabled by default */
    /* Switch egress / Receive Flow Control Enabled:
     *  Half-Dup mode - Collisions are initiated when ON:
     *  Full-Dup mode - Outgoing pause frames are sent when ON */
    val |= ETH_GMAC_SW_SL_MACCTRL_RX_FLOW_EN;

    /* don't put it in idle mode - use it mode change for future */
    /*  val |= ETH_GMAC_SW_SL_MACCTRL_CMD_IDLE; */

    /* Loopback mode: forces internal fullduplex mode regardless of whether the FULLDUPLEX bit is set or not.
      Note : The LOOPBACK bit should be changed  only when GMII_EN is de asserted */
#if defined(CFG_ETH_LOOPBACK)
    val |= ETH_GMAC_SW_SL_MACCTRL_LOOPBACK;
#endif
    val &= ~ETH_GMAC_SW_SL_MACCTRL_GIG;
    val &= ~ETH_GMAC_SW_SL_MACCTRL_GIG_FORCE;
    if(pCfgPtr->EthHwSpeed == MBPS_10){
        /* 0 - 10MBPS  */
        val &= ~ETH_GMAC_SW_SL_MACCTRL_IFCTL_A;
        /* 0 - 10MBPS says non functional */
        /* val &= ~ETH_GMAC_SW_SL_MACCTRL_IFCTL_B; */

    }else if(pCfgPtr->EthHwSpeed == MBPS_100){
        /*  1 - 100MBPS */
        val |= ETH_GMAC_SW_SL_MACCTRL_IFCTL_A;
         /* 1 - 100MBPS says non functional */
        /* val|= ETH_GMAC_SW_SL_MACCTRL_IFCTL_B; */
    }else{
        /* 1000MBPS */
        val |= ETH_GMAC_SW_SL_MACCTRL_GIG;
        val |= ETH_GMAC_SW_SL_MACCTRL_GIG_FORCE;
    }
    /* Enable Full duplex mode */
    val |= ETH_GMAC_SW_SL_MACCTRL_FULLDUPLEX;

    if(ethHwPort == GMAC_SW_PORT1){
        pHwPtr->SL1.SL_MACCONTROL |= val;
    }else{
        pHwPtr->SL2.SL_MACCONTROL |= val;
    }
    /* RGMII inband operation and also set phy for the same */
    /* val = ETH_GMAC_SW_SL_MACCTRL_EXT_EN;  */

    /* GMII RX and TX released from reset */
    /* IFCTL_A is set only for RMII why not also for MII and RGMII ?? */
    val = ETH_GMAC_SW_SL_MACCTRL_GMII_EN;

    if(ethHwPort == GMAC_SW_PORT1){
        pHwPtr->SL1.SL_MACCONTROL |= val;
    }else{
        pHwPtr->SL2.SL_MACCONTROL |= val;
    }

#if defined(CFG_ETH_HW_SHARE)
    if(EthHwPvtConfig.vConfigureControllerExtra != NULL){
      	EthHwPvtConfig.vConfigureControllerExtra(ethHwPort);
      }
#endif


#if defined(CFG_ETH_HW_SHARE)  /* No support for multiple EthIf configured vlans */
    if(EthHwPvtConfig.vGetConfiguredVid != NULL){
		if(E_OK != configureTCI(ethHwPort,pCfgPtr->EthCtrlPhyAddress,EthHwPvtConfig.vGetConfiguredVid(ethHwPort))){
			 return E_NOT_OK ;
		}
    }
#endif
    return (Std_ReturnType)E_OK;
}

/**
 * Inserts Ethernet header in a data buffer
 * @param pCtrlCfg
 * @param pPhysAddr
 * @param pData
 * @param FrameType
 * @return void
 */
static void insertEthHeader(const Eth_ControllerConfigType *pCtrlCfg,
        const uint8* pPhysAddr, uint8* pData, Eth_FrameType frameType) {
    uint8 i;
    /* Dest MAC */
    for (i=0u; i < ETH_MAC_ADDR_SIZE; i++){
        pData[ETH_MAC_DST_ADDR_START_INDEX+i] =  pPhysAddr[i];
    }
    /* Src MAC */
    for (i=0u; i < ETH_MAC_ADDR_SIZE; i++){
        pData[ETH_MAC_SRC_ADDR_START_INDEX+i] =  pCtrlCfg->EthCtrlPhyAddress[i];
    }
    /* Ethernet type */
    pData[ETH_ETHERNETTYPE_START_INDEX] = (uint8) ((frameType
            >> ETH_SHIFT_BYTE1) & ETH_BYTE_MASK);
    pData[ETH_ETHERNETTYPE_START_INDEX + 1] = (uint8) (frameType & ETH_BYTE_MASK);
}

#if !defined(CFG_ETH_HW_SHARE)
/**
 * Check if data has been received
 * @param ctrlIdx
 * @return Eth_RxStatusType
 */
static Eth_RxStatusType isRxDatAvailable(uint8 ctrlIdx) {
    const volatile EthDescType *pEthRxDesc = EthCtrlUnit[ctrlIdx].pEthRxDescChain->pDescHead; /* Just read from the Head */
    Eth_RxStatusType rxStatus = ETH_NOT_RECEIVED;
    for (vuint32_t i = 0; i < EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthRxBufTotal; i++) {
        if ((pEthRxDesc[i].PktFlgLen & ETH_GMAC_SW_DSC_FLAG_OWNER ) == 0u) {
            rxStatus = ETH_RECEIVED_MORE_DATA_AVAILABLE;
            break;
        }
    }
    return rxStatus;
}
#endif

#if defined(CFG_ETH_HW_SHARE)
/**
 * Verify if last/all TX transfer is done and acknowledged by HOST software to proceed
 * @param EthCtrlIdx
 * @return boolean
 */
static boolean checktTxDescFree(uint8 EthCtrlIdx){
    for (uint32 txBufIdx = 0; txBufIdx <  EthCtrlUnit[EthCtrlIdx].pEthcfgPtr->EthTxBufTotal; txBufIdx++) {
        if((EthCtrlUnit[EthCtrlIdx].EthTxDescStatus[txBufIdx].TxState != ETH_TX_DESC_IDLE)){
            return FALSE;
        }
    }
  return TRUE;
}
#endif

/* ========================================================================== */
/*                           HW APIs                                          */
/* ========================================================================== */
/**
 * Initializes Ethernet HW modules configured
 * @param CfgPtr
 * @return none
 */
Std_ReturnType Eth_Hw_Init(const Eth_ConfigType* CfgPtr) {
	Std_ReturnType ret = E_OK;
	if(CfgPtr != NULL){
#if defined(CFG_ETH_HW_SHARE)
		/*
		 *
		 * Note: Call Eth_Init/Eth_Hw_Init from non-pre emptable first task or before OS startup
		 *
		 * And Spin lock used here is application specific just to synchronize initialization sequence across CPUs
		 * may take the critical section beyond 200 micro secs and
		 * hence deprecated to use it in this way
		 *
		 * It's an HW binary sem..does not cares about the initiator or the process which locked it
		 *
		 *  */
#if 0   /* Ideal case */
		/* Disable interrupts before checking lock status , enable interrupts back if it is taken already and
		 *  do this process in a loop the same    */
		while( (READ_REG_32((uint32)(SPIN_LOCK_REG(HW_M4_AUTOSAR_TO_AVB_ETH)))) ==  SPIN_LOCK_TAKEN ){};/* Atomic operation */
#endif
		uint32 hwLock;
		hwLock = READ_REG_32((uint32)(SPIN_LOCK_REG(HW_M4_AUTOSAR_TO_AVB_ETH))); /* Atomic operation */
		/* Note - different operation here - No spinning in case if spinlock is taken already
		 * It is expected that the Bootloader to consume the spinlock prior to this and do not free it */
		(void)hwLock;
#endif
#if (ETH_HW_SOFT_RESET == STD_ON)
        /* reset mode */
        reset();
#endif
        configureMDIO();

#if defined(CFG_ETH_FIFO_LOOPBACK)
        pHwPtr->SS.CPSW_CONTROL |= ETH_GMAC_SW_FIFO_LOOPBACK; /* Note: Port 0 receive is fixed on channel zero. */
#else
        pHwPtr->SS.CPSW_CONTROL &= ~ETH_GMAC_SW_FIFO_LOOPBACK;
#endif
        configureCommonALE();

		for (uint8 ctrlIdx = 0u;ctrlIdx < ETH_NOF_CONFIG_CTRL; ctrlIdx++){
        	EthCtrlUnit[CfgPtr->ConfigSet->Controllers[ctrlIdx].EthCtrlIdx].pEthcfgPtr = &CfgPtr->ConfigSet->Controllers[ctrlIdx];
        	EthCtrlUnit[CfgPtr->ConfigSet->Controllers[ctrlIdx].EthCtrlIdx].EthMaxRxBufLen = EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthCtrlRxBufLenByte + \
        			                                         (EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthCtrlRxBufLenByte % (uint32)ETH_BUF_ALIGNING_BYTES);
			ret |= Eth_Hw_ControllerInit(&CfgPtr->ConfigSet->Controllers[ctrlIdx],CfgPtr->ConfigSet->Controllers[ctrlIdx].EthCtrlIdx);
		}
#if defined(CFG_ETH_HW_SHARE)
		WRITE_REG_32((uint32)(SPIN_LOCK_REG(HW_M4_AUTOSAR_TO_AVB_ETH)), SPIN_LOCK_FREE); /* Free it - No atomic but not desired */
		/* Enable interrupts - Ideal - here not required  */
#endif
		for (uint8 ctrlIdx = 0u;ctrlIdx < ETH_NOF_CONFIG_CTRL; ctrlIdx++){
			/* Configure descriptors */
		    configureDesc(&CfgPtr->ConfigSet->Controllers[ctrlIdx]);
		    /* Initialize buffer runtime data */
		    initBuffers(&CfgPtr->ConfigSet->Controllers[ctrlIdx],CfgPtr->ConfigSet->Controllers[ctrlIdx].EthCtrlIdx);
		}
	}else{
		ret = E_NOT_OK;
	}
	return ret;
}

/**
 * Initializes an Ethernet controller
 * @param CtrlCfgPtr
 * @param CtrlIdx
 * @return E_OK: Initialization OK, E_NOT_OK: Initialization failed
 */
Std_ReturnType Eth_Hw_ControllerInit(const Eth_ControllerConfigType *CtrlCfgPtr,
        uint8 CtrlIdx) {
    /*
     * 1: Disable the controller
     * 2: Clear pending Ethernet interrupts
     * 3: Configure all controller configuration parameters (e.g. interrupts, frame length, frame filter, ...)
     * 4: Configure all transmit / receive resources (e.g. buffer initialization)
     * 5: delete all pending transmit and receive requests
     *
     */
    VALIDATE_HW_RV(CtrlCfgPtr->EthHwUnit, ETH_GLOBAL_ID, ETH_E_CONFIG_INVALID,
            E_NOT_OK);

    /* no config mode */

    /* Disable controller */
    if (E_OK != setCommunicationMode(ETH_MODE_DOWN, CtrlIdx)) {
        return E_NOT_OK ;
    }
    /* Configure the controller */
    if (E_OK != configureController(CtrlCfgPtr)) {
        return E_NOT_OK ;
    }

    /* Enter operation mode */
    return E_OK ;
}

/**
 * TX ISR for GMAC SW PORT1/2 data interrupt
 */
/* !req 4.1.2/SWS_Eth_00114 *//* !req 4.0.3/ETH114 */
void Eth_TxIrqHdlr(void) {
    /* !req 4.1.2/SWS_Eth_00111 *//* !req 4.0.3/ETH111 */
    /* !req 4.1.2/SWS_Eth_00116 *//* !req 4.0.3/ETH116 */
    /* @req 4.1.2/SWS_Eth_00115 *//* @req 4.0.3/ETH115 */
    uint32 txChStat = (pHwPtr->WR.WR_C0_TX_STAT) & (ETH_GMAC_SW_INT_STAT_MASK);
#if (ETH_USE_CTRL_0 == STD_ON ) /*lint !e553 no harm */
    if((txChStat & ((uint32)1u << EthCtrlUnit[0].pEthcfgPtr->EthHwTxDmaCh)) != 0u){
        Eth_Hw_TxConfirmation(0); /* This parses everything */
    }
#endif
#if (ETH_USE_CTRL_1 == STD_ON ) /*lint !e553 no harm */
    if((txChStat & ((uint32)1u << EthCtrlUnit[1].pEthcfgPtr->EthHwTxDmaCh)) != 0u){
        Eth_Hw_TxConfirmation(1); /* This parses everything */
    }
#endif
    pHwPtr->CPDMA.CPDMA_EOI_VECTOR = (ETH_GMAC_CPDMA_EOI_VECTOR_MASK & ETH_GMAC_SW_CPDMA_EOI_TX_PULSE);

#if defined(CFG_ETH_ARC_STATISTICS)
    EthStatistics.TxInterptCnt++;
#endif
}

/**
 * RX ISR for GMAC SW PORT1/2 data interrupt
 */
/* !req 4.1.2/SWS_Eth_00114 *//* !req 4.0.3/ETH114 */
void Eth_RxIrqHdlr(void) {
    /* !req 4.1.2/SWS_Eth_00111 *//* !req 4.0.3/ETH111 */
    /* !req 4.1.2/SWS_Eth_00116 *//* !req 4.0.3/ETH116 */
    uint32 rxChStat = ((pHwPtr->WR.WR_C0_RX_STAT) & (ETH_GMAC_SW_INT_STAT_MASK));
    uint32 rxChThreshStat = ((pHwPtr->WR.WR_C0_RX_THRESH_STAT) & (ETH_GMAC_SW_INT_STAT_MASK));

#if (ETH_USE_CTRL_0 == STD_ON ) /*lint !e553 no harm */
    if(((rxChStat & ((uint32)1u << EthCtrlUnit[0].pEthcfgPtr->EthHwRxDmaCh)) != 0u) ||
       ((rxChThreshStat & ((uint32)1u << EthCtrlUnit[0].pEthcfgPtr->EthHwRxDmaCh)) != 0u))	{
        Eth_Hw_Receive(0, NULL); /* This parses everything */
    }
#endif
#if (ETH_USE_CTRL_1 == STD_ON ) /*lint !e553 no harm */
    if(((rxChStat & ((uint32)1u << EthCtrlUnit[1].pEthcfgPtr->EthHwRxDmaCh)) != 0u) ||
       ((rxChThreshStat & ((uint32)1u << EthCtrlUnit[1].pEthcfgPtr->EthHwRxDmaCh)) != 0u))	{
        Eth_Hw_Receive(1, NULL); /* This parses everything */
    }
#endif
       pHwPtr->CPDMA.CPDMA_EOI_VECTOR = (ETH_GMAC_CPDMA_EOI_VECTOR_MASK & ETH_GMAC_SW_CPDMA_EOI_RX_PULSE);
       pHwPtr->CPDMA.CPDMA_EOI_VECTOR = (ETH_GMAC_CPDMA_EOI_VECTOR_MASK & ETH_GMAC_SW_CPDMA_EOI_RX_THRESH_PULSE);

#if defined(CFG_ETH_ARC_STATISTICS)
    EthStatistics.RxInterptCnt++;
#endif
}


/**
 * Miscellaneous ISR for GMAC SW PORT1/2 data interrupt
 */
#ifdef CFG_ETH_TEST
void Eth_MiscIrqHdlr(void) {
    pHwPtr->CPDMA.CPDMA_EOI_VECTOR = (ETH_GMAC_CPDMA_EOI_VECTOR_MASK & ETH_GMAC_SW_CPDMA_EOI_MISSL);
}
#endif


#if (ETH_MII_API == STD_ON)
/**
 * Writes PHY register through MII
 * @param CtrlCfgPtr
 * @param TrcvIdx
 * @param RegIdx
 * @param RegVal
 * @return E_OK: Write OK, E_NOT_OK: Write failed
 */
Std_ReturnType Eth_Hw_WriteMii(const Eth_ControllerConfigType *CtrlCfgPtr,
        uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal) {

    VALIDATE_HW_RV(CtrlCfgPtr->EthHwUnit, ETH_GLOBAL_ID, ETH_E_CONFIG_INVALID,
               E_NOT_OK);

    Std_ReturnType ret;

    BUSY_WAIT_A_WHILE(&pHwPtr->MDIO.MDIO_USERACCESS0, ETH_GMAC_SW_MDIO_USERACCESS_GO, 0,&ret);
    if(ret != E_OK){
        return ret; /* Busy still for some reason */
    }
    uint32_t reg;
    reg = (ETH_GMAC_SW_MDIO_USERACCESS_GO | /* write operation */
    	   ETH_GMAC_SW_MDIO_USERACCESS_WRITE |
		   (RegIdx  << ETH_GMAC_SW_MDIO_USERACCESS_REG_SHIFT)|
		   (TrcvIdx << ETH_GMAC_SW_MDIO_USERACCESS_PHYADR_SHIFT) |
		   (RegVal & ETH_GMAC_SW_MDIO_USERACCESS_DATA_MASK) );

    pHwPtr->MDIO.MDIO_USERACCESS0 = reg;
    BUSY_WAIT_A_WHILE(&pHwPtr->MDIO.MDIO_USERACCESS0, ETH_GMAC_SW_MDIO_USERACCESS_GO, 0,&ret);
    return ret;
}

/**
 * Reads PHY register through MII
 * @param CtrlCfgPtr
 * @param TrcvIdx
 * @param RegIdx
 * @param RegVal
 * @return E_OK: Read OK, E_NOT_OK: Read failed
 */
Std_ReturnType Eth_Hw_ReadMii(const Eth_ControllerConfigType *CtrlCfgPtr,
        uint8 TrcvIdx, uint8 RegIdx, uint16 *RegVal) {
    VALIDATE_HW_RV(CtrlCfgPtr->EthHwUnit, ETH_GLOBAL_ID, ETH_E_CONFIG_INVALID,
                   E_NOT_OK);

    Std_ReturnType ret;

    BUSY_WAIT_A_WHILE(&pHwPtr->MDIO.MDIO_USERACCESS0, ETH_GMAC_SW_MDIO_USERACCESS_GO, 0,&ret);
    if(ret != E_OK){
        return ret; /* Busy still for some reason */
    }
    uint32_t reg;
    reg = (ETH_GMAC_SW_MDIO_USERACCESS_GO | /* read operation */
    	  (RegIdx << ETH_GMAC_SW_MDIO_USERACCESS_REG_SHIFT) |
		  (TrcvIdx << ETH_GMAC_SW_MDIO_USERACCESS_PHYADR_SHIFT) );

    pHwPtr->MDIO.MDIO_USERACCESS0 = reg;
    BUSY_WAIT_A_WHILE(&pHwPtr->MDIO.MDIO_USERACCESS0, ETH_GMAC_SW_MDIO_USERACCESS_GO,0,&ret);
    BUSY_WAIT_A_WHILE(&pHwPtr->MDIO.MDIO_USERACCESS0, ETH_GMAC_SW_MDIO_USERACCESS_ACK, ETH_GMAC_SW_MDIO_USERACCESS_ACK,&ret);
    *RegVal = (pHwPtr->MDIO.MDIO_USERACCESS0 & ETH_GMAC_SW_MDIO_USERACCESS_DATA_MASK);
    return ret;
}
#endif

/**
 * Set hw in requested mode
 * @param CtrlCfgPtr
 * @param CtrlMode
 * @return E_OK: Success, E_NOT_OK: Failed
 */
Std_ReturnType Eth_Hw_SetControllerMode(
        const Eth_ControllerConfigType *CtrlCfgPtr, uint8 CtrlIdx,
        Eth_ModeType CtrlMode) {
    VALIDATE_HW_RV(CtrlCfgPtr->EthHwUnit, ETH_GLOBAL_ID, ETH_E_CONFIG_INVALID,
            E_NOT_OK);
    Std_ReturnType ret = E_OK;
    switch (CtrlMode) {
        case ETH_MODE_ACTIVE:
            if (E_OK
                    != setCommunicationMode(ETH_MODE_ACTIVE, CtrlIdx)) {
                ret = E_NOT_OK;
            }
            break;
        case ETH_MODE_DOWN:
            if (E_OK
                    != setCommunicationMode(ETH_MODE_DOWN, CtrlIdx)) {
                ret = E_NOT_OK;
            }
            /* @req 4.2.2/SWS_Eth_00137 */
            /* @req 4.2.2/SWS_Eth_00138 */
            if (E_OK != resetBuffers(CtrlCfgPtr, CtrlIdx)) {
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
 * Sets the MAC address of the Hw, Reentrant function
 * @param CtrlIdx
 * @param PhysAddrPtr
 * @return E_OK: Success, E_NOT_OK: Failed
 */
Std_ReturnType Eth_Hw_UpdatePhysAddrFilter(
        const Eth_ControllerConfigType *CtrlCfgPtr, const uint8* PhysAddrPtr,
        Eth_FilterActionType Action) {
    VALIDATE_HW_RV(CtrlCfgPtr->EthHwUnit, ETH_GLOBAL_ID, ETH_E_CONFIG_INVALID,
            E_NOT_OK);
    Std_ReturnType ret = E_OK;
    boolean isFilterOpen = TRUE;
    boolean isFilterUni =  TRUE;
    uint16 vid = 0u; /* No vlan id by default */

    for (uint8 i = 0; (i < ETH_MAC_ADDR_SIZE) && isFilterOpen ; i++) {
        if (ETH_BROADCAST_BYTE != PhysAddrPtr[i]) {
            isFilterOpen = FALSE;
        }
    }
    for (uint8 i = 0; (i < ETH_MAC_ADDR_SIZE) && isFilterUni; i++) {
		if (0x00u != PhysAddrPtr[i]) {
			isFilterUni = FALSE;
		}
	}
#if defined(CFG_ETH_HW_SHARE)
    /* cannot be able to configure vlan in ETH config as ideally ETH should support multiple vlans,
     * no support for this in the spec */
    if(EthHwPvtConfig.vGetConfiguredVid != NULL){
    	vid = EthHwPvtConfig.vGetConfiguredVid(CtrlCfgPtr->EthHwUnit);
    }
#endif
    /* @req 4.2.2/SWS_Eth_00245 */
    /* @req 4.2.2/SWS_Eth_00246 */

    if (ETH_ADD_TO_FILTER == Action) {
        if (isFilterUni) {
            /* @req 4.2.2/SWS_Eth_00147 */
            pHwPtr->ALE.ALE_CONTROL &= ~ETH_GMAC_SW_ALE_BYPASS; /* end this mode */
            ret = configureALETabl(CtrlCfgPtr->EthCtrlIdx, CtrlCfgPtr->EthHwUnit,CtrlCfgPtr->EthCtrlPhyAddress);
        }else if (isFilterOpen) {
            /* @req 4.2.2/SWS_Eth_00144 */
            /* open the filter completely */
            /* Clear ALE address table */
            pHwPtr->ALE.ALE_CONTROL |= ETH_GMAC_SW_ALE_CLEAR_TABLE;
            while((pHwPtr->ALE.ALE_CONTROL & ETH_GMAC_SW_ALE_CLEAR_TABLE) ==  ETH_GMAC_SW_ALE_CLEAR_TABLE){};
            pHwPtr->ALE.ALE_CONTROL |= ETH_GMAC_SW_ALE_BYPASS;
        }else{
            /* Adding same filter multiple times are needed to be taken care by upper layers */
             /* though Underlying HW mechanism is available. matching is via source address  */
            if(isEntryMulticast(PhysAddrPtr) == FALSE ){
                ret |= addUnicastAdrsTablEntry(CtrlCfgPtr->EthHwUnit,PhysAddrPtr,vid);
                ret |= addUnicastAdrsTablEntry(0,PhysAddrPtr,vid);
            }else{
                ret |= addMulticastAdrsTablEntry(CtrlCfgPtr->EthHwUnit,PhysAddrPtr,vid);
                ret |= addMulticastAdrsTablEntry(0,PhysAddrPtr,vid);
            }
        }
    }
    else{
        if(isEntryMulticast(PhysAddrPtr) == FALSE ){
            ret |= removeUnicastAdrsTablEntry(CtrlCfgPtr->EthHwUnit,PhysAddrPtr,vid);
            ret |= removeUnicastAdrsTablEntry(0,PhysAddrPtr,vid);
        }else{
            ret |= removeMulticastAdrsTablEntry(CtrlCfgPtr->EthHwUnit,PhysAddrPtr,vid);
            ret |= removeMulticastAdrsTablEntry(0,PhysAddrPtr,vid);
        }
    }
    return ret;
}

/**
 * Reads MAC address from Hw
 * @param CtrlIdx
 * @param PhysAddrPtr (network byte order)
 */
void Eth_Hw_GetPhysAddr(const Eth_ControllerConfigType *CtrlCfgPtr,
        uint8* PhysAddrPtr) {
    VALIDATE_HW_NO_RV(CtrlCfgPtr->EthHwUnit, ETH_GLOBAL_ID, ETH_E_CONFIG_INVALID);
    uint32 ValHi;
    uint32 ValLo;
    if(CtrlCfgPtr->EthHwUnit == GMAC_SW_PORT1){
        ValLo = pHwPtr->PORT1.SA_LO;
        ValHi = pHwPtr->PORT1.SA_HI;
    }else{
        ValLo = pHwPtr->PORT2.SA_LO;
        ValHi = pHwPtr->PORT2.SA_HI;
    }
    PhysAddrPtr[5] = (uint8) ((ValLo >> ETH_SHIFT_BYTE1) & ETH_BYTE_MASK);
    PhysAddrPtr[4] = (uint8) ((ValLo & ETH_BYTE_MASK));
    PhysAddrPtr[3] = (uint8) ((ValHi >> ETH_SHIFT_BYTE3) & ETH_BYTE_MASK);
    PhysAddrPtr[2] = (uint8) ((ValHi >> ETH_SHIFT_BYTE2) & ETH_BYTE_MASK);
    PhysAddrPtr[1] = (uint8) ((ValHi >> ETH_SHIFT_BYTE1) & ETH_BYTE_MASK);
    PhysAddrPtr[0] = (uint8) ((ValHi & ETH_BYTE_MASK));
}

/**
 * Sets the MAC address of the HW,Reentrant function
 * @param CtrlCfgPtr
 * @param PhysAddrPtr
 */
void Eth_Hw_SetPhysAddr(const Eth_ControllerConfigType *CtrlCfgPtr,
        const uint8* PhysAddrPtr) {
    VALIDATE_HW_NO_RV(CtrlCfgPtr->EthHwUnit, ETH_GLOBAL_ID,ETH_E_CONFIG_INVALID);
    configureMacAdrs(CtrlCfgPtr->EthHwUnit, PhysAddrPtr); /* Configure MAC address */
    if( configureALETabl(CtrlCfgPtr->EthCtrlIdx, CtrlCfgPtr->EthHwUnit,PhysAddrPtr) != E_OK){
        DET_REPORT_ERROR(ETH_GLOBAL_ID, ETH_E_GENERAL_ERROR);
    }
}

/**
 * Provides free tx buffer if available
 * @param CtrlIdx
 * @param BufIdxPtr
 * @param BufPtr
 * @param LenBytePtr
 * @return
 */
BufReq_ReturnType Eth_Hw_ProvideTxBuffer(
        const Eth_ControllerConfigType *CtrlCfgPtr, Eth_BufIdxType* BufIdxPtr,
        Eth_DataType** BufPtr, uint16* LenBytePtr) {
    /* @req 4.2.2/SWS_Eth_00078 */
    /* @req 4.2.2/SWS_Eth_00080 */
    BufReq_ReturnType ret = BUFREQ_E_BUSY;
    VALIDATE_HW_RV(CtrlCfgPtr->EthHwUnit, ETH_GLOBAL_ID, ETH_E_CONFIG_INVALID, BUFREQ_E_NOT_OK);
    /* Find a free buffer */ /* make round-robbin method for safety */
    for (Eth_BufIdxType bufIndex = 0; ((bufIndex < CtrlCfgPtr->EthTxBufTotal) && (BUFREQ_E_BUSY == ret)); bufIndex++) {
    	SchM_Enter_Eth_EA_0();
        if ( FALSE  == EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[bufIndex].locked) {
            if (*LenBytePtr > ((uint16) CtrlCfgPtr->EthCtrlTxBufLenByte - ETH_HEADER_SIZE)) {
                /* @req 4.2.2/SWS_Eth_00079 *//* !req 4.0.3/ETH079 */
                *LenBytePtr = (uint16) CtrlCfgPtr->EthCtrlTxBufLenByte - ETH_HEADER_SIZE;
                ret = BUFREQ_E_OVFL;
            }
            else {
                EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[bufIndex].locked = TRUE;
                *BufIdxPtr = bufIndex;
                *BufPtr =  &EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[bufIndex].dataPtr[ETH_HEADER_SIZE];
                ret = BUFREQ_OK;
            }
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
Std_ReturnType Eth_Hw_Transmit(const Eth_ControllerConfigType *CtrlCfgPtr,
        Eth_BufIdxType BufIdx, Eth_FrameType FrameType, boolean TxConfirmation,
        uint16 LenByte, const uint8* PhysAddrPtr) {
    VALIDATE_HW_RV(CtrlCfgPtr->EthHwUnit, ETH_GLOBAL_ID, ETH_E_CONFIG_INVALID,
            E_NOT_OK);

    if (BufIdx >= CtrlCfgPtr->EthTxBufTotal) {
        /* Bad buffer id */
        return E_NOT_OK ;
    }
    if ( FALSE == EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[BufIdx].locked) {
        /* Trying to transmit using a buffer not provided */
        return E_NOT_OK ;
    }
    if (LenByte > (CtrlCfgPtr->EthCtrlTxBufLenByte - ETH_HEADER_SIZE)) {
        return E_NOT_OK ;
    }
    uint32 Val;

    /* Check if the next descriptor in the chain is available*/
    Std_ReturnType ret = E_NOT_OK;

    SchM_Enter_Eth_EA_0(); /* ASR deviated - This function is called from multiple tasks */
    /* Check if the next descriptor in the chain is available*/
    volatile EthDescType *pEthTxDesc =  &EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].pEthTxDesc[EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx];
    if  ((( pEthTxDesc->PktFlgLen & ETH_GMAC_SW_DSC_FLAG_OWNER) == 0u)
#if defined(CFG_ETH_HW_SHARE) /* if last Tx has been completed and acknowledged - mainly in Polling mode */
        &&	(checktTxDescFree(CtrlCfgPtr->EthCtrlIdx) == TRUE)
        &&  (READ_REG_32( (uint32)(&pHwPtr->STATERAM.TX0_HDP) + (sizeof(uint32) * EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].pEthcfgPtr->EthHwTxDmaCh)) == 0u)
#endif
         ){
#if !defined(CFG_ETH_TX_STATIC_BUF_ASSIGN)
        /*  Dynamic linking of an individual buffer to the descriptor */
        pEthTxDesc->pBuf = EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[BufIdx].dataPtr;
#endif
        /* This descriptor can be used */
        /* @req 4.2.2/SWS_Eth_00088 */
        insertEthHeader(CtrlCfgPtr, PhysAddrPtr,
                EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[BufIdx].dataPtr,
                FrameType);

        /* Write Len */
        Val = pEthTxDesc->PktFlgLen;
        Val = (Val & ~ETH_GMAC_SW_DSC_PKT_LEN_MASK) | ((uint32) LenByte + ETH_HEADER_SIZE);
        pEthTxDesc->PktFlgLen = Val;
        Val = pEthTxDesc->BufOffLen; /* Single frame buffer */
        Val = (Val & ~ETH_GMAC_SW_DSC_TX_BUF_LEN_MASK) | ((uint32) LenByte + ETH_HEADER_SIZE);
        pEthTxDesc->BufOffLen = Val;

        EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxDescStatus[EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx].TxBufferIdx =  BufIdx;
        /* @req 4.2.2/SWS_Eth_00089 */

        if (TxConfirmation) {
            EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxDescStatus[EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx].TxState =
                    ETH_TX_DESC_TX_REQUESTED_CONFIRM;
        }
        else {
            EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxDescStatus[EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx].TxState =
                    ETH_TX_DESC_TX_REQUESTED_NO_CONFIRM;
        }

        /*  flush buffers here... */
        /*	The buffer that contains the Ethernet frame data should be flushed from cache if cached
         memory is being used */

        /*  start transmitting the frame */

        /* Issue transmit request for the queue */
        pEthTxDesc->PktFlgLen |= ETH_GMAC_SW_DSC_FLAG_PKT_SINGLE;
        pEthTxDesc->PktFlgLen |= ETH_GMAC_SW_DSC_FLAG_OWNER; /* Add this only for SOP descs */

        WRITE_REG_32( (uint32)(&pHwPtr->STATERAM.TX0_HDP) + (sizeof(uint32) * EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].pEthcfgPtr->EthHwTxDmaCh), (uint32)pEthTxDesc);

        EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx =
                        (EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx + 1)
                                % CtrlCfgPtr->EthTxBufTotal;
        /* releasing or locking depending up on Txconfirmation request */
        /* wait for transmission if TxConfirmation is FALSE, since buffer is getting released for upper layer if not in exclusive area */
        EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[BufIdx].locked =  TxConfirmation;
#if	defined(CFG_ETH_ARC_STATISTICS)
        uint8 offset = 0;
        if(FrameType == ETH_TYPE_VLAN){
        	offset = 4;
        }
        if((pEthTxDesc->pBuf[12 + offset] == 0x08) && (pEthTxDesc->pBuf[13 + offset] == 0x00) && (pEthTxDesc->pBuf[23 + offset] == 0x01)){
        	EthStatistics.TxIcmp++;
        }
#endif
        ret = E_OK;
    }
    else {
        /* No descriptor available. Something wrong or something wrong with HW controller- error handling*/
        /* Retry needs to be done, can happen in polling mechanism */
        ret = E_PENDING; /* internal error */
    }
    SchM_Exit_Eth_EA_0();
    return ret;
}

/**
 * Triggers frame transmission confirmation, call this function bit faster
 * when polling method is used, as it is expected to have each confirmation is serviced
 * for each data transfer, rather than sending more than 1 transmits and polling this routine
  * @param CtrlIdx
 */
void Eth_Hw_TxConfirmation(uint8 CtrlIdx) {
    /* @req 4.2.2/SWS_Eth_00101 */
    volatile EthDescType *pEthTxDesc;
    /* Parse all Descs */
    for (volatile uint32 txDescIndex = 0; txDescIndex < EthCtrlUnit[CtrlIdx].pEthcfgPtr->EthTxBufTotal; txDescIndex++) {
        pEthTxDesc = &EthCtrlUnit[CtrlIdx].pEthTxDesc[txDescIndex];
#if defined(CFG_ETH_HW_SHARE) /* In polling mode basically */
    SchM_Enter_Eth_EA_0();
#endif
        if (((pEthTxDesc->PktFlgLen & ETH_GMAC_SW_DSC_FLAG_OWNER) == 0u) &&
             (ETH_TX_DESC_IDLE != EthCtrlUnit[CtrlIdx].EthTxDescStatus[txDescIndex].TxState)) { /*lint !e9007 no right hand side effects of && */
            if (ETH_TX_DESC_TX_REQUESTED_CONFIRM ==
                    EthCtrlUnit[CtrlIdx].EthTxDescStatus[txDescIndex].TxState) {
                /* @req 4.2.2/SWS_Eth_00243 */
                EthIf_TxConfirmation(CtrlIdx,
                        EthCtrlUnit[CtrlIdx].EthTxDescStatus[txDescIndex].TxBufferIdx);
                /* @req 4.2.2/SWS_Eth_00102 */
                EthCtrlUnit[CtrlIdx].EthTxBufferStatus[EthCtrlUnit[CtrlIdx].EthTxDescStatus[txDescIndex].TxBufferIdx].locked =
                        FALSE;
            }

            WRITE_REG_32( (uint32)(&pHwPtr->STATERAM.TX0_CP)  + (sizeof(uint32) * EthCtrlUnit[CtrlIdx].pEthcfgPtr->EthHwTxDmaCh), ((uint32) pEthTxDesc));

            if((pEthTxDesc->PktFlgLen & ETH_GMAC_SW_DSC_FLAG_EOQ) == ETH_GMAC_SW_DSC_FLAG_EOQ){
                pEthTxDesc->PktFlgLen &= ~ETH_GMAC_SW_DSC_FLAG_EOQ;
            }
            EthCtrlUnit[CtrlIdx].EthTxDescStatus[txDescIndex].TxState =	ETH_TX_DESC_IDLE;
        }
#if defined(CFG_ETH_HW_SHARE)
    SchM_Exit_Eth_EA_0();
#endif
    }
}


/**
 * Triggers frame reception
 * @param CtrlIdx
 * @param  RxStatusPtr
 */
void Eth_Hw_Receive(uint8 CtrlIdx, Eth_RxStatusType* RxStatusPtr) {
    uint8 bEoq = FALSE;
    /* @req 4.2.2/SWS_Eth_00096 */
    Eth_FrameType frameType;
	boolean isBroadcast;
	uint8* framePtr;
	uint16 lenByte;
    volatile EthDescType *pEthRxDesc = EthCtrlUnit[CtrlIdx].pEthRxDescChain->pDescHead;
    volatile EthDescType *pEthRxNextDesc;
#if defined(CFG_ETH_HW_SHARE)
    SchM_Enter_Eth_EA_0();
#endif
    while ((pEthRxDesc->PktFlgLen & ETH_GMAC_SW_DSC_FLAG_OWNER ) == 0u){
		/* cache coherence mechanism */
#if !defined(CFG_ETH_RXBUF_CACHE_INVALIDATE_NONE) /* not required for default applications depending upon project integration */
		WRITE_REG_32(IPUx_UNICACHE_CFG_CACHE_MTSTART,pEthRxDesc->pBuf);/* set start addr */
		WRITE_REG_32(IPUx_UNICACHE_CFG_CACHE_MTEND,(pEthRxDesc->pBuf + EthCtrlUnit[CtrlIdx].pEthcfgPtr->EthCtrlRxBufLenByte));/*lint !e9016 pointer arithmetic other than array indexing used*/ /* set end addr */
		WRITE_REG_32(IPUx_UNICACHE_CFG_CACHE_MAINT,IPUx_UNICACHE_INVALIDATE);/* invalidate cache */
		for(vuint32_t i= 0; i < ETH_RX_BUF_ACCESS_SOME_DELAY; i++){
			/* Busy wait */
		};
#endif
		/* Current descriptor will be attached to the tail before releasing this descriptor to the port */
		pEthRxNextDesc = EthCtrlUnit[CtrlIdx].pEthRxDescChain->pDescHead->pNextDesc;
		if(EthCtrlUnit[CtrlIdx].pEthcfgPtr->EthHwEnableCircDesc == FALSE){
			EthCtrlUnit[CtrlIdx].pEthRxDescChain->pDescHead->pNextDesc = NULL;
			EthCtrlUnit[CtrlIdx].pEthRxDescChain->pDescTail->pNextDesc = EthCtrlUnit[CtrlIdx].pEthRxDescChain->pDescHead;
			EthCtrlUnit[CtrlIdx].pEthRxDescChain->pDescTail = EthCtrlUnit[CtrlIdx].pEthRxDescChain->pDescHead;
		}
		frameType = 0u;
		if ( ETH_GMAC_SW_DSC_FLAG_PKT_SINGLE == (pEthRxDesc->PktFlgLen & ETH_GMAC_SW_DSC_FLAG_PKT_SINGLE)){
			framePtr = (uint8*)pEthRxDesc->pBuf;/*lint !e926 !e9005 Intentional cast */

			/* @req 4.2.2/SWS_Eth_000153 */
			isBroadcast = TRUE;
			for (vuint8_t i = 0; (i < ETH_MAC_ADDR_SIZE) && isBroadcast; i++) {
				if (ETH_BROADCAST_BYTE != framePtr[i]) {
					isBroadcast = FALSE;
				}
			}
			frameType |=  (Eth_FrameType) framePtr[ETH_ETHERNETTYPE_START_INDEX]
						   << ETH_SHIFT_BYTE1;/*lint !e9033 no harm in shifting from Autosar defined byte pointers*/
			frameType |=  (Eth_FrameType) framePtr[ETH_ETHERNETTYPE_START_INDEX + 1];/*lint !e9033 no harm in taking the byte pointer*/
			/* The function shall be callable on interrupt level */
			/* @req 4.2.2/SWS_Eth_000244 */
			lenByte = ((pEthRxDesc->PktFlgLen
							& ETH_GMAC_SW_DSC_PKT_LEN_MASK)
					  - (ETH_HEADER_SIZE + ETH_CRC_SIZE ));
		}
#if defined(USE_DEM) || defined(CFG_ETH_USE_DEM)
		if ((pEthRxDesc->PktFlgLen & ETH_GMAC_SW_DSC_FLAG_OVERRUN ) == ETH_GMAC_SW_DSC_FLAG_OVERRUN) {
			/* @req 4.2.2/SWS_Eth_00174 */
			if(DEM_EVENT_ID_NULL != EthCtrlUnit[CtrlIdx].pEthcfgPtr->ETH_E_RX_FRAMES_LOST) {
				Dem_ReportErrorStatus(EthCtrlUnit[CtrlIdx].pEthcfgPtr->ETH_E_RX_FRAMES_LOST, DEM_EVENT_STATUS_FAILED);
			}
		}
#endif
#if	defined(CFG_ETH_ARC_STATISTICS)
		if ((pEthRxDesc->PktFlgLen & ETH_GMAC_SW_DSC_FLAG_OVERRUN ) == ETH_GMAC_SW_DSC_FLAG_OVERRUN) {
			EthStatistics.RxPktOverrun++;
#if defined(USE_DLT) && defined(CFG_DLT_ETH_DEBUG)
		ETH_DLT_LOG_INFO("EthRX Packet Overrun (ERR %u)", EthStatistics.RxPktOverrun);
#endif
		}
#endif
		/* pEthRxDesc->BufOffLen = 0uL; */ /* Unnecessary */
		/* pEthRxDesc->BufOffLen &= ~ETH_GMAC_SW_DSC_RX_BUF_LEN_MASK; */ /* Unnecessary */
		pEthRxDesc->BufOffLen =  EthCtrlUnit[CtrlIdx].EthMaxRxBufLen;
		if((pEthRxDesc->PktFlgLen & ETH_GMAC_SW_DSC_FLAG_EOQ) == ETH_GMAC_SW_DSC_FLAG_EOQ){
			bEoq = TRUE;
		}
		pEthRxDesc->PktFlgLen  = 0x0uL;
		/* Note - ownership flag is added only when all the descriptors are read in case of multi frame packet */
		pEthRxDesc->PktFlgLen |= ETH_GMAC_SW_DSC_FLAG_OWNER;
		WRITE_REG_32( (uint32)(&pHwPtr->STATERAM.RX0_CP) + (sizeof(uint32) * EthCtrlUnit[CtrlIdx].pEthcfgPtr->EthHwRxDmaCh),((uint32)pEthRxDesc));
		WRITE_REG_32( (uint32)(&pHwPtr->CPDMA.CPDMA_RX0_FREEBUFFER) + (sizeof(uint32) * EthCtrlUnit[CtrlIdx].pEthcfgPtr->EthHwRxDmaCh),0x01u);
		EthCtrlUnit[CtrlIdx].pEthRxDescChain->pDescHead = pEthRxNextDesc;
		if(frameType != 0){
			EthIf_RxIndication( CtrlIdx, frameType, isBroadcast,
								&framePtr[ETH_MAC_SRC_ADDR_START_INDEX],
								&framePtr[ETH_HEADER_SIZE],
								lenByte);
#if	defined(CFG_ETH_ARC_STATISTICS)
			uint8 offset = 0;
			if(frameType == ETH_TYPE_VLAN){
				offset = 4;
			}
			if((framePtr[12 + offset] == 0x08) && (framePtr[13 + offset] == 0x00) && (framePtr[23 + offset] == 0x01)){
				EthStatistics.RxIcmp++;
			}
#endif
		}
		if(bEoq  == TRUE){ /* Cannot happen for the circular linked list */
			EthCtrlUnit[CtrlIdx].pEthRxDescChain->EthQueueMissed++;/* circular only */
#if defined(USE_DLT) && defined(CFG_DLT_ETH_DEBUG)
			ETH_DLT_LOG_INFO("EthRX Buffer Misqueued (WARN %u)", EthCtrlUnit[CtrlIdx].pEthRxDescChain->EthQueueMissed);
#endif
			bEoq = FALSE;
			/* start from the available descriptor */
			/* this below line / waiting is meant only during HW sharing */
			while(READ_REG_32((uint32)(&pHwPtr->STATERAM.RX0_HDP) + (sizeof(uint32) * EthCtrlUnit[CtrlIdx].pEthcfgPtr->EthHwRxDmaCh)) != 0u){};
			WRITE_REG_32( (uint32)(&pHwPtr->STATERAM.RX0_HDP) + (sizeof(uint32) * EthCtrlUnit[CtrlIdx].pEthcfgPtr->EthHwRxDmaCh),(uint32)pEthRxNextDesc);
		}
		pEthRxDesc = pEthRxNextDesc;
    }
#if defined(CFG_ETH_HW_SHARE)
    SchM_Exit_Eth_EA_0();
#endif
#if !defined(CFG_ETH_HW_SHARE)
    if(RxStatusPtr != NULL){
        *RxStatusPtr = isRxDatAvailable(CtrlIdx); /* for polling method  to inform EthIf*/
    }
#endif

}


/* ========================================================================== */
/*                           Missl Functions                                  */
/* ========================================================================== */
#if defined(CFG_ETH_ARC_STATISTICS)
Std_ReturnType Eth_Arc_GetStatistics(Eth_Arc_StatisticsType *stats)
{
    Std_ReturnType ret = E_OK;
    if(NULL != stats) {
        stats->RxInterptCnt = EthStatistics.RxInterptCnt;
        stats->TxInterptCnt = EthStatistics.TxInterptCnt;
        stats->RxPktOverrun = EthStatistics.RxPktOverrun;
        stats->TxIcmp =       EthStatistics.TxIcmp;
        stats->RxIcmp =       EthStatistics.RxIcmp;
    }
    else {
        ret = E_NOT_OK;
    }
    return ret;
}

void Eth_Arc_ResetStatistics(void)
{
    EthStatistics.RxInterptCnt = 0;
    EthStatistics.TxInterptCnt = 0;
    EthStatistics.RxPktOverrun = 0;
    EthStatistics.TxIcmp = 0;
    EthStatistics.RxIcmp = 0;
}
#endif

/*lint -restore*/
