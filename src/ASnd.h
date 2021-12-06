//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ASND_H
#define ASND_H

#include "XAudio2Wrapper.h"
#include "Handle.h"
#include "DLink.h"
//#include "Snd.h"
#include "Playlist.h"

//class Voice;

class ASnd : public DLink
{
public:
	// Big 4
	ASnd();
	ASnd(const ASnd&) = delete;
	ASnd& operator = (const ASnd&) = delete;
	virtual ~ASnd();

	void Set(Snd* pSnd, SndId);
	Snd* GetSnd();

	void Dump();
	void Wash();

	virtual bool Compare(DLink* pTargetNode) override;

	void Play();
	void Stop();
	void AdjustVolume(float);
	void Pan(float);
	float GetCurrentVolume();
	

private:
	void privClear();


public:
	//----------------------------------------------------
	// Data
	//----------------------------------------------------
	Playlist* pPlaylist;
	SndId sndID;
	Snd* pSnd;

	Handle handle;
};

#endif

// --- End of File ---
