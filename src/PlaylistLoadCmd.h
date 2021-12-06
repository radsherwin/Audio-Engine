//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Playlist_LOAD_COMMAND_H
#define Playlist_LOAD_COMMAND_H

#include "Command.h"
#include "Snd.h"
#include "Wave.h"
#include "User_File_CB.h"


class PlaylistLoadCmd : public Command
{

public:
	// Big 4
	PlaylistLoadCmd() = delete;
	PlaylistLoadCmd(const PlaylistLoadCmd&) = delete;
	PlaylistLoadCmd& operator = (const PlaylistLoadCmd&) = delete;
	~PlaylistLoadCmd() = default;

	PlaylistLoadCmd(SndId, Wave::ID, User_File_CB* = nullptr);

	virtual void Execute() override;

public:
	// Data
	SndId sndID;
	Wave::ID waveID;
	User_File_CB* pUserCB;
};

#endif

// --- End of File ---
