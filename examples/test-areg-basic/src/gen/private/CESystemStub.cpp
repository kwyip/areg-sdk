//////////////////////////////////////////////////////////////////////////
// Begin generate src/gen/private/CESystemStub.cpp file
//////////////////////////////////////////////////////////////////////////
/************************************************************************
 * (c) copyright    2021
 *                  Create by AREGtech code generator tool from source System.
 * Generated at     21.04.2021  18:33:57 GMT+02:00 
 ************************************************************************/

/************************************************************************
 * \file            src/gen/private/CESystemStub.cpp
 * \ingroup         System Service Interface
 * \brief           This is an automatic generated code of System Service Interface Stub class implementation.
 ************************************************************************/

/************************************************************************
 * Includes
 ************************************************************************/
#include "src/gen/CESystemStub.hpp"
#include "src/gen/private/CESystemEvents.hpp"

#include "areg/src/component/CEServiceResponseEvent.hpp"
#include "areg/src/base/CEThread.hpp"
#include "areg/src/trace/GETrace.h"

//////////////////////////////////////////////////////////////////////////
// CESystemStub class implementation
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Constructor / Destructor
//////////////////////////////////////////////////////////////////////////
CESystemStub::CESystemStub( CEComponent & masterComp )
    : CEStubBase    ( masterComp, NESystem::CreateInterfaceData() )
    
    , mSystemState        (  )
    , mSystemStateState   ( NEService::DATA_UNAVAILABLE )
    
{
    ; // do nothing
}

CESystemStub::~CESystemStub( void )
{
    ; // do nothing
}

//////////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////////

void CESystemStub::UnlockAllRequests( void )
{
    CEStubBase::CancelAllRequests( );
}

//////////////////////////////////////////////////////////////////////////
// Overrides
//////////////////////////////////////////////////////////////////////////

void CESystemStub::ProcessStubEvent( CEStubEvent & eventElem )
{
    ; // do nothing
}

void CESystemStub::ProcessGenericEvent( CEEvent & eventElem )
{
    ; // do nothing
}

DEF_TRACE_SCOPE(src_gen_CESystemStub_StartupServiceInterface);
void CESystemStub::StartupServiceInterface( CEComponent & holder )
{
    TRACE_SCOPE(src_gen_CESystemStub_StartupServiceInterface);
    
    CESystemRequestEvent::AddListener( static_cast<IEEventConsumer &>(self()), CEThread::GetCurrentThreadName() );
    CESystemNotifyRequestEvent::AddListener( static_cast<IEEventConsumer &>(self()), CEThread::GetCurrentThreadName() );
    CEStubBase::StartupServiceInterface( holder );

    TRACE_DBG("The Stub Service [ %s ] of component with role name [ %s ] has been started and is available ...", mAddress.GetServiceName().GetBuffer(), mAddress.GetRoleName().GetBuffer());
}

DEF_TRACE_SCOPE(src_gen_CESystemStub_ShutdownServiceIntrface);
void CESystemStub::ShutdownServiceIntrface( CEComponent & holder )
{
    TRACE_SCOPE(src_gen_CESystemStub_ShutdownServiceIntrface);
    TRACE_DBG("The Stub Service [ %s ] of component with role name [ %s ] is shutting down and not available anymore ...", mAddress.GetServiceName().GetBuffer(), mAddress.GetRoleName().GetBuffer());
    
    CESystemRequestEvent::RemoveListener( static_cast<IEEventConsumer &>(self()), CEThread::GetCurrentThreadName() );
    CESystemNotifyRequestEvent::RemoveListener( static_cast<IEEventConsumer &>(self()), CEThread::GetCurrentThreadName() );
    CEStubBase::ShutdownServiceIntrface( holder );
}

unsigned int CESystemStub::GetNumberOfRequests( void ) const
{
    return NESystem::NumberofRequests;
}

unsigned int CESystemStub::GetNumberOfResponses( void ) const
{
    return NESystem::NumberofResponses;
}

unsigned int CESystemStub::GetNumberOfAttributes( void ) const
{
    return NESystem::NumberofAttributes;
}

const unsigned int * CESystemStub::GetRequestIds( void ) const
{
    return reinterpret_cast<const unsigned int *>(NESystem::RequestIds);
}

const unsigned int * CESystemStub::GetResponseIds( void ) const
{
    return reinterpret_cast<const unsigned int *>(NESystem::ResponseIds);
}

const unsigned int * CESystemStub::GetAttributeIds( void ) const
{
    return reinterpret_cast<const unsigned int *>(NESystem::AttributeIds);
}

CEResponseEvent * CESystemStub::CreateResponseEvent( const CEProxyAddress & proxy, unsigned int msgId, NEService::eResultType result, const CEEventDataStream & data ) const
{
    return (data.IsEmpty() == false ? DEBUG_NEW CESystemResponseEvent(data, proxy, result, msgId) : DEBUG_NEW CESystemResponseEvent(proxy, result, msgId));
}

CERemoteRequestEvent * CESystemStub::CreateRemoteServiceRequestEvent( const IEInStream & stream ) const
{
    // not relevant for local stub
    return static_cast<CERemoteRequestEvent *>(NULL);
}

CERemoteNotifyRequestEvent * CESystemStub::CreateRemoteNotifyRequestEvent( const IEInStream & stream ) const
{
    // not relevant for local stub
    return static_cast<CERemoteNotifyRequestEvent *>(NULL);
}

const CEVersion & CESystemStub::GetImplVersion( void ) const
{
    return NESystem::InterfaceVersion;
}

DEF_TRACE_SCOPE(src_gen_CESystemStub_SendNotification);
void CESystemStub::SendNotification( unsigned int msgId )
{
    CEEventDataStream args(CEEventDataStream::EventDataInternal);
    IEOutStream & stream = args.GetStreamForWrite();

    switch ( static_cast<NESystem::eMessageIDs>(msgId) )
    {
    case NESystem::MSG_ID_SystemState:
        mSystemStateState = NEService::DATA_OK;
        stream << mSystemState;
        SendUpdateEvent(msgId, args, NEService::RESULT_DATA_OK);
        break;

    default:
        {
            TRACE_SCOPE(src_gen_CESystemStub_SendNotification);
            TRACE_ERR("Unexpected attribute ID [ %d ] requested to send by Stub [ %s ].", msgId, CEStubAddress::ConvertAddressToPath(mAddress).GetBuffer());
            ASSERT(false);
        }
        break; // do nothing
    }
}
DEF_TRACE_SCOPE(src_gen_CESystemStub_ErrorRequest);
void CESystemStub::ErrorRequest( unsigned int msgId, bool msgCancel )
{
    NEService::eResultType result = NEService::RESULT_NOT_PROCESSED;
    unsigned int listenerId = static_cast<unsigned int>(msgId);
    
    switch ( static_cast<NESystem::eMessageIDs>(msgId) )
    {
/************************************************************************
 * Attribute errors
 ************************************************************************/
    case NESystem::MSG_ID_SystemState:
        mSystemStateState = NEService::DATA_INVALID;
        result = NEService::RESULT_DATA_INVALID;
        break;

/************************************************************************
 * Response errors
 ************************************************************************/
/************************************************************************
 * Broadcast errors
 ************************************************************************/
/************************************************************************
 * Request errors
 ************************************************************************/
    case NESystem::MSG_ID_RequestPowerOff:
    case NESystem::MSG_ID_RequestPowerOn:
    case NESystem::MSG_ID_RequestShutdown:
    case NESystem::MSG_ID_RequestStart:
        listenerId = NESystem::GetResponseId(static_cast< NESystem::eMessageIDs>(msgId));
        result = msgCancel ? NEService::RESULT_REQUEST_CANCELED : NEService::RESULT_REQUEST_ERROR;
        break;

    default:
        OUTPUT_ERR("Unexpected message ID [ %d ] received!", msgId);
        ASSERT(false);
        break;
    }
    
    CEStubBase::CEStubListenerList listeners;
    if ( FindListeners(listenerId, listeners) > 0 )
    {
        TRACE_SCOPE(src_gen_CESystemStub_ErrorRequest);
        TRACE_WARN(" >>> The message [ %s ] of Stub [ %s ] is responding with error [ %s ], sending message [ %s ] to [ %d ] targets... <<<"
                        , NESystem::GetString( static_cast<NESystem::eMessageIDs>(msgId) )
                        , CEStubAddress::ConvertAddressToPath(mAddress).GetBuffer()
                        , NEService::GetString( result )
                        , NESystem::GetString(static_cast<NESystem::eMessageIDs>(msgId))
                        , listeners.GetSize() );

        CEStubBase::SendErrorNotification(listeners, CESystemResponseEvent(listeners[0].mProxy, result, msgId));
    }
}

/************************************************************************
 * Set attributes and send notifications
 ************************************************************************/

void CESystemStub::SetSystemState( const NESystem::eSystemState & newValue )
{
    if ( (mSystemStateState != NEService::DATA_OK) || (mSystemState != newValue) )
    {
        mSystemState = newValue;
        SendNotification( NESystem::MSG_ID_SystemState );
    }
}

/************************************************************************
 * Send responses
 ************************************************************************/

/************************************************************************
 * Send Broadcast
 ************************************************************************/

/************************************************************************
 * Process messages
 ************************************************************************/

DEF_TRACE_SCOPE(src_gen_CESystemStub_ProcessRequestEvent);
void CESystemStub::ProcessRequestEvent( CEServiceRequestEvent & eventElem )
{
    ASSERT( NEService::IsRequestId(eventElem.GetRequestId()) );
    CESystemRequestEvent * reqEvent = RUNTIME_CAST(&eventElem, CESystemRequestEvent);

    if ( (reqEvent != static_cast<CESystemRequestEvent *>(NULL)) && (reqEvent->GetRequestType() == NEService::REQUEST_CALL) )
    {
        unsigned int reqId          = reqEvent->GetRequestId();
        CEStubBase::CEListener listener( reqId, 0, reqEvent->GetEventSource() );

        switch ( static_cast<NESystem::eMessageIDs>(reqId) )
        {
        case NESystem::MSG_ID_RequestPowerOff:
            if ( true )
            {
                RequestPowerOff(  );
            }
            break;
            
        case NESystem::MSG_ID_RequestPowerOn:
            if ( true )
            {
                RequestPowerOn(  );
            }
            break;
            
        case NESystem::MSG_ID_RequestShutdown:
            if ( true )
            {
                RequestShutdown(  );
            }
            break;
            
        case NESystem::MSG_ID_RequestStart:
            if ( true )
            {
                RequestStart(  );
            }
            break;
            
        default:
            {
                TRACE_SCOPE(src_gen_CESystemStub_ProcessRequestEvent);
                TRACE_ERR("Unexpected request ID [ %d ] to process in Stub [ %s ]!", reqId, CEStubAddress::ConvertAddressToPath(mAddress).GetBuffer());
                ASSERT(false);
            }
            break;
        }
    }
    CancelCurrentRequest();
}

DEF_TRACE_SCOPE(src_gen_CESystemStub_ProcessAttributeEvent);
void CESystemStub::ProcessAttributeEvent( CEServiceRequestEvent & eventElem )
{
    const NEService::eRequestType reqType = eventElem.GetRequestType();
    if (reqType == NEService::REQUEST_REMOVE_ALL_NOTIFY)
    {
        CEIntegerArray removedIds;
        CEStubBase::ClearAllListeners(eventElem.GetEventSource(), removedIds);
    }
    else
    {
        NESystem::eMessageIDs updId  = static_cast<NESystem::eMessageIDs>(eventElem.GetRequestId());
        if (reqType == NEService::REQUEST_STOP_NOTIFY)
        {
            RemoveNotificationListener( static_cast<unsigned int>(updId), eventElem.GetEventSource() );
        }
        else if (reqType == NEService::REQUEST_START_NOTIFY)
        {
#ifdef  _DEBUG
            if (AddNotificationListener( static_cast<unsigned int>(updId), eventElem.GetEventSource() ) == false )
            {
                TRACE_SCOPE(src_gen_CESystemStub_ProcessAttributeEvent);
                TRACE_WARN("The notification request of message ID [ %s ] of sources [ %s ] is already registered. Ignoring start notification registration request."
                            , NESystem::GetString(updId)
                            , CEProxyAddress::ConvertAddressToPath(eventElem.GetEventSource()).GetBuffer());
            }
#else   // _DEBUG
            AddNotificationListener( static_cast<unsigned int>(updId), eventElem.GetEventSource() );
#endif  // _DEBUG
            CEEventDataStream args(CEEventDataStream::EventDataInternal);
            NEService::eResultType validUpdate = NEService::RESULT_DATA_OK;
            IEOutStream & stream               = args.GetStreamForWrite();

            switch (updId)
            {
            case NESystem::MSG_ID_SystemState:
                if ( mSystemStateState == NEService::DATA_OK )
                    stream << mSystemState;
                else
                    validUpdate = NEService::RESULT_DATA_INVALID;
                break;

            default:
#ifdef  _DEBUG
                if ( NEService::IsResponseId(static_cast<unsigned int>(updId)) == false )
                {
                    TRACE_SCOPE(src_gen_CESystemStub_ProcessAttributeEvent);
                    TRACE_ERR("Unexpected notification request of attribute ID [ %d ] received in Stub [ %s ]!", updId, CEStubAddress::ConvertAddressToPath(GetAddress()).GetBuffer());
                    ASSERT(false);
                }
#endif // _DEBUG
                validUpdate = NEService::RESULT_DATA_INVALID;
                updId       = NESystem::MSG_ID_NO_PROCEED;
                break;
            }

            if (updId != NESystem::MSG_ID_NO_PROCEED)
                SendUpdateEvent( static_cast<unsigned int>(updId), args, validUpdate );
        }
    }
}

//////////////////////////////////////////////////////////////////////////
// End generate src/gen/private/CESystemStub.cpp file
//////////////////////////////////////////////////////////////////////////