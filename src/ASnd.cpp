//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ASnd.h"
#include "StringThis.h"
#include "APlaylistManager.h"
#include "PlaylistManager.h"

using namespace ThreadFramework;

ASnd::ASnd()
	:pPlaylist(nullptr),
	sndID(SndId::Uninitialized),
	pSnd(nullptr)
{
	// nothing dynamic...

	// Pattern:
	//    Manager calls default wave
	//    set(...)  dynamic allocation
	//    privClear(...) release dynamic allocation
	//    destructor release of any owned objects
}

ASnd::~ASnd()
{
	//Debug::out("~ASnd()\n");
}


void ASnd::Set(Snd* _pSnd, SndId _sndID)
{
	this->sndID = _sndID;

	assert(_pSnd);
	this->pSnd = _pSnd;

	pSnd->Set(this);

	//Playlist* pPlayRef = APlaylistManager::Find(_sndID);
	this->pPlaylist = PlaylistManager::Find(_sndID);
	//CHANGE TO FIND PLAYLIST
	//this->pPlaylist = PlaylistManager::Add(_sndID, pPlayRef->pVoice->GetWave()->id, pPlayRef->pHeadVoice);
	assert(this->pPlaylist);
}

Snd* ASnd::GetSnd()
{
	return this->pSnd;
}

void ASnd::Play()
{
	assert(this->pPlaylist);

	this->pPlaylist->Play();

	//Debug::out("ASnd::Play(%p)\n", this);
}

void ASnd::Stop()
{
	assert(this->pPlaylist);

	this->pPlaylist->Stop();
	//Debug::out("ASnd::Stop(%p)\n", this);
}

void ASnd::Pan(float _amt)
{
	assert(this->pPlaylist);

	this->pPlaylist->Pan(_amt);
	//Debug::out("ASnd::Pan(%p)\n", this);
}

void ASnd::AdjustVolume(float _amt)
{
	assert(this->pPlaylist);

	this->pPlaylist->Volume(_amt);

	//Debug::out("ASnd::Volume(%p)\n", this);
}

float ASnd::GetCurrentVolume()
{
	assert(this->pPlaylist);
	return this->pPlaylist->GetCurrentVolume();
}

void ASnd::Dump()
{
	// Dump - Print contents to the debug output window
	Trace::out("\t\tASnd(%p) %s Playlist(%p)\n", this, StringMe(this->sndID), this->pPlaylist);
}

void ASnd::privClear()
{
	this->pPlaylist = nullptr;
	this->sndID = SndId::Uninitialized;
}

void ASnd::Wash()
{
	// Wash - clear the entire hierarchy
	DLink::Clear();

	// Sub class clear
	this->privClear();
}

bool ASnd::Compare(DLink* pTarget)
{
	// This is used in ManBase.Find() 
	assert(pTarget != nullptr);

	ASnd* pDataB = (ASnd*)pTarget;

	bool status = false;

	if (this->sndID == pDataB->sndID)
	{
		status = true;
	}

	return status;
}





// --- End of File ---
