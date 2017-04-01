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

/* ----------------------------[includes]------------------------------------*/

/* @req SWS_Gpt_00293 */
#include "Gpt.h"
#include "Mcu.h"
#include "Gpt_Internal.h"
#include "Arc_Types.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS) /*lint -e961 */
#include "isr.h"
#endif
#include "core_cr4.h"

#include "timer_rti.h"

#include "Os.h" /* Required by ISR() */

/* ----------------------------[private define]------------------------------*/

#if !defined(GPT_ISR_PRIORITY)
#define GPT_ISR_PRIORITY            4u
#endif

#define MEM_START(_ch)				(_ch * 2uL)
#define MEM_TARGET(_ch)				(_ch * 2uL + 1uL)
#define MEM_STOP(_ch)				(_ch * 2uL + 2uL)

#define GPT_COMP_CTRL_COMPSEL_JUMP	4u


/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/

/* lint --e{754} We don't reference all members of the structure */

/* Indexed with HW channel */
uint32 Gpt_Hw_ChannelMemory[GPT_MAXIMUM_CHANNELS * 3uL];


/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/


/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

ISR(Gpt_0_Isr);
ISR(Gpt_1_Isr);
ISR(Gpt_2_Isr);

static void Gpt_Isr(uint8 hwChannel);

/*lint -e{923} */
//struct TAUJ_reg * const Gpt_HwReg = ((struct TAUJ_reg *) (TAUJ_BASE));

ISR(Gpt_0_Isr) {
    Gpt_Isr(1u);
}
ISR(Gpt_1_Isr) {
    Gpt_Isr(2u);
}
ISR(Gpt_2_Isr) {
    Gpt_Isr(3u);
}

#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)	/*lint -e961 */

static void installChannelInterrupt(uint8 Chnl) {
    switch (Chnl) {
        case 1:
            ISR_INSTALL_ISR2("Gpt", Gpt_0_Isr, (IrqType )(RTI_COMPARE_1), GPT_ISR_PRIORITY, 0);
            break;

        case 2:
            ISR_INSTALL_ISR2("Gpt", Gpt_1_Isr, (IrqType )(RTI_COMPARE_2),GPT_ISR_PRIORITY, 0);
            break;

        case 3:
            ISR_INSTALL_ISR2("Gpt", Gpt_2_Isr, (IrqType )(RTI_COMPARE_3), GPT_ISR_PRIORITY, 0);
            break;

        default:
            break;
    }
}
#endif

void Gpt_Hw_Init(const Gpt_ConfigType* ConfigPtr) {
    uint8 hwChannel;

    (void) ConfigPtr; /*lint !e920 */

    uint32 chanCmpMask = 0;

    /* Loop over all configured channels */
    for (uint8 chnlcnt = 0; chnlcnt < GPT_CHANNEL_CNT; chnlcnt++) {

        /* Override Init settings of HW channel so we don't have to
         * adjust in all functions. */
        hwChannel = GET_CONFIG(chnlcnt).GptChannelId;

        Gpt_Global.channelToHwChannel[chnlcnt] = hwChannel + 1;
        Gpt_Global.channelMap[hwChannel + 1] = chnlcnt;

        /* @req SWS_Gpt_00068 */
        hwChannel = ChannelToHwChannel(chnlcnt);

#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
        installChannelInterrupt(hwChannel);
#endif
        /* Disable the hardware interrupts for compare registers. */
        rtiREG1->CLEARINT = (1uL << hwChannel);

        Gpt_Hw_DisableNotification(hwChannel);

        chanCmpMask |= (1u << (GPT_COMP_CTRL_COMPSEL_JUMP * hwChannel));
    }

    Timer_Rt1Init();

    rtiREG1->COMPCTRL |= chanCmpMask;
}

static void Gpt_Isr(uint8 hwChannel) {
    uint8 channel = HwChannelToChannel(hwChannel);

    /* Clear Interrupt */
    rtiREG1->INTFLAG |= (1 << hwChannel);

    if (GPT_CH_MODE_ONESHOT == GET_CONFIG(channel).GptChannelMode ) {
        Gpt_Hw_StopTimer(hwChannel);

        Gpt_Global.Gpt_ChannelState[channel] = GPT_STATE_EXPIRED;

        /* Disable the interrupt */
        rtiREG1->CLEARINT |= (1 << hwChannel);

#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
        /* Report wake up to ECUM */
        if (Gpt_Global.Gpt_WakUpEnable[channel]) {
            EcuM_CheckWakeup(GET_CONFIG(channel).GptWakeupSource);
        }
#endif
    }

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
    /* Notify */
    if (Gpt_Global.Gpt_NotifEnable[channel] && (GET_CONFIG(channel).GptNotification != NULL) ) {
        GET_CONFIG(channel).GptNotification();
    }
#endif

}

#if GPT_DEINIT_API == STD_ON
void Gpt_Hw_DeInit( void ) {
    uint8 hwChannel;

    /* @req SWS_Gpt_00105 */
    for (uint8 chnlcnt = 0; chnlcnt < GPT_CHANNEL_CNT; chnlcnt++) {
        hwChannel = ChannelToHwChannel(chnlcnt);
        rtiREG1->CLEARINT = (1 << hwChannel);
    }

    /* Also disable the counter itself */
    rtiREG1->GCTRL &= ~0x2UL;
}
#endif

#if ( GPT_TIME_ELAPSED_API == STD_ON )
Gpt_ValueType Gpt_Hw_GetTimeElapsed( Gpt_Hw_ChannelType Channel ) {
    Gpt_ValueType val;

    if ( Gpt_Global.Gpt_ChannelState[HwChannelToChannel(Channel)] == GPT_STATE_STOPPED )
    {
        /* @req SWS_Gpt_00297 */
        val = Gpt_Hw_ChannelMemory[MEM_STOP(Channel)] - Gpt_Hw_ChannelMemory[MEM_START(Channel)];
    } else {
        val = rtiREG1->CNT[1].FRCx - Gpt_Hw_ChannelMemory[MEM_START(Channel)];
    }

    return val;
}
#endif

#if ( GPT_TIME_REMAINING_API == STD_ON )
Gpt_ValueType Gpt_Hw_GetTimeRemaining( Gpt_Hw_ChannelType Channel ) {
    Gpt_ValueType val;

    if ( Gpt_Global.Gpt_ChannelState[HwChannelToChannel(Channel)] == GPT_STATE_STOPPED )
    {
        /* @req SWS_Gpt_00303 */
        val = Gpt_Hw_ChannelMemory[MEM_TARGET(Channel)] - Gpt_Hw_ChannelMemory[MEM_STOP(Channel)];
    } else {
        val = Gpt_Hw_ChannelMemory[MEM_TARGET(Channel)] - rtiREG1->CNT[1].FRCx;
    }

    return val;
}
#endif

void Gpt_Hw_StartTimer(Gpt_Hw_ChannelType Channel, Gpt_ValueType Value ) {

    /* @req SWS_Gpt_00274 */
    /* Clear interrupt */
    rtiREG1->INTFLAG |= (1uL << Channel);

    /* Grab the free-running counter */
    uint32 current = rtiREG1->CNT[1].FRCx;

    /* We want a trigger Value ahead so write that into compare for the channel */
    rtiREG1->CMP[Channel].COMPx = current + Value;

    if (GPT_CH_MODE_ONESHOT == GET_CONFIG(HwChannelToChannel(Channel)).GptChannelMode ) {
        rtiREG1->CMP[Channel].UDCPx = 0xffffffffuL;
    } else {
        /* Value added once an for continuous operation */
        rtiREG1->CMP[Channel].UDCPx = Value;
    }

    /* Save current and target value for later */
    Gpt_Hw_ChannelMemory[MEM_TARGET(Channel)] = current + Value;
    Gpt_Hw_ChannelMemory[MEM_START(Channel)] = current;

    /* Enable interrupt */
    rtiREG1->SETINT = (1uL << Channel);
}

void Gpt_Hw_StopTimer(Gpt_Hw_ChannelType Channel) {
    /* @req SWS_Gpt_00013 */

    /* Disable Interrupt */
    rtiREG1->CLEARINT = (1uL << Channel);

    Gpt_Hw_ChannelMemory[MEM_STOP(Channel)] = rtiREG1->CNT[1].FRCx;
}

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
void Gpt_Hw_EnableNotification( Gpt_Hw_ChannelType Channel ) {
    Gpt_Global.Gpt_NotifEnable[Channel] = TRUE;
}

void Gpt_Hw_DisableNotification( Gpt_Hw_ChannelType Channel ) {
    Gpt_Global.Gpt_NotifEnable[Channel] = FALSE;
}
#endif

uint32 Gpt_Arc_GetClock(Gpt_ChannelType Channel) {

    (void) Channel;

    return Timer_Rt1GetClock();
}


