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
/** @tagSettings DEFAULT_ARCHITECTURE=MPC5777M */

#ifndef MESSAGERAM_H_
#define MESSAGERAM_H_

/*
 * Lint Exceptions For this file:
 * - Allow use of union based types (9018)
 */
/*lint -save -e9018*/

/* ============================================================================
   =============================== Module: MessageRAM =========================
   ============================================================================ */

/*
 * 0xFFED4000 - 0xFFED7FFF = 0x4000	Shared CAN Message RAM
 * 0xFFED8000 - 0xFFED9000 = 0x1000	Shared CAN Message RAM (extended)
 *
 * One message RAM = 0x4400 (max)
 *
 */


    typedef union {
        vuint32_t R;
        struct {
            vuint8_t DB[4];
        } B;
    }Data;


//MessageRAM structure
   struct M_CAN_SIDF_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t SFT:2;
                vuint32_t SFEC:3;
                vuint32_t SFID1:11;
                vuint32_t :1;
                vuint32_t SFID2:11;
            } B;
        } S;                          /* Standard Message ID Filter Element */
    };

    struct M_CAN_EIDF_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t EFEC:3;
                vuint32_t EFID1:29;
            } B;
        } F0;                          /* Extended Message ID Filter Element */

        union {
            vuint32_t R;
            struct {
                vuint32_t EFT:2;
                vuint32_t :1;
                vuint32_t EFID2:29;
            } B;
        } F1;                          /* Extended Message ID Filter Element */
    };

   struct M_CAN_Tx_FIFO_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t ESI:1;
                vuint32_t XTD:1;
                vuint32_t RTR:1;
                vuint32_t ID:29;
            } B;
        } E0;                          /* Tx Event FIFO Element */

        union {
            vuint32_t R;
            struct {
                vuint32_t MM:8;
                vuint32_t ET:2;
                vuint32_t EDL:1;
                vuint32_t BRS:1;
                vuint32_t DLC:4;
                vuint32_t TXTS:16;
            } B;
        } E1;                          /* Tx Event FIFO Element */
    };

   struct M_CAN_Tx_BUF_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t:1;
                vuint32_t XTD:1;
                vuint32_t RTR:1;
                vuint32_t ID:29;
            } B;
        } T0;                          /* Tx Buffer Element */

        union {
            vuint32_t R;
            struct {
                vuint32_t MM:8;
                vuint32_t EFC:1;
                vuint32_t :3;
                vuint32_t DLC:4;
                vuint32_t :16;
            } B;
        } T1;                          /* Tx Buffer Element */
        Data TD[2];               /* Tx Buffer Element */
    };

       struct M_CAN_Rx_FIFO_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t ESI:1;
                vuint32_t XTD:1;
                vuint32_t RTR:1;
                vuint32_t ID:29;
            } B;
        } R0;                          /* Rx FIFO Element */

        union {
            vuint32_t R;
            struct {
                vuint32_t ANMF:1;
                vuint32_t FIDX:7;
                vuint32_t :2;
                vuint32_t EDL:1;
                vuint32_t BRS:1;
                vuint32_t DLC:4;
                vuint32_t RXTS:16;
            } B;
        } R1;                          /* Rx FIFO Element */

        Data RD[2];
    };

/*lint -restore */
#endif /* MESSAGERAM_H_ */
