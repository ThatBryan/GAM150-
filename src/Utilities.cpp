#include "Utilities.h"
#include <iostream>


int Utilities::RandomRangeInt(const s32 lowerBound, const s32 upperBound)
{
	return (lowerBound + rand() % (upperBound - lowerBound + 1));
}
//float Utilities::RandomRangeFloat(const f32 lowerBound, const f32 upperBound)
//{
//	return (lowerBound + rand() % (upperBound - 1 - lowerBound));
//}

AEVec2 Utilities::Vector_Set(AEVec2 Vector, const f32 x, const f32 y)
{
	AEVec2Set(&Vector, x, y);
	return Vector;
}

void Utilities::Set_FullScreen(void)
{
	static bool fullscreen = false;
	if (AEInputCheckCurr(AEVK_LALT) && AEInputCheckCurr(AEVK_RETURN))
	{
		if (fullscreen)
		{
			fullscreen = false;
		}
		else
		{
			fullscreen = true;
		}
		AEToogleFullScreen(fullscreen);
	}
	// testing again
}