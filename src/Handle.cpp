//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "HandleMan.h"
#include "Handle.h"

using namespace ThreadFramework;

// --------------------------------------------------
// Handle
// --------------------------------------------------

Handle::Handle()
{
	//Activate
	Status status = Handle::ActivateHandle(*this);
	assert(status == Handle::Status::VALID_HANDLE);

}

Handle::Status Handle::ActivateHandle(Handle& handle)
{
	//Activate
	Status status = HandleMan::ActivateHandle(handle.id, handle.index);
	assert(status == Handle::Status::VALID_HANDLE);

	//Trace::out("activate id: %x \n", handle.id);
	return status;
}

Handle::~Handle()
{
	//Debug::out("~Handle()\n");

	// Invalidate handle;
	HandleMan::InvalidateHandle(*this);

}

Handle::ID Handle::GetID() const
{
	return this->id;
}

Handle::Index Handle::GetIndex() const
{
	return this->index;
}


//---------------------------------------------------------------
// Tunneling... I only want handle.h to be used
//---------------------------------------------------------------
Handle::Status Handle::IsValid(const Handle& handle)
{
	return HandleMan::IsValid(handle);
}

Handle::Status Handle::InvalidateHandle(const Handle& handle)
{
	return HandleMan::InvalidateHandle(handle);
}

// ---  End of File ---------------
