#include "Player.h"

Player::Player(const s8* filepath, const f32 width, const f32 height) : sprite(filepath, width, height)
{
	this->active = true;
}
void Player::Update_Position(void)
{
	static f32 HeightLimit = (f32)AEGetWindowHeight();
	static f32 WidthLimit = (f32)AEGetWindowWidth();
	static float speed = 5.0f;
	static float gravity = 2.5f;
	static bool onAir = false;

	if (AEInputCheckCurr(AEVK_W) || AEInputCheckCurr(AEVK_UP))
	{
		if (this->sprite.pos.y + this->sprite.height / 2 <= HeightLimit)
		{
			this->sprite.pos.y += speed;
		}
	}
	if (AEInputCheckCurr(AEVK_S) || AEInputCheckCurr(AEVK_DOWN))
	{
		if (this->sprite.pos.y - this->sprite.height / 2 >= 0)
		{
			this->sprite.pos.y -= speed;
		}
	}
	if (AEInputCheckCurr(AEVK_D) || AEInputCheckCurr(AEVK_RIGHT))
	{
		if (this->sprite.pos.x + this->sprite.width / 2 <= WidthLimit)
		{
			this->sprite.pos.x += speed;
		}
	}
	if (AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_LEFT))
	{
		if (this->sprite.pos.x - this->sprite.width / 2 >= 0)
		{
			this->sprite.pos.x -= speed;
		}
	}
	AEVec2 Mouse = Utilities::GetMousePos();
	if (AETestPointToRect(&Mouse, &this->sprite.pos, this->sprite.width, this->sprite.height))
	{
		if (AEInputCheckCurr(AEVK_LBUTTON))
			this->sprite.pos = Mouse;
	}
}

void Player::CheckEnemyCollision(std::vector <Enemy> enemy)
{
	for (size_t i = 0; i < enemy.size(); i++)
	{
		if (AETestRectToRect(&this->sprite.pos, this->sprite.width, this->sprite.height, &enemy[i].sprite.pos, enemy[i].sprite.width, enemy[i].sprite.height))
		{
			this->active = false;
		}
	}
}
