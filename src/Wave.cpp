//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "XAudio2Wrapper.h"
#include "AudioEngine.h"
#include "Wave.h"
#include "StringThis.h"
#include "Audio.h"
#include "AuxIFileCBCmd.h"
#include "QueueManager.h"

#include "AuxUserFileCBCmd.h"
#include "User_File_CB.h"

Wave::Wave()
	: poWfx(nullptr),
	poRawBuff(nullptr),
	rawBuffSize(0),
	id(Uninitialized),
	strName("uninialized"),
	handle()
{
	// nothing dynamic...

	// Pattern:
	//    Manager calls default wave
	//    set(...)  dynamic allocation
	//    privClear(...) release dynamic allocation
	//    destructor release of any owned objects
}

Wave::~Wave()
{
	Debug::out("~Wave()\n");
	delete this->poWfx;
	delete[] this->poRawBuff;
}

void Wave::SetId(Wave::ID _id)
{
	this->id = _id;
}

Wave::ID Wave::GetId() const
{
	return this->id;
}

void Wave::SetPending(const char* const _pWaveName, Wave::ID _waveID, I_File_CB* _pIFileCB)
{
	assert(_pWaveName);
	assert(_pIFileCB);

	this->id = _waveID;
	this->privSetName(_pWaveName);
	this->pUserFileCB = nullptr;
	this->pIFileCB = _pIFileCB;
	this->status = Wave::Status::PENDING;
}

void Wave::SetPending(const char* const _pWaveName, Wave::ID _waveID, User_File_CB* _pUserFileCB)
{
	assert(_pWaveName);
	assert(_pUserFileCB);

	this->id = _waveID;
	this->privSetName(_pWaveName);
	this->pIFileCB = nullptr;
	this->pUserFileCB = _pUserFileCB;
	this->status = Wave::Status::PENDING;
}

void Wave::Register(WAVEFORMATEXTENSIBLE* _poWfx, unsigned char* _poRawBuff, unsigned long _rawBuffSize)
{
	assert(_poWfx);
	this->poWfx = _poWfx;

	assert(_poRawBuff);
	this->poRawBuff = _poRawBuff;

	assert(_rawBuffSize > 0);
	this->rawBuffSize = _rawBuffSize;

	this->status = Wave::Status::READY;

	//should exist on audio thread
	WaveTable* pWaveTable = Audio::GetWaveTable();
	assert(pWaveTable);
	pWaveTable->Update(this->id, WaveTable::Status::READY);

	bool s = false;

	if (this->pIFileCB != nullptr) {
		AuxIFileCBCmd* pCmd = new AuxIFileCBCmd(this->pIFileCB);
		s = QueueManager::SendAux(pCmd);
	}
	
	if (this->pUserFileCB != nullptr) 
	{
		
		AuxUserFileCBCmd* pCmd = new AuxUserFileCBCmd(this->pUserFileCB);
		s = QueueManager::SendAux(pCmd);
	}
	assert(s);
}

void Wave::Dump()
{
	// Dump - Print contents to the debug output window
	Trace::out("\t\tWave(%p) %s \"%s\" \n", this, StringMe(this->id), this->strName);
}

void Wave::privClear()
{
	// This method... is used in wash to reuse the wave
	// Reset the fmt
	delete this->poWfx;
	this->poWfx = nullptr;

	delete[] this->poRawBuff;
	this->poRawBuff = nullptr;

	this->rawBuffSize = 0;

	// ID
	this->id = Wave::ID::Uninitialized;

	// Name
	char* pWaveName = "Uninitialized";
	this->privSetName(pWaveName);
}

void Wave::Wash()
{
	// Wash - clear the entire hierarchy
	DLink::Clear();

	// Sub class clear
	this->privClear();
}

bool Wave::Compare(DLink* pTarget)
{
	// This is used in ManBase.Find() 
	assert(pTarget != nullptr);

	Wave* pDataB = (Wave*)pTarget;

	bool s = false;

	if (this->id == pDataB->id)
	{
		s = true;
	}

	return s;
}

void Wave::privSetName(const char* const pWaveName)
{
	assert(pWaveName);
	memset(this->strName, 0x0, Wave::NAME_SIZE);

	// Quick hack to trim the string before '/
	unsigned int len = strlen(pWaveName);

	const char* pEnd = pWaveName + len;
	const char* pStart = pEnd;

	while (pStart != pWaveName)
	{
		if (*pStart == '/')
		{
			pStart++;
			break;
		}
		pStart--;
	}

	// At this point we have a trimmed name
	strcpy_s(this->strName, Wave::NAME_SIZE, pStart);
}

// --- End of File ---
