#include "Audio.h"
#include "I_File_CB.h"
#include "WaveLoadCmd.h"
#include "QueueManager.h"
#include "SndManager.h"
#include "PlaylistManager.h"

//Game Thread stuff
#include "AudioThread.h"
#include "HandleMan.h"
#include "GameTimer.h"
#include "TimerCmd.h"
#include "AsyncWaveLoadCmd.h"
#include "AuxUserFileCBCmd.h"
#include "LerpVolume.h"
#include "LerpPan.h"

#include "StringThis.h"

Audio* Audio::posInstance = nullptr;



Audio::Audio()
	:QuitFlag(false),
	TimerQuitFlag(false)
{
	this->poWaveTable = new WaveTable();
	this->poPriorityTable = new PriorityTable();
	//this->poEventList = new EventList();
}





Audio::~Audio()
{

}

void Audio::Create()
{
	assert(posInstance == nullptr);

	if (posInstance == nullptr)
	{
		posInstance = new Audio();
	}
	//main thread
	std::thread  t_Audio(Audio_Main, std::ref(posInstance->QuitFlag));
	Debug::SetName(t_Audio, "--Audio--");
	t_Audio.detach();

	HandleMan::Create();
	QueueManager::Create();
	SndManager::Create();
}

void Audio::Destroy()
{
	Audio* pMan = Audio::privGetInstance();
	assert(pMan != nullptr);

	delete pMan->poWaveTable;
	delete pMan->poPriorityTable;

	delete Audio::posInstance;
	Audio::posInstance = nullptr;
}

void Audio::SoftDestroy()
{
	/*SndManager::SoftDestroy();
	SoftDestroyCmd* pCmd = new SoftDestroyCmd();
	QueueManager::SendAudio(pCmd);*/

}

void Audio::Update()
{
	CircularData* pAudioGameIn = QueueManager::GetAudioGameInQueue();

	Command* pCmd;

	//Audio* pAudio = Audio::privGetInstance();

	if (pAudioGameIn->PopFront(pCmd) == true)
	{
		pCmd->Execute();
	}

	//Receieve usercallback when it's done loading. 
}

void Audio::Quit()
{
	Audio* pMan = Audio::privGetInstance();
	assert(pMan != nullptr);

	pMan->QuitFlag = true;
	pMan->TimerQuitFlag = true;
}

void Audio::WaveTableDump()
{
	Audio* pAudio = Audio::privGetInstance();
	pAudio->poWaveTable->Dump();
}

WaveTable* Audio::GetWaveTable()
{
	Audio* pAudio = Audio::privGetInstance();
	return pAudio->poWaveTable;
}

void Audio::UnloadPriorityTable()
{
	Audio* pAudio = Audio::privGetInstance();
	pAudio->poPriorityTable->ClearTable();
}

void Audio::UnloadWaveTable()
{
	Audio* pAudio = Audio::privGetInstance();
	pAudio->poWaveTable->ClearTable();
}

void Audio::PrintPriority(SndId _sndID, Wave::ID _waveID, float _amt)
{
	Audio* pAudio = Audio::privGetInstance();
	pAudio->poPriorityTable->Print(_sndID, StringMe(_waveID), _amt);
}

Audio* Audio::privGetInstance()
{
	assert(posInstance != nullptr);

	return posInstance;
}

void Audio::ClearQueue()
{
	CircularData* pGameIn = QueueManager::GetGameInQueue();
	CircularData* pAudioGameIn = QueueManager::GetAudioGameInQueue();

	pGameIn->ClearQueue();
	pAudioGameIn->ClearQueue();
}

void Audio::Load(Blocking, Wave::ID _waveID, const char* const _pWaveName)
{
	Audio* pAudio = Audio::privGetInstance();

	//Is wave in wavetable?
	WaveTable* pWaveTable = pAudio->poWaveTable;
	WaveTable::Table* pTable = pWaveTable->Find(_waveID);

	//If not there
	if (pTable == nullptr)
	{
		pWaveTable->Register(_waveID, WaveTable::Status::PENDING);

		assert(_pWaveName);

		//Setup the callback
		bool DoneFlag = false;
		I_File_CB* pFileCB = new I_File_CB(DoneFlag);

		WaveLoadCmd* pCmd = new WaveLoadCmd(_waveID, _pWaveName, pFileCB);
		assert(pCmd);

		QueueManager::SendAudio(pCmd);

		while (!DoneFlag);
	}
	else
	{
		//its ready or pending
		if (pTable->status == WaveTable::Status::READY || pTable->status == WaveTable::Status::PENDING)
		{
			//Do nothing
		}
		else
		{
			//bad
			assert(false);
		}
	}

	
}

void Audio::Load(Async, Wave::ID _waveID, const char* const _pWaveName, User_File_CB* _userCB)
{
	Audio* pAudio = Audio::privGetInstance();

	//Is this already loaded?
	WaveTable* pWaveTable = pAudio->poWaveTable;
	WaveTable::Table* pTable = pWaveTable->Find(_waveID);


	if (pTable == nullptr)
	{
		pWaveTable->Register(_waveID, WaveTable::Status::PENDING);

		assert(_pWaveName);

		AsyncWaveLoadCmd* pCmd = new AsyncWaveLoadCmd(_waveID, _pWaveName, _userCB);
		assert(pCmd);

		QueueManager::SendAudio(pCmd);
	}
	else
	{
		//its ready or pending
		if (pTable->status == WaveTable::Status::READY || pTable->status == WaveTable::Status::PENDING)
		{
			//Pass userCB straight to Aux 
			AuxUserFileCBCmd* pCmd = new AuxUserFileCBCmd(_userCB);
			QueueManager::SendAux(pCmd);
		}
		else
		{
			//bad
			assert(false);
		}
	}
}

void Audio::Unload(Wave::ID _waveID)
{
	Audio* pAudio = Audio::privGetInstance();

	//Is this already loaded?
	WaveTable* pWaveTable = pAudio->poWaveTable;
	WaveTable::Table* pTable = pWaveTable->Find(_waveID);

	if (pTable != nullptr)
	{
		pWaveTable->Remove(_waveID);
	}
	else
	{
		//Not even on table
	}
}

User_File_CB* Audio::CreateCB(SndId _sndID, Wave::ID _waveID)
{
	User_File_CB* pUserCB = new User_File_CB(_sndID, _waveID);

	return pUserCB;
}

void Audio::CreatePlaylist(SndId _sndID, Wave::ID _waveID)
{
	Audio* pAudio = Audio::privGetInstance();

	//Is wave in wavetable?
	WaveTable* pWaveTable = pAudio->poWaveTable;
	WaveTable::Table* pTable = pWaveTable->Find(_waveID);

	if (pTable != nullptr && pTable->status == WaveTable::Status::READY)
	{
		//PlaylistManager::Load(_sndID, _waveID);
		PlaylistManager::Add(_sndID, _waveID);
		SndManager::Add(_sndID, _waveID);
	}
}

void Audio::StitchPlaylist (SndId _sndID, Wave::ID _waveID)
{
	PlaylistManager::Stitch(_sndID, _waveID);
}


void Audio::CreateSnd(SndId _sndID, Wave::ID _waveID, User_File_CB* _pUserCB)
{
	//Check if loaded,
	//If not loaded, send callback
	
	Audio* pAudio = Audio::privGetInstance();

	//Is wave in wavetable?
	WaveTable* pWaveTable = pAudio->poWaveTable;
	WaveTable::Table* pTable = pWaveTable->Find(_waveID);        

	if (pTable != nullptr && pTable->status == WaveTable::Status::READY)
	{
		Snd* snd = SndManager::Find(_sndID);
		if (snd == nullptr)
		{
			//PlaylistManager::Load(_sndID, _waveID, _pUserCB);
			PlaylistManager::Add(_sndID, _waveID, _pUserCB);
			SndManager::Add(_sndID, _waveID);
		}
	}
	else 
	{
		//Send callback to AudioGameIn, 
	}
	
}

void Audio::StitchSnd(SndId _sndID, SndId _nextID)
{
	SndManager::Stitch(_sndID, _nextID);
}

void Audio::Play(SndId _sndID)
{
	Snd* snd = SndManager::Find(_sndID);
	if (snd != nullptr)
	{
		snd->Play();
	}
}

void Audio::Volume(SndId _sndID, float _amt)
{
	Snd* snd = SndManager::Find(_sndID);
	snd->AdjustVolume(_amt);
}

void Audio::Pan(SndId _sndID, float _amt)
{
	Snd* snd = SndManager::Find(_sndID);
	snd->Pan(_amt);
}

void Audio::Stop(SndId _sndID)
{
	Snd* snd = SndManager::Find(_sndID);
	if (snd != nullptr) snd->Stop();
}

void Audio::LerpVolume(SndId _sndID, int direction, int _priority)
{
	SetPriorityTable(_sndID, _priority, PriorityTable::Status::PLAY);
	Snd* snd = SndManager::Find(_sndID);
	std::thread t_LerpVolume(LerpVolume_Main, snd, direction);
	Debug::SetName(t_LerpVolume, "-LerpVolume-");
	t_LerpVolume.detach();
}

void Audio::LerpPan(SndId _sndID, int direction, int _priority)
{
	SetPriorityTable(_sndID, _priority, PriorityTable::Status::PLAY);
	Snd* snd = SndManager::Find(_sndID);
	std::thread t_LerpPan(LerpPan_Main, snd, direction);
	Debug::SetName(t_LerpPan, "-LerpPan-");
	t_LerpPan.detach();
}

void Audio::StartTimer()
{
	Audio* pMan = Audio::privGetInstance();
	assert(pMan != nullptr);
	pMan->TimerQuitFlag = false;
	std::thread  t_Timer(Timer_Main, std::ref(pMan->TimerQuitFlag));

	Debug::SetName(t_Timer, "--Timer--");
	t_Timer.detach();
}

void Audio::StopTimer()
{
	Audio* pMan = Audio::privGetInstance();
	assert(pMan != nullptr);

	pMan->TimerQuitFlag = true;
	SndManager::SetTime(0);
}

//main priority
void Audio::Timer(Audio::AudioEvents _events, int _time, SndId _sndID, int _priority, float amt)
{
	CircularData* pTimerIn = QueueManager::GetTimerInQueue();
	TimerCmd* pCmd = new TimerCmd(_sndID, _events, _time, _priority, amt);
	pTimerIn->PushBack(pCmd);


}

//Regular
void Audio::Timer(Audio::AudioEvents _events, int _time, SndId _sndID, float amt)
{
	CircularData* pTimerIn = QueueManager::GetTimerInQueue();
	TimerCmd* pCmd = new TimerCmd(_sndID, _events, _time, amt);
	pTimerIn->PushBack(pCmd);
	

}

//for unload
void Audio::Timer(Audio::AudioEvents _events, int _time, Wave::ID _waveID)
{
	CircularData* pTimerIn = QueueManager::GetTimerInQueue();
	TimerCmd* pCmd = new TimerCmd(_waveID, _events, _time);
	pTimerIn->PushBack(pCmd);
}

//Wavetable dump
void Audio::Timer(Audio::AudioEvents _events, int _time)
{
	CircularData* pTimerIn = QueueManager::GetTimerInQueue();
	TimerCmd* pCmd = new TimerCmd( _events, _time);
	pTimerIn->PushBack(pCmd);
}

void Audio::RunEvent(SndId _sndID, Audio::AudioEvents _events, float amt, int _priority, Wave::ID _waveID)
{
	Snd* snd = SndManager::Find(_sndID);
	Audio* pAudio = Audio::privGetInstance();
	switch (_events)
	{
	case Audio::AudioEvents::PLAY:
		Debug::out("Audio - Snd Play\n");
		snd->Play();
		break;
	case Audio::AudioEvents::STOP:
		Debug::out("Audio - Snd Stop\n");
		snd->Stop();
		break;
	case Audio::AudioEvents::PAN:
		Debug::out("Audio - Snd Play\n");
		snd->Pan(amt);
		break;
	case Audio::AudioEvents::VOLUME:
		snd->AdjustVolume(amt);
		break;
	case Audio::AudioEvents::STOP_TIMER:
		Audio::StopTimer();
		break;
	case Audio::AudioEvents::UNLOAD:
		Debug::out("%s ----> Unloading\n", StringMe(_waveID));
		Audio::Unload(_waveID);
		break;
	case Audio::AudioEvents::WAVE_TABLE_DUMP:
		Audio::WaveTableDump();
		break;
	case Audio::AudioEvents::PRIORITY_PLAY:
		Audio::SetPriorityTable(_sndID, _priority, PriorityTable::Status::PLAY);
		break;
	case Audio::AudioEvents::PRIORITY_STOP:
		Audio::SetPriorityTable(_sndID, _priority, PriorityTable::Status::STOP);
		break;
	case Audio::AudioEvents::LERP_VOLUME:
		Audio::LerpVolume(_sndID, (int)amt, _priority);
		break;
	case Audio::AudioEvents::LERP_PAN:
		Audio::LerpPan(_sndID, (int)amt, _priority);
		break;
	case Audio::AudioEvents::PRIORITY_TABLE_DUMP:
		Audio::PriorityTableDump();
		break;
	case Audio::AudioEvents::UNLOAD_PRIORITY_TABLE:
		Audio::UnloadPriorityTable();
		break;
	case Audio::AudioEvents::UNLOAD_WAVE_TABLE:
		Audio::UnloadWaveTable();
		break;
	case Audio::AudioEvents::ELAPSED_TIME:
		pAudio->poPriorityTable->GetTime(_sndID);
		break;
	case Audio::AudioEvents::DEFAULT:
		break;
	default:	
		//fail
		return;
	}
	
}

//Priority
void Audio::UpdateTime()
{
	Audio* pMan = Audio::privGetInstance();
	PriorityTable* pPriorityTable = pMan->poPriorityTable;
	pPriorityTable->UpdateTime();
}

void Audio::SetPriorityTable(SndId _sndID, int _priority, PriorityTable::Status _status)
{
	Audio* pMan = Audio::privGetInstance();

	Snd* snd = SndManager::Find(_sndID);
	PriorityTable* pPriorityTable = pMan->poPriorityTable;
	pPriorityTable->Register(_sndID, snd->GetHandleID(), _priority, _status);
}

void Audio::RemovePriorityTable(SndId _sndID)
{
	Audio* pMan = Audio::privGetInstance();

	PriorityTable* pPriorityTable = pMan->poPriorityTable;
	pPriorityTable->Remove(_sndID);
}

void Audio::PriorityTableDump()
{
	Audio* pAudio = Audio::privGetInstance();
	pAudio->poPriorityTable->Dump();
}
