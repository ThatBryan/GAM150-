/******************************************************************************/
/*!
\file				GameMode.h
\author: 			Bryan Koh Yan Wei
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 10, 2021
\brief				Header file of GameMode implementation.
					Contains the function declaration for initializing, rendering
					,loading etc that is called from MainMenu.cpp

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#pragma once

enum class GameMode{Casual		= 0, 
					TimeAttack	= 1};

namespace GameModeSetting {

	// Complete TimeAttack within a certain time frame?
	static const float TimeAttackTimer{ 600.0f }; // 10 Mins?

	void Load();
	void Init();
	void Update();
	void Render();
	void Unload();

	void SetModeCasual();
	void SetModeTimeAttack();
	void SwitchToModeSetting();
	GameMode GetGameMode();
}
// For TimeAttack stuff.
namespace TimeAttackGameMode {
	void CheckTimer();
}