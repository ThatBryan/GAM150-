#pragma once

#include "AEEngine.h"

namespace Utils 
{
	// Returns a random int between the specified perimeters.
	int RandomRangeInt(const s32 lowerBound, const s32 upperBound);
	float RandomRangeFloat(const f32 lowerBound, const f32 upperBound);

	// Returns half window width/height to be used for calculations.
	f32 Get_HalfWindowWidth(void);
	f32 Get_HalfWindowHeight(void);

	//Returns the position of the mouse in window coordinates.
	AEVec2 GetMousePos(void);

	void CheckFullScreenKeyInput(void);// Set window to full screen with L ALT + Enter.
	void ToggleFullscreen();
	bool GetFullscreenStatus();
	void TogglePause(void); 	// Press Tab to pause the game.
	void CheckDebugMode(void);		// F1 to enter debug mode
	void ReturnToMenu(void);
	void RestartLevel(void);
	void ExitGame(void);
	void ToggleQuitUI(void);

	// User has to increment t
	float Lerp(const float start, const float end, const float t);

	AEVec2 GetScreenMiddle(void);
	AEVec2 GetRandomPos(void);
	AEVec2 GetRandomRangeVec(const AEVec2 lowerBound, const AEVec2 upperBound);
	// Returns a random normalized vector.
	AEVec2 GetRandomVecVel(void);

	bool ColliderAABB(AEVec2 pos, f32 width, f32 height, AEVec2 pos2, f32 width2, f32 height2);
}

// Overloading vector functions to set result as return value.
// lhs - rhs

AEVec2 AEVec2Sub(const AEVec2 vec1, const AEVec2 vec2);
// lhs + rhs
AEVec2 AEVec2Add(const AEVec2 vec1, const AEVec2 vec2);
AEVec2 AEVec2Zero(void);
AEVec2 AEVec2Set(const f32 x, const f32 y);
bool operator==(const AEVec2& lhs, const AEVec2& rhs);
