//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "VoiceManager.h"
#include "WaveManager.h"
#include "AudioEngine.h"

using namespace ThreadFramework;

VoiceManager* VoiceManager::posInstance = nullptr;

//----------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------
VoiceManager::VoiceManager(int reserveNum, int reserveGrow)
    : ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
{
    // Preload the reserve
    this->proFillReservedPool(reserveNum);

    // initialize derived data here
    this->poNodeCompare = new Voice();
}

VoiceManager::~VoiceManager()
{
    Debug::out("~VoiceManager()\n");
    delete this->poNodeCompare;
    this->poNodeCompare = nullptr;

    // iterate through the list and delete
    Iterator* pIt = this->baseGetActiveIterator();

    DLink* pNode = pIt->First();

    // Walk through the nodes
    while (!pIt->IsDone())
    {
        Voice* pDeleteMe = (Voice*)pIt->Curr();
        pNode = pIt->Next();
        delete pDeleteMe;
    }

    pIt = this->baseGetReserveIterator();

    pNode = pIt->First();

    // Walk through the nodes
    while (!pIt->IsDone())
    {
        Voice* pDeleteMe = (Voice*)pIt->Curr();
        pNode = pIt->Next();
        delete pDeleteMe;
    }
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void VoiceManager::Create(int reserveNum, int reserveGrow)
{
    // make sure values are ressonable 
    assert(reserveNum > 0);
    assert(reserveGrow > 0);

    // initialize the singleton here
    assert(posInstance == nullptr);

    // Do the initialization
    if (posInstance == nullptr)
    {
        posInstance = new VoiceManager(reserveNum, reserveGrow);
    }

}

void VoiceManager::Destroy()
{
    VoiceManager* pMan = VoiceManager::privGetInstance();
    assert(pMan != nullptr);

    delete VoiceManager::posInstance;
    VoiceManager::posInstance = nullptr;
}

void VoiceManager::UpdateVoice(Wave::ID _waveID)
{
    Wave* pWave = WaveManager::Find(_waveID);
    assert(pWave);
    Voice* tmp = VoiceManager::Find(_waveID);
    if (tmp != nullptr)
    {
        tmp->UpdateVoice(_waveID, pWave);
    }
}

Voice* VoiceManager::Add(Wave::ID _waveID, SndId _sndID)
{
    VoiceManager* pMan = VoiceManager::privGetInstance();
    //Pass in Voice. Set compare to voice. 
    // Find the wave from the manager
    Wave* pWave = WaveManager::Find(_waveID);
    assert(pWave);

    Voice* newVoice = (Voice*)pMan->baseAddToFront();
    assert(newVoice != nullptr);
    VoiceCallback* pCallback = new VoiceCallback(_sndID);
    // Initialize the date
    newVoice->Set(_waveID, pWave, pCallback);
    return newVoice;
}

Voice* VoiceManager::Find(Wave::ID _waveID)
{
    VoiceManager* pMan = VoiceManager::privGetInstance();
    assert(pMan != nullptr);

    // Compare functions only compares two Nodes

    // So:  Use the Compare Node - as a reference
    //      use in the Compare() function
    pMan->poNodeCompare->SetWaveID(_waveID);

    Voice* pData = (Voice*)pMan->baseFind(pMan->poNodeCompare);
    return pData;
}

void VoiceManager::Remove(Voice* pNode)
{
    assert(pNode != nullptr);

    VoiceManager* pMan = VoiceManager::privGetInstance();
    assert(pMan != nullptr);
    pMan->baseRemove(pNode);
}

void VoiceManager::Dump()
{
    VoiceManager* pMan = VoiceManager::privGetInstance();
    assert(pMan != nullptr);

    pMan->baseDump();
}



//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
VoiceManager* VoiceManager::privGetInstance()
{
    // Safety - this forces users to call Create() first before using class
    assert(posInstance != nullptr);

    return posInstance;
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* VoiceManager::derivedCreateNode()
{
    DLink* pNodeBase = new Voice();
    assert(pNodeBase != nullptr);

    return pNodeBase;
}

