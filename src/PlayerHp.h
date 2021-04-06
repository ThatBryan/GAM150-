/******************************************************************************/
/*!
\file				PlayerHp.h
\primary author: 	Bryan Koh Yan Wei
\par    			email: yanweibryan.koh@digipen.edu
\date   			February 28, 2021
\brief

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#pragma once

struct Health {
	short current, max; 
	Health() : current{ 0 }, max{ 0 } {}
};
