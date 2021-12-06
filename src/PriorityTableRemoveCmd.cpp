#include "PriorityTableRemoveCmd.h"
#include "Audio.h"

PriorityTableRemoveCmd::PriorityTableRemoveCmd(SndId _sndID)
	: Command(),
	sndID(_sndID)
{

}


void PriorityTableRemoveCmd::Execute()
{
	Audio::RemovePriorityTable(sndID);

	delete this;
}


// --- End of File ---
