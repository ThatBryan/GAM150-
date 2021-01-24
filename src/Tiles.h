#pragma once
#include "Image.h"
#include <vector>
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"

class Tiles
{
	public:
		Tiles(const s8* filepath, const f32 width, const f32 height);
		s32 ID;
		f64 delay;
		bool active, collapsing;
		Image image;
		void Collapse(void);
		void DecreaseLifespan(void);
		void CheckPlayerCollision(std::vector <Image> Demo_Player);
};