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

#ifndef JACINTO5E_PORTDEFS_H_
#define JACINTO5E_PORTDEFS_H_



/* Ball: AG3 */
#define PIN_CTRL_REG_ADDR_AG3 (0x48140834UL)


/* Ball: AG2 */
#define PIN_CTRL_REG_ADDR_AG2 (0x48140838UL)
#ifndef PIN_FUNCTION_AG2_PWM
#define PIN_FUNCTION_AG2_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_AG2_ICU
#define PIN_FUNCTION_AG2_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_AG2_DIO
#define PIN_FUNCTION_AG2_DIO (0x080UL)
#endif
#ifndef PIN_AG2_GPIO
#define PIN_AG2_GPIO (0u)
#define PIN_AG2_GPIO_PIN (8u)
#endif


/* Ball: AD5 */
#define PIN_CTRL_REG_ADDR_AD5 (0x4814083CUL)
#ifndef PIN_FUNCTION_AD5_PWM
#define PIN_FUNCTION_AD5_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_AD5_ICU
#define PIN_FUNCTION_AD5_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_AD5_DIO
#define PIN_FUNCTION_AD5_DIO (0x080UL)
#endif
#ifndef PIN_AD5_GPIO
#define PIN_AD5_GPIO (0u)
#define PIN_AD5_GPIO_PIN (9u)
#endif


/* Ball: AD24 */
#define PIN_CTRL_REG_ADDR_AD24 (0x48140910UL)
#ifndef PIN_FUNCTION_AD24_CAN
#define PIN_FUNCTION_AD24_CAN (0x001UL)
#endif
#ifndef PIN_FUNCTION_AD24_UART2
#define PIN_FUNCTION_AD24_UART2 (0x002UL)
#endif
#ifndef PIN_FUNCTION_AD24_I2C3
#define PIN_FUNCTION_AD24_I2C3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_AD24_DIO
#define PIN_FUNCTION_AD24_DIO (0x080UL)
#endif
#ifndef PIN_AD24_GPIO
#define PIN_AD24_GPIO (1u)
#define PIN_AD24_GPIO_PIN (1u)
#endif


/* Ball: AE24 */
#define PIN_CTRL_REG_ADDR_AE24 (0x4814090CUL)
#ifndef PIN_FUNCTION_AE24_CAN
#define PIN_FUNCTION_AE24_CAN (0x001UL)
#endif
#ifndef PIN_FUNCTION_AE24_UART2
#define PIN_FUNCTION_AE24_UART2 (0x002UL)
#endif
#ifndef PIN_FUNCTION_AE24_I2C3
#define PIN_FUNCTION_AE24_I2C3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_AE24_DIO
#define PIN_FUNCTION_AE24_DIO (0x080UL)
#endif
#ifndef PIN_AE24_GPIO
#define PIN_AE24_GPIO (1u)
#define PIN_AE24_GPIO_PIN (0u)
#endif


/* Ball: AF13 */
#define PIN_CTRL_REG_ADDR_AF13 (0x48140818UL)
#ifndef PIN_FUNCTION_AF13_SPI1
#define PIN_FUNCTION_AF13_SPI1 (0x002UL)
#endif
#ifndef PIN_FUNCTION_AF13_PWM
#define PIN_FUNCTION_AF13_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_AF13_ICU
#define PIN_FUNCTION_AF13_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_AF13_DIO
#define PIN_FUNCTION_AF13_DIO (0x080UL)
#endif
#ifndef PIN_AF13_GPIO
#define PIN_AF13_GPIO (1u)
#define PIN_AF13_GPIO_PIN (7u)
#endif


/* Ball: A9 */
#define PIN_CTRL_REG_ADDR_A9 (0x48140BACUL)
#ifndef PIN_FUNCTION_A9_DIO
#define PIN_FUNCTION_A9_DIO (0x080UL)
#endif
#ifndef PIN_A9_GPIO
#define PIN_A9_GPIO (3u)
#define PIN_A9_GPIO_PIN (24u)
#endif


/* Ball: B10 */
#define PIN_CTRL_REG_ADDR_B10 (0x48140BB0UL)
#ifndef PIN_FUNCTION_B10_DIO
#define PIN_FUNCTION_B10_DIO (0x080UL)
#endif
#ifndef PIN_B10_GPIO
#define PIN_B10_GPIO (3u)
#define PIN_B10_GPIO_PIN (25u)
#endif


/* Ball: A8 */
#define PIN_CTRL_REG_ADDR_A8 (0x48140BB8UL)
#ifndef PIN_FUNCTION_A8_SPI3
#define PIN_FUNCTION_A8_SPI3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_A8_DIO
#define PIN_FUNCTION_A8_DIO (0x080UL)
#endif
#ifndef PIN_A8_GPIO
#define PIN_A8_GPIO (3u)
#define PIN_A8_GPIO_PIN (27u)
#endif


/* Ball: A6 */
#define PIN_CTRL_REG_ADDR_A6 (0x48140BDCUL)
#ifndef PIN_FUNCTION_A6_SPI2
#define PIN_FUNCTION_A6_SPI2 (0x020UL)
#endif
#ifndef PIN_FUNCTION_A6_DIO
#define PIN_FUNCTION_A6_DIO (0x080UL)
#endif
#ifndef PIN_A6_GPIO
#define PIN_A6_GPIO (5u)
#define PIN_A6_GPIO_PIN (21u)
#endif


/* Ball: D10 */
#define PIN_CTRL_REG_ADDR_D10 (0x48140BBCUL)
#ifndef PIN_FUNCTION_D10_DIO
#define PIN_FUNCTION_D10_DIO (0x080UL)
#endif
#ifndef PIN_D10_GPIO
#define PIN_D10_GPIO (3u)
#define PIN_D10_GPIO_PIN (28u)
#endif


/* Ball: B8 */
#define PIN_CTRL_REG_ADDR_B8 (0x48140BC0UL)
#ifndef PIN_FUNCTION_B8_DIO
#define PIN_FUNCTION_B8_DIO (0x080UL)
#endif
#ifndef PIN_B8_GPIO
#define PIN_B8_GPIO (3u)
#define PIN_B8_GPIO_PIN (29u)
#endif


/* Ball: C8 */
#define PIN_CTRL_REG_ADDR_C8 (0x48140BC4UL)
#ifndef PIN_FUNCTION_C8_DIO
#define PIN_FUNCTION_C8_DIO (0x080UL)
#endif
#ifndef PIN_C8_GPIO
#define PIN_C8_GPIO (3u)
#define PIN_C8_GPIO_PIN (30u)
#endif


/* Ball: D9 */
#define PIN_CTRL_REG_ADDR_D9 (0x48140BC8UL)
#ifndef PIN_FUNCTION_D9_UART5
#define PIN_FUNCTION_D9_UART5 (0x020UL)
#endif
#ifndef PIN_FUNCTION_D9_DIO
#define PIN_FUNCTION_D9_DIO (0x080UL)
#endif
#ifndef PIN_D9_GPIO
#define PIN_D9_GPIO (5u)
#define PIN_D9_GPIO_PIN (16u)
#endif


/* Ball: C9 */
#define PIN_CTRL_REG_ADDR_C9 (0x48140BB4UL)
#ifndef PIN_FUNCTION_C9_DIO
#define PIN_FUNCTION_C9_DIO (0x080UL)
#endif
#ifndef PIN_C9_GPIO
#define PIN_C9_GPIO (3u)
#define PIN_C9_GPIO_PIN (26u)
#endif


/* Ball: B9 */
#define PIN_CTRL_REG_ADDR_B9 (0x48140BA8UL)
#ifndef PIN_FUNCTION_B9_SPI3
#define PIN_FUNCTION_B9_SPI3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_B9_I2C2
#define PIN_FUNCTION_B9_I2C2 (0x040UL)
#endif
#ifndef PIN_FUNCTION_B9_DIO
#define PIN_FUNCTION_B9_DIO (0x080UL)
#endif
#ifndef PIN_B9_GPIO
#define PIN_B9_GPIO (3u)
#define PIN_B9_GPIO_PIN (23u)
#endif


/* Ball: D7 */
#define PIN_CTRL_REG_ADDR_D7 (0x48140BE4UL)
#ifndef PIN_FUNCTION_D7_SPI2
#define PIN_FUNCTION_D7_SPI2 (0x020UL)
#endif
#ifndef PIN_FUNCTION_D7_DIO
#define PIN_FUNCTION_D7_DIO (0x080UL)
#endif
#ifndef PIN_D7_GPIO
#define PIN_D7_GPIO (5u)
#define PIN_D7_GPIO_PIN (23u)
#endif


/* Ball: C6 */
#define PIN_CTRL_REG_ADDR_C6 (0x48140BE8UL)
#ifndef PIN_FUNCTION_C6_UART4
#define PIN_FUNCTION_C6_UART4 (0x020UL)
#endif
#ifndef PIN_FUNCTION_C6_DIO
#define PIN_FUNCTION_C6_DIO (0x080UL)
#endif
#ifndef PIN_C6_GPIO
#define PIN_C6_GPIO (5u)
#define PIN_C6_GPIO_PIN (24u)
#endif


/* Ball: A5 */
#define PIN_CTRL_REG_ADDR_A5 (0x48140BECUL)
#ifndef PIN_FUNCTION_A5_UART4
#define PIN_FUNCTION_A5_UART4 (0x020UL)
#endif
#ifndef PIN_FUNCTION_A5_DIO
#define PIN_FUNCTION_A5_DIO (0x080UL)
#endif
#ifndef PIN_A5_GPIO
#define PIN_A5_GPIO (5u)
#define PIN_A5_GPIO_PIN (25u)
#endif


/* Ball: B5 */
#define PIN_CTRL_REG_ADDR_B5 (0x48140BF0UL)
#ifndef PIN_FUNCTION_B5_UART4
#define PIN_FUNCTION_B5_UART4 (0x020UL)
#endif
#ifndef PIN_FUNCTION_B5_DIO
#define PIN_FUNCTION_B5_DIO (0x080UL)
#endif
#ifndef PIN_B5_GPIO
#define PIN_B5_GPIO (5u)
#define PIN_B5_GPIO_PIN (26u)
#endif


/* Ball: C4 */
#define PIN_CTRL_REG_ADDR_C4 (0x48140C04UL)
#ifndef PIN_FUNCTION_C4_UART1
#define PIN_FUNCTION_C4_UART1 (0x020UL)
#endif
#ifndef PIN_FUNCTION_C4_DIO
#define PIN_FUNCTION_C4_DIO (0x080UL)
#endif
#ifndef PIN_C4_GPIO
#define PIN_C4_GPIO (5u)
#define PIN_C4_GPIO_PIN (31u)
#endif


/* Ball: D8 */
#define PIN_CTRL_REG_ADDR_D8 (0x48140BCCUL)
#ifndef PIN_FUNCTION_D8_UART5
#define PIN_FUNCTION_D8_UART5 (0x020UL)
#endif
#ifndef PIN_FUNCTION_D8_DIO
#define PIN_FUNCTION_D8_DIO (0x080UL)
#endif
#ifndef PIN_D8_GPIO
#define PIN_D8_GPIO (5u)
#define PIN_D8_GPIO_PIN (17u)
#endif


/* Ball: C7 */
#define PIN_CTRL_REG_ADDR_C7 (0x48140BD8UL)
#ifndef PIN_FUNCTION_C7_SPI2
#define PIN_FUNCTION_C7_SPI2 (0x020UL)
#endif
#ifndef PIN_FUNCTION_C7_DIO
#define PIN_FUNCTION_C7_DIO (0x080UL)
#endif
#ifndef PIN_C7_GPIO
#define PIN_C7_GPIO (5u)
#define PIN_C7_GPIO_PIN (20u)
#endif


/* Ball: B7 */
#define PIN_CTRL_REG_ADDR_B7 (0x48140BD4UL)
#ifndef PIN_FUNCTION_B7_UART5
#define PIN_FUNCTION_B7_UART5 (0x020UL)
#endif
#ifndef PIN_FUNCTION_B7_DIO
#define PIN_FUNCTION_B7_DIO (0x080UL)
#endif
#ifndef PIN_B7_GPIO
#define PIN_B7_GPIO (5u)
#define PIN_B7_GPIO_PIN (19u)
#endif


/* Ball: A7 */
#define PIN_CTRL_REG_ADDR_A7 (0x48140BD0UL)
#ifndef PIN_FUNCTION_A7_UART5
#define PIN_FUNCTION_A7_UART5 (0x020UL)
#endif
#ifndef PIN_FUNCTION_A7_DIO
#define PIN_FUNCTION_A7_DIO (0x080UL)
#endif
#ifndef PIN_A7_GPIO
#define PIN_A7_GPIO (5u)
#define PIN_A7_GPIO_PIN (18u)
#endif


/* Ball: B6 */
#define PIN_CTRL_REG_ADDR_B6 (0x48140BE0UL)
#ifndef PIN_FUNCTION_B6_SPI2
#define PIN_FUNCTION_B6_SPI2 (0x020UL)
#endif
#ifndef PIN_FUNCTION_B6_DIO
#define PIN_FUNCTION_B6_DIO (0x080UL)
#endif
#ifndef PIN_B6_GPIO
#define PIN_B6_GPIO (5u)
#define PIN_B6_GPIO_PIN (22u)
#endif


/* Ball: A4 */
#define PIN_CTRL_REG_ADDR_A4 (0x48140BFCUL)
#ifndef PIN_FUNCTION_A4_UART1
#define PIN_FUNCTION_A4_UART1 (0x020UL)
#endif
#ifndef PIN_FUNCTION_A4_DIO
#define PIN_FUNCTION_A4_DIO (0x080UL)
#endif
#ifndef PIN_A4_GPIO
#define PIN_A4_GPIO (5u)
#define PIN_A4_GPIO_PIN (29u)
#endif


/* Ball: D6 */
#define PIN_CTRL_REG_ADDR_D6 (0x48140BF8UL)
#ifndef PIN_FUNCTION_D6_UART1
#define PIN_FUNCTION_D6_UART1 (0x020UL)
#endif
#ifndef PIN_FUNCTION_D6_DIO
#define PIN_FUNCTION_D6_DIO (0x080UL)
#endif
#ifndef PIN_D6_GPIO
#define PIN_D6_GPIO (5u)
#define PIN_D6_GPIO_PIN (28u)
#endif


/* Ball: C5 */
#define PIN_CTRL_REG_ADDR_C5 (0x48140BF4UL)
#ifndef PIN_FUNCTION_C5_UART4
#define PIN_FUNCTION_C5_UART4 (0x020UL)
#endif
#ifndef PIN_FUNCTION_C5_DIO
#define PIN_FUNCTION_C5_DIO (0x080UL)
#endif
#ifndef PIN_C5_GPIO
#define PIN_C5_GPIO (5u)
#define PIN_C5_GPIO_PIN (27u)
#endif


/* Ball: B4 */
#define PIN_CTRL_REG_ADDR_B4 (0x48140C00UL)
#ifndef PIN_FUNCTION_B4_UART1
#define PIN_FUNCTION_B4_UART1 (0x020UL)
#endif
#ifndef PIN_FUNCTION_B4_DIO
#define PIN_FUNCTION_B4_DIO (0x080UL)
#endif
#ifndef PIN_B4_GPIO
#define PIN_B4_GPIO (5u)
#define PIN_B4_GPIO_PIN (30u)
#endif


/* Ball: D11 */
#define PIN_CTRL_REG_ADDR_D11 (0x48140B9CUL)
#ifndef PIN_FUNCTION_D11_PWM
#define PIN_FUNCTION_D11_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_D11_ICU
#define PIN_FUNCTION_D11_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_D11_DIO
#define PIN_FUNCTION_D11_DIO (0x080UL)
#endif
#ifndef PIN_D11_GPIO
#define PIN_D11_GPIO (1u)
#define PIN_D11_GPIO_PIN (10u)
#endif


/* Ball: C23 */
#define PIN_CTRL_REG_ADDR_C23 (0x481409A0UL)
#ifndef PIN_FUNCTION_C23_I2C2
#define PIN_FUNCTION_C23_I2C2 (0x008UL)
#endif
#ifndef PIN_FUNCTION_C23_DIO
#define PIN_FUNCTION_C23_DIO (0x080UL)
#endif
#ifndef PIN_C23_GPIO
#define PIN_C23_GPIO (2u)
#define PIN_C23_GPIO_PIN (5u)
#endif


/* Ball: A24 */
#define PIN_CTRL_REG_ADDR_A24 (0x481409A4UL)
#ifndef PIN_FUNCTION_A24_I2C2
#define PIN_FUNCTION_A24_I2C2 (0x008UL)
#endif
#ifndef PIN_FUNCTION_A24_DIO
#define PIN_FUNCTION_A24_DIO (0x080UL)
#endif
#ifndef PIN_A24_GPIO
#define PIN_A24_GPIO (2u)
#define PIN_A24_GPIO_PIN (6u)
#endif


/* Ball: A23 */
#define PIN_CTRL_REG_ADDR_A23 (0x481409A8UL)
#ifndef PIN_FUNCTION_A23_I2C3
#define PIN_FUNCTION_A23_I2C3 (0x008UL)
#endif
#ifndef PIN_FUNCTION_A23_PWM
#define PIN_FUNCTION_A23_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_A23_ICU
#define PIN_FUNCTION_A23_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_A23_DIO
#define PIN_FUNCTION_A23_DIO (0x080UL)
#endif
#ifndef PIN_A23_GPIO
#define PIN_A23_GPIO (1u)
#define PIN_A23_GPIO_PIN (13u)
#endif


/* Ball: B23 */
#define PIN_CTRL_REG_ADDR_B23 (0x481409ACUL)
#ifndef PIN_FUNCTION_B23_I2C3
#define PIN_FUNCTION_B23_I2C3 (0x008UL)
#endif
#ifndef PIN_FUNCTION_B23_PWM
#define PIN_FUNCTION_B23_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_B23_ICU
#define PIN_FUNCTION_B23_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_B23_DIO
#define PIN_FUNCTION_B23_DIO (0x080UL)
#endif
#ifndef PIN_B23_GPIO
#define PIN_B23_GPIO (1u)
#define PIN_B23_GPIO_PIN (14u)
#endif


/* Ball: D21 */
#define PIN_CTRL_REG_ADDR_D21 (0x481409B0UL)
#ifndef PIN_FUNCTION_D21_SPI2
#define PIN_FUNCTION_D21_SPI2 (0x004UL)
#endif
#ifndef PIN_FUNCTION_D21_DIO
#define PIN_FUNCTION_D21_DIO (0x040UL)
#endif
#ifndef PIN_D21_GPIO
#define PIN_D21_GPIO (4u)
#define PIN_D21_GPIO_PIN (8u)
#endif
#ifndef PIN_FUNCTION_D21_DIO
#define PIN_FUNCTION_D21_DIO (0x080UL)
#endif
#ifndef PIN_D21_GPIO
#define PIN_D21_GPIO (1u)
#define PIN_D21_GPIO_PIN (15u)
#endif


/* Ball: C22 */
#define PIN_CTRL_REG_ADDR_C22 (0x481409B4UL)
#ifndef PIN_FUNCTION_C22_SPI2
#define PIN_FUNCTION_C22_SPI2 (0x004UL)
#endif
#ifndef PIN_FUNCTION_C22_DIO
#define PIN_FUNCTION_C22_DIO (0x080UL)
#endif
#ifndef PIN_C22_GPIO
#define PIN_C22_GPIO (1u)
#define PIN_C22_GPIO_PIN (16u)
#endif


/* Ball: B22 */
#define PIN_CTRL_REG_ADDR_B22 (0x481409B8UL)
#ifndef PIN_FUNCTION_B22_SPI2
#define PIN_FUNCTION_B22_SPI2 (0x004UL)
#endif
#ifndef PIN_FUNCTION_B22_PWM
#define PIN_FUNCTION_B22_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_B22_ICU
#define PIN_FUNCTION_B22_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_B22_DIO
#define PIN_FUNCTION_B22_DIO (0x080UL)
#endif
#ifndef PIN_B22_GPIO
#define PIN_B22_GPIO (1u)
#define PIN_B22_GPIO_PIN (17u)
#endif


/* Ball: D23 */
#define PIN_CTRL_REG_ADDR_D23 (0x481409BCUL)
#ifndef PIN_FUNCTION_D23_SPI2
#define PIN_FUNCTION_D23_SPI2 (0x004UL)
#endif
#ifndef PIN_FUNCTION_D23_PWM
#define PIN_FUNCTION_D23_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_D23_ICU
#define PIN_FUNCTION_D23_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_D23_DIO
#define PIN_FUNCTION_D23_DIO (0x080UL)
#endif
#ifndef PIN_D23_GPIO
#define PIN_D23_GPIO (1u)
#define PIN_D23_GPIO_PIN (18u)
#endif


/* Ball: A17 */
#define PIN_CTRL_REG_ADDR_A17 (0x481409FCUL)
#ifndef PIN_FUNCTION_A17_PWM
#define PIN_FUNCTION_A17_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_A17_ICU
#define PIN_FUNCTION_A17_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_A17_DIO
#define PIN_FUNCTION_A17_DIO (0x080UL)
#endif
#ifndef PIN_A17_GPIO
#define PIN_A17_GPIO (1u)
#define PIN_A17_GPIO_PIN (28u)
#endif


/* Ball: E17 */
#define PIN_CTRL_REG_ADDR_E17 (0x48140A0CUL)
#ifndef PIN_FUNCTION_E17_PWM
#define PIN_FUNCTION_E17_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_E17_ICU
#define PIN_FUNCTION_E17_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_E17_DIO
#define PIN_FUNCTION_E17_DIO (0x080UL)
#endif
#ifndef PIN_E17_GPIO
#define PIN_E17_GPIO (1u)
#define PIN_E17_GPIO_PIN (30u)
#endif


/* Ball: D17 */
#define PIN_CTRL_REG_ADDR_D17 (0x48140A08UL)
#ifndef PIN_FUNCTION_D17_PWM
#define PIN_FUNCTION_D17_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_D17_ICU
#define PIN_FUNCTION_D17_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_D17_DIO
#define PIN_FUNCTION_D17_DIO (0x080UL)
#endif
#ifndef PIN_D17_GPIO
#define PIN_D17_GPIO (1u)
#define PIN_D17_GPIO_PIN (29u)
#endif


/* Ball: D16 */
#define PIN_CTRL_REG_ADDR_D16 (0x481409F8UL)
#ifndef PIN_FUNCTION_D16_SPI2
#define PIN_FUNCTION_D16_SPI2 (0x004UL)
#endif
#ifndef PIN_FUNCTION_D16_PWM
#define PIN_FUNCTION_D16_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_D16_ICU
#define PIN_FUNCTION_D16_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_D16_DIO
#define PIN_FUNCTION_D16_DIO (0x080UL)
#endif
#ifndef PIN_D16_GPIO
#define PIN_D16_GPIO (1u)
#define PIN_D16_GPIO_PIN (27u)
#endif


/* Ball: E16 */
#define PIN_CTRL_REG_ADDR_E16 (0x481409E4UL)
#ifndef PIN_FUNCTION_E16_DIO
#define PIN_FUNCTION_E16_DIO (0x080UL)
#endif
#ifndef PIN_E16_GPIO
#define PIN_E16_GPIO (1u)
#define PIN_E16_GPIO_PIN (23u)
#endif


/* Ball: B16 */
#define PIN_CTRL_REG_ADDR_B16 (0x481409E8UL)
#ifndef PIN_FUNCTION_B16_DIO
#define PIN_FUNCTION_B16_DIO (0x080UL)
#endif
#ifndef PIN_B16_GPIO
#define PIN_B16_GPIO (1u)
#define PIN_B16_GPIO_PIN (24u)
#endif


/* Ball: A16 */
#define PIN_CTRL_REG_ADDR_A16 (0x481409ECUL)
#ifndef PIN_FUNCTION_A16_DIO
#define PIN_FUNCTION_A16_DIO (0x080UL)
#endif
#ifndef PIN_A16_GPIO
#define PIN_A16_GPIO (1u)
#define PIN_A16_GPIO_PIN (25u)
#endif


/* Ball: A14 */
#define PIN_CTRL_REG_ADDR_A14 (0x481409F0UL)
#ifndef PIN_FUNCTION_A14_SPI2
#define PIN_FUNCTION_A14_SPI2 (0x004UL)
#endif
#ifndef PIN_FUNCTION_A14_DIO
#define PIN_FUNCTION_A14_DIO (0x080UL)
#endif
#ifndef PIN_A14_GPIO
#define PIN_A14_GPIO (1u)
#define PIN_A14_GPIO_PIN (26u)
#endif


/* Ball: B14 */
#define PIN_CTRL_REG_ADDR_B14 (0x481409F4UL)
#ifndef PIN_FUNCTION_B14_DIO
#define PIN_FUNCTION_B14_DIO (0x080UL)
#endif
#ifndef PIN_B14_GPIO
#define PIN_B14_GPIO (1u)
#define PIN_B14_GPIO_PIN (8u)
#endif


/* Ball: B18 */
#define PIN_CTRL_REG_ADDR_B18 (0x48140960UL)
#ifndef PIN_FUNCTION_B18_SPI2
#define PIN_FUNCTION_B18_SPI2 (0x004UL)
#endif


/* Ball: C18 */
#define PIN_CTRL_REG_ADDR_C18 (0x48140964UL)
#ifndef PIN_FUNCTION_C18_SPI2
#define PIN_FUNCTION_C18_SPI2 (0x004UL)
#endif


/* Ball: D18 */
#define PIN_CTRL_REG_ADDR_D18 (0x48140968UL)


/* Ball: D19 */
#define PIN_CTRL_REG_ADDR_D19 (0x4814096CUL)


/* Ball: B19 */
#define PIN_CTRL_REG_ADDR_B19 (0x48140970UL)
#ifndef PIN_FUNCTION_B19_DIO
#define PIN_FUNCTION_B19_DIO (0x040UL)
#endif
#ifndef PIN_B19_GPIO
#define PIN_B19_GPIO (5u)
#define PIN_B19_GPIO_PIN (6u)
#endif


/* Ball: A20 */
#define PIN_CTRL_REG_ADDR_A20 (0x48140974UL)
#ifndef PIN_FUNCTION_A20_DIO
#define PIN_FUNCTION_A20_DIO (0x040UL)
#endif
#ifndef PIN_A20_GPIO
#define PIN_A20_GPIO (5u)
#define PIN_A20_GPIO_PIN (7u)
#endif


/* Ball: C19 */
#define PIN_CTRL_REG_ADDR_C19 (0x48140978UL)
#ifndef PIN_FUNCTION_C19_DIO
#define PIN_FUNCTION_C19_DIO (0x040UL)
#endif
#ifndef PIN_C19_GPIO
#define PIN_C19_GPIO (5u)
#define PIN_C19_GPIO_PIN (8u)
#endif


/* Ball: E18 */
#define PIN_CTRL_REG_ADDR_E18 (0x4814097CUL)
#ifndef PIN_FUNCTION_E18_DIO
#define PIN_FUNCTION_E18_DIO (0x040UL)
#endif
#ifndef PIN_E18_GPIO
#define PIN_E18_GPIO (5u)
#define PIN_E18_GPIO_PIN (9u)
#endif


/* Ball: B20 */
#define PIN_CTRL_REG_ADDR_B20 (0x48140980UL)
#ifndef PIN_FUNCTION_B20_UART7
#define PIN_FUNCTION_B20_UART7 (0x008UL)
#endif
#ifndef PIN_FUNCTION_B20_DIO
#define PIN_FUNCTION_B20_DIO (0x040UL)
#endif
#ifndef PIN_B20_GPIO
#define PIN_B20_GPIO (4u)
#define PIN_B20_GPIO_PIN (0u)
#endif


/* Ball: C20 */
#define PIN_CTRL_REG_ADDR_C20 (0x48140984UL)
#ifndef PIN_FUNCTION_C20_UART7
#define PIN_FUNCTION_C20_UART7 (0x008UL)
#endif
#ifndef PIN_FUNCTION_C20_DIO
#define PIN_FUNCTION_C20_DIO (0x040UL)
#endif
#ifndef PIN_C20_GPIO
#define PIN_C20_GPIO (4u)
#define PIN_C20_GPIO_PIN (1u)
#endif


/* Ball: D20 */
#define PIN_CTRL_REG_ADDR_D20 (0x48140988UL)
#ifndef PIN_FUNCTION_D20_UART7
#define PIN_FUNCTION_D20_UART7 (0x008UL)
#endif
#ifndef PIN_FUNCTION_D20_DIO
#define PIN_FUNCTION_D20_DIO (0x040UL)
#endif
#ifndef PIN_D20_GPIO
#define PIN_D20_GPIO (4u)
#define PIN_D20_GPIO_PIN (2u)
#endif


/* Ball: C21 */
#define PIN_CTRL_REG_ADDR_C21 (0x4814098CUL)
#ifndef PIN_FUNCTION_C21_UART7
#define PIN_FUNCTION_C21_UART7 (0x008UL)
#endif
#ifndef PIN_FUNCTION_C21_DIO
#define PIN_FUNCTION_C21_DIO (0x040UL)
#endif
#ifndef PIN_C21_GPIO
#define PIN_C21_GPIO (4u)
#define PIN_C21_GPIO_PIN (3u)
#endif


/* Ball: D22 */
#define PIN_CTRL_REG_ADDR_D22 (0x48140990UL)
#ifndef PIN_FUNCTION_D22_DIO
#define PIN_FUNCTION_D22_DIO (0x040UL)
#endif
#ifndef PIN_D22_GPIO
#define PIN_D22_GPIO (4u)
#define PIN_D22_GPIO_PIN (4u)
#endif


/* Ball: A21 */
#define PIN_CTRL_REG_ADDR_A21 (0x48140994UL)
#ifndef PIN_FUNCTION_A21_DIO
#define PIN_FUNCTION_A21_DIO (0x040UL)
#endif
#ifndef PIN_A21_GPIO
#define PIN_A21_GPIO (4u)
#define PIN_A21_GPIO_PIN (5u)
#endif


/* Ball: B21 */
#define PIN_CTRL_REG_ADDR_B21 (0x48140998UL)
#ifndef PIN_FUNCTION_B21_DIO
#define PIN_FUNCTION_B21_DIO (0x040UL)
#endif
#ifndef PIN_B21_GPIO
#define PIN_B21_GPIO (4u)
#define PIN_B21_GPIO_PIN (6u)
#endif


/* Ball: A22 */
#define PIN_CTRL_REG_ADDR_A22 (0x4814099CUL)
#ifndef PIN_FUNCTION_A22_DIO
#define PIN_FUNCTION_A22_DIO (0x040UL)
#endif
#ifndef PIN_A22_GPIO
#define PIN_A22_GPIO (4u)
#define PIN_A22_GPIO_PIN (7u)
#endif


/* Ball: C17 */
#define PIN_CTRL_REG_ADDR_C17 (0x48140A00UL)
#ifndef PIN_FUNCTION_C17_DIO
#define PIN_FUNCTION_C17_DIO (0x080UL)
#endif
#ifndef PIN_C17_GPIO
#define PIN_C17_GPIO (4u)
#define PIN_C17_GPIO_PIN (9u)
#endif


/* Ball: A19 */
#define PIN_CTRL_REG_ADDR_A19 (0x48140A10UL)
#ifndef PIN_FUNCTION_A19_DIO
#define PIN_FUNCTION_A19_DIO (0x080UL)
#endif
#ifndef PIN_A19_GPIO
#define PIN_A19_GPIO (1u)
#define PIN_A19_GPIO_PIN (31u)
#endif


/* Ball: B17 */
#define PIN_CTRL_REG_ADDR_B17 (0x48140A04UL)
#ifndef PIN_FUNCTION_B17_DIO
#define PIN_FUNCTION_B17_DIO (0x080UL)
#endif
#ifndef PIN_B17_GPIO
#define PIN_B17_GPIO (4u)
#define PIN_B17_GPIO_PIN (10u)
#endif


/* Ball: AE18 */
#define PIN_CTRL_REG_ADDR_AE18 (0x48140C18UL)
#ifndef PIN_FUNCTION_AE18_I2C0
#define PIN_FUNCTION_AE18_I2C0 (0x001UL)
#endif


/* Ball: AF18 */
#define PIN_CTRL_REG_ADDR_AF18 (0x48140C1CUL)
#ifndef PIN_FUNCTION_AF18_I2C0
#define PIN_FUNCTION_AF18_I2C0 (0x001UL)
#endif


/* Ball: AE16 */
#define PIN_CTRL_REG_ADDR_AE16 (0x48140934UL)
#ifndef PIN_FUNCTION_AE16_I2C1
#define PIN_FUNCTION_AE16_I2C1 (0x001UL)
#endif


/* Ball: AG17 */
#define PIN_CTRL_REG_ADDR_AG17 (0x48140938UL)
#ifndef PIN_FUNCTION_AG17_I2C1
#define PIN_FUNCTION_AG17_I2C1 (0x001UL)
#endif


/* Ball: AG4 */
#define PIN_CTRL_REG_ADDR_AG4 (0x48140848UL)


/* Ball: AE5 */
#define PIN_CTRL_REG_ADDR_AE5 (0x48140840UL)


/* Ball: AE4 */
#define PIN_CTRL_REG_ADDR_AE4 (0x4814084CUL)


/* Ball: AH4 */
#define PIN_CTRL_REG_ADDR_AH4 (0x48140844UL)


/* Ball: AH3 */
#define PIN_CTRL_REG_ADDR_AH3 (0x48140850UL)


/* Ball: AE6 */
#define PIN_CTRL_REG_ADDR_AE6 (0x48140854UL)
#ifndef PIN_FUNCTION_AE6_I2C3
#define PIN_FUNCTION_AE6_I2C3 (0x020UL)
#endif


/* Ball: AF4 */
#define PIN_CTRL_REG_ADDR_AF4 (0x48140858UL)
#ifndef PIN_FUNCTION_AF4_I2C3
#define PIN_FUNCTION_AF4_I2C3 (0x020UL)
#endif


/* Ball: AE7 */
#define PIN_CTRL_REG_ADDR_AE7 (0x4814085CUL)


/* Ball: AG6 */
#define PIN_CTRL_REG_ADDR_AG6 (0x48140860UL)


/* Ball: AH6 */
#define PIN_CTRL_REG_ADDR_AH6 (0x48140864UL)


/* Ball: AF6 */
#define PIN_CTRL_REG_ADDR_AF6 (0x48140868UL)


/* Ball: AF5 */
#define PIN_CTRL_REG_ADDR_AF5 (0x4814086CUL)


/* Ball: AH5 */
#define PIN_CTRL_REG_ADDR_AH5 (0x48140870UL)


/* Ball: AG5 */
#define PIN_CTRL_REG_ADDR_AG5 (0x48140874UL)


/* Ball: AF7 */
#define PIN_CTRL_REG_ADDR_AF7 (0x48140880UL)


/* Ball: AG7 */
#define PIN_CTRL_REG_ADDR_AG7 (0x48140878UL)


/* Ball: AE8 */
#define PIN_CTRL_REG_ADDR_AE8 (0x48140884UL)


/* Ball: AF8 */
#define PIN_CTRL_REG_ADDR_AF8 (0x4814087CUL)


/* Ball: AH8 */
#define PIN_CTRL_REG_ADDR_AH8 (0x48140888UL)


/* Ball: AG8 */
#define PIN_CTRL_REG_ADDR_AG8 (0x4814088CUL)


/* Ball: AH7 */
#define PIN_CTRL_REG_ADDR_AH7 (0x48140890UL)


/* Ball: AE9 */
#define PIN_CTRL_REG_ADDR_AE9 (0x48140894UL)


/* Ball: AE10 */
#define PIN_CTRL_REG_ADDR_AE10 (0x48140898UL)
#ifndef PIN_FUNCTION_AE10_DIO
#define PIN_FUNCTION_AE10_DIO (0x080UL)
#endif
#ifndef PIN_AE10_GPIO
#define PIN_AE10_GPIO (0u)
#define PIN_AE10_GPIO_PIN (10u)
#endif


/* Ball: AF9 */
#define PIN_CTRL_REG_ADDR_AF9 (0x4814089CUL)
#ifndef PIN_FUNCTION_AF9_DIO
#define PIN_FUNCTION_AF9_DIO (0x080UL)
#endif
#ifndef PIN_AF9_GPIO
#define PIN_AF9_GPIO (0u)
#define PIN_AF9_GPIO_PIN (11u)
#endif


/* Ball: AF10 */
#define PIN_CTRL_REG_ADDR_AF10 (0x481408A0UL)
#ifndef PIN_FUNCTION_AF10_UART5
#define PIN_FUNCTION_AF10_UART5 (0x020UL)
#endif
#ifndef PIN_FUNCTION_AF10_DIO
#define PIN_FUNCTION_AF10_DIO (0x080UL)
#endif
#ifndef PIN_AF10_GPIO
#define PIN_AF10_GPIO (0u)
#define PIN_AF10_GPIO_PIN (12u)
#endif


/* Ball: AG9 */
#define PIN_CTRL_REG_ADDR_AG9 (0x481408A4UL)
#ifndef PIN_FUNCTION_AG9_UART5
#define PIN_FUNCTION_AG9_UART5 (0x020UL)
#endif
#ifndef PIN_FUNCTION_AG9_DIO
#define PIN_FUNCTION_AG9_DIO (0x080UL)
#endif
#ifndef PIN_AG9_GPIO
#define PIN_AG9_GPIO (0u)
#define PIN_AG9_GPIO_PIN (13u)
#endif


/* Ball: AH9 */
#define PIN_CTRL_REG_ADDR_AH9 (0x481408A8UL)
#ifndef PIN_FUNCTION_AH9_PWM
#define PIN_FUNCTION_AH9_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_AH9_ICU
#define PIN_FUNCTION_AH9_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_AH9_DIO
#define PIN_FUNCTION_AH9_DIO (0x080UL)
#endif
#ifndef PIN_AH9_GPIO
#define PIN_AH9_GPIO (0u)
#define PIN_AH9_GPIO_PIN (14u)
#endif


/* Ball: AF3 */
#define PIN_CTRL_REG_ADDR_AF3 (0x481408ACUL)
#ifndef PIN_FUNCTION_AF3_PWM
#define PIN_FUNCTION_AF3_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_AF3_ICU
#define PIN_FUNCTION_AF3_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_AF3_DIO
#define PIN_FUNCTION_AF3_DIO (0x080UL)
#endif
#ifndef PIN_AF3_GPIO
#define PIN_AF3_GPIO (0u)
#define PIN_AF3_GPIO_PIN (15u)
#endif


/* Ball: AB4 */
#define PIN_CTRL_REG_ADDR_AB4 (0x481408B0UL)
#ifndef PIN_FUNCTION_AB4_DIO
#define PIN_FUNCTION_AB4_DIO (0x080UL)
#endif
#ifndef PIN_AB4_GPIO
#define PIN_AB4_GPIO (0u)
#define PIN_AB4_GPIO_PIN (16u)
#endif


/* Ball: AC4 */
#define PIN_CTRL_REG_ADDR_AC4 (0x481408B4UL)
#ifndef PIN_FUNCTION_AC4_DIO
#define PIN_FUNCTION_AC4_DIO (0x080UL)
#endif
#ifndef PIN_AC4_GPIO
#define PIN_AC4_GPIO (0u)
#define PIN_AC4_GPIO_PIN (17u)
#endif


/* Ball: AC2 */
#define PIN_CTRL_REG_ADDR_AC2 (0x481408B8UL)
#ifndef PIN_FUNCTION_AC2_PWM
#define PIN_FUNCTION_AC2_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_AC2_ICU
#define PIN_FUNCTION_AC2_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_AC2_DIO
#define PIN_FUNCTION_AC2_DIO (0x080UL)
#endif
#ifndef PIN_AC2_GPIO
#define PIN_AC2_GPIO (0u)
#define PIN_AC2_GPIO_PIN (18u)
#endif


/* Ball: AD1 */
#define PIN_CTRL_REG_ADDR_AD1 (0x481408BCUL)
#ifndef PIN_FUNCTION_AD1_PWM
#define PIN_FUNCTION_AD1_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_AD1_ICU
#define PIN_FUNCTION_AD1_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_AD1_DIO
#define PIN_FUNCTION_AD1_DIO (0x080UL)
#endif
#ifndef PIN_AD1_GPIO
#define PIN_AD1_GPIO (0u)
#define PIN_AD1_GPIO_PIN (19u)
#endif


/* Ball: AD2 */
#define PIN_CTRL_REG_ADDR_AD2 (0x481408C0UL)
#ifndef PIN_FUNCTION_AD2_DIO
#define PIN_FUNCTION_AD2_DIO (0x080UL)
#endif
#ifndef PIN_AD2_GPIO
#define PIN_AD2_GPIO (0u)
#define PIN_AD2_GPIO_PIN (20u)
#endif


/* Ball: AC3 */
#define PIN_CTRL_REG_ADDR_AC3 (0x481408C4UL)


/* Ball: AE3 */
#define PIN_CTRL_REG_ADDR_AE3 (0x481408C8UL)
#ifndef PIN_FUNCTION_AE3_DIO
#define PIN_FUNCTION_AE3_DIO (0x080UL)
#endif
#ifndef PIN_AE3_GPIO
#define PIN_AE3_GPIO (0u)
#define PIN_AE3_GPIO_PIN (21u)
#endif


/* Ball: AD3 */
#define PIN_CTRL_REG_ADDR_AD3 (0x481408CCUL)
#ifndef PIN_FUNCTION_AD3_DIO
#define PIN_FUNCTION_AD3_DIO (0x080UL)
#endif
#ifndef PIN_AD3_GPIO
#define PIN_AD3_GPIO (0u)
#define PIN_AD3_GPIO_PIN (22u)
#endif


/* Ball: AE1 */
#define PIN_CTRL_REG_ADDR_AE1 (0x481408D0UL)
#ifndef PIN_FUNCTION_AE1_DIO
#define PIN_FUNCTION_AE1_DIO (0x080UL)
#endif
#ifndef PIN_AE1_GPIO
#define PIN_AE1_GPIO (0u)
#define PIN_AE1_GPIO_PIN (23u)
#endif


/* Ball: AD4 */
#define PIN_CTRL_REG_ADDR_AD4 (0x481408D4UL)
#ifndef PIN_FUNCTION_AD4_PWM
#define PIN_FUNCTION_AD4_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_AD4_ICU
#define PIN_FUNCTION_AD4_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_AD4_DIO
#define PIN_FUNCTION_AD4_DIO (0x080UL)
#endif
#ifndef PIN_AD4_GPIO
#define PIN_AD4_GPIO (0u)
#define PIN_AD4_GPIO_PIN (24u)
#endif


/* Ball: AG1 */
#define PIN_CTRL_REG_ADDR_AG1 (0x481408D8UL)
#ifndef PIN_FUNCTION_AG1_DIO
#define PIN_FUNCTION_AG1_DIO (0x080UL)
#endif
#ifndef PIN_AG1_GPIO
#define PIN_AG1_GPIO (0u)
#define PIN_AG1_GPIO_PIN (25u)
#endif


/* Ball: AF2 */
#define PIN_CTRL_REG_ADDR_AF2 (0x481408DCUL)
#ifndef PIN_FUNCTION_AF2_DIO
#define PIN_FUNCTION_AF2_DIO (0x080UL)
#endif
#ifndef PIN_AF2_GPIO
#define PIN_AF2_GPIO (0u)
#define PIN_AF2_GPIO_PIN (26u)
#endif


/* Ball: AF1 */
#define PIN_CTRL_REG_ADDR_AF1 (0x481408E0UL)
#ifndef PIN_FUNCTION_AF1_DIO
#define PIN_FUNCTION_AF1_DIO (0x080UL)
#endif
#ifndef PIN_AF1_GPIO
#define PIN_AF1_GPIO (0u)
#define PIN_AF1_GPIO_PIN (27u)
#endif


/* Ball: AE2 */
#define PIN_CTRL_REG_ADDR_AE2 (0x481408E4UL)
#ifndef PIN_FUNCTION_AE2_PWM
#define PIN_FUNCTION_AE2_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_AE2_ICU
#define PIN_FUNCTION_AE2_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_AE2_DIO
#define PIN_FUNCTION_AE2_DIO (0x080UL)
#endif
#ifndef PIN_AE2_GPIO
#define PIN_AE2_GPIO (0u)
#define PIN_AE2_GPIO_PIN (28u)
#endif


/* Ball: C11 */
#define PIN_CTRL_REG_ADDR_C11 (0x48140BA0UL)
#ifndef PIN_FUNCTION_C11_DIO
#define PIN_FUNCTION_C11_DIO (0x080UL)
#endif
#ifndef PIN_C11_GPIO
#define PIN_C11_GPIO (1u)
#define PIN_C11_GPIO_PIN (11u)
#endif


/* Ball: C10 */
#define PIN_CTRL_REG_ADDR_C10 (0x48140BA4UL)
#ifndef PIN_FUNCTION_C10_DIO
#define PIN_FUNCTION_C10_DIO (0x080UL)
#endif
#ifndef PIN_C10_GPIO
#define PIN_C10_GPIO (1u)
#define PIN_C10_GPIO_PIN (12u)
#endif


/* Ball: AG18 */
#define PIN_CTRL_REG_ADDR_AG18 (0x48140908UL)


/* Ball: AH18 */
#define PIN_CTRL_REG_ADDR_AH18 (0x48140904UL)


/* Ball: AG19 */
#define PIN_CTRL_REG_ADDR_AG19 (0x48140900UL)
#ifndef PIN_FUNCTION_AG19_DIO
#define PIN_FUNCTION_AG19_DIO ((3)UL)
#endif
#ifndef PIN_AG19_GPIO
#define PIN_AG19_GPIO (1u)
#define PIN_AG19_GPIO_PIN (10u)
#endif


/* Ball: AH19 */
#define PIN_CTRL_REG_ADDR_AH19 (0x481408FCUL)
#ifndef PIN_FUNCTION_AH19_DIO
#define PIN_FUNCTION_AH19_DIO ((4)UL)
#endif
#ifndef PIN_AH19_GPIO
#define PIN_AH19_GPIO (1u)
#define PIN_AH19_GPIO_PIN (9u)
#endif


/* Ball: AG20 */
#define PIN_CTRL_REG_ADDR_AG20 (0x481408F8UL)
#ifndef PIN_FUNCTION_AG20_DIO
#define PIN_FUNCTION_AG20_DIO ((6)UL)
#endif
#ifndef PIN_AG20_GPIO
#define PIN_AG20_GPIO (1u)
#define PIN_AG20_GPIO_PIN (8u)
#endif


/* Ball: AH20 */
#define PIN_CTRL_REG_ADDR_AH20 (0x481408F4UL)
#ifndef PIN_FUNCTION_AH20_DIO
#define PIN_FUNCTION_AH20_DIO ((7)UL)
#endif
#ifndef PIN_AH20_GPIO
#define PIN_AH20_GPIO (1u)
#define PIN_AH20_GPIO_PIN (7u)
#endif


/* Ball: AG14 */
#define PIN_CTRL_REG_ADDR_AG14 (0x481408F0UL)
#ifndef PIN_FUNCTION_AG14_UART2
#define PIN_FUNCTION_AG14_UART2 (0x008UL)
#endif
#ifndef PIN_FUNCTION_AG14_DIO
#define PIN_FUNCTION_AG14_DIO (0x080UL)
#endif
#ifndef PIN_AG14_GPIO
#define PIN_AG14_GPIO (0u)
#define PIN_AG14_GPIO_PIN (31u)
#endif


/* Ball: AF14 */
#define PIN_CTRL_REG_ADDR_AF14 (0x481408ECUL)
#ifndef PIN_FUNCTION_AF14_DIO
#define PIN_FUNCTION_AF14_DIO (0x080UL)
#endif
#ifndef PIN_AF14_GPIO
#define PIN_AF14_GPIO (0u)
#define PIN_AF14_GPIO_PIN (30u)
#endif


/* Ball: AH13 */
#define PIN_CTRL_REG_ADDR_AH13 (0x481408E8UL)
#ifndef PIN_FUNCTION_AH13_UART2
#define PIN_FUNCTION_AH13_UART2 (0x008UL)
#endif
#ifndef PIN_FUNCTION_AH13_DIO
#define PIN_FUNCTION_AH13_DIO (0x080UL)
#endif
#ifndef PIN_AH13_GPIO
#define PIN_AH13_GPIO (0u)
#define PIN_AH13_GPIO_PIN (29u)
#endif


/* Ball: E25 */
#define PIN_CTRL_REG_ADDR_E25 (0x48140C10UL)


/* Ball: A3 */
#define PIN_CTRL_REG_ADDR_A3 (0x48140C0CUL)


/* Ball: AF19 */
#define PIN_CTRL_REG_ADDR_AF19 (0x48140C30UL)
#ifndef PIN_FUNCTION_AF19_DIO
#define PIN_FUNCTION_AF19_DIO (0x080UL)
#endif
#ifndef PIN_AF19_GPIO
#define PIN_AF19_GPIO (5u)
#define PIN_AF19_GPIO_PIN (0u)
#endif


/* Ball: AF11 */
#define PIN_CTRL_REG_ADDR_AF11 (0x4814081CUL)
#ifndef PIN_FUNCTION_AF11_DIO
#define PIN_FUNCTION_AF11_DIO (0x080UL)
#endif
#ifndef PIN_AF11_GPIO
#define PIN_AF11_GPIO (0u)
#define PIN_AF11_GPIO_PIN (1u)
#endif


/* Ball: AG10 */
#define PIN_CTRL_REG_ADDR_AG10 (0x48140820UL)
#ifndef PIN_FUNCTION_AG10_DIO
#define PIN_FUNCTION_AG10_DIO (0x080UL)
#endif
#ifndef PIN_AG10_GPIO
#define PIN_AG10_GPIO (0u)
#define PIN_AG10_GPIO_PIN (2u)
#endif


/* Ball: AH11 */
#define PIN_CTRL_REG_ADDR_AH11 (0x48140824UL)
#ifndef PIN_FUNCTION_AH11_DIO
#define PIN_FUNCTION_AH11_DIO (0x080UL)
#endif
#ifndef PIN_AH11_GPIO
#define PIN_AH11_GPIO (0u)
#define PIN_AH11_GPIO_PIN (3u)
#endif


/* Ball: AD13 */
#define PIN_CTRL_REG_ADDR_AD13 (0x48140830UL)
#ifndef PIN_FUNCTION_AD13_DIO
#define PIN_FUNCTION_AD13_DIO (0x080UL)
#endif
#ifndef PIN_AD13_GPIO
#define PIN_AD13_GPIO (0u)
#define PIN_AD13_GPIO_PIN (6u)
#endif


/* Ball: AD12 */
#define PIN_CTRL_REG_ADDR_AD12 (0x48140828UL)
#ifndef PIN_FUNCTION_AD12_DIO
#define PIN_FUNCTION_AD12_DIO (0x080UL)
#endif
#ifndef PIN_AD12_GPIO
#define PIN_AD12_GPIO (0u)
#define PIN_AD12_GPIO_PIN (4u)
#endif


/* Ball: AG11 */
#define PIN_CTRL_REG_ADDR_AG11 (0x4814082CUL)
#ifndef PIN_FUNCTION_AG11_DIO
#define PIN_FUNCTION_AG11_DIO (0x080UL)
#endif
#ifndef PIN_AG11_GPIO
#define PIN_AG11_GPIO (0u)
#define PIN_AG11_GPIO_PIN (5u)
#endif


/* Ball: AF12 */
#define PIN_CTRL_REG_ADDR_AF12 (0x48140800UL)
#ifndef PIN_FUNCTION_AF12_DIO
#define PIN_FUNCTION_AF12_DIO (0x080UL)
#endif
#ifndef PIN_AF12_GPIO
#define PIN_AF12_GPIO (4u)
#define PIN_AF12_GPIO_PIN (11u)
#endif


/* Ball: AE11 */
#define PIN_CTRL_REG_ADDR_AE11 (0x48140804UL)
#ifndef PIN_FUNCTION_AE11_DIO
#define PIN_FUNCTION_AE11_DIO (0x080UL)
#endif
#ifndef PIN_AE11_GPIO
#define PIN_AE11_GPIO (0u)
#define PIN_AE11_GPIO_PIN (0u)
#endif


/* Ball: AE12 */
#define PIN_CTRL_REG_ADDR_AE12 (0x48140808UL)
#ifndef PIN_FUNCTION_AE12_DIO
#define PIN_FUNCTION_AE12_DIO (0x080UL)
#endif
#ifndef PIN_AE12_GPIO
#define PIN_AE12_GPIO (4u)
#define PIN_AE12_GPIO_PIN (12u)
#endif


/* Ball: AG12 */
#define PIN_CTRL_REG_ADDR_AG12 (0x48140814UL)
#ifndef PIN_FUNCTION_AG12_DIO
#define PIN_FUNCTION_AG12_DIO (0x080UL)
#endif
#ifndef PIN_AG12_GPIO
#define PIN_AG12_GPIO (4u)
#define PIN_AG12_GPIO_PIN (15u)
#endif


/* Ball: AG13 */
#define PIN_CTRL_REG_ADDR_AG13 (0x4814080CUL)
#ifndef PIN_FUNCTION_AG13_DIO
#define PIN_FUNCTION_AG13_DIO (0x080UL)
#endif
#ifndef PIN_AG13_GPIO
#define PIN_AG13_GPIO (4u)
#define PIN_AG13_GPIO_PIN (13u)
#endif


/* Ball: AH12 */
#define PIN_CTRL_REG_ADDR_AH12 (0x48140810UL)
#ifndef PIN_FUNCTION_AH12_DIO
#define PIN_FUNCTION_AH12_DIO (0x080UL)
#endif
#ifndef PIN_AH12_GPIO
#define PIN_AH12_GPIO (4u)
#define PIN_AH12_GPIO_PIN (14u)
#endif


/* Ball: B15 */
#define PIN_CTRL_REG_ADDR_B15 (0x481409E0UL)
#ifndef PIN_FUNCTION_B15_DIO
#define PIN_FUNCTION_B15_DIO (0x080UL)
#endif
#ifndef PIN_B15_GPIO
#define PIN_B15_GPIO (1u)
#define PIN_B15_GPIO_PIN (15u)
#endif


/* Ball: C16 */
#define PIN_CTRL_REG_ADDR_C16 (0x481409DCUL)
#ifndef PIN_FUNCTION_C16_DIO
#define PIN_FUNCTION_C16_DIO (0x080UL)
#endif
#ifndef PIN_C16_GPIO
#define PIN_C16_GPIO (1u)
#define PIN_C16_GPIO_PIN (14u)
#endif


/* Ball: A15 */
#define PIN_CTRL_REG_ADDR_A15 (0x481409D0UL)
#ifndef PIN_FUNCTION_A15_DIO
#define PIN_FUNCTION_A15_DIO (0x080UL)
#endif
#ifndef PIN_A15_GPIO
#define PIN_A15_GPIO (2u)
#define PIN_A15_GPIO_PIN (5u)
#endif


/* Ball: E14 */
#define PIN_CTRL_REG_ADDR_E14 (0x481409CCUL)
#ifndef PIN_FUNCTION_E14_PWM
#define PIN_FUNCTION_E14_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_E14_ICU
#define PIN_FUNCTION_E14_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_E14_DIO
#define PIN_FUNCTION_E14_DIO (0x080UL)
#endif
#ifndef PIN_E14_GPIO
#define PIN_E14_GPIO (1u)
#define PIN_E14_GPIO_PIN (22u)
#endif


/* Ball: D14 */
#define PIN_CTRL_REG_ADDR_D14 (0x481409C8UL)
#ifndef PIN_FUNCTION_D14_PWM
#define PIN_FUNCTION_D14_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_D14_ICU
#define PIN_FUNCTION_D14_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_D14_DIO
#define PIN_FUNCTION_D14_DIO (0x080UL)
#endif
#ifndef PIN_D14_GPIO
#define PIN_D14_GPIO (1u)
#define PIN_D14_GPIO_PIN (21u)
#endif


/* Ball: C15 */
#define PIN_CTRL_REG_ADDR_C15 (0x481409C4UL)
#ifndef PIN_FUNCTION_C15_UART2
#define PIN_FUNCTION_C15_UART2 (0x020UL)
#endif
#ifndef PIN_FUNCTION_C15_DIO
#define PIN_FUNCTION_C15_DIO (0x080UL)
#endif
#ifndef PIN_C15_GPIO
#define PIN_C15_GPIO (1u)
#define PIN_C15_GPIO_PIN (20u)
#endif


/* Ball: C14 */
#define PIN_CTRL_REG_ADDR_C14 (0x481409C0UL)
#ifndef PIN_FUNCTION_C14_UART2
#define PIN_FUNCTION_C14_UART2 (0x020UL)
#endif
#ifndef PIN_FUNCTION_C14_DIO
#define PIN_FUNCTION_C14_DIO (0x080UL)
#endif
#ifndef PIN_C14_GPIO
#define PIN_C14_GPIO (1u)
#define PIN_C14_GPIO_PIN (19u)
#endif


/* Ball: E15 */
#define PIN_CTRL_REG_ADDR_E15 (0x481409D8UL)
#ifndef PIN_FUNCTION_E15_DIO
#define PIN_FUNCTION_E15_DIO (0x080UL)
#endif
#ifndef PIN_E15_GPIO
#define PIN_E15_GPIO (1u)
#define PIN_E15_GPIO_PIN (13u)
#endif


/* Ball: D15 */
#define PIN_CTRL_REG_ADDR_D15 (0x481409D4UL)
#ifndef PIN_FUNCTION_D15_DIO
#define PIN_FUNCTION_D15_DIO (0x080UL)
#endif
#ifndef PIN_D15_GPIO
#define PIN_D15_GPIO (2u)
#define PIN_D15_GPIO_PIN (6u)
#endif


/* Ball: AE13 */
#define PIN_CTRL_REG_ADDR_AE13 (0x4814094CUL)
#ifndef PIN_FUNCTION_AE13_SPI0
#define PIN_FUNCTION_AE13_SPI0 (0x001UL)
#endif


/* Ball: AF16 */
#define PIN_CTRL_REG_ADDR_AF16 (0x48140948UL)
#ifndef PIN_FUNCTION_AF16_SPI0
#define PIN_FUNCTION_AF16_SPI0 (0x001UL)
#endif


/* Ball: AD14 */
#define PIN_CTRL_REG_ADDR_AD14 (0x48140944UL)
#ifndef PIN_FUNCTION_AD14_SPI0
#define PIN_FUNCTION_AD14_SPI0 (0x001UL)
#endif


/* Ball: AG16 */
#define PIN_CTRL_REG_ADDR_AG16 (0x48140940UL)
#ifndef PIN_FUNCTION_AG16_SPI0
#define PIN_FUNCTION_AG16_SPI0 (0x001UL)
#endif
#ifndef PIN_FUNCTION_AG16_DIO
#define PIN_FUNCTION_AG16_DIO (0x080UL)
#endif
#ifndef PIN_AG16_GPIO
#define PIN_AG16_GPIO (4u)
#define PIN_AG16_GPIO_PIN (18u)
#endif


/* Ball: AF17 */
#define PIN_CTRL_REG_ADDR_AF17 (0x4814093CUL)
#ifndef PIN_FUNCTION_AF17_SPI0
#define PIN_FUNCTION_AF17_SPI0 (0x001UL)
#endif
#ifndef PIN_FUNCTION_AF17_PWM
#define PIN_FUNCTION_AF17_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_AF17_ICU
#define PIN_FUNCTION_AF17_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_AF17_DIO
#define PIN_FUNCTION_AF17_DIO (0x080UL)
#endif
#ifndef PIN_AF17_GPIO
#define PIN_AF17_GPIO (1u)
#define PIN_AF17_GPIO_PIN (6u)
#endif


/* Ball: AE14 */
#define PIN_CTRL_REG_ADDR_AE14 (0x4814095CUL)
#ifndef PIN_FUNCTION_AE14_SPI1
#define PIN_FUNCTION_AE14_SPI1 (0x001UL)
#endif
#ifndef PIN_FUNCTION_AE14_DIO
#define PIN_FUNCTION_AE14_DIO (0x080UL)
#endif
#ifndef PIN_AE14_GPIO
#define PIN_AE14_GPIO (1u)
#define PIN_AE14_GPIO_PIN (26u)
#endif


/* Ball: AG15 */
#define PIN_CTRL_REG_ADDR_AG15 (0x48140958UL)
#ifndef PIN_FUNCTION_AG15_SPI1
#define PIN_FUNCTION_AG15_SPI1 (0x001UL)
#endif
#ifndef PIN_FUNCTION_AG15_DIO
#define PIN_FUNCTION_AG15_DIO (0x080UL)
#endif
#ifndef PIN_AG15_GPIO
#define PIN_AG15_GPIO (1u)
#define PIN_AG15_GPIO_PIN (18u)
#endif


/* Ball: AF15 */
#define PIN_CTRL_REG_ADDR_AF15 (0x48140954UL)
#ifndef PIN_FUNCTION_AF15_SPI1
#define PIN_FUNCTION_AF15_SPI1 (0x001UL)
#endif
#ifndef PIN_FUNCTION_AF15_DIO
#define PIN_FUNCTION_AF15_DIO (0x080UL)
#endif
#ifndef PIN_AF15_GPIO
#define PIN_AF15_GPIO (1u)
#define PIN_AF15_GPIO_PIN (17u)
#endif


/* Ball: AD15 */
#define PIN_CTRL_REG_ADDR_AD15 (0x48140950UL)
#ifndef PIN_FUNCTION_AD15_SPI1
#define PIN_FUNCTION_AD15_SPI1 (0x001UL)
#endif
#ifndef PIN_FUNCTION_AD15_DIO
#define PIN_FUNCTION_AD15_DIO (0x080UL)
#endif
#ifndef PIN_AD15_GPIO
#define PIN_AD15_GPIO (1u)
#define PIN_AD15_GPIO_PIN (16u)
#endif


/* Ball: AF25 */
#define PIN_CTRL_REG_ADDR_AF25 (0x4814091CUL)
#ifndef PIN_FUNCTION_AF25_UART0
#define PIN_FUNCTION_AF25_UART0 (0x001UL)
#endif
#ifndef PIN_FUNCTION_AF25_UART4
#define PIN_FUNCTION_AF25_UART4 (0x002UL)
#endif
#ifndef PIN_FUNCTION_AF25_CAN
#define PIN_FUNCTION_AF25_CAN (0x008UL)
#endif
#ifndef PIN_FUNCTION_AF25_SPI1
#define PIN_FUNCTION_AF25_SPI1 (0x010UL)
#endif
#ifndef PIN_FUNCTION_AF25_DIO
#define PIN_FUNCTION_AF25_DIO (0x080UL)
#endif
#ifndef PIN_AF25_GPIO
#define PIN_AF25_GPIO (4u)
#define PIN_AF25_GPIO_PIN (16u)
#endif


/* Ball: AF23 */
#define PIN_CTRL_REG_ADDR_AF23 (0x48140924UL)
#ifndef PIN_FUNCTION_AF23_UART0
#define PIN_FUNCTION_AF23_UART0 (0x001UL)
#endif
#ifndef PIN_FUNCTION_AF23_UART3
#define PIN_FUNCTION_AF23_UART3 (0x002UL)
#endif
#ifndef PIN_FUNCTION_AF23_SPI0
#define PIN_FUNCTION_AF23_SPI0 (0x010UL)
#endif
#ifndef PIN_FUNCTION_AF23_I2C2
#define PIN_FUNCTION_AF23_I2C2 (0x020UL)
#endif
#ifndef PIN_FUNCTION_AF23_DIO
#define PIN_FUNCTION_AF23_DIO (0x080UL)
#endif
#ifndef PIN_AF23_GPIO
#define PIN_AF23_GPIO (1u)
#define PIN_AF23_GPIO_PIN (2u)
#endif


/* Ball: AE15 */
#define PIN_CTRL_REG_ADDR_AE15 (0x48140928UL)
#ifndef PIN_FUNCTION_AE15_UART0
#define PIN_FUNCTION_AE15_UART0 (0x001UL)
#endif
#ifndef PIN_FUNCTION_AE15_UART3
#define PIN_FUNCTION_AE15_UART3 (0x002UL)
#endif
#ifndef PIN_FUNCTION_AE15_SPI0
#define PIN_FUNCTION_AE15_SPI0 (0x010UL)
#endif
#ifndef PIN_FUNCTION_AE15_I2C2
#define PIN_FUNCTION_AE15_I2C2 (0x020UL)
#endif
#ifndef PIN_FUNCTION_AE15_DIO
#define PIN_FUNCTION_AE15_DIO (0x080UL)
#endif
#ifndef PIN_AE15_GPIO
#define PIN_AE15_GPIO (1u)
#define PIN_AE15_GPIO_PIN (3u)
#endif


/* Ball: AE17 */
#define PIN_CTRL_REG_ADDR_AE17 (0x4814092CUL)
#ifndef PIN_FUNCTION_AE17_UART0
#define PIN_FUNCTION_AE17_UART0 (0x001UL)
#endif
#ifndef PIN_FUNCTION_AE17_UART3
#define PIN_FUNCTION_AE17_UART3 (0x002UL)
#endif
#ifndef PIN_FUNCTION_AE17_UART1
#define PIN_FUNCTION_AE17_UART1 (0x004UL)
#endif
#ifndef PIN_FUNCTION_AE17_DIO
#define PIN_FUNCTION_AE17_DIO (0x080UL)
#endif
#ifndef PIN_AE17_GPIO
#define PIN_AE17_GPIO (1u)
#define PIN_AE17_GPIO_PIN (4u)
#endif


/* Ball: AD16 */
#define PIN_CTRL_REG_ADDR_AD16 (0x48140930UL)
#ifndef PIN_FUNCTION_AD16_UART0
#define PIN_FUNCTION_AD16_UART0 (0x001UL)
#endif
#ifndef PIN_FUNCTION_AD16_UART3
#define PIN_FUNCTION_AD16_UART3 (0x002UL)
#endif
#ifndef PIN_FUNCTION_AD16_UART1
#define PIN_FUNCTION_AD16_UART1 (0x004UL)
#endif
#ifndef PIN_FUNCTION_AD16_DIO
#define PIN_FUNCTION_AD16_DIO (0x080UL)
#endif
#ifndef PIN_AD16_GPIO
#define PIN_AD16_GPIO (1u)
#define PIN_AD16_GPIO_PIN (5u)
#endif


/* Ball: AE25 */
#define PIN_CTRL_REG_ADDR_AE25 (0x48140920UL)
#ifndef PIN_FUNCTION_AE25_UART0
#define PIN_FUNCTION_AE25_UART0 (0x001UL)
#endif
#ifndef PIN_FUNCTION_AE25_UART4
#define PIN_FUNCTION_AE25_UART4 (0x002UL)
#endif
#ifndef PIN_FUNCTION_AE25_CAN
#define PIN_FUNCTION_AE25_CAN (0x008UL)
#endif
#ifndef PIN_FUNCTION_AE25_SPI1
#define PIN_FUNCTION_AE25_SPI1 (0x010UL)
#endif
#ifndef PIN_FUNCTION_AE25_DIO
#define PIN_FUNCTION_AE25_DIO (0x080UL)
#endif
#ifndef PIN_AE25_GPIO
#define PIN_AE25_GPIO (4u)
#define PIN_AE25_GPIO_PIN (17u)
#endif


/* Ball: AF26 */
#define PIN_CTRL_REG_ADDR_AF26 (0x48140914UL)
#ifndef PIN_FUNCTION_AF26_UART0
#define PIN_FUNCTION_AF26_UART0 (0x001UL)
#endif


/* Ball: AF24 */
#define PIN_CTRL_REG_ADDR_AF24 (0x48140918UL)
#ifndef PIN_FUNCTION_AF24_UART0
#define PIN_FUNCTION_AF24_UART0 (0x001UL)
#endif


/* Ball: V25 */
#define PIN_CTRL_REG_ADDR_V25 (0x48140C34UL)
#ifndef PIN_FUNCTION_V25_DIO
#define PIN_FUNCTION_V25_DIO (0x002UL)
#endif
#ifndef PIN_V25_GPIO
#define PIN_V25_GPIO (0u)
#define PIN_V25_GPIO_PIN (7u)
#endif


/* Ball: M27 */
#define PIN_CTRL_REG_ADDR_M27 (0x48140A20UL)
#ifndef PIN_FUNCTION_M27_DIO
#define PIN_FUNCTION_M27_DIO (0x080UL)
#endif
#ifndef PIN_M27_GPIO
#define PIN_M27_GPIO (2u)
#define PIN_M27_GPIO_PIN (2u)
#endif


/* Ball: R26 */
#define PIN_CTRL_REG_ADDR_R26 (0x48140A2CUL)
#ifndef PIN_FUNCTION_R26_DIO
#define PIN_FUNCTION_R26_DIO (0x080UL)
#endif
#ifndef PIN_R26_GPIO
#define PIN_R26_GPIO (1u)
#define PIN_R26_GPIO_PIN (11u)
#endif


/* Ball: R27 */
#define PIN_CTRL_REG_ADDR_R27 (0x48140A30UL)
#ifndef PIN_FUNCTION_R27_DIO
#define PIN_FUNCTION_R27_DIO (0x080UL)
#endif
#ifndef PIN_R27_GPIO
#define PIN_R27_GPIO (1u)
#define PIN_R27_GPIO_PIN (12u)
#endif


/* Ball: T26 */
#define PIN_CTRL_REG_ADDR_T26 (0x48140A34UL)
#ifndef PIN_FUNCTION_T26_DIO
#define PIN_FUNCTION_T26_DIO (0x080UL)
#endif
#ifndef PIN_T26_GPIO
#define PIN_T26_GPIO (2u)
#define PIN_T26_GPIO_PIN (7u)
#endif


/* Ball: R28 */
#define PIN_CTRL_REG_ADDR_R28 (0x48140A38UL)
#ifndef PIN_FUNCTION_R28_DIO
#define PIN_FUNCTION_R28_DIO (0x080UL)
#endif
#ifndef PIN_R28_GPIO
#define PIN_R28_GPIO (2u)
#define PIN_R28_GPIO_PIN (8u)
#endif


/* Ball: R25 */
#define PIN_CTRL_REG_ADDR_R25 (0x48140A3CUL)
#ifndef PIN_FUNCTION_R25_DIO
#define PIN_FUNCTION_R25_DIO (0x080UL)
#endif
#ifndef PIN_R25_GPIO
#define PIN_R25_GPIO (2u)
#define PIN_R25_GPIO_PIN (9u)
#endif


/* Ball: P25 */
#define PIN_CTRL_REG_ADDR_P25 (0x48140A40UL)
#ifndef PIN_FUNCTION_P25_DIO
#define PIN_FUNCTION_P25_DIO (0x080UL)
#endif
#ifndef PIN_P25_GPIO
#define PIN_P25_GPIO (2u)
#define PIN_P25_GPIO_PIN (10u)
#endif


/* Ball: P26 */
#define PIN_CTRL_REG_ADDR_P26 (0x48140A44UL)
#ifndef PIN_FUNCTION_P26_DIO
#define PIN_FUNCTION_P26_DIO (0x080UL)
#endif
#ifndef PIN_P26_GPIO
#define PIN_P26_GPIO (2u)
#define PIN_P26_GPIO_PIN (11u)
#endif


/* Ball: P28 */
#define PIN_CTRL_REG_ADDR_P28 (0x48140A48UL)
#ifndef PIN_FUNCTION_P28_DIO
#define PIN_FUNCTION_P28_DIO (0x080UL)
#endif
#ifndef PIN_P28_GPIO
#define PIN_P28_GPIO (2u)
#define PIN_P28_GPIO_PIN (12u)
#endif


/* Ball: L28 */
#define PIN_CTRL_REG_ADDR_L28 (0x48140A6CUL)
#ifndef PIN_FUNCTION_L28_I2C2
#define PIN_FUNCTION_L28_I2C2 (0x020UL)
#endif
#ifndef PIN_FUNCTION_L28_DIO
#define PIN_FUNCTION_L28_DIO (0x080UL)
#endif
#ifndef PIN_L28_GPIO
#define PIN_L28_GPIO (0u)
#define PIN_L28_GPIO_PIN (10u)
#endif


/* Ball: L26 */
#define PIN_CTRL_REG_ADDR_L26 (0x48140A70UL)
#ifndef PIN_FUNCTION_L26_DIO
#define PIN_FUNCTION_L26_DIO (0x080UL)
#endif
#ifndef PIN_L26_GPIO
#define PIN_L26_GPIO (0u)
#define PIN_L26_GPIO_PIN (11u)
#endif


/* Ball: L24 */
#define PIN_CTRL_REG_ADDR_L24 (0x48140A74UL)
#ifndef PIN_FUNCTION_L24_I2C3
#define PIN_FUNCTION_L24_I2C3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_L24_DIO
#define PIN_FUNCTION_L24_DIO (0x080UL)
#endif
#ifndef PIN_L24_GPIO
#define PIN_L24_GPIO (0u)
#define PIN_L24_GPIO_PIN (12u)
#endif


/* Ball: K25 */
#define PIN_CTRL_REG_ADDR_K25 (0x48140A78UL)
#ifndef PIN_FUNCTION_K25_I2C3
#define PIN_FUNCTION_K25_I2C3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_K25_DIO
#define PIN_FUNCTION_K25_DIO (0x080UL)
#endif
#ifndef PIN_K25_GPIO
#define PIN_K25_GPIO (0u)
#define PIN_K25_GPIO_PIN (13u)
#endif


/* Ball: K27 */
#define PIN_CTRL_REG_ADDR_K27 (0x48140A7CUL)
#ifndef PIN_FUNCTION_K27_SPI3
#define PIN_FUNCTION_K27_SPI3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_K27_DIO
#define PIN_FUNCTION_K27_DIO (0x080UL)
#endif
#ifndef PIN_K27_GPIO
#define PIN_K27_GPIO (0u)
#define PIN_K27_GPIO_PIN (14u)
#endif


/* Ball: K26 */
#define PIN_CTRL_REG_ADDR_K26 (0x48140A80UL)
#ifndef PIN_FUNCTION_K26_SPI3
#define PIN_FUNCTION_K26_SPI3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_K26_DIO
#define PIN_FUNCTION_K26_DIO (0x080UL)
#endif
#ifndef PIN_K26_GPIO
#define PIN_K26_GPIO (0u)
#define PIN_K26_GPIO_PIN (15u)
#endif


/* Ball: J25 */
#define PIN_CTRL_REG_ADDR_J25 (0x48140A84UL)
#ifndef PIN_FUNCTION_J25_SPI3
#define PIN_FUNCTION_J25_SPI3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_J25_DIO
#define PIN_FUNCTION_J25_DIO (0x080UL)
#endif
#ifndef PIN_J25_GPIO
#define PIN_J25_GPIO (0u)
#define PIN_J25_GPIO_PIN (16u)
#endif


/* Ball: J26 */
#define PIN_CTRL_REG_ADDR_J26 (0x48140A88UL)
#ifndef PIN_FUNCTION_J26_SPI3
#define PIN_FUNCTION_J26_SPI3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_J26_DIO
#define PIN_FUNCTION_J26_DIO (0x080UL)
#endif
#ifndef PIN_J26_GPIO
#define PIN_J26_GPIO (0u)
#define PIN_J26_GPIO_PIN (17u)
#endif


/* Ball: J27 */
#define PIN_CTRL_REG_ADDR_J27 (0x48140A8CUL)
#ifndef PIN_FUNCTION_J27_UART6
#define PIN_FUNCTION_J27_UART6 (0x010UL)
#endif
#ifndef PIN_FUNCTION_J27_DIO
#define PIN_FUNCTION_J27_DIO (0x080UL)
#endif
#ifndef PIN_J27_GPIO
#define PIN_J27_GPIO (0u)
#define PIN_J27_GPIO_PIN (18u)
#endif


/* Ball: N24 */
#define PIN_CTRL_REG_ADDR_N24 (0x48140A54UL)
#ifndef PIN_FUNCTION_N24_DIO
#define PIN_FUNCTION_N24_DIO (0x080UL)
#endif
#ifndef PIN_N24_GPIO
#define PIN_N24_GPIO (2u)
#define PIN_N24_GPIO_PIN (15u)
#endif


/* Ball: N25 */
#define PIN_CTRL_REG_ADDR_N25 (0x48140A58UL)
#ifndef PIN_FUNCTION_N25_DIO
#define PIN_FUNCTION_N25_DIO (0x080UL)
#endif
#ifndef PIN_N25_GPIO
#define PIN_N25_GPIO (2u)
#define PIN_N25_GPIO_PIN (16u)
#endif


/* Ball: N26 */
#define PIN_CTRL_REG_ADDR_N26 (0x48140A5CUL)
#ifndef PIN_FUNCTION_N26_UART7
#define PIN_FUNCTION_N26_UART7 (0x010UL)
#endif
#ifndef PIN_FUNCTION_N26_DIO
#define PIN_FUNCTION_N26_DIO (0x080UL)
#endif
#ifndef PIN_N26_GPIO
#define PIN_N26_GPIO (2u)
#define PIN_N26_GPIO_PIN (17u)
#endif


/* Ball: N27 */
#define PIN_CTRL_REG_ADDR_N27 (0x48140A60UL)
#ifndef PIN_FUNCTION_N27_UART7
#define PIN_FUNCTION_N27_UART7 (0x010UL)
#endif
#ifndef PIN_FUNCTION_N27_DIO
#define PIN_FUNCTION_N27_DIO (0x080UL)
#endif
#ifndef PIN_N27_GPIO
#define PIN_N27_GPIO (2u)
#define PIN_N27_GPIO_PIN (18u)
#endif


/* Ball: N28 */
#define PIN_CTRL_REG_ADDR_N28 (0x48140A64UL)
#ifndef PIN_FUNCTION_N28_UART7
#define PIN_FUNCTION_N28_UART7 (0x010UL)
#endif
#ifndef PIN_FUNCTION_N28_DIO
#define PIN_FUNCTION_N28_DIO (0x080UL)
#endif
#ifndef PIN_N28_GPIO
#define PIN_N28_GPIO (2u)
#define PIN_N28_GPIO_PIN (19u)
#endif


/* Ball: M25 */
#define PIN_CTRL_REG_ADDR_M25 (0x48140A68UL)
#ifndef PIN_FUNCTION_M25_UART7
#define PIN_FUNCTION_M25_UART7 (0x010UL)
#endif
#ifndef PIN_FUNCTION_M25_DIO
#define PIN_FUNCTION_M25_DIO (0x080UL)
#endif
#ifndef PIN_M25_GPIO
#define PIN_M25_GPIO (2u)
#define PIN_M25_GPIO_PIN (20u)
#endif


/* Ball: P27 */
#define PIN_CTRL_REG_ADDR_P27 (0x48140A4CUL)
#ifndef PIN_FUNCTION_P27_DIO
#define PIN_FUNCTION_P27_DIO (0x080UL)
#endif
#ifndef PIN_P27_GPIO
#define PIN_P27_GPIO (2u)
#define PIN_P27_GPIO_PIN (13u)
#endif


/* Ball: P24 */
#define PIN_CTRL_REG_ADDR_P24 (0x48140A50UL)
#ifndef PIN_FUNCTION_P24_DIO
#define PIN_FUNCTION_P24_DIO (0x080UL)
#endif
#ifndef PIN_P24_GPIO
#define PIN_P24_GPIO (2u)
#define PIN_P24_GPIO_PIN (14u)
#endif


/* Ball: J28 */
#define PIN_CTRL_REG_ADDR_J28 (0x48140A94UL)
#ifndef PIN_FUNCTION_J28_UART6
#define PIN_FUNCTION_J28_UART6 (0x010UL)
#endif
#ifndef PIN_FUNCTION_J28_DIO
#define PIN_FUNCTION_J28_DIO (0x080UL)
#endif
#ifndef PIN_J28_GPIO
#define PIN_J28_GPIO (0u)
#define PIN_J28_GPIO_PIN (20u)
#endif


/* Ball: M26 */
#define PIN_CTRL_REG_ADDR_M26 (0x48140A24UL)
#ifndef PIN_FUNCTION_M26_UART5
#define PIN_FUNCTION_M26_UART5 (0x020UL)
#endif
#ifndef PIN_FUNCTION_M26_DIO
#define PIN_FUNCTION_M26_DIO (0x080UL)
#endif
#ifndef PIN_M26_GPIO
#define PIN_M26_GPIO (2u)
#define PIN_M26_GPIO_PIN (3u)
#endif


/* Ball: M28 */
#define PIN_CTRL_REG_ADDR_M28 (0x48140A28UL)
#ifndef PIN_FUNCTION_M28_UART5
#define PIN_FUNCTION_M28_UART5 (0x020UL)
#endif
#ifndef PIN_FUNCTION_M28_DIO
#define PIN_FUNCTION_M28_DIO (0x080UL)
#endif
#ifndef PIN_M28_GPIO
#define PIN_M28_GPIO (2u)
#define PIN_M28_GPIO_PIN (4u)
#endif


/* Ball: M24 */
#define PIN_CTRL_REG_ADDR_M24 (0x48140A14UL)
#ifndef PIN_FUNCTION_M24_DIO
#define PIN_FUNCTION_M24_DIO (0x080UL)
#endif
#ifndef PIN_M24_GPIO
#define PIN_M24_GPIO (1u)
#define PIN_M24_GPIO_PIN (9u)
#endif


/* Ball: L27 */
#define PIN_CTRL_REG_ADDR_L27 (0x48140A18UL)
#ifndef PIN_FUNCTION_L27_UART5
#define PIN_FUNCTION_L27_UART5 (0x020UL)
#endif
#ifndef PIN_FUNCTION_L27_I2C2
#define PIN_FUNCTION_L27_I2C2 (0x040UL)
#endif
#ifndef PIN_FUNCTION_L27_DIO
#define PIN_FUNCTION_L27_DIO (0x080UL)
#endif
#ifndef PIN_L27_GPIO
#define PIN_L27_GPIO (2u)
#define PIN_L27_GPIO_PIN (0u)
#endif


/* Ball: L25 */
#define PIN_CTRL_REG_ADDR_L25 (0x48140A1CUL)
#ifndef PIN_FUNCTION_L25_UART5
#define PIN_FUNCTION_L25_UART5 (0x020UL)
#endif
#ifndef PIN_FUNCTION_L25_I2C2
#define PIN_FUNCTION_L25_I2C2 (0x040UL)
#endif
#ifndef PIN_FUNCTION_L25_DIO
#define PIN_FUNCTION_L25_DIO (0x080UL)
#endif
#ifndef PIN_L25_GPIO
#define PIN_L25_GPIO (2u)
#define PIN_L25_GPIO_PIN (1u)
#endif


/* Ball: Y27 */
#define PIN_CTRL_REG_ADDR_Y27 (0x48140AC8UL)
#ifndef PIN_FUNCTION_Y27_SPI3
#define PIN_FUNCTION_Y27_SPI3 (0x010UL)
#endif
#ifndef PIN_FUNCTION_Y27_PWM
#define PIN_FUNCTION_Y27_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_Y27_ICU
#define PIN_FUNCTION_Y27_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_Y27_DIO
#define PIN_FUNCTION_Y27_DIO (0x080UL)
#endif
#ifndef PIN_Y27_GPIO
#define PIN_Y27_GPIO (2u)
#define PIN_Y27_GPIO_PIN (21u)
#endif


/* Ball: Y25 */
#define PIN_CTRL_REG_ADDR_Y25 (0x48140ACCUL)
#ifndef PIN_FUNCTION_Y25_DIO
#define PIN_FUNCTION_Y25_DIO (0x080UL)
#endif
#ifndef PIN_Y25_GPIO
#define PIN_Y25_GPIO (2u)
#define PIN_Y25_GPIO_PIN (22u)
#endif


/* Ball: Y26 */
#define PIN_CTRL_REG_ADDR_Y26 (0x48140AD0UL)
#ifndef PIN_FUNCTION_Y26_UART6
#define PIN_FUNCTION_Y26_UART6 (0x040UL)
#endif
#ifndef PIN_FUNCTION_Y26_DIO
#define PIN_FUNCTION_Y26_DIO (0x080UL)
#endif
#ifndef PIN_Y26_GPIO
#define PIN_Y26_GPIO (2u)
#define PIN_Y26_GPIO_PIN (23u)
#endif


/* Ball: AA28 */
#define PIN_CTRL_REG_ADDR_AA28 (0x48140AD4UL)
#ifndef PIN_FUNCTION_AA28_DIO
#define PIN_FUNCTION_AA28_DIO (0x080UL)
#endif
#ifndef PIN_AA28_GPIO
#define PIN_AA28_GPIO (4u)
#define PIN_AA28_GPIO_PIN (21u)
#endif


/* Ball: AA25 */
#define PIN_CTRL_REG_ADDR_AA25 (0x48140AD8UL)
#ifndef PIN_FUNCTION_AA25_DIO
#define PIN_FUNCTION_AA25_DIO (0x080UL)
#endif
#ifndef PIN_AA25_GPIO
#define PIN_AA25_GPIO (4u)
#define PIN_AA25_GPIO_PIN (22u)
#endif


/* Ball: AA27 */
#define PIN_CTRL_REG_ADDR_AA27 (0x48140ADCUL)
#ifndef PIN_FUNCTION_AA27_DIO
#define PIN_FUNCTION_AA27_DIO (0x080UL)
#endif
#ifndef PIN_AA27_GPIO
#define PIN_AA27_GPIO (4u)
#define PIN_AA27_GPIO_PIN (23u)
#endif


/* Ball: AA26 */
#define PIN_CTRL_REG_ADDR_AA26 (0x48140AE0UL)
#ifndef PIN_FUNCTION_AA26_DIO
#define PIN_FUNCTION_AA26_DIO (0x080UL)
#endif
#ifndef PIN_AA26_GPIO
#define PIN_AA26_GPIO (4u)
#define PIN_AA26_GPIO_PIN (24u)
#endif


/* Ball: AB28 */
#define PIN_CTRL_REG_ADDR_AB28 (0x48140AE4UL)
#ifndef PIN_FUNCTION_AB28_DIO
#define PIN_FUNCTION_AB28_DIO (0x080UL)
#endif
#ifndef PIN_AB28_GPIO
#define PIN_AB28_GPIO (4u)
#define PIN_AB28_GPIO_PIN (25u)
#endif


/* Ball: AB27 */
#define PIN_CTRL_REG_ADDR_AB27 (0x48140AE8UL)
#ifndef PIN_FUNCTION_AB27_DIO
#define PIN_FUNCTION_AB27_DIO (0x080UL)
#endif
#ifndef PIN_AB27_GPIO
#define PIN_AB27_GPIO (4u)
#define PIN_AB27_GPIO_PIN (26u)
#endif


/* Ball: W26 */
#define PIN_CTRL_REG_ADDR_W26 (0x48140ABCUL)


/* Ball: AB26 */
#define PIN_CTRL_REG_ADDR_AB26 (0x48140AECUL)
#ifndef PIN_FUNCTION_AB26_DIO
#define PIN_FUNCTION_AB26_DIO (0x080UL)
#endif
#ifndef PIN_AB26_GPIO
#define PIN_AB26_GPIO (2u)
#define PIN_AB26_GPIO_PIN (24u)
#endif


/* Ball: AB25 */
#define PIN_CTRL_REG_ADDR_AB25 (0x48140AF0UL)
#ifndef PIN_FUNCTION_AB25_UART6
#define PIN_FUNCTION_AB25_UART6 (0x040UL)
#endif
#ifndef PIN_FUNCTION_AB25_DIO
#define PIN_FUNCTION_AB25_DIO (0x080UL)
#endif
#ifndef PIN_AB25_GPIO
#define PIN_AB25_GPIO (2u)
#define PIN_AB25_GPIO_PIN (25u)
#endif


/* Ball: AC27 */
#define PIN_CTRL_REG_ADDR_AC27 (0x48140AF4UL)
#ifndef PIN_FUNCTION_AC27_DIO
#define PIN_FUNCTION_AC27_DIO (0x080UL)
#endif
#ifndef PIN_AC27_GPIO
#define PIN_AC27_GPIO (5u)
#define PIN_AC27_GPIO_PIN (10u)
#endif


/* Ball: AD26 */
#define PIN_CTRL_REG_ADDR_AD26 (0x48140AF8UL)
#ifndef PIN_FUNCTION_AD26_DIO
#define PIN_FUNCTION_AD26_DIO (0x080UL)
#endif
#ifndef PIN_AD26_GPIO
#define PIN_AD26_GPIO (5u)
#define PIN_AD26_GPIO_PIN (11u)
#endif


/* Ball: AC26 */
#define PIN_CTRL_REG_ADDR_AC26 (0x48140AFCUL)
#ifndef PIN_FUNCTION_AC26_DIO
#define PIN_FUNCTION_AC26_DIO (0x080UL)
#endif
#ifndef PIN_AC26_GPIO
#define PIN_AC26_GPIO (5u)
#define PIN_AC26_GPIO_PIN (12u)
#endif


/* Ball: AC25 */
#define PIN_CTRL_REG_ADDR_AC25 (0x48140B00UL)
#ifndef PIN_FUNCTION_AC25_DIO
#define PIN_FUNCTION_AC25_DIO (0x080UL)
#endif
#ifndef PIN_AC25_GPIO
#define PIN_AC25_GPIO (5u)
#define PIN_AC25_GPIO_PIN (13u)
#endif


/* Ball: AD28 */
#define PIN_CTRL_REG_ADDR_AD28 (0x48140B04UL)
#ifndef PIN_FUNCTION_AD28_DIO
#define PIN_FUNCTION_AD28_DIO (0x080UL)
#endif
#ifndef PIN_AD28_GPIO
#define PIN_AD28_GPIO (5u)
#define PIN_AD28_GPIO_PIN (14u)
#endif


/* Ball: AE28 */
#define PIN_CTRL_REG_ADDR_AE28 (0x48140B08UL)
#ifndef PIN_FUNCTION_AE28_DIO
#define PIN_FUNCTION_AE28_DIO (0x080UL)
#endif
#ifndef PIN_AE28_GPIO
#define PIN_AE28_GPIO (5u)
#define PIN_AE28_GPIO_PIN (15u)
#endif


/* Ball: W25 */
#define PIN_CTRL_REG_ADDR_W25 (0x48140AC0UL)
#ifndef PIN_FUNCTION_W25_DIO
#define PIN_FUNCTION_W25_DIO (0x080UL)
#endif
#ifndef PIN_W25_GPIO
#define PIN_W25_GPIO (4u)
#define PIN_W25_GPIO_PIN (19u)
#endif


/* Ball: H25 */
#define PIN_CTRL_REG_ADDR_H25 (0x48140A9CUL)
#ifndef PIN_FUNCTION_H25_UART4
#define PIN_FUNCTION_H25_UART4 (0x020UL)
#endif
#ifndef PIN_FUNCTION_H25_DIO
#define PIN_FUNCTION_H25_DIO (0x080UL)
#endif
#ifndef PIN_H25_GPIO
#define PIN_H25_GPIO (0u)
#define PIN_H25_GPIO_PIN (22u)
#endif


/* Ball: G25 */
#define PIN_CTRL_REG_ADDR_G25 (0x48140AA0UL)
#ifndef PIN_FUNCTION_G25_UART4
#define PIN_FUNCTION_G25_UART4 (0x020UL)
#endif
#ifndef PIN_FUNCTION_G25_DIO
#define PIN_FUNCTION_G25_DIO (0x080UL)
#endif
#ifndef PIN_G25_GPIO
#define PIN_G25_GPIO (0u)
#define PIN_G25_GPIO_PIN (23u)
#endif


/* Ball: AD27 */
#define PIN_CTRL_REG_ADDR_AD27 (0x48140B0CUL)
#ifndef PIN_FUNCTION_AD27_UART6
#define PIN_FUNCTION_AD27_UART6 (0x040UL)
#endif
#ifndef PIN_FUNCTION_AD27_DIO
#define PIN_FUNCTION_AD27_DIO (0x080UL)
#endif
#ifndef PIN_AD27_GPIO
#define PIN_AD27_GPIO (2u)
#define PIN_AD27_GPIO_PIN (26u)
#endif


/* Ball: AE27 */
#define PIN_CTRL_REG_ADDR_AE27 (0x48140B10UL)
#ifndef PIN_FUNCTION_AE27_UART6
#define PIN_FUNCTION_AE27_UART6 (0x040UL)
#endif
#ifndef PIN_FUNCTION_AE27_DIO
#define PIN_FUNCTION_AE27_DIO (0x080UL)
#endif
#ifndef PIN_AE27_GPIO
#define PIN_AE27_GPIO (2u)
#define PIN_AE27_GPIO_PIN (27u)
#endif


/* Ball: AE26 */
#define PIN_CTRL_REG_ADDR_AE26 (0x48140B14UL)
#ifndef PIN_FUNCTION_AE26_DIO
#define PIN_FUNCTION_AE26_DIO (0x080UL)
#endif
#ifndef PIN_AE26_GPIO
#define PIN_AE26_GPIO (4u)
#define PIN_AE26_GPIO_PIN (27u)
#endif


/* Ball: AD25 */
#define PIN_CTRL_REG_ADDR_AD25 (0x48140B18UL)
#ifndef PIN_FUNCTION_AD25_DIO
#define PIN_FUNCTION_AD25_DIO (0x080UL)
#endif
#ifndef PIN_AD25_GPIO
#define PIN_AD25_GPIO (4u)
#define PIN_AD25_GPIO_PIN (28u)
#endif


/* Ball: AF28 */
#define PIN_CTRL_REG_ADDR_AF28 (0x48140B1CUL)
#ifndef PIN_FUNCTION_AF28_DIO
#define PIN_FUNCTION_AF28_DIO (0x080UL)
#endif
#ifndef PIN_AF28_GPIO
#define PIN_AF28_GPIO (4u)
#define PIN_AF28_GPIO_PIN (29u)
#endif


/* Ball: AG27 */
#define PIN_CTRL_REG_ADDR_AG27 (0x48140B20UL)
#ifndef PIN_FUNCTION_AG27_DIO
#define PIN_FUNCTION_AG27_DIO (0x080UL)
#endif
#ifndef PIN_AG27_GPIO
#define PIN_AG27_GPIO (4u)
#define PIN_AG27_GPIO_PIN (30u)
#endif


/* Ball: AF27 */
#define PIN_CTRL_REG_ADDR_AF27 (0x48140B24UL)
#ifndef PIN_FUNCTION_AF27_DIO
#define PIN_FUNCTION_AF27_DIO (0x080UL)
#endif
#ifndef PIN_AF27_GPIO
#define PIN_AF27_GPIO (4u)
#define PIN_AF27_GPIO_PIN (31u)
#endif


/* Ball: AG28 */
#define PIN_CTRL_REG_ADDR_AG28 (0x48140B28UL)
#ifndef PIN_FUNCTION_AG28_DIO
#define PIN_FUNCTION_AG28_DIO (0x080UL)
#endif
#ifndef PIN_AG28_GPIO
#define PIN_AG28_GPIO (5u)
#define PIN_AG28_GPIO_PIN (5u)
#endif


/* Ball: Y28 */
#define PIN_CTRL_REG_ADDR_Y28 (0x48140AC4UL)
#ifndef PIN_FUNCTION_Y28_DIO
#define PIN_FUNCTION_Y28_DIO (0x080UL)
#endif
#ifndef PIN_Y28_GPIO
#define PIN_Y28_GPIO (4u)
#define PIN_Y28_GPIO_PIN (20u)
#endif


/* Ball: G27 */
#define PIN_CTRL_REG_ADDR_G27 (0x48140B38UL)
#ifndef PIN_FUNCTION_G27_UART4
#define PIN_FUNCTION_G27_UART4 (0x020UL)
#endif
#ifndef PIN_FUNCTION_G27_PWM
#define PIN_FUNCTION_G27_PWM (0x040UL)
#endif
#ifndef PIN_FUNCTION_G27_ICU
#define PIN_FUNCTION_G27_ICU (0x040UL)
#endif
#ifndef PIN_FUNCTION_G27_DIO
#define PIN_FUNCTION_G27_DIO (0x080UL)
#endif
#ifndef PIN_G27_GPIO
#define PIN_G27_GPIO (2u)
#define PIN_G27_GPIO_PIN (31u)
#endif


/* Ball: B24 */
#define PIN_CTRL_REG_ADDR_B24 (0x48140B98UL)
#ifndef PIN_FUNCTION_B24_SPI2
#define PIN_FUNCTION_B24_SPI2 (0x020UL)
#endif
#ifndef PIN_FUNCTION_B24_DIO
#define PIN_FUNCTION_B24_DIO (0x080UL)
#endif
#ifndef PIN_B24_GPIO
#define PIN_B24_GPIO (3u)
#define PIN_B24_GPIO_PIN (30u)
#endif


/* Ball: F27 */
#define PIN_CTRL_REG_ADDR_F27 (0x48140B3CUL)
#ifndef PIN_FUNCTION_F27_UART4
#define PIN_FUNCTION_F27_UART4 (0x020UL)
#endif
#ifndef PIN_FUNCTION_F27_DIO
#define PIN_FUNCTION_F27_DIO (0x080UL)
#endif
#ifndef PIN_F27_GPIO
#define PIN_F27_GPIO (3u)
#define PIN_F27_GPIO_PIN (0u)
#endif


/* Ball: F28 */
#define PIN_CTRL_REG_ADDR_F28 (0x48140B40UL)
#ifndef PIN_FUNCTION_F28_UART4
#define PIN_FUNCTION_F28_UART4 (0x020UL)
#endif
#ifndef PIN_FUNCTION_F28_DIO
#define PIN_FUNCTION_F28_DIO (0x080UL)
#endif
#ifndef PIN_F28_GPIO
#define PIN_F28_GPIO (3u)
#define PIN_F28_GPIO_PIN (1u)
#endif


/* Ball: E24 */
#define PIN_CTRL_REG_ADDR_E24 (0x48140B44UL)
#ifndef PIN_FUNCTION_E24_UART4
#define PIN_FUNCTION_E24_UART4 (0x020UL)
#endif
#ifndef PIN_FUNCTION_E24_DIO
#define PIN_FUNCTION_E24_DIO (0x080UL)
#endif
#ifndef PIN_E24_GPIO
#define PIN_E24_GPIO (3u)
#define PIN_E24_GPIO_PIN (2u)
#endif


/* Ball: E26 */
#define PIN_CTRL_REG_ADDR_E26 (0x48140B48UL)
#ifndef PIN_FUNCTION_E26_UART3
#define PIN_FUNCTION_E26_UART3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_E26_DIO
#define PIN_FUNCTION_E26_DIO (0x080UL)
#endif
#ifndef PIN_E26_GPIO
#define PIN_E26_GPIO (3u)
#define PIN_E26_GPIO_PIN (3u)
#endif


/* Ball: E27 */
#define PIN_CTRL_REG_ADDR_E27 (0x48140B4CUL)
#ifndef PIN_FUNCTION_E27_UART3
#define PIN_FUNCTION_E27_UART3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_E27_DIO
#define PIN_FUNCTION_E27_DIO (0x080UL)
#endif
#ifndef PIN_E27_GPIO
#define PIN_E27_GPIO (3u)
#define PIN_E27_GPIO_PIN (4u)
#endif


/* Ball: E28 */
#define PIN_CTRL_REG_ADDR_E28 (0x48140B50UL)
#ifndef PIN_FUNCTION_E28_I2C3
#define PIN_FUNCTION_E28_I2C3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_E28_DIO
#define PIN_FUNCTION_E28_DIO (0x080UL)
#endif
#ifndef PIN_E28_GPIO
#define PIN_E28_GPIO (3u)
#define PIN_E28_GPIO_PIN (5u)
#endif


/* Ball: D24 */
#define PIN_CTRL_REG_ADDR_D24 (0x48140B54UL)
#ifndef PIN_FUNCTION_D24_I2C3
#define PIN_FUNCTION_D24_I2C3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_D24_DIO
#define PIN_FUNCTION_D24_DIO (0x080UL)
#endif
#ifndef PIN_D24_GPIO
#define PIN_D24_GPIO (3u)
#define PIN_D24_GPIO_PIN (6u)
#endif


/* Ball: G26 */
#define PIN_CTRL_REG_ADDR_G26 (0x48140B2CUL)
#ifndef PIN_FUNCTION_G26_DIO
#define PIN_FUNCTION_G26_DIO (0x080UL)
#endif
#ifndef PIN_G26_GPIO
#define PIN_G26_GPIO (2u)
#define PIN_G26_GPIO_PIN (28u)
#endif


/* Ball: B28 */
#define PIN_CTRL_REG_ADDR_B28 (0x48140B8CUL)
#ifndef PIN_FUNCTION_B28_SPI2
#define PIN_FUNCTION_B28_SPI2 (0x020UL)
#endif
#ifndef PIN_FUNCTION_B28_I2C2
#define PIN_FUNCTION_B28_I2C2 (0x040UL)
#endif
#ifndef PIN_FUNCTION_B28_DIO
#define PIN_FUNCTION_B28_DIO (0x080UL)
#endif
#ifndef PIN_B28_GPIO
#define PIN_B28_GPIO (3u)
#define PIN_B28_GPIO_PIN (20u)
#endif


/* Ball: D25 */
#define PIN_CTRL_REG_ADDR_D25 (0x48140B58UL)
#ifndef PIN_FUNCTION_D25_DIO
#define PIN_FUNCTION_D25_DIO (0x080UL)
#endif
#ifndef PIN_D25_GPIO
#define PIN_D25_GPIO (3u)
#define PIN_D25_GPIO_PIN (7u)
#endif


/* Ball: D26 */
#define PIN_CTRL_REG_ADDR_D26 (0x48140B5CUL)
#ifndef PIN_FUNCTION_D26_DIO
#define PIN_FUNCTION_D26_DIO (0x080UL)
#endif
#ifndef PIN_D26_GPIO
#define PIN_D26_GPIO (3u)
#define PIN_D26_GPIO_PIN (8u)
#endif
#ifndef PIN_FUNCTION_D26_UART2
#define PIN_FUNCTION_D26_UART2 (0x400UL)
#endif


/* Ball: D27 */
#define PIN_CTRL_REG_ADDR_D27 (0x48140B60UL)
#ifndef PIN_FUNCTION_D27_DIO
#define PIN_FUNCTION_D27_DIO (0x080UL)
#endif
#ifndef PIN_D27_GPIO
#define PIN_D27_GPIO (3u)
#define PIN_D27_GPIO_PIN (9u)
#endif
#ifndef PIN_FUNCTION_D27_UART2
#define PIN_FUNCTION_D27_UART2 (0x400UL)
#endif


/* Ball: D28 */
#define PIN_CTRL_REG_ADDR_D28 (0x48140B64UL)
#ifndef PIN_FUNCTION_D28_DIO
#define PIN_FUNCTION_D28_DIO (0x080UL)
#endif
#ifndef PIN_D28_GPIO
#define PIN_D28_GPIO (3u)
#define PIN_D28_GPIO_PIN (10u)
#endif
#ifndef PIN_FUNCTION_D28_UART7
#define PIN_FUNCTION_D28_UART7 (0x400UL)
#endif


/* Ball: C25 */
#define PIN_CTRL_REG_ADDR_C25 (0x48140B68UL)
#ifndef PIN_FUNCTION_C25_DIO
#define PIN_FUNCTION_C25_DIO (0x080UL)
#endif
#ifndef PIN_C25_GPIO
#define PIN_C25_GPIO (3u)
#define PIN_C25_GPIO_PIN (11u)
#endif
#ifndef PIN_FUNCTION_C25_UART7
#define PIN_FUNCTION_C25_UART7 (0x400UL)
#endif


/* Ball: C26 */
#define PIN_CTRL_REG_ADDR_C26 (0x48140B6CUL)
#ifndef PIN_FUNCTION_C26_DIO
#define PIN_FUNCTION_C26_DIO (0x080UL)
#endif
#ifndef PIN_C26_GPIO
#define PIN_C26_GPIO (3u)
#define PIN_C26_GPIO_PIN (12u)
#endif
#ifndef PIN_FUNCTION_C26_UART7
#define PIN_FUNCTION_C26_UART7 (0x400UL)
#endif


/* Ball: C27 */
#define PIN_CTRL_REG_ADDR_C27 (0x48140B70UL)
#ifndef PIN_FUNCTION_C27_DIO
#define PIN_FUNCTION_C27_DIO (0x080UL)
#endif
#ifndef PIN_C27_GPIO
#define PIN_C27_GPIO (3u)
#define PIN_C27_GPIO_PIN (13u)
#endif
#ifndef PIN_FUNCTION_C27_UART7
#define PIN_FUNCTION_C27_UART7 (0x400UL)
#endif


/* Ball: F25 */
#define PIN_CTRL_REG_ADDR_F25 (0x48140B30UL)
#ifndef PIN_FUNCTION_F25_SPI3
#define PIN_FUNCTION_F25_SPI3 (0x010UL)
#endif
#ifndef PIN_FUNCTION_F25_UART3
#define PIN_FUNCTION_F25_UART3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_F25_DIO
#define PIN_FUNCTION_F25_DIO (0x080UL)
#endif
#ifndef PIN_F25_GPIO
#define PIN_F25_GPIO (2u)
#define PIN_F25_GPIO_PIN (29u)
#endif


/* Ball: A25 */
#define PIN_CTRL_REG_ADDR_A25 (0x48140B94UL)
#ifndef PIN_FUNCTION_A25_SPI2
#define PIN_FUNCTION_A25_SPI2 (0x020UL)
#endif
#ifndef PIN_FUNCTION_A25_DIO
#define PIN_FUNCTION_A25_DIO (0x080UL)
#endif
#ifndef PIN_A25_GPIO
#define PIN_A25_GPIO (3u)
#define PIN_A25_GPIO_PIN (22u)
#endif


/* Ball: A27 */
#define PIN_CTRL_REG_ADDR_A27 (0x48140B90UL)
#ifndef PIN_FUNCTION_A27_SPI2
#define PIN_FUNCTION_A27_SPI2 (0x020UL)
#endif
#ifndef PIN_FUNCTION_A27_I2C2
#define PIN_FUNCTION_A27_I2C2 (0x040UL)
#endif
#ifndef PIN_FUNCTION_A27_DIO
#define PIN_FUNCTION_A27_DIO (0x080UL)
#endif
#ifndef PIN_A27_GPIO
#define PIN_A27_GPIO (3u)
#define PIN_A27_GPIO_PIN (21u)
#endif


/* Ball: A26 */
#define PIN_CTRL_REG_ADDR_A26 (0x48140B74UL)
#ifndef PIN_FUNCTION_A26_SPI3
#define PIN_FUNCTION_A26_SPI3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_A26_DIO
#define PIN_FUNCTION_A26_DIO (0x080UL)
#endif
#ifndef PIN_A26_GPIO
#define PIN_A26_GPIO (3u)
#define PIN_A26_GPIO_PIN (14u)
#endif


/* Ball: C28 */
#define PIN_CTRL_REG_ADDR_C28 (0x48140B78UL)
#ifndef PIN_FUNCTION_C28_SPI3
#define PIN_FUNCTION_C28_SPI3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_C28_DIO
#define PIN_FUNCTION_C28_DIO (0x080UL)
#endif
#ifndef PIN_C28_GPIO
#define PIN_C28_GPIO (3u)
#define PIN_C28_GPIO_PIN (15u)
#endif


/* Ball: B25 */
#define PIN_CTRL_REG_ADDR_B25 (0x48140B7CUL)
#ifndef PIN_FUNCTION_B25_SPI3
#define PIN_FUNCTION_B25_SPI3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_B25_DIO
#define PIN_FUNCTION_B25_DIO (0x080UL)
#endif
#ifndef PIN_B25_GPIO
#define PIN_B25_GPIO (3u)
#define PIN_B25_GPIO_PIN (16u)
#endif


/* Ball: B26 */
#define PIN_CTRL_REG_ADDR_B26 (0x48140B80UL)
#ifndef PIN_FUNCTION_B26_SPI3
#define PIN_FUNCTION_B26_SPI3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_B26_DIO
#define PIN_FUNCTION_B26_DIO (0x080UL)
#endif
#ifndef PIN_B26_GPIO
#define PIN_B26_GPIO (3u)
#define PIN_B26_GPIO_PIN (17u)
#endif
#ifndef PIN_FUNCTION_B26_PWM
#define PIN_FUNCTION_B26_PWM (0x400UL)
#endif
#ifndef PIN_FUNCTION_B26_ICU
#define PIN_FUNCTION_B26_ICU (0x400UL)
#endif


/* Ball: B27 */
#define PIN_CTRL_REG_ADDR_B27 (0x48140B84UL)
#ifndef PIN_FUNCTION_B27_UART5
#define PIN_FUNCTION_B27_UART5 (0x020UL)
#endif
#ifndef PIN_FUNCTION_B27_DIO
#define PIN_FUNCTION_B27_DIO (0x080UL)
#endif
#ifndef PIN_B27_GPIO
#define PIN_B27_GPIO (3u)
#define PIN_B27_GPIO_PIN (18u)
#endif
#ifndef PIN_FUNCTION_B27_PWM
#define PIN_FUNCTION_B27_PWM (0x400UL)
#endif
#ifndef PIN_FUNCTION_B27_ICU
#define PIN_FUNCTION_B27_ICU (0x400UL)
#endif


/* Ball: C24 */
#define PIN_CTRL_REG_ADDR_C24 (0x48140B88UL)
#ifndef PIN_FUNCTION_C24_UART5
#define PIN_FUNCTION_C24_UART5 (0x020UL)
#endif
#ifndef PIN_FUNCTION_C24_DIO
#define PIN_FUNCTION_C24_DIO (0x080UL)
#endif
#ifndef PIN_C24_GPIO
#define PIN_C24_GPIO (3u)
#define PIN_C24_GPIO_PIN (19u)
#endif


/* Ball: F26 */
#define PIN_CTRL_REG_ADDR_F26 (0x48140B34UL)
#ifndef PIN_FUNCTION_F26_SPI3
#define PIN_FUNCTION_F26_SPI3 (0x010UL)
#endif
#ifndef PIN_FUNCTION_F26_UART3
#define PIN_FUNCTION_F26_UART3 (0x020UL)
#endif
#ifndef PIN_FUNCTION_F26_DIO
#define PIN_FUNCTION_F26_DIO (0x080UL)
#endif
#ifndef PIN_F26_GPIO
#define PIN_F26_GPIO (2u)
#define PIN_F26_GPIO_PIN (30u)
#endif


#endif /* JACINTO5E_PORTDEFS_H_ */
