#include "WaveTable.h"
#include "StringThis.h"

using namespace ThreadFramework;

WaveTable::Table::Table()
	: waveID(Wave::ID::Empty),
	status(WaveTable::Status::EMPTY)
{

}

WaveTable::WaveTable()
	: table(),
	mtx()
{

}

WaveTable::~WaveTable()
{

}

WaveTable::Table* WaveTable::Find(const Wave::ID _waveID)
{
	std::lock_guard<std::mutex> lock(this->mtx);

	Table* pTable = this->privFind(_waveID);

	return pTable;
}

WaveTable::Table* WaveTable::privFind(const Wave::ID _waveID)
{
	Table* pTable = nullptr;

	for (int i = 0; i < WaveTable::TABLE_COUNT; i++)
	{
		if (table[i].waveID == _waveID)
		{
			pTable = &table[i];
			break;
		}
	}

	return pTable;
}

void WaveTable::Register(const Wave::ID _waveID, const WaveTable::Status _status)
{
	std::lock_guard<std::mutex> lock(this->mtx);

	Table* pTable = this->privFindEmpty();

	//is it filled?
	assert(pTable);

	pTable->waveID = _waveID;
	pTable->status = _status;
}

WaveTable::Table* WaveTable::privFindEmpty()
{
	Table* pTable = nullptr;

	for (int i = 0; i < WaveTable::TABLE_COUNT; i++)
	{
		if (table[i].waveID == Wave::ID::Empty && table[i].status == WaveTable::Status::EMPTY)
		{
			pTable = &table[i];
			break;
		}
	}

	return pTable;
}

void WaveTable::Update(const Wave::ID _waveID, const WaveTable::Status _status)
{
	std::lock_guard<std::mutex> lock(this->mtx);

	Table* pTable = this->privFind(_waveID);

	//is it filled?
	assert(pTable);

	pTable->waveID = _waveID;
	pTable->status = _status;
}

void WaveTable::Remove(const Wave::ID _waveID)
{
	std::lock_guard<std::mutex> lock(this->mtx);

	this->privRemove(_waveID);
}

void WaveTable::ClearTable()
{
	std::lock_guard<std::mutex> lock(this->mtx);
	this->privClear();
}

void WaveTable::privClear()
{
	for (int i = 0; i < WaveTable::TABLE_COUNT; i++)
	{
		if (table[i].waveID != Wave::ID::Empty && table[i].status != WaveTable::Status::EMPTY)
		{
			table[i].waveID = Wave::ID::Empty;
			table[i].status = WaveTable::Status::EMPTY;
		}
	}
}

void WaveTable::privRemove(const Wave::ID _waveID)
{
	//Check if it's in the table
	Table* pTable = this->privFind(_waveID);

	//is already removed?
	assert(pTable);

	pTable->status = WaveTable::Status::EMPTY;
	pTable->waveID = Wave::ID::Empty;

}

void WaveTable::Dump()
{

	for (int i = 0; i < WaveTable::TABLE_COUNT; i++)
	{
		Trace::out("Wave: %s ||  Status: %s\n", StringMe(table[i].waveID), StringMe(table[i].status));
	}
}
