#pragma once
#include "AEEngine.h"
#include <vector>
#include "Image.h"
#include "Constants.h"
#include "Player.h"
#include "Enemy.h"

enum class TileType{ Grass = 0, Goal, Safe, Special, Max };
TileType& operator++(TileType& rhs);

static AEGfxTexture* tileTex[static_cast<int>(TileType::Max)]{ nullptr };
class Tiles
{
	private:
		short ID;
		TileType type;
		f64 collapseDelay;
		bool active, collapsing;
		Graphics::Rect ColliderAABB;

		// Abstracting away functions so the user cannot call it
		void DecreaseLifespan(void);
		void Collapse(void);
		void CheckPos(void);
		void CheckPlayerGoal(std::vector <Player>& player);
		void CheckEnemyStatus(std::vector <Enemies> enemy);

	public:
		Tiles(AEGfxTexture*, const f32 width, const f32 height);
		Image image;
		AEVec2 spawnPos;
		void Update(void);
		void Render(void);

		static void Unload(void);
		static void LoadTex(void);
		//static void CheckTilesPos(std::vector <std::vector<Tiles>*>& TileManager);
		static void CheckPlayerCollision(std::vector <std::vector<Tiles>*>& TileManager, std::vector <Player>& player);

		// Add whole new row of tile.
		static void AddTileRow(std::vector < Tiles>& tile, TileType type, const int count, const f32 width, const f32 height, const AEVec2 pos);
		// Collapse the tile on its left and right if it is collapsible.

		static void CollapseNext(std::vector <Tiles>& tiles);
		// Handles the collision between the enemy and tiles, and enemy with player.

		static void UpdateManager(std::vector <Tiles>& tiles, std::vector <Player>& player, std::vector <Enemies>& enemy);

		// Resets the level.
		static void Reset(std::vector <Tiles>& tiles);
};
