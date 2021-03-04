#include "MainMenu.h"
#include "Image.h"
#include "Constants.h"
#include <array>
#include "Graphics.h"
#include "Utilities.h"

enum {Victory = 0, MAX_IMAGE };
static std::array <Image, MAX_IMAGE> Images;
std::vector <Button> buttons;

void MainMenu::Init(void)
{
	Load();
	Images[Victory].Init(VictoryScreen, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());
	Buttons_Init();
}

void MainMenu::Update(void)
{
	Images[Victory].Draw_Texture(255);
	DrawButtons();
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

void MainMenu::Buttons_Init(void) 
{
	buttons.push_back(Button(100.0, 50.0f, 0.9f));
	buttons[0].Set_Position(Utils::GetScreenMiddle());
	buttons[0].Set_Callback(Test_Callback);
	buttons[0].Set_Text("Pause");

	buttons.push_back(Button(100.0, 50.0f, 0.7f));
	buttons[1].Set_Position(AEVec2{ 500.0f, 25.0f });
	buttons[1].Set_Callback(Mute_BGM);
	buttons[1].Set_Text("Mute BGM");
}

void MainMenu::DrawButtons(void)
{
	for (size_t i = 0; i < buttons.size(); ++i) {
		buttons[i].Update();
	}
}