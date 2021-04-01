#pragma once
#include "Graphics.h"

struct Collider {

	Graphics::Rect sprite, top, bottom, left, right;

	Collider();
	void SetMeshes();
	void SetWidthHeight(Graphics::Rect& arg, float width, float height);
	inline void SetHeight(Graphics::Rect& arg, float Height) { arg.height = Height; }
	void Draw();
};