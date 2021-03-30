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
static AEVec2 ScreenMid;
extern Player Jumperman;
Image lives;

void UI::Init() {

	UI::PausedInit();

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
	const size_t btnCount{4};
	const float BtnHeight{ 50.0f }, BtnWidth{ 150.0f };
	for (size_t i = 0; i < btnCount; ++i) {
		PausedBtn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, 0.45f));
	}
	PausedBtn[0].Set_Callback(Utils::TogglePause);
	PausedBtn[0].Set_Text("Resume");


	PausedBtn[1].Set_Callback(AudioManager::ToggleMuteAll);
	PausedBtn[2].Set_Callback(Utils::ToggleFullscreen);

	PausedBtn[3].Set_Text("Exit to Main Menu");
	PausedBtn[3].Set_Callback(Utils::ReturnToMenu);


	ScreenMid = Utils::GetScreenMiddle();
	for (size_t i = 0; i < btnCount; ++i) {
		PausedBtn[i].Set_Position(AEVec2Set(BtnWidth / 4.0f + BtnWidth / 2.0f + BtnWidth * i * 1.3f, ScreenMid.y + 2 * BtnHeight));
	}
}

void UI::PausedUpdate()
{
	AudioManager::GetGlobalMute() == true ? PausedBtn[1].Set_Text("Unmute") : PausedBtn[1].Set_Text("Mute");
	Utils::GetFullscreen() == true ? PausedBtn[2].Set_Text("Windows Mode") : PausedBtn[2].Set_Text("Fullscreen");

	for (size_t i = 0; i < PausedBtn.size(); ++i) {
		PausedBtn[i].Update();
	}
}

void UI::PausedRender()
{
	for (size_t i = 0; i < PausedBtn.size(); ++i) {
		PausedBtn[i].Render();
	}
}

void UI::PausedUnload()
{
	PausedBtn.clear();
}


void UI::Unload()
{
	lives.Free();
	UI::PausedUnload();
}
