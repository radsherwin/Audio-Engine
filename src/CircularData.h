#ifndef CIRCULAR_DATA_H
#define CIRCULAR_DATA_H

#include "CircularIndex.h"
#include "Command.h"

class CircularData
{
public:
	static const int CIRCULAR_DATA_SIZE = 512; //need to be a power of 2

public:
	CircularData();

	CircularData(const CircularData&) = delete;
	const CircularData& operator = (const CircularData&) = delete;
	~CircularData() = default;

	bool PushBack(Command*);
	bool PopFront(Command*&);
	bool PeekFront(Command*&);

	void ClearQueue();

private:
	Command* data[CIRCULAR_DATA_SIZE];

	CircularIndex front;
	CircularIndex back;
	bool empty;
	bool full;

	std::mutex mtx;
};

#endif