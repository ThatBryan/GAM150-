#pragma once
#include "AEEngine.h"
#include <vector>
#include "Image.h"
#include "Constants.h"
#include "Player.h"
#include "Enemy.h"

enum TileType {COLLAPSIBLE, GOAL, SAFE, SPECIAL, TILE_MAX};
static AEGfxTexture* tileTex[TILE_MAX]{ nullptr };

class Tiles
{
	private:
		short ID, type;
		f64 collapseDelay;
		bool active, collapsing;
		Graphics::Rect ColliderAABB;

	public:
		Tiles(AEGfxTexture*, const f32 width, const f32 height);
		Image image;
		AEVec2 spawnPos;
		void Collapse(void);
		void DecreaseLifespan(void);
		void CheckPlayerGoal(std::vector <Player>& player);
		void CheckEnemyStatus(std::vector <Enemies> enemy);
		void Update(void);
		void CheckPos(void);
		static void Unload(void);
		static void LoadTex(void);

		static void CheckTilesPos(std::vector <std::vector<Tiles>*>& TileManager);
		static void CheckPlayerCollision(std::vector <std::vector<Tiles>*>& TileManager, std::vector <Player>& player);

		// Add whole new row of tile.
		static void AddTileRow(std::vector < Tiles>& tile, const s32 type, const size_t num, const f32 width, const f32 height, const AEVec2 pos);
		// Collapse the tile on its left and right if it is collapsible.

		static void CollapseNext(std::vector <Tiles>& tiles);
		// Handles the collision between the enemy and tiles, and enemy with player.

		static void UpdateManager(std::vector <Tiles>& tiles, std::vector <Player>& player, std::vector <Enemies>& enemy);

		// Resets the level.
		static void Reset(std::vector <Tiles>& tiles);

		// Draws to screen the tiles.
		static void Draw(std::vector <Tiles>& tile);
};
