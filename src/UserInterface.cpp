#include "UserInterface.h"
#include <fstream>
#include "AEEngine.h"
#include "Graphics.h"
#include "Constants.h"
#include "Utilities.h"
#include <string>
#include <vector>
#include <array>
#include "Button.h"
#include "Image.h"
#include "MainMenu.h"
#include "Player.h"

char strBuffer[100];
char strBuffer1[100];
char strBuffer2[100];
Graphics::Text FPS_Display(strBuffer, 0.5f);
Graphics::Text LevelDisplay(strBuffer1, 0.5f);
Graphics::Text TimerDisplay(strBuffer2, 0.5f);

static std::vector <Button> PausedBtn;
static std::vector <Button> QuitBtn;
static Graphics::Text QuitText;
static AEVec2 ScreenMid;
extern Player Jumperman;
Image lives;

void UI::Init() {

	UI::PausedInit();
	UI::QuitInit();

	FPS_Display.color.Set(Color{ 0, 0, 0, 255 });
	LevelDisplay.color.Set(Color{0, 0, 0, 255});
	TimerDisplay.color.Set(Color{ 0, 0, 0, 255 });

	memset(strBuffer, 0, 100 * sizeof(char));
	memset(strBuffer1, 0, 100 * sizeof(char));
	memset(strBuffer2, 0, 100 * sizeof(char));

	lives.Init(FP::HeartSprite, 35.0f, 35.0f, AEVec2Zero());
}

const size_t pauseButtonIdx{ 1 };
void UI::Update() {

	sprintf_s(strBuffer, "FPS: %.2f", AEFrameRateControllerGetFrameRate());
	sprintf_s(strBuffer1, "Current Level: %d", Level);
	sprintf_s(strBuffer2, "Time Elapsed: %.2f", app_time);

	FPS_Display.SetText(strBuffer);
	LevelDisplay.SetText(strBuffer1);
	TimerDisplay.SetText(strBuffer2);

	Utils::CheckDebugMode();

	if (paused && !Jumperman.GetWinStatus() && !Jumperman.GetLoseStatus())
		UI::PausedUpdate();

	UI::Draw();
}

void UI::Draw() {
	AEVec2 Pos0{ FPS_Display.GetBufferSize() };
	FPS_Display.Draw_Wrapped(AEVec2Set(Pos0.x / 2.0f, 80.0f + Pos0.y / 2.0f) );
	//if (DebugMode)
	AEVec2 Pos{ LevelDisplay.GetBufferSize() };
	AEVec2 Pos2{ TimerDisplay.GetBufferSize() };

	TimerDisplay.Draw_Wrapped(AEVec2Set(AEGetWindowWidth() - Pos2.x / 2.0f, Pos2.y / 2.0f));
	LevelDisplay.Draw_Wrapped(AEVec2Set(Pos.x / 2.0f, Pos.y / 2.0f));

	if (paused && !Jumperman.GetWinStatus() && !Jumperman.GetLoseStatus())
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

	const size_t btnCount{5};
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
	PausedBtn[4].Set_Position(AEVec2Set(ScreenMid.x, WindHeight - BtnHeight / 2.0f));
	PausedBtn[4].Set_Callback(Utils::ToggleQuitUI);

	const float PosY{ PausedBtn[4].GetPosY() };
	std::cout << "PosY: " << PosY << std::endl;
	for (size_t i = 0; i < btnCount - 1; ++i) {
		PausedBtn[i].Set_Position(AEVec2Set(BtnWidth / 4.0f + BtnWidth / 2.0f + BtnWidth * i * 1.3f, PosY - BtnHeight * 1.2f ));
	}

}

void UI::PausedUpdate()
{
	AudioManager::GetGlobalMute() == true ? PausedBtn[1].Set_Text("Unmute") : PausedBtn[1].Set_Text("Mute");
	Utils::GetFullscreenStatus() == true ? PausedBtn[2].Set_Text("Windows Mode") : PausedBtn[2].Set_Text("Fullscreen");

	if (!DisplayQuitUI) {
		for (size_t i = 0; i < PausedBtn.size(); ++i) {
			PausedBtn[i].Update();
		}
	}

	if (DisplayQuitUI)
		UI::QuitUpdate();
}

void UI::PausedRender()
{
	if (!DisplayQuitUI) {
		for (size_t i = 0; i < PausedBtn.size(); ++i) {
			PausedBtn[i].Render();
		}
	}
	if (DisplayQuitUI)
		UI::QuitRender();
}

void UI::PausedUnload()
{
	PausedBtn.clear();
}

void UI::QuitInit()
{
	const size_t QuitBtnCount{ 2 };
	const float BtnHeight{ 50.0f }, BtnWidth{ 150.0f };
	for (size_t i = 0; i < QuitBtnCount; ++i) {
		QuitBtn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, 0.7f));
	}
	QuitBtn[0].Set_Text("Cancel");
	QuitBtn[0].Set_Callback(Utils::ToggleQuitUI);
	QuitBtn[0].Set_Position(AEVec2Set(ScreenMid.x - BtnWidth, 300.0f));

	QuitBtn[1].Set_Text("Quit");
	QuitBtn[1].Set_Callback(Utils::ExitGame);
	QuitBtn[1].Set_Position(AEVec2Set(ScreenMid.x + BtnWidth, 300.0f));

	QuitText.SetText("Do you want to exit?");
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
	QuitText.Draw_Wrapped(AEVec2Set(ScreenMid.x, ScreenMid.y - 100.0f));
}

void UI::QuitUnload()
{
	QuitBtn.clear();
}


void UI::Unload()
{
	lives.Free();
	UI::PausedUnload();
	UI::QuitUnload();
}
