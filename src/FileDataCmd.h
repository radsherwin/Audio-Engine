//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef FILE_DATA_COMMAND_H
#define FILE_DATA_COMMAND_H

#include "Command.h"
#include "Wave.h"

class FileDataCmd : public Command
{
public:
	// Big 4
	FileDataCmd() = delete;
	FileDataCmd(const FileDataCmd&) = delete;
	FileDataCmd& operator = (const FileDataCmd&) = delete;
	~FileDataCmd() = default;

	//Main call from Snd.cpp
	FileDataCmd(const char* const pWaveName, Wave*);

	virtual void Execute() override;
	void LoadBuffer(const char* const _pWaveName);

public:
	// Data
	WAVEFORMATEXTENSIBLE*	poWfx;
	unsigned char*			poRawBuff;
	unsigned long           rawBuffSize;
	Wave*					pWave;
	const char* const pWaveName;
};

#endif

// --- End of File ---
