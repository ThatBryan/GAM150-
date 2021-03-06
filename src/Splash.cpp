#include <vector>
#include "Splash.h"
#include "Utilities.h"
#include "Image.h"
#include "Constants.h"
#include "GameStateManager.h"
#include "AEEngine.h"

std::vector <Image> splash;
static float splashDuration, alpha;

void Splash::Init() {
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	splash.push_back(Image());
	if (Utils::RandomRangeInt(0, 1))
		splash[0].Init(DigipenLogoRed, 800.0f, 194.0f,Utils::GetScreenMiddle());
	else
		splash[0].Init(DigipenLogoWhite, 800.0f, 194.0f, Utils::GetScreenMiddle());

	splashDuration = 3.0f;
	alpha = 255.0f;
}
void Splash::Update() {
	splashDuration -= g_dt;
	alpha = (splashDuration / 3.0f) * 255.0f;
	if (splashDuration <= 0) {
		gamestateNext = GS_MAINMENU;
	}
}
void Splash::Render() {
	splash[0].Draw_Texture(alpha);
}
void Splash::Load() {
	rectMesh = Graphics::Mesh_Rectangle();
}
void Splash::Unload() {
	splash[0].Free();
}
void Splash::Free() {

}