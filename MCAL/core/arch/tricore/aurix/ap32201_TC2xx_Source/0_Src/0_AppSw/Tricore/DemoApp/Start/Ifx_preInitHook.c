/**
 * \file Ifx_preInitHook.c
 * \brief Driver configuration.
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
 * $Revision: 001 $
 * $Date: 24-05-2013 12:09 +0530 $
 *
 * \defgroup Ifx Infineon Software
 * \defgroup Ifx_Lld Infineon Low Level Drivers' Software
 * \ingroup I
 */ 
/******************************************************************************/
#include "Ifx_Types.h"
#include "IfxScuWdt.h"
#include "Ifx_preInitHook.h"


void IfxSysPreC_InitHook0()
{
     mySysPreInitHook (0);

    __jump_to_link();
}

void IfxSysPreC_InitHook1()
{
    mySysPreInitHook (1);
    __jump_to_link();
}

void IfxSysPreC_InitHook2()
{
    mySysPreInitHook (2);
    __jump_to_link();
}
