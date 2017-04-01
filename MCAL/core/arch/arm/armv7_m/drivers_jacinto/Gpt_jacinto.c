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


/** @tagSettings DEFAULT_ARCHITECTURE=JACINTO5|JACINTO6 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/* ----------------------------[information]----------------------------------*/
/*
 *
 *
 * Description:
 *   Implementation of the GPT Driver module for Jacinto 5/6
 *
 * Limitations:
 *   General                        Information
 *   -------------------------------------------
 *   J5 Interrupt for TIM8			Interrupt for timer 8 is not installed
 *	 J6 Timer 2 not correct			Timer 2 registers not accessible
 */

/* ----------------------------[includes]------------------------------------*/

#include "Gpt.h"
#include "Mcu.h"
#include "Gpt_Internal.h"
#include "Gpt_jacinto.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS) /*lint -e961 */
#include "isr.h"
#include "irq_jacinto.h"
#endif
#include "Os.h" /* Required by ISR() */

/* ----------------------------[private define]------------------------------*/

#define GPT_ISR_PRIORITY            4u
#define GPT_COUNTER_RST_VAL			0x00000000U
#define GPT_NO_PRESCAL_VAL			0x00000000U
#define GPT_COMP_RST_VAL			0xFFFFFFFFU
#define GPT_MAX_COUNTER_VAL			0xFFFFFFFFU
#define GPT_DEFAULT_RETURN_VALUE	0u

/**
 * Bit positions in registers
 */
#define TIM_CTRL_SFTRST				0u
#define TIM_CTRL_IDLEMODE			2u
#define TIM_MODE_ST					0u
#define TIM_MODE_AR					1u
#define TIM_MODE_PTV				2u
#define TIM_MODE_PRE				5u
#define TIM_MODE_CE					6u
#define TIM_IRQ_MAT	        		0u
#define TIM_IRQ_OVF	        		1u
#define TIM_IRQ_TCAR          		2u
#define TIM_CONFIG_SFT				1u

/**
 * Timer read and write access mode
 */
#define TIM_REG_RNP_WNP 			8uL

/**
 * Timer autoreload modes
 */
#define TIM_ONESHOT_MODE 			0uL
#define TIM_CONTINIOUS_MODE 		2uL

/**
 * Channels
 */
#define GPT_CHANNEL_0              	0uL
#define GPT_CHANNEL_1               1uL
#define GPT_CHANNEL_2               2uL
#define GPT_CHANNEL_3               3uL
#define GPT_CHANNEL_4               4uL
#define GPT_CHANNEL_5               5uL
#define GPT_CHANNEL_6               6uL
#define GPT_CHANNEL_7               7uL
#define GPT_CHANNEL_8               8uL
#define GPT_CHANNEL_9               9uL
#define GPT_CHANNEL_10              10uL
#define GPT_CHANNEL_11              11uL
#define GPT_CHANNEL_12              12uL
#define GPT_CHANNEL_13              13uL
#define GPT_CHANNEL_14              14uL
#define GPT_CHANNEL_15              15uL

/* ----------------------------[private macro]-------------------------------*/

/**
 * Translating values from the channel number to a pointer in the hardware pointer
 */
#define GET_TIM_MODULE(_c)          (TIM_PTR[(_c) % (GPT_MAXIMUM_CHANNELS)])

/**
 * Bit values
 */
#define TIM_DISABLE_COUNTER			(1uL<<TIM_CTRL_SFTRST)
#define TIM_FORCE_IDLE_MODE			(0uL<<TIM_CTRL_IDLEMODE)
#define TIM_IRQSETCLR_TCAR			(1uL<<TIM_IRQ_TCAR)
#define TIM_IRQSETCLR_OVF			(1uL<<TIM_IRQ_OVF)
#define TIM_IRQSETCLR_MAT			(1uL<<TIM_IRQ_MAT)
#define TIM_IRQWAKEUPENA_TCAR_SET	(1uL<<TIM_IRQ_TCAR)
#define TIM_IRQWAKEUPENA_OVF_SET	(1uL<<TIM_IRQ_OVF)
#define TIM_IRQWAKEUPENA_MAT_SET	(1uL<<TIM_IRQ_MAT)
#define TIM_IRQWAKEUPENA_TCAR_CLEAR	(0uL<<TIM_IRQ_TCAR)
#define TIM_IRQWAKEUPENA_OVF_CLEAR	(0uL<<TIM_IRQ_OVF)
#define TIM_IRQWAKEUPENA_MAT_CLEAR	(0uL<<TIM_IRQ_MAT)
#define TIM_IRQSTATUS_TCAR_CLR		(1uL<<TIM_IRQ_TCAR)
#define TIM_IRQSTATUS_OVF_CLR		(1uL<<TIM_IRQ_OVF)
#define TIM_IRQSTATUS_MAT_CLR		(1uL<<TIM_IRQ_MAT)
#define TIM_MODE_PRESCALAR_EN		(1uL<<TIM_MODE_PRE)
#define TIM_MODE_STOP				(1uL<<TIM_MODE_ST)
#define TIM_MODE_START				(1uL<<TIM_MODE_ST)
#define TIM_CONFIG_SFT_EN			(1uL<<TIM_CONFIG_SFT)

/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/** Prototypes for ISR*/
ISR(Gpt_0_Isr);
ISR(Gpt_1_Isr);
ISR(Gpt_2_Isr);
ISR(Gpt_3_Isr);
ISR(Gpt_4_Isr);
ISR(Gpt_5_Isr);
ISR(Gpt_6_Isr);
ISR(Gpt_7_Isr);
#if defined(CFG_JAC6)
ISR(Gpt_8_Isr);
ISR(Gpt_9_Isr);
ISR(Gpt_10_Isr);
ISR(Gpt_11_Isr);
ISR(Gpt_12_Isr);
ISR(Gpt_13_Isr);
ISR(Gpt_14_Isr);
ISR(Gpt_15_Isr);
#endif

static void Gpt_Isr(uint8 Chnl);

/* ----------------------------[private variables]---------------------------*/

// Global config
/*lint -save -e785 Misra 2012 9.3  Too few initializers.
 * Just the necessary record are initialized.*/
Gpt_GlobalType Gpt_Global = {
    .initRun = STD_OFF,
    .mode = GPT_MODE_UNINTIALIZED,
    .config = NULL,
};
/*lint -restore*/

/* ----------------------------[private functions]---------------------------*/

/*lint -save -e{923} --e{843}  Variable 'TIM_PTR' could be declared as const \
 * cast from unsigned int to pointer MISRA 2004 11.1 11.3 2012 11.4 11.6 \
 * Integer to pointer casting is necessary to set SFR of Microcontroller. */
static TIM_HwRegType *TIM_PTR[] = {
        TIM1_REG, TIM2_REG, TIM3_REG, TIM4_REG, TIM5_REG, TIM6_REG, TIM7_REG, TIM8_REG
#if defined(CFG_JAC6)
        , TIM9_REG, TIM10_REG, TIM11_REG, TIM12_REG, TIM13_REG, TIM14_REG, TIM15_REG, TIM16_REG
#endif
};
/*lint -restore */

ISR(Gpt_0_Isr) {
    Gpt_Isr(GPT_CHANNEL_0);
}
ISR(Gpt_1_Isr) {
    Gpt_Isr(GPT_CHANNEL_1);
}
ISR(Gpt_2_Isr) {
    Gpt_Isr(GPT_CHANNEL_2);
}
ISR(Gpt_3_Isr) {
    Gpt_Isr(GPT_CHANNEL_3);
}
ISR(Gpt_4_Isr) {
    Gpt_Isr(GPT_CHANNEL_4);
}
ISR(Gpt_5_Isr) {
    Gpt_Isr(GPT_CHANNEL_5);
}
ISR(Gpt_6_Isr) {
    Gpt_Isr(GPT_CHANNEL_6);
}
ISR(Gpt_7_Isr) {
    Gpt_Isr(GPT_CHANNEL_7);
}
#if defined(CFG_JAC6)
ISR(Gpt_8_Isr) {
    Gpt_Isr(GPT_CHANNEL_8);
}
ISR(Gpt_9_Isr) {
    Gpt_Isr(GPT_CHANNEL_9);
}
ISR(Gpt_10_Isr) {
    Gpt_Isr(GPT_CHANNEL_10);
}
ISR(Gpt_11_Isr) {
    Gpt_Isr(GPT_CHANNEL_11);
}
ISR(Gpt_12_Isr) {
    Gpt_Isr(GPT_CHANNEL_12);
}
ISR(Gpt_13_Isr) {
    Gpt_Isr(GPT_CHANNEL_13);
}
ISR(Gpt_14_Isr) {
    Gpt_Isr(GPT_CHANNEL_14);
}
ISR(Gpt_15_Isr) {
    Gpt_Isr(GPT_CHANNEL_15);
}
#endif


#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
#if defined(CFG_JAC6)
/**
 * installing remaining J6 interrupts in another function to satisfy MVG
 * @param Chnl
 */
static void installJ6ChannelInterrupt(uint8 Chnl)
{
    switch (Chnl) {
        case GPT_CHANNEL_7:
            ISR_INSTALL_ISR2("Gpt", Gpt_7_Isr, (IrqType )(TINT8_IRQ), GPT_ISR_PRIORITY, 0);
            break;
        case GPT_CHANNEL_8:
            ISR_INSTALL_ISR2("Gpt", Gpt_8_Isr, (IrqType )(TINT9_IRQ), GPT_ISR_PRIORITY, 0);
            break;
        case GPT_CHANNEL_9:
            ISR_INSTALL_ISR2("Gpt", Gpt_9_Isr, (IrqType )(TINT10_IRQ), GPT_ISR_PRIORITY, 0);
            break;
        case GPT_CHANNEL_10:
            ISR_INSTALL_ISR2("Gpt", Gpt_10_Isr, (IrqType )(TINT11_IRQ), GPT_ISR_PRIORITY, 0);
            break;
        case GPT_CHANNEL_11:
            ISR_INSTALL_ISR2("Gpt", Gpt_11_Isr, (IrqType )(TINT12_IRQ), GPT_ISR_PRIORITY, 0);
            break;
        case GPT_CHANNEL_12:
            ISR_INSTALL_ISR2("Gpt", Gpt_12_Isr, (IrqType )(TINT13_IRQ), GPT_ISR_PRIORITY, 0);
            break;
        case GPT_CHANNEL_13:
            ISR_INSTALL_ISR2("Gpt", Gpt_13_Isr, (IrqType )(TINT14_IRQ), GPT_ISR_PRIORITY, 0);
            break;
        case GPT_CHANNEL_14:
            ISR_INSTALL_ISR2("Gpt", Gpt_14_Isr, (IrqType )(TINT15_IRQ), GPT_ISR_PRIORITY, 0);
            break;
        case GPT_CHANNEL_15:
            ISR_INSTALL_ISR2("Gpt", Gpt_15_Isr, (IrqType )(TINT16_IRQ), GPT_ISR_PRIORITY, 0);
            break;
    default:
        break;
    }
}
#endif /* defined(CFG_JAC6) */

/**
 * Installs Interrupts for timers
 * @param Chnl
 * @desc Installing interrupts during initialization
 */
static void installChannelInterrupt(uint8 Chnl)
{
    switch (Chnl) {
        case GPT_CHANNEL_0:
            ISR_INSTALL_ISR2("Gpt", Gpt_0_Isr, (IrqType )(TINT1_IRQ), GPT_ISR_PRIORITY, 0);
            break;

        case GPT_CHANNEL_1:
            ISR_INSTALL_ISR2("Gpt", Gpt_1_Isr, (IrqType )(TINT2_IRQ), GPT_ISR_PRIORITY, 0);
            break;

        case GPT_CHANNEL_2:
            ISR_INSTALL_ISR2("Gpt", Gpt_2_Isr, (IrqType )(TINT3_IRQ), GPT_ISR_PRIORITY, 0);
            break;

        case GPT_CHANNEL_3:
            ISR_INSTALL_ISR2("Gpt", Gpt_3_Isr, (IrqType )(TINT4_IRQ), GPT_ISR_PRIORITY, 0);
            break;

        case GPT_CHANNEL_4:
            ISR_INSTALL_ISR2("Gpt", Gpt_4_Isr, (IrqType )(TINT5_IRQ), GPT_ISR_PRIORITY, 0);
            break;

        case GPT_CHANNEL_5:
            ISR_INSTALL_ISR2("Gpt", Gpt_5_Isr, (IrqType )(TINT6_IRQ), GPT_ISR_PRIORITY, 0);
            break;

        case GPT_CHANNEL_6:
            ISR_INSTALL_ISR2("Gpt", Gpt_6_Isr, (IrqType )(TINT7_IRQ), GPT_ISR_PRIORITY, 0);
            break;

            /* IMPROVEMENT: Install Interrupt for timer 8 for J5*/
        default:
            break;
    }
}
#endif /* !defined(CFG_DRIVERS_USE_CONFIG_ISRS) */

/**
 * ISR for all GPT channels
 * @param Chnl
 */
static void Gpt_Isr(uint8 Chnl) {

    uint8 channel = HwChannelToChannel(Chnl);
    TIM_HwRegType *reg = GET_TIM_MODULE(Chnl);

    /* @req SWS_Gpt_00206 */
    /* @req SWS_Gpt_00327 */
    /* Clear any pending interrupts on read */
    reg->GPT_IRQSTATUS = TIM_IRQSETCLR_MAT | TIM_IRQSETCLR_OVF | TIM_IRQSETCLR_TCAR;

    /* @req SWS_Gpt_00185 */
    if (GPT_CH_MODE_ONESHOT == GET_CONFIG(channel).GptChannelMode ) {

        Gpt_Global.Gpt_ChannelState[channel] = GPT_STATE_EXPIRED;

#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
        /* Report wake up to ECUM */
        if (Gpt_Global.Gpt_WakUpEnable[channel] == TRUE) {
            EcuM_CheckWakeup(GET_CONFIG(channel).GptWakeupSource);
            /* @req SWS_Gpt_00326 */
        }
#endif
    }

    /* @req SWS_Gpt_00086 */
    if (Gpt_Global.Gpt_NotifEnable[channel] == TRUE) {
        GET_CONFIG(channel).GptNotification();
    }
}

/* ----------------------------[public functions]----------------------------*/

void Gpt_Hw_Init(const Gpt_ConfigType* ConfigPtr) {
    TIM_HwRegType * reg;
    uint8 phyChnl;
    (void) ConfigPtr; /*lint !e920 */

    for (uint8 chnlcnt = 0; (chnlcnt < GPT_CHANNEL_CNT); chnlcnt++) {
#if defined(CFG_JAC6)
        if(GPT_CHANNEL_1 != GET_CONFIG(chnlcnt).GptChannelId) { //IMPROVEMENT: Timer 2 registers not accessible
#endif
            /* @req SWS_Gpt_00068 */
            phyChnl = ChannelToHwChannel(chnlcnt);
            reg =  GET_TIM_MODULE(phyChnl);
            uint32 u32Prescaler = GET_CONFIG(chnlcnt).GptChannelPrescale;

            /* Enable software reset */
            reg->GPT_CONFIG 	= 	TIM_CONFIG_SFT_EN;
            /* Perform a software reset */
            reg->GPT_CTRL 		= 	TIM_FORCE_IDLE_MODE | TIM_DISABLE_COUNTER;
            while ((reg->GPT_CTRL & TIM_DISABLE_COUNTER) != 0uL){
                /* Busy wait for the software reset to finish */
            }

            uint32 modeRegValue = 0;

            if (((Gpt_ChannelClockDivisorType) u32Prescaler) != GPT_CHANNEL_DIVISOR_1) {
                modeRegValue |= TIM_MODE_PRESCALAR_EN;
                modeRegValue |= u32Prescaler << TIM_MODE_PTV;
            } else {
                /* Nothing to set if prescaler is 1. */
            }

            if (GET_CONFIG(chnlcnt).GptChannelMode == GPT_CH_MODE_CONTINUOUS) {
                modeRegValue |= TIM_CONTINIOUS_MODE;
            } else {
                /* Nothing to set for oneshot mode. */
            }

            reg->GPT_MODE = modeRegValue;

            reg->GPT_IRQSTATUS 	= 	TIM_IRQSETCLR_MAT | TIM_IRQSETCLR_OVF | TIM_IRQSETCLR_TCAR; //Clear any pending interrupts on read
            reg->GPT_IRQENACLR 	= 	TIM_IRQSETCLR_MAT | TIM_IRQSETCLR_OVF | TIM_IRQSETCLR_TCAR; //Disable interrupts

#if (defined(CFG_JAC5) || defined(CFG_JAC5E))
            /* Disable software reset and set posted mode to inactive.
             * The READ_MODE bit does not exist on Jacinto 5 and Jacinto 5 Eco,
             * it is reserved. */
            reg->GPT_CONFIG 	=	0;
#elif defined(CFG_JAC6)
            /* Disable software reset, set posted mode to inactive and set READ_MODE to
             * read non posted. */
            reg->GPT_CONFIG 	= 	TIM_REG_RNP_WNP;
#else
#error GPT - Driver not implemented for the used MCU
#endif

            reg->GPT_COUNTER 	= 	GPT_COUNTER_RST_VAL; //Resetting counter value
            reg->GPT_COMPARE 	= 	GPT_COMP_RST_VAL; //Resetting compare value

#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
            installChannelInterrupt(phyChnl);
#if defined(CFG_JAC6)
            installJ6ChannelInterrupt(phyChnl);
#endif /* defined(CFG_JAC6) */
#endif /* !defined(CFG_DRIVERS_USE_CONFIG_ISRS) */
#if defined(CFG_JAC6)
        } /* IMPROVEMENT: Timer 2 registers not accessible if(GPT_CHANNEL_1 != Gpt_Global.config[chnlcnt].GptChannelId) */
#endif
    } /* for (uint8 chnlcnt = 0; (chnlcnt < GPT_CHANNEL_CNT); chnlcnt++) */
}

/* @req SWS_Gpt_00105 */
#if GPT_DEINIT_API == STD_ON
void Gpt_Hw_DeInit( void ) {
    TIM_HwRegType * reg;

    /* @req SWS_Gpt_00008 */
    for (uint8 chnlcnt = 0; (chnlcnt < GPT_CHANNEL_CNT); chnlcnt++) {
#if defined(CFG_JAC6)
        if(GPT_CHANNEL_1 != GET_CONFIG(chnlcnt).GptChannelId) { //IMPROVEMENT: Timer 2 registers not accessible
#endif
            /* @req SWS_Gpt_00068 */
            reg    = GET_TIM_MODULE(ChannelToHwChannel(chnlcnt));

            /* @req SWS_Gpt_00162 */
            reg->GPT_MODE 		= ~TIM_MODE_STOP;	//Stop counter
            reg->GPT_COUNTER 	= GPT_COUNTER_RST_VAL; //Resetting counter value
            reg->GPT_COMPARE 	= GPT_COMP_RST_VAL; //Resetting compare value
            reg->GPT_IRQSTATUS 	= TIM_IRQSETCLR_MAT | TIM_IRQSETCLR_OVF | TIM_IRQSETCLR_TCAR; //Clear any pending interrupts on read
            reg->GPT_IRQENACLR 	= TIM_IRQSETCLR_MAT | TIM_IRQSETCLR_OVF | TIM_IRQSETCLR_TCAR; //Disable interrupts
            reg->GPT_CTRL 		= TIM_FORCE_IDLE_MODE | TIM_DISABLE_COUNTER; //Soft reset counter
#if defined(CFG_JAC6)
        } /* IMPROVEMENT: Timer 2 registers not accessible if(GPT_CHANNEL_1 != Gpt_Global.config[chnlcnt].GptChannelId) */
#endif
    } /* for (uint8 chnlcnt = 0; (chnlcnt < GPT_CHANNEL_CNT); chnlcnt++) */
}
#endif

#if ( GPT_TIME_ELAPSED_API == STD_ON )
Gpt_ValueType Gpt_Hw_GetTimeElapsed( Gpt_Hw_ChannelType Channel ) {
    const TIM_HwRegType * reg;
    uint8 chnlidx;
    Gpt_ValueType retVal;

    reg     = GET_TIM_MODULE(Channel);
    chnlidx = Gpt_Global.channelMap[Channel];

    /*lint -e{9005} volatile qualifier casted away to have the proper return value Misra 11.8 */
    retVal = (Gpt_ValueType)(reg->GPT_COUNTER) - (GPT_MAX_COUNTER_VAL - (Gpt_ValueType)(Gpt_Global.Gpt_ChannelTargetValue[chnlidx]));
    /*lint -restore*/
    return retVal;

}
#endif

#if ( GPT_TIME_REMAINING_API == STD_ON )
Gpt_ValueType Gpt_Hw_GetTimeRemaining( Gpt_Hw_ChannelType Channel ) {
    const TIM_HwRegType * reg;
    Gpt_ValueType retVal;

    reg     = GET_TIM_MODULE(Channel);

    /*lint -e{9005} volatile qualifier casted away to have the proper return value Misra 11.8 */
    retVal = (GPT_MAX_COUNTER_VAL - (Gpt_ValueType)(reg->GPT_COUNTER));
    /*lint -restore*/
    return retVal;
}
#endif

void Gpt_Hw_StartTimer(Gpt_Hw_ChannelType Channel, Gpt_ValueType Value) {
    TIM_HwRegType *reg;
    reg     = GET_TIM_MODULE(Channel);

    /*  @req SWS_Gpt_00274 */
    //Lint warnings disable pointer would not result in out-of-bound pointer. Verified the maximum possible value for offset (2).
    /*lint -save -e662 -e661 */
    reg->GPT_MODE 		&= 	~TIM_MODE_STOP;	//Stop counter
    reg->GPT_COUNTER  	= 	(GPT_MAX_COUNTER_VAL - Value); //Enable match
    reg->GPT_RELOAD		= 	(GPT_MAX_COUNTER_VAL - Value); //Set interval
    reg->GPT_IRQENASET 	= 	TIM_IRQSETCLR_MAT | TIM_IRQSETCLR_OVF | TIM_IRQSETCLR_TCAR; //Enable interrupts
    reg->GPT_MODE 		|= 	TIM_MODE_START;//Start counter
    /*lint -restore*/
}

void Gpt_Hw_StopTimer(Gpt_Hw_ChannelType Channel) {
    TIM_HwRegType *reg;
    reg     = GET_TIM_MODULE(Channel);

    //Lint warnings disable pointer would not result in out-of-bound pointer. Verified the maximum possible value for offset (2).
    /*lint -save -e662 -e661 */
    reg->GPT_IRQSTATUS = TIM_IRQSETCLR_MAT | TIM_IRQSETCLR_OVF | TIM_IRQSETCLR_TCAR; //Clear any pending interrupts on read
    reg->GPT_IRQENACLR = TIM_IRQSETCLR_MAT | TIM_IRQSETCLR_OVF | TIM_IRQSETCLR_TCAR; //Disable interrupts
    /* @req SWS_Gpt_00013 */
    reg->GPT_MODE &= ~TIM_MODE_STOP;	//Stop counter
    /*lint -restore */
}

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
void Gpt_Hw_EnableNotification( Gpt_Hw_ChannelType Channel ) {
    TIM_HwRegType *reg;
    reg     = GET_TIM_MODULE(Channel);

    reg->GPT_IRQENASET = TIM_IRQSETCLR_MAT | TIM_IRQSETCLR_OVF | TIM_IRQSETCLR_TCAR; //Enable interrupts
}
#endif

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
void Gpt_Hw_DisableNotification( Gpt_Hw_ChannelType Channel ) {
    TIM_HwRegType *reg;
    reg     = GET_TIM_MODULE(Channel);

    reg->GPT_IRQENACLR = TIM_IRQSETCLR_MAT | TIM_IRQSETCLR_OVF | TIM_IRQSETCLR_TCAR; //Disable interrupts
}
#endif
