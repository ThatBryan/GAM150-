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
	static float speedx = 5.0f;
	static float speedy = 5.0f;
	static bool jump = FALSE;

	if (AEInputCheckCurr(AEVK_W) || AEInputCheckCurr(AEVK_UP) && jump == FALSE)
	{
		jump = TRUE;
	}
	if (jump == TRUE)
	{
		if (this->sprite.pos.y + this->sprite.height / 2 <= HeightLimit)
		{
			this->sprite.pos.y += speedy;

			speedy -= 1.0f;
			if (speedy < -10.0f)
			{
				jump = FALSE;
				speedy = 10.0f;
			}
		}

		if (AEInputCheckCurr(AEVK_D) || AEInputCheckCurr(AEVK_RIGHT))
		{
			this->sprite.pos.x += speed;
		}

		if (AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_LEFT))
		{
			this->sprite.pos.x -= speed;
		}
	}

	if (AEInputCheckCurr(AEVK_S) || AEInputCheckCurr(AEVK_DOWN) && !AEInputCheckCurr(AEVK_W) && !AEInputCheckCurr(AEVK_UP))
	{
		if (this->sprite.pos.y - this->sprite.height / 2 >= 0)
		{
			this->sprite.pos.y -= speed;
		}
	}
	if (AEInputCheckCurr(AEVK_D) || AEInputCheckCurr(AEVK_RIGHT) && !AEInputCheckCurr(AEVK_W) && !AEInputCheckCurr(AEVK_UP))
	{
		if (this->sprite.pos.x + this->sprite.width / 2 <= WidthLimit)
		{
			this->sprite.pos.x += speed;
		}
	}
	if (AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_LEFT) && !AEInputCheckCurr(AEVK_W) && !AEInputCheckCurr(AEVK_UP))
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
