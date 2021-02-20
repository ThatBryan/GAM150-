#include "Player.h"

Player::Player(const s8* filepath, const f32 width, const f32 height) : sprite(filepath, width, height) 
{
	active = true;
	gravity = false;
	jump = false;
	win = false;
	startingPos = { 0, 0 };
	colliderAABB.color.SetColor(255.0f, 0, 0, 255.0f);
}

void Player::Reset(void)
{
	active = true;
	win = false;
	sprite.pos = startingPos;
}

void Player::Draw(void)
{
	sprite.Draw_Texture(255.0f);
	
	if (DebugMode)
		colliderAABB.Draw();
}
void Player::Free(std::vector <Player> player)
{
	//player[player.size() - 1].colliderAABB.Free();
	player[player.size() - 1].sprite.Free();
}
void Player::Update_Position(void)
{
	static f32 maxY = AEGfxGetWinMaxY();
	static f32 maxX = AEGfxGetWinMaxX();
	static f32 minY = AEGfxGetWinMinY();
	static f32 minX = AEGfxGetWinMinX();
	static float jumpspeed_y = 10.0f;

	if (AEInputCheckCurr(AEVK_W) || AEInputCheckCurr(AEVK_UP) && this->jump == FALSE)
	{
		jump = TRUE;
	}
	if (jump == TRUE)
	{
		if (sprite.pos.y + sprite.height / 2 <= maxY)
		{

			sprite.pos.y += jumpspeed_y;

			jumpspeed_y -= 1.0f;
			if (jumpspeed_y < -10.0f)
			{
				jump = FALSE;
				jumpspeed_y = 10.0f;
			}
		}

		if (AEInputCheckCurr(AEVK_D) || AEInputCheckCurr(AEVK_RIGHT))
		{
			sprite.pos.x += player_speed;
		}

		if (AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_LEFT))
		{
			sprite.pos.x -= player_speed;
		}
	}

	if (AEInputCheckCurr(AEVK_S) || AEInputCheckCurr(AEVK_DOWN) && !AEInputCheckCurr(AEVK_W) && !AEInputCheckCurr(AEVK_UP))
		if (sprite.pos.y - sprite.height / 2 >= minY)
			sprite.pos.y -= player_speed;

	if (AEInputCheckCurr(AEVK_D) || AEInputCheckCurr(AEVK_RIGHT) && !AEInputCheckCurr(AEVK_W) && !AEInputCheckCurr(AEVK_UP))
		if (sprite.pos.x + sprite.width / 2 <= maxX)
			sprite.pos.x += player_speed;

	if (AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_LEFT) && !AEInputCheckCurr(AEVK_W) && !AEInputCheckCurr(AEVK_UP))
		if (sprite.pos.x - sprite.width / 2 >= minX)
			sprite.pos.x -= player_speed;

	AEVec2 Mouse = Utilities::GetMousePos();
	if (AETestPointToRect(&Mouse, &sprite.pos, sprite.width, sprite.height))
	{
		if (AEInputCheckCurr(AEVK_LBUTTON))
			sprite.pos = Mouse;
	}
	colliderAABB.pos = AEVec2{ sprite.pos.x, sprite.pos.y - player_collider_offset };
}

void Player::GravityManager(void)
{
	if (gravity)
	{
		if(DebugMode)
			printf("Apply gravity\n");
	}
}

void Player::CheckEnemyCollision(std::vector <Enemies>& enemy)
{
	for (size_t i = 0; i < enemy.size(); i++)
	{
		if (enemy[i].active)
		{
			if (AETestRectToRect(&enemy[i].sprite.pos, enemy[i].sprite.width, enemy[i].sprite.height, &sprite.pos, sprite.width - 5.0f, sprite.height))
			{
				if (AETestRectToRect(&enemy[i].sprite.pos, enemy[i].sprite.width, enemy[i].sprite.height, &colliderAABB.pos, colliderAABB.width, colliderAABB.height))// && 
					enemy[i].active = false;
				//AEVec2 EnemyTop = { enemy[i].sprite.pos.x, enemy[i].sprite.pos.y + enemy[i].sprite.height / 2 };
				//if(AETestPointToRect(&EnemyTop, &colliderAABB.pos, this->colliderAABB.width, this->colliderAABB.height))
				//if (this->colldierPos.y >= enemy[i].sprite.pos.y)
					//enemy[i].active = false;
				else
					this->active = false;
			}
		}
	}
}