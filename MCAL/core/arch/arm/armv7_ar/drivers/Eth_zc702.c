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
/* ASR general requirements */
/* @req 4.1.2/SWS_Eth_00009 */
///////////////////////////////////////////////////////////////////////////////////////////
/// ........................private includes start........................................
///////////////////////////////////////////////////////////////////////////////////////////
#include "Eth.h"
#include "Eth_Internal.h"
/* HW file */
#include "zynq.h"
#include "irq_types.h"
#include <string.h>
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
#include "isr.h"
#endif
/* MCU file dependency*/
#include "Mcu.h"
#include "EthIf_Cbk.h"/*file to abstract ETH from HW */
#include "SchM_Eth.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// ........................private includes end.........................................
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
/// ... ...................Config verification start ...................................
///////////////////////////////////////////////////////////////////////////////////////////
#if (ETH_NOF_CONFIG_CTRL > 2u)
#error "ETH: The number of configured Eth controllers exceeds to number of controller supported by Zc702"
#endif

#if ( ETH_DEV_ERROR_DETECT == STD_ON )
#if defined(USE_DET)
#include "Det.h"
#else
#error "Eth: Det must be used when dev error detect is enabled"
#endif
#define DET_REPORT_ERROR(_api,_err)                  (void)Det_ReportError(ETH_MODULE_ID,0,(_api),(_err))
#else
#define DET_REPORT_ERROR(_api,_err)
#endif

///////////////////////////////////////////////////////////////////////////////////////////
/// ........................Config verification end .....................................
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
/// ........................ETH Private Macros and constants start .....................
///////////////////////////////////////////////////////////////////////////////////////////
/* GEM registers */
/* Register net_ctrl Details *******************************/
#define ETH_GEM_NWCTRL_LOOPEN                         0x00000002U /* loopback mode */
#define ETH_GEM_NWCTRL_RXEN                           0x00000004U /* Rx Enable  */
#define ETH_GEM_NWCTRL_TXEN                           0x00000008U /* Tx Enable */
#define ETH_GEM_NWCTRL_MDEN                           0x00000010U /* MDIO enable */
#define ETH_GEM_NWCTRL_STATCLR                        0x00000020U /* clear statistics */
#define ETH_GEM_NWCTRL_STATINC                        0x00000040U
#define ETH_GEM_NWCTRL_STATWEN                        0x00000080U
#define ETH_GEM_NWCTRL_STARTTX                        0x00000200U
#define ETH_GEM_NWCTRL_HALTTX                         0x00000400U
#define ETH_GEM_NWCTRL_PAUSETX                        0x00000800U
#define ETH_GEM_NWCTRL_FLUSH_NXT_RX_DPRAM             0x00040000U //Flush the next packet from the external RX DPRAM.
/* Register net_cfg Details **********************************/
#define ETH_GEM_NWCFG_SPEED                           0x00000001U /* Speed - set to logic one to indicate 100Mbps ,logic zero for 10Mbps */
#define ETH_GEM_NWCFG_FDEN                            0x00000002U /* Full duplex - if set to logic one */
#define ETH_GEM_NWCFG_NVLANDISC                       0x00000004U /* Discard non-VLAN frames - when set only VLAN tagged */
#define ETH_GEM_NWCFG_COPYALLEN                       0x00000010U /* Copy all frames */
#define ETH_GEM_NWCFG_BCASTDI                         0x00000020U /* No broadcast Recievee - when set to logic one */
#define ETH_GEM_NWCFG_MCASTHASHEN                     0x00000040U /* Multicast hash enable */
#define ETH_GEM_NWCFG_UCASTHASHEN                     0x00000080U /* Unicast hash enable */
#define ETH_GEM_NWCFG_1536RXEN                        0x00000100U /* Receive 1536 byte frames */
#define ETH_GEM_NWCFG_EXTADDRMATCHEN                  0x00000200U /* External address match enable */
#define ETH_GEM_NWCFG_1000                            0x00000400U /* Gigabit mode enable */
#define ETH_GEM_NWCFG_PCS_SEL                         0x00000800U
#define ETH_GEM_NWCFG_RETRYTESTEN                     0x00001000U /* Retry test - must be set to zero for normal operation. */
#define ETH_GEM_NWCFG_PAUSEEN                         0x00002000U /* Pause enable - when set */
#define ETH_GEM_NWCFG_RXOFFS                          0x0000C000U /* Receive buffer offset */
#define ETH_GEM_NWCFG_LENGTHERRDSCRD                  0x00010000U /* Length field error frame discard */
#define ETH_GEM_NWCFG_FCSREM                          0x00020000U /* FCS remove */
#define ETH_GEM_NWCFG_MDCCLKDIV_MASK                  0x001C0000U /* MDC clock division  */
#define ETH_GEM_NWCFG_PAUSECOPYDI                     0x00800000U /* Disable copy of pause frames */
#define ETH_GEM_NWCFG_RXCHKSUMEN                      0x01000000U /* Receive checksum offload enable  */
#define ETH_GEM_NWCFG_HDRXEN                          0x02000000U /* Enable frames to be received in half-duplex mode while transmitting.*/
#define ETH_GEM_NWCFG_FCSIGNORE                       0x04000000U /* Ignore RX FCS */
#define ETH_GEM_SGMII_EN                              0x08000000U /* SGMII mode enable */
#define ETH_GEM_NWCFG_IPDSTRETCH                      0x10000000U /* IPG stretch enable */
#define ETH_GEM_NWCFG_BADPREAMBEN                     0x20000000U /* Receive bad preambleas well */
#define ETH_GEM_NWCFG_IGNORE_IPG_RX_ER                0x40000000U /* Ignore IPG rx_er */
/* Register dma_cfg Details *******************************/
#define ETH_GEM_DMACR_BLENGTH	                      0x00000010U
#define ETH_GEM_DMACR_RXSIZE    		              0x00000300U /* Use full configured addressable space (8 kB) */
#define ETH_GEM_DMACR_TXSIZE     		              0x00000400U /* 1: Use full configured addressable space (4 kB) */
#define ETH_GEM_DMACR_TCPCKSUM                        0x00000800U
#define ETH_GEM_DMACR_RXBUF_MASK                      0x00FF0000U
/* Buffers */
/* RX word 0 */
#define ETH_GEM_RXBUF_ADDRESS_MASK                    0xFFFFFFFCU
#define ETH_GEM_RXBUF_USED                            0x00000001U
#define ETH_GEM_RXBUF_WRAP                            0x00000002U
/* RX word 1 */
#define ETH_GEM_RXBUF_LENGTH_MASK                     0x00001FFFU
#define ETH_GEM_RXBUF_FRAME_START                     0x00004000U
#define ETH_GEM_RXBUF_FRAME_END                       0x00008000U
#define ETH_GEM_RXBUF_FRAME_SINGLE                    (ETH_GEM_RXBUF_FRAME_START | ETH_GEM_RXBUF_FRAME_END)
/* TX word 0 *//* NA */
/* TX word 1 */
#define ETH_GEM_TXBUF_LENGTH_MASK                     0x00003FFFU
#define ETH_GEM_TXBUF_RETRY_EXCEEDED                  0x20000000U
#define ETH_GEM_TXBUF_LAST                            0x00008000U /*last buffer in the current frame is reached */
#define ETH_GEM_TXBUF_NO_CRC                          0x00010000U /* no CRC to be appended by GEM if set */
#define ETH_GEM_TXBUF_WRAP                            0x40000000U
#define ETH_GEM_TXBUF_USED                            0x80000000U
/* Interrupt related ****************************************/
#define ETH_GEM_INTR_MASK_ALL                         0x00007FFFU
#define ETH_GEM_IXR_ALL                               ETH_GEM_INTR_MASK_ALL
#define ETH_GEM_IXR_MGMNT           	              0x00000001U
#define ETH_GEM_IXR_FRAMERX        		              0x00000002U
#define ETH_GEM_IXR_RXUSED          	              0x00000004U
#define ETH_GEM_IXR_TXUSED          	              0x00000008U
#define ETH_GEM_IXR_URUN            	              0x00000010U
#define ETH_GEM_IXR_RETRY           	              0x00000020U
#define ETH_GEM_IXR_TXEXH           	              0x00000040U
#define ETH_GEM_IXR_TXCOMPL         	              0x00000080U
#define ETH_GEM_IXR_RXOVR          	 	              0x00000400U
#define ETH_GEM_IXR_HRESPNOK        	              0x00000800U
#define ETH_GEM_IXR_PAUSENZERO      	              0x00001000U
#define ETH_GEM_IXR_PAUSEZERO       	              0x00002000U
#define ETH_GEM_IXR_PAUSETX         	              0x00004000U
#define ETH_GEM_IXR_PTPDRRX         	              0x00040000U
#define ETH_GEM_IXR_PTPSRX         		              0x00080000U
#define ETH_GEM_IXR_PTPPDRRX        	              0x00100000U
#define ETH_GEM_IXR_PTPPSRX         	              0x00200000U
#define ETH_GEM_IXR_PTPDRTX         	              0x00400000U
#define ETH_GEM_IXR_PTPSTX          	              0x00800000U
#define ETH_GEM_IXR_PTPPDRTX        	              0x01000000U
#define ETH_GEM_IXR_PTPPSTX         	              0x02000000U
/* *************************************************************/
#define ETH_GEM_TXSR_USEDREAD       	              0x00000001U
#define ETH_GEM_TXSR_FRAMERX        	              0x00000002U
#define ETH_GEM_TXSR_RXOVR          	              0x00000004U
#define ETH_GEM_TXSR_TXGO           	              0x00000008U
#define ETH_GEM_TXSR_BUFEXH         	              0x00000010U
#define ETH_GEM_TXSR_TXCOMPL        	              0x00000020U
#define ETH_GEM_TXSR_URUN           	              0x00000040U
#define ETH_GEM_TXSR_HRESPNOK       	              0x00000100U
#define ETH_GEM_RXSR_BUFFNA         	              0x00000001U
#define ETH_GEM_RXSR_FRAMERX        	              0x00000002U
#define ETH_GEM_RXSR_RXOVR          	              0x00000004U
#define ETH_GEM_RXSR_HRESP          	              0x00000008U
/* MII Management Frame ***************************************/
#define ETH_MII_DATA_ST			                      0x40000000U
#define ETH_MII_DATA_OP_RD		                      0x20000000U
#define ETH_MII_DATA_OP_WR		                      0x10000000U
#define ETH_MII_DATA_TA			                      0x00020000U
/* Net status **************************************************/
#define ETH_GEM_NETSTATUS_MGMT_IDLE                   0x00000004U /*The PHY management logic is idle (i.e. has completed) */

/* Defines for sizes in Ethernet header *************************/
#define ETH_MAC_ADDR_SIZE                             6u
#define ETH_ETHERNETTYPE_SIZE                         2u
/* Start indices for content of Ethernet header *********************/
#define ETH_MAC_DST_ADDR_START_INDEX                  0u
#define ETH_MAC_SRC_ADDR_START_INDEX                  ETH_MAC_ADDR_SIZE
#define ETH_ETHERNETTYPE_START_INDEX                  (2*ETH_MAC_ADDR_SIZE)
/* Size of Ethernet header ***************************************/
#define ETH_HEADER_SIZE                               ((2*ETH_MAC_ADDR_SIZE) + ETH_ETHERNETTYPE_SIZE)
#define ETH_BROADCAST_BYTE                            0xFFu
#define ETH_MAX_MAC_ADRS_SPACE                        4u
/* Max wait cycles for actions to occur in busy wait***** */
#define ETH_MAX_BUSY_WAIT_CYCLES                      (uint32)10000
/* *************************************************************/
#define ETH_SHIFT_BYTE1                               8u
#define ETH_SHIFT_BYTE2                               16u
#define ETH_SHIFT_BYTE3                               24u
/* *************************************************************/
#define ETH_NOF_MAX_TX_AHB_BUF                        128u
#define ETH_NOF_MAX_RX_AHB_BUF                        128u
#define ETH_RX_BDDESC_START_ADRS                      0x0FF00000u        /* configure this address to use it from  uncached area*/
#define ETH_TX_BDDESC_START_ADRS                      0x0FF10000u        /* configure this address to use it from  uncached area */
/* *************************************************************/
#define ETH_ISR_PRIORITY                              5u                 /* configure */
#define ETH_MAX_HW_UNITS                              2u
/* *************************************************************/
#define ETH_GET_HW_PTR(_unit)                         GEM[_unit]

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
void Eth_TxRxIrqHdlr(uint8 HwUnit);

/**
 * @}
 */

/*!req 4.1.2/SWS_Eth_00109 */
#if (ETH_USE_HW_UNIT_0 == STD_ON )
void Eth_TxIrqHdlr_0 (void);
void Eth_RxIrqHdlr_0 (void);
ISR(Eth_TxIrqHdlr_0) {Eth_TxRxIrqHdlr(GEM_0);}
ISR(Eth_RxIrqHdlr_0) {Eth_TxRxIrqHdlr(GEM_0);}

#endif
#if (ETH_USE_HW_UNIT_1 == STD_ON )
void Eth_TxIrqHdlr_1 (void);
void Eth_RxIrqHdlr_1 (void);
ISR(Eth_TxIrqHdlr_1) {Eth_TxRxIrqHdlr(GEM_1);}
ISR(Eth_RxIrqHdlr_1) {Eth_TxRxIrqHdlr(GEM_1);}
#endif
/*lint -save -e9024 -e9023*/
/* '#/##' operator used in macro 'INSTALL_HANDLER'
 *  Multiple use of '#/##' operators in definition of macro 'INSTALL_HANDLER'
 * '#/##' operator used in macro 'INSTALL_HANDLER'
 *  Reasoning:: No harmfulness ISR is same for TX and RX  ASR says Eth_TxIrqHdlr_0 for GEM0 and Eth_TxIrqHdlr_1 for GEM1
 *  see above and hence optimised to have this way */

#define INSTALL_HANDLER(_name,_sce) \
  do { \
    ISR_INSTALL_ISR2( "GEM_TX", Eth_TxIrqHdlr_##_name , _sce, ETH_ISR_PRIORITY, 0 ); \
    ISR_INSTALL_ISR2( "GEM_RX", Eth_RxIrqHdlr_##_name , _sce, ETH_ISR_PRIORITY, 0 ); \
} while(0);
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
  if( (_hw != GEM_0) && (_hw != GEM_1) ) { \
      DET_REPORT_ERROR(_api, _err); \
      return; \
  }

#define VALIDATE_HW_RV(_hw,_api,_err,_ret ) \
  if( (_hw != GEM_0) && (_hw != GEM_1)) { \
      DET_REPORT_ERROR(_api, _err); \
      return (_ret); \
  }

enum {
    ETH_MDCCLKDIV_8 = 0,
    ETH_MDCCLKDIV_16,
    ETH_MDCCLKDIV_32,
    ETH_MDCCLKDIV_48,
    ETH_MDCCLKDIV_64,
    ETH_MDCCLKDIV_96,
    ETH_MDCCLKDIV_128,
    ETH_MDCCLKDIV_224,
} EthMdcClkDivider;
///////////////////////////////////////////////////////////////////////////////////////////
/// ........................ETH Private Macros and constants end .....................
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
/// ........................ETH Private TypesDefinitions start .....................
///////////////////////////////////////////////////////////////////////////////////////////

typedef volatile struct GEM_reg Gem_HwRegType; /* HW register type */

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
} EthTxDescriptorStatusType;

typedef struct Descriptor_s {
    vuint32_t Address; /* address word in TX desc *//* address word in RX desc */
    vuint32_t Status; /* Status word in  TX desc *//* status word in  RX desc */
}/* __attribute__((packed))*/EthDescriptorType;

/* Type for holding information about each controller */
typedef struct {
    /* RX/TX descriptors */
    EthDescriptorType* pEthRxDescriptors;
    EthDescriptorType* pEthTxDescriptors;
    EthTxDescriptorStatusType* EthTxDescriptorStatus;
    EthBufferStatusType* EthTxBufferStatus;
    /* For holding buffer sizes from configuration */
    uint16 EthRxBufTotal;
    /* For holding buffer sizes from configuration */
    uint16 EthTxBufTotal;
    /* Index of the next descriptor to use for TX */
    uint8 EthNextTxDescIdx;
    /* Index of HW unit used for this ctrl id */
    uint8 EthHwUnit;
    /* Index of the next descriptor to handle TX confirmation (which descriptor to start from on intrpt or call to Eth_TxConfirmation) */
    uint8 NextTxConfirmDescIndex;
    /* Receive Frame filter count  */
    uint8 EthFrameFilterCount;
    /* Enable RX checksum offload */
    boolean EthHwEnableRxChecksumOffload;
    /* Enable TX checksum offload */
    boolean EthHwEnableTxChecksumOffload;
    /* Receive Frame lost notice variable */
    boolean EthFrameLost;
    /* Enable or disable FCS discard mode */
    boolean EthHwCtrlDiscardRxFCS;

} Eth_CtrlType;

///////////////////////////////////////////////////////////////////////////////////////////
/// ........................ETH Private TypesDefinitions end .....................
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
/// ........................ETH Private variable data start .....................
///////////////////////////////////////////////////////////////////////////////////////////
static Gem_HwRegType * const GEM[ETH_MAX_HW_UNITS] = {
        (Gem_HwRegType*) (ZYNQ_GEM_BASE),/*lint !e923 Intentional cast from integer literal HW register address to pointer */
        (Gem_HwRegType*) (ZYNQ_GEM_BASE + 0x1000u), /*lint !e923 Intentional cast from integer literal HW register address to pointer */
};

/* Buffers for RX/TX data */
/* It is a byte address */
/*lint -save -e728 -e551 -e843 -e9003*//* Should this be suppressed in file scope? otherwise it does not work*/
/* The variables are not supposed to be global - against to ASR
 * These variables are accessed,addresses of variables are accessed the HW registers
 * Not needed to be initialized explicitely
 * Cannot be made const as well
 * */
#define ETH_BUF_START_SEC_CLEARED_4
#include "MemMap.h"
static uint8 EthRxDataBuffer[ETH_TOTAL_RX_BUFFER_SIZE] __balign(ETH_ALIGNING_BYTES);
#define ETH_BUF_STOP_SEC_CLEARED_4
#include "MemMap.h"

#define ETH_BUF_START_SEC_CLEARED_4
#include "MemMap.h"
static uint8 EthTxDataBuffer[ETH_TOTAL_TX_BUFFER_SIZE] __balign(ETH_ALIGNING_BYTES);
#define ETH_BUF_STOP_SEC_CLEARED_4
#include "MemMap.h"

/* RX/TX descriptors */
#if !defined(CFG_ETH_HW_DESC_ASSIGN_NON_LOCAL)
#define ETH_DESC_START_SEC_CLEARED_4
#include "MemMap.h"
static EthDescriptorType EthRxDescriptors[ETH_NUM_RX_BUFFERS] __balign(ETH_ALIGNING_BYTES);
#define ETH_DESC_STOP_SEC_CLEARED_4
#include "MemMap.h"

#define ETH_DESC_START_SEC_CLEARED_4
#include "MemMap.h"
static EthDescriptorType EthTxDescriptors[ETH_NUM_TX_BUFFERS] __balign(ETH_ALIGNING_BYTES);
#define ETH_DESC_STOP_SEC_CLEARED_4
#include "MemMap.h"
#endif

#if (ETH_USE_CTRL_0 == STD_ON )
/* For link to TX buffer and state of TX descriptor */
static EthTxDescriptorStatusType EthCtrl0TxDescriptorStatus [ETH_CTRL_0_NUM_TX_BUFFERS];
/* For holding the state of a TX buffer */
static EthBufferStatusType EthCtrl0TxBufferStatus [ETH_CTRL_0_NUM_TX_BUFFERS];
#endif
#if (ETH_USE_CTRL_1 == STD_ON )   /*lint !e553, Intentional it is defined if second controller is not configured from the tool */
/* For link to TX buffer and state of TX descriptor */
static EthTxDescriptorStatusType EthCtrl1TxDescriptorStatus [ETH_CTRL_1_NUM_TX_BUFFERS];
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
#if defined(CFG_ETH_HW_DESC_ASSIGN_NON_LOCAL)
        .pEthRxDescriptors = (EthDescriptorType*)ETH_RX_BDDESC_START_ADRS,
#else
        .pEthRxDescriptors = EthRxDescriptors,
#endif
#if defined(CFG_ETH_HW_DESC_ASSIGN_NON_LOCAL)
        .pEthTxDescriptors = (EthDescriptorType*)ETH_TX_BDDESC_START_ADRS,
#else
        .pEthTxDescriptors = EthTxDescriptors,
#endif
        .EthTxDescriptorStatus = EthCtrl0TxDescriptorStatus,

        .EthTxBufferStatus = EthCtrl0TxBufferStatus,
        .EthRxBufTotal = 0,
        .EthTxBufTotal = 0,
        .EthNextTxDescIdx = 0,
        .EthHwUnit = GEM_0, /* initial map of HW ID to CTRL ID */
        .EthFrameFilterCount = 0,
        .NextTxConfirmDescIndex = 0,
        .EthHwEnableRxChecksumOffload = FALSE,
        .EthHwEnableTxChecksumOffload = FALSE,
        .EthFrameLost = FALSE,
        .EthHwCtrlDiscardRxFCS = FALSE,
    },
#endif
#if (ETH_USE_CTRL_1 == STD_ON )  /*lint !e553, Intentional it is defined if second controller is not configured from the tool */
        {
#if defined(CFG_ETH_HW_DESC_ASSIGN_NON_LOCAL)
        .pEthRxDescriptors = (EthDescriptorType*)(ETH_RX_BDDESC_START_ADRS + ETH_MAX_DESCRIPTOR_SIZE),
#else
        .pEthRxDescriptors = &EthRxDescriptors[ETH_NUM_RX_BUFFERS - ETH_CTRL_0_NUM_RX_BUFFERS],
#endif
#if defined(CFG_ETH_HW_DESC_ASSIGN_NON_LOCAL)
        .pEthTxDescriptors = (EthDescriptorType*)(ETH_TX_BDDESC_START_ADRS + ETH_MAX_DESCRIPTOR_SIZE),
#else
        .pEthTxDescriptors = &EthTxDescriptors[ETH_NUM_TX_BUFFERS - ETH_CTRL_0_NUM_TX_BUFFERS],
#endif
        .EthTxDescriptorStatus = EthCtrl1TxDescriptorStatus,
        .EthTxBufferStatus = EthCtrl1TxBufferStatus,
        .EthRxBufTotal = 0,
        .EthTxBufTotal = 0,
        .EthNextTxDescIdx = 0,
        .EthHwUnit = GEM_1, /* initial map of HW ID to CTRL ID */
        .EthFrameFilterCount = 0,
        .NextTxConfirmDescIndex = 0,
        .EthHwEnableRxChecksumOffload = FALSE,
        .EthHwEnableTxChecksumOffload = FALSE,
        .EthFrameLost = FALSE,
        .EthHwCtrlDiscardRxFCS = FALSE,
    }
#endif
    };
///////////////////////////////////////////////////////////////////////////////////////////
/// ........................ETH Private variable data end .....................
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
/// ........................ETH static functions start .....................
///////////////////////////////////////////////////////////////////////////////////////////

/**
 * Gets the Controller index(virtual) of mapped to HW unit(physical)
 * @param HwUnit
 * @return CtrlIdx
 */
static inline uint8 getCtrldx(uint8 HwUnit) {
    uint8 CtrlIdx = 0;
    for (; CtrlIdx < ETH_NOF_CONFIG_CTRL; CtrlIdx++) {
        if (EthCtrlUnit[CtrlIdx].EthHwUnit == HwUnit) {
            return CtrlIdx;
        }
    }
    return CtrlIdx;
}

/**
 * Gets the MDC CLK divider value, taken from CPU_1xClk of the system
 * The MDIO interface clock (MDC) E is generated by dividing down the CPU_1x clock
 * @param none
 * @return EthMdcClkDivType
 */
static inline uint32 getMdcClkDiv(void) {
    uint32 cpu1xClk = (uint32) MCU_ARC_CLOCK_ARM_CPU_1X_FREQUENCY;
    uint32 mdcClkDiv = (uint32) ETH_MDCCLKDIV_8;
    /*lint -save -e774 */
    /* Boolean within 'if' always evaluates to False
     * Reasoning:: MCU_ARC_CLOCK_ARM_CPU_1X_FREQUENCY is generated from configuration tool and changes according to configuration
     * But misra is not happy since it is a constant - however no harmness and alternative */
    if (cpu1xClk != 0u) {
        cpu1xClk = (cpu1xClk / 1000000uL);
    }
    if (cpu1xClk <= 20u) {
        mdcClkDiv = (uint32) ETH_MDCCLKDIV_8;
    }
    else if (cpu1xClk <= 40u) {
        mdcClkDiv = (uint32) ETH_MDCCLKDIV_16;
    }
    else if (cpu1xClk <= 80u) {
        mdcClkDiv = (uint32) ETH_MDCCLKDIV_32;
    }
    else if (cpu1xClk <= 120u) {
        mdcClkDiv = (uint32) ETH_MDCCLKDIV_48;
    }
    else if (cpu1xClk <= 160u) {
        mdcClkDiv = (uint32) ETH_MDCCLKDIV_64;
    }
    else if (cpu1xClk <= 240u) {
        mdcClkDiv = (uint32) ETH_MDCCLKDIV_96;
    }
    else if (cpu1xClk <= 320u) {
        mdcClkDiv = (uint32) ETH_MDCCLKDIV_128;
    }
    else if (cpu1xClk <= 540u) {
        mdcClkDiv = (uint32) ETH_MDCCLKDIV_224;
    }
    else {
        /* Else do nothing, something wrong */
    }
    return mdcClkDiv;
    /*lint -restore*/
}

/**
 * Configures the MAC adress
 * @param macAdrs
 * @return none
 */
static void configureMacAdrs(uint8 hwUnit, const uint8* macAdrs) {
    uint32 Val;
    Gem_HwRegType *hwPtr = ETH_GET_HW_PTR(hwUnit);
    Val = 0uL;
    /*lint -save -e9033 -e9053*/
    /* Impermissible cast of composite expression (wider essential type for the destination
     * The shift value is at least the precision of the essential type of the left hand side
     * Misra is not happy with shifting u char and loading on to u int and ultimately with casting
     * Reasoning :: Autosar API is addressed by u character pointer and HW register is an u integer and has to be stored in the same manner
     */
    Val |= (uint32) macAdrs[0];
    Val |= ((uint32) macAdrs[1] << ETH_SHIFT_BYTE1);
    Val |= ((uint32) macAdrs[2] << ETH_SHIFT_BYTE2);
    Val |= ((uint32) macAdrs[3] << ETH_SHIFT_BYTE3);
    hwPtr->spec_addr1_bot = Val;
    Val = 0uL;
    Val |= (uint32) macAdrs[4];
    Val |= ((uint32) macAdrs[5] << ETH_SHIFT_BYTE1);
    /*lint -restore*/
    hwPtr->spec_addr1_top = Val;
}

/**
 * Activates/deactivates the Eth controller
 * @param active
 * @return E_OK: Action OK
 */
static Std_ReturnType setCommunicationMode(Eth_ModeType CtrlMode, uint8 CtrlIdx,
        uint8 EthHwUnit) {
    Std_ReturnType ret = E_OK;

    Gem_HwRegType *hwPtr = ETH_GET_HW_PTR(EthHwUnit);
    uint32 Val;

    switch (CtrlMode) {
        case ETH_MODE_ACTIVE:
            /*write start location of receive-buffer queue base address */
            hwPtr->rx_qbar = (uint32) EthCtrlUnit[CtrlIdx].pEthRxDescriptors; /*lint !e923 Intentional cast from pointer to integer,storing address   */
            /*write start location of transmit-buffer queue base address */
            hwPtr->tx_qbar = (uint32) EthCtrlUnit[CtrlIdx].pEthTxDescriptors; /*lint !e923 Intentional cast from pointer to integer,storing address   */
            /* Enable transmission and reception */
            /*clear interrupt status register before a fresh start */
            hwPtr->intr_status = ETH_GEM_INTR_MASK_ALL;
            if (0 == (hwPtr->net_ctrl & ETH_GEM_NWCTRL_TXEN)) {
                hwPtr->net_ctrl |= ETH_GEM_NWCTRL_TXEN;
            }
            if (0 == (hwPtr->net_ctrl & ETH_GEM_NWCTRL_RXEN)) {
                hwPtr->net_ctrl |= ETH_GEM_NWCTRL_RXEN;
            }
            break;

        case ETH_MODE_DOWN:
            /* Disable transmission and reception */
            hwPtr->net_ctrl &= ~ETH_GEM_NWCTRL_TXEN;
            hwPtr->net_ctrl &= ~ETH_GEM_NWCTRL_RXEN;
            /* clear DMA Receive andTransmit Queue Base Address Controls */
            hwPtr->rx_qbar = 0u;
            hwPtr->tx_qbar = 0u;
            /* Clear statuses of TX and RX if any */
            Val = hwPtr->rx_status;
            hwPtr->rx_status = Val;
            Val = hwPtr->tx_status;
            hwPtr->tx_status = Val;
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
static void initBuffers(const Eth_ControllerConfigType *CfgPtr, uint8 CtrlIdx) {
    uint32 nextDataIndex = 0u;
    /* Set up the buffer runtime variables */
    EthCtrlUnit[CtrlIdx].EthNextTxDescIdx = 0u;
    EthCtrlUnit[CtrlIdx].NextTxConfirmDescIndex = 0u;
    memset(EthCtrlUnit[CtrlIdx].EthTxDescriptorStatus, 0u,
            (sizeof(EthTxDescriptorStatusType) * ETH_FIND_TX_BUFFERS(CtrlIdx)));/*lint !e778 Constant expression evaluates to 0 in operation */
    /* constants used are not zero or ealuates to zero after operation */
    for (uint8 txBufIdx = 0; txBufIdx < CfgPtr->EthTxBufTotal; txBufIdx++) {
        EthCtrlUnit[CtrlIdx].EthTxBufferStatus[txBufIdx].locked = FALSE;
        EthCtrlUnit[CtrlIdx].EthTxBufferStatus[txBufIdx].dataPtr =
                &EthTxDataBuffer[(CfgPtr->EthCtrlIdx * ETH_TX_BUFFERMARKER)
                        + nextDataIndex];
        nextDataIndex = (CfgPtr->EthCtrlIdx * ETH_TX_BUFFERMARKER)
                + nextDataIndex
                + (uint32) (CfgPtr->EthCtrlTxBufLenByte
                        + (CfgPtr->EthCtrlTxBufLenByte % ETH_ALIGNING_BYTES));/*lint !e9033 !e778*/
        /* wider essential type for the destination - destination would not exceed the limit -
         * ASR restrictions are available too */
    }
}

/**
 * Resets rx and tx buffer
 * @return E_OK: Action OK
 */
static Std_ReturnType resetBuffers(const Eth_ControllerConfigType *CtrlCfgPtr,
        uint8 CtrlIdx) {

    volatile EthDescriptorType *pEthDescriptor =
            EthCtrlUnit[CtrlIdx].pEthTxDescriptors;
    for (uint8 txBufIdx = 0; txBufIdx < CtrlCfgPtr->EthTxBufTotal; txBufIdx++) {
        /*  write word 1 with used bit set, so no transmission*/
        pEthDescriptor[txBufIdx].Status |= ETH_GEM_TXBUF_USED;
    }
    pEthDescriptor = EthCtrlUnit[CtrlIdx].pEthRxDescriptors;
    for (uint8 rxBufIdx = 0; rxBufIdx < CtrlCfgPtr->EthRxBufTotal; rxBufIdx++) {
        /* Rx buffers are not used now */
        pEthDescriptor[rxBufIdx].Address &= ~ETH_GEM_RXBUF_USED;
        ;
    }
    /* Initialize buffer runtime data */
    initBuffers(CtrlCfgPtr, CtrlIdx);
    /*  Desc addresses are re loaded  */
    return E_OK ;
}

/**
 * Configures descriptors
 * @param CfgPtr
 * @param hwPtr
 */
static void configureDescriptors(const Eth_ControllerConfigType *CfgPtr) {
    uint32 Val;
    Gem_HwRegType *hwPtr = ETH_GET_HW_PTR(CfgPtr->EthHwUnit);
    /* Set the descriptor base addresses */
    /* assigned only when GEM is halted or not active */
    hwPtr->rx_qbar = (uint32) EthCtrlUnit[CfgPtr->EthCtrlIdx].pEthRxDescriptors; /*lint !e923 Intentional cast from pointer to integer,storing address   */
    /* assigned only when GEM is halted or not active */
    hwPtr->tx_qbar = (uint32) EthCtrlUnit[CfgPtr->EthCtrlIdx].pEthTxDescriptors; /*lint !e923 Intentional cast from pointer to integer,storing address   */
    volatile EthDescriptorType *pEthDescriptor =
            EthCtrlUnit[CfgPtr->EthCtrlIdx].pEthRxDescriptors;
    /* Setup buffer descriptor lists / chains */
    uint32 nextDataIndex = 0;
    for (uint8 rxBufIdx = 0; rxBufIdx < CfgPtr->EthRxBufTotal; rxBufIdx++) {
        pEthDescriptor[rxBufIdx].Address = 0uL;
        pEthDescriptor[rxBufIdx].Status = 0uL;
        /*  Used bit-Set bit 0 of word 0,Mark all entries in this list as owned by controller */
        pEthDescriptor[rxBufIdx].Address &= ~ETH_GEM_RXBUF_USED; /* no effect though */
        /* Write word 0 with the buffer address(bits 31-2, Word 0) */
        Val = (uint32) (pEthDescriptor[rxBufIdx].Address & ~0xFFFFFFFCU);
        pEthDescriptor[rxBufIdx].Address = Val
                | (uint32) (&EthRxDataBuffer[(CfgPtr->EthCtrlIdx
                        * ETH_RX_BUFFERMARKER) + nextDataIndex]);/*lint !e923 !e9033  Intentional cast from pointer to an unsigned integer for the address transfer */
        nextDataIndex = nextDataIndex
                + (uint32) (CfgPtr->EthCtrlRxBufLenByte
                        + (CfgPtr->EthCtrlRxBufLenByte % ETH_ALIGNING_BYTES));/*lint !e9033 destination would not exceed the limit */

        if ((CfgPtr->EthRxBufTotal - 1) == rxBufIdx) {
            /* Last one should be link */
            /*  write word 0 with wrap bit set, bit 1 in word 0 */
            pEthDescriptor[rxBufIdx].Address |= ETH_GEM_RXBUF_WRAP;
        }
    }
#if defined(CFG_ETH_TX_STATIC_BUF_ASSIGN)
    nextDataIndex = 0;
#endif
    pEthDescriptor = EthCtrlUnit[CfgPtr->EthCtrlIdx].pEthTxDescriptors;
    for (uint8 txBufIdx = 0; txBufIdx < CfgPtr->EthTxBufTotal; txBufIdx++) {
        /*  write word 1 with used bit set, so no transmission*/
        pEthDescriptor[txBufIdx].Status = ETH_GEM_TXBUF_USED;
#if defined(CFG_ETH_TX_STATIC_BUF_ASSIGN)
        /* Static buffer assignment to the descriptor */
        pEthDescriptor[txBufIdx].Address = (uint32)&EthTxDataBuffer[(CfgPtr->EthCtrlIdx * ETH_TX_BUFFERMARKER) + nextDataIndex];
        nextDataIndex = nextDataIndex + (uint32)(CfgPtr->EthCtrlTxBufLenByte + (CfgPtr->EthCtrlTxBufLenByte % ETH_ALIGNING_BYTES));
#endif
        /* Set Bit 15 (Last buffer bit) of  word 1, no options in ASR, just support Single frames */
        pEthDescriptor[txBufIdx].Status |= ETH_GEM_TXBUF_LAST;
        if (FALSE
                == EthCtrlUnit[CfgPtr->EthCtrlIdx].EthHwEnableTxChecksumOffload) {
            /* Set Bit 16  of word 1,no CRC by GEM, add checksum Offload mechanism in this case */
            pEthDescriptor[txBufIdx].Status |= ETH_GEM_TXBUF_NO_CRC;
        }
        /* Last one should be link */
        /* write word 1 with wrap bit set */
        if ((CfgPtr->EthTxBufTotal - 1) == txBufIdx) {
            pEthDescriptor[txBufIdx].Status |= ETH_GEM_TXBUF_WRAP;
        }
    }
}

/**
 * Configures the Eth controller
 * @param CtrlIdx
 * @param CfgPtr
 * @return E_OK: Configuration successful, E_NOT_OK: Configuration failed
 */
static Std_ReturnType configureController(
        const Eth_ControllerConfigType *CfgPtr) {
    Std_ReturnType ret = E_OK;
    uint32 Val;
    uint32 RxBufSize;
    uint32 mdcClkDiv;
    Gem_HwRegType *hwPtr = ETH_GET_HW_PTR(CfgPtr->EthHwUnit);
    EthCtrlUnit[CfgPtr->EthCtrlIdx].EthHwUnit = CfgPtr->EthHwUnit;
    EthCtrlUnit[CfgPtr->EthCtrlIdx].EthHwEnableRxChecksumOffload =
            CfgPtr->EthHwEnableRxChecksumOffload;
    EthCtrlUnit[CfgPtr->EthCtrlIdx].EthHwEnableTxChecksumOffload =
            CfgPtr->EthHwEnableTxChecksumOffload;
    EthCtrlUnit[CfgPtr->EthCtrlIdx].EthHwCtrlDiscardRxFCS =
            CfgPtr->EthHwCtrlDiscardRxFCS;
    EthCtrlUnit[CfgPtr->EthCtrlIdx].EthRxBufTotal = CfgPtr->EthRxBufTotal;
    EthCtrlUnit[CfgPtr->EthCtrlIdx].EthTxBufTotal = CfgPtr->EthTxBufTotal;
    hwPtr->intr_dis = ETH_GEM_INTR_MASK_ALL; /* Disable all the interrupts */
    hwPtr->intr_status = ETH_GEM_INTR_MASK_ALL; /*clear interrupt status register before a fresh start */
    hwPtr->tx_status = 0u; /* clear Tx status values */
    hwPtr->rx_status = 0u; /* clear Rx status values */
    hwPtr->net_cfg = 0u;
    hwPtr->phy_maint = 0u; /* PHY maintainance register initialization */
    hwPtr->net_ctrl = ETH_GEM_NWCTRL_MDEN;
    hwPtr->net_ctrl |= ETH_GEM_NWCTRL_STATCLR;
    RxBufSize = (uint32) ((CfgPtr->EthCtrlRxBufLenByte / 64u)
            + (((CfgPtr->EthCtrlRxBufLenByte % 64u) != 0 )? 1 : 0)) << 16u;/*lint !e9032 expression does not lead to harmness */
    /* Initial Config- copied to single buffer always, no scatter and gather functionality */
    /*RxBufSize = ( 1600u / 64u ) << 16u;   */
    hwPtr->dma_cfg = ETH_GEM_DMACR_RXSIZE;
    hwPtr->dma_cfg |= ETH_GEM_DMACR_TXSIZE;
    hwPtr->dma_cfg |= (RxBufSize & ETH_GEM_DMACR_RXBUF_MASK);
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)  /* ISR routine is combined for both TX and RX */
    if ((TRUE == CfgPtr->EthCtrlEnableRxInterrupt)
            || (TRUE == CfgPtr->EthCtrlEnableTxInterrupt)) {
#if (ETH_USE_HW_UNIT_0 == STD_ON )
        INSTALL_HANDLER(0,IRQ_ETH_0); /*lint !e9036 Conditional expression should have essentially Boolean type - No harmness*/
#endif
#if (ETH_USE_HW_UNIT_1 == STD_ON )
        INSTALL_HANDLER(1,IRQ_ETH_1); /*lint !e9036 Conditional expression should have essentially Boolean type - No harmness*/
#endif
    }
#endif
#if defined(CFG_ETH_LOOPBACK)
    hwPtr->net_ctrl |= ETH_GEM_NWCTRL_LOOPEN;
#else
    hwPtr->net_ctrl &= ~ETH_GEM_NWCTRL_LOOPEN;
#endif
    hwPtr->net_cfg &= ~ETH_GEM_NWCFG_1000; /* Disable Gigabit operation using GMII or TBI interface - ASR compliant */
    if (CfgPtr->EthHwSpeed == MBPS_100) { /* 10/100 operation using MII or TBI interface - ASR allows only this */
        hwPtr->net_cfg |= ETH_GEM_NWCFG_SPEED;
    }
    else {
        hwPtr->net_cfg &= ~ETH_GEM_NWCFG_SPEED; /* default - 10MBPS */
    }
    hwPtr->net_cfg |= ETH_GEM_NWCFG_FDEN; /* Full duplex - is config needed for this */
    configureMacAdrs(CfgPtr->EthHwUnit, CfgPtr->EthCtrlPhyAddress); /* Configure MAC address */
    if (TRUE == EthCtrlUnit[CfgPtr->EthCtrlIdx].EthHwCtrlDiscardRxFCS) {
        hwPtr->net_cfg |= ETH_GEM_NWCFG_FCSREM; /* FCS discard mode enable */
    }
    hwPtr->net_cfg |= ETH_GEM_NWCFG_PAUSEEN; /* Pause enable bit is set for the FC mechanism,TX will be halted during pause frame handling */
    /* @req 4.1.2/SWS_Eth_00146 *//* Hardware filtering is available and hence there is no promiscous mode set */
#if 0                                   /* enabling the incoming frames with broadcast address to be  stored - special case of multicast.*/
    hwPtr->net_cfg &= (~ETH_GEM_NWCFG_BCASTDI);
#endif
    hwPtr->net_cfg |= ETH_GEM_NWCFG_LENGTHERRDSCRD;
#if 0	                                                   /* ASR requirement - up to 1522 bytes */
    hwPtr->net_cfg |= ETH_GEM_NWCFG_1536RXEN; /* allow up to 1536 bytes RX, else it will reject frames after 1518 bytes */
#endif
    if (TRUE == EthCtrlUnit[CfgPtr->EthCtrlIdx].EthHwEnableRxChecksumOffload) {
        hwPtr->net_cfg |= ETH_GEM_NWCFG_RXCHKSUMEN; /* Enable RX checksum offload */
    }
    if (TRUE == EthCtrlUnit[CfgPtr->EthCtrlIdx].EthHwEnableTxChecksumOffload) {
        hwPtr->dma_cfg |= ETH_GEM_DMACR_TCPCKSUM; /* Enable TX checksum offload */
    }
    hwPtr->dma_cfg |= ETH_GEM_DMACR_BLENGTH; /*Attempt to use INCR16 AHB bursts otherwise single AHB bursts are used */
    configureDescriptors(CfgPtr); /* Configure descriptors */
    Val = hwPtr->net_cfg;
    Val &= ~ETH_GEM_NWCFG_MDCCLKDIV_MASK;
    mdcClkDiv = getMdcClkDiv(); /* Set MDC */
    hwPtr->net_cfg = (Val | (mdcClkDiv << 18u));
    /*  Enable TX and RX interrupts, selected ones as below */
    if (TRUE == CfgPtr->EthCtrlEnableRxInterrupt) {
        hwPtr->intr_en = (ETH_GEM_IXR_ALL & ETH_GEM_IXR_FRAMERX);
        hwPtr->intr_en |= (ETH_GEM_IXR_ALL & ETH_GEM_IXR_RXUSED);
        hwPtr->intr_en |= (ETH_GEM_IXR_ALL & ETH_GEM_IXR_RXOVR);
        hwPtr->intr_en |= (ETH_GEM_IXR_ALL & ETH_GEM_IXR_HRESPNOK);
    }
    if (TRUE == CfgPtr->EthCtrlEnableTxInterrupt) {
        hwPtr->intr_en |= (ETH_GEM_IXR_ALL & ETH_GEM_IXR_TXCOMPL);
        hwPtr->intr_en |= (ETH_GEM_IXR_ALL & ETH_GEM_IXR_TXUSED);
        hwPtr->intr_en |= (ETH_GEM_IXR_ALL & ETH_GEM_IXR_TXEXH);
        hwPtr->intr_en |= (ETH_GEM_IXR_ALL & ETH_GEM_IXR_URUN);
    }
    return ret;
}

/**
 * Inserts Ethernet header in a data buffer
 * @param CtrlCfgPtr
 * @param PhysAddrPtr
 * @param dataPtr
 */
static void insertEthHeader(const Eth_ControllerConfigType *CtrlCfgPtr,
        const uint8* PhysAddrPtr, uint8* dataPtr, Eth_FrameType FrameType) {
    uint8 i;
    /* Dest MAC */
    for (i=0; i < ETH_MAC_ADDR_SIZE; i++){
        dataPtr[ETH_MAC_DST_ADDR_START_INDEX+i] =  PhysAddrPtr[i]; /*lint !e835*/ /*A zero has been given as left argument */
    }
    /* Src MAC */
    for (i=0; i < ETH_MAC_ADDR_SIZE; i++){
           dataPtr[ETH_MAC_SRC_ADDR_START_INDEX+i] =  CtrlCfgPtr->EthCtrlPhyAddress[i];
    }
    /* Ethernet type */
    dataPtr[ETH_ETHERNETTYPE_START_INDEX] = (uint8) ((FrameType
            >> ETH_SHIFT_BYTE1) & 0xFFu);
    dataPtr[ETH_ETHERNETTYPE_START_INDEX + 1] = (uint8) (FrameType & 0xFFu);
}

/**
 * Check if data has been received
 * @param CtrlIdx
 * @return boolean
 */
static Eth_RxStatusType isRxDatAvailable(uint8 CtrlIdx) {
    const volatile EthDescriptorType *pEthRxDescriptor =
            EthCtrlUnit[CtrlIdx].pEthRxDescriptors;
    Eth_RxStatusType rxStatus = ETH_NOT_RECEIVED;
    for (volatile uint8 i = 0; i < EthCtrlUnit[CtrlIdx].EthRxBufTotal; i++) {
        if ((pEthRxDescriptor[i].Address & ETH_GEM_RXBUF_USED) != 0) {
            if (rxStatus == ETH_NOT_RECEIVED) {
                rxStatus = ETH_RECEIVED;
            }
            else if (rxStatus == ETH_RECEIVED) {
                rxStatus = ETH_RECEIVED_MORE_DATA_AVAILABLE;
            }
            else {
                /* Do nothing */
            }
            if (EthCtrlUnit[CtrlIdx].EthFrameLost == TRUE) {
                if (rxStatus != ETH_NOT_RECEIVED) {
                    rxStatus = ETH_RECEIVED_FRAMES_LOST;
                }
                /* @req 4.1.2/SWS_Eth_00155 */
                DET_REPORT_ERROR(ETH_RECEIVE_ID,ETH_E_FRAMES_LOST);
                EthCtrlUnit[CtrlIdx].EthFrameLost = FALSE;
            }
        }
    }
    return rxStatus;
}
///////////////////////////////////////////////////////////////////////////////////////////
/// ........................ETH static functions end .....................
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
/// ........................ETH HW APIS  start ....................................
///////////////////////////////////////////////////////////////////////////////////////////
/**
 * Initializes Ethernet hw module
 * @param CfgPtr
 */
void Eth_Hw_Init(const Eth_ConfigType* CfgPtr) {
    (void) CfgPtr;/*lint !e920 */
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

    /* no reset mode */

    /* no config mode */

    /* Disable controller */
    if (E_OK
            != setCommunicationMode(ETH_MODE_DOWN, CtrlIdx,
                    CtrlCfgPtr->EthHwUnit)) {
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
 * TX-RX ISR for GEM0/1 data interrupt
 */
/* !req 4.1.2/SWS_Eth_00114 *//* !req 4.0.3/ETH114 */
void Eth_TxRxIrqHdlr(uint8 HwUnit) {
    /* !req 4.1.2/SWS_Eth_00111 *//* !req 4.0.3/ETH111 */
    /* !req 4.1.2/SWS_Eth_00116 *//* !req 4.0.3/ETH116 */
    uint32 ievent;
    uint8 ctrldx;
    Gem_HwRegType *hwPtr = ETH_GET_HW_PTR(HwUnit);
    ievent = hwPtr->intr_status;
    hwPtr->intr_status = ievent;
    ctrldx = getCtrldx(HwUnit);
    if (0 != (ievent & ETH_GEM_IXR_FRAMERX)) {
        /* @req 4.1.2/SWS_Eth_00110 *//* @req 4.0.3/ETH110 */
        /*  clear events */
        hwPtr->rx_status = ETH_GEM_RXSR_FRAMERX;
        /* clear this as well */
        hwPtr->rx_status = ETH_GEM_RXSR_BUFFNA;
        Eth_Hw_Receive(getCtrldx(HwUnit), NULL);
#if defined(CFG_ETH_ARC_STATISTICS)
        EthStatistics.RxInterptCnt++;
#endif
    }
    /* Check events */
    /*  TX complete */
    if (0 != (ievent & ETH_GEM_IXR_TXCOMPL)) {
        /* @req 4.1.2/SWS_Eth_00115 *//* @req 4.0.3/ETH115 */
        /*  clear events */
        hwPtr->tx_status = ETH_GEM_TXSR_TXCOMPL;
        /* clear this as well */
        hwPtr->tx_status = ETH_GEM_TXSR_USEDREAD;
        /* halt transmission */
        hwPtr->net_ctrl |= ETH_GEM_NWCTRL_HALTTX;
        Eth_Hw_TxConfirmation(ctrldx);
#if defined(CFG_ETH_ARC_STATISTICS)
        EthStatistics.TxInterptCnt++;
#endif
    }
    /* Error handling */
    if (0 != (ievent & ( ETH_GEM_IXR_RXUSED | ETH_GEM_IXR_RXOVR))) {
        uint32 Val;
        Val = hwPtr->rx_status;
        hwPtr->rx_status = Val;
        hwPtr->net_ctrl |= ETH_GEM_NWCTRL_FLUSH_NXT_RX_DPRAM;
        /* The received packets will remain to be (disc_when_no_ahb = 0)
        stored in the SRAM based packet buffer until
        AHB buffer resource next becomes available ,
        so ETH_GEM_IXR_RXUSED bit is an indication not an error */
        if(0 != (ievent & ETH_GEM_IXR_RXOVR)){
            EthCtrlUnit[getCtrldx(HwUnit)].EthFrameLost = TRUE;
        }
    }
    /* severe error, assumed will not happen
        For safety the error status is cleared in order to recover without restarting GEM TX,
        this happens usually when DMA cannot be able to read data from system memory or
        both descriptors and AHB buffers are in cached memory */
    if (0 != (ievent & ETH_GEM_IXR_TXEXH )) {
        hwPtr->tx_status = ETH_GEM_TXSR_BUFEXH;
    }
}

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
    uint32 reg;
    uint32 phy;
    Std_ReturnType ret;
    volatile struct GEM_reg * hwPtr = ETH_GET_HW_PTR(CtrlCfgPtr->EthHwUnit);/*lint !e923 Intentional cast from integer literal HW register address to pointer */
    /* check if already busy state for some reasons */
    if ((hwPtr->net_status & ETH_GEM_NETSTATUS_MGMT_IDLE) == 0u) {
        BUSY_WAIT_A_WHILE(&hwPtr->net_status, ETH_GEM_NETSTATUS_MGMT_IDLE,
                    ETH_GEM_NETSTATUS_MGMT_IDLE, &ret);
        if(ret != E_OK){
            return ret; /* Some problem */
        }
    }
    reg = (uint32) RegIdx << 18u;
    phy = (uint32) TrcvIdx << 23u;
    hwPtr->phy_maint = (ETH_MII_DATA_ST | ETH_MII_DATA_OP_WR | ETH_MII_DATA_TA
            | phy | reg | RegVal);
    BUSY_WAIT_A_WHILE(&hwPtr->net_status, ETH_GEM_NETSTATUS_MGMT_IDLE,
            ETH_GEM_NETSTATUS_MGMT_IDLE, &ret);
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
    uint32 reg;
    uint32 phy;
    Std_ReturnType ret;
    Gem_HwRegType *hwPtr = ETH_GET_HW_PTR(CtrlCfgPtr->EthHwUnit);
    /* check if already busy state for some reasons */
    if ((hwPtr->net_status & ETH_GEM_NETSTATUS_MGMT_IDLE) == 0u) {
        BUSY_WAIT_A_WHILE(&hwPtr->net_status, ETH_GEM_NETSTATUS_MGMT_IDLE,
                    ETH_GEM_NETSTATUS_MGMT_IDLE, &ret);
        if(ret != E_OK){
            return ret; /* Some problem */
        }
    }
    reg = (uint32) RegIdx << 18u;
    phy = (uint32) TrcvIdx << 23u;
    hwPtr->phy_maint = (ETH_MII_DATA_ST | ETH_MII_DATA_OP_RD | ETH_MII_DATA_TA
            | phy | reg);
    BUSY_WAIT_A_WHILE(&hwPtr->net_status, ETH_GEM_NETSTATUS_MGMT_IDLE,
            ETH_GEM_NETSTATUS_MGMT_IDLE, &ret);
    *RegVal = (uint16) hwPtr->phy_maint;
    return ret;
}

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
                    != setCommunicationMode(ETH_MODE_ACTIVE, CtrlIdx,
                            CtrlCfgPtr->EthHwUnit)) {
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
            if (E_OK
                    != setCommunicationMode(ETH_MODE_DOWN, CtrlIdx,
                            CtrlCfgPtr->EthHwUnit)) {
                ret = E_NOT_OK;
            }
            /* @req 4.1.2/SWS_Eth_00137 *//* @req 4.0.3/ETH137 */
            /* @req 4.1.2/SWS_Eth_00138 *//* @req 4.0.3/ETH138 */
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
    Gem_HwRegType *hwPtr = ETH_GET_HW_PTR(CtrlCfgPtr->EthHwUnit);
    Std_ReturnType ret = E_OK;
    uint32 addrs1 = 0;
    uint32 addrs2 = 0;
    /* Little endian */
    /*lint -save -e9033 -e9053 */
    /* Impermissible cast of composite expression (wider essential type for the destination
     * The shift value is at least the precision of the essential type of the left hand side
     * Misra is not happy with shifting u char and loading on to u int and ultimately with casting
     * Reasoning :: Autosar API is addressed by u character pointer and HW register is an u integer and has to be stored in the same manner
     */
    addrs1 |= (uint32) PhysAddrPtr[0];
    addrs1 |= ((uint32) PhysAddrPtr[1] << ETH_SHIFT_BYTE1);
    addrs1 |= ((uint32) PhysAddrPtr[2] << ETH_SHIFT_BYTE2);
    addrs1 |= ((uint32) PhysAddrPtr[3] << ETH_SHIFT_BYTE3);
    addrs2 |= (uint32) PhysAddrPtr[4];
    addrs2 |= ((uint32) PhysAddrPtr[5] << ETH_SHIFT_BYTE1);
    /*lint -restore*/
    if (ETH_ADD_TO_FILTER == Action) {
        if ((addrs1 == 0u) && (addrs2 == 0u)) {
            /* !req 4.1.2/SWS_Eth_00147 */
            /* Receive unicast hash frames -The first bit of the destination address is zero */
            hwPtr->net_cfg &= ETH_GEM_NWCFG_COPYALLEN; /* end this mode */
            hwPtr->net_cfg |= ETH_GEM_NWCFG_UCASTHASHEN;
        }
        else if ((addrs1 == 0xFFFFFFFFu) && (addrs2 == 0x0000FFFFu)) {
            /* @req 4.1.2/SWS_Eth_00144 */
            /* open the filter completely */
            hwPtr->net_cfg |= ETH_GEM_NWCFG_COPYALLEN;

            /* Adding same filter multiple times are needed to be taken care by upper layers */
        }
        else if (EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthFrameFilterCount
                < (ETH_MAX_MAC_ADRS_SPACE - 1)) {
            if ((hwPtr->spec_addr2_bot == 0uL)
                    && (hwPtr->spec_addr2_top == 0uL)) { /*lint !e9007 side effects on right hand of logical operator, ''&&'*/
                hwPtr->spec_addr2_bot = addrs1;
                hwPtr->spec_addr2_top = addrs2;
                EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthFrameFilterCount++;
            }
            else if ((hwPtr->spec_addr3_bot == 0uL)
                    && (hwPtr->spec_addr3_top == 0uL)) {/*lint !e9007 side effects on right hand of logical operator, ''&&'*/
                hwPtr->spec_addr3_bot = addrs1;
                hwPtr->spec_addr3_top = addrs2;
                EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthFrameFilterCount++;
            }
            else if ((hwPtr->spec_addr4_bot == 0uL)
                    && (hwPtr->spec_addr4_top == 0uL)) {/*lint !e9007 side effects on right hand of logical operator, ''&&'*/
                hwPtr->spec_addr4_bot = addrs1;
                hwPtr->spec_addr4_top = addrs2;
                EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthFrameFilterCount++;
            }
            else {
                ret = E_NOT_OK;
            }
        }
        else {
            /* no space for additional frame filter address */
            ret = E_NOT_OK;
        }
    }
    else {
        if ((addrs1 == 0u) && (addrs2 == 0u)) {
            ret = E_NOT_OK;
        }
        if (addrs1 == hwPtr->spec_addr2_bot) {
            if (addrs2 == hwPtr->spec_addr2_top) {
                hwPtr->spec_addr2_bot = 0u;
                hwPtr->spec_addr2_top = 0u;
                EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthFrameFilterCount--;
            }
        }
        if (addrs1 == hwPtr->spec_addr3_bot) {
            if (addrs2 == hwPtr->spec_addr3_top) {
                hwPtr->spec_addr3_bot = 0u;
                hwPtr->spec_addr3_top = 0u;
                EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthFrameFilterCount--;
            }
        }
        if (addrs1 == hwPtr->spec_addr4_bot) {
            if (addrs2 == hwPtr->spec_addr4_top) {
                hwPtr->spec_addr4_bot = 0u;
                hwPtr->spec_addr4_top = 0u;
                EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthFrameFilterCount--;
            }
        }
        else {
            ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * Reads MAC address from Hw
 * @param CtrlIdx
 * @param PhysAddrPtr
 */
void Eth_Hw_GetPhysAddr(const Eth_ControllerConfigType *CtrlCfgPtr,
        uint8* PhysAddrPtr) {
    VALIDATE_HW_NO_RV(CtrlCfgPtr->EthHwUnit, ETH_GLOBAL_ID,
            ETH_E_CONFIG_INVALID);
    const Gem_HwRegType *hwPtr = ETH_GET_HW_PTR(CtrlCfgPtr->EthHwUnit);
    /* Little endian */

    uint32 temp = (uint32) hwPtr->spec_addr1_bot;
    PhysAddrPtr[3] = (uint8) ((temp >> ETH_SHIFT_BYTE3) & 0xFFu);
    PhysAddrPtr[2] = (uint8) ((temp >> ETH_SHIFT_BYTE2) & 0xFFu);
    PhysAddrPtr[1] = (uint8) ((temp >> ETH_SHIFT_BYTE1) & 0xFFu);
    PhysAddrPtr[0] = (uint8) (temp & 0xFFu);
    temp = (uint32) hwPtr->spec_addr1_top;
    PhysAddrPtr[5] = (uint8) ((temp >> ETH_SHIFT_BYTE1) & 0xFFu);
    PhysAddrPtr[4] = (uint8) (temp & 0xFFu);
}

/**
 * Sets the MAC address of the Hw,Reentrant function
 * @param CtrlIdx
 * @param PhysAddrPtr
 */
void Eth_Hw_SetPhysAddr(const Eth_ControllerConfigType *CtrlCfgPtr,
        const uint8* PhysAddrPtr) {
    VALIDATE_HW_NO_RV(CtrlCfgPtr->EthHwUnit, ETH_GLOBAL_ID,
            ETH_E_CONFIG_INVALID);
    configureMacAdrs(CtrlCfgPtr->EthHwUnit, PhysAddrPtr);
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
    /* @req 4.1.2/SWS_Eth_00078 *//* @req 4.0.3/ETH078 */
    /* @req 4.1.2/SWS_Eth_00080 *//* @req 4.0.3/ETH080 */
    BufReq_ReturnType ret = BUFREQ_E_BUSY;
    VALIDATE_HW_RV(CtrlCfgPtr->EthHwUnit, ETH_GLOBAL_ID, ETH_E_CONFIG_INVALID,
            BUFREQ_E_NOT_OK);
    /* Find a free buffer */

    for (Eth_BufIdxType bufIndex = 0;
            ((bufIndex < CtrlCfgPtr->EthTxBufTotal) && (BUFREQ_E_BUSY == ret));
            bufIndex++) {
    	SchM_Enter_Eth_EA_0();
        if ( FALSE
                == EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[bufIndex].locked) {
            if (*LenBytePtr
                    > ((uint16) CtrlCfgPtr->EthCtrlTxBufLenByte
                            - ETH_HEADER_SIZE)) {
                /* @req 4.1.2/SWS_Eth_00079 *//* !req 4.0.3/ETH079 */
                ret = BUFREQ_E_OVFL;
                *LenBytePtr = (uint16) CtrlCfgPtr->EthCtrlTxBufLenByte - ETH_HEADER_SIZE;
            }
            else {
                EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[bufIndex].locked =
                        TRUE;
                *BufIdxPtr = bufIndex;
                *BufPtr =
                        &EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[bufIndex].dataPtr[ETH_HEADER_SIZE];
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
    if ( FALSE
            == EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[BufIdx].locked) {
        /* Trying to transmit using a buffer not provided */
        return E_NOT_OK ;
    }
    if (LenByte > (CtrlCfgPtr->EthCtrlTxBufLenByte - ETH_HEADER_SIZE)) {
        return E_NOT_OK ;
    }

    Gem_HwRegType *hwPtr = ETH_GET_HW_PTR(CtrlCfgPtr->EthHwUnit);
    uint32 Val;

    /* Check if the next descriptor in the chain is available*/
    Std_ReturnType ret = E_NOT_OK;
    SchM_Enter_Eth_EA_0();
    uint32 BdAddr = hwPtr->tx_qbar;
    volatile EthDescriptorType *pEthTxDescriptor = (EthDescriptorType*) BdAddr;/*lint !e923 Intentional cast from an unsigned integer holding address to a pointer holding register address*/
    if ((pEthTxDescriptor->Status & ETH_GEM_TXBUF_USED) != 0) {
#if !defined(CFG_ETH_TX_STATIC_BUF_ASSIGN)
        /*  Dynamic linking of an individual buffer to the descriptor */
        pEthTxDescriptor->Address =
                (uint32) EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[BufIdx].dataPtr;/*lint !e923 Intentional cast from pointer to integer literal HW register address*/
#endif
        /* This descriptor can be used */
        /* @req 4.1.2/SWS_Eth_00088 *//* @req 4.0.3/ETH088 */
        insertEthHeader(CtrlCfgPtr, PhysAddrPtr,
                EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[BufIdx].dataPtr,
                FrameType);
        Val = pEthTxDescriptor->Status;
        Val = (Val & ~ETH_GEM_TXBUF_LENGTH_MASK)
                | ((uint32) LenByte + ETH_HEADER_SIZE);
        /* write size */
        pEthTxDescriptor->Status = Val;
        if (FALSE
                == EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthHwEnableTxChecksumOffload) {
            /* set customised FCS field instead */
            /* When 16 bit of word 1 is set this implies that the data in the buffers already contains
             a valid CRC and hence no CRC or padding is to be appended to the current frame by the MAC,
             offload enable - it shud be 0 */
            pEthTxDescriptor->Status |= ETH_GEM_TXBUF_NO_CRC;
        }
        EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxDescriptorStatus[EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx].TxBufferIdx =
                BufIdx;
        /* @req 4.1.2/SWS_Eth_00089 *//* @req 4.0.3/ETH089 */
        /* releasing or locking depending up on Txconfirmation request */
        EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[BufIdx].locked =
                TxConfirmation;
        if (TxConfirmation) {
            EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxDescriptorStatus[EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx].TxState =
                    ETH_TX_DESC_TX_REQUESTED_CONFIRM;
        }
        else {
            EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxDescriptorStatus[EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx].TxState =
                    ETH_TX_DESC_TX_REQUESTED_NO_CONFIRM;
        }
        /*  flush buffers here... */
        /*	The buffer that contains the Ethernet frame data should be flushed from cache if cached
         memory is being used */

        /* Issue transmit request for the queue */
        /*  clear 31st bit of word 1, so transmission */
        pEthTxDescriptor->Status &= ~ETH_GEM_TXBUF_USED;
        /*  start transmitting the frame */
        hwPtr->net_ctrl |= ETH_GEM_NWCTRL_STARTTX;
        EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx =
                (EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthNextTxDescIdx + 1)
                        % CtrlCfgPtr->EthTxBufTotal;
        ret = E_OK;
    }
    else {
        /* No descriptor available. Something wrong or something wrong with HW controller- error handling*/
        EthCtrlUnit[CtrlCfgPtr->EthCtrlIdx].EthTxBufferStatus[BufIdx].locked =
                FALSE;
        DET_REPORT_ERROR(ETH_GLOBAL_ID, ETH_E_GENERAL_ERROR);
    }
    SchM_Exit_Eth_EA_0();
    return ret;
}

/**
 * Triggers frame transmission confirmation
 * @param CtrlIdx
 */
void Eth_Hw_TxConfirmation(uint8 CtrlIdx) {
    /* @req 4.1.2/SWS_Eth_00101 *//* @req 4.0.3/ETH101 */
    const volatile EthDescriptorType *pEthTxDescriptor =
            EthCtrlUnit[CtrlIdx].pEthTxDescriptors;
    for (volatile uint8 indx = 0; indx < EthCtrlUnit[CtrlIdx].EthTxBufTotal;
            indx++) {
    	SchM_Enter_Eth_EA_0(); //basically when in TX polling
        if (((pEthTxDescriptor[indx].Status & ETH_GEM_TXBUF_USED) != 0)
                && (ETH_TX_DESC_IDLE
                        != EthCtrlUnit[CtrlIdx].EthTxDescriptorStatus[EthCtrlUnit[CtrlIdx].NextTxConfirmDescIndex].TxState)) {
            if (ETH_TX_DESC_TX_REQUESTED_CONFIRM
                    == EthCtrlUnit[CtrlIdx].EthTxDescriptorStatus[EthCtrlUnit[CtrlIdx].NextTxConfirmDescIndex].TxState) {
                EthIf_TxConfirmation(CtrlIdx,
                        EthCtrlUnit[CtrlIdx].EthTxDescriptorStatus[EthCtrlUnit[CtrlIdx].NextTxConfirmDescIndex].TxBufferIdx);
                /* @req 4.1.2/SWS_Eth_00102 *//* @req 4.0.3/ETH102 */
                EthCtrlUnit[CtrlIdx].EthTxBufferStatus[EthCtrlUnit[CtrlIdx].EthTxDescriptorStatus[EthCtrlUnit[CtrlIdx].NextTxConfirmDescIndex].TxBufferIdx].locked =
                        FALSE;
            }
            EthCtrlUnit[CtrlIdx].EthTxDescriptorStatus[EthCtrlUnit[CtrlIdx].NextTxConfirmDescIndex].TxState =
                    ETH_TX_DESC_IDLE;
            EthCtrlUnit[CtrlIdx].NextTxConfirmDescIndex =
                    (EthCtrlUnit[CtrlIdx].NextTxConfirmDescIndex + 1)
                            % ETH_FIND_TX_BUFFERS(CtrlIdx);/*lint !e414 !e778 constant experession will not turn zero, taken care accordingly */
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
    Eth_RxStatusType rxStatus;
    uint8 nextRxDescIndex;
    rxStatus = isRxDatAvailable(CtrlIdx); /* for polling method */
    if (RxStatusPtr != NULL) {
        *RxStatusPtr = rxStatus;
    }
    if (ETH_NOT_RECEIVED != rxStatus) {
        /* @req 4.1.2/SWS_Eth_00096 *//* @req 4.0.3/ETH096 */
        volatile EthDescriptorType *pEthRxDescriptor =
                EthCtrlUnit[CtrlIdx].pEthRxDescriptors;
        for (nextRxDescIndex = 0;
                nextRxDescIndex < EthCtrlUnit[CtrlIdx].EthRxBufTotal;
                nextRxDescIndex++) {
            if ((pEthRxDescriptor[nextRxDescIndex].Address & ETH_GEM_RXBUF_USED)
                    != 0) {
                if ( ETH_GEM_RXBUF_FRAME_SINGLE
                        == (pEthRxDescriptor[nextRxDescIndex].Status
                                & ETH_GEM_RXBUF_FRAME_SINGLE)) {
                    uint8* framePtr =
                            (uint8*) (pEthRxDescriptor[nextRxDescIndex].Address
                                    & ETH_GEM_RXBUF_ADDRESS_MASK);/*lint !e923 !e9033 Intentional cast from unsigned integer holding address to a pointer holding register address */
                    Eth_FrameType frameType = 0u;
                    boolean isBroadcast = TRUE;
                    /* @req 4.1.2/SWS_Eth_000153 */
                    for (uint8 i = 0; (i < ETH_MAC_ADDR_SIZE) && isBroadcast;
                            i++) {
                        if (ETH_BROADCAST_BYTE != framePtr[i]) {
                            isBroadcast = FALSE;
                        }
                    }
                    frameType |=
                            (Eth_FrameType) framePtr[ETH_ETHERNETTYPE_START_INDEX]
                                    << ETH_SHIFT_BYTE1;/*lint !e9033 no harm in shifting from Autosar defined byte pointers*/
                    frameType |=
                            (Eth_FrameType) framePtr[ETH_ETHERNETTYPE_START_INDEX
                                    + 1];/*lint !e9033 no harm in taking the byte pointer*/
                    /* The function shall be callable on interrupt level */
                    EthIf_RxIndication(CtrlIdx, frameType, isBroadcast,
                            &framePtr[ETH_MAC_SRC_ADDR_START_INDEX],
                            &framePtr[ETH_HEADER_SIZE],
                            (uint16) ((pEthRxDescriptor[nextRxDescIndex].Status
                                    & ETH_GEM_RXBUF_LENGTH_MASK)
                                    - ETH_HEADER_SIZE));
                    pEthRxDescriptor[nextRxDescIndex].Address &=
                            ~ETH_GEM_RXBUF_USED;
                    break;
                    /*  consecutive frame */
                }
                else if (ETH_GEM_RXBUF_FRAME_START
                        == (pEthRxDescriptor[nextRxDescIndex].Status
                                & ETH_GEM_RXBUF_FRAME_SINGLE)) {
                    /* No support for split frames */
                    DET_REPORT_ERROR(ETH_GLOBAL_ID, ETH_E_GENERAL_ERROR);
                    /*  consecutive frame */
                }
                else if (ETH_GEM_RXBUF_FRAME_END
                        == (pEthRxDescriptor[nextRxDescIndex].Status
                                & ETH_GEM_RXBUF_FRAME_SINGLE)) {
                    /* No support for split frames */
                    DET_REPORT_ERROR(ETH_GLOBAL_ID, ETH_E_GENERAL_ERROR);
                }
                else {
                    /* Unsupported frame */
                }
            }
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
/// ........................ETH HW APIS  end ....................................
///////////////////////////////////////////////////////////////////////////////////////////

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

