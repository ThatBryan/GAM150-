#include "Enemy.h"

Enemy::Enemy(const s8* filepath, const f32 width, const f32 height) : sprite(filepath, width, height)
{
	this->active = true;
}

void Enemy::Update_Position(void)
{
	static float speed = 1.0f;
	static float counter = 0.0f;

	this->sprite.pos.x += speed;
	counter += 1.0f;
	if (counter > 60.0f)
	{
		speed *= -1;
		counter = 0.0f;
	}
}