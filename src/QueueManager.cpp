#include "QueueManager.h"

QueueManager* QueueManager::posInstance = nullptr;

using namespace ThreadFramework;

QueueManager::QueueManager()
{
	//Shared queues
	poAudioIn = new CircularData();
	assert(poAudioIn);

	poGameIn = new CircularData();
	assert(poGameIn);

	poFileIn = new CircularData();
	assert(poFileIn);

	poAuxIn = new CircularData();
	assert(poAuxIn);

	poAudioGameIn = new CircularData();
	assert(poAudioGameIn);

	poTimerIn = new CircularData();
	assert(poTimerIn);
}

QueueManager::~QueueManager()
{
	delete this->poAudioIn;
	this->poAudioIn = nullptr;

	delete this->poGameIn;
	this->poGameIn = nullptr;

	delete this->poFileIn;
	this->poFileIn = nullptr;

	delete this->poAuxIn;
	this->poAuxIn = nullptr;

	delete this->poAudioGameIn;
	this->poAudioGameIn = nullptr;

	delete this->poTimerIn;
	this->poTimerIn = nullptr;
}

void QueueManager::Destroy()
{
	QueueManager* pQueueManager = QueueManager::privGetInstance();
	assert(pQueueManager != nullptr);

	delete QueueManager::posInstance;
	QueueManager::posInstance = nullptr;
}

void QueueManager::Create()
{
	assert(posInstance == nullptr);

	if (posInstance == nullptr)
	{
		posInstance = new QueueManager();
	}
}

QueueManager* QueueManager::privGetInstance()
{
	assert(posInstance != nullptr);

	return posInstance;
}


bool QueueManager::SendAudio(Command* _pCmd)
{
	QueueManager* pMan = QueueManager::privGetInstance();
	Debug::out("-->Audio:  Command -> %x \n", _pCmd);
	bool status = pMan->poAudioIn->PushBack(_pCmd);

	return status;
}

bool QueueManager::SendGame(Command* _pCmd)
{
	QueueManager* pMan = QueueManager::privGetInstance();
	Debug::out("-->Game:  Command -> %x \n", _pCmd);
	bool status = pMan->poGameIn->PushBack(_pCmd);

	return status;
}

bool QueueManager::SendFile(Command* _pCmd)
{
	QueueManager* pMan = QueueManager::privGetInstance();
	Debug::out("-->File:  Command -> %x \n", _pCmd);
	bool status = pMan->poFileIn->PushBack(_pCmd);

	return status;
}

bool QueueManager::SendAux(Command* _pCmd)
{
	QueueManager* pMan = QueueManager::privGetInstance();
	Debug::out("-->Aux:  Command -> %x \n", _pCmd);
	bool status = pMan->poAuxIn->PushBack(_pCmd);

	return status;
}

bool QueueManager::SendAudioGame(Command* _pCmd)
{
	QueueManager* pMan = QueueManager::privGetInstance();
	Debug::out("-->AudioGame:  Command -> %x \n", _pCmd);
	bool status = pMan->poAudioGameIn->PushBack(_pCmd);

	return status;
}

bool QueueManager::SendTimer(Command* _pCmd)
{
	QueueManager* pMan = QueueManager::privGetInstance();
	Debug::out("-->Timer:  Command -> %x \n", _pCmd);
	bool status = pMan->poTimerIn->PushBack(_pCmd);

	return status;
}

//Get
CircularData* QueueManager::GetAudioInQueue()
{
	QueueManager* pMan = QueueManager::privGetInstance();
	return pMan->poAudioIn;
}

CircularData* QueueManager::GetGameInQueue()
{
	QueueManager* pMan = QueueManager::privGetInstance();
	return pMan->poGameIn;
}

CircularData* QueueManager::GetFileInQueue()
{
	QueueManager* pMan = QueueManager::privGetInstance();
	return pMan->poFileIn;
}

CircularData* QueueManager::GetAuxInQueue()
{
	QueueManager* pMan = QueueManager::privGetInstance();
	return pMan->poAuxIn;
}

CircularData* QueueManager::GetAudioGameInQueue()
{
	QueueManager* pMan = QueueManager::privGetInstance();
	return pMan->poAudioGameIn;
}

CircularData* QueueManager::GetTimerInQueue()
{
	QueueManager* pMan = QueueManager::privGetInstance();
	return pMan->poTimerIn;
}