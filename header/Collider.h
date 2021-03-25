#pragma once
#include "Graphics.h"

struct Collider {
	Graphics::Rect top;
	Graphics::Rect bottom;
	Graphics::Rect left;
	Graphics::Rect right;

	Collider();
	void SetMeshes();
	void SetWidthHeight(Graphics::Rect& arg, float width, float height);
	void SetHeight(Graphics::Rect& arg, float Height) { arg.height = Height; }
	void Draw();
};