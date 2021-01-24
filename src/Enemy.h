#pragma once
#include "Image.h"
#include "Utilities.h"
#include <vector>
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"

class Enemy
{
public:
	Enemy(const s8* filepath, const f32 width, const f32 height);
	bool active;
	Image sprite;

};