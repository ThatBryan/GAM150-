#pragma once
#include "AEEngine.h"
#include <vector>
#include "Image.h"
#include "Constants.h"
#include "Player.h"
#include "Enemy.h"

enum TileType {NIL, COLLAPSIBLE, GOAL, SAFE, SPECIAL};

class Tiles
{
	private:
		s32 ID, type;
		f64 collapseDelay;
		bool active, collapsing;
		Graphics::Rect ColliderAABB{ 80.0f, 50.0f };

	public:
		Tiles(const s8* filepath, const f32 width, const f32 height);
		Image image;
		AEVec2 spawnPos;
		void Collapse(void);
		void DecreaseLifespan(void);
		void CheckPlayerGoal(std::vector <Player>& player);
		void CheckEnemyStatus(std::vector <Enemies> enemy);
		static void Free(std::vector <Tiles>& tiles);

		static void CheckTilesPos(std::vector <std::vector<Tiles>*>& TileManager);
		static void CheckPlayerCollision(std::vector <std::vector<Tiles>*>& TileManager, std::vector <Player>& player);

		// Add whole new row of tile.
		static void AddTileRow(std::vector < Tiles>& tile, const s8* filepath, const s32 type, const size_t num, const f32 width, const f32 height, const AEVec2 pos);
		// Collapse the tile on its left and right if it is collapsible.

		static void CollapseNext(std::vector <Tiles>& tiles);
		// Handles the collision between the enemy and tiles, and enemy with player.

		static void CollisionManager(std::vector <Tiles>& tiles, std::vector <Player>& player, std::vector <Enemies>& enemy);

		// Resets the level.
		static void Reset(std::vector <Tiles>& tiles);

		// Draws to screen the tiles.
		static void Draw(std::vector <Tiles>& tile);
};
