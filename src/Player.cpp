/******************************************************************************/
/*!
\file				Player.cpp
\primary author: 	Bryan Koh Yan Wei
\secondary author:	Seet Min Yi, Lim Wee Boon
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021

\brief				Function definition for the player type.
	
					Functionalities inclueds:

					Initializing/Loading of player data members.
					Update function.
					Render function
					Accessor/Modifiers.



All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.

 */
 /******************************************************************************/
#include "Player.h"
#include "Enemy.h"
#include "Utilities.h"
#include "Graphics.h"
#include "Particles.h"
#include "UserInterface.h"
#include "LevelSystem.h"
#include "Globals.h"

#include <array>
#include <iostream>

extern std::array <AudioClass, static_cast<int>(AudioID::Max)> soundTest;
extern AudioManager Audio;
extern LevelSystem LevelSys;

static f32 maxY;
static f32 maxX;
AEGfxTexture* Player::playerTex{ nullptr };
AEGfxTexture* Player::playerMovTex{ nullptr };
AEGfxTexture* Player::playerParticle{ nullptr };
float Player::gravityStrength = 20.0f;

Player::Player(AEGfxTexture* texture, const f32 width, const f32 height) : sprite(texture, Mesh::PlayerCurr, width, height), lose{ false },
active{ true }, gravity{ false }, jump{ false }, chargedjump{ false }, win{ false }, startingPos{ 0, 0 }, vel{ 0, 0 }, jumpvel{ PLAYER_CONST::JUMPVEL },
hp(), direction{ SpriteDirection::Right }, chargedjumpvel{ PLAYER_CONST::CHARGED_JUMPVEL }, gravityMultiplier{ GAMEPLAY_CONST::BASE_GRAVITY_MULTIPLIER },
chargedjump_counter{ PLAYER_CONST::CHARGEDJUMP_COUNTER }, collider()
{
	maxY = static_cast<f32>(AEGetWindowHeight());
	maxX = static_cast<f32>(AEGetWindowWidth());
	hp.max = PLAYER_CONST::HP_MAX;
	hp.current = PLAYER_CONST::HP_MAX;
}

Player::Player() : lose{ false }, active{ true }, gravity{ false }, jump{ false }, chargedjump{ false },
win{ false }, startingPos{ 0, 0 }, vel{ 0, 0 }, jumpvel{ PLAYER_CONST::JUMPVEL }, chargedjumpvel{ PLAYER_CONST::CHARGED_JUMPVEL },
hp(), direction{ SpriteDirection::Right }, gravityMultiplier{ GAMEPLAY_CONST::BASE_GRAVITY_MULTIPLIER }, chargedjump_counter{ PLAYER_CONST::CHARGEDJUMP_COUNTER }
, collider(){

	maxY = static_cast<f32>(AEGetWindowHeight());
	maxX = static_cast<f32>(AEGetWindowWidth());
	hp.max = PLAYER_CONST::HP_MAX;
	hp.current = PLAYER_CONST::HP_MAX;
}

void Player::Reset(void)
{
	/*jump = false;
	chargedjump = false;
	win = false;
	lose = false;
	active = true;
	sprite.pos = startingPos;
	sprite.Set_Texture(playerTex);
	jumpvel = player_jumpvel;
	chargedjumpvel = player_chargedjumpvel;
	chargedjump_counter = player_chargedjump_counter;*/
	
	Respawn();
	hp.current = hp.max;
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
	if (Mesh::PlayerCurr == Mesh::Anim)
	{
		sprite.Set_Texture(playerTex);
	}
	else if (Mesh::PlayerCurr == Mesh::Anim2)
	{
		sprite.Set_Texture(playerMovTex);
	}
	sprite.Draw_Texture(20, PLAYER_CONST::PLAYER_IDLE_OFFSET_X, Mesh::PlayerCurr, 255.0f);
	UI::DisplayLife(hp.current);

	if (GAMEPLAY_MISC::DEBUG_MODE) {
		collider.Draw();
	}
}
void Player::LoadTex(void) {
	playerTex = AEGfxTextureLoad(FP::PlayerSpriteSheetIdle);
	playerMovTex = AEGfxTextureLoad(FP::WaterSlimeSprite);
	playerParticle = AEGfxTextureLoad(FP::PlayerSprite);
	AE_ASSERT_MESG(playerTex, "Failed to create texture!");
	AE_ASSERT_MESG(playerMovTex, "Failed to create texture!");
	AE_ASSERT_MESG(playerParticle, "Failed to create texture!");
}

void Player::Unload(void) {
	AEGfxTextureUnload(playerTex);
	AEGfxTextureUnload(playerMovTex);
	AEGfxTextureUnload(playerParticle);

	// if (playerTex) {
	// 	AEGfxTextureUnload(playerTex);
	// 	playerTex = nullptr;
	// }
}
void Player::Update_Position(void)
{

	if (!jump && !gravity && (AEInputCheckTriggered(AEVK_W) || AEInputCheckTriggered(AEVK_UP)))
	{
		if (!GAMEPLAY_MISC::DEBUG_MODE) {
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
				jumpvel = PLAYER_CONST::JUMPVEL;
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
				chargedjumpvel = PLAYER_CONST::CHARGED_JUMPVEL;
			}
		}
	}

	if (!gravity) // reset counter if player's feet touches the ground
	{
		jumpvel = PLAYER_CONST::JUMPVEL;
		chargedjumpvel = PLAYER_CONST::CHARGED_JUMPVEL;
	}

	if (AEInputCheckCurr(AEVK_D) || AEInputCheckCurr(AEVK_RIGHT))
	{
		if (sprite.pos.x + sprite.width / 2 <= maxX)
			sprite.pos.x += PLAYER_CONST::SPEED * g_dt;

		if (direction != SpriteDirection::Right) {
			sprite.ReflectAboutYAxis();
			direction = SpriteDirection::Right;
		}

	}

	if (AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_LEFT))
	{
		if (sprite.pos.x >= 0 - sprite.width / 2.0f)
			sprite.pos.x -= PLAYER_CONST::SPEED * g_dt;

		if (direction != SpriteDirection::Left) {
			sprite.ReflectAboutYAxis();
			direction = SpriteDirection::Left;
		}

	}

	if (GAMEPLAY_MISC::DEBUG_MODE) {
		AEVec2 Mouse = Utils::GetMousePos();
		if (AETestPointToRect(&Mouse, &sprite.pos, sprite.width, sprite.height))
		{
			if (AEInputCheckCurr(AEVK_LBUTTON))
				sprite.pos = Mouse;
		}
		if (AEInputCheckCurr(AEVK_S) || AEInputCheckCurr(AEVK_DOWN)) {
			if (sprite.pos.y + sprite.height / 2 <= maxY) {
				sprite.pos.y += PLAYER_CONST::SPEED * g_dt;
			}
		}
		if (AEInputCheckCurr(AEVK_W) || AEInputCheckCurr(AEVK_UP)) {
			if (sprite.pos.y - sprite.height / 2 >= 0) {
				sprite.pos.y -= PLAYER_CONST::SPEED * g_dt;
			}
		}
	}
	collider.sprite.pos = sprite.pos;
	if (direction == SpriteDirection::Left) {
		collider.bottom.pos = AEVec2Set(sprite.pos.x - PLAYER_CONST::COLLIDER_OFFSET_X, sprite.pos.y + +sprite.height / 2.0f - collider.bottom.height / 2.0f);
	}
	else {
		collider.bottom.pos = AEVec2Set(sprite.pos.x + PLAYER_CONST::COLLIDER_OFFSET_X, sprite.pos.y + sprite.height / 2.0f - collider.bottom.height / 2.0f);
	}
	collider.top.pos = AEVec2Set(sprite.pos.x, sprite.pos.y - sprite.height / 2.0f + collider.top.height / 2.0f);
	collider.right.pos = AEVec2Set(sprite.pos.x + abs(sprite.width) / 4.0f, sprite.pos.y);
	collider.left.pos = AEVec2Set(sprite.pos.x - abs(sprite.width) / 4.0f, sprite.pos.y);
}

void Player::ChangeDirection() {
	sprite.width *= -1.0f;
}

void Player::Respawn(void)
{
	jump = false;
	chargedjump = false;
	win = false;
	lose = false;
	active = true;
	sprite.rotation = 0;
	sprite.pos = startingPos;
	sprite.Set_Texture(playerTex);
	jumpvel = PLAYER_CONST::JUMPVEL;
	chargedjumpvel = PLAYER_CONST::CHARGED_JUMPVEL;
	chargedjump_counter = PLAYER_CONST::CHARGEDJUMP_COUNTER;
	gravityMultiplier = GAMEPLAY_CONST::BASE_GRAVITY_MULTIPLIER;

	static const float spriteWidth{ fabsf(sprite.width) };
	if (sprite.pos.x - (spriteWidth / 2.0f) <= 0) {
		sprite.pos.x = spriteWidth / 2.0f;
	}
}

void Player::CheckOutOfBound() {
	if ((sprite.pos.y - sprite.height / 2) > maxY) {
		--hp.current;
		Particles::Create(sprite.pos, AEVec2{ 0, -1 }, Color{ 255.0f, 255.0f, 255.0f, 255.0f }, 1, 250.0f, 150.0f, 40.0f, 5.0f, playerParticle);
		if(hp.current >= 1)
			Respawn();
	}

	if (sprite.pos.x - (sprite.width / 2.0f) < 0) {
		sprite.pos.x = sprite.width / 2.0f;
	}

	if (sprite.pos.y - sprite.height / 2.0f <= 0) {
		jumpvel = 0;
		chargedjumpvel = 0;
	}
}
void Player::GravityManager(void)
{
	if (gravity && !jump && !chargedjump)
	{
		if (!GAMEPLAY_MISC::DEBUG_MODE) {
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
	static const float bounceVelocity{ PLAYER_CONST::JUMPVEL * 1.5f };
	for (size_t i = 0; i < enemy.size(); i++)
	{
		if (!enemy[i].GetKilledStatus())
		{
			if (Utils::ColliderAABB(enemy[i].collider.sprite.pos, enemy[i].collider.sprite.width, enemy[i].collider.sprite.height, 
				collider.sprite.pos, collider.sprite.width, collider.sprite.height))
			{
				if (Utils::ColliderAABB(enemy[i].collider.top.pos, enemy[i].collider.top.width, enemy[i].collider.top.height, 
					collider.bottom.pos, collider.bottom.width, collider.bottom.height)) {
					if (!GAMEPLAY_MISC::DEBUG_MODE) {
						jump = true;
						jumpvel = bounceVelocity;
						gravityMultiplier = GAMEPLAY_CONST::BASE_GRAVITY_MULTIPLIER;
						enemy[i].KillEnemy();
						continue;
					}
					if (GAMEPLAY_MISC::DEBUG_MODE)
						printf("enemy dies\n");
				}
				else {
					if (!GAMEPLAY_MISC::DEBUG_MODE) {
						--hp.current;
						Particles::Create(sprite.pos, AEVec2{ 0, -1 }, Color{ 255.0f, 255.0f, 255.0f, 255.0f }, 1, 250.0f, 150.0f, 40.0f, 5.0f, playerParticle);
						if(hp.current >= 1)
							Respawn();
					}
					if (GAMEPLAY_MISC::DEBUG_MODE)
						printf("player dies\n");
				}
			}
		}
	}
}

void Player::CreatePlayer(Player& player, const AEVec2 pos, const f32 width, const f32 height)
{
	player.sprite.Set(playerTex, width, height, pos, Mesh::PlayerCurr);

	player.startingPos = pos;
	player.sprite.pos = pos;

	player.collider.SetWidthHeight(player.collider.sprite, width, height);
	player.collider.SetWidthHeight(player.collider.top, PLAYER_CONST::WIDTH - 4.0f, 5.0f);
	player.collider.SetWidthHeight(player.collider.left, 20.0f, PLAYER_CONST::HEIGHT - 10.0f);
	player.collider.SetWidthHeight(player.collider.right, 20.0f, PLAYER_CONST::HEIGHT - 10.0f);
	player.collider.SetWidthHeight(player.collider.bottom, PLAYER_CONST::WIDTH / 1.6f, 5.0f);
	player.collider.SetMeshes();
}