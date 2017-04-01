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


/** @tagSettings DEFAULT_ARCHITECTURE=STM32 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#include "stm32f10x.h"
#include "Wdg.h"

/* Independant WD.  */
static const Wdg_IWDG_ConfigType *configIWDGPtr;
static const Wdg_IWDG_SettingsType *modeIWDGConfig;
/* Windowed WD. */
static const Wdg_WWDG_ConfigType *configWWDGPtr;
static const Wdg_WWDG_SettingsType *modeWWDGConfig;


void Wdg_IWDG_Init (const Wdg_IWDG_ConfigType* ConfigPtr)
{
    /* Keep a pointer to the config. */
    configIWDGPtr = ConfigPtr;

	(void)Wdg_IWDG_SetMode(ConfigPtr->Wdg_IWDGModeConfig->Wdg_DefaultMode);
}

void Wdg_WWDG_Init (const Wdg_WWDG_ConfigType* ConfigPtr)
{
    /* Keep a pointer to the config. */
    configWWDGPtr = ConfigPtr;

    /* IMPROVEMENT: Move to Mcu.. */
    RCC->APB1ENR |= (1 << 11);

	(void)Wdg_WWDG_SetMode(ConfigPtr->Wdg_WWDGModeConfig->Wdg_DefaultMode);
}

/* This is the AUTOSAR function. It is just a wrapper to the IWDG to
 * be able to use the other parts of the watchdog stack 
 */
void Wdg_Init (const Wdg_ConfigType* ConfigPtr)
{
    Wdg_IWDG_Init(ConfigPtr->Wdg_IWDG_Config);
}

/* This is the AUTOSAR function. It is just a wrapper to the IWDG to
 * be able to use the other parts of the watchdog stack 
 */
void Wdg_SetTriggerCondition (uint16 timeout) {
    Wdg_IWDG_Trigger(timeout);
}

/* This is the AUTOSAR function. It is just a wrapper to the IWDG to
 * be able to use the other parts of the watchdog stack 
 */
Std_ReturnType Wdg_SetMode (WdgIf_ModeType Mode) {
    return Wdg_IWDG_SetMode(Mode);
}

/* Parameter timeout added to make it compatible with AUTOSAR API.*/
void Wdg_IWDG_Trigger (uint16 timeout) {
    (void)timeout;

    /* Kick until you have no more time */
    if (timeout)
        IWDG->KR = 0xAAAA;
}

/* Parameter timeout added to make it compatible with AUTOSAR API.*/
void Wdg_WWDG_Trigger (uint16 timeout) {
    volatile uint32 temp;
    (void)timeout;

    if (modeWWDGConfig != 0)
    {
        temp = WWDG->CR;

        /* Set counter to preset value. */
        temp |= (modeWWDGConfig->CounterPreset & WWDG_CR_T);

        WWDG->CR = temp;
    }
}

Std_ReturnType Wdg_IWDG_SetMode (WdgIf_ModeType Mode)
{
	Std_ReturnType res = E_NOT_OK;
	switch (Mode)
	{
	case WDGIF_OFF_MODE:
		modeIWDGConfig = &configIWDGPtr->Wdg_IWDGModeConfig->WdgSettingsOff;
		break;
	case WDGIF_FAST_MODE:
		modeIWDGConfig = &configIWDGPtr->Wdg_IWDGModeConfig->WdgSettingsFast;
		break;
	case WDGIF_SLOW_MODE:
		modeIWDGConfig = &(configIWDGPtr->Wdg_IWDGModeConfig->WdgSettingsSlow);
		break;
	default:
		modeIWDGConfig = 0;
		break;
	}
    if (modeIWDGConfig != 0)
    {
    /* Unlock the iwdg registers. */
    IWDG->KR = 0x5555;

    /* Configure prescaler and reload value.  */
    IWDG->PR = (uint32)modeIWDGConfig->TimerBase;
    IWDG->RLR = modeIWDGConfig->ReloadValue;

    /* Lock the iwdg registers again. */
    IWDG->KR = 0x0;

    /* Enable watchdog if config tell us to.. */
    if(modeIWDGConfig->ActivationBit)
    {
        /* IWDG is started by writing 0xCCCC to key register. */
        IWDG->KR = 0xCCCC;
    }
    else
    {
        /* There is no way to disable this watchdog.. */
    }
    res = E_OK;
	}
  return res;

}

Std_ReturnType Wdg_WWDG_SetMode (WdgIf_ModeType Mode)
{
	Std_ReturnType res = E_NOT_OK;
	switch (Mode)
	{
	case WDGIF_OFF_MODE:
		modeWWDGConfig = &configWWDGPtr->Wdg_WWDGModeConfig->WdgSettingsOff;
		break;
	case WDGIF_FAST_MODE:
		modeWWDGConfig = &configWWDGPtr->Wdg_WWDGModeConfig->WdgSettingsFast;
		break;
	case WDGIF_SLOW_MODE:
		modeWWDGConfig = &configWWDGPtr->Wdg_WWDGModeConfig->WdgSettingsSlow;
		break;
	default:
		modeWWDGConfig = 0;
		break;
	}
	if (modeWWDGConfig != 0)
	{
		/* Enable watchdog in system reset mode. */
		volatile uint32 temp;
		temp = WWDG->CFR;
		/* Clear prescaler bits. */
		temp &= ~WWDG_CFR_WDGTB;
		temp |= (((uint32)modeWWDGConfig->TimerBase << 7) & WWDG_CFR_WDGTB);

		/* Configure window. */
		temp &= ~WWDG_CFR_W;
		temp |= (modeWWDGConfig->WindowValue & WWDG_CFR_W);

		WWDG->CFR = temp;

		temp = WWDG->CR;
		temp &= ~WWDG_CR_T;
		/* Set counter. */
		temp |= (modeWWDGConfig->CounterPreset & WWDG_CR_T);

		/* Enable watchdog if config tell us to.. */
		if (modeWWDGConfig->ActivationBit)
		{
			temp |= WWDG_CR_WDGA;
		}
		else
		{
			temp &= ~WWDG_CR_WDGA;
		}
		WWDG->CR = temp;

		/* Clear EWI flag. */
		WWDG->SR = 0;
		res = E_OK;
	}
	return res;
}


void Wdg_IWDG_GetVersionInfo (void /*Std_VersionInfoType* versioninfo*/)
{

}

void Wdg_WWDG_GetVersionInfo (void /*Std_VersionInfoType* versioninfo*/)
{

}
