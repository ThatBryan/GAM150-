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



All content � 2021 DigiPen Institute of Technology Singapore. All
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
#include "GameMode.h"

#include <array>
#include <iostream>
#include <fstream>
#include <sstream>   
#include <cstring>
extern std::array <AudioClass, static_cast<int>(AudioID::Max)> AudioArray;
extern AudioManager Audio;
extern LevelSystem LevelSys;

static f32 maxY, maxX;
AEGfxTexture* Player::playerTex{ nullptr };
AEGfxTexture* Player::playerMovTex{ nullptr };
AEGfxTexture* Player::playerParticle{ nullptr };
float Player::gravityStrength = 20.0f;
static const char* UsernameFile{ "./Assets/Username/username.txt" };
static bool isSoundPlayed;

Player::Player(AEGfxTexture* texture, const f32 width, const f32 height) : sprite(texture, Mesh::PlayerCurr, width, height), lose{ false },
active{ true }, gravity{ false }, jump{ false }, chargedjump{ false }, playerWin{ false }, startingPos{ 0, 0 }, vel{ 0, 0 }, jumpvel{ PLAYER_CONST::JUMPVEL },
hp(), direction{ SpriteDirection::Right }, chargedjumpvel{ PLAYER_CONST::CHARGED_JUMPVEL }, gravityMultiplier{ GAMEPLAY_CONST::BASE_GRAVITY_MULTIPLIER },
chargedjump_counter{ PLAYER_CONST::CHARGEDJUMP_COUNTER }, collider(), playerscore { 0 }, playername{"Jumperman"}
{
	maxY = static_cast<f32>(AEGetWindowHeight());
	maxX = static_cast<f32>(AEGetWindowWidth());
}

Player::Player() : lose{ false }, active{ true }, gravity{ false }, jump{ false }, chargedjump{ false },
playerWin{ false }, startingPos{ 0, 0 }, vel{ 0, 0 }, jumpvel{ PLAYER_CONST::JUMPVEL }, chargedjumpvel{ PLAYER_CONST::CHARGED_JUMPVEL },
hp(), direction{ SpriteDirection::Right }, gravityMultiplier{ GAMEPLAY_CONST::BASE_GRAVITY_MULTIPLIER }, chargedjump_counter{ PLAYER_CONST::CHARGEDJUMP_COUNTER }
, collider(), playerscore{ 0 }, playername{ "Jumperman" }{

	maxY = static_cast<f32>(AEGetWindowHeight());
	maxX = static_cast<f32>(AEGetWindowWidth());

}
void Player::Update() {

	if (lose | playerWin)
		return;

	CheckOutOfBound();
	CheckJumpInputs();
	Update_Position();
	UpdateColliders();
	GravityManager();

	if (hp.current <= 0 && GameModeSetting::GetGameMode() == GameMode::Casual) 
		SetPlayerLose();
}
void Player::Render(void)
{
	if (!active)
		return;

	if (Mesh::PlayerCurr == Mesh::Anim)
	{
		sprite.Set_Texture(playerTex);
		sprite.Draw_Texture(20, PLAYER_CONST::PLAYER_IDLE_OFFSET_X, Mesh::PlayerCurr, 255.0f);
	}
	else if (Mesh::PlayerCurr == Mesh::Anim2)
	{
		sprite.Set_Texture(playerMovTex);
		sprite.Draw_Texture(5, PLAYER_CONST::PLAYER_RUN_OFFSET_X, Mesh::PlayerCurr, 255.0f);
	}
	UI::DisplayLife(hp.current);

	if (GAMEPLAY_MISC::DEBUG_MODE) {
		collider.Draw();
	}
}
void Player::SetPlayerLose(void)
{
	lose = true;
	active = false; 
	if (!isSoundPlayed) {
		Audio.playAudio(AudioArray[static_cast<int>(AudioID::PlayerDeath)], AudioID::PlayerDeath);
		isSoundPlayed = true;
	}
}
void Player::LoadTex(void) {
	playerTex		= AEGfxTextureLoad(FP::PLAYER::SpriteSheetIdle);
	playerMovTex	= AEGfxTextureLoad(FP::PLAYER::SpriteSheetRun);
	playerParticle	= AEGfxTextureLoad(FP::PLAYER::Sprite);
	AE_ASSERT_MESG(playerTex, "Failed to create Player spirte sheet Idle");
	AE_ASSERT_MESG(playerMovTex, "Failed to create Player sprite sheet run!");
	AE_ASSERT_MESG(playerParticle, "Failed to create Player Particle texture!");
}

void Player::Unload(void) {
	if (playerTex) {
		AEGfxTextureUnload(playerTex);
		playerTex = nullptr;
	}
	if (playerMovTex) {
		AEGfxTextureUnload(playerMovTex);
		playerMovTex = nullptr;
	}
	if (playerParticle) {
		AEGfxTextureUnload(playerParticle);
		playerParticle = nullptr;
	}
}
void Player::Update_Position(void)
{
	if (jump)
		ApplyJump();

	if (AEInputCheckCurr(AEVK_D) && GAMEPLAY_MISC::AWSD_KEYS || AEInputCheckCurr(AEVK_RIGHT) && GAMEPLAY_MISC::ARROW_KEYS)
	{
		if (sprite.pos.x + sprite.width / 2 <= maxX || GAMEPLAY_MISC::DEBUG_MODE) {

			if(GAMEPLAY_MISC::DEBUG_MODE)
				sprite.pos.x += PLAYER_CONST::DEBUGSPEED * g_dt;
			else
				sprite.pos.x += PLAYER_CONST::SPEED * g_dt;
		}

		if (direction != SpriteDirection::Right) {
			sprite.ReflectAboutYAxis();
			direction = SpriteDirection::Right;
		}
	}
	if (AEInputCheckCurr(AEVK_A) && GAMEPLAY_MISC::AWSD_KEYS || AEInputCheckCurr(AEVK_LEFT) && GAMEPLAY_MISC::ARROW_KEYS)
	if (AEInputCheckCurr(AEVK_A) && GAMEPLAY_MISC::AWSD_KEYS || AEInputCheckCurr(AEVK_LEFT) && GAMEPLAY_MISC::ARROW_KEYS)
	{
		if (sprite.pos.x >= 0 - sprite.width / 2.0f || GAMEPLAY_MISC::DEBUG_MODE) {

			if (GAMEPLAY_MISC::DEBUG_MODE)
				sprite.pos.x -= PLAYER_CONST::DEBUGSPEED * g_dt;
			else
				sprite.pos.x -= PLAYER_CONST::SPEED * g_dt;
		}
		if (direction != SpriteDirection::Left) {
			sprite.ReflectAboutYAxis();
			direction = SpriteDirection::Left;
		}
	}
	if (GAMEPLAY_MISC::DEBUG_MODE) {
		ApplyDebugMovements();
	}
}

void Player::UpdateColliders()
{
	collider.sprite.pos = sprite.pos;
	if (direction == SpriteDirection::Left) {
		collider.bottom.pos = AEVec2Set(sprite.pos.x - PLAYER_CONST::COLLIDER_BTM_OFFSET_X, sprite.pos.y + +sprite.height / 2.0f - collider.bottom.height / 2.0f);
	}
	else {
		collider.bottom.pos = AEVec2Set(sprite.pos.x + PLAYER_CONST::COLLIDER_BTM_OFFSET_X, sprite.pos.y + sprite.height / 2.0f - collider.bottom.height / 2.0f);
	}

	collider.top.pos		= AEVec2Set(sprite.pos.x, sprite.pos.y - sprite.height / 2.0f + collider.top.height / 2.0f);
	collider.left.pos		= AEVec2Set(sprite.pos.x - fabsf(sprite.width / 4.0f), sprite.pos.y);
	collider.right.pos		= AEVec2Set(sprite.pos.x + fabsf(sprite.width / 4.0f), sprite.pos.y);
}

void Player::ApplyDebugMovements()
{
	AEVec2 Mouse = Utils::GetMousePos();
	if (AETestPointToRect(&Mouse, &sprite.pos, sprite.width, sprite.height))
	{
		if (AEInputCheckCurr(AEVK_LBUTTON))
			sprite.pos = Mouse;
	}
	if (AEInputCheckCurr(AEVK_S) && GAMEPLAY_MISC::AWSD_KEYS || AEInputCheckCurr(AEVK_DOWN) && GAMEPLAY_MISC::ARROW_KEYS) {
		if (sprite.pos.y + sprite.height / 2 <= maxY) {
			sprite.pos.y += PLAYER_CONST::DEBUGSPEED * g_dt;
		}
	}
	if (AEInputCheckCurr(AEVK_W) && GAMEPLAY_MISC::AWSD_KEYS || AEInputCheckCurr(AEVK_UP) && GAMEPLAY_MISC::ARROW_KEYS) {
		if (sprite.pos.y - sprite.height / 2 >= 0) {
			sprite.pos.y -= PLAYER_CONST::DEBUGSPEED * g_dt;
		}
	}
}

void Player::ApplyJump()
{
	chargedjump_counter = PLAYER_CONST::CHARGEDJUMP_COUNTER;
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

void Player::CheckJumpInputs()
{
	if (!jump && !gravity) {
		if (AEInputCheckCurr(AEVK_SPACE)) {
			chargedjump_counter -= g_dt;
			// Prevent the particles from spawning when doing a regular jump
			if (chargedjump_counter < (0.7f * PLAYER_CONST::CHARGEDJUMP_COUNTER)) {
				AEVec2 Min = AEVec2Sub(collider.bottom.pos, AEVec2{ sprite.width, 25.0f });
				AEVec2 Max = AEVec2Add(collider.bottom.pos, AEVec2{ sprite.width, 25.0f });
				AEVec2 Destination = AEVec2Add(sprite.pos, AEVec2{ 0, sprite.height / 2.0f });
				Particles::CreateReverseParticles(Destination, Min, Max, Color{ 255.0f, 255.0f, 0, 255.0f }, 1, Utils::RandomRangeFloat(10.0f, 100.0f), 50.0f, 3.0f, 1.0f);
			}
		}
		else if (AEInputCheckReleased(AEVK_SPACE)) {
			jump = true;
			Audio.playAudio(AudioArray[static_cast<int>(AudioID::Jump)], AudioID::Jump);
		}
		if (chargedjump_counter < 0.0f) {
			chargedjump = true;
			chargedjump_counter = PLAYER_CONST::CHARGEDJUMP_COUNTER;
		}
	} // end if !jump && !gravity
	if (chargedjump)
	{
		jump = false;
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
}

void Player::ChangeDirection() {
	sprite.width *= -1.0f;
}

void Player::Respawn(void)
{
	if(--hp.current <= 0)
	active				= false;

	jump				= false;
	jumpvel				= PLAYER_CONST::JUMPVEL;
	sprite.pos			= startingPos;
	chargedjump			= false;
	chargedjumpvel		= PLAYER_CONST::CHARGED_JUMPVEL;
	sprite.rotation		= 0;
	gravityMultiplier	= GAMEPLAY_CONST::BASE_GRAVITY_MULTIPLIER;
	chargedjump_counter = PLAYER_CONST::CHARGEDJUMP_COUNTER;

						  sprite.Set_Texture(playerTex);

	if (GameModeSetting::GetGameMode() == GameMode::TimeAttack) {
		Utils::RestartLevel();
		return;
	}
}
void Player::Reset(void) // For level restart.
{
	lose		= false;
	active		= true;
	playerWin	= false;
	hp.current	= hp.max;
	direction	= SpriteDirection::Right;
}

void Player::CheckOutOfBound() {

	if ((sprite.pos.y - sprite.height / 2) > maxY) {
		Particles::Create(sprite.pos, AEVec2{ 0, -1 }, Color{ 255.0f, 255.0f, 255.0f, 255.0f }, 1, 250.0f, 150.0f, 40.0f, 5.0f, playerParticle);
			Respawn();
	}
	static const float Width{ fabsf(sprite.width / 2.0f) };
	if (sprite.pos.x - Width / 2.0f < 0) {
		sprite.pos.x = Width / 2.0f;
	}

	if (sprite.pos.y - sprite.height / 2.0f <= 0) {
		jumpvel = 0;
		chargedjumpvel = 0;
	}
}
void Player::GravityManager(void)
{
	if (!gravity) // reset counter if player's feet touches the ground
	{
		jumpvel = PLAYER_CONST::JUMPVEL;
		chargedjumpvel = PLAYER_CONST::CHARGED_JUMPVEL;
	}

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
	static std::string str;
	UNREFERENCED_PARAMETER(str);
	if (!playerWin) {
		LevelSys.UnlockNext();
		playerWin = true;

		////std::ifstream ifs(UsernameFile);
		////static std::string line;
		////static std::string data;
		////std::string word = "score:"; std::string word2 = "username:";
		////size_t pos = 0; size_t pos2 = 0;
		////std::string replace = std::to_string(playerscore);

		////if (ifs.is_open()) {
		////	getline(ifs, line);

		////	pos = line.find(word);
		////	pos2 = line.find(word2);
		////	if (pos != std::string::npos)
		////	{
		////		pos += word.length();
		////		pos2 += word2.length();
		////		playername = line.substr(pos2, line.size() - 1);
		////		line.replace(pos, replace.length(), std::to_string(playerscore));
		////	}
		////	ifs.close();
		////}

		////std::ofstream ofs(UsernameFile);

		////if (ofs.is_open())
		////{
		////	ofs << line;
		////	ofs.close();
		////}
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
						return;
					}
				}
				else {
					if (!GAMEPLAY_MISC::DEBUG_MODE) {
						Particles::Create(sprite.pos, AEVec2{ 0, -1 }, Color{ 255.0f, 255.0f, 255.0f, 255.0f }, 1, 250.0f, 150.0f, 40.0f, 5.0f, playerParticle);
							Respawn();
					}
				}
			}
		}
	}
}

void Player::CreatePlayer(Player& player, const AEVec2 pos, const f32 width, const f32 height)
{
	player.sprite.Set(playerTex, width, height, pos, Mesh::PlayerCurr);
	player.startingPos = pos;
	player.sprite.pos = player.startingPos;
	
	player.collider.SetWidthHeight(player.collider.sprite, width, height);
	player.collider.SetWidthHeight(player.collider.top, width - 4.0f, height / 4.0f);
	player.collider.SetWidthHeight(player.collider.left, width / 2.0f - PLAYER_CONST::COLLIDER_SIDE_OFFSET_X, height - 10.0f);
	player.collider.SetWidthHeight(player.collider.right, width / 2.0f - PLAYER_CONST::COLLIDER_SIDE_OFFSET_X, height - 10.0f);
	player.collider.SetWidthHeight(player.collider.bottom, width /2.0f, 5.0f);
	player.collider.SetMeshes();

	player.hp.max = GameModeSetting::GetGameMode() == GameMode::Casual	? PLAYER_CONST::CASUAL_MODE_HP_MAX
																		: PLAYER_CONST::TIMEATK_MODE_HP_MAX;

	player.hp.current = player.hp.max;

	isSoundPlayed = false;
}