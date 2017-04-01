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

#ifndef PORTDEFS_H_
#define PORTDEFS_H_

#if defined(CFG_MPC5516)
#include "mpc5516_portdefs.h"
#elif defined(CFG_MPC5604B)
#include "mpc5604b_portdefs.h"
#elif defined(CFG_SPC560B54)
#include "spc560b54_portdefs.h"
#elif defined(CFG_MPC5606B)
#include "mpc5606b_portdefs.h"
#elif defined(CFG_MPC5606S)
#include "mpc5606s_portdefs.h"
#elif defined(CFG_MPC5567)
#include "mpc5567_portdefs.h"
#elif defined(CFG_MPC5777M)
#include "mpc5777m_portdefs.h"
#elif defined(CFG_MPC5645S)
#include "MPC5645S_portdefs.h"
#elif defined(CFG_MPC5744P)
#include "mpc5744p_portdefs.h"
#elif defined(CFG_MPC5746C)
#include "mpc5746c_portdefs.h"
#elif defined(CFG_MPC5748G) || defined(CFG_MPC5747C)
#include "mpc5748g_portdefs.h"
#elif defined(CFG_MPC563XM)
#include "mpc563Xm_portdefs.h"
#elif defined(CFG_MPC5643L)
#include "MPC5643L_portdefs.h"
#elif defined(CFG_MPC5644A)
#include "MPC5644A_portdefs.h"
#elif defined(CFG_MPC5668)
#include "MPC5668_portdefs.h"
#elif defined(CFG_SPC56XL70)
#include "SPC56XL70_portdefs.h"
#elif defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
#include "tms570ls12x_portdefs.h"
#elif defined(CFG_TMS570LC43X)
#include "tms570lc43x_portdefs.h"
#elif defined(CFG_ZYNQ)
#include "zynq_portdefs.h"
#elif defined(CFG_RH850F1L)
#include "rh850f1l_portdefs.h"
#elif defined(CFG_RH850)
#include "rh850_portdefs.h"
#elif defined(CFG_JAC5)
#include "jacinto5_portdefs.h"
#elif defined(CFG_JAC5E)
#include "jacinto5e_portdefs.h"
#elif defined(CFG_JAC6)
#include "jacinto6_portdefs.h"
#else
#error "No PortDefinition file defined for the CPU."
#endif

#endif /*PORTDEFS_H_*/
