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
private:
	bool win;

public:
	Player(const s8* filepath, const f32 width, const f32 height);
	bool active, jump, gravity;
	Image sprite;
	Graphics::Rect colliderAABB {player_width, 10.0f };
	AEVec2 startingPos;
	void Update_Position(void);
	void Update(void);
	void CheckEnemyCollision(std::vector <Enemies>& enemy);
	void Reset(void);
	void Draw(void);
	//void GravityManager(void);
	inline void SetPlayerWin(void) { win = true; }
	inline bool GetWinStatus(void) { return win; }

	static void Free(std::vector <Player> player);
};