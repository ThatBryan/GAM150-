#include "Enemy.h"

Enemies::Enemies(const s8* filepath, const f32 width, const f32 height) : sprite(filepath, width, height)
{
	active = true;
	spawnPos = { 0, 0 };
	type = None;
	colliderAABB.color.SetColor(0, 0, 255.0f, 255.0f);
}

void Enemies::Update_Position(void)
{
	static float speed = 1.0f;
	static float counter = 0.0f;

	sprite.pos.x += speed;
	colliderAABB.pos = sprite.pos;
	if(type == Slime)
		colliderAABB.pos.y += 20.0f;

	counter += 1.0f;
	if (counter > 180.0f)
	{
		speed *= -1;
		counter = 0.0f;
	}
}

void Enemies::Draw(std::vector <Enemies> enemy)
{
	for (size_t i = 0; i < enemy.size(); i++)
	{
		if (enemy[i].active)
		{
			enemy[i].sprite.Draw_Default(enemy[i].sprite.pos, 255.0f);
				if (DebugMode)
					enemy[i].colliderAABB.Draw(enemy[i].colliderAABB.pos);
		}
	}
}

void Enemies::AddNew(std::vector <Enemies>& enemy, const short type, const s8* filepath, const AEVec2 pos, const f32 width, const f32 height)
{
	enemy.push_back(Enemies(filepath, width, height));
	enemy[enemy.size() - 1].sprite.pos = pos;
	enemy[enemy.size() - 1].type = type;
	enemy[enemy.size() - 1].spawnPos = pos;
}

void Enemies::Reset(std::vector <Enemies>& enemy)
{
	for (size_t i = 0; i < enemy.size(); i++)
	{
		enemy[i].sprite.pos = enemy[i].spawnPos;
		enemy[i].active = true;
	}
}
void Enemies::Free(std::vector <Enemies>& enemy)
{
	for (size_t i = 0; i < enemy.size(); i++)
	{
		enemy[i].sprite.Free();
		enemy[i].colliderAABB.Free();
	}
}