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

#include <vector>

Image splash;


static float splashLife, alpha;
static const float splashDuration = 3.0f;

void Splash::Init() {
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	if (Utils::RandomRangeInt(0, 1))
		splash.Init(FP::DigipenLogoRed, 800.0f, 194.0f,Utils::GetScreenMiddle());
	else
		splash.Init(FP::DigipenLogoWhite, 800.0f, 194.0f, Utils::GetScreenMiddle());

	splashLife = splashDuration;
	alpha = 255.0f;
}
void Splash::Update() {
	splashLife -= g_dt;
	alpha = (splashLife / splashDuration) * 255.0f;
	if (splashLife <= 0) {
		gamestateNext = GS_MAINMENU;
	}
}
void Splash::Render() {
	splash.Draw_Texture(alpha);
}
void Splash::Load() {

}
void Splash::Unload() {
	splash.Free();
}