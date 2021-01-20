#pragma once
#include "Image.h"
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"

class Tiles
{
	public:
		Tiles(const s8* filepath, const f32 width, const f32 height);
		Image image;
};