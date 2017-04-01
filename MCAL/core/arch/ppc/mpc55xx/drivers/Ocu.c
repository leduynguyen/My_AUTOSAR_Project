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
/** @tagSettings DEFAULT_ARCHITECTURE=PPC|MPC5607B|MPC5645S */

//lint -save -e923 // PC-Lint Exception : Assignment of hardware address pointer.

#include "Std_Types.h"


/** General req tagging */
/* @req  SWS_Ocu_00001 */
/* @req  SWS_Ocu_00008 */
/* @req  SWS_Ocu_00012 */
/* @req  SWS_Ocu_00017 */
/* @req  SWS_Ocu_00013 */
/* @req  SWS_Ocu_00015 */
/* @req  SWS_Ocu_00016 */
/* @req  SWS_Ocu_00018 */
/* @req  SWS_Ocu_00019 */
/* @req  SWS_Ocu_00023 */
/* @req  SWS_Ocu_00024 */
/* @req  SWS_Ocu_00025 */
/* @req  SWS_Ocu_00026 */
/* @req  SWS_Ocu_00127 */
/* @req  SWS_Ocu_00053 */
/* @req  SWS_Ocu_00061 */
/* @req  SWS_Ocu_00068 */
/* @req  SWS_Ocu_00078 */
/* @req  SWS_Ocu_00087 */
/* @req  SWS_Ocu_00093 */
/* @req  SWS_Ocu_00102 */
/* @req  SWS_Ocu_00110 */
/* @req  SWS_Ocu_00117 */
/* @req  SWS_Ocu_00128 */
/* @req  SWS_Ocu_00134 */


/* @req SWS_Ocu_00006 */
#include "Ocu.h"
#include "Ocu_MemMap.h"
#include "string.h"
#include "Ocu_Internal.h"

#if (OCU_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#if ( OCU_DEV_ERROR_DETECT == STD_ON )
/* @req SWS_Ocu_00021 */
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(OCU_MODULE_ID,0,_api,_err); \
          return; \
        }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(OCU_MODULE_ID,0,_api,_err); \
          return (_rv); \
        }
#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_W_RV(_exp,_api,_err,_rv )
#endif

static Ocu_DriverStatusType OcuDriverStatus = OCU_UNINIT;
const Ocu_ConfigType * OcuConfigPtr = NULL;
static Ocu_ChnlStateType OcuChnlState[OCU_MATCH_CHANNEL_COUNT];

Ocu_ReturnType setthrshld(Ocu_ChannelType ChannelNumber,Ocu_ValueType ReferenceValue,Ocu_ValueType AbsoluteValue);


/* @req SWS_Ocu_00035 */
void Ocu_Init(const Ocu_ConfigType* ConfigPtr)
{
    volatile struct EMIOS_tag * emiosUnit;
    uint8 channelId;
    uint8 absChnlId;

    /* @req SWS_Ocu_00041 **/
    VALIDATE( (ConfigPtr != NULL), OCU_INIT_SERVICE_ID, OCU_E_PARAM_CONFIG );

    /* @req SWS_Ocu_00043 **/
    /* @req SWS_Ocu_00044 */
    VALIDATE( (OcuDriverStatus == OCU_UNINIT), OCU_INIT_SERVICE_ID, OCU_E_ALREADY_INITIALIZED );

    OcuConfigPtr = ConfigPtr;

    //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
    if ((OCU_COUNTER_CHANNEL_COUNT > 0) && (OcuConfigPtr->OcuGroupConfig == NULL)) { return; }

    /* @req SWS_Ocu_00036 */
    /* @req SWS_Ocu_00037 */
    /* @req SWS_Ocu_00038 */
    // Counter channel specific configuration
    for (uint8 chnlcnt = 0; chnlcnt < OCU_COUNTER_CHANNEL_COUNT; chnlcnt++)  {
        channelId = OcuConfigPtr->OcuGroupConfig[chnlcnt].OcuGroupId;

        //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
        if (CHANNELS_PER_EMIOS_UNIT != 0) {
            emiosUnit = GET_EMIOS_UNIT(channelId/CHANNELS_PER_EMIOS_UNIT);
        } else { return; }

        absChnlId = GET_EMIOS_CHANNEL(channelId);

        emiosUnit->UCDIS.R &= ~(1UL << absChnlId); //Enable channels

        //17.8.2.3 in uc reference manual
        emiosUnit->CH[absChnlId].CCR.B.UCPEN    = OCU_PRESCALER_DISABLE; //disable channel prescaler
        emiosUnit->CH[absChnlId].CADR.R         = (vuint32_t)(OcuConfigPtr->OcuGroupConfig[chnlcnt].OcuMaxCounterTickVal + 1UL); // HW is 1 based counter
        /* @req SWS_Ocu_00011 */
        emiosUnit->CH[absChnlId].CCR.B.MODE     = MCB_CHANNEL_MODE; //MCB Upcounter
        emiosUnit->CH[absChnlId].CCR.B.UCPRE    = (vuint32_t)(OcuConfigPtr->OcuGroupConfig[chnlcnt].OcuChannelTickDur - 1UL); //prescaler value (zero base)
        emiosUnit->CH[absChnlId].CCR.B.UCPEN    = OCU_PRESCALER_ENABLE; //enable prescaler
        emiosUnit->CH[absChnlId].CCR.B.BSL      = SELECT_INTERNAL_COUNTER; //Use internal counter

        emiosUnit->CH[absChnlId].CCR.B.FREN     = OCU_FREEZE_ENABLE; //Freeze enable - debug purpose

    }

    //Match Channel specific settings

    //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
    if ((OCU_MATCH_CHANNEL_COUNT > 0) &&  (OcuConfigPtr->OcuChannelConfig == NULL)) { return; }

    for (uint8 chnlcnt = 0; chnlcnt < OCU_MATCH_CHANNEL_COUNT; chnlcnt++)  {

        channelId = OcuConfigPtr->OcuChannelConfig[chnlcnt].OcuChannelId;

        //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
        if (CHANNELS_PER_EMIOS_UNIT != 0) {
            emiosUnit = GET_EMIOS_UNIT(channelId/CHANNELS_PER_EMIOS_UNIT);
        } else { return; }

        absChnlId = GET_EMIOS_CHANNEL(channelId);

        emiosUnit->UCDIS.R &= ~(1UL << absChnlId); //Enable channels

        emiosUnit->CH[absChnlId].CCR.B.UCPEN    = OCU_PRESCALER_DISABLE; //disable channel prescaler
        emiosUnit->CH[absChnlId].CADR.R         = (vuint32_t)(OcuConfigPtr->OcuChannelConfig[chnlcnt].OcuDefaultThreshold + 1); // In MCB counter is 1 based
        emiosUnit->CH[absChnlId].CCR.B.BSL      = SELECT_C_D_COUNTER_BUS; //Counter bus C or D
        emiosUnit->CH[absChnlId].CCR.B.MODE     = GPIO_OUTPUT_CHANNEL_MODE; //Reset counter by selecting GPIO outpupt mode (Also to set default pin state)

        /* @req SWS_Ocu_00040 */
        //Reset value of FEN is 0
        emiosUnit->CH[absChnlId].CCR.B.FREN     = OCU_FREEZE_ENABLE; //Freeze enable


        // Output Pin default state
        if (TRUE == OcuConfigPtr->OcuChannelConfig[chnlcnt].OcuOutpinUsed) {

            if (OCU_HIGH == OcuConfigPtr->OcuChannelConfig[chnlcnt].OcuOutputPinDefState) //If default state is high
            {
                emiosUnit->CH[absChnlId].CCR.B.EDPOL = SET_OUTPUT_FF_HIGH; //Set EDPOL to 1 which makes output pin to high
            } else {
                emiosUnit->CH[absChnlId].CCR.B.EDPOL = SET_OUTPUT_FF_LOW;
            }
        }
        /* @req SWS_Ocu_00039 */
        OcuChnlState[chnlcnt]                   = OCU_CHANNEL_STOPPED;
    }

#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
    Ocu_Arc_InstallInterrupts(); //Install Interrupts
#endif
    OcuDriverStatus = OCU_INIT;
}

/* @req SWS_Ocu_00049 */
#if (OCU_DE_INIT_API == STD_ON)
/* @req SWS_Ocu_00045 */
void Ocu_DeInit(void)
{
    volatile struct EMIOS_tag * emiosUnit;
    uint8 channelId;
    uint8 absChnlId;

    /* @req SWS_Ocu_00050 **/
    VALIDATE( (OcuDriverStatus != OCU_UNINIT), OCU_DEINIT_SEVICE_ID, OCU_E_UNINIT );

    //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
    if ((OCU_MATCH_CHANNEL_COUNT > 0) &&  (OcuConfigPtr->OcuChannelConfig == NULL)) { return; }

    /* @req SWS_Ocu_00046 */
    for (uint8 chnlcnt = 0; chnlcnt < OCU_MATCH_CHANNEL_COUNT; chnlcnt++)  {
        /* @req SWS_Ocu_00048 */
        channelId  = OcuConfigPtr->OcuChannelConfig[chnlcnt].OcuChannelId;
        /* @req SWS_Ocu_00137 **/
        VALIDATE( (OcuChnlState[chnlcnt] != OCU_CHANNEL_RUNNING), OCU_DEINIT_SEVICE_ID, OCU_E_PARAM_INVALID_STATE );

        //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
        if (CHANNELS_PER_EMIOS_UNIT != 0) {
            emiosUnit = GET_EMIOS_UNIT(channelId/CHANNELS_PER_EMIOS_UNIT);
        } else { return; }

        absChnlId = GET_EMIOS_CHANNEL(channelId);
        /* @req SWS_Ocu_00047 */
        emiosUnit->CH[absChnlId].CCR.B.MODE      = GPIO_INPUT_CHANNEL_MODE;
        emiosUnit->CH[absChnlId].CCR.B.FEN       = OCU_INTERRUPT_DISABLE; //Disable Interrupts
        emiosUnit->CH[absChnlId].CSR.B.FLAG      = 1; //Clear flags
        emiosUnit->CH[absChnlId].CSR.B.OVR       = 1; //Clear overrun flags
        emiosUnit->CH[absChnlId].CSR.B.OVFL      = 1; //Clear overflow flags
        emiosUnit->CH[absChnlId].CADR.R          = 0;
        /* @req SWS_Ocu_00136 */
        OcuChnlState[chnlcnt]                    = OCU_CHANNEL_STOPPED;
    }

    //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
    if ((OCU_COUNTER_CHANNEL_COUNT > 0) && (OcuConfigPtr->OcuGroupConfig == NULL)) { return; }

    for (uint8 chnlcnt = 0; chnlcnt < OCU_COUNTER_CHANNEL_COUNT; chnlcnt++)  {
        channelId = OcuConfigPtr->OcuGroupConfig[chnlcnt].OcuGroupId;

        //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
        if (CHANNELS_PER_EMIOS_UNIT != 0) {
            emiosUnit = GET_EMIOS_UNIT(channelId/CHANNELS_PER_EMIOS_UNIT);
        } else { return; }
        absChnlId = GET_EMIOS_CHANNEL(channelId);
        emiosUnit->CH[absChnlId].CCR.B.MODE     = GPIO_INPUT_CHANNEL_MODE; //Reset Upcounter by setting GPIO mode
        emiosUnit->CH[absChnlId].CADR.R         = 0;
    }
    OcuDriverStatus = OCU_UNINIT;
}
#endif


/* @req SWS_Ocu_00051 */
void Ocu_StartChannel(Ocu_ChannelType ChannelNumber)
{
    volatile struct EMIOS_tag * emiosUnit;
    uint8 channelId;
    uint8 absChnlId;

    /* @req SWS_Ocu_00057 **/
    VALIDATE( (OcuDriverStatus != OCU_UNINIT), OCU_STARTCHANNEL_SERVICE_ID, OCU_E_UNINIT );

    /* @req SWS_Ocu_00056 **/
    VALIDATE( (ChannelNumber < OCU_MATCH_CHANNEL_COUNT), OCU_STARTCHANNEL_SERVICE_ID, OCU_E_PARAM_INVALID_CHANNEL );

    /* @req SWS_Ocu_00055 **/
    VALIDATE( (OcuChnlState[ChannelNumber] != OCU_CHANNEL_RUNNING), OCU_STARTCHANNEL_SERVICE_ID, OCU_E_BUSY );

    channelId = OcuConfigPtr->OcuChannelConfig[ChannelNumber].OcuChannelId;

    //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
    if (CHANNELS_PER_EMIOS_UNIT != 0) {
        emiosUnit = GET_EMIOS_UNIT(channelId/CHANNELS_PER_EMIOS_UNIT);
    } else { return; }
    absChnlId = GET_EMIOS_CHANNEL(channelId);

    /* @req SWS_Ocu_00052 */
    //The mode can be set only when channel is enabled
    emiosUnit->CH[absChnlId].CCR.B.MODE     = SAOC_CHANNEL_MODE; //Set it to SAOC

    /* @req SWS_Ocu_00054 */
    OcuChnlState[ChannelNumber] = OCU_CHANNEL_RUNNING;

}



/* @req SWS_Ocu_00058 */
void Ocu_StopChannel(Ocu_ChannelType ChannelNumber)
{
    volatile struct EMIOS_tag * emiosUnit;
    uint8 channelId;
    uint8 absChnlId;


    /* @req SWS_Ocu_00065 **/
    VALIDATE( (OcuDriverStatus != OCU_UNINIT), OCU_STOPCHANNEL_SERVICE_ID, OCU_E_UNINIT );

    /* @req SWS_Ocu_00064 **/
    VALIDATE( (ChannelNumber < OCU_MATCH_CHANNEL_COUNT), OCU_STOPCHANNEL_SERVICE_ID, OCU_E_PARAM_INVALID_CHANNEL );

    /* @req SWS_Ocu_00063 **/
    if (OcuChnlState[ChannelNumber] != OCU_CHANNEL_STOPPED) {

        channelId = OcuConfigPtr->OcuChannelConfig[ChannelNumber].OcuChannelId;

        //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
        if (CHANNELS_PER_EMIOS_UNIT != 0) {
            emiosUnit = GET_EMIOS_UNIT(channelId/CHANNELS_PER_EMIOS_UNIT);
        } else { return; }
        absChnlId = GET_EMIOS_CHANNEL(channelId);

        /* @req SWS_Ocu_00059 */
        emiosUnit->CH[absChnlId].CCR.B.MODE     = GPIO_OUTPUT_CHANNEL_MODE; //Set it to GPIO output mode to support Ocu_SetPinState API (Counter & Match disabled)

        /* @req SWS_Ocu_00062 */
        OcuChnlState[ChannelNumber] = OCU_CHANNEL_STOPPED;
        /* @req SWS_Ocu_00060 */ //Counter is not stopped
    }

}



/* @req SWS_Ocu_00070 */
#if (OCU_SET_PIN_STATE_API == STD_ON)
/* @req SWS_Ocu_00066 */
void Ocu_SetPinState(Ocu_ChannelType ChannelNumber,Ocu_PinStateType PinState)
{
    volatile struct EMIOS_tag * emiosUnit;
    uint8 channelId;
    uint8 absChnlId;

    /* @req SWS_Ocu_00074 **/
    VALIDATE( (OcuDriverStatus != OCU_UNINIT), OCU_SETPINSTATE_SERVICE_ID, OCU_E_UNINIT );

    /* @req SWS_Ocu_00071 **/
    VALIDATE( (ChannelNumber < OCU_MATCH_CHANNEL_COUNT), OCU_SETPINSTATE_SERVICE_ID, OCU_E_PARAM_INVALID_CHANNEL );

    /* @req SWS_Ocu_00072**/
    VALIDATE( (OcuConfigPtr->OcuChannelConfig[ChannelNumber].OcuOutpinUsed == TRUE ), OCU_SETPINSTATE_SERVICE_ID, OCU_E_PARAM_NO_PIN );

    /* @req SWS_Ocu_00073**/
    VALIDATE( ((PinState == OCU_HIGH )||(PinState ==  OCU_LOW )), OCU_SETPINSTATE_SERVICE_ID, OCU_E_PARAM_INVALID_STATE );

    /* @req SWS_Ocu_00069 **/
    /* @req SWS_Ocu_00075 **/
    VALIDATE( (OcuChnlState[ChannelNumber] != OCU_CHANNEL_RUNNING), OCU_SETPINSTATE_SERVICE_ID, OCU_E_PARAM_INVALID_STATE );

    channelId = OcuConfigPtr->OcuChannelConfig[ChannelNumber].OcuChannelId;

    //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
    if (CHANNELS_PER_EMIOS_UNIT != 0) {
        emiosUnit = GET_EMIOS_UNIT(channelId/CHANNELS_PER_EMIOS_UNIT);
    } else { return; }
    absChnlId = GET_EMIOS_CHANNEL(channelId);

    /* @req SWS_Ocu_00067 **/
    emiosUnit->CH[absChnlId].CCR.B.EDPOL    = (OCU_LOW == PinState) ? SET_OUTPUT_FF_LOW : SET_OUTPUT_FF_HIGH;

}
#endif



/* @req SWS_Ocu_00079 */
#if (OCU_SET_PIN_ACTION_API == STD_ON)
/* @req SWS_Ocu_00076 */
void Ocu_SetPinAction(Ocu_ChannelType ChannelNumber,Ocu_PinActionType PinAction)
{
    volatile struct EMIOS_tag * emiosUnit;
    uint8 channelId;
    uint8 absChnlId;


    /* @req SWS_Ocu_00083 **/
    VALIDATE( (OcuDriverStatus != OCU_UNINIT), OCU_SETPINACTION_SERVICE_ID, OCU_E_UNINIT );

    /* @req SWS_Ocu_00080 **/
    VALIDATE( (ChannelNumber < OCU_MATCH_CHANNEL_COUNT), OCU_SETPINACTION_SERVICE_ID, OCU_E_PARAM_INVALID_CHANNEL );

    /* @req SWS_Ocu_00081 **/
    VALIDATE( (OcuConfigPtr->OcuChannelConfig[ChannelNumber].OcuOutpinUsed == TRUE), OCU_SETPINACTION_SERVICE_ID, OCU_E_PARAM_NO_PIN );

    /* @req SWS_Ocu_00082 **/
    VALIDATE( ((PinAction >= OCU_SET_HIGH) && (PinAction <= OCU_DISABLE)), OCU_SETPINACTION_SERVICE_ID, OCU_E_PARAM_INVALID_ACTION ); /*lint !e685 Can be out of bound if used incorrectly by the user */

    channelId = OcuConfigPtr->OcuChannelConfig[ChannelNumber].OcuChannelId;

    //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
    if (CHANNELS_PER_EMIOS_UNIT != 0) {
        emiosUnit = GET_EMIOS_UNIT(channelId/CHANNELS_PER_EMIOS_UNIT);
    } else { return; }
    absChnlId = GET_EMIOS_CHANNEL(channelId);


    /* @req SWS_Ocu_00077 */
    /* @req SWS_Ocu_00084 */
    switch (PinAction) {

        case OCU_SET_HIGH :
            emiosUnit->CH[absChnlId].CCR.B.EDPOL    = SET_OUTPUT_FF_HIGH;
            emiosUnit->CH[absChnlId].CCR.B.EDSEL    = DISABLE_EDSEL;
            break;

        case OCU_SET_LOW :
            emiosUnit->CH[absChnlId].CCR.B.EDPOL    = SET_OUTPUT_FF_LOW;
            emiosUnit->CH[absChnlId].CCR.B.EDSEL    = DISABLE_EDSEL;
            break;

        case OCU_TOGGLE :
            emiosUnit->CH[absChnlId].CCR.B.EDSEL    = ENABLE_EDSEL_OUTPUT_TOGGLE;
            break;

        case OCU_DISABLE :
            emiosUnit->CH[absChnlId].CCR.B.EDSEL    = DISABLE_EDSEL;
            emiosUnit->CH[absChnlId].CCR.B.EDPOL    = emiosUnit->CH[absChnlId].CSR.B.UCOUT; //Restore the EDPOL to last output state
            break;

        default:
            break; /* Misra compliance */
    }

}
#endif



/* @req SWS_Ocu_00088 */
#if (OCU_GET_COUNTER_API == STD_ON)
/* @req SWS_Ocu_00085 */
Ocu_ValueType  Ocu_GetCounter(Ocu_ChannelType ChannelNumber)
{

    vuint32_t cntr;
    uint8 cntrchnl;
    const volatile struct EMIOS_tag * emiosUnit;
    uint8 channelId;
    uint8 absChnlId;


    /* @req SWS_Ocu_00090 **/
    VALIDATE_W_RV( (OcuDriverStatus != OCU_UNINIT), OCU_GETCOUNTER_SERVICE_ID, OCU_E_UNINIT,INVALID_COUNTERVALUE );

    /* @req SWS_Ocu_00089 **/
    VALIDATE_W_RV( (ChannelNumber < OCU_MATCH_CHANNEL_COUNT), OCU_GETCOUNTER_SERVICE_ID, OCU_E_PARAM_INVALID_CHANNEL,INVALID_COUNTERVALUE );

    channelId = OcuConfigPtr->OcuChannelConfig[ChannelNumber].OcuChannelId;

    //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
    if (CHANNELS_PER_EMIOS_UNIT != 0) {
        emiosUnit = GET_EMIOS_UNIT(channelId/CHANNELS_PER_EMIOS_UNIT);
    } else { return INVALID_COUNTERVALUE; }
    absChnlId = GET_EMIOS_CHANNEL(channelId);


    // Get the unified channel section which drives the counter
    cntrchnl  = (absChnlId < UNIFIED_CHANNEL_D) ? UNIFIED_CHANNEL_C:UNIFIED_CHANNEL_D ;

    /* @req SWS_Ocu_00086 */
    cntr = emiosUnit->CH[cntrchnl].CCNTR.R -1UL; //In MCB mode CNTR is 1 based
    return (Ocu_ValueType)cntr;
}
#endif

Ocu_ReturnType setthrshld(Ocu_ChannelType ChannelNumber,Ocu_ValueType ReferenceValue,Ocu_ValueType AbsoluteValue) {

    /* No range check is needed for parameters ReferenceValue and AbsolutValue since every
     * possible value is valid in the used context. */

    Ocu_ReturnType ret = OCU_CM_OUT_REF_INTERVAL;
    Ocu_ValueType cntr;
    uint8 cntrchnl;
    volatile struct EMIOS_tag * emiosUnit;
    uint8 channelId;
    uint8 absChnlId;

    channelId = OcuConfigPtr->OcuChannelConfig[ChannelNumber].OcuChannelId;

    //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
    if (CHANNELS_PER_EMIOS_UNIT != 0) {
        emiosUnit = GET_EMIOS_UNIT(channelId/CHANNELS_PER_EMIOS_UNIT);
    } else { return ret; }
    absChnlId = GET_EMIOS_CHANNEL(channelId);


    cntrchnl  = (absChnlId < UNIFIED_CHANNEL_D) ? UNIFIED_CHANNEL_C:UNIFIED_CHANNEL_D ;

    /* @req SWS_Ocu_00097 */
    /* @req SWS_Ocu_00092 */
#ifdef HOST_TEST
    //Create delay
    for (uint32_t i= 0; (i < 10000) && Ocu_enablDelayGlobalVariable; i++) {}
#endif
    emiosUnit->CH[absChnlId].CADR.R = (vuint32_t)(AbsoluteValue + 1UL);
    cntr = (Ocu_ValueType)(emiosUnit->CH[cntrchnl].CCNTR.R - 1);

    if (AbsoluteValue > ReferenceValue) {
            ret =  ((cntr < ReferenceValue) || (cntr > AbsoluteValue)) ? OCU_CM_OUT_REF_INTERVAL : OCU_CM_IN_REF_INTERVAL;
    }
    else if (AbsoluteValue < ReferenceValue) {
        ret = ((cntr < ReferenceValue) && (cntr > AbsoluteValue)) ? OCU_CM_OUT_REF_INTERVAL : OCU_CM_IN_REF_INTERVAL;
    }
    else if (AbsoluteValue == cntr) { //If AbsoluteValue = ReferenceValue are equal, not specified in ASR
        ret = OCU_CM_IN_REF_INTERVAL;
    } else {
        ; /* Misra compliance */
    }

    /* @req SWS_Ocu_00098 */
    return ret;
}

/* @req SWS_Ocu_00094 */
#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
/* @req SWS_Ocu_00091 */
Ocu_ReturnType Ocu_SetAbsoluteThreshold(Ocu_ChannelType ChannelNumber,Ocu_ValueType ReferenceValue,Ocu_ValueType AbsoluteValue)
{


    /* @req SWS_Ocu_00095 **/
    VALIDATE_W_RV( (OcuDriverStatus != OCU_UNINIT), OCU_SETABSOLUTETHRESHOLD_SERVICE_ID, OCU_E_UNINIT,OCU_CM_OUT_REF_INTERVAL );

    /* @req SWS_Ocu_00096 **/
    VALIDATE_W_RV( (ChannelNumber < OCU_MATCH_CHANNEL_COUNT), OCU_SETABSOLUTETHRESHOLD_SERVICE_ID, OCU_E_PARAM_INVALID_CHANNEL,OCU_CM_OUT_REF_INTERVAL );


    /* @req SWS_Ocu_00098 */
    return setthrshld(ChannelNumber,ReferenceValue,AbsoluteValue);
}
#endif



/* @req SWS_Ocu_00103 */
#if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
/* @req SWS_Ocu_00100 */
Ocu_ReturnType Ocu_SetRelativeThreshold(Ocu_ChannelType ChannelNumber,Ocu_ValueType RelativeValue)
{

    Ocu_ValueType newAbsThreshld;
    Ocu_ValueType cntrval;
    uint8 cntrchnl;
    const volatile struct EMIOS_tag * emiosUnit;
    uint8 channelId;
    uint8 absChnlId;


    /* @req SWS_Ocu_00104 **/
    VALIDATE_W_RV( (OcuDriverStatus != OCU_UNINIT), OCU_SETRELATIVETHRESHOLD_SERVICE_ID, OCU_E_UNINIT,OCU_CM_OUT_REF_INTERVAL );

    /* @req SWS_Ocu_00105 **/
    VALIDATE_W_RV( (ChannelNumber < OCU_MATCH_CHANNEL_COUNT), OCU_SETRELATIVETHRESHOLD_SERVICE_ID, OCU_E_PARAM_INVALID_CHANNEL,OCU_CM_OUT_REF_INTERVAL );

    channelId = OcuConfigPtr->OcuChannelConfig[ChannelNumber].OcuChannelId;

    //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
    if (CHANNELS_PER_EMIOS_UNIT != 0) {
        emiosUnit = GET_EMIOS_UNIT(channelId/CHANNELS_PER_EMIOS_UNIT);
    } else { return OCU_CM_OUT_REF_INTERVAL; }
    absChnlId = GET_EMIOS_CHANNEL(channelId);

    cntrchnl  = (absChnlId < UNIFIED_CHANNEL_D) ? UNIFIED_CHANNEL_C:UNIFIED_CHANNEL_D ;

    cntrval = (Ocu_ValueType)(emiosUnit->CH[cntrchnl].CCNTR.R - 1UL);
    /* @req SWS_Ocu_00101 */
    newAbsThreshld = cntrval + RelativeValue;

    /* @req SWS_Ocu_00106 */
    /* @req SWS_Ocu_00107 */
    return setthrshld(ChannelNumber, cntrval, newAbsThreshld);

}
#endif



/* @req SWS_Ocu_00111 */
#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
/* @req SWS_Ocu_00108 */
void Ocu_DisableNotification(Ocu_ChannelType ChannelNumber)
{
    volatile struct EMIOS_tag * emiosUnit;
    uint8 channelId;
    uint8 absChnlId;

    /* @req SWS_Ocu_00112 **/
    VALIDATE( (OcuDriverStatus != OCU_UNINIT), OCU_DISABLE_NOTIFICATION_SERVICE_ID, OCU_E_UNINIT );

    /* @req SWS_Ocu_00113 **/
    VALIDATE( (ChannelNumber < OCU_MATCH_CHANNEL_COUNT), OCU_DISABLE_NOTIFICATION_SERVICE_ID, OCU_E_PARAM_INVALID_CHANNEL );

    /* @req SWS_Ocu_00114 **/
    VALIDATE( (OcuConfigPtr->OcuChannelConfig[ChannelNumber].OcuNotification != NULL), OCU_DISABLE_NOTIFICATION_SERVICE_ID, OCU_E_NO_VALID_NOTIF );

    channelId = OcuConfigPtr->OcuChannelConfig[ChannelNumber].OcuChannelId;

    //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
    if (CHANNELS_PER_EMIOS_UNIT != 0) {
        emiosUnit = GET_EMIOS_UNIT(channelId/CHANNELS_PER_EMIOS_UNIT);
    } else { return; }
    absChnlId = GET_EMIOS_CHANNEL(channelId);


    /* @req SWS_Ocu_00109 */
    emiosUnit->CH[absChnlId].CCR.B.FEN      = OCU_INTERRUPT_DISABLE; //Disable Interrupts

}
#endif



/* @req SWS_Ocu_00118 */
#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
/* @req SWS_Ocu_00115 */
void Ocu_EnableNotification(Ocu_ChannelType ChannelNumber)
{
    volatile struct EMIOS_tag * emiosUnit;
    uint8 channelId;
    uint8 absChnlId;

    /* @req SWS_Ocu_00119 **/
     VALIDATE( (OcuDriverStatus != OCU_UNINIT), OCU_ENABLE_NOTIFICATION_SERVICE_ID, OCU_E_UNINIT );

     /* @req SWS_Ocu_00120 **/
     VALIDATE( (ChannelNumber < OCU_MATCH_CHANNEL_COUNT), OCU_ENABLE_NOTIFICATION_SERVICE_ID, OCU_E_PARAM_INVALID_CHANNEL );

     /* @req SWS_Ocu_00121 **/
     VALIDATE( (OcuConfigPtr->OcuChannelConfig[ChannelNumber].OcuNotification != NULL), OCU_ENABLE_NOTIFICATION_SERVICE_ID, OCU_E_NO_VALID_NOTIF );

     channelId = OcuConfigPtr->OcuChannelConfig[ChannelNumber].OcuChannelId;

     //lint --e(506, 774)    PC-Lint exception Misra 2004:13.7, 2004:14.1, 2012:2.1 Allow configuration variables in boolean expression
     if (CHANNELS_PER_EMIOS_UNIT != 0) {
         emiosUnit = GET_EMIOS_UNIT(channelId/CHANNELS_PER_EMIOS_UNIT);
     } else { return; }
     absChnlId = GET_EMIOS_CHANNEL(channelId);


     /* @req SWS_Ocu_00116 */
     emiosUnit->CH[absChnlId].CCR.B.FEN      = OCU_INTERRUPT_ENABLE; //enable Interrupts
}
#endif



/* @req SWS_Ocu_00122 */
/* @req SWS_Ocu_00124 */
#if (OCU_VERSION_INFO_API == STD_ON)
void Ocu_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    /* @req SWS_Ocu_00126 **/
    VALIDATE( (versioninfo != NULL), OCU_GETVERSIONINFO_SERVICE_ID, OCU_E_PARAM_POINTER );

    /* @req SWS_Ocu_00123 */
    versioninfo->vendorID = OCU_VENDOR_ID;
    versioninfo->moduleID = OCU_MODULE_ID;
    versioninfo->sw_major_version = OCU_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = OCU_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = OCU_SW_PATCH_VERSION;

    return;
}
#endif

//lint -restore
