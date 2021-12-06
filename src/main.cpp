//-----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "Game.h"

int CALLBACK WinMain(HINSTANCE , HINSTANCE ,  LPSTR , int)                  
{          
	START_BANNER_MAIN("main");

	IDEWinSDKCheck
	IDEToolsCheck
	IDECompilerCheck

	// create Game
	Game *pGame = new Game();    
	assert(pGame);

	// start the game
	pGame->run();                                  

	delete pGame;

	return 0;                                       
}

//---  End of File ---
