//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SND_CALLBACK_PLAY_NEXT_COMMAND_H
#define SND_CALLBACK_PLAY_NEXT_COMMAND_H

#include "Command.h"
#include "Wave.h"
#include "Voice.h"
#include "SndCallRegistry.h"

class SndCallback_PlayNextCmd : public Command
{

public:
	// Big 4
	SndCallback_PlayNextCmd() = delete;
	SndCallback_PlayNextCmd(const SndCallback_PlayNextCmd&) = delete;
	SndCallback_PlayNextCmd& operator = (const SndCallback_PlayNextCmd&) = delete;
	~SndCallback_PlayNextCmd() = default;

	SndCallback_PlayNextCmd(Snd*);

	virtual void Execute() override;

public:
	// Data
	Snd* pSnd;
};

#endif

// --- End of File ---
