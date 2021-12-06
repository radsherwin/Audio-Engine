//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PRIORITY_TABLE_REMOVE_COMMAND_H
#define PRIORITY_TABLE_REMOVE_COMMAND_H

#include "Command.h"
#include "Snd.h"


class PriorityTableRemoveCmd : public Command
{

public:
	// Big 4
	PriorityTableRemoveCmd() = delete;
	PriorityTableRemoveCmd(const PriorityTableRemoveCmd&) = delete;
	PriorityTableRemoveCmd& operator = (const PriorityTableRemoveCmd&) = delete;
	~PriorityTableRemoveCmd() = default;

	PriorityTableRemoveCmd(SndId);

	virtual void Execute() override;

public:
	// Data
	SndId sndID;
};

#endif

// --- End of File ---
