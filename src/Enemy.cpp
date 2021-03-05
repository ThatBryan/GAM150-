#include "Enemy.h"
#include "Tiles.h"
#include "Utilities.h"

float numberOfTicks = 0.0f;
float Enemies::gravityStrength = 100.0f;
float Enemies::slime_counter = 2.0f, Enemies::slime_speed = 50.0f, Enemies::slimeBBOffset = 22.0f;;
float Enemies::bat_speed = 100.0f, Enemies::bat_counter = 5.0f;


Enemies::Enemies(AEGfxTexture* filepath, const f32 width, const f32 height) : sprite(filepath, width, height), 
spawnPos{0, 0}, active{true}, type{EnemyType::Slime}, isGravity{false}
{
	ID = EnemyCount;
	EnemyCount++;
	headBB.color.SetColor(0, 0, 255.0f, 255.0f);
	enemyBB.color.SetColor(0, 0, 0, 255.0f);
}

void Enemies::Update_Position(void)
{
	static f32 maxY = static_cast<f32>(AEGetWindowHeight());
	static f32 maxX = static_cast<f32>(AEGetWindowWidth());

	//if (DebugMode)
	//	sprite.rotation -= 1.0f * ID;
	if (type == EnemyType::Slime)
	{
		sprite.pos.x += slime_speed * g_dt;
		headBB.pos = sprite.pos;
		enemyBB.pos = sprite.pos;
		headBB.pos.y -= slimeBBOffset;

		slime_counter -= g_dt;
		if (slime_counter < -2.0f || sprite.pos.x < 0 || sprite.pos.x + sprite.width / 2 >= maxX)
		{
			slime_speed *= -1.0f;
			slime_counter = 1.0f;
		}
	}

	if (type == EnemyType::Bat)
	{
		// Sine-Wave
		static AEVec2 startpos = sprite.pos;
		sprite.pos.x += bat_speed*g_dt;
		sprite.pos.y = startpos.y + 20 * sin(static_cast<f32>(sprite.pos.x) * 2.0f * PI / 180.0f); // y = amplitude * sin(x * period * pi / 180)

		bat_counter -= g_dt;

		if (bat_counter < -5.0f || sprite.pos.x < 0 ||  sprite.pos.x + sprite.width / 2 >= maxX)
		{
			bat_speed *= -1;
			bat_counter = 1.0f;
		}
	}
}

void Enemies::GravityCheck(std::vector <std::vector<Tiles>*>& TileManager) {
	for (size_t i = 0; i < TileManager.size(); i++)
	{
		for (size_t j = 0; j < TileManager[i]->size(); j++)
		{
			if (TileManager[i]->at(j).GetActive() == false)
				continue;
			if (Utils::ColliderAABB(TileManager[i]->at(j).image.pos, TileManager[i]->at(j).image.width, TileManager[i]->at(j).image.height,
				enemyBB.pos, enemyBB.width, enemyBB.height))
			{
				isGravity = false;
				return;
			}
		}
	}
	isGravity = true;
}

void Enemies::ApplyGravity(void) {
	if (isGravity)
		sprite.pos.y += gravityStrength * g_dt;
}

void Enemies::Update()
{
	Update_Position();
	ApplyGravity();
}

void Enemies::Draw()
{
	if (active)
	{
		sprite.Draw_Texture(255.0f);
		if (DebugMode) {
			headBB.Draw();
			enemyBB.Draw();
		}
	}
}

void Enemies::AddNew(std::vector <Enemies>& enemy, EnemyType type, const AEVec2 pos, const f32 width, const f32 height)
{
	enemy.push_back(Enemies(enemyTex[static_cast<int>(type)], width, height));
	enemy[enemy.size() - 1].sprite.pos = pos;
	enemy[enemy.size() - 1].type = type;
	enemy[enemy.size() - 1].spawnPos = pos;
}

void Enemies::Reset(std::vector <Enemies>& enemy)
{
	for (size_t i = 0; i < enemy.size(); i++)
	{
		enemy[i].sprite.pos = enemy[i].spawnPos;
		enemy[i].active = true;
		enemy[i].sprite.rotation = 0;
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
			pTex = WaterSlimeSprite;
			break;
		case EnemyType::Bat:
			pTex = FlyingEnemySprite;
			break;
		case EnemyType::Squirrel:
			pTex = SquirrelSprite;
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