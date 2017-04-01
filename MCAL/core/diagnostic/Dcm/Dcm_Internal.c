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

#include <string.h>
#include "Dcm.h"
#include "Dcm_Internal.h"
#include "MemMap.h"
#ifndef DCM_NOT_SERVICE_COMPONENT
#include "Rte_Dcm.h"
#endif
#if defined(USE_NVM)
#include "NvM.h"
#endif

/* Disable MISRA 2004 rule 16.2, MISRA 2012 rule 17.2.
 * This because of recursive calls to readDidData.
 *  */
//lint -estring(974,*recursive*)

typedef struct {
    uint8   session;
    uint8   testerSrcAddr;
    uint8   protocolId;
    boolean requestFullComm;
    boolean requested;
}DcmProtocolRequestType;

typedef void (*Dcm_StartProtocolNotificationFncType)(boolean started);

typedef struct {
    uint8 priority;
    Dcm_StartProtocolNotificationFncType StartProtNotification;
}DcmRequesterConfigType;



static DcmProtocolRequestType ProtocolRequests[DCM_NOF_REQUESTERS];
static boolean ProtocolRequestsAllowed = FALSE;

boolean lookupNonDynamicDid(uint16 didNr, const Dcm_DspDidType **didPtr)
{
    const Dcm_DspDidType *dspDid = Dcm_ConfigPtr->Dsp->DspDid;
    boolean didFound = FALSE;

    while ((dspDid->DspDidIdentifier != didNr) &&  (FALSE == dspDid->Arc_EOL)) {
        dspDid++;
    }

    /* @req Dcm651 */
    if ((FALSE == dspDid->Arc_EOL) && (!((TRUE == dspDid->DspDidInfoRef->DspDidDynamicllyDefined) && DID_IS_IN_DYNAMIC_RANGE(didNr)) ) ) {
        didFound = TRUE;
        *didPtr = dspDid;
    }

    return didFound;
}

boolean lookupDynamicDid(uint16 didNr, const Dcm_DspDidType **didPtr)
{
    const Dcm_DspDidType *dspDid = Dcm_ConfigPtr->Dsp->DspDid;
    boolean didFound = FALSE;

    if( DID_IS_IN_DYNAMIC_RANGE(didNr) ) {
        while ((dspDid->DspDidIdentifier != didNr) &&  (FALSE == dspDid->Arc_EOL)) {
            dspDid++;
        }

        /* @req Dcm651 */
        if ((FALSE == dspDid->Arc_EOL) && (TRUE == dspDid->DspDidInfoRef->DspDidDynamicllyDefined)) {
            didFound = TRUE;
            *didPtr = dspDid;
        }
    }

    return didFound;
}

Dcm_NegativeResponseCodeType readDidData(const Dcm_DspDidType *didPtr, PduInfoType *pduTxData, uint16 *txPos,
        ReadDidPendingStateType *pendingState, uint16 *pendingDid, uint16 *pendingSignalIndex, uint16 *pendingDataLen, uint16 *didIndex, uint16 didStartIndex, uint16 *didDataStartPos)
{
    Dcm_NegativeResponseCodeType responseCode = DCM_E_POSITIVERESPONSE;

    boolean didOnlyRefsDids = ((NULL == didPtr->DspSignalRef));
    if (didPtr->DspDidInfoRef->DspDidAccess.DspDidRead != NULL) {  /** @req DCM433 */
        if (TRUE == DspCheckSessionLevel(didPtr->DspDidInfoRef->DspDidAccess.DspDidRead->DspDidReadSessionRef)) { /** @req DCM434 */
            if (TRUE == DspCheckSecurityLevel(didPtr->DspDidInfoRef->DspDidAccess.DspDidRead->DspDidReadSecurityLevelRef)) { /** @req DCM435 */
                if( (FALSE == didOnlyRefsDids) && (*didIndex >= didStartIndex)) {
                    /* Get the data if available */
                    responseCode = getDidData(didPtr, pduTxData, txPos, pendingState, pendingDataLen, pendingSignalIndex, didDataStartPos);
                    if(DCM_E_RESPONSEPENDING == responseCode) {
                        *pendingDid = didPtr->DspDidIdentifier;
                    } else if( DCM_E_POSITIVERESPONSE == responseCode ) {
                        /* Data successfully read */
                        (*didIndex)++;
                        *pendingSignalIndex = 0;
                    }else{
                        /* do nothing */
                    }
                } else {
                    /* This did only references other dids or did already read. */
                    if( *didIndex >= didStartIndex ) {
                        /* Not already read. */
                        if ((*txPos + 2) <= pduTxData->SduLength) {
                            pduTxData->SduDataPtr[(*txPos)] = (didPtr->DspDidIdentifier >> 8) & 0xFFu;
                            (*txPos)++;
                            pduTxData->SduDataPtr[(*txPos)] = didPtr->DspDidIdentifier & 0xFFu;
                            (*txPos)++;
                            responseCode = DCM_E_POSITIVERESPONSE;
                        } else {
                            /* Tx buffer full. */
                            responseCode = DCM_E_REQUESTOUTOFRANGE;
                        }
                    }
                    (*didIndex)++;
                }
            }
            else {  // Not allowed in current security level
                responseCode = DCM_E_SECURITYACCESSDENIED;
            }
        }
        else {  // Not allowed in current session
            responseCode = DCM_E_REQUESTOUTOFRANGE;/** @req DCM433 */
        }
    }
    else {  // Read access not configured
        responseCode = DCM_E_REQUESTOUTOFRANGE;
    }

    for (uint16 i = 0; (FALSE == didPtr->DspDidRef[i]->Arc_EOL) && (DCM_E_POSITIVERESPONSE == responseCode); i++) {
        /* Recurse trough the rest of the dids. *//** @req DCM440 */
        responseCode = readDidData(didPtr->DspDidRef[i], pduTxData, txPos, pendingState, pendingDid, pendingSignalIndex, pendingDataLen, didIndex, didStartIndex, didDataStartPos);
    }

    return responseCode;
}


Dcm_NegativeResponseCodeType getDidData(const Dcm_DspDidType *didPtr, const PduInfoType *pduTxData, uint16 *txPos, ReadDidPendingStateType *pendingState, uint16 *pendingDataLen, uint16 *pendingSignalIndex, uint16 *didDataStartPos)
{
    Dcm_NegativeResponseCodeType errorCode = DCM_E_POSITIVERESPONSE;
    Dcm_OpStatusType opStatus = DCM_INITIAL;
    Std_ReturnType result = E_OK;
    const Dcm_DspSignalType *signalPtr;
    const Dcm_DspDataType *dataPtr;
    if( (DCM_READ_DID_PENDING_COND_CHECK == *pendingState) || (DCM_READ_DID_PENDING_READ_DATA == *pendingState) ){
        opStatus = DCM_PENDING;
    } else {
        pduTxData->SduDataPtr[*txPos] = (didPtr->DspDidIdentifier >> 8u) & 0xFFu;
        (*txPos)++;
        pduTxData->SduDataPtr[*txPos] = didPtr->DspDidIdentifier & 0xFFu;
        (*txPos)++;
        *didDataStartPos = *txPos;
    }
    /* @req Dcm578 Skipping condition check for ECU_SIGNALs */

    for(uint16 signalIndex = *pendingSignalIndex; (signalIndex < didPtr->DspNofSignals) && (DCM_E_POSITIVERESPONSE == errorCode); signalIndex++) {
        signalPtr = &didPtr->DspSignalRef[signalIndex];
        dataPtr = signalPtr->DspSignalDataRef;

        if( ((DCM_READ_DID_PENDING_COND_CHECK == *pendingState) || (DCM_READ_DID_IDLE == *pendingState)) && (DATA_PORT_ECU_SIGNAL != dataPtr->DspDataUsePort)) {
            /* @req Dcm439 */
            if((DATA_PORT_ASYNCH == dataPtr->DspDataUsePort) || (DATA_PORT_SYNCH == dataPtr->DspDataUsePort)) {
                if( NULL != dataPtr->DspDataConditionCheckReadFnc ) {
                    result = dataPtr->DspDataConditionCheckReadFnc(opStatus, &errorCode);
                } else {
                    result = E_NOT_OK;
                }
                if(DATA_PORT_ASYNCH == dataPtr->DspDataUsePort) {
                    if( E_PENDING == result ) {
                        *pendingState = DCM_READ_DID_PENDING_COND_CHECK;
                    } else {
                        *pendingState = DCM_READ_DID_IDLE;
                        opStatus = DCM_INITIAL;
                    }
                } else {
                    if( E_PENDING == result ) {
                        DCM_DET_REPORTERROR(DCM_GLOBAL_ID, DCM_E_UNEXPECTED_RESPONSE);
                        result = E_NOT_OK;
                    }
                }
            }
#if defined(USE_NVM) && defined(DCM_USE_NVM_DID)
            else if(DATA_PORT_BLOCK_ID == dataPtr->DspDataUsePort){
                /* @req DCM560 */
                if (E_OK == NvM_ReadBlock(dataPtr->DspNvmUseBlockID, &pduTxData->SduDataPtr[(*txPos)])) {
                    *pendingState = DCM_READ_DID_PENDING_READ_DATA;
                }else{
                    DCM_DET_REPORTERROR(DCM_GLOBAL_ID, DCM_E_UNEXPECTED_RESPONSE);
                    result = E_NOT_OK;
                }
            }
#endif
            else {
                /* Port not supported */
                DCM_DET_REPORTERROR(DCM_GLOBAL_ID, DCM_E_CONFIG_INVALID);
                result = E_NOT_OK;
            }
        } else {
            /* Condition check function already called with positive return */
            result = E_OK;
            errorCode = DCM_E_POSITIVERESPONSE;
        }

        if ((result == E_OK) && (errorCode == DCM_E_POSITIVERESPONSE)) {    /** @req DCM439 */
            uint16 dataLen = 0;
            if ( TRUE == dataPtr->DspDataInfoRef->DspDidFixedLength ) {  /** @req DCM436 */
                dataLen = dataPtr->DspDataSize;
            } else {
                if (dataPtr->DspDataReadDataLengthFnc != NULL) {
                    if( DCM_READ_DID_IDLE == *pendingState ) {
                        /* ReadDataLengthFunction is only allowed to return E_OK  */
                        if(E_OK != dataPtr->DspDataReadDataLengthFnc(&dataLen)) {
                            DCM_DET_REPORTERROR(DCM_GLOBAL_ID, DCM_E_UNEXPECTED_RESPONSE);
                            result = E_NOT_OK;
                        }
                    } else {
                        /* Read length function has already been called */
                        dataLen = *pendingDataLen;
                    }
                }
            }
            if( E_OK == result ) {
                // Now ready for reading the data!
                if ((*didDataStartPos + signalPtr->DspSignalsPosition + dataLen) <= pduTxData->SduLength) {
                    /** @req DCM437 */
                    if((DATA_PORT_SYNCH == dataPtr->DspDataUsePort ) || (DATA_PORT_ECU_SIGNAL == dataPtr->DspDataUsePort)) {
                        if( NULL != dataPtr->DspDataReadDataFnc.SynchDataReadFnc ) {
                            /* Synch read function is only allowed to return E_OK */
                            if(E_OK != dataPtr->DspDataReadDataFnc.SynchDataReadFnc(&pduTxData->SduDataPtr[(*didDataStartPos) + signalPtr->DspSignalsPosition]) ) {
                                DCM_DET_REPORTERROR(DCM_GLOBAL_ID, DCM_E_UNEXPECTED_RESPONSE);
                                result = E_NOT_OK;
                            }
                        } else {
                            result = E_NOT_OK;
                        }
                    } else if( DATA_PORT_ASYNCH == dataPtr->DspDataUsePort ) {
                        if( NULL != dataPtr->DspDataReadDataFnc.AsynchDataReadFnc ) {
                            result = dataPtr->DspDataReadDataFnc.AsynchDataReadFnc(opStatus, &pduTxData->SduDataPtr[(*didDataStartPos) + signalPtr->DspSignalsPosition]);
                        } else {
                            result = E_NOT_OK;
                        }
#if defined(USE_NVM) && defined(DCM_USE_NVM_DID)
                    } else if ( DATA_PORT_BLOCK_ID == dataPtr->DspDataUsePort ){
                        NvM_RequestResultType errorStatus;
                        if (E_OK != NvM_GetErrorStatus(dataPtr->DspNvmUseBlockID, &errorStatus)){
                            DCM_DET_REPORTERROR(DCM_GLOBAL_ID, DCM_E_UNEXPECTED_RESPONSE);
                            result = E_NOT_OK;
                        }
                        if (errorStatus == NVM_REQ_PENDING){
                            result = E_PENDING;
                        }else if (errorStatus == NVM_REQ_OK){
                            *pendingState = DCM_READ_DID_IDLE;
                        }else{
                            DCM_DET_REPORTERROR(DCM_GLOBAL_ID, DCM_E_UNEXPECTED_RESPONSE);
                            result = E_NOT_OK;
                        }
#endif
                    }else {
                        /* Port not supported */
                        DCM_DET_REPORTERROR(DCM_GLOBAL_ID, DCM_E_CONFIG_INVALID);
                        result = E_NOT_OK;
                    }
                    if( *txPos < ((*didDataStartPos) + signalPtr->DspSignalsPosition + dataLen) ) {
                        *txPos = ((*didDataStartPos) + signalPtr->DspSignalsPosition + dataLen);
                    }

                    if( E_PENDING == result ) {
                        *pendingState = DCM_READ_DID_PENDING_READ_DATA;
                        *pendingDataLen = dataLen;
                        *pendingSignalIndex = signalIndex;
                        errorCode = DCM_E_RESPONSEPENDING;
                    }
                    else if (result != E_OK) {
                        errorCode = DCM_E_CONDITIONSNOTCORRECT;
                    } else {
                        /* Did successfully read */
                        *pendingState = DCM_READ_DID_IDLE;
                    }
                } else { // tx buffer full
                    errorCode = DCM_E_REQUESTOUTOFRANGE;
                }
            } else {// Invalid return from readLenFunction
                errorCode = DCM_E_CONDITIONSNOTCORRECT;
            }
        } else if( E_PENDING == result ) {
            /* Pending condition check */
            *pendingSignalIndex = signalIndex;
            errorCode = DCM_E_RESPONSEPENDING;
        } else {    // CheckRead failed
            errorCode = DCM_E_CONDITIONSNOTCORRECT;
        }
    }

    return errorCode;
}


void getDidLength(const Dcm_DspDidType *didPtr, uint16 *length, uint16* nofDatas)
{

    boolean didOnlyRefsDids = ((NULL == didPtr->DspSignalRef));

    if( FALSE == didOnlyRefsDids) {
        /* Get the data if available */
        (*length) += didPtr->DspDidDataSize;
        (*nofDatas)++;
    }

    for (uint16 i = 0; FALSE == didPtr->DspDidRef[i]->Arc_EOL; i++) {
        /* Recurse trough the rest of the dids. */
        getDidLength(didPtr->DspDidRef[i], length, nofDatas);
    }

}

void DcmResetDiagnosticActivityOnSessionChange(Dcm_SesCtrlType newSession)
{
    DspResetDiagnosticActivityOnSessionChange(newSession);
    DsdCancelPendingExternalServices();
}

void DcmResetDiagnosticActivity(void)
{
    DcmDspResetDiagnosticActivity();
    DsdCancelPendingExternalServices();
}

/**
 * Function for canceling pending requests
 */
void DcmCancelPendingRequests()
{
    DspCancelPendingRequests();
    DsdCancelPendingExternalServices();
}
/**
 *
 * @param requester
 * @param session
 * @param protocolId
 * @param testerSrcAddr
 * @param requestFullComm
 * @return E_OK: Operation successful, E_NOT_OK: Operation failed
 */
Std_ReturnType DcmRequestStartProtocol(DcmProtocolRequesterType requester, uint8 session, uint8 protocolId, uint8 testerSrcAddr, boolean requestFullComm)
{
    Std_ReturnType ret = E_NOT_OK;
    if( (requester < DCM_NOF_REQUESTERS) && (TRUE == ProtocolRequestsAllowed) ) {
        ProtocolRequests[requester].requested = TRUE;
        ProtocolRequests[requester].session = session;
        ProtocolRequests[requester].testerSrcAddr = testerSrcAddr;
        ProtocolRequests[requester].protocolId = protocolId;
        ProtocolRequests[requester].requestFullComm = requestFullComm;
        ret = E_OK;
    }
    return ret;
}

/**
 * Checks for protocol start requests and tries to start the highest prioritized
 */
void DcmExecuteStartProtocolRequest(void)
{
   static const DcmRequesterConfigType DcmRequesterConfig[DCM_NOF_REQUESTERS] = {
        [DCM_REQ_DSP] = {
                .priority = 0,
                .StartProtNotification = DcmDspProtocolStartNotification
        },
    #if defined(DCM_USE_SERVICE_RESPONSEONEVENT) && defined(USE_NVM)
        [DCM_REQ_ROE] = {
                .priority = 1,
                .StartProtNotification = DcmRoeProtocolStartNotification
        },
    #endif
    };
    DcmProtocolRequesterType decidingRequester = DCM_NOF_REQUESTERS;
    boolean requestFullComm = FALSE;
    uint8 currPrio = 0xff;
    for( uint8 requester = 0; requester < (uint8)DCM_NOF_REQUESTERS; requester++ ) {
        if( TRUE == ProtocolRequests[requester].requested ) {
            if(DcmRequesterConfig[requester].priority < currPrio ) {
                currPrio = DcmRequesterConfig[requester].priority;
                decidingRequester = (DcmProtocolRequesterType)requester;
                requestFullComm = ProtocolRequests[requester].requestFullComm;
            }
        }
    }
    if(  decidingRequester != DCM_NOF_REQUESTERS ) {
        /* Find out if fullcomm should be requested */
        for( uint8 requester = 0; requester <(uint8)DCM_NOF_REQUESTERS; requester++ ) {
            if( (TRUE == ProtocolRequests[requester].requested) && (ProtocolRequests[requester].requestFullComm == TRUE) &&
                    (ProtocolRequests[requester].session == ProtocolRequests[decidingRequester].session) &&
                    (ProtocolRequests[requester].testerSrcAddr == ProtocolRequests[decidingRequester].testerSrcAddr) &&
                    (ProtocolRequests[requester].protocolId == ProtocolRequests[decidingRequester].protocolId) ) {
                requestFullComm = TRUE;
            }
        }
        Std_ReturnType ret = DslDspSilentlyStartProtocol(ProtocolRequests[decidingRequester].session, ProtocolRequests[decidingRequester].protocolId, (uint16)ProtocolRequests[decidingRequester].testerSrcAddr, requestFullComm);
        /* Notify requesters */
        boolean started;
        for( uint8 requester = 0; requester <(uint8)DCM_NOF_REQUESTERS; requester++ ) {
            if( ProtocolRequests[requester].requested == TRUE ) {
                started = FALSE;
                if( (ProtocolRequests[requester].session == ProtocolRequests[decidingRequester].session) &&
                        (ProtocolRequests[requester].testerSrcAddr == ProtocolRequests[decidingRequester].testerSrcAddr) &&
                        (ProtocolRequests[requester].protocolId == ProtocolRequests[decidingRequester].protocolId) ) {
                    started = (E_OK == ret) ? TRUE : FALSE;
                }
                if( NULL != DcmRequesterConfig[requester].StartProtNotification ) {
                    DcmRequesterConfig[requester].StartProtNotification(started);
                }
            }
        }
    }
}

/**
 * Sets allowance to request protocol start
 * @param allowed
 */
void DcmSetProtocolStartRequestsAllowed(boolean allowed)
{
    if( (TRUE == allowed) && (FALSE == ProtocolRequestsAllowed)) {
        memset(ProtocolRequests, 0, sizeof(ProtocolRequests));
    }
    ProtocolRequestsAllowed = allowed;
}
