#pragma once

class Player;

namespace Background {
	void Load();
	void Init();
	void Update();
	void Render(Player& player);
	void Unload();
	void LerpBackgroundColor(void);
}