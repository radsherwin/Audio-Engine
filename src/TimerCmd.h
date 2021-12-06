//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef TIMER_COMMAND_H
#define TIMER_COMMAND_H

#include "Command.h"
#include "SndCallRegistry.h"
#include "Audio.h"
#include "Wave.h"

class TimerCmd : public Command
{

public:
	// Big 4
	TimerCmd() = default;
	TimerCmd(const TimerCmd&) = default;
	TimerCmd& operator = (const TimerCmd&) = default;
	virtual ~TimerCmd() = default;

	TimerCmd(SndId _sndID, Audio::AudioEvents _events, int _audioTime, int _priority, float _amt);
	TimerCmd(SndId _sndID, Audio::AudioEvents _events, int _audioTime, float _amt);
	TimerCmd(Wave::ID _waveID, Audio::AudioEvents _events, int _time);
	TimerCmd(Audio::AudioEvents _events, int _time);

	virtual void Execute() override;
	void Destroy();

public:
	// Data
	SndId sndID;
	Wave::ID waveID;
	Audio::AudioEvents events;
	int audioTime;
	int priority;
	float amt;

};

#endif

// --- End of File ---
