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

#include "Port_RegFinder.h"
#include "rh850.h"
#if defined(USE_DET)
#include "Det.h"
#endif

typedef enum {
    PORTTYPE_P,
    PORTTYPE_JP,
    PORTTYPE_AP,
    PORTTYPE_IP,
    PORTTYPE_NOT_CONFIGURABLE
}ArcPort_PortType;

typedef struct {
    ArcPort_PortType    portType;
    uint8       portNr;
    uint8       bit;
} PinIdToPortTranslation;

#include "PortData_rh850f1l.h"
#include "PortData_rh850f1l.c"


typedef struct {
    const volatile uint16  *P;
    const volatile uint16  *AP;
    const volatile uint8   *JP;
    const volatile uint16  *IP;
} PortTypes;

PortTypes regs[_NO_OF_REGISTERSELECTION_] = {
        /*PMC    */{  &PMC0,       0U,   &JPMC0,       0U},
        /*PIPC   */{ &PIPC0,       0U,      0U,       0U},
        /*PM     */{   &PM0,   &APM0,    &JPM0,       0U},
#if defined(CFG_RH850F1H)
        /*PIBC   */{ &PIBC0, &APIBC0, &JPIBC0, &IPIBC0},
#else
        /*PIBC   */{ &PIBC0, &APIBC0,  &JPIBC0,       0U},
#endif
        /*PFC    */{  &PFC0,       0U,  &JPFC0,       0U},
        /*PFCE   */{ &PFCE0,       0U,      0U,       0U},
        /*PFCAE  */{&PFCAE0,       0U,      0U,       0U},
        /*PBDC   */{ &PBDC0,  &APBDC0, &JPBDC0,       0U},
#if defined(CFG_RH850F1H)
        /*PPR    */{  &PPR0,  &APPR0,  &JPPR0,  &IPPR0},
#else
        /*PPR    */{  &PPR0,   &APPR0,  &JPPR0,       0U},
#endif
        /*P      */{    &P0,     &AP0,    &JP0,       0U},
        /*PU     */{   &PU0,       0U,   &JPU0,       0U},
        /*PD     */{   &PD0,       0U,   &JPD0,       0U},
        /*PDSC   */{ (volatile uint16 *)0xFFC14600UL,       0U,       0U,       0U},
        /*PODC   */{ (volatile uint16 *)0xFFC14500UL,       0U, (volatile uint8 *)0xFFC20450,       0U},
        /*PIS    */{  &PIS0,       0U,       0U,       0U}
};

volatile uint16 * Port_Arc_getRegPointerFromPinId(Port_Arc_RegisterSelectionType regType, uint16 pinId, uint16 ModuleId, uint8 ApiId, uint8 ErrorId){
    volatile uint16 * retVal=0U;
    if( regType < _NO_OF_REGISTERSELECTION_){
        switch (PinIdToPort[pinId].portType) {
            case PORTTYPE_P:
                retVal = (volatile uint16 *)(((volatile unsigned char *)regs[regType].P)+(PinIdToPort[pinId].portNr*4));
                break;
            case PORTTYPE_AP:
                retVal = (volatile uint16 *)(((volatile unsigned char *)regs[regType].AP)+(PinIdToPort[pinId].portNr*4));
                break;
            case PORTTYPE_JP:
                retVal = (volatile uint16 *)regs[regType].JP;
                break;
            case PORTTYPE_IP:
                retVal = (volatile uint16 *)regs[regType].IP;
                break;
            default:
#if defined(USE_DET)
                Det_ReportError(ModuleId, 0U, ApiId, ErrorId );
#endif
                break;
        }
    }
    return retVal;
}

volatile uint16 * Port_Arc_getRegPointerFromPort(Port_Arc_RegisterSelectionType regType, Port_Arc_PortGroups portGroup, uint16 ModuleId, uint8 ApiId, uint8 ErrorId){
    volatile uint16 * retVal=0U;

    if( portGroup < _NR_OF_PORTGROUPS_){
        switch (Dio_PortTypeToRH850Port[portGroup].portType) {
            case PORTTYPE_P:
                retVal = (volatile uint16 *)(((volatile unsigned char *)regs[regType].P)+(Dio_PortTypeToRH850Port[portGroup].portNr*4));
                break;
            case PORTTYPE_AP:
                retVal = (volatile uint16 *)(((volatile unsigned char *)regs[regType].AP)+(Dio_PortTypeToRH850Port[portGroup].portNr*4));
                break;
            case PORTTYPE_JP:
                retVal = (volatile uint16 *)regs[regType].JP;
                break;
            case PORTTYPE_IP:
                retVal = (volatile uint16 *)regs[regType].IP;
                break;
            default:
#if defined(USE_DET)
                Det_ReportError(ModuleId, 0, ApiId, ErrorId );
#endif
                break;
        }
    }
    return retVal;
}

void Port_Arc_setPin(uint16 pinId, volatile uint16 *reg, uint8 flag) {

    uint16 regVal = (0x0001 << PinIdToPort[pinId].bit);
    if (flag > 0) {
        *reg |= regVal;
    }
    else {
        *reg &= ~regVal;
    }

}

#define protected_write(preg,reg,value)   preg=0xa5;\
                                          reg=value;\
                                          reg=~value;\
                                          reg=value;
#define PORT_BASE_ADDRESS 0xFFC10000UL
#define PORT_PPCMD_OFFSET 0x4C00UL
#define GET_PROT_REG_PTR(_port) (*(volatile unsigned long  *)(PORT_BASE_ADDRESS + PORT_PPCMD_OFFSET + (_port)*4))
void Port_Arc_setProtectedPin(uint16 pinId, volatile uint16 *reg, uint8 flag) {

    uint16 regVal = (0x0001 << PinIdToPort[pinId].bit);
    uint16 temp = *reg;
    if (flag > 0) {
        temp |= regVal;
    }  else {
        temp &= ~regVal;
    }
    if( temp != *reg ) {
        protected_write(GET_PROT_REG_PTR(PinIdToPort[pinId].portNr), *reg, temp);
    }
}

uint8 Port_Arc_getPin(uint16 pinId, volatile uint16 *reg) {
    uint16 retVal = 0;
    if ((0x0001 << PinIdToPort[pinId].bit) & (*reg)) {
        retVal = 1;
    }
    return retVal;
}
