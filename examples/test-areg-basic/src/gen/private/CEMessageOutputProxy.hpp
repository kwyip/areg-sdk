//////////////////////////////////////////////////////////////////////////
// Begin generate src/gen/private/CEMessageOutputProxy.hpp file
//////////////////////////////////////////////////////////////////////////
#ifndef  SRC_GEN_PRIVATE_CEMESSAGEOUTPUTPROXY_HPP
#define  SRC_GEN_PRIVATE_CEMESSAGEOUTPUTPROXY_HPP
/************************************************************************
 * (c) copyright    2021
 *                  Create by AREGtech code generator tool from source MessageOutput.
 * Generated at     21.04.2021  18:33:55 GMT+02:00 
 ************************************************************************/

/************************************************************************
 * \file            src/gen/private/CEMessageOutputProxy.hpp
 * \ingroup         MessageOutput Service Interface
 * \brief           This is an automatic generated code of MessageOutput Service Interface Proxy class declaration.
 ************************************************************************/

/************************************************************************
 * Include files
 ************************************************************************/
#include "areg/src/base/GEGlobal.h"
#include "src/gen/NEMessageOutput.hpp"
#include "areg/src/component/CEProxyBase.hpp"
 
/************************************************************************
 * Dependencies
 ************************************************************************/
class CEMessageOutputResponseEvent;
 
//////////////////////////////////////////////////////////////////////////
// CEMessageOutputProxy class declaration Begin
//////////////////////////////////////////////////////////////////////////
/**
 * \brief       MessageOutput Service Interface proxy class.
 *              Automatically instantiated per thread at client startup.
 *              Used to communicate with stub object and sending notifications
 *              to each client running in the thread instance.
 *
 *              The message output service to interact with user.
 **/
class CEMessageOutputProxy   : public CEProxyBase
{

private:
    //////////////////////////////////////////////////////////////////////////
    // CEMessageOutputProxy::CEMessageOutputServiceAvailableEvent class declaration
    //////////////////////////////////////////////////////////////////////////
    /**
     * \brief       The event is used to immediately notify new client
     *              about service availability and escape duplicating 
     *              notification for other, already connected clients.
     *  
     **/
    class CEMessageOutputServiceAvailableEvent : public CEProxyBase::CEServiceAvailableEvent
    {
    //////////////////////////////////////////////////////////////////////////
    // Runtime internals
    //////////////////////////////////////////////////////////////////////////
        DECLARE_RUNTIME_EVENT(CEMessageOutputProxy::CEMessageOutputServiceAvailableEvent)

    //////////////////////////////////////////////////////////////////////////
    // Constructor/ Destructor
    //////////////////////////////////////////////////////////////////////////
    public:
        /**
         * \brief   Sets event consumer object to deliver notification.
         **/
        CEMessageOutputServiceAvailableEvent( IENotificationEventConsumer & consumer );
        /**
         * \brief   Destructor
         **/
        virtual ~CEMessageOutputServiceAvailableEvent( void );
    //////////////////////////////////////////////////////////////////////////
    // Forbidden calls
    //////////////////////////////////////////////////////////////////////////
    private:
        CEMessageOutputServiceAvailableEvent( void );
        CEMessageOutputServiceAvailableEvent( const CEMessageOutputServiceAvailableEvent & /*src*/ );
        const CEMessageOutputServiceAvailableEvent & operator = ( const CEMessageOutputServiceAvailableEvent & /*src*/ );
    };
//////////////////////////////////////////////////////////////////////////
// CEMessageOutputProxy predefined constants and static members.
//////////////////////////////////////////////////////////////////////////
public:
    /**
     * \brief   Returns existing or creates new proxy object if it is not existing
     *          in the current thread scope.
     * \param   roleName        The role name of stub component object
     * \param   connectListener The reference to connection listener
     * \param   ownerThread     The instance of thread to dispatch messages.
     * \return  Returns pointer to instantiated proxy object.
     **/
    static CEMessageOutputProxy * CreateProxy( const char * roleName, IEProxyListener & connectListener, CEDispatcherThread & ownerThread );

    /**
     * \brief   Returns existing or creates new proxy object if it is not existing
     *          in the current thread scope.
     * \param   roleName        The role name of stub component object
     * \param   connectListener The reference to connection listener
     * \param   ownerThread     The name of thread instance to dispatch messages.
     *                          If NULL, current dispatching thread is used to dispatch messages.
     * \return  Returns pointer to instantiated proxy object.
     **/
    static CEMessageOutputProxy * CreateProxy( const char * roleName, IEProxyListener & connectListener, const char * ownerThread = static_cast<const char *>(NULL) );

//////////////////////////////////////////////////////////////////////////
// Constructor / Destructor. Protected
//////////////////////////////////////////////////////////////////////////
protected:
    /**
     * \brief   Constructor. Creates Proxy object by given role name. 
     *          Do not create proxy object directly, instead use CreateProxy function.
     * \param   roleName    The role name of proxy, i.e. role name of server component object.
     * \param   ownerThread The instance of thread to dispatch messages.
     *                      If NULL, current dispatching thread is used to dispatch messages.
     **/
    CEMessageOutputProxy( const char * roleName, CEDispatcherThread * ownerThread = static_cast<CEDispatcherThread *>(NULL) );
    /**
     * \brief   Destructor
     **/
    virtual ~CEMessageOutputProxy( void );

//////////////////////////////////////////////////////////////////////////
// Attributes and operations.
//////////////////////////////////////////////////////////////////////////
public:
/************************************************************************
 * Attributes
 ************************************************************************/
    /**
     * \brief   Returns true if value of LastMessage attribute is valid.
     *          If Update Notification is disabled, this method will return false.
     **/
    inline bool IsLastMessageValid( void ) const;
    /**
     * \brief   Returns the value of LastMessage attribute.
     *          To get valid value, the Update Notification should be enabled. 
     *          Attribute LastMessage description: 
     *          The last message to output on console.
     * \param   state   On returns, contains the validation flag of attribute data. 
     *                  Check validation flag before use attribute value.
     **/
    inline const CEString & GetLastMessage( NEService::eDataStateType & state ) const;

/************************************************************************
 * Parameters
 ************************************************************************/
    /**
     * \brief   Returns value of userAction of response call function.
     *          The parameter is validated and set when Proxy is getting response call.
     *          Parameter userAction description: 
     *          The action requested by user.
     **/
    inline const NEMessageOutput::eRequestedActons & GetParamuserAction( void ) const;

    /**
     * \brief   Returns value of msgInput of response call function.
     *          The parameter is validated and set when Proxy is getting response call.
     *          Parameter msgInput description: 
     *          The input message from the user.
     **/
    inline const CEString & GetParammsgInput( void ) const;

/************************************************************************
 * Requests
 ************************************************************************/
    /**
     * \brief   Request call.
     *          Sent to service to output message on console.
     * \param   msgOutput   The message requested to output on console.
     * \param   dateTime    The date and the time when it was requested.
     * \see     Has no Response.
     **/
    void RequestOutputMessage( const CEString & msgOutput, const CEDateTime & dateTime );

//////////////////////////////////////////////////////////////////////////
// Operations.
//////////////////////////////////////////////////////////////////////////
public:
    /**
     * \brief   Checks whether there is already listener of Notification Event
     *          exists. If does not exit, adds new listener entry in the listener
     *          list. If need, send appropriate message to Stub to start 
     *          sending attribute update messages. If already listener
     *          exists in listener list and notifyAlways flag is true, 
     *          sends immediate update notification based on existing update data status.
     * \param   msgId           The Notification Message ID
     * \param   consumer        The pointer of Notification Event consumer
     * \param   notifyAlways    The flag, indicating whether the notification event
     *                          should be send to client immediately if the notification
     *                          already exists. By default it is false. 
     **/
    inline void SetNotification( NEMessageOutput::eMessageIDs notifyId, IENotificationEventConsumer & listener, bool notifyAlways = false );
    /**
     * \brief   Clears listener entries of specified Notification Event consumer
     * \param   msgId       The Notification Message ID
     * \param   consumer    The pointer of Notification Event Consumer.
     * \return  
     **/
    inline void ClearNotification( NEMessageOutput::eMessageIDs notifyId, IENotificationEventConsumer & listener );
    /**
     * \brief   Clears all notification for specified listener and unregisters it
     * \param   listener    The notification consumer object, which should be unregistered.
     **/
    inline void ClearAllNotifications( IENotificationEventConsumer & listener );

//////////////////////////////////////////////////////////////////////////
// Overrides
//////////////////////////////////////////////////////////////////////////
protected:
/************************************************************************/
// IEProxyEventConsumer interface overrides.
/************************************************************************/
    /**
     * \brief   Method derived from IEProxyEventConsumer interface.
     *          Triggered when on the request to execute function
     *          on server side, Proxy have got response message.
     * \param   eventElem   The Service Response event object.
     *                      Contains response message and information
     *                      sent by Stub
     **/
    virtual void ProcessResponseEvent( CEServiceResponseEvent & eventElem );
    /**
     * \brief   Method derived from IEProxyEventConsumer interface.
     *          Triggered when on server side a certain Attribute 
     *          value has been updated.
     * \param   eventElem   The Service Response event object.
     *                      Contains new updated value of Attribute
     *                      and validation flag.
     **/
    virtual void ProcessAttributeEvent( CEServiceResponseEvent & eventElem );

/************************************************************************/
// CEProxyBase interface overrides.
/************************************************************************/

    /**
     * \brief   Creates notification event to send to client objects. 
     *          All Notification Events should be internal events and 
     *          should be instances of CENotificationEvent class.
     * \param   data    The Notification Event data object containing
     *                  notification information.
     * \return  Returns new created notification event object.
     **/
    virtual CENotificationEvent * CreateNotificationEvent( const CENotificationEventData & data ) const;

    /**
     * \brief   Create Request event to send to Stub object. 
     *          Request events are triggering request calls on Stub side.
     * \param   args    The buffer containing serialized arguments of request call.
     * \param   reqId   The ID of request call.
     * \return  Return pointer of valid Request event.
     **/
    virtual CEServiceRequestEvent * CreateRequestEvent( const CEEventDataStream & args, unsigned int reqId );

    /**
     * \brief   Creates event requesting to receive update notification events.
     *          The caller should be address of current proxy and the target 
     *          should address of appropriate sub address.
     * \param   msgId       The message ID to send. Should be either attribute or response (info)
     * \param   reqType     The type of request.
     * \return  Returns valid pointer of created service request event object.
     **/
    virtual CEServiceRequestEvent * CreateNotificationRequestEvent( unsigned int msgId, NEService::eRequestType reqType );

    /**
     * \brief   Overwrite method to create response event from streaming object for 
     *          further dispatching by proxy.
     * \param   stream  Streaming object, which contains event data.
     * \return  If operation succeeds, returns valid pointer to Service Response event object.
     *          Otherwise, it returns NULL.
     **/
    virtual CERemoteResponseEvent * CreateRemoteResponseEvent( const IEInStream & stream ) const;

    /**
     * \brief   Overwrite method to create error remote response event.
     *          Function is triggered when remote request sent by proxy failed and did not reach target.
     * \param   addrProxy   Address of Proxy object, which sent request event
     * \param   msgId       Message ID, which was requested to process
     * \param   reason      Failure reason set by system
     * \param   seqNr       The sequence number of processing message.
     **/
    virtual CERemoteResponseEvent * CreateRemoteRequestFailedEvent( const CEProxyAddress & addrProxy, unsigned int msgId, NEService::eResultType reason, unsigned int seqNr ) const;

    /**
     * \brief   Overwrite this method to create service available event to new instantiated clients.
     * \param   consumer    The instance of consumer, which receives service available event.
     * \return  If succeeds, returns valid pointer to service available event object.
     **/
    virtual CEProxyBase::CEServiceAvailableEvent * CreateServiceAvailableEvent( IENotificationEventConsumer & consumer );

    /**
     * \brief   Called to register all servicing listeners. It is called when proxy is instantiated.
     *          Overwrite method to add service event listeners.
     **/
    virtual void RegisterServiceListeners( void );

    /**
     * \brief   Called to unregister all servicing listeners. It is called when proxy is freed.
     *          Overwrite method to remove service event listeners.
     **/
    virtual void UnregisterServiceListeners( void );

//////////////////////////////////////////////////////////////////////////
// Member variables
//////////////////////////////////////////////////////////////////////////
private:
/************************************************************************
 * Attribute members
 ************************************************************************/
    /**
     * \brief   LastMessage attribute value.
     *          The last message to output on console.
     **/
    CEString                            mLastMessage;

/************************************************************************
 * Parameter members
 ************************************************************************/
    /**
     * \brief   userAction parameter value.
     *          The action requested by user.
     **/
    NEMessageOutput::eRequestedActons   mParamuserAction;

    /**
     * \brief   msgInput parameter value.
     *          The input message from the user.
     **/
    CEString                            mParammsgInput;

//////////////////////////////////////////////////////////////////////////
// Hidden methods
//////////////////////////////////////////////////////////////////////////
private:
/************************************************************************
 * Hidden operations
 ************************************************************************/
    /**
     * \brief   Updates attribute and response call variable data received from Stub
     * \param   eventElem   The event object containing buffer with serialized data
     * \param   respId      The response message ID, which received. 
     *                      It is either attribute or response message ID
     **/
    void UpdateData( CEMessageOutputResponseEvent & eventElem, NEMessageOutput::eMessageIDs respId );
    /**
     * \brief   Starts processing response message. The received event contains
     *          ID of appropriate message to update and contains result flag.
     *          If request calls failed (busy), the ID in event is a request call ID.
     *          In all other cases, the ID is either response call, info call, 
     *          or attribute update notification call. 
     *          It will also update parameters and states.
     * \param   evenElem    The response object containing message ID, result and data.
     **/
    void ProcessResponse( CEMessageOutputResponseEvent & evenElem );

    /**
     * \brief   returns reference CEMessageOutputProxy object
     **/
    inline CEMessageOutputProxy & self( void );

/************************************************************************
 * Hidden static operations
 ************************************************************************/
private:
    /**
     * \brief   Create proxy object.
     * \param   roleName    The server component role name
     * \param   ownerThread The instance of thread to dispatch messages.
     *                      If NULL, current dispatching thread is used to dispatch messages.
     * \return  Pointer to instantiated proxy object.
     **/
    static CEProxyBase * _createProxy( const char * roleName, CEDispatcherThread * ownerThread = static_cast<CEDispatcherThread *>(NULL) );
    /**
     * \brief   Creates and returns service interface data object.
     **/
    static const NEService::SInterfaceData & _createInterfaceData( void );
};

//////////////////////////////////////////////////////////////////////////
// CEMessageOutputProxy class declaration End
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// CEMessageOutputProxy class inline functions implementation
//////////////////////////////////////////////////////////////////////////

/************************************************************************
 * Inline operations
 ************************************************************************/

inline void CEMessageOutputProxy::SetNotification( NEMessageOutput::eMessageIDs notifyId, IENotificationEventConsumer & listener, bool notifyAlways /* = false */ )
{   CEProxyBase::SetNotification(static_cast<unsigned int>(notifyId), &listener, notifyAlways); }

inline void CEMessageOutputProxy::ClearNotification( NEMessageOutput::eMessageIDs notifyId, IENotificationEventConsumer & listener )
{   CEProxyBase::ClearNotification(static_cast<unsigned int>(notifyId), &listener); }

inline void CEMessageOutputProxy::ClearAllNotifications( IENotificationEventConsumer & listener )
{   CEProxyBase::UnregisterListener( &listener ); }

inline CEMessageOutputProxy & CEMessageOutputProxy::self( void )
{   return (*this); }

/************************************************************************
 * Inline attributes
 ************************************************************************/

inline bool CEMessageOutputProxy::IsLastMessageValid( void ) const
{   return (GetProxyData().GetAttributeState(NEMessageOutput::MSG_ID_LastMessage) == NEService::DATA_OK);   }

inline const CEString & CEMessageOutputProxy::GetLastMessage( NEService::eDataStateType & state ) const
{   state = GetProxyData().GetAttributeState(NEMessageOutput::MSG_ID_LastMessage); return mLastMessage;  }

/************************************************************************
 * Inline parameters
 ************************************************************************/

inline const NEMessageOutput::eRequestedActons & CEMessageOutputProxy::GetParamuserAction( void ) const
{   return mParamuserAction;  }

inline const CEString & CEMessageOutputProxy::GetParammsgInput( void ) const
{   return mParammsgInput;  }

#endif   // SRC_GEN_PRIVATE_CEMESSAGEOUTPUTPROXY_HPP

//////////////////////////////////////////////////////////////////////////
// End generate src/gen/private/CEMessageOutputProxy.hpp file
//////////////////////////////////////////////////////////////////////////