#include <vector>
#include "Splash.h"
#include "Utilities.h"
#include "Image.h"
#include "Constants.h"
#include "GameStateManager.h"
#include "AEEngine.h"

Image splash;
static float splashLife, alpha;
const float splashDuration = 3.0f;

void Splash::Init() {
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	if (Utils::RandomRangeInt(0, 1))
		splash.Init(DigipenLogoRed, 800.0f, 194.0f,Utils::GetScreenMiddle());
	else
		splash.Init(DigipenLogoWhite, 800.0f, 194.0f, Utils::GetScreenMiddle());

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
	rectMesh = Graphics::Mesh_Rectangle();
}
void Splash::Unload() {
	splash.Free();
}