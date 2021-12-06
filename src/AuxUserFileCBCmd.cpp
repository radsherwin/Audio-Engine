using namespace ThreadFramework;

#include "AuxUserFileCBCmd.h"
#include "QueueManager.h"

AuxUserFileCBCmd::AuxUserFileCBCmd(User_File_CB* _pUserFileCB)
	: pUserFileCB(_pUserFileCB)
{
	assert(pUserFileCB);
}

void AuxUserFileCBCmd::Execute()
{
	Debug::out("AuxUserFileCBCmd::Execute()\n");
	//QueueManager::SendAudioGame(this);
	this->pUserFileCB->Execute();

	delete this;
}