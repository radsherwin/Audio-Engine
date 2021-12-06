#include "SndStartCmd.h"
#include "VoiceManager.h"
#include "AudioEngine.h"
#include "SndManager.h"
#include "StringThis.h"

SndStartCmd::SndStartCmd(Snd* _snd)
	: Command(),
	pSnd(_snd)

{

}


void SndStartCmd::Execute()
{
	ASnd* tmpASnd = this->pSnd->GetASnd();
	ThreadFramework::Debug::out("SndStartCmd() -> pSnd: %s\n", StringMe(this->pSnd->GetSndID()));
	tmpASnd->Play();
	delete this;
}

// --- End of File ---
