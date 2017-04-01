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

#include "Det.h"

#if !(((DET_SW_MAJOR_VERSION == 1) && (DET_SW_MINOR_VERSION == 0)) )
#error Det: Configuration file expected BSW module version to be 1.0.*
#endif

#if !(((DET_AR_MAJOR_VERSION == 4) && (DET_AR_MINOR_VERSION == 0)) )
#error Det: Expected AUTOSAR version to be 4.0.*
#endif

#if (DET_USE_STATIC_CALLBACKS == STD_ON )

extern void StaticErrorHookTest(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

detCbk_t DetStaticHooks[] = {
    StaticErrorHookTest,
};
#endif

