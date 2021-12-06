#ifndef AUDIO_H
#define AUDIO_H

#include "Wave.h"
#include "SndCallRegistry.h"
#include "WaveTable.h"
#include "PriorityTable.h"
#include "User_File_CB.h"

class Audio
{
public:

	enum class Blocking
	{
		LOAD
	};

	enum class Async
	{
		LOAD
	};

	enum class AudioEvents
	{
		PLAY,
		STOP,
		PAN,
		VOLUME,
		UNLOAD,
		WAVE_TABLE_DUMP,
		PRIORITY_TABLE_DUMP,
		STOP_TIMER,
		UNLOAD_PRIORITY_TABLE,
		UNLOAD_WAVE_TABLE,
		PRIORITY_PLAY,
		PRIORITY_STOP,
		LERP_VOLUME,
		LERP_PAN,
		ELAPSED_TIME,
		DEFAULT
	};

public:
	static void Create();
	static void Destroy();
	static void SoftDestroy();
	static void Update();

	static void Load(const Blocking, Wave::ID _waveID, const char* const _pWaveName);
	static void Load(const Async, Wave::ID _waveID, const char* const _pWaveName, User_File_CB*);
	static void Unload(Wave::ID _waveID);
	
	static WaveTable* GetWaveTable();
	static void WaveTableDump();

	static void CreateSnd(SndId _sndID, Wave::ID _waveID, User_File_CB* = nullptr);
	static void StitchSnd(SndId _sndID, SndId _nextID);
	static void Quit();

	//Async
	static User_File_CB* CreateCB(SndId _sndID, Wave::ID _waveID);

	//Audio
	static void Play(SndId _sndID);
	static void Volume(SndId _sndID, float _amt);
	static void Pan(SndId _sndID, float _amt);
	static void Stop(SndId _sndID);
	static void LerpVolume(SndId _sndID, int direction, int _priority);
	static void LerpPan(SndId _sndID, int direction, int _priority);


	//Timer
	static void StartTimer();
	static void StopTimer();
	static void ClearQueue();
	static void RunEvent(SndId _sndID, Audio::AudioEvents _events, float amt, int _priority, Wave::ID = Wave::ID::Uninitialized);

	static void Timer(Audio::AudioEvents _events, int _time, SndId _sndID, int _priority, float amt = 0.0f);
	static void Timer(Audio::AudioEvents _events, int _time, SndId _sndID,   float amt = 0.0f);
	static void Timer(Audio::AudioEvents _events, int _time, Wave::ID _waveID); //For unload
	static void Timer(Audio::AudioEvents _events, int _time); //For wavetable dump

	//Priority Table stuff
	static void UpdateTime();
	static void SetPriorityTable(SndId _sndID, int _priority, PriorityTable::Status _status);
	static void PriorityTableDump();
	static void RemovePriorityTable(SndId _sndID);
	static void UnloadPriorityTable();
	static void UnloadWaveTable();
	static void PrintPriority(SndId _sndID, Wave::ID _waveID, float _amt);

	//Playlists
	static void CreatePlaylist(SndId _sndID, Wave::ID _waveID);
	static void StitchPlaylist(SndId _sndID, Wave::ID _waveID);

private:
	Audio();
	Audio(const Audio&) = delete;
	Audio& operator=(const Audio&) = delete;
	~Audio();

	WaveTable* poWaveTable;
	PriorityTable* poPriorityTable;

	std::atomic_bool QuitFlag;
	std::atomic_bool TimerQuitFlag;

	static Audio* privGetInstance();
	static Audio* posInstance;

	
};

#endif