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

#ifndef CORE_CR4_H_
#define CORE_CR4_H_

#include "Std_Types.h"

#define EXCEPTION_PREFETCH_ABORT     0x00uL
#define EXCEPTION_DATA_ABORT         0x01uL

#define     __I     volatile const            /*!< defines 'read only' permissions      */
#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */

#define FSM_WR_ENA_REG       (*(volatile uint32 *)0xFFF87288U)
#define EEPROM_CONFIG_REG    (*(volatile uint32 *)0xFFF872B8U)

#define RTIGCTRL_CANT1EN        2ul
#define RTIGCTRL_CANT0EN        1ul

typedef volatile struct vimBase
{
    unsigned              : 24U;    /* 0x0000        */
    unsigned      IRQINDEX :  8U;    /* 0x0000        */
    unsigned              : 24U;    /* 0x0004        */
    unsigned      FIQINDEX :  8U;    /* 0x0004        */
    unsigned      : 32U;            /* 0x0008        */
    unsigned      : 32U;            /* 0x000C        */
    unsigned      FIRQPR0;          /* 0x0010        */
    unsigned      FIRQPR1;          /* 0x0014        */
    unsigned      FIRQPR2;          /* 0x0018        */
    unsigned      FIRQPR3;          /* 0x001C        */
    unsigned      INTREQ0;          /* 0x0020        */
    unsigned      INTREQ1;          /* 0x0024        */
    unsigned      INTREQ2;          /* 0x0028        */
    unsigned      INTREQ3;          /* 0x002C        */
    unsigned      REQENASET0;      /* 0x0030        */
    unsigned      REQENASET1;      /* 0x0034        */
    unsigned      REQENASET2;      /* 0x0038        */
    unsigned      REQENASET3;      /* 0x003C        */
    unsigned      REQENACLR0;      /* 0x0040        */
    unsigned      REQENACLR1;      /* 0x0044        */
    unsigned      REQENACLR2;      /* 0x0048        */
    unsigned      REQENACLR3;      /* 0x004C        */
    unsigned      WAKEMASKSET0;     /* 0x0050        */
    unsigned      WAKEMASKSET1;     /* 0x0054        */
    unsigned      WAKEMASKSET2;     /* 0x0058        */
    unsigned      WAKEMASKSET3;     /* 0x005C        */
    unsigned      WAKEMASKCLR0;     /* 0x0060        */
    unsigned      WAKEMASKCLR1;     /* 0x0064        */
    unsigned      WAKEMASKCLR2;     /* 0x0068        */
    unsigned      WAKEMASKCLR3;     /* 0x006C        */
    unsigned      IRQVECREG;        /* 0x0070        */
    unsigned      FIQVECREQ;        /* 0x0074        */
    unsigned                 :  9U; /* 0x0078        */
    unsigned      CAPEVTSRC1 :  7U; /* 0x0078        */
    unsigned                 :  9U; /* 0x0078        */
    unsigned      CAPEVTSRC0 :  7U; /* 0x0078        */
    unsigned      : 32U;            /* 0x007C        */
    unsigned char CHANMAP[64U];     /* 0x0080-0x017C */
} vimBASE_t;

#define vimREG ((vimBASE_t *)0xFFFFFE00U)



typedef volatile struct rtiBase
{
    unsigned GCTRL;          /**< 0x0000: Global Control Register   */
    unsigned TBCTRL;         /**< 0x0004: Timebase Control Register */
    unsigned CAPCTRL;        /**< 0x0008: Capture Control Register  */
    unsigned COMPCTRL;       /**< 0x000C: Compare Control Register  */
    struct
    {
        unsigned FRCx;       /**< 0x0010,0x0030: Free Running Counter x Register         */
        unsigned UCx;        /**< 0x0014,0x0034: Up Counter x Register                   */
        unsigned CPUCx;      /**< 0x0018,0x0038: Compare Up Counter x Register           */
        unsigned : 32;       /**< 0x001C,0x003C: Reserved                                */
        unsigned CAFRCx;     /**< 0x0020,0x0040: Capture Free Running Counter x Register */
        unsigned CAUCx;      /**< 0x0024,0x0044: Capture Up Counter x Register           */
        unsigned : 32;       /**< 0x0028,0x0048: Reserved                                */
        unsigned : 32;       /**< 0x002C,0x004C: Reserved                                */
    } CNT[2U];               /**< Counter x selection:
                                    - 0: Counter 0
                                    - 1: Counter 1                                       */
    struct
    {
        unsigned COMPx;      /**< 0x0050,0x0058,0x0060,0x0068: Compare x Register        */
        unsigned UDCPx;      /**< 0x0054,0x005C,0x0064,0x006C: Update Compare x Register */
    } CMP[4U];               /**< Compare x selection:
                                    - 0: Compare 0
                                    - 1: Compare 1
                                    - 2: Compare 2
                                    - 3: Compare 3                                       */
    unsigned TBLCOMP;        /**< 0x0070: External Clock Timebase Low Compare Register   */
    unsigned TBHCOMP;        /**< 0x0074: External Clock Timebase High Compare Register  */
    unsigned : 32;           /**< 0x0078: Reserved                                       */
    unsigned : 32;           /**< 0x007C: Reserved                                       */
    unsigned SETINT;         /**< 0x0080: Set/Status Interrupt Register                  */
    unsigned CLEARINT;       /**< 0x0084: Clear/Status Interrupt Register                */
    unsigned INTFLAG;        /**< 0x008C: Interrupt Flag Register                        */
} rtiBASE_t;

/** @def rtiREG1
*   @brief RTI1 Register Frame Pointer
*
*   This pointer is used by the RTI driver to access the RTI1 registers.
*/
#define rtiREG1 ((rtiBASE_t *)0xFFFFFC00)


/** @enum systemClockSource
*   @brief Alias names for clock sources
*
*   This enumeration is used to provide alias names for the clock sources:
*     - Oscillator
*     - Pll1
*     - External1
*     - Low Power Oscillator Low
*     - Low Power Oscillator High
*     - PLL2
*     - External2
*     - Synchronous VCLK1
*/
enum systemClockSource
{
    SYS_OSC             = 0x0U,  /**< Alias for oscillator clock Source                */
    SYS_PLL1            = 0x1U,  /**< Alias for Pll1 clock Source                      */
    SYS_EXTERNAL1       = 0x3U,  /**< Alias for external clock Source                  */
    SYS_LPO_LOW         = 0x4U,  /**< Alias for low power oscillator low clock Source  */
    SYS_LPO_HIGH        = 0x5U,  /**< Alias for low power oscillator high clock Source */
    SYS_PLL2            = 0x6U,  /**< Alias for Pll2 clock Source                      */
    SYS_EXTERNAL2       = 0x7U,  /**< Alias for external 2 clock Source                */
    SYS_VCLK            = 0x9U,  /**< Alias for synchronous VCLK1 clock Source         */
    SYS_PLL2_ODCLK_8    = 0xEU,  /**< Alias for PLL2_post_ODCLK/8                      */
    SYS_PLL2_ODCLK_16   = 0xFU   /**< Alias for PLL2_post_ODCLK/8                      */
};

typedef volatile struct systemBase1
{
    unsigned SYSPC1;                 /* 0x0000 */
    unsigned SYSPC2;                 /* 0x0004 */
    unsigned SYSPC3;                 /* 0x0008 */
    unsigned SYSPC4;                 /* 0x000C */
    unsigned SYSPC5;                 /* 0x0010 */
    unsigned SYSPC6;                 /* 0x0014 */
    unsigned SYSPC7;                 /* 0x0018 */
    unsigned SYSPC8;                 /* 0x001C */
    unsigned SYSPC9;                 /* 0x0020 */
    unsigned SSWPLL1;                /* 0x0024 */
    unsigned SSWPLL2;                /* 0x0028 */
    unsigned SSWPLL3;                /* 0x002C */
    unsigned CSDIS;                  /* 0x0030 */
    unsigned CSDISSET;               /* 0x0034 */
    unsigned CSDISCLR;               /* 0x0038 */
    unsigned CDDIS;                  /* 0x003C */
    unsigned CDDISSET;              /* 0x0040 */
    unsigned CDDISCLR;              /* 0x0044 */
    unsigned GHVSRC;                 /* 0x0048 */
    unsigned VCLKASRC;               /* 0x004C */
    unsigned RCLKSRC;                /* 0x0050 */
    unsigned CSVSTAT;                /* 0x0054 */
    unsigned MSTGCR;                 /* 0x0058 */
    unsigned MINITGCR;               /* 0x005C */
    unsigned MSINENA;                /* 0x0060 */
    unsigned MSTFAIL;                /* 0x0064 */
    unsigned MSTCGSTAT;              /* 0x0068 */
    unsigned MINISTAT;               /* 0x006C */
    unsigned PLLCTL1;                /* 0x0070 */
    unsigned PLLCTL2;                /* 0x0074 */
    unsigned UERFLAG;                /* 0x0078 */
    unsigned DIEIDL;                 /* 0x007C */
    unsigned DIEIDH;                 /* 0x0080 */
    unsigned VRCTL;                  /* 0x0084 */
    unsigned LPOMONCTL;              /* 0x0088 */
    unsigned CLKTEST;                /* 0x008C */
    unsigned DFTCTRLREG1;            /* 0x0090 */
    unsigned DFTCTRLREG2;            /* 0x0094 */
    unsigned : 32U;                  /* 0x0098 */
    unsigned : 32U;                  /* 0x009C */
    unsigned GPREG1;                 /* 0x00A0 */
    unsigned BTRMSEL;                /* 0x00A4 */
    unsigned IMPFASTS;               /* 0x00A8 */
    unsigned IMPFTADD;               /* 0x00AC */
    unsigned SSIR1;                 /* 0x00B0 */
    unsigned SSIR2;                 /* 0x00B4 */
    unsigned SSIR3;                 /* 0x00B8 */
    unsigned SSIR4;                 /* 0x00BC */
    unsigned RAMGCR;                 /* 0x00C0 */
    unsigned BMMCR1;                 /* 0x00C4 */
    unsigned BMMCR2;                 /* 0x00C8 */
    unsigned MMUGCR;                 /* 0x00CC */
#ifdef _little_endian__
    unsigned        : 8U;            /* 0x00D0 */
    unsigned PENA   : 1U;            /* 0x00D0 */
    unsigned        : 7U;            /* 0x00D0 */
    unsigned VCLKR  : 4U;            /* 0x00D0 */
    unsigned        : 4U;            /* 0x00D0 */
    unsigned VCLK2R : 4U;            /* 0x00D0 */
    unsigned        : 4U;            /* 0x00D0 */
#else
    unsigned CLKCNTL;
//    unsigned        : 4U;            /* 0x00D0 */
//    unsigned VCLK2R : 4U;            /* 0x00D0 */
//    unsigned        : 4U;            /* 0x00D0 */
//    unsigned VCLKR  : 4U;            /* 0x00D0 */
//    unsigned        : 7U;            /* 0x00D0 */
//    unsigned PENA   : 1U;            /* 0x00D0 */
//    unsigned        : 8U;            /* 0x00D0 */

#endif
    unsigned : 32U;                  /* 0x00D4 */
    unsigned DSPGCR;                 /* 0x00D8 */
    unsigned DEVCR1;                 /* 0x00DC */
    unsigned SYSECR;                 /* 0x00E0 */
    unsigned SYSESR;                 /* 0x00E4 */
    unsigned ITIFLAG;                /* 0x00E8 */
    unsigned GBLSTAT;                /* 0x00EC */
    unsigned DEV;                    /* 0x00F0 */
    unsigned SSIVEC;                 /* 0x00F4 */
    unsigned SSIF;                   /* 0x00F8 */
} systemBASE1_t;

typedef volatile struct systemBase2 {
    unsigned PLLCTL3;					/* 0x0000 */
    unsigned : 32U;						/* 0x0004 */
    unsigned STCCLKDIV;					/* 0x0008 */
    unsigned : 32U;	                	/* 0x000C */
    unsigned : 32U;                 	/* 0x0010 */
    unsigned : 32U;                 	/* 0x0014 */
    unsigned : 32U;                 	/* 0x0018 */
    unsigned : 32U;                 	/* 0x001C */
    unsigned : 32U;                 	/* 0x0020 */
    unsigned ECPCNTL;					/* 0x0024 */
    unsigned : 32U;                		/* 0x0028 */
    unsigned : 32U;                		/* 0x002C */
    unsigned : 32U;                  	/* 0x0030 */
    unsigned : 32U;               		/* 0x0034 */
    unsigned : 32U;               		/* 0x0038 */
    unsigned CLK2CNTRL;					/* 0x003C */
    unsigned VCLKACON1;					/* 0x0040 */
    unsigned : 32U;                  	/* 0x0044 */
    unsigned : 32U;               		/* 0x0048 */
    unsigned : 32U;               		/* 0x004C */
    unsigned : 32U;               		/* 0x0050 */
    unsigned HCLKCNTL;					/* 0x0054 */

} systemBASE2_t;


/** @def systemREG1
*   @brief System Register Frame 1 Pointer
*
*   This pointer is used by the system driver to access the system frame 1 registers.
*/
#define systemREG1 ((systemBASE1_t *)0xFFFFFF00U)


/** @def PRE1
*   @brief Alias name for RTI1CLK PRE clock source
*
*   This is an alias name for the RTI1CLK pre clock source.
*   This can be either:
*     - Oscillator
*     - Pll
*     - 32 kHz Oscillator
*     - External
*     - Low Power Oscillator Low
*     - Low Power Oscillator High
*     - Flexray Pll
*/
#define PRE1 SYS_PLL

/** @def PRE2
*   @brief Alias name for RTI2CLK pre clock source
*
*   This is an alias name for the RTI2CLK pre clock source.
*   This can be either:
*     - Oscillator
*     - Pll
*     - 32 kHz Oscillator
*     - External
*     - Low Power Oscillator Low
*     - Low Power Oscillator High
*     - Flexray Pll
*/
#define PRE2 SYS_PLL

/** @def systemREG2
*   @brief System Register Frame 2 Pointer
*
*   This pointer is used by the system driver to access the system frame 2 registers.
*/
#define systemREG2 ((systemBASE2_t *)0xFFFFE100U)

typedef volatile struct pcrBase
{
    unsigned PMPROTSET0;    /* 0x0000 */
    unsigned PMPROTSET1;    /* 0x0004 */
    unsigned : 32U;         /* 0x0008 */
    unsigned : 32U;         /* 0x000C */
    unsigned PMPROTCLR0;    /* 0x0010 */
    unsigned PMPROTCLR1;    /* 0x0014 */
    unsigned : 32U;         /* 0x0018 */
    unsigned : 32U;         /* 0x001C */
    unsigned PPROTSET0;     /* 0x0020 */
    unsigned PPROTSET1;     /* 0x0024 */
    unsigned PPROTSET2;     /* 0x0028 */
    unsigned PPROTSET3;     /* 0x002C */
    unsigned : 32U;         /* 0x0030 */
    unsigned : 32U;         /* 0x0034 */
    unsigned : 32U;         /* 0x0038 */
    unsigned CLK2CNTRL;     /* 0x003C */
    unsigned PPROTCLR0;     /* 0x0040 */
    unsigned PPROTCLR1;     /* 0x0044 */
    unsigned PPROTCLR2;     /* 0x0048 */
    unsigned PPROTCLR3;     /* 0x004C */
    unsigned : 32U;         /* 0x0050 */
    unsigned : 32U;         /* 0x0054 */
    unsigned : 32U;         /* 0x0058 */
    unsigned : 32U;         /* 0x005C */
    unsigned PCSPWRDWNSET0; /* 0x0060 */
    unsigned PCSPWRDWNSET1; /* 0x0064 */
    unsigned : 32U;         /* 0x0068 */
    unsigned : 32U;         /* 0x006C */
    unsigned PCSPWRDWNCLR0; /* 0x0070 */
    unsigned PCSPWRDWNCLR1; /* 0x0074 */
    unsigned : 32U;         /* 0x0078 */
    unsigned : 32U;         /* 0x007C */
    unsigned PSPWRDWNSET0;  /* 0x0080 */
    unsigned PSPWRDWNSET1;  /* 0x0084 */
    unsigned PSPWRDWNSET2;  /* 0x0088 */
    unsigned PSPWRDWNSET3;  /* 0x008C */
    unsigned : 32U;         /* 0x0090 */
    unsigned : 32U;         /* 0x0094 */
    unsigned : 32U;         /* 0x0098 */
    unsigned : 32U;         /* 0x009C */
    unsigned PSPWRDWNCLR0;  /* 0x00A0 */
    unsigned PSPWRDWNCLR1;  /* 0x00A4 */
    unsigned PSPWRDWNCLR2;  /* 0x00A8 */
    unsigned PSPWRDWNCLR3;  /* 0x00AC */
} pcrBASE_t;


#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
/** @def pcrREG
*   @brief Pcr Register Frame Pointer
*
*   This pointer is used by the system driver to access the Pcr registers.
*/
#define pcrREG ((pcrBASE_t *)0xFFFFE000U)

#elif defined(CFG_TMS570LC43X)

/** @def pcrREG1
*   @brief Pcr1 Register Frame Pointer
*
*   This pointer is used by the system driver to access the Pcr1 registers.
*/
#define pcrREG1 ((pcrBASE_t *)0xFFFF1000U)

/** @def pcrREG2
*   @brief Pcr2 Register Frame Pointer
*
*   This pointer is used by the system driver to access the Pcr2 registers.
*/
#define pcrREG2 ((pcrBASE_t *)0xFCFF1000U)

/** @def pcrREG3
*   @brief Pcr3 Register Frame Pointer
*
*   This pointer is used by the system driver to access the Pcr3 registers.
*/
#define pcrREG3 ((pcrBASE_t *)0xFFF78000U)
#elif defined(CFG_TRAVEO_S6J328C)
/* Not there */
#else
#error MCU not defined
#endif



/*----------------------------------------------------------------------------*/
/* CAN register definition                                                    */

typedef volatile struct
{
    uint32   CTL;
    uint32   SR;
    unsigned     : 16;
    unsigned REC :  8;
    unsigned TEC :  8;
    uint32   BTR;
    uint32   IR;
    uint32   TR;
    unsigned : 32;
    uint32   PEC;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    uint32   ABOT;
    uint32   TRX;
    uint32   TRx[4];
    uint32   NDX;
    uint32   NDx[4];
    uint32   IPX;
    uint32   IPx[4];
    uint32   MVX;
    uint32   MVx[4];
    unsigned : 32;
    uint32   IPMx[4];
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    struct
    {
        uint32   COM;
        uint32   MASK;
        uint32   ARB;
        uint32   MC;
        uint8    DATx[8];
        unsigned : 32;
        unsigned : 32;
    } IFx[3];
    uint32   IF3UEy[4];
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    unsigned : 32;
    uint32   IOTX;
    uint32   IORX;
} Can_RegisterType;


#define DCAN1_Base ((Can_RegisterType *)0xFFF7DC00)
#define DCAN2_Base ((Can_RegisterType *)0xFFF7DE00)
#define DCAN3_Base ((Can_RegisterType *)0xFFF7E000)



typedef volatile struct gioBase
{
    unsigned GCR0;      /**< 0x0000: Global Control Register */
    unsigned PWDN;      /**< 0x0004: Power Down Register */
    unsigned INTDET;    /**< 0x0008: Interrupt Detect Regsiter*/
    unsigned POL;       /**< 0x000C: Interrupt Polarity Register */
    unsigned INTENASET; /**< 0x0010: Interrupt Enable Set Register */
    unsigned INTENACLR; /**< 0x0014: Interrupt Enable Clear Register */
    unsigned LVLSET;    /**< 0x0018: Interrupt Priority Set Register */
    unsigned LVLCLR;    /**< 0x001C: Interrupt Priority Clear Register */
    unsigned FLG;       /**< 0x0020: Interrupt Flag Register */
    unsigned OFFSET0;   /**< 0x0024: Interrupt Offset A Register */
    unsigned OFFSET1;   /**< 0x0028: Interrupt Offset B Register */
} GIO_Base_RegisterType;


/** @struct gioPort
*   @brief GIO Port Register Definition
*/
/** @typedef gioPORT_t
*   @brief GIO Port Register Type Definition
*
*   This type is used to access the GIO Port Registers.
*/
typedef volatile struct gioPort
{
    unsigned DIR;    /**< 0x0000: Data Direction Register */
    unsigned DIN;    /**< 0x0004: Data Input Register */
    unsigned DOUT;   /**< 0x0008: Data Output Register */
    unsigned DSET;   /**< 0x000C: Data Output Set Register */
    unsigned DCLR;   /**< 0x0010: Data Output Clear Register */
    unsigned PDR;    /**< 0x0014: Open Drain Regsiter */
    unsigned PULDIS; /**< 0x0018: Pullup Disable Register */
    unsigned PSL;    /**< 0x001C: Pull Up/Down Selection Register */
} GIO_RegisterType;

typedef volatile struct spiJoinedPort
{
    uint32_t* dirReg;
    uint32_t* inReg;
    uint32_t* outReg;
} GIO_SpiRegisterCollectionType;



#define GIO_PORTA_BASE ((GIO_RegisterType *)0xFFF7BC34)
#define GIO_PORTB_BASE ((GIO_RegisterType *)0xFFF7BC54)
#define GIO_PORTC_BASE ((GIO_RegisterType *)0xFFF7B84C) //N2HET1 as GIO



/** @def gioREG
*   @brief GIO Register Frame Pointer
*
*   This pointer is used by the GIO driver to access the gio module registers.
*/
#define gioREG   ((GIO_Base_RegisterType *)0xFFF7BC00U)

/** @def gioPORTA
*   @brief GIO Port (A) Register Pointer
*
*   Pointer used by the GIO driver to access PORTA
*/
#define gioPORTA ((gioPORT_t *)0xFFF7BC34U)

/** @def gioPORTB
*   @brief GIO Port (B) Register Pointer
*
*   Pointer used by the GIO driver to access PORTB
*/
#define gioPORTB ((gioPORT_t *)0xFFF7BC54U)


/** @def IOMM_BASE_ADDR
*   @brief Base address of the I/O Multiplexing Module
*/
#define IOMM_BASE_ADDR	0xFFFF1C00u



typedef volatile struct flashControl {
    unsigned FRDCNTL;
    unsigned FSPRD;
    unsigned FEDACCTRL1;
    unsigned FEDACCTRL2;
    unsigned FCOR_ERR_CNT;
    unsigned FCOR_ERR_ADD;
    unsigned FEDACSTATUS;
    unsigned FUNC_ERR_ADD;
    unsigned FEDACSDIS;
    /* .. */
} Flash_RegisterType;

#define flashREG ((Flash_RegisterType *)0xFFF87000)


typedef volatile struct PMMRegs {
    uint32_t LOGICPDPWRCTRL0;	/* 0x0, Logic Power Domain Control Register 0 */
    uint32_t :32;
    uint32_t :32;
    uint32_t :32;
    uint32_t MEMPDPWRCTRL0;		/* 0x10, */
    uint32_t :32;
    uint32_t :32;
    uint32_t :32;
    uint32_t PDCLKDIS;			/* 0x20, Power Domain Clock Disable Register */
    uint32_t PDCLKDISSET;		/* 0x24, Power Domain Clock Disable Set Register */
    uint32_t PDCLKDISCLR;		/* 0x28, Power Domain Clock Disable Clear Register */
    uint32_t :32;
    uint32_t :32;
    uint32_t :32;
    uint32_t :32;
    uint32_t :32;
    uint32_t LOGICPDPWRSTAT0;	/* 0x40, Logic Power Domain PD2 Power Status Register */
    uint32_t LOGICPDPWRSTAT1;	/* 0x44, Logic Power Domain PD3 Power Status Register */
    uint32_t LOGICPDPWRSTAT2;	/* 0x48, Logic Power Domain PD4 Power Status Register */
    uint32_t LOGICPDPWRSTAT3;	/* 0x4c, Logic Power Domain PD5 Power Status Register */
    /* .. */
} PMM_RegisterType;

#define pmmREG  ((PMM_RegisterType *)0xFFFF0000UL)



typedef struct
{
  __IO uint32_t CTRL;                         /*!< SysTick Control and Status Register */
  __IO uint32_t LOAD;                         /*!< SysTick Reload Value Register       */
  __IO uint32_t VAL;                          /*!< SysTick Current Value Register      */
  __I  uint32_t CALIB;                        /*!< SysTick Calibration Register        */
} SysTick_Type;



/* Flash Register Frame Definition */
/** @struct flashWBase
*   @brief Flash Wrapper Register Frame Definition
*
*   This type is used to access the Flash Wrapper Registers.
*/
/** @typedef flashWBASE_t
*   @brief Flash Wrapper Register Frame Type Definition
*
*   This type is used to access the Flash Wrapper Registers.
*/
typedef volatile struct flashWBase
{
    uint32 FRDCNTL;         /* 0x0000 */
    uint32 rsvd1;           /* 0x0004 */
    uint32 EE_FEDACCTRL1;   /* 0x0008 */
    uint32 rsvd2;           /* 0x000C */
    uint32 rsvd3;           /* 0x0010 */
    uint32 FEDAC_PASTATUS;  /* 0x0014 */
    uint32 FEDAC_PBSTATUS;  /* 0x0018 */
    uint32 FEDAC_GBLSTATUS; /* 0x001C */
    uint32 rsvd4;           /* 0x0020 */
    uint32 FEDACSDIS;       /* 0x0024 */
    uint32 FPRIM_ADD_TAG;   /* 0x0028 */
    uint32 FDUP_ADD_TAG;    /* 0x002C */
    uint32 FBPROT;          /* 0x0030 */
    uint32 FBSE;            /* 0x0034 */
    uint32 FBBUSY;          /* 0x0038 */
    uint32 FBAC;            /* 0x003C */
    uint32 FBPWRMODE;       /* 0x0040 */
    uint32 FBPRDY;          /* 0x0044 */
    uint32 FPAC1;           /* 0x0048 */
    uint32 rsvd5;           /* 0x004C */
    uint32 FMAC;            /* 0x0050 */
    uint32 FMSTAT;          /* 0x0054 */
    uint32 FEMU_DMSW;       /* 0x0058 */
    uint32 FEMU_DLSW;       /* 0x005C */
    uint32 FEMU_ECC;        /* 0x0060 */
    uint32 FLOCK;           /* 0x0064 */
    uint32 rsvd6;           /* 0x0068 */
    uint32 FDIAGCTRL;       /* 0x006C */
    uint32 rsvd7;           /* 0x0070 */
    uint32 FRAW_ADDR;       /* 0x0074 */
    uint32 rsvd8;           /* 0x0078 */
    uint32 FPAR_OVR;        /* 0x007C */
    uint32 rsvd9[13U];      /* 0x0080 - 0x00B0 */
    uint32 RCR_VALID;       /* 0x00B4 */
    uint32 ACC_THRESHOLD;   /* 0x00B8 */
    uint32 rsvd10;          /* 0x00BC */
    uint32 FEDACSDIS2;      /* 0x00C0 */
    uint32 rsvd11;          /* 0x00C4 */
    uint32 rsvd12;          /* 0x00C8 */
    uint32 rsvd13;          /* 0x00CC */
    uint32 RCR_VALUE0;      /* 0x00D0 */
    uint32 RCR_VALUE1;      /* 0x00D4 */
    uint32 rsvd14[108U];   	/* 0x00D8 - 0x00284 */
    uint32 FSM_WR_ENA;      /* 0x0288 */
    uint32 rsvd15[11U];     /* 0x028C - 0x002B4 */
    uint32 EEPROM_CONFIG;   /* 0x02B8 */
    uint32 rsvd16;          /* 0x02BC */
    uint32 FSM_SECTOR1;     /* 0x02C0 */
    uint32 FSM_SECTOR2;     /* 0x02C4 */
    uint32 rsvd17[78U];     /* 0x02C8 - 0x03FC*/
    uint32 FCFG_BANK;       /* 0x0400 */
} flashWBASE_t;

/** @def flashWREG
*   @brief Flash Wrapper Register Frame Pointer
*
*   This pointer is used by the system driver to access the flash wrapper registers.
*/
#define flashWREG ((flashWBASE_t *)(0xFFF87000U))

#define FSM_WR_ENA_HL       (*(volatile uint32 *)0xFFF87288U)
#define EEPROM_CONFIG_HL    (*(volatile uint32 *)0xFFF872B8U)
#define FSM_SECTOR1         (*(volatile uint32 *)0xFFF872C0U)

/** @enum flashWPowerModes
*   @brief Alias names for flash bank power modes
*
*   This enumeration is used to provide alias names for the flash bank power modes:
*     - sleep
*     - standby
*     - active
*/
enum flashWPowerModes
{
    SYS_SLEEP   = 0U, /**< Alias for flash bank power mode sleep   */
    SYS_STANDBY = 1U, /**< Alias for flash bank power mode standby */
    SYS_ACTIVE  = 3U  /**< Alias for flash bank power mode active  */
};





static inline uint32_t CoreGetIFSR( void ) {
    uint32 __val;
    asm volatile (" mrc   p15, #0, %0, c5, c0, #1" : "=r"(__val) :);
    return __val;
}

static inline uint32_t CoreGetDFSR( void ) {
    uint32 __val;
    asm volatile (" mrc   p15, #0, %0, c5, c0, #0" : "=r"(__val) :);
    return __val;
}


static inline uint32_t CoreGetIFAR( void ) {
    uint32 __val;
    asm volatile (" mrc   p15, #0, %0, c6, c0, #2" : "=r"(__val) :);
    return __val;
}

static inline uint32_t CoreGetDFAR( void ) {
    uint32 __val;
    asm volatile (" mrc   p15, #0, %0, c6, c0, #0" : "=r"(__val) :);
    return __val;
}

static inline uint32_t CoreGetCPSR( void ) {
    uint32 __val;
    asm volatile (" mrs %0, cpsr" : "=r"(__val) :);
    return __val;
}


#endif /* CORE_CR4_H_ */
