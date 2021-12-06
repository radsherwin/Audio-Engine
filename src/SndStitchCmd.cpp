#include "SndStitchCmd.h"
#include "VoiceManager.h"
#include "AudioEngine.h"
#include "SndManager.h"

SndStitchCmd::SndStitchCmd(Snd* _snd, Snd* _nextSnd)
	: Command(),
	pSnd(_snd),
	pNextSound(_nextSnd)

{

}


void SndStitchCmd::Execute()
{
	ASnd* tmpASnd = this->pSnd->GetASnd();
	ASnd* tmpASndNext = this->pNextSound->GetASnd();

	tmpASnd->SetNextVoice(tmpASndNext);
	delete this;
}

// --- End of File ---
