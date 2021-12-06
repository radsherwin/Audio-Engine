#include "ASndAddCmd.h"
#include "ASndManager.h"

ASndAddCmd::ASndAddCmd(Snd* _snd, SndId _sndID)
	: Command(),
	snd(_snd),
	sndID(_sndID)
{
}


void ASndAddCmd::Execute()
{
	ASnd* pASnd = ASndManager::Add(this->snd, this->sndID);
	assert(pASnd);

	delete this;
}

// --- End of File ---
