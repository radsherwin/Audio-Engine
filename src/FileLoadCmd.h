//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef FILE_LOAD_COMMAND_H
#define FILE_LOAD_COMMAND_H

#include "Command.h"
#include "Wave.h"

class FileLoadCmd : public Command
{
public:
	// Big 4
	FileLoadCmd() = delete;
	FileLoadCmd(const FileLoadCmd&) = delete;
	FileLoadCmd& operator = (const FileLoadCmd&) = delete;
	~FileLoadCmd() = default;

	//Main call from Snd.cpp
	FileLoadCmd(Wave::ID id, const char* const pWaveName, Wave*);

	virtual void Execute() override;

public:
	// Data
	Wave::ID waveID;
	const char* const pWaveName;
	Wave* pWave;
};

#endif

// --- End of File ---
