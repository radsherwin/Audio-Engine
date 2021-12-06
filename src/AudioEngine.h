//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "XAudio2Wrapper.h"
#include "CircularData.h"
#include "VoiceCallback.h"
#include "Voice.h"

class AudioEngine
{
public:
	// Big 4
	AudioEngine();
	AudioEngine(const AudioEngine&) = delete;
	AudioEngine& operator = (const AudioEngine&) = delete;
	~AudioEngine();

	void LoadBuffer(const char* pFileName,
		WAVEFORMATEXTENSIBLE& wfx,
		XAUDIO2_BUFFER& buffer,
		BYTE*& _pDataBuffer);

	static IXAudio2* GetXAudio2();
	static IXAudio2MasteringVoice* GetMasterVoice();
	static void StartSound(Voice& voice);
	static void StopSound(Voice& voice);
	static void AdjustVolume(Voice& voice, float);
	static void PanSound(Voice& voice, float);

private:
	void privStartCOMThreads();
	void privEndCOMThreads();
	void privCreateXAudio2();
	void privCreateMasterVoice();

private:
	//----------------------------------------------------------------------
	// Data - unique data for this manager 
	//----------------------------------------------------------------------
	static AudioEngine* privGetInstance();
	static AudioEngine* psInstance;

	IXAudio2* poXAudio2;
	IXAudio2MasteringVoice* poMasterVoice;
};


#endif

// --- End of File ---
