#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include <vector>
#include "Image.h"
#include "Player.h"
#include "Constants.h"

enum TileType {NIL, COLLAPSIBLE, GOAL, GREYTILE};

class Tiles
{
	private:

	public:
		Tiles(const s8* filepath, const f32 width, const f32 height);
		s32 ID, type;
		f64 collapseDelay;
		bool active, collapsing;
		AEVec2 startingPos;
		Image image;
		void Collapse(void);
		void DecreaseLifespan(void);
		void CheckPlayerGoal(std::vector <Player>& player);
		void CheckEnemyStatus(std::vector <Enemies> enemy);
		static void Free(std::vector <Tiles>& tiles);

		// Add whole new row of tile.
		static std::vector <Tiles> AddTileRow(std::vector < Tiles> tile, const s8* filepath, const s32 type, const size_t num, const f32 width, const f32 height, const AEVec2 pos);
		// Collapse the tile on its left and right if it is collapsible.
		static void CollapseNext(std::vector <Tiles>& tiles);
		// Handles the collision between the enemy and tiles, and enemy with player.
		static void CollisionManager(std::vector <Tiles>& tiles, std::vector <Player>& player, std::vector <Enemies>& enemy);
		// Resets the level.
		static void Reset(std::vector <Tiles>& tiles);
		// Draws to screen the tiles.
		static void Draw(std::vector <Tiles> tile);
};
