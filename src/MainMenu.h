#pragma once
#include "AudioManager.h"

extern AudioManager Audio;

namespace MainMenu
{
	void Init(void);
	void Update(void);
	void Free(void);

	void Load(void);
	void Unload(void);
	void Render(void);

	void Buttons_Init(void);
	void DrawButtons(void);

	void StartGame();
	void QuitGame();
	void placeholder(void);
}