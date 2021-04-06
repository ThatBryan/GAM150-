/******************************************************************************/
/*!
\file		Background.h
\author 	Bryan Koh Yan Wei
\par    	email: yanweibryan.koh@digipen.edu
\date   	February 28, 2021
\brief

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.

 */
 /******************************************************************************/
#pragma once

class Player;

namespace Background {
	void Load();
	void Init();
	void Update();
	void Render(Player& player);
	void Unload();
	void LerpBackgroundColor(void);
}