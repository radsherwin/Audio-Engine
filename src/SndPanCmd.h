//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SND_PAN_COMMAND_H
#define SND_PAN_COMMAND_H

#include "Command.h"
#include "Snd.h"
#include "SndCallRegistry.h"

class SndPanCmd : public Command
{

public:
	// Big 4
	SndPanCmd() = delete;
	SndPanCmd(const SndPanCmd&) = delete;
	SndPanCmd& operator = (const SndPanCmd&) = delete;
	~SndPanCmd() = default;

	SndPanCmd(Snd*, float);

	virtual void Execute() override;

public:
	// Data
	Snd* pSnd;
	float amt;
};

#endif

// --- End of File ---
