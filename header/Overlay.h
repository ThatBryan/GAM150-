#pragma once

class Player;

namespace Overlay {
	void Load();
	void Init();
	void Update();
	void Render(Player& player);
	void Unload();
}