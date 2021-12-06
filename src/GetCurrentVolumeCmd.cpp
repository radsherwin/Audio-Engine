#include "GetCurrentVolumeCmd.h"
#include "Audio.h"
#include "SndManager.h"

GetCurrentVolumeCmd::GetCurrentVolumeCmd(Snd* _pSnd, I_File_CB* _pIFileCB)
	: Command(),
	pSnd(_pSnd),
	pIFileCB(_pIFileCB)
{

}

void GetCurrentVolumeCmd::Execute()
{
	//In audio thread
	pSnd->currentVolume = pSnd->GetASnd()->GetCurrentVolume();
	this->pIFileCB->Execute();


	delete this;
}


// --- End of File ---
