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

/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.0.3 */
/** @tagSettings DEFAULT_ARCHITECTURE=RH850F1H */


#ifndef FR_INTERNAL_H_
#define FR_INTERNAL_H_

#include "Fr.h"

//CHI Command Vector Bit
#define CHI_CMD_NOT_ACCEPTED            0x00
#define CHI_CMD_CONFIG                  0x01
#define CHI_CMD_READY                   0x02
#define CHI_CMD_WAKEUP                  0x03
#define CHI_CMD_RUN                     0x04
#define CHI_CMD_ALL_SLOTS               0x05
#define CHI_CMD_HALT                    0x06
#define CHI_CMD_FREEZE                  0x07
#define CHI_CMD_SEND_MTS                0x08
#define CHI_CMD_ALLOW_COLDSTART         0x09
#define CHI_CMD_RESET_STATUS_INDICATORS 0x0A
#define CHI_CMD_MONITOR_MODE            0x0B
#define CHI_CMD_CLEAR_RAMS              0x0C

#if defined(CFG_RH850)
struct FLXA_reg {
    uint32 FROC;
    uint32 pad_0;
    uint32 FROS;
    uint32 FRTEST1;
    uint32 FRTEST2;
    uint32 pad_1;
    uint32 FRLCK;
    uint32 FREIR;
    uint32 FRSIR;
    uint32 FREILS;
    uint32 FRSILS;
    uint32 FREIES;
    uint32 FREIER;
    uint32 FRSIES;
    uint32 FRSIER;
    uint32 FRILE;
    uint32 FRT0C;
    uint32 FRT1C;
    uint32 FRSTPW1;
    uint32 FRSTPW2;
    uint32 pad_2[11];
    uint32 FRSUCC1;
    uint32 FRSUCC2;
    uint32 FRSUCC3;
    uint32 FRNEMC;
    uint32 FRPRTC1;
    uint32 FRPRTC2;
    uint32 FRMHDC;
    uint32 pad_3;
    uint32 FRGTUC1;
    uint32 FRGTUC2;
    uint32 FRGTUC3;
    uint32 FRGTUC4;
    uint32 FRGTUC5;
    uint32 FRGTUC6;
    uint32 FRGTUC7;
    uint32 FRGTUC8;
    uint32 FRGTUC9;
    uint32 FRGTUC10;
    uint32 FRGTUC11;
    uint32 pad_4[13];
    uint32 FRCCSV;
    uint32 FRCCEV;
    uint32 pad_5[2];
    uint32 FRSCV;
    uint32 FRMTCCV;
    uint32 FRRCV;
    uint32 FROCV;
    uint32 FRSFS;
    uint32 FRSWNIT;
    uint32 FRACS;
    uint32 pad_6;
    uint32 FRESID1;
    uint32 FRESID2;
    uint32 FRESID3;
    uint32 FRESID4;
    uint32 FRESID5;
    uint32 FRESID6;
    uint32 FRESID7;
    uint32 FRESID8;
    uint32 FRESID9;
    uint32 FRESID10;
    uint32 FRESID11;
    uint32 FRESID12;
    uint32 FRESID13;
    uint32 FRESID14;
    uint32 FRESID15;
    uint32 pad_7;
    uint32 FROSID1;
    uint32 FROSID2;
    uint32 FROSID3;
    uint32 FROSID4;
    uint32 FROSID5;
    uint32 FROSID6;
    uint32 FROSID7;
    uint32 FROSID8;
    uint32 FROSID9;
    uint32 FROSID10;
    uint32 FROSID11;
    uint32 FROSID12;
    uint32 FROSID13;
    uint32 FROSID14;
    uint32 FROSID15;
    uint32 pad_8;
    uint32 FRNMV1;
    uint32 FRNMV2;
    uint32 FRNMV3;
    uint32 pad_9[81];
    uint32 FRMRC;
    uint32 FRFRF;
    uint32 FRFRFM;
    uint32 FRFCL;
    uint32 FRMHDS;
    uint32 FRLDTS;
    uint32 FRFSR;
    uint32 FRMHDF;
    uint32 FRTXRQ1;
    uint32 FRTXRQ2;
    uint32 FRTXRQ3;
    uint32 FRTXRQ4;
    uint32 FRNDAT1;
    uint32 FRNDAT2;
    uint32 FRNDAT3;
    uint32 FRNDAT4;
    uint32 FRMBSC1;
    uint32 FRMBSC2;
    uint32 FRMBSC3;
    uint32 FRMBSC4;
    uint32 pad_10[44];
    uint8 FRWRDS[256]; /* Use the 8-bit access */
    uint32 FRWRHS1;
    uint32 FRWRHS2;
    uint32 FRWRHS3;
    uint32 pad_11;
    uint32 FRIBCM;
    uint32 FRIBCR;
    uint32 pad_12[58];
    uint8 FRRDDS[256]; /* Use the 8-bit access */
    uint32 FRRDHS1;
    uint32 FRRDHS2;
    uint32 FRRDHS3;
    uint32 FRMBS;
    uint32 FROBCM;
    uint32 FROBCR;
    uint32 pad_13[58];
    uint32 FRITC;
    uint32 FROTC;
    uint32 FRIBA;
    uint32 FRFBA;
    uint32 FROBA;
    uint32 FRIQC;
    uint32 FRUIR;
    uint32 FRUOR;
    uint32 FRITS;
    uint32 FROTS;
    uint32 FRAES;
    uint32 FRAEA;
    uint32 FRDA0;
    uint32 FRDA1;
    uint32 FRDA2;
    uint32 FRDA3;
    uint32 pad_14;
    uint32 FRT2C;
};
#endif



typedef struct {
    const Fr_ConfigType *Fr_ConfigPtr;
    Fr_POCStateType Fr_CCPocState[FR_ARC_CTRL_CONFIG_CNT];
    boolean Fr_HasIntiailized;
#if defined(CFG_RH850)
    volatile struct FLXA_reg *hwPtr[FR_ARC_CTRL_CONFIG_CNT];
#endif
}Fr_ContainerType;

/* @req FR098 */
Std_ReturnType Fr_Internal_ClearPendingTx(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx);
Std_ReturnType Fr_Internal_ClearPendingRx(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx);
Std_ReturnType Fr_Internal_RunAllCCTest(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx);
Std_ReturnType Fr_Internal_RunCCTest(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx);
void Fr_Internal_SetupCC(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx);
Std_ReturnType Fr_Internal_SetupRxTxResources(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx);
void Fr_Arc_ClearPendingIsr(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx);
void Fr_Internal_DisableAllTimers(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx);
void Fr_Internal_DisableAllFrIsr(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx);
void Fr_Internal_DisableAllLPdu(void);
Std_ReturnType Fr_Internal_SetCtrlChiCmd(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8 chiCmd);
Std_ReturnType Fr_Internal_EnableCtrl(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx);
Std_ReturnType Fr_Internal_setupAndTestCC(Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx);
Std_ReturnType Fr_Internal_GetChiPocState(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, Fr_POCStatusType* Fr_POCStatusPtr);
Std_ReturnType Fr_Internal_SetTxData(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, const uint8* Fr_LSduPtr, uint8 Fr_LSduLength, uint16 Fr_MsgBuffrIdx);
Std_ReturnType Fr_Internal_CheckHeader(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint32 trigIdx);
Std_ReturnType Fr_Internal_CheckNewData(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint16 msgBufferIdx);
Std_ReturnType Fr_Internal_GetNewData(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint32 trigIdx, uint8* Fr_LSduPtr, uint8* Fr_LSduLengthPtr);
Std_ReturnType Fr_Internal_GetTxPending(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint32 trigIdx, boolean *txPending);
Std_ReturnType Fr_Internal_CancelTx(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint16 msgBufferIdx);
Std_ReturnType Fr_Internal_SetWUPChannel(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, Fr_ChannelType Fr_ChnlIdx);
Std_ReturnType  Fr_Internal_GetGlobalTime(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8* Fr_CyclePtr, uint16* Fr_MacroTickPtr);
Std_ReturnType Fr_Internal_IsSynchronous(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx);
void Fr_Internal_SetupAbsTimer(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx, uint8 Fr_Cycle, uint16 Fr_Offset);
void Fr_Internal_DisableAbsTimer(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx);
boolean Fr_Internal_GetAbsTimerIrqStatus(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx);
void Fr_Internal_ResetAbsTimerIsrFlag(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx);
void Fr_Internal_DisableAbsTimerIrq(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx);
void Fr_Internal_EnableAbsTimerIrq(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx);
Std_ReturnType Fr_Internal_UpdateHeaderLength(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8 length, uint16 msgBuffrIdx, uint32 frameTrigIdx);
#if defined(USE_DEM) || defined(CFG_FR_DEM_TEST)
static inline void Fr_Internal_reportDem(Dem_EventIdType eventId, Dem_EventStatusType eventStatus);
#endif

#endif /*FR_INTERNAL_H_*/
