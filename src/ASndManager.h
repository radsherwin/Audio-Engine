//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ASND_MANAGER_H
#define ASND_MANAGER_H 

#include "ManBase.h"
#include "DLinkMan.h"
#include "Snd.h"
#include "ASnd.h"

class ASndManager : public ManBase
{

    //----------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------
private:
    ASndManager(int reserveNum = 3, int reserveGrow = 1);
    ~ASndManager();

    //----------------------------------------------------------------------
    // Static Methods
    //----------------------------------------------------------------------
public:
    static void Create(int reserveNum = 3, int reserveGrow = 1);
    static void Destroy();

    static ASnd* Add(Snd* , SndId);
    static ASnd* Find(SndId);

    static void Remove(ASnd* pNode);
    static void Dump();

    //----------------------------------------------------------------------
    // Private methods
    //----------------------------------------------------------------------
private:
    static ASndManager* privGetInstance();

    //----------------------------------------------------------------------
    // Override Abstract methods
    //----------------------------------------------------------------------
protected:
    DLink* derivedCreateNode() override;


    //----------------------------------------------------------------------
    // Data: unique data for this manager 
    //----------------------------------------------------------------------
private:
    ASnd* poNodeCompare;
    static ASndManager* posInstance;

};


#endif