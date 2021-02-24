#pragma once
#include "Image.h"
#include "Utilities.h"
#include <vector>
#include "AEEngine.h"
#include "Graphics.h"
#include "Constants.h"

enum EnemyType {Slime = 0, Bat = 1, Squirrel, ENEMY_MAX };

static AEGfxTexture* enemyTex[ENEMY_MAX]{ nullptr };


class Enemies : public GameObject
{
	unsigned short type;
	AEVec2 spawnPos;
	Graphics::Rect colliderAABB {enemy_width, 10.0f };
	short ID;

public:
	Enemies(AEGfxTexture* filepath, const f32 width, const f32 height);
	Image sprite;
	bool active;
	void Update_Position(void);
	void Update(void);

	// Add new enemy into the vector.
	static void LoadTex(void);
	static void AddNew(std::vector <Enemies>& enemy, const short type, const s8* filepath, const AEVec2 pos, const f32 width, const f32 height);
	static void Reset(std::vector <Enemies>& enemy);
	void Draw();
	static void Unload(void);
};
