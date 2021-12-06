//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AudioEngine.h"
#include "Playlist.h"
#include "StringThis.h"
#include "VoiceManager.h"
#include "SndManager.h"
#include "QueueManager.h"
#include "PriorityTableRemoveCmd.h"

Playlist::Playlist()
	: pVoice(nullptr),
	pHeadVoice(nullptr),
	sndID(SndId::Uninitialized)
{
	// nothing dynamic...

	// Pattern:
	//    Manager calls default wave
	//    set(...)  dynamic allocation
	//    privClear(...) release dynamic allocation
	//    destructor release of any owned objects
}

Playlist::~Playlist()
{
	//Debug::out("~Playlist()\n");
	if (this->pVoice)
	{
		VoiceManager::Remove(this->pVoice);
		//this->pHeadVoice = tmp;
		this->pVoice = nullptr;
	}


}

void Playlist::SetId(SndId _sndID)
{
	this->sndID = _sndID;
}

SndId Playlist::GetId() const
{
	return this->sndID;
}

void Playlist::Set(SndId _sndID, Wave::ID _waveID, Voice* _pHeadVoice, User_File_CB* _pUserCB)
{
	this->sndID = _sndID;
	this->waveID = _waveID;
	this->pUserCB = _pUserCB;
	if (_pHeadVoice == nullptr)
	{
		this->pVoice = VoiceManager::Add(_waveID, _sndID);
		this->pHeadVoice = this->pVoice;
	}
	else
	{
		this->pHeadVoice = _pHeadVoice;
		this->pVoice = this->pHeadVoice;
	}
	assert(this->pVoice);
}

void Playlist::AddVoices(SndId _sndID, Wave::ID _waveID)
{

	Voice* tmp = this->pHeadVoice;
	while (tmp != nullptr)
	{
		if (tmp->nextVoice == nullptr)
		{
			tmp->nextVoice = VoiceManager::Add(_waveID, _sndID);
			break;
		}
		tmp = tmp->nextVoice;
	}

	
}

void Playlist::PlayNext()
{
	if (this->pUserCB != nullptr)
	{
		this->pUserCB->Execute(this->pVoice->GetCurrentPanning());
		this->pUserCB = nullptr;
	}

	if (this->pVoice->nextVoice == nullptr)
	{



		//PriorityTableRemoveCmd* pCmd = new PriorityTableRemoveCmd(this->sndID);
		//QueueManager::SendGame(pCmd);
		Debug::out("Playlist finished --------->%s\n", StringMe(this->sndID));
	}
	else
	{
		
		this->pVoice = this->pVoice->nextVoice;
		this->waveID = this->pVoice->GetWaveID();
		AudioEngine::StartSound(*this->pVoice);
		//Trace::out("PLAYNEXT Voice panning: %#4x, homeVoice: %#4x\n", this->pVoice, this->pHeadVoice);
		Debug::out("Now stitching --------->%s\n", StringMe(this->waveID));
	}
	
}

void Playlist::UpdatePlaylist(Wave::ID _waveID)
{
	this->waveID = _waveID;
	VoiceManager::UpdateVoice(_waveID);
}

void Playlist::Play()
{
	AudioEngine::StartSound(*this->pVoice);
}
void Playlist::Stop()
{
	AudioEngine::StopSound(*this->pVoice);
}
void Playlist::Volume(float _amt)
{
	AudioEngine::AdjustVolume(*this->pHeadVoice, _amt);
}
void Playlist::Pan(float _amt)
{
	//Trace::out("Voice panning: %#4x, homeVoice: %#4x\n", this->pVoice, this->pHeadVoice);
	AudioEngine::PanSound(*this->pHeadVoice, _amt);
}


float Playlist::GetCurrentVolume()
{
	return this->pVoice->GetCurrentVolume();
}


void Playlist::Dump()
{
	// Dump - Print contents to the debug output window
	Trace::out("\t\tPlaylist(%p) %s Voice(%p) src:%p\n", this, StringMe(this->sndID), this->pVoice, this->pVoice->GetSourceVoice());
}

void Playlist::privClear()
{
	// This method... is used in wash to reuse 
	// If its alive... remove the data
	if (this->pVoice)
	{
		VoiceManager::Remove(this->pVoice);
		this->pVoice = nullptr;
	}


	this->sndID = SndId::Uninitialized;

}

void Playlist::Wash()
{
	// Wash - clear the entire hierarchy
	DLink::Clear();

	// Sub class clear
	this->privClear();
}

bool Playlist::Compare(DLink* pTarget)
{
	// This is used in ManBase.Find() 
	assert(pTarget != nullptr);

	Playlist* pDataB = (Playlist*)pTarget;

	bool status = false;

	if (this->sndID == pDataB->sndID)
	{
		status = true;
	}

	return status;
}





// --- End of File ---
