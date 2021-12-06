//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef VOICE_CALLBACK_PLAY_NEXT_COMMAND_H
#define VOICE_CALLBACK_PLAY_NEXT_COMMAND_H

#include "Command.h"
#include "SndCallRegistry.h"

class VoiceCallback_PlayNextCmd : public Command
{

public:
	// Big 4
	VoiceCallback_PlayNextCmd() = default;
	VoiceCallback_PlayNextCmd(const VoiceCallback_PlayNextCmd&) = default;
	VoiceCallback_PlayNextCmd& operator = (const VoiceCallback_PlayNextCmd&) = default;
	virtual ~VoiceCallback_PlayNextCmd() = default;

	VoiceCallback_PlayNextCmd(SndId);

	virtual void Execute() override;

public:
	// Data
	SndId thisID;

};

#endif

// --- End of File ---
