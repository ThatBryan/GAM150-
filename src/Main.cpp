// ---------------------------------------------------------------------------
// includes

#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include <iostream>
#include "Image.h"
#include <ctime>
#include "Utilities.h"
#include "Graphics.h"
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
	int counter = 255;
	// Variable declaration end
	///////////////////////////

	/////////////////
	// Initialization
	srand(time(NULL));
	AEGfxSetBackgroundColor(1.0f, 0, 0.0f);


	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);


	// Changing the window title
	AESysSetWindowTitle("GAM150");

	// reset the system modules
	AESysReset();

	/// Test init functions

	Img logo("../Assets/Logo/DigiPen_RED.png", AEGetWindowWidth() - 50.0f, AEGetWindowHeight() / 2.0f);

	Rect lol(50.0f, 50.0f);
	lol.color.SetColor(0, 0, 255, 255);

	Img boi("../Assets/Art/boi.png", 100.0f, 100.0f);
	Img boi2("../Assets/Art/boi.png", 100.0f, 100.0f);

	boi2.pos = { 400, 300 };

	boi.pos = { 200, 400 };

	Line linetest(Utilities::Vector_Set(0, 0), Utilities::Vector_Set(800, 600), 5.0f);


	char strBuffer[100];
	Text testText("../Assets/Font/Roboto-Regular.ttf", strBuffer, 15, 1.0f);
	testText.color.SetColor(0, 255, 0, 255);

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
		AEGfxSetBackgroundColor(0, 0, 0);
		Utilities::Set_FullScreen();

		// Draw boi
		counter -= 4;
		if (counter < 0)
			counter = 255;

		Image::Draw_Default(logo, Utilities::Vector_Set(400.0f, 300.0f),counter);
		
		boi2.Update_Position();
		Image::Draw_Tinted(boi2, boi2.pos, 0, 255, 0, 255);

		Graphics::Draw_Line(linetest);
		boi.Update_Position();
		for (int i = 0; i < 5; i++)
		{
			Image::Draw_Tinted(boi, Utilities::Vector_Set(boi.pos.x + i * boi.width, boi.pos.y), 255, 0, 0, 255);
			Graphics::Draw_Rect(lol, Utilities::Vector_Set(60 * i + (AEGetWindowWidth() / 2.0f), (AEGetWindowHeight() / 2.0f)));
		}

		memset(strBuffer, 0, 100 * sizeof(char));
		sprintf_s(strBuffer, "Frame Rate:  %.2f", AEFrameRateControllerGetFrameRate());
		Graphics::Draw_Text(testText, Utilities::Vector_Set(0, 0));


		// Game loop draw end
		/////////////////////

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	testText.Free();
	logo.Free();
	boi.Free();
	boi2.Free();
	lol.Free();
	linetest.Free();
	AESysExit();
}