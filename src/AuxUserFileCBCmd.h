//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef AUX_USER_FILE_CB_COMMAND_H
#define AUX_USER_FILE_CB_COMMAND_H

#include "Command.h"
#include "User_File_CB.h"

class AuxUserFileCBCmd : public Command
{
public:
	// Big 4
	AuxUserFileCBCmd() = delete;
	AuxUserFileCBCmd(const AuxUserFileCBCmd&) = delete;
	AuxUserFileCBCmd& operator = (const AuxUserFileCBCmd&) = delete;
	~AuxUserFileCBCmd() = default;

	AuxUserFileCBCmd(User_File_CB* _pUserFileCB);

	virtual void Execute() override;

public:
	// Data
	User_File_CB* pUserFileCB;
};

#endif

// --- End of File ---
