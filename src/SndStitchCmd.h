//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SND_STITCH_COMMAND_H
#define SND_STITCH_COMMAND_H

#include "Command.h"
#include "Wave.h"
#include "Voice.h"
#include "SndCallRegistry.h"

class SndStitchCmd : public Command
{

public:
	// Big 4
	SndStitchCmd() = delete;
	SndStitchCmd(const SndStitchCmd&) = delete;
	SndStitchCmd& operator = (const SndStitchCmd&) = delete;
	~SndStitchCmd() = default;

	SndStitchCmd(Snd*, Snd*);

	virtual void Execute() override;

public:
	// Data
	Snd* pSnd;
	Snd* pNextSound;
};

#endif

// --- End of File ---
