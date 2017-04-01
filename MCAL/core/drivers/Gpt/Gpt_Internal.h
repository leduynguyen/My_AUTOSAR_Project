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

/** @tagSettings DEFAULT_ARCHITECTURE=RH850F1H|JACINTO5|JACINTO6 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#ifndef GPT_INTERNAL_H_
#define GPT_INTERNAL_H_


#if !defined(GPT_ARC_HW_UNIT_CNT)

#if defined(CFG_TMS570)
#define GPT_MAXIMUM_CHANNELS        4u
#elif defined(CFG_RH850F1H)
#define GPT_MAXIMUM_CHANNELS        4u
#endif

/* New style, define it */
#define GPT_ARC_HW_UNIT_CNT			GPT_MAXIMUM_CHANNELS
#endif

#if !defined(GPT_ARC_LOG_UNIT_CNT)
#define GPT_ARC_LOG_UNIT_CNT	GPT_CHANNEL_CNT
#endif

#define IS_TARGET_VALID(_c)      /*lint -save -e685 */  ((_c != 0) && (_c <= 65535)) /*lint -restore */

#define GET_CONFIG(ch)			(*Gpt_Global.config)[ch]



typedef enum {
    GPT_STATE_STOPPED = 0,
    GPT_STATE_RUNNING,
    GPT_STATE_EXPIRED,
    GPT_STATE_INITIALIZED
} Gpt_ChannelStateType;

/**
 * Type that holds all global data for Gpt
 */
typedef struct {
    /* Set if Gpt_Init() have been called */
    boolean initRun;

    /* Gpt driver mode */
    Gpt_ModeType mode;
    /* Our config */
    const Gpt_ConfigType (*config)[GPT_ARC_LOG_UNIT_CNT];

#if ( GPT_WAKEUP_FUNCTIONALITY_API == STD_ON )
    uint8 wakeupEnabled;
#endif

    /* Maps the a physical channel id to configured channel index */
    uint8 channelMap[GPT_ARC_HW_UNIT_CNT];
    uint8 channelToHwChannel[GPT_ARC_LOG_UNIT_CNT];
    Gpt_ChannelStateType Gpt_ChannelState[GPT_ARC_LOG_UNIT_CNT];
    Gpt_ValueType Gpt_ChannelTargetValue[GPT_ARC_LOG_UNIT_CNT];
    boolean Gpt_NotifEnable[GPT_ARC_LOG_UNIT_CNT];
    boolean Gpt_WakUpEnable[GPT_ARC_LOG_UNIT_CNT];

} Gpt_GlobalType;

/*lint -esym(9003,Gpt_Global) */
extern Gpt_GlobalType Gpt_Global;

typedef uint8 Gpt_Hw_ChannelType;

static inline Gpt_ChannelType HwChannelToChannel(Gpt_Hw_ChannelType ch) {
    return Gpt_Global.channelMap[ch];
}
static inline Gpt_Hw_ChannelType ChannelToHwChannel(Gpt_ChannelType ch) {
    return Gpt_Global.channelToHwChannel[ch];
}

/**
 * Initializes all the timers according to the settings in ConfigPtr
 * @param ConfigPtr
 */
void Gpt_Hw_Init(const Gpt_ConfigType* ConfigPtr);

/**
 * Deinitializes all the timers.
 */
void Gpt_Hw_DeInit(void);

/**
 * Retrieves time that has passed from the timer in ticks
 * @param Channel
 * @return
 */
Gpt_ValueType Gpt_Hw_GetTimeElapsed(Gpt_Hw_ChannelType Channel);

/**
 * Retrieves remaining time from the timer in ticks
 * @param Channel
 * @return
 */
Gpt_ValueType Gpt_Hw_GetTimeRemaining(Gpt_Hw_ChannelType Channel);

/**
 * Loads registers with required value in ticks and starts timer.
 * @param Channel
 * @param Value The unit is ticks and not micro- or milliseconds.
 */
void Gpt_Hw_StartTimer(Gpt_Hw_ChannelType Channel, Gpt_ValueType Value);

/**
 * Stops timers and disables (and if necessary clears) interrupts.
 * @param Channel
 */
void Gpt_Hw_StopTimer(Gpt_Hw_ChannelType Channel);

/**
 * Enabling interrupts and notifications
 * @param Channel
 */
void Gpt_Hw_EnableNotification(Gpt_Hw_ChannelType Channel);

/**
 * Disabling interrupts and notifications
 * @param Channel
 */
void Gpt_Hw_DisableNotification(Gpt_Hw_ChannelType Channel);

void Gpt_Hw_SetMode(Gpt_ModeType Mode);
void Gpt_Hw_DisableWakeup(Gpt_Hw_ChannelType Channel);
void Gpt_Hw_EnableWakeup(Gpt_Hw_ChannelType Channel);

#ifdef HOST_TEST
/**
 * @param Channel
 * @return The state of the channel
 */
Gpt_ChannelStateType Gpt_Test_GetChannelState(Gpt_ChannelType Channel);
#endif /* HOST_TEST */

#endif /* GPT_INTERNAL_H_ */
