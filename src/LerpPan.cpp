//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AzulTimer.h"
#include "LerpPan.h"

using namespace ThreadFramework;
// cool way to deal with time...
using namespace std::chrono_literals;

float Lerp(float A, float B, float t)
{
	float tmp;
	tmp = A + t * (B - A);
	return tmp;
}

void UpdatePan(float pan, float& left, float& right)
{
	left = 0.5f - pan * 0.5f;
	right = 0.5f + pan * 0.5f;
}

void LerpPan_Main(Snd* sndToLerp, int direction)
{
	SimpleBanner b;

	Debug::out("- PANNING - \n");

	float leftPan = 0.0f;
	float rightPan = 0.0f;

	if (direction == 0) {
		leftPan = -1.0f;
		rightPan = 1.0f;
	}
	else {
		leftPan = 1.0f;
		rightPan = -1.0f;
	}

	float pan(0.0f);
	float left(0.0f);
	float right(0.0f);
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

		pan = Lerp(leftPan, rightPan, ratio);
		UpdatePan(pan, left, right);
		sndToLerp->Pan(pan);
		Debug::out("l: %0.2f  r: %0.2f\n", left, right);

		std::this_thread::sleep_for(10ms);

		// subtract time passed
		TimeElapsed += tA.toc();
	}
}



// End of File 