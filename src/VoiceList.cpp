#include "VoiceList.h"
#include "VoiceList.h"


VoiceList::VoiceList()
	: pHead(nullptr),
	pNext(nullptr)
{}

VoiceList::~VoiceList()
{
	this->pHead = nullptr;
	this->pNext = nullptr;
}

void VoiceList::Add(Voice* _voice)
{
	//VoiceList* pMan = VoiceList::privGetInstance();

	//check if in linked list already

	if (this->pHead == nullptr) this->pHead = _voice;
	else {
		Voice* tmpHead = this->pHead;
		while (tmpHead != nullptr)
		{
			if (tmpHead == _voice)
			{
				//Already in list
				break;
			}

			//If we're at the end of the loop
			//Add voice to the end
			if (tmpHead->GetNext() == nullptr)
			{
				tmpHead->SetNext(_voice);
				break;
			}

			tmpHead = tmpHead->GetNext();
		}
	}

	
}

void VoiceList::DeleteVoices()
{
	Voice* tmpHead = this->pHead;
	while (tmpHead != nullptr)
	{
		Voice* pDeleteMe = tmpHead;
		tmpHead = tmpHead->GetNext();
		ThreadFramework::Debug::out("Running VoiceList DeleteMe\n");
		delete pDeleteMe;
	}
}
