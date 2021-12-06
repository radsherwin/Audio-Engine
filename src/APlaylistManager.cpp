//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "APlaylistManager.h"
#include "SndManager.h"

using namespace ThreadFramework;

APlaylistManager* APlaylistManager::posInstance = nullptr;

//----------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------
APlaylistManager::APlaylistManager(int reserveNum, int reserveGrow)
    : ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
{
    // Preload the reserve
    this->proFillReservedPool(reserveNum);

    // initialize derived data here
    this->poNodeCompare = new Playlist();
}

APlaylistManager::~APlaylistManager()
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
void APlaylistManager::Create(int reserveNum, int reserveGrow)
{
    // make sure values are ressonable 
    assert(reserveNum > 0);
    assert(reserveGrow > 0);

    // initialize the singleton here
    assert(posInstance == nullptr);

    // Do the initialization
    if (posInstance == nullptr)
    {
        posInstance = new APlaylistManager(reserveNum, reserveGrow);
    }

}

void APlaylistManager::Destroy()
{
    APlaylistManager* pMan = APlaylistManager::privGetInstance();
    assert(pMan != nullptr);

    delete APlaylistManager::posInstance;
    APlaylistManager::posInstance = nullptr;
}

Playlist* APlaylistManager::Add(SndId _sndID, Wave::ID _waveID, User_File_CB* _pUserCB)
{
    APlaylistManager* pMan = APlaylistManager::privGetInstance();

    Playlist* pNode = (Playlist*)pMan->baseAddToFront();
    assert(pNode != nullptr);

    // Initialize the date
    pNode->Set(_sndID, _waveID, nullptr, _pUserCB);

    return pNode;
}

Playlist* APlaylistManager::Find(SndId _sndID)
{
    APlaylistManager* pMan = APlaylistManager::privGetInstance();
    assert(pMan != nullptr);

    // Compare functions only compares two Nodes

    // So:  Use the Compare Node - as a reference
    //      use in the Compare() function
    pMan->poNodeCompare->sndID = _sndID;

    Playlist* pData = (Playlist*)pMan->baseFind(pMan->poNodeCompare);
    return pData;
}

void APlaylistManager::Remove(Playlist* pNode)
{
    assert(pNode != nullptr);

    APlaylistManager* pMan = APlaylistManager::privGetInstance();
    assert(pMan != nullptr);

    pMan->baseRemove(pNode);
}

void APlaylistManager::Dump()
{
    APlaylistManager* pMan = APlaylistManager::privGetInstance();
    assert(pMan != nullptr);

    pMan->baseDump();
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
APlaylistManager* APlaylistManager::privGetInstance()
{
    // Safety - this forces users to call Create() first before using class
    assert(posInstance != nullptr);

    return posInstance;
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* APlaylistManager::derivedCreateNode()
{
    DLink* pNodeBase = new Playlist();
    assert(pNodeBase != nullptr);

    return pNodeBase;
}

