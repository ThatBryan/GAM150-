#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include "Tiles.h"


namespace Demo
{
	void Init(void);
	void Update(void);
	void Exit(void);
	void Free(std::vector <Tiles> tiles);
	void Draw(std::vector <Tiles> tiles);

	void AssignID(std::vector <Tiles>& tiles);
	void CollapseNext(std::vector <Tiles>& tiles);
	void CollisionManager(std::vector <Tiles>& tiles, std::vector <Image> player);

	void Restart(void);
	std::vector <Tiles> AddTileRow(std::vector < Tiles> tile, const s8* filepath, const f32 width, const AEVec2 pos);
}