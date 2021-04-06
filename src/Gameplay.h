#pragma once
/******************************************************************************/
/*!
\file				Gameplay.h
\primary author: 	Bryan Koh Yan Wei
\secondary authors: Dallas Cheong, Seet Min Yi

\date   			February 28, 2021
\brief

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/

namespace Gameplay {

	void Init();
	void Update();
	void Load();
	void Render();
	void Restart();
	void Unload();

	void UpdateManager(void);
}