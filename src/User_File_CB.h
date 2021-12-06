#ifndef USER_FILE_CB_H
#define USER_FILE_CB_H

#include "Wave.h"
#include "SndCallRegistry.h"

class User_File_CB
{
public:
	User_File_CB(SndId _sndID, Wave::ID _waveID, bool = false);
	User_File_CB(const User_File_CB&) = delete;
	User_File_CB& operator=(const User_File_CB&) = delete;
	~User_File_CB() = default;

	void Execute();
	void Execute(float _amt);

private:
	SndId sndID;
	Wave::ID waveID;
	bool priorityPlay;

};

#endif