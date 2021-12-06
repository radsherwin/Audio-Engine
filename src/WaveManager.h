//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef WAVE_MAN_H
#define WAVE_MAN_H 

#include "ManBase.h"
#include "DLinkMan.h"
#include "Wave.h"
#include "I_File_CB.h"
#include "User_File_CB.h"

class WaveManager : public ManBase
{

    //----------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------
private:
    WaveManager(int reserveNum = 3, int reserveGrow = 1);
    ~WaveManager();

    //----------------------------------------------------------------------
    // Static Methods
    //----------------------------------------------------------------------
public:
    static void Create(int reserveNum = 3, int reserveGrow = 1);
    static void Destroy();

    static Wave* Add(Wave::ID id, const char* const pWaveName, I_File_CB*);
    static Wave* Add(Wave::ID id, const char* const pWaveName, User_File_CB*); //Async
    static Wave* Find(Wave::ID id);

    static void Remove(Wave* pNode);
    static void Dump();

    //----------------------------------------------------------------------
    // Private methods
    //----------------------------------------------------------------------
private:
    static WaveManager* privGetInstance();

    //----------------------------------------------------------------------
    // Override Abstract methods
    //----------------------------------------------------------------------
protected:
    DLink* derivedCreateNode() override;


    //----------------------------------------------------------------------
    // Data: unique data for this manager 
    //----------------------------------------------------------------------
private:
    Wave* poNodeCompare;
    static WaveManager* posInstance;

};


#endif