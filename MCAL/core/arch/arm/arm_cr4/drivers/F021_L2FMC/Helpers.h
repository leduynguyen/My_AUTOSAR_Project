/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 � Copyright 2009-2012 Texas Instruments Incorporated.  All rights reserved.
 *
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *      Project:  Hercules� ARM� Safety MCUs - F021 Flash API 
 *      Version:  v2.01.01 Build(000830)                                                                                
 *   Build Date:  2014-10-21                                                                                            
 *
 *         File:  Helpers.h                                                                                             
 *
 *  Description:  These helper Macros are to facilitate common operations.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  John R Hall
 *---------------------------------------------------------------------------------------------------------------------
 *
 *********************************************************************************************************************/


#ifndef HELPERS_H_
#define HELPERS_H_

/* Quick Register referencing macro */
#define REGISTER(mRegister) (* (volatile uint32_t* )(mRegister))

/* Macro allowing a write to a locked FSM register */
#define FAPI_WRITE_LOCKED_FSM_REGISTER(mRegister,mValue)                 \
    do {                                                                  \
        FLASH_CONTROL_REGISTER->FsmWrEna.FSM_WR_ENA_BITS.WR_ENA    = 0x5U; \
        (mRegister) = (mValue);                                            \
        FLASH_CONTROL_REGISTER->FsmWrEna.FSM_WR_ENA_BITS.WR_ENA    = 0x2U; \
    } while(0)



/* These are helper functions to handle generic Big Endian/Little Endian code bases */
#if defined(_LITTLE_ENDIAN)
    #define EI16(idx)            ((idx) ^ 1)
    #define EI8(idx)             ((idx) ^ 3)
#else
    #define EI16(idx)            (idx)
    #define EI8(idx)             (idx)
#endif

/* These are helper functions to handle generic Big Endian/Little Endian code bases */
#if defined(_L2FMC) && defined(_BIG_ENDIAN)
#define L2EI16(idx)            ((idx) ^ 1)
#define L2EI8(idx)             ((idx) ^ 3)
#else
#define L2EI16 EI16
#define L2EI8  EI8
#endif

/* Macro that reads the FMSTAT register and indicates if the FSM is Ready or Busy */
#define FAPI_CHECK_FSM_READY_BUSY \
         (FLASH_CONTROL_REGISTER->FmStat.FMSTAT_BITS.BUSY ? Fapi_Status_FsmBusy : Fapi_Status_FsmReady)

/* Macro that clears the FSM_DONE event */
#define FAPI_CLEAR_FSM_DONE_EVENT (FLASH_CONTROL_REGISTER->FedAcStatus.FEDACSTATUS_BITS.FSM_DONE = 1U)

/* Macro that returns the value in the FMStat Register */
#define FAPI_GET_FSM_STATUS (FLASH_CONTROL_REGISTER->FmStat.u32Register)

/* Macro that issues a Suspend command to the FSM */
#define FAPI_SUSPEND_FSM \
         FAPI_WRITE_LOCKED_FSM_REGISTER(FLASH_CONTROL_REGISTER->FsmExecute.FSM_EXECUTE_BITS.SUSPEND_NOW, 0x5U)

/* Macro to set the EWAIT value */
#define FAPI_WRITE_EWAIT(_mEwait) \
         FAPI_WRITE_LOCKED_FSM_REGISTER(FLASH_CONTROL_REGISTER->EepromConfig.EEPROM_CONFIG_BITS.EWAIT,(_mEwait))

#endif /* HELPERS_H_ */

/**********************************************************************************************************************
 *  END OF FILE: Helpers.h
 *********************************************************************************************************************/
