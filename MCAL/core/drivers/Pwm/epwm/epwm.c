/* --COPYRIGHT--,BSD
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//! \file   drivers/pwm/src/32b/hercules/champion/epwm.c
//! \brief  Contains the various functions related to the 
//!         pulse width modulation (PWM) object
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

/*lint -w1 EXTERNAL FILE */
#include "epwm.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions

void PWM_disableChopping(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

  // clear the bits
  pwm->PCCTL &= (~PWM_PCCTL_CHPEN_BITS);

  return;
} // end of PWM_disableChopping() function


void PWM_disableCounterLoad(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->TBCTL &= (~PWM_TBCTL_PHSEN_BITS);

  return;
} // end of PWM_disableCounterLoad() function


void PWM_disableDeadBand(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->DBCTL = 0;

  return;
} // end of PWM_disableDeadBand() function


void PWM_disableDeadBandHalfCycle(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->DBCTL &= (~PWM_DBCTL_HALFCYCLE_BITS);

  return;
} // end of PWM_disableDeadBandHalfCycle() function


void PWM_disableInt(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->ETSEL &= (~PWM_ETSEL_INTEN_BITS);

  return;
} // end of PWM_disableInt() function


void PWM_disableSocAPulse(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->ETSEL &= (~PWM_ETSEL_SOCAEN_BITS);

  return;
} // end of PWM_disableSocAPulse() function


void PWM_disableSocBPulse(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->ETSEL &= (~PWM_ETSEL_SOCBEN_BITS);

  return;
} // end of PWM_disableSocBPulse() function


void PWM_disableTripZones(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  //ENABLE_PROTECTED_REGISTER_WRITE_MODE;

  // set the bits
  pwm->TZSEL = 0;

  //DISABLE_PROTECTED_REGISTER_WRITE_MODE;

  return;
} // end of PWM_disableTripZones() function


void PWM_disableTripZoneSrc(PWM_Handle pwmHandle,const PWM_TripZoneSrc_e src)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  //ENABLE_PROTECTED_REGISTER_WRITE_MODE;

  // clear the bits
  pwm->TZSEL &= (~src);

  //DISABLE_PROTECTED_REGISTER_WRITE_MODE;

  return;
} // end of PWM_disableTripZoneSrc() function


void PWM_enableChopping(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

  // set the bits
  pwm->PCCTL = (uint16_t)1;

  return;
} // end of PWM_enableChopping() function


void PWM_enableCounterLoad(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // set the bits
  pwm->TBCTL |= PWM_TBCTL_PHSEN_BITS;

  return;
} // end of PWM_enableCounterLoad() function


void PWM_enableDeadBandHalfCycle(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // set the bits
  pwm->DBCTL |= (uint16_t)PWM_DBCTL_HALFCYCLE_BITS;

  return;
} // end of PWM_enableDeadBandHalfCycle() function



void PWM_enableInt(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // set the bits
  pwm->ETSEL |= PWM_ETSEL_INTEN_BITS;

  return;
} // end of PWM_enableInt() function


void PWM_enableSocAPulse(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // set the bits
  pwm->ETSEL |= PWM_ETSEL_SOCAEN_BITS;

  return;
} // end of PWM_enableSocAPulse() function


void PWM_enableSocBPulse(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // set the bits
  pwm->ETSEL |= (uint16_t)PWM_ETSEL_SOCBEN_BITS;

  return;
} // end of PWM_enableSocBPulse() function


void PWM_enableTripZoneSrc(PWM_Handle pwmHandle,const PWM_TripZoneSrc_e src)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  //ENABLE_PROTECTED_REGISTER_WRITE_MODE;

  // set the bits
  pwm->TZSEL |= src;

  //DISABLE_PROTECTED_REGISTER_WRITE_MODE;

  return;
} // end of PWM_enableTripZoneSrc() function


uint16_t PWM_getIntCount(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
  uint16_t intCount;

  intCount = pwm->ETPS & PWM_ETPS_INTCNT_BITS;

  return(intCount);
} // end of PWM_getIntCount() function


uint16_t PWM_getSocACount(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
  uint16_t intCount;

  intCount = pwm->ETPS & PWM_ETPS_SOCACNT_BITS;

  intCount >>= 10;

  return(intCount);
} // end of PWM_getSocACount() function


uint16_t PWM_getSocBCount(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;
  uint16_t intCount;

  intCount = pwm->ETPS & (uint16_t)PWM_ETPS_SOCBCNT_BITS;

  intCount >>= 14;

  return(intCount);
} // end of PWM_getSocBCount() function


PWM_Handle PWM_init(void *pMemory,const size_t numBytes)
{
  PWM_Handle pwmHandle;


  if(numBytes < sizeof(PWM_Obj))
    return((PWM_Handle)0);


  // assign the handle
  pwmHandle = (PWM_Handle)pMemory;

  return(pwmHandle);
} // end of PWM_init() function


void PWM_setActionQual_CntDown_CmpA_PwmA(PWM_Handle pwmHandle,const PWM_ActionQual_e actionQual)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->AQCTLA &= (~PWM_AQCTL_CAD_BITS);

  // set the bits
  pwm->AQCTLA |= (actionQual << 6);

  return;
} // end of PWM_setActionQual_CntDown_CmpA_PwmA() function


void PWM_setActionQual_CntDown_CmpA_PwmB(PWM_Handle pwmHandle,const PWM_ActionQual_e actionQual)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->AQCTLB &= (~PWM_AQCTL_CAD_BITS);

  // set the bits
  pwm->AQCTLB |= (actionQual << 6);

  return;
} // end of PWM_setActionQual_CntDown_CmpA_PwmB() function


void PWM_setActionQual_CntDown_CmpB_PwmA(PWM_Handle pwmHandle,const PWM_ActionQual_e actionQual)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->AQCTLA &= (~PWM_AQCTL_CBD_BITS);

  // set the bits
  pwm->AQCTLA |= (actionQual << 10);

  return;
} // end of PWM_setActionQual_CntDown_CmpB_PwmA() function


void PWM_setActionQual_CntDown_CmpB_PwmB(PWM_Handle pwmHandle,const PWM_ActionQual_e actionQual)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->AQCTLB &= (~PWM_AQCTL_CBD_BITS);

  // set the bits
  pwm->AQCTLB |= (actionQual << 10);

  return;
} // end of PWM_setActionQual_CntDown_CmpB_PwmB() function


void PWM_setActionQual_CntUp_CmpA_PwmA(PWM_Handle pwmHandle,const PWM_ActionQual_e actionQual)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->AQCTLA &= (~PWM_AQCTL_CAU_BITS);

  // set the bits
  pwm->AQCTLA |= (actionQual << 4);

  return;
} // end of PWM_setActionQual_CntUp_CmpA_PwmA() function


void PWM_setActionQual_CntUp_CmpA_PwmB(PWM_Handle pwmHandle,const PWM_ActionQual_e actionQual)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->AQCTLB &= (~PWM_AQCTL_CAU_BITS);

  // set the bits
  pwm->AQCTLB |= (actionQual << 4);

  return;
} // end of PWM_setActionQual_CntUp_CmpA_PwmB() function


void PWM_setActionQual_CntUp_CmpB_PwmA(PWM_Handle pwmHandle,const PWM_ActionQual_e actionQual)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->AQCTLA &= (~PWM_AQCTL_CBU_BITS);

  // set the bits
  pwm->AQCTLA |= (actionQual << 4);

  return;
} // end of PWM_setActionQual_CntUp_CmpB_PwmA() function


void PWM_setActionQual_CntUp_CmpB_PwmB(PWM_Handle pwmHandle,const PWM_ActionQual_e actionQual)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->AQCTLB &= (~PWM_AQCTL_CBU_BITS);

  // set the bits
  pwm->AQCTLB |= (actionQual << 8);

  return;
} // end of PWM_setActionQual_CntUp_CmpB_PwmB() function


void PWM_setActionQualContSWForce_PwmA(PWM_Handle pwmHandle,const PWM_ActionQualContSWForce_e actionQualContSWForce)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->AQCSFRC &= (~PWM_AQCSFRC_CSFA_BITS);

  // set the bits
  pwm->AQCSFRC |= actionQualContSWForce;

  return;
} // end of PWM_setActionQualContSWForce_PwmA() function


void PWM_setActionQualContSWForce_PwmB(PWM_Handle pwmHandle,const PWM_ActionQualContSWForce_e actionQualContSWForce)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->AQCSFRC &= (~PWM_AQCSFRC_CSFB_BITS);

  // set the bits
  pwm->AQCSFRC |= (actionQualContSWForce << 2);

  return;
} // end of PWM_setActionQualContSWForce_PwmA() function


void PWM_setActionQual_Period_PwmA(PWM_Handle pwmHandle,const PWM_ActionQual_e actionQual)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->AQCTLA &= (~PWM_AQCTL_PRD_BITS);

  // set the bits
  pwm->AQCTLA |= (actionQual << 2);

  return;
} // end of PWM_setActionQual_Period_PwmA() function


void PWM_setActionQual_Period_PwmB(PWM_Handle pwmHandle,const PWM_ActionQual_e actionQual)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->AQCTLB &= (~PWM_AQCTL_PRD_BITS);

  // set the bits
  pwm->AQCTLB |= (actionQual << 2);

  return;
} // end of PWM_setActionQual_Period_PwmB() function


void PWM_setActionQual_Zero_PwmA(PWM_Handle pwmHandle,const PWM_ActionQual_e actionQual)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->AQCTLA &= (~PWM_AQCTL_ZRO_BITS);

  // set the bits
  pwm->AQCTLA |= actionQual;

  return;
} // end of PWM_setActionQualZero_PwmA() function


void PWM_setActionQual_Zero_PwmB(PWM_Handle pwmHandle,const PWM_ActionQual_e actionQual)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->AQCTLB &= (~PWM_AQCTL_ZRO_BITS);

  // set the bits
  pwm->AQCTLB |= actionQual;

  return;
} // end of PWM_setActionQualZero_PwmB() function


void PWM_setChoppingClkFreq(PWM_Handle pwmHandle,const PWM_ChoppingClkFreq_e clkFreq)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->PCCTL &= (~PWM_PCCTL_CHPFREQ_BITS);

  // set the bits
  pwm->PCCTL |= clkFreq;

  return;
} // end of PWM_setChoppingClkFreq() function


void PWM_setChoppingDutyCycle(PWM_Handle pwmHandle,const PWM_ChoppingDutyCycle_e dutyCycle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->PCCTL &= (~PWM_PCCTL_CHPDUTY_BITS);

  // set the bits
  pwm->PCCTL |= dutyCycle;

  return;
} // end of PWM_setChoppingDutyCycle() function


void PWM_setChoppingPulseWidth(PWM_Handle pwmHandle,const PWM_ChoppingPulseWidth_e pulseWidth)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->PCCTL &= (~PWM_PCCTL_OSHTWTH_BITS);

  // set the bits
  pwm->PCCTL |= pulseWidth;

  return;
} // end of PWM_setChoppingPulseWidth() function


void PWM_setClkDiv(PWM_Handle pwmHandle,const PWM_ClkDiv_e clkDiv)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->TBCTL &= (~PWM_TBCTL_CLKDIV_BITS);

  // set the bits
  pwm->TBCTL |= clkDiv;

  return;
} // end of PWM_setClkDiv() function


void PWM_setCount(PWM_Handle pwmHandle,const uint16_t count)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // set the bits
  pwm->TBCTR = count;

  return;
} // end of PWM_setCount() function


void PWM_setCounterMode(PWM_Handle pwmHandle,const PWM_CounterMode_e counterMode)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->TBCTL &= (~PWM_TBCTL_CTRMODE_BITS);

  // set the bits
  pwm->TBCTL |= counterMode;

  return;
} // end of PWM_setCounterMode() function


void PWM_setDeadBandFallingEdgeDelay(PWM_Handle pwmHandle,const uint8_t delay)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  pwm->DBFED |= delay;

  return;
} // end of PWM_setDeadBandFallingEdgeDelay() function


void PWM_setDeadBandInputMode(PWM_Handle pwmHandle,const PWM_DeadBandInputMode_e inputMode)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->DBCTL &= (~PWM_DBCTL_INMODE_BITS);
  
  // set the bits
  pwm->DBCTL |= inputMode;

  return;
} // end of PWM_setDeadBandInputMode() function


void PWM_setDeadBandOutputMode(PWM_Handle pwmHandle,const PWM_DeadBandOutputMode_e outputMode)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->DBCTL &= (~PWM_DBCTL_OUTMODE_BITS);
  
  // set the bits
  pwm->DBCTL |= outputMode;

  return;
} // end of PWM_setDeadBandOutputMode() function


void PWM_setDeadBandPolarity(PWM_Handle pwmHandle,const PWM_DeadBandPolarity_e polarity)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->DBCTL &= (~PWM_DBCTL_POLSEL_BITS);
  
  // set the bits
  pwm->DBCTL |= polarity;

  return;
} // end of PWM_setDeadBandPolarity() function


void PWM_setDeadBandRisingEdgeDelay(PWM_Handle pwmHandle,const uint8_t delay)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  pwm->DBRED |= delay;

  return;
} // end of PWM_setDeadBandRisingEdgeDelay() function


void PWM_setPeriod(PWM_Handle pwmHandle,const uint16_t period)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // initialize the Time-Base Period Register (TBPRD).  These bits determine the period of the time-base counter.
  pwm->TBPRD = period;

  return;
} // end of PWM_setPeriod() function


void PWM_setHighSpeedClkDiv(PWM_Handle pwmHandle,const PWM_HspClkDiv_e clkDiv)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->TBCTL &= (~PWM_TBCTL_HSPCLKDIV_BITS);

  // set the bits
  pwm->TBCTL |= clkDiv;

  return;
} // end of PWM_setHighSpeedClkDiv() function


void PWM_setIntMode(PWM_Handle pwmHandle,const PWM_IntMode_e intMode)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->ETSEL &= (~PWM_ETSEL_INTSEL_BITS);

  // set the bits
  pwm->ETSEL |= intMode;

  return;
} // end of PWM_setIntMode() function


void PWM_setIntPeriod(PWM_Handle pwmHandle,const PWM_IntPeriod_e intPeriod)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->ETPS &= (~PWM_ETPS_INTPRD_BITS);

  // set the bits
  pwm->ETPS |= intPeriod;

  return;
} // end of PWM_setIntPeriod() function


void PWM_setLoadMode_CmpA(PWM_Handle pwmHandle,const PWM_LoadMode_e loadMode)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->CMPCTL &= (~PWM_CMPCTL_LOADAMODE_BITS);

  // set the bits
  pwm->CMPCTL |= loadMode;

  return;
} // end of PWM_setLoadMode_CmpA() function


void PWM_setLoadMode_CmpB(PWM_Handle pwmHandle,const PWM_LoadMode_e loadMode)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->CMPCTL &= (~PWM_CMPCTL_LOADBMODE_BITS);

  // set the bits
  pwm->CMPCTL |= (loadMode << 2);

  return;
} // end of PWM_setLoadMode_CmpB() function


void PWM_setPhase(PWM_Handle pwmHandle,const uint16_t phase)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  pwm->TBPHS = phase;

  return;
} // end of PWM_setPhase() function


void PWM_setPhaseDir(PWM_Handle pwmHandle,const PWM_PhaseDir_e phaseDir)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->TBCTL &= (~PWM_TBCTL_PHSDIR_BITS);

  // set the bits
  pwm->TBCTL |= phaseDir;

  return;
} // end of PWM_setPhaseDir() function


void PWM_setPeriodLoad(PWM_Handle pwmHandle,const PWM_PeriodLoad_e periodLoad)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->TBCTL &= (~PWM_TBCTL_PRDLD_BITS);

  // set the bits
  pwm->TBCTL |= periodLoad;

  return;
} // end of PWM_setPeriodLoad() function


void PWM_setRunMode(PWM_Handle pwmHandle,const PWM_RunMode_e runMode)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->TBCTL &= (~PWM_TBCTL_FREESOFT_BITS);

  // set the bits
  pwm->TBCTL |= runMode;

  return;
} // end of PWM_setRunMode() function


void PWM_setSocAPeriod(PWM_Handle pwmHandle,const PWM_SocPeriod_e intPeriod)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->ETPS &= (~PWM_ETPS_SOCAPRD_BITS);

  // set the bits
  pwm->ETPS |= (intPeriod << 8);

  return;
} // end of PWM_setSocAPeriod() function


void PWM_setSocAPulseSrc(PWM_Handle pwmHandle,const PWM_SocPulseSrc_e pulseSrc)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->ETSEL &= (~PWM_ETSEL_SOCASEL_BITS);

  // set the bits
  pwm->ETSEL |= (pulseSrc << 8);

  return;
} // end of PWM_setSocAPulseSrc() function


void PWM_setSocBPeriod(PWM_Handle pwmHandle,const PWM_SocPeriod_e intPeriod)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->ETPS &= (~PWM_ETPS_SOCBPRD_BITS);

  // set the bits
  pwm->ETPS |= (intPeriod << 12);

  return;
} // end of PWM_setSocBPeriod() function


void PWM_setSocBPulseSrc(PWM_Handle pwmHandle,const PWM_SocPulseSrc_e pulseSrc)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->ETSEL &= (~PWM_ETSEL_SOCBSEL_BITS);

  // set the bits
  pwm->ETSEL |= (pulseSrc << 12);

  return;
} // end of PWM_setSocBPulseSrc() function


void PWM_setShadowMode_CmpA(PWM_Handle pwmHandle,const PWM_ShadowMode_e shadowMode)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->CMPCTL &= (~PWM_CMPCTL_SHDWAMODE_BITS);

  // set the bits
  pwm->CMPCTL |= (shadowMode << 4);

  return;
} // end of PWM_setShadowMode_CmpA() function


void PWM_setShadowMode_CmpB(PWM_Handle pwmHandle,const PWM_ShadowMode_e shadowMode)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->CMPCTL &= (~PWM_CMPCTL_SHDWBMODE_BITS);

  // set the bits
  pwm->CMPCTL |= (shadowMode << 6);

  return;
} // end of PWM_setShadowMode_CmpB() function


void PWM_setSwSync(PWM_Handle pwmHandle)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // set the bits
  pwm->TBCTL |= 1 << 6;

  return;
} // end of PWM_setSwSync() function


void PWM_setSyncMode(PWM_Handle pwmHandle,const PWM_SyncMode_e syncMode)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  // clear the bits
  pwm->TBCTL &= (~PWM_TBCTL_SYNCOSEL_BITS);

  // set the bits
  pwm->TBCTL |= syncMode;

  return;
} // end of PWM_setSyncMode() function


void PWM_setTripZoneState_DCAEVT1(PWM_Handle pwmHandle,const PWM_TripZoneState_e tripZoneState)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  //ENABLE_PROTECTED_REGISTER_WRITE_MODE;

  // clear the bits
  pwm->TZCTL &= (~PWM_TZCTL_DCAEVT1_BITS);

  // set the bits
  pwm->TZCTL |= tripZoneState << 4;

  //DISABLE_PROTECTED_REGISTER_WRITE_MODE;

  return;
}  // end of PWM_setTripZoneState_DCAEVT1() function


void PWM_setTripZoneState_DCAEVT2(PWM_Handle pwmHandle,const PWM_TripZoneState_e tripZoneState)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  //ENABLE_PROTECTED_REGISTER_WRITE_MODE;

  // clear the bits
  pwm->TZCTL &= (~PWM_TZCTL_DCAEVT2_BITS);

  // set the bits
  pwm->TZCTL |= tripZoneState << 6;

  //DISABLE_PROTECTED_REGISTER_WRITE_MODE;

  return;
}  // end of PWM_setTripZoneState_DCAEVT2() function


void PWM_setTripZoneState_DCBEVT1(PWM_Handle pwmHandle,const PWM_TripZoneState_e tripZoneState)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  //ENABLE_PROTECTED_REGISTER_WRITE_MODE;

  // clear the bits
  pwm->TZCTL &= (~PWM_TZCTL_DCBEVT1_BITS);

  // set the bits
  pwm->TZCTL |= tripZoneState << 8;

  //DISABLE_PROTECTED_REGISTER_WRITE_MODE;

  return;
}  // end of PWM_setTripZoneState_DCBEVT1() function


void PWM_setTripZoneState_DCBEVT2(PWM_Handle pwmHandle,const PWM_TripZoneState_e tripZoneState)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  //ENABLE_PROTECTED_REGISTER_WRITE_MODE;

  // clear the bits
  pwm->TZCTL &= (~PWM_TZCTL_DCBEVT2_BITS);

  // set the bits
  pwm->TZCTL |= tripZoneState << 10;

  //DISABLE_PROTECTED_REGISTER_WRITE_MODE;

  return;
}  // end of PWM_setTripZoneState_DCBEVT2() function


void PWM_setTripZoneState_TZA(PWM_Handle pwmHandle,const PWM_TripZoneState_e tripZoneState)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  //ENABLE_PROTECTED_REGISTER_WRITE_MODE;

  // clear the bits
  pwm->TZCTL &= (~PWM_TZCTL_TZA_BITS);

  // set the bits
  pwm->TZCTL |= tripZoneState << 0;

  //DISABLE_PROTECTED_REGISTER_WRITE_MODE;

  return;
}  // end of PWM_setTripZoneState_TZA() function


void PWM_setTripZoneState_TZB(PWM_Handle pwmHandle,const PWM_TripZoneState_e tripZoneState)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;


  //ENABLE_PROTECTED_REGISTER_WRITE_MODE;

  // clear the bits
  pwm->TZCTL &= (~PWM_TZCTL_TZB_BITS);

  // set the bits
  pwm->TZCTL |= tripZoneState << 2;

  //DISABLE_PROTECTED_REGISTER_WRITE_MODE;

  return;
}  // end of PWM_setTripZoneState_TZB() function


// end of file
