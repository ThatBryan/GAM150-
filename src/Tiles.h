#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include <vector>
#include "Image.h"
#include "Player.h"

enum TileType {NIL, COLLAPSIBLE, GOAL, GREYTILE};

class Tiles
{
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
};

namespace Tile
{
	// Add whole new row of tile.
	std::vector <Tiles> AddTileRow(std::vector < Tiles> tile, const s8* filepath, const s32 type, const size_t num, const f32 width, const f32 height, const AEVec2 pos);

	// Collapse the tile on its left and right if it is collapsible.
	void CollapseNext(std::vector <Tiles>& tiles);

	// Handles the collision between the enemy and tiles, and enemy with player.
	void CollisionManager(std::vector <Tiles>& tiles, std::vector <Player>& player, std::vector <Enemies>& enemy);
	
	// Resets the level.
	void Reset(std::vector <Tiles>& tiles);

	// Draws to screen the tiles.
	void Draw(std::vector <Tiles> tile);

	// Frees the mesh and texture used for the tiles.
	void Free(std::vector <Tiles>& tiles);
}