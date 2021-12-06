#include "WaveLoadCmd.h"
#include "WaveManager.h"

WaveLoadCmd::WaveLoadCmd(Wave::ID _id, const char* const _pWaveName, I_File_CB* _pFileCB)
	: Command(),
	id(_id),
	pWaveName(_pWaveName),
	pIFileCB(_pFileCB)
{
	assert(pWaveName);
}


void WaveLoadCmd::Execute()
{
	WaveManager::Add(this->id, this->pWaveName, this->pIFileCB);

	delete this;
}


// --- End of File ---
