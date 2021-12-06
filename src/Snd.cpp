//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "SndManager.h"
#include "QueueManager.h"
#include "Snd.h"
#include "StringThis.h"


#include "SndStartCmd.h"
#include "SndStopCmd.h"
#include "SndVolumeCmd.h"
#include "SndPanCmd.h"
#include "ASndAddCmd.h"

using namespace ThreadFramework;

Snd::Snd()
	: pASnd(nullptr),
	sndID(SndId::Uninitialized),
	sndWaveID(Wave::Uninitialized),
	pNextID(SndId::Uninitialized),
	isPlaying(false),
	handle()
{
	Handle::Status s = Handle::IsValid(this->handle);
	assert(s == Handle::Status::VALID_HANDLE);
}

Snd::~Snd()
{ 
	assert(Handle::IsValid(this->handle) == Handle::Status::VALID_HANDLE);
}
//MAIN SET
void Snd::Set(SndId _sndID, Wave::ID _waveID)
{
	//ThreadFramework::Debug::out("SND.CPP SET CONSTRUCTION\n");

	this->sndID = _sndID;

	assert(_waveID);
	this->sndWaveID = _waveID;

	//Make ASound
	ASndAddCmd* pCmd = new ASndAddCmd(this, this->sndID);
	assert(pCmd);

	QueueManager::SendAudio(pCmd);

}

//SetASnd
void Snd::Set(ASnd* _aSnd)
{
	assert(_aSnd);
	this->pASnd = _aSnd;
}

void Snd::UpdateSnd(Wave::ID _waveID)
{
	this->sndWaveID = _waveID;
}

ASnd* Snd::GetASnd()
{
	return this->pASnd;
}

void Snd::SetSndID(SndId _sndID)
{
	this->sndID = _sndID;
}
SndId Snd::GetSndID()
{
	return this->sndID;
}

Handle::ID Snd::GetHandleID()
{
	return this->handle.GetID();
}

void Snd::SetNextID(SndId _nextID)
{
	this->pNextID = _nextID;
}

SndId Snd::GetNext()
{
	return this->pNextID;
}


//Manager Methods
//DLINK OVERRIDERS
void Snd::privClear()
{

	this->sndID = SndId::Uninitialized;
}

// Manager methods
char* Snd::GetName()
{
	StringThis s(this->sndID);
	return s;
}

void Snd::Wash()
{
	DLink::Clear();

	this->privClear();
}

void Snd::Dump()
{
	Trace::out("\t\tVoice(%p): %s \n", this, StringMe(this->sndID));
}

bool Snd::Compare(DLink* pTarget)
{
	// This is used in ManBase.Find() 
	assert(pTarget != nullptr);

	Snd* pDataB = (Snd*)pTarget;

	bool status = false;

	if (this->sndID == pDataB->sndID)
	{
		status = true;
	}

	return status;
}

Handle::Status Snd::Play()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		ThreadFramework::Debug::out("--------------------------------------------\n \t\t\t\t\t Starting --->%s \n \t\t\t--------------------------------------------\n", StringMe(this->sndID));
		SndStartCmd* pCmd = new SndStartCmd(this);
		QueueManager::SendAudio(pCmd);

	}

	return lock;
}

Handle::Status Snd::Stop()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		ThreadFramework::Debug::out("--------------------------------------------\n \t\t\t\t Stopping --->%s \n \t\t\t--------------------------------------------\n", StringMe(this->sndID));

		SndStopCmd* pCmd = new SndStopCmd(this);

		QueueManager::SendAudio(pCmd);


	}
	return lock;
}

Handle::Status Snd::AdjustVolume(float amt)
{
	
	
	Handle::Lock lock(this->handle);

	if (lock)
	{
		ThreadFramework::Debug::out("Increasing Volume --->%d\n", (int)this->sndID);

		SndVolumeCmd* pCmd = new SndVolumeCmd(this, amt);

		QueueManager::SendAudio(pCmd);

	}

	return lock;
}

Handle::Status Snd::Pan(float amt)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		ThreadFramework::Debug::out("Panning --->%d\n", (int)this->sndID);

		SndPanCmd* pCmd = new SndPanCmd(this, amt);
		QueueManager::SendAudio(pCmd);
	}

	return lock;
}



// End of File 
