#pragma once

#include "AudioManager.h"
extern AudioManager Audio;
namespace Demo
{
	//Level main entry points
	void Init(void);
	void Update(void);
	void Exit(void);

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