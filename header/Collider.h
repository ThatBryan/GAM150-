#pragma once
#include "Graphics.h"

struct Collider {

	Graphics::Rect sprite, top, bottom, left, right;

	Collider();
	inline void SetHeight(Graphics::Rect& arg, float Height) { arg.height = Height; }
	void SetMeshes();
	void SetWidthHeight(Graphics::Rect& arg, float width, float height);
	void Draw();
};