//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GET_CURRENT_VOLUME_COMMAND_H
#define GET_CURRENT_VOLUME_COMMAND_H

#include "Command.h"
#include "Snd.h"
#include "I_File_CB.h"

class GetCurrentVolumeCmd : public Command
{

public:
	// Big 4
	GetCurrentVolumeCmd() = default;
	GetCurrentVolumeCmd(const GetCurrentVolumeCmd&) = default;
	GetCurrentVolumeCmd& operator = (const GetCurrentVolumeCmd&) = default;
	virtual ~GetCurrentVolumeCmd() = default;

	GetCurrentVolumeCmd(Snd* _pSnd, I_File_CB* _pIFileCB);

	virtual void Execute() override;

public:
	// Data
	Snd* pSnd;
	I_File_CB* pIFileCB;


};

#endif

// --- End of File ---
