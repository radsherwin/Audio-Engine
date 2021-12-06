//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef VOICE_CALLBACK_H
#define VOICE_CALLBACK_H

#include "XAudio2Wrapper.h"
#include "CircularData.h"
#include "SndCallRegistry.h"


using namespace ThreadFramework;
//  Sample voice callback
class VoiceCallback : public IXAudio2VoiceCallback
{
public:
	CircularData* pOut;
	VoiceCallback() = delete;
	VoiceCallback(const VoiceCallback&) = delete;
	VoiceCallback(VoiceCallback&&) = delete;
	VoiceCallback& operator = (const VoiceCallback&) = delete;
	VoiceCallback& operator = (VoiceCallback&&) = delete;
	virtual ~VoiceCallback();

	VoiceCallback(SndId);

	virtual void STDMETHODCALLTYPE OnStreamEnd() override;
	virtual void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() override;
	virtual void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32) override;
	virtual void STDMETHODCALLTYPE OnBufferEnd(void*) override;
	virtual void STDMETHODCALLTYPE OnBufferStart(void*) override;
	virtual void STDMETHODCALLTYPE OnLoopEnd(void*) override;
	virtual void STDMETHODCALLTYPE OnVoiceError(void*, HRESULT) override;

private:
	SndId thisID;
	SndId lastUsedID = SndId::Uninitialized;
};

#endif

// --- End of File ---
