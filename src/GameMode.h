#pragma once

enum class GameMode{Casual = 0, 
					TimeAttack};

namespace GameModeSetting {

	// Complete TimeAttack within a certain time frame?
	static GameMode Mode;

	void Load();
	void Init();
	void Update();
	void Render();
	void Unload();

	void SetModeCasual();
	void SetModeTimeAttack();
	void SwitchModeSetting();
	GameMode GetSetting();
}