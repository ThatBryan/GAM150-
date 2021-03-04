#include "MainMenu.h"
#include "Image.h"
#include "Utilities.h"
#include "Constants.h"
#include <array>
#include "Graphics.h"
enum {Victory = 0, MAX_IMAGE };
static std::array <Image, MAX_IMAGE> Images;

void MainMenu::Init(void)
{
	Load();
	Images[Victory].Init(VictoryScreen, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());
}

void MainMenu::Update(void)
{
	Images[Victory].Draw_Texture(255);
}

void MainMenu::Exit(void)
{
	Unload();
}

void MainMenu::Load(void)
{
	rectMesh = Graphics::Mesh_Rectangle();
}

void MainMenu::Unload(void)
{
	for (int i = 0; i < Images.size(); ++i) {
		Images[i].Free();
	}
}