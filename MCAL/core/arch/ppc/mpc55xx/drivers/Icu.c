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


/** @tagSettings DEFAULT_ARCHITECTURE=PPC|MPC5607B|MPC5645S */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/*lint -e923 Cast in Freescale header file */

#include "Icu.h"
#include "Icu_Internal.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "mpc55xx.h"

#include "Os.h"
#include "Mcu.h"
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
#include "isr.h"
#include "irq.h"
#endif
#include "arc.h"
#include "SchM_Icu.h"

#if ( ICU_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(ICU_MODULE_ID,0,_api,_err); \
          return; \
        }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(ICU_MODULE_ID,0,_api,_err); \
          return (_rv); \
        }
#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_W_RV(_exp,_api,_err,_rv )
#endif

#if  ( ICU_DEV_ERROR_DETECT == STD_ON )
#define DET_REPORT_ERROR( _api, _err) (void)Det_ReportError(ICU_MODULE_ID, 0, _api, _err);
#else
#define DET_REPORT_ERROR( _api, _err)
#endif


/*lint -save -e9024 Considered ok, only advisory  */
#define ICU_ENTER_EXCLUSIVE_AREA(_area) SchM_Enter_Icu_##_area()
#define ICU_EXIT_EXCLUSIVE_AREA(_area) SchM_Exit_Icu_##_area()
/*lint -restore */


/*------------------ private function prototypes ----------------------*/


/*---------------------------------------------------------------------*/

const Icu_ConfigType* IcuConfigPtr = NULL;


/* Retrieves the physical Channel ID from the logical Channel ID */
static Icu_ChannelType GetPhysicalChannel (Icu_ChannelType ChannelID)
{
        return (IcuConfigPtr->Channels[ChannelID].physical_channel);
}

#if defined(CFG_MPC5645S)
#define IS_VALID_CHANNEL(_x) ( ((_x) < ICU_NUMBER_OF_CHANNELS) && \
                               ((((GetPhysicalChannel(_x)) <= (ICU_MAX_CHANNEL-1)) && ((GetPhysicalChannel(_x)) >= 32)) || \
                               (((GetPhysicalChannel(_x)) <= 23) && ((GetPhysicalChannel(_x)) >= 8))))
#elif defined(CFG_MPC5606S)
#define IS_VALID_CHANNEL(_x) ( ((_x) < ICU_NUMBER_OF_CHANNELS) && \
                               ((((GetPhysicalChannel(_x)) <= (ICU_MAX_CHANNEL-1)) && ((GetPhysicalChannel(_x)) >= 48)) || \
                               (((GetPhysicalChannel(_x)) <= 23) && ((GetPhysicalChannel(_x)) >= 8))))
#else  /* CFG_MPC560XB and CFG_MPC5746C */
#define IS_VALID_CHANNEL(_x) ( ((_x) < ICU_NUMBER_OF_CHANNELS) && \
                               ((GetPhysicalChannel(_x)) <= (ICU_MAX_CHANNEL-1)) )
#endif

typedef enum {
    ICU_STATE_UNINITIALIZED, ICU_STATE_INITIALIZED
} Icu_ModuleStateType;

static Icu_ModuleStateType Icu_ModuleState = ICU_STATE_UNINITIALIZED;


/* Struct contaning runtime settings for each channels */
typedef struct{
#if (ICU_TIMESTAMP_API == STD_ON)
    Icu_ValueType* NextTimeStampIndexPtr;
    uint16 NextTimeStampIndex;
    uint16 TimeStampBufferSize;
    uint16 NotifyInterval;
    uint16 NotificationCounter;
    boolean IsActive; /* IsActive is set to TRUE when Timestamping is executing */
#endif

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
    Icu_ValueType PreviousEndTime;  /* For DutyCycle calculations */
    Icu_ValueType Max_Counter;
    Icu_DutyCycleType DutyCycle;
    Icu_ValueType ElapsedTime;
    boolean PreviousEndTimeAcquired;
#endif

#if ((ICU_DISABLE_WAKEUP_API == STD_ON) || (ICU_ENABLE_WAKEUP_API == STD_ON))
boolean IsWakeupEnabled;
#endif

Icu_InputStateType InputState;

#if (ICU_EDGE_COUNT_API == STD_ON)
Icu_EdgeNumberType EdgeCounter;
#endif

/* IsRunning is set to TRUE when a running operation (i.e. Edge Counting, Timestamping or Signal Measurement) is executing*/
boolean IsRunning;

boolean NotificationEnabled;

}Icu_ChannelStructType;

static Icu_ChannelStructType IcuChannelRuntimeStruct[ICU_NUMBER_OF_CHANNELS];


ISR(Icu_Isr);

static void configureChannel(Icu_ChannelType channelId, const Icu_ChannelConfigurationType* channelConfig){
    Icu_ChannelType channel = channelConfig->physical_channel;
    volatile struct EMIOS_tag *emiosHw;

#if defined(CFG_MPC5645S) || defined (CFG_MPC560XB) || defined(CFG_MPC5606S) || defined(CFG_MPC5746C)
    if(channel <= (ICU_NUMBER_OF_EACH_EMIOS-1)) {
        emiosHw = &EMIOS_0;
    } else {
        emiosHw = &EMIOS_1;
        channel -= ICU_NUMBER_OF_EACH_EMIOS;
    }
#endif
#if defined(CFG_MPC560XB) || defined(CFG_MPC5645S) || defined(CFG_MPC5606S) || defined(CFG_MPC5746C)
    emiosHw->CH[channel].CCR.B.BSL = channelConfig->clksrc; /* Bus select */
    emiosHw->CH[channel].CCR.B.UCPRE = channelConfig->prescaler;
#else
    emiosHw->CH[channel].CCR.B.BSL = 0; /* Bus select */
    emiosHw->CH[channel].CCR.B.UCPRE = 1;
#endif
#if defined(CFG_MPC5746C)
    emiosHw->CH[channel].CCR.B.UCPREN = 1;
#else
    emiosHw->CH[channel].CCR.B.UCPEN = 1;
#endif
    emiosHw->CH[channel].CCR.B.IF = 1;
    emiosHw->CH[channel].CCR.B.FREN = 1;
    emiosHw->CH[channel].CCR.B.MODE = 0; /* Reset by setting GPIO */

    if( channelConfig->default_start_edge == ICU_BOTH_EDGES ) {
        emiosHw->CH[channel].CCR.B.EDSEL = 1; /* Both edges triggering */
    }
    else {
        emiosHw->CH[channel].CCR.B.EDSEL = 0; /* Single edge triggering */
        if( channelConfig->default_start_edge == ICU_RISING_EDGE ) {
            emiosHw->CH[channel].CCR.B.EDPOL = 1; /* Trigger on a rising edge */
        }
        else if( channelConfig->default_start_edge == ICU_FALLING_EDGE ) {
            emiosHw->CH[channel].CCR.B.EDPOL = 0; /* Trigger on a falling edge */
        }
        else {
            /* MISRA */;
        }
    }


#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
    if ((channelConfig->measurement_mode == ICU_MODE_SIGNAL_MEASUREMENT)) {

    	/* For Signal Measurement mode use IPM modes */
    	switch (channelConfig->signal_measurement_property) {
    	case ICU_PERIOD_TIME :
        	emiosHw->CH[channel].CCR.B.MODE = EMIOS_UC_MODE_IPM; /* Input Pulse Measurement */
        	break;
    	case ICU_DUTY_CYCLE:
    	case ICU_HIGH_TIME:
    	case ICU_LOW_TIME:
        	emiosHw->CH[channel].CCR.B.MODE = EMIOS_UC_MODE_IPWM; /* Input Pulse Width Measurement */
        	break;
    	default:
    		/* MISRA */
    		;
    	}


#if defined(CFG_MPC560XB) || defined(CFG_MPC5645S) || defined(CFG_MPC5606S) || defined(CFG_MPC5746C)
        Icu_ChannelType cntrbus_driver;

        /* Save counter wrap value. Fetch value from clksrc channel reg. */
        switch (channelConfig->clksrc) {
        case ICU_CLKSRC_COUNTER_BUS_A:
        case ICU_CLKSRC_INTERNAL_COUNTER:
            cntrbus_driver = 23;
            break;
        case ICU_CLKSRC_COUNTER_BUS_B_TO_E:
            /* Decide the counter bus driver channel */
            if ((channel >= 1) && (channel <= 7)) {
                cntrbus_driver = 0;
            }
            else if ((channel >= 9) && (channel <= 15)) {
                cntrbus_driver = 8;
            }
            else if ((channel >= 17) && (channel <= 22)) {
                cntrbus_driver = 16;
            }
            else if ((channel >= 25) && (channel <= 31)) {
                cntrbus_driver = 24;
            }
            else {
                /* Erroneous configuration. Should not occur after validation. */
                cntrbus_driver = 0;

                /* MISRA: PC-lint reacts on the channel numbers in the if-else conditions above.
                 * An extra condition is added to resolve PC-lint messages. Considering this block
                 * is for an erroneous configuration, an extra the check of channel number at this
                 * point should not effect normal execution.
                 */
                if(channel >= ICU_NUMBER_OF_EACH_EMIOS) {
                    channel -= ICU_NUMBER_OF_EACH_EMIOS;
                }
            }
            break;
        default:
            // Catch error during development. This function is called from Icu_Init.
            DET_REPORT_ERROR(ICU_INIT_ID, ICU_E_UNEXPECTED_EXECUTION);
            cntrbus_driver = 0;
        }

        /* Fetch counter wrap value from driver channel configuration */
        IcuChannelRuntimeStruct[channelId].Max_Counter = (Icu_ValueType) emiosHw->CH[cntrbus_driver].CBDR.R;

        /* Clear overflow flag */
        emiosHw->CH[channel].CSR.B.OVFL = 1;
#endif
    }
    else
#endif
    {
        /* For all other modes use SAIC */
        emiosHw->CH[channel].CCR.B.MODE = EMIOS_UC_MODE_SAIC; /* Single Action Input Capture */
    }
    emiosHw->CH[channel].CCR.B.FEN = 0;

    /** @req SWS_Icu_00040 */
    IcuChannelRuntimeStruct[channelId].InputState = ICU_IDLE;
    IcuChannelRuntimeStruct[channelId].IsActive = FALSE;
    IcuChannelRuntimeStruct[channelId].IsRunning = FALSE;
}
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)

static void installChannelInterrupt(uint8 hwUnit, Icu_ChannelType physical_channelId)
{
    /* Install ISR */
#if defined(CFG_MPC560XB) || defined(CFG_MPC5746C)
    Icu_ChannelType channel = (Icu_ChannelType) (physical_channelId + (uint8) (hwUnit * (uint8)ICU_NUMBER_OF_EACH_EMIOS));

    switch(channel)
    {
    case 0:
    case 1:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F0_F1),ICU_ISR_PRIORITY, 0);
        break;
    case 2:
    case 3:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F2_F3),ICU_ISR_PRIORITY, 0);
        break;
    case 4:
    case 5:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F4_F5),ICU_ISR_PRIORITY, 0);
        break;
    case 6:
    case 7:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F6_F7),ICU_ISR_PRIORITY, 0);
        break;
    case 8:
    case 9:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F8_F9),ICU_ISR_PRIORITY, 0);
        break;
    case 10:
    case 11:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F10_F11),ICU_ISR_PRIORITY, 0);
        break;
    case 12:
    case 13:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F12_F13),ICU_ISR_PRIORITY, 0);
        break;
    case 14:
    case 15:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F14_F15),ICU_ISR_PRIORITY, 0);
        break;
    case 16:
    case 17:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F16_F17),ICU_ISR_PRIORITY, 0);
        break;
    case 18:
    case 19:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F18_F19),ICU_ISR_PRIORITY, 0);
        break;
    case 20:
    case 21:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F20_F21),ICU_ISR_PRIORITY, 0);
        break;
    case 22:
    case 23:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F22_F23),ICU_ISR_PRIORITY, 0);
        break;
    case 24:
    case 25:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F24_F25),ICU_ISR_PRIORITY, 0);
        break;
    case 26:
    case 27:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F26_F27),ICU_ISR_PRIORITY, 0);
        break;
    case 28:
    case 29:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F28_F29),ICU_ISR_PRIORITY, 0);
        break;
    case 30:
    case 31:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F30_F31),ICU_ISR_PRIORITY, 0);
        break;
    case 32:
    case 33:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F0_F1),ICU_ISR_PRIORITY, 0);
        break;
    case 34:
    case 35:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F2_F3),ICU_ISR_PRIORITY, 0);
        break;
    case 36:
    case 37:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F4_F5),ICU_ISR_PRIORITY, 0);
        break;
    case 38:
    case 39:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F6_F7),ICU_ISR_PRIORITY, 0);
        break;
    case 40:
    case 41:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F8_F9),ICU_ISR_PRIORITY, 0);
        break;
    case 42:
    case 43:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F10_F11),ICU_ISR_PRIORITY, 0);
        break;
    case 44:
    case 45:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F12_F13),ICU_ISR_PRIORITY, 0);
        break;
    case 46:
    case 47:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F14_F15),ICU_ISR_PRIORITY, 0);
        break;
    case 48:
    case 49:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F16_F17),ICU_ISR_PRIORITY, 0);
        break;
    case 50:
    case 51:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F18_F19),ICU_ISR_PRIORITY, 0);
        break;
    case 52:
    case 53:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F20_F21),ICU_ISR_PRIORITY, 0);
        break;
    case 54:
    case 55:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F22_F23),ICU_ISR_PRIORITY, 0);
        break;
    case 56:
    case 57:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F24_F25),ICU_ISR_PRIORITY, 0);
        break;
    case 58:
    case 59:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F26_F27),ICU_ISR_PRIORITY, 0);
        break;
    case 60:
    case 61:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F28_F29),ICU_ISR_PRIORITY, 0);
        break;
    case 62:
    case 63:
        ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F30_F31),ICU_ISR_PRIORITY, 0);
        break;
    default:
        break;
    }
    /* Install ISR */
#elif defined(CFG_MPC5606S)
       Icu_ChannelType channel = (Icu_ChannelType) (physical_channelId + (uint8) (hwUnit * (uint8)ICU_NUMBER_OF_EACH_EMIOS));

       switch(channel)
       {
       case 8:
       case 9:
           ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F8_F9),ICU_ISR_PRIORITY, 0);
           break;
       case 10:
       case 11:
           ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F10_F11),ICU_ISR_PRIORITY, 0);
           break;
       case 12:
       case 13:
           ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F12_F13),ICU_ISR_PRIORITY, 0);
           break;
       case 14:
       case 15:
           ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F14_F15),ICU_ISR_PRIORITY, 0);
           break;
       case 16:
       case 17:
           ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F16_F17),ICU_ISR_PRIORITY, 0);
           break;
       case 18:
       case 19:
           ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F18_F19),ICU_ISR_PRIORITY, 0);
           break;
       case 20:
       case 21:
           ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F20_F21),ICU_ISR_PRIORITY, 0);
           break;
       case 22:
       case 23:
           ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F22_F23),ICU_ISR_PRIORITY, 0);
           break;
       case 48:
       case 49:
           ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F16_F17),ICU_ISR_PRIORITY, 0);
           break;
       case 50:
       case 51:
           ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F18_F19),ICU_ISR_PRIORITY, 0);
           break;
       case 52:
       case 53:
           ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F20_F21),ICU_ISR_PRIORITY, 0);
           break;
       case 54:
       case 55:
           ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F22_F23),ICU_ISR_PRIORITY, 0);
           break;
       default:
           break;
       }
 #elif defined(CFG_MPC5645S)

    switch(hwUnit) {
        case 0:
            switch(physical_channelId) {
                case 8:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F8),ICU_ISR_PRIORITY, 0);
                    break;
                case 9:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F9),ICU_ISR_PRIORITY, 0);
                    break;
                case 10:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F10),ICU_ISR_PRIORITY, 0);
                    break;
                case 11:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F11),ICU_ISR_PRIORITY, 0);
                    break;
                case 12:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F12),ICU_ISR_PRIORITY, 0);
                    break;
                case 13:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F13),ICU_ISR_PRIORITY, 0);
                    break;
                case 14:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F14),ICU_ISR_PRIORITY, 0);
                    break;
                case 15:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F15),ICU_ISR_PRIORITY, 0);
                    break;
                case 16:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F16),ICU_ISR_PRIORITY, 0);
                    break;
                case 17:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F17),ICU_ISR_PRIORITY, 0);
                    break;
                case 18:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F18),ICU_ISR_PRIORITY, 0);
                    break;
                case 19:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F19),ICU_ISR_PRIORITY, 0);
                    break;
                case 20:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F20),ICU_ISR_PRIORITY, 0);
                    break;
                case 21:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F21),ICU_ISR_PRIORITY, 0);
                    break;
                case 22:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F22),ICU_ISR_PRIORITY, 0);
                    break;
                case 23:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_0_GFR_F23),ICU_ISR_PRIORITY, 0);
                    break;
                default:
                    break;
            }
            break;
        case 1:
            switch(physical_channelId) {
                case 8:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F8),ICU_ISR_PRIORITY, 0);
                    break;
                case 9:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F9),ICU_ISR_PRIORITY, 0);
                    break;
                case 10:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F10),ICU_ISR_PRIORITY, 0);
                    break;
                case 11:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F11),ICU_ISR_PRIORITY, 0);
                    break;
                case 12:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F12),ICU_ISR_PRIORITY, 0);
                    break;
                case 13:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F13),ICU_ISR_PRIORITY, 0);
                    break;
                case 14:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F14),ICU_ISR_PRIORITY, 0);
                    break;
                case 15:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F15),ICU_ISR_PRIORITY, 0);
                    break;
                case 16:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F16),ICU_ISR_PRIORITY, 0);
                    break;
                case 17:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F17),ICU_ISR_PRIORITY, 0);
                    break;
                case 18:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F18),ICU_ISR_PRIORITY, 0);
                    break;
                case 19:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F19),ICU_ISR_PRIORITY, 0);
                    break;
                case 20:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F20),ICU_ISR_PRIORITY, 0);
                    break;
                case 21:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F21),ICU_ISR_PRIORITY, 0);
                    break;
                case 22:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F22),ICU_ISR_PRIORITY, 0);
                    break;
                case 23:
                    ISR_INSTALL_ISR2("IcuIsr", Icu_Isr, (int16_t)(EMIOS_1_GFR_F23),ICU_ISR_PRIORITY, 0);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
#endif

}
#endif


void Icu_Init(const Icu_ConfigType* ConfigPtr) {

    /** @req SWS_Icu_00001 */
    /** @req SWS_Icu_00023 */
    VALIDATE( ( NULL != ConfigPtr ), ICU_INIT_ID, ICU_E_PARAM_CONFIG );

    /** @req SWS_Icu_00271 */
    /** @req SWS_Icu_00220 */
    if( Icu_ModuleState == ICU_STATE_INITIALIZED ) {
#if ICU_DEV_ERROR_DETECT==STD_ON
        (void)Det_ReportError(ICU_MODULE_ID,0,ICU_INIT_ID,ICU_E_ALREADY_INITIALIZED);
#endif
        return;
    }

    Icu_ModuleState = ICU_STATE_INITIALIZED;

    IcuConfigPtr = ConfigPtr;

#if defined(CFG_MPC5645S) || defined (CFG_MPC560XB) || defined(CFG_MPC5606S) || defined(CFG_MPC5746C)
    /* Stop channels when in debug mode */
    EMIOS_0.MCR.B.FRZ = ICU_FREEZE_ENABLE;
    EMIOS_1.MCR.B.FRZ = ICU_FREEZE_ENABLE;

    /* Use global time base */
    EMIOS_0.MCR.B.GTBE = 1;
    EMIOS_1.MCR.B.GTBE = 1;

    /* Enable clock */
    EMIOS_0.MCR.B.MDIS = 0;
    EMIOS_1.MCR.B.MDIS = 0;

#endif
    Icu_ChannelType channel_iterator;

    for (channel_iterator = 0; channel_iterator < ICU_NUMBER_OF_CHANNELS; channel_iterator++) {
        const Icu_ChannelConfigurationType* channelConfig = &ConfigPtr->Channels[channel_iterator];


        Icu_ChannelType physical_channel = channelConfig->physical_channel;
        uint8 hwUnit = 0;
#if defined(CFG_MPC5645S) || defined(CFG_MPC560XB) || defined(CFG_MPC5606S)|| defined(CFG_MPC5746C)
        if(physical_channel >= ICU_NUMBER_OF_EACH_EMIOS) {
            physical_channel -= ICU_NUMBER_OF_EACH_EMIOS;
            hwUnit = 1;
        }
#endif

        configureChannel( channel_iterator, channelConfig );
#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
        installChannelInterrupt(hwUnit, physical_channel);
#endif

        /** @req SWS_Icu_00061 */
        Icu_DisableNotification(channel_iterator);

#if (ICU_DISABLE_WAKEUP_API == STD_ON)
        /** @req SWS_Icu_00121 */
        Icu_DisableWakeup(channel_iterator);
#endif

#if (ICU_SET_MODE_API == STD_ON)
        /** @req SWS_Icu_00060 */
        Icu_SetMode( ICU_MODE_NORMAL );
#endif

#if (ICU_TIMESTAMP_API == STD_ON)
        Icu_ChannelType active_iterator;

        for (active_iterator = 0; active_iterator < ICU_NUMBER_OF_CHANNELS; active_iterator++) {
            IcuChannelRuntimeStruct[active_iterator].IsActive = FALSE;
        }
#endif

    }
    /* Enable clock */
    EMIOS_0.MCR.B.MDIS = 0;
    EMIOS_1.MCR.B.MDIS = 0;
}


/** @req SWS_Icu_00092 */
/** @req SWS_Icu_00301 */
#if (ICU_DE_INIT_API == STD_ON)
static void DeInitChannel(Icu_ChannelType Channel) {

    Icu_ChannelType emios_ch = GetPhysicalChannel(Channel);


    volatile struct EMIOS_tag *emiosHw;

#if defined(CFG_MPC5645S) || defined(CFG_MPC560XB) || defined(CFG_MPC5606S)|| defined(CFG_MPC5746C)
    if(emios_ch <= (ICU_NUMBER_OF_EACH_EMIOS-1)) {
        emiosHw = &EMIOS_0;
    } else {
        emiosHw = &EMIOS_1;
        emios_ch -= ICU_NUMBER_OF_EACH_EMIOS;
    }
#else
    emiosHw = &EMIOS;
#endif

    /** @req SWS_Icu_00036 */
    /* Set registers topPower on reset values */
    emiosHw->CH[emios_ch].CADR.R = 0;
    emiosHw->CH[emios_ch].CCR.B.MODE = 0; /* Set to GPIO Mode */
    emiosHw->CH[emios_ch].CCR.B.EDSEL = 0; /* Single edge triggering */
    emiosHw->CH[emios_ch].CCR.B.EDPOL = 0; /* Trigger on a falling edge */

    /* @req SWS_Icu_0037 */
    Icu_DisableNotification(Channel);

}

/* De-initialize the ICU module */
/** @req SWS_Icu_00193 */
void Icu_DeInit( void ) {

    /** @req ICU268 */
    VALIDATE(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_DEINIT_ID, ICU_E_UNINIT);

    Icu_ChannelType channel_iterator;

    /** @req SWS_Icu_00152 */
    /* Check if any channel is currently active.*/
    for (channel_iterator = 0; channel_iterator < ICU_NUMBER_OF_CHANNELS; channel_iterator++) {
        if (IcuChannelRuntimeStruct[channel_iterator].IsRunning) {
            return;
        }
    }


    for (channel_iterator = 0; channel_iterator < ICU_NUMBER_OF_CHANNELS; channel_iterator++) {
        DeInitChannel(channel_iterator);
    }

    Icu_ModuleState = ICU_STATE_UNINITIALIZED;

}
#endif

/** @req SWS_Icu_00095 */
/** @req SWS_Icu_00303 */
#if (ICU_SET_MODE_API == STD_ON)
/* Sets the ICU mode */
/** @req SWS_Icu_00194 */
void Icu_SetMode( Icu_ModeType Mode ){

    /** @req SWS_Icu_00125 */
    VALIDATE(((Mode == ICU_MODE_NORMAL) || (Mode == ICU_MODE_SLEEP)), ICU_SETMODE_ID, ICU_E_PARAM_MODE);

    /* NOT IMPLEMENTED: Decide what registers are affected */
}
#endif
/** @req SWS_Icu_00096 */
/** @req SWS_Icu_00306 */
#if (ICU_DISABLE_WAKEUP_API == STD_ON)
/* Disables the wakeup capability of a single ICU channel */
void Icu_DisableWakeup( Icu_ChannelType Channel ){

    /** @req ICU268 */
    VALIDATE(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_DISABLEWAKEUP_ID, ICU_E_UNINIT);

    /** @req SWS_Icu_00024 */
    VALIDATE(IS_VALID_CHANNEL(Channel), ICU_DISABLEWAKEUP_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00059 */
    VALIDATE(( IcuConfigPtr->Channels[Channel].wakeup_capability), ICU_DISABLEWAKEUP_ID, ICU_E_PARAM_CHANNEL);


    /* NOT IMPLEMENTED: Disable wakeup in channel hardware */

    IcuChannelRuntimeStruct[Channel].IsWakeupEnabled = FALSE;

}
#endif

/** @req SWS_Icu_00097 */
/** @req SWS_Icu_00308 */
#if (ICU_ENABLE_WAKEUP_API == STD_ON)
/* (Re-)enables the wakeup capability of the given ICU channel */
/** @req SWS_Icu_00196 */
void Icu_EnableWakeup( Icu_ChannelType Channel ){
    /** @req ICU268 */
    VALIDATE(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_ENABLEWAKEUP_ID, ICU_E_UNINIT);

    /** @req SWS_Icu_00155 */
    VALIDATE(IS_VALID_CHANNEL(Channel), ICU_ENABLEWAKEUP_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00156 */
    VALIDATE(( IcuConfigPtr->Channels[Channel].wakeup_capability), ICU_ENABLEWAKEUP_ID, ICU_E_PARAM_CHANNEL);

    /* NOT IMPLEMENTED: Enable wakeup in channel hardware */

    IcuChannelRuntimeStruct[Channel].IsWakeupEnabled = TRUE;

}
#endif

/** @req SWS_Icu_00360 */
/** @req SWS_Icu_00362 */
#if ((ICU_WAKEUP_FUNCTIONALITY_API == STD_ON) && (ICU_REPORT_WAKEUP_SOURCE == STD_ON))
/* Checks if a wakeup capable ICU channel is the source for a wakeup event
 * and calls the ECU state manager service EcuM_SetWakeupEvent
 * in case of a valid ICU channel wakeup event. */
/** @req SWS_Icu_00358 */
void Icu_CheckWakeup( EcuM_WakeupSourceType WakeupSource ){

    /** @req SWS_Icu_00363 */
    /** @req ICU268 */

    VALIDATE((Icu_ModuleState == ICU_STATE_INITIALIZED), ICU_CHECKWAKEUP_ID, ICU_E_UNINIT);

    /* NOT IMPLEMENTED: Implement functionality */
}
#endif


/* Sets the activation-edge for the given channel */
/** @req SWS_Icu_00197 */
void Icu_SetActivationCondition( Icu_ChannelType Channel, Icu_ActivationType Activation ){

    volatile struct EMIOS_tag *emiosHw;
    Icu_ChannelType emios_ch = GetPhysicalChannel(Channel);

    /** @req ICU268 */
    VALIDATE(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_SETACTIVATIONCONDITION_ID, ICU_E_UNINIT);

    /** @req SWS_Icu_00159 */
    VALIDATE(IS_VALID_CHANNEL(Channel), ICU_SETACTIVATIONCONDITION_ID, ICU_E_PARAM_CHANNEL);
    /** @req SWS_Icu_00090 */
    VALIDATE(( IcuConfigPtr->Channels[Channel].measurement_mode != ICU_MODE_SIGNAL_MEASUREMENT), ICU_SETACTIVATIONCONDITION_ID, ICU_E_PARAM_CHANNEL);
    /** @req SWS_Icu_00043 */
    VALIDATE((( Activation == ICU_RISING_EDGE ) || ( Activation == ICU_FALLING_EDGE ) || ( Activation == ICU_BOTH_EDGES )), ICU_SETACTIVATIONCONDITION_ID, ICU_E_PARAM_ACTIVATION);

#if defined(CFG_MPC5645S) || defined(CFG_MPC560XB) || defined(CFG_MPC5606S)|| defined(CFG_MPC5746C)
    if(emios_ch <= (ICU_NUMBER_OF_EACH_EMIOS-1)) {
        emiosHw = &EMIOS_0;
    } else {
        emiosHw = &EMIOS_1;
        emios_ch -= ICU_NUMBER_OF_EACH_EMIOS;
    }

    emiosHw->CH[emios_ch].CCR.B.MODE = EMIOS_UC_MODE_SAIC; /* Single Action Input Capture */

    if( Activation == ICU_BOTH_EDGES ) {
        emiosHw->CH[emios_ch].CCR.B.EDSEL = 1; /* Both edges triggering */
    }
    else {
        emiosHw->CH[emios_ch].CCR.B.EDSEL = 0; /* Single edge triggering */
        if( Activation == ICU_RISING_EDGE ) {
            emiosHw->CH[emios_ch].CCR.B.EDPOL = 1; /* Trigger on a rising edge */
        }
        else if( Activation == ICU_FALLING_EDGE ) {
            emiosHw->CH[emios_ch].CCR.B.EDPOL = 0; /* Trigger on a falling edge */
        }
        else
        {
            /* MISRA */;
        }
    }

    /** @req SWS_Icu_00139 */
#if ((ICU_EDGE_DETECT_API == STD_ON) || (ICU_SIGNAL_MEASUREMENT_API == STD_ON))
    IcuChannelRuntimeStruct[Channel].InputState = ICU_IDLE;
#endif

#endif
}


/* Disables the notification of a channel */
/** @req SWS_Icu_00198 */
void Icu_DisableNotification( Icu_ChannelType Channel ){

    /** @req ICU268 */
    VALIDATE(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_DISABLENOTIFICATION_ID, ICU_E_UNINIT);

    /** @req SWS_Icu_00160 */
    VALIDATE(IS_VALID_CHANNEL(Channel), ICU_DISABLENOTIFICATION_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00009 */
    VALIDATE((Channel < ICU_NUMBER_OF_CHANNELS), ICU_DISABLENOTIFICATION_ID, ICU_E_PARAM_CHANNEL);
    IcuChannelRuntimeStruct[Channel].NotificationEnabled = FALSE;

}

/* Enables the notification on the given channel */
/** @req SWS_Icu_00199 */
void Icu_EnableNotification( Icu_ChannelType Channel ){

    /** @req ICU268 */
    VALIDATE(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_ENABLENOTIFICATION_ID, ICU_E_UNINIT);

    /** @req SWS_Icu_00161 */
    VALIDATE(IS_VALID_CHANNEL(Channel), ICU_ENABLENOTIFICATION_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00010 */
    IcuChannelRuntimeStruct[Channel].NotificationEnabled = TRUE;
}

/** @req SWS_Icu_00122 */
/** @req SWS_Icu_00315 */

#if (ICU_GET_INPUT_STATE_API == STD_ON)
/* Returns the status of the ICU input */
/** @req SWS_Icu_00200 */
Icu_InputStateType Icu_GetInputState( Icu_ChannelType Channel ){

    /** @req ICU268 */
    VALIDATE_W_RV(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_GETINPUTSTATE_ID, ICU_E_UNINIT, ICU_IDLE);

    /** @req SWS_Icu_00162 */
    /** @req SWS_Icu_00049 */
    VALIDATE_W_RV(IS_VALID_CHANNEL(Channel), ICU_GETINPUTSTATE_ID, ICU_E_PARAM_CHANNEL, ICU_IDLE);

    /** @req SWS_Icu_00030 */
    /** @req SWS_Icu_00162 */
    VALIDATE_W_RV((( IcuConfigPtr->Channels[Channel].measurement_mode == ICU_MODE_SIGNAL_EDGE_DETECT) ||
                   ( IcuConfigPtr->Channels[Channel].measurement_mode == ICU_MODE_SIGNAL_MEASUREMENT)) ,
                     ICU_GETINPUTSTATE_ID, ICU_E_PARAM_CHANNEL, ICU_IDLE);

    /* Return the current input status for the channel */
     Icu_InputStateType CurrentState = IcuChannelRuntimeStruct[Channel].InputState;

    /** @req SWS_Icu_00032 */
    if (CurrentState == ICU_ACTIVE) {
        IcuChannelRuntimeStruct[Channel].InputState = ICU_IDLE;
    }

    if (IcuConfigPtr->Channels[Channel].measurement_mode == ICU_MODE_SIGNAL_MEASUREMENT)
    {
#if defined(CFG_MPC5645S)
        /* ICU_MODE_SIGNAL_MEASUREMENT is NOT IMPLEMENTED for MPC5645S*/
        return (ICU_IDLE);
#else
    /** @req SWS_Icu_00314*/
        /* Check if measurement is completed before returning ICU_ACTIVE */

        if (IcuChannelRuntimeStruct[Channel].IsRunning) {
            IcuChannelRuntimeStruct[Channel].InputState = CurrentState;
            return (ICU_IDLE);
        }
        else {
            return (CurrentState);
        }


#endif
    }
    else
    {
        /** @req SWS_Icu_00313 */
        /** @req SWS_Icu_00031 */
        return (CurrentState);
    }
}
#endif


/** @req SWS_Icu_00098 */
/** @req SWS_Icu_00321 */
/** @req SWS_Icu_00099 */
/** @req SWS_Icu_00323 */
/** @req SWS_Icu_00100 */
/** @req SWS_Icu_00325 */
#if (ICU_TIMESTAMP_API == STD_ON)

/* Timestamp_ISR is called by the Icu_Isr when a timestamp interupt is raised.
 * It captures the timestamp value into the buffer provided in the call to Icu_StartTimestamp().
 */
static void Timestamp_ISR(Icu_ChannelType Channel)
{
    Icu_ChannelType emios_ch = GetPhysicalChannel(Channel);

    volatile struct EMIOS_tag *emiosHw;
#if defined(CFG_MPC5645S) || defined(CFG_MPC560XB) || defined(CFG_MPC5606S) || defined(CFG_MPC5746C)
    if(emios_ch <= (ICU_NUMBER_OF_EACH_EMIOS-1)) {
        emiosHw = &EMIOS_0;
    } else {
        emiosHw = &EMIOS_1;
        emios_ch -= ICU_NUMBER_OF_EACH_EMIOS;
    }
#else
    emiosHw = &EMIOS;
#endif

    /* Buffer pointer null check */
    if (IcuChannelRuntimeStruct[Channel].NextTimeStampIndexPtr == NULL) {
        return;
    }

    /* Fetch current timestamp value */
    IcuChannelRuntimeStruct[Channel].NextTimeStampIndexPtr[IcuChannelRuntimeStruct[Channel].NextTimeStampIndex] = (Icu_ValueType) emiosHw->CH[emios_ch].CADR.R;

    /* Increase Index pointer */
    IcuChannelRuntimeStruct[Channel].NextTimeStampIndex++;

    /* Handle End of Buffer */
    if (IcuChannelRuntimeStruct[Channel].NextTimeStampIndex >= (IcuChannelRuntimeStruct[Channel].TimeStampBufferSize))
    {
        switch (IcuConfigPtr->Channels[Channel].buffer_type)
        {
           case ICU_LINEAR_BUFFER:
                /* Stop capturing timestamps  */

                /** @req SWS_Icu_00065 */
                /* Stop capturing timestamps, but keep nextTimeStampindex value  */

                /* Disable the interrupt.  */
                emiosHw->CH[emios_ch].CCR.B.FEN = 0;

                IcuChannelRuntimeStruct[Channel].IsRunning = FALSE;
                IcuChannelRuntimeStruct[Channel].IsActive = FALSE;
                break;

           case ICU_CIRCULAR_BUFFER:
               /** @req SWS_Icu_0064 */
               /* next timestamp writes over the first item, and continues capturing timestamps  */
               IcuChannelRuntimeStruct[Channel].NextTimeStampIndex = 0;

               break;

           default:
               /* No other values possible. */
               break;

        }
    }

}

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
static void SignalMeasurementISR(Icu_ChannelType Channel)
{
    Icu_ChannelType emios_ch = GetPhysicalChannel(Channel);
    Icu_ValueType startTime;
    Icu_ValueType endTime;

    volatile struct EMIOS_tag *emiosHw;
#if defined(CFG_MPC5645S) || defined(CFG_MPC560XB) || defined(CFG_MPC5606S) || defined(CFG_MPC5746C)
    if(emios_ch <= (ICU_NUMBER_OF_EACH_EMIOS-1)) {
        emiosHw = &EMIOS_0;
    } else {
        emiosHw = &EMIOS_1;
        emios_ch -= ICU_NUMBER_OF_EACH_EMIOS;
    }
#else
    emiosHw = &EMIOS;
#endif

    // Note: The order of reading these registers is important to get coherent data
    endTime = (Icu_ValueType) emiosHw->CH[emios_ch].CADR.R;
    startTime = (Icu_ValueType) emiosHw->CH[emios_ch].CBDR.R;

    // Handle counter wrapping of end time compared to start time.
    // Note! Only one wrap is handled.
    if ((emiosHw->CH[emios_ch].CSR.B.OVFL == 1) ||
            (endTime < startTime))
    {
        endTime += IcuChannelRuntimeStruct[Channel].Max_Counter;

        /* Clear overflow flag */
        emiosHw->CH[emios_ch].CSR.B.OVFL = 1;
    }

    switch (IcuConfigPtr->Channels[Channel].signal_measurement_property) {
        case ICU_DUTY_CYCLE:
            /** @req SWS_Icu_00137 */
            /** @req SWS_Icu_00343 */
            if (IcuChannelRuntimeStruct[Channel].PreviousEndTimeAcquired) {
                Icu_ValueType previousEndTime = IcuChannelRuntimeStruct[Channel].PreviousEndTime;

                // Store the end time until next run of this function
                IcuChannelRuntimeStruct[Channel].PreviousEndTime = endTime;

                IcuChannelRuntimeStruct[Channel].DutyCycle.ActiveTime = endTime - startTime;

                // Handle counter wrapping current pulse end time compared to previous pulse end time.
                // Note! Only one wrap is handled.
                if (endTime < previousEndTime) {
                    endTime += IcuChannelRuntimeStruct[Channel].Max_Counter;
                }

                IcuChannelRuntimeStruct[Channel].DutyCycle.PeriodTime = endTime - previousEndTime;
            } else {
                // Store the pulse end time until next run of this function
                IcuChannelRuntimeStruct[Channel].PreviousEndTime = endTime;
                IcuChannelRuntimeStruct[Channel].PreviousEndTimeAcquired = TRUE;
            }
            break;

        case ICU_PERIOD_TIME:
        case ICU_HIGH_TIME:
        case ICU_LOW_TIME:
            IcuChannelRuntimeStruct[Channel].ElapsedTime = endTime - startTime;
            break;

        default:
            /* MISRA */
            ;
    }
}

/* Reset Signal measurement runtime properties */
static void Init_Signal_Measurement(Icu_ChannelType Channel)
{
    IcuChannelRuntimeStruct[Channel].ElapsedTime = 0;
    IcuChannelRuntimeStruct[Channel].DutyCycle.ActiveTime = 0;
    IcuChannelRuntimeStruct[Channel].DutyCycle.PeriodTime = 0;
    IcuChannelRuntimeStruct[Channel].PreviousEndTime = 0;
    IcuChannelRuntimeStruct[Channel].PreviousEndTimeAcquired = FALSE;
}

#endif

/* Initialize Timestamping runtime properties */
/** @req SWS_Icu_00317 */
static void Init_Timestamping(Icu_ChannelType Channel, Icu_ValueType* StartPtr, uint16 Size, uint16 NotifyInterval)
{
    IcuChannelRuntimeStruct[Channel].NextTimeStampIndexPtr = StartPtr;
    IcuChannelRuntimeStruct[Channel].TimeStampBufferSize = Size;
    IcuChannelRuntimeStruct[Channel].NextTimeStampIndex = 0;
    IcuChannelRuntimeStruct[Channel].NotifyInterval = NotifyInterval;
    IcuChannelRuntimeStruct[Channel].NotificationCounter = 0;
}

/* Reset Timestamping runtime properties */
static void Clear_Timestamping(Icu_ChannelType Channel)
{
    IcuChannelRuntimeStruct[Channel].NextTimeStampIndexPtr = NULL;
    IcuChannelRuntimeStruct[Channel].TimeStampBufferSize = 0;
    IcuChannelRuntimeStruct[Channel].NextTimeStampIndex = 0;
    IcuChannelRuntimeStruct[Channel].NotifyInterval = 0;
    IcuChannelRuntimeStruct[Channel].NotificationCounter = 0;
}


/* Starts the capturing of timer values on the edges*/
/** @req SWS_Icu_00201 */
void Icu_StartTimestamp( Icu_ChannelType Channel, Icu_ValueType* BufferPtr, uint16 BufferSize, uint16 NotifyInterval ){

    /** @req ICU268 */
    VALIDATE(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_STARTTIMESTAMP_ID, ICU_E_UNINIT);

    /** @req SWS_Icu_00163 */
    VALIDATE(IS_VALID_CHANNEL(Channel), ICU_STARTTIMESTAMP_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00120 */
    VALIDATE((BufferPtr != NULL), ICU_STARTTIMESTAMP_ID, ICU_E_PARAM_BUFFER_PTR);

    /** @req SWS_Icu_00108 */
     VALIDATE((BufferSize > 0), ICU_STARTTIMESTAMP_ID, ICU_E_PARAM_BUFFER_SIZE);

    /** @req SWS_Icu_00354 */
    VALIDATE(((IcuConfigPtr->Channels[Channel].notification != NULL) && (NotifyInterval > 0)), ICU_STARTTIMESTAMP_ID, ICU_E_PARAM_NOTIFY_INTERVAL);

    /** @req SWS_Icu_00066 */
    /** @req SWS_Icu_00163 */
    VALIDATE(( IcuConfigPtr->Channels[Channel].measurement_mode == ICU_MODE_TIMESTAMP), ICU_STARTTIMESTAMP_ID, ICU_E_PARAM_CHANNEL);

    Init_Timestamping(Channel, BufferPtr, BufferSize, NotifyInterval);

    /** @req SWS_Icu_00063 */
    /* Enable Interrupt for the channels */
    volatile struct EMIOS_tag *emiosHw;
    Icu_ChannelType emios_ch = GetPhysicalChannel(Channel);

#if defined(CFG_MPC5645S) || defined(CFG_MPC560XB) || defined(CFG_MPC5606S) || defined(CFG_MPC5746C)
     if(emios_ch <= (ICU_NUMBER_OF_EACH_EMIOS-1)) {
         emiosHw = &EMIOS_0;
     } else {
         emiosHw = &EMIOS_1;
         emios_ch -= ICU_NUMBER_OF_EACH_EMIOS;
     }
 #else
     emiosHw = &EMIOS;
 #endif


    emiosHw->CH[emios_ch].CSR.B.FLAG = 1;
    emiosHw->CH[emios_ch].CCR.B.FEN = 1;

    /* Reset counter */
    emiosHw->CH[emios_ch].CCR.B.MODE = 0; /* Reset by setting GPIO */
    emiosHw->CH[emios_ch].CCR.B.MODE = EMIOS_UC_MODE_SAIC; /* Single Action Input Capture */

    IcuChannelRuntimeStruct[Channel].IsRunning = TRUE;
    IcuChannelRuntimeStruct[Channel].IsActive = TRUE;

}

/* Stops the timestamp measurement of the given channel */
/** @req SWS_Icu_00202 */
void Icu_StopTimestamp( Icu_ChannelType Channel ){

    /** @req ICU268 */
    VALIDATE(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_STOPTIMESTAMP_ID, ICU_E_UNINIT);

    /** @req SWS_Icu_00164 */
    VALIDATE(IS_VALID_CHANNEL(Channel), ICU_STOPTIMESTAMP_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00165 */
    /** @req SWS_Icu_00164 */
    VALIDATE(( IcuConfigPtr->Channels[Channel].measurement_mode == ICU_MODE_TIMESTAMP), ICU_STOPTIMESTAMP_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00166 */
    VALIDATE((IcuChannelRuntimeStruct[Channel].IsActive), ICU_STOPTIMESTAMP_ID, ICU_E_NOT_STARTED);

    /** @req SWS_Icu_00067 */
    /* Disable the interrupt.  */
    volatile struct EMIOS_tag *emiosHw;
    Icu_ChannelType emios_ch = GetPhysicalChannel(Channel);

 #if defined(CFG_MPC5645S) || defined(CFG_MPC560XB)|| defined(CFG_MPC5606S)|| defined(CFG_MPC5746C)
     if(emios_ch <= (ICU_NUMBER_OF_EACH_EMIOS-1)) {
         emiosHw = &EMIOS_0;
     } else {
         emiosHw = &EMIOS_1;
         emios_ch -= ICU_NUMBER_OF_EACH_EMIOS;
     }
 #else
     emiosHw = &EMIOS;
 #endif

   emiosHw->CH[emios_ch].CCR.B.FEN = 0;

    Clear_Timestamping(Channel);

    IcuChannelRuntimeStruct[Channel].IsRunning = FALSE;
    IcuChannelRuntimeStruct[Channel].IsActive = FALSE;

}

/* Reads the timestamp index of the given channel */
/** @req SWS_Icu_00203 */
Icu_IndexType Icu_GetTimestampIndex( Icu_ChannelType Channel ){

    /** @req ICU268 */
    VALIDATE_W_RV(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_GETTIMESTAMPINDEX_ID, ICU_E_UNINIT, 0);

    /** @req SWS_Icu_00169 */
    /** @req SWS_Icu_00107 */
    VALIDATE_W_RV(IS_VALID_CHANNEL(Channel), ICU_GETTIMESTAMPINDEX_ID, ICU_E_PARAM_CHANNEL, 0);

    /** @req SWS_Icu_00170 */
    VALIDATE_W_RV(( IcuConfigPtr->Channels[Channel].measurement_mode == ICU_MODE_TIMESTAMP), ICU_GETTIMESTAMPINDEX_ID, ICU_E_PARAM_CHANNEL,0);

    /** @req SWS_Icu_00135 */
    if (!(IcuChannelRuntimeStruct[Channel].IsActive)) { return (0); }

    /** @req SWS_Icu_00071 */
    /* return next timestamp index of channel_iterator to be written */
    return ((Icu_IndexType) IcuChannelRuntimeStruct[Channel].NextTimeStampIndex);
}

#endif /* #if(ICU_TIMESTAMP_API == STD_ON) */

/** @req SWS_Icu_00101 */
/** @req SWS_Icu_00327 */
/** @req SWS_Icu_00102 */
/** @req SWS_Icu_00329 */
/** @req SWS_Icu_00103 */
/** @req SWS_Icu_00331 */
/** @req SWS_Icu_00104 */
/** @req SWS_Icu_00333 */
#if (ICU_EDGE_COUNT_API == STD_ON)
/* Resets the value of the counted edges to zero */
/** @req SWS_Icu_00204 */
void Icu_ResetEdgeCount( Icu_ChannelType Channel ){

    /** @req ICU268 */
    VALIDATE(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_RESETEDGECOUNT_ID, ICU_E_UNINIT);

    /** @req SWS_Icu_00171 */
    VALIDATE(IS_VALID_CHANNEL(Channel), ICU_RESETEDGECOUNT_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00171 */
    VALIDATE(( IcuConfigPtr->Channels[Channel].measurement_mode == ICU_MODE_EDGE_COUNTER), ICU_RESETEDGECOUNT_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00072 */
    IcuChannelRuntimeStruct[Channel].EdgeCounter = 0;

}

/* Enables the counting of edges of the given channel */
/** @req SWS_Icu_00205 */

void Icu_EnableEdgeCount( Icu_ChannelType Channel ){

    /** @req ICU268 */
    VALIDATE(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_ENABLEEDGECOUNT_ID, ICU_E_UNINIT);

    /** @req SWS_Icu_00172 */
    VALIDATE(IS_VALID_CHANNEL(Channel), ICU_ENABLEEDGECOUNT_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00074 */
    /** @req SWS_Icu_00172 */
    VALIDATE(( IcuConfigPtr->Channels[Channel].measurement_mode == ICU_MODE_EDGE_COUNTER), ICU_ENABLEEDGECOUNT_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00073 */
    Icu_ChannelType emios_ch = GetPhysicalChannel(Channel);

    /** @req SWS_Icu_00078 */
    /* Enable Interrupt for the channels */
    volatile struct EMIOS_tag *emiosHw;
 #if defined(CFG_MPC5645S) || defined(CFG_MPC560XB) || defined(CFG_MPC5606S)|| defined(CFG_MPC5746C)
     if(emios_ch <= (ICU_NUMBER_OF_EACH_EMIOS-1)) {
         emiosHw = &EMIOS_0;
     } else {
         emiosHw = &EMIOS_1;
         emios_ch -= ICU_NUMBER_OF_EACH_EMIOS;
     }
 #else
     emiosHw = &EMIOS;
 #endif

    emiosHw->CH[emios_ch].CSR.B.FLAG = 1;
    emiosHw->CH[emios_ch].CCR.B.FEN = 1;

    IcuChannelRuntimeStruct[Channel].IsRunning = TRUE;
}

/* Disables the counting of edges of the given channel */
/** @req SWS_Icu_00206 */
void Icu_DisableEdgeCount( Icu_ChannelType Channel ){

    /** @req ICU268 */
    VALIDATE(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_DISABLEEDGECOUNT_ID, ICU_E_UNINIT);

    /** @req SWS_Icu_00173 */
    VALIDATE(IS_VALID_CHANNEL(Channel), ICU_DISABLEEDGECOUNT_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00173 */
    VALIDATE(( IcuConfigPtr->Channels[Channel].measurement_mode == ICU_MODE_EDGE_COUNTER), ICU_DISABLEEDGECOUNT_ID, ICU_E_PARAM_CHANNEL);

    Icu_ChannelType emios_ch = GetPhysicalChannel(Channel);

    /** @req SWS_Icu_00079 */
    /* Disable Interrupt for the channels */
    volatile struct EMIOS_tag *emiosHw;
 #if defined(CFG_MPC5645S) || defined(CFG_MPC560XB) || defined(CFG_MPC5606S)|| defined(CFG_MPC5746C)
     if(emios_ch <= (ICU_NUMBER_OF_EACH_EMIOS-1)) {
         emiosHw = &EMIOS_0;
     } else {
         emiosHw = &EMIOS_1;
         emios_ch -= ICU_NUMBER_OF_EACH_EMIOS;
     }
 #else
     emiosHw = &EMIOS;
 #endif

    emiosHw->CH[emios_ch].CCR.B.FEN = 0;

    IcuChannelRuntimeStruct[Channel].IsRunning = FALSE;

}

/* Reads the number of counted edges since last call of Icu_ResetEdgeCount */
/** @req SWS_Icu_00207 */
Icu_EdgeNumberType Icu_GetEdgeNumbers( Icu_ChannelType Channel ){

    /** @req ICU268 */
    VALIDATE_W_RV(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_GETEDGENUMBERS_ID, ICU_E_UNINIT, 0);

    /** @req SWS_Icu_00174 */
    /** @req SWS_Icu_00175 */
    VALIDATE_W_RV(IS_VALID_CHANNEL(Channel), ICU_GETEDGENUMBERS_ID, ICU_E_PARAM_CHANNEL, 0);

    /** @req SWS_Icu_00174 */
    /** @req SWS_Icu_00175 */
    VALIDATE_W_RV(( IcuConfigPtr->Channels[Channel].measurement_mode == ICU_MODE_EDGE_COUNTER), ICU_GETEDGENUMBERS_ID, ICU_E_PARAM_CHANNEL,0);

    /** @req SWS_Icu_00080 */
    /* return number of counted edges for Channel */
    return (IcuChannelRuntimeStruct[Channel].EdgeCounter);
}
#endif

/** @req SWS_Icu_00369 */
/** @req SWS_Icu_00370 */
/** @req SWS_Icu_00374 */
/** @req SWS_Icu_00375 */
#if (ICU_EDGE_DETECT_API == STD_ON)
/* (Re-)Enables the detection of edges of the given channel */
/** @req SWS_Icu_00364 */
void Icu_EnableEdgeDetection( Icu_ChannelType Channel ){

    /** @req ICU268 */
    VALIDATE(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_ENABLEEDGEDETECTION_ID, ICU_E_UNINIT);

    /** @req SWS_Icu_00371 */
    VALIDATE(IS_VALID_CHANNEL(Channel), ICU_ENABLEEDGEDETECTION_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00371 */
    VALIDATE(( IcuConfigPtr->Channels[Channel].measurement_mode == ICU_MODE_SIGNAL_EDGE_DETECT), ICU_ENABLEEDGEDETECTION_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00365 */
    /* Disable interrupt for the given Channel */
    volatile struct EMIOS_tag *emiosHw;
    Icu_ChannelType emios_ch = GetPhysicalChannel(Channel);

#if defined(CFG_MPC5645S) || defined(CFG_MPC560XB) || defined(CFG_MPC5606S)|| defined(CFG_MPC5746C)
    if(emios_ch <= (ICU_NUMBER_OF_EACH_EMIOS-1)) {
        emiosHw = &EMIOS_0;
    } else {
        emiosHw = &EMIOS_1;
        emios_ch -= ICU_NUMBER_OF_EACH_EMIOS;
    }
#endif


    emiosHw->CH[emios_ch].CSR.B.FLAG = 1;
    emiosHw->CH[emios_ch].CCR.B.FEN = 1;

}

/* Disables the detection of edges of the given channel */
/** @req SWS_Icu_00377 */
void Icu_DisableEdgeDetection( Icu_ChannelType Channel ){

    /** @req ICU268 */
    VALIDATE(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_DISABLEEDGEDETECTION_ID, ICU_E_UNINIT);

    /** @req SWS_Icu_00376 */
    VALIDATE(IS_VALID_CHANNEL(Channel), ICU_DISABLEEDGEDETECTION_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00376 */
    VALIDATE(( IcuConfigPtr->Channels[Channel].measurement_mode == ICU_MODE_SIGNAL_EDGE_DETECT), ICU_DISABLEEDGEDETECTION_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00372 */
    /* Disable interrupt for the given Channel */
    volatile struct EMIOS_tag *emiosHw;
    Icu_ChannelType emios_ch = GetPhysicalChannel(Channel);

#if defined(CFG_MPC5645S) || defined(CFG_MPC560XB) || defined(CFG_MPC5606S)|| defined(CFG_MPC5746C)
    if(emios_ch <= (ICU_NUMBER_OF_EACH_EMIOS-1)) {
        emiosHw = &EMIOS_0;
    } else {
        emiosHw = &EMIOS_1;
        emios_ch -= ICU_NUMBER_OF_EACH_EMIOS;
    }
#endif


    emiosHw->CH[emios_ch].CCR.B.FEN = 0;

}
#endif

/** @req SWS_Icu_00142 */
/** @req SWS_Icu_00335 */
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/* Starts the measurement of signals */
/** @req SWS_Icu_00208 */
void Icu_StartSignalMeasurement( Icu_ChannelType Channel ){

/*MPC5606S does not support IPM and IPWM modes*/
    /** @req ICU268 */
	VALIDATE(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_STARTSIGNALMEASUREMENT_ID, ICU_E_UNINIT);


    /** @req SWS_Icu_00176 */
    VALIDATE(IS_VALID_CHANNEL(Channel), ICU_STARTSIGNALMEASUREMENT_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00141 */
    /** @req SWS_Icu_00176 */
    VALIDATE(( IcuConfigPtr->Channels[Channel].measurement_mode == ICU_MODE_SIGNAL_MEASUREMENT), ICU_STARTSIGNALMEASUREMENT_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00146 */
    IcuChannelRuntimeStruct[Channel].InputState = ICU_IDLE;
    Init_Signal_Measurement(Channel);

    /** @req SWS_Icu_00063 */
    /* Enable Interrupt for the channels */
    volatile struct EMIOS_tag *emiosHw;
    Icu_ChannelType emios_ch = GetPhysicalChannel(Channel);

#if defined(CFG_MPC5645S) || defined(CFG_MPC560XB)|| defined(CFG_MPC5746C)
    if(emios_ch <= (ICU_NUMBER_OF_EACH_EMIOS-1)) {
        emiosHw = &EMIOS_0;
    } else {
        emiosHw = &EMIOS_1;
        emios_ch -= ICU_NUMBER_OF_EACH_EMIOS;
    }
#else
    emiosHw = &EMIOS;
#endif


    emiosHw->CH[emios_ch].CSR.B.FLAG = 1;
    emiosHw->CH[emios_ch].CCR.B.FEN = 1;

    /* Reset counter */
    emiosHw->CH[emios_ch].CCR.B.MODE = 0; /* Reset by setting GPIO */

    const Icu_ChannelConfigurationType* channelConfig = &IcuConfigPtr->Channels[Channel];

    /* For Signal Measurement mode use IPM modes */
    switch (channelConfig->signal_measurement_property) {
    case ICU_PERIOD_TIME :
        emiosHw->CH[emios_ch].CCR.B.MODE = EMIOS_UC_MODE_IPM; /* Input Pulse Measurement */
        break;
    case ICU_DUTY_CYCLE :
    case ICU_HIGH_TIME:
    case ICU_LOW_TIME:
        emiosHw->CH[emios_ch].CCR.B.MODE = EMIOS_UC_MODE_IPWM; /* Input Pulse Width Measurement */
        break;
    default:
        /* MISRA */
        ;
    }

	IcuChannelRuntimeStruct[Channel].IsRunning = TRUE;



}

/* Stops the measurement of signals of the given channel */
/** @req SWS_Icu_00209 */
void Icu_StopSignalMeasurement( Icu_ChannelType Channel ){

/*MPC5606S does not support IPM and IPWM modes*/
    /** @req ICU268 */
    VALIDATE(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_STOPSIGNALMEASUREMENT_ID, ICU_E_UNINIT);

    /** @req SWS_Icu_00176 */
    VALIDATE(IS_VALID_CHANNEL(Channel), ICU_STOPSIGNALMEASUREMENT_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00144 */
    /** @req SWS_Icu_00177 */
    VALIDATE(( IcuConfigPtr->Channels[Channel].measurement_mode == ICU_MODE_SIGNAL_MEASUREMENT), ICU_STOPSIGNALMEASUREMENT_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00143 */
    /* Disable the interrupt.  */
    volatile struct EMIOS_tag *emiosHw;
    Icu_ChannelType emios_ch = GetPhysicalChannel(Channel);

#if defined(CFG_MPC5645S) || defined(CFG_MPC560XB)|| defined(CFG_MPC5746C)
    if(emios_ch <= (ICU_NUMBER_OF_EACH_EMIOS-1)) {
        emiosHw = &EMIOS_0;
    } else {
        emiosHw = &EMIOS_1;
        emios_ch -= ICU_NUMBER_OF_EACH_EMIOS;
    }
#else
    emiosHw = &EMIOS;
#endif

    emiosHw->CH[emios_ch].CCR.B.FEN = 0;

    IcuChannelRuntimeStruct[Channel].IsRunning = FALSE;

}
#endif

/** @req SWS_Icu_00105 */
/** @req SWS_Icu_00341 */
#if (ICU_GET_TIME_ELAPSED_API == STD_ON)

/* Reads the elapsed Signal Low/High/Period Time for the given channel,
 * depending on the configuration of the channel */
/** @req SWS_Icu_00210 */
Icu_ValueType Icu_GetTimeElapsed( Icu_ChannelType Channel ){

    Icu_ValueType elapsedTime;

    /** @req ICU268 */
    /** @req SWS_Icu_00179 */
    VALIDATE_W_RV(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_GETTIMEELAPSED_ID, ICU_E_UNINIT, 0);

    /** @req SWS_Icu_00178 */
    VALIDATE_W_RV(IS_VALID_CHANNEL(Channel), ICU_GETTIMEELAPSED_ID, ICU_E_PARAM_CHANNEL, 0);

    /** @req SWS_Icu_00178 */
    VALIDATE_W_RV(( IcuConfigPtr->Channels[Channel].measurement_mode == ICU_MODE_SIGNAL_MEASUREMENT), ICU_GETTIMEELAPSED_ID, ICU_E_PARAM_CHANNEL, 0);


    ICU_ENTER_EXCLUSIVE_AREA(EXCLUSIVE_AREA_0); /* Disable interrupts */

    elapsedTime = IcuChannelRuntimeStruct[Channel].ElapsedTime;
    IcuChannelRuntimeStruct[Channel].ElapsedTime = 0U;

    ICU_EXIT_EXCLUSIVE_AREA(EXCLUSIVE_AREA_0); /* Enable interrupts */

    return elapsedTime;
}
#endif

/** @req SWS_Icu_00106 */
/** @req SWS_Icu_00345 */
#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)
/* Reads the coherent active time and period time for the given ICU Channel */
/** @req SWS_Icu_00211 */
void Icu_GetDutyCycleValues( Icu_ChannelType Channel, Icu_DutyCycleType* DutyCycleValues ){

    /** @req ICU268 */
    /** @req SWS_Icu_00179 */
    VALIDATE(Icu_ModuleState == ICU_STATE_INITIALIZED, ICU_GETDUTYCYCLEVALUES_ID, ICU_E_UNINIT);

    /** @req SWS_Icu_00180 */
    VALIDATE(IS_VALID_CHANNEL(Channel), ICU_GETDUTYCYCLEVALUES_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00180 */
    VALIDATE(( IcuConfigPtr->Channels[Channel].measurement_mode == ICU_MODE_SIGNAL_MEASUREMENT), ICU_GETDUTYCYCLEVALUES_ID, ICU_E_PARAM_CHANNEL);

    /** @req SWS_Icu_00181 */
    VALIDATE(DutyCycleValues != NULL, ICU_GETDUTYCYCLEVALUES_ID, ICU_E_PARAM_BUFFER_PTR);

    ICU_ENTER_EXCLUSIVE_AREA(EXCLUSIVE_AREA_0); /* Disable interrupts */

    DutyCycleValues->PeriodTime = IcuChannelRuntimeStruct[Channel].DutyCycle.PeriodTime;
    DutyCycleValues->ActiveTime = IcuChannelRuntimeStruct[Channel].DutyCycle.ActiveTime;

    /** @req SWS_Icu_00344 */
    IcuChannelRuntimeStruct[Channel].DutyCycle.PeriodTime = 0U;
    IcuChannelRuntimeStruct[Channel].DutyCycle.ActiveTime = 0U;

    ICU_EXIT_EXCLUSIVE_AREA(EXCLUSIVE_AREA_0); /* Enable interrupts */
}
#endif

ISR(Icu_Isr) {
    volatile struct EMIOS_tag *emiosHw;

    uint32_t flagmask;
    uint32_t flagmask_0 = (uint32_t) EMIOS_0.GFR.R;
    uint32_t flagmask_1 = (uint32_t) EMIOS_1.GFR.R;
    for (Icu_ChannelType channel_iterator = 0; channel_iterator < ICU_NUMBER_OF_CHANNELS; channel_iterator++) {

        Icu_ChannelType emios_ch = IcuConfigPtr->Channels[channel_iterator].physical_channel;

#if defined(CFG_MPC5645S) || defined(CFG_MPC560XB) || defined(CFG_MPC5606S) || defined(CFG_MPC5746C)

    if(emios_ch <= (ICU_NUMBER_OF_EACH_EMIOS-1)) {
        emiosHw = &EMIOS_0;
        flagmask = flagmask_0;
    } else {
        emiosHw = &EMIOS_1;
        emios_ch -= ICU_NUMBER_OF_EACH_EMIOS;
        flagmask = flagmask_1;
    }
#else
    emiosHw = &EMIOS;
#endif

        if ((emiosHw->CH[emios_ch].CCR.B.FEN == 1) && ((flagmask & (1UL << emios_ch)) != 0)) {
#if (ICU_TIMESTAMP_API == STD_ON)
            if (IcuConfigPtr->Channels[channel_iterator].measurement_mode == ICU_MODE_TIMESTAMP)
            {
                /* Call TimeStamp ISR to save timestamp value into buffer */
                Timestamp_ISR (channel_iterator);

                /** @req SWS_Icu_00319 */
                /** @req SWS_Icu_00320 */
                if ((++IcuChannelRuntimeStruct[channel_iterator].NotificationCounter >= IcuChannelRuntimeStruct[channel_iterator].NotifyInterval) &&
                        IcuChannelRuntimeStruct[channel_iterator].NotificationEnabled)
                {
                    /* Call configured notification function if defined */
                    if (IcuConfigPtr->Channels[channel_iterator].notification != NULL)
                    {
                        IcuConfigPtr->Channels[channel_iterator].notification();  /*lint !e746 OK, prototype not necessary for callback pointers */
                    }
                }
            }
            else
#endif

#if (ICU_EDGE_DETECT_API == STD_ON)
                if (IcuConfigPtr->Channels[channel_iterator].measurement_mode == ICU_MODE_SIGNAL_EDGE_DETECT)
                {
                    IcuChannelRuntimeStruct[channel_iterator].InputState = ICU_ACTIVE;
                    if (IcuChannelRuntimeStruct[channel_iterator].NotificationEnabled &&
                            (IcuConfigPtr->Channels[channel_iterator].notification != NULL))
                    {
                        IcuConfigPtr->Channels[channel_iterator].notification(); /*lint !e746 OK, prototype not necessary for callback pointers */
                    }
                }
                else
                {
                    /* MISRA */ ;
                }
#endif

#if (ICU_EDGE_COUNT_API == STD_ON)
            if (IcuConfigPtr->Channels[channel_iterator].measurement_mode == ICU_MODE_EDGE_COUNTER)
            {
                IcuChannelRuntimeStruct[channel_iterator].InputState = ICU_ACTIVE;

                /* Increase the Edge Counter */
                IcuChannelRuntimeStruct[channel_iterator].EdgeCounter++;
            }
            else
            {
                /* MISRA */ ;
            }
#endif

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
            if (IcuConfigPtr->Channels[channel_iterator].measurement_mode == ICU_MODE_SIGNAL_MEASUREMENT)
            {
                IcuChannelRuntimeStruct[channel_iterator].InputState = ICU_ACTIVE;

                /* Store signal measurement values */
                SignalMeasurementISR(channel_iterator);
            }
            else
            {
                /* MISRA */ ;
            }
#endif

            /* Clear interrupt */
            emiosHw->CH[emios_ch].CSR.B.FLAG = 1;
        }

        else
        {
            /* MISRA */ ;
        }
    }
}

#if (ICU_GET_VERSION_INFO_API)
/* returns the version information of this module */
/** @req SWS_Icu_00212 */
void Icu_GetVersionInfo( Std_VersionInfoType* versioninfo ){

    /* @req SWS_Icu_00356 */
    VALIDATE( ( NULL != versioninfo ), ICU_GETVERSIONINFO_ID, ICU_E_PARAM_VINFO);

    versioninfo->vendorID = ICU_VENDOR_ID;
    versioninfo->moduleID = ICU_MODULE_ID;
    versioninfo->sw_major_version = ICU_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = ICU_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = ICU_SW_PATCH_VERSION;

}
#endif
