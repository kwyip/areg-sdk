//////////////////////////////////////////////////////////////////////////
// Begin generate gen/shared/CECentralMessagerClientBase.hpp file
//////////////////////////////////////////////////////////////////////////
#ifndef  GEN_SHARED_CECENTRALMESSAGERCLIENTBASE_HPP
#define  GEN_SHARED_CECENTRALMESSAGERCLIENTBASE_HPP
/************************************************************************
 * (c) copyright    2019
 *                  Create by AREGtech code generator tool from source CentralMessager.
 * Generated at     24.08.2019  21:12:29 GMT+02:00 
 ************************************************************************/

/************************************************************************
 * \file            gen/shared/CECentralMessagerClientBase.hpp
 * \ingroup         CentralMessager Service Interface
 * \brief           This is an automatic generated code of CentralMessager Service Interface Client base class declaration.
 ************************************************************************/

/************************************************************************
 * Include files
 ************************************************************************/
#include "gen/shared/NECentralMessager.hpp"
#include "areg/core/component/CEClientBase.hpp"
#include "areg/core/component/IEProxyListener.hpp"
#include "areg/core/component/CENotificationEvent.hpp"

#include "gen/shared/private/CECentralMessagerProxy.hpp"

/************************************************************************
 * Dependencies
 ************************************************************************/
class CEComponent;
class CEDispatcherThread;

//////////////////////////////////////////////////////////////////////////
// CECentralMessagerClientBase class declaration.
//////////////////////////////////////////////////////////////////////////
/**
 * \brief       The interface of CentralMessager Service Interface
 *              Client base object. This object should be inherited
 *              and overrides should be implemented.
 *
 *              This service is receiving message from connected client when they are typed or 
 *              requested to be send. The service receives text message from initiator and
 *              broadcast to all clients, which have subscribed on event.
 *              It as well broadcasts own text message to all connected clients.
 **/
class CECentralMessagerClientBase  : public    IEProxyListener, private CEClientBase
{
//////////////////////////////////////////////////////////////////////////
// Constructor / Destructor. Protected
//////////////////////////////////////////////////////////////////////////
protected:
    /**
     * \brief   Constructs and initialize CentralMessager Service Interface client object
     * \param   roleName    The role name assigned to CentralMessager servicing component object.
     * \param   ownerThread The name of component owner thread to dispatch messages.
     *                      If NULL, all messages are dispatched in current component thread.
     **/
    CECentralMessagerClientBase( const char* const roleName, const char * ownerThread = static_cast<const char *>(NULL) );

    /**
     * \brief   Constructs and initialize CentralMessager Service Interface client object.
     * \param   roleName    The role name assigned to CentralMessager servicing component object.
     * \param   ownerThread The instance of component owner thread to dispatch messages.
     **/
    CECentralMessagerClientBase( const char* const roleName, CEDispatcherThread & ownerThread );

    /**
     * \brief   Constructs and initialize CentralMessager Service Interface client object.
     * \param   roleName    The role name assigned to CentralMessager servicing component object.
     * \param   owner       The instance of client owner component. The component object should be already initialized.
     * \note    When this constructor is used, it is important that the CEComponent object is already initialized.
     *          and the component thread is set.
     **/
    CECentralMessagerClientBase( const char* const roleName, CEComponent & owner );

    /**
     * \brief   Destructor.
     **/
    virtual ~CECentralMessagerClientBase( void );

//////////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////////
public:
    /**
     * \brief   Clears all notifications, stops receiving notifications from server
     **/
    void ClearAllNotifications( void );

    /**
     * \brief   Returns true if the specified certain notification is already assigned.
     *          Otherwise returns false.
     * \param   msgId   The ID of message to check.
     **/
    const bool IsNotificationAssigned( const NECentralMessager::eMessageIDs msgId ) const;

    /**
     * \brief   Returns true if client object has got connection with servicing component
     **/
    bool IsConnected( void ) const;

//////////////////////////////////////////////////////////////////////////
// Start Service Interface operations / attributes and overrides declaration
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// CentralMessager Interface Attributes
//////////////////////////////////////////////////////////////////////////
public:

//////////////////////////////////////////////////////////////////////////
// CentralMessager Interface Requests / Responses / Informations
//////////////////////////////////////////////////////////////////////////
public:

/************************************************************************
 * Request SendMessage
 ************************************************************************/
    /**
     * \brief   Request call.
     *          Request to sends message that all clients can see.
     * \param   nickName    The nick name of initiator
     * \param   cookie      Cookie given by connection manager. Should not be invalid.
     * \param   newMessage  The message sent by connected initiator
     * \param   dateTime    The timestamp create on local host of initiator
     * \see     Has no response
     **/
    inline void RequestSendMessage( const CEString & nickName, const unsigned int & cookie, const CEString & newMessage, const CEDateTime & dateTime );
    /**
     * \brief   Overwrite to handle error of SendMessage request call.
     * \param   FailureReason   The failure reason value of request call.
     **/
    virtual void RequestSendMessageFailed( const NEService::eResultType FailureReason );
    
/************************************************************************
 * Request KeyTyping
 ************************************************************************/
    /**
     * \brief   Request call.
     *          Sent each time when typing a key
     * \param   nickName    The nick name of initiator
     * \param   cookie      The cookie assigned to initiator
     * \param   newMessage  The message typed.
     * \see     Has no response
     **/
    inline void RequestKeyTyping( const CEString & nickName, const unsigned int & cookie, const CEString & newMessage );
    /**
     * \brief   Overwrite to handle error of KeyTyping request call.
     * \param   FailureReason   The failure reason value of request call.
     **/
    virtual void RequestKeyTypingFailed( const NEService::eResultType FailureReason );
    
/************************************************************************
 * Broadcast SendMessage
 ************************************************************************/
    /**
     * \brief   Server broadcast.
     *          The response, sent by connection manager to notify the message typing update
     *          Overwrite, if need to handle Information call of server object. 
     *          This call will be automatically triggered, on every appropriate request call
     * \param   nickName    The nick name of initiator
     * \param   cookie      The cookie assigned to initiator
     * \param   newMessage  The message sent by initiator
     * \param   dateTime    The local timestamp of initiator
     **/
    virtual void BroadcastSendMessage( const CEString & nickName, const unsigned int & cookie, const CEString & newMessage, const CEDateTime & dateTime );
    /**
     * \brief   Call to enable or disable receiving notifications on SendMessage information call.
     *          This function is triggered, when client object is interested only on response result
     *          without triggering request call.
     * \param   notify  If true, notification will be enable. If false, notification is disabled
     **/
    inline void NotifyOnBroadcastSendMessage( bool notify = true );

/************************************************************************
 * Broadcast KeyTyping
 ************************************************************************/
    /**
     * \brief   Server broadcast.
     *          Sent each time when a client is typing a key
     *          Overwrite, if need to handle Information call of server object. 
     *          This call will be automatically triggered, on every appropriate request call
     * \param   nickName    The nick name of initiator
     * \param   cookie      Assigned cookie of initiator
     * \param   newMessage  The message typed by initiator
     **/
    virtual void BroadcastKeyTyping( const CEString & nickName, const unsigned int & cookie, const CEString & newMessage );
    /**
     * \brief   Call to enable or disable receiving notifications on KeyTyping information call.
     *          This function is triggered, when client object is interested only on response result
     *          without triggering request call.
     * \param   notify  If true, notification will be enable. If false, notification is disabled
     **/
    inline void NotifyOnBroadcastKeyTyping( bool notify = true );

/************************************************************************
 * Broadcast BroadcastMessage
 ************************************************************************/
    /**
     * \brief   Server broadcast.
     *          Server broadcasts a message to all clients.
     *          Overwrite, if need to handle Information call of server object. 
     *          This call will be automatically triggered, on every appropriate request call
     * \param   serverMessage   The message sent by servicing server
     * \param   dateTime        The timestamp of servicing component
     **/
    virtual void BroadcastBroadcastMessage( const CEString & serverMessage, const CEDateTime & dateTime );
    /**
     * \brief   Call to enable or disable receiving notifications on BroadcastMessage information call.
     *          This function is triggered, when client object is interested only on response result
     *          without triggering request call.
     * \param   notify  If true, notification will be enable. If false, notification is disabled
     **/
    inline void NotifyOnBroadcastBroadcastMessage( bool notify = true );

//////////////////////////////////////////////////////////////////////////
// End Service Interface operations / attributes and overrides declaration
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Overrides
//////////////////////////////////////////////////////////////////////////
protected:
/************************************************************************/
// IEProxyListener Overrides
/************************************************************************/
    /**
     * \brief   Triggered by Proxy, when gets service connected event.
     *          Make client initializations in this function. No request
     *          will be processed until this function is not called for
     *          client object. Also set listeners here if client is interested
     *          to receive update notifications.
     * \param   isConnected     The flag, indicating whether service is connected
     *                          or disconnected. Make cleanups and stop sending
     *                          requests or assigning for notification if
     *                          this flag is false. No event to Stub target will
     *                          be sent, until no service connected event is
     *                          received.
     * \param   proxy           The Service Interface Proxy object, which is
     *                          notifying service connection.
     * \return  Return true if this service connect notification was relevant to client object,
     *          i.e. if passed Proxy address is equal to the Proxy object that client has.
     *          If Proxy objects are not equal, it should return false;
     **/
    virtual bool ServiceConnected( const bool isConnected, CEProxyBase & proxy );

protected:
/************************************************************************/
// CECentralMessagerClientBase Error Handling overrides
/************************************************************************/

    /**
     * \brief   Overwrite this method if need to make error handling on invalid response
     * \param   InvalidRespId   The ID of invalid response
     **/
    virtual void InvalidResponse( const NECentralMessager::eMessageIDs InvalidRespId );

    /**
     * \brief   Overwrite this method if need to make error handling on invalid request
     * \param   InvalidReqId    The ID of invalid request
     **/
    virtual void InvalidRequest( const NECentralMessager::eMessageIDs InvalidReqId );
    
    /**
     * \brief   By default, the function calls appropriate request failure function.
     *          Overwrite this method if need to make error handling on request failed.
     * \param   msgId           The ID of either response of request message, which failed. Normally ID of request.
     * \param   FailureReason   The failure reason value of request call.
     **/
    virtual void RequestFailed( const NECentralMessager::eMessageIDs FailureMsgId, const NEService::eResultType FailureReason );

//////////////////////////////////////////////////////////////////////////
// Attributes
//////////////////////////////////////////////////////////////////////////
protected:

    /**
     * \brief   Returns the current sequence number
     **/
    unsigned int GetCurrentSequenceNr( void ) const;

    /**
     * \brief   Call to recreate Proxy for the client. This call will remove and unregister all existing notifications
     *          and the client will not receive pending update or response notifications. 
     *          The client first will receive disconnect message, then again connect.
     *          Reset update notifications manually in connect if need.          
     *          This function call can be used when the client instance should be registered and run in new thread.
     *
     * \return  Returns true if Proxy was created with success.
     **/
     bool RecreateProxy( void );

     /**
      * \brief  Returns pointer to client dispatcher thread where the messages are dispatched.
      *         The function can return NULL if Proxy was not instantiated yet.
      **/
     CEDispatcherThread * GetDispatcherThread( void );

//////////////////////////////////////////////////////////////////////////
// Member variables
//////////////////////////////////////////////////////////////////////////
private:
    /**
     * \brief   Connection flag. If true, the client object is connected to server
     **/
    bool                mIsConnected;
    /**
     * \brief   The counter of sequence number
     **/
    unsigned int        mCurrSequenceNr;
    /**
     * \brief   Pointer of Proxy object providing communication
     **/
    CECentralMessagerProxy *   mProxy;

//////////////////////////////////////////////////////////////////////////
// Hidden methods
//////////////////////////////////////////////////////////////////////////
private:
/************************************************************************/
// IENotificationEventConsumer overrides
/************************************************************************/

    /**
     * \brief   Is processing notification event calls.
     * \param   eventElem   Notification Event object to process
     **/
    virtual void ProcessNotificationEvent( CENotificationEvent & eventElem );
    
private:
    /**
     * \brief   Enables / Disables notification flags on appropriate message call.
     * \param   msgId   The ID of message to enable / disable notification
     * \param   notify  If true, the notification is enabled. 
     *                  If false, the notification is disabled.
     * \param   always  Flag, indicating whether should notify always or not.
     *                  if 'notify' parameter is true and the notification is already
     *                  assigned, then if parameter 'always' is true, it will trigger
     *                  notification immediately after call. 
     **/
    void NotifyOn( const NECentralMessager::eMessageIDs msgId, bool notify, bool always = false );
    /**
     * \brief   Returns reference of CECentralMessagerClientBase object
     **/
    CECentralMessagerClientBase & self( void );

//////////////////////////////////////////////////////////////////////////
// Forbidden calls
//////////////////////////////////////////////////////////////////////////
private:
    CECentralMessagerClientBase( void );
    CECentralMessagerClientBase( const CECentralMessagerClientBase & /* src */ );
    const CECentralMessagerClientBase & operator = ( const CECentralMessagerClientBase & /* src */ );
};

//////////////////////////////////////////////////////////////////////////
// CECentralMessagerClientBase class inline functions implementation
//////////////////////////////////////////////////////////////////////////

inline CECentralMessagerClientBase & CECentralMessagerClientBase::self( void )
{   return (*this);         }

inline unsigned int CECentralMessagerClientBase::GetCurrentSequenceNr( void ) const
{   return mCurrSequenceNr; }

inline bool CECentralMessagerClientBase::IsConnected( void ) const
{   return mIsConnected;    }

inline const bool CECentralMessagerClientBase::IsNotificationAssigned( const NECentralMessager::eMessageIDs msgId ) const
{   return mProxy->HasNotificationListener(static_cast<const unsigned int>(msgId));   }

/************************************************************************
 * Request calls
 ************************************************************************/

inline void CECentralMessagerClientBase::RequestSendMessage( const CEString & nickName, const unsigned int & cookie, const CEString & newMessage, const CEDateTime & dateTime )
{   mProxy->RequestSendMessage( nickName, cookie, newMessage, dateTime );   }

inline void CECentralMessagerClientBase::RequestKeyTyping( const CEString & nickName, const unsigned int & cookie, const CEString & newMessage )
{   mProxy->RequestKeyTyping( nickName, cookie, newMessage );   }

/************************************************************************
 * Broadcast notifications
 ************************************************************************/

inline void CECentralMessagerClientBase::NotifyOnBroadcastSendMessage( bool notify /* = true */ )
{   NotifyOn(NECentralMessager::MSG_ID_BroadcastSendMessage, notify, false);    }

inline void CECentralMessagerClientBase::NotifyOnBroadcastKeyTyping( bool notify /* = true */ )
{   NotifyOn(NECentralMessager::MSG_ID_BroadcastKeyTyping, notify, false);    }

inline void CECentralMessagerClientBase::NotifyOnBroadcastBroadcastMessage( bool notify /* = true */ )
{   NotifyOn(NECentralMessager::MSG_ID_BroadcastBroadcastMessage, notify, false);    }

#endif   // GEN_SHARED_CECENTRALMESSAGERCLIENTBASE_HPP

//////////////////////////////////////////////////////////////////////////
// End generate gen/shared/CECentralMessagerClientBase.hpp file
//////////////////////////////////////////////////////////////////////////