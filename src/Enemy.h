#pragma once
#include <vector>
#include "AEEngine.h"
#include "Graphics.h"
#include "Constants.h"
#include "Image.h"

enum class EnemyType {Slime = 0, Bat, Squirrel, Max};
EnemyType& operator++(EnemyType& rhs);

// Foward declarations
class Player;
class Tiles;

class Enemies
{
private:
	friend class Player; // Enemy can modify player
	EnemyType type;
	AEVec2 spawnPos;
	Graphics::Rect headBB {enemy_width, 5.0f};
	Graphics::Rect enemyBB {enemy_width, 10.0f};
	bool isGravity, killed;
	float counter, velocity, jumpcounter, jumpvelocity, alpha, alphaTimer;
	unsigned short ID;

	static float slime_counter, slime_speed, slimeBBOffset;
	static float bat_speed, bat_counter, batBBOffset;
	static float squirrel_speed, squirrel_counter, squirrel_jumpspeed, jump_counter, squirrelBBOffset;
	static float gravityStrength;

	// Private functions
	void Update_Position(void);
	void ApplyGravity(void);
	void Bat_Movement(f32 maxX);
	void Squirrel_Movement(f32 maxX);
	void Slime_Movement(f32 maxX);
	void DecrementAlpha(void);

public:
	Enemies(AEGfxTexture* filepath, const f32 width, const f32 height);
	Image sprite;
	bool active;
	void Update(void);
	void Draw();
	inline EnemyType GetType() { return type; }
	inline bool getKilled() { return killed; }
	void setKilled(bool status = true);

	void GravityCheck(std::vector <std::vector<Tiles>*>& TileManager);

	// Add new enemy into the vector.
	static void AddNew(std::vector <Enemies>& enemy, EnemyType type, const AEVec2 pos, const f32 width, const f32 height);
	static void Reset(std::vector <Enemies>& enemy);
	static void LoadTex(void);
	static void Unload(void);
};
