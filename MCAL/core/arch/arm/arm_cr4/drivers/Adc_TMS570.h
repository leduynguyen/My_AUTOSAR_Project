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

#ifndef __ADC_H__
#define __ADC_H__

#define adcGROUP0 0U
#define adcGROUP1 1U
#define adcGROUP2 2U

enum adcResolution
{
    ADC_12_BIT = 0x00000000, /**< Alias for 12 bit data resolution */
    ADC_10_BIT = 0x00000100, /**< Alias for 10 bit data resolution */
    ADC_8_BIT  = 0x00000200  /**< Alias for 8 bit data resolution  */
};

enum adcFiFoStatus
{
    ADC_FIFO_IS_NOT_FULL = 0, /**< Alias for FiFo is not full       */
    ADC_FIFO_IS_FULL     = 1, /**< Alias for FiFo is full           */
    ADC_FIFO_OVERFLOW    = 3  /**< Alias for FiFo overflow occured  */
};

enum adcConversionStatus
{
    ADC_CONVERSION_IS_NOT_FINISHED = 0, /**< Alias for current conversion is not finished */
    ADC_CONVERSION_IS_FINISHED     = 8  /**< Alias for current conversion is  finished    */
};

enum adcHwTriggerSource
{
    ADC_EVENT,     /**< Alias for event pin           */
    ADC_HET8,      /**< Alias for HET pin 8           */
    ADC_HET10,     /**< Alias for HET pin 10          */
    ADC_RTI_COMP0, /**< Alias for RTI compare 0 match */
    ADC_HET17,     /**< Alias for HET pin 17          */
    ADC_HET19,     /**< Alias for HET pin 19          */
    ADC_GIOB0,     /**< Alias for GIO port b pin 0    */
    ADC_GIOB1      /**< Alias for GIO port b pin 1    */
};

typedef struct tagAdcData
{
    uint16_t id;     /**< Channel/Pin Id        */
    uint16_t value;  /**< Conversion data value */
} adcData_t;


typedef volatile struct tagAdcBase
{
    uint32_t RSTCR;              /**< 0x0000: Reset control register                            */
    uint32_t OPMODECR;           /**< 0x0004: Operating mode control register                   */
    uint32_t CLOCKCR;            /**< 0x0008: Clock control register                            */
    uint32_t CALCR;              /**< 0x000C: Calibration control register                      */
    uint32_t GxMODECR[3U];       /**< 0x0010,0x0014,0x0018: Group 0-2 mode control register     */
    uint32_t GxSRC[3U];              /**< 0x001C: Group 0,1,2 trigger source control register           */
    uint32_t GxINTENA[3U];       /**< 0x0028,0x002C,0x0030: Group 0-2 interrupt enable register */
    uint32_t GxINTFLG[3U];       /**< 0x0034,0x0038,0x003C: Group 0-2 interrupt flag register   */
    uint32_t GxTHRINTCR[3U];     /**< 0x0040-0x0048: Group 0-2 interrupt threshold register     */
    uint32_t G0DMACR;            /**< 0x004C: Group 0 DMA control register                      */
    uint32_t G1DMACR;            /**< 0x0050: Group 1 DMA control register                      */
    uint32_t G2DMACR;            /**< 0x0054: Group 2 DMA control register                      */
    uint32_t BNDCR;              /**< 0x0058: Buffer boundary control register                  */
#ifdef _little_endian__
    uint32_t BNDEND  : 16U;      /**< 0x005C: Buffer boundary end register                      */
    uint32_t BUFINIT : 16U;      /**< 0x005C: Buffer initialization register                    */
#else
    uint32_t BUFINIT : 16U;      /**< 0x005C: Buffer initialization register                    */
    uint32_t BNDEND  : 16U;      /**< 0x005C: Buffer boundary end register                      */
#endif
    uint32_t GxSAMP[3U];         /**< 0x0060: Group 0,1,2 sample window register                 */
    uint32_t GxSR[3U];           /**< 0x006C: Group 01,2, status register                        */
    uint32_t GxSEL[3U];          /**< 0x0078-0x007C: Group 0-2 channel select register          */
    uint32_t CALR;               /**< 0x0084: Calibration register                              */
    uint32_t SMSTATE;            /**< 0x0088: State machine state register                      */
    uint32_t LASTCONV;           /**< 0x008C: Last conversion register                          */
    struct
    {
        uint32_t BUF0;           /**< 0x0090,0x00B0,0x00D0: Group 0-2 result buffer 1 register  */
        uint32_t BUF1;           /**< 0x0094,0x00B4,0x00D4: Group 0-2 result buffer 1 register  */
        uint32_t BUF2;           /**< 0x0098,0x00B8,0x00D8: Group 0-2 result buffer 2 register  */
        uint32_t BUF3;           /**< 0x009C,0x00BC,0x00DC: Group 0-2 result buffer 3 register  */
        uint32_t BUF4;           /**< 0x00A0,0x00C0,0x00E0: Group 0-2 result buffer 4 register  */
        uint32_t BUF5;           /**< 0x00A4,0x00C4,0x00E4: Group 0-2 result buffer 5 register  */
        uint32_t BUF6;           /**< 0x00A8,0x00C8,0x00E8: Group 0-2 result buffer 6 register  */
        uint32_t BUF7;           /**< 0x00AC,0x00CC,0x00EC: Group 0-2 result buffer 7 register  */
    } GxBUF[3U];
    uint32_t G0EMUBUFFER;        /**< 0x00F0: Group 0 emulation result buffer                   */
    uint32_t G1EMUBUFFER;        /**< 0x00F4: Group 1 emulation result buffer                   */
    uint32_t G2EMUBUFFER;        /**< 0x00F8: Group 2 emulation result buffer                   */
    uint32_t EVTDIR;             /**< 0x00FC: Event pin direction register                      */
    uint32_t EVTOUT;             /**< 0x0100: Event pin digital output register                 */
    uint32_t EVTIN;              /**< 0x0104: Event pin digital input register                  */
    uint32_t EVTSET;             /**< 0x0108: Event pin set register                            */
    uint32_t EVTCLR;             /**< 0x010C: Event pin clear register                          */
    uint32_t EVTPDR;             /**< 0x0110: Event pin open drain register                     */
    uint32_t EVTDIS;             /**< 0x0114: Event pin pull disable register                   */
    uint32_t EVTPSEL;            /**< 0x0118: Event pin pull select register                    */
    uint32_t G0SAMPDISEN;        /**< 0x011C: Group 0 sample discharge register                 */
    uint32_t G1SAMPDISEN;        /**< 0x0120: Group 1 sample discharge register                 */
    uint32_t G2SAMPDISEN;        /**< 0x0124: Group 2 sample discharge register                 */
    uint32_t MAGINTCR1;          /**< 0x0128: Magnitude interrupt control register 1            */
    uint32_t MAGINT1MASK;        /**< 0x012C: Magnitude interrupt mask register 1               */
    uint32_t MAGINTCR2;          /**< 0x0130: Magnitude interrupt control register 2            */
    uint32_t MAGINT2MASK;        /**< 0x0134: Magnitude interrupt mask register 2               */
    uint32_t MAGINTCR3;          /**< 0x0138: Magnitude interrupt control register 3            */
    uint32_t MAGINT3MASK;        /**< 0x013C: Magnitude interrupt mask register 3               */
    uint32_t MAGINTCR4;          /**< 0x0140: Magnitude interrupt control register 4            */
    uint32_t MAGINT4MASK;        /**< 0x0144: Magnitude interrupt mask register 4               */
    uint32_t MAGINTCR5;          /**< 0x0148: Magnitude interrupt control register 5            */
    uint32_t MAGINT5MASK;        /**< 0x014C: Magnitude interrupt mask register 5               */
    uint32_t MAGINTCR6;          /**< 0x0150: Magnitude interrupt control register 6            */
    uint32_t MAGINT6MASK;        /**< 0x0154: Magnitude interrupt mask register 6               */
    uint32_t MAGTHRINTENASET;    /**< 0x0158: Magnitude interrupt set register                  */
    uint32_t MAGTHRINTENACLR;    /**< 0x015C: Magnitude interrupt clear register                */
    uint32_t MAGTHRINTFLG;       /**< 0x0160: Magnitude interrupt flag register                 */
    uint32_t MAGTHRINTOFFSET;    /**< 0x0164: Magnitude interrupt offset register               */
    uint32_t GxFIFORESETCR[3U];  /**< 0x0168,0x016C,0x0170: Group 0-2 fifo reset register       */
    uint32_t G0RAMADDR;          /**< 0x0174: Group 0 RAM pointer register                      */
    uint32_t G1RAMADDR;          /**< 0x0178: Group 1 RAM pointer register                      */
    uint32_t G2RAMADDR;          /**< 0x017C: Group 2 RAM pointer register                      */
    uint32_t PARCR;              /**< 0x0180: Parity control register                           */
    uint32_t PARADDR;            /**< 0x0184: Parity error address register                     */
    uint32 pad[(0x200-0x188)/4];
} adcBASE_t;


/*lint -emacro(923,adcREG1) Hw access */
#define adcREG1 ((adcBASE_t *)0xFFF7C000U)
/*lint -emacro(923,adcREG2) Hw access */
#define adcREG2 ((adcBASE_t *)0xFFF7C200U)


#define adcMEM1 0xFF3E0000UL
#define adcMEM2 0xFF3A0000UL

#define REQENASET0_BASE_ADDR 0xFFFFFE30uL
#define REQENASET1_BASE_ADDR 0xFFFFFE34uL

#define REQENACLR0_BASE_ADDR 0xFFFFFE40uL
#define REQENACLR1_BASE_ADDR 0xFFFFFE44uL

#define ADC_IOMM_KICK0 0xFFFFEA38uL
#define ADC_IOMM_KICK1 0xFFFFEA3CuL

#endif
