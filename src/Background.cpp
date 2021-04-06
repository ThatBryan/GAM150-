/******************************************************************************/
/*!
\file		Background.cpp
\author 	Bryan Koh Yan Wei
\par    	email: yanweibryan.koh@digipen.edu
\date   	April 6, 2021
\brief		Function definitions for the background display during gameplay.

			Functionalities includes:
			Loading & initializing of Background overlay.

			Spawning of particles on player victory.

			Lerping of background color to simulate a morning to night cycle.


All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.

 */
 /******************************************************************************/
#include "Background.h"
#include "Globals.h"
#include "Image.h"
#include "Button.h"
#include "Utilities.h"
#include "Player.h"
#include "MainMenu.h"
#include "AEEngine.h"
#include "LevelSystem.h"
#include "Particles.h"

#include <array>
#include <vector>

enum ImageIndex{ Pause = 0, Victory, Defeat, MAX_IMAGE };

static std::array <Image, MAX_IMAGE> Images;
static std::vector<Button> MenuBtn;	Graphics::Text text;

static AEVec2 Midpt;
static Color Scene;

enum class SceneType { Day = 0, Noon, Night, Max};
static Color SceneColors [static_cast<int>(SceneType::Max)];

SceneType& operator++(SceneType& rhs) {
	rhs = (rhs == SceneType::Night) ? SceneType::Day : SceneType((int)rhs + 1);
	return rhs;
}

void Background::Load()
{
	Images[Pause].Init(FP::PauseOverlay, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());
	Images[Victory].Init(FP::VictoryOverlay, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());
	Images[Defeat].Init(FP::GameoverOverlay, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());

	SceneColors[static_cast<int>(SceneType::Day)] = Color{ 51.0f, 215.0f, 255.0f, 255.0f };
	SceneColors[static_cast<int>(SceneType::Noon)] = Color{ 255.0f, 175.0f, 51.0f, 255.0f };
	SceneColors[static_cast<int>(SceneType::Night)] = Color{ 100.0f, 149.0f, 237.0f, 255.0f };
}

void Background::Init()
{
	for (int i = 0; i < 4; ++i) {
		MenuBtn.push_back(Button(ButtonType::Color, 150.0f, 75.0f, 0.8f));
	}

	MenuBtn[0].Set_Callback(Utils::ReturnToMenu);
	MenuBtn[0].Set_Text("Menu");

	GAMEPLAY_MISC::Level != 9 ? MenuBtn[1].Set_Text("Next Level") : MenuBtn[1].Set_Text("Menu");
	MenuBtn[1].Set_Callback(LevelSystem::SetNextLevel);
	
	MenuBtn[2].Set_Callback(Utils::ReturnToMenu);
	MenuBtn[2].Set_Text("Menu");
	
	MenuBtn[3].Set_Text("Retry");
	MenuBtn[3].Set_Callback(Utils::RestartLevel);

	Midpt =  Utils::GetScreenMiddle();

	for (int i = 0; i < MenuBtn.size(); ++i) {
		if (i % 2 == 0)
			MenuBtn[i].Set_Position(AEVec2{ Midpt.x + MenuBtn[i].GetWidth(), Midpt.y * 2 - MenuBtn[i].GetHeight() / 2.0f });
		else
			MenuBtn[i].Set_Position(AEVec2{ Midpt.x - MenuBtn[i].GetWidth(), Midpt.y * 2 - MenuBtn[i].GetHeight() / 2.0f });
	}

	text.SetPos(AEVec2Set(Midpt.x, Midpt.y + 100.0f));
	text.SetColor(Color{ 0, 0, 0, 255.0f });
	text.SetScale(1.0f);
	text.SetFontType(fontID::Pixel_Digivolve);
	Scene.Set(SceneColors[static_cast<int>(SceneType::Day)]);
}

void Background::Update()
{
	LerpBackgroundColor();
	AEGfxSetBackgroundColor(Scene.r, Scene.g, Scene.b);
}

void Background::Render(Player& player)
{
	if (!GAMEPLAY_MISC::DISPLAY_QUIT_UI && (GAMEPLAY_MISC::PAUSED && player.active && !player.GetWinStatus()))
	{
		Images[Pause].Draw_Texture(100.0f);
		text.SetText(const_cast<s8*>("PAUSED"));
		text.Draw_Wrapped(text.pos);
	}
	if (player.GetLoseStatus())
	{
		if(!GAMEPLAY_MISC::PAUSED)
			Utils::TogglePause();
		Images[Defeat].Draw_Texture(150.0f);
		text.SetText(const_cast<s8*>("YOU LOSE"));
		text.Draw_Wrapped(text.pos);
		for (int i = 2; i < MenuBtn.size(); ++i) {
			MenuBtn[i].Update();
			MenuBtn[i].Render();
		}
	}
	if (player.GetWinStatus())
	{	
		if (!GAMEPLAY_MISC::PAUSED)
			Utils::TogglePause();
		Images[Victory].Draw_Texture(50.0f);
		text.SetText(const_cast<s8*>("YOU WIN"));
		text.Draw_Wrapped(text.pos);
		for (int i = 0; i < 2; ++i) {
			MenuBtn[i].Update();
			MenuBtn[i].Render();
		}
		const int particleCount{ 50 };
		static float spawnTimer{0.0f};
		spawnTimer -= g_dt;
		if (spawnTimer <= 0) {
			for (int i = 0; i < particleCount; ++i) {
				AEVec2 Emitter = { Utils::RandomRangeFloat(0, static_cast<f32>(AEGetWindowWidth())), Utils::RandomRangeFloat(-20, 0) };
				AEVec2 Vel{ 0, 1 };
				Particles::Create(Emitter, Vel, Color::CreateRandomColor(), 1, Utils::RandomRangeFloat(100, 400), 0, Utils::RandomRangeFloat(10, 30), 2.0f);
				spawnTimer = 1.0f;
			}
		}
	}
}

void Background::Unload()
{
	for (size_t i = 0; i < Images.size(); ++i) {
		Images[i].Free();
	}
	MenuBtn.clear();
}
void Background::LerpBackgroundColor(void)
{
	static float t = 0;
	static SceneType Identifier = SceneType::Noon;
	static Color Destination = SceneColors[static_cast<int>(Identifier)];

	if (Scene == Destination) {
		++Identifier;
		Destination = SceneColors[static_cast<int>(Identifier)];
		t = 0;
	}
	Scene = Color::Lerp(Scene, Destination, t);
	static const float LerpFactor{ 0.000005f };
	t += LerpFactor;
}

