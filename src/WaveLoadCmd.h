//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef WAVE_LOAD_COMMAND_H
#define WAVE_LOAD_COMMAND_H

#include "Command.h"
#include "Wave.h"
#include "I_File_CB.h"

class WaveLoadCmd : public Command
{
public:
	// Big 4
	WaveLoadCmd() = delete;
	WaveLoadCmd(const WaveLoadCmd&) = delete;
	WaveLoadCmd& operator = (const WaveLoadCmd&) = delete;
	~WaveLoadCmd() = default;

	//Main call from Snd.cpp
	WaveLoadCmd(Wave::ID id, const char* const pWaveName, I_File_CB*);

	virtual void Execute() override;

public:
	// Data
	Wave::ID id;
	const char* const pWaveName;
	I_File_CB* pIFileCB;
};

#endif

// --- End of File ---
