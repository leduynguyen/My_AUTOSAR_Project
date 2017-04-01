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

#ifndef LIN_JAC_H_
#define LIN_JAC_H_


#define UART_1_ADDRESS (0x4806A000 + L3_OFFSET)
#define UART_2_ADDRESS (0x4806C000 + L3_OFFSET)
#define UART_3_ADDRESS (0x48020000 + L3_OFFSET)
#define UART_4_ADDRESS (0x4806E000 + L3_OFFSET)
#define UART_5_ADDRESS (0x48066000 + L3_OFFSET)
#define UART_6_ADDRESS (0x48068000 + L3_OFFSET)
#define UART_7_ADDRESS (0x48420000 + L3_OFFSET)
#define UART_8_ADDRESS (0x48422000 + L3_OFFSET)
#define UART_9_ADDRESS (0x48424000 + L3_OFFSET)
#define UART_10_ADDRESS (0x4AE2B000 + L3_OFFSET)

#define MAX_UART_CHANNELS (8)
#define DATA_BUFFER_SIZE (128)

#define SYSC_RESET_MASK (0x02U)
#define SYSS_RESET_PROGRESS_MASK (0x1U)
#define LCR_MODE_A_MASK (0x80U)
#define LCR_MODE_B_MASK (0xBFU)
#define LCR_MODE_OP (0xFCU) /* This needs to be unset for op mode */
#define EFR_ENHANCED_EN_MASK (0x10U)
#define MCR_ENABLE_TLR_MASK (0x40U)
#define MCR_LOOPBACK_MASK (0x10U)
#define TLR_RX_TRIGGER_1_MASK (0x10U)
#define TLR_RX_TRIGGER_4_MASK (0x40U)
#define TLR_TX_TRIGGER_1_MASK (0x01U)
#define TLR_TX_TRIGGER_4_MASK (0x04U)
#define MDR1_DISABLE_UART_MASK (0x7U)
#define IER_SLEEP_BIT (0x10U)
#define IER_RHR_IT_MASK (0x1U)
#define IER_THR_IT_MASK (0x2U)
#define LCR_BREAK_BIT (0x40U)
#define FCR_ENABLE_FIFO_MASK (0x01U)
#define FCR_ENABLE_DMA_MASK (0x08U)
#include "Std_Types.h"
#define LSR_TX_EMPTY_BIT (0x40U)
#define LSR_RX_DATA_PRESENT_BIT (0x1U)

#define IIR_INTERRUPT_TYPE_MASK (0x3EU)
#define IIR_RX_TIMEOUT (0x6U)
#define IIR_RECEIVER_ERROR (0x3U)
#define IIR_TX_INTERRUPT (0x2U)
#define IIR_RX_INTERRUPT (0x1U)

typedef struct {
  uint8 Channel;
  uint32 BaudRate;
} UartChannelConfigType;

typedef struct {
  uint8 NumChannels;
  UartChannelConfigType* ChannelConfigs;
} UartConfigType;

void Uart_EnableLoopback(uint8 channel);
void Uart_DisableLoopback(uint8 channel);

/* Useless fact: 48 MHz is just below VHF bands used for TV channels
   in Europe! */
#define UART_FIXED_CLOCK_RATE (48000000) /* 48 MHz */

typedef struct {
  volatile uint32 THR_RHR_DLL;   /* Offset: 0x00 */
  volatile uint32 IER_DLH;       /* Offset: 0x04 */
  volatile uint32 IIR_FCR_EFR;   /* Offset: 0x08 */
  volatile uint32 LCR;           /* Offset: 0x0C */
  volatile uint32 MCR_XON1;      /* Offset: 0x10 */
  volatile uint32 LSR_XON2;      /* Offset: 0x14 */
  volatile uint32 MSR_XOFF1;     /* Offset: 0x18 */
  volatile uint32 TLR_SPR_XOFF2; /* Offset: 0x1C */
  volatile uint32 MDR1;          /* Offset: 0x20 */
  volatile uint32 MDR2;          /* Offset: 0x24 */
  volatile uint32 SFLSR_TXFLL;   /* Offset: 0x28 */
  volatile uint32 TXFLH_RESUME;  /* Offset: 0x2C */
  volatile uint32 SFREGL_RXFLL;  /* Offset: 0x30 */
  volatile uint32 RXFLH_SFREGH;  /* Offset: 0x34 */
  volatile uint32 BLR_UASR;      /* Offset: 0x38 */
  volatile uint32 ACREG;         /* Offset: 0x3C */
  volatile uint32 SCR;           /* Offset: 0x40 */
  volatile uint32 SSR;           /* Offset: 0x44 */
  volatile uint32 EBLR;          /* Offset: 0x48 */
  volatile uint32 : 32; /* Unused   Offset: 0x4C */
  volatile uint32 MVR;           /* Offset: 0x50 */
  volatile uint32 SYSC;          /* Offset: 0x54 */
  volatile uint32 SYSS;          /* Offset: 0x58 */
  volatile uint32 WER;          /* Offset: 0x5C */
  volatile uint32 CFPS;          /* Offset: 0x60 */
  volatile uint32 RXFIFO_LVL;    /* Offset: 0x64 */
  volatile uint32 TXFIFO_LVL;          /* Offset: 0x68 */
  volatile uint32 IER2;          /* Offset: 0x6C */
  volatile uint32 ISR2;          /* Offset: 0x70 */
  volatile uint32 FREQ_SEL;          /* Offset: 0x74 */
  volatile uint32 : 32;          /* Reserved: Offset 0x78 */
  volatile uint32 : 32;          /* Reserved: Offset 0x7C */
  volatile uint32 MDR3;          /* Offset 0x80 */
  volatile uint32 TX_DMA_THRESH;  /* Offset: 0x84 */
} Uart_reg; /* Total: 136 bytes */

#endif
