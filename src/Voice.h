//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef VOICE_H
#define VOICE_H

#include "Snd.h"

#include "XAudio2Wrapper.h"
#include "Handle.h"
#include "DLink.h"
#include "Wave.h"
#include "VoiceCallback.h"

class AudioEngine;
//class Snd;

class Voice : public DLink 
{

public:
	Voice();
	Voice& operator=(const Voice& v) = delete;
	Voice(const Voice& v) = delete;
	virtual ~Voice();


	//Manager - non virtual
	void Set(Wave::ID,  Wave*, VoiceCallback*);
	void Clear();
	void UpdateVoice(Wave::ID, Wave*);

	//Manager methods
	virtual char* GetName() override;
	virtual void Wash() override;
	virtual void Dump() override;
	virtual bool Compare(DLink*) override;


	//public voice methods:
	//Handle::Status Stitch(Voice*, IXAudio2MasteringVoice*);
	Handle::Status Play();
	Handle::Status Stop();
	Handle::Status AdjustVolume(float);
	Handle::Status Pan(float, IXAudio2MasteringVoice*);
	Handle::Status PanHelper(float amt, IXAudio2MasteringVoice* _p_masterVoice);
	Handle::Status VolumeHelper(float amt);


	//GETTERS AND SETTERS
	void SetSourceVoice(IXAudio2SourceVoice*);
	IXAudio2SourceVoice* GetSourceVoice();

	void SetWaveID(Wave::ID);
	Wave::ID GetWaveID();

	float GetCurrentVolume();
	float GetCurrentPanning();

	Wave* GetWave();
	Voice* nextVoice;
private:
	void privInitSrcBuff();

private: 
	Wave* p_Wave;

	Wave::ID waveID;

	XAUDIO2_BUFFER* po_Buffer;
	VoiceCallback* por_Callback;
	IXAudio2SourceVoice* po_SourceVoice;	

	float currentVolume;
	float currentPanning;

	//store sourcevoice
	Handle handle;
};

#endif

// --- End of File ---
