#include "UserInterface.h"

char strBuffer[100];
char strBuffer1[100];
char strBuffer2[100];
Graphics::Text FPS_Display(strBuffer, 0.5);
Graphics::Text LevelDisplay(strBuffer1);
Graphics::Text TimerDisplay(strBuffer2);

void UI::Init() {

	FPS_Display.color.SetColor(255, 0, 0, 255);
	LevelDisplay.color.SetColor(255, 0, 0, 255);
	TimerDisplay.color.SetColor(0, 0, 0, 255);

	memset(strBuffer, 0, 100 * sizeof(char));
	memset(strBuffer1, 0, 100 * sizeof(char));
	memset(strBuffer2, 0, 100 * sizeof(char));

}

void UI::Update() {
	sprintf_s(strBuffer, "FPS: %.2f", AEFrameRateControllerGetFrameRate());
	sprintf_s(strBuffer2, "Time Elapsed: %.2f", app_time);
	sprintf_s(strBuffer1, "Current Level: Tutorial");
	UI::Draw();
}

void UI::Draw() {
	if (DebugMode)
		FPS_Display.Draw_Text(AEVec2Set(0, 200));
	LevelDisplay.Draw_Text(AEVec2Set(0, 25));
	TimerDisplay.Draw_Text(AEVec2Set(665, 25));
}
