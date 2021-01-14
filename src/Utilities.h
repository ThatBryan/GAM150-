#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"

namespace Utilities 
{
	int RandomRangeInt(const s32 lowerBound, const s32 upperBound);
	AEVec2 Vector_Set(AEVec2 Vector, const f32 x, const f32 y);
	void Set_FullScreen(void);
	//float RandomRangeFloat(const f32 lowerBound, const f32 upperBound);
}