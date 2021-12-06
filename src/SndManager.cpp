#include "SndManager.h"
#include "SndStartCmd.h"
#include "WaveManager.h"
#include "APlaylistManager.h"
#include "StringThis.h"
#include "QueueManager.h"


using namespace ThreadFramework;

SndManager* SndManager::posInstance = nullptr;

SndManager::SndManager(int reserveNum, int reserveGrow)
	: ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
{
	// Preload the reserve
	this->proFillReservedPool(reserveNum);

	// initialize derived data here
	this->poNodeCompare = new Snd();
	
}

SndManager::~SndManager()
{
	Debug::out("~SndManager()\n");
	delete this->poNodeCompare;
	this->poNodeCompare = nullptr;

	// iterate through the list and delete
	Iterator* pIt = this->baseGetActiveIterator();

	DLink* pNode = pIt->First();

	// Walk through the nodes
	while (!pIt->IsDone())
	{
		Snd* pDeleteMe = (Snd*)pIt->Curr();
		pNode = pIt->Next();
		delete pDeleteMe;
	}

	pIt = this->baseGetReserveIterator();

	pNode = pIt->First();

	// Walk through the nodes
	while (!pIt->IsDone())
	{
		Snd* pDeleteMe = (Snd*)pIt->Curr();
		pNode = pIt->Next();
		delete pDeleteMe;
	}
}

void SndManager::Create(int reserveNum, int reserveGrow)
{
	Debug::out("SndManager::Create()");
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(posInstance == nullptr);

	// Do the initialization
	if (posInstance == nullptr)
	{
		posInstance = new SndManager(reserveNum, reserveGrow);
	}

}

void SndManager::Destroy()
{

	Debug::out("SndManager::Destroy()\n");
	SndManager* pMan = SndManager::privGetInstance();
	assert(pMan != nullptr);

	delete SndManager::posInstance;
	SndManager::posInstance = nullptr;
}

Snd* SndManager::Add(SndId _sndID, Wave::ID _waveID)
{
	//Create playlist from here. 

	SndManager* pMan = SndManager::privGetInstance();
	//Pass in Voice. Set compare to voice. 
	// Find the wave from the manager

	//

	Snd* newSnd = (Snd*)pMan->baseAddToFront();
	assert(newSnd != nullptr);
	// Initialize the date
	newSnd->Set(_sndID, _waveID);


	
	return newSnd;
}
//At this point Snd, ASnd, Playlist, and Voice should exist
void SndManager::Stitch(SndId _sndID, SndId _nextID)
{
	//might need a check to see if it's loaded?
	//add some fool proof regarding "homevoice"
	Snd* curSnd = SndManager::Find(_sndID);
	//Snd* nextSnd = SndManager::Find(_nextID);
	
	curSnd->SetNextID(_nextID);


	//Find sound,
	//If it doesn't exist...SndManager::Add WITHOUT the playlist creation
	//Pass in "original" sndID aka "seinfeld"



}

/*SndManager::Stitch(SndId _sndID, SndId _nextID, bool _homeVoice)
* 
* Snd* snd = SndManager::Find(_sndID)
* Snd* snd2 = SndManager::Find(_nextID)
* 
* SndHomeVoice* pCmd = new SndHomeVoice(_sndID, _homeVoice);
* QueueManager::SendAudio(pCmd);
* pCmd = new SndHomeVoice(_nextID, false);
* QueueManager::SendAudio(pCmd);
* 
* SndStitchCmd* pCmd = new SndStitchCmd(snd, snd2);
*/


void SndManager::SetTime(int _time)
{
	SndManager* pMan = SndManager::privGetInstance();
	pMan->time = _time;
}

int SndManager::GetTime()
{
	SndManager* pMan = SndManager::privGetInstance();
	
	return pMan->time;
}

void SndManager::Update()
{
	CircularData* pGameIn = QueueManager::GetGameInQueue();
	//Aux should send to this
	Command* cTmp = nullptr;
	if (pGameIn->PopFront(cTmp) == true)
	{
		cTmp->Execute();
	}
}


//Overload methods
Snd* SndManager::Find(SndId _sndID)
{
	SndManager* pMan = SndManager::privGetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->SetSndID(_sndID);

	Snd* pData = (Snd*)pMan->baseFind(pMan->poNodeCompare);
	return pData;
}

void SndManager::Remove(Snd* pNode)
{
	assert(pNode != nullptr);

	SndManager* pMan = SndManager::privGetInstance();
	assert(pMan != nullptr);

	pMan->baseRemove(pNode);
}

void SndManager::Dump()
{
	SndManager* pMan = SndManager::privGetInstance();
	assert(pMan != nullptr);

	pMan->baseDump();
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
SndManager* SndManager::privGetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(posInstance != nullptr);

	return posInstance;
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* SndManager::derivedCreateNode()
{
	DLink* pNodeBase = new Snd();
	assert(pNodeBase != nullptr);

	return pNodeBase;
}
