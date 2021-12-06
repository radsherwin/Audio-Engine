#include "VoiceCallback_PlayNextCmd.h"
#include "Playlist.h"
#include "PlaylistManager.h"
#include "StringThis.h"

VoiceCallback_PlayNextCmd::VoiceCallback_PlayNextCmd(SndId _thisID)
	: Command(),
	thisID(_thisID)
{

}

void VoiceCallback_PlayNextCmd::Execute()
{
	////At this point we're in AUDIO THREAD

	//We're in audio thread
	Playlist* pPlay = PlaylistManager::Find(thisID);
	pPlay->PlayNext();
	

	delete this;
}


// --- End of File ---
