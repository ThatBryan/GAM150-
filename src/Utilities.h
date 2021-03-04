#pragma once
#include "AEEngine.h"
#include "Constants.h"
#include <fstream>

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

	void CheckFullScreenInput(void);// Set window to full screen with L ALT + Enter.
	void CheckPauseInput(void); 	// Press Tab to pause the game.
	void CheckDebugMode(void);		// F1 to enter debug mode
	AEVec2 GetScreenMiddle(void);
	bool ColliderAABB(AEVec2 pos, f32 width, f32 height, AEVec2 pos2, f32 width2, f32 height2);
}

// Overloading vector functions to set result as return value.
AEVec2 AEVec2Sub(const AEVec2 vec1, const AEVec2 vec2);
AEVec2 AEVec2Zero(void);
AEVec2 AEVec2Set(const f32 x, const f32 y);
AEVec2 AEVec2Add(const AEVec2 vec1, const AEVec2 vec2);