#ifndef SND_MANAGER_H
#define SND_MANAGER_H

#include "ManBase.h"
#include "DLinkMan.h"
#include "Snd.h"
#include "ASnd.h"
#include "CircularData.h"
#include "Command.h"

//void Test_Main(CircularData* pIn_TestQueue, CircularData* pOut_TestQueue, bool &Quitflag);

class SndManager : public ManBase
{
public:
	// Default constructors
	SndManager(int reserveNum = 3, int reserveGrow = 1);
	SndManager(const SndManager&) = delete;
	const SndManager& operator = (const SndManager&) = delete;
	~SndManager();

	// Public methods:
	static void Update();
	static void SetTime(int);
	static int GetTime();


	//NEW METHODS FROM MANBASE
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();
	static Snd* Add(SndId _SndID, Wave::ID wave_id);
	static Snd* Find(SndId);
	static void Remove(Snd*);
	static void Dump();


	//Custom methods
	static void Stitch(SndId _sndID, SndId _nextID);


	//----------------------------------------------------------------------
	// Private methods
	//----------------------------------------------------------------------
private:
	static SndManager* privGetInstance();

	//----------------------------------------------------------------------
	// Override Abstract methods
	//----------------------------------------------------------------------
protected:
	DLink* derivedCreateNode() override;


	//----------------------------------------------------------------------
	// Data: unique data for this manager 
	//----------------------------------------------------------------------
private:
	Snd* poNodeCompare;
	static SndManager* posInstance;

	int time;
};

#endif