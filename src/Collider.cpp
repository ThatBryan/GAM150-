/******************************************************************************/
/*!
\file		Collider.cpp
\author 	Bryan Koh Yan Wei, yanweibryan.koh, 390001520
\par    	email: yanweibryan.koh@digipen.edu
\date   	February 28, 2021
\brief

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#include "Collider.h"
#include <iostream>

Collider::Collider() : sprite{ 0.0f, 0.0f }, top { 0.0f, 0.0f }, bottom{ 0.0f, 0.0f }, left{ 0.0f, 0.0f }, right{ 0.0f, 0.0f } {
	sprite.color.Set((Color{ 150, 0, 0, 150 }));
	bottom.color.Set(Color{ 255.0f, 255.0f, 0, 255.0f }); // yellow
	top.color.Set(Color{ 255.0f, 0, 0, 255.0f }); // red
	left.color.Set(Color{ 0, 255.0f, 0, 255.0f }); // green
	right.color.Set(Color{ 0, 0, 255.0f, 255.0f }); // blue
}

void Collider::SetMeshes()
{
	sprite.SetMesh();
	top.SetMesh();
	left.SetMesh();
	bottom.SetMesh();
	right.SetMesh();
}


void Collider::SetWidthHeight(Graphics::Rect& arg, float width, float height) {
	arg.width = width;
	arg.height = height;
}

void Collider::Draw()
{
	sprite.Draw();
	left.Draw();
	right.Draw();
	bottom.Draw();
	top.Draw();
}
