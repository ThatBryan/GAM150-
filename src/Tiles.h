/******************************************************************************/
/*!
\file				Tiles.h
\primary author: 	Bryan Koh Yan Wei
\secondary author:	Seet Min Yi
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Type definition for Tile objects.

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#pragma once
#include "AEEngine.h"
#include <vector>
#include "Image.h"
#include "Constants.h"
#include "Collider.h"

enum class TileType { Grass = 0, Goal, Safe, Special, Dialogue, Max };
TileType& operator++(TileType& rhs);

// Foward declaration
class Player;
class Enemies;

class Tiles
{
public:
	// Reference to a vector, containing a vector of Tiles*
	using TileMgr = std::vector<std::vector<Tiles>*>&;

private:
	Collider collider;
	TileType type;
	f64 collapseDelay;
	bool active, isCollapsing;
	static bool isTutorialLevel;

	void DecreaseLifespan(void);
	void Collapse(const Player& player);
	void CheckPos(void);
	void CheckPlayerGoal(Player& player);
	void CheckEnemyDeath(std::vector <Enemies>& enemy);
	void Update(Player& player);
	void TileShake(void);
	static void LoadTutorialTexture(void);
	static void FreeTutorialTexture(void);

public:
	Tiles(AEGfxTexture*, const f32 width, const f32 height);
	Image image;
	AEVec2 spawnPos;
	short ID;
	void Render(void);

	inline bool GetActive() const { return active; }

	// Static class Functions
	static void Unload(void);
	static void LoadTex(void);

	// Resets the level.
	static void Reset(std::vector <Tiles>& tiles);

	static void CollapsingManager(TileMgr TileManager);
	static void CheckEnemyGravity(const TileMgr TileManager, Enemies& enemy);
	static void CheckPlayerGravity(const TileMgr TileManager, Player& ThePlayer);
	static void CheckPlayerCollision(const TileMgr TileManager, Player& ThePlayer);
	static void CheckEnemyCollision(const TileMgr TileManager, Enemies& enemy);

	// Add single tile to a given vector.
	static void AddTile(std::vector<Tiles>& tile, TileType type, const f32 width, const f32 height, AEVec2 pos);

	// Handles the collision between the enemy and tiles, and enemy with player.
	static void UpdateManager(std::vector <Tiles>& tiles, Player& player, std::vector <Enemies>& enemy);

	//// Add whole new row of tile. Only for main menu.
	static void AddTileRow(std::vector < Tiles>& tile, TileType type, const int count, const f32 width, const f32 height, const AEVec2 pos);

	static void CreateDialogue(const short tileID, const AEVec2 tilePos);
};