#ifndef PRIORITY_TABLE_H
#define PRIORITY_TABLE_H

#include "Snd.h"
#include "SndCallRegistry.h"


class PriorityTable
{
public:
	static const unsigned int TABLE_COUNT = 6;

	enum class Status
	{
		PLAY,
		STALLED,
		STOP,
		EMPTY
	};

	struct Table
	{
		Table();

		SndId sndID;
		Status status;
		unsigned int handleID;
		int priority;
		int timeElapsed; //in ms, lives on Snd.cpp
	};

public:
	PriorityTable();
	PriorityTable(const PriorityTable&) = delete;
	PriorityTable& operator=(const PriorityTable&) = delete;
	~PriorityTable();

	PriorityTable::Table* Find(const SndId _sndID);

	void Register(const SndId _sndID, const unsigned int _handleID, const int _priority, Status _status);
	void Remove(const SndId _sndID);
	void UpdateTime();
	void ClearTable();
	void GetTime(const SndId _sndID);
	
	//void Remove(Snd* _snd, const int _priority);
	void Dump();
	void Print(SndId _sndID, char* _waveID, float _amt);

private:
	bool privFindBestFit(Table*& _table, const int _priority);
	Table* privFind(const SndId _sndID);
	void privUpdateTime();
	void privClearTable();
	void privRemove(const SndId _sndID);
	void privGetTime(const SndId _sndID);

private:
	Table table[TABLE_COUNT];
	std::mutex mtx;
};

#endif