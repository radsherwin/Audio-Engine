#include "TimerEventCmd.h"

TimerEventCmd::TimerEventCmd(float _amt)
	: Command(),
	timeAmount(_amt)
{

}


void TimerEventCmd::Execute()
{

	delete this;
}

float TimerEventCmd::TimeAmount()
{
	return this->timeAmount;
}


// --- End of File ---
