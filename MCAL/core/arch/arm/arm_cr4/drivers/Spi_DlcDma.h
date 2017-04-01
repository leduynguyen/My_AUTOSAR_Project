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

/** @tagSettings DEFAULT_ARCHITECTURE=TMS570 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#ifndef SPI_DLCDMA_H
#define SPI_DLCDMA_H

#define SPI_DLCDMA_SW_MAJOR_VERSION    (2U)
#define SPI_DLCDMA_SW_MINOR_VERSION    (20U)
#define SPI_DLCDMA_SW_PATCH_VERSION    (0U)

/* Interrupt request mask set register 1 */
#define VIM_REQMASKSET1 ((uint32*) 0xFFFFFE34U)
/* Interrupt request mask clear register 1 */
#define VIM_REQMASKCLR1 ((uint32*) 0xFFFFFE44U)

typedef uint8 Dma_HWChannelType;            /* Numeric ID of a hardware channel */
typedef uint8 Dma_ChannelType;              /* Numeric ID of a Channel */
typedef uint8 Dma_TriggerType;              /* Numeric ID of a hardware trigger source */

typedef enum
{
    DMA_UNINIT = 0U,
    DMA_IDLE,
    DMA_BUSY
} Dma_StatusType;       /* Current status of the DMA Module. */

typedef enum
{
    DMA_GROUP_IDLE = 0U,
    DMA_GROUP_BUSY,
    DMA_GROUP_FRAME_COMPLETE,
    DMA_GROUP_BLOCK_COMPLETE
} Dma_GroupStatusType;  /* Current status of a DMA Group. */

typedef enum
{
    SPI_DLCDMA_ADDR_CONST    = 0U,
    DMA_ADDR_POSTINC  = 1U,
    DMA_ADDR_RESERVED = 2U,
    DMA_ADDR_INDEXED  = 3U
} Dma_AddrModeType;     /* addressing mode of the DMA Module. */

typedef enum
{
    DMA_ESIZE_8BIT  = 0U,
    DMA_ESIZE_16BIT = 1U,
    DMA_ESIZE_32BIT = 2U,
    DMA_ESIZE_64BIT = 3U
} Dma_ElementSizeType;     /* element size of the DMA Module. */

enum
{
    DMA_TTYPE_FRAME  = 0U,
    DMA_TTYPE_BLOCK  = 1U
};

typedef enum
{
    DMA0_TXCTRL = 0U,
    DMA0_TXDATA = 1U,
    DMA1_RXSTAT = 2U,
    DMA1_RXDATA = 3U
} Dma_ChannelUsedType;

typedef enum
{
    DMA_TX = 0U,
    DMA_RX
} Dma_ChannelDir;       /* Direction of DMA Channel TX / RX. */


typedef struct
{
    uint32 SrcAddr;
    uint32 DstAddr;
    uint16 FCount;
    uint16 ECount;
    uint16 EISrcInc;
    uint16 EIDstInc;
    uint16 FISrcInc;
    uint16 FIDstInc;
    uint16 NextChTrg; /* next channel trigger, usually zero */
    uint16 ChCtrl;
    uint16 Unit;      /* hardware unit */
    Dma_ChannelType Channel;
    Dma_ChannelDir Direction;
} Dma_ChannelSetupType;

typedef struct
{
    uint8  DmaReq[2U];
}Dma_RequestType;

typedef struct
{
    uint8  Dmachannel[2U];
}Dma_ChannelSelectType;

#define DMA_RES(x)    ((uint16)((x) << 14U))
#define DMA_WES(x)    ((uint16)((x) << 12U))
#define DMA_TTP(x)    ((uint16)((x) << 8U))
#define DMA_AMR(x)    ((uint16)((x) << 3U))
#define DMA_AWR(x)    ((uint16)((x) << 1U))
#define DMA_AIM        (uint16)       (1U)

#define SPI_DLC_RXUNIT0    (0U)   /* MIBSPI1_RX, DREQ[0] */
#define SPI_DLC_TXUNIT0    (1U)   /* MIBSPI1_RX, DREQ[1] */

#define SPI_DLC_RXUNIT1    (2U)   /* SPI2_RX   , DREQ[2] */
#define SPI_DLC_TXUNIT1    (3U)   /* SPI2_RX   , DREQ[3] */

#define SPI_DLC_RXUNIT2    (14U)  /* MIBSPI3_RX, DREQ[14] */
#define SPI_DLC_TXUNIT2    (15U)  /* MIBSPI3_RX, DREQ[15] */

#define SPI_DLC_RXUNIT3    (24U)  /* SPI4_RX   , DREQ[24] */
#define SPI_DLC_TXUNIT3    (25U)  /* SPI4_RX 1 , DREQ[25] */

#define SPI_DLC_RXUNIT4    (30U)  /* MIBSPI5_RX, DREQ[30] */
#define SPI_DLC_TXUNIT4    (31U)  /* MIBSPI5_RX, DREQ[31] */

#define SPI_DLC_RXUNIT0_Channel    (0xFFU)  /* MIBSPI1_RX, Channel / Control packet [Not used] */
#define SPI_DLC_TXUNIT0_Channel    (0xFFU)  /* MIBSPI1_RX, Channel / Control packet [Not used] */

#define SPI_DLC_RXUNIT1_Channel    (0U)     /* SPI2_RX   , Channel / Control packet [0] */
#define SPI_DLC_TXUNIT1_Channel    (1U)     /* SPI2_RX   , Channel / Control packet [1] */

#define SPI_DLC_RXUNIT2_Channel    (0xFFU)  /* MIBSPI3_RX, Channel / Control packet [Not used] */
#define SPI_DLC_TXUNIT2_Channel    (0xFFU)  /* MIBSPI3_RX, Channel / Control packet [Not used] */

#define SPI_DLC_RXUNIT3_Channel    (2U)     /* SPI4_RX   , Channel / Control packet [2] */
#define SPI_DLC_TXUNIT3_Channel    (3U)     /* SPI4_RX 1 , Channel / Control packet [3] */

#define SPI_DLC_RXUNIT4_Channel    (0xFFU)  /* MIBSPI5_RX, Channel / Control packet [Not used] */
#define SPI_DLC_TXUNIT4_Channel    (0xFFU)  /* MIBSPI5_RX, Channel / Control packet [Not used] */

/* definitions for channel control (MIB unit and STD unit) */
/*  RES WES 11:9 TTYPE 7:5  ADDMR ADDMW AIM (Autoinitiation mode)
 *  xx  xx  000   x    000   xx     xx   x
 * ->  x x x x 0 0 0 x 0 0 0 x x x x x
 */
/*  for MIB we use TXCTRL : SRC const
 *                        : DST inc by 2 (indexed)
 *                 TXDATA : SRC inc by 1 (8bit) or 2 (16bit)
 *                        : DST inc by 2 (indexed)
 *                 RXSTAT : SRC inc by 2 (indexed)
 *                        : DST const
 *                 RXDATA : SRC inc by 2 (indexed)
 *                        : DST inc by 1 (8bit) or 2 (16bit)
 */
#define DMA_MIBTXCTRL      (uint16)0x5106U  /* RES:01, WES:01, TType:1, ADDMR:00, ADDMW:11, AIM:0 see DMA manual */
#define DMA_MIBRXSTAT      (uint16)0x5106U  /* RES:01, WES:01, TType:1, ADDMR:00, ADDMW:11, AIM:0 */

#define DMA_MIBTX08_CONST  (uint16)0x0106U  /* RES:00, WES:00, TType:1, ADDMR:00, ADDMW:11, AIM:0 */
#define DMA_MIBTX08_INC    (uint16)0x010EU  /* RES:00, WES:00, TType:1, ADDMR:01, ADDMW:11, AIM:0 */
#define DMA_MIBTX16_CONST  (uint16)0x5106U  /* add RES:01, WES:01 */
#define DMA_MIBTX16_INC    (uint16)0x510EU  /* add RES:01, WES:01 */

#define DMA_MIBRX08_CONST  (uint16)0x0118U  /* RES:00, WES:00, TType:1, ADDMR:11, ADDMW:00, AIM:0 */
#define DMA_MIBRX08_INC    (uint16)0x011AU  /* RES:00, WES:00, TType:1, ADDMR:11, ADDMW:01, AIM:0 */
#define DMA_MIBRX16_CONST  (uint16)0x5118U  /* add RES:01, WES:01 */
#define DMA_MIBRX16_INC    (uint16)0x511AU  /* add RES:01, WES:01 */

/*  for STD we use TXDATA : SRC inc by 1 (8bit) or 2 (16bit) post increment mode
 *                        : DST const
 *                 RXDATA : SRC const
 *                        : DST inc by 1 (8bit) or 2 (16bit) post increment mode
 */
#define DMA_STDTX08_CONST  (uint16)0x0000U  /* RES:00, WES:00, TType:0, ADDMR:00, ADDMW:00, AIM:0 */
#define DMA_STDTX08_INC    (uint16)0x0008U  /* RES:00, WES:00, TType:0, ADDMR:01, ADDMW:00, AIM:0 */
#define DMA_STDTX16_CONST  (uint16)0x5000U  /* add RES:01, WES:01 */
#define DMA_STDTX16_INC    (uint16)0x5008U  /* add RES:01, WES:01 */

#define DMA_STDRX08_CONST  (uint16)0x0000U  /* RES:00, WES:00, TType:0, ADDMR:00, ADDMW:00, AIM:0 */
#define DMA_STDRX08_INC    (uint16)0x0002U  /* RES:00, WES:00, TType:0, ADDMR:00, ADDMW:01, AIM:0 */
#define DMA_STDRX16_CONST  (uint16)0x5000U  /* add RES:01, WES:01 */
#define DMA_STDRX16_INC    (uint16)0x5002U /* add RES:01, WES:01 */

#define SPI_DMA_CHANNEL0_TXDATA    (0U)
#define SPI_DMA_CHANNEL1_RXDATA    (1U)

/* Maximum number of DMA channels used ( SPI2 and SPI4) */
#define DMA_MAX_HW_CHN      (4U)

/* This struct type is intended to be an easier way of accessing the Primary Control Packet of each DMA channel.
 * Use a pointer to this type which points to the base address of Primary Control Packet 0.
 * The Primary Control Packets 1 - 31 can be accessed by using the pointer like an array where
 * the index identifies the number of the Primary Control Packet.
 */
typedef struct   /* Values can be changed by hardware and by software */
{
    volatile uint32 ISADDR;            /* Control Packet base address + Channel offset;  INITIAL SOURCE ADDRESS */
    volatile uint32 IDADDR;            /* Offset: 0x004;   INITIAL DESTINATION ADDRESS */
    volatile uint16 IFTCOUNT;          /* Offset: 0x008;   INITIAL FRAME COUNT */
    volatile uint16 IETCOUNT;          /* Offset: 0x00A;   INITIAL ELEMENT COUNT */
    volatile uint32 Reserved_0x00C;    /* Offset: 0x00C;   Reserved */
    volatile uint16 CHCTRL_CHAIN;      /* Offset: 0x010;   CHANNEL CONTROL: Next Channel to be triggered (0x000000 = no channel) */
    volatile uint16 CHCTRL;            /* Offset: 0x012;   CHANNEL CONTROL: Trigger Type, Read and Write Element Size, Address modes */
    volatile uint16 EIDXD;             /* Offset: 0x014;   Destination Address Element Offset */
    volatile uint16 EIDXS;             /* Offset: 0x016;   Source Address Element Offset */
    volatile uint16 FIDXD;             /* Offset: 0x018;   Destination Address Frame Offset */
    volatile uint16 FIDXS;             /* Offset: 0x01A;   Source Address Frame Offset */
    volatile uint32 Reserved_0x01C;    /* Offset: 0x01C;   Reserved */
} Dma_ChannelControlPacketType;

typedef struct
{
    Dma_ChannelControlPacketType DMA_CHCTRL[32U];
}Dma_ChanCtrlType;

typedef struct   /* Values can be changed by hardware and by software */
{
    volatile uint32 DMA_GCTRL;             /* Register base address;   GLOBAL CONTROL */
    volatile uint32 DMA_PEND;              /* Offset: 0x004;       CHANNEL PENDING */
    volatile uint32 DMA_FBREG;             /* Offset: 0x008;       FALL BACK */
    volatile uint32 DMA_DMASTAT;           /* Offset: 0x00C;       DMA STATUS */
    volatile uint32 DMA_Reserved_0x010;    /* Offset: 0x010;       Reserved */
    volatile uint32 DMA_HWCHENAS;          /* Offset: 0x014;       HW CHANNEL ENABLE SET */
    volatile uint32 DMA_Reserved_0x018;    /* Offset: 0x018;       Reserved */
    volatile uint32 DMA_HWCHENAR;          /* Offset: 0x01C;       HW CHANNEL ENABLE RESET */
    volatile uint32 DMA_Reserved_0x020;    /* Offset: 0x020;       Reserved */
    volatile uint32 DMA_SWCHENAS;          /* Offset: 0x024;       SW CHANNEL ENABLE SET */
    volatile uint32 DMA_Reserved_0x028;    /* Offset: 0x028;       Reserved */
    volatile uint32 DMA_SWCHENAR;          /* Offset: 0x02C;       SW CHANNEL ENABLE RESET */
    volatile uint32 DMA_Reserved_0x030;    /* Offset: 0x030;       Reserved */
    volatile uint32 DMA_CHPRIOS;           /* Offset: 0x034;       CHANNEL PRIORITY SET */
    volatile uint32 DMA_Reserved_0x038;    /* Offset: 0x038;       Reserved */
    volatile uint32 DMA_CHPRIOR;           /* Offset: 0x03C;       CHANNEL PRIORITY RESET */
    volatile uint32 DMA_Reserved_0x040;    /* Offset: 0x040;       Reserved */
    volatile uint32 DMA_GCHIENAS;          /* Offset: 0x044;       GLOBAL CHANNEL INTERRUPT ENABLE SET */
    volatile uint32 DMA_Reserved_0x048;    /* Offset: 0x048;       Reserved */
    volatile uint32 DMA_GCHIENAR;          /* Offset: 0x04C;       GLOBAL CHANNEL INTERRUPT ENABLE RESET */
    volatile uint32 DMA_Reserved_0x050;    /* Offset: 0x050;       Reserved */
    volatile uint8  DMA_DREQASI[32U];       /* Offset: 0x054-0x70;  DMA request assignment [32] for channel */
    volatile uint32 DMA_Reserved_0x074;    /* Offset: 0x074;       Reserved */
    volatile uint32 DMA_Reserved_0x078;    /* Offset: 0x078;       Reserved */
    volatile uint32 DMA_Reserved_0x07C;    /* Offset: 0x07C;       Reserved */
    volatile uint32 DMA_Reserved_0x080;    /* Offset: 0x080;       Reserved */
    volatile uint32 DMA_Reserved_0x084;    /* Offset: 0x084;       Reserved */
    volatile uint32 DMA_Reserved_0x088;    /* Offset: 0x088;       Reserved */
    volatile uint32 DMA_Reserved_0x08C;    /* Offset: 0x08C;       Reserved */
    volatile uint32 DMA_Reserved_0x090;    /* Offset: 0x090;       Reserved */
    volatile uint32 DMA_PAR[4];            /* Offset: 0x094-0xA0;  PORT ASSIGNMENT Register 0-3 */
    volatile uint32 DMA_Reserved_0x0A4;    /* Offset: 0x0A4;       Reserved */
    volatile uint32 DMA_Reserved_0x0A8;    /* Offset: 0x0A8;       Reserved */
    volatile uint32 DMA_Reserved_0x0AC;    /* Offset: 0x0AC;       Reserved */
    volatile uint32 DMA_Reserved_0x0B0;    /* Offset: 0x0B0;       Reserved */
    volatile uint32 DMA_FTCMAP;            /* Offset: 0x0B4;       FTC INTERRUPT MAPPING */
    volatile uint32 DMA_Reserved_0x0B8;    /* Offset: 0x0B8;       Reserved */
    volatile uint32 DMA_LFSMAP;            /* Offset: 0x0BC;       LFS INTERRUPT MAPPING */
    volatile uint32 DMA_Reserved_0x0C0;    /* Offset: 0x0C0;       Reserved */
    volatile uint32 DMA_HBCMAP;            /* Offset: 0x0C4;       HBC INTERRUPT MAPPING */
    volatile uint32 DMA_Reserved_0x0C8;    /* Offset: 0x0C8;       Reserved */
    volatile uint32 DMA_BTCMAP;            /* Offset: 0x0CC;       BTC INTERRUPT MAPPING */
    volatile uint32 DMA_Reserved_0x0D0;    /* Offset: 0x0D0;       Reserved */
    volatile uint32 DMA_BERMAP;            /* Offset: 0x0D4;       BER INTERRUPT MAPPING */
    volatile uint32 DMA_Reserved_0x0D8;    /* Offset: 0x0D8;       Reserved */
    volatile uint32 DMA_FTCINTENAS;        /* Offset: 0x0DC;       FTC INTERRUPT ENABLE SET */
    volatile uint32 DMA_Reserved_0x0E0;    /* Offset: 0x0E0;       Reserved */
    volatile uint32 DMA_FTCINTENAR;        /* Offset: 0x0E4;       FTC INTERRUPT ENABLE RESET */
    volatile uint32 DMA_Reserved_0x0E8;    /* Offset: 0x0E8;       Reserved */
    volatile uint32 DMA_LFSINTENAS;        /* Offset: 0x0EC;       LFS INTERRUPT ENABLE SET */
    volatile uint32 DMA_Reserved_0x0F0;    /* Offset: 0x0F0;       Reserved */
    volatile uint32 DMA_LFSINTENAR;        /* Offset: 0x0F4;       LFS INTERRUPT ENABLE RESET */
    volatile uint32 DMA_Reserved_0x0F8;    /* Offset: 0x0F8;       Reserved */
    volatile uint32 DMA_HBCINTENAS;        /* Offset: 0x0FC;       HBC INTERRUPT ENABLE SET */
    volatile uint32 DMA_Reserved_0x100;    /* Offset: 0x100;       Reserved */
    volatile uint32 DMA_HBCINTENAR;        /* Offset: 0x104;       HBC INTERRUPT ENABLE RESET */
    volatile uint32 DMA_Reserved_0x108;    /* Offset: 0x108;       Reserved */
    volatile uint32 DMA_BTCINTENAS;        /* Offset: 0x10C;       BTC INTERRUPT ENABLE SET */
    volatile uint32 DMA_Reserved_0x110;    /* Offset: 0x110;       Reserved */
    volatile uint32 DMA_BTCINTENAR;        /* Offset: 0x114;       BTC INTERRUPT ENABLE RESET */
    volatile uint32 DMA_Reserved_0x118;    /* Offset: 0x118;       Reserved */
    volatile uint32 DMA_GINTFLAG;          /* Offset: 0x11C;       GLOBAL INTERRUPT FLAG */
    volatile uint32 DMA_Reserved_0x120;    /* Offset: 0x120;       Reserved */
    volatile uint32 DMA_FTCFLAG;           /* Offset: 0x124;       FTC INTERRUPT FLAG */
    volatile uint32 DMA_Reserved_0x128;    /* Offset: 0x128;       Reserved */
    volatile uint32 DMA_LFSFLAG;           /* Offset: 0x12C;       LFS INTERRUPT FLAG */
    volatile uint32 DMA_Reserved_0x130;    /* Offset: 0x130;       Reserved */
    volatile uint32 DMA_HBCFLAG;           /* Offset: 0x134;       HBC INTERRUPT FLAG */
    volatile uint32 DMA_Reserved_0x138;    /* Offset: 0x138;       Reserved */
    volatile uint32 DMA_BTCFLAG;           /* Offset: 0x13C;       BTC INTERRUPT FLAG */
    volatile uint32 DMA_Reserved_0x140;    /* Offset: 0x140;       Reserved */
    volatile uint32 DMA_BERFLAG;           /* Offset: 0x144;       BER INTERRUPT FLAG */
    volatile uint32 DMA_Reserved_0x148;    /* Offset: 0x148;       Reserved */
    volatile uint32 DMA_FTCAOFFSET;        /* Offset: 0x14C;       FTCA INTERRUPT CHANNEL OFFSET */
    volatile uint32 DMA_LFSAOFFSET;        /* Offset: 0x150;       LFSA INTERRUPT CHANNEL OFFSET */
    volatile uint32 DMA_HBCAOFFSET;        /* Offset: 0x154;       HBCA INTERRUPT CHANNEL OFFSET */
    volatile uint32 DMA_BTCAOFFSET;        /* Offset: 0x158;       BTCA INTERRUPT CHANNEL OFFSET */
    volatile uint32 DMA_BERAOFFSET;        /* Offset: 0x15C;       BERA INTERRUPT CHANNEL OFFSET */
    volatile uint32 DMA_FTCBOFFSET;        /* Offset: 0x160;       FTCB INTERRUPT CHANNEL OFFSET */
    volatile uint32 DMA_LFSBOFFSET;        /* Offset: 0x164;       LFSB INTERRUPT CHANNEL OFFSET */
    volatile uint32 DMA_HBCBOFFSET;        /* Offset: 0x168;       HBCB INTERRUPT CHANNEL OFFSET */
    volatile uint32 DMA_BTCBOFFSET;        /* Offset: 0x16C;       BTCB INTERRUPT CHANNEL OFFSET */
    volatile uint32 DMA_BERBOFFSET;        /* Offset: 0x170;       BERB INTERRUPT CHANNEL OFFSET */
    volatile uint32 DMA_Reserved_0x174;    /* Offset: 0x174;       Reserved */
    volatile uint8  DMA_PTCRL_PENDB;       /* Offset: 0x178;       PORT CONTROL Transactions Pending for Port B */
    volatile uint8  DMA_PTCRL_BYB_PRIO;    /* Offset: 0x179;       PORT CONTROL Bypassing of FIFO and Priority Scheme for Port B */
    volatile uint8  DMA_PTCRL_PENDA;       /* Offset: 0x17A;       PORT CONTROL Transactions Pending for Port A */
    volatile uint8  DMA_PTCRL_BYA_PRIO;    /* Offset: 0x17B;       PORT CONTROL Bypassing of FIFO and Priority Scheme for Port A */
    volatile uint32 DMA_RTCTRL;            /* Offset: 0x17C;       RAM TEST CONTROL */
    volatile uint32 DMA_DCTRL;             /* Offset: 0x180;       DEBUG CONTROL */
    volatile uint32 DMA_WPR;               /* Offset: 0x184;       WATCH POINT */
    volatile uint32 DMA_WMR;               /* Offset: 0x188;       WATCH MASK */
    volatile uint32 DMA_PAACSADDR;         /* Offset: 0x18C;       PORT A ACTIVE CHANNEL SOURCE ADDRESS */
    volatile uint32 DMA_PAACDADDR;         /* Offset: 0x190;       PORT A ACTIVE CHANNEL DESTINATION ADDRESS */
    volatile uint32 DMA_PAACTC;            /* Offset: 0x194;       PORT A ACTIVE CHANNEL TRANSFER COUNT */
    volatile uint32 DMA_PBACSADDR;         /* Offset: 0x198;       PORT B ACTIVE CHANNEL SOURCE ADDRESS */
    volatile uint32 DMA_PBACDADDR;         /* Offset: 0x19C;       PORT B ACTIVE CHANNEL DESTINATION ADDRESS */
    volatile uint32 DMA_PBACTC;            /* Offset: 0x1A0;       PORT B ACTIVE CHANNEL TRANSFER COUNT */
    volatile uint32 DMA_Reserved_0x1A4;    /* Offset: 0x1A4;       Reserved */
    volatile uint32 DMA_DMAPCR;            /* Offset: 0x1A8;       PARITY CONTROL */
    volatile uint32 DMA_DMAPAR;            /* Offset: 0x1AC;       PARITY ERROR ADDRESS */
    volatile uint32 DMA_DMAMPCTRL;         /* Offset: 0x1B0;       MEMORY PROTECTION CONTROL */
    volatile uint32 DMA_DMAMPST;           /* Offset: 0x1B4;       MEMORY PROTECTION STATUS */
    volatile uint32 DMA_DMAMPR0S;          /* Offset: 0x1B8;       MEMORY PROTECTION REGION 0 START ADDRESS */
    volatile uint32 DMA_DMAMPR0E;          /* Offset: 0x1BC;       MEMORY PROTECTION REGION 0 END ADDRESS */
    volatile uint32 DMA_DMAMPR1S;          /* Offset: 0x1C0;       MEMORY PROTECTION REGION 1 START ADDRESS */
    volatile uint32 DMA_DMAMPR1E;          /* Offset: 0x1C4;       MEMORY PROTECTION REGION 1 END ADDRESS */
    volatile uint32 DMA_DMAMPR2S;          /* Offset: 0x1C8;       MEMORY PROTECTION REGION 2 START ADDRESS */
    volatile uint32 DMA_DMAMPR2E;          /* Offset: 0x1CC;       MEMORY PROTECTION REGION 2 END ADDRESS */
    volatile uint32 DMA_DMAMPR3S;          /* Offset: 0x1D0;       MEMORY PROTECTION REGION 3 START ADDRESS */
    volatile uint32 DMA_DMAMPR3E;          /* Offset: 0x1D4;       MEMORY PROTECTION REGION 3 END ADDRESS */
} Dma_GlobalRegisterType;

typedef P2VAR(Dma_GlobalRegisterType, AUTOMATIC, SPI_CONST) Dma_GlobalRegisterPtrType;
typedef P2VAR(Dma_ChanCtrlType, AUTOMATIC, SPI_CONST) Dma_ChanCtrlPtrType;

#define DMA_BIT(BitPos)      (((uint32)0x1U) << (BitPos))

/* hardware trigger sources for LS1xxxx, LS2xxxx triggers Dma in compatibility mode */
#define DMA_REQ_SPI2_RX         ((Dma_TriggerType)2U)
#define DMA_REQ_SPI2_TX         ((Dma_TriggerType)3U)
#define DMA_REQ_SPI4_RX         ((Dma_TriggerType)24U)
#define DMA_REQ_SPI4_TX         ((Dma_TriggerType)25U)

#define DMA_REQ_SPI1_RX         ((Dma_TriggerType)0U)
#define DMA_REQ_SPI1_TX         ((Dma_TriggerType)1U)
#define DMA_REQ_SPI3_RX         ((Dma_TriggerType)14U)
#define DMA_REQ_SPI3_TX         ((Dma_TriggerType)15U)
#define DMA_REQ_SPI5_RX         ((Dma_TriggerType)30U)
#define DMA_REQ_SPI5_TX         ((Dma_TriggerType)31U)

#define DMA_GLOBAL_REGISTER_BASE_ADDRESS          ((Dma_GlobalRegisterPtrType) 0xFFFFF000U)
/* Base address where the Primary Control Packets of the DMA hardware channels begin */
#define DMA_PRIMARY_CONTROL_PACKET_BASE_ADDRESS   ((Dma_ChanCtrlPtrType) 0xFFF80000U)


typedef struct
{
    P2FUNC(void, SPI_CODE, NotificationFrame)(void);
    P2FUNC(void, SPI_CODE, NotificationBlock)(void);
    uint32 HWUnit;
}Dma_NotificationType;

#define SPI_START_SEC_CODE
#include "MemMap.h"

FUNC(void, SPI_CODE) Dma_Init( void );
FUNC(void, SPI_CODE) Dma_DeInit( void );
FUNC(void, SPI_CODE) Dma_Setup
(
    P2CONST(Dma_ChannelSetupType, AUTOMATIC, SPI_VAR) Setup
);
FUNC(Dma_ChannelType, SPI_CODE) Dma_GetFree_Channel( void );

#define SPI_STOP_SEC_CODE
#include "MemMap.h"

#define SPI_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

extern P2VAR(Dma_GlobalRegisterType, AUTOMATIC, SPI_CONST) Dma_GlobalRegister;

#define SPI_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#endif
