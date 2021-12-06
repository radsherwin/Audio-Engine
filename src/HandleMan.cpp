//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "HandleMan.h"

using namespace ThreadFramework;

HandleMan* HandleMan::psInstance = nullptr;

// --------------------------------------------------------------------
//   No Mutex protection
// --------------------------------------------------------------------

void HandleMan::Create()
{
	assert(HandleMan::psInstance == nullptr);
	HandleMan::psInstance = new HandleMan();
	assert(HandleMan::psInstance);
}

void HandleMan::Destroy()
{
	assert(HandleMan::psInstance);

	delete HandleMan::psInstance;
	HandleMan::psInstance = nullptr;
}

HandleMan::HandleMan()
{
	this->srcID = STARTING_ID;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		this->table[i].id.store(INVALID_STATE);
	}
}

HandleMan::~HandleMan()
{
	//	Debug::out("~HandleMan()\n");
		// safety - nuke it again
	this->srcID = STARTING_ID;

	//this->PrintTable();
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		this->table[i].id.store(INVALID_STATE);
	}
}

Handle::ID HandleMan::privGetNewID()
{
	// Increment
	this->srcID++;

	return this->srcID;
}

// --------------------------------------------------------------------
//   No Mutex protection
// --------------------------------------------------------------------

Handle::Status HandleMan::InvalidateHandle(const Handle& handle)
{
	HandleMan* pMan = HandleMan::privInstance();
	assert(pMan);

	// Is Range and ID valid?
	Handle::Status status = pMan->privIsHandleAndRangeValid(handle);

	if (status == Handle::Status::VALID_HANDLE)
	{
		// Protect access to resource: acquire
		bool lockStatus = pMan->table[handle.GetIndex()].mtx.try_lock();

		// ---------------------------------------------------------------------
		// Race condition:
		// What happens if the ID is invalidated between the test and the lock?
		// ---------------------------------------------------------------------

		if (lockStatus)
		{
			// Is ID valid?
			status = pMan->privIsHandleAndRangeValid(handle);

			if (status == Handle::Status::VALID_HANDLE)
			{
				// nuke it
				pMan->table[handle.GetIndex()].id.store(INVALID_STATE);

				// release the mtx
				pMan->table[handle.GetIndex()].mtx.unlock();

				status = Handle::Status::INVALID_HANDLE;
			}
			else
			{
				// race condition... handle is invalid - status is ERROR

				// release the mtx
				pMan->table[handle.GetIndex()].mtx.unlock();
			}
		}
		else
		{
			// Do nothing since mtx was never aquired
			// Fall through - error
			status = Handle::Status::HANDLE_ERROR;
		}
	}
	else
	{
		// fall through - status is error
	}

	return status;
}

Handle::Status HandleMan::IsValid(const Handle& handle)
{
	HandleMan* pMan = HandleMan::privInstance();
	assert(pMan);

	// is it valid?
	Handle::Status status = pMan->privIsHandleAndRangeValid(handle);

	return status;
}

Handle::Status HandleMan::ActivateHandle(Handle::ID& new_id, Handle::Index& index)
{
	HandleMan* pMan = HandleMan::privInstance();
	assert(pMan);

	Handle::Status 	status = Handle::Status::HANDLE_ERROR;

	if (pMan->privFindNextAvailable(index))
	{
		// Protect access to resource: acquire
		bool lockStatus = pMan->table[index].mtx.try_lock();

		// ---------------------------------------------------------------------
		// Race condition:
		// What happens if the ID is invalidated between the test and the lock?
		// ---------------------------------------------------------------------
		if (pMan->table[index].id.load() != INVALID_STATE)
		{
			if (lockStatus)
			{
				// unlock
				pMan->table[index].mtx.unlock();
				lockStatus = false;
				// bail and fall through
			}
		}

		if (lockStatus)
		{
			status = Handle::Status::SUCCESS;

			// Set it - atomic!
			new_id = pMan->privGetNewID();
			pMan->table[index].id.store(new_id);

			// unlock
			pMan->table[index].mtx.unlock();

			status = Handle::Status::VALID_HANDLE;
		}
		else
		{
			// Do nothing since mtx was never aquired
			// fall through - error

			status = Handle::Status::HANDLE_ERROR;
		}
	}
	else
	{
		status = Handle::Status::INSUFFIENT_SPACE;
		Debug::out("Index space used: %d\n", index);
		// trap for Debug
		assert(status == Handle::Status::SUCCESS);
	}

	return status;
}

// --------------------------------------------------------------------
//   No Mutex protection
// --------------------------------------------------------------------

bool HandleMan::privFindNextAvailable(Handle::Index& index)
{
	bool status = false;

	for (Handle::Index i = 0; i < TABLE_SIZE; i++)
	{
		if (this->table[i].id.load() == INVALID_STATE)
		{
			// found one
			index = i;
			status = true;
			break;
		}
	}

	return status;
}


Handle::Status HandleMan::privIsHandleAndRangeValid(const Handle& handle)
{
	Handle::Status status = Handle::Status::HANDLE_ERROR;

	if (handle.GetIndex() < TABLE_SIZE)
	{
		if (this->table[handle.GetIndex()].id.load() == handle.GetID())
		{
			status = Handle::Status::VALID_HANDLE;
		}
		else
		{
			status = Handle::Status::INVALID_HANDLE;
		}
	}
	else
	{
		status = Handle::Status::HANDLE_ERROR;
	}

	return status;
}

HandleMan* HandleMan::privInstance()
{
	HandleMan* pInstance = nullptr;

	// Here's the singleton
	if (HandleMan::psInstance)
	{
		pInstance = HandleMan::psInstance;
	}
	else
	{
		assert(false);
	}

	return pInstance;
}

void HandleMan::PrintTable()
{
	HandleMan* pMan = HandleMan::privInstance();
	assert(pMan);

	Trace::out("\n");

	// No protection.... Just printing
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (pMan->table[i].id == INVALID_STATE)
		{
			Trace::out("[%d]: %s \n", i, STRING_ME(INVALID_STATE));
		}
		else
		{
			Trace::out("[%d]: %x \n", i, pMan->table[i].id.load());
		}
	}

	Trace::out("\n");
}

// ---  End of File ---------------
