#ifndef VOICELIST_H
#define VOICELIST_H

#include "Voice.h"

class VoiceList
{
public:
	VoiceList();
	VoiceList(const VoiceList&) = delete;
	VoiceList& operator=(const VoiceList&) = delete;
	~VoiceList();

public:
	void Add(Voice*);
	void Remove(Voice*); //remove individual voice from list
	void DeleteVoices(); //delete all voices and access their destructors. 
	

//Variables
private:
	Voice* pHead;
	Voice* pNext;

};

#endif
