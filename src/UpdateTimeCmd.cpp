#include "UpdateTimeCmd.h"
#include "Audio.h"

UpdateTimeCmd::UpdateTimeCmd()
	: Command()
{

}

void UpdateTimeCmd::Execute()
{
	Audio::UpdateTime();

	delete this;
}


// --- End of File ---
