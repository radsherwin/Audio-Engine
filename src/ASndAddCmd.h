//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ASND_ADD_COMMAND_H
#define ASND_ADD_COMMAND_H

#include "Command.h"
#include "Snd.h"
#include "Wave.h"

class ASndAddCmd : public Command
{
public:
	// Big 4
	ASndAddCmd() = delete;
	ASndAddCmd(const ASndAddCmd&) = delete;
	ASndAddCmd& operator = (const ASndAddCmd&) = delete;
	~ASndAddCmd() = default;

	//Main call from Snd.cpp
	ASndAddCmd(Snd*, SndId);

	virtual void Execute() override;

public:
	// Data
	Snd* snd;
	SndId sndID;
};

#endif

// --- End of File ---
