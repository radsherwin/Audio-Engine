//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef APlaylist_MANAGER_H
#define APlaylist_MANAGER_H 

#include "ManBase.h"
#include "DLinkMan.h"
#include "Snd.h"
#include "Playlist.h"
#include "Voice.h"
#include "Wave.h"
#include "User_File_CB.h"

class APlaylistManager : public ManBase
{

    //----------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------
private:
    APlaylistManager(int reserveNum = 3, int reserveGrow = 1);
    ~APlaylistManager();

    //----------------------------------------------------------------------
    // Static Methods
    //----------------------------------------------------------------------
public:
    static void Create(int reserveNum = 3, int reserveGrow = 1);
    static void Destroy();

    static Playlist* Add(SndId, Wave::ID, User_File_CB* _pUserCB = nullptr);
    static Playlist* Find(SndId);

    static void Remove(Playlist*);
    static void Dump();

    //----------------------------------------------------------------------
    // Private methods
    //----------------------------------------------------------------------
private:
    static APlaylistManager* privGetInstance();

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
    static APlaylistManager* posInstance;

};


#endif