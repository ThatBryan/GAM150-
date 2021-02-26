#include "Player.h"

AEGfxTexture* Player::playerTex{ nullptr };

Player::Player(AEGfxTexture* texture, const f32 width, const f32 height) : sprite(texture, width, height),
active{ true }, gravity{ false }, jump{ false }, win{ false }, startingPos{ 0, 0 }, vel{ 0, 0 }
{
	playerBB.color.SetColor(0, 0, 0, 255.0f);
	feetBB.color.SetColor(255.0f, 255.0f, 0, 255.0f);
}

void Player::Reset(void)
{
	jump = false;
	win = false;
	active = true;
	sprite.pos = startingPos;
}

void Player::Update() {
	if (!paused) {
		//sprite.direction += 1;
		Update_Position();
	}
	Render();
}
void Player::Render(void)
{
	sprite.Draw_Texture(255.0f);
	
	if (DebugMode) {
		playerBB.Draw();
		feetBB.Draw();
	}
}
void Player::LoadTex(void) {
	playerTex = AEGfxTextureLoad(PlayerSprite);
	AE_ASSERT_MESG(playerTex, "Failed to create texture!");
}

void Player::Unload(void) {
	AEGfxTextureUnload(playerTex);
}
void Player::Update_Position(void)
{
	static f32 maxY = AEGfxGetWinMaxY();
	static f32 maxX = AEGfxGetWinMaxX();
	static f32 minY = AEGfxGetWinMinY();
	static f32 minX = AEGfxGetWinMinX();
	static float jumpspeed_y = 5.0f;

	if (AEInputCheckCurr(AEVK_W) || AEInputCheckCurr(AEVK_UP) && this->jump == FALSE)
	{
		sound.playSound(soundTest[JUMP], JUMP);
		jump = TRUE;
	}
	if (jump)
	{
		if (sprite.pos.y + sprite.height / 2 <= maxY)
		{
			sprite.pos.y += jumpspeed_y;

			jumpspeed_y -= .2f;
			if (jumpspeed_y < -5.0f)
			{
				jump = FALSE;
				jumpspeed_y = 5.0f;
			}
		}
	}
	if (AEInputCheckCurr(AEVK_D) || AEInputCheckCurr(AEVK_RIGHT))
	{
		if (sprite.pos.x + sprite.width / 2 <= maxX)
			sprite.pos.x += player_speed;
	}

	if (AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_LEFT))
	{
		if (sprite.pos.x - sprite.width / 2 >= minX)
		sprite.pos.x -= player_speed;
	}

	if (AEInputCheckCurr(AEVK_S) || AEInputCheckCurr(AEVK_DOWN) && !AEInputCheckCurr(AEVK_W) && !AEInputCheckCurr(AEVK_UP))
	{
		if (sprite.pos.y - sprite.height / 2 >= 0)
		{
			sprite.pos.y -= player_speed;
		}
	}
	if (AEInputCheckCurr(AEVK_D) || AEInputCheckCurr(AEVK_RIGHT) && !AEInputCheckCurr(AEVK_W) && !AEInputCheckCurr(AEVK_UP))
	{
		if (sprite.pos.x + sprite.width / 2 <= maxX)
			sprite.pos.x += player_speed;

	}
	if (AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_LEFT) && !AEInputCheckCurr(AEVK_W) && !AEInputCheckCurr(AEVK_UP))
	{
		if (sprite.pos.x - sprite.width / 2 >= minX)
		{
			sprite.pos.x -= player_speed;
		}
	}

	if (DebugMode) {
	AEVec2 Mouse = Utilities::GetMousePos();
	if (AETestPointToRect(&Mouse, &sprite.pos, sprite.width, sprite.height))
	{
		if (AEInputCheckCurr(AEVK_LBUTTON))
			sprite.pos = Mouse;
		}
	}
	playerBB.pos = sprite.pos;
	feetBB.pos = AEVec2{ sprite.pos.x, sprite.pos.y - player_collider_offset };
}

//void Player::GravityManager(void)
//{
//	if (gravity)
//	{
//		if(DebugMode)
//			printf("Apply gravity\n");
//	}
//}

void Player::CheckEnemyCollision(std::vector <Enemies>& enemy)
{
	if (AEInputCheckCurr(AEVK_SPACE))
		printf("\n");
	for (size_t i = 0; i < enemy.size(); i++)
	{
		if (enemy[i].ID == 1 && enemy[i].active)
		{
			//printf("%.2f %.2f %.2f %.2f\n", enemy[i].headBB.pos.x, this->playerBB.pos.x, enemy[i].headBB.pos.y, this->playerBB.pos.y);
			//enemy[i].headBB.pos.y -= 15.0f;
			//if (AETestRectToRect(&enemy[i].headBB.pos, enemy[i].headBB.width, enemy[i].headBB.height, &this->feetBB.pos, feetBB.width, feetBB.height))// && 
			//	printf("enemy dies\n");
			//	//enemy[i].active = false;
			if (AETestRectToRect(&enemy[i].enemyBB.pos, enemy[i].enemyBB.width, enemy[i].enemyBB.height, &playerBB.pos, playerBB.width, playerBB.height))
			{
			if (enemy[i].headBB.pos.y < feetBB.pos.y) {
				printf("enemy dies\n");
				enemy[i].active = false;
			}
			else {
				printf("player dies\n");
				active = false;
			}
				//active = false;
			}
		}
	}
}