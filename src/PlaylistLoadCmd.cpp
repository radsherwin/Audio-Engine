#include "PlaylistLoadCmd.h"
#include "APlaylistManager.h"
#include "PlaylistManager.h"

PlaylistLoadCmd::PlaylistLoadCmd(SndId _sndID, Wave::ID _waveID, User_File_CB* _pUserCB)
	: Command(),
	sndID(_sndID),
	waveID(_waveID),
	pUserCB(_pUserCB)
{

}


void PlaylistLoadCmd::Execute()
{
	PlaylistManager::Add(sndID, waveID, pUserCB);

	delete this;
}


// --- End of File ---
