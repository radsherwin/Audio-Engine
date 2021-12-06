//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef VOICE_MAN_H
#define VOICE_MAN_H 

#include "ManBase.h"
#include "DLinkMan.h"
#include "Voice.h"
#include "Wave.h"
#include "SndCallRegistry.h"
#include "CircularData.h"
//#include "ASnd.h"

class VoiceManager : public ManBase
{

    //----------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------
private:
    VoiceManager(int reserveNum = 3, int reserveGrow = 1);
    ~VoiceManager();

    //----------------------------------------------------------------------
    // Static Methods
    //----------------------------------------------------------------------
public:
    
    static void Create(int reserveNum = 3, int reserveGrow = 1);
    static void Destroy();
    static void UpdateVoice(Wave::ID _waveId);
  
    static Voice* Add(Wave::ID wave_id, SndId);
    static Voice* Find(Wave::ID);
    static void Remove(Voice*);
    static void Dump();

    //----------------------------------------------------------------------
    // Private methods
    //----------------------------------------------------------------------
private:
    static VoiceManager* privGetInstance();

    //----------------------------------------------------------------------
    // Override Abstract methods
    //----------------------------------------------------------------------
protected:
    DLink* derivedCreateNode() override;


    //----------------------------------------------------------------------
    // Data: unique data for this manager 
    //----------------------------------------------------------------------
private:
    Voice* poNodeCompare;
    static VoiceManager* posInstance;

};


#endif