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

#ifndef OS_I_H_
#define OS_I_H_

#define NO_TASK_OWNER   (TaskType)(~0U)

#include "arc_assert.h"
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>


/* Forward declare most object, so we don't have to care later
 * Rule: In all files use the name without the "Type" and with "struct"
 * */
struct OsApplication;
struct OsCounter;
struct OsAlarm;
struct OsResource;
struct OsTask;
struct OsTaskVar;
struct Os_Sys;
struct OsIsrVar;
struct OsTimingProtection;



#if (OS_STATUS_EXTENDED == STD_ON )


#define OS_VALIDATE(_exp,_err ) \
        if( !(_exp) ) { \
          rv = _err; \
          goto err; \
        }

#define VALIDATE_W_RV(_exp,_rv) \
    if( (_exp) ) { \
        ERRORHOOK(_rv); \
        return _rv; \
    }

#else
#define OS_VALIDATE(_exp,_err )
#define OS_VALIDATE_W_RV(_exp,_err )
#endif

#define OS_STD_VALIDATE(_exp,_err ) \
        if( !(_exp) ) { \
          rv = _err; \
          goto err; \
        }



#include "Std_Types.h"
#include "Os.h"
#include "os_internal.h"
#include "os_sys.h"
#include "debug.h"
#include "irq_types.h"

/* "Normal" includes */
#include "os_config_macros.h"
#include "alist_i.h"
#include "os_resource_i.h"
#include "os_application_i.h"
#include "os_task_i.h"
#include "os_counter_i.h"
#include "os_alarm_i.h"
#include "os_sched_table_i.h"
#if (OS_NUM_CORES > 1)
#include "os_spinlock_i.h"
#endif
#include "isr.h"
#include "arch.h"
#include "os_multicore_i.h"
#include "arc.h"

#if (OS_SC3 == STD_ON )||(OS_SC4 == STD_ON )
#include "os_mm.h"
void Os_MMInit( void );
void Os_MMSetUserMode( OsTaskVarType *pcbPtr );
#endif

/* Sanity checks */


#define APPL_CHECK_STATE(_appId) \
        if( Os_ApplGetState(_appId) != APPLICATION_ACCESSIBLE ) {  \
            rv=E_OS_ACCESS;     \
            goto err;   \
        }

#define APPL_CHECK_ACCESS(_appId, _mask) \
        if( (APPL_ID_TO_MASK(_appId) & _mask) == 0 ) { \
            rv=E_OS_ACCESS;     \
            goto err;   \
        }


#endif
