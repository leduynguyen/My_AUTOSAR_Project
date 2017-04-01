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

#ifndef RH850_OSTM_H_
#define RH850_OSTM_H_

struct OSTM_reg {
    vuint32_t OSTMnCMP;
    vuint32_t OSTMnCNT;
    uint32_t  pad1;
    uint32_t  pad2;
    vuint8_t OSTMnTE;
    uint8_t  pad3[3];
    vuint8_t OSTMnTS;
    uint8_t  pad4[3];
    vuint8_t OSTMnTT;       /* 0x18 */
    uint8_t  pad5[3];
    uint8_t  pad9[4];       /* 0x1c */
    vuint8_t OSTMnCTL;      /* 0x20 */
    uint8_t  pad6[3];
    vuint8_t OSTMnEMU;      /* 0x24 */
    uint8_t  pad7[3];
    uint32_t  pad8[(0x100-0x24-4)/4];   /* align to 0x100 */
};

#if defined(CFG_RH850F1H)
#define OSTM_BASE   0xFFD70000ul
#elif defined(CFG_RH850F1L)
#define OSTM_BASE   0xFFEC0000ul
#else
#error No base defined
#endif


#define OSTMp           ((struct OSTM_reg *)OSTM_BASE)
#define OSTM            (*(struct OSTM_reg *)OSTM_BASE)


#endif /* RH850_OSTM_H_ */
