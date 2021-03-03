#pragma once
#include "Image.h"
#include "Utilities.h"
#include <vector>
#include "AEEngine.h"
#include "Graphics.h"
#include "Constants.h"
enum class EnemyType {Slime = 0, Bat, Squirrel, Max };

static AEGfxTexture* enemyTex[static_cast<int>(EnemyType::Max)]{ nullptr };

class Player;
class Enemies : public GameObject
{
	unsigned short type;
	AEVec2 spawnPos;
	Graphics::Rect headBB {enemy_width, 5.0f};
	Graphics::Rect enemyBB {enemy_width, enemy_height};
	short ID;
	friend class Player;

public:
	Enemies(AEGfxTexture* filepath, const f32 width, const f32 height);
	Image sprite;
	bool active;
	void Update_Position(void);
	void Update(void);
	void Draw();

	// Add new enemy into the vector.
	static void LoadTex(void);
	static void AddNew(std::vector <Enemies>& enemy, const short type, const AEVec2 pos, const f32 width, const f32 height);
	static void Reset(std::vector <Enemies>& enemy);
	static void Unload(void);
};
