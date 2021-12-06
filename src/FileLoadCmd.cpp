#include "FileLoadCmd.h"
#include "FileDataCmd.h"
#include "QueueManager.h"

FileLoadCmd::FileLoadCmd(Wave::ID _waveID, const char* const _pWaveName, Wave* _pWave)
	: Command(),
	waveID(_waveID),
	pWaveName(_pWaveName),
	pWave(_pWave)
{
	assert(pWaveName);
	assert(pWave);
}

void FileLoadCmd::Execute()
{
	//Load the file and fill in data structure
	//This will block on Fiel thread doing the loading
	FileDataCmd* pCmd = new FileDataCmd(this->pWaveName, this->pWave);
	assert(pCmd);

	//Send the data back to audio thread for registration
	bool status = QueueManager::SendAudio(pCmd);
	assert(status == true);

	delete this;
}