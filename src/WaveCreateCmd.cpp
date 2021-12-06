#include "WaveCreateCmd.h"
#include "WaveManager.h"

WaveCreateCmd::WaveCreateCmd(Wave::ID _id, const char* const _pWaveName)
	: Command(),
	id(_id),
	pWaveName(_pWaveName)
{
	assert(pWaveName);
}


void WaveCreateCmd::Execute()
{
	WaveManager::Add(this->id, this->pWaveName);

	delete this;
}


// --- End of File ---
