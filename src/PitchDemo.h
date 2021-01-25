#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include "Tiles.h"
#include "Player.h"


namespace Demo
{
	//Level main entry points
	void Init(void);
	void Update(void);
	void Exit(void);

	// Collection of drawing related code.
	void DrawingManager(void);

	// Restarts the level (kinda)
	void Restart(void);

	// Collection of collision related code.
	void CollisionManager(void);

	// Collection of tile collapsing related code.
	void CollapsingManager(void);

	void CheckPauseInput(void);
}