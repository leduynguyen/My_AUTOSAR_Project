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








#ifndef CAN_TEST_H_
#define CAN_TEST_H_

void CT_CanIf_TxConfirmation_Called( PduIdType canTxPduId );
void CT_CanIf_RxIndication_Called( uint8 Hrh,Can_IdType CanId,uint8 CanDlc, const uint8 *CanSduPtr );
void CT_CanIf_CancelTxConfirmation_Called( const Can_PduType *PduInfoPtr );
void CT_CanIf_ControllerBusOff_Called( uint8 Controller );
void CT_CanIf_ControllerWakeup_Called( uint8 Controller );

#endif /*CAN_TEST_H_*/
