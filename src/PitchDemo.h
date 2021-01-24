#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include "Tiles.h"
#include "Player.h"


namespace Demo
{
	void Init(void);
	void Update(void);
	void Exit(void);
	void Free(std::vector <Tiles> tiles);
	
	void Draw(std::vector <Tiles> tiles);
	void DrawingManager(void);

	void Restart(void);
	void AssignID(std::vector <Tiles>& tiles);
	
	void CollapseNext(std::vector <Tiles>& tiles);
	void CollisionManager(void);


	void CheckCollisionTilesPlayer(std::vector <Tiles>& tiles, std::vector <Player> player);
	void CollapsingManager(void);
	
	void AddNewEnemy(const s8* filepath, const AEVec2 pos, const f32 width, const f32 height);
	std::vector <Tiles> AddTileRow(std::vector < Tiles> tile, const s8* filepath, const f32 width, const AEVec2 pos);
}