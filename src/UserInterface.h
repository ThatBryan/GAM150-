#pragma once

namespace UI {
	void Init();
	void Update();
	void Draw();
	void Unload();

	void DisplayLife(short livesCount);

	void PausedInit();
	void PausedUpdate();
	void PausedRender();
	void PausedUnload();
}