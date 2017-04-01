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

#ifndef IRQ_JACINTO_H_
#define IRQ_JACINTO_H_

/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */

/**
 * @brief Configuration of the Cortex-M3 Processor and Core Peripherals
 */
#define __MPU_PRESENT             0

#define __CM3_REV               0x200
#define __NVIC_PRIO_BITS          4 /*!< STM32 uses 7 Bits for the Priority Levels    */
#define __Vendor_SysTickConfig    0 /*!< Set to 1 if different SysTick Config is used */
#define __CHECK_DEVICE_DEFINES      1

/* Some defines used */
#define  SCB_CFSR_INVSTATE                   ((uint32_t)0x00020000)
#define  SCB_CFSR_INVPC                      ((uint32_t)0x00040000)
#define  SCB_CFSR_BFARVALID                  ((uint32_t)0x00008000)


#if defined(CFG_JAC5) || defined(CFG_JAC5E)
typedef enum {
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
    HardFault_IRQn              = -13,    /*!< 3 Cortex-M3 Hard Fault Interrupt                     */
    MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
    BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
    UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
    SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
    DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
    PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
    SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */

/******  jacinto specific Interrupt Numbers *********************************************************/

    /* The jacinto Cortex-M3 have 64 interrupts described in ECO manual:
     * "1.6.4 Interrupt Requests to Media Controller NVICs"
     *
     * These interrupts are the default mapping and can be REPLACED by using the MUX feature.
     * The Cortex-M3 processor exceptions (NMI, etc) can't be replaced but the rest can.
     *
     * Using the Media_Controller_INTMUX_x will give you an additional 83 interrupt sources.
     */

    XLATE_MMU_FAULT_IRQ, /* 0 */
    UNICACHE_MMU_IRQ,
    CTM_TIM_EVENT1_IRQ,
    HWSEM_M4_IRQ,
    ICE_NEMU_IRQ,
    IPU_IMP_FAULT_IRQ,
    CTM_TIM_EVENT2_IRQ,
    HDMI_IRQ, /* First mux'able i.e. corresponds to intmux[0]; */
    SPIINT1_IRQ, /* intmux[1]; Muxed here in Mcu_Arc_Jacinto.c. Changed from Reserved1 to SPIINT1 */
    TINT1_IRQ,
    TINT2_IRQ,
    TINT3_IRQ,
    TINT4_IRQ,
    TINT5_IRQ,
    TINT6_IRQ,
    TINT7_IRQ,
    ISSINT0_IRQ, /*16*/
    ISSINT1_IRQ,
    ISSINT2_IRQ,
    ISSINT3_IRQ,
    ISSINT4_IRQ,
    ISSINT5_IRQ,
    HDVICPMBOXINT2_IRQ,
    HDVICPCONT1SYNC_IRQ,
    HDVICPCONT2SYNC_IRQ,
    I2CINT0_IRQ,
    I2CINT1_IRQ,
    UARTINT0_IRQ,
    UARTINT1_IRQ,
    UARTINT2_IRQ,
    GPIO0INT0_IRQ,
    GPIO0INT1_IRQ,
    VCPINT_IRQ,/*32*/
    USBSSINT_IRQ,
    USBINT0_IRQ,
    USBINT1_IRQ,
    TSC_ADC_MUX_IRQ, /* Reserved2, intmux[29]; Muxed here in Mcu_Arc_Jacinto.c */
    MB1INT2_IRQ,
    MB1INT3_IRQ,
    SR_CORE_IRQ,
    I2CINT2_IRQ,/* intmux[33]; Muxed here in Mcu_Arc_Jacinto.c, original: Reserved3 */
    I2CINT3_IRQ,/* intmux[34]; Muxed here in Mcu_Arc_Jacinto.c, original: Reserved4 */
    SPIINT2_IRQ, /* intmux[35]; Muxed here in Mcu_Arc_Jacinto.c. Changed from Reserved5 to SPIINT2 */
    SR_ARM_IRQ,
    HDVPSSINT2_IRQ,
    HDVPSSINT3_IRQ,
    EDMA3CC_INT4_IRQ,
    EDMA3CC_INT5_IRQ,
    EMACSWRXTHR_IRQ,/*48*/
    EMACSWRXINT_IRQ,
    EMACSWTXINT_IRQ,
    EMACSWMISC_IRQ,
    MCATXINT0_IRQ,
    MCARXINT0_IRQ,
    MCATXINT1_IRQ,
    MCARXINT1_IRQ,
    GPIO1INT0_IRQ,
    GPIO1INT1_IRQ,
    SDINT0_IRQ,
    SPIINT0_IRQ,
    DCAN0_IRQ_INT0,/* intmux[53]; Muxed here in Mcu_Arc_Jacinto.c */
    DCAN1_IRQ_INT0,/* intmux[54]; Muxed here in Mcu_Arc_Jacinto.c */
    GPIO2INT0_IRQ,
    GPIO2INT1_IRQ, /*63 intmux[56]; */
} IRQn_Type;

#if defined(CFG_JAC5)
/* MUX values. We set up a default and this could be altered in Mcu_Arc_Jacinto.c */
typedef enum{
    SATAINT = 1,
    SDINT1,
    SDINT2,
    I2CINT2,
    I2CINT3,
    GPIO3INT0,
    GPIO3INT1,
    GFXINT,
    UARTINT3,
    UARTINT4,
    UARTINT5,
    FDIFINT1,
    PCIINT0,
    PCIINT1,
    PCIINT2,
    PCIINT3,
    DCAN0INT0,
    DCAN0INT1,
    DCAN0PARIT,
    DCAN1INT0,
    DCAN1INT1,
    DCAN1PARIT,
    MLBSYSINT0,
    MLBSYSINT1,
    MLBINT,
    RTCINT,
    RTCALARMINT,
    IDEINTR,
    MCATXINT2,
    MCARXINT2,
    MCBSPINT,
    GPMCINT,
    MCATXINT3,
    MCARXINT3,
    MCATXINT4,
    MCARXINT4,
    MCATXINT5,
    MCARXINT5,
    EDMA3TC0_ERRINT,
    EDMA3TC1_ERRINT,
    EDMA3TC2_ERRINT,
    EDMA3TC3_ERRINT,
    SPIINT1,
    SPIINT2,
    SPIINT3,
    Reserved8,
    SR_HDVICP_IRQ,
}IntMux_Type;
# elif defined (CFG_JAC5E)
typedef enum{
    DEFAULT_INTERRUPT = 0,
    ReservedEco0,
    SDINT1,
    SDINT2,
    I2CINT2,
    I2CINT3,
    GPIOINT3A,
    GPIOINT3B,
    GFXINT, /* 8 */
    UARTINT3,
    UARTINT4,
    UARTINT5,
    ReservedEco1,
    PCIINT0,
    PCIINT1,
    PCIINT2,
    PCIINT3, /* 16 */
    DCAN0INT0,
    DCAN0INT1,
    DCAN0PARITY,
    DCAN1INT0,
    DCAN1INT1,
    DCAN1PARITY,
    MLBSYSINT0,
    MLBSYSINT1, /* 24 */
    MLBINT,
    RTCINT,
    RTCALARMINT,
    ReservedEco2,
    MCATXINT2,
    MCARXINT2,
    MCBSPINT,
    GPMCINT, /* 32 */
    MCATXINT3,
    MCARXINT3,
    MCATXINT4,
    MCARXINT4,
    MCATXINT5,
    MCARXINT5,
    TCERRINT0,
    TCERRINT1, /* 40 */
    TCERRINT2,
    TCERRINT3,
    SPIINT1,
    SPIINT2,
    SPIINT3,
    ReservedEco3,
    ReservedEco4,
    PRUSS_EVTOUT0, /* 48 */
    PRUSS_EVTOUT1,
    PRUSS_EVTOUT2,
    PRUSS_EVTOUT3,
    PRUSS_EVTOUT4,
    PRUSS_EVTOUT5,
    PRUSS_EVTOUT6,
    PRUSS_EVTOUT7,
    EPWM0_TZINT, /* 56 */
    EPWM1_TZINT,
    EPWM2_TZINT,
    EPWM0INT,
    EPWM1INT,
    EPWM2INT,
    ReservedEco5,
    EQEP1INT,
    EQEP2INT, /* 64 */
    ECAP0INT,
    ECAP1INT,
    ECAP2INT,
    GPIOINT4A,
    GPIOINT4B,
    GPIOINT5A,
    GPIOINT5B,
    ADC_TSC_GENINT, /* 72 */
    UARTINT6,
    UARTINT7,
    DHWAINT2,
    DHWAMMU2,
    EQEP0INT,
    MB3INT2,
    MB3INT1,
    ReservedEco6, /* 80 */
    ReservedEco7,
    ReservedEco8,
    ReservedEco9
}IntMux_Type;
#endif

#elif defined(CFG_JAC6)

typedef enum {
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
    HardFault_IRQn              = -13,    /*!< 3 Cortex-M3 Hard Fault Interrupt                     */
    MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
    BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
    UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
    SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
    DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
    PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
    SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */

/******  jacinto specific Interrupt Numbers *********************************************************/
    /* IPU specific interrupts */
    XLATE_MMU_FAULT_IRQ,
    UNICACHE_MMU_IRQ,
    CTM_TIM_EVENT1_IRQ,
    HWSEM_M4_IRQ,
    ICE_NEMU_IRQ,
    IPU_IMP_FAULT_IRQ,
    CTM_TIM_EVENT2_IRQ,

    /*
     * MUX:ed interrupts
     */

    /* Timers */
    TINT1_IRQ = 7,    /* 23 */
    TINT2_IRQ,        /* 24 */
    TINT3_IRQ,
    TINT4_IRQ,
    TINT5_IRQ,        /* 27/0x1B */
    TINT6_IRQ,
    TINT7_IRQ,
    TINT8_IRQ,
    TINT9_IRQ,
    TINT10_IRQ,
    TINT11_IRQ,
    TINT12_IRQ,
    TINT13_IRQ,
    TINT14_IRQ,
    TINT15_IRQ,
    TINT16_IRQ,

    /* CAN */
    DCAN0_IRQ_INT0,
    DCAN1_IRQ_INT0,

    /* ETH */
    GMAC_SW_IRQ_RX_THRESH_PULSE,  /* mapped to IPU1_IRQ_69 */
    GMAC_SW_IRQ_RX_PULSE,         /* mapped to IPU1_IRQ_70 */
    GMAC_SW_IRQ_TX_PULSE,         /* mapped to IPU1_IRQ_71 */
//    GMAC_SW_IRQ_MISC_PULSE,

    /* SPI */
    MCSPI1_IRQ,
    MCSPI2_IRQ,
    MCSPI3_IRQ,
    MCSPI4_IRQ,

    /* LIN */
    UARTINT1_IRQ,
    UARTINT2_IRQ,
    UARTINT3_IRQ,

    /* I2C */
    I2CINT1_IRQ,
    I2CINT2_IRQ,
    I2CINT3_IRQ,
    I2CINT4_IRQ,
    I2CINT5_IRQ,

    /* ePWM */
    PWMSS1_ePWM0INT_IRQ,
    PWMSS2_ePWM1INT_IRQ,
    PWMSS3_ePWM2INT_IRQ,

    /* GPIO */
    GPIO5_IRQ_1,

    /* MailBox */
    MAILBOX1_IRQ_USER2,

    DUMMY_LAST_IRQ = 64,              /* Make compilation error if the list is too long */
} IRQn_Type;

/* MUX values. We set up a default and this could be altered in Mcu_Arc_Jacinto.c */
typedef enum{
    GPIO5INT1 = 28,
    TIMER1INT = 32,
    TIMER2INT = 33,
    TIMER3INT = 34,
    TIMER4INT = 35,
    TIMER5INT = 36,
    TIMER6INT = 37,
    TIMER7INT = 38,
    TIMER8INT = 39,
    TIMER9INT = 40,
    TIMER10INT = 41,
    TIMER11INT = 42,
    MCSPI4INT   = 43,
    TIMER12INT = 90,
    I2C1INT   = 51,
    I2C2INT   = 52,
    I2C5INT   = 55,
    I2C3INT   = 56,
    I2C4INT   = 57,
    MCSPI1INT   = 60,
    MCSPI2INT   = 61,
    UARTINT1  = 67,
    UARTINT2  = 68,
    UARTINT3  = 69,
    MCSPI3INT   = 86,
    MB1USR2INT	= 134,
    PWMSS1_IRQ_ePWM0INT = 207,
    PWMSS2_IRQ_ePWM1INT = 208,
    PWMSS3_IRQ_ePWM2INT = 209,
    DCAN0INT0 = 222,
    DCAN1INT0 = 225,
    MBXINT = 250,
    GMACSWIRQ_RX_THRESH_PULSE  = 334,
    GMACSWIRQ_RX_PULSE         = 335,
    GMACSWIRQ_TX_PULSE         = 336,
    GMACSW_RQ_MISC_PULSE       = 337,
    TIMER13INT = 339,
    TIMER14INT = 340,
    TIMER15INT = 341,
    TIMER16INT = 342,
}IntMux_Type;

#else
#error "Unknown type"
#endif

typedef IRQn_Type IrqType;


#if defined(CFG_ARM_CM3)
#include "core_cm3.h"
#elif defined(CFG_ARM_CM4)
#define __FPU_PRESENT	1U
#define __CM4_REV		0x0000U
#include "core_cm4.h"
#else
#error No CPU defined
#endif



 /* Offset from start of exceptions to interrupts
  * Exceptions have negative offsets while interrupts have positive
  */
 #define IRQ_INTERRUPT_OFFSET  16

 #define Irq_SOI()

 /* Total number of interrupts and exceptions
  */

#if defined (CFG_JAC5) || defined (CFG_JAC5E)
#define NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS (GPIO2INT1_IRQ+IRQ_INTERRUPT_OFFSET+1)
#elif defined (CFG_JAC6)
#define NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS (DUMMY_LAST_IRQ+IRQ_INTERRUPT_OFFSET+1)
#else
#error "Unknown cpu type"
#endif


 typedef enum {
    PERIPHERAL_CLOCK_DCAN,
    PERIPHERAL_CLOCK_UART,
    PERIPHERAL_CLOCK_I2C,
    PERIPHERAL_CLOCK_SPI,
    PERIPHERAL_CLOCK_GMAC_SW,
    PERIPHERAL_CLOCK_TIMER_PWM,
#if defined(CFG_JAC6)
    PERIPHERAL_CLOCK_EPWM,
#endif
    PERIPHERAL_CLOCK_GPT,
    PERIPHERAL_CLOCK_SCTM
 } Mcu_Arc_PeriperalClock_t;


 typedef enum {
     CPU_0 = 0,
 } Cpu_t;


#endif /* IRQ_JACINTO_H_ */
