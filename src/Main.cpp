// ---------------------------------------------------------------------------
// includes

#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include <iostream>
#include "Image.h"
#include <ctime>
#include "Utilities.h"
#include "Graphics.h"
#include "Tiles.h"
#include <vector>
#include "PitchDemo.h"
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
	AESysSetWindowTitle("GAM150");

	// reset the system modules
	AESysReset();

	/// Test init functions

	Demo::Init();

	char strBuffer[100];
	Graphics::Text testText("../Assets/Font/Roboto-Regular.ttf", strBuffer, 15, 1.0f);
	testText.color.SetColor(255, 0, 0, 255);

	std::cout << "Window Width: " << AEGetWindowWidth() << "\tWindow Height: " << AEGetWindowHeight() << std::endl;

	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		///////////////////
		// Game loop update

		// Game loop update end
		///////////////////////

		//////////////////
		// Game loop draw
		Utilities::Set_FullScreen();
		Demo::Update();


		memset(strBuffer, 0, 100 * sizeof(char));
		sprintf_s(strBuffer, "Frame Rate:  %.2f", AEFrameRateControllerGetFrameRate());
		testText.Draw_Text(testText, AEVector2::Set(0, 570));


		// Game loop draw end
		/////////////////////

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	testText.Free();
	Demo::Exit();

	AESysExit();
}