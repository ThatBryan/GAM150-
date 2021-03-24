#include "Collider.h"
#include <iostream>

Collider::Collider() : topBB{ 0.0f, 0.0f }, bottomBB{ 0.0f, 0.0f }, leftBB{ 0.0f, 0.0f }, rightBB{ 0.0f, 0.0f } {}


void Collider::SetWidthHeight(Graphics::Rect& arg, float width, float height) {
	std::cout << "Wtf\n";
	arg.width = width;
	arg.height = height;
}

void Collider::Draw()
{
	topBB.Draw();
	bottomBB.Draw();
	leftBB.Draw();
	rightBB.Draw();
}
