#include "Enemy.h"

Enemy::Enemy(const s8* filepath, const f32 width, const f32 height) : sprite(filepath, width, height)
{
	this->active = true;
}