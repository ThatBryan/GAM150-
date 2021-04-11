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
#include "Leaderboard.h"
#include "LevelSystem.h"
#include "GameMode.h"
#include "Username.h"

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
static Color SceneColor, LerpColorDestination;
static SceneType CurrentScene, NextScene;

static float  WindowWidth, WindowHeight, tLerp;
static bool isScoreInserted;

static GameMode gameMode;

extern LevelSystem LevelSys;

SceneType& operator++(SceneType& rhs) {
	rhs = (rhs == SceneType::Night) ? SceneType::Day : SceneType((int)rhs + 1);
	return rhs;
}

void Background::Load()
{
	ObjectsLoad();

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

	if (GAMEPLAY_MISC::Level == LevelSys.GetMaxLevel() - 1)
		MenuBtn[0].Set_Position(AEVec2Set(Midpt.x, WindowHeight - MenuBtn[0].GetHeight() / 2.0f));

	const float TextPosYOffset{ 100.0f }, TitleTextScale{ 0.9f };

	text.SetPos(AEVec2Set(Midpt.x, Midpt.y + TextPosYOffset));
	text.SetTextColor(Color{ 0, 0, 0, Color::RGBA_MAX });
	text.SetTextScale(TitleTextScale);
	text.SetFontID(fontID::Pixel_Digivolve);

	BgOverlayArr[BackgroundIndex::Pause].Load(FP::BACKGROUND::Pause, WindowWidth, WindowHeight, Midpt);
	BgOverlayArr[BackgroundIndex::Victory].Load(FP::BACKGROUND::Victory, WindowWidth, WindowHeight, Midpt);
	BgOverlayArr[BackgroundIndex::Defeat].Load(FP::BACKGROUND::Gameover, WindowWidth, WindowHeight, Midpt);
}

void Background::Init()
{
	ObjectsInit();
	isScoreInserted = false;
	gameMode = GameModeSetting::GetGameMode();

	if (gameMode == GameMode::TimeAttack)
		MenuBtn[2].Set_Position(AEVec2Set(Midpt.x, WindowHeight - MenuBtn[2].GetHeight() / 2.0f));
}

void Background::Update()
{
	LerpBackgroundColor();
	ObjectsUpdate();
}

void Background::Render(const Player& player)
{
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

		if (gameMode == GameMode::Casual)
			RenderCasual();
		else
			RenderTimeAttack();

	}
	else if (player.GetWinStatus())
	{	
		if (!GAMEPLAY_MISC::PAUSED)
			Utils::TogglePause();
		BgOverlayArr[BackgroundIndex::Victory].Draw_Texture(50.0f);
		text.Draw_Wrapped(text.pos);

		GAMEPLAY_MISC::Level == LevelSys.GetMaxLevel() - 1 ? 
			text.SetText(const_cast<s8*>("Congratulations!! you beat the game!"))
		  : text.SetText(const_cast<s8*>("YOU WIN"));
		
		if (gameMode == GameMode::TimeAttack && GAMEPLAY_MISC::Level == 8)
		{
			text.Draw_Wrapped({ text.pos.x, text.pos.y - 120.0f });
			text.SetText("YOUR SCORE: ");
			text.Draw_Wrapped({ text.pos.x, text.pos.y - 50.0f });
			int time_remaining = static_cast<int>(GAMEPLAY_MISC::TimeAttack_remaining);
			text.SetText(std::to_string(time_remaining));

			Leaders L = Leaderboard::GetLastPlacement();

			if (!isScoreInserted && L.score < GAMEPLAY_MISC::TimeAttack_remaining)
			{
				Leaders newleader;
				newleader.name = Username::GetUsername();
				newleader.score = static_cast<int>(GAMEPLAY_MISC::TimeAttack_remaining);
				L.InsertNewLeader(newleader);
				isScoreInserted = true;
			}
		}
		

		int btnNum; // Only update one button at level 8 since last level.

		GAMEPLAY_MISC::Level == LevelSys.GetMaxLevel() - 1 ? btnNum = 1 
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

void Background::RenderCasual()
{
	BgOverlayArr[BackgroundIndex::Defeat].Draw_Texture(150.0f);
	text.SetText(const_cast<s8*>("YOU LOSE"));
	text.Draw_Wrapped(text.pos);
	for (int i = 2; i < MenuBtn.size(); ++i) {
		MenuBtn[i].Update();
		MenuBtn[i].Render();
	}

}

void Background::RenderTimeAttack()
{
	BgOverlayArr[BackgroundIndex::Defeat].Draw_Texture(150.0f);
	text.SetText(const_cast<s8*>("TIME ATTACK MODE FAIL"));
	text.Draw_Wrapped(text.pos);
	MenuBtn[2].Update();
	MenuBtn[2].Render();
}

void Background::Unload()
{
	for (size_t i = 0; i < BgOverlayArr.size(); ++i) {
		BgOverlayArr[i].Free();
	}
	ObjectsUnload();
	MenuBtn.clear();
}
void Background::LerpBackgroundColor(void)
{
	static const float LerpFactor{ 0.000005f }; // per t increment
	LerpColorDestination = SceneColors[static_cast<int>(NextScene)];

	if (SceneColor == LerpColorDestination) {
		++NextScene;
		++CurrentScene;

		LerpColorDestination = SceneColors[static_cast<int>(NextScene)];
		tLerp = 0;
	}
	SceneColor = Color::Lerp(SceneColor, LerpColorDestination, tLerp);
	tLerp += LerpFactor;

	AEGfxSetBackgroundColor(SceneColor.r, SceneColor.g, SceneColor.b);
}

void Background::ObjectsInit()
{
	SceneColor.Set(SceneColors[static_cast<int>(SceneType::Day)]);
	tLerp = 0.0f;
	CurrentScene = SceneType::Day;
	NextScene = SceneType::SunSet;
}

void Background::ObjectsLoad()
{
	Midpt = Utils::GetScreenMiddle();
	WindowWidth = static_cast<f32>(AEGetWindowWidth());
	WindowHeight = static_cast<f32>(AEGetWindowHeight());

	for (int i = 0; i < LastCloudIdx; ++i) {
		BgObj[i].Load("./Assets/Art/cloud.png", Utils::RandomRangeFloat(50.0f, 100.0f), Utils::RandomRangeFloat(20.0f, 40.0f),
			AEVec2Set(i * 100.0f + Utils::RandomRangeFloat(-50.0f, 50.0f), Utils::RandomRangeFloat(25.0f, 50.0f)));
	}
	BgObj[5].Load("./Assets/Art/moon.png", 50.0f, 50.0f, AEVec2{ 40, 30.0f });
	BgObj[6].Load("./Assets/Art/moon.png", 50.0f, 50.0f, AEVec2{ 760, 30.0f });
	BgObj[6].ReflectAboutYAxis();

	SceneColors[static_cast<int>(SceneType::Day)] = Color{ 51.0f, 215.0f, 255.0f, 255.0f };
	SceneColors[static_cast<int>(SceneType::SunSet)] = Color{ 255.0f, 175.0f, 51.0f, 255.0f };
	SceneColors[static_cast<int>(SceneType::Night)] = Color{ 100.0f, 149.0f, 237.0f, 255.0f };
}

void Background::ObjectsUpdate()
{
	static AEVec2 CloudDir{ -1.0f, 0.0f };
	static const float CloudSpeed{ 50.0f };

	if (!GAMEPLAY_MISC::PAUSED) {
		for (int i = 0; i < LastCloudIdx; ++i) {
			AEVec2ScaleAdd(&BgObj[i].pos, &CloudDir, &BgObj[i].pos, g_dt * CloudSpeed);
			BgObj[i].pos.x = AEWrap(BgObj[i].pos.x, -BgObj[i].width / 2.0f, WindowWidth + BgObj[i].width / 2.0f);
		}
	}
}

void Background::ObjectsRender()
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
}

void Background::ObjectsUnload()
{
	for (size_t i = 0; i < BgObj.size(); ++i) {
		BgObj[i].Free();
	}
}
