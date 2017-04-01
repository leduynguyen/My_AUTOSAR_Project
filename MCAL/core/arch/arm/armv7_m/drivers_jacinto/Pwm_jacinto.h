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

#ifndef __PWM_JACINTO_H__
#define __PWM_JACINTO_H__

#define TIOCP_CFG_SOFTRESET_BITMASK	0x00000001U

#define TCLR_PT_PULSE   			0x00000000U
#define TCLR_PT_TOGGLE  			0x00001000U
#define TCLR_TRG_MASK  				0x00000C00U
#define TCLR_TRG_NO   				0x00000000U
#define TCLR_TRG_OVRFLW				0x00000400U
#define TCLR_TRG_OVRFLW_AND_MATCH   0x00000800U
#define TCLR_SCPWM_MASK 			0x00000080U
#define TCLR_SCPWM_POS_POLARITY 	0x00000000U
#define TCLR_SCPWM_NEG_POLARITY 	0x00000080U
#define TCLR_CE_ENABLE  			0x00000040U
#define TCLR_CE_DISABLE  			0x00000000U
#define TCLR_PRE_ENABLE   			0x00000020U
#define TCLR_PRE_DISABLE   			0x00000000U
#define TCLR_MASK_PTV   			0x0000001CU
#define TCLR_AR_AUTO_RELOAD			0x00000002U
#define TCLR_AR_ONE_SHOT  			0x00000000U
#define TCLR_ST_START_TIMER_MASK	0x00000001U
#define TCLR_ST_START_TIMER			0x00000001U
#define TCLR_ST_STOP_TIMER			0x00000000U

#define TCLR_PTV_BIT_POS   			2u


#define TIM_FORCE_IDLE_MODE      0x0
#define TIM_NO_IDLE_MODE         0x4
#define TIM_SMART_IDLE_MODE      0x8
#define TIM_SMART_IDLE_WKUP_MODE 0xC

#define TIM_REG_RP_WNP  0
#define TIM_REG_RP_WP   4
#define TIM_REG_RNP_WNP 8


typedef volatile struct timBase
{
    uint32_t TIDR;          /**< 0x0000: Identification Register                */
    uint32_t : 32U;         /**< 0x0004: Reserved                               */
    uint32_t : 32U;         /**< 0x0008: Reserved                               */
    uint32_t : 32U;         /**< 0x000C: Reserved                               */
    uint32_t TIOCP_CFG;     /**< 0x0010: Timer OCP Configuration Register       */
    uint32_t : 32U;         /**< 0x0014: Reserved                               */
    uint32_t : 32U;         /**< 0x0018: Reserved                               */
    uint32_t : 32U;         /**< 0x001C: Reserved                               */
    uint32_t IRQ_EOI;       /**< 0x0020: Timer IRQ End-Of-Interrupt Register    */
    uint32_t IRQSTATUS_RAW; /**< 0x0024: Timer IRQSTATUS Raw Register           */
    uint32_t IRQSTATUS;     /**< 0x0028: Timer IRQSTATUS Register               */
    uint32_t IRQENABLE_SET; /**< 0x002C: Timer IRQENABLE Set Register           */
    uint32_t IRQENABLE_CLR;	/**< 0x0030: Timer IRQENABLE Clear Register         */
    uint32_t IRQWAKEEN;     /**< 0x0034: Timer IRQ Wakeup Enable Register       */
    uint32_t TCLR;          /**< 0x0038: Timer Control Register                 */
    uint32_t TCRR;          /**< 0x003C: Timer Counter Register                 */
    uint32_t TLDR;          /**< 0x0040: Timer Load Register     				*/
    uint32_t TTGR;          /**< 0x0044: Timer Trigger Register                 */
    uint32_t TWPS;          /**< 0x0048: Timer Write Posted Status Register     */
    uint32_t TMAR;          /**< 0x004C: Timer Match Register                   */
    uint32_t TCAR1;         /**< 0x0050: Timer Capture Register                 */
    uint32_t TSICR;         /**< 0x0054: Timer Synchronous Interface Control Register */
    uint32_t TCAR2;         /**< 0x0058: Timer Capture Register                 */
#if defined(CFG_JAC6)
    uint32_t TPIR;         	/**< 0x005C: TPIR Register                          */
    uint32_t TNIR;         	/**< 0x0060: TNIR Register                          */
    uint32_t TCVR;        	/**< 0x0064: TCVR Register                          */
    uint32_t TOCR;  		/**< 0x0068: TOCR Register                          */
    uint32_t TOWR;       	/**< 0x006C: TOWR Register                          */
#endif
} timBASE_t;

#if defined(CFG_JAC5) || defined(CFG_JAC5E)
#define timREG1 ((timBASE_t *)0x4802E000U)
#define timREG2 ((timBASE_t *)0x48040000U)
#define timREG3 ((timBASE_t *)0x48042000U)
#define timREG4 ((timBASE_t *)0x48044000U)
#define timREG5 ((timBASE_t *)0x48046000U)
#define timREG6 ((timBASE_t *)0x48048000U)
#define timREG7 ((timBASE_t *)0x4804a000U)
#define timREG8 ((timBASE_t *)0x481C1000U)
#elif defined(CFG_JAC6)
#define timREG1 ((timBASE_t *)(0x4AE18000U + L3_OFFSET))
#define timREG2 ((timBASE_t *)(0x48032000U + L3_OFFSET))
#define timREG3 ((timBASE_t *)(0x48034000U + L3_OFFSET))
#define timREG4 ((timBASE_t *)(0x48036000U + L3_OFFSET))
#define timREG5 ((timBASE_t *)(0x48820000U + L3_OFFSET))
#define timREG6 ((timBASE_t *)(0x48822000U + L3_OFFSET))
#define timREG7 ((timBASE_t *)(0x48824000U + L3_OFFSET))
#define timREG8 ((timBASE_t *)(0x48826000U + L3_OFFSET))
#define timREG9 ((timBASE_t *)(0x4803E000U + L3_OFFSET))
#define timREG10 ((timBASE_t *)(0x48086000U + L3_OFFSET))
#define timREG11 ((timBASE_t *)(0x48088000U + L3_OFFSET))
#define timREG12 ((timBASE_t *)(0x4AE20000U + L3_OFFSET))
#define timREG13 ((timBASE_t *)(0x48828000U + L3_OFFSET))
#define timREG14 ((timBASE_t *)(0x4882A000U + L3_OFFSET))
#define timREG15 ((timBASE_t *)(0x4882C000U + L3_OFFSET))
#define timREG16 ((timBASE_t *)(0x4882E000U + L3_OFFSET))
#endif

#endif /* __PWM_JACINTO_H__ */
