/******************************************************************************/
/*!
\file				Username.h
\primary author: 	Seet Min Yi
\par    			email: minyi.seet@digipen.edu
\date   			April 6, 2021
\brief				Header file which contains the function declarations and variables
					for the user to input their username

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
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
	std::string GetUsername();
}