/******************************************************************************/
/*!
\file				MainMenu.h
\primary author: 	Bryan Koh Yan Wei
\secondary author: 	Seet Min Yi
\par    			email: yanweibryan.koh@digipen.edu
\date   			February 28, 2021
\brief

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
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

	void StartGame();
	void QuitGame();

	inline void placeholder(void) { std::cout << "Feature comming soon!" << std::endl; };
	inline void LockedLevel(void) { std::cout << "Level is locked!\n"; }

	void EnemyMovement(void);
	void PlayerMovement(void);

	void SwitchToMainMenu(void);
	void SwitchToLevelSelection(void);
	void SwitchToCreditScreen(void);
	void SwitchToSettings();
	void SwitchToLeaderboard(void);
}

namespace LevelSelection{
	void Init(void);
	void Update(void);
	void Render(void);
	void Unload(void);
}

namespace Options {
	void Init();
	void Update();
	void Render();
	void Unload();
}

namespace Credits {
	void Init();
	void Update();
	void Render();
	void Unload();
}