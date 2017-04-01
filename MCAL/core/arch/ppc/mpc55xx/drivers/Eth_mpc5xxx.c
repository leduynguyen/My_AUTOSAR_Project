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
/* Note:
 *
 *  This driver is intended to support MPC5XXX Family * *
 *
 *  */

/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.2.2 */
/** @tagSettings DEFAULT_ARCHITECTURE=MPC5748G|MPC5747C */


/* ASR general requirements */
/* @req 4.2.2/SWS_Eth_00009 */
#include "Eth.h"
#include "Eth_Internal.h"
#include "Eth_mpc5xxx.h"                   /* HW file */
#include <string.h>
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
#include "isr.h"
#include "irq_types.h"
#endif
#include "SchM_Eth.h"
#if defined(USE_DEM) || defined(CFG_ETH_USE_DEM)
#include "Dem.h"
#endif
#include "EthIf_Cbk.h"/*file to abstract ETH from HW */
#include "Mcu.h"
#include "Compiler.h"

/* ========================================================================== */
/*                             Configuration verification                                  */
/* ========================================================================== */
#if (ETH_NOF_CONFIG_CTRL > ETH_MAX_HW_UNITS)
#error "ETH: The number of configured ETH controllers exceeds to number of controller supported by MPC574XC/G"
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

/*
Configurations

CFG_ETH_ENHANCED_DESC
CFG_ETH_DEBUG
CFG_ETH_MII_DEBUG
CFG_ETH_ARC_STATISTICS
CFG_ETH_LOOPBACK
CFG_ETH_EXTRA_PROTECT_TX
*/

#define CFG_ETH_DEBUG
#define CFG_ETH_ENHANCED_DESC


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
#define ETH_MCAST_ADDR_VALIDATE_BYTE                  (0u)
#define ETH_MCAST_ADDR_MASK                           (1u)
/* *************************************************************/
#define ETH_ISR_PRIORITY                              (6u)                 /* configure */
#define ETH_GET_HW_PTR(_unit)                         ETH_HW[_unit]
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
void Eth_TxIrqHdlr(uint8 HwUnit);
void Eth_RxIrqHdlr(uint8 HwUnit);
#if defined(CFG_ETH_DEBUG)
void Eth_ErrIrqHdlr(uint8 HwUnit);
#endif

/**
 * @}
 */

#if (ETH_USE_HW_UNIT_0 == STD_ON )
void Eth_TxIrqHdlr_0 (void);
void Eth_RxIrqHdlr_0 (void);
#if defined(CFG_ETH_DEBUG)
void Eth_ErrIrqHdlr_0 (void);
#endif
ISR(Eth_TxIrqHdlr_0) {Eth_TxIrqHdlr (HWUNIT_0);}
ISR(Eth_RxIrqHdlr_0) {Eth_RxIrqHdlr (HWUNIT_0);}
#if defined(CFG_ETH_DEBUG)
ISR(Eth_ErrIrqHdlr_0){Eth_ErrIrqHdlr(HWUNIT_0);}
#endif
#endif


#if (ETH_USE_HW_UNIT_1 == STD_ON )
void Eth_TxIrqHdlr_1 (void);
void Eth_RxIrqHdlr_1 (void);
#if defined(CFG_ETH_DEBUG)
void Eth_ErrIrqHdlr_1 (void);
#endif
ISR(Eth_TxIrqHdlr_1) {Eth_TxIrqHdlr (HWUNIT_1);}
ISR(Eth_RxIrqHdlr_1) {Eth_RxIrqHdlr (HWUNIT_1);}
#if defined(CFG_ETH_DEBUG)
ISR(Eth_ErrIrqHdlr_1){Eth_ErrIrqHdlr(HWUNIT_1);}
#endif
#endif
/*lint -save -e9024 -e9023*/
/* '#/##' operator used in macro 'INSTALL_HANDLER'
 *  Multiple use of '#/##' operators in definition of macro 'INSTALL_HANDLER'
 * '#/##' operator used in macro 'INSTALL_HANDLER'
 *  Reasoning:: No harmfulness ISR is same for TX and RX  ASR says Eth_TxIrqHdlr_0 for GEM0 and Eth_TxIrqHdlr_1 for GEM1
 *  see above and hence optimised to have this way */

#define INSTALL_TX_HANDLER(_name,_sce) \
  do { \
    ISR_INSTALL_ISR2( "ETH_HW_TX", Eth_TxIrqHdlr_##_name , _sce, ETH_ISR_PRIORITY, 0 ); \
} while(0);

#define INSTALL_RX_HANDLER(_name,_sce) \
  do { \
    ISR_INSTALL_ISR2( "ETH_HW_RX", Eth_RxIrqHdlr_##_name , _sce, ETH_ISR_PRIORITY, 0 ); \
} while(0);

#if defined(CFG_ETH_DEBUG)
#define INSTALL_ERR_HANDLER(_name,_sce) \
  do { \
    ISR_INSTALL_ISR2( "ETH_HW_ERR", Eth_ErrIrqHdlr_##_name , _sce, ETH_ISR_PRIORITY, 0 ); \
} while(0);
#endif
/*lint -restore*/

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
  if( (_hw != HWUNIT_0) \
     && (_hw != HWUNIT_1)  \
     ) \
  { \
      DET_REPORT_ERROR(_api, _err); \
      return; \
  }

#define VALIDATE_HW_RV(_hw,_api,_err,_ret ) \
  if( (_hw != HWUNIT_0) \
      && (_hw != HWUNIT_1) \
      ) \
  { \
      DET_REPORT_ERROR(_api, _err); \
      return (_ret); \
  }

#define PAD_BYTES(_totlen,_offlen) \
	if((_totlen % (uint32)ETH_BUF_ALIGNING_BYTES) != 0u){ \
		*(_offlen) = ((uint32)(ETH_BUF_ALIGNING_BYTES) - (_totlen % (uint32)ETH_BUF_ALIGNING_BYTES)); \
	} else { \
		*(_offlen) = 0u; \
	}\

/* ETH HW macros */

/* Buf Desc Common status macros */
#define ETH_HW_BD_WRAP                     (uint16)(0x2000)
#define ETH_HW_BD_INT              		   (uint16)(0x1000)
#define ETH_HW_BD_LAST		               (uint16)(0x0800)

/* RxBD desc status macros */
#define ETH_HW_RXBD_EMPTY	               (uint16)(0x8000) /* Reception is in progress or no reception if 1*/
#define ETH_HW_RXBD_RO1           	       (uint16)(0x4000) /* reserved */
/*#define ETH_HW_BD_WRAP                   (uint16)(0x2000) */
#define ETH_HW_RXBD_RO2           	       (uint16)(0x1000) /* reserved */

/* #define ETH_HW_BD_LAST		           (uint16)(0x0800) */
/* 2 bits reserved  */
#define ETH_HW_RXBD_MISS	               (uint16)(0x0100) /* buffers recieved in Promiscous mode if 1 else normal/internal adrs recognition */

#define ETH_HW_RXBD_BCAST	               (uint16)(0x0080) /* Brodacasted frame */
#define ETH_HW_RXBD_MCAST	               (uint16)(0x0040) /* Multicasted frame */
#define ETH_HW_RXBD_LG		         	   (uint16)(0x0020) /* Receive - frame max length violation */
#define ETH_HW_RXBD_NO		         	   (uint16)(0x0010) /* Receive - non-octet aligned frame.*/

/* #define ETH_HW_RXBD_SH		           (uint16)(0x0008) - check in other FEC */
/* 1 bit reserved */
#define ETH_HW_RXBD_CR		         	   (uint16)(0x0004) /* Receive CRC or frame error. */
#define ETH_HW_RXBD_OV		         	   (uint16)(0x0002) /* Receive overrun */
#define ETH_HW_RXBD_TR		         	   (uint16)(0x0001) /* Set if the receive frame is truncated (frame length >TRUNC_FL) */

#define ETH_HW_RXBD_ERR		               (uint16)(  ETH_HW_RXBD_LG | \
                                                      ETH_HW_RXBD_NO | \
													  ETH_HW_RXBD_CR | \
													  ETH_HW_RXBD_OV | \
													  ETH_HW_RXBD_TR)
#define ETH_HW_FLAG_PKT_SINGLE             (ETH_HW_BD_LAST)

#if defined(CFG_ETH_ENHANCED_DESC)
#define ETH_HW_RXBD_ME		               (uint16)(0x8000) /* MAC error */

#define ETH_HW_RXBD_PE		               (uint16)(0x0400) /* PHY Error*/
#define ETH_HW_RXBD_CE                     (uint16)(0x0200) /* Collision */
#define ETH_HW_RXBD_UC                     (uint16)(0x0100) /* Unicast frame */

#define ETH_HW_RXBD_INT                    (uint16)(0x0080) /* Generate RXB/RXF interrupt */

#define ETH_HW_RXBD_VPCP_MASK              (uint16)(0xE000) /* VLAN frame priority level */

#define ETH_HW_RXBD_ICE                    (uint16)(0x0020) /* IP header checksum error. */ /* Note: sets also when it is a non IP frame */
#define ETH_HW_RXBD_PCR                    (uint16)(0x0010) /* Protocol checksum error  */ /* Note: sets also when there is an unknown protocol */

#define ETH_HW_RXBD_VLAN                   (uint16)(0x0004) /* Frame has a VLAN tag */
#define ETH_HW_RXBD_IPV6                   (uint16)(0x0002) /* IPV6 Frame. */
#define ETH_HW_RXBD_FRAG                   (uint16)(0x0001) /* IPv4 Fragmented frame */

#define ETH_HW_RXBD_HEADER_LEN_MASK        (uint16)(0xF000) /*  */
#define ETH_HW_RXBD_PROTO_TYPE_MASK        (uint16)(0x00FF) /*  */

#define ETH_HW_TXBD_BDU                    (uint16)(0x8000) /* Last buffer descriptor update done */

#define ETH_HW_RXBD_ENH_ERR		           (uint16)(  ETH_HW_RXBD_ME | \
													  ETH_HW_RXBD_PE | \
													  ETH_HW_RXBD_CE | \
													  ETH_HW_RXBD_ICE| \
													  ETH_HW_RXBD_PCR )

#endif

/* TxBD desc status/control macros */
#define ETH_HW_TXBD_READY		           (uint16)(0x8000)
#define ETH_HW_TXBD_TO1		               (uint16)(0x4000) /* reserved */
/* #define ETH_HW_BD_WRAP                  (uint16)(0x2000) */
#define ETH_HW_TXBD_TO2		               (uint16)(0x1000) /* reserved */

/* #define ETH_HW_BD_LAST		            (uint16)(0x0800) */
#define ETH_HW_TXBD_CRC		               (uint16)(0x0400) /* Transmit CRC */

#if defined(CFG_ETH_ENHANCED_DESC)
#define ETH_HW_TXBD_INT		               (uint16)(0x4000) /* Generate Interrupt flags */
#define ETH_HW_TXBD_TS		               (uint16)(0x2000) /* Generates Time stamp */
#define ETH_HW_TXBD_PINS                   (uint16)(0x1000) /* Insert protocol specific checksum */

#define ETH_HW_TXBD_IINS                   (uint16)(0x0800) /* Insert IP header checksum*/
#define ETH_HW_TXBD_UTLT                   (uint16)(0x0100) /* Use transmit Launch time */

#define ETH_HW_TXBD_FTYPE_MASK             (uint16)(0x00F0) /* Type of frame to be transmitted */

/* status flags */
#define ETH_HW_TXBD_TXE                    (uint16)(0x8000) /* Transmit error  */
#define ETH_HW_TXBD_UE                     (uint16)(0x2000) /* Underflow error  */
#define ETH_HW_TXBD_EE                     (uint16)(0x1000) /* Excess Collision error  */

#define ETH_HW_TXBD_FE                     (uint16)(0x0800) /* Frame with error */
#define ETH_HW_TXBD_LCE                    (uint16)(0x0400) /* Late collision error.*/
#define ETH_HW_TXBD_OE                     (uint16)(0x0200) /* Overflow error */
#define ETH_HW_TXBD_TSE                    (uint16)(0x0100) /* Time stamp error */

#endif


/* MII macros - MDIO clause 22 frame */
#define ETH_HW_MII_DATA_ST		           (0x40000000U)
#define ETH_HW_MII_DATA_OP_RD		       (0x20000000U)
#define ETH_HW_MII_DATA_OP_WR		       (0x10000000U)
#define ETH_HW_MII_DATA_PA_MSK	           (0x0F800000U)
#define ETH_HW_MII_DATA_RA_MSK	           (0x007C0000U)
#define ETH_HW_MII_DATA_TA		           (0x00020000U)
#define ETH_HW_MII_DATA_DATA_MSK	       (0x0000FFFFU)
#define ETH_HW_MII_DATA_RA_SHIFT	       (18)
#define ETH_HW_MII_DATA_PA_SHIFT	       (23)
#define ETH_HW_MII_INT_MASK                (0x00800000U)


#define ETH_PAUSE_FRAME_TYPE               (0x8808)
#define ETH_HW_CLEAR_ALL_INT_EVENTS	       (0xFFFFFFFFU)


#define ETH_HW_INT_BABR                    (0x40000000U) /* Babbling Receive Error */
#define ETH_HW_INT_BABT                    (0x20000000U) /* Babbling Transmit Error */
#define ETH_HW_INT_GRA                     (0x10000000U) /* Graceful Stop Complete */

#define ETH_HW_INT_TXF                     (0x08000000U) /* Transmit Frame Interrupt */
#define ETH_HW_INT_TXB                     (0x04000000U) /* Transmit Buffer Interrupt */
#define ETH_HW_INT_RXF                     (0x02000000U) /* Receive Frame Interrupt */
#define ETH_HW_INT_RXB                     (0x01000000U) /* Receive Buffer Interrupt */

#define ETH_HW_INT_MII                     (0x00800000U) /* MII Interrupt. */
#define ETH_HW_INT_EBERR                   (0x00400000U) /* Ethernet Bus Error */ /* critical */
#define ETH_HW_INT_LC                      (0x00200000U) /* Late Collision */
#define ETH_HW_INT_RL                      (0x00100000U) /* Collision Retry Limit */

#define ETH_HW_INT_UN                      (0x00080000U) /* Transmit FIFO Underrun */
#define ETH_HW_INT_PLR                     (0x00040000U) /* Payload Receive Error */
#define ETH_HW_INT_WAKEUP                  (0x00020000U) /* Node Wakeup Request Indication */
#define ETH_HW_INT_TS_AVAIL                (0x00010000U) /* Transmit Timestamp Available */

#define ETH_HW_INT_TS_TIMER                (0x00008000U) /* Timestamp Timer */
#define ETH_HW_INT_TS_RXFLUSH_2            (0x00004000U) /* RX DMA Ring 2 flush indication */
#define ETH_HW_INT_TS_RXFLUSH_1            (0x00002000U) /* RX DMA Ring 1 flush indication */
#define ETH_HW_INT_TS_RXFLUSH_0            (0x00001000U) /* RX DMA Ring 0 flush indication */

#define ETH_HW_INT_TS_PARSERR              (0x00000400U) /* Receive parser error */
#define ETH_HW_INT_TS_PARSRF               (0x00000200U) /* Receive frame rejected */

#define ETH_HW_INT_TS_TXF2                 (0x00000080U) /* class 2 */
#define ETH_HW_INT_TS_TXB2                 (0x00000040U) /* class 2 */
#define ETH_HW_INT_TS_RXF2                 (0x00000020U) /* class 2 */
#define ETH_HW_INT_TS_RXB2                 (0x00000010U) /* class 2 */
#define ETH_HW_INT_TS_TXF1                 (0x00000008U) /* class 1 */
#define ETH_HW_INT_TS_TXB1                 (0x00000004U) /* class 1 */
#define ETH_HW_INT_TS_RXF1                 (0x00000002U) /* class 1 */
#define ETH_HW_INT_TS_RXB1                 (0x00000001U) /* class 1 */


#define ETH_HW_INT_TX_MASK                 (ETH_HW_INT_TXF)
#define ETH_HW_INT_RX_MASK                 (ETH_HW_INT_RXF)
#define ETH_HW_INT_ERR_MASK                (ETH_HW_INT_EBERR)

/* For CRC32  */
#define ETH_HW_CRC32_START_VALUE  	       (0xFFFFFFFFU)
#define ETH_HW_CRC32_POLYNOMIAL_REV        (0xEDB88320U)

#define ETH_HW_HASH_TABL_ENTRY_UNKNOWN     (32u)

#define ETH_HW_MII_SPEED_DIV               (5000000U)



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

/* #pragma pack(1)*/ /* or use compiler option (-pack=n) for ghs */
typedef struct Desc_s {
	vuint16_t status;                        /* Control and status info */
	vuint16_t length;                        /* Data length */
	vuint8_t  *pBuf;                         /* Buffer pointer */
#if defined(CFG_ETH_ENHANCED_DESC)
	vuint16_t enhancedControl;               /* More Control and status info.*/
	vuint16_t enhancedStatus;				 /* More Control and status info.*/
	vuint16_t halfWordHi;                    /* Protocol Info / payload Or Transmit launch time */
	vuint16_t halfWordLo;                    /* Protocol Info / payload Or Transmit launch time */
	vuint16_t lastDescStatus;                /* Last Descriptor status */
	vuint16_t reserved0;                     /* reserved */
	vuint16_t timeStampHi;                   /* Time stamp High */
	vuint16_t timeStampLo;                   /* Time stamp High */
	vuint16_t reserved1;                     /* reserved */
	vuint16_t reserved2;                     /* reserved */
	vuint16_t reserved3;                     /* reserved */
	vuint16_t reserved4;                     /* reserved */
#endif
} EthDescType;
/* #pragma pack() */

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
    /* Index of the next descriptor to use for RX */
    uint32 EthNextRxDescIdx;
} Eth_CtrlType;



/* ========================================================================== */
/*                           Private Variables                                */
/* ========================================================================== */

static Eth_HwRegType * const ETH_HW[ETH_MAX_HW_UNITS] = {
        (Eth_HwRegType*) (ETH_HW0_ADRS),/*lint !e923 Intentional cast from integer literal HW register address to pointer */
#if (ETH_MAX_HW_UNITS == 2)
        (Eth_HwRegType*) (ETH_HW1_ADRS) /*lint !e923 Intentional cast from integer literal HW register address to pointer */
#endif
};/*lint !e923 Intentional cast from integer literal HW register address to pointer */


/* @req 4.2.2/SWS_Eth_00218 */
/* Buffers for RX/TX data */
/*lint -save -e9003 */ /* Global scope for EthRxDataBuffer and EthTxDataBuffer is allowed */

#define ETH_BUF_START_SEC_CLEARED_4
#include "MemMap.h" /*lint !e9019 variables declared before this include - no issue */
static uint8 EthRxDataBuffer[ETH_TOTAL_RX_BUFFER_SIZE] __balign(ETH_BUF_ALIGNING_BYTES);
#define ETH_BUF_STOP_SEC_CLEARED_4
#include "MemMap.h" /*lint !e9019 variables declared before this include - no issue */

#define ETH_BUF_START_SEC_CLEARED_4
#include "MemMap.h" /*lint !e9019 variables declared before this include - no issue */
static uint8 EthTxDataBuffer[ETH_TOTAL_TX_BUFFER_SIZE] __balign(ETH_BUF_ALIGNING_BYTES);
#define ETH_BUF_STOP_SEC_CLEARED_4
#include "MemMap.h" /*lint !e9019 variables declared before this include - no issue */

/* RX/TX descriptors */
static EthDescType EthRxDesc[ETH_NUM_RX_BUFFERS] __balign(ETH_DESC_ALIGNING_BYTES);
static EthDescType EthTxDesc[ETH_NUM_TX_BUFFERS] __balign(ETH_DESC_ALIGNING_BYTES);


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

#if defined(CFG_ETH_ARC_STATISTICS)
static Eth_Arc_StatisticsType EthStatistics;
#endif

/* Controller private data. */
static Eth_CtrlType EthCtrlUnit[ETH_NOF_CONFIG_CTRL] =
        {
#if (ETH_USE_CTRL_0 == STD_ON )
        {
       	.pEthcfgPtr = NULL,
        .pEthRxDesc = EthRxDesc,
        .pEthTxDesc = EthTxDesc,
        .EthTxDescStatus = EthCtrl0TxDescStatus,
		.EthTxBufferStatus = EthCtrl0TxBufferStatus,
		.EthNextTxDescIdx = 0u,
		.EthNextRxDescIdx = 0u,
    },
#endif
#if (ETH_USE_CTRL_1 == STD_ON )  /*lint !e553, Intentional it is defined if second controller is not configured from the tool */
        {
        .pEthcfgPtr = NULL,
		.pEthRxDesc = &EthRxDesc[ETH_NUM_RX_BUFFERS - ETH_CTRL_0_NUM_RX_BUFFERS],
		.pEthTxDesc = &EthTxDesc[ETH_NUM_TX_BUFFERS - ETH_CTRL_0_NUM_TX_BUFFERS],
        .EthTxDescStatus = EthCtrl1TxDescStatus,
        .EthTxBufferStatus = EthCtrl1TxBufferStatus,
        .EthNextTxDescIdx = 0u,
		.EthNextRxDescIdx = 0u,
    }
#endif
    };

/* ========================================================================== */
/*                           Static Functions                                 */
/* ========================================================================== */
/* Static function declarations */
static void configureDesc(const Eth_ControllerConfigType *pCfgPtr);

/**
 * Gets the Controller index(virtual) of mapped to HW unit(physical)
 * @param HwUnit
 * @return CtrlIdx
 */
static uint8 getCtrldx(uint8 HwUnit) {
    uint8 CtrlIdx = 0;
    for (; CtrlIdx < ETH_NOF_CONFIG_CTRL; CtrlIdx++) {
        if (EthCtrlUnit[CtrlIdx].pEthcfgPtr->EthHwUnit == HwUnit) {
            return CtrlIdx;/*lint !e904 */
        }
    }
    return CtrlIdx;
}

/**
 * Clear Desc Pointers
*  @param ctrlIdx
 * @return None
 */
static inline void resetHeadDescPointers(uint8 ctrlIdx) {
	Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwUnit);
	pHwPtr->RDSR.R = 0U;
	pHwPtr->TDSR.R = 0U;
}


/**
 * Enables GMAC Switch interrupts if configured
 * @param ctrlIdx
 * @return none
 */
static void enableInterrupts (uint8 ctrlIdx){

	Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwUnit);
	pHwPtr->EIR.R = ETH_HW_CLEAR_ALL_INT_EVENTS;  /* Clear all outstanding interrupts if any to proceed further */

	if (TRUE == EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthCtrlEnableRxInterrupt) {
		pHwPtr->EIMR.R |= ETH_HW_INT_RX_MASK;
	}

	if (TRUE == EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthCtrlEnableTxInterrupt) {
		pHwPtr->EIMR.R |= ETH_HW_INT_TX_MASK;
	}

#if defined(CFG_ETH_DEBUG)
	pHwPtr->EIMR.R |= ETH_HW_INT_ERR_MASK;
#if defined(CFG_ETH_MII_DEBUG)
	/* MII Interrupt test enable. */
	pHwPtr->EIR.B.MIIx =  1; /* Cleared MII event */
	pHwPtr->EIMR.B.MIIx = 1; /* MII Interrupt Mask */
#endif
#endif
}


/**
 * Disables GMAC Switch interrupts if configured
 * @param ctrlIdx
 * @return none
 */
static void disableInterrupts (uint8 ctrlIdx){
	Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwUnit);
	if (TRUE == EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthCtrlEnableRxInterrupt) {
		pHwPtr->EIMR.R &= ~ETH_HW_INT_RX_MASK;
	}
	if (TRUE == EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthCtrlEnableTxInterrupt) {
		pHwPtr->EIMR.R &= ~ETH_HW_INT_TX_MASK;
	}
#if defined(CFG_ETH_DEBUG)
	pHwPtr->EIMR.R &= ~ETH_HW_INT_ERR_MASK;
#if defined(CFG_ETH_MII_DEBUG)
	/* MII Interrupt test disable. */
	pHwPtr->EIMR.B.MIIx = 0; /* MII Interrupt Mask */
#endif
#endif
}

/**
 * Configures the MAC address
 * @param hwUnit
 * @param macAdrs (network byte order)
 * @return none
 */
static void configureMacAdrs(uint8 hwUnit, const uint8* macAdrs) {
    uint32 valLo;
    uint16 valHi;
    Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(hwUnit);
    /*lint -save -e9033 -e9053*/
    /* Impermissible cast of composite expression (wider essential type for the destination
     * The shift value is at least the precision of the essential type of the left hand side
     * Misra is not happy with shifting u char and loading on to u int and ultimately with casting
     * Reasoning :: Autosar API is addressed by u character pointer and HW register is an u integer
     * and has to be stored in the same manner
     */
    valLo = 0uL;
    valHi = 0uL;
    valLo |= ((uint32) macAdrs[0] << ETH_SHIFT_BYTE3);
    valLo |= ((uint32) macAdrs[1] << ETH_SHIFT_BYTE2);
    valLo |= ((uint32) macAdrs[2] << ETH_SHIFT_BYTE1);
    valLo |= ((uint32) macAdrs[3]);

    valHi |= ((uint16) macAdrs[4] << ETH_SHIFT_BYTE1);
    valHi |= ((uint16) macAdrs[5]);
    /*lint -restore*/

	pHwPtr->PALR.B.PADDR1 = valLo;
	pHwPtr->PAUR.B.PADDR2 = valHi;
	pHwPtr->PAUR.B.TYPE   = ETH_PAUSE_FRAME_TYPE;
}

/**
 * Activates/deactivates the Eth controller
 * @param ctrlMode
 * @param ctrlIdx
 * @return E_OK: Action OK
 */
static Std_ReturnType setCommunicationMode(Eth_ModeType ctrlMode, uint8 ctrlIdx) {
    Std_ReturnType ret = E_OK;
    Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(EthCtrlUnit[ctrlIdx].pEthcfgPtr->EthHwUnit);
    switch (ctrlMode) {
        case ETH_MODE_ACTIVE:
            /* Start TX and RX operations */

            enableInterrupts(ctrlIdx);

            configureDesc(EthCtrlUnit[ctrlIdx].pEthcfgPtr);
			/* Enable MAC / transmission and reception */
            pHwPtr->ECR.B.ETHEREN = 1;
            pHwPtr->RDAR.B.RDAR = 1; /* New desc is free */
            break;

        case ETH_MODE_DOWN:
        	pHwPtr->RDAR.B.RDAR = 0;
            /* Clear DMA Receive and Transmit HDP Controls */
            resetHeadDescPointers(ctrlIdx);
            /* Clear statuses of TX and RX if any */
            disableInterrupts(ctrlIdx);

            /* Disable transmission and reception */
            //  pHwPtr->ECR.B.ETHEREN = 0;
            /* when ETHEREN is in reset, The uDMA, buffer descriptor, and FIFO control logic are reset, including
            the buffer descriptor and FIFO pointers. */
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
    uint16 offLen;
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
        PAD_BYTES(pCfgPtr->EthCtrlTxBufLenByte,&offLen);
        nextDataIndex = (pCfgPtr->EthCtrlIdx * ETH_TX_BUFFERMARKER)
                + nextDataIndex
                + (uint32) (pCfgPtr->EthCtrlTxBufLenByte
                + offLen);/*lint !e9033 */
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
        pEthDesc[txBufIdx].status &= (uint16)~ETH_HW_TXBD_READY; /* not yet ready for transmission */
#if defined(CFG_ETH_ENHANCED_DESC)
        pEthDesc[txBufIdx].enhancedControl &= (uint16)(~ETH_HW_TXBD_INT);
        pEthDesc[txBufIdx].lastDescStatus     = 0u; /* BDU = 0 */
#endif
    }
    pEthDesc = EthCtrlUnit[ctrlIdx].pEthRxDesc;
    for (uint32 rxBufIdx = 0; rxBufIdx < pCtrlCfgPtr->EthRxBufTotal; rxBufIdx++) {
        /* Rx buffers are busy*/
        pEthDesc[rxBufIdx].status  |= ETH_HW_RXBD_EMPTY;
#if defined(CFG_ETH_ENHANCED_DESC)
        pEthDesc[rxBufIdx].enhancedControl &= (uint16)(~ETH_HW_RXBD_INT);
        pEthDesc[rxBufIdx].lastDescStatus     = 0u; /* BDU = 0 */
#endif
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

    Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(pCfgPtr->EthHwUnit);
    volatile EthDescType *pEthDesc = EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthRxDesc;
#if defined(CFG_ETH_ENHANCED_DESC)
    pHwPtr->ECR.B.EN1588 = 0x1;
#endif
    /* Setup buffer descriptor lists / chains */
    uint32 nextDataIndex = 0;
    uint32 bufIdx;
    uint16 offLen;

    for (bufIdx = 0; bufIdx < pCfgPtr->EthRxBufTotal; bufIdx++) {
    	pEthDesc[bufIdx].status = 0u;
    	pEthDesc[bufIdx].length = 0u;
        /* Write with the buffer address */
        pEthDesc[bufIdx].pBuf = (vuint8_t *)((&EthRxDataBuffer[(pCfgPtr->EthCtrlIdx * (uint32)ETH_RX_BUFFERMARKER) + nextDataIndex]));/*lint !e926  Intentional cast from pointer to pointer*/
        PAD_BYTES(pCfgPtr->EthCtrlRxBufLenByte,&offLen);
        nextDataIndex = nextDataIndex
                + (uint32) (pCfgPtr->EthCtrlRxBufLenByte
                + offLen);/*lint !e9033 destination would not exceed the limit */

		/* Mark all entries in this as empty */
		pEthDesc[bufIdx].status  |= ETH_HW_RXBD_EMPTY;
#if defined(CFG_ETH_ENHANCED_DESC)
        pEthDesc[bufIdx].enhancedControl = 0u;
        if (TRUE == pCfgPtr->EthCtrlEnableRxInterrupt){
        	pEthDesc[bufIdx].enhancedControl |= ETH_HW_RXBD_INT;
        }

        pEthDesc[bufIdx].enhancedStatus = 0u;

        pEthDesc[bufIdx].halfWordHi     = 0u;
        pEthDesc[bufIdx].halfWordLo     = 0u;

        pEthDesc[bufIdx].lastDescStatus     = 0u; /* BDU = 0 */

        pEthDesc[bufIdx].timeStampHi = 0u;
        pEthDesc[bufIdx].timeStampLo = 0u;

        pEthDesc[bufIdx].reserved0 = 0u;
        pEthDesc[bufIdx].reserved1 = 0u;
        pEthDesc[bufIdx].reserved2 = 0u;
        pEthDesc[bufIdx].reserved3 = 0u;
        pEthDesc[bufIdx].reserved4 = 0u;
#endif
    }
    pEthDesc[bufIdx-1].status |=  ETH_HW_BD_WRAP;

    nextDataIndex = 0;
    pEthDesc = EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthTxDesc;
    for (bufIdx = 0; bufIdx <  pCfgPtr->EthTxBufTotal ; bufIdx++) {
    	pEthDesc[bufIdx].status = 0u;
        /* Static buffer assignment to the descriptor */
		pEthDesc[bufIdx].pBuf = (vuint8_t *)((&EthTxDataBuffer[(pCfgPtr->EthCtrlIdx * (uint32)ETH_TX_BUFFERMARKER) + nextDataIndex]));/*lint !e926  Intentional cast from pointer to pointer*/
		PAD_BYTES(pCfgPtr->EthCtrlRxBufLenByte,&offLen);
		nextDataIndex = nextDataIndex
				          + (uint32)(pCfgPtr->EthCtrlTxBufLenByte
        		          + offLen);/*lint !e9033 destination would not exceed the limit */
        /* Last buffer, no options in ASR for multi frames, just support Single frames */
        pEthDesc[bufIdx].status |= ETH_HW_FLAG_PKT_SINGLE;

        pEthDesc[bufIdx].status &= (uint16)(~ETH_HW_TXBD_READY); /* not yet ready for transmission */

        pEthDesc[bufIdx].length = 0u; /* Length is updated dynamically */

        if (TRUE == EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthcfgPtr->EthHwEnableTxChecksumOffload) {
             pEthDesc[bufIdx].status |= ETH_HW_TXBD_CRC;
        }

#if defined(CFG_ETH_ENHANCED_DESC)
        pEthDesc[bufIdx].enhancedControl = 0u;
        if (TRUE == pCfgPtr->EthCtrlEnableTxInterrupt){
        	pEthDesc[bufIdx].enhancedControl |= ETH_HW_TXBD_INT;
        }
        if (TRUE == pCfgPtr->EthHwEnableTxChecksumOffload) {
        	 pEthDesc[bufIdx].enhancedControl |= ETH_HW_TXBD_PINS;//IMPROVEMENT The checksum field must be cleared by the application generating the frame
        	 pEthDesc[bufIdx].enhancedControl |= ETH_HW_TXBD_IINS;//IMPROVEMENT The checksum field must be cleared by the application generating the frame
        }
        pEthDesc[bufIdx].enhancedStatus = 0u;

        pEthDesc[bufIdx].halfWordHi     = 0u; /* TLT */
        pEthDesc[bufIdx].halfWordLo     = 0u; /* TLT */

        pEthDesc[bufIdx].lastDescStatus  = 0u; /* BDU = 0 */

        pEthDesc[bufIdx].timeStampHi = 0u;
        pEthDesc[bufIdx].timeStampLo = 0u;

        pEthDesc[bufIdx].reserved0 = 0u;
        pEthDesc[bufIdx].reserved1 = 0u;
        pEthDesc[bufIdx].reserved2 = 0u;
        pEthDesc[bufIdx].reserved3 = 0u;
        pEthDesc[bufIdx].reserved4 = 0u;
#endif
    }
    pEthDesc[bufIdx-1].status |=  ETH_HW_BD_WRAP;
    pHwPtr->RDSR.R =  (uint32)EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthRxDesc;/*lint !e923 Intentional cast */
    pHwPtr->TDSR.R =  (uint32)EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthTxDesc;/*lint !e923 Intentional cast */
}

/**
 * MAC HW reset
 * @param hwUnit
 * @return none
 */
static inline void reset(uint8 hwUnit){
	Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(hwUnit);
	pHwPtr->ECR.B.RESET = 1;
	/* Wait for reset to complete */
	while (pHwPtr->ECR.B.RESET != 0){} ;
	/* Disable controller */
	pHwPtr->ECR.B.ETHEREN = 0; /* redundant when reset happens */
	/* when ETHEREN is in reset, The uDMA, buffer descriptor, and FIFO control logic are reset, including
	the buffer descriptor and FIFO pointers. */
}


/**
 * Configures MDIO operation
 * @param hwUnit
 * @return none
 */
static void configureMDIO(uint8 hwUnit){

	Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(hwUnit);

	uint32 clock = Mcu_Arc_GetPeripheralClock(PERIPHERAL_CLOCK_ENET);

	pHwPtr->MSCR.B.DIS_PRE = 0; /* Preamble enabled */

	pHwPtr->MSCR.B.HOLDTIME = 0; /* Hold time - min 10ns depending on host freq, options 0,1,2,7 */

	/*  1/(MII_SPEED x 2) of internal bus frequency = 2.5 MHz*/
	pHwPtr->MSCR.B.MII_SPEED = (clock / (ETH_HW_MII_SPEED_DIV));
}

/**
 * Search for an unicast address table entry
 * @param pMacAdrs
 * @return uint32
 */
static uint32 calcCRC32(const uint8 *pMacAdrs){
	/* Calc crc */
	uint8 currByte;
	uint32 crc = ETH_HW_CRC32_START_VALUE;
	for (uint8 i = 0; i < ETH_MAC_ADDR_SIZE; i++) {
		currByte = pMacAdrs[i];
		for (uint8 bit = 0; bit < 8; bit++) {
			if (((currByte & 0x01) ^ (crc & 0x01)) == TRUE) { /*((currByte ^ crc) & 1u)*/ /*lint !e9027 operand to operators */
				crc >>= 1;
				crc = crc ^ ETH_HW_CRC32_POLYNOMIAL_REV;
			} else {
				crc >>= 1;
			}
			currByte >>= 1;
		}
	}
	crc = crc >> 26u;
	return crc;
}

/**
 * Remove the Multicast address entry in the ALE table
 * @param ethHwUnit
 * @param pMacAdrs
 * @return none
 */
static inline void removeUnicastAdrsTablEntry(uint8 ethHwUnit,const uint8* pMacAdrs){
	Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(ethHwUnit);
	uint32 crc = calcCRC32(pMacAdrs);
	if (crc >= 32) {
		pHwPtr->IAUR.B.IADDR1 &= ~(1uL << (crc - 32));
	} else {
		pHwPtr->IALR.B.IADDR2 &= ~(1uL << crc);
	}
}

/**
 * Remove the Multicast address entry in the ALE table
 * @param ethHwUnit
 * @param pMacAdrs
 * @return none
 */
static inline void removeMulticastAdrsTablEntry(uint8 ethHwUnit,const uint8* pMacAdrs){
	Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(ethHwUnit);
	uint32 crc = calcCRC32(pMacAdrs);
	if (crc >= 32) {
		pHwPtr->GAUR.B.GADDR1 &= ~(1uL << (crc - 32));
	} else {
		pHwPtr->GALR.B.GADDR2 &= ~(1uL << crc);
	}
}

/**
 * Insert a unicast address entry in the Address recognition engine
 * @param ethHwUnit
 * @param pMacAdrs
 * @return none
 */
static inline void addUnicastAdrsTablEntry(uint8 ethHwUnit,const uint8* pMacAdrs){
	Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(ethHwUnit);
	uint32 crc = calcCRC32(pMacAdrs);
	if (crc >= 32) {
		pHwPtr->IAUR.B.IADDR1 |= (1uL << (crc - 32));
	} else {
		pHwPtr->IALR.B.IADDR2 |= (1uL << crc);
	}
}


/**
 * Insert a Multicast address entry in the Address recognition engine
 * @param ethHwUnit
 * @param pMacAdrs
 * @return none
 */
static inline void addMulticastAdrsTablEntry(uint8 ethHwUnit,const uint8* pMacAdrs){
	Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(ethHwUnit);
	uint32 crc = calcCRC32(pMacAdrs);
	if (crc >= 32) {
		pHwPtr->GAUR.B.GADDR1 |= (uint32)(1uL << (crc - 32));
	} else {
		pHwPtr->GALR.B.GADDR2 |= (uint32)(1uL << crc);
	}
}

/**
 * Verifies if the address is a multicast entry
 * @param pMacAdrs
 * @return boolean
 */
static inline boolean isEntryMulticast (const uint8 *pMacAdrs){
	boolean isMcastEntry = FALSE;
	if( (pMacAdrs[ETH_MCAST_ADDR_VALIDATE_BYTE] & ETH_MCAST_ADDR_MASK) == ETH_MCAST_ADDR_MASK){
		isMcastEntry = TRUE;
	}
	return isMcastEntry;
}


/**
 * Configures MII / RMII and speed of the PORT according to user settings
 * @param ethHwUnit
 * @param ethMIIMode
 * @param ethHwSpeed
 * @return none
 */
static void configureMIIInterface(uint8 ethHwUnit,uint8 ethMIIMode,uint8 ethHwSpeed){

	Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(ethHwUnit);
	 /* always set, only MII or RMII mode */
	pHwPtr->RCR.B.MII_MODE = 0x1;
	/* Enable Full duplex mode */
	pHwPtr->TCR.B.FDEN = 1;

	/* 0x0: MII,0x1: RMII */
	if(ethMIIMode == MII){
		pHwPtr->RCR.B.RMII_MODE = 0x0;
	}else if (ethMIIMode == RMII){
		pHwPtr->RCR.B.RMII_MODE = 0x1;
	}else{
		/* Others *//* No option */
	}
	if(ethHwSpeed== MBPS_10){
		pHwPtr->RCR.B.RMII_10T = 0x1;
	}else if(ethHwSpeed == MBPS_100){
		pHwPtr->RCR.B.RMII_10T = 0x0;
	}else{
		/* 1000MBPS *//* No option */
	}
	pHwPtr->RCR.B.LOOP = 0x0;
#if defined(CFG_ETH_LOOPBACK)
	/*In MII internal loopback, MII_TXCLK and MII_RXCLK must be provided with a clock signal (2.5 MHz for 10
	Mbit/s, and 25 MHz for 100 Mbit/s)) */
	pHwPtr->RCR.B.RMII_MODE = 0x0;
	pHwPtr->RCR.B.DRT = 0x0;
	pHwPtr->RCR.B.LOOP = 0x1;
#endif
}

/**
 * Configures the Eth controller
 * @param pCfgPtr
 * @return E_OK: Configuration successful, E_NOT_OK: Configuration failed
 */
static Std_ReturnType configureController( const Eth_ControllerConfigType *pCfgPtr) {
	uint16 offLen;

	Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(pCfgPtr->EthHwUnit);

	pHwPtr->TFWR.B.STRFWD = 0x0; /* Store And Forward Enable TX FIFO option, carry out as TFWR  */
	pHwPtr->TFWR.B.TFWR = 0x0;/* default 0=64bytes, 0x2=128bytes 0x3=192bytes */


#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
    if (TRUE == pCfgPtr->EthCtrlEnableRxInterrupt){
    	if (pCfgPtr->EthHwUnit == HWUNIT_0){
#if (ETH_USE_HW_UNIT_0 == STD_ON )
    		INSTALL_TX_HANDLER(0, ENET_0_GROUP_2);/*lint !e9036  No harmness*/
#endif
    	}else{
#if (ETH_USE_HW_UNIT_1 == STD_ON )
    		INSTALL_TX_HANDLER(1, ENET_1_GROUP_2);/*lint !e9036  No harmness*/
#endif
    	}
    }
    if(TRUE == pCfgPtr->EthCtrlEnableTxInterrupt) {
    	if (pCfgPtr->EthHwUnit == HWUNIT_0){
#if (ETH_USE_HW_UNIT_0 == STD_ON )
			INSTALL_RX_HANDLER(0, ENET_0_GROUP_1);/*lint !e9036  No harmness*/
#endif
		}else{
#if (ETH_USE_HW_UNIT_1 == STD_ON )
			INSTALL_RX_HANDLER(1, ENET_1_GROUP_1);/*lint !e9036  No harmness*/
#endif
		}
    }
#if defined(CFG_ETH_DEBUG)
    if (pCfgPtr->EthHwUnit == HWUNIT_0){
#if (ETH_USE_HW_UNIT_0 == STD_ON )
		INSTALL_ERR_HANDLER(0, ENET_0_GROUP_0);/*lint !e9036   No harmness*/
#endif
	}else{
#if (ETH_USE_HW_UNIT_1 == STD_ON )
		INSTALL_ERR_HANDLER(1, ENET_1_GROUP_1);/*lint !e9036   No harmness*/
#endif
	}
#endif
#endif

    /* Configure  Group and Individual Address fields */
    pHwPtr->GALR.R = 0;
    pHwPtr->GAUR.R = 0;
    pHwPtr->IALR.R = 0;
    pHwPtr->IAUR.R = 0;
    /* Configure MAC address */
    pHwPtr->TCR.B.ADDINS = 0; /* No programmed Mac address */
    configureMacAdrs(pCfgPtr->EthHwUnit, pCfgPtr->EthCtrlPhyAddress);

    if (FALSE == EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthcfgPtr->EthHwEnableTxChecksumOffload) {
    	pHwPtr->TCR.B.CRCFWD = 0x1; /* TX CRC control */
    }else{
    	pHwPtr->TCR.B.CRCFWD = 0x0;
    	pHwPtr->TFWR.B.STRFWD = 0x1; /* this is required */
    	pHwPtr->TACC.B.IPCHK = 0x01;/* insert IP header Checksum */ /* The filed must be cleared.*/
    	pHwPtr->TACC.B.PROCHK = 0x01;/* insert protocol Checksum */ /* The filed must be cleared.*/
    }

    if (TRUE == EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthcfgPtr->EthHwEnableRxChecksumOffload) {
    	pHwPtr->RSFL.R         = 0x00; /* enable store and forward on the RX FIFO, this is required*/
    	pHwPtr->RACC.B.LINEDIS = 0x01; /* Enable Discard Of Frames With MAC Layer Errors including CRC errors */
    	pHwPtr->RACC.B.IPDIS   = 0x01; /* Enable Discard Of Frames With Wrong IPv4 Header Checksum */
    	pHwPtr->RACC.B.PRODIS  = 0x01; /* Enable Discard Of Frames With Wrong Protocol Checksum */

    	pHwPtr->RACC.B.PADREM  = 0x01; /* this is not related though,Enable Padding Removal For Short IP Frames */
    }else{
    	 pHwPtr->RCR.B.CRCFWD = 0x0; /* RX CRC is not stripped but forwarded to application */
    	 pHwPtr->RCR.B.PADEN = 0x0;
    }
    /* Additional feature */
	if (TRUE == EthCtrlUnit[pCfgPtr->EthCtrlIdx].pEthcfgPtr->EthHwCtrlDiscardRxFCS) { /* this is applicable only when RX checksum offloaded */
	   pHwPtr->RCR.B.CRCFWD = 0x1; /* RX CRC is stripped */
	   pHwPtr->RCR.B.PADEN = 0x1;/* Padding bytes are also stripped along with CRC */
	}

    pHwPtr->OPD.B.PAUSE_DUR = 0x01; /* Pause Duration for TX Pause frames */ //IMPROVEMENT
    pHwPtr->OPD.B.OPCODE = 0x01; /*Opcode field in Pause frames */

    /* @req 4.2.2/SWS_Eth_00146 *//* Hardware filtering is available and hence there is no promiscous mode set */
    /* 1518 bytes default including CRC - SR max is 1522 ( in case of VLAN) */
    PAD_BYTES(pCfgPtr->EthCtrlRxBufLenByte,&offLen);
    pHwPtr->RCR.B.MAX_FL = (pCfgPtr->EthCtrlRxBufLenByte + offLen); /* max length per frame */
    pHwPtr->MRBR.R = ((uint32)pCfgPtr->EthCtrlRxBufLenByte + offLen); /* each ring buffer size - R_BUF_SIZE should have lower
                                                      2 bits 0 for alignment purposes, good to have min 256 bytes */
    pHwPtr->RCR.B.NLC = 0x0; /* No payload length check */
    pHwPtr->RCR.B.FCE = 0x1;  /* Flow control enabled */

    pHwPtr->TCR.B.TFC_PAUSE = 0x0; /* No Transmit Frame Control Pause */
    pHwPtr->TCR.B.GTS = 0x0; /* No Graceful Transmit Stop */

    pHwPtr->RCR.B.BC_REJ = 0x0;

    pHwPtr->RCR.B.PROM = 0x0; /* Promiscous mode is disabled */

    pHwPtr->RCR.B.PAUFWD = 0x0; /* No Pause frames are given to application area */

    configureMIIInterface( pCfgPtr->EthHwUnit,pCfgPtr->EthMIIMode,pCfgPtr->EthHwSpeed);

	/* Configure descriptors */
	configureDesc(pCfgPtr);

	pHwPtr->ECR.B.MAGICEN = 0x1;/* Magic packet detection => EIR[WAKEUP] when a frame is detected.*/
	pHwPtr->ECR.B.SLEEP = 0x0; /* Normal mode */

	/* No support of S-VLAN */
	pHwPtr->ECR.B.SVLANEN = 0x0;
	pHwPtr->ECR.B.VLANUSE2ND = 0x0;/* Supports only single tag */

	pHwPtr->QOS.B.RX_FLUSH0 = 0x1; /* Enable receive flushing */

	pHwPtr->RCMR[0].B.MATCHEN = 0x0; /* No VLAN priority matching in MAC, should be handled in EthIf layer acc to ASR spec */

	return (Std_ReturnType)E_OK;
	/* IMPROVEMENT - To be added when statistics data is required ASR 4.2.1 */
	/* IMPROVEMENT - To be added Interrupt Coalescing */
	/* IMPROVEMENT - To be added enhanced descriptor handling */
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


/**
 * Check if data has been received
 * @param ctrlIdx
 * @return Eth_RxStatusType
 */
static Eth_RxStatusType isRxDatAvailable(uint8 ctrlIdx) {
    const volatile EthDescType *pEthRxDesc =
    		&EthCtrlUnit[ctrlIdx].pEthRxDesc[EthCtrlUnit[ctrlIdx].EthNextRxDescIdx];
    Eth_RxStatusType rxStatus = ETH_NOT_RECEIVED;
    if ((pEthRxDesc->status & ETH_HW_RXBD_EMPTY ) == 0u) {
    	rxStatus = ETH_RECEIVED_MORE_DATA_AVAILABLE;
    }
    return rxStatus;
}

/*lint -save -e904 */ /*Return statement before end of function */
/**
 * Verify if last/all TX transfer is done and acknowledged by HOST software to proceed
 * @param EthCtrlIdx
 * @return boolean
 */
#if defined(CFG_ETH_EXTRA_PROTECT_TX)
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
	Eth_HwRegType *pHwPtr;
	if(CfgPtr != NULL){
		for (uint8 ctrlIdx = 0u;ctrlIdx < ETH_NOF_CONFIG_CTRL; ctrlIdx++){
			EthCtrlUnit[CfgPtr->ConfigSet->Controllers[ctrlIdx].EthCtrlIdx].pEthcfgPtr = &CfgPtr->ConfigSet->Controllers[ctrlIdx];
			/* reset mode */
			reset(CfgPtr->ConfigSet->Controllers[ctrlIdx].EthHwUnit);
			pHwPtr = ETH_GET_HW_PTR(CfgPtr->ConfigSet->Controllers[ctrlIdx].EthHwUnit);

			pHwPtr->EIMR.R = 0U; /* Interrupts are disabled for safety */
			pHwPtr->EIR.R  = ETH_HW_CLEAR_ALL_INT_EVENTS;  /* Clear all outstanding interrupts if any to proceed further */

			configureMDIO(CfgPtr->ConfigSet->Controllers[ctrlIdx].EthHwUnit);
			ret |= Eth_Hw_ControllerInit(&CfgPtr->ConfigSet->Controllers[ctrlIdx],CfgPtr->ConfigSet->Controllers[ctrlIdx].EthCtrlIdx);
			EthCtrlUnit[ctrlIdx].EthNextRxDescIdx = 0;
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
    /* Initialize buffer runtime data */
    initBuffers(CtrlCfgPtr, CtrlIdx);
    /* Enter operation mode */
    return E_OK ;
}

/**
 * TX ISR for ETH SW PORT1/2 data interrupt
 */
/* !req 4.1.2/SWS_Eth_00114 *//* !req 4.0.3/ETH114 */
void Eth_TxIrqHdlr(uint8 HwUnit) {
	/* !req 4.1.2/SWS_Eth_00111 *//* !req 4.0.3/ETH111 */
	/* !req 4.1.2/SWS_Eth_00116 *//* !req 4.0.3/ETH116 */
	/* @req 4.1.2/SWS_Eth_00115 *//* @req 4.0.3/ETH115 */
	uint32 ievent;
	Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(HwUnit);
	/* Check events */
	ievent = (pHwPtr->EIR.R & (uint32)ETH_HW_INT_TX_MASK);

	Eth_Hw_TxConfirmation(getCtrldx(HwUnit)); /* This parses everything */

	pHwPtr->EIR.R = ievent;

#if defined(CFG_ETH_ARC_STATISTICS)
	EthStatistics.TxInterptCnt++;
#endif
}

/**
 * RX ISR for ETH SW PORT1/2 data interrupt
 */
/* !req 4.1.2/SWS_Eth_00114 *//* !req 4.0.3/ETH114 */
void Eth_RxIrqHdlr(uint8 HwUnit) {
	/* !req 4.1.2/SWS_Eth_00111 *//* !req 4.0.3/ETH111 */
	/* !req 4.1.2/SWS_Eth_00116 *//* !req 4.0.3/ETH116 */
	uint32 ievent;

	Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(HwUnit);
	/* Check events */
	ievent = (pHwPtr->EIR.R & (uint32)ETH_HW_INT_RX_MASK);

	Eth_Hw_Receive(getCtrldx(HwUnit), NULL); /* This parses everything */

	pHwPtr->EIR.R = ievent;

#if defined(CFG_ETH_ARC_STATISTICS)
	EthStatistics.RxInterptCnt++;
#endif
}

#if defined(CFG_ETH_DEBUG)
/**
 * ERROR ISR for ETH SW PORT1/2 data interrupt
 */
void Eth_ErrIrqHdlr(uint8 HwUnit) {

	uint32 ievent;

	Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(HwUnit);
	/* Check events */
	ievent = (pHwPtr->EIR.R & (uint32)ETH_HW_INT_ERR_MASK);

    /* IMPROVEMENT- complete this */
	if((ievent & ETH_HW_INT_EBERR) != 0){
		/* reset the MAC */
	}
	pHwPtr->EIR.R = ievent;
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
    Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(CtrlCfgPtr->EthHwUnit);
    uint32 reg;
    uint32 phy;

    BUSY_WAIT_A_WHILE(&pHwPtr->EIR.R, ETH_HW_MII_INT_MASK, 0,&ret);
	if(ret != E_OK){
		/* clear interrupt */
		pHwPtr->EIR.B.MIIx = 1; /* Busy still for some reason */
	}
	phy = (uint32) TrcvIdx << ETH_HW_MII_DATA_PA_SHIFT;
	reg = (uint32) RegIdx  << ETH_HW_MII_DATA_RA_SHIFT;
    pHwPtr->MMFR.R =  (ETH_HW_MII_DATA_ST |
    				   ETH_HW_MII_DATA_OP_WR |
					   ETH_HW_MII_DATA_TA |
					   phy |
					   reg |
					   RegVal);

    BUSY_WAIT_A_WHILE(&pHwPtr->EIR.R, ETH_HW_MII_INT_MASK, ETH_HW_MII_INT_MASK, &ret);
    if(ret != E_NOT_OK){
		/* clear interrupt */
		pHwPtr->EIR.B.MIIx = 1;
    }
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
	Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(CtrlCfgPtr->EthHwUnit);
	uint32 reg;
	uint32 phy;

	BUSY_WAIT_A_WHILE(&pHwPtr->EIR.R, ETH_HW_MII_INT_MASK, 0,&ret);
	if(ret != E_OK){
		/* clear interrupt */
		pHwPtr->EIR.B.MIIx = 1;/* Busy still for some reason */
	}
	phy = (uint32) TrcvIdx << ETH_HW_MII_DATA_PA_SHIFT;
	reg = (uint32) RegIdx  << ETH_HW_MII_DATA_RA_SHIFT;
	pHwPtr->MMFR.R =  (ETH_HW_MII_DATA_ST |
					   ETH_HW_MII_DATA_OP_RD |
					   ETH_HW_MII_DATA_TA |
					   phy |
					   reg );

	BUSY_WAIT_A_WHILE(&pHwPtr->EIR.R, ETH_HW_MII_INT_MASK, ETH_HW_MII_INT_MASK, &ret);
	if(ret != E_NOT_OK){
		/* clear interrupt */
		pHwPtr->EIR.B.MIIx = 1;
		*RegVal = (uint16)pHwPtr->MMFR.B.DATA;
	}
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
    Std_ReturnType ret = E_NOT_OK;
    boolean isFilterOpen = TRUE;
    boolean isFilterUni =  TRUE;
    Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(CtrlCfgPtr->EthHwUnit);

    for (uint8 i = 0; (i < ETH_MAC_ADDR_SIZE) && isFilterOpen ; i++) { /*lint !e9027 operand to operators */
		if (ETH_BROADCAST_BYTE != PhysAddrPtr[i]) {
			isFilterOpen = FALSE;
		}
    }
    for (uint8 i = 0; (i < ETH_MAC_ADDR_SIZE) && isFilterUni; i++) { /*lint !e9027 operand to operators */
		if (0x00u != PhysAddrPtr[i]) {
			isFilterUni = FALSE;
		}
	}
    /* @req 4.2.2/SWS_Eth_00245 */
    /* @req 4.2.2/SWS_Eth_00246 */
    if (ETH_ADD_TO_FILTER == Action) {
    	if (isFilterUni == TRUE) {
    		/* @req 4.2.2/SWS_Eth_00147 */
    		pHwPtr->RCR.B.PROM = 0; /* end Promiscous mode */
    		pHwPtr->GALR.R = 0;
			pHwPtr->GAUR.R = 0;
			pHwPtr->IALR.R = 0;
			pHwPtr->IAUR.R = 0;
			ret = E_OK;
        }else if (isFilterOpen == TRUE) {
            /* @req 4.2.2/SWS_Eth_00144 */
			pHwPtr->RCR.B.PROM = 1;
			ret = E_OK;
        }else{
        	if(isEntryMulticast(PhysAddrPtr) == FALSE ){
				addUnicastAdrsTablEntry(CtrlCfgPtr->EthHwUnit,PhysAddrPtr);
        	}else{
        		addMulticastAdrsTablEntry(CtrlCfgPtr->EthHwUnit,PhysAddrPtr);
        	}
        	ret = E_OK;
        }
    }
    else{
    	if(isEntryMulticast(PhysAddrPtr) == FALSE ){
    		removeUnicastAdrsTablEntry(CtrlCfgPtr->EthHwUnit,PhysAddrPtr);
    	}else{
			removeMulticastAdrsTablEntry(CtrlCfgPtr->EthHwUnit,PhysAddrPtr);
    	}
    	ret = E_OK;
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
    const Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(CtrlCfgPtr->EthHwUnit);
	ValLo = pHwPtr->PALR.B.PADDR1;
	ValHi = pHwPtr->PAUR.B.PADDR2;

	PhysAddrPtr[0] = (uint8) ((ValLo >> ETH_SHIFT_BYTE3) & ETH_BYTE_MASK);
	PhysAddrPtr[1] = (uint8) ((ValLo >> ETH_SHIFT_BYTE2) & ETH_BYTE_MASK);
	PhysAddrPtr[2] = (uint8) ((ValLo >> ETH_SHIFT_BYTE1) & ETH_BYTE_MASK);
	PhysAddrPtr[3] = (uint8) (ValLo & ETH_BYTE_MASK);
	PhysAddrPtr[4] = (uint8) ((ValHi >> ETH_SHIFT_BYTE1) & ETH_BYTE_MASK);
	PhysAddrPtr[5] = (uint8) (ValHi & ETH_BYTE_MASK);
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
    uint16 offLen;
    PAD_BYTES(CtrlCfgPtr->EthCtrlRxBufLenByte,&offLen);
    /* Find a free buffer */ /* make round-robbin method for safety */
    for (Eth_BufIdxType bufIndex = 0; ((bufIndex < (uint32)CtrlCfgPtr->EthTxBufTotal) && (BUFREQ_E_BUSY == ret)); bufIndex++) {
    	SchM_Enter_Eth_EA_0();
        if (FALSE  == EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[bufIndex].locked){
            if (*LenBytePtr > ((uint16) (CtrlCfgPtr->EthCtrlTxBufLenByte + offLen) - (uint16)(ETH_HEADER_SIZE + ETH_CRC_SIZE))) {
                /* @req 4.2.2/SWS_Eth_00079 *//* !req 4.0.3/ETH079 */
            	*LenBytePtr = (uint16) (CtrlCfgPtr->EthCtrlTxBufLenByte + offLen) - (uint16)(ETH_HEADER_SIZE + ETH_CRC_SIZE);
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
    /* Transmit padding is always performed by HW  */
    if (BufIdx >= (uint32)CtrlCfgPtr->EthTxBufTotal) {
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
    uint16 Val;
    Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].pEthcfgPtr->EthHwUnit);

    /* Check if the next descriptor in the chain is available*/
    Std_ReturnType ret = E_NOT_OK;

    SchM_Enter_Eth_EA_0(); /* ASR deviated - This function is called from multiple tasks */
    /* Check if the next descriptor in the chain is available*/
    volatile EthDescType *pEthTxDesc =  &EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].pEthTxDesc[EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx];
    if  ((( pEthTxDesc->status & ETH_HW_TXBD_READY) == 0u)
#if defined(CFG_ETH_EXTRA_PROTECT_TX) /* if last Tx has been completed and acknowledged - mainly in Polling mode */
    	&&	(checktTxDescFree(CtrlCfgPtr->EthCtrlIdx) == TRUE)
		&&  (pHwPtr->TDAR.B.TDAR == 0u) // cleared by MAC when no additional ready descriptors are available
#endif
    	 ){
        /*  Dynamic linking of an individual buffer to the descriptor */
        pEthTxDesc->pBuf = EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[BufIdx].dataPtr;

        /* This descriptor can be used */
        /* @req 4.2.2/SWS_Eth_00088 */
        insertEthHeader(CtrlCfgPtr, PhysAddrPtr,
                EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[BufIdx].dataPtr,
                FrameType);

        /* Write Len */

        Val =  LenByte + (uint16)ETH_HEADER_SIZE;

        pEthTxDesc->length = Val;

        EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxDescStatus[EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx].TxBufferIdx =  BufIdx;
        /* @req 4.2.2/SWS_Eth_00089 */

        if (TxConfirmation != FALSE) {
            EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxDescStatus[EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx].TxState =
                    ETH_TX_DESC_TX_REQUESTED_CONFIRM;
        }
        else {
            EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxDescStatus[EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx].TxState =
                    ETH_TX_DESC_TX_REQUESTED_NO_CONFIRM;
        }

        EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx =
                                (EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx + 1)
                                        % CtrlCfgPtr->EthTxBufTotal;
        /*  flush buffers here... */
        /*	The buffer that contains the Ethernet frame data should be flushed from cache if cached
         memory is being used */

        /*  start transmitting the frame */

        /* Issue transmit request for the queue */

        pEthTxDesc->status |= ETH_HW_FLAG_PKT_SINGLE;
        pEthTxDesc->status |= ETH_HW_TXBD_READY; /* Add this only for SOP descs */
        /*  start transmitting the frame */
        pHwPtr->TDAR.B.TDAR = 1;

        /* releasing or locking depending up on Txconfirmation request */
        /* wait for transmission if TxConfirmation is FALSE, since buffer is getting released for upper layer if not in exclusive area */
        EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[BufIdx].locked =  TxConfirmation;
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
		SchM_Enter_Eth_EA_0();
		if (((pEthTxDesc->status & ETH_HW_TXBD_READY) == 0u) &&
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
			EthCtrlUnit[CtrlIdx].EthTxDescStatus[txDescIndex].TxState =	ETH_TX_DESC_IDLE;
#if defined(CFG_ETH_ENHANCED_DESC)
			pEthTxDesc->lastDescStatus     = 0u; /* BDU = 0 */
#endif
		}
		SchM_Exit_Eth_EA_0();
	}
}

/**
 * Triggers frame reception
 * @param CtrlIdx
 * @param  RxStatusPtr
 */
void Eth_Hw_Receive(uint8 CtrlIdx, Eth_RxStatusType* RxStatusPtr) {
    register uint32 rxDescIndex;
    uint16 len;
    Eth_HwRegType *pHwPtr = ETH_GET_HW_PTR(EthCtrlUnit[CtrlIdx].pEthcfgPtr->EthHwUnit);
	SchM_Enter_Eth_EA_0();
	/* @req 4.2.2/SWS_Eth_00096 */
	volatile EthDescType *pEthRxDesc;
	if(isRxDatAvailable(CtrlIdx) != ETH_NOT_RECEIVED){
		for (rxDescIndex = 0; rxDescIndex < EthCtrlUnit[CtrlIdx].pEthcfgPtr->EthRxBufTotal; rxDescIndex++) {
			pEthRxDesc= &EthCtrlUnit[CtrlIdx].pEthRxDesc[EthCtrlUnit[CtrlIdx].EthNextRxDescIdx];
			if ((pEthRxDesc->status & ETH_HW_RXBD_EMPTY ) == 0u) {
				if ( ETH_HW_FLAG_PKT_SINGLE == (pEthRxDesc->status & ETH_HW_FLAG_PKT_SINGLE)){
					uint8* framePtr = (uint8*)pEthRxDesc->pBuf;/*lint !e926 !e9005 Intentional cast */
					Eth_FrameType frameType = 0u;
					boolean isBroadcast = FALSE;
					/* @req 4.2.2/SWS_Eth_000153 */
					if ( ETH_HW_RXBD_BCAST == (pEthRxDesc->status & ETH_HW_RXBD_BCAST)){
						isBroadcast = TRUE;
					}
					frameType |=  (Eth_FrameType) framePtr[ETH_ETHERNETTYPE_START_INDEX]
								   << ETH_SHIFT_BYTE1;/*lint !e9033 no harm in shifting from Autosar defined byte pointers*/
					frameType |=  (Eth_FrameType) framePtr[ETH_ETHERNETTYPE_START_INDEX + 1];/*lint !e9033 no harm in taking the byte pointer*/
					len = (uint16) (pEthRxDesc->length - ETH_HEADER_SIZE);
#if !defined(CFG_ETH_LOOPBACK)
					if (FALSE == EthCtrlUnit[CtrlIdx].pEthcfgPtr->EthHwCtrlDiscardRxFCS) {
						len = len - ETH_CRC_SIZE ;
					}
#endif

					/* The function shall be callable on interrupt level */
					/* @req 4.2.2/SWS_Eth_000244 */
					EthIf_RxIndication(CtrlIdx, frameType, isBroadcast,
							&framePtr[ETH_MAC_SRC_ADDR_START_INDEX],
							&framePtr[ETH_HEADER_SIZE],
							len);
				}
#if defined(USE_DEM) || defined(CFG_ETH_USE_DEM)
				if ((pEthRxDesc->status & ETH_HW_RXBD_OV ) == ETH_HW_RXBD_OV) {
					/* @req 4.2.2/SWS_Eth_00174 */
					if(DEM_EVENT_ID_NULL != EthCtrlUnit[CtrlIdx].pEthcfgPtr->ETH_E_RX_FRAMES_LOST) {
						Dem_ReportErrorStatus(EthCtrlUnit[CtrlIdx].pEthcfgPtr->ETH_E_RX_FRAMES_LOST, DEM_EVENT_STATUS_FAILED);
					}
				}
#endif
				pEthRxDesc->length = 0u;
				pEthRxDesc->status |= ETH_HW_RXBD_EMPTY;
#if defined(CFG_ETH_ENHANCED_DESC)
				pEthRxDesc->lastDescStatus  = 0u; /* BDU = 0 */
#endif
				EthCtrlUnit[CtrlIdx].EthNextRxDescIdx = (EthCtrlUnit[CtrlIdx].EthNextRxDescIdx + 1)
													   % EthCtrlUnit[CtrlIdx].pEthcfgPtr->EthRxBufTotal;
			}else{
				break;
			}
		}
		pHwPtr->RDAR.B.RDAR = 1; /* New desc is free */
	}
	SchM_Exit_Eth_EA_0();
	if(RxStatusPtr != NULL){
		*RxStatusPtr = isRxDatAvailable(CtrlIdx); /* for polling method to inform EthIf */
	}
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
}
#endif
/*lint -restore*/ /*Return statement before end of function */
