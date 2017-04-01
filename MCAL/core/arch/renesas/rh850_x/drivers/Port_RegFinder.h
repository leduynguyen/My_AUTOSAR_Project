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

#ifndef PORT_REGFINDER_H_
#define PORT_REGFINDER_H_
/**
 * Helper functions to get which register to use for a certain pin id.
 * The Renesas RH850's registers are spread out in memory and the registers
 * are not in sequential order.
 *
 * To set a register, for example Port Input Buffer Control Register, the
 * first step is to go from Pin Id to Port Group using the "PinIdToPort"
 * array. For example PinId 1 => P10_3. From there the base address for the
 * register for this port group is looked up in the "regs" array.  The
 * register address is then stepped using the portnr, 10. Finally the bit, 3,
 * is used to set the correct bit in the register.
 */

#include "Std_Types.h"
#include "PortData_rh850f1l.h"

#define SET_PORT_REGISTER(pinNr, reg, pinCfg, ModuleId, ApiId, ErrorId) Port_Arc_setPin( pinNr, Port_Arc_getRegPointerFromPinId( REGISTERSELECTION_ ## reg , pinNr, ModuleId, ApiId, ErrorId), pinCfg.flags.BITF.reg)
#define SET_PROTECTED_PORT_REGISTER(pinNr, reg, pinCfg, ModuleId, ApiId, ErrorId) Port_Arc_setProtectedPin( pinNr, Port_Arc_getRegPointerFromPinId( REGISTERSELECTION_ ## reg , pinNr, ModuleId, ApiId, ErrorId), pinCfg.flags.BITF.reg)

typedef enum {
    REGISTERSELECTION_PMC,
    REGISTERSELECTION_PIPC,
    REGISTERSELECTION_PM,
    REGISTERSELECTION_PIBC,
    REGISTERSELECTION_PFC,
    REGISTERSELECTION_PFCE,
    REGISTERSELECTION_PFCAE,
    REGISTERSELECTION_PBDC,
    REGISTERSELECTION_PPR,
    REGISTERSELECTION_P,
    REGISTERSELECTION_PU,
    REGISTERSELECTION_PD,
    REGISTERSELECTION_PDSC,
    REGISTERSELECTION_PODC,
    REGISTERSELECTION_PIS,
    _NO_OF_REGISTERSELECTION_
}Port_Arc_RegisterSelectionType;


/**
 * Returns a pointer to a register for the supplied pinId.
 * First the pinId is used to get the port type, port number and bit through a
 * lookup table. Then the register address is fetched using the port type
 * and the register type (regType). Finally the address is adjusted using the
 * port number.
 *
 * @param regType Which register to get the address for. (For example
 * REGISTERSELECTION_PMC if you want the PMC register corresponding to the port
 * type and port number for the supplied pinId.
 * @param pinId This is the pinId as listed in Table 2.1 Pin Assignment 176-Pin
 *  LQFP in the Renesas RH850 Reference Manual. For example 3 if you want to
 *  read/write registers having to do with P10_5)
 * @param ModuleId Used by DET to track error.
 * @param ApiId Used by DET to track error.
 * @param ErrorId Used by DET to track error.
 * @return Pointer to the register.
 */
volatile uint16 * Port_Arc_getRegPointerFromPinId(Port_Arc_RegisterSelectionType regType, uint16 pinId, uint16 ModuleId, uint8 ApiId, uint8 ErrorId);

/**
 * Returns a pointer to a register for the supplied portGroup.
 *
 * Uses the portGroup and regType to return a pointer to the register that
 * should be used for this port group.
 *
 * @param regType Which register to get the address for. (For example
 * REGISTERSELECTION_PMC if you want the PMC register.
 * @param portGroup Which port group. (For example PORT_P18 if you want to
 * modify or read registers having to do with P18.)
 * @param ModuleId Used by DET to track error.
 * @param ApiId Used by DET to track error.
 * @param ErrorId Used by DET to track error.
 * @return Pointer to the register.
 */
volatile uint16 * Port_Arc_getRegPointerFromPort(Port_Arc_RegisterSelectionType regType, Port_Arc_PortGroups portGroup, uint16 ModuleId, uint8 ApiId, uint8 ErrorId);

/**
 * Sets one bit in the register pointed to by reg to flag.
 *
 * @param pinId This is the pinId as listed in Table 2.1 Pin Assignment 176-Pin
 *  LQFP in the Renesas RH850 Reference Manual. For example 3 if you want to
 *  write one bit in a register having to do with P10_5)
 * @param reg pointer to the register to set
 * @param flag boolean flag to set the bit in the register to
 */
void Port_Arc_setPin(uint16 pinId, volatile uint16 *reg, uint8 flag);

/**
 * Returns the value of one bit in the register pointed to by reg.
 * @param pinId This is the pinId as listed in Table 2.1 Pin Assignment 176-Pin
 *  LQFP in the Renesas RH850 Reference Manual. For example 3 if you want to
 *  read one bit in a register having to do with P10_5)
 * @param reg pointer to the register to set, in the above example should be
 * the address to Pxxx10 where xxx depends on the functionality you want to set.
 * @return 1 if the read bit is 1, 0 otherwise.
 */
uint8 Port_Arc_getPin(uint16 pinId, volatile uint16 *reg);

void Port_Arc_setProtectedPin(uint16 pinId, volatile uint16 *reg, uint8 flag);

#endif /* PORT_REGFINDER_H_ */
