#include "PlaylistStitchCmd.h"
#include "PlaylistManager.h"
#include "Playlist.h"

PlaylistStitchCmd::PlaylistStitchCmd(SndId _sndID, Wave::ID _waveID)
	: Command(),
	sndID(_sndID),
	waveID(_waveID)
{

}


void PlaylistStitchCmd::Execute()
{
	Playlist* pPlay = PlaylistManager::Find(sndID);
	pPlay->AddVoices(sndID, waveID);
	

	delete this;
}


// --- End of File ---
