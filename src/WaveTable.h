#ifndef WAVE_TABLE_H
#define WAVE_TABLE_H

#include "Wave.h"


class WaveTable
{
public:
	static const unsigned int TABLE_COUNT = 24;

	enum class Status
	{
		PENDING,
		READY,
		EMPTY
	};

	struct Table
	{
		Table();

		Wave::ID waveID;
		Status status;
	};

public:
	WaveTable();
	WaveTable(const WaveTable&) = delete;
	WaveTable& operator=(const WaveTable&) = delete;
	~WaveTable();

	WaveTable::Table* Find(const Wave::ID _waveID);
	
	void Register(const Wave::ID _waveID, const WaveTable::Status _status);
	void Update(const Wave::ID _waveID, const WaveTable::Status _status);
	void Remove(const Wave::ID _waveID);
	void ClearTable();
	void Dump();

private:
	Table* privFindEmpty();
	Table* privFind(const Wave::ID _waveID);
	void privRemove(const Wave::ID _waveID);
	void privClear();

private:
	Table table[TABLE_COUNT];
	std::mutex mtx;
};

#endif