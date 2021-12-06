#include "PriorityTable.h"
#include "StringThis.h"
#include "SndManager.h"
#include "Audio.h"

using namespace ThreadFramework;

PriorityTable::Table::Table()
	: sndID(SndId::Uninitialized),
	status(Status::EMPTY),
	handleID(0),
	priority(INT_MAX),
	timeElapsed(0)
{

}

PriorityTable::PriorityTable()
	: table(),
	mtx()
{

}

PriorityTable::~PriorityTable()
{

}

PriorityTable::Table* PriorityTable::Find(const SndId _sndID)
{
	std::lock_guard<std::mutex> lock(this->mtx);

	Table* pTable = this->privFind(_sndID);

	return pTable;
}

PriorityTable::Table* PriorityTable::privFind(const SndId _sndID)
{

	Table* pTable = nullptr;

	for (int i = 0; i < PriorityTable::TABLE_COUNT; i++)
	{
		if (table[i].sndID == _sndID)
		{
			pTable = &table[i];
			break;
		}
	}

	return pTable;
}

void PriorityTable::Register(const SndId _sndID, const unsigned int _handleID, const int _priority, Status _status)
{
	std::lock_guard<std::mutex> lock(this->mtx);

	Table* pTable = nullptr;
	bool found = this->privFindBestFit(pTable, _priority);
	
	if (found)
	{
		pTable->sndID = _sndID;
		pTable->handleID = _handleID;
		pTable->priority = _priority;
		pTable->status = _status;
		if (_status == Status::PLAY)
		{
			Audio::Play(pTable->sndID);
		}
		else if (_status == Status::STOP)
		{
			Audio::Stop(pTable->sndID);
		}


		
		pTable->timeElapsed = 0;
	}
	else
	{
		Debug::out("Priority rejected for -----> %x\t%s\n", _handleID, StringMe(_sndID));
	}

	
}

void PriorityTable::Remove(const SndId _sndID)
{
	std::lock_guard<std::mutex> lock(this->mtx);

	this->privRemove(_sndID);
}

void PriorityTable::privRemove(const SndId _sndID)
{
	for (int i = 0; i < PriorityTable::TABLE_COUNT; i++)
	{
		if (table[i].sndID == _sndID)
		{
			table[i].sndID = SndId::EMPTY;
			table[i].handleID = 0;
			table[i].priority = INT_MAX;
			table[i].status = Status::EMPTY;
			table[i].timeElapsed = 0;
		}
	}
}

void PriorityTable::UpdateTime()
{
	std::lock_guard<std::mutex> lock(this->mtx);

	this->privUpdateTime();
}

void PriorityTable::privUpdateTime()
{
	for (int i = 0; i < PriorityTable::TABLE_COUNT; i++)
	{
		if (table[i].status == Status::PLAY)
		{
			table[i].timeElapsed+=500;
		}
	}
}

bool PriorityTable::privFindBestFit(Table*& _table, const int _priority)
{
	//if not empty spot, find one where the priorty is == or >= and replace it
	int lowestPriority = _priority;
	int oldestTimeElapsed = 0;
	int tableSpot = -1;
	//Find empty
	for (int i = 0; i < PriorityTable::TABLE_COUNT; i++)
	{
		//table[i].timeElapsed = table[i].pSnd->GetTimeElapsed();
		if (table[i].priority > lowestPriority) //ALSO CHECK FOR ==
		{
			lowestPriority = table[i].priority;
			oldestTimeElapsed = table[i].timeElapsed;
			tableSpot = i;
		}
		else if (table[i].priority == lowestPriority)
		{
			if (table[i].timeElapsed > oldestTimeElapsed)
			{
				oldestTimeElapsed = table[i].timeElapsed;
				lowestPriority = table[i].priority;
				tableSpot = i;
			}
		}

		if (table[i].sndID == SndId::EMPTY && table[i].status == Status::EMPTY)
		{
			tableSpot = i;
			break;
		}
	}

	if (table[tableSpot].sndID != SndId::EMPTY && table[tableSpot].sndID != SndId::Uninitialized && tableSpot >=0)
	{
		//Stop audio
		Debug::out("Dropping from Priority Table ------> %x\t%s\n", table[tableSpot].handleID, StringMe(table[tableSpot].sndID));
		Audio::Stop(table[tableSpot].sndID);
		
	}
	if (tableSpot >= 0)
	{
		_table = &table[tableSpot];
		return true;
	}
	else
	{
		return false;
	}

	
}

void PriorityTable::ClearTable()
{
	std::lock_guard<std::mutex> lock(this->mtx);
	this->privClearTable();
}

void PriorityTable::privClearTable()
{
	for (int i = 0; i < PriorityTable::TABLE_COUNT; i++)
	{
		if (table[i].sndID != SndId::EMPTY && table[i].sndID != SndId::Uninitialized)
		{
			Audio::Stop(table[i].sndID);
			table[i].sndID = SndId::EMPTY;
			table[i].handleID = 0;
			table[i].priority = INT_MAX;
			table[i].status = Status::EMPTY;
			table[i].timeElapsed = 0;
		}
	}
}

void PriorityTable::GetTime(const SndId _sndID)
{
	std::lock_guard<std::mutex> lock(this->mtx);
	this->privGetTime(_sndID);
}

void PriorityTable::privGetTime(const SndId _sndID)
{
	for (int i = 0; i < PriorityTable::TABLE_COUNT; i++)
	{
		if (table[i].sndID == _sndID)
		{
			Debug::out("SndID: %s elapsed time---> %d\n", StringMe(_sndID), table[i].timeElapsed);
		}
	}
}

void PriorityTable::Dump()
{
	Debug::out("------ Active Priority Table ------\n");
	for (int i = 0; i < PriorityTable::TABLE_COUNT; i++)
	{
		if (table[i].sndID != SndId::EMPTY && table[i].sndID != SndId::Uninitialized)
			Debug::out("%x: \t%d\t%d ms\n", table[i].handleID, table[i].priority, table[i].timeElapsed);
	}
}

void PriorityTable::Print(SndId _sndID, char* _waveID, float _amt)
{
	for (int i = 0; i < PriorityTable::TABLE_COUNT; i++)
	{
		if (table[i].sndID == _sndID)
		{
			Debug::out("------ Active Priority Table ------\n");
			Debug::out("Wave file: %s\n\t\t\tTime elapsed: %d\n \t\t\t Handle ID: %x\n\t\t\tPan amount: %04.1f\n", _waveID, table[i].timeElapsed, table[i].handleID, _amt);
		}
	}
}
