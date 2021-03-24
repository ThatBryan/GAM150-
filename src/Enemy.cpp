#include "Enemy.h"
#include "Tiles.h"
#include "Utilities.h"
#include "Particles.h"


bool jump = FALSE;

float Enemies::gravityStrength = 100.0f;

float Enemies::slime_counter = 2.0f, Enemies::slime_speed = 50.0f, Enemies::slimeBBOffset = 22.0f;
float Enemies::bat_counter = 5.0f, Enemies::bat_speed = 100.0f, Enemies::batBBOffset = 9.0f;
float Enemies::squirrel_counter = 4.0f, Enemies::squirrel_speed = 110.0f, Enemies::squirrelBBOffset = 20.0f,
Enemies::jump_counter = 0.5f, Enemies::squirrel_jumpspeed = 25.0f;

static AEGfxTexture* enemyTex[static_cast<int>(EnemyType::Max)]{ nullptr };

Enemies::Enemies(AEGfxTexture* filepath, const f32 width, const f32 height) : sprite(filepath, width, height), 
spawnPos{ 0, 0 }, active{ true }, type{ EnemyType::Slime }, isGravity{ false }, counter{ 0 }, jumpcounter{ 0 },
velocity{ 0 }, jumpvelocity{ 0 }, killed{ false }, alpha{ 255.0f }, alphaTimer{ 1.0f }{
	ID = EnemyCount;
	EnemyCount++;
	headBB.color.Set(Color{ 255.0f, 255.0, 255.0f, 255.0f });
	enemyBB.color.Set(Color{ 0, 0, 0, 100.0f });
}

void Enemies::Update_Position(void)
{
	f32 maxX{ static_cast<f32>(AEGetWindowWidth()) };

	if (active && !killed) {
		switch (type) {
		case EnemyType::Slime:
			Slime_Movement(maxX);
			return;
		case EnemyType::Bat:
			Bat_Movement(maxX);
			return;
		case EnemyType::Squirrel:
			Squirrel_Movement(maxX);
			return;
		}
	}
}


void Enemies::ApplyGravity(void) {
	if (isGravity && !killed)
	{
		sprite.pos.y += gravityStrength * g_dt;
	}
}

void Enemies::Bat_Movement(f32 maxX)
{
	// Sine-Wave
	sprite.pos.y = spawnPos.y + 10.0f * sinf(static_cast<f32>(sprite.pos.x) * 2.0f * PI / 180.0f); // y = amplitude * sin(x * period * pi / 180)
	counter -= g_dt;

	if (counter < 0.0f || sprite.pos.x + sprite.width / 2.0f < 0 || sprite.pos.x + sprite.width / 2 >= maxX)
	{
		velocity *= -1;
		sprite.ReflectAboutYAxis();
		counter = Enemies::bat_counter;
	}
	sprite.pos.x += velocity * g_dt;
	headBB.pos = sprite.pos;
	enemyBB.pos = sprite.pos;
	headBB.pos.y -= batBBOffset;
}

void Enemies::Squirrel_Movement(f32 maxX)
{
	sprite.pos.x += velocity * g_dt;
	sprite.pos.y += static_cast<f32>(jumpvelocity) * g_dt;
	counter -= g_dt;
	jumpcounter -= g_dt;

	if (counter < 0.0f || sprite.pos.x + sprite.width / 2.0f < 0 || sprite.pos.x + sprite.width / 2 >= maxX)
	{
		velocity *= -1;
		sprite.ReflectAboutYAxis();
		counter = Enemies::squirrel_counter;
	}
	if (jumpcounter < 0.0f)
	{
		jumpvelocity *= -1.0f;
		jumpcounter = Enemies::jump_counter;
	}

	headBB.pos = sprite.pos;
	enemyBB.pos = sprite.pos;
	headBB.pos.y -= squirrelBBOffset;
}

void Enemies::Slime_Movement(f32 maxX)
{
	sprite.pos.x -= velocity * g_dt;
	counter -= g_dt;
	if (counter < 0.0f || sprite.pos.x - sprite.width / 2.0f < 0 || sprite.pos.x + sprite.width / 2 >= maxX)
	{
		sprite.ReflectAboutYAxis();
		velocity *= -1.0f;
		counter = Enemies::slime_counter;
	}
	headBB.pos = sprite.pos;
	enemyBB.pos = sprite.pos;
	headBB.pos.y -= slimeBBOffset;
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
	ApplyGravity();
	DecrementAlpha();
}

void Enemies::Draw()
{
	if (active)
	{
		sprite.Draw_Texture(alpha);
		if (DebugMode) {
			headBB.Draw();
			enemyBB.Draw();
		}
	}
}

void Enemies::AddNew(std::vector <Enemies>& enemy, EnemyType type, const AEVec2 pos, const f32 width, const f32 height)
{
	float bbHeight{ height }, counter{ 0 }, vel{ 0 }, jumpcounter{ 0 }, jumpvel{ 0 };
	const float BatOffset{ 20.0f }, squirrelOffset{ 43.0f };
	switch (type) {
	case EnemyType::Bat:
		bbHeight = BatOffset;
		counter = Enemies::bat_counter;
		vel = Enemies::bat_speed;
		break;
	case EnemyType::Squirrel:
		bbHeight = squirrelOffset;
		counter = Enemies::squirrel_counter;
		vel = Enemies::squirrel_speed;
		jumpcounter = Enemies::jump_counter;
		jumpvel = Enemies::squirrel_jumpspeed;
		break;
	case EnemyType::Slime:
		counter = Enemies::slime_counter;
		vel = Enemies::slime_speed;
		break;
	default:
		break;
	}
	enemy.push_back(Enemies(enemyTex[static_cast<int>(type)], width, height));
	Enemies& Enemy = enemy.back();
	Enemy.sprite.pos = pos;
	Enemy.type = type;
	Enemy.spawnPos = pos;
	Enemy.enemyBB.height = bbHeight;
	Enemy.counter = counter;
	Enemy.velocity = vel;
	Enemy.jumpcounter = jumpcounter;
	Enemy.jumpvelocity = jumpvel;
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
			pTex = FP::FlyingEnemySprite;
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
			Particles::Create(sprite.pos, Utils::GetRandomVecVel(), Color::CreateRandomColor(), 1, 75.0f, Utils::RandomRangeFloat(100.0f, 250.0f), 25.0f, 3.0f, enemyTex[static_cast<int>(type)]);
		}
	}
}