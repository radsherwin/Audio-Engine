#include "TimerCmd.h"

TimerCmd::TimerCmd(SndId _sndID, Audio::AudioEvents _events, int _audioTime, int _priority, float _amt)
	: Command(),
	sndID(_sndID),
	waveID(Wave::ID::Uninitialized),
	events(_events),
	audioTime(_audioTime),
	priority(_priority),
	amt(_amt)
{

}

TimerCmd::TimerCmd(SndId _sndID, Audio::AudioEvents _events, int _audioTime, float _amt)
	: Command(),
	sndID(_sndID),
	waveID(Wave::ID::Uninitialized),
	events(_events),
	audioTime(_audioTime),
	priority(INT_MAX),
	amt(_amt)
{

}

TimerCmd::TimerCmd(Wave::ID _waveID, Audio::AudioEvents _events, int _time)
	: Command(),
	sndID(SndId::Uninitialized),
	waveID(_waveID),
	events(_events),
	audioTime(_time),
	priority(INT_MAX),
	amt(0)
{
}

TimerCmd::TimerCmd(Audio::AudioEvents _events, int _time)
	: Command(),
	sndID(SndId::Uninitialized),
	waveID(Wave::ID::Uninitialized),
	events(_events),
	audioTime(_time),
	priority(INT_MAX),
	amt(0)
{
}

void TimerCmd::Execute()
{
	Audio::RunEvent(this->sndID, this->events, this->amt, this->priority, this->waveID);
	
	delete this;
}


// --- End of File ---
