#pragma once
#include "AEEngine.h"
#include <vector>
#include "Image.h"
#include "Constants.h"

enum class TileType{ Grass = 0, Goal, Safe, Special, Max };
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
		short ID;
		TileType type;
		f64 collapseDelay;
		bool active, isCollapsing;

		Graphics::Rect ColliderAABB;
		Graphics::Rect tile_bottomBB;
		Graphics::Rect tile_topBB;
		Graphics::Rect tile_leftBB;
		Graphics::Rect tile_rightBB;

		// Abstraction
		void DecreaseLifespan(void);
		void Collapse(const Player& player);
		void Collapse(void);
		void CheckPos(void);
		void CheckPlayerGoal(Player& player);
		void CheckEnemyStatus(std::vector <Enemies>& enemy);
		void Update(Player& player);
		
		void TileShake(void);

		public:
		Tiles(AEGfxTexture*, const f32 width, const f32 height);
		Image image;
		AEVec2 spawnPos;
		void Update(void);
		void Render(void);

		inline bool GetActive() const { return active; }

		// Static class Functions
		static void Unload(void);
		static void LoadTex(void);
		// Resets the level.
		static void Reset(std::vector <Tiles>& tiles);
		static void CollapsingManager(TileMgr TileManager);
		static void CheckPlayerGravity(const TileMgr TileManager, Player & ThePlayer);
		static void CheckPlayerCollision(const TileMgr TileManager, Player& ThePlayer);

		// Add whole new row of tile.
		static void AddTileRow(std::vector < Tiles>& tile, TileType type, const int count, const f32 width, const f32 height, const AEVec2 pos);
		static void AddTile(std::vector<Tiles>& tile, TileType type, const f32 width, const f32 height, AEVec2 pos);
		// Collapse the tile on its left and right if it is collapsible.
		static void CollapseNext(std::vector <Tiles>& tiles);
		// Handles the collision between the enemy and tiles, and enemy with player.
		static void UpdateManager(std::vector <Tiles>& tiles, Player& player, std::vector <Enemies>& enemy);
};
// Archieve
//static void CheckTilesPos(std::vector <std::vector<Tiles>*>& TileManager);