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

enum BackgroundIndex{ Pause = 0, Victory, Defeat, Overlay_Max };

static std::array <Image, BackgroundIndex::Overlay_Max> BgOverlayArr;

enum BackgroundObj{Cloud = 0, MAX};
static const int BgObjMax{ 7 }, LastCloudIdx{ 5 };

static std::array <Image, BgObjMax> BgObj;
static std::vector<Button> MenuBtn;	
static Graphics::Text text;

static AEVec2 Midpt;

enum class SceneType { Day = 0, SunSet, Night, Max};
static Color SceneColors [static_cast<int>(SceneType::Max)];
static Color Scene, LerpDestination;
static SceneType CurrentScene;

static float  WindowWidth, WindowHeight, tLerp;

SceneType& operator++(SceneType& rhs) {
	rhs = (rhs == SceneType::Night) ? SceneType::Day : SceneType((int)rhs + 1);
	return rhs;
}

void Background::Load()
{
	Midpt = Utils::GetScreenMiddle();
	WindowWidth = static_cast<f32>(AEGetWindowWidth());
	WindowHeight = static_cast<f32>(AEGetWindowHeight());

	BgOverlayArr[BackgroundIndex::Pause].Init(FP::PauseOverlay, WindowWidth, WindowHeight, Midpt);
	BgOverlayArr[BackgroundIndex::Victory].Init(FP::VictoryOverlay, WindowWidth, WindowHeight, Midpt);
	BgOverlayArr[BackgroundIndex::Defeat].Init(FP::GameoverOverlay, WindowWidth, WindowHeight, Midpt);

	for (int i = 0; i < LastCloudIdx; ++i) {
		BgObj[i].Init("./Assets/Art/cloud.png", Utils::RandomRangeFloat(50.0f, 100.0f), Utils::RandomRangeFloat(20.0f, 40.0f),
			AEVec2Set(i * 100.0f + Utils::RandomRangeFloat(-50.0f, 50.0f), Utils::RandomRangeFloat(25.0f, 50.0f)));
	}
	BgObj[5].Init("./Assets/Art/moon.png", 50.0f, 50.0f, AEVec2{ 40, 30.0f });
	BgObj[6].Init("./Assets/Art/moon.png", 50.0f, 50.0f, AEVec2{ 760, 30.0f });
	BgObj[6].ReflectAboutYAxis();

	SceneColors[static_cast<int>(SceneType::Day)] = Color{ 51.0f, 215.0f, 255.0f, 255.0f };
	SceneColors[static_cast<int>(SceneType::SunSet)] = Color{ 255.0f, 175.0f, 51.0f, 255.0f };
	SceneColors[static_cast<int>(SceneType::Night)] = Color{ 100.0f, 149.0f, 237.0f, 255.0f };
}

void Background::Init()
{
	const int BtnCount{ 4 };
	const float BtnWidth{ 150.0f }, BtnHeight{ 75.0f }, BtnTextScale{ 0.8f };

	for (int i = 0; i < BtnCount; ++i) {
		MenuBtn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, BtnTextScale));
	}

	MenuBtn[0].Set_Callback(Utils::ReturnToMenu);
	MenuBtn[0].Set_Text("Menu");

	GAMEPLAY_MISC::Level != 9 ? MenuBtn[1].Set_Text("Next Level") 
							  : MenuBtn[1].Set_Text("Menu");

	MenuBtn[1].Set_Callback(LevelSystem::SetNextLevel);
	
	MenuBtn[2].Set_Callback(Utils::ReturnToMenu);
	MenuBtn[2].Set_Text("Menu");
	
	MenuBtn[3].Set_Text("Retry");
	MenuBtn[3].Set_Callback(Utils::RestartLevel);

	for (int i = 0; i < MenuBtn.size(); ++i) {
		if (i % 2 == 0)
			MenuBtn[i].Set_Position(AEVec2{ Midpt.x + BtnWidth, Midpt.y * 2 - BtnHeight / 2.0f });
		else
			MenuBtn[i].Set_Position(AEVec2{ Midpt.x - BtnWidth, Midpt.y * 2 - BtnHeight / 2.0f });
	}

	if (GAMEPLAY_MISC::Level == 9)
		MenuBtn[0].Set_Position(AEVec2Set(Midpt.x, WindowHeight - BtnHeight / 2.0f));
	
	const float TextPosYOffset{ 100.0f }, TitleTextScale{ 0.9f };

	text.SetPos(AEVec2Set(Midpt.x, Midpt.y + TextPosYOffset));
	text.SetTextColor(Color{ 0, 0, 0, Color::RGBA_MAX});
	text.SetTextScale(TitleTextScale);
	text.SetFontID(fontID::Pixel_Digivolve);
	Scene.Set(SceneColors[static_cast<int>(SceneType::Day)]);

	CurrentScene = SceneType::Day;
	tLerp = 0.0f;
}

void Background::Update()
{
	static AEVec2 CloudDir{ -1.0f, 0.0f };
	static const float CloudSpeed{ 50.0f };

	LerpBackgroundColor();
	AEGfxSetBackgroundColor(Scene.r, Scene.g, Scene.b);

	if (!GAMEPLAY_MISC::PAUSED) {
		for (int i = 0; i < LastCloudIdx; ++i) {
			AEVec2ScaleAdd(&BgObj[i].pos, &CloudDir, &BgObj[i].pos, g_dt * CloudSpeed);
			BgObj[i].pos.x = AEWrap(BgObj[i].pos.x, - BgObj[i].width / 2.0f, WindowWidth + BgObj[i].width / 2.0f);
		}
	}
}

void Background::Render(const Player& player)
{
	static const float CloudAlpha{ 100.0f };
	for (size_t i = 0; i < LastCloudIdx; ++i) {
		BgObj[i].Draw_Texture(BgObj[i].pos, CloudAlpha);
	}
	if (CurrentScene != SceneType::Day) {
		for (size_t i = LastCloudIdx; i < BgObj.size(); ++i) {
			BgObj[i].Draw_Texture(BgObj[i].pos, CloudAlpha);
		}
	}

	if (!GAMEPLAY_MISC::DISPLAY_QUIT_UI && (GAMEPLAY_MISC::PAUSED && player.active && !player.GetWinStatus()))
	{
		BgOverlayArr[BackgroundIndex::Pause].Draw_Texture(100.0f);
		text.SetText(const_cast<s8*>("PAUSED"));
		text.Draw_Wrapped(text.pos);
	}
	else if (player.GetLoseStatus())
	{
		if(!GAMEPLAY_MISC::PAUSED)
			Utils::TogglePause();

		BgOverlayArr[BackgroundIndex::Defeat].Draw_Texture(150.0f);
		text.SetText(const_cast<s8*>("YOU LOSE"));
		text.Draw_Wrapped(text.pos);
		for (int i = 2; i < MenuBtn.size(); ++i) {
			MenuBtn[i].Update();
			MenuBtn[i].Render();
		}
	}
	else if (player.GetWinStatus())
	{	
		if (!GAMEPLAY_MISC::PAUSED)
			Utils::TogglePause();
		BgOverlayArr[BackgroundIndex::Victory].Draw_Texture(50.0f);
		text.Draw_Wrapped(text.pos);

		GAMEPLAY_MISC::Level == 9 ? text.SetText(const_cast<s8*>("Congratulations!! you beat the game!")) 
								  : text.SetText(const_cast<s8*>("YOU WIN"));
		
		text.Draw_Wrapped({ text.pos.x, text.pos.y - 50.0f });
		text.SetText("YOUR SCORE: ");
		text.Draw_Wrapped({ text.pos.x, text.pos.y - 100.0f });
		text.SetText(std::to_string(player.GetScore()));

		int btnNum; // Only update one button at level 9 since last level.

		GAMEPLAY_MISC::Level == 9 ? btnNum = 1 
								  : btnNum = 2;

		for (int i = 0; i < btnNum; ++i) {
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
	} // end if player win
}

void Background::Unload()
{
	for (size_t i = 0; i < BgOverlayArr.size(); ++i) {
		BgOverlayArr[i].Free();
	}

	for (size_t i = 0; i < BgObj.size(); ++i) {
		BgObj[i].Free();
	}

	MenuBtn.clear();
}
void Background::LerpBackgroundColor(void)
{
	
	static const float LerpFactor{ 0.000005f }; // per t increment
	static SceneType nextScene = SceneType::SunSet;
	LerpDestination = SceneColors[static_cast<int>(nextScene)];

	if (Scene == LerpDestination) {
		++nextScene;
		++CurrentScene;

		LerpDestination = SceneColors[static_cast<int>(nextScene)];
		tLerp = 0;
	}
	Scene = Color::Lerp(Scene, LerpDestination, tLerp);
	tLerp += LerpFactor;
}