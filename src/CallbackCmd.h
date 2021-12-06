//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CALLBACK_COMMAND_H
#define CALLBACK_COMMAND_H

#include "Command.h"
#include "SndCallRegistry.h"

class CallbackCmd : public Command
{

public:
	// Big 4
	CallbackCmd() = default;
	CallbackCmd(const CallbackCmd&) = default;
	CallbackCmd& operator = (const CallbackCmd&) = default;
	virtual ~CallbackCmd() = default;

	CallbackCmd(SndId);

	virtual void Execute() override;

public:
	// Data
	SndId thisID;

};

#endif

// --- End of File ---
