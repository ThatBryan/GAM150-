/******************************************************************************/
/*!
\file				Enemy.cpp
\primary author: 	Bryan Koh Yan Wei
\Secondary author:	Seet Min Yi
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Source file of an Enemy class implementation.

					Functionalities include:

					Creating of enemies.
					Updating of enemies.
					Rendering of enemies.
					Load/unloading of texture pointers for the enemies.
					Enemy & Tile collision
					Accessors/Modifiers for the data members.

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#include "Enemy.h"
#include "Tiles.h"
#include "Utilities.h"
#include "Particles.h"
#include "Globals.h"

#include <iostream>

float Enemies::baseGravityStrength = 20.0f;

float Enemies::slime_counter = 2.0f, Enemies::slime_speed = 50.0f, Enemies::slimeBBOffset = 22.0f;
float Enemies::bat_counter = 5.0f, Enemies::bat_speed = 100.0f, Enemies::batBBOffset = 9.0f;
float Enemies::squirrel_counter = 4.0f, Enemies::squirrel_speed = 110.0f, Enemies::squirrelBBOffset = 20.0f, Enemies::squirrel_offset_x = 10.0f,
Enemies::squirrel_jumpspeed = 100.0f;

int Enemies::jump_counter = 5;

static AEGfxTexture* enemyTex[static_cast<int>(EnemyType::Max)]{ nullptr };

Enemies::Enemies(AEGfxTexture* filepath, AEGfxVertexList* mesh, const f32 width, const f32 height) : sprite(filepath, mesh, width, height), collider(),
spawnPos{ 0, 0 }, active{ true }, type{ EnemyType::Slime }, isGravity{ false }, counter{ 0 }, jumpcounter{ 5 }, squirrelJump { false },
velocity{ 0 }, jumpvelocity{ 0 }, killed{ false }, alpha{ 255.0f }, alphaTimer{ 1.0f }, stepGravityMultiplier{ GAMEPLAY_CONST::BASE_GRAVITY_MULTIPLIER }{
	EnemyCount++;
	collider.sprite.color.Set(Color{ 0, 0, 0, 100.0f });
}

void Enemies::Update_Position(void)
{
	f32 maxX{ static_cast<f32>(AEGetWindowWidth()) };

	if (active && !killed) {

	collider.sprite.pos = sprite.pos;
	collider.top.pos = AEVec2Set(sprite.pos.x, sprite.pos.y - sprite.height / 2.0f);
	collider.bottom.pos = AEVec2Set(sprite.pos.x, sprite.pos.y + sprite.height / 2.0f);
	collider.right.pos = AEVec2Set(sprite.pos.x + abs(sprite.width) / 2.0f - collider.right.width / 2.0f, sprite.pos.y);
	collider.left.pos = AEVec2Set(sprite.pos.x - abs(sprite.width) / 2.0f + collider.left.width / 2.0f, sprite.pos.y);

		switch (type) {
		case EnemyType::Slime:
			Slime_Movement(maxX);
			return;
		case EnemyType::Bat:
			Bat_Movement(maxX);
			break;
			return;
		case EnemyType::Squirrel:
			Squirrel_Movement(maxX);
			return;
		}
	}
}


void Enemies::ApplyGravity(void) {

	const float GravityStep{ 10.0f };
	if (isGravity && !killed)
	{
		stepGravityMultiplier += g_dt * GravityStep;
		sprite.pos.y += (baseGravityStrength * (g_dt * stepGravityMultiplier));
	}
}

void Enemies::Bat_Movement(f32 maxX)
{
	// Sine-Wave
	sprite.pos.x += velocity * g_dt;
	sprite.pos.y = spawnPos.y + 10.0f * sinf(static_cast<f32>(sprite.pos.x) * 2.0f * PI / 180.0f); // y = amplitude * sin(x * period * pi / 180)

	counter -= g_dt;

	if (counter < 0.0f || sprite.pos.x + sprite.width / 2.0f < 0 || sprite.pos.x + sprite.width / 2 >= maxX)
	{
		velocity *= -1;
		sprite.ReflectAboutYAxis();
		counter = Enemies::bat_counter;
	}
}

void Enemies::Squirrel_Movement(f32 maxX)
{
	sprite.pos.x += velocity * g_dt;
	counter -= g_dt;

	if (squirrelJump)
	{
		sprite.pos.y -= static_cast<f32>(jumpvelocity) * g_dt;
	}

	const float halfWidth{ fabsf(sprite.width / 2.0f) };
	if (!isGravity && counter < 0.0f || sprite.pos.x - sprite.width / 2.0f < 0 || sprite.pos.x + halfWidth >= maxX)
	{
		if (sprite.pos.x + halfWidth >= maxX)
			sprite.pos.x = maxX - halfWidth;

		sprite.ReflectAboutYAxis();
		velocity *= -1.0f;
		counter = Enemies::squirrel_counter;
	}

	if (velocity < 0)
		collider.bottom.pos.x = sprite.pos.x - squirrel_offset_x;
	else
		collider.bottom.pos.x = sprite.pos.x + squirrel_offset_x;
}

void Enemies::Slime_Movement(f32 maxX)
{
	if (!isGravity)
	{
		sprite.pos.x -= velocity * g_dt;
		counter -= g_dt;
	}
	const float halfWidth {fabsf(sprite.width / 2.0f)};
	if (counter < 0.0f || sprite.pos.x - sprite.width / 2.0f < 0 || sprite.pos.x + halfWidth >= maxX)
	{
		if(sprite.pos.x + halfWidth >= maxX)
			sprite.pos.x = maxX - halfWidth;

		sprite.ReflectAboutYAxis();
		velocity *= -1.0f;
		counter = Enemies::slime_counter;
	}
}
void Enemies::DecrementAlpha(void)
{
	static const float Timer{ alphaTimer };
	static const float Alpha{ 255.0f };

	if (alphaTimer <= 0)
		active = false;
	if (killed) {
		alphaTimer -= g_dt;
		alpha = (alphaTimer / Timer) * Alpha;
	}
}

void Enemies::Update()
{
	Update_Position();
	if(type != EnemyType::Bat)
		ApplyGravity();
	DecrementAlpha();
}

void Enemies::Draw()
{
	if (active)
	{
		if (type != EnemyType::Bat)
			sprite.Draw_Texture(alpha);
		else
			sprite.Draw_Texture(20, bat_anim_offset_x, Mesh::BatAnim, alpha);
		if (GAMEPLAY_MISC::DEBUG_MODE) {
			collider.Draw();
		}
	}
}

void Enemies::AddNew(std::vector <Enemies>& enemy, EnemyType type, const AEVec2 pos, const f32 width, const f32 height)
{
	float bbHeight{ height }, counter{ 0 }, vel{ 0 }, jumpvel{ 0 };
	int jumpcounter{ 0 };
	const float BatOffset{ 20.0f }, squirrelOffset{ 43.0f };
	AEGfxVertexList* currMesh = nullptr;
	switch (type) {
	case EnemyType::Bat:
		bbHeight = BatOffset;
		counter = Enemies::bat_counter;
		vel = Enemies::bat_speed;
		currMesh = Mesh::BatAnim;
		break;
	case EnemyType::Squirrel:
		bbHeight = squirrelOffset;
		counter = Enemies::squirrel_counter;
		vel = Enemies::squirrel_speed;
		jumpcounter = Enemies::jump_counter;
		jumpvel = Enemies::squirrel_jumpspeed;
		currMesh = Mesh::Rect;
		break;
	case EnemyType::Slime:
		counter = Enemies::slime_counter;
		vel = Enemies::slime_speed;
		currMesh = Mesh::Rect;
		break;
	default:
		std::cout << "Invalid enemy type!\n";
		break;
	}
	enemy.push_back(Enemies(enemyTex[static_cast<int>(type)], currMesh, width, height));
	Enemies& Enemy = enemy.back();
	Enemy.sprite.pos = pos;
	Enemy.type = type;
	Enemy.spawnPos = pos;
	Enemy.counter = counter;
	Enemy.velocity = vel;
	Enemy.jumpcounter = jumpcounter;
	Enemy.jumpvelocity = jumpvel;

	Enemy.collider.SetWidthHeight(Enemy.collider.sprite, width, bbHeight);
	Enemy.collider.SetWidthHeight(Enemy.collider.top, Enemy.sprite.width, 5.0f);
	Enemy.collider.SetWidthHeight(Enemy.collider.left, 20.0f, Enemy.sprite.height * 0.7f);
	Enemy.collider.SetWidthHeight(Enemy.collider.right, 20.0f, Enemy.sprite.height * 0.7f);
	Enemy.collider.SetWidthHeight(Enemy.collider.bottom, Enemy.sprite.width, 5.0f);

	// Temp fixes
	if (type == EnemyType::Bat)
	{
		Enemy.collider.SetWidthHeight(Enemy.collider.left, 20.0f, 30.0f);
		Enemy.collider.SetWidthHeight(Enemy.collider.right, 20.0f, 30.0f);
	}
	if (type == EnemyType::Squirrel) {
		Enemy.collider.SetWidthHeight(Enemy.collider.left, 20.0f, 20.0f);
		Enemy.collider.SetWidthHeight(Enemy.collider.right, 20.0f, 20.0f);
		Enemy.collider.SetWidthHeight(Enemy.collider.bottom, Enemy.sprite.width * 0.5f, 5.0f);
	}
}

void Enemies::Reset(std::vector <Enemies>& enemy)
{
	for (size_t i = 0; i < enemy.size(); i++)
	{
		enemy[i].sprite.pos = enemy[i].spawnPos;
		enemy[i].active = true;
		enemy[i].killed = false;
		enemy[i].sprite.rotation = 0;
		enemy[i].alpha = 255.0f;
		enemy[i].alphaTimer = 1.0f;
	}
}
void Enemies::Unload(void)
{
	for (size_t i = 0; i < static_cast<int>(EnemyType::Max); i++)
	{
		AEGfxTextureUnload(enemyTex[i]);
	}
}

void Enemies::LoadTex(void) {
	for (EnemyType i = EnemyType::Slime; i < EnemyType::Max; ++i) {
		const char* pTex = nullptr;
		switch (i) {
		case EnemyType::Slime:
			pTex = FP::WaterSlimeSprite;
			break;
		case EnemyType::Bat:
			pTex = FP::BatSpriteSheet;
			break;
		case EnemyType::Squirrel:
			pTex = FP::SquirrelSprite;
			break;
		default:
			return;
		}
		enemyTex[static_cast<int>(i)] = AEGfxTextureLoad(pTex);
		AE_ASSERT_MESG(pTex, "Failed to create texture!");
	}
}

EnemyType& operator++(EnemyType& rhs) {
	rhs = static_cast<EnemyType>((static_cast<int>(rhs) + 1));
	return rhs;
}

void Enemies::KillEnemy(bool status) {
	killed = status;
	const int particleCount{ 50 };
	if (killed) {
		for (int i = 0; i < particleCount; ++i) {
			Particles::Create(sprite.pos, Utils::GetRandomVecVel(), Color::CreateRandomColor(), 1, 75.0f, Utils::RandomRangeFloat(100.0f, 250.0f), sprite.width / 3.0f, 3.0f, enemyTex[static_cast<int>(type)]);
		}
	}
}