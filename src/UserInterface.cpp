#include "UserInterface.h"
#include <fstream>
char strBuffer[100];
char strBuffer1[100];
char strBuffer2[100];
Graphics::Text FPS_Display(strBuffer, 0.5);
Graphics::Text LevelDisplay(strBuffer1, 0.5);
Graphics::Text TimerDisplay(strBuffer2, 1.0);

std::vector <Button> buttonTest;

void UI::Init() {

	UI::Buttons_Init();

	FPS_Display.color.SetColor(0, 0, 0, 255);
	LevelDisplay.color.SetColor(0, 0, 0, 255);
	TimerDisplay.color.SetColor(0, 0, 0, 255);

	memset(strBuffer, 0, 100 * sizeof(char));
	memset(strBuffer1, 0, 100 * sizeof(char));
	memset(strBuffer2, 0, 100 * sizeof(char));

	FPS_Display.Set_Pos(AEVec2Set(0, 100));
	LevelDisplay.Set_Pos(AEVec2Set(0, 15));
	TimerDisplay.Set_Pos(AEVec2Set(660, 15));

}

void UI::Update() {
	sprintf_s(strBuffer, "FPS: %.2f", AEFrameRateControllerGetFrameRate());
	sprintf_s(strBuffer2, "Time Elapsed: %.2f", app_time);
	sprintf_s(strBuffer1, "Current Level: Tutorial");
	UI::Draw();
}

void UI::Draw() {
	if (DebugMode)
		FPS_Display.Draw();
	TimerDisplay.Draw();
	LevelDisplay.Draw();
	for (size_t i = 0; i < buttonTest.size(); ++i) {
		buttonTest[i].Update();
	}
}

void UI::Buttons_Init() {

	buttonTest.push_back(Button(100.0, 50.0f, 0.9f));
	buttonTest[0].Set_Position(AEVec2{ 300.0f, 25.0f });
	buttonTest[0].Set_Callback(Test_Callback);
	buttonTest[0].Set_Text("Pause");

	buttonTest.push_back(Button(100.0, 50.0f, 0.7f));
	buttonTest[1].Set_Position(AEVec2{ 500.0f, 25.0f });
	buttonTest[1].Set_Callback(Mute_BGM);
	buttonTest[1].Set_Text("Mute BGM");
}