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

#ifndef IP_FLEXRAY_H_
#define IP_FLEXRAY_H_


/*
 * INFORMATION:
 *   This file is originally from mpc5644a.h (since it also had types in it).
 *   Some registers updates have been done to support later FlexRay implementations.
 */


/****************************************************************************/
/*                          MODULE : FlexRay                                */
/****************************************************************************/

    typedef union uMVR {
        vuint16_t R;
        struct {
            vuint16_t CHIVER:8; /* CHI Version Number */
            vuint16_t PEVER:8;  /* PE Version Number */
        } B;
    } MVR_t;

    typedef union uMCR {
        vuint16_t R;
        struct {
            vuint16_t MEN:1;
            vuint16_t SBFF:1;                /* System Bus Failure Freeze */
            vuint16_t SCM:1;
            vuint16_t CHB:1;
            vuint16_t CHA:1;
            vuint16_t SFFE:1;
            vuint16_t ECCE:1;
            vuint16_t  :1;                   /* Reserved bit, will not be changed. Application must not write any value different from the reset value. */
            vuint16_t FUM:1;
            vuint16_t FAM:1;
            vuint16_t  :1;
            vuint16_t CLKSEL:1;
            vuint16_t BITRATE:3;
            vuint16_t  :1;

        } B;
    } MCR_t;

    typedef union uSTBSCR {
        vuint16_t R;
        struct {
            vuint16_t WMD:1;    /* write mode */
            vuint16_t STBSSEL:7;        /* strobe signal select */
              vuint16_t:3;
            vuint16_t ENB:1;    /* strobe signal enable */
              vuint16_t:2;
            vuint16_t STBPSEL:2;        /* strobe port select */
        } B;
    } STBSCR_t;
    typedef union uSTBPCR {
        vuint16_t R;
        struct {
            vuint16_t:12;
            vuint16_t STB3EN:1; /* strobe port enable */
            vuint16_t STB2EN:1; /* strobe port enable */
            vuint16_t STB1EN:1; /* strobe port enable */
            vuint16_t STB0EN:1; /* strobe port enable */
        } B;
    } STBPCR_t;

    typedef union uMBDSR {
        vuint16_t R;
        struct {
            vuint16_t:1;
            vuint16_t MBSEG2DS:7;       /* message buffer segment 2 data size */
              vuint16_t:1;
            vuint16_t MBSEG1DS:7;       /* message buffer segment 1 data size */
        } B;
    } MBDSR_t;
    typedef union uMBSSUTR {
        vuint16_t R;
        struct {

            vuint16_t:1;
            vuint16_t LAST_MB_SEG1:7;   /* last message buffer control register for message buffer segment 1 */
              vuint16_t:1;
            vuint16_t LAST_MB_UTIL:7;   /* last message buffer utilized */
        } B;
    } MBSSUTR_t;

    typedef union uPOCR {
        vuint16_t R;
        vuint8_t byte[2];
        struct {
            vuint16_t WME:1;    /* write mode external correction command */
              vuint16_t:3;
            vuint16_t EOC_AP:2; /* external offset correction application */
            vuint16_t ERC_AP:2; /* external rate correction application */
            vuint16_t BSY:1;    /* command write busy / write mode command */
              vuint16_t:3;
            vuint16_t POCCMD:4; /* protocol command */
        } B;
    } POCR_t;
/* protocol commands */
    typedef union uGIFER {
        vuint16_t R;
        struct {
            vuint16_t MIF:1;    /* module interrupt flag */
            vuint16_t PRIF:1;   /* protocol interrupt flag */
            vuint16_t CHIF:1;   /* CHI interrupt flag */
            vuint16_t WKUPIF:1; /* wakeup interrupt flag */
            vuint16_t FNEBIF:1; /* receive FIFO channel B not empty interrupt flag */
            vuint16_t FNEAIF:1; /* receive FIFO channel A not empty interrupt flag */
            vuint16_t RBIF:1;   /* receive message buffer interrupt flag */
            vuint16_t TBIF:1;   /* transmit buffer interrupt flag */
            vuint16_t MIE:1;    /* module interrupt enable */
            vuint16_t PRIE:1;   /* protocol interrupt enable */
            vuint16_t CHIE:1;   /* CHI interrupt enable */
            vuint16_t WKUPIE:1; /* wakeup interrupt enable */
            vuint16_t FNEBIE:1; /* receive FIFO channel B not empty interrupt enable */
            vuint16_t FNEAIE:1; /* receive FIFO channel A not empty interrupt enable */
            vuint16_t RBIE:1;   /* receive message buffer interrupt enable */
            vuint16_t TBIE:1;   /* transmit buffer interrupt enable */
        } B;
    } GIFER_t;
    typedef union uPIFR0 {
        vuint16_t R;
        struct {
            vuint16_t FATLIF:1; /* fatal protocol error interrupt flag */
            vuint16_t INTLIF:1; /* internal protocol error interrupt flag */
            vuint16_t ILCFIF:1; /* illegal protocol configuration flag */
            vuint16_t CSAIF:1;  /* cold start abort interrupt flag */
            vuint16_t MRCIF:1;  /* missing rate correctio interrupt flag */
            vuint16_t MOCIF:1;  /* missing offset correctio interrupt flag */
            vuint16_t CCLIF:1;  /* clock correction limit reached interrupt flag */
            vuint16_t MXSIF:1;  /* max sync frames detected interrupt flag */
            vuint16_t MTXIF:1;  /* media access test symbol received flag */
            vuint16_t LTXBIF:1; /* pdLatestTx violation on channel B interrupt flag */
            vuint16_t LTXAIF:1; /* pdLatestTx violation on channel A interrupt flag */
            vuint16_t TBVBIF:1; /* Transmission across boundary on channel B Interrupt Flag */
            vuint16_t TBVAIF:1; /* Transmission across boundary on channel A Interrupt Flag */
            vuint16_t TI2IF:1;  /* timer 2 expired interrupt flag */
            vuint16_t TI1IF:1;  /* timer 1 expired interrupt flag */
            vuint16_t CYSIF:1;  /* cycle start interrupt flag */
        } B;
    } PIFR0_t;
    typedef union uPIFR1 {
        vuint16_t R;
        struct {
            vuint16_t EMCIF:1;  /* error mode changed interrupt flag */
            vuint16_t IPCIF:1;  /* illegal protocol command interrupt flag */
            vuint16_t PECFIF:1; /* protocol engine communication failure interrupt flag */
            vuint16_t PSCIF:1;  /* Protocol State Changed Interrupt Flag */
            vuint16_t SSI3IF:1; /* slot status counter incremented interrupt flag */
            vuint16_t SSI2IF:1; /* slot status counter incremented interrupt flag */
            vuint16_t SSI1IF:1; /* slot status counter incremented interrupt flag */
            vuint16_t SSI0IF:1; /* slot status counter incremented interrupt flag */
              vuint16_t:2;
            vuint16_t EVTIF:1;  /* even cycle table written interrupt flag */
            vuint16_t ODTIF:1;  /* odd cycle table written interrupt flag */
              vuint16_t:4;
        } B;
    } PIFR1_t;
    typedef union uPIER0 {
        vuint16_t R;
        struct {
            vuint16_t FATLIE:1; /* fatal protocol error interrupt enable */
            vuint16_t INTLIE:1; /* internal protocol error interrupt interrupt enable  */
            vuint16_t ILCFIE:1; /* illegal protocol configuration interrupt enable */
            vuint16_t CSAIE:1;  /* cold start abort interrupt enable */
            vuint16_t MRCIE:1;  /* missing rate correctio interrupt enable */
            vuint16_t MOCIE:1;  /* missing offset correctio interrupt enable */
            vuint16_t CCLIE:1;  /* clock correction limit reached interrupt enable */
            vuint16_t MXSIE:1;  /* max sync frames detected interrupt enable */
            vuint16_t MTXIE:1;  /* media access test symbol received interrupt enable */
            vuint16_t LTXBIE:1; /* pdLatestTx violation on channel B interrupt enable */
            vuint16_t LTXAIE:1; /* pdLatestTx violation on channel A interrupt enable */
            vuint16_t TBVBIE:1; /* Transmission across boundary on channel B Interrupt enable */
            vuint16_t TBVAIE:1; /* Transmission across boundary on channel A Interrupt enable */
            vuint16_t TI2IE:1;  /* timer 2 expired interrupt enable */
            vuint16_t TI1IE:1;  /* timer 1 expired interrupt enable */
            vuint16_t CYSIE:1;  /* cycle start interrupt enable */
        } B;
    } PIER0_t;
    typedef union uPIER1 {
        vuint16_t R;
        struct {
            vuint16_t EMCIE:1;  /* error mode changed interrupt enable */
            vuint16_t IPCIE:1;  /* illegal protocol command interrupt enable */
            vuint16_t PECFIE:1; /* protocol engine communication failure interrupt enable */
            vuint16_t PSCIE:1;  /* Protocol State Changed Interrupt enable */
            vuint16_t SSI3IE:1; /* slot status counter incremented interrupt enable */
            vuint16_t SSI2IE:1; /* slot status counter incremented interrupt enable */
            vuint16_t SSI1IE:1; /* slot status counter incremented interrupt enable */
            vuint16_t SSI0IE:1; /* slot status counter incremented interrupt enable */
              vuint16_t:2;
            vuint16_t EVTIE:1;  /* even cycle table written interrupt enable */
            vuint16_t ODTIE:1;  /* odd cycle table written interrupt enable */
              vuint16_t:4;
        } B;
    } PIER1_t;
    typedef union uCHIERFR {
        vuint16_t R;
        struct {
            vuint16_t FRLBEF:1; /* flame lost channel B error flag */
            vuint16_t FRLAEF:1; /* frame lost channel A error flag */
            vuint16_t PCMIEF:1; /* command ignored error flag */
            vuint16_t FOVBEF:1; /* receive FIFO overrun channel B error flag */
            vuint16_t FOVAEF:1; /* receive FIFO overrun channel A error flag */
            vuint16_t MSBEF:1;  /* message buffer search error flag */
            vuint16_t MBUEF:1;  /* message buffer utilization error flag */
            vuint16_t LCKEF:1;  /* lock error flag */
            vuint16_t DBLEF:1;  /* double transmit message buffer lock error flag */
            vuint16_t SBCFEF:1; /* system bus communication failure error flag */
            vuint16_t FIDEF:1;  /* frame ID error flag */
            vuint16_t DPLEF:1;  /* dynamic payload length error flag */
            vuint16_t SPLEF:1;  /* static payload length error flag */
            vuint16_t NMLEF:1;  /* network management length error flag */
            vuint16_t NMFEF:1;  /* network management frame error flag */
            vuint16_t ILSAEF:1; /* illegal access error flag */
        } B;
    } CHIERFR_t;
    typedef union uMBIVEC {
        vuint16_t R;
        struct {

            vuint16_t:1;
            vuint16_t TBIVEC:7; /* transmit buffer interrupt vector */
              vuint16_t:1;
            vuint16_t RBIVEC:7; /* receive buffer interrupt vector */
        } B;
    } MBIVEC_t;

    typedef union uPSR0 {
        vuint16_t R;
        struct {
            vuint16_t ERRMODE:2;        /* error mode */
            vuint16_t SLOTMODE:2;       /* slot mode */
              vuint16_t:1;
            vuint16_t PROTSTATE:3;      /* protocol state */
            vuint16_t STARTUPSTATE:4;     /* protocol sub state */
              vuint16_t:1;
            vuint16_t WAKEUPSTATUS:3;   /* wakeup status */
        } B;
    } PSR0_t;

/* protocol states */
/* protocol sub-states */
/* wakeup status */
    typedef union uPSR1 {
        vuint16_t R;
        struct {
            vuint16_t CSAA:1;   /* cold start attempt abort flag */
            vuint16_t SCP:1;    /* cold start path */
              vuint16_t:1;
            vuint16_t REMCSAT:5;        /* remanining coldstart attempts */
            vuint16_t CPN:1;    /* cold start noise path */
            vuint16_t HHR:1;    /* host halt request pending */
            vuint16_t FRZ:1;    /* freeze occured */
            vuint16_t APTAC:5;  /* allow passive to active counter */
        } B;
    } PSR1_t;
    typedef union uPSR2 {
        vuint16_t R;
        struct {
            vuint16_t NBVB:1;   /* NIT boundary violation on channel B */
            vuint16_t NSEB:1;   /* NIT syntax error on channel B */
            vuint16_t STCB:1;   /* symbol window transmit conflict on channel B */
            vuint16_t SBVB:1;   /* symbol window boundary violation on channel B */
            vuint16_t SSEB:1;   /* symbol window syntax error on channel B */
            vuint16_t MTB:1;    /* media access test symbol MTS received on channel B */
            vuint16_t NBVA:1;   /* NIT boundary violation on channel A */
            vuint16_t NSEA:1;   /* NIT syntax error on channel A */
            vuint16_t STCA:1;   /* symbol window transmit conflict on channel A */
            vuint16_t SBVA:1;   /* symbol window boundary violation on channel A */
            vuint16_t SSEA:1;   /* symbol window syntax error on channel A */
            vuint16_t MTA:1;    /* media access test symbol MTS received on channel A */
            vuint16_t CLKCORRFAILCNT:4; /* clock correction failed counter */
        } B;
    } PSR2_t;
    typedef union uPSR3 {
        vuint16_t R;
        struct {
            vuint16_t:2;
            vuint16_t WUB:1;    /* wakeup symbol received on channel B */
            vuint16_t ABVB:1;   /* aggregated boundary violation on channel B */
            vuint16_t AACB:1;   /* aggregated additional communication on channel B */
            vuint16_t ACEB:1;   /* aggregated content error on channel B */
            vuint16_t ASEB:1;   /* aggregated syntax error on channel B */
            vuint16_t AVFB:1;   /* aggregated valid frame on channel B */
              vuint16_t:2;
            vuint16_t WUA:1;    /* wakeup symbol received on channel A */
            vuint16_t ABVA:1;   /* aggregated boundary violation on channel A */
            vuint16_t AACA:1;   /* aggregated additional communication on channel A */
            vuint16_t ACEA:1;   /* aggregated content error on channel A */
            vuint16_t ASEA:1;   /* aggregated syntax error on channel A */
            vuint16_t AVFA:1;   /* aggregated valid frame on channel A */
        } B;
    } PSR3_t;
    typedef union uCIFRR {
        vuint16_t R;
        struct {
            vuint16_t:8;
            vuint16_t MIFR:1;   /* module interrupt flag */
            vuint16_t PRIFR:1;  /* protocol interrupt flag */
            vuint16_t CHIFR:1;  /* CHI interrupt flag */
            vuint16_t WUPIFR:1; /* wakeup interrupt flag */
            vuint16_t FNEBIFR:1;        /* receive fifo channel B no empty interrupt flag */
            vuint16_t FNEAIFR:1;        /* receive fifo channel A no empty interrupt flag */
            vuint16_t RBIFR:1;  /* receive message buffer interrupt flag */
            vuint16_t TBIFR:1;  /* transmit buffer interrupt flag */
        } B;
    } CIFRR_t;
    typedef union uSFCNTR {
        vuint16_t R;
        struct {
            vuint16_t SFEVB:4;  /* sync frames channel B, even cycle */
            vuint16_t SFEVA:4;  /* sync frames channel A, even cycle */
            vuint16_t SFODB:4;  /* sync frames channel B, odd cycle */
            vuint16_t SFODA:4;  /* sync frames channel A, odd cycle */
        } B;
    } SFCNTR_t;

    typedef union uSFTCCSR {
        vuint16_t R;
        struct {
            vuint16_t ELKT:1;   /* even cycle tables lock and unlock trigger */
            vuint16_t OLKT:1;   /* odd cycle tables lock and unlock trigger */
            vuint16_t CYCNUM:6; /* cycle number */
            vuint16_t ELKS:1;   /* even cycle tables lock status */
            vuint16_t OLKS:1;   /* odd cycle tables lock status */
            vuint16_t EVAL:1;   /* even cycle tables valid */
            vuint16_t OVAL:1;   /* odd cycle tables valid */
              vuint16_t:1;
            vuint16_t OPT:1;    /*one pair trigger */
            vuint16_t SDVEN:1;  /* sync frame deviation table enable */
            vuint16_t SIDEN:1;  /* sync frame ID table enable */
        } B;
    } SFTCCSR_t;
    typedef union uSFIDRFR {
        vuint16_t R;
        struct {
            vuint16_t:6;
            vuint16_t SYNFRID:10;       /* sync frame rejection ID */
        } B;
    } SFIDRFR_t;

    typedef union uTICCR {
        vuint16_t R;
        struct {
            vuint16_t:2;
            vuint16_t T2CFG:1;  /* timer 2 configuration */
            vuint16_t T2REP:1;  /* timer 2 repetitive mode */
              vuint16_t:1;
            vuint16_t T2SP:1;   /* timer 2 stop */
            vuint16_t T2TR:1;   /* timer 2 trigger */
            vuint16_t T2ST:1;   /* timer 2 state */
              vuint16_t:3;
            vuint16_t T1REP:1;  /* timer 1 repetitive mode */
              vuint16_t:1;
            vuint16_t T1SP:1;   /* timer 1 stop */
            vuint16_t T1TR:1;   /* timer 1 trigger */
            vuint16_t T1ST:1;   /* timer 1 state */

        } B;
    } TICCR_t;
    typedef union uTI1CYSR {
        vuint16_t R;
        struct {
            vuint16_t:2;
            vuint16_t TI1CYCVAL:6;      /* timer 1 cycle filter value */
              vuint16_t:2;
            vuint16_t TI1CYCMSK:6;      /* timer 1 cycle filter mask */

        } B;
    } TI1CYSR_t;

    typedef union uSSSR {
        vuint16_t R;
        struct {
            vuint16_t WMD:1;    /* write mode */
              vuint16_t:1;
            vuint16_t SEL:2;    /* static slot number */
              vuint16_t:1;
            vuint16_t SLOTNUMBER:11;    /* selector */
        } B;
    } SSSR_t;

    typedef union uSSCCR {
        vuint16_t R;
        struct {
            vuint16_t WMD:1;    /* write mode */
              vuint16_t:1;
            vuint16_t SEL:2;    /* selector */
              vuint16_t:1;
            vuint16_t CNTCFG:2; /* counter configuration */
            vuint16_t MCY:1;    /* multi cycle selection */
            vuint16_t VFR:1;    /* valid frame selection */
            vuint16_t SYF:1;    /* sync frame selection */
            vuint16_t NUF:1;    /* null frame selection  */
            vuint16_t SUF:1;    /* startup frame selection */
            vuint16_t STATUSMASK:4;     /* slot status mask */
        } B;
    } SSCCR_t;
    typedef union uSSR {
        vuint16_t R;
        struct {
            vuint16_t VFB:1;    /* valid frame on channel B */
            vuint16_t SYB:1;    /* valid sync frame on channel B */
            vuint16_t NFB:1;    /* valid null frame on channel B */
            vuint16_t SUB:1;    /* valid startup frame on channel B */
            vuint16_t SEB:1;    /* syntax error on channel B */
            vuint16_t CEB:1;    /* content error on channel B */
            vuint16_t BVB:1;    /* boundary violation on channel B */
            vuint16_t TCB:1;    /* tx conflict on channel B */
            vuint16_t VFA:1;    /* valid frame on channel A */
            vuint16_t SYA:1;    /* valid sync frame on channel A */
            vuint16_t NFA:1;    /* valid null frame on channel A */
            vuint16_t SUA:1;    /* valid startup frame on channel A */
            vuint16_t SEA:1;    /* syntax error on channel A */
            vuint16_t CEA:1;    /* content error on channel A */
            vuint16_t BVA:1;    /* boundary violation on channel A */
            vuint16_t TCA:1;    /* tx conflict on channel A */
        } B;
    } SSR_t;
    typedef union uMTSCFR {
        vuint16_t R;
        struct {
            vuint16_t MTE:1;    /* media access test symbol transmission enable */
              vuint16_t:1;
            vuint16_t CYCCNTMSK:6;      /* cycle counter mask */
              vuint16_t:2;
            vuint16_t CYCCNTVAL:6;      /* cycle counter value */
        } B;
    } MTSCFR_t;
    typedef union uRSBIR {
        vuint16_t R;
        struct {
            vuint16_t WMD:1;    /* write mode */
              vuint16_t:1;
            vuint16_t SEL:2;    /* selector */
              vuint16_t:4;
            vuint16_t RSBIDX:8; /* receive shadow buffer index */
        } B;
    } RSBIR_t;
    typedef union uRFDSR {
        vuint16_t R;
        struct {
            vuint16_t FIFODEPTH:8;      /* fifo depth */
              vuint16_t:1;
            vuint16_t ENTRYSIZE:7;      /* entry size */
        } B;
    } RFDSR_t;

    typedef union uRFRFCFR {
        vuint16_t R;
        struct {
            vuint16_t WMD:1;    /* write mode */
            vuint16_t IBD:1;    /* interval boundary */
            vuint16_t SEL:2;    /* filter number */
              vuint16_t:1;
            vuint16_t SID:11;   /* slot ID */
        } B;
    } RFRFCFR_t;

    typedef union uRFRFCTR {
        vuint16_t R;
        struct {
            vuint16_t:4;
            vuint16_t F3MD:1;   /* filter mode */
            vuint16_t F2MD:1;   /* filter mode */
            vuint16_t F1MD:1;   /* filter mode */
            vuint16_t F0MD:1;   /* filter mode */
              vuint16_t:4;
            vuint16_t F3EN:1;   /* filter enable */
            vuint16_t F2EN:1;   /* filter enable */
            vuint16_t F1EN:1;   /* filter enable */
            vuint16_t F0EN:1;   /* filter enable */
        } B;
    } RFRFCTR_t;
    typedef union uPCR0 {
        vuint16_t R;
        struct {
            vuint16_t ACTION_POINT_OFFSET:6;
            vuint16_t STATIC_SLOT_LENGTH:10;
        } B;
    } PCR0_t;

    typedef union uPCR1 {
        vuint16_t R;
        struct {
            vuint16_t:2;
            vuint16_t MACRO_AFTER_FIRST_STATIC_SLOT:14;
        } B;
    } PCR1_t;

    typedef union uPCR2 {
        vuint16_t R;
        struct {
            vuint16_t MINISLOT_AFTER_ACTION_POINT:6;
            vuint16_t NUMBER_OF_STATIC_SLOTS:10;
        } B;
    } PCR2_t;

    typedef union uPCR3 {
        vuint16_t R;
        struct {
            vuint16_t WAKEUP_SYMBOL_RX_LOW:6;
            vuint16_t MINISLOT_ACTION_POINT_OFFSET:5;
            vuint16_t COLDSTART_ATTEMPTS:5;
        } B;
    } PCR3_t;

    typedef union uPCR4 {
        vuint16_t R;
        struct {
            vuint16_t CAS_RX_LOW_MAX:7;
            vuint16_t WAKEUP_SYMBOL_RX_WINDOW:9;
        } B;
    } PCR4_t;

    typedef union uPCR5 {
        vuint16_t R;
        struct {
            vuint16_t TSS_TRANSMITTER:4;
            vuint16_t WAKEUP_SYMBOL_TX_LOW:6;
            vuint16_t WAKEUP_SYMBOL_RX_IDLE:6;
        } B;
    } PCR5_t;

    typedef union uPCR6 {
        vuint16_t R;
        struct {
            vuint16_t:1;
            vuint16_t SYMBOL_WINDOW_AFTER_ACTION_POINT:8;
            vuint16_t MACRO_INITIAL_OFFSET_A:7;
        } B;
    } PCR6_t;

    typedef union uPCR7 {
        vuint16_t R;
        struct {
            vuint16_t DECODING_CORRECTION_B:9;
            vuint16_t MICRO_PER_MACRO_NOM_HALF:7;
        } B;
    } PCR7_t;

    typedef union uPCR8 {
        vuint16_t R;
        struct {
            vuint16_t MAX_WITHOUT_CLOCK_CORRECTION_FATAL:4;
            vuint16_t MAX_WITHOUT_CLOCK_CORRECTION_PASSIVE:4;
            vuint16_t WAKEUP_SYMBOL_TX_IDLE:8;
        } B;
    } PCR8_t;

    typedef union uPCR9 {
        vuint16_t R;
        struct {
            vuint16_t MINISLOT_EXISTS:1;
            vuint16_t SYMBOL_WINDOW_EXISTS:1;
            vuint16_t OFFSET_CORRECTION_OUT:14;
        } B;
    } PCR9_t;

    typedef union uPCR10 {
        vuint16_t R;
        struct {
            vuint16_t SINGLE_SLOT_ENABLED:1;
            vuint16_t WAKEUP_CHANNEL:1;
            vuint16_t MACRO_PER_CYCLE:14;
        } B;
    } PCR10_t;

    typedef union uPCR11 {
        vuint16_t R;
        struct {
            vuint16_t KEY_SLOT_USED_FOR_STARTUP:1;
            vuint16_t KEY_SLOT_USED_FOR_SYNC:1;
            vuint16_t OFFSET_CORRECTION_START:14;
        } B;
    } PCR11_t;

    typedef union uPCR12 {
        vuint16_t R;
        struct {
            vuint16_t ALLOW_PASSIVE_TO_ACTIVE:5;
            vuint16_t KEY_SLOT_HEADER_CRC:11;
        } B;
    } PCR12_t;

    typedef union uPCR13 {
        vuint16_t R;
        struct {
            vuint16_t FIRST_MINISLOT_ACTION_POINT_OFFSET:6;
            vuint16_t STATIC_SLOT_AFTER_ACTION_POINT:10;
        } B;
    } PCR13_t;

    typedef union uPCR14 {
        vuint16_t R;
        struct {
            vuint16_t RATE_CORRECTION_OUT:11;
            vuint16_t LISTEN_TIMEOUT_H:5;
        } B;
    } PCR14_t;

    typedef union uPCR15 {
        vuint16_t R;
        struct {
            vuint16_t LISTEN_TIMEOUT_L:16;
        } B;
    } PCR15_t;

    typedef union uPCR16 {
        vuint16_t R;
        struct {
            vuint16_t MACRO_INITIAL_OFFSET_B:7;
            vuint16_t NOISE_LISTEN_TIMEOUT_H:9;
        } B;
    } PCR16_t;

    typedef union uPCR17 {
        vuint16_t R;
        struct {
            vuint16_t NOISE_LISTEN_TIMEOUT_L:16;
        } B;
    } PCR17_t;

    typedef union uPCR18 {
        vuint16_t R;
        struct {
            vuint16_t WAKEUP_PATTERN:6;
            vuint16_t KEY_SLOT_ID:10;
        } B;
    } PCR18_t;

    typedef union uPCR19 {
        vuint16_t R;
        struct {
            vuint16_t DECODING_CORRECTION_A:9;
            vuint16_t PAYLOAD_LENGTH_STATIC:7;
        } B;
    } PCR19_t;

    typedef union uPCR20 {
        vuint16_t R;
        struct {
            vuint16_t MICRO_INITIAL_OFFSET_B:8;
            vuint16_t MICRO_INITIAL_OFFSET_A:8;
        } B;
    } PCR20_t;

    typedef union uPCR21 {
        vuint16_t R;
        struct {
            vuint16_t EXTERN_RATE_CORRECTION:3;
            vuint16_t LATEST_TX:13;
        } B;
    } PCR21_t;

    typedef union uPCR22 {
        vuint16_t R;
        struct {
            vuint16_t:1;
            vuint16_t COMP_ACCEPTED_STARTUP_RANGE_A:11;
            vuint16_t MICRO_PER_CYCLE_H:4;
        } B;
    } PCR22_t;

    typedef union uPCR23 {
        vuint16_t R;
        struct {
            vuint16_t micro_per_cycle_l:16;
        } B;
    } PCR23_t;

    typedef union uPCR24 {
        vuint16_t R;
        struct {
            vuint16_t CLUSTER_DRIFT_DAMPING:5;
            vuint16_t MAX_PAYLOAD_LENGTH_DYNAMIC:7;
            vuint16_t MICRO_PER_CYCLE_MIN_H:4;
        } B;
    } PCR24_t;

    typedef union uPCR25 {
        vuint16_t R;
        struct {
            vuint16_t MICRO_PER_CYCLE_MIN_L:16;
        } B;
    } PCR25_t;

    typedef union uPCR26 {
        vuint16_t R;
        struct {
            vuint16_t ALLOW_HALT_DUE_TO_CLOCK:1;
            vuint16_t COMP_ACCEPTED_STARTUP_RANGE_B:11;
            vuint16_t MICRO_PER_CYCLE_MAX_H:4;
        } B;
    } PCR26_t;

    typedef union uPCR27 {
        vuint16_t R;
        struct {
            vuint16_t MICRO_PER_CYCLE_MAX_L:16;
        } B;
    } PCR27_t;

    typedef union uPCR28 {
        vuint16_t R;
        struct {
            vuint16_t DYNAMIC_SLOT_IDLE_PHASE:2;
            vuint16_t MACRO_AFTER_OFFSET_CORRECTION:14;
        } B;
    } PCR28_t;

    typedef union uPCR29 {
        vuint16_t R;
        struct {
            vuint16_t EXTERN_OFFSET_CORRECTION:3;
            vuint16_t MINISLOTS_MAX:13;
        } B;
    } PCR29_t;

    typedef union uPCR30 {
        vuint16_t R;
        struct {
            vuint16_t:12;
            vuint16_t SYNC_NODE_MAX:4;
        } B;
    } PCR30_t;

    typedef struct uMSG_BUFF_CCS {
        union {
            vuint16_t R;
            struct {
                vuint16_t:1;
                vuint16_t MCM:1;        /* message buffer commit mode */
                vuint16_t MBT:1;        /* message buffer type */
                vuint16_t MTD:1;        /* message buffer direction */
                vuint16_t CMT:1;        /* commit for transmission */
                vuint16_t EDT:1;        /* enable / disable trigger */
                vuint16_t LCKT:1;       /* lock request trigger */
                vuint16_t MBIE:1;       /* message buffer interrupt enable */
                  vuint16_t:3;
                vuint16_t DUP:1;        /* data updated  */
                vuint16_t DVAL:1;       /* data valid */
                vuint16_t EDS:1;        /* lock status */
                vuint16_t LCKS:1;       /* enable / disable status */
                vuint16_t MBIF:1;       /* message buffer interrupt flag */
            } B;
        } MBCCSR;
        union {
            vuint16_t R;
            struct {
                vuint16_t MTM:1;        /* message buffer transmission mode */
                vuint16_t CHNLA:1;      /* channel assignement */
                vuint16_t CHNLB:1;      /* channel assignement */
                vuint16_t CCFE:1;       /* cycle counter filter enable */
                vuint16_t CCFMSK:6;     /* cycle counter filter mask */
                vuint16_t CCFVAL:6;     /* cycle counter filter value */
            } B;
        } MBCCFR;
        union {
            vuint16_t R;
            struct {
                vuint16_t:5;
                vuint16_t FID:11;       /* frame ID */
            } B;
        } MBFIDR;
        union {
            vuint16_t R;
            struct {
                vuint16_t:8;
                vuint16_t MBIDX:8;      /* message buffer index */
            } B;
        } MBIDXR;
    } MSG_BUFF_CCS_t;
    typedef union uSYSBADHR {
        vuint16_t R;
    } SYSBADHR_t;
    typedef union uSYSBADLR {
        vuint16_t R;
    } SYSBADLR_t;
    typedef union uPDAR {
        vuint16_t R;
    } PDAR_t;
    typedef union uCASERCR {
        vuint16_t R;
    } CASERCR_t;
    typedef union uCBSERCR {
        vuint16_t R;
    } CBSERCR_t;
    typedef union uCYCTR {
        vuint16_t R;
    } CYCTR_t;
    typedef union uMTCTR {
        vuint16_t R;
    } MTCTR_t;
    typedef union uSLTCTAR {
        vuint16_t R;
    } SLTCTAR_t;
    typedef union uSLTCTBR {
        vuint16_t R;
    } SLTCTBR_t;
    typedef union uRTCORVR {
        vuint16_t R;
    } RTCORVR_t;
    typedef union uOFCORVR {
        vuint16_t R;
    } OFCORVR_t;
    typedef union uSFTOR {
        vuint16_t R;
    } SFTOR_t;
    typedef union uSFIDAFVR {
        vuint16_t R;
    } SFIDAFVR_t;
    typedef union uSFIDAFMR {
        vuint16_t R;
    } SFIDAFMR_t;
    typedef union uNMVR {
        vuint16_t R;
    } NMVR_t;
    typedef union uNMVLR {
        vuint16_t R;
    } NMVLR_t;
    typedef union uT1MTOR {
        vuint16_t R;
    } T1MTOR_t;

    typedef union uTI2CR0 {
        vuint16_t R;
        struct {
            vuint16_t:2;
            vuint16_t TI2CYCVAL:6;      /* timer 1 cycle filter value */
              vuint16_t:2;
            vuint16_t TI2CYCMSK:6;      /* timer 1 cycle filter mask */

        } B;
    } TI2CR0_t;
    typedef union uTI2CR1 {
        vuint16_t R;
    } TI2CR1_t;
    typedef union uSSCR {
        vuint16_t R;
    } SSCR_t;
    typedef union uRFSR {
        vuint16_t R;
    } RFSR_t;
    typedef union uRFSIR {
        vuint16_t R;
    } RFSIR_t;
    typedef union uRFARIR {
        vuint16_t R;
    } RFARIR_t;
    typedef union uRFBRIR {
        vuint16_t R;
    } RFBRIR_t;
    typedef union uRFMIDAFVR {
        vuint16_t R;
    } RFMIDAFVR_t;
    typedef union uRFMIAFMR {
        vuint16_t R;
    } RFMIAFMR_t;
    typedef union uRFFIDRFVR {
        vuint16_t R;
    } RFFIDRFVR_t;
    typedef union uRFFIDRFMR {
        vuint16_t R;
    } RFFIDRFMR_t;
    typedef union uLDTXSLAR {
        vuint16_t R;
    } LDTXSLAR_t;
    typedef union uLDTXSLBR {
        vuint16_t R;
    } LDTXSLBR_t;

    typedef union uMBDOR { /* Message Buffer Data Field Offset Register */
        vuint16_t R;
        struct {
            vuint16_t MBDO :16;
        } B;
    } MBDOR_t;

    typedef union uLEETR { /* LRAM ECC Error Test Register */
        vuint16_t R;
        struct {
        vuint16_t LEETD:16;
        } B;
    } LEETR_t;

    typedef struct FR_tag {
        volatile MVR_t MVR;     /*module version register *//*0  */
        volatile MCR_t MCR;     /*module configuration register *//*2  */
        volatile SYSBADHR_t SYSBADHR;   /*system memory base address high register *//*4        */
        volatile SYSBADLR_t SYSBADLR;   /*system memory base address low register *//*6         */
        volatile STBSCR_t STBSCR;       /*strobe signal control register *//*8      */
        volatile STBPCR_t STBPCR;       /*strobe port control register *//*A        */
        volatile MBDSR_t MBDSR; /*message buffer data size register *//*C  */
        volatile MBSSUTR_t MBSSUTR;     /*message buffer segment size and utilization register *//*E  */
        vuint16_t reserved3a[1];        /*10 */
        volatile PDAR_t PDAR;   /*PE data register *//*12 */
        volatile POCR_t POCR;   /*Protocol operation control register *//*14 */
        volatile GIFER_t GIFER; /*global interrupt flag and enable register *//*16 */
        volatile PIFR0_t PIFR0; /*protocol interrupt flag register 0 *//*18 */
        volatile PIFR1_t PIFR1; /*protocol interrupt flag register 1 *//*1A */
        volatile PIER0_t PIER0; /*protocol interrupt enable register 0 *//*1C */
        volatile PIER1_t PIER1; /*protocol interrupt enable register 1 *//*1E */
        volatile CHIERFR_t CHIERFR;     /*CHI error flag register *//*20 */
        volatile MBIVEC_t MBIVEC;       /*message buffer interrupt vector register *//*22 */
        volatile CASERCR_t CASERCR;     /*channel A status error counter register *//*24 */
        volatile CBSERCR_t CBSERCR;     /*channel B status error counter register *//*26 */
        volatile PSR0_t PSR0;   /*protocol status register 0 *//*28 */
        volatile PSR1_t PSR1;   /*protocol status register 1 *//*2A */
        volatile PSR2_t PSR2;   /*protocol status register 2 *//*2C */
        volatile PSR3_t PSR3;   /*protocol status register 3 *//*2E */
        volatile MTCTR_t MTCTR; /*macrotick counter register *//*30 */
        volatile CYCTR_t CYCTR; /*cycle counter register *//*32 */
        volatile SLTCTAR_t SLTCTAR;     /*slot counter channel A register *//*34 */
        volatile SLTCTBR_t SLTCTBR;     /*slot counter channel B register *//*36 */
        volatile RTCORVR_t RTCORVR;     /*rate correction value register *//*38 */
        volatile OFCORVR_t OFCORVR;     /*offset correction value register *//*3A */
        volatile CIFRR_t CIFRR; /*combined interrupt flag register *//*3C */
        vuint16_t reserved3[1]; /*3E */
        volatile SFCNTR_t SFCNTR;       /*sync frame counter register *//*40 */
        volatile SFTOR_t SFTOR; /*sync frame table offset register *//*42 */
        volatile SFTCCSR_t SFTCCSR;     /*sync frame table configuration, control, status register *//*44 */
        volatile SFIDRFR_t SFIDRFR;     /*sync frame ID rejection filter register *//*46 */
        volatile SFIDAFVR_t SFIDAFVR;   /*sync frame ID acceptance filter value regiater *//*48 */
        volatile SFIDAFMR_t SFIDAFMR;   /*sync frame ID acceptance filter mask register *//*4A */
        volatile NMVR_t NMVR[6];        /*network management vector registers (12 bytes) *//*4C */
        volatile NMVLR_t NMVLR; /*network management vector length register *//*58 */
        volatile TICCR_t TICCR; /*timer configuration and control register *//*5A */
        volatile TI1CYSR_t TI1CYSR;     /*timer 1 cycle set register *//*5C */
        volatile T1MTOR_t T1MTOR;       /*timer 1 macrotick offset register *//*5E */
        volatile TI2CR0_t TI2CR0;       /*timer 2 configuration register 0 *//*60 */
        volatile TI2CR1_t TI2CR1;       /*timer 2 configuration register 1 *//*62 */
        volatile SSSR_t SSSR;   /*slot status selection register *//*64 */
        volatile SSCCR_t SSCCR; /*slot status counter condition register *//*66 */
        volatile SSR_t SSR[8];  /*slot status registers 0-7 *//*68 */
        volatile SSCR_t SSCR[4];        /*slot status counter registers 0-3 *//*78 */
        volatile MTSCFR_t MTSACFR;      /*mts a config register *//*80 */
        volatile MTSCFR_t MTSBCFR;      /*mts b config register *//*82 */
        volatile RSBIR_t RSBIR; /*receive shadow buffer index register *//*84 */
        volatile RFSR_t RFSR;   /*receive fifo selection register *//*86 */
        volatile RFSIR_t RFSIR; /*receive fifo start index register *//*88 */
        volatile RFDSR_t RFDSR; /*receive fifo depth and size register *//*8A */
        volatile RFARIR_t RFARIR;       /*receive fifo a read index register *//*8C */
        volatile RFBRIR_t RFBRIR;       /*receive fifo b read index register *//*8E */
        volatile RFMIDAFVR_t RFMIDAFVR; /*receive fifo message ID acceptance filter value register *//*90 */
        volatile RFMIAFMR_t RFMIAFMR;   /*receive fifo message ID acceptance filter mask register *//*92 */
        volatile RFFIDRFVR_t RFFIDRFVR; /*receive fifo frame ID rejection filter value register *//*94 */
        volatile RFFIDRFMR_t RFFIDRFMR; /*receive fifo frame ID rejection filter mask register *//*96 */
        volatile RFRFCFR_t RFRFCFR;     /*receive fifo range filter configuration register *//*98 */
        volatile RFRFCTR_t RFRFCTR;     /*receive fifo range filter control register *//*9A */
        volatile LDTXSLAR_t LDTXSLAR;   /*last dynamic transmit slot channel A register *//*9C */
        volatile LDTXSLBR_t LDTXSLBR;   /*last dynamic transmit slot channel B register *//*9E */
        volatile PCR0_t PCR0;   /*protocol configuration register 0 *//*A0 */
        volatile PCR1_t PCR1;   /*protocol configuration register 1 *//*A2 */
        volatile PCR2_t PCR2;   /*protocol configuration register 2 *//*A4 */
        volatile PCR3_t PCR3;   /*protocol configuration register 3 *//*A6 */
        volatile PCR4_t PCR4;   /*protocol configuration register 4 *//*A8 */
        volatile PCR5_t PCR5;   /*protocol configuration register 5 *//*AA */
        volatile PCR6_t PCR6;   /*protocol configuration register 6 *//*AC */
        volatile PCR7_t PCR7;   /*protocol configuration register 7 *//*AE */
        volatile PCR8_t PCR8;   /*protocol configuration register 8 *//*B0 */
        volatile PCR9_t PCR9;   /*protocol configuration register 9 *//*B2 */
        volatile PCR10_t PCR10; /*protocol configuration register 10 *//*B4 */
        volatile PCR11_t PCR11; /*protocol configuration register 11 *//*B6 */
        volatile PCR12_t PCR12; /*protocol configuration register 12 *//*B8 */
        volatile PCR13_t PCR13; /*protocol configuration register 13 *//*BA */
        volatile PCR14_t PCR14; /*protocol configuration register 14 *//*BC */
        volatile PCR15_t PCR15; /*protocol configuration register 15 *//*BE */
        volatile PCR16_t PCR16; /*protocol configuration register 16 *//*C0 */
        volatile PCR17_t PCR17; /*protocol configuration register 17 *//*C2 */
        volatile PCR18_t PCR18; /*protocol configuration register 18 *//*C4 */
        volatile PCR19_t PCR19; /*protocol configuration register 19 *//*C6 */
        volatile PCR20_t PCR20; /*protocol configuration register 20 *//*C8 */
        volatile PCR21_t PCR21; /*protocol configuration register 21 *//*CA */
        volatile PCR22_t PCR22; /*protocol configuration register 22 *//*CC */
        volatile PCR23_t PCR23; /*protocol configuration register 23 *//*CE */
        volatile PCR24_t PCR24; /*protocol configuration register 24 *//*D0 */
        volatile PCR25_t PCR25; /*protocol configuration register 25 *//*D2 */
        volatile PCR26_t PCR26; /*protocol configuration register 26 *//*D4 */
        volatile PCR27_t PCR27; /*protocol configuration register 27 *//*D6 */
        volatile PCR28_t PCR28; /*protocol configuration register 28 *//*D8 */
        volatile PCR29_t PCR29; /*protocol configuration register 29 *//*DA */
        volatile PCR30_t PCR30; /*protocol configuration register 30 *//*DC */
        uint8 reserved2[0x22 + 0x700];
        volatile MSG_BUFF_CCS_t MBCCS[128];     /* 0x800->0xBFF,  message buffer configuration, control & status registers 0-31 *//*100 */
        uint8 reserved123[0x400];
        volatile MBDOR_t MBDOR[132];
        volatile LEETR_t LEETR[6];
    } FR_tag_t;

    typedef union uF_HEADER     /* frame header */
    {
        struct {
            vuint16_t:1;
            vuint16_t PPI:1;    /* Payload Preamble Indicator */
            vuint16_t NUF:1;    /* Null Frame Indicator */
            vuint16_t SYF:1;    /* Sync Frame Indicator */
            vuint16_t SUF:1;    /* Startup Frame Indicator */
            vuint16_t FID:11;   /* Frame ID */

            vuint16_t:2;
            vuint16_t CYCCNT:6; /* Cycle Count */
            vuint16_t:1;
            vuint16_t PLDLEN:7; /* Payload Length */

            vuint16_t:5;
            vuint16_t HDCRC:11; /* Header CRC */
        } B;
        vuint16_t WORDS[3];
    } F_HEADER_t;
    typedef union uS_STSTUS     /* slot status */
    {
        struct {
            vuint16_t VFB:1;    /* Valid Frame on channel B */
            vuint16_t SYB:1;    /* Sync Frame Indicator channel B */
            vuint16_t NFB:1;    /* Null Frame Indicator channel B */
            vuint16_t SUB:1;    /* Startup Frame Indicator channel B */
            vuint16_t SEB:1;    /* Syntax Error on channel B */
            vuint16_t CEB:1;    /* Content Error on channel B */
            vuint16_t BVB:1;    /* Boundary Violation on channel B */
            vuint16_t CH:1;     /* Channel */
            vuint16_t VFA:1;    /* Valid Frame on channel A */
            vuint16_t SYA:1;    /* Sync Frame Indicator channel A */
            vuint16_t NFA:1;    /* Null Frame Indicator channel A */
            vuint16_t SUA:1;    /* Startup Frame Indicator channel A */
            vuint16_t SEA:1;    /* Syntax Error on channel A */
            vuint16_t CEA:1;    /* Content Error on channel A */
            vuint16_t BVA:1;    /* Boundary Violation on channel A */
              vuint16_t:1;
        } RX;
        struct {
            vuint16_t VFB:1;    /* Valid Frame on channel B */
            vuint16_t SYB:1;    /* Sync Frame Indicator channel B */
            vuint16_t NFB:1;    /* Null Frame Indicator channel B */
            vuint16_t SUB:1;    /* Startup Frame Indicator channel B */
            vuint16_t SEB:1;    /* Syntax Error on channel B */
            vuint16_t CEB:1;    /* Content Error on channel B */
            vuint16_t BVB:1;    /* Boundary Violation on channel B */
            vuint16_t TCB:1;    /* Tx Conflict on channel B */
            vuint16_t VFA:1;    /* Valid Frame on channel A */
            vuint16_t SYA:1;    /* Sync Frame Indicator channel A */
            vuint16_t NFA:1;    /* Null Frame Indicator channel A */
            vuint16_t SUA:1;    /* Startup Frame Indicator channel A */
            vuint16_t SEA:1;    /* Syntax Error on channel A */
            vuint16_t CEA:1;    /* Content Error on channel A */
            vuint16_t BVA:1;    /* Boundary Violation on channel A */
            vuint16_t TCA:1;    /* Tx Conflict on channel A */
        } TX;
        vuint16_t R;
    } S_STATUS_t;

    typedef struct uMB_HEADER   /* message buffer header */
    {
        F_HEADER_t FRAME_HEADER;
        // vuint16_t DATA_OFFSET;  // Newer FR does not have this...
        S_STATUS_t SLOT_STATUS;
    } MB_HEADER_t;


#endif /* IP_FLEXCAN_H_ */
