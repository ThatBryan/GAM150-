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
	char strBuffer1[100];
	char strBuffer2[100];
	Graphics::Text FPS_Display(FontFile, strBuffer, 15, 1.0f);
	Graphics::Text LevelDisplay(FontFile, strBuffer1, 30, 1.0f);
	Graphics::Text TimerDisplay(FontFile, strBuffer2, 30, 1.0f);
	FPS_Display.color.SetColor(255, 0, 0, 255);
	LevelDisplay.color.SetColor(255, 0, 0, 255);
	TimerDisplay.color.SetColor(0, 0, 0, 255);
	float elapsedTime = 0;

	std::cout << "Window Width: " << AEGetWindowWidth() << "\tWindow Height: " << AEGetWindowHeight() << std::endl;

	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();
	
		Demo::Update();

		memset(strBuffer, 0, 100 * sizeof(char));
		sprintf_s(strBuffer, "Current Level: Tutorial Time Elapsed:  %.2f", AEFrameRateControllerGetFrameRate());
		if(DebugMode)
			FPS_Display.Draw_Text(FPS_Display, AEVec2Set(0, 400));
		
		memset(strBuffer1, 0, 100 * sizeof(char));
		memset(strBuffer2, 0, 100 * sizeof(char));

		elapsedTime += AEFrameRateControllerGetFrameTime();
		sprintf_s(strBuffer1, "Current Level: Tutorial");
		sprintf_s(strBuffer2, "Time Elapsed: %.2f", elapsedTime);

		LevelDisplay.Draw_Text(LevelDisplay, AEVec2Set(0, 550));
		TimerDisplay.Draw_Text(TimerDisplay, AEVec2Set(665, 550));

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	FPS_Display.Free();
	LevelDisplay.Free();
	TimerDisplay.Free();

	Demo::Exit();
	AESysExit();
}