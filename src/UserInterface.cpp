/******************************************************************************/
/*!
\file				UserInterface.cpp
\author: 			Bryan Koh Yan Wei
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Source file for UI related code. (I.e player hp, time 
					elapsed, etc.)

All content � 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#include "UserInterface.h"
#include "AEEngine.h"
#include "Graphics.h"
#include "Constants.h"
#include "Utilities.h"
#include "Button.h"
#include "Image.h"
#include "MainMenu.h"
#include "Player.h"
#include "Globals.h"
#include "GameMode.h"

#include <fstream>
#include <string>
#include <vector>
#include <array>

static char strBuffer[100];
static char strBuffer1[100];
static char strBuffer2[100];
static Graphics::Text FPS_Display(strBuffer, 0.5f);
static Graphics::Text LevelDisplay(strBuffer1, 0.5f);
static Graphics::Text TimerDisplay(strBuffer2, 0.5f);

static std::vector <Button> PausedBtn;
static std::vector <Button> QuitBtn;
static Graphics::Text QuitText;
static AEVec2 ScreenMid;
static Image lives;
static GameMode gameMode;

extern Player Jumperman;

void UI::Init() {

	UI::PausedInit();
	UI::QuitInit();
	FPS_Display.color.Set(Color{ 0, 0, 0, 255 });
	LevelDisplay.color.Set(Color{0, 0, 0, 255});
	TimerDisplay.color.Set(Color{ 0, 0, 0, 255 });

	FPS_Display.SetFontID(fontID::Courier);
	LevelDisplay.SetFontID(fontID::Courier);
	TimerDisplay.SetFontID(fontID::Courier);

	memset(strBuffer, 0, 100 * sizeof(char));
	memset(strBuffer1, 0, 100 * sizeof(char));
	memset(strBuffer2, 0, 100 * sizeof(char));

	lives.Load(FP::UI::HeartSprite, 35.0f, 35.0f, AEVec2Zero());

	gameMode = GameModeSetting::GetGameMode();
}

void UI::Update() {

	
	GAMEPLAY_MISC::Level == 0 ? sprintf_s(strBuffer1, "Current Level: Tutorial")
							  : sprintf_s(strBuffer1, "Current Level: %d", GAMEPLAY_MISC::Level);

	sprintf_s(strBuffer, "FPS: %.2f", AEFrameRateControllerGetFrameRate());

	if (gameMode == GameMode::TimeAttack) {
		sprintf_s(strBuffer2, "Time Remaining: %.2f", GAMEPLAY_MISC::TimeAttack_remaining);
		if(!GAMEPLAY_MISC::PAUSED && GAMEPLAY_MISC::TimeAttack_remaining >= 0.0f)
			GAMEPLAY_MISC::TimeAttack_remaining -= g_dt;

		TimeAttackGameMode::CheckTimer();
	}
	else
		sprintf_s(strBuffer2, "Time Elapsed: %.2f", GAMEPLAY_MISC::app_time);

	FPS_Display.SetText(strBuffer);
	LevelDisplay.SetText(strBuffer1);
	TimerDisplay.SetText(strBuffer2);

	if (GAMEPLAY_MISC::PAUSED && !Jumperman.GetWinStatus() && !Jumperman.GetLoseStatus())
		UI::PausedUpdate();

	UI::Draw();
}

void UI::Draw() {
	AEVec2 Pos0{ FPS_Display.GetBufferSize() };
	FPS_Display.Draw_Wrapped(AEVec2Set(Pos0.x / 2.0f, 80.0f + Pos0.y / 2.0f) );
	AEVec2 Pos{ LevelDisplay.GetBufferSize() };
	AEVec2 Pos2{ TimerDisplay.GetBufferSize() };

	TimerDisplay.Draw_Wrapped(AEVec2Set(AEGetWindowWidth() - Pos2.x / 2.0f, Pos2.y / 2.0f));
	LevelDisplay.Draw_Wrapped(AEVec2Set(Pos.x / 2.0f, Pos.y / 2.0f));

	if (GAMEPLAY_MISC::PAUSED && !Jumperman.GetWinStatus() && !Jumperman.GetLoseStatus())
		UI::PausedRender();
}

void UI::DisplayLife(short livesCount) {
	for (short i = 0; i < livesCount; ++i) {
		lives.Draw_Texture(AEVec2Set(lives.width / 2.0f + i * 50.0f, 50.0f), 255.0f);
	}
}

void UI::PausedInit()
{
	ScreenMid = Utils::GetScreenMiddle();

	const size_t btnCount{ 6 };
	const float BtnHeight{ 50.0f }, BtnWidth{ 150.0f }, BtnTextScale{ 0.45f };
	static const float WindHeight{ static_cast<float>(AEGetWindowHeight()) };
	for (size_t i = 0; i < btnCount; ++i) {
		PausedBtn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, BtnTextScale));
	}
	PausedBtn[0].Set_Callback(Utils::TogglePause);
	PausedBtn[0].Set_Text("Resume");
	PausedBtn[0].ChangeStateColor(ButtonState::Idle, Color{ 229.0f, 145.0f, 255.0f, 255.0f });

	PausedBtn[1].Set_Callback(AudioManager::ToggleMuteAll);
	PausedBtn[1].ChangeStateColor(ButtonState::Idle, Color{ 229.0f, 145.0f, 255.0f, 255.0f });

	PausedBtn[2].Set_Callback(Utils::ToggleFullscreen);
	PausedBtn[2].ChangeStateColor(ButtonState::Idle, Color{ 229.0f, 145.0f, 255.0f, 255.0f });

	PausedBtn[3].Set_Text("Exit to Main Menu");
	PausedBtn[3].Set_Callback(Utils::ReturnToMenu);
	PausedBtn[3].ChangeStateColor(ButtonState::Idle, Color{ 229.0f, 145.0f, 255.0f, 255.0f });

	PausedBtn[4].Set_Text("Quit Game");
	PausedBtn[4].Set_Callback(Utils::ToggleQuitUI);
	PausedBtn[4].ChangeStateColor(ButtonState::Idle, Color{ 229.0f, 145.0f, 255.0f, 255.0f });

	PausedBtn[5].Set_Text("Restart Level");
	PausedBtn[5].Set_Callback(Utils::RestartLevel);
	PausedBtn[5].ChangeStateColor(ButtonState::Idle, Color{ 229.0f, 145.0f, 255.0f, 255.0f });


	const float PosY{ WindHeight - BtnHeight / 2.0f };
	const float BtnPosXOffset{ 1.3f }, BtnPosYOffset{ 1.2f };
	for (size_t i = 0; i < btnCount - 2; ++i) {
		PausedBtn[i].Set_Position(AEVec2Set(BtnWidth / 4.0f + BtnWidth / 2.0f + BtnWidth * i * BtnPosXOffset,
			PosY - BtnHeight * BtnPosYOffset));
	}

	PausedBtn[4].Set_Position(AEVec2Set(PausedBtn[2].GetPosX(), PosY));
	PausedBtn[5].Set_Position(AEVec2Set(PausedBtn[1].GetPosX(), PosY));
}

void UI::PausedUpdate()
{
	AudioManager::GetGlobalMute() == true ? PausedBtn[1].Set_Text("Unmute") 
										  : PausedBtn[1].Set_Text("Mute");

	Utils::GetFullscreenStatus() == true ? PausedBtn[2].Set_Text("Windows Mode") 
										 : PausedBtn[2].Set_Text("Fullscreen");

	if (!GAMEPLAY_MISC::DISPLAY_QUIT_UI) {
		for (size_t i = 0; i < PausedBtn.size(); ++i) {
			PausedBtn[i].Update();
		}
	}

	if (GAMEPLAY_MISC::DISPLAY_QUIT_UI)
		UI::QuitUpdate();
}

void UI::PausedRender()
{
	if (!GAMEPLAY_MISC::DISPLAY_QUIT_UI) {
		for (size_t i = 0; i < PausedBtn.size(); ++i) {
			PausedBtn[i].Render();
		}
	}
	if (GAMEPLAY_MISC::DISPLAY_QUIT_UI)
		UI::QuitRender();
}

void UI::PausedUnload()
{
	PausedBtn.clear();
}

void UI::QuitInit()
{
	ScreenMid = Utils::GetScreenMiddle();
	const size_t QuitBtnCount{ 2 };
	const float BtnHeight{ 50.0f }, BtnWidth{ 150.0f }, BtnTextScale{ 0.7f },
		BtnYOffset{ 50.0f };

	for (size_t i = 0; i < QuitBtnCount; ++i) {
		QuitBtn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, BtnTextScale));
	}
	QuitBtn[0].Set_Text("Quit");
	QuitBtn[0].ChangeStateColor(ButtonState::Idle, Color{ 255.0f, 0.0f, 0.0f, 255.0f });
	QuitBtn[0].Set_Callback(Utils::ExitGame);
	QuitBtn[0].Set_Position(AEVec2Set(ScreenMid.x - BtnWidth, ScreenMid.y + BtnHeight + BtnYOffset));

	QuitBtn[1].Set_Text("Cancel");
	QuitBtn[1].Set_Callback(Utils::ToggleQuitUI);
	QuitBtn[1].Set_Position(AEVec2Set(ScreenMid.x + BtnWidth, ScreenMid.y + BtnHeight + BtnYOffset));

	QuitText.SetText("Do you want to exit the game?");
	QuitText.SetFontID(fontID::Roboto);
	QuitText.SetTextColor(Color{ 255.0f, 0.0f, 0.0f, 255.0f });
	QuitText.SetTextScale(1.0f);
}

void UI::QuitUpdate()
{
	for (size_t i = 0; i < QuitBtn.size(); ++i) {
		QuitBtn[i].Update();
	}
}

void UI::QuitRender()
{
	for (size_t i = 0; i < QuitBtn.size(); ++i) {
		QuitBtn[i].Render();
	}
	QuitText.Draw_Wrapped(ScreenMid);
}

void UI::QuitUnload()
{
	QuitBtn.clear();
}

void UI::Unload()
{
	lives.Free();
	UI::PausedUnload();
	QuitBtn.clear();
}
