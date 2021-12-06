#include "AudioThread.h"
#include "XAudio2Wrapper.h"
#include "VoiceCallback.h"
#include "SndCallRegistry.h"
#include "AudioEngine.h"
#include "Voice.h"
#include "VoiceManager.h"
#include "Wave.h"
#include "WaveManager.h"
#include "SndManager.h"
#include "QueueManager.h"
#include "PlaylistManager.h"
#include "APlaylistManager.h"
#include "ASndManager.h"

//Threads
#include "FileThread.h"
#include "AuxThread.h"

using namespace ThreadFramework;

void Audio_Main(std::atomic_bool& QuitFlag)
{
	SimpleBanner b;

	//START FILE THREAD HERE
	std::thread t_File(FileMain, std::ref(QuitFlag));
	Debug::SetName(t_File, "--File--", 2);
	t_File.detach();

	//start aux thread
	std::thread t_Aux(AuxMain, std::ref(QuitFlag));
	Debug::SetName(t_Aux, "--Aux--", 2);
	t_Aux.detach();

	AudioEngine audioEngine;

	VoiceManager::Create();
	WaveManager::Create();
	APlaylistManager::Create();
	PlaylistManager::Create();
	ASndManager::Create();

	CircularData* pAudioIn = QueueManager::GetAudioInQueue();

	// ----------------------------------------
	// Loop for ever until quit is hit
	// ----------------------------------------

	while (!QuitFlag)
	{
		//Debug::out("AudioThread loop running\n");
		Command* p_Cmd;

		if (pAudioIn->PopFront(p_Cmd) == true)
		{
			assert(p_Cmd);
			p_Cmd->Execute();
		
		}

		
	}

	WaveManager::Dump();
	VoiceManager::Dump();

	Debug::out("ASndManager Destroy\n");
	ASndManager::Destroy();
	Debug::out("PlaylistManager Destroy\n");
	PlaylistManager::Destroy();
	Debug::out("APlaylistManager Destroy\n");
	APlaylistManager::Destroy();
	Debug::out("VoiceManager Destroy\n");
	VoiceManager::Destroy();
	WaveManager::Destroy();

}


