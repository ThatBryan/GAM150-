#pragma once
#include "AudioManager.h"
#include <iostream>

extern AudioManager Audio;

namespace MainMenu
{
	void Init(void);
	void Update(void);

	void Load(void);
	void Unload(void);
	void Render(void);

	void Buttons_Init(void);

	void StartGame();
	void QuitGame();
	inline void placeholder(void) { std::cout << "Feature comming soon!" << std::endl; };
	void TestEnemyMovement(void);
	void TestPlayerMovement(void);

	// Min yi's
	void DrawButtons(void);
}