#include "Utilities.h"
#include <iostream>

int Utils::RandomRangeInt(const s32 lowerBound, const s32 upperBound)
{
	return (lowerBound + rand() % (upperBound - lowerBound + 1));
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
	return (f32)(AEGetWindowWidth() / 2.0f);
}
f32 Utils::Get_HalfWindowHeight(void)
{
	return (f32)(AEGetWindowHeight() / 2.0f);
}
AEVec2 Utils::GetScreenMiddle() {
	static f32 HalfWidth = Utils::Get_HalfWindowWidth();
	static f32 HalfHeight = Utils::Get_HalfWindowHeight();
	return AEVec2{ HalfWidth, HalfHeight };
}

AEVec2 Utils::GetMousePos(void)
{
	int mouseX = 0;
	int mouseY = 0;
	AEInputGetCursorPosition(&mouseX, &mouseY);
	//return AEVec2Set((f32)mouseX - AEGfxGetWinMinX(), -(mouseY + AEGfxGetWinMinY())); // (f32)AEGetWindowHeight() - (f32)
	return AEVec2Set(mouseX, mouseY);
}

void Utils::CheckPauseInput(void)
{
	if (AEInputCheckTriggered(PAUSE_KEY))
	{
		paused = !paused;
	}
}

void Utils::CheckDebugMode(void)
{
	if (AEInputCheckTriggered(DEBUG_KEY))
	{
		DebugMode = !DebugMode;
	}
}
