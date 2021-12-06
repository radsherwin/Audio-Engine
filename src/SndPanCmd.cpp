#include "SndPanCmd.h"
#include "VoiceManager.h"
#include "AudioEngine.h"
#include "SndManager.h"

SndPanCmd::SndPanCmd(Snd* _snd, float _amt)
	: Command(),
	pSnd(_snd),
	amt(_amt)
{

}

void SndPanCmd::Execute()
{
	ASnd* tmpASnd = this->pSnd->GetASnd();

	tmpASnd->Pan(this->amt);
	//AudioEngine::PanSound(*this->aSnd->GetVoice(), this->amt);

	delete this;
}