#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"

namespace Utilities 
{
	// Returns a random int between the specified perimeters.
	int RandomRangeInt(const s32 lowerBound, const s32 upperBound);

	// Returns a 2D-vector set to to perimeter x and y. 
	AEVec2 Vector_Set(const f32 x, const f32 y);

	// Returns the sum of two 2D-vectors.
	AEVec2 Vector_Add(const AEVec2 vec1, const AEVec2 vec2);

	AEVec2 Vector_Sub(const AEVec2 vec1, const AEVec2 vec2);

	// Set window to full screen with L ALT + Enter.
	void Set_FullScreen(void);

	// Returns half window width/height to be used for calculations.
	f32 Get_HalfWindowWidth(void);
	f32 Get_HalfWindowHeight(void);

	//Returns the position of the mouse in window coordinates.
	AEVec2 GetMousePos(void);
}