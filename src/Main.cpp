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
// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	///////////////////////
	// Variable declaration

	int gGameRunning = 1;
	// Variable declaration end
	///////////////////////////

	/////////////////
	// Initialization
	srand(time(NULL));

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("JumperMan");

	// reset the system modules
	AESysReset();

	/// Test init functions

	Demo::Init();
	char strBuffer[100];
	Graphics::Text FPS_Display(FontFile, strBuffer, 15, 1.0f);
	FPS_Display.color.SetColor(255, 0, 0, 255);

	std::cout << "Window Width: " << AEGetWindowWidth() << "\tWindow Height: " << AEGetWindowHeight() << std::endl;

	Image test(PlayerSprite, 100.0f, 100.0f);
	test.pos = { 400, 300 };

	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		Demo::Update();

		//test.Draw_Advanced(test, test.pos, 255.0f, 90.0f);

		memset(strBuffer, 0, 100 * sizeof(char));
		sprintf_s(strBuffer, "Frame Rate:  %.2f", AEFrameRateControllerGetFrameRate());
		FPS_Display.Draw_Text(FPS_Display, AEVec2Set(0, 570));

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	FPS_Display.Free();
	test.Free();
	Demo::Exit();
	AESysExit();
}