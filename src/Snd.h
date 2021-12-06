//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SND_H
#define SND_H

#include "Handle.h"
#include "SndCallRegistry.h"
#include"DLink.h"
#include "Wave.h"

class ASnd;

class Snd : public DLink
{
public:
	// defaults
	Snd();
	Snd(const Snd&) = delete;
	const Snd& operator=(const Snd&) = delete;
	virtual ~Snd();

	// public
	//Snd();
	
	//CreateSnd
	void Set(SndId _voiceID, Wave::ID);
	void Set(ASnd*);
	void UpdateSnd(Wave::ID);
	ASnd* GetASnd();

	//Manager methods
	virtual char* GetName() override;
	virtual void Wash() override;
	virtual void Dump() override;
	virtual bool Compare(DLink*) override;	

	Handle::Status Play();
	Handle::Status Stop();
	Handle::Status AdjustVolume(float);
	Handle::Status Pan(float);

	void SetNextID(SndId);
	SndId GetNext();

	void SetSndID(SndId);
	SndId GetSndID();

	Handle::ID GetHandleID();

	float currentVolume;

private:
	void privClear();

private:
	ASnd* pASnd;
	
	SndId sndID;
	Wave::ID sndWaveID;

	SndId pNextID;
	
	bool isPlaying;
	Handle handle;
};

#endif


// End of File 
