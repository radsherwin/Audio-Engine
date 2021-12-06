//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PLAYLIST_STITCH_COMMAND_H
#define PLAYLIST_STITCH_COMMAND_H

#include "Command.h"
#include "Snd.h"
#include "Wave.h"


class PlaylistStitchCmd : public Command
{

public:
	// Big 4
	PlaylistStitchCmd() = delete;
	PlaylistStitchCmd(const PlaylistStitchCmd&) = delete;
	PlaylistStitchCmd& operator = (const PlaylistStitchCmd&) = delete;
	~PlaylistStitchCmd() = default;

	PlaylistStitchCmd(SndId, Wave::ID);

	virtual void Execute() override;

public:
	// Data
	SndId sndID;
	Wave::ID waveID;
};

#endif

// --- End of File ---
