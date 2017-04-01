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

#ifndef ISR_H_
#define ISR_H_

#include "Os.h"

struct OsResource;


/*
 * INCLUDE "RULES"
 *  Since the types and methods defined here are used by the drivers, they should
 *  include it. E.g. #include "isr.h"
 *
 *  This file is also used internally by the kernel
 *
 *
 *  irq_types.h ( Vector enums )
 *  irq.h       ( Interface )
 *
 *  Problem:
 *    Os_Cfg.h needs types from isr.h
 *
 */

/* ----------------------------[includes]------------------------------------*/
/* ----------------------------[define]--------------------------------------*/

#define ISR_TYPE_1			0
#define ISR_TYPE_2			1

/* ----------------------------[macro]---------------------------------------*/

#ifdef CFG_DRIVERS_USE_CONFIG_ISRS
#define ISR_INSTALL_ISR2( _name, _entry, _vector, _priority, _app )
#define ISR_INSTALL_ISR1(_name,_entry, _vector,_priority,_app)
#else
#define ISR_DECLARE_ISR2(_name, _entry, _unique, _vector,_priority,_app )        \
      static const OsIsrConstType _entry ## _unique = { \
            .vector = _vector,   \
            .type = ISR_TYPE_2, \
            .priority = _priority,      \
            .entry = _entry,      \
            .name = _name,      \
            .resourceMask = 0,  \
            .timingProtPtr = NULL, \
            .appOwner = _app,      \
          };                    \


#define __ISR_INSTALL_ISR2(_name, _entry, _unique, _vector,_priority,_app )        \
    do { \
      static const OsIsrConstType _entry ## _unique = { \
            .vector = _vector,   \
            .type = ISR_TYPE_2, \
            .priority = _priority,      \
            .entry = _entry,      \
            .name = _name,      \
            .resourceMask = 0,  \
            .timingProtPtr = NULL, \
            .appOwner = _app,      \
          };                    \
      (void)Os_IsrAdd( & _entry ## _unique);   \
    } while(FALSE);



#define _ISR_INSTALL_ISR2(_name,_entry, _unique, _vector,_priority,_app)        \
        __ISR_INSTALL_ISR2(_name,_entry, _unique, _vector,_priority,_app)

#define ISR_INSTALL_ISR2(_name,_entry, _vector,_priority,_app)        \
        _ISR_INSTALL_ISR2(_name,_entry, __LINE__, _vector,_priority,_app)


#define ISR_DECLARE_ISR1(_name, _entry, _unique, _vector,_priority,_app )        \
      static const OsIsrConstType _entry ## _unique = { \
            .vector = _vector,   \
            .type = ISR_TYPE_1, \
            .priority = _priority,      \
            .entry = _entry,      \
            .name = _name,      \
            .resourceMask = 0,  \
            .timingProtPtr = NULL, \
            .appOwner = _app,      \
          };                    \

#define __ISR_INSTALL_ISR1(_name, _entry, _unique, _vector,_priority,_app )        \
    do { \
      static const OsIsrConstType _entry ## _unique = { \
            .vector = _vector,   \
            .type = ISR_TYPE_1, \
            .priority = _priority,      \
            .entry = _entry,      \
            .name = _name,      \
            .resourceMask = 0,  \
            .timingProtPtr = NULL, \
            .appOwner = _app,      \
          };                    \
     (void) Os_IsrAdd( & _entry ## _unique);   \
    } while(0);

#define _ISR_INSTALL_ISR1(_name,_entry, _unique, _vector,_priority,_app)        \
        __ISR_INSTALL_ISR1(_name,_entry, _unique, _vector,_priority,_app)

#define ISR_INSTALL_ISR1(_name,_entry, _vector,_priority,_app)        \
        _ISR_INSTALL_ISR1(_name,_entry, __LINE__, _vector,_priority,_app)

#endif

/* ----------------------------[typedef]-------------------------------------*/



/* STD container : OsIsrResourceLock
 * Class: 2 and 4
 *
 * OsIsrResourceLockBudget  	1    Float in seconds (MAXRESOURCELOCKINGTIME)
 * OsIsrResourceLockResourceRef 1    Ref to OsResource
 * */

typedef struct OsIsrResourceLock {
    uint32_t lockBudget;
    uint32_t lockResourceRef; 	/* Wrong type */
} OsIsrResourceLockType;


/* STD container : OsIsrTimingProtection
 * Class: 2 and 4
 *
 * OsIsrAllInterruptLockBudget  0..1 float
 * OsIsrExecutionBudget 		0..1 float
 * OsIsrOsInterruptLockBudget 	0..1 float
 * OsIsrTimeFrame 				0..1 float
 * OsIsrResourceLock[C] 		0..*
 * */

typedef struct OsIsrTimingProtection {
    uint32_t allInterruptLockBudget;
    uint32_t executionBudget;
    uint32_t osInterruptLockBudget;
    uint32_t timeFrame;
    uint32_t resourceLock;		/* Wrong type */
} OsIsrTimingProtectionType;

typedef struct {
    void   		*curr;	/* Current stack ptr( at swap time ) */
    void   		*top;	/* Top of the stack( low address )   */
    uint32		size;	/* The size of the stack             */
} OsIsrStackType;


/* STD container : OsIsr
 * Class: ALL
 *
 * OsIsrCategory:				1    CATEGORY_1 or CATEGORY_2
 * OsIsrResourceRef:			0..* Reference to OsResources
 * OsIsrTimingProtection[C] 	0..1
 * */

typedef struct OsIsrConst {
    const char 		*name;
    uint8_t			core;
    uint8_t			priority;
    int16_t			vector;
    int16_t 		type;
    void 			(*entry)( void );
    ApplicationType	appOwner;
    /* Mapped against OsIsrResourceRef */
    uint32_t		resourceMask;
#if (  OS_USE_ISR_TIMING_PROT == STD_ON )
    /* Mapped against OsIsrTimingProtection[C] */
    OsIsrTimingProtectionType *timingProtPtr;
#else
    void *timingProtPtr;
#endif
} OsIsrConstType;

/*
 *
 */
typedef struct OsIsrVar{
    ISRType id;
#if defined(CFG_OS_ISR_HOOKS)
    ISRType preemtedId;
#endif
//	OsIsrStackType		stack;
    int					state;
    const OsIsrConstType *constPtr;
#if defined(CFG_TMS570) || defined(CFG_ARMV7_AR)
    int16_t activeVector;
#endif

    /* List of resource held by this ISR */
    TAILQ_HEAD(,OsResource) resourceHead;
} OsIsrVarType;


/* ----------------------------[functions]-----------------------------------*/

#if OS_ISR_MAX_CNT!=0
extern OsIsrVarType Os_IsrVarList[OS_ISR_MAX_CNT];
#endif

void Os_IsrInit( void );
ISRType Os_IsrAdd( const OsIsrConstType * isrPtr );
void Os_IsrAddWithId( const OsIsrConstType * isrPtr, ISRType id );
void Os_IsrRemove( int16_t vector);

void Os_IsrGetStackInfo( OsIsrStackType *stack );
void *Os_Isr( void *stack, int16_t vector);
#if defined(CFG_TMS570)
void *Os_Isr_cr4( void *stack, int16_t virtualVector, int16_t vector );
#endif
#if defined(CFG_ARM_CM3)
void Os_Isr_cm3( int16_t vector );
void TailChaining(void *stack);
#endif

const OsIsrVarType *Os_IsrGet( ISRType id );
ApplicationType Os_IsrGetApplicationOwner( ISRType id );
void Os_IsrResourceAdd( struct OsResource *rPtr, OsIsrVarType *isrPtr);
const OsIsrVarType * Os_IsrGetFromVector( int16_t vector );
ISRType Os_IsrGetIdFromVector( int16_t vector );


#endif /*ISR_H_*/
