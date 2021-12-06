#include "CallbackCmd.h"
#include "Snd.h"
#include "SndManager.h"
#include "StringThis.h"
#include "SndStitchCmd.h"
#include "QueueManager.h"

CallbackCmd::CallbackCmd(SndId _thisID)
	: Command(),
	thisID(_thisID)
{

}

void CallbackCmd::Execute()
{
	//At this point we're in GAME THREAD
	Snd* curSnd = SndManager::Find(this->thisID);

	SndId nextSndId = curSnd->GetNext();
	if (nextSndId != SndId::Uninitialized)
	{
		Snd* nextSnd = SndManager::Find(nextSndId);
		Debug::out("Current:  %s, next:  %s \n", StringMe(this->thisID), StringMe(nextSndId));

		SndStitchCmd* pCmd = new SndStitchCmd(curSnd, nextSnd);
		QueueManager::SendAudio(pCmd);
	}
	
	delete this;
}


// --- End of File ---
