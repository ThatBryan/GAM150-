// ---------------------------------------------------------------------------
// includes

#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include <iostream>
#include "Image.h"
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
	s8 fontId = 0;
	int counter = 255;
	// Variable declaration end
	///////////////////////////

	/////////////////
	// Initialization
	AEGfxSetBackgroundColor(1.0f, 0, 0.0f);


	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);


	// Changing the window title
	AESysSetWindowTitle("GAM150");

	// reset the system modules
	AESysReset();

	// Initialization end
	/////////////////////



	////////////////////////////////
	// Creating the objects (Shapes)

	// Creating the objects (Shapes) end
	////////////////////////////////////


	////////////////////////////
	// Loading textures (images)

	// Texture 1: From file

	// Loading textures (images) end
	//////////////////////////////////

	//////////////////////////////////
	// Creating Fonts	

	fontId = AEGfxCreateFont("../Assets/Font/Roboto-Regular.ttf", 12);

	// Creating Fonts end
	//////////////////////////////////

	/// Test init functions

	const char* logofile = "../Assets/Logo/DigiPen_RED.png";
	img logo = { 0 };
	logo = Image::Initialize(logo, logofile, 400, 300, AEGetWindowWidth() - 50.0f, AEGetWindowHeight() / 2.0f);

	Rect lol = { 0 };
	lol = Graphics::Set_Rect(lol, AEGetWindowWidth() / 2.0f, AEGetWindowHeight() / 2.0f, 100.0f, 100.0f);
	Graphics::Set_Color(&lol, 255, 0, 0);

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

		Utilities::Set_FullScreen();
		// Game loop update end
		///////////////////////


		//////////////////
		// Game loop draw
		AEGfxSetBackgroundColor(0, 0, 0);

		// Draw boi
		counter -= 2;
		if (counter < 0)
			counter = 255;
		Image::Draw_Default(logo, counter);

		Graphics::Draw_Rect(lol);
	
		char strBuffer[100];
		memset(strBuffer, 0, 100 * sizeof(char));
		sprintf_s(strBuffer, "Frame Time:  %.6f", AEFrameRateControllerGetFrameTime());

		f32 TextWidth, TextHeight;
		AEGfxGetPrintSize(fontId, strBuffer, 1.0f, TextWidth, TextHeight);
		AEGfxPrint(fontId, strBuffer, 0.99 - TextWidth, 0.99 - TextHeight, 1.0f, 0, 0, 0);

		// Game loop draw end
		/////////////////////

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	AEGfxDestroyFont(fontId);
	Image::FreeEntities(logo);
	Graphics::FreeEntities(lol);
	// free the system
	AESysExit();
}