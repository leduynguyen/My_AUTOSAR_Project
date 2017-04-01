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


/* ----------------------------[includes]------------------------------------*/
#include "Fr.h"
#include "Fr_Internal.h"
#if defined(USE_DEM) || defined(CFG_FR_DEM_TEST)
#include "Dem.h"
#endif
#if defined(USE_DET)
#include "Det.h"
#endif


/* ----------------------------[private define]------------------------------*/
#define MASK_FRITC_ITE      (uint32)0x00000001UL
#define MASK_FRITC_IQHR     (uint32)0x00000002UL
#define MASK_FRITS_ITS      (uint32)0x00000001UL
#define MASK_FROTC_OTE      (uint32)0x00000001UL
#define MASK_FROTS_OTS      (uint32)0x00000001UL
#define MASK_FRTXC_T2RC     (uint32)0x00000001UL
#define MASK_FROC_T0IE      (uint32)0x010000UL
#define MASK_FROC_T1IE      (uint32)0x020000UL
#define MASK_FROC_T2IE      (uint32)0x040000UL

#define MASK_FRITC_IQFIE    (uint32)0x00000100UL
#define MASK_FRITC_IQEIE    (uint32)0x00000200UL

#define LOCK_FIRST_WRITE        (uint32)0xCEUL
#define LOCK_SECOND_WRITE       (uint32)0x31UL

#define MASK_FRSUCC1_CMD        (uint32)0x0FUL
#define MASK_FRSUCC1_PBSY       (uint32)0x80UL
#define MASK_FRSUCC1_TXST       (uint32)0x100UL
#define BIT_SHIFT_FRSUCC1_TXST  (uint32)8UL
#define MASK_FRSUCC1_TXSY       (uint32)0x200UL
#define BIT_SHIFT_FRSUCC1_TXSY  (uint32)9UL
#define MASK_FRSUCC1_CSA        (uint32)0xF800UL
#define BIT_SHIFT_FRSUCC1_CSA   (uint32)11UL
#define MASK_FRSUCC1_PTA        (uint32)0x1F0000UL
#define BIT_SHIFT_FRSUCC1_PTA   (uint32)16UL
#define MASK_FRSUCC1_WUCS       (uint32)0x200000UL
#define BIT_SHIFT_FRSUCC1_WUCS  (uint32)21UL
#define MASK_FRSUCC1_TSM        (uint32)0x400000UL
#define BIT_SHIFT_FRSUCC1_TSM   (uint32)22UL
#define MASK_FRSUCC1_HCSE       (uint32)0x800000UL
#define BIT_SHIFT_FRSUCC1_HCSE  (uint32)23UL
#define MASK_FRSUCC1_CCH        (uint32)0xC000000UL
#define BIT_SHIFT_FRSUCC1_CCH   (uint32)26UL
#define MASK_FRSUCC1_CLEAR_PARAM (uint32)(MASK_FRSUCC1_TXST | MASK_FRSUCC1_TXSY | MASK_FRSUCC1_PTA | MASK_FRSUCC1_WUCS | MASK_FRSUCC1_TSM | MASK_FRSUCC1_HCSE | MASK_FRSUCC1_CCH | MASK_FRSUCC1_CSA)

#define MASK_FRSUCC2_LT         (uint32)0x1FFFFFUL
#define BIT_SHIFT_FRSUCC2_LT    (uint32)0UL
#define MASK_FRSUCC2_LTN        (uint32)0x0F000000UL
#define BIT_SHIFT_FRSUCC2_LTN   (uint32)24UL
#define MASK_FRSUCC2_CLEAR_PARAM (uint32)(MASK_FRSUCC2_LT | MASK_FRSUCC2_LTN)

#define MASK_FRSUCC3_WCP        (uint32)0x0FUL
#define BIT_SHIFT_FRSUCC3_WCP   (uint32)0UL
#define MASK_FRSUCC3_WCF        (uint32)0xF0UL
#define BIT_SHIFT_FRSUCC3_WCF   (uint32)4UL
#define MASK_FRSUCC3_CLEAR_PARAM (uint32)(MASK_FRSUCC3_WCP | MASK_FRSUCC3_WCF)

#define MASK_FRNEMC_NML         (uint32)0x00000FUL
#define MASK_FRNEMC_CLEAR_PARAM (uint32)(MASK_FRNEMC_NML)

#define MASK_FRPRTC1_TSST       (uint32)0x0FUL
#define BIT_SHIFT_FRPRTC1_TSST  (uint32)0UL
#define MASK_FRPRTC1_CASM       (uint32)0x07F0UL
#define BIT_SHIFT_FRPRTC1_CASM  (uint32)4UL
#define MASK_FRPRTC1_BRP        (uint32)0xC000UL
#define BIT_SHIFT_FRPRTC1_BRP   (uint32)14UL
#define MASK_FRPRTC1_RXW        (uint32)0x01FF0000UL
#define BIT_SHIFT_FRPRTC1_RXW   (uint32)16UL
#define MASK_FRPRTC1_RWP        (uint32)0xFC000000UL
#define BIT_SHIFT_FRPRTC1_RWP   (uint32)26UL
#define MASK_FRPRTC1_CLEAR_PARAM (uint32)(MASK_FRPRTC1_TSST | MASK_FRPRTC1_CASM | MASK_FRPRTC1_BRP | MASK_FRPRTC1_RXW | MASK_FRPRTC1_RWP)

#define MASK_FRPRTC2_RXI        (uint32)0x3FUL
#define BIT_SHIFT_FRPRTC2_RXI   (uint32)0UL
#define MASK_FRPRTC2_RXL        (uint32)0x3F00UL
#define BIT_SHIFT_FRPRTC2_RXL   (uint32)8UL
#define MASK_FRPRTC2_TXI        (uint32)0xFF0000UL
#define BIT_SHIFT_FRPRTC2_TXI   (uint32)16UL
#define MASK_FRPRTC2_TXL        (uint32)0x3F000000UL
#define BIT_SHIFT_FRPRTC2_TXL   (uint32)24UL
#define MASK_FRPRTC2_CLEAR_PARAM (uint32)(MASK_FRPRTC2_RXI | MASK_FRPRTC2_RXL | MASK_FRPRTC2_TXI | MASK_FRPRTC2_TXL)

#define MASK_FRMHDC_SFDL        (uint32)0x7FUL
#define BIT_SHIFT_FRMHDC_SFDL   (uint32)0UL
#define MASK_FRMHDC_SLT         (uint32)0x1FFF0000UL
#define BIT_SHIFT_FRMHDC_SLT    (uint32)16UL
#define MASK_FRMHDC_CLEAR_PARAM (uint32)(MASK_FRMHDC_SLT | MASK_FRMHDC_SFDL)

#define MASK_FRGTUC1_UT         (uint32)0x000FFFFFUL
#define MASK_FRGTUC1_CLEAR_PARAM (uint32)(MASK_FRGTUC1_UT)

#define MASK_FRGTUC2_MPC        (uint32)0x3FFFUL
#define BIT_SHIFT_FRGTUC2_MPC   (uint32)0UL
#define MASK_FRGTUC2_SNM        (uint32)0x0F0000UL
#define BIT_SHIFT_FRGTUC2_SNM   (uint32)16UL
#define MASK_FRGTUC2_CLEAR_PARAM (uint32)(MASK_FRGTUC2_MPC | MASK_FRGTUC2_SNM)

#define MASK_FRGTUC3_UIOA       (uint32)0xFFUL
#define BIT_SHIFT_FRGTUC3_UIOA  (uint32)0UL
#define MASK_FRGTUC3_UIOB       (uint32)0xFF00UL
#define BIT_SHIFT_FRGTUC3_UIOB  (uint32)8UL
#define MASK_FRGTUC3_MIOA       (uint32)0x7F0000UL
#define BIT_SHIFT_FRGTUC3_MIOA  (uint32)16UL
#define MASK_FRGTUC3_MIOB       (uint32)0x7F000000UL
#define BIT_SHIFT_FRGTUC3_MIOB  (uint32)24UL
#define MASK_FRGTUC3_CLEAR_PARAM (uint32)(MASK_FRGTUC3_UIOA | MASK_FRGTUC3_UIOB | MASK_FRGTUC3_MIOA | MASK_FRGTUC3_MIOB)

#define MASK_FRGTUC4_NIT        (uint32)0x3FFFUL
#define BIT_SHIFT_FRGTUC4_NIT   (uint32)0UL
#define MASK_FRGTUC4_OCS        (uint32)0x3FFF0000UL
#define BIT_SHIFT_FRGTUC4_OCS   (uint32)16UL
#define MASK_FRGTUC4_CLEAR_PARAM (uint32)(MASK_FRGTUC4_NIT | MASK_FRGTUC4_OCS)

#define MASK_FRGTUC5_DCA        (uint32)0xFFUL
#define BIT_SHIFT_FRGTUC5_DCA   (uint32)0UL
#define MASK_FRGTUC5_DCB        (uint32)0xFF00UL
#define BIT_SHIFT_FRGTUC5_DCB   (uint32)8UL
#define MASK_FRGTUC5_CDD        (uint32)0x1F0000UL
#define BIT_SHIFT_FRGTUC5_CDD   (uint32)16UL
#define MASK_FRGTUC5_DEC        (uint32)0xFF000000UL
#define BIT_SHIFT_FRGTUC5_DEC   (uint32)24UL
#define MASK_FRGTUC5_CLEAR_PARAM (uint32)(MASK_FRGTUC5_DCA | MASK_FRGTUC5_DCB | MASK_FRGTUC5_CDD | MASK_FRGTUC5_DEC)

#define MASK_FRGTUC6_ASR        (uint32)0x07FFUL
#define BIT_SHIFT_FRGTUC6_ASR   (uint32)0UL
#define MASK_FRGTUC6_MOD        (uint32)0x07FF0000UL
#define BIT_SHIFT_FRGTUC6_MOD   (uint32)16UL
#define MASK_FRGTUC6_CLEAR_PARAM (uint32)(MASK_FRGTUC6_ASR | MASK_FRGTUC6_MOD)

#define MASK_FRGTUC7_SSL        (uint32)0x3FFUL
#define BIT_SHIFT_FRGTUC7_SSL   (uint32)0UL
#define MASK_FRGTUC7_NSS        (uint32)0x3FF0000UL
#define BIT_SHIFT_FRGTUC7_NSS   (uint32)16UL
#define MASK_FRGTUC7_CLEAR_PARAM (uint32)(MASK_FRGTUC7_SSL | MASK_FRGTUC7_NSS)

#define MASK_FRGTUC8_MSL        (uint32)0x3FUL
#define BIT_SHIFT_FRGTUC8_MSL   (uint32)0UL
#define MASK_FRGTUC8_NMS        (uint32)0x1FFF0000UL
#define BIT_SHIFT_FRGTUC8_NMS   (uint32)16UL
#define MASK_FRGTUC8_CLEAR_PARAM (uint32)(MASK_FRGTUC8_MSL | MASK_FRGTUC8_NMS)

#define MASK_FRGTUC9_APO        (uint32)0x3FUL
#define BIT_SHIFT_FRGTUC9_APO   (uint32)0UL
#define MASK_FRGTUC9_MAPO       (uint32)0x1F00UL
#define BIT_SHIFT_FRGTUC9_MAPO  (uint32)8UL
#define MASK_FRGTUC9_DSI        (uint32)0x30000UL
#define BIT_SHIFT_FRGTUC9_DSI   (uint32)16UL
#define MASK_FRGTUC9_CLEAR_PARAM (uint32)(MASK_FRGTUC9_APO | MASK_FRGTUC9_MAPO | MASK_FRGTUC9_DSI)

#define MASK_FRGTUC10_MOC       (uint32)0x3FFFUL
#define BIT_SHIFT_FRGTUC10_MOC  (uint32)0UL
#define MASK_FRGTUC10_MRC       (uint32)0x7FF0000UL
#define BIT_SHIFT_FRGTUC10_MRC  (uint32)16UL
#define MASK_FRGTUC10_CLEAR_PARAM (uint32)(MASK_FRGTUC10_MOC | MASK_FRGTUC10_MRC)

#define MASK_FRMRC_FDB          (uint32)0xFFUL
#define MASK_FRMRC_FFB          (uint32)0xFF00UL
#define BIT_SHIFT_FRMRC_FFB     (uint32)8UL
#define MASK_FRMRC_LCB          (uint32)0xFF0000UL
#define BIT_SHIFT_FRMRC_LCB     (uint32)16UL
#define SETUP_MAX_BUFFERS       (uint32)127UL

#define RAM_MESSAGE_BASE_ADDR   (uint32)0UL
#define RAM_MESSAGE_END_ADDR    (uint32)(2048*4)

#define MASK_FRWRHS1_FID        (uint32)0x07FFUL
#define BIT_SHIFT_FRWRHS1_FID   (uint32)0UL
#define MASK_FRWRHS1_CYC        (uint32)0x7F0000UL
#define BIT_SHIFT_FRWRHS1_CYC   (uint32)16UL
#define MASK_FRWRHS1_CH         (uint32)0x3000000UL
#define BIT_SHIFT_FRWRHS1_CH    (uint32)24UL
#define MASK_FRWRHS1_CFG        (uint32)0x40000000UL
#define BIT_SHIFT_FRWRHS1_CFG   (uint32)26UL
#define MASK_FRWRHS1_PPIT       (uint32)0x80000000UL
#define BIT_SHIFT_FRWRHS1_PPIT  (uint32)27UL
#define MASK_FRWRHS1_TXM        (uint32)0x100000000UL
#define BIT_SHIFT_FRWRHS1_TXM   (uint32)28UL
#define MASK_FRWRHS1_MBI        (uint32)0x100000000UL
#define BIT_SHIFT_FRWRHS1_MBI   (uint32)29UL

#define MASK_FRWRHS2_CRC        (uint32)0x07FFUL
#define BIT_SHIFT_FRWRHS1_CRC   (uint32)0UL
#define MASK_FRWRHS2_PLC        (uint32)0x7F0000UL
#define BIT_SHIFT_FRWRHS2_PLC   (uint32)16UL

#define MASK_FROC_OEP           (uint32)0x80UL
#define BIT_SHIFT_FROC_OEP      (uint32)8UL
#define MASK_FROC_OE            (uint32)0x01UL
#define MASK_FREIR_CCL          (uint32)0x20UL
#define MASK_FREIR_CNA          (uint32)0x02UL

#define ARC_NBR_CHI_CMD_RETRIES 100UL

#define MASK_FROS_OS            (uint32)0x01UL
#define MASK_FROS_T0IS          (uint32)0x10000UL
#define BIT_SHIFT_FROS_T0IS     (uint32)16UL
#define MASK_FROS_T2IS          (uint32)0x40000UL
#define BIT_SHIFT_FROS_T2IS     (uint32)18UL

#define MASK_FRCCEV_CCFC       (uint32)0x0FUL
#define BIT_SHIFT_FRCCEV_CCFC  (uint32)0UL
#define MASK_FRCCEV_ERRM       (uint32)0xC0UL
#define BIT_SHIFT_FRCCEV_ERRM  (uint32)6UL
#define FRCCEV_ERRM_RESERVED   (uint32)3UL
#define MASK_FRCCEV_PTAC       (uint32)0x1F00UL
#define BIT_SHIFT_FRCCEV_PTAC  (uint32)8UL
#define MASK_FRCCEV_ERRM_ACTIVE  (uint32)0x00UL
#define MASK_FRCCEV_ERRM_PASSIVE (uint32)0x40UL

#define MASK_FRCCSV_POCS       (uint32)0x3FUL
#define BIT_SHIFT_FRCCSV_POCS  (uint32)0UL
#define MASK_FRCCSV_FSI        (uint32)0x40UL
#define BIT_SHIFT_FRCCSV_FSI   (uint32)6UL
#define MASK_FRCCSV_HRQ        (uint32)0x80UL
#define BIT_SHIFT_FRCCSV_HRQ   (uint32)7UL
#define MASK_FRCCSV_SLM        (uint32)0x300UL
#define BIT_SHIFT_FRCCSV_SLM   (uint32)8UL
#define MASK_FRCCSV_CSNI       (uint32)0x1000UL
#define BIT_SHIFT_FRCCSV_CSNI  (uint32)12UL
#define MASK_FRCCSV_CSAI       (uint32)0x2000UL
#define BIT_SHIFT_FRCCSV_CSAI  (uint32)13UL
#define MASK_FRCCSV_CSI        (uint32)0x4000UL
#define BIT_SHIFT_FRCCSV_CSI   (uint32)14UL
#define MASK_FRCCSV_WSV        (uint32)0x70000UL
#define FRCCEV_WSV_RESERVED    (uint32)7UL
#define BIT_SHIFT_FRCCSV_WSV   (uint32)16UL
#define MASK_FRCCSV_RCA        (uint32)0xF80000UL
#define BIT_SHIFT_FRCCSV_RCA   (uint32)19UL

#define MASK_DEFAULT_CONFIG                 (uint32)0x00UL
#define MASK_READY                          (uint32)0x01UL
#define MASK_NORMAL_ACTIVE                  (uint32)0x02UL
#define MASK_NORMAL_PASSIVE                 (uint32)0x03UL
#define MASK_HALT                           (uint32)0x04UL
#define MASK_CONFIG                         (uint32)0x0FUL

//Indicates the actual of operation of the POC in the wakeup path
#define MASK_WAKEUP_BITS                    (uint32)0x1FUL
#define MASK_WAKEUP                         (uint32)0x10UL
#define MASK_WAKEUP_STANDBY                 (uint32)0x10UL
#define MASK_WAKEUP_LISTEN                  (uint32)0x11UL
#define MASK_WAKEUP_SEND                    (uint32)0x12UL
#define MASK_WAKEUP_DETECT                  (uint32)0x13UL

//Indicates the actual of operation of the POC in the startup path
#define MASK_STARTUP                        (uint32)0x20UL
#define MASK_STARTUP_BITS                   (uint32)0x2FUL
#define MASK_STARTUP_PREPARE                (uint32)0x20UL
#define MASK_COLDSTART_LISTEN               (uint32)0x21UL
#define MASK_COLDSTART_COLLISION_RESOLUTION (uint32)0x22UL
#define MASK_COLDSTART_CONSISTENCY_CHECK    (uint32)0x23UL
#define MASK_COLDSTART_GAP                  (uint32)0x24UL
#define MASK_COLDSTART_JOIN                 (uint32)0x25UL
#define MASK_INTEGRATION_COLDSTART_CHECK    (uint32)0x26UL
#define MASK_INTEGRATION_LISTEN             (uint32)0x27UL
#define MASK_INTEGRATION_CONSISTENCY_CHECK  (uint32)0x28UL
#define MASK_INITIALIZE_SCHEDULE            (uint32)0x29UL
#define MASK_ABORT_STARTUP                  (uint32)0x2AUL
#define MASK_STARTUP_SUCCESS                (uint32)0x2BUL

#define MASK_FRIBCM_LHSH    (uint32)0x01UL
#define MASK_FRIBCM_LDSH    (uint32)0x02UL
#define MASK_FRIBCM_STXRH   (uint32)0x04UL
#define MASK_FRIBCR_IBSYH   (uint32)0x8000UL

#define MASK_FROBCM_RHSS    (uint32)0x01UL
#define MASK_FROBCM_RDSS    (uint32)0x02UL

#define V_CRC_SIZE (uint32)11UL
#define V_CRC_POLYNOMIAL (uint32)0x385UL
#define V_CRC_INIT   (uint32)0x1AUL

#define BUFFER_START_IDX 0UL

#define MASK_FROBCR_OBRS    (uint32)0x7FUL
#define MASK_FROBCR_VIEW    (uint32)0x100UL
#define MASK_FROBCR_REQ     (uint32)0x200UL
#define MASK_FROBCR_OBSYS   (uint32)0x8000UL
#define MASK_FROBCR_CLEAR   (uint32)(MASK_FROBCR_OBRS | MASK_FROBCR_VIEW | MASK_FROBCR_REQ)

#define MASK_FRRDHS1_FID        (uint32)0x7FFUL
#define MASK_FRRDHS1_CYC        (uint32)0x7F0000UL
#define MASK_FRRDHS1_CH         (uint32)0x3000000UL
#define MASK_FRRDHS1_CFG        (uint32)0x4000000UL
#define MASK_FRRDHS1_PPIT       (uint32)0x8000000UL
#define MASK_FRRDHS1_TXM        (uint32)0x10000000UL
#define MASK_FRRDHS1_MBI        (uint32)0x20000000UL

#define BIT_SHIFT_FRRDHS1_FID    (uint32)0UL
#define BIT_SHIFT_FRRDHS1_CYC    (uint32)16UL
#define BIT_SHIFT_FRRDHS1_CH     (uint32)24UL
#define BIT_SHIFT_FRRDHS1_CFG    (uint32)26UL
#define BIT_SHIFT_FRRDHS1_PPIT   (uint32)27UL
#define BIT_SHIFT_FRRDHS1_TXM    (uint32)28UL
#define BIT_SHIFT_FRRDHS1_MBI    (uint32)29UL

#define MASK_FRRDHS2_PLC        (uint32)0x7F0000UL
#define BIT_SHIFT_FRRDHS2_PLC   (uint32)16UL
#define MASK_FRRDHS2_PLR        (uint32)0x7F000000UL
#define BIT_SHIFT_FRRDHS2_PLR   (uint32)24UL

#define FR_LENGTH_DIV           2UL

#define MASK_FRMBS_RESS             (uint32)0x20000000UL
#define MASK_FRMBS_PPIS             (uint32)0x10000000UL
#define MASK_FRMBS_NFIS             (uint32)0x8000000UL
#define MASK_FRMBS_SYNS             (uint32)0x4000000UL
#define MASK_FRMBS_SFIS             (uint32)0x2000000UL
#define MASK_FRMBS_RCIS             (uint32)0x1000000UL
#define MASK_FRMBS_CCS              (uint32)0x3F0000UL
#define MASK_FRMBS_FTB              (uint32)0x8000UL
#define MASK_FRMBS_FTA              (uint32)0x4000UL
#define MASK_FRMBS_MLST             (uint32)0x1000UL
#define MASK_FRMBS_ESB              (uint32)0x800UL
#define MASK_FRMBS_ESA              (uint32)0x400UL
#define MASK_FRMBS_TCIB             (uint32)0x200UL
#define MASK_FRMBS_TCIA             (uint32)0x100UL
#define MASK_FRMBS_SVOB             (uint32)0x80UL
#define MASK_FRMBS_SVOA             (uint32)0x40UL
#define MASK_FRMBS_CEOB             (uint32)0x20UL
#define MASK_FRMBS_CEOA             (uint32)0x10UL
#define MASK_FRMBS_SEOB             (uint32)0x08UL
#define MASK_FRMBS_SEOA             (uint32)0x04UL
#define MASK_FRMBS_VFRB             (uint32)0x02UL
#define MASK_FRMBS_VFRA             (uint32)0x01UL

#define BIT_SHIFT_FRMBS_RESS        (uint32)29UL
#define BIT_SHIFT_FRMBS_PPIS        (uint32)28UL
#define BIT_SHIFT_FRMBS_NFIS        (uint32)27UL
#define BIT_SHIFT_FRMBS_SYNS        (uint32)26UL
#define BIT_SHIFT_FRMBS_SFIS        (uint32)25UL
#define BIT_SHIFT_FRMBS_RCIS        (uint32)24UL
#define BIT_SHIFT_FRMBS_CCS         (uint32)21UL
#define BIT_SHIFT_FRMBS_FTB         (uint32)15UL
#define BIT_SHIFT_FRMBS_FTA         (uint32)14UL
#define BIT_SHIFT_FRMBS_MLST        (uint32)12UL
#define BIT_SHIFT_FRMBS_ESB         (uint32)11UL
#define BIT_SHIFT_FRMBS_ESA         (uint32)10UL
#define BIT_SHIFT_FRMBS_TCIB        (uint32)9UL
#define BIT_SHIFT_FRMBS_TCIA        (uint32)8UL
#define BIT_SHIFT_FRMBS_SVOB        (uint32)7UL
#define BIT_SHIFT_FRMBS_SVOA        (uint32)6UL
#define BIT_SHIFT_FRMBS_CEOB        (uint32)5UL
#define BIT_SHIFT_FRMBS_CEOA        (uint32)4UL
#define BIT_SHIFT_FRMBS_SEOB        (uint32)3UL
#define BIT_SHIFT_FRMBS_SEOA        (uint32)2UL
#define BIT_SHIFT_FRMBS_VFRB        (uint32)1UL
#define BIT_SHIFT_FRMBS_VFRA        (uint32)0UL

#define MASK_FRSFS_STATUS_FLAGS (uint32)0xF0000UL
#define MASK_FRSFS_VSBO         (uint32)0xF000UL
#define BIT_SHIFT_FRSFS_VSBO    (uint32)12UL
#define MASK_FRSFS_VSBE         (uint32)0xF00UL
#define BIT_SHIFT_FRSFS_VSBE    (uint32)8UL
#define MASK_FRSFS_VSAO         (uint32)0xF0UL
#define BIT_SHIFT_FRSFS_VSAO    (uint32)4UL
#define MASK_FRSFS_VSAE         (uint32)0xFUL
#define BIT_SHIFT_FRSFS_VSAE    (uint32)0UL

#define MASK_FRMTCCV_MTV        (uint32)0x3FFFUL
#define BIT_SHIFT_FRMTCCV_MTV   (uint32)0UL
#define MASK_FRMTCCV_CCV        (uint32)0x3F0000UL
#define BIT_SHIFT_FRMTCCV_CCV   (uint32)16UL

#define BIT_SHIFT_FRTXC_TXMO    (uint32)16UL
#define BIT_SHIFT_FRTXC_TXCC    (uint32)8UL
#define BIT_SHIFT_FRTXC_TXMS    (uint32)1UL
#define BIT_SHIFT_FRTXC_TXRC    (uint32)0UL

#define MASK_ABS_TIMER_MODE_CONTINUOUS   (uint32)1UL
#define MASK_ABS_TIMER_CTRL_ACTIVE       (uint32)1UL

#define MAX_WAIT_CYCLES (uint32)10000UL

#define MASK_FREIR_FIFO_ERR (uint32)0x180UL
#define MASK_FREIR_CHN_A    (uint32)0x70000UL
#define MASK_FREIR_CHN_B    (uint32)0x7000000UL

#ifndef DEM_EVENT_ID_NULL
#define DEM_EVENT_ID_NULL    0u
#endif
/* ----------------------------[private macro]-------------------------------*/
#if defined(USE_DEM) || defined(CFG_FR_DEM_TEST)
#define DEM_REPORT(_eventId, _status) Fr_Internal_reportDem((_eventId), (_status))
#else
#define DEM_REPORT(_eventId, _status)
#endif
/* ----------------------------[private typedef]-----------------------------*/
typedef enum {
    HEADER = 0,
    HEADER_AND_DATA,
    DATA,
}MsgRAMReadoutType;
/* ----------------------------[private function prototypes]-----------------*/
static Std_ReturnType findTrigIdx(const Fr_FrIfCCTriggeringType *FrTrigConf, uint32 searchedId, uint32 *trigIdx);
static Std_ReturnType setupMessageBuffer(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint32 frameTrigIdx, uint32 *dataAddr);
static Std_ReturnType writeHeader(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint32 frameTrigIdx);
static uint32 getHeaderCrc(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint32 frameTrigIdx, uint32 dynLen);
static Std_ReturnType waitWhileBusy(volatile const uint32 *regBaseAddr, uint32 mask, boolean retCondition);
static Std_ReturnType readOutMessageRamBuffer(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint16 msgBufferIdx, MsgRAMReadoutType readType);
/* ----------------------------[private variables]---------------------------*/
static uint16 bufferindex = BUFFER_START_IDX;
/* ----------------------------[functions]---------------------------*/


/**
 * Disable Tx
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @return
 */
Std_ReturnType Fr_Internal_ClearPendingTx(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx) {
    Std_ReturnType retval;
    //Output transfer operation disable request
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROTC &= ~MASK_FROTC_OTE;

    //Wait for ongoing transmissions to finish
    retval = waitWhileBusy(&Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROTS, MASK_FROTS_OTS, FALSE);

    return retval;
}

/**
 * Disable Rx
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @return
 */
Std_ReturnType Fr_Internal_ClearPendingRx(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx) {
    Std_ReturnType retval;

    //Input queue halt request
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRITC |= MASK_FRITC_IQHR;

    //Operation Disable request
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRITC &= ~MASK_FRITC_ITE;

    //Wait for controller to finish sending off the remaining queue before it enters disabled state.
    retval = waitWhileBusy(&Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRITS, MASK_FRITS_ITS, FALSE);

    return retval;
}


/**
 * Compares the parameters written to register to those defined in the config.
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @return
 */
Std_ReturnType Fr_Internal_RunCCTest(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx) {
    const Fr_FrIfClusterConfigType *clusterParamPtr = &Fr_Cfg->Fr_ConfigPtr->FrClusterConfig[Fr_CtrlIdx];
    const Fr_CtrlConfigParametersType *paramPtr = &Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx];
    const volatile struct FLXA_reg *hwPtr = Fr_Cfg->hwPtr[Fr_CtrlIdx];
    Fr_CtrlConfigParametersType rCfgParam = {0};
    Fr_FrIfClusterConfigType rClstParam = {0};
    Std_ReturnType retval;

    uint32 errCnt = 0;
    uint32 frsucc1  = hwPtr->FRSUCC1;
    uint32 frsucc2  = hwPtr->FRSUCC2;
    uint32 frsucc3  = hwPtr->FRSUCC3;
    uint32 frprtc1  = hwPtr->FRPRTC1;
    uint32 frprtc2  = hwPtr->FRPRTC2;
    uint32 frmhdc   = hwPtr->FRMHDC;
    uint32 frgtuc1  = hwPtr->FRGTUC1;
    uint32 frgtuc2  = hwPtr->FRGTUC2;
    uint32 frgtuc3  = hwPtr->FRGTUC3;
    uint32 frgtuc4  = hwPtr->FRGTUC4;
    uint32 frgtuc5  = hwPtr->FRGTUC5;
    uint32 frgtuc6  = hwPtr->FRGTUC6;
    uint32 frgtuc7  = hwPtr->FRGTUC7;
    uint32 frgtuc8  = hwPtr->FRGTUC8;
    uint32 frgtuc9  = hwPtr->FRGTUC9;
    uint32 frgtuc10 = hwPtr->FRGTUC10;
    uint32 frnemc   = hwPtr->FRNEMC;
    uint32 frpChnl;
    uint32 brp;

    //Read parameters in register FRSUCC1
    rCfgParam.FrPKeySlotUsedForStartup = (((frsucc1 & MASK_FRSUCC1_TXST) >> BIT_SHIFT_FRSUCC1_TXST) > 0) ? TRUE : FALSE;
    rCfgParam.FrPKeySlotUsedForSync = (((frsucc1 & MASK_FRSUCC1_TXSY) >> BIT_SHIFT_FRSUCC1_TXSY) > 0) ? TRUE : FALSE;
    rCfgParam.FrPAllowPassiveToActive = (frsucc1 & MASK_FRSUCC1_PTA) >> BIT_SHIFT_FRSUCC1_PTA;
    if (((frsucc1 & MASK_FRSUCC1_WUCS) >> BIT_SHIFT_FRSUCC1_WUCS) > 0) {
        rCfgParam.FrPWakeupChannel = FR_CHANNEL_B;
    } else {
        rCfgParam.FrPWakeupChannel = FR_CHANNEL_A;
    }
    rCfgParam.FrPKeySlotOnlyEnabled = (((frsucc1 & MASK_FRSUCC1_TSM) >> BIT_SHIFT_FRSUCC1_TSM) > 0) ? TRUE : FALSE;
    rCfgParam.FrPAllowHaltDueToClock = (((frsucc1 & MASK_FRSUCC1_HCSE) >> BIT_SHIFT_FRSUCC1_HCSE) > 0) ? TRUE : FALSE;
    frpChnl = (frsucc1 & MASK_FRSUCC1_CCH) >> BIT_SHIFT_FRSUCC1_CCH;
    if (frpChnl  == 1) {
        rCfgParam.FrPChannels = FR_CHANNEL_A;
    } else if (frpChnl == 2) {
        rCfgParam.FrPChannels = FR_CHANNEL_B;
    } else if (frpChnl == 3) {
        rCfgParam.FrPChannels = FR_CHANNEL_AB;
    } else {
        errCnt++;
    }
    rClstParam.FrClusterGColdStartAttempts = (frsucc1 & MASK_FRSUCC1_CSA) >> BIT_SHIFT_FRSUCC1_CSA;

    //Check parameters in register FRSUCC1
    errCnt += (paramPtr->FrPKeySlotUsedForStartup != rCfgParam.FrPKeySlotUsedForStartup) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPKeySlotUsedForSync != rCfgParam.FrPKeySlotUsedForSync) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPAllowPassiveToActive != rCfgParam.FrPAllowPassiveToActive) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPWakeupChannel != rCfgParam.FrPWakeupChannel) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPKeySlotOnlyEnabled != rCfgParam.FrPKeySlotOnlyEnabled) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPAllowHaltDueToClock != rCfgParam.FrPAllowHaltDueToClock) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPChannels != rCfgParam.FrPChannels) ? (uint32)1 : (uint32)0;
    errCnt += (clusterParamPtr->FrClusterGColdStartAttempts != rClstParam.FrClusterGColdStartAttempts) ? (uint32)1 : (uint32)0;

    //Read parameters in register FRSUCC2
    rCfgParam.FrPdListenTimeout = frsucc2 & MASK_FRSUCC2_LT;
    rClstParam.FrClusterGListenNoise = (frsucc2 & MASK_FRSUCC2_LTN) >> BIT_SHIFT_FRSUCC2_LTN;

    //Check parameters in register FRSUCC2
    errCnt += (paramPtr->FrPdListenTimeout != rCfgParam.FrPdListenTimeout) ? (uint32)1 : (uint32)0;
    errCnt += (clusterParamPtr->FrClusterGListenNoise != rClstParam.FrClusterGListenNoise) ? (uint32)1 : (uint32)0;

    //Read parameters in register FRSUCC3
    rClstParam.FrClusterGMaxWithoutClockCorrectPassive = frsucc3 & MASK_FRSUCC3_WCP;
    rClstParam.FrClusterGMaxWithoutClockCorrectFatal = (frsucc3 & MASK_FRSUCC3_WCF) >> BIT_SHIFT_FRSUCC3_WCF;

    //Check parameters in register FRSUCC3
    errCnt += (clusterParamPtr->FrClusterGMaxWithoutClockCorrectPassive != rClstParam.FrClusterGMaxWithoutClockCorrectPassive) ? (uint32)1 : (uint32)0;
    errCnt += (clusterParamPtr->FrClusterGMaxWithoutClockCorrectFatal != rClstParam.FrClusterGMaxWithoutClockCorrectFatal) ? (uint32)1 : (uint32)0;

    //Read parameters in register FRPRTC1
    rClstParam.FrClusterGdTSSTransmitter = frprtc1 & MASK_FRPRTC1_TSST;
    rCfgParam.FrPWakeupPattern = (frprtc1 & MASK_FRPRTC1_RWP) >> BIT_SHIFT_FRPRTC1_RWP;
    rClstParam.FrClusterGdCasRxLowMax = (frprtc1 & MASK_FRPRTC1_CASM) >> BIT_SHIFT_FRPRTC1_CASM;
    rClstParam.FrClusterGdWakeupRxWindow = (frprtc1 & MASK_FRPRTC1_RXW) >> BIT_SHIFT_FRPRTC1_RXW;
    brp = (frprtc1 & MASK_FRPRTC1_BRP) >> BIT_SHIFT_FRPRTC1_BRP;

    if (brp == 1) {
        rClstParam.FrClusterGdSampleClockPeriod = FR_T25NS;
    } else if (brp == 2) {
        rClstParam.FrClusterGdSampleClockPeriod = FR_T50NS;
    } else {
        rClstParam.FrClusterGdSampleClockPeriod = FR_T12_5NS;
    }

    //Check parameters in register FRPRTC1
    errCnt += (clusterParamPtr->FrClusterGdTSSTransmitter != rClstParam.FrClusterGdTSSTransmitter) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPWakeupPattern != rCfgParam.FrPWakeupPattern) ? (uint32)1 : (uint32)0;
    errCnt += (clusterParamPtr->FrClusterGdCasRxLowMax != rClstParam.FrClusterGdCasRxLowMax) ? (uint32)1 : (uint32)0;
    errCnt += (clusterParamPtr->FrClusterGdWakeupRxWindow != rClstParam.FrClusterGdWakeupRxWindow) ? (uint32)1 : (uint32)0;
    errCnt += (clusterParamPtr->FrClusterGdSampleClockPeriod != rClstParam.FrClusterGdSampleClockPeriod) ? (uint32)1 : (uint32)0;

    //Read parameters in register FRPRTC2
    rClstParam.FrClusterGdWakeupRxIdle = frprtc2 & MASK_FRPRTC2_RXI;
    rClstParam.FrClusterGdWakeupRxLow = (frprtc2 & MASK_FRPRTC2_RXL) >> BIT_SHIFT_FRPRTC2_RXL;
    rClstParam.FrClusterGdWakeupTxIdle = (frprtc2 & MASK_FRPRTC2_TXI) >> BIT_SHIFT_FRPRTC2_TXI;
    rClstParam.FrClusterGdWakeupTxActive = (frprtc2 & MASK_FRPRTC2_TXL) >> BIT_SHIFT_FRPRTC2_TXL;

    //Check parameters in register FRPRTC2
    errCnt += (clusterParamPtr->FrClusterGdWakeupRxIdle != rClstParam.FrClusterGdWakeupRxIdle) ? (uint32)1 : (uint32)0;
    errCnt += (clusterParamPtr->FrClusterGdWakeupRxLow != rClstParam.FrClusterGdWakeupRxLow) ? (uint32)1 : (uint32)0;
    errCnt += (clusterParamPtr->FrClusterGdWakeupTxIdle != rClstParam.FrClusterGdWakeupTxIdle) ? (uint32)1 : (uint32)0;
    errCnt += (clusterParamPtr->FrClusterGdWakeupTxActive != rClstParam.FrClusterGdWakeupTxActive) ? (uint32)1 : (uint32)0;

    //Read parameters in register FRMHDC
    rClstParam.FrClusterGPayloadLengthStatic = frmhdc & MASK_FRMHDC_SFDL;
    rCfgParam.FrPLatestTx = (frmhdc & MASK_FRMHDC_SLT) >> BIT_SHIFT_FRMHDC_SLT;

    //Check parameters in register FRMHDC
    errCnt += (clusterParamPtr->FrClusterGPayloadLengthStatic != rClstParam.FrClusterGPayloadLengthStatic) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPLatestTx != rCfgParam.FrPLatestTx) ? (uint32)1 : (uint32)0;

    //Read parameters in register FRGTUC1
    rCfgParam.FrPMicroPerCycle = frgtuc1 & MASK_FRGTUC1_UT;

    //Check parameters in register FRGTUC1
    errCnt += (paramPtr->FrPMicroPerCycle != rCfgParam.FrPMicroPerCycle) ? (uint32)1 : (uint32)0;

    //Read parameters in register FRGTUC2
    rClstParam.FrClusterGMacroPerCycle = frgtuc2 & MASK_FRGTUC2_MPC;
    rClstParam.FrClusterGSyncFrameIDCountMax = (frgtuc2 & MASK_FRGTUC2_SNM) >> BIT_SHIFT_FRGTUC2_SNM;

    //Check parameters in register FRGTUC2
    errCnt += (clusterParamPtr->FrClusterGMacroPerCycle != rClstParam.FrClusterGMacroPerCycle) ? (uint32)1 : (uint32)0;
    errCnt += (clusterParamPtr->FrClusterGSyncFrameIDCountMax != rClstParam.FrClusterGSyncFrameIDCountMax) ? (uint32)1 : (uint32)0;

    //Read parameters in register FRGTUC3
    rCfgParam.FrPMicroInitialOffsetA = frgtuc3 & MASK_FRGTUC3_UIOA;
    rCfgParam.FrPMicroInitialOffsetB = (frgtuc3 & MASK_FRGTUC3_UIOB) >> BIT_SHIFT_FRGTUC3_UIOB;
    rCfgParam.FrPMacroInitialOffsetA = (frgtuc3 & MASK_FRGTUC3_MIOA) >> BIT_SHIFT_FRGTUC3_MIOA;
    rCfgParam.FrPMacroInitialOffsetB = (frgtuc3 & MASK_FRGTUC3_MIOB) >> BIT_SHIFT_FRGTUC3_MIOB;

    //Check parameters in register FRGTUC3
    errCnt += (paramPtr->FrPMicroInitialOffsetA != rCfgParam.FrPMicroInitialOffsetA) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPMicroInitialOffsetB != rCfgParam.FrPMicroInitialOffsetB) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPMacroInitialOffsetA != rCfgParam.FrPMacroInitialOffsetA) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPMacroInitialOffsetB != rCfgParam.FrPMacroInitialOffsetB) ? (uint32)1 : (uint32)0;

    //Read parameters in register FRGTUC4
    rClstParam.FrClusterGMacroPerCycle = (frgtuc4 & MASK_FRGTUC4_NIT) + clusterParamPtr->FrClusterGdNit + (uint32)1;
    rCfgParam.FrPOffsetCorrectionStart = ((frgtuc4 & MASK_FRGTUC4_OCS) >> BIT_SHIFT_FRGTUC4_OCS) + (uint32)1;

    //Check parameters in register FRGTUC4
    errCnt += (clusterParamPtr->FrClusterGMacroPerCycle != rClstParam.FrClusterGMacroPerCycle) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPOffsetCorrectionStart != rCfgParam.FrPOffsetCorrectionStart) ? (uint32)1 : (uint32)0;

    //Read parameters in register FRGTUC5
    rCfgParam.FrPDelayCompensationA = frgtuc5 & MASK_FRGTUC5_DCA;
    rCfgParam.FrPDelayCompensationB = (frgtuc5 & MASK_FRGTUC5_DCB) >> BIT_SHIFT_FRGTUC5_DCB;
    rCfgParam.FrPClusterDriftDamping = (frgtuc5 & MASK_FRGTUC5_CDD) >> BIT_SHIFT_FRGTUC5_CDD;
    rCfgParam.FrPDecodingCorrection = (frgtuc5 & MASK_FRGTUC5_DEC) >> BIT_SHIFT_FRGTUC5_DEC;

    //Check parameters in register FRGTUC5
    errCnt += (paramPtr->FrPDelayCompensationA != rCfgParam.FrPDelayCompensationA) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPDelayCompensationB != rCfgParam.FrPDelayCompensationB) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPClusterDriftDamping != rCfgParam.FrPClusterDriftDamping) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPDecodingCorrection != rCfgParam.FrPDecodingCorrection) ? (uint32)1 : (uint32)0;

    //Read parameters in register FRGTUC6
    rCfgParam.FrPdAcceptedStartupRange = frgtuc6 & MASK_FRGTUC6_ASR;
    rCfgParam.FrPRateCorrectionOut = (frgtuc6 & MASK_FRGTUC6_MOD) >> BIT_SHIFT_FRGTUC6_MOD;

    //Read parameters in register FRGTUC6
    errCnt += (paramPtr->FrPdAcceptedStartupRange != rCfgParam.FrPdAcceptedStartupRange) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPRateCorrectionOut != rCfgParam.FrPRateCorrectionOut) ? (uint32)1 : (uint32)0;

    //Read parameters in register FRGTUC7
    rClstParam.FrClusterGdStaticSlot = frgtuc7 & MASK_FRGTUC7_SSL;
    rClstParam.FrClusterGNumberOfStaticSlots = (frgtuc7 & MASK_FRGTUC7_NSS) >> BIT_SHIFT_FRGTUC7_NSS;

    //Check parameters in register FRGTUC7
    errCnt += (clusterParamPtr->FrClusterGdStaticSlot != rClstParam.FrClusterGdStaticSlot) ? (uint32)1 : (uint32)0;
    errCnt += (clusterParamPtr->FrClusterGNumberOfStaticSlots != rClstParam.FrClusterGNumberOfStaticSlots) ? (uint32)1 : (uint32)0;

    //Read parameters in register FRGTUC8
    rClstParam.FrClusterGdMinislot = frgtuc8 & MASK_FRGTUC8_MSL;
    rClstParam.FrClusterGNumberOfMinislots = (frgtuc8 & MASK_FRGTUC8_NMS) >> BIT_SHIFT_FRGTUC8_NMS;

    //Check parameters in register FRGTUC8
    errCnt += (clusterParamPtr->FrClusterGdMinislot != rClstParam.FrClusterGdMinislot) ? (uint32)1 : (uint32)0;
    errCnt += (clusterParamPtr->FrClusterGNumberOfMinislots != rClstParam.FrClusterGNumberOfMinislots) ? (uint32)1 : (uint32)0;

    //Read parameters in register FRGTUC9
    rClstParam.FrClusterGdActionPointOffset = frgtuc9 & MASK_FRGTUC9_APO;
    rClstParam.FrClusterGdMiniSlotActionPointOffset = (frgtuc9 & MASK_FRGTUC9_MAPO) >> BIT_SHIFT_FRGTUC9_MAPO;
    rClstParam.FrClusterGdDynamicSlotIdlePhase = (frgtuc9 & MASK_FRGTUC9_DSI) >> BIT_SHIFT_FRGTUC9_DSI;

    //Check parameters in register FRGTUC9
    errCnt += (clusterParamPtr->FrClusterGdActionPointOffset != rClstParam.FrClusterGdActionPointOffset) ? (uint32)1 : (uint32)0;
    errCnt += (clusterParamPtr->FrClusterGdMiniSlotActionPointOffset != rClstParam.FrClusterGdMiniSlotActionPointOffset) ? (uint32)1 : (uint32)0;
    errCnt += (clusterParamPtr->FrClusterGdDynamicSlotIdlePhase != rClstParam.FrClusterGdDynamicSlotIdlePhase) ? (uint32)1 : (uint32)0;

    //Read parameters in register FRGTUC10
    rCfgParam.FrPOffsetCorrectionOut = frgtuc10 & MASK_FRGTUC10_MOC;
    rCfgParam.FrPRateCorrectionOut = (frgtuc10 & MASK_FRGTUC10_MRC) >> BIT_SHIFT_FRGTUC10_MRC;

    //Check parameters in register FRGTUC10
    errCnt += (paramPtr->FrPOffsetCorrectionOut != rCfgParam.FrPOffsetCorrectionOut) ? (uint32)1 : (uint32)0;
    errCnt += (paramPtr->FrPRateCorrectionOut != rCfgParam.FrPRateCorrectionOut) ? (uint32)1 : (uint32)0;

    //Read parameters in register FRNEMC
    rClstParam.FrClusterGNetworkManagementVectorLength = frnemc;

    //Check parameters in register FRNEMC
    errCnt += (clusterParamPtr->FrClusterGNetworkManagementVectorLength != rClstParam.FrClusterGNetworkManagementVectorLength) ? (uint32)1 : (uint32)0;


    if (errCnt > 0) {
        retval = E_NOT_OK;
    } else {
        retval = E_OK;
    }

    return retval;
}


/**
 * Setup the Flexray CC registers
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 */
Std_ReturnType Fr_Internal_SetupCC(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx) {
    volatile struct FLXA_reg *hwPtr = Fr_Cfg->hwPtr[Fr_CtrlIdx];
    const Fr_CtrlConfigParametersType *paramPtr = &Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx];
    const Fr_FrIfClusterConfigType *clusterParamPtr = &Fr_Cfg->Fr_ConfigPtr->FrClusterConfig[Fr_CtrlIdx];

    uint32 frsucc1  = hwPtr->FRSUCC1;
    uint32 frsucc2  = hwPtr->FRSUCC2;
    uint32 frsucc3  = hwPtr->FRSUCC3;
    uint32 frprtc1  = hwPtr->FRPRTC1;
    uint32 frprtc2  = hwPtr->FRPRTC2;
    uint32 frmhdc   = hwPtr->FRMHDC;
    uint32 frgtuc1  = hwPtr->FRGTUC1;
    uint32 frgtuc2  = hwPtr->FRGTUC2;
    uint32 frgtuc3  = hwPtr->FRGTUC3;
    uint32 frgtuc4  = hwPtr->FRGTUC4;
    uint32 frgtuc5  = hwPtr->FRGTUC5;
    uint32 frgtuc6  = hwPtr->FRGTUC6;
    uint32 frgtuc7  = hwPtr->FRGTUC7;
    uint32 frgtuc8  = hwPtr->FRGTUC8;
    uint32 frgtuc9  = hwPtr->FRGTUC9;
    uint32 frgtuc10 = hwPtr->FRGTUC10;
    uint32 frnemc   = hwPtr->FRNEMC;
    uint32 brp;

    frsucc1 &= ~MASK_FRSUCC1_CLEAR_PARAM;
    frsucc1 |= ((paramPtr->FrPKeySlotUsedForStartup)    ?(uint32)1:(uint32)0)   << BIT_SHIFT_FRSUCC1_TXST;
    frsucc1 |= ((paramPtr->FrPKeySlotUsedForSync)       ?(uint32)1:(uint32)0)   << BIT_SHIFT_FRSUCC1_TXSY;
    frsucc1 |= ((paramPtr->FrPAllowPassiveToActive > 0) ?(uint32)1:(uint32)0)   << BIT_SHIFT_FRSUCC1_PTA;
    frsucc1 |= (uint32)paramPtr->FrPWakeupChannel                               << BIT_SHIFT_FRSUCC1_WUCS;
    frsucc1 |= ((paramPtr->FrPKeySlotOnlyEnabled)       ?(uint32)1:(uint32)0)   << BIT_SHIFT_FRSUCC1_TSM;
    frsucc1 |= ((paramPtr->FrPAllowHaltDueToClock)      ?(uint32)1:(uint32)0)   << BIT_SHIFT_FRSUCC1_HCSE;
    frsucc1 |= ((uint32)paramPtr->FrPChannels + (uint32)1)                      << BIT_SHIFT_FRSUCC1_CCH;
    frsucc1 |= clusterParamPtr->FrClusterGColdStartAttempts                     << BIT_SHIFT_FRSUCC1_CSA;
    hwPtr->FRSUCC1 = frsucc1;

    frsucc2 &= ~MASK_FRSUCC2_CLEAR_PARAM;
    frsucc2 |= paramPtr->FrPdListenTimeout;
    frsucc2 |= clusterParamPtr->FrClusterGListenNoise << BIT_SHIFT_FRSUCC2_LTN;
    hwPtr->FRSUCC2 = frsucc2;

    frsucc3 &= ~MASK_FRSUCC3_CLEAR_PARAM;
    frsucc3 |= clusterParamPtr->FrClusterGMaxWithoutClockCorrectPassive;
    frsucc3 |= clusterParamPtr->FrClusterGMaxWithoutClockCorrectFatal   << BIT_SHIFT_FRSUCC3_WCF;
    hwPtr->FRSUCC3 = frsucc3;

    if (clusterParamPtr->FrClusterGdSampleClockPeriod == FR_T25NS) {
        brp = 1;
    } else if (clusterParamPtr->FrClusterGdSampleClockPeriod == FR_T50NS) {
        brp = 2;
    } else {
        brp = 0;
    }

    frprtc1 &= ~MASK_FRPRTC1_CLEAR_PARAM;
    frprtc1 |= clusterParamPtr->FrClusterGdTSSTransmitter;
    frprtc1 |= paramPtr->FrPWakeupPattern                 << BIT_SHIFT_FRPRTC1_RWP;
    frprtc1 |= clusterParamPtr->FrClusterGdCasRxLowMax    << BIT_SHIFT_FRPRTC1_CASM;
    frprtc1 |= brp                                        << BIT_SHIFT_FRPRTC1_BRP;
    frprtc1 |= clusterParamPtr->FrClusterGdWakeupRxWindow << BIT_SHIFT_FRPRTC1_RXW;
    hwPtr->FRPRTC1 = frprtc1;

    frprtc2 &= ~MASK_FRPRTC2_CLEAR_PARAM;
    frprtc2 |= clusterParamPtr->FrClusterGdWakeupRxIdle;
    frprtc2 |= clusterParamPtr->FrClusterGdWakeupRxLow    << BIT_SHIFT_FRPRTC2_RXL;
    frprtc2 |= clusterParamPtr->FrClusterGdWakeupTxIdle   << BIT_SHIFT_FRPRTC2_TXI;
    frprtc2 |= clusterParamPtr->FrClusterGdWakeupTxActive << BIT_SHIFT_FRPRTC2_TXL;
    hwPtr->FRPRTC2 = frprtc2;

    frmhdc &= ~MASK_FRMHDC_CLEAR_PARAM;
    frmhdc |= clusterParamPtr->FrClusterGPayloadLengthStatic;
    frmhdc |= paramPtr->FrPLatestTx << BIT_SHIFT_FRMHDC_SLT;
    hwPtr->FRMHDC = frmhdc;

    frgtuc1 &= ~MASK_FRGTUC1_CLEAR_PARAM;
    frgtuc1 |= paramPtr->FrPMicroPerCycle;
    hwPtr->FRGTUC1 = frgtuc1;

    frgtuc2 &= ~MASK_FRGTUC2_CLEAR_PARAM;
    frgtuc2 |= clusterParamPtr->FrClusterGMacroPerCycle;
    frgtuc2 |= clusterParamPtr->FrClusterGSyncFrameIDCountMax << BIT_SHIFT_FRGTUC2_SNM;
    hwPtr->FRGTUC2 = frgtuc2;

    frgtuc3 &= ~MASK_FRGTUC3_CLEAR_PARAM;
    frgtuc3 |= paramPtr->FrPMicroInitialOffsetA;
    frgtuc3 |= paramPtr->FrPMicroInitialOffsetB << BIT_SHIFT_FRGTUC3_UIOB;
    frgtuc3 |= paramPtr->FrPMacroInitialOffsetA << BIT_SHIFT_FRGTUC3_MIOA;
    frgtuc3 |= paramPtr->FrPMacroInitialOffsetB << BIT_SHIFT_FRGTUC3_MIOB;
    hwPtr->FRGTUC3 = frgtuc3;

    frgtuc4 &= ~MASK_FRGTUC4_CLEAR_PARAM;
    frgtuc4 |= (paramPtr->FrPOffsetCorrectionStart - (uint32)1) << BIT_SHIFT_FRGTUC4_OCS;
    frgtuc4 |= ((clusterParamPtr->FrClusterGMacroPerCycle - clusterParamPtr->FrClusterGdNit) - (uint32)1);
    hwPtr->FRGTUC4 = frgtuc4;

    frgtuc5 &= ~MASK_FRGTUC5_CLEAR_PARAM;
    frgtuc5 |= paramPtr->FrPDelayCompensationA;
    frgtuc5 |= paramPtr->FrPDelayCompensationB  << BIT_SHIFT_FRGTUC5_DCB;
    frgtuc5 |= paramPtr->FrPClusterDriftDamping << BIT_SHIFT_FRGTUC5_CDD;
    frgtuc5 |= paramPtr->FrPDecodingCorrection  << BIT_SHIFT_FRGTUC5_DEC;
    hwPtr->FRGTUC5 = frgtuc5;

    frgtuc6 &= ~MASK_FRGTUC6_CLEAR_PARAM;
    frgtuc6 |= paramPtr->FrPdAcceptedStartupRange;
    frgtuc6 |= paramPtr->FrPRateCorrectionOut     << BIT_SHIFT_FRGTUC6_MOD;
    hwPtr->FRGTUC6 = frgtuc6;

    frgtuc7 &= ~MASK_FRGTUC7_CLEAR_PARAM;
    frgtuc7 |= clusterParamPtr->FrClusterGdStaticSlot;
    frgtuc7 |= clusterParamPtr->FrClusterGNumberOfStaticSlots << BIT_SHIFT_FRGTUC7_NSS;
    hwPtr->FRGTUC7 = frgtuc7;

    frgtuc8 &= ~MASK_FRGTUC8_CLEAR_PARAM;
    frgtuc8 |= clusterParamPtr->FrClusterGdMinislot;
    frgtuc8 |= clusterParamPtr->FrClusterGNumberOfMinislots << BIT_SHIFT_FRGTUC8_NMS;
    hwPtr->FRGTUC8 = frgtuc8;

    frgtuc9 &= ~MASK_FRGTUC9_CLEAR_PARAM;
    frgtuc9 |= clusterParamPtr->FrClusterGdActionPointOffset;
    frgtuc9 |= clusterParamPtr->FrClusterGdMiniSlotActionPointOffset << BIT_SHIFT_FRGTUC9_MAPO;
    frgtuc9 |= clusterParamPtr->FrClusterGdDynamicSlotIdlePhase      << BIT_SHIFT_FRGTUC9_DSI;
    hwPtr->FRGTUC9 = frgtuc9;

    frgtuc10 &= ~MASK_FRGTUC10_CLEAR_PARAM;
    frgtuc10 |= paramPtr->FrPOffsetCorrectionOut;
    frgtuc10 |= paramPtr->FrPRateCorrectionOut   << BIT_SHIFT_FRGTUC10_MRC;
    hwPtr->FRGTUC10 = frgtuc10;

    frnemc &= ~MASK_FRNEMC_CLEAR_PARAM;
    frnemc |= clusterParamPtr->FrClusterGNetworkManagementVectorLength;
    hwPtr->FRNEMC = frnemc;

    hwPtr->FRITC |= MASK_FRITC_ITE;
    hwPtr->FROTC |= MASK_FROTC_OTE;

    return E_OK;
}

/**
 * Setup the Message RAM and header for the configured FrIf triggering units.
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @return
 */
Std_ReturnType Fr_Internal_SetupRxTxResources(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx) {
    const Fr_FrIfCCTriggeringType *FrTrigConf = &Fr_Cfg->Fr_ConfigPtr->FrTrigConfig[Fr_CtrlIdx];
    uint32 keySlotId = Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx].FrPKeySlotId;
    uint32 keySlotIdx = 0;
    uint32 frmrc = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRMRC;
    uint32 addr = RAM_MESSAGE_BASE_ADDR;
    Std_ReturnType status;
    uint32 n;

    //Wait for CLEAR_RAM to finish.
    status = waitWhileBusy(&Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRSUCC1, MASK_FRSUCC1_PBSY, FALSE);
    if (status == E_NOT_OK) {
        return E_NOT_OK;
    }

    bufferindex = BUFFER_START_IDX;

    frmrc &= ~MASK_FRMRC_FDB;
    frmrc &= ~MASK_FRMRC_FFB;
    frmrc &= ~MASK_FRMRC_LCB;

    //Configure Message RAM to use the static + dynamic section for now.
    // Set number of message buffers to the number of buffers used
    frmrc |= FrTrigConf->FrNbrTrigConfiged << BIT_SHIFT_FRMRC_FFB;
    frmrc |= FrTrigConf->FrNbrTrigConfiged << BIT_SHIFT_FRMRC_LCB;
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRMRC = frmrc;

    //Setup buffer data pointer to the message frame
    //The header section of each message buffer occupies four 32-bit words in the header partition of the
    //Message RAM. The header of message buffer 0 starts with the first word in the Message RAM.

    //The data partition starts after the last word of the header partition.
    //The data partition is allowed to start at Message RAM word number: (FLXAnFRMRC.LCB + 1) * 4
    addr += (FrTrigConf->FrNbrTrigConfiged + (uint32)1) * 4;

    if (keySlotId > 0) {
        //FrPKeySlotId must be configured into message buffer 0.
        status = findTrigIdx(FrTrigConf, keySlotId, &keySlotIdx);

        if (status == E_OK) {
            status = setupMessageBuffer(Fr_Cfg, Fr_CtrlIdx, keySlotIdx, &addr);

            if (status == E_NOT_OK) {
                return E_NOT_OK;
            }

        } else {
            return E_NOT_OK;
        }
    }

    //Loop through the remaining buffers that needs setup.
    for (n = 0; n < FrTrigConf->FrNbrTrigConfiged; n++) {

        //If its not key slot 1 then initialize it.
        if (!((keySlotId > 0) && (keySlotIdx == n)))
        {
            status = setupMessageBuffer(Fr_Cfg, Fr_CtrlIdx, n, &addr);

            if (status != E_OK) {
                return E_NOT_OK;
            }
        }
    }
    return E_OK;
}

/**
 * Used to find the trigger index linked to the LPdu
 * @param FrTrigConf
 * @param searchedId
 * @param trigIdx
 * @return
 */
static Std_ReturnType findTrigIdx(const Fr_FrIfCCTriggeringType *FrTrigConf, uint32 searchedId, uint32 *trigIdx) {
    uint32 n;

    for (n = 0; n < FrTrigConf->FrNbrTrigConfiged; n++) {
        if (FrTrigConf->FrTrigConfPtr[n].FrTrigSlotId == searchedId) {
            *trigIdx = n;
            return E_OK;
        }
    }

    return E_NOT_OK;
}

/**
 * Setup Message RAM
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param frameTrigIdx
 * @param dataAddr
 * @return
 */
static Std_ReturnType setupMessageBuffer(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint32 frameTrigIdx, uint32 *dataAddr) {
    const Fr_CtrlConfigParametersType *paramPtr = &Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx];
    const Fr_FrIfCCTriggeringType *FrTrigConf = &Fr_Cfg->Fr_ConfigPtr->FrTrigConfig[Fr_CtrlIdx];
    const Fr_FrIfClusterConfigType *clusterParamPtr = &Fr_Cfg->Fr_ConfigPtr->FrClusterConfig[Fr_CtrlIdx];
    uint32 addr = *dataAddr;
    boolean isStaticFrame;
    Std_ReturnType retval;
    uint32 missAligned;
    uint32 maxLengh;
    uint32 length;

    //If the size of the data section is an odd number of 2-byte words, the remaining 16 bits in the last 32bit
    //word are unused (see Table 21.108 below).
    missAligned = addr % (uint32)4;
    if (missAligned > 0) {
        addr += ((uint32)4 - missAligned);
    }

    isStaticFrame = (FrTrigConf->FrTrigConfPtr[frameTrigIdx].FrTrigSlotId <= clusterParamPtr->FrClusterGNumberOfStaticSlots) ? TRUE : FALSE;
    maxLengh = ((isStaticFrame) ? clusterParamPtr->FrClusterGPayloadLengthStatic : paramPtr->FrPPayloadLengthDynMax) * FR_LENGTH_DIV;
    length = FrTrigConf->FrTrigConfPtr[frameTrigIdx].FrTrigLSduLength;

    if (length > maxLengh)
    {
        return E_NOT_OK;
    }

    //Message RAM is able to store up to 2048 32-bit words (header and data partition)
    if ((addr + length) >= RAM_MESSAGE_END_ADDR) {
        /* @req FR485 Is also checked at configuration validation */
#if ( FR_DEV_ERROR_DETECT == STD_ON )
        (void)Det_ReportError(FR_MODULE_ID, 0, FR_CTRLINIT_SERVICE_ID, FR_E_ARC_DATA_PARTITION);
#endif
        return E_NOT_OK;
    }

    //Store the selected address and index.
    FrTrigConf->FrMsgBufferCfg[frameTrigIdx].FrDataPartitionAddr = addr;

    //increment address pointer
    addr += length;

    // Write header
    retval = writeHeader(Fr_Cfg, Fr_CtrlIdx, frameTrigIdx);
    if (retval == E_OK) {
        *dataAddr = addr;
    }

    return retval;
}

/**
 * Function used to setup the header registers
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param frameTrigIdx
 * @return
 */
static Std_ReturnType writeHeader(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint32 frameTrigIdx) {
    const Fr_FrIfTriggeringConfType *FrTrigConf = &Fr_Cfg->Fr_ConfigPtr->FrTrigConfig[Fr_CtrlIdx].FrTrigConfPtr[frameTrigIdx];
    Std_ReturnType retval;
    uint32 frwrhs1 = 0;
    uint32 frwrhs2 = 0;
    uint32 frwrhs3 = 0;
    uint32 ch = 0;
    uint32 txm = (FrTrigConf->FrTrigAlwaysTransmit == STD_ON)? (uint32)0 : (uint32)1;

    // (1) Header section 1 (word 0), FLXAnFRWRHS1
    if (FrTrigConf->FrTrigChannel == FR_CHANNEL_A) {
        ch = 1;
    } else if (FrTrigConf->FrTrigChannel == FR_CHANNEL_B) {
        ch = 2;
    } else {
        ch = 3;
    }

    frwrhs1 |= FrTrigConf->FrTrigSlotId;
    frwrhs1 |=  (FrTrigConf->FrTrigBaseCycle | FrTrigConf->FrTrigCycleRepetition) << BIT_SHIFT_FRWRHS1_CYC;
    frwrhs1 |= ch << BIT_SHIFT_FRWRHS1_CH;
    frwrhs1 |= FrTrigConf->FrTrigIsTx << BIT_SHIFT_FRWRHS1_CFG;
    frwrhs1 |= (uint32)FrTrigConf->FrTrigPayloadPreamble << BIT_SHIFT_FRWRHS1_PPIT;
    frwrhs1 |= txm << BIT_SHIFT_FRWRHS1_TXM;

    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRWRHS1 = frwrhs1;

    // (2) Header section 2 (word 1), FLXAnFRWRHS2
    frwrhs2 |= getHeaderCrc(Fr_Cfg, Fr_CtrlIdx, frameTrigIdx, FrTrigConf->FrTrigLSduLength);
    frwrhs2 |= (FrTrigConf->FrTrigLSduLength / FR_LENGTH_DIV) << BIT_SHIFT_FRWRHS2_PLC;

    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRWRHS2 = frwrhs2;

    // (3) Header section 3 (word 2), FLXAnFRWRHS3
    frwrhs3 |= Fr_Cfg->Fr_ConfigPtr->FrTrigConfig[Fr_CtrlIdx].FrMsgBufferCfg[frameTrigIdx].FrDataPartitionAddr;
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRWRHS3 = frwrhs3;

    retval = waitWhileBusy(&Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRIBCR, MASK_FRIBCR_IBSYH, FALSE);
    if (retval == E_OK) {
        Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRIBCM = MASK_FRIBCM_LHSH;

        Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRIBCR = (uint32)bufferindex;

        Fr_Cfg->Fr_ConfigPtr->FrTrigConfig[Fr_CtrlIdx].FrMsgBufferCfg[frameTrigIdx].FrMsgBufferIdx = bufferindex;
        Fr_Cfg->Fr_ConfigPtr->FrTrigConfig[Fr_CtrlIdx].FrMsgBufferCfg[frameTrigIdx].FrCurrentLengthSetup = FrTrigConf->FrTrigLSduLength;
        bufferindex++;
    }

    return retval;
}

/**
 * Updates the length of a message buffer
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param msgBuffrIdx
 * @return
 */
Std_ReturnType Fr_Internal_UpdateHeaderLength(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8 length, uint16 msgBuffrIdx, uint32 frameTrigIdx) {
    Std_ReturnType retval;
    uint32 frwrhs1;
    uint32 frwrhs2 = 0;
    uint32 frwrhs3;

    //Read out the current header setup so we can write it back.
    retval = readOutMessageRamBuffer(Fr_Cfg, Fr_CtrlIdx, msgBuffrIdx, HEADER);

    if (retval == E_OK) {
        frwrhs1 = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRRDHS1;
        frwrhs3 = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRRDHS3;

        frwrhs2 |= getHeaderCrc(Fr_Cfg, Fr_CtrlIdx, frameTrigIdx, (uint32)length);
        frwrhs2 |= ((uint32)length / FR_LENGTH_DIV) << BIT_SHIFT_FRWRHS2_PLC;

        Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRWRHS1 = frwrhs1;
        Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRWRHS2 = frwrhs2;
        Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRWRHS3 = frwrhs3;

        retval = waitWhileBusy(&Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRIBCR, MASK_FRIBCR_IBSYH, FALSE);
        if (retval == E_OK) {
            Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRIBCM = MASK_FRIBCM_LHSH;

            Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRIBCR = (uint32)msgBuffrIdx;

            Fr_Cfg->Fr_ConfigPtr->FrTrigConfig[Fr_CtrlIdx].FrMsgBufferCfg[frameTrigIdx].FrCurrentLengthSetup = (uint32)length;
        }
    }

    return retval;
}

/**
 * Calculate checksum according to Flexray specification chapter 4.5.
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param frameTrigIdx
 * @return
 */
/* !@req Flexray specification does not allow CC to calculate checksum */
static uint32 getHeaderCrc(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint32 frameTrigIdx, uint32 dynLen){
    const Fr_FrIfTriggeringConfType *FrTrigConf = &Fr_Cfg->Fr_ConfigPtr->FrTrigConfig[Fr_CtrlIdx].FrTrigConfPtr[frameTrigIdx];
    const Fr_FrIfClusterConfigType *clusterParamPtr = &Fr_Cfg->Fr_ConfigPtr->FrClusterConfig[Fr_CtrlIdx];
    const Fr_CtrlConfigParametersType *paramPtr = &Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx];

    // Data setup
    uint32 keySlotId = Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx].FrPKeySlotId;
    uint8  slotIsKey = (FrTrigConf->FrTrigSlotId == keySlotId) ? 1 : 0;

    uint32 syncFrameInd  = ((slotIsKey > 0) && paramPtr->FrPKeySlotUsedForSync) ? (uint32)1 : (uint32)0;
    uint32 startFrameInd = ((slotIsKey > 0) && paramPtr->FrPKeySlotUsedForStartup) ? (uint32)1 : (uint32)0;

    uint32 payloadLen = (FrTrigConf->FrTrigSlotId > clusterParamPtr->FrClusterGNumberOfStaticSlots) ? \
            (dynLen/FR_LENGTH_DIV) : clusterParamPtr->FrClusterGPayloadLengthStatic;

    uint32 data = (syncFrameInd << 19u)      |
            (startFrameInd << 18u)           |
            (FrTrigConf->FrTrigSlotId << 7u) |
            (payloadLen);

    //Checksum calculation
    uint32 vCrcPolynomial = V_CRC_POLYNOMIAL;
    sint32 vNextBitIdx;
    uint32 vCrcReg = V_CRC_INIT;
    uint32 vCrcNext;
    uint32 nextBit;

    for (vNextBitIdx = 19; vNextBitIdx >= 0; vNextBitIdx--) {

        nextBit =  (data >> (uint32)vNextBitIdx) & (uint32)0x01;
        vCrcNext = nextBit ^ ((vCrcReg >> (V_CRC_SIZE-1)) & (uint32)0x01);

        vCrcReg = vCrcReg << 1u;

        if (vCrcNext > 0) {
            vCrcReg = vCrcReg ^ vCrcPolynomial;
        }
    }

    return (uint32)(vCrcReg & (uint32)0x7FF);
}

/**
 * Clear pending status bits
 *
 * Reference manual chapter 21.3.14, the Host has access to the actual status and error information by reading registers
 * FLXAnFREIR, FLXAnFRSIR, FLXAnFROS, FLXAnFROTS and FLXAnFRITS.
 *
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 */
void Fr_Arc_ClearPendingIsr(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx) {
    uint32 toggleOnWrite;

    //The status bits of FREIR, FRSIR and FROS are cleared when writing a 1 to them.
    toggleOnWrite = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FREIR;
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FREIR = toggleOnWrite;

    toggleOnWrite = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRSIR;
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRSIR = toggleOnWrite;

    toggleOnWrite = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROS;
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROS  = toggleOnWrite;

    //The flags in FROTS are cleared by the operation performed in function Fr_Arc_clearPendingTx.
    //The flags in FRITS are cleared by the operation performed in function Fr_Arc_clearPendingRx.
}

/**
 * Disable all absolut timers
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 */
void Fr_Internal_DisableAllTimers(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx) {
    //Put the timers in halt.
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRT0C &= ~MASK_FRTXC_T2RC;
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRT1C &= ~MASK_FRTXC_T2RC;
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRT2C &= ~MASK_FRTXC_T2RC;
}

/**
 * Disable all interrupts
 *
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 */
void Fr_Internal_DisableAllFrIsr(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx) {
    uint32 writeToClear;

    writeToClear = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FREIER;
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FREIER = writeToClear;

    writeToClear = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRSIER;
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRSIER = writeToClear;

    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRILE = 0;

    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRITC &= ~(MASK_FRITC_IQFIE | MASK_FRITC_IQEIE);

    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROC &= ~(MASK_FROC_T0IE | MASK_FROC_T1IE | MASK_FROC_T2IE);
}

#if 0
void Fr_Internal_DisableAllLPdu(void) {
    //Reconfigurable LPdus are not supported.
}
#endif

/**
 * Run the configuration test n number of times and report status to the DEM.
 * @param Fr_CtrlIdx
 * @return
 */
Std_ReturnType Fr_Internal_RunAllCCTest(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx) {
    Std_ReturnType retval = E_OK;
    Std_ReturnType status;
    uint8 ccErrCnt = 0;
    uint8 n;

#if (FR_CTRL_TEST_COUNT > 0)
    for(n = 0; n < FR_CTRL_TEST_COUNT; n++) {
        /* @req FR647 */
        status = Fr_Internal_RunCCTest(Fr_Cfg, Fr_CtrlIdx);

        /* @req FR598 */
        if (status == E_OK) {
            DEM_REPORT(Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx].FrDemEventParamRef, DEM_EVENT_STATUS_PASSED);
            break;
        } else {
            ccErrCnt++;
        }
    }

    /* @req FR147 */
    if (ccErrCnt == FR_CTRL_TEST_COUNT) {
        DEM_REPORT(Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx].FrDemEventParamRef, DEM_EVENT_STATUS_FAILED);
        retval = E_NOT_OK;
    }
#endif

    return retval;
}

/**
 * Set the CHI command according to FLXAnFRSUCC1.CMD page 991 ref manual.
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param chiCmd
 * @return
 */
Std_ReturnType Fr_Internal_SetCtrlChiCmd(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8 chiCmd) {
    uint32 frsucc1 = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRSUCC1;
    Std_ReturnType retval;
    uint32 freir;
    uint8 n;

    retval = waitWhileBusy(&Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRSUCC1, MASK_FRSUCC1_PBSY, FALSE);
    if (retval == E_NOT_OK) {
        return E_NOT_OK;
    }

    frsucc1 &= ~MASK_FRSUCC1_CMD;
    frsucc1 |= (uint32)chiCmd;
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRSUCC1 = frsucc1;

    for (n = 0; n < ARC_NBR_CHI_CMD_RETRIES; n++) {
        //Previous CHI command has not yet completed; the CHI command needs to be repeated.
        freir = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FREIR;
        if (((freir & MASK_FREIR_CNA) == MASK_FREIR_CNA) &&
            ((freir & MASK_FREIR_CCL) == MASK_FREIR_CCL))
        {
            Fr_Cfg->hwPtr[Fr_CtrlIdx]->FREIR |= MASK_FREIR_CNA;
            Fr_Cfg->hwPtr[Fr_CtrlIdx]->FREIR |= MASK_FREIR_CCL;
            //Repeat command
            frsucc1 = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRSUCC1;
            frsucc1 &= ~MASK_FRSUCC1_CMD;
            frsucc1 |= (uint32)chiCmd;
            Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRSUCC1 = frsucc1;
        } else {
            break;
        }
    }

    if ((Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRSUCC1 & MASK_FRSUCC1_CMD) == CHI_CMD_NOT_ACCEPTED) {
        /* @req FR181 */
        /* @req FR186 */
        /* @req FR190 */
        /* @req FR195 */
        /* @req FR201 */
        DEM_REPORT(Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx].FrDemEventParamRef, DEM_EVENT_STATUS_FAILED);
        retval = E_NOT_OK;
    }

    return retval;
}

/**
 * Will enable controller if its disabled.
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @return
 */
Std_ReturnType Fr_Internal_EnableCtrl(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx) {
    Std_ReturnType retval;

    if (!((Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROC & MASK_FROC_OE) == MASK_FROC_OE)) {
        //Enable sequence described in ref manual 21.3.1.1
        Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROC &= ~MASK_FROC_OEP;
        Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROC |= MASK_FROC_OE;

        retval = waitWhileBusy(&Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROS, MASK_FROS_OS, TRUE);
        if (retval == E_NOT_OK) {
            return E_NOT_OK;
        }

        Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROC |= MASK_FROC_OEP;

        retval = waitWhileBusy(&Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRSUCC1, MASK_FRSUCC1_PBSY, FALSE);
        if (retval == E_NOT_OK) {
            return E_NOT_OK;
        }

        Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROC |= MASK_FROC_OEP;
    }

    return E_OK;
}

/**
 * Setup the CC according to all configuration parameters and run the CC test.
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @return
 */
Std_ReturnType Fr_Internal_setupAndTestCC(Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx) {
    Std_ReturnType retval;
    uint32 frits;
    uint32 fribcr;
    uint32 frobcr;

    /* @req FR148 */

    // 1. Switch CC into ‘POC:config’ (from any other POCState).
    // State moves from (ANY) -> HALT
    retval = Fr_AbortCommunication(Fr_CtrlIdx);
    if (retval == E_NOT_OK) {
        return E_NOT_OK;
    }
    // State moves from HALT -> DEFAULT_CONFIG
    retval = Fr_Internal_SetCtrlChiCmd(Fr_Cfg, Fr_CtrlIdx, (uint8)CHI_CMD_CONFIG);
    if (retval == E_NOT_OK) {
        return E_NOT_OK;
    }
    // State moves from DEFAULT_CONFIG -> CONFIG
    retval = Fr_Internal_SetCtrlChiCmd(Fr_Cfg, Fr_CtrlIdx, (uint8)CHI_CMD_CONFIG);
    if (retval == E_NOT_OK) {
        return E_NOT_OK;
    }
    Fr_Cfg->Fr_CCPocState[Fr_CtrlIdx] = FR_POCSTATE_CONFIG;

    //Clear message ram
    //Make sure that no buffer transfer in progress.
    retval = E_NOT_OK;
    frits  = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRITS;
    fribcr = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRIBCR;
    frobcr = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROBCR;

    if (((frits & MASK_FRITS_ITS) == 0) && ((frits & MASK_FRITS_ITS) == 0) &&
            ((fribcr & MASK_FRIBCR_IBSYH) == 0) && ((frobcr & MASK_FROBCR_OBSYS) == 0))
    {
        retval = Fr_Internal_SetCtrlChiCmd(Fr_Cfg, Fr_CtrlIdx, (uint8)CHI_CMD_CLEAR_RAMS);
    }

    if (retval == E_NOT_OK) {
        return E_NOT_OK;
    }


    // 2. Configure all FlexRay cluster and node configuration parameters (e.g., cycle length, macrotick duration).
    Fr_Internal_SetupCC(Fr_Cfg, Fr_CtrlIdx);
    // 3. Configure all transmit/receive resources (e.g., buffer initialization) according to the frame triggering configuration parameters contained in the FrIf.
    retval = Fr_Internal_SetupRxTxResources(Fr_Cfg, Fr_CtrlIdx);
    if (retval == E_NOT_OK) {
        return E_NOT_OK;
    }


    //Run the CC tests before we change the state of the controller.
    retval = Fr_Internal_RunAllCCTest(Fr_Cfg, Fr_CtrlIdx);

    if(retval == E_OK) {
        // 4. Switch CC into ‘POC:ready’
        Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRLCK = LOCK_FIRST_WRITE;
        Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRLCK = LOCK_SECOND_WRITE;
        retval = Fr_Internal_SetCtrlChiCmd(Fr_Cfg, Fr_CtrlIdx, (uint8)CHI_CMD_READY);
        if (retval == E_NOT_OK) {
                return E_NOT_OK;
        }
        Fr_Cfg->Fr_CCPocState[Fr_CtrlIdx] = FR_POCSTATE_READY;
        // -  Set the register CC POC state to ready.
        // 5. Return E_OK. (BSW05059, BSW05012)
        retval = E_OK;
    }

    return retval;
}

/**
 * Read chi poc status.
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param Fr_POCStatusPtr
 * @return E_OK or E_NOT_OK
 */
Std_ReturnType Fr_Internal_GetChiPocState(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, Fr_POCStatusType* Fr_POCStatusPtr) {
    Fr_POCStatusType pocStatus = {0};
    uint32 chiPocStateReg = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRCCSV;
    uint32 chiErrStateReg = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRCCEV;
    uint32 tempReg;
    uint32 errMode;
    uint32 wakeUpMode;
    uint32 slotMode;

    pocStatus.CHIHaltRequest = ((chiPocStateReg & MASK_FRCCSV_HRQ) == MASK_FRCCSV_HRQ)? TRUE : FALSE;
    pocStatus.ColdstartNoise = ((chiPocStateReg & MASK_FRCCSV_CSNI) == MASK_FRCCSV_CSNI)? TRUE : FALSE;

    errMode = (chiErrStateReg & MASK_FRCCEV_ERRM) >> BIT_SHIFT_FRCCEV_ERRM;
    if (errMode == FRCCEV_ERRM_RESERVED) {
        /* @req FR216 */
        DEM_REPORT(Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx].FrDemEventParamRef, DEM_EVENT_STATUS_FAILED);
        return E_NOT_OK;
    } else {
        pocStatus.ErrorMode = (Fr_ErrorModeType)errMode;
    }

    pocStatus.Freeze = ((chiPocStateReg & MASK_FRCCSV_FSI) ==  MASK_FRCCSV_FSI)? TRUE : FALSE;

    slotMode = (chiPocStateReg & MASK_FRCCSV_SLM) >> BIT_SHIFT_FRCCSV_SLM;
    if (slotMode == 0) {
        pocStatus.SlotMode = FR_SLOTMODE_KEYSLOT;
    } else if (slotMode == 2) {
        pocStatus.SlotMode = FR_SLOTMODE_ALL_PENDING;
    } else if (slotMode == 3) {
        pocStatus.SlotMode = FR_SLOTMODE_ALL;
    } else {
        DEM_REPORT(Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx].FrDemEventParamRef, DEM_EVENT_STATUS_FAILED);
        return E_NOT_OK;
    }

    if ((chiPocStateReg & MASK_FRCCSV_POCS) == MASK_DEFAULT_CONFIG) {
        pocStatus.State = FR_POCSTATE_DEFAULT_CONFIG;
    } else if ((chiPocStateReg & MASK_WAKEUP) == MASK_WAKEUP) {
        pocStatus.State = FR_POCSTATE_WAKEUP; // double check
    } else if ((chiPocStateReg & MASK_STARTUP) == MASK_STARTUP) {
        pocStatus.State = FR_POCSTATE_STARTUP; // double check
    } else if ((chiPocStateReg & MASK_READY) == MASK_READY) {
        pocStatus.State = FR_POCSTATE_READY;
    } else if ((chiPocStateReg & MASK_NORMAL_ACTIVE) == MASK_NORMAL_ACTIVE) {
        pocStatus.State = FR_POCSTATE_NORMAL_ACTIVE;
    } else if ((chiPocStateReg & MASK_NORMAL_PASSIVE) == MASK_NORMAL_PASSIVE) {
        pocStatus.State = FR_POCSTATE_NORMAL_PASSIVE;
    } else if ((chiPocStateReg & MASK_HALT) == MASK_HALT) {
        pocStatus.State = FR_POCSTATE_HALT;
    } else if ((chiPocStateReg & MASK_CONFIG) == MASK_CONFIG) {
        pocStatus.State = FR_POCSTATE_CONFIG;
    } else {
        /* @req FR216 */
        DEM_REPORT(Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx].FrDemEventParamRef, DEM_EVENT_STATUS_FAILED);
        return E_NOT_OK;
    }

    tempReg = chiPocStateReg & MASK_STARTUP_BITS;
    // Set the start up state
    if (tempReg == MASK_COLDSTART_LISTEN) {
        pocStatus.StartupState = FR_STARTUP_COLDSTART_LISTEN;
    } else if (tempReg == MASK_COLDSTART_COLLISION_RESOLUTION) {
        pocStatus.StartupState = FR_STARTUP_COLDSTART_COLLISION_RESOLUTION;
    } else if (tempReg == MASK_COLDSTART_CONSISTENCY_CHECK) {
        pocStatus.StartupState = FR_STARTUP_COLDSTART_CONSISTENCY_CHECK;
    } else if (tempReg == MASK_COLDSTART_GAP) {
        pocStatus.StartupState = FR_STARTUP_COLDSTART_GAP;
    } else if (tempReg == MASK_COLDSTART_JOIN) {
        pocStatus.StartupState = FR_STARTUP_COLDSTART_JOIN;
    } else if (tempReg == MASK_INTEGRATION_COLDSTART_CHECK) {
        pocStatus.StartupState = FR_STARTUP_INTEGRATION_COLDSTART_CHECK;
    } else if (tempReg == MASK_INTEGRATION_LISTEN) {
        pocStatus.StartupState = FR_STARTUP_INTEGRATION_LISTEN;
    } else if (tempReg == MASK_INTEGRATION_CONSISTENCY_CHECK) {
        pocStatus.StartupState = FR_STARTUP_INTEGRATION_CONSISTENCY_CHECK;
    } else if (tempReg == MASK_INITIALIZE_SCHEDULE) {
        pocStatus.StartupState = FR_STARTUP_INITIALIZE_SCHEDULE;
    } else {
        pocStatus.StartupState = FR_STARTUP_UNDEFINED;
    }

    wakeUpMode = (chiPocStateReg & MASK_FRCCSV_WSV) >> BIT_SHIFT_FRCCSV_WSV;
    if (wakeUpMode == FRCCEV_WSV_RESERVED) {
        /* @req FR216 */
        DEM_REPORT(Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx].FrDemEventParamRef, DEM_EVENT_STATUS_FAILED);
        return E_NOT_OK;
    } else {
        pocStatus.WakeupStatus = (Fr_WakeupStatusType)wakeUpMode;
    }

    //Successful readout, set output values.
    Fr_POCStatusPtr->CHIHaltRequest = pocStatus.CHIHaltRequest;
    Fr_POCStatusPtr->ColdstartNoise = pocStatus.ColdstartNoise;
    Fr_POCStatusPtr->ErrorMode      = pocStatus.ErrorMode;
    Fr_POCStatusPtr->Freeze         = pocStatus.Freeze;
    Fr_POCStatusPtr->SlotMode       = pocStatus.SlotMode;
    Fr_POCStatusPtr->StartupState   = pocStatus.StartupState;
    Fr_POCStatusPtr->State          = pocStatus.State;
    Fr_POCStatusPtr->WakeupStatus   = pocStatus.WakeupStatus;
    return E_OK;
}

/**
 * Set data to transmit
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param Fr_LSduPtr
 * @param Fr_LSduLength
 * @param Fr_MsgBuffrIdx
 * @return
 */
Std_ReturnType Fr_Internal_SetTxData(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, const uint8* Fr_LSduPtr, uint8 Fr_LSduLength, uint16 Fr_MsgBuffrIdx) {
    volatile struct FLXA_reg *hwPtr = Fr_Cfg->hwPtr[Fr_CtrlIdx];
    Std_ReturnType retval;
    uint32 fribcm = 0;
    uint8 n, j, undefined;

    //Copy byte by byte.
    /* @req FR225 */
    for (n = 0; n < Fr_LSduLength; n++) {
        hwPtr->FRWRDS[n] = Fr_LSduPtr[n];
    }

    //As the 8-byte access was used we shall check if any remaining bytes of the
    //32-bit register is undefined and set them to 0.
    undefined = (uint8)4 - (n % (uint8)4);
    if (undefined < 4) {
        for (j = 0; j < undefined; j++) {
            hwPtr->FRWRDS[n] = 0;
            n++;
        }
    }

    retval = waitWhileBusy(&Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRIBCR, MASK_FRIBCR_IBSYH, FALSE);
    if (retval == E_NOT_OK) {
        /* @req FR223 */
        DEM_REPORT(Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx].FrDemEventParamRef, DEM_EVENT_STATUS_FAILED);
        return E_NOT_OK;
    }

    fribcm |= MASK_FRIBCM_LDSH;
    fribcm |= MASK_FRIBCM_STXRH;
    hwPtr->FRIBCM = fribcm;

    hwPtr->FRIBCR = (uint32)Fr_MsgBuffrIdx;

    return E_OK;
}

/**
 * Check if the index message buffer have received any new data.
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param msgBufferIdx
 * @return
 */
Std_ReturnType Fr_Internal_CheckNewData(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint16 msgBufferIdx) {
    const volatile uint32 *basePtr = &Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRNDAT1;
    uint16 registerIdx = msgBufferIdx / 32UL;
    uint16 registerBitPos = msgBufferIdx % (uint16)32;
    uint32 newData = ((basePtr[registerIdx] >> registerBitPos) & (uint32)0x01);
    Std_ReturnType retval = (newData > 0)? E_OK : E_NOT_OK;

    return retval;
}

/**
 * Copy data from the message ram
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param msgBufferIdx
 * @param Fr_LSduLengthPtr
 * @return
 */
Std_ReturnType Fr_Internal_GetNewData(  const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint32 trigIdx,
                                        uint16 msgBufferIdx, uint8* Fr_LSduPtr, uint8* Fr_LSduLengthPtr) {
    const volatile struct FLXA_reg *hwPtr = Fr_Cfg->hwPtr[Fr_CtrlIdx];
    const Fr_FrIfTriggeringConfType trigConf = Fr_Cfg->Fr_ConfigPtr->FrTrigConfig[Fr_CtrlIdx].FrTrigConfPtr[trigIdx];
    Std_ReturnType retval;
    boolean errorStatusChnA = FALSE;
    boolean errorStatusChnB = FALSE;
    uint32 frrdhs2;
    uint32 frmbs;
    uint32 length;
    uint32 i;

    //Start by transferring the header and data from the message ram
    retval = readOutMessageRamBuffer(Fr_Cfg, Fr_CtrlIdx, msgBufferIdx, HEADER_AND_DATA);
    if (retval == E_NOT_OK) {
        /* @req FR232 */
        DEM_REPORT(Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx].FrDemEventParamRef, DEM_EVENT_STATUS_FAILED);
        return E_NOT_OK;
    }

    //Read out header and status registers of the message buffer
    frrdhs2 = hwPtr->FRRDHS2;
    frmbs   = hwPtr->FRMBS;

    //Received length as indicated by the frame header
    length = ((frrdhs2 & MASK_FRRDHS2_PLR)*FR_LENGTH_DIV) >> BIT_SHIFT_FRRDHS2_PLR;

    /* @req FR236 */
    //Null frame check.
    if ((frmbs & MASK_FRMBS_NFIS) == 0) {
        return E_NOT_OK;
    }

    /* @req FR605 */
    if (((frmbs & MASK_FRMBS_RCIS) == MASK_FRMBS_RCIS) && /* Data received on channel A */
            (((frmbs & MASK_FRMBS_SEOA) == MASK_FRMBS_SEOA) || /* vSS!SyntaxError */
            ((frmbs & MASK_FRMBS_CEOA) == MASK_FRMBS_CEOA)  || /* vSS!ContentError */
            ((frmbs & MASK_FRMBS_SVOA) == MASK_FRMBS_SVOA)))   /* vSS!Bviolation */
    {
        DEM_REPORT(trigConf.FrTrigDemFTSlotStatusRef, DEM_EVENT_STATUS_FAILED);
        errorStatusChnA = TRUE;
    }
    else if (((frmbs & MASK_FRMBS_RCIS) == 0) && /* Data received on channel B */
            (((frmbs & MASK_FRMBS_SEOB) == MASK_FRMBS_SEOB) || /* vSS!SyntaxError */
            ((frmbs & MASK_FRMBS_CEOB) == MASK_FRMBS_CEOB)  || /* vSS!ContentError */
            ((frmbs & MASK_FRMBS_SVOB) == MASK_FRMBS_SVOB)))   /* vSS!Bviolation */
    {
        DEM_REPORT(trigConf.FrTrigDemFTSlotStatusRef, DEM_EVENT_STATUS_FAILED);
        errorStatusChnB = TRUE;
    }
    else
    {
        ; /* For Misra compliance */
    }

    /* @req FR603 */
#if defined(FR_RX_STRINGENT_CHECK)
    if ((((frmbs & MASK_FRMBS_RCIS) == MASK_FRMBS_RCIS) && /* Data received on channel A */
        !((frmbs & MASK_FRMBS_VFRA) == MASK_FRMBS_VFRA)) || /* vSS!ValidFrame */
        errorStatusChnA) /* Bit error channel A */
    {
        return E_NOT_OK;
    }
    else if ((((frmbs & MASK_FRMBS_RCIS) == 0) && /* Data received on channel B */
        !((frmbs & MASK_FRMBS_VFRB) == MASK_FRMBS_VFRB)) || /* vSS!ValidFrame */
        errorStatusChnB) /* Bit error channel B */
    {
        return E_NOT_OK;
    }
    else
    {
        ; /* For Misra compliance */
    }
#else
    /* @req FR604 */
    if (!(((frmbs & MASK_FRMBS_RCIS) == MASK_FRMBS_RCIS) && /* Data received on channel A */
            ((frmbs & MASK_FRMBS_VFRA) == MASK_FRMBS_VFRA))) /* vSS!ValidFrame */
    {
        return E_NOT_OK;
    }
    if (!(((frmbs & MASK_FRMBS_RCIS) == 0) && /* Data received on channel B */
            ((frmbs & MASK_FRMBS_VFRB) == MASK_FRMBS_VFRB))) /* vSS!ValidFrame */
    {
        return E_NOT_OK;
    }
#endif

    /* @req FR645 */
#if defined(FR_RX_STRINGENT_LENGTH_CHECK)
    if (length != trigConf.FrTrigLSduLength) {
        return E_NOT_OK;
    }
#endif

    /* @req FR239 */
    if (length > trigConf.FrTrigLSduLength) {
        return E_NOT_OK;
    }

    /* @req FR234 */
    for (i = 0; i < length; i++) {
        Fr_LSduPtr[i] = hwPtr->FRRDDS[i];
    }
    //FrIf validator shall have checked that the range is within 0 .. 254, cast to uint8 is ok.
    *Fr_LSduLengthPtr = (uint8)length;

    /* @req FR627 */
    DEM_REPORT(trigConf.FrTrigDemFTSlotStatusRef, DEM_EVENT_STATUS_PASSED);

    return E_OK;
}

/**
 * Checks the message buffer status in FLXAnFRTXRQ.
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param msgBufferIdx
 * @return
 */
Std_ReturnType Fr_Internal_GetTxPending(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint32 trigIdx, boolean *txPending) {
    const Fr_FrIfCCTriggeringType *trigConfPtr = &Fr_Cfg->Fr_ConfigPtr->FrTrigConfig[Fr_CtrlIdx];
    uint16 msgBufferIdx = trigConfPtr->FrMsgBufferCfg[trigIdx].FrMsgBufferIdx;
    Fr_ChannelType confChnl = Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx].FrPChannels;
    const volatile uint32 *basePtr;
    uint32 msgBufferStatusChanged;
    boolean errorIsSet = FALSE;
    Std_ReturnType retval;
    uint16 registerBitPos;
    boolean isTxPending;
    uint16 registerIdx;
    uint32 txStatusFlag;
    uint32 frmbs;

    //Calculate message buffer status flag index
    registerIdx    = msgBufferIdx / 32UL;
    registerBitPos = msgBufferIdx % (uint16)32;

    //Check if tx for the buffer is pending
    basePtr      = &Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRTXRQ1;
    txStatusFlag = ((basePtr[registerIdx] >> registerBitPos) & (uint32)0x01);
    isTxPending  = (txStatusFlag > 0)? TRUE : FALSE;

    //Check if general message buffer status flag is set.
    basePtr = &Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRMBSC1;
    msgBufferStatusChanged = ((basePtr[registerIdx] >> registerBitPos) & (uint32)0x01);

    //Status flags that might indicate error have changed,
    //must read out message buffer header from Message RAM to read individual status flags.
    if (msgBufferStatusChanged != 0UL) {
        retval = readOutMessageRamBuffer(Fr_Cfg, Fr_CtrlIdx, msgBufferIdx, HEADER);
        if (retval == E_NOT_OK) {
            /* @req FR613 */
            DEM_REPORT(Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx].FrDemEventParamRef, DEM_EVENT_STATUS_FAILED);
            return E_NOT_OK;
        }

        frmbs   = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRMBS;

        /* @req FR606 */
        if (((confChnl == FR_CHANNEL_A) || (confChnl == FR_CHANNEL_AB)) &&
            (((frmbs & MASK_FRMBS_SEOA) == MASK_FRMBS_SEOA) || /* vSS!SyntaxError */
            ((frmbs & MASK_FRMBS_CEOA) == MASK_FRMBS_CEOA) || /* vSS!ContentError */
            ((frmbs & MASK_FRMBS_SVOA) == MASK_FRMBS_SVOA)))  /* vSS!Bviolation */
        {
            DEM_REPORT(trigConfPtr->FrTrigConfPtr[trigIdx].FrTrigDemFTSlotStatusRef, DEM_EVENT_STATUS_FAILED);
            errorIsSet = TRUE;
        }

        /* @req FR606 */
        if (((confChnl == FR_CHANNEL_B) || (confChnl == FR_CHANNEL_AB)) &&
            (((frmbs & MASK_FRMBS_SEOB) == MASK_FRMBS_SEOB) || /* vSS!SyntaxError */
            ((frmbs & MASK_FRMBS_CEOB) == MASK_FRMBS_CEOB) || /* vSS!ContentError */
            ((frmbs & MASK_FRMBS_SVOB) == MASK_FRMBS_SVOB)))  /* vSS!Bviolation */
        {
            DEM_REPORT(trigConfPtr->FrTrigConfPtr[trigIdx].FrTrigDemFTSlotStatusRef, DEM_EVENT_STATUS_FAILED);
            errorIsSet = TRUE;
        }

        /* @req FR629 */
        if (!errorIsSet) {
            DEM_REPORT(trigConfPtr->FrTrigConfPtr[trigIdx].FrTrigDemFTSlotStatusRef, DEM_EVENT_STATUS_PASSED);
        }
    }

    *txPending = isTxPending;

    return E_OK;
}

/**
 * Set the FLXAnFRIBCM.STXRH to 0 for the indexed message buffer.
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param msgBufferIdx
 * @return
 */
Std_ReturnType Fr_Internal_CancelTx(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint16 msgBufferIdx) {
    Std_ReturnType retval;

    retval = waitWhileBusy(&Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRIBCR, MASK_FRIBCR_IBSYH, FALSE);
    if(retval == E_OK) {
        Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRIBCM &= ~(MASK_FRIBCM_STXRH | MASK_FRIBCM_LDSH | MASK_FRIBCM_LHSH);

        Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRIBCR = (uint32)msgBufferIdx;
    } else {
        /* @req FR613 */
        DEM_REPORT(Fr_Cfg->Fr_ConfigPtr->FrCtrlParam[Fr_CtrlIdx].FrDemEventParamRef, DEM_EVENT_STATUS_FAILED);
    }
    return retval;
}

/**
 * Set the wakeup channel
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param Fr_ChnlIdx
 * @return
 */
Std_ReturnType Fr_Internal_SetWUPChannel(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, Fr_ChannelType Fr_ChnlIdx) {
    uint32 frsucc1 = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRSUCC1;
    Std_ReturnType retval;

    retval = Fr_Internal_SetCtrlChiCmd(Fr_Cfg, Fr_CtrlIdx, (uint8)CHI_CMD_CONFIG);
    if (retval == E_NOT_OK) {
        return E_NOT_OK;
    }

    frsucc1 &= ~MASK_FRSUCC1_WUCS;
    frsucc1 |= (uint32)Fr_ChnlIdx << BIT_SHIFT_FRSUCC1_WUCS;
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRSUCC1 = frsucc1;

    //Unlock sequence + CHI_CMD_READY = CONFIG_COMPLETE
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRLCK = LOCK_FIRST_WRITE;
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRLCK = LOCK_SECOND_WRITE;
    retval = Fr_Internal_SetCtrlChiCmd(Fr_Cfg, Fr_CtrlIdx, (uint8)CHI_CMD_READY);

    return retval;
}

/**
 * Read out the global time from hw register
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param Fr_CyclePtr
 * @param Fr_MacroTickPtr
 * @return
 */
Std_ReturnType  Fr_Internal_GetGlobalTime(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8* Fr_CyclePtr, uint16* Fr_MacroTickPtr) {
    Std_ReturnType retval;
    uint8 cycleCounter;
    uint16 macroTick;
    uint32 frmtccv;

    /* @req FR257 */
    // CycleCounter and Macrotick read out from the same register
    frmtccv = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRMTCCV;

    cycleCounter =  (uint8)((frmtccv & MASK_FRMTCCV_CCV) >> BIT_SHIFT_FRMTCCV_CCV);
    macroTick    = (uint16)((frmtccv & MASK_FRMTCCV_MTV));// >> BIT_SHIFT_FRMTCCV_MTV);

    /* @req FR044 */
    retval = Fr_Internal_IsSynchronous(Fr_Cfg, Fr_CtrlIdx);
    if (retval == E_NOT_OK) {
        return E_NOT_OK;
    }

    *Fr_CyclePtr     = cycleCounter;
    *Fr_MacroTickPtr = macroTick;

    return E_OK;
}

/**
 * Checks error status register if the unit is synchronous or not.
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @return
 */
Std_ReturnType Fr_Internal_IsSynchronous(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx) {
    Std_ReturnType retval = E_NOT_OK;
    boolean freeze;

    uint32 chiPocStateReg = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRCCSV;

    freeze = ((chiPocStateReg & MASK_FRCCSV_FSI) ==  MASK_FRCCSV_FSI)? TRUE : FALSE;

    if( (!freeze &&  ((chiPocStateReg & MASK_NORMAL_ACTIVE) == MASK_NORMAL_ACTIVE) ) ||
        ((chiPocStateReg & MASK_NORMAL_PASSIVE) == MASK_NORMAL_PASSIVE ) ) {
            /* Synchronized */
        retval = E_OK;
    }

    return retval;
}

/**
 * Absolute timer setup
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param Fr_AbsTimerIdx
 * @param Fr_Cycle
 * @param Fr_Offset
 * @return
 */
void Fr_Internal_SetupAbsTimer(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx, uint8 Fr_Cycle, uint16 Fr_Offset) {
    uint32 fros = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROS;
    volatile uint32 clearMask;
    volatile uint32 *baseTimerPtr;
    volatile uint32 timerReg = 0;

    if (Fr_AbsTimerIdx == 0) {
        baseTimerPtr = &Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRT0C;
        clearMask = fros & MASK_FROS_T0IS;
    } else {
        baseTimerPtr = &Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRT2C;
        clearMask = fros & MASK_FROS_T2IS;
    }

    //To ensure that the timer is halted;
    *baseTimerPtr = 0;

    timerReg |= (uint32)Fr_Offset               << BIT_SHIFT_FRTXC_TXMO;
    timerReg |= (uint32)Fr_Cycle                << BIT_SHIFT_FRTXC_TXCC;
    // AMBIGOUS - The Flexray specification does not specify if the timer is supposed to be one-shot or continuous
    timerReg |= MASK_ABS_TIMER_MODE_CONTINUOUS  << BIT_SHIFT_FRTXC_TXMS;

    //First set the parameters
    *baseTimerPtr = timerReg;

    //Clear the interrupt status flag if its set
    fros |= clearMask;
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROS = fros;

    //Then activate the timer
    timerReg |= MASK_ABS_TIMER_CTRL_ACTIVE;//      << BIT_SHIFT_FRTXC_TXRC;
    *baseTimerPtr = timerReg;
}

/**
 * Set the timer to halt.
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param Fr_AbsTimerIdx
 */
void Fr_Internal_DisableAbsTimer(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx) {
    volatile uint32 *baseTimerPtr;
    volatile uint32 timerReg;

    if (Fr_AbsTimerIdx == 0) {
        baseTimerPtr = &Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRT0C;
    } else {
        baseTimerPtr = &Fr_Cfg->hwPtr[Fr_CtrlIdx]->FRT2C;
    }

    timerReg = *baseTimerPtr;
    timerReg &= ~MASK_ABS_TIMER_CTRL_ACTIVE;
    *baseTimerPtr = timerReg;
}

/**
 * Returns the absolute timer status
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param Fr_AbsTimerIdx
 * @return
 */
boolean Fr_Internal_GetAbsTimerIrqStatus(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx) {
    uint32 fros = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROS;
    uint32 statusMask;
    boolean retval;

    if (Fr_AbsTimerIdx == 0) {
        statusMask = MASK_FROS_T0IS;
    } else {
        statusMask = MASK_FROS_T2IS;
    }

    retval = ((fros & statusMask) == statusMask)? TRUE : FALSE;

    return retval;
}

/**
 * Clear the interrupt flag for the selected absolute timer
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param Fr_AbsTimerIdx
 */
void Fr_Internal_ResetAbsTimerIsrFlag(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx) {
    volatile uint32 fros = Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROS;
    uint32 clearMask;

    //Status flag will only be cleared if its set
    if (Fr_AbsTimerIdx == 0) {
        clearMask = fros & MASK_FROS_T0IS;
    } else {
        clearMask = fros & MASK_FROS_T2IS;
    }
    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROS |= clearMask;
}

/**
 * Disables the interrupt line to the absolute timer.
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param Fr_AbsTimerIdx
 */
void Fr_Internal_DisableAbsTimerIrq(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx) {
    uint32 clearMask;

    if (Fr_AbsTimerIdx == 0) {
        clearMask = MASK_FROC_T0IE;
    } else {
        clearMask = MASK_FROC_T2IE;
    }

    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROC &= ~clearMask;
}

/**
 * Enables the interrupt line to the absolute timer.
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param Fr_AbsTimerIdx
 */
void Fr_Internal_EnableAbsTimerIrq(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint8 Fr_AbsTimerIdx) {
    uint32 setMask;

    if (Fr_AbsTimerIdx == 0) {
        setMask = MASK_FROC_T0IE;
    } else {
        setMask = MASK_FROC_T2IE;
    }

    Fr_Cfg->hwPtr[Fr_CtrlIdx]->FROC |= setMask;
}

/**
 * This function is used instead of "while". It returns when the condition is cleared or
 * when n reach MAX_WAIT_CYCLES.
 * @param regBaseAddr
 * @param mask
 * @param retCondition
 * @return
 */
static Std_ReturnType waitWhileBusy(volatile const uint32 *regBaseAddr, uint32 mask, boolean retCondition) {
    Std_ReturnType retval = E_NOT_OK;
    boolean condition;
    uint32 n;

    for (n = 0; n < MAX_WAIT_CYCLES ; n++) {
        condition = ((*regBaseAddr & mask) == mask) ? TRUE : FALSE;

        //Shall remain in the loop while the condition is false.
        if(retCondition == condition) {
            retval = E_OK;
            break;
        }
    }
    return retval;
}

/**
 * Read out message buffer header/data from Message RAM.
 * @param Fr_Cfg
 * @param Fr_CtrlIdx
 * @param msgBufferIdx
 * @param readType
 * @return
 */
static Std_ReturnType readOutMessageRamBuffer(const Fr_ContainerType *Fr_Cfg, uint8 Fr_CtrlIdx, uint16 msgBufferIdx, MsgRAMReadoutType readType) {
    volatile struct FLXA_reg *hwPtr = Fr_Cfg->hwPtr[Fr_CtrlIdx];
    Std_ReturnType retval;

    retval = waitWhileBusy(&hwPtr->FROBCR, MASK_FROBCR_OBSYS, FALSE);
    if (retval == E_NOT_OK) {
        return E_NOT_OK;
    }

    //Set to copy header and/or data
    if (readType == HEADER_AND_DATA) {
        hwPtr->FROBCM = (MASK_FROBCM_RHSS | MASK_FROBCM_RDSS);
    } else if (readType == HEADER) {
        hwPtr->FROBCM = MASK_FROBCM_RHSS;
    } else {
        hwPtr->FROBCM = MASK_FROBCM_RDSS;
    }

    hwPtr->FROBCR &= ~MASK_FROBCR_CLEAR;
    hwPtr->FROBCR |= MASK_FROBCR_REQ | (uint32)msgBufferIdx;
    //Wait while its busy transferring data
    retval = waitWhileBusy(&hwPtr->FROBCR, MASK_FROBCR_OBSYS, FALSE);
    if (retval == E_NOT_OK) {
        return E_NOT_OK;
    }

    hwPtr->FROBCR |= MASK_FROBCR_VIEW;

    return retval;
}

/**
 * Used to wrap the call to DEM.
 * @param eventId
 * @param eventStatus
 */
#if defined(USE_DEM) || defined(CFG_FR_DEM_TEST)
static inline void Fr_Internal_reportDem(Dem_EventIdType eventId, Dem_EventStatusType eventStatus) {

    /* @req FR628 */
    /* @req FR630 */
    if (eventId != DEM_EVENT_ID_NULL) {
        /* @req FR028 */
        Dem_ReportErrorStatus(eventId, eventStatus);
    }
}
#endif


