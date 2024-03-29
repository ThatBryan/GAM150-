/******************************************************************************/
/*!
\file				Enemy.h
\primary author: 	Bryan Koh Yan Wei (60%)
\Secondary author:	Seet Min Yi	(40%)
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Header file of an Enemy class implementation.

All content � 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#pragma once
#include <vector>
#include "AEEngine.h"
#include "Graphics.h"
#include "Constants.h"
#include "Image.h"
#include "Tiles.h"

enum class EnemyType {Slime = 0, Bat, Squirrel, Max};
EnemyType& operator++(EnemyType& rhs);

// Foward declarations
class Player;

class Enemies
{
private:
	friend class Player; // Enemy can modify player
	EnemyType type;
	Collider collider;
	AEVec2 spawnPos;

	bool isGravity, killed, squirrelJump;
	float counter, velocity, jumpvelocity, alpha, alphaTimer;
	float stepGravityMultiplier;
	int jumpcounter;

	static float slime_counter, slime_speed, slimeBBOffset;
	static float bat_speed, bat_counter, batBBOffset;
	static float squirrel_speed, squirrel_counter, squirrel_jumpspeed, squirrelBBOffset, squirrel_offset_x;
	static int jump_counter;
	static float baseGravityStrength;

	void Update_Position(void);
	void Set_Collders();
	void ApplyGravity(void);
	void Bat_Movement(const f32 maxX);
	void Squirrel_Movement(const f32 maxX);
	void Slime_Movement(const f32 maxX);
	void DecreaseAlpha(void);
	void PlayDeathSFX();
	void CheckOutOfBound();

public:
	Enemies(AEGfxTexture* filepath, AEGfxVertexList* mesh, const f32 width, const f32 height);
	Image sprite;
	bool active;
	void Update(void);
	void Draw();
	void KillEnemy(bool status = true);
	
	inline EnemyType GetType() const { return type; }
	inline bool GetKilledStatus() const { return killed; }
	inline void SetGravity(bool X) { isGravity = X; }

	// Adds new enemy into the vector.
	static void AddNew(std::vector <Enemies>& enemy, EnemyType type, const AEVec2 pos, const f32 width, const f32 height);
	static void Reset(std::vector <Enemies>& enemy);
	static void LoadTex(void);
	static void Unload(void);

	friend void Tiles::CheckEnemyGravity(const TileMgr TileManager, Enemies& enemy);
	friend void Tiles::CheckEnemyCollision(const TileMgr TileManager, Enemies& enemy);
};