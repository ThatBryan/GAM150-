#include "Collider.h"
#include <iostream>

Collider::Collider() : topBB{ 0.0f, 0.0f }, bottomBB{ 0.0f, 0.0f }, leftBB{ 0.0f, 0.0f }, rightBB{ 0.0f, 0.0f } {}

void Collider::SetMeshes()
{
	topBB.SetMesh();
	leftBB.SetMesh();
	bottomBB.SetMesh();
	rightBB.SetMesh();
}


void Collider::SetWidthHeight(Graphics::Rect& arg, float width, float height) {
	arg.width = width;
	arg.height = height;


	bottomBB.color.Set(Color{ 255.0f, 255.0f, 0, 255.0f }); // yellow
	topBB.color.Set(Color{ 255.0f, 0, 0, 255.0f }); // red
	leftBB.color.Set(Color{ 0, 255.0f, 0, 255.0f }); // green
	rightBB.color.Set(Color{ 0, 0, 255.0f, 255.0f }); // blue
}

void Collider::Draw()
{
	topBB.Draw();
	bottomBB.Draw();
	leftBB.Draw();
	rightBB.Draw();
}
