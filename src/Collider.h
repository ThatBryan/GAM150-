#pragma once
#include "Graphics.h"

struct Collider {
	Graphics::Rect topBB;
	Graphics::Rect bottomBB;
	Graphics::Rect leftBB;
	Graphics::Rect rightBB;

	Collider();

	void SetWidthHeight(Graphics::Rect& arg, float width, float height);
	void Draw();
};