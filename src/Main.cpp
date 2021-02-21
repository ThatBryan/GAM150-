// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"
#include <iostream>
#include "Image.h"
#include <ctime>
#include "Utilities.h"
#include "Graphics.h"
#include "Tiles.h"
#include <vector>
#include "PitchDemo.h"
#include "Constants.h"
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
	// Variable declaration

	int gGameRunning = 1;
	// Variable declaration end
	///////////////////////////

	/////////////////
	// Initialization
	srand((u32)time(NULL));
	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("JumperMan");

	// reset the system modules
	AESysReset();

	/// Test init functions

	fontID = AEGfxCreateFont(FontFile, 30);
	Demo::Init();


	std::cout << "Window Width: " << AEGetWindowWidth() << "\tWindow Height: " << AEGetWindowHeight() << std::endl;

	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		g_dt = static_cast<f32>(AEFrameRateControllerGetFrameTime());
		Demo::Update();

		// Informing the system about the loop's end
		AESysFrameEnd();

		if(!paused)
			app_time += g_dt;

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}
	Demo::Exit();
	Graphics::Free();
	AESysExit();
}