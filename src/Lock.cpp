//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "HandleMan.h"
#include "Handle.h"

using namespace ThreadFramework;
// --------------------------------------------------
// Handle::Lock paradigm
// --------------------------------------------------

//----------------------------------------------------------------------------
// Observation by Andrew Trumbo - why not a HandleLock?
//    You are correct sir!  Great idea
// Further Jedi Points to Trumbo ...
//    Conversion operator
//    bool operator
//----------------------------------------------------------------------------

Handle::Lock::Lock(const Handle& h)
	: handle(h),
	status(Lock::Status::UNLOCKED)
{
	this->lock();
}

Handle::Lock::~Lock()
{
	// Do nothing
}

// boolean operator
Handle::Lock::operator bool() const
{
	return (this->status == Lock::Status::LOCKED);
}

void Handle::Lock::unlock()
{
	// Do nothing
}

void Handle::Lock::lock()
{
	if (this->status == Lock::Status::UNLOCKED)
	{
		Handle::Status h_status = Handle::IsValid(handle);
		if (h_status == Handle::Status::VALID_HANDLE)
		{
			this->status = Lock::Status::LOCKED;
		}
		else
		{
			this->status = Lock::Status::UNLOCKED;
		}
	}
	else
	{
		// already locked
	}
}


// conversion operator
Handle::Lock::operator Handle::Status() const
{
	Handle::Status h_status;

	if (this->status == Lock::Status::LOCKED)
	{
		h_status = Handle::Status::SUCCESS;
	}
	else
	{
		h_status = Handle::Status::HANDLE_ERROR;
	}
	return h_status;
}
