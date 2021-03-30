// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"
#include <iostream>
#include "Image.h"
#include <ctime>
#include "Utilities.h"
#include "Graphics.h"
#include "Tiles.h"
#include "Constants.h"
#include "GameStateManager.h"
#include "MainMenu.h"
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
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
	///////////////////////
	// Variable declaration end
	///////////////////////////

	/////////////////
	// Initialization
	srand(static_cast<u32>(time(NULL)));
	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("JumperMan");

	// reset the system modules

	/// Test init functions
	font::ID = AEGfxCreateFont(FP::FontFile, 40);
	Graphics::Load_Meshes();

	//std::cout << "Window Width: " << AEGetWindowWidth() << "\tWindow Height: " << AEGetWindowHeight() << std::endl << std::endl;
	//std::cout << "\nUse keys WASD to navigate around the game\n";
	//std::cout << "\nKey F1 enables debug mode during gameplay\n";
	//std::cout << "\nL ALT + Enter streches to full screen during gameplay\n";
	// Initialises the GSM
	GameStateManagerInit();
	AEToogleFullScreen(fullscreen);

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

			//const float target = 2.0f; //c1
			//const float start = 0.0f; //c0
			//static float range = target - start;

			//static float t = 0.0f; //t
			//static float current = start;
			//

			//current = current < target ? start + t * range : target;
			//t += g_dt;


			//printf("%f \n", current);


			Utils::CheckFullScreenKeyInput();
		}
		GameStateFree(); //Resets the game state

		if (gamestateNext != GS_RESTART)
		{
			GameStateUnload(); //Unloads all loaded assets of game state
		}

		gamestatePrev = gamestateCurr;
		gamestateCurr = gamestateNext;
	}
	Graphics::Free();
	AESysExit();
}