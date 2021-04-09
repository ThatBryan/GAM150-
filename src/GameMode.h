#pragma once

enum class GameMode{Casual = 0, 
					TimeAttack};

namespace GameModeSetting {

	// Complete TimeAttack within a certain time frame?
	static const float TimeAttackTimer{ 5.0f }; // 10 Mins?

	void Load();
	void Init();
	void Update();
	void Render();
	void Unload();

	void SetModeCasual();
	void SetModeTimeAttack();
	void SwitchModeSetting();
	GameMode GetGameMode();

}

// For TimeAttack stuff.
namespace TimeAttackGameMode {
	void CheckTimer();
}