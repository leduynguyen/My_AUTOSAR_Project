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

/* ----------------------------[information]----------------------------------*/
/*
 *
 *
 * Description:
 *   Implementation of the Can Driver module
 *
 * Limitations:
 *   General                        Information
 *   -------------------------------------------
 *   CAN_HW_TRANSMIT_CANCELLATION   This API is not supported.
 *   CAN_IDENTICAL_ID_CANCELLATION  This API is not supported.
 *   CAN_INDEX                      This API is not supported.
 *   CAN_MULTIPLEXED_TRANSMISSION   This API is not supported.
 *   CAN_TIMEOUT_DURATION           This API is not supported.
 *
 *   CAN_CPU_CLOCK_REFERENCE        It assumes that there is a PERIPHERAL clock defined.
 *
 *   CanWakeupSourceRef             Config generator does not provide CanWakeupSourceRef value.
 *
 *   Tx High Priority Buffer        This hardware feature is currently not used.
 *   Rx High Priority Buffer        This hardware feature is currently not used.
 *   Acceptance Filters             This hardware feature is currently not used. CanId filtering is solved by software.
 *
 *
 */

/* General requirements */
/** @req 4.1.2/SWS_Can_00237 *//* No transmit triggered by RTR */
/** @req 4.1.2/SWS_Can_00236 *//* No transmit triggered by RTR */
/** @req 4.1.2/SWS_Can_00238 *//* On-chip controller, does not use other drivers */
/** @req 4.1.2/SWS_Can_00401 *//* Multiple mbs per HTH */
/** @req 4.1.2/SWS_Can_00402 *//* Multiplexed transmission, possible to identify free mb */
/** @req 4.1.2/SWS_Can_00220 *//* Precompile variant */
/** @req 4.1.2/SWS_Can_00035 *//* No callbacks */
/** @req 4.1.2/SWS_Can_00413 *//* Can_ConfigType */
/** @req 4.1.2/SWS_Can_00079 *//* Coding guidelines (compiler abstraction not used)*/
/** @req 4.1.2/SWS_Can_00007 *//* Complete polling configurable */

/*lint -save -e9003 Misra 2012 8.9 Blockscope variables definitions neglected.
 * Static variable declaration in Function body violates the AUTOSAR memory mapping concept.*/

/* ----------------------------[includes]------------------------------------*/
#include "Can.h"
#include "CanIf_Cbk.h"
#include "Can_Internal.h"
#include "zynq.h"

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

/*#define USE_LDEBUG_PRINTF*/
#include "debug.h"



/* ----------------------------[private define]------------------------------*/

#define MASK_SRR_SRST         ((uint32)0x1u )
#define MASK_SRR_CEN          ((uint32)0x1u << 1u)
#define MASK_MSR_SLEEP        ((uint32)0x1u )
#define MASK_MSR_LBACK        ((uint32)0x1u << 1u)
#define MASK_MSR_SNOOP        ((uint32)0x1u << 2u)
#define MASK_BRPR_BRP         ((uint32)0xFFu )
#define MASK_BTR_TS1          ((uint32)0xFu )
#define MASK_BTR_TS2          ((uint32)0x7u << 4u)
#define MASK_BTR_SJW          ((uint32)0x3u << 7u)
#define MASK_ECR_TEC          ((uint32)0xFFu0u)
#define MASK_ECR_REC          ((uint32)0xFFu << 8u)
#define MASK_ESR_CRCER        ((uint32)0x1u )
#define MASK_ESR_FMER         ((uint32)0x1u << 1u)
#define MASK_ESR_STER         ((uint32)0x1u << 2u)
#define MASK_ESR_BERR         ((uint32)0x1u << 3u)
#define MASK_ESR_ACKER        ((uint32)0x1u << 4u)
#define MASK_SR_CONFIG        ((uint32)0x1u )
#define MASK_SR_LBACK         ((uint32)0x1u << 1u)
#define MASK_SR_SLEEP         ((uint32)0x1u << 2u)
#define MASK_SR_NORMAL        ((uint32)0x1u << 3u)
#define MASK_SR_BIDLE         ((uint32)0x1u << 4u)
#define MASK_SR_BBSY          ((uint32)0x1u << 5u)
#define MASK_SR_ERRWRN        ((uint32)0x1u << 6u)
#define MASK_SR_ESTAT         ((uint32)0x1u << 7u)
#define MASK_SR_TXBFLL        ((uint32)0x1u << 8u)
#define MASK_SR_TXFLL         ((uint32)0x1u << 9u)
#define MASK_SR_ACFBSY        ((uint32)0x1u << 10u)
#define MASK_SR_SNOOP         ((uint32)0x1u << 11u)
#define MASK_ISR_ARBLST       ((uint32)0x1u )
#define MASK_ISR_TXOK         ((uint32)0x1u << 1u)
#define MASK_ISR_TXFLL        ((uint32)0x1u << 2u)
#define MASK_ISR_TXBFLL       ((uint32)0x1u << 3u)
#define MASK_ISR_RXOK         ((uint32)0x1u << 4u)
#define MASK_ISR_RXUFLW       ((uint32)0x1u << 5u)
#define MASK_ISR_RXOFLW       ((uint32)0x1u << 6u)
#define MASK_ISR_RXNEMP       ((uint32)0x1u << 7u)
#define MASK_ISR_ERROR        ((uint32)0x1u << 8u)
#define MASK_ISR_BSOFF        ((uint32)0x1u << 9u)
#define MASK_ISR_SLP          ((uint32)0x1u << 10u)
#define MASK_ISR_WKUP         ((uint32)0x1u << 11u)
#define MASK_ISR_RXFWMFLL     ((uint32)0x1u << 12u)
#define MASK_ISR_TXFWMEMP     ((uint32)0x1u << 13u)
#define MASK_ISR_TXFEMP       ((uint32)0x1u << 14u)
#define MASK_IER_EARBLST      ((uint32)0x1u )
#define MASK_IER_ETXOK        ((uint32)0x1u << 1u)
#define MASK_IER_ETXFLL       ((uint32)0x1u << 2u)
#define MASK_IER_ETXBFLL      ((uint32)0x1u << 3u)
#define MASK_IER_ERXOK        ((uint32)0x1u << 4u)
#define MASK_IER_ERXUFLW      ((uint32)0x1u << 5u)
#define MASK_IER_ERXOFLW      ((uint32)0x1u << 6u)
#define MASK_IER_ERXNEMP      ((uint32)0x1u << 7u)
#define MASK_IER_EERROR       ((uint32)0x1u << 8u)
#define MASK_IER_EBSOFF       ((uint32)0x1u << 9u)
#define MASK_IER_ESLP         ((uint32)0x1u << 10u)
#define MASK_IER_EWKUP        ((uint32)0x1u << 11u)
#define MASK_IER_ERXFWMFLL    ((uint32)0x1u << 12u)
#define MASK_IER_ETXFWMEMP    ((uint32)0x1u << 13u)
#define MASK_IER_ETXFEMP      ((uint32)0x1u << 14u)
#define MASK_ICR_CARBLST      ((uint32)0x1u )
#define MASK_ICR_CTXOK        ((uint32)0x1u << 1u)
#define MASK_ICR_CTXFLL       ((uint32)0x1u << 2u)
#define MASK_ICR_CTXBFLL      ((uint32)0x1u << 3u)
#define MASK_ICR_CRXOK        ((uint32)0x1u << 4u)
#define MASK_ICR_CRXUFLW      ((uint32)0x1u << 5u)
#define MASK_ICR_CRXOFLW      ((uint32)0x1u << 6u)
#define MASK_ICR_CRXNEMP      ((uint32)0x1u << 7u)
#define MASK_ICR_CERROR       ((uint32)0x1u << 8u)
#define MASK_ICR_CBSOFF       ((uint32)0x1u << 9u)
#define MASK_ICR_CSLP         ((uint32)0x1u << 10u)
#define MASK_ICR_CWKUP        ((uint32)0x1u << 11u)
#define MASK_ICR_CRXFWMFLL    ((uint32)0x1u << 12u)
#define MASK_ICR_CTXFWMEMP    ((uint32)0x1u << 13u)
#define MASK_ICR_CTXFEMP      ((uint32)0x1u << 14u)
#define MASK_TCR_CTS          ((uint32)0x1u )
#define MASK_WIR_FW           ((uint32)0xFFu )
#define MASK_WIR_EW           ((uint32)0xFFu << 8u)
#define MASK_TXFIFO_ID_RTR    ((uint32)0x1u )
#define MASK_TXFIFO_ID_IDL    ((uint32)0x3FFFFu << 1u)
#define MASK_TXFIFO_ID_IDE    ((uint32)0x1u << 19u)
#define MASK_TXFIFO_ID_SRRRTR ((uint32)0x1u << 20u)
#define MASK_TXFIFO_ID_IDH    ((uint32)0x7FFu << 21u)
#define MASK_TXFIFO_DLC_DLC   ((uint32)0xFu << 28u)
#define MASK_TXFIFO_DATA1_DB3 ((uint32)0xFFu )
#define MASK_TXFIFO_DATA1_DB2 ((uint32)0xFFu << 8u)
#define MASK_TXFIFO_DATA1_DB1 ((uint32)0xFFu << 16u)
#define MASK_TXFIFO_DATA1_DB0 ((uint32)0xFFu << 24u)
#define MASK_TXFIFO_DATA2_DB3 ((uint32)0xFFu )
#define MASK_TXFIFO_DATA2_DB2 ((uint32)0xFFu << 8u)
#define MASK_TXFIFO_DATA2_DB1 ((uint32)0xFFu << 16u)
#define MASK_TXFIFO_DATA2_DB0 ((uint32)0xFFu << 24u)
#define MASK_TXHPB_ID_RTR     ((uint32)0x1u )
#define MASK_TXHPB_ID_IDL     ((uint32)0x3FFFFu << 1u)
#define MASK_TXHPB_ID_IDE     ((uint32)0x1u << 19u)
#define MASK_TXHPB_ID_SRRRTR  ((uint32)0x1u << 20u)
#define MASK_TXHPB_ID_IDH     ((uint32)0x7FFu << 21u)
#define MASK_TXHPB_DLC_DLC    ((uint32)0xFu << 28u)
#define MASK_TXHPB_DATA1_DB3  ((uint32)0xFFu )
#define MASK_TXHPB_DATA1_DB2  ((uint32)0xFFu << 8u)
#define MASK_TXHPB_DATA1_DB1  ((uint32)0xFFu << 16u)
#define MASK_TXHPB_DATA1_DB0  ((uint32)0xFFu << 24u)
#define MASK_TXHPB_DATA2_DB3  ((uint32)0xFFu )
#define MASK_TXHPB_DATA2_DB2  ((uint32)0xFFu << 8u)
#define MASK_TXHPB_DATA2_DB1  ((uint32)0xFFu << 16u)
#define MASK_TXHPB_DATA2_DB0  ((uint32)0xFFu << 24u)
#define MASK_RXFIFO_ID_RTR    ((uint32)0x1u )
#define MASK_RXFIFO_ID_IDL    ((uint32)0x3FFFFu << 1u)
#define MASK_RXFIFO_ID_IDE    ((uint32)0x1u << 19u)
#define MASK_RXFIFO_ID_SRRRTR ((uint32)0x1u << 20u)
#define MASK_RXFIFO_ID_IDH    ((uint32)0x7FFu << 21u)
#define MASK_RXFIFO_DLC_RXT   ((uint32)0xFFFFu )
#define MASK_RXFIFO_DLC_DLC   ((uint32)0xFu << 28u)
#define MASK_RXFIFO_DATA1_DB3 ((uint32)0xFFu )
#define MASK_RXFIFO_DATA1_DB2 ((uint32)0xFFu << 8u)
#define MASK_RXFIFO_DATA1_DB1 ((uint32)0xFFu << 16u)
#define MASK_RXFIFO_DATA1_DB0 ((uint32)0xFFu << 24u)
#define MASK_RXFIFO_DATA2_DB3 ((uint32)0xFFu )
#define MASK_RXFIFO_DATA2_DB2 ((uint32)0xFFu << 8u)
#define MASK_RXFIFO_DATA2_DB1 ((uint32)0xFFu << 16u)
#define MASK_RXFIFO_DATA2_DB0 ((uint32)0xFFu << 24u)
#define MASK_AFR_UAF1         ((uint32)0x1u )
#define MASK_AFR_UAF2         ((uint32)0x1u << 1u)
#define MASK_AFR_UAF3         ((uint32)0x1u << 2u)
#define MASK_AFR_UAF4         ((uint32)0x1u << 3u)
#define MASK_AFMR_AMRTR       ((uint32)0x1u )
#define MASK_AFMR_AMIDL       ((uint32)0x3FFFFu << 1u)
#define MASK_AFMR_AMIDE       ((uint32)0x1u << 19u)
#define MASK_AFMR_AMSRR       ((uint32)0x1u << 20u)
#define MASK_AFMR_AMIDH       ((uint32)0x7FFu << 21u)
#define MASK_AF_AIRTR         ((uint32)0x1u )
#define MASK_AF_AIIDL         ((uint32)0x3FFFFu << 1u)
#define MASK_AF_AIIDE         ((uint32)0x1u << 19u)
#define MASK_AF_AISRR         ((uint32)0x1u << 20u)
#define MASK_AF_AIIDH         ((uint32)0x7FFu << 21u)

#define SHIFT_SRR_SRST         (0u)
#define SHIFT_SRR_CEN          (1u)
#define SHIFT_MSR_SLEEP        (0u)
#define SHIFT_MSR_LBACK        (1u)
#define SHIFT_MSR_SNOOP        (2u)
#define SHIFT_BRPR_BRP         (0u)
#define SHIFT_BTR_TS1          (0u)
#define SHIFT_BTR_TS2          (4u)
#define SHIFT_BTR_SJW          (7u)
#define SHIFT_ECR_TEC          (0u)
#define SHIFT_ECR_REC          (8u)
#define SHIFT_ESR_CRCER        (0u)
#define SHIFT_ESR_FMER         (1u)
#define SHIFT_ESR_STER         (2u)
#define SHIFT_ESR_BERR         (3u)
#define SHIFT_ESR_ACKER        (4u)
#define SHIFT_SR_CONFIG        (0u)
#define SHIFT_SR_LBACK         (1u)
#define SHIFT_SR_SLEEP         (2u)
#define SHIFT_SR_NORMAL        (3u)
#define SHIFT_SR_BIDLE         (4u)
#define SHIFT_SR_BBSY          (5u)
#define SHIFT_SR_ERRWRN        (6u)
#define SHIFT_SR_ESTAT         (7u)
#define SHIFT_SR_TXBFLL        (8u)
#define SHIFT_SR_TXFLL         (9u)
#define SHIFT_SR_ACFBSY        (10u)
#define SHIFT_SR_SNOOP         (11u)
#define SHIFT_ISR_ARBLST       (0u)
#define SHIFT_ISR_TXOK         (1u)
#define SHIFT_ISR_TXFLL        (2u)
#define SHIFT_ISR_TXBFLL       (3u)
#define SHIFT_ISR_RXOK         (4u)
#define SHIFT_ISR_RXUFLW       (5u)
#define SHIFT_ISR_RXOFLW       (6u)
#define SHIFT_ISR_RXNEMP       (7u)
#define SHIFT_ISR_ERROR        (8u)
#define SHIFT_ISR_BSOFF        (9u)
#define SHIFT_ISR_SLP          (10u)
#define SHIFT_ISR_WKUP         (11u)
#define SHIFT_ISR_RXFWMFLL     (12u)
#define SHIFT_ISR_TXFWMEMP     (13u)
#define SHIFT_ISR_TXFEMP       (14u)
#define SHIFT_IER_EARBLST      (0u)
#define SHIFT_IER_ETXOK        (1u)
#define SHIFT_IER_ETXFLL       (2u)
#define SHIFT_IER_ETXBFLL      (3u)
#define SHIFT_IER_ERXOK        (4u)
#define SHIFT_IER_ERXUFLW      (5u)
#define SHIFT_IER_ERXOFLW      (6u)
#define SHIFT_IER_ERXNEMP      (7u)
#define SHIFT_IER_EERROR       (8u)
#define SHIFT_IER_EBSOFF       (9u)
#define SHIFT_IER_ESLP         (10u)
#define SHIFT_IER_EWKUP        (11u)
#define SHIFT_IER_ERXFWMFLL    (12u)
#define SHIFT_IER_ETXFWMEMP    (13u)
#define SHIFT_IER_ETXFEMP      (14u)
#define SHIFT_ICR_CARBLST      (0u)
#define SHIFT_ICR_CTXOK        (1u)
#define SHIFT_ICR_CTXFLL       (2u)
#define SHIFT_ICR_CTXBFLL      (3u)
#define SHIFT_ICR_CRXOK        (4u)
#define SHIFT_ICR_CRXUFLW      (5u)
#define SHIFT_ICR_CRXOFLW      (6u)
#define SHIFT_ICR_CRXNEMP      (7u)
#define SHIFT_ICR_CERROR       (8u)
#define SHIFT_ICR_CBSOFF       (9u)
#define SHIFT_ICR_CSLP         (10u)
#define SHIFT_ICR_CWKUP        (11u)
#define SHIFT_ICR_CRXFWMFLL    (12u)
#define SHIFT_ICR_CTXFWMEMP    (13u)
#define SHIFT_ICR_CTXFEMP      (14u)
#define SHIFT_TCR_CTS          (0u)
#define SHIFT_WIR_FW           (0u)
#define SHIFT_WIR_EW           (8u)
#define SHIFT_TXFIFO_ID_RTR    (0u)
#define SHIFT_TXFIFO_ID_IDL    (1u)
#define SHIFT_TXFIFO_ID_IDE    (19u)
#define SHIFT_TXFIFO_ID_SRRRTR (20u)
#define SHIFT_TXFIFO_ID_IDH    (21u)
#define SHIFT_TXFIFO_DLC_DLC   (28u)
#define SHIFT_TXFIFO_DATA1_DB3 (0u)
#define SHIFT_TXFIFO_DATA1_DB2 (8u)
#define SHIFT_TXFIFO_DATA1_DB1 (16u)
#define SHIFT_TXFIFO_DATA1_DB0 (24u)
#define SHIFT_TXFIFO_DATA2_DB3 (0u)
#define SHIFT_TXFIFO_DATA2_DB2 (8u)
#define SHIFT_TXFIFO_DATA2_DB1 (16u)
#define SHIFT_TXFIFO_DATA2_DB0 (24u)
#define SHIFT_TXHPB_ID_RTR     (0u)
#define SHIFT_TXHPB_ID_IDL     (1u)
#define SHIFT_TXHPB_ID_IDE     (19u)
#define SHIFT_TXHPB_ID_SRRRTR  (20u)
#define SHIFT_TXHPB_ID_IDH     (21u)
#define SHIFT_TXHPB_DLC_DLC    (28u)
#define SHIFT_TXHPB_DATA1_DB3  (0u)
#define SHIFT_TXHPB_DATA1_DB2  (8u)
#define SHIFT_TXHPB_DATA1_DB1  (16u)
#define SHIFT_TXHPB_DATA1_DB0  (24u)
#define SHIFT_TXHPB_DATA2_DB3  (0u)
#define SHIFT_TXHPB_DATA2_DB2  (8u)
#define SHIFT_TXHPB_DATA2_DB1  (16u)
#define SHIFT_TXHPB_DATA2_DB0  (24u)
#define SHIFT_RXFIFO_ID_RTR    (0u)
#define SHIFT_RXFIFO_ID_IDL    (1u)
#define SHIFT_RXFIFO_ID_IDE    (19u)
#define SHIFT_RXFIFO_ID_SRRRTR (20u)
#define SHIFT_RXFIFO_ID_IDH    (21u)
#define SHIFT_RXFIFO_DLC_RXT   (0u)
#define SHIFT_RXFIFO_DLC_DLC   (28u)
#define SHIFT_RXFIFO_DATA1_DB3 (0u)
#define SHIFT_RXFIFO_DATA1_DB2 (8u)
#define SHIFT_RXFIFO_DATA1_DB1 (16u)
#define SHIFT_RXFIFO_DATA1_DB0 (24u)
#define SHIFT_RXFIFO_DATA2_DB3 (0u)
#define SHIFT_RXFIFO_DATA2_DB2 (8u)
#define SHIFT_RXFIFO_DATA2_DB1 (16u)
#define SHIFT_RXFIFO_DATA2_DB0 (24u)
#define SHIFT_AFR_UAF1         (0u)
#define SHIFT_AFR_UAF2         (1u)
#define SHIFT_AFR_UAF3         (2u)
#define SHIFT_AFR_UAF4         (3u)
#define SHIFT_AFMR_AMRTR       (0u)
#define SHIFT_AFMR_AMIDL       (1u)
#define SHIFT_AFMR_AMIDE       (19u)
#define SHIFT_AFMR_AMSRR       (20u)
#define SHIFT_AFMR_AMIDH       (21u)
#define SHIFT_AF_AIRTR         (0u)
#define SHIFT_AF_AIIDL         (1u)
#define SHIFT_AF_AIIDE         (19u)
#define SHIFT_AF_AISRR         (20u)
#define SHIFT_AF_AIIDH         (21u)


/*Can interrupt mask. */
#define INTR_MASK_TXFEMP   ((uint32)1u<<13u)
#define INTR_MASK_TXFWMEMP ((uint32)1u<<12u)
#define INTR_MASK_WKUP     ((uint32)1u<<11u)
#define INTR_MASK_SLP      ((uint32)1u<<10u)
#define INTR_MASK_BSOFF    ((uint32)1u<<9u)
#define INTR_MASK_ERROR    ((uint32)1u<<8u)
#define INTR_MASK_RXNEMP   ((uint32)1u<<7u)
#define INTR_MASK_RXOFLW   ((uint32)1u<<6u)
#define INTR_MASK_RXUFLW   ((uint32)1u<<5u)
#define INTR_MASK_RXOK     ((uint32)1u<<4u)
#define INTR_MASK_TXBFLL   ((uint32)1u<<3u)
#define INTR_MASK_TXFLL    ((uint32)1u<<2u)
#define INTR_MASK_TXOK     ((uint32)1u<<1u)
#define INTR_MASK_ARBLST   ((uint32)1u<<0u)

/* Can Tx Fifo Queue structure */
#define TX_FIFO_QUEUE_LENGTH  64u
#define TX_FIFO_QUEUE_SIZE    (TX_FIFO_QUEUE_LENGTH + 1u)

/* Number of Can channel in Zynq*/
#define NUM_OF_CAN_CHANNEL 2u

#define CAN_ASSERT(_x)	    /*lint -save -e716 -e9036 -e9027 -e506 -e774 \
                             * while(1), \
                             * Conditional expression should have essentially Boolean type Misra 2012 14.4 \
                             * Unpermitted operand to operator '!'  Misra 2012 10.1 \
                             * Constant value Boolean Misra 2004 13.7, 2004 14.1, 2012 2.1 \
                             * Boolean within 'if' always evaluates to True \
                             * All these warning are tolerable to stop code execution*/ \
                             if( !(_x) ) { while(1) {} } /*lint -restore*/

/* ----------------------------[private typedef]-----------------------------*/

typedef volatile struct CAN_reg HwRegType;

typedef enum {
    CAN_CTRL_INDICATION_NONE,
    CAN_CTRL_INDICATION_PENDING_START,
    CAN_CTRL_INDICATION_PENDING_STOP,
    CAN_CTRL_INDICATION_PENDING_SLEEP
} CtrlPendingStateIndicationType;


/* Type for holding information about each controller */
typedef struct {
    /* This unit have uses controller */

    const Can_ControllerConfigType * cfgCtrlPtr; /* Pointer to controller config. */
    const Can_HardwareObjectType * cfgHohPtr; /* List of HOHs. */
    HwRegType * hwPtr; /* Pointer to the proper SFRs. */

    CanIf_ControllerModeType state;
    CtrlPendingStateIndicationType pendingStateIndication;

    uint32 interruptMask; /*Possible interrupts of this controller.*/
    PduIdType Queue[TX_FIFO_QUEUE_SIZE];
    uint8 QueueIn;
    uint8 QueueOut;

} UnitType;

/* This type definition is responsible to handle the incoming Rx frame easily. */
typedef struct {
    uint32 RXFIFO_ID; /* receive message fifo message identifier*/
    uint32 RXFIFO_DLC; /* receive message fifo data length code*/
    uint32 RXFIFO_DATA1; /* receive message fifo data word 1*/
    uint32 RXFIFO_DATA2; /* receive message fifo data word 2*/
} RxFrameType;

typedef enum {
    CAN_HARDWARE_MODE_CONFIGURATION = 0u,
    CAN_HARDWARE_MODE_NORMAL = 1u,
    CAN_HARDWARE_MODE_SLEEP = 2u,
    CAN_HARDWARE_MODE_LOOPBACK = 3u,
} ControllerModeType;

/* ----------------------------[private macro]-------------------------------*/

#define SET_REG(_register, _mask, _shift, _value) ((_register) = ( (_register) & ~(uint32)(_mask) ) | ( (uint32)(_value) << (_shift) ) )
#define SET_REG2(_register, _value) ((_register) = (_value))

#define GET_REG(_register, _mask, _shift) ( ((_register) & (_mask)) >> (_shift) )
#define GET_REG2(_register) (_register)

#define CAN_UNUSED(_variable)            ((void)(_variable))
#define GET_CAN_HW(_hwUnit)              (canRegisters[_hwUnit])

#define CTRL_TO_UNIT_PTR(_controller)    (&canUnitData[_controller])
#define HWUNIT_TO_CONTROLLER_ID(_hwunit) (Can_Global.config->CanConfigSetPtr->ArcHwUnitToController[_hwunit])

#define SET_TXFIFO_ID(_idh, _srrrtr, _ide, _idl, _rtr)                            \
            ( (MASK_TXFIFO_ID_IDH & ((uint32)(_idh)       << SHIFT_TXFIFO_ID_IDH))    \
            | (MASK_TXFIFO_ID_SRRRTR & ((uint32)(_srrrtr) << SHIFT_TXFIFO_ID_SRRRTR)) \
            | (MASK_TXFIFO_ID_IDE & ((uint32)(_ide)       << SHIFT_TXFIFO_ID_IDE))    \
            | (MASK_TXFIFO_ID_IDL & ((uint32)(_idl)       << SHIFT_TXFIFO_ID_IDL))    \
            | (MASK_TXFIFO_ID_RTR & ((uint32)(_rtr)       << SHIFT_TXFIFO_ID_RTR))    )

#if defined(USE_DEM)
#define VALIDATE_DEM(_exp,_err,_rv) \
        if (!(_exp)) { \
            Dem_ReportErrorStatus(_err, DEM_EVENT_STATUS_FAILED); \
            return _rv; \
        }
#else /* !defined(USE_DEM)*/
#define VALIDATE_DEM(_exp,_err,_rv )
#endif /*USE_DEM*/

/* ----------------------------[private function prototypes]-----------------*/

static void createInterruptMask(UnitType * const unitPtr);
static void installControllerInterrupts(const UnitType * const unitPtr);
static void interruptHandler(CanHwUnitIdType hwUnit);
static void isrError(const UnitType * const unitPtr);
static void isrBusoff(const UnitType * const unitPtr);
static void isrWakeup(const UnitType * const unitPtr);
static void isrSleep(UnitType * const unitPtr);
static void isrTx(UnitType * const constunitPtr);
static void isrRx(const UnitType * const unitPtr);
static void processReceiveData(RxFrameType *rxFramePtr, const UnitType * const unitPtr);
static void resetHardware(UnitType * const unitPtr);
static void setCanHardwareMode(UnitType * const unitPtr, ControllerModeType mode);
static ControllerModeType getCanHardwareMode( const UnitType * const unitPtr);
static void txQueueInit(UnitType * const canUnit);
static Std_ReturnType txQueuePut(UnitType * const canUnit, PduIdType new);
static Std_ReturnType txQueueGet(UnitType * const canUnit, PduIdType *old);
static Std_ReturnType modifyBaudrate(UnitType * const canUnit, const Can_ControllerBaudrateConfigType *baudratePtr);
static Std_ReturnType getCheckFilter( const Can_HardwareObjectType * hohCfgPtr, uint32 canId);
static uint32 u32ChangeEndianess(uint32 value);
#if (USE_CAN_CTRL_0 == STD_ON)
static ISR(ctrl_0_InterruptHandler);
#endif /*USE_CAN_CTRL_0 == STD_ON*/
#if (USE_CAN_CTRL_1 == STD_ON)
static ISR(ctrl_1_InterruptHandler);
#endif /*USE_CAN_CTRL_1 == STD_ON*/

/* ----------------------------[private constants]---------------------------*/

/*lint -save -e923 cast from unsigned int to pointer MISRA 2004 11.1 11.3 2012 11.4 11.6
 * Integer to pointer casting is necessary to set SFR of Microcontroller. */
static HwRegType* const canRegisters[NUM_OF_CAN_CHANNEL] = {
        (HwRegType*) ZYNQ_CAN0_BASE,
        (HwRegType*) ZYNQ_CAN1_BASE,
};
/*lint -restore*/

/* ----------------------------[private variables]---------------------------*/

UnitType canUnitData[CAN_ARC_CTRL_CONFIG_CNT];

/* ----------------------------[private functions]---------------------------*/

#if (USE_CAN_CTRL_0 == STD_ON)
static ISR(ctrl_0_InterruptHandler) {interruptHandler(CAN_CTRL_0);}
#endif /*USE_CAN_CTRL_0 == STD_ON*/

#if (USE_CAN_CTRL_1 == STD_ON)
static ISR(ctrl_1_InterruptHandler) {interruptHandler(CAN_CTRL_1);}
#endif /*USE_CAN_CTRL_1 == STD_ON*/

/**
 * Hardware error ISR for CAN
 * @param unit CAN controller number( from 0 )
 */
static void isrError(const UnitType * const unitPtr)
{
    /** @req 4.1.2/SWS_Can_00033 */
    uint8 controllerId = HWUNIT_TO_CONTROLLER_ID(unitPtr->cfgCtrlPtr->Can_Arc_HwUnitId);
    Can_Arc_ErrorType err;   /*lint !e9018 HARDWARE ACCESS */

    err.R = GET_REG2(unitPtr->hwPtr->ESR);

    /* Clear errors. */
    SET_REG2(unitPtr->hwPtr->ESR, 0x1fu);

    (void)err;          /*lint !e920 STANDARDIZED_API */
    (void)controllerId;   /*lint !e920 STANDARDIZED_API */

#if defined(CFG_CAN_USE_SYMBOLIC_CANIF_CONTROLLER_ID)
    Can_Arc_Error(Can_Global.config->CanConfigSetPtr->CanController[controllerId].Can_Arc_CanIfControllerId, err);
#else
    Can_Arc_Error(controllerId, err);
#endif
}

/**
 *
 * @param unitPtr
 */
static void isrBusoff(const UnitType * const unitPtr)
{
    /** @req 4.1.2/SWS_Can_00273 *//* After bus-off detection, the Can module shall cancel still pending messages without
                                    * raising a cancellation notification*/
    /** @req 4.1.2/SWS_Can_00274 *//*The Can module shall disable or suppress automatic bus-off recovery */

    /** @req 4.1.2/SWS_Can_00033 */
    uint8 controllerId = HWUNIT_TO_CONTROLLER_ID(unitPtr->cfgCtrlPtr->Can_Arc_HwUnitId);

    /** @req 4.1.2/SWS_Can_00020 */
    /** @req 4.1.2/SWS_Can_00272 */
    /* This will give an indication to CanIf that stopped is reached.*/
    (void) Can_Hw_SetControllerMode(controllerId, CAN_T_STOP);

#if defined(CFG_CAN_USE_SYMBOLIC_CANIF_CONTROLLER_ID)
    CanIf_ControllerBusOff(Can_Global.config->CanConfigSetPtr->CanController[controllerId].Can_Arc_CanIfControllerId);
#else
    CanIf_ControllerBusOff(controllerId);
#endif
}

/**
 *  This function is responsible handle the result of a successful transmission
 *  Precondition: TXOK interrupt happened
 *  @param unitPtr Pointer to the given controller data
 */
static void isrTx(UnitType * const unitPtr)
{
    /** @req 4.1.2/SWS_Can_00033 */
    PduIdType pduId;

    /** @req 4.1.2/SWS_Can_00276 */
    /* Get the oldest txPdu from the queue */
    if ( E_OK == txQueueGet(unitPtr, &pduId)) /*lint !e934 MISRA 2004 Rule 1.2 Rule 1.3 Taking address of near auto variable Using stack pointer as argument is tolerable. */
    {
        /** @req 4.1.2/SWS_Can_00016 */
        CanIf_TxConfirmation(pduId);
    }
    else
    {
        /* Something corrupted - Init the queue */
        txQueueInit(unitPtr);
    }
}

/**
 *
 * @param hohCfgPtr
 * @param canId
 * @return
 */
static Std_ReturnType getCheckFilter(
        const Can_HardwareObjectType * hohCfgPtr,
        uint32 canId)
{
    Std_ReturnType retVal = E_NOT_OK;

    /* If filter is not configured. */
    if (0u == hohCfgPtr->CanHwFilterSize)
    {
        retVal = E_OK;
    }
    else
    {
        /* Scan through all Hardware Filter of the given Hoh */
        for (uint8 hwFilterIdx = 0u; (hwFilterIdx < hohCfgPtr->CanHwFilterSize); hwFilterIdx++)
        {
            const Can_HardwareFilterType *hwFilterPtr = &(hohCfgPtr->CanHwFilterPtr[hwFilterIdx]);

            if ((canId & hwFilterPtr->CanHwFilterMask)                      !=
                (hwFilterPtr->CanHwFilterCode & hwFilterPtr->CanHwFilterMask))
            {
                continue;
            }

            retVal = E_OK;
            break;
        }/*end of For*/
    }

    return retVal;
}

/**
 *
 * @param rxFramePtr
 */
static void processReceiveData(
        RxFrameType *rxFramePtr,
        const UnitType * const unitPtr)
{
    const Can_ControllerConfigType * ctrCfgPtr = unitPtr->cfgCtrlPtr;
    boolean breakFlag = FALSE;
    uint8 saveHohIdx = 0u;
    uint8 canDlc;
    uint32 canId;
    uint32 canId_low;
    uint32 canId_high;

    /*Swap data to have the original byte order*/
    rxFramePtr->RXFIFO_DATA1 = u32ChangeEndianess(rxFramePtr->RXFIFO_DATA1);
    rxFramePtr->RXFIFO_DATA2 = u32ChangeEndianess(rxFramePtr->RXFIFO_DATA2);

    /* Retrieve CanId and convert to proper format in case of extended CanId */
    if (0u != GET_REG(rxFramePtr->RXFIFO_ID, MASK_RXFIFO_ID_IDE, SHIFT_RXFIFO_ID_IDE))
    {
        canId_low  = GET_REG(rxFramePtr->RXFIFO_ID, MASK_RXFIFO_ID_IDL, SHIFT_RXFIFO_ID_IDL);
        canId_high = GET_REG(rxFramePtr->RXFIFO_ID, MASK_RXFIFO_ID_IDH, SHIFT_RXFIFO_ID_IDH);
        canId      = canId_low | (canId_high << 18u);

        canId |= 0x80000000uL; /** @req 4.1.2/SWS_Can_00423 */
    }
    else
    {
        canId = GET_REG(rxFramePtr->RXFIFO_ID, MASK_RXFIFO_ID_IDH,
                SHIFT_RXFIFO_ID_IDH);
    }

    /* Scan through all HOH of the given controller */
    for (uint8 hohIdx = 0u; (hohIdx < ctrCfgPtr->Can_Arc_HohCnt) && (!breakFlag); hohIdx++)
    {
        const Can_HardwareObjectType * hohCfgPtr = &(ctrCfgPtr->Can_Arc_Hoh[hohIdx]);

        if (CAN_OBJECT_TYPE_RECEIVE != hohCfgPtr->CanObjectType)
        {
            continue;
        }

        if (E_OK == getCheckFilter(hohCfgPtr, canId))
        {
            breakFlag = TRUE;
            saveHohIdx = hohIdx;
        }

    }/*end of For*/

    if ((breakFlag))
    {

        canDlc = (uint8) GET_REG(rxFramePtr->RXFIFO_DLC, MASK_RXFIFO_DLC_DLC, SHIFT_RXFIFO_DLC_DLC);

        /** @req 4.1.2/SWS_Can_00396 */
        /** @req 4.1.2/SWS_Can_00279 */
        /** @req 4.1.2/SWS_Can_00060 */
        CanIf_RxIndication(
                unitPtr->cfgCtrlPtr->Can_Arc_Hoh[saveHohIdx].CanObjectId,
                canId,
                canDlc,
                (const uint8*) ((void*) (&rxFramePtr->RXFIFO_DATA1)));
    }
}

/**
 * This function is responsible to handle the interrupt caused by message receiving.
 * Precondition: RXOK interrupt happened.
 * @param unitPtr Pointer to the given controller data
 */
static void isrRx(const UnitType * const unitPtr)
{
    /** @req 4.1.2/SWS_Can_00033 */
    /** @req 4.1.2/SWS_Can_00012 */
    HwRegType   *canHw = unitPtr->hwPtr;
    RxFrameType  rxFrame;
    RxFrameType *rxFramePtr = &rxFrame; /*lint !e934 MISRA 2004 Rule 1.2 Rule 1.3 Taking address of near auto variable Using stack pointer as argument is tolerable. */

    if (1u == GET_REG(canHw->ISR, MASK_ISR_RXNEMP, SHIFT_ISR_RXNEMP)) /*lint !e123 Macro 'ISR' defined with arguments, naming convention of SFT followed thus it is tolerable.*/
    {
            rxFramePtr->RXFIFO_ID = GET_REG2(canHw->RXFIFO_ID);
            rxFramePtr->RXFIFO_DLC = GET_REG2(canHw->RXFIFO_DLC);

            /* Save data bytes registers*/
            rxFramePtr->RXFIFO_DATA1 = GET_REG2(canHw->RXFIFO_DATA1);
            rxFramePtr->RXFIFO_DATA2 = GET_REG2(canHw->RXFIFO_DATA2);

            processReceiveData(rxFramePtr, unitPtr);

            /*lint -e{845} -e{835} A zero has been given as argument tolerated to use uniform macros to set SFRs*/
            SET_REG(canHw->ICR, MASK_ICR_CRXNEMP, SHIFT_ICR_CRXNEMP, 1u);
    }
}

/**
 *
 * @param unitPtr
 */
static void isrWakeup(const UnitType * const unitPtr) {
    /** !req 4.1.2/SWS_Can_00269 *//* The Can module shall not further process the L-PDU that caused a wake-up*/
    /** @req 4.1.2/SWS_Can_00270 *//* On hardware wakeup (triggered by a wake-up event from CAN bus), the CAN controller shall transition into the state STOPPED.*/
    /** !req 4.1.2/SWS_Can_00271 *//* On hardware wakeup (triggered by a wake-up event from CAN bus), the Can module shall call the function EcuM_CheckWakeup either in interrupt context or in the context of Can_MainFunction_Wakeup*/
    /** !req 4.1.2/SWS_Can_00364 *//* If the ISR for wakeup events is called, it shall call EcuM_CheckWakeup in turn. The parameter passed to EcuM_CheckWakeup shall be the ID of the wakeup source referenced by the CanWakeupSourceRef configuration parameter*/
    /** !req 4.1.2/SWS_Can_00390 *//* The Can module shall include the header file EcuM_Cbk.h, in which the callback functions called by the Can module at the Ecu State Manager module are declared*/
    /** !req 4.1.2/SWS_Can_00461 *//* If hardware supports wake-up (i.e. CanWakeupSupport == true), it shall be checked during controller initialization if there was a wake-up event on the specific CAN controller. If a wake-up event has been detected, the wake-up shall directly be reported to the EcuM via EcuM_SetWakeupEvent call-back function.*/
    /** !req 4.1.2/SWS_Can_00048 *//* In case of a CAN bus wake-up during sleep transition, the function Can_SetControllerMode(CAN_T_WAKEUP) shall return CAN_NOT_OK*/

    uint8 controllerId = HWUNIT_TO_CONTROLLER_ID(unitPtr->cfgCtrlPtr->Can_Arc_HwUnitId);

    if (CAN_OK != Can_Hw_SetControllerMode(controllerId, CAN_T_WAKEUP))
    {
        /*This must not be reached*/
        CAN_ASSERT(0);
    }

    /* Wake up source reference currently not a configurable element. EcuM_CheckWakeup must be called from here
     * EcuM_CheckWakeup(unitPtr->cfgCtrlPtr->CanWakeupSourceRef);
     */
}

/**
 *
 * @param unitPtr
 */
static void isrSleep(UnitType * const unitPtr)
{
    CAN_UNUSED(unitPtr); /*lint !e920 Misra 2012 1.3 cast from pointer to void */
    /* This function is called because Can_SetControllerMode function was called to set the controller
     * to Sleep mode previously. The result of the state transition will be polled from main function of Can module. */
}


/**
 * This function is responsible to handle all kind of interrupt which came from CAN.
 * @param hwUnit
 */
static void interruptHandler(CanHwUnitIdType hwUnit)
{
    UnitType *unitPtr = CTRL_TO_UNIT_PTR(HWUNIT_TO_CONTROLLER_ID(hwUnit));

    /* Get valid interrupts*/
    uint32 intrStateReg = GET_REG2(unitPtr->hwPtr->ISR); /*lint !e123 Macro 'ISR' defined with arguments, naming convention of SFT followed thus it is tolerable.*/
    uint32 intrEnableReg = GET_REG2(unitPtr->hwPtr->IER);
    uint32 intrVector = intrStateReg & intrEnableReg;

    /* Error check. Get Interrupt Status Register and Interrupt Enable Register. */
    if ((intrVector & INTR_MASK_ERROR) != 0u) {
        isrError(unitPtr);
    }

    /* Busoff check. Get Interrupt Status Register and Interrupt Enable Register.*/
    if ((intrVector & INTR_MASK_BSOFF) != 0u) {
        isrBusoff(unitPtr);
    }

    /* Wakeup check. Get Interrupt Status Register and Interrupt Enable Register. */
    if ((intrVector & INTR_MASK_WKUP) != 0u) {
        isrWakeup(unitPtr);
    }

    /* Sleep check. Get Interrupt Status Register and Interrupt Enable Register. */
    if ((intrVector & INTR_MASK_SLP) != 0u) {
        isrSleep(unitPtr);
    }

    /* Tx check. Get Interrupt Status Register and Interrupt Enable Register. */
    if ((intrVector & INTR_MASK_TXOK) != 0u) {
        isrTx(unitPtr);
    }

    /* Rx check. Get Interrupt Status Register and Interrupt Enable Register. */
    if ((intrVector & INTR_MASK_RXOK) != 0u) {
        isrRx(unitPtr);
    }

    /** @req 4.1.2/SWS_Can_00420 */
    /* Can module shall reset the interrupt flag at the end of the ISR */
    SET_REG2(unitPtr->hwPtr->ICR, intrVector); /*lint !e123 Macro 'ISR' defined with arguments, naming convention of SFT followed thus it is tolerable.*/
}

/**
 * Create interrupt mask for a controller
 * @param unitPtr
 */
static void createInterruptMask(UnitType * const unitPtr)
{
    uint32 arcFlags = unitPtr->cfgCtrlPtr->Can_Arc_Flags;
    uint32 mask = 0u;

    /* Set Reception interrupt. */
    if (0u != (arcFlags & CAN_CTRL_RX_PROCESSING_INTERRUPT)) {
        mask |= INTR_MASK_RXOK;
    }

    /* Set Transmission interrupt. */
    if (0u != (arcFlags & CAN_CTRL_TX_PROCESSING_INTERRUPT)) {
        mask |= INTR_MASK_TXOK;
    }

    /* Set BusOff and warning interrupt. */
    if (0u != (arcFlags & CAN_CTRL_BUSOFF_PROCESSING_INTERRUPT)) {
        mask |= INTR_MASK_BSOFF;
    }

    /* Set Error interrupt. */
    if (0u != (arcFlags & CAN_CTRL_ERROR_PROCESSING_INTERRUPT)) {
        mask |= INTR_MASK_ERROR;
    }

    //error added by default
    mask |= INTR_MASK_ERROR;

    unitPtr->interruptMask = mask;
}

/**
 * By calling this function all interrupts will registered to Os.
 * @param unitPtr
 */
static void installControllerInterrupts(const UnitType * const unitPtr)
{
    CanHwUnitIdType hwUnitId = unitPtr->cfgCtrlPtr->Can_Arc_HwUnitId;
    uint32 arcFlags = unitPtr->cfgCtrlPtr->Can_Arc_Flags;

    switch (hwUnitId) {
#if (USE_CAN_CTRL_0 == STD_ON)
    case CAN_CTRL_0:
        /*lint -save -e9027 2012 10.1 Unpermitted operand to operator '<<' */
        if ( (arcFlags & ((uint32)CAN_CTRL_RX_PROCESSING_INTERRUPT |
                          (uint32)CAN_CTRL_TX_PROCESSING_INTERRUPT |
                          (uint32)CAN_CTRL_WAKEUP_PROCESSING_INTERRUPT |
                          (uint32)CAN_CTRL_BUSOFF_PROCESSING_INTERRUPT |
                          (uint32)CAN_CTRL_ERROR_PROCESSING_INTERRUPT ) ) != 0u )
        {
            ISR_INSTALL_ISR2( "Can", ctrl_0_InterruptHandler, (uint16)IRQ_CAN_0, 2, 0);
        }
        /*lint -restore*/
        break;
#endif /*USE_CAN_CTRL_0 == STD_ON*/
#if (USE_CAN_CTRL_1 == STD_ON)
    case CAN_CTRL_1:
        /*lint -save -e9027 2012 10.1 Unpermitted operand to operator '<<' */
        if ( (arcFlags & ((uint32)CAN_CTRL_RX_PROCESSING_INTERRUPT |
                          (uint32)CAN_CTRL_TX_PROCESSING_INTERRUPT |
                          (uint32)CAN_CTRL_WAKEUP_PROCESSING_INTERRUPT |
                          (uint32)CAN_CTRL_BUSOFF_PROCESSING_INTERRUPT |
                          (uint32)CAN_CTRL_ERROR_PROCESSING_INTERRUPT ) ) != 0u )
        {
            ISR_INSTALL_ISR2( "Can", ctrl_1_InterruptHandler, (uint16)IRQ_CAN_1, 2, 0);
        }
        /*lint -restore*/
        break;
#endif /*USE_CAN_CTRL_1 == STD_ON*/
    default:
        /*This must not be reached*/
        CAN_ASSERT(0);
    }
}

/**
 *
 * @param canUnit
 */
static void txQueueInit(UnitType* const canUnit)
{
    canUnit->QueueIn = (canUnit->QueueOut = 0u);
}

/**
 *
 * @param canUnit
 * @param new
 * @return
 */
static Std_ReturnType txQueuePut(UnitType* const canUnit, PduIdType new)
{
    if (canUnit->QueueIn == (((canUnit->QueueOut  + TX_FIFO_QUEUE_SIZE) - 1u) % TX_FIFO_QUEUE_SIZE))
    {
        return E_NOT_OK; /* Queue Full*/
    }

    canUnit->Queue[canUnit->QueueIn] = new;
    canUnit->QueueIn = (canUnit->QueueIn + 1) % TX_FIFO_QUEUE_SIZE;
    return E_OK; /* No errors */
}

/**
 *
 * @param canUnit
 * @param old
 * @return
 */
static Std_ReturnType txQueueGet(UnitType * const canUnit, PduIdType *old)
{
    if (canUnit->QueueIn == canUnit->QueueOut)
    {
        return E_NOT_OK; /* Queue Empty - nothing to get*/
    }

    *old = canUnit->Queue[canUnit->QueueOut];
    canUnit->QueueOut = (canUnit->QueueOut + 1) % TX_FIFO_QUEUE_SIZE;
    return E_OK; /* No errors */
}

/**
 *
 * @param value
 * @return
 */
static uint32 u32ChangeEndianess(uint32 value)
{
    /** @req 4.1.2/SWS_Can_00059 */ /*Data mapping by CAN to memory is defined in a way that the CAN data byte which is sent out first is array element 0, the CAN data byte which is sent out last is array element 7*/

    uint32 result;
    const uint8 *ptrValue = (uint8*) ((void*) (&value)); /*lint !e934 MISRA 2004 Rule 1.2 Rule 1.3 Taking address of near auto variable Using stack pointer as argument is tolerable. */
    uint8 *ptrResult = (uint8*) ((void*) (&result)); /*lint !e934 MISRA 2004 Rule 1.2 Rule 1.3 Taking address of near auto variable Using stack pointer as argument is tolerable. */

    ptrResult[0] = ptrValue[3];
    ptrResult[1] = ptrValue[2];
    ptrResult[2] = ptrValue[1];
    ptrResult[3] = ptrValue[0];

    return result;
}

/**
 * This function resets the hardware, by calling this function hardware goes to configuration mode immediately.
 * @param unitPtr
 */
static void resetHardware(UnitType * const unitPtr)
{
    SchM_Enter_Can_EA_0(); /* Enter exclusive area. *//*lint !e632 Assignment to strong type 'imask_t'. Tolerable to enter exclusive area*/

    /*lint -e{835} A zero has been given as argument tolerated to use uniform macros to set SFRs*/
    SET_REG(unitPtr->hwPtr->SRR, MASK_SRR_SRST, SHIFT_SRR_SRST, 1u);
    txQueueInit(unitPtr);

    SchM_Exit_Can_EA_0(); /* Exit exclusive area*/
}

/**
 *
 * @param unitPtr
 * @param mode
 */
static void setCanHardwareMode(UnitType * const unitPtr, ControllerModeType mode)
{
    ControllerModeType currentMode;

    SchM_Enter_Can_EA_0(); /* Enter exclusive area. *//*lint !e632 Assignment to strong type 'imask_t'. Tolerable to enter exclusive area*/

    currentMode = getCanHardwareMode(unitPtr);

    if (currentMode != mode)
    {
        /* Go to config mode first -> reset CEN and SRR bits */
        SET_REG2(unitPtr->hwPtr->SRR, 0u);

        /* Inint the queue */
        txQueueInit(unitPtr);

        if (CAN_HARDWARE_MODE_CONFIGURATION == getCanHardwareMode(unitPtr))
        {
            if (CAN_HARDWARE_MODE_NORMAL == mode)
            {
                SET_REG2(unitPtr->hwPtr->MSR, 0u);
                SET_REG(unitPtr->hwPtr->SRR, MASK_SRR_CEN, SHIFT_SRR_CEN, 1u);
            }
            else if (CAN_HARDWARE_MODE_SLEEP == mode)
            {
                /*lint -e{845} -e{835} A zero has been given as argument tolerated to use uniform macros to set SFRs*/

                //this is commented out to handle LogicalSleepState
                //SET_REG(unitPtr->hwPtr->MSR, MASK_MSR_SLEEP, SHIFT_MSR_SLEEP, 1u);
                //SET_REG(unitPtr->hwPtr->SRR, MASK_SRR_CEN, SHIFT_SRR_CEN, 1u);
            }
            else if (CAN_HARDWARE_MODE_LOOPBACK == mode)
            {
                SET_REG(unitPtr->hwPtr->MSR, MASK_MSR_LBACK, SHIFT_MSR_LBACK, 1u);
                SET_REG(unitPtr->hwPtr->SRR, MASK_SRR_CEN, SHIFT_SRR_CEN, 1u);
            }
            else
            {
                ;/*do nothing*/
            }
        }
        else
        {
            /*This must not be reached*/
            CAN_ASSERT(0);
        }
    }

    SchM_Exit_Can_EA_0(); /* Exit exclusive area*/
}

/**
 *
 * @param unitPtr
 * @return
 */
static ControllerModeType getCanHardwareMode( const UnitType * const unitPtr)
{
    ControllerModeType mode;

    /*lint -e{835} A zero has been given as argument tolerated to use uniform macros to set SFRs*/
    if (1u == GET_REG(unitPtr->hwPtr->SR, MASK_SR_CONFIG, SHIFT_SR_CONFIG))
    {
        mode = CAN_HARDWARE_MODE_CONFIGURATION;
    }
    else if (1u == GET_REG(unitPtr->hwPtr->SR, MASK_SR_LBACK, SHIFT_SR_LBACK))
    {
        mode = CAN_HARDWARE_MODE_LOOPBACK;
    }
    else if (1u == GET_REG(unitPtr->hwPtr->SR, MASK_SR_SLEEP, SHIFT_SR_SLEEP))
    {
        mode = CAN_HARDWARE_MODE_SLEEP;
    }
    else /* 1u == GET_REG(unitPtr->hwPtr->SR, MASK_SR_NORMAL, SHIFT_SR_NORMAL)*/
    {
        mode = CAN_HARDWARE_MODE_NORMAL;
    }

    return mode;
}

/**
 *
 * @param canUnit Can unit identifier
 * @param Baudrate Value of the proposed baudrate.
 * @return E_OK The new baudrate was set successfully.
 * 		   E_NOT_OK	The new was failed to set.
 */
static Std_ReturnType modifyBaudrate(
        UnitType * const canUnit, const Can_ControllerBaudrateConfigType *baudratePtr)
{
    /** @req 4.1.2/SWS_Can_00449 */
    const Can_ControllerConfigType *config = canUnit->cfgCtrlPtr;

    HwRegType *canHw = canUnit->hwPtr;
    uint32 clockFreq;
    uint32 nominalBitTime;
    uint32 baudPrescaler;


    /* Catch NULL-pointer when no DET is available. */
    if (baudratePtr == NULL) {
        return E_NOT_OK ; /* Baudrate not found. */
    }

    /** @req 4.1.2/SWS_Can_00062 *//* Re-initialize the CAN controller and the controller specific settings. */
    /** @req 4.1.2/SWS_Can_00255 *//* Only affect register areas that contain specific configuration for a single CAN
                                           * controller. */

    SchM_Enter_Can_EA_0(); /* Enter exclusive area. *//*lint !e632 Assignment to strong type 'imask_t'. Tolerable to enter exclusive area*/

    /** @req 4.1.2/SWS_Can_00422 *//*If re-initialization is necessary the function Can_SetBaudrate shall ensure that
                                    *any settings that will cause the CAN controller to participate in the network are
                                    *any not set.*/

    /* Check whether the hardware is in configuration mode. */
    setCanHardwareMode(canUnit, CAN_HARDWARE_MODE_CONFIGURATION);
    if (CAN_HARDWARE_MODE_CONFIGURATION != getCanHardwareMode(canUnit)) {
    	SchM_Exit_Can_EA_0(); /* Exit exclusive area*/
        return E_NOT_OK ;
    }

    /* Update timing bits. */

    /*lint -e{835} A zero has been given as argument tolerated to use uniform macros to set SFRs*/
    SET_REG(canHw->BTR, MASK_BTR_TS1, SHIFT_BTR_TS1, (baudratePtr->CanControllerPropSeg + baudratePtr->CanControllerSeg1) - 1u); /*lint !e9033 Misra 2012 10.8 Impermissible cast of composite expression*/
    SET_REG(canHw->BTR, MASK_BTR_TS2, SHIFT_BTR_TS2, baudratePtr->CanControllerSeg2 - 1u); /*lint !e9033 Misra 2012 10.8 Impermissible cast of composite expression*/
    SET_REG(canHw->BTR, MASK_BTR_SJW, SHIFT_BTR_SJW, baudratePtr->CanControllerSyncJumpWidth - 1u); /*lint !e9033 Misra 2012 10.8 Impermissible cast of composite expression*/

    /* Get correct clock frequency from Mcu. */
    clockFreq = (CAN_CTRL_0 == config->Can_Arc_HwUnitId) ? (MCU_ARC_CLOCK_CAN_0_FREQUENCY) : (MCU_ARC_CLOCK_CAN_1_FREQUENCY);

    /*lint -e{9033} Misra 10.8 Update baudrate prescaler based on corrected equation. */
    nominalBitTime = (uint32) (((uint32) (baudratePtr->CanControllerBaudRate) * 1000u)
            * (uint32) (baudratePtr->CanControllerPropSeg + baudratePtr->CanControllerSeg1 + baudratePtr->CanControllerSeg2 + 1u));

    baudPrescaler = (uint32) ((clockFreq + (nominalBitTime / 2)) / nominalBitTime);

    /*lint -e{835} A zero has been given as argument tolerated to use uniform macros to set SFRs*/
    SET_REG(canHw->BRPR, MASK_BRPR_BRP, SHIFT_BRPR_BRP, baudPrescaler - 1u);

    SchM_Exit_Can_EA_0(); /* Exit exclusive area*/

    return E_OK;
}

/**
 * Initializes the CAN driver
 * @param Config - a pointer to the configuration that is used during initialization
 */
void Can_Hw_Init(void)
{
    /** @req 4.1.2/SWS_Can_00223 */
    /** @req 4.1.2/SWS_Can_00021 */
    /** @req 4.1.2/SWS_Can_00291 */
    /** !req 4.1.2/SWS_Can_00408 */
    /** @req 4.1.2/SWS_Can_00419 *//* Disable all unused interrupts. We only enable the ones used. */
    /** @req 4.1.2/SWS_Can_00053 *//* Don't change registers for controllers not used. */
    /** @req 4.1.2/SWS_Can_00250 *//* Initialize variables, init controllers. */
    /** @req 4.1.2/SWS_Can_00239 *//* Init all on chip hardware */

    UnitType *unitPtr;

    /** @req 4.1.2/SWS_Can_00245 */
    for (uint8 controllerId = 0; controllerId < CAN_ARC_CTRL_CONFIG_CNT; controllerId++)
    {
        const Can_ControllerConfigType *cfgCtrlPtr = &Can_Global.config->CanConfigSetPtr->CanController[controllerId];
        unitPtr = CTRL_TO_UNIT_PTR(controllerId);

        memset(unitPtr, 0u, sizeof(UnitType));

        /* Add controller config pointer and hoh pointer */
        unitPtr->cfgCtrlPtr = cfgCtrlPtr;
        unitPtr->cfgHohPtr = cfgCtrlPtr->Can_Arc_Hoh;

        /* Set base address of the Controller. */
        unitPtr->hwPtr = GET_CAN_HW(cfgCtrlPtr->Can_Arc_HwUnitId);

        /** @req 4.1.2/SWS_Can_00259 *//* Reset the controller. The device goes to Configuration Mode immediately. */
        resetHardware(unitPtr);
        unitPtr->state = CANIF_CS_STOPPED;
        unitPtr->pendingStateIndication = CAN_CTRL_INDICATION_NONE;

        /* Create interrupt mask for a given controller. */
        createInterruptMask(unitPtr);

        /* Install the interrupts used. */
        installControllerInterrupts(unitPtr);

        /* Set default baudrate. */
        (void)modifyBaudrate(unitPtr, unitPtr->cfgCtrlPtr->CanControllerDefaultBaudrate);

    }/*End of for: ControllerId*/
}



/**
 * Checks if a baudrate is supported for a controller
 * @param Controller - controller id
 * @param Baudrate - in kbps
 * @return E_OK if supported, otherwiese E_NOT_OK
 */
Std_ReturnType Can_Hw_CheckBaudrate(uint8 Controller, const uint16 Baudrate)
{
    /** @req 4.1.2/SWS_Can_00454 */
    /* Checks that the target baudrate is found among the configured baudrates for this controller. */

    const UnitType             *canUnit = CTRL_TO_UNIT_PTR(Controller);
    const Can_ControllerConfigType *config  = canUnit->cfgCtrlPtr;
    Std_ReturnType supportedBR = E_NOT_OK;

    /* Find the baudrate config for the target baudrate. */
    for (uint32 i = 0u; i < config->CanControllerSupportedBaudratesCount; i++)
    {
        if (config->CanControllerSupportedBaudrates[i].CanControllerBaudRate == Baudrate) {
            supportedBR = E_OK;
            break;
        }
    }

    return supportedBR;
}



/**
 * Changes baudrate for a controller
 * @param Controller - controller id
 * @param Baudrate - in kpbs
 * @return E_OK if baudrate is changed, otherwise E_NOT_OK
 */
Std_ReturnType Can_Hw_ChangeBaudrate( uint8 Controller, const Can_ControllerBaudrateConfigType *baudratePtr)
{
    /** @req 4.1.2/SWS_Can_00449 */
    /** @req 4.1.2/SWS_Can_00260 *//*If re-initialization is necessary the function Can_SetBaudrate shall maintain the
                                    *CAN controller in the state STOPPED*/

    UnitType *canUnit;

    canUnit = CTRL_TO_UNIT_PTR(Controller);

    /** @req 4.1.2/SWS_Can_00453 */
    VALIDATE( (canUnit->state==CANIF_CS_STOPPED), CAN_CHANGE_BAUD_RATE_SERVICE_ID, CAN_E_TRANSITION );

    return modifyBaudrate(canUnit, baudratePtr);
}


/**
 * Changes the controller mode
 * @param Controller - controller id
 * @param Transition - type of transition to be made
 * @return CAN_OK if request accepted, otherwise CAN_NOT_OK
 */
Can_ReturnType Can_Hw_SetControllerMode(
        uint8 Controller,
        Can_StateTransitionType Transition)
{
    /** @req 4.1.2/SWS_Can_00230 */
    /** @req 4.1.2/SWS_Can_00017 */
    /** !req 4.1.2/SWS_Can_00294 *//* The function Can_SetControllerMode shall disable the wake-up interrupt, while checking the wake-up status */
    /** !req 4.1.2/SWS_Can_00197 *//* Disable interrupts */
    /** @req 4.1.2/SWS_Can_00200 *//* Detect invalid transitions */
    /** @req 4.1.2/SWS_Can_00404 *//* Hardware stopped while logical sleep active */
    /** @req 4.1.2/SWS_Can_00405 *//* Logical sleep left on CAN_T_WAKEUP */

    Can_ReturnType retVal = CAN_OK;

    UnitType *canUnit = CTRL_TO_UNIT_PTR(Controller);
    Can_UnitType *unitPtr;

    VALIDATE_RV( (canUnit->state!=CANIF_CS_UNINIT), CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_UNINIT, CAN_NOT_OK );

    /** @req 4.1.2/SWS_Can_00417 */
    switch (Transition) {
    case CAN_T_START:

        /** @req 4.1.2/SWS_Can_00409 */
        VALIDATE_RV(canUnit->state == CANIF_CS_STOPPED, CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_TRANSITION, CAN_NOT_OK);

        /** @req 4.1.2/SWS_Can_00384 *//* I.e. present conf not changed */
        /** @req 4.1.2/SWS_Can_00261 */

        SchM_Enter_Can_EA_0(); /* Enter exclusive area. *//*lint !e632 Assignment to strong type 'imask_t'. Tolerable to enter exclusive area*/

        if (0u != (canUnit->cfgCtrlPtr->Can_Arc_Flags & CAN_CTRL_LOOPBACK))
        {
            setCanHardwareMode(canUnit, CAN_HARDWARE_MODE_LOOPBACK);
        }
        else
        {
            setCanHardwareMode(canUnit, CAN_HARDWARE_MODE_NORMAL);
        }

        /** @req 4.1.2/SWS_Can_00196 */
        /** @req 4.1.2/SWS_Can_00425 */
        /* Improvement - change so global variables do not have to be referenced. */
        unitPtr = &Can_Unit[Can_Global.channelMap[Controller]];
        /* The lock count should not be changed here so call Can_Hw_EnableControllerInterrupts
         * and not Can_EnableControllerInterrupts. */
        if (unitPtr->lockCnt == 0u)
        {
            Can_Hw_EnableControllerInterrupts(Controller);
        }

        canUnit->state = CANIF_CS_STARTED;
        canUnit->pendingStateIndication = CAN_CTRL_INDICATION_PENDING_START;

        SchM_Exit_Can_EA_0(); /* Exit exclusive area*/

        break;

    case CAN_T_WAKEUP:

        /** @req 4.1.2/SWS_Can_00267 */
        /** @req 4.1.2/SWS_Can_00412 */
        VALIDATE_RV((canUnit->state == CANIF_CS_SLEEP) || (canUnit->state == CANIF_CS_STOPPED), CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_TRANSITION, CAN_NOT_OK);

        SchM_Enter_Can_EA_0(); /* Enter exclusive area. *//*lint !e632 Assignment to strong type 'imask_t'. Tolerable to enter exclusive area*/

        setCanHardwareMode(canUnit, CAN_HARDWARE_MODE_CONFIGURATION);

        canUnit->state = CANIF_CS_STOPPED;
        canUnit->pendingStateIndication = CAN_CTRL_INDICATION_PENDING_STOP;

        SchM_Exit_Can_EA_0(); /* Exit exclusive area*/

        break;

    case CAN_T_SLEEP:

        /** @req 4.1.2/SWS_Can_00265 */
        /** @req 4.1.2/SWS_Can_00411 */
        /** @req 4.1.2/SWS_Can_00258 */
        /** @req 4.1.2/SWS_Can_00290 */
        /** @req 4.1.2/SWS_Can_00257 *//*When the CAN hardware supports sleep mode and is triggered to transition into
                                        * SLEEP state, the Can module shall set the controller to the SLEEP state from
                                        * which the hardware can be woken over CAN Bus*/

        VALIDATE_RV(canUnit->state == CANIF_CS_STOPPED, CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_TRANSITION, CAN_NOT_OK);

        SchM_Enter_Can_EA_0(); /* Enter exclusive area. *//*lint !e632 Assignment to strong type 'imask_t'. Tolerable to enter exclusive area*/

        setCanHardwareMode(canUnit, CAN_HARDWARE_MODE_SLEEP);

        canUnit->state = CANIF_CS_SLEEP;
        canUnit->pendingStateIndication = CAN_CTRL_INDICATION_PENDING_SLEEP;

        SchM_Exit_Can_EA_0(); /* Exit exclusive area*/

        break;

    case CAN_T_STOP:

        /** @req 4.1.2/SWS_Can_00263 */
        /** @req 4.1.2/SWS_Can_00282 */
        /** @req 4.1.2/SWS_Can_00410 */
        /** @req 4.1.2/SWS_Can_00283 */

        VALIDATE_RV((canUnit->state == CANIF_CS_STARTED) || (canUnit->state == CANIF_CS_STOPPED), CAN_SETCONTROLLERMODE_SERVICE_ID, CAN_E_TRANSITION, CAN_NOT_OK);

        SchM_Enter_Can_EA_0(); /* Enter exclusive area. *//*lint !e632 Assignment to strong type 'imask_t'. Tolerable to enter exclusive area*/

        setCanHardwareMode(canUnit, CAN_HARDWARE_MODE_CONFIGURATION);

        canUnit->state = CANIF_CS_STOPPED;
        canUnit->pendingStateIndication = CAN_CTRL_INDICATION_PENDING_STOP;
        
        /** @req 4.1.2/SWS_Can_00426 */
        /* Improvement - change so global variables do not have to be referenced. */
        unitPtr = &Can_Unit[Can_Global.channelMap[Controller]];
        /* The lock count should not be changed here so call Can_Hw_DisableControllerInterrupts
         * and not Can_DisableControllerInterrupts. */
        if (unitPtr->lockCnt == 0u)
        {
            Can_Hw_DisableControllerInterrupts(Controller);
        }

        SchM_Exit_Can_EA_0(); /* Exit exclusive area*/

        break;

    default:

        /** @req 4.1.2/SWS_Can_00200 */
        DET_REPORTERROR(CAN_MODULE_ID,0,CAN_SETCONTROLLERMODE_SERVICE_ID,CAN_E_TRANSITION);

        retVal = CAN_NOT_OK;
        break;
    }

    return retVal;
}

/**
 *
 * @param Controller Controller identifier.
 */
void Can_Hw_DisableControllerInterrupts(uint8 Controller)
{
    UnitType *canUnit = CTRL_TO_UNIT_PTR(Controller);

    /** @req 4.1.2/SWS_Can_00205 */
    VALIDATE_NO_RV( (canUnit->state != CANIF_CS_UNINIT), CAN_DISABLECONTROLLERINTERRUPTS_SERVICE_ID, CAN_E_UNINIT );

    SET_REG2(canUnit->hwPtr->IER, 0u);
}

/**
 * Enables interrupts for a controller
 * @param Controller - controller id
 */
void Can_Hw_EnableControllerInterrupts(uint8 Controller)
{
    /** @req 4.1.2/SWS_Can_00232 */
    /** @req 4.1.2/SWS_Can_00050 */

    const UnitType *canUnit = CTRL_TO_UNIT_PTR(Controller);

    /* Get valid interrupts*/
    SET_REG2(canUnit->hwPtr->IER, canUnit->interruptMask);
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
Can_ReturnType Can_Hw_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo)
{
    /** @req 4.1.2/SWS_Can_00233 */
    /** @req 4.1.2/SWS_Can_00214 */
    /** @req 4.1.2/SWS_Can_00272 */
    /** @req 4.1.2/SWS_Can_00011 */
    /** @req 4.1.2/SWS_Can_00275 */
    /** @req 4.1.2/SWS_Can_00212 */

    const Can_HardwareObjectType *hohObj;
    UnitType *canUnit;
    HwRegType *canHw;
    Can_ReturnType retVal;
    Can_HwHandleType internalHth;
    uint32 data1;
    uint32 data2;

    /* Hth is the symbolic name for this hoh. Get the internal id */
    internalHth = Can_Global.config->CanConfigSetPtr->ArcSymbolicHohToInternalHoh[Hth];

    VALIDATE_RV( (internalHth < NUM_OF_HTHS), 0x6, CAN_E_PARAM_HANDLE, CAN_NOT_OK );

    canUnit = CTRL_TO_UNIT_PTR(Can_Global.config->CanConfigSetPtr->ArcHthToSymbolicController[internalHth]);
    hohObj  = &canUnit->cfgHohPtr[Can_Global.config->CanConfigSetPtr->ArcHthToHoh[internalHth]];
    canHw   = canUnit->hwPtr;

    SchM_Enter_Can_EA_0(); /* Enter exclusive area. *//*lint !e632 Assignment to strong type 'imask_t'. Tolerable to enter exclusive area*/

    /* Check if TxFifo is full and fill the Software Fifo*/
    if ((0u == GET_REG(canHw->SR, MASK_SR_TXFLL, SHIFT_SR_TXFLL)) && (txQueuePut(canUnit, PduInfo->swPduHandle) == E_OK)) /*lint !e9007 HARDWARE ACCESS */
    {

        if (hohObj->CanIdType == CAN_ID_TYPE_EXTENDED)
        {
            /*lint -e{845} -e{835} A zero has been given as argument tolerated to use uniform macros to set SFRs*/
            uint32 reg = SET_TXFIFO_ID(((uint32)PduInfo->id>>18u), 1u, 1u, PduInfo->id, 0u);
            SET_REG2(canHw->TXFIFO_ID, reg);
        }
        else
        {
            CAN_ASSERT(!(PduInfo->id & 0xfffff800uL));

            /*lint -e{845} -e{835} A zero has been given as argument tolerated to use uniform macros to set SFRs*/
            uint32 reg = SET_TXFIFO_ID(PduInfo->id, 0u, 0u, 0u, 0u);
            SET_REG2(canHw->TXFIFO_ID, reg);
        }

        /*lint -e{9033} Misra 10.8 Impermissible cast of composite expression */
        data1 = u32ChangeEndianess(*((const uint32*) ((const void*) (&PduInfo->sdu[0u]))));

        /*lint -e{9033} Misra 10.8 Impermissible cast of composite expression */
        data2 = u32ChangeEndianess(*((const uint32*) ((const void*) (&PduInfo->sdu[4u]))));

        SET_REG(canHw->TXFIFO_DLC, MASK_TXFIFO_DLC_DLC, SHIFT_TXFIFO_DLC_DLC, PduInfo->length);
        SET_REG2(canHw->TXFIFO_DATA1, data1);
        SET_REG2(canHw->TXFIFO_DATA2, data2);

        retVal = CAN_OK;
    }
    else
    {
        /*TxFifo is full */
        retVal = CAN_BUSY;
    }

    SchM_Exit_Can_EA_0(); /* Leave exclusive area. */

    return retVal;
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
    for (uint8 controllerId = 0u; controllerId < CAN_ARC_CTRL_CONFIG_CNT; controllerId++)
    {
        unitPtr = CTRL_TO_UNIT_PTR(controllerId);
        if( (unitPtr->cfgCtrlPtr->Can_Arc_Flags & CAN_CTRL_TX_PROCESSING_INTERRUPT) == 0u )
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
    for (uint8 controllerId = 0u; controllerId < CAN_ARC_CTRL_CONFIG_CNT; controllerId++)
    {
        unitPtr = CTRL_TO_UNIT_PTR(controllerId);
        if( (unitPtr->cfgCtrlPtr->Can_Arc_Flags & CAN_CTRL_RX_PROCESSING_INTERRUPT) == 0u )
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
    for (uint8 controllerId = 0u; controllerId < CAN_ARC_CTRL_CONFIG_CNT; controllerId++)
    {
        unitPtr = CTRL_TO_UNIT_PTR(controllerId);
        if( (unitPtr->cfgCtrlPtr->Can_Arc_Flags & CAN_CTRL_BUSOFF_PROCESSING_INTERRUPT) == 0u )
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
    for (uint8 controllerId = 0u; controllerId < CAN_ARC_CTRL_CONFIG_CNT; controllerId++)
    {
        unitPtr = CTRL_TO_UNIT_PTR(controllerId);
        if( (unitPtr->cfgCtrlPtr->Can_Arc_Flags & CAN_CTRL_ERROR_PROCESSING_INTERRUPT) == 0u )
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


Can_Arc_ModeType Can_Hw_GetControllerMode( uint8 hwCh ) {

    const UnitType            *unitPtr    = CTRL_TO_UNIT_PTR(hwCh);
    ControllerModeType hardwareMode = getCanHardwareMode(unitPtr);
    Can_Arc_ModeType mode;

    switch(hardwareMode) {
    case CAN_HARDWARE_MODE_CONFIGURATION:
        mode = CAN_CTRL_MODE_STOP;
        break;
    case CAN_HARDWARE_MODE_NORMAL:
        mode = CAN_CTRL_MODE_COMM;
        break;
    case CAN_HARDWARE_MODE_SLEEP:
        mode = CAN_CTRL_MODE_SLEEP;
        break;
    case CAN_HARDWARE_MODE_LOOPBACK:
        mode = CAN_CTRL_MODE_COMM;
        break;
    default:
        mode = CAN_CTRL_MODE_COMM;
    }

    return mode;
}

/**
 * Unitialize the module
 */
void Can_Arc_Hw_DeInit(void) {
    UnitType *unitPtr;

    for (uint8 controllerId = 0u; controllerId < CAN_ARC_CTRL_CONFIG_CNT;
            controllerId++) {
        unitPtr = CTRL_TO_UNIT_PTR(controllerId);

        resetHardware(unitPtr);

    }
}

