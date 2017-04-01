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

/** @tagSettings DEFAULT_ARCHITECTURE=TMS570 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#define SPI_IRQ_SOURCE 1

/* SourceId : SPI_SourceId_068 */
/* Requirements : AR_SPI_SR15 */
#include "Spi.h"
#include "isr.h"

#if (SPI_HARDWAREUNIT0_ACTIVE == STD_ON)
ISR( Spi_IrqUnit0TxRxERR )
    {
    Spi_IrqTxRxERR(0) ;
    }

ISR( Spi_IrqUnit0TxRx )    {
    Spi_IrqTxRx(0) ;
    }
#endif

#if (SPI_HARDWAREUNIT1_ACTIVE == STD_ON)
ISR( Spi_IrqUnit1TxRxERR )
    {
    Spi_IrqTxRxERR(1) ;
    }

ISR( Spi_IrqUnit1TxRx )
    {
    Spi_IrqTxRx(1) ;
    }
#endif

#if (SPI_HARDWAREUNIT2_ACTIVE == STD_ON)
ISR( Spi_IrqUnit2TxRxERR )
    {
        Spi_IrqTxRxERR(2) ;
    }

ISR( Spi_IrqUnit2TxRx )
    {
    Spi_IrqTxRx(2) ;
    }
#endif

#if (SPI_HARDWAREUNIT3_ACTIVE == STD_ON)
ISR( Spi_IrqUnit3TxRxERR )
    {
        Spi_IrqTxRxERR(3) ;
    }

ISR( Spi_IrqUnit3TxRx )
    {
    Spi_IrqTxRx(3) ;
    }
#endif

#if (SPI_HARDWAREUNIT4_ACTIVE == STD_ON)
ISR( Spi_IrqUnit4TxRxERR )
    {
        Spi_IrqTxRxERR(4) ;
    }

ISR( Spi_IrqUnit4TxRx )
    {
    Spi_IrqTxRx(4) ;
    }
#endif

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
#if ((SPI_HARDWAREUNIT1_ACTIVE == STD_ON) || (SPI_HARDWAREUNIT3_ACTIVE == STD_ON))
ISR( Dma_IsrBTC )
{
    /* Call the Notification */
    Spi_DlcBlockCbk();
}
#endif
#endif /* defined(CFG_TMS570LS12X) */
