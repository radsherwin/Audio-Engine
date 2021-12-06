#ifndef SND_STOP_COMMAND_H
#define SND_STOP_COMMAND_H

#include "Command.h"
#include "ASnd.h"
#include "Voice.h"
#include "SndCallRegistry.h"

class SndStopCmd : public Command
{
public:
	SndStopCmd() = delete;
	SndStopCmd(const SndStopCmd&) = delete;
	SndStopCmd& operator=(const SndStopCmd&) = delete;
	~SndStopCmd() = default;

	SndStopCmd(Snd*);

	virtual void Execute() override;

public:
	//data
	Snd* pSnd;
};

#endif