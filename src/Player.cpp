#include "Player.h"
#include "Enemy.h"
#include <array>
#include "Utilities.h"
#include "Graphics.h"
#include "Particles.h"
#include "UserInterface.h"
#include "LevelSystem.h"
#include <iostream>

extern std::array <AudioClass, static_cast<int>(AudioID::Max)> soundTest;
extern AudioManager Audio;
extern LevelSystem LevelSys;

AEGfxTexture* Player::playerTex{ nullptr };
static f32 maxY;
static f32 maxX;
float Player::gravityStrength = 150.0f;


Player::Player(AEGfxTexture* texture, const f32 width, const f32 height) : sprite(texture, width, height), lose{false},
active{ true }, gravity{ false }, jump{ false }, chargedjump{ false }, win{ false }, startingPos{ 0, 0 }, vel{ 0, 0 }, jumpvel{ player_jumpvel },
hp(), direction{MovementState::Right}, chargedjumpvel{ player_chargedjumpvel }, gravityMultiplier{ player_base_gravityMultiplier }
{
	playerBB.color.Set(Color{ 0, 0, 0, 255.0f });
	maxY = static_cast<f32>(AEGetWindowHeight());
	maxX = static_cast<f32>(AEGetWindowWidth());
	hp.max = player_hp_max;
	hp.current = player_hp_max;
}

Player::Player() : lose{ false }, active{ true }, gravity{ false }, jump{ false }, chargedjump { false },
win{ false }, startingPos{ 0, 0 }, vel{ 0, 0 }, jumpvel{ player_jumpvel }, chargedjumpvel{ player_chargedjumpvel },
hp(), direction{ MovementState::Right }, gravityMultiplier{ player_base_gravityMultiplier } {

	playerBB.color.Set(Color{ 0, 0, 0, 255.0f });

	maxY = static_cast<f32>(AEGetWindowHeight());
	maxX = static_cast<f32>(AEGetWindowWidth());
	hp.max = player_hp_max;
	hp.current = player_hp_max;
}

void Player::Reset(void)
{
	jump = false;
	chargedjump = false;
	win = false;
	lose = false;
	active = true;
	sprite.pos = startingPos;
	jumpvel = player_jumpvel;
	chargedjumpvel = player_chargedjumpvel;
	hp.current = hp.max;
	sprite.rotation = 0;
	gravityMultiplier = player_base_gravityMultiplier;
	direction = MovementState::Right;
}

void Player::Update() {
	CheckOutOfBound();
	Update_Position();
	if (hp.current <= 0)
		SetPlayerLose();
}
void Player::Render(void)
{
	sprite.Draw_Texture(255.0f);
	UI::DisplayLife(hp.current);
	
	if (DebugMode) {
		collider.Draw();
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
			jump = true;
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
		}
	}

	static float chargedjump_counter = 1.0f;
	if (AEInputCheckCurr(AEVK_SPACE) && !chargedjump && !gravity)
	{
		chargedjump_counter -= g_dt;
		if (chargedjump_counter < 0)
		{
			chargedjump = true;
			jump = false;

		}
		
		//printf("%.2f\n", chargedjump_counter);
	}
	if (AEInputCheckReleased(AEVK_SPACE))
	{
		chargedjump = false;
		chargedjump_counter = 1.0f;
	}
	if (chargedjump)
	{
		//printf("chargedjump\n");
		if (sprite.pos.y + sprite.height / 2 <= maxY)
		{
			sprite.pos.y -= chargedjumpvel;

			chargedjumpvel -= 0.2f; // velocity decrease as y increases
			if (chargedjumpvel < -10.0f)
			{
				chargedjump = false;
				chargedjumpvel = 10.0f;
			}
		}
	}

	if (!gravity) // reset counter if player's feet touches the ground
	{
		jumpvel = 5.0f;
		chargedjumpvel = 10.0f;
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
	if (direction == MovementState::Left) {
		//bottomBB.pos = AEVec2Set(sprite.pos.x - player_collider_offset_x, sprite.pos.y + +sprite.height / 2.0f - bottomBB.height / 2.0f);
		collider.bottomBB.pos = AEVec2Set(sprite.pos.x - player_collider_offset_x, sprite.pos.y + +sprite.height / 2.0f - collider.bottomBB.height / 2.0f);
	}
	else {
		//bottomBB.pos = AEVec2Set(sprite.pos.x + player_collider_offset_x, sprite.pos.y + sprite.height / 2.0f - bottomBB.height / 2.0f);
		collider.bottomBB.pos = AEVec2Set(sprite.pos.x + player_collider_offset_x, sprite.pos.y + sprite.height / 2.0f - collider.bottomBB.height / 2.0f);
	}
	collider.topBB.pos = AEVec2Set(sprite.pos.x, sprite.pos.y - sprite.height / 2.0f);
	collider.rightBB.pos = AEVec2Set(sprite.pos.x + abs(sprite.width) / 4.0f, sprite.pos.y);
	collider.leftBB.pos = AEVec2Set(sprite.pos.x - abs(sprite.width) / 4.0f, sprite.pos.y);
}

void Player::ChangeDirection() {
	sprite.width *= -1.0f;
}

void Player::CheckOutOfBound() {
	if ((sprite.pos.y - sprite.height / 2) > maxY)
		SetPlayerLose();

	// Resolve collision conflict on spawn
	if (sprite.pos.x - (sprite.width / 2.0f) < 0) {
		sprite.pos.x = sprite.width / 2.0f;
	}
	//std::cout << sprite.pos.x << std::endl;
}
void Player::GravityManager(void)
{
	if (gravity && !jump && !chargedjump)
	{
		if (!DebugMode) {
			gravityMultiplier += g_dt;
			sprite.pos.y += (gravityStrength * (g_dt * gravityMultiplier));
		}
	}
}

void Player::SetPlayerWin(void)
{
	if (!win) {
		LevelSys.UnlockNext();
		win = true;
	}
}

void Player::CheckEnemyCollision(std::vector <Enemies>& enemy)
{
	for (size_t i = 0; i < enemy.size(); i++)
	{
		if (!enemy[i].GetKilledStatus())
		{
			if (Utils::ColliderAABB(enemy[i].enemyBB.pos, enemy[i].enemyBB.width, enemy[i].enemyBB.height, playerBB.pos, playerBB.width, playerBB.height))
			{
				if (Utils::ColliderAABB(enemy[i].topBB.pos, enemy[i].topBB.width, enemy[i].topBB.height, collider.bottomBB.pos, collider.bottomBB.width, collider.bottomBB.height)) {
					if (!DebugMode)
						enemy[i].KillEnemy();

					if (DebugMode)
						printf("enemy dies\n");
				}
				else {
					if (!DebugMode) {
						sprite.pos = startingPos;
						--hp.current;
					}
					if (DebugMode)
						printf("player dies\n");
				}
			}
		}
	}
}

void Player::CreatePlayer(Player& player, const AEVec2 pos, const f32 width, const f32 height)
{
	player.sprite.Init(FP::PlayerSprite, width, height, pos);
	player.startingPos = pos;
	player.sprite.pos = pos;
	player.playerBB.width = width;
	player.playerBB.height = height;

	player.collider.SetWidthHeight(player.collider.topBB, player_width, 5.0f);
	player.collider.SetWidthHeight(player.collider.leftBB, 20.0f, player_height - 10.0f);
	player.collider.SetWidthHeight(player.collider.rightBB, 20.0f, player_height - 10.0f);
	player.collider.SetWidthHeight(player.collider.bottomBB, player_width / 2.0f, 5.0f);
	player.collider.SetMeshes();
}
