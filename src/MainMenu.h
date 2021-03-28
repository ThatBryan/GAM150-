#pragma once
#include "AudioManager.h"
#include <iostream>

extern AudioManager Audio;

namespace MainMenu
{
	void Init(void);
	void Buttons_Init(void);
	void Update(void);

	void Load(void);
	void Unload(void);
	void Render(void);

	// Continue from max unlocked level.
	void StartGame();
	void QuitGame();
	inline void placeholder(void) { std::cout << "Feature comming soon!" << std::endl; };
	inline void LockedLevel(void) { std::cout << "Level is locked!\n"; }

	void TestEnemyMovement(void);
	void TestPlayerMovement(void);

	void SwitchToMainMenu(void);
	void SwitchToLevelSelection(void);
	void SwitchToSettings();
}

namespace LevelSelection{
	void Init(void);
	void Update(void);
	void Render(void);
}

namespace Settings {
	void Init();
	void Update();
	void Render();
}