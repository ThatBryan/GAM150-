#include "Player.h"
#include "Enemy.h"
#include <array>
#include "Utilities.h"
#include "PitchDemo.h"
#include "Graphics.h"

AEGfxTexture* Player::playerTex{ nullptr };
static f32 maxY;
static f32 maxX;
float Player::gravityStrength = 100.0f;

Player::Player(AEGfxTexture* texture, const f32 width, const f32 height) : sprite(texture, width, height), lose{false},
active{ true }, gravity{ false }, jump{ false }, win{ false }, startingPos{ 0, 0 }, vel{ 0, 0 }, jumpspeed_y{jumpspeed},
lives{3}
{
	playerBB.color.SetColor(Color{ 0, 0, 0, 255.0f });
	feetBB.color.SetColor(Color{ 255.0f, 255.0f, 0, 255.0f });
	maxY = static_cast<f32>(AEGetWindowHeight());
	maxX = static_cast<f32>(AEGetWindowWidth());
}

void Player::Reset(void)
{
	jump = false;
	win = false;
	lose = false;
	active = true;
	sprite.pos = startingPos;
	jumpspeed_y = jumpspeed;
	sprite.rotation = 0;
}

void Player::Update() {
	//if(DebugMode)
	//	sprite.rotation += 1;
	CheckOutOfBound();
	Update_Position();
	if (lives <= 0)
		SetLose();
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

	if (!jump && (AEInputCheckTriggered(AEVK_W) || AEInputCheckTriggered(AEVK_UP)))
	{
		if (!DebugMode) {
			jump = TRUE;
			Audio.playAudio(soundTest[static_cast<int>(AudioID::Jump)], AudioID::Jump);
		}
	}
	if (jump)
	{
		if (sprite.pos.y + sprite.height / 2 <= maxY)
		{
			sprite.pos.y -= jumpspeed_y;

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
		if (sprite.pos.x - sprite.width / 2 >= 0)
		sprite.pos.x -= player_speed;
	}
	if (AEInputCheckCurr(AEVK_D) || AEInputCheckCurr(AEVK_RIGHT) && !AEInputCheckCurr(AEVK_W) && !AEInputCheckCurr(AEVK_UP))
	{
		if (sprite.pos.x + sprite.width / 2 <= maxX)
			sprite.pos.x += player_speed;

	}
	if (AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_LEFT) && !AEInputCheckCurr(AEVK_W) && !AEInputCheckCurr(AEVK_UP))
	{
		if (sprite.pos.x - sprite.width / 2 >= 0)
		{
			sprite.pos.x -= player_speed;
		}
	}

	if (DebugMode) {
	AEVec2 Mouse = Utils::GetMousePos();
	if (AETestPointToRect(&Mouse, &sprite.pos, sprite.width, sprite.height))
	{
		if (AEInputCheckCurr(AEVK_LBUTTON))
			sprite.pos = Mouse;
		}
	if (AEInputCheckCurr(AEVK_S) || AEInputCheckCurr(AEVK_DOWN)) {
		if (sprite.pos.y + sprite.height / 2 <= maxY) {
			sprite.pos.y += player_speed;
		}
	}
	if (AEInputCheckCurr(AEVK_W) || AEInputCheckCurr(AEVK_UP)) {
		if (sprite.pos.y - sprite.height / 2 >= 0) {
			sprite.pos.y -= player_speed;
		}
	}

	}
	playerBB.pos = sprite.pos;
	feetBB.pos = AEVec2Set(sprite.pos.x, sprite.pos.y + player_collider_offset);
}

void Player::CheckOutOfBound() {
	if ((sprite.pos.y - sprite.height / 2) > maxY)
		SetLose();
}

void Player::GravityManager(void)
{
	if (gravity && !jump)
	{
		if(!DebugMode)
			sprite.pos.y += gravityStrength * g_dt;
		//if(DebugMode)
			//printf("Apply gravity\n");
	}
}

void Player::CheckEnemyCollision(std::vector <Enemies>& enemy)
{
	for (size_t i = 0; i < enemy.size(); i++)
	{
		if (enemy[i].active)
		{
			if (Utils::ColliderAABB(enemy[i].enemyBB.pos, enemy[i].enemyBB.width, enemy[i].enemyBB.height, playerBB.pos, playerBB.width, playerBB.height))
			{
				if (Utils::ColliderAABB(enemy[i].headBB.pos, enemy[i].headBB.width, enemy[i].headBB.height, feetBB.pos, feetBB.width, feetBB.height)) {
					if (!DebugMode)
						enemy[i].active = false;
					if (DebugMode)
						printf("enemy dies\n");
				}
				else {
					if (!DebugMode) {
						DecreaseLife();
						Reset();
						printf("%d\n", lives);
					}
					if (DebugMode)
						printf("player dies\n");

				}
			}
		}
	}
}