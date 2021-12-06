#include "AsyncWaveLoadCmd.h"
#include "WaveManager.h"

AsyncWaveLoadCmd::AsyncWaveLoadCmd(Wave::ID _id, const char* const _pWaveName, User_File_CB* _pFileCB)
	: Command(),
	id(_id),
	pWaveName(_pWaveName),
	pUserFileCB(_pFileCB)
{
	assert(pWaveName);
}


void AsyncWaveLoadCmd::Execute()
{
	WaveManager::Add(this->id, this->pWaveName, this->pUserFileCB);

	delete this;
}


// --- End of File ---
