#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include <vector>
#include "Image.h"
#include "Player.h"

enum TileType {NIL, COLLAPSIBLE = 1, GOAL };

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
		void CheckPlayerGoal(std::vector <Player>& Demo_Player);
		void CheckEnemyStatus(std::vector <Enemy> enemy);
};