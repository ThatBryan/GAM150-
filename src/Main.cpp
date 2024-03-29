/******************************************************************************/
/*!
\file				Main.cpp
\primary author: 	Team Only4 (25% each)

\date   			February 28, 2021
\brief				Main entry point of the program. 

All content � 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/

#include "AEEngine.h"
#include "Image.h"
#include "Utilities.h"
#include "Graphics.h"
#include "Tiles.h"
#include "Constants.h"
#include "GameStateManager.h"
#include "MainMenu.h"
#include "Globals.h"
#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <crtdbg.h>
#include "Leaderboard.h"
// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//// Enable run-time memory check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

	//int * pi = new int;
	srand(static_cast<u32>(time(NULL)));

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("JumperMan");

	// reset the system modules

	Graphics::Load_Fonts();
	Graphics::Load_Meshes();
	Leaderboard::Load();

	// Initialises the GSM
	GameStateManagerInit();
	AEToogleFullScreen(GAMEPLAY_MISC::FULLSCREEN);

	//Checks if game state isnt at quit status
	while (gamestateCurr != GS_QUIT)
	{
		AESysReset();
		//checks if game state isnt at restart
		if (gamestateCurr != GS_RESTART)
		{
			GameStateManagerUpdate(); //Update GSM
			GameStateLoad(); //Loads the game state
		}
		else
		{
			gamestateNext = gamestateCurr = gamestatePrev;
		}

		GameStateInit(); //Init the game state

		//Game Loop
		while (gamestateCurr == gamestateNext)
		{
			// Informing the system about the loop's start
			AESysFrameStart();

			// Handling Input
			AEInputUpdate();
			g_dt = static_cast<f32>(AEFrameRateControllerGetFrameTime()); //Getting delta time

			if (g_dt >= 0.01667f) // 1 / 60fps;
			{
				g_dt = 0.01667f;
			}
			GameStateUpdate(); //Update game state
			GameStateDraw(); //Render game state

			// Informing the system about the loop's end
			AESysFrameEnd();

			// check if forcing the application to quit
			if (0 == AESysDoesWindowExist())
				gamestateNext = GS_QUIT;

			Utils::CheckKeyBindInputs();
		}
		GameStateFree(); //Resets the game state

		if (gamestateNext != GS_RESTART)
		{
			GameStateUnload(); //Unloads all loaded assets of game state
		}

		gamestatePrev = gamestateCurr;
		gamestateCurr = gamestateNext;
	}
	Leaderboard::Save();
	Graphics::Free();
	AESysExit();
}