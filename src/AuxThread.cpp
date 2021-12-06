#include "AuxThread.h"
#include "QueueManager.h"
#include "Command.h"

using namespace ThreadFramework;

void AuxMain(std::atomic_bool& QuitFlag)
{
	SimpleBanner b;

	CircularData* pAuxIn = QueueManager::GetAuxInQueue();

	while (!QuitFlag)
	{
		Command* pCmd;

		if (pAuxIn->PopFront(pCmd) == true)
		{
			assert(pCmd);
			pCmd->Execute();
		}
	}
}