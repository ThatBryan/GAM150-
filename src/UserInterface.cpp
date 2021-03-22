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

static std::vector <Button> buttonTest;

extern Player Jumperman;
Image lives;

void UI::Init() {

	UI::Buttons_Init();

	FPS_Display.color.Set(Color{ 0, 0, 0, 255 });
	LevelDisplay.color.Set(Color{0, 0, 0, 255});
	TimerDisplay.color.Set(Color{ 0, 0, 0, 255 });

	memset(strBuffer, 0, 100 * sizeof(char));
	memset(strBuffer1, 0, 100 * sizeof(char));
	memset(strBuffer2, 0, 100 * sizeof(char));

	lives.Init(FP::HeartSprite, 35.0f, 35.0f, AEVec2Zero());
}

const size_t pauseButtonIdx{ 2 };
void UI::Update() {

	sprintf_s(strBuffer, "FPS: %.2f", AEFrameRateControllerGetFrameRate());
	sprintf_s(strBuffer1, "Current Level: %d", Level);
	sprintf_s(strBuffer2, "Time Elapsed: %.2f", app_time);

	FPS_Display.SetText(strBuffer);
	LevelDisplay.SetText(strBuffer1);
	TimerDisplay.SetText(strBuffer2);

	Utils::CheckDebugMode();
	Utils::CheckFullScreenInput();

	if (!paused)
		for (size_t i = 0; i < pauseButtonIdx; ++i) {
			buttonTest[i].Update();
		}
	else if (paused && !Jumperman.GetLoseStatus() && !Jumperman.GetWinStatus()) {
		for (size_t i = pauseButtonIdx; i < buttonTest.size(); ++i) {
			buttonTest[i].Update();
		}
	}
	UI::Draw();
}

void UI::Draw() {
	if (DebugMode)
		FPS_Display.Draw();
	AEVec2 Pos{ LevelDisplay.GetBufferSize() };
	AEVec2 Pos2{ TimerDisplay.GetBufferSize() };
	TimerDisplay.Draw_Wrapped(AEVec2Set(AEGetWindowWidth() - Pos2.x / 2.0f, Pos2.y / 2.0f));
	LevelDisplay.Draw_Wrapped(AEVec2Set(Pos.x / 2.0f, Pos.y / 2.0f));

}

void UI::Buttons_Init() {
	const float buttonWidth{ 100.0f }, buttonHeight{ 50.0f };

	AEVec2 Midpt{ Utils::GetScreenMiddle() };

	for (size_t i = 0; i < 4; ++i) {
		buttonTest.push_back(Button(ButtonType::Color, buttonWidth, buttonHeight, 0.5f));
	}

	buttonTest[0].Set_Position(AEVec2{ Midpt.x - buttonTest[0].GetWidth(), buttonTest[0].GetHeight() / 2.0f });
	buttonTest[0].Set_Text("Pause");
	buttonTest[0].Set_Callback(Test_Callback);

	buttonTest[1].Set_Position(AEVec2{ Midpt.x + buttonTest[0].GetWidth(), buttonTest[1].GetHeight() / 2.0f });
	buttonTest[1].Set_Callback(Mute_BGM);
	buttonTest[1].Set_Text("Mute BGM");

	buttonTest[2].Set_Text("Resume");
	buttonTest[2].Set_Callback(Utils::CheckPauseInput);
	buttonTest[2].Set_Position(AEVec2{ Midpt.x - buttonTest[2].GetWidth(), buttonTest[2].GetHeight() / 2.0f });

	buttonTest[3].Set_Text("Menu");
	buttonTest[3].Set_Callback(Utils::ReturnToMenu);
	buttonTest[3].Set_Position(AEVec2{ Midpt.x + buttonTest[2].GetWidth(), buttonTest[3].GetHeight() / 2.0f });
}

void UI::DisplayLife(short livesCount) {
	for (short i = 0; i < livesCount; ++i) {
		lives.Draw_Texture(AEVec2Set(lives.width / 2.0f + i * 50.0f, 50.0f), 255.0f);
	}
}


void UI::Unload()
{
	buttonTest.clear();
	lives.Free();
}
