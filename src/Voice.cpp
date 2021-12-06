#include "Voice.h"
#include "AudioEngine.h"
#include "StringThis.h"
#include "SndCallRegistry.h"

#include "VoiceManager.h"

using namespace ThreadFramework;

Voice::Voice()
	:nextVoice(nullptr),
	p_Wave(nullptr),
	waveID(Wave::ID::Uninitialized),
	por_Callback(nullptr),
	po_SourceVoice(nullptr),
	handle()
{
	Handle::Status s = Handle::IsValid(this->handle);
	assert(s == Handle::Status::VALID_HANDLE);

	this->po_Buffer = new XAUDIO2_BUFFER();
	assert(this->po_Buffer);

	Debug::out("voice(): %p\n", this);
}


Voice::~Voice()
{
	Debug::out("~Voice()\n");

	// This was initialized in XAudio2... so its destroyed there

	// Protection for empty voices
	if (this->po_SourceVoice)
	{
		this->po_SourceVoice->Stop();
		this->po_SourceVoice->DestroyVoice();
		this->po_SourceVoice = nullptr;
	}

	if (this->po_Buffer)
	{
		// Done in the wave manager
			//delete this->poBuff->pAudioData;
		delete this->po_Buffer;
		this->po_Buffer = nullptr;
	}

	if (this->por_Callback)
	{
		delete this->por_Callback;
		this->por_Callback = nullptr;
	}

	if (this->nextVoice !=nullptr && this->nextVoice->waveID == Wave::ID::Uninitialized)
	{
		this->nextVoice = nullptr;
	}
}

void Voice::privInitSrcBuff()
{
	assert(this->po_Buffer);
	assert(this->p_Wave);

	*po_Buffer = { 0 };

	po_Buffer->AudioBytes = p_Wave->rawBuffSize; //buffer containing audio data
	po_Buffer->pAudioData = p_Wave->poRawBuff;   //size of the audio buffer in bytes
	po_Buffer->Flags = XAUDIO2_END_OF_STREAM;   // tell the source voice not to expect any data after this buffer
	po_Buffer->LoopCount = 0;				     // looping...

}

void Voice::Set(Wave::ID _waveID,  Wave* _p_Wave, VoiceCallback* _p_Callback)
{
	Debug::out("voice::set(): %p\n", this);
	Handle::Status s;

	s = Handle::IsValid(this->handle);
	assert(s == Handle::Status::INVALID_HANDLE);

	s = Handle::ActivateHandle(this->handle);
	assert(s == Handle::Status::VALID_HANDLE);

	this->waveID = _waveID;
	this->currentVolume = 0.1f;
	this->currentPanning = 0.0f;

	assert(_p_Wave);
	this->p_Wave = _p_Wave;

	this->nextVoice = nullptr;
	// transfer ownership
	assert(_p_Callback);
	this->por_Callback = _p_Callback;

	IXAudio2* pXAudio2 = AudioEngine::GetXAudio2();
	assert(pXAudio2);

	// Create Source Voice
	this->po_SourceVoice = nullptr;
	HRESULT hr;
	hr = pXAudio2->CreateSourceVoice(&this->po_SourceVoice, (WAVEFORMATEX*)this->p_Wave->poWfx, 0, XAUDIO2_MAX_FREQ_RATIO, this->por_Callback);
	assert(hr == S_OK);
	assert(this->po_SourceVoice);


	// SourceBuffer
	assert(this->po_Buffer);
	this->privInitSrcBuff();
	hr = this->po_SourceVoice->SubmitSourceBuffer(this->po_Buffer);
	assert(hr == S_OK);
	assert(this->po_Buffer);
}


//SETTERS AND GETTERS
void Voice::SetSourceVoice(IXAudio2SourceVoice* _p_sourceVoice)
{
	this->po_SourceVoice = _p_sourceVoice;
}

IXAudio2SourceVoice* Voice::GetSourceVoice()
{
	return this->po_SourceVoice;
}

void Voice::SetWaveID(Wave::ID _waveID)
{
	this->waveID = _waveID;
}

Wave::ID Voice::GetWaveID()
{
	return this->waveID;
}

Wave* Voice::GetWave()
{
	return this->p_Wave;
}

float Voice::GetCurrentVolume()
{
	return this->currentVolume;
}

float Voice::GetCurrentPanning()
{
	return this->currentPanning;
}


//DLINK OVERRIDERS
void Voice::Clear()
{
	assert(this->po_Buffer);
	*this->po_Buffer = { 0 };

	if (this->por_Callback)
	{
		delete this->por_Callback;
		this->por_Callback = nullptr;
	}

	if (this->po_SourceVoice)
	{
		this->po_SourceVoice->Stop();
		this->po_SourceVoice->DestroyVoice();
		this->po_SourceVoice = nullptr;
	}

	this->waveID = Wave::ID::Uninitialized;

	Debug::out(" voice::clear()  %p\n", this);
	// validate when used in Set

	Handle::Status s = Handle::IsValid(this->handle);
	//assert(s == Handle::Status::VALID_HANDLE);
	if (s == Handle::Status::VALID_HANDLE)
	{
		s = Handle::InvalidateHandle(this->handle);
		assert(s == Handle::Status::INVALID_HANDLE);
	}
	
}

void Voice::UpdateVoice(Wave::ID _waveID, Wave* _pWave)
{
	this->waveID = _waveID;
	this->p_Wave = _pWave;

	if (this->po_SourceVoice)
	{
		this->po_SourceVoice->Stop();
		this->po_SourceVoice->DestroyVoice();
		this->po_SourceVoice = nullptr;
	}

	IXAudio2* pXAudio2 = AudioEngine::GetXAudio2();
	assert(pXAudio2);

	// Create Source Voice
	this->po_SourceVoice = nullptr;
	HRESULT hr;
	hr = pXAudio2->CreateSourceVoice(&this->po_SourceVoice, (WAVEFORMATEX*)this->p_Wave->poWfx, 0, XAUDIO2_MAX_FREQ_RATIO, this->por_Callback);
	assert(hr == S_OK);
	assert(this->po_SourceVoice);


	// SourceBuffer
	assert(this->po_Buffer);
	this->privInitSrcBuff();
	hr = this->po_SourceVoice->SubmitSourceBuffer(this->po_Buffer);
	assert(hr == S_OK);
	assert(this->po_Buffer);
}

// Manager methods
char* Voice::GetName()
{
	StringThis s(this->waveID);
	return s;
}

void Voice::Wash()
{
	this->Clear();
	/*Voice* tmp = this;
	while (tmp != nullptr)
	{
		
		tmp = tmp->nextVoice;
	}*/
	
}

void Voice::Dump()
{
	Trace::out("\t\tVoice(%p): %s \n", this, StringMe(this->waveID));
}

bool Voice::Compare(DLink* pTarget)
{
	// This is used in ManBase.Find() 
	assert(pTarget != nullptr);

	Voice* pDataB = (Voice*)pTarget;

	bool status = false;

	if (this->waveID == pDataB->waveID)
	{
		status = true;
	}

	return status;
}

//CREATING MAIN /
//X AUDIO STUFF /


//AUDIO 
Handle::Status Voice::Play()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		HRESULT hr;
		this->po_SourceVoice->FlushSourceBuffers();
		this->privInitSrcBuff();
		hr = this->po_SourceVoice->SubmitSourceBuffer(this->po_Buffer);

		Voice* tmp = this;

		while (tmp != nullptr)
		{
			Debug::out("Voice: %#4x\n", tmp);
			tmp = tmp->nextVoice;
		}

		hr = po_SourceVoice->SetVolume(this->currentVolume);
		//this->currentVolume = 0.1f;
		//this->currentPanning = 0.0f;
		assert(hr == S_OK);
		hr = po_SourceVoice->Start(0);
		assert(hr == S_OK);
	}

	return lock;
	
}


Handle::Status Voice::Stop()
{
	
	Handle::Lock lock(this->handle);

	if (lock)
	{
		//HRESULT hr;
		//hr = po_SourceVoice->Stop(0);
		
		Voice* tmp = this;

		while(tmp != nullptr)
		{
			tmp->po_SourceVoice->Stop();
			tmp = tmp->nextVoice;
		}

		//assert(hr == S_OK);
	}

	return lock;
	
}

Handle::Status Voice::VolumeHelper(float amt)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		Voice* tmp = this;
		while (tmp != nullptr)
		{
			tmp->currentVolume = amt;
			tmp->AdjustVolume(amt);
			tmp = tmp->nextVoice;
		}
	}
	return lock;
}

Handle::Status Voice::AdjustVolume(float amt)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		HRESULT hr;
		hr = po_SourceVoice->SetVolume(amt);
		this->currentVolume = amt;

		assert(hr == S_OK);
	}

	return lock;
}

Handle::Status Voice::PanHelper(float amt, IXAudio2MasteringVoice* _p_masterVoice)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		Voice* tmp = this;
		while (tmp != nullptr)
		{
			tmp->currentPanning = amt;
			tmp->Pan(amt, _p_masterVoice);
			tmp = tmp->nextVoice;
		}
	}
	return lock;
}

Handle::Status Voice::Pan(float amt, IXAudio2MasteringVoice* _p_masterVoice)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		//homeVoice->currentPanning = amt;
		this->currentPanning = amt;

		DWORD dwChannelMask;
		_p_masterVoice->GetChannelMask(&dwChannelMask);

		float outputMatrix[8];
		for (int i = 0; i < 8; i++) outputMatrix[i] = 0;

		float left = 0.5f - amt / 2;
		float right = 0.5f + amt / 2;

		//set local output matrix
		outputMatrix[0] = outputMatrix[2] = left;
		outputMatrix[1] = outputMatrix[3] = right;

		// Assuming pVoice sends to pMasteringVoice

		XAUDIO2_VOICE_DETAILS VoiceDetails;
		this->po_SourceVoice->GetVoiceDetails(&VoiceDetails);

		XAUDIO2_VOICE_DETAILS MasterVoiceDetails;
		_p_masterVoice->GetVoiceDetails(&MasterVoiceDetails);

		this->po_SourceVoice->SetOutputMatrix(NULL, VoiceDetails.InputChannels, MasterVoiceDetails.InputChannels, outputMatrix);
		
	}

	return lock;
	
}

