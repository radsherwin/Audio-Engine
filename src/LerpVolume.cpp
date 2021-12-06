//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AzulTimer.h"
#include "LerpVolume.h"
#include "Audio.h"
#include "QueueManager.h"
#include "GetCurrentVolumeCmd.h"

using namespace ThreadFramework;
// cool way to deal with time...
using namespace std::chrono_literals;

float LerpVolume(float A, float B, float t)
{
	float tmp;
	tmp = A + t * (B - A);
	return tmp;
}

void LerpVolume_Main(Snd* sndToLerp, int direction)
{
	SimpleBanner b;

	Debug::out("- VOLUME ADJUSTING - \n");
	bool DoneFlag = false;
	I_File_CB* pFileCB = new I_File_CB(DoneFlag);

	GetCurrentVolumeCmd* pCmd = new GetCurrentVolumeCmd(sndToLerp, pFileCB);
	QueueManager::SendAudio(pCmd);
	//while (!DoneFlag); //wat till we get the current volume

	//Send command to Audio to get currentVolume

	float start = sndToLerp->currentVolume;
	float end = 0.0f;

	if (direction == 0) { //increase volume
		start = 0.0f;
		end = 1.0f;
	}
	else { //decrease volume
		start = 1.0f;
		end = 0.0f;
	}

	sndToLerp->AdjustVolume(start);

	float amt(0.0f);
	//	float time(0.0f);
		//float delta_time = 1.0f / 2000.0f;

	Time TimeTotal = Time(Duration::TIME_ONE_SECOND) * 2;
	Time TimeElapsed(Duration::TIME_ZERO);

	float tElapsed = (float)Time::quotient(TimeElapsed, Time(Duration::TIME_ONE_MILLISECOND));
	float tTotal = (float)Time::quotient(TimeTotal, Time(Duration::TIME_ONE_MILLISECOND));
	float ratio = 0.0f;

	Timer tA;

	while (TimeElapsed <= TimeTotal)
	{
		tA.tic();

		tElapsed = (float)Time::quotient(TimeElapsed, Time(Duration::TIME_ONE_MILLISECOND));
		ratio = tElapsed / tTotal;

		//Everytime adjustvolume is called, the game sends GetVolume back to the gameInqueue


		//Debug::out("VOLUME GET %d\n", sndToLerp->GetVolume());
		amt = LerpVolume(end, start, ratio);
		sndToLerp->AdjustVolume(amt);
		Debug::out("amt  %0.2f\n", amt);

		std::this_thread::sleep_for(10ms);

		// subtract time passed
		TimeElapsed += tA.toc();
	}
}



// End of File 