/***************************************************************** 
 * FILE        : MPC5645S.h
 * 
 * DESCRIPTION : This is the header file describing the register
 *               set for:
 *               MPC5645S second cut only
 *
 *               In some places this includes alternative register
 *               nomenclature. Comment out the unused version to
 *               match code requirements
 *               The default version is used by Freescale in code
 *               examples
 * 
 * COPYRIGHT   :(c) 2011, Freescale Semiconductor
 * 
 * VERSION     : 0.30
 * DATE        : 8 March 2011
 * AUTHOR      : ttz778 
 * HISTORY     : Original source taken from MPC5645S.h
 * 0.10 : Updated and corrected LINFlex, updated QuadSPI
 * 0.20 : Updated LINFlex UARTCR, UARTSR and LINIBRR registers.
 *        Added CGM.VIU_MUX register
 * 0.30 : Added Tx FIFO flush enable bit in the RLE
 ******************************************************************/

/*>>>>NOTE! this file is auto-generated please do not edit it!<<<<*/

/***************************************************************** 
* Example instantiation and use:
*
*  <MODULE>.<REGISTER>.B.<BIT>    = 1;
*  <MODULE>.<REGISTER>.R        = 0x10000000;
*
******************************************************************/
//lint -e9058

#ifndef _JDP_H_
#define _JDP_H_

#include "typedefs.h"

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef __MWERKS__
#pragma push
#pragma ANSI_strict off
#endif
/****************************************************************************/
/*                             MODULE : ADC                                 */
/****************************************************************************/
    struct ADC_tag {

        union {
            vuint32_t R;
            struct {
                vuint32_t OWREN:1;
                vuint32_t WLSIDE:1;
                vuint32_t MODE:1;
                vuint32_t EDGLEV:1;
                vuint32_t TRGEN:1;
                vuint32_t EDGE:1;
                  vuint32_t:1;
                vuint32_t NSTART:1;
                  vuint32_t:1;
                vuint32_t JTRGEN:1;
                vuint32_t JEDGE:1;
                vuint32_t JSTART:1;
                  vuint32_t:11;
                vuint32_t ADCLKSEL:1;
                vuint32_t ABORTCHAIN:1;
                vuint32_t ABORT:1;
                vuint32_t ACK0:1;
                  vuint32_t:4;
                vuint32_t PWDN:1;
            } B;
        } MCR;                          /* Main Configuration Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:7;
                vuint32_t NSTART:1;
                vuint32_t JABORT:1;
                  vuint32_t:2;
                vuint32_t JSTART:1;
                  vuint32_t:4;
                vuint32_t CHADDR:7;
                  vuint32_t:3;
                vuint32_t ACK0:1;
                  vuint32_t:2;
                vuint32_t ADCSTATUS:3;
            } B;
        } MSR;                          /* Main Status Register */

        int32_t ADC_reserved1[2];       /* (0x008 - 0x00F)/4 = 0x02 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:28;
                vuint32_t JEOC:1;
                vuint32_t JECH:1;
                vuint32_t EOC:1;
                vuint32_t ECH:1;
            } B;
        } ISR_STATUS;                          /* Interrupt Status Register. Renamed from ISR due to name clashing with macro in OS */


        union {
            vuint32_t R;
            struct {
                vuint32_t EOC31:1;
                vuint32_t EOC30:1;
                vuint32_t EOC29:1;
                vuint32_t EOC28:1;
                vuint32_t EOC27:1;
                vuint32_t EOC26:1;
                vuint32_t EOC25:1;
                vuint32_t EOC24:1;
                vuint32_t EOC23:1;
                vuint32_t EOC22:1;
                vuint32_t EOC21:1;
                vuint32_t EOC20:1;
                vuint32_t EOC19:1;
                vuint32_t EOC18:1;
                vuint32_t EOC17:1;
                vuint32_t EOC16:1;
                vuint32_t EOC15:1;
                vuint32_t EOC14:1;
                vuint32_t EOC13:1;
                vuint32_t EOC12:1;
                vuint32_t EOC11:1;
                vuint32_t EOC10:1;
                vuint32_t EOC9:1;
                vuint32_t EOC8:1;
                vuint32_t EOC7:1;
                vuint32_t EOC6:1;
                vuint32_t EOC5:1;
                vuint32_t EOC4:1;
                vuint32_t EOC3:1;
                vuint32_t EOC2:1;
                vuint32_t EOC1:1;
                vuint32_t EOC0:1;
            } B;
        } CEOCFR[3];                    /* Channel Pending Registers - [0] not supported */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:28;
                vuint32_t MSKJEOC:1;
                vuint32_t MSKJECH:1;
                vuint32_t MSKEOC:1;
                vuint32_t MSKECH:1;
            } B;
        } IMR;                          /* Interrupt Mask Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t CIM31:1;
                vuint32_t CIM30:1;
                vuint32_t CIM29:1;
                vuint32_t CIM28:1;
                vuint32_t CIM27:1;
                vuint32_t CIM26:1;
                vuint32_t CIM25:1;
                vuint32_t CIM24:1;
                vuint32_t CIM23:1;
                vuint32_t CIM22:1;
                vuint32_t CIM21:1;
                vuint32_t CIM20:1;
                vuint32_t CIM19:1;
                vuint32_t CIM18:1;
                vuint32_t CIM17:1;
                vuint32_t CIM16:1;
                vuint32_t CIM15:1;
                vuint32_t CIM14:1;
                vuint32_t CIM13:1;
                vuint32_t CIM12:1;
                vuint32_t CIM11:1;
                vuint32_t CIM10:1;
                vuint32_t CIM9:1;
                vuint32_t CIM8:1;
                vuint32_t CIM7:1;
                vuint32_t CIM6:1;
                vuint32_t CIM5:1;
                vuint32_t CIM4:1;
                vuint32_t CIM3:1;
                vuint32_t CIM2:1;
                vuint32_t CIM1:1;
                vuint32_t CIM0:1;
            } B;
        } CIMR[3];                      /* Channel Interrupt Mask Registers - [0] not supported */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:24;
                vuint32_t WDG3H:1;
                vuint32_t WDG2H:1;
                vuint32_t WDG1H:1;
                vuint32_t WDG0H:1;
                vuint32_t WDG3L:1;
                vuint32_t WDG2L:1;
                vuint32_t WDG1L:1;
                vuint32_t WDG0L:1;
            } B;
        } WTISR;                        /* Watchdog Interrupt Threshold Register was WDGTHR */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:24;
                vuint32_t MSKWDG3H:1;
                vuint32_t MSKWDG2H:1;
                vuint32_t MSKWDG1H:1;
                vuint32_t MSKWDG0H:1;
                vuint32_t MSKWDG3L:1;
                vuint32_t MSKWDG2L:1;
                vuint32_t MSKWDG1L:1;
                vuint32_t MSKWDG0L:1;
            } B;
        } WTIMR;                        /* Watchdog Interrupt Mask Register was IMWDGTHR */

        int32_t ADC_reserved2[2];       /* (0x038 - 0x03F)/4 = 0x02 */

    union {
            vuint32_t R;
            struct {
                  vuint32_t:30;
                vuint32_t DCLR:1;
                vuint32_t DMAEN:1;
            } B;
        } DMAE;                         /* DMA Enable Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t DMA31:1;      /* was unused [16] */
                vuint32_t DMA30:1;
                vuint32_t DMA29:1;
                vuint32_t DMA28:1;
                vuint32_t DMA27:1;
                vuint32_t DMA26:1;
                vuint32_t DMA25:1;
                vuint32_t DMA24:1;
                vuint32_t DMA23:1;
                vuint32_t DMA22:1;
                vuint32_t DMA21:1;
                vuint32_t DMA20:1;
                vuint32_t DMA19:1;
                vuint32_t DMA18:1;
                vuint32_t DMA17:1;
                vuint32_t DMA16:1;
                vuint32_t DMA15:1;
                vuint32_t DMA14:1;
                vuint32_t DMA13:1;
                vuint32_t DMA12:1;
                vuint32_t DMA11:1;
                vuint32_t DMA10:1;
                vuint32_t DMA9:1;
                vuint32_t DMA8:1;
                vuint32_t DMA7:1;
                vuint32_t DMA6:1;
                vuint32_t DMA5:1;
                vuint32_t DMA4:1;
                vuint32_t DMA3:1;
                vuint32_t DMA2:1;
                vuint32_t DMA1:1;
                vuint32_t DMA0:1;
            } B;
        } DMAR[3];                      /* DMA Channel select Registers - [0] not supported */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t THREN:1;
                vuint32_t THRINV:1;
                  vuint32_t:7;
                vuint32_t THRCH:7;
            } B;
        } TRC[4];                       /* Threshold Control Registers */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:6;
                vuint32_t THRH:10;
                  vuint32_t:6;
                vuint32_t THRL:10;
            } B;
        } THRHLR[4];                    /* Threshold Registers */

        int32_t ADC_reserved3[9];       /* (0x070 - 0x08F)/4 = 0x09 */

    union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t INPLATCH:1;
                  vuint32_t:1;
                vuint32_t OFFSHIFT:2;   /* !!! This field only in CTR[0] */
                  vuint32_t:1;
                vuint32_t INPCMP:2;
                  vuint32_t:1;
                vuint32_t INPSAMP:8;
            } B;
        } CTR[3];                       /* Conversion Timing Register - [0] not supported */

    int32_t ADC_reserved4[1];           /* (0x0A0 - 0x0A3)/4 = 0x01 */

    union {
            vuint32_t R;
            struct {
                vuint32_t CH31:1;
                vuint32_t CH30:1;
                vuint32_t CH29:1;
                vuint32_t CH28:1;
                vuint32_t CH27:1;
                vuint32_t CH26:1;
                vuint32_t CH25:1;
                vuint32_t CH24:1;
                vuint32_t CH23:1;
                vuint32_t CH22:1;
                vuint32_t CH21:1;
                vuint32_t CH20:1;
                vuint32_t CH19:1;
                vuint32_t CH18:1;
                vuint32_t CH17:1;
                vuint32_t CH16:1;
                vuint32_t CH15:1;
                vuint32_t CH14:1;
                vuint32_t CH13:1;
                vuint32_t CH12:1;
                vuint32_t CH11:1;
                vuint32_t CH10:1;
                vuint32_t CH9:1;
                vuint32_t CH8:1;
                vuint32_t CH7:1;
                vuint32_t CH6:1;
                vuint32_t CH5:1;
                vuint32_t CH4:1;
                vuint32_t CH3:1;
                vuint32_t CH2:1;
                vuint32_t CH1:1;
                vuint32_t CH0:1;
            } B;
        } NCMR[3];                      /* Normal Conversion Mask Register was [6] */

        int32_t ADC_reserved5[1];       /* (0x0B0 - 0x0B3)/4 = 0x01 */

        union {
            vuint32_t R;
            struct {
                vuint32_t CH31:1;
                vuint32_t CH30:1;
                vuint32_t CH29:1;
                vuint32_t CH28:1;
                vuint32_t CH27:1;
                vuint32_t CH26:1;
                vuint32_t CH25:1;
                vuint32_t CH24:1;
                vuint32_t CH23:1;
                vuint32_t CH22:1;
                vuint32_t CH21:1;
                vuint32_t CH20:1;
                vuint32_t CH19:1;
                vuint32_t CH18:1;
                vuint32_t CH17:1;
                vuint32_t CH16:1;
                vuint32_t CH15:1;
                vuint32_t CH14:1;
                vuint32_t CH13:1;
                vuint32_t CH12:1;
                vuint32_t CH11:1;
                vuint32_t CH10:1;
                vuint32_t CH9:1;
                vuint32_t CH8:1;
                vuint32_t CH7:1;
                vuint32_t CH6:1;
                vuint32_t CH5:1;
                vuint32_t CH4:1;
                vuint32_t CH3:1;
                vuint32_t CH2:1;
                vuint32_t CH1:1;
                vuint32_t CH0:1;
            } B;
        } JCMR[3];                      /* Injected Conversion Mask Register */

        int32_t ADC_reserved6[1];       /* (0x0C0 - 0x0C3)/4 = 0x01 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:24;
                vuint32_t DSD:8;
            } B;
        } DSDR;                         /* Decide Signals Delay Register was DSD */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:24;
                vuint32_t PDED:8;
            } B;
        } PDEDR;                        /* Power Down Delay Register was PDD */

        int32_t ADC_reserved7[13];      /* (0x0CC - 0xFF)/4 = 0x0D */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:12;
                vuint32_t VALID:1;
                vuint32_t OVERW:1;
                vuint32_t RESULT:2;
                  vuint32_t:6;
                vuint32_t CDATA:10;
            } B;
        } CDR[96];                      /* Channel 0-95 Data Register - 0-31, 48-63, 72-95 not supported */


    };                                  /* end of ADC_tag */
/****************************************************************************/
/*                             MODULE : CANSP                               */
/****************************************************************************/
    struct CANSP_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t RX_COMPLETE:1;
                vuint32_t BUSY:1;
                vuint32_t ACTIVE_CK:1;
                  vuint32_t:3;
                vuint32_t MODE:1;
                vuint32_t CAN_RX_SEL:3;
                vuint32_t BRP:5;
                vuint32_t CAN_SMPLR_EN:1;
            } B;
        } CR;                           /* CANSP Control Register */

        union {
            vuint32_t R;
        } SR[12];                       /* CANSP Sample Register 0 to 11 */

    };                                 /* end of CANSP_tag */
/****************************************************************************/
/*                             MODULE : ECSM                                */
/****************************************************************************/
    struct ECSM_tag {

        union {
            vuint16_t R;
        } PCT;                          /* MCM Processor Core Type Register */

        union {
            vuint16_t R;
        } REV;                          /* MCM  Revision Register */

        int32_t ECSM_reserved;

        union {
            vuint32_t R;
        } IMC;                          /* IPS Configuration Register */

        int8_t ECSM_reserved1[3];

        union {
            vuint8_t R;
            struct {
                vuint8_t POR:1;
                vuint8_t DIR:1;
                  vuint8_t:6;
            } B;
        } MRSR;                         /* MCM Miscellaneous Reset Status Register */

        int8_t ECSM_reserved2[3];

        union {
            vuint8_t R;
            struct {
                vuint8_t ENBWCR:1;
                  vuint8_t:3;
                vuint8_t PRILVL:4;
            } B;
        } MWCR;                         /* MCM Miscellaneous Wakeup Control Register */

        int32_t ECSM_reserved3[2];
        int8_t ESCM_reserved4[3];

        union {
            vuint8_t R;
            struct {
                vuint8_t FB0AI:1;
                vuint8_t FB0SI:1;
                vuint8_t FB1AI:1;
                vuint8_t FB1SI:1;
                  vuint8_t:4;
            } B;
        } MIR;                          /* MCM Miscellaneous Interrupt Register */

        int32_t ECSM_reserved5;

        union {
            vuint32_t R;
        } MUDCR;                        /* MCM Miscellaneous User-Defined Control Register */

        int32_t ECSM_reserved6[6];      /* (0x040- 0x028)/4 = 0x06 */
        int8_t ECSM_reserved7[3];

        union {
            vuint8_t R;
            struct {
                  vuint8_t:2;
                vuint8_t ER1BR:1;
                vuint8_t EF1BR:1;
                  vuint8_t:2;
                vuint8_t ERNCR:1;
                vuint8_t EFNCR:1;
            } B;
        } ECR;                          /* MCM ECC Configuration Register */

        int8_t ECSM_reserved8[3];

        union {
            vuint8_t R;
            struct {
                  vuint8_t:2;
                vuint8_t R1BC:1;
                vuint8_t F1BC:1;
                  vuint8_t:2;
                vuint8_t RNCE:1;
                vuint8_t FNCE:1;
            } B;
        } ESR;                          /* MCM ECC Status Register */

        int16_t ECSM_reserved9;

        union {
            vuint16_t R;
            struct {
                  vuint16_t:2;
                vuint16_t FRC1BI:1;
                vuint16_t FR11BI:1;
                  vuint16_t:2;
                vuint16_t FRCNCI:1;
                vuint16_t FR1NCI:1;
                  vuint16_t:1;
                vuint16_t ERRBIT:7;
            } B;
        } EEGR;                         /* MCM ECC Error Generation Register */

        int32_t ECSM_reserved10;

        union {
            vuint32_t R;
        } FEAR;                         /* MCM Flash ECC Address Register */

        int16_t ECSM_reserved11;

        union {
            vuint8_t R;
            struct {
                  vuint8_t:4;
                vuint8_t FEMR:4;
            } B;
        } FEMR;                         /* MCM Flash ECC Master Number Register */

        union {
            vuint8_t R;
            struct {
                vuint8_t WRITE:1;
                vuint8_t SIZE:3;
                vuint8_t PROTECTION:4;
            } B;
        } FEAT;                         /* MCM Flash ECC Attributes Register */

        int32_t ECSM_reserved12;

        union {
            vuint32_t R;
        } FEDR;                         /* MCM Flash ECC Data Register */

        union {
            vuint32_t R;
        } REAR;                         /* MCM RAM ECC Address Register */

        int8_t ECSM_reserved13;

        union {
            vuint8_t R;
        } RESR;                         /* MCM RAM ECC Address Register */

        union {
            vuint8_t R;
            struct {
                  vuint8_t:4;
                vuint8_t REMR:4;
            } B;
        } REMR;                         /* MCM RAM ECC Master Number Register */

        union {
            vuint8_t R;
            struct {
                vuint8_t WRITE:1;
                vuint8_t SIZE:3;
                vuint8_t PROTECTION:4;
            } B;
        } REAT;                         /* MCM RAM ECC Attributes Register */

        int32_t ECSM_reserved14;

        union {
            vuint32_t R;
        } REDR;                         /* MCM RAM ECC Data Register */

    };                                  /* end of ECSM_tag */
/****************************************************************************/
/*                             MODULE : RTC                                 */
/****************************************************************************/
    struct RTC_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t SUPV:1;
                  vuint32_t:31;
            } B;
        } RTCSUPV;                      /* RTC Supervisor Control Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t CNTEN:1;
                vuint32_t RTCIE:1;
                vuint32_t FRZEN:1;
                vuint32_t ROVREN:1;
                vuint32_t RTCVAL:12;
                vuint32_t APIEN:1;
                vuint32_t APIIE:1;
                vuint32_t CLKSEL:2;
                vuint32_t DIV512EN:1;
                vuint32_t DIV32EN:1;
                vuint32_t APIVAL:10;
            } B;
        } RTCC;                         /* RTC Control Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:2;
                vuint32_t RTCF:1;
                  vuint32_t:15;
                vuint32_t APIF:1;
                  vuint32_t:2;
                vuint32_t ROVRF:1;
                  vuint32_t:10;
            } B;
        } RTCS;                         /* RTC Status Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t RTCCNT:32;
            } B;
        } RTCCNT;                       /* RTC Counter Register */

    };                                  /* end of RTC_tag */
/****************************************************************************/
/*                             MODULE : SIU                                 */
/****************************************************************************/
    struct SIU_tag {

        int32_t SIU_reserved0;

        union {                         /* MCU ID Register 1 */
            vuint32_t R;
            struct {
                vuint32_t PARTNUM:16;
                vuint32_t CSP:1;
                vuint32_t PKG:5;
                  vuint32_t:2;
                vuint32_t MAJOR_MASK:4;
                vuint32_t MINOR_MASK:4;
            } B;
        } MIDR;

        union {                         /* MCU ID Register 2 */
            vuint32_t R;
            struct {
                vuint32_t SF:1;
                vuint32_t FLASH_SIZE_1:4;
                vuint32_t FLASH_SIZE_2:4;
                  vuint32_t:7;
                vuint32_t PARTNUM:8;
                  vuint32_t:3;
                vuint32_t EE:1;
                  vuint32_t:4;
            } B;
        } MIDR2;

        int32_t SIU_reserved1[2];

        union {                         /* Interrupt Status Flag Register */
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t EIF23:1;
                vuint32_t EIF22:1;
                vuint32_t EIF21:1;
                vuint32_t EIF20:1;
                vuint32_t EIF19:1;
                vuint32_t EIF18:1;
                vuint32_t EIF17:1;
                vuint32_t EIF16:1;
                vuint32_t EIF15:1;
                vuint32_t EIF14:1;
                vuint32_t EIF13:1;
                vuint32_t EIF12:1;
                vuint32_t EIF11:1;
                vuint32_t EIF10:1;
                vuint32_t EIF9:1;
                vuint32_t EIF8:1;
                vuint32_t EIF7:1;
                vuint32_t EIF6:1;
                vuint32_t EIF5:1;
                vuint32_t EIF4:1;
                vuint32_t EIF3:1;
                vuint32_t EIF2:1;
                vuint32_t EIF1:1;
                vuint32_t EIF0:1;
            } B;
        } ISR;

        union {                         /* Interrupt Request Enable Register */
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t IRE23:1;
                vuint32_t IRE22:1;
                vuint32_t IRE21:1;
                vuint32_t IRE20:1;
                vuint32_t IRE19:1;
                vuint32_t IRE18:1;
                vuint32_t IRE17:1;
                vuint32_t IRE16:1;
                vuint32_t IRE15:1;
                vuint32_t IRE14:1;
                vuint32_t IRE13:1;
                vuint32_t IRE12:1;
                vuint32_t IRE11:1;
                vuint32_t IRE10:1;
                vuint32_t IRE9:1;
                vuint32_t IRE8:1;
                vuint32_t IRE7:1;
                vuint32_t IRE6:1;
                vuint32_t IRE5:1;
                vuint32_t IRE4:1;
                vuint32_t IRE3:1;
                vuint32_t IRE2:1;
                vuint32_t IRE1:1;
                vuint32_t IRE0:1;
            } B;
        } IRER;

        int32_t SIU_reserved2[3];

        union {                         /* Interrupt Rising-Edge Event Enable Register */
            vuint32_t R;
            struct {
                  vuint32_t:8;
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
        } IREER;

        union {                         /* Interrupt Falling-Edge Event Enable Register */
            vuint32_t R;
            struct {
                  vuint32_t:8;
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
        } IFEER;

        union {                         /* Interrupt Filter Enable Register */
            vuint32_t R;
            struct {
                  vuint32_t:8;
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
        } IFER;

        int32_t SIU_reserved3[3];

/* This register contains a bit called SMC, however, on this family SMC is also the name 
** of the Stepper Motor Controller. This is a conflict due to the macro substitution approach
** used by this header. Therefore for this family that bit is renamed "SME"
*/   
        union {                         /* Pad Configuration Registers */
            vuint16_t R;
            struct {
                  vuint16_t:1;
                vuint16_t SME:1;        /* Standard definition is vuint16_t SMC:1; */
                vuint16_t APC:1;
                  vuint16_t:1;
                vuint16_t PA:2;
                vuint16_t OBE:1;
                vuint16_t IBE:1;
                 vuint16_t:2;
                vuint16_t ODE:1;
                vuint16_t SRC:3;        /* Not all pad types have three SRC bits */
                vuint16_t WPE:1;
                vuint16_t WPS:1;
            } B;
        } PCR[282];

        int32_t SIU_reserved5[163];     /* {0x500-0x274}/0x4 */

        union {                         /* Pad Selection for Multiplexed Input Register */
            vuint8_t R;
            struct {
                  vuint8_t:4;
                vuint8_t PADSEL:4;
            } B;
        } PSMI[54];

        int8_t SIU_reserved6[2];        /* {0x536/7} */
        int32_t SIU_reserved7[50];      /* {0x600-0x538}/0x4 */

        union {                         /* GPIO Pin Data Output Registers */
            vuint8_t R;
            struct {
                  vuint8_t:7;
                vuint8_t PDO:1;
            } B;
        } GPDO[185];

        int8_t SIU_reserved8[3];        /* {0x6B9-6BB} */
        int32_t SIU_reserved9[81];      /* {0x800-0x6BC}/0x4 */

        union {                         /* GPIO Pin Data Input Registers */
            vuint8_t R;
            struct {
                  vuint8_t:7;
                vuint8_t PDI:1;
            } B;
        } GPDI[185];

        int8_t SIU_reserved10[3];       /* {0x8B9-8BB} */
        int32_t SIU_reserved11[209];    /* {0xC00-0x8BC}/0x4 */

        union {                         /* Parallel GPIO Pin Data Output Register */
            vuint32_t R;
            struct {
                vuint32_t PPD0:32;
            } B;
        } PGPDO[6];

        int32_t SIU_reserved12[10];     /* {0xC40-0xC18}/0x4 */

        union {                         /* Parallel GPIO Pin Data Input Register */
            vuint32_t R;
            struct {
                vuint32_t PPDI:32;
            } B;
        } PGPDI[6];

        int32_t SIU_reserved13[10];     /* {0xC80-0xC58}/0x4 */

        union {                         /* Masked Parallel GPIO Pin Data Out Register */
            vuint32_t R;
            struct {
                vuint32_t MASK:16;
                vuint32_t MPPDO:16;
            } B;
        } MPGPDO[12];

        int32_t SIU_reserved14[212];    /* {0x1000-0x0CB0}/0x4 */

        union {                         /* Interrupt Filter Maximum Counter Register */
            vuint32_t R;
            struct {
                  vuint32_t:28;
                vuint32_t MAXCNT:4;
            } B;
        } IFMC[24];

        int32_t SIU_reserved15[8];      /* {0x1080-0x1060}/4 = 0x08 */

        union {                         /* Interrupt Filter Clock Prescaler Register */
            vuint32_t R;
            struct {
                  vuint32_t:28;
                vuint32_t IFCP:4;
            } B;
        } IFCPR;

    };                                  /* end of SIU_tag */
/****************************************************************************/
/*                             MODULE : SSCM                                */
/****************************************************************************/
    struct SSCM_tag {
        union {
            vuint16_t R;
            struct {
                  vuint16_t:4;
                vuint16_t NXEN:1;
                vuint16_t PUB:1;
                vuint16_t SEC:1;
                  vuint16_t:1;
                vuint16_t BMODE:3;
                  vuint16_t :1;
                vuint16_t ABD:1;
                  vuint16_t:3;
            } B;
        } STATUS;                       /* Status Register */

        union {
            vuint16_t R;
            struct {
                  vuint16_t:10;
                vuint16_t IVLD:1;
                  vuint16_t:4;
                vuint16_t DVLD:1;
            } B;
        } MEMCONFIG;                    /* System Memory Configuration Register */

        int16_t SSCM_reserved;

        union {
            vuint16_t R;
            struct {
                  vuint16_t:14;
                vuint16_t PAE:1;
                vuint16_t RAE:1;
            } B;
        } ERROR;                        /* Error Configuration Register */

        union {
            vuint16_t R;
            struct {
                  vuint16_t:13;
                vuint16_t DEBUG_MODE:3;
            } B;
        } DEBUGPORT;                    /* Debug Status Port Register */

        int16_t SSCM_reserved1;

        union {
            vuint32_t R;
            struct {
                vuint32_t PWD_HI:32;
            } B;
        } PWCMPH;                       /* Password Comparison Register High Word */

        union {
            vuint32_t R;
            struct {
                vuint32_t PWD_LO:32;
            } B;
        } PWCMPL;                       /* Password Comparison Register Low Word */

    };                                  /* end of SSCM_tag */
/****************************************************************************/
/*                             MODULE : STM                                 */
/****************************************************************************/
    struct STM_CHANNEL_tag {

        union {
            vuint32_t R;
            struct {
                  vuint32_t:31;
                vuint32_t CEN:1;
            } B;
        } CCR;                          /* STM Channel Control Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:31;
                vuint32_t CIF:1;
            } B;
        } CIR;                          /* STM Channel Interrupt Register */

        union {
            vuint32_t R;
        } CMP;                          /* STM Channel Compare Register 0 */

        int32_t STM_CHANNEL_reserved;

    };                                  /* end of STM_CHANNEL_tag */

    struct STM_tag {

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t CPS:8;
                  vuint32_t:6;
                vuint32_t FRZ:1;
                vuint32_t TEN:1;
            } B;
        } CR;                           /* STM Control Register */

        union {
            vuint32_t R;
        } CNT;                          /* STM Count Register */

        int32_t STM_reserved[2];

        struct STM_CHANNEL_tag CH[4];

    };                                  /* end of STM_tag */
/****************************************************************************/
/*                             MODULE : SWT                                 */
/****************************************************************************/
    struct SWT_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t MAP0:1;
                vuint32_t MAP1:1;
                vuint32_t MAP2:1;
                vuint32_t MAP3:1;
                  vuint32_t:19;
                vuint32_t RIA:1;
                vuint32_t WND:1;
                vuint32_t ITR:1;
                vuint32_t HLK:1;
                vuint32_t SLK:1;
                vuint32_t CSL:1;
                vuint32_t STP:1;
                vuint32_t FRZ:1;
                vuint32_t WEN:1;
            } B;
        } CR;                           /* SWT Control Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:31;
                vuint32_t TIF:1;
            } B;
        } IR;                           /* SWT Interrupt Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t WTO:32;
            } B;
        } TO;                           /* SWT Time-Out Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t WST:32;
            } B;
        } WN;                           /* SWT Window Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t WSC:16;
            } B;
        } SR;                           /* SWT Service Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t CNT:32;
            } B;
        } CO;                           /* SWT Counter Output Register */

    };                                  /* end of SWT_tag */
/****************************************************************************/
/*                             MODULE : WKUP                                */
/****************************************************************************/
    struct WKUP_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t NIF0:1;
                vuint32_t NOVF0:1;
                  vuint32_t:30;
            } B;
        } NSR;                          /* NMI Status Register */

        int32_t WKUP_reserved;

        union {
            vuint32_t R;
            struct {
                vuint32_t NLOCK0:1;
                vuint32_t NDSS:2;
                vuint32_t NWRE:1;
                  vuint32_t:1;
                vuint32_t NREE:1;
                vuint32_t NFEE:1;
                vuint32_t NFE:1;
                  vuint32_t:24;
            } B;
        } NCR;                          /* NMI Configuration Register */

        int32_t WKUP_reserved1[2];

        union {
            vuint32_t R;
            struct {
                  vuint32_t:6;
                vuint32_t EIF25:1;
                vuint32_t EIF24:1;
                vuint32_t EIF23:1;
                vuint32_t EIF22:1;
                vuint32_t EIF21:1;
                vuint32_t EIF20:1;
                vuint32_t EIF19:1;
                vuint32_t EIF18:1;
                vuint32_t EIF17:1;
                vuint32_t EIF16:1;
                vuint32_t EIF15:1;
                vuint32_t EIF14:1;
                vuint32_t EIF13:1;
                vuint32_t EIF12:1;
                vuint32_t EIF11:1;
                vuint32_t EIF10:1;
                vuint32_t EIF9:1;
                vuint32_t EIF8:1;
                vuint32_t EIF7:1;
                vuint32_t EIF6:1;
                vuint32_t EIF5:1;
                vuint32_t EIF4:1;
                vuint32_t EIF3:1;
                vuint32_t EIF2:1;
                vuint32_t EIF1:1;
                vuint32_t EIF0:1;
            } B;
        } WISR;                         /* Wakeup/Interrupt Status Flag Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:6;
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
        } IRER;                         /* Interrupt Request Enable Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:6;
                vuint32_t WRE25:1;
                vuint32_t WRE24:1;
                vuint32_t WRE23:1;
                vuint32_t WRE22:1;
                vuint32_t WRE21:1;
                vuint32_t WRE20:1;
                vuint32_t WRE19:1;
                vuint32_t WRE18:1;
                vuint32_t WRE17:1;
                vuint32_t WRE16:1;
                vuint32_t WRE15:1;
                vuint32_t WRE14:1;
                vuint32_t WRE13:1;
                vuint32_t WRE12:1;
                vuint32_t WRE11:1;
                vuint32_t WRE10:1;
                vuint32_t WRE9:1;
                vuint32_t WRE8:1;
                vuint32_t WRE7:1;
                vuint32_t WRE6:1;
                vuint32_t WRE5:1;
                vuint32_t WRE4:1;
                vuint32_t WRE3:1;
                vuint32_t WRE2:1;
                vuint32_t WRE1:1;
                vuint32_t WRE0:1;
            } B;
        } WRER;                         /* Wakeup Request Enable Register */

        int32_t WKUP_reserved2[2];

        union {
            vuint32_t R;
            struct {
                  vuint32_t:6;
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
        } WIREER;                       /* Wakeup/Interrupt Rising-Edge Event Enable Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:6;
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
        } WIFEER;                       /* Wakeup/Interrupt Falling-Edge Event Enable Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:6;
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
        } WIFER;                        /* Wakeup/Interrupt Filter Enable Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:6;
                vuint32_t IPUE25:1;
                vuint32_t IPUE24:1;
                vuint32_t IPUE23:1;
                vuint32_t IPUE22:1;
                vuint32_t IPUE21:1;
                vuint32_t IPUE20:1;
                vuint32_t IPUE19:1;
                vuint32_t IPUE18:1;
                vuint32_t IPUE17:1;
                vuint32_t IPUE16:1;
                vuint32_t IPUE15:1;
                vuint32_t IPUE14:1;
                vuint32_t IPUE13:1;
                vuint32_t IPUE12:1;
                vuint32_t IPUE11:1;
                vuint32_t IPUE10:1;
                vuint32_t IPUE9:1;
                vuint32_t IPUE8:1;
                vuint32_t IPUE7:1;
                vuint32_t IPUE6:1;
                vuint32_t IPUE5:1;
                vuint32_t IPUE4:1;
                vuint32_t IPUE3:1;
                vuint32_t IPUE2:1;
                vuint32_t IPUE1:1;
                vuint32_t IPUE0:1;
            } B;
        } WIPUER;                       /* Wakeup/Interrupt Pullup Enable Register */

    };                                  /* end of WKUP_tag */
/****************************************************************************/
/*                             MODULE : LINFLEXD Master Slave               */
/****************************************************************************/

    struct LINFLEX_MS_tag {

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t CCD:1;
                vuint32_t CFD:1;
                vuint32_t LASE:1;
                vuint32_t AWUM:1;
                vuint32_t MBL:4;
                vuint32_t BF:1;
                vuint32_t SLFM:1;
                vuint32_t LBKM:1;
                vuint32_t MME:1;
                vuint32_t SBDT:1;
                vuint32_t RBLM:1;
                vuint32_t SLEEP:1;
                vuint32_t INIT:1;
            } B;
        } LINCR1;                       /* LINFLEX Control Register 1 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t SZIE:1;
                vuint32_t OCIE:1;
                vuint32_t BEIE:1;
                vuint32_t CEIE:1;
                vuint32_t HEIE:1;
                  vuint32_t:2;
                vuint32_t FEIE:1;
                vuint32_t BOIE:1;
                vuint32_t LSIE:1;
                vuint32_t WUIE:1;
                vuint32_t DBFIE:1;
                vuint32_t DBEIE:1;
                vuint32_t DRIE:1;
                vuint32_t DTIE:1;
                vuint32_t HRIE:1;
            } B;
        } LINIER;                       /* LINFLEX Interrupt Enable Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t LINS:4;
                  vuint32_t:2;
                vuint32_t RMB:1;
                  vuint32_t:1;
                vuint32_t RBSY:1;
                vuint32_t RPS:1;
                vuint32_t WUF:1;
                vuint32_t DBFF:1;
                vuint32_t DBEF:1;
                vuint32_t DRF:1;
                vuint32_t DTF:1;
                vuint32_t HRF:1;
            } B;
        } LINSR;                        /* LINFLEX Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t SZF:1;
                vuint32_t OCF:1;
                vuint32_t BEF:1;
                vuint32_t CEF:1;
                vuint32_t SFEF:1;
                vuint32_t BDEF:1;
                vuint32_t IDPEF:1;
                vuint32_t FEF:1;
                vuint32_t BOF:1;
                  vuint32_t:6;
                vuint32_t NF:1;
            } B;
        } LINESR;                       /* LINFLEX LIN Error Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t TDFL:3;
                vuint32_t RDFL:3;
                vuint32_t RFBM:1;
                vuint32_t TFBM:1;
                vuint32_t WL1:1;
                vuint32_t PC1:1;
                vuint32_t RXEN:1;
                vuint32_t TXEN:1;
                vuint32_t PC0:1;
                vuint32_t PCE:1;
                vuint32_t WL0:1;
                vuint32_t UART:1;
            } B;
        } UARTCR;                       /* LINFLEX UART Mode Control Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t SZF:1;
                vuint32_t OCF:1;
                vuint32_t PE:4;
                vuint32_t RMB:1;
                vuint32_t FEF:1;
                vuint32_t BOF:1;
                vuint32_t RPS:1;
                vuint32_t WUF:1;
                  vuint32_t:1;
                vuint32_t TO:1;
                vuint32_t DRF:1;
                vuint32_t DTF:1;
                vuint32_t NF:1;
            } B;
        } UARTSR;                       /* LINFLEX UART Mode Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:21;
                vuint32_t LTOM:1;
                vuint32_t IOT:1;
                vuint32_t TOCE:1;
                vuint32_t CNT:8;
            } B;
        } LINTCSR;                      /* LINFLEX Time-Out Control Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t OC2:8;
                vuint32_t OC1:8;
            } B;
        } LINOCR;                       /* LINFLEX Output Compare Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:20;
                vuint32_t RTO:4;
                  vuint32_t:1;
                vuint32_t HTO:7;
            } B;
        } LINTOCR;                      /* LINFLEX Output Compare Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:28;
                vuint32_t DIV_F:4;
            } B;
        } LINFBRR;                      /* LINFLEX Fractional Baud Rate Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:12;
                vuint32_t DIV_M:20;
            } B;
        } LINIBRR;                      /* LINFLEX Integer Baud Rate Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:24;
                vuint32_t CF:8;
            } B;
        } LINCFR;                       /* LINFLEX Checksum Field Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:17;
                vuint32_t IOBE:1;
                vuint32_t IOPE:1;
                vuint32_t WURQ:1;
                vuint32_t DDRQ:1;
                vuint32_t DTRQ:1;
                vuint32_t ABRQ:1;
                vuint32_t HTRQ:1;
                  vuint32_t:8;
            } B;
        } LINCR2;                       /* LINFLEX Control Register 2 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t DFL:6;
                vuint32_t DIR:1;
                vuint32_t CCS:1;
                  vuint32_t:2;
                vuint32_t ID:6;
            } B;
        } BIDR;                         /* LINFLEX Buffer Identifier Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t DATA3:8;
                vuint32_t DATA2:8;
                vuint32_t DATA1:8;
                vuint32_t DATA0:8;
            } B;
        } BDRL;                         /* LINFLEX Buffer Data Register Least Significant */

        union {
            vuint32_t R;
            struct {
                vuint32_t DATA7:8;
                vuint32_t DATA6:8;
                vuint32_t DATA5:8;
                vuint32_t DATA4:8;
            } B;
        } BDRM;                         /* LINFLEX Buffer Data Register Most Significant */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:24;
                vuint32_t FACT:8;
            } B;
        } IFER;                         /* LINFLEX Identifier Filter Enable Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:28;
                vuint32_t IFMI:4;
            } B;
        } IFMI;                         /* LINFLEX Identifier Filter Match Index Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:28;
                vuint32_t IFM:4;
            } B;
        } IFMR;                         /* LINFLEX Identifier Filter Mode Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:19;
                vuint32_t DFL:3;
                vuint32_t DIR:1;
                vuint32_t CCS:1;
                  vuint32_t:2;
                vuint32_t ID:6;
            } B;
        } IFCR[16];                     /* LINFLEX Identifier Filter Control Registers */

        union {
            vuint32_t R;
            struct {
                vuint32_t:26;
                vuint32_t TDFBM:1;
                vuint32_t RDFBM:1;
                vuint32_t TDLIS:1;
                vuint32_t RDLIS:1;
                vuint32_t STOP:1;
                vuint32_t SR:1;			
            } B;
        } GCR;                          /* LINFLEX Global Control (+0x008C) */

        union {                 
            vuint32_t R;
            struct {
                vuint32_t:20;
                vuint32_t PTO:12;
            } B;
        } UARTPTO;                      /* LINFLEX UART preset timeout (+0x0090) */
        
        union {
            vuint32_t R;
            struct {
                vuint32_t:20;
                vuint32_t CTO:12;
            } B;
        } UARTCTO;                      /* LINFLEX UART current timeout (+0x0090) */
        
        union {
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t DTE15:1;
                vuint32_t DTE14:1;			
                vuint32_t DTE13:1;			
                vuint32_t DTE12:1;
                vuint32_t DTE11:1;
                vuint32_t DTE10:1;
                vuint32_t DTE9:1;
                vuint32_t DTE8:1;
                vuint32_t DTE7:1;			
                vuint32_t DTE6:1;			
                vuint32_t DTE5:1;			
                vuint32_t DTE4:1;			
                vuint32_t DTE3:1;			
                vuint32_t DTE2:1;			
                vuint32_t DTE1:1;			
                vuint32_t DTE0:1;
            } B;
        } DMATXE;                       /* LINFLEX DMA Tx Enable (+0x0098) */
        
        union {
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t DRE15:1;
                vuint32_t DRE14:1;			
                vuint32_t DRE13:1;			
                vuint32_t DRE12:1;
                vuint32_t DRE11:1;
                vuint32_t DRE10:1;
                vuint32_t DRE9:1;
                vuint32_t DRE8:1;
                vuint32_t DRE7:1;			
                vuint32_t DRE6:1;			
                vuint32_t DRE5:1;			
                vuint32_t DRE4:1;			
                vuint32_t DRE3:1;			
                vuint32_t DRE2:1;			
                vuint32_t DRE1:1;			
                vuint32_t DRE0:1;
            } B;
        } DMARXE;                       /* LINFLEX DMA RX Enable (+0x009C) */
    
};                                  /* end of LINFLEX_tag */
/****************************************************************************/
/*                             MODULE : LINFLEXD Master                     */
/****************************************************************************/
/*	struct LINFLEX_M_tag  {
 * Renamed to LINFLEX_tag to ease implementation in LinFlex driver
 */
    struct LINFLEX_tag  {

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t CCD:1;
                vuint32_t CFD:1;
                vuint32_t LASE:1;
                vuint32_t AWUM:1;
                vuint32_t MBL:4;
                vuint32_t BF:1;
                vuint32_t SLFM:1;
                vuint32_t LBKM:1;
                vuint32_t MME:1;
                vuint32_t SBDT:1;
                vuint32_t RBLM:1;
                vuint32_t SLEEP:1;
                vuint32_t INIT:1;
            } B;
        } LINCR1;                       /* LINFLEX Control Register 1 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t SZIE:1;
                vuint32_t OCIE:1;
                vuint32_t BEIE:1;
                vuint32_t CEIE:1;
                vuint32_t HEIE:1;
                  vuint32_t:2;
                vuint32_t FEIE:1;
                vuint32_t BOIE:1;
                vuint32_t LSIE:1;
                vuint32_t WUIE:1;
                vuint32_t DBFIE:1;
                vuint32_t DBEIE:1;
                vuint32_t DRIE:1;
                vuint32_t DTIE:1;
                vuint32_t HRIE:1;
            } B;
        } LINIER;                       /* LINFLEX Interrupt Enable Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t LINS:4;
                  vuint32_t:2;
                vuint32_t RMB:1;
                  vuint32_t:1;
                vuint32_t RBSY:1;
                vuint32_t RPS:1;
                vuint32_t WUF:1;
                vuint32_t DBFF:1;
                vuint32_t DBEF:1;
                vuint32_t DRF:1;
                vuint32_t DTF:1;
                vuint32_t HRF:1;
            } B;
        } LINSR;                        /* LINFLEX Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t SZF:1;
                vuint32_t OCF:1;
                vuint32_t BEF:1;
                vuint32_t CEF:1;
                vuint32_t SFEF:1;
                vuint32_t BDEF:1;
                vuint32_t IDPEF:1;
                vuint32_t FEF:1;
                vuint32_t BOF:1;
                  vuint32_t:6;
                vuint32_t NF:1;
            } B;
        } LINESR;                       /* LINFLEX LIN Error Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t TDFL:3;
                vuint32_t RDFL:3;
                vuint32_t RFBM:1;
                vuint32_t TFBM:1;
                vuint32_t WL1:1;
                vuint32_t PC1:1;
                vuint32_t RXEN:1;
                vuint32_t TXEN:1;
                vuint32_t PC0:1;
                vuint32_t PCE:1;
                vuint32_t WL0:1;
                vuint32_t UART:1;
            } B;
        } UARTCR;                       /* LINFLEX UART Mode Control Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t SZF:1;
                vuint32_t OCF:1;
                vuint32_t PE:4;
                vuint32_t RMB:1;
                vuint32_t FEF:1;
                vuint32_t BOF:1;
                vuint32_t RPS:1;
                vuint32_t WUF:1;
                  vuint32_t:1;
                vuint32_t TO:1;
                vuint32_t DRF:1;
                vuint32_t DTF:1;
                vuint32_t NF:1;
            } B;
        } UARTSR;                       /* LINFLEX UART Mode Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:21;
                vuint32_t LTOM:1;
                vuint32_t IOT:1;
                vuint32_t TOCE:1;
                vuint32_t CNT:8;
            } B;
        } LINTCSR;                      /* LINFLEX Time-Out Control Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t OC2:8;
                vuint32_t OC1:8;
            } B;
        } LINOCR;                       /* LINFLEX Output Compare Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:20;
                vuint32_t RTO:4;
                  vuint32_t:1;
                vuint32_t HTO:7;
            } B;
        } LINTOCR;                      /* LINFLEX Output Compare Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:28;
                vuint32_t DIV_F:4;
            } B;
        } LINFBRR;                      /* LINFLEX Fractional Baud Rate Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:12;
                vuint32_t DIV_M:20;
            } B;
        } LINIBRR;                      /* LINFLEX Integer Baud Rate Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:24;
                vuint32_t CF:8;
            } B;
        } LINCFR;                       /* LINFLEX Checksum Field Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:17;
                vuint32_t IOBE:1;
                vuint32_t IOPE:1;
                vuint32_t WURQ:1;
                vuint32_t DDRQ:1;
                vuint32_t DTRQ:1;
                vuint32_t ABRQ:1;
                vuint32_t HTRQ:1;
                  vuint32_t:8;
            } B;
        } LINCR2;                       /* LINFLEX Control Register 2 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t DFL:6;
                vuint32_t DIR:1;
                vuint32_t CCS:1;
                  vuint32_t:2;
                vuint32_t ID:6;
            } B;
        } BIDR;                         /* LINFLEX Buffer Identifier Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t DATA3:8;
                vuint32_t DATA2:8;
                vuint32_t DATA1:8;
                vuint32_t DATA0:8;
            } B;
        } BDRL;                         /* LINFLEX Buffer Data Register Least Significant */

        union {
            vuint32_t R;
            struct {
                vuint32_t DATA7:8;
                vuint32_t DATA6:8;
                vuint32_t DATA5:8;
                vuint32_t DATA4:8;
            } B;
        } BDRM;                         /* LINFLEX Buffer Data Register Most Significant */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:24;
                vuint32_t FACT:8;
            } B;
        } IFER;                         /* LINFLEX Identifier Filter Enable Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:28;
                vuint32_t IFMI:4;
            } B;
        } IFMI;                         /* LINFLEX Identifier Filter Match Index Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:28;
                vuint32_t IFM:4;
            } B;
        } IFMR;                         /* LINFLEX Identifier Filter Mode Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t:26;
                vuint32_t TDFBM:1;
                vuint32_t RDFBM:1;
                vuint32_t TDLIS:1;
                vuint32_t RDLIS:1;
                vuint32_t STOP:1;
                vuint32_t SR:1;			
            } B;
        } GCR;                         /* LINFLEX Global Control (+0x004C) */

        union {
            vuint32_t R;
            struct {
                vuint32_t:20;
                vuint32_t PTO:12;
            } B;
        } UARTPTO;                     /* LINFLEX UART preset timeout (+0x0050) */	
        
        union {
            vuint32_t R;
            struct {
                vuint32_t:20;
                vuint32_t CTO:12;
            } B;
        } UARTCTO;                     /* LINFLEX UART current timeout (+0x0054) */
        
        union {
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t DTE15:1;
                vuint32_t DTE14:1;			
                vuint32_t DTE13:1;			
                vuint32_t DTE12:1;
                vuint32_t DTE11:1;
                vuint32_t DTE10:1;
                vuint32_t DTE9:1;
                vuint32_t DTE8:1;
                vuint32_t DTE7:1;			
                vuint32_t DTE6:1;			
                vuint32_t DTE5:1;			
                vuint32_t DTE4:1;			
                vuint32_t DTE3:1;			
                vuint32_t DTE2:1;			
                vuint32_t DTE1:1;			
                vuint32_t DTE0:1;
            } B;
        } DMATXE;                       /* LINFLEX DMA Tx Enable (+0x0058) */	
        
        union {
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t DRE15:1;
                vuint32_t DRE14:1;			
                vuint32_t DRE13:1;			
                vuint32_t DRE12:1;
                vuint32_t DRE11:1;
                vuint32_t DRE10:1;
                vuint32_t DRE9:1;
                vuint32_t DRE8:1;
                vuint32_t DRE7:1;			
                vuint32_t DRE6:1;			
                vuint32_t DRE5:1;			
                vuint32_t DRE4:1;			
                vuint32_t DRE3:1;			
                vuint32_t DRE2:1;			
                vuint32_t DRE1:1;			
                vuint32_t DRE0:1;
            } B;
        } DMARXE;                       /* LINFLEX DMA RX Enable (+0x005C) */
    
};                                  /* end of LINFLEX_tag */
/****************************************************************************/
/*                             MODULE : ME                                  */
/****************************************************************************/
    struct ME_tag {

        union {
            vuint32_t R;
            struct {
                vuint32_t S_CURRENTMODE:4;
                vuint32_t S_MTRANS:1;
                vuint32_t S_DC:1;
                  vuint32_t:2;
                vuint32_t S_PDO:1;
                  vuint32_t:2;
                vuint32_t S_MVR:1;
                vuint32_t S_DFLA:2;
                vuint32_t S_CFLA:2;
                  vuint32_t:8;
                vuint32_t S_FMPLL1:1;
                vuint32_t S_FMPLL0:1;
                vuint32_t S_FXOSC:1;
                vuint32_t S_FIRC:1;
                vuint32_t S_SYSCLK:4;
            } B;
        } GS;                           /* Global Status Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t TARGET_MODE:4;
                  vuint32_t:12;
                vuint32_t KEY:16;
            } B;
        } MCTL;                         /* Mode Control Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:18;
                vuint32_t STANDBY:1;
                  vuint32_t:2;
                vuint32_t STOP:1;
                  vuint32_t:1;
                vuint32_t HALT:1;
                vuint32_t RUN3:1;
                vuint32_t RUN2:1;
                vuint32_t RUN1:1;
                vuint32_t RUN0:1;
                vuint32_t DRUN:1;
                vuint32_t SAFE:1;
                vuint32_t TEST:1;
                vuint32_t RESET:1;
            } B;
        } MER;                          /* Mode Enable Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:28;
                vuint32_t I_ICONF:1;
                vuint32_t I_IMODE:1;
                vuint32_t I_SAFE:1;
                vuint32_t I_MTC:1;
            } B;
        } IS;                           /* Interrupt Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:28;
                vuint32_t M_ICONF:1;
                vuint32_t M_IMODE:1;
                vuint32_t M_SAFE:1;
                vuint32_t M_MTC:1;
            } B;
        } IM;                           /* Interrupt Mask Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:27;
                vuint32_t S_MTI:1;
                vuint32_t S_MRI:1;
                vuint32_t S_DMA:1;
                vuint32_t S_NMA:1;
                vuint32_t S_SEA:1;
            } B;
        } IMTS;                         /* Invalid Mode Transition Status Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t:8;
                vuint32_t MPH_BUSY:1;
                  vuint32_t:2;
                vuint32_t PMC_PROG:1;
                vuint32_t CORE_DBG:1;
                  vuint32_t:2;
                vuint32_t SMR:1;
                vuint32_t FMPLL1_SC:1;
                vuint32_t FMPLL0_SC:1;
                vuint32_t FXOSC_SC:1;
                vuint32_t FIRC_SC:1;
                vuint32_t SSCLK_SC:1;
                vuint32_t SYSCLK_SW:1;
                vuint32_t DFLASH_SC:1;
                vuint32_t CFLASH_SC:1;
                vuint32_t CDP_PRPH_0_143:1;
                  vuint32_t:3;
                vuint32_t CDP_PRPH_96_127:1;
                vuint32_t CDP_PRPH_64_95:1;
                vuint32_t CDP_PRPH_32_63:1;
                vuint32_t CDP_PRPH_0_31:1;
            } B;
        } DMTS;                         /* Invalid Mode Transition Status Register */

        int32_t ME_reserved0;

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t PDO:1;
                  vuint32_t:2;
                vuint32_t MVRON:1;
                vuint32_t:2;
                vuint32_t FLAON:2;
                  vuint32_t:8;
                vuint32_t FMPLL1ON:1;
                vuint32_t FMPLL0ON:1;
                vuint32_t FXOSCON:1;
                vuint32_t FIRCON:1;
                vuint32_t SYSCLK:4;
            } B;
        } RESET;                        /* Reset Mode Configuration Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t PDO:1;
                  vuint32_t:2;
                vuint32_t MVRON:1;
                vuint32_t:2;
                vuint32_t FLAON:2;
                  vuint32_t:8;
                vuint32_t FMPLL1ON:1;
                vuint32_t FMPLL0ON:1;
                vuint32_t FXOSCON:1;
                vuint32_t FIRCON:1;
                vuint32_t SYSCLK:4;
            } B;
        } TEST;                         /* Test Mode Configuration Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t PDO:1;
                  vuint32_t:2;
                vuint32_t MVRON:1;
                vuint32_t:2;
                vuint32_t FLAON:2;
                  vuint32_t:8;
                vuint32_t FMPLL1ON:1;
                vuint32_t FMPLL0ON:1;
                vuint32_t FXOSCON:1;
                vuint32_t FIRCON:1;
                vuint32_t SYSCLK:4;
            } B;
        } SAFE;                         /* Safe Mode Configuration Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t PDO:1;
                  vuint32_t:2;
                vuint32_t MVRON:1;
                vuint32_t:2;
                vuint32_t FLAON:2;
                  vuint32_t:8;
                vuint32_t FMPLL1ON:1;
                vuint32_t FMPLL0ON:1;
                vuint32_t FXOSCON:1;
                vuint32_t FIRCON:1;
                vuint32_t SYSCLK:4;
            } B;
        } DRUN;                         /* DRUN Mode Configuration Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t PDO:1;
                  vuint32_t:2;
                vuint32_t MVRON:1;
                vuint32_t:2;
                vuint32_t FLAON:2;
                  vuint32_t:8;
                vuint32_t FMPLL1ON:1;
                vuint32_t FMPLL0ON:1;
                vuint32_t FXOSCON:1;
                vuint32_t FIRCON:1;
                vuint32_t SYSCLK:4;
            } B;
        } RUN[4];                       /* RUN 0->4 Mode Configuration Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t PDO:1;
                  vuint32_t:2;
                vuint32_t MVRON:1;
                vuint32_t:2;
                vuint32_t FLAON:2;
                  vuint32_t:8;
                vuint32_t FMPLL1ON:1;
                vuint32_t FMPLL0ON:1;
                vuint32_t FXOSCON:1;
                vuint32_t FIRCON:1;
                vuint32_t SYSCLK:4;
            } B;
        } HALT;                         /* HALT Mode Configuration Register */

        int32_t ME_reserved1;

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t PDO:1;
                  vuint32_t:2;
                vuint32_t MVRON:1;
                vuint32_t:2;
                vuint32_t FLAON:2;
                  vuint32_t:8;
                vuint32_t FMPLL1ON:1;
                vuint32_t FMPLL0ON:1;
                vuint32_t FXOSCON:1;
                vuint32_t FIRCON:1;
                vuint32_t SYSCLK:4;
            } B;
        } STOP;                         /* STOP Mode Configuration Register */

        int32_t ME_reserved2[2];

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t PDO:1;
                  vuint32_t:2;
                vuint32_t MVRON:1;
                vuint32_t:2;
                vuint32_t FLAON:2;
                  vuint32_t:8;
                vuint32_t FMPLL1ON:1;
                vuint32_t FMPLL0ON:1;
                vuint32_t FXOSCON:1;
                vuint32_t FIRCON:1;
                vuint32_t SYSCLK:4;
            } B;
        } STANDBY;                      /* STANDBY Mode Configuration Register */

        int32_t ME_reserved3[2];

/* Former declaration included to allow backwards compatibility with Peripheral Status 0->4 Register
        union {
            vuint32_t R;
            struct {
                vuint32_t PERIPH:32;
            } B;
        } PS[4];                        */

        union {
            vuint32_t R;
            struct {
                vuint32_t S_BAM:1;      /* Index 31 */
                  vuint32_t:7;
                vuint32_t S_DMA_CH_MUX:1; /* Index 23 */
                  vuint32_t:4;
                vuint32_t S_FLEXCAN2:1; /* Index 18 */
                vuint32_t S_FLEXCAN1:1; /* Index 17 */
                vuint32_t S_FLEXCAN0:1; /* Index 16 */
                  vuint32_t:7;
                vuint32_t S_QUADSPI:1;  /* Index 8 */
                  vuint32_t:1;
                vuint32_t S_DSPI2:1;    /* Index 6 */
                vuint32_t S_DSPI1:1;    /* Index 5 */
                vuint32_t S_DSPI0:1;    /* Index 4 */
                  vuint32_t:4;
            } B;
        } PS0;                          /* Peripheral Status 0 Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t S_TCON:1;     /* Index 63 */
                vuint32_t S_SGM:1;      /* Index 62 */
                 vuint32_t:1;
                vuint32_t S_CANSAMPLER:1; /* Index 60 */
                  vuint32_t:3;
                vuint32_t S_GAUGEDRIVER:1; /* Index 56 */
                vuint32_t S_DCU:1;      /* Index 55 */
                vuint32_t S_DCULITE:1;  /* Index 54 */
                vuint32_t S_GXG:1;      /* Index 53 */
                vuint32_t S_GFX2D:1;    /* Index 52 */
                vuint32_t S_LINFLEX3:1; /* Index 51 */
                vuint32_t S_LINFLEX2:1; /* Index 50 */
                vuint32_t S_LINFLEX1:1; /* Index 49 */
                vuint32_t S_LINFLEX0:1; /* Index 48 */
                vuint32_t S_I2C_DMA3:1; /* Index 47 */
                vuint32_t S_I2C_DMA2:1; /* Index 46 */
                vuint32_t S_I2C_DMA1:1; /* Index 45 */
                vuint32_t S_I2C_DMA0:1; /* Index 44 */
                  vuint32_t:6;
                vuint32_t S_RLE:1;      /* Index 44 */
                  vuint32_t:4;
                vuint32_t S_ADC0:1;     /* Index 32 */
            } B;
        } PS1;                          /* Peripheral Status 1 Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:3;
                vuint32_t S_PIT_RTI:1;  /* Index 92 */
                vuint32_t S_RTC_API:1;  /* Index 91 */
                vuint32_t S_MC_PCU:1;   /* Index 90 */
                vuint32_t S_MC_RGM:1;   /* Index 89 */
                vuint32_t S_MC_CGM:1;   /* Index 88 */
                vuint32_t S_MC_ME:1;    /* Index 87 */
                vuint32_t S_SSCM:1;     /* Index 86 */
                  vuint32_t:12;
                vuint32_t S_EMIOS1:1;   /* Index 73 */
                vuint32_t S_EMIOS0:1;   /* Index 72 */
                  vuint32_t:2;
                vuint32_t S_WKPU:1;     /* Index 69 */
                vuint32_t S_SIUL:1;     /* Index 68 */
                  vuint32_t:1;
                vuint32_t S_CFLASH0:1;  /* Index 66 */
                  vuint32_t:2;
            } B;
        } PS2;                          /* Peripheral Status 0 Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:23;
                vuint32_t S_CMU0:1;     /* Index 104 */
                  vuint32_t:8;
            } B;
        } PS3;                          /* Peripheral Status 0 Register */

        int32_t ME_reserved4[4];

        union {
            vuint32_t R;
            struct {
                  vuint32_t:24;
                vuint32_t RUN3:1;
                vuint32_t RUN2:1;
                vuint32_t RUN1:1;
                vuint32_t RUN0:1;
                vuint32_t DRUN:1;
                vuint32_t SAFE:1;
                vuint32_t TEST:1;
                vuint32_t RESET:1;
            } B;
        } RUNPC[8];                     /* RUN Peripheral Configuration 0->7 Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:18;
                vuint32_t STANDBY:1;
                  vuint32_t:2;
                vuint32_t STOP:1;
                  vuint32_t:1;
                vuint32_t HALT:1;
                  vuint32_t:8;
            } B;
        } LPPC[8];                      /* Low Power Peripheral Configuration 0->7 Register */

        union {
            vuint8_t R;
            struct {
                  vuint8_t:1;
                vuint8_t DBG_F:1;
                vuint8_t LP_CFG:3;
                vuint8_t RUN_CFG:3;
            } B;
        } PCTL[144];                    /* Peripheral Control 0->143 Register */

    };                                  /* end of ME_tag */
/****************************************************************************/
/*                             MODULE : CGM                                 */
/****************************************************************************/
    
    struct CGM_tag {

    /* The CGM provides a unified register interface, enabling access to 
       all clock sources:

     Base Address |  Clock Sources
    -------------------------------
     C3FE0000      | FXOSC_CTL
     -              | Reserved
     C3FE0040      | SXOSC_CTL
     C3FE0060      | FIRC_CTL
     C3FE0080      | SIRC_CTL
     C3FE00A0      | FMPLL_0
     C3FE00C0      | FMPLL_1
     -              | Reserved
     C3FE0100      | CMU_0 & CMU_1
    */

    /***************************************/
    /* OSC_CTL @ CGM base address + 0x0000 */
    /***************************************/
        union {
            vuint32_t R;
            struct {
                vuint32_t OSCBYP:1;
                  vuint32_t:7;
                vuint32_t EOCV:8;
                vuint32_t M_OSC:1;
                  vuint32_t:2;
                vuint32_t OSCDIV:5;
                vuint32_t I_OSC:1;
                  vuint32_t:7;
            } B;
        } FXOSC_CTL;                    /* Main OSC Control Register */

    /*****************************************/
    /* LPOSC_CTL @ CGM base address + 0x0040 */
    /*****************************************/
        int32_t CGM_reserved0[15];      /* (0x040 - 0x004)/4 = 0x0F */

        union {
            vuint32_t R;
            struct {
                vuint32_t OSCBYP:1;
                  vuint32_t:7;
                vuint32_t EOCV:8;
                vuint32_t M_OSC:1;
                  vuint32_t:2;
                vuint32_t OSCDIV:5;
                vuint32_t I_OSC:1;
                  vuint32_t:5;
                vuint32_t S_OSC:1;
                vuint32_t OSCON:1;
            } B;
        } SXOSC_CTL;                    /* Low Power OSC Control Register */

    /**************************************/
    /* RC_CTL @ CGM base address + 0x0060 */
    /**************************************/
        int32_t CGM_reserved1[7];       /* (0x060 - 0x044)/4 = 0x07 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:10;
                vuint32_t RCTRIM:6;
                  vuint32_t:3;
                vuint32_t RCDIV:5;
                  vuint32_t:2;
                vuint32_t S_RC_STDBY:1;
                  vuint32_t:5;
            } B;
        } FIRC_CTL;                     /* RC OSC Control Register */

    /****************************************/
    /* LPRC_CTL @ CGM base address + 0x0080 */
    /****************************************/
        int32_t CGM_reserved2[7];       /* (0x080 - 0x064)/4 = 0x07 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:11;
                vuint32_t LRCTRIM:5;
                  vuint32_t:3;
                vuint32_t LPRCDIV:5;
                  vuint32_t:3;
                vuint32_t S_LPRC:1;
                  vuint32_t:3;
                vuint32_t LPRCON_STDBY:1;
            } B;
        } SIRC_CTL;                     /* Low Power RC OSC Control Register */

    /***************************************/
    /* FMPLL_0 @ CGM base address + 0x00A0 */
    /* FMPLL_1 @ CGM base address + 0x00C0 */
    /***************************************/
        int32_t CGM_reserved3[7];       /* (0x0A0 - 0x084)/4 = 0x07 */

        struct {
            union {
                vuint32_t R;
                 struct {
                       vuint32_t:2;
                     vuint32_t IDF:4;
                     vuint32_t ODF:2;
                      vuint32_t:1;
                    vuint32_t NDIV:7;
                      vuint32_t:7;
                    vuint32_t EN_PLL_SW:1;
                    vuint32_t MODE:1;
                    vuint32_t UNLOCK_ONCE:1;
                      vuint32_t:1;
                    vuint32_t I_LOCK:1;
                    vuint32_t S_LOCK:1;
                    vuint32_t PLL_FAIL_MASK:1;
                    vuint32_t PLL_FAIL_FLAG:1;
                      vuint32_t:1;
                } B;
            } CR;                       /* FMPLL Control Register */

            union {
                vuint32_t R;
                struct {
                    vuint32_t STRB_BYPASS:1;
                      vuint32_t:1;
                    vuint32_t SPRD_SEL:1;
                    vuint32_t MOD_PERIOD:13;
                    vuint32_t FM_EN:1;
                    vuint32_t INC_STEP:15;
                } B;
            } MR;                       /* FMPLL Modulation Register */

            int32_t CGM_reserved4[6];   /* (0x0C0 - 0x0A8)/4 = 0x06 */
                                        /* (0x0E0 - 0x0C8)/4 = 0x06 */

        } FMPLL[2];

    /************************************/
    /* CMU @ CGM base address + 0x0100  */
    /************************************/
        int32_t CGM_reserved5[8];       /* (0x100 - 0x0E0)/4 = 0x08 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t SFM:1;
                  vuint32_t:13;
                vuint32_t CLKSEL1:2;
                  vuint32_t:5;
                vuint32_t RCDIV:2;
                vuint32_t CME_A:1;
            } B;
        } CMU_CSR;                      /* Control Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:12;
                vuint32_t FD:20;
            } B;
        } CMU_FDR;                      /* Frequency Display Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:20;
                vuint32_t HFREF_A:12;
            } B;
        } CMU_HFREFR_A;                 /* High Frequency Reference Register PLL_A Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:20;
                vuint32_t LFREF_A:12;
            } B;
        } CMU_LFREFR_A;                 /* Low Frequency Reference Register PLL_A Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:29;
                vuint32_t FHHI:1;
                vuint32_t FLLI:1;
                vuint32_t OLRI:1;
            } B;
        } CMU_ISR;                      /* Interrupt Status Register */

        int32_t CGM_reserved6;          /* 0x0014 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:12;
                vuint32_t MD:20;
            } B;
        } CMU_MDR;                      /* Measurement Duration Register */


    /*****************************************************/
    /* CGM VIU_MUX Register @ CGM base address + 0x0340 */
    /*****************************************************/
        int32_t CGM_reserved7[137];     /* (0x340 - 0x11C)/4 = 0x89 */

        union {
            vuint32_t R;
            struct {
                vuint32_t VIU_SEL:1;
                  vuint32_t:28;
                vuint32_t AUTO_DIV2:2;
                  vuint32_t:1;
            } B;
        } VIU_MUX;                        /* VIU Multiplexor register */

    /*****************************************************/
    /* CGM General Registers @ CGM base address + 0x0370 */
    /*****************************************************/
        int32_t CGM_reserved8[11];     /* (0x370 - 0x344)/4 = 0x0B */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:31;
                vuint32_t EN:1;
            } B;
        } OC_EN;                        /* Output Clock Enable Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:2;
                vuint32_t SELDIV:2;
                vuint32_t SELCTL:4;
                  vuint32_t:24;
            } B;
        } OCDS_SC;                      /* Output Clock Division Select Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:4;
                vuint32_t SELSTAT:4;
                  vuint32_t:24;
            } B;
        } SC_SS;                        /* System Clock Select Status */

        union {
            vuint8_t R;
            struct {
                vuint8_t DE:1;
                  vuint8_t:3;
                vuint8_t DIV:4;
            } B;
        } SC_DC[4];                     /* System Clock Divider Configuration 0->3 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:4;
                vuint32_t SELCTL:4;
                  vuint32_t:24;
            } B;
        } AC0_SC;                       /* Aux Clock 0 Select Control */

        union {
            vuint32_t R;
            struct {
                vuint32_t DE0:1;
                  vuint32_t:3;
                vuint32_t DIV0:4;
                  vuint32_t:24;
            } B;
        } AC0_DC;                       /* Aux Clock 0 Divider Configuration */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:4;
                vuint32_t SELCTL:4;
                  vuint32_t:24;
            } B;
        } AC1_SC;                       /* Aux Clock 1 Select Control */

        union {
            vuint32_t R;
            struct {
                vuint32_t DE0:1;
                  vuint32_t:3;
                vuint32_t DIV0:4;
                  vuint32_t:24;
            } B;
        } AC1_DC;                       /* Aux Clock 1 Divider Configuration */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:4;
                vuint32_t SELCTL:4;
                  vuint32_t:24;
            } B;
        } AC2_SC;                       /* Aux Clock 2 Select Control */

        union {
            vuint32_t R;
            struct {
                vuint32_t DE0:1;
                  vuint32_t:3;
                vuint32_t DIV0:4;
                  vuint32_t:24;
            } B;
        } AC2_DC;                       /* Aux Clock 2 Divider Configuration */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:4;
                vuint32_t SELCTL:4;
                  vuint32_t:24;
            } B;
        } AC3_SC;                       /* Aux Clock 3 Select Control */

        union {
            vuint32_t R;
            struct {
                vuint32_t DE0:1;
                  vuint32_t:3;
                vuint32_t DIV0:4;
                  vuint32_t:24;
            } B;
        } AC3_DC;                       /* Aux Clock 3 Divider Configuration */
  
        union {
            vuint32_t R;
            struct {
                  vuint32_t:4;
                vuint32_t SELCTL:4;
                  vuint32_t:24;
            } B;
        } AC4_SC;                       /* Aux Clock 4 Select Control */

        union {
            vuint32_t R;
            struct {
                vuint32_t DE0:1;
                  vuint32_t:3;
                vuint32_t DIV0:4;
                  vuint32_t:24;
            } B;
        } AC4_DC;                       /* Aux Clock 4 Divider Configuration */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:4;
                vuint32_t SELCTL:4;
                  vuint32_t:24;
            } B;
        } AC5_SC;                       /* Aux Clock 5 Select Control */

        union {
            vuint32_t R;
            struct {
                vuint32_t DE0:1;
                  vuint32_t:3;
                vuint32_t DIV0:4;
                  vuint32_t:24;
            } B;
        } AC5_DC;                       /* Aux Clock 5 Divider Configuration */
  
    };                                  /* end of CGM_tag */
/****************************************************************************/
/*                             MODULE : RGM                                 */
/****************************************************************************/
    struct RGM_tag {

        union {
            vuint16_t R;
            struct {
                vuint16_t F_EXR:1;
                  vuint16_t:6;
                vuint16_t F_FLASH:1;
                vuint16_t F_LVD45:1;
                vuint16_t F_CMU_FHL:1;
                vuint16_t F_CMU_OLR:1;
                vuint16_t F_FMPLL0:1;
                vuint16_t F_CHKSTOP:1;
                vuint16_t F_SOFT:1;
                vuint16_t F_CORE:1;
                vuint16_t F_JTAG:1;
            } B;
        } FES;                          /* Functional Event Status */

        union {
            vuint16_t R;
            struct {
                vuint16_t F_POR:1;
                  vuint16_t:11;
                vuint16_t F_LVD27:1;
                vuint16_t F_SWT:1;
                vuint16_t F_LVD12_PD1:1;
                vuint16_t F_LVD12_PD0:1;
            } B;
        } DES;                          /* Destructive Event Status */

        union {
            vuint16_t R;
            struct {
                vuint16_t D_EXR:1;
                  vuint16_t:6;
                vuint16_t D_FLASH:1;
                vuint16_t D_LVD45:1;
                vuint16_t D_CMU0_FHL:1;
                vuint16_t D_CMU0_OLR:1;
                vuint16_t D_FMPLL0:1;
                vuint16_t D_CHKSTOP:1;
                vuint16_t D_SOFT:1;
                vuint16_t D_CORE:1;
                vuint16_t D_JTAG:1;
            } B;
        } FERD;                         /* Functional Event Reset Disable */

        union {
            vuint16_t R;
            struct {
                  vuint16_t:12;
                vuint16_t D_LVD27:1;
                vuint16_t D_SWT:1;
                vuint16_t D_LVD12_PD1:1;
                vuint16_t D_LVD12_PD0:1;
            } B;
        } DERD;                         /* Destructive Event Reset Disable */

        int16_t RGM_reserved0[4];

        union {
            vuint16_t R;
            struct {
                vuint16_t AR_EXR:1;
                  vuint16_t:6;
                vuint16_t AR_FLASH:1;
                vuint16_t AR_LVD45:1;
                vuint16_t AR_CMU_FHL:1;
                vuint16_t AR_CMU_OLR:1;
                vuint16_t AR_FMPLL0:1;
                vuint16_t AR_CHKSTOP:1;
                vuint16_t AR_SOFT:1;
                vuint16_t AR_CORE:1;
                vuint16_t AR_JTAG:1;
            } B;
        } FEAR;                         /* Functional Event Alternate Request */

        union {
            vuint16_t R;
            struct {
                  vuint16_t:12;
                vuint16_t AR_LVD27:1;
                vuint16_t AR_SWT:1;
                vuint16_t AR_LVD12_PD1:1;
                vuint16_t AR_LVD12_PD0:1;
            } B;
        } DEAR;                         /* Destructive Event Alternate Request */

        int16_t RGM_reserved1[2];

        union {
            vuint16_t R;
            struct {
                vuint16_t SS_EXR:1;
                  vuint16_t:6;
                vuint16_t SS_FLASH:1;
                vuint16_t SS_LVD45:1;
                vuint16_t SS_CMU0_FHL:1;
                vuint16_t SS_CMU0_OLR:1;
                vuint16_t SS_FMPLL0:1;
                vuint16_t SS_CHKSTOP:1;
                vuint16_t SS_SOFT:1;
                vuint16_t SS_CORE:1;
                vuint16_t SS_JTAG:1;
            } B;
        } FESS;                         /* Functional Event Short Sequence */

        union {
            vuint16_t R;
            struct {
                  vuint16_t:8;
                vuint16_t BOOT_FROM_BKP_RAM:1;
                  vuint16_t:7;
            } B;
        } STDBY;                        /* STANDBY reset sequence */

        union {
            vuint16_t R;
            struct {
                vuint16_t BE_EXR:1;
                  vuint16_t:6;
                vuint16_t BE_FLASH:1;
                vuint16_t BE_LVD45:1;
                vuint16_t BE_CMU0_FHL:1;
                vuint16_t BE_CMU0_OLR:1;
                vuint16_t BE_FMPLL0:1;
                vuint16_t BE_CHKSTOP:1;
                vuint16_t BE_SOFT:1;
                vuint16_t BE_CORE:1;
                vuint16_t BE_JTAG:1;
            } B;
        } FBRE;                         /* Functional Bidirectional Reset Enable */

    };                                  /* end of RGM_tag */
/****************************************************************************/
/*                             MODULE : PCU                                 */
/****************************************************************************/
    struct PCU_tag {

        union {
            vuint32_t R;
            struct {
                  vuint32_t:18;
                vuint32_t STBY0:1;
                  vuint32_t:2;
                vuint32_t STOP0:1;
                  vuint32_t:1;
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
        } PCONF[3];                     /* Power domain 0-15 configuration register */

        int32_t PCU_reserved0[13];      /* (0x040 - 0x00C)/4 = 0x0D */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:29;
                vuint32_t PD2:1;
                vuint32_t PD1:1;
                vuint32_t PD0:1;
            } B;
        } PSTAT;                        /* Power Domain Status Register */

        int32_t PCU_reserved1[15];      /* {0x0080-0x0044}/0x4 = 0xF */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:31;
                vuint32_t MASK_LVDHV5:1;
            } B;
        } VREG_CTL;                     /* Voltage Regulator Control Register */

    };                                  /* end of PCU_tag */
/****************************************************************************/
/*                             MODULE : DCU v3                              */
/****************************************************************************/
    struct DCU_FG_tag {

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t COLOR:24;
            } B;
        } F;                            /* Transparency layer foreground color */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t COLOR:24;
            } B;
        } B;                            /* Transparency layer foreground color */
    };
    
    struct DCU_LAYER_tag {

        union {
            vuint32_t R;
            struct {
                vuint32_t:5;
                vuint32_t HEIGHT:11;
                  vuint32_t:5;
                vuint32_t WIDTH:11;
            } B;
        } CTRLDESCL1;                   /* LAYER[X].CTRLDESCL1 */

        union {
            vuint32_t R;
            struct {
                vuint32_t:4;
                vuint32_t POSY:12;
                  vuint32_t:4;
                vuint32_t POSX:12;
            } B;
        } CTRLDESCL2;                   /* LAYER[X].CTRLDESCL2 */

        union {
            vuint32_t R;
            struct {
                vuint32_t ADDR:32;
            } B;
        } CTRLDESCL3;                   /* LAYER[X].CTRLDESCL3 */

        union {
            vuint32_t R;
            struct {
                vuint32_t EN:1;
                vuint32_t TILE_EN:1;
                vuint32_t DATA_SEL:1;
                vuint32_t SAFETY_EN:1;
                vuint32_t TRANS:8;
                vuint32_t BPP:4;
                vuint32_t RLE_EN:1;
                vuint32_t LUOFFS:11;
                  vuint32_t:1;
                vuint32_t BB:1;
                vuint32_t AB:2;
            } B;
        } CTRLDESCL4;                   /* LAYER[X].CTRLDESCL4 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t CKMAX_R:8;
                vuint32_t CKMAX_G:8;
                vuint32_t CKMAX_B:8;
            } B;
        } CTRLDESCL5;                   /* LAYER[X].CTRLDESCL5 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t CKMIN_R:8;
                vuint32_t CKMIN_G:8;
                vuint32_t CKMIN_B:8;
            } B;
        } CTRLDESCL6;                   /* LAYER[X].CTRLDESCL6 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t TILE_VER_SIZE:11;
                  vuint32_t:9;
                vuint32_t TILE_HOR_SIZE:7;
            } B;
        } CTRLDESCL7;                   /* LAYER[X].CTRLDESCL7 */

    };                                  /* end of DCU_LAYER_tag */

    struct DCU_tag {

        /* DCU.LAYER<[x]>.CTRLDESCL<y>.R  {x = 0-15, y = 1-7} */
        /* eg DCU.LAYER[0].CTRLDESCL1.R        = 0;           */
        /*      DCU.LAYER[0].CTRLDESCL1.B.HEIGHT = 0;           */
        struct DCU_LAYER_tag LAYER[16];

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t HEIGHT:11;
                  vuint32_t:5;
                vuint32_t WIDTH:11;
            } B;
        } CTRLDESCCURSOR1;              /* Cursor Control Descriptor 1 Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t POSY:11;
                  vuint32_t:5;
                vuint32_t POSX:11;
            } B;
        } CTRLDESCCURSOR2;              /* Cursor Control Descriptor 2 Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t CUR_EN:1;
                  vuint32_t:7;
                vuint32_t CURSOR_DEFAULT_COLOR:24;
            } B;
        } CTRLDESCCURSOR3;              /* Cursor Control Descriptor 3 Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t HWC_BLINK_OFF:8;
                  vuint32_t:7;
                vuint32_t EN_BLINK:1;
                vuint32_t HWC_BLINK_ON:8;
            } B;
        } CTRLDESCCURSOR4;              /* Cursor Control Descriptor 4 Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t DCU_SW_RESET:1;
                vuint32_t DITHER_EN:1;        
                vuint32_t ADDB:2;
                vuint32_t ADDG:2;
                vuint32_t ADDR:2;
                vuint32_t DDR_MODE:1;
                vuint32_t BLEND_ITER:3;
                vuint32_t PDI_SYNC_LOCK:4;
                vuint32_t PDI_INTERPOL_EN:1;        
                vuint32_t RASTER_EN:1;        
                vuint32_t PDI_EN:1;
                vuint32_t PDI_BYTE_REV:1;
                vuint32_t PDI_DE_MODE:1;
                vuint32_t PDI_NARROW_MODE:1;
                vuint32_t PDI_MODE:2;
                vuint32_t PDI_SLAVE_MODE:1;
                vuint32_t TAG_EN:1;
                vuint32_t SIG_EN:1;
                vuint32_t PDI_SYNC:1;
                  vuint32_t:1;
                vuint32_t EN_GAMMA:1;
                vuint32_t DCU_MODE:2;
            } B;
        } DCU_MODE;                     /* Mode Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t BGND_R:8;
                vuint32_t BGND_G:8;
                vuint32_t BGND_B:8;
            } B;
        } BGND;                         /* Background Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t DELTA_Y:11;
                  vuint32_t:9;
                vuint32_t DELTA_X:7;
            } B;
        } DISP_SIZE;                    /* Display Size Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t BP_H:9;
                  vuint32_t:2;
                vuint32_t PW_H:9;
                  vuint32_t:2;
                vuint32_t FP_H:9;
            } B;
        } HSYN_PARA;                    /* Horizontal Synchronisation Parameters Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t BP_V:9;
                  vuint32_t:2;
                vuint32_t PW_V:9;
                  vuint32_t:2;
                vuint32_t FP_V:9;
            } B;
        } VSYN_PARA;                    /* Vertical Synchronisation Parameters Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:21;
                vuint32_t INV_PDI_DE:1;
                vuint32_t INV_PDI_HS:1;
                vuint32_t INV_PDI_VS:1;
                vuint32_t INV_PDI_CLK:1;
                vuint32_t INV_PXCK:1;
                vuint32_t NEG:1;
                vuint32_t BP_VS:1;
                vuint32_t BP_HS:1;
                vuint32_t INV_CS:1;
                vuint32_t INV_VS:1;
                vuint32_t INV_HS:1;
            } B;
        } SYN_POL;                      /* Synchronisation Polarity Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:6;
                vuint32_t LS_BF_VS:10;
                vuint32_t OUT_BUF_HIGH:8;
                vuint32_t OUT_BUF_LOW:8;
            } B;
        } THRESHOLD;                    /* Threshold Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:12;
                vuint32_t P4_FIFO_HI_FLAG:1;
                vuint32_t P4_FIFO_LO_FLAG:1;
                vuint32_t P3_FIFO_HI_FLAG:1;
                vuint32_t P3_FIFO_LO_FLAG:1;
                  vuint32_t:1;
                vuint32_t DMA_TRANS_FINISH:1;
                  vuint32_t:2;
                vuint32_t IPM_ERROR:1;
                vuint32_t PROG_END:1;
                vuint32_t P2_FIFO_HI_FLAG:1;
                vuint32_t P2_FIFO_LO_FLAG:1;
                vuint32_t P1_FIFO_HI_FLAG:1;
                vuint32_t P1_FIFO_LO_FLAG:1;
                vuint32_t CRC_OVERFLOW:1;
                vuint32_t CRC_READY:1;
                vuint32_t VS_BLANK:1;
                vuint32_t LS_BF_VS:1;
                vuint32_t UNDRUN:1;
                vuint32_t VSYNC:1;
            } B;
        } INT_STATUS;                   /* Interrupt Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:12;
                vuint32_t M_P4_FIFO_HI_FLAG:1;
                vuint32_t M_P4_FIFO_LO_FLAG:1;
                vuint32_t M_P3_FIFO_HI_FLAG:1;
                vuint32_t M_P3_FIFO_LO_FLAG:1;
                  vuint32_t:1;
                vuint32_t M_DMA_TRANS_FINISH:1;
                  vuint32_t:2;
                vuint32_t M_IPM_ERROR:1;
                vuint32_t M_PROG_END:1;
                vuint32_t M_P2_FIFO_HI_FLAG:1;
                vuint32_t M_P2_FIFO_LO_FLAG:1;
                vuint32_t M_P1_FIFO_HI_FLAG:1;
                vuint32_t M_P1_FIFO_LO_FLAG:1;
                vuint32_t M_CRC_OVERFLOW:1;
                vuint32_t M_CRC_READY:1;
                vuint32_t M_VS_BLANK:1;
                vuint32_t M_LS_BF_VS:1;
                vuint32_t M_UNDRUN:1;
                vuint32_t M_VSYNC:1;
            } B;
        } INT_MASK;                     /* Interrupt Mask Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t COLBAR_R:8;
                vuint32_t COLBAR_G:8;
                vuint32_t COLBAR_B:8;
            } B;
        } COLBAR[8];                    /* Color Bar 1-8 Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:24;
                vuint32_t DIV_RATIO:8;
            } B;
        } DIV_RATIO;                    /* Clock Divider Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t SIG_VER_SIZE:11;
                  vuint32_t:5;
                vuint32_t SIG_HOR_SIZE:11;
            } B;
        } SIGN_CALC_1;                  /* CRC size configuration */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t SIG_VER_POS:11;
                  vuint32_t:5;
                vuint32_t SIG_HOR_POS:11;
            } B;
        } SIGN_CALC_2;                  /* CRC position configuration */

        union {
            vuint32_t R;
            struct {
                vuint32_t CRC_VAL:32;
            } B;
        } CRC_VAL;                      /* CRC Result register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:22;
                vuint32_t PDI_BLANKING_ERR:1;
                vuint32_t PDI_ECC_ERR2:1;
                vuint32_t PDI_ECC_ERR1:1;
                vuint32_t PDI_LOCK_LOST:1;
                vuint32_t PDI_LOCK_DET:1;
                vuint32_t PDI_VSYNC_DET:1;
                vuint32_t PDI_HSYNC_DET:1;
                vuint32_t PDI_DE_DET:1;
                vuint32_t PDI_CLK_LOST:1;
                vuint32_t PDI_CLK_DET:1;
            } B;
        } PDI_STATUS;                   /* PDI status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:22;
                vuint32_t M_PDI_BLANKING_ERR:1;
                vuint32_t M_PDI_ECC_ERR2:1;
                vuint32_t M_PDI_ECC_ERR1:1;
                vuint32_t M_PDI_LOCK_LOST:1;
                vuint32_t M_PDI_LOCK_DET:1;
                vuint32_t M_PDI_VSYNC_DET:1;
                vuint32_t M_PDI_HSYNC_DET:1;
                vuint32_t M_PDI_DE_DET:1;
                vuint32_t M_PDI_CLK_LOST:1;
                vuint32_t M_PDI_CLK_DET:1;
            } B;
        } MASK_PDI_STATUS;              /* PDI Status Mask Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:12;
                vuint32_t RLE_ERR:1;
                vuint32_t HWC_ERR:1;
                vuint32_t SIG_ERR:1;
                vuint32_t DISP_ERR:1;
                vuint32_t L_PAR_ERR:16;
            } B;
        } PARR_ERR_STATUS;              /* Parameter error status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:12;
                vuint32_t M_RLE_ERR:1;
                vuint32_t M_HWC_ERR:1;
                vuint32_t M_SIG_ERR:1;
                vuint32_t M_DISP_ERR:1;
                vuint32_t M_L_PAR_ERR:16;
            } B;
        } MASK_PARR_ERR_STATUS;         /* Parameter error mask Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t INP_BUF_P2_HI:7;
                  vuint32_t:1;
                vuint32_t INP_BUF_P2_LO:7;
                  vuint32_t:1;
                vuint32_t INP_BUF_P1_HI:7;
                  vuint32_t:1;
                vuint32_t INP_BUF_P1_LO:7;
            } B;
        } THRESHOLD_INP1;               /* Threshold Input Buffer Register 1 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t INP_BUF_P4_HI:7;
                  vuint32_t:1;
                vuint32_t INP_BUF_P4_LO:7;
                  vuint32_t:1;
                vuint32_t INP_BUF_P3_HI:7;
                  vuint32_t:1;
                vuint32_t INP_BUF_P3_LO:7;
            } B;
        } THRESHOLD_INP2;               /* Threshold Input Buffer Register 2 */

        union {
            vuint32_t R;
            struct {
                vuint32_t Y_RED:10;
                  vuint32_t:1;
                vuint32_t Y_GREEN:10;
                  vuint32_t:1;
                vuint32_t Y_BLUE:10;
            } B;
        } LUMA_COMP;                    /* Luminance component Register */    

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t CR_RED:11;
                  vuint32_t:4;
                vuint32_t CB_RED:12;
            } B;
        } CHROMA_RED;                   /* Red component Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t CR_GREEN:11;
                  vuint32_t:4;
                vuint32_t CB_GREEN:12;
            } B;
        } CHROMA_GREEN;                 /* Green component Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t CR_BLUE:11;
                  vuint32_t:4;
                vuint32_t CB_BLUE:12;
            } B;
        } CHROMA_BLUE;                  /* Blue component Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t CRC_POS:32;
            } B;
        } CRC_POS;                      /* CRC Position Register */
    
        struct DCU_FG_tag FG[16];       /* FGCOLOR 1-16 */

        union {
            vuint32_t R;
            struct {
                vuint32_t EN:1;
                  vuint32_t:31;
            } B;
        } LYR_INTPOL_EN;                /* Layer Interpolation Enable Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t Y_RED:10;
                  vuint32_t:1;
                vuint32_t Y_GREEN:10;
                  vuint32_t:1;
                vuint32_t Y_BLUE:10;
            } B;
        } LYR_LUMA_COMP;                /* Layer LUMA Component Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t CR_RED:11;
                  vuint32_t:4;
                vuint32_t CB_RED:12;
            } B;
        } LYR_CHROMA_RED;               /* Layer RED Chroma Component Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t CR_GREEN:11;
                  vuint32_t:4;
                vuint32_t CB_GREEN:12;
            } B;
        } LYR_CHROMA_GREEN;             /* Layer GREEN Chroma Component Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t CR_BLUE:11;
                  vuint32_t:4;
                vuint32_t CB_BLUE:12;
            } B;
        } LYR_CHROMA_BLUE;              /* Layer BLUE Chroma Component Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:10;
                vuint32_t SIZE:22;
            } B;
        } COMP_IMSIZE;                  /* Compressed Image Size Register */

        vuint32_t DCU_reserved1[0x06];  /* 0x300 - 0x2E8 = 6 words */

        union {
            vuint32_t R;
            struct {
                vuint32_t HLB:1;
                  vuint32_t:31;
            } B;
        } GPR;                          /* Global Protection Register */
    
        union {
            vuint32_t R;
            struct {
                vuint32_t WEN_L0_1:1;
                vuint32_t WEN_L0_2:1;
                vuint32_t WEN_L0_3:1;
                vuint32_t WEN_L0_4:1;
                vuint32_t SLB_L0_1:1;
                vuint32_t SLB_L0_2:1;
                vuint32_t SLB_L0_3:1;
                vuint32_t SLB_L0_4:1;
                vuint32_t WEN_L0_5:1;
                vuint32_t WEN_L0_6:1;
                vuint32_t WEN_L0_7:1;
                  vuint32_t:1;
                vuint32_t SLB_L0_5:1;
                vuint32_t SLB_L0_6:1;
                vuint32_t SLB_L0_7:1;
                  vuint32_t:17;
            } B;
        } SLR_L0;                       /* Soft Lock Register Layer 0 */
    
        union {
            vuint32_t R;
            struct {
                vuint32_t WEN_L1_1:1;
                vuint32_t WEN_L1_2:1;
                vuint32_t WEN_L1_3:1;
                vuint32_t WEN_L1_4:1;
                vuint32_t SLB_L1_1:1;
                vuint32_t SLB_L1_2:1;
                vuint32_t SLB_L1_3:1;
                vuint32_t SLB_L1_4:1;
                vuint32_t WEN_L1_5:1;
                vuint32_t WEN_L1_6:1;
                vuint32_t WEN_L1_7:1;
                  vuint32_t:1;
                vuint32_t SLB_L1_5:1;
                vuint32_t SLB_L1_6:1;
                vuint32_t SLB_L1_7:1;
                  vuint32_t:17;
            } B;
        } SLR_L1;                       /* Soft Lock Register Layer 1 */
    
        union {
            vuint32_t R;
            struct {
                vuint32_t WEN_DISP:1;
                  vuint32_t:3;
                vuint32_t SLB_DISP:1;
                  vuint32_t:27;
            } B;
        } SLR_DISP_SIZE;                /* Soft Lock Register DISP_SIZE */
    
        union {
            vuint32_t R;
            struct {
                vuint32_t WEN_HSYNC:1;
                vuint32_t WEN_VSYNC:1;
                  vuint32_t:2;
                vuint32_t SLB_HSYNC:1;
                vuint32_t SLB_VSYNC:1;
                  vuint32_t:26;
            } B;
        } SLR_HVSYNC_PARA;              /* Soft Lock Register HSYNC VSYNC PARA */
    
        union {
            vuint32_t R;
            struct {
                vuint32_t WEN_POL:1;
                  vuint32_t:3;
                vuint32_t SLB_POL:1;
                  vuint32_t:27;
            } B;
        } SLR_POL;                      /* Soft Lock Register POL */
    
        union {
            vuint32_t R;
            struct {
                vuint32_t WEN_L0_FCOLOR:1;
                vuint32_t WEN_L0_BCOLOR:1;
                  vuint32_t:2;
                vuint32_t SLB_L0_FCOLOR:1;
                vuint32_t SLB_L0_BCOLOR:1;
                  vuint32_t:26;
            } B;
        } SLR_L0TRANSP;                 /* Soft Lock Register Layer 0 TRANSP */
    
        union {
            vuint32_t R;
            struct {
                vuint32_t WEN_L1_FCOLOR:1;
                vuint32_t WEN_L1_BCOLOR:1;
                  vuint32_t:2;
                vuint32_t SLB_L1_FCOLOR:1;
                vuint32_t SLB_L1_BCOLOR:1;
                  vuint32_t:26;
            } B;
        } SLR_L1TRANSP;                 /* Soft Lock Register Layer 1 TRANSP */
    
        vuint32_t DCU_reserved2[0x038]; /* Unused from end of registers */

        vuint32_t CURSOR[0x0100];       /* Hardware Cursor = 256 * 32bit */

        vuint32_t GAMMARED[0x100];      /* Gamma red table = 256 * 32bit */

        vuint32_t GAMMAGREEN[0x100];    /* Gamma green table = 256 * 32bit */

        vuint32_t GAMMABLUE[0x100];     /* Gamma blue table = 256 * 32bit */

        vuint32_t DCU_reserved3[0x300]; /* Unused = 768 * 32bit */

        vuint32_t CLUT[0x0800];         /* CLUT-Pallete memory + Tile memory = 2k * 32bit */

    };                                  /* end of DCU_tag */

/****************************************************************************/
/*                             MODULE : SMC - Stepper Motor Control         */
/****************************************************************************/
    struct SMC_tag {

        union {
            vuint8_t R;
            struct {
                  vuint8_t:1;
                vuint8_t MCPRE:2;
                vuint8_t MCHME:1;
                  vuint8_t:1;
                vuint8_t DITH:1;
                  vuint8_t:1;
                vuint8_t MCTOIF:1;
            } B;
        } CTL0;                         /* Motor Controller Control Register 0 */

        union {
            vuint8_t R;
            struct {
                vuint8_t RECIRC:1;
                  vuint8_t:6;
                vuint8_t MCTOIE:1;
            } B;
        } CTL1;                         /* Motor Controller Control Register 1 */

        union {
            vuint16_t R;
            struct {
                  vuint16_t:5;
                vuint16_t PER:11;
            } B;
        } PER;                          /* Motor Controller Period Register */

        int32_t SMC_reserved0[3];       /* (0x010 - 0x004)/4 = 0x01 */

        union {
            vuint8_t R;
            struct {
                vuint8_t MCOM:2;
                vuint8_t MCAM:2;
                  vuint8_t:2;
                vuint8_t CD:2;
            } B;
        } CC[12];                       /* Motor Controller Channel Control Register 0..11 */

        int32_t SMC_reserved1;          /* (0x020 - 0x01C)/4 = 0x01 */

        union {
            vuint16_t R;
            struct {
                vuint16_t SIGN:1;
                vuint16_t SIGN30:4;
                vuint16_t DUTY:11;
            } B;
        } DC[12];                       /* Motor Controller Duty Cycle Register 0..11 */

        int32_t SMC_reserved2[2];       /* (0x040 - 0x038)/2 = 0x02 */

        union {
            vuint8_t R;
            struct {
                vuint8_t TOUT:8;
            } B;
        } SDTO;                         /* Shortcut detector time-out register  */

        int8_t SMC_reserved3[3];        /* (0x044 - 0x041) = 0x03 */

        union {
            vuint8_t R;
            struct {
                vuint8_t SDEN:8;
            } B;
        } SDE[3];                       /* Shortcut detector enable register 0..2 */

        int8_t SMC_reserved4;           /* (0x048 - 0x047) = 0x01 */

        union {
            vuint8_t R;
            struct {
                vuint8_t SDIE:8;
            } B;
        } SDIEN[3];                     /* Shortcut detector interrupt enable register 0..2 */

        int8_t SMC_reserved5;           /* (0x04C - 0x04B) = 0x01 */

        union {
            vuint8_t R;
            struct {
                vuint8_t SDIF:8;
            } B;
        } SDI[3];                       /* Shortcut detector interrupt register 0..2 */

    };                                  /* end of SMC_tag */
/****************************************************************************/
/*                             MODULE : SSD - Stepper Stall Detect          */
/****************************************************************************/
    struct SSD_tag {

        union {
            vuint16_t R;
            struct {
                vuint16_t TRIG:1;
                vuint16_t STEP:2;
                vuint16_t RCIR:1;
                vuint16_t ITGDIR:1;
                vuint16_t BLNDCL:1;
                vuint16_t ITGDCL:1;
                vuint16_t RTZE:1;
                  vuint16_t:1;
                vuint16_t BLNST:1;
                vuint16_t ITGST:1;
                  vuint16_t:3;
                vuint16_t SDCPU:1;
                vuint16_t DZDIS:1;
            } B;
        } CONTROL;                      /* Control & Status Register */

        union {
            vuint16_t R;
            struct {
                vuint16_t BLNIF:1;
                vuint16_t ITGIF:1;
                  vuint16_t:5;
                vuint16_t ACOVIF:1;
                vuint16_t BLNIE:1;
                vuint16_t ITGIE:1;
                  vuint16_t:5;
                vuint16_t ACOVIE:1;
            } B;
        } IRQ;                          /* Interrupt Flag and Enable Register */

        union {
            vuint16_t R;
            struct {
                vuint16_t ITGACC:16;
            } B;
        } ITGACC;                       /* Integrator Accumulator register */

        union {
            vuint16_t R;
            struct {
                vuint16_t DCNT:16;
            } B;
        } DCNT;                         /* Down Counter Count register */

        union {
            vuint16_t R;
            struct {
                vuint16_t BLNCNTLD:16;
            } B;
        } BLNCNTLD;                     /* Blanking Counter Load register */

        union {
            vuint16_t R;
            struct {
                vuint16_t ITGCNTLD:16;
            } B;
        } ITGCNTLD;                     /* Integration Counter Load register */

        union {
            vuint16_t R;
            struct {
                  vuint16_t:1;
                vuint16_t BLNDIV:3;
                  vuint16_t:1;
                vuint16_t ITGDIV:3;
                  vuint16_t:2;
                vuint16_t OFFCNC:2;
                  vuint16_t:1;
                vuint16_t ACDIV:3;
            } B;
        } PRESCALE;                     /* Prescaler register */

        union {
            vuint16_t R;
            struct {
                vuint16_t TMST:1;
                vuint16_t ANLOUT:1;
                vuint16_t ANLIN:1;
                vuint16_t SSDEN:1;
                vuint16_t STEP1:1;
                vuint16_t POL:1;
                vuint16_t ITG:1;
                vuint16_t DACHIZ:1;
                vuint16_t BUFHIZ:1;
                vuint16_t AMPHIZ:1;
                vuint16_t RESSHORT:1;
                vuint16_t ITSSDRV:1;
                vuint16_t ITSSDRVEN:1;
                vuint16_t REFDRV:1;
                vuint16_t REFDRVEN:1;
            } B;
        } FNTEST;                       /* Functional Test Mode register */

    };                                  /* end of SSD_tag */
/****************************************************************************/
/*                             MODULE : EMIOS                               */
/****************************************************************************/
    struct EMIOS_CHANNEL_tag {
        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t CADR:16;
            } B;
        } CADR;                         /* Channel A Data Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t CBDR:16;
            } B;
        } CBDR;                         /* Channel B Data Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t CCNTR:16;
            } B;
        } CCNTR;                        /* Channel Counter Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t FREN:1;
                vuint32_t ODIS:1;
                vuint32_t ODISSL:2;
                vuint32_t UCPRE:2;
                vuint32_t UCPEN:1;
                vuint32_t DMA:1;
                  vuint32_t:1;
                vuint32_t IF:4;
                vuint32_t FCK:1;
                vuint32_t FEN:1;
                  vuint32_t:3;
                vuint32_t FORCMA:1;
                vuint32_t FORCMB:1;
                  vuint32_t:1;
                vuint32_t BSL:2;
                vuint32_t EDSEL:1;
                vuint32_t EDPOL:1;
                vuint32_t MODE:7;
            } B;
        } CCR;                          /* Channel Control Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t OVR:1;
                  vuint32_t:15;
                vuint32_t OVFL:1;
                  vuint32_t:12;
                vuint32_t UCIN:1;
                vuint32_t UCOUT:1;
                vuint32_t FLAG:1;
            } B;
        } CSR;                          /* Channel Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t ALTCADR:16;
            } B;
        } ALTCADR;                      /* Alternate Channel A Data Register */

        uint32_t emios_channel_reserved[2];

    };                                  /* end of EMIOS_CHANNEL_tag */

    struct EMIOS_tag {
        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t MDIS:1;
                vuint32_t FRZ:1;
                vuint32_t GTBE:1;
                vuint32_t ETB:1;
                vuint32_t GPREN:1;
                  vuint32_t:6;
                vuint32_t SRV:4;
                vuint32_t GPRE:8;
                  vuint32_t:8;
            } B;
        } MCR;                          /* Module Configuration Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t F23:1;
                vuint32_t F22:1;
                vuint32_t F21:1;
                vuint32_t F20:1;
                vuint32_t F19:1;
                vuint32_t F18:1;
                vuint32_t F17:1;
                vuint32_t F16:1;
                vuint32_t F15:1;
                vuint32_t F14:1;
                vuint32_t F13:1;
                vuint32_t F12:1;
                vuint32_t F11:1;
                vuint32_t F10:1;
                vuint32_t F9:1;
                vuint32_t F8:1;
                vuint32_t F7:1;
                vuint32_t F6:1;
                vuint32_t F5:1;
                vuint32_t F4:1;
                vuint32_t F3:1;
                vuint32_t F2:1;
                vuint32_t F1:1;
                vuint32_t F0:1;
            } B;
        } GFR;                          /* Global FLAG Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t OU23:1;
                vuint32_t OU22:1;
                vuint32_t OU21:1;
                vuint32_t OU20:1;
                vuint32_t OU19:1;
                vuint32_t OU18:1;
                vuint32_t OU17:1;
                vuint32_t OU16:1;
                vuint32_t OU15:1;
                vuint32_t OU14:1;
                vuint32_t OU13:1;
                vuint32_t OU12:1;
                vuint32_t OU11:1;
                vuint32_t OU10:1;
                vuint32_t OU9:1;
                vuint32_t OU8:1;
                vuint32_t OU7:1;
                vuint32_t OU6:1;
                vuint32_t OU5:1;
                vuint32_t OU4:1;
                vuint32_t OU3:1;
                vuint32_t OU2:1;
                vuint32_t OU1:1;
                vuint32_t OU0:1;
            } B;
        } OUDR;                         /* Output Update Disable Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t CHDIS23:1;
                vuint32_t CHDIS22:1;
                vuint32_t CHDIS21:1;
                vuint32_t CHDIS20:1;
                vuint32_t CHDIS19:1;
                vuint32_t CHDIS18:1;
                vuint32_t CHDIS17:1;
                vuint32_t CHDIS16:1;
                vuint32_t CHDIS15:1;
                vuint32_t CHDIS14:1;
                vuint32_t CHDIS13:1;
                vuint32_t CHDIS12:1;
                vuint32_t CHDIS11:1;
                vuint32_t CHDIS10:1;
                vuint32_t CHDIS9:1;
                vuint32_t CHDIS8:1;
                vuint32_t CHDIS7:1;
                vuint32_t CHDIS6:1;
                vuint32_t CHDIS5:1;
                vuint32_t CHDIS4:1;
                vuint32_t CHDIS3:1;
                vuint32_t CHDIS2:1;
                vuint32_t CHDIS1:1;
                vuint32_t CHDIS0:1;
            } B;
        } UCDIS;                        /* Disable Channel Register */

        uint32_t emios_reserved1[4];

        struct EMIOS_CHANNEL_tag CH[24];

    };                                  /* end of EMIOS_tag */
/****************************************************************************/
/*                             MODULE : PIT                                 */
/****************************************************************************/
    struct PIT_tag {
        union {
            vuint32_t R;
            struct {
                  vuint32_t:30;
                vuint32_t MDIS:1;
                vuint32_t FRZ:1;
            } B;
        } MCR;                          /* Module Control Register */

        uint32_t pit_reserved1[63];     /* (0x0100 - 0x0004)/4 = 0x3F */

        struct {
            union {
                vuint32_t R;
                struct {
                    vuint32_t TSV:32;
                 } B;
             } LDVAL;                   /* Timer Load Value Register */

             union {
                vuint32_t R;
                 struct {
                     vuint32_t TVL:32;
                 } B;
             } CVAL;                    /* Current Timer Value Register */

             union {
                vuint32_t R;
                 struct {
                       vuint32_t:30;
                     vuint32_t TIE:1;
                     vuint32_t TEN:1;
                 } B;
             } TCTRL;                   /* Timer Control Register */

             union {
                vuint32_t R;
                 struct {
                       vuint32_t:31;
                     vuint32_t TIF:1;
                 } B;
             } TFLG;                    /* Timer Flasg Register */
        } CH[8];

    };                                  /* end of PIT_tag */
/****************************************************************************/
/*                             MODULE : I2C                                 */
/****************************************************************************/
    struct I2C_tag {
        union {
            vuint8_t R;
            struct {
                vuint8_t ADR:7;
                  vuint8_t:1;
            } B;
        } IBAD;                         /* Module Bus Address Register */

        union {
            vuint8_t R;
            struct {
                vuint8_t IBC:8;
            } B;
        } IBFD;                         /* Module Bus Frequency Register */

        union {
            vuint8_t R;
            struct {
                vuint8_t MDIS:1;
                vuint8_t IBIE:1;
                vuint8_t MS:1;
                vuint8_t TX:1;
                vuint8_t NOACK:1;
                vuint8_t RSTA:1;
                vuint8_t DMAEN:1;
                vuint8_t IBDOZE:1;
            } B;
        } IBCR;                         /* Module Bus Control Register */

        union {
            vuint8_t R;
            struct {
                vuint8_t TCF:1;
                vuint8_t IAAS:1;
                vuint8_t IBB:1;
                vuint8_t IBAL:1;
                  vuint8_t:1;
                vuint8_t SRW:1;
                vuint8_t IBIF:1;
                vuint8_t RXAK:1;
            } B;
        } IBSR;                         /* Module Status Register */

        union {
            vuint8_t R;
            struct {
                vuint8_t DATA:8;
            } B;
        } IBDR;                         /* Module Data Register */

        union {
            vuint8_t R;
            struct {
                vuint8_t BIIE:1;
                  vuint8_t:7;
            } B;
        } IBIC;                         /* Module Interrupt Configuration Register */

    };                                  /* end of I2C_tag */
/****************************************************************************/
/*                             MODULE : MPU                                 */
/****************************************************************************/
    struct MPU_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t SPERR:8;
                  vuint32_t:4;
                vuint32_t HRL:4;
                vuint32_t NSP:4;
                vuint32_t NGRD:4;
                  vuint32_t:7;
                vuint32_t VLD:1;
            } B;
        } CESR;                         /* Module Control/Error Status Register */

        uint32_t mpu_reserved1[3];      /* (0x010 - 0x004)/4 = 0x03 */

        union {
            vuint32_t R;
            struct {
                vuint32_t EADDR:32;
            } B;
        } EAR0;                         /* Error Address Register port 0*/

        union {
            vuint32_t R;
            struct {
                vuint32_t EACD:16;
                vuint32_t EPID:8;
                vuint32_t EMN:4;
                vuint32_t EATTR:3;
                vuint32_t ERW:1;
            } B;
        } EDR0;                         /* Error Detail Register port 0 */

        union {
            vuint32_t R;
            struct {
                vuint32_t EADDR:32;
            } B;
        } EAR1;                         /* Error Address Register port 1 */

        union {
            vuint32_t R;
            struct {
                vuint32_t EACD:16;
                vuint32_t EPID:8;
                vuint32_t EMN:4;
                vuint32_t EATTR:3;
                vuint32_t ERW:1;
            } B;
        } EDR1;                         /* Error Detail Register port 1 */

        union {
            vuint32_t R;
            struct {
                vuint32_t EADDR:32;
            } B;
        } EAR2;                         /* Error Address Register port 2 */

        union {
            vuint32_t R;
            struct {
                vuint32_t EACD:16;
                vuint32_t EPID:8;
                vuint32_t EMN:4;
                vuint32_t EATTR:3;
                vuint32_t ERW:1;
            } B;
        } EDR2;                         /* Error Detail Register port 2 */

        union {
            vuint32_t R;
            struct {
                vuint32_t EADDR:32;
            } B;
        } EAR3;                         /* Error Address Register port 3 */

        union {
            vuint32_t R;
            struct {
                vuint32_t EACD:16;
                vuint32_t EPID:8;
                vuint32_t EMN:4;
                vuint32_t EATTR:3;
                vuint32_t ERW:1;
            } B;
        } EDR3;                         /* Error Detail Register port 3 */

        uint32_t mpu_reserved2[244];    /* (0x0400 - 0x0030)/4 = 0x0F4 */

        struct {
            union {
                vuint32_t R;
                struct {
                     vuint32_t SRTADDR:27;
                      vuint32_t:5;
                 } B;
             } WORD0;                   /* Region Descriptor n Word 0 */

             union {
                vuint32_t R;
                 struct {
                     vuint32_t ENDADDR:27;
                      vuint32_t:5;
                 } B;
             } WORD1;                   /* Region Descriptor n Word 1 */

             union {
                vuint32_t R;
                 struct {
                     vuint32_t M7RE:1;
                     vuint32_t M7WE:1;
                     vuint32_t M6RE:1;
                     vuint32_t M6WE:1;
                     vuint32_t M5RE:1;
                     vuint32_t M5WE:1;
                     vuint32_t M4RE:1;
                     vuint32_t M4WE:1;
                     vuint32_t M3PE:1;
                     vuint32_t M3SM:2;
                     vuint32_t M3UM:3;
                     vuint32_t M2PE:1;
                     vuint32_t M2SM:2;
                     vuint32_t M2UM:3;
                     vuint32_t M1PE:1;
                     vuint32_t M1SM:2;
                     vuint32_t M1UM:3;
                     vuint32_t M0PE:1;
                     vuint32_t M0SM:2;
                     vuint32_t M0UM:3;
                 } B;
             } WORD2;                   /* Region Descriptor n Word 2 */

             union {
                vuint32_t R;
                 struct {
                     vuint32_t PID:8;
                     vuint32_t PIDMASK:8;
                      vuint32_t:15;
                     vuint32_t VLD:1;
                 } B;
             } WORD3;                   /* Region Descriptor n Word 3 */

        } RGD[16];

        uint32_t mpu_reserved3[192];    /* (0x0800 - 0x0500)/4 = 0x0C0 */

        union {
            vuint32_t R;
            struct {
                vuint32_t M7RE:1;
                vuint32_t M7WE:1;
                vuint32_t M6RE:1;
                vuint32_t M6WE:1;
                vuint32_t M5RE:1;
                vuint32_t M5WE:1;
                vuint32_t M4RE:1;
                vuint32_t M4WE:1;
                vuint32_t M3PE:1;
                vuint32_t M3SM:2;
                vuint32_t M3UM:3;
                vuint32_t M2PE:1;
                vuint32_t M2SM:2;
                vuint32_t M2UM:3;
                vuint32_t M1PE:1;
                vuint32_t M1SM:2;
                vuint32_t M1UM:3;
                vuint32_t M0PE:1;
                vuint32_t M0SM:2;
                vuint32_t M0UM:3;
            } B;
        } RGDAAC[16];                   /* Region Descriptor Alternate Access Control n */

    };                                  /* end of MPU_tag */
/****************************************************************************/
/*                             MODULE : eDMA                                */
/****************************************************************************/

/*for "standard" format TCD (when EDMA.TCD[x].CITER.E_LINK==BITER.E_LINK=0) */
    struct EDMA_TCD_STD_tag {

        vuint32_t SADDR;                /* source address */

        vuint16_t SMOD:5;               /* source address modulo */
        vuint16_t SSIZE:3;              /* source transfer size */
        vuint16_t DMOD:5;               /* destination address modulo */
        vuint16_t DSIZE:3;              /* destination transfer size */
        vint16_t SOFF;                  /* signed source address offset */

        union {
            vuint32_t R;
            struct {
                vuint32_t SMLOE:1;
                vuint32_t DMLOE:1;
                int32_t   MLOFF:20;
                vuint32_t NBYTES:10;
            } B;
        } NBYTESu;                      /* Region Descriptor Alternate Access Control n */
    
        vint32_t SLAST;                 /* last destination address adjustment, or
                                          scatter/gather address (if e_sg = 1) */

        vuint32_t DADDR;                /* destination address */

        vuint16_t CITERE_LINK:1;
        vuint16_t CITER:15;

        vint16_t DOFF;                  /* signed destination address offset */

        vint32_t DLAST_SGA;

        vuint16_t BITERE_LINK:1;        /* beginning ("major") iteration count */
        vuint16_t BITER:15;

        vuint16_t BWC:2;                /* bandwidth control */
        vuint16_t MAJORLINKCH:6;        /* enable channel-to-channel link */
        vuint16_t DONE:1;               /* channel done */
        vuint16_t ACTIVE:1;             /* channel active */
        vuint16_t MAJORE_LINK:1;        /* enable channel-to-channel link */
        vuint16_t E_SG:1;               /* enable scatter/gather descriptor */
        vuint16_t D_REQ:1;              /* disable ipd_req when done */
        vuint16_t INT_HALF:1;           /* interrupt on citer = (biter >> 1) */
        vuint16_t INT_MAJ:1;            /* interrupt on major loop completion */
        vuint16_t START:1;              /* explicit channel start */

    };                                  /* end of EDMA_TCD_STD_tag */

/*for "channel link" format TCD (when EDMA.TCD[x].CITER.E_LINK==BITER.E_LINK=1)*/
    struct EDMA_TCD_CHLINK_tag {

        vuint32_t SADDR;                /* source address */

        vuint16_t SMOD:5;               /* source address modulo */
        vuint16_t SSIZE:3;              /* source transfer size */
        vuint16_t DMOD:5;               /* destination address modulo */
        vuint16_t DSIZE:3;              /* destination transfer size */
        vint16_t SOFF;                  /* signed source address offset */

        union {
            vuint32_t R;
            struct {
                vuint32_t SMLOE:1;
                vuint32_t DMLOE:1;
                int32_t   MLOFF:20;
                vuint32_t NBYTES:10;
            } B;
        } NBYTESu;                      /* Region Descriptor Alternate Access Control n */
        vint32_t SLAST;                 /* last destination address adjustment, or
                                          scatter/gather address (if e_sg = 1) */

        vuint32_t DADDR;                /* destination address */

        vuint16_t CITERE_LINK:1;
        vuint16_t CITERLINKCH:6;
        vuint16_t CITER:9;

        vint16_t DOFF;                  /* signed destination address offset */

        vint32_t DLAST_SGA;

        vuint16_t BITERE_LINK:1;        /* beginning (�major�) iteration count */
        vuint16_t BITERLINKCH:6;
        vuint16_t BITER:9;

        vuint16_t BWC:2;                /* bandwidth control */
        vuint16_t MAJORLINKCH:6;        /* enable channel-to-channel link */
        vuint16_t DONE:1;               /* channel done */
        vuint16_t ACTIVE:1;             /* channel active */
        vuint16_t MAJORE_LINK:1;        /* enable channel-to-channel link */
        vuint16_t E_SG:1;               /* enable scatter/gather descriptor */
        vuint16_t D_REQ:1;              /* disable ipd_req when done */
        vuint16_t INT_HALF:1;           /* interrupt on citer = (biter >> 1) */
        vuint16_t INT_MAJ:1;            /* interrupt on major loop completion */
        vuint16_t START:1;              /* explicit channel start */    

    };                                  /* end of EDMA_TCD_CHLINK_tag */

    struct EDMA_tag {
        union {
            vuint32_t R;
            struct {
                  vuint32_t:14;
                vuint32_t CX:1;
                vuint32_t ECX:1;
                vuint32_t GRP3PRI:2;
                vuint32_t GRP2PRI:2;
                vuint32_t GRP1PRI:2;
                vuint32_t GRP0PRI:2;
                vuint32_t EMLM:1;
                vuint32_t CLM:1;
                vuint32_t HALT:1;
                vuint32_t HOE:1;
                vuint32_t ERGA:1;
                vuint32_t ERCA:1;
                vuint32_t EDBG:1;
                vuint32_t EBW:1;
            } B;
        } CR;                           /* Control Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t VLD:1;
                  vuint32_t:14;
                vuint32_t ECX:1;
                vuint32_t GPE:1;
                vuint32_t CPE:1;
                vuint32_t ERRCHN:6;
                vuint32_t SAE:1;
                vuint32_t SOE:1;
                vuint32_t DAE:1;
                vuint32_t DOE:1;
                vuint32_t NCE:1;
                vuint32_t SGE:1;
                vuint32_t SBE:1;
                vuint32_t DBE:1;
            } B;
        } ES;                           /* Error Status Register */

        int16_t EDMA_reserved1[3];      /* (0x0E - 0x08)/2 = 0x03 */

        union {
            vuint16_t R;
            struct {
                vuint16_t ERQ15:1;
                vuint16_t ERQ14:1;
                vuint16_t ERQ13:1;
                vuint16_t ERQ12:1;
                vuint16_t ERQ11:1;
                vuint16_t ERQ10:1;
                vuint16_t ERQ09:1;
                vuint16_t ERQ08:1;
                vuint16_t ERQ07:1;
                vuint16_t ERQ06:1;
                vuint16_t ERQ05:1;
                vuint16_t ERQ04:1;
                vuint16_t ERQ03:1;
                vuint16_t ERQ02:1;
                vuint16_t ERQ01:1;
                vuint16_t ERQ00:1;
            } B;
        } ERQL;                         /* DMA Enable Request Low */

        int16_t EDMA_reserved2[3];      /* (0x16 - 0x10)/2 = 0x03 */

        union {
            vuint16_t R;
            struct {
                vuint16_t EEI15:1;
                vuint16_t EEI14:1;
                vuint16_t EEI13:1;
                vuint16_t EEI12:1;
                vuint16_t EEI11:1;
                vuint16_t EEI10:1;
                vuint16_t EEI09:1;
                vuint16_t EEI08:1;
                vuint16_t EEI07:1;
                vuint16_t EEI06:1;
                vuint16_t EEI05:1;
                vuint16_t EEI04:1;
                vuint16_t EEI03:1;
                vuint16_t EEI02:1;
                vuint16_t EEI01:1;
                vuint16_t EEI00:1;
            } B;
        } EEIL;                         /* DMA Enable Error Interrupt Low */

        union {
            vuint8_t R;
            struct {
                vuint8_t NOP:1;
                vuint8_t SERQ:7;
            } B;
        } SERQ;                         /* DMA Set Enable Request Register */

        union {
            vuint8_t R;
            struct {
                vuint8_t NOP:1;
                vuint8_t CERQ:7;
            } B;
        } CERQ;                         /* DMA Clear Enable Request Register */

        union {
            vuint8_t R;
            struct {
                vuint8_t NOP:1;
                vuint8_t SEEI:7;
            } B;
        } SEEI;                         /* DMA Set Enable Error Interrupt Register */

        union {
            vuint8_t R;
            struct {
                vuint8_t NOP:1;
                vuint8_t CEEI:7;
            } B;
        } CEEI;                         /* DMA Clear Enable Error Interrupt Register */

        union {
            vuint8_t R;
            struct {
                vuint8_t NOP:1;
                vuint8_t CINT:7;
            } B;
        } CINT;                         /* DMA Clear Interrupt Request Register */

        union {
            vuint8_t R;
            struct {
                vuint8_t NOP:1;
                vuint8_t CER:7;
            } B;
        } CERR;                         /* DMA Clear error Register */

        union {
            vuint8_t R;
            struct {
                vuint8_t NOP:1;
                vuint8_t SSB:7;
            } B;
        } SSRT;                         /* Set Start Bit Register */

        union {
            vuint8_t R;
            struct {
                vuint8_t NOP:1;
                vuint8_t CDNE:7;
            } B;
        } CDNE;                         /* Clear Done Status Bit Register */

        int16_t EDMA_reserved3[3];      /* (0x26 - 0x20)/2 = 0x03 */

        union {
            vuint16_t R;
            struct {
                vuint16_t INT15:1;
                vuint16_t INT14:1;
                vuint16_t INT13:1;
                vuint16_t INT12:1;
                vuint16_t INT11:1;
                vuint16_t INT10:1;
                vuint16_t INT09:1;
                vuint16_t INT08:1;
                vuint16_t INT07:1;
                vuint16_t INT06:1;
                vuint16_t INT05:1;
                vuint16_t INT04:1;
                vuint16_t INT03:1;
                vuint16_t INT02:1;
                vuint16_t INT01:1;
                vuint16_t INT00:1;
            } B;
        } INTL;                         /* DMA Interrupt Request Low */

        int16_t EDMA_reserved4[3];      /* (0x2E - 0x28)/2 = 0x03 */

        union {
            vuint16_t R;
            struct {
                vuint16_t ERR15:1;
                vuint16_t ERR14:1;
                vuint16_t ERR13:1;
                vuint16_t ERR12:1;
                vuint16_t ERR11:1;
                vuint16_t ERR10:1;
                vuint16_t ERR09:1;
                vuint16_t ERR08:1;
                vuint16_t ERR07:1;
                vuint16_t ERR06:1;
                vuint16_t ERR05:1;
                vuint16_t ERR04:1;
                vuint16_t ERR03:1;
                vuint16_t ERR02:1;
                vuint16_t ERR01:1;
                vuint16_t ERR00:1;
            } B;
        } ERRL;                         /* DMA Error Low */

        int16_t EDMA_reserved5[3];      /* (0x36 - 0x30)/2 = 0x03 */

        union {
            vuint16_t R;
            struct {
                vuint16_t HRS15:1;
                vuint16_t HRS14:1;
                vuint16_t HRS13:1;
                vuint16_t HRS12:1;
                vuint16_t HRS11:1;
                vuint16_t HRS10:1;
                vuint16_t HRS09:1;
                vuint16_t HRS08:1;
                vuint16_t HRS07:1;
                vuint16_t HRS06:1;
                vuint16_t HRS05:1;
                vuint16_t HRS04:1;
                vuint16_t HRS03:1;
                vuint16_t HRS02:1;
                vuint16_t HRS01:1;
                vuint16_t HRS00:1;
            } B;
        } HRSL;                         /* DMA Hardware Request Status Low */

        uint32_t edma_reserved1[50];    /* (0x100 - 0x038)/4 = 0x32 */

        union {
            vuint8_t R;
            struct {
                vuint8_t ECP:1;
                vuint8_t DPA:1;
                vuint8_t GRPPRI:2;
                vuint8_t CHPRI:4;
            } B;
        } CPR[16];                      /* Channel n Priority */

        uint32_t edma_reserved2[956];   /* (0x1000 - 0x0110)/4 = 0x3BC */

    /* Select one of the following declarations depending on the DMA mode chosen */
        struct EDMA_TCD_STD_tag TCD[16];
        /* struct EDMA_TCD_CHLINK_tag TCD[16]; */

    };                                  /* end of EDMA_tag */
/****************************************************************************/
/*                             MODULE : INTC                                */
/****************************************************************************/
    struct INTC_tag {
        union {
            vuint32_t R;
            struct {
                  vuint32_t:26;
                vuint32_t VTES:1;
                  vuint32_t:4;
                vuint32_t HVEN:1;
            } B;
        } MCR;                          /* Module Configuration Register */

        int32_t INTC_reserved1;         /* (0x008 - 0x004)/4 = 0x01 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:28;
                vuint32_t PRI:4;
            } B;
        } CPR;                          /* Current Priority Register */

        int32_t INTC_reserved2;         /* (0x010 - 0x00C)/4 = 0x01 */

        union {
            vuint32_t R;
            struct {
                vuint32_t VTBA:21;
                vuint32_t INTVEC:9;
                  vuint32_t:2;
            } B;
        } IACKR;                        /* Interrupt Acknowledge Register */

        int32_t INTC_reserved3;         /* (0x018 - 0x014)/4 = 0x01 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:32;
            } B;
        } EOIR;                         /* End of Interrupt Register */

        int32_t INTC_reserved4;         /* (0x020 - 0x01C)/4 = 0x01 */

        union {
            vuint8_t R;
            struct {
                  vuint8_t:6;
                vuint8_t SET:1;
                vuint8_t CLR:1;
            } B;
        } SSCIR[8];                     /* Software Set/Clear Interruput Register */

        uint32_t intc_reserved5[6];     /* (0x040 - 0x028)/4 = 0x06 */

        union {
            vuint8_t R;
            struct {
                  vuint8_t:4;
                vuint8_t PRI:4;
            } B;
        } PSR[239];                     /* Software Set/Clear Interrupt Register */

    };                                  /* end of INTC_tag */
/****************************************************************************/
/*                             MODULE : DSPI                                */
/****************************************************************************/
    struct DSPI_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t MSTR:1;
                vuint32_t CONT_SCKE:1;
                vuint32_t DCONF:2;
                vuint32_t FRZ:1;
                vuint32_t MTFE:1;
                vuint32_t PCSSE:1;
                vuint32_t ROOE:1;
                  vuint32_t:2;
                vuint32_t PCSIS5:1;
                vuint32_t PCSIS4:1;
                vuint32_t PCSIS3:1;
                vuint32_t PCSIS2:1;
                vuint32_t PCSIS1:1;
                vuint32_t PCSIS0:1;
                  vuint32_t:1;
                vuint32_t MDIS:1;
                vuint32_t DIS_TXF:1;
                vuint32_t DIS_RXF:1;
                vuint32_t CLR_TXF:1;
                vuint32_t CLR_RXF:1;
                vuint32_t SMPL_PT:2;
                  vuint32_t:7;
                vuint32_t HALT:1;
            } B;
        } MCR;                          /* Module Configuration Register */

        uint32_t dspi_reserved1;

        union {
            vuint32_t R;
            struct {
                vuint32_t SPI_TCNT:16;
                  vuint32_t:16;
            } B;
        } TCR;                          /* Transfer Count Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t DBR:1;
                vuint32_t FMSZ:4;
                vuint32_t CPOL:1;
                vuint32_t CPHA:1;
                vuint32_t LSBFE:1;
                vuint32_t PCSSCK:2;
                vuint32_t PASC:2;
                vuint32_t PDT:2;
                vuint32_t PBR:2;
                vuint32_t CSSCK:4;
                vuint32_t ASC:4;
                vuint32_t DT:4;
                vuint32_t BR:4;
            } B;
        } CTAR[8];                      /* Clock and Transfer Attributes Registers */

        union {
            vuint32_t R;
            struct {
                vuint32_t TCF:1;
                vuint32_t TXRXS:1;
                  vuint32_t:1;
                vuint32_t EOQF:1;
                vuint32_t TFUF:1;
                  vuint32_t:1;
                vuint32_t TFFF:1;
                  vuint32_t:5;
                vuint32_t RFOF:1;
                  vuint32_t:1;
                vuint32_t RFDF:1;
                  vuint32_t:1;
                vuint32_t TXCTR:4;
                vuint32_t TXNXTPTR:4;
                vuint32_t RXCTR:4;
                vuint32_t POPNXTPTR:4;
            } B;
        } SR;                           /* Status Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t TCF_RE:1;
                  vuint32_t:2;
                vuint32_t EOQF_RE:1;
                vuint32_t TFUF_RE:1;
                  vuint32_t:1;
                vuint32_t TFFF_RE:1;
                vuint32_t TFFF_DIRS:1;
                  vuint32_t:4;
                vuint32_t RFOF_RE:1;
                  vuint32_t:1;
                vuint32_t RFDF_RE:1;
                vuint32_t RFDF_DIRS:1;
                  vuint32_t:16;
            } B;
        } RSER;                         /* DMA/Interrupt Request Select and Enable Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t CONT:1;
                vuint32_t CTAS:3;
                vuint32_t EOQ:1;
                vuint32_t CTCNT:1;
                  vuint32_t:7;
                vuint32_t PCS2:1;
                vuint32_t PCS1:1;
                vuint32_t PCS0:1;
                vuint32_t TXDATA:16;
            } B;
        } PUSHR;                        /* PUSH TX FIFO Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t RXDATA:16;
            } B;
        } POPR;                         /* POP RX FIFO Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t TXCMD:16;
                vuint32_t TXDATA:16;
            } B;
        } TXFR[5];                      /* Transmit FIFO Registers */

        vuint32_t DSPI_reserved_txf[11];

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t RXDATA:16;
            } B;
        } RXFR[5];                      /* Transmit FIFO Registers */

        vuint32_t DSPI_reserved_rxf[11];

    };                                  /* end of DSPI_tag */
/****************************************************************************/
/*                             MODULE : QUADSPI v3                          */
/****************************************************************************/
    struct QUADSPI_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t SCLKCFG:8;    /* Reserved for future use */
                  vuint32_t:4;
                vuint32_t ISD3FB:1;     /* Reserved for future use */
                vuint32_t ISD2FB:1;     /* Reserved for future use */
                vuint32_t ISD3FA:1;     /* Reserved for future use */
                vuint32_t ISD2FA:1;     /* Reserved for future use */
                vuint32_t DOZE:1;
                vuint32_t MDIS:1;
                  vuint32_t:2;
                vuint32_t CLR_TXF:1;
                vuint32_t CLR_RXF:1;
                  vuint32_t:3;
                vuint32_t VMID:4;
                  vuint32_t:2;
                vuint32_t EXT_ADD:1;    /* Extended address support (v3) */
            } B;
        } MCR;                          /* Module Configuration Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:26;
                vuint32_t NDC:6;    /* Number of dummy cycles (v3) */
            } B;
        } LCR;                          /* Latency Configuration Register */

        uint32_t quadspi_reserved1[62]; /* {0x0100-0x0008}/0x4 = 0x3E */

        union {
            vuint32_t R;
            struct {
                vuint32_t SFADR:32;
            } B;
        } SFAR;                         /* Serial Flash Address Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t ICO:24;
                vuint32_t IC:8;
            } B;
        } ICR;                          /* Instruction Code Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:25;
                vuint32_t FSDLY:1;
                vuint32_t FSPHS:1;
                  vuint32_t:2;
                vuint32_t HSDLY:1;
                vuint32_t HSPHS:1;
                vuint32_t HSENA:1;
            } B;
        } SMPR;                         /* Sampling Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t RDCTR:16;
                  vuint32_t:2;
                vuint32_t RDBFL:6;
                  vuint32_t:8;
            } B;
        } RBSR;                         /* RX Buffer Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:23;
                vuint32_t RXBRD:1;
                  vuint32_t:3;
                vuint32_t WMRK:5;
            } B;
        } RBCT;                         /* RX Buffer Control Register 0 - 14 */

        uint32_t quadspi_reserved2[15]; /* {0x0150-0x0114}/0x4 = 0x0F */

        union {
            vuint32_t R;
            struct {
                vuint32_t TRCTR:16;
                  vuint32_t:3;
                vuint32_t TRBFL:5;
                  vuint32_t:8;
            } B;
        } TBSR;                         /* TX Buffer Status Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t TXDATA:32;
            } B;
        } TBDR;                         /* TX Buffer Data Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t ARMB:8;
                vuint32_t ARSZ:5;
                  vuint32_t:3;
                vuint32_t ARIC:8;
            } B;
        } ACR;                          /* AMBA Control Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:4;
                vuint32_t TXFULL:1;
                  vuint32_t:2;
                vuint32_t TXNE:1;
                vuint32_t RXDMA:1;
                  vuint32_t:3;
                vuint32_t RXFULL:1;
                  vuint32_t:2;
                vuint32_t RXNE:1;
                  vuint32_t:4;
                vuint32_t AHBFULL:1;
                  vuint32_t:2;
                vuint32_t AHBNE:1;
                  vuint32_t:1;
                vuint32_t AHBTRN:1;
                vuint32_t AHBGNT:1;
                vuint32_t CNTMDFB:1;
                vuint32_t CNTMDFA:1;
                vuint32_t AHB_ACC:1;
                vuint32_t IP_ACC:1;
                vuint32_t BUSY:1;
            } B;
        } SFMSR;                        /* Serial Flash Mode Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:4;
                vuint32_t TBFF:1;
                vuint32_t TBUF:1;
                  vuint32_t:8;
                vuint32_t RBOF:1;
                vuint32_t RBDF:1;
                  vuint32_t:1;
                vuint32_t ABCEF:1;
                vuint32_t ABMEF:1;
                vuint32_t ABOF:1;
                vuint32_t IUEF:1;
                vuint32_t ICEF:1;
                vuint32_t IMEF:1;
                  vuint32_t:1;
                vuint32_t IPAEF:1;
                vuint32_t IPIEF:1;
                  vuint32_t:1;
                vuint32_t IPGEF:1;
                  vuint32_t:3;
                vuint32_t TFF:1;
            } B;
        } SFMFR;                        /* Serial Flash Mode Flag Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:4;
                vuint32_t TBFIE:1;
                vuint32_t TBUIE:1;
                  vuint32_t:4;
                vuint32_t RBDDE:1;
                  vuint32_t:3;
                vuint32_t RBOIE:1;
                vuint32_t RBDIE:1;
                  vuint32_t:1;
                vuint32_t ABCEIE:1;
                vuint32_t ABMEIE:1;
                vuint32_t ABOIE:1;
                vuint32_t IUEIE:1;
                vuint32_t ICEIE:1;
                vuint32_t IMEIE:1;
                  vuint32_t:1;
                vuint32_t IPAEIE:1;
                vuint32_t IPIEIE:1;
                  vuint32_t:1;
                vuint32_t IPGEIE:1;
                  vuint32_t:3;
                vuint32_t TFIE:1;
            } B;
        } SFMRSER;                      /* SFM Interrupt and DMA Request Select and Enable Register */

        uint32_t quadspi_reserved3[38]; /* {0x0200-0x0168}/0x4 = 0x26 */

        union {
            vuint32_t R;
            struct {
                vuint32_t RXDATA:32;
            } B;
        } RBDR[32];                     /* RX Buffer Data Registers */        

    };                                  /* end of QUADSPI_tag */
/****************************************************************************/
/*                             MODULE : FlexCAN                             */
/****************************************************************************/
#include "ip_flexcan.h"
/****************************************************************************/
/*                             MODULE : DMAMUX                              */
/****************************************************************************/
    struct DMAMUX_tag {
        union {
            vuint8_t R;
            struct {
                vuint8_t ENBL:1;
                vuint8_t TRIG:1;
                vuint8_t SOURCE:6;
            } B;
        } CHCONFIG[16];                 /* DMA Channel Configuration Register */

    };                                  /* end of DMAMUX_tag */

/****************************************************************************/
/*                             MODULE : CFLASH                              */
/****************************************************************************/
    struct CFLASH_tag {
        union {                         /* Module Configuration Register */
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t SIZE:3;
                  vuint32_t:1;
                vuint32_t LAS:3;
                  vuint32_t:3;
                vuint32_t MAS:1;
                vuint32_t EER:1;
                vuint32_t RWE:1;
                vuint32_t SBC:1;
                  vuint32_t:1;
                vuint32_t PEAS:1;
                vuint32_t DONE:1;
                vuint32_t PEG:1;
                  vuint32_t:4;
                vuint32_t PGM:1;
                vuint32_t PSUS:1;
                vuint32_t ERS:1;
                vuint32_t ESUS:1;
                vuint32_t EHV:1;
            } B;
        } MCR;

        union {                         /* LML Register */
            vuint32_t R;
            struct {
                vuint32_t LME:1;
                  vuint32_t:10;
                vuint32_t SLOCK:1;
                  vuint32_t:2;
                vuint32_t MLOCK:2;
                  vuint32_t:6;
                vuint32_t LLOCK:10;
            } B;
        } LML;

        union {                         /* HBL Register */
            vuint32_t R;
            struct {
                vuint32_t HBE:1;
                  vuint32_t:25;
                vuint32_t HLOCK:6;
            } B;
        } HBL;

        union {                         /* SLML Register */
            vuint32_t R;
            struct {
                vuint32_t SLE:1;
                  vuint32_t:10;
                vuint32_t SSLOCK:1;
                  vuint32_t:2;
                vuint32_t SMLOCK:2;
                  vuint32_t:6;
                vuint32_t SLK:10;
            } B;
        } SLL;

        union {                         /* LMS Register */
            vuint32_t R;
            struct {
                  vuint32_t:14;
                vuint32_t MSEL:2;
                  vuint32_t:6;
                vuint32_t LSEL:10;
            } B;
        } LMS;

        union {                         /* High Address Space Block Select Register */
            vuint32_t R;
            struct {
                  vuint32_t:26;
                vuint32_t HSEL:6;
            } B;
        } HBS;

        union {                         /* Address Register */
            vuint32_t R;
            struct {
                vuint32_t SAD:1;
                  vuint32_t:10;
                vuint32_t ADD:18;
                  vuint32_t:3;
            } B;
        } ADR;

        union {                         /* CFLASH Configuration Register 0 */
            vuint32_t R;
            struct {
                vuint32_t LBCFG:4;      
                vuint32_t ARB:1;
                vuint32_t PRI:1;
                  vuint32_t :3;
                vuint32_t M6PFE:1; 
                vuint32_t M5PFE:1;             
                vuint32_t M4PFE:1; 
                vuint32_t M3PFE:1; 
                vuint32_t M2PFE:1;
                vuint32_t M1PFE:1;
                vuint32_t M0PFE:1;
                vuint32_t APC:3;
                vuint32_t WWSC:2;
                vuint32_t RWSC:3;
                  vuint32_t :1; 
                vuint32_t DPFEN:1;
                  vuint32_t :1; 
                vuint32_t IPFEN:1; 	
                  vuint32_t :1;
                vuint32_t PFLIM:2;
                vuint32_t BFEN:1;
            } B;
        } PFCR0;

        union {                         /* CFLASH Configuration Register 1 */
            vuint32_t R;
            struct {
                vuint32_t LBCFG:4;      
                  vuint32_t :5; 
                vuint32_t M6PFE:1; 
                vuint32_t M5PFE:1;             
                vuint32_t M4PFE:1; 
                vuint32_t M3PFE:1; 
                vuint32_t M2PFE:1;
                vuint32_t M1PFE:1;
                vuint32_t M0PFE:1;
                vuint32_t APC:3;
                vuint32_t WWSC:2;
                vuint32_t RWSC:3;
                  vuint32_t :1; 
                vuint32_t DPFEN:1;
                  vuint32_t :1; 
                vuint32_t IPFEN:1; 	
                  vuint32_t :1;
                vuint32_t PFLIM:2;
                vuint32_t BFEN:1;
            } B;
        } PFCR1;

        union {                         /* CFLASH Access Protection Register */
            vuint32_t R;
            struct {
                  vuint32_t :2; 
                vuint32_t M6AP:2; 
                vuint32_t M5AP:2;
                vuint32_t M4AP:2;
                vuint32_t M3AP:2;
                vuint32_t M2AP:2;
                vuint32_t M1AP:2;
                vuint32_t M0AP:2;             
                vuint32_t SHSACC:8;
                vuint32_t SHDACC:8;
            } B;
        } PFAPR;

        union {                         /* cflash Supervisor Access Control Register */
            vuint32_t R;
            struct {
                  vuint32_t :1;
                vuint32_t SACC:31; 
            } B;
        } PFSACC;

        int32_t CFLASH_reserved0[4];    /* {0x003C-0x002C}/0x4 = 0x04 */

        union {                         /* User Test Register 0 */
            vuint32_t R;
            struct {
                vuint32_t UTE:1;
                  vuint32_t:7;
                vuint32_t DSI:8;
                  vuint32_t:10;
                vuint32_t MRE:1;
                vuint32_t MRV:1;
                vuint32_t EIE:1;
                vuint32_t AIS:1;
                vuint32_t AIE:1;
                vuint32_t AID:1;
            } B;
        } UT0;

        union {                         /* User Test Register 1 */
            vuint32_t R;
            struct {
                vuint32_t DAI:32;
            } B;
        } UT1;

        union {                         /* User Test Register 2 */
            vuint32_t R;
            struct {
                vuint32_t DAI:32;
            } B;
        } UT2;

        union {                         /* User Multiple Input Signature Register 0-4 */
            vuint32_t R;
            struct {
                vuint32_t MISR:32;
            } B;
        } UM[5];

    };                                  /* end of CFLASH_tag */
/****************************************************************************/
/*                             MODULE : SGM                                 */
/****************************************************************************/
    typedef struct {

        union {
            vuint32_t R;
            struct {
                vuint32_t CLKS:2;
                  vuint32_t:11;
                vuint32_t PRSR:3;
                vuint32_t PRSM:16;
            } B;
        } CLK;                          /* CH[X].CLK Clock Configuration Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t DDSF:16;
                  vuint32_t:16;
            } B;
        } DDS;                          /* CH[X].DDS DDS Configuration Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t ATKT:8;
                vuint32_t ATKSL:8;
                vuint32_t ATKSC:16;
            } B;
        } ECRA;                         /* CH[X].ECRA Envelop Configuration Register of Attack Phase */

        union {
            vuint32_t R;
            struct {
                vuint32_t RELT:8;
                vuint32_t RELSL:8;
                vuint32_t RELSC:16;
            } B;
        } ECRR;                         /* CH[X].ECRR Envelop Configuration Register of Release Phase */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t SUST:24;
            } B;
        } ECRS;                         /* CH[X].ECRS Envelop Configuration Register of sustain Timing */
        
        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t NOPT:24;
            } B;
        } NT;                           /* CH[X].NT Inter-Note Nop Phase Timing Register*/

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t TPC:16;
            } B;
        } TPC;                          /* CH[X].TPC Target Note Pulse Count Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t PLAYBT:24;
            } B;
        } PTC;                          /* CH[X].PTC PlayBack Timing Configuration Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t DEADT:24;
            } B;
        } DTC;                          /* CH[X].DTC Dead Time Configuration Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:22;
                vuint32_t RPTN:10;
            } B;
        } RNC;                          /* CH[X].DTC Dead Time Configuration Register */

    } SGM_CHANNEL_tag;                  /* end of SGM_CHANNEL_tag */

    struct SGM_tag{
        union{
            vuint32_t R;
            struct{
                vuint32_t SOGCH3:1;
                vuint32_t SOGCH2:1;
                vuint32_t SOGCH1:1;
                vuint32_t SOGCH0:1;
                  vuint32_t:4;
                vuint32_t MDIS:1;
                  vuint32_t:7;
                vuint32_t MODCH3:1;
                vuint32_t MODCH2:1;
                vuint32_t MODCH1:1;
                vuint32_t MODCH0:1;
                  vuint32_t:4;
                vuint32_t TOE:1;
                vuint32_t WAVCLKS:1;
                  vuint32_t:3;
                vuint32_t PWME:1;
                vuint32_t PWMCHS:1;
                vuint32_t OS:1;
            } B;
        }CTL;                           /* Control Register */

        union{
            vuint32_t R;
            struct{
                vuint32_t ATKCH3:1;
                vuint32_t ATKCH2:1;
                vuint32_t ATKCH1:1;
                vuint32_t ATKCH0:1;
                vuint32_t RELFCH3:1;
                vuint32_t RELFCH2:1;
                vuint32_t RELFCH1:1;
                vuint32_t RELFCH0:1;
                vuint32_t NOPCH3:1;
                vuint32_t NOPCH2:1;
                vuint32_t NOPCH1:1;
                vuint32_t NOPCH0:1;
                vuint32_t TPCECH3:1;
                vuint32_t TPCECH2:1;
                vuint32_t TPCECH1:1;
                vuint32_t TPCECH0:1;
                vuint32_t RPTECH3:1;
                vuint32_t RPTECH2:1;
                vuint32_t RPTECH1:1;
                vuint32_t RPTECH0:1;
                  vuint32_t:4;
                vuint32_t SFCH3:2;
                vuint32_t SFCH2:2;
                vuint32_t SFCH1:2;
                vuint32_t SFCH0:2;
            } B;
        }CFG;                           /* Configuration Register */

        union{
            vuint32_t R;
            struct{
                vuint32_t CLKS:2;
                  vuint32_t:11;
                vuint32_t PRSR:3;
                vuint32_t PRSM:16;
            } B;
        }CLKRSP;                        /* Clock Configuration Register for Resampler */
        
        SGM_CHANNEL_tag CH3;

        SGM_CHANNEL_tag CH2;

        SGM_CHANNEL_tag CH1;

        SGM_CHANNEL_tag CH0;

        union{
            vuint32_t R;
            struct{
                vuint32_t VOLCH3:8;
                vuint32_t VOLCH2:8;
                vuint32_t VOLCH1:8;
                vuint32_t VOLCH0:8;
            } B;
        }VCRWAV;                        /* Volume Control Register for Wave-Mode Register */
        
        union{
            vuint32_t R;
            struct{
                vuint32_t TIMEOUT:32;
            } B;
        }TOCR;                          /* TimeOut Count Register */
        
        union{
            vuint32_t R;
            struct{
                  vuint32_t:12;
                vuint32_t CHSL:4;
                  vuint32_t:12;
                vuint32_t CHSR:4;
            } B;
        }MIXCR;                         /* Mixer Configuration Register */
        
        union{
            vuint32_t R;
            struct{
                vuint32_t CLKS:2;
                  vuint32_t:11;
                vuint32_t PRSR:3;
                vuint32_t PRSM:16;
            } B;
        }CLKPWM;                        /* Clock Configuration Register for PWM */
        
        union{
            vuint32_t R;
            struct{
                vuint32_t PWMF:16;
                vuint32_t TONF:16;
            } B;
        }PWMCR;                         /* PWM Configuration Register */
        
        union{
            vuint32_t R;
            struct{
                vuint32_t FIFOCH3:16;
                vuint32_t FIFOCH2:16;
            } B;
        }DFIFO1;                        /* Data FIFO Register 1 */
        
        union{
            vuint32_t R;
            struct{
                vuint32_t FIFOCH1:16;
                vuint32_t FIFOCH0:16;
            } B;
        }DFIFO2;                        /* Data FIFO Register 2 */
        
        union{
            vuint32_t R;
            struct{
                vuint32_t WMCH3:8;
                vuint32_t WMCH2:8;
                vuint32_t WMCH1:8;
                vuint32_t WMCH0:8;
            } B;
        }FIFOWM;                        /* FIFO WaterMark Register */
        
        union{
            vuint32_t R;
            struct{
                vuint32_t FRPCH3:8;
                vuint32_t FRPCH2:8;
                vuint32_t FRPCH1:8;
                vuint32_t FRPCH0:8;
            } B;
        }FIFORP;                        /* FIFO Read Pointer Register */
        
        union{
            vuint32_t R;
            struct{
                vuint32_t FWPCH3:8;
                vuint32_t FWPCH2:8;
                vuint32_t FWPCH1:8;
                vuint32_t FWPCH0:8;
            } B;
        }FIFOWP;                        /* FIFO Write Pointer Register */
        
        union{
            vuint32_t R;
            struct{
                  vuint32_t:4;
                vuint32_t FLSCH3:1;
                vuint32_t STATCH3:3;
                  vuint32_t:4;
                vuint32_t FLSCH2:1;
                vuint32_t STATCH2:3;
                  vuint32_t:4;
                vuint32_t FLSCH1:1;
                vuint32_t STATCH1:3;
                  vuint32_t:4;
                vuint32_t FLSCH0:1;
                vuint32_t STATCH0:3;
            } B;
        }ST;                            /* Interrupt Control Register for FIFO and DMA */
        
        union{
            vuint32_t R;
            struct{
                vuint32_t FLDECH3:1;
                vuint32_t FLDECH2:1;
                vuint32_t FLDECH1:1;
                vuint32_t FLDECH0:1;
                  vuint32_t:4;
                vuint32_t FLIECH3:1;
                vuint32_t FLIECH2:1;
                vuint32_t FLIECH1:1;
                vuint32_t FLIECH0:1;
                  vuint32_t:4;
                vuint32_t FFIECH3:1;
                vuint32_t FFIECH2:1;
                vuint32_t FFIECH1:1;
                vuint32_t FFIECH0:1;
                vuint32_t FEIECH3:1;
                vuint32_t FEIECH2:1;
                vuint32_t FEIECH1:1;
                vuint32_t FEIECH0:1;
                vuint32_t FOIECH3:1;
                vuint32_t FOIECH2:1;
                vuint32_t FOIECH1:1;
                vuint32_t FOIECH0:1;
                vuint32_t FUIECH3:1;
                vuint32_t FUIECH2:1;
                vuint32_t FUIECH1:1;
                vuint32_t FUIECH0:1;
            } B;
        }ICFD;                          /* Interrupt Control Register for FIFO and DMA */
        
        union{
            vuint32_t R;
            struct{
                vuint32_t TOIE:1;
                  vuint32_t:7;
                vuint32_t PDIECH3:1;
                vuint32_t PDIECH2:1;
                vuint32_t PDIECH1:1;
                vuint32_t PDIECH0:1;
                vuint32_t RDIECH3:1;
                vuint32_t RDIECH2:1;
                vuint32_t RDIECH1:1;
                vuint32_t RDIECH0:1;
                vuint32_t EORIECH3:1;
                vuint32_t EORIECH2:1;
                vuint32_t EORIECH1:1;
                vuint32_t EORIECH0:1;
                vuint32_t EOAIECH3:1;
                vuint32_t EOAIECH2:1;
                vuint32_t EOAIECH1:1;
                vuint32_t EOAIECH0:1;
                vuint32_t EONIECH3:1;
                vuint32_t EONIECH2:1;
                vuint32_t EONIECH1:1;
                vuint32_t EONIECH0:1;
                vuint32_t PCIECH3:1;
                vuint32_t PCIECH2:1;
                vuint32_t PCIECH1:1;
                vuint32_t PCIECH0:1;
            } B;
        }IC;                            /* Interrupt Control Register */
        
        union{
            vuint32_t R;
            struct{
                  vuint32_t:8;
                vuint32_t FLFCH3:1;
                vuint32_t FLFCH2:1;
                vuint32_t FLFCH1:1;
                vuint32_t FLFCH0:1;
                  vuint32_t:4;
                vuint32_t FFFCH3:1;
                vuint32_t FFFCH2:1;
                vuint32_t FFFCH1:1;
                vuint32_t FFFCH0:1;
                vuint32_t FEFCH3:1;
                vuint32_t FEFCH2:1;
                vuint32_t FEFCH1:1;
                vuint32_t FEFCH0:1;
                vuint32_t FOFCH3:1;
                vuint32_t FOFCH2:1;
                vuint32_t FOFCH1:1;
                vuint32_t FOFCH0:1;
                vuint32_t FUFCH3:1;
                vuint32_t FUFCH2:1;
                vuint32_t FUFCH1:1;
                vuint32_t FUFCH0:1;
            } B;
        }ISFD;                          /* Interrupt Status Register for FIFO and DMA */
        
        union{
            vuint32_t R;
            struct{
                vuint32_t TOF:1;
                  vuint32_t:7;
                vuint32_t PDFCH3:1;
                vuint32_t PDFCH2:1;
                vuint32_t PDFCH1:1;
                vuint32_t PDFCH0:1;
                vuint32_t RDFCH3:1;
                vuint32_t RDFCH2:1;
                vuint32_t RDFCH1:1;
                vuint32_t RDFCH0:1;
                vuint32_t EORFCH3:1;
                vuint32_t EORFCH2:1;
                vuint32_t EORFCH1:1;
                vuint32_t EORFCH0:1;
                vuint32_t EOAFCH3:1;
                vuint32_t EOAFCH2:1;
                vuint32_t EOAFCH1:1;
                vuint32_t EOAFCH0:1;
                vuint32_t EONFCH3:1;
                vuint32_t EONFCH2:1;
                vuint32_t EONFCH1:1;
                vuint32_t EONFCH0:1;
                vuint32_t PCFCH3:1;
                vuint32_t PCFCH2:1;
                vuint32_t PCFCH1:1;
                vuint32_t PCFCH0:1;
            } B;
        }IS;                            /* Interrupt Status Register */

        union{
            vuint32_t R;
            struct{
                  vuint32_t:27;
                vuint32_t SRST:1;
                  vuint32_t:3;
                vuint32_t IEN:1;
            } B;
        }I2SEN;                         /* I2S Enable Register */

        union{
            vuint32_t R;
            struct{
                  vuint32_t:16;
                vuint32_t FIFOTH:2;
                  vuint32_t:4;
                vuint32_t ACEN:1;
                vuint32_t ACSEL:1;
                vuint32_t CHSEL:1;
                  vuint32_t:1;
                vuint32_t PM:2;
                  vuint32_t:2;
                vuint32_t PSYNC:1;
                vuint32_t POL:1;
            } B;
        }I2SCTL;                        /* I2S Control Register */

        union{
            vuint32_t R;
            struct{
                  vuint32_t:11;
                vuint32_t FSL:5;
                  vuint32_t:3;
                vuint32_t MSBF:2;
                  vuint32_t:1;
                vuint32_t BSO:2;
                  vuint32_t:2;
                vuint32_t ODF:2;
                  vuint32_t:3;
                vuint32_t IDF:1;
            } B;
        }I2SDFC;                        /* I2S Output Data Format Control Register */

        union{
            vuint32_t R;
            struct{
                vuint32_t ACPSCLR:16;
                vuint32_t I2SPSCLR:16;
            } B;
        }I2SPRS;                         /* I2S Clock Prescale Register */
        
        union{
            vuint32_t R;
            struct{
                vuint32_t TSFEN:1;
                  vuint32_t:5;
                vuint32_t FOFE:1;
                vuint32_t FUFE:1;
                  vuint32_t:5;
                vuint32_t CPLEN:1;
                  vuint32_t:18;
            } B;
        }I2SINTC;                       /* I2S Interrupt Control Register */

        union{
            vuint32_t R;
            struct{
                vuint32_t TSFE:1;
                  vuint32_t:5;
                vuint32_t FOF:1;
                vuint32_t FUF:1;
                  vuint32_t:5;
                vuint32_t CPL:1;
                  vuint32_t:10;
                vuint32_t FIFOST:4;
                  vuint32_t:3;
                vuint32_t BSY:1;
            } B;
        }I2SST;                         /* SI2S Status Register */
    };                                  /* end of SGM_tag */

/****************************************************************************/
/*                             MODULE : RLE                                 */
/****************************************************************************/
    struct RLE_tag {

        union {
            vuint32_t R;
            struct {
                vuint32_t RX_FIFO_THRESHOLD:8;
                vuint32_t TX_FIFO_THRESHOLD:8;
                  vuint32_t:13;
                vuint32_t TXFFEN:1;
                  vuint32_t:1;
                vuint32_t MDIS:1;
            } B;
        } MCR;                          /* Module Configuration Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:30;
                vuint32_t WIDTH:2;
            } B;
        } ICR;                          /* Image Configuration Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t SIZE:16;
            } B;
        } CISR;                         /* Compressed Image Size Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t X:16;
                vuint32_t Y:16;
            } B;
        } DICR;                         /* Decompressed Image Co-ordinates Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t RXFREE:8;
                vuint32_t TXFILL:8;
            } B;
        } SR;                           /* Compressed Image Size Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:24;
                vuint32_t RXDIF:1;
                vuint32_t TXDIF:1;
                vuint32_t RXUIF:1;
                vuint32_t TXUIF:1;
                vuint32_t RXFIF:1;
                vuint32_t TXFIF:1; 
                vuint32_t RXEIF:1;
                vuint32_t TXEIF:1;            
            } B;
        } ISR;                          /* Interrupt Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:24;
                vuint32_t RXDIE:1;
                vuint32_t TXDIE:1;
                vuint32_t RXUIE:1;
                vuint32_t TXUIE:1;
                vuint32_t RXFIE:1;
                vuint32_t TXFIE:1; 
                vuint32_t RXEIE:1;
                vuint32_t TXEIE:1;            
            } B;
        } RIER;                         /* Interrupt Request Enable Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t X:16;
                vuint32_t Y:16;
            } B;
        } SPCR;                         /* Start Pixel Co-ordinate Register of Image */

        union {
            vuint32_t R;
            struct {
                vuint32_t X:16;
                vuint32_t Y:16;
            } B;
        } EPCR;                         /* End Pixel Co-ordinate Register of Image */

    };                                  /* end of RLE_tag */

/****************************************************************************/
/*                             MODULE : DCULITE                             */
/****************************************************************************/
    struct DCULITE_FG_tag {

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t COLOR:24;
            } B;
        } F;                            /* Transparency layer foreground color */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t COLOR:24;
            } B;
        } B;                            /* Transparency layer foreground color */
    };
    
    struct DCULITE_LAYER_tag {

        union {
            vuint32_t R;
            struct {
                vuint32_t:5;
                vuint32_t HEIGHT:11;
                  vuint32_t:5;
                vuint32_t WIDTH:11;
            } B;
        } CTRLDESCL1;                   /* LAYER[X].CTRLDESCL1 */

        union {
            vuint32_t R;
            struct {
                vuint32_t:4;
                vuint32_t POSY:12;
                  vuint32_t:4;
                vuint32_t POSX:12;
            } B;
        } CTRLDESCL2;                   /* LAYER[X].CTRLDESCL2 */

        union {
            vuint32_t R;
            struct {
                vuint32_t ADDR:32;
            } B;
        } CTRLDESCL3;                   /* LAYER[X].CTRLDESCL3 */

        union {
            vuint32_t R;
            struct {
                vuint32_t EN:1;
                vuint32_t TILE_EN:1;
                  vuint32_t:1;
                vuint32_t SAFETY_EN:1;
                vuint32_t TRANS:8;
                vuint32_t BPP:4;
                vuint32_t RLE_EN:1;
                  vuint32_t:2;
                vuint32_t LUOFFS:9;
                  vuint32_t:1;
                vuint32_t BB:1;
                vuint32_t AB:2;
            } B;
        } CTRLDESCL4;                   /* LAYER[X].CTRLDESCL4 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t CKMAX_R:8;
                vuint32_t CKMAX_G:8;
                vuint32_t CKMAX_B:8;
            } B;
        } CTRLDESCL5;                   /* LAYER[X].CTRLDESCL5 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t CKMIN_R:8;
                vuint32_t CKMIN_G:8;
                vuint32_t CKMIN_B:8;
            } B;
        } CTRLDESCL6;                   /* LAYER[X].CTRLDESCL6 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t TILE_VER_SIZE:11;
                  vuint32_t:9;
                vuint32_t TILE_HOR_SIZE:7;
            } B;
        } CTRLDESCL7;                   /* LAYER[X].CTRLDESCL7 */

    };                                  /* end of DCU_LAYER_tag */

    struct DCULITE_tag {

        /* DCU.LAYER<[x]>.CTRLDESCL<y>.R  {x = 0-15, y = 1-7} */
        /* eg DCU.LAYER[0].CTRLDESCL1.R        = 0;           */
        /*      DCU.LAYER[0].CTRLDESCL1.B.HEIGHT = 0;           */
        struct DCULITE_LAYER_tag LAYER[4];

        vuint32_t DCULITE_reserved1[0x54]; /* 0x1C0- 0x070 = 84 words*/

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t HEIGHT:11;
                  vuint32_t:5;
                vuint32_t WIDTH:11;
            } B;
        } CTRLDESCCURSOR1;              /* Cursor Control Descriptor 1 Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t POSY:11;
                  vuint32_t:5;
                vuint32_t POSX:11;
            } B;
        } CTRLDESCCURSOR2;              /* Cursor Control Descriptor 2 Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t CUR_EN:1;
                  vuint32_t:7;
                vuint32_t CURSOR_DEFAULT_COLOR:24;
            } B;
        } CTRLDESCCURSOR3;              /* Cursor Control Descriptor 3 Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t HWC_BLINK_OFF:8;
                  vuint32_t:7;
                vuint32_t EN_BLINK:1;
                vuint32_t HWC_BLINK_ON:8;
            } B;
        } CTRLDESCCURSOR4;              /* Cursor Control Descriptor 4 Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t DCU_SW_RESET:1;
                vuint32_t DITHER_EN:1;        
                vuint32_t ADDB:2;
                vuint32_t ADDG:2;
                vuint32_t ADDR:2;
                vuint32_t DDR_MODE:1;
                  vuint32_t:3;
                vuint32_t PDI_SYNC_LOCK:4;
                vuint32_t PDI_INTERPOL_EN:1;        
                vuint32_t RASTER_EN:1;        
                vuint32_t PDI_EN:1;
                vuint32_t PDI_BYTE_REV:1;
                vuint32_t PDI_DE_MODE:1;
                vuint32_t PDI_NARROW_MODE:1;
                vuint32_t PDI_MODE:2;
                vuint32_t PDI_SLAVE_MODE:1;
                vuint32_t TAG_EN:1;
                vuint32_t SIG_EN:1;
                vuint32_t PDI_SYNC:1;
                  vuint32_t:1;
                vuint32_t EN_GAMMA:1;
                vuint32_t DCU_MODE:2;
            } B;
        } DCU_MODE;                     /* Mode Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t BGND_R:8;
                vuint32_t BGND_G:8;
                vuint32_t BGND_B:8;
            } B;
        } BGND;                         /* Background Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t DELTA_Y:11;
                  vuint32_t:9;
                vuint32_t DELTA_X:7;
            } B;
        } DISP_SIZE;                    /* Display Size Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t BP_H:9;
                  vuint32_t:2;
                vuint32_t PW_H:9;
                  vuint32_t:2;
                vuint32_t FP_H:9;
            } B;
        } HSYN_PARA;                    /* Horizontal Synchronisation Parameter Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t BP_V:9;
                  vuint32_t:2;
                vuint32_t PW_V:9;
                  vuint32_t:2;
                vuint32_t FP_V:9;
            } B;
        } VSYN_PARA;                    /* Vertical Synchronisation Parameter Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:21;
                vuint32_t INV_PDI_DE:1;
                vuint32_t INV_PDI_HS:1;
                vuint32_t INV_PDI_VS:1;
                vuint32_t INV_PDI_CLK:1;
                vuint32_t INV_PXCK:1;
                vuint32_t NEG:1;
                vuint32_t BP_VS:1;
                vuint32_t BP_HS:1;
                vuint32_t INV_CS:1;
                vuint32_t INV_VS:1;
                vuint32_t INV_HS:1;
            } B;
        } SYN_POL;                      /* Synchronisation Polarity Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t LS_BF_VS:11;
                vuint32_t OUT_BUF_HIGH:8;
                vuint32_t OUT_BUF_LOW:8;
            } B;
        } THRESHOLD;                    /* Threshold Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:17;
                vuint32_t DMA_TRANS_FINISH:1;
                  vuint32_t:2;
                vuint32_t IPM_ERROR:1;
                vuint32_t PROG_END:1;
                vuint32_t P2_FIFO_HI_FLAG:1;
                vuint32_t P2_FIFO_LO_FLAG:1;
                vuint32_t P1_FIFO_HI_FLAG:1;
                vuint32_t P1_FIFO_LO_FLAG:1;
                vuint32_t CRC_OVERFLOW:1;
                vuint32_t CRC_READY:1;
                vuint32_t VS_BLANK:1;
                vuint32_t LS_BF_VS:1;
                vuint32_t UNDRUN:1;
                vuint32_t VSYNC:1;
            } B;
        } INT_STATUS;                   /* Interrupt Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:17;
                vuint32_t M_DMA_TRANSFINISH:1;
                  vuint32_t:2;
                vuint32_t M_IPM_ERROR:1;
                vuint32_t M_PROG_END:1;
                vuint32_t M_P2_FIFO_HI_FLAG:1;
                vuint32_t M_P2_FIFO_LO_FLAG:1;
                vuint32_t M_P1_FIFO_HI_FLAG:1;
                vuint32_t M_P1_FIFO_LO_FLAG:1;
                vuint32_t M_CRC_OVERFLOW:1;
                vuint32_t M_CRC_READY:1;
                vuint32_t M_VS_BLANK:1;
                vuint32_t M_LS_BF_VS:1;
                vuint32_t M_UNDRUN:1;
                vuint32_t M_VSYNC:1;
            } B;
        } INT_MASK;                     /* Interrupt Mask Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t COLBAR_R:8;
                vuint32_t COLBAR_G:8;
                vuint32_t COLBAR_B:8;
            } B;
        } COLBAR[8];                    /* Color Bar 1-8 Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:24;
                vuint32_t DIV_RATIO:8;
            } B;
        } DIV_RATIO;                    /* Clock Divider Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t SIG_VER_SIZE:11;
                  vuint32_t:5;
                vuint32_t SIG_HOR_SIZE:11;
            } B;
        } SIGN_CALC_1;                  /* CRC size configuration */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t SIG_VER_POS:11;
                  vuint32_t:5;
                vuint32_t SIG_HOR_POS:11;
            } B;
        } SIGN_CALC_2;                  /* CRC position configuration */

        union {
            vuint32_t R;
            struct {
                vuint32_t CRC_VAL:32;
            } B;
        } CRC_VAL;                      /* CRC Result register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:22;
                vuint32_t PDI_BLANKING_ERR:1;
                vuint32_t PDI_ECC_ERR2:1;
                vuint32_t PDI_ECC_ERR1:1;
                vuint32_t PDI_LOCK_LOST:1;
                vuint32_t PDI_LOCK_DET:1;
                vuint32_t PDI_VSYNC_DET:1;
                vuint32_t PDI_HSYNC_DET:1;
                vuint32_t PDI_DE_DET:1;
                vuint32_t PDI_CLK_LOST:1;
                vuint32_t PDI_CLK_DET:1;
            } B;
        } PDI_STATUS;                   /* PDI status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:22;
                vuint32_t M_PDI_BLANKING_ERR:1;
                vuint32_t M_PDI_ECC_ERR2:1;
                vuint32_t M_PDI_ECC_ERR1:1;
                vuint32_t M_PDI_LOCK_LOST:1;
                vuint32_t M_PDI_LOCK_DET:1;
                vuint32_t M_PDI_VSYNC_DET:1;
                vuint32_t M_PDI_HSYNC_DET:1;
                vuint32_t M_PDI_DE_DET:1;
                vuint32_t M_PDI_CLK_LOST:1;
                vuint32_t M_PDI_CLK_DET:1;
            } B;
        } MASK_PDI_STATUS;              /* PDI Status Mask Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:12;
                vuint32_t RLE_ERR:1;
                vuint32_t HWC_ERR:1;
                vuint32_t SIG_ERR:1;
                vuint32_t DISP_ERR:1;
                  vuint32_t:12;
                vuint32_t L_PAR_ERR:4;
            } B;
        } PARR_ERR_STATUS;              /* Parameter error status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:12;
                vuint32_t M_RLE_ERR:1;
                vuint32_t M_HWC_ERR:1;
                vuint32_t M_SIG_ERR:1;
                vuint32_t M_DISP_ERR:1;
                  vuint32_t:12;
                vuint32_t M_L_PAR_ERR:4;
            } B;
        } MASK_PARR_ERR_STATUS;         /* Parameter error mask Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t INP_BUF_P2_HI:7;
                  vuint32_t:1;
                vuint32_t INP_BUF_P2_LO:7;
                  vuint32_t:1;
                vuint32_t INP_BUF_P1_HI:7;
                  vuint32_t:1;
                vuint32_t INP_BUF_P1_LO:7;
            } B;
        } THRESHOLD_INP1;               /* Threshold Input Buffer Register */

        vuint32_t DCULITE_reserved2;    /* 1 word */

        union {
            vuint32_t R;
            struct {
                vuint32_t Y_RED:10;
                  vuint32_t:1;
                vuint32_t Y_GREEN:10;
                  vuint32_t:1;
                vuint32_t Y_BLUE:10;
            } B;
        } LUMA_COMP;                    /* Luminance component Register */    

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t CR_RED:11;
                  vuint32_t:4;
                vuint32_t CB_RED:12;
            } B;
        } CHROMA_RED;                   /* Red component Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t CR_GREEN:11;
                  vuint32_t:4;
                vuint32_t CB_GREEN:12;
            } B;
        } CHROMA_GREEN;                 /* Green component Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t CR_BLUE:11;
                  vuint32_t:4;
                vuint32_t CB_BLUE:12;
            } B;
        } CHROMA_BLUE;                  /* Blue component Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t CRC_POS:32;
            } B;
        } CRC_POS;                      /* CRC Position Register */
    
        struct DCULITE_FG_tag FG[4];    /* FGCOLOR 1-4 */

        vuint32_t DCULITE_reserved3[0x18]; /* (0x2D0 - 0x270)/4 =  18 words*/

        union {
            vuint32_t R;
            struct {
                vuint32_t EN:1;
                  vuint32_t:31;
            } B;
        } LYR_INTPOL_EN;                /* Layer Interpolation Enable Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t Y_RED:10;
                  vuint32_t:1;
                vuint32_t Y_GREEN:10;
                  vuint32_t:1;
                vuint32_t Y_BLUE:10;
            } B;
        } LYR_LUMA_COMP;                /* Layer LUMA Component Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t CR_RED:11;
                  vuint32_t:4;
                vuint32_t CB_RED:12;
            } B;
        } LYR_CHROMA_RED;               /* Layer RED Chroma Component Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t CR_GREEN:11;
                  vuint32_t:4;
                vuint32_t CB_GREEN:12;
            } B;
        } LYR_CHROMA_GREEN;             /* Layer GREEN Chroma Component Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t CR_BLUE:11;
                  vuint32_t:4;
                vuint32_t CB_BLUE:12;
            } B;
        } LYR_CHROMA_BLUE;              /* Layer BLUE Chroma Component Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t SIZE:24;
            } B;
        } COMP_IMSIZE;                  /* Compressed Image Size Register */

        vuint32_t DCULITE_reserved4[0x06]; /* 0x300 - 0x2E8 =  6 words*/

        union {
            vuint32_t R;
            struct {
                vuint32_t HLB:1;
                  vuint32_t:31;
            } B;
        } GPR;                          /* Global Protection Register */
    
        union {
            vuint32_t R;
            struct {
                vuint32_t WEN_L0_1:1;
                vuint32_t WEN_L0_2:1;
                vuint32_t WEN_L0_3:1;
                vuint32_t WEN_L0_4:1;
                vuint32_t SLB_L0_1:1;
                vuint32_t SLB_L0_2:1;
                vuint32_t SLB_L0_3:1;
                vuint32_t SLB_L0_4:1;
                vuint32_t WEN_L0_5:1;
                vuint32_t WEN_L0_6:1;
                vuint32_t WEN_L0_7:1;
                  vuint32_t:1;
                vuint32_t SLB_L0_5:1;
                vuint32_t SLB_L0_6:1;
                vuint32_t SLB_L0_7:1;
                  vuint32_t:17;
            } B;
        } SLR_L0;                       /* Soft Lock Register Layer 0 */
    
        union {
            vuint32_t R;
            struct {
                vuint32_t WEN_L1_1:1;
                vuint32_t WEN_L1_2:1;
                vuint32_t WEN_L1_3:1;
                vuint32_t WEN_L1_4:1;
                vuint32_t SLB_L1_1:1;
                vuint32_t SLB_L1_2:1;
                vuint32_t SLB_L1_3:1;
                vuint32_t SLB_L1_4:1;
                vuint32_t WEN_L1_5:1;
                vuint32_t WEN_L1_6:1;
                vuint32_t WEN_L1_7:1;
                  vuint32_t:1;
                vuint32_t SLB_L1_5:1;
                vuint32_t SLB_L1_6:1;
                vuint32_t SLB_L1_7:1;
                  vuint32_t:17;
            } B;
        } SLR_L1;                       /* Soft Lock Register Layer 1 */
    
        union {
            vuint32_t R;
            struct {
                vuint32_t WEN_DISP:1;
                  vuint32_t:3;
                vuint32_t SLB_DISP:1;
                  vuint32_t:27;
            } B;
        } SLR_DISP_SIZE;                /* Soft Lock Register DISP_SIZE */
    
        union {
            vuint32_t R;
            struct {
                vuint32_t WEN_HSYNC:1;
                vuint32_t WEN_VSYNC:1;
                  vuint32_t:2;
                vuint32_t SLB_HSYNC:1;
                vuint32_t SLB_VSYNC:1;
                  vuint32_t:26;
            } B;
        } SLR_HVSYNC_PARA;              /* Soft Lock Register HSYNC VSYNC PARA */
    
        union {
            vuint32_t R;
            struct {
                vuint32_t WEN_POL:1;
                  vuint32_t:3;
                vuint32_t SLB_POL:1;
                  vuint32_t:27;
            } B;
        } SLR_POL;                      /* Soft Lock Register POL */
    
        union {
            vuint32_t R;
            struct {
                vuint32_t WEN_L0_FCOLOR:1;
                vuint32_t WEN_L0_BCOLOR:1;
                  vuint32_t:2;
                vuint32_t SLB_L0_FCOLOR:1;
                vuint32_t SLB_L0_BCOLOR:1;
                  vuint32_t:26;
            } B;
        } SLR_L0TRANSP;                 /* Soft Lock Register Layer 0 TRANSP */
    
        union {
            vuint32_t R;
            struct {
                vuint32_t WEN_L1_FCOLOR:1;
                vuint32_t WEN_L1_BCOLOR:1;
                  vuint32_t:2;
                vuint32_t SLB_L1_FCOLOR:1;
                vuint32_t SLB_L1_BCOLOR:1;
                  vuint32_t:26;
            } B;
        } SLR_L1TRANSP;                 /* Soft Lock Register Layer 1 TRANSP */
    
        vuint32_t DCU_reserved2[0x038]; /* Unused from end of registers */

        vuint32_t CURSOR[0x0100];       /* Hardware Cursor = 256 * 32bit */

        vuint32_t GAMMARED[0x100];      /* Gamma red table = 256 * 32bit */

        vuint32_t GAMMAGREEN[0x100];    /* Gamma green table = 256 * 32bit */

        vuint32_t GAMMABLUE[0x100];     /* Gamma blue table = 256 * 32bit */

        vuint32_t DCU_reserved3[0x300]; /* Unused = 768 * 32bit */

        vuint32_t CLUT[0x0200];         /* CLUT-Pallete memory = 512 * 32bit */

    };                                  /* end of DCULITE_tag */

/****************************************************************************/
/*                             MODULE : DRAMC                               */
/****************************************************************************/
    struct DRAMC_tag {

        union {
            vuint32_t R;
            struct {
                vuint32_t RST:1;
                vuint32_t CKE:1;
                vuint32_t CLKON:1;
                vuint32_t CMD:1;
                vuint32_t ROWSEL:3;
                vuint32_t BKSEL:4;
                  vuint32_t:3;
                vuint32_t B16:1;
                vuint32_t RDLY:4;
                vuint32_t H_DQSDLY:1;
                vuint32_t Q_DQSDLY:1;
                vuint32_t WDLY:3;
                vuint32_t EODT:1;
                vuint32_t ODT:1;
                vuint32_t FIFO_OVP:1;
                vuint32_t FIFO_UVP:1;
                  vuint32_t:2;
                vuint32_t FIFO_OVEN:1;
                vuint32_t FIFO_UVEN:1;
            } B;
        } SCR;                          /* System Configuration Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:2;
                vuint32_t REFRESH:14;
                vuint32_t CMD:8;
                vuint32_t PRE:8;
            } B;
        } TC0;                          /* Time Configuration Register 0 */

        union {
            vuint32_t R;
            struct {
                vuint32_t RFC:6;
                vuint32_t WR1:5;
                vuint32_t WRT:4;
                vuint32_t RRD:6;
                vuint32_t RC:6;
                vuint32_t RAS:5;
            } B;
        } TC1;                          /* Time Configuration Register 1 */
        
        union {
            vuint32_t R;
            struct {
                vuint32_t RCD:4;
                vuint32_t FAW:5;
                vuint32_t RTW:4;
                vuint32_t CCD:4;
                vuint32_t RTP:5;
                vuint32_t RP:5;
                vuint32_t RPA:5;
            } B;
        } TC2;                          /* Time Configuration Register 2 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t CMD:24;
            } B;
        } CMD;                          /* Command Register */
        
        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t CMD:16;
            } B;
        } CCMD;                         /* Compact Command Register */
        
        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t CMD:16;
            } B;
        } SRC[8];                       /* Self Refresh Command Registers 0..7 */
        
        union {
            vuint32_t R;
            struct {
                vuint32_t OFF3:8;
                vuint32_t OFF2:8;
                vuint32_t OFF1:8;
                vuint32_t OFF0:8;
            } B;
        } DQS_OC;                       /* DQS config offset count Register */
        
        union {
            vuint32_t R;
            struct {
                  vuint32_t:2;
                vuint32_t OFF3:6;
                  vuint32_t:2;
                vuint32_t OFF2:6;
                  vuint32_t:2;
                vuint32_t OFF1:6;
                  vuint32_t:2;
                vuint32_t OFF0:6;
            } B;
        } DQS_OT;                       /* DQS config offset time Register */
        
        union {
            vuint32_t R;
            struct {
                  vuint32_t:4;
                vuint32_t MC2:12;
                  vuint32_t:4;
                vuint32_t MC1:12;
            } B;
        } DQS_DS;                       /* DQS delay status Register */
        
        union {
            vuint32_t R;
            struct {
                vuint32_t WDATAI:1;
                vuint32_t LOOPB:1;
                vuint32_t RDCOMP:1;
                vuint32_t DQSTIM:2;
                vuint32_t DQSDRV:1;
                vuint32_t INPEN:1;
                  vuint32_t:25;
            } B;        
        } AUXCFG;                       /* Auxiliary Configuration Register */

        vuint32_t dramc_reserved[0x06]; /* 0x060 - 0x048 =  6 words*/
        
        union {
            vuint32_t R;
            struct {
                vuint32_t CCD_OTHER:4;
                vuint32_t WTR1_OTHER:4;
                vuint32_t CONFIG_SDR:1;
                vuint32_t CONFIG_CAS3:1;
                vuint32_t CONFIG_A15:1;
                  vuint32_t:17;
                vuint32_t CS_SELECT:4;
            } B;        
        } EXTRA;                        /* Extra Attributes */

    };                                  /* end of DRAMC_tag */

/****************************************************************************/
/*                             MODULE : DRAM PRIORITY MANGER                */
/****************************************************************************/
    struct DRAMPM_tag {

        union {
            vuint32_t R;
            struct {
                  vuint32_t:2;
                vuint32_t LUTSEL4:2;
                vuint32_t LUTSEL3:2;
                vuint32_t LUTSEL2:2;
                vuint32_t LUTSEL1:2;
                vuint32_t LUTSEL0:2;
                vuint32_t ACKCNT4:4;
                vuint32_t ACKCNT3:4;
                vuint32_t ACKCNT2:4;
                vuint32_t ACKCNT1:4;
                vuint32_t ACKCNT0:4;
            } B;
        } CFG1;                         /* Configuration Register 1 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:25;
                vuint32_t CONG:1;
                vuint32_t DCUOVR:1;
                vuint32_t ACKSEL4:1;
                vuint32_t ACKSEL3:1;
                vuint32_t ACKSEL2:1;
                vuint32_t ACKSEL1:1;
                vuint32_t ACKSEL0:1;
            } B;
        } CFG2;                         /* Configuration Register 2 */

        union {
            vuint32_t R;
            struct {
                vuint32_t SETCGLVL:8;
                vuint32_t CLRCGLVL:8;
                vuint32_t FLTRBAND:3;
                vuint32_t AVGHIPR:13;
            } B;
        } HPCFG;                        /* High Priority Configuration Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t PRIO15:4;
                vuint32_t PRIO14:4;
                vuint32_t PRIO13:4;
                vuint32_t PRIO12:4;
                vuint32_t PRIO11:4;
                vuint32_t PRIO10:4;
                vuint32_t PRIO9:4;
                vuint32_t PRIO8:4;
            } B;
        } MLUTU[5];                     /* Main Look Up Table 0..4 Upper */

        union {
            vuint32_t R;
            struct {
                vuint32_t PRIO7:4;
                vuint32_t PRIO6:4;
                vuint32_t PRIO5:4;
                vuint32_t PRIO4:4;
                vuint32_t PRIO3:4;
                vuint32_t PRIO2:4;
                vuint32_t PRIO1:4;
                vuint32_t PRIO0:4;
            } B;
        } MLUTL[5];                     /* Main Look Up Table 0..4 Lower */

        union {
            vuint32_t R;
            struct {
                vuint32_t PRIO15:4;
                vuint32_t PRIO14:4;
                vuint32_t PRIO13:4;
                vuint32_t PRIO12:4;
                vuint32_t PRIO11:4;
                vuint32_t PRIO10:4;
                vuint32_t PRIO9:4;
                vuint32_t PRIO8:4;
            } B;
        } ALUTU[5];                     /* Alternate Look Up Table 0..4 Upper */

        union {
            vuint32_t R;
            struct {
                vuint32_t PRIO7:4;
                vuint32_t PRIO6:4;
                vuint32_t PRIO5:4;
                vuint32_t PRIO4:4;
                vuint32_t PRIO3:4;
                vuint32_t PRIO2:4;
                vuint32_t PRIO1:4;
                vuint32_t PRIO0:4;
            } B;
        } ALUTL[5];                     /* Alternate Look Up Table 0..4 Lower */

        union {
            vuint32_t R;
            struct {
                vuint32_t INT:1;
                vuint32_t CLRINT:1;
                vuint32_t INTEN:1;
                vuint32_t DMAREQ:1;
                vuint32_t DMARSTP:1;
                vuint32_t EVTTIM:1;
                vuint32_t EVTTIMTRG:1;
                  vuint32_t:15;
                vuint32_t LUTSEL4:2;
                vuint32_t LUTSEL3:2;
                vuint32_t LUTSEL2:2;
                vuint32_t LUTSEL1:2;
                vuint32_t LUTSEL0:2;
            } B;
        } PMCFG;                        /* Performance Monitor Configuration */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t EVTMR:24;
            } B;
        } EVTMR;                        /* Event Timer */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t EVPRST:24;
            } B;
        } EVPRST;                       /* Event Timer Preset */

        union {
            vuint32_t R;
            struct {
                vuint32_t ADDR:27;
                  vuint32_t:5;
            } B;
        } PM1L;                         /* Performance Monitor 1 low address */

        union {
            vuint32_t R;
            struct {
                vuint32_t ADDR:27;
                  vuint32_t:5;
            } B;
        } PM2L;                         /* Performance Monitor 2 low address */

        union {
            vuint32_t R;
            struct {
                vuint32_t ADDR:27;
                  vuint32_t:5;
            } B;
        } PM1H;                         /* Performance Monitor 1 high address */

        union {
            vuint32_t R;
            struct {
                vuint32_t ADDR:27;
                  vuint32_t:5;
            } B;
        } PM2H;                         /* Performance Monitor 2 high address */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t CNTR:24;
            } B;
        } PM1CNTR;                      /* Performance Monitor 1 read counter */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t CNTR:24;
            } B;
        } PM2CNTR;                      /* Performance Monitor 2 read counter */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t CNTR:24;
            } B;
        } PM1CNTW;                      /* Performance Monitor 1 write counter */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t CNTR:24;
            } B;
        } PM2CNTW;                      /* Performance Monitor 2 write counter */

        vuint32_t DRMAPM_reserved1[2];  /* (0x100 - 0x0F8)/4 = 2 */

        union {
            vuint32_t R;
            struct {
                vuint32_t SPRIOCTR2_7_0:8;
                vuint32_t CNTR:24;
            } B;
        } GACKCTR0;                     /* Granted Ack Counter 0 */

        union {
            vuint32_t R;
            struct {
                vuint32_t SPRIOCTR2_15_8:8;
                vuint32_t CNTR:24;
            } B;
        } GACKCTR1;                     /* Granted Ack Counter 1 */

        union {
            vuint32_t R;
            struct {
                vuint32_t SPRIOCTR2_23_16:8;
                vuint32_t CNTR:24;
            } B;
        } GACKCTR2;                     /* Granted Ack Counter 2 */

        union {
            vuint32_t R;
            struct {
                vuint32_t SPRIOCTR3_7_0:8;
                vuint32_t CNTR:24;
            } B;
        } GACKCTR3;                     /* Granted Ack Counter 3 */

        union {
            vuint32_t R;
            struct {
                vuint32_t SPRIOCTR3_15_8:8;
                vuint32_t CNTR:24;
            } B;
        } GACKCTR4;                     /* Granted Ack Counter 4 */

        union {
            vuint32_t R;
            struct {
                vuint32_t SPRIOCTR3_23_16:8;
                vuint32_t CNTR:24;
            } B;
        } CUMWCTR0;                     /* Cumulative Wait Counter 0 */

        union {
            vuint32_t R;
            struct {
                vuint32_t SPRIOCTR4_7_0:8;
                vuint32_t CNTR:24;
            } B;
        } CUMWCTR1;                     /* Cumulative Wait Counter 1 */

        union {
            vuint32_t R;
            struct {
                vuint32_t SPRIOCTR4_15_8:8;
                vuint32_t CNTR:24;
            } B;
        } CUMWCTR2;                     /* Cumulative Wait Counter 2 */

        union {
            vuint32_t R;
            struct {
                vuint32_t SPRIOCTR4_23_16:8;
                vuint32_t CNTR:24;
            } B;
        } CUMWCTR3;                     /* Cumulative Wait Counter 3 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t CNTR:24;
            } B;
        } CUMWCTR4;                     /* Cumulative Wait Counter 4 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t CNTR:24;
            } B;
        } SPRIOCTR[5];                  /* Summed Priority Counters 0..4 */

    };                                  /* end of DRAMC_tag */

/****************************************************************************/
/*                             MODULE : VIU                                 */
/****************************************************************************/
    struct VIU_tag {

        union {
            vuint32_t R;
            struct {
                vuint32_t MODE32BIT:1;
                vuint32_t ROUND_ON:1;
                vuint32_t DITHER_ON:1;
                vuint32_t FIELD_NO:1;
                vuint32_t DMA_ACT:1;
                vuint32_t SCALER_EN:1;
                vuint32_t RGB_EN:1;
                vuint32_t BC_EN:1;
                vuint32_t MODE444:1;
                  vuint32_t:1;
                vuint32_t ERROR_IRQ:1;
                vuint32_t DMA_END_IRQ:1;
                vuint32_t VSTART_IRQ:1;
                vuint32_t HSYNC_IRQ:1;
                vuint32_t VSYNC_IRQ:1;
                vuint32_t FIELD_IRQ:1;
                  vuint32_t:1;
                vuint32_t ECC_EN:1;
                vuint32_t ERROR_EN:1;
                vuint32_t DMA_END_EN:1;
                vuint32_t VSTART_EN:1;
                vuint32_t HSYNC_EN:1;
                vuint32_t VSYNC_EN:1;
                vuint32_t FIELD_EN:1;
                vuint32_t ERROR_CODE:4;
                vuint32_t FORMAT_CTRL:3;
                vuint32_t SOFT_RESET:1;
            } B;
        } SCR;                          /* Status and Configuration Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t Y_RED:10;
                  vuint32_t:1;
                vuint32_t Y_GREEN:10;
                  vuint32_t:1;
                vuint32_t Y_BLUE:10;
            } B;
        } LUMA_COMP;                    /* Luminance coefficients Register */    

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t CR_RED:11;
                  vuint32_t:4;
                vuint32_t CB_RED:12;
            } B;
        } CHROMA_RED;                   /* Red coefficient Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t CR_GREEN:11;
                  vuint32_t:4;
                vuint32_t CB_GREEN:12;
            } B;
        } CHROMA_GREEN;                 /* Green coefficient Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:5;
                vuint32_t CR_BLUE:11;
                  vuint32_t:4;
                vuint32_t CB_BLUE:12;
            } B;
        } CHROMA_BLUE;                  /* Blue coefficient Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t ADDR:29;
                  vuint32_t:3;
            } B;
        } DMA_ADDR;                     /* DMA Address Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t INC:13;
                  vuint32_t:3;
            } B;
        } DMA_INC;                      /* DMA increment Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t LINEC:16;
                vuint32_t PIXELC:16;
            } B;
        } INVSZ;                        /* Input Video Size */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t ALARM:16;
            } B;
        } HPALRM;                       /* High Priority Alarm Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:24;
                vuint32_t ALPHA:8;
            } B;
        } ALPHA;                        /* Alpha Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:21;
                vuint32_t FACTOR:11;
            } B;
        } HFACTOR;                      /* Horizontal Factor Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:21;
                vuint32_t FACTOR:11;
            } B;
        } VFACTOR;                      /* Vertical Factor Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t LINEC:16;
                vuint32_t PIXELC:16;
            } B;
        } VID_SIZE;                     /* Output Video Size Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:22;
                vuint32_t ADDR:8;
                  vuint32_t:2;
            } B;
        } LUT_ADDR;                     /* B/C Adjust LUT addr Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t DATA:32;
            } B;
        } LUT_DATA;                     /* B/C Adjust LUT data Register */

    };                                  /* end of VIU_tag */

/****************************************************************************/
/*                             MODULE : GFX2D                               */
/****************************************************************************/
    struct GFX2D_tag {

        vuint32_t G12_COMMANDSTREAM;    /* Status and Configuration Register */
        
        vuint32_t GFX2D_reserved1[0xFE];/* 0x3FC - 0x004 = 254 words */

        vuint32_t G12_MMUCOMMANDSTREAM;

        vuint32_t G12_REVISION;

        vuint32_t GFX2D_reserved2[3];   /* 0x410 - 0x404 = 3 words */

        vuint32_t G12_SYSSTATUS;

        vuint32_t GFX2D_reserved3;      /* 0x418 - 0x414 = 1 word */

        vuint32_t G12_IRQSTATUS;

        vuint32_t GFX2D_reserved4[7];   /* 0x438 - 0x41C = 7 words*/

        vuint32_t G12_IRQENABLE;

        vuint32_t GFX2D_reserved5[41];  /* 0x4E0 - 0x43C = 41 words */

        vuint32_t G12_IRQ_ACTIVE_CNT;

        vuint32_t GFX2D_reserved6[9];   /* 0x508 - 0x4E4 = 9 words */

        vuint32_t G12_CLOCKEN;

        vuint32_t GFX2D_reserved7;      /* 0x510 - 0x50C = 1 word */

        vuint32_t MMU_READ_ADDR;

        vuint32_t GFX2D_reserved8;      /* 0x518 - 0x514 = 1 word */

        vuint32_t MMU_READ_DATA;

        vuint32_t GFX2D_reserved9[0xA9]; /* 0x7C0 - 0x51C = 169 words */

        vuint32_t G12_FIFOFREE;
    };                                  /* end of GFX2D_tag */

/****************************************************************************/
/*                             MODULE : GXG                                 */
/****************************************************************************/
    struct GXG_WINDOW_tag {
        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t RWD:1;
                vuint32_t RHW:1;
                vuint32_t RBY:1;
                  vuint32_t:1;
                vuint32_t WWD:1;
                vuint32_t WHW:1;
                vuint32_t WBY:1;
                vuint32_t ALPHA:8;
                vuint32_t MODE:2;
                  vuint32_t:2;
                vuint32_t STRIDE:12;
            } B;
        } CNFG;                         /* Window Configuration Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t BASE3123:1;
                vuint32_t BASE223:1;
                vuint32_t BASE20:1;
            } B;
        } BASE;                         /* Window Destination Base Address Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t FIRST313:1;
                vuint32_t FIRST20:1;
            } B;
        } FRST;                         /* Window First Address Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t LAST313:1;
                vuint32_t LAST20:1;
            } B;
        } LAST;                         /* Window Last Address Register */

    };
    
    struct GXG_tag {

        struct GXG_WINDOW_tag WINDOW[4];

    };                                  /* end of GXG_tag */

/****************************************************************************/
/*                             MODULE : TCON                                */
/****************************************************************************/
    struct TCON_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t TCON_EN:1;
                  vuint32_t:1;
                vuint32_t TCON_BYPASS:1;
                vuint32_t DATA_INV_EN:1;
                vuint32_t TCON11_INV:1;
                vuint32_t TCON10_INV:1;
                vuint32_t TCON9_INV:1;
                vuint32_t TCON8_INV:1;
                vuint32_t TCON7_INV:1;
                vuint32_t TCON6_INV:1;
                vuint32_t TCON5_INV:1;
                vuint32_t TCON4_INV:1;
                vuint32_t TCON3_INV:1;
                vuint32_t TCON2_INV:1;
                vuint32_t TCON1_INV:1;
                vuint32_t TCON0_INV:1;
                vuint32_t INIT_DELAY:3;
                vuint32_t V_REF_SEL:3;
                vuint32_t H_REF_SEL:2;
                vuint32_t VLEN:2;
                vuint32_t HSYNC_INV:1;
                vuint32_t VSYNC_INV:1;
                vuint32_t COLOR_DEPTH:1;
                vuint32_t RGB_PADDING_EN:1;
                vuint32_t RGB_PADDING:1;
                vuint32_t RSDS_MODE:1;
            } B;
        } CTRL1;                        /* Control 1 Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:22;
                vuint32_t CLK_POS:5;
                vuint32_t COLOR_ORDER:3;
                vuint32_t BIT_ORDER:1;
                vuint32_t BIT_SWAP:1;
            } B;
        } BMC;                          /* Comparator Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t FUNC_SEL:1;
                  vuint32_t:19;
                vuint32_t COMP_VALUE:12;
            } B;
        } COMP[4];                      /* Comparator Mask Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:20;
                vuint32_t MASK:12;
            } B;
        } COMP_MSK[4];                  /* Bit map control Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t FUNC_SEL:2;
                  vuint32_t:2;
                vuint32_t SET:12;
                vuint32_t COMPARATOR_SEL:2;
                  vuint32_t:2;
                vuint32_t RESET:12;
            } B;
        } PULSE[6];                     /* Pulse Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:4;
                vuint32_t SETMASK:12;
                  vuint32_t:4;
                vuint32_t RESETMASK:12;
            } B;
        } PULSE_MSK[6];                 /* Pulse mask Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t INDEX3_SEL:3;
                vuint32_t INDEX2_SEL:3;
                vuint32_t INDEX1_SEL:3;
                vuint32_t INDEX0_SEL:3;
                  vuint32_t:10;
                vuint32_t Y_SEL:5;
                vuint32_t X_SEL:5;
            } B1;
        } SMX[14];                      /* Multiplexer control Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:2;
                vuint32_t TCON5:5;
                vuint32_t TCON4:5;
                vuint32_t TCON3:5;
                vuint32_t TCON2:5;
                vuint32_t TCON1:5;
                vuint32_t TCON0:5;
            } B;
        } OMUX_LOW;                     /* Output MUX Low Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:2;
                vuint32_t TCON11:5;
                vuint32_t TCON10:5;
                vuint32_t TCON9:5;
                vuint32_t TCON8:5;
                vuint32_t TCON7:5;
                vuint32_t TCON6:5;
            } B;
        } OMUX_HIGH;                    /* Output MUX high Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t LUT:32;
            } B;
        } LUT[14];                      /* Look up table Registers */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:16;
                vuint32_t POL:1;
                  vuint32_t:2;
                vuint32_t OSUFINE2:1;
                vuint32_t OSUFINE1:1;
                vuint32_t OSUCRSE2:1;
                vuint32_t OSUCRSE1:1;
                vuint32_t OSDFINE:1;
                vuint32_t SKEWOPT:8;
            } B;
        } DLY[13];                      /* Look up table Registers */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:7;
                vuint32_t CLK_OFFSET:9;
                  vuint32_t:8;
                vuint32_t DIV_RATIO:8;
            } B;
        } CTRL2;                        /* Control 2 Register */
    };                                  /* end of TCON_tag */

/****************************************************************************/
/*                             MODULE : GRAMC                               */
/****************************************************************************/
    struct GRAMC_tag {

        union {
            vuint32_t R;
            struct {
                  vuint32_t:26;
                vuint32_t PFE1:1;
                vuint32_t PFE0:1;
                  vuint32_t:2;
                vuint32_t PRI:2;
            } B;
        } CR;                           /* Control Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:31;
                vuint32_t BUSY:1;
            } B;
        } SR;                           /* Status Register */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t ADDR:20;
                  vuint32_t:4;
            } B;
        } BEG;                          /* Beginning address for Fill Register */
        
        union {
            vuint32_t R;
            struct {
                  vuint32_t:8;
                vuint32_t ADDR:20;
                  vuint32_t:4;
            } B;
        } END;                          /* End address for Fill Register */
        
        union {
            vuint32_t R;
            struct {
                  vuint32_t:27;
                vuint32_t FILL:1;
                  vuint32_t:3;
                vuint32_t START:1;
            } B;
        } FIL;                          /* Fill Register */
        
    };                                  /* end of GRAMC_tag */

/****************************************************************************/
/*                     MODULE : XBAR                                      */
/****************************************************************************/
    struct XBAR_tag {
        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t MSTR7:3;    	/* Master 7 Priority - Reserved */
                  vuint32_t:1;
                vuint32_t MSTR6:3;    	/* Master 6 Priority - DCU */
                  vuint32_t:1;
                vuint32_t MSTR5:3;    	/* Master 5 Priority - DCULite */
                  vuint32_t:1;
                vuint32_t MSTR4:3;      /* Master 4 Priority - VIU */
                  vuint32_t:1;
                vuint32_t MSTR3:3;      /* Master 3 Priority - GFX2D/GXG */
                  vuint32_t:1;
                vuint32_t MSTR2:3;      /* Master 2 Priority - eDMA */
                  vuint32_t:1;
                vuint32_t MSTR1:3;      /* Master 1 Priority - e200z4 Core load/store & Nexus port  */
                  vuint32_t:1;
                vuint32_t MSTR0:3;      /* Master 0 Priority - e200z4 core Instruction */
            } B;
        } MPR0;                         /* Master Priority Register for Slave port 0 (Instruction Flash) @baseaddress + 0x00 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t MSTR7:3;    	/* Master 7 Priority - Reserved */
                  vuint32_t:1;
                vuint32_t MSTR6:3;    	/* Master 6 Priority - DCU */
                  vuint32_t:1;
                vuint32_t MSTR5:3;    	/* Master 5 Priority - DCULite */
                  vuint32_t:1;
                vuint32_t MSTR4:3;      /* Master 4 Priority - VIU */
                  vuint32_t:1;
                vuint32_t MSTR3:3;      /* Master 3 Priority - GFX2D/GXG */
                  vuint32_t:1;
                vuint32_t MSTR2:3;      /* Master 2 Priority - eDMA */
                  vuint32_t:1;
                vuint32_t MSTR1:3;      /* Master 1 Priority - e200z4 Core load/store & Nexus port  */
                  vuint32_t:1;
                vuint32_t MSTR0:3;      /* Master 0 Priority - e200z4 core Instruction */
            } B;
        } AMPR0;                        /* Alternate Priority Register for Slave port 0 (Instruction Flash) @baseaddress + 0x04 */

        int32_t XBAR_reserved_0008[2];	/* 0x0008 - 0x000F */

        union {
            vuint32_t R;
            struct {
                vuint32_t RO:1;
                vuint32_t HLP:1;        /* Halt Low Priority */
                  vuint32_t:6;
                vuint32_t HPE7:1;       /* High Priority Enable */
                vuint32_t HPE6:1;       /* High Priority Enable */
                vuint32_t HPE5:1;       /* High Priority Enable */
                vuint32_t HPE4:1;       /* High Priority Enable */
                vuint32_t HPE3:1;       /* High Priority Enable */
                vuint32_t HPE2:1;       /* High Priority Enable */
                vuint32_t HPE1:1;       /* High Priority Enable */
                vuint32_t HPE0:1;       /* High Priority Enable */
                  vuint32_t:6;
                vuint32_t ARB:2;
                vuint32_t:2;
                vuint32_t PCTL:2;
                vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } SGPCR0;                       /* Slave General Purpose Control Register 0 (Instruction Flash) @baseaddress + 0x10 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t HLP:1;        /* Halt Low Priority */
                  vuint32_t:6;
                vuint32_t HPE7:1;       /* High Priority Enable */
                vuint32_t HPE6:1;       /* High Priority Enable */
                vuint32_t HPE5:1;       /* High Priority Enable */
                vuint32_t HPE4:1;       /* High Priority Enable */
                vuint32_t HPE3:1;       /* High Priority Enable */
                vuint32_t HPE2:1;       /* High Priority Enable */
                vuint32_t HPE1:1;       /* High Priority Enable */
                vuint32_t HPE0:1;       /* High Priority Enable */
                  vuint32_t:6;
                vuint32_t ARB:2;
                vuint32_t:2;
                vuint32_t PCTL:2;
                vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } ASGPCR0;                      /* Alternate Slave General Purpose Control Register 0 (Instruction Flash) @baseaddress + 0x14 */

        int32_t XBAR_reserved_0018[58];	/* 0x0018 - 0x01FF */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t MSTR7:3;    	/* Master 7 Priority - Reserved */
                  vuint32_t:1;
                vuint32_t MSTR6:3;    	/* Master 6 Priority - DCU */
                  vuint32_t:1;
                vuint32_t MSTR5:3;    	/* Master 5 Priority - DCULite */
                  vuint32_t:1;
                vuint32_t MSTR4:3;      /* Master 4 Priority - VIU */
                  vuint32_t:1;
                vuint32_t MSTR3:3;      /* Master 3 Priority - GFX2D/GXG */
                  vuint32_t:1;
                vuint32_t MSTR2:3;      /* Master 2 Priority - eDMA */
                  vuint32_t:1;
                vuint32_t MSTR1:3;      /* Master 1 Priority - e200z4 Core load/store & Nexus port  */
                  vuint32_t:1;
                vuint32_t MSTR0:3;      /* Master 0 Priority - e200z4 core Instruction */
            } B;
        } MPR1;                         /* Master Priority Register for Slave port 1 (Flash) @baseaddress + 0x100 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t MSTR7:3;    	/* Master 7 Priority - Reserved */
                  vuint32_t:1;
                vuint32_t MSTR6:3;    	/* Master 6 Priority - DCU */
                  vuint32_t:1;
                vuint32_t MSTR5:3;    	/* Master 5 Priority - DCULite */
                  vuint32_t:1;
                vuint32_t MSTR4:3;      /* Master 4 Priority - VIU */
                  vuint32_t:1;
                vuint32_t MSTR3:3;      /* Master 3 Priority - GFX2D/GXG */
                  vuint32_t:1;
                vuint32_t MSTR2:3;      /* Master 2 Priority - eDMA */
                  vuint32_t:1;
                vuint32_t MSTR1:3;      /* Master 1 Priority - e200z4 Core load/store & Nexus port  */
                  vuint32_t:1;
                vuint32_t MSTR0:3;      /* Master 0 Priority - e200z4 core Instruction */
            } B;
        } AMPR1;                        /* Master Priority Register for Slave port 1 (Flash) @baseaddress + 0x104 */

        int32_t XBAR_reserved_0108[2];	/* 0x0108 - 0x010F */

        union {
            vuint32_t R;
            struct {
                vuint32_t RO:1;
                vuint32_t HLP:1;        /* Halt Low Priority */
                  vuint32_t:6;
                vuint32_t HPE7:1;       /* High Priority Enable */
                vuint32_t HPE6:1;       /* High Priority Enable */
                vuint32_t HPE5:1;       /* High Priority Enable */
                vuint32_t HPE4:1;       /* High Priority Enable */
                vuint32_t HPE3:1;       /* High Priority Enable */
                vuint32_t HPE2:1;       /* High Priority Enable */
                vuint32_t HPE1:1;       /* High Priority Enable */
                vuint32_t HPE0:1;       /* High Priority Enable */
                  vuint32_t:6;
                vuint32_t ARB:2;
                vuint32_t:2;
                vuint32_t PCTL:2;
                vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } SGPCR1;                       /* Slave General Purpose Control Register 1 (Flash) @baseaddress + 0x110 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t HLP:1;        /* Halt Low Priority */
                  vuint32_t:6;
                vuint32_t HPE7:1;       /* High Priority Enable */
                vuint32_t HPE6:1;       /* High Priority Enable */
                vuint32_t HPE5:1;       /* High Priority Enable */
                vuint32_t HPE4:1;       /* High Priority Enable */
                vuint32_t HPE3:1;       /* High Priority Enable */
                vuint32_t HPE2:1;       /* High Priority Enable */
                vuint32_t HPE1:1;       /* High Priority Enable */
                vuint32_t HPE0:1;       /* High Priority Enable */
                  vuint32_t:6;
                vuint32_t ARB:2;
                vuint32_t:2;
                vuint32_t PCTL:2;
                vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } ASGPCR1;                      /* Alternate Slave General Purpose Control Register 1 (Flash) @baseaddress + 0x114 */

        int32_t XBAR_reserved_0118[58];	/* 0x0118 - 0x01FF */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t MSTR7:3;    	/* Master 7 Priority - Reserved */
                  vuint32_t:1;
                vuint32_t MSTR6:3;    	/* Master 6 Priority - DCU */
                  vuint32_t:1;
                vuint32_t MSTR5:3;    	/* Master 5 Priority - DCULite */
                  vuint32_t:1;
                vuint32_t MSTR4:3;      /* Master 4 Priority - VIU */
                  vuint32_t:1;
                vuint32_t MSTR3:3;      /* Master 3 Priority - GFX2D/GXG */
                  vuint32_t:1;
                vuint32_t MSTR2:3;      /* Master 2 Priority - eDMA */
                  vuint32_t:1;
                vuint32_t MSTR1:3;      /* Master 1 Priority - e200z4 Core load/store & Nexus port  */
                  vuint32_t:1;
                vuint32_t MSTR0:3;      /* Master 0 Priority - e200z4 core Instruction */
            } B;
        } MPR2;                         /* Master Priority Register for Slave port 2 (SRAM) @baseaddress + 0x200 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t MSTR7:3;    	/* Master 7 Priority - Reserved */
                  vuint32_t:1;
                vuint32_t MSTR6:3;    	/* Master 6 Priority - DCU */
                  vuint32_t:1;
                vuint32_t MSTR5:3;    	/* Master 5 Priority - DCULite */
                  vuint32_t:1;
                vuint32_t MSTR4:3;      /* Master 4 Priority - VIU */
                  vuint32_t:1;
                vuint32_t MSTR3:3;      /* Master 3 Priority - GFX2D/GXG */
                  vuint32_t:1;
                vuint32_t MSTR2:3;      /* Master 2 Priority - eDMA */
                  vuint32_t:1;
                vuint32_t MSTR1:3;      /* Master 1 Priority - e200z4 Core load/store & Nexus port  */
                  vuint32_t:1;
                vuint32_t MSTR0:3;      /* Master 0 Priority - e200z4 core Instruction */
            } B;
        } AMPR2;                        /* Master Priority Register for Slave port 2 (SRAM) @baseaddress + 0x204 */

        int32_t XBAR_reserved_0208[2];	/* 0x0208 - 0x020F */

        union {
            vuint32_t R;
            struct {
                vuint32_t RO:1;
                vuint32_t HLP:1;        /* Halt Low Priority */
                  vuint32_t:6;
                vuint32_t HPE7:1;       /* High Priority Enable */
                vuint32_t HPE6:1;       /* High Priority Enable */
                vuint32_t HPE5:1;       /* High Priority Enable */
                vuint32_t HPE4:1;       /* High Priority Enable */
                vuint32_t HPE3:1;       /* High Priority Enable */
                vuint32_t HPE2:1;       /* High Priority Enable */
                vuint32_t HPE1:1;       /* High Priority Enable */
                vuint32_t HPE0:1;       /* High Priority Enable */
                  vuint32_t:6;
                vuint32_t ARB:2;
                vuint32_t:2;
                vuint32_t PCTL:2;
                vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } SGPCR2;                       /* Slave General Purpose Control Register 2 (SRAM)@baseaddress + 0x210 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t HLP:1;        /* Halt Low Priority */
                  vuint32_t:6;
                vuint32_t HPE7:1;       /* High Priority Enable */
                vuint32_t HPE6:1;       /* High Priority Enable */
                vuint32_t HPE5:1;       /* High Priority Enable */
                vuint32_t HPE4:1;       /* High Priority Enable */
                vuint32_t HPE3:1;       /* High Priority Enable */
                vuint32_t HPE2:1;       /* High Priority Enable */
                vuint32_t HPE1:1;       /* High Priority Enable */
                vuint32_t HPE0:1;       /* High Priority Enable */
                  vuint32_t:6;
                vuint32_t ARB:2;
                vuint32_t:2;
                vuint32_t PCTL:2;
                vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } ASGPCR2;                      /* Alternate Slave General Purpose Control Register 2 (SRAM) @baseaddress + 0x214 */

        int32_t XBAR_reserved_0218[58];	/* 0x0218 - 0x02FF */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t MSTR7:3;    	/* Master 7 Priority - Reserved */
                  vuint32_t:1;
                vuint32_t MSTR6:3;    	/* Master 6 Priority - DCU */
                  vuint32_t:1;
                vuint32_t MSTR5:3;    	/* Master 5 Priority - DCULite */
                  vuint32_t:1;
                vuint32_t MSTR4:3;      /* Master 4 Priority - VIU */
                  vuint32_t:1;
                vuint32_t MSTR3:3;      /* Master 3 Priority - GFX2D/GXG */
                  vuint32_t:1;
                vuint32_t MSTR2:3;      /* Master 2 Priority - eDMA */
                  vuint32_t:1;
                vuint32_t MSTR1:3;      /* Master 1 Priority - e200z4 Core load/store & Nexus port  */
                  vuint32_t:1;
                vuint32_t MSTR0:3;      /* Master 0 Priority - e200z4 core Instruction */
            } B;
        } MPR3;                         /* Master Priority Register for Slave port 3 (GFX2D GRAM) @baseaddress + 0x300 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t MSTR7:3;    	/* Master 7 Priority - Reserved */
                  vuint32_t:1;
                vuint32_t MSTR6:3;    	/* Master 6 Priority - DCU */
                  vuint32_t:1;
                vuint32_t MSTR5:3;    	/* Master 5 Priority - DCULite */
                  vuint32_t:1;
                vuint32_t MSTR4:3;      /* Master 4 Priority - VIU */
                  vuint32_t:1;
                vuint32_t MSTR3:3;      /* Master 3 Priority - GFX2D/GXG */
                  vuint32_t:1;
                vuint32_t MSTR2:3;      /* Master 2 Priority - eDMA */
                  vuint32_t:1;
                vuint32_t MSTR1:3;      /* Master 1 Priority - e200z4 Core load/store & Nexus port  */
                  vuint32_t:1;
                vuint32_t MSTR0:3;      /* Master 0 Priority - e200z4 core Instruction */
            } B;
        } AMPR3;                        /* Master Priority Register for Slave port 3 (GFX2D GRAM) @baseaddress + 0x304 */

        int32_t XBAR_reserved_0308[2];	/* 0x0308 - 0x030F */

        union {
            vuint32_t R;
            struct {
                vuint32_t RO:1;
                vuint32_t HLP:1;        /* Halt Low Priority */
                  vuint32_t:6;
                vuint32_t HPE7:1;       /* High Priority Enable */
                vuint32_t HPE6:1;       /* High Priority Enable */
                vuint32_t HPE5:1;       /* High Priority Enable */
                vuint32_t HPE4:1;       /* High Priority Enable */
                vuint32_t HPE3:1;       /* High Priority Enable */
                vuint32_t HPE2:1;       /* High Priority Enable */
                vuint32_t HPE1:1;       /* High Priority Enable */
                vuint32_t HPE0:1;       /* High Priority Enable */
                  vuint32_t:6;
                vuint32_t ARB:2;
                vuint32_t:2;
                vuint32_t PCTL:2;
                vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } SGPCR3;                       /* Slave General Purpose Control Register 3 (GFX2D GRAM)@baseaddress + 0x310 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t HLP:1;        /* Halt Low Priority */
                  vuint32_t:6;
                vuint32_t HPE7:1;       /* High Priority Enable */
                vuint32_t HPE6:1;       /* High Priority Enable */
                vuint32_t HPE5:1;       /* High Priority Enable */
                vuint32_t HPE4:1;       /* High Priority Enable */
                vuint32_t HPE3:1;       /* High Priority Enable */
                vuint32_t HPE2:1;       /* High Priority Enable */
                vuint32_t HPE1:1;       /* High Priority Enable */
                vuint32_t HPE0:1;       /* High Priority Enable */
                  vuint32_t:6;
                vuint32_t ARB:2;
                vuint32_t:2;
                vuint32_t PCTL:2;
                vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } ASGPCR3;                      /* Alternate Slave General Purpose Control Register 3 (GFX2D GRAM) @baseaddress + 0x314 */

        int32_t XBAR_reserved_0318[58];	/* 0x0318 - 0x03FF */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t MSTR7:3;    	/* Master 7 Priority - Reserved */
                  vuint32_t:1;
                vuint32_t MSTR6:3;    	/* Master 6 Priority - DCU */
                  vuint32_t:1;
                vuint32_t MSTR5:3;    	/* Master 5 Priority - DCULite */
                  vuint32_t:1;
                vuint32_t MSTR4:3;      /* Master 4 Priority - VIU */
                  vuint32_t:1;
                vuint32_t MSTR3:3;      /* Master 3 Priority - GFX2D/GXG */
                  vuint32_t:1;
                vuint32_t MSTR2:3;      /* Master 2 Priority - eDMA */
                  vuint32_t:1;
                vuint32_t MSTR1:3;      /* Master 1 Priority - e200z4 Core load/store & Nexus port  */
                  vuint32_t:1;
                vuint32_t MSTR0:3;      /* Master 0 Priority - e200z4 core Instruction */
            } B;
        } MPR4;                         /* Master Priority Register for Slave port 4 (GRAM) @baseaddress + 0x400 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t MSTR7:3;    	/* Master 7 Priority - Reserved */
                  vuint32_t:1;
                vuint32_t MSTR6:3;    	/* Master 6 Priority - DCU */
                  vuint32_t:1;
                vuint32_t MSTR5:3;    	/* Master 5 Priority - DCULite */
                  vuint32_t:1;
                vuint32_t MSTR4:3;      /* Master 4 Priority - VIU */
                  vuint32_t:1;
                vuint32_t MSTR3:3;      /* Master 3 Priority - GFX2D/GXG */
                  vuint32_t:1;
                vuint32_t MSTR2:3;      /* Master 2 Priority - eDMA */
                  vuint32_t:1;
                vuint32_t MSTR1:3;      /* Master 1 Priority - e200z4 Core load/store & Nexus port  */
                  vuint32_t:1;
                vuint32_t MSTR0:3;      /* Master 0 Priority - e200z4 core Instruction */
            } B;
        } AMPR4;                        /* Master Priority Register for Slave port 4 (GRAM) @baseaddress + 0x404 */

        int32_t XBAR_reserved_0408[2];	/* 0x0408 - 0x040F */

        union {
            vuint32_t R;
            struct {
                vuint32_t RO:1;
                vuint32_t HLP:1;        /* Halt Low Priority */
                  vuint32_t:6;
                vuint32_t HPE7:1;       /* High Priority Enable */
                vuint32_t HPE6:1;       /* High Priority Enable */
                vuint32_t HPE5:1;       /* High Priority Enable */
                vuint32_t HPE4:1;       /* High Priority Enable */
                vuint32_t HPE3:1;       /* High Priority Enable */
                vuint32_t HPE2:1;       /* High Priority Enable */
                vuint32_t HPE1:1;       /* High Priority Enable */
                vuint32_t HPE0:1;       /* High Priority Enable */
                  vuint32_t:6;
                vuint32_t ARB:2;
                vuint32_t:2;
                vuint32_t PCTL:2;
                vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } SGPCR4;                       /* Slave General Purpose Control Register 4 (GRAM)@baseaddress + 0x410 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t HLP:1;        /* Halt Low Priority */
                  vuint32_t:6;
                vuint32_t HPE7:1;       /* High Priority Enable */
                vuint32_t HPE6:1;       /* High Priority Enable */
                vuint32_t HPE5:1;       /* High Priority Enable */
                vuint32_t HPE4:1;       /* High Priority Enable */
                vuint32_t HPE3:1;       /* High Priority Enable */
                vuint32_t HPE2:1;       /* High Priority Enable */
                vuint32_t HPE1:1;       /* High Priority Enable */
                vuint32_t HPE0:1;       /* High Priority Enable */
                  vuint32_t:6;
                vuint32_t ARB:2;
                vuint32_t:2;
                vuint32_t PCTL:2;
                vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } ASGPCR5;                      /* Alternate Slave General Purpose Control Register 5 (Flash) @baseaddress + 0x514 */

        int32_t XBAR_reserved_0418[58];	/* 0x0418 - 0x04FF */

        /* Slave XBAR Port 5 Not implemented @baseaddress + 0x510 */

        int32_t XBAR_reserved_0500[64];	/* 0x0500 - 0x05FF */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t MSTR7:3;    	/* Master 7 Priority - Reserved */
                  vuint32_t:1;
                vuint32_t MSTR6:3;    	/* Master 6 Priority - DCU */
                  vuint32_t:1;
                vuint32_t MSTR5:3;    	/* Master 5 Priority - DCULite */
                  vuint32_t:1;
                vuint32_t MSTR4:3;      /* Master 4 Priority - VIU */
                  vuint32_t:1;
                vuint32_t MSTR3:3;      /* Master 3 Priority - GFX2D/GXG */
                  vuint32_t:1;
                vuint32_t MSTR2:3;      /* Master 2 Priority - eDMA */
                  vuint32_t:1;
                vuint32_t MSTR1:3;      /* Master 1 Priority - e200z4 Core load/store & Nexus port  */
                  vuint32_t:1;
                vuint32_t MSTR0:3;      /* Master 0 Priority - e200z4 core Instruction */
            } B;
        } MPR6;                         /* Master Priority Register for Slave port 6 (QuadSPI/RLE) @baseaddress + 0x600 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t MSTR7:3;    	/* Master 7 Priority - Reserved */
                  vuint32_t:1;
                vuint32_t MSTR6:3;    	/* Master 6 Priority - DCU */
                  vuint32_t:1;
                vuint32_t MSTR5:3;    	/* Master 5 Priority - DCULite */
                  vuint32_t:1;
                vuint32_t MSTR4:3;      /* Master 4 Priority - VIU */
                  vuint32_t:1;
                vuint32_t MSTR3:3;      /* Master 3 Priority - GFX2D/GXG */
                  vuint32_t:1;
                vuint32_t MSTR2:3;      /* Master 2 Priority - eDMA */
                  vuint32_t:1;
                vuint32_t MSTR1:3;      /* Master 1 Priority - e200z4 Core load/store & Nexus port  */
                  vuint32_t:1;
                vuint32_t MSTR0:3;      /* Master 0 Priority - e200z4 core Instruction */
            } B;
        } AMPR6;                        /* Master Priority Register for Slave port 6 (QuadSPI/RLE) @baseaddress + 0x604 */

        int32_t XBAR_reserved_0604[2];	/* 0x0608 - 0x060F */

        union {
            vuint32_t R;
            struct {
                vuint32_t RO:1;
                vuint32_t HLP:1;        /* Halt Low Priority */
                  vuint32_t:6;
                vuint32_t HPE7:1;       /* High Priority Enable */
                vuint32_t HPE6:1;       /* High Priority Enable */
                vuint32_t HPE5:1;       /* High Priority Enable */
                vuint32_t HPE4:1;       /* High Priority Enable */
                vuint32_t HPE3:1;       /* High Priority Enable */
                vuint32_t HPE2:1;       /* High Priority Enable */
                vuint32_t HPE1:1;       /* High Priority Enable */
                vuint32_t HPE0:1;       /* High Priority Enable */
                  vuint32_t:6;
                vuint32_t ARB:2;
                vuint32_t:2;
                vuint32_t PCTL:2;
                vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } SGPCR6;                       /* Slave General Purpose Control Register 6 (QuadSPI/RLE)@baseaddress + 0x610 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t HLP:1;        /* Halt Low Priority */
                  vuint32_t:6;
                vuint32_t HPE7:1;       /* High Priority Enable */
                vuint32_t HPE6:1;       /* High Priority Enable */
                vuint32_t HPE5:1;       /* High Priority Enable */
                vuint32_t HPE4:1;       /* High Priority Enable */
                vuint32_t HPE3:1;       /* High Priority Enable */
                vuint32_t HPE2:1;       /* High Priority Enable */
                vuint32_t HPE1:1;       /* High Priority Enable */
                vuint32_t HPE0:1;       /* High Priority Enable */
                  vuint32_t:6;
                vuint32_t ARB:2;
                vuint32_t:2;
                vuint32_t PCTL:2;
                vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } ASGPCR6;                      /* Alternate Slave General Purpose Control Register 6 (QuadSPI/RLE) @baseaddress + 0x614 */

        int32_t XBAR_reserved_0618[58];	/* 0x0618 - 0x06FF */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t MSTR7:3;    	/* Master 7 Priority - Reserved */
                  vuint32_t:1;
                vuint32_t MSTR6:3;    	/* Master 6 Priority - DCU */
                  vuint32_t:1;
                vuint32_t MSTR5:3;    	/* Master 5 Priority - DCULite */
                  vuint32_t:1;
                vuint32_t MSTR4:3;      /* Master 4 Priority - VIU */
                  vuint32_t:1;
                vuint32_t MSTR3:3;      /* Master 3 Priority - GFX2D/GXG */
                  vuint32_t:1;
                vuint32_t MSTR2:3;      /* Master 2 Priority - eDMA */
                  vuint32_t:1;
                vuint32_t MSTR1:3;      /* Master 1 Priority - e200z4 Core load/store & Nexus port  */
                  vuint32_t:1;
                vuint32_t MSTR0:3;      /* Master 0 Priority - e200z4 core Instruction */
            } B;
        } MPR7;                         /* Master Priority Register for Slave port 7 (Peripherals) @baseaddress + 0x700 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t MSTR7:3;    	/* Master 7 Priority - Reserved */
                  vuint32_t:1;
                vuint32_t MSTR6:3;    	/* Master 6 Priority - DCU */
                  vuint32_t:1;
                vuint32_t MSTR5:3;    	/* Master 5 Priority - DCULite */
                  vuint32_t:1;
                vuint32_t MSTR4:3;      /* Master 4 Priority - VIU */
                  vuint32_t:1;
                vuint32_t MSTR3:3;      /* Master 3 Priority - GFX2D/GXG */
                  vuint32_t:1;
                vuint32_t MSTR2:3;      /* Master 2 Priority - eDMA */
                  vuint32_t:1;
                vuint32_t MSTR1:3;      /* Master 1 Priority - e200z4 Core load/store & Nexus port  */
                  vuint32_t:1;
                vuint32_t MSTR0:3;      /* Master 0 Priority - e200z4 core Instruction */
            } B;
        } AMPR7;                        /* Master Priority Register for Slave port 7 (Peripherals) @baseaddress + 0x704 */

        int32_t XBAR_reserved_0708[2];	/* 0x0708 - 0x070F */

        union {
            vuint32_t R;
            struct {
                vuint32_t RO:1;
                vuint32_t HLP:1;        /* Halt Low Priority */
                  vuint32_t:6;
                vuint32_t HPE7:1;       /* High Priority Enable */
                vuint32_t HPE6:1;       /* High Priority Enable */
                vuint32_t HPE5:1;       /* High Priority Enable */
                vuint32_t HPE4:1;       /* High Priority Enable */
                vuint32_t HPE3:1;       /* High Priority Enable */
                vuint32_t HPE2:1;       /* High Priority Enable */
                vuint32_t HPE1:1;       /* High Priority Enable */
                vuint32_t HPE0:1;       /* High Priority Enable */
                  vuint32_t:6;
                vuint32_t ARB:2;
                vuint32_t:2;
                vuint32_t PCTL:2;
                vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } SGPCR7;                       /* Slave General Purpose Control Register 7 (Peripherals) @baseaddress + 0x710 */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:1;
                vuint32_t HLP:1;        /* Halt Low Priority */
                  vuint32_t:6;
                vuint32_t HPE7:1;       /* High Priority Enable */
                vuint32_t HPE6:1;       /* High Priority Enable */
                vuint32_t HPE5:1;       /* High Priority Enable */
                vuint32_t HPE4:1;       /* High Priority Enable */
                vuint32_t HPE3:1;       /* High Priority Enable */
                vuint32_t HPE2:1;       /* High Priority Enable */
                vuint32_t HPE1:1;       /* High Priority Enable */
                vuint32_t HPE0:1;       /* High Priority Enable */
                  vuint32_t:6;
                vuint32_t ARB:2;
                vuint32_t:2;
                vuint32_t PCTL:2;
                vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } ASGPCR7;                      /* Alternate Slave General Purpose Control Register 7 (Peripherals) @baseaddress + 0x714 */

        int32_t XBAR_reserved_0718[58];	/* 0x0714 - 0x07FF */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:29;
                vuint32_t AULB:3;
            } B;
        } MGPCR0;                       /* General Purpose Control Register for Master port 0 @baseaddress + 0x800 */

        int32_t XBAR_reserved_0804[63];	/* 0x0804 - 0x08FF */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:29;
                vuint32_t AULB:3;
            } B;
        } MGPCR1;                       /* General Purpose Control Register for Master port 1 @baseaddress + 0x900 */

        int32_t XBAR_reserved_0904[63];	/* 0x0904 - 0x09FF */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:29;
                vuint32_t AULB:3;
            } B;
        } MGPCR2;                       /* General Purpose Control Register for Master port 2 @baseaddress + 0xA00 */

        int32_t XBAR_reserved_0A04[63];	/* 0x0A04 - 0x0AFF */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:29;
                vuint32_t AULB:3;
            } B;
        } MGPCR3;                       /* General Purpose Control Register for Master port 3 @baseaddress + 0xB00 */

        int32_t XBAR_reserved_0B04[63];	/* 0x0B04 - 0x0BFF */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:29;
                vuint32_t AULB:3;
            } B;
        } MGPCR4;                       /* General Purpose Control Register for Master port 4 @baseaddress + 0xC00 */

        int32_t XBAR_reserved_0C04[63];	/* 0x0C04 - 0x0CFF */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:29;
                vuint32_t AULB:3;
            } B;
        } MGPCR5;                       /* General Purpose Control Register for Master port D @baseaddress + 0xD00 */

        int32_t XBAR_reserved_0D04[63];	/* 0x0D04 - 0x0DFF */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:29;
                vuint32_t AULB:3;
            } B;
        } MGPCR6;                       /* General Purpose Control Register for Master port 6 @baseaddress + 0xE00 */

        int32_t XBAR_reserved_0E04[63];	/* 0x0E04 - 0x0EFF */

        union {
            vuint32_t R;
            struct {
                  vuint32_t:29;
                vuint32_t AULB:3;
            } B;
        } MGPCR7;                       /* General Purpose Control Register for Master port 7 @baseaddress + 0xF00 */

        int32_t XBAR_reserved_0F04[63];	/* 0x0F04 - 0x0FFF */

    };

/****************************************************************** 
| defines and macros (scope: module-local) 
|-----------------------------------------------------------------*/
/* Define instances of modules */
#define CFLASH0         (*(volatile struct CFLASH_tag *)        0xC3F88000UL)
#define SIU             (*(volatile struct SIU_tag *)           0xC3F90000UL)
#define WKUP            (*(volatile struct WKUP_tag *)          0xC3F94000UL)
#define EMIOS_0         (*(volatile struct EMIOS_tag *)         0xC3FA0000UL)
#define EMIOS_1         (*(volatile struct EMIOS_tag *)         0xC3FA4000UL)
#define SSCM            (*(volatile struct SSCM_tag *)          0xC3FD8000UL)
#define ME              (*(volatile struct ME_tag *)            0xC3FDC000UL)
#define CGM             (*(volatile struct CGM_tag *)           0xC3FE0000UL)
#define RGM             (*(volatile struct RGM_tag *)           0xC3FE4000UL)
#define PCU             (*(volatile struct PCU_tag *)           0xC3FE8000UL)
#define RTC             (*(volatile struct RTC_tag *)           0xC3FEC000UL)
#define PIT             (*(volatile struct PIT_tag *)           0xC3FF0000UL)
#define ADC_0           (*(volatile struct ADC_tag *)           0xFFE00000UL)
#define RLE             (*(volatile struct RLE_tag *)           0xFFE14000UL)
#define VIU             (*(volatile struct VIU_tag *)           0xFFE24000UL)
#define DRAMC           (*(volatile struct DRAMC_tag *)         0xFFE28000UL)
#define DRAMPM          (*(volatile struct DRAMPM_tag *)        0xFFE28080UL)
#define I2C_0           (*(volatile struct I2C_tag *)           0xFFE30000UL)
#define I2C_1           (*(volatile struct I2C_tag *)           0xFFE34000UL)
#define I2C_2           (*(volatile struct I2C_tag *)           0xFFE38000UL)
#define I2C_3           (*(volatile struct I2C_tag *)           0xFFE3C000UL)
/*
#define LINFLEX_0       (*(volatile struct LINFLEX_MS_tag *)    0xFFE40000UL)
#define LINFLEX_1       (*(volatile struct LINFLEX_M_tag *)     0xFFE44000UL)
#define LINFLEX_2       (*(volatile struct LINFLEX_M_tag *)     0xFFE48000UL)
#define LINFLEX_3       (*(volatile struct LINFLEX_M_tag *)     0xFFE4C000UL)
LINFLEX_MS_tag and LINFLEX_M_tag types can be considered same since Slave mode, UART and DMA are not supported for Linflex
i.e Memory map for IFCR, GCR, UARTPTO, UARTCTO, DMATXE, DMARXE are never used
*/
#define LINFLEX_0       (*(volatile struct LINFLEX_tag *)       0xFFE40000UL)
#define LINFLEX_1       (*(volatile struct LINFLEX_tag *)       0xFFE44000UL)
#define LINFLEX_2       (*(volatile struct LINFLEX_tag *)       0xFFE48000UL)
#define LINFLEX_3       (*(volatile struct LINFLEX_tag *)       0xFFE4C000UL)
#define GFX2D           (*(volatile struct GFX2D_tag *)         0xFFE50000UL)
#define GXG             (*(volatile struct GXG_tag *)           0xFFE54000UL)
#define DCULITE         (*(volatile struct DCULITE_tag *)       0xFFE58000UL)
#define DCU             (*(volatile struct DCU_tag *)           0xFFE5C000UL)
#define SMC             (*(volatile struct SMC_tag *)           0xFFE60000UL)
#define SSD_0           (*(volatile struct SSD_tag *)           0xFFE61000UL)
#define SSD_1           (*(volatile struct SSD_tag *)           0xFFE61800UL)
#define SSD_2           (*(volatile struct SSD_tag *)           0xFFE62000UL)
#define SSD_3           (*(volatile struct SSD_tag *)           0xFFE62800UL)
#define SSD_4           (*(volatile struct SSD_tag *)           0xFFE63000UL)
#define SSD_5           (*(volatile struct SSD_tag *)           0xFFE63800UL)
#define CANSP           (*(volatile struct CANSP_tag *)         0xFFE70000UL)
#define SGM             (*(volatile struct SGM_tag *)           0xFFE78000UL)
#define TCON            (*(volatile struct TCON_tag *)          0xFFE7C000UL)
#define XBAR            (*(volatile struct XBAR_tag *)          0xFFF04000UL)
#define GRAMC           (*(volatile struct GRAMC_tag *)         0xFFF0C000UL)
#define MPU             (*(volatile struct MPU_tag *)           0xFFF10000UL)
#define SWT             (*(volatile struct SWT_tag *)           0xFFF38000UL)
#define STM             (*(volatile struct STM_tag *)           0xFFF3C000UL)
#define ECSM            (*(volatile struct ECSM_tag *)          0xFFF40000UL)
#define EDMA            (*(volatile struct EDMA_tag *)          0xFFF44000UL)
#define INTC            (*(volatile struct INTC_tag *)          0xFFF48000UL)
#define DSPI_0          (*(volatile struct DSPI_tag *)          0xFFF90000UL)
#define DSPI_1          (*(volatile struct DSPI_tag *)          0xFFF94000UL)
#define DSPI_2          (*(volatile struct DSPI_tag *)          0xFFF98000UL)
#define QUADSPI_0       (*(volatile struct QUADSPI_tag *)       0xFFFA0000UL)
#define CAN_0           (*(volatile struct FLEXCAN_tag *)       0xFFFC0000UL)
#define CAN_1           (*(volatile struct FLEXCAN_tag *)       0xFFFC4000UL)
#define CAN_2           (*(volatile struct FLEXCAN_tag *)       0xFFFC8000UL)
#define DMAMUX          (*(volatile struct DMAMUX_tag *)        0xFFFDC000UL)

#ifdef __MWERKS__
#pragma pop
#endif

#ifdef  __cplusplus
}
#endif
#endif                                  /* ifdef _JDP_H */
/* End of file */
