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








//
// Module Id:s from document "List of Basic Sofware Modules" Rev 1.2.1  Part of release 3.0
//

#ifndef MODULES_H
#define MODULES_H

#include "Std_Types.h"

#define VENDOR_ID_ARCCORE   (60u)

#define MODULE_ID_OS       (1u) // Os

#define MODULE_ID_RTE      (2u) // Runtime Environment

#define MODULE_ID_ECUM    (10u) // ECU state manager
#define MODULE_ID_FIM     (11u) // Function Inhibition Manager
#define MODULE_ID_COMM    (12u) // Communication manager
#define MODULE_ID_WDGM    (13u) // Watchdog manager

#define MODULE_ID_DET     (15u) // Development Error Tracer

#define MODULE_ID_NVM     (20u) // NVRAM Manager
#define MODULE_ID_FEE     (21u) // Flash EEPROM Emulation
#define MODULE_ID_MEMIF   (22u) // Memory Abstraction Interface
#define MODULE_ID_NM      (29u) // Generic network management
#define MODULE_ID_OSEKNM  (30u) // Osek network management

#define MODULE_ID_CANNM   (31u) // Can network management
#define MODULE_ID_FRNM    (32u) // Flexray network management
#define MODULE_ID_UDPNM   (33u)  // UDP network management
#define MODULE_ID_CANTP   (35u) // Can transport layer
#define MODULE_ID_FRTP    (36u) // Flexray transport protocol
#define MODULE_ID_J1939TP (37u) // J1939 Transport protocol (Autosar 4)
#define MODULE_ID_EA      (40u) // EEPROM Abstraction

#define MODULE_ID_BSWM    (42u) // BSW Mode Manager
#define MODULE_ID_WDGIF   (43u) // Watchdog interface
#define MODULE_ID_LDCOM   (49u) /* Large Data Com */
#define MODULE_ID_COM     (50u) // Autosar COM
#define MODULE_ID_PDUR    (51u) // PDU router
#define MODULE_ID_IPDUM   (52u) // IPDU Multiplexer
#define MODULE_ID_DCM     (53u) // Diagnostic Communication Manager
#define MODULE_ID_DEM     (54u) // Diagnostic Event Manager
#define MODULE_ID_DLT     (55u) // Diagnostic Log and Trace
#define MODULE_ID_SOAD    (56u) // Socket Adaptor

#define MODULE_ID_CANIF   (60u) // CAN Interface
#define MODULE_ID_FRIF    (61u) // Flexray interface
#define MODULE_ID_LINIF   (62u) // LIN interface
#define MODULE_ID_LINNM   (63u) // LIN network management
#define MODULE_ID_ETHIF   (65u) // Ethernet Interface

#define MODULE_ID_CANTRCV (70u) // Can tranceiver driver
#define MODULE_ID_FRTRCV  (71u) // Flexray tranceiver driver

#define MODULE_ID_CAN     (80u) // Can Driver
#define MODULE_ID_FR      (81u) // Flexray driver
#define MODULE_ID_LIN     (82u) // LIN Driver
#define MODULE_ID_SPI     (83u) // SPI Handler Driver
#define MODULE_ID_ETHTRCV (73u)// Ethernet transceiver
#define MODULE_ID_ETH     (88u) // Ethernet Driver

#define MODULE_ID_EEP     (90u) // EEPROM Driver
#define MODULE_ID_FLS     (92u) // Flash driver
#define MODULE_ID_RAMTST  (93u) // RAM test

#define MODULE_ID_GPT    (100u) // GPT driver
#define MODULE_ID_MCU    (101u) // MCU driver
#define MODULE_ID_WDG    (102u) // Watchdog driver

#define MODULE_ID_DIO    (120u) // Dio driver
#define MODULE_ID_PWM    (121u) // PWM driver
#define MODULE_ID_ICU    (122u) // ICU Driver
#define MODULE_ID_ADC    (123u) // ADC driver
#define MODULE_ID_PORT   (124u) // Port driver

#define MODULE_ID_SCHM   (130u) // BSW Scheduler Module
#define MODULE_ID_STBM   (160u) // Sync Time base Manger

#define MODULE_ID_CANSM  (140u) // Can state manager
#define MODULE_ID_LINSM  (141u) // LIN state manager
#define MODULE_ID_FRSM   (142u) // Flexray state manager
#define MODULE_ID_ETHSM  (143u) // Ethernet State Management
#define MODULE_ID_SOMEIPXF   (148u) // SOME/IP Transformer
#define MODULE_ID_SECOC  (150u) // Secure onboard communication
#define MODULE_ID_ETHTSYN    (164u) // Time Sync Over Ethernet
#define MODULE_ID_SD	 (171u) // Service Discovery

#define MODULE_ID_TCPIP  (170u) // Ethernet State Management

#define MODULE_ID_E2EXF   (176u) // E2E Transformer
#define MODULE_ID_CRC    (201u) // CRC Routines
#define MODULE_ID_CAL    (206u) // Cypto abstraction library
#define MODULE_ID_E2E    (207u) // End-to-end protections

#define MODULE_ID_CANXCP (210u) // Can specific XCP module

#define MODULE_ID_C2CAN  (220u) // CAN
#define MODULE_ID_C2COM  (221u) // COM Services
#define MODULE_ID_C2DIAG (222u) // Diagnostic
#define MODULE_ID_C2FW   (223u) // ECU Firmware
#define MODULE_ID_C2FR   (224u) // FlexRay
#define MODULE_ID_C2LIN  (225u) // LIN
#define MODULE_ID_C2MMGT (226u) // Mode Management

#define MODULE_ID_IO     (254u) // IO Hardware Abstraction
#define MODULE_ID_CPLX   (255u) // Complex drivers


#endif
