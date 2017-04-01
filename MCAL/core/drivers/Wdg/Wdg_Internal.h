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

#ifndef WDG_INTERNAL_H_
#define WDG_INTERNAL_H_

#include "Wdg.h"

#if defined(USE_DET)
#include "Det.h"
#endif

#if defined(USE_DEM) || defined (WDG_USE_DEM)
#include "Dem.h"
#endif

#if (WDG_DEV_ERROR_DETECT)
#define VALIDATE(_exp,_api,_err ) \
        /*lint -save -e506 -e774*/ \
        if( !(_exp) ) { \
          (void)Det_ReportError(WDG_MODULE_ID,0,_api,_err); \
          return; /*lint -restore*/\
        }
#define VALIDATE_RV(_exp,_api,_err,_ret ) \
        if( !(_exp) ) { \
          (void)Det_ReportError(WDG_MODULE_ID,0,_api,_err); \
          return _ret; \
        }
#define VALIDATE_FAIL(_api,_err) \
          (void)Det_ReportError(WDG_MODULE_ID,0,_api,_err); \
          return
#define VALIDATE_FAIL_RV(_api,_err,_ret ) \
          (void)Det_ReportError(WDG_MODULE_ID,0,_api,_err); \
          return _ret
#define VALIDARE_FAIL_REPORT(_api,_err) \
        (void)Det_ReportError(WDG_MODULE_ID,0,_api,_err)
#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_RV(_exp,_api,_err,_ret )
#define VALIDATE_FAIL(_api,_err)
#define VALIDATE_FAIL_RV(_api,_err,_ret )
#define VALIDARE_FAIL_REPORT(_api,_err)
#endif

#if defined(USE_DEM) || defined (CFG_WDG_USE_DEM)
#define WDG_REPORT_DEM_ERROR(event, status) if (event != DEM_EVENT_ID_NULL) { Dem_ReportErrorStatus(event, status); }
#else
#define WDG_REPORT_DEM_ERROR(event, status)
#endif

typedef enum {
    WDG_UNINIT = 0u,
    WDG_IDLE,
    WDG_BUSY
} WdgInternalState;

Std_ReturnType Wdg_Hw_Init(const Wdg_ConfigType* ConfigPtr);

Std_ReturnType Wdg_Hw_SetMode(WdgIf_ModeType Mode, const Wdg_ConfigType* ConfigPtr, uint8 callingServiceId);

void Wdg_Hw_SetTriggerCondition(uint16 timeout);

/**
 * @brief Validates that timeout is within the allowed range.
 * @param timeout This is the watchdog timeout period for WDGIF_FAST_MODE or
 * WDGIF_SLOW_MODE.
 * @return E_OK if the timeout is valid, else E_NOT_OK.
 */
Std_ReturnType Wdg_Hw_ValidateTimeout(uint16 timeout);

#endif /* WDG_INTERNAL_H_ */
