#include "UserInterface.h"
#include <fstream>
char strBuffer[100];
char strBuffer1[100];
char strBuffer2[100];
Graphics::Text FPS_Display(strBuffer, 0.5);
Graphics::Text LevelDisplay(strBuffer1);
Graphics::Text TimerDisplay(strBuffer2, 0.5f);

std::vector <Button> buttonTest;

void UI::Init() {

	UI::Buttons_Init();

	FPS_Display.color.SetColor(Color{ 0, 0, 0, 255 });
	LevelDisplay.color.SetColor(Color{0, 0, 0, 255});
	TimerDisplay.color.SetColor(Color{ 0, 0, 0, 255 });

	memset(strBuffer, 0, 100 * sizeof(char));
	memset(strBuffer1, 0, 100 * sizeof(char));
	memset(strBuffer2, 0, 100 * sizeof(char));


	FPS_Display.Set_Pos(AEVec2Set(0, 100));
	//LevelDisplay.Set_Pos(AEVec2Set(0, 15));
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
	AEVec2 Pos{ LevelDisplay.GetBufferSize() };
	printf("%.2f %.2f\n", Pos.x / 2.0f, Pos.y);
	TimerDisplay.Draw();
	LevelDisplay.Draw_Wrapped(AEVec2Set(Pos.x / 2.0f, Pos.y));
	if(!paused)
		for (size_t i = 0; i < buttonTest.size(); ++i) {
			buttonTest[i].Update();
		}
}

void UI::Buttons_Init() {
	AEVec2 Midpt{ Utils::GetScreenMiddle() };
	buttonTest.push_back(Button(150.0, 50.0f, 0.9f));
	buttonTest[0].Set_Position(AEVec2{ Midpt.x - buttonTest[0].GetWidth(), buttonTest[0].GetHeight() / 2.0f });
	buttonTest[0].Set_Callback(Test_Callback);
	buttonTest[0].Set_Text("Pause");

	buttonTest.push_back(Button(150.0, 50.0f, 0.7f));
	buttonTest[1].Set_Position(AEVec2{ Midpt.x + buttonTest[0].GetWidth(), buttonTest[1].GetHeight() / 2.0f });
	buttonTest[1].Set_Callback(Mute_BGM);
	buttonTest[1].Set_Text("Mute BGM");
}

void UI::Buttons_Unload()
{
	buttonTest.clear();
}
