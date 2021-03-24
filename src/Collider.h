#pragma once
#include "Graphics.h"

struct Collider {
	Graphics::Rect topBB;
	Graphics::Rect bottomBB;
	Graphics::Rect leftBB;
	Graphics::Rect rightBB;

	Collider();
	void SetMeshes();
	void SetWidthHeight(Graphics::Rect& arg, float width, float height);
	void SetHeight(Graphics::Rect& arg, float Height) { arg.height = Height; }
	void Draw();
};