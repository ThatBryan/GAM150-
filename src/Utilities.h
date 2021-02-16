#pragma once
#include "AEEngine.h"
#include "Constants.h"

namespace Utilities 
{
	// Returns a random int between the specified perimeters.
	int RandomRangeInt(const s32 lowerBound, const s32 upperBound);

	// Set window to full screen with L ALT + Enter.
	void CheckFullScreenInput(void);

	// Returns half window width/height to be used for calculations.
	f32 Get_HalfWindowWidth(void);
	f32 Get_HalfWindowHeight(void);

	//Returns the position of the mouse in window coordinates.
	AEVec2 GetMousePos(void);

	// Press Tab to pause the game.
	void CheckPauseInput(void);

	void CheckDebugMode(void);
}


// Overloading vector functions.
AEVec2 AEVec2Sub(const AEVec2 vec1, const AEVec2 vec2);
AEVec2 AEVec2Set(const f32 x, const f32 y);
AEVec2 AEVec2Add(const AEVec2 vec1, const AEVec2 vec2);