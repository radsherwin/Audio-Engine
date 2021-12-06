//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef WAVE_H
#define WAVE_H

#include "XAudio2Wrapper.h"
#include "Handle.h"
#include "DLink.h"
#include "I_File_CB.h"

class User_File_CB;

class Wave : public DLink
{
public:
	enum ID
	{
		Fiddle = 0x77770000,
		Bassoon,
		Strings,
		Calliope,
		Oboe,
		SongA,
		SongB,
		A,
		AtoB,
		B,
		BtoC,
		C,
		CtoA,
		End,
		Intro,
		Electro,
		Alarm,
		Beethoven,
		Coma,
		Dial,
		MoonPatrol,
		Sequence,
		Donkey,
		Uninitialized,
		Empty
	};

	enum Status
	{
		READY,
		PENDING,
		EMPTY
	};

	static const unsigned int NAME_SIZE = 256;

public:
	// Big 4
	Wave();
	Wave(const Wave&) = delete;
	Wave& operator = (const Wave&) = delete;
	virtual ~Wave();

	void SetPending(const char* const _pWaveName, Wave::ID _waveID, I_File_CB* _pIFileCB);
	void SetPending(const char* const _pWaveName, Wave::ID _waveID, User_File_CB* _pUserFileCB);

	void Register(WAVEFORMATEXTENSIBLE* _poWfx, unsigned char* _poRawBuff, unsigned long rawBuffSize);

	void SetId(Wave::ID id);
	Wave::ID GetId() const;

	void Dump();
	void Wash();

	virtual bool Compare(DLink* pTargetNode) override;

private:
	void privClear();
	void privSetName(const char* const pWaveName);

public:
	//-------------------------------------------
	// Data:  public for now
	//-------------------------------------------

	I_File_CB* pIFileCB;
	User_File_CB* pUserFileCB;

	WAVEFORMATEXTENSIBLE* poWfx;
	unsigned char* poRawBuff;
	Wave::Status status;
	unsigned long           rawBuffSize;
	ID                      id;
	char                    strName[NAME_SIZE];

	Handle handle;
};

#endif

// --- End of File ---
