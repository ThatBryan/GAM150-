#include "MainMenu.h"
#include "Image.h"
#include "Utilities.h"
#include "Constants.h"
#include <array>
#include "Graphics.h"
enum { GGPen = 0, MAX_IMAGE };
static std::array <Image, MAX_IMAGE> Imagess;

void MainMenu::Init(void)
{
	Imagess[GGPen].Init(VictoryScreen, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());
	Load();
}

void MainMenu::Update(void)
{
	Imagess[GGPen].Draw_Texture(255);
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
	for (int i = 0; i < Imagess.size(); ++i) {
		Imagess[i].Free();
	}
}