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

#include "os_i.h"
#include "isr.h"
#include "irq_types.h"
#include "core_cr4.h"

//#pragma GCC optimize "O3"

typedef void (* IrqFuncType)(void);

extern TaskType Os_Arc_CreateIsr( void (*entry)(void ), uint8_t prio, const char *name );
IrqFuncType Irq_VectorTable[NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS];

static inline void Irq_Setup( void ) {
    vimREG->FIRQPR0 = 0x0;
    vimREG->FIRQPR1 = 0x0;
    vimREG->FIRQPR2 = 0x0;
    vimREG->FIRQPR3 = 0x0;
}

void Irq_Init( void ) {
    Irq_Setup();
    //Irq_Enable();
}

#define MASK_L		0
#define MASK_H		1

uint32_t prioMask[32][4];	/* 128 */
uint16_t Irq_StackPrio[16] ;
uint16_t Irq_Index =  0;

/**
 *
 * Interrupt channels can be found in the datasheet (not RM) under
 * "Interrupt Request Assignments", e.g. http://www.ti.com/lit/ds/spns192a/spns192a.pdf
 *
 * @param stack_p Ptr to the current stack.
 */
void *Irq_Entry( void *stack_p ) {

    uint16_t channel = vimREG->IRQINDEX;

    if( channel == 0 ) {
        /* No Pending Interrupt */
        return stack_p;
    }

    /* Adjust to real channel */
    channel -= 1;

    /* Check for software interrupt */
    if( channel == SSI ) {
        /* First get what software register caused the interrupt */
        uint32 reg = systemREG1->SSIVEC;		/* also clears SSI_FLAG */
        if( (reg & 0xff) == 0 ) {
            /* Nothing pending....*/
            return stack_p;
        }

        channel = (reg >> 8) & 0xff;
    }

//	Irq_Index++;

    Os_Isr(stack_p, channel );

    return stack_p;
}


/**
 *
 * @param priority The priority of the ISR we are about to start
 */
void Irq_SOI3( uint8_t priority ) {
    /* Disable lower prio interrupts */
    Irq_StackPrio[++Irq_Index] = priority; 	/* save prio */

    /* It seems that we need to clear the enable of the interrupt here
     * because not doing it and enabling interrupts will cause a Data Exception
     * In the same time we must also set the priority mask according to the
     * priority of this ISR.
     * */

    vimREG->REQENACLR0 = (vimREG->REQENACLR0 ^ prioMask[priority][0]);
    vimREG->REQENACLR1 = (vimREG->REQENACLR1 ^ prioMask[priority][1]);
    vimREG->REQENACLR2 = (vimREG->REQENACLR2 ^ prioMask[priority][2]);
    vimREG->REQENACLR3 = (vimREG->REQENACLR3 ^ prioMask[priority][3]);
}


void Irq_EOI( int16_t vector ) {
    (void)vector;
    /* Enable higher prio interrupts (more interrupts )  */
    --Irq_Index;
    vimREG->REQENASET0 = prioMask[Irq_StackPrio[Irq_Index]][0];
    vimREG->REQENASET1 = prioMask[Irq_StackPrio[Irq_Index]][1];
    vimREG->REQENASET2 = prioMask[Irq_StackPrio[Irq_Index]][2];
    vimREG->REQENASET3 = prioMask[Irq_StackPrio[Irq_Index]][3];

}

/**
 * Attach an ISR type 1 to the interrupt controller.
 *
 * @param entry
 * @param int_ctrl
 * @param vector
 * @param prio
 */
void Irq_AttachIsr1( void (*entry)(void), void *int_ctrl, uint32_t vector, uint8_t prio) {

    // IMPROVEMENT: Use NVIC_InitVector(vector, osPrioToCpuPio(pcb->prio)); here
}

/**
 * NVIC prio have priority 0-15, 0-highest priority.
 * Autosar does it the other way around, 0-Lowest priority
 *
 * Autosar    NVIC
 *   31        0
 *   30        0
 *   ..
 *   0         15
 *   0         15
 * @param prio
 * @return
 */
static inline uint8_t osPrioToCpuPio( uint8_t prio ) {
    ASSERT(prio<32);
    prio = 31 - prio;
    return (prio>>1);
}


/*
 * Channels and priority
 *
 * Default VIM Channel interrupt
 * Priority: Low Channel = High Priority
 *
 *
 *
 */


void Irq_EnableVector2( IrqFuncType func,  int16_t vector, uint16_t type,  uint8_t priority, int core ) {

    if (vector < NUMBER_OF_INTERRUPTS_AND_EXCEPTIONS) {

        if( type == ISR_TYPE_1 ) {
            /* don't mask FIQs */
            priority = 31;
        }

        /* priority is from 0 to 31, 0 = lowest, 31-highest - priority
         * The mask should be set to on all lower prio's that this one
         * */
        for(int i=0; i < priority ; i++  ) {
            prioMask[i][vector/32] |= (1 << (vector%32));
        }

        /* Assume this is done in non-interrupt context, set to lowest prio */
        vimREG->REQENASET0 = prioMask[0][0];
        vimREG->REQENASET1 = prioMask[0][1];
        vimREG->REQENASET2 = prioMask[0][2];
        vimREG->REQENASET3 = prioMask[0][3];

        /* ISR_TYPE_1 is FIQ interrupt so set that.*/
        if( type == ISR_TYPE_1 ) {
            volatile unsigned *p = (&vimREG->FIRQPR0);
            p[vector/32] |= (1 << (vector%32));
            Irq_VectorTable[vector] = func;
        }

    } else {
        /* Invalid vector! */
        ASSERT(0);
    }
}

void irqDummy( void ) {

}
void irqDummy2( void ) {

}

#define GPIO_BASE 0xFFF7BC00
#define GPIO_REG (*(GPIO_regs *)GPIO_BASE)

typedef volatile struct  {
    uint32_t GIOGCR0;    /* 00h GIO Global Control Register Section 25.5.1 */
    uint32_t : 32; 	/* res */
    uint32_t GIOINTDET;  /* 08h GIO Interrupt Detect Register Section 25.5.2 */
    uint32_t GIOPOL;     /* 0Ch GIO Interrupt Polarity Register Section 25.5.3 */
    uint32_t GIOENASET;  /* 10h GIO Interrupt Enable Set Register Section 25.5.4.1 */
    uint32_t GIOENACLR;  /* 14h GIO Interrupt Enable Clear Register Section 25.5.4.2 */
    uint32_t GIOLVLSET;  /* 18h GIO Interrupt Priority Set Register Section 25.5.5.1 */
    uint32_t GIOLVLCLR;  /* 1Ch GIO Interrupt Priority Clear Register Section 25.5.5.2 */
    uint32_t GIOFLG;     /* 20h GIO Interrupt Flag Register Section 25.5.6 */
    uint32_t GIOOFF1;    /* 24h GIO Offset 1 Register Section 25.5.7 */
    uint32_t GIOOFF2;    /* 28h GIO Offset 2 Register Section 25.5.8 */
    uint32_t GIOEMU1;    /* 2Ch GIO Emulation 1 Register Section 25.5.9 */
    uint32_t GIOEMU2;    /* 30h GIO Emulation 2 Register Section 25.5.10 */
    uint32_t GIODIRA;    /* 34h GIO Data Direction Register Section 25.5.11 */
    uint32_t GIODINA;    /* 38h GIO Data Input Register Section 25.5.12 */
    uint32_t GIODOUTA;   /* 3Ch GIO Data Output Register Section 25.5.13 */
    uint32_t GIODSETA;   /* 40h GIO Data Set Register Section 25.5.14 */
    uint32_t GIODCLRA;   /* 44h GIO Data Clear Register Section 25.5.15 */
    uint32_t GIOPDRA;    /* 48h GIO Open Drain Register Section 25.5.16 */
    uint32_t GIOPULDISA; /* 4Ch GIO Pull Disable Register Section 25.5.17 */
    uint32_t GIOPSLA;    /* 50h GIO Pull Select Register Section 25.5.18 */
    uint32_t GIODIRB;    /* 54h GIO Data Direction Register Section 25.5.11 */
    uint32_t GIODINB;    /* 58h GIO Data Input Register Section 25.5.12 */
    uint32_t GIODOUTB;   /* 5Ch GIO Data Output Register Section 25.5.13 */
    uint32_t GIODSETB;   /* 60h GIO Data Set Register Section 25.5.14 */
    uint32_t GIODCLRB;   /* 64h GIO Data Clear Register Section 25.5.15 */
    uint32_t GIOPDRB;    /* 68h GIO Open Drain Register Section 25.5.16 */
    uint32_t GIOPULDISB; /* 6Ch GIO Pull Disable Register Section 25.5.17 */
    uint32_t GIOPSLB;    /* 70h GIO Pull Select Register Section 25.5.18 */
} GPIO_regs;

void SetOutputA( uint8_t pin, uint8_t level ) {
    if( level == 0) {
        GPIO_REG.GIODCLRA |= (1<<pin);
    } else {
        GPIO_REG.GIODOUTA |= (1<<pin);
    }
    __asm volatile(" isb");
}

void enablePinInt( uint32_t pin, uint8_t xxx ) {
    GPIO_REG.GIOINTDET &= ~(1<<pin);	/* 0-either falling or rising edle, 1 -both */
    GPIO_REG.GIOPOL |= (1<<pin);		/* 0- falling, 1- Rising Edge */
    if( xxx == 1) {
        GPIO_REG.GIOLVLSET |= (1<<pin);
    } else {
        GPIO_REG.GIOLVLSET &= ~(1<<pin);
    }
    GPIO_REG.GIOFLG |= (1<<pin); 		/* Clear interrupt request */
    GPIO_REG.GIOENASET |= (1<<pin);		/* 1 - enabled */
}

void enablePinOutA( uint32_t pin ) {
    GPIO_REG.GIODIRA |= (1<<pin);		/* 1-out */
    GPIO_REG.GIOPDRA &= ~(1<<pin);		/* 0-no open drain, 1-open drain */
}

/**
 * Setup pins to generate IRQ on write to pin.
 *
 * Here we use GIOA[0] and GIOA[1] to generate real interrupts to the CPU.
 * GIOA[0] connected to GIO interrupt A (vector 9)
 * GIOA[1] connected to GIO interrupt B (vector 23)
 */

void setupPinsForIrq( void ) {
    /* PENA and clocks already running from MCU */

    /* Normal state */
    GPIO_REG.GIOGCR0 = 1;

    /* Out pins */
    enablePinOutA(0);
    enablePinOutA(1);
    enablePinInt(0, 1);			/* Connect to Level A (vector 9 )*/
    enablePinInt(1, 0 );		/* Connect to Level B (vector 23 )*/
}



/**
 * Generates a soft interrupt
 *
 * Note! This implementation uses real HW interrupts
 * for vector 9 and 23
 *
 * @param vector
 */
void Irq_GenerateSoftInt( IrqType vector ) {
    imask_t flags;
    static uint8_t pinSetup = 0;

    if( pinSetup == 0 ) {
        setupPinsForIrq();
        pinSetup = 1;
    }

    Irq_Save(flags);
    if( vector == DIO_LEVEL_0) {
        SetOutputA(0,1);
        SetOutputA(0,0);
    } else if (vector == DIO_LEVEL_1 ) {
        SetOutputA(1,1);
        SetOutputA(1,0);
    } else if (vector == RESERVED ) { /* fake vector */
        SetOutputA(2,1);
        SetOutputA(2,0);
    } else {
        /* Use software interrupt for the rest */
        systemREG1->SSIR1 = (0x75 << 8) | vector;
    }
    Irq_Restore(flags);
}

void Irq_AckSoftInt( IrqType vector ) {
    if( vector == DIO_LEVEL_0) {
        GPIO_REG.GIOFLG = 0x001;	/* GPIOA[0] */
    } else if (vector == DIO_LEVEL_1 ) {
        GPIO_REG.GIOFLG = 0x002;	/* GPIOA[1] */
    } else if (vector == RESERVED ) { /* fake vector */
    } else {
        systemREG1->SSIVEC;			/* SSI */
    }
}

/**
 * Get the current priority from the interrupt controller.
 * @param cpu
 * @return
 */
uint8_t Irq_GetCurrentPriority( Cpu_t cpu) {

    uint8_t prio = 0;

    // SCB_ICSR contains the active vector
    return prio;
}

typedef struct {
    uint32_t dummy;
} exc_stack_t;


