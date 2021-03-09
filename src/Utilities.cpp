#include "Utilities.h"
#include "GameStateManager.h"
#include <iostream>

int Utils::RandomRangeInt(const s32 lowerBound, const s32 upperBound)
{
	return (lowerBound + rand() % (upperBound - lowerBound + 1));
}
float Utils::RandomRangeFloat(const f32 lowerBound, const f32 upperBound) {
	return((AERandFloat() * (upperBound - lowerBound) + lowerBound));
}

AEVec2 AEVec2Set(const f32 x, const f32 y)
{
	return AEVec2{ x, y };
}

AEVec2 AEVec2Zero()
{
	return AEVec2{0, 0};
}
AEVec2 AEVec2Add(const AEVec2 vec1, const AEVec2 vec2)
{
	return AEVec2{ vec1.x + vec2.x, vec1.y + vec2.y };
}

AEVec2 AEVec2Sub(const AEVec2 vec1, const AEVec2 vec2)
{
	return AEVec2{ vec1.x - vec2.x, vec1.y - vec2.y };
}

void Utils::CheckFullScreenInput(void)
{
	if (AEInputCheckCurr(FULLSCREEN_KEY1) && AEInputCheckTriggered(FULLSCREEN_KEY2))
	{
		fullscreen = !fullscreen;
		AEToogleFullScreen(fullscreen);
	}
}

f32 Utils::Get_HalfWindowWidth(void)
{
	return static_cast<f32>((AEGetWindowWidth() / 2.0f));
}
f32 Utils::Get_HalfWindowHeight(void)
{
	return static_cast<f32>((AEGetWindowHeight() / 2.0f));
}
AEVec2 Utils::GetScreenMiddle() {
	static f32 HalfWidth = Utils::Get_HalfWindowWidth();
	static f32 HalfHeight = Utils::Get_HalfWindowHeight();
	return AEVec2{ HalfWidth, HalfHeight };
}

AEVec2 Utils::GetMousePos(void)
{
	int mouseX = 0, mouseY = 0;
	AEInputGetCursorPosition(&mouseX, &mouseY);
	return AEVec2Set(static_cast<f32>(mouseX), static_cast<f32>(mouseY));
}

void Utils::CheckPauseInput(void)
{
	paused = !paused;
}

void Utils::CheckDebugMode(void)
{
	if (AEInputCheckTriggered(DEBUG_KEY))
		DebugMode = !DebugMode;
}

void Utils::ReturnToMenu(void) {
	gamestateNext = GS_MAINMENU;
}

bool Utils::ColliderAABB(AEVec2 A, f32 A_width, f32 A_height, AEVec2 B, f32 B_width, f32 B_height) {
	if (A.x + A_width / 2.0f < B.x - B_width / 2.0f ||
		A.y - A_height / 2.0f > B.y + B_height / 2.0f ||
		A.x - A_width / 2.0f > B.x + B_width / 2.0f ||
		A.y + A_height / 2.0f < B.y - B_height / 2.0f) {
		//printf("%.2f %.2f %.2f %.2f\n", A.x, A.y, A_width, A_height);
		//printf("%.2f %.2f %.2f %.2f\n", B.x, B.y, B_width, B_height);
		return false;
	}
	return true;
}
