#ifndef USER_FILETOGAME_CB_H
#define USER_FILETOGAME_CB_H

#include "Wave.h"
#include "Command.h"
#include "SndCallRegistry.h"

class User_FileToGame_CB : public Command
{
public:
	User_FileToGame_CB(SndId _sndID, Wave::ID _waveID);
	User_FileToGame_CB(const User_File_CB&) = delete;
	User_FileToGame_CB& operator=(const User_FileToGame_CB&) = delete;
	~User_FileToGame_CB() = default;

	virtual void Execute() override;

private:
	SndId sndID;
	Wave::ID waveID;
};

#endif