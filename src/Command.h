//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef COMMAND_H
#define COMMAND_H

#include "Handle.h"

class Command
{
public:
	enum Type
	{
		CreateWave,
		PlaySnd,
		StopSnd,
		AdjustVolumeSnd,
		PanSnd,
		Uninitialized
	};

public:
	// Big 4
	Command() = default;
	Command(const Command&) = default;
	Command& operator = (const Command&) = default;
	virtual ~Command() = default;

	virtual void Execute() = 0;

public:
	// Data

	Handle handle;
};

#endif

// --- End of File ---
