//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef AUX_I_FILE_CB_COMMAND_H
#define AUX_I_FILE_CB_COMMAND_H

#include "Command.h"
#include "I_File_CB.h"

class AuxIFileCBCmd : public Command
{
public:
	// Big 4
	AuxIFileCBCmd() = delete;
	AuxIFileCBCmd(const AuxIFileCBCmd&) = delete;
	AuxIFileCBCmd& operator = (const AuxIFileCBCmd&) = delete;
	~AuxIFileCBCmd() = default;

	AuxIFileCBCmd(I_File_CB* _pIFileCB);

	virtual void Execute() override;

public:
	// Data
	I_File_CB* pIFileCB;
};

#endif

// --- End of File ---
