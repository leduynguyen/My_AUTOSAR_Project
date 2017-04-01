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

#ifndef JACINTO6_PORTDEFS_H_
#define JACINTO6_PORTDEFS_H_

/* Addresses for pad register */
#define SYSCFG_PAD_GPMC_AD0         (0x4A003400)
#define SYSCFG_PAD_GPMC_AD1         (0x4A003404)
#define SYSCFG_PAD_GPMC_AD2         (0x4A003408)
#define SYSCFG_PAD_GPMC_AD3         (0x4A00340C)
#define SYSCFG_PAD_GPMC_AD4         (0x4A003410)
#define SYSCFG_PAD_GPMC_AD5         (0x4A003414)
#define SYSCFG_PAD_GPMC_AD6         (0x4A003418)
#define SYSCFG_PAD_GPMC_AD7         (0x4A00341C)
#define SYSCFG_PAD_GPMC_AD8         (0x4A003420)
#define SYSCFG_PAD_GPMC_AD9         (0x4A003424)
#define SYSCFG_PAD_GPMC_AD10        (0x4A003428)
#define SYSCFG_PAD_GPMC_AD11        (0x4A00342C)
#define SYSCFG_PAD_GPMC_AD12        (0x4A003430)
#define SYSCFG_PAD_GPMC_AD13        (0x4A003434)
#define SYSCFG_PAD_GPMC_AD14        (0x4A003438)
#define SYSCFG_PAD_GPMC_AD15        (0x4A00343C)
#define SYSCFG_PAD_GPMC_A0          (0x4A003440)
#define SYSCFG_PAD_GPMC_A1          (0x4A003444)
#define SYSCFG_PAD_GPMC_A2          (0x4A003448)
#define SYSCFG_PAD_GPMC_A3          (0x4A00344C)
#define SYSCFG_PAD_GPMC_A4          (0x4A003450)
#define SYSCFG_PAD_GPMC_A5          (0x4A003454)
#define SYSCFG_PAD_GPMC_A6          (0x4A003458)
#define SYSCFG_PAD_GPMC_A7          (0x4A00345C)
#define SYSCFG_PAD_GPMC_A8          (0x4A003460)
#define SYSCFG_PAD_GPMC_A9          (0x4A003464)
#define SYSCFG_PAD_GPMC_A10         (0x4A003468)
#define SYSCFG_PAD_GPMC_A11         (0x4A00346C)
#define SYSCFG_PAD_GPMC_A12         (0x4A003470)
#define SYSCFG_PAD_GPMC_A13         (0x4A003474)
#define SYSCFG_PAD_GPMC_A14         (0x4A003478)
#define SYSCFG_PAD_GPMC_A15         (0x4A00347C)
#define SYSCFG_PAD_GPMC_A16         (0x4A003480)
#define SYSCFG_PAD_GPMC_A17         (0x4A003484)
#define SYSCFG_PAD_GPMC_A18         (0x4A003488)
#define SYSCFG_PAD_GPMC_A19         (0x4A00348C)
#define SYSCFG_PAD_GPMC_A20         (0x4A003490)
#define SYSCFG_PAD_GPMC_A21         (0x4A003494)
#define SYSCFG_PAD_GPMC_A22         (0x4A003498)
#define SYSCFG_PAD_GPMC_A23         (0x4A00349C)
#define SYSCFG_PAD_GPMC_A24         (0x4A0034A0)
#define SYSCFG_PAD_GPMC_A25         (0x4A0034A4)
#define SYSCFG_PAD_GPMC_A26         (0x4A0034A8)
#define SYSCFG_PAD_GPMC_A27         (0x4A0034AC)
#define SYSCFG_PAD_GPMC_CS1         (0x4A0034B0)
#define SYSCFG_PAD_GPMC_CS0         (0x4A0034B4)
#define SYSCFG_PAD_GPMC_CS2         (0x4A0034B8)
#define SYSCFG_PAD_GPMC_CS3         (0x4A0034BC)
#define SYSCFG_PAD_GPMC_CLK         (0x4A0034C0)
#define SYSCFG_PAD_GPMC_ADVN_ALE    (0x4A0034C4)
#define SYSCFG_PAD_GPMC_OEN_REN     (0x4A0034C8)
#define SYSCFG_PAD_GPMC_WEN         (0x4A0034CC)
#define SYSCFG_PAD_GPMC_BEN0        (0x4A0034D0)
#define SYSCFG_PAD_GPMC_BEN1        (0x4A0034D4)
#define SYSCFG_PAD_GPMC_WAIT0       (0x4A0034D8)
#define SYSCFG_PAD_VIN1A_CLK0       (0x4A0034DC)
#define SYSCFG_PAD_VIN1B_CLK1       (0x4A0034E0)
#define SYSCFG_PAD_VIN1A_DE0        (0x4A0034E4)
#define SYSCFG_PAD_VIN1A_FLD0       (0x4A0034E8)
#define SYSCFG_PAD_VIN1A_HSYNC0     (0x4A0034EC)
#define SYSCFG_PAD_VIN1A_VSYNC0     (0x4A0034F0)
#define SYSCFG_PAD_VIN1A_D0         (0x4A0034F4)
#define SYSCFG_PAD_VIN1A_D1         (0x4A0034F8)
#define SYSCFG_PAD_VIN1A_D2         (0x4A0034FC)
#define SYSCFG_PAD_VIN1A_D3         (0x4A003500)
#define SYSCFG_PAD_VIN1A_D4         (0x4A003504)
#define SYSCFG_PAD_VIN1A_D5         (0x4A003508)
#define SYSCFG_PAD_VIN1A_D6         (0x4A00350C)
#define SYSCFG_PAD_VIN1A_D7         (0x4A003510)
#define SYSCFG_PAD_VIN1A_D8         (0x4A003514)
#define SYSCFG_PAD_VIN1A_D9         (0x4A003518)
#define SYSCFG_PAD_VIN1A_D10        (0x4A00351C)
#define SYSCFG_PAD_VIN1A_D11        (0x4A003520)
#define SYSCFG_PAD_VIN1A_D12        (0x4A003524)
#define SYSCFG_PAD_VIN1A_D13        (0x4A003528)
#define SYSCFG_PAD_VIN1A_D14        (0x4A00352C)
#define SYSCFG_PAD_VIN1A_D15        (0x4A003530)
#define SYSCFG_PAD_VIN1A_D16        (0x4A003534)
#define SYSCFG_PAD_VIN1A_D17        (0x4A003538)
#define SYSCFG_PAD_VIN1A_D18        (0x4A00353C)
#define SYSCFG_PAD_VIN1A_D19        (0x4A003540)
#define SYSCFG_PAD_VIN1A_D20        (0x4A003544)
#define SYSCFG_PAD_VIN1A_D21        (0x4A003548)
#define SYSCFG_PAD_VIN1A_D22        (0x4A00354C)
#define SYSCFG_PAD_VIN1A_D23        (0x4A003550)
#define SYSCFG_PAD_VIN2A_CLK0       (0x4A003554)
#define SYSCFG_PAD_VIN2A_DE0        (0x4A003558)
#define SYSCFG_PAD_VIN2A_FLD0       (0x4A00355C)
#define SYSCFG_PAD_VIN2A_HSYNC0     (0x4A003560)
#define SYSCFG_PAD_VIN2A_VSYNC0     (0x4A003564)
#define SYSCFG_PAD_VIN2A_D0         (0x4A003568)
#define SYSCFG_PAD_VIN2A_D1         (0x4A00356C)
#define SYSCFG_PAD_VIN2A_D2         (0x4A003570)
#define SYSCFG_PAD_VIN2A_D3         (0x4A003574)
#define SYSCFG_PAD_VIN2A_D4         (0x4A003578)
#define SYSCFG_PAD_VIN2A_D5         (0x4A00357C)
#define SYSCFG_PAD_VIN2A_D6         (0x4A003580)
#define SYSCFG_PAD_VIN2A_D7         (0x4A003584)
#define SYSCFG_PAD_VIN2A_D8         (0x4A003588)
#define SYSCFG_PAD_VIN2A_D9         (0x4A00358C)
#define SYSCFG_PAD_VIN2A_D10        (0x4A003590)
#define SYSCFG_PAD_VIN2A_D11        (0x4A003594)
#define SYSCFG_PAD_VIN2A_D12        (0x4A003598)
#define SYSCFG_PAD_VIN2A_D13        (0x4A00359C)
#define SYSCFG_PAD_VIN2A_D14        (0x4A0035A0)
#define SYSCFG_PAD_VIN2A_D15        (0x4A0035A4)
#define SYSCFG_PAD_VIN2A_D16        (0x4A0035A8)
#define SYSCFG_PAD_VIN2A_D17        (0x4A0035AC)
#define SYSCFG_PAD_VIN2A_D18        (0x4A0035B0)
#define SYSCFG_PAD_VIN2A_D19        (0x4A0035B4)
#define SYSCFG_PAD_VIN2A_D20        (0x4A0035B8)
#define SYSCFG_PAD_VIN2A_D21        (0x4A0035BC)
#define SYSCFG_PAD_VIN2A_D22        (0x4A0035C0)
#define SYSCFG_PAD_VIN2A_D23        (0x4A0035C4)
#define SYSCFG_PAD_VOUT1_CLK        (0x4A0035C8)
#define SYSCFG_PAD_VOUT1_DE         (0x4A0035CC)
#define SYSCFG_PAD_VOUT1_FLD        (0x4A0035D0)
#define SYSCFG_PAD_VOUT1_HSYNC      (0x4A0035D4)
#define SYSCFG_PAD_VOUT1_VSYNC      (0x4A0035D8)
#define SYSCFG_PAD_VOUT1_D0         (0x4A0035DC)
#define SYSCFG_PAD_VOUT1_D1         (0x4A0035E0)
#define SYSCFG_PAD_VOUT1_D2         (0x4A0035E4)
#define SYSCFG_PAD_VOUT1_D3         (0x4A0035E8)
#define SYSCFG_PAD_VOUT1_D4         (0x4A0035EC)
#define SYSCFG_PAD_VOUT1_D5         (0x4A0035F0)
#define SYSCFG_PAD_VOUT1_D6         (0x4A0035F4)
#define SYSCFG_PAD_VOUT1_D7         (0x4A0035F8)
#define SYSCFG_PAD_VOUT1_D8         (0x4A0035FC)
#define SYSCFG_PAD_VOUT1_D9         (0x4A003600)
#define SYSCFG_PAD_VOUT1_D10        (0x4A003604)
#define SYSCFG_PAD_VOUT1_D11        (0x4A003608)
#define SYSCFG_PAD_VOUT1_D12        (0x4A00360C)
#define SYSCFG_PAD_VOUT1_D13        (0x4A003610)
#define SYSCFG_PAD_VOUT1_D14        (0x4A003614)
#define SYSCFG_PAD_VOUT1_D15        (0x4A003618)
#define SYSCFG_PAD_VOUT1_D16        (0x4A00361C)
#define SYSCFG_PAD_VOUT1_D17        (0x4A003620)
#define SYSCFG_PAD_VOUT1_D18        (0x4A003624)
#define SYSCFG_PAD_VOUT1_D19        (0x4A003628)
#define SYSCFG_PAD_VOUT1_D20        (0x4A00362C)
#define SYSCFG_PAD_VOUT1_D21        (0x4A003630)
#define SYSCFG_PAD_VOUT1_D22        (0x4A003634)
#define SYSCFG_PAD_VOUT1_D23        (0x4A003638)
#define SYSCFG_PAD_MDIO_MCLK        (0x4A00363C)
#define SYSCFG_PAD_MDIO_D           (0x4A003640)
#define SYSCFG_PAD_RMII_MHZ_50_CLK  (0x4A003644)
#define SYSCFG_PAD_UART3_RXD        (0x4A003648)
#define SYSCFG_PAD_UART3_TXD        (0x4A00364C)
#define SYSCFG_PAD_RGMII0_TXC       (0x4A003650)
#define SYSCFG_PAD_RGMII0_TXCTL     (0x4A003654)
#define SYSCFG_PAD_RGMII0_TXD3      (0x4A003658)
#define SYSCFG_PAD_RGMII0_TXD2      (0x4A00365C)
#define SYSCFG_PAD_RGMII0_TXD1      (0x4A003660)
#define SYSCFG_PAD_RGMII0_TXD0      (0x4A003664)
#define SYSCFG_PAD_RGMII0_RXC       (0x4A003668)
#define SYSCFG_PAD_RGMII0_RXCTL     (0x4A00366C)
#define SYSCFG_PAD_RGMII0_RXD3      (0x4A003670)
#define SYSCFG_PAD_RGMII0_RXD2      (0x4A003674)
#define SYSCFG_PAD_RGMII0_RXD1      (0x4A003678)
#define SYSCFG_PAD_RGMII0_RXD0      (0x4A00367C)
#define SYSCFG_PAD_USB1_DRVVBUS     (0x4A003680)
#define SYSCFG_PAD_USB2_DRVVBUS     (0x4A003684)
#define SYSCFG_PAD_GPIO6_14         (0x4A003688)
#define SYSCFG_PAD_GPIO6_15         (0x4A00368C)
#define SYSCFG_PAD_GPIO6_16         (0x4A003690)
#define SYSCFG_PAD_XREF_CLK0        (0x4A003694)
#define SYSCFG_PAD_XREF_CLK1        (0x4A003698)
#define SYSCFG_PAD_XREF_CLK2        (0x4A00369C)
#define SYSCFG_PAD_XREF_CLK3        (0x4A0036A0)
#define SYSCFG_PAD_MCASP1_ACLKX     (0x4A0036A4)
#define SYSCFG_PAD_MCASP1_FSX       (0x4A0036A8)
#define SYSCFG_PAD_MCASP1_ACLKR     (0x4A0036AC)
#define SYSCFG_PAD_MCASP1_FSR       (0x4A0036B0)
#define SYSCFG_PAD_MCASP1_AXR0      (0x4A0036B4)
#define SYSCFG_PAD_MCASP1_AXR1      (0x4A0036B8)
#define SYSCFG_PAD_MCASP1_AXR2      (0x4A0036BC)
#define SYSCFG_PAD_MCASP1_AXR3      (0x4A0036C0)
#define SYSCFG_PAD_MCASP1_AXR4      (0x4A0036C4)
#define SYSCFG_PAD_MCASP1_AXR5      (0x4A0036C8)
#define SYSCFG_PAD_MCASP1_AXR6      (0x4A0036CC)
#define SYSCFG_PAD_MCASP1_AXR7      (0x4A0036D0)
#define SYSCFG_PAD_MCASP1_AXR8      (0x4A0036D4)
#define SYSCFG_PAD_MCASP1_AXR9      (0x4A0036D8)
#define SYSCFG_PAD_MCASP1_AXR10     (0x4A0036DC)
#define SYSCFG_PAD_MCASP1_AXR11     (0x4A0036E0)
#define SYSCFG_PAD_MCASP1_AXR12     (0x4A0036E4)
#define SYSCFG_PAD_MCASP1_AXR13     (0x4A0036E8)
#define SYSCFG_PAD_MCASP1_AXR14     (0x4A0036EC)
#define SYSCFG_PAD_MCASP1_AXR15     (0x4A0036F0)
#define SYSCFG_PAD_MCASP2_ACLKX     (0x4A0036F4)
#define SYSCFG_PAD_MCASP2_FSX       (0x4A0036F8)
#define SYSCFG_PAD_MCASP2_ACLKR     (0x4A0036FC)
#define SYSCFG_PAD_MCASP2_FSR       (0x4A003700)
#define SYSCFG_PAD_MCASP2_AXR0      (0x4A003704)
#define SYSCFG_PAD_MCASP2_AXR1      (0x4A003708)
#define SYSCFG_PAD_MCASP2_AXR2      (0x4A00370C)
#define SYSCFG_PAD_MCASP2_AXR3      (0x4A003710)
#define SYSCFG_PAD_MCASP2_AXR4      (0x4A003714)
#define SYSCFG_PAD_MCASP2_AXR5      (0x4A003718)
#define SYSCFG_PAD_MCASP2_AXR6      (0x4A00371C)
#define SYSCFG_PAD_MCASP2_AXR7      (0x4A003720)
#define SYSCFG_PAD_MCASP3_ACLKX     (0x4A003724)
#define SYSCFG_PAD_MCASP3_FSX       (0x4A003728)
#define SYSCFG_PAD_MCASP3_AXR0      (0x4A00372C)
#define SYSCFG_PAD_MCASP3_AXR1      (0x4A003730)
#define SYSCFG_PAD_MCASP4_ACLKX     (0x4A003734)
#define SYSCFG_PAD_MCASP4_FSX       (0x4A003738)
#define SYSCFG_PAD_MCASP4_AXR0      (0x4A00373C)
#define SYSCFG_PAD_MCASP4_AXR1      (0x4A003740)
#define SYSCFG_PAD_MCASP5_ACLKX     (0x4A003744)
#define SYSCFG_PAD_MCASP5_FSX       (0x4A003748)
#define SYSCFG_PAD_MCASP5_AXR0      (0x4A00374C)
#define SYSCFG_PAD_MCASP5_AXR1      (0x4A003750)
#define SYSCFG_PAD_MMC1_CLK         (0x4A003754)
#define SYSCFG_PAD_MMC1_CMD         (0x4A003758)
#define SYSCFG_PAD_MMC1_DAT0        (0x4A00375C)
#define SYSCFG_PAD_MMC1_DAT1        (0x4A003760)
#define SYSCFG_PAD_MMC1_DAT2        (0x4A003764)
#define SYSCFG_PAD_MMC1_DAT3        (0x4A003768)
#define SYSCFG_PAD_MMC1_SDCD        (0x4A00376C)
#define SYSCFG_PAD_MMC1_SDWP        (0x4A003770)
#define SYSCFG_PAD_GPIO6_10         (0x4A003774)
#define SYSCFG_PAD_GPIO6_11         (0x4A003778)
#define SYSCFG_PAD_MMC3_CLK         (0x4A00377C)
#define SYSCFG_PAD_MMC3_CMD         (0x4A003780)
#define SYSCFG_PAD_MMC3_DAT0        (0x4A003784)
#define SYSCFG_PAD_MMC3_DAT1        (0x4A003788)
#define SYSCFG_PAD_MMC3_DAT2        (0x4A00378C)
#define SYSCFG_PAD_MMC3_DAT3        (0x4A003790)
#define SYSCFG_PAD_MMC3_DAT4        (0x4A003794)
#define SYSCFG_PAD_MMC3_DAT5        (0x4A003798)
#define SYSCFG_PAD_MMC3_DAT6        (0x4A00379C)
#define SYSCFG_PAD_MMC3_DAT7        (0x4A0037A0)
#define SYSCFG_PAD_SPI1_SCLK        (0x4A0037A4)
#define SYSCFG_PAD_SPI1_D1          (0x4A0037A8)
#define SYSCFG_PAD_SPI1_D0          (0x4A0037AC)
#define SYSCFG_PAD_SPI1_CS0         (0x4A0037B0)
#define SYSCFG_PAD_SPI1_CS1         (0x4A0037B4)
#define SYSCFG_PAD_SPI1_CS2         (0x4A0037B8)
#define SYSCFG_PAD_SPI1_CS3         (0x4A0037BC)
#define SYSCFG_PAD_SPI2_SCLK        (0x4A0037C0)
#define SYSCFG_PAD_SPI2_D1          (0x4A0037C4)
#define SYSCFG_PAD_SPI2_D0          (0x4A0037C8)
#define SYSCFG_PAD_SPI2_CS0         (0x4A0037CC)
#define SYSCFG_PAD_DCAN1_TX         (0x4A0037D0)
#define SYSCFG_PAD_DCAN1_RX         (0x4A0037D4)
#define SYSCFG_PAD_UART1_RXD        (0x4A0037E0)
#define SYSCFG_PAD_UART1_TXD        (0x4A0037E4)
#define SYSCFG_PAD_UART1_CTSN       (0x4A0037E8)
#define SYSCFG_PAD_UART1_RTSN       (0x4A0037EC)
#define SYSCFG_PAD_UART3_CTSN       (0x4A0037F0)
#define SYSCFG_PAD_UART2_TXD        (0x4A0037F4)
#define SYSCFG_PAD_UART2_CTSN       (0x4A0037F8)
#define SYSCFG_PAD_UART2_RTSN       (0x4A0037FC)
#define SYSCFG_PAD_I2C1_SDA         (0x4A003800)
#define SYSCFG_PAD_I2C1_SCL         (0x4A003804)
#define SYSCFG_PAD_I2C2_SDA         (0x4A003808)
#define SYSCFG_PAD_I2C2_SCL         (0x4A00380C)
#define SYSCFG_PAD_I2C3_SDA         (0x4A003810)
#define SYSCFG_PAD_I2C3_SCL         (0x4A003814)
#define SYSCFG_PAD_WAKEUP0          (0x4A003818)
#define SYSCFG_PAD_WAKEUP1          (0x4A00381C)
#define SYSCFG_PAD_WAKEUP2          (0x4A003820)
#define SYSCFG_PAD_WAKEUP3          (0x4A003824)
#define SYSCFG_PAD_ON_OFF           (0x4A003828)
#define SYSCFG_PAD_RTC_PORZ         (0x4A00382C)
#define SYSCFG_PAD_TMS              (0x4A003830)
#define SYSCFG_PAD_TDI              (0x4A003834)
#define SYSCFG_PAD_TDO              (0x4A003838)
#define SYSCFG_PAD_TCLK             (0x4A00383C)
#define SYSCFG_PAD_TRSTN            (0x4A003840)
#define SYSCFG_PAD_RTCK             (0x4A003844)
#define SYSCFG_PAD_EMU0             (0x4A003848)
#define SYSCFG_PAD_EMU1             (0x4A00384C)



/* Ball: G19 */
#define PIN_CTRL_REG_ADDR_G19 SYSCFG_PAD_DCAN1_RX
#ifndef PIN_FUNCTION_G19_CAN
#define PIN_FUNCTION_G19_CAN 0UL
#endif
#ifndef PIN_FUNCTION_G19_UART8
#define PIN_FUNCTION_G19_UART8 2UL
#endif
#ifndef PIN_FUNCTION_G19_DIO
#define PIN_FUNCTION_G19_DIO 14UL
#endif
#ifndef PIN_G19_GPIO
#define PIN_G19_GPIO 1u
#define PIN_G19_GPIO_PIN 15u
#endif

/* Ball: G20 */
#define PIN_CTRL_REG_ADDR_G20 SYSCFG_PAD_DCAN1_TX
#ifndef PIN_FUNCTION_G20_CAN
#define PIN_FUNCTION_G20_CAN 0UL
#endif
#ifndef PIN_FUNCTION_G20_UART8
#define PIN_FUNCTION_G20_UART8 2UL
#endif
#ifndef PIN_FUNCTION_G20_DIO
#define PIN_FUNCTION_G20_DIO 14UL
#endif
#ifndef PIN_G20_GPIO
#define PIN_G20_GPIO 1u
#define PIN_G20_GPIO_PIN 14u
#endif

/* Ball: G21 */
#define PIN_CTRL_REG_ADDR_G21 SYSCFG_PAD_EMU0
#ifndef PIN_FUNCTION_G21_DIO
#define PIN_FUNCTION_G21_DIO 14UL
#endif
#ifndef PIN_G21_GPIO
#define PIN_G21_GPIO 8u
#define PIN_G21_GPIO_PIN 30u
#endif

/* Ball: D24 */
#define PIN_CTRL_REG_ADDR_D24 SYSCFG_PAD_EMU1
#ifndef PIN_FUNCTION_D24_DIO
#define PIN_FUNCTION_D24_DIO 14UL
#endif
#ifndef PIN_D24_GPIO
#define PIN_D24_GPIO 8u
#define PIN_D24_GPIO_PIN 31u
#endif

/* Ball: AC5 */
#define PIN_CTRL_REG_ADDR_AC5 SYSCFG_PAD_GPIO6_10
#ifndef PIN_FUNCTION_AC5_DIO
#define PIN_FUNCTION_AC5_DIO 0UL
#endif
#ifndef PIN_AC5_GPIO
#define PIN_AC5_GPIO 6u
#define PIN_AC5_GPIO_PIN 10u
#endif
#ifndef PIN_FUNCTION_AC5_ETH_MDIO
#define PIN_FUNCTION_AC5_ETH_MDIO 1UL
#endif
#ifndef PIN_FUNCTION_AC5_I2C3
#define PIN_FUNCTION_AC5_I2C3 2UL
#endif
#ifndef PIN_FUNCTION_AC5_PWM
#define PIN_FUNCTION_AC5_PWM 10UL
#endif
#ifndef PIN_FUNCTION_AC5_DIO
#define PIN_FUNCTION_AC5_DIO 14UL
#endif
#ifndef PIN_AC5_GPIO
#define PIN_AC5_GPIO 6u
#define PIN_AC5_GPIO_PIN 10u
#endif

/* Ball: AB4 */
#define PIN_CTRL_REG_ADDR_AB4 SYSCFG_PAD_GPIO6_11
#ifndef PIN_FUNCTION_AB4_DIO
#define PIN_FUNCTION_AB4_DIO 0UL
#endif
#ifndef PIN_AB4_GPIO
#define PIN_AB4_GPIO 6u
#define PIN_AB4_GPIO_PIN 11u
#endif
#ifndef PIN_FUNCTION_AB4_ETH_MDIO
#define PIN_FUNCTION_AB4_ETH_MDIO 1UL
#endif
#ifndef PIN_FUNCTION_AB4_I2C3
#define PIN_FUNCTION_AB4_I2C3 2UL
#endif
#ifndef PIN_FUNCTION_AB4_PWM
#define PIN_FUNCTION_AB4_PWM 10UL
#endif
#ifndef PIN_FUNCTION_AB4_DIO
#define PIN_FUNCTION_AB4_DIO 14UL
#endif
#ifndef PIN_AB4_GPIO
#define PIN_AB4_GPIO 6u
#define PIN_AB4_GPIO_PIN 11u
#endif

/* Ball: E21 */
#define PIN_CTRL_REG_ADDR_E21 SYSCFG_PAD_GPIO6_14
#ifndef PIN_FUNCTION_E21_DIO
#define PIN_FUNCTION_E21_DIO 0UL
#endif
#ifndef PIN_E21_GPIO
#define PIN_E21_GPIO 6u
#define PIN_E21_GPIO_PIN 14u
#endif
#ifndef PIN_FUNCTION_E21_CAN
#define PIN_FUNCTION_E21_CAN 2UL
#endif
#ifndef PIN_FUNCTION_E21_UART10
#define PIN_FUNCTION_E21_UART10 3UL
#endif
#ifndef PIN_FUNCTION_E21_I2C3
#define PIN_FUNCTION_E21_I2C3 9UL
#endif
#ifndef PIN_FUNCTION_E21_PWM
#define PIN_FUNCTION_E21_PWM 10UL
#endif
#ifndef PIN_FUNCTION_E21_ICU
#define PIN_FUNCTION_E21_ICU 10UL
#endif
#ifndef PIN_FUNCTION_E21_DIO
#define PIN_FUNCTION_E21_DIO 14UL
#endif
#ifndef PIN_E21_GPIO
#define PIN_E21_GPIO 6u
#define PIN_E21_GPIO_PIN 14u
#endif

/* Ball: F20 */
#define PIN_CTRL_REG_ADDR_F20 SYSCFG_PAD_GPIO6_15
#ifndef PIN_FUNCTION_F20_DIO
#define PIN_FUNCTION_F20_DIO 0UL
#endif
#ifndef PIN_F20_GPIO
#define PIN_F20_GPIO 6u
#define PIN_F20_GPIO_PIN 15u
#endif
#ifndef PIN_FUNCTION_F20_CAN
#define PIN_FUNCTION_F20_CAN 2UL
#endif
#ifndef PIN_FUNCTION_F20_UART10
#define PIN_FUNCTION_F20_UART10 3UL
#endif
#ifndef PIN_FUNCTION_F20_I2C3
#define PIN_FUNCTION_F20_I2C3 9UL
#endif
#ifndef PIN_FUNCTION_F20_PWM
#define PIN_FUNCTION_F20_PWM 10UL
#endif
#ifndef PIN_FUNCTION_F20_ICU
#define PIN_FUNCTION_F20_ICU 10UL
#endif
#ifndef PIN_FUNCTION_F20_DIO
#define PIN_FUNCTION_F20_DIO 14UL
#endif
#ifndef PIN_F20_GPIO
#define PIN_F20_GPIO 6u
#define PIN_F20_GPIO_PIN 15u
#endif

/* Ball: F21 */
#define PIN_CTRL_REG_ADDR_F21 SYSCFG_PAD_GPIO6_16
#ifndef PIN_FUNCTION_F21_DIO
#define PIN_FUNCTION_F21_DIO 0UL
#endif
#ifndef PIN_F21_GPIO
#define PIN_F21_GPIO 6u
#define PIN_F21_GPIO_PIN 16u
#endif
#ifndef PIN_FUNCTION_F21_PWM
#define PIN_FUNCTION_F21_PWM 10UL
#endif
#ifndef PIN_FUNCTION_F21_ICU
#define PIN_FUNCTION_F21_ICU 10UL
#endif
#ifndef PIN_FUNCTION_F21_DIO
#define PIN_FUNCTION_F21_DIO 14UL
#endif
#ifndef PIN_F21_GPIO
#define PIN_F21_GPIO 6u
#define PIN_F21_GPIO_PIN 16u
#endif

/* Ball: R6 */
#define PIN_CTRL_REG_ADDR_R6 SYSCFG_PAD_GPMC_A0
#ifndef PIN_FUNCTION_R6_I2C4
#define PIN_FUNCTION_R6_I2C4 7UL
#endif
#ifndef PIN_FUNCTION_R6_UART5
#define PIN_FUNCTION_R6_UART5 8UL
#endif
#ifndef PIN_FUNCTION_R6_DIO
#define PIN_FUNCTION_R6_DIO 14UL
#endif
#ifndef PIN_R6_GPIO
#define PIN_R6_GPIO 7u
#define PIN_R6_GPIO_PIN 3u
#endif

/* Ball: T9 */
#define PIN_CTRL_REG_ADDR_T9 SYSCFG_PAD_GPMC_A1
#ifndef PIN_FUNCTION_T9_I2C4
#define PIN_FUNCTION_T9_I2C4 7UL
#endif
#ifndef PIN_FUNCTION_T9_UART5
#define PIN_FUNCTION_T9_UART5 8UL
#endif
#ifndef PIN_FUNCTION_T9_DIO
#define PIN_FUNCTION_T9_DIO 14UL
#endif
#ifndef PIN_T9_GPIO
#define PIN_T9_GPIO 7u
#define PIN_T9_GPIO_PIN 4u
#endif

/* Ball: N9 */
#define PIN_CTRL_REG_ADDR_N9 SYSCFG_PAD_GPMC_A10
#ifndef PIN_FUNCTION_N9_PWM
#define PIN_FUNCTION_N9_PWM 7UL
#endif
#ifndef PIN_FUNCTION_N9_ICU
#define PIN_FUNCTION_N9_ICU 7UL
#endif
#ifndef PIN_FUNCTION_N9_SPI4
#define PIN_FUNCTION_N9_SPI4 8UL
#endif
#ifndef PIN_FUNCTION_N9_DIO
#define PIN_FUNCTION_N9_DIO 14UL
#endif
#ifndef PIN_N9_GPIO
#define PIN_N9_GPIO 2u
#define PIN_N9_GPIO_PIN 0u
#endif

/* Ball: P9 */
#define PIN_CTRL_REG_ADDR_P9 SYSCFG_PAD_GPMC_A11
#ifndef PIN_FUNCTION_P9_PWM
#define PIN_FUNCTION_P9_PWM 7UL
#endif
#ifndef PIN_FUNCTION_P9_ICU
#define PIN_FUNCTION_P9_ICU 7UL
#endif
#ifndef PIN_FUNCTION_P9_SPI4
#define PIN_FUNCTION_P9_SPI4 8UL
#endif
#ifndef PIN_FUNCTION_P9_DIO
#define PIN_FUNCTION_P9_DIO 14UL
#endif
#ifndef PIN_P9_GPIO
#define PIN_P9_GPIO 2u
#define PIN_P9_GPIO_PIN 1u
#endif

/* Ball: P4 */
#define PIN_CTRL_REG_ADDR_P4 SYSCFG_PAD_GPMC_A12
#ifndef PIN_FUNCTION_P4_PWM
#define PIN_FUNCTION_P4_PWM 7UL
#endif
#ifndef PIN_FUNCTION_P4_ICU
#define PIN_FUNCTION_P4_ICU 7UL
#endif
#ifndef PIN_FUNCTION_P4_SPI4
#define PIN_FUNCTION_P4_SPI4 8UL
#endif
#ifndef PIN_FUNCTION_P4_DIO
#define PIN_FUNCTION_P4_DIO 14UL
#endif
#ifndef PIN_P4_GPIO
#define PIN_P4_GPIO 2u
#define PIN_P4_GPIO_PIN 2u
#endif

/* Ball: R3 */
#define PIN_CTRL_REG_ADDR_R3 SYSCFG_PAD_GPMC_A13
#ifndef PIN_FUNCTION_R3_PWM
#define PIN_FUNCTION_R3_PWM 7UL
#endif
#ifndef PIN_FUNCTION_R3_ICU
#define PIN_FUNCTION_R3_ICU 7UL
#endif
#ifndef PIN_FUNCTION_R3_SPI4
#define PIN_FUNCTION_R3_SPI4 8UL
#endif
#ifndef PIN_FUNCTION_R3_DIO
#define PIN_FUNCTION_R3_DIO 14UL
#endif
#ifndef PIN_R3_GPIO
#define PIN_R3_GPIO 2u
#define PIN_R3_GPIO_PIN 3u
#endif

/* Ball: T2 */
#define PIN_CTRL_REG_ADDR_T2 SYSCFG_PAD_GPMC_A14
#ifndef PIN_FUNCTION_T2_PWM
#define PIN_FUNCTION_T2_PWM 7UL
#endif
#ifndef PIN_FUNCTION_T2_ICU
#define PIN_FUNCTION_T2_ICU 7UL
#endif
#ifndef PIN_FUNCTION_T2_SPI4
#define PIN_FUNCTION_T2_SPI4 8UL
#endif
#ifndef PIN_FUNCTION_T2_DIO
#define PIN_FUNCTION_T2_DIO 14UL
#endif
#ifndef PIN_T2_GPIO
#define PIN_T2_GPIO 2u
#define PIN_T2_GPIO_PIN 4u
#endif

/* Ball: U2 */
#define PIN_CTRL_REG_ADDR_U2 SYSCFG_PAD_GPMC_A15
#ifndef PIN_FUNCTION_U2_PWM
#define PIN_FUNCTION_U2_PWM 7UL
#endif
#ifndef PIN_FUNCTION_U2_ICU
#define PIN_FUNCTION_U2_ICU 7UL
#endif
#ifndef PIN_FUNCTION_U2_DIO
#define PIN_FUNCTION_U2_DIO 14UL
#endif
#ifndef PIN_U2_GPIO
#define PIN_U2_GPIO 2u
#define PIN_U2_GPIO_PIN 5u
#endif

/* Ball: U1 */
#define PIN_CTRL_REG_ADDR_U1 SYSCFG_PAD_GPMC_A16
#ifndef PIN_FUNCTION_U1_DIO
#define PIN_FUNCTION_U1_DIO 14UL
#endif
#ifndef PIN_U1_GPIO
#define PIN_U1_GPIO 2u
#define PIN_U1_GPIO_PIN 6u
#endif

/* Ball: P3 */
#define PIN_CTRL_REG_ADDR_P3 SYSCFG_PAD_GPMC_A17
#ifndef PIN_FUNCTION_P3_DIO
#define PIN_FUNCTION_P3_DIO 14UL
#endif
#ifndef PIN_P3_GPIO
#define PIN_P3_GPIO 2u
#define PIN_P3_GPIO_PIN 7u
#endif

/* Ball: R2 */
#define PIN_CTRL_REG_ADDR_R2 SYSCFG_PAD_GPMC_A18
#ifndef PIN_FUNCTION_R2_DIO
#define PIN_FUNCTION_R2_DIO 14UL
#endif
#ifndef PIN_R2_GPIO
#define PIN_R2_GPIO 2u
#define PIN_R2_GPIO_PIN 8u
#endif

/* Ball: K7 */
#define PIN_CTRL_REG_ADDR_K7 SYSCFG_PAD_GPMC_A19
#ifndef PIN_FUNCTION_K7_DIO
#define PIN_FUNCTION_K7_DIO 14UL
#endif
#ifndef PIN_K7_GPIO
#define PIN_K7_GPIO 2u
#define PIN_K7_GPIO_PIN 9u
#endif

/* Ball: T6 */
#define PIN_CTRL_REG_ADDR_T6 SYSCFG_PAD_GPMC_A2
#ifndef PIN_FUNCTION_T6_UART7
#define PIN_FUNCTION_T6_UART7 7UL
#endif
#ifndef PIN_FUNCTION_T6_UART5
#define PIN_FUNCTION_T6_UART5 8UL
#endif
#ifndef PIN_FUNCTION_T6_DIO
#define PIN_FUNCTION_T6_DIO 14UL
#endif
#ifndef PIN_T6_GPIO
#define PIN_T6_GPIO 7u
#define PIN_T6_GPIO_PIN 5u
#endif

/* Ball: M7 */
#define PIN_CTRL_REG_ADDR_M7 SYSCFG_PAD_GPMC_A20
#ifndef PIN_FUNCTION_M7_DIO
#define PIN_FUNCTION_M7_DIO 14UL
#endif
#ifndef PIN_M7_GPIO
#define PIN_M7_GPIO 2u
#define PIN_M7_GPIO_PIN 10u
#endif

/* Ball: J5 */
#define PIN_CTRL_REG_ADDR_J5 SYSCFG_PAD_GPMC_A21
#ifndef PIN_FUNCTION_J5_DIO
#define PIN_FUNCTION_J5_DIO 14UL
#endif
#ifndef PIN_J5_GPIO
#define PIN_J5_GPIO 2u
#define PIN_J5_GPIO_PIN 11u
#endif

/* Ball: K6 */
#define PIN_CTRL_REG_ADDR_K6 SYSCFG_PAD_GPMC_A22
#ifndef PIN_FUNCTION_K6_DIO
#define PIN_FUNCTION_K6_DIO 14UL
#endif
#ifndef PIN_K6_GPIO
#define PIN_K6_GPIO 2u
#define PIN_K6_GPIO_PIN 12u
#endif

/* Ball: J7 */
#define PIN_CTRL_REG_ADDR_J7 SYSCFG_PAD_GPMC_A23
#ifndef PIN_FUNCTION_J7_DIO
#define PIN_FUNCTION_J7_DIO 14UL
#endif
#ifndef PIN_J7_GPIO
#define PIN_J7_GPIO 2u
#define PIN_J7_GPIO_PIN 13u
#endif

/* Ball: J4 */
#define PIN_CTRL_REG_ADDR_J4 SYSCFG_PAD_GPMC_A24
#ifndef PIN_FUNCTION_J4_DIO
#define PIN_FUNCTION_J4_DIO 14UL
#endif
#ifndef PIN_J4_GPIO
#define PIN_J4_GPIO 2u
#define PIN_J4_GPIO_PIN 14u
#endif

/* Ball: J6 */
#define PIN_CTRL_REG_ADDR_J6 SYSCFG_PAD_GPMC_A25
#ifndef PIN_FUNCTION_J6_DIO
#define PIN_FUNCTION_J6_DIO 14UL
#endif
#ifndef PIN_J6_GPIO
#define PIN_J6_GPIO 2u
#define PIN_J6_GPIO_PIN 15u
#endif

/* Ball: H4 */
#define PIN_CTRL_REG_ADDR_H4 SYSCFG_PAD_GPMC_A26
#ifndef PIN_FUNCTION_H4_DIO
#define PIN_FUNCTION_H4_DIO 14UL
#endif
#ifndef PIN_H4_GPIO
#define PIN_H4_GPIO 2u
#define PIN_H4_GPIO_PIN 16u
#endif

/* Ball: H5 */
#define PIN_CTRL_REG_ADDR_H5 SYSCFG_PAD_GPMC_A27
#ifndef PIN_FUNCTION_H5_DIO
#define PIN_FUNCTION_H5_DIO 14UL
#endif
#ifndef PIN_H5_GPIO
#define PIN_H5_GPIO 2u
#define PIN_H5_GPIO_PIN 17u
#endif

/* Ball: T7 */
#define PIN_CTRL_REG_ADDR_T7 SYSCFG_PAD_GPMC_A3
#ifndef PIN_FUNCTION_T7_UART7
#define PIN_FUNCTION_T7_UART7 7UL
#endif
#ifndef PIN_FUNCTION_T7_UART5
#define PIN_FUNCTION_T7_UART5 8UL
#endif
#ifndef PIN_FUNCTION_T7_DIO
#define PIN_FUNCTION_T7_DIO 14UL
#endif
#ifndef PIN_T7_GPIO
#define PIN_T7_GPIO 7u
#define PIN_T7_GPIO_PIN 6u
#endif

/* Ball: P6 */
#define PIN_CTRL_REG_ADDR_P6 SYSCFG_PAD_GPMC_A4
#ifndef PIN_FUNCTION_P6_I2C5
#define PIN_FUNCTION_P6_I2C5 7UL
#endif
#ifndef PIN_FUNCTION_P6_UART6
#define PIN_FUNCTION_P6_UART6 8UL
#endif
#ifndef PIN_FUNCTION_P6_DIO
#define PIN_FUNCTION_P6_DIO 14UL
#endif
#ifndef PIN_P6_GPIO
#define PIN_P6_GPIO 1u
#define PIN_P6_GPIO_PIN 26u
#endif

/* Ball: R9 */
#define PIN_CTRL_REG_ADDR_R9 SYSCFG_PAD_GPMC_A5
#ifndef PIN_FUNCTION_R9_I2C5
#define PIN_FUNCTION_R9_I2C5 7UL
#endif
#ifndef PIN_FUNCTION_R9_UART6
#define PIN_FUNCTION_R9_UART6 8UL
#endif
#ifndef PIN_FUNCTION_R9_DIO
#define PIN_FUNCTION_R9_DIO 14UL
#endif
#ifndef PIN_R9_GPIO
#define PIN_R9_GPIO 1u
#define PIN_R9_GPIO_PIN 27u
#endif

/* Ball: R5 */
#define PIN_CTRL_REG_ADDR_R5 SYSCFG_PAD_GPMC_A6
#ifndef PIN_FUNCTION_R5_UART8
#define PIN_FUNCTION_R5_UART8 7UL
#endif
#ifndef PIN_FUNCTION_R5_UART6
#define PIN_FUNCTION_R5_UART6 8UL
#endif
#ifndef PIN_FUNCTION_R5_DIO
#define PIN_FUNCTION_R5_DIO 14UL
#endif
#ifndef PIN_R5_GPIO
#define PIN_R5_GPIO 1u
#define PIN_R5_GPIO_PIN 28u
#endif

/* Ball: P5 */
#define PIN_CTRL_REG_ADDR_P5 SYSCFG_PAD_GPMC_A7
#ifndef PIN_FUNCTION_P5_UART8
#define PIN_FUNCTION_P5_UART8 7UL
#endif
#ifndef PIN_FUNCTION_P5_UART6
#define PIN_FUNCTION_P5_UART6 8UL
#endif
#ifndef PIN_FUNCTION_P5_DIO
#define PIN_FUNCTION_P5_DIO 14UL
#endif
#ifndef PIN_P5_GPIO
#define PIN_P5_GPIO 1u
#define PIN_P5_GPIO_PIN 29u
#endif

/* Ball: N7 */
#define PIN_CTRL_REG_ADDR_N7 SYSCFG_PAD_GPMC_A8
#ifndef PIN_FUNCTION_N7_PWM
#define PIN_FUNCTION_N7_PWM 7UL
#endif
#ifndef PIN_FUNCTION_N7_ICU
#define PIN_FUNCTION_N7_ICU 7UL
#endif
#ifndef PIN_FUNCTION_N7_SPI4
#define PIN_FUNCTION_N7_SPI4 8UL
#endif
#ifndef PIN_FUNCTION_N7_DIO
#define PIN_FUNCTION_N7_DIO 14UL
#endif
#ifndef PIN_N7_GPIO
#define PIN_N7_GPIO 1u
#define PIN_N7_GPIO_PIN 30u
#endif

/* Ball: R4 */
#define PIN_CTRL_REG_ADDR_R4 SYSCFG_PAD_GPMC_A9
#ifndef PIN_FUNCTION_R4_PWM
#define PIN_FUNCTION_R4_PWM 7UL
#endif
#ifndef PIN_FUNCTION_R4_ICU
#define PIN_FUNCTION_R4_ICU 7UL
#endif
#ifndef PIN_FUNCTION_R4_SPI4
#define PIN_FUNCTION_R4_SPI4 8UL
#endif
#ifndef PIN_FUNCTION_R4_DIO
#define PIN_FUNCTION_R4_DIO 14UL
#endif
#ifndef PIN_R4_GPIO
#define PIN_R4_GPIO 1u
#define PIN_R4_GPIO_PIN 31u
#endif

/* Ball: M6 */
#define PIN_CTRL_REG_ADDR_M6 SYSCFG_PAD_GPMC_AD0
#ifndef PIN_FUNCTION_M6_DIO
#define PIN_FUNCTION_M6_DIO 14UL
#endif
#ifndef PIN_M6_GPIO
#define PIN_M6_GPIO 1u
#define PIN_M6_GPIO_PIN 6u
#endif

/* Ball: M2 */
#define PIN_CTRL_REG_ADDR_M2 SYSCFG_PAD_GPMC_AD1
#ifndef PIN_FUNCTION_M2_DIO
#define PIN_FUNCTION_M2_DIO 14UL
#endif
#ifndef PIN_M2_GPIO
#define PIN_M2_GPIO 1u
#define PIN_M2_GPIO_PIN 7u
#endif

/* Ball: J1 */
#define PIN_CTRL_REG_ADDR_J1 SYSCFG_PAD_GPMC_AD10
#ifndef PIN_FUNCTION_J1_DIO
#define PIN_FUNCTION_J1_DIO 14UL
#endif
#ifndef PIN_J1_GPIO
#define PIN_J1_GPIO 7u
#define PIN_J1_GPIO_PIN 28u
#endif

/* Ball: J2 */
#define PIN_CTRL_REG_ADDR_J2 SYSCFG_PAD_GPMC_AD11
#ifndef PIN_FUNCTION_J2_DIO
#define PIN_FUNCTION_J2_DIO 14UL
#endif
#ifndef PIN_J2_GPIO
#define PIN_J2_GPIO 7u
#define PIN_J2_GPIO_PIN 29u
#endif

/* Ball: H1 */
#define PIN_CTRL_REG_ADDR_H1 SYSCFG_PAD_GPMC_AD12
#ifndef PIN_FUNCTION_H1_DIO
#define PIN_FUNCTION_H1_DIO 14UL
#endif
#ifndef PIN_H1_GPIO
#define PIN_H1_GPIO 1u
#define PIN_H1_GPIO_PIN 18u
#endif

/* Ball: J3 */
#define PIN_CTRL_REG_ADDR_J3 SYSCFG_PAD_GPMC_AD13
#ifndef PIN_FUNCTION_J3_DIO
#define PIN_FUNCTION_J3_DIO 14UL
#endif
#ifndef PIN_J3_GPIO
#define PIN_J3_GPIO 1u
#define PIN_J3_GPIO_PIN 19u
#endif

/* Ball: H2 */
#define PIN_CTRL_REG_ADDR_H2 SYSCFG_PAD_GPMC_AD14
#ifndef PIN_FUNCTION_H2_DIO
#define PIN_FUNCTION_H2_DIO 14UL
#endif
#ifndef PIN_H2_GPIO
#define PIN_H2_GPIO 1u
#define PIN_H2_GPIO_PIN 20u
#endif

/* Ball: H3 */
#define PIN_CTRL_REG_ADDR_H3 SYSCFG_PAD_GPMC_AD15
#ifndef PIN_FUNCTION_H3_DIO
#define PIN_FUNCTION_H3_DIO 14UL
#endif
#ifndef PIN_H3_GPIO
#define PIN_H3_GPIO 1u
#define PIN_H3_GPIO_PIN 21u
#endif

/* Ball: L5 */
#define PIN_CTRL_REG_ADDR_L5 SYSCFG_PAD_GPMC_AD2
#ifndef PIN_FUNCTION_L5_DIO
#define PIN_FUNCTION_L5_DIO 14UL
#endif
#ifndef PIN_L5_GPIO
#define PIN_L5_GPIO 1u
#define PIN_L5_GPIO_PIN 8u
#endif

/* Ball: M1 */
#define PIN_CTRL_REG_ADDR_M1 SYSCFG_PAD_GPMC_AD3
#ifndef PIN_FUNCTION_M1_DIO
#define PIN_FUNCTION_M1_DIO 14UL
#endif
#ifndef PIN_M1_GPIO
#define PIN_M1_GPIO 1u
#define PIN_M1_GPIO_PIN 9u
#endif

/* Ball: L6 */
#define PIN_CTRL_REG_ADDR_L6 SYSCFG_PAD_GPMC_AD4
#ifndef PIN_FUNCTION_L6_DIO
#define PIN_FUNCTION_L6_DIO 14UL
#endif
#ifndef PIN_L6_GPIO
#define PIN_L6_GPIO 1u
#define PIN_L6_GPIO_PIN 10u
#endif

/* Ball: L4 */
#define PIN_CTRL_REG_ADDR_L4 SYSCFG_PAD_GPMC_AD5
#ifndef PIN_FUNCTION_L4_DIO
#define PIN_FUNCTION_L4_DIO 14UL
#endif
#ifndef PIN_L4_GPIO
#define PIN_L4_GPIO 1u
#define PIN_L4_GPIO_PIN 11u
#endif

/* Ball: L3 */
#define PIN_CTRL_REG_ADDR_L3 SYSCFG_PAD_GPMC_AD6
#ifndef PIN_FUNCTION_L3_DIO
#define PIN_FUNCTION_L3_DIO 14UL
#endif
#ifndef PIN_L3_GPIO
#define PIN_L3_GPIO 1u
#define PIN_L3_GPIO_PIN 12u
#endif

/* Ball: L2 */
#define PIN_CTRL_REG_ADDR_L2 SYSCFG_PAD_GPMC_AD7
#ifndef PIN_FUNCTION_L2_DIO
#define PIN_FUNCTION_L2_DIO 14UL
#endif
#ifndef PIN_L2_GPIO
#define PIN_L2_GPIO 1u
#define PIN_L2_GPIO_PIN 13u
#endif

/* Ball: L1 */
#define PIN_CTRL_REG_ADDR_L1 SYSCFG_PAD_GPMC_AD8
#ifndef PIN_FUNCTION_L1_DIO
#define PIN_FUNCTION_L1_DIO 14UL
#endif
#ifndef PIN_L1_GPIO
#define PIN_L1_GPIO 7u
#define PIN_L1_GPIO_PIN 18u
#endif

/* Ball: K2 */
#define PIN_CTRL_REG_ADDR_K2 SYSCFG_PAD_GPMC_AD9
#ifndef PIN_FUNCTION_K2_DIO
#define PIN_FUNCTION_K2_DIO 14UL
#endif
#ifndef PIN_K2_GPIO
#define PIN_K2_GPIO 7u
#define PIN_K2_GPIO_PIN 19u
#endif

/* Ball: N1 */
#define PIN_CTRL_REG_ADDR_N1 SYSCFG_PAD_GPMC_ADVN_ALE
#ifndef PIN_FUNCTION_N1_PWM
#define PIN_FUNCTION_N1_PWM 7UL
#endif
#ifndef PIN_FUNCTION_N1_ICU
#define PIN_FUNCTION_N1_ICU 7UL
#endif
#ifndef PIN_FUNCTION_N1_I2C3
#define PIN_FUNCTION_N1_I2C3 8UL
#endif
#ifndef PIN_FUNCTION_N1_DIO
#define PIN_FUNCTION_N1_DIO 14UL
#endif
#ifndef PIN_N1_GPIO
#define PIN_N1_GPIO 2u
#define PIN_N1_GPIO_PIN 23u
#endif

/* Ball: N6 */
#define PIN_CTRL_REG_ADDR_N6 SYSCFG_PAD_GPMC_BEN0
#ifndef PIN_FUNCTION_N6_PWM
#define PIN_FUNCTION_N6_PWM 7UL
#endif
#ifndef PIN_FUNCTION_N6_ICU
#define PIN_FUNCTION_N6_ICU 7UL
#endif
#ifndef PIN_FUNCTION_N6_DIO
#define PIN_FUNCTION_N6_DIO 14UL
#endif
#ifndef PIN_N6_GPIO
#define PIN_N6_GPIO 2u
#define PIN_N6_GPIO_PIN 26u
#endif

/* Ball: M4 */
#define PIN_CTRL_REG_ADDR_M4 SYSCFG_PAD_GPMC_BEN1
#ifndef PIN_FUNCTION_M4_PWM
#define PIN_FUNCTION_M4_PWM 7UL
#endif
#ifndef PIN_FUNCTION_M4_ICU
#define PIN_FUNCTION_M4_ICU 7UL
#endif
#ifndef PIN_FUNCTION_M4_DIO
#define PIN_FUNCTION_M4_DIO 14UL
#endif
#ifndef PIN_M4_GPIO
#define PIN_M4_GPIO 2u
#define PIN_M4_GPIO_PIN 27u
#endif

/* Ball: P7 */
#define PIN_CTRL_REG_ADDR_P7 SYSCFG_PAD_GPMC_CLK
#ifndef PIN_FUNCTION_P7_PWM
#define PIN_FUNCTION_P7_PWM 7UL
#endif
#ifndef PIN_FUNCTION_P7_ICU
#define PIN_FUNCTION_P7_ICU 7UL
#endif
#ifndef PIN_FUNCTION_P7_I2C3
#define PIN_FUNCTION_P7_I2C3 8UL
#endif
#ifndef PIN_FUNCTION_P7_DIO
#define PIN_FUNCTION_P7_DIO 14UL
#endif
#ifndef PIN_P7_GPIO
#define PIN_P7_GPIO 2u
#define PIN_P7_GPIO_PIN 22u
#endif

/* Ball: T1 */
#define PIN_CTRL_REG_ADDR_T1 SYSCFG_PAD_GPMC_CS0
#ifndef PIN_FUNCTION_T1_DIO
#define PIN_FUNCTION_T1_DIO 14UL
#endif
#ifndef PIN_T1_GPIO
#define PIN_T1_GPIO 2u
#define PIN_T1_GPIO_PIN 19u
#endif

/* Ball: H6 */
#define PIN_CTRL_REG_ADDR_H6 SYSCFG_PAD_GPMC_CS1
#ifndef PIN_FUNCTION_H6_DIO
#define PIN_FUNCTION_H6_DIO 14UL
#endif
#ifndef PIN_H6_GPIO
#define PIN_H6_GPIO 2u
#define PIN_H6_GPIO_PIN 18u
#endif

/* Ball: P2 */
#define PIN_CTRL_REG_ADDR_P2 SYSCFG_PAD_GPMC_CS2
#ifndef PIN_FUNCTION_P2_DIO
#define PIN_FUNCTION_P2_DIO 14UL
#endif
#ifndef PIN_P2_GPIO
#define PIN_P2_GPIO 2u
#define PIN_P2_GPIO_PIN 20u
#endif

/* Ball: P1 */
#define PIN_CTRL_REG_ADDR_P1 SYSCFG_PAD_GPMC_CS3
#ifndef PIN_FUNCTION_P1_DIO
#define PIN_FUNCTION_P1_DIO 14UL
#endif
#ifndef PIN_P1_GPIO
#define PIN_P1_GPIO 2u
#define PIN_P1_GPIO_PIN 21u
#endif

/* Ball: M5 */
#define PIN_CTRL_REG_ADDR_M5 SYSCFG_PAD_GPMC_OEN_REN
#ifndef PIN_FUNCTION_M5_DIO
#define PIN_FUNCTION_M5_DIO 14UL
#endif
#ifndef PIN_M5_GPIO
#define PIN_M5_GPIO 2u
#define PIN_M5_GPIO_PIN 24u
#endif

/* Ball: N2 */
#define PIN_CTRL_REG_ADDR_N2 SYSCFG_PAD_GPMC_WAIT0
#ifndef PIN_FUNCTION_N2_DIO
#define PIN_FUNCTION_N2_DIO 14UL
#endif
#ifndef PIN_N2_GPIO
#define PIN_N2_GPIO 2u
#define PIN_N2_GPIO_PIN 28u
#endif

/* Ball: M3 */
#define PIN_CTRL_REG_ADDR_M3 SYSCFG_PAD_GPMC_WEN
#ifndef PIN_FUNCTION_M3_DIO
#define PIN_FUNCTION_M3_DIO 14UL
#endif
#ifndef PIN_M3_GPIO
#define PIN_M3_GPIO 2u
#define PIN_M3_GPIO_PIN 25u
#endif

/* Ball: C20 */
#define PIN_CTRL_REG_ADDR_C20 SYSCFG_PAD_I2C1_SCL
#ifndef PIN_FUNCTION_C20_I2C1
#define PIN_FUNCTION_C20_I2C1 0UL
#endif

/* Ball: C21 */
#define PIN_CTRL_REG_ADDR_C21 SYSCFG_PAD_I2C1_SDA
#ifndef PIN_FUNCTION_C21_I2C1
#define PIN_FUNCTION_C21_I2C1 0UL
#endif

/* Ball: F17 */
#define PIN_CTRL_REG_ADDR_F17 SYSCFG_PAD_I2C2_SCL
#ifndef PIN_FUNCTION_F17_I2C2
#define PIN_FUNCTION_F17_I2C2 0UL
#endif

/* Ball: C25 */
#define PIN_CTRL_REG_ADDR_C25 SYSCFG_PAD_I2C2_SDA
#ifndef PIN_FUNCTION_C25_I2C2
#define PIN_FUNCTION_C25_I2C2 0UL
#endif

/* Ball: B14 */
#define PIN_CTRL_REG_ADDR_B14 SYSCFG_PAD_MCASP1_ACLKR
#ifndef PIN_FUNCTION_B14_I2C4
#define PIN_FUNCTION_B14_I2C4 10UL
#endif
#ifndef PIN_FUNCTION_B14_DIO
#define PIN_FUNCTION_B14_DIO 14UL
#endif
#ifndef PIN_B14_GPIO
#define PIN_B14_GPIO 5u
#define PIN_B14_GPIO_PIN 0u
#endif

/* Ball: C14 */
#define PIN_CTRL_REG_ADDR_C14 SYSCFG_PAD_MCASP1_ACLKX
#ifndef PIN_FUNCTION_C14_I2C3
#define PIN_FUNCTION_C14_I2C3 10UL
#endif
#ifndef PIN_FUNCTION_C14_DIO
#define PIN_FUNCTION_C14_DIO 14UL
#endif
#ifndef PIN_C14_GPIO
#define PIN_C14_GPIO 7u
#define PIN_C14_GPIO_PIN 31u
#endif

/* Ball: G12 */
#define PIN_CTRL_REG_ADDR_G12 SYSCFG_PAD_MCASP1_AXR0
#ifndef PIN_FUNCTION_G12_UART6
#define PIN_FUNCTION_G12_UART6 3UL
#endif
#ifndef PIN_FUNCTION_G12_I2C5
#define PIN_FUNCTION_G12_I2C5 10UL
#endif
#ifndef PIN_FUNCTION_G12_DIO
#define PIN_FUNCTION_G12_DIO 14UL
#endif
#ifndef PIN_G12_GPIO
#define PIN_G12_GPIO 5u
#define PIN_G12_GPIO_PIN 2u
#endif

/* Ball: F12 */
#define PIN_CTRL_REG_ADDR_F12 SYSCFG_PAD_MCASP1_AXR1
#ifndef PIN_FUNCTION_F12_UART6
#define PIN_FUNCTION_F12_UART6 3UL
#endif
#ifndef PIN_FUNCTION_F12_I2C5
#define PIN_FUNCTION_F12_I2C5 10UL
#endif
#ifndef PIN_FUNCTION_F12_DIO
#define PIN_FUNCTION_F12_DIO 14UL
#endif
#ifndef PIN_F12_GPIO
#define PIN_F12_GPIO 5u
#define PIN_F12_GPIO_PIN 3u
#endif

/* Ball: B13 */
#define PIN_CTRL_REG_ADDR_B13 SYSCFG_PAD_MCASP1_AXR10
#ifndef PIN_FUNCTION_B13_SPI3
#define PIN_FUNCTION_B13_SPI3 3UL
#endif
#ifndef PIN_FUNCTION_B13_PWM
#define PIN_FUNCTION_B13_PWM 10UL
#endif
#ifndef PIN_FUNCTION_B13_ICU
#define PIN_FUNCTION_B13_ICU 10UL
#endif
#ifndef PIN_FUNCTION_B13_DIO
#define PIN_FUNCTION_B13_DIO 14UL
#endif
#ifndef PIN_B13_GPIO
#define PIN_B13_GPIO 5u
#define PIN_B13_GPIO_PIN 12u
#endif

/* Ball: A12 */
#define PIN_CTRL_REG_ADDR_A12 SYSCFG_PAD_MCASP1_AXR11
#ifndef PIN_FUNCTION_A12_SPI3
#define PIN_FUNCTION_A12_SPI3 3UL
#endif
#ifndef PIN_FUNCTION_A12_PWM
#define PIN_FUNCTION_A12_PWM 10UL
#endif
#ifndef PIN_FUNCTION_A12_ICU
#define PIN_FUNCTION_A12_ICU 10UL
#endif
#ifndef PIN_FUNCTION_A12_DIO
#define PIN_FUNCTION_A12_DIO 14UL
#endif
#ifndef PIN_A12_GPIO
#define PIN_A12_GPIO 4u
#define PIN_A12_GPIO_PIN 17u
#endif

/* Ball: E14 */
#define PIN_CTRL_REG_ADDR_E14 SYSCFG_PAD_MCASP1_AXR12
#ifndef PIN_FUNCTION_E14_SPI3
#define PIN_FUNCTION_E14_SPI3 3UL
#endif
#ifndef PIN_FUNCTION_E14_PWM
#define PIN_FUNCTION_E14_PWM 10UL
#endif
#ifndef PIN_FUNCTION_E14_ICU
#define PIN_FUNCTION_E14_ICU 10UL
#endif
#ifndef PIN_FUNCTION_E14_DIO
#define PIN_FUNCTION_E14_DIO 14UL
#endif
#ifndef PIN_E14_GPIO
#define PIN_E14_GPIO 4u
#define PIN_E14_GPIO_PIN 18u
#endif

/* Ball: A13 */
#define PIN_CTRL_REG_ADDR_A13 SYSCFG_PAD_MCASP1_AXR13
#ifndef PIN_FUNCTION_A13_PWM
#define PIN_FUNCTION_A13_PWM 10UL
#endif
#ifndef PIN_FUNCTION_A13_ICU
#define PIN_FUNCTION_A13_ICU 10UL
#endif
#ifndef PIN_FUNCTION_A13_DIO
#define PIN_FUNCTION_A13_DIO 14UL
#endif
#ifndef PIN_A13_GPIO
#define PIN_A13_GPIO 6u
#define PIN_A13_GPIO_PIN 4u
#endif

/* Ball: G14 */
#define PIN_CTRL_REG_ADDR_G14 SYSCFG_PAD_MCASP1_AXR14
#ifndef PIN_FUNCTION_G14_PWM
#define PIN_FUNCTION_G14_PWM 10UL
#endif
#ifndef PIN_FUNCTION_G14_ICU
#define PIN_FUNCTION_G14_ICU 10UL
#endif
#ifndef PIN_FUNCTION_G14_DIO
#define PIN_FUNCTION_G14_DIO 14UL
#endif
#ifndef PIN_G14_GPIO
#define PIN_G14_GPIO 6u
#define PIN_G14_GPIO_PIN 5u
#endif

/* Ball: F14 */
#define PIN_CTRL_REG_ADDR_F14 SYSCFG_PAD_MCASP1_AXR15
#ifndef PIN_FUNCTION_F14_PWM
#define PIN_FUNCTION_F14_PWM 10UL
#endif
#ifndef PIN_FUNCTION_F14_ICU
#define PIN_FUNCTION_F14_ICU 10UL
#endif
#ifndef PIN_FUNCTION_F14_DIO
#define PIN_FUNCTION_F14_DIO 14UL
#endif
#ifndef PIN_F14_GPIO
#define PIN_F14_GPIO 6u
#define PIN_F14_GPIO_PIN 6u
#endif

/* Ball: G13 */
#define PIN_CTRL_REG_ADDR_G13 SYSCFG_PAD_MCASP1_AXR2
#ifndef PIN_FUNCTION_G13_UART6
#define PIN_FUNCTION_G13_UART6 3UL
#endif
#ifndef PIN_FUNCTION_G13_DIO
#define PIN_FUNCTION_G13_DIO 14UL
#endif
#ifndef PIN_G13_GPIO
#define PIN_G13_GPIO 5u
#define PIN_G13_GPIO_PIN 4u
#endif

/* Ball: J11 */
#define PIN_CTRL_REG_ADDR_J11 SYSCFG_PAD_MCASP1_AXR3
#ifndef PIN_FUNCTION_J11_UART6
#define PIN_FUNCTION_J11_UART6 3UL
#endif
#ifndef PIN_FUNCTION_J11_DIO
#define PIN_FUNCTION_J11_DIO 14UL
#endif
#ifndef PIN_J11_GPIO
#define PIN_J11_GPIO 5u
#define PIN_J11_GPIO_PIN 5u
#endif

/* Ball: E12 */
#define PIN_CTRL_REG_ADDR_E12 SYSCFG_PAD_MCASP1_AXR4
#ifndef PIN_FUNCTION_E12_DIO
#define PIN_FUNCTION_E12_DIO 14UL
#endif
#ifndef PIN_E12_GPIO
#define PIN_E12_GPIO 5u
#define PIN_E12_GPIO_PIN 6u
#endif

/* Ball: F13 */
#define PIN_CTRL_REG_ADDR_F13 SYSCFG_PAD_MCASP1_AXR5
#ifndef PIN_FUNCTION_F13_DIO
#define PIN_FUNCTION_F13_DIO 14UL
#endif
#ifndef PIN_F13_GPIO
#define PIN_F13_GPIO 5u
#define PIN_F13_GPIO_PIN 7u
#endif

/* Ball: C12 */
#define PIN_CTRL_REG_ADDR_C12 SYSCFG_PAD_MCASP1_AXR6
#ifndef PIN_FUNCTION_C12_DIO
#define PIN_FUNCTION_C12_DIO 14UL
#endif
#ifndef PIN_C12_GPIO
#define PIN_C12_GPIO 5u
#define PIN_C12_GPIO_PIN 8u
#endif

/* Ball: D12 */
#define PIN_CTRL_REG_ADDR_D12 SYSCFG_PAD_MCASP1_AXR7
#ifndef PIN_FUNCTION_D12_PWM
#define PIN_FUNCTION_D12_PWM 10UL
#endif
#ifndef PIN_FUNCTION_D12_ICU
#define PIN_FUNCTION_D12_ICU 10UL
#endif
#ifndef PIN_FUNCTION_D12_DIO
#define PIN_FUNCTION_D12_DIO 14UL
#endif
#ifndef PIN_D12_GPIO
#define PIN_D12_GPIO 5u
#define PIN_D12_GPIO_PIN 9u
#endif

/* Ball: B12 */
#define PIN_CTRL_REG_ADDR_B12 SYSCFG_PAD_MCASP1_AXR8
#ifndef PIN_FUNCTION_B12_SPI3
#define PIN_FUNCTION_B12_SPI3 3UL
#endif
#ifndef PIN_FUNCTION_B12_PWM
#define PIN_FUNCTION_B12_PWM 10UL
#endif
#ifndef PIN_FUNCTION_B12_ICU
#define PIN_FUNCTION_B12_ICU 10UL
#endif
#ifndef PIN_FUNCTION_B12_DIO
#define PIN_FUNCTION_B12_DIO 14UL
#endif
#ifndef PIN_B12_GPIO
#define PIN_B12_GPIO 5u
#define PIN_B12_GPIO_PIN 10u
#endif

/* Ball: A11 */
#define PIN_CTRL_REG_ADDR_A11 SYSCFG_PAD_MCASP1_AXR9
#ifndef PIN_FUNCTION_A11_SPI3
#define PIN_FUNCTION_A11_SPI3 3UL
#endif
#ifndef PIN_FUNCTION_A11_PWM
#define PIN_FUNCTION_A11_PWM 10UL
#endif
#ifndef PIN_FUNCTION_A11_ICU
#define PIN_FUNCTION_A11_ICU 10UL
#endif
#ifndef PIN_FUNCTION_A11_DIO
#define PIN_FUNCTION_A11_DIO 14UL
#endif
#ifndef PIN_A11_GPIO
#define PIN_A11_GPIO 5u
#define PIN_A11_GPIO_PIN 11u
#endif

/* Ball: J14 */
#define PIN_CTRL_REG_ADDR_J14 SYSCFG_PAD_MCASP1_FSR
#ifndef PIN_FUNCTION_J14_I2C4
#define PIN_FUNCTION_J14_I2C4 10UL
#endif
#ifndef PIN_FUNCTION_J14_DIO
#define PIN_FUNCTION_J14_DIO 14UL
#endif
#ifndef PIN_J14_GPIO
#define PIN_J14_GPIO 5u
#define PIN_J14_GPIO_PIN 1u
#endif

/* Ball: D14 */
#define PIN_CTRL_REG_ADDR_D14 SYSCFG_PAD_MCASP1_FSX
#ifndef PIN_FUNCTION_D14_I2C3
#define PIN_FUNCTION_D14_I2C3 10UL
#endif
#ifndef PIN_FUNCTION_D14_DIO
#define PIN_FUNCTION_D14_DIO 14UL
#endif
#ifndef PIN_D14_GPIO
#define PIN_D14_GPIO 7u
#define PIN_D14_GPIO_PIN 30u
#endif

/* Ball: C15 */
#define PIN_CTRL_REG_ADDR_C15 SYSCFG_PAD_MCASP2_AXR2
#ifndef PIN_FUNCTION_C15_DIO
#define PIN_FUNCTION_C15_DIO 14UL
#endif
#ifndef PIN_C15_GPIO
#define PIN_C15_GPIO 6u
#define PIN_C15_GPIO_PIN 8u
#endif

/* Ball: A16 */
#define PIN_CTRL_REG_ADDR_A16 SYSCFG_PAD_MCASP2_AXR3
#ifndef PIN_FUNCTION_A16_DIO
#define PIN_FUNCTION_A16_DIO 14UL
#endif
#ifndef PIN_A16_GPIO
#define PIN_A16_GPIO 6u
#define PIN_A16_GPIO_PIN 9u
#endif

/* Ball: D15 */
#define PIN_CTRL_REG_ADDR_D15 SYSCFG_PAD_MCASP2_AXR4
#ifndef PIN_FUNCTION_D15_DIO
#define PIN_FUNCTION_D15_DIO 14UL
#endif
#ifndef PIN_D15_GPIO
#define PIN_D15_GPIO 1u
#define PIN_D15_GPIO_PIN 4u
#endif

/* Ball: B16 */
#define PIN_CTRL_REG_ADDR_B16 SYSCFG_PAD_MCASP2_AXR5
#ifndef PIN_FUNCTION_B16_DIO
#define PIN_FUNCTION_B16_DIO 14UL
#endif
#ifndef PIN_B16_GPIO
#define PIN_B16_GPIO 6u
#define PIN_B16_GPIO_PIN 7u
#endif

/* Ball: B17 */
#define PIN_CTRL_REG_ADDR_B17 SYSCFG_PAD_MCASP2_AXR6
#ifndef PIN_FUNCTION_B17_DIO
#define PIN_FUNCTION_B17_DIO 14UL
#endif
#ifndef PIN_B17_GPIO
#define PIN_B17_GPIO 2u
#define PIN_B17_GPIO_PIN 29u
#endif

/* Ball: A17 */
#define PIN_CTRL_REG_ADDR_A17 SYSCFG_PAD_MCASP2_AXR7
#ifndef PIN_FUNCTION_A17_DIO
#define PIN_FUNCTION_A17_DIO 14UL
#endif
#ifndef PIN_A17_GPIO
#define PIN_A17_GPIO 1u
#define PIN_A17_GPIO_PIN 5u
#endif

/* Ball: B18 */
#define PIN_CTRL_REG_ADDR_B18 SYSCFG_PAD_MCASP3_ACLKX
#ifndef PIN_FUNCTION_B18_UART7
#define PIN_FUNCTION_B18_UART7 3UL
#endif
#ifndef PIN_FUNCTION_B18_DIO
#define PIN_FUNCTION_B18_DIO 14UL
#endif
#ifndef PIN_B18_GPIO
#define PIN_B18_GPIO 5u
#define PIN_B18_GPIO_PIN 13u
#endif

/* Ball: B19 */
#define PIN_CTRL_REG_ADDR_B19 SYSCFG_PAD_MCASP3_AXR0
#ifndef PIN_FUNCTION_B19_UART7
#define PIN_FUNCTION_B19_UART7 3UL
#endif
#ifndef PIN_FUNCTION_B19_UART5
#define PIN_FUNCTION_B19_UART5 4UL
#endif

/* Ball: C17 */
#define PIN_CTRL_REG_ADDR_C17 SYSCFG_PAD_MCASP3_AXR1
#ifndef PIN_FUNCTION_C17_UART7
#define PIN_FUNCTION_C17_UART7 3UL
#endif
#ifndef PIN_FUNCTION_C17_UART5
#define PIN_FUNCTION_C17_UART5 4UL
#endif

/* Ball: F15 */
#define PIN_CTRL_REG_ADDR_F15 SYSCFG_PAD_MCASP3_FSX
#ifndef PIN_FUNCTION_F15_UART7
#define PIN_FUNCTION_F15_UART7 3UL
#endif
#ifndef PIN_FUNCTION_F15_DIO
#define PIN_FUNCTION_F15_DIO 14UL
#endif
#ifndef PIN_F15_GPIO
#define PIN_F15_GPIO 5u
#define PIN_F15_GPIO_PIN 14u
#endif

/* Ball: C18 */
#define PIN_CTRL_REG_ADDR_C18 SYSCFG_PAD_MCASP4_ACLKX
#ifndef PIN_FUNCTION_C18_SPI3
#define PIN_FUNCTION_C18_SPI3 2UL
#endif
#ifndef PIN_FUNCTION_C18_UART8
#define PIN_FUNCTION_C18_UART8 3UL
#endif
#ifndef PIN_FUNCTION_C18_I2C4
#define PIN_FUNCTION_C18_I2C4 4UL
#endif

/* Ball: G16 */
#define PIN_CTRL_REG_ADDR_G16 SYSCFG_PAD_MCASP4_AXR0
#ifndef PIN_FUNCTION_G16_SPI3
#define PIN_FUNCTION_G16_SPI3 2UL
#endif
#ifndef PIN_FUNCTION_G16_UART8
#define PIN_FUNCTION_G16_UART8 3UL
#endif
#ifndef PIN_FUNCTION_G16_UART4
#define PIN_FUNCTION_G16_UART4 4UL
#endif

/* Ball: D17 */
#define PIN_CTRL_REG_ADDR_D17 SYSCFG_PAD_MCASP4_AXR1
#ifndef PIN_FUNCTION_D17_SPI3
#define PIN_FUNCTION_D17_SPI3 2UL
#endif
#ifndef PIN_FUNCTION_D17_UART8
#define PIN_FUNCTION_D17_UART8 3UL
#endif
#ifndef PIN_FUNCTION_D17_UART4
#define PIN_FUNCTION_D17_UART4 4UL
#endif

/* Ball: A21 */
#define PIN_CTRL_REG_ADDR_A21 SYSCFG_PAD_MCASP4_FSX
#ifndef PIN_FUNCTION_A21_SPI3
#define PIN_FUNCTION_A21_SPI3 2UL
#endif
#ifndef PIN_FUNCTION_A21_UART8
#define PIN_FUNCTION_A21_UART8 3UL
#endif
#ifndef PIN_FUNCTION_A21_I2C4
#define PIN_FUNCTION_A21_I2C4 4UL
#endif

/* Ball: AA3 */
#define PIN_CTRL_REG_ADDR_AA3 SYSCFG_PAD_MCASP5_ACLKX
#ifndef PIN_FUNCTION_AA3_SPI4
#define PIN_FUNCTION_AA3_SPI4 2UL
#endif
#ifndef PIN_FUNCTION_AA3_UART9
#define PIN_FUNCTION_AA3_UART9 3UL
#endif
#ifndef PIN_FUNCTION_AA3_I2C5
#define PIN_FUNCTION_AA3_I2C5 4UL
#endif

/* Ball: AB3 */
#define PIN_CTRL_REG_ADDR_AB3 SYSCFG_PAD_MCASP5_AXR0
#ifndef PIN_FUNCTION_AB3_SPI4
#define PIN_FUNCTION_AB3_SPI4 2UL
#endif
#ifndef PIN_FUNCTION_AB3_UART9
#define PIN_FUNCTION_AB3_UART9 3UL
#endif
#ifndef PIN_FUNCTION_AB3_UART3
#define PIN_FUNCTION_AB3_UART3 4UL
#endif

/* Ball: AA4 */
#define PIN_CTRL_REG_ADDR_AA4 SYSCFG_PAD_MCASP5_AXR1
#ifndef PIN_FUNCTION_AA4_SPI4
#define PIN_FUNCTION_AA4_SPI4 2UL
#endif
#ifndef PIN_FUNCTION_AA4_UART9
#define PIN_FUNCTION_AA4_UART9 3UL
#endif
#ifndef PIN_FUNCTION_AA4_UART3
#define PIN_FUNCTION_AA4_UART3 4UL
#endif

/* Ball: AB9 */
#define PIN_CTRL_REG_ADDR_AB9 SYSCFG_PAD_MCASP5_FSX
#ifndef PIN_FUNCTION_AB9_SPI4
#define PIN_FUNCTION_AB9_SPI4 2UL
#endif
#ifndef PIN_FUNCTION_AB9_UART9
#define PIN_FUNCTION_AB9_UART9 3UL
#endif
#ifndef PIN_FUNCTION_AB9_I2C5
#define PIN_FUNCTION_AB9_I2C5 4UL
#endif

/* Ball: U4 */
#define PIN_CTRL_REG_ADDR_U4 SYSCFG_PAD_MDIO_D
#ifndef PIN_FUNCTION_U4_ETH_MDIO
#define PIN_FUNCTION_U4_ETH_MDIO 0UL
#endif
#ifndef PIN_FUNCTION_U4_UART3
#define PIN_FUNCTION_U4_UART3 1UL
#endif
#ifndef PIN_FUNCTION_U4_ETH_MII
#define PIN_FUNCTION_U4_ETH_MII 3UL
#endif
#ifndef PIN_FUNCTION_U4_DIO
#define PIN_FUNCTION_U4_DIO 14UL
#endif
#ifndef PIN_U4_GPIO
#define PIN_U4_GPIO 5u
#define PIN_U4_GPIO_PIN 16u
#endif

/* Ball: V1 */
#define PIN_CTRL_REG_ADDR_V1 SYSCFG_PAD_MDIO_MCLK
#ifndef PIN_FUNCTION_V1_ETH_MDIO
#define PIN_FUNCTION_V1_ETH_MDIO 0UL
#endif
#ifndef PIN_FUNCTION_V1_UART3
#define PIN_FUNCTION_V1_UART3 1UL
#endif
#ifndef PIN_FUNCTION_V1_ETH_MII
#define PIN_FUNCTION_V1_ETH_MII 3UL
#endif
#ifndef PIN_FUNCTION_V1_DIO
#define PIN_FUNCTION_V1_DIO 14UL
#endif
#ifndef PIN_V1_GPIO
#define PIN_V1_GPIO 5u
#define PIN_V1_GPIO_PIN 15u
#endif

/* Ball: W6 */
#define PIN_CTRL_REG_ADDR_W6 SYSCFG_PAD_MMC1_CLK
#ifndef PIN_FUNCTION_W6_DIO
#define PIN_FUNCTION_W6_DIO 14UL
#endif
#ifndef PIN_W6_GPIO
#define PIN_W6_GPIO 6u
#define PIN_W6_GPIO_PIN 21u
#endif

/* Ball: Y6 */
#define PIN_CTRL_REG_ADDR_Y6 SYSCFG_PAD_MMC1_CMD
#ifndef PIN_FUNCTION_Y6_DIO
#define PIN_FUNCTION_Y6_DIO 14UL
#endif
#ifndef PIN_Y6_GPIO
#define PIN_Y6_GPIO 6u
#define PIN_Y6_GPIO_PIN 22u
#endif

/* Ball: AA6 */
#define PIN_CTRL_REG_ADDR_AA6 SYSCFG_PAD_MMC1_DAT0
#ifndef PIN_FUNCTION_AA6_DIO
#define PIN_FUNCTION_AA6_DIO 14UL
#endif
#ifndef PIN_AA6_GPIO
#define PIN_AA6_GPIO 6u
#define PIN_AA6_GPIO_PIN 23u
#endif

/* Ball: Y4 */
#define PIN_CTRL_REG_ADDR_Y4 SYSCFG_PAD_MMC1_DAT1
#ifndef PIN_FUNCTION_Y4_DIO
#define PIN_FUNCTION_Y4_DIO 14UL
#endif
#ifndef PIN_Y4_GPIO
#define PIN_Y4_GPIO 6u
#define PIN_Y4_GPIO_PIN 24u
#endif

/* Ball: AA5 */
#define PIN_CTRL_REG_ADDR_AA5 SYSCFG_PAD_MMC1_DAT2
#ifndef PIN_FUNCTION_AA5_DIO
#define PIN_FUNCTION_AA5_DIO 14UL
#endif
#ifndef PIN_AA5_GPIO
#define PIN_AA5_GPIO 6u
#define PIN_AA5_GPIO_PIN 25u
#endif

/* Ball: Y3 */
#define PIN_CTRL_REG_ADDR_Y3 SYSCFG_PAD_MMC1_DAT3
#ifndef PIN_FUNCTION_Y3_DIO
#define PIN_FUNCTION_Y3_DIO 14UL
#endif
#ifndef PIN_Y3_GPIO
#define PIN_Y3_GPIO 6u
#define PIN_Y3_GPIO_PIN 26u
#endif

/* Ball: W7 */
#define PIN_CTRL_REG_ADDR_W7 SYSCFG_PAD_MMC1_SDCD
#ifndef PIN_FUNCTION_W7_UART6
#define PIN_FUNCTION_W7_UART6 3UL
#endif
#ifndef PIN_FUNCTION_W7_I2C4
#define PIN_FUNCTION_W7_I2C4 4UL
#endif
#ifndef PIN_FUNCTION_W7_DIO
#define PIN_FUNCTION_W7_DIO 14UL
#endif
#ifndef PIN_W7_GPIO
#define PIN_W7_GPIO 6u
#define PIN_W7_GPIO_PIN 27u
#endif

/* Ball: Y9 */
#define PIN_CTRL_REG_ADDR_Y9 SYSCFG_PAD_MMC1_SDWP
#ifndef PIN_FUNCTION_Y9_UART6
#define PIN_FUNCTION_Y9_UART6 3UL
#endif
#ifndef PIN_FUNCTION_Y9_I2C4
#define PIN_FUNCTION_Y9_I2C4 4UL
#endif
#ifndef PIN_FUNCTION_Y9_DIO
#define PIN_FUNCTION_Y9_DIO 14UL
#endif
#ifndef PIN_Y9_GPIO
#define PIN_Y9_GPIO 6u
#define PIN_Y9_GPIO_PIN 28u
#endif

/* Ball: AD4 */
#define PIN_CTRL_REG_ADDR_AD4 SYSCFG_PAD_MMC3_CLK
#ifndef PIN_FUNCTION_AD4_PWM
#define PIN_FUNCTION_AD4_PWM 10UL
#endif
#ifndef PIN_FUNCTION_AD4_DIO
#define PIN_FUNCTION_AD4_DIO 14UL
#endif
#ifndef PIN_AD4_GPIO
#define PIN_AD4_GPIO 6u
#define PIN_AD4_GPIO_PIN 29u
#endif

/* Ball: AC4 */
#define PIN_CTRL_REG_ADDR_AC4 SYSCFG_PAD_MMC3_CMD
#ifndef PIN_FUNCTION_AC4_SPI3
#define PIN_FUNCTION_AC4_SPI3 1UL
#endif
#ifndef PIN_FUNCTION_AC4_DIO
#define PIN_FUNCTION_AC4_DIO 14UL
#endif
#ifndef PIN_AC4_GPIO
#define PIN_AC4_GPIO 6u
#define PIN_AC4_GPIO_PIN 30u
#endif

/* Ball: AC7 */
#define PIN_CTRL_REG_ADDR_AC7 SYSCFG_PAD_MMC3_DAT0
#ifndef PIN_FUNCTION_AC7_SPI3
#define PIN_FUNCTION_AC7_SPI3 1UL
#endif
#ifndef PIN_FUNCTION_AC7_UART5
#define PIN_FUNCTION_AC7_UART5 2UL
#endif
#ifndef PIN_FUNCTION_AC7_DIO
#define PIN_FUNCTION_AC7_DIO 14UL
#endif
#ifndef PIN_AC7_GPIO
#define PIN_AC7_GPIO 6u
#define PIN_AC7_GPIO_PIN 31u
#endif

/* Ball: AC6 */
#define PIN_CTRL_REG_ADDR_AC6 SYSCFG_PAD_MMC3_DAT1
#ifndef PIN_FUNCTION_AC6_SPI3
#define PIN_FUNCTION_AC6_SPI3 1UL
#endif
#ifndef PIN_FUNCTION_AC6_UART5
#define PIN_FUNCTION_AC6_UART5 2UL
#endif
#ifndef PIN_FUNCTION_AC6_DIO
#define PIN_FUNCTION_AC6_DIO 14UL
#endif
#ifndef PIN_AC6_GPIO
#define PIN_AC6_GPIO 7u
#define PIN_AC6_GPIO_PIN 0u
#endif

/* Ball: AC9 */
#define PIN_CTRL_REG_ADDR_AC9 SYSCFG_PAD_MMC3_DAT2
#ifndef PIN_FUNCTION_AC9_SPI3
#define PIN_FUNCTION_AC9_SPI3 1UL
#endif
#ifndef PIN_FUNCTION_AC9_UART5
#define PIN_FUNCTION_AC9_UART5 2UL
#endif
#ifndef PIN_FUNCTION_AC9_DIO
#define PIN_FUNCTION_AC9_DIO 14UL
#endif
#ifndef PIN_AC9_GPIO
#define PIN_AC9_GPIO 7u
#define PIN_AC9_GPIO_PIN 1u
#endif

/* Ball: AC3 */
#define PIN_CTRL_REG_ADDR_AC3 SYSCFG_PAD_MMC3_DAT3
#ifndef PIN_FUNCTION_AC3_SPI3
#define PIN_FUNCTION_AC3_SPI3 1UL
#endif
#ifndef PIN_FUNCTION_AC3_UART5
#define PIN_FUNCTION_AC3_UART5 2UL
#endif
#ifndef PIN_FUNCTION_AC3_DIO
#define PIN_FUNCTION_AC3_DIO 14UL
#endif
#ifndef PIN_AC3_GPIO
#define PIN_AC3_GPIO 7u
#define PIN_AC3_GPIO_PIN 2u
#endif

/* Ball: AC8 */
#define PIN_CTRL_REG_ADDR_AC8 SYSCFG_PAD_MMC3_DAT4
#ifndef PIN_FUNCTION_AC8_SPI4
#define PIN_FUNCTION_AC8_SPI4 1UL
#endif
#ifndef PIN_FUNCTION_AC8_UART10
#define PIN_FUNCTION_AC8_UART10 2UL
#endif
#ifndef PIN_FUNCTION_AC8_PWM
#define PIN_FUNCTION_AC8_PWM 10UL
#endif
#ifndef PIN_FUNCTION_AC8_DIO
#define PIN_FUNCTION_AC8_DIO 14UL
#endif
#ifndef PIN_AC8_GPIO
#define PIN_AC8_GPIO 1u
#define PIN_AC8_GPIO_PIN 22u
#endif

/* Ball: AD6 */
#define PIN_CTRL_REG_ADDR_AD6 SYSCFG_PAD_MMC3_DAT5
#ifndef PIN_FUNCTION_AD6_SPI4
#define PIN_FUNCTION_AD6_SPI4 1UL
#endif
#ifndef PIN_FUNCTION_AD6_UART10
#define PIN_FUNCTION_AD6_UART10 2UL
#endif
#ifndef PIN_FUNCTION_AD6_PWM
#define PIN_FUNCTION_AD6_PWM 10UL
#endif
#ifndef PIN_FUNCTION_AD6_DIO
#define PIN_FUNCTION_AD6_DIO 14UL
#endif
#ifndef PIN_AD6_GPIO
#define PIN_AD6_GPIO 1u
#define PIN_AD6_GPIO_PIN 23u
#endif

/* Ball: AB8 */
#define PIN_CTRL_REG_ADDR_AB8 SYSCFG_PAD_MMC3_DAT6
#ifndef PIN_FUNCTION_AB8_SPI4
#define PIN_FUNCTION_AB8_SPI4 1UL
#endif
#ifndef PIN_FUNCTION_AB8_UART10
#define PIN_FUNCTION_AB8_UART10 2UL
#endif
#ifndef PIN_FUNCTION_AB8_PWM
#define PIN_FUNCTION_AB8_PWM 10UL
#endif
#ifndef PIN_FUNCTION_AB8_DIO
#define PIN_FUNCTION_AB8_DIO 14UL
#endif
#ifndef PIN_AB8_GPIO
#define PIN_AB8_GPIO 1u
#define PIN_AB8_GPIO_PIN 24u
#endif

/* Ball: AB5 */
#define PIN_CTRL_REG_ADDR_AB5 SYSCFG_PAD_MMC3_DAT7
#ifndef PIN_FUNCTION_AB5_SPI4
#define PIN_FUNCTION_AB5_SPI4 1UL
#endif
#ifndef PIN_FUNCTION_AB5_UART10
#define PIN_FUNCTION_AB5_UART10 2UL
#endif
#ifndef PIN_FUNCTION_AB5_DIO
#define PIN_FUNCTION_AB5_DIO 14UL
#endif
#ifndef PIN_AB5_GPIO
#define PIN_AB5_GPIO 1u
#define PIN_AB5_GPIO_PIN 25u
#endif

/* Ball: U5 */
#define PIN_CTRL_REG_ADDR_U5 SYSCFG_PAD_RGMII0_RXC
#ifndef PIN_FUNCTION_U5_ETH_RGMII
#define PIN_FUNCTION_U5_ETH_RGMII 0UL
#endif
#ifndef PIN_FUNCTION_U5_ETH_RMII
#define PIN_FUNCTION_U5_ETH_RMII 2UL
#endif
#ifndef PIN_FUNCTION_U5_ETH_MII
#define PIN_FUNCTION_U5_ETH_MII 3UL
#endif
#ifndef PIN_FUNCTION_U5_DIO
#define PIN_FUNCTION_U5_DIO 14UL
#endif
#ifndef PIN_U5_GPIO
#define PIN_U5_GPIO 5u
#define PIN_U5_GPIO_PIN 26u
#endif

/* Ball: V5 */
#define PIN_CTRL_REG_ADDR_V5 SYSCFG_PAD_RGMII0_RXCTL
#ifndef PIN_FUNCTION_V5_ETH_RGMII
#define PIN_FUNCTION_V5_ETH_RGMII 0UL
#endif
#ifndef PIN_FUNCTION_V5_ETH_RMII
#define PIN_FUNCTION_V5_ETH_RMII 2UL
#endif
#ifndef PIN_FUNCTION_V5_ETH_MII
#define PIN_FUNCTION_V5_ETH_MII 3UL
#endif
#ifndef PIN_FUNCTION_V5_DIO
#define PIN_FUNCTION_V5_DIO 14UL
#endif
#ifndef PIN_V5_GPIO
#define PIN_V5_GPIO 5u
#define PIN_V5_GPIO_PIN 27u
#endif

/* Ball: W2 */
#define PIN_CTRL_REG_ADDR_W2 SYSCFG_PAD_RGMII0_RXD0
#ifndef PIN_FUNCTION_W2_ETH_RGMII
#define PIN_FUNCTION_W2_ETH_RGMII 0UL
#endif
#ifndef PIN_FUNCTION_W2_ETH_RMII
#define PIN_FUNCTION_W2_ETH_RMII 1UL
#endif
#ifndef PIN_FUNCTION_W2_ETH_MII
#define PIN_FUNCTION_W2_ETH_MII 3UL
#endif
#ifndef PIN_FUNCTION_W2_DIO
#define PIN_FUNCTION_W2_DIO 14UL
#endif
#ifndef PIN_W2_GPIO
#define PIN_W2_GPIO 5u
#define PIN_W2_GPIO_PIN 31u
#endif

/* Ball: Y2 */
#define PIN_CTRL_REG_ADDR_Y2 SYSCFG_PAD_RGMII0_RXD1
#ifndef PIN_FUNCTION_Y2_ETH_RGMII
#define PIN_FUNCTION_Y2_ETH_RGMII 0UL
#endif
#ifndef PIN_FUNCTION_Y2_ETH_RMII
#define PIN_FUNCTION_Y2_ETH_RMII 1UL
#endif
#ifndef PIN_FUNCTION_Y2_ETH_MII
#define PIN_FUNCTION_Y2_ETH_MII 3UL
#endif
#ifndef PIN_FUNCTION_Y2_DIO
#define PIN_FUNCTION_Y2_DIO 14UL
#endif
#ifndef PIN_Y2_GPIO
#define PIN_Y2_GPIO 5u
#define PIN_Y2_GPIO_PIN 30u
#endif

/* Ball: V3 */
#define PIN_CTRL_REG_ADDR_V3 SYSCFG_PAD_RGMII0_RXD2
#ifndef PIN_FUNCTION_V3_ETH_RGMII
#define PIN_FUNCTION_V3_ETH_RGMII 0UL
#endif
#ifndef PIN_FUNCTION_V3_ETH_RMII
#define PIN_FUNCTION_V3_ETH_RMII 1UL
#endif
#ifndef PIN_FUNCTION_V3_ETH_MII
#define PIN_FUNCTION_V3_ETH_MII 3UL
#endif
#ifndef PIN_FUNCTION_V3_DIO
#define PIN_FUNCTION_V3_DIO 14UL
#endif
#ifndef PIN_V3_GPIO
#define PIN_V3_GPIO 5u
#define PIN_V3_GPIO_PIN 29u
#endif

/* Ball: V4 */
#define PIN_CTRL_REG_ADDR_V4 SYSCFG_PAD_RGMII0_RXD3
#ifndef PIN_FUNCTION_V4_ETH_RGMII
#define PIN_FUNCTION_V4_ETH_RGMII 0UL
#endif
#ifndef PIN_FUNCTION_V4_ETH_RMII
#define PIN_FUNCTION_V4_ETH_RMII 2UL
#endif
#ifndef PIN_FUNCTION_V4_ETH_MII
#define PIN_FUNCTION_V4_ETH_MII 3UL
#endif
#ifndef PIN_FUNCTION_V4_DIO
#define PIN_FUNCTION_V4_DIO 14UL
#endif
#ifndef PIN_V4_GPIO
#define PIN_V4_GPIO 5u
#define PIN_V4_GPIO_PIN 28u
#endif

/* Ball: W9 */
#define PIN_CTRL_REG_ADDR_W9 SYSCFG_PAD_RGMII0_TXC
#ifndef PIN_FUNCTION_W9_ETH_RGMII
#define PIN_FUNCTION_W9_ETH_RGMII 0UL
#endif
#ifndef PIN_FUNCTION_W9_UART3
#define PIN_FUNCTION_W9_UART3 1UL
#endif
#ifndef PIN_FUNCTION_W9_ETH_RMII
#define PIN_FUNCTION_W9_ETH_RMII 2UL
#endif
#ifndef PIN_FUNCTION_W9_ETH_MII
#define PIN_FUNCTION_W9_ETH_MII 3UL
#endif
#ifndef PIN_FUNCTION_W9_SPI3
#define PIN_FUNCTION_W9_SPI3 7UL
#endif
#ifndef PIN_FUNCTION_W9_SPI4
#define PIN_FUNCTION_W9_SPI4 8UL
#endif
#ifndef PIN_FUNCTION_W9_DIO
#define PIN_FUNCTION_W9_DIO 14UL
#endif
#ifndef PIN_W9_GPIO
#define PIN_W9_GPIO 5u
#define PIN_W9_GPIO_PIN 20u
#endif

/* Ball: V9 */
#define PIN_CTRL_REG_ADDR_V9 SYSCFG_PAD_RGMII0_TXCTL
#ifndef PIN_FUNCTION_V9_ETH_RGMII
#define PIN_FUNCTION_V9_ETH_RGMII 0UL
#endif
#ifndef PIN_FUNCTION_V9_UART3
#define PIN_FUNCTION_V9_UART3 1UL
#endif
#ifndef PIN_FUNCTION_V9_ETH_RMII
#define PIN_FUNCTION_V9_ETH_RMII 2UL
#endif
#ifndef PIN_FUNCTION_V9_ETH_MII
#define PIN_FUNCTION_V9_ETH_MII 3UL
#endif
#ifndef PIN_FUNCTION_V9_SPI3
#define PIN_FUNCTION_V9_SPI3 7UL
#endif
#ifndef PIN_FUNCTION_V9_SPI4
#define PIN_FUNCTION_V9_SPI4 8UL
#endif
#ifndef PIN_FUNCTION_V9_DIO
#define PIN_FUNCTION_V9_DIO 14UL
#endif
#ifndef PIN_V9_GPIO
#define PIN_V9_GPIO 5u
#define PIN_V9_GPIO_PIN 21u
#endif

/* Ball: U6 */
#define PIN_CTRL_REG_ADDR_U6 SYSCFG_PAD_RGMII0_TXD0
#ifndef PIN_FUNCTION_U6_ETH_RGMII
#define PIN_FUNCTION_U6_ETH_RGMII 0UL
#endif
#ifndef PIN_FUNCTION_U6_ETH_RMII
#define PIN_FUNCTION_U6_ETH_RMII 1UL
#endif
#ifndef PIN_FUNCTION_U6_ETH_MII
#define PIN_FUNCTION_U6_ETH_MII 3UL
#endif
#ifndef PIN_FUNCTION_U6_SPI4
#define PIN_FUNCTION_U6_SPI4 7UL
#endif
#ifndef PIN_FUNCTION_U6_UART4
#define PIN_FUNCTION_U6_UART4 8UL
#endif
#ifndef PIN_FUNCTION_U6_DIO
#define PIN_FUNCTION_U6_DIO 14UL
#endif
#ifndef PIN_U6_GPIO
#define PIN_U6_GPIO 5u
#define PIN_U6_GPIO_PIN 25u
#endif

/* Ball: V6 */
#define PIN_CTRL_REG_ADDR_V6 SYSCFG_PAD_RGMII0_TXD1
#ifndef PIN_FUNCTION_V6_ETH_RGMII
#define PIN_FUNCTION_V6_ETH_RGMII 0UL
#endif
#ifndef PIN_FUNCTION_V6_ETH_RMII
#define PIN_FUNCTION_V6_ETH_RMII 1UL
#endif
#ifndef PIN_FUNCTION_V6_ETH_MII
#define PIN_FUNCTION_V6_ETH_MII 3UL
#endif
#ifndef PIN_FUNCTION_V6_SPI4
#define PIN_FUNCTION_V6_SPI4 7UL
#endif
#ifndef PIN_FUNCTION_V6_UART4
#define PIN_FUNCTION_V6_UART4 8UL
#endif
#ifndef PIN_FUNCTION_V6_DIO
#define PIN_FUNCTION_V6_DIO 14UL
#endif
#ifndef PIN_V6_GPIO
#define PIN_V6_GPIO 5u
#define PIN_V6_GPIO_PIN 24u
#endif

/* Ball: U7 */
#define PIN_CTRL_REG_ADDR_U7 SYSCFG_PAD_RGMII0_TXD2
#ifndef PIN_FUNCTION_U7_ETH_RGMII
#define PIN_FUNCTION_U7_ETH_RGMII 0UL
#endif
#ifndef PIN_FUNCTION_U7_ETH_RMII
#define PIN_FUNCTION_U7_ETH_RMII 1UL
#endif
#ifndef PIN_FUNCTION_U7_ETH_MII
#define PIN_FUNCTION_U7_ETH_MII 3UL
#endif
#ifndef PIN_FUNCTION_U7_SPI4
#define PIN_FUNCTION_U7_SPI4 7UL
#endif
#ifndef PIN_FUNCTION_U7_UART4
#define PIN_FUNCTION_U7_UART4 8UL
#endif
#ifndef PIN_FUNCTION_U7_DIO
#define PIN_FUNCTION_U7_DIO 14UL
#endif
#ifndef PIN_U7_GPIO
#define PIN_U7_GPIO 5u
#define PIN_U7_GPIO_PIN 23u
#endif

/* Ball: V7 */
#define PIN_CTRL_REG_ADDR_V7 SYSCFG_PAD_RGMII0_TXD3
#ifndef PIN_FUNCTION_V7_ETH_RGMII
#define PIN_FUNCTION_V7_ETH_RGMII 0UL
#endif
#ifndef PIN_FUNCTION_V7_ETH_RMII
#define PIN_FUNCTION_V7_ETH_RMII 1UL
#endif
#ifndef PIN_FUNCTION_V7_ETH_MII
#define PIN_FUNCTION_V7_ETH_MII 3UL
#endif
#ifndef PIN_FUNCTION_V7_SPI4
#define PIN_FUNCTION_V7_SPI4 7UL
#endif
#ifndef PIN_FUNCTION_V7_UART4
#define PIN_FUNCTION_V7_UART4 8UL
#endif
#ifndef PIN_FUNCTION_V7_DIO
#define PIN_FUNCTION_V7_DIO 14UL
#endif
#ifndef PIN_V7_GPIO
#define PIN_V7_GPIO 5u
#define PIN_V7_GPIO_PIN 22u
#endif

/* Ball: U3 */
#define PIN_CTRL_REG_ADDR_U3 SYSCFG_PAD_RMII_MHZ_50_CLK
#ifndef PIN_FUNCTION_U3_ETH_RMII
#define PIN_FUNCTION_U3_ETH_RMII 0UL
#endif
#ifndef PIN_FUNCTION_U3_DIO
#define PIN_FUNCTION_U3_DIO 14UL
#endif
#ifndef PIN_U3_GPIO
#define PIN_U3_GPIO 5u
#define PIN_U3_GPIO_PIN 17u
#endif

/* Ball: E18 */
#define PIN_CTRL_REG_ADDR_E18 SYSCFG_PAD_RTCK
#ifndef PIN_FUNCTION_E18_DIO
#define PIN_FUNCTION_E18_DIO 14UL
#endif
#ifndef PIN_E18_GPIO
#define PIN_E18_GPIO 8u
#define PIN_E18_GPIO_PIN 29u
#endif

/* Ball: A24 */
#define PIN_CTRL_REG_ADDR_A24 SYSCFG_PAD_SPI1_CS0
#ifndef PIN_FUNCTION_A24_SPI1
#define PIN_FUNCTION_A24_SPI1 0UL
#endif
#ifndef PIN_FUNCTION_A24_DIO
#define PIN_FUNCTION_A24_DIO 14UL
#endif
#ifndef PIN_A24_GPIO
#define PIN_A24_GPIO 7u
#define PIN_A24_GPIO_PIN 10u
#endif

/* Ball: A22 */
#define PIN_CTRL_REG_ADDR_A22 SYSCFG_PAD_SPI1_CS1
#ifndef PIN_FUNCTION_A22_SPI1
#define PIN_FUNCTION_A22_SPI1 0UL
#endif
#ifndef PIN_FUNCTION_A22_SPI2
#define PIN_FUNCTION_A22_SPI2 3UL
#endif
#ifndef PIN_FUNCTION_A22_DIO
#define PIN_FUNCTION_A22_DIO 14UL
#endif
#ifndef PIN_A22_GPIO
#define PIN_A22_GPIO 7u
#define PIN_A22_GPIO_PIN 11u
#endif

/* Ball: B21 */
#define PIN_CTRL_REG_ADDR_B21 SYSCFG_PAD_SPI1_CS2
#ifndef PIN_FUNCTION_B21_SPI1
#define PIN_FUNCTION_B21_SPI1 0UL
#endif
#ifndef PIN_FUNCTION_B21_UART4
#define PIN_FUNCTION_B21_UART4 1UL
#endif
#ifndef PIN_FUNCTION_B21_SPI2
#define PIN_FUNCTION_B21_SPI2 3UL
#endif
#ifndef PIN_FUNCTION_B21_CAN
#define PIN_FUNCTION_B21_CAN 4UL
#endif
#ifndef PIN_FUNCTION_B21_ETH_MDIO
#define PIN_FUNCTION_B21_ETH_MDIO 5UL
#endif
#ifndef PIN_FUNCTION_B21_DIO
#define PIN_FUNCTION_B21_DIO 14UL
#endif
#ifndef PIN_B21_GPIO
#define PIN_B21_GPIO 7u
#define PIN_B21_GPIO_PIN 12u
#endif

/* Ball: B20 */
#define PIN_CTRL_REG_ADDR_B20 SYSCFG_PAD_SPI1_CS3
#ifndef PIN_FUNCTION_B20_SPI1
#define PIN_FUNCTION_B20_SPI1 0UL
#endif
#ifndef PIN_FUNCTION_B20_UART4
#define PIN_FUNCTION_B20_UART4 1UL
#endif
#ifndef PIN_FUNCTION_B20_SPI2
#define PIN_FUNCTION_B20_SPI2 3UL
#endif
#ifndef PIN_FUNCTION_B20_CAN
#define PIN_FUNCTION_B20_CAN 4UL
#endif
#ifndef PIN_FUNCTION_B20_ETH_MDIO
#define PIN_FUNCTION_B20_ETH_MDIO 5UL
#endif
#ifndef PIN_FUNCTION_B20_DIO
#define PIN_FUNCTION_B20_DIO 14UL
#endif
#ifndef PIN_B20_GPIO
#define PIN_B20_GPIO 7u
#define PIN_B20_GPIO_PIN 13u
#endif

/* Ball: B25 */
#define PIN_CTRL_REG_ADDR_B25 SYSCFG_PAD_SPI1_D0
#ifndef PIN_FUNCTION_B25_SPI1
#define PIN_FUNCTION_B25_SPI1 0UL
#endif
#ifndef PIN_FUNCTION_B25_DIO
#define PIN_FUNCTION_B25_DIO 14UL
#endif
#ifndef PIN_B25_GPIO
#define PIN_B25_GPIO 7u
#define PIN_B25_GPIO_PIN 9u
#endif

/* Ball: F16 */
#define PIN_CTRL_REG_ADDR_F16 SYSCFG_PAD_SPI1_D1
#ifndef PIN_FUNCTION_F16_SPI1
#define PIN_FUNCTION_F16_SPI1 0UL
#endif
#ifndef PIN_FUNCTION_F16_DIO
#define PIN_FUNCTION_F16_DIO 14UL
#endif
#ifndef PIN_F16_GPIO
#define PIN_F16_GPIO 7u
#define PIN_F16_GPIO_PIN 8u
#endif

/* Ball: A25 */
#define PIN_CTRL_REG_ADDR_A25 SYSCFG_PAD_SPI1_SCLK
#ifndef PIN_FUNCTION_A25_SPI1
#define PIN_FUNCTION_A25_SPI1 0UL
#endif
#ifndef PIN_FUNCTION_A25_DIO
#define PIN_FUNCTION_A25_DIO 14UL
#endif
#ifndef PIN_A25_GPIO
#define PIN_A25_GPIO 7u
#define PIN_A25_GPIO_PIN 7u
#endif

/* Ball: B24 */
#define PIN_CTRL_REG_ADDR_B24 SYSCFG_PAD_SPI2_CS0
#ifndef PIN_FUNCTION_B24_SPI2
#define PIN_FUNCTION_B24_SPI2 0UL
#endif
#ifndef PIN_FUNCTION_B24_UART3
#define PIN_FUNCTION_B24_UART3 1UL
#endif
#ifndef PIN_FUNCTION_B24_UART5
#define PIN_FUNCTION_B24_UART5 2UL
#endif
#ifndef PIN_FUNCTION_B24_DIO
#define PIN_FUNCTION_B24_DIO 14UL
#endif
#ifndef PIN_B24_GPIO
#define PIN_B24_GPIO 7u
#define PIN_B24_GPIO_PIN 17u
#endif

/* Ball: G17 */
#define PIN_CTRL_REG_ADDR_G17 SYSCFG_PAD_SPI2_D0
#ifndef PIN_FUNCTION_G17_SPI2
#define PIN_FUNCTION_G17_SPI2 0UL
#endif
#ifndef PIN_FUNCTION_G17_UART3
#define PIN_FUNCTION_G17_UART3 1UL
#endif
#ifndef PIN_FUNCTION_G17_UART5
#define PIN_FUNCTION_G17_UART5 2UL
#endif
#ifndef PIN_FUNCTION_G17_DIO
#define PIN_FUNCTION_G17_DIO 14UL
#endif
#ifndef PIN_G17_GPIO
#define PIN_G17_GPIO 7u
#define PIN_G17_GPIO_PIN 16u
#endif

/* Ball: B22 */
#define PIN_CTRL_REG_ADDR_B22 SYSCFG_PAD_SPI2_D1
#ifndef PIN_FUNCTION_B22_SPI2
#define PIN_FUNCTION_B22_SPI2 0UL
#endif
#ifndef PIN_FUNCTION_B22_UART3
#define PIN_FUNCTION_B22_UART3 1UL
#endif
#ifndef PIN_FUNCTION_B22_DIO
#define PIN_FUNCTION_B22_DIO 14UL
#endif
#ifndef PIN_B22_GPIO
#define PIN_B22_GPIO 7u
#define PIN_B22_GPIO_PIN 15u
#endif

/* Ball: A26 */
#define PIN_CTRL_REG_ADDR_A26 SYSCFG_PAD_SPI2_SCLK
#ifndef PIN_FUNCTION_A26_SPI2
#define PIN_FUNCTION_A26_SPI2 0UL
#endif
#ifndef PIN_FUNCTION_A26_UART3
#define PIN_FUNCTION_A26_UART3 1UL
#endif
#ifndef PIN_FUNCTION_A26_DIO
#define PIN_FUNCTION_A26_DIO 14UL
#endif
#ifndef PIN_A26_GPIO
#define PIN_A26_GPIO 7u
#define PIN_A26_GPIO_PIN 14u
#endif

/* Ball: D23 */
#define PIN_CTRL_REG_ADDR_D23 SYSCFG_PAD_TDI
#ifndef PIN_FUNCTION_D23_DIO
#define PIN_FUNCTION_D23_DIO 14UL
#endif
#ifndef PIN_D23_GPIO
#define PIN_D23_GPIO 8u
#define PIN_D23_GPIO_PIN 27u
#endif

/* Ball: F19 */
#define PIN_CTRL_REG_ADDR_F19 SYSCFG_PAD_TDO
#ifndef PIN_FUNCTION_F19_DIO
#define PIN_FUNCTION_F19_DIO 14UL
#endif
#ifndef PIN_F19_GPIO
#define PIN_F19_GPIO 8u
#define PIN_F19_GPIO_PIN 28u
#endif

/* Ball: E25 */
#define PIN_CTRL_REG_ADDR_E25 SYSCFG_PAD_UART1_CTSN
#ifndef PIN_FUNCTION_E25_UART1
#define PIN_FUNCTION_E25_UART1 0UL
#endif
#ifndef PIN_FUNCTION_E25_UART9
#define PIN_FUNCTION_E25_UART9 2UL
#endif
#ifndef PIN_FUNCTION_E25_DIO
#define PIN_FUNCTION_E25_DIO 14UL
#endif
#ifndef PIN_E25_GPIO
#define PIN_E25_GPIO 7u
#define PIN_E25_GPIO_PIN 24u
#endif

/* Ball: C27 */
#define PIN_CTRL_REG_ADDR_C27 SYSCFG_PAD_UART1_RTSN
#ifndef PIN_FUNCTION_C27_UART1
#define PIN_FUNCTION_C27_UART1 0UL
#endif
#ifndef PIN_FUNCTION_C27_UART9
#define PIN_FUNCTION_C27_UART9 2UL
#endif
#ifndef PIN_FUNCTION_C27_DIO
#define PIN_FUNCTION_C27_DIO 14UL
#endif
#ifndef PIN_C27_GPIO
#define PIN_C27_GPIO 7u
#define PIN_C27_GPIO_PIN 25u
#endif

/* Ball: B27 */
#define PIN_CTRL_REG_ADDR_B27 SYSCFG_PAD_UART1_RXD
#ifndef PIN_FUNCTION_B27_UART1
#define PIN_FUNCTION_B27_UART1 0UL
#endif
#ifndef PIN_FUNCTION_B27_DIO
#define PIN_FUNCTION_B27_DIO 14UL
#endif
#ifndef PIN_B27_GPIO
#define PIN_B27_GPIO 7u
#define PIN_B27_GPIO_PIN 22u
#endif

/* Ball: C26 */
#define PIN_CTRL_REG_ADDR_C26 SYSCFG_PAD_UART1_TXD
#ifndef PIN_FUNCTION_C26_UART1
#define PIN_FUNCTION_C26_UART1 0UL
#endif
#ifndef PIN_FUNCTION_C26_DIO
#define PIN_FUNCTION_C26_DIO 14UL
#endif
#ifndef PIN_C26_GPIO
#define PIN_C26_GPIO 7u
#define PIN_C26_GPIO_PIN 23u
#endif

/* Ball: D27 */
#define PIN_CTRL_REG_ADDR_D27 SYSCFG_PAD_UART2_CTSN
#ifndef PIN_FUNCTION_D27_UART2
#define PIN_FUNCTION_D27_UART2 0UL
#endif
#ifndef PIN_FUNCTION_D27_UART3
#define PIN_FUNCTION_D27_UART3 2UL
#endif
#ifndef PIN_FUNCTION_D27_UART10
#define PIN_FUNCTION_D27_UART10 4UL
#endif
#ifndef PIN_FUNCTION_D27_UART1
#define PIN_FUNCTION_D27_UART1 5UL
#endif
#ifndef PIN_FUNCTION_D27_DIO
#define PIN_FUNCTION_D27_DIO 14UL
#endif
#ifndef PIN_D27_GPIO
#define PIN_D27_GPIO 1u
#define PIN_D27_GPIO_PIN 16u
#endif

/* Ball: C28 */
#define PIN_CTRL_REG_ADDR_C28 SYSCFG_PAD_UART2_RTSN
#ifndef PIN_FUNCTION_C28_UART2
#define PIN_FUNCTION_C28_UART2 0UL
#endif
#ifndef PIN_FUNCTION_C28_UART3
#define PIN_FUNCTION_C28_UART3 1UL
#endif
#ifndef PIN_FUNCTION_C28_UART3
#define PIN_FUNCTION_C28_UART3 2UL
#endif
#ifndef PIN_FUNCTION_C28_UART10
#define PIN_FUNCTION_C28_UART10 4UL
#endif
#ifndef PIN_FUNCTION_C28_UART1
#define PIN_FUNCTION_C28_UART1 5UL
#endif
#ifndef PIN_FUNCTION_C28_DIO
#define PIN_FUNCTION_C28_DIO 14UL
#endif
#ifndef PIN_C28_GPIO
#define PIN_C28_GPIO 1u
#define PIN_C28_GPIO_PIN 17u
#endif

/* Ball: D28 */
#define PIN_CTRL_REG_ADDR_D28 SYSCFG_PAD_UART3_CTSN
#ifndef PIN_FUNCTION_D28_UART3
#define PIN_FUNCTION_D28_UART3 1UL
#endif
#ifndef PIN_FUNCTION_D28_UART3
#define PIN_FUNCTION_D28_UART3 2UL
#endif
#ifndef PIN_FUNCTION_D28_UART2
#define PIN_FUNCTION_D28_UART2 4UL
#endif
#ifndef PIN_FUNCTION_D28_UART1
#define PIN_FUNCTION_D28_UART1 5UL
#endif
#ifndef PIN_FUNCTION_D28_DIO
#define PIN_FUNCTION_D28_DIO 14UL
#endif
#ifndef PIN_D28_GPIO
#define PIN_D28_GPIO 7u
#define PIN_D28_GPIO_PIN 26u
#endif

/* Ball: D26 */
#define PIN_CTRL_REG_ADDR_D26 SYSCFG_PAD_UART2_TXD
#ifndef PIN_FUNCTION_D26_UART2
#define PIN_FUNCTION_D26_UART2 0UL
#endif
#ifndef PIN_FUNCTION_D26_UART3
#define PIN_FUNCTION_D26_UART3 1UL
#endif
#ifndef PIN_FUNCTION_D26_UART3
#define PIN_FUNCTION_D26_UART3 2UL
#endif
#ifndef PIN_FUNCTION_D26_UART2
#define PIN_FUNCTION_D26_UART2 4UL
#endif
#ifndef PIN_FUNCTION_D26_UART1
#define PIN_FUNCTION_D26_UART1 5UL
#endif
#ifndef PIN_FUNCTION_D26_DIO
#define PIN_FUNCTION_D26_DIO 14UL
#endif
#ifndef PIN_D26_GPIO
#define PIN_D26_GPIO 7u
#define PIN_D26_GPIO_PIN 27u
#endif

/* Ball: V2 */
#define PIN_CTRL_REG_ADDR_V2 SYSCFG_PAD_UART3_RXD
#ifndef PIN_FUNCTION_V2_UART3
#define PIN_FUNCTION_V2_UART3 0UL
#endif
#ifndef PIN_FUNCTION_V2_ETH_RMII
#define PIN_FUNCTION_V2_ETH_RMII 2UL
#endif
#ifndef PIN_FUNCTION_V2_ETH_MII
#define PIN_FUNCTION_V2_ETH_MII 3UL
#endif
#ifndef PIN_FUNCTION_V2_SPI3
#define PIN_FUNCTION_V2_SPI3 7UL
#endif
#ifndef PIN_FUNCTION_V2_DIO
#define PIN_FUNCTION_V2_DIO 14UL
#endif
#ifndef PIN_V2_GPIO
#define PIN_V2_GPIO 5u
#define PIN_V2_GPIO_PIN 18u
#endif

/* Ball: Y1 */
#define PIN_CTRL_REG_ADDR_Y1 SYSCFG_PAD_UART3_TXD
#ifndef PIN_FUNCTION_Y1_UART3
#define PIN_FUNCTION_Y1_UART3 0UL
#endif
#ifndef PIN_FUNCTION_Y1_ETH_RMII
#define PIN_FUNCTION_Y1_ETH_RMII 2UL
#endif
#ifndef PIN_FUNCTION_Y1_ETH_MII
#define PIN_FUNCTION_Y1_ETH_MII 3UL
#endif
#ifndef PIN_FUNCTION_Y1_SPI3
#define PIN_FUNCTION_Y1_SPI3 7UL
#endif
#ifndef PIN_FUNCTION_Y1_SPI4
#define PIN_FUNCTION_Y1_SPI4 8UL
#endif
#ifndef PIN_FUNCTION_Y1_DIO
#define PIN_FUNCTION_Y1_DIO 14UL
#endif
#ifndef PIN_Y1_GPIO
#define PIN_Y1_GPIO 5u
#define PIN_Y1_GPIO_PIN 19u
#endif

/* Ball: AB10 */
#define PIN_CTRL_REG_ADDR_AB10 SYSCFG_PAD_USB1_DRVVBUS
#ifndef PIN_FUNCTION_AB10_PWM
#define PIN_FUNCTION_AB10_PWM 7UL
#endif
#ifndef PIN_FUNCTION_AB10_ICU
#define PIN_FUNCTION_AB10_ICU 7UL
#endif
#ifndef PIN_FUNCTION_AB10_DIO
#define PIN_FUNCTION_AB10_DIO 14UL
#endif
#ifndef PIN_AB10_GPIO
#define PIN_AB10_GPIO 6u
#define PIN_AB10_GPIO_PIN 12u
#endif

/* Ball: AC10 */
#define PIN_CTRL_REG_ADDR_AC10 SYSCFG_PAD_USB2_DRVVBUS
#ifndef PIN_FUNCTION_AC10_PWM
#define PIN_FUNCTION_AC10_PWM 7UL
#endif
#ifndef PIN_FUNCTION_AC10_ICU
#define PIN_FUNCTION_AC10_ICU 7UL
#endif
#ifndef PIN_FUNCTION_AC10_DIO
#define PIN_FUNCTION_AC10_DIO 14UL
#endif
#ifndef PIN_AC10_GPIO
#define PIN_AC10_GPIO 6u
#define PIN_AC10_GPIO_PIN 13u
#endif

/* Ball: AG8 */
#define PIN_CTRL_REG_ADDR_AG8 SYSCFG_PAD_VIN1A_CLK0
#ifndef PIN_FUNCTION_AG8_DIO
#define PIN_FUNCTION_AG8_DIO 14UL
#endif
#ifndef PIN_AG8_GPIO
#define PIN_AG8_GPIO 2u
#define PIN_AG8_GPIO_PIN 30u
#endif

/* Ball: AE8 */
#define PIN_CTRL_REG_ADDR_AE8 SYSCFG_PAD_VIN1A_D0
#ifndef PIN_FUNCTION_AE8_UART8
#define PIN_FUNCTION_AE8_UART8 5UL
#endif
#ifndef PIN_FUNCTION_AE8_PWM
#define PIN_FUNCTION_AE8_PWM 10UL
#endif
#ifndef PIN_FUNCTION_AE8_DIO
#define PIN_FUNCTION_AE8_DIO 14UL
#endif
#ifndef PIN_AE8_GPIO
#define PIN_AE8_GPIO 3u
#define PIN_AE8_GPIO_PIN 4u
#endif

/* Ball: AD8 */
#define PIN_CTRL_REG_ADDR_AD8 SYSCFG_PAD_VIN1A_D1
#ifndef PIN_FUNCTION_AD8_PWM
#define PIN_FUNCTION_AD8_PWM 10UL
#endif
#ifndef PIN_FUNCTION_AD8_DIO
#define PIN_FUNCTION_AD8_DIO 14UL
#endif
#ifndef PIN_AD8_GPIO
#define PIN_AD8_GPIO 3u
#define PIN_AD8_GPIO_PIN 5u
#endif

/* Ball: AG3 */
#define PIN_CTRL_REG_ADDR_AG3 SYSCFG_PAD_VIN1A_D10
#ifndef PIN_FUNCTION_AG3_DIO
#define PIN_FUNCTION_AG3_DIO 14UL
#endif
#ifndef PIN_AG3_GPIO
#define PIN_AG3_GPIO 3u
#define PIN_AG3_GPIO_PIN 14u
#endif

/* Ball: AG5 */
#define PIN_CTRL_REG_ADDR_AG5 SYSCFG_PAD_VIN1A_D11
#ifndef PIN_FUNCTION_AG5_DIO
#define PIN_FUNCTION_AG5_DIO 14UL
#endif
#ifndef PIN_AG5_GPIO
#define PIN_AG5_GPIO 3u
#define PIN_AG5_GPIO_PIN 15u
#endif

/* Ball: AF2 */
#define PIN_CTRL_REG_ADDR_AF2 SYSCFG_PAD_VIN1A_D12
#ifndef PIN_FUNCTION_AF2_DIO
#define PIN_FUNCTION_AF2_DIO 14UL
#endif
#ifndef PIN_AF2_GPIO
#define PIN_AF2_GPIO 3u
#define PIN_AF2_GPIO_PIN 16u
#endif

/* Ball: AF6 */
#define PIN_CTRL_REG_ADDR_AF6 SYSCFG_PAD_VIN1A_D13
#ifndef PIN_FUNCTION_AF6_DIO
#define PIN_FUNCTION_AF6_DIO 14UL
#endif
#ifndef PIN_AF6_GPIO
#define PIN_AF6_GPIO 3u
#define PIN_AF6_GPIO_PIN 17u
#endif

/* Ball: AF3 */
#define PIN_CTRL_REG_ADDR_AF3 SYSCFG_PAD_VIN1A_D14
#ifndef PIN_FUNCTION_AF3_DIO
#define PIN_FUNCTION_AF3_DIO 14UL
#endif
#ifndef PIN_AF3_GPIO
#define PIN_AF3_GPIO 3u
#define PIN_AF3_GPIO_PIN 18u
#endif

/* Ball: AF4 */
#define PIN_CTRL_REG_ADDR_AF4 SYSCFG_PAD_VIN1A_D15
#ifndef PIN_FUNCTION_AF4_DIO
#define PIN_FUNCTION_AF4_DIO 14UL
#endif
#ifndef PIN_AF4_GPIO
#define PIN_AF4_GPIO 3u
#define PIN_AF4_GPIO_PIN 19u
#endif

/* Ball: AF1 */
#define PIN_CTRL_REG_ADDR_AF1 SYSCFG_PAD_VIN1A_D16
#ifndef PIN_FUNCTION_AF1_DIO
#define PIN_FUNCTION_AF1_DIO 14UL
#endif
#ifndef PIN_AF1_GPIO
#define PIN_AF1_GPIO 3u
#define PIN_AF1_GPIO_PIN 20u
#endif

/* Ball: AE3 */
#define PIN_CTRL_REG_ADDR_AE3 SYSCFG_PAD_VIN1A_D17
#ifndef PIN_FUNCTION_AE3_DIO
#define PIN_FUNCTION_AE3_DIO 14UL
#endif
#ifndef PIN_AE3_GPIO
#define PIN_AE3_GPIO 3u
#define PIN_AE3_GPIO_PIN 21u
#endif

/* Ball: AE5 */
#define PIN_CTRL_REG_ADDR_AE5 SYSCFG_PAD_VIN1A_D18
#ifndef PIN_FUNCTION_AE5_DIO
#define PIN_FUNCTION_AE5_DIO 14UL
#endif
#ifndef PIN_AE5_GPIO
#define PIN_AE5_GPIO 3u
#define PIN_AE5_GPIO_PIN 22u
#endif

/* Ball: AE1 */
#define PIN_CTRL_REG_ADDR_AE1 SYSCFG_PAD_VIN1A_D19
#ifndef PIN_FUNCTION_AE1_DIO
#define PIN_FUNCTION_AE1_DIO 14UL
#endif
#ifndef PIN_AE1_GPIO
#define PIN_AE1_GPIO 3u
#define PIN_AE1_GPIO_PIN 23u
#endif

/* Ball: AG7 */
#define PIN_CTRL_REG_ADDR_AG7 SYSCFG_PAD_VIN1A_D2
#ifndef PIN_FUNCTION_AG7_UART8
#define PIN_FUNCTION_AG7_UART8 5UL
#endif
#ifndef PIN_FUNCTION_AG7_PWM
#define PIN_FUNCTION_AG7_PWM 10UL
#endif
#ifndef PIN_FUNCTION_AG7_DIO
#define PIN_FUNCTION_AG7_DIO 14UL
#endif
#ifndef PIN_AG7_GPIO
#define PIN_AG7_GPIO 3u
#define PIN_AG7_GPIO_PIN 6u
#endif

/* Ball: AE2 */
#define PIN_CTRL_REG_ADDR_AE2 SYSCFG_PAD_VIN1A_D20
#ifndef PIN_FUNCTION_AE2_DIO
#define PIN_FUNCTION_AE2_DIO 14UL
#endif
#ifndef PIN_AE2_GPIO
#define PIN_AE2_GPIO 3u
#define PIN_AE2_GPIO_PIN 24u
#endif

/* Ball: AE6 */
#define PIN_CTRL_REG_ADDR_AE6 SYSCFG_PAD_VIN1A_D21
#ifndef PIN_FUNCTION_AE6_DIO
#define PIN_FUNCTION_AE6_DIO 14UL
#endif
#ifndef PIN_AE6_GPIO
#define PIN_AE6_GPIO 3u
#define PIN_AE6_GPIO_PIN 25u
#endif

/* Ball: AD2 */
#define PIN_CTRL_REG_ADDR_AD2 SYSCFG_PAD_VIN1A_D22
#ifndef PIN_FUNCTION_AD2_DIO
#define PIN_FUNCTION_AD2_DIO 14UL
#endif
#ifndef PIN_AD2_GPIO
#define PIN_AD2_GPIO 3u
#define PIN_AD2_GPIO_PIN 26u
#endif

/* Ball: AD3 */
#define PIN_CTRL_REG_ADDR_AD3 SYSCFG_PAD_VIN1A_D23
#ifndef PIN_FUNCTION_AD3_DIO
#define PIN_FUNCTION_AD3_DIO 14UL
#endif
#ifndef PIN_AD3_GPIO
#define PIN_AD3_GPIO 3u
#define PIN_AD3_GPIO_PIN 27u
#endif

/* Ball: AH6 */
#define PIN_CTRL_REG_ADDR_AH6 SYSCFG_PAD_VIN1A_D3
#ifndef PIN_FUNCTION_AH6_UART8
#define PIN_FUNCTION_AH6_UART8 5UL
#endif
#ifndef PIN_FUNCTION_AH6_DIO
#define PIN_FUNCTION_AH6_DIO 14UL
#endif
#ifndef PIN_AH6_GPIO
#define PIN_AH6_GPIO 3u
#define PIN_AH6_GPIO_PIN 7u
#endif

/* Ball: AH3 */
#define PIN_CTRL_REG_ADDR_AH3 SYSCFG_PAD_VIN1A_D4
#ifndef PIN_FUNCTION_AH3_PWM
#define PIN_FUNCTION_AH3_PWM 10UL
#endif
#ifndef PIN_FUNCTION_AH3_DIO
#define PIN_FUNCTION_AH3_DIO 14UL
#endif
#ifndef PIN_AH3_GPIO
#define PIN_AH3_GPIO 3u
#define PIN_AH3_GPIO_PIN 8u
#endif

/* Ball: AH5 */
#define PIN_CTRL_REG_ADDR_AH5 SYSCFG_PAD_VIN1A_D5
#ifndef PIN_FUNCTION_AH5_PWM
#define PIN_FUNCTION_AH5_PWM 10UL
#endif
#ifndef PIN_FUNCTION_AH5_DIO
#define PIN_FUNCTION_AH5_DIO 14UL
#endif
#ifndef PIN_AH5_GPIO
#define PIN_AH5_GPIO 3u
#define PIN_AH5_GPIO_PIN 9u
#endif

/* Ball: AG6 */
#define PIN_CTRL_REG_ADDR_AG6 SYSCFG_PAD_VIN1A_D6
#ifndef PIN_FUNCTION_AG6_DIO
#define PIN_FUNCTION_AG6_DIO 14UL
#endif
#ifndef PIN_AG6_GPIO
#define PIN_AG6_GPIO 3u
#define PIN_AG6_GPIO_PIN 10u
#endif

/* Ball: AH4 */
#define PIN_CTRL_REG_ADDR_AH4 SYSCFG_PAD_VIN1A_D7
#ifndef PIN_FUNCTION_AH4_DIO
#define PIN_FUNCTION_AH4_DIO 14UL
#endif
#ifndef PIN_AH4_GPIO
#define PIN_AH4_GPIO 3u
#define PIN_AH4_GPIO_PIN 11u
#endif

/* Ball: AG4 */
#define PIN_CTRL_REG_ADDR_AG4 SYSCFG_PAD_VIN1A_D8
#ifndef PIN_FUNCTION_AG4_DIO
#define PIN_FUNCTION_AG4_DIO 14UL
#endif
#ifndef PIN_AG4_GPIO
#define PIN_AG4_GPIO 3u
#define PIN_AG4_GPIO_PIN 12u
#endif

/* Ball: AG2 */
#define PIN_CTRL_REG_ADDR_AG2 SYSCFG_PAD_VIN1A_D9
#ifndef PIN_FUNCTION_AG2_DIO
#define PIN_FUNCTION_AG2_DIO 14UL
#endif
#ifndef PIN_AG2_GPIO
#define PIN_AG2_GPIO 3u
#define PIN_AG2_GPIO_PIN 13u
#endif

/* Ball: AD9 */
#define PIN_CTRL_REG_ADDR_AD9 SYSCFG_PAD_VIN1A_DE0
#ifndef PIN_FUNCTION_AD9_UART7
#define PIN_FUNCTION_AD9_UART7 5UL
#endif
#ifndef PIN_FUNCTION_AD9_PWM
#define PIN_FUNCTION_AD9_PWM 7UL
#endif
#ifndef PIN_FUNCTION_AD9_ICU
#define PIN_FUNCTION_AD9_ICU 7UL
#endif
#ifndef PIN_FUNCTION_AD9_SPI3
#define PIN_FUNCTION_AD9_SPI3 8UL
#endif
#ifndef PIN_FUNCTION_AD9_DIO
#define PIN_FUNCTION_AD9_DIO 14UL
#endif
#ifndef PIN_AD9_GPIO
#define PIN_AD9_GPIO 3u
#define PIN_AD9_GPIO_PIN 0u
#endif

/* Ball: AF9 */
#define PIN_CTRL_REG_ADDR_AF9 SYSCFG_PAD_VIN1A_FLD0
#ifndef PIN_FUNCTION_AF9_UART7
#define PIN_FUNCTION_AF9_UART7 5UL
#endif
#ifndef PIN_FUNCTION_AF9_PWM
#define PIN_FUNCTION_AF9_PWM 7UL
#endif
#ifndef PIN_FUNCTION_AF9_ICU
#define PIN_FUNCTION_AF9_ICU 7UL
#endif
#ifndef PIN_FUNCTION_AF9_SPI3
#define PIN_FUNCTION_AF9_SPI3 8UL
#endif
#ifndef PIN_FUNCTION_AF9_DIO
#define PIN_FUNCTION_AF9_DIO 14UL
#endif
#ifndef PIN_AF9_GPIO
#define PIN_AF9_GPIO 3u
#define PIN_AF9_GPIO_PIN 1u
#endif

/* Ball: AE9 */
#define PIN_CTRL_REG_ADDR_AE9 SYSCFG_PAD_VIN1A_HSYNC0
#ifndef PIN_FUNCTION_AE9_UART7
#define PIN_FUNCTION_AE9_UART7 5UL
#endif
#ifndef PIN_FUNCTION_AE9_PWM
#define PIN_FUNCTION_AE9_PWM 7UL
#endif
#ifndef PIN_FUNCTION_AE9_ICU
#define PIN_FUNCTION_AE9_ICU 7UL
#endif
#ifndef PIN_FUNCTION_AE9_SPI3
#define PIN_FUNCTION_AE9_SPI3 8UL
#endif
#ifndef PIN_FUNCTION_AE9_DIO
#define PIN_FUNCTION_AE9_DIO 14UL
#endif
#ifndef PIN_AE9_GPIO
#define PIN_AE9_GPIO 3u
#define PIN_AE9_GPIO_PIN 2u
#endif

/* Ball: AF8 */
#define PIN_CTRL_REG_ADDR_AF8 SYSCFG_PAD_VIN1A_VSYNC0
#ifndef PIN_FUNCTION_AF8_UART7
#define PIN_FUNCTION_AF8_UART7 5UL
#endif
#ifndef PIN_FUNCTION_AF8_PWM
#define PIN_FUNCTION_AF8_PWM 7UL
#endif
#ifndef PIN_FUNCTION_AF8_ICU
#define PIN_FUNCTION_AF8_ICU 7UL
#endif
#ifndef PIN_FUNCTION_AF8_DIO
#define PIN_FUNCTION_AF8_DIO 14UL
#endif
#ifndef PIN_AF8_GPIO
#define PIN_AF8_GPIO 3u
#define PIN_AF8_GPIO_PIN 3u
#endif

/* Ball: AH7 */
#define PIN_CTRL_REG_ADDR_AH7 SYSCFG_PAD_VIN1B_CLK1
#ifndef PIN_FUNCTION_AH7_DIO
#define PIN_FUNCTION_AH7_DIO 14UL
#endif
#ifndef PIN_AH7_GPIO
#define PIN_AH7_GPIO 2u
#define PIN_AH7_GPIO_PIN 31u
#endif

/* Ball: E1 */
#define PIN_CTRL_REG_ADDR_E1 SYSCFG_PAD_VIN2A_CLK0
#ifndef PIN_FUNCTION_E1_DIO
#define PIN_FUNCTION_E1_DIO 14UL
#endif
#ifndef PIN_E1_GPIO
#define PIN_E1_GPIO 3u
#define PIN_E1_GPIO_PIN 28u
#endif

/* Ball: F2 */
#define PIN_CTRL_REG_ADDR_F2 SYSCFG_PAD_VIN2A_D0
#ifndef PIN_FUNCTION_F2_UART9
#define PIN_FUNCTION_F2_UART9 7UL
#endif
#ifndef PIN_FUNCTION_F2_SPI4
#define PIN_FUNCTION_F2_SPI4 8UL
#endif
#ifndef PIN_FUNCTION_F2_PWM
#define PIN_FUNCTION_F2_PWM 10UL
#endif
#ifndef PIN_FUNCTION_F2_DIO
#define PIN_FUNCTION_F2_DIO 14UL
#endif
#ifndef PIN_F2_GPIO
#define PIN_F2_GPIO 4u
#define PIN_F2_GPIO_PIN 1u
#endif

/* Ball: F3 */
#define PIN_CTRL_REG_ADDR_F3 SYSCFG_PAD_VIN2A_D1
#ifndef PIN_FUNCTION_F3_UART9
#define PIN_FUNCTION_F3_UART9 7UL
#endif
#ifndef PIN_FUNCTION_F3_SPI4
#define PIN_FUNCTION_F3_SPI4 8UL
#endif
#ifndef PIN_FUNCTION_F3_PWM
#define PIN_FUNCTION_F3_PWM 10UL
#endif
#ifndef PIN_FUNCTION_F3_DIO
#define PIN_FUNCTION_F3_DIO 14UL
#endif
#ifndef PIN_F3_GPIO
#define PIN_F3_GPIO 4u
#define PIN_F3_GPIO_PIN 2u
#endif

/* Ball: D3 */
#define PIN_CTRL_REG_ADDR_D3 SYSCFG_PAD_VIN2A_D10
#ifndef PIN_FUNCTION_D3_ETH_MDIO
#define PIN_FUNCTION_D3_ETH_MDIO 3UL
#endif
#ifndef PIN_FUNCTION_D3_PWM
#define PIN_FUNCTION_D3_PWM 10UL
#endif
#ifndef PIN_FUNCTION_D3_DIO
#define PIN_FUNCTION_D3_DIO 14UL
#endif
#ifndef PIN_D3_GPIO
#define PIN_D3_GPIO 4u
#define PIN_D3_GPIO_PIN 11u
#endif

/* Ball: F6 */
#define PIN_CTRL_REG_ADDR_F6 SYSCFG_PAD_VIN2A_D11
#ifndef PIN_FUNCTION_F6_ETH_MDIO
#define PIN_FUNCTION_F6_ETH_MDIO 3UL
#endif
#ifndef PIN_FUNCTION_F6_PWM
#define PIN_FUNCTION_F6_PWM 10UL
#endif
#ifndef PIN_FUNCTION_F6_DIO
#define PIN_FUNCTION_F6_DIO 14UL
#endif
#ifndef PIN_F6_GPIO
#define PIN_F6_GPIO 4u
#define PIN_F6_GPIO_PIN 12u
#endif

/* Ball: D5 */
#define PIN_CTRL_REG_ADDR_D5 SYSCFG_PAD_VIN2A_D12
#ifndef PIN_FUNCTION_D5_ETH_RGMII
#define PIN_FUNCTION_D5_ETH_RGMII 3UL
#endif
#ifndef PIN_FUNCTION_D5_ETH_MII
#define PIN_FUNCTION_D5_ETH_MII 8UL
#endif
#ifndef PIN_FUNCTION_D5_DIO
#define PIN_FUNCTION_D5_DIO 14UL
#endif
#ifndef PIN_D5_GPIO
#define PIN_D5_GPIO 4u
#define PIN_D5_GPIO_PIN 13u
#endif

/* Ball: C2 */
#define PIN_CTRL_REG_ADDR_C2 SYSCFG_PAD_VIN2A_D13
#ifndef PIN_FUNCTION_C2_ETH_RGMII
#define PIN_FUNCTION_C2_ETH_RGMII 3UL
#endif
#ifndef PIN_FUNCTION_C2_ETH_MII
#define PIN_FUNCTION_C2_ETH_MII 8UL
#endif
#ifndef PIN_FUNCTION_C2_DIO
#define PIN_FUNCTION_C2_DIO 14UL
#endif
#ifndef PIN_C2_GPIO
#define PIN_C2_GPIO 4u
#define PIN_C2_GPIO_PIN 14u
#endif

/* Ball: C3 */
#define PIN_CTRL_REG_ADDR_C3 SYSCFG_PAD_VIN2A_D14
#ifndef PIN_FUNCTION_C3_ETH_RGMII
#define PIN_FUNCTION_C3_ETH_RGMII 3UL
#endif
#ifndef PIN_FUNCTION_C3_ETH_MII
#define PIN_FUNCTION_C3_ETH_MII 8UL
#endif
#ifndef PIN_FUNCTION_C3_DIO
#define PIN_FUNCTION_C3_DIO 14UL
#endif
#ifndef PIN_C3_GPIO
#define PIN_C3_GPIO 4u
#define PIN_C3_GPIO_PIN 15u
#endif

/* Ball: C4 */
#define PIN_CTRL_REG_ADDR_C4 SYSCFG_PAD_VIN2A_D15
#ifndef PIN_FUNCTION_C4_ETH_RGMII
#define PIN_FUNCTION_C4_ETH_RGMII 3UL
#endif
#ifndef PIN_FUNCTION_C4_ETH_MII
#define PIN_FUNCTION_C4_ETH_MII 8UL
#endif
#ifndef PIN_FUNCTION_C4_DIO
#define PIN_FUNCTION_C4_DIO 14UL
#endif
#ifndef PIN_C4_GPIO
#define PIN_C4_GPIO 4u
#define PIN_C4_GPIO_PIN 16u
#endif

/* Ball: B2 */
#define PIN_CTRL_REG_ADDR_B2 SYSCFG_PAD_VIN2A_D16
#ifndef PIN_FUNCTION_B2_ETH_RGMII
#define PIN_FUNCTION_B2_ETH_RGMII 3UL
#endif
#ifndef PIN_FUNCTION_B2_ETH_MII
#define PIN_FUNCTION_B2_ETH_MII 8UL
#endif
#ifndef PIN_FUNCTION_B2_DIO
#define PIN_FUNCTION_B2_DIO 14UL
#endif
#ifndef PIN_B2_GPIO
#define PIN_B2_GPIO 4u
#define PIN_B2_GPIO_PIN 24u
#endif

/* Ball: D6 */
#define PIN_CTRL_REG_ADDR_D6 SYSCFG_PAD_VIN2A_D17
#ifndef PIN_FUNCTION_D6_ETH_RGMII
#define PIN_FUNCTION_D6_ETH_RGMII 3UL
#endif
#ifndef PIN_FUNCTION_D6_ETH_MII
#define PIN_FUNCTION_D6_ETH_MII 8UL
#endif
#ifndef PIN_FUNCTION_D6_PWM
#define PIN_FUNCTION_D6_PWM 10UL
#endif
#ifndef PIN_FUNCTION_D6_DIO
#define PIN_FUNCTION_D6_DIO 14UL
#endif
#ifndef PIN_D6_GPIO
#define PIN_D6_GPIO 4u
#define PIN_D6_GPIO_PIN 25u
#endif

/* Ball: C5 */
#define PIN_CTRL_REG_ADDR_C5 SYSCFG_PAD_VIN2A_D18
#ifndef PIN_FUNCTION_C5_ETH_RGMII
#define PIN_FUNCTION_C5_ETH_RGMII 3UL
#endif
#ifndef PIN_FUNCTION_C5_ETH_MII
#define PIN_FUNCTION_C5_ETH_MII 8UL
#endif
#ifndef PIN_FUNCTION_C5_PWM
#define PIN_FUNCTION_C5_PWM 10UL
#endif
#ifndef PIN_FUNCTION_C5_DIO
#define PIN_FUNCTION_C5_DIO 14UL
#endif
#ifndef PIN_C5_GPIO
#define PIN_C5_GPIO 4u
#define PIN_C5_GPIO_PIN 26u
#endif

/* Ball: A3 */
#define PIN_CTRL_REG_ADDR_A3 SYSCFG_PAD_VIN2A_D19
#ifndef PIN_FUNCTION_A3_ETH_RGMII
#define PIN_FUNCTION_A3_ETH_RGMII 3UL
#endif
#ifndef PIN_FUNCTION_A3_ETH_MII
#define PIN_FUNCTION_A3_ETH_MII 8UL
#endif
#ifndef PIN_FUNCTION_A3_PWM
#define PIN_FUNCTION_A3_PWM 10UL
#endif
#ifndef PIN_FUNCTION_A3_DIO
#define PIN_FUNCTION_A3_DIO 14UL
#endif
#ifndef PIN_A3_GPIO
#define PIN_A3_GPIO 4u
#define PIN_A3_GPIO_PIN 27u
#endif

/* Ball: D1 */
#define PIN_CTRL_REG_ADDR_D1 SYSCFG_PAD_VIN2A_D2
#ifndef PIN_FUNCTION_D1_UART10
#define PIN_FUNCTION_D1_UART10 8UL
#endif
#ifndef PIN_FUNCTION_D1_DIO
#define PIN_FUNCTION_D1_DIO 14UL
#endif
#ifndef PIN_D1_GPIO
#define PIN_D1_GPIO 4u
#define PIN_D1_GPIO_PIN 3u
#endif

/* Ball: B3 */
#define PIN_CTRL_REG_ADDR_B3 SYSCFG_PAD_VIN2A_D20
#ifndef PIN_FUNCTION_B3_ETH_RGMII
#define PIN_FUNCTION_B3_ETH_RGMII 3UL
#endif
#ifndef PIN_FUNCTION_B3_ETH_MII
#define PIN_FUNCTION_B3_ETH_MII 8UL
#endif
#ifndef PIN_FUNCTION_B3_DIO
#define PIN_FUNCTION_B3_DIO 14UL
#endif
#ifndef PIN_B3_GPIO
#define PIN_B3_GPIO 4u
#define PIN_B3_GPIO_PIN 28u
#endif

/* Ball: B4 */
#define PIN_CTRL_REG_ADDR_B4 SYSCFG_PAD_VIN2A_D21
#ifndef PIN_FUNCTION_B4_ETH_RGMII
#define PIN_FUNCTION_B4_ETH_RGMII 3UL
#endif
#ifndef PIN_FUNCTION_B4_ETH_MII
#define PIN_FUNCTION_B4_ETH_MII 8UL
#endif
#ifndef PIN_FUNCTION_B4_DIO
#define PIN_FUNCTION_B4_DIO 14UL
#endif
#ifndef PIN_B4_GPIO
#define PIN_B4_GPIO 4u
#define PIN_B4_GPIO_PIN 29u
#endif

/* Ball: B5 */
#define PIN_CTRL_REG_ADDR_B5 SYSCFG_PAD_VIN2A_D22
#ifndef PIN_FUNCTION_B5_ETH_RGMII
#define PIN_FUNCTION_B5_ETH_RGMII 3UL
#endif
#ifndef PIN_FUNCTION_B5_ETH_MII
#define PIN_FUNCTION_B5_ETH_MII 8UL
#endif
#ifndef PIN_FUNCTION_B5_DIO
#define PIN_FUNCTION_B5_DIO 14UL
#endif
#ifndef PIN_B5_GPIO
#define PIN_B5_GPIO 4u
#define PIN_B5_GPIO_PIN 30u
#endif

/* Ball: A4 */
#define PIN_CTRL_REG_ADDR_A4 SYSCFG_PAD_VIN2A_D23
#ifndef PIN_FUNCTION_A4_ETH_RGMII
#define PIN_FUNCTION_A4_ETH_RGMII 3UL
#endif
#ifndef PIN_FUNCTION_A4_ETH_MII
#define PIN_FUNCTION_A4_ETH_MII 8UL
#endif
#ifndef PIN_FUNCTION_A4_DIO
#define PIN_FUNCTION_A4_DIO 14UL
#endif
#ifndef PIN_A4_GPIO
#define PIN_A4_GPIO 4u
#define PIN_A4_GPIO_PIN 31u
#endif

/* Ball: E2 */
#define PIN_CTRL_REG_ADDR_E2 SYSCFG_PAD_VIN2A_D3
#ifndef PIN_FUNCTION_E2_UART10
#define PIN_FUNCTION_E2_UART10 8UL
#endif
#ifndef PIN_FUNCTION_E2_PWM
#define PIN_FUNCTION_E2_PWM 10UL
#endif
#ifndef PIN_FUNCTION_E2_DIO
#define PIN_FUNCTION_E2_DIO 14UL
#endif
#ifndef PIN_E2_GPIO
#define PIN_E2_GPIO 4u
#define PIN_E2_GPIO_PIN 4u
#endif

/* Ball: D2 */
#define PIN_CTRL_REG_ADDR_D2 SYSCFG_PAD_VIN2A_D4
#ifndef PIN_FUNCTION_D2_UART10
#define PIN_FUNCTION_D2_UART10 8UL
#endif
#ifndef PIN_FUNCTION_D2_PWM
#define PIN_FUNCTION_D2_PWM 10UL
#endif
#ifndef PIN_FUNCTION_D2_DIO
#define PIN_FUNCTION_D2_DIO 14UL
#endif
#ifndef PIN_D2_GPIO
#define PIN_D2_GPIO 4u
#define PIN_D2_GPIO_PIN 5u
#endif

/* Ball: F4 */
#define PIN_CTRL_REG_ADDR_F4 SYSCFG_PAD_VIN2A_D5
#ifndef PIN_FUNCTION_F4_UART10
#define PIN_FUNCTION_F4_UART10 8UL
#endif
#ifndef PIN_FUNCTION_F4_DIO
#define PIN_FUNCTION_F4_DIO 14UL
#endif
#ifndef PIN_F4_GPIO
#define PIN_F4_GPIO 4u
#define PIN_F4_GPIO_PIN 6u
#endif

/* Ball: C1 */
#define PIN_CTRL_REG_ADDR_C1 SYSCFG_PAD_VIN2A_D6
#ifndef PIN_FUNCTION_C1_ETH_MII
#define PIN_FUNCTION_C1_ETH_MII 8UL
#endif
#ifndef PIN_FUNCTION_C1_DIO
#define PIN_FUNCTION_C1_DIO 14UL
#endif
#ifndef PIN_C1_GPIO
#define PIN_C1_GPIO 4u
#define PIN_C1_GPIO_PIN 7u
#endif

/* Ball: E4 */
#define PIN_CTRL_REG_ADDR_E4 SYSCFG_PAD_VIN2A_D7
#ifndef PIN_FUNCTION_E4_ETH_MII
#define PIN_FUNCTION_E4_ETH_MII 8UL
#endif
#ifndef PIN_FUNCTION_E4_DIO
#define PIN_FUNCTION_E4_DIO 14UL
#endif
#ifndef PIN_E4_GPIO
#define PIN_E4_GPIO 4u
#define PIN_E4_GPIO_PIN 8u
#endif

/* Ball: F5 */
#define PIN_CTRL_REG_ADDR_F5 SYSCFG_PAD_VIN2A_D8
#ifndef PIN_FUNCTION_F5_ETH_MII
#define PIN_FUNCTION_F5_ETH_MII 8UL
#endif
#ifndef PIN_FUNCTION_F5_DIO
#define PIN_FUNCTION_F5_DIO 14UL
#endif
#ifndef PIN_F5_GPIO
#define PIN_F5_GPIO 4u
#define PIN_F5_GPIO_PIN 9u
#endif

/* Ball: E6 */
#define PIN_CTRL_REG_ADDR_E6 SYSCFG_PAD_VIN2A_D9
#ifndef PIN_FUNCTION_E6_ETH_MII
#define PIN_FUNCTION_E6_ETH_MII 8UL
#endif
#ifndef PIN_FUNCTION_E6_PWM
#define PIN_FUNCTION_E6_PWM 10UL
#endif
#ifndef PIN_FUNCTION_E6_DIO
#define PIN_FUNCTION_E6_DIO 14UL
#endif
#ifndef PIN_E6_GPIO
#define PIN_E6_GPIO 4u
#define PIN_E6_GPIO_PIN 10u
#endif

/* Ball: G2 */
#define PIN_CTRL_REG_ADDR_G2 SYSCFG_PAD_VIN2A_DE0
#ifndef PIN_FUNCTION_G2_DIO
#define PIN_FUNCTION_G2_DIO 14UL
#endif
#ifndef PIN_G2_GPIO
#define PIN_G2_GPIO 3u
#define PIN_G2_GPIO_PIN 29u
#endif

/* Ball: H7 */
#define PIN_CTRL_REG_ADDR_H7 SYSCFG_PAD_VIN2A_FLD0
#ifndef PIN_FUNCTION_H7_DIO
#define PIN_FUNCTION_H7_DIO 14UL
#endif
#ifndef PIN_H7_GPIO
#define PIN_H7_GPIO 3u
#define PIN_H7_GPIO_PIN 30u
#endif

/* Ball: G1 */
#define PIN_CTRL_REG_ADDR_G1 SYSCFG_PAD_VIN2A_HSYNC0
#ifndef PIN_FUNCTION_G1_UART9
#define PIN_FUNCTION_G1_UART9 7UL
#endif
#ifndef PIN_FUNCTION_G1_SPI4
#define PIN_FUNCTION_G1_SPI4 8UL
#endif
#ifndef PIN_FUNCTION_G1_DIO
#define PIN_FUNCTION_G1_DIO 14UL
#endif
#ifndef PIN_G1_GPIO
#define PIN_G1_GPIO 3u
#define PIN_G1_GPIO_PIN 31u
#endif

/* Ball: G6 */
#define PIN_CTRL_REG_ADDR_G6 SYSCFG_PAD_VIN2A_VSYNC0
#ifndef PIN_FUNCTION_G6_UART9
#define PIN_FUNCTION_G6_UART9 7UL
#endif
#ifndef PIN_FUNCTION_G6_SPI4
#define PIN_FUNCTION_G6_SPI4 8UL
#endif
#ifndef PIN_FUNCTION_G6_PWM
#define PIN_FUNCTION_G6_PWM 10UL
#endif
#ifndef PIN_FUNCTION_G6_DIO
#define PIN_FUNCTION_G6_DIO 14UL
#endif
#ifndef PIN_G6_GPIO
#define PIN_G6_GPIO 4u
#define PIN_G6_GPIO_PIN 0u
#endif

/* Ball: D11 */
#define PIN_CTRL_REG_ADDR_D11 SYSCFG_PAD_VOUT1_CLK
#ifndef PIN_FUNCTION_D11_SPI3
#define PIN_FUNCTION_D11_SPI3 8UL
#endif
#ifndef PIN_FUNCTION_D11_DIO
#define PIN_FUNCTION_D11_DIO 14UL
#endif
#ifndef PIN_D11_GPIO
#define PIN_D11_GPIO 4u
#define PIN_D11_GPIO_PIN 19u
#endif

/* Ball: F11 */
#define PIN_CTRL_REG_ADDR_F11 SYSCFG_PAD_VOUT1_D0
#ifndef PIN_FUNCTION_F11_UART5
#define PIN_FUNCTION_F11_UART5 2UL
#endif
#ifndef PIN_FUNCTION_F11_SPI3
#define PIN_FUNCTION_F11_SPI3 8UL
#endif
#ifndef PIN_FUNCTION_F11_DIO
#define PIN_FUNCTION_F11_DIO 14UL
#endif
#ifndef PIN_F11_GPIO
#define PIN_F11_GPIO 8u
#define PIN_F11_GPIO_PIN 0u
#endif

/* Ball: G10 */
#define PIN_CTRL_REG_ADDR_G10 SYSCFG_PAD_VOUT1_D1
#ifndef PIN_FUNCTION_G10_UART5
#define PIN_FUNCTION_G10_UART5 2UL
#endif
#ifndef PIN_FUNCTION_G10_DIO
#define PIN_FUNCTION_G10_DIO 14UL
#endif
#ifndef PIN_G10_GPIO
#define PIN_G10_GPIO 8u
#define PIN_G10_GPIO_PIN 1u
#endif

/* Ball: D7 */
#define PIN_CTRL_REG_ADDR_D7 SYSCFG_PAD_VOUT1_D10
#ifndef PIN_FUNCTION_D7_DIO
#define PIN_FUNCTION_D7_DIO 14UL
#endif
#ifndef PIN_D7_GPIO
#define PIN_D7_GPIO 8u
#define PIN_D7_GPIO_PIN 10u
#endif

/* Ball: D8 */
#define PIN_CTRL_REG_ADDR_D8 SYSCFG_PAD_VOUT1_D11
#ifndef PIN_FUNCTION_D8_DIO
#define PIN_FUNCTION_D8_DIO 14UL
#endif
#ifndef PIN_D8_GPIO
#define PIN_D8_GPIO 8u
#define PIN_D8_GPIO_PIN 11u
#endif

/* Ball: A5 */
#define PIN_CTRL_REG_ADDR_A5 SYSCFG_PAD_VOUT1_D12
#ifndef PIN_FUNCTION_A5_DIO
#define PIN_FUNCTION_A5_DIO 14UL
#endif
#ifndef PIN_A5_GPIO
#define PIN_A5_GPIO 8u
#define PIN_A5_GPIO_PIN 12u
#endif

/* Ball: C6 */
#define PIN_CTRL_REG_ADDR_C6 SYSCFG_PAD_VOUT1_D13
#ifndef PIN_FUNCTION_C6_DIO
#define PIN_FUNCTION_C6_DIO 14UL
#endif
#ifndef PIN_C6_GPIO
#define PIN_C6_GPIO 8u
#define PIN_C6_GPIO_PIN 13u
#endif

/* Ball: C8 */
#define PIN_CTRL_REG_ADDR_C8 SYSCFG_PAD_VOUT1_D14
#ifndef PIN_FUNCTION_C8_DIO
#define PIN_FUNCTION_C8_DIO 14UL
#endif
#ifndef PIN_C8_GPIO
#define PIN_C8_GPIO 8u
#define PIN_C8_GPIO_PIN 14u
#endif

/* Ball: C7 */
#define PIN_CTRL_REG_ADDR_C7 SYSCFG_PAD_VOUT1_D15
#ifndef PIN_FUNCTION_C7_DIO
#define PIN_FUNCTION_C7_DIO 14UL
#endif
#ifndef PIN_C7_GPIO
#define PIN_C7_GPIO 8u
#define PIN_C7_GPIO_PIN 15u
#endif

/* Ball: B7 */
#define PIN_CTRL_REG_ADDR_B7 SYSCFG_PAD_VOUT1_D16
#ifndef PIN_FUNCTION_B7_UART7
#define PIN_FUNCTION_B7_UART7 2UL
#endif
#ifndef PIN_FUNCTION_B7_DIO
#define PIN_FUNCTION_B7_DIO 14UL
#endif
#ifndef PIN_B7_GPIO
#define PIN_B7_GPIO 8u
#define PIN_B7_GPIO_PIN 16u
#endif

/* Ball: B8 */
#define PIN_CTRL_REG_ADDR_B8 SYSCFG_PAD_VOUT1_D17
#ifndef PIN_FUNCTION_B8_UART7
#define PIN_FUNCTION_B8_UART7 2UL
#endif
#ifndef PIN_FUNCTION_B8_DIO
#define PIN_FUNCTION_B8_DIO 14UL
#endif
#ifndef PIN_B8_GPIO
#define PIN_B8_GPIO 8u
#define PIN_B8_GPIO_PIN 17u
#endif

/* Ball: A7 */
#define PIN_CTRL_REG_ADDR_A7 SYSCFG_PAD_VOUT1_D18
#ifndef PIN_FUNCTION_A7_DIO
#define PIN_FUNCTION_A7_DIO 14UL
#endif
#ifndef PIN_A7_GPIO
#define PIN_A7_GPIO 8u
#define PIN_A7_GPIO_PIN 18u
#endif

/* Ball: A8 */
#define PIN_CTRL_REG_ADDR_A8 SYSCFG_PAD_VOUT1_D19
#ifndef PIN_FUNCTION_A8_DIO
#define PIN_FUNCTION_A8_DIO 14UL
#endif
#ifndef PIN_A8_GPIO
#define PIN_A8_GPIO 8u
#define PIN_A8_GPIO_PIN 19u
#endif

/* Ball: F10 */
#define PIN_CTRL_REG_ADDR_F10 SYSCFG_PAD_VOUT1_D2
#ifndef PIN_FUNCTION_F10_DIO
#define PIN_FUNCTION_F10_DIO 14UL
#endif
#ifndef PIN_F10_GPIO
#define PIN_F10_GPIO 8u
#define PIN_F10_GPIO_PIN 2u
#endif

/* Ball: C9 */
#define PIN_CTRL_REG_ADDR_C9 SYSCFG_PAD_VOUT1_D20
#ifndef PIN_FUNCTION_C9_DIO
#define PIN_FUNCTION_C9_DIO 14UL
#endif
#ifndef PIN_C9_GPIO
#define PIN_C9_GPIO 8u
#define PIN_C9_GPIO_PIN 20u
#endif

/* Ball: A9 */
#define PIN_CTRL_REG_ADDR_A9 SYSCFG_PAD_VOUT1_D21
#ifndef PIN_FUNCTION_A9_DIO
#define PIN_FUNCTION_A9_DIO 14UL
#endif
#ifndef PIN_A9_GPIO
#define PIN_A9_GPIO 8u
#define PIN_A9_GPIO_PIN 21u
#endif

/* Ball: B9 */
#define PIN_CTRL_REG_ADDR_B9 SYSCFG_PAD_VOUT1_D22
#ifndef PIN_FUNCTION_B9_DIO
#define PIN_FUNCTION_B9_DIO 14UL
#endif
#ifndef PIN_B9_GPIO
#define PIN_B9_GPIO 8u
#define PIN_B9_GPIO_PIN 22u
#endif

/* Ball: A10 */
#define PIN_CTRL_REG_ADDR_A10 SYSCFG_PAD_VOUT1_D23
#ifndef PIN_FUNCTION_A10_SPI3
#define PIN_FUNCTION_A10_SPI3 8UL
#endif
#ifndef PIN_FUNCTION_A10_DIO
#define PIN_FUNCTION_A10_DIO 14UL
#endif
#ifndef PIN_A10_GPIO
#define PIN_A10_GPIO 8u
#define PIN_A10_GPIO_PIN 23u
#endif

/* Ball: G11 */
#define PIN_CTRL_REG_ADDR_G11 SYSCFG_PAD_VOUT1_D3
#ifndef PIN_FUNCTION_G11_DIO
#define PIN_FUNCTION_G11_DIO 14UL
#endif
#ifndef PIN_G11_GPIO
#define PIN_G11_GPIO 8u
#define PIN_G11_GPIO_PIN 3u
#endif

/* Ball: E9 */
#define PIN_CTRL_REG_ADDR_E9 SYSCFG_PAD_VOUT1_D4
#ifndef PIN_FUNCTION_E9_DIO
#define PIN_FUNCTION_E9_DIO 14UL
#endif
#ifndef PIN_E9_GPIO
#define PIN_E9_GPIO 8u
#define PIN_E9_GPIO_PIN 4u
#endif

/* Ball: F9 */
#define PIN_CTRL_REG_ADDR_F9 SYSCFG_PAD_VOUT1_D5
#ifndef PIN_FUNCTION_F9_DIO
#define PIN_FUNCTION_F9_DIO 14UL
#endif
#ifndef PIN_F9_GPIO
#define PIN_F9_GPIO 8u
#define PIN_F9_GPIO_PIN 5u
#endif

/* Ball: F8 */
#define PIN_CTRL_REG_ADDR_F8 SYSCFG_PAD_VOUT1_D6
#ifndef PIN_FUNCTION_F8_DIO
#define PIN_FUNCTION_F8_DIO 14UL
#endif
#ifndef PIN_F8_GPIO
#define PIN_F8_GPIO 8u
#define PIN_F8_GPIO_PIN 6u
#endif

/* Ball: E7 */
#define PIN_CTRL_REG_ADDR_E7 SYSCFG_PAD_VOUT1_D7
#ifndef PIN_FUNCTION_E7_DIO
#define PIN_FUNCTION_E7_DIO 14UL
#endif
#ifndef PIN_E7_GPIO
#define PIN_E7_GPIO 8u
#define PIN_E7_GPIO_PIN 7u
#endif

/* Ball: E8 */
#define PIN_CTRL_REG_ADDR_E8 SYSCFG_PAD_VOUT1_D8
#ifndef PIN_FUNCTION_E8_UART6
#define PIN_FUNCTION_E8_UART6 2UL
#endif
#ifndef PIN_FUNCTION_E8_DIO
#define PIN_FUNCTION_E8_DIO 14UL
#endif
#ifndef PIN_E8_GPIO
#define PIN_E8_GPIO 8u
#define PIN_E8_GPIO_PIN 8u
#endif

/* Ball: D9 */
#define PIN_CTRL_REG_ADDR_D9 SYSCFG_PAD_VOUT1_D9
#ifndef PIN_FUNCTION_D9_UART6
#define PIN_FUNCTION_D9_UART6 2UL
#endif
#ifndef PIN_FUNCTION_D9_DIO
#define PIN_FUNCTION_D9_DIO 14UL
#endif
#ifndef PIN_D9_GPIO
#define PIN_D9_GPIO 8u
#define PIN_D9_GPIO_PIN 9u
#endif

/* Ball: B10 */
#define PIN_CTRL_REG_ADDR_B10 SYSCFG_PAD_VOUT1_DE
#ifndef PIN_FUNCTION_B10_SPI3
#define PIN_FUNCTION_B10_SPI3 8UL
#endif
#ifndef PIN_FUNCTION_B10_DIO
#define PIN_FUNCTION_B10_DIO 14UL
#endif
#ifndef PIN_B10_GPIO
#define PIN_B10_GPIO 4u
#define PIN_B10_GPIO_PIN 20u
#endif

/* Ball: B11 */
#define PIN_CTRL_REG_ADDR_B11 SYSCFG_PAD_VOUT1_FLD
#ifndef PIN_FUNCTION_B11_SPI3
#define PIN_FUNCTION_B11_SPI3 8UL
#endif
#ifndef PIN_FUNCTION_B11_DIO
#define PIN_FUNCTION_B11_DIO 14UL
#endif
#ifndef PIN_B11_GPIO
#define PIN_B11_GPIO 4u
#define PIN_B11_GPIO_PIN 21u
#endif

/* Ball: C11 */
#define PIN_CTRL_REG_ADDR_C11 SYSCFG_PAD_VOUT1_HSYNC
#ifndef PIN_FUNCTION_C11_SPI3
#define PIN_FUNCTION_C11_SPI3 8UL
#endif
#ifndef PIN_FUNCTION_C11_DIO
#define PIN_FUNCTION_C11_DIO 14UL
#endif
#ifndef PIN_C11_GPIO
#define PIN_C11_GPIO 4u
#define PIN_C11_GPIO_PIN 22u
#endif

/* Ball: E11 */
#define PIN_CTRL_REG_ADDR_E11 SYSCFG_PAD_VOUT1_VSYNC
#ifndef PIN_FUNCTION_E11_SPI3
#define PIN_FUNCTION_E11_SPI3 8UL
#endif
#ifndef PIN_FUNCTION_E11_DIO
#define PIN_FUNCTION_E11_DIO 14UL
#endif
#ifndef PIN_E11_GPIO
#define PIN_E11_GPIO 4u
#define PIN_E11_GPIO_PIN 23u
#endif

/* Ball: AD17 */
#define PIN_CTRL_REG_ADDR_AD17 SYSCFG_PAD_WAKEUP0
#ifndef PIN_FUNCTION_AD17_CAN
#define PIN_FUNCTION_AD17_CAN 1UL
#endif
#ifndef PIN_FUNCTION_AD17_DIO
#define PIN_FUNCTION_AD17_DIO 14UL
#endif
#ifndef PIN_AD17_GPIO
#define PIN_AD17_GPIO 1u
#define PIN_AD17_GPIO_PIN 0u
#endif

/* Ball: AC17 */
#define PIN_CTRL_REG_ADDR_AC17 SYSCFG_PAD_WAKEUP1
#ifndef PIN_FUNCTION_AC17_CAN
#define PIN_FUNCTION_AC17_CAN 1UL
#endif
#ifndef PIN_FUNCTION_AC17_DIO
#define PIN_FUNCTION_AC17_DIO 14UL
#endif
#ifndef PIN_AC17_GPIO
#define PIN_AC17_GPIO 1u
#define PIN_AC17_GPIO_PIN 1u
#endif

/* Ball: AB16 */
#define PIN_CTRL_REG_ADDR_AB16 SYSCFG_PAD_WAKEUP2
#ifndef PIN_FUNCTION_AB16_DIO
#define PIN_FUNCTION_AB16_DIO 14UL
#endif
#ifndef PIN_AB16_GPIO
#define PIN_AB16_GPIO 1u
#define PIN_AB16_GPIO_PIN 2u
#endif

/* Ball: AC16 */
#define PIN_CTRL_REG_ADDR_AC16 SYSCFG_PAD_WAKEUP3
#ifndef PIN_FUNCTION_AC16_DIO
#define PIN_FUNCTION_AC16_DIO 14UL
#endif
#ifndef PIN_AC16_GPIO
#define PIN_AC16_GPIO 1u
#define PIN_AC16_GPIO_PIN 3u
#endif

/* Ball: D18 */
#define PIN_CTRL_REG_ADDR_D18 SYSCFG_PAD_XREF_CLK0
#ifndef PIN_FUNCTION_D18_PWM
#define PIN_FUNCTION_D18_PWM 10UL
#endif
#ifndef PIN_FUNCTION_D18_ICU
#define PIN_FUNCTION_D18_ICU 10UL
#endif
#ifndef PIN_FUNCTION_D18_DIO
#define PIN_FUNCTION_D18_DIO 14UL
#endif
#ifndef PIN_D18_GPIO
#define PIN_D18_GPIO 6u
#define PIN_D18_GPIO_PIN 17u
#endif

/* Ball: E17 */
#define PIN_CTRL_REG_ADDR_E17 SYSCFG_PAD_XREF_CLK1
#ifndef PIN_FUNCTION_E17_PWM
#define PIN_FUNCTION_E17_PWM 10UL
#endif
#ifndef PIN_FUNCTION_E17_ICU
#define PIN_FUNCTION_E17_ICU 10UL
#endif
#ifndef PIN_FUNCTION_E17_DIO
#define PIN_FUNCTION_E17_DIO 14UL
#endif
#ifndef PIN_E17_GPIO
#define PIN_E17_GPIO 6u
#define PIN_E17_GPIO_PIN 18u
#endif

/* Ball: B26 */
#define PIN_CTRL_REG_ADDR_B26 SYSCFG_PAD_XREF_CLK2
#ifndef PIN_FUNCTION_B26_PWM
#define PIN_FUNCTION_B26_PWM 10UL
#endif
#ifndef PIN_FUNCTION_B26_ICU
#define PIN_FUNCTION_B26_ICU 10UL
#endif
#ifndef PIN_FUNCTION_B26_DIO
#define PIN_FUNCTION_B26_DIO 14UL
#endif
#ifndef PIN_B26_GPIO
#define PIN_B26_GPIO 6u
#define PIN_B26_GPIO_PIN 19u
#endif

/* Ball: C23 */
#define PIN_CTRL_REG_ADDR_C23 SYSCFG_PAD_XREF_CLK3
#ifndef PIN_FUNCTION_C23_PWM
#define PIN_FUNCTION_C23_PWM 10UL
#endif
#ifndef PIN_FUNCTION_C23_ICU
#define PIN_FUNCTION_C23_ICU 10UL
#endif
#ifndef PIN_FUNCTION_C23_DIO
#define PIN_FUNCTION_C23_DIO 14UL
#endif
#ifndef PIN_C23_GPIO
#define PIN_C23_GPIO 6u
#define PIN_C23_GPIO_PIN 20u
#endif

#endif /* JACINTO6_PORTDEFS_H_ */
