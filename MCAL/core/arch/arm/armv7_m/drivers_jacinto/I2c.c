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


/** @tagSettings DEFAULT_ARCHITECTURE=JACINTO6 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/* @req SWS_I2c_00001 */  /* I2c supports pre-compile time configuration */
/* @req SWS_I2c_00002 */  /* Imported types */

#include <string.h>
#include "Os.h"
#include "Det.h"
#include "isr.h"
#include "irq_types.h"
#include "timer.h"
#include "SchM_I2c.h"
#include "I2c_MemMap.h"
#include "I2c.h"
#include "Arc_Types.h" /* ARC specific */

#define I2C_CONFIG_BUS_RECOVERY_CONT_CLK             STD_OFF
#define I2C_WAIT_BB_TIMEOUT                          (4000uL)
#define I2C_RECOVERY_CLK_COUNT                       (9u)

/* !req SWS_I2c_00013 */ /* There needs some deviations in including or excluding files */
/* !req SWS_I2c_00040 */ /* Requirement is not clear since there is no abort API and contradictory with req @SWS_I2c_00040 for timeout handling */
/* @req SWS_I2c_00002 */ /* Imported types */

/* ------------------------------------------------------------------------ *
 *  Register Parameters for I2C CON                                         *
 * ------------------------------------------------------------------------ */
#define I2C_CON_I2C_EN                      (0x00008000UL) /* I2C module enable */
#define I2C_CON_STB                         (0x00000800UL) /* Start byte mode   */
#define I2C_CON_MST                         (0x00000400UL) /* Master/slave mode */
#define I2C_CON_TX                          (0x00000200UL)  /* TX mode           */
#define I2C_CON_RX                          (0x00000000UL)  /* RX mode           */
#define I2C_CON_XSA                         (0x00000100UL)  /* Expand address    */
#define I2C_CON_STP                         (0x00000002UL)  /* Stop condition    */
#define I2C_CON_STT                         (0x00000001UL)  /* Start condition   */

/* ------------------------------------------------------------------------ *
 *  Register Parameters for I2C SYSC                                        *
 * ------------------------------------------------------------------------ */
#define I2C_SYSC_SRST                       (0x00000002UL)  // The module reset

/* ------------------------------------------------------------------------ *
 *  Register Parameters for I2C IRQSTATUS                                   *
 * ------------------------------------------------------------------------ */
#define I2C_STAT_XDR                        (0x00004000UL) /* Transmit draining IRQ status */
#define I2C_STAT_RDR                        (0x00002000UL) /* Receive draining IRQ status  */
#define I2C_STAT_BB                         (0x00001000UL) /* Bus is occupied              */
#define I2C_STAT_ROVR                       (0x00000800UL) /* Receive overrun status       */
#define I2C_STAT_XUDF                       (0x00000400UL) /* Transmit underflow status    */
#define I2C_STAT_AAS                        (0x00000200UL) /* Address recognized as slave  */
#define I2C_STAT_BF                         (0x00000100UL) /* I2C bus became free          */
#define I2C_STAT_AERR                       (0x00000080UL) /* Access Error IRQ status      */
#define I2C_STAT_STC                        (0x00000040UL) /* Start Condition IRQ status   */
#define I2C_STAT_GC                         (0x00000020UL) /* General call                 */
#define I2C_STAT_XRDY                       (0x00000010UL) /* Transmit data ready          */
#define I2C_STAT_RRDY                       (0x00000008UL) /* Receive data ready           */
#define I2C_STAT_ARDY                       (0x00000004UL) /* Register access ready        */
#define I2C_STAT_NACK                       (0x00000002UL) /* No acknowledgment            */
#define I2C_STAT_AL                         (0x00000001UL)       /* Arbitration lost             */
#define I2C_STAT_MASK                       (0xFFFFUL)  /* all status bits              */

/* ------------------------------------------------------------------------ *
 *  Register Parameters for I2C IRQENABLE                                   *
 * ------------------------------------------------------------------------ */
#define  I2C_IRQENABLE_XDR_IE               (0x00004000UL) /* Transmit draining interrupt     */
#define  I2C_IRQENABLE_RDR_IE               (0x00002000UL) /* Receive draining interrupt      */
#define  I2C_IRQENABLE_ROVR_IE              (0x00000800UL) /* Receive draining interrupt      */
#define  I2C_IRQENABLE_XUDF_IE              (0x00000400UL) /* Transmit underflow interrupt    */
#define  I2C_IRQENABLE_AAS_IE               (0x00000200UL) /* Addressed as slave interrupt    */
#define  I2C_IRQENABLE_BF_IE                (0x00000100UL) /* Bus free interrupt              */
#define  I2C_IRQENABLE_AERR_IE              (0x00000080UL) /* Access error interrupt          */
#define  I2C_IRQENABLE_STC_IE               (0x00000040UL) /* Start condition interrupt       */
#define  I2C_IRQENABLE_GC_IE                (0x00000020UL) /* General call interrupt          */
#define  I2C_IRQENABLE_XRDY_IE              (0x00000010UL) /* Transmit data ready interrupt   */
#define  I2C_IRQENABLE_RRDY_IE              (0x00000008UL) /* Receive data ready interrupt    */
#define  I2C_IRQENABLE_ARDY_IE              (0x00000004UL) /* Register access ready interrupt */
#define  I2C_IRQENABLE_NACK_IE              (0x00000002UL) /* Not Acknowledge interrupt       */
#define  I2C_IRQENABLE_AL_IE                (0x00000001UL)       /* Arbitration lost interrupt      */

/* ------------------------------------------------------------------------ *
 *  I2C_BUF Register (Buffer Configuration)                                 *
 * ------------------------------------------------------------------------ */
#define  I2C_BUF_RXFIFO_CLR                 (1UL << 14) /* Rx FIFO is reset     */
#define  I2C_BUF_TXFIFO_CLR                 (1UL <<  6) /* Tx FIFO is reset     */

/* ------------------------------------------------------------------------ *
 *  Register Parameters for I2C_SYSTEST                                   *
 * ------------------------------------------------------------------------ */

#define  I2C_ST_EN                          (0x00008000UL) /* System test enable     */
#define  I2C_ST_FREE                        (0x00004000UL) /* Free running mode      */
#define  I2C_ST_TMODE_COUNTER_TEST          (0x00002000UL) /* SCL in Permanent clock in master mode       */
#define  I2C_ST_TMODE_LOOPBACK_IO           (0x00003000UL) /* Master transmit mode, Loopback + IO mode     */
#define  I2C_ST_TMODE_MASK                  (0x00003000UL)
#define  I2C_ST_SSB                         (0x00000800UL)  /* Set interrupt status bits to 1      */
#define  I2C_ST_SCL_I_FUNC                  (0x00000100UL)  /* SCL line input value (functional mode).      */
#define  I2C_ST_SCL_O_FUNC                  (0x00000080UL)  /* SCL line output value (functional mode).     */
#define  I2C_ST_SDA_I_FUNC                  (0x00000040UL)  /* SDA line input value (functional mode).      */
#define  I2C_ST_SDA_O_FUNC                  (0x00000020UL)  /* SDA line output value (functional mode).     */
#define  I2C_ST_SCL_I                       (0x00000008UL)  /* SCL line sense input value.      */
#define  I2C_ST_SCL_O                       (0x00000004UL)  /* SCL line drive output value.     */
#define  I2C_ST_SDA_I                       (0x00000002UL)  /* SDA line sense input value.      */
#define  I2C_ST_SDA_O                       (0x00000001UL)  /* SDA line drive output value..    */

/* ------------------------------------------------------------------------ *
 *  Register Parameters for I2C BUFSTAT                                     *
 * ------------------------------------------------------------------------ */
/*  indicates the internal FIFO buffer depth. */
#define I2C_FIFODEPTH(base)                (8 * (1U <<  ((I2C_REG(base, I2C_BUFSTAT)) >> 14)))
/*  indicates the number of bytes to be transferred from the RX FIFO  */
#define I2C_BUFRXSTAT(base)                (((I2C_REG(base, I2C_BUFSTAT)) >> 8) & 0x3fU)
/*  indicates the number of data bytes still left to be written in the TX FIFO */
#define I2C_BUFTXSTAT(base)                (I2C_REG(base, I2C_BUFSTAT) & 0x3fU)

/* ---------------------------------------------------------------------------- *
 *  I2C Register                                                                *
 * ---------------------------------------------------------------------------- */
#define I2C_REVNB_LO                       (0x00UL)    /* Module Revision Register (low bytes)     */
#define I2C_REVNB_HI                       (0x04UL)    /* Module Revision Register (high bytes)    */
#define I2C_SYSC                           (0x10UL)    /* System Configuration Register            */
#define I2C_EOI I2C                        (0x20UL)    /* End of Interrupt Register                */
#define I2C_IRQSTATUS_RAW                  (0x24UL)    /* I2C Status Raw Register                  */
#define I2C_IRQSTATUS                      (0x28UL)    /* I2C Status Register                      */
#define I2C_IRQENABLE_SET                  (0x2cUL)    /* I2C Interrupt Enable Set Register        */
#define I2C_IRQENABLE_CLR                  (0x30UL)    /* I2C Interrupt Enable Clear Register      */
#define I2C_WE                             (0x34UL)    /* I2C Wakeup Enable Register               */
#define I2C_DMARXENABLE_SET                (0x38UL)    /* Receive DMA Enable Set Register          */
#define I2C_DMATXENABLE_SET                (0x3cUL)    /* Transmit DMA Enable Set Register         */
#define I2C_DMARXENABLE_CLR                (0x40UL)    /* Receive DMA Enable Clear Register        */
#define I2C_DMATXENABLE_CLR                (0x44UL)    /* Transmit DMA Enable Clear Register       */
#define I2C_DMARXWAKE_EN                   (0x48UL)    /* Receive DMA Wakeup Register              */
#define I2C_DMATXWAKE_EN                   (0x4cUL)    /* Transmit DMA Wakeup Register             */
#define I2C_SYSS                           (0x90UL)    /* System Status Register                   */
#define I2C_BUF                            (0x94UL)    /* Buffer Configuration Register            */
#define I2C_CNT                            (0x98UL)    /* Data Counter Register                    */
#define I2C_DATA                           (0x9cUL)    /* Data Access Register                     */
#define I2C_CON                            (0xa4UL)    /* I2C Configuration Register               */
#define I2C_OA                             (0xa8UL)    /* I2C Own Address Register                 */
#define I2C_SA                             (0xacUL)    /* I2C Slave Address Register               */
#define I2C_PSC                            (0xb0UL)    /* I2C Clock Prescaler Register             */
#define I2C_SCLL                           (0xb4UL)    /* I2C SCL Low Time Register                */
#define I2C_SCLH                           (0xb8UL)    /* I2C SCL High Time Register               */
#define I2C_SYSTEST                        (0xbcUL)    /* System Test Register                     */
#define I2C_BUFSTAT                        (0xc0UL)    /* I2C Buffer Status Register               */
#define I2C_OA1                            (0xc4UL)    /* I2C Own Address 1 Register               */
#define I2C_OA2                            (0xc8UL)    /* I2C Own Address 2 Register               */
#define I2C_OA3                            (0xccUL)    /* I2C Own Address 3 Register               */
#define I2C_ACTOA                          (0xd0UL)    /* Active Own Address Register              */
#define I2C_SBLOCK                         (0xd4UL)    /* I2C Clock Blocking Enable Register       */

/* Used to send bus recovery cycles */
#define I2C_JOB_TIMEOUT_HEALING_CNTR       (250u)     /* atleast 250 ms */

/*lint -save -e9033 -e923
 * these are are thrown because of I2C_REG macro
 * 1.Impermissible cast of composite expression (different essential type categories)
 * 2.cast from unsigned long to pointer
 * */
#define I2C_REG(base, reg)                 ( *( volatile uint32* )( (base) + (reg) ) )

/* Frequency settings */
#if defined(CFG_JAC5) || defined(CFG_JAC5E)
/* Set Clock Prescaler, no scale down needed */
#define I2C_CLOCK_PRESCALAR_100KHZ         (0U)
#define I2C_CLOCK_LOW_100KHZ               (233U)
#define I2C_CLOCK_HIGH_100KHZ              (220U)
#define I2C_CLOCK_PRESCALAR_400KHZ         (0U)
#define I2C_CLOCK_LOW_400KHZ               (47U)
#define I2C_CLOCK_HIGH_400KHZ              (50U)
#define I2C_CLOCK_PRESCALAR_3400KHZ        (0U)
#define I2C_CLOCK_LOW_3400KHZ              (3U)
#define I2C_CLOCK_HIGH_3400KHZ             (3U)
#else
/* I2Ci_INTERNAL_CLK freq = I2Ci_FCLK / (PSC +1) */
#define I2C_CLOCK_PRESCALAR_100KHZ         (23U)
#define I2C_CLOCK_LOW_100KHZ               (13U)
#define I2C_CLOCK_HIGH_100KHZ              (15U)
#define I2C_CLOCK_PRESCALAR_400KHZ         (9U)
#define I2C_CLOCK_LOW_400KHZ               (7U)
#define I2C_CLOCK_HIGH_400KHZ              (5U)
#define I2C_CLOCK_PRESCALAR_3400KHZ        (1U)
#define I2C_CLOCK_LOW_3400KHZ              (0x00000C73U)    /* ((12<<8U)|(115U)) *//* Supported only on I2C3, I2C4 and I2C5 */
#define I2C_CLOCK_HIGH_3400KHZ             (0x00000571U)    /* ( (5<<8U)|(113U)) *//* Supported only on I2C3, I2C4 and I2C5 */
#endif

#if defined(CFG_JAC5) || defined(CFG_JAC5E)
#define I2C0_Base                         (0x48028000UL)
#define I2C0_IRQ                          (I2CINT0_IRQ)
#define I2C1_Base                         (0x4802a000UL)
#define I2C1_IRQ                          (I2CINT1_IRQ)
#define I2C2_Base                         (0x4819c000UL)
#define I2C2_IRQ                          (I2CINT2_IRQ)
#define I2C3_Base                         (0x4819e000UL)
#define I2C3_IRQ                          (I2CINT3_IRQ)

#elif defined (CFG_JAC6)
#define I2C0_Base                         (0x48070000UL + L3_OFFSET)
#define I2C0_IRQ                          (I2CINT1_IRQ)
#define I2C1_Base                         (0x48072000UL + L3_OFFSET)
#define I2C1_IRQ                          (I2CINT2_IRQ)
#define I2C2_Base                         (0x48060000UL + L3_OFFSET)
#define I2C2_IRQ                          (I2CINT3_IRQ)
#define I2C3_Base                         (0x4807A000UL + L3_OFFSET)
#define I2C3_IRQ                          (I2CINT4_IRQ)
#define I2C4_Base                         (0x4807C000UL + L3_OFFSET)
#define I2C4_IRQ                          (I2CINT5_IRQ)
#else
#error I2c: Incorrect cpu selected
#endif

/* @req SWS_I2c_00011 */
#if ( I2C_DEV_ERROR_DETECT == STD_ON )
#if defined(USE_DET)
#include "Det.h"
#else
#error "I2C: DET must be used when dev error detect is enabled"
#endif
#define DET_REPORT_ERROR(_api,_err)      (void)Det_ReportError(I2C_MODULE_ID,0,(_api),(_err))
#else
#define DET_REPORT_ERROR(_api,_err)
#endif

typedef struct
{
    uint8        bInit;
}I2c_CtrlType;

/* Container for the actual jobs */
typedef struct
{
    uint32       DestReg;
    uint8*       pTxData;
    uint8*       pRxData; /* Use same as I2cChannelMaxLength? No buffers are allocated from User itself */
    uint16       Length;
    uint16       DataCounter;
    uint16       RequestHandle;
    uint16       SlaveAddress;
    uint8        Controller;
    uint8        ServiceID;
    uint8        SlaveAddressSize;
    uint8        RegisterSize;
    uint8        State;
}I2c_JobType;

typedef struct
{
    I2c_JobType *Job;
}I2c_ChannelSetType;

typedef struct
{
    uint32      Job;
    vuint32_t   JobKeepingTimer;
    uint32      Channel;
    uint32      PriorityOrder[I2C_CH_COUNT];
    uint32      JobTimeoutHealingCounter;
    uint8       JobState;
}I2c_JobQueueType;

typedef struct{
    uint32     channelId;
    uint32     channelPrio;
}I2c_ChannelPrioType;

/*lint -esym(9003,I2cJobs )*/
static I2c_JobType        I2cJobs[I2C_TOTAL_CHANNEL_QUEUE_SIZE];      /*@req SWS_I2c_00033, I2cChannelQueueSize bytes */
/*lint -esym(9003,I2cChDataBuffer )*/
static uint8              I2cChDataBuffer[I2C_TOTAL_CHANNEL_LENGTH];  /*@req SWS_I2c_00039, buffering I2cChannelMaxLength bytes */
static I2c_ChannelSetType I2cChannelUnit[I2C_CH_COUNT];
const  I2c_ConfigSetType  *const pI2cCfgPtr = &I2cConfigSet;    /* Globally available */
const  I2c_ConfigType     *pI2cImplConfigPtr;             /* Privately available */
static I2c_JobQueueType   I2cJobPriorityQueue;
static I2c_CtrlType       I2cCtrl[I2C_CONTROLLER_COUNT];
static boolean            I2cInitRun = FALSE;
static uint16             I2cJobHandle = 0u;

/* @req SWS_I2c_00031 */ /* I2cChannels are taken care as channels between user and controller */

/* HW specific, not dependent on configurations */
enum
{
     I2C_CTRL_ID_0
    ,I2C_CTRL_ID_1
    ,I2C_CTRL_ID_2
    ,I2C_CTRL_ID_3
#if defined (CFG_JAC6)
    ,I2C_CTRL_ID_4
#endif
    ,I2C_CTRL_ID_COUNT
};
/*lint -esym(9003,I2c_RegisterBase ) cannot be made global */
static const uint32       I2c_RegisterBase[I2C_CTRL_ID_COUNT] = {     I2C0_Base
                                                                     ,I2C1_Base
                                                                     ,I2C2_Base
                                                                     ,I2C3_Base
#if defined (CFG_JAC6)
                                                                     ,I2C4_Base
#endif
};

/* Static Function prototypes */
static void I2c_InterruptHandler(uint8 controller);
static ISR(I2c0_Level0InterruptHandler);
static ISR(I2c1_Level0InterruptHandler);
static ISR(I2c2_Level0InterruptHandler);
static ISR(I2c3_Level0InterruptHandler);
#if defined (CFG_JAC6)
static ISR(I2c4_Level0InterruptHandler);
#endif

/* Interrupt entry for I2C0 */
static ISR(I2c0_Level0InterruptHandler) {I2c_InterruptHandler(I2C_CTRL_ID_0);}
/* Interrupt entry for I2C1 */
static ISR(I2c1_Level0InterruptHandler) {I2c_InterruptHandler(I2C_CTRL_ID_1);}
/* Interrupt entry for I2C2 */
static ISR(I2c2_Level0InterruptHandler) {I2c_InterruptHandler(I2C_CTRL_ID_2);}
/* Interrupt entry for I2C3 */
static ISR(I2c3_Level0InterruptHandler) {I2c_InterruptHandler(I2C_CTRL_ID_3);}
#if defined (CFG_JAC6)
/* Interrupt entry for I2C4 */
static ISR(I2c4_Level0InterruptHandler) {I2c_InterruptHandler(I2C_CTRL_ID_4);}
#endif

static inline void startTimer(uint32 time)
{
    uint32 mainFnPeriod = I2C_MAIN_FUNCTION_PERIOD;
    if(0u != mainFnPeriod){/*lint !e774 */ /* avoid divide by 0 */
        I2cJobPriorityQueue.JobKeepingTimer = (time / (I2C_MAIN_FUNCTION_PERIOD));
    }else{
        /* cannot happen */
        I2cJobPriorityQueue.JobKeepingTimer = 1u;
    }
}

/* returns the controller base */
static uint32 I2c_GetRegisterBase(uint8 controller)
{
    uint32 base;
    base = I2c_RegisterBase[controller];
    return base;
}

static boolean I2c_IsBusBusy(uint8 controller){
    uint32 base = I2c_GetRegisterBase(controller);
    uint32 start=Timer_GetTicks();
    while ((I2C_REG(base, I2C_IRQSTATUS_RAW) & I2C_STAT_BB) != 0){
        if( TIMER_TICK2US(Timer_GetTicks()-start) > I2C_WAIT_BB_TIMEOUT ) {
            return TRUE;
        }
    }
    return FALSE;
}

static void I2c_RecoverBusBusy(uint8 controller){
    uint32 base = I2c_GetRegisterBase(controller);
    I2C_REG(base, I2C_CON) |= I2C_CON_MST;       /* Master Mode */

#if (I2C_CONFIG_BUS_RECOVERY_CONT_CLK == STD_ON)

    /* Option 1 - Put it in mode where it emits clock continously   */
    I2C_REG(base, I2C_SYSTEST) |= (I2C_ST_EN | I2C_ST_TMODE_COUNTER_TEST);
    I2C_REG(base, I2C_SYSTEST) |= I2C_ST_SDA_O;

    Timer_uDelay(I2C_WAIT_BB_TIMEOUT);
#else
    /* Option 2 - Put it in Loopback / IO  mode  */
    I2C_REG(base, I2C_SYSTEST) |= (I2C_ST_EN | I2C_ST_TMODE_LOOPBACK_IO | I2C_ST_SDA_O/* SDA high */);
    for(uint8 clks = 0; clks < I2C_RECOVERY_CLK_COUNT; clks++){
        I2C_REG(base, I2C_SYSTEST) &= ~I2C_ST_SCL_O;/* SCL low */
        Timer_uDelay(3);
        I2C_REG(base, I2C_SYSTEST) |=  I2C_ST_SCL_O;/* SCL high */
        Timer_uDelay(3);
    }
    I2C_REG(base, I2C_SYSTEST) &= ~I2C_ST_SCL_O;/* SCL low to finish last pulse */
    Timer_uDelay(3);

    I2C_REG(base, I2C_SYSTEST) &=  ~I2C_ST_SDA_O; /* SDA low, slave should have released SDA bus */
    Timer_uDelay(2);
    /* Issue manual stop command for safety after 9 clk pulses */
    I2C_REG(base, I2C_SYSTEST) |=  I2C_ST_SCL_O; /* SCL high */
    Timer_uDelay(2);
    I2C_REG(base, I2C_SYSTEST) |=   I2C_ST_SDA_O; /* SDA high */
#endif
    I2C_REG(base, I2C_SYSTEST) &= ~I2C_ST_TMODE_MASK; /* Enable Default functional mode */
    I2C_REG(base, I2C_SYSTEST) &= ~I2C_ST_EN;         /* Disable test mode */
    I2C_REG(base, I2C_CON) |= I2C_CON_STP;            /* Query stop */
    I2C_REG(base, I2C_IRQSTATUS) = I2C_REG(base, I2C_IRQSTATUS_RAW);/* clear status register for safety */
}


/* starting of a I2C read or write job  */
static void I2c_StartJob(I2c_JobType* job)
{
    uint32 registerSize = 0;
    uint32 base = I2c_GetRegisterBase(job->Controller);
    /* Enable I2C */
    I2C_REG(base, I2C_CON) = (uint32)I2C_CON_I2C_EN;
    startTimer (pI2cCfgPtr->I2cController[job->Controller].I2cControllerTimeout);
    /* wait until module is enabled */
    while( (I2C_REG(base, I2C_CON) & I2C_CON_I2C_EN) == 0u ){};
    /* set expanded address if needed */
    if (job->SlaveAddressSize == (uint8)I2C_ADDR_SIZE_10BIT)
    {
        I2C_REG(base, I2C_CON) |= I2C_CON_XSA;
    }
    /* clear status register */
    I2C_REG(base, I2C_IRQSTATUS) = I2C_STAT_MASK;

    /* Set slave address */
    I2C_REG(base, I2C_SA) = job->SlaveAddress;

    /* transmit register */
    if (job->RegisterSize < I2C_SIZE_NONE)
    {
        job->State = I2C_JOB_STATE_TRANSMIT_REGISTER;
        I2cJobPriorityQueue.JobState = job->State;

        if (job->ServiceID == I2C_SERVICE_ID_READ)
        {
            /* set register size */
            I2C_REG(base, I2C_CNT) = job->RegisterSize + 1;
        }

        if (job->ServiceID == I2C_SERVICE_ID_WRITE)
        {
            /* set register size plus 1, to trigger the correct txd interrupt */
            registerSize = job->RegisterSize + 1 + job->Length;
            if (registerSize < 0x10000)
            {
                I2C_REG(base, I2C_CNT) = job->RegisterSize + 1 + job->Length;
            }
            else
            {
                I2C_REG(base, I2C_CNT) = 0xffff;
            }
        }

        /* Master Receive mode with start and stop */
        I2C_REG(base, I2C_CON)      |= I2C_CON_MST       /* Master Mode */
                                    |  I2C_CON_TX        /* Transmit Mode */
                                    |  I2C_CON_STT       /* Start */
                                    |  I2C_CON_STP;      /* Stop */

    }
    else if (job->ServiceID == I2C_SERVICE_ID_READ)
    {
        job->State = I2C_JOB_STATE_RECEIVE_DATA;
        I2cJobPriorityQueue.JobState = job->State;

        I2C_REG(base, I2C_CNT) = job->Length;
        /* Master Receive mode with start and stop */
        I2C_REG(base, I2C_CON)      |= I2C_CON_MST       /* Master Mode */
                                    |  I2C_CON_STT       /* Start */
                                    |  I2C_CON_STP;      /* Stop */
    }
    else if (job->ServiceID == I2C_SERVICE_ID_WRITE)
    {
        job->State = I2C_JOB_STATE_TRANSMIT_DATA;
        I2cJobPriorityQueue.JobState = job->State;

        I2C_REG(base, I2C_CNT) = job->Length;
        /* Master Transmit mode with start and stop */
        I2C_REG(base, I2C_CON)      |= I2C_CON_MST       /* Master Mode */
                                    |  I2C_CON_TX        /* Transmit Mode */
                                    |  I2C_CON_STT       /* Start */
                                    |  I2C_CON_STP;      /* Stop */
    }
    else
    {
        /* nothing to do */
    }

    /* Wait until I2C address was sent */
    if (job->RegisterSize < I2C_SIZE_NONE) {
        while ((I2C_REG(base, I2C_IRQSTATUS_RAW) & I2C_STAT_XRDY) == 0){};
    }

    /* Not Acknowledge detected */
    if ((I2C_REG(base, I2C_IRQSTATUS_RAW) & I2C_STAT_NACK) != 0)
    {
        /* disable all interrupts */
        I2C_REG(base, I2C_IRQENABLE_CLR) = I2C_STAT_MASK;
        /* clear status register */
        I2C_REG(base, I2C_IRQSTATUS) = I2C_STAT_MASK;
        /* disable I2C */
        I2C_REG(base, I2C_CON) = 0;
        job->State = I2C_JOB_STATE_READY;
        I2cJobPriorityQueue.JobState = I2C_JOB_STATE_ERROR;
    }
    /* enable interrupts */
    else
    {
        I2C_REG(base, I2C_IRQENABLE_SET) =      I2C_IRQENABLE_XRDY_IE
                                              | I2C_IRQENABLE_RRDY_IE
                                              | I2C_IRQENABLE_BF_IE;

        if (job->ServiceID == I2C_SERVICE_ID_READ)
        {
            I2C_REG(base, I2C_IRQENABLE_SET) = I2C_IRQENABLE_RRDY_IE;
        }
    }
}

/* gets the I2c controller number from channel */
static uint8 I2c_GetController(uint32 channelId)
{
    uint8 controller = I2C_CONTROLLER_WRONG;
    const I2c_ChannelType* ch;
    for (vuint8_t cc = 0; cc < I2C_CONTROLLER_COUNT; cc++)
    {
        ch = *pI2cCfgPtr->I2cController[cc].I2cChannel;
        for (uint32_t  cn = 0; cn < pI2cImplConfigPtr->module[cc].I2cChannelCount; cn++)
        {
            if (pI2cCfgPtr->I2cController[cc].I2cChannel == NULL)
            {
                continue; /* no controller assigned */
            }
            else if ( ch[cn].I2cChannelId == channelId)
            {
                controller = cc; /* controller found */
                cc = I2C_CONTROLLER_COUNT;
                break;
            }
            else{
                /* Do nothing */
            }
        }
    }
    return controller;
}

/* gets the I2c channel array index  */
static uint32 I2c_GetChannelIndex(uint8 controller,uint32 channelId){
    uint32 channelIndex = I2C_CH_WRONG;
    const I2c_ChannelType* ch;
    ch = *pI2cCfgPtr->I2cController[controller].I2cChannel;
    for (uint32 cn = 0; cn < pI2cImplConfigPtr->module[controller].I2cChannelCount; cn++)
    {
        if (ch[cn].I2cChannelId == channelId)
        {
            channelIndex = cn;
            break;
        }
    }
    return channelIndex;

}

/* set I2C clock, low and high periode in registers SCLL and SCLH */
static void I2c_SetClock(uint32 base, uint32 clock)
{
    switch (clock)
    {
    case 100:
        I2C_REG(base, I2C_PSC) = I2C_CLOCK_PRESCALAR_100KHZ;
        I2C_REG(base, I2C_SCLH) = I2C_CLOCK_HIGH_100KHZ;
        I2C_REG(base, I2C_SCLL) = I2C_CLOCK_LOW_100KHZ;
        break;
    case 400:
        I2C_REG(base, I2C_PSC) = I2C_CLOCK_PRESCALAR_400KHZ;
        I2C_REG(base, I2C_SCLH) = I2C_CLOCK_HIGH_400KHZ;
        I2C_REG(base, I2C_SCLL) = I2C_CLOCK_LOW_400KHZ;
        break;
    case 3400:
        I2C_REG(base, I2C_PSC) = I2C_CLOCK_PRESCALAR_3400KHZ;
        I2C_REG(base, I2C_SCLH) = I2C_CLOCK_HIGH_3400KHZ;
        I2C_REG(base, I2C_SCLL) = I2C_CLOCK_LOW_3400KHZ;
        break;

    default:
        /* Handle if error */
        break;
    }
}

/* interrupt handler for I2C0 to I2C3 */
static void I2c_InterruptHandler(uint8 controller)
{
    uint32 base;
    I2c_JobType* pJob;
    base = I2c_GetRegisterBase(controller);
    pJob = &I2cChannelUnit[I2cJobPriorityQueue.Channel].Job[I2cJobPriorityQueue.Job];

    /* Transmit data ready */
    if ( ((I2C_REG(base, I2C_IRQENABLE_SET) & I2C_IRQENABLE_XRDY_IE) != 0)
           && ((I2C_REG(base, I2C_IRQSTATUS_RAW) & I2C_STAT_XRDY) != 0) ) /*lint !e9007 no side effects on right hand of logical operator && */
    {
        /* set job states */
        if (pJob->State == I2C_JOB_STATE_TRANSMIT_REGISTER)
        {
            /* transmit register */
            for (uint8 n = (pJob->RegisterSize + 1); n > 0 ; n--)
            {
                /* Converting in to 8 bit data from given pJob->DestReg  which could be of different size */
                I2C_REG(base, I2C_DATA) = ((pJob->DestReg >> (8 * (n - 1))) & 0xff);/*lint !e9027 Operator & >> are allowed */
            }
            /* 1 T */
            /* start write service */
            if (pJob->ServiceID == I2C_SERVICE_ID_WRITE)
            {
                pJob->State = I2C_JOB_STATE_TRANSMIT_DATA;
            }
            /* 1 R */
            /* start read service */
            if (pJob->ServiceID == I2C_SERVICE_ID_READ)
            {
                pJob->State = I2C_JOB_STATE_RECEIVE_DATA;
                I2C_REG(base, I2C_IRQENABLE_SET) = I2C_IRQENABLE_ARDY_IE;
            }
        }
        /* transmit data */
        else if (pJob->State == I2C_JOB_STATE_TRANSMIT_DATA)
        {
            /* 2n T */
            if (pJob->DataCounter < pJob->Length)
            {
                //break;
                I2C_REG(base, I2C_DATA) = (uint32)pJob->pTxData[pJob->DataCounter];
                pJob->DataCounter++;
            }
        }
        else
        {
            /* nothing to do */
        }

        /* clear interrupt bit */
        I2C_REG(base, I2C_IRQSTATUS) = I2C_STAT_XRDY;
    }
    /* Receive data ready for read */
    else if ( ((I2C_REG(base, I2C_IRQENABLE_SET) & I2C_IRQENABLE_RRDY_IE) != 0)
          &&  ((I2C_REG(base, I2C_IRQSTATUS_RAW) & I2C_STAT_RRDY) != 0) )/*lint !e9007 no side effects on right hand of logical operator && */
    {
        /* 3n R */
        /* receive data */
        if (pJob->DataCounter < pJob->Length)
        {
            pJob->pRxData[pJob->DataCounter] = (uint8)I2C_REG(base, I2C_DATA); /* I2C_DATA is of 8 bit size */
            pJob->DataCounter++;
        }

        /* clear interrupt bit */
        I2C_REG(base, I2C_IRQSTATUS) = I2C_STAT_RRDY;
    }
    /* Transfer has been performed  */
    else if ( ((I2C_REG(base, I2C_IRQENABLE_SET) & I2C_IRQENABLE_ARDY_IE) != 0)
            && ((I2C_REG(base, I2C_IRQSTATUS_RAW) & I2C_STAT_ARDY) != 0) )/*lint !e9007 no side effects on right hand of logical operator && */
    {
        /* 2 R */
        /* start read service */
        if (pJob->ServiceID == I2C_SERVICE_ID_READ)
        {
            /* Delete this interrupt */
            I2C_REG(base, I2C_IRQENABLE_CLR) = I2C_IRQENABLE_ARDY_IE;
            pJob->State = I2C_JOB_STATE_RECEIVE_DATA;
            /* clear transmit interrupt */
            I2C_REG(base, I2C_IRQENABLE_CLR) = I2C_IRQENABLE_XRDY_IE;
            /* clear status register */
            I2C_REG(base, I2C_IRQSTATUS) = I2C_STAT_MASK;

            I2C_REG(base, I2C_CNT) = pJob->Length;
            /* Master Receive mode with start and stop */
            I2C_REG(base, I2C_CON) &= ~I2C_CON_TX;
            I2C_REG(base, I2C_CON) |= I2C_CON_MST       /* Master Mode */
                                   |  I2C_CON_STT       /* Start */
                                   |  I2C_CON_STP;      /* Stop */
        }
    }
    /* bus free */
    else if ( ((I2C_REG(base, I2C_IRQENABLE_SET) & I2C_IRQENABLE_BF_IE) != 0)
           && ((I2C_REG(base, I2C_IRQSTATUS_RAW) & I2C_STAT_BF) != 0) )/*lint !e9007 no side effects on right hand of logical operator && */
    {
      /* L R/T */
		pJob->State = I2C_JOB_STATE_READY; /* Bus is free */
		if((pJob->ServiceID == I2C_SERVICE_ID_READ) &&
		 (((I2C_REG(base, I2C_IRQSTATUS_RAW) & I2C_STAT_NACK) != 0) ||
		  (pJob->DataCounter == 0u))){
		  /* nothing is received */
		  I2cJobPriorityQueue.JobState = I2C_JOB_STATE_ERROR;
		}else if((pJob->ServiceID == I2C_SERVICE_ID_WRITE) &&
			   (((I2C_REG(base, I2C_IRQSTATUS_RAW) & I2C_STAT_NACK) != 0) ||
			   (pJob->DataCounter != pJob->Length))) {
		  /* Or not everything is sent or sent but with NACK */
		  I2cJobPriorityQueue.JobState = I2C_JOB_STATE_ERROR;
		}else{
		  I2cJobPriorityQueue.JobState = I2C_JOB_STATE_FINISHED;
		}
		/* disable all interrupts */
		I2C_REG(base, I2C_IRQENABLE_CLR) = I2C_STAT_MASK;
		/* clear status register */
		I2C_REG(base, I2C_IRQSTATUS) = I2C_STAT_MASK;
		/* disable I2C */
		I2C_REG(base, I2C_CON) = 0;
    }
    else
    {
        /* nothing to do */
    }
}

/* installation of an interrupt handler */
static void I2c_InstallInterruptHandlers(uint8 controller)
{
    switch (controller)
    {
    case I2C_CTRL_ID_0:
        ISR_INSTALL_ISR2("I2c0Level0", I2c0_Level0InterruptHandler, I2C0_IRQ, I2C_IRQ_PRIORITY, 0);
        break;
    case I2C_CTRL_ID_1:
        ISR_INSTALL_ISR2("I2c1Level0", I2c1_Level0InterruptHandler, I2C1_IRQ, I2C_IRQ_PRIORITY, 0);
        break;
    case I2C_CTRL_ID_2:
        ISR_INSTALL_ISR2("I2c2Level0", I2c2_Level0InterruptHandler, I2C2_IRQ, I2C_IRQ_PRIORITY, 0);
        break;
    case I2C_CTRL_ID_3:
        ISR_INSTALL_ISR2("I2c3Level0", I2c3_Level0InterruptHandler, I2C3_IRQ, I2C_IRQ_PRIORITY, 0);
        break;
#if defined (CFG_JAC6)
    case I2C_CTRL_ID_4:
        ISR_INSTALL_ISR2("I2c4Level0", I2c4_Level0InterruptHandler, I2C4_IRQ, I2C_IRQ_PRIORITY, 0);
        break;
#endif
    default:
           break;
    }
}

/* Allocate Job buffers, TX/RX buffers to the channel and
 *  sort the channel Ids according to their priority set */
static void initializeChannelData(void){
    uint32 vali;
    uint32 valj;
    uint32 temp;
    uint32 job;
    I2c_ChannelPrioType prio[I2C_CH_COUNT];
    uint32 chCnt = 0;
    uint32 chQueueSize = 0;
    uint32 chLength    = 0;

    for(vali= 0u; vali < I2C_CH_COUNT; vali++) {/* For misra purpose */
        prio[vali].channelId =   0;
        prio[vali].channelPrio = 0;
    }
    /* find */
    const I2c_ChannelType* ch;
    for (uint8 cc = 0; cc < I2C_CONTROLLER_COUNT; cc++)
    {
        ch = *pI2cCfgPtr->I2cController[cc].I2cChannel;
        for (uint32 cn = 0; cn < pI2cImplConfigPtr->module[cc].I2cChannelCount; cn++)
        {
            prio[chCnt].channelId =   ch[cn].I2cChannelId;
            prio[chCnt].channelPrio = ch[cn].I2cChannelPriority;
            I2cChannelUnit[ch[cn].I2cChannelId].Job = &I2cJobs[chQueueSize];
            for(job = 0u; job < ch[cn].I2cChannelQueueSize; job++){
                I2cChannelUnit[ch[cn].I2cChannelId].Job[job].pTxData = &I2cChDataBuffer[chLength];
                I2cChannelUnit[ch[cn].I2cChannelId].Job[job].State = I2C_JOB_STATE_READY;
            }
            chQueueSize += ch[cn].I2cChannelQueueSize;
            chLength    += ch[cn].I2cChannelMaxLength;
            chCnt++;
        }
    }

    /* Sort */
    for(vali= 0u; vali < I2C_CH_COUNT; vali++)
    {
        for(valj = vali; valj < I2C_CH_COUNT; valj++)
        {
            if(prio[vali].channelPrio < prio[valj].channelPrio)
            {
                temp = prio[vali].channelPrio;
                prio[vali].channelPrio = prio[valj].channelPrio;
                prio[valj].channelPrio = temp;
                temp = prio[vali].channelId;
                prio[vali].channelId = prio[valj].channelId;
                prio[valj].channelId = temp;
            }
        }
    }
    /* assign */
    for(vali = 0u; vali < I2C_CH_COUNT; vali++)
    {
        I2cJobPriorityQueue.PriorityOrder[vali] = prio[vali].channelId;
    }

}

/* Functions */
/* @file I2c.h */
void I2c_JobTimeoutNotification(void)
{
    uint16 requestHandle;
    uint8 controller;
    uint32 channelIndex;
    DET_REPORT_ERROR(I2C_SERVICE_ID_MAIN, I2C_E_TIMEOUT);
    requestHandle = I2cChannelUnit[I2cJobPriorityQueue.Channel].Job[I2cJobPriorityQueue.Job].RequestHandle;
    controller = I2c_GetController(I2cJobPriorityQueue.Channel);
    channelIndex =  I2c_GetChannelIndex(controller,I2cJobPriorityQueue.Channel);
    I2cChannelUnit[I2cJobPriorityQueue.Channel].Job[I2cJobPriorityQueue.Job].State = I2C_JOB_STATE_TIMEOUT;
    /* user notification */
    if(pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cJobEndNotification != NULL){
       pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cJobEndNotification(E_NOT_OK,requestHandle);
    }
    I2cJobPriorityQueue.JobState = I2C_JOB_STATE_TIMEOUT;
    I2cJobPriorityQueue.JobTimeoutHealingCounter = I2C_JOB_TIMEOUT_HEALING_CNTR;
}

static void I2c_InitHw(void){
    uint32 base;
    /* clean job list */
    memset((void*)I2cChannelUnit, 0, sizeof(I2cChannelUnit));
    /* @req SWS_I2c_00019 */
    /* initialization of all enabled I2C controllers */
    for (vuint8_t c = 0u; c < I2C_CONTROLLER_COUNT; c++)
    {
        if (pI2cImplConfigPtr->module[c].enable == (uint8)I2C_ENABLE)
        {
            /* get I2C register base */
            base = I2c_GetRegisterBase(c);
            /* reset I2C module */
            I2C_REG(base, I2C_SYSC) = I2C_SYSC_SRST;
            /* wait until reset is done */
            while((I2C_REG(base, I2C_SYSC) & I2C_SYSC_SRST) != 0u){};
            /* set I2C clock */
            I2c_SetClock(base, pI2cCfgPtr->I2cController[c].I2cBusSpeed);
            /* Enable I2C */
            I2C_REG(base, I2C_CON) = I2C_CON_I2C_EN;
            /* wait until module is enabled */
            while( (I2C_REG(base, I2C_CON) & I2C_CON_I2C_EN) == 0u ){};
            /* send stop condition */
            I2C_REG(base, I2C_CON) |= I2C_CON_STP;     /* Stop */
            /* clear status register */
            I2C_REG(base, I2C_IRQSTATUS) = I2C_REG(base, I2C_IRQSTATUS_RAW);
            /* recover bus busy status if in case */
            I2c_RecoverBusBusy(c);
            /* install interrupt handler */
            I2c_InstallInterruptHandlers(c);
            /* disable I2C */
            I2C_REG(base, I2C_CON) = 0;
            /* Done */
            I2cCtrl[c].bInit = TRUE;
        }
    }

    initializeChannelData();
    I2cJobPriorityQueue.Channel = 0u;
    I2cJobPriorityQueue.Job = 0u;
    I2cJobPriorityQueue.JobState = I2C_JOB_STATE_READY;
    I2cJobPriorityQueue.JobKeepingTimer = 0u;
    I2cJobPriorityQueue.JobTimeoutHealingCounter = 0u;
    I2cInitRun = TRUE;
}


/* @file I2c.h */
/* @req SWS_I2c_00006 */
void I2c_Init(const I2c_ConfigType* ConfigPtr)
{
    /* Take the implementation specific configurations */
    if(ConfigPtr != NULL){
        pI2cImplConfigPtr = ConfigPtr;
    }else{
        /* @req SWS_I2c_00017 */
        DET_REPORT_ERROR(I2C_SERVICE_ID_INIT, I2C_E_PARAM_POINTER);
        return;
    }
    I2c_InitHw();
}
/*lint -restore*/ /* 9033, 923 are restored */
/* @file I2c.h */
/* @req SWS_I2c_00007 */
#if (I2C_VERSION_INFO_API == STD_ON)
void I2c_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    /* @req SWS_I2c_00017 */
    if(versioninfo == NULL){
        DET_REPORT_ERROR(I2C_SERVICE_ID_GETVERSION, I2C_E_PARAM_POINTER);
        return;
    }
    versioninfo->vendorID = I2C_VENDOR_ID;
    versioninfo->moduleID = I2C_MODULE_ID;
    versioninfo->sw_major_version = I2C_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = I2C_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = I2C_SW_PATCH_VERSION;
}
#endif

/* @file I2c.h */
/* @req SWS_I2c_00008 */
/* @req SWS_I2c_00020 */
Std_ReturnType I2c_Write(I2c_ChannelHandleType channel,
                         uint32 destReg,
                         I2c_AddressSizeType registerSize,
                         const uint8* data,
                         uint16 length,
                         uint16* requestHandle)
{
    Std_ReturnType retVal;
    uint8 controller;
    uint32 jobNum;
    uint32 channelIndex;

    /* check run mode */
    /* @req SWS_I2c_00015 */
    if(I2cInitRun == FALSE){
        DET_REPORT_ERROR(I2C_SERVICE_ID_WRITE, I2C_E_UNINIT);
        return E_NOT_OK;
    }

    /* is data a Null pointer */
    /* @req SWS_I2c_00017 */
    if (data == NULL)
    {
        DET_REPORT_ERROR(I2C_SERVICE_ID_WRITE, I2C_E_PARAM_POINTER);
        return E_NOT_OK;
    }

    /* get I2C controller, assigned from channel */
    controller = I2c_GetController(channel);
    channelIndex = I2c_GetChannelIndex(controller,channel);

    /* no I2C controller found */
    /* @req SWS_I2c_00018 */
    if (  (channel >= I2C_CH_COUNT)
       || (controller >= I2C_CONTROLLER_COUNT))
    {
        DET_REPORT_ERROR(I2C_SERVICE_ID_WRITE, I2C_E_CHANNEL_UNAVAILABLE);
        return E_NOT_OK;
    }

    /* Parameter tests */
    /* @req SWS_I2c_00016 */
    if ( (registerSize > I2C_SIZE_NONE) /* Is Register size OK */
      || (length > pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cChannelMaxLength) ) /* is length OK */
    {
        DET_REPORT_ERROR(I2C_SERVICE_ID_WRITE, I2C_E_PARAM);
        return E_NOT_OK;
    }

    SchM_Enter_I2c_EA_0();
    /* find the free entry */
    jobNum = pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cChannelQueueSize;
    for(vuint32_t job = 0; job  < pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cChannelQueueSize; job++)
    {
        if(I2cChannelUnit[channel].Job[job].State == I2C_JOB_STATE_READY)
        {
            jobNum = job;
            break;
        }
    }

    /* transfer job data */
    /* @req SWS_I2c_00022 */
    if ( (I2cCtrl[controller].bInit == TRUE)
          && (jobNum < pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cChannelQueueSize))
    {
        /* @req SWS_I2c_00034 */
        *requestHandle = I2cJobHandle; /* assign the request handle */
        I2cChannelUnit[channel].Job[jobNum].ServiceID = I2C_SERVICE_ID_WRITE;
        I2cChannelUnit[channel].Job[jobNum].Controller = controller;
        I2cChannelUnit[channel].Job[jobNum].DestReg = destReg;
        I2cChannelUnit[channel].Job[jobNum].RegisterSize = registerSize;
        memcpy(I2cChannelUnit[channel].Job[jobNum].pTxData, data,length);
        I2cChannelUnit[channel].Job[jobNum].Length = length;
        I2cChannelUnit[channel].Job[jobNum].DataCounter = 0;
        I2cChannelUnit[channel].Job[jobNum].RequestHandle = *requestHandle;
        /* @req SWS_I2c_00016 */
        I2cChannelUnit[channel].Job[jobNum].SlaveAddress = (uint16)pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cSlaveRef->I2cSlaveAddress;
        I2cChannelUnit[channel].Job[jobNum].SlaveAddressSize = (uint8)pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cSlaveRef->I2cSlaveAddressSize;
        I2cChannelUnit[channel].Job[jobNum].State = I2C_JOB_STATE_START;
        I2cJobHandle++;
        retVal = E_OK;
    }
    else
    {
        /* @req SWS_I2c_00021 */
        retVal = E_NOT_OK;
    }
    SchM_Exit_I2c_EA_0();
    return retVal;
}

/* @file I2c.h */
/* @req SWS_I2c_00009 */
/* @req SWS_I2c_00024 */
Std_ReturnType I2c_Read(I2c_ChannelHandleType channel,
                        uint32 destReg,
                        I2c_AddressSizeType registerSize,
                        uint8* data,
                        uint16 length,
                        uint16* requestHandle)
{
    Std_ReturnType retVal;
    uint8 controller;
    uint32 jobNum;
    uint32 channelIndex;

    /* check run mode */
    /* @req SWS_I2c_00015 */
    if(I2cInitRun == FALSE){
        DET_REPORT_ERROR(I2C_SERVICE_ID_READ, I2C_E_UNINIT);
        return E_NOT_OK;
    }

    /* is data a Null pointer */
    /* @req SWS_I2c_00017 */
    if (data == NULL)
    {
        DET_REPORT_ERROR(I2C_SERVICE_ID_READ, I2C_E_PARAM_POINTER);
        return E_NOT_OK;
    }
    /* get I2C controller, assigned from channel */
    controller = I2c_GetController(channel);
    channelIndex = I2c_GetChannelIndex(controller,channel);

    /* no I2C controller found */
    /* @req SWS_I2c_00018 */
    if (  (channel >= I2C_CH_COUNT)
       || (controller >= I2C_CONTROLLER_COUNT))
    {
        DET_REPORT_ERROR(I2C_SERVICE_ID_READ, I2C_E_CHANNEL_UNAVAILABLE);
        return E_NOT_OK;
    }

    /* Parameter tests */
    /* @req SWS_I2c_00016 */
    if ( (registerSize > I2C_SIZE_NONE) /* Is Register size OK */
      || (length > pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cChannelMaxLength) ) /* is length OK */
    {
           DET_REPORT_ERROR(I2C_SERVICE_ID_READ, I2C_E_PARAM);
        return E_NOT_OK;
    }

    SchM_Enter_I2c_EA_0();
    /* find the free entry */
    jobNum = pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cChannelQueueSize;
    for(vuint32_t job = 0; job  < pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cChannelQueueSize; job++)
    {
        if(I2cChannelUnit[channel].Job[job].State == I2C_JOB_STATE_READY)
        {
            jobNum = job;
            break;
        }
    }
    /* @req SWS_I2c_00026 */
    if ( (I2cCtrl[controller].bInit == TRUE)
          && (jobNum < pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cChannelQueueSize) )
    {
        /* @req SWS_I2c_00034 */
        *requestHandle = I2cJobHandle; /* assign the request handle */
        I2cChannelUnit[channel].Job[jobNum].ServiceID = I2C_SERVICE_ID_READ;
        I2cChannelUnit[channel].Job[jobNum].Controller = controller;
        I2cChannelUnit[channel].Job[jobNum].DestReg = destReg;
        I2cChannelUnit[channel].Job[jobNum].RegisterSize = registerSize;
        I2cChannelUnit[channel].Job[jobNum].pRxData = data;
        I2cChannelUnit[channel].Job[jobNum].Length = length;
        I2cChannelUnit[channel].Job[jobNum].DataCounter = 0;
        I2cChannelUnit[channel].Job[jobNum].RequestHandle = *requestHandle;
        /* @req SWS_I2c_00032 */
        I2cChannelUnit[channel].Job[jobNum].SlaveAddress = (uint16)pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cSlaveRef->I2cSlaveAddress;
        I2cChannelUnit[channel].Job[jobNum].SlaveAddressSize = (uint8)pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cSlaveRef->I2cSlaveAddressSize;
        I2cChannelUnit[channel].Job[jobNum].State = I2C_JOB_STATE_START;
        I2cJobHandle++;
        retVal = E_OK;
    }
    else
    {
        /* @req SWS_I2c_00025 */
        retVal = E_NOT_OK;
    }
    SchM_Exit_I2c_EA_0();
    return retVal;
}

/* @file I2c.h */
/* @req SWS_I2c_00029 */
/* @req SWS_I2c_00028 */
/* @req SWS_I2c_00034 */
/* @req SWS_I2c_00035 */
/* @req SWS_I2c_00036 */
/* @req SWS_I2c_00038 */
/* @req SWS_I2c_00023 */
/* @req SWS_I2c_00027 */
void I2c_MainFunction(void)
{
    /* @req SWS_I2c_00015 */
    if(I2cInitRun == FALSE){
        DET_REPORT_ERROR(I2C_SERVICE_ID_MAIN, I2C_E_UNINIT);
        return;
    }
    uint8 controller;
    uint16 requestHandle;
    uint32 channelIndex;

    /*User notification */
    controller =    I2c_GetController(I2cJobPriorityQueue.Channel);
    channelIndex =  I2c_GetChannelIndex(controller,I2cJobPriorityQueue.Channel);
    requestHandle = I2cChannelUnit[I2cJobPriorityQueue.Channel].Job[I2cJobPriorityQueue.Job].RequestHandle;
    if (I2cJobPriorityQueue.JobState == I2C_JOB_STATE_FINISHED){
        I2cJobPriorityQueue.JobKeepingTimer = 0u;
        I2cJobPriorityQueue.JobState = I2C_JOB_STATE_READY;
        /* @req SWS_I2c_00037 */
        if(pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cJobEndNotification != NULL){
            pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cJobEndNotification(E_OK,requestHandle);
        }
    }
    if (I2cJobPriorityQueue.JobState == I2C_JOB_STATE_ERROR){
        I2cJobPriorityQueue.JobKeepingTimer = 0u;
        I2cJobPriorityQueue.JobState = I2C_JOB_STATE_READY;
        DET_REPORT_ERROR(I2C_SERVICE_ID_MAIN, I2C_E_TIMEOUT);
        /* @req SWS_I2c_00037 */
        if(pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cJobEndNotification != NULL){
            pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cJobEndNotification(E_NOT_OK,requestHandle);
        }
    }
    if(I2cJobPriorityQueue.JobKeepingTimer != 0u){
        I2cJobPriorityQueue.JobKeepingTimer--;
        if(I2cJobPriorityQueue.JobKeepingTimer == 0u){
            SchM_Enter_I2c_EA_0();
            if(I2cJobPriorityQueue.JobState != I2C_JOB_STATE_READY){
                I2c_JobTimeoutNotification();
            }
            SchM_Exit_I2c_EA_0();
        }
    }
    /* Healing time wait for "bus free" or to overwrite the job state I2C_JOB_STATE_TIMEOUT to final
     * I2C_JOB_STATE_FINISHED from interrupt routine*/

    /* Purpose 1: I2c Job timedout but still I2c hung in between or bus is not getting free,
     *            carryout bus recovery mechanism
     * Purpose 2: I2C Job timedout but interrupts are still pending for some reasons
     *            This is a rare probable case i assume when both i2c main function time and job timeout time are very less.
     *            In this case there would be unavoidable multiple notifications to the user for the same job */
    if(I2cJobPriorityQueue.JobState == I2C_JOB_STATE_TIMEOUT){
        I2cJobPriorityQueue.JobTimeoutHealingCounter--;
        if(I2cJobPriorityQueue.JobTimeoutHealingCounter == 0u){
            /* Carry out bus recovery mechanism here */
            if(I2c_IsBusBusy(controller) == TRUE){
                I2c_RecoverBusBusy(controller);
                /* can also be called I2c_init() here */
            }
            I2cChannelUnit[I2cJobPriorityQueue.Channel].Job[I2cJobPriorityQueue.Job].State = I2C_JOB_STATE_READY;
            I2cJobPriorityQueue.JobState = I2C_JOB_STATE_READY;
        }
    }
    if(I2cJobPriorityQueue.JobState == I2C_JOB_STATE_READY){
        for(uint32 ch = 0; ch < I2C_CH_COUNT; ch++){ /* priority round  */
            controller =    I2c_GetController(I2cJobPriorityQueue.PriorityOrder[ch]);
            channelIndex =  I2c_GetChannelIndex(controller,I2cJobPriorityQueue.PriorityOrder[ch]);
            for(uint32 job = 0; job  < pI2cCfgPtr->I2cController[controller].I2cChannel[channelIndex]->I2cChannelQueueSize; job++){
                if( (I2cJobPriorityQueue.JobState == I2C_JOB_STATE_READY) &&
                    (I2cChannelUnit[I2cJobPriorityQueue.PriorityOrder[ch]].Job[job].State == I2C_JOB_STATE_START)){
                    I2cJobPriorityQueue.Channel = I2cJobPriorityQueue.PriorityOrder[ch];
                    I2cJobPriorityQueue.Job = job;
                    I2cJobPriorityQueue.JobState = I2C_JOB_STATE_START;
                    I2c_StartJob(&I2cChannelUnit[I2cJobPriorityQueue.Channel].Job[I2cJobPriorityQueue.Job]);
                    break; /* One job at a time */
                }
            }
        }
    }
}

/* @file I2c.h */
uint8 I2c_GetActualJobState(I2c_ChannelHandleType channel)
{
    uint8 state = (uint8)I2C_JOB_STATE_NONE;
    if(I2cInitRun == FALSE){
        return state;
    }
    if(channel == I2cJobPriorityQueue.Channel){
        state = (uint8)I2cJobPriorityQueue.JobState;
    }
    return state;
}

