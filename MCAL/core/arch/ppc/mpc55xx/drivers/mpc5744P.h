/**************************************************************************
 * FILE NAME: MPC5744P                       COPYRIGHT (c) Freescale 2013 *
 * REVISION:  1.0.1                                   All Rights Reserved *
 *                                                                        *
 * DESCRIPTION:                                                           *
 * This file contains all of the register and bit field definitions for   *
 * the mpc5744p.                                                          *
 *========================================================================*
 * UPDATE HISTORY                                                         *
 * REV      AUTHOR      DATE       DESCRIPTION OF CHANGE                  *
 * ---   -----------  ---------    ---------------------                  *
 * 0.2      P.A.      16-APR-12     -XBIC and PRAMC modules were added.   *
 *                                  -PWM module name was modified as      *
 *                                  FlexPWM (Just in the header file).    *
 *                                  -In FlexPWM, DCHMID, DCHPRI and TCDs  *
 *                                  were arranged in an array.            *
 *                                  -In the MEMU, SYS_RAM_CERR_STS and    *
 *                                  SYS_RAM_CERR_ADDR were organized as   *
 *                                  an array of 10 channels.              *
 *                                  FLASH_CERR_STS and FLASH_CERR _ADDR   *
 *                                  were organized as an array of 20      *
 *                                  channels. PERIPH_RAM_CERR_STS and     *
 *                                  PERIPH_RAM_CERR _ADDR were organized  *
 *                                  as an array of 2 channels.            *
 *                                  -In the PIT, LDVAL, CVAL, TCTRL,      *
 *                                  TFLG were organized as an array of    *
 *                                  4 timers.                             *
 *                                  -In the SMPU, EAR and EDR were        *
 *                                  organized as an array of 16 channels. *
 *                                  -In the STM, CCR, CIR and CMP were    *
 *                                  organized as an array of 4 channels.  *
 *                                  -In the XBAR, PRS and CRS were        *
 *                                  organized as an array of 8 channels.  *
 *                                  -In the DMAMUX, CHCFG was organized   *
 *                                  as an array of 16 channels.           *
 *                                  -In the DSPI, RXFR was organized as   *
 *                                  an array of 5 registers and TXFR was  *
 *                                  organized as an array of 5 registers. *
 *                                  -In the FR, SSR was organized as an   *
 *                                  array of 8 registers. SSCR was        *
 *                                  organized as an array of 4 registers. *
 *                                  NMVR was organized as an array of 6   *
 *                                  registers. MBCCSR, MBCCFR, MBFIDR,    *
 *                                  MBIDXR were organized as an array of  *
 *                                  64. MBDOR was organized as an array   *
 *                                  of 68 registers. LEETR was organized  *
 *                                  as an array of 6 registers.           *
 *                                  -In the INTC, CPR was organized as    *
 *                                  an array of 4 registers. IACKR was    *
 *                                  organized as an array of 4 registers. *
 *                                  EOIR was organized as an array of     *
 *                                  4 registers.                          *
 *                                  -In the ME, RUN_MC was organized as   *
 *                                  an array of 4 registers. RUN_PC was   *
 *                                  organized as an array of 8 registers. *
 *                                  LP_PC was organized as an array of    *
 *                                  8 registers.                          *
 *                                                                        *
 * 0.3      P.A.      07-MAY-12     -Adding PFLASH module.                *
 *                                                                        *
 * 0.4      P.A.      12-JUN-12     -Adding AIPS, C55FMC, LINFlexD, and   *
 *                                  SIUL2 modules.                        *
 *                                  -All the other modules are from the   *
 *                                  previous release.                     *
 *                                                                        *
 * 0.5      P.A.      13-JUN-12     -Generated using the last update of   *
 *                                  of AIPS, C55FMC, LINFlexD, and        *
 *                                  SIUL2 modules.                        *
 *                                                                        *
 * 0.6      P.A.      14-JUN-12     -Fix filter issues in AIPS module.    *
 *                                                                        *
 * 0.6.1    P.A.      14-JUN-12     -The IMCR register of SIUL2 module was*
 *                                  modified in the size of the array     *
 *                                  adding 32 more and decreasing the     *
 *                                  previous memory spot in 128.          *
 *                                  -Next drop of XML files is going to   *
 *                                  include this change.                  *
 *                                                                        *
 * 0.7      P.A.      27-JUN-12     -Adding latest files sended by Nick   *
 *                                  Evans.                                *
 *                                                                        *
 * 0.7.1    P.A.      28-JUN-12     -Some registers were arranged in      *
 *                                  arrays.                               *
 *                                                                        *
 * 0.7.2    P.A.      29-JUN-12     -Registers NCFS_CFG, NCFS_CFG, NCF_S, *
 *                                  NCF_E, NCF_TOE, IRQ_ALARM_EN, NMI_EN, *
 *                                  and EOUT_SIG_EN were expanded from    *
 *                                  arrays and they were indexed with     *
 *                                  their corresponding number.           *
 *                                                                        *
 * 0.7.3    P.A.      29-JUN-12     -Registers NCFS_CFG, NCFS_CFG, NCF_S, *
 *                                  NCF_E, NCF_TOE, IRQ_ALARM_EN, NMI_EN, *
 *                                  and EOUT_SIG_EN were changed to get   *
 *                                  something similar to McKinley.        *
 *                                                                        *
 * 0.7.4    P.A.      12-JUL-12     -GPDO and GPDI registers were added   *
 *                                  into an array.                        *
 *                                  -FCCU XML files has an incorrect      *
 *                                  address value for the tag             *
 *                                  componentUnitAddrAsHex. Nick Evans    *
 *                                  has the fixed one and he is going     *
 *                                  to send it untill the next release.   *
 *                                  I'm changing manually the value from  *
 *                                  0xFEED0000UL to 0xFBF58000UL.         *
 *                                                                        *
 * 0.7.5    P.A.      24-JUL-12     -CDRx_MCR_WLSIDE_n registers were     *
 *                                  removed. Also, CDRx_MCR_WLSIDE_0      *
 *                                  registers were put into an array and  *
 *                                  its name were modified to CDR_MCR.    *
 *                                  -Bit CIF of STM_CCR register was      *
 *                                  corrected to CEN.                     *
 *                                  -Registers T0CR-T7CR were put into    *
 *                                  an array.                             *
 *                                  -CLR_x_n were put into a struct named *
 *                                  CHANNEL.                              *
 *                                                                        *
 * 0.7.6    P.A.      26-JUL-12     -THRHLR registers were included into  *
 *                                  two arrays. First one includes from   *
 *                                  THRHLR0 to THRHLR3 and it was named   *
 *                                  as THRHLR. Second one includes from   *
 *                                  THRHLR4 to THRHLR15 and it was named  *
 *                                  as THRHLRx.                           *
 *                                                                        *
 *                                                                        *
 * 0.7.7    P.A.      27-JUL-12     -eTIMER channel registers were added  *
 *                                  into a structure call CHANNEL.        *
 *                                                                        *
 * 0.7.8    P.A.      31-JUL-12     -PS5 was removed from MC_ME module.   *
 *                                                                        *
 * 0.7.9    P.A.      06-AUG-12     -GPDO and GPDI registers were         *
 *                                   modified from vuint32_t to           *
 *                                   vuint8_t.                            *
 *                                                                        *
 * 0.7.10   P.A.      06-AUG-12     -PS5 was added again because Nick     *
 *                                  Evans notified about an errata in the *
 *                                  RM where PS5 was not included.        *
 *                                  -TCD array was modified from 64 to 32 *
 *                                  channels.                             *
 *                                                                        *
 * 0.7.11   P.A.      14-AUG-12     -CTR0_SLAVE module was removed.       *
 *                                  -Registers CPR, IACKR, and EOIR were  *
 *                                  removed for processor 1 and up. A     *
 *                                  reserved space was added for each one.*
 *                                                                        *
 * 0.7.12   P.A.      21-AUG-12     -PS5 was removed.                     *
 *                                                                        *
 * 0.7.13   P.A.      14-SEP-12     -Line uint8_t LFAST_reserved0[1]; was *
 *                                  removed from LFAST module.            *
 *                                                                        *
 * 0.7.14   P.A.      18-SEP-12     -CAN module was modified according    *
 *                                  with the changes requested by         *
 *                                  Barbara.                              *
 *                                  -Struct canbuf_t was added.           *
 *                                  -Some memory spots were added and     *
 *                                  modified.                             *
 *                                                                        *
 * 0.7.15   P.A.      26-SEP-12     -CLR_B and CLR_C registers of CTU     *
 *                                  module were commented out.            *
 *                                  -Also, the struct CHANNEL, that       *
 *                                  used to contain those registers, was  *
 *                                  removed.                              *
 *                                                                        *
 * 0.7.16   P.A.      03-OCT-12     -Register NICCH4 had an wrong name.   *
 *                                  I changed it to NIBBCH4.              *
 *                                                                        *
 * 0.7.17   P.A.      23-Oct-12     -Added                                *
 *               #define CRC_1 (*(volatile struct CRC_tag *) 0xFFF64010UL)*
 *               #define CRC_2 (*(volatile struct CRC_tag *) 0xFFF64020UL)*
 *                                                                        *
 *                                                                        *
 * 0.7.18   P.A.      26-Oct-12     -CRC module was modified adding:      *
 *                                     •	CRC_CFG1                        *
 *                                     •	CRC_INP1                        *
 *                                     •	CRC_CSTAT1                      *
 *                                     •	CRC_OUTP1                       *
 *                                     •	CRC_CFG2                        *
 *                                     •	CRC_INP2                        *
 *                                     •	CRC_CSTAT2                      *
 *                                     •	CRC_OUTP2                       *
 *                                     •	CRC_CFG3                        *
 *                                     •	CRC_INP3                        *
 *                                     •	CRC_CSTAT3                      *
 *                                     •	CRC_OUTP3                       *
 *                                                                        *
 * 0.7.19   M.D.      05-Dec-12     -Regenerated from SIDSC database      *
 *                                  -CLR_A, CLR_B, CLR_C compressed into  *
 *                                   CHANNEL struct                       *
 *                                  -CH_FMSG_DATA, CH_FMSG_CRC,           *
 *                                   CH_FMSG_TS, CH_SMSG_BIT3,            *
 *                                   CH_SMSG_BIT2, CH_SMSG_TS compressed  *
 *                                   into CHANNEL struct                  *
 *                                  -MB_CTRL compressed into array        *
 *                                                                        *
 * 0.7.20   M.D.      20-Dec-12     -Regenerated from SIDSC database      *
 *                                  -CAN Module:                          *
 *                                    inserted code in place of uint8_t   *
 *                                    CAN_reserved2[2096]; and in between *
 *                                    RXFIR and RXIMR                     *
 *                                  -Module: CTU                          *
 *                                   CLR_A, CLR_B, CLR_C -> union {CLR_A, *
 *                                    CLR_B, CLR_C} CLR                   *
 *                                  -Module: DMA                          *
 *                                   TCD_NBYTES_MLOFFNO,                  *
 *                                    TCD_NBYTES_MLOFFYES, TCD_NBYTES_MLNO*
 *                                    -> union {OFFNO, OFFYES, NO}        *
 *                                    NBYTES_ML                           *
 *                                   TCD_CITER_ELINKYES, TCD_CITER_ELINKNO*
 *                                    -> union {YES, NO} CITER_ELINK      *
 *                                   TCD_BITER_ELINKYES, TCD_BITER_ELINKNO*
 *                                    -> union {YES, NO} BITER_ELINK      *
 *                                  -Module: FR                           *
 *                                   MTSACFR, MTSBCFR -> MTSxCFR[2]       *
 *                                   RFARIR, RFBRIR -> RFxRIR[2]          *
 *                                  -Module: FlexPWM                      *
 *                                   SUB0_VAL0 through SUB0_VAL5 to array *
 *                                    SUB0_VAL[6]                         *
 *                                   SUB0_CNT, SUB0_INIT, SUB0_CTRL2,     *
 *                                    SUB0_CTRL1, SUB0_VAL[6], SUB0_OCTRL,*
 *                                    SUB0_STS, SUB0_INTEN, SUB0_DMAEN,   *
 *                                    SUB0_TCTRL, SUB0_DISMAP, SUB0_DTCNT,*
 *                                    SUB0_CAPTCTRLX, SUB0_CAPTCMPX,      *
 *                                    SUB0_CVAL0, SUB0_CVAL0CYC,          *
 *                                    SUB0_CVAL1, SUB0_CVAL1CYC to struct *
 *                                    {} SUB[4]                           *
 *                                  -Module: INTC                         *
 *                                   HIPRI0C0 -> HIPRIC0[4]               *
 *                                   LAT0C0 -> LATC0[4]                   *
 *                                   IMER0C0 -> TIMERC0[4]                *
 *                                  -Module: MC_CGM                       *
 *                                   PCS_DIVC1, PCS_DIVS1, PCS_DIVE1      *
 *                                    through 2 -> struct {DIVC, DIVS,    *
 *                                    DIVE} PCS[2]                        *
 *                                  -Module: SPI                          *
 *                                   CTAR0, CTAR0_SLAVE -> union {CTAR0,  *
 *                                    SLAVE} CTAR                         *
 *                                   CTAR from 1 through 3 to array       *
 *                                    CTAR[3]                             *
 *                                   PUSHR, PUSHR_SLAVE -> union {PUSHR,  *
 *                                    PUSHR_SLAVE} PUSHR                  *
 *                                  -Module: SRX                          *
 *                                   CH0_CLK_CTRL, CH0_STATUS, CH0_CONFIG *
 *                                    from 1 through 15 to struct {}      *
 *                                    CH1[16]                             *
 *                                   CH0_FMSG_DATA, CH0_FMSG_CRC,         *
 *                                    CH0_FMSG_TS, CH0_SMSG_BIT3,         *
 *                                    CH0_SMSG_BIT2, CH0_SMSG_TS -> struct*
 *                                    {} CH2[16]                          *
 *                                  -Module: STCU                         *
 *                                   LB0_CTRL, LB0_PCS, LB0_MISRELSW,     *
 *                                    LB0_MISREHSW from 1 through 3 to    *
 *                                    struct {CTRL, PCS, MISRELSW,        *
 *                                    MISREHSW} LB[4]                     *
 *                                                                        *
 * 0.7.21   M.D.      18-Feb-13     -Regenerated from SIDSC database      *
 *                                                                        *
 * 0.7.22   M.D.      22-Feb-13     -Removed duplicate LINFlexD registers *
 *                                                                        *
 * 0.7.23   M.D.      25-Feb-13     -Updated per Barbara                  *
 *                                                                        *
 * 0.7.24   M.D.      27-Feb-13     -More updates per Barbara             *
 *                                                                        *
 * 0.7.25   M.D.      28-Feb-13     -ADC THRHLR (offset 0x60) should be THRHLR[4] so there are 4 registers. Nick confirmed this error is in the RM and XML and he will make the correction in the source.
 *                                  -For the CTU registers, add a comment near CHANNEL[24] that for CLR_A_n, CLR_B_n, CLR_C_n,  n=1:24.
 *                                  -For INTC LATC[4], change to LATC0[4].
 *                                  -Add the missing SSCIR[8:15] registers. There’s no need to adjust the INTC_reserved4 size.
 *                                  -For SRX CH1[] and CH[2], follow the Mattherhorn format of uncompressed names.
 *                                  -For SRX PRS and CRS, follow Matterhorn format of arrays and add a comment to check the RM for unimplemented registers.
 *                                                                        *
 * 0.7.26   M.D.      11-Mar-13     -Changed ADC_reserved5 array from 28  *
 *                                   to 16                                *
 *                                  -Changed CAN Message Buffer definition*
 *                                   vuint32_t ID to                      *
 *                                    union {                             *
 *                                        vuint32_t R;                    *
 *                                        struct {                        *
 *                                            vuint32_t PRIO:3;           *
 *                                            vuint32_t ID_STD:11;        *
 *                                            vuint32_t ID_EXT:18;        *
 *                                        } B;                            *
 *                                    } ID;                               *
 *                                                                        *
 * 0.7.27   M.D.      17-Apr-13     -Corrected reserved memory within FCCU*
 *                                                                        *
 * 1.0.0    M.D.      11-Jun-13     -Updated per RM Rev2                  *
 *                                                                        *
 * 1.0.1    M.D.      26-Aug-13     -Removed register PS5 from MC_ME      *
 *                                  -Corrected address of DCL module      *
 *                                  -Some registers in FCCU were updated  *
 *                                   due to improvement in generation prog*
 *                                   resulting in the order of the bit    *
 *                                   names being resorted to the correct  *
 *                                   order of 31-0 instead of 0-32        *
 *                                                                        *
 *========================================================================*
 * COPYRIGHT:                                                             *
 *  Freescale Semiconductor, INC. All Rights Reserved. You are hereby     *
 *  granted a copyright license to use, modify, and distribute the        *
 *  SOFTWARE so long as this entire notice is retained without alteration *
 *  in any modified and/or redistributed versions, and that such modified *
 *  versions are clearly identified as such. No licenses are granted by   *
 *  implication, estoppel or otherwise under any patentsor trademarks     *
 *  of Freescale Semiconductor, Inc. This software is provided on an      *
 *  "AS IS" basis and without warranty.                                   *
 *                                                                        *
 *  To the maximum extent permitted by applicable law, Freescale          *
 *  Semiconductor DISCLAIMS ALL WARRANTIES WHETHER EXPRESS OR IMPLIED,    *
 *  INCLUDING IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A      *
 *  PARTICULAR PURPOSE AND ANY WARRANTY AGAINST INFRINGEMENT WITH REGARD  *
 *  TO THE SOFTWARE (INCLUDING ANY MODIFIED VERSIONS THEREOF) AND ANY     *
 *  ACCOMPANYING WRITTEN MATERIALS.                                       *
 *                                                                        *
 *  To the maximum extent permitted by applicable law, IN NO EVENT        *
 *  SHALL Freescale Semiconductor BE LIABLE FOR ANY DAMAGES WHATSOEVER    *
 *  (INCLUDING WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,  *
 *  BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR OTHER         *
 *  PECUNIARY LOSS) ARISING OF THE USE OR INABILITY TO USE THE SOFTWARE.  *
 *                                                                        *
 *  Freescale Semiconductor assumes no responsibility for the             *
 *  maintenance and support of this software                              *
 *                                                                        *
 **************************************************************************/
/*>>>>>>> NOTE! this file is auto-generated please do not edit it! <<<<<<<*/

/**************************************************************************
 * Example register & bit field write:                                    *
 *                                                                        *
 *  <MODULE>.<REGISTER>.B.<BIT> = 1;                                      *
 *  <MODULE>.<REGISTER>.R       = 0x10000000;                             *
 *                                                                        *
 **************************************************************************/

#ifndef _MPC5744P_H_
#define _MPC5744P_H_
#include "typedefs.h"
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __MWERKS__
#pragma push
#pragma ANSI_strict off
#endif
#ifdef __ghs__
#pragma ghs nowarning 618
#endif


/* ============================================================================
   =============================== Module: ADC ================================
   ============================================================================ */

struct ADC_tag {
  union {                              /* Main Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t OWREN:1;               /* Overwrite enable. */
      vuint32_t WLSIDE:1;              /* Write Left/Right aligned. */
      vuint32_t MODE:1;                /* One_Shot/Scan. */
      vuint32_t  :1;                   /* Reserved. */
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t NSTART:1;
      vuint32_t  :1;
      vuint32_t JTRGEN:1;              /* Injection external trigger enable. */
      vuint32_t JEDGE:1;               /* Injection trigger edge selection. */
      vuint32_t JSTART:1;              /* Injection start. */
      vuint32_t  :2;
      vuint32_t CTUEN:1;               /* Crosstrigger Unit Enable. */
      vuint32_t  :1;
      vuint32_t STCL:1;                /* Self Testing Configuration Lock. */
      vuint32_t  :6;
      vuint32_t ADCLKSEL:1;            /* Analog Clock frequency Selector. */
      vuint32_t ABORTCHAIN:1;         /* Abort Chain. */
      vuint32_t ABORT:1;               /* Abort Conversion. */
      vuint32_t ACKO:1;                /* Auto clock off enable. */
      vuint32_t  :2;
      vuint32_t REFSEL:2;              /* Reference voltage selection for ADC analog part. */
      vuint32_t PWDN:1;                /* Power-down enable. */
    } B;
  } MCR;

  union {                              /* Main Status register */
    vuint32_t R;
    struct {
      vuint32_t CALIBRTD:1;            /* This bit indicates the ADC calibration status. */
      vuint32_t  :6;
      vuint32_t NSTART:1;              /* This status bit is used to signal that a Normal conversion is ongoing. */
      vuint32_t JABORT:1;
      vuint32_t  :2;
      vuint32_t JSTART:1;              /* This status bit is used to signal that an Injected conversion is ongoing. */
      vuint32_t  :1;
      vuint32_t SELF_TEST_S:1;         /* This status bit signals that self test conversion is ongoing. */
      vuint32_t  :1;
      vuint32_t CTUSTART:1;            /* This status bit is used to signal that a CTU conversion is ongoing. */
      vuint32_t CHADDR:7;              /* Channel under measure address. */
      vuint32_t  :3;
      vuint32_t ACKO:1;                /* Auto clock off enable. */
      vuint32_t  :2;
      vuint32_t ADCSTATUS:3;           /* Status of the ADC. */
    } B;
  } MSR;

  uint8_t ADC_reserved0[8];
  union {                              /* Interrupt Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :27;
      vuint32_t EOCTU:1;
      vuint32_t JEOC:1;                /* End of injected channel conversion. */
      vuint32_t JECH:1;                /* End of injected chain conversion. */
      vuint32_t EOC:1;                 /* End of channel conversion. */
      vuint32_t ECH:1;                 /* End of chain conversion. */
    } B;
  } ISR_STATUS;                        /* Renamed from ISR due to name clashing with macro in OS */

  union {                              /* Channel Pending register 0 */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t EOCCH15:1;             /* EOC Channel 15. */
      vuint32_t EOCCH14:1;             /* EOC Channel 14. */
      vuint32_t EOCCH13:1;             /* EOC Channel 13. */
      vuint32_t EOCCH12:1;             /* EOC Channel 12. */
      vuint32_t EOCCH11:1;             /* EOC Channel 11. */
      vuint32_t EOCCH10:1;             /* EOC Channel 10. */
      vuint32_t EOCCH9:1;              /* EOC Channel 9. */
      vuint32_t EOCCH8:1;              /* EOC Channel 8. */
      vuint32_t EOCCH7:1;              /* EOC Channel 7. */
      vuint32_t EOCCH6:1;              /* EOC Channel 6. */
      vuint32_t EOCCH5:1;              /* EOC Channel 5. */
      vuint32_t EOCCH4:1;              /* EOC Channel 4. */
      vuint32_t EOCCH3:1;              /* EOC Channel 3. */
      vuint32_t EOCCH2:1;              /* EOC Channel 2. */
      vuint32_t EOCCH1:1;              /* EOC Channel 1. */
      vuint32_t EOCCH0:1;              /* EOC Channel 0. */
    } B;
  } CEOCFR0;

  uint8_t ADC_reserved1[8];
  union {                              /* Interrupt Mask Register */
    vuint32_t R;
    struct {
      vuint32_t  :27;
      vuint32_t MSKEOCTU:1;            /* Mask bit for EOCTU. */
      vuint32_t MSKJEOC:1;             /* Mask bit for JEOC. */
      vuint32_t MSKJECH:1;             /* Mask bit for JECH. */
      vuint32_t MSKEOC:1;              /* Mask bit for EOC. */
      vuint32_t MSKECH:1;              /* Mask bit for ECH. */
    } B;
  } IMR;

  union {                              /* Channel Interrupt Mask Register 0 */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t CIM15:1;               /* Channel 15 interrupt enable. */
      vuint32_t CIM14:1;               /* Channel 14 interrupt enable. */
      vuint32_t CIM13:1;               /* Channel 13 interrupt enable. */
      vuint32_t CIM12:1;               /* Channel 12 interrupt enable. */
      vuint32_t CIM11:1;               /* Channel 11 interrupt enable. */
      vuint32_t CIM10:1;               /* Channel 10 interrupt enable. */
      vuint32_t CIM9:1;                /* Channel 9 interrupt enable. */
      vuint32_t CIM8:1;                /* Channel 8 interrupt enable. */
      vuint32_t CIM7:1;                /* Channel 7 interrupt enable. */
      vuint32_t CIM6:1;                /* Channel 6 interrupt enable. */
      vuint32_t CIM5:1;                /* Channel 5 interrupt enable. */
      vuint32_t CIM4:1;                /* Channel 4 interrupt enable. */
      vuint32_t CIM3:1;                /* Channel 3 interrupt enable. */
      vuint32_t CIM2:1;                /* Channel 2 interrupt enable. */
      vuint32_t CIM1:1;                /* Channel 1 interrupt enable. */
      vuint32_t CIM0:1;                /* Channel 0 interrupt enable. */
    } B;
  } CIMR[1];

  uint8_t ADC_reserved2[8];
  union {                              /* Watchdog Threshold Interrupt Status Register */
    vuint32_t R;
    struct {
      vuint32_t WDG15H:1;
      vuint32_t WDG15L:1;
      vuint32_t WDG14H:1;
      vuint32_t WDG14L:1;
      vuint32_t WDG13H:1;
      vuint32_t WDG13L:1;
      vuint32_t WDG12H:1;
      vuint32_t WDG12L:1;
      vuint32_t WDG11H:1;
      vuint32_t WDG11L:1;
      vuint32_t WDG10H:1;
      vuint32_t WDG10L:1;
      vuint32_t WDG9H:1;
      vuint32_t WDG9L:1;
      vuint32_t WDG8H:1;
      vuint32_t WDG8L:1;
      vuint32_t WDG7H:1;
      vuint32_t WDG7L:1;
      vuint32_t WDG6H:1;
      vuint32_t WDG6L:1;
      vuint32_t WDG5H:1;
      vuint32_t WDG5L:1;
      vuint32_t WDG4H:1;
      vuint32_t WDG4L:1;
      vuint32_t WDG3H:1;
      vuint32_t WDG3L:1;
      vuint32_t WDG2H:1;
      vuint32_t WDG2L:1;
      vuint32_t WDG1H:1;
      vuint32_t WDG1L:1;
      vuint32_t WDG0H:1;
      vuint32_t WDG0L:1;
    } B;
  } WTISR;

  union {                              /* Watchdog Threshold Interrupt Mask Register */
    vuint32_t R;
    struct {
      vuint32_t MSKWDG15H:1;
      vuint32_t MSKWDG15L:1;
      vuint32_t MSKWDG14H:1;
      vuint32_t MSKWDG14L:1;
      vuint32_t MSKWDG13H:1;
      vuint32_t MSKWDG13L:1;
      vuint32_t MSKWDG12H:1;
      vuint32_t MSKWDG12L:1;
      vuint32_t MSKWDG11H:1;
      vuint32_t MSKWDG11L:1;
      vuint32_t MSKWDG10H:1;
      vuint32_t MSKWDG10L:1;
      vuint32_t MSKWDG9H:1;
      vuint32_t MSKWDG9L:1;
      vuint32_t MSKWDG8H:1;
      vuint32_t MSKWDG8L:1;
      vuint32_t MSKWDG7H:1;
      vuint32_t MSKWDG7L:1;
      vuint32_t MSKWDG6H:1;
      vuint32_t MSKWDG6L:1;
      vuint32_t MSKWDG5H:1;
      vuint32_t MSKWDG5L:1;
      vuint32_t MSKWDG4H:1;
      vuint32_t MSKWDG4L:1;
      vuint32_t MSKWDG3H:1;
      vuint32_t MSKWDG3L:1;
      vuint32_t MSKWDG2H:1;
      vuint32_t MSKWDG2L:1;
      vuint32_t MSKWDG1H:1;
      vuint32_t MSKWDG1L:1;
      vuint32_t MSKWDG0H:1;
      vuint32_t MSKWDG0L:1;
    } B;
  } WTIMR;

  uint8_t ADC_reserved3[8];
  union {                              /* DMA Enable register */
    vuint32_t R;
    struct {
      vuint32_t  :30;
      vuint32_t DCLR:1;                /* DMA Clear sequence enable. */
      vuint32_t DMAEN:1;               /* DMA global enable. */
    } B;
  } DMAE;

  union {                              /* DMA Channel Select Register 0 */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t DMA15:1;               /* DMA enable for channel 15. */
      vuint32_t DMA14:1;               /* DMA enable for channel 14. */
      vuint32_t DMA13:1;               /* DMA enable for channel 13. */
      vuint32_t DMA12:1;               /* DMA enable for channel 12. */
      vuint32_t DMA11:1;               /* DMA enable for channel 11. */
      vuint32_t DMA10:1;               /* DMA enable for channel 10. */
      vuint32_t DMA9:1;                /* DMA enable for channel 9. */
      vuint32_t DMA8:1;                /* DMA enable for channel 8. */
      vuint32_t DMA7:1;                /* DMA enable for channel 7. */
      vuint32_t DMA6:1;                /* DMA enable for channel 6. */
      vuint32_t DMA5:1;                /* DMA enable for channel 5. */
      vuint32_t DMA4:1;                /* DMA enable for channel 4. */
      vuint32_t DMA3:1;                /* DMA enable for channel 3. */
      vuint32_t DMA2:1;                /* DMA enable for channel 2. */
      vuint32_t DMA1:1;                /* DMA enable for channel 1. */
      vuint32_t DMA0:1;                /* DMA enable for channel 0. */
    } B;
  } DMAR0;

  uint8_t ADC_reserved4[24];
  union {                              /* Threshold Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t THRH:12;               /* High threshold value for watchdog n. */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value for watchdog n. */
    } B;
  } THRHLR[4];

  uint8_t ADC_reserved5[16];
  union {                              /* Presampling Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :25;
      vuint32_t PREVAL2:2;             /* Internal voltage selection for Presampling */
      vuint32_t PREVAL1:2;             /* Internal voltage selection for Presampling. */
      vuint32_t PREVAL0:2;             /* Internal voltage selection for Presampling. */
      vuint32_t PRECONV:1;             /* Convert Presampled value */
    } B;
  } PSCR;

  union {                              /* Presampling register 0 */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t PRES15:1;              /* Presampling enable for channel 15. */
      vuint32_t PRES14:1;              /* Presampling enable for channel 14. */
      vuint32_t PRES13:1;              /* Presampling enable for channel 13. */
      vuint32_t PRES12:1;              /* Presampling enable for channel 12. */
      vuint32_t PRES11:1;              /* Presampling enable for channel 11. */
      vuint32_t PRES10:1;              /* Presampling enable for channel 10. */
      vuint32_t PRES9:1;               /* Presampling enable for channel 9. */
      vuint32_t PRES8:1;               /* Presampling enable for channel 8. */
      vuint32_t PRES7:1;               /* Presampling enable for channel 7. */
      vuint32_t PRES6:1;               /* Presampling enable for channel 6. */
      vuint32_t PRES5:1;               /* Presampling enable for channel 5. */
      vuint32_t PRES4:1;               /* Presampling enable for channel 4. */
      vuint32_t PRES3:1;               /* Presampling enable for channel 3. */
      vuint32_t PRES2:1;               /* Presampling enable for channel 2. */
      vuint32_t PRES1:1;               /* Presampling enable for channel 1. */
      vuint32_t PRES0:1;               /* Presampling enable for channel 0. */
    } B;
  } PSR0;

  uint8_t ADC_reserved6[12];
  union {
      union {                              /* Conversion Timing Register */
        vuint32_t R;
        struct {
          vuint32_t  :24;
          vuint32_t INPSAMP:8;             /* Configuration of sampling phase duration. */
        } B;
      }CTR[2];
      struct {
          union {                              /* Conversion Timing Register 0 */
            vuint32_t R;
            struct {
              vuint32_t  :24;
              vuint32_t INPSAMP:8;             /* Configuration of sampling phase duration. */
            } B;
          } CTR0;

          union {                              /* Conversion Timing Register 1 */
            vuint32_t R;
            struct {
              vuint32_t  :24;
              vuint32_t INPSAMP:7;             /* Configuration of sampling phase duration. */
              vuint32_t TSENSOR_SEL:1;         /* Voltage Select for temperature sensor. */
            } B;
          } CTR1;
      };
  };
  uint8_t ADC_reserved7[8];
  union {                              /* Normal Conversion Mask Register 0 */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t CH15:1;                /* Sampling enable for channel 15. */
      vuint32_t CH14:1;                /* Sampling enable for channel 14. */
      vuint32_t CH13:1;                /* Sampling enable for channel 13. */
      vuint32_t CH12:1;                /* Sampling enable for channel 12. */
      vuint32_t CH11:1;                /* Sampling enable for channel 11. */
      vuint32_t CH10:1;                /* Sampling enable for channel 10. */
      vuint32_t CH9:1;                 /* Sampling enable for channel 9. */
      vuint32_t CH8:1;                 /* Sampling enable for channel 8. */
      vuint32_t CH7:1;                 /* Sampling enable for channel 7. */
      vuint32_t CH6:1;                 /* Sampling enable for channel 6. */
      vuint32_t CH5:1;                 /* Sampling enable for channel 5. */
      vuint32_t CH4:1;                 /* Sampling enable for channel 4. */
      vuint32_t CH3:1;                 /* Sampling enable for channel 3. */
      vuint32_t CH2:1;                 /* Sampling enable for channel 2. */
      vuint32_t CH1:1;                 /* Sampling enable for channel 1. */
      vuint32_t CH0:1;                 /* Sampling enable for channel 0. */
    } B;
  } NCMR[1];

  uint8_t ADC_reserved8[12];
  union {                              /* Injected Conversion Mask Register 0 */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t CH15:1;                /* Sampling enable for channel 15. */
      vuint32_t CH14:1;                /* Sampling enable for channel 14. */
      vuint32_t CH13:1;                /* Sampling enable for channel 13. */
      vuint32_t CH12:1;                /* Sampling enable for channel 12. */
      vuint32_t CH11:1;                /* Sampling enable for channel 11. */
      vuint32_t CH10:1;                /* Sampling enable for channel 10. */
      vuint32_t CH9:1;                 /* Sampling enable for channel 9. */
      vuint32_t CH8:1;                 /* Sampling enable for channel 8. */
      vuint32_t CH7:1;                 /* Sampling enable for channel 7. */
      vuint32_t CH6:1;                 /* Sampling enable for channel 6. */
      vuint32_t CH5:1;                 /* Sampling enable for channel 5. */
      vuint32_t CH4:1;                 /* Sampling enable for channel 4. */
      vuint32_t CH3:1;                 /* Sampling enable for channel 3. */
      vuint32_t CH2:1;                 /* Sampling enable for channel 2. */
      vuint32_t CH1:1;                 /* Sampling enable for channel 1. */
      vuint32_t CH0:1;                 /* Sampling enable for channel 0. */
    } B;
  } JCMR0;

  uint8_t ADC_reserved9[16];
  union {                              /* Power Down Exit Delay Register */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t PDED:8;
    } B;
  } PDEDR;

  uint8_t ADC_reserved10[52];
  union {                              /* Channel Data Register n (Precision Channels) */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t VALID:1;               /* Used to notify when the data is valid (a new value has been written). It is automatically cleared when data is read. */
      vuint32_t OVERW:1;               /* Overwrite data */
      vuint32_t RESULT:2;
      vuint32_t CDATA:16;              /* Converted Data 11:0. */
    } B;
  } CDR[16];

  uint8_t ADC_reserved11[320];
  union {                              /* Threshold Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t THRH:12;               /* High threshold value for channel x. */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value for channel x. */
    } B;
  } THRHLR4;

  union {                              /* Threshold Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t THRH:12;               /* High threshold value for channel x. */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value for channel x. */
    } B;
  } THRHLR5;

  union {                              /* Threshold Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t THRH:12;               /* High threshold value for channel x. */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value for channel x. */
    } B;
  } THRHLR6;

  union {                              /* Threshold Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t THRH:12;               /* High threshold value for channel x. */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value for channel x. */
    } B;
  } THRHLR7;

  union {                              /* Threshold Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t THRH:12;               /* High threshold value for channel x. */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value for channel x. */
    } B;
  } THRHLR8;

  union {                              /* Threshold Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t THRH:12;               /* High threshold value for channel x. */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value for channel x. */
    } B;
  } THRHLR9;

  union {                              /* Threshold Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t THRH:12;               /* High threshold value for channel x. */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value for channel x. */
    } B;
  } THRHLR10;

  union {                              /* Threshold Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t THRH:12;               /* High threshold value for channel x. */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value for channel x. */
    } B;
  } THRHLR11;

  union {                              /* Threshold Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t THRH:12;               /* High threshold value for channel x. */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value for channel x. */
    } B;
  } THRHLR12;

  union {                              /* Threshold Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t THRH:12;               /* High threshold value for channel x. */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value for channel x. */
    } B;
  } THRHLR13;

  union {                              /* Threshold Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t THRH:12;               /* High threshold value for channel x. */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value for channel x. */
    } B;
  } THRHLR14;

  union {                              /* Threshold Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t THRH:12;               /* High threshold value for channel x. */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value for channel x. */
    } B;
  } THRHLR15;

  union {                              /* Channel Watchdog Select Register 0 */
    vuint32_t R;
    struct {
      vuint32_t WSEL_CH7:4;            /* Channel Watchdog select for channel 7. */
      vuint32_t WSEL_CH6:4;            /* Channel Watchdog select for channel 6. */
      vuint32_t WSEL_CH5:4;            /* Channel Watchdog select for channel 5. */
      vuint32_t WSEL_CH4:4;            /* Channel Watchdog select for channel 4. */
      vuint32_t WSEL_CH3:4;            /* Channel Watchdog select for channel 3. */
      vuint32_t WSEL_CH2:4;            /* Channel Watchdog select for channel 2. */
      vuint32_t WSEL_CH1:4;            /* Channel Watchdog select for channel 1. */
      vuint32_t WSEL_CH0:4;            /* Channel Watchdog select for channel 0. */
    } B;
  } CWSELR0;

  union {                              /* Channel Watchdog Select Register 1 */
    vuint32_t R;
    struct {
      vuint32_t WSEL_CH15:4;           /* Channel Watchdog select for channel 15. */
      vuint32_t WSEL_CH14:4;           /* Channel Watchdog select for channel 14. */
      vuint32_t WSEL_CH13:4;           /* Channel Watchdog select for channel 13. */
      vuint32_t WSEL_CH12:4;           /* Channel Watchdog select for channel 12. */
      vuint32_t WSEL_CH11:4;           /* Channel Watchdog select for channel 11. */
      vuint32_t WSEL_CH10:4;           /* Channel Watchdog select for channel 10. */
      vuint32_t WSEL_CH9:4;            /* Channel Watchdog select for channel 9. */
      vuint32_t WSEL_CH8:4;            /* Channel Watchdog select for channel 8. */
    } B;
  } CWSELR1;

  uint8_t ADC_reserved12[40];
  union {                              /* Channel Watchdog Enable Register 0 */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t CWEN15:1;              /* Sampling enable for channel 15. */
      vuint32_t CWEN14:1;              /* Sampling enable for channel 14. */
      vuint32_t CWEN13:1;              /* Sampling enable for channel 13. */
      vuint32_t CWEN12:1;              /* Sampling enable for channel 12. */
      vuint32_t CWEN11:1;              /* Sampling enable for channel 11. */
      vuint32_t CWEN10:1;              /* Sampling enable for channel 10. */
      vuint32_t CWEN9:1;               /* Sampling enable for channel 9. */
      vuint32_t CWEN8:1;               /* Sampling enable for channel 8. */
      vuint32_t CWEN7:1;               /* Sampling enable for channel 7. */
      vuint32_t CWEN6:1;               /* Sampling enable for channel 6. */
      vuint32_t CWEN5:1;               /* Sampling enable for channel 5. */
      vuint32_t CWEN4:1;               /* Sampling enable for channel 4. */
      vuint32_t CWEN3:1;               /* Sampling enable for channel 3. */
      vuint32_t CWEN2:1;               /* Sampling enable for channel 2. */
      vuint32_t CWEN1:1;               /* Sampling enable for channel 1. */
      vuint32_t CWEN0:1;               /* Sampling enable for channel 0. */
    } B;
  } CWENR0;

  uint8_t ADC_reserved13[12];
  union {                              /* Analog Watchdog Out of Range Register 0 */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t AWOR_CH15:1;           /* Analog watchdog out of range for channel 15. */
      vuint32_t AWOR_CH14:1;           /* Analog watchdog out of range for channel 14. */
      vuint32_t AWOR_CH13:1;           /* Analog watchdog out of range for channel 13. */
      vuint32_t AWOR_CH12:1;           /* Analog watchdog out of range for channel 12. */
      vuint32_t AWOR_CH11:1;           /* Analog watchdog out of range for channel 11. */
      vuint32_t AWOR_CH10:1;           /* Analog watchdog out of range for channel 10. */
      vuint32_t AWOR_CH9:1;            /* Analog watchdog out of range for channel 9. */
      vuint32_t AWOR_CH8:1;            /* Analog watchdog out of range for channel 8. */
      vuint32_t AWOR_CH7:1;            /* Analog watchdog out of range for channel 7. */
      vuint32_t AWOR_CH6:1;            /* Analog watchdog out of range for channel 6. */
      vuint32_t AWOR_CH5:1;            /* Analog watchdog out of range for channel 5. */
      vuint32_t AWOR_CH4:1;            /* Analog watchdog out of range for channel 4. */
      vuint32_t AWOR_CH3:1;            /* Analog watchdog out of range for channel 3. */
      vuint32_t AWOR_CH2:1;            /* Analog watchdog out of range for channel 2. */
      vuint32_t AWOR_CH1:1;            /* Analog watchdog out of range for channel 1. */
      vuint32_t AWOR_CH0:1;            /* Analog watchdog out of range for channel 0. */
    } B;
  } AWORR0;

  uint8_t ADC_reserved14[76];
  union {                              /* Self Test Configuration Register 1 */
    vuint32_t R;
    struct {
      vuint32_t INPSAMP_C:8;
      vuint32_t  :8;
      vuint32_t INPSAMP_S:8;
      vuint32_t  :8;
    } B;
  } STCR1;

  union {                              /* Self Test Configuration Register 2 */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t MSKWDSERR:1;
      vuint32_t SERR:1;
      vuint32_t MSKWDTERR:1;           /* Interrupt enable (STSR.WDTERR status bit) */
      vuint32_t  :1;
      vuint32_t MSKST_EOC:1;           /* Interrupt Enable bit for STSR2.ST_EOC */
      vuint32_t  :4;
      vuint32_t MSKWDG_EOA_C:1;        /* Interrupt enable (WDG_EOA_C status bit) */
      vuint32_t  :1;
      vuint32_t MSKWDG_EOA_S:1;        /* Interrupt enable (WDG_EOA_S status bit) */
      vuint32_t MSKERR_C:1;            /* Interrupt enable (ERR_C status bit) */
      vuint32_t  :1;
      vuint32_t MSKERR_S2:1;           /* Interrupt enable (ERR_S2 status bit) */
      vuint32_t MSKERR_S1:1;           /* Interrupt enable (ERR_S1 status bit) */
      vuint32_t MSKERR_S0:1;           /* Interrupt enable (ERR_S1 status bit) */
      vuint32_t  :3;
      vuint32_t EN:1;                  /* Self testing channel enable. The TEST conversions are enabled. */
      vuint32_t  :2;
      vuint32_t FMA_WDSERR:1;          /* Fault mapping for the Watchdog Sequence error. */
      vuint32_t FMA_WDTERR:1;          /* Fault mapping for the Watchdog Timer error. */
      vuint32_t FMA_C:1;               /* Fault mapping for self test algorithm C. */
      vuint32_t  :1;
      vuint32_t FMA_S:1;               /* Fault mapping for the self test algorithm BGAP. */
    } B;
  } STCR2;

  union {                              /* Self Test Configuration Register 3 */
    vuint32_t R;
    struct {
      vuint32_t  :22;
      vuint32_t ALG:2;                 /* Algorithm scheduling. */
      vuint32_t  :3;
      vuint32_t MSTEP:5;
    } B;
  } STCR3;

  union {                              /* Self Test Baud Rate Register */
    vuint32_t R;
    struct {
      vuint32_t  :13;
      vuint32_t WDT:3;
      vuint32_t  :8;
      vuint32_t BR:8;                  /* Baud rate for the selected algorithm in SCAN mode (MCR[MODE] = 1). */
    } B;
  } STBRR;

  union {                              /* Self Test Status Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t WDSERR:1;
      vuint32_t  :1;
      vuint32_t WDTERR:1;
      vuint32_t OVERWR:1;              /* Overwrite error. */
      vuint32_t ST_EOC:1;              /* Self Test EOC Bit. */
      vuint32_t  :4;
      vuint32_t WDG_EOA_C:1;
      vuint32_t  :1;
      vuint32_t WDG_EOA_S:1;
      vuint32_t ERR_C:1;
      vuint32_t  :1;
      vuint32_t ERR_S2:1;
      vuint32_t ERR_S1:1;
      vuint32_t ERR_S0:1;
      vuint32_t  :1;
      vuint32_t STEP_C:5;              /* Step of the algorithm C when an ERR_C has occurred. */
      vuint32_t  :5;
    } B;
  } STSR1;

  union {                              /* Self Test Status Register 2 */
    vuint32_t R;
    struct {
      vuint32_t OVFL:1;                /* Overflow Bit */
      vuint32_t  :3;
      vuint32_t DATA1:12;              /* Test channel converted data when the ERR_S1 has occurred. */
      vuint32_t  :4;
      vuint32_t DATA0:12;              /* Test channel converted data when the ERR_S1 has occurred. */
    } B;
  } STSR2;

  union {                              /* Self Test Status Register 3 */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t DATA1:12;              /* Test channel converted data when the ERR_S2 has occurred. */
      vuint32_t  :4;
      vuint32_t DATA0:12;              /* Test channel converted data when the ERR_S0 has occurred. */
    } B;
  } STSR3;

  union {                              /* Self Test Status Register 4 */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t DATA1:12;              /* Test channel converted data when the ERR_C has occurred. */
      vuint32_t  :4;
      vuint32_t  :12;
    } B;
  } STSR4;

  uint8_t ADC_reserved15[16];
  union {                              /* Self Test Data Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t VALID:1;               /* Valid data. */
      vuint32_t OWERWR:1;              /* Overwrite data. */
      vuint32_t  :6;
      vuint32_t TCDATA:12;             /* Test channel converted data. (In 2's complement format) */
    } B;
  } STDR1;

  union {                              /* Self Test Data Register 2 */
    vuint32_t R;
    struct {
      vuint32_t FDATA:12;
      vuint32_t VALID:1;               /* Valid data. */
      vuint32_t OWERWR:1;              /* Overwrite data. */
      vuint32_t  :6;
      vuint32_t IDATA:12;
    } B;
  } STDR2;

  uint8_t ADC_reserved16[8];
  union {                              /* Self Test Analog Watchdog Register 0 */
    vuint32_t R;
    struct {
      vuint32_t AWDE:1;                /* Analog watchdog enable (related to the algorithm S (step 0)) */
      vuint32_t WDTE:1;                /* Watchdog timer enable (related to the algorithm S) */
      vuint32_t  :2;
      vuint32_t THRH:12;               /* High threshold value for channel 0. */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value for channel 0. */
    } B;
  } STAW0R;

  union {                              /* Self Test Analog Watchdog Register 1A */
    vuint32_t R;
    struct {
      vuint32_t AWDE:1;                /* Analog watchdog enable related to the algorithm S (step1). */
      vuint32_t  :3;
      vuint32_t THRH:12;               /* High threshold value (integer part) for test channel for algorithm S (step 1) (unsigned coding). */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value (integer part) for test channel for algorithm S (step 1) (unsigned coding). */
    } B;
  } STAW1AR;

  union {                              /* Self Test Analog Watchdog Register 1B */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t THRH:12;               /* High threshold value (fractional part) for test channel for algorithm S (step 1)(unsigned coding). */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value (fractional part) for test channel for algorithm S (step 1) (unsigned coding). */
    } B;
  } STAW1BR;

  union {                              /* Self Test Analog Watchdog Register 2 */
    vuint32_t R;
    struct {
      vuint32_t AWDE:1;                /* Analog watchdog enable related to the algorithm S (step2). */
      vuint32_t  :19;
      vuint32_t THRL:12;               /* Low threshold value for channel x (unsigned coding). If the analog watchdog is enabled, the STSR1.ERR_S2 status bit is set if STDR1.TCDATA < THRL. */
    } B;
  } STAW2R;

  uint8_t ADC_reserved17[4];
  union {                              /* Self Test Analog Watchdog Register 4 */
    vuint32_t R;
    struct {
      vuint32_t AWDE:1;                /* Analog watchdog enable (related to the algorithm C) */
      vuint32_t WDTE:1;                /* Watchdog timer enable (related to the algorithm C). */
      vuint32_t  :2;
      vuint32_t THRH:12;               /* High threshold value for channel sampled for C algorithm. */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value for channel sampled for the C self test algorithm. */
    } B;
  } STAW4R;

  union {                              /* Self Test Analog Watchdog Register 5 */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t THRH:12;               /* High threshold value for the algorithm C (step1 to step CS-1). */
      vuint32_t  :4;
      vuint32_t THRL:12;               /* Low threshold value for the algorithm C (step1 to step CS-1). */
    } B;
  } STAW5R;

  uint8_t ADC_reserved18[4];
  union {                              /* Calibration, BIST Control and status Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t  :2;
      vuint32_t TSAMP:2;               /* Test Sample period in Calibration, BIST and Offset calculation process. */
      vuint32_t  :3;
      vuint32_t  :8;
      vuint32_t C_T_BUSY:1;
      vuint32_t  :1;
      vuint32_t  :6;
      vuint32_t  :1;
      vuint32_t NR_SMPL:2;             /* Number of Samples for averaging. */
      vuint32_t AVG_EN:1;              /* Average Enable (for Calibration only). */
      vuint32_t TEST_FAIL:1;           /* Test Fail. */
      vuint32_t  :2;
      vuint32_t TEST_EN:1;             /* Enable the test. */
    } B;
  } CALBISTREG;

  uint8_t ADC_reserved19[4];
  union {                              /* Offset and Gain User Register */
    vuint32_t R;
    struct {
      vuint32_t  :6;
      vuint32_t GAIN_USER:10;
      vuint32_t  :8;
      vuint32_t OFFSET_USER:8;
    } B;
  } OFSGNUSR;

  uint8_t ADC_reserved20[12];
  union {                              /* Alternate Result register */
    vuint32_t R;
    struct {
      vuint32_t  :32;
    } B;
  } ALTR;
};


/* ============================================================================
   =============================== Module: AIPS ===============================
   ============================================================================ */

struct AIPS_tag {
  union {                              /* Master Privilege Register A */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t MTR0:1;                /* Master 0 Trusted For Read */
      vuint32_t MTW0:1;                /* Master 0 Trusted For Writes */
      vuint32_t MPL0:1;                /* Master 0 Privilege Level */
      vuint32_t  :4;
      vuint32_t  :1;
      vuint32_t MTR2:1;                /* Master 2 Trusted For Read */
      vuint32_t MTW2:1;                /* Master 2 Trusted For Writes */
      vuint32_t MPL2:1;                /* Master 2 Privilege Level */
      vuint32_t  :1;
      vuint32_t MTR3:1;                /* Master 3 Trusted For Read */
      vuint32_t MTW3:1;                /* Master 3 Trusted For Writes */
      vuint32_t MPL3:1;                /* Master 3 Privilege Level */
      vuint32_t  :1;
      vuint32_t MTR4:1;                /* Master 4 Trusted For Read */
      vuint32_t MTW4:1;                /* Master 4 Trusted For Writes */
      vuint32_t MPL4:1;                /* Master 4 Privilege Level */
      vuint32_t  :1;
      vuint32_t MTR5:1;                /* Master 5 Trusted For Read */
      vuint32_t MTW5:1;                /* Master 5 Trusted For Writes */
      vuint32_t MPL5:1;                /* Master 5 Privilege Level */
      vuint32_t  :4;
      vuint32_t  :4;
    } B;
  } MPRA;

  uint8_t AIPS_reserved0[252];
  union {                              /* Peripheral Access Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t SP0:1;                 /* Supervisor Protect */
      vuint32_t WP0:1;                 /* Write Protect */
      vuint32_t TP0:1;                 /* Trusted Protect */
      vuint32_t  :1;
      vuint32_t SP1:1;                 /* Supervisor Protect */
      vuint32_t WP1:1;                 /* Write Protect */
      vuint32_t TP1:1;                 /* Trusted Protect */
      vuint32_t  :1;
      vuint32_t SP2:1;                 /* Supervisor Protect */
      vuint32_t WP2:1;                 /* Write Protect */
      vuint32_t TP2:1;                 /* Trusted Protect */
      vuint32_t  :1;
      vuint32_t SP3:1;                 /* Supervisor Protect */
      vuint32_t WP3:1;                 /* Write Protect */
      vuint32_t TP3:1;                 /* Trusted Protect */
      vuint32_t  :1;
      vuint32_t SP4:1;                 /* Supervisor Protect */
      vuint32_t WP4:1;                 /* Write Protect */
      vuint32_t TP4:1;                 /* Trusted Protect */
      vuint32_t  :1;
      vuint32_t SP5:1;                 /* Supervisor Protect */
      vuint32_t WP5:1;                 /* Write Protect */
      vuint32_t TP5:1;                 /* Trusted Protect */
      vuint32_t  :1;
      vuint32_t SP6:1;                 /* Supervisor Protect */
      vuint32_t WP6:1;                 /* Write Protect */
      vuint32_t TP6:1;                 /* Trusted Protect */
      vuint32_t  :1;
      vuint32_t SP7:1;                 /* Supervisor Protect */
      vuint32_t WP7:1;                 /* Write Protect */
      vuint32_t TP7:1;                 /* Trusted Protect */
    } B;
  } PACR[8];

  uint8_t AIPS_reserved1[32];
  union {                              /* Off-Platform Peripheral Access Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t SP0:1;                 /* Supervisor Protect */
      vuint32_t WP0:1;                 /* Write Protect */
      vuint32_t TP0:1;                 /* Trusted Protect */
      vuint32_t  :1;
      vuint32_t SP1:1;                 /* Supervisor Protect */
      vuint32_t WP1:1;                 /* Write Protect */
      vuint32_t TP1:1;                 /* Trusted Protect */
      vuint32_t  :1;
      vuint32_t SP2:1;                 /* Supervisor Protect */
      vuint32_t WP2:1;                 /* Write Protect */
      vuint32_t TP2:1;                 /* Trusted Protect */
      vuint32_t  :1;
      vuint32_t SP3:1;                 /* Supervisor Protect */
      vuint32_t WP3:1;                 /* Write Protect */
      vuint32_t TP3:1;                 /* Trusted Protect */
      vuint32_t  :1;
      vuint32_t SP4:1;                 /* Supervisor Protect */
      vuint32_t WP4:1;                 /* Write Protect */
      vuint32_t TP4:1;                 /* Trusted Protect */
      vuint32_t  :1;
      vuint32_t SP5:1;                 /* Supervisor Protect */
      vuint32_t WP5:1;                 /* Write Protect */
      vuint32_t TP5:1;                 /* Trusted Protect */
      vuint32_t  :1;
      vuint32_t SP6:1;                 /* Supervisor Protect */
      vuint32_t WP6:1;                 /* Write Protect */
      vuint32_t TP6:1;                 /* Trusted Protect */
      vuint32_t  :1;
      vuint32_t SP7:1;                 /* Supervisor Protect */
      vuint32_t WP7:1;                 /* Write Protect */
      vuint32_t TP7:1;                 /* Trusted Protect */
    } B;
  } OPACR[32];
};


/* ============================================================================
   =============================== Module: C55FMC =============================
   ============================================================================ */

struct C55FMC_tag {
  union {                              /* Module Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t RVE:1;                 /* Read Voltage Error */
      vuint32_t RRE:1;                 /* Read Reference Error */
      vuint32_t AEE:1;                 /* Address Encode Error */
      vuint32_t EEE:1;                 /* ECC after ECC Error */
      vuint32_t  :12;
      vuint32_t EER:1;                 /* ECC Event Error */
      vuint32_t RWE:1;                 /* Read-While-Write Event Error */
      vuint32_t SBC:1;                 /* Single Bit Correction */
      vuint32_t  :1;
      vuint32_t PEAS:1;                /* Program Access Space */
      vuint32_t DONE:1;                /* State Machine Status */
      vuint32_t PEG:1;                 /* Program/Erase Good */
      vuint32_t PECIE:1;               /* Program/Erase Complete Interrupt Enable */
      vuint32_t  :1;
      vuint32_t  :2;
      vuint32_t PGM:1;                 /* Program */
      vuint32_t PSUS:1;                /* Program Suspend */
      vuint32_t ERS:1;                 /* Erase */
      vuint32_t ESUS:1;                /* Erase Suspend */
      vuint32_t EHV:1;                 /* Enable High Voltage */
    } B;
  } MCR;

  uint8_t C55FMC_reserved0[4];
  union {                              /* Extended Module Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t HT:1;                  /* High Temperature Enabled. */
      vuint32_t  :2;
      vuint32_t n256K:5;
      vuint32_t n64Kh:3;
      vuint32_t n32Kh:2;
      vuint32_t n16Kh:3;
      vuint32_t n64Km:3;
      vuint32_t n32Km:2;
      vuint32_t n16Km:3;
      vuint32_t n64Kl:3;
      vuint32_t n32Kl:2;
      vuint32_t n16Kl:3;
    } B;
  } MCRE;

  uint8_t C55FMC_reserved1[4];
  union {                              /* Lock 0 register */
    vuint32_t R;
    struct {
      vuint32_t TSLOCK:1;              /* UTest NVM Lock. */
      vuint32_t  :1;
      vuint32_t LOWLOCK:14;            /* Low Block Lock */
      vuint32_t MIDLOCK:16;            /* Mid Block Lock */
    } B;
  } LOCK0;

  union {                              /* Lock 1 register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t HIGHLOCK:16;           /* High Block Lock */
    } B;
  } LOCK1;

  union {                              /* Lock 2 register */
    vuint32_t R;
    struct {
      vuint32_t A256KLOCK:32;          /* 256 KB Block Lock */
    } B;
  } LOCK2;

  union {                              /* Lock 3 register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t A256KLOCK:16;          /* 256 KB Block Lock */
    } B;
  } LOCK3;

  uint8_t C55FMC_reserved2[24];
  union {                              /* Select 0 register */
    vuint32_t R;
    struct {
      vuint32_t  :2;
      vuint32_t LOWSEL:14;             /* LOW Block Select. */
      vuint32_t MIDSEL:16;             /* Mid Block Select. */
    } B;
  } SEL0;

  union {                              /* Select 1 register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t HIGHSEL:16;            /* High Block Select. */
    } B;
  } SEL1;

  union {                              /* Select 2 register */
    vuint32_t R;
    struct {
      vuint32_t A256KSEL:32;           /* 256 KB Block Select. */
    } B;
  } SEL2;

  union {                              /* Select 3 register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t A256KSEL:16;           /* 256 KB Block Select. */
    } B;
  } SEL3;

  uint8_t C55FMC_reserved3[8];
  union {                              /* Address register */
    vuint32_t R;
    struct {
      vuint32_t SAD:1;
      vuint32_t aH:1;
      vuint32_t aM:1;
      vuint32_t aL:1;
      vuint32_t a256k:1;
      vuint32_t a64k:1;
      vuint32_t a32k:1;
      vuint32_t a16k:1;
      vuint32_t ADDR:21;
      vuint32_t  :3;
    } B;
  } ADR;

  union {                              /* UTest 0 register */
    vuint32_t R;
    struct {
      vuint32_t UTE:1;
      vuint32_t SBCE:1;
      vuint32_t  :11;
      vuint32_t CPR:1;
      vuint32_t CPA:1;
      vuint32_t CPE:1;
      vuint32_t  :6;
      vuint32_t NAIBP:1;
      vuint32_t AIBPE:1;
      vuint32_t  :1;
      vuint32_t AISUS:1;
      vuint32_t MRE:1;
      vuint32_t MRV:1;
      vuint32_t  :1;
      vuint32_t AIS:1;
      vuint32_t AIE:1;
      vuint32_t AID:1;
    } B;
  } UT0;

  union {                              /* UMISR register */
    vuint32_t R;
    struct {
      vuint32_t MISR:32;
    } B;
  } UM[9];

  union {                              /* UMISR register */
    vuint32_t R;
    struct {
      vuint32_t  :31;
      vuint32_t MISR:1;                /* MISR[288]. */
    } B;
  } UM9;

  union {                              /* Over-Program Protection 0 register */
    vuint32_t R;
    struct {
      vuint32_t  :2;
      vuint32_t LOWOPP:14;             /* Low Block Over-Program Protection[13:0]. */
      vuint32_t MIDOPP:16;             /* Mid Block Over-Program Protection[15:0]. */
    } B;
  } OPP0;

  union {                              /* Over-Program Protection 1 register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t HIGHOPP:16;            /* High Block Over-Program Protection[15:0]. */
    } B;
  } OPP1;

  union {                              /* Over-Program Protection 2 register */
    vuint32_t R;
    struct {
      vuint32_t A256KOPP:32;           /* 256K Block Over-Program Protection[31:0]. */
    } B;
  } OPP2;

  union {                              /* Over-Program Protection 3 register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t A256KOPP:16;           /* 256K Block Over-Program Protection[47:32]. */
    } B;
  } OPP3;
};


/* ============================================================================
   =============================== Module: CAN ================================
   ============================================================================ */
struct FLEXCAN_BUF_t {
     union {
         vuint32_t R;
         struct {
               vuint32_t:4;
             vuint32_t CODE:4;
               vuint32_t:1;
             vuint32_t SRR:1;
             vuint32_t IDE:1;
             vuint32_t RTR:1;
             vuint32_t LENGTH:4;
             vuint32_t TIMESTAMP:16;
         } B;
     } CS;                          /* Control and Status */

     union {
         vuint32_t R;
         struct {
             vuint32_t PRIO:3;
             vuint32_t STD_ID:11;
             vuint32_t EXT_ID:18;
         } B;
     } ID;                          /* Identifier Field */

     union {
         vuint8_t  B[8];  /* Data buffer in Bytes (8 bits) */
         /*vuint16_t H[4]; *//* Data buffer in Half-words (16 bits) */
         vuint32_t W[2]; /* Data buffer in words (32 bits) */
         /*vuint32_t R[2]; *//* Data buffer in words (32 bits) */
     } DATA;                        /* Data field */

 };                                 /* end of FLEXCAN_BUF_t */

 struct FLEXCAN_RXFIFO_t {
     union {
         vuint32_t R;
         struct {
               vuint32_t:9;
             vuint32_t SRR:1;
             vuint32_t IDE:1;
             vuint32_t RTR:1;
             vuint32_t LENGTH:4;
             vuint32_t TIMESTAMP:16;
         } B;
     } CS;                          /* Control and Status */

     union {
         vuint32_t R;
         struct {
             vuint32_t STD_ID:11;
             vuint32_t EXT_ID:18;
         } B;
     } ID;                          /* Identifier Field */

     union {
         /*vuint8_t  B[8]; *//* Data buffer in Bytes (8 bits) */
         /*vuint16_t H[4]; *//* Data buffer in Half-words (16 bits) */
         vuint32_t W[2]; /* Data buffer in words (32 bits) */
         /*vuint32_t R[2]; *//* Data buffer in words (32 bits) */
     } DATA;                        /* Data field */

     uint32_t FLEXCAN_RXFIFO_reserved[20];        /* {0x00E0-0x0090}/0x4 = 0x14 */

     union {
         vuint32_t R;
     } IDTABLE[8];                  /* Identifier table */

 };                                 /* end of FLEXCAN_RXFIFO_t */
struct FLEXCAN_tag {
  union {                              /* Module Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t MDIS:1;                /* Module Disable */
      vuint32_t FRZ:1;                 /* Freeze Enable */
      vuint32_t FEN:1;                /* Rx FIFO Enable */
      vuint32_t HALT:1;                /* Halt FlexCAN */
      vuint32_t NOTRDY:1;              /* FlexCAN Not Ready */
      vuint32_t  :1;
      vuint32_t SOFTRST:1;             /* Soft Reset */
      vuint32_t FRZACK:1;              /* Freeze Mode Acknowledge */
      vuint32_t SUPV:1;                /* Supervisor Mode */
      vuint32_t  :1;
      vuint32_t WRNEN:1;               /* Warning Interrupt Enable */
      vuint32_t LPMACK:1;              /* Low-Power Mode Acknowledge */
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t SRXDIS:1;              /* Self Reception Disable */
      vuint32_t BCC:1;                /* Individual Rx Masking And Queue Enable */
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t LPRIOEN:1;             /* Local Priority Enable */
      vuint32_t AEN:1;                 /* Abort Enable */
      vuint32_t  :2;
      vuint32_t IDAM:2;                /* ID Acceptance Mode */
      vuint32_t  :1;
      vuint32_t MAXMB:7;               /* Number Of The Last Message Buffer */
    } B;
  } MCR;

  union {                              /* Control 1 register */
    vuint32_t R;
    struct {
      vuint32_t PRESDIV:8;             /* Prescaler Division Factor */
      vuint32_t RJW:2;                 /* Resync Jump Width */
      vuint32_t PSEG1:3;               /* Phase Segment 1 */
      vuint32_t PSEG2:3;               /* Phase Segment 2 */
      vuint32_t BOFFMSK:1;             /* Bus Off Mask */
      vuint32_t ERRMSK:1;              /* Error Mask */
      vuint32_t CLKSRC:1;              /* CAN Engine Clock Source */
      vuint32_t LPB:1;                 /* Loop Back Mode */
      vuint32_t TWRNMSK:1;             /* Tx Warning Interrupt Mask */
      vuint32_t RWRNMSK:1;             /* Rx Warning Interrupt Mask */
      vuint32_t  :2;
      vuint32_t SMP:1;                 /* CAN Bit Sampling */
      vuint32_t BOFFREC:1;             /* Bus Off Recovery */
      vuint32_t TSYN:1;                /* Timer Sync */
      vuint32_t LBUF:1;                /* Lowest Buffer Transmitted First */
      vuint32_t LOM:1;                 /* Listen-Only Mode */
      vuint32_t PROPSEG:3;             /* Propagation Segment */
    } B;
  } CR;

  union {                              /* Free Running Timer */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t TIMER:16;              /* Timer Value */
    } B;
  } TIMER;

  uint8_t CAN_reserved0[4];
  union {                              /* Rx Mailboxes Global Mask Register */
    vuint32_t R;
    struct {
      vuint32_t MG:32;                 /* Rx Mailboxes Global Mask Bits */
    } B;
  } RXGMASK;

  union {                              /* Rx 14 Mask register */
    vuint32_t R;
    struct {
      vuint32_t RX14M:32;              /* Rx Buffer 14 Mask Bits */
    } B;
  } RX14MASK;

  union {                              /* Rx 15 Mask register */
    vuint32_t R;
    struct {
      vuint32_t RX15M:32;              /* Rx Buffer 15 Mask Bits */
    } B;
  } RX15MASK;

  union {                              /* Error Counter */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t RXERRCNT:8;            /* Receive Error Counter */
      vuint32_t TXERRCNT:8;            /* Transmit Error Counter */
    } B;
  } ECR;

  union {                              /* Error and Status 1 register */
    vuint32_t R;
    struct {
      vuint32_t  :13;
      vuint32_t SYNCH:1;               /* CAN Synchronization Status */
      vuint32_t TWRNINT:1;             /* Tx Warning Interrupt Flag */
      vuint32_t RWRNINT:1;             /* Rx Warning Interrupt Flag */
      vuint32_t BIT1ERR:1;             /* Bit1 Error */
      vuint32_t BIT0ERR:1;             /* Bit0 Error */
      vuint32_t ACKERR:1;              /* Acknowledge Error */
      vuint32_t CRCERR:1;              /* Cyclic Redundancy Check Error */
      vuint32_t FRMERR:1;              /* Form Error */
      vuint32_t STFERR:1;              /* Stuffing Error */
      vuint32_t TXWRN:1;               /* TX Error Warning */
      vuint32_t RXWRN:1;               /* Rx Error Warning */
      vuint32_t IDLE:1;
      vuint32_t TX:1;                  /* FlexCAN In Transmission */
      vuint32_t FLTCONF:2;             /* Fault Confinement State */
      vuint32_t RX:1;                  /* FlexCAN In Reception */
      vuint32_t BOFFINT:1;             /* Bus Off Interrupt */
      vuint32_t ERRINT:1;              /* Error Interrupt */
      vuint32_t  :1;
    } B;
  } ESR;

  union {                              /* Interrupt Masks 2 register */
    vuint32_t R;
    struct {
      vuint32_t BUFHM:32;              /* Buffer MB i Mask */
    } B;
  } IMRH;

  union {                              /* Interrupt Masks 1 register */
    vuint32_t R;
    struct {
      vuint32_t BUFLM:32;              /* Buffer MB i Mask */
    } B;
  } IMRL;

  union {                              /* Interrupt Flags 2 register */
    vuint32_t R;
    struct {
      vuint32_t BUFHI:32;              /* Buffer MB i Interrupt */
    } B;
  } IFRH;

  union {                              /* Interrupt Flags 1 register */
    vuint32_t R;
    struct {
      vuint32_t BUF31TO8I:24;          /* Buffer MBi Interrupt */
      vuint32_t BUF07I:1;               /* Buffer MB7 Interrupt Or "Rx FIFO Overflow" */
      vuint32_t BUF06I:1;               /* Buffer MB6 Interrupt Or "Rx FIFO Warning" */
      vuint32_t BUF05I:1;               /* Buffer MB5 Interrupt Or "Frames available in Rx FIFO" */
      vuint32_t BUF4TO1I:4;            /* Buffer MB i Interrupt Or "reserved" */
      vuint32_t BUF0I:1;               /* Buffer MB0 Interrupt Or "reserved" */
    } B;
  } IFRL;

  union {                              /* Control 2 register */
    vuint32_t R;
    struct {
      vuint32_t  :2;
      vuint32_t ECRWRE:1;              /* Error-correction Configuration Register Write Enable */
      vuint32_t WRMFRZ:1;              /* Write-Access To Memory In Freeze Mode */
      vuint32_t RFFN:4;                /* Number Of Rx FIFO Filters */
      vuint32_t TASD:5;                /* Tx Arbitration Start Delay */
      vuint32_t MRP:1;                 /* Mailboxes Reception Priority */
      vuint32_t RRS:1;                 /* Remote Request Storing */
      vuint32_t EACEN:1;               /* Entire Frame Arbitration Field Comparison Enable For Rx Mailboxes */
      vuint32_t  :16;
    } B;
  } CTRL2;

  union {                              /* Error and Status 2 register */
    vuint32_t R;
    struct {
      vuint32_t  :9;
      vuint32_t LPTM:7;                /* Lowest Priority Tx Mailbox */
      vuint32_t  :1;
      vuint32_t VPS:1;                 /* Valid Priority Status */
      vuint32_t IMB:1;                 /* Inactive Mailbox */
      vuint32_t  :13;
    } B;
  } ESR2;

  uint8_t CAN_reserved1[8];
  union {                              /* CRC Register */
    vuint32_t R;
    struct {
      vuint32_t  :9;
      vuint32_t MBCRC:7;               /* CRC Mailbox */
      vuint32_t  :1;
      vuint32_t TXCRC:15;              /* CRC Transmitted */
    } B;
  } CRCR;

  union {                              /* Rx FIFO Global Mask register */
    vuint32_t R;
    struct {
      vuint32_t FGM:32;                /* Rx FIFO Global Mask Bits */
    } B;
  } RXFGMASK;

  union {                              /* Rx FIFO Information Register */
    vuint32_t R;
    struct {
      vuint32_t  :23;
      vuint32_t IDHIT:9;               /* Identifier Acceptance Filter Hit Indicator */
    } B;
  } RXFIR;

  uint8_t CAN_reserved2[48];
  struct canbuf_t {
    union {                            /* Message Buffer 0 CS Register */
      vuint32_t R;
      struct {
        vuint32_t  :4;
        vuint32_t CODE:4;              /* Message Buffer Code */
        vuint32_t  :1;
        vuint32_t SRR:1;               /* Substitute Remote Request. Contains a fixed recessive bit. */
        vuint32_t IDE:1;               /* ID Extended. One/zero for extended/standard format frame. */
        vuint32_t RTR:1;               /* Remote Transmission Request. One/zero for remote/data frame. */
        vuint32_t LENGTH:4;               /* Length of the data to be stored/transmitted. */
        vuint32_t TIMESTAMP:16;        /* Free-Running Counter Time stamp. This 16-bit field is a copy of the Free-Running Timer, captured for Tx and Rx frames at the time when the beginning of the Identifier field appears on the CAN bus. */
      } B;
    } CS;
    union {                            /* Message Buffer 0 ID Register */
      vuint32_t R;
      struct {
        vuint32_t PRIO:3;              /* Local Priority */
        vuint32_t STD_ID:11;              /* Frame Identifier Standard */
        vuint32_t EXT_ID:18;              /* Frame Identifier Extended */
      } B;
    } ID;
    union {
      vuint8_t B[8];
      vuint16_t H[4];
      vuint32_t W[2];
    } DATA;
  } BUF[64];

  uint8_t CAN_reserved3[1024];
  union {                              /* Rx Individual Mask Registers */
    vuint32_t R;
    struct {
      vuint32_t MI:32;                 /* Individual Mask Bits */
    } B;
  } RXIMR[64];

  uint8_t CAN_reserved4[352];
  union {                              /* Memory Error Control Register */
    vuint32_t R;
    struct {
      vuint32_t ECRWRDIS:1;            /* Error Configuration Register Write Disable */
      vuint32_t  :14;
      vuint32_t CEI_MSK:1;             /* Correctable Errors Interrupt Mask */
      vuint32_t HAERRIE:1;             /* Host Access Error Injection Enable */
      vuint32_t FAERRIE:1;             /* FlexCAN Access Error Injection Enable */
      vuint32_t EXTERRIE:1;            /* Extended Error Injection Enable */
      vuint32_t  :3;
      vuint32_t RERRDIS:1;             /* Error Report Disable */
      vuint32_t ECCDIS:1;              /* Error Correction Disable */
      vuint32_t NCEFAFRZ:1;            /* Non-Correctable Errors In FlexCAN Access Put Device In Freeze Mode */
      vuint32_t  :7;
    } B;
  } MECR;

  union {                              /* Error Injection Address Register */
    vuint32_t R;
    struct {
      vuint32_t  :18;
      vuint32_t INJADDR:14;            /* Address Where Error Is To Be Injected */
    } B;
  } ERRIAR;

  union {                              /* Error Injection Data Pattern Register */
    vuint32_t R;
    struct {
      vuint32_t DFLIP:32;              /* Data flip pattern */
    } B;
  } ERRIDPR;

  union {                              /* Error Injection Parity Pattern Register */
    vuint32_t R;
    struct {
      vuint32_t  :3;
      vuint32_t PFLIP3:5;              /* Parity Flip Pattern For Byte 3 (most significant) */
      vuint32_t  :3;
      vuint32_t PFLIP2:5;              /* Parity Flip Pattern For Byte 2 */
      vuint32_t  :3;
      vuint32_t PFLIP1:5;              /* Parity Flip Pattern For Byte 1 */
      vuint32_t  :3;
      vuint32_t PFLIP0:5;              /* Parity Flip Pattern For Byte 0 (Least Significant) */
    } B;
  } ERRIPPR;

  union {                              /* Error Report Address Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t NCE:1;                 /* Non-Correctable Error */
      vuint32_t  :5;
      vuint32_t SAID:3;
      vuint32_t  :2;
      vuint32_t ERRADDR:14;            /* Address Where The Error Was Detected */
    } B;
  } RERRAR;

  union {                              /* Error Report Data Register */
    vuint32_t R;
    struct {
      vuint32_t RDATA:32;              /* Raw data word read from memory with error */
    } B;
  } RERRDR;

  union {                              /* Error Report Syndrome Register */
    vuint32_t R;
    struct {
      vuint32_t BE3:1;                 /* Byte Enabled For Byte 3 (Most Significant) */
      vuint32_t  :2;
      vuint32_t SYND3:5;               /* Error Syndrome For Byte 3 (Most Significant) */
      vuint32_t BE2:1;                 /* Byte Enabled For Byte 2 */
      vuint32_t  :2;
      vuint32_t SYND2:5;               /* Error Syndrome For Byte 2 */
      vuint32_t BE1:1;                 /* Byte Enabled For Byte 1 */
      vuint32_t  :2;
      vuint32_t SYND1:5;               /* Error Syndrome for Byte 1 */
      vuint32_t BE0:1;                 /* Byte Enabled For Byte 0 (least significant) */
      vuint32_t  :2;
      vuint32_t SYND0:5;               /* Error Syndrome For Byte 0 (least significant) */
    } B;
  } RERRSYNR;

  union {                              /* Error Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t HANCEIF:1;             /* Host Access With Non-Correctable Error Interrupt Flag */
      vuint32_t FANCEIF:1;             /* FlexCAN Access With Non-Correctable Error Interrupt Flag */
      vuint32_t  :1;
      vuint32_t CEIF:1;                /* Correctable Error Interrupt Flag */
      vuint32_t  :12;
      vuint32_t HANCEIOF:1;            /* Host Access With Non-Correctable Error Interrupt Overrun Flag */
      vuint32_t FANCEIOF:1;            /* FlexCAN Access With Non-Correctable Error Interrupt Overrun Flag */
      vuint32_t  :1;
      vuint32_t CEIOF:1;               /* Correctable Error Interrupt Overrun Flag */
    } B;
  } ERRSR;
};

/* ============================================================================
   =============================== Module: CMU ================================
   ============================================================================ */

struct CMU_tag {
  union {                              /* CMU Control Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :8;
      vuint32_t SFM:1;                 /* Start frequency measure. */
      vuint32_t  :13;
      vuint32_t CKSEL1:2;              /* Frequency measure clock selection bit. */
      vuint32_t  :5;
      vuint32_t RCDIV:2;               /* CLKMT0_RMN division factor. */
      vuint32_t CME:1;                 /* CLKMN1 monitor enable. */
    } B;
  } CSR;

  union {                              /* CMU Frequency Display Register */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t FD:20;                 /* Measured frequency bits. */
    } B;
  } FDR;

  union {                              /* CMU High Frequency Reference Register CLKMN1 */
    vuint32_t R;
    struct {
      vuint32_t  :20;
      vuint32_t HFREF:12;              /* High Frequency reference value. */
    } B;
  } HFREFR;

  union {                              /* CMU Low Frequency Reference Register CLKMN1 */
    vuint32_t R;
    struct {
      vuint32_t  :20;
      vuint32_t LFREF:12;              /* Low Frequency reference value. */
    } B;
  } LFREFR;

  union {                              /* CMU Interrupt Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :28;
      vuint32_t  :1;
      vuint32_t FHHI:1;                /* CLKMN1 frequency higher than high reference event status. */
      vuint32_t FLLI:1;                /* CLKMN1 frequency less than low reference event status. */
      vuint32_t OLRI:1;                /* Oscillator frequency less than f CLKMT0_RMN * 2RCDIVevent status. */
    } B;
  } ISR;

  uint8_t CMU_reserved0[4];
  union {                              /* CMU Measurement Duration Register */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t MD:20;                 /* Measurement duration bits */
    } B;
  } MDR;
};


/* ============================================================================
   =============================== Module: CRC ================================
   ============================================================================ */

struct CRC_tag {
  struct {
    union {                            /* Configuration Register */
      vuint32_t R;
      struct {
        vuint32_t  :8;
        vuint32_t  :18;
        vuint32_t  :2;
        vuint32_t POLYG:2;             /* Polynomial selection */
        vuint32_t SWAP:1;              /* Swap selection */
        vuint32_t INV:1;               /* Inversion selection */
      } B;
    } CFG;
    union {                            /* Input Register */
      vuint32_t R;
      struct {
        vuint32_t INP:32;              /* Input data for the CRC computation */
      } B;
    } INP;
    union {                            /* Current Status Register */
      vuint32_t R;
      struct {
        vuint32_t CSTAT:32;            /* CRC signature status */
      } B;
    } CSTAT;
    union {                            /* Output Register */
      vuint32_t R;
      struct {
        vuint32_t OUTP:32;             /* Final CRC signature */
      } B;
    } OUTP;
  } CHANNEL[3];
};


/* ============================================================================
   =============================== Module: CTU ================================
   ============================================================================ */

struct CTU_tag {
  union {                              /* Trigger Generator Subunit Input Selection Register */
    vuint32_t R;
    struct {
      vuint32_t I15_FE:1;              /* Input 15 Falling Edge Enable. */
      vuint32_t I15_RE:1;              /* Input 15 Rising Edge Enable. */
      vuint32_t I14_FE:1;              /* Input 14 Falling Edge Enable. */
      vuint32_t I14_RE:1;              /* Input 14 Rising Edge Enable. */
      vuint32_t I13_FE:1;              /* Input 13 Falling Edge Enable. */
      vuint32_t I13_RE:1;              /* Input 13 Rising Edge Enable. */
      vuint32_t I12_FE:1;              /* Input 12 Falling Edge Enable. */
      vuint32_t I12_RE:1;              /* Input 12 Rising Edge Enable. */
      vuint32_t I11_FE:1;              /* Input 11 Falling Edge Enable. */
      vuint32_t I11_RE:1;              /* Input 11 Rising Edge Enable. */
      vuint32_t I10_FE:1;              /* Input 10 Falling Edge Enable. */
      vuint32_t I10_RE:1;              /* Input 10 Rising Edge Enable. */
      vuint32_t I9_FE:1;               /* Input 9 Falling Edge Enable. */
      vuint32_t I9_RE:1;               /* Input 9 Rising Edge Enable. */
      vuint32_t I8_FE:1;               /* Input 8 Falling Edge Enable. */
      vuint32_t I8_RE:1;               /* Input 8 Rising Edge Enable. */
      vuint32_t I7_FE:1;               /* Input 7 Falling Edge Enable. */
      vuint32_t I7_RE:1;               /* Input 7 Rising Edge Enable. */
      vuint32_t I6_FE:1;               /* Input 6 Falling Edge Enable. */
      vuint32_t I6_RE:1;               /* Input 6 Rising Edge Enable. */
      vuint32_t I5_FE:1;               /* Input 5 Falling Edge Enable. */
      vuint32_t I5_RE:1;               /* Input 5 Rising Edge Enable. */
      vuint32_t I4_FE:1;               /* Input 4 Falling Edge Enable. */
      vuint32_t I4_RE:1;               /* Input 4 Rising Edge Enable. */
      vuint32_t I3_FE:1;               /* Input 3 Falling Edge Enable. */
      vuint32_t I3_RE:1;               /* Input 3 Rising edge Enable */
      vuint32_t I2_FE:1;               /* Input 2 Falling Edge Enable. */
      vuint32_t I2_RE:1;               /* Input 2 Rising Edge Enable. */
      vuint32_t I1_FE:1;               /* Input 1 Falling Edge Enable. */
      vuint32_t I1_RE:1;               /* Input 1 Rising edge Enable */
      vuint32_t I0_FE:1;               /* Input 0 Falling Edge Enable. */
      vuint32_t I0_RE:1;               /* Input 0 Rising Edge Enable. */
    } B;
  } TGSISR;

  union {                              /* Trigger Generator Subunit Control Register */
    vuint16_t R;
    struct {
      vuint16_t  :7;
      vuint16_t ET_TM:1;
      vuint16_t PRES:2;
      vuint16_t MRS_SM:5;
      vuint16_t TGS_M:1;
    } B;
  } TGSCR;

  union {                              /* Trigger Compare Register */
    vuint16_t R;
    struct {
      vuint16_t TCRV:16;
    } B;
  } TCR[8];

  union {                              /* TGS Counter Compare Register */
    vuint16_t R;
    struct {
      vuint16_t TGSCCV:16;
    } B;
  } TGSCCR;

  union {                              /* TGS Counter Reload Register */
    vuint16_t R;
    struct {
      vuint16_t TGSCRV:16;
    } B;
  } TGSCRR;

  uint8_t CTU_reserved0[2];
  union {                              /* Commands List Control Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :3;
      vuint32_t T3_INDEX:5;
      vuint32_t  :3;
      vuint32_t T2_INDEX:5;
      vuint32_t  :3;
      vuint32_t T1_INDEX:5;
      vuint32_t  :3;
      vuint32_t T0_INDEX:5;
    } B;
  } CLCR1;

  union {                              /* Commands List Control Register 2 */
    vuint32_t R;
    struct {
      vuint32_t  :3;
      vuint32_t T7_INDEX:5;
      vuint32_t  :3;
      vuint32_t T6_INDEX:5;
      vuint32_t  :3;
      vuint32_t T5_INDEX:5;
      vuint32_t  :3;
      vuint32_t T4_INDEX:5;
    } B;
  } CLCR2;

  union {                              /* Trigger Handler Control Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t T3_E:1;
      vuint32_t T3_ETE:1;
      vuint32_t T3_T4E:1;
      vuint32_t T3_T3E:1;
      vuint32_t T3_T2E:1;
      vuint32_t T3_T1E:1;
      vuint32_t T3_ADCE:1;
      vuint32_t  :1;
      vuint32_t T2_E:1;
      vuint32_t T2_ETE:1;
      vuint32_t T2_T4E:1;
      vuint32_t T2_T3E:1;
      vuint32_t T2_T2E:1;
      vuint32_t T2_T1E:1;
      vuint32_t T2_ADCE:1;
      vuint32_t  :1;
      vuint32_t T1_E:1;
      vuint32_t T1_ETE:1;
      vuint32_t T1_T4E:1;
      vuint32_t T1_T3E:1;
      vuint32_t T1_T2E:1;
      vuint32_t T1_T1E:1;
      vuint32_t T1_ADCE:1;
      vuint32_t  :1;
      vuint32_t T0_E:1;
      vuint32_t T0_ETE:1;
      vuint32_t T0_T4E:1;
      vuint32_t T0_T3E:1;
      vuint32_t T0_T2E:1;
      vuint32_t T0_T1E:1;
      vuint32_t T0_ADCE:1;
    } B;
  } THCR1;

  union {                              /* Trigger Handler Control Register 2 */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t T7_E:1;
      vuint32_t T7_ETE:1;
      vuint32_t T7_T4E:1;
      vuint32_t T7_T3E:1;
      vuint32_t T7_T2E:1;
      vuint32_t T7_T1E:1;
      vuint32_t T7_ADCE:1;
      vuint32_t  :1;
      vuint32_t T6_E:1;
      vuint32_t T6_ETE:1;
      vuint32_t T6_T4E:1;
      vuint32_t T6_T3E:1;
      vuint32_t T6_T2E:1;
      vuint32_t T6_T1E:1;
      vuint32_t T6_ADCE:1;
      vuint32_t  :1;
      vuint32_t T5_E:1;
      vuint32_t T5_ETE:1;
      vuint32_t T5_T4E:1;
      vuint32_t T5_T3E:1;
      vuint32_t T5_T2E:1;
      vuint32_t T5_T1E:1;
      vuint32_t T5_ADCE:1;
      vuint32_t  :1;
      vuint32_t T4_E:1;
      vuint32_t T4_ETE:1;
      vuint32_t T4_T4E:1;
      vuint32_t T4_T3E:1;
      vuint32_t T4_T2E:1;
      vuint32_t T4_T1E:1;
      vuint32_t T4_ADCE:1;
    } B;
  } THCR2;

  union {
    union {                            /* Commands List Register A for ADC single-conversion mode commands */
      vuint16_t R;
      struct {
        vuint16_t CIR:1;
        vuint16_t LC:1;
        vuint16_t CMS:1;
        vuint16_t FIFO:3;              /* FIFO used for ADC Port A / Port B. */
        vuint16_t ST0:1;
        vuint16_t  :3;
        vuint16_t SU:1;                /* ADC Port A / Port B selection. */
        vuint16_t  :1;
        vuint16_t CH:4;                /* ADC Port channel number. */
      } B;
    } A;
    union {                            /* Command List Register B for ADC dual-conversion mode commands */
      vuint16_t R;
      struct {
        vuint16_t CIR:1;
        vuint16_t LC:1;
        vuint16_t CMS:1;
        vuint16_t FIFO:3;              /* FIFO used for ADC Port A / Port B. */
        vuint16_t ST0:1;               /* Sel-Test mode control 0. Must be 0 in this register format. */
        vuint16_t CH_B:4;              /* ADC Port B channel number. */
        vuint16_t  :1;                 /* Reserved. */
        vuint16_t CH_A:4;              /* ADC Port A channel number. */
      } B;
    } B;
    union {                            /* Command List Register C for self-test commands */
      vuint16_t R;
      struct {
        vuint16_t CIR:1;
        vuint16_t LC:1;
        vuint16_t ST1:1;
        vuint16_t ST_CMS:1;
        vuint16_t ST_SU:1;
        vuint16_t  :1;
        vuint16_t ST0:1;
        vuint16_t ALG:2;
        vuint16_t BSIZE:7;
      } B;
    } C;
  } CLR[24];

  uint8_t CTU_reserved1[16];
  union {                              /* FIFO DMA Control Register */
    vuint16_t R;
    struct {
      vuint16_t  :4;
      vuint16_t  :1;
      vuint16_t  :1;
      vuint16_t  :1;
      vuint16_t  :1;
      vuint16_t  :4;
      vuint16_t DE3:1;
      vuint16_t DE2:1;
      vuint16_t DE1:1;
      vuint16_t DE0:1;
    } B;
  } FDCR;

  uint8_t CTU_reserved2[2];
  union {                              /* FIFO Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t OR_EN3:1;
      vuint32_t OF_EN3:1;
      vuint32_t EMPTY_EN3:1;
      vuint32_t FULL_EN3:1;
      vuint32_t OR_EN2:1;
      vuint32_t OF_EN2:1;
      vuint32_t EMPTY_EN2:1;
      vuint32_t FULL_EN2:1;
      vuint32_t OR_EN1:1;
      vuint32_t OF_EN1:1;
      vuint32_t EMPTY_EN1:1;
      vuint32_t FULL_EN1:1;
      vuint32_t OR_EN0:1;
      vuint32_t OF_EN0:1;
      vuint32_t EMPTY_EN0:1;
      vuint32_t FULL_EN0:1;
    } B;
  } FCR;

  union {                              /* FIFO Threshold Register */
    vuint32_t R;
    struct {
      vuint32_t TH3:8;
      vuint32_t TH2:8;
      vuint32_t TH1:8;
      vuint32_t TH0:8;
    } B;
  } FTH;

  uint8_t CTU_reserved3[4];
  union {                              /* FIFO Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t OR3:1;
      vuint32_t OF3:1;
      vuint32_t EMP3:1;
      vuint32_t FULL3:1;
      vuint32_t OR2:1;
      vuint32_t OF2:1;
      vuint32_t EMP2:1;
      vuint32_t FULL2:1;
      vuint32_t OR1:1;
      vuint32_t OF1:1;
      vuint32_t EMP1:1;
      vuint32_t FULL1:1;
      vuint32_t OR0:1;
      vuint32_t OF0:1;
      vuint32_t EMP0:1;
      vuint32_t FULL0:1;
    } B;
  } FST;

  union {                              /* FIFO Right Aligned Data Register */
    vuint32_t R;
    struct {
      vuint32_t  :11;
      vuint32_t ADC:1;                 /* This bit indicates from which ADC Port the value in the DATA field corresponds to. */
      vuint32_t N_CH:4;
      vuint32_t  :4;
      vuint32_t DATA:12;
    } B;
  } FR[4];

  uint8_t CTU_reserved4[16];
  union {                              /* FIFO Signed Left Aligned Data Register */
    vuint32_t R;
    struct {
      vuint32_t  :11;
      vuint32_t ADC:1;                 /* This bit indicates from which ADC Port the value in the DATA field corresponds to. */
      vuint32_t N_CH:4;
      vuint32_t  :1;
      vuint32_t LA_DATA:12;
      vuint32_t  :3;
    } B;
  } FL[4];

  uint8_t CTU_reserved5[16];
  union {                              /* Error Flag Register */
    vuint16_t R;
    struct {
      vuint16_t  :2;
      vuint16_t LIST_BE:1;
      vuint16_t CS:1;
      vuint16_t ET_OE:1;
      vuint16_t ERRCMP:1;
      vuint16_t T4_OE:1;
      vuint16_t T3_OE:1;
      vuint16_t T2_OE:1;
      vuint16_t T1_OE:1;
      vuint16_t ADC_OE:1;
      vuint16_t TGS_OSM:1;
      vuint16_t MRS_O:1;
      vuint16_t ICE:1;
      vuint16_t SM_TO:1;
      vuint16_t MRS_RE:1;
    } B;
  } EFR;

  union {                              /* Interrupt Flag Register */
    vuint16_t R;
    struct {
      vuint16_t  :4;
      vuint16_t SERR_B:1;
      vuint16_t SERR_A:1;
      vuint16_t ADC_I:1;
      vuint16_t T7_I:1;
      vuint16_t T6_I:1;
      vuint16_t T5_I:1;
      vuint16_t T4_I:1;
      vuint16_t T3_I:1;
      vuint16_t T2_I:1;
      vuint16_t T1_I:1;
      vuint16_t T0_I:1;
      vuint16_t MRS_I:1;
    } B;
  } IFR;

  union {                              /* Interrupt/DMA Register */
    vuint16_t R;
    struct {
      vuint16_t T7_IE:1;
      vuint16_t T6_IE:1;
      vuint16_t T5_IE:1;
      vuint16_t T4_IE:1;
      vuint16_t T3_IE:1;
      vuint16_t T2_IE:1;
      vuint16_t T1_IE:1;
      vuint16_t T0_IE:1;
      vuint16_t  :2;
      vuint16_t SAF_CNT_B_EN:1;        /* Enable the ADC Port B counter to check the conversion time. */
      vuint16_t SAF_CNT_A_EN:1;        /* Enable the ADC Port A counter to check the conversion time. */
      vuint16_t DMA_DE:1;
      vuint16_t MRS_DMAE:1;
      vuint16_t MRS_IE:1;
      vuint16_t IEE:1;
    } B;
  } IR;

  union {                              /* Control ON Time Register */
    vuint16_t R;
    struct {
      vuint16_t  :8;
      vuint16_t COTGT:8;
    } B;
  } COTR;

  union {                              /* Control Register */
    vuint16_t R;
    struct {
      vuint16_t T7_SG:1;
      vuint16_t T6_SG:1;
      vuint16_t T5_SG:1;
      vuint16_t T4_SG:1;
      vuint16_t T3_SG:1;
      vuint16_t T2_SG:1;
      vuint16_t T1_SG:1;
      vuint16_t T0_SG:1;
      vuint16_t CTU_ADC_R:1;
      vuint16_t CTU_ODIS:1;
      vuint16_t DFE:1;
      vuint16_t CGRE:1;
      vuint16_t FGRE:1;
      vuint16_t MRS_SG:1;
      vuint16_t GRE:1;
      vuint16_t TGSISR_RE:1;
    } B;
  } CR;

  union {                              /* Digital Filter Register */
    vuint16_t R;
    struct {
      vuint16_t  :8;
      vuint16_t FILTER_N:8;
    } B;
  } DFR;

  union {                              /* Expected Value A Register */
    vuint16_t R;
    struct {
      vuint16_t EXPA:16;               /* This value is the maximum number of system clock cycles needed by ADC Port A in order to complete a conversion. */
    } B;
  } EXPAR;

  union {                              /* Expected Value B Register */
    vuint16_t R;
    struct {
      vuint16_t EXPB:16;               /* This value is the maximum number of system clock cycles needed by ADC Port B in order to complete a conversion. */
    } B;
  } EXPBR;

  union {                              /* Counter Range Register */
    vuint16_t R;
    struct {
      vuint16_t  :8;
      vuint16_t CNTRNG:8;
    } B;
  } CNTRNGR;

  uint8_t CTU_reserved6[2];
  union {                              /* List Control/Status Register */
    vuint32_t R;
    struct {
      vuint32_t LIST1_BLK:1;
      vuint32_t  :2;
      vuint32_t LIST1_ADDR:5;
      vuint32_t LIST0_BLK:1;
      vuint32_t  :2;
      vuint32_t LIST0_ADDR:5;          /* List Address 0, indicates the command address being executed when LIST_BE flag in EFR register bit was set. */
      vuint32_t  :15;
      vuint32_t PAR_LIST:1;
    } B;
  } LISTCSR;
};


/* ============================================================================
   =============================== Module: DCL ================================
   ============================================================================ */

struct DCL_tag {
  union {                              /* Different Clock register */
    vuint32_t R;
    struct {
      vuint32_t DCL_IPS:32;
    } B;
  } IPS0;
};


/* ============================================================================
   =============================== Module: DMAMUX =============================
   ============================================================================ */

struct DMAMUX_tag {
  union {                              /* Channel Configuration register */
    vuint8_t R;
    struct {
      vuint8_t ENBL:1;                 /* DMA Channel Enable */
      vuint8_t TRIG:1;                 /* DMA Channel Trigger Enable */
      vuint8_t SOURCE:6;               /* DMA Channel Source (Slot) */
    } B;
  } CHCFG[16];
};


/* ============================================================================
   =============================== Module: DMA ================================
   ============================================================================ */

struct DMA_tag {
  union {                              /* Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :14;
      vuint32_t CX:1;                  /* Cancel Transfer */
      vuint32_t ECX:1;                 /* Error Cancel Transfer */
      vuint32_t  :4;
      vuint32_t  :1;
      vuint32_t GRP1PRI:1;             /* Channel Group 1 Priority */
      vuint32_t  :1;
      vuint32_t GRP0PRI:1;             /* Channel Group 0 Priority */
      vuint32_t EMLM:1;                /* Enable Minor Loop Mapping */
      vuint32_t CLM:1;                 /* Continuous Link Mode */
      vuint32_t HALT:1;                /* Halt DMA Operations */
      vuint32_t HOE:1;                 /* Halt On Error */
      vuint32_t ERGA:1;                /* Enable Round Robin Group Arbitration */
      vuint32_t ERCA:1;                /* Enable Round Robin Channel Arbitration */
      vuint32_t EDBG:1;                /* Enable Debug */
      vuint32_t  :1;
    } B;
  } CR;

  union {                              /* Error Status Register */
    vuint32_t R;
    struct {
      vuint32_t VLD:1;
      vuint32_t  :13;
      vuint32_t UCE:1;                 /* Uncorrectable ECC error during channel execution. */
      vuint32_t ECX:1;                 /* Transfer Canceled */
      vuint32_t GPE:1;                 /* Group Priority Error */
      vuint32_t CPE:1;                 /* Channel Priority Error */
      vuint32_t  :1;
      vuint32_t ERRCHN:5;              /* Error Channel Number or Canceled Channel Number */
      vuint32_t SAE:1;                 /* Source Address Error */
      vuint32_t SOE:1;                 /* Source Offset Error */
      vuint32_t DAE:1;                 /* Destination Address Error */
      vuint32_t DOE:1;                 /* Destination Offset Error */
      vuint32_t NCE:1;                 /* NBYTES/CITER Configuration Error */
      vuint32_t SGE:1;                 /* Scatter/Gather Configuration Error */
      vuint32_t SBE:1;                 /* Source Bus Error */
      vuint32_t DBE:1;                 /* Destination Bus Error */
    } B;
  } ES;

  uint8_t DMA_reserved0[4];
  union {                              /* Enable Request Register */
    vuint32_t R;
    struct {
      vuint32_t ERQ31:1;               /* Enable DMA Request 31 */
      vuint32_t ERQ30:1;               /* Enable DMA Request 30 */
      vuint32_t ERQ29:1;               /* Enable DMA Request 29 */
      vuint32_t ERQ28:1;               /* Enable DMA Request 28 */
      vuint32_t ERQ27:1;               /* Enable DMA Request 27 */
      vuint32_t ERQ26:1;               /* Enable DMA Request 26 */
      vuint32_t ERQ25:1;               /* Enable DMA Request 25 */
      vuint32_t ERQ24:1;               /* Enable DMA Request 24 */
      vuint32_t ERQ23:1;               /* Enable DMA Request 23 */
      vuint32_t ERQ22:1;               /* Enable DMA Request 22 */
      vuint32_t ERQ21:1;               /* Enable DMA Request 21 */
      vuint32_t ERQ20:1;               /* Enable DMA Request 20 */
      vuint32_t ERQ19:1;               /* Enable DMA Request 19 */
      vuint32_t ERQ18:1;               /* Enable DMA Request 18 */
      vuint32_t ERQ17:1;               /* Enable DMA Request 17 */
      vuint32_t ERQ16:1;               /* Enable DMA Request 16 */
      vuint32_t ERQ15:1;               /* Enable DMA Request 15 */
      vuint32_t ERQ14:1;               /* Enable DMA Request 14 */
      vuint32_t ERQ13:1;               /* Enable DMA Request 13 */
      vuint32_t ERQ12:1;               /* Enable DMA Request 12 */
      vuint32_t ERQ11:1;               /* Enable DMA Request 11 */
      vuint32_t ERQ10:1;               /* Enable DMA Request 10 */
      vuint32_t ERQ9:1;                /* Enable DMA Request 9 */
      vuint32_t ERQ8:1;                /* Enable DMA Request 8 */
      vuint32_t ERQ7:1;                /* Enable DMA Request 7 */
      vuint32_t ERQ6:1;                /* Enable DMA Request 6 */
      vuint32_t ERQ5:1;                /* Enable DMA Request 5 */
      vuint32_t ERQ4:1;                /* Enable DMA Request 4 */
      vuint32_t ERQ3:1;                /* Enable DMA Request 3 */
      vuint32_t ERQ2:1;                /* Enable DMA Request 2 */
      vuint32_t ERQ1:1;                /* Enable DMA Request 1 */
      vuint32_t ERQ0:1;                /* Enable DMA Request 0 */
    } B;
  } ERQ;

  uint8_t DMA_reserved1[4];
  union {                              /* Enable Error Interrupt Register */
    vuint32_t R;
    struct {
      vuint32_t EEI31:1;               /* Enable Error Interrupt 31 */
      vuint32_t EEI30:1;               /* Enable Error Interrupt 30 */
      vuint32_t EEI29:1;               /* Enable Error Interrupt 29 */
      vuint32_t EEI28:1;               /* Enable Error Interrupt 28 */
      vuint32_t EEI27:1;               /* Enable Error Interrupt 27 */
      vuint32_t EEI26:1;               /* Enable Error Interrupt 26 */
      vuint32_t EEI25:1;               /* Enable Error Interrupt 25 */
      vuint32_t EEI24:1;               /* Enable Error Interrupt 24 */
      vuint32_t EEI23:1;               /* Enable Error Interrupt 23 */
      vuint32_t EEI22:1;               /* Enable Error Interrupt 22 */
      vuint32_t EEI21:1;               /* Enable Error Interrupt 21 */
      vuint32_t EEI20:1;               /* Enable Error Interrupt 20 */
      vuint32_t EEI19:1;               /* Enable Error Interrupt 19 */
      vuint32_t EEI18:1;               /* Enable Error Interrupt 18 */
      vuint32_t EEI17:1;               /* Enable Error Interrupt 17 */
      vuint32_t EEI16:1;               /* Enable Error Interrupt 16 */
      vuint32_t EEI15:1;               /* Enable Error Interrupt 15 */
      vuint32_t EEI14:1;               /* Enable Error Interrupt 14 */
      vuint32_t EEI13:1;               /* Enable Error Interrupt 13 */
      vuint32_t EEI12:1;               /* Enable Error Interrupt 12 */
      vuint32_t EEI11:1;               /* Enable Error Interrupt 11 */
      vuint32_t EEI10:1;               /* Enable Error Interrupt 10 */
      vuint32_t EEI9:1;                /* Enable Error Interrupt 9 */
      vuint32_t EEI8:1;                /* Enable Error Interrupt 8 */
      vuint32_t EEI7:1;                /* Enable Error Interrupt 7 */
      vuint32_t EEI6:1;                /* Enable Error Interrupt 6 */
      vuint32_t EEI5:1;                /* Enable Error Interrupt 5 */
      vuint32_t EEI4:1;                /* Enable Error Interrupt 4 */
      vuint32_t EEI3:1;                /* Enable Error Interrupt 3 */
      vuint32_t EEI2:1;                /* Enable Error Interrupt 2 */
      vuint32_t EEI1:1;                /* Enable Error Interrupt 1 */
      vuint32_t EEI0:1;                /* Enable Error Interrupt 0 */
    } B;
  } EEI;

  union {                              /* Set Enable Request Register */
    vuint8_t R;
    struct {
      vuint8_t NOP:1;                  /* No Op enable */
      vuint8_t SAER:1;                 /* Set All Enable Requests */
      vuint8_t  :1;
      vuint8_t SERQ:5;                 /* Set Enable Request */
    } B;
  } SERQ;

  union {                              /* Clear Enable Request Register */
    vuint8_t R;
    struct {
      vuint8_t NOP:1;                  /* No Op enable */
      vuint8_t CAER:1;                 /* Clear All Enable Requests */
      vuint8_t  :1;
      vuint8_t CERQ:5;                 /* Clear Enable Request */
    } B;
  } CERQ;

  union {                              /* Set Enable Error Interrupt Register */
    vuint8_t R;
    struct {
      vuint8_t NOP:1;                  /* No Op enable */
      vuint8_t SAEE:1;                 /* Sets All Enable Error Interrupts */
      vuint8_t  :1;
      vuint8_t SEEI:5;                 /* Set Enable Error Interrupt */
    } B;
  } SEEI;

  union {                              /* Clear Enable Error Interrupt Register */
    vuint8_t R;
    struct {
      vuint8_t NOP:1;                  /* No Op enable */
      vuint8_t CAEE:1;                 /* Clear All Enable Error Interrupts */
      vuint8_t  :1;
      vuint8_t CEEI:5;                 /* Clear Enable Error Interrupt */
    } B;
  } CEEI;

  union {                              /* Clear Interrupt Request Register */
    vuint8_t R;
    struct {
      vuint8_t NOP:1;                  /* No Op enable */
      vuint8_t CAIR:1;                 /* Clear All Interrupt Requests */
      vuint8_t  :1;
      vuint8_t CINT:5;                 /* Clear interrupt request */
    } B;
  } CINT;

  union {                              /* Clear Error Register */
    vuint8_t R;
    struct {
      vuint8_t NOP:1;                  /* No Op enable */
      vuint8_t CAEI:1;                 /* Clear All Error Indicators */
      vuint8_t  :1;
      vuint8_t CERR:5;                 /* Clear Error Indicator */
    } B;
  } CERR;

  union {                              /* Set START Bit Register */
    vuint8_t R;
    struct {
      vuint8_t NOP:1;                  /* No Op enable */
      vuint8_t SAST:1;                 /* Set All START Bits (activates all channels) */
      vuint8_t  :1;
      vuint8_t SSRT:5;                 /* Set START Bit */
    } B;
  } SSRT;

  union {                              /* Clear DONE Status Bit Register */
    vuint8_t R;
    struct {
      vuint8_t NOP:1;                  /* No Op enable */
      vuint8_t CADN:1;                 /* Clears All DONE Bits */
      vuint8_t  :1;
      vuint8_t CDNE:5;                 /* Clear DONE Bit */
    } B;
  } CDNE;

  uint8_t DMA_reserved2[4];
  union {                              /* Interrupt Request Register */
    vuint32_t R;
    struct {
      vuint32_t INT31:1;               /* Interrupt Request 31 */
      vuint32_t INT30:1;               /* Interrupt Request 30 */
      vuint32_t INT29:1;               /* Interrupt Request 29 */
      vuint32_t INT28:1;               /* Interrupt Request 28 */
      vuint32_t INT27:1;               /* Interrupt Request 27 */
      vuint32_t INT26:1;               /* Interrupt Request 26 */
      vuint32_t INT25:1;               /* Interrupt Request 25 */
      vuint32_t INT24:1;               /* Interrupt Request 24 */
      vuint32_t INT23:1;               /* Interrupt Request 23 */
      vuint32_t INT22:1;               /* Interrupt Request 22 */
      vuint32_t INT21:1;               /* Interrupt Request 21 */
      vuint32_t INT20:1;               /* Interrupt Request 20 */
      vuint32_t INT19:1;               /* Interrupt Request 19 */
      vuint32_t INT18:1;               /* Interrupt Request 18 */
      vuint32_t INT17:1;               /* Interrupt Request 17 */
      vuint32_t INT16:1;               /* Interrupt Request 16 */
      vuint32_t INT15:1;               /* Interrupt Request 15 */
      vuint32_t INT14:1;               /* Interrupt Request 14 */
      vuint32_t INT13:1;               /* Interrupt Request 13 */
      vuint32_t INT12:1;               /* Interrupt Request 12 */
      vuint32_t INT11:1;               /* Interrupt Request 11 */
      vuint32_t INT10:1;               /* Interrupt Request 10 */
      vuint32_t INT9:1;                /* Interrupt Request 9 */
      vuint32_t INT8:1;                /* Interrupt Request 8 */
      vuint32_t INT7:1;                /* Interrupt Request 7 */
      vuint32_t INT6:1;                /* Interrupt Request 6 */
      vuint32_t INT5:1;                /* Interrupt Request 5 */
      vuint32_t INT4:1;                /* Interrupt Request 4 */
      vuint32_t INT3:1;                /* Interrupt Request 3 */
      vuint32_t INT2:1;                /* Interrupt Request 2 */
      vuint32_t INT1:1;                /* Interrupt Request 1 */
      vuint32_t INT0:1;                /* Interrupt Request 0 */
    } B;
  } INT;

  uint8_t DMA_reserved3[4];
  union {                              /* Error Register */
    vuint32_t R;
    struct {
      vuint32_t ERR31:1;               /* Error In Channel 31 */
      vuint32_t ERR30:1;               /* Error In Channel 30 */
      vuint32_t ERR29:1;               /* Error In Channel 29 */
      vuint32_t ERR28:1;               /* Error In Channel 28 */
      vuint32_t ERR27:1;               /* Error In Channel 27 */
      vuint32_t ERR26:1;               /* Error In Channel 26 */
      vuint32_t ERR25:1;               /* Error In Channel 25 */
      vuint32_t ERR24:1;               /* Error In Channel 24 */
      vuint32_t ERR23:1;               /* Error In Channel 23 */
      vuint32_t ERR22:1;               /* Error In Channel 22 */
      vuint32_t ERR21:1;               /* Error In Channel 21 */
      vuint32_t ERR20:1;               /* Error In Channel 20 */
      vuint32_t ERR19:1;               /* Error In Channel 19 */
      vuint32_t ERR18:1;               /* Error In Channel 18 */
      vuint32_t ERR17:1;               /* Error In Channel 17 */
      vuint32_t ERR16:1;               /* Error In Channel 16 */
      vuint32_t ERR15:1;               /* Error In Channel 15 */
      vuint32_t ERR14:1;               /* Error In Channel 14 */
      vuint32_t ERR13:1;               /* Error In Channel 13 */
      vuint32_t ERR12:1;               /* Error In Channel 12 */
      vuint32_t ERR11:1;               /* Error In Channel 11 */
      vuint32_t ERR10:1;               /* Error In Channel 10 */
      vuint32_t ERR9:1;                /* Error In Channel 9 */
      vuint32_t ERR8:1;                /* Error In Channel 8 */
      vuint32_t ERR7:1;                /* Error In Channel 7 */
      vuint32_t ERR6:1;                /* Error In Channel 6 */
      vuint32_t ERR5:1;                /* Error In Channel 5 */
      vuint32_t ERR4:1;                /* Error In Channel 4 */
      vuint32_t ERR3:1;                /* Error In Channel 3 */
      vuint32_t ERR2:1;                /* Error In Channel 2 */
      vuint32_t ERR1:1;                /* Error In Channel 1 */
      vuint32_t ERR0:1;                /* Error In Channel 0 */
    } B;
  } ERR;

  uint8_t DMA_reserved4[4];
  union {                              /* Hardware Request Status Register */
    vuint32_t R;
    struct {
      vuint32_t HRS31:1;               /* Hardware Request Status Channel 31 */
      vuint32_t HRS30:1;               /* Hardware Request Status Channel 30 */
      vuint32_t HRS29:1;               /* Hardware Request Status Channel 29 */
      vuint32_t HRS28:1;               /* Hardware Request Status Channel 28 */
      vuint32_t HRS27:1;               /* Hardware Request Status Channel 27 */
      vuint32_t HRS26:1;               /* Hardware Request Status Channel 26 */
      vuint32_t HRS25:1;               /* Hardware Request Status Channel 25 */
      vuint32_t HRS24:1;               /* Hardware Request Status Channel 24 */
      vuint32_t HRS23:1;               /* Hardware Request Status Channel 23 */
      vuint32_t HRS22:1;               /* Hardware Request Status Channel 22 */
      vuint32_t HRS21:1;               /* Hardware Request Status Channel 21 */
      vuint32_t HRS20:1;               /* Hardware Request Status Channel 20 */
      vuint32_t HRS19:1;               /* Hardware Request Status Channel 19 */
      vuint32_t HRS18:1;               /* Hardware Request Status Channel 18 */
      vuint32_t HRS17:1;               /* Hardware Request Status Channel 17 */
      vuint32_t HRS16:1;               /* Hardware Request Status Channel 16 */
      vuint32_t HRS15:1;               /* Hardware Request Status Channel 15 */
      vuint32_t HRS14:1;               /* Hardware Request Status Channel 14 */
      vuint32_t HRS13:1;               /* Hardware Request Status Channel 13 */
      vuint32_t HRS12:1;               /* Hardware Request Status Channel 12 */
      vuint32_t HRS11:1;               /* Hardware Request Status Channel 11 */
      vuint32_t HRS10:1;               /* Hardware Request Status Channel 10 */
      vuint32_t HRS9:1;                /* Hardware Request Status Channel 9 */
      vuint32_t HRS8:1;                /* Hardware Request Status Channel 8 */
      vuint32_t HRS7:1;                /* Hardware Request Status Channel 7 */
      vuint32_t HRS6:1;                /* Hardware Request Status Channel 6 */
      vuint32_t HRS5:1;                /* Hardware Request Status Channel 5 */
      vuint32_t HRS4:1;                /* Hardware Request Status Channel 4 */
      vuint32_t HRS3:1;                /* Hardware Request Status Channel 3 */
      vuint32_t HRS2:1;                /* Hardware Request Status Channel 2 */
      vuint32_t HRS1:1;                /* Hardware Request Status Channel 1 */
      vuint32_t HRS0:1;                /* Hardware Request Status Channel 0 */
    } B;
  } HRS;

  uint8_t DMA_reserved5[200];
  union {                              /* Channel n Priority Register */
    vuint8_t R;
    struct {
      vuint8_t ECP:1;                  /* Enable Channel Preemption. This bit resets to zero. */
      vuint8_t DPA:1;                  /* Disable preempt ability. This bit resets to zero. */
      vuint8_t GRPPRI:2;               /* Channel n Current Group Priority */
      vuint8_t CHPRI:4;                /* Channel n Arbitration Priority */
    } B;
  } DCHPRI[32];

  uint8_t DMA_reserved6[32];
  union {                              /* Channel n Master ID Register */
    vuint8_t R;
    struct {
      vuint8_t EMI:1;                  /* Enable Master ID replication */
      vuint8_t PAL:1;                  /* Privileged Access Level */
      vuint8_t  :2;
      vuint8_t MID:4;                  /* Master ID */
    } B;
  } DCHMID[32];

  uint8_t DMA_reserved7[3744];
  struct {
    union {                            /* TCD Source Address */
      vuint32_t R;
      struct {
        vuint32_t SADDR:32;            /* Source Address */
      } B;
    } SADDR;
    union {                            /* TCD Transfer Attributes */
      vuint16_t R;
      struct {
        vuint16_t SMOD:5;              /* Source Address Modulo */
        vuint16_t SSIZE:3;             /* Source data transfer size */
        vuint16_t DMOD:5;              /* Destination Address Modulo */
        vuint16_t DSIZE:3;             /* Destination Data Transfer Size */
      } B;
    } ATTR;
    union {                            /* TCD Signed Source Address Offset */
      vuint16_t R;
      struct {
        vuint16_t SOFF:16;             /* Source Address Signed Offset */
      } B;
    } SOFF;
    union {
      union {                          /* TCD Minor Byte Count (Minor Loop Disabled) */
        vuint32_t R;
        struct {
          vuint32_t NBYTES:32;         /* Minor Byte Transfer Count */
        } B;
      } MLNO;
      union {                          /* TCD Signed Minor Loop Offset (Minor Loop Enabled and Offset Disabled) */
        vuint32_t R;
        struct {
          vuint32_t SMLOE:1;           /* Source Minor Loop Offset Enable */
          vuint32_t DMLOE:1;           /* Destination Minor Loop Offset enable */
          vuint32_t NBYTES:30;         /* Minor Byte Transfer Count */
        } B;
      } MLOFFNO;
      union {                          /* TCD Signed Minor Loop Offset (Minor Loop and Offset Enabled) */
        vuint32_t R;
        struct {
          vuint32_t SMLOE:1;           /* Source Minor Loop Offset Enable */
          vuint32_t DMLOE:1;           /* Destination Minor Loop Offset Enable */
          vuint32_t MLOFF:20;          /* If SMLOE or DMLOE is set, this field represents a sign-extended offset applied to the source or destination address to form the next-state value after the minor loop completes. */
          vuint32_t NBYTES:10;         /* Minor Byte Transfer Count */
        } B;
      } MLOFFYES;
    } NBYTES;
    union {                            /* TCD Last Source Address Adjustment */
      vuint32_t R;
      struct {
        vuint32_t SLAST:32;            /* Last Source Address Adjustment */
      } B;
    } SLAST;
    union {                            /* TCD Destination Address */
      vuint32_t R;
      struct {
        vuint32_t DADDR:32;            /* Destination Address */
      } B;
    } DADDR;
    union {
      union {                          /* TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled) */
        vuint16_t R;
        struct {
          vuint16_t ELINK:1;           /* Enable channel-to-channel linking on minor-loop complete */
          vuint16_t CITER:15;          /* Current Major Iteration Count */
        } B;
      } ELINKNO;
      union {                          /* TCD Current Minor Loop Link, Major Loop Count (Channel Linking Enabled) */
        vuint16_t R;
        struct {
          vuint16_t ELINK:1;           /* Enable channel-to-channel linking on minor-loop complete */
          vuint16_t  :1;
          vuint16_t LINKCH:5;          /* Link Channel Number */
          vuint16_t CITER:9;           /* Current Major Iteration Count */
        } B;
      } ELINKYES;
    } CITER;
    union {                            /* TCD Signed Destination Address Offset */
      vuint16_t R;
      struct {
        vuint16_t DOFF:16;             /* Destination Address Signed Offset */
      } B;
    } DOFF;
    union {                            /* TCD Last Destination Address Adjustment/Scatter Gather Address */
      vuint32_t R;
      struct {
        vuint32_t DLASTSGA:32;
      } B;
    } DLASTSGA;
    union {
      union {                          /* TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled) */
        vuint16_t R;
        struct {
          vuint16_t ELINK:1;           /* Enables channel-to-channel linking on minor loop complete */
          vuint16_t BITER:15;          /* Starting Major Iteration Count */
        } B;
      } ELINKNO;
      union {                          /* TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Enabled) */
        vuint16_t R;
        struct {
          vuint16_t ELINK:1;           /* Enables channel-to-channel linking on minor loop complete */
          vuint16_t  :1;
          vuint16_t LINKCH:5;          /* Link Channel Number */
          vuint16_t BITER:9;           /* Starting Major Iteration Count */
        } B;
      } ELINKYES;
    } BITER;
    union {                            /* TCD Control and Status */
      vuint16_t R;
      struct {
        vuint16_t BWC:2;               /* Bandwidth Control */
        vuint16_t  :1;
        vuint16_t MAJORLINKCH:5;       /* Link Channel Number */
        vuint16_t DONE:1;              /* Channel Done */
        vuint16_t ACTIVE:1;            /* Channel Active */
        vuint16_t MAJORELINK:1;        /* Enable channel-to-channel linking on major loop complete */
        vuint16_t ESG:1;               /* Enable Scatter/Gather Processing */
        vuint16_t DREQ:1;              /* Disable Request */
        vuint16_t INTHALF:1;           /* Enable an interrupt when major counter is half complete. */
        vuint16_t INTMAJOR:1;          /* Enable an interrupt when major iteration count completes */
        vuint16_t START:1;             /* Channel Start */
      } B;
    } CSR;
  } TCD[32];
};


/* ============================================================================
   =============================== Module: EIM ================================
   ============================================================================ */

struct EIM_tag {
  union {                              /* Error Injection Module Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :31;
      vuint32_t GEIEN:1;               /* Global Error Injection Enable. */
    } B;
  } EIMCR;

  union {                              /* Error Injection Channel Enable register */
    vuint32_t R;
    struct {
      vuint32_t EICH0EN:1;             /* Error Injection Channel 0 Enable */
      vuint32_t  :31;
    } B;
  } EICHEN;

  uint8_t EIM_reserved0[248];
  union {                              /* Error Injection Channel Descriptor, Word0 */
    vuint32_t R;
    struct {
      vuint32_t CHKBIT_MASK:8;         /* Checkbit Mask. */
      vuint32_t  :24;
    } B;
  } EICHD_Word0;

  union {                              /* Error Injection Channel Descriptor, Word1 */
    vuint32_t R;
    struct {
      vuint32_t UDATA_MASK:32;         /* Upper Data Mask. */
    } B;
  } EICHD_Word1;

  union {                              /* Error Injection Channel Descriptor, Word2 */
    vuint32_t R;
    struct {
      vuint32_t LDATA_MASK:32;         /* Lower Data Mask. */
    } B;
  } EICHD_Word2;
};


/* ============================================================================
   =============================== Module: FEC ===============================
   ============================================================================ */

struct FEC_tag {
  uint8_t FEC_reserved0[4];
  union {                              /* Interrupt Event Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t BABR:1;                /* Babbling Receive Error */
      vuint32_t BABT:1;                /* Babbling Transmit Error */
      vuint32_t GRA:1;                 /* Graceful Stop Complete */
      vuint32_t TXF:1;                 /* Transmit Frame Interrupt */
      vuint32_t TXB:1;                 /* Transmit Buffer Interrupt */
      vuint32_t RXF:1;                 /* Receive Frame Interrupt */
      vuint32_t RXB:1;                 /* Receive Buffer Interrupt */
      vuint32_t MII:1;                 /* MII Interrupt. */
      vuint32_t EBERR:1;               /* Ethernet Bus Error */
      vuint32_t LC:1;                  /* Late Collision */
      vuint32_t RL:1;                  /* Collision Retry Limit */
      vuint32_t UN:1;                  /* Transmit FIFO Underrun */
      vuint32_t PLR:1;                 /* Payload Receive Error */
      vuint32_t WAKEUP:1;              /* Node Wakeup Request Indication */
      vuint32_t TS_AVAIL:1;            /* Transmit Timestamp Available */
      vuint32_t TS_TIMER:1;            /* Timestamp Timer */
      vuint32_t  :2;
      vuint32_t  :1;
      vuint32_t  :12;
    } B;
  } EIR;

  union {                              /* Interrupt Mask Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t BABR:1;                /* BABR Interrupt Mask */
      vuint32_t BABT:1;                /* BABT Interrupt Mask */
      vuint32_t GRA:1;                 /* GRA Interrupt Mask */
      vuint32_t TXF:1;                 /* TXF Interrupt Mask */
      vuint32_t TXB:1;                 /* TXB Interrupt Mask */
      vuint32_t RXF:1;                 /* RXF Interrupt Mask */
      vuint32_t RXB:1;                 /* RXB Interrupt Mask */
      vuint32_t MII:1;                 /* MII Interrupt Mask */
      vuint32_t EBERR:1;               /* EBERR Interrupt Mask */
      vuint32_t LC:1;                  /* LC Interrupt Mask */
      vuint32_t RL:1;                  /* RL Interrupt Mask */
      vuint32_t UN:1;                  /* UN Interrupt Mask */
      vuint32_t PLR:1;                 /* PLR Interrupt Mask */
      vuint32_t WAKEUP:1;              /* WAKEUP Interrupt Mask */
      vuint32_t TS_AVAIL:1;            /* TS_AVAIL Interrupt Mask */
      vuint32_t TS_TIMER:1;            /* TS_TIMER Interrupt Mask */
      vuint32_t  :2;
      vuint32_t  :1;
      vuint32_t  :12;
    } B;
  } EIMR;

  uint8_t FEC_reserved1[4];
  union {                              /* Receive Descriptor Active Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t R_DES_ACTIVE:1;                /* Receive Descriptor Active */
      vuint32_t  :24;
    } B;
  } RDAR;

  union {                              /* Transmit Descriptor Active Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t X_DES_ACTIVE:1;                /* Transmit Descriptor Active */
      vuint32_t  :24;
    } B;
  } TDAR;

  uint8_t FEC_reserved2[12];
  union {                              /* Ethernet Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :20;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t DBSWP:1;               /* Descriptor Byte Swapping Enable */
      vuint32_t STOPEN:1;              /* STOPEN Signal Control */
      vuint32_t DBGEN:1;               /* Debug Enable */
      vuint32_t  :1;
      vuint32_t EN1588:1;              /* EN1588 Enable */
      vuint32_t SLEEP:1;               /* Sleep Mode Enable */
      vuint32_t MAGICEN:1;             /* Magic Packet Detection Enable */
      vuint32_t ETHER_EN:1;             /* Ethernet Enable */
      vuint32_t RESET:1;               /* Ethernet MAC Reset */
    } B;
  } ECR;

  uint8_t FEC_reserved3[24];
  union {                              /* MII Management Frame Register */
    vuint32_t R;
    struct {
      vuint32_t ST:2;                  /* Start Of Frame Delimiter */
      vuint32_t OP:2;                  /* Operation Code */
      vuint32_t PA:5;                  /* PHY Address */
      vuint32_t RA:5;                  /* Register Address */
      vuint32_t TA:2;                  /* Turn Around */
      vuint32_t DATA:16;               /* Management Frame Data */
    } B;
  } MDATA;

  union {                              /* MII Speed Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :21;
      vuint32_t HOLDTIME:3;            /* Holdtime On MDIO Output */
      vuint32_t DIS_PREAMBLE:1;             /* Disable Preamble */
      vuint32_t MII_SPEED:6;           /* MII Speed */
      vuint32_t  :1;
    } B;
  } MSCR;

  uint8_t FEC_reserved4[28];
  union {                              /* MIB Control Register */
    vuint32_t R;
    struct {
      vuint32_t MIB_DIS:1;             /* Disable MIB Logic */
      vuint32_t MIB_IDLE:1;            /* MIB Idle */
      vuint32_t MIB_CLEAR:1;           /* MIB Clear */
      vuint32_t  :29;
    } B;
  } MIBC;

  uint8_t FEC_reserved5[28];
  union {                              /* Receive Control Register */
    vuint32_t R;
    struct {
      vuint32_t GRS:1;                 /* Graceful Receive Stopped */
      vuint32_t NLC:1;                 /* Payload Length Check Disable */
      vuint32_t MAX_FL:14;             /* Maximum Frame Length */
      vuint32_t CFEN:1;                /* MAC Control Frame Enable */
      vuint32_t CRCFWD:1;              /* Terminate/Forward Received CRC */
      vuint32_t PAUFWD:1;              /* Terminate/Forward Pause Frames */
      vuint32_t PADEN:1;               /* Enable Frame Padding Remove On Receive */
      vuint32_t  :2;
      vuint32_t RMII_10T:1;
      vuint32_t RMII_MODE:1;           /* RMII Mode Enable */
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t FCE:1;                 /* Flow Control Enable */
      vuint32_t BC_REJ:1;              /* Broadcast Frame Reject */
      vuint32_t PROM:1;                /* Promiscuous Mode */
      vuint32_t MII_MODE:1;            /* Media Independent Interface Mode */
      vuint32_t DRT:1;                 /* Disable Receive On Transmit */
      vuint32_t LOOP:1;                /* Internal Loopback */
    } B;
  } RCR;

  uint8_t FEC_reserved6[60];
  union {                              /* Transmit Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :22;
      vuint32_t CRCFWD:1;              /* Forward Frame From Application With CRC */
      vuint32_t ADDINS:1;              /* Set MAC Address On Transmit */
      vuint32_t ADDSEL:3;              /* Source MAC Address Select On Transmit */
      vuint32_t RFC_PAUSE:1;           /* Receive Frame Control Pause */
      vuint32_t TFC_PAUSE:1;           /* Transmit Frame Control Pause */
      vuint32_t FDEN:1;                /* Full-Duplex Enable */
      vuint32_t HBC:1;
      vuint32_t GTS:1;                 /* Graceful Transmit Stop */
    } B;
  } TCR;

  uint8_t FEC_reserved7[28];
  union {                              /* Physical Address Lower Register */
    vuint32_t R;
    struct {
      vuint32_t PADDR1:32;             /* Pause Address */
    } B;
  } PALR;

  union {                              /* Physical Address Upper Register */
    vuint32_t R;
    struct {
      vuint32_t PADDR2:16;
      vuint32_t TYPE:16;               /* Type Field In PAUSE Frames */
    } B;
  } PAUR;

  union {                              /* Opcode/Pause Duration Register */
    vuint32_t R;
    struct {
      vuint32_t OPCODE:16;             /* Opcode Field In PAUSE Frames */
      vuint32_t PAUSE_DUR:16;          /* Pause Duration */
    } B;
  } OPD;

  uint8_t FEC_reserved8[40];
  union {                              /* Descriptor Individual Upper Address Register */
    vuint32_t R;
    struct {
      vuint32_t IADDR1:32;
    } B;
  } IAUR;

  union {                              /* Descriptor Individual Lower Address Register */
    vuint32_t R;
    struct {
      vuint32_t IADDR2:32;
    } B;
  } IALR;

  union {                              /* Descriptor Group Upper Address Register */
    vuint32_t R;
    struct {
      vuint32_t GADDR1:32;
    } B;
  } GAUR;

  union {                              /* Descriptor Group Lower Address Register */
    vuint32_t R;
    struct {
      vuint32_t GADDR2:32;
    } B;
  } GALR;

  uint8_t FEC_reserved9[28];
  union {                              /* Transmit FIFO Watermark Register */
    vuint32_t R;
    struct {
      vuint32_t  :23;
      vuint32_t STRFWD:1;              /* Store And Forward Enable */
      vuint32_t  :2;
      vuint32_t X_WMRK:6;                /* Transmit FIFO Write */
    } B;
  } TFWR;

  uint8_t FEC_reserved10[56];
  union {                              /* Receive Descriptor Ring Start Register */
    vuint32_t R;
    struct {
      vuint32_t R_DES_START:29;
      vuint32_t  :3;
    } B;
  } ERDSR;

  union {                              /* Transmit Buffer Descriptor Ring Start Register */
    vuint32_t R;
    struct {
      vuint32_t X_DES_START:29;
      vuint32_t  :3;
    } B;
  } ETDSR;

  union {                              /* Maximum Receive Buffer Size Register */
    vuint32_t R;
    struct {
      vuint32_t  :18;
      vuint32_t R_BUF_SIZE:10;
      vuint32_t  :4;
    } B;
  } EMRBR;

  uint8_t FEC_reserved11[4];
  union {                              /* Receive FIFO Section Full Threshold */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t RX_SECTION_FULL:8;     /* Value Of Receive FIFO Section Full Threshold */
    } B;
  } RSFL;

  union {                              /* Receive FIFO Section Empty Threshold */
    vuint32_t R;
    struct {
      vuint32_t  :11;
      vuint32_t STAT_SECTION_EMPTY:5;  /* RX Status FIFO Section Empty Threshold */
      vuint32_t  :8;
      vuint32_t RX_SECTION_EMPTY:8;    /* Value Of The Receive FIFO Section Empty Threshold */
    } B;
  } RSEM;

  union {                              /* Receive FIFO Almost Empty Threshold */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t RX_ALMOST_EMPTY:8;     /* Value Of The Receive FIFO Almost Empty Threshold */
    } B;
  } RAEM;

  union {                              /* Receive FIFO Almost Full Threshold */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t RX_ALMOST_FULL:8;      /* Value Of The Receive FIFO Almost Full Threshold */
    } B;
  } RAFL;

  union {                              /* Transmit FIFO Section Empty Threshold */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t TX_SECTION_EMPTY:8;    /* Value Of The Transmit FIFO Section Empty Threshold */
    } B;
  } TSEM;

  union {                              /* Transmit FIFO Almost Empty Threshold */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t TX_ALMOST_EMPTY:8;     /* Value of Transmit FIFO Almost Empty Threshold */
    } B;
  } TAEM;

  union {                              /* Transmit FIFO Almost Full Threshold */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t TX_ALMOST_FULL:8;      /* Value Of The Transmit FIFO Almost Full Threshold */
    } B;
  } TAFL;

  union {                              /* Transmit Inter-Packet Gap */
    vuint32_t R;
    struct {
      vuint32_t  :27;
      vuint32_t IPG:5;                 /* Transmit Inter-Packet Gap */
    } B;
  } TIPG;

  union {                              /* Frame Truncation Length */
    vuint32_t R;
    struct {
      vuint32_t  :18;
      vuint32_t TRUNC_FL:14;           /* Frame Truncation Length */
    } B;
  } FTRL;

  uint8_t FEC_reserved12[12];
  union {                              /* Transmit Accelerator Function Configuration */
    vuint32_t R;
    struct {
      vuint32_t  :27;
      vuint32_t PROCHK:1;
      vuint32_t IPCHK:1;
      vuint32_t  :2;
      vuint32_t SHIFT16:1;             /* TX FIFO Shift-16 */
    } B;
  } TACC;

  union {                              /* Receive Accelerator Function Configuration */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t SHIFT16:1;             /* RX FIFO Shift-16 */
      vuint32_t LINEDIS:1;             /* Enable Discard Of Frames With MAC Layer Errors */
      vuint32_t  :3;
      vuint32_t PRODIS:1;              /* Enable Discard Of Frames With Wrong Protocol Checksum */
      vuint32_t IPDIS:1;               /* Enable Discard Of Frames With Wrong IPv4 Header Checksum */
      vuint32_t PADREM:1;              /* Enable Padding Removal For Short IP Frames */
    } B;
  } RACC;

  uint8_t FEC_reserved13[568];
  union {                              /* Timer Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :18;
      vuint32_t SLAVE:1;               /* Enable Timer Slave Mode */
      vuint32_t  :1;
      vuint32_t CAPTURE:1;             /* Capture Timer Value */
      vuint32_t  :1;
      vuint32_t RE_START:1;             /* Reset Timer, changed name from RESTART since defined in os.h */
      vuint32_t  :1;
      vuint32_t PINPER:1;
      vuint32_t  :2;
      vuint32_t PEREN:1;               /* Enable Periodical Event */
      vuint32_t OFFRST:1;              /* Reset Timer On Offset Event */
      vuint32_t OFFEN:1;               /* Enable One-Shot Offset Event */
      vuint32_t  :1;
      vuint32_t EN:1;                  /* Enable Timer */
    } B;
  } ATCR;

  union {                              /* Timer Value Register */
    vuint32_t R;
    struct {
      vuint32_t ATIME:32;
    } B;
  } ATVR;

  union {                              /* Timer Offset Register */
    vuint32_t R;
    struct {
      vuint32_t OFFSET:32;
    } B;
  } ATOFF;

  union {                              /* Timer Period Register */
    vuint32_t R;
    struct {
      vuint32_t PERIOD:32;
    } B;
  } ATPER;

  union {                              /* Timer Correction Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t COR:31;                /* Correction Counter Wrap-Around Value */
    } B;
  } ATCOR;

  union {                              /* Time-Stamping Clock Period Register */
    vuint32_t R;
    struct {
      vuint32_t  :17;
      vuint32_t INC_CORR:7;            /* Correction Increment Value */
      vuint32_t  :1;
      vuint32_t INC:7;                 /* Clock Period Of The Timestamping Clock (ts_clk) In Nanoseconds */
    } B;
  } ATINC;

  union {                              /* Timestamp of Last Transmitted Frame */
    vuint32_t R;
    struct {
      vuint32_t TIMESTAMP:32;
    } B;
  } ATSTMP;

  uint8_t FEC_reserved14[488];
  union {                              /* Timer Global Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :28;
      vuint32_t TF3:1;                 /* Copy Of Timer Flag For Channel 3 */
      vuint32_t TF2:1;                 /* Copy Of Timer Flag For Channel 2 */
      vuint32_t TF1:1;                 /* Copy Of Timer Flag For Channel 1 */
      vuint32_t TF0:1;                 /* Copy Of Timer Flag For Channel 0 */
    } B;
  } TGSR;

  struct {
    union {                            /* Timer Control Status Register */
      vuint32_t R;
      struct {
        vuint32_t  :24;
        vuint32_t TF:1;                /* Timer Flag */
        vuint32_t TIE:1;               /* Timer Interrupt Enable */
        vuint32_t TMODE:4;             /* Timer Mode */
        vuint32_t  :1;
        vuint32_t TDRE:1;              /* Timer DMA Request Enable */
      } B;
    } TCSR;
    union {                            /* Timer Compare Capture Register */
      vuint32_t R;
      struct {
        vuint32_t TCC:32;              /* Timer Capture Compare */
      } B;
    } TCCR;
  } TIMER[4];
};


/* ============================================================================
   =============================== Module: ETIMER =============================
   ============================================================================ */

struct ETIMER_tag {
  struct {
    union {                            /* Channel n Compare Register 1 */
      vuint16_t R;
      struct {
        vuint16_t COMP1:16;
      } B;
    } COMP1;
    union {                            /* Channel n Compare Register 2 */
      vuint16_t R;
      struct {
        vuint16_t COMP2:16;
      } B;
    } COMP2;
    union {                            /* Channel n Capture Register 1 */
      vuint16_t R;
      struct {
        vuint16_t CAPT1:16;
      } B;
    } CAPT1;
    union {                            /* Channel n Capture Register 2 */
      vuint16_t R;
      struct {
        vuint16_t CAPT2:16;
      } B;
    } CAPT2;
    union {                            /* Channel n Load Register */
      vuint16_t R;
      struct {
        vuint16_t LOAD:16;
      } B;
    } LOAD;
    union {                            /* Channel n Hold Register */
      vuint16_t R;
      struct {
        vuint16_t HOLD:16;
      } B;
    } HOLD;
    union {                            /* Channel n Counter Register */
      vuint16_t R;
      struct {
        vuint16_t CNTR:16;
      } B;
    } CNTR;
    union {                            /* Channel n Control Register 1 */
      vuint16_t R;
      struct {
        vuint16_t CNTMODE:3;           /* Count mode */
        vuint16_t PRISRC:5;            /* Primary Count Source */
        vuint16_t ONCE:1;              /* Count once */
        vuint16_t LENGTH:1;            /* Count Length */
        vuint16_t DIR:1;               /* Count Direction */
        vuint16_t SECSRC:5;            /* Secondary Count Source */
      } B;
    } CTRL1;
    union {                            /* Channel n Control Register 2 */
      vuint16_t R;
      struct {
        vuint16_t OEN:1;               /* Output Enable */
        vuint16_t RDNT:1;              /* Redundant Channel Enable */
        vuint16_t INPUT:1;             /* External input signal */
        vuint16_t VAL:1;               /* Forced OFLAG Value */
        vuint16_t FORCE:1;             /* Force the OFLAG output */
        vuint16_t COFRC:1;             /* Co-channel OFLAG Force */
        vuint16_t COINIT:2;            /* Co-channel Initialization */
        vuint16_t SIPS:1;              /* Secondary Source Input Polarity Select */
        vuint16_t PIPS:1;              /* Primary Source Input Polarity Select */
        vuint16_t OPS:1;               /* Output Polarity Select. */
        vuint16_t MSTR:1;              /* Master Mode */
        vuint16_t OUTMODE:4;           /* Output Mode */
      } B;
    } CTRL2;
    union {                            /* Channel n Control Register 3 */
      vuint16_t R;
      struct {
        vuint16_t STPEN:1;             /* Stop Actions Enable */
        vuint16_t ROC:2;               /* Reload on Capture */
        vuint16_t  :5;
        vuint16_t C2FCNT:3;            /* Capture 2 FIFO count */
        vuint16_t C1FCNT:3;            /* Capture 1 FIFO count */
        vuint16_t DBGEN:2;             /* Debug Actions Enable */
      } B;
    } CTRL3;
    union {                            /* Channel n Status Register */
      vuint16_t R;
      struct {
        vuint16_t  :6;
        vuint16_t WDF:1;               /* Watchdog Time-out Flag */
        vuint16_t RCF:1;               /* Redundant Channel Flag */
        vuint16_t ICF2:1;              /* Input Capture 2 Flag */
        vuint16_t ICF1:1;              /* Input Capture 1 Flag */
        vuint16_t IEHF:1;              /* Input Edge High Flag */
        vuint16_t IELF:1;              /* Input Edge Low Flag */
        vuint16_t TOF:1;               /* Timer Overflow Flag */
        vuint16_t TCF2:1;              /* Timer Compare 2 Flag */
        vuint16_t TCF1:1;              /* Timer Compare 1 Flag */
        vuint16_t TCF:1;
      } B;
    } STS;
    union {                            /* Channel n Interrupt and DMA Enable Register */
      vuint16_t R;
      struct {
        vuint16_t ICF2DE:1;            /* Input Capture 2 Flag DMA Enable */
        vuint16_t ICF1DE:1;            /* Input Capture 1 Flag DMA Enable */
        vuint16_t CMPLD2DE:1;          /* Comparator Load Register 2 Flag DMA Enable */
        vuint16_t CMPLD1DE:1;          /* Comparator Load Register 1 Flag DMA Enable */
        vuint16_t  :2;
        vuint16_t WDFIE:1;             /* Watchdog Flag Interrupt Enable */
        vuint16_t RCFIE:1;             /* Redundant Channel Flag Interrupt Enable */
        vuint16_t ICF2IE:1;            /* Input Capture 2 Flag Interrupt Enable */
        vuint16_t ICF1IE:1;            /* Input Capture 1 Flag Interrupt Enable */
        vuint16_t IEHFIE:1;            /* Input Edge High Flag Interrupt Enable */
        vuint16_t IELFIE:1;            /* Input Edge Low Flag Interrupt Enable */
        vuint16_t TOFIE:1;             /* Timer Overflow Flag Interrupt Enable */
        vuint16_t TCF2IE:1;            /* Timer Compare 2 Flag Interrupt Enable */
        vuint16_t TCF1IE:1;            /* Timer Compare 1 Flag Interrupt Enable */
        vuint16_t TCFIE:1;             /* Timer Compare Flag Interrupt Enable */
      } B;
    } INTDMA;
    union {                            /* Channel n Comparator Load Register 1 */
      vuint16_t R;
      struct {
        vuint16_t CMPLD1:16;
      } B;
    } CMPLD1;
    union {                            /* Channel n Comparator Load Register 2 */
      vuint16_t R;
      struct {
        vuint16_t CMPLD2:16;
      } B;
    } CMPLD2;
    union {                            /* Channel n Compare and Capture Control Register */
      vuint16_t R;
      struct {
        vuint16_t CLC2:3;              /* Compare Load Control 2 */
        vuint16_t CLC1:3;              /* Compare Load Control 1 */
        vuint16_t CMPMODE:2;           /* Compare Mode */
        vuint16_t CPT2MODE:2;          /* Capture 2 Mode Control */
        vuint16_t CPT1MODE:2;          /* Capture 1 Mode Control */
        vuint16_t CFWM:2;              /* Capture FIFO Water Mark */
        vuint16_t ONESHOT:1;           /* One Shot Capture Mode */
        vuint16_t ARM:1;               /* Arm Capture */
      } B;
    } CCCTRL;
    union {                            /* Channel n Input Filter Register */
      vuint16_t R;
      struct {
        vuint16_t  :5;
        vuint16_t FILT_CNT:3;          /* Input Filter Sample Count */
        vuint16_t FILT_PER:8;          /* Input Filter Sample Period */
      } B;
    } FILT;
  } CH[6];

  uint8_t ETIMER_reserved0[64];
  union {                              /* Watchdog Time-out Low Word Register */
    vuint16_t R;
    struct {
      vuint16_t WDTOL:16;
    } B;
  } WDTOL;

  union {                              /* Watchdog Time-out High Word Register */
    vuint16_t R;
    struct {
      vuint16_t WDTOH:16;
    } B;
  } WDTOH;

  uint8_t ETIMER_reserved1[8];
  union {                              /* Channel Enable Register */
    vuint16_t R;
    struct {
      vuint16_t  :10;
      vuint16_t ENBL:6;                /* Timer Channel Enable */
    } B;
  } ENBL;

  uint8_t ETIMER_reserved2[2];
  union {                              /* DMA Request 0 Select Register */
    vuint16_t R;
    struct {
      vuint16_t DREQ0_EN:1;
      vuint16_t  :10;
      vuint16_t DREQ0:5;
    } B;
  } DREQ0;

  union {                              /* DMA Request 1 Select Register */
    vuint16_t R;
    struct {
      vuint16_t DREQ1_EN:1;
      vuint16_t  :10;
      vuint16_t DREQ1:5;               /* DMA Request Select */
    } B;
  } DREQ1;

  union {                              /* DMA Request 2 Select Register */
    vuint16_t R;
    struct {
      vuint16_t DREQ2_EN:1;
      vuint16_t  :10;
      vuint16_t DREQ2:5;               /* DMA Request Select */
    } B;
  } DREQ2;

  union {                              /* DMA Request 3 Select Register */
    vuint16_t R;
    struct {
      vuint16_t DREQ3_EN:1;
      vuint16_t  :10;
      vuint16_t DREQ3:5;               /* DMA Request Select */
    } B;
  } DREQ3;
};


/* ============================================================================
   =============================== Module: FCCU ===============================
   ============================================================================ */

struct FCCU_tag {
  union {                              /* Control Register */
    vuint32_t R;
    struct {
      vuint32_t FILTER_BYPASS:1;
      vuint32_t FILTER_WIDTH:2;
      vuint32_t  :19;
      vuint32_t DEBUG:1;
      vuint32_t  :1;
      vuint32_t OPS:2;
      vuint32_t  :1;
      vuint32_t OPR:5;
    } B;
  } CTRL;

  union {                              /* CTRL Key Register */
    vuint32_t R;
    struct {
      vuint32_t CTRLK:32;
    } B;
  } CTRLK;

  union {                              /* Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t FCCU_SET_AFTER_RESET:1;
      vuint32_t FCCU_SET_CLEAR:2;
      vuint32_t  :2;
      vuint32_t  :4;
      vuint32_t FOPE:1;
      vuint32_t  :2;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t SM:1;
      vuint32_t PS:1;
      vuint32_t FOM:3;
      vuint32_t FOP:6;
    } B;
  } CFG;

  uint8_t FCCU_reserved0[16];
  union {                              /* NCF Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t NCFC31:1;
      vuint32_t NCFC30:1;
      vuint32_t NCFC29:1;
      vuint32_t NCFC28:1;
      vuint32_t NCFC27:1;
      vuint32_t NCFC26:1;
      vuint32_t NCFC25:1;
      vuint32_t NCFC24:1;
      vuint32_t NCFC23:1;
      vuint32_t NCFC22:1;
      vuint32_t NCFC21:1;
      vuint32_t NCFC20:1;
      vuint32_t NCFC19:1;
      vuint32_t NCFC18:1;
      vuint32_t NCFC17:1;
      vuint32_t NCFC16:1;
      vuint32_t NCFC15:1;
      vuint32_t NCFC14:1;
      vuint32_t NCFC13:1;
      vuint32_t NCFC12:1;
      vuint32_t NCFC11:1;
      vuint32_t NCFC10:1;
      vuint32_t NCFC9:1;
      vuint32_t NCFC8:1;
      vuint32_t NCFC7:1;
      vuint32_t NCFC6:1;
      vuint32_t NCFC5:1;
      vuint32_t NCFC4:1;
      vuint32_t NCFC3:1;
      vuint32_t NCFC2:1;
      vuint32_t NCFC1:1;
      vuint32_t NCFC0:1;
    } B;
  } NCF_CFG[3];

  uint8_t FCCU_reserved1[36];
  union {                              /* NCFS Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t NCFSC31:1;
      vuint32_t NCFSC30:1;
      vuint32_t NCFSC29:1;
      vuint32_t NCFSC28:1;
      vuint32_t NCFSC27:1;
      vuint32_t NCFSC26:1;
      vuint32_t NCFSC25:1;
      vuint32_t NCFSC24:1;
      vuint32_t NCFSC23:1;
      vuint32_t NCFSC22:1;
      vuint32_t NCFSC21:1;
      vuint32_t NCFSC20:1;
      vuint32_t NCFSC19:1;
      vuint32_t NCFSC18:1;
      vuint32_t NCFSC17:1;
      vuint32_t NCFSC16:1;
      vuint32_t NCFSC15:1;
      vuint32_t NCFSC14:1;
      vuint32_t NCFSC13:1;
      vuint32_t NCFSC12:1;
      vuint32_t NCFSC11:1;
      vuint32_t NCFSC10:1;
      vuint32_t NCFSC9:1;
      vuint32_t NCFSC8:1;
      vuint32_t NCFSC7:1;
      vuint32_t NCFSC6:1;
      vuint32_t NCFSC5:1;
      vuint32_t NCFSC4:1;
      vuint32_t NCFSC3:1;
      vuint32_t NCFSC2:1;
      vuint32_t NCFSC1:1;
      vuint32_t NCFSC0:1;
    } B;
  } NCFS_CFG[5];

  uint8_t FCCU_reserved2[32];
  union {                              /* NCF Status Register */
    vuint32_t R;
    struct {
      vuint32_t NCFS31:1;
      vuint32_t NCFS30:1;
      vuint32_t NCFS29:1;
      vuint32_t NCFS28:1;
      vuint32_t NCFS27:1;
      vuint32_t NCFS26:1;
      vuint32_t NCFS25:1;
      vuint32_t NCFS24:1;
      vuint32_t NCFS23:1;
      vuint32_t NCFS22:1;
      vuint32_t NCFS21:1;
      vuint32_t NCFS20:1;
      vuint32_t NCFS19:1;
      vuint32_t NCFS18:1;
      vuint32_t NCFS17:1;
      vuint32_t NCFS16:1;
      vuint32_t NCFS15:1;
      vuint32_t NCFS14:1;
      vuint32_t NCFS13:1;
      vuint32_t NCFS12:1;
      vuint32_t NCFS11:1;
      vuint32_t NCFS10:1;
      vuint32_t NCFS9:1;
      vuint32_t NCFS8:1;
      vuint32_t NCFS7:1;
      vuint32_t NCFS6:1;
      vuint32_t NCFS5:1;
      vuint32_t NCFS4:1;
      vuint32_t NCFS3:1;
      vuint32_t NCFS2:1;
      vuint32_t NCFS1:1;
      vuint32_t NCFS0:1;
    } B;
  } NCF_S[3];

  uint8_t FCCU_reserved3[4];
  union {                              /* NCF Key Register */
    vuint32_t R;
    struct {
      vuint32_t NCFK:32;
    } B;
  } NCFK;

  union {                              /* NCF Enable Register */
    vuint32_t R;
    struct {
      vuint32_t NCFE31:1;
      vuint32_t NCFE30:1;
      vuint32_t NCFE29:1;
      vuint32_t NCFE28:1;
      vuint32_t NCFE27:1;
      vuint32_t NCFE26:1;
      vuint32_t NCFE25:1;
      vuint32_t NCFE24:1;
      vuint32_t NCFE23:1;
      vuint32_t NCFE22:1;
      vuint32_t NCFE21:1;
      vuint32_t NCFE20:1;
      vuint32_t NCFE19:1;
      vuint32_t NCFE18:1;
      vuint32_t NCFE17:1;
      vuint32_t NCFE16:1;
      vuint32_t NCFE15:1;
      vuint32_t NCFE14:1;
      vuint32_t NCFE13:1;
      vuint32_t NCFE12:1;
      vuint32_t NCFE11:1;
      vuint32_t NCFE10:1;
      vuint32_t NCFE9:1;
      vuint32_t NCFE8:1;
      vuint32_t NCFE7:1;
      vuint32_t NCFE6:1;
      vuint32_t NCFE5:1;
      vuint32_t NCFE4:1;
      vuint32_t NCFE3:1;
      vuint32_t NCFE2:1;
      vuint32_t NCFE1:1;
      vuint32_t NCFE0:1;
    } B;
  } NCF_E[3];

  uint8_t FCCU_reserved4[4];
  union {                              /* NCF Time-out Enable Register */
    vuint32_t R;
    struct {
      vuint32_t NCFTOE31:1;
      vuint32_t NCFTOE30:1;
      vuint32_t NCFTOE29:1;
      vuint32_t NCFTOE28:1;
      vuint32_t NCFTOE27:1;
      vuint32_t NCFTOE26:1;
      vuint32_t NCFTOE25:1;
      vuint32_t NCFTOE24:1;
      vuint32_t NCFTOE23:1;
      vuint32_t NCFTOE22:1;
      vuint32_t NCFTOE21:1;
      vuint32_t NCFTOE20:1;
      vuint32_t NCFTOE19:1;
      vuint32_t NCFTOE18:1;
      vuint32_t NCFTOE17:1;
      vuint32_t NCFTOE16:1;
      vuint32_t NCFTOE15:1;
      vuint32_t NCFTOE14:1;
      vuint32_t NCFTOE13:1;
      vuint32_t NCFTOE12:1;
      vuint32_t NCFTOE11:1;
      vuint32_t NCFTOE10:1;
      vuint32_t NCFTOE9:1;
      vuint32_t NCFTOE8:1;
      vuint32_t NCFTOE7:1;
      vuint32_t NCFTOE6:1;
      vuint32_t NCFTOE5:1;
      vuint32_t NCFTOE4:1;
      vuint32_t NCFTOE3:1;
      vuint32_t NCFTOE2:1;
      vuint32_t NCFTOE1:1;
      vuint32_t NCFTOE0:1;
    } B;
  } NCF_TOE[3];

  uint8_t FCCU_reserved5[4];
  union {                              /* NCF Time-out Register */
    vuint32_t R;
    struct {
      vuint32_t TO:32;
    } B;
  } NCF_TO;

  union {                              /* CFG Timeout Register */
    vuint32_t R;
    struct {
      vuint32_t  :29;
      vuint32_t TO:3;
    } B;
  } CFG_TO;

  union {                              /* IO Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :26;
      vuint32_t EIN1:1;
      vuint32_t EIN0:1;
      vuint32_t  :2;
      vuint32_t EOUT1:1;
      vuint32_t EOUT0:1;
    } B;
  } EINOUT;

  union {                              /* Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :26;
      vuint32_t PhysicErrorPin:2;
      vuint32_t ESTAT:1;
      vuint32_t STATUS:3;
    } B;
  } STAT;

  union {                              /* NA Freeze Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t NAFS:8;
    } B;
  } N2AF_STATUS;

  union {                              /* AF Freeze Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :22;
      vuint32_t AF_SRC:2;
      vuint32_t AFFS:8;
    } B;
  } A2FF_STATUS;

  union {                              /* NF Freeze Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :22;
      vuint32_t NF_SRC:2;
      vuint32_t NFFS:8;
    } B;
  } N2FF_STATUS;

  union {                              /* FA Freeze Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :23;
      vuint32_t FAFS:9;
    } B;
  } F2A_STATUS;

  uint8_t FCCU_reserved6[8];
  union {                              /* NCF Fake Register */
    vuint32_t R;
    struct {
      vuint32_t  :25;
      vuint32_t FNCFC:7;
    } B;
  } NCFF;

  union {                              /* IRQ Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :27;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t NMI_STAT:1;
      vuint32_t ALRM_STAT:1;
      vuint32_t CFG_TO_STAT:1;
    } B;
  } IRQ_STAT;

  union {                              /* IRQ Enable Register */
    vuint32_t R;
    struct {
      vuint32_t  :28;
      vuint32_t  :1;
      vuint32_t  :2;
      vuint32_t CFG_TO_IEN:1;
    } B;
  } IRQ_EN;

  union {                              /* XTMR Register */
    vuint32_t R;
    struct {
      vuint32_t XTMR:32;
    } B;
  } XTMR;

  union {                              /* MCS Register */
    vuint32_t R;
    struct {
      vuint32_t VL3:1;
      vuint32_t FS3:1;
      vuint32_t  :2;
      vuint32_t MCS3:4;
      vuint32_t VL2:1;
      vuint32_t FS2:1;
      vuint32_t  :2;
      vuint32_t MCS2:4;
      vuint32_t VL1:1;
      vuint32_t FS1:1;
      vuint32_t  :2;
      vuint32_t MCS1:4;
      vuint32_t VL0:1;
      vuint32_t FS0:1;
      vuint32_t  :2;
      vuint32_t MCS0:4;
    } B;
  } MCS;

  union {                              /* Transient Lock Register */
    vuint32_t R;
    struct {
      vuint32_t  :23;
      vuint32_t TRANSKEY:9;
    } B;
  } TRANS_LOCK;

  union {                              /* Permanent Lock Register */
    vuint32_t R;
    struct {
      vuint32_t  :23;
      vuint32_t PERMNTKEY:9;
    } B;
  } PERMNT_LOCK;

  union {                              /* Delta T Register */
    vuint32_t R;
    struct {
      vuint32_t  :2;
      vuint32_t  :14;
      vuint32_t  :2;
      vuint32_t DELTA_T:14;
    } B;
  } DELTA_T;

  union {                              /* IRQ Alarm Enable Register */
    vuint32_t R;
    struct {
      vuint32_t IRQEN31:1;
      vuint32_t IRQEN30:1;
      vuint32_t IRQEN29:1;
      vuint32_t IRQEN28:1;
      vuint32_t IRQEN27:1;
      vuint32_t IRQEN26:1;
      vuint32_t IRQEN25:1;
      vuint32_t IRQEN24:1;
      vuint32_t IRQEN23:1;
      vuint32_t IRQEN22:1;
      vuint32_t IRQEN21:1;
      vuint32_t IRQEN20:1;
      vuint32_t IRQEN19:1;
      vuint32_t IRQEN18:1;
      vuint32_t IRQEN17:1;
      vuint32_t IRQEN16:1;
      vuint32_t IRQEN15:1;
      vuint32_t IRQEN14:1;
      vuint32_t IRQEN13:1;
      vuint32_t IRQEN12:1;
      vuint32_t IRQEN11:1;
      vuint32_t IRQEN10:1;
      vuint32_t IRQEN9:1;
      vuint32_t IRQEN8:1;
      vuint32_t IRQEN7:1;
      vuint32_t IRQEN6:1;
      vuint32_t IRQEN5:1;
      vuint32_t IRQEN4:1;
      vuint32_t IRQEN3:1;
      vuint32_t IRQEN2:1;
      vuint32_t IRQEN1:1;
      vuint32_t IRQEN0:1;
    } B;
  } IRQ_ALARM_EN[3];

  uint8_t FCCU_reserved7[4];
  union {                              /* NMI Enable Register */
    vuint32_t R;
    struct {
      vuint32_t NMIEN31:1;
      vuint32_t NMIEN30:1;
      vuint32_t NMIEN29:1;
      vuint32_t NMIEN28:1;
      vuint32_t NMIEN27:1;
      vuint32_t NMIEN26:1;
      vuint32_t NMIEN25:1;
      vuint32_t NMIEN24:1;
      vuint32_t NMIEN23:1;
      vuint32_t NMIEN22:1;
      vuint32_t NMIEN21:1;
      vuint32_t NMIEN20:1;
      vuint32_t NMIEN19:1;
      vuint32_t NMIEN18:1;
      vuint32_t NMIEN17:1;
      vuint32_t NMIEN16:1;
      vuint32_t NMIEN15:1;
      vuint32_t NMIEN14:1;
      vuint32_t NMIEN13:1;
      vuint32_t NMIEN12:1;
      vuint32_t NMIEN11:1;
      vuint32_t NMIEN10:1;
      vuint32_t NMIEN9:1;
      vuint32_t NMIEN8:1;
      vuint32_t NMIEN7:1;
      vuint32_t NMIEN6:1;
      vuint32_t NMIEN5:1;
      vuint32_t NMIEN4:1;
      vuint32_t NMIEN3:1;
      vuint32_t NMIEN2:1;
      vuint32_t NMIEN1:1;
      vuint32_t NMIEN0:1;
    } B;
  } NMI_EN[3];

  uint8_t FCCU_reserved8[4];
  union {                              /* EOUT Signaling Enable Register */
    vuint32_t R;
    struct {
      vuint32_t EOUTEN31:1;
      vuint32_t EOUTEN30:1;
      vuint32_t EOUTEN29:1;
      vuint32_t EOUTEN28:1;
      vuint32_t EOUTEN27:1;
      vuint32_t EOUTEN26:1;
      vuint32_t EOUTEN25:1;
      vuint32_t EOUTEN24:1;
      vuint32_t EOUTEN23:1;
      vuint32_t EOUTEN22:1;
      vuint32_t EOUTEN21:1;
      vuint32_t EOUTEN20:1;
      vuint32_t EOUTEN19:1;
      vuint32_t EOUTEN18:1;
      vuint32_t EOUTEN17:1;
      vuint32_t EOUTEN16:1;
      vuint32_t EOUTEN15:1;
      vuint32_t EOUTEN14:1;
      vuint32_t EOUTEN13:1;
      vuint32_t EOUTEN12:1;
      vuint32_t EOUTEN11:1;
      vuint32_t EOUTEN10:1;
      vuint32_t EOUTEN9:1;
      vuint32_t EOUTEN8:1;
      vuint32_t EOUTEN7:1;
      vuint32_t EOUTEN6:1;
      vuint32_t EOUTEN5:1;
      vuint32_t EOUTEN4:1;
      vuint32_t EOUTEN3:1;
      vuint32_t EOUTEN2:1;
      vuint32_t EOUTEN1:1;
      vuint32_t EOUTEN0:1;
    } B;
  } EOUT_SIG_EN[3];
};


/* ============================================================================
   =============================== Module: FR =================================
   ============================================================================ */

#include "ip_flexray.h"


/* ============================================================================
   =============================== Module: FlexPWM ============================
   ============================================================================ */

struct FLEXPWM_tag {
  struct {
    union {                            /* Submodule n Counter Register */
      vuint16_t R;
      struct {
        vuint16_t CNT:16;              /* Count */
      } B;
    } CNT;
    union {                            /* Submodule n Initial Count Register */
      vuint16_t R;
      struct {
        vuint16_t INIT:16;             /* Initial count */
      } B;
    } INIT;
    union {                            /* Submodule n Control 2 Register */
      vuint16_t R;
      struct {
        vuint16_t DBGEN:1;             /* Debug Enable */
        vuint16_t  :1;
        vuint16_t INDEP:1;             /* Independent or Complementary Pair Operation */
        vuint16_t PWM23_INIT:1;        /* PWM23 Initial Value */
        vuint16_t PWM45_INIT:1;        /* PWM45 Initial Value */
        vuint16_t PWMX_INIT:1;         /* PWMX Initial Value */
        vuint16_t INIT_SEL:2;          /* Initialization Control Select */
        vuint16_t FRCEN:1;             /* Force Initialization Enable */
        vuint16_t FORCE:1;             /* Force Initialization */
        vuint16_t FORCE_SEL:3;         /* Force Source Select */
        vuint16_t RELOAD_SEL:1;        /* Reload Source Select */
        vuint16_t CLK_SEL:2;           /* Clock Source Select */
      } B;
    } CTRL2;
    union {                            /* Submodule n Control 1 Register */
      vuint16_t R;
      struct {
        vuint16_t LDFQ:4;              /* Load Frequency */
        vuint16_t HALF:1;              /* Half Cycle Reload */
        vuint16_t FULL:1;              /* Full Cycle Reload */
        vuint16_t DT:2;                /* Deadtime */
        vuint16_t  :1;
        vuint16_t PRSC:3;              /* Prescaler */
        vuint16_t PHSSHFT:1;           /* Phase Shift Mode Enable */
        vuint16_t LDMOD:1;             /* Load Mode Select */
        vuint16_t  :1;
        vuint16_t DBLEN:1;             /* Double Switching Enable */
      } B;
    } CTRL;
    union {                            /* Submodule n Value Register */
      vuint16_t R;
      struct {
        vuint16_t VAL:16;             /* Value */
      } B;
    } VAL[6];
    uint8_t SUB_reserved0[4];
    union {                            /* Submodule n Output Control Register */
      vuint16_t R;
      struct {
        vuint16_t  :1;
        vuint16_t  :1;
        vuint16_t PWMX_IN:1;
        vuint16_t  :2;
        vuint16_t POLA:1;
        vuint16_t POLB:1;
        vuint16_t POLX:1;
        vuint16_t  :2;
        vuint16_t PWMAFS:2;            /* PWMA Fault State */
        vuint16_t PWMBFS:2;            /* PWMB Fault State */
        vuint16_t PWMXFS:2;            /* PWMX Fault State */
      } B;
    } OCTRL;
    union {                            /* Submodule n Status Register */
      vuint16_t R;
      struct {
        vuint16_t  :1;
        vuint16_t RUF:1;
        vuint16_t REF:1;
        vuint16_t RF:1;
        vuint16_t  :4;
        vuint16_t CFX1:1;
        vuint16_t CFX0:1;
        vuint16_t CMPF:6;
      } B;
    } STS;
    union {                            /* Submodule n Interrupt Enable Register */
      vuint16_t R;
      struct {
        vuint16_t  :2;
        vuint16_t REIE:1;
        vuint16_t RIE:1;
        vuint16_t  :4;
        vuint16_t CX1IE:1;
        vuint16_t CX0IE:1;
        vuint16_t CMPIE:6;
      } B;
    } INTEN;
    union {                            /* Submodule n DMA Enable Register */
      vuint16_t R;
      struct {
        vuint16_t  :6;
        vuint16_t VALDE:1;
        vuint16_t FAND:1;
        vuint16_t CAPTDE:2;
        vuint16_t  :4;
        vuint16_t CX1DE:1;
        vuint16_t CX0DE:1;
      } B;
    } DMAEN;
    union {                            /* Submodule n Output Trigger Control Register */
      vuint16_t R;
      struct {
        vuint16_t  :10;
        vuint16_t OUT_TRIG_EN:6;
      } B;
    } TCTRL;
    union {                            /* Submodule n Fault Disable Mapping Register */
      vuint16_t R;
      struct {
        vuint16_t  :4;
        vuint16_t DISX:4;
        vuint16_t DISB:4;
        vuint16_t DISA:4;
      } B;
    } DISMAP;
    union {                            /* Submodule n Deadtime Count Register 0 */
      vuint16_t R;
      struct {
        vuint16_t  :5;
        vuint16_t DTCNT0:11;
      } B;
    } DTCNT0;
    union {                            /* Submodule n Deadtime Count Register 1 */
      vuint16_t R;
      struct {
        vuint16_t  :5;
        vuint16_t DTCNT1:11;
      } B;
    } DTCNT1;
    uint8_t SUB_reserved1[8];
    union {                            /* Submodule n Capture Control X Register */
      vuint16_t R;
      struct {
        vuint16_t CX1CNT:3;
        vuint16_t CX0CNT:3;
        vuint16_t CFXWM:2;             /* Capture X FIFOs Watermark */
        vuint16_t EDGCNTX_EN:1;
        vuint16_t INPSELX:1;
        vuint16_t EDGX1:2;
        vuint16_t EDGX0:2;
        vuint16_t ONESHOTX:1;
        vuint16_t ARMX:1;
      } B;
    } CAPTCTRLX;
    union {                            /* Submodule n Capture Compare X Register */
      vuint16_t R;
      struct {
        vuint16_t EDGCNTX:8;
        vuint16_t EDGCMPX:8;
      } B;
    } CAPTCMPX;
    union {                            /* Submodule n Capture Value 0 Register */
      vuint16_t R;
      struct {
        vuint16_t CAPTVAL0:16;
      } B;
    } CVAL0;
    union {                            /* Submodule n Capture Value 0 Cycle Register */
      vuint16_t R;
      struct {
        vuint16_t  :13;
        vuint16_t CVAL0CYC:3;          /* CVAL0 Cycle */
      } B;
    } CVAL0CYC;
    union {                            /* Submodule n Capture Value 1 Register */
      vuint16_t R;
      struct {
        vuint16_t CAPTVAL1:16;
      } B;
    } CVAL1;
    union {                            /* Submodule n Capture Value 1 Cycle Register */
      vuint16_t R;
      struct {
        vuint16_t  :13;
        vuint16_t CVAL1CYC:3;          /* CVAL1 Cycle */
      } B;
    } CVAL1CYC;
    uint8_t SUB_reserved2[20];
  } SUB[4];

  union {                              /* Output Enable Register */
    vuint16_t R;
    struct {
      vuint16_t  :4;
      vuint16_t PWMA_EN:4;
      vuint16_t PWMB_EN:4;
      vuint16_t PWMX_EN:4;
    } B;
  } OUTEN;

  union {                              /* Mask Register */
    vuint16_t R;
    struct {
      vuint16_t UPDATE_MASK:4;         /* Update Mask */
      vuint16_t MASKA:4;
      vuint16_t MASKB:4;
      vuint16_t MASKX:4;
    } B;
  } MASK;

  union {                              /* Software Controlled Output Register */
    vuint16_t R;
    struct {
      vuint16_t  :8;
      vuint16_t OUT23_3:1;
      vuint16_t OUT45_3:1;
      vuint16_t OUT23_2:1;
      vuint16_t OUT45_2:1;
      vuint16_t OUT23_1:1;
      vuint16_t OUT45_1:1;
      vuint16_t OUT23_0:1;
      vuint16_t OUT45_0:1;
    } B;
  } SWCOUT;

  union {                              /* Deadtime Source Select Register */
    vuint16_t R;
    struct {
      vuint16_t SEL23_3:2;
      vuint16_t SEL45_3:2;
      vuint16_t SEL23_2:2;
      vuint16_t SEL45_2:2;
      vuint16_t SEL23_1:2;
      vuint16_t SEL45_1:2;
      vuint16_t SEL23_0:2;
      vuint16_t SEL45_0:2;
    } B;
  } DTSRCSEL;

  union {                              /* Master Control Register */
    vuint16_t R;
    struct {
      vuint16_t IPOL:4;                /* Current Polarity */
      vuint16_t RUN:4;                 /* Run */
      vuint16_t CLDOK:4;               /* Clear Load Okay */
      vuint16_t LDOK:4;                /* Load Okay */
    } B;
  } MCTRL;

  uint8_t FlexPWM_reserved0[2];
  union {                              /* Fault Control Register */
    vuint16_t R;
    struct {
      vuint16_t FLVL:4;
      vuint16_t FAUTO:4;
      vuint16_t FSAFE:4;
      vuint16_t FIE:4;
    } B;
  } FCTRL;

  union {                              /* Fault Status Register */
    vuint16_t R;
    struct {
      vuint16_t  :3;
      vuint16_t FTEST:1;
      vuint16_t FFPIN:4;
      vuint16_t FFULL:4;
      vuint16_t FFLAG:4;
    } B;
  } FSTS;

  union {                              /* Fault Filter Register */
    vuint16_t R;
    struct {
      vuint16_t GSTR:1;
      vuint16_t  :4;
      vuint16_t FILT_CNT:3;
      vuint16_t FILT_PER:8;
    } B;
  } FFILT;
};


/* ============================================================================
   =============================== Module: INTC ===============================
   ============================================================================ */

struct INTC_tag {
  union {                              /* INTC Block Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :19;
      vuint32_t HVEN_PRC3:1;
      vuint32_t  :3;
      vuint32_t HVEN_PRC2:1;
      vuint32_t  :3;
      vuint32_t HVEN_PRC1:1;
      vuint32_t  :3;
      vuint32_t HVEN_PRC0:1;
    } B;
  } MCR;

  uint8_t INTC_reserved0[12];
  union {                              /* INTC Current Priority Register for Processor n */
    vuint32_t R;
    struct {
      vuint32_t  :27;
      vuint32_t PRI:5;
    } B;
  } CPR[1];

  uint8_t INTC_reserved1[12];
  union {                              /* INTC Interrupt Acknowledge Register for Processor n */
    vuint32_t R;
    struct {
      vuint32_t VTBA:20;
      vuint32_t INTVEC:10;
      vuint32_t  :2;
    } B;
  } IACKR[1];

  uint8_t INTC_reserved2[12];
  union {                              /* INTC End Of Interrupt Register for Processor n */
    vuint32_t R;
    struct {
      vuint32_t EOI:32;
    } B;
  } EOIR[1];

  uint8_t INTC_reserved3[12];
  union {                              /* INTC Software Set/Clear Interrupt Register */
    vuint8_t R;
    struct {
      vuint8_t  :6;
      vuint8_t SET:1;
      vuint8_t CLR:1;
    } B;
  } SSCIR[16];

  uint8_t INTC_reserved4[16];
  union {                              /* INTC Priority Select Register */
    vuint16_t R;
    struct {
      vuint16_t PRC_SEL:4;
      vuint16_t  :3;
      vuint16_t SWTN:1;
      vuint16_t  :3;
      vuint16_t PRI:5;
    } B;
  } PSR[1024];

  uint8_t INTC_reserved5[1952];
  union {                              /* INTC Monitor Mode Register */
    vuint32_t R;
    struct {
      vuint32_t  :30;
      vuint32_t MM:2;
    } B;
  } MMRC[1];

  union {                              /* INTC HIPRI Register */
    vuint32_t R;
    struct {
      vuint32_t  :22;
      vuint32_t IRQ:10;
    } B;
  } HIPRIC0[4];

  union {                              /* INTC LAT Register */
    vuint32_t R;
    struct {
      vuint32_t  :8;
      vuint32_t LAT:24;
    } B;
  } LATC0[4];

  union {                              /* INTC Timer Register */
    vuint32_t R;
    struct {
      vuint32_t  :8;
      vuint32_t TIMER:24;
    } B;
  } TIMERC0[4];
};


/* ============================================================================
   =============================== Module: IRCOSC =============================
   ============================================================================ */

struct IRCOSC_tag {
  union {                              /* IRCOSC Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t  :1;
      vuint32_t  :3;
      vuint32_t USER_TRIM:5;
      vuint32_t  :3;
      vuint32_t  :5;
      vuint32_t  :2;
      vuint32_t  :1;
      vuint32_t  :5;
    } B;
  } CTL;
};


/* ============================================================================
   =============================== Module: LFAST ==============================
   ============================================================================ */

struct LFAST_tag {
  union {                              /* LFAST Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t MSEN:1;
      vuint32_t  :6;
      vuint32_t IPGDBG:1;
      vuint32_t  :7;
      vuint32_t LSSEL:1;
      vuint32_t DRFEN:1;
      vuint32_t RXEN:1;
      vuint32_t TXEN:1;
      vuint32_t  :8;
      vuint32_t TXARBD:1;
      vuint32_t CTSEN:1;
      vuint32_t  :1;
      vuint32_t DRFRST:1;
      vuint32_t DATAEN:1;
    } B;
  } MCR;

  union {                              /* LFAST Speed Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :15;
      vuint32_t DRMD:1;
      vuint32_t  :7;
      vuint32_t RDR:1;
      vuint32_t  :7;
      vuint32_t TDR:1;
    } B;
  } SCR;

  union {                              /* LFAST Correlator Control Register */
    vuint32_t R;
    struct {
      vuint32_t SMPSEL:8;
      vuint32_t  :6;
      vuint32_t  :2;
      vuint32_t  :12;
      vuint32_t CORRTH:3;
      vuint32_t PHSSEL:1;
    } B;
  } COCR;

  union {                              /* LFAST Test Mode Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :6;
      vuint32_t CLKTST:1;
      vuint32_t LPON:1;
      vuint32_t  :5;
      vuint32_t LPMOD:3;
      vuint32_t LPFRMTH:16;
    } B;
  } TMCR;

  union {                              /* LFAST Auto Loopback Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :15;
      vuint32_t LPCNTEN:1;
      vuint32_t LPFMCNT:16;
    } B;
  } ALCR;

  union {                              /* LFAST Rate Change Delay Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t DRCNT:4;
      vuint32_t  :16;
    } B;
  } RCDCR;

  union {                              /* LFAST Wakeup Delay Control Register */
    vuint32_t R;
    struct {
      vuint32_t HSCNT:8;
      vuint32_t  :4;
      vuint32_t LSCNT:4;
      vuint32_t HWKCNT:8;
      vuint32_t  :4;
      vuint32_t LWKCNT:4;
    } B;
  } SLCR;

  union {                              /* LFAST ICLC Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :14;
      vuint32_t ICLCSEQ:1;
      vuint32_t SNDICLC:1;
      vuint32_t  :8;
      vuint32_t ICLCPLD:8;
    } B;
  } ICR;

  union {                              /* LFAST Ping Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :15;
      vuint32_t PNGREQ:1;
      vuint32_t PNGAUTO:1;
      vuint32_t  :7;
      vuint32_t PNGPYLD:8;
    } B;
  } PICR;

  uint8_t LFAST_reserved0[8];
  union {                              /* LFAST Rx FIFO CTS Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :10;
      vuint32_t RCTSMX:6;
      vuint32_t  :10;
      vuint32_t RCTSMN:6;
    } B;
  } RFCR;

  union {                              /* LFAST Tx Interrupt Enable Register */
    vuint32_t R;
    struct {
      vuint32_t  :14;
      vuint32_t TXIIE:1;
      vuint32_t TXOVIE:1;
      vuint32_t  :11;
      vuint32_t TXPNGIE:1;
      vuint32_t  :1;
      vuint32_t TXUNSIE:1;
      vuint32_t TXICLCIE:1;
      vuint32_t TXDTIE:1;
    } B;
  } TIER;

  union {                              /* LFAST Rx Interrupt Enable Register */
    vuint32_t R;
    struct {
      vuint32_t  :8;
      vuint32_t RXUOIE:1;
      vuint32_t RXMNIE:1;
      vuint32_t RXMXIE:1;
      vuint32_t RXUFIE:1;
      vuint32_t RXOFIE:1;
      vuint32_t RXSZIE:1;
      vuint32_t RXICIE:1;
      vuint32_t RXLCEIE:1;
      vuint32_t  :12;
      vuint32_t RXCTSIE:1;
      vuint32_t RXDIE:1;
      vuint32_t RXUNSIE:1;
      vuint32_t  :1;
    } B;
  } RIER;

  union {                              /* LFAST Rx ICLC Interrupt Enable Register */
    vuint32_t R;
    struct {
      vuint32_t  :18;
      vuint32_t ICPFIE:1;
      vuint32_t ICPSIE:1;
      vuint32_t ICPRIE:1;
      vuint32_t ICTOIE:1;
      vuint32_t ICLPIE:1;
      vuint32_t ICCTIE:1;
      vuint32_t ICTDIE:1;
      vuint32_t ICTEIE:1;
      vuint32_t ICRFIE:1;
      vuint32_t ICRSIE:1;
      vuint32_t ICTFIE:1;
      vuint32_t ICTSIE:1;
      vuint32_t ICPOFIE:1;
      vuint32_t ICPONIE:1;
    } B;
  } RIIER;

  union {                              /* LFAST PLL Control Register */
    vuint32_t R;
    struct {
      vuint32_t IPTMOD:3;
      vuint32_t  :11;
      vuint32_t SWPOFF:1;
      vuint32_t SWPON:1;
      vuint32_t REFINV:1;
      vuint32_t LPCFG:2;
      vuint32_t  :2;
      vuint32_t PLCKCW:2;
      vuint32_t FDIVEN:1;
      vuint32_t FBDIV:6;
      vuint32_t PREDIV:2;
    } B;
  } PLLCR;

  union {                              /* LFAST LVDS Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :8;
      vuint32_t SWWKLD:1;
      vuint32_t SWSLPLD:1;
      vuint32_t SWWKLR:1;
      vuint32_t SWSLPLR:1;
      vuint32_t SWOFFLD:1;
      vuint32_t SWONLD:1;
      vuint32_t SWOFFLR:1;
      vuint32_t SWONLR:1;
      vuint32_t LVRXOFF:1;
      vuint32_t LVTXOE:1;
      vuint32_t TXCMUX:1;
      vuint32_t LVRFEN:1;
      vuint32_t LVLPEN:1;
      vuint32_t  :5;
      vuint32_t LVRXOP:3;
      vuint32_t LVTXOP:1;
      vuint32_t LVCKSS:1;
      vuint32_t LVCKP:1;
    } B;
  } LCR;

  union {                              /* LFAST Unsolicited Tx Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :15;
      vuint32_t USNDRQ:1;
      vuint32_t  :9;
      vuint32_t UNSHDR:7;
    } B;
  } UNSTCR;

  union {                              /* LFAST Unsolicited Tx Data Registers */
    vuint32_t R;
    struct {
      vuint32_t UNTXD:32;
    } B;
  } UNSTDR[9];

  uint8_t LFAST_reserved1[20];
  union {                              /* LFAST Global Status Register */
    vuint32_t R;
    struct {
      vuint32_t DUALMD:1;
      vuint32_t  :12;
      vuint32_t LRMD:1;
      vuint32_t LDSM:1;
      vuint32_t DRSM:1;
      vuint32_t  :11;
      vuint32_t LPTXDN:1;
      vuint32_t LPFPDV:1;
      vuint32_t LPCPDV:1;
      vuint32_t LPCHDV:1;
      vuint32_t LPCSDV:1;
    } B;
  } GSR;

  union {                              /* LFAST Ping Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t RXPNGD:8;
    } B;
  } PISR;

  uint8_t LFAST_reserved2[12];
  union {                              /* LFAST Data Frame Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :2;
      vuint32_t RXDCNT:6;
      vuint32_t  :5;
      vuint32_t RXFCNT:3;
      vuint32_t  :2;
      vuint32_t TXDCNT:6;
      vuint32_t  :5;
      vuint32_t TXFCNT:3;
    } B;
  } DFSR;

  union {                              /* LFAST Tx Interrupt Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :14;
      vuint32_t TXIEF:1;
      vuint32_t TXOVF:1;
      vuint32_t  :11;
      vuint32_t TXPNGF:1;
      vuint32_t  :1;
      vuint32_t TXUNSF:1;
      vuint32_t TXICLCF:1;
      vuint32_t TXDTF:1;
    } B;
  } TISR;

  union {                              /* LFAST Rx Interrupt Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :8;
      vuint32_t RXUOF:1;
      vuint32_t RXMNF:1;
      vuint32_t RXMXF:1;
      vuint32_t RXUFF:1;
      vuint32_t RXOFF:1;
      vuint32_t RXSZF:1;
      vuint32_t RXICF:1;
      vuint32_t RXLCEF:1;
      vuint32_t  :12;
      vuint32_t RXCTSF:1;
      vuint32_t RXDF:1;
      vuint32_t RXUNSF:1;
      vuint32_t  :1;
    } B;
  } RISR;

  union {                              /* LFAST Rx ICLC Interrupt Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :18;
      vuint32_t ICPFF:1;
      vuint32_t ICPSF:1;
      vuint32_t ICPRF:1;
      vuint32_t ICTOF:1;
      vuint32_t ICLPF:1;
      vuint32_t ICCTF:1;
      vuint32_t ICTDF:1;
      vuint32_t ICTEF:1;
      vuint32_t ICRFF:1;
      vuint32_t ICRSF:1;
      vuint32_t ICTFF:1;
      vuint32_t ICTSF:1;
      vuint32_t ICPOFF:1;
      vuint32_t ICPONF:1;
    } B;
  } RIISR;

  union {                              /* LFAST PLL and LVDS Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :14;
      vuint32_t PLLDIS:1;
      vuint32_t PLDCR:1;
      vuint32_t  :12;
      vuint32_t LRSLPS:1;
      vuint32_t LDSLPS:1;
      vuint32_t LDPDS:1;
      vuint32_t LRPDS:1;
    } B;
  } PLLLSR;

  union {                              /* LFAST Unsolicited Rx Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :23;
      vuint32_t URXDV:1;
      vuint32_t  :5;
      vuint32_t URPCNT:3;
    } B;
  } UNSRSR;

  union {                              /* LFAST Unsolicited Rx Data Register */
    vuint32_t R;
    struct {
      vuint32_t UNRXD:32;
    } B;
  } UNSRDR[9];
};


/* ============================================================================
   =============================== Module: LINFlexD ===========================
   ============================================================================ */

struct LINFLEX_tag {
  union {                              /* LIN Control Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t CCD:1;
      vuint32_t CFD:1;
      vuint32_t LASE:1;
      vuint32_t AWUM:1;
      vuint32_t MBL:4;
      vuint32_t BF:1;
      vuint32_t SLFM :1; // added for compatibility reasons, not part of 5744
      vuint32_t LBKM:1;
      vuint32_t MME:1;
      vuint32_t SBDT:1;
      vuint32_t RBLM:1;
      vuint32_t SLEEP:1;
      vuint32_t INIT:1;
    } B;
  } LINCR1;

  union {                              /* LIN Interrupt enable register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t SZIE:1;
      vuint32_t OCIE:1;
      vuint32_t BEIE:1;
      vuint32_t CEIE:1;
      vuint32_t HEIE:1;
      vuint32_t  :2;
      vuint32_t FEIE:1;
      vuint32_t BOIE:1;
      vuint32_t LSIE:1;
      vuint32_t WUIE:1;
      vuint32_t DBFIE:1;
      vuint32_t DBEIETOIE:1;
      vuint32_t DRIE:1;
      vuint32_t DTIE:1;
      vuint32_t HRIE:1;
    } B;
  } LINIER;

  union {                              /* LIN Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t  :1;
      vuint32_t RDC:3;
      vuint32_t LINS:4;
      vuint32_t  :2;
      vuint32_t RMB:1;
      vuint32_t DRBNE:1;
      vuint32_t /* RXbusy */RBSY:1;
      vuint32_t RDI:1;
      vuint32_t WUF:1;
      vuint32_t DBFF:1;
      vuint32_t DBEF:1;
      vuint32_t DRF:1;
      vuint32_t DTF:1;
      vuint32_t HRF:1;
    } B;
  } LINSR;

  union {                              /* LIN Error Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t SZF:1;
      vuint32_t OCF:1;
      vuint32_t BEF:1;
      vuint32_t CEF:1;
      vuint32_t SFEF:1;
      vuint32_t /* SDEF */BDEF:1;
      vuint32_t IDPEF:1;
      vuint32_t FEF:1;
      vuint32_t BOF:1;
      vuint32_t  :6;
      vuint32_t NF:1;
    } B;
  } LINESR;

  union {                              /* UART Mode Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t TDFLTFC:3;
      vuint32_t RDFLRFC:3;
      vuint32_t RFBM:1;
      vuint32_t TFBM:1;
      vuint32_t WL1:1;
      vuint32_t PC1:1;
      vuint32_t RxEn:1;
      vuint32_t TxEn:1;
      vuint32_t PC0:1;
      vuint32_t PCE:1;
      vuint32_t WL0:1;
      vuint32_t UART:1;
    } B;
  } UARTCR;

  union {                              /* UART Mode Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t SZF:1;
      vuint32_t OCF:1;
      vuint32_t PE:4;
      vuint32_t RMB:1;
      vuint32_t FEF:1;
      vuint32_t BOF:1;
      vuint32_t RDI:1;
      vuint32_t WUF:1;
      vuint32_t RFNE:1;
      vuint32_t TO:1;
      vuint32_t DRFRFE:1;
      vuint32_t DTFTFF:1;
      vuint32_t NF:1;
    } B;
  } UARTSR;

  union {                              /* LIN Time-Out Control Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :21;
      vuint32_t /* MODE */LTOM:1;
      vuint32_t IOT:1;
      vuint32_t TOCE:1;
      vuint32_t CNT:8;
    } B;
  } LINTCSR;

  union {                              /* LIN Output Compare Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t OC2:8;
      vuint32_t OC1:8;
    } B;
  } LINOCR;

  union {                              /* LIN Time-Out Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :20;
      vuint32_t RTO:4;
      vuint32_t  :1;
      vuint32_t HTO:7;
    } B;
  } LINTOCR;

  union {                              /* LIN Fractional Baud Rate Register */
    vuint32_t R;
    struct {
      vuint32_t  :28;
      vuint32_t DIV_F:4;               /* Fractional bits of LFDIV */
    } B;
  } LINFBRR;

  union {                              /* LIN Integer Baud Rate Register */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t DIV_M:20;              /* LFDIV mantissa */
    } B;
  } LINIBRR;

  union {                              /* LIN Checksum Field Register */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t CF:8;
    } B;
  } LINCFR;

  union {                              /* LIN Control Register 2 */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t TBDE:1;
      vuint32_t IOBE:1;
      vuint32_t IOPE:1;
      vuint32_t WURQ:1;
      vuint32_t DDRQ:1;
      vuint32_t DTRQ:1;
      vuint32_t ABRQ:1;
      vuint32_t HTRQ:1;
      vuint32_t  :8;
    } B;
  } LINCR2;

  union {                              /* Buffer Identifier Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t DFL:6;
      vuint32_t DIR:1;
      vuint32_t CCS:1;
      vuint32_t  :2;
      vuint32_t ID:6;
    } B;
  } BIDR;

  union {                              /* Buffer Data Register Least Significant */
    vuint32_t R;
    struct {
      vuint32_t DATA3:8;
      vuint32_t DATA2:8;
      vuint32_t DATA1:8;
      vuint32_t DATA0:8;
    } B;
  } BDRL;

  union {                              /* Buffer Data Register Most Significant */
    vuint32_t R;
    struct {
      vuint32_t DATA7:8;
      vuint32_t DATA6:8;
      vuint32_t DATA5:8;
      vuint32_t DATA4:8;
    } B;
  } BDRM;

  union {                              /* Identifier Filter Enable Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t FACT:16;
    } B;
  } IFER;

  union {                              /* Identifier Filter Match Index */
    vuint32_t R;
    struct {
      vuint32_t  :27;
      vuint32_t IFMI:5;
    } B;
  } IFMI;

  union {                              /* Identifier Filter Mode Register */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t IFM:8;
    } B;
  } IFMR;

  union {                              /* Identifier Filter Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t DFL:6;                 /* Data Field Length */
      vuint32_t DIR:1;                 /* Direction */
      vuint32_t CCS:1;                 /* Classic Checksum */
      vuint32_t  :2;
      vuint32_t ID:6;                  /* Identifier */
    } B;
  } IFCR[16];

  union {                              /* Global Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :26;
      vuint32_t TDFBM:1;
      vuint32_t RDFBM:1;
      vuint32_t TDLIS:1;
      vuint32_t RDLIS:1;
      vuint32_t STOP:1;
      vuint32_t SR:1;
    } B;
  } GCR;

  union {                              /* UART Preset Timeout Register */
    vuint32_t R;
    struct {
      vuint32_t  :20;
      vuint32_t PTO:12;
    } B;
  } UARTPTO;

  union {                              /* UART Current Timeout Register */
    vuint32_t R;
    struct {
      vuint32_t  :20;
      vuint32_t CTO:12;
    } B;
  } UARTCTO;

  union {                              /* DMA Tx Enable Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t DTE:16;
    } B;
  } DMATXE;

  union {                              /* DMA Rx Enable Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t DRE:16;
    } B;
  } DMARXE;
};


/* ============================================================================
   =============================== Module: MC_CGM =============================
   ============================================================================ */

struct MC_CGM_tag {
  uint8_t MC_CGM_reserved0[1792];
  union {                              /* PCS Switch Duration Register */
    vuint8_t R;
    struct {
      vuint8_t SDUR:8;
    } B;
  } PCS_SDUR;

  uint8_t MC_CGM_reserved1[3];
  union {                              /* PCS Divider End Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t DIVE:20;
    } B;
  } PCS_DIVE1;

  union {                              /* PCS Divider Start Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t DIVS:20;
    } B;
  } PCS_DIVS1;

  union {                              /* PCS Divider Change Register 1 */
    vuint32_t R;
    struct {
      vuint32_t INIT:16;
      vuint32_t  :8;
      vuint32_t RATE:8;
    } B;
  } PCS_DIVC1;

  union {                              /* PCS Divider End Register 2 */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t DIVE:20;
    } B;
  } PCS_DIVE2;

  union {                              /* PCS Divider Start Register 2 */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t DIVS:20;
    } B;
  } PCS_DIVS2;

  union {                              /* PCS Divider Change Register 2 */
    vuint32_t R;
    struct {
      vuint32_t INIT:16;
      vuint32_t  :8;
      vuint32_t RATE:8;
    } B;
  } PCS_DIVC2;

  uint8_t MC_CGM_reserved2[12];
  union {                              /* PCS Divider End Register 4 */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t DIVE:20;
    } B;
  } PCS_DIVE4;

  union {                              /* PCS Divider Start Register 4 */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t DIVS:20;
    } B;
  } PCS_DIVS4;

  union {                              /* PCS Divider Change Register 4 */
    vuint32_t R;
    struct {
      vuint32_t INIT:16;
      vuint32_t  :8;
      vuint32_t RATE:8;
    } B;
  } PCS_DIVC4;

  uint8_t MC_CGM_reserved3[176];
  union {                              /* System Clock Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t SELSTAT:4;
      vuint32_t  :4;
      vuint32_t SWTRG:3;
      vuint32_t SWIP:1;
      vuint32_t  :16;
    } B;
  } SC_SS;

  union {                              /* System Clock Divider 0 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :9;
      vuint32_t DIV:6;
      vuint32_t  :16;
    } B;
  } SC_DC0;

  uint8_t MC_CGM_reserved4[20];
  union {                              /* Auxiliary Clock 0 Select Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :6;
      vuint32_t SELCTL:2;
      vuint32_t  :24;
    } B;
  } AC0_SC;

  union {                              /* Auxiliary Clock 0 Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :6;
      vuint32_t SELSTAT:2;
      vuint32_t  :24;
    } B;
  } AC0_SS;

  union {                              /* Auxiliary Clock 0 Divider 0 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :11;
      vuint32_t DIV:4;
      vuint32_t  :16;
    } B;
  } AC0_DC0;

  union {                              /* Auxiliary Clock 0 Divider 1 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :10;
      vuint32_t DIV:5;
      vuint32_t  :16;
    } B;
  } AC0_DC1;

  union {                              /* Auxiliary Clock 0 Divider 2 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :10;
      vuint32_t DIV:5;
      vuint32_t  :16;
    } B;
  } AC0_DC2;

  uint8_t MC_CGM_reserved5[20];
  union {                              /* Auxiliary Clock 1 Divider 0 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :10;
      vuint32_t DIV:5;
      vuint32_t  :16;
    } B;
  } AC1_DC0;

  union {                              /* Auxiliary Clock 1 Divider 1 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :9;
      vuint32_t DIV:6;
      vuint32_t  :16;
    } B;
  } AC1_DC1;

  uint8_t MC_CGM_reserved6[24];
  union {                              /* Auxiliary Clock 2 Divider 0 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :11;
      vuint32_t DIV:4;
      vuint32_t  :16;
    } B;
  } AC2_DC0;

  uint8_t MC_CGM_reserved7[20];
  union {                              /* Auxiliary Clock 3 Select Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SELCTL:1;
      vuint32_t  :24;
    } B;
  } AC3_SC;

  union {                              /* Auxiliary Clock 3 Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SELSTAT:1;
      vuint32_t  :24;
    } B;
  } AC3_SS;

  uint8_t MC_CGM_reserved8[24];
  union {                              /* Auxiliary Clock 4 Select Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :6;
      vuint32_t SELCTL:2;
      vuint32_t  :24;
    } B;
  } AC4_SC;

  union {                              /* Auxiliary Clock 4 Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :6;
      vuint32_t SELSTAT:2;
      vuint32_t  :24;
    } B;
  } AC4_SS;

  uint8_t MC_CGM_reserved9[24];
  union {                              /* Auxiliary Clock 5 Select Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :5;
      vuint32_t SELCTL:3;
      vuint32_t  :24;
    } B;
  } AC5_SC;

  union {                              /* Auxiliary Clock 5 Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :5;
      vuint32_t SELSTAT:3;
      vuint32_t  :24;
    } B;
  } AC5_SS;

  union {                              /* Auxiliary Clock 5 Divider 0 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :10;
      vuint32_t DIV:5;
      vuint32_t  :16;
    } B;
  } AC5_DC0;

  uint8_t MC_CGM_reserved10[20];
  union {                              /* Auxiliary Clock 6 Select Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :5;
      vuint32_t SELCTL:3;
      vuint32_t  :24;
    } B;
  } AC6_SC;

  union {                              /* Auxiliary Clock 6 Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :5;
      vuint32_t SELSTAT:3;
      vuint32_t  :24;
    } B;
  } AC6_SS;

  union {                              /* Auxiliary Clock 6 Divider 0 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :8;
      vuint32_t DIV:7;
      vuint32_t  :16;
    } B;
  } AC6_DC0;

  uint8_t MC_CGM_reserved11[116];
  union {                              /* Auxiliary Clock 10 Select Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :5;
      vuint32_t SELCTL:3;
      vuint32_t  :24;
    } B;
  } AC10_SC;

  union {                              /* Auxiliary Clock 10 Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :5;
      vuint32_t SELSTAT:3;
      vuint32_t  :24;
    } B;
  } AC10_SS;

  union {                              /* Auxiliary Clock 10 Divider 0 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :11;
      vuint32_t DIV:4;
      vuint32_t  :16;
    } B;
  } AC10_DC0;

  uint8_t MC_CGM_reserved12[20];
  union {                              /* Auxiliary Clock 11 Select Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :5;
      vuint32_t SELCTL:3;
      vuint32_t  :24;
    } B;
  } AC11_SC;

  union {                              /* Auxiliary Clock 11 Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :5;
      vuint32_t SELSTAT:3;
      vuint32_t  :24;
    } B;
  } AC11_SS;

  union {                              /* Auxiliary Clock 11 Divider 0 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :11;
      vuint32_t DIV:4;
      vuint32_t  :16;
    } B;
  } AC11_DC0;
};


/* ============================================================================
   =============================== Module: MC_ME ==============================
   ============================================================================ */

struct MC_ME_tag {
  union {                              /* Global Status Register */
    vuint32_t R;
    struct {
      vuint32_t S_CURRENTMODE:4;
      vuint32_t S_MTRANS:1;
      vuint32_t  :1;
      vuint32_t  :2;
      vuint32_t S_PDO:1;
      vuint32_t  :2;
      vuint32_t S_MVR:1;
      vuint32_t  :2;
      vuint32_t S_FLA:2;
      vuint32_t  :8;
      vuint32_t S_PLL1:1;
      vuint32_t S_PLL0:1;
      vuint32_t S_XOSC:1;
      vuint32_t S_IRC:1;
      vuint32_t S_SYSCLK:4;
    } B;
  } GS;

  union {                              /* Mode Control Register */
    vuint32_t R;
    struct {
      vuint32_t TARGET_MODE:4;
      vuint32_t  :12;
      vuint32_t KEY:16;
    } B;
  } MCTL;

  union {                              /* Mode Enable Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t RESET_DEST:1;
      vuint32_t  :4;
      vuint32_t STOP0:1;
      vuint32_t  :1;
      vuint32_t HALT0:1;
      vuint32_t RUN3:1;
      vuint32_t RUN2:1;
      vuint32_t RUN1:1;
      vuint32_t RUN0:1;
      vuint32_t DRUN:1;
      vuint32_t SAFE:1;
      vuint32_t TEST:1;
      vuint32_t RESET_FUNC:1;
    } B;
  } ME;

  union {                              /* Interrupt Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :26;
      vuint32_t I_ICONF_CC:1;
      vuint32_t I_ICONF_CU:1;
      vuint32_t I_ICONF:1;
      vuint32_t I_IMODE:1;
      vuint32_t I_SAFE:1;
      vuint32_t I_MTC:1;
    } B;
  } IS;

  union {                              /* Interrupt Mask Register */
    vuint32_t R;
    struct {
      vuint32_t  :26;
      vuint32_t M_ICONF_CC:1;
      vuint32_t M_ICONF_CU:1;
      vuint32_t M_ICONF:1;
      vuint32_t M_IMODE:1;
      vuint32_t M_SAFE:1;
      vuint32_t M_MTC:1;
    } B;
  } IM;

  union {                              /* Invalid Mode Transition Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :26;
      vuint32_t S_MRIG:1;
      vuint32_t S_MTI:1;
      vuint32_t S_MRI:1;
      vuint32_t S_DMA:1;
      vuint32_t S_NMA:1;
      vuint32_t S_SEA:1;
    } B;
  } IMTS;

  union {                              /* Debug Mode Transition Status Register */
    vuint32_t R;
    struct {
      vuint32_t PREVIOUS_MODE:4;
      vuint32_t  :4;
      vuint32_t MPH_BUSY:1;
      vuint32_t  :2;
      vuint32_t PMC_PROG:1;
      vuint32_t DBG_MODE:1;
      vuint32_t CCKL_PROG:1;
      vuint32_t PCS_PROG:1;            /* Progressive System Clock Switching in Progress */
      vuint32_t SMR:1;
      vuint32_t CDP_PRPH_0_255:1;      /* Clock Disable Process Pending status for Peripherals 0 to 255 */
      vuint32_t VREG_CSRC_SC:1;
      vuint32_t CSRC_CSRC_SC:1;
      vuint32_t IRC_SC:1;
      vuint32_t SCSRC_SC:1;
      vuint32_t SYSCLK_SW:1;
      vuint32_t  :1;
      vuint32_t FLASH_SC:1;
      vuint32_t CDP_PRPH_224_255:1;
      vuint32_t CDP_PRPH_192_223:1;
      vuint32_t CDP_PRPH_160_191:1;
      vuint32_t CDP_PRPH_128_159:1;
      vuint32_t CDP_PRPH_96_127:1;
      vuint32_t CDP_PRPH_64_95:1;
      vuint32_t CDP_PRPH_32_63:1;
      vuint32_t CDP_PRPH_0_31:1;
    } B;
  } DMTS;

  uint8_t MC_ME_reserved0[4];
  union {                              /* RESET Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PWRLVL:3;
      vuint32_t  :4;
      vuint32_t PDO:1;
      vuint32_t  :2;
      vuint32_t MVRON:1;
      vuint32_t  :2;
      vuint32_t FLAON:2;
      vuint32_t  :8;
      vuint32_t PLL1ON:1;
      vuint32_t PLL0ON:1;
      vuint32_t XOSCON:1;
      vuint32_t IRCON:1;
      vuint32_t SYSCLK:4;
    } B;
  } RESET_MC;

  union {                              /* TEST Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PWRLVL:3;
      vuint32_t  :4;
      vuint32_t PDO:1;
      vuint32_t  :2;
      vuint32_t MVRON:1;
      vuint32_t  :2;
      vuint32_t FLAON:2;
      vuint32_t  :8;
      vuint32_t PLL1ON:1;
      vuint32_t PLL0ON:1;
      vuint32_t XOSCON:1;
      vuint32_t IRCON:1;
      vuint32_t SYSCLK:4;
    } B;
  } TEST_MC;

  union {                              /* SAFE Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PWRLVL:3;
      vuint32_t  :4;
      vuint32_t PDO:1;
      vuint32_t  :2;
      vuint32_t MVRON:1;
      vuint32_t  :2;
      vuint32_t FLAON:2;
      vuint32_t  :8;
      vuint32_t PLL1ON:1;
      vuint32_t PLL0ON:1;
      vuint32_t XOSCON:1;
      vuint32_t IRCON:1;
      vuint32_t SYSCLK:4;
    } B;
  } SAFE_MC;

  union {                              /* DRUN Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PWRLVL:3;
      vuint32_t  :4;
      vuint32_t PDO:1;
      vuint32_t  :2;
      vuint32_t MVRON:1;
      vuint32_t  :2;
      vuint32_t FLAON:2;
      vuint32_t  :8;
      vuint32_t PLL1ON:1;
      vuint32_t PLL0ON:1;
      vuint32_t XOSCON:1;
      vuint32_t IRCON:1;
      vuint32_t SYSCLK:4;
    } B;
  } DRUN_MC;

  union {                              /* RUN0 Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PWRLVL:3;
      vuint32_t  :4;
      vuint32_t PDO:1;
      vuint32_t  :2;
      vuint32_t MVRON:1;
      vuint32_t  :2;
      vuint32_t FLAON:2;
      vuint32_t  :8;
      vuint32_t PLL1ON:1;
      vuint32_t PLL0ON:1;
      vuint32_t XOSCON:1;
      vuint32_t IRCON:1;
      vuint32_t SYSCLK:4;
    } B;
  } RUN0_MC;

  union {                              /* RUN1 Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PWRLVL:3;
      vuint32_t  :4;
      vuint32_t PDO:1;
      vuint32_t  :2;
      vuint32_t MVRON:1;
      vuint32_t  :2;
      vuint32_t FLAON:2;
      vuint32_t  :8;
      vuint32_t PLL1ON:1;
      vuint32_t PLL0ON:1;
      vuint32_t XOSCON:1;
      vuint32_t IRCON:1;
      vuint32_t SYSCLK:4;
    } B;
  } RUN1_MC;

  union {                              /* RUN2 Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PWRLVL:3;
      vuint32_t  :4;
      vuint32_t PDO:1;
      vuint32_t  :2;
      vuint32_t MVRON:1;
      vuint32_t  :2;
      vuint32_t FLAON:2;
      vuint32_t  :8;
      vuint32_t PLL1ON:1;
      vuint32_t PLL0ON:1;
      vuint32_t XOSCON:1;
      vuint32_t IRCON:1;
      vuint32_t SYSCLK:4;
    } B;
  } RUN2_MC;

  union {                              /* RUN3 Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PWRLVL:3;
      vuint32_t  :4;
      vuint32_t PDO:1;
      vuint32_t  :2;
      vuint32_t MVRON:1;
      vuint32_t  :2;
      vuint32_t FLAON:2;
      vuint32_t  :8;
      vuint32_t PLL1ON:1;
      vuint32_t PLL0ON:1;
      vuint32_t XOSCON:1;
      vuint32_t IRCON:1;
      vuint32_t SYSCLK:4;
    } B;
  } RUN3_MC;

  union {                              /* HALT0 Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PWRLVL:3;
      vuint32_t  :4;
      vuint32_t PDO:1;
      vuint32_t  :2;
      vuint32_t MVRON:1;
      vuint32_t  :2;
      vuint32_t FLAON:2;
      vuint32_t  :8;
      vuint32_t PLL1ON:1;
      vuint32_t PLL0ON:1;
      vuint32_t XOSCON:1;
      vuint32_t IRCON:1;
      vuint32_t SYSCLK:4;
    } B;
  } HALT0_MC;

  uint8_t MC_ME_reserved1[4];
  union {                              /* STOP0 Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PWRLVL:3;
      vuint32_t  :4;
      vuint32_t PDO:1;
      vuint32_t  :2;
      vuint32_t MVRON:1;
      vuint32_t  :2;
      vuint32_t FLAON:2;
      vuint32_t  :8;
      vuint32_t PLL1ON:1;
      vuint32_t PLL0ON:1;
      vuint32_t XOSCON:1;
      vuint32_t IRCON:1;
      vuint32_t SYSCLK:4;
    } B;
  } STOP0_MC;

  uint8_t MC_ME_reserved2[20];
  union {                              /* Peripheral Status Register 0 */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t S_PIT_0:1;
      vuint32_t  :17;
      vuint32_t S_FEC_0:1;
      vuint32_t S_SIPI_0:1;
      vuint32_t  :1;
      vuint32_t S_LFAST_0:1;
      vuint32_t  :9;
    } B;
  } PS0;

  union {                              /* Peripheral Status Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :25;
      vuint32_t S_CRC_0:1;
      vuint32_t  :1;
      vuint32_t S_DMAMUX_0:1;
      vuint32_t  :1;
      vuint32_t S_ATX:1;
      vuint32_t  :2;
    } B;
  } PS1;

  union {                              /* Peripheral Status Register 2 */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t S_LINFlex_1:1;
      vuint32_t  :11;
      vuint32_t S_CAN_0:1;
      vuint32_t S_CAN_1:1;
      vuint32_t S_CAN_2:1;
      vuint32_t  :13;
    } B;
  } PS2;

  union {                              /* Peripheral Status Register 3 */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t S_ADC_1:1;
      vuint32_t  :1;
      vuint32_t S_ADC_3:1;
      vuint32_t  :16;
      vuint32_t S_FLEXRAY:1;
      vuint32_t  :2;
      vuint32_t S_SENT_0:1;
      vuint32_t  :4;
      vuint32_t S_DSPI_0:1;
      vuint32_t S_DSPI_1:1;
      vuint32_t  :2;
    } B;
  } PS3;

  union {                              /* Peripheral Status Register 4 */
    vuint32_t R;
    struct {
      vuint32_t  :13;
      vuint32_t S_DMAMUX_1:1;
      vuint32_t  :1;
      vuint32_t S_PWM_1:1;
      vuint32_t  :2;
      vuint32_t S_CTU_1:1;
      vuint32_t  :3;
      vuint32_t S_ETIMER_1:1;
      vuint32_t  :9;
    } B;
  } PS4;

  uint8_t MC_ME_reserved3[4];
  union {                              /* Peripheral Status Register 6 */
    vuint32_t R;
    struct {
      vuint32_t  :9;
      vuint32_t S_SENT_1:1;
      vuint32_t  :4;
      vuint32_t S_DSPI_2:1;
      vuint32_t S_DSPI_3:1;
      vuint32_t  :3;
      vuint32_t S_LINFlex_0:1;
      vuint32_t  :12;
    } B;
  } PS6;

  union {                              /* Peripheral Status Register 7 */
    vuint32_t R;
    struct {
      vuint32_t S_PWM_0:1;
      vuint32_t  :3;
      vuint32_t S_CTU_0:1;
      vuint32_t  :3;
      vuint32_t S_ETIMER_0:1;
      vuint32_t  :1;
      vuint32_t S_ETIMER_2:1;
      vuint32_t  :5;
      vuint32_t S_SWG_0:1;
      vuint32_t  :1;
      vuint32_t S_ADC_0:1;
      vuint32_t  :1;
      vuint32_t S_ADC_2:1;
      vuint32_t  :11;
    } B;
  } PS7;

  union {                              /* Run Peripheral Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t RUN3:1;
      vuint32_t RUN2:1;
      vuint32_t RUN1:1;
      vuint32_t RUN0:1;
      vuint32_t DRUN:1;
      vuint32_t SAFE:1;
      vuint32_t TEST:1;
      vuint32_t RESET:1;
    } B;
  } RUN_PC[8];

  union {                              /* Low-Power Peripheral Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :21;
      vuint32_t STOP0:1;
      vuint32_t  :1;
      vuint32_t HALT0:1;
      vuint32_t  :8;
    } B;
  } LP_PC[8];

  uint8_t MC_ME_reserved4[9];
  union {                              /* LFAST_0 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL9;

  uint8_t MC_ME_reserved5[1];
  union {                              /* SIPI_0 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL11;

  union {                              /* FEC_0 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL12;

  uint8_t MC_ME_reserved6[17];
  union {                              /* PIT_0 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL30;

  uint8_t MC_ME_reserved7[5];
  union {                              /* DMAMUX_0 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL36;

  uint8_t MC_ME_reserved8[1];
  union {                              /* CRC_0 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL38;

  uint8_t MC_ME_reserved9[38];
  union {                              /* CAN_2 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL77;

  union {                              /* CAN_1 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL78;

  union {                              /* CAN_0 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL79;

  uint8_t MC_ME_reserved10[11];
  union {                              /* LINFlex_1 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL91;

  uint8_t MC_ME_reserved11[6];
  union {                              /* DSPI_1 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL98;

  union {                              /* DSPI_0 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL99;

  uint8_t MC_ME_reserved12[4];
  union {                              /* SENT_0 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL104;

  uint8_t MC_ME_reserved13[2];
  union {                              /* FLEXRAY Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL107;

  uint8_t MC_ME_reserved14[16];
  union {                              /* ADC_3 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL124;

  uint8_t MC_ME_reserved15[1];
  union {                              /* ADC_1 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL126;

  uint8_t MC_ME_reserved16[10];
  union {                              /* ETIMER_1 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL137;

  uint8_t MC_ME_reserved17[3];
  union {                              /* CTU_1 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL141;

  uint8_t MC_ME_reserved18[2];
  union {                              /* PWM_1 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL144;

  uint8_t MC_ME_reserved19[1];
  union {                              /* DMAMUX_1 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL146;

  uint8_t MC_ME_reserved20[57];
  union {                              /* LINFlex_0 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL204;

  uint8_t MC_ME_reserved21[3];
  union {                              /* DSPI_3 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL208;

  union {                              /* DSPI_2 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL209;

  uint8_t MC_ME_reserved22[4];
  union {                              /* SENT_1 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL214;

  uint8_t MC_ME_reserved23[20];
  union {                              /* ADC_2 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL235;

  uint8_t MC_ME_reserved24[1];
  union {                              /* ADC_0 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL237;

  uint8_t MC_ME_reserved25[1];
  union {                              /* SGEN_0 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL239;

  uint8_t MC_ME_reserved26[5];
  union {                              /* ETIMER_2 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL245;

  uint8_t MC_ME_reserved27[1];
  union {                              /* ETIMER_0 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL247;

  uint8_t MC_ME_reserved28[3];
  union {                              /* CTU_0 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL251;

  uint8_t MC_ME_reserved29[3];
  union {                              /* PWM_0 Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL255;

  union {                              /* Core Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :31;
      vuint32_t S_CORE0:1;
    } B;
  } CS;

  union {                              /* Core Control Register */
    vuint16_t R;
    struct {
      vuint16_t  :5;
      vuint16_t STOP0:1;
      vuint16_t  :1;
      vuint16_t HALT0:1;
      vuint16_t RUN3:1;
      vuint16_t RUN2:1;
      vuint16_t RUN1:1;
      vuint16_t RUN0:1;
      vuint16_t DRUN:1;
      vuint16_t SAFE:1;
      vuint16_t TEST:1;
      vuint16_t RESET:1;
    } B;
  } CCTL0;

  uint8_t MC_ME_reserved30[26];
  union {                              /* CORE0 Address Register */
    vuint32_t R;
    struct {
      vuint32_t ADDR:30;
      vuint32_t  :1;
      vuint32_t  :1;
    } B;
  } CADDR0;
};


/* ============================================================================
   =============================== Module: MC_PCU =============================
   ============================================================================ */

struct MC_PCU_tag {
  union {                              /* Power Domain #0 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :21;
      vuint32_t STOP0:1;
      vuint32_t  :1;
      vuint32_t HALT0:1;
      vuint32_t RUN3:1;
      vuint32_t RUN2:1;
      vuint32_t RUN1:1;
      vuint32_t RUN0:1;
      vuint32_t DRUN:1;
      vuint32_t SAFE:1;
      vuint32_t TEST:1;
      vuint32_t RST:1;
    } B;
  } PCONF0;

  uint8_t MC_PCU_reserved0[60];
  union {                              /* Power Domain Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :31;
      vuint32_t PD0:1;
    } B;
  } PSTAT;
};


/* ============================================================================
   =============================== Module: MC_RGM =============================
   ============================================================================ */

struct MC_RGM_tag {
  union {                              /* 'Destructive' Event Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t F_VOR_DEST:1;
      vuint32_t F_TSR_DEST:1;
      vuint32_t  :13;
      vuint32_t F_FIF:1;
      vuint32_t F_EDR:1;
      vuint32_t  :2;
      vuint32_t F_SUF:1;
      vuint32_t F_FFRR:1;
      vuint32_t F_SOFT_DEST:1;
      vuint32_t  :2;
      vuint32_t F_POR:1;
    } B;
  } DES;

  uint8_t MC_RGM_reserved0[12];
  union {                              /* 'Destructive' Event Reset Disable Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t D_VOR_DEST:1;
      vuint32_t D_TSR_DEST:1;
      vuint32_t  :13;
      vuint32_t F_FIF:1;
      vuint32_t D_EDR:1;
      vuint32_t  :2;
      vuint32_t F_SUF:1;
      vuint32_t D_FFRR:1;
      vuint32_t D_SOF_DEST:1;
      vuint32_t  :2;
      vuint32_t D_POR:1;
    } B;
  } DERD;

  uint8_t MC_RGM_reserved1[28];
  union {                              /* Destructive' Bidirectional Reset Enable Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t BE_VOR_DEST:1;
      vuint32_t BE_TSR_DEST:1;
      vuint32_t  :13;
      vuint32_t F_FIF:1;
      vuint32_t BE_EDR:1;
      vuint32_t  :2;
      vuint32_t F_SUF:1;
      vuint32_t BE_FFRR:1;
      vuint32_t BE_SOF_DEST:1;
      vuint32_t  :2;
      vuint32_t BE_POR:1;
    } B;
  } DBRE;

  uint8_t MC_RGM_reserved2[716];
  union {                              /* 'Functional' Event Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t F_VOR_FUNC:1;
      vuint32_t F_TSR_FUNC:1;
      vuint32_t  :12;
      vuint32_t F_JTAG_FUNC:1;         /* Flag for JTAG 'functional' reset */
      vuint32_t  :3;
      vuint32_t F_FCCU_SOFT:1;
      vuint32_t F_FCCU_HARD:1;
      vuint32_t  :1;
      vuint32_t F_SOFT_FUNC:1;
      vuint32_t F_ST_DONE:1;
      vuint32_t  :1;
      vuint32_t F_EXR:1;
    } B;
  } FES;

  uint8_t MC_RGM_reserved3[12];
  union {                              /* 'Functional' Event Reset Disable Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t D_VOR_FUNC:1;
      vuint32_t D_TSR_FUNC:1;
      vuint32_t  :12;
      vuint32_t D_JTAG_FUNC:1;
      vuint32_t  :3;
      vuint32_t D_FCCU_SOFT:1;
      vuint32_t D_FCCU_HARD:1;
      vuint32_t  :1;
      vuint32_t D_SOFT_FUNC:1;
      vuint32_t D_ST_DONE:1;
      vuint32_t  :2;
    } B;
  } FERD;

  uint8_t MC_RGM_reserved4[12];
  union {                              /* 'Functional' Event Alternate Request Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t AR_VOR_FUNC:1;
      vuint32_t AR_TSR_FUNC:1;
      vuint32_t  :12;
      vuint32_t AR_JTAG_FUNC:1;
      vuint32_t  :10;
    } B;
  } FEAR;

  uint8_t MC_RGM_reserved5[12];
  union {                              /* 'Functional' Bidirectional Reset Enable Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t BE_VOR_FUNC:1;
      vuint32_t BE_TSR_FUNC:1;
      vuint32_t  :12;
      vuint32_t BE_JTAG_FUNC:1;
      vuint32_t  :3;
      vuint32_t BE_FCCU_SOFT:1;
      vuint32_t BE_FCCU_HARD:1;
      vuint32_t  :1;
      vuint32_t BE_SOFT_FUNC:1;
      vuint32_t BE_ST_DONE:1;
      vuint32_t  :1;
      vuint32_t BE_EXR:1;
    } B;
  } FBRE;

  uint8_t MC_RGM_reserved6[12];
  union {                              /* 'Functional' Event Short Sequence Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SS_VOR_FUNC:1;
      vuint32_t SS_TSR_FUNC:1;
      vuint32_t  :12;
      vuint32_t SS_JTAG_FUNC:1;
      vuint32_t  :3;
      vuint32_t SS_FCCU_SOFT:1;
      vuint32_t SS_FCCU_HARD:1;
      vuint32_t  :1;
      vuint32_t SS_SOFT_FUNC:1;
      vuint32_t SS_ST_DONE:1;
      vuint32_t  :1;
      vuint32_t SS_EXR:1;
    } B;
  } FESS;

  uint8_t MC_RGM_reserved7[704];
  union {                              /* 'Functional' Reset Escalation Threshold Register */
    vuint8_t R;
    struct {
      vuint8_t  :4;
      vuint8_t FRET:4;
    } B;
  } FRET;

  uint8_t MC_RGM_reserved8[3];
  union {                              /* 'Destructive' Reset Escalation Threshold Register */
    vuint8_t R;
    struct {
      vuint8_t  :4;
      vuint8_t DRET:4;
    } B;
  } DRET;
};


/* ============================================================================
   =============================== Module: MEMU ===============================
   ============================================================================ */

struct MEMU_tag {
  union {                              /* Control register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t SWR:1;
      vuint32_t  :15;
    } B;
  } CTRL;

  union {                              /* Error flag register */
    vuint32_t R;
    struct {
      vuint32_t  :11;
      vuint32_t PR_CE:1;
      vuint32_t PR_UCE:1;
      vuint32_t PR_CEO:1;
      vuint32_t PR_UCO:1;
      vuint32_t PR_EBO:1;
      vuint32_t  :3;
      vuint32_t F_CE:1;
      vuint32_t F_UCE:1;
      vuint32_t F_CEO:1;
      vuint32_t F_UCO:1;
      vuint32_t F_EBO:1;
      vuint32_t  :3;
      vuint32_t SR_CE:1;
      vuint32_t SR_UCE:1;
      vuint32_t SR_CEO:1;
      vuint32_t SR_UCO:1;
      vuint32_t SR_EBO:1;
    } B;
  } ERR_FLAG;

  uint8_t MEMU_reserved0[4];
  union {                              /* Debug register */
    vuint32_t R;
    struct {
      vuint32_t  :11;
      vuint32_t FR_PR_CE:1;
      vuint32_t FR_PR_UCE:1;
      vuint32_t FR_PR_CEO:1;
      vuint32_t FR_PR_UCO:1;
      vuint32_t FR_PR_EBO:1;
      vuint32_t  :3;
      vuint32_t FR_F_CE:1;
      vuint32_t FR_F_UCE:1;
      vuint32_t FR_F_CEO:1;
      vuint32_t FR_F_UCO:1;
      vuint32_t FR_F_EBO:1;
      vuint32_t  :3;
      vuint32_t FR_SR_CE:1;
      vuint32_t FR_SR_UCE:1;
      vuint32_t FR_SR_CEO:1;
      vuint32_t FR_SR_UCO:1;
      vuint32_t FR_SR_EBO:1;
    } B;
  } DEBUG;

  uint8_t MEMU_reserved1[16];
  struct {
    union {                            /* System RAM correctable error reporting table status register */
      vuint32_t R;
      struct {
        vuint32_t VLD:1;
        vuint32_t  :23;
        vuint32_t BAD_BIT:8;
      } B;
    } STS;
    union {                            /* System RAM correctable error reporting table address register */
      vuint32_t R;
      struct {
        vuint32_t ERR_ADD:32;
      } B;
    } ADDR;
  } SYS_RAM_CERR[10];

  union {                              /* System RAM uncorrectable error reporting table status register */
    vuint32_t R;
    struct {
      vuint32_t VLD:1;
      vuint32_t  :31;
    } B;
  } SYS_RAM_UNCERR_STS;

  union {                              /* System RAM uncorrectable error reporting table address register */
    vuint32_t R;
    struct {
      vuint32_t ERR_ADD:32;
    } B;
  } SYS_RAM_UNCERR_ADDR;

  union {                              /* System RAM concurrent overflow register */
    vuint32_t R;
    struct {
      vuint32_t OFLW:32;
    } B;
  } SYS_RAM_OFLW[3];

  uint8_t MEMU_reserved2[1436];
  struct {
    union {                            /* Peripheral RAM correctable error reporting table status register */
      vuint32_t R;
      struct {
        vuint32_t VLD:1;
        vuint32_t  :23;
        vuint32_t BAD_BIT:8;
      } B;
    } STS;
    union {                            /* Peripheral RAM correctable error reporting table address register */
      vuint32_t R;
      struct {
        vuint32_t ERR_ADD:32;
      } B;
    } ADDR;
  } PERIPH_RAM_CERR[2];

  union {                              /* Peripheral RAM uncorrectable error reporting table status register */
    vuint32_t R;
    struct {
      vuint32_t VLD:1;
      vuint32_t  :31;
    } B;
  } PERIPH_RAM_UNCERR_STS;

  union {                              /* Peripheral RAM uncorrectable error reporting table address register */
    vuint32_t R;
    struct {
      vuint32_t ERR_ADD:32;
    } B;
  } PERIPH_RAM_UNCERR_ADDR;

  union {                              /* Peripheral RAM concurrent overflow register */
    vuint32_t R;
    struct {
      vuint32_t OFLW:32;
    } B;
  } PERIPH_RAM_OFLW0;

  uint8_t MEMU_reserved3[1508];
  struct {
    union {                            /* Flash memory correctable error reporting table status register */
      vuint32_t R;
      struct {
        vuint32_t VLD:1;
        vuint32_t  :23;
        vuint32_t BAD_BIT:8;
      } B;
    } STS;
    union {                            /* Flash memory correctable error reporting table address register */
      vuint32_t R;
      struct {
        vuint32_t ERR_ADD:32;
      } B;
    } ADDR;
  } FLASH_CERR[20];

  union {                              /* Flash memory uncorrectable error reporting table status register */
    vuint32_t R;
    struct {
      vuint32_t VLD:1;
      vuint32_t  :31;
    } B;
  } FLASH_UNCERR_STS;

  union {                              /* Flash memory uncorrectable error reporting table address register */
    vuint32_t R;
    struct {
      vuint32_t ERR_ADD:32;
    } B;
  } FLASH_UNCERR_ADDR;

  union {                              /* Flash memory concurrent overflow register */
    vuint32_t R;
    struct {
      vuint32_t OFLW:32;
    } B;
  } FLASH_OFLW0;
};


/* ============================================================================
   =============================== Module: PCM ================================
   ============================================================================ */

struct PCM_tag {
  uint8_t PCM_reserved0[4];
  union {                              /* Bus Bridge Configuration Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :13;
      vuint32_t PRE:1;                 /* Pending Read Enable */
      vuint32_t BRE:1;                 /* Burst Read Enable */
      vuint32_t BWE:1;                 /* Burst Write Enable */
      vuint32_t  :16;
    } B;
  } IAHB_BE1;

  union {                              /* Bus Bridge Configuration Register 2 */
    vuint32_t R;
    struct {
      vuint32_t  :21;
      vuint32_t PRE:1;                 /* Pending Read Enable */
      vuint32_t BRE:1;                 /* Burst Read Enable */
      vuint32_t BWE:1;                 /* Burst Write Enable */
      vuint32_t  :8;
    } B;
  } IAHB_BE2;

  union {                              /* Bus Bridge Configuration Register 3 */
    vuint32_t R;
    struct {
      vuint32_t  :21;
      vuint32_t PRE_B:1;               /* Pending Read Enable */
      vuint32_t BRE_B:1;               /* Burst Read Enable */
      vuint32_t BWE_B:1;               /* Burst Write Enable */
      vuint32_t  :5;
      vuint32_t PRE_A:1;               /* Pending Read Enable */
      vuint32_t BRE_A:1;               /* Burst Read Enable */
      vuint32_t BWE_A:1;               /* Burst Write Enable */
    } B;
  } IAHB_BE3;
};


/* ============================================================================
   =============================== Module: PFLASH =============================
   ============================================================================ */

struct PFLASH_tag {
  union {                              /* Platform Flash Configuration Register 1 */
    vuint32_t R;
    struct {
      vuint32_t P0_M15PFE:1;
      vuint32_t P0_M14PFE:1;
      vuint32_t P0_M13PFE:1;
      vuint32_t P0_M12PFE:1;
      vuint32_t P0_M11PFE:1;
      vuint32_t P0_M10PFE:1;
      vuint32_t P0_M9PFE:1;
      vuint32_t P0_M8PFE:1;
      vuint32_t P0_M7PFE:1;
      vuint32_t P0_M6PFE:1;
      vuint32_t P0_M5PFE:1;
      vuint32_t P0_M4PFE:1;
      vuint32_t P0_M3PFE:1;
      vuint32_t P0_M2PFE:1;
      vuint32_t P0_M1PFE:1;
      vuint32_t P0_M0PFE:1;
      vuint32_t APC:3;
      vuint32_t RWSC:5;
      vuint32_t  :1;
      vuint32_t P0_DPFEN:1;
      vuint32_t  :1;
      vuint32_t P0_IPFEN:1;
      vuint32_t  :1;
      vuint32_t P0_PFLIM:2;
      vuint32_t P0_BFEN:1;
    } B;
  } PFCR1;

  uint8_t PFLASH_reserved0[4];
  union {                              /* Platform Flash Configuration Register 3 */
    vuint32_t R;
    struct {
      vuint32_t P0_WCFG:2;
      vuint32_t  :2;
      vuint32_t  :2;
      vuint32_t  :5;
      vuint32_t  :1;
      vuint32_t  :3;
      vuint32_t  :1;
      vuint32_t  :4;
      vuint32_t  :11;
      vuint32_t  :1;
    } B;
  } PFCR3;

  union {                              /* Platform Flash Access Protection Register */
    vuint32_t R;
    struct {
      vuint32_t M0AP:2;
      vuint32_t M1AP:2;
      vuint32_t M2AP:2;
      vuint32_t M3AP:2;
      vuint32_t M4AP:2;
      vuint32_t M5AP:2;
      vuint32_t M6AP:2;
      vuint32_t M7AP:2;
      vuint32_t M8AP:2;
      vuint32_t M9AP:2;
      vuint32_t M10AP:2;
      vuint32_t M11AP:2;
      vuint32_t M12AP:2;
      vuint32_t M13AP:2;
      vuint32_t M14AP:2;
      vuint32_t M15AP:2;
    } B;
  } PFAPR;

  union {                              /* Platform Flash Remap Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :23;
      vuint32_t SAFE_CAL:1;
      vuint32_t  :3;
      vuint32_t IRMEN:1;
      vuint32_t  :3;
      vuint32_t GRMEN:1;
    } B;
  } PFCRCR;

  union {                              /* Platform Flash Remap Descriptor Enable Register */
    vuint32_t R;
    struct {
      vuint32_t CRD0EN:1;
      vuint32_t CRD1EN:1;
      vuint32_t CRD2EN:1;
      vuint32_t CRD3EN:1;
      vuint32_t CRD4EN:1;
      vuint32_t CRD5EN:1;
      vuint32_t CRD6EN:1;
      vuint32_t CRD7EN:1;
      vuint32_t CRD8EN:1;
      vuint32_t CRD9EN:1;
      vuint32_t CRD10EN:1;
      vuint32_t CRD11EN:1;
      vuint32_t CRD12EN:1;
      vuint32_t CRD13EN:1;
      vuint32_t CRD14EN:1;
      vuint32_t CRD15EN:1;
      vuint32_t CRD16EN:1;
      vuint32_t CRD17EN:1;
      vuint32_t CRD18EN:1;
      vuint32_t CRD19EN:1;
      vuint32_t CRD20EN:1;
      vuint32_t CRD21EN:1;
      vuint32_t CRD22EN:1;
      vuint32_t CRD23EN:1;
      vuint32_t CRD24EN:1;
      vuint32_t CRD25EN:1;
      vuint32_t CRD26EN:1;
      vuint32_t CRD27EN:1;
      vuint32_t CRD28EN:1;
      vuint32_t CRD29EN:1;
      vuint32_t CRD30EN:1;
      vuint32_t CRD31EN:1;
    } B;
  } PFCRDE;

  uint8_t PFLASH_reserved1[232];
  struct {
    union {                            /* Platform Flash Calibration Region Descriptor n Word0 */
      vuint32_t R;
      struct {
        vuint32_t LSTARTADDR:32;
      } B;
    } Word0;
    union {                            /* Platform Flash Calibration Region Descriptor n Word1 */
      vuint32_t R;
      struct {
        vuint32_t PSTARTADDR:32;
      } B;
    } Word1;
    union {                            /* Platform Flash Calibration Region Descriptor n Word2 */
      vuint32_t R;
      struct {
        vuint32_t M0EN:1;
        vuint32_t M1EN:1;
        vuint32_t M2EN:1;
        vuint32_t M3EN:1;
        vuint32_t M4EN:1;
        vuint32_t M5EN:1;
        vuint32_t M6EN:1;
        vuint32_t M7EN:1;
        vuint32_t M8EN:1;
        vuint32_t M9EN:1;
        vuint32_t M10EN:1;
        vuint32_t M11EN:1;
        vuint32_t M12EN:1;
        vuint32_t M13EN:1;
        vuint32_t M14EN:1;
        vuint32_t M15EN:1;
        vuint32_t  :11;
        vuint32_t CRDSize:5;
      } B;
    } Word2;
    uint8_t PFCRD_reserved0[4];
  } PFCRD[8];
};


/* ============================================================================
   =============================== Module: PIT ================================
   ============================================================================ */

struct PIT_tag {
  union {                              /* PIT Module Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :29;
      vuint32_t  :1;
      vuint32_t MDIS:1;                /* Module Disable - (PIT section) */
      vuint32_t FRZ:1;                 /* Freeze */
    } B;
  } MCR;

  uint8_t PIT_reserved0[220];
  union {                              /* PIT Upper Lifetime Timer Register */
    vuint32_t R;
    struct {
      vuint32_t LTH:32;                /* Life Timer value */
    } B;
  } LTMR64H;

  union {                              /* PIT Lower Lifetime Timer Register */
    vuint32_t R;
    struct {
      vuint32_t LTL:32;                /* Life Timer value */
    } B;
  } LTMR64L;

  uint8_t PIT_reserved1[24];
  struct {
    union {                            /* Timer Load Value Register */
      vuint32_t R;
      struct {
        vuint32_t TSV:32;              /* Timer Start Value */
      } B;
    } LDVAL;
    union {                            /* Current Timer Value Register */
      vuint32_t R;
      struct {
        vuint32_t TVL:32;              /* Current Timer Value */
      } B;
    } CVAL;
    union {                            /* Timer Control Register */
      vuint32_t R;
      struct {
        vuint32_t  :29;
        vuint32_t CHN:1;               /* Chain Mode */
        vuint32_t TIE:1;               /* Timer Interrupt Enable */
        vuint32_t TEN:1;               /* Timer Enable */
      } B;
    } TCTRL;
    union {                            /* Timer Flag Register */
      vuint32_t R;
      struct {
        vuint32_t  :31;
        vuint32_t TIF:1;               /* Timer Interrupt Flag */
      } B;
    } TFLG;
  } CH[4];
};


/* ============================================================================
   =============================== Module: PLLDIG =============================
   ============================================================================ */

struct PLLDIG_tag {
  union {                              /* PLLDIG PLL0 Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :22;
      vuint32_t CLKCFG:2;              /* Clock Configuration */
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t LOLIE:1;               /* Loss-of-lock interrupt enable. */
      vuint32_t  :1;
      vuint32_t LOCIE:1;               /* Loss-of-clock interrupt request. */
      vuint32_t  :1;
    } B;
  } PLL0CR;

  union {                              /* PLLDIG PLL0 Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t LOLF:1;
      vuint32_t LOCK:1;
      vuint32_t  :1;
      vuint32_t  :1;
    } B;
  } PLL0SR;

  union {                              /* PLLDIG PLL0 Divider Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t RFDPHI1:4;             /* PHI1 reduced frequency divider. */
      vuint32_t  :5;
      vuint32_t RFDPHI:6;              /* PHI reduced frequency divider. */
      vuint32_t  :1;
      vuint32_t PREDIV:3;              /* Input clock predivider. */
      vuint32_t  :5;
      vuint32_t MFD:7;                 /* Loop multiplication factor divider. */
    } B;
  } PLL0DV;

  uint8_t PLLDIG_reserved0[20];
  union {                              /* PLLDIG PLL1 Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :22;
      vuint32_t CLKCFG:2;              /* Clock Configuration */
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t LOLIE:1;               /* Loss-of-lock interrupt enable. */
      vuint32_t  :1;
      vuint32_t LOCIE:1;               /* Loss-of-clock interrupt request. */
      vuint32_t  :1;
    } B;
  } PLL1CR;

  union {                              /* PLLDIG PLL1 Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :22;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t LOLF:1;
      vuint32_t LOCK:1;
      vuint32_t  :1;
      vuint32_t  :1;
    } B;
  } PLL1SR;

  union {                              /* PLLDIG PLL1 Divider Register */
    vuint32_t R;
    struct {
      vuint32_t  :10;
      vuint32_t RFDPHI:6;
      vuint32_t  :5;
      vuint32_t  :4;
      vuint32_t MFD:7;                 /* Loop multiplication factor divider. */
    } B;
  } PLL1DV;

  union {                              /* PLLDIG PLL1 Frequency Modulation Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t MODEN:1;               /* Modulation enable. */
      vuint32_t MODSEL:1;              /* Modulation selection. */
      vuint32_t MODPRD:13;             /* Modulation period. */
      vuint32_t  :1;
      vuint32_t INCSTP:15;             /* Increment step. */
    } B;
  } PLL1FM;

  union {                              /* PLLDIG PLL1 Fractional Divide Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t FDEN:1;                /* Fractional Divide Enable */
      vuint32_t  :12;
      vuint32_t DTHDIS:2;              /* Dither Disable. */
      vuint32_t  :4;
      vuint32_t FRCDIV:12;
    } B;
  } PLL1FD;
};


/* ============================================================================
   =============================== Module: PMC ================================
   ============================================================================ */

struct PMC_tag {
  union {                              /* PMC Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :30;                  /* Reserved */
      vuint32_t INT_EXT_AUX_REG:1;
      vuint32_t EXT_INT_REG:1;
    } B;
  } PMCSR;

  union {                              /* Regulator Voltage Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :25;                  /* Reserved */
      vuint32_t VD6:1;
      vuint32_t  :1;                   /* Reserved */
      vuint32_t VD4:1;
      vuint32_t VD3:1;
      vuint32_t  :3;                   /* Reserved */
    } B;
  } RSSR;

  union {                              /* PMC Control Register */
    vuint32_t R;
    struct {
      vuint32_t PMCCR_EN:1;
      vuint32_t  :16;                  /* Reserved */
      vuint32_t LVD_OSC_DIS:1;
      vuint32_t LVD_ADC_DIS:1;
      vuint32_t LVD_IO_DIS:1;
      vuint32_t LVD_FLASH_DIS:1;
      vuint32_t LVD2_CORE_DIS:1;
      vuint32_t  :2;
      vuint32_t HVD_CORE_DIS:1;
      vuint32_t  :2;                   /* Reserved */
      vuint32_t LVD1_H_CORE_DIS:1;
      vuint32_t LVD1_C_CORE_DIS:1;
      vuint32_t  :1;                   /* Reserved */
      vuint32_t INT_AUX_REG_BYPASS:1;
      vuint32_t INT_REG_BYPASS:1;
    } B;
  } PMCCR;

  uint8_t PMC_reserved0[4];
  union {                              /* Interrupt Enable Register */
    vuint32_t R;
    struct {
      vuint32_t IE_EN:1;
      vuint32_t  :1;                   /* Reserved */
      vuint32_t TS1_3IE:1;
      vuint32_t TS1_2IE:1;
      vuint32_t TS1_0IE:1;
      vuint32_t TS0_3IE:1;
      vuint32_t TS0_2IE:1;
      vuint32_t TS0_0IE:1;
      vuint32_t  :9;                   /* Reserved */
      vuint32_t VD6IE_O:1;
      vuint32_t VD6IE_ADC:1;
      vuint32_t VD6IE_IM:1;
      vuint32_t VD6IE_F:1;
      vuint32_t VD6IE_C:1;
      vuint32_t  :2;                   /* Reserved */
      vuint32_t VD4IE_C:1;
      vuint32_t  :2;                   /* Reserved */
      vuint32_t VD3IE_H:1;             /* Voltage Detect 3 Interrupt Enable Hot */
      vuint32_t VD3IE_C:1;
      vuint32_t  :3;                   /* Reserved */
    } B;
  } IER;

  uint8_t PMC_reserved1[12];
  union {                              /* Event Status Register 0 */
    vuint32_t R;
    struct {
      vuint32_t  :10;                  /* Reserved */
      vuint32_t VD0_C:1;               /* Voltage Detect 0 Cold low-voltage POR flag */
      vuint32_t  :1;                   /* Reserved */
      vuint32_t VD15_C:1;
      vuint32_t  :1;
      vuint32_t VD12_C:1;
      vuint32_t  :2;
      vuint32_t VD6_O:1;
      vuint32_t VD6_ADC:1;
      vuint32_t VD6_IM:1;
      vuint32_t VD6_F:1;
      vuint32_t VD6_C:1;
      vuint32_t  :1;
      vuint32_t VD5_C:1;
      vuint32_t VD4_C:1;
      vuint32_t  :2;
      vuint32_t VD3_H:1;               /* Voltage Detect 3 Hot low-voltage detect flag. */
      vuint32_t VD3_C:1;
      vuint32_t  :1;
      vuint32_t VD2_C:1;
      vuint32_t VD1_C:1;
    } B;
  } ESR_0;

  uint8_t PMC_reserved2[12];
  union {                              /* Reset Event Enable 0 */
    vuint32_t R;
    struct {
      vuint32_t  :17;
      vuint32_t VD6RE_O:1;
      vuint32_t VD6RE_ADC:1;
      vuint32_t VD6RE_IM:1;
      vuint32_t VD6RE_F:1;
      vuint32_t VD6RE_C:1;
      vuint32_t  :2;                   /* Reserved */
      vuint32_t VD4RE_C:1;
      vuint32_t  :2;                   /* Reserved */
      vuint32_t VD3RE_H:1;             /* Voltage Detect 3 Reset Enable Hot. */
      vuint32_t VD3RE_C:1;
      vuint32_t  :3;                   /* Reserved */
    } B;
  } REE_0;

  uint8_t PMC_reserved3[12];
  union {                              /* Reset Event Selection 0 */
    vuint32_t R;
    struct {
      vuint32_t  :17;                  /* Reserved */
      vuint32_t VD6RES_O:1;
      vuint32_t VD6RES_ADC:1;
      vuint32_t VD6RES_IM:1;
      vuint32_t VD6RES_F:1;
      vuint32_t VD6RES_C:1;
      vuint32_t  :2;                   /* Reserved */
      vuint32_t VD4RES_C:1;
      vuint32_t  :2;                   /* Reserved */
      vuint32_t VD3RES_H:1;            /* Voltage Detect 3 Reset Event Select Hot. */
      vuint32_t VD3RES_C:1;
      vuint32_t  :3;                   /* Reserved */
    } B;
  } RES_0;

  uint8_t PMC_reserved4[44];
  union {                              /* FCCU Fault Injection Register */
    vuint32_t R;
    struct {
      vuint32_t  :28;                  /* Reserved */
      vuint32_t STEST_Fault:1;
      vuint32_t TSNS_Fault:1;
      vuint32_t HVD_Fault:1;
      vuint32_t LVD_Fault:1;
    } B;
  } FIR;

  uint8_t PMC_reserved5[140];
  union {                              /* Temperature Event Status register */
    vuint32_t R;
    struct {
      vuint32_t  :4;                   /* Reserved */
      vuint32_t TEMP1_3_OP:1;          /* Temperature Sensor 1 Output 3 */
      vuint32_t TEMP1_2_OP:1;          /* Temperature Sensor 1 Output 2 */
      vuint32_t  :1;                   /* Reserved */
      vuint32_t TEMP1_0_OP:1;          /* Temperature Sensor 1 Output 0 */
      vuint32_t  :4;                   /* Reserved */
      vuint32_t TEMP0_3_OP:1;          /* Temperature Sensor 0 Output 3 */
      vuint32_t TEMP0_2_OP:1;          /* Temperature Sensor 0 Output 2 */
      vuint32_t  :1;                   /* Reserved */
      vuint32_t TEMP0_0_OP:1;          /* Temperature Sensor 0 Output 0 */
      vuint32_t  :4;                   /* Reserved */
      vuint32_t TEMP1_3:1;
      vuint32_t TEMP1_2:1;
      vuint32_t  :1;                   /* Reserved */
      vuint32_t TEMP1_0:1;
      vuint32_t  :4;                   /* Reserved */
      vuint32_t TEMP0_3:1;
      vuint32_t TEMP0_2:1;
      vuint32_t  :1;                   /* Reserved */
      vuint32_t TEMP0_0:1;
    } B;
  } ESR_TD;

  union {                              /* Temperature Reset Event Enable register */
    vuint32_t R;
    struct {
      vuint32_t  :20;                  /* Reserved */
      vuint32_t TEMP1_3:1;
      vuint32_t TEMP1_2:1;
      vuint32_t  :1;                   /* Reserved */
      vuint32_t TEMP1_0:1;
      vuint32_t  :4;                   /* Reserved */
      vuint32_t TEMP0_3:1;
      vuint32_t TEMP0_2:1;
      vuint32_t  :1;                   /* Reserved */
      vuint32_t TEMP0_0:1;
    } B;
  } REE_TD;

  union {                              /* Temperature Reset Event Selection register */
    vuint32_t R;
    struct {
      vuint32_t  :20;                  /* Reserved */
      vuint32_t TEMP1_3:1;             /* TEMP1_3 Reset Event Select. */
      vuint32_t TEMP1_2:1;             /* TEMP1_2 Reset Event Select. */
      vuint32_t  :1;                   /* Reserved */
      vuint32_t TEMP1_0:1;             /* TEMP1_0 Reset Event Select. */
      vuint32_t  :4;                   /* Reserved */
      vuint32_t TEMP0_3:1;             /* TEMP0_3 Reset Event Select. */
      vuint32_t TEMP0_2:1;             /* TEMP0_2 Reset Event Select. */
      vuint32_t  :1;                   /* Reserved */
      vuint32_t TEMP0_0:1;             /* TEMP0_0 Reset Event Select. */
    } B;
  } RES_TD;

  union {                              /* Temperature detector configuration register */
    vuint32_t R;
    struct {
      vuint32_t  :17;                  /* Reserved */
      vuint32_t TS1_TRIM_ADJ:5;
      vuint32_t TS1_DOUT_EN:1;
      vuint32_t TS1_AOUT_EN:1;
      vuint32_t  :1;                   /* Reserved */
      vuint32_t TS0_TRIM_ADJ:5;
      vuint32_t TS0_DOUT_EN:1;
      vuint32_t TS0_AOUT_EN:1;
    } B;
  } CTL_TD;

  uint8_t PMC_reserved6[44];
  union {                              /* LVD Self Test Time Window Register */
    vuint32_t R;
    struct {
      vuint32_t  :20;                  /* Reserved */
      vuint32_t STTW:12;
    } B;
  } STTW;

  union {                              /* Voltage Detect User Mode Test Register */
    vuint32_t R;
    struct {
      vuint32_t  :14;                  /* Reserved */
      vuint32_t ST_RESULT:1;           /* Self Test Result. */
      vuint32_t ST_DONE:1;
      vuint32_t  :8;                   /* Reserved */
      vuint32_t ST_MODE:2;             /* Self Test mode bits for testing of LVDs and HVDs. */
      vuint32_t VD_ST_CTRL:6;
    } B;
  } VD_UTST;
};


/* ============================================================================
   =============================== Module: PRAMC ==============================
   ============================================================================ */

struct PRAMC_tag {
  union {                              /* Platform RAM Configuration Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :22;
      vuint32_t PRI:2;                 /* AHB port arbitration mode. */
      vuint32_t P1_BO_DIS:1;           /* Port p1 read burst optimization disable. */
      vuint32_t P0_BO_DIS:1;           /* Port p0 read burst optimization disable. */
      vuint32_t  :5;
      vuint32_t FT_DIS:1;              /* Flow through disabled. */
    } B;
  } PRCR1;
};


/* ============================================================================
   =============================== Module: SGEN ===============================
   ============================================================================ */

struct SGEN_tag {
  union {                              /* Control Register */
    vuint32_t R;
    struct {
      vuint32_t LDOS:1;                /* Load on set */
      vuint32_t  :1;
      vuint32_t IOAMPL:4;              /* IO amplitude */
      vuint32_t  :2;
      vuint32_t SEMASK:1;              /* Sine wave generator error mask interrupt register */
      vuint32_t  :3;
      vuint32_t TRIG_SEL:1;            /* Input trigger select */
      vuint32_t TRIG_EN:1;             /* Input phase align trigger enable bit */
      vuint32_t S0H1:1;                /* Operation status */
      vuint32_t PDS:1;                 /* Operation status */
      vuint32_t IOFREQ:16;             /* Sine wave frequency value on I/O pad */
    } B;
  } CTRL;

  union {                              /* Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :8;
      vuint32_t SERR:1;                /* Status error */
      vuint32_t  :3;
      vuint32_t FERR:1;                /* Force error */
      vuint32_t PHERR:1;               /* Phase error force bit */
      vuint32_t  :18;
    } B;
  } STAT;
};


/* ============================================================================
   =============================== Module: SIPI ===============================
   ============================================================================ */

struct SIPI_tag {
  union {                              /* SIPI Channel Control Register 0 */
    vuint32_t R;
    struct {
      vuint32_t  :15;
      vuint32_t TC:1;                  /* Send Trigger Command. */
      vuint32_t  :8;
      vuint32_t WL:2;                  /* Word Length Transfer. */
      vuint32_t CHEN:1;                /* Channel Enable. */
      vuint32_t ST:1;                  /* Streaming Transfer. */
      vuint32_t IDT:1;                 /* ID Read Request Transfer. */
      vuint32_t RRT:1;                 /* Read Request Transfer. */
      vuint32_t WRT:1;                 /* Write Request Transfer. */
      vuint32_t DEN:1;                 /* DMA Enable. */
    } B;
  } CCR0;

  union {                              /* SIPI Channel Status Register 0 */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t RAR:1;
      vuint32_t TID:3;                 /* Transaction ID of transmitted frame. */
      vuint32_t ACKR:1;
      vuint32_t CB:1;                  /* Channel Busy. */
      vuint32_t  :2;
    } B;
  } CSR0;

  uint8_t SIPI_reserved0[4];
  union {                              /* SIPI Channel Interrupt Register 0 */
    vuint32_t R;
    struct {
      vuint32_t  :26;
      vuint32_t WAIE:1;                /* Write Acknowledge Interrupt Enable. */
      vuint32_t RAIE:1;                /* Read Answer Interrupt Enable. */
      vuint32_t TCIE:1;                /* Trigger Command Interrupt Enable. */
      vuint32_t TOIE:1;                /* Timeout Error Interrupt Enabled. */
      vuint32_t TIDIE:1;               /* Transaction ID Error Interrupt Enable. */
      vuint32_t ACKIE:1;               /* Acknowledge Error Interrupt Enable. */
    } B;
  } CIR0;

  union {                              /* SIPI Channel Timeout Register 0 */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t TOR:8;                 /* Timeout value for transmitted requests. */
    } B;
  } CTOR0;

  union {                              /* SIPI Channel CRC Register 0 */
    vuint32_t R;
    struct {
      vuint32_t CRCI:16;
      vuint32_t CRCT:16;
    } B;
  } CCRC0;

  union {                              /* SIPI Channel Address Register 0 */
    vuint32_t R;
    struct {
      vuint32_t CAR:32;
    } B;
  } CAR0;

  union {                              /* SIPI Channel Data Register 0 */
    vuint32_t R;
    struct {
      vuint32_t CDR:32;
    } B;
  } CDR0;

  union {                              /* SIPI Channel Control Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :15;
      vuint32_t TC:1;                  /* Send Trigger Command. */
      vuint32_t  :8;
      vuint32_t WL:2;                  /* Word Length Transfer. */
      vuint32_t CHEN:1;                /* Channel Enable. */
      vuint32_t ST:1;
      vuint32_t IDT:1;                 /* ID Read Request Transfer. */
      vuint32_t RRT:1;
      vuint32_t WRT:1;
      vuint32_t DEN:1;                 /* DMA Enable. */
    } B;
  } CCR1;

  union {                              /* SIPI Channel Status Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t RAR:1;
      vuint32_t TID:3;
      vuint32_t ACKR:1;
      vuint32_t CB:1;                  /* Channel Busy. */
      vuint32_t  :2;
    } B;
  } CSR1;

  uint8_t SIPI_reserved1[4];
  union {                              /* SIPI Channel Interrupt Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :26;
      vuint32_t WAIE:1;
      vuint32_t RAIE:1;
      vuint32_t TCIE:1;
      vuint32_t TOIE:1;
      vuint32_t TIDIE:1;
      vuint32_t ACKIE:1;
    } B;
  } CIR1;

  union {                              /* SIPI Channel Timeout Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t TOR:8;                 /* Timeout value for transmitted requests. */
    } B;
  } CTOR1;

  union {                              /* SIPI Channel CRC Register 1 */
    vuint32_t R;
    struct {
      vuint32_t CRCI:16;
      vuint32_t CRCT:16;
    } B;
  } CCRC1;

  union {                              /* SIPI Channel Address Register 1 */
    vuint32_t R;
    struct {
      vuint32_t CAR:32;
    } B;
  } CAR1;

  union {                              /* SIPI Channel Data Register 1 */
    vuint32_t R;
    struct {
      vuint32_t CDR:32;
    } B;
  } CDR1;

  union {                              /* SIPI Channel Control Register 2 */
    vuint32_t R;
    struct {
      vuint32_t  :15;
      vuint32_t TC:1;                  /* Send Trigger Command. */
      vuint32_t  :8;
      vuint32_t WL:2;                  /* Word Length Transfer. */
      vuint32_t CHEN:1;                /* Channel Enable. */
      vuint32_t ST:1;
      vuint32_t IDT:1;                 /* ID Read Request Transfer. */
      vuint32_t RRT:1;                 /* Read Request Transfer. */
      vuint32_t WRT:1;
      vuint32_t DEN:1;
    } B;
  } CCR2;

  union {                              /* SIPI Channel Status Register 2 */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t RAR:1;
      vuint32_t TID:3;                 /* Transaction ID of transmitted frame. */
      vuint32_t ACKR:1;
      vuint32_t CB:1;                  /* Channel Busy. */
      vuint32_t  :2;
    } B;
  } CSR2;

  uint8_t SIPI_reserved2[4];
  union {                              /* SIPI Channel Interrupt Register 2 */
    vuint32_t R;
    struct {
      vuint32_t  :26;
      vuint32_t WAIE:1;
      vuint32_t RAIE:1;
      vuint32_t TCIE:1;
      vuint32_t TOIE:1;
      vuint32_t TIDIE:1;
      vuint32_t ACKIE:1;
    } B;
  } CIR2;

  union {                              /* SIPI Channel Timeout Register 2 */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t TOR:8;
    } B;
  } CTOR2;

  union {                              /* SIPI Channel CRC Register 2 */
    vuint32_t R;
    struct {
      vuint32_t CRCI:16;
      vuint32_t CRCT:16;
    } B;
  } CCRC2;

  union {                              /* SIPI Channel Address Register 2 */
    vuint32_t R;
    struct {
      vuint32_t CAR:32;
    } B;
  } CAR2;

  union {                              /* SIPI Channel Data Register 2 */
    vuint32_t R;
    struct {
      vuint32_t CDR2:32;
    } B;
  } CDR2_[8];

  union {                              /* SIPI Channel Control Register 3 */
    vuint32_t R;
    struct {
      vuint32_t  :15;
      vuint32_t TC:1;                  /* Send Trigger Command. */
      vuint32_t  :8;
      vuint32_t WL:2;                  /* Word Length Transfer. */
      vuint32_t CHEN:1;                /* Channel Enable. */
      vuint32_t ST:1;                  /* Streaming Transfer. */
      vuint32_t IDT:1;                 /* ID Read Request Transfer. */
      vuint32_t RRT:1;
      vuint32_t WRT:1;
      vuint32_t DEN:1;                 /* DMA Enable. */
    } B;
  } CCR3;

  union {                              /* SIPI Channel Status Register 3 */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t RAR:1;
      vuint32_t TID:3;                 /* Transaction ID of transmitted frame. */
      vuint32_t ACKR:1;
      vuint32_t CB:1;                  /* Channel Busy. */
      vuint32_t  :2;
    } B;
  } CSR3;

  uint8_t SIPI_reserved3[4];
  union {                              /* SIPI Channel Interrupt Register 3 */
    vuint32_t R;
    struct {
      vuint32_t  :26;
      vuint32_t WAIE:1;
      vuint32_t RAIE:1;
      vuint32_t TCIE:1;
      vuint32_t TOIE:1;
      vuint32_t TIDIE:1;
      vuint32_t ACKIE:1;
    } B;
  } CIR3;

  union {                              /* SIPI Channel Timeout Register 3 */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t TOR:8;                 /* Timeout value for transmitted requests. */
    } B;
  } CTOR3;

  union {                              /* SIPI Channel CRC Register 3 */
    vuint32_t R;
    struct {
      vuint32_t CRCI:16;
      vuint32_t CRCT:16;
    } B;
  } CCRC3;

  union {                              /* SIPI Channel Address Register 3 */
    vuint32_t R;
    struct {
      vuint32_t CAR:32;
    } B;
  } CAR3;

  union {                              /* SIPI Channel Data Register 3 */
    vuint32_t R;
    struct {
      vuint32_t CDR:32;
    } B;
  } CDR3;

  union {                              /* SIPI Module Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t FRZ:1;                 /* Freeze Enable */
      vuint32_t  :1;
      vuint32_t HALT:1;                /* Halt Mode Enable */
      vuint32_t  :2;
      vuint32_t PRSCLR:11;             /* Timeout counter prescaler */
      vuint32_t AID:2;                 /* Address Increment/Decrement */
      vuint32_t  :3;
      vuint32_t CRCIE:1;               /* CRC Error Interrupt Enable */
      vuint32_t MCRIE:1;               /* Max Count Reached Interrupt Enable */
      vuint32_t  :4;
      vuint32_t CHNSB:1;               /* Channel coding select bit. */
      vuint32_t TEN:1;                 /* Target Enable */
      vuint32_t INIT:1;                /* Initialization Mode */
      vuint32_t MOEN:1;                /* Module Enable */
      vuint32_t SR:1;                  /* Soft Reset */
    } B;
  } MCR;

  union {                              /* SIPI Status Register */
    vuint32_t R;
    struct {
      vuint32_t FRZACK:1;
      vuint32_t LPMACK:1;              /* Low Power Mode Acknowledge. */
      vuint32_t  :19;
      vuint32_t GCRCE:1;
      vuint32_t MCR:1;                 /* Maximum Count Reached. */
      vuint32_t  :1;
      vuint32_t TE:4;
      vuint32_t STATE:4;
    } B;
  } SR;

  union {                              /* SIPI Max Count Register */
    vuint32_t R;
    struct {
      vuint32_t MXCNT:30;
      vuint32_t  :2;
    } B;
  } MAXCR;

  union {                              /* SIPI Address Reload Register */
    vuint32_t R;
    struct {
      vuint32_t ADRLD:30;
      vuint32_t  :2;
    } B;
  } ARR;

  union {                              /* SIPI Address Count Register */
    vuint32_t R;
    struct {
      vuint32_t ADCNT:30;              /* Feflects the count value of address counter at target node. */
      vuint32_t  :2;
    } B;
  } ACR;

  union {                              /* SIPI Error Register */
    vuint32_t R;
    struct {
      vuint32_t  :5;
      vuint32_t TOE3:1;
      vuint32_t TIDE3:1;
      vuint32_t ACKE3:1;
      vuint32_t  :5;
      vuint32_t TOE2:1;
      vuint32_t TIDE2:1;
      vuint32_t ACKE2:1;
      vuint32_t  :5;
      vuint32_t TOE1:1;
      vuint32_t TIDE1:1;
      vuint32_t ACKE1:1;
      vuint32_t  :5;
      vuint32_t TOE0:1;
      vuint32_t TIDE0:1;
      vuint32_t ACKE0:1;
    } B;
  } ERR;
};


/* ============================================================================
   =============================== Module: SIUL2 ==============================
   ============================================================================ */

struct SIUL2_tag {
  uint8_t SIUL2_reserved0[4];
  union {                              /* SIUL2 MCU ID Register #1 */
    vuint32_t R;
    struct {
      vuint32_t PARTNUM:16;            /* MCU Part Number */
      vuint32_t ED:1;
      vuint32_t PKG:5;                 /* Package Settings */
      vuint32_t  :2;
      vuint32_t MAJOR_MASK:4;          /* Major Mask Revision */
      vuint32_t MINOR_MASK:4;          /* Minor Mask Revision */
    } B;
  } MIDR;

  union {                              /* SIUL2 MCU ID Register #2 */
    vuint32_t R;
    struct {
      vuint32_t SF:1;                  /* Manufacturer */
      vuint32_t FLASH_SIZE_1:4;        /* Coarse granularity for flash memory size */
      vuint32_t FLASH_SIZE_2:4;        /* Fine granularity for flash memory size */
      vuint32_t  :7;
      vuint32_t PARTNUM:8;             /* ASCII character in MCU Part Number */
      vuint32_t  :8;
    } B;
  } MIDR2;

  uint8_t SIUL2_reserved1[4];
  union {                              /* SIUL2 DMA/Interrupt Status Flag Register0 */
    vuint32_t R;
    struct {
      vuint32_t EIF31:1;               /* External Interrupt Status Flag 31 */
      vuint32_t EIF30:1;               /* External Interrupt Status Flag 30 */
      vuint32_t EIF29:1;               /* External Interrupt Status Flag 29 */
      vuint32_t EIF28:1;               /* External Interrupt Status Flag 28 */
      vuint32_t EIF27:1;               /* External Interrupt Status Flag 27 */
      vuint32_t EIF26:1;               /* External Interrupt Status Flag 26 */
      vuint32_t EIF25:1;               /* External Interrupt Status Flag 25 */
      vuint32_t EIF24:1;               /* External Interrupt Status Flag 24 */
      vuint32_t EIF23:1;               /* External Interrupt Status Flag 23 */
      vuint32_t EIF22:1;               /* External Interrupt Status Flag 22 */
      vuint32_t EIF21:1;               /* External Interrupt Status Flag 21 */
      vuint32_t EIF20:1;               /* External Interrupt Status Flag 20 */
      vuint32_t EIF19:1;               /* External Interrupt Status Flag 19 */
      vuint32_t EIF18:1;               /* External Interrupt Status Flag 18 */
      vuint32_t EIF17:1;               /* External Interrupt Status Flag 17 */
      vuint32_t EIF16:1;               /* External Interrupt Status Flag 16 */
      vuint32_t EIF15:1;               /* External Interrupt Status Flag 15 */
      vuint32_t EIF14:1;               /* External Interrupt Status Flag 14 */
      vuint32_t EIF13:1;               /* External Interrupt Status Flag 13 */
      vuint32_t EIF12:1;               /* External Interrupt Status Flag 12 */
      vuint32_t EIF11:1;               /* External Interrupt Status Flag 11 */
      vuint32_t EIF10:1;               /* External Interrupt Status Flag 10 */
      vuint32_t EIF9:1;                /* External Interrupt Status Flag 9 */
      vuint32_t EIF8:1;                /* External Interrupt Status Flag 8 */
      vuint32_t EIF7:1;                /* External Interrupt Status Flag 7 */
      vuint32_t EIF6:1;                /* External Interrupt Status Flag 6 */
      vuint32_t EIF5:1;                /* External Interrupt Status Flag 5 */
      vuint32_t EIF4:1;                /* External Interrupt Status Flag 4 */
      vuint32_t EIF3:1;                /* External Interrupt Status Flag 3 */
      vuint32_t EIF2:1;                /* External Interrupt Status Flag 2 */
      vuint32_t EIF1:1;                /* External Interrupt Status Flag 1 */
      vuint32_t EIF0:1;                /* External Interrupt Status Flag 0 */
    } B;
  } DISR0;

  uint8_t SIUL2_reserved2[4];
  union {                              /* SIUL2 DMA/Interrupt Request Enable Register0 */
    vuint32_t R;
    struct {
      vuint32_t EIRE31:1;
      vuint32_t EIRE30:1;
      vuint32_t EIRE29:1;
      vuint32_t EIRE28:1;
      vuint32_t EIRE27:1;
      vuint32_t EIRE26:1;
      vuint32_t EIRE25:1;
      vuint32_t EIRE24:1;
      vuint32_t EIRE23:1;
      vuint32_t EIRE22:1;
      vuint32_t EIRE21:1;
      vuint32_t EIRE20:1;
      vuint32_t EIRE19:1;
      vuint32_t EIRE18:1;
      vuint32_t EIRE17:1;
      vuint32_t EIRE16:1;
      vuint32_t EIRE15:1;
      vuint32_t EIRE14:1;
      vuint32_t EIRE13:1;
      vuint32_t EIRE12:1;
      vuint32_t EIRE11:1;
      vuint32_t EIRE10:1;
      vuint32_t EIRE9:1;
      vuint32_t EIRE8:1;
      vuint32_t EIRE7:1;
      vuint32_t EIRE6:1;
      vuint32_t EIRE5:1;
      vuint32_t EIRE4:1;
      vuint32_t EIRE3:1;
      vuint32_t EIRE2:1;
      vuint32_t EIRE1:1;
      vuint32_t EIRE0:1;
    } B;
  } DIRER0;

  uint8_t SIUL2_reserved3[4];
  union {                              /* SIUL2 DMA/Interrupt Request Select Register0 */
    vuint32_t R;
    struct {
      vuint32_t DIRSR31:1;
      vuint32_t DIRSR30:1;
      vuint32_t DIRSR29:1;
      vuint32_t DIRSR28:1;
      vuint32_t DIRSR27:1;
      vuint32_t DIRSR26:1;
      vuint32_t DIRSR25:1;
      vuint32_t DIRSR24:1;
      vuint32_t DIRSR23:1;
      vuint32_t DIRSR22:1;
      vuint32_t DIRSR21:1;
      vuint32_t DIRSR20:1;
      vuint32_t DIRSR19:1;
      vuint32_t DIRSR18:1;
      vuint32_t DIRSR17:1;
      vuint32_t DIRSR16:1;
      vuint32_t DIRSR15:1;
      vuint32_t DIRSR14:1;
      vuint32_t DIRSR13:1;
      vuint32_t DIRSR12:1;
      vuint32_t DIRSR11:1;
      vuint32_t DIRSR10:1;
      vuint32_t DIRSR9:1;
      vuint32_t DIRSR8:1;
      vuint32_t DIRSR7:1;
      vuint32_t DIRSR6:1;
      vuint32_t DIRSR5:1;
      vuint32_t DIRSR4:1;
      vuint32_t DIRSR3:1;
      vuint32_t DIRSR2:1;
      vuint32_t DIRSR1:1;
      vuint32_t DIRSR0:1;
    } B;
  } DIRSR0;

  uint8_t SIUL2_reserved4[4];
  union {                              /* SIUL2 Interrupt Rising-Edge Event Enable Register 0 */
    vuint32_t R;
    struct {
      vuint32_t IREE31:1;
      vuint32_t IREE30:1;
      vuint32_t IREE29:1;
      vuint32_t IREE28:1;
      vuint32_t IREE27:1;
      vuint32_t IREE26:1;
      vuint32_t IREE25:1;
      vuint32_t IREE24:1;
      vuint32_t IREE23:1;
      vuint32_t IREE22:1;
      vuint32_t IREE21:1;
      vuint32_t IREE20:1;
      vuint32_t IREE19:1;
      vuint32_t IREE18:1;
      vuint32_t IREE17:1;
      vuint32_t IREE16:1;
      vuint32_t IREE15:1;
      vuint32_t IREE14:1;
      vuint32_t IREE13:1;
      vuint32_t IREE12:1;
      vuint32_t IREE11:1;
      vuint32_t IREE10:1;
      vuint32_t IREE9:1;
      vuint32_t IREE8:1;
      vuint32_t IREE7:1;
      vuint32_t IREE6:1;
      vuint32_t IREE5:1;
      vuint32_t IREE4:1;
      vuint32_t IREE3:1;
      vuint32_t IREE2:1;
      vuint32_t IREE1:1;
      vuint32_t IREE0:1;
    } B;
  } IREER0;

  uint8_t SIUL2_reserved5[4];
  union {                              /* SIUL2 Interrupt Falling-Edge Event Enable Register 0 */
    vuint32_t R;
    struct {
      vuint32_t IFEE31:1;
      vuint32_t IFEE30:1;
      vuint32_t IFEE29:1;
      vuint32_t IFEE28:1;
      vuint32_t IFEE27:1;
      vuint32_t IFEE26:1;
      vuint32_t IFEE25:1;
      vuint32_t IFEE24:1;
      vuint32_t IFEE23:1;
      vuint32_t IFEE22:1;
      vuint32_t IFEE21:1;
      vuint32_t IFEE20:1;
      vuint32_t IFEE19:1;
      vuint32_t IFEE18:1;
      vuint32_t IFEE17:1;
      vuint32_t IFEE16:1;
      vuint32_t IFEE15:1;
      vuint32_t IFEE14:1;
      vuint32_t IFEE13:1;
      vuint32_t IFEE12:1;
      vuint32_t IFEE11:1;
      vuint32_t IFEE10:1;
      vuint32_t IFEE9:1;
      vuint32_t IFEE8:1;
      vuint32_t IFEE7:1;
      vuint32_t IFEE6:1;
      vuint32_t IFEE5:1;
      vuint32_t IFEE4:1;
      vuint32_t IFEE3:1;
      vuint32_t IFEE2:1;
      vuint32_t IFEE1:1;
      vuint32_t IFEE0:1;
    } B;
  } IFEER0;

  uint8_t SIUL2_reserved6[4];
  union {                              /* SIUL2 Interrupt Filter Enable Register 0 */
    vuint32_t R;
    struct {
      vuint32_t IFE31:1;
      vuint32_t IFE30:1;
      vuint32_t IFE29:1;
      vuint32_t IFE28:1;
      vuint32_t IFE27:1;
      vuint32_t IFE26:1;
      vuint32_t IFE25:1;
      vuint32_t IFE24:1;
      vuint32_t IFE23:1;
      vuint32_t IFE22:1;
      vuint32_t IFE21:1;
      vuint32_t IFE20:1;
      vuint32_t IFE19:1;
      vuint32_t IFE18:1;
      vuint32_t IFE17:1;
      vuint32_t IFE16:1;
      vuint32_t IFE15:1;
      vuint32_t IFE14:1;
      vuint32_t IFE13:1;
      vuint32_t IFE12:1;
      vuint32_t IFE11:1;
      vuint32_t IFE10:1;
      vuint32_t IFE9:1;
      vuint32_t IFE8:1;
      vuint32_t IFE7:1;
      vuint32_t IFE6:1;
      vuint32_t IFE5:1;
      vuint32_t IFE4:1;
      vuint32_t IFE3:1;
      vuint32_t IFE2:1;
      vuint32_t IFE1:1;
      vuint32_t IFE0:1;
    } B;
  } IFER0;

  uint8_t SIUL2_reserved7[4];
  union {                              /* SIUL2 Interrupt Filter Maximum Counter Register */
    vuint32_t R;
    struct {
      vuint32_t  :28;
      vuint32_t MAXCNT:4;              /* Maximum Interrupt Filter Counter setting */
    } B;
  } IFMCR[32];

  union {                              /* SIUL2 Interrupt Filter Clock Prescaler Register */
    vuint32_t R;
    struct {
      vuint32_t  :28;
      vuint32_t IFCP:4;                /* Interrupt Filter Clock Prescaler setting */
    } B;
  } IFCPR;

  uint8_t SIUL2_reserved8[380];

/*******************************************************************************
*   Unimplemented registers should not be accessed by the user. Refer to the   *
*     Reference Manual for the implemented SIUL2 MSCR and IMCR registers.      *
* *****************************************************************************/

  union {                              /* SIUL2 Multiplexed Signal Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :2;
      vuint32_t SRC:2;                 /* Slew Rate Control */
      vuint32_t  :2;
      vuint32_t OBE:1;                 /* GPIO Output Buffer Enable */
      vuint32_t ODE:1;                 /* Open Drain Enable */
      vuint32_t SMC:1;                 /* Safe Mode Control */
      vuint32_t APC:1;                 /* Analog Pad Control */
      vuint32_t  :2;
      vuint32_t IBE:1;                 /* Input Buffer Enable */
      vuint32_t HYS:1;                 /* Input Hysteresis */
      vuint32_t PUS:1;                 /* Pull Select */
      vuint32_t PUE:1;                 /* Pull Enable */
      vuint32_t INV:1;                 /* Invert */
      vuint32_t  :7;
      vuint32_t  :4;
      vuint32_t SSS:4;                 /* Source Signal Select */
    } B;
  } PCR[155];
//} MSCR[155];

  uint8_t SIUL2_reserved9[1428];

/*******************************************************************************
*   Unimplemented registers should not be accessed by the user. Refer to the   *
*     Reference Manual for the implemented SIUL2 MSCR and IMCR registers.      *
* *****************************************************************************/

  union {                              /* SIUL2 Input Multiplexed Signal Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t INV:1;                 /* Invert */
      vuint32_t  :7;
      vuint32_t  :4;
      vuint32_t SSS:4;                 /* Source Signal Select */
    } B;
//  } IMCR[234];
  } PSMI[234]; /* Pad Selection for Multiplexed Input Register */
  uint8_t SIUL2_reserved10[1304];
  union {
    vuint8_t R;
      struct {
        vuint8_t  :7;					 /*  */
        vuint8_t PDO:1;					 /* Pad Data Out */
    } B;
  } GPDO[156];

  uint8_t SIUL2_reserved11[356];
  union {
    vuint8_t R;
      struct {
        vuint8_t  :7;					 /*  */
        vuint8_t PDI:1;					 /* Pad Data In */
    } B;
  } GPDI[156];

  uint8_t SIUL2_reserved12[356];
  union {                              /* SIUL2 Parallel GPIO Pad Data Out Register */
    vuint16_t R;
    struct {
      vuint16_t PPDO:16;               /* Parallel Pad Data Out */
    } B;
  } PGPDO[10];

  uint8_t SIUL2_reserved13[44];
  union {                              /* SIUL2 Parallel GPIO Pad Data In Register */
    vuint16_t R;
    struct {
      vuint16_t PPDI:16;               /* Parallel Pad Data In */
    } B;
  } PGPDI[10];

  uint8_t SIUL2_reserved14[44];
  union {                              /* SIUL2 Masked Parallel GPIO Pad Data Out Register */
    vuint32_t R;
    struct {
      vuint32_t MASK:16;               /* Mask Field */
      vuint32_t MPPDO:16;              /* Masked Parallel Pad Data Out */
    } B;
  } MPGPDO[10];
};


/* ============================================================================
   =============================== Module: SMPU ===============================
   ============================================================================ */

struct SMPU_tag {
  union {                              /* Control/Error Status Register 0 */
    vuint32_t R;
    struct {
      vuint32_t MERR:16;               /* Master n error, where the bus master number matches the bit number */
      vuint32_t  :1;
      vuint32_t  :11;
      vuint32_t HRL:3;                 /* Hardware revision level */
      vuint32_t GVLD:1;                /* Global Valid (global enable/disable for the SMPU) */
    } B;
  } CESR0;

  union {                              /* Control/Error Status Register 1 */
    vuint32_t R;
    struct {
      vuint32_t MEOVR:16;              /* Master n error overrun, where the bus master number matches the bit number */
      vuint32_t  :1;
      vuint32_t  :11;
      vuint32_t NRGD:4;                /* Number of region descriptors */
    } B;
  } CESR1;

  uint8_t SMPU_reserved0[248];
  struct {
    union {                            /* Error Address Register, Bus Master n */
      vuint32_t R;
      struct {
        vuint32_t EADDR:32;            /* Error address */
      } B;
    } EAR;
    union {                            /* Error Detail Register, Bus Master n */
      vuint32_t R;
      struct {
        vuint32_t EACD:24;             /* Error access control detail */
        vuint32_t  :1;
        vuint32_t EATTR:2;             /* Error attributes */
        vuint32_t ERW:1;               /* Error read/write */
        vuint32_t EMN:4;               /* Error master number */
      } B;
    } EDR;
  } ERROR[16];

  uint8_t SMPU_reserved1[640];
  struct {
    union {                            /* Region Descriptor n, Word 0 */
      vuint32_t R;
      struct {
        vuint32_t SRTADDR:32;          /* Start address */
      } B;
    } WORD0;
    union {                            /* Region Descriptor n, Word 1 */
      vuint32_t R;
      struct {
        vuint32_t ENDADDR:32;          /* End address */
      } B;
    } WORD1;
    union {                            /* Region Descriptor n, Word 2 */
      vuint32_t R;
      struct {
        vuint32_t M0P:2;               /* Bus master 0 permissions */
        vuint32_t M1P:2;               /* Bus master 1 permissions */
        vuint32_t M2P:2;               /* Bus master 2 permissions */
        vuint32_t M3P:2;               /* Bus master 3 permissions */
        vuint32_t M4P:2;               /* Bus master 4 permissions */
        vuint32_t M5P:2;               /* Bus master 5 permissions */
        vuint32_t M6P:2;               /* Bus master 6 permissions */
        vuint32_t M7P:2;               /* Bus master 7 permissions */
        vuint32_t M8P:2;               /* Bus master 8 permissions */
        vuint32_t M9P:2;               /* Bus master 9 permissions */
        vuint32_t M10P:2;              /* Bus master 10 permissions */
        vuint32_t M11P:2;              /* Bus master 11 permissions */
        vuint32_t M12P:2;              /* Bus master 12 permissions */
        vuint32_t M13P:2;              /* Bus master 13 permissions */
        vuint32_t M14P:2;              /* Bus master 14 permissions */
        vuint32_t M15P:2;              /* Bus master 15 permissions */
      } B;
    } WORD2;
    union {                            /* Region Descriptor n, Word 3 */
      vuint32_t R;
      struct {
        vuint32_t  :28;
        vuint32_t RO:1;                /* Read-Only */
        vuint32_t  :1;
        vuint32_t CI:1;                /* Cache Inhibit */
        vuint32_t VLD:1;               /* Valid */
      } B;
    } WORD3;
  } RGD[16];
};


/* ============================================================================
   =============================== Module: SPI ================================
   ============================================================================ */

struct DSPI_tag {
  union {                              /* Module Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t MSTR:1;                /* Master/Slave Mode Select */
      vuint32_t CONT_SCKE:1;           /* Continuous SCK Enable */
      vuint32_t DCONF:2;               /* SPI Configuration. */
      vuint32_t FRZ:1;                 /* Freeze */
      vuint32_t MTFE:1;                /* Modified Timing Format Enable */
      vuint32_t  :1;
      vuint32_t ROOE:1;                /* Receive FIFO Overflow Overwrite Enable */
      vuint32_t PCSIS7:1;
      vuint32_t PCSIS6:1;
      vuint32_t PCSIS5:1;
      vuint32_t PCSIS4:1;
      vuint32_t PCSIS3:1;
      vuint32_t PCSIS2:1;
      vuint32_t PCSIS1:1;
      vuint32_t PCSIS0:1;
      vuint32_t  :1;
      vuint32_t MDIS:1;                /* Module Disable */
      vuint32_t DIS_TXF:1;             /* Disable Transmit FIFO */
      vuint32_t DIS_RXF:1;             /* Disable Receive FIFO */
      vuint32_t CLR_TXF:1;             /* Clear TX FIFO */
      vuint32_t CLR_RXF:1;
      vuint32_t SMPL_PT:2;             /* Sample Point */
      vuint32_t  :5;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t HALT:1;                /* Halt */
    } B;
  } MCR;

  uint8_t SPI_reserved0[4];
  union {                              /* Transfer Count Register */
    vuint32_t R;
    struct {
      vuint32_t SPI_TCNT:16;           /* SPI Transfer Counter */
      vuint32_t  :16;
    } B;
  } TCR;

  union {
    union {                            /* Clock and Transfer Attributes Register (In Master Mode) */
      vuint32_t R;
      struct {
        vuint32_t DBR:1;               /* Double Baud Rate */
        vuint32_t FMSZ:4;              /* Frame Size */
        vuint32_t CPOL:1;              /* Clock Polarity */
        vuint32_t CPHA:1;              /* Clock Phase */
        vuint32_t LSBFE:1;             /* LSB First */
        vuint32_t PCSSCK:2;            /* PCS to SCK Delay Prescaler */
        vuint32_t PASC:2;              /* After SCK Delay Prescaler */
        vuint32_t PDT:2;               /* Delay after Transfer Prescaler */
        vuint32_t PBR:2;               /* Baud Rate Prescaler */
        vuint32_t CSSCK:4;             /* PCS to SCK Delay Scaler */
        vuint32_t ASC:4;               /* After SCK Delay Scaler */
        vuint32_t DT:4;                /* Delay After Transfer Scaler */
        vuint32_t BR:4;                /* Baud Rate Scaler */
      } B;
    } CTAR[4];
    union {                            /* Clock and Transfer Attributes Register (In Slave Mode) */
      vuint32_t R;
      struct {
        vuint32_t FMSZ:5;              /* Frame Size */
        vuint32_t CPOL:1;              /* Clock Polarity */
        vuint32_t CPHA:1;              /* Clock Phase */
        vuint32_t  :2;
        vuint32_t  :1;
        vuint32_t  :22;
      } B;
    } CTAR_SLAVE[1];
  };

  uint8_t SPI_reserved1[16];
  union {                              /* Status Register */
    vuint32_t R;
    struct {
      vuint32_t TCF:1;                 /* Transfer Complete Flag */
      vuint32_t TXRXS:1;               /* TX and RX Status */
      vuint32_t  :1;
      vuint32_t EOQF:1;                /* End of Queue Flag */
      vuint32_t TFUF:1;                /* Transmit FIFO Underflow Flag */
      vuint32_t  :1;
      vuint32_t TFFF:1;                /* Transmit FIFO Fill Flag */
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t RFOF:1;                /* Receive FIFO Overflow Flag */
      vuint32_t  :1;
      vuint32_t RFDF:1;                /* Receive FIFO Drain Flag */
      vuint32_t  :1;
      vuint32_t TXCTR:4;               /* TX FIFO Counter */
      vuint32_t TXNXTPTR:4;            /* Transmit Next Pointer */
      vuint32_t RXCTR:4;               /* RX FIFO Counter */
      vuint32_t POPNXTPTR:4;           /* Pop Next Pointer */
    } B;
  } SR;

  union {                              /* DMA/Interrupt Request Select and Enable Register */
    vuint32_t R;
    struct {
      vuint32_t TCF_RE:1;              /* Transmission Complete Request Enable */
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t EOQF_RE:1;             /* Finished Request Enable */
      vuint32_t TFUF_RE:1;             /* Transmit FIFO Underflow Request Enable */
      vuint32_t  :1;
      vuint32_t TFFF_RE:1;             /* Transmit FIFO Fill Request Enable */
      vuint32_t TFFF_DIRS:1;           /* Transmit FIFO Fill DMA or Interrupt Request Select */
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t RFOF_RE:1;             /* Receive FIFO Overflow Request Enable */
      vuint32_t  :1;
      vuint32_t RFDF_RE:1;             /* Receive FIFO Drain Request Enable */
      vuint32_t RFDF_DIRS:1;           /* Receive FIFO Drain DMA or Interrupt Request Select */
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :14;
    } B;
  } RSER;

  union {
    union {                            /* PUSH TX FIFO Register In Master Mode */
      vuint32_t R;
      struct {
        vuint32_t CONT:1;              /* Continuous Peripheral Chip Select Enable */
        vuint32_t CTAS:3;              /* Clock and Transfer Attributes Select */
        vuint32_t EOQ:1;               /* End Of Queue */
        vuint32_t CTCNT:1;             /* Clear Transfer Counter */
        vuint32_t  :2;
        vuint32_t PCS:8;
        vuint32_t TXDATA:16;           /* Transmit Data */
      } B;
    } PUSHR;
    union {                            /* PUSH TX FIFO Register In Slave Mode */
      vuint32_t R;
      struct {
        vuint32_t TXDATA:32;           /* Transmit Data */
      } B;
    } PUSHR_SLAVE;
  };

  union {                              /* POP RX FIFO Register */
    vuint32_t R;
    struct {
      vuint32_t RXDATA:32;             /* Received Data */
    } B;
  } POPR;

  union {                              /* Transmit FIFO Registers */
    vuint32_t R;
    struct {
      vuint32_t TXCMD_TXDATA:16;       /* Transmit Command or Transmit Data */
      vuint32_t TXDATA:16;             /* Transmit Data */
    } B;
  } TXFR[5];

  uint8_t SPI_reserved2[44];
  union {                              /* Receive FIFO Registers */
    vuint32_t R;
    struct {
      vuint32_t RXDATA:32;             /* Receive Data */
    } B;
  } RXFR[5];
};


/* ============================================================================
   =============================== Module: SRX ================================
   ============================================================================ */

struct SRX_tag {
  union {                              /* Global Control Register */
    vuint32_t R;
    struct {
      vuint32_t TSPRSC:8;
      vuint32_t  :3;
      vuint32_t FIFOWM:5;
      vuint32_t  :5;
      vuint32_t FMFOIE:1;
      vuint32_t FMDUIE:1;
      vuint32_t SMDUIE:1;
      vuint32_t  :1;
      vuint32_t FIFO_EN:1;
      vuint32_t  :1;
      vuint32_t FAST_CLR:1;
      vuint32_t  :1;
      vuint32_t DBG_FRZ:1;
      vuint32_t  :1;
      vuint32_t SENT_EN:1;
    } B;
  } GBL_CTRL;

  union {                              /* Channel Enable Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t EN_CH:16;
    } B;
  } CHNL_EN;

  union {                              /* Global Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :21;
      vuint32_t FMFO:1;
      vuint32_t FDMU:1;
      vuint32_t SMDU:1;
      vuint32_t  :8;
    } B;
  } GBL_STATUS;

  union {                              /* Fast Message Ready Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t F_RDY:16;
    } B;
  } FMSG_RDY;

  union {                              /* Slow Serial Message Ready Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t S_RDY:16;
    } B;
  } SMSG_RDY;

  uint8_t SRX_reserved0[4];
  union {                              /* Data Control Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t NIBBCH0:3;
      vuint32_t  :1;
      vuint32_t NIBBCH1:3;
      vuint32_t  :1;
      vuint32_t NIBBCH2:3;
      vuint32_t  :1;
      vuint32_t NIBBCH3:3;
      vuint32_t  :1;
      vuint32_t NIBBCH4:3;
      vuint32_t  :1;
      vuint32_t NIBBCH5:3;
      vuint32_t  :1;
      vuint32_t NIBBCH6:3;
      vuint32_t  :1;
      vuint32_t NIBBCH7:3;
    } B;
  } DATA_CTRL1;

  union {                              /* Data Control Register 2 */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t NIBBCH8:3;
      vuint32_t  :1;
      vuint32_t NIBBCH9:3;
      vuint32_t  :1;
      vuint32_t NIBBCH10:3;
      vuint32_t  :1;
      vuint32_t NIBBCH11:3;
      vuint32_t  :1;
      vuint32_t NIBBCH12:3;
      vuint32_t  :1;
      vuint32_t NIBBCH13:3;
      vuint32_t  :1;
      vuint32_t NIBBCH14:3;
      vuint32_t  :1;
      vuint32_t NIBBCH15:3;
    } B;
  } DATA_CTRL2;

  uint8_t SRX_reserved1[8];
  union {                              /* Fast Message DMA Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t FDMA_EN:16;
    } B;
  } FDMA_CTRL;

  union {                              /* Slow Serial Message DMA Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t SDMA_EN:16;
    } B;
  } SDMA_CTRL;

  uint8_t SRX_reserved2[4];
  union {                              /* Fast Message Ready Interrupt Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t FRDY_IE:16;
    } B;
  } FRDY_IE;

  union {                              /* Slow Serial Message Ready Interrupt Enable Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t SRDY_IE:16;
    } B;
  } SRDY_IE;

  uint8_t SRX_reserved3[4];
  union {                              /* DMA Fast Message Data Read Register */
    vuint32_t R;
    struct {
      vuint32_t CHNUM:4;
      vuint32_t SCNIB:4;
      vuint32_t DNIB1:4;
      vuint32_t DNIB2:4;
      vuint32_t DNIB3:4;
      vuint32_t DNIB4:4;
      vuint32_t DNIB5:4;
      vuint32_t DNIB6:4;
    } B;
  } DMA_FMSG_DATA;

  union {                              /* DMA Fast Message CRC Read Register */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t CRC4b:4;
      vuint32_t  :16;
    } B;
  } DMA_FMSG_CRC;

  union {                              /* DMA Fast Message Time Stamp Read Register */
    vuint32_t R;
    struct {
      vuint32_t TS:32;
    } B;
  } DMA_FMSG_TS;

  uint8_t SRX_reserved4[4];
  union {                              /* DMA Slow Serial Message Bit3 Read Register */
    vuint32_t R;
    struct {
      vuint32_t CHNUM:4;
      vuint32_t TYPE:1;
      vuint32_t  :16;
      vuint32_t CFG:1;
      vuint32_t ID7_4_D3_0:4;
      vuint32_t  :1;
      vuint32_t ID3_0_DATA15_12:4;
      vuint32_t  :1;
    } B;
  } DMA_SMSG_BIT3;

  union {                              /* DMA Slow Serial Message Bit2 Read Register */
    vuint32_t R;
    struct {
      vuint32_t  :10;
      vuint32_t SMCRC:6;
      vuint32_t  :4;
      vuint32_t DATA:12;
    } B;
  } DMA_SMSG_BIT2;

  union {                              /* DMA Slow Serial Message Time Stamp Read Register */
    vuint32_t R;
    struct {
      vuint32_t TS:32;
    } B;
  } DMA_SMSG_TS;

  uint8_t SRX_reserved5[4];
  struct {
    union {                            /* Channel 'n' Clock Control Register (n = 0 to (CH-1)) */
      vuint32_t R;
      struct {
        vuint32_t  :1;
        vuint32_t CM_PRSC:15;
        vuint32_t COMP_EN:1;
        vuint32_t  :1;
        vuint32_t PRSC:14;
      } B;
    } CLK_CTRL;
    union {                            /* Channel 'n' Status Register (n=0 to (CH-1)) */
      vuint32_t R;
      struct {
        vuint32_t BUS_IDLE:1;
        vuint32_t  :3;
        vuint32_t CAL_RESYNC:1;
        vuint32_t CAL_20_25:1;
        vuint32_t SMSG_OFLW:1;
        vuint32_t FMSG_OFLW:1;
        vuint32_t  :1;
        vuint32_t PP_DIAG_ERR:1;
        vuint32_t CAL_LEN_ERR:1;
        vuint32_t CAL_DIAG_ERR:1;
        vuint32_t NIB_VAL_ERR:1;
        vuint32_t SMSG_CRC_ERR:1;
        vuint32_t FMSG_CRC_ERR:1;
        vuint32_t NUM_EDGES_ERR:1;
        vuint32_t  :16;
      } B;
    } STATUS;
    union {                            /* Channel 'n' Configuration Register (n=0 to (CH-1)) */
      vuint32_t R;
      struct {
        vuint32_t BUS_IDLE_CNT:4;
        vuint32_t IE_CAL_RESYNC:1;
        vuint32_t IE_CAL_20_25:1;
        vuint32_t IE_SMSG_OFLW:1;
        vuint32_t IE_FMSG_OFLW:1;
        vuint32_t FCRC_CHK_OFF:1;
        vuint32_t IE_PP_DIAG_ERR:1;
        vuint32_t IE_CAL_LEN_ERR:1;
        vuint32_t IE_CAL_DIAG_ERR:1;
        vuint32_t IE_NIB_VAL_ERR:1;
        vuint32_t IE_SMSG_CRC_ERR:1;
        vuint32_t IE_FMSG_CRC_ERR:1;
        vuint32_t IE_NUM_EDGES_ERR:1;
        vuint32_t DCHNG_INT:1;
        vuint32_t CAL_RNG:1;
        vuint32_t PP_CHKSEL:1;
        vuint32_t FCRC_TYPE:1;
        vuint32_t FCRC_SC_EN:1;
        vuint32_t SCRC_TYPE:1;
        vuint32_t PAUSE_EN:1;
        vuint32_t SUCC_CAL_CHK:1;
        vuint32_t FIL_CNT:8;
      } B;
    } CONFIG;
    uint8_t CH_reserved0[4];
  } CH[16];

  struct {
    union {                            /* Channel 'n' Fast Message Data Read Register (n=0 to (CH-1)) */
      vuint32_t R;
      struct {
        vuint32_t CHNUM:4;
        vuint32_t SCNIB:4;
        vuint32_t DNIB1:4;
        vuint32_t DNIB2:4;
        vuint32_t DNIB3:4;
        vuint32_t DNIB4:4;
        vuint32_t DNIB5:4;
        vuint32_t DNIB6:4;
      } B;
    } FMSG_DATA;
    union {                            /* Channel 'n' Fast Message CRC Read Register (n=0 to (CH-1)) */
      vuint32_t R;
      struct {
        vuint32_t  :12;
        vuint32_t CRC4b:4;
        vuint32_t  :16;
      } B;
    } FMSG_CRC;
    union {                            /* Channel 'n' Fast Message Time Stamp Read Register (n=0 to (CH-1)) */
      vuint32_t R;
      struct {
        vuint32_t TS:32;
      } B;
    } FMSG_TS;
    union {                            /* Channel 'n' Serial Message Read Register (Bit 3) (n=0 to (CH-1)) */
      vuint32_t R;
      struct {
        vuint32_t CHNUM:4;
        vuint32_t TYPE:1;
        vuint32_t  :16;
        vuint32_t CFG:1;
        vuint32_t ID7_4_ID3_0:4;
        vuint32_t  :1;
        vuint32_t ID3_0_DATA15_12:4;
        vuint32_t  :1;
      } B;
    } SMSG_BIT3;
    union {                            /* Channel 'n' Serial Message Read Register (Bit 2)(n=0 to (CH-1)) */
      vuint32_t R;
      struct {
        vuint32_t  :10;
        vuint32_t SMCRC:6;
        vuint32_t  :4;
        vuint32_t DATA:12;
      } B;
    } SMSG_BIT2;
    union {                            /* Channel 'n' Serial Message Time Stamp Read Register (n=0 to (CH-1)) */
      vuint32_t R;
      struct {
        vuint32_t TS:32;
      } B;
    } SMSG_TS;
  } CHANNEL[16];
};


/* ============================================================================
   =============================== Module: SSCM ===============================
   ============================================================================ */

struct SSCM_tag {
  union {                              /* SSCM System Status */
    vuint16_t R;
    struct {
      vuint16_t  :1;
      vuint16_t CER:1;                 /* Configuration Error */
      vuint16_t CERS:1;                /* Configuration Error for Safe DCF Clients */
      vuint16_t  :1;
      vuint16_t NXEN:1;                /* Processor 0 Nexus enable status */
      vuint16_t PUB:1;                 /* Public Serial Access Status */
      vuint16_t SEC:1;                 /* Security Status */
      vuint16_t  :1;
      vuint16_t BMODE:3;               /* Device Boot Mode */
      vuint16_t VLE:1;
      vuint16_t  :1;
      vuint16_t  :1;
      vuint16_t  :2;
    } B;
  } STATUS;

  union {                              /* SSCM System Memory and ID Register */
    vuint16_t R;
    struct {
      vuint16_t JPIN:10;
      vuint16_t IVLD:1;                /* Instruction flash memory Valid */
      vuint16_t MREV:4;                /* Minor Mask Revision */
      vuint16_t DVLD:1;                /* Data flash memory Valid */
    } B;
  } MEMCONFIG;

  uint8_t SSCM_reserved0[2];
  union {                              /* SSCM Error Configuration Register */
    vuint16_t R;
    struct {
      vuint16_t  :14;
      vuint16_t PAE:1;                 /* Peripheral Bus Abort Enable. */
      vuint16_t RAE:1;                 /* Register Bus Abort Enable. */
    } B;
  } ERROR;

  union {                              /* SSCM Debug Status Port Register */
    vuint16_t R;
    struct {
      vuint16_t  :13;
      vuint16_t DEBUG_MODE:3;
    } B;
  } DEBUGPORT;

  uint8_t SSCM_reserved1[22];
  union {                              /* User Option Status Register */
    vuint32_t R;
    struct {
      vuint32_t UOPT:32;               /* Shows the values read from the User Option Bits location in the flash memory. */
    } B;
  } UOPS;

  uint8_t SSCM_reserved2[4];
  union {                              /* Processor Start Address Register */
    vuint32_t R;
    struct {
      vuint32_t SADR:32;               /* Processor Start Address */
    } B;
  } PSA;
};


/* ============================================================================
   =============================== Module: STCU ===============================
   ============================================================================ */

struct STCU_tag {
  uint8_t STCU_reserved0[4];
  union {                              /* STCU2 Run Software Register */
    vuint32_t R;
    struct {
      vuint32_t  :20;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t MBSWPLLEN:1;
      vuint32_t LBSWPLLEN:1;
      vuint32_t  :6;
      vuint32_t  :1;
      vuint32_t RUNSW:1;
    } B;
  } RUNSW;

  union {                              /* STCU2 SK Code Register */
    vuint32_t R;
    struct {
      vuint32_t SKC:32;
    } B;
  } SKC;

  union {                              /* STCU2 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PTR:7;
      vuint32_t LB_DELAY:8;
      vuint32_t  :7;
      vuint32_t WRP:1;
      vuint32_t  :2;
      vuint32_t  :1;
      vuint32_t PMOSEN:1;
      vuint32_t MBU:1;
      vuint32_t CLK_CFG:3;
    } B;
  } CFG;

  uint8_t STCU_reserved1[4];
  union {                              /* STCU2 Watchdog Register Granularity */
    vuint32_t R;
    struct {
      vuint32_t WDGEOC:32;
    } B;
  } WDG;

  uint8_t STCU_reserved2[12];
  union {                              /* STCU2 Error Register */
    vuint32_t R;
    struct {
      vuint32_t  :6;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :3;
      vuint32_t LOCKESW:1;
      vuint32_t WDTOSW:1;
      vuint32_t  :1;
      vuint32_t ENGESW:1;
      vuint32_t INVPSW:1;
      vuint32_t  :6;
      vuint32_t CFSF:1;
      vuint32_t NCFSF:1;
      vuint32_t  :3;
      vuint32_t LOCKE:1;
      vuint32_t WDTO:1;
      vuint32_t  :1;
      vuint32_t ENGE:1;
      vuint32_t INVP:1;
    } B;
  } ERR_STAT;

  uint8_t STCU_reserved3[4];
  union {                              /* STCU2 Startup LBIST Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :28;
      vuint32_t LBS3:1;
      vuint32_t LBS2:1;
      vuint32_t LBS1:1;
      vuint32_t LBS0:1;
    } B;
  } LBS;

  union {                              /* STCU2 Startup LBIST End Flag Register */
    vuint32_t R;
    struct {
      vuint32_t  :28;
      vuint32_t LBE3:1;
      vuint32_t LBE2:1;
      vuint32_t LBE1:1;
      vuint32_t LBE0:1;
    } B;
  } LBE;

  union {                              /* STCU2 Shutdown LBIST Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :28;
      vuint32_t LBSSW3:1;
      vuint32_t LBSSW2:1;
      vuint32_t LBSSW1:1;
      vuint32_t LBSSW0:1;
    } B;
  } LBSSW;

  union {                              /* STCU2 Shutdown LBIST End Flag Register */
    vuint32_t R;
    struct {
      vuint32_t  :28;
      vuint32_t LBESW3:1;
      vuint32_t LBESW2:1;
      vuint32_t LBESW1:1;
      vuint32_t LBESW0:1;
    } B;
  } LBESW;

  union {                              /* STCU2 Shutdown LBIST Reset Management */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t LBRMSW15:1;
      vuint32_t LBRMSW14:1;
      vuint32_t LBRMSW13:1;
      vuint32_t LBRMSW12:1;
      vuint32_t LBRMSW11:1;
      vuint32_t LBRMSW10:1;
      vuint32_t LBRMSW9:1;
      vuint32_t LBRMSW8:1;
      vuint32_t LBRMSW7:1;
      vuint32_t LBRMSW6:1;
      vuint32_t LBRMSW5:1;
      vuint32_t LBRMSW4:1;
      vuint32_t LBRMSW3:1;
      vuint32_t LBRMSW2:1;
      vuint32_t LBRMSW1:1;
      vuint32_t LBRMSW0:1;
    } B;
  } LBRMSW;

  uint8_t STCU_reserved4[4];
  union {                              /* STCU2 Startup MBIST Status Low Register */
    vuint32_t R;
    struct {
      vuint32_t  :5;
      vuint32_t MBS26:1;
      vuint32_t MBS25:1;
      vuint32_t MBS24:1;
      vuint32_t MBS23:1;
      vuint32_t MBS22:1;
      vuint32_t MBS21:1;
      vuint32_t MBS20:1;
      vuint32_t MBS19:1;
      vuint32_t MBS18:1;
      vuint32_t MBS17:1;
      vuint32_t MBS16:1;
      vuint32_t MBS15:1;
      vuint32_t MBS14:1;
      vuint32_t MBS13:1;
      vuint32_t MBS12:1;
      vuint32_t MBS11:1;
      vuint32_t MBS10:1;
      vuint32_t MBS9:1;
      vuint32_t MBS8:1;
      vuint32_t MBS7:1;
      vuint32_t MBS6:1;
      vuint32_t MBS5:1;
      vuint32_t MBS4:1;
      vuint32_t MBS3:1;
      vuint32_t MBS2:1;
      vuint32_t MBS1:1;
      vuint32_t MBS0:1;
    } B;
  } MBSL;

  uint8_t STCU_reserved5[8];
  union {                              /* STCU2 Startup MBIST End Flag Low Register */
    vuint32_t R;
    struct {
      vuint32_t  :5;
      vuint32_t MBE26:1;
      vuint32_t MBE25:1;
      vuint32_t MBE24:1;
      vuint32_t MBE23:1;
      vuint32_t MBE22:1;
      vuint32_t MBE21:1;
      vuint32_t MBE20:1;
      vuint32_t MBE19:1;
      vuint32_t MBE18:1;
      vuint32_t MBE17:1;
      vuint32_t MBE16:1;
      vuint32_t MBE15:1;
      vuint32_t MBE14:1;
      vuint32_t MBE13:1;
      vuint32_t MBE12:1;
      vuint32_t MBE11:1;
      vuint32_t MBE10:1;
      vuint32_t MBE9:1;
      vuint32_t MBE8:1;
      vuint32_t MBE7:1;
      vuint32_t MBE6:1;
      vuint32_t MBE5:1;
      vuint32_t MBE4:1;
      vuint32_t MBE3:1;
      vuint32_t MBE2:1;
      vuint32_t MBE1:1;
      vuint32_t MBE0:1;
    } B;
  } MBEL;

  uint8_t STCU_reserved6[8];
  union {                              /* STCU2 Shutdown MBIST Status Low Register */
    vuint32_t R;
    struct {
      vuint32_t  :5;
      vuint32_t MBSSW26:1;
      vuint32_t MBSSW25:1;
      vuint32_t MBSSW24:1;
      vuint32_t MBSSW23:1;
      vuint32_t MBSSW22:1;
      vuint32_t MBSSW21:1;
      vuint32_t MBSSW20:1;
      vuint32_t MBSSW19:1;
      vuint32_t MBSSW18:1;
      vuint32_t MBSSW17:1;
      vuint32_t MBSSW16:1;
      vuint32_t MBSSW15:1;
      vuint32_t MBSSW14:1;
      vuint32_t MBSSW13:1;
      vuint32_t MBSSW12:1;
      vuint32_t MBSSW11:1;
      vuint32_t MBSSW10:1;
      vuint32_t MBSSW9:1;
      vuint32_t MBSSW8:1;
      vuint32_t MBSSW7:1;
      vuint32_t MBSSW6:1;
      vuint32_t MBSSW5:1;
      vuint32_t MBSSW4:1;
      vuint32_t MBSSW3:1;
      vuint32_t MBSSW2:1;
      vuint32_t MBSSW1:1;
      vuint32_t MBSSW0:1;
    } B;
  } MBSLSW;

  uint8_t STCU_reserved7[8];
  union {                              /* STCU2 Shutdown MBIST End Flag Low Register */
    vuint32_t R;
    struct {
      vuint32_t  :5;
      vuint32_t MBESW26:1;
      vuint32_t MBESW25:1;
      vuint32_t MBESW24:1;
      vuint32_t MBESW23:1;
      vuint32_t MBESW22:1;
      vuint32_t MBESW21:1;
      vuint32_t MBESW20:1;
      vuint32_t MBESW19:1;
      vuint32_t MBESW18:1;
      vuint32_t MBESW17:1;
      vuint32_t MBESW16:1;
      vuint32_t MBESW15:1;
      vuint32_t MBESW14:1;
      vuint32_t MBESW13:1;
      vuint32_t MBESW12:1;
      vuint32_t MBESW11:1;
      vuint32_t MBESW10:1;
      vuint32_t MBESW9:1;
      vuint32_t MBESW8:1;
      vuint32_t MBESW7:1;
      vuint32_t MBESW6:1;
      vuint32_t MBESW5:1;
      vuint32_t MBESW4:1;
      vuint32_t MBESW3:1;
      vuint32_t MBESW2:1;
      vuint32_t MBESW1:1;
      vuint32_t MBESW0:1;
    } B;
  } MBELSW;

  uint8_t STCU_reserved8[148];
  struct {
    union {                            /* STCU2 LBIST Control Register */
      vuint32_t R;
      struct {
        vuint32_t CSM:1;
        vuint32_t PTR:7;
        vuint32_t  :4;
        vuint32_t PRPGEN:1;
        vuint32_t SHS:3;
        vuint32_t SCEN_OFF:4;
        vuint32_t SCEN_ON:4;
        vuint32_t  :2;
        vuint32_t CWS:6;
      } B;
    } CTRL;
    union {                            /* STCU2 LBIST PC Stop Register */
      vuint32_t R;
      struct {
        vuint32_t  :6;
        vuint32_t PCS:26;
      } B;
    } PCS;
    uint8_t LB_reserved0[24];
    union {                            /* STCU2 Shutdown LBIST MISR Expected Low Register */
      vuint32_t R;
      struct {
        vuint32_t MISRESWx:32;
      } B;
    } MISRELSW;
    union {                            /* STCU2 Shutdown LBIST MISR Expected High Register */
      vuint32_t R;
      struct {
        vuint32_t MISRESWx:32;
      } B;
    } MISREHSW;
    uint8_t LB_reserved1[24];
  } LB[4];

  uint8_t STCU_reserved9[1024];
  union {                              /* STCU2 MBIST Control Register */
    vuint32_t R;
    struct {
      vuint32_t CSM:1;
      vuint32_t PTR:7;
      vuint32_t  :24;
    } B;
  } MB_CTRL[27];
};


/* ============================================================================
   =============================== Module: STM ================================
   ============================================================================ */

struct STM_tag {
  union {                              /* STM Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t CPS:8;                 /* Counter Prescaler. */
      vuint32_t  :6;
      vuint32_t FRZ:1;                 /* Freeze. */
      vuint32_t TEN:1;                 /* Timer counter Enabled. */
    } B;
  } CR;

  union {                              /* STM Count Register */
    vuint32_t R;
    struct {
      vuint32_t CNT:32;                /* Timer count value used as the time base for all channels. */
    } B;
  } CNT;

  uint8_t STM_reserved0[8];
  struct {
    union {                            /* STM Channel Control Register */
      vuint32_t R;
      struct {
        vuint32_t  :31;
        vuint32_t CEN:1;               /* Channel Enable */
      } B;
    } CCR;
    union {                            /* STM Channel Interrupt Register */
      vuint32_t R;
      struct {
        vuint32_t  :31;
        vuint32_t CIF:1;               /* Channel Interrupt Flag */
      } B;
    } CIR;
    union {                            /* STM Channel Compare Register */
      vuint32_t R;
      struct {
        vuint32_t CMP:32;              /* Compare value for channel n. */
      } B;
    } CMP;
    uint8_t CHANNEL_reserved0[4];
  } CHANNEL[4];
};


/* ============================================================================
   =============================== Module: SWT ================================
   ============================================================================ */

struct SWT_tag {
  union {                              /* SWT Control Register */
    vuint32_t R;
    struct {
      vuint32_t MAP0:1;
      vuint32_t MAP1:1;
      vuint32_t MAP2:1;
      vuint32_t MAP3:1;
      vuint32_t MAP4:1;
      vuint32_t MAP5:1;
      vuint32_t MAP6:1;
      vuint32_t MAP7:1;
      vuint32_t  :13;
      vuint32_t SMD:2;                 /* Service Mode. */
      vuint32_t RIA:1;
      vuint32_t WND:1;
      vuint32_t ITR:1;
      vuint32_t HLK:1;
      vuint32_t SLK:1;
      vuint32_t  :1;                   /* Reserved. */
      vuint32_t STP:1;
      vuint32_t FRZ:1;
      vuint32_t WEN:1;
    } B;
  } CR;

  union {                              /* SWT Interrupt Register */
    vuint32_t R;
    struct {
      vuint32_t  :31;
      vuint32_t TIF:1;
    } B;
  } IR;

  union {                              /* SWT Time-out Register */
    vuint32_t R;
    struct {
      vuint32_t WTO:32;
    } B;
  } TO;

  union {                              /* SWT Window Register */
    vuint32_t R;
    struct {
      vuint32_t WST:32;
    } B;
  } WN;

  union {                              /* SWT Service Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t WSC:16;
    } B;
  } SR;

  union {                              /* SWT Counter Output Register */
    vuint32_t R;
    struct {
      vuint32_t CNT:32;
    } B;
  } CO;

  union {                              /* SWT Service Key Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t SK:16;
    } B;
  } SK;
};


/* ============================================================================
   =============================== Module: WKPU ===============================
   ============================================================================ */

struct WKPU_tag {
  union {                              /* NMI Status Flag Register */
    vuint32_t R;
    struct {
      vuint32_t NIF0:1;
      vuint32_t NOVF0:1;
      vuint32_t  :6;
      vuint32_t  :2;
      vuint32_t  :6;
      vuint32_t  :2;
      vuint32_t  :6;
      vuint32_t  :2;
      vuint32_t  :6;
    } B;
  } NSR;

  uint8_t WKPU_reserved0[4];
  union {                              /* NMI Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t NLOCK0:1;
      vuint32_t NDSS0:2;
      vuint32_t NWRE0:1;
      vuint32_t  :1;
      vuint32_t NREE0:1;
      vuint32_t NFEE0:1;
      vuint32_t NFE0:1;
      vuint32_t  :24;
    } B;
  } NCR;
};


/* ============================================================================
   =============================== Module: XBAR ===============================
   ============================================================================ */

struct XBAR_tag {
  struct {
    union {                            /* Priority Registers Slave */
      vuint32_t R;
      struct {
        vuint32_t  :1;
        vuint32_t  :3;
        vuint32_t  :1;
        vuint32_t M6:3;                /* Master 6 Priority. Sets the arbitration priority for this port on the associated slave port. */
        vuint32_t  :1;
        vuint32_t M5:3;                /* Master 5 Priority. Sets the arbitration priority for this port on the associated slave port. */
        vuint32_t  :1;
        vuint32_t  :3;
        vuint32_t  :1;
        vuint32_t  :3;
        vuint32_t  :1;
        vuint32_t  :3;
        vuint32_t  :1;
        vuint32_t M1:3;                /* Master 1 Priority. Sets the arbitration priority for this port on the associated slave port. */
        vuint32_t  :1;
        vuint32_t M0:3;                /* Master 0 Priority. Sets the arbitration priority for this port on the associated slave port. */
      } B;
    } PRS;
    uint8_t PORT_reserved0[12];
    union {                            /* Control Register */
      vuint32_t R;
      struct {
        vuint32_t RO:1;                /* Read Only */
        vuint32_t HLP:1;               /* Halt Low Priority */
        vuint32_t  :6;
        vuint32_t  :1;
        vuint32_t HPE6:1;
        vuint32_t HPE5:1;
        vuint32_t  :1;
        vuint32_t  :1;
        vuint32_t  :1;
        vuint32_t HPE1:1;
        vuint32_t HPE0:1;
        vuint32_t  :6;
        vuint32_t ARB:2;               /* Arbitration Mode */
        vuint32_t  :2;
        vuint32_t PCTL:2;              /* Parking Control */
        vuint32_t  :1;
        vuint32_t PARK:3;              /* Park */
      } B;
    } CRS;
    uint8_t PORT_reserved1[236];
  } PORT[8];
};


/* ============================================================================
   =============================== Module: XBIC ===============================
   ============================================================================ */

struct XBIC_tag {
  union {                              /* XBIC Module Control Register */
    vuint32_t R;
    struct {
      vuint32_t SE0:1;
      vuint32_t SE1:1;
      vuint32_t SE2:1;
      vuint32_t SE3:1;
      vuint32_t SE4:1;
      vuint32_t SE5:1;
      vuint32_t SE6:1;
      vuint32_t SE7:1;
      vuint32_t ME0:1;
      vuint32_t ME1:1;
      vuint32_t ME2:1;
      vuint32_t ME3:1;
      vuint32_t ME4:1;
      vuint32_t ME5:1;
      vuint32_t ME6:1;
      vuint32_t ME7:1;
      vuint32_t  :16;
    } B;
  } MCR;

  union {                              /* XBIC Error Injection Register */
    vuint32_t R;
    struct {
      vuint32_t EIE:1;
      vuint32_t  :16;
      vuint32_t SLV:3;
      vuint32_t MST:4;
      vuint32_t SYN:8;
    } B;
  } EIR;

  union {                              /* XBIC Error Status Register */
    vuint32_t R;
    struct {
      vuint32_t VLD:1;
      vuint32_t DPSE0:1;
      vuint32_t DPSE1:1;
      vuint32_t DPSE2:1;
      vuint32_t DPSE3:1;
      vuint32_t DPSE4:1;
      vuint32_t DPSE5:1;
      vuint32_t DPSE6:1;
      vuint32_t DPSE7:1;
      vuint32_t DPME0:1;
      vuint32_t DPME1:1;
      vuint32_t DPME2:1;
      vuint32_t DPME3:1;
      vuint32_t DPME4:1;
      vuint32_t DPME5:1;
      vuint32_t DPME6:1;
      vuint32_t DPME7:1;
      vuint32_t SLV:3;
      vuint32_t MST:4;
      vuint32_t SYN:8;
    } B;
  } ESR;

  union {                              /* XBIC Error Address Register */
    vuint32_t R;
    struct {
      vuint32_t ADDR:32;
    } B;
  } EAR;
};


/* ============================================================================
   =============================== Module: XOSC ===============================
   ============================================================================ */

struct XOSC_tag {
  union {                              /* XOSC Control Register */
    vuint32_t R;
    struct {
      vuint32_t OSCBYP:1;
      vuint32_t OSCM:1;
      vuint32_t MON:1;
      vuint32_t  :5;
      vuint32_t EOCV:8;                /* End of Count Value */
      vuint32_t M_OSC:1;               /* Crystal oscillator clock interrupt mask */
      vuint32_t  :2;
      vuint32_t  :5;
      vuint32_t I_OSC:1;
      vuint32_t  :5;
      vuint32_t  :1;
      vuint32_t  :1;
    } B;
  } CTL;
};
#define SRAM0_START 0x40000000UL;
#define ADC_0 (*(volatile struct ADC_tag *) 0xFBE00000UL)
#define ADC_1 (*(volatile struct ADC_tag *) 0xFFE04000UL)
#define ADC_2 (*(volatile struct ADC_tag *) 0xFBE08000UL)
#define ADC_3 (*(volatile struct ADC_tag *) 0xFFE0C000UL)
#define AIPS_0 (*(volatile struct AIPS_tag *) 0xFC000000UL)
#define AIPS_1 (*(volatile struct AIPS_tag *) 0xF8000000UL)
#define C55FMC (*(volatile struct C55FMC_tag *) 0xFFFE0000UL)
#define CAN_0 (*(volatile struct FLEXCAN_tag *) 0xFFEC0000UL)
#define CAN_1 (*(volatile struct FLEXCAN_tag *) 0xFFEC4000UL)
#define CAN_2 (*(volatile struct FLEXCAN_tag *) 0xFFEC8000UL)
#define CMU_0 (*(volatile struct CMU_tag *) 0xFBFB0200UL)
#define CMU_1 (*(volatile struct CMU_tag *) 0xFBFB0240UL)
#define CMU_2 (*(volatile struct CMU_tag *) 0xFBFB0280UL)
#define CMU_3 (*(volatile struct CMU_tag *) 0xFBFB02C0UL)
#define CMU_4 (*(volatile struct CMU_tag *) 0xFBFB0300UL)
#define CRC_0 (*(volatile struct CRC_tag *) 0xFFF64000UL)
#define CTU_0 (*(volatile struct CTU_tag *) 0xFBC10000UL)
#define CTU_1 (*(volatile struct CTU_tag *) 0xFFC14000UL)
#define DCL (*(volatile struct DCL_tag *) 0xFFC00104UL)
#define DMAMUX_0 (*(volatile struct DMAMUX_tag *) 0xFFF6C000UL)
#define DMAMUX_1 (*(volatile struct DMAMUX_tag *) 0xFBF6C000UL)
#define DMA_0 (*(volatile struct DMA_tag *) 0xFC0A0000UL)
#define EIM (*(volatile struct EIM_tag *) 0xFC080000UL)
#define FEC (*(volatile struct FEC_tag *) 0xFC0B0000UL)
#define ETIMER_0 (*(volatile struct ETIMER_tag *) 0xFBC20000UL)
#define ETIMER_1 (*(volatile struct ETIMER_tag *) 0xFFC24000UL)
#define ETIMER_2 (*(volatile struct ETIMER_tag *) 0xFBC28000UL)
#define FCCU (*(volatile struct FCCU_tag *) 0xFBF58000UL)
#define FR_0 (*(volatile struct FR_tag *) 0xFFE50000UL)
#define FLEXPWM_0 (*(volatile struct FLEXPWM_tag *) 0xFBC00000UL)
#define FLEXPWM_1 (*(volatile struct FLEXPWM_tag *) 0xFFC04000UL)
#define INTC (*(volatile struct INTC_tag *) 0xFC040000UL)
#define IRCOSC (*(volatile struct IRCOSC_tag *) 0xFFFB0000UL)
#define LFAST_0 (*(volatile struct LFAST_tag *) 0xFFFD8000UL)
#define LINFlexD_0 (*(volatile struct LINFLEX_tag *) 0xFBE84000UL)
#define LINFlexD_1 (*(volatile struct LINFLEX_tag *) 0xFFE90000UL)
#define MC_CGM (*(volatile struct MC_CGM_tag *) 0xFFFB0000UL)
#define MC_ME (*(volatile struct MC_ME_tag *) 0xFFFB8000UL)
#define MC_PCU (*(volatile struct MC_PCU_tag *) 0xFFFA0000UL)
#define MC_RGM (*(volatile struct MC_RGM_tag *) 0xFFFA8000UL)
#define MEMU (*(volatile struct MEMU_tag *) 0xFFF50000UL)
#define PCM (*(volatile struct PCM_tag *) 0xFC028000UL)
#define PFLASH (*(volatile struct PFLASH_tag *) 0xFC030000UL)
#define PIT (*(volatile struct PIT_tag *) 0xFFF84000UL)
#define PLLDIG (*(volatile struct PLLDIG_tag *) 0xFFFB0100UL)
#define PMC (*(volatile struct PMC_tag *) 0xFFFA0400UL)
#define PRAMC (*(volatile struct PRAMC_tag *) 0xFC020000UL)
#define SGEN_0 (*(volatile struct SGEN_tag *) 0xFBC40000UL)
#define SIPI_0 (*(volatile struct SIPI_tag *) 0xFFFD0000UL)
#define SIUL2 (*(volatile struct SIUL2_tag *) 0xFFFC0000UL)
#define SIU (*(volatile struct SIUL2_tag *) 0xFFFC0000UL)  // added define to simplify code reuse
#define SMPU_0 (*(volatile struct SMPU_tag *) 0xFC010000UL)
#define SPI_0 (*(volatile struct DSPI_tag *) 0xFFE70000UL)
#define SPI_1 (*(volatile struct DSPI_tag *) 0xFFE74000UL)
#define SPI_2 (*(volatile struct DSPI_tag *) 0xFBE70000UL)
#define SPI_3 (*(volatile struct DSPI_tag *) 0xFBE74000UL)
#define SRX_0 (*(volatile struct SRX_tag *) 0xFFE5C000UL)
#define SRX_1 (*(volatile struct SRX_tag *) 0xFBE5C000UL)
#define SSCM (*(volatile struct SSCM_tag *) 0xFFFF8000UL)
#define STCU (*(volatile struct STCU_tag *) 0xFFF44000UL)
#define STM_0 (*(volatile struct STM_tag *) 0xFC068000UL)
#define SWT (*(volatile struct SWT_tag *) 0xFC050000UL)
#define WKPU (*(volatile struct WKPU_tag *) 0xFFF98000UL)
#define XBAR_0 (*(volatile struct XBAR_tag *) 0xFC004000UL)
#define XBIC (*(volatile struct XBIC_tag *) 0xFC018000UL)
#define XOSC (*(volatile struct XOSC_tag *) 0xFFFB0080UL)


#ifdef __MWERKS__
#pragma pop
#endif
#ifdef __ghs__
#pragma ghs endnowarning
#endif
#ifdef  __cplusplus
}
#endif
#endif /* ifdef _MPC5744P_H */
