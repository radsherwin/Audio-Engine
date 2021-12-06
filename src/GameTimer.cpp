#include "GameTimer.h"
#include "AzulTimer.h"
#include "AzulCore.h"

#include "QueueManager.h"
#include "TimerCmd.h"
#include "UpdateTimeCmd.h"
#include "CircularData.h"

using namespace ThreadFramework;

void Timer_Main(std::atomic_bool& QuitFlag)
{
	SimpleBanner b;
	Timer T1;
	T1.tic();

	Time deltaTime;
	bool flag(true);

	CircularData* pAudioGameIn = QueueManager::GetAudioGameInQueue();
	CircularData* pGameIn = QueueManager::GetGameInQueue();
	CircularData* pTimerIn = QueueManager::GetTimerInQueue();
	Command* pCmd;

	while (!QuitFlag)
	{
		int time = Time::quotient(deltaTime, Time(TIME_ONE_MILLISECOND));
		if (flag)
		{
			Debug::out("Time: %d\n", time);

			while (pTimerIn->PeekFront(pCmd) == true)
			{
				if (fabs(((TimerCmd*)pCmd)->audioTime-time) <=500)
				{
					pTimerIn->PopFront(pCmd);
					pAudioGameIn->PushBack(pCmd);
				}
				else break;
			}

			UpdateTimeCmd* updateCmd = new UpdateTimeCmd();
			pGameIn->PushBack(updateCmd);
			
		}

		deltaTime = T1.toc();
		
		Time scrap = Time::remainder(deltaTime, (Time(TIME_ONE_MILLISECOND)*500));
		if (scrap == Time(TIME_ZERO))
		{
			flag = true;
		}
		else
		{
			flag = false;
		}
	}
	
}

