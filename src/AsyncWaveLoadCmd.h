//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ASYNC_WAVE_LOAD_COMMAND_H
#define ASYNC_WAVE_LOAD_COMMAND_H

#include "Command.h"
//#include "Wave.h"
#include "User_File_CB.h"

class AsyncWaveLoadCmd : public Command
{
public:
	// Big 4
	AsyncWaveLoadCmd() = delete;
	AsyncWaveLoadCmd(const AsyncWaveLoadCmd&) = delete;
	AsyncWaveLoadCmd& operator = (const AsyncWaveLoadCmd&) = delete;
	~AsyncWaveLoadCmd() = default;

	//Main call from Snd.cpp
	AsyncWaveLoadCmd(Wave::ID id, const char* const pWaveName, User_File_CB*);

	virtual void Execute() override;

public:
	// Data
	Wave::ID id;
	const char* const pWaveName;
	User_File_CB* pUserFileCB;
};

#endif

// --- End of File ---
