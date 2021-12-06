//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ASndManager.h"
#include "SndManager.h"

using namespace ThreadFramework;

ASndManager* ASndManager::posInstance = nullptr;

//----------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------
ASndManager::ASndManager(int reserveNum, int reserveGrow)
    : ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
{
    // Preload the reserve
    this->proFillReservedPool(reserveNum);

    // initialize derived data here
    this->poNodeCompare = new ASnd();
}

ASndManager::~ASndManager()
{
    // Debug::out("~ASnd()\n");
    delete this->poNodeCompare;
    this->poNodeCompare = nullptr;

    // iterate through the list and delete
    Iterator* pIt = this->baseGetActiveIterator();

    DLink* pNode = pIt->First();

    // Walk through the nodes
    while (!pIt->IsDone())
    {
        ASnd* pDeleteMe = (ASnd*)pIt->Curr();
        pNode = pIt->Next();
        delete pDeleteMe;
    }

    pIt = this->baseGetReserveIterator();

    pNode = pIt->First();

    // Walk through the nodes
    while (!pIt->IsDone())
    {
        ASnd* pDeleteMe = (ASnd*)pIt->Curr();
        pNode = pIt->Next();
        delete pDeleteMe;
    }
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void ASndManager::Create(int reserveNum, int reserveGrow)
{
    // make sure values are ressonable 
    assert(reserveNum > 0);
    assert(reserveGrow > 0);

    // initialize the singleton here
    assert(posInstance == nullptr);

    // Do the initialization
    if (posInstance == nullptr)
    {
        posInstance = new ASndManager(reserveNum, reserveGrow);
    }

}

void ASndManager::Destroy()
{
    ASndManager* pMan = ASndManager::privGetInstance();
    assert(pMan != nullptr);

    delete ASndManager::posInstance;
    ASndManager::posInstance = nullptr;
}

ASnd* ASndManager::Add(Snd* pSnd, SndId _sndID)
{
    ASndManager* pMan = ASndManager::privGetInstance();

    ASnd* pNode = (ASnd*)pMan->baseAddToFront();
    assert(pNode != nullptr);

    // Initialize the date
    assert(pSnd);
    pNode->Set(pSnd, _sndID);

    return pNode;
}

ASnd* ASndManager::Find(SndId _sndID)
{
    ASndManager* pMan = ASndManager::privGetInstance();
    assert(pMan != nullptr);

    // Compare functions only compares two Nodes

    // So:  Use the Compare Node - as a reference
    //      use in the Compare() function
    pMan->poNodeCompare->sndID = _sndID;

    ASnd* pData = (ASnd*)pMan->baseFind(pMan->poNodeCompare);
    return pData;
}

void ASndManager::Remove(ASnd* pNode)
{
    assert(pNode != nullptr);

    ASndManager* pMan = ASndManager::privGetInstance();
    assert(pMan != nullptr);

    pMan->baseRemove(pNode);
}

void ASndManager::Dump()
{
    ASndManager* pMan = ASndManager::privGetInstance();
    assert(pMan != nullptr);

    pMan->baseDump();
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
ASndManager* ASndManager::privGetInstance()
{
    // Safety - this forces users to call Create() first before using class
    assert(posInstance != nullptr);

    return posInstance;
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* ASndManager::derivedCreateNode()
{
    DLink* pNodeBase = new ASnd();
    assert(pNodeBase != nullptr);

    return pNodeBase;
}

