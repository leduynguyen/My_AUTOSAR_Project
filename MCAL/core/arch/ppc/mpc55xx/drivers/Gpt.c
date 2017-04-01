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


/** @tagSettings DEFAULT_ARCHITECTURE=PPC|MPC5607B|MPC5645S|MPC5746C|MPC5747C|MPC5748G */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

/* ----------------------------[includes]------------------------------------*/


/*lint -e923 Cast in Freescale header file */

/* @req SWS_Gpt_00293 */
/* @req SWS_Gpt_00375 */
/* @req SWS_Gpt_00331 Notification support */

#include "Std_Types.h"
#include "Gpt.h"
#include "Cpu.h"
#include "arc_assert.h"
#include "mpc55xx.h"
#include "Mcu.h"
#include "debug.h"


#if defined(USE_DET) && (GPT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
#include "Os.h"
#include "isr.h"

/* ----------------------------[private define]------------------------------*/


#if defined(CFG_MPC5604P)
#define GPT_CHANNELS_CNT       3u
#elif defined(CFG_MPC5606S) || defined(CFG_MPC563XM) || defined(CFG_MPC5744P) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC5644A)
#define GPT_CHANNELS_CNT       4u
#elif defined(CFG_MPC5604B)
#define GPT_CHANNELS_CNT       5u
#elif defined(CFG_MPC5606B)  || defined(CFG_MPC5645S) || defined(CFG_SPC560B54)
#define GPT_CHANNELS_CNT       7u
#elif defined (CFG_MPC5746C) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C)
#define GPT_CHANNELS_CNT       16U
#elif defined(CFG_MPC5516)
#define GPT_CHANNELS_CNT       9u
#else
#define GPT_CHANNELS_CNT       8u
#endif

#define GPT_CHANNEL_PIT_LAST    (GPT_CHANNELS_CNT-1u)


/* ----------------------------[private macro]-------------------------------*/

#if ( GPT_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
          return; \
        }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
          return (_rv); \
        }
#define VALID_CHANNEL(_ch)		( (Gpt_Global.configured & (1uL<<(_ch))) > 0)
#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_W_RV(_exp,_api,_err,_rv )
#endif


#if defined(CFG_MPC560X) || defined(CFG_MPC563XM) || defined(CFG_MPC5744P) || defined(CFG_MPC5748G) || defined(CFG_MPC5645S) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC5777M) || defined(CFG_MPC5668) || defined (CFG_MPC5746C)
#define ENABLE_INTERRUPTS(_ch)              (PIT.CH[_ch].TCTRL.B.TIE = 1)
#define DISABLE_INTERRUPT(_ch)              (PIT.CH[_ch].TCTRL.B.TIE = 0)
#define ENABLE_CHANNEL(_ch)                 (PIT.CH[_ch].TCTRL.B.TEN = 1)
#define DISABLE_CHANNEL(_ch)                (PIT.CH[_ch].TCTRL.B.TEN = 0)

#define CLEAR_CHANNEL_INTERRUPT(_ch)        (PIT.CH[_ch].TFLG.B.TIF = 1)

#define GET_REMAINING_TIME(_ch)             PIT.CH[_ch].CVAL.R

#define SET_PERIOD(_ch,_period)             (PIT.CH[_ch].LDVAL.R = (_period));

#elif defined(CFG_MPC5644A)
#define ENABLE_INTERRUPTS(_ch)              (PIT.TIMER[_ch].TCTRL.B.TIE = 1)
#define DISABLE_INTERRUPT(_ch)              (PIT.TIMER[_ch].TCTRL.B.TIE = 0)
#define ENABLE_CHANNEL(_ch)                 (PIT.TIMER[_ch].TCTRL.B.TEN = 1)
#define DISABLE_CHANNEL(_ch)                (PIT.TIMER[_ch].TCTRL.B.TEN = 0)

#define CLEAR_CHANNEL_INTERRUPT(_ch)        (PIT.TIMER[_ch].TFLG.B.TIF = 1)

#define GET_REMAINING_TIME(_ch)             PIT.TIMER[_ch].CVAL.R

#define SET_PERIOD(_ch,_period)             (PIT.TIMER[_ch].LDVAL.R = _period);

#else
#define ENABLE_INTERRUPTS(_ch)              PIT.INTEN.R |= ( 1 << (_ch) )
#define DISABLE_INTERRUPT(_ch)              PIT.INTEN.R &= ~( 1 << (_ch) )

#define ENABLE_CHANNEL(_ch)                 PIT.EN.R |= (1 << (_ch))
#define DISABLE_CHANNEL(_ch)                PIT.EN.R &= ~( 1 << (_ch) )
#define CLEAR_CHANNEL_INTERRUPT(_ch)        PIT.FLG.R = ( 1 << (_ch) )

#define GET_REMAINING_TIME(_ch)             ((uint32 *)&PIT.TVAL0)[_ch]

#define SET_PERIOD(_ch,_period)     \
             ((uint32 *)&PIT.TLVAL0)[_ch] = _period;   \
             ((uint32 *)&PIT.TVAL0)[_ch] = _period;    \
             if (_ch != GPT_CHANNEL_RTI) {                  \
                 PIT.INTSEL.R |= (1 << _ch);                \
             }

#define PIT_INT0 PIT_PITFLG_RTIF
#define PIT_INT1 PIT_PITFLG_PIT1
#define PIT_INT2 PIT_PITFLG_PIT2
#define PIT_INT3 PIT_PITFLG_PIT3
#define PIT_INT4 PIT_PITFLG_PIT4
#define PIT_INT5 PIT_PITFLG_PIT5
#define PIT_INT6 PIT_PITFLG_PIT6
#define PIT_INT7 PIT_PITFLG_PIT7


#endif
#if defined(CFG_MPC560X) || defined(CFG_MPC563XM) || defined(CFG_MPC5744P) || defined(CFG_MPC5748G) || defined(CFG_MPC5645S) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC5777M) || defined(CFG_MPC5668) || defined (CFG_MPC5746C) || defined(CFG_MPC5747C)
static inline void disableModule( void ) {
    for(uint32 i = 0; i <= GPT_CHANNEL_PIT_LAST; i++)
    {
        PIT.CH[i].TCTRL.B.TIE = 0;
    }
    PIT.MCR.B.MDIS = 0;
    PIT.MCR.B.FRZ = 1;
}
#elif defined(CFG_MPC5644A)
static inline void disableModule( void ) {
    for(uint32 i = 0; i <= GPT_CHANNEL_PIT_LAST; i++)
    {
        PIT.TIMER[i].TCTRL.B.TIE = 0;
    }
    PIT.PITMCR.B.MDIS = 0;
    PIT.PITMCR.B.FRZ = 1;
}
#else
static inline void disableModule( void ) {
    /* @req 3.1.5|GPT258 */
    PIT.CTRL.B.MDIS = 0;
}
#endif



/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

typedef enum {
    GPT_STATE_STOPPED = 0, GPT_STATE_STARTED, GPT_STATE_EXPIRED, GPT_STATE_INITIALIZED
} Gpt_StateType;

/**
 * Type that holds all global data for Gpt
 */
typedef struct {
    // Set if Gpt_Init() have been called
    boolean initRun;

    // Our config
    const Gpt_ConfigType *config;

#if ( GPT_WAKEUP_FUNCTIONALITY_API == STD_ON )
    uint8 wakeupEnabled;
#endif

    // One bit for each channel that is configured.
    // Used to determine if validity of a channel
    // 1 - configured
    // 0 - NOT configured
    uint32 configured;

    // Maps the a channel id to a configured channel id
    uint8 channelMap[GPT_CHANNEL_CNT];

} Gpt_GlobalType;

/**
 * Type that holds data that are specific for a channel
 */
typedef struct {
    Gpt_StateType state;
    boolean expiredWhenStopped;
} Gpt_UnitType;


/* GPT_CHANNEL_CNT represents the number of physical channels */
Gpt_UnitType Gpt_Unit[GPT_CHANNEL_CNT];

// Global config
Gpt_GlobalType Gpt_Global;

//-------------------------------------------------------------------


static void Gpt_Isr( uint32_t channel) {
    const Gpt_ConfigType *config;
    uint32 confCh;

    /* Find the config entry for the PIT channel. */
    confCh = Gpt_Global.channelMap[ channel ];
    ASSERT(confCh != GPT_CHANNEL_ILL);
    config = &Gpt_Global.config[ confCh ];

    if (config->GptChannelMode == GPT_CH_MODE_ONESHOT)
    {
        /* Disable the channel. */
        DISABLE_CHANNEL(channel);
        Gpt_Unit[channel].state = GPT_STATE_EXPIRED;
    }
    config->GptNotification();
    /* Clear interrupt. */
    CLEAR_CHANNEL_INTERRUPT(channel);
}

/*
 * Create instances of the ISR for each PIT channel.
 */
ISR(Gpt_Isr_Channel0);
ISR(Gpt_Isr_Channel1);
ISR(Gpt_Isr_Channel2);
ISR(Gpt_Isr_Channel0) {Gpt_Isr(0);}
ISR(Gpt_Isr_Channel1) {Gpt_Isr(1);}
ISR(Gpt_Isr_Channel2) {Gpt_Isr(2);}
#if (GPT_CHANNELS_CNT > 3)
ISR(Gpt_Isr_Channel3);
ISR(Gpt_Isr_Channel3) {Gpt_Isr(3);}
#if (GPT_CHANNELS_CNT > 4)
ISR(Gpt_Isr_Channel4);
ISR(Gpt_Isr_Channel5);
ISR(Gpt_Isr_Channel4) {Gpt_Isr(4);}
ISR(Gpt_Isr_Channel5) {Gpt_Isr(5);}
#if (GPT_CHANNELS_CNT > 6)
ISR(Gpt_Isr_Channel6);
ISR(Gpt_Isr_Channel7);
ISR(Gpt_Isr_Channel6) {Gpt_Isr(6);}
ISR(Gpt_Isr_Channel7) {Gpt_Isr(7);}
#endif
#endif
#endif


#if defined(CFG_MPC5516)
ISR(Gpt_Isr_Channel8);
ISR(Gpt_Isr_Channel8) {Gpt_Isr(8);}
#endif

#if defined (CFG_MPC5746C) || defined(CFG_MPC5748G) || defined(CFG_MPC5747C)
ISR(Gpt_Isr_Channel8);
ISR(Gpt_Isr_Channel8) {Gpt_Isr(8);}
ISR(Gpt_Isr_Channel9);
ISR(Gpt_Isr_Channel9) {Gpt_Isr(9);}
ISR(Gpt_Isr_Channel10);
ISR(Gpt_Isr_Channel10) {Gpt_Isr(10);}
ISR(Gpt_Isr_Channel11);
ISR(Gpt_Isr_Channel11) {Gpt_Isr(11);}
ISR(Gpt_Isr_Channel12);
ISR(Gpt_Isr_Channel12) {Gpt_Isr(12);}
ISR(Gpt_Isr_Channel13);
ISR(Gpt_Isr_Channel13) {Gpt_Isr(13);}
ISR(Gpt_Isr_Channel14);
ISR(Gpt_Isr_Channel14) {Gpt_Isr(14);}
ISR(Gpt_Isr_Channel15);
ISR(Gpt_Isr_Channel15) {Gpt_Isr(15);}
#endif
//-------------------------------------------------------------------

void Gpt_Init(const Gpt_ConfigType *ConfigPtr) {
    /** @req SWS_Gpt_00006 */
    /** @req SWS_Gpt_000107 The module is disabled */
    /** @req SWS_Gpt_00068 Global registers must be touched */

    uint8 i;
    const Gpt_ConfigType *cfg;
    /* @req SWS_Gpt_00307 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE( (Gpt_Global.initRun == STD_OFF), GPT_INIT_SERVICE_ID, GPT_E_ALREADY_INITIALIZED );
    /* @req SWS_Gpt_00294 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE( (ConfigPtr != NULL ), GPT_INIT_SERVICE_ID, GPT_E_PARAM_POINTER );
    Gpt_ChannelType ch;

    for (i = 0; i < GPT_CHANNEL_CNT; i++) {
        Gpt_Global.channelMap[i] = GPT_CHANNEL_ILL;
        Gpt_Unit[i].state = GPT_STATE_INITIALIZED;
        Gpt_Unit[i].expiredWhenStopped = FALSE;
    }

    i = 0;
    cfg = ConfigPtr;
    while (cfg->GptChannelId != GPT_CHANNEL_ILL) {
        ch = cfg->GptChannelId;

        // Assign the configuration channel used later..
        Gpt_Global.channelMap[cfg->GptChannelId] = i;
        Gpt_Global.configured |= (1uL << (uint8)ch);

        if (ch <= GPT_CHANNEL_PIT_LAST)
        {
            if (cfg->GptNotification != NULL)
            {
                switch( ch )
                {
                    /*lint -save -e641 Ok, to cast*/
                    case 0: ISR_INSTALL_ISR2( "Gpt_0", Gpt_Isr_Channel0, PIT_INT0, 2, 0 ); break;
                    case 1: ISR_INSTALL_ISR2( "Gpt_1", Gpt_Isr_Channel1, PIT_INT1, 2, 0 ); break;
                    case 2: ISR_INSTALL_ISR2( "Gpt_2", Gpt_Isr_Channel2, PIT_INT2, 2, 0 ); break;
#if (GPT_CHANNELS_CNT > 3)
                    case 3: ISR_INSTALL_ISR2( "Gpt_3", Gpt_Isr_Channel3, PIT_INT3, 2, 0 ); break;
#if (GPT_CHANNELS_CNT > 4)
                    case 4: ISR_INSTALL_ISR2( "Gpt_4", Gpt_Isr_Channel4, PIT_INT4, 2, 0 ); break;
                    case 5: ISR_INSTALL_ISR2( "Gpt_5", Gpt_Isr_Channel5, PIT_INT5, 2, 0 ); break;
#if (GPT_CHANNELS_CNT > 6)
                    case 6: ISR_INSTALL_ISR2( "Gpt_6", Gpt_Isr_Channel6, PIT_INT6, 2, 0 ); break;
                    case 7: ISR_INSTALL_ISR2( "Gpt_7", Gpt_Isr_Channel7, PIT_INT7, 2, 0 ); break;
#if defined (CFG_MPC5746C) || defined(CFG_MPC5748G)|| defined(CFG_MPC5747C)
                    case 8: ISR_INSTALL_ISR2( "Gpt_8", Gpt_Isr_Channel8, PIT_INT8, 2, 0 ); break;
                    case 9: ISR_INSTALL_ISR2( "Gpt_9", Gpt_Isr_Channel9, PIT_INT9, 2, 0 ); break;
                    case 10: ISR_INSTALL_ISR2( "Gpt_10", Gpt_Isr_Channel10, PIT_INT10, 2, 0 ); break;
                    case 11: ISR_INSTALL_ISR2( "Gpt_11", Gpt_Isr_Channel11, PIT_INT11, 2, 0 ); break;
                    case 12: ISR_INSTALL_ISR2( "Gpt_12", Gpt_Isr_Channel12, PIT_INT12, 2, 0 ); break;
                    case 13: ISR_INSTALL_ISR2( "Gpt_13", Gpt_Isr_Channel13, PIT_INT13, 2, 0 ); break;
                    case 14: ISR_INSTALL_ISR2( "Gpt_14", Gpt_Isr_Channel14, PIT_INT14, 2, 0 ); break;
                    case 15: ISR_INSTALL_ISR2( "Gpt_15", Gpt_Isr_Channel15, PIT_INT15, 2, 0 ); break;

#elif defined (CFG_MPC5516)
                    case 8: ISR_INSTALL_ISR2( "Gpt_8", Gpt_Isr_Channel8, PIT_PITFLG_PIT8, 2, 0 );break;
#else
#endif
#endif
#endif
#endif
                    /*lint -restore */
                    default:
                    {
                        // Unknown PIT channel.
                        ASSERT( 0 );
                        break;
                    }
                }
            }
        }
        cfg++;
        i++;
    }

    Gpt_Global.config = ConfigPtr;

    Gpt_Global.initRun = STD_ON;
        
    /* @req SWS_Gpt_00258 */
    disableModule();
}

//-------------------------------------------------------------------


#if GPT_DEINIT_API == STD_ON
void Gpt_DeInit(void)
{
    /** !req SWS_Gpt_00008 Shouldn't MDIS be set to 1 */
    /** @req SWS_Gpt_00105 */
    /** @req SWS_Gpt_00162 */
    /** @req SWS_Gpt_00308 Post build not supported */

    Gpt_ChannelType channel;

    /* @req SWS_Gpt_00220*/
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE( (Gpt_Global.initRun == STD_ON), GPT_DEINIT_SERVICE_ID, GPT_E_UNINIT );
    // Validate that all channels have been stopped
    for (channel=0; channel<GPT_CHANNEL_CNT; channel++) {
        /* @req SWS_Gpt_00234*/
        /*lint -e{904} ARGUMENT_CHECK */
        VALIDATE( (Gpt_Unit[channel].state != GPT_STATE_STARTED), GPT_DEINIT_SERVICE_ID, GPT_E_BUSY );
    }

    /* @req SWS_Gpt_00363 */
    Gpt_Global.initRun = STD_OFF;
    Gpt_Global.configured = 0;
}
#endif

//-------------------------------------------------------------------
// Value is the period is in "ticks" !!
void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value) {

    uint8 confCh;

    /* @req SWS_Gpt_00212 */
    /* @req SWS_Gpt_00218 */
    /* @req SWS_Gpt_00224 */
    /* @req SWS_Gpt_00084 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE( (Gpt_Global.initRun == STD_ON), GPT_STARTTIMER_SERVICE_ID, GPT_E_UNINIT );
    VALIDATE( VALID_CHANNEL(Channel), GPT_STARTTIMER_SERVICE_ID, GPT_E_PARAM_CHANNEL );
    VALIDATE( (Value != 0UL), GPT_STARTTIMER_SERVICE_ID, GPT_E_PARAM_VALUE);
    VALIDATE( (Gpt_Unit[Channel].state != GPT_STATE_STARTED), GPT_STARTTIMER_SERVICE_ID, GPT_E_BUSY );
    /*lint -restore*/
    // GPT_E_PARAM_VALUE, all have 32-bit so no need to check

    DEBUG(DEBUG_HIGH, "Gpt_StartTimer ch=%d, period=%d [ticks]\n", Channel, Value);

    confCh = Gpt_Global.channelMap[Channel];
    if (Channel <= GPT_CHANNEL_PIT_LAST) {
        SET_PERIOD(Channel,Value);
        // Make sure that no interrupt is pending.
        CLEAR_CHANNEL_INTERRUPT(Channel);
        // Enable timer
        ENABLE_CHANNEL(Channel);
    }

    if (Gpt_Global.config[confCh].GptNotification != NULL) {
        /* @req SWS_Gpt_00275 */
        Gpt_EnableNotification(Channel);
    }
    /*lint -save -e661 OTHER Channel validation is done, so valid pointer is accessed */
    Gpt_Unit[Channel].state = GPT_STATE_STARTED;
    Gpt_Unit[Channel].expiredWhenStopped = FALSE;
    /*lint -restore*/
}

void Gpt_StopTimer(Gpt_ChannelType Channel) {

    /* @req SWS_Gpt_00225 */
    /* @req SWS_Gpt_00213 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE( (Gpt_Global.initRun == STD_ON), GPT_STOPTIMER_SERVICE_ID, GPT_E_UNINIT );
    VALIDATE( VALID_CHANNEL(Channel), GPT_STOPTIMER_SERVICE_ID, GPT_E_PARAM_CHANNEL );
    /*lint -restore*/

    /* @req SWS_Gpt_00013 */
    if (Channel <= GPT_CHANNEL_PIT_LAST)
    {
        // Disable timer
        DISABLE_CHANNEL(Channel);
    }


    Gpt_DisableNotification(Channel);
    /*lint -save -e661 OTHER Channel validation is done, so valid pointer is accessed */
    if( GPT_STATE_EXPIRED == Gpt_Unit[Channel].state ) {
        Gpt_Unit[Channel].expiredWhenStopped = TRUE;
    }
    Gpt_Unit[Channel].state = GPT_STATE_STOPPED;
    /*lint -restore*/
}

#if ( GPT_TIME_REMAINING_API == STD_ON )

Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType channel)
{
    /* @req SWS_Gpt_00223 */
    /* @req SWS_Gpt_00211 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_W_RV( (Gpt_Global.initRun == STD_ON), GPT_GETTIMEREMAINING_SERVICE_ID, GPT_E_UNINIT, (Gpt_ValueType)0u );
    VALIDATE_W_RV( VALID_CHANNEL(channel),GPT_GETTIMEREMAINING_SERVICE_ID, GPT_E_PARAM_CHANNEL, (Gpt_ValueType)0u );
    /*lint -restore*/

    Gpt_ValueType remaining = 0;

    /* @req SWS_Gpt_00301 */
    /* @req SWS_Gpt_00305 */
    if( (Gpt_Unit[channel].state == GPT_STATE_INITIALIZED) ||
        (GPT_STATE_EXPIRED == Gpt_Unit[channel].state) ||
        ((GPT_STATE_STOPPED == Gpt_Unit[channel].state) && (TRUE == Gpt_Unit[channel].expiredWhenStopped)) ) {
        remaining = 0;
    }

    else if (channel <= GPT_CHANNEL_PIT_LAST) {
        // Time remaining is the time until it hits 0, so just return the current timer value
        remaining = (Gpt_ValueType)(GET_REMAINING_TIME(channel));
    } else {
        /*To satisfy compiler*/
    }

    return remaining;
}
#endif

#if ( GPT_TIME_ELAPSED_API == STD_ON )
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType channel)
{
    Gpt_ValueType timer = 0;

    /* @req SWS_Gpt_00222 */
    /* @req SWS_Gpt_00210 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE_W_RV( (Gpt_Global.initRun == STD_ON), GPT_GETTIMEELAPSED_SERVICE_ID, GPT_E_UNINIT ,0 );
    VALIDATE_W_RV( VALID_CHANNEL(channel),GPT_GETTIMEELAPSED_SERVICE_ID, GPT_E_PARAM_CHANNEL, 0 );
    /*lint -restore*/

    /* @req SWS_Gpt_00295 */
    /*lint -save -e904 ARGUMENT_CHECK */
    if(Gpt_Unit[channel].state == GPT_STATE_INITIALIZED) {
        return timer;
    }
    /* @req SWS_Gpt_00299 */
    if( (Gpt_Unit[channel].state == GPT_STATE_EXPIRED) ||
        ((GPT_STATE_STOPPED == Gpt_Unit[channel].state) && (TRUE == Gpt_Unit[channel].expiredWhenStopped)) ) {
#if defined(CFG_MPC560X) || defined(CFG_MPC563XM) || defined(CFG_MPC5746C) || defined(CFG_MPC5744P) || defined(CFG_MPC5748G) || defined(CFG_MPC5645S) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC5777M) || defined(CFG_MPC5668) || defined(CFG_MPC5747C)
        return (Gpt_ValueType)(PIT.CH[channel].LDVAL.R);
#elif defined(CFG_MPC5644A)
        return (Gpt_ValueType)(PIT.TIMER[channel].LDVAL.R);
#else
        uint32 *tlval = (uint32 *)&PIT.TLVAL0;
        return tlval[channel];
#endif
    }
    /*lint -restore*/
    // NOTE!
// These little creatures count down

    if (channel <= GPT_CHANNEL_PIT_LAST) {
#if defined(CFG_MPC560X) || defined(CFG_MPC563XM) || defined(CFG_MPC5746C) || defined(CFG_MPC5744P) || defined(CFG_MPC5748G) || defined(CFG_MPC5645S) || defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) || defined(CFG_MPC5777M)|| defined(CFG_MPC5668) || defined(CFG_MPC5747C)
        uint32 tval = PIT.CH[channel].CVAL.R;
        uint32 tlval = PIT.CH[channel].LDVAL.R;
        timer = tlval - tval;
#elif defined(CFG_MPC5644A)
        uint32 tval = PIT.TIMER[channel].CVAL.R;
        uint32 tlval = PIT.TIMER[channel].LDVAL.R;
        timer = tlval - tval;
#else
        uint32 *tval = (uint32 *)&PIT.TVAL0;
        uint32 *tlval = (uint32 *)&PIT.TLVAL0;
        timer = tlval[channel] - tval[channel];
#endif
    }

    return (timer);
}
#endif

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
void Gpt_EnableNotification(Gpt_ChannelType Channel)
{

    /* @req SWS_Gpt_00226 */
    /* @req SWS_Gpt_00214 */
    /* !req SWS_Gpt_00377 */
    /*lint -save -e904 ARGUMENT_CHECK */
    VALIDATE( (Gpt_Global.initRun == STD_ON), 0x7, GPT_E_UNINIT );
    VALIDATE( VALID_CHANNEL(Channel),0x7, GPT_E_PARAM_CHANNEL );
    /*lint -restore*/
    /* @req SWS_Gpt_00014 Note: Not saving attribiute */
    if (Channel <= GPT_CHANNEL_PIT_LAST) {
        ENABLE_INTERRUPTS(Channel);
    }
}

void Gpt_DisableNotification(Gpt_ChannelType Channel)
{
    /* @req SWS_Gpt_00227 */
    /* @req SWS_Gpt_00217 */
    /* !req SWS_Gpt_00379 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE( (Gpt_Global.initRun == STD_ON), 0x8, GPT_E_UNINIT );
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE( VALID_CHANNEL(Channel),0x8, GPT_E_PARAM_CHANNEL );

    /* @req SWS_Gpt_00015 Note: Not saving attribiute */
    if (Channel <= GPT_CHANNEL_PIT_LAST) {
        DISABLE_INTERRUPT(Channel);
    }

}

#endif /* ( GPT_TIME_REMAINING_API == STD_ON ) */

#if ( GPT_WAKEUP_FUNCTIONALITY_API == STD_ON ) && defined(GPT_NOT_SUPPORTED)

void Gpt_SetMode( Gpt_ModeType Mode ) {

    /* !req SWS_Gpt_00228 */
    /* !req SWS_Gpt_00231 */
    VALIDATE( (Gpt_Global.initRun == STD_ON), GPT_SETMODE_SERVICE_ID, GPT_E_UNINIT );
    VALIDATE( ( Mode <= GPT_MODE_SLEEP ), GPT_SETMODE_SERVICE_ID, GPT_E_PARAM_MODE );

    /* NOT SUPPORTED  */

}
void Gpt_DisableWakeup(Gpt_ChannelType Channel)
{
    /* !req SWS_Gpt_00215 */
    /* !req SWS_Gpt_00229 */
    VALIDATE( (Gpt_Global.initRun == STD_ON), GPT_DISABLEWAKEUP_SERVICE_ID, GPT_E_UNINIT );
    VALIDATE( VALID_CHANNEL(Channel), GPT_DISABLEWAKEUP_SERVICE_ID, GPT_E_PARAM_CHANNEL );

    // Only RTI have system wakeup
    VALIDATE( Channel == GPT_CHANNEL_RTI ,GPT_ENABLEWAKEUP_SERVICE_ID, GPT_E_PARAM_CHANNEL );

    Gpt_Global.wakeupEnabled = STD_OFF;

}

void Gpt_EnableWakeup(Gpt_ChannelType Channel)
{
    /* !req SWS_Gpt_00230 */
    /* !req SWS_Gpt_00216 */
    VALIDATE( (Gpt_Global.initRun == STD_ON), GPT_ENABLEWAKEUP_SERVICE_ID, GPT_E_UNINIT );
    VALIDATE( VALID_CHANNEL(Channel),GPT_ENABLEWAKEUP_SERVICE_ID, GPT_E_PARAM_CHANNEL );

    // Only RTI have system wakeup
    VALIDATE( Channel == GPT_CHANNEL_RTI ,GPT_ENABLEWAKEUP_SERVICE_ID, GPT_E_PARAM_CHANNEL );

    Gpt_Global.wakeupEnabled = STD_ON;

}

void Gpt_CheckWakeup(EcuM_WakeupSourceType wakeupSource)
{
    /* !req SWS_Gpt_00325 */
    VALIDATE( (Gpt_Global.initRun == STD_ON), GPT_ENABLEWAKEUP_SERVICE_ID, GPT_E_UNINIT );

    /* NOT SUPPORTED  */

}

#endif

#if (GPT_VERSION_INFO_API == STD_ON)
void Gpt_GetVersionInfo( Std_VersionInfoType* versioninfo) {

    /* @req SWS_Gpt_00338 */
    /*lint -e{904} ARGUMENT_CHECK */
    VALIDATE( ( NULL != versioninfo ), GPT_GETVERSIONINFO_SERVICE_ID, GPT_E_PARAM_POINTER);

    versioninfo->vendorID = GPT_VENDOR_ID;
    versioninfo->moduleID = GPT_MODULE_ID;
    versioninfo->sw_major_version = GPT_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = GPT_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = GPT_SW_PATCH_VERSION;
}
#endif

#if defined(CFG_MPC5668) || defined(CFG_MPC5744P) || defined(CFG_MPC5748G) || defined(CFG_MPC5746C) || defined(CFG_MPC5645S) || defined(CFG_MPC5777M) || defined(CFG_MPC5747C)
#define GPT_PER_CLOCK PERIPHERAL_CLOCK_PIT_0
#elif defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) ||defined (CFG_MPC5604P)
#define GPT_PER_CLOCK PERIPHERAL_CLOCK_PIT
#endif

#if defined(CFG_MPC5668) || defined(CFG_MPC5744P) || defined(CFG_MPC5748G) || defined(CFG_MPC5746C) || defined(CFG_MPC5645S) || defined(CFG_MPC5777M) ||defined(CFG_MPC5643L) || defined(CFG_SPC56XL70) ||defined (CFG_MPC5604P) || defined(CFG_MPC5747C)
/**
 * @brief Gets frequency associated with Channel
 *
 * @param[in] Channel
 *    Gpt Channel number.
 *
 * @return
 *    Frequency in herz.
 */
uint32 Gpt_Arc_GetClock(Gpt_ChannelType Channel)
{
    /* all channels use the same clock source */
    (void) Channel;

    return Mcu_Arc_GetPeripheralClock(GPT_PER_CLOCK);
}
#endif
