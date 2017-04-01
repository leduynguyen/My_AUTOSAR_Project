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

#ifndef __ADC_JACINTO_H__
#define __ADC_JACINTO_H__

#include "Std_Types.h"

#define ADC_TSC_MAX_NBR_STEP_CONFIGS     16U

typedef volatile struct STEPCONFn {
    uint32 STEPCONFIG;
    uint32 STEPDELAY;
}STEPCONFnType;

typedef volatile struct TSC_ADC_Reg {
    uint32 REVISION;        /* 0h REVISION Section 26.5.1       */
    uint32 PADDING0[3];     /* Padding                          */
    uint32 SYSCONFIG;       /* 10h SYSCONFIG Section 26.5.2     */
    uint32 PADDING1[4];     /* Padding                          */
    uint32 IRQSTATUS_RAW;   /* 24h IRQSTATUS_RAW Section 26.5.3 */
    uint32 IRQSTATUS;       /* 28h IRQSTATUS Section 26.5.4     */
    uint32 IRQENABLE_SET;   /* 2Ch IRQENABLE_SET Section 26.5.5 */
    uint32 IRQENABLE_CLR;   /* 30h IRQENABLE_CLR Section 26.5.6 */
    uint32 IRQWAKEUP;       /* 34h IRQWAKEUP Section 26.5.7     */
    uint32 DMAENABLE_SET;   /* 38h DMAENABLE_SET Section 26.5.8 */
    uint32 DMAENABLE_CLR;   /* 3Ch DMAENABLE_CLR Section 26.5.9 */
    uint32 CTRL;            /* 40h CTRL Section 26.5.10         */
    uint32 ADCSTAT;         /* 44h ADCSTAT Section 26.5.11      */
    uint32 ADCRANGE;        /* 48h ADCRANGE Section 26.5.12     */
    uint32 ADC_CLKDIV;      /* 4Ch ADC_CLKDIV Section 26.5.13   */
    uint32 ADC_MISC;        /* 50h ADC_MISC Section 26.5.14     */
    uint32 STEPENABLE;      /* 54h STEPENABLE Section 26.5.15   */
    uint32 IDLECONFIG;      /* 58h IDLECONFIG Section 26.5.16   */
    uint32 TS_CHARGE_STEPCONFIG; /* 5Ch TS_CHARGE_STEPCONFIG Section 26.5.17 */
    uint32 TS_CHARGE_DELAY; /* 60h TS_CHARGE_DELAY Section 26.5.18 */
    STEPCONFnType STEPCONF[ADC_TSC_MAX_NBR_STEP_CONFIGS];
    #if 0
    uint32 STEPCONFIG1;     /* 64h STEPCONFIG1 Section 26.5.19  */
    uint32 STEPDELAY1;      /* 68h STEPDELAY1 Section 26.5.20   */
    uint32 STEPCONFIG2;     /* 6Ch STEPCONFIG2 Section 26.5.21  */
    uint32 STEPDELAY2;      /* 70h STEPDELAY2 Section 26.5.22   */
    uint32 STEPCONFIG3;     /* 74h STEPCONFIG3 Section 26.5.23  */
    uint32 STEPDELAY3;      /* 78h STEPDELAY3 Section 26.5.24   */
    uint32 STEPCONFIG4;     /* 7Ch STEPCONFIG4 Section 26.5.25  */
    uint32 STEPDELAY4;      /* 80h STEPDELAY4 Section 26.5.26   */
    uint32 STEPCONFIG5;     /* 84h STEPCONFIG5 Section 26.5.27  */
    uint32 STEPDELAY5;      /* 88h STEPDELAY5 Section 26.5.28   */
    uint32 STEPCONFIG6;     /* 8Ch STEPCONFIG6 Section 26.5.29  */
    uint32 STEPDELAY6;      /* 90h STEPDELAY6 Section 26.5.30   */
    uint32 STEPCONFIG7;     /* 94h STEPCONFIG7 Section 26.5.31  */
    uint32 STEPDELAY7;      /* 98h STEPDELAY7 Section 26.5.32   */
    uint32 STEPCONFIG8;     /* 9Ch STEPCONFIG8 Section 26.5.33  */
    uint32 STEPDELAY8;      /* A0h STEPDELAY8 Section 26.5.34   */
    uint32 STEPCONFIG9;     /* A4h STEPCONFIG9 Section 26.5.35  */
    uint32 STEPDELAY9;      /* A8h STEPDELAY9 Section 26.5.36   */
    uint32 STEPCONFIG10;    /* ACh STEPCONFIG10 Section 26.5.37 */
    uint32 STEPDELAY10;     /* B0h STEPDELAY10 Section 26.5.38  */
    uint32 STEPCONFIG11;    /* B4h STEPCONFIG11 Section 26.5.39 */
    uint32 STEPDELAY11;     /* B8h STEPDELAY11 Section 26.5.40  */
    uint32 STEPCONFIG12;    /* BCh STEPCONFIG12 Section 26.5.41 */
    uint32 STEPDELAY12;     /* C0h STEPDELAY12 Section 26.5.42  */
    uint32 STEPCONFIG13;    /* C4h STEPCONFIG13 Section 26.5.43 */
    uint32 STEPDELAY13;     /* C8h STEPDELAY13 Section 26.5.44  */
    uint32 STEPCONFIG14;    /* CCh STEPCONFIG14 Section 26.5.45 */
    uint32 STEPDELAY14;     /* D0h STEPDELAY14 Section 26.5.46  */
    uint32 STEPCONFIG15;    /* D4h STEPCONFIG15 Section 26.5.47 */
    uint32 STEPDELAY15;     /* D8h STEPDELAY15 Section 26.5.48  */
    uint32 STEPCONFIG16;    /* DCh STEPCONFIG16 Section 26.5.49 */
    uint32 STEPDELAY16;     /* E0h STEPDELAY16 Section 26.5.50  */
#endif
    uint32 FIFO0COUNT;      /* E4h FIFO0COUNT Section 26.5.51   */
    uint32 FIFO0THRESHOLD;  /* E8h FIFO0THRESHOLD Section 26.5.52 */
    uint32 DMA0REQ;         /* ECh DMA0REQ Section 26.5.53      */
    uint32 FIFO1COUNT;      /* F0h FIFO1COUNT Section 26.5.54   */
    uint32 FIFO1THRESHOLD;  /* F4h FIFO1THRESHOLD Section 26.5.55 */
    uint32 DMA1REQ;         /* F8h DMA1REQ Section 26.5.56      */
    uint32 PADDING2;        /* Padding                          */
    uint32 FIFO0DATA;       /* 100h FIFO0DATA Section 26.5.57   */
    uint32 PADDING3[63];    /* Padding                          */
    uint32 FIFO1DATA;       /* 200h FIFO1DATA Section 26.5.58   */
}TSC_ADC_RegType;


#define TSC_ADC_REG ((TSC_ADC_RegType *)0x54C00000uL)

#endif /* __ADC_JACINTO_H__ */
