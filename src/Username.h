#include "MainMenu.h"
#include "Image.h"
#include "Constants.h"
#include "Graphics.h"
#pragma once

namespace Username {
	void Init();
	void Update();
	void Render();
	void Unload();
	void DrawCursor(void);

	void ReadUsernameInput(void);
	static void WriteToFile(const char* filepath);
	static void ReadFromFile(const char* filepath);
}