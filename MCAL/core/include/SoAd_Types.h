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
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.2.2 */

#ifndef SOAD_TYPES_H
#define SOAD_TYPES_H

#include "TcpIp_Types.h"

/** @req SWS_SOAD_00512 */
typedef enum{
    SOAD_SOCON_ONLINE,
    SOAD_SOCON_RECONNECT,
    SOAD_SOCON_OFFLINE
}SoAd_SoConModeType;

typedef enum {
    SOAD_AF_INET = 0x02,	// Use IPv4
    SOAD_AF_INET6 = 0x1c	// Use IPv6
} SoAd_DomainType;

typedef struct {
    uint16	dummy;
} TcpIpLocalAddr;

// IMPROVEMENT: Where shall these enums be defined?
typedef enum{
    SOAD_SOCKET_PROT_TCP,
    SOAD_SOCKET_PROT_UDP
}SoAd_SocketProtocolType;

/** @req SWS_SOAD_00518 */
typedef uint16 SoAd_SoConIdType; // NOTE: Could be uint16 if SoAdSoConMax is > 256

/* 10.2.11 SoAdSocketRemoteAddress */
typedef struct{
    boolean Set;	// Does this Socket Connection have a Remote Address Set?
    TcpIp_DomainType	Domain;
    uint8  SocketRemoteIpAddress[4];
    uint16  SocketRemotePort;
} SoAd_SocketRemoteAddressType;

/* 10.2.16 SoAdRoutingGroup */
typedef struct{
    uint16  RoutingGroupId;
    boolean RoutingGroupIsEnabledAtInit;
    boolean RoutingGroupTxTriggerable;
} SoAd_RoutingGroupType;

/* 10.2.7 SoAdSocketConnection */
typedef struct{
    uint16						    SocketId;
    SoAd_SocketRemoteAddressType*	SoAdSocketRemoteAddress;
    uint8*							nPduUdpTxBuffer;
    uint32							nPduUdpTxBufferSize;
    uint8*							TcpRxBuffer;
    uint32							TcpRxBufferSize;
    uint32 							GroupNr;   // NOTE: Added to keep track of group belonging
    uint32 							IndexInGroup;   // NOTE: Added to keep track of group belonging
}SoAd_SocketConnectionType;


/* 10.2.9 SoAdSocketUdp */
typedef struct{
    uint32  UdpAliveSupervisionTimeout;
    boolean SocketUdpListenOnly;
    boolean SocketUdpStrictHeaderLenCheckEnabled;
    uint32  SocketUdpTriggerTimeout;
}SoAd_SocketUdpType;

/* 10.2.10 SoAdSocketTcp */
typedef struct{
    boolean SocketTcpImmediateTpTxConfirmation;
    boolean SocketTcpInitiate;
    boolean SocketTcpKeepAlive;
    uint32  SocketTcpKeepAliveInterval;
    uint16  SocketTcpKeepAliveProbesMax;
    uint32  SocketTcpKeepAliveTime;
    boolean SocketTcpNoDelay;
    uint32  SocketTcpTxQuota;
}SoAd_SocketTcpType;

typedef enum{
    SOAD_GROUPTYPE_LONELY_UDP,	// UDP group with only one SoCon. Uses one TCP/IP socket connected to the SoCon
    SOAD_GROUPTYPE_MULTI_UDP,	// UDP group with multiple SoCons. Uses one TCP/IP socket connected to the SoCon group.
    SOAD_GROUPTYPE_LISTEN_TCP,	// TCP group with TcpInitiate==false. Uses one TCP/IP socket connected to the SoCon group to listen and then spawns new ones connected to the SoCons as connections are established.
    SOAD_GROUPTYPE_INIT_TCP,	// TCP group with TcpInitiate==true. Used one TCP/IP socket for each SoSon, connected to the SoCon. No TCP/IP socket connected to the SoCon group.
}SoAd_GroupTypeType;


/* 10.2.6 SoAdSocketConnectionGroup */
 typedef struct  {
    boolean                     PduHeaderEnable;
    boolean                     ResourceManagementEnable;
    boolean                     SocketAutomaticSoConSetup;
    boolean                     SocketFramePriorityUsed;
    uint8                       SocketFramePriority;
    boolean                     SocketIpAddrAssignmentChgNotification;
    void (*SocketIpAddrAssignmentChgNotificationFunction)(SoAd_SoConIdType SoConId, TcpIp_IpAddrStateType State);
    uint16                      SocketLocalPort;
    boolean                     SocketMsgAcceptanceFilterEnabled;
    boolean                     SocketSoConModeChgNotification;
    void (*SocketSoConModeChgNotificationFunction)(SoAd_SoConIdType SoConId, SoAd_SoConModeType Mode);
    uint16                      SocketTpRxBufferMin;
    uint8			            SocketLocalAddressRef;
    const SoAd_SocketConnectionType*  	SoAdSocketConnection;
    const SoAd_SocketProtocolType     	SocketProtocol;
    const SoAd_SocketUdpType*         	SocketProtocolUdp;
    const SoAd_SocketTcpType*         	SocketProtocolTcp;
    const SoAd_GroupTypeType        	GroupType;
    uint16                      NrOfSocketConnections;  // NOTE: Added in implementation
} SoAd_SocketConnectionGroupType;


#endif
