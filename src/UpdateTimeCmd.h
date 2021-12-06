//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef UPDATE_TIME_COMMAND_H
#define UPDATE_TIME_COMMAND_H

#include "Command.h"
#include "SndCallRegistry.h"
#include "Audio.h"
#include "Wave.h"

class UpdateTimeCmd : public Command
{

public:
	// Big 4
	UpdateTimeCmd();
	UpdateTimeCmd(const UpdateTimeCmd&) = default;
	UpdateTimeCmd& operator = (const UpdateTimeCmd&) = default;
	virtual ~UpdateTimeCmd() = default;

	virtual void Execute() override;

public:
	// Data

};

#endif

// --- End of File ---
