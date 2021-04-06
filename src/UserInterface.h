/******************************************************************************/
/*!
\file				UserInterface.h
\primary author: 	Bryan Koh Yan Wei
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Header file for UI related code.

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
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