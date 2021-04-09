/******************************************************************************/
/*!
\file		Background.h
\author 	Bryan Koh Yan Wei
\par    	email: yanweibryan.koh@digipen.edu
\date   	April 6, 2021
\brief		Header file which Contains implementation regarding the
			background during gameplay.
			

All content � 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#pragma once

class Player;

namespace Background {
	void Load();
	void Init();
	void Update();
	void Render(const Player& player);// , const Leaders& leader);
	void Unload();
	void LerpBackgroundColor(void);
}