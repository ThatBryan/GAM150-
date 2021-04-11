/******************************************************************************/
/*!
\file				Utilities.h
\author: 			Bryan Koh Yan Wei
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Contains the definition of helper functions used 
					throughout the game development process.

					Some functionalities are:

					Random number generators
					Lerping of float.
					Function overloading for AEVec2 type.
					Toggling of pause/fullscreen.
					etc.

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#include "Utilities.h"
#include "GameStateManager.h"
#include "Constants.h"
#include "AudioManager.h"
#include "Globals.h"
#include "LevelSystem.h"

#include <iostream>
#include <fstream>
#include "Utilities.h"

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

bool operator==(const AEVec2& lhs, const AEVec2& rhs)
{
const float Episilon{ 1.0f };
	if (fabsf(lhs.x - rhs.x) <= Episilon &&
		fabsf(lhs.y - rhs.y) <= Episilon)
		return true;

	return false;
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

void Utils::CheckKeyBindInputs(void)
{
	if (AEInputCheckCurr(FULLSCREEN_KEY1) && AEInputCheckTriggered(FULLSCREEN_KEY2))
	{
		Utils::ToggleFullscreen();
	}
	CheckMinimizeConditions();
}

void Utils::CheckMinimizeConditions()
{
	if (GetAsyncKeyState(AEVK_LALT)) {
		if (GetAsyncKeyState(AEVK_TAB))
			ShowWindow(AESysGetWindowHandle(), SW_MINIMIZE);

		if (GetAsyncKeyState(AEVK_LCTRL) && GetAsyncKeyState(VK_DELETE))
			ShowWindow(AESysGetWindowHandle(), SW_MINIMIZE);
	}
	if (GetFocus() == NULL)
		ShowWindow(AESysGetWindowHandle(), SW_MINIMIZE);
}

void Utils::ToggleFullscreen()
{
	GAMEPLAY_MISC::FULLSCREEN = !GAMEPLAY_MISC::FULLSCREEN;
	AEToogleFullScreen(GAMEPLAY_MISC::FULLSCREEN);
}

bool Utils::GetFullscreenStatus()
{
	return GAMEPLAY_MISC::FULLSCREEN;
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

AEVec2 Utils::GetRandomPos(void)
{
	static f32 Height = static_cast<f32>(AEGetWindowHeight());
	static f32 Width = static_cast<f32>(AEGetWindowWidth());

	return AEVec2{ Utils::RandomRangeFloat(0, Width), Utils::RandomRangeFloat(0, Height)};
}

AEVec2 Utils::GetRandomRangeVec(const AEVec2 lowerBound, const AEVec2 upperBound)
{
	AEVec2 Rand{ 0, 0 };
	Rand.x = Utils::RandomRangeFloat(lowerBound.x, upperBound.x);
	Rand.y = Utils::RandomRangeFloat(lowerBound.y, upperBound.y);
	return Rand;
}

AEVec2 Utils::GetRandomVecVel(void)
{
	AEVec2 Vel{ Utils::RandomRangeFloat(-1.0f, 1.0f), Utils::RandomRangeFloat(-1.0f, 1.0f) };
	AEVec2Normalize(&Vel, &Vel);
	return Vel;
}

AEVec2 Utils::GetMousePos(void)
{
	int mouseX = 0, mouseY = 0;
	AEInputGetCursorPosition(&mouseX, &mouseY);
	return AEVec2Set(static_cast<f32>(mouseX), static_cast<f32>(mouseY));
}

void Utils::TogglePause(void)
{
	GAMEPLAY_MISC::PAUSED = !GAMEPLAY_MISC::PAUSED;
	if (!GAMEPLAY_MISC::PAUSED) {
		GAMEPLAY_MISC::DISPLAY_QUIT_UI = false;
	}
}

void Utils::ToggleDevMode(void)
{
	static bool isFirstTime{ false };
	GAMEPLAY_MISC::DEV_MODE = !GAMEPLAY_MISC::DEV_MODE;
	GAMEPLAY_MISC::DEV_MODE == true ? std::cout << "\nDeveloper mode turned on\n" : std::cout << "\nDeveloper mode turned off\n";

	if (GAMEPLAY_MISC::DEV_MODE && !isFirstTime) { // Only ever print once
		std::cout << "\nUse F1 to toggle Debug Mode\n";
		std::cout << "	Use F2 to toggle player collision\n";
		isFirstTime = true;
	}
}

void Utils::ToggleDebugMode(void)
{
	if (AEInputCheckTriggered(DEBUG_KEY))
		GAMEPLAY_MISC::DEBUG_MODE = !GAMEPLAY_MISC::DEBUG_MODE;

	if (!GAMEPLAY_MISC::DEBUG_MODE) {
		GAMEPLAY_MISC::DISABLE_COLLISION = false;
	}
}

void Utils::ToggleCollisionOff(void)
{
	if (AEInputCheckTriggered(COLLISION_OFF_KEY)) {
		GAMEPLAY_MISC::DEBUG_MODE = true;
		GAMEPLAY_MISC::DISABLE_COLLISION = !GAMEPLAY_MISC::DISABLE_COLLISION;
		GAMEPLAY_MISC::DISABLE_COLLISION == false ? std::cout << "Collision turned on \n" : std::cout << "Collision turned off \n";
	}
}

void Utils::DebugKeysManager()
{
	//if (!GAMEPLAY_MISC::DEV_MODE) // Exit if dev mode is not enabled. disabled for now. 
	//	return;
	ToggleCollisionOff();
	ToggleDebugMode();
}


void Utils::DebugHelper()
{
	if (AEInputCheckCurr(FASTFOWARD_TIME_KEY)) {
		static const float TimeSkipAmount = 5.0f;
		GAMEPLAY_MISC::TimeAttack_remaining -= TimeSkipAmount;
	}
	if (AEInputCheckReleased(NEXT_LEVEL_KEY)) {
		LevelSystem::SetNextLevel();
	}
	if (AEInputCheckReleased(PREV_LEVEL_KEY)) {
		GAMEPLAY_MISC::Level == 0	? Utils::ReturnToMenu()
									: LevelSystem::SetLevel(GAMEPLAY_MISC::Level - 1);
	}
	
}

void Utils::CursorManager()
{
	static bool CursorDisplay{ true };

	if (GAMEPLAY_MISC::PAUSED && CursorDisplay == false) {
		ShowCursor(true);
		CursorDisplay = true;
	}

	if (!GAMEPLAY_MISC::PAUSED && CursorDisplay == true) {
		ShowCursor(false);
		CursorDisplay = false;
	}
}

void Utils::ReturnToMenu(void) {
	gamestateNext = GS_MAINMENU;
}

void Utils::RestartLevel(void)
{
	gamestateNext = GS_RESTART;
}

void Utils::ExitGame(void)
{
	gamestateNext = GS_QUIT;
}

void Utils::ToggleQuitUI(void)
{
	GAMEPLAY_MISC::DISPLAY_QUIT_UI = !GAMEPLAY_MISC::DISPLAY_QUIT_UI;
}

float Utils::Lerp(const float start, const float end, const float t)
{
	return start + t * (end - start);
}

bool Utils::ColliderAABB(AEVec2 A, f32 A_width, f32 A_height, AEVec2 B, f32 B_width, f32 B_height) {
	A_width = fabsf(A_width);
	B_width = fabsf(B_width);

	if (A.x + A_width / 2.0f < B.x - B_width / 2.0f ||
		A.y - A_height / 2.0f > B.y + B_height / 2.0f ||
		A.x - A_width / 2.0f > B.x + B_width / 2.0f ||
		A.y + A_height / 2.0f < B.y - B_height / 2.0f) {
		return false;
	}
	return true;
}
