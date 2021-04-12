/******************************************************************************/
/*!
\file				Gameplay.h
\primary author: 	Bryan Koh Yan Wei
\secondary authors: Dallas Cheong, Seet Min Yi

\date   			April 6, 2021
\brief				Header file which contains the Game loop for the 
					actual Jumperman gameplay.

All content � 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/

#pragma once
namespace Gameplay {

	enum GameLevel {
		TUTORIAL = 0
	};

	void Init();
	void Update();
	void Load();
	void Render();
	void Restart();
	void Unload();

	// For player, tiles, enemy
	void EntitiesUpdate(void);
}