/******************************************************************************/
/*!
\file		Collider.h
\author 	Bryan Koh Yan Wei, yanweibryan.koh, 390001520
\par    	email: yanweibryan.koh@digipen.edu
\date   	February 28, 2021
\brief		Header file for a user defined type which contains 5 rectangles.

			Used for collision detection between game objects. 


All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
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