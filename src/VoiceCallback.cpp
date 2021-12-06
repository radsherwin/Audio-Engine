//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "VoiceCallback.h"
#include "VoiceCallback_PlayNextCmd.h"
#include "QueueManager.h"


VoiceCallback::VoiceCallback(SndId _thisID)
	: thisID(_thisID)
{
	this->pOut = QueueManager::GetAudioInQueue();
}

VoiceCallback::~VoiceCallback()
{

}

void VoiceCallback::OnStreamEnd()
{
	VoiceCallback_PlayNextCmd* pCmd = new VoiceCallback_PlayNextCmd(this->thisID);
	pOut->PushBack(pCmd);

}

void VoiceCallback::OnVoiceProcessingPassEnd()
{
}

void VoiceCallback::OnVoiceProcessingPassStart(UINT32)
{
	//Debug::out("VoiceCallback::OnVoiceProcessingPassStart------------\n");
	//About to end pass in the next voice

}

void VoiceCallback::OnBufferEnd(void*)
{
	//Send custom CallBack Command that asks for appending of buffer

	/*if (this->lastUsedID != this->thisID)
	{
		this->lastUsedID = this->thisID;
		CallbackCmd* stichCmd = new CallbackCmd(this->thisID);
		pOut->PushBack(stichCmd);

	}*/
	
}

void VoiceCallback::OnBufferStart(void*)
{
}

void VoiceCallback::OnLoopEnd(void*)
{
}

void VoiceCallback::OnVoiceError(void*, HRESULT)
{
}

// --- End of File ---
