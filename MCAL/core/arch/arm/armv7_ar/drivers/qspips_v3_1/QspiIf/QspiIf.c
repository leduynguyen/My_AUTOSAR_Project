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

#include "QspiIf.h"
#include "xqspips.h"        /* QSPI device driver */
#include "Mcu.h"

/* ----------------------------[private define]------------------------------*/
#define QSPIIF_DEVICE_ID		XPAR_XQSPIPS_0_DEVICE_ID

#define QSPIIF_WR_EN_CMD		0x06u
#define QSPIIF_WR_CMD			0x02u
#define QSPIIF_RD_CMD			0x03u
#define QSPIIF_RD_STAT_CMD		0x05u
#define QSPIIF_RD_ID_CMD		0x9Fu
#define QSPIIF_RD_ID_CMD_SIZE	4u
#define QSPIIF_Q_RD_CMD		0x6Bu
#define QSPIIF_BLK_ER_CMD		0xC7u
#define QSPIIF_BLK_ER_CMD_SIZE	1u
#define	QSPIIF_SEC_ER_CMD		0xD8u
#define	QSPIIF_SEC_ER_CMD_SIZE	4u

#define QSPIIF_FLS_OK_STATUS 	0x01u

#define QSPIIF_CMD_IDX			0u 			/* Index of command in buffers */
#define QSPIIF_ADDR1_IDX		1u 			/* Index of address in buffers */
#define QSPIIF_ADDR2_IDX		2u 			/* Index of address in buffers */
#define QSPIIF_ADDR3_IDX		3u 			/* Index of address in buffers */
#define QSPIIF_DUMMYBYTES		0x090823u	/*Random Dummy values that is used by ReadId*/

#define QSPIIF_ADDR1_MSK				0x00FF0000u
#define QSPIIF_ADDR2_MSK				0x0000FF00u
#define QSPIIF_ADDR3_MSK				0x000000FFu
#define QSPIIF_ADDR1_SHIFT				16u
#define QSPIIF_ADDR2_SHIFT				8u

#define QSPIIF_REG_CFG_MANSTRTEN_SHIFT	15u
#define QSPIIF_REG_CFG_PCS_SHIFT		10u
#define QSPIIF_SPI_EN					0x00000001u
#define QSPIIF_SPI_DIS					0x00000000u
#define QSPIIF_MICRON_LQSPI_REG_VAL	0x80000003u
#define QSPIIF_LQSPI_MAP_START			0xFC000000u
#define QSPIIF_LQSPI_MAP_END			0xFDFFFFFFu
#define QSPIIF_LQSPI_CFG_RESET_VAL		0x01D002EBu
#define QSPIIF_MAX_OP_FREQ				54000000u

/* ----------------------------[private macro]-------------------------------*/
#define WRITE_HEADER(_Cmd, _Addr)	\
    WriteBuffer[QSPIIF_CMD_IDX]   = _Cmd;	\
    WriteBuffer[QSPIIF_ADDR1_IDX] = (uint8)(((uint32)_Addr & QSPIIF_ADDR1_MSK) >> QSPIIF_ADDR1_SHIFT);		\
    WriteBuffer[QSPIIF_ADDR2_IDX] = (uint8)(((uint32)_Addr & QSPIIF_ADDR2_MSK) >> QSPIIF_ADDR2_SHIFT);		\
    WriteBuffer[QSPIIF_ADDR3_IDX] = (uint8) ((uint32)_Addr & QSPIIF_ADDR3_MSK);

#define VALIDATE_FUNC_RV(_func)		\
        if(_func != XST_SUCCESS) {	\
            return E_NOT_OK;		\
        }
#define VALIDATE_FUNC(_func)		\
        if(_func != XST_SUCCESS) {	\
            return;		\
        }

#define QSPIIF_PRESCALAR(val)   XQSPIPS_CLK_PRESCALE_## val

/* ----------------------------[private macro]-------------------------------*/

uint8 ReadBuffer[FLASH_PAGE_SIZE + HEADER_SIZE + DUMMY_RD_BYTES] __attribute__ ((aligned (4)));
uint8 WriteBuffer[FLASH_PAGE_SIZE + HEADER_SIZE] __attribute__ ((aligned (4)));


static XQspiPs Qspi;

/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
static uint8 flashReadID(void);
static void lQSPI_Init(void);
static void lQSPI_Uninit(void);

/* ----------------------------[private functions]---------------------------*/
/**
 * Reads the flash Identification in order to test the initialization
 * @return
 */
static uint8 flashReadID(void) {
    WRITE_HEADER(QSPIIF_RD_ID_CMD, QSPIIF_DUMMYBYTES)

    VALIDATE_FUNC_RV(
            XQspiPs_PolledTransfer(&Qspi, WriteBuffer, ReadBuffer, QSPIIF_RD_ID_CMD_SIZE))

    return E_OK;
}

/**
 * LQSPI Initializing
 */
static void lQSPI_Init(void) {
    VALIDATE_FUNC(
            XQspiPs_SetOptions(&Qspi, (uint32)XQSPIPS_LQSPI_MODE_OPTION | (uint32)XQSPIPS_HOLD_B_DRIVE_OPTION))
    /*lint -e{9033,923} Not changeable as its a part of the Xilinx driver */
    XQspiPs_SetLqspiConfigReg(&Qspi, QSPIIF_MICRON_LQSPI_REG_VAL);
}
/**
 * LQSPI Uninitializing
 */
static void lQSPI_Uninit(void) {
    /*lint -e{9033,923} Not changeable as its a part of the Xilinx driver */
    XQspiPs_SetLqspiConfigReg(&Qspi, QSPIIF_LQSPI_CFG_RESET_VAL);
}
/**
 * Setting QSpi prescalar according to the input frequency
 */
static void setPrescalar(void) {
    /*Setting the Frequency at or below 54 Mhz*/
    uint32 presclr = MCU_ARC_CLOCK_LQSPI_FREQUENCY/QSPIIF_MAX_OP_FREQ;
    if (presclr <= 2u) { /*lint !e774 CONFIGURATION */
        VALIDATE_FUNC(XQspiPs_SetClkPrescaler(&Qspi, XQSPIPS_CLK_PRESCALE_2))
    }
    else if (presclr <= 4u) { /*lint !e774 CONFIGURATION */
        VALIDATE_FUNC(XQspiPs_SetClkPrescaler(&Qspi, XQSPIPS_CLK_PRESCALE_4))
    }
    else if (presclr <= 8u) { /*lint !e774 CONFIGURATION */
        VALIDATE_FUNC(XQspiPs_SetClkPrescaler(&Qspi, XQSPIPS_CLK_PRESCALE_8))
    }
    else if (presclr <= 16u) { /*lint !e774 CONFIGURATION */
        VALIDATE_FUNC(XQspiPs_SetClkPrescaler(&Qspi, XQSPIPS_CLK_PRESCALE_16))
    }
    else if (presclr <= 32u) { /*lint !e774 CONFIGURATION */
        VALIDATE_FUNC(XQspiPs_SetClkPrescaler(&Qspi, XQSPIPS_CLK_PRESCALE_32))
    }
    else if (presclr <= 64u) { /*lint !e774 CONFIGURATION */
        VALIDATE_FUNC(XQspiPs_SetClkPrescaler(&Qspi, XQSPIPS_CLK_PRESCALE_64))
    }
    else if (presclr <= 128u) { /*lint !e774 CONFIGURATION */
        VALIDATE_FUNC(XQspiPs_SetClkPrescaler(&Qspi, XQSPIPS_CLK_PRESCALE_128))
    }
    else if (presclr <= 256u) { /*lint !e774 CONFIGURATION */
        VALIDATE_FUNC(XQspiPs_SetClkPrescaler(&Qspi, XQSPIPS_CLK_PRESCALE_256))
    }
    else{
        /* Input frequency too high for internal divider */
    }
}
/* ----------------------------[public functions]----------------------------*/

/**
 * Initializing Qspi and Buffers
 */
void QspiIf_Arc_Init(void) {
    XQspiPs_Config *config;

    config = XQspiPs_LookupConfig(QSPIIF_DEVICE_ID);

    VALIDATE_FUNC(XQspiPs_CfgInitialize(&Qspi, config, config->BaseAddress))

    VALIDATE_FUNC(XQspiPs_SelfTest(&Qspi))

    memset(WriteBuffer, 0x00, sizeof(WriteBuffer));
    memset(ReadBuffer, 0x00, sizeof(ReadBuffer));

    VALIDATE_FUNC(
            XQspiPs_SetOptions(&Qspi, (uint32)XQSPIPS_MANUAL_START_OPTION | (uint32)XQSPIPS_FORCE_SSELECT_OPTION | (uint32)XQSPIPS_HOLD_B_DRIVE_OPTION))

    setPrescalar();

    VALIDATE_FUNC(XQspiPs_SetSlaveSelect(&Qspi))

    VALIDATE_FUNC(flashReadID())
}

/**
 * Flash Write using Qspi
 * 	*	Write enable
 * 	*	Write to address
 * 	*	Poll for status
 * Send
 * @param Address
 * @param ByteCount
 * @param Command
 * @return
 */
Std_ReturnType QspiIf_Arc_Write(uint32 address, uint32 bytecnt) {
    uint8 QspiIf_FlsStat[2] = { 0, 0 };
    __balign(4) uint8 QspiIf_WrEnCmd =  QSPIIF_WR_EN_CMD ;
    __balign(4) uint8 QspiIf_RdStatCmd[2] = { QSPIIF_RD_STAT_CMD, 0 };
    VALIDATE_FUNC_RV(
            XQspiPs_PolledTransfer(&Qspi, &QspiIf_WrEnCmd, NULL, sizeof(QspiIf_WrEnCmd)))

    WRITE_HEADER(QSPIIF_WR_CMD, address)

    VALIDATE_FUNC_RV(
            XQspiPs_PolledTransfer(&Qspi, WriteBuffer, NULL, bytecnt + HEADER_SIZE))

    do {
        VALIDATE_FUNC_RV(XQspiPs_PolledTransfer(&Qspi, QspiIf_RdStatCmd, QspiIf_FlsStat,
                sizeof(QspiIf_RdStatCmd)))
    } while (QspiIf_FlsStat[1] != 0);

    return E_OK;

}

/**
 * Flash Read using Qspi
 * @param address
 * @param bytecnt
 * @return
 */
Std_ReturnType QspiIf_Arc_Read(uint32 address, uint32 bytecnt) {

    WRITE_HEADER(QSPIIF_RD_CMD, address)

    VALIDATE_FUNC_RV (XQspiPs_PolledTransfer(&Qspi, WriteBuffer, ReadBuffer,
            (bytecnt + HEADER_SIZE + DUMMY_RD_BYTES)))

    return E_OK;

}

/**
 * Flash Erase using Qspi
 * 	* Bulk erase
 * 	* else sector erase
 *
 * @param address
 * @param bytecnt
 * @return
 */
Std_ReturnType QspiIf_Arc_Erase(uint32 address, uint32 bytecnt) {
    uint8 QspiIf_FlsStat[2] = { 0, 0 };
    __balign(4) uint8 QspiIf_WrEnCmd =  QSPIIF_WR_EN_CMD ;
    __balign(4) uint8 QspiIf_RdStatCmd[2] = { QSPIIF_RD_STAT_CMD, 0 };
    uint32 jobAddr = address;
    if (bytecnt == FLS_TOTAL_SIZE) {
        VALIDATE_FUNC_RV(
                XQspiPs_PolledTransfer(&Qspi, &QspiIf_WrEnCmd, NULL, sizeof(QspiIf_WrEnCmd)))

        WriteBuffer[QSPIIF_CMD_IDX] = QSPIIF_BLK_ER_CMD;

        VALIDATE_FUNC_RV(
                XQspiPs_PolledTransfer(&Qspi, WriteBuffer, NULL, QSPIIF_BLK_ER_CMD_SIZE))

        do {
            VALIDATE_FUNC_RV (XQspiPs_PolledTransfer(&Qspi, QspiIf_RdStatCmd,
                    QspiIf_FlsStat, sizeof(QspiIf_RdStatCmd)))

        } while (QspiIf_FlsStat[1] != 0);

    } else if  (bytecnt > 0u) {
        for (uint32 Sector = 0; Sector < (((bytecnt-1) / FLASH_SECTOR_SIZE) + 1); Sector++) {
            VALIDATE_FUNC_RV(
                    XQspiPs_PolledTransfer(&Qspi, &QspiIf_WrEnCmd, NULL, sizeof(QspiIf_WrEnCmd)))

            WRITE_HEADER(QSPIIF_SEC_ER_CMD, jobAddr)

            VALIDATE_FUNC_RV(
                    XQspiPs_PolledTransfer(&Qspi, WriteBuffer, NULL, QSPIIF_SEC_ER_CMD_SIZE))
            do {
                VALIDATE_FUNC_RV (XQspiPs_PolledTransfer(&Qspi, QspiIf_RdStatCmd,
                        QspiIf_FlsStat, sizeof(QspiIf_RdStatCmd)))
            } while (QspiIf_FlsStat[1] != 0);

            jobAddr = jobAddr + FLASH_SECTOR_SIZE;
        }
    } else {
        /* For Lint */
    }
    return E_OK;
}
/**
 * Fast read function
 * @param address
 * @param bytecnt
 * @return
 */
Std_ReturnType QspiIf_Arc_Fast_Read(uint32 address, uint32 bytecnt) {
    WRITE_HEADER(QSPIIF_Q_RD_CMD, address)

    VALIDATE_FUNC_RV (XQspiPs_PolledTransfer(&Qspi, WriteBuffer, ReadBuffer,
            (bytecnt + HEADER_SIZE + DUMMY_RD_BYTES)))

    return E_OK;
}

/**
 * LQSPI read function
 * @param address
 * @param bytecnt
 * @return
 */
Std_ReturnType QspiIf_Arc_LQSPI_Read(uint32 address, uint32 bytecnt) {
    if (((address >= QSPIIF_LQSPI_MAP_START)
            && (address <= QSPIIF_LQSPI_MAP_END))
            && ((bytecnt > 1u) && ((bytecnt + address) <= QSPIIF_LQSPI_MAP_END))) {
        lQSPI_Init();
        VALIDATE_FUNC_RV(
                XQspiPs_LqspiRead(&Qspi, ReadBuffer, address, bytecnt))
        lQSPI_Uninit();
        QspiIf_Arc_Init();
        return E_OK ;
    }
    return E_NOT_OK ;
}

