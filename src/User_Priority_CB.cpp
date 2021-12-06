#include "User_Priority_CB.h"
#include "User_File_CB.h"
#include "Audio.h"

using namespace ThreadFramework;

User_Priority_CB::User_Priority_CB(SndId _sndID, Wave::ID _waveID, float _amt)
	: sndID(_sndID),
	waveID(_waveID),
	amt(_amt)
{

}

void User_Priority_CB::Execute()
{
	Debug::out("User_Priority_CB()::Execute()\n");

	//Currently on game thread
	Audio::PrintPriority(sndID, waveID, amt);

	delete this;
}