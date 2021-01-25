#include "Player.h"

Player::Player(const s8* filepath, const f32 width, const f32 height) : sprite(filepath, width, height)
{
	this->active = true;
	this->jump = false;
	this->win = false;
	this->startingPos = { 0, 0 };
}

void Player::Reset(void)
{
	this->active = true;
	this->win = false;
	this->sprite.pos = this->startingPos;
}

void Player::Draw(void)
{
	this->sprite.Draw_Default(this->sprite, this->sprite.pos, 255.0f);
}

void Player::Update_Position(void)
{
	static f32 HeightLimit = (f32)AEGetWindowHeight();
	static f32 WidthLimit = (f32)AEGetWindowWidth();
	static float speed = 5.0f;
	static float jumpspeed_y = 10.0f;

	if (AEInputCheckCurr(AEVK_W) || AEInputCheckCurr(AEVK_UP) && this->jump == FALSE)
	{
		this->jump = TRUE;
	}
	if (this->jump == TRUE)
	{
		if (this->sprite.pos.y + this->sprite.height / 2 <= HeightLimit)
		{

			this->sprite.pos.y += jumpspeed_y;

			jumpspeed_y -= 1.0f;
			if (jumpspeed_y < -10.0f)
			{
				this->jump = FALSE;
				jumpspeed_y = 10.0f;
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

void Player::CheckEnemyCollision(std::vector <Enemies>& enemy)
{
	for (size_t i = 0; i < enemy.size(); i++)
	{
		if (enemy[i].active)
		{
			if (AETestRectToRect(&this->sprite.pos, this->sprite.width, this->sprite.height, &enemy[i].sprite.pos, enemy[i].sprite.width, enemy[i].sprite.height))
			{
				if (this->sprite.pos.y >= enemy[i].sprite.pos.y && this->jump)
				{
					enemy[i].active = false;
				}
				else
				{
					this->active = false;
				}

			}

		}
	}
}
