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

/** @tagSettings DEFAULT_ARCHITECTURE=PPC|MPC5607B|MPC5645S */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#ifndef MCU_FCCU_H_
#define MCU_FCCU_H_


#define STATE_NORMAL    0
#define STATE_CONFIG    1
#define STATE_ALARM     2
#define STATE_FAULT     3

#define OP_NOOP             0
#define OP_CONFIG           1
#define OP_NORMAL           2
#define OP_READ_CFS         9
#define OP_READ_NCFS        10
#define OP_CLEARING_CFS     11

/* RGM FCCU bits */
#define F_FCCU_HARD_BIT     (1uL<<(15u-1u))
#define F_FCCU_SAFE_BIT     (1uL<<(15u-8u))

#define SPR_PIR 286
#define SPR_PVR 287

#define WAIT_FOR_OP()  while( FCCU.CTRL.R & 0x1f ) {}

/**
 * Get Fault Control and Collection Unit status
 */
uint32 Fccu_GetStat( void );


#if defined(CFG_MCU_ARC_CLEAR_FCCU)
void Fccu_ClearCriticalStatusReg( uint32 regIndex, uint32_t val );
#endif
/**
 * Executes one operation on the Initialize the Fault Control and Collection Unit.
 * @param op - operation to perfrom
 */
void Fccu_Op( uint32 operation );


/**
 * Initialize the Fault Control and Collection Unit.
 */
void Fccu_Init( void );

#endif
