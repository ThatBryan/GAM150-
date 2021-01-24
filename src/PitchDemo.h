#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include "Tiles.h"
#include "Player.h"


namespace Demo
{
	//Level main entry points
	void Init(void);
	void Update(void);
	void Exit(void);

	//Frees the vector of tiles
	void Free(std::vector <Tiles> tiles);
	
	// Draws the vector of tiles.
	void Draw(std::vector <Tiles> tiles);

	// Collection of drawing related code.
	void DrawingManager(void);

	// Restarts the level (kinda)
	void Restart(void);
	
	// Collapse the tile on its left and right if it exist.
	void CollapseNext(std::vector <Tiles>& tiles);

	// Collection of collision related code.
	void CollisionManager(void);

	// Check player collision with tiles.
	void CheckCollisionTilesPlayer(std::vector <Tiles>& tiles, std::vector <Player> player);

	// Collection of tile collapsing related code.
	void CollapsingManager(void);
	
	// Add new enemy into the vector.
	void AddNewEnemy(const s8* filepath, const AEVec2 pos, const f32 width, const f32 height);

	// Add whole new row of tile.
	std::vector <Tiles> AddTileRow(std::vector < Tiles> tile, const s8* filepath, const s32 type, const size_t num, const f32 width, const f32 height, const AEVec2 pos);
}