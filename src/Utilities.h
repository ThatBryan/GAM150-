#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"

namespace Utilities 
{
	int RandomRangeInt(const s32 lowerBound, const s32 upperBound);
	AEVec2 Vector_Set(const f32 x, const f32 y);
	void Set_FullScreen(void);
	f32 Get_HalfWindowWidth(void);
	f32 Get_HalfWindowHeight(void);
	AEVec2 GetMousePos(void);
}