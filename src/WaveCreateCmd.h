//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef WAVE_CREATE_COMMAND_H
#define WAVE_CREATE_COMMAND_H

#include "Command.h"
#include "Wave.h"

class WaveCreateCmd : public Command
{
public:
	// Big 4
	WaveCreateCmd() = delete;
	WaveCreateCmd(const WaveCreateCmd&) = delete;
	WaveCreateCmd& operator = (const WaveCreateCmd&) = delete;
	~WaveCreateCmd() = default;

	//Main call from Snd.cpp
	WaveCreateCmd(Wave::ID id, const char* const pWaveName);

	virtual void Execute() override;

public:
	// Data
	Wave::ID id;
	const char* const pWaveName;
};

#endif

// --- End of File ---
