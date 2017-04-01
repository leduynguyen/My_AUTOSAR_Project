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

/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */
/** @tagSettings DEFAULT_ARCHITECTURE=JACINTO5|JACINTO6|RH850 */

/** @req SWS_Pwm_00070 All time units shall be in ticks. */
/** @req SWS_Pwm_00088 Re-entrant functions. */
/** @req SWS_Pwm_00121 Re-initialization with Pwm_Init requires call to Pwm_DeInit before. */
/** @req SWS_Pwm_10051 Report to Det if enabled. */
/** @req SWS_Pwm_20002 Return PWM_E_UNINIT when API service is used without module initialization. */
/** @req SWS_Pwm_30002 Return PWM_E_PARAM_CHANNEL when API service is used with an invalid channel Identifier. */
/** @req SWS_Pwm_40002 Return PWM_E_PERIOD_UNCHANGEABLE if user is trying to change period on a channel
 * not configured as variable period. */
/** @req SWS_Pwm_20051 Do not perform action if Det is enabled and error is deteced.
 * Supported with some exceptions (Pwm_Init and PWM_E_EXECUTION_ERROR). */

/* ----------------------------[includes]------------------------------------*/

#include "Pwm.h"
#include "Pwm_Internal.h"
#include <string.h>

#if defined(USE_DET)
#include "Det.h"
#endif


/* ----------------------------[private define]------------------------------*/
/* ----------------------------[private macro]-------------------------------*/

#if defined(USE_DET)
#	define Pwm_Det_ReportError(ApiId, ErrorId) (void) Det_ReportError( PWM_MODULE_ID, 0, ApiId, ErrorId);
#else
#   define Pwm_Det_ReportError(ApiId, ErrorId)
#endif

/* Is HW channel valid */
#define IS_HW_CHANNEL_VALID(_hwCh)       (((_hwCh) <= PWM_ARC_HW_UNIT_HIGH) && (HwChannelToChannel(_hwCh) < PWM_ARC_LOG_UNIT_CNT))


#define IS_CHANNEL_VALID(_c)        ((_c) < PWM_ARC_LOG_UNIT_CNT)

#if ( PWM_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
        (void)  Det_ReportError(PWM_MODULE_ID,0,_api,_err); \
          return; \
        }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(PWM_MODULE_ID,0,_api,_err); \
          return (_rv); \
        }

#define VALID_CHANNEL(_ch)      ( Pwm_Global.configured & (1u<<(_ch)) )
#endif

/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/


Pwm_GlobalType Pwm_Global;
const Pwm_ConfigType *PwmConfigPtr = NULL;
uint32 Pwm_Clock = 0;

/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

#if ( PWM_VERSION_INFO_API == STD_ON)
void Pwm_GetVersionInfo(Std_VersionInfoType* versioninfo) {
    /* @req SWS_Pwm_00151 */
    VALIDATE( ( NULL != versioninfo ), PWM_GETVERSIONINFO_SERVICE_ID, PWM_E_PARAM_POINTER);

    versioninfo->vendorID = PWM_VENDOR_ID;
    versioninfo->moduleID = PWM_MODULE_ID;
    versioninfo->sw_major_version = PWM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = PWM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = PWM_SW_PATCH_VERSION;
}
#endif

void Pwm_Init(const Pwm_ConfigType* ConfigPtr){
    uint8 hwCh;

    /** @req SWS_Pwm_00118 Already init check check */
    /** @req SWS_Pwm_50002 Return PWM_E_ALREADY_INITIALIZED if Pwm_Init is called when already initialized. */
    VALIDATE ((STD_OFF == Pwm_Global.initRun), PWM_INIT_SERVICE_ID, PWM_E_ALREADY_INITIALIZED);
    /** @req SWS_Pwm_00046 Null pointer check */
    VALIDATE((ConfigPtr != NULL), PWM_INIT_SERVICE_ID, PWM_E_INIT_FAILED);


    /** @req SWS_Pwm_00007 init internal variables */
    /** @req SWS_Pwm_00062 no not touch anything but the config */
    PwmConfigPtr = ConfigPtr;

    memset(Pwm_Global.channelMap,0xff, sizeof(Pwm_Global.channelMap) );
    memset(Pwm_Global.channelToHwChannel,0xff, sizeof(Pwm_Global.channelToHwChannel) );

    for (uint8 ch = 0; ch < PWM_ARC_LOG_UNIT_CNT; ch++) {
        hwCh = PwmConfigPtr->Channels[ch].channel;
        Pwm_Global.channelToHwChannel[ch] = hwCh;
        Pwm_Global.channelMap[hwCh] = ch;
        Pwm_Global.Pwm_NotifEnable[ch] = FALSE;
    }

    /** @req SWS_Pwm_10002 */
    VALIDATE( Pwm_Hw_Init(PwmConfigPtr) == E_OK, PWM_INIT_SERVICE_ID, PWM_E_PARAM_CONFIG );

    Pwm_Global.initRun = STD_ON;
}

/** Note!
 *  SWS_Pwm_00096, SWS_Pwm_10080, SWS_Pwm_20080 requirements handled
 *  in the header file
 */
#if (PWM_DE_INIT_API==STD_ON)
void Pwm_DeInit(void){

    /** @req SWS_Pwm_00011 PWM output signals to the idle state */

    VALIDATE ((STD_ON == Pwm_Global.initRun), PWM_DEINIT_SERVICE_ID, PWM_E_UNINIT);

    Pwm_Hw_Deinit(PwmConfigPtr);

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
    for (uint8 ch = 0; ch < PWM_ARC_LOG_UNIT_CNT; ch++) {
        Pwm_Global.Pwm_NotifEnable[ch] = FALSE;
    }
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) */

    Pwm_Global.initRun = STD_OFF;
}
#endif

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
/** @req SWS_Pwm_00150 */
/** @req SWS_Pwm_00041 */
/** @req SWS_Pwm_00045 */
void Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle) {

    /** @req SWS_Pwm_00117 */
    VALIDATE ((STD_ON == Pwm_Global.initRun), PWM_SETPERIODANDDUTY_SERVICE_ID, PWM_E_UNINIT);
    /** @req SWS_Pwm_00047 */
    VALIDATE (IS_HW_CHANNEL_VALID(ChannelNumber), PWM_SETPERIODANDDUTY_SERVICE_ID, PWM_E_PARAM_CHANNEL);

    Pwm_ChannelType logCh = HwChannelToChannel(ChannelNumber);

    if (PwmConfigPtr->Channels[logCh].class != PWM_VARIABLE_PERIOD) {
#if (PWM_DEV_ERROR_DETECT == STD_ON)
        (void) Det_ReportError(PWM_MODULE_ID, 0, PWM_SETPERIODANDDUTY_SERVICE_ID, PWM_E_PERIOD_UNCHANGEABLE);
#endif
        return;
    }

       Pwm_Hw_SetPeriodAndDuty(ChannelNumber, Period, DutyCycle, PwmConfigPtr->Channels[logCh].polarity);
}
#endif

#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle) {

    /** @req SWS_Pwm_00117 */
    VALIDATE ((STD_ON == Pwm_Global.initRun), PWM_SETDUTYCYCLE_SERVICE_ID, PWM_E_UNINIT);
    /** @req SWS_Pwm_00047 */
    VALIDATE (IS_HW_CHANNEL_VALID(ChannelNumber), PWM_SETDUTYCYCLE_SERVICE_ID, PWM_E_PARAM_CHANNEL);

    Pwm_ChannelType logCh = HwChannelToChannel(ChannelNumber);

    Pwm_Hw_SetDutyCycle(ChannelNumber, DutyCycle, PwmConfigPtr->Channels[logCh].polarity);
}
#endif

#if ( PWM_SET_OUTPUT_TO_IDLE_API == STD_ON )
void Pwm_SetOutputToIdle(Pwm_ChannelType ChannelNumber) {

    /** @req SWS_Pwm_00117 */
    VALIDATE ((STD_ON == Pwm_Global.initRun), PWM_SETOUTPUTTOIDLE_SERVICE_ID, PWM_E_UNINIT);
    /** @req SWS_Pwm_00047 */
    VALIDATE (IS_HW_CHANNEL_VALID(ChannelNumber), PWM_SETOUTPUTTOIDLE_SERVICE_ID, PWM_E_PARAM_CHANNEL);

    Pwm_ChannelType logCh = HwChannelToChannel(ChannelNumber);

    Pwm_Hw_SetOutputToIdle(ChannelNumber, PwmConfigPtr->Channels[logCh].idleState);
}
#endif

#if (PWM_GET_OUTPUT_STATE_API == STD_ON)
/** @req SWS_Pwm_30051 Interpreted as if a Det error happens in Pwm_GetOutputState. */
Pwm_OutputStateType Pwm_GetOutputState(Pwm_ChannelType ChannelNumber){

    /** @req SWS_Pwm_00117 */
    VALIDATE_W_RV ((STD_ON == Pwm_Global.initRun), PWM_GETOUTPUTSTATE_SERVICE_ID, PWM_E_UNINIT, PWM_LOW);
    /** @req SWS_Pwm_00047 */
    VALIDATE_W_RV (IS_HW_CHANNEL_VALID(ChannelNumber), PWM_GETOUTPUTSTATE_SERVICE_ID, PWM_E_PARAM_CHANNEL, PWM_LOW);

    return Pwm_Hw_GetOutputState(ChannelNumber);
}
#endif

/** @req:JACINTO6 SWS_Pwm_10112 */
/** @req:JACINTO6 SWS_Pwm_10113 */
/** @req SWS_Pwm_10115 */
/** @req SWS_Pwm_20115 */
#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
void Pwm_DisableNotification(Pwm_ChannelType ChannelNumber){

    /** @req SWS_Pwm_00117 */
    VALIDATE ((STD_ON == Pwm_Global.initRun), PWM_DISABLENOTIFICATION_SERVICE_ID, PWM_E_UNINIT);
    /** @req SWS_Pwm_00047 */
    VALIDATE (IS_HW_CHANNEL_VALID(ChannelNumber), PWM_DISABLENOTIFICATION_SERVICE_ID, PWM_E_PARAM_CHANNEL);

    Pwm_Hw_DisableNotification(ChannelNumber);

    Pwm_ChannelType logCh = HwChannelToChannel(ChannelNumber);
    Pwm_Global.Pwm_NotifEnable[logCh] = FALSE;
}

void Pwm_EnableNotification(Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification){

    /** @req SWS_Pwm_00117 */
    VALIDATE ((STD_ON == Pwm_Global.initRun), PWM_ENABLENOTIFICATION_SERVICE_ID, PWM_E_UNINIT);
    /** @req SWS_Pwm_00047 */
    VALIDATE (IS_HW_CHANNEL_VALID(ChannelNumber), PWM_ENABLENOTIFICATION_SERVICE_ID, PWM_E_PARAM_CHANNEL);

    Pwm_ChannelType logCh = HwChannelToChannel(ChannelNumber);
    Pwm_Hw_EnableNotification(ChannelNumber, Notification, PwmConfigPtr->Channels[logCh].polarity);

    Pwm_Global.Pwm_NotifEnable[logCh] = TRUE;
}
#endif
