#pragma once
#include "Tiles.h"
#include "Player.h"
#include "AEEngine.h"
#include "UserInterface.h"
#include "AudioManager.h"
extern SoundSystemClass sound;
namespace Demo
{
	//Level main entry points
	void Load(void);
	void Init(void);
	void Update(void);

	// Collection of drawing related code.
	void Render(void);
	void Load(void);
	void Unload(void);

	// Restarts the level (kinda)asd
	void Restart(void);

	// Collection of collision related code.
	void UpdateManager(void);
	void UpdateOverlay(void);
	// Collection of tile collapsing related code.
	void CollapsingManager(void);
}