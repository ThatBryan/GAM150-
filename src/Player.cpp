
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

static f32 maxY;
static f32 maxX;
AEGfxTexture* Player::playerTex{ nullptr };
AEGfxTexture* Player::playerMovTex{ nullptr };
float Player::gravityStrength = 20.0f;


Player::Player(AEGfxTexture* texture, const f32 width, const f32 height) : sprite(texture, Mesh::PlayerCurr, width, height), lose{false},
active{ true }, gravity{ false }, jump{ false }, chargedjump{ false }, win{ false }, startingPos{ 0, 0 }, vel{ 0, 0 }, jumpvel{ player_jumpvel },
hp(), direction{ SpriteDirection::Right }, chargedjumpvel{ player_chargedjumpvel }, gravityMultiplier{ base_gravityMultiplier }, 
chargedjump_counter{ player_chargedjump_counter }, collider()
{
	maxY = static_cast<f32>(AEGetWindowHeight());
	maxX = static_cast<f32>(AEGetWindowWidth());
	hp.max = player_hp_max;
	hp.current = player_hp_max;
}

Player::Player() : lose{ false }, active{ true }, gravity{ false }, jump{ false }, chargedjump{ false },
win{ false }, startingPos{ 0, 0 }, vel{ 0, 0 }, jumpvel{ player_jumpvel }, chargedjumpvel{ player_chargedjumpvel },
hp(), direction{ SpriteDirection::Right }, gravityMultiplier{ base_gravityMultiplier }, chargedjump_counter{player_chargedjump_counter }
, collider(){

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
	chargedjump_counter = player_chargedjump_counter;
	hp.current = hp.max;
	sprite.rotation = 0;
	gravityMultiplier = base_gravityMultiplier;
	direction = SpriteDirection::Right;
}

void Player::Update() {
	CheckOutOfBound();
	Update_Position();
	if (hp.current <= 0)
		SetPlayerLose();
	GravityManager();
}
void Player::Render(void)
{
	if(Mesh::PlayerCurr == Mesh::Anim)
		sprite.Draw_Texture(30, playerTex, Mesh::PlayerCurr, 255.0f);
	else if (Mesh::PlayerCurr == Mesh::Anim2)
		sprite.Draw_Texture(30, playerMovTex, Mesh::PlayerCurr, 255.0f);
	UI::DisplayLife(hp.current);

	if (DebugMode) {
		collider.Draw();
	}
}
void Player::LoadTex(void) {
	playerTex = AEGfxTextureLoad(FP::PlayerSpriteSheetIdle);
	playerMovTex = AEGfxTextureLoad(FP::WaterSlimeSprite);
	AE_ASSERT_MESG(playerTex, "Failed to create texture!");
	AE_ASSERT_MESG(playerMovTex, "Failed to create texture!");
}

void Player::Unload(void) {
	AEGfxTextureUnload(playerTex);
	AEGfxTextureUnload(playerMovTex);

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
			jumpvel -= 0.1f; // velocity decrease as y increases
			if (jumpvel <= 0)
			{
				jump = false;
				jumpvel = player_jumpvel;
			}
		}
	}

	if (AEInputCheckCurr(AEVK_SPACE) && !chargedjump && !gravity)
	{
		chargedjump_counter -= g_dt;
		AEVec2 Min = AEVec2Sub(collider.bottom.pos, AEVec2{ sprite.width, 25.0f});
		AEVec2 Max = AEVec2Add(collider.bottom.pos, AEVec2{ sprite.width, 25.0f});
		AEVec2 Destination = AEVec2Add(sprite.pos, AEVec2{ 0, sprite.height / 2.0f });
		Particles::CreateReverseParticles(Destination, Min, Max, Color{ 255.0f, 255.0f, 0, 255.0f}, 1, Utils::RandomRangeFloat(10.0f, 100.0f), 50.0f, 3.0f, 1.0f);
		//std::cout << Particles::GetContainerSize() << std::endl;
	}

	if (AEInputCheckReleased(AEVK_SPACE) && chargedjump_counter < 0)
	{
		chargedjump = true;
		chargedjump_counter = 1.0f;
	}
	if (chargedjump)
	{
		if (sprite.pos.y + sprite.height / 2 <= maxY)
		{
			sprite.pos.y -= chargedjumpvel;

			chargedjumpvel -= 0.2f; // velocity decrease as y increases
			if (chargedjumpvel < 0.0f)
			{
				chargedjump = false;
				chargedjumpvel = player_chargedjumpvel;
			}
			//if (chargedjumpvel < -player_chargedjumpvel)
			//{
			//	chargedjump = false;
			//	chargedjumpvel = player_chargedjumpvel;
			//}
		}
	}

	if (!gravity) // reset counter if player's feet touches the ground
	{
		jumpvel = player_jumpvel;
		chargedjumpvel = player_chargedjumpvel;
	}

	if (AEInputCheckCurr(AEVK_D) || AEInputCheckCurr(AEVK_RIGHT))
	{
		if (sprite.pos.x + sprite.width / 2 <= maxX)
			sprite.pos.x += player_speed * g_dt;

		if (direction != SpriteDirection::Right) {
			sprite.ReflectAboutYAxis();
			direction = SpriteDirection::Right;
		}

	}

	if (AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_LEFT))
	{
		if (sprite.pos.x >= 0 - sprite.width / 2.0f)
			sprite.pos.x -= player_speed * g_dt;

		if (direction != SpriteDirection::Left) {
			sprite.ReflectAboutYAxis();
			direction = SpriteDirection::Left;
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
	collider.sprite.pos = sprite.pos;
	if (direction == SpriteDirection::Left) {
		collider.bottom.pos = AEVec2Set(sprite.pos.x - player_collider_offset_x, sprite.pos.y + +sprite.height / 2.0f - collider.bottom.height / 2.0f);
	}
	else {
		collider.bottom.pos = AEVec2Set(sprite.pos.x + player_collider_offset_x, sprite.pos.y + sprite.height / 2.0f - collider.bottom.height / 2.0f);
	}
	collider.top.pos = AEVec2Set(sprite.pos.x, sprite.pos.y - sprite.height / 2.0f + collider.top.height / 2.0f);
	collider.right.pos = AEVec2Set(sprite.pos.x + abs(sprite.width) / 4.0f, sprite.pos.y);
	collider.left.pos = AEVec2Set(sprite.pos.x - abs(sprite.width) / 4.0f, sprite.pos.y);
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
}
void Player::GravityManager(void)
{
	if (gravity && !jump && !chargedjump)
	{
		if (!DebugMode) {
			gravityMultiplier += g_dt * 20;
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
			if (Utils::ColliderAABB(enemy[i].collider.sprite.pos, enemy[i].collider.sprite.width, enemy[i].collider.sprite.height, 
				collider.sprite.pos, collider.sprite.width, collider.sprite.height))
			{
				if (Utils::ColliderAABB(enemy[i].collider.top.pos, enemy[i].collider.top.width, enemy[i].collider.top.height, 
					collider.bottom.pos, collider.bottom.width, collider.bottom.height)) {
					if (!DebugMode) {
						jump = true;
						jumpvel += player_jumpvel / 2.0f;
						gravityMultiplier = base_gravityMultiplier;
						enemy[i].KillEnemy();
					}
					if (DebugMode)
						printf("enemy dies\n");
				}
				else {
					if (!DebugMode) {
						--hp.current;
						Particles::Create(sprite.pos, AEVec2{ 0, -1 }, Color{ 255.0f, 255.0f, 255.0f, 255.0f }, 1, 250.0f, 150.0f, 40.0f, 5.0f, playerTex);
						sprite.pos = startingPos;
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
	player.sprite.Init(FP::PlayerSpriteSheetIdle, width, height, pos, Mesh::PlayerCurr);
	player.startingPos = pos;
	player.sprite.pos = pos;

	player.collider.SetWidthHeight(player.collider.sprite, width, height);
	player.collider.SetWidthHeight(player.collider.top, player_width - 4.0f, 5.0f);
	player.collider.SetWidthHeight(player.collider.left, 20.0f, player_height - 10.0f);
	player.collider.SetWidthHeight(player.collider.right, 20.0f, player_height - 10.0f);
	player.collider.SetWidthHeight(player.collider.bottom, player_width / 2.0f, 5.0f);
	player.collider.SetMeshes();
}