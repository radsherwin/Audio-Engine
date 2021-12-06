//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef HANDLE_MAN_H
#define HANDLE_MAN_H

#include "Handle.h"

class HandleMan
{
private:

	// constants
	static const unsigned int TABLE_SIZE = 512;
	static const unsigned int INVALID_STATE = 0x0;
	static const unsigned int STARTING_ID = 0xAAAA0000;

	// Nested class
	class HandleTableEntry
	{
	public:
		HandleTableEntry() = default;
		HandleTableEntry(const HandleTableEntry&) = delete;
		HandleTableEntry& operator = (const HandleTableEntry&) = delete;
		~HandleTableEntry() = default;

	public:
		std::atomic<unsigned int> id;
		std::mutex				  mtx;
	};


public:
	static void Create();
	static void Destroy();

	//-----------------------------------------------------
	// You cannot copy the singleton
	//-----------------------------------------------------
	HandleMan(const HandleMan&) = delete;
	const HandleMan& operator = (const HandleMan&) = delete;

	//-----------------------------------------------------
	// Being strategic on what is expose or not
	//-----------------------------------------------------

	// Test it
	static Handle::Status IsValid(const Handle& handle);

	// Nuke and Reset
	static Handle::Status InvalidateHandle(const Handle& handle);
	static Handle::Status ActivateHandle(Handle::ID& id, Handle::Index& index);

	//-----------------------------------------------------
	// Only for our DEBUG - remove for application
	//-----------------------------------------------------
	static void PrintTable();

private:
	HandleMan();
	~HandleMan();

	//-----------------------------------------------------
	// Keeping internals... private
	//-----------------------------------------------------
	static HandleMan* privInstance();
	static HandleMan* psInstance;
	Handle::ID privGetNewID();
	bool privFindNextAvailable(Handle::Index& index);
	Handle::Status privIsHandleAndRangeValid(const Handle& handle);

	//-----------------------------------------------------
	// Raw data
	//-----------------------------------------------------
	HandleTableEntry	table[TABLE_SIZE];
	Handle::ID			srcID;

};

#endif

// ---  End of File ---------------
