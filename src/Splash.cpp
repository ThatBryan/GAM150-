/******************************************************************************/
/*!
\file				Splash.cpp
\author: 			Bryan Koh Yan Wei
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Source file which contains the function definitions for
					the Digipen Logo splash screen displayed on launch
					of application.

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#include "Globals.h"
#include "Splash.h"
#include "Utilities.h"
#include "Image.h"
#include "Constants.h"
#include "GameStateManager.h"
#include "AEEngine.h"

#include <array>

Image splash;

enum ImageIdx { DigiPen = 0,
				FMod   = 1,
				Max    = 2};

std::array <Image, ImageIdx::Max> Splashes;

static float splashDurationCurr, alpha;
static const float splashDurationDesired = 3.0f;
static int splashFrame;
static bool FlipAlpha; // For fade in and out effect

void Splash::Init() {
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	splashDurationCurr = 0.0f;
	splashFrame = ImageIdx::DigiPen;
	alpha = 0.0f;
	FlipAlpha = false;
}
void Splash::Update() {

	if (!FlipAlpha) {
		if(splashDurationCurr >= splashDurationDesired / 2.0f)
			FlipAlpha = true;

		splashDurationCurr += g_dt;
	}
	else{
		splashDurationCurr -= g_dt;
	}
									
	alpha = (splashDurationCurr / splashDurationDesired) * 255.0f;

	if (splashDurationCurr <= 0 || AEInputCheckReleased(AEVK_LBUTTON)) {

		splashFrame < ImageIdx::Max - 1 ? ++splashFrame : gamestateNext = GS_MAINMENU;
		FlipAlpha = false;
		splashDurationCurr = 0.0f;
		alpha = 0.0f;
	}
}
void Splash::Render() {
	Splashes[splashFrame].Draw_Texture(alpha);
}
void Splash::Load() {
	AEVec2 ScreenMid{ Utils::GetScreenMiddle() };
	const float splashWidth{ 800.0f }, splashHeight{ 194.0f }; // After applying aspect ratio to original image. 

	if (Utils::RandomRangeInt(0, 1))
		Splashes[ImageIdx::DigiPen].Load(FP::LOGOS::DigipenRed, splashWidth, splashHeight, ScreenMid);
	else
		Splashes[ImageIdx::DigiPen].Load(FP::LOGOS::DigipenWhite, splashWidth, splashHeight, ScreenMid);

	Splashes[ImageIdx::FMod].Load(FP::LOGOS::FMod, splashWidth, splashHeight, ScreenMid);
}
void Splash::Unload() {
	splash.Free();
	for (size_t i = 0; i < Splashes.size(); ++i) {
		Splashes[i].Free();
	}
}