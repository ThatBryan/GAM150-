#pragma once
#include "Image.h"
#include "Utilities.h"
#include <vector>
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include "Enemy.h"

class Player
{
public:
	Player(const s8* filepath, const f32 width, const f32 height);
	bool active, jump;
	Image sprite;

	void Update_Position(void);
	void CheckEnemyCollision(std::vector <Enemy>& enemy);
};