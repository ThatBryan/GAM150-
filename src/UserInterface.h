#pragma once

namespace UI {
	void Init();
	void Update();
	void Draw();
	void Buttons_Init();
	void Buttons_Unload();

	void DisplayLife(short livesCount);
	void ResetLives();
}