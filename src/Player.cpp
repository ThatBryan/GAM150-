#include "Player.h"
#include "Enemy.h"
#include <array>
#include "Utilities.h"
#include "PitchDemo.h"
#include "Graphics.h"

AEGfxTexture* Player::playerTex{ nullptr };
static f32 maxY;
static f32 maxX;
float Player::gravityStrength = 150.0f;

Player::Player(AEGfxTexture* texture, const f32 width, const f32 height) : sprite(texture, width, height), lose{false},
active{ true }, gravity{ false }, jump{ false }, win{ false }, startingPos{ 0, 0 }, vel{ 0, 0 }, jumpvel{player_jumpvel},
lives{3}, direction{MovementState::Right}
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
	jumpvel = player_jumpvel;
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
	playerTex = AEGfxTextureLoad(FP::PlayerSprite);
	AE_ASSERT_MESG(playerTex, "Failed to create texture!");
}

void Player::Unload(void) {
	AEGfxTextureUnload(playerTex);
}
void Player::Update_Position(void)
{

	if (!jump && !gravity && (AEInputCheckTriggered(AEVK_W) || AEInputCheckTriggered(AEVK_UP)))
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
			sprite.pos.y -= jumpvel;

			jumpvel -= 0.2f; // velocity decrease as y increases
			if (jumpvel < -5.0f)
			{
				jump = false;
				jumpvel = 5.0f;
			}
			if (!gravity) // reset counter if player's feet touches the ground
			{
				jumpvel = 5.0f;
			}
		}
	}
	if (AEInputCheckCurr(AEVK_D) || AEInputCheckCurr(AEVK_RIGHT))
	{
		if (sprite.pos.x + sprite.width / 2 <= maxX)
			sprite.pos.x += player_speed * g_dt;

		if (direction != MovementState::Right) {
			sprite.ReflectAboutYAxis();
			direction = MovementState::Right;
		}
	}

	if (AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_LEFT))
	{
		if (sprite.pos.x >= 0 - sprite.width / 2.0f)
			sprite.pos.x -= player_speed * g_dt;

		if (direction != MovementState::Left) {
			sprite.ReflectAboutYAxis();
			direction = MovementState::Left;
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
			sprite.pos.y += player_speed * g_dt;
		}
	}
	if (AEInputCheckCurr(AEVK_W) || AEInputCheckCurr(AEVK_UP)) {
		if (sprite.pos.y - sprite.height / 2 >= 0) {
			sprite.pos.y -= player_speed * g_dt;
		}
	}
	}
	playerBB.pos = sprite.pos;
	feetBB.pos = AEVec2Set(sprite.pos.x + player_collider_offset_x, sprite.pos.y + player_collider_offset_y);
}

void Player::ChangeDirection() {
	sprite.width *= -1.0f;
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
		if (!enemy[i].getKilled())
		{
			if (Utils::ColliderAABB(enemy[i].enemyBB.pos, enemy[i].enemyBB.width, enemy[i].enemyBB.height, playerBB.pos, playerBB.width, playerBB.height))
			{
				if (Utils::ColliderAABB(enemy[i].headBB.pos, enemy[i].headBB.width, enemy[i].headBB.height, feetBB.pos, sprite.width, feetBB.height)) {
					if (!DebugMode)
						enemy[i].setKilled();
					if (DebugMode)
						printf("enemy dies\n");
				}
				else {
					if (!DebugMode) {
						DecreaseLife();
						UI::DecreaseLife();
						if(lives > 0)
							Reset();
					}
					if (DebugMode)
						printf("player dies\n");
				}
			}
		}
	}
}