#include "SndStopCmd.h"
#include "VoiceManager.h"
#include "AudioEngine.h"
#include "SndManager.h"

SndStopCmd::SndStopCmd(Snd* _pSnd)
	: Command(),
	pSnd(_pSnd)
{

}

void SndStopCmd::Execute()
{

	ASnd* tmpASnd = this->pSnd->GetASnd();

	tmpASnd->Stop();

	delete this;
}