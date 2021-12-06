//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Playlist_MANAGER_H
#define Playlist_MANAGER_H 

#include "ManBase.h"
#include "DLinkMan.h"
#include "Snd.h"
//#include "ASnd.h"
#include "Playlist.h"
#include "Voice.h"
#include "Wave.h"
#include "User_File_CB.h"

class PlaylistManager : public ManBase
{

    //----------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------
private:
    PlaylistManager(int reserveNum = 3, int reserveGrow = 1);
    ~PlaylistManager();

    //----------------------------------------------------------------------
    // Static Methods
    //----------------------------------------------------------------------
public:
    static void Create(int reserveNum = 3, int reserveGrow = 1);
    static void Destroy();

    static void Load(SndId, Wave::ID, User_File_CB* = nullptr);
    static Playlist* Add(SndId, Wave::ID, Voice* _pHeadVoice);
    static Playlist* Add(SndId, Wave::ID, User_File_CB* = nullptr);
    static Playlist* Find(SndId);
    static void Stitch(SndId _sndID, Wave::ID _waveID);

    static void Remove(Playlist*);
    static void Dump();

    //----------------------------------------------------------------------
    // Private methods
    //----------------------------------------------------------------------
private:
    static PlaylistManager* privGetInstance();

    //----------------------------------------------------------------------
    // Override Abstract methods
    //----------------------------------------------------------------------
protected:
    DLink* derivedCreateNode() override;


    //----------------------------------------------------------------------
    // Data: unique data for this manager 
    //----------------------------------------------------------------------
private:
    Playlist* poNodeCompare;
    static PlaylistManager* posInstance;

};


#endif