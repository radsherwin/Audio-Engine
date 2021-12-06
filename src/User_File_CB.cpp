#include "User_File_CB.h"
#include "User_FileToGame_CB.h"
#include "User_Priority_CB.h"
#include "QueueManager.h"

using namespace ThreadFramework;

User_File_CB::User_File_CB(SndId _sndID, Wave::ID _waveID, bool _priority)
	: sndID(_sndID),
	waveID(_waveID),
	priorityPlay(_priority)
{

}

void User_File_CB::Execute()
{
	Debug::out("User_File_CB()::Execute()\n");
	if (!priorityPlay)
	{
		//Send Callback back to game thread, we're currently in Aux
		User_FileToGame_CB* pCmd = new User_FileToGame_CB(sndID, waveID);
		QueueManager::SendGame(pCmd);
	}	

	delete this;
}

void User_File_CB::Execute(float _amt)
{
	if (priorityPlay)
	{
		User_Priority_CB* pCmd = new User_Priority_CB(sndID, waveID, _amt);
		QueueManager::SendGame(pCmd);
	}

	delete this;
}