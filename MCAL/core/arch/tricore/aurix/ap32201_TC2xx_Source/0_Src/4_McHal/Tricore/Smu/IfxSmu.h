/**
 * \file IfxSmu.h
 * \brief This file contains defintions of SMU 
 *
 * \license
 * You can use this file under the terms of the IFX License.
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the IFX License for more details (IFX_License.txt).
 *
 * This file may be used, copied, and distributed, with or without modification, provided
 * that all copyright notices are retained; that all modifications to this file are
 * prominently noted in the modified file; and that this paragraph is not modified.
 *
 * \copyright Copyright (C) 2013 Infineon Technologies AG
 * \author Puneetha Mukherjee <puneetha.mukherjee@infineon.com>
 *
 * $Revision: 002 $
 * $Date: 24-05-2013 12:09 +0530 $
 *
 * \defgroup Ifx Infineon Software
 * \defgroup Ifx_Lld Infineon Low Level Drivers' Software
 * \ingroup I
 */ 
 
#ifndef IFXSMU_H_
#define IFXSMU_H_

#include "IfxSmu_cfg.h"

#define IFXSMU_NO_ERROR         (0U)

typedef volatile union {
    unsigned U;
    int I;
} SMU_Alarm_Debug_type ;
/*lint -save -e923 */
/*lint -save -e923 */#define SCU_SMU_AD0 (*( SMU_Alarm_Debug_type *) 0xF0036A00U)
#define SCU_SMU_AD1 (*( SMU_Alarm_Debug_type *) 0xF0036A04U)
#define SCU_SMU_AD2 (*( SMU_Alarm_Debug_type *) 0xF0036A08U)
#define SCU_SMU_AD3 (*( SMU_Alarm_Debug_type *) 0xF0036A0CU)
#define SCU_SMU_AD4 (*( SMU_Alarm_Debug_type *) 0xF0036A10U)
#define SCU_SMU_AD5 (*( SMU_Alarm_Debug_type *) 0xF0036A14U)
#define SCU_SMU_AD6 (*( SMU_Alarm_Debug_type *) 0xF0036A18U)
/*lint -restore */
#endif /* IFXSMU_H_ */
