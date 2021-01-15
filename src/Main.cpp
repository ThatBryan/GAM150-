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
	Img logo;
	logo = Image::Initialize(logo, logofile, AEGetWindowWidth() - 50.0f, AEGetWindowHeight() / 2.0f);
	AEVec2 logoPos = { 0, 0 };

	Rect lol;
	lol = Graphics::Set_Rect(lol, 50.0f, 50.0f);
	lol.Set_Color(&lol, 0, 255, 255, 255);

	AEVec2 lolPos = { 0, 0 };
	Img boi;
	const char* boiFile = "../Assets/Art/boi.png";
	boi = Image::Initialize(boi, boiFile, 100.0f, 100.0f);
	AEVec2 boiPos = { 0, 0 };

	char strBuffer[100];
	Text testText;
	testText = Graphics::Set_Text(testText, fontId, strBuffer, 1.0f);
	testText.Set_Color(&testText, 0, 255, 0, 255);
	AEVec2 lmao = { 0, 0 };

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
		counter -= 4;
		if (counter < 0)
			counter = 255;

		Image::Draw_Default(logo, Utilities::Vector_Set(logoPos, 400.0f, 300.0f),counter);
		for (int i = 0; i < 5; i++)
		{
			Image::Draw_Tinted(boi, Utilities::Vector_Set(boiPos, 200.0f + i * boi.width, 200.0f), 255, 0, 0, 255);
			Graphics::Draw_Rect(lol, Utilities::Vector_Set(lolPos, 60 * i + (AEGetWindowWidth() / 2.0f), (AEGetWindowHeight() / 2.0f)));
		}
		memset(strBuffer, 0, 100 * sizeof(char));
		sprintf_s(strBuffer, "Frame Time:  %.6f", AEFrameRateControllerGetFrameRate());
		Graphics::Draw_Text(testText, Utilities::Vector_Set(lmao, AEGetWindowWidth(), AEGetWindowHeight()));

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
	Image::FreeEntities(boi);
	Graphics::FreeEntities(lol);
	// free the system
	AESysExit();
}