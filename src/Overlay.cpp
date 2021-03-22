#include "Overlay.h"
#include <array>
#include "Image.h"
#include "Button.h"
#include "Utilities.h"
#include "Player.h"
#include <vector>
#include "MainMenu.h"
#include "AEEngine.h"
#include "LevelSystem.h"

enum { Pause = 0, Victory, Defeat, MAX_IMAGE };

static std::array <Image, MAX_IMAGE> Images;
static std::vector<Button> buttons;

static AEVec2 Midpt;

void Overlay::Load()
{
	Images[Pause].Init(FP::PauseOverlay, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());
	Images[Victory].Init(FP::VictoryOverlay, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());
	Images[Defeat].Init(FP::GameoverOverlay, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());
}

void Overlay::Init()
{
	for (int i = 0; i < 4; ++i) {
		buttons.push_back(Button(ButtonType::Color, 150.0f, 75.0f, 0.8f));
	}

	buttons[0].Set_Callback(Utils::ReturnToMenu);
	buttons[0].Set_Text("Menu");


	buttons[1].Set_Text("Next Level");
	buttons[1].Set_Callback(LevelSystem::SetNextLevel);
	
	buttons[2].Set_Callback(Utils::ReturnToMenu);
	buttons[2].Set_Text("Menu");
	
	buttons[3].Set_Text("Retry");
	buttons[3].Set_Callback(Utils::RestartLevel);

	Midpt =  Utils::GetScreenMiddle();

	for (int i = 0; i < buttons.size(); ++i) {
		if (i % 2 == 0)
			buttons[i].Set_Position(AEVec2{ Midpt.x + buttons[i].GetWidth(), Midpt.y * 2 - buttons[i].GetHeight() / 2.0f });
		else
			buttons[i].Set_Position(AEVec2{ Midpt.x - buttons[i].GetWidth(), Midpt.y * 2 - buttons[i].GetHeight() / 2.0f });
	}

}

void Overlay::Update()
{
}

void Overlay::Render(Player& player)
{
	Graphics::Text text;
	text.SetPos(Utils::GetScreenMiddle());
	text.SetColor(Color{ 0, 0, 0, 255.0f });
	text.SetScale(2.0f);

	if (paused && player.active && !player.GetWinStatus())
	{
		Images[Pause].Draw_Texture(100.0f);
		text.SetText(const_cast<s8*>("PAUSED"));
		text.Draw_Wrapped(text.pos);
	}
	if (player.GetLose())
	{
		paused = true;
		Images[Defeat].Draw_Texture(150.0f);
		text.SetText(const_cast<s8*>("YOU LOSE"));
		text.Draw_Wrapped(text.pos);
		for (int i = 2; i < buttons.size(); ++i) {
			buttons[i].Update();
		}
	}
	if (player.GetWinStatus())
	{
		paused = true;
		Images[Victory].Draw_Texture(100.0f);
		text.SetText(const_cast<s8*>("YOU WIN"));
		text.Draw_Wrapped(text.pos);
		for (int i = 0; i < 2; ++i) {
			buttons[i].Update();
		}
	}
}

void Overlay::Unload()
{
	for (size_t i = 0; i < Images.size(); ++i) {
		Images[i].Free();
	}
	buttons.clear();
}

