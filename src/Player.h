#pragma once
#include "Image.h"
#include "Utilities.h"
#include <vector>
#include "AEEngine.h"
#include "Enemy.h"
#include "Constants.h"

class Player
{
public:
	Player(const s8* filepath, const f32 width, const f32 height);
	bool active, jump;
	Image sprite;
	AEVec2 startingPos;
	void Update_Position(void);
	void CheckEnemyCollision(std::vector <Enemies>& enemy);
	void Reset(void);
	void Draw(void);
	inline void SetWin(void) { this->win = true; }
	inline bool GetWinStatus(void) { return this->win; }

private:
	bool win;
};