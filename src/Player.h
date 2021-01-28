#pragma once
//#include "Tiles.h"
#include "Image.h"
#include "Utilities.h"
#include <vector>
#include "Graphics.h"
#include "AEEngine.h"
#include "Enemy.h"
#include "Constants.h"


class Player
{
	int x;
public:
	Player(const s8* filepath, const f32 width, const f32 height);
	Player();
	bool active, jump, gravity;
	Image sprite;
	Graphics::Rect colliderAABB = Graphics::Rect(player_width, 10.0f);
	AEVec2 startingPos;
	void Update_Position(void);
	void CheckEnemyCollision(std::vector <Enemies>& enemy);
	void Reset(void);
	void Draw(void);
	void GravityManager(void);
	inline void SetWin(void) { this->win = true; }
	inline bool GetWinStatus(void) { return this->win; }

	static void Free(std::vector <Player> player);
private:
	bool win;
};