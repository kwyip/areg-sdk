/************************************************************************
 * This file is part of the AREG SDK core engine.
 * AREG SDK is dual-licensed under Free open source (Apache version 2.0
 * License) and Commercial (with various pricing models) licenses, depending
 * on the nature of the project (commercial, research, academic or free).
 * You should have received a copy of the AREG SDK license description in LICENSE.txt.
 * If not, please contact to info[at]aregtech.com
 *
 * \copyright   (c) 2017-2021 Aregtech UG. All rights reserved.
 * \file        areg/base/private/win32/ESynchObjectsWin32.cpp
 * \ingroup     AREG SDK, Asynchronous Event Generator Software Development Kit 
 * \author      Artak Avetyan
 * \brief       AREG Platform, Synchronization objects. Windows specific methods
 *
 ************************************************************************/
#include "areg/base/SynchObjects.hpp"

#ifdef  _WINDOWS
#include "areg/base/NEMemory.hpp"
#include "areg/base/Thread.hpp"
#include "areg/base/private/win32/SpinLockWin32.hpp"
#include <windows.h>

//////////////////////////////////////////////////////////////////////////
// IESynchObject class implementation
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// IESynchObject class methods
//////////////////////////////////////////////////////////////////////////

void IESynchObject::_destroySynchObject( void )
{
    if (mSynchObject != nullptr)
    {
        CloseHandle( static_cast<HANDLE>(mSynchObject) );
    }

    mSynchObject = nullptr;
}

//////////////////////////////////////////////////////////////////////////
// Mutex class implementation
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Mutex class, Constructor / Destructor
//////////////////////////////////////////////////////////////////////////
Mutex::Mutex(bool lock /* = true */)
    : IEResourceLock( IESynchObject::eSyncObject::SoMutex )

    , mOwnerThreadId( 0 )
{
    static_assert(std::atomic<id_type>::is_always_lock_free);
    SYNCHANDLE synchObj = static_cast<SYNCHANDLE>(CreateMutex( nullptr, lock ? TRUE : FALSE, nullptr ));
    if (lock && (synchObj != nullptr))
    {
        mSynchObject = synchObj;
        _lockMutex(NECommon::WAIT_INFINITE);
    }
}

//////////////////////////////////////////////////////////////////////////
// Mutex class, Methods
//////////////////////////////////////////////////////////////////////////

bool Mutex::_lockMutex( unsigned int timeout )
{
    bool result = false;

    if ((mSynchObject != nullptr) && (WaitForSingleObject(static_cast<HANDLE>(mSynchObject), timeout) == WAIT_OBJECT_0))
    {
        mOwnerThreadId.store( Thread::getCurrentThreadId( ) );
        result = true;
    }

    return result;
}

bool Mutex::_unlockMutex( void )
{
    bool result = false;
    if ((mSynchObject != nullptr) && ReleaseMutex(static_cast<HANDLE>(mSynchObject)))
    {
        mOwnerThreadId.store( 0 );
        result = true;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////
// SynchEvent class implementation
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// SynchEvent class, Constructor / Destructor
//////////////////////////////////////////////////////////////////////////
SynchEvent::SynchEvent(bool lock /* = true */, bool autoReset /* = true */)
    : IESynchObject   (IESynchObject::eSyncObject::SoEvent)

    , mAutoReset        (autoReset)
{
    mSynchObject= static_cast<void *>(CreateEvent(nullptr, autoReset ? FALSE : TRUE, lock ? FALSE : TRUE, nullptr));
}

SynchEvent::~SynchEvent( void )
{
    _unlockEvent(mSynchObject);
}

//////////////////////////////////////////////////////////////////////////
// SynchEvent class, Methods
//////////////////////////////////////////////////////////////////////////

bool SynchEvent::_unlockEvent( void * eventHandle )
{
    HANDLE handle = static_cast<HANDLE>(eventHandle);
    ASSERT(handle == static_cast<HANDLE>(mSynchObject));
    return (handle != nullptr ? ::SetEvent(handle) != FALSE : false);
}

bool SynchEvent::lock(unsigned int timeout /* = NECommon::WAIT_INFINITE */)
{
    ASSERT(mSynchObject != nullptr);
    return ( WaitForSingleObject(static_cast<HANDLE>(mSynchObject), timeout) == WAIT_OBJECT_0 );
}

bool SynchEvent::setEvent( void )
{
    ASSERT(mSynchObject != nullptr);
    return (::SetEvent(static_cast<HANDLE>(mSynchObject)) != FALSE);
}

bool SynchEvent::resetEvent( void )
{
    ASSERT(mSynchObject != nullptr);
    return (::ResetEvent(static_cast<HANDLE>(mSynchObject)) != FALSE);
}

void SynchEvent::pulseEvent( void )
{
    ASSERT(mSynchObject != nullptr);
    ::PulseEvent(static_cast<HANDLE>(mSynchObject));
}

//////////////////////////////////////////////////////////////////////////
// Semaphore class implementation
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Semaphore class, Constructor / Destructor
//////////////////////////////////////////////////////////////////////////
Semaphore::Semaphore(int maxCount, int initCount /* = 0 */)
    : IEResourceLock(IESynchObject::eSyncObject::SoSemaphore)

    , mMaxCount     ( MACRO_MAX( maxCount, 1 ) )
    , mCurrCount    ( MACRO_IN_RANGE( initCount, 0, mMaxCount ) ? initCount : 0 )
{
    static_assert(std::atomic_long::is_always_lock_free);
    mSynchObject= static_cast<void *>(CreateSemaphore(nullptr, mCurrCount.load(), mMaxCount, nullptr));
}

Semaphore::~Semaphore( void )
{
}

//////////////////////////////////////////////////////////////////////////
// Semaphore class, Methods
//////////////////////////////////////////////////////////////////////////
bool Semaphore::lock(unsigned int timeout /* = NECommon::WAIT_INFINITE */)
{
    ASSERT(mSynchObject != nullptr);
    bool result = false;
    if (WaitForSingleObject(static_cast<HANDLE>(mSynchObject), timeout) == WAIT_OBJECT_0)
    {
        mCurrCount.fetch_sub(1);
        result = true;
    }

    return result;
}

bool Semaphore::unlock( void )
{
    ASSERT(mSynchObject != nullptr);
    bool result = false;
    if (ReleaseSemaphore(static_cast<HANDLE>(mSynchObject), 1, nullptr) == TRUE)
    {
        mCurrCount.fetch_add( 1 );
        result = true;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////
// CriticalSection implementation
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// CriticalSection class, Constructor / Destructor
//////////////////////////////////////////////////////////////////////////
CriticalSection::CriticalSection( void )
    : IEResourceLock(IESynchObject::eSyncObject::SoCritical)
{
    ASSERT(mSynchObject == nullptr);
    mSynchObject = static_cast<void *>( DEBUG_NEW unsigned char [sizeof(CRITICAL_SECTION)] );
    if (mSynchObject != nullptr)
    {
        NEMemory::constructElems<CRITICAL_SECTION>(mSynchObject, 1);
        InitializeCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(mSynchObject));
    }
}

CriticalSection::~CriticalSection( void )
{
    if (mSynchObject != nullptr)
    {
        DeleteCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(mSynchObject));
        delete [] reinterpret_cast<unsigned char *>(mSynchObject);
    }

    mSynchObject = nullptr;
}

//////////////////////////////////////////////////////////////////////////
// CriticalSection class, Methods
//////////////////////////////////////////////////////////////////////////
bool CriticalSection::lock(unsigned int  /*timeout = NECommon::WAIT_INFINITE */)
{
    if (mSynchObject != nullptr)
    {
        EnterCriticalSection( reinterpret_cast<LPCRITICAL_SECTION>(mSynchObject) );
    }

    return (mSynchObject != nullptr);
}

bool CriticalSection::unlock( void )
{
    if (mSynchObject != nullptr)
    {
        LeaveCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(mSynchObject));
    }

    return (mSynchObject != nullptr);
}

bool CriticalSection::tryLock( void )
{
    return ( (mSynchObject != nullptr) && (TryEnterCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(mSynchObject)) == TRUE) );
}

//////////////////////////////////////////////////////////////////////////
// SpinLock class implementation
//////////////////////////////////////////////////////////////////////////

SpinLock::SpinLock( void )
    : IEResourceLock( IESynchObject::eSyncObject::SoSpinlock )
{
#if defined (__cplusplus) && (__cplusplus > 201703L)
    mSynchObject    = DEBUG_NEW SpinLockWin32( );
#else // defined (__cplusplus) && (__cplusplus > 201703L)
    mSynchObject    = DEBUG_NEW CriticalSection( );
#endif // defined (__cplusplus) && (__cplusplus > 201703L)
}

SpinLock::~SpinLock( void )
{
    if ( mSynchObject != nullptr )
    {
#if defined (__cplusplus) && (__cplusplus > 201703L)
        delete reinterpret_cast<SpinLockWin32 *>(mSynchObject);
#else // defined (__cplusplus) && (__cplusplus > 201703L)
        delete reinterpret_cast<CriticalSection *>(mSynchObject);
#endif // defined (__cplusplus) && (__cplusplus > 201703L)
        mSynchObject = nullptr;
    }
}

bool SpinLock::lock( unsigned int /*timeout = NECommon::WAIT_INFINITE*/ )
{
#if defined (__cplusplus) && (__cplusplus > 201703L)
    return (mSynchObject != nullptr ? reinterpret_cast<SpinLockWin32 *>(mSynchObject)->lock( ) : false);
#else // defined (__cplusplus) && (__cplusplus > 201703L)
    return (mSynchObject != nullptr ? reinterpret_cast<CriticalSection *>(mSynchObject)->lock( ) : false);
#endif // defined (__cplusplus) && (__cplusplus > 201703L)
}

bool SpinLock::unlock( void )
{
#if defined (__cplusplus) && (__cplusplus > 201703L)
    return (mSynchObject != nullptr ? reinterpret_cast<SpinLockWin32 *>(mSynchObject)->unlock( ) : false);
#else // defined (__cplusplus) && (__cplusplus > 201703L)
    return (mSynchObject != nullptr ? reinterpret_cast<CriticalSection *>(mSynchObject)->unlock( ) : false);
#endif // defined (__cplusplus) && (__cplusplus > 201703L)
}

bool SpinLock::tryLock( void )
{
#if defined (__cplusplus) && (__cplusplus > 201703L)
    return (mSynchObject != nullptr ? reinterpret_cast<SpinLockWin32 *>(mSynchObject)->tryLock( ) : false);
#else // defined (__cplusplus) && (__cplusplus > 201703L)
    return (mSynchObject != nullptr ? reinterpret_cast<CriticalSection *>(mSynchObject)->tryLock( ) : false);
#endif // defined (__cplusplus) && (__cplusplus > 201703L)
}

//////////////////////////////////////////////////////////////////////////
// ResourceLock class implementation
//////////////////////////////////////////////////////////////////////////

ResourceLock::ResourceLock( bool initLock /*= false*/ )
    : IEResourceLock(IESynchObject::eSyncObject::SoReslock)
{

#if 0
    mSynchObject    = new Mutex(initLock);

#else

    mSynchObject    = new CriticalSection();
    if ( initLock && (mSynchObject != nullptr) )
    {
        reinterpret_cast<IEResourceLock *>(mSynchObject)->lock(NECommon::WAIT_INFINITE);
    }

#endif

}

ResourceLock::~ResourceLock(void)
{
    if (mSynchObject != nullptr)
    {
        reinterpret_cast<IEResourceLock *>(mSynchObject)->unlock();
        delete reinterpret_cast<IEResourceLock *>(mSynchObject);
        mSynchObject = nullptr;
    }
}

bool ResourceLock::lock(unsigned int timeout /*= NECommon::WAIT_INFINITE */)
{
    return( (mSynchObject != nullptr) && reinterpret_cast<IEResourceLock *>(mSynchObject)->lock(timeout) );
}

bool ResourceLock::unlock(void)
{
    return ( (mSynchObject != nullptr) && reinterpret_cast<IEResourceLock *>(mSynchObject)->unlock() );
}

bool ResourceLock::tryLock(void)
{
    return ( (mSynchObject != nullptr) && reinterpret_cast<IEResourceLock *>(mSynchObject)->tryLock() );
}

//////////////////////////////////////////////////////////////////////////
// SynchTimer implementation
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// SynchTimer class, Constructor / Destructor
//////////////////////////////////////////////////////////////////////////
SynchTimer::SynchTimer( unsigned int timeMilliseconds, bool periodic /* = false */, bool autoReset /* = true */, bool initSignaled /* = true */ )
    : IESynchObject   ( IESynchObject::eSyncObject::SoTimer )

    , mTimeMilliseconds ( timeMilliseconds )
    , mIsPeriodic       ( periodic )
    , mIsAutoReset      ( autoReset )
{
    mSynchObject= static_cast<SYNCHANDLE>(CreateWaitableTimer( nullptr, autoReset ? FALSE : TRUE, nullptr ));
    if ( initSignaled == false )
    {
        setTimer( );
    }
}

SynchTimer::~SynchTimer( void )
{
    if ( mSynchObject != nullptr )
    {
        CancelWaitableTimer( static_cast<HANDLE>(mSynchObject) );
        CloseHandle( static_cast<HANDLE>(mSynchObject) );
    }

    mSynchObject = nullptr;
}

//////////////////////////////////////////////////////////////////////////
// SynchTimer class, Methods
//////////////////////////////////////////////////////////////////////////
bool SynchTimer::lock( unsigned int timeout /* = NECommon::WAIT_INFINITE */ )
{
    return (WaitForSingleObject( static_cast<HANDLE>(mSynchObject), timeout ) == WAIT_OBJECT_0);
}

bool SynchTimer::unlock( void )
{
    return (CancelWaitableTimer( static_cast<HANDLE>(mSynchObject) ) != FALSE);
}

bool SynchTimer::setTimer( void )
{
    constexpr unsigned int   NANOSECONDS_KOEF_100    = 10'000u;

    LARGE_INTEGER dueTime;
    dueTime.QuadPart = static_cast<int64_t>(-1) * static_cast<int64_t>(mTimeMilliseconds) * static_cast<int64_t>(NANOSECONDS_KOEF_100);
    LONG lPeriod = mIsPeriodic ? static_cast<LONG>(mTimeMilliseconds) : 0;
    return (SetWaitableTimer( static_cast<HANDLE>(mSynchObject), &dueTime, lPeriod, nullptr, nullptr, FALSE ) != FALSE);
}

bool SynchTimer::cancelTimer( void )
{
    return (CancelWaitableTimer( static_cast<HANDLE>(mSynchObject) ) != FALSE);
}

//////////////////////////////////////////////////////////////////////////
// MultiLock class implementation
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// MultiLock class, Methods
//////////////////////////////////////////////////////////////////////////
int MultiLock::lock(unsigned int timeout /* = NECommon::WAIT_INFINITE */, bool waitForAll /* = false */, bool isAlertable /*= false*/)
{
    void * syncHandles[NECommon::MAXIMUM_WAITING_OBJECTS];
    for ( int i = 0; i < mSizeCount; ++ i)
    {
        syncHandles[i] = mSyncObjArray[i]->getHandle( );
    }

    int index = MultiLock::LOCK_INDEX_INVALID;
    unsigned int maxEvent= static_cast<unsigned int>(WAIT_OBJECT_0 + mSizeCount);
    unsigned int result  = mSizeCount > 0 ? WaitForMultipleObjectsEx(static_cast<unsigned int>(mSizeCount), static_cast<HANDLE *>(syncHandles), waitForAll ? TRUE : FALSE, timeout, isAlertable ? TRUE : FALSE) : WAIT_FAILED;
    if (result < maxEvent)
    {
        if (waitForAll == false)
        {
            index = static_cast<int>(result - WAIT_OBJECT_0);
            ASSERT((index >= 0) && index < mSizeCount);
            mLockedStates[index] = MultiLock::eLockedState::StateLocked;
        }
        else
        {
            for (int i = 0; i < mSizeCount; ++ i)
            {
                mLockedStates[i] = MultiLock::eLockedState::StateLocked;
            }

            index = MultiLock::LOCK_INDEX_ALL;
        }
    }
    else if (result == WAIT_IO_COMPLETION)
    {
        index = MultiLock::LOCK_INDEX_COMPLETION;
    }
    else if (result == WAIT_TIMEOUT)
    {
        index = MultiLock::LOCK_INDEX_TIMEOUT;
    }

    return index;
}

#endif  // _WINDOWS
