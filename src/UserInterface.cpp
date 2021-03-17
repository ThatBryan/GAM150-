#include "UserInterface.h"
#include <fstream>
char strBuffer[100]{'\0'};
char strBuffer1[100]{ '\0' };
char strBuffer2[100]{ '\0' };
Graphics::Text FPS_Display(strBuffer, 0.5f);
Graphics::Text LevelDisplay(strBuffer1, 0.5f);
Graphics::Text TimerDisplay(strBuffer2, 0.5f);

std::vector <Button> buttonTest;
Image lives;

void UI::Init() {

	UI::Buttons_Init();

	FPS_Display.color.Set(Color{ 0, 0, 0, 255 });
	LevelDisplay.color.Set(Color{0, 0, 0, 255});
	TimerDisplay.color.Set(Color{ 0, 0, 0, 255 });

	memset(strBuffer, 0, 100 * sizeof(char));
	memset(strBuffer1, 0, 100 * sizeof(char));
	memset(strBuffer2, 0, 100 * sizeof(char));

	UI::LivesCount = 3;

	lives.Init(FP::HeartSprite, 35.0f, 35.0f, AEVec2Zero());
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
	AEVec2 Pos2{ TimerDisplay.GetBufferSize() };
	TimerDisplay.Draw_Wrapped(AEVec2Set(AEGetWindowWidth() - Pos2.x / 2.0f, Pos2.y / 2.0f));
	LevelDisplay.Draw_Wrapped(AEVec2Set(Pos.x / 2.0f, Pos.y / 2.0f));
	if(!paused)
		for (size_t i = 0; i < buttonTest.size(); ++i) {
			buttonTest[i].Update();
		}
	for (int i = 0; i < UI::LivesCount; ++i) {
		lives.Draw_Texture(AEVec2Set(lives.width / 2.0f + i * 50.0f , 50.0f), 255.0f);
	}
}

void UI::Buttons_Init() {
	const float buttonWidth{ 100.0f }, buttonHeight{ 50.0f };
	AEVec2 Midpt{ Utils::GetScreenMiddle() };
	buttonTest.push_back(Button(ButtonType::Color, buttonWidth, buttonHeight, 0.5f));
	buttonTest[0].Set_Position(AEVec2{ Midpt.x - buttonTest[0].GetWidth(), buttonTest[0].GetHeight() / 2.0f });
	buttonTest[0].Set_Callback(Test_Callback);
	char Test[20];
	strcpy_s(Test, "Pause");
	buttonTest[0].Set_Text(Test);

	//buttonTest.push_back(Button(ButtonType::Color, buttonWidth, buttonHeight, 0.5f));
	//buttonTest[1].Set_Position(AEVec2{ Midpt.x + buttonTest[0].GetWidth(), buttonTest[1].GetHeight() / 2.0f });
	//buttonTest[1].Set_Callback(Mute_BGM);
	//buttonTest[1].Set_Text("Mute BGM");
}

void UI::DecreaseLife() {
	UI::LivesCount--;
}

void UI::ResetLives() {
	UI::LivesCount = 3;
}

void UI::Buttons_Unload()
{
	buttonTest.clear();
	lives.Free();
}
