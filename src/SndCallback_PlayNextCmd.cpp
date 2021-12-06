#include "SndCallback_PlayNextCmd.h"
#include "VoiceManager.h"
#include "AudioEngine.h"
#include "SndManager.h"

SndCallback_PlayNextCmd::SndCallback_PlayNextCmd(Snd* _snd)
	: Command(),
	pSnd(_snd)

{

}


void SndCallback_PlayNextCmd::Execute()
{
	ASnd* tmpASnd = this->pSnd->GetASnd();

	tmpASnd->Play();
	delete this;
}

// --- End of File ---
