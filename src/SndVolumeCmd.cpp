#include "SndVolumeCmd.h"
#include "VoiceManager.h"
#include "AudioEngine.h"
#include "SndManager.h"

SndVolumeCmd::SndVolumeCmd(Snd* _pSnd, float _amt)
	: Command(),
	pSnd(_pSnd),
	amt(_amt)
{

}

void SndVolumeCmd::Execute()
{
	ASnd* tmpASnd = this->pSnd->GetASnd();

	tmpASnd->AdjustVolume(this->amt);

	delete this;
}