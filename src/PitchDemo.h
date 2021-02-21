#pragma once
#include "Tiles.h"
#include "Player.h"
#include "AEEngine.h"
#include "UserInterface.h"

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
	void UpdateManager(void);

	// Collection of tile collapsing related code.
	void CollapsingManager(void);
}