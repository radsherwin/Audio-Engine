#include "FileThread.h"
#include "QueueManager.h"
#include "Command.h"

using namespace ThreadFramework;

void FileMain(std::atomic_bool& QuitFlag)
{
	SimpleBanner b;

	CircularData* pFileIn = QueueManager::GetFileInQueue();

	while (!QuitFlag)
	{
		Command* pCmd;

		if (pFileIn->PopFront(pCmd) == true)
		{
			assert(pCmd);
			pCmd->Execute();
		}
	}
}