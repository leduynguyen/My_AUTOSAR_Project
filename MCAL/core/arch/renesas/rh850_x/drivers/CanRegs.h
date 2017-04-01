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

#ifndef CANREGS_H_
#define CANREGS_H_

#include "Arc_Types.h"
#include "rh850.h"

// Global Status Masks
#define CAN_GSTS_GRSTSTS_MASK  0x00000001UL
#define CAN_GSTS_GHLTSTS_MASK  0x00000002UL
#define CAN_GSTS_GSLPSTS_MASK  0x00000004UL
#define CAN_GSTS_GRAMINIT_MASK 0x00000008UL

// GCTR.GMDC bits
#define CAN_GMDC_GLBL_OPR_MODE   0x0UL
#define CAN_GMDC_GLBL_RST_MODE   0x1UL
#define CAN_GMDC_GLBL_TST_MODE   0x2UL

// GCTR.GSLPR bit
#define CAN_GSLPR_GLBL_STOP_MODE  0x1UL

// GAFLECTR.AFLDAE bit
#define CAN_AFLDAE_BITPOS        8
#define CAN_AFLDAE_MASK         (1UL << AFLDAE_BITPOS)
#define CAN_AFLDAE_WREN          0x1

// RFCCx.RFDC bits
#define CAN_RFDC_0_MSGS         0x0
#define CAN_RFDC_4_MSGS         0x1
#define CAN_RFDC_8_MSGS         0x2
#define CAN_RFDC_16_MSGS        0x3
#define CAN_RFDC_32_MSGS        0x4
#define CAN_RFDC_48_MSGS        0x5
#define CAN_RFDC_64_MSGS        0x6
#define CAN_RFDC_128_MSGS       0x7

#define CAN_RFMC_BITPOS          8uL
#define CAN_RFIF_BITPOS          3uL
#define CAN_RFMLT_BITPOS         2uL
#define CAN_RFFLL_BITPOS         1uL
#define CAN_RFEMP_BITPOS         0uL

#define CAN_RFMC_MASK            (0xFFuL << CAN_RFMC_BITPOS)
#define CAN_RFIF_MASK            (1uL << CAN_RFIF_BITPOS)
#define CAN_RFMLT_MASK           (1uL << CAN_RFMLT_BITPOS)
#define CAN_RFFLL_MASK           (1uL << CAN_RFFLL_BITPOS)
#define CAN_RFEMP_MASK           (1uL << CAN_RFEMP_BITPOS)


// CxCTR.CHMDC bits
#define CAN_CHMDC_CH_COM_MODE    0x0UL
#define CAN_CHMDC_CH_RST_MODE    0x1UL
#define CAN_CHMDC_CH_HLT_MODE    0x2UL

// CxCTR.CSLPR bit
#define CAN_CSLPR_CH_STOP_MODE   0x1UL

// Control Channel x Status Masks
#define CAN_CxSTS_CRSTSTS_MASK 0x00000001UL
#define CAN_CxSTS_CHLTSTS_MASK 0x00000002UL
#define CAN_CxSTS_CSLPSTS_MASK 0x00000004UL
#define CAN_CxSTS_EPSTS_MASK   0x00000008UL
#define CAN_CxSTS_BOSTS_MASK   0x00000010UL
#define CAN_CxSTS_TRMSTS_MASK  0x00000020UL
#define CAN_CxSTS_RECSTS_MASK  0x00000040UL
#define CAN_CxSTS_COMSTS_MASK  0x00000080UL

#define CAN_TMC_TMTR_BITPOS    0x0U
#define CAN_TMC_TMTAR_BITPOS   0x1U
#define CAN_TMC_TMOM_BITPOS    0x2U

#define CAN_TMC_TMTR           0x1U
#define CAN_TMC_TMTAR          0x2U
#define CAN_TMC_TMOM           0x4U

#define CAN_CTMS_STANDARD      0x0U
#define CAN_CTMS_LISTENONLY    0x1U
#define CAN_CTMS_EXT_LOOPBACK  0x2U
#define CAN_CTMS_INT_LOOPBACK  0x3U

#define CAN_BOM_ISO11898_1     0x0U
#define CAN_BOM_AUTO_ENTRY     0x1U
#define CAN_BOM_AUTO_END       0x2U
#define CAN_BOM_PROG_REQ       0x3U

#define CAN_GTINTSTS_TSIF_BITPOS     0u
#define CAN_GTINTSTS_TAIF_BITPOS     1u
#define CAN_GTINTSTS_TQIF_BITPOS     2u
#define CAN_GTINTSTS_CFTIF_BITPOS    3u
#define CAN_GTINTSTS_THIF_BITPOS     4u

#define CAN_GTINTSTS_TSIF_MASK       (1uL << CAN_GTINTSTS_TSIF_BITPOS)
#define CAN_GTINTSTS_TAIF_MASK       (1uL << CAN_GTINTSTS_TAIF_BITPOS)
#define CAN_GTINTSTS_TQIF_MASK       (1uL << CAN_GTINTSTS_TQIF_BITPOS)
#define CAN_GTINTSTS_CFTIF_MASK      (1uL << CAN_GTINTSTS_CFTIF_BITPOS)
#define CAN_GTINTSTS_THIF_MASK       (1uL << CAN_GTINTSTS_THIF_BITPOS)

#define CAN_TMSTS_TMTSTS_BITPOS      0u
#define CAN_TMSTS_TMTRF_BITPOS       1u
#define CAN_TMSTS_TMTRM_BITPOS       3u
#define CAN_TMSTS_TMTARM_BITPOS      4u

#define CAN_TMSTS_TMTSTS_MASK        (1u << CAN_TMSTS_TMTSTS_BITPOS)
#define CAN_TMSTS_TMTRF_MASK         (3u << CAN_TMSTS_TMTRF_BITPOS)
#define CAN_TMSTS_TMTRM_MASK         (1u << CAN_TMSTS_TMTRM_BITPOS)
#define CAN_TMSTS_TMTARM_MASK        (1u << CAN_TMSTS_TMTARM_BITPOS)

#define CAN_TMSTS_TMTRF_NO_XMIT      (0u << CAN_TMSTS_TMTRF_BITPOS)
#define CAN_TMSTS_TMTRF_ABORTOK      (1u << CAN_TMSTS_TMTRF_BITPOS)
#define CAN_TMSTS_TMTRF_TXOK         (2u << CAN_TMSTS_TMTRF_BITPOS)
#define CAN_TMSTS_TMTRF_TXOK_W_AREQ  (3u << CAN_TMSTS_TMTRF_BITPOS)

/* Lint Exception, allow "our" vuint32_t type in all bitfields below */
/*lint -save -e46 */
typedef union {
    vuint32_t R;
    struct {
        vuint32_t GMDC:2;
        vuint32_t GSLPR:1;
        vuint32_t :5;
        vuint32_t DEIE:1;
        vuint32_t MEIE:1;
        vuint32_t THLEIE:1;
        vuint32_t :5;
        vuint32_t TSRST:1;
        vuint32_t :15;
    } B;
} CAN_GCTR_t;

typedef union {
    vuint32_t R;
    struct {
        vuint32_t TPRI:1;   //  Transmit Priority Select
        vuint32_t DCE:1;    // DLC Check Enable
        vuint32_t DRE:1;    // DLC Replacement Enable
        vuint32_t MME:1;    // Mirror Function Enable
        vuint32_t DCS:1;    // CAN Clock Source Select*2
        vuint32_t :3;       // Reserved
        vuint32_t TSP:4;    // Timestamp Clock Source Division
        vuint32_t TSSS:1;   // Timestamp Source Select
        vuint32_t TSBTCS:3; // Timestamp Clock Source Select
        vuint32_t ITRCP:16; // Interval Timer Prescaler Set
    } B;
} CAN_GCFG_t;

typedef union {
    vuint32_t R;
    struct {
        vuint32_t GRSTSTS:1;
        vuint32_t GHLTSTS:1;
        vuint32_t GSLPSTS:1;
        vuint32_t GRAMINIT:1;
        vuint32_t :28;
    } B;
} CAN_GSTS_t;


typedef union {
    vuint32_t R;
    struct {
        vuint32_t RFE:1;    // Receive FIFO Buffer Enable
        vuint32_t RFIE:1;   // Receive FIFO Interrupt Enable
        vuint32_t :6;       // Reserved
        vuint32_t RFDC:3;   // Receive FIFO Buffer Depth Configuration
        vuint32_t :1;       // Reserved
        vuint32_t RFIM:1;   // Receive FIFO Interrupt Source Select
        vuint32_t RFIGCV:3; // Receive FIFO Interrupt Request Timing Select
        vuint32_t :16;      // Reserved
    } B;
} CAN_RFCCx_t;

typedef struct {
    union {
        vuint32_t R;
        struct {
            vuint32_t RFID:29;
            vuint32_t :1;
            vuint32_t RFRTR:1;
            vuint32_t RFIDE:1;
        } B;
    } RFIDx; /* ID register */

    union {
        vuint32_t R;
        struct {
            vuint32_t RFTS:16;
            vuint32_t RFPTR:12;
            vuint32_t RFDLC:4;
        } B;
    } RFPTRx; /* ID register */

    union {
        vuint32_t R;
        struct {
            vuint32_t RFDB0:8;
            vuint32_t RFDB1:8;
            vuint32_t RFDB2:8;
            vuint32_t RFDB3:8;
        } B;
    } RFDF0x; /* ID register */

    union {
        vuint32_t R;
        struct {
            vuint32_t RFDB4:8;
            vuint32_t RFDB5:8;
            vuint32_t RFDB6:8;
            vuint32_t RFDB7:8;
        } B;
    } RFDF1x; /* ID register */

} CAN_LPDU_t;
typedef CAN_LPDU_t CAN_RXFIFO_t;
typedef CAN_LPDU_t CAN_RXBUF_t;

typedef struct {
    union {
        vuint32_t R;
        struct {
            vuint32_t TMID:29;
            vuint32_t THLEN:1;
            vuint32_t TMRTR:1;
            vuint32_t TMIDE:1;
        } B;
    } TMIDx; /* ID register */

    union {
        vuint32_t R;
        struct {
            vuint32_t :16;
            vuint32_t TMPTR:8;
            vuint32_t :4;
            vuint32_t TMDLC:4;
        } B;
    } TMPTRx; /* PTR register */

    union {
        vuint32_t R;
        struct {
            vuint32_t TMDB0:8;
            vuint32_t TMDB1:8;
            vuint32_t TMDB2:8;
            vuint32_t TMDB3:8;
        } B;
    } TMDF0x; /* DF0 register */

    union {
        vuint32_t R;
        struct {
            vuint32_t TMDB4:8;
            vuint32_t TMDB5:8;
            vuint32_t TMDB6:8;
            vuint32_t TMDB7:8;
        } B;
    } TMDF1x; /* DF1 register */

} CAN_TXBUF_t;


typedef union {
    vuint32_t R;
    struct {
        vuint32_t BEF:1; /* Bus Error Flag */
        vuint32_t EWF:1; /*  Error Warning Flag */
        vuint32_t EPF:1; /*  Error Passive Flag */
        vuint32_t BOEF:1; /*  Bus Off Entry Flag */
        vuint32_t BORF:1; /*  Bus Off Recovery Flag */
        vuint32_t OVLF:1; /*  Overload Flag */
        vuint32_t BLF:1; /*  Bus Lock Flag */
        vuint32_t ALF:1; /*  Arbitration-lost Flag */
        vuint32_t SERR:1; /*  Stuff Error Flag */
        vuint32_t FERR:1; /*  Form Error Flag */
        vuint32_t AERR:1; /*  ACK Error Flag */
        vuint32_t CERR:1; /*  CRC Error Flag */
        vuint32_t B1ERR:1; /*  Recessive Bit Error Flag */
        vuint32_t B0ERR:1; /*  Dominant Bit Error Flag */
        vuint32_t ADERR:1; /*  ACK Delimiter Error Flag */
        vuint32_t :1; /* Reserved */
        vuint32_t CRCREG:15; /* CRC Calculation Data */
        vuint32_t :1; /* Reserved */
    } B;
} CxERFL_t;

typedef struct CxREGS {

    union {
        vuint32_t R;
        struct {
            vuint32_t BRP:10;  // Prescaler Division Ratio Set
            vuint32_t :6;      // Reserved
            vuint32_t TSEG1:4; // Time Segment 1 Control
            vuint32_t TSEG2:3; // Time Segment 2 Control
            vuint32_t :1;      // Reserved
            vuint32_t SJW:2;   // Resynchronization Jump Width Control
            vuint32_t :6;      // Reserved
        } B;
    } CxCFG;

    union {
        vuint32_t R;
        struct {
            vuint32_t CHMDC:2; // Mode Select
            vuint32_t CSLPR:1; // Channel Stop Mode
            vuint32_t RTBO:1;  // Forcible Return from Bus-off
            vuint32_t :4;      //Reserved
            vuint32_t BEIE:1;  // Bus Error Interrupt Enable
            vuint32_t EWIE:1;  // Error Warning Interrupt Enable
            vuint32_t EPIE:1;  // Error Passive Interrupt Enable
            vuint32_t BOEIE:1; // Bus Off Entry Interrupt Enable
            vuint32_t BORIE:1; // Bus Off Recovery Interrupt Enable
            vuint32_t OLIE:1;  // Overload Frame Transmit Interrupt Enable
            vuint32_t BLIE:1;  // Bus Lock Interrupt Enable
            vuint32_t ALIE:1;  // Arbitration Lost Interrupt Enable
            vuint32_t TAIE:1;  // Transmit Abort Interrupt Enable
            vuint32_t :4;      // Reserved
            vuint32_t BOM:2;   // Bus Off Recovery Mode Select
            vuint32_t ERRD:1;  // Error Display Mode Select
            vuint32_t CTME:1;  // Communication Test Mode Enable
            vuint32_t CTMS:2;  // Communication Test Mode Select
            vuint32_t :5;      // Reserved
        } B;
    } CxCTR;

    union {
        vuint32_t R;
        struct {
            vuint32_t CRSTSTS:1; // Channel Reset Status Flag
            vuint32_t CHLTSTS:1; // Channel Halt Status Flag
            vuint32_t CSLPSTS:1; // Channel Stop Status Flag
            vuint32_t EPSTS:1;   // Error Passive Status Flag
            vuint32_t BOSTS:1;   // Bus Off Status Flag
            vuint32_t TRMSTS:1;  // Transmit Status Flag
            vuint32_t RECSTS:1;  // Receive Status Flag
            vuint32_t COMSTS:1;  // Communication Status Flag
            vuint32_t :8;        // Reserved These bits are read as the value after reset.
            vuint32_t REC:8;     // The receive error counter (REC) can be read.
            vuint32_t TEC:8;     // The transmit error counter (TEC) can be read.
        } B;
    } CxSTS;

    CxERFL_t CxERFL;
} CAN_CxREGS_t;


typedef union {
    vuint32_t R;
    struct {
        vuint32_t TXQE:1;  /* Transmit Queue Enable */
        vuint32_t :7;      /* Reserved */
        vuint32_t TXQDC:4; /* Transmit Queue Depth Configuration */
        vuint32_t TXQIE:1; /* Transmit Queue Interrupt Enable */
        vuint32_t TXQIM:1; /* Transmit Queue Interrupt Source Select */
        vuint32_t :18;     /* Reserved */
    } B;
} CAN_TXQCCx_t;

typedef union {
    vuint32_t R;
    struct {
        vuint32_t TXQEMP:1; /* Transmit Queue Empty Status Flag */
        vuint32_t TXQFLL:1; /* Transmit Queue Full Status Flag */
        vuint32_t TXQIF:1;  /* Transmit Queue Interrupt Request Flag */
        vuint32_t :29;      /* Reserved */
    } B;
} CAN_TXQSTSx_t;

typedef union {
    vuint32_t R;
    struct {
        vuint32_t THLE:1;  /* Transmit History Buffer Enable */
        vuint32_t :7;      /* Reserved */
        vuint32_t THLIE:1; /* Transmit History Interrupt Enable */
        vuint32_t THLIM:1; /* Transmit History Interrupt Source Select */
        vuint32_t THLDTE:1; /* Transmit History Target Buffer Select */
        vuint32_t :21;     /* Reserved */
    } B;
} CAN_THLCCx_t;

typedef union {
    vuint32_t R;
    struct {
        vuint32_t THLEMP:1; /* Transmit History Buffer Empty */
        vuint32_t THLFLL:1; /* Transmit history Buffer Full */
        vuint32_t THLELT:1; /* Transmit History Buffer Overflow */
        vuint32_t THLIF:1;  /* Transmit History Interrupt Request */
        vuint32_t :4;       /* Reserved */
        vuint32_t THLMC:5;  /* Transmit History Buffer Unread Data Counter */
        vuint32_t :19;      /* Reserved */
    } B;
} CAN_THLSTSx_t;

typedef struct GAFL {
    // Receive Rule Register
    union {
        vuint32_t R;
        struct {
            vuint32_t GAFLID:29; // ID
            vuint32_t GAFLLB:1;  // Receive Rule Target Message Select
            vuint32_t GAFLRTR:1; // RTR Select
            vuint32_t GAFLIDE:1; // IDE Select
        } B;
    } GAFLID;

    // Receive Rule Mask Register
    union {
        vuint32_t R;
        struct {
            vuint32_t GAFLIDM:29; // IDE Mask
            vuint32_t :1;         // Reserved
            vuint32_t GAFLRTRM:1; // RTR Mask
            vuint32_t GAFLIDEM:1; // IDE Mask
        } B;
    } GAFLM;

    // Receive Rule Pointer 0 Register
    union {
        vuint32_t R;
        struct {
            vuint32_t :8;         // Reserved
            vuint32_t GAFLRMDP:7; // Receive Buffer Number Select
            vuint32_t GAFLRMV:1;  // Receive Buffer Enable
            vuint32_t GAFLPTR:12; // Receive Rule Label
            vuint32_t GAFLDLC:4;  // Receive Rule DLC
        } B;
    } GAFLP0;

    // Receive Rule Pointer 1 Register
    union {
        vuint32_t R;
        struct {
            vuint32_t GAFLFDP0:8;  // Receive FIFO Buffer x Select
            vuint32_t GAFLFDP1:18; // Transmit/Receive FIFO Buffer k Select
            vuint32_t :6;          // Reserved
        } B;
    } GAFLP1;

} CAN_GAFLx_t;

typedef union
{
    vuint32_t R;
    struct {
        vuint32_t NRXMB:8; // Receive Buffer Number Configuration
        vuint32_t :24;     // Reserved
    } B;
} CAN_RMNB_t;

typedef union
{
    vuint32_t R;
    struct {
        vuint32_t RMNSq:32; // Receive Buffer Receive Complete Flag q=0..31
    } B;
} CAN_RMND0_t;

typedef union
{
    vuint32_t R;
    struct {
        vuint32_t RMNSq:32; // Receive Buffer Receive Complete Flag q=32..63
    } B;
} CAN_RMND1_t;

typedef union
{
    vuint32_t R;
    struct {
        vuint32_t RMNSq:32; // Receive Buffer Receive Complete Flag q=64..95
    } B;
} CAN_RMND2_t;

typedef union {
    vuint32_t R;
    struct {
        vuint32_t AFLPN:5;  // Receive Rule Table Page Number Configuration (24 pages total)
        vuint32_t :3;       // Reserved
        vuint32_t AFLDAE:1; // Receive Rule Table Write Enable
        vuint32_t :23;      // Reserved
    } B;
} CAN_GAFLECTR_t;

typedef union {
    vuint32_t R;
    struct {
        vuint32_t BT:3;  /* Buffer Type Data */
        vuint32_t BN:4;  /* Buffer Number Data */
        vuint32_t :1;    /* Reserved */
        vuint32_t TID:8; /* Label Data */
        vuint32_t :16;   /* Reserved */
    } B;
} CAN_THLACCm_t;


typedef union {
    vuint32_t R;
    struct {
        vuint32_t CFEMP:1;    /* FIFO Buffer Empty Status Flag */
        vuint32_t CFFLL:1;    /*  FIFO Buffer Full Status Flag */
        vuint32_t CFMLT:1;    /*  FIFO Message Lost Flag */
        vuint32_t CFRXIF:1;   /*  FIFO Receive Interrupt Request Flag */
        vuint32_t CFTXIF:1;   /*  FIFO Transmit Interrupt Request Flag */
        vuint32_t :3;   	  /* Reserved */
        vuint32_t CFMC:8;    /*  FIFO Message Counter */
        vuint32_t :16;   	  /* Reserved */
    } B;
} CAN_CFSTSx_t;


typedef union {
    vuint32_t R;
    struct {
        vuint32_t APA:32;
    } B;
} CAN_RMID_t;

typedef union {
    vuint32_t R;
    struct {
        vuint32_t APA:32;
    } B;
} CAN_RMPTR_t;

typedef union {
    vuint32_t R;
    struct {
        vuint32_t APA:32;
    } B;
} CAN_RMDF0_t;

typedef union {
    vuint32_t R;
    struct {
        vuint32_t APA:32;
    } B;
} CAN_RMDF1_t;

typedef union {
    vuint32_t R;
    struct {
        vuint32_t CFE:1;
        vuint32_t CFRXIE:1;
        vuint32_t CFTXIE:1;
        vuint32_t :5;
        vuint32_t CFDC:3;
        vuint32_t :1;
        vuint32_t CFIM:1;
        vuint32_t CFIGCV:3;
        vuint32_t CFM:2;
        vuint32_t CFITSS:1;
        vuint32_t CFITR:1;
        vuint32_t CFTML:4;
        vuint32_t CFITT:8;
    } B;
} CAN_CFCC_t;


typedef union {
    vuint32_t R;
    struct {
        vuint32_t THLEMP:1;
        vuint32_t THLFLL:1;
        vuint32_t THLELT:1;
        vuint32_t THLIF:1;
        vuint32_t :4;
        vuint32_t THLMC:5;
        vuint32_t :19;
    } B;
} CAN_THLSTS_t;


typedef union {
    vuint32_t R;
    struct {
        vuint32_t BT:3;
        vuint32_t BN:4;
        vuint32_t :1;
        vuint32_t TID:8;
        vuint32_t :16;
    } B;
} CAN_THLACC_t;


typedef struct CAN_RMx {
    CAN_RMID_t 	RMID;
    CAN_RMPTR_t	RMPTR;
    CAN_RMDF0_t RMDF0;
    CAN_RMDF1_t	RMDF1;
} CAN_RMx_t;


typedef union {
    vuint32_t R;
    struct {
        vuint32_t CFTS:16;
        vuint32_t CFPTR:12;
        vuint32_t CFDLC:4;
    } B;
} CAN_CFPTR_t;


typedef struct CAN_CFx {
    vuint32_t CFID;
    CAN_CFPTR_t CFPTR;
    vuint32_t CFDF0;
    vuint32_t CFDF1;
} CAN_CFx_t;

typedef vuint32_t CAN_RPGACCx_t;

/*lint -restore */

typedef union {
    vuint32_t R;
    struct {
        vuint32_t APA:32;
    } B;
} ___type10;


typedef struct
{
    CAN_CxREGS_t CxREGS[6];
    uint8  dummy54[36];                                    /* Reserved         */
    CAN_GCFG_t GCFG;                                         /* GCFG             */
    CAN_GCTR_t GCTR;                                         /* GCTR             */
    const CAN_GSTS_t GSTS;                                   /* GSTS             */
    ___type10 GERFL;                                        /* GERFL            */
    const __type17 GTSC;                                   /* GTSC             */
    CAN_GAFLECTR_t GAFLECTR;                                     /* GAFLECTR         */
    ___type10 GAFLCFGx[2];                                  /* GAFLCFG0         */
//    ___type10 GAFLCFG1;                                     /* GAFLCFG1         */
    ___type10 RMNB;                                         /* RMNB             */
    ___type10 RMND0;                                        /* RMND0            */
    ___type10 RMND1;                                        /* RMND1            */
    ___type10 RMND2;                                        /* RMND2            */
    uint8  dummy55[4];                                     /* Reserved         */
    CAN_RFCCx_t RFCC[8];                                      /* RFCC0            */
    ___type10 RFSTS[8];                                     /* RFSTS0           */
    ___type10 RFPCTR[8];                                    /* RFPCTR0          */
    CAN_CFCC_t CFCC[18];                                     /* CFCC0            */
    uint8  dummy56[24];                                    /* Reserved         */
    CAN_CFSTSx_t CFSTS[18];                                     /* CFSTS0           */
    uint8  dummy57[24];                                    /* Reserved         */
    ___type10 CFPCTR[18];                                   /* CFPCTR0          */
    uint8  dummy58[24];                                    /* Reserved         */
    const ___type10 FESTS;                                  /* FESTS            */
    const ___type10 FFSTS;                                  /* FFSTS            */
    const ___type10 FMSTS;                                  /* FMSTS            */
    const ___type10 RFISTS;                                 /* RFISTS           */
    const ___type10 CFRISTS;                                /* CFRISTS          */
    const ___type10 CFTISTS;                                /* CFTISTS          */
    uint8  TMC[96];                                        /* TMC0             */
    uint8  dummy59[32];                                    /* Reserved         */
    uint8  TMSTS[96];                                      /* TMSTS0           */
    uint8  dummy60[32];                                    /* Reserved         */
    const ___type10 TMTRSTS0;                               /* TMTRSTS0         */
    const ___type10 TMTRSTS1;                               /* TMTRSTS1         */
    const ___type10 TMTRSTS2;                               /* TMTRSTS2         */
    uint8  dummy61[4];                                     /* Reserved         */
    const ___type10 TMTARSTS0;                              /* TMTARSTS0        */
    const ___type10 TMTARSTS1;                              /* TMTARSTS1        */
    const ___type10 TMTARSTS2;                              /* TMTARSTS2        */
    uint8  dummy62[4];                                     /* Reserved         */
    const ___type10 TMTCSTS0;                               /* TMTCSTS0         */
    const ___type10 TMTCSTS1;                               /* TMTCSTS1         */
    const ___type10 TMTCSTS2;                               /* TMTCSTS2         */
    uint8  dummy63[4];                                     /* Reserved         */
    const ___type10 TMTASTS0;                               /* TMTASTS0         */
    const ___type10 TMTASTS1;                               /* TMTASTS1         */
    const ___type10 TMTASTS2;                               /* TMTASTS2         */
    uint8  dummy64[4];                                     /* Reserved         */
    ___type10 TMIEC0;                                       /* TMIEC0           */
    ___type10 TMIEC1;                                       /* TMIEC1           */
    ___type10 TMIEC2;                                       /* TMIEC2           */
    uint8  dummy65[4];                                     /* Reserved         */
    CAN_TXQCCx_t TXQCC[6];                                       /* TXQCC0           */
    uint8  dummy66[8];                                     /* Reserved         */
    CAN_TXQSTSx_t TXQSTS[6];                                      /* TXQSTS0          */
    uint8  dummy67[8];                                     /* Reserved         */
    ___type10 TXQPCTR[6];                                     /* TXQPCTR0         */
    uint8  dummy68[8];                                     /* Reserved         */
    CAN_THLCCx_t THLCC[6];                                       /* THLCC0           */
    uint8  dummy69[8];                                     /* Reserved         */
    CAN_THLSTS_t THLSTS[6];                                      /* THLSTS0          */
    uint8  dummy70[8];                                     /* Reserved         */
    ___type10 THLPCTR[6];                                     /* THLPCTR0         */
    uint8  dummy71[8];                                     /* Reserved         */
    const ___type10 GTINTSTS0;                              /* GTINTSTS0        */
    const ___type10 GTINTSTS1;                              /* GTINTSTS1        */
    ___type10 GTSTCFG;                                      /* GTSTCFG          */
    ___type10 GTSTCTR;                                      /* GTSTCTR          */
    uint8  dummy72[12];                                    /* Reserved         */
    __type17 GLOCKK;                                       /* GLOCKK           */
    uint8  dummy73[128];                                   /* Reserved         */
    CAN_GAFLx_t GAFLx[16];								   /* GAFLID0, Receive rules */
    CAN_RMx_t RMx[96];									   /* RMID0            */
    uint8  dummy74[512];                                   /* Reserved         */
    CAN_RXBUF_t RFx[8];									    /* CFID0            */
    CAN_CFx_t CFx[18];									    /* CFID0            */
    uint8  dummy75[96];                                    /* Reserved         */
    CAN_TXBUF_t TMx[96];									  /* TMID0, Transmit buffer            */
    uint8  dummy76[512];                                   /* Reserved         */
    const CAN_THLACC_t THLACC[6];                                /* THLACC0          */
    uint8  dummy77[232];                                   /* Reserved         */
    CAN_RPGACCx_t RPGACCx[64];                             /* RPGACC0, RAM Test Page Access Register          */
} RSCAN_RegType;


#endif /* CANREGS_H_ */
