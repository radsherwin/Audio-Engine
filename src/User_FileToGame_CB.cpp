#include "User_FileToGame_CB.h"
#include "User_File_CB.h"
#include "Audio.h"

using namespace ThreadFramework;

User_FileToGame_CB::User_FileToGame_CB(SndId _sndID, Wave::ID _waveID)
	: sndID(_sndID),
	waveID(_waveID)
{

}

void User_FileToGame_CB::Execute()
{
	Debug::out("User_FileToGame_CB()::Execute()\n");

	Audio::CreateSnd(this->sndID, this->waveID);
	Audio::Play(this->sndID);
	Audio::Volume(this->sndID, 0.5f);

	delete this;
}