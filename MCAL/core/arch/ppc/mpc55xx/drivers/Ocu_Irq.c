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

/* SWS_Ocu_00008 */
#include "Ocu.h"
#include "Ocu_MemMap.h"
#include "Ocu_Internal.h"
#include "isr.h"
#include "irq.h"
#include "Os.h"

static void Check_Ocu_Notification (uint8 chan);
static void Ocu_Notification(uint8 channelId);

#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
static void Ocu_Notification(uint8 channelId) {

    volatile struct EMIOS_tag * emiosUnit;
    uint8  absChnlId;
    uint8 ChannelNumber = 0;
    uint16 n;

    emiosUnit = GET_EMIOS_UNIT(channelId/CHANNELS_PER_EMIOS_UNIT);
    absChnlId = GET_EMIOS_CHANNEL(channelId);
    /* @req SWS_Ocu_00130 */
    emiosUnit->CH[absChnlId].CSR.B.FLAG     = 1; // clear flag

    //ChannelNumber = OcuConfigPtr->OcuHwMap[channelId];
    for (n = 0; n < OCU_MATCH_CHANNEL_COUNT; n++) {
        if (OcuConfigPtr->OcuHwMap[n] == channelId) {
            ChannelNumber = (uint8)n;
            break;
        }
    }

    if ((OcuConfigPtr->OcuChannelConfig[ChannelNumber].OcuNotification != NULL) &&
            (OCU_MATCH_CHANNEL_COUNT != n)){
        /* @req SWS_Ocu_00129 */
        /* @req SWS_Ocu_00131 */
        /* @req SWS_Ocu_00132 */
        /* @req SWS_Ocu_00133 */
        OcuConfigPtr->OcuChannelConfig[ChannelNumber].OcuNotification();
    }

    // Other conditions : Just reset flags no action
    if ((emiosUnit->CH[absChnlId].CSR.B.OVFL > 0) || (emiosUnit->CH[absChnlId].CSR.B.OVR > 0)) { /*lint !e9007 Register is not of type  "read to clear" */
        emiosUnit->CH[absChnlId].CSR.B.OVFL= 1;
        emiosUnit->CH[absChnlId].CSR.B.OVR = 1;
    }

}

#if defined (CFG_MPC5645S)
/* Counter Channels */
/*
#ifdef USE_OCU_CHANNEL_8
void Ocu_isr_8() {
    Ocu_Notification (8);
}
#endif
#ifdef USE_OCU_CHANNEL_16
void Ocu_isr_16() {
    Ocu_Notification (16);
}
#endif
#ifdef USE_OCU_CHANNEL_32
void Ocu_isr_32() {
    Ocu_Notification (32);
}
#endif
#ifdef USE_OCU_CHANNEL_40
void Ocu_isr_40() {
    Ocu_Notification (40);
}
#endif
*/

/* Match Channels */
#ifdef USE_OCU_CHANNEL_9
ISR(Ocu_isr_9);
ISR(Ocu_isr_9) {Ocu_Notification(9);}
#endif
#ifdef USE_OCU_CHANNEL_10
ISR(Ocu_isr_10);
ISR(Ocu_isr_10) {Ocu_Notification(10);}
#endif
#ifdef USE_OCU_CHANNEL_11
ISR(Ocu_isr_11);
ISR(Ocu_isr_11) {Ocu_Notification(11);}
#endif
#ifdef USE_OCU_CHANNEL_12
ISR(Ocu_isr_12);
ISR(Ocu_isr_12) {Ocu_Notification(12);}
#endif
#ifdef USE_OCU_CHANNEL_13
ISR(Ocu_isr_13)
ISR(Ocu_isr_13) {Ocu_Notification(13);}
#endif
#ifdef USE_OCU_CHANNEL_14
ISR(Ocu_isr_14)
ISR(Ocu_isr_14) {Ocu_Notification(14);}
#endif
#ifdef USE_OCU_CHANNEL_15
ISR(Ocu_isr_15)
ISR(Ocu_isr_15) {Ocu_Notification(15);}
#endif
#ifdef USE_OCU_CHANNEL_17
ISR(Ocu_isr_17)
ISR(Ocu_isr_17) {Ocu_Notification(17);}
#endif
#ifdef USE_OCU_CHANNEL_18
ISR(Ocu_isr_18)
ISR(Ocu_isr_18) {Ocu_Notification(18);}
#endif
#ifdef USE_OCU_CHANNEL_19
ISR(Ocu_isr_19);
ISR(Ocu_isr_19) {Ocu_Notification(19);}
#endif
#ifdef USE_OCU_CHANNEL_20
ISR(Ocu_isr_20);
ISR(Ocu_isr_20) {Ocu_Notification(20);}
#endif
#ifdef USE_OCU_CHANNEL_21
ISR(Ocu_isr_21);
ISR(Ocu_isr_21) {Ocu_Notification(21);}
#endif
#ifdef USE_OCU_CHANNEL_22
ISR(Ocu_isr_22);
ISR(Ocu_isr_22) {Ocu_Notification(22);}
#endif
#ifdef USE_OCU_CHANNEL_33
ISR(Ocu_isr_33);
ISR(Ocu_isr_33) {Ocu_Notification(33);}
#endif
#ifdef USE_OCU_CHANNEL_34
ISR(Ocu_isr_34);
ISR(Ocu_isr_34) {Ocu_Notification(34);}
#endif
#ifdef USE_OCU_CHANNEL_35
ISR(Ocu_isr_35);
ISR(Ocu_isr_35) {Ocu_Notification(35);}
#endif
#ifdef USE_OCU_CHANNEL_36
ISR(Ocu_isr_36);
ISR(Ocu_isr_36) {Ocu_Notification(36);}
#endif
#ifdef USE_OCU_CHANNEL_37
ISR(Ocu_isr_37);
ISR(Ocu_isr_37) {Ocu_Notification(37);}
#endif
#ifdef USE_OCU_CHANNEL_38
ISR(Ocu_isr_38);
ISR(Ocu_isr_38) {Ocu_Notification(38);}
#endif
#ifdef USE_OCU_CHANNEL_39
ISR(Ocu_isr_39);
ISR(Ocu_isr_39) {Ocu_Notification(39);}
#endif
#ifdef USE_OCU_CHANNEL_41
ISR(Ocu_isr_41);
ISR(Ocu_isr_41) {Ocu_Notification(41);}
#endif
#ifdef USE_OCU_CHANNEL_42
ISR(Ocu_isr_42);
ISR(Ocu_isr_42) {Ocu_Notification(42);}
#endif
#ifdef USE_OCU_CHANNEL_43
ISR(Ocu_isr_43);
ISR(Ocu_isr_43) {Ocu_Notification(43);}
#endif
#ifdef USE_OCU_CHANNEL_44
ISR(Ocu_isr_44);
ISR(Ocu_isr_44) {Ocu_Notification(44);}
#endif
#ifdef USE_OCU_CHANNEL_45
ISR(Ocu_isr_45);
ISR(Ocu_isr_45) {Ocu_Notification(45);}
#endif
#ifdef USE_OCU_CHANNEL_46
ISR(Ocu_isr_46);
ISR(Ocu_isr_46) {Ocu_Notification(46);}
#endif

void Ocu_Arc_InstallInterrupts (void) {
    /* Counter Channels */
/*
#ifdef USE_OCU_CHANNEL_8
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_8, (int16_t)EMIOS_0_GFR_F8, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_16
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_16, (int16_t)EMIOS_0_GFR_F16, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_32
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_32, (int16_t)EMIOS_1_GFR_F8, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_40
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_40, (int16_t)EMIOS_1_GFR_F16, 2, 0 );
#endif
*/
    /* Match Channels */
#ifdef USE_OCU_CHANNEL_9
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_9, (int16_t)EMIOS_0_GFR_F9, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_10
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_10, (int16_t)EMIOS_0_GFR_F10, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_11
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_11, (int16_t)EMIOS_0_GFR_F11, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_12
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_12, (int16_t)EMIOS_0_GFR_F12, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_13
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_13, (int16_t)EMIOS_0_GFR_F13, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_14
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_14, (int16_t)EMIOS_0_GFR_F14, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_15
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_15, (int16_t)EMIOS_0_GFR_F15, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_17
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_17, (int16_t)EMIOS_0_GFR_F17, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_18
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_18, (int16_t)EMIOS_0_GFR_F18, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_19
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_19, (int16_t)EMIOS_0_GFR_F19, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_20
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_20, (int16_t)EMIOS_0_GFR_F20, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_21
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_21, (int16_t)EMIOS_0_GFR_F21, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_22
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_22, (int16_t)EMIOS_0_GFR_F22, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_33
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_33, (int16_t)EMIOS_1_GFR_F9, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_34
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_34, (int16_t)EMIOS_1_GFR_F10, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_35
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_35, (int16_t)EMIOS_1_GFR_F11, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_36
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_36, (int16_t)EMIOS_1_GFR_F12, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_37
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_37, (int16_t)EMIOS_1_GFR_F13, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_38
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_38, (int16_t)EMIOS_1_GFR_F14, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_39
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_39, (int16_t)EMIOS_1_GFR_F15, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_41
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_41, (int16_t)EMIOS_1_GFR_F17, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_42
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_42, (int16_t)EMIOS_1_GFR_F18, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_43
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_43, (int16_t)EMIOS_1_GFR_F19, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_44
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_44, (int16_t)EMIOS_1_GFR_F20, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_45
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_45, (int16_t)EMIOS_1_GFR_F21, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_46
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_46, (int16_t)EMIOS_1_GFR_F22, 2, 0 );
#endif
}

#elif defined (CFG_MPC5606B) || defined(CFG_SPC560B54)
/* Counter Channels */
/* These channels drives the counters and should not be used for OCU functions. */
/*
#ifdef USE_OCU_CHANNEL_0
void Ocu_isr_0() {
    Ocu_Notification (0);
}
 *
#ifdef USE_OCU_CHANNEL_8
void Ocu_isr_8() {
    Ocu_Notification (8);
}
#endif
#ifdef USE_OCU_CHANNEL_16
void Ocu_isr_16() {
    Ocu_Notification (16);
}
#endif
#ifdef USE_OCU_CHANNEL_23
void Ocu_isr_23() {
    Ocu_Notification (23);
}
#endif
#ifdef USE_OCU_CHANNEL_24
void Ocu_isr_24() {
    Ocu_Notification (24);
}
#endif
#ifdef USE_OCU_CHANNEL_32
void Ocu_isr_32() {
    Ocu_Notification (32);
}
#endif
#ifdef USE_OCU_CHANNEL_40
void Ocu_isr_40() {
    Ocu_Notification (40);
}
#endif
#ifdef USE_OCU_CHANNEL_48
void Ocu_isr_48() {
    Ocu_Notification (48);
}
#endif
#ifdef USE_OCU_CHANNEL_55
void Ocu_isr_55() {
    Ocu_Notification (55);
}
#endif
#ifdef USE_OCU_CHANNEL_56
void Ocu_isr_56() {
    Ocu_Notification (56);
}
#endif
*/

/* Since two channels are connected to the same interrupt we need to
 * check if the given channel is the source for the interrupt.
 * In that case call the notification handler.
 */
static void Check_Ocu_Notification (uint8 chan)
{
    const volatile struct EMIOS_tag * emiosUnit = GET_EMIOS_UNIT(chan/CHANNELS_PER_EMIOS_UNIT);
    uint8 absChnlId = GET_EMIOS_CHANNEL(chan);

    uint32 flagmask = emiosUnit->GFR.R;

    if ((emiosUnit->CH[absChnlId].CCR.B.FEN == 1UL) && ((flagmask & (1UL << absChnlId)) > 0))
    {
        Ocu_Notification(chan);
    }
}

/* Match Channels */

/* Channel 0 drives the counter bus */

#ifdef USE_OCU_CHANNEL_1
ISR(Ocu_isr_1);
ISR(Ocu_isr_1) {Ocu_Notification(1);}
#endif

#if (defined(USE_OCU_CHANNEL_2) || defined(USE_OCU_CHANNEL_3))
ISR(Ocu_isr_2_3);
ISR(Ocu_isr_2_3) {
    Check_Ocu_Notification(2);
    Check_Ocu_Notification(3);
}
#endif

#if (defined(USE_OCU_CHANNEL_4) || defined(USE_OCU_CHANNEL_5))
ISR(Ocu_isr_4_5);
ISR(Ocu_isr_4_5) {
    Check_Ocu_Notification(4);
    Check_Ocu_Notification(5);
}
#endif

#if (defined(USE_OCU_CHANNEL_6) || defined(USE_OCU_CHANNEL_7))
ISR(Ocu_isr_6_7);
ISR(Ocu_isr_6_7) {
    Check_Ocu_Notification(6);
    Check_Ocu_Notification(7);
}
#endif

/* Channel 8 drives the counter bus */

#ifdef USE_OCU_CHANNEL_9
ISR(Ocu_isr_9);
ISR(Ocu_isr_9) {Ocu_Notification(9);}
#endif

#if (defined(USE_OCU_CHANNEL_10) || defined(USE_OCU_CHANNEL_11))
ISR(Ocu_isr_10_11);
ISR(Ocu_isr_10_11) {
    Check_Ocu_Notification(10);
    Check_Ocu_Notification(11);
}
#endif

#if (defined(USE_OCU_CHANNEL_12) || defined(USE_OCU_CHANNEL_13))
ISR(Ocu_isr_12_13);
ISR(Ocu_isr_12_13) {
    Check_Ocu_Notification(12);
    Check_Ocu_Notification(13);
}
#endif

#if (defined(USE_OCU_CHANNEL_14) || defined(USE_OCU_CHANNEL_15))
ISR(Ocu_isr_14_15);
ISR(Ocu_isr_14_15) {
    Check_Ocu_Notification(14);
    Check_Ocu_Notification(15);
}
#endif

/* Channel 16 drives the counter bus */

#ifdef USE_OCU_CHANNEL_17
ISR(Ocu_isr_17);
ISR(Ocu_isr_17) {Ocu_Notification(17);}
#endif

#if (defined(USE_OCU_CHANNEL_18) || defined(USE_OCU_CHANNEL_19))
ISR(Ocu_isr_18_19);
ISR(Ocu_isr_18_19) {
    Check_Ocu_Notification(18);
    Check_Ocu_Notification(19);
}
#endif

#if (defined(USE_OCU_CHANNEL_20) || defined(USE_OCU_CHANNEL_21))
ISR(Ocu_isr_20_21);
ISR(Ocu_isr_20_21) {
    Check_Ocu_Notification(20);
    Check_Ocu_Notification(21);
}
#endif

#ifdef USE_OCU_CHANNEL_22
ISR(Ocu_isr_22);
ISR(Ocu_isr_22) {Ocu_Notification(22);}
#endif

/* Channel 23, 24 drives the counter bus */

#ifdef USE_OCU_CHANNEL_25
ISR(Ocu_isr_25);
ISR(Ocu_isr_25) {Ocu_Notification(25);}
#endif

#if (defined(USE_OCU_CHANNEL_26) || defined(USE_OCU_CHANNEL_27))
ISR(Ocu_isr_26_27);
ISR(Ocu_isr_26_27) {
    Check_Ocu_Notification(26);
    Check_Ocu_Notification(27);
}
#endif
#if (defined(USE_OCU_CHANNEL_28) || defined(USE_OCU_CHANNEL_29))
ISR(Ocu_isr_28_29);
ISR(Ocu_isr_28_29) {
    Check_Ocu_Notification(28);
    Check_Ocu_Notification(29);
}
#endif
#if (defined(USE_OCU_CHANNEL_30) || defined(USE_OCU_CHANNEL_31))
ISR(Ocu_isr_30_31);
ISR(Ocu_isr_30_31) {
    Check_Ocu_Notification(30);
    Check_Ocu_Notification(31);
}
#endif

/* Channel 32 drives the counter bus */

#ifdef USE_OCU_CHANNEL_33
ISR(Ocu_isr_33);
ISR(Ocu_isr_33) {Ocu_Notification(33);}
#endif

#if (defined(USE_OCU_CHANNEL_34) || defined(USE_OCU_CHANNEL_35))
ISR(Ocu_isr_34_35);
ISR(Ocu_isr_34_35) {
    Check_Ocu_Notification(34);
    Check_Ocu_Notification(35);
}
#endif

#if (defined(USE_OCU_CHANNEL_36) || defined(USE_OCU_CHANNEL_37))
ISR(Ocu_isr_36_37);
ISR(Ocu_isr_36_37) {
    Check_Ocu_Notification(36);
    Check_Ocu_Notification(37);
}
#endif

#if (defined(USE_OCU_CHANNEL_38) || defined(USE_OCU_CHANNEL_39))
ISR(Ocu_isr_38_39);
ISR(Ocu_isr_38_39) {
    Check_Ocu_Notification(38);
    Check_Ocu_Notification(39);
}
#endif

/* Channel 40 drives the counter bus */

#ifdef USE_OCU_CHANNEL_41
ISR(Ocu_isr_41);
ISR(Ocu_isr_41) {Ocu_Notification(41);}
#endif

#if (defined(USE_OCU_CHANNEL_42) || defined(USE_OCU_CHANNEL_43))
ISR(Ocu_isr_42_43);
ISR(Ocu_isr_42_43) {
    Check_Ocu_Notification(42);
    Check_Ocu_Notification(43);
}
#endif

#if (defined(USE_OCU_CHANNEL_44) || defined(USE_OCU_CHANNEL_45))
ISR(Ocu_isr_44_45);
ISR(Ocu_isr_44_45) {
    Check_Ocu_Notification(44);
    Check_Ocu_Notification(45);
}
#endif

#if (defined(USE_OCU_CHANNEL_46) || defined(USE_OCU_CHANNEL_47))
ISR(Ocu_isr_46_47);
ISR(Ocu_isr_46_47) {
    Check_Ocu_Notification(46);
    Check_Ocu_Notification(47);
}
#endif

/* Channel 48 drives the counter bus */

#ifdef USE_OCU_CHANNEL_49
ISR(Ocu_isr_49);
ISR(Ocu_isr_49) {Ocu_Notification(49);}
#endif

#if (defined(USE_OCU_CHANNEL_50) || defined(USE_OCU_CHANNEL_51))
ISR(Ocu_isr_50_51);
ISR(Ocu_isr_50_51) {
    Check_Ocu_Notification(50);
    Check_Ocu_Notification(51);
}
#endif

#if (defined(USE_OCU_CHANNEL_52) || defined(USE_OCU_CHANNEL_53))
ISR(Ocu_isr_52_53);
ISR(Ocu_isr_52_53) {
    Check_Ocu_Notification(52);
    Check_Ocu_Notification(53);
}
#endif

#ifdef USE_OCU_CHANNEL_54
ISR(Ocu_isr_54);
ISR(Ocu_isr_54) {Ocu_Notification(54);}
#endif

/* Channel 56 drives the counter bus */

#ifdef USE_OCU_CHANNEL_57
ISR(Ocu_isr_57);
ISR(Ocu_isr_57) {Ocu_Notification(57);}
#endif

#if (defined(USE_OCU_CHANNEL_58) || defined(USE_OCU_CHANNEL_59))
ISR(Ocu_isr_58_59);
ISR(Ocu_isr_58_59) {
    Check_Ocu_Notification(58);
    Check_Ocu_Notification(59);
}
#endif

#if (defined(USE_OCU_CHANNEL_60) || defined(USE_OCU_CHANNEL_61))
ISR(Ocu_isr_60_61);
ISR(Ocu_isr_60_61) {
    Check_Ocu_Notification(60);
    Check_Ocu_Notification(61);
}
#endif

#if (defined(USE_OCU_CHANNEL_62) || defined(USE_OCU_CHANNEL_62))
ISR(Ocu_isr_62_63);
ISR(Ocu_isr_62_63) {
    Check_Ocu_Notification(62);
    Check_Ocu_Notification(63);
}
#endif

void Ocu_Arc_InstallInterrupts () {
    /* Counter Channels */
    /* These channels drives the counters and should not be used for OCU functions. */
/*
#ifdef USE_OCU_CHANNEL_0
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_0 (int16_t)EMIOS_0_GFR_F0_F1, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_8
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_8, (int16_t)EMIOS_0_GFR_F8_F9, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_16
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_16, (int16_t)EMIOS_0_GFR_F16_F17, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_23
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_0 (int16_t)EMIOS_0_GFR_F22_F23, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_24
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_8, (int16_t)EMIOS_0_GFR_F24_F25, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_32
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_32, (int16_t)EMIOS_1_GFR_F0_F1, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_40
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_40, (int16_t)EMIOS_1_GFR_F8_F9, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_48
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_48, (int16_t)EMIOS_1_GFR_F16_F17, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_55
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_55, (int16_t)EMIOS_1_GFR_F22_F23, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_56
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_56, (int16_t)EMIOS_1_GFR_F24_F25, 2, 0 );
#endif
*/

    /* Match Channels */

/* Channel 0 drives the counter bus */
#ifdef USE_OCU_CHANNEL_1
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_1, (int16_t)EMIOS_0_GFR_F0_F1, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_2) || defined(USE_OCU_CHANNEL_3)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_2_3, (int16_t)EMIOS_0_GFR_F2_F3, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_4) || defined(USE_OCU_CHANNEL_5)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_4_5, (int16_t)EMIOS_0_GFR_F4_F5, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_6) || defined(USE_OCU_CHANNEL_7)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_6_7, (int16_t)EMIOS_0_GFR_F6_F7, 2, 0 );
#endif
/* Channel 8 drives the counter bus */
#ifdef USE_OCU_CHANNEL_9
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_9, (int16_t)EMIOS_0_GFR_F8_F9, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_10) || defined(USE_OCU_CHANNEL_11)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_10_11, (int16_t)EMIOS_0_GFR_F10_F11, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_12) || defined(USE_OCU_CHANNEL_13)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_12_13, (int16_t)EMIOS_0_GFR_F12_F13, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_14) || defined(USE_OCU_CHANNEL_15)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_14_15, (int16_t)EMIOS_0_GFR_F14_F15, 2, 0 );
#endif
/* Channel 16 drives the counter bus */
#ifdef USE_OCU_CHANNEL_17
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_17, (int16_t)EMIOS_0_GFR_F16_F17, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_18) || defined(USE_OCU_CHANNEL_19)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_18_19, (int16_t)EMIOS_0_GFR_F18_F19, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_20) || defined(USE_OCU_CHANNEL_21)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_20_21, (int16_t)EMIOS_0_GFR_F20_F21, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_22
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_22, (int16_t)EMIOS_0_GFR_F22_F23, 2, 0 );
#endif
/* Channel 23 and 24 drives the counter bus */
#ifdef USE_OCU_CHANNEL_25
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_25, (int16_t)EMIOS_0_GFR_F24_F25, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_26) || defined(USE_OCU_CHANNEL_27)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_26_27, (int16_t)EMIOS_0_GFR_F26_F27, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_28) || defined(USE_OCU_CHANNEL_29)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_28_29, (int16_t)EMIOS_0_GFR_F28_F29, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_30) || defined(USE_OCU_CHANNEL_31)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_30_31, (int16_t)EMIOS_0_GFR_F30_F31, 2, 0 );
#endif
/* Channel 32 drives the counter bus */
#ifdef USE_OCU_CHANNEL_33
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_33, (int16_t)EMIOS_1_GFR_F0_F1, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_34) || defined(USE_OCU_CHANNEL_35)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_34_35, (int16_t)EMIOS_1_GFR_F2_F3, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_36) || defined(USE_OCU_CHANNEL_37)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_36_37, (int16_t)EMIOS_1_GFR_F4_F5, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_38) || defined(USE_OCU_CHANNEL_39)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_38_39, (int16_t)EMIOS_1_GFR_F6_F7, 2, 0 );
#endif
/* Channel 40 drives the counter bus */
#ifdef USE_OCU_CHANNEL_41
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_41, (int16_t)EMIOS_1_GFR_F8_F9, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_42) || defined(USE_OCU_CHANNEL_43)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_42_43, (int16_t)EMIOS_1_GFR_F10_F11, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_44) || defined(USE_OCU_CHANNEL_45)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_44_45, (int16_t)EMIOS_1_GFR_F12_F13, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_46) || defined(USE_OCU_CHANNEL_47)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_46_47, (int16_t)EMIOS_1_GFR_F14_F15, 2, 0 );
#endif
/* Channel 48 drives the counter bus */
#ifdef USE_OCU_CHANNEL_49
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_49, (int16_t)EMIOS_1_GFR_F16_F17, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_50) || defined(USE_OCU_CHANNEL_51)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_50_51, (int16_t)EMIOS_1_GFR_F18_F19, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_52) || defined(USE_OCU_CHANNEL_53)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_52_53, (int16_t)EMIOS_1_GFR_F20_F21, 2, 0 );
#endif
#ifdef USE_OCU_CHANNEL_54
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_54, (int16_t)EMIOS_1_GFR_F22_F23, 2, 0 );
#endif
/* Channel 55 and 56 drives the counter bus */
#ifdef USE_OCU_CHANNEL_57
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_57, (int16_t)EMIOS_1_GFR_F24_F25, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_58) || defined(USE_OCU_CHANNEL_59)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_58_59, (int16_t)EMIOS_1_GFR_F26_F27, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_60) || defined(USE_OCU_CHANNEL_61)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_60_61, (int16_t)EMIOS_1_GFR_F28_F29, 2, 0 );
#endif
#if defined(USE_OCU_CHANNEL_62) || defined(USE_OCU_CHANNEL_63)
    ISR_INSTALL_ISR2( "Ocu", Ocu_isr_62_63, (int16_t)EMIOS_1_GFR_F30_F31, 2, 0 );
#endif
}

#endif

#endif

//lint -restore
