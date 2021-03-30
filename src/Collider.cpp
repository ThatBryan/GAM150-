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
