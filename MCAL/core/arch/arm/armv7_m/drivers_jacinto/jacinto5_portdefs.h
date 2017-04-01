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

#ifndef JACINTO5_PORTDEFS_H_
#define JACINTO5_PORTDEFS_H_


/* Ball: P3 */
#define PIN_CTRL_REG_ADDR_P3 0x48140800UL

/* Ball: P2 */
#define PIN_CTRL_REG_ADDR_P2 0x48140804UL
#ifndef PIN_FUNCTION_P2_DIO
#define PIN_FUNCTION_P2_DIO 0x80UL
#endif
#ifndef PIN_P2_GPIO
#define PIN_P2_GPIO 0u
#define PIN_P2_GPIO_PIN 0u
#endif

/* Ball: P1 */
#define PIN_CTRL_REG_ADDR_P1 0x48140808UL

/* Ball: P5 */
#define PIN_CTRL_REG_ADDR_P5 0x4814080CUL

/* Ball: P4 */
#define PIN_CTRL_REG_ADDR_P4 0x48140810UL

/* Ball: P6 */
#define PIN_CTRL_REG_ADDR_P6 0x48140814UL

/* Ball: W6 */
#define PIN_CTRL_REG_ADDR_W6 0x48140818UL
#ifndef PIN_FUNCTION_W6_DIO
#define PIN_FUNCTION_W6_DIO 0x80UL
#endif
#ifndef PIN_W6_GPIO
#define PIN_W6_GPIO 1u
#define PIN_W6_GPIO_PIN 7u
#endif

/* Ball: Y6 */
#define PIN_CTRL_REG_ADDR_Y6 0x4814081CUL
#ifndef PIN_FUNCTION_Y6_DIO
#define PIN_FUNCTION_Y6_DIO 0x80UL
#endif
#ifndef PIN_Y6_GPIO
#define PIN_Y6_GPIO 0u
#define PIN_Y6_GPIO_PIN 1u
#endif

/* Ball: N1 */
#define PIN_CTRL_REG_ADDR_N1 0x48140820UL
#ifndef PIN_FUNCTION_N1_DIO
#define PIN_FUNCTION_N1_DIO 0x80UL
#endif
#ifndef PIN_N1_GPIO
#define PIN_N1_GPIO 0u
#define PIN_N1_GPIO_PIN 2u
#endif

/* Ball: R7 */
#define PIN_CTRL_REG_ADDR_R7 0x48140824UL
#ifndef PIN_FUNCTION_R7_DIO
#define PIN_FUNCTION_R7_DIO 0x80UL
#endif
#ifndef PIN_R7_GPIO
#define PIN_R7_GPIO 0u
#define PIN_R7_GPIO_PIN 3u
#endif

/* Ball: Y5 */
#define PIN_CTRL_REG_ADDR_Y5 0x48140828UL
#ifndef PIN_FUNCTION_Y5_DIO
#define PIN_FUNCTION_Y5_DIO 0x80UL
#endif
#ifndef PIN_Y5_GPIO
#define PIN_Y5_GPIO 0u
#define PIN_Y5_GPIO_PIN 4u
#endif

/* Ball: Y3 */
#define PIN_CTRL_REG_ADDR_Y3 0x4814082CUL
#ifndef PIN_FUNCTION_Y3_DIO
#define PIN_FUNCTION_Y3_DIO 0x80UL
#endif
#ifndef PIN_Y3_GPIO
#define PIN_Y3_GPIO 0u
#define PIN_Y3_GPIO_PIN 5u
#endif

/* Ball: Y4 */
#define PIN_CTRL_REG_ADDR_Y4 0x48140830UL
#ifndef PIN_FUNCTION_Y4_DIO
#define PIN_FUNCTION_Y4_DIO 0x80UL
#endif
#ifndef PIN_Y4_GPIO
#define PIN_Y4_GPIO 0u
#define PIN_Y4_GPIO_PIN 6u
#endif

/* Ball: L5 */
#define PIN_CTRL_REG_ADDR_L5 0x48140834UL

/* Ball: R5 */
#define PIN_CTRL_REG_ADDR_R5 0x48140838UL
#ifndef PIN_FUNCTION_R5_DIO
#define PIN_FUNCTION_R5_DIO 0x80UL
#endif
#ifndef PIN_R5_GPIO
#define PIN_R5_GPIO 0u
#define PIN_R5_GPIO_PIN 8u
#endif

/* Ball: H1 */
#define PIN_CTRL_REG_ADDR_H1 0x4814083CUL
#ifndef PIN_FUNCTION_H1_DIO
#define PIN_FUNCTION_H1_DIO 0x80UL
#endif
#ifndef PIN_H1_GPIO
#define PIN_H1_GPIO 0u
#define PIN_H1_GPIO_PIN 9u
#endif

/* Ball: R4 */
#define PIN_CTRL_REG_ADDR_R4 0x48140840UL

/* Ball: L3 */
#define PIN_CTRL_REG_ADDR_L3 0x48140844UL

/* Ball: K2 */
#define PIN_CTRL_REG_ADDR_K2 0x48140848UL

/* Ball: K1 */
#define PIN_CTRL_REG_ADDR_K1 0x4814084CUL

/* Ball: J2 */
#define PIN_CTRL_REG_ADDR_J2 0x48140850UL

/* Ball: J1 */
#define PIN_CTRL_REG_ADDR_J1 0x48140854UL

/* Ball: L4 */
#define PIN_CTRL_REG_ADDR_L4 0x48140858UL

/* Ball: M5 */
#define PIN_CTRL_REG_ADDR_M5 0x4814085CUL

/* Ball: R6 */
#define PIN_CTRL_REG_ADDR_R6 0x48140860UL

/* Ball: M3 */
#define PIN_CTRL_REG_ADDR_M3 0x48140864UL

/* Ball: M4 */
#define PIN_CTRL_REG_ADDR_M4 0x48140868UL

/* Ball: L2 */
#define PIN_CTRL_REG_ADDR_L2 0x4814086CUL

/* Ball: L1 */
#define PIN_CTRL_REG_ADDR_L1 0x48140870UL

/* Ball: M6 */
#define PIN_CTRL_REG_ADDR_M6 0x48140874UL

/* Ball: U5 */
#define PIN_CTRL_REG_ADDR_U5 0x48140878UL

/* Ball: V3 */
#define PIN_CTRL_REG_ADDR_V3 0x4814087CUL

/* Ball: M1 */
#define PIN_CTRL_REG_ADDR_M1 0x48140880UL

/* Ball: M2 */
#define PIN_CTRL_REG_ADDR_M2 0x48140884UL

/* Ball: V4 */
#define PIN_CTRL_REG_ADDR_V4 0x48140888UL

/* Ball: T6 */
#define PIN_CTRL_REG_ADDR_T6 0x4814088CUL

/* Ball: R3 */
#define PIN_CTRL_REG_ADDR_R3 0x48140890UL

/* Ball: N6 */
#define PIN_CTRL_REG_ADDR_N6 0x48140894UL

/* Ball: U6 */
#define PIN_CTRL_REG_ADDR_U6 0x48140898UL
#ifndef PIN_FUNCTION_U6_DIO
#define PIN_FUNCTION_U6_DIO 0x80UL
#endif
#ifndef PIN_U6_GPIO
#define PIN_U6_GPIO 0u
#define PIN_U6_GPIO_PIN 10u
#endif

/* Ball: AA5 */
#define PIN_CTRL_REG_ADDR_AA5 0x4814089CUL
#ifndef PIN_FUNCTION_AA5_DIO
#define PIN_FUNCTION_AA5_DIO 0x80UL
#endif
#ifndef PIN_AA5_GPIO
#define PIN_AA5_GPIO 0u
#define PIN_AA5_GPIO_PIN 11u
#endif

/* Ball: N2 */
#define PIN_CTRL_REG_ADDR_N2 0x481408A0UL
#ifndef PIN_FUNCTION_N2_DIO
#define PIN_FUNCTION_N2_DIO 0x80UL
#endif
#ifndef PIN_N2_GPIO
#define PIN_N2_GPIO 0u
#define PIN_N2_GPIO_PIN 12u
#endif

/* Ball: V6 */
#define PIN_CTRL_REG_ADDR_V6 0x481408A4UL
#ifndef PIN_FUNCTION_V6_DIO
#define PIN_FUNCTION_V6_DIO 0x80UL
#endif
#ifndef PIN_V6_GPIO
#define PIN_V6_GPIO 0u
#define PIN_V6_GPIO_PIN 13u
#endif

/* Ball: V5 */
#define PIN_CTRL_REG_ADDR_V5 0x481408A8UL
#ifndef PIN_FUNCTION_V5_DIO
#define PIN_FUNCTION_V5_DIO 0x80UL
#endif
#ifndef PIN_V5_GPIO
#define PIN_V5_GPIO 0u
#define PIN_V5_GPIO_PIN 14u
#endif

/* Ball: H2 */
#define PIN_CTRL_REG_ADDR_H2 0x481408ACUL
#ifndef PIN_FUNCTION_H2_DIO
#define PIN_FUNCTION_H2_DIO 0x80UL
#endif
#ifndef PIN_H2_GPIO
#define PIN_H2_GPIO 0u
#define PIN_H2_GPIO_PIN 15u
#endif

/* Ball: G6 */
#define PIN_CTRL_REG_ADDR_G6 0x481408B0UL
#ifndef PIN_FUNCTION_G6_DIO
#define PIN_FUNCTION_G6_DIO 0x80UL
#endif
#ifndef PIN_G6_GPIO
#define PIN_G6_GPIO 0u
#define PIN_G6_GPIO_PIN 16u
#endif

/* Ball: H4 */
#define PIN_CTRL_REG_ADDR_H4 0x481408B4UL
#ifndef PIN_FUNCTION_H4_DIO
#define PIN_FUNCTION_H4_DIO 0x80UL
#endif
#ifndef PIN_H4_GPIO
#define PIN_H4_GPIO 0u
#define PIN_H4_GPIO_PIN 17u
#endif

/* Ball: G1 */
#define PIN_CTRL_REG_ADDR_G1 0x481408B8UL
#ifndef PIN_FUNCTION_G1_DIO
#define PIN_FUNCTION_G1_DIO 0x80UL
#endif
#ifndef PIN_FUNCTION_G1_PWM
#define PIN_FUNCTION_G1_PWM 0x40UL
#endif
#ifndef PIN_G1_GPIO
#define PIN_G1_GPIO 0u
#define PIN_G1_GPIO_PIN 18u
#endif

/* Ball: G2 */
#define PIN_CTRL_REG_ADDR_G2 0x481408BCUL
#ifndef PIN_FUNCTION_G2_DIO
#define PIN_FUNCTION_G2_DIO 0x80UL
#endif
#ifndef PIN_G2_GPIO
#define PIN_G2_GPIO 0u
#define PIN_G2_GPIO_PIN 19u
#endif

/* Ball: F2 */
#define PIN_CTRL_REG_ADDR_F2 0x481408C0UL
#ifndef PIN_FUNCTION_F2_DIO
#define PIN_FUNCTION_F2_DIO 0x80UL
#endif
#ifndef PIN_F2_GPIO
#define PIN_F2_GPIO 0u
#define PIN_F2_GPIO_PIN 20u
#endif

/* Ball: J6 */
#define PIN_CTRL_REG_ADDR_J6 0x481408C4UL

/* Ball: K7 */
#define PIN_CTRL_REG_ADDR_K7 0x481408C8UL
#ifndef PIN_FUNCTION_K7_DIO
#define PIN_FUNCTION_K7_DIO 0x80UL
#endif
#ifndef PIN_K7_GPIO
#define PIN_K7_GPIO 0u
#define PIN_K7_GPIO_PIN 21u
#endif

/* Ball: H3 */
#define PIN_CTRL_REG_ADDR_H3 0x481408CCUL
#ifndef PIN_FUNCTION_H3_DIO
#define PIN_FUNCTION_H3_DIO 0x80UL
#endif
#ifndef PIN_H3_GPIO
#define PIN_H3_GPIO 0u
#define PIN_H3_GPIO_PIN 22u
#endif

/* Ball: H6 */
#define PIN_CTRL_REG_ADDR_H6 0x481408D0UL
#ifndef PIN_FUNCTION_H6_DIO
#define PIN_FUNCTION_H6_DIO 0x80UL
#endif
#ifndef PIN_H6_GPIO
#define PIN_H6_GPIO 0u
#define PIN_H6_GPIO_PIN 23u
#endif

/* Ball: J4 */
#define PIN_CTRL_REG_ADDR_J4 0x481408D4UL
#ifndef PIN_FUNCTION_J4_DIO
#define PIN_FUNCTION_J4_DIO 0x80UL
#endif
#ifndef PIN_J4_GPIO
#define PIN_J4_GPIO 0u
#define PIN_J4_GPIO_PIN 24u
#endif

/* Ball: J3 */
#define PIN_CTRL_REG_ADDR_J3 0x481408D8UL
#ifndef PIN_FUNCTION_J3_DIO
#define PIN_FUNCTION_J3_DIO 0x80UL
#endif
#ifndef PIN_J3_GPIO
#define PIN_J3_GPIO 0u
#define PIN_J3_GPIO_PIN 25u
#endif

/* Ball: H5 */
#define PIN_CTRL_REG_ADDR_H5 0x481408DCUL
#ifndef PIN_FUNCTION_H5_DIO
#define PIN_FUNCTION_H5_DIO 0x80UL
#endif
#ifndef PIN_H5_GPIO
#define PIN_H5_GPIO 0u
#define PIN_H5_GPIO_PIN 26u
#endif

/* Ball: L7 */
#define PIN_CTRL_REG_ADDR_L7 0x481408E0UL
#ifndef PIN_FUNCTION_L7_DIO
#define PIN_FUNCTION_L7_DIO 0x80UL
#endif
#ifndef PIN_L7_GPIO
#define PIN_L7_GPIO 0u
#define PIN_L7_GPIO_PIN 27u
#endif

/* Ball: L6 */
#define PIN_CTRL_REG_ADDR_L6 0x481408E4UL
#ifndef PIN_FUNCTION_L6_DIO
#define PIN_FUNCTION_L6_DIO 0x80UL
#endif
#ifndef PIN_L6_GPIO
#define PIN_L6_GPIO 0u
#define PIN_L6_GPIO_PIN 28u
#endif

/* Ball: U4 */
#define PIN_CTRL_REG_ADDR_U4 0x481408E8UL
#ifndef PIN_FUNCTION_U4_DIO
#define PIN_FUNCTION_U4_DIO 0x80UL
#endif
#ifndef PIN_U4_GPIO
#define PIN_U4_GPIO 0u
#define PIN_U4_GPIO_PIN 29u
#endif

/* Ball: T2 */
#define PIN_CTRL_REG_ADDR_T2 0x481408ECUL
#ifndef PIN_FUNCTION_T2_DIO
#define PIN_FUNCTION_T2_DIO 0x80UL
#endif
#ifndef PIN_T2_GPIO
#define PIN_T2_GPIO 0u
#define PIN_T2_GPIO_PIN 30u
#endif

/* Ball: U3 */
#define PIN_CTRL_REG_ADDR_U3 0x481408F0UL
#ifndef PIN_FUNCTION_U3_DIO
#define PIN_FUNCTION_U3_DIO 0x80UL
#endif
#ifndef PIN_U3_GPIO
#define PIN_U3_GPIO 0u
#define PIN_U3_GPIO_PIN 31u
#endif

/* Ball: W1 */
#define PIN_CTRL_REG_ADDR_W1 0x481408F4UL
#ifndef PIN_FUNCTION_W1_DIO
#define PIN_FUNCTION_W1_DIO 0x80UL
#endif
#ifndef PIN_W1_GPIO
#define PIN_W1_GPIO 1u
#define PIN_W1_GPIO_PIN 7u
#endif

/* Ball: W2 */
#define PIN_CTRL_REG_ADDR_W2 0x481408F8UL
#ifndef PIN_FUNCTION_W2_DIO
#define PIN_FUNCTION_W2_DIO 0x80UL
#endif
#ifndef PIN_W2_GPIO
#define PIN_W2_GPIO 1u
#define PIN_W2_GPIO_PIN 8u
#endif

/* Ball: V1 */
#define PIN_CTRL_REG_ADDR_V1 0x481408FCUL
#ifndef PIN_FUNCTION_V1_DIO
#define PIN_FUNCTION_V1_DIO 0x80UL
#endif
#ifndef PIN_V1_GPIO
#define PIN_V1_GPIO 1u
#define PIN_V1_GPIO_PIN 9u
#endif

/* Ball: V2 */
#define PIN_CTRL_REG_ADDR_V2 0x48140900UL
#ifndef PIN_FUNCTION_V2_DIO
#define PIN_FUNCTION_V2_DIO 0x80UL
#endif
#ifndef PIN_V2_GPIO
#define PIN_V2_GPIO 1u
#define PIN_V2_GPIO_PIN 10u
#endif

/* Ball: U1 */
#define PIN_CTRL_REG_ADDR_U1 0x48140904UL

/* Ball: U2 */
#define PIN_CTRL_REG_ADDR_U2 0x48140908UL

/* Ball: AH6 */
#define PIN_CTRL_REG_ADDR_AH6 0x4814090CUL
#ifndef PIN_FUNCTION_AH6_CAN
#define PIN_FUNCTION_AH6_CAN 0x1UL
#endif
#ifndef PIN_FUNCTION_AH6_DIO
#define PIN_FUNCTION_AH6_DIO 0x80UL
#endif
#ifndef PIN_AH6_GPIO
#define PIN_AH6_GPIO 1u
#define PIN_AH6_GPIO_PIN 0u
#endif

/* Ball: AG6 */
#define PIN_CTRL_REG_ADDR_AG6 0x48140910UL
#ifndef PIN_FUNCTION_AG6_CAN
#define PIN_FUNCTION_AG6_CAN 0x1UL
#endif
#ifndef PIN_FUNCTION_AG6_DIO
#define PIN_FUNCTION_AG6_DIO 0x80UL
#endif
#ifndef PIN_AG6_GPIO
#define PIN_AG6_GPIO 1u
#define PIN_AG6_GPIO_PIN 1u
#endif

/* Ball: AH5 */
#define PIN_CTRL_REG_ADDR_AH5 0x48140914UL

/* Ball: AG5 */
#define PIN_CTRL_REG_ADDR_AG5 0x48140918UL

/* Ball: AE6 */
#define PIN_CTRL_REG_ADDR_AE6 0x4814091CUL
#ifndef PIN_FUNCTION_AE6_CAN
#define PIN_FUNCTION_AE6_CAN 0x8UL
#endif

/* Ball: AF5 */
#define PIN_CTRL_REG_ADDR_AF5 0x48140920UL
#ifndef PIN_FUNCTION_AF5_CAN
#define PIN_FUNCTION_AF5_CAN 0x8UL
#endif

/* Ball: AH4 */
#define PIN_CTRL_REG_ADDR_AH4 0x48140924UL
#ifndef PIN_FUNCTION_AH4_DIO
#define PIN_FUNCTION_AH4_DIO 0x80UL
#endif
#ifndef PIN_AH4_GPIO
#define PIN_AH4_GPIO 1u
#define PIN_AH4_GPIO_PIN 2u
#endif

/* Ball: AG4 */
#define PIN_CTRL_REG_ADDR_AG4 0x48140928UL
#ifndef PIN_FUNCTION_AG4_DIO
#define PIN_FUNCTION_AG4_DIO 0x80UL
#endif
#ifndef PIN_AG4_GPIO
#define PIN_AG4_GPIO 1u
#define PIN_AG4_GPIO_PIN 3u
#endif

/* Ball: AG2 */
#define PIN_CTRL_REG_ADDR_AG2 0x4814092CUL
#ifndef PIN_FUNCTION_AG2_DIO
#define PIN_FUNCTION_AG2_DIO 0x80UL
#endif
#ifndef PIN_AG2_GPIO
#define PIN_AG2_GPIO 1u
#define PIN_AG2_GPIO_PIN 4u
#endif

/* Ball: AF4 */
#define PIN_CTRL_REG_ADDR_AF4 0x48140930UL
#ifndef PIN_FUNCTION_AF4_DIO
#define PIN_FUNCTION_AF4_DIO 0x80UL
#endif
#ifndef PIN_AF4_GPIO
#define PIN_AF4_GPIO 1u
#define PIN_AF4_GPIO_PIN 5u
#endif

/* Ball: AF24 */
#define PIN_CTRL_REG_ADDR_AF24 0x48140934UL

/* Ball: AG24 */
#define PIN_CTRL_REG_ADDR_AG24 0x48140938UL

/* Ball: AE5 */
#define PIN_CTRL_REG_ADDR_AE5 0x4814093CUL
#ifndef PIN_FUNCTION_AE5_DIO
#define PIN_FUNCTION_AE5_DIO 0x80UL
#endif
#ifndef PIN_AE5_GPIO
#define PIN_AE5_GPIO 1u
#define PIN_AE5_GPIO_PIN 6u
#endif


/* Ball: AD6 */
#define PIN_CTRL_REG_ADDR_AD6 0x48140940UL

/* Ball: AC7 */
#define PIN_CTRL_REG_ADDR_AC7 0x48140944UL

/* Ball: AF3 */
#define PIN_CTRL_REG_ADDR_AF3 0x48140948UL

/* Ball: AE3 */
#define PIN_CTRL_REG_ADDR_AE3 0x4814094CUL

/* Ball: AD3 */
#define PIN_CTRL_REG_ADDR_AD3 0x48140950UL
#ifndef PIN_FUNCTION_AD3_DIO
#define PIN_FUNCTION_AD3_DIO 0x80UL
#endif
#ifndef PIN_AD3_GPIO
#define PIN_AD3_GPIO 1u
#define PIN_AD3_GPIO_PIN 16u
#endif

/* Ball: AC3 */
#define PIN_CTRL_REG_ADDR_AC3 0x48140954UL
#ifndef PIN_FUNCTION_AC3_DIO
#define PIN_FUNCTION_AC3_DIO 0x80UL
#endif
#ifndef PIN_AC3_GPIO
#define PIN_AC3_GPIO 1u
#define PIN_AC3_GPIO_PIN 17u
#endif

/* Ball: AA3 */
#define PIN_CTRL_REG_ADDR_AA3 0x48140958UL
#ifndef PIN_FUNCTION_AA3_DIO
#define PIN_FUNCTION_AA3_DIO 0x80UL
#endif
#ifndef PIN_AA3_GPIO
#define PIN_AA3_GPIO 1u
#define PIN_AA3_GPIO_PIN 18u
#endif

/* Ball: AA6 */
#define PIN_CTRL_REG_ADDR_AA6 0x4814095CUL
#ifndef PIN_FUNCTION_AA6_DIO
#define PIN_FUNCTION_AA6_DIO 0x80UL
#endif
#ifndef PIN_AA6_GPIO
#define PIN_AA6_GPIO 1u
#define PIN_AA6_GPIO_PIN 26u
#endif

/* Ball: U26 */
#define PIN_CTRL_REG_ADDR_U26 0x48140960UL

/* Ball: Y28 */
#define PIN_CTRL_REG_ADDR_Y28 0x48140964UL

/* Ball: V27 */
#define PIN_CTRL_REG_ADDR_V27 0x48140968UL

/* Ball: W27 */
#define PIN_CTRL_REG_ADDR_W27 0x4814096CUL

/* Ball: V26 */
#define PIN_CTRL_REG_ADDR_V26 0x48140970UL

/* Ball: AA28 */
#define PIN_CTRL_REG_ADDR_AA28 0x48140974UL

/* Ball: U25 */
#define PIN_CTRL_REG_ADDR_U25 0x48140978UL

/* Ball: V25 */
#define PIN_CTRL_REG_ADDR_V25 0x4814097CUL

/* Ball: Y27 */
#define PIN_CTRL_REG_ADDR_Y27 0x48140980UL

/* Ball: AB28 */
#define PIN_CTRL_REG_ADDR_AB28 0x48140984UL

/* Ball: Y26 */
#define PIN_CTRL_REG_ADDR_Y26 0x48140988UL

/* Ball: AA27 */
#define PIN_CTRL_REG_ADDR_AA27 0x4814098CUL

/* Ball: U24 */
#define PIN_CTRL_REG_ADDR_U24 0x48140990UL

/* Ball: U23 */
#define PIN_CTRL_REG_ADDR_U23 0x48140994UL

/* Ball: V24 */
#define PIN_CTRL_REG_ADDR_V24 0x48140998UL

/* Ball: Y25 */
#define PIN_CTRL_REG_ADDR_Y25 0x4814099CUL

/* Ball: AD27 */
#define PIN_CTRL_REG_ADDR_AD27 0x481409A0UL
#ifndef PIN_FUNCTION_AD27_DIO
#define PIN_FUNCTION_AD27_DIO 0x80UL
#endif
#ifndef PIN_AD27_GPIO
#define PIN_AD27_GPIO 2u
#define PIN_AD27_GPIO_PIN 5u
#endif

/* Ball: V23 */
#define PIN_CTRL_REG_ADDR_V23 0x481409A4UL
#ifndef PIN_FUNCTION_V23_DIO
#define PIN_FUNCTION_V23_DIO 0x80UL
#endif
#ifndef PIN_V23_GPIO
#define PIN_V23_GPIO 2u
#define PIN_V23_GPIO_PIN 6u
#endif

/* Ball: AE28 */
#define PIN_CTRL_REG_ADDR_AE28 0x481409A8UL
#ifndef PIN_FUNCTION_AE28_DIO
#define PIN_FUNCTION_AE28_DIO 0x80UL
#endif
#ifndef PIN_AE28_GPIO
#define PIN_AE28_GPIO 1u
#define PIN_AE28_GPIO_PIN 13u
#endif

/* Ball: AC27 */
#define PIN_CTRL_REG_ADDR_AC27 0x481409ACUL
#ifndef PIN_FUNCTION_AC27_DIO
#define PIN_FUNCTION_AC27_DIO 0x80UL
#endif
#ifndef PIN_AC27_GPIO
#define PIN_AC27_GPIO 1u
#define PIN_AC27_GPIO_PIN 14u
#endif

/* Ball: AD28 */
#define PIN_CTRL_REG_ADDR_AD28 0x481409B0UL
#ifndef PIN_FUNCTION_AD28_DIO
#define PIN_FUNCTION_AD28_DIO 0x80UL
#endif
#ifndef PIN_AD28_GPIO
#define PIN_AD28_GPIO 1u
#define PIN_AD28_GPIO_PIN 15u
#endif

/* Ball: AC28 */
#define PIN_CTRL_REG_ADDR_AC28 0x481409B4UL
#ifndef PIN_FUNCTION_AC28_DIO
#define PIN_FUNCTION_AC28_DIO 0x80UL
#endif
#ifndef PIN_AC28_GPIO
#define PIN_AC28_GPIO 1u
#define PIN_AC28_GPIO_PIN 16u
#endif

/* Ball: AB27 */
#define PIN_CTRL_REG_ADDR_AB27 0x481409B8UL
#ifndef PIN_FUNCTION_AB27_DIO
#define PIN_FUNCTION_AB27_DIO 0x80UL
#endif
#ifndef PIN_AB27_GPIO
#define PIN_AB27_GPIO 1u
#define PIN_AB27_GPIO_PIN 17u
#endif

/* Ball: AA26 */
#define PIN_CTRL_REG_ADDR_AA26 0x481409BCUL
#ifndef PIN_FUNCTION_AA26_DIO
#define PIN_FUNCTION_AA26_DIO 0x80UL
#endif
#ifndef PIN_AA26_GPIO
#define PIN_AA26_GPIO 1u
#define PIN_AA26_GPIO_PIN 18u
#endif

/* Ball: L25 */
#define PIN_CTRL_REG_ADDR_L25 0x481409C0UL
#ifndef PIN_FUNCTION_L25_DIO
#define PIN_FUNCTION_L25_DIO 0x80UL
#endif
#ifndef PIN_L25_GPIO
#define PIN_L25_GPIO 1u
#define PIN_L25_GPIO_PIN 19u
#endif

/* Ball: N23 */
#define PIN_CTRL_REG_ADDR_N23 0x481409C4UL
#ifndef PIN_FUNCTION_N23_DIO
#define PIN_FUNCTION_N23_DIO 0x80UL
#endif
#ifndef PIN_N23_GPIO
#define PIN_N23_GPIO 1u
#define PIN_N23_GPIO_PIN 20u
#endif

/* Ball: P22 */
#define PIN_CTRL_REG_ADDR_P22 0x481409C8UL
#ifndef PIN_FUNCTION_P22_DIO
#define PIN_FUNCTION_P22_DIO 0x80UL
#endif
#ifndef PIN_P22_GPIO
#define PIN_P22_GPIO 1u
#define PIN_P22_GPIO_PIN 21u
#endif

/* Ball: R24 */
#define PIN_CTRL_REG_ADDR_R24 0x481409CCUL
#ifndef PIN_FUNCTION_R24_DIO
#define PIN_FUNCTION_R24_DIO 0x80UL
#endif
#ifndef PIN_R24_GPIO
#define PIN_R24_GPIO 1u
#define PIN_R24_GPIO_PIN 22u
#endif

/* Ball: J28 */
#define PIN_CTRL_REG_ADDR_J28 0x481409D0UL
#ifndef PIN_FUNCTION_J28_DIO
#define PIN_FUNCTION_J28_DIO 0x80UL
#endif
#ifndef PIN_J28_GPIO
#define PIN_J28_GPIO 2u
#define PIN_J28_GPIO_PIN 5u
#endif

/* Ball: K27 */
#define PIN_CTRL_REG_ADDR_K27 0x481409D4UL
#ifndef PIN_FUNCTION_K27_DIO
#define PIN_FUNCTION_K27_DIO 0x80UL
#endif
#ifndef PIN_K27_GPIO
#define PIN_K27_GPIO 2u
#define PIN_K27_GPIO_PIN 6u
#endif

/* Ball: M24 */
#define PIN_CTRL_REG_ADDR_M24 0x481409D8UL
#ifndef PIN_FUNCTION_M24_DIO
#define PIN_FUNCTION_M24_DIO 0x80UL
#endif
#ifndef PIN_M24_GPIO
#define PIN_M24_GPIO 1u
#define PIN_M24_GPIO_PIN 13u
#endif

/* Ball: L26 */
#define PIN_CTRL_REG_ADDR_L26 0x481409DCUL
#ifndef PIN_FUNCTION_L26_DIO
#define PIN_FUNCTION_L26_DIO 0x80UL
#endif
#ifndef PIN_L26_GPIO
#define PIN_L26_GPIO 1u
#define PIN_L26_GPIO_PIN 14u
#endif

/* Ball: M23 */
#define PIN_CTRL_REG_ADDR_M23 0x481409E0UL
#ifndef PIN_FUNCTION_M23_DIO
#define PIN_FUNCTION_M23_DIO 0x80UL
#endif
#ifndef PIN_M23_GPIO
#define PIN_M23_GPIO 1u
#define PIN_M23_GPIO_PIN 15u
#endif

/* Ball: T28 */
#define PIN_CTRL_REG_ADDR_T28 0x481409E4UL
#ifndef PIN_FUNCTION_T28_DIO
#define PIN_FUNCTION_T28_DIO 0x80UL
#endif
#ifndef PIN_T28_GPIO
#define PIN_T28_GPIO 1u
#define PIN_T28_GPIO_PIN 23u
#endif

/* Ball: K28 */
#define PIN_CTRL_REG_ADDR_K28 0x481409E8UL
#ifndef PIN_FUNCTION_K28_DIO
#define PIN_FUNCTION_K28_DIO 0x80UL
#endif
#ifndef PIN_K28_GPIO
#define PIN_K28_GPIO 1u
#define PIN_K28_GPIO_PIN 24u
#endif

/* Ball: M25 */
#define PIN_CTRL_REG_ADDR_M25 0x481409ECUL
#ifndef PIN_FUNCTION_M25_DIO
#define PIN_FUNCTION_M25_DIO 0x80UL
#endif
#ifndef PIN_M25_GPIO
#define PIN_M25_GPIO 1u
#define PIN_M25_GPIO_PIN 25u
#endif

/* Ball: P26 */
#define PIN_CTRL_REG_ADDR_P26 0x481409F0UL
#ifndef PIN_FUNCTION_P26_DIO
#define PIN_FUNCTION_P26_DIO 0x80UL
#endif
#ifndef PIN_P26_GPIO
#define PIN_P26_GPIO 1u
#define PIN_P26_GPIO_PIN 26u
#endif

/* Ball: P25 */
#define PIN_CTRL_REG_ADDR_P25 0x481409F4UL
#ifndef PIN_FUNCTION_P25_DIO
#define PIN_FUNCTION_P25_DIO 0x80UL
#endif
#ifndef PIN_P25_GPIO
#define PIN_P25_GPIO 1u
#define PIN_P25_GPIO_PIN 8u
#endif

/* Ball: R26 */
#define PIN_CTRL_REG_ADDR_R26 0x481409F8UL
#ifndef PIN_FUNCTION_R26_DIO
#define PIN_FUNCTION_R26_DIO 0x80UL
#endif
#ifndef PIN_R26_GPIO
#define PIN_R26_GPIO 1u
#define PIN_R26_GPIO_PIN 27u
#endif

/* Ball: M26 */
#define PIN_CTRL_REG_ADDR_M26 0x481409FCUL
#ifndef PIN_FUNCTION_M26_DIO
#define PIN_FUNCTION_M26_DIO 0x80UL
#endif
#ifndef PIN_M26_GPIO
#define PIN_M26_GPIO 1u
#define PIN_M26_GPIO_PIN 28u
#endif

/* Ball: T27 */
#define PIN_CTRL_REG_ADDR_T27 0x48140A00UL

/* Ball: U28 */
#define PIN_CTRL_REG_ADDR_U28 0x48140A04UL

/* Ball: U27 */
#define PIN_CTRL_REG_ADDR_U27 0x48140A08UL
#ifndef PIN_FUNCTION_U27_DIO
#define PIN_FUNCTION_U27_DIO 0x80UL
#endif
#ifndef PIN_U27_GPIO
#define PIN_U27_GPIO 1u
#define PIN_U27_GPIO_PIN 29u
#endif

/* Ball: V28 */
#define PIN_CTRL_REG_ADDR_V28 0x48140A0CUL
#ifndef PIN_FUNCTION_V28_DIO
#define PIN_FUNCTION_V28_DIO 0x80UL
#endif
#ifndef PIN_V28_GPIO
#define PIN_V28_GPIO 1u
#define PIN_V28_GPIO_PIN 30u
#endif

/* Ball: W28 */
#define PIN_CTRL_REG_ADDR_W28 0x48140A10UL
#ifndef PIN_FUNCTION_W28_DIO
#define PIN_FUNCTION_W28_DIO 0x80UL
#endif
#ifndef PIN_W28_GPIO
#define PIN_W28_GPIO 1u
#define PIN_W28_GPIO_PIN 31u
#endif

/* Ball: AE17 */
#define PIN_CTRL_REG_ADDR_AE17 0x48140A14UL
#ifndef PIN_FUNCTION_AE17_DIO
#define PIN_FUNCTION_AE17_DIO 0x80UL
#endif
#ifndef PIN_AE17_GPIO
#define PIN_AE17_GPIO 1u
#define PIN_AE17_GPIO_PIN 9u
#endif

/* Ball: AE21 */
#define PIN_CTRL_REG_ADDR_AE21 0x48140A18UL
#ifndef PIN_FUNCTION_AE21_DIO
#define PIN_FUNCTION_AE21_DIO 0x80UL
#endif
#ifndef PIN_AE21_GPIO
#define PIN_AE21_GPIO 2u
#define PIN_AE21_GPIO_PIN 0u
#endif

/* Ball: AA20 */
#define PIN_CTRL_REG_ADDR_AA20 0x48140A1CUL
#ifndef PIN_FUNCTION_AA20_DIO
#define PIN_FUNCTION_AA20_DIO 0x80UL
#endif
#ifndef PIN_AA20_GPIO
#define PIN_AA20_GPIO 2u
#define PIN_AA20_GPIO_PIN 1u
#endif

/* Ball: AB20 */
#define PIN_CTRL_REG_ADDR_AB20 0x48140A20UL
#ifndef PIN_FUNCTION_AB20_DIO
#define PIN_FUNCTION_AB20_DIO 0x80UL
#endif
#ifndef PIN_AB20_GPIO
#define PIN_AB20_GPIO 2u
#define PIN_AB20_GPIO_PIN 2u
#endif

/* Ball: AC20 */
#define PIN_CTRL_REG_ADDR_AC20 0x48140A24UL
#ifndef PIN_FUNCTION_AC20_DIO
#define PIN_FUNCTION_AC20_DIO 0x80UL
#endif
#ifndef PIN_AC20_GPIO
#define PIN_AC20_GPIO 2u
#define PIN_AC20_GPIO_PIN 3u
#endif

/* Ball: AD20 */
#define PIN_CTRL_REG_ADDR_AD20 0x48140A28UL
#ifndef PIN_FUNCTION_AD20_DIO
#define PIN_FUNCTION_AD20_DIO 0x80UL
#endif
#ifndef PIN_AD20_GPIO
#define PIN_AD20_GPIO 2u
#define PIN_AD20_GPIO_PIN 4u
#endif

/* Ball: AF9 */
#define PIN_CTRL_REG_ADDR_AF9 0x48140A2CUL
#ifndef PIN_FUNCTION_AF9_DIO
#define PIN_FUNCTION_AF9_DIO 0x80UL
#endif
#ifndef PIN_AF9_GPIO
#define PIN_AF9_GPIO 1u
#define PIN_AF9_GPIO_PIN 11u
#endif

/* Ball: AB11 */
#define PIN_CTRL_REG_ADDR_AB11 0x48140A30UL
#ifndef PIN_FUNCTION_AB11_DIO
#define PIN_FUNCTION_AB11_DIO 0x80UL
#endif
#ifndef PIN_AB11_GPIO
#define PIN_AB11_GPIO 1u
#define PIN_AB11_GPIO_PIN 12u
#endif

/* Ball: AC9 */
#define PIN_CTRL_REG_ADDR_AC9 0x48140A34UL
#ifndef PIN_FUNCTION_AC9_DIO
#define PIN_FUNCTION_AC9_DIO 0x80UL
#endif
#ifndef PIN_AC9_GPIO
#define PIN_AC9_GPIO 2u
#define PIN_AC9_GPIO_PIN 7u
#endif

/* Ball: AE12 */
#define PIN_CTRL_REG_ADDR_AE12 0x48140A38UL
#ifndef PIN_FUNCTION_AE12_DIO
#define PIN_FUNCTION_AE12_DIO 0x80UL
#endif
#ifndef PIN_AE12_GPIO
#define PIN_AE12_GPIO 2u
#define PIN_AE12_GPIO_PIN 8u
#endif

/* Ball: AH8 */
#define PIN_CTRL_REG_ADDR_AH8 0x48140A3CUL
#ifndef PIN_FUNCTION_AH8_DIO
#define PIN_FUNCTION_AH8_DIO 0x80UL
#endif
#ifndef PIN_AH8_GPIO
#define PIN_AH8_GPIO 2u
#define PIN_AH8_GPIO_PIN 9u
#endif

/* Ball: AG16 */
#define PIN_CTRL_REG_ADDR_AG16 0x48140A40UL
#ifndef PIN_FUNCTION_AG16_DIO
#define PIN_FUNCTION_AG16_DIO 0x80UL
#endif
#ifndef PIN_AG16_GPIO
#define PIN_AG16_GPIO 2u
#define PIN_AG16_GPIO_PIN 10u
#endif

/* Ball: AH16 */
#define PIN_CTRL_REG_ADDR_AH16 0x48140A44UL
#ifndef PIN_FUNCTION_AH16_DIO
#define PIN_FUNCTION_AH16_DIO 0x80UL
#endif
#ifndef PIN_AH16_GPIO
#define PIN_AH16_GPIO 2u
#define PIN_AH16_GPIO_PIN 11u
#endif

/* Ball: AA11 */
#define PIN_CTRL_REG_ADDR_AA11 0x48140A48UL
#ifndef PIN_FUNCTION_AA11_DIO
#define PIN_FUNCTION_AA11_DIO 0x80UL
#endif
#ifndef PIN_AA11_GPIO
#define PIN_AA11_GPIO 2u
#define PIN_AA11_GPIO_PIN 12u
#endif

/* Ball: AB15 */
#define PIN_CTRL_REG_ADDR_AB15 0x48140A4CUL
#ifndef PIN_FUNCTION_AB15_DIO
#define PIN_FUNCTION_AB15_DIO 0x80UL
#endif
#ifndef PIN_AB15_GPIO
#define PIN_AB15_GPIO 2u
#define PIN_AB15_GPIO_PIN 13u
#endif

/* Ball: AG9 */
#define PIN_CTRL_REG_ADDR_AG9 0x48140A50UL
#ifndef PIN_FUNCTION_AG9_DIO
#define PIN_FUNCTION_AG9_DIO 0x80UL
#endif
#ifndef PIN_AG9_GPIO
#define PIN_AG9_GPIO 2u
#define PIN_AG9_GPIO_PIN 14u
#endif

/* Ball: AH9 */
#define PIN_CTRL_REG_ADDR_AH9 0x48140A54UL
#ifndef PIN_FUNCTION_AH9_DIO
#define PIN_FUNCTION_AH9_DIO 0x80UL
#endif
#ifndef PIN_AH9_GPIO
#define PIN_AH9_GPIO 2u
#define PIN_AH9_GPIO_PIN 15u
#endif

/* Ball: AH17 */
#define PIN_CTRL_REG_ADDR_AH17 0x48140A58UL
#ifndef PIN_FUNCTION_AH17_DIO
#define PIN_FUNCTION_AH17_DIO 0x80UL
#endif
#ifndef PIN_AH17_GPIO
#define PIN_AH17_GPIO 2u
#define PIN_AH17_GPIO_PIN 16u
#endif

/* Ball: AG17 */
#define PIN_CTRL_REG_ADDR_AG17 0x48140A5CUL
#ifndef PIN_FUNCTION_AG17_DIO
#define PIN_FUNCTION_AG17_DIO 0x80UL
#endif
#ifndef PIN_AG17_GPIO
#define PIN_AG17_GPIO 2u
#define PIN_AG17_GPIO_PIN 17u
#endif

/* Ball: AF17 */
#define PIN_CTRL_REG_ADDR_AF17 0x48140A60UL
#ifndef PIN_FUNCTION_AF17_DIO
#define PIN_FUNCTION_AF17_DIO 0x80UL
#endif
#ifndef PIN_AF17_GPIO
#define PIN_AF17_GPIO 2u
#define PIN_AF17_GPIO_PIN 18u
#endif

/* Ball: AC12 */
#define PIN_CTRL_REG_ADDR_AC12 0x48140A64UL
#ifndef PIN_FUNCTION_AC12_DIO
#define PIN_FUNCTION_AC12_DIO 0x80UL
#endif
#ifndef PIN_AC12_GPIO
#define PIN_AC12_GPIO 2u
#define PIN_AC12_GPIO_PIN 19u
#endif

/* Ball: AC14 */
#define PIN_CTRL_REG_ADDR_AC14 0x48140A68UL
#ifndef PIN_FUNCTION_AC14_DIO
#define PIN_FUNCTION_AC14_DIO 0x80UL
#endif
#ifndef PIN_AC14_GPIO
#define PIN_AC14_GPIO 2u
#define PIN_AC14_GPIO_PIN 20u
#endif

/* Ball: AA21 */
#define PIN_CTRL_REG_ADDR_AA21 0x48140A6CUL
#ifndef PIN_FUNCTION_AA21_DIO
#define PIN_FUNCTION_AA21_DIO 0x80UL
#endif
#ifndef PIN_AA21_GPIO
#define PIN_AA21_GPIO 0u
#define PIN_AA21_GPIO_PIN 10u
#endif

/* Ball: AB21 */
#define PIN_CTRL_REG_ADDR_AB21 0x48140A70UL
#ifndef PIN_FUNCTION_AB21_DIO
#define PIN_FUNCTION_AB21_DIO 0x80UL
#endif
#ifndef PIN_AB21_GPIO
#define PIN_AB21_GPIO 0u
#define PIN_AB21_GPIO_PIN 11u
#endif

/* Ball: AF20 */
#define PIN_CTRL_REG_ADDR_AF20 0x48140A74UL

/* Ball: AF21 */
#define PIN_CTRL_REG_ADDR_AF21 0x48140A78UL

/* Ball: AC17 */
#define PIN_CTRL_REG_ADDR_AC17 0x48140A7CUL

/* Ball: AE18 */
#define PIN_CTRL_REG_ADDR_AE18 0x48140A80UL

/* Ball: AC21 */
#define PIN_CTRL_REG_ADDR_AC21 0x48140A84UL

/* Ball: AC16 */
#define PIN_CTRL_REG_ADDR_AC16 0x48140A88UL

/* Ball: AB17 */
#define PIN_CTRL_REG_ADDR_AB17 0x48140A8CUL
#ifndef PIN_FUNCTION_AB17_DIO
#define PIN_FUNCTION_AB17_DIO 0x80UL
#endif
#ifndef PIN_AB17_GPIO
#define PIN_AB17_GPIO 0u
#define PIN_AB17_GPIO_PIN 18u
#endif

/* Ball: AC15 */
#define PIN_CTRL_REG_ADDR_AC15 0x48140A90UL
#ifndef PIN_FUNCTION_AC15_DIO
#define PIN_FUNCTION_AC15_DIO 0x80UL
#endif
#ifndef PIN_AC15_GPIO
#define PIN_AC15_GPIO 0u
#define PIN_AC15_GPIO_PIN 19u
#endif

/* Ball: AC22 */
#define PIN_CTRL_REG_ADDR_AC22 0x48140A94UL
#ifndef PIN_FUNCTION_AC22_DIO
#define PIN_FUNCTION_AC22_DIO 0x80UL
#endif
#ifndef PIN_AC22_GPIO
#define PIN_AC22_GPIO 0u
#define PIN_AC22_GPIO_PIN 20u
#endif

/* Ball: AD17 */
#define PIN_CTRL_REG_ADDR_AD17 0x48140A98UL
#ifndef PIN_FUNCTION_AD17_DIO
#define PIN_FUNCTION_AD17_DIO 0x80UL
#endif
#ifndef PIN_AD17_GPIO
#define PIN_AD17_GPIO 0u
#define PIN_AD17_GPIO_PIN 21u
#endif

/* Ball: AD18 */
#define PIN_CTRL_REG_ADDR_AD18 0x48140A9CUL
#ifndef PIN_FUNCTION_AD18_DIO
#define PIN_FUNCTION_AD18_DIO 0x80UL
#endif
#ifndef PIN_AD18_GPIO
#define PIN_AD18_GPIO 0u
#define PIN_AD18_GPIO_PIN 22u
#endif

/* Ball: AC18 */
#define PIN_CTRL_REG_ADDR_AC18 0x48140AA0UL
#ifndef PIN_FUNCTION_AC18_DIO
#define PIN_FUNCTION_AC18_DIO 0x80UL
#endif
#ifndef PIN_AC18_GPIO
#define PIN_AC18_GPIO 0u
#define PIN_AC18_GPIO_PIN 23u
#endif

/* Ball: AC19 */
#define PIN_CTRL_REG_ADDR_AC19 0x48140AA4UL
#ifndef PIN_FUNCTION_AC19_DIO
#define PIN_FUNCTION_AC19_DIO 0x80UL
#endif
#ifndef PIN_AC19_GPIO
#define PIN_AC19_GPIO 0u
#define PIN_AC19_GPIO_PIN 24u
#endif

/* Ball: AA22 */
#define PIN_CTRL_REG_ADDR_AA22 0x48140AA8UL
#ifndef PIN_FUNCTION_AA22_DIO
#define PIN_FUNCTION_AA22_DIO 0x80UL
#endif
#ifndef PIN_AA22_GPIO
#define PIN_AA22_GPIO 0u
#define PIN_AA22_GPIO_PIN 25u
#endif

/* Ball: AE23 */
#define PIN_CTRL_REG_ADDR_AE23 0x48140AACUL
#ifndef PIN_FUNCTION_AE23_DIO
#define PIN_FUNCTION_AE23_DIO 0x80UL
#endif
#ifndef PIN_AE23_GPIO
#define PIN_AE23_GPIO 0u
#define PIN_AE23_GPIO_PIN 26u
#endif

/* Ball: AD23 */
#define PIN_CTRL_REG_ADDR_AD23 0x48140AB0UL
#ifndef PIN_FUNCTION_AD23_DIO
#define PIN_FUNCTION_AD23_DIO 0x80UL
#endif
#ifndef PIN_AD23_GPIO
#define PIN_AD23_GPIO 0u
#define PIN_AD23_GPIO_PIN 27u
#endif

/* Ball: AB23 */
#define PIN_CTRL_REG_ADDR_AB23 0x48140AB4UL
#ifndef PIN_FUNCTION_AB23_DIO
#define PIN_FUNCTION_AB23_DIO 0x80UL
#endif
#ifndef PIN_AB23_GPIO
#define PIN_AB23_GPIO 0u
#define PIN_AB23_GPIO_PIN 28u
#endif

/* Ball: AF18 */
#define PIN_CTRL_REG_ADDR_AF18 0x48140AB8UL
#ifndef PIN_FUNCTION_AF18_DIO
#define PIN_FUNCTION_AF18_DIO 0x80UL
#endif
#ifndef PIN_AF18_GPIO
#define PIN_AF18_GPIO 2u
#define PIN_AF18_GPIO_PIN 2u
#endif

/* Ball: AD12 */
#define PIN_CTRL_REG_ADDR_AD12 0x48140ABCUL

/* Ball: AC11 */
#define PIN_CTRL_REG_ADDR_AC11 0x48140AC0UL

/* Ball: AB13 */
#define PIN_CTRL_REG_ADDR_AB13 0x48140AC4UL

/* Ball: AA10 */
#define PIN_CTRL_REG_ADDR_AA10 0x48140AC8UL
#ifndef PIN_FUNCTION_AA10_DIO
#define PIN_FUNCTION_AA10_DIO 0x80UL
#endif
#ifndef PIN_FUNCTION_AA10_PWM
#define PIN_FUNCTION_AA10_PWM 0x40UL
#endif
#ifndef PIN_AA10_GPIO
#define PIN_AA10_GPIO 2u
#define PIN_AA10_GPIO_PIN 21u
#endif

/* Ball: AG7 */
#define PIN_CTRL_REG_ADDR_AG7 0x48140ACCUL
#ifndef PIN_FUNCTION_AG7_DIO
#define PIN_FUNCTION_AG7_DIO 0x80UL
#endif
#ifndef PIN_AG7_GPIO
#define PIN_AG7_GPIO 2u
#define PIN_AG7_GPIO_PIN 22u
#endif

/* Ball: AE15 */
#define PIN_CTRL_REG_ADDR_AE15 0x48140AD0UL
#ifndef PIN_FUNCTION_AE15_DIO
#define PIN_FUNCTION_AE15_DIO 0x80UL
#endif
#ifndef PIN_AE15_GPIO
#define PIN_AE15_GPIO 2u
#define PIN_AE15_GPIO_PIN 23u
#endif

/* Ball: AD11 */
#define PIN_CTRL_REG_ADDR_AD11 0x48140AD4UL

/* Ball: AD15 */
#define PIN_CTRL_REG_ADDR_AD15 0x48140AD8UL

/* Ball: AC10 */
#define PIN_CTRL_REG_ADDR_AC10 0x48140ADCUL

/* Ball: AB10 */
#define PIN_CTRL_REG_ADDR_AB10 0x48140AE0UL

/* Ball: AF15 */
#define PIN_CTRL_REG_ADDR_AF15 0x48140AE4UL

/* Ball: AG15 */
#define PIN_CTRL_REG_ADDR_AG15 0x48140AE8UL

/* Ball: AH7 */
#define PIN_CTRL_REG_ADDR_AH7 0x48140AECUL
#ifndef PIN_FUNCTION_AH7_DIO
#define PIN_FUNCTION_AH7_DIO 0x80UL
#endif
#ifndef PIN_AH7_GPIO
#define PIN_AH7_GPIO 2u
#define PIN_AH7_GPIO_PIN 24u
#endif

/* Ball: AH15 */
#define PIN_CTRL_REG_ADDR_AH15 0x48140AF0UL
#ifndef PIN_FUNCTION_AH15_DIO
#define PIN_FUNCTION_AH15_DIO 0x80UL
#endif
#ifndef PIN_AH15_GPIO
#define PIN_AH15_GPIO 2u
#define PIN_AH15_GPIO_PIN 25u
#endif

/* Ball: AB8 */
#define PIN_CTRL_REG_ADDR_AB8 0x48140AF4UL

/* Ball: AB12 */
#define PIN_CTRL_REG_ADDR_AB12 0x48140AF8UL

/* Ball: AA8 */
#define PIN_CTRL_REG_ADDR_AA8 0x48140AFCUL

/* Ball: AD14 */
#define PIN_CTRL_REG_ADDR_AD14 0x48140B00UL

/* Ball: AE14 */
#define PIN_CTRL_REG_ADDR_AE14 0x48140B04UL

/* Ball: AF14 */
#define PIN_CTRL_REG_ADDR_AF14 0x48140B08UL

/* Ball: AD9 */
#define PIN_CTRL_REG_ADDR_AD9 0x48140B0CUL
#ifndef PIN_FUNCTION_AD9_DIO
#define PIN_FUNCTION_AD9_DIO 0x80UL
#endif
#ifndef PIN_AD9_GPIO
#define PIN_AD9_GPIO 2u
#define PIN_AD9_GPIO_PIN 26u
#endif

/* Ball: AB9 */
#define PIN_CTRL_REG_ADDR_AB9 0x48140B10UL
#ifndef PIN_FUNCTION_AB9_DIO
#define PIN_FUNCTION_AB9_DIO 0x80UL
#endif
#ifndef PIN_AB9_GPIO
#define PIN_AB9_GPIO 2u
#define PIN_AB9_GPIO_PIN 27u
#endif

/* Ball: AA9 */
#define PIN_CTRL_REG_ADDR_AA9 0x48140B14UL

/* Ball: AF8 */
#define PIN_CTRL_REG_ADDR_AF8 0x48140B18UL

/* Ball: AF6 */
#define PIN_CTRL_REG_ADDR_AF6 0x48140B1CUL

/* Ball: AF12 */
#define PIN_CTRL_REG_ADDR_AF12 0x48140B20UL

/* Ball: AE8 */
#define PIN_CTRL_REG_ADDR_AE8 0x48140B24UL

/* Ball: AC13 */
#define PIN_CTRL_REG_ADDR_AC13 0x48140B28UL

/* Ball: AE24 */
#define PIN_CTRL_REG_ADDR_AE24 0x48140B2CUL
#ifndef PIN_FUNCTION_AE24_DIO
#define PIN_FUNCTION_AE24_DIO 0x80UL
#endif
#ifndef PIN_AE24_GPIO
#define PIN_AE24_GPIO 2u
#define PIN_AE24_GPIO_PIN 28u
#endif

/* Ball: AC24 */
#define PIN_CTRL_REG_ADDR_AC24 0x48140B30UL
#ifndef PIN_FUNCTION_AC24_DIO
#define PIN_FUNCTION_AC24_DIO 0x80UL
#endif
#ifndef PIN_AC24_GPIO
#define PIN_AC24_GPIO 2u
#define PIN_AC24_GPIO_PIN 29u
#endif

/* Ball: AA23 */
#define PIN_CTRL_REG_ADDR_AA23 0x48140B34UL
#ifndef PIN_FUNCTION_AA23_DIO
#define PIN_FUNCTION_AA23_DIO 0x80UL
#endif
#ifndef PIN_AA23_GPIO
#define PIN_AA23_GPIO 2u
#define PIN_AA23_GPIO_PIN 30u
#endif

/* Ball: Y22 */
#define PIN_CTRL_REG_ADDR_Y22 0x48140B38UL
#ifndef PIN_FUNCTION_Y22_DIO
#define PIN_FUNCTION_Y22_DIO 0x80UL
#endif
#ifndef PIN_FUNCTION_Y22_PWM
#define PIN_FUNCTION_Y22_PWM 0x40UL
#endif
#ifndef PIN_Y22_GPIO
#define PIN_Y22_GPIO 2u
#define PIN_Y22_GPIO_PIN 31u
#endif

/* Ball: AH25 */
#define PIN_CTRL_REG_ADDR_AH25 0x48140B3CUL
#ifndef PIN_FUNCTION_AH25_DIO
#define PIN_FUNCTION_AH25_DIO 0x80UL
#endif
#ifndef PIN_AH25_GPIO
#define PIN_AH25_GPIO 3u
#define PIN_AH25_GPIO_PIN 0u
#endif

/* Ball: AG25 */
#define PIN_CTRL_REG_ADDR_AG25 0x48140B40UL
#ifndef PIN_FUNCTION_AG25_DIO
#define PIN_FUNCTION_AG25_DIO 0x80UL
#endif
#ifndef PIN_AG25_GPIO
#define PIN_AG25_GPIO 3u
#define PIN_AG25_GPIO_PIN 1u
#endif

/* Ball: AF25 */
#define PIN_CTRL_REG_ADDR_AF25 0x48140B44UL
#ifndef PIN_FUNCTION_AF25_DIO
#define PIN_FUNCTION_AF25_DIO 0x80UL
#endif
#ifndef PIN_AF25_GPIO
#define PIN_AF25_GPIO 3u
#define PIN_AF25_GPIO_PIN 2u
#endif

/* Ball: AD25 */
#define PIN_CTRL_REG_ADDR_AD25 0x48140B48UL
#ifndef PIN_FUNCTION_AD25_DIO
#define PIN_FUNCTION_AD25_DIO 0x80UL
#endif
#ifndef PIN_AD25_GPIO
#define PIN_AD25_GPIO 3u
#define PIN_AD25_GPIO_PIN 3u
#endif

/* Ball: AC25 */
#define PIN_CTRL_REG_ADDR_AC25 0x48140B4CUL
#ifndef PIN_FUNCTION_AC25_DIO
#define PIN_FUNCTION_AC25_DIO 0x80UL
#endif
#ifndef PIN_AC25_GPIO
#define PIN_AC25_GPIO 3u
#define PIN_AC25_GPIO_PIN 4u
#endif

/* Ball: AH26 */
#define PIN_CTRL_REG_ADDR_AH26 0x48140B50UL
#ifndef PIN_FUNCTION_AH26_DIO
#define PIN_FUNCTION_AH26_DIO 0x80UL
#endif
#ifndef PIN_AH26_GPIO
#define PIN_AH26_GPIO 3u
#define PIN_AH26_GPIO_PIN 5u
#endif

/* Ball: AA24 */
#define PIN_CTRL_REG_ADDR_AA24 0x48140B54UL
#ifndef PIN_FUNCTION_AA24_DIO
#define PIN_FUNCTION_AA24_DIO 0x80UL
#endif
#ifndef PIN_AA24_GPIO
#define PIN_AA24_GPIO 3u
#define PIN_AA24_GPIO_PIN 6u
#endif

/* Ball: Y23 */
#define PIN_CTRL_REG_ADDR_Y23 0x48140B58UL
#ifndef PIN_FUNCTION_Y23_DIO
#define PIN_FUNCTION_Y23_DIO 0x80UL
#endif
#ifndef PIN_Y23_GPIO
#define PIN_Y23_GPIO 3u
#define PIN_Y23_GPIO_PIN 7u
#endif

/* Ball: W22 */
#define PIN_CTRL_REG_ADDR_W22 0x48140B5CUL
#ifndef PIN_FUNCTION_W22_DIO
#define PIN_FUNCTION_W22_DIO 0x80UL
#endif
#ifndef PIN_W22_GPIO
#define PIN_W22_GPIO 3u
#define PIN_W22_GPIO_PIN 8u
#endif

/* Ball: AG26 */
#define PIN_CTRL_REG_ADDR_AG26 0x48140B60UL
#ifndef PIN_FUNCTION_AG26_DIO
#define PIN_FUNCTION_AG26_DIO 0x80UL
#endif
#ifndef PIN_AG26_GPIO
#define PIN_AG26_GPIO 3u
#define PIN_AG26_GPIO_PIN 9u
#endif

/* Ball: AH27 */
#define PIN_CTRL_REG_ADDR_AH27 0x48140B64UL
#ifndef PIN_FUNCTION_AH27_DIO
#define PIN_FUNCTION_AH27_DIO 0x80UL
#endif
#ifndef PIN_AH27_GPIO
#define PIN_AH27_GPIO 3u
#define PIN_AH27_GPIO_PIN 10u
#endif

/* Ball: AF26 */
#define PIN_CTRL_REG_ADDR_AF26 0x48140B68UL
#ifndef PIN_FUNCTION_AF26_DIO
#define PIN_FUNCTION_AF26_DIO 0x80UL
#endif
#ifndef PIN_AF26_GPIO
#define PIN_AF26_GPIO 3u
#define PIN_AF26_GPIO_PIN 11u
#endif

/* Ball: AE26 */
#define PIN_CTRL_REG_ADDR_AE26 0x48140B6CUL
#ifndef PIN_FUNCTION_AE26_DIO
#define PIN_FUNCTION_AE26_DIO 0x80UL
#endif
#ifndef PIN_AE26_GPIO
#define PIN_AE26_GPIO 3u
#define PIN_AE26_GPIO_PIN 12u
#endif

/* Ball: AD26 */
#define PIN_CTRL_REG_ADDR_AD26 0x48140B70UL
#ifndef PIN_FUNCTION_AD26_DIO
#define PIN_FUNCTION_AD26_DIO 0x80UL
#endif
#ifndef PIN_AD26_GPIO
#define PIN_AD26_GPIO 3u
#define PIN_AD26_GPIO_PIN 13u
#endif

/* Ball: AG27 */
#define PIN_CTRL_REG_ADDR_AG27 0x48140B74UL
#ifndef PIN_FUNCTION_AG27_DIO
#define PIN_FUNCTION_AG27_DIO 0x80UL
#endif
#ifndef PIN_AG27_GPIO
#define PIN_AG27_GPIO 3u
#define PIN_AG27_GPIO_PIN 14u
#endif

/* Ball: AC26 */
#define PIN_CTRL_REG_ADDR_AC26 0x48140B78UL
#ifndef PIN_FUNCTION_AC26_DIO
#define PIN_FUNCTION_AC26_DIO 0x80UL
#endif
#ifndef PIN_AC26_GPIO
#define PIN_AC26_GPIO 3u
#define PIN_AC26_GPIO_PIN 15u
#endif

/* Ball: AA25 */
#define PIN_CTRL_REG_ADDR_AA25 0x48140B7CUL
#ifndef PIN_FUNCTION_AA25_DIO
#define PIN_FUNCTION_AA25_DIO 0x80UL
#endif
#ifndef PIN_AA25_GPIO
#define PIN_AA25_GPIO 3u
#define PIN_AA25_GPIO_PIN 16u
#endif

/* Ball: V22 */
#define PIN_CTRL_REG_ADDR_V22 0x48140B80UL
#ifndef PIN_FUNCTION_V22_DIO
#define PIN_FUNCTION_V22_DIO 0x80UL
#endif
#ifndef PIN_V22_GPIO
#define PIN_V22_GPIO 3u
#define PIN_V22_GPIO_PIN 17u
#endif

/* Ball: W23 */
#define PIN_CTRL_REG_ADDR_W23 0x48140B84UL
#ifndef PIN_FUNCTION_W23_DIO
#define PIN_FUNCTION_W23_DIO 0x80UL
#endif
#ifndef PIN_W23_GPIO
#define PIN_W23_GPIO 3u
#define PIN_W23_GPIO_PIN 18u
#endif

/* Ball: Y24 */
#define PIN_CTRL_REG_ADDR_Y24 0x48140B88UL
#ifndef PIN_FUNCTION_Y24_DIO
#define PIN_FUNCTION_Y24_DIO 0x80UL
#endif
#ifndef PIN_Y24_GPIO
#define PIN_Y24_GPIO 3u
#define PIN_Y24_GPIO_PIN 19u
#endif

/* Ball: AF27 */
#define PIN_CTRL_REG_ADDR_AF27 0x48140B8CUL
#ifndef PIN_FUNCTION_AF27_DIO
#define PIN_FUNCTION_AF27_DIO 0x80UL
#endif
#ifndef PIN_AF27_GPIO
#define PIN_AF27_GPIO 3u
#define PIN_AF27_GPIO_PIN 20u
#endif

/* Ball: AG28 */
#define PIN_CTRL_REG_ADDR_AG28 0x48140B90UL
#ifndef PIN_FUNCTION_AG28_DIO
#define PIN_FUNCTION_AG28_DIO 0x80UL
#endif
#ifndef PIN_AG28_GPIO
#define PIN_AG28_GPIO 3u
#define PIN_AG28_GPIO_PIN 21u
#endif

/* Ball: AE27 */
#define PIN_CTRL_REG_ADDR_AE27 0x48140B94UL
#ifndef PIN_FUNCTION_AE27_DIO
#define PIN_FUNCTION_AE27_DIO 0x80UL
#endif
#ifndef PIN_AE27_GPIO
#define PIN_AE27_GPIO 3u
#define PIN_AE27_GPIO_PIN 22u
#endif

/* Ball: AF28 */
#define PIN_CTRL_REG_ADDR_AF28 0x48140B98UL
#ifndef PIN_FUNCTION_AF28_DIO
#define PIN_FUNCTION_AF28_DIO 0x80UL
#endif
#ifndef PIN_AF28_GPIO
#define PIN_AF28_GPIO 3u
#define PIN_AF28_GPIO_PIN 30u
#endif

/* Ball: J27 */
#define PIN_CTRL_REG_ADDR_J27 0x48140B9CUL
#ifndef PIN_FUNCTION_J27_DIO
#define PIN_FUNCTION_J27_DIO 0x80UL
#endif
#ifndef PIN_J27_GPIO
#define PIN_J27_GPIO 1u
#define PIN_J27_GPIO_PIN 10u
#endif

/* Ball: H28 */
#define PIN_CTRL_REG_ADDR_H28 0x48140BA0UL
#ifndef PIN_FUNCTION_H28_DIO
#define PIN_FUNCTION_H28_DIO 0x80UL
#endif
#ifndef PIN_H28_GPIO
#define PIN_H28_GPIO 1u
#define PIN_H28_GPIO_PIN 11u
#endif

/* Ball: P24 */
#define PIN_CTRL_REG_ADDR_P24 0x48140BA4UL
#ifndef PIN_FUNCTION_P24_DIO
#define PIN_FUNCTION_P24_DIO 0x80UL
#endif
#ifndef PIN_P24_GPIO
#define PIN_P24_GPIO 1u
#define PIN_P24_GPIO_PIN 12u
#endif

/* Ball: L24 */
#define PIN_CTRL_REG_ADDR_L24 0x48140BA8UL
#ifndef PIN_FUNCTION_L24_DIO
#define PIN_FUNCTION_L24_DIO 0x80UL
#endif
#ifndef PIN_L24_GPIO
#define PIN_L24_GPIO 3u
#define PIN_L24_GPIO_PIN 23u
#endif

/* Ball: L23 */
#define PIN_CTRL_REG_ADDR_L23 0x48140BACUL
#ifndef PIN_FUNCTION_L23_DIO
#define PIN_FUNCTION_L23_DIO 0x80UL
#endif
#ifndef PIN_L23_GPIO
#define PIN_L23_GPIO 3u
#define PIN_L23_GPIO_PIN 24u
#endif

/* Ball: R25 */
#define PIN_CTRL_REG_ADDR_R25 0x48140BB0UL
#ifndef PIN_FUNCTION_R25_DIO
#define PIN_FUNCTION_R25_DIO 0x80UL
#endif
#ifndef PIN_R25_GPIO
#define PIN_R25_GPIO 3u
#define PIN_R25_GPIO_PIN 25u
#endif

/* Ball: J26 */
#define PIN_CTRL_REG_ADDR_J26 0x48140BB4UL
#ifndef PIN_FUNCTION_J26_DIO
#define PIN_FUNCTION_J26_DIO 0x80UL
#endif
#ifndef PIN_J26_GPIO
#define PIN_J26_GPIO 3u
#define PIN_J26_GPIO_PIN 26u
#endif

/* Ball: H27 */
#define PIN_CTRL_REG_ADDR_H27 0x48140BB8UL
#ifndef PIN_FUNCTION_H27_DIO
#define PIN_FUNCTION_H27_DIO 0x80UL
#endif
#ifndef PIN_H27_GPIO
#define PIN_H27_GPIO 3u
#define PIN_H27_GPIO_PIN 27u
#endif

/* Ball: G28 */
#define PIN_CTRL_REG_ADDR_G28 0x48140BBCUL
#ifndef PIN_FUNCTION_G28_DIO
#define PIN_FUNCTION_G28_DIO 0x80UL
#endif
#ifndef PIN_G28_GPIO
#define PIN_G28_GPIO 3u
#define PIN_G28_GPIO_PIN 28u
#endif

/* Ball: P23 */
#define PIN_CTRL_REG_ADDR_P23 0x48140BC0UL
#ifndef PIN_FUNCTION_P23_DIO
#define PIN_FUNCTION_P23_DIO 0x80UL
#endif
#ifndef PIN_P23_GPIO
#define PIN_P23_GPIO 3u
#define PIN_P23_GPIO_PIN 29u
#endif

/* Ball: R23 */
#define PIN_CTRL_REG_ADDR_R23 0x48140BC4UL
#ifndef PIN_FUNCTION_R23_DIO
#define PIN_FUNCTION_R23_DIO 0x80UL
#endif
#ifndef PIN_R23_GPIO
#define PIN_R23_GPIO 3u
#define PIN_R23_GPIO_PIN 30u
#endif

/* Ball: J25 */
#define PIN_CTRL_REG_ADDR_J25 0x48140BC8UL

/* Ball: T23 */
#define PIN_CTRL_REG_ADDR_T23 0x48140BCCUL

/* Ball: H26 */
#define PIN_CTRL_REG_ADDR_H26 0x48140BD0UL

/* Ball: F28 */
#define PIN_CTRL_REG_ADDR_F28 0x48140BD4UL

/* Ball: G27 */
#define PIN_CTRL_REG_ADDR_G27 0x48140BD8UL

/* Ball: K22 */
#define PIN_CTRL_REG_ADDR_K22 0x48140BDCUL

/* Ball: K23 */
#define PIN_CTRL_REG_ADDR_K23 0x48140BE0UL

/* Ball: J24 */
#define PIN_CTRL_REG_ADDR_J24 0x48140BE4UL

/* Ball: H25 */
#define PIN_CTRL_REG_ADDR_H25 0x48140BE8UL

/* Ball: H22 */
#define PIN_CTRL_REG_ADDR_H22 0x48140BECUL

/* Ball: H23 */
#define PIN_CTRL_REG_ADDR_H23 0x48140BF0UL

/* Ball: G23 */
#define PIN_CTRL_REG_ADDR_G23 0x48140BF4UL

/* Ball: F27 */
#define PIN_CTRL_REG_ADDR_F27 0x48140BF8UL

/* Ball: J22 */
#define PIN_CTRL_REG_ADDR_J22 0x48140BFCUL

/* Ball: H24 */
#define PIN_CTRL_REG_ADDR_H24 0x48140C00UL

/* Ball: J23 */
#define PIN_CTRL_REG_ADDR_J23 0x48140C04UL

/* Ball: J7 */
#define PIN_CTRL_REG_ADDR_J7 0x48140C08UL
#ifndef PIN_FUNCTION_J7_DIO
#define PIN_FUNCTION_J7_DIO 0x80UL
#endif
#ifndef PIN_J7_GPIO
#define PIN_J7_GPIO 3u
#define PIN_J7_GPIO_PIN 31u
#endif

/* Ball: J5 */
#define PIN_CTRL_REG_ADDR_J5 0x48140C0CUL

/* Ball: H7 */
#define PIN_CTRL_REG_ADDR_H7 0x48140C10UL

/* Ball: K6 */
#define PIN_CTRL_REG_ADDR_K6 0x48140C14UL

/* Ball: AC4 */
#define PIN_CTRL_REG_ADDR_AC4 0x48140C18UL

/* Ball: AB6 */
#define PIN_CTRL_REG_ADDR_AB6 0x48140C1CUL

/* Ball: AF11 */
#define PIN_CTRL_REG_ADDR_AF11 0x48140C34UL
#ifndef PIN_FUNCTION_AF11_DIO
#define PIN_FUNCTION_AF11_DIO 0x2UL
#endif
#ifndef PIN_AF11_GPIO
#define PIN_AF11_GPIO 0u
#define PIN_AF11_GPIO_PIN 7u
#endif

#endif /* JACINTO5_PORTDEFS_H_ */
