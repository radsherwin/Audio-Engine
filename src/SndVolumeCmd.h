//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SND_VOLUME_COMMAND_H
#define SND_VOLUME_COMMAND_H

#include "Command.h"
#include "Wave.h"
#include "Voice.h"
#include "SndCallRegistry.h"

class SndVolumeCmd : public Command
{

public:
	// Big 4
	SndVolumeCmd() = delete;
	SndVolumeCmd(const SndVolumeCmd&) = delete;
	SndVolumeCmd& operator = (const SndVolumeCmd&) = delete;
	~SndVolumeCmd() = default;

	SndVolumeCmd(Snd*, float);

	virtual void Execute() override;

public:
	// Data
	Snd* pSnd;
	float amt;
};

#endif

// --- End of File ---
