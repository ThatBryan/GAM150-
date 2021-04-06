/******************************************************************************/
/*!
\file				UserInterface.cpp
\author: 			Bryan Koh Yan Wei
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Source file for UI related code. (I.e player hp, time 
					elapsed, etc.)

All content © 2021 DigiPen Institute of Technology Singapore. All
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

extern Player Jumperman;

void UI::Init() {

	UI::PausedInit();
	UI::QuitInit();
	FPS_Display.color.Set(Color{ 0, 0, 0, 255 });
	LevelDisplay.color.Set(Color{0, 0, 0, 255});
	TimerDisplay.color.Set(Color{ 0, 0, 0, 255 });

	FPS_Display.SetFontType(fontID::Courier);
	LevelDisplay.SetFontType(fontID::Courier);
	TimerDisplay.SetFontType(fontID::Courier);

	memset(strBuffer, 0, 100 * sizeof(char));
	memset(strBuffer1, 0, 100 * sizeof(char));
	memset(strBuffer2, 0, 100 * sizeof(char));

	lives.Init(FP::HeartSprite, 35.0f, 35.0f, AEVec2Zero());
}

const size_t pauseButtonIdx{ 1 };
void UI::Update() {

	
	GAMEPLAY_MISC::Level == 1 ? sprintf_s(strBuffer1, "Current Level: Tutorial") : 
								sprintf_s(strBuffer1, "Current Level: %d", GAMEPLAY_MISC::Level - 1);

	sprintf_s(strBuffer, "FPS: %.2f", AEFrameRateControllerGetFrameRate());
	sprintf_s(strBuffer2, "Time Elapsed: %.2f", GAMEPLAY_MISC::app_time);

	FPS_Display.SetText(strBuffer);
	LevelDisplay.SetText(strBuffer1);
	TimerDisplay.SetText(strBuffer2);

	Utils::ToggleDebugMode();

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

	const size_t btnCount{6};
	const float BtnHeight{ 50.0f }, BtnWidth{ 150.0f };
	static const float WindHeight{ static_cast<float>(AEGetWindowHeight()) };
	for (size_t i = 0; i < btnCount; ++i) {
		PausedBtn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, 0.45f));
	}
	PausedBtn[0].Set_Callback(Utils::TogglePause);
	PausedBtn[0].Set_Text("Resume");

	PausedBtn[1].Set_Callback(AudioManager::ToggleMuteAll);
	PausedBtn[2].Set_Callback(Utils::ToggleFullscreen);

	PausedBtn[3].Set_Text("Exit to Main Menu");
	PausedBtn[3].Set_Callback(Utils::ReturnToMenu);

	PausedBtn[4].Set_Text("Quit Game");
	PausedBtn[4].Set_Callback(Utils::ToggleQuitUI);

	PausedBtn[5].Set_Text("Restart Level");
	PausedBtn[5].Set_Callback(Utils::RestartLevel);


	const float PosY{ WindHeight - BtnHeight / 2.0f };

	for (size_t i = 0; i < btnCount - 2; ++i) {
		PausedBtn[i].Set_Position(AEVec2Set(BtnWidth / 4.0f + BtnWidth / 2.0f + BtnWidth * i * 1.3f, PosY - BtnHeight * 1.2f ));
	}

	PausedBtn[4].Set_Position(AEVec2Set(PausedBtn[2].GetPosX(), PosY));
	PausedBtn[5].Set_Position(AEVec2Set(PausedBtn[1].GetPosX(), PosY));
}

void UI::PausedUpdate()
{
	AudioManager::GetGlobalMute() == true ? PausedBtn[1].Set_Text("Unmute") : PausedBtn[1].Set_Text("Mute");
	Utils::GetFullscreenStatus() == true ? PausedBtn[2].Set_Text("Windows Mode") : PausedBtn[2].Set_Text("Fullscreen");

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
	const float BtnHeight{ 50.0f }, BtnWidth{ 150.0f };
	for (size_t i = 0; i < QuitBtnCount; ++i) {
		QuitBtn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, 0.7f));
	}
	QuitBtn[0].Set_Text("Cancel");
	QuitBtn[0].Set_Callback(Utils::ToggleQuitUI);
	QuitBtn[0].Set_Position(AEVec2Set(ScreenMid.x - BtnWidth, ScreenMid.y + 50.0f));

	QuitBtn[1].Set_Text("Quit");
	QuitBtn[1].Set_Callback(Utils::ExitGame);
	QuitBtn[1].Set_Position(AEVec2Set(ScreenMid.x + BtnWidth, ScreenMid.y + 50.0f));

	QuitText.SetText("Do you want to exit the game?");
	QuitText.SetFontType(fontID::Roboto);
	QuitText.SetColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	QuitText.SetScale(1.0f);
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
	QuitText.Draw_Wrapped(AEVec2Set(ScreenMid.x, ScreenMid.y - 50.0f));
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
