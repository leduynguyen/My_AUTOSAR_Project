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

#ifndef __GPT_JACINTO_H__
#define __GPT_JACINTO_H__

#include "Arc_Types.h"

/** Registers for GPT */
#if defined(CFG_JAC6)
#define TIM1_BASE					(0x4AE18000U + L3_OFFSET)
#define TIM2_BASE					(0x48032000U + L3_OFFSET)
#define TIM3_BASE					(0x48034000U + L3_OFFSET)
#define TIM4_BASE					(0x48036000U + L3_OFFSET)
#define TIM5_BASE					(0x48820000U + L3_OFFSET)
#define TIM6_BASE					(0x48822000U + L3_OFFSET)
#define TIM7_BASE					(0x48824000U + L3_OFFSET)
#define TIM8_BASE					(0x48826000U + L3_OFFSET)
#define TIM9_BASE					(0x4803E000U + L3_OFFSET)
#define TIM10_BASE					(0x48086000U + L3_OFFSET)
#define TIM11_BASE					(0x48088000U + L3_OFFSET)
#define TIM12_BASE					(0x4AE20000U + L3_OFFSET)
#define TIM13_BASE					(0x48828000U + L3_OFFSET)
#define TIM14_BASE					(0x4882A000U + L3_OFFSET)
#define TIM15_BASE					(0x4882C000U + L3_OFFSET)
#define TIM16_BASE					(0x4882E000U + L3_OFFSET)
#else
#define TIM1_BASE					0x4802E000U
#define TIM2_BASE					0x48040000U
#define TIM3_BASE					0x48042000U
#define TIM4_BASE					0x48044000U
#define TIM5_BASE					0x48046000U
#define TIM6_BASE					0x48048000U
#define TIM7_BASE					0x4804a000U
#define TIM8_BASE					0x481C1000U
#endif

#if defined(CFG_JAC6)
#define TIM1_REG					((TIM_HwRegType *)TIM1_BASE)
#define TIM2_REG					((TIM_HwRegType *)TIM2_BASE)
#define TIM3_REG					((TIM_HwRegType *)TIM3_BASE)
#define TIM4_REG					((TIM_HwRegType *)TIM4_BASE)
#define TIM5_REG					((TIM_HwRegType *)TIM5_BASE)
#define TIM6_REG					((TIM_HwRegType *)TIM6_BASE)
#define TIM7_REG					((TIM_HwRegType *)TIM7_BASE)
#define TIM8_REG					((TIM_HwRegType *)TIM8_BASE)
#define TIM9_REG					((TIM_HwRegType *)TIM9_BASE)
#define TIM10_REG					((TIM_HwRegType *)TIM10_BASE)
#define TIM11_REG					((TIM_HwRegType *)TIM11_BASE)
#define TIM12_REG					((TIM_HwRegType *)TIM12_BASE)
#define TIM13_REG					((TIM_HwRegType *)TIM13_BASE)
#define TIM14_REG					((TIM_HwRegType *)TIM14_BASE)
#define TIM15_REG					((TIM_HwRegType *)TIM15_BASE)
#define TIM16_REG					((TIM_HwRegType *)TIM16_BASE)
#endif
#if defined(CFG_JAC5) || defined(CFG_JAC5E)
#define TIM1_REG					((TIM_HwRegType *)TIM1_BASE)
#define TIM2_REG					((TIM_HwRegType *)TIM2_BASE)
#define TIM3_REG					((TIM_HwRegType *)TIM3_BASE)
#define TIM4_REG					((TIM_HwRegType *)TIM4_BASE)
#define TIM5_REG					((TIM_HwRegType *)TIM5_BASE)
#define TIM6_REG					((TIM_HwRegType *)TIM6_BASE)
#define TIM7_REG 					((TIM_HwRegType *)TIM7_BASE)
#define TIM8_REG					((TIM_HwRegType *)TIM8_BASE)
#endif

/*lint --e{754} We don't reference all members of the structure */
struct TIM_reg
{
    vuint32_t GPT_REVISION;				/**< 0x0000: TIDR Revision Register                 */
    vuint32_t RESERVED1[3];				/**< 0x0004: Reserved                               */
    vuint32_t GPT_CTRL;					/**< 0x0010: TIOCP_CFG Register                     */
    vuint32_t RESERVED2[3];				/**< 0x0014: Reserved                               */
    vuint32_t GPT_EOI;					/**< 0x0020: IRQ_EOI Register                       */
    vuint32_t GPT_IRQSTATUSRAW;			/**< 0x0024: IRQ RAW Status Register                */
    vuint32_t GPT_IRQSTATUS;			/**< 0x0028: IRQ Status Register                    */
    vuint32_t GPT_IRQENASET;			/**< 0x002C: IRQ Enable Set Register                */
    vuint32_t GPT_IRQENACLR;			/**< 0x0030: IRQ Enable Clear Register              */
    vuint32_t GPT_IRQWAKEUPENA;			/**< 0x0034: IRQ Wakeup Enable Register             */
    vuint32_t GPT_MODE;					/**< 0x0038: TCLR Register                          */
    vuint32_t GPT_COUNTER;				/**< 0x003C: TCRR Register                          */
    vuint32_t GPT_RELOAD;				/**< 0x0040: TLDR Counter Reload Value Register     */
    vuint32_t GPT_TRIGGER;				/**< 0x0044: TTGR Trigger Register                  */
    vuint32_t GPT_STATUS;				/**< 0x0048: TWPS Register                          */
    vuint32_t GPT_COMPARE;				/**< 0x004C: TMAR Register                          */
    vuint32_t GPT_CAPTURE1;				/**< 0x0050: TCAR1 Register                         */
    vuint32_t GPT_CONFIG;				/**< 0x0054: TSICR Register                         */
    vuint32_t GPT_CAPTURE2;				/**< 0x0058: TCAR2 Register                         */
    vuint32_t GPT_POSINC_1MS;			/**< 0x005C: TPIR Register                          */
    vuint32_t GPT_NEGINC_1MS;			/**< 0x0060: TNIR Register                          */
    vuint32_t GPT_COUNTER_1MS;			/**< 0x0064: TCVR Register                          */
    vuint32_t GPT_OVERFLOWVALUE_1MS;	/**< 0x0068: TOCR Register                          */
    vuint32_t GPT_WRAPPING_1MS;			/**< 0x006C: TOWR Register                          */
};

typedef volatile struct TIM_reg TIM_HwRegType;

#endif /* __GPT_JACINTO_H__ */
