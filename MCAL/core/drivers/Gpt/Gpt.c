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

/** @tagSettings DEFAULT_ARCHITECTURE=RH850F1H|TMS570|JACINTO5|JACINTO6 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/* ----------------------------[includes]------------------------------------*/

#include <string.h>

/* @req SWS_Gpt_00293 */
/* @req SWS_Gpt_00331 Notification support */
#include "Gpt.h"
#include "Gpt_Internal.h"
#if defined(USE_DET)
#include "Det.h"
#endif

// General requirements implemented/inspected
/* @req SWS_Gpt_00352  */
/* @req SWS_Gpt_00113  */
/* @req SWS_Gpt_00114  */
/* @req SWS_Gpt_00115  */
/* @req SWS_Gpt_00116  */
/* @req SWS_Gpt_00117  */
/* @req SWS_Gpt_00118  */
/* @req SWS_Gpt_00155  */
/* @req SWS_Gpt_00156  */
/* @req SWS_Gpt_00323  */
/* @req SWS_Gpt_00360  */
/* @req SWS_Gpt_00359  */
/* @req SWS_Gpt_00342  */
/* @req SWS_Gpt_00270  */
/* @req SWS_Gpt_00309  */
/* @req SWS_Gpt_00329  */
/* @req SWS_Gpt_00357  */
/* @req SWS_Gpt_00362  */
/* @req SWS_Gpt_00209 Each channel shall provide its own notification if configured */
/* @req SWS_Gpt_00278 Partially supported, no DEM. */
/* @req SWS_Gpt_00233  */
/* @req SWS_Gpt_00308  */
/* @req SWS_Gpt_00186  */ /* Timer in continuos mode will start counting up from a reload value (Max - TargetValue) till Maximum ex incase of JACINTO.
 * This in essence provides same interval as if counting from 0 till target value. After reaching Max (i.e completing the interval) it is reset to reload value */
/* @req SWS_Gpt_00330 */ /* Timer reload value can be set to 0 to provide a free running counter for maximum duration possible */
/* @req SWS_Gpt_00375  */
#if defined(USE_DET) && (GPT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/* ----------------------------[private define]------------------------------*/

#define DEFAULT_RETURN_VALUE	0

/* ----------------------------[private macro]-------------------------------*/

#define IS_CHANNEL_VALID(_c)        (((GPT_CHANNELS_CONFIGURED & (1u << _c))!=0) && (_c < GPT_ARC_LOG_UNIT_CNT))
/* @req SWS_Gpt_00332 */
#if ( GPT_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
        (void)  Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
          return; \
        }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
          return (_rv); \
        }

#define VALID_CHANNEL(_ch)      ( Gpt_Global.configured & (1u<<(_ch)) )

#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_W_RV(_exp,_api,_err,_rv )
#endif

/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
// Global config
Gpt_GlobalType Gpt_Global;

/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

#if (GPT_VERSION_INFO_API == STD_ON)
/* @req SWS_Gpt_00279 */
void Gpt_GetVersionInfo(Std_VersionInfoType* VersionInfoPtr) {

    const Std_VersionInfoType _Gpt_VersionInfo = {
            .vendorID = (uint16) GPT_VENDOR_ID,
            .moduleID = (uint16) GPT_MODULE_ID,
            .sw_major_version = (uint8)GPT_SW_MAJOR_VERSION,
            .sw_minor_version = (uint8)GPT_SW_MINOR_VERSION,
            .sw_patch_version = (uint8)GPT_SW_PATCH_VERSION,
    };

    /* @req SWS_Gpt_00338 **/
    VALIDATE( (VersionInfoPtr != NULL), GPT_GETVERSIONINFO_SERVICE_ID, GPT_E_PARAM_POINTER );

    memcpy(VersionInfoPtr, &_Gpt_VersionInfo, sizeof(Std_VersionInfoType));
}
#endif /* (GPT_VERSION_INFO_API == STD_ON) */

/* @req SWS_Gpt_00280 */
/* @req SWS_Gpt_00257 */
void Gpt_Init(const Gpt_ConfigType* ConfigPtr) {
    uint8 hwCh;

    /* @req SWS_Gpt_00307 */
    VALIDATE ((STD_OFF == Gpt_Global.initRun), GPT_INIT_SERVICE_ID, GPT_E_ALREADY_INITIALIZED);
    /* @req SWS_Gpt_00294 */
    VALIDATE((ConfigPtr != NULL), GPT_INIT_SERVICE_ID, GPT_E_PARAM_POINTER);

    /* @req SWS_Gpt_00107 */
    /* @req SWS_Gpt_00258 */
    memset(&Gpt_Global, 0, sizeof(Gpt_Global));

    /* @req SWS_Gpt_00006 */
    Gpt_Global.config = (const Gpt_ConfigType (*)[GPT_ARC_LOG_UNIT_CNT]) ConfigPtr; /*lint !e929 !e740 !e826 */

    for (uint8 ch = 0; ch < GPT_ARC_LOG_UNIT_CNT; ch++) {
        hwCh = GET_CONFIG(ch).GptChannelId;

        Gpt_Global.channelToHwChannel[ch] = hwCh;
        Gpt_Global.channelMap[hwCh] = ch;

        Gpt_Global.Gpt_ChannelState[ch] = GPT_STATE_INITIALIZED;
    }

    Gpt_Hw_Init(ConfigPtr);

    /* @req SWS_Gpt_00339 */
    Gpt_Global.mode = GPT_MODE_NORMAL;
    Gpt_Global.initRun = STD_ON;
}

/* @req SWS_Gpt_00194 */
#if GPT_DEINIT_API == STD_ON
/* @req SWS_Gpt_00281 */
void Gpt_DeInit( void ) {

    /* @req SWS_Gpt_00220 */
    VALIDATE ((STD_ON == Gpt_Global.initRun), GPT_DEINIT_SERVICE_ID, GPT_E_UNINIT);

    /* @req SWS_Gpt_00008 */
    for (uint8 chnlcnt = 0; chnlcnt < GPT_ARC_LOG_UNIT_CNT; chnlcnt++) {
        /* @req SWS_Gpt_00234 */
        VALIDATE(( GPT_STATE_RUNNING != Gpt_Global.Gpt_ChannelState[chnlcnt]),GPT_DEINIT_SERVICE_ID,GPT_E_BUSY);
    }

    Gpt_Hw_DeInit();

    Gpt_Global.mode = GPT_MODE_UNINTIALIZED;
    /* @req SWS_Gpt_00363 */
    Gpt_Global.initRun = STD_OFF;
}
#endif


/* @req SWS_Gpt_00195 */
#if ( GPT_TIME_ELAPSED_API == STD_ON )
/* @req SWS_Gpt_00282 */
Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel ) {
    /* @req SWS_Gpt_00222 */
    VALIDATE_W_RV((STD_ON == Gpt_Global.initRun), GPT_GETTIMEELAPSED_SERVICE_ID, GPT_E_UNINIT, DEFAULT_RETURN_VALUE);

    /* @req SWS_Gpt_00210 */
    VALIDATE_W_RV(IS_CHANNEL_VALID(Channel), GPT_GETTIMEELAPSED_SERVICE_ID, GPT_E_PARAM_CHANNEL, DEFAULT_RETURN_VALUE); /*lint !e731*/

    /*lint -save -e{661} -e{662} channels are being checked to be in valid range before use*/
    if (GPT_STATE_INITIALIZED == Gpt_Global.Gpt_ChannelState[Channel])
    {
        /* @req SWS_Gpt_00295 */
        return DEFAULT_RETURN_VALUE;
    }

    /*lint -save -e{661} -e{662} channels are being checked to be in valid range before use*/
    /* @req SWS_Gpt_00299 */ // Expired - Counter Freeze at target
    if ( (GPT_CH_MODE_ONESHOT == GET_CONFIG(Channel).GptChannelMode) &&
         (GPT_STATE_EXPIRED == Gpt_Global.Gpt_ChannelState[Channel])) {
        return Gpt_Global.Gpt_ChannelTargetValue[Channel];
    }

    /* @req SWS_Gpt_00010 */
    /* @req SWS_Gpt_00297 */ // Stopped
    /* @req SWS_Gpt_00361 */
    return Gpt_Hw_GetTimeElapsed(ChannelToHwChannel(Channel));
}

#endif

/* @req SWS_Gpt_00196 */
#if ( GPT_TIME_REMAINING_API == STD_ON )
/* @req SWS_Gpt_00283 */
Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel ) {

    /* @req SWS_Gpt_00223 */
    VALIDATE_W_RV((STD_ON == Gpt_Global.initRun), GPT_GETTIMEREMAINING_SERVICE_ID, GPT_E_UNINIT, DEFAULT_RETURN_VALUE);

    /* @req SWS_Gpt_00211 */
    VALIDATE_W_RV(IS_CHANNEL_VALID(Channel), GPT_GETTIMEREMAINING_SERVICE_ID, GPT_E_PARAM_CHANNEL, DEFAULT_RETURN_VALUE);

    /*lint -save -e{661} -e{662} channels are being checked to be in valid range before use*/
    if (GPT_STATE_INITIALIZED == Gpt_Global.Gpt_ChannelState[Channel])
    {
        /* @req SWS_Gpt_00301 */
        return DEFAULT_RETURN_VALUE;
    }

    /*lint -save -e{661} -e{662} channels are being checked to be in valid range before use*/
    /* @req SWS_Gpt_00305 */ // Expired - Counter Freeze at target
    if ((GPT_CH_MODE_ONESHOT == GET_CONFIG(Channel).GptChannelMode) &&
            (GPT_STATE_EXPIRED == Gpt_Global.Gpt_ChannelState[Channel])) {
        return DEFAULT_RETURN_VALUE;
    }
    /* @req SWS_Gpt_00083 */
    /* @req SWS_Gpt_00303 */ // Stopped
    return Gpt_Hw_GetTimeRemaining(ChannelToHwChannel(Channel));
}
#endif

/* @req SWS_Gpt_00284 */
void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value) {

    /* @req SWS_Gpt_00224 */
    VALIDATE((STD_ON == Gpt_Global.initRun), GPT_STARTTIMER_SERVICE_ID, GPT_E_UNINIT);

    /* @req SWS_Gpt_00212 */
    VALIDATE(IS_CHANNEL_VALID(Channel), GPT_STARTTIMER_SERVICE_ID, GPT_E_PARAM_CHANNEL);

    /* @req SWS_Gpt_00218 */
    VALIDATE(IS_TARGET_VALID(Value), GPT_STARTTIMER_SERVICE_ID, GPT_E_PARAM_VALUE);

    /*lint -save -e{661} -e{662} channels are being checked to be in valid range before use*/
    /* @req SWS_Gpt_00084 */
    VALIDATE((GPT_STATE_RUNNING != Gpt_Global.Gpt_ChannelState[Channel]), GPT_STARTTIMER_SERVICE_ID, GPT_E_BUSY);

    /*lint -save -e{661} -e{662} channels are being checked to be in valid range before use*/
    Gpt_Global.Gpt_ChannelTargetValue[Channel] = Value;

    Gpt_Hw_StartTimer(ChannelToHwChannel(Channel), Value);

    /* !req SWS_Gpt_00275 */

    /*lint -save -e{661} -e{662} channels are being checked to be in valid range before use*/
    /* @req SWS_Gpt_00364 */
    Gpt_Global.Gpt_ChannelState[Channel] = GPT_STATE_RUNNING;
}

/* @req SWS_Gpt_00285 */
void Gpt_StopTimer(Gpt_ChannelType Channel) {

    /* @req SWS_Gpt_00225 */
    VALIDATE((STD_ON == Gpt_Global.initRun), GPT_STOPTIMER_SERVICE_ID, GPT_E_UNINIT);

    /* @req SWS_Gpt_00213 */
    VALIDATE(IS_CHANNEL_VALID(Channel), GPT_STOPTIMER_SERVICE_ID, GPT_E_PARAM_CHANNEL);

    Gpt_Hw_StopTimer(ChannelToHwChannel(Channel));

    /*lint -save -e{661} -e{662} channels are being checked to be in valid range before use*/
    if (GPT_STATE_RUNNING != Gpt_Global.Gpt_ChannelState[Channel]) {
        /* @req SWS_Gpt_00099 */
        /* @req SWS_Gpt_00344 */
        return;
    }

    /*lint -save -e{661} -e{662} channels are being checked to be in valid range before use*/
    /* @req SWS_Gpt_00343 */
    Gpt_Global.Gpt_ChannelState[Channel] = GPT_STATE_STOPPED;

}

/* @req SWS_Gpt_00199 */
/* @req SWS_Gpt_00200 */
#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
/* @req SWS_Gpt_00286 */
void Gpt_EnableNotification( Gpt_ChannelType Channel ) {

    /* @req SWS_Gpt_00226 */
    VALIDATE((STD_ON == Gpt_Global.initRun), GPT_ENABLENOTIFICATION_SERVICE_ID, GPT_E_UNINIT);

    /* @req SWS_Gpt_00214 */
    VALIDATE(IS_CHANNEL_VALID(Channel), GPT_ENABLENOTIFICATION_SERVICE_ID, GPT_E_PARAM_CHANNEL);

    /* @req SWS_Gpt_00377 */
    VALIDATE((NULL != GET_CONFIG(Channel).GptNotification), GPT_ENABLENOTIFICATION_SERVICE_ID, GPT_E_PARAM_CHANNEL);

    Gpt_Hw_EnableNotification(ChannelToHwChannel(Channel));

    /*lint -save -e{661} -e{662} channels are being checked to be in valid range before use*/
    /* @req SWS_Gpt_00014 */
    Gpt_Global.Gpt_NotifEnable[Channel] = TRUE;

}

/* @req SWS_Gpt_00287 */
void Gpt_DisableNotification( Gpt_ChannelType Channel ) {

    /* @req SWS_Gpt_00227 */
    VALIDATE((STD_ON == Gpt_Global.initRun), GPT_DISABLENOTIFICATION_SERVICE_ID, GPT_E_UNINIT);

    /* @req SWS_Gpt_00217 */
    VALIDATE(IS_CHANNEL_VALID(Channel), GPT_DISABLENOTIFICATION_SERVICE_ID, GPT_E_PARAM_CHANNEL);

    /* @req SWS_Gpt_00379 */
    VALIDATE((NULL != GET_CONFIG(Channel).GptNotification), GPT_DISABLENOTIFICATION_SERVICE_ID, GPT_E_PARAM_CHANNEL);

    Gpt_Hw_DisableNotification(ChannelToHwChannel(Channel));

    /*lint -save -e{661} -e{662} channels are being checked to be in valid range before use*/
    /* @req SWS_Gpt_00015 */
    Gpt_Global.Gpt_NotifEnable[Channel] = FALSE;

}
#endif

/* @req SWS_Gpt_00201 */
/* @req SWS_Gpt_00202 */
/* @req SWS_Gpt_00203 */
/* @req SWS_Gpt_00324 */
#if ( GPT_WAKEUP_FUNCTIONALITY_API == STD_ON )

/* @req SWS_Gpt_00157 */
/* @req SWS_Gpt_00255 */
/* @req SWS_Gpt_00158 */
/* @req SWS_Gpt_00322 */
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)

/* @req SWS_Gpt_00288 */
void Gpt_SetMode( Gpt_ModeType Mode ) {

    /* @req SWS_Gpt_00228 */
    VALIDATE((STD_ON == Gpt_Global.initRun), GPT_SETMODE_SERVICE_ID, GPT_E_UNINIT);

    /* @req SWS_Gpt_00231 */
    VALIDATE(((GPT_MODE_SLEEP == Mode) || (GPT_MODE_NORMAL == Mode)), GPT_SETMODE_SERVICE_ID, GPT_E_PARAM_MODE);

    /* @req SWS_Gpt_00164 */
    if (GPT_MODE_SLEEP == Mode) {
        for (uint8 chnlCnt = 0; chnlCnt < GPT_ARC_LOG_UNIT_CNT; chnlCnt++) {
            if ((!Gpt_Global.Gpt_WakUpEnable[chnlCnt]) && (GPT_STATE_RUNNING == Gpt_Global.Gpt_ChannelState[chnlCnt])) {
                Gpt_StopTimer( GET_CONFIG(chnlCnt).GptChannelId); //Stop channels not configured/Enabled for wakeup
            }
            /* @req SWS_Gpt_00153 */
            /* @req SWS_Gpt_00093 */
            /* @req SWS_Gpt_00341 */
            //No Wakeup timer started
        }
    }
    else {
        /* @req SWS_Gpt_00165 */
        //Other timers are not started in Normal mode
    }

    /* @req SWS_Gpt_00151 */
    Gpt_Global.mode = Mode;
}

/* @req SWS_Gpt_00289 */
void Gpt_DisableWakeup( Gpt_ChannelType Channel ) {

    uint8 chnlidx;

    /* @req SWS_Gpt_00229 */
    VALIDATE((STD_ON == Gpt_Global.initRun), GPT_DISABLEWAKEUP_SERVICE_ID, GPT_E_UNINIT);

    /* @req SWS_Gpt_00215 */
    VALIDATE(IS_CHANNEL_VALID(Channel), GPT_DISABLEWAKEUP_SERVICE_ID, GPT_E_PARAM_CHANNEL);

    chnlidx = Gpt_Global.channelMap[Channel];

    /* @req SWS_Gpt_00215 */
    VALIDATE(GET_CONFIG(chnlidx).GptEnableWakeup, GPT_DISABLEWAKEUP_SERVICE_ID, GPT_E_PARAM_CHANNEL);

    /* @req SWS_Gpt_00159 */
    Gpt_Global.Gpt_WakUpEnable[chnlidx] = FALSE;

}

/* @req SWS_Gpt_00290 */
void Gpt_EnableWakeup( Gpt_ChannelType Channel ) {

    uint8 chnlidx;

    /* @req SWS_Gpt_00230 */
    VALIDATE((STD_ON == Gpt_Global.initRun), GPT_ENABLEWAKEUP_SERVICE_ID, GPT_E_UNINIT);

    /* @req SWS_Gpt_00216 */
    VALIDATE(IS_CHANNEL_VALID(Channel), GPT_ENABLEWAKEUP_SERVICE_ID, GPT_E_PARAM_CHANNEL);

    chnlidx = Gpt_Global.channelMap[Channel];

    /* @req SWS_Gpt_00216 */
    VALIDATE(GET_CONFIG(chnlidx).GptEnableWakeup, GPT_ENABLEWAKEUP_SERVICE_ID, GPT_E_PARAM_CHANNEL);

    /* @req SWS_Gpt_00160 */
    Gpt_Global.Gpt_WakUpEnable[chnlidx] = TRUE;

}

/* @req SWS_Gpt_00328 */
void Gpt_CheckWakeup( EcuM_WakeupSourceType WakeupSource ) {

    /* @req SWS_Gpt_00325 */
    VALIDATE((STD_ON == Gpt_Global.initRun), GPT_CHECKWAKEUP_SERVICE_ID, GPT_E_UNINIT);

    for (uint8 chnlCnt = 0; chnlCnt < GPT_ARC_LOG_UNIT_CNT; chnlCnt++) {
        /* @req SWS_Gpt_00127 */
        // Loop over all channels to check if Wakeup source is found
        if (Gpt_Global.Gpt_WakUpEnable[chnlCnt] && (GET_CONFIG(chnlCnt).GptWakeupSource == WakeupSource)
                && ( GPT_STATE_EXPIRED == Gpt_Global.Gpt_ChannelState[chnlCnt])) {
            /* @req SWS_Gpt_00321 */
            EcuM_SetWakeupEvent(WakeupSource);
            break;
        }
    }

    return;
}
#endif
#endif
/*lint -restore*/

#ifdef HOST_TEST
Gpt_ChannelStateType Gpt_Test_GetChannelState(Gpt_ChannelType Channel) {

    return Gpt_Global.Gpt_ChannelState[Channel];
}
#endif /* HOST_TEST */
