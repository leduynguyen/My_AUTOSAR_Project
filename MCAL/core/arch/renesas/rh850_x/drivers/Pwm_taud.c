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
/** @tagSettings DEFAULT_ARCHITECTURE=RH850F1H */

/* ----------------------------[includes]------------------------------------*/

#include "Pwm.h"
#include "Pwm_Internal.h"
#include "Mcu.h"
#if defined(USE_DET)
#include "Det.h"
#endif

#include "os.h"
#include "isr.h"

/* ----------------------------[private define]------------------------------*/

#if defined(CFG_RH850F1L)
#define TAUD_BASE    0xFFE20000UL /* TAUD0 */
#else
#error CPU not defined
#endif

/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/

/*lint --e{754} */
struct TAUD_reg {
    struct {
        uint16 R;
        uint16 pad;
    } CDRm[16];

    uint16 TOL;                                            /* TOL              */
    uint8  dummy99[2];                                     /* Reserved         */
    uint16 RDT;                                            /* RDT              */
    uint8  dummy100[2];                                    /* Reserved         */
    const uint16 RSF;                                      /* RSF              */
    uint8  dummy101[2];                                    /* Reserved         */
    uint16 TRO;                                            /* TRO              */
    uint8  dummy102[2];                                    /* Reserved         */
    uint16 TME;                                            /* TME              */
    uint8  dummy103[2];                                    /* Reserved         */
    uint16 TDL;                                            /* TDL              */
    uint8  dummy104[2];                                    /* Reserved         */
    uint16 TO;                                             /* TO               */
    uint8  dummy105[2];                                    /* Reserved         */
    uint16 TOE;                                            /* TOE              */
    uint8  dummy106[34];                                   /* Reserved         */

    struct {
        uint16 R;
        uint16 pad;
    } CNTm[16];

    struct {
        uint16 R;
        uint16 pad;
    } CMURm[16];

    uint8  dummy11[64];

    struct {
        uint16 R;
        uint16 pad;
    } CSRm[16];

    struct {
        uint16 R;
        uint16 pad;
    } CSCm[16];

    const uint16 TE;                                       /* TE               */
    uint8  dummy171[2];                                    /* Reserved         */
    uint16 TS;                                             /* TS               */
    uint8  dummy172[2];                                    /* Reserved         */
    uint16 TT;                                             /* TT               */
    uint8  dummy173[54];                                   /* Reserved         */

    struct {
        uint16 R;
        uint16 pad;
    } CMORm[16];

    uint16 TPS;                                            /* TPS              */
    uint8  dummy190[2];                                    /* Reserved         */
    uint8  BRS;                                            /* BRS              */
    uint8  dummy191[3];                                    /* Reserved         */
    uint16 TOM;                                            /* TOM              */
    uint8  dummy192[2];                                    /* Reserved         */
    uint16 TOC;                                            /* TOC              */
    uint8  dummy193[2];                                    /* Reserved         */
    uint16 TDE;                                            /* TDE              */
    uint8  dummy194[2];                                    /* Reserved         */
    uint16 TDM;                                            /* TDM              */
    uint8  dummy195[2];                                    /* Reserved         */
    uint16 TRE;                                            /* TRE              */
    uint8  dummy196[2];                                    /* Reserved         */
    uint16 TRC;                                            /* TRC              */
    uint8  dummy197[2];                                    /* Reserved         */
    uint16 RDE;                                            /* RDE              */
    uint8  dummy198[2];                                    /* Reserved         */
    uint16 RDM;                                            /* RDM              */
    uint8  dummy199[2];                                    /* Reserved         */
    uint16 RDS;                                            /* RDS              */
    uint8  dummy200[2];                                    /* Reserved         */
    uint16 RDC;                                            /* RDC              */
    uint8  dummy201[34];                                   /* Reserved         */
    uint8  EMU;                                            /* EMU              */
};

/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/

/*lint -e{923} */
struct TAUD_reg * Pwm_HwReg = ((struct TAUD_reg *) (TAUD_BASE));
const uint32_t Pwm_PrescaleMap[4] = {2U^0U,2U^5U,2U^10U,400U};

/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/


ISR(Pwm_0_Isr);
ISR(Pwm_1_Isr);
ISR(Pwm_2_Isr);
ISR(Pwm_3_Isr);
ISR(Pwm_4_Isr);
ISR(Pwm_5_Isr);
ISR(Pwm_6_Isr);
ISR(Pwm_7_Isr);
ISR(Pwm_8_Isr);
ISR(Pwm_9_Isr);
ISR(Pwm_10_Isr);
ISR(Pwm_11_Isr);
ISR(Pwm_12_Isr);
ISR(Pwm_13_Isr);
ISR(Pwm_14_Isr);
ISR(Pwm_15_Isr);

static void Pwm_Isr(Pwm_Hw_ChannelType hwChannel);

ISR(Pwm_0_Isr) { Pwm_Isr(0u); }
ISR(Pwm_1_Isr) { Pwm_Isr(1u); }
ISR(Pwm_2_Isr) { Pwm_Isr(2u); }
ISR(Pwm_3_Isr) { Pwm_Isr(3u); }
ISR(Pwm_4_Isr) { Pwm_Isr(4u); }
ISR(Pwm_5_Isr) { Pwm_Isr(5u); }
ISR(Pwm_6_Isr) { Pwm_Isr(6u); }
ISR(Pwm_7_Isr) { Pwm_Isr(7u); }
ISR(Pwm_8_Isr) { Pwm_Isr(8u); }
ISR(Pwm_9_Isr) { Pwm_Isr(9u); }
ISR(Pwm_10_Isr) { Pwm_Isr(10u); }
ISR(Pwm_11_Isr) { Pwm_Isr(11u); }
ISR(Pwm_12_Isr) { Pwm_Isr(12u); }
ISR(Pwm_13_Isr) { Pwm_Isr(13u); }
ISR(Pwm_14_Isr) { Pwm_Isr(14u); }
ISR(Pwm_15_Isr) { Pwm_Isr(15u); }

#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)    /*lint -e961 */

static void installChannelInterrupt(uint8 Chnl) {
    switch (Chnl) {
        case 0:
            ISR_INSTALL_ISR2("Gpt", Pwm_0_Isr, (IrqType )(IRQ_INTTAUD0I0), PWM_ISR_PRIORITY, 0);
            break;
        case 1:
            ISR_INSTALL_ISR2("Gpt", Pwm_1_Isr, (IrqType )(IRQ_INTTAUD0I1), PWM_ISR_PRIORITY, 0);
            break;
        case 2:
            ISR_INSTALL_ISR2("Gpt", Pwm_2_Isr, (IrqType )(IRQ_INTTAUD0I2), PWM_ISR_PRIORITY, 0);
            break;
        case 3:
            ISR_INSTALL_ISR2("Gpt", Pwm_3_Isr, (IrqType )(IRQ_INTTAUD0I3), PWM_ISR_PRIORITY, 0);
            break;
        case 4:
            ISR_INSTALL_ISR2("Gpt", Pwm_4_Isr, (IrqType )(IRQ_INTTAUD0I4), PWM_ISR_PRIORITY, 0);
            break;
        case 5:
            ISR_INSTALL_ISR2("Gpt", Pwm_5_Isr, (IrqType )(IRQ_INTTAUD0I5), PWM_ISR_PRIORITY, 0);
            break;
        case 6:
            ISR_INSTALL_ISR2("Gpt", Pwm_6_Isr, (IrqType )(IRQ_INTTAUD0I6), PWM_ISR_PRIORITY, 0);
            break;
        case 7:
            ISR_INSTALL_ISR2("Gpt", Pwm_7_Isr, (IrqType )(IRQ_INTTAUD0I7), PWM_ISR_PRIORITY, 0);
            break;
        case 8:
            ISR_INSTALL_ISR2("Gpt", Pwm_8_Isr, (IrqType )(IRQ_INTTAUD0I8), PWM_ISR_PRIORITY, 0);
            break;
        case 9:
            ISR_INSTALL_ISR2("Gpt", Pwm_9_Isr, (IrqType )(IRQ_INTTAUD0I9), PWM_ISR_PRIORITY, 0);
            break;
        case 10:
            ISR_INSTALL_ISR2("Gpt", Pwm_10_Isr, (IrqType )(IRQ_INTTAUD0I10), PWM_ISR_PRIORITY, 0);
            break;
        case 11:
            ISR_INSTALL_ISR2("Gpt", Pwm_11_Isr, (IrqType )(IRQ_INTTAUD0I11), PWM_ISR_PRIORITY, 0);
            break;
        case 12:
            ISR_INSTALL_ISR2("Gpt", Pwm_12_Isr, (IrqType )(IRQ_INTTAUD0I12), PWM_ISR_PRIORITY, 0);
            break;
        case 13:
            ISR_INSTALL_ISR2("Gpt", Pwm_13_Isr, (IrqType )(IRQ_INTTAUD0I13), PWM_ISR_PRIORITY, 0);
            break;
        case 14:
            ISR_INSTALL_ISR2("Gpt", Pwm_14_Isr, (IrqType )(IRQ_INTTAUD0I14), PWM_ISR_PRIORITY, 0);
            break;
        case 15:
            ISR_INSTALL_ISR2("Gpt", Pwm_15_Isr, (IrqType )(IRQ_INTTAUD0I15), PWM_ISR_PRIORITY, 0);
            break;
        default:
            break;
    }
}
#endif


static void Pwm_Isr( Pwm_Hw_ChannelType ch ) {
    (void)ch;   /*lint !e920 */

}

static void setDuty(uint8 hwCh, Pwm_PeriodType periodTicks, uint16 dutyCycle ) {
    if( dutyCycle == PWM_100_PERCENT ) {
        /* TAUDnCDRm (slave) setting > TAUDnCDRm (master) setting + 1, */
        Pwm_HwReg->CDRm[hwCh + 1U].R = (uint16)(periodTicks + 1UL);
    } else {
        Pwm_HwReg->CDRm[hwCh + 1U].R = (uint16)((periodTicks * dutyCycle) / (PWM_100_PERCENT));
    }
}


static void changePeriodAndDuty(uint8 hwCh, Pwm_PeriodType periodTicks, uint16 dutyCycle)
{
    if( periodTicks == 0u )
    {
        /* If the period is set to zero the setting of the duty-cycle is not
         * relevant. In this case the output shall be zero (zero percent duty-cycle)
         */
        setDuty( hwCh, Pwm_HwReg->CDRm[hwCh].R, 0u );

    } else {
        Pwm_HwReg->CDRm[hwCh].R = periodTicks;    /* Set the period time */
        setDuty( hwCh, periodTicks, dutyCycle );
    }
}



static void changeDuty(uint8 hwCh, uint16 dutyCycle)
{
    uint16 periodTicks = Pwm_HwReg->CDRm[hwCh].R;
    setDuty( hwCh, periodTicks, dutyCycle );
}

/** !req SWS_Pwm_00052  disable all notifications */
Std_ReturnType Pwm_Hw_Init(const Pwm_ConfigType* ConfigPtr) {
    uint8 hwCh;
    uint8 slaveHwCh;
    uint32 clock;
    uint32 freq;
    uint16 periodTicks;

    /* Set the fixed pre-scalers, CK0 - 2^0, CK1 - 2^5, CK2 - 2^ 10, CK3 - (2^2)*100 */
    Pwm_HwReg->TPS = 0x2950u;

    Pwm_HwReg->BRS = 99;

    /* Re-write registers, make sure they are 0 */
    Pwm_HwReg->TOM = 0u;
    Pwm_HwReg->TOC = 0u;
    Pwm_HwReg->TOL = 0u;
    Pwm_HwReg->TDE = 0u;
    Pwm_HwReg->TDM = 0u;
    Pwm_HwReg->TDL = 0u;
    Pwm_HwReg->TRE = 0u;
    Pwm_HwReg->TRC = 0u;
    Pwm_HwReg->TRO = 0u;
    Pwm_HwReg->TME = 0u;
    Pwm_HwReg->TOE = 0u;

    Pwm_HwReg->RDE = 0u;
    Pwm_HwReg->RDS = 0u;
    Pwm_HwReg->RDM = 0u;
    Pwm_HwReg->RDC = 0u;


    clock = Mcu_Arc_GetPeripheralClock(C_ISO_PERI1);
    Pwm_Clock = clock;

    for (uint8 ch = 0; ch < PWM_ARC_LOG_UNIT_CNT; ch++) {
        const Pwm_ChannelConfigurationType* chPtr = &ConfigPtr->Channels[ch];
        hwCh = ChannelToHwChannel(ch);
        slaveHwCh = hwCh+1u;

        /* Setup the master channel */
        Pwm_HwReg->CMORm[hwCh].R = (uint16)((chPtr->prescaler<<14UL) |
                                            (1UL<<11U) |    /* Master = 1 */
                                            1UL);

        /* Setup the slave channel */
        Pwm_HwReg->CMORm[slaveHwCh].R = (uint16)((chPtr->prescaler<<14U) |
                                                (0UL<<11U) |    /* Slave = 0 */ /*lint !e845 Readability */
                                                (4UL<<8U) |     /* Trigger = master */
                                                (4UL<<1U) |     /* One count mode */
                                                1UL);

        /* Slave, Re-write registers */
        Pwm_HwReg->TOM |= (uint16)(1UL<<slaveHwCh);        /* Synchrone operation */
        Pwm_HwReg->TOE |= (uint16)(1UL<<slaveHwCh);        /* Enables the independent timer output function */

        freq = chPtr->frequency;

        periodTicks = (uint16)(((clock/freq) - 1UL) / (uint32)Pwm_PrescaleMap[chPtr->prescaler]);

        changePeriodAndDuty(hwCh,periodTicks,chPtr->duty);

        /* Write "reload" counters
         * ,-----,       ,-----,       ,-----,
         *       |       |     |       |     |
         *       ´-------`     ´-------`
         * |<-     P   ->|<-     P   ->|
         *               |<-D->|
         * P - Period
         * D - Duty
         * */

        Pwm_HwReg->TS |= (uint16)((1UL<<hwCh) | (1UL<<slaveHwCh));

        installChannelInterrupt(hwCh);
        installChannelInterrupt(slaveHwCh);
    }
    return E_OK;
}

#if (PWM_DE_INIT_API==STD_ON)
/** @req SWS_Pwm_00010 Does not deinitialize the hardware but the module is effectively deinitialized
 * (according to the idle states of the channels). */
/** !req SWS_Pwm_00012 Pwm_DeInit shall disable PWM interrupts and PWM signal edge notifications */
void Pwm_Hw_Deinit(const Pwm_ConfigType* ConfigPtr) {
    /* Not Supported */
    if(ConfigPtr==NULL){
        return;
    }

    /* Stop all channels */
    Pwm_HwReg->TT = 0xffffu;

    Pwm_ChannelType channel_iterator;
    for (channel_iterator = 0; channel_iterator < PWM_NUMBER_OF_CHANNELS; channel_iterator++) {
        const Pwm_ChannelConfigurationType* channelConfig = &ConfigPtr->Channels[channel_iterator];

        Pwm_Hw_SetOutputToIdle(channelConfig->channel, channelConfig->idleState);
    }
}
#endif

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
void Pwm_Hw_SetPeriodAndDuty(Pwm_ChannelType hwCh, Pwm_PeriodType Period, uint16 DutyCycle, Pwm_OutputStateType Polarity) {
    (void)Polarity;  /*lint !e715 */
    changePeriodAndDuty((uint8)hwCh, Period, DutyCycle);
}
#endif

#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
void Pwm_Hw_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle, Pwm_OutputStateType Polarity) {
    (void)Polarity;  /*lint !e715 */
    changeDuty(ChannelNumber, DutyCycle);

}
#endif

#if ( PWM_SET_OUTPUT_TO_IDLE_API == STD_ON )
void Pwm_Hw_SetOutputToIdle(Pwm_ChannelType ChannelNumber, Pwm_OutputStateType IdleState) {

    if( IdleState == PWM_HIGH){
        /* idle state high == neg polarity (for 0% duty) */
        Pwm_Hw_SetDutyCycle(ChannelNumber, 0, PWM_LOW);
    }
    else{
        Pwm_Hw_SetDutyCycle(ChannelNumber, 0, PWM_HIGH);
    }
}
#endif

#if (PWM_GET_OUTPUT_STATE_API == STD_ON)
Pwm_OutputStateType Pwm_Hw_GetOutputState(Pwm_ChannelType ChannelNumber) {

    Pwm_OutputStateType state;

    /* +1 since it's the slave channel that outputs the PWM */
    if( (((uint32)Pwm_HwReg->TO >> (ChannelNumber+1UL)) & 1UL) == 1UL ) {
        state = PWM_HIGH;
    } else {
        state = PWM_LOW;
    }

    return state;
}
#endif

#if (PWM_NOTIFICATION_SUPPORTED==STD_ON)
void Pwm_Hw_DisableNotification(Pwm_ChannelType ChannelNumber) {
    /* Not Supported */
    (void)ChannelNumber;	/*lint !e715 */
}

void Pwm_Hw_EnableNotification(Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification,
        Pwm_OutputStateType Polarity) {
    /* Not Supported */
    (void)ChannelNumber;	/*lint !e715 */
    (void)Notification;		/*lint !e715 */
    (void)Polarity;			/*lint !e715 */
}
#endif


#if (PWM_ARC_PERIOD_API==STD_ON)
uint32 Pwm_Arc_Tick2us( Pwm_ChannelType ChannelNumber,Pwm_PeriodType ticks)
{
    uint8 ch = HwChannelToChannel((Pwm_Hw_ChannelType)ChannelNumber);
    return ( (((uint32)ticks) * 1000UL) / (Pwm_Clock/(Pwm_PrescaleMap[PwmConfigPtr->Channels[ch].prescaler]*1000UL)) );
}

Pwm_PeriodType Pwm_Arc_us2Tick( Pwm_ChannelType ChannelNumber, uint32 us)
{
    uint8 ch = HwChannelToChannel((Pwm_Hw_ChannelType)ChannelNumber);
    return (Pwm_PeriodType)(((us) * (Pwm_Clock/1000000UL)) / (Pwm_PrescaleMap[PwmConfigPtr->Channels[ch].prescaler]));
}
#endif






