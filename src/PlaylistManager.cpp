//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "PlaylistManager.h"
#include "PlaylistLoadCmd.h"
#include "PlaylistStitchCmd.h"
#include "SndManager.h"
#include "QueueManager.h"

using namespace ThreadFramework;

PlaylistManager* PlaylistManager::posInstance = nullptr;

//----------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------
PlaylistManager::PlaylistManager(int reserveNum, int reserveGrow)
    : ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
{
    // Preload the reserve
    this->proFillReservedPool(reserveNum); 

    // initialize derived data here
    this->poNodeCompare = new Playlist();
}

PlaylistManager::~PlaylistManager()
{
    // Debug::out("~Playlist()\n");
    delete this->poNodeCompare;
    this->poNodeCompare = nullptr;

    // iterate through the list and delete
    Iterator* pIt = this->baseGetActiveIterator();

    DLink* pNode = pIt->First();

    // Walk through the nodes
    while (!pIt->IsDone())
    {
        Playlist* pDeleteMe = (Playlist*)pIt->Curr();
        pNode = pIt->Next();
        delete pDeleteMe;
    }

    pIt = this->baseGetReserveIterator();

    pNode = pIt->First();

    // Walk through the nodes
    while (!pIt->IsDone())
    {
        Playlist* pDeleteMe = (Playlist*)pIt->Curr();
        pNode = pIt->Next();
        delete pDeleteMe;
    }
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void PlaylistManager::Create(int reserveNum, int reserveGrow)
{
    // make sure values are ressonable 
    assert(reserveNum > 0);
    assert(reserveGrow > 0);

    // initialize the singleton here
    assert(posInstance == nullptr);

    // Do the initialization
    if (posInstance == nullptr)
    {
        posInstance = new PlaylistManager(reserveNum, reserveGrow);
    }

}

void PlaylistManager::Destroy()
{
    PlaylistManager* pMan = PlaylistManager::privGetInstance();
    assert(pMan != nullptr);

    delete PlaylistManager::posInstance;
    PlaylistManager::posInstance = nullptr;
}

void PlaylistManager::Load(SndId _sndID, Wave::ID _waveID, User_File_CB* _pUserCB)
{
    PlaylistLoadCmd* pCmd = new PlaylistLoadCmd(_sndID, _waveID, _pUserCB);
    assert(pCmd);

    QueueManager::SendAudio(pCmd);
}

void PlaylistManager::Stitch(SndId _sndID, Wave::ID _waveID)
{
    PlaylistStitchCmd* pCmd = new PlaylistStitchCmd(_sndID, _waveID);
    assert(pCmd);

    QueueManager::SendAudio(pCmd);
}

//Playlist* PlaylistManager::Add(SndId _sndID, Wave::ID _waveID, Voice* _pHeadVoice)
//{
//    PlaylistManager* pMan = PlaylistManager::privGetInstance();
//
//    Playlist* pNode = (Playlist*)pMan->baseAddToFront();
//    assert(pNode != nullptr);
//
//    // Initialize the date
//    pNode->Set(_sndID, _waveID, _pHeadVoice);
//
//    return pNode;
//}

Playlist* PlaylistManager::Add(SndId _sndID, Wave::ID _waveID, User_File_CB* _pUserCB)
{
    PlaylistManager* pMan = PlaylistManager::privGetInstance();

    Playlist* pNode = (Playlist*)pMan->baseAddToFront();
    assert(pNode != nullptr);

    // Initialize the date
    pNode->Set(_sndID, _waveID, nullptr, _pUserCB);

    return pNode;
}

Playlist* PlaylistManager::Find(SndId _sndID)
{
    PlaylistManager* pMan = PlaylistManager::privGetInstance();
    assert(pMan != nullptr);

    // Compare functions only compares two Nodes

    // So:  Use the Compare Node - as a reference
    //      use in the Compare() function
    pMan->poNodeCompare->sndID = _sndID;

    Playlist* pData = (Playlist*)pMan->baseFind(pMan->poNodeCompare);
    return pData;
}

void PlaylistManager::Remove(Playlist* pNode)
{
    assert(pNode != nullptr);

    PlaylistManager* pMan = PlaylistManager::privGetInstance();
    assert(pMan != nullptr);

    pMan->baseRemove(pNode);
}

void PlaylistManager::Dump()
{
    PlaylistManager* pMan = PlaylistManager::privGetInstance();
    assert(pMan != nullptr);

    pMan->baseDump();
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
PlaylistManager* PlaylistManager::privGetInstance()
{
    // Safety - this forces users to call Create() first before using class
    assert(posInstance != nullptr);

    return posInstance;
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* PlaylistManager::derivedCreateNode()
{
    DLink* pNodeBase = new Playlist();
    assert(pNodeBase != nullptr);

    return pNodeBase;
}

