#pragma once

namespace UI {
	//Gameplay UI
	void Init();
	void Update();
	void Draw();
	void Unload();
	void DisplayLife(short livesCount);

	// Paused interface.
	void PausedInit();
	void PausedUpdate();
	void PausedRender();
	void PausedUnload();

	// Comfirmation on quit.
	void QuitInit();
	void QuitUpdate();
	void QuitRender();
	void QuitUnload();
}