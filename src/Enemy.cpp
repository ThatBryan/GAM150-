#include "Enemy.h"

float numberOfTicks = 0.0f;

Enemies::Enemies(AEGfxTexture* filepath, const f32 width, const f32 height) : sprite(filepath, width, height), 
spawnPos{0, 0}, active{true}, type{0}
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

	static float slime_counter = -2.0f;
	static float slime_speed = 50.0f * g_dt;
	static float bat_speed = 1.0f;
	static float bat_counter = 0.0f;
	
	if(DebugMode)
		sprite.direction -= 1.0f * ID;
	if (type == Enemy_Slime)
	{
		sprite.pos.x += slime_speed;
		headBB.pos = sprite.pos;
		enemyBB.pos = sprite.pos;
		headBB.pos.y -= 20.0f;

		slime_counter -= g_dt;
		if (slime_counter < -2.0f)
		{
			slime_speed *= -1;
			slime_counter = 1.0f;
		}
	}
	
	if (type == Enemy_Bat)
	{
		// Sine-Wave
		sprite.pos.x += bat_speed;
		sprite.pos.y = 20 * sin(static_cast<f32>(sprite.pos.x) * 2.0f * 3.14159 / 180.0f); // y = amplitude * sin(x * period * pi / 180)

		bat_counter += 1.0f;
		if (bat_counter > 120)
		{
			bat_speed *= -1;
			bat_counter = 0.0f;
		}
	}

}

void Enemies::Update()
{
	if (!paused) {
		Update_Position();
	}
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

void Enemies::AddNew(std::vector <Enemies>& enemy, const short type, const AEVec2 pos, const f32 width, const f32 height)
{
	enemy.push_back(Enemies(enemyTex[type], width, height));
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
		enemy[i].sprite.direction = 0;
	}
}
void Enemies::Unload(void)
{
	for (size_t i = 0; i < Enemy_Max; i++)
	{
		AEGfxTextureUnload(enemyTex[i]);
	}
}

void Enemies::LoadTex(void) {
	for (int i = 0; i < Enemy_Max; i++) {
		const char* pTex = nullptr;
		switch (i) {
		case Enemy_Slime:
			pTex = WaterSlimeSprite;
			break;
		case Enemy_Bat:
			pTex = FlyingEnemySprite;
			break;
		case Enemy_Squirrel:
			pTex = SquirrelSprite;
			break;
		default:
			return;
		}
		enemyTex[i] = AEGfxTextureLoad(pTex);
		AE_ASSERT_MESG(pTex, "Failed to create texture!");
	}
}