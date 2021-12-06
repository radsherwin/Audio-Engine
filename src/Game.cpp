 //-----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "AzulCore.h"
#include "HandleMan.h"
#include "Game.h"
#include "GameApp.h"
#include "InputTest.h"
#include "AudioThread.h"
#include "GameTimer.h"
#include "CircularData.h"
#include "Snd.h"
#include "AzulTimer.h"

//Managers
#include "PlaylistManager.h"
#include "APlaylistManager.h"
#include "WaveManager.h"
#include "VoiceManager.h"
#include "SndManager.h"
#include "AudioEngine.h"
#include "QueueManager.h"
#include "Audio.h"
//Commands
#include "User_File_CB.h"

// Global varables just for the demo:
std::atomic_bool AudioReadyFlag = false;


using namespace ThreadFramework;

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Game::Initialize()
{ 
	// Game Window Device setup
	this->setWindowName("Audio Engine");
	this->setWidthHeight(400, 300);
	this->SetClearColor(0.74f, 0.74f, 0.86f, 1.0f);
}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Game::LoadContent()
{	
	//glDisable(GL_DEBUG_OUTPUT);

	// Load up the demo application
	GameApp::LoadDemo(this->getWidth(), this->getHeight());


	ThreadFramework::Debug::out("Load Content\n");

	//---------------------------------------------------------------------------------------------------------
	// Launch a Thread
	//---------------------------------------------------------------------------------------------------------
	Audio::Create();

}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Game::Update()
{
	GameApp::UpdateDemo();
	SndManager::Update();
	Audio::Update();

	// Read Quit Key
	Keyboard* key = Keyboard::GetInstance();
	if (key->GetKeyState(AZUL_KEY::KEY_Q))
	{
		Audio::Quit();
	}

	static bool key1_state = false;
	if (key->GetKeyState(AZUL_KEY::KEY_1) && !key1_state)
	{
		key1_state = true;

		Audio::Load(Audio::Blocking::LOAD, Wave::ID::Fiddle, "../Assets/Fiddle_mono.wav");
		Audio::Load(Audio::Blocking::LOAD, Wave::ID::Bassoon, "../Assets/Bassoon_mono.wav");
		Audio::Load(Audio::Blocking::LOAD, Wave::ID::Oboe, "../Assets/Oboe_mono.wav");
		Audio::Load(Audio::Blocking::LOAD, Wave::ID::SongA, "../Assets/SongA.wav");
		Audio::Load(Audio::Blocking::LOAD, Wave::ID::SongB, "../Assets/SongB.wav");

		//Playlist with no stitching
		//Audio::CreatePlaylist(PlaylistId::DEMO_1);

		Audio::CreateSnd(SndId::FIDDLE_ID, Wave::ID::Fiddle);
		Audio::CreateSnd(SndId::BASSOON_ID, Wave::ID::Bassoon);
		Audio::CreateSnd(SndId::OBOE2_ID, Wave::ID::Oboe);
		Audio::CreateSnd(SndId::SONGA_ID, Wave::ID::SongA);
		Audio::CreateSnd(SndId::SONGB_ID, Wave::ID::SongB);

		Audio::CreateSnd(SndId::BASSOON2_ID, Wave::ID::Bassoon);
		Audio::CreateSnd(SndId::BASSOON3_ID, Wave::ID::Bassoon);
		Audio::CreateSnd(SndId::BASSOON4_ID, Wave::ID::Bassoon);
		Audio::CreateSnd(SndId::BASSOON5_ID, Wave::ID::Bassoon);
		
		Audio::StartTimer();

		Audio::SetPriorityTable(SndId::FIDDLE_ID, 200,PriorityTable::Status::PLAY);

		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 3000, SndId::FIDDLE_ID, 200);
		Audio::Timer(Audio::AudioEvents::PAN, 3000, SndId::FIDDLE_ID, -1.0f);

		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 6000, SndId::FIDDLE_ID, 200);
		Audio::Timer(Audio::AudioEvents::PAN, 6000, SndId::FIDDLE_ID, 1.0f);

		Audio::Timer(Audio::AudioEvents::LERP_PAN, 10000, SndId::BASSOON_ID, 200, 1.0f);

		Audio::Timer(Audio::AudioEvents::LERP_PAN, 15000, SndId::BASSOON_ID, 200, 0.0f);

		Audio::Timer(Audio::AudioEvents::LERP_VOLUME, 20000, SndId::OBOE2_ID, 200, 1.0f);
		Audio::Timer(Audio::AudioEvents::LERP_VOLUME, 25000, SndId::OBOE2_ID, 200, 0.0f);

		Audio::Timer(Audio::AudioEvents::PAN, 30000, SndId::SONGA_ID, -1.0f);
		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 30000, SndId::SONGA_ID, 200);

		Audio::Timer(Audio::AudioEvents::PAN, 30000, SndId::SONGB_ID, 1.0f);
		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 30000, SndId::SONGB_ID, 200);

		Audio::Timer(Audio::AudioEvents::ELAPSED_TIME, 35000, SndId::SONGA_ID);
		Audio::Timer(Audio::AudioEvents::ELAPSED_TIME, 38000, SndId::SONGA_ID);

		Audio::Timer(Audio::AudioEvents::ELAPSED_TIME, 60000, SndId::SONGA_ID);
		Audio::Timer(Audio::AudioEvents::PRIORITY_STOP, 60000, SndId::SONGA_ID, 100);

		Audio::Timer(Audio::AudioEvents::ELAPSED_TIME, 72000, SndId::SONGB_ID);
		Audio::Timer(Audio::AudioEvents::PRIORITY_STOP, 72000, SndId::SONGB_ID, 100);

		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 80000, SndId::BASSOON2_ID, 200);
		Audio::Timer(Audio::AudioEvents::PRIORITY_TABLE_DUMP, 80000);
		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 80500, SndId::BASSOON3_ID, 200);

		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 81000, SndId::BASSOON4_ID, 200);

		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 81500, SndId::BASSOON5_ID, 200);

		
	}

	static bool key2_state = false;
	if (key->GetKeyState(AZUL_KEY::KEY_2) && !key2_state)
	{
		key2_state = true;
		//reset timer
		Audio::UnloadPriorityTable();
		Audio::UnloadWaveTable();
		//Audio::SoftDestroy();
		Audio::StopTimer();
		//Audio::ClearQueue();

		Audio::Load(Audio::Blocking::LOAD, Wave::ID::Intro, "../Assets/Intro_mono.wav");
		Audio::Load(Audio::Blocking::LOAD, Wave::ID::A, "../Assets/A_mono.wav");
		Audio::Load(Audio::Blocking::LOAD, Wave::ID::AtoB, "../Assets/AtoB_mono.wav");
		Audio::Load(Audio::Blocking::LOAD, Wave::ID::B, "../Assets/B_mono.wav");
		Audio::Load(Audio::Blocking::LOAD, Wave::ID::BtoC, "../Assets/BtoC_mono.wav");
		Audio::Load(Audio::Blocking::LOAD, Wave::ID::C, "../Assets/C_mono.wav");
		Audio::Load(Audio::Blocking::LOAD, Wave::ID::CtoA, "../Assets/CtoA_mono.wav");
		Audio::Load(Audio::Blocking::LOAD, Wave::ID::End, "../Assets/End_mono.wav");

		//Audio::CreatePlaylist(SndId::INTRO_ID);
		//Audio::AddToPlaylist(SndId::INTRO_ID, Wave::ID::A);

		Audio::CreatePlaylist(SndId::INTRO_ID, Wave::ID::Intro);
		Audio::StitchPlaylist(SndId::INTRO_ID, Wave::ID::A);
		Audio::StitchPlaylist(SndId::INTRO_ID, Wave::ID::AtoB);
		Audio::StitchPlaylist(SndId::INTRO_ID, Wave::ID::B);
		Audio::StitchPlaylist(SndId::INTRO_ID, Wave::ID::BtoC);
		Audio::StitchPlaylist(SndId::INTRO_ID, Wave::ID::C);
		Audio::StitchPlaylist(SndId::INTRO_ID, Wave::ID::CtoA);
		Audio::StitchPlaylist(SndId::INTRO_ID, Wave::ID::End);
		Audio::StartTimer();
		//Audio::Play(SndId::INTRO_ID);
		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 0, SndId::INTRO_ID, 200);

		Audio::Timer(Audio::AudioEvents::PAN, 10000, SndId::INTRO_ID, 1.0f);
		Audio::Timer(Audio::AudioEvents::PAN, 20000, SndId::INTRO_ID, -1.0f);
		Audio::Timer(Audio::AudioEvents::PAN, 30000, SndId::INTRO_ID, 0.0f);
		Audio::Timer(Audio::AudioEvents::PAN, 40000, SndId::INTRO_ID, 1.0f);
		Audio::Timer(Audio::AudioEvents::PAN, 50000, SndId::INTRO_ID, -1.0f);
		/*Audio::Timer(Audio::AudioEvents::PAN, 60000, SndId::INTRO_ID, 0.0f);
		Audio::Timer(Audio::AudioEvents::PAN, 70000, SndId::INTRO_ID, 1.0f);
		Audio::Timer(Audio::AudioEvents::PAN, 80000, SndId::INTRO_ID, -1.0f);
		Audio::Timer(Audio::AudioEvents::PAN, 90000, SndId::INTRO_ID, 0.0f);*/
		
	}

	static bool key3_state = false;
	if (key->GetKeyState(AZUL_KEY::KEY_3) && !key3_state)
	{
		key3_state = true;
		//reset timer
		Audio::UnloadPriorityTable();
		Audio::UnloadWaveTable();
		Audio::StopTimer();
		//Audio::ClearQueue();

		Audio::Load(Audio::Blocking::LOAD, Wave::ID::Coma, "../Assets/Coma_mono.wav");

		Audio::CreateSnd(SndId::SND_A, Wave::ID::Coma);
		Audio::CreateSnd(SndId::SND_B, Wave::ID::Coma);
		Audio::CreateSnd(SndId::SND_C, Wave::ID::Coma);
		Audio::CreateSnd(SndId::SND_D, Wave::ID::Coma);
		Audio::CreateSnd(SndId::SND_E, Wave::ID::Coma);
		Audio::CreateSnd(SndId::SND_F, Wave::ID::Coma);
		Audio::CreateSnd(SndId::SND_G, Wave::ID::Coma);
		Audio::CreateSnd(SndId::SND_HH, Wave::ID::Coma);
		Audio::CreateSnd(SndId::SND_I, Wave::ID::Coma);
		Audio::CreateSnd(SndId::SND_J, Wave::ID::Coma);
		Audio::CreateSnd(SndId::SND_K, Wave::ID::Coma);

		Audio::StartTimer();

		Audio::SetPriorityTable(SndId::SND_A, 10,PriorityTable::Status::PLAY);
		Audio::SetPriorityTable(SndId::SND_B, 50, PriorityTable::Status::PLAY);
		Audio::SetPriorityTable(SndId::SND_C, 150, PriorityTable::Status::PLAY);

		Audio::PriorityTableDump();


		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 1000, SndId::SND_D, 50);
		Audio::Timer(Audio::AudioEvents::PRIORITY_TABLE_DUMP, 1000);

		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 2000, SndId::SND_E, 75);
		Audio::Timer(Audio::AudioEvents::PRIORITY_TABLE_DUMP, 2000);

		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 3000, SndId::SND_F, 100);
		Audio::Timer(Audio::AudioEvents::PRIORITY_TABLE_DUMP, 3000);

		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 4000, SndId::SND_G, 150);
		Audio::Timer(Audio::AudioEvents::PRIORITY_TABLE_DUMP, 4000);

		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 5000, SndId::SND_HH, 75);
		Audio::Timer(Audio::AudioEvents::PRIORITY_TABLE_DUMP, 5000);

		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 6000, SndId::SND_I, 75);
		Audio::Timer(Audio::AudioEvents::PRIORITY_TABLE_DUMP, 6000);

		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 7000, SndId::SND_J, 75);
		Audio::Timer(Audio::AudioEvents::PRIORITY_TABLE_DUMP, 7000);

		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 8000, SndId::SND_K, 150);
		Audio::Timer(Audio::AudioEvents::PRIORITY_TABLE_DUMP, 8000);

		Audio::Timer(Audio::AudioEvents::PRIORITY_TABLE_DUMP, 13000);
		Audio::Timer(Audio::AudioEvents::UNLOAD_PRIORITY_TABLE, 13000);
		Audio::Timer(Audio::AudioEvents::PRIORITY_TABLE_DUMP, 13000);

	}

	static bool key4_state = false;
	if (key->GetKeyState(AZUL_KEY::KEY_4) && !key4_state)
	{
		key4_state = true;
		//reset timer
		Audio::UnloadPriorityTable();
		Audio::UnloadWaveTable();
		Audio::StopTimer();

		Audio::Load(Audio::Blocking::LOAD, Wave::ID::Dial, "../Assets/Dial_mono.wav");
		Audio::Load(Audio::Blocking::LOAD, Wave::ID::MoonPatrol, "../Assets/MoonPatrol_mono.wav");
		Audio::Load(Audio::Blocking::LOAD, Wave::ID::Sequence, "../Assets/Sequence1_mono.wav");
		Audio::Load(Audio::Blocking::LOAD, Wave::ID::Donkey, "../Assets/Donkey_mono.wav");

		User_File_CB* pUserDIAL_CB = new User_File_CB(SndId::DIAL_ID, Wave::ID::Dial, true);
		User_File_CB* pUserMOONPATROL_CB = new User_File_CB(SndId::MOON_PATROL_ID, Wave::ID::MoonPatrol, true);
		User_File_CB* pUserSEQUENCE_CB = new User_File_CB(SndId::SEQUENCE_ID, Wave::ID::Sequence, true);
		User_File_CB* pUserDONKEY_CB = new User_File_CB(SndId::DONKEY_ID, Wave::ID::Donkey, true);

		Audio::CreateSnd(SndId::DIAL_ID, Wave::ID::Dial, pUserDIAL_CB);
		Audio::CreateSnd(SndId::MOON_PATROL_ID, Wave::ID::MoonPatrol, pUserMOONPATROL_CB);
		Audio::CreateSnd(SndId::SEQUENCE_ID, Wave::ID::Sequence, pUserSEQUENCE_CB);
		Audio::CreateSnd(SndId::DONKEY_ID, Wave::ID::Donkey, pUserDONKEY_CB);
		
		Audio::StartTimer();
		Audio::Pan(SndId::DIAL_ID, -1.0f);
		Audio::Pan(SndId::MOON_PATROL_ID, 1.0f);
		Audio::Pan(SndId::SEQUENCE_ID, -1.0f);
		Audio::Pan(SndId::DONKEY_ID, 1.0f);
		Audio::SetPriorityTable(SndId::DIAL_ID, 200, PriorityTable::Status::PLAY);
		Audio::SetPriorityTable(SndId::MOON_PATROL_ID, 200, PriorityTable::Status::PLAY);
		Audio::SetPriorityTable(SndId::SEQUENCE_ID, 200, PriorityTable::Status::PLAY);

		Audio::Timer(Audio::AudioEvents::PRIORITY_PLAY, 3500, SndId::DONKEY_ID, 200);

	}

	static bool key5_state = false;
	if (key->GetKeyState(AZUL_KEY::KEY_5) && !key5_state)
	{
		key5_state = true;
		//reset timer
		Audio::UnloadPriorityTable();
		Audio::UnloadWaveTable();
		Audio::StopTimer();

		User_File_CB* userCB = Audio::CreateCB(SndId::BEETHOVEN_ID, Wave::ID::Beethoven);

		Audio::Load(Audio::Blocking::LOAD, Wave::ID::Electro, "../Assets/Electro_mono.wav");
		Audio::Load(Audio::Blocking::LOAD, Wave::ID::Alarm, "../Assets/Alert_mono.wav");
		Audio::Load(Audio::Async::LOAD, Wave::ID::Beethoven, "../Assets/Beethoven_stereo.wav", userCB);

		Audio::CreateSnd(SndId::ELECTRO_ID, Wave::ID::Electro);
		Audio::CreateSnd(SndId::ALARM_ID, Wave::ID::Alarm); //also loads playlist BTS

		Audio::WaveTableDump();

		Audio::Play(SndId::ELECTRO_ID);
		Audio::Pan(SndId::ELECTRO_ID, 1.0f);
		Audio::Volume(SndId::ELECTRO_ID, 0.1f);

		Audio::Play(SndId::ALARM_ID);
		Audio::Pan(SndId::ALARM_ID, -1.0f);
		Audio::Volume(SndId::ALARM_ID, 0.1f);

		Audio::StartTimer();

		Audio::Timer(Audio::AudioEvents::PAN, 5000, SndId::ALARM_ID, -1.0f);
		Audio::Timer(Audio::AudioEvents::PLAY, 5000, SndId::ALARM_ID);

		Audio::Timer(Audio::AudioEvents::PAN, 10000, SndId::ALARM_ID, -1.0f);
		Audio::Timer(Audio::AudioEvents::PLAY, 10000, SndId::ALARM_ID);

		Audio::Timer(Audio::AudioEvents::PAN, 15000, SndId::ALARM_ID, -1.0f);
		Audio::Timer(Audio::AudioEvents::PLAY, 15000, SndId::ALARM_ID);

		Audio::Timer(Audio::AudioEvents::PAN, 20000, SndId::ALARM_ID, -1.0f);
		Audio::Timer(Audio::AudioEvents::PLAY, 20000, SndId::ALARM_ID);

		Audio::Timer(Audio::AudioEvents::PAN, 25000, SndId::ALARM_ID, -1.0f);
		Audio::Timer(Audio::AudioEvents::PLAY, 25000, SndId::ALARM_ID);

		Audio::Timer(Audio::AudioEvents::STOP, 60000, SndId::BEETHOVEN_ID);

		Audio::Timer(Audio::AudioEvents::WAVE_TABLE_DUMP, 60000);
		Audio::Timer(Audio::AudioEvents::UNLOAD_WAVE_TABLE, 60000);
		Audio::Timer(Audio::AudioEvents::WAVE_TABLE_DUMP, 60000);

		Audio::Timer(Audio::AudioEvents::STOP_TIMER, 60000 );
	}
}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Game::Draw()
{
	// Draw the demo application
	GameApp::DrawDemo();

}



//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Game::UnLoadContent()
{
	SndManager::Destroy();
	HandleMan::Destroy();
	Audio::Destroy();
	QueueManager::Destroy();

	//std::terminate();
}


//---  End of File ---
