#ifndef AREG_BASE_PRIVATE_POSIX_CRITICALSECTIONIX_HPP
#define AREG_BASE_PRIVATE_POSIX_CRITICALSECTIONIX_HPP
/************************************************************************
 * \file        areg/base/private/posix/CriticalSectionIX.hpp
 * \ingroup     AREG SDK, Asynchronous Event Generator Software Development Kit
 * \author      Artak Avetyan (mailto:artak@aregtech.com)
 * \brief       AREG Platform, POSIX Spin Lock wrapper class.
 *
 ************************************************************************/

 /************************************************************************
  * Includes
  ************************************************************************/
#include "areg/base/GEGlobal.h"

#ifdef  _POSIX
#include "areg/base/private/posix/IESynchObjectBaseIX.hpp"
#include <pthread.h>

//////////////////////////////////////////////////////////////////////////
// CriticalSectionIX class declaration.
//////////////////////////////////////////////////////////////////////////
/**
 * \brief   POSIX Critical Section is a wrapper of POSIX spin lock, since
 *          it is specified as the  fastest locking / synchronization object.
 *          The Critical Section can be used only for the communication between threads.
 *          The Critical Section can be owned only by one thread at a time.
 **/
class CriticalSectionIX   : protected IESynchObjectBaseIX
{
	/**
	 * \brief	Describes the Critical Section structure, which has a simple
	 * 			recursive spin-lock object thread locking mechanism
	 */
	typedef struct S_CSection
	{
		pthread_spinlock_t  spinLock;		//!< The POSIX spin lock to synchronize multithreading access of critical section.
		pthread_spinlock_t  internLock;		//!< The POSIX spin lock to synchronize internal sructure resources.
		pthread_t			spinOwner;		//!< The spin-lock owner POSIX thread
		int 				lockCounter;	//!< The lock counter to release spin lock when counter reaches zero.
	} sSection;

//////////////////////////////////////////////////////////////////////////
// Constructor / Destructor.
//////////////////////////////////////////////////////////////////////////
public:

    /**
     * \brief   Creates Critical Section object and initializes POSIX spin lock.
     * \param   initLock    If true, the critical section (spin lock) is initially locked.
     **/
    CriticalSectionIX( bool initLock = false );

    /**
     * \brief   Destroy the object, free resources.
     **/
    virtual ~CriticalSectionIX( void );

//////////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////////
public:

    /**
     * \brief   Locks the critical section and prevents other threads to
     *          access shared data until the locking thread does not release
     *          the critical section.
     * \return  Returns true if operation succeeded.
     **/
    bool lock( void ) const;

    /**
     * \brief   Unlocks critical section so that, one of waiting threads is released
     *          to own critical section.
     **/
    void unlock( void ) const;

    /**
     * \brief   Tests whether the critical section can be locked or not.
     *          It is locked if returned value is 'true'.
     * \return  Returns true if calling thread have got the ownership.
     *          Returns false if calling thread could not get the ownership.
     **/
    bool tryLock( void ) const;

protected:
/************************************************************************/
// IESynchObjectBaseIX overrides.
/************************************************************************/
    
    /**
     * \brief   Returns true if synchronization object is valid.
     **/
    virtual bool isValid( void ) const;

    /**
     * \brief   Triggered when synchronization object is going to be deleted.
     *          This should free all resources.
     **/
    virtual void freeResources( void );

//////////////////////////////////////////////////////////////////////////
// Hidden calls
//////////////////////////////////////////////////////////////////////////
private:
    /**
     * \brief	Takes the ownership of critical section spin lock.
     * \return	Returns true if operation succeeded.
     */
    inline bool lockSpin( void ) const;
    /**
     * \brief	Releases the ownership of critical section spin lock.
     */
    inline void unlockSpin( void ) const;
    /**
     * \brief	Takes the ownership of spin lock to access resources of critical section.
     */
    inline void lockIntern( void ) const;
    /**
     * \brief	Releases the ownership of spin lock to access resources of critical section.
     */
    inline void unlockIntern( void ) const;

//////////////////////////////////////////////////////////////////////////
// Member variables
//////////////////////////////////////////////////////////////////////////
private:
    /**
     * \brief   The Critical Section object, which has implementation of recursive spin lock.
     **/
    mutable sSection	mSpin;
    /**
     * \brief   The spin lock validity flag.
     **/
    mutable bool        mSpinValid;

//////////////////////////////////////////////////////////////////////////
// Forbidden calls
//////////////////////////////////////////////////////////////////////////
private:
    CriticalSectionIX( const CriticalSectionIX & /*src*/ );
    const CriticalSectionIX & operator = ( const CriticalSectionIX & /*src*/ );
};

//////////////////////////////////////////////////////////////////////////
// SpinLockIX class declaration.
//////////////////////////////////////////////////////////////////////////
/**
 * \brief   POSIX spin-lock wrapper with the basic functionalities to lock and unlock.
 *          Instead of calling global methods, it receives instance of CriticalSectionIX
 *          to call lock / unlock.
 **/
class SpinLockIX
{
//////////////////////////////////////////////////////////////////////////
// Constructor / Destructor.
//////////////////////////////////////////////////////////////////////////
public:
    /**
     * \brief   Sets the instance of CriticalSectionIX object, which is the 
     *          real POSIX spin-lock wrapper class.
     **/
    SpinLockIX( CriticalSectionIX & lock );

    /**
     * \brief   Destructor.
     **/
    ~SpinLockIX( void );

//////////////////////////////////////////////////////////////////////////
// Operations.
//////////////////////////////////////////////////////////////////////////

    /**
     * \brief   The calling thread acquires the ownership of the spin-lock. So that, while the thread
     *          holds the ownership, any other thread trying to acquire spin-lock will be blocked
     *          and hold until the spin-lock is released.
     * \return  Returns true if succeeded to lock.
     **/
    inline bool lock( void ) const;

    /**
     * \brief   Whether the spin-lock is owned by thread or not, this function returns immediately.
     *          If returned true, the spin-lock is owned by calling thread. Otherwise, the spin-lock
     *          is already owned by another thread.
     * \return  Returns true if spin-lock is owned by calling thread.
     *          Returns false, if spin-lock is owned by another thread.
     **/
    inline bool tryLock( void ) const;

    /**
     * \brief   Release and unlock the spin-lock. So that, let's other waiting thread to acquire lock
     *          and take the ownership.
     **/
    inline void unlock( void ) const;

//////////////////////////////////////////////////////////////////////////
// Member variables.
//////////////////////////////////////////////////////////////////////////
private:
    /**
     * \brief   Instance of POSIX spin-lock wrapper object.
     **/
    CriticalSectionIX & mLocker;

//////////////////////////////////////////////////////////////////////////
// Forbidden calls.
//////////////////////////////////////////////////////////////////////////
private:
    SpinLockIX( void );
    SpinLockIX( const SpinLockIX & /*src*/ );
    const SpinLockIX & operator = ( const SpinLockIX & /*src*/ );
};
//////////////////////////////////////////////////////////////////////////
// CriticalSectionIX inline methods.
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// SpinLockIX inline methods.
//////////////////////////////////////////////////////////////////////////

inline bool SpinLockIX::lock(void) const
{
    return mLocker.lock();
}

inline bool SpinLockIX::tryLock(void) const
{
    return mLocker.tryLock();
}

inline void SpinLockIX::unlock(void) const
{
    mLocker.unlock();
}

#endif  // _POSIX

#endif  // AREG_BASE_PRIVATE_POSIX_CRITICALSECTIONIX_HPP