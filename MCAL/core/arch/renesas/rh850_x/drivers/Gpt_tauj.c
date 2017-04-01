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

/** @tagSettings DEFAULT_ARCHITECTURE=RH850F1H */
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
#include "Os.h" /* Required by ISR() */

/* ----------------------------[private define]------------------------------*/

#if defined(CFG_RH850F1H)
#define TAUJ_BASE	0xFFE50000uL
#elif defined(CFG_RH850F1L)
#define TAUJ_BASE	0xFFE50000uL
#else
#error No device selected.
#endif

#define TAUJ			(*(struct TAUJ_reg *)((void *)TAUJ_BASE))

#define GPT_ISR_PRIORITY            4u

/* ----------------------------[private macro]-------------------------------*/
/* ----------------------------[private typedef]-----------------------------*/

/*lint --e{754} We don't reference all members of the structure */
struct TAUJ_reg {
    vuint32_t TAUJnCDRm[4]; /* <TAUJn_base> + m × 4        TAUJn channel data register m */
    vuint32_t TAUJnCNTm[4]; /* <TAUJn_base> + 10H + m × 4H TAUJn channel counter register m */
    struct a {
        vuint8_t R;
        uint8_t _pad[3];
    } TAUJnCMURm[4]; /* <TAUJn_base> + 20H + m × 4H TAUJn channel mode user register m */
    struct {
        vuint8_t R;
        uint8_t _pad[3];
    } TAUJnCSRm[4]; /* <TAUJn_base> + 30H + m × 4H TAUJn channel status register m */
    struct {
        vuint8_t R;
        uint8_t _pad[3];
    } TAUJnCSCm[4]; /* <TAUJn_base> + 40H + m × 4H TAUJn channel status clear trigger register m */

    vuint8_t TAUJnTE; /* <TAUJn_base> + 50H		   TAUJn channel enable status register */
    uint8_t _pad2[3];
    vuint8_t TAUJnTS; /* <TAUJn_base> + 54H		   TAUJn channel start trigger register */
    uint8_t _pad3[3];
    vuint8_t TAUJnTT; /* <TAUJn_base> + 58H 		   TAUJn channel stop trigger register */
    uint8_t _pad4[3 + 4];
    vuint8_t TAUJnTOE; /* <TAUJn_base> + 60H          TAUJn channel output enable register */
    uint8_t _pad5[3];

    uint32_t pad8[((0x80 - 0x60) - 4) / 4];

    struct {
        vuint16_t R;
        uint16_t _pad;
    } TAUJnCMORm[4]; /* <TAUJn_base> + 80H + m × 4H TAUJn channel mode OS register m */

    vuint16_t TAUJnTPS; /* 0x90, TAUJn prescaler clock select register */
    uint16_t _pad;
    vuint8_t TAUJnBRS; /* 0x94 TAUJn prescaler baud rate setting register */
    uint8_t _pad6[3];
};

/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/

ISR(Gpt_0_Isr);
ISR(Gpt_1_Isr);
ISR(Gpt_2_Isr);
ISR(Gpt_3_Isr);

static void Gpt_Isr(uint8 hwChannel);

/*lint -e{923} */
struct TAUJ_reg * const Gpt_HwReg = ((struct TAUJ_reg *) (TAUJ_BASE));

ISR(Gpt_0_Isr) {
    Gpt_Isr(0u);
}
ISR(Gpt_1_Isr) {
    Gpt_Isr(1u);
}
ISR(Gpt_2_Isr) {
    Gpt_Isr(2u);
}
ISR(Gpt_3_Isr) {
    Gpt_Isr(3u);
}

#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)	/*lint -e961 */

static void installChannelInterrupt(uint8 Chnl) {
    switch (Chnl) {
        case 0:
            ISR_INSTALL_ISR2("Gpt", Gpt_0_Isr, (IrqType )(IRQ_INTTAUJ0I0), GPT_ISR_PRIORITY, 0);
            break;

        case 1:
            ISR_INSTALL_ISR2("Gpt", Gpt_1_Isr, (IrqType )(IRQ_INTTAUJ0I1),GPT_ISR_PRIORITY, 0);
            break;

        case 2:
            ISR_INSTALL_ISR2("Gpt", Gpt_2_Isr, (IrqType )(IRQ_INTTAUJ0I2), GPT_ISR_PRIORITY, 0);
            break;

        case 3:
            ISR_INSTALL_ISR2("Gpt", Gpt_3_Isr, (IrqType )(IRQ_INTTAUJ0I3), GPT_ISR_PRIORITY, 0);
            break;
        default:
            break;
    }
}
#endif

void Gpt_Hw_Init(const Gpt_ConfigType* ConfigPtr) {
    uint8 hwChannel;

    (void) ConfigPtr; /*lint !e920 */

    /* Set the fixed pre-scalers, CK0 - 2^0, CK1 - 2^5, CK2 - 2^ 10, CK3 - 2^15 */
    Gpt_HwReg->TAUJnTPS = 0xf950u;

    /* loop over all configured channels */
    for (uint8 chnlcnt = 0; chnlcnt < GPT_ARC_LOG_UNIT_CNT; chnlcnt++) {

        /* @req SWS_Gpt_00068 */
        hwChannel = ChannelToHwChannel(chnlcnt);

        /*lint -e{835,845,960} Want the 0uL for readability */
        Gpt_HwReg->TAUJnCMORm[hwChannel].R =
                (vuint16_t) ((GET_CONFIG(chnlcnt).GptChannelPrescale<<14u) + /* CK0->CK03 */
                            (0uL<<12u) +       /* Operation clock specified by TAUJnCMORm.TAUJnCKS[1:0]. */
                            (0uL<<11u) +       /* Channel Master/Slave -> does not matter here. */
                            (0uL<<8u) +        /* Start trigger, 0=Software */
                            (0uL<<6u) +        /* Used for capture only */
                            (0uL<<0u));        /* interval mode do NOT generate interrupt at beginning */

#if !defined(CFG_DRIVERS_USE_CONFIG_ISRS)
        installChannelInterrupt(hwChannel);
#endif
    }
}

static void Gpt_Isr(uint8 hwChannel) {
    uint8 channel = HwChannelToChannel(hwChannel);

    if (GPT_CH_MODE_ONESHOT == GET_CONFIG(channel).GptChannelMode ) {
        Gpt_Hw_StopTimer(hwChannel);

        Gpt_Global.Gpt_ChannelState[channel] = GPT_STATE_EXPIRED;

        /* Trigger re-load of counter */
        Gpt_HwReg->TAUJnCDRm[hwChannel] = Gpt_HwReg->TAUJnCDRm[hwChannel];

#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
        /* Report wake up to ECUM */
        if (Gpt_Global.Gpt_WakUpEnable[channel]) {
            EcuM_CheckWakeup(GET_CONFIG(channel).GptWakeupSource);
        }
#endif
    }

    /* Notify */
    if (Gpt_Global.Gpt_NotifEnable[channel]) {
        GET_CONFIG(channel).GptNotification();
    }
}

#if GPT_DEINIT_API == STD_ON
void Gpt_Hw_DeInit( void ) {
    uint8 hwChannel;

    /* @req SWS_Gpt_00105 */
    for (uint8 chnlcnt = 0; chnlcnt < GPT_ARC_LOG_UNIT_CNT; chnlcnt++) {
        hwChannel = ChannelToHwChannel(chnlcnt);
        Gpt_HwReg->TAUJnCMORm[hwChannel].R = (vuint16_t)0uL;
    }
}
#endif

#if ( GPT_TIME_ELAPSED_API == STD_ON )
Gpt_ValueType Gpt_Hw_GetTimeElapsed( Gpt_Hw_ChannelType Channel ) {
    uint32_t v1 = Gpt_HwReg->TAUJnCDRm[Channel];
    uint32_t v2 = Gpt_HwReg->TAUJnCNTm[Channel];

    return (v1 - v2);
}
#endif

#if ( GPT_TIME_REMAINING_API == STD_ON )
Gpt_ValueType Gpt_Hw_GetTimeRemaining( Gpt_Hw_ChannelType Channel ) {
    return Gpt_HwReg->TAUJnCNTm[Channel];
}
#endif

void Gpt_Hw_StartTimer(Gpt_Hw_ChannelType Channel, Gpt_ValueType Value) {

    /* Counter starts to count down */

    /* @req SWS_Gpt_00274 */
    Gpt_HwReg->TAUJnCDRm[Channel] = Value; /* reload value */
    Gpt_HwReg->TAUJnTOE = 0u; /* software controlled output */

    /* Start timer */
    Gpt_HwReg->TAUJnTS = (vuint8_t) (1u << Channel); /* TAUJnTSm */
}

void Gpt_Hw_StopTimer(Gpt_Hw_ChannelType Channel) {
    /* @req SWS_Gpt_00013 */
    Gpt_HwReg->TAUJnTT = (vuint8_t) (1u << Channel); /* Stop timer */

}

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
void Gpt_Hw_EnableNotification( Gpt_Hw_ChannelType Channel ) {
    (void)Channel;
}

void Gpt_Hw_DisableNotification( Gpt_Hw_ChannelType Channel ) {
    (void)Channel;
}
#endif

uint32 Gpt_Arc_GetClock(Gpt_ChannelType Channel) {
    const uint32 ckPrescale[] = {0ul,32ul,1042ul,32768ul};
    uint32 prescale = GET_CONFIG(Channel).GptChannelPrescale;
    prescale = ckPrescale[prescale];

    return Mcu_Arc_GetPeripheralClock(C_AWO_TAUJ)/prescale;
}

