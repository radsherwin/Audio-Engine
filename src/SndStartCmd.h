//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SND_START_COMMAND_H
#define SND_START_COMMAND_H

#include "Command.h"
#include "Wave.h"
#include "Voice.h"
#include "SndCallRegistry.h"

class SndStartCmd : public Command
{

public:
	// Big 4
	SndStartCmd() = delete;
	SndStartCmd(const SndStartCmd&) = delete;
	SndStartCmd& operator = (const SndStartCmd&) = delete;
	~SndStartCmd() = default;

	SndStartCmd(Snd*);

	virtual void Execute() override;

public:
	// Data
	Snd* pSnd;
};

#endif

// --- End of File ---
