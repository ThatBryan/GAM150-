#include "MainMenu.h"
#include "Image.h"
#include "Constants.h"
#include "Graphics.h"
#pragma once

namespace Username {

	static const char* UsernameFile{ "./Assets/Username/username.txt" };
	void Init();
	void Load();
	void Update();
	void Render();
	void Unload();
	void DrawCursor(void);

	void ReadUsernameInput(void);

	void SaveToFile(const char* filepath = UsernameFile);
	void GetUsernameFromFile(const char* filepath = UsernameFile);
}