#ifndef USER_PRIORITY_CB_H
#define USER_PRIORITY_CB_H

#include "Wave.h"
#include "Command.h"
#include "SndCallRegistry.h"

class User_Priority_CB : public Command
{
public:
	User_Priority_CB(SndId _sndID, Wave::ID _waveID, float _amt);
	User_Priority_CB(const User_Priority_CB&) = delete;
	User_Priority_CB& operator=(const User_Priority_CB&) = delete;
	~User_Priority_CB() = default;

	virtual void Execute() override;

private:
	SndId sndID;
	Wave::ID waveID;
	float amt;
};

#endif