#ifndef QUEUE_MANAGER_H
#define QUEUE_MANAGER_H

#include "CircularData.h"

class QueueManager
{
public:
	static void Create();
	static void Destroy();

	static bool SendAudio(Command* pCmd);
	static bool SendFile(Command* pCmd);
	static bool SendGame(Command* pCmd);
	static bool SendAux(Command* pCmd);
	static bool SendAudioGame(Command* pCmd);
	static bool SendTimer(Command* pCmd);

	static CircularData* GetGameInQueue();
	static CircularData* GetAudioInQueue();
	static CircularData* GetFileInQueue();
	static CircularData* GetAuxInQueue();
	static CircularData* GetAudioGameInQueue();
	static CircularData* GetTimerInQueue();

private:
	QueueManager();
	QueueManager(const QueueManager&) = delete;
	QueueManager& operator=(const QueueManager&) = delete;
	~QueueManager();

	static QueueManager* privGetInstance();
	static QueueManager* posInstance;

private:
	CircularData* poAudioIn;
	CircularData* poGameIn;
	CircularData* poFileIn;
	CircularData* poAuxIn;
	CircularData* poAudioGameIn;
	CircularData* poTimerIn;

};

#endif