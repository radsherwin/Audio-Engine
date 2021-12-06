using namespace ThreadFramework;

#include "AuxIFileCBCmd.h"

AuxIFileCBCmd::AuxIFileCBCmd(I_File_CB* _pIFileCB)
	: pIFileCB(_pIFileCB)
{
	assert(pIFileCB);
}

void AuxIFileCBCmd::Execute()
{
	Debug::out("AuxIFileCBCmd::Execute()\n");

	this->pIFileCB->Execute();

	delete this;
}