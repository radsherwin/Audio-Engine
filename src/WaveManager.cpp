//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "WaveManager.h"
#include "WaveTable.h"
#include "Audio.h"
#include "QueueManager.h"

#include "FileLoadCmd.h"
using namespace ThreadFramework;

WaveManager* WaveManager::posInstance = nullptr;

//----------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------
WaveManager::WaveManager(int reserveNum, int reserveGrow)
    : ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
{
    // Preload the reserve
    this->proFillReservedPool(reserveNum);

    // initialize derived data here
    this->poNodeCompare = new Wave();
}

WaveManager::~WaveManager()
{
    Debug::out("~WaveManager()\n");
    delete this->poNodeCompare;
    this->poNodeCompare = nullptr;

    // iterate through the list and delete
    Iterator* pIt = this->baseGetActiveIterator();

    DLink* pNode = pIt->First();

    // Walk through the nodes
    while (!pIt->IsDone())
    {
        Wave* pDeleteMe = (Wave*)pIt->Curr();
        pNode = pIt->Next();
        delete pDeleteMe;
    }

    pIt = this->baseGetReserveIterator();

    pNode = pIt->First();

    // Walk through the nodes
    while (!pIt->IsDone())
    {
        Wave* pDeleteMe = (Wave*)pIt->Curr();
        pNode = pIt->Next();
        delete pDeleteMe;
    }
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void WaveManager::Create(int reserveNum, int reserveGrow)
{
    // make sure values are ressonable 
    assert(reserveNum > 0);
    assert(reserveGrow > 0);

    // initialize the singleton here
    assert(posInstance == nullptr);

    // Do the initialization
    if (posInstance == nullptr)
    {
        posInstance = new WaveManager(reserveNum, reserveGrow);
    }

}

void WaveManager::Destroy()
{
    WaveManager* pMan = WaveManager::privGetInstance();
    assert(pMan != nullptr);

    delete WaveManager::posInstance;
    WaveManager::posInstance = nullptr;
}

Wave* WaveManager::Add(Wave::ID _waveID, const char* const _pWaveName, I_File_CB* _pIFileCB)
{
    WaveManager* pMan = WaveManager::privGetInstance();

    Wave* pNode = (Wave*)pMan->baseAddToFront();
    assert(pNode != nullptr);

    //Initialize 
    assert(_pWaveName);
    assert(_pIFileCB);
    pNode->SetPending(_pWaveName, _waveID, _pIFileCB);

    Debug::out("WaveManager::Add() create FileLoadCmd() \n");
    FileLoadCmd* pCmd = new FileLoadCmd(_waveID, _pWaveName, pNode);
    assert(pCmd);

    bool status = QueueManager::SendFile(pCmd);
    assert(status);

    return pNode;
}

Wave* WaveManager::Add(Wave::ID _waveID, const char* const _pWaveName, User_File_CB* _pUserFileCB)
{
    WaveManager* pMan = WaveManager::privGetInstance();

    Wave* pNode = (Wave*)pMan->baseAddToFront();
    assert(pNode != nullptr);

    //Initialize 
    assert(_pWaveName);
    assert(_pUserFileCB);
    pNode->SetPending(_pWaveName, _waveID, _pUserFileCB);

    Debug::out("WaveManager::Add() create FileLoadCmd() \n");
    FileLoadCmd* pCmd = new FileLoadCmd(_waveID, _pWaveName, pNode);
    assert(pCmd);

    bool status = QueueManager::SendFile(pCmd);
    assert(status);

    return pNode;
}

Wave* WaveManager::Find(Wave::ID _id)
{
    WaveManager* pMan = WaveManager::privGetInstance();
    assert(pMan != nullptr);

    // Compare functions only compares two Nodes

    // So:  Use the Compare Node - as a reference
    //      use in the Compare() function
    pMan->poNodeCompare->id = _id;

    Wave* pData = (Wave*)pMan->baseFind(pMan->poNodeCompare);
    return pData;
}

void WaveManager::Remove(Wave* pNode)
{
    assert(pNode != nullptr);

    WaveManager* pMan = WaveManager::privGetInstance();
    assert(pMan != nullptr);

    pMan->baseRemove(pNode);
}

void WaveManager::Dump()
{
    WaveManager* pMan = WaveManager::privGetInstance();
    assert(pMan != nullptr);

    pMan->baseDump();
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
WaveManager* WaveManager::privGetInstance()
{
    // Safety - this forces users to call Create() first before using class
    assert(posInstance != nullptr);

    return posInstance;
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* WaveManager::derivedCreateNode()
{
    DLink* pNodeBase = new Wave();
    assert(pNodeBase != nullptr);

    return pNodeBase;
}

