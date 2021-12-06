//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Playlist_H
#define Playlist_H

#include "XAudio2Wrapper.h"
#include "Handle.h"
#include "DLink.h"
#include "Snd.h"
#include "Voice.h"
#include "PlaylistCmd.h"
#include "SndCallRegistry.h"
#include "User_File_CB.h"


class Playlist : public DLink
{
	enum class AudioEvents
	{
		PLAY,
		STOP,
		PAN,
		VOLUME,
		STITCH
	};
public:
	// Big 4
	Playlist();
	Playlist(const Playlist&) = delete;
	Playlist& operator = (const Playlist&) = delete;
	virtual ~Playlist();

	//void Set(SndId, Wave::ID);
	void Set(SndId, Wave::ID, Voice* _pHeadVoice, User_File_CB* = nullptr);
	void AddVoices(SndId _sndID, Wave::ID _waveID);
	void PlayNext();
	void UpdatePlaylist(Wave::ID _waveID);

	void Play();
	void Stop();
	void Volume(float _amt);
	void Pan(float _amt);
	float GetCurrentVolume();


	void SetId(SndId id);
	SndId GetId() const;

	void Dump();
	void Wash();

	virtual bool Compare(DLink* pTargetNode) override;
	
private:
	void privClear();
	//void privLoadBuffer(const char* const pWaveName);
	//void privSetName(const char* const pWaveName);

public:
	//----------------------------------------------------
	// Data
	//----------------------------------------------------

	// In the future it can be many...
	Voice* pVoice;
	Voice* pHeadVoice;
	User_File_CB* pUserCB;
	SndId sndID;
	Wave::ID waveID;
	Handle handle;
};

#endif

// --- End of File ---
