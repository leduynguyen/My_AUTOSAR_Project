/*
 * Xqspi_types.h
 *
 * This is a header file has been written by Arccore in order to use the 3rd party Qspi drivers.
 * It defines the macors that are used by the driver and also provides the Arccore MCU module in order
 * to provide the clock value for the driver.
 */

#ifndef XQSPI_TYPES_H_
#define XQSPI_TYPES_H_

#include "Mcu.h"

typedef uint8 u8;
typedef uint16 u16;
typedef uint32 u32;

typedef volatile uint32_t vuint32_t;

#define XST_SUCCESS                     0L
#define XST_FAILURE                     1L

#define XST_DEVICE_NOT_FOUND            2L
#define XST_DEVICE_BLOCK_NOT_FOUND      3L
#define XST_INVALID_VERSION             4L
#define XST_DEVICE_IS_STARTED           5L
#define XST_DEVICE_IS_STOPPED           6L
#define XST_FIFO_ERROR                  7L

#define XST_REGISTER_ERROR              14L		/* a register did not contain the expected value */
#define XST_DEVICE_BUSY                 21L	/* device is busy */
#define XST_SPI_TRANSFER_DONE       	1152	/* data transfer is complete */
#define XST_SPI_RECEIVE_OVERRUN     	1154	/* device overruns receive register */
#define XST_SPI_TRANSMIT_UNDERRUN   	1153	/* slave underruns transmit register */

#define XIL_COMPONENT_IS_READY     		0x11111111  /**< component has been initialized */
#define XIL_COMPONENT_IS_STARTED   		0x22222222  /**< component has been started */

/******************************************************************/

/* Canonical definitions for peripheral PS7_QSPI_0 */
#define XPAR_XQSPIPS_0_DEVICE_ID 		0
#define XPAR_XQSPIPS_0_BASEADDR 		0xE000D000
#define XPAR_XQSPIPS_0_HIGHADDR 		0xE000DFFF
#define XPAR_XQSPIPS_0_QSPI_CLK_FREQ_HZ MCU_ARC_CLOCK_LQSPI_FREQUENCY
#define XPAR_XQSPIPS_0_QSPI_MODE 		0

/* Definitions for driver QSPIPS */
#define XPAR_XQSPIPS_NUM_INSTANCES 		1

/* Definitions for peripheral PS7_QSPI_0 */
#define XPAR_PS7_QSPI_0_QSPI_MODE 		0

/* Definitions for peripheral PS7_QSPI_LINEAR_0 */
#define XPAR_PS7_QSPI_LINEAR_0_S_AXI_BASEADDR 0xFC000000UL
#define XPAR_PS7_QSPI_LINEAR_0_S_AXI_HIGHADDR 0xFCFFFFFFUL

#define Xil_In32(address)  							((u32)(*(vuint32_t*)(address)))
#define Xil_Out32(address, val)						(*(vuint32_t*)(address) = val)

//xqspips_options.c
#define Xil_AssertNonvoid(_condition) \
        if( !(_condition) ) { \
          return XST_FAILURE; \
        }
#define Xil_AssertVoid(_condition) \
        if( !(_condition) ) { \
          return; \
        }
#define Xil_AssertVoidAlways()


#endif /* XQSPI_TYPES_H_ */
