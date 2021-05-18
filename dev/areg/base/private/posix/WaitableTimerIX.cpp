/************************************************************************
 * \file        areg/base/private/posix/WaitableTimerIX.cpp
 * \ingroup     AREG SDK, Asynchronous Event Generator Software Development Kit
 * \author      Artak Avetyan (mailto:artak@aregtech.com)
 * \brief       AREG Platform, POSIX Waitable Timer class.
 *
 ************************************************************************/

 /************************************************************************
  * Includes
  ************************************************************************/

#include "areg/base/private/posix/WaitableTimerIX.hpp"

#ifdef  _POSIX
#include "areg/base/NEMemory.hpp"
#include "areg/base/Thread.hpp"
#include "areg/base/private/posix/NESynchTypesIX.hpp"
#include "areg/base/private/posix/SynchLockAndWaitIX.hpp"
#include <signal.h>


void WaitableTimerIX::_posixTimerRoutine(union sigval si)
{
    WaitableTimerIX *timer = reinterpret_cast<WaitableTimerIX *>(si.sival_ptr);

    OUTPUT_DBG("Fired waitable timer [ %p ], processing in thread [ %p ]", timer, pthread_self());
    if ( timer != NULL )
    {
        timer->_timerExpired();
    }
}


WaitableTimerIX::WaitableTimerIX(bool isAutoReset /*= false*/, bool isSignaled /*= true*/, const char * name /*= NULL*/)
    : IEWaitableBaseIX  ( NESynchTypesIX::SoWaitTimer, false, name )

    , mResetInfo        ( isAutoReset ? NESynchTypesIX::EventResetAutomatic : NESynchTypesIX::EventResetManual )
    , mTimerId          ( static_cast<timer_t>(0) )
    , mTimeout          ( 0 )
    , mIsSignaled       ( isSignaled )
    , mFiredCount       ( 0 )
    , mDueTime          ( )
    , mThreadId     ( Thread::INVALID_THREAD_ID )
{

}

WaitableTimerIX::~WaitableTimerIX(void)
{
    _resetTimer();
}

bool WaitableTimerIX::setTimer(unsigned int msTimeout, bool isPeriodic)
{
    bool result = false;    
    ObjectLockIX lock(*this);

    _resetTimer();
    if (msTimeout != 0)
    {
        struct sigevent sigEvent;
        NEMemory::zeroBuffer(static_cast<void *>(&sigEvent), sizeof(struct sigevent));
        sigEvent.sigev_notify           = SIGEV_THREAD;
        sigEvent.sigev_value.sival_ptr  = static_cast<void *>(this);
        sigEvent.sigev_notify_function  = &WaitableTimerIX::_posixTimerRoutine;
        sigEvent.sigev_notify_attributes= NULL;

        if (RETURNED_OK == timer_create(CLOCK_REALTIME, &sigEvent, &mTimerId))
        {
            struct itimerspec interval;
            NEMemory::zeroBuffer(static_cast<void *>(&interval), sizeof(struct itimerspec));
            NESynchTypesIX::convTimeout(interval.it_value, msTimeout);
            if ( isPeriodic )
            {
                interval.it_interval.tv_sec = interval.it_value.tv_sec;
                interval.it_interval.tv_nsec= interval.it_value.tv_nsec;
            }

            mDueTime.tv_sec = interval.it_value.tv_sec;
            mDueTime.tv_nsec= interval.it_value.tv_nsec;
            mTimeout        = msTimeout;
            mIsSignaled     = false;
            mThreadId       = Thread::getCurrentThreadId();
            result          = true;
            if ( RETURNED_OK != timer_settime(mTimerId, 0, &interval, NULL) )
            {
                result = false;
                _resetTimer();
            }
        }
    }

    return result;
}

bool WaitableTimerIX::stopTimer(void)
{
    bool sendSignal = false;
    do 
    {
        ObjectLockIX lock(*this);

        sendSignal = (mIsSignaled == false);
        _stopTimer();
        mIsSignaled = true;

    } while (false);

    if (sendSignal)
    {
        SynchLockAndWaitIX::eventSignaled(*this);
    }

    return true;
}



bool WaitableTimerIX::cancelTimer(void)
{
    bool sendSignal = false;
    do 
    {
        ObjectLockIX lock(*this);

        sendSignal = (mIsSignaled == false);
        _resetTimer();
        mIsSignaled = true;

    } while (false);

    if (sendSignal)
    {
        SynchLockAndWaitIX::eventSignaled(*this);
    }

    return true;
}

bool WaitableTimerIX::checkSignaled(void) const
{
    ObjectLockIX lock(*this);
    return mIsSignaled;
}

bool WaitableTimerIX::isValid( void ) const
{
    ObjectLockIX lock(*this);
    return (mTimerId != static_cast<timer_t>(0));
}

bool WaitableTimerIX::notifyRequestOwnership(pthread_t /* ownerThread */ )
{
    return true;
}

bool WaitableTimerIX::checkCanSignalMultipleThreads(void) const
{
    return true;
}

void WaitableTimerIX::notifyReleasedThreads(int /* numThreads */)
{
    ObjectLockIX lock(*this);
    if (mResetInfo == NESynchTypesIX::EventResetAutomatic)
    {
        OUTPUT_DBG("Automatically resets waitable timer [ %s ] state to unsignaled.", getName());
        mIsSignaled = false;
    }
}

inline void WaitableTimerIX::_resetTimer( void )
{
    _stopTimer();
    if (mTimerId != static_cast<timer_t>(NULL))
    {
        timer_delete(mTimerId);
    }

    mTimerId    = static_cast<timer_t>(NULL);
    mThreadId   = 0;
}

inline void WaitableTimerIX::_stopTimer( void )
{
    if ((mTimerId != static_cast<timer_t>(NULL)) && (mTimeout != 0))
    {
        mDueTime.tv_sec = 0;
        mDueTime.tv_nsec= 0;
        itimerspec cancelSpec;
        NEMemory::zeroBuffer(static_cast<void *>(&cancelSpec), sizeof(itimerspec));
        timer_settime(mTimerId, 0, &cancelSpec, NULL);
    }

    mTimeout    = 0;
    mFiredCount = 0;
    mThreadId   = 0;
}

inline void WaitableTimerIX::_timerExpired(void)
{
    bool sendSignal = false;

    do 
    {
        ObjectLockIX lock(*this);
        
        if ( mTimerId != static_cast<timer_t>(0) )
        {
            ++ mFiredCount;
            NESynchTypesIX::convTimeout(mDueTime, mTimeout);
            
            mIsSignaled = true;
            sendSignal  = true;

            OUTPUT_DBG("Waitable timer [ %s ] has fired event [ %d ] times with timeout [ %d ] ms", getName(), mFiredCount, mTimeout);
        }
#ifdef DEBUG
        else
        {
            OUTPUT_WARN("The waitaible timer was previousely canceled, ignoring processing");
        }
#endif // DEBUG

    } while (false);

    if (sendSignal)
    {
        SynchLockAndWaitIX::eventSignaled(*this);

        SynchLockAndWaitIX * lockAndWait = SynchLockAndWaitIX::_mapWaitIdResource.findResourceObject(mThreadId);
        if ( lockAndWait != NULL )
        {
            lockAndWait->_notifyAsynchSignal( );
        }
    }
}

#endif  // !_POSIX
