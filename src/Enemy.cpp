#include "Enemy.h"

Enemies::Enemies(const s8* filepath, const f32 width, const f32 height) : sprite(filepath, width, height)
{
	this->active = true;
	this->startingPos = { 0, 0 };
}

void Enemies::Update_Position(void)
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

void Enemy::Draw(std::vector <Enemies> enemy)
{
	for (size_t i = 0; i < enemy.size(); i++)
	{
		if (enemy[i].active)
			enemy[i].sprite.Draw_Tinted(enemy[i].sprite, enemy[i].sprite.pos, 255.0f, 0, 0, 255.0f);
	}
}

void Enemy::AddNew(std::vector <Enemies>& enemy, const s8* filepath, const AEVec2 pos, const f32 width, const f32 height)
{
	enemy.push_back(Enemies(filepath, width, height));
	enemy[enemy.size() - 1].sprite.pos = pos;
	enemy[enemy.size() - 1].startingPos = pos;
}

void Enemy::Reset(std::vector <Enemies>& enemy)
{
	for (size_t i = 0; i < enemy.size(); i++)
	{
		enemy[i].sprite.pos = enemy[i].startingPos;
		enemy[i].active = true;
	}
}
void Enemy::Free(std::vector <Enemies>& enemy)
{
	for (size_t i = 0; i < enemy.size(); i++)
	{
		enemy[i].sprite.Free();
	}
}