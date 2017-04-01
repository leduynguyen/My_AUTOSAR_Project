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

#include "Std_Types.h"
#include "Platform_Types.h"

#include "Wdg_Internal.h"
#include "Wdg_rh850f1h.h"
#include "rh850_ostm.h"
#include "isr.h"

/**
 * @param timerFreq Frequency of the clock for the timer used to kick the watchdog.
 * @param timeoutMs
 * @return The value for the OSTMnCMP register.
 */
static uint32 calcKickCounterValue(uint32 timerFreq, uint32 timeoutMs);

/**
 * @brief Changes the watchdog clock frequency to the provided setting.
 * @param clockDividerSetting 1 for 240kHz / 128 or 2 for 240kHz / 1.
 * @param maxTries The maximum number of tries to change the watchdog clock.
 * @return E_OK if the watchdog clock was changed successfully, else E_NOT_OK.
 */
static Std_ReturnType tryScaleWdgClock(uint32 clockDividerSetting, uint8 maxTries);

/**
 * @brief Changes the watchdog clock frequency to the provided setting.
 * @param clockDividerSetting 1 for 240kHz / 128 or 2 for 240kHz / 1.
 * @return E_OK if the watchdog clock was changed successfully, else E_NOT_OK.
 */
static Std_ReturnType scaleWdgClock(uint32 clockDividerSetting);

/**
 * @brief RH850F1H specific. RH850F1L only has one OS timer so this will have to be done differently.
 *
 * @param kickIntervalMs The interval for kicking the watchdog in milliseconds.
 */
static void startWdgKickTimer(uint16 kickIntervalMs);

/**
 * @brief Given a timeout in milliseconds it finds the correct settings to achieve that.
 * @param[in] timeoutMs					The desired timeout in milliseconds.
 * @param[out] overflowMaskOut			The settings for the watchdog timeout/overflow bits (WDTAnOVF).
 * @param[out] wdgClockDividerSetting	The setting for scaling the watchdog clock (CKSC_AWDTAD_CTL).
 * @return E_OK if matching settings were found, else E_NOT_OK.
 */
static Std_ReturnType getWdgOverflowSettings(uint16 timeoutMs, uint8 *overflowMaskOut, uint32 *wdgClockDividerSetting);

/**
 * @brief On return from this function the watchdog has been started and cannot be stopped or changed.
 * @param overflowMask					A mask with the bits for the WDTAnOVF settings (the rest of the bits must be 0).
 */
static void startWatchdog(uint8 overflowMask);

static uint16 Wdg_MaxTimeoutMs;

extern volatile uint16 Wdg_TriggerCounter;

extern WdgIf_ModeType Wdg_Mode;

/*lint -e{923} cast from unsigned int to pointer MISRA 2004 11.1 11.3 2012 11.4 11.6
 * Integer to pointer casting is necessary to set SFR of Microcontroller. */
static Wdg_WdtaHwRegType* const WDTA0_PTR = (Wdg_WdtaHwRegType*) WDTAN_BASE;

ISR(Wdg_Isr_Kick)
{
    if (Wdg_TriggerCounter > 0)
    {
        --Wdg_TriggerCounter;

        WDTA0_PTR->WDTE = WDT_KICK_CODE;
    }
}

Std_ReturnType Wdg_Hw_SetMode(WdgIf_ModeType mode, const Wdg_ConfigType* ConfigPtr, uint8 callingServiceId)
{
    uint8 overflowMask;
    uint32 wdgClockDividerSetting;
    Std_ReturnType result;

    /* SWS_Wdg_00173 */
    /* SWS_Wdg_00016 */
    if (Wdg_Mode != WDGIF_OFF_MODE)
    {
        WDG_REPORT_DEM_ERROR(ConfigPtr->Wdg_DEMEventIdRefs->WdgSetMode, DEM_EVENT_STATUS_FAILED);

        return E_NOT_OK;
    }

    if (WDGIF_FAST_MODE == mode)
    {
        result = getWdgOverflowSettings(
                ConfigPtr->Wdg_ModeConfig->WdgSettingsFast,
                &overflowMask,
                &wdgClockDividerSetting);
    }
    else if (WDGIF_SLOW_MODE == mode)
    {
        result = getWdgOverflowSettings(
                ConfigPtr->Wdg_ModeConfig->WdgSettingsSlow,
                &overflowMask,
                &wdgClockDividerSetting);
    }
    else
    {
        WDG_REPORT_DEM_ERROR(ConfigPtr->Wdg_DEMEventIdRefs->WdgSetMode, DEM_EVENT_STATUS_PASSED);

        return E_OK;
    }


    if (result != E_OK)
    {
        uint8 err = WDG_E_PARAM_MODE;

        if (callingServiceId == WDG_INIT_SERVICE_ID)
        {
            err = WDG_E_PARAM_CONFIG;
        }

        /* @req SWS_Wdg_00090 */
        /* @req SWS_Wdg_00092 */
        VALIDARE_FAIL_REPORT(callingServiceId, err);

        /* SWS_Wdg_00173 */
        /* SWS_Wdg_00016 */
        WDG_REPORT_DEM_ERROR(ConfigPtr->Wdg_DEMEventIdRefs->WdgSetMode, DEM_EVENT_STATUS_FAILED);

        return E_NOT_OK;
    }

    if (tryScaleWdgClock(wdgClockDividerSetting, WDG_SCALE_MAX_TRIES) != E_OK)
    {
        /* SWS_Wdg_00173 */
        /* SWS_Wdg_00016 */
        WDG_REPORT_DEM_ERROR(ConfigPtr->Wdg_DEMEventIdRefs->WdgSetMode, DEM_EVENT_STATUS_FAILED);

        return E_NOT_OK;
    }

    Wdg_Mode = mode;

    startWatchdog(overflowMask);

    startWdgKickTimer(WDG_TRIGGER_PERIOD_MS);

    WDG_REPORT_DEM_ERROR(ConfigPtr->Wdg_DEMEventIdRefs->WdgSetMode, DEM_EVENT_STATUS_PASSED);

    return E_OK;
}

Std_ReturnType Wdg_Hw_Init(const Wdg_ConfigType* ConfigPtr)
{
#if defined(CFG_RH850F1H)
    ISR_INSTALL_ISR2("Wdg_Isr_Kick", Wdg_Isr_Kick, (IrqType)(IRQ_INTOSTM5), WDG_KICK_ISR_PRIO, WDG_ISR_APP);
#endif

    /* WdgInitialTimeout and WdgMaxTimeout are given in seconds,
     * convert to milliseconds. */
    /*lint -e{734} WdgInitialTimeout is validated to be less than or equal to 65 and thus will always fit
     * in 16 bits. */
    Wdg_TriggerCounter = ConfigPtr->WdgInitialTimeout * 1000;
    /*lint -e{734} WdgMaxTimeout is validated to be less than or equal to 65 and thus will always fit
     * in 16 bits. */
    Wdg_MaxTimeoutMs = ConfigPtr->WdgMaxTimeout * 1000;

    return Wdg_Hw_SetMode(ConfigPtr->Wdg_ModeConfig->Wdg_DefaultMode, ConfigPtr, WDG_INIT_SERVICE_ID);
}

void Wdg_Hw_SetTriggerCondition(uint16 timeout)
{
    /* SWS_Wdg_00146 */
    VALIDATE((timeout <= Wdg_MaxTimeoutMs), WDG_SET_TRIGGERING_CONDITION_SERVICE_ID, WDG_E_PARAM_TIMEOUT);

    /*lint -save -e9013 no 'else' at end of 'if ... else if' - This is OK, all cases are handled. */
    if (Wdg_Mode == WDGIF_OFF_MODE)
    {
        /* @req SWS_Wdg_00138 - No conversion is needed between milliseconds and count since
         * we trigger each millisecond.
         */
        /* @req SWS_Wdg_00139 - No regard to the current mode is necessary since we always trigger with
         * a 1 ms interval. */
        Wdg_TriggerCounter = timeout;
    }
    else if ((Wdg_Mode == WDGIF_FAST_MODE) || (Wdg_Mode == WDGIF_SLOW_MODE))
    {
#if defined(CFG_RH850F1H)
        /*lint -e{923} cast from unsigned int to pointer MISRA 2004 11.1 11.3 2012 11.4 11.6
         * Integer to pointer casting is necessary to use SFR registers. */
        struct OSTM_reg *tPtr = OSTM5p;

        /* Stop the timer. */
        tPtr->OSTMnTT |= OSTMNTT_STOP;

        /* @req SWS_Wdg_00138 - No conversion is needed between milliseconds and count since
         * we trigger each millisecond.
         */
        /* @req SWS_Wdg_00139 - No regard to the current mode is necessary since we always trigger with
         * a 1 ms interval. */
        Wdg_TriggerCounter = timeout;

        /* Start the timer. */
        tPtr->OSTMnTS |= OSTMNTS_START;
#endif
    }
    /*lint -restore -e9013 */
}

static uint32 calcKickCounterValue(uint32 timerFreq, uint32 timeoutMs)
{
    return timeoutMs * timerFreq / 1000;
}

static Std_ReturnType tryScaleWdgClock(uint32 clockDividerSetting, uint8 maxTries)
{
    uint8 tries = 0;
    Std_ReturnType result = E_NOT_OK;

    while ((result != E_OK) && (tries < maxTries))
    {
        tries++;
        result = scaleWdgClock(clockDividerSetting);
    }

    return result;
}

static Std_ReturnType scaleWdgClock(uint32 clockDividerSetting)
{
    vuint32_t *controlReg;
    vuint32_t *protectionReg;
    uint32 regValue;
    Std_ReturnType status;

    /*lint -e{923} cast from unsigned int to pointer MISRA 2004 11.1 11.3 2012 11.4 11.6
     * Integer to pointer casting is necessary to use SFR registers. */
    if ((CKSC_AWDTAD_ACT_CONTENT & CKSC_AWDTAD_ACT_MASK) != CKSC_AWDTAD_CTL_IS_ACTIVE)
    {
        return E_NOT_OK;
    }

    /*lint -e{923} cast from unsigned int to pointer MISRA 2004 11.1 11.3 2012 11.4 11.6
     * Integer to pointer casting is necessary to use SFR registers. */
    controlReg = (vuint32_t*) CKSC_AWDTAD_CTL_ADDR;

    if ((*controlReg & WDTA0_CLOCK_DIVIDER_MASK) == clockDividerSetting)
    {
        return E_OK;
    }

    /*lint -e{923} cast from unsigned int to pointer MISRA 2004 11.1 11.3 2012 11.4 11.6
     * Integer to pointer casting is necessary to use SFR registers. */
    protectionReg = (vuint32_t*) PROTCMD0_ADDR;

    /* Bits 31:2 = Write back the same value.
     * Bits 1:0  = 1,0 for 240kHz / 1 and 0,1 for 240kHz / 128.
     */
    regValue = (*controlReg) & 0xFFFFFFFCu;
    regValue |= clockDividerSetting;

    *protectionReg = PROTECTION_REG_UNLOCK_CODE;

    *controlReg = regValue;

    *controlReg = ~regValue;

    *controlReg = regValue;

    status = E_NOT_OK;

    /*lint -e{923} cast from unsigned int to pointer MISRA 2004 11.1 11.3 2012 11.4 11.6
     * Integer to pointer casting is necessary to use SFR registers. */
    if ((PROTS0_CONTENT & PROTS0_ERROR_BIT) == PROTS0_NO_ERROR)
    {
        if  ((*controlReg & WDTA0_CLOCK_DIVIDER_MASK) == clockDividerSetting)
        {
            status = E_OK;
        }
    }

    return status;
}

static void startWdgKickTimer(uint16 kickIntervalMs) {

    /* Use OSTM5 because OSTM0 is taken and the other OSTMn only have
     * maskable interrupts.
     */
    /*lint -e{923} cast from unsigned int to pointer MISRA 2004 11.1 11.3 2012 11.4 11.6
     * Integer to pointer casting is necessary to use SFR registers. */
    struct OSTM_reg *tPtr = OSTM5p;

    /* In interval mode the counter starts counting down from the value in OSTMnCMP. */
    tPtr->OSTMnCMP = calcKickCounterValue(Mcu_Arc_GetPeripheralClock(C_CPUCLK2), kickIntervalMs);

    /* Bits 7:2 should be written back as they are.
     * Bit 1 = 0 for interval mode.
     * Bit 0 = 0 for no interrupt at the start of counting.
     * 0b11111100 = OxFC
     */
    tPtr->OSTMnCTL &= 0xFCu;

    /* Bit 7 = 0 to stop timer when debugger stops.
     * Bit 6:0 should be written back as they are.
     * 0b01111111 = 0x7F
     */
    tPtr->OSTMnEMU &= 0x7Fu;

    /* Bits 7:1 should be written back as they are.
     * Bit 0 = 1 to start timer.
     */
    tPtr->OSTMnTS |= OSTMNTS_START;
}

static Std_ReturnType getWdgOverflowSettings(uint16 timeoutMs, uint8 *overflowMaskOut,
        uint32 *wdgClockDividerSetting)
{
    Std_ReturnType status = E_OK;

    *overflowMaskOut = 0;
    *wdgClockDividerSetting = WDTA0_CLOCK_DIVIDER_128;

    switch (timeoutMs)
    {
    case 2:

        /* 2^9 / WDTATCKI, WDTATCKI = 240000 / 1 */
        *overflowMaskOut = 0;

        *wdgClockDividerSetting = WDTA0_CLOCK_DIVIDER_1;

        break;

    case 4:

        /* 2^10 / WDTATCKI, WDTATCKI = 240000 / 1 */
        *overflowMaskOut = 0x10u;

        *wdgClockDividerSetting = WDTA0_CLOCK_DIVIDER_1;

        break;

    case 9:

        /* 2^11 / WDTATCKI, WDTATCKI = 240000 / 1 */
        *overflowMaskOut = 0x20u;

        *wdgClockDividerSetting = WDTA0_CLOCK_DIVIDER_1;

        break;

    case 17:

        /* 2^12 / WDTATCKI, WDTATCKI = 240000 / 1 */
        *overflowMaskOut = 0x30u;

        *wdgClockDividerSetting = WDTA0_CLOCK_DIVIDER_1;

        break;

    case 34:

        /* 2^13 / WDTATCKI, WDTATCKI = 240000 / 1 */
        *overflowMaskOut = 0x40u;

        *wdgClockDividerSetting = WDTA0_CLOCK_DIVIDER_1;

        break;

    case 68:

        /* 2^14 / WDTATCKI, WDTATCKI = 240000 / 1 */
        *overflowMaskOut = 0x50u;

        *wdgClockDividerSetting = WDTA0_CLOCK_DIVIDER_1;

        break;

    case 137:

        /* 2^15 / WDTATCKI, WDTATCKI = 240000 / 1 */
        *overflowMaskOut = 0x60u;

        *wdgClockDividerSetting = WDTA0_CLOCK_DIVIDER_1;

        break;

    case 273:

        /* 2^9 / WDTATCKI, WDTATCKI = 240000 / 128 */
        *overflowMaskOut = 0;

        *wdgClockDividerSetting = WDTA0_CLOCK_DIVIDER_128;

        break;

    case 546:

        /* 2^10 / WDTATCKI, WDTATCKI = 240000 / 128 */
        *overflowMaskOut = 0x10u;

        *wdgClockDividerSetting = WDTA0_CLOCK_DIVIDER_128;

        break;

    case 1092:

        /* 2^11 / WDTATCKI, WDTATCKI = 240000 / 128 */
        *overflowMaskOut = 0x20u;

        *wdgClockDividerSetting = WDTA0_CLOCK_DIVIDER_128;

        break;

    case 2185:

        /* 2^12 / WDTATCKI, WDTATCKI = 240000 / 128 */
        *overflowMaskOut = 0x30u;

        *wdgClockDividerSetting = WDTA0_CLOCK_DIVIDER_128;

        break;

    case 4369:

        /* 2^13 / WDTATCKI, WDTATCKI = 240000 / 128 */
        *overflowMaskOut = 0x40u;

        *wdgClockDividerSetting = WDTA0_CLOCK_DIVIDER_128;

        break;

    case 8738:

        /* 2^14 / WDTATCKI, WDTATCKI = 240000 / 128 */
        *overflowMaskOut = 0x50u;

        *wdgClockDividerSetting = WDTA0_CLOCK_DIVIDER_128;

        break;

    case 17476:

        /* 2^15 / WDTATCKI, WDTATCKI = 240000 / 128 */
        *overflowMaskOut = 0x60u;

        *wdgClockDividerSetting = WDTA0_CLOCK_DIVIDER_128;

        break;

    case 34953:

        /* 2^16 / WDTATCKI, WDTATCKI = 240000 / 128 */
        *overflowMaskOut = 0x70u;

        *wdgClockDividerSetting = WDTA0_CLOCK_DIVIDER_128;

        break;

    default:

        status = E_NOT_OK;

        break;
    }

    return status;
}

static void startWatchdog(uint8 overflowMask) {

    uint8 wdtaMdSetup;

    /* Bit 7: The value of WDTA0MD7 should be written back as it is. */
    wdtaMdSetup = WDTA0_PTR->MD & WDTA0MD7_MASK;

    /* Bit 6,5,4: WDTA0OVF[2:0] */
    wdtaMdSetup |= overflowMask;

    /* Bit 3: WDTA0WIE = 0 => No 75% interrupt */
    wdtaMdSetup &= 0xF7u;

    /* Bit 2: WDTA0ERM = 1 => Reset (Reset or interrupt/NMI) */
    wdtaMdSetup |= 0x04u;

    /* Bit 1 and 0: WDTA0WS:1,0 = 1,1 => 100% window open period. */
    wdtaMdSetup |= WDT_100_PERCENT_WINDOW;

    /* Set the mode of the watchdog. */
    WDTA0_PTR->MD = wdtaMdSetup;

    /* Kick the watchdog. This will apply the settings written to WDTA0_PTR->MD. */
    WDTA0_PTR->WDTE = WDT_KICK_CODE;
}

Std_ReturnType Wdg_Hw_ValidateTimeout(uint16 timeout)
{
    uint8 i;
    uint16 allowedTimeouts[] = {2, 4, 9, 17, 34, 68, 137, 273, 546, 1092, 2185, 4369, 8738, 17476, 34953};

    for (i = 0; i < (sizeof(allowedTimeouts) / sizeof(uint16)); i++)
    {
        if (timeout == allowedTimeouts[i])
        {
            return E_OK;
        }
    }

    return E_NOT_OK;
}

void Wdg_Arc_StopWatchdog(void)
{
    return;
}
