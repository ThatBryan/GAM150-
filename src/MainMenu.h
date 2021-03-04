#pragma once
#include "Button.h"
#include "AudioManager.h"

extern AudioManager Audio;

namespace MainMenu
{
	void Init(void);
	void Update(void);
	void Exit(void);

	void Load(void);
	void Unload(void);

	void Buttons_Init(void);
	void DrawButtons(void);
}